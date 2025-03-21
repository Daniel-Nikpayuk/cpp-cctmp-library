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
		return frame
		(
		 	U_gchar_type,

			binding( "id"                    , _id_                    ),
			binding( "first"                 , _first_                 ),
			binding( "upshift"               , _upshift_               ),
			binding( "downshift"             , _downshift_             ),

			binding( "dereference"           , _dereference_           ),
			binding( "appoint"               , _appoint_               ),

			binding( "not"                   , _not_                   ),
			binding( "and"                   , _and_                   ),
			binding( "or"                    , _or_                    ),
			binding( "implies"               , _implies_               ),
			binding( "equivalent"            , _equivalent_            ),

			binding( "equal"                 , _equal_                 ),
			binding( "is_zero"               , _is_zero_               ),
			binding( "not_equal"             , _not_equal_             ),
			binding( "not_zero"              , _not_zero_              ),
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

			binding( "@"                     , _id_                    ),
			binding( "*"                     , _dereference_           ),
			binding( "+"                     , _increment_<1>          ),
			binding( "-"                     , _increment_<-1>         )
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
									callable_source, extended_env, out_types
								>;

		template<typename... Ts>
		nik_ces auto result(Ts... vs) { return T_metapile_apply::template result<Ts...>(vs...); }
	};

/***********************************************************************************************************************/

// fast apply:

	template<auto contr, auto callable_source, auto initial_env, typename... OutTypes>
	struct T_fast_apply
	{
		nik_ces auto extended_env		= push_<initial_env, chord_default_frame>;
		nik_ces auto out_types			= U_pack_Ts<OutTypes...>;
		using T_metapile_fast_apply		= assembly::T_metapile_fast_apply
							<
								contr, callable_source, extended_env, out_types
							>;

		template<typename... Ts>
		nik_ces auto result(Ts... vs) { return T_metapile_fast_apply::template result<Ts...>(vs...); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

