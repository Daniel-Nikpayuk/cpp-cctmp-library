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

#define NIK_PARSER_GENERATOR_PARSER_OBJ       "../object/00_parser_generator_parser.hpp"
#define NIK_CHORD_ASSEMBLY_SCANNER_PARSER_OBJ "../object/01_chord_assembly_scanner.hpp"
#define NIK_CHORD_ASSEMBLY_PARSER_OBJ         "../object/02_chord_assembly_parser.hpp"
#define NIK_SCHEME_PARSER_OBJ                 "../object/03_scheme_parser.hpp"

//#define NIK_PARSER_GENERATOR_PARSER // bug: currently all need to be on or all off.
//#define NIK_CHORD_ASSEMBLY_SCANNER_PARSER
//#define NIK_CHORD_ASSEMBLY_PARSER
//#define NIK_SCHEME_PARSER

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
#include"01_machine/03_chain_state.hpp"
#include"01_machine/04_chain_action.hpp"
#include"01_machine/05_assembly_state.hpp"
#include"01_machine/06_assembly_action.hpp"

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

#include"04_scheme/00_lexer.hpp"
#include"04_scheme/01_action.hpp"
#include"04_scheme/02_syntax.hpp"
#include"04_scheme/03_parser.hpp"
#include"04_scheme/04_metapiler.hpp"

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

// scheme:

	constexpr auto _scheme_test_func()
	{
		return source
	        (
			"(define (main x y z)          "
			" (if x (if y 4 5) (if z 6 7)) "
			")                             "
		);
	}

	template<typename T, typename... Ts>
	constexpr auto scheme_test_func(Ts... vs)
		{ return scheme::scheme_apply<_scheme_test_func, null_env, T>(vs...); }

/***********************************************************************************************************************/

//	using chord_grammar			= chord::T_chord_assembly_scanner_grammar;
//	using chord_grammar			= chord::T_chord_assembly_grammar;
//	constexpr auto static_grammar		= U_store_T<chord_grammar>;

	int main(int argc, char *argv[])
	{
		printf("%d\n", scheme_test_func<int>( true  , true  , true  ));
		printf("%d\n", scheme_test_func<int>( true  , true  , false ));
		printf("%d\n", scheme_test_func<int>( true  , false , true  ));
		printf("%d\n", scheme_test_func<int>( true  , false , false ));
		printf("%d\n", scheme_test_func<int>( false , true  , true  ));
		printf("%d\n", scheme_test_func<int>( false , true  , false ));
		printf("%d\n", scheme_test_func<int>( false , false , true  ));
		printf("%d\n", scheme_test_func<int>( false , false , false ));

	//	auto tr_table_printer = generator::parser_generator_tt_printer<static_grammar>{};
	//	tr_table_printer.print_num_tr_table();

	//	using stack_type = pair_stack<gindex_type, 3>;

	//	stack_type stack;

	//	stack.push(15, 5);
	//	stack.push(17, 1);
	//	stack.push(11, 12);

	//	auto p2 = stack.pop();
	//	auto p1 = stack.pop();
	//	auto p0 = stack.pop();

	//	printf("(%d, %d)\n", p0.v0, p0.v1);
	//	printf("(%d, %d)\n", p1.v0, p1.v1);
	//	printf("(%d, %d)\n", p2.v0, p2.v1);

		return 0;
	}

