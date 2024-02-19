/************************************************************************************************************************
**
** Copyright 2022-2024 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// frame:

/***********************************************************************************************************************/

// default:

	nik_ce auto chord_default_frame_callable()
	{
		return cctmp::frame
		(
		 	U_gchar_type,

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
			cctmp::binding( "not_zero"              , cctmp::_not_zero_              ),
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
			cctmp::binding( "array_size"            , cctmp::_array_size_            ),
			cctmp::binding( "array_begin"           , cctmp::_array_begin_           ),
			cctmp::binding( "array_last"            , cctmp::_array_last_            ),
			cctmp::binding( "array_end"             , cctmp::_array_end_             ),
			cctmp::binding( "log_floor"             , cctmp::_log_floor_             ),

			cctmp::binding( "is_sequence"           , cctmp::_is_sequence_           ),
			cctmp::binding( "sequence_type"         , cctmp::_sequence_type_         ),
			cctmp::binding( "sequence_length"       , cctmp::_sequence_length_       )
		);
	};

	nik_ce auto chord_default_frame = _static_callable_<chord_default_frame_callable>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// metapile:

/***********************************************************************************************************************/

// interface:

	template
	<
		auto callable_source,
		auto initial_env,

		auto contr_size =  512,
		auto stack_size =  512,
		auto model_size = 1024
	>
	nik_ce auto metapile = assembly::metapile
	<
		T_chord_grammar, generator::T_parser_generator_scanned, generator::T_parser_generator_parsed,
		T_chord_parsed, callable_source, push_<initial_env, chord_default_frame>,
		contr_size, stack_size, model_size
	>;

/***********************************************************************************************************************/

// apply:

	template<auto callable_source, auto initial_env, typename... OutTypes>
	struct T_apply
	{
		using T_grammar					= T_chord_grammar;
		template<auto... Vs> using T_pg_scanned		= generator::T_parser_generator_scanned<Vs...>;
		template<auto... Vs> using T_pg_parsed		= generator::T_parser_generator_parsed<Vs...>;
		template<auto... Vs> using T_parsed		= T_chord_parsed<Vs...>;
		nik_ces auto extended_env			= push_<initial_env, chord_default_frame>;
		nik_ces auto out_types				= U_pack_Ts<OutTypes...>;
		using T_metapile_apply				= assembly::T_metapile_apply
								<
									T_grammar, T_pg_scanned, T_pg_parsed, T_parsed,
									callable_source, _chord_subsource_,
									extended_env, out_types
								>;

		template<typename... Ts>
		nik_ces auto result(Ts... vs) { return T_metapile_apply::template result<Ts...>(vs...); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord
