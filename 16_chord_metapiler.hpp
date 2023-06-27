/************************************************************************************************************************
**
** Copyright 2022-2023 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
**
** This file is part of cpp_cctmp_library.
**
** cpp_cctmp_library is free software: you can redistribute it and/or modify it under the terms
** of the GNU General Public License as published by the Free Software Foundation, either version 3
** of the License, or (at your option) any later version.
**
** cpp_cctmp_library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
** without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License along with cpp_cctmp_library.
** If not, see <http://www.gnu.org/licenses/>.
**
************************************************************************************************************************/

// metapiler:

namespace chord {

	template<typename T>
	nik_ce auto U_store_T					= cctmp::U_store_T<T>;

	template<auto... Vs>
	nik_ce auto U_pack_Vs					= cctmp::U_pack_Vs<Vs...>;

	nik_ce auto U_null_Vs					= cctmp::U_null_Vs;

	nik_ce auto H_id					= cctmp::H_id;

	nik_ce auto _id_					= cctmp::_id_;

	template<auto f>
	nik_ce auto _wrap_					= cctmp::_wrap_<f>;

	nik_ce auto _map_					= cctmp::_map_;
	nik_ce auto _push_					= cctmp::_push_;

	nik_ce auto _read_only_					= cctmp::_read_only_;
	nik_ce auto _read_write_				= cctmp::_read_write_;

	template<auto p, auto Op, auto... Vs>
	nik_ce auto unpack_					= cctmp::unpack_<p, Op, Vs...>;

	template<auto H = H_id>
	nik_ce auto _list_					= cctmp::_list_<H>;

	template<typename T>
	nik_ce auto U_custom_T					= cctmp::U_custom_T<T>;

	nik_ce auto _par_at_					= cctmp::_par_at_;

	nik_ce auto _instr_					= cctmp::_instr_;
	nik_ce auto _contr_					= cctmp::_contr_;

	template<auto Key, auto Map>
	nik_ce auto U_cast_lookup				= cctmp::U_cast_lookup<Key, Map>;

	using MI						= cctmp::MI;
	using MN						= cctmp::MN;
	using MT						= cctmp::MT;

	using T_machine_start					= cctmp::T_machine_start;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// source:

