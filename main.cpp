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
#include"00_cctmp/03_praxis.hpp"
#include"00_cctmp/04_interpreter.hpp"
#include"00_cctmp/05_scope.hpp"
#include"00_cctmp/06_relation.hpp"
#include"00_cctmp/07_graph.hpp"
#include"00_cctmp/08_lexer.hpp"
#include"00_cctmp/09_syntax.hpp"
#include"00_cctmp/10_parser.hpp"
#include"00_cctmp/11_generator.hpp"

#include"01_chord/00_lexer.hpp"
#include"01_chord/01_scanner.hpp"
#include"01_chord/02_syntax.hpp"
#include"01_chord/03_action.hpp"
#include"01_chord/04_parser.hpp"
#include"01_chord/05_chain.hpp"
#include"01_chord/06_lookup.hpp"
#include"01_chord/07_cycle.hpp"
#include"01_chord/08_progression.hpp"
#include"01_chord/09_machine.hpp"
#include"01_chord/10_targeter.hpp"

//#include"02_math/00_byte_ring.hpp"
//#include"02_math/01_byte_array_ring.hpp"
//#include"02_math/02_cryptography.hpp"
//#include"02_math/03_linear_algebra.hpp"
//#include"02_math/04_signal_processing.hpp"

#include"undef_macros.hpp"

//#include"documentation/01_case_studies.hpp"
//#include"documentation/02_chord_progressions.hpp"

#include"testing/00_generic_printers.hpp"
#include"testing/01_parser_generator_printers.hpp"
#include"testing/02_chord_assembly_printers.hpp"
//#include"testing/04_chord_grammar_tests.hpp"
//#include"testing/05_progression_grammar_tests.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	chord::grammar_tests(); // 24 tests.

	//	chord::repeat_tests ();
	//	chord::map_tests    ();
	//	chord::fold_tests   ();
	//	chord::find_tests   ();
	//	chord::sift_tests   ();

	//	chord::change_of_base_tests ();
	//	chord::array_printer_tests  ();

		return 0;
	}

