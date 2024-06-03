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
#define NIK_HUSTLE_PARSER_OBJ           "../object/02_hustle_parser.hpp"

#define NIK_PARSER_GENERATOR_PARSER // bug: currently all need to be on or all off.
#define NIK_CHORD_PARSER
#define NIK_HUSTLE_PARSER

/***********************************************************************************************************************/

#include"define_macros.hpp"

#include"include/00_cctmp.h"
#include"include/01_assembly.h"
#include"include/02_generator.h"
#include"include/03_fileput.h"
#include"include/04_chord.h"
#include"include/05_hustle.h"

#include"undef_macros.hpp"

//#include"testing/chord/assembly/unit_test.hpp"
//#include"testing/chord/progression/unit_test.hpp"
//#include"testing/hustle/unit_test.hpp"

//#include"experimental/00_generic_printers.hpp"
//#include"experimental/01_parser_generator_printers.hpp"
//#include"experimental/02_chord_assembly_printers.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

	using chord_grammar			= chord::T_chord_grammar;
	using hustle_grammar			= hustle::T_hustle_grammar;
	constexpr auto static_grammar		= U_store_T<hustle_grammar>;

/***********************************************************************************************************************/

	struct T_atoi
	{
		template<typename CharPtr>
		constexpr static auto result(CharPtr c) { return atoi(c); }

	}; constexpr auto _atoi_ = U_store_T<T_atoi>;

/***********************************************************************************************************************/

	unsigned long main_at(unsigned long n, int argc, char *argv[], unsigned long def = 0)
	{
		auto pos = n + 1;

		if (pos < argc) return atoi(argv[pos]);
		else            return def;
	}

	unsigned long main_sum(int argc, char *argv[])
	{
		auto sum = 0;

		for (int k = 0; k != argc; ++k)
			sum += atoi(argv[k]);

		return sum;
	}

/***********************************************************************************************************************/

// hustle:

	constexpr auto _hustle_test_func()
	{
		return source
	        (
			"(define (main n)         "
			"  ((if (= n 0) + *) 2 3) "
			")                        "
		);
	}

/***********************************************************************************************************************/

