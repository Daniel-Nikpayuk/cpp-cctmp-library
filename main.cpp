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
#include"00_cctmp/07_machine.hpp"
#include"00_cctmp/08_graph.hpp"

#include"01_assembly/00_space.hpp"
#include"01_assembly/01_constant.hpp"
#include"01_assembly/02_application.hpp"
#include"01_assembly/03_conditional.hpp"
#include"01_assembly/04_action.hpp"

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
			"(define (main n)                    "

			"  (define (factorial k p) -> fact_t "
			"    (if (= k 0)                     "
			"      p                             "
			"      (factorial (- k 1) (* k p))   "
			"    )                               "
			"  )                                 "

			"  (factorial n 1)                   "
			")                                   "

			, binding("fact_t", 0)	// translation: the type is
						// at (deferred) location 0.
		);
	}

	template<typename... OutTs>
	struct hustle_test_op
	{
		constexpr static auto OutUs = U_pack_Ts<OutTs...>;

		template<typename... Ts>
		constexpr static auto result(Ts... vs)
			{ return hustle::hustle_apply<_hustle_test_func, null_env, OutUs>(vs...); }

	}; template<typename... OutTs>
		constexpr auto _hustle_test_op_ = U_store_T<hustle_test_op<OutTs...>>;

/***********************************************************************************************************************/

//	using chord_grammar			= chord::T_chord_assembly_grammar;
//	constexpr auto static_grammar		= U_store_T<chord_grammar>;

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	using size_type = unsigned long;

	//	size_type val = hustle_test_op<size_type>::result(main_at(0, argc, argv));
	//	printf("%lu\n", val);

	//	print_controller();

	//	auto tr_table_printer = generator::parser_generator_tt_printer<static_grammar>{};
	//	tr_table_printer.print_num_tr_table();

		return 0;
	}

