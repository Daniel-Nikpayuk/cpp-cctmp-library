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

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// segment:

/***********************************************************************************************************************/

	struct T_interpreter_segment
	{
		nik_ces auto sH0 = U_pack_Vs<H_id>;
		nik_ces auto  H0 = U_pack_Vs<_car_, sH0>;

		template<auto n>
		nik_ces auto contr = controller
		<
			instruction < IN::call , IT::praxis , PN::segment , n >,
			instruction < IN::halt , IT::eval                     >
		>;

		template<auto d, auto n, auto m = _zero>
		nik_ces auto result = T_interpreter_start::template result<d, contr<n>, m>(H0);
	};

	nik_ce auto _dpar_segment_ = U_custom_T<T_interpreter_segment>;
	nik_ce auto  _par_segment_ = ID::template with_initial_depth<_dpar_segment_>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// chord:

	// todo:

		// 1. allow arg_subpose to compose void functions (change _assign_ to void).

/***********************************************************************************************************************/

// pose:

	template<auto Name, auto f, auto gs_p>
	struct T_arg_pose
	{
		nik_ces auto lookup = U_pack_Vs<f, gs_p>;

		template<auto m = _zero, auto n = _one>
		nik_ces auto contr = controller
		<
			instruction< CN::select , n >,
			instruction< Name           >,
			instruction< CN::select , m >,
			instruction< CN::apply      >,
			instruction< CN::first      >
		>;

		template<typename... Ts>
		nik_ces auto result(Ts... vs) { return T_chain_start::template result<contr<>, lookup>(vs...); }

	}; template<auto Name, auto f, auto gs_p>
		nik_ce auto _arg_pose_ = U_store_T<T_arg_pose<Name, f, gs_p>>;

	// syntactic sugar:

		template<auto f, auto... gs>
		nik_ce auto arg_subpose = _arg_pose_<CN::mapwise, f, U_pack_Vs<gs...>>;

		template<auto f, auto... gs>
		nik_ce auto arg_compose = _arg_pose_<CN::applywise, f, U_pack_Vs<gs...>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// frame:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// binding:

/***********************************************************************************************************************/

	template<typename CharType, auto Size, typename ValueType>
	struct binding
	{
		using char_type			= CharType;
		using string_type		= char_type const*;
		using size_type			= decltype(Size);

		nik_ces size_type size		= Size - 1; // best policy?
		nik_ces auto value		= U_restore_T<ValueType>;
		using value_type		= decltype(value);

		string_type string;

		nik_ce binding(const CharType (&s)[Size], ValueType) : string{s} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// table:

/***********************************************************************************************************************/

	template<typename CharType, typename... Bindings>
	struct table
	{
		using char_type			= T_restore_T<CharType>;
		using cchar_type		= char_type const;
		using string_type		= char_type const*;
		using cstring_type		= string_type const;

		nik_ces auto size		= sizeof...(Bindings);
		using size_type			= decltype(size);

		nik_ces auto sizes		= array<size_type, Bindings::size...>;
		nik_ces auto values		= U_pack_Vs<Bindings::value...>;

		cstring_type string[size];

		nik_ce table(CharType, Bindings... bs) : string{bs.string...} { }
	};

/***********************************************************************************************************************/

// function:

	template<auto f, typename StringType>
	nik_ce auto key_function(StringType str_begin, StringType str_end)
	{
		nik_ce auto table		= f();

		using table_type		= decltype(table);
		using size_type			= typename table_type::size_type;
		using string_type		= typename table_type::string_type;
		using cstring_type		= typename table_type::cstring_type;

		cstring_type *key		= table.string;
		cstring_type *key_end		= key + table.size;

		size_type *size			= table.sizes;

		while (key != key_end)
		{
			string_type b		= *key;
			string_type e		= b + *(size++);

			if (ptr_diff_equal(b, e, str_begin, str_end)) break;

			++key;
		}

		return key - table.string;
	}

	template<auto f>
	nik_ce auto make_key_function()
	{
		using table_type	= T_out_type<f>;
		using string_type	= typename table_type::string_type;

		nik_ce auto values	= table_type::values;
		nik_ce auto key_f	= key_function<f, string_type>;

		return U_pack_Vs<key_f, values>;
	}

	template<auto f>
	nik_ce auto make_frame = make_key_function<f>();

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// default:

	nik_ce auto default_machine_frame()
	{
		return table
		(
		 	U_char,

			binding( "id"                    , _id_                    ),
			binding( "nop"                   , _nop_                   ),
			binding( "upshift"               , _upshift_               ),
			binding( "downshift"             , _downshift_             ),

			binding( "assign"                , _assign_                ),
			binding( "dereference"           , _dereference_           ),
			binding( "to_bool"               , _to_bool_               ),

			binding( "not"                   , _not_                   ),
			binding( "and"                   , _and_                   ),
			binding( "or"                    , _or_                    ),
			binding( "implies"               , _implies_               ),
			binding( "equivalent"            , _equivalent_            ),

			binding( "equal"                 , _equal_                 ),
			binding( "is_zero"               , _is_zero_               ),
			binding( "not_equal"             , _not_equal_             ),
			binding( "less_than"             , _less_than_             ),
			binding( "less_than_or_equal"    , _less_than_or_equal_    ),
			binding( "greater_than"          , _greater_than_          ),
			binding( "greater_than_or_equal" , _greater_than_or_equal_ ),

			binding( "add"                   , _add_                   ),
			binding( "subtract"              , _subtract_              ),
			binding( "multiply"              , _multiply_              ),
			binding( "divide"                , _divide_                ),
			binding( "modulo"                , _modulo_                ),

			binding( "increment"             , _increment_<1>          ),
			binding( "decrement"             , _increment_<-1>         ),

			binding( "is_array"              , _is_array_              ),
			binding( "array_type"            , _array_type_            ),
			binding( "array_size"            , _array_size_            ),
			binding( "array_begin"           , _array_begin_           ),
			binding( "array_last"            , _array_last_            ),
			binding( "array_end"             , _array_end_             ),
			binding( "log_floor"             , _log_floor_             ),

			binding( "is_sequence"           , _is_sequence_           ),
			binding( "sequence_type"         , _sequence_type_         ),
			binding( "sequence_size"         , _sequence_size_         ),
			binding( "to_sequence"           , _to_sequence_           ),
			binding( "sequence_begin"        , _sequence_begin_        ),
			binding( "sequence_last"         , _sequence_last_         ),
			binding( "sequence_end"          , _sequence_end_          ),

			binding( "is_tuple"              , _is_tuple_              ),
			binding( "tuple_type"            , _tuple_type_            ),
			binding( "tuple_size"            , _tuple_size_            ),
			binding( "to_tuple"              , _to_tuple_              )
		);
	};

	nik_ce auto default_machine_lookup = make_frame<default_machine_frame>;

/***********************************************************************************************************************/

// constant:

	nik_ce auto constant_machine_frame()
	{
		return table
		(
		 	U_char,

			binding( "zero"  , _constant_< _zero  >),
			binding( "one"   , _constant_< _one   >),
			binding( "two"   , _constant_< _two   >),
			binding( "three" , _constant_< _three >),
			binding( "four"  , _constant_< _four  >),
			binding( "five"  , _constant_< _five  >),
			binding( "six"   , _constant_< _six   >),
			binding( "seven" , _constant_< _seven >),
			binding( "eight" , _constant_< _eight >),
			binding( "nine"  , _constant_< _nine  >),
			binding( "ten"   , _constant_< _ten   >)
		);
	};

	nik_ce auto constant_machine_lookup = make_frame<constant_machine_frame>;

/***********************************************************************************************************************/

// environment:

	template<auto... frames>
	nik_ce auto env = U_pack_Vs<frames...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic assembly:

/***********************************************************************************************************************/

// survey:

	struct survey
	{
		template<auto frame>
		nik_ces auto find(gstring_type start, gstring_type finish)
		{
			nik_ce auto key_f  = unpack_<frame, _car_>;
			nik_ce auto values = unpack_<frame, _cadr_>;
			nik_ce auto size   = unpack_<values, _length_>;

			auto key = key_f(start, finish);

			return survey(key, size);
		}

		nik_ces auto search(const survey *begin, const survey *end)
		{
			auto k = begin;

			while (k != end)
			{
				if (k->match) break; 

				++k;
			}

			return (k - begin);
		}

		bool match;
		gindex_type key;

		nik_ce survey(gcindex_type _k, gcindex_type size) : match{_k != size}, key{_k} { }
	};

/***********************************************************************************************************************/

// automaton:

	template<auto SourceCallable, auto Env = U_null_Vs>
	struct T_generic_assembly_metapiler
	{
		nik_ces auto env	= eval<_push_, H_id, Env, default_machine_lookup>;
		nik_ces auto target	= T_generic_assembly_targeter<SourceCallable>::value;
		nik_ces auto toc	= target.toc;

		// toc:

			struct T_entry_poses
			{
				template<auto n>
				nik_ces auto result = eval
				<
					_par_segment_, toc.lookup_line_size(n), toc.lookup_line_shift(n)
				>;

			}; nik_ces auto _entry_poses_ = U_custom_T<T_entry_poses>;

		// target:

			struct T_instr_poses
			{
				template<auto n>
				nik_ces auto result = eval<_par_segment_, target.instr_size(n)>;

			}; nik_ces auto _instr_poses_ = U_custom_T<T_instr_poses>;

		// controller:

			template<auto n, auto... ms>
			nik_ces auto unpack_instr(nik_avp(T_pack_Vs<ms...>*))
			{
				return eval<_instr_, target.instr_at(n, ms)...>;
			}

			template<auto... c_ps, auto... i_ps>
			nik_ces auto to_contr(nik_avp(T_pack_Vs<c_ps...>*), nik_avp(T_pack_Vs<i_ps...>*))
			{
				return eval<_contr_, unpack_instr<c_ps>(i_ps)...>;
			}

			nik_ces auto static_target_contr()
			{
				nik_ce auto contr_poses = eval<_par_segment_, target.contr.size()>;
				nik_ce auto instr_poses = unpack_<contr_poses, _map_, H_id, _instr_poses_>;

				return to_contr(contr_poses, instr_poses);
			}

			nik_ces auto contr = static_target_contr();

		// lookup:

			template<auto n, auto m, auto... frames>
			nik_ces auto resolve(nik_avp(T_pack_Vs<frames...>*))
			{
				nik_ce auto   start    = toc.lookup_entry_start(n, m);
				nik_ce auto   finish   = toc.lookup_entry_finish(n, m);

				nik_ce survey record[] = { survey::find<frames>(start, finish)... };
				nik_ce auto   pos      = survey::search(record, record + sizeof...(frames));

				nik_ce auto   frame    = eval<_par_at_, pos, frames...>;
				nik_ce auto   values   = unpack_<frame, _cadr_>;

				return unpack_<values, _par_at_, record[pos].key>;
			}

			template<auto that_f, auto n, auto m>
			nik_ces auto resolve_value()
			{
				nik_ce auto sign = toc.lookup_entry_sign(n, m);

				if nik_ce      (Sign::is_recurse(sign)) return that_f;
				else if nik_ce (Sign::is_lookup (sign)) return resolve<n, m>(env);
				else                                    return toc.lookup_entry_index(n, m);
			}

			template<auto this_f, auto n, auto m>
			nik_ces auto resolve_first() { return resolve_value<this_f, n, m>(); }

			template<auto this_f, auto n, auto m>
			nik_ces auto resolve_rest() { return resolve_value<_constant_<this_f>, n, m>(); }

			template<auto n, auto m>
			nik_ces auto resolve_type()
			{
				nik_ce auto sign = toc.lookup_entry_sign(n, m);

				if constexpr (Sign::is_marg(sign)) return _read_write_;
				else                               return _id_;
			}

			template<auto this_f, auto n, auto m0, auto... ms>
			nik_ces auto resolve_void_operator(nik_avp(T_pack_Vs<m0, ms...>*))
			{
				nik_ce auto first  = resolve_first<this_f, n, m0>();
				nik_ce auto second = resolve_rest<this_f, n, _zero>();
				nik_ce auto f_pack = U_pack_Vs<first, second, resolve_rest<this_f, n, ms>()...>;
				nik_ce auto t_pack = U_pack_Vs<_read_write_, resolve_type<n, ms>()...>;

				return eval<_list_<>, f_pack, t_pack>;
			}

			template<auto this_f, auto n, auto m0, auto... ms>
			nik_ces auto resolve_def_operator(nik_avp(T_pack_Vs<m0, ms...>*))
			{
				nik_ce auto first  = resolve_first<this_f, n, m0>();
				nik_ce auto f_pack = U_pack_Vs<first, resolve_rest<this_f, n, ms>()...>;
				nik_ce auto t_pack = U_pack_Vs<resolve_type<n, ms>()...>;

				return eval<_list_<>, f_pack, t_pack>;
			}

			template<auto this_f, auto n, typename Pack>
			nik_ces auto unpack_entry(Pack p)
			{
				if constexpr (toc.lookup_line_void(n)) return resolve_void_operator<this_f, n>(p);
				else                                   return resolve_def_operator<this_f, n>(p);
			}

			template<auto this_f, auto... l_ps, auto... e_ps>
			nik_ces auto to_pack(nik_avp(T_pack_Vs<l_ps...>*), nik_avp(T_pack_Vs<e_ps...>*))
			{
				return eval<_list_<>, unpack_entry<this_f, l_ps>(e_ps)...>;
			}

			template<auto this_f>
			nik_ces auto to_lookup_pack()
			{
				nik_ce auto line_poses  = eval<_par_segment_, toc.lookup.size()>;
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
				nik_ce auto this_f   = _wrap_<result<S, Ts...>>;
				nik_ce auto lookup   = resolve_lookup<this_f>;

				return T_machine_start::template result
				<
					out_type, contr, lookup, modify_type<_read_only_, Ts>...

				>((modify_type<_read_only_, Ts>) vs...);
			}
	};

	// syntactic sugar:

		template<typename CharType, auto Size>
		nik_ce auto source(const CharType (&s)[Size]) { return T_generic_assembly_source(s); }

		template<auto SourceCallable, auto Env, typename S, typename... Ts>
		nik_ce auto generic_assembly_apply(Ts... vs)
		{
			using T_function = T_generic_assembly_metapiler<SourceCallable, Env>;

			return T_function::template result<S, Ts...>(vs...);
		}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

