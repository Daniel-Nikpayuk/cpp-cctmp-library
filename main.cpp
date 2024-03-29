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

//#define NIK_PARSER_GENERATOR_PARSER // bug: currently all need to be on or all off.
//#define NIK_CHORD_PARSER
//#define NIK_HUSTLE_PARSER

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
//#include"testing/hustle/unit_test.hpp"

//#include"experimental/00_generic_printers.hpp"
//#include"experimental/01_parser_generator_printers.hpp"
//#include"experimental/02_chord_assembly_printers.hpp"
//#include"experimental/04_chord_grammar_tests.hpp"
//#include"experimental/05_progression_grammar_tests.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

	using chord_grammar			= chord::T_chord_grammar;
	constexpr auto static_grammar		= U_store_T<chord_grammar>;

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

// chord:

	constexpr auto _chord_test_func()
	{
		return source
		(
			"main out in end in1                               ;"

			"vars:                                             ;"
			"  declare conv                                    ;"

			"defs:                                             ;"
			"  conv # fold[2]{add * @|multiply||} <> (-|+,] [] ;"

			"body:                                             ;"
			"  . = conv !out end in in1                        ;"
			"  return _                                        ;"
		);
	}

/***********************************************************************************************************************/

// hustle:

	constexpr auto _hustle_test_func()
	{
		return source
	        (
			"(define (main)           "
			"  5                      "
			")                        "
		);
	}

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	using hustle_size_type = double;
	//	using T_hustle_apply   = hustle::T_apply<_hustle_test_func, null_env, hustle_size_type>;

	//	auto val = T_hustle_apply::result();
	//	printf("%f\n", val);

		//

	//	using chord_size_type = int*;
	//	using T_chord_apply   = chord::T_apply<_chord_test_func, null_env, chord_size_type>;
	//	using chord_arr_type  = sequence<int, 5>;

	//	int val = 0;

	//	chord_arr_type s0({ 1, 2, 3, 4, 5 });
	//	chord_arr_type s1({ 1, 2, 3, 4, 5 });

	//	T_chord_apply::template result<chord_size_type>(&val, s0.cbegin(), s0.cend(), s1.cbegin());
	//	printf("%d\n", val);

		//

	//	fileput::print_controller<chord::metapile<_chord_test_func, null_env>>();
	//	fileput::print_controller<hustle::metapile<_hustle_test_func, null_env>>();

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
	//	unit_test_chord_semidynamic_typing_v0 <gindex_type> (complex_number{1, 0}, 6); // *
	//	unit_test_chord_semidynamic_typing_v1 <gindex_type> (complex_number{1, 0}, 6); // **
	//	unit_test_chord_binary_dispatch_v0    <gindex_type> (true, 3, 4); // **
	//	unit_test_chord_binary_dispatch_v1    <gindex_type> (true, 3, 4); // **
	//	unit_test_chord_factorial_v0          <gindex_type> (9);
	//	unit_test_chord_factorial_v1          <gindex_type> (9);
	//	unit_test_chord_factorial_v2          <gindex_type> (9); // **
	//	unit_test_chord_factorial_v3          <gindex_type> (9);
	//	unit_test_chord_factorial_v4          <gindex_type> (9);
	//	unit_test_chord_factorial_v5          <gindex_type> (9);
	//	unit_test_chord_fibonacci_v0          <gindex_type> (8); // **
	//	unit_test_chord_fibonacci_v1          <gindex_type> (8); // **
	//	unit_test_chord_fall_fact_2_v0        <true, gindex_type> (5);
	//	unit_test_chord_fall_fact_2_v1        <true, gindex_type> (5); // *
	//	unit_test_chord_void_effects_v0       <gindex_type> ();
	//	unit_test_chord_side_effects_v0       <gindex_type> ();

		//

	//	unit_test_hustle_square_root_v0<gindex_type>(double(main_at(0, argc, argv)));

		return 0;
	}

