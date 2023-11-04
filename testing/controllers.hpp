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

#include<cstdio>

#define NIK_PARSER_GENERATOR_PARSER_OBJ       "../transition_tables/00_parser_generator_parser.hpp"
#define NIK_CHORD_ASSEMBLY_SCANNER_PARSER_OBJ "../transition_tables/01_chord_assembly_scanner.hpp"
#define NIK_CHORD_ASSEMBLY_PARSER_OBJ         "../transition_tables/02_chord_assembly_parser.hpp"

#define NIK_PARSER_GENERATOR_PARSER // bug: currently all need to be on or all off.
#define NIK_CHORD_ASSEMBLY_SCANNER_PARSER
#define NIK_CHORD_ASSEMBLY_PARSER

/***********************************************************************************************************************/

#include"define_macros.hpp"

#include"00_cctmp/00_grammar.hpp"
#include"00_cctmp/01_argument.hpp"
#include"00_cctmp/02_parameter.hpp"
#include"00_cctmp/03_scope.hpp"
#include"00_cctmp/04_relation.hpp"
#include"00_cctmp/05_praxis.hpp"
#include"00_cctmp/06_algorithm.hpp"
#include"00_cctmp/07_interpreter.hpp"
#include"00_cctmp/08_graph.hpp"

#include"01_machine/00_lookup_state.hpp"
#include"01_machine/01_lookup_action.hpp"
#include"01_machine/02_chain_state.hpp"
#include"01_machine/03_chain_action.hpp"
#include"01_machine/04_cycle_state.hpp"
#include"01_machine/05_cycle_action.hpp"
#include"01_machine/06_assembly_state.hpp"
#include"01_machine/07_assembly_action.hpp"

//#include"documentation/01_lookup_controllers.hpp"
//#include"documentation/02_chain_controllers.hpp"
//#include"documentation/03_cycle_controllers.hpp"
//#include"documentation/04_assembly_controllers.hpp"

#include"undef_macros.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

// default:

	constexpr auto default_machine_frame_callable()
	{
		return frame
		(
		 	U_char,

			binding( "id"                    , _id_                    ),
			binding( "nop"                   , _nop_                   ),
			binding( "upshift"               , _upshift_               ),
			binding( "downshift"             , _downshift_             ),

			binding( "dereference"           , _dereference_           ),
			binding( "appoint"               , _appoint_               ),
			binding( "to_bool"               , _to_bool_               ),

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

			binding( "is_array"              , _is_array_              ),
			binding( "array_type"            , _array_type_            ),
			binding( "array_size"            , _array_size_            ),
			binding( "array_begin"           , _array_begin_           ),
			binding( "array_last"            , _array_last_            ),
			binding( "array_end"             , _array_end_             ),
			binding( "log_floor"             , _log_floor_             ),

			binding( "is_sequence"           , _is_sequence_           ),
			binding( "sequence_type"         , _sequence_type_         ),
			binding( "sequence_length"       , _sequence_length_       )
		);
	};

	constexpr auto default_machine_frame = _static_callable_<default_machine_frame_callable>;

/***********************************************************************************************************************/

// constant:

	constexpr auto constant_machine_frame_callable()
	{
		return frame
		(
			U_char,

			binding( "zero"  , _zero  ),
			binding( "one"   , _one   ),
			binding( "two"   , _two   ),
			binding( "three" , _three ),
			binding( "four"  , _four  ),
			binding( "five"  , _five  ),
			binding( "six"   , _six   ),
			binding( "seven" , _seven ),
			binding( "eight" , _eight ),
			binding( "nine"  , _nine  ),
			binding( "ten"   , _ten   )
		);
	};

	constexpr auto constant_machine_frame = _static_callable_<constant_machine_frame_callable>;

/***********************************************************************************************************************/

// source:

	template<typename CharType, auto N>
	constexpr auto source(const CharType (&s)[N]) { return cctmp::string_literal{s}; }

/***********************************************************************************************************************/

// one:

	constexpr auto one_f() { return source("one"); }

	constexpr auto one_str = _static_callable_<one_f>;

/***********************************************************************************************************************/

// add:

	constexpr auto add_f() { return source("add"); }

	constexpr auto add_str = _static_callable_<add_f>;

/***********************************************************************************************************************/

// multiply:

	constexpr auto multiply_f() { return source("multiply"); }

	constexpr auto multiply_str = _static_callable_<multiply_f>;

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	printf("%d\n", machine::lookup_env<one_str>(U_pack_Vs<constant_machine_frame>));

	//	constexpr auto f  = machine::_subpose_<_multiply_, _decrement_<>, _id_, _increment_<>>;
	//	constexpr auto sq = machine::_argpose_<_multiply_, 0, 0>;

	//	printf("%d\n", apply<f>(3, 4, 5));
	//	printf("%d\n", apply<sq>(3));
	//	printf("%d\n", apply<machine::_arg_at_<0>>(3, 4, 5));

		constexpr auto env = U_pack_Vs<default_machine_frame>;
		constexpr auto g   = machine::_subpose_env_<add_str, env, _decrement_<>, _id_, _increment_<>>;

		printf("%d\n", apply<g>(3, 4, 5));

		return 0;
	}

