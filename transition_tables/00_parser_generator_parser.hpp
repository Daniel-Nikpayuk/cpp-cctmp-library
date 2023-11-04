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

// parser:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automaton:

/***********************************************************************************************************************/

// interface:

	template<typename T_grammar>
	struct T_parser_generator_pda
	{
		using ActName			= typename T_grammar::ActName;
		using T_lexer			= typename T_grammar::T_lexer;
		using Terminal			= typename T_grammar::Terminal;
		using Nonterminal		= typename T_grammar::Nonterminal;

		nik_ces auto row_size		= Nonterminal::dimension;
		nik_ces auto col_size		= Terminal::dimension;

		nik_ces auto prod_size		= cctmp::string_literal("aMAsB").size();

		nik_ces auto & stack_start	= Nonterminal::stack_start;
		nik_ces auto & stack_finish	= Terminal::stack_finish;

		nik_ces auto stack_size		= cctmp::literal("TNAsBD").size();
							// literal is intentional.
							// this is the longest possible sentential.

		using prod_type				= generator::Production<prod_size>;
		using cprod_type			= prod_type const;
		using list_type				= cctmp::sequence<prod_type, row_size * col_size>;

		list_type list; // list instead of table due to clang bug.

		nik_ce T_parser_generator_pda()
		{
			list.fullsize();

			list[3].push({false, 3}); list[3].push({true, 2}); list[3].push({true, 1});
			list[3].valid = true; list[3].action = 1;
			list[11].valid = true; list[11].action = 8;
			list[12].push({false, 3}); list[12].push({true, 3}); list[12].push({true, 1});
			list[12].valid = true; list[12].action = 1;
			list[23].push({false, 5}); list[23].push({true, 5}); list[23].push({true, 8});
			list[23].push({false, 8}); list[23].push({true, 4}); list[23].valid = true; list[23].action = 5;
			list[24].push({false, 6}); list[24].push({true, 11}); list[24].push({true, 10});
			list[24].push({true, 12}); list[24].valid = true; list[24].action = 0;
			list[32].push({false, 5}); list[32].push({true, 5}); list[32].push({true, 8});
			list[32].push({false, 8}); list[32].push({true, 4}); list[32].valid = true; list[32].action = 6;
			list[33].push({false, 6}); list[33].push({true, 11}); list[33].push({true, 10});
			list[33].push({true, 12}); list[33].valid = true; list[33].action = 0;
			list[38].valid = true; list[38].action = 0;
			list[39].valid = true; list[39].action = 0;
			list[41].push({false, 5}); list[41].push({true, 5}); list[41].push({true, 8});
			list[41].push({false, 8}); list[41].push({true, 4}); list[41].valid = true; list[41].action = 7;
			list[48].push({true, 7}); list[48].push({true, 6}); list[48].valid = true; list[48].action = 0;
			list[49].push({false, 4}); list[49].valid = true; list[49].action = 3;
			list[57].push({true, 7}); list[57].push({true, 6}); list[57].valid = true; list[57].action = 0;
			list[61].valid = true; list[61].action = 0;
			list[62].valid = true; list[62].action = 0;
			list[66].push({false, 3}); list[66].valid = true; list[66].action = 2;
			list[79].push({false, 7}); list[79].push({true, 9}); list[79].valid = true; list[79].action = 0;
			list[80].valid = true; list[80].action = 0;
			list[84].push({false, 3}); list[84].valid = true; list[84].action = 4;
			list[93].push({true, 11}); list[93].push({true, 10}); list[93].valid = true; list[93].action = 0;
			list[98].valid = true; list[98].action = 0;
			list[102].push({false, 3}); list[102].valid = true; list[102].action = 0;
			list[116].push({false, 8}); list[116].valid = true; list[116].action = 0;
		}

		nik_ce cprod_type & production(csymbol_type & row, ctoken_type col) const
			{ return list[row.token() * col_size + col]; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

