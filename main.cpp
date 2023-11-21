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
#include<cstdlib>

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

#include"01_machine/00_control.hpp"
#include"01_machine/01_lookup_state.hpp"
#include"01_machine/02_lookup_action.hpp"
#include"01_machine/03_chain_state.hpp"
#include"01_machine/04_chain_action.hpp"
#include"01_machine/05_cycle_state.hpp"
#include"01_machine/06_cycle_action.hpp"
#include"01_machine/07_assembly_state.hpp"
#include"01_machine/08_assembly_action.hpp"

#include"02_generator/00_ll_lexer.hpp"
#include"02_generator/01_ll_syntax.hpp"
#include"02_generator/02_ll_parser.hpp"
#include"02_generator/03_ll_table.hpp"

#include"03_chord/00_lexer.hpp"
#include"03_chord/01_assembly_action.hpp"
#include"03_chord/02_morph_action.hpp"
#include"03_chord/03_cycle_action.hpp"
#include"03_chord/04_scanner.hpp"
#include"03_chord/05_syntax.hpp"
#include"03_chord/06_parser.hpp"
#include"03_chord/07_metapiler.hpp"

//#include"04_math/00_byte_ring.hpp"
//#include"04_math/01_byte_array_ring.hpp"
//#include"04_math/02_cryptography.hpp"
//#include"04_math/03_linear_algebra.hpp"
//#include"04_math/04_signal_processing.hpp"

#include"undef_macros.hpp"

//#include"documentation/01_lookup_controllers.hpp"
//#include"documentation/02_chain_controllers.hpp"
//#include"documentation/03_cycle_controllers.hpp"
//#include"documentation/04_assembly_controllers.hpp"
//#include"documentation/05_generic_assembly.hpp"
//#include"documentation/06_chord_progressions.hpp"

//#include"testing/00_generic_printers.hpp"
//#include"testing/01_parser_generator_printers.hpp"
//#include"testing/02_chord_assembly_printers.hpp"
//#include"testing/04_chord_grammar_tests.hpp"
//#include"testing/05_progression_grammar_tests.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

	int main_at(int n, int argc, char *argv[], int def = 0)
	{
		auto pos = n + 1;

		if (pos < argc) return atoi(argv[pos]);
		else            return def;
	}

	int main_sum(int argc, char *argv[])
	{
		auto sum = 0;

		for (int k = 0; k != argc; ++k)
			sum += atoi(argv[k]);

		return sum;
	}

/***********************************************************************************************************************/

// square:

	// version 0:

		constexpr auto _square_v0()
		{
			return chord::source
			(
				"square x         ;"

				"body:            ;"
				". = multiply x x ;"
				"return _         ;"
			);
		}

		template<typename T>
		constexpr auto square_v0(T v)
			{ return chord::chord_apply<_square_v0, null_env, T>(v); }

	// version 1:

		constexpr auto _square_v1()
		{
			return chord::source
			(
				"square x                      ;"

				"definitions:                  ;"
				"sq # argpose[1]{multiply 0 0} ;"

				"body:                         ;"
				". = sq x                      ;"
				"return _                      ;"
			);
		}

		template<typename T>
		constexpr auto square_v1(T v)
			{ return chord::chord_apply<_square_v1, null_env, T>(v); }

/***********************************************************************************************************************/

// sum of squares:

	// version 0:

		constexpr auto _sum_of_squares_v0()
		{
			return chord::source
		        (
				"sum_of_squares x y ;"

				"body:              ;"
				"x = multiply x x   ;"
				"y = multiply y y   ;"
				". = add      x y   ;"
				"return _           ;"
			);
		}

		template<typename T>
		constexpr auto sum_of_squares_v0(T x, T y)
			{ return chord::chord_apply<_sum_of_squares_v0, null_env, T>(x, y); }

	// version 1:

/*
		constexpr auto _sum_of_squares_v1()
		{
			return chord::source
		        (
				"f x y                                ;"

				"definitions:                         ;"
				"sq        # argpose[1]{multiply 0 0} ;"
				"sum_of_sq # subpose[2]{add sq sq}    ;"

				"body:                                ;"
				". = sum_of_sq x y                    ;"
				"return _                             ;"
			);
		}

		template<typename T>
		constexpr auto sum_of_squares_v1(T x, T y)
			{ return chord::chord_apply<_sum_of_squares_v1, null_env, T>(x, y); }
*/

/***********************************************************************************************************************/

// two_x_sqd:

	// version 0:

		constexpr auto _two_x_sqd_v0()
		{
			return chord::source
		        (
				"f x                                   ;"

				"definitions:                          ;"
				"sq        # argpose[1]{multiply 0 0}  ;"
				"sum_of_sq # subpose[2]{add sq sq}     ;"
				"two_x_sqd # argpose[1]{sum_of_sq 0 0} ;"

				"body:                                 ;"
				". = two_x_sqd x                       ;"
				"return _                              ;"
			);
		}

		template<typename T>
		constexpr auto two_x_sqd_v0(T x)
			{ return chord::chord_apply<_two_x_sqd_v0, null_env, T>(x); }

/***********************************************************************************************************************/

		constexpr auto _sum_of_squares_v1()
		{
			return chord::source
		        (
				"f x y                                ;"

				"definitions:                         ;"
				"sq        # argpose[1]{multiply 0 0} ;"
				"sum_of_sq # subpose[2]{add sq sq}    ;"

				"body:                                ;"
				". = sum_of_sq x y                    ;"
				"return _                             ;"
			);
		}

		template<typename T>
		constexpr auto sum_of_squares_v1(T x, T y)
			{ return chord::chord_apply<_sum_of_squares_v1, null_env, T>(x, y); }

/***********************************************************************************************************************/

//	using chord_grammar			= chord::T_chord_assembly_scanner_grammar;
//	using chord_grammar			= chord::T_chord_assembly_grammar;
//	constexpr auto static_grammar		= U_store_T<chord_grammar>;

	int main(int argc, char *argv[])
	{
	//	printf("%d\n", main_sum(argc, argv));

	//	auto tr_table_printer = generator::parser_generator_tt_printer<static_grammar>{};
	//	tr_table_printer.print_num_tr_table();

	//	printf("%d\n", square_v0(5));
	//	printf("%d\n", square_v1(5));
	//	printf("%d\n", sum_of_squares_v0(3, 4));
	//	printf("%d\n", sum_of_squares_v1(3, 4));

	//	printf("%d\n", square_v0(main_at(0, argc, argv)));
	//	printf("%d\n", sum_of_squares_v0(main_at(0, argc, argv), main_at(1, argc, argv)));

		return 0;
	}

