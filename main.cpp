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
//#include"07_cctmp_chord.hpp"
#include"08_cctmp_parser.hpp"
#include"09_cctmp_translator.hpp"
#include"10_cctmp_targeter.hpp"
#include"11_cctmp_metapiler.hpp"

#include"undef_macros.hpp"

#include"documentation/01_case_studies.hpp"
#include"documentation/03_chord_machines.hpp"

//#include"testing/metapiler_printer.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{

	// factorial:

		static_assert(factorial_v0(0) ==     1);
		static_assert(factorial_v1(3) ==     6);
		static_assert(factorial_v2(5) ==   120);
		static_assert(factorial_v3(7) ==  5040);
		static_assert(factorial_v4(8) == 40320);

	// fibonacci:

		static_assert(fibonacci_v0(7) ==   21);
		static_assert(fibonacci_v1(8) ==   34);

	// case studies:

		constexpr auto comp_sq      = square_v0(complex_number(1, 2));
		constexpr auto comp_sum_sqs = sum_of_squares_v0(complex_number(1, 2), complex_number(0, 1));
		constexpr auto int_sum_sqs  = sum_of_squares_v0(3, 4);
		constexpr auto polynom_val  = x_to5_plus1_v0(2);
		constexpr auto semidyntyp0  = semidynamic_typing_v0(complex_number(0, 1), 17);
		constexpr auto semidyntyp1  = semidynamic_typing_v0(complex_number(1, 0), 17);
		constexpr auto reassign_val = reassign_v0(2, 17);

		static_assert(comp_sq      == complex_number(-3.0, 4.0));
		static_assert(comp_sum_sqs == complex_number(-4.0, 4.0));
		static_assert(int_sum_sqs  == 25);
		static_assert(polynom_val  == 33);
		static_assert(semidyntyp0  == 18);
		static_assert(semidyntyp1  == 5);
		static_assert(reassign_val == 17);

	// falling factorial:

		constexpr auto fall_val0 = fall_fact_2_v0<true>(7);
		constexpr auto fall_val1 = fall_fact_2_v1<true>(7);

		static_assert(fall_val0 == 42);
		static_assert(fall_val1 == 42);

	// void effects:

		int vf_n = 5, *vf_ptr = &vf_n;

		void_effects_v0(vf_ptr);

		printf("%d\n", *vf_ptr); // prints: 3

	// side effects:

		int sf_n = 5, *sf_ptr = &sf_n;

		side_effects_v0(sf_ptr);

		printf("%d\n", *sf_ptr); // prints: 3

	// map:

		constexpr auto _sq_ = arg_compose<_multiply_, _arg_at_<0>, _arg_at_<0>>;
		constexpr auto map  = cctmp_chord::_map_<env<cctmp_chord::map_frame<_sq_>>>;

		int x[10];

		apply<map>(x, 0, 10);

		for (int k = 0; k < 10; ++k) printf("%d, ", x[k]);
		printf("\n");			// prints: 0, 1, 4, 9, 16, 25, 36, 49, 64, 81,

		return 0;
	}

