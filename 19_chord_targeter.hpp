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

// targeter:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// targeter:

/***********************************************************************************************************************/

// interface:

	template<auto static_scanned>
	struct T_chord_assembly_targeter
	{
		template<auto st, auto ss>
		nik_ces auto U_static_parsed		= U_store_T<T_chord_assembly_parsed<st, ss>>;

		using T_pg_grammar			= T_chord_assembly_grammar;
		using T_pg_tt				= cctmp::T_generic_tt<T_pg_grammar>;

		nik_ces auto static_grammar		= U_store_T<T_pg_grammar>;
		nik_ces auto static_pg_parsed		= T_pg_tt::static_parsed;
		nik_ces auto static_parsed		= U_static_parsed<static_pg_parsed, static_scanned>;

		nik_ces auto & scanned			= member_value_U<static_scanned>;
		nik_ces auto & toc			= member_value_U<static_parsed>;

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

		nik_ce T_chord_assembly_targeter() { translate(); resolve_lookup(); resolve_jump(); }

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
	struct T_chord_assembly_targeted
	{
		nik_ces auto value	= T_chord_assembly_targeter<static_scanned>{};
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

			cctmp::binding( "dereference"           , cctmp::_dereference_           ),
			cctmp::binding( "appoint"               , cctmp::_appoint_               ),
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

} // namespace chord

