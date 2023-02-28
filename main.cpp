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

/***********************************************************************************************************************/

#include"define_macros.hpp"

#include"00_cctmp_grammar.hpp"
#include"01_cctmp_argument.hpp"
#include"02_cctmp_parameter.hpp"
#include"03_cctmp_praxis.hpp"
#include"04_cctmp_interpreter.hpp"
#include"05_cctmp_machine.hpp"
#include"06_cctmp_lexer.hpp"
#include"07_cctmp_parser.hpp"
#include"08_cctmp_assembler.hpp"
#include"09_cctmp_targeter.hpp"
#include"10_cctmp_metapiler.hpp"

#include"documentation/00_case_studies.hpp"
#include"documentation/01_chord_machines.hpp"
//#include"testing/metapiler_printer.hpp"

#include"undef_macros.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	// todo: possible bug steming from copy/paste/has_side interoperability.

	using namespace cctmp;

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		static_assert(factorial_v0(0) ==     1);
		static_assert(factorial_v1(3) ==     6);
		static_assert(factorial_v2(5) ==   120);
		static_assert(factorial_v3(7) ==  5040);
		static_assert(factorial_v4(8) == 40320);

		static_assert(fibonacci_v0(7) ==   21);
		static_assert(fibonacci_v1(8) ==   34);

		print_complex(square_v0(complex_number(1, 2))); // prints: (-3.000000, 4.000000)
		print_complex(sum_of_squares_v0(complex_number(1, 2), complex_number(0, 1))); // prints: (-4.000000, 4.000000)
		printf("%d\n", sum_of_squares_v0(3, 4)); // prints: 25
		printf("%d\n", x_to5_plus1_v0(2)); // prints: 33

		constexpr auto map = cctmp_chord::_map_<cctmp_chord::map_lookup<>>;

		int x[10];

		apply<map>(x, 0, 10);

		for (int k = 0; k < 10; ++k) printf("%d, ", x[k]); // prints: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		printf("\n");

		return 0;
	}