	template<typename CharType, auto N>
	nik_ce auto source(const CharType (&s)[N]) { return cctmp::string_literal(s); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// targeter:

/***********************************************************************************************************************/

	template<auto static_scanned>
	struct T_generic_assembly_targeter
	{
		template<auto st, auto ss>
		nik_ces auto U_static_parsed		= U_store_T<T_generic_assembly_parsed<st, ss>>;

		using T_pg_grammar			= T_generic_assembly_grammar;
		using T_pg_tt				= cctmp::T_generic_tt<T_pg_grammar>;

		nik_ces auto static_grammar		= U_store_T<T_pg_grammar>;
		nik_ces auto static_pg_parsed		= T_pg_tt::static_parsed;
		nik_ces auto static_parsed		= U_static_parsed<static_pg_parsed, static_scanned>;

		nik_ces auto scanned			= member_value_U<static_scanned>;
		nik_ces auto toc			= member_value_U<static_parsed>;

		using Total				= typename member_type_U<static_scanned>::Total;

		nik_ces gindex_type instr_length	= MI::dimension; // to parallel machine instrs.
		nik_ces gindex_type lookup_size		= toc.lookup_level.size();
		nik_ces gindex_type label_size		= scanned.total[Total::label];
		nik_ces gindex_type go_into_size	= label_size;

		nik_ces gindex_type jump_size		= scanned.total[Total::jump] + go_into_size;
		nik_ces gindex_type length		= ( 1 * scanned.total[Total::label  ] ) // go_into.
							+ ( 1 * scanned.total[Total::go_to  ] )
							+ ( 1 * scanned.total[Total::branch ] )
							+ ( 2 * scanned.total[Total::test   ] )
							+ ( 2 * scanned.total[Total::vo_id  ] )
							+ ( 2 * scanned.total[Total::copy   ] )
							+ ( 3 * scanned.total[Total::re_turn] ) // upper bound:
							+ ( 4 * scanned.total[Total::replace] ) // (1 * size <= 3 * size)
							+ 1; // to parallel machine contrs.

		using label_type			= cctmp::sequence    < gindex_type , label_size   >;
		using instr_type			= cctmp::sequence    < gindex_type , instr_length >;
		using contr_type			= cctmp::sequence    < instr_type  , length       >;
		using contr_lookup_type			= cctmp::subsequence < instr_type  , lookup_size  >;
		using contr_jump_type			= cctmp::subsequence < instr_type  , jump_size    >;

		struct Mark { enum : gkey_type { none = 0, value }; };

		label_type label;
		contr_type contr;
		contr_lookup_type contr_lookup;
		contr_jump_type contr_jump;

		nik_ce T_generic_assembly_targeter() { translate(); resolve_lookup(); resolve_jump(); }

		nik_ce void translate()
		{
			add_size_instr();

			// can check if function calls are redundant and refactor,
			// but it also might not be necessary if the compiler optimizes.

			auto pad = toc.pad_size();

			if (pad > 0) add_pad_instr(pad);

			for (auto k = toc.hierarchy.cguide(); k.not_end(); ++k)
			{
				auto line_iter = k.next();

				switch (toc.kind(line_iter))
				{
					case Context::assign  : { add_assign_instr (line_iter); break; }
					case Context::apply   : { add_apply_instr  (line_iter); break; }
					case Context::test    : { add_test_instr   (line_iter); break; }
					case Context::label   : { add_label_instr  (line_iter); break; }
					case Context::branch  : { add_branch_instr (line_iter); break; }
					case Context::go_to   : { add_goto_instr   (line_iter); break; }
					case Context::re_turn : { add_return_instr (line_iter); break; }
				}
			}

			set_contr_size(contr.size());
		}

		nik_ce auto call_name      (const cguider & l) const { return toc.has_paste (l) ? MN::recall : MN::call; }
		nik_ce auto call_note      (const cguider & l) const { return toc.has_void  (l) ? MT::void_f : MT::id  ; }
		nik_ce auto first_sign     (const cguider & l) const { return toc.entry_at(l.next()).sign; }
		nik_ce auto first_index    (const cguider & l) const { return toc.entry_at(l.next()).index; }
		nik_ce auto set_label_line (const cguider & l)       { label[first_index(l)] = contr.max(); }

		nik_ce void increment_instr () { contr.upsize(); }
		nik_ce void increment_value () { contr.end()->upsize(); }

		nik_ce void increment_value (gcindex_type value) { contr.end()->push(value); }
		nik_ce void set_instr_pos   (gcindex_type value) { contr.end()->operator [] (MI::pos) = value; }
		nik_ce void set_contr_size  (gcindex_type value) { contr.begin()->push(value); }

		// add:

			nik_ce void add_lookup () { contr_lookup.push(contr.end()); }
			nik_ce void add_jump   () { contr_jump.push(contr.end()); }

			nik_ce void add_size_instr() { increment_instr(); }

			nik_ce void add_instr(gckey_type name, gckey_type note, gckey_type m = Mark::none)
			{
				bool marked = (m == Mark::value);

				increment_value(marked ? _four : _three);
				increment_value(name);
				increment_value(note);
				if (marked) increment_value();

				increment_instr();
			}

			nik_ce void add_pad_instr(gcindex_type pad)
			{
				set_instr_pos(pad);

				add_instr(MN::pad, MT::segment, Mark::value);
				add_instr(MN::pad, MT::id);
			}

			nik_ce void add_replace_instr(const cguider & l)
			{
				auto sign = first_sign(l);

				if (Sign::is_carg(sign))
				{
					set_instr_pos(first_index(l));

					add_instr(MN::reselect, MT::front, Mark::value);
					add_instr(MN::replace, MT::id);
				}
				// else if Sign::is_copy do nothing.
			}

			nik_ce void add_assign_instr(const cguider & l)
			{
				if (toc.has_lookup(l)) add_lookup();

				add_instr(MN::select, MT::pair, Mark::value);
				add_instr(call_name(l), MT::value);

				add_replace_instr(l);
			}

			nik_ce void add_apply_instr(const cguider & l)
			{
				if (toc.has_lookup(l)) add_lookup();

				add_instr(MN::select, MT::pair, Mark::value);
				add_instr(call_name(l), call_note(l));

				if (!toc.has_void(l)) add_replace_instr(l);
			}

			nik_ce void add_test_instr(const cguider & l)
			{
				if (toc.has_lookup(l)) add_lookup();

				add_instr(MN::select, MT::pair, Mark::value);
				add_instr(call_name(l), MT::id);
			}

			nik_ce void add_label_instr(const cguider & l)
				{ set_label_line(l); }

			nik_ce void add_branch_instr(const cguider & l)
			{
				add_jump();

				add_instr(MN::jump, MT::branch, Mark::value);
			}

			nik_ce void add_goto_instr(const cguider & l)
			{
				add_jump();

				add_instr(MN::jump, MT::go_to, Mark::value);
			}

			nik_ce void add_get_lookup_instr(const cguider & l)
			{
				add_lookup();

				add_instr(MN::select, MT::pair, Mark::value);
				add_instr(call_name(l), MT::value);
			}

			nik_ce void add_get_arg_instr(const cguider & l, gcindex_type index)
			{
				set_instr_pos(index);

				add_instr(MN::select, MT::front, Mark::value);
				add_instr(MN::right, MT::id);
			}

			nik_ce void add_return_instr(const cguider & l)
			{
				auto sign = first_sign(l);

				if      (Sign::is_env(sign))  add_get_lookup_instr(l);
				else if (Sign::is_carg(sign)) add_get_arg_instr(l, first_index(l));
				// else if (Sign::is_quote(sign))

				add_instr(MN::first , MT::id);
			}

		// resolve:

			nik_ce void resolve_lookup()
			{
				auto num = 0;
				for (auto k = contr_lookup.begin(); k != contr_lookup.end(); ++k, ++num)
					(*k)->operator [] (MI::pos) = num;
			}

			nik_ce void resolve_jump()
			{
				auto line = toc.jump.cbegin();
				for (auto k = contr_jump.begin(); k != contr_jump.end(); ++k, ++line)
				{
					auto & entry = toc.entry_level[(*line)->entry];
					(*k)->operator [] (MI::pos) = label[entry.index];
				}
			}
	};

/***********************************************************************************************************************/

// automaton:

	template<auto static_scanned>
	struct T_generic_assembly_targeted
	{
		nik_ces auto value	= T_generic_assembly_targeter<static_scanned>{};
		using type		= decltype(value);

		// accessors:

			nik_ces auto instr(gcindex_type i) { return value.contr[i].cbegin(); }
						// cbegin() required due to restrictions on constant expressions.
						// change cbegin() to origin().

		// navigators:

			nik_ces gkey_type   next_name  (gcindex_type i) { return value.contr[i+1][MI::name]; }
			nik_ces gkey_type   next_note  (gcindex_type i) { return value.contr[i+1][MI::note]; }
			nik_ces gindex_type next_index (gcindex_type i) { return i+1; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tail call:

/***********************************************************************************************************************/

	// nothing yet.

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

	template<auto... frames>
	nik_ce auto env = U_pack_Vs<frames...>;

/***********************************************************************************************************************/

// default:

	nik_ce auto default_machine_frame_callable()
	{
		return cctmp::frame
		(
		 	cctmp::U_char,

			cctmp::binding( "id"                    , cctmp::_id_                    ),
			cctmp::binding( "nop"                   , cctmp::_nop_                   ),
			cctmp::binding( "upshift"               , cctmp::_upshift_               ),
			cctmp::binding( "downshift"             , cctmp::_downshift_             ),

			cctmp::binding( "appoint"               , cctmp::_appoint_               ),
			cctmp::binding( "dereference"           , cctmp::_dereference_           ),
			cctmp::binding( "to_bool"               , cctmp::_to_bool_               ),

			cctmp::binding( "not"                   , cctmp::_not_                   ),
			cctmp::binding( "and"                   , cctmp::_and_                   ),
			cctmp::binding( "or"                    , cctmp::_or_                    ),
			cctmp::binding( "implies"               , cctmp::_implies_               ),
			cctmp::binding( "equivalent"            , cctmp::_equivalent_            ),

			cctmp::binding( "equal"                 , cctmp::_equal_                 ),
			cctmp::binding( "is_zero"               , cctmp::_is_zero_               ),
			cctmp::binding( "not_equal"             , cctmp::_not_equal_             ),
			cctmp::binding( "less_than"             , cctmp::_less_than_             ),
			cctmp::binding( "less_than_or_equal"    , cctmp::_less_than_or_equal_    ),
			cctmp::binding( "greater_than"          , cctmp::_greater_than_          ),
			cctmp::binding( "greater_than_or_equal" , cctmp::_greater_than_or_equal_ ),

			cctmp::binding( "add"                   , cctmp::_add_                   ),
			cctmp::binding( "subtract"              , cctmp::_subtract_              ),
			cctmp::binding( "multiply"              , cctmp::_multiply_              ),
			cctmp::binding( "divide"                , cctmp::_divide_                ),
			cctmp::binding( "modulo"                , cctmp::_modulo_                ),

			cctmp::binding( "increment"             , cctmp::_increment_<1>          ),
			cctmp::binding( "decrement"             , cctmp::_increment_<-1>         ),

			cctmp::binding( "is_array"              , cctmp::_is_array_              ),
			cctmp::binding( "array_type"            , cctmp::_array_type_            ),
			cctmp::binding( "array_length"          , cctmp::_array_length_          ),
			cctmp::binding( "array_begin"           , cctmp::_array_begin_           ),
			cctmp::binding( "array_last"            , cctmp::_array_last_            ),
			cctmp::binding( "array_end"             , cctmp::_array_end_             ),
			cctmp::binding( "log_floor"             , cctmp::_log_floor_             ),

			cctmp::binding( "is_sequence"           , cctmp::_is_sequence_           ),
			cctmp::binding( "sequence_type"         , cctmp::_sequence_type_         ),
			cctmp::binding( "sequence_length"       , cctmp::_sequence_length_       )
		);
	};

	nik_ce auto default_machine_frame = _static_callable_<default_machine_frame_callable>;

/***********************************************************************************************************************/

// constant:

	nik_ce auto constant_machine_frame_callable()
	{
		return cctmp::frame
		(
			cctmp::U_char,

			cctmp::binding( "zero"  , _zero  ),
			cctmp::binding( "one"   , _one   ),
			cctmp::binding( "two"   , _two   ),
			cctmp::binding( "three" , _three ),
			cctmp::binding( "four"  , _four  ),
			cctmp::binding( "five"  , _five  ),
			cctmp::binding( "six"   , _six   ),
			cctmp::binding( "seven" , _seven ),
			cctmp::binding( "eight" , _eight ),
			cctmp::binding( "nine"  , _nine  ),
			cctmp::binding( "ten"   , _ten   )
		);
	};

	nik_ce auto constant_machine_frame = _static_callable_<constant_machine_frame_callable>;

/***********************************************************************************************************************/

// recurse:

	template<auto f>
	nik_ce auto recurse_machine_frame_callable()
	{
		return cctmp::frame
		(
			cctmp::U_char,

			cctmp::binding( "this" , f )
		);
	};

	template<auto f>
	nik_ce auto recurse_machine_frame = _static_callable_<recurse_machine_frame_callable<f>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// metapiler:

/***********************************************************************************************************************/

// interface:

	template<auto callable_source, auto Env = U_null_Vs>
	struct T_generic_assembly_metapiler
	{
		nik_ces auto static_src		= _static_callable_<callable_source>;
		nik_ces auto static_scanned	= U_store_T<T_generic_assembly_scanned<static_src>>;
		nik_ces auto static_targeted	= U_store_T<T_generic_assembly_targeted<static_scanned>>;

		nik_ces auto & targeted		= member_value_U<static_targeted>;
		nik_ces auto & toc		= targeted.toc;
		nik_ces auto & lookup		= toc.lookup_level;

		nik_ces auto env		= eval<_push_, H_id, Env, default_machine_frame>;

		// toc:

			struct T_entry_poses
			{
				template<auto n>
				nik_ces auto result = eval<_par_segment_, lookup[n].size()>;

			}; nik_ces auto _entry_poses_ = U_custom_T<T_entry_poses>;

		// lookup:

			using pair_type  = cctmp::pair<gindex_type, gindex_type>;
			using citer_type = citerator<strlit_type>;

			nik_ces void update_frame(pair_type & pos, bool & match, citer_type k)
			{
				if (!match)
				{
					match   = k.not_end();
					pos.v0 += not match;
					pos.v1  = k.left_size();
				}
			}

			template<auto n, auto m, auto... static_frames>
			nik_ces auto find_frame()
			{
				nik_ce const auto & entry = toc.lookup_entry(n, m);

				pair_type pos;
				bool match{false};

				(update_frame(pos, match, member_value_U<static_frames>.contains(entry)), ...);

				return pos;
			}

			template<auto n, auto m, auto... static_frames>
			nik_ces auto resolve(nik_avp(T_pack_Vs<static_frames...>*))
			{
				nik_ce auto record	 = find_frame<n, m, static_frames...>();
				nik_ce auto position     = record.v0;
				nik_ce auto subposition  = record.v1;
				nik_ce auto static_frame = eval<_par_at_, position, static_frames...>;

				return U_cast_lookup<subposition, static_frame>;
			}

			template<auto this_f>
			nik_ces auto resolve_recurse()
			{
				return U_cast_lookup<_zero, recurse_machine_frame<this_f>>;
			}
	
			template<auto this_f, auto n, auto m>
			nik_ces auto resolve_value()
			{
				nik_ce auto sign = toc.lookup_entry_sign(n, m);

				if nik_ce      (Sign::is_env(sign))     return resolve<n, m>(env);
				else if nik_ce (Sign::is_recurse(sign)) return resolve_recurse<this_f>();
				else                                    return toc.lookup_entry_index(n, m);
			}

			template<auto n, auto m>
			nik_ces auto resolve_type()
			{
				nik_ce auto sign = toc.lookup_entry_sign(n, m);

				if nik_ce (Sign::is_marg(sign)) return _read_write_;
				else                            return _id_;
			}

			template<auto this_f, auto n, auto m0>
			nik_ces auto resolve_line_single(nik_avp(T_pack_Vs<m0>*))
			{
				nik_ce auto f_pack = U_pack_Vs<resolve_value<this_f, n, m0>()>;
				nik_ce auto t_pack = U_pack_Vs<resolve_type<n, m0>()>;

				return eval<_list_<>, f_pack, t_pack>;
			}

			template<auto this_f, auto n, auto m0, auto m1, auto... ms>
			nik_ces auto resolve_void_swap(nik_avp(T_pack_Vs<m0, m1, ms...>*))
			{
				nik_ce auto first  = resolve_value<this_f, n, m1>();
				nik_ce auto second = resolve_value<this_f, n, m0>();
				nik_ce auto f_pack = U_pack_Vs<first, second, resolve_value<this_f, n, ms>()...>;
				nik_ce auto t_pack = U_pack_Vs<_read_write_, resolve_type<n, ms>()...>;

				return eval<_list_<>, f_pack, t_pack>;
			}

			template<auto this_f, auto n, auto m0, auto... ms>
			nik_ces auto resolve_void(nik_avp(T_pack_Vs<m0, ms...>*))
			{
				nik_ce auto first  = resolve_value<this_f, n, m0>();
				nik_ce auto f_pack = U_pack_Vs<first, resolve_value<this_f, n, ms>()...>;
				nik_ce auto t_pack = U_pack_Vs<resolve_type<n, ms>()...>;

				return eval<_list_<>, f_pack, t_pack>;
			}

			template<auto this_f, auto n, typename Pack>
			nik_ces auto resolve_line_void(Pack p)
			{
				nik_ce auto sign = toc.lookup_entry_sign(n, _zero);

				if nik_ce (Sign::is_marg(sign)) return resolve_void_swap<this_f, n>(p);
				else                            return resolve_void<this_f, n>(p);
			}

			template<auto this_f, auto n, auto m0, auto... ms>
			nik_ces auto resolve_line_apply(nik_avp(T_pack_Vs<m0, ms...>*))
			{
				nik_ce auto first  = resolve_value<this_f, n, m0>();
				nik_ce auto f_pack = U_pack_Vs<first, resolve_value<this_f, n, ms>()...>;
				nik_ce auto t_pack = U_pack_Vs<resolve_type<n, ms>()...>;

				return eval<_list_<>, f_pack, t_pack>;
			}

			template<auto this_f, auto n, typename Pack>
			nik_ces auto unpack_entry(Pack p)
			{
				if nik_ce      (lookup[n].is_assign()) return resolve_line_single <this_f, n>(p);
				else if nik_ce (lookup[n].is_return()) return resolve_line_single <this_f, n>(p);
				else if nik_ce (lookup[n].is_void  ()) return resolve_line_void   <this_f, n>(p);
				else                                   return resolve_line_apply  <this_f, n>(p);
			}

			template<auto this_f, auto... l_ps, auto... e_ps>
			nik_ces auto to_pack(nik_avp(T_pack_Vs<l_ps...>*), nik_avp(T_pack_Vs<e_ps...>*))
			{
				return eval<_list_<>, unpack_entry<this_f, l_ps>(e_ps)...>;
			}

			template<auto this_f>
			nik_ces auto to_lookup_pack()
			{
				nik_ce auto line_poses  = eval<_par_segment_, lookup.size()>;
				nik_ce auto entry_poses = unpack_<line_poses, _map_, H_id, _entry_poses_>;

				return to_pack<this_f>(line_poses, entry_poses);
			}

			template<auto this_f>
			nik_ces auto resolve_lookup = to_lookup_pack<this_f>();

		// function:

			template<typename S, typename... Ts>
			nik_ces S result(Ts... vs)
			{
				nik_ce auto out_type = U_store_T<S>;
				nik_ce auto contr    = static_targeted;
				nik_ce auto this_f   = _wrap_<result<S, Ts...>>;
				nik_ce auto lookup   = resolve_lookup<this_f>;

				return T_machine_start::template result
				<
					out_type, contr, lookup, modify_type<_read_only_, Ts>...

				>((modify_type<_read_only_, Ts>) vs...);
			}
	};

	// syntactic sugar:

		template<auto callable_source, auto Env, typename S, typename... Ts>
		nik_ce auto generic_assembly_apply(Ts... vs)
		{
			using T_function = T_generic_assembly_metapiler<callable_source, Env>;

			return T_function::template result<S, Ts...>(vs...);
		}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

