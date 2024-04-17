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
#define NIK_HUSTLE_PARSER_OBJ           "../object/02_hustle_parser.hpp"

//#define NIK_PARSER_GENERATOR_PARSER // bug: currently all need to be on or all off.
//#define NIK_HUSTLE_PARSER

/***********************************************************************************************************************/

#include"../../define_macros.hpp"

#include"../../include/00_cctmp.h"
#include"../../include/01_assembly.h"
#include"../../include/02_generator.h"
#include"../../include/03_fileput.h"
#include"../../include/05_hustle.h"

#include"../../undef_macros.hpp"

#include"inventory.hpp"

/***********************************************************************************************************************/

	template<auto callable_source, auto initial_env>
	constexpr auto metapile = hustle::metapile<callable_source, initial_env>;

	constexpr auto null_env = cctmp::null_env;

/***********************************************************************************************************************/

//	constexpr auto contr_hustle_square_v0         = metapile< _hustle_square_v0         , null_env >;
//	constexpr auto contr_hustle_sum_of_squares_v0 = metapile< _hustle_sum_of_squares_v0 , null_env >;
//	constexpr auto contr_hustle_sum_of_squares_v1 = metapile< _hustle_sum_of_squares_v1 , null_env >;
//	constexpr auto contr_hustle_factorial_v0      = metapile< _hustle_factorial_v0      , null_env >;
//	constexpr auto contr_hustle_factorial_v1      = metapile< _hustle_factorial_v1      , null_env >;
//	constexpr auto contr_hustle_factorial_v2      = metapile< _hustle_factorial_v2      , null_env >;
//	constexpr auto contr_hustle_fibonacci_v0      = metapile< _hustle_fibonacci_v0      , null_env >;
//	constexpr auto contr_hustle_square_root_v0    = metapile< _hustle_square_root_v0    , null_env >;
//	constexpr auto contr_hustle_square_root_v1    = metapile< _hustle_square_root_v1    , null_env >;

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		constexpr char dsl[] = "hustle";

	//	fileput::write_assembly_controller< contr_hustle_square_v0         >(dsl, "square_v0"         );
	//	fileput::write_assembly_controller< contr_hustle_sum_of_squares_v0 >(dsl, "sum_of_squares_v0" );
	//	fileput::write_assembly_controller< contr_hustle_sum_of_squares_v1 >(dsl, "sum_of_squares_v1" );
	//	fileput::write_assembly_controller< contr_hustle_factorial_v0      >(dsl, "factorial_v0"      );
	//	fileput::write_assembly_controller< contr_hustle_factorial_v1      >(dsl, "factorial_v1"      );
	//	fileput::write_assembly_controller< contr_hustle_factorial_v2      >(dsl, "factorial_v2"      );
	//	fileput::write_assembly_controller< contr_hustle_fibonacci_v0      >(dsl, "fibonacci_v0"      );
	//	fileput::write_assembly_controller< contr_hustle_square_root_v0    >(dsl, "square_root_v0"    );
	//	fileput::write_assembly_controller< contr_hustle_square_root_v1    >(dsl, "square_root_v1"    );

		return 0;
	}