// chord:

	constexpr auto _chord_test_func()
	{
		return source
		(
			"main out in end in1                               ;"

			"vars:                                             ;"
			"  declare chord_f                                 ;"

			"defs:                                             ;"
		//	"  chord_f # fold[1]{add|@ @||} <> [,)             ;"
			"  chord_f # fold[2]{add * @|multiply||} <> (,] (] ;"

			"body:                                             ;"
			"  . = chord_f !out in end in1                     ;"
			"  return _                                        ;"
		);
	}

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		using chord_size_type = int const*;
		using T_chord_apply   = chord::T_apply<_chord_test_func, null_env, chord_size_type>;
		using chord_arr_type  = sequence<int , 5>;

		chord_arr_type s0({ 1, 2, 3, 4, 5 });

		//

		int val = 0;

		T_chord_apply::result(&val, s0.cbegin(), s0.cend() - 1, s0.cbegin());
		printf("%d\n", val);
	//	fileput::print_assembly_controller<chord::metapile<_chord_test_func, null_env>>();

		//

	//	using chord_find_type = sequence<int*, 1>;
	//	chord_find_type record;

	//	T_chord_apply::result(record.begin(), s0.cbegin(), s0.cend());
	//	printf("%d\n", record.size());

		//

	//	using T_chord_apply = chord::T_apply<_chord_test_func, null_env, unsigned long>;

	//	static_assert(T_chord_apply::result(9) == 362880);

		//

	//	chord_arr_type val;
	//	val.fullsize();

	//	T_chord_apply::result(val.begin(), 1563);
	//	printf("\n");

		//

	//	using hustle_size_type = int;
	//	using T_hustle_apply   = hustle::T_apply<_hustle_test_func, null_env, hustle_size_type>;
	//	fileput::print_assembly_controller<hustle::metapile<_hustle_test_func, null_env>>();

	//	auto val = T_hustle_apply::result(5);
	//	printf("%d\n", val);

		//

	//	using hustle_size_type = unsigned long;
	//	using T_hustle_apply   = hustle::T_apply<_hustle_test_func, null_env, hustle_size_type>;

	//	auto val = T_hustle_apply::result(main_at(0, argc, argv));
	//	printf("%lu\n", val);

		// gcc - 1.892s
		// gcc - 1.178s
		// gcc - 0.914s

		// clang - 2.721s
		// clang - 1.698s
		// clang - 1.461s

		//

	//	fileput::print_assembly_controller<chord::metapile<_chord_test_func, null_env>>();
	//	fileput::print_assembly_controller<hustle::metapile<_hustle_test_func, null_env>>();

	//	auto tr_table_printer = generator::parser_generator_tt_printer<static_grammar>{};
	//	tr_table_printer.print_num_tr_table();

		//

	//	unit_test_chord_square_v0             <gindex_type> (5);
	//	unit_test_chord_square_v1             <gindex_type> (5);
	//	unit_test_chord_sum_of_squares_v0     <gindex_type> (3, 4);
	//	unit_test_chord_sum_of_squares_v1     <gindex_type> (3, 4);
	//	unit_test_chord_twice_v0              <gindex_type> (5);
	//	unit_test_chord_plus_n_v0             <gindex_type> (3, 4);
	//	unit_test_chord_two_x_sqd_v0          <gindex_type> (5);
	//	unit_test_chord_x_sqd_plus_y4_v0      <gindex_type> (3, 2);
	//	unit_test_chord_x_to5_plus1_v0        <gindex_type> (2, 0);
	//	unit_test_chord_reassign_v0           <gindex_type> (3, 4);
	//	unit_test_chord_if_then_else_v0       <gindex_type> (true, 5, 6);
	//	unit_test_chord_semidynamic_typing_v0 <gindex_type> (complex_number{0, 1}, 6);
	//	unit_test_chord_semidynamic_typing_v1 <gindex_type> (complex_number{0, 1}, 6);
	//	unit_test_chord_factorial_v0          <gindex_type> (9);
	//	unit_test_chord_factorial_v1          <gindex_type> (9);
	//	unit_test_chord_factorial_v3          <gindex_type> (9);
	//	unit_test_chord_factorial_v4          <gindex_type> (9);
	//	unit_test_chord_factorial_v5          <gindex_type> (9);
	//	unit_test_chord_fall_fact_2_v0        <true, gindex_type> (5);
	//	unit_test_chord_void_effects_v0       <gindex_type> (5, 6);

		//

	//	unit_test_chord_initialize_v0             <gindex_type> (0, s0, s1);
	//	unit_test_chord_array_square_v0           <gindex_type> (0, s0, s1);
	//	unit_test_chord_vector_sum_v0             <gindex_type> (0, s0, s1);
	//	unit_test_chord_array_add_v0              <gindex_type> (0, s0, s1);
	//	unit_test_chord_sum_v0                    <gindex_type> (0, 1, 100);
	//	unit_test_chord_dot_product_v0            <gindex_type> (0, s0, s1);
	//	unit_test_chord_convolution_v0            <gindex_type> (0, s0, s1);
	//	unit_test_chord_first_less_than_five_v0   <gindex_type> (0, s0, s1);
	//	unit_test_chord_all_less_than_five_v0     <gindex_type> (0, s0, s1);
	//	unit_test_chord_change_of_base_printer_v0 <gindex_type> (main_at(0, argc, argv));
	//	unit_test_chord_array_printer_v0          <gindex_type> (0, s0, s1);

		//

	//	unit_test_hustle_square_v0<gindex_type>(5);
	//	unit_test_hustle_sum_of_squares_v0<gindex_type>(3, 4);
	//	unit_test_hustle_sum_of_squares_v1<gindex_type>(3, 4);
	//	unit_test_hustle_factorial_v0<gindex_type>(9);
	//	unit_test_hustle_factorial_v1<gindex_type>(9);
	//	unit_test_hustle_factorial_v2<gindex_type>(9);
	//	unit_test_hustle_fibonacci_v0<gindex_type>(12);
	//	unit_test_hustle_square_root_v0<gindex_type>(double(main_at(0, argc, argv)));
	//	unit_test_hustle_square_root_v1<gindex_type>(double(main_at(0, argc, argv))); // **

		return 0;
	}

