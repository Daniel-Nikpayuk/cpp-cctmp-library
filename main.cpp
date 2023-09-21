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
#include"00_cctmp/08_chain.hpp"
#include"00_cctmp/09_action.hpp"
#include"00_cctmp/10_compose.hpp"

#include"01_generator/00_graph.hpp"
#include"01_generator/01_lexer.hpp"
#include"01_generator/02_syntax.hpp"
#include"01_generator/03_parser.hpp"
#include"01_generator/04_parse_table.hpp"

#include"02_chord/00_lexer.hpp"
#include"02_chord/01_scanner.hpp"
#include"02_chord/02_syntax.hpp"
#include"02_chord/03_action.hpp"
#include"02_chord/04_parser.hpp"
#include"02_chord/05_morph.hpp"
//#include"02_chord/06_cycle.hpp"
//#include"02_chord/07_progression.hpp"
#include"02_chord/08_lookup.hpp"
#include"02_chord/09_machine.hpp"
#include"02_chord/10_targeter.hpp"

//#include"03_math/00_byte_ring.hpp"
//#include"03_math/01_byte_array_ring.hpp"
//#include"03_math/02_cryptography.hpp"
//#include"03_math/03_linear_algebra.hpp"
//#include"03_math/04_signal_processing.hpp"

#include"undef_macros.hpp"

#include"documentation/01_case_studies.hpp"
//#include"documentation/02_chord_progressions.hpp"

#include"testing/00_generic_printers.hpp"
#include"testing/01_parser_generator_printers.hpp"
#include"testing/02_chord_assembly_printers.hpp"
#include"testing/04_chord_grammar_tests.hpp"
//#include"testing/05_progression_grammar_tests.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

// targeter:

	template<auto static_source>
	struct T_chord_assembly_targeter
	{
		using T_grammar					= chord::T_chord_assembly_grammar;

		constexpr static auto static_grammar		= U_store_T<T_grammar>;

		// pg parsed:

		template<auto ss, auto sg>
		constexpr static auto U_static_pg_parsed	= U_store_T<T_parser_generator_parsed<ss, sg>>;

		constexpr static auto static_pg_src		= _static_callable_<T_grammar::source>;
		constexpr static auto static_pg_scanned		= U_store_T<T_parser_generator_scanned<static_pg_src>>;
		constexpr static auto static_pg_parsed		= U_static_pg_parsed<static_pg_scanned, static_grammar>;

		// scanned:

		template<auto st, auto ss>
		constexpr static auto U_static_scanned		= U_store_T<chord::T_chord_assembly_scanner_parsed<st, ss>>;

		constexpr static auto static_scanned		= U_static_scanned<static_pg_parsed, static_source>;

		// parsed:

		template<auto st, auto ss>
		constexpr static auto U_static_parsed		= U_store_T<chord::T_chord_assembly_parsed<st, ss>>;

		constexpr static auto static_parsed		= U_static_parsed<static_pg_parsed, static_scanned>;
	};

/***********************************************************************************************************************/

// targeted:

	template<auto callable_source>
	struct T_chord_assembly_targeted
	{
		constexpr static auto static_pair	= _static_callable_<callable_source>;
		constexpr static auto static_src	= _static_car_<static_pair>;
		constexpr static auto value		= T_chord_assembly_targeter<static_src>{};
		using type				= decltype(value);
	};

/***********************************************************************************************************************/

	using chord_scanner_grammar		= chord::T_chord_assembly_scanner_grammar;
	using chord_grammar			= chord::T_chord_assembly_grammar;
	constexpr auto static_scanner_grammar	= U_store_T<chord_scanner_grammar>;
	constexpr auto static_grammar		= U_store_T<chord_grammar>;
//	constexpr auto src			= chord::_square_v0;
//	constexpr auto src			= chord::_square_v1;
//	constexpr auto src			= chord::_sum_of_squares_v0;
//	constexpr auto src			= chord::_sum_of_squares_v1;
	constexpr auto src			= chord::_twice_v0;
//	constexpr auto src			= chord::_x_to5_plus1_v0;
//	constexpr auto src			= chord::_binary_dispatch_v0;
//	constexpr auto src			= chord::_factorial_v0;

/***********************************************************************************************************************/

//	using targt_type = T_chord_assembly_targeted<src>;
//	using contr_type = T_chain_comply_contr<U_store_T<targt_type>, 10>;

	int main(int argc, char *argv[])
	{
	//	constexpr auto f  = _subpose_<_multiply_, _decrement_<>, _id_, _increment_<>>;
	//	constexpr auto sq = _argpose_<_multiply_, 0, 0>;

	//	printf("%d\n", apply<sq>(3));
	//	printf("%d\n", apply<f>(3, 4, 5));

	//	auto parsed_printer = chord_assembly_parsed_printer<static_grammar, src>{};
	//	parsed_printer.print_tree();
	//	parsed_printer.print_morph();

	//	auto targeted_printer = chord_assembly_targeted_printer<src>{};
	//	targeted_printer.print_controller();

	//	printf("%d\n", chord::square_v0(5));
	//	printf("%d\n", chord::square_v1(7));
	//	printf("%d\n", chord::sum_of_squares_v1(3, 5));
		printf("%d\n", chord::twice_v0(3));
	//	printf("%d\n", chord::factorial_v0(5));

	//	chord::grammar_tests();

		return 0;
	}

