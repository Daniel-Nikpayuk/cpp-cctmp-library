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

#define NIK_PARSER_GENERATOR_PDA // bug: currently both need to be on or both off.
#define NIK_CHORD_ASSEMBLY_PDA

/***********************************************************************************************************************/

#include"define_macros.hpp"

#include"00_cctmp_grammar.hpp"
#include"01_cctmp_argument.hpp"
#include"02_cctmp_parameter.hpp"
#include"03_cctmp_praxis.hpp"
#include"04_cctmp_interpreter.hpp"
#include"05_cctmp_scope.hpp"
#include"06_cctmp_relation.hpp"
#include"07_cctmp_graph.hpp"
#include"08_cctmp_lexer.hpp"
#include"09_cctmp_syntax.hpp"
#include"10_cctmp_parser.hpp"
#include"11_cctmp_generator.hpp"

#include"12_chord_lexer.hpp"
#include"13_chord_syntax.hpp"
#include"14_chord_action.hpp"
#include"15_chord_parser.hpp"
#include"16_chord_chain.hpp"
#include"17_chord_progression.hpp"
#include"18_chord_machine.hpp"
#include"19_chord_targeter.hpp"
#include"20_chord_metapiler.hpp"

#include"undef_macros.hpp"

//#include"documentation/01_case_studies.hpp"
#include"documentation/02_chord_progressions.hpp"

#include"testing/00_generic_printers.hpp"
#include"testing/01_parser_generator_printers.hpp"
#include"testing/02_chord_assembly_printers.hpp"
//#include"testing/04_chord_grammar_tests.hpp"
#include"testing/05_progression_grammar_tests.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	chord::grammar_tests(); // 24 tests.

	//	chord::repeat_tests ();
	//	chord::fold_tests   ();
	//	chord::find_tests   ();
	//	chord::sift_tests   ();
	//	chord::map_tests    ();
	//	chord::zip_tests    ();
	//	chord::glide_tests  ();
	//	chord::fasten_tests ();

		return 0;
	}

