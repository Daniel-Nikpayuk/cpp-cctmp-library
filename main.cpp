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
//#define NIK_HUSTLE_PARSER

/***********************************************************************************************************************/

#include"define_macros.hpp"

#include"00_cctmp/00_grammar.hpp"
#include"00_cctmp/01_argument.hpp"
#include"00_cctmp/02_parameter.hpp"
#include"00_cctmp/03_scope.hpp"
#include"00_cctmp/04_relation.hpp"
#include"00_cctmp/05_praxis.hpp"
#include"00_cctmp/06_algorithm.hpp"
#include"00_cctmp/07_machine.hpp"
#include"00_cctmp/08_graph.hpp"

#include"01_assembly/00_space.hpp"
#include"01_assembly/01_constant.hpp"
#include"01_assembly/02_application.hpp"
#include"01_assembly/03_conditional.hpp"
#include"01_assembly/04_action.hpp"
#include"01_assembly/05_syntax.hpp"

#include"02_generator/00_ll_lexer.hpp"
#include"02_generator/01_ll_syntax.hpp"
#include"02_generator/02_ll_parser.hpp"
#include"02_generator/03_ll_table.hpp"

#include"03_chord/00_lexer.hpp"
#include"03_chord/01_parser.hpp"
#include"03_chord/02_syntax.hpp"
#include"03_chord/03_kernel_action.hpp"
#include"03_chord/04_cycle_action.hpp"
#include"03_chord/05_metapiler.hpp"

#include"04_hustle/00_lexer.hpp"
#include"04_hustle/01_parser.hpp"
#include"04_hustle/02_action.hpp"
#include"04_hustle/03_metapiler.hpp"

//#include"05_math/00_byte_ring.hpp"
//#include"05_math/01_byte_array_ring.hpp"
//#include"05_math/02_cryptography.hpp"
//#include"05_math/03_linear_algebra.hpp"
//#include"05_math/04_signal_processing.hpp"

#include"undef_macros.hpp"

//#include"documentation/02_controllers.hpp"
//#include"documentation/03_generic_assembly.hpp"
//#include"documentation/04_chord_progressions.hpp"

//#include"testing/00_generic_printers.hpp"
//#include"testing/01_parser_generator_printers.hpp"
//#include"testing/02_chord_assembly_printers.hpp"
//#include"testing/04_chord_grammar_tests.hpp"
//#include"testing/05_progression_grammar_tests.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

	using chord_grammar			= chord::T_chord_grammar;
	constexpr auto static_grammar		= U_store_T<chord_grammar>;

	template<auto static_contr>
	void print_controller(int b = 0, int e = member_value_U<static_contr>.size())
	{
		constexpr auto & contr = member_value_U<static_contr>;

		for (auto k = b; k != e; ++k)
		{
			auto s = (k < 10) ? "  " : (k < 100) ? " " : "";
			printf("line %s%d -", s, k);

			for (auto j = 0; j != Instr::dimension; ++j)
			{
				auto v = contr[k][j];
				auto t = (v < 10) ? "  " : (v < 100) ? " " : "";

				printf(" %s%d", t, v);
			}

			printf("\n");
		}
	}

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
			"(type T                                                                    "
			"  (define (sqrt x)                                                         "

			"    (define (square y) (* y y))                                            "
			"    (define (abs y) (if (< y 0) (- y) y))                                  "
			"    (define (good-enough? guess) (< (abs (- (square guess) x)) tolerance)) "

			"    (define (average y z) (/ (+ y z) 2))                                   "
			"    (define (improve guess) (average guess (/ x guess)) )                  "

			"    (define (sqrt-iter guess) -> T                                         "
			"      (if (good-enough? guess) guess (sqrt-iter (improve guess)))          "
			"    )                                                                      "

			"    (sqrt-iter 1:T)                                                        "
			"  )                                                                        "
			")                                                                          "

			, binding( "tolerance" , 0.0001 )
		);
	}

/***********************************************************************************************************************/

		//	"main out in end in1                               ;"

		//	"vars:                                             ;"
		//	"  declare conv                                    ;"

		//	"defs:                                             ;"
		//	"  conv # fold[2]{add * @|multiply||} <> (-|+,] [] ;"

		//	"body:                                             ;"
		//	"  . = conv !out end in in1                        ;"
		//	"  return _                                        ;"

// chord:

	constexpr auto _chord_test_func()
	{
		return source
		(
			"main out in end in1                                ;"

			"vars:                                              ;"
			"  declare dot_prod                                 ;"

			"defs:                                              ;"
			"  dot_prod # fold[2]{add * @|multiply||} <> [,) [) ;"

			"body:                                              ;"
			"  . = dot_prod !out in end in1                     ;"
			"  return _                                         ;"
		);
	}

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		// 17032, 16994

		using chord_size_type = int*;
		using T_chord_apply   = chord::T_apply<_chord_test_func, null_env, chord_size_type>;
		using chord_arr_type  = sequence<int, 5>;

		int val = 0;

		chord_arr_type s0({ 1, 1, 1, 1, 1 });
		chord_arr_type s1({ 0, 1, 2, 3, 4 });

		T_chord_apply::template result<chord_size_type>(&val, s0.cbegin(), s0.cend(), s1.cbegin());
		printf("%d\n", val);

		// 17136, 17056
		// 17136, 16952
		// 17680, 16952

	//	using hustle_size_type = double;
	//	using T_hustle_apply   = hustle::T_apply<_hustle_test_func, null_env, hustle_size_type>;

	//	auto val = T_hustle_apply::result(hustle_size_type(main_at(0, argc, argv)));
	//	printf("%1.11f\n", val);

		//

	//	print_controller<chord::metapile<_chord_test_func, null_env>>();//103);
	//	print_controller<hustle::metapile<_hustle_test_func, null_env>>();

	//	auto tr_table_printer = generator::parser_generator_tt_printer<static_grammar>{};
	//	tr_table_printer.print_num_tr_table();

		return 0;
	}

