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

#define NIK_PARSER_GENERATOR_PARSER_OBJ       "../object/00_parser_generator_parser.hpp"
#define NIK_CHORD_ASSEMBLY_SCANNER_PARSER_OBJ "../object/01_chord_assembly_scanner.hpp"
#define NIK_CHORD_ASSEMBLY_PARSER_OBJ         "../object/02_chord_assembly_parser.hpp"
#define NIK_HUSTLE_PARSER_OBJ                 "../object/03_hustle_parser.hpp"

//#define NIK_PARSER_GENERATOR_PARSER // bug: currently all need to be on or all off.
//#define NIK_CHORD_ASSEMBLY_SCANNER_PARSER
//#define NIK_CHORD_ASSEMBLY_PARSER
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
#include"00_cctmp/07_interpreter.hpp"
#include"00_cctmp/08_graph.hpp"

#include"01_machine/00_control.hpp"
#include"01_machine/01_literal_state.hpp"
#include"01_machine/02_literal_action.hpp"
#include"01_machine/03_assembly_state.hpp"
#include"01_machine/04_assembly_action.hpp"

#include"02_generator/00_ll_lexer.hpp"
#include"02_generator/01_ll_syntax.hpp"
#include"02_generator/02_ll_parser.hpp"
#include"02_generator/03_ll_table.hpp"

//#include"03_chord/00_lexer.hpp"
//#include"03_chord/01_assembly_action.hpp"
//#include"03_chord/02_morph_action.hpp"
//#include"03_chord/03_cycle_action.hpp"
//#include"03_chord/04_syntax.hpp"
//#include"03_chord/05_parser.hpp"
//#include"03_chord/06_metapiler.hpp"

#include"04_hustle/00_lexer.hpp"
#include"04_hustle/01_action.hpp"
#include"04_hustle/02_syntax.hpp"
#include"04_hustle/03_parser.hpp"
#include"04_hustle/04_metapiler.hpp"

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

	struct T_atoi
	{
		template<typename CharPtr>
		constexpr static auto result(CharPtr c) { return atoi(c); }

	}; constexpr auto _atoi_ = U_store_T<T_atoi>;

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

		//	"(define (factorial (type 0) n) "
		//	"  (if (= n 0)                  "
		//	"    1                          "
		//	"    (* n (factorial (- n 1)))  "
		//	"  )                            "
		//	")                              "

		//	"(define (fib (type 0) n)            "
		//	"  (if (< n 2)                       "
		//	"    1                               "
		//	"    (+ (fib (- n 1)) (fib (- n 2))) "
		//	"  )                                 "
		//	")                                   "

		//	"(define (main n)                 "
		//	"  (define (sq (type 0) m) * m m) "
		//	"  (sq n)                         "
		//	")                                "

/***********************************************************************************************************************/

// hustle:

	constexpr auto _hustle_test_func()
	{
		return source
	        (
			"(define (factorial (type 0) n) "
			"  (if (= n 0)                  "
			"    1                          "
			"    (* n (factorial (- n 1)))  "
			"  )                            "
			")                              "
		);
	}

	template<typename... OutTs>
	struct hustle_test_op
	{
		constexpr static auto OutUs = U_pack_Ts<OutTs...>;

		template<typename... Ts>
		constexpr static auto result(Ts... vs)
			{ return hustle::hustle_apply<_hustle_test_func, null_env, OutUs>(vs...); }
	};

/***********************************************************************************************************************/

//	using chord_grammar			= chord::T_chord_assembly_scanner_grammar;
//	using chord_grammar			= chord::T_chord_assembly_grammar;
//	constexpr auto static_grammar		= U_store_T<chord_grammar>;
//	constexpr auto static_contr		= hustle::metapile<_hustle_test_func, null_env>;

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	printf("%d\n", hustle_test_op<gindex_type>::result(gindex_type{5}));//main_at(0, argc, argv)));

	//	auto & contr = member_value_U<static_contr>;

	//	for (auto k = 0; k != contr.size(); ++k)
	//	{
	//		auto s = (k < 10) ? "  " : (k < 100) ? " " : "";
	//		printf("line %s%d -", s, k);

	//		for (auto j = 0; j != Instr::dimension; ++j)
	//		{
	//			auto v = contr[k][j];
	//			auto t = (v < 10) ? "  " : (v < 100) ? " " : "";

	//			printf(" %s%d", t, v);
	//		}

	//		printf("\n");
	//	}

	//	auto tr_table_printer = generator::parser_generator_tt_printer<static_grammar>{};
	//	tr_table_printer.print_num_tr_table();

		return 0;
	}

