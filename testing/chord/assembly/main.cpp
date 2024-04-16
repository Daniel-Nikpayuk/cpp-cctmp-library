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

#include<cstdio>
#include<cstdlib>

#define NIK_PARSER_GENERATOR_PARSER_OBJ "../object/00_parser_generator_parser.hpp"
#define NIK_CHORD_PARSER_OBJ            "../object/01_chord_parser.hpp"

#define NIK_PARSER_GENERATOR_PARSER // bug: currently all need to be on or all off.
#define NIK_CHORD_PARSER

/***********************************************************************************************************************/

#include"../../../define_macros.hpp"

#include"../../../include/00_cctmp.h"
#include"../../../include/01_assembly.h"
#include"../../../include/02_generator.h"
#include"../../../include/03_fileput.h"
#include"../../../include/04_chord.h"

#include"../../../undef_macros.hpp"

#include"inventory.hpp"

/***********************************************************************************************************************/

	template<auto callable_source, auto initial_env>
	constexpr auto metapile = chord::metapile<callable_source, initial_env>;

	constexpr auto null_env    = cctmp::null_env;
	constexpr auto complex_env = cctmp::env<complex_constant_frame>;

/***********************************************************************************************************************/

//	constexpr auto contr_chord_square_v0             = metapile< _chord_square_v0             , null_env    >;
//	constexpr auto contr_chord_square_v1             = metapile< _chord_square_v1             , null_env    >;
//	constexpr auto contr_chord_sum_of_squares_v0     = metapile< _chord_sum_of_squares_v0     , null_env    >;
//	constexpr auto contr_chord_sum_of_squares_v1     = metapile< _chord_sum_of_squares_v1     , null_env    >;
//	constexpr auto contr_chord_twice_v0              = metapile< _chord_twice_v0              , null_env    >;
//	constexpr auto contr_chord_plus_n_v0             = metapile< _chord_plus_n_v0             , null_env    >;
//	constexpr auto contr_chord_two_x_sqd_v0          = metapile< _chord_two_x_sqd_v0          , null_env    >;
//	constexpr auto contr_chord_x_sqd_plus_y4_v0      = metapile< _chord_x_sqd_plus_y4_v0      , null_env    >;
//	constexpr auto contr_chord_x_to5_plus1_v0        = metapile< _chord_x_to5_plus1_v0        , null_env    >;
//	constexpr auto contr_chord_reassign_v0           = metapile< _chord_reassign_v0           , null_env    >;
//	constexpr auto contr_chord_if_then_else_v0       = metapile< _chord_if_then_else_v0       , null_env    >;
//	constexpr auto contr_chord_semidynamic_typing_v0 = metapile< _chord_semidynamic_typing_v0 , null_env    >;
//	constexpr auto contr_chord_semidynamic_typing_v1 = metapile< _chord_semidynamic_typing_v1 , complex_env >;
//	constexpr auto contr_chord_binary_dispatch_v0    = metapile< _chord_binary_dispatch_v0    , null_env    >;
//	constexpr auto contr_chord_binary_dispatch_v1    = metapile< _chord_binary_dispatch_v1    , null_env    >;
//	constexpr auto contr_chord_factorial_v0          = metapile< _chord_factorial_v0          , null_env    >;
//	constexpr auto contr_chord_factorial_v1          = metapile< _chord_factorial_v1          , null_env    >;
//	constexpr auto contr_chord_factorial_v2          = metapile< _chord_factorial_v2          , null_env    >;
//	constexpr auto contr_chord_factorial_v3          = metapile< _chord_factorial_v3          , null_env    >;
//	constexpr auto contr_chord_factorial_v4          = metapile< _chord_factorial_v4          , null_env    >;
//	constexpr auto contr_chord_factorial_v5          = metapile< _chord_factorial_v5          , null_env    >;
//	constexpr auto contr_chord_fibonacci_v0          = metapile< _chord_fibonacci_v0          , null_env    >;
//	constexpr auto contr_chord_fibonacci_v1          = metapile< _chord_fibonacci_v1          , null_env    >;
//	constexpr auto contr_chord_fall_fact_2_v0        = metapile< _chord_fall_fact_2_v0<true>  , null_env    >;
//	constexpr auto contr_chord_fall_fact_2_v1        = metapile< _chord_fall_fact_2_v1<true>  , null_env    >;
//	constexpr auto contr_chord_void_effects_v0       = metapile< _chord_void_effects_v0       , null_env    >;
//	constexpr auto contr_chord_side_effects_v0       = metapile< _chord_side_effects_v0       , null_env    >;

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		constexpr char dsl[] = "chord";

	//	fileput::write_assembly_controller< contr_chord_square_v0             >(dsl, "square_v0"             );
	//	fileput::write_assembly_controller< contr_chord_square_v1             >(dsl, "square_v1"             );
	//	fileput::write_assembly_controller< contr_chord_sum_of_squares_v0     >(dsl, "sum_of_squares_v0"     );
	//	fileput::write_assembly_controller< contr_chord_sum_of_squares_v1     >(dsl, "sum_of_squares_v1"     );
	//	fileput::write_assembly_controller< contr_chord_twice_v0              >(dsl, "twice_v0"              );
	//	fileput::write_assembly_controller< contr_chord_plus_n_v0             >(dsl, "plus_n_v0"             );
	//	fileput::write_assembly_controller< contr_chord_two_x_sqd_v0          >(dsl, "two_x_sqd_v0"          );
	//	fileput::write_assembly_controller< contr_chord_x_sqd_plus_y4_v0      >(dsl, "x_sqd_plus_y4_v0"      );
	//	fileput::write_assembly_controller< contr_chord_x_to5_plus1_v0        >(dsl, "x_to5_plus1_v0"        );
	//	fileput::write_assembly_controller< contr_chord_reassign_v0           >(dsl, "reassign_v0"           );
	//	fileput::write_assembly_controller< contr_chord_if_then_else_v0       >(dsl, "if_then_else_v0"       );
	//	fileput::write_assembly_controller< contr_chord_semidynamic_typing_v0 >(dsl, "semidynamic_typing_v0" );
	//	fileput::write_assembly_controller< contr_chord_semidynamic_typing_v1 >(dsl, "semidynamic_typing_v1" );
	//	fileput::write_assembly_controller< contr_chord_binary_dispatch_v0    >(dsl, "binary_dispatch_v0"    );
	//	fileput::write_assembly_controller< contr_chord_binary_dispatch_v1    >(dsl, "binary_dispatch_v1"    );
	//	fileput::write_assembly_controller< contr_chord_factorial_v0          >(dsl, "factorial_v0"          );
	//	fileput::write_assembly_controller< contr_chord_factorial_v1          >(dsl, "factorial_v1"          );
	//	fileput::write_assembly_controller< contr_chord_factorial_v2          >(dsl, "factorial_v2"          );
	//	fileput::write_assembly_controller< contr_chord_factorial_v3          >(dsl, "factorial_v3"          );
	//	fileput::write_assembly_controller< contr_chord_factorial_v4          >(dsl, "factorial_v4"          );
	//	fileput::write_assembly_controller< contr_chord_factorial_v5          >(dsl, "factorial_v5"          );
	//	fileput::write_assembly_controller< contr_chord_fibonacci_v0          >(dsl, "fibonacci_v0"          );
	//	fileput::write_assembly_controller< contr_chord_fibonacci_v1          >(dsl, "fibonacci_v1"          );
	//	fileput::write_assembly_controller< contr_chord_fall_fact_2_v0        >(dsl, "fall_fact_2_v0"        );
	//	fileput::write_assembly_controller< contr_chord_fall_fact_2_v1        >(dsl, "fall_fact_2_v1"        );
	//	fileput::write_assembly_controller< contr_chord_void_effects_v0       >(dsl, "void_effects_v0"       );
	//	fileput::write_assembly_controller< contr_chord_side_effects_v0       >(dsl, "side_effects_v0"       );

		return 0;
	}

