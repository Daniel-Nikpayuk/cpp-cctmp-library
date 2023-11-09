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

// scanner:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// chord assembly:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automaton:

/***********************************************************************************************************************/

// interface:

	template<typename T_grammar>
	struct T_chord_assembly_scanner_pda
	{
		using ActName			= typename T_grammar::ActName;
		using T_lexer			= typename T_grammar::T_lexer;
		using Token			= typename T_grammar::Token;

		nik_ces auto start_index	= 0;
		nik_ces auto row_size		= 42;
		nik_ces auto col_size		= 42;

		nik_ces auto prod_size		= 7; // cctmp::string_literal("<A|C|B|B>").size();

		nik_ces auto stack_finish	= symbol_type{generator::Sign::terminal, Token::prompt};
		nik_ces auto stack_start	= symbol_type{generator::Sign::nonterminal, start_index};

		nik_ces auto stack_size		= cctmp::literal("F<A|C|B|B>YPZ{}YPZYP,PZV;HGO").size(); // needs refining.
							// literal is intentional.
							// this is the longest possible sentential.

		using prod_type				= generator::Production<prod_size>;
		using cprod_type			= prod_type const;
		using list_type				= cctmp::sequence<prod_type, row_size * col_size>;

		list_type list; // list instead of table due to clang bug.
		bool ambiguous;

		nik_ce T_chord_assembly_scanner_pda() : ambiguous{}
		{
			list.fullsize();

			list[3].push({true, 9}); list[3].push({true, 1}); list[3].push({true, 11});
			list[3].push({true, 2}); list[3].push({true, 3}); list[3].valid = true; list[3].action = 0;
			list[45].push({true, 10}); list[45].push({true, 1}); list[45].valid = true; list[45].action = 0;
			list[49].valid = true; list[49].action = 0;
			list[92].push({true, 12}); list[92].push({true, 14}); list[92].push({true, 4});
			list[92].valid = true; list[92].action = 0;
			list[128].valid = true; list[128].action = 1;
			list[134].push({true, 2}); list[134].push({true, 3}); list[134].valid = true; list[134].action = 0;
			list[171].push({true, 7}); list[171].push({true, 5}); list[171].push({true, 6});
			list[171].valid = true; list[171].action = 0;
			list[172].push({true, 7}); list[172].push({true, 5}); list[172].push({true, 6});
			list[172].valid = true; list[172].action = 0;
			list[177].push({true, 15}); list[177].push({true, 41}); list[177].push({true, 16});
			list[177].valid = true; list[177].action = 0;
			list[180].push({true, 7}); list[180].push({true, 5}); list[180].push({true, 6});
			list[180].valid = true; list[180].action = 0;
			list[182].push({true, 7}); list[182].push({true, 5}); list[182].push({true, 6});
			list[182].valid = true; list[182].action = 0;
			list[184].push({true, 7}); list[184].push({true, 5}); list[184].push({true, 6});
			list[184].valid = true; list[184].action = 0;
			list[213].push({true, 7}); list[213].push({true, 5}); list[213].valid = true; list[213].action = 0;
			list[214].push({true, 7}); list[214].push({true, 5}); list[214].valid = true; list[214].action = 0;
			list[218].valid = true; list[218].action = 0;
			list[219].valid = true; list[219].action = 0;
			list[220].valid = true; list[220].action = 0;
			list[221].valid = true; list[221].action = 0;
			list[222].push({true, 7}); list[222].push({true, 5}); list[222].valid = true; list[222].action = 0;
			list[224].push({true, 7}); list[224].push({true, 5}); list[224].valid = true; list[224].action = 0;
			list[226].push({true, 7}); list[226].push({true, 5}); list[226].valid = true; list[226].action = 0;
			list[260].push({true, 13}); list[260].push({true, 14}); list[260].push({true, 7});
			list[260].push({true, 5}); list[260].push({true, 6}); list[260].valid = true; list[260].action = 0;
			list[261].push({true, 15}); list[261].push({true, 41}); list[261].push({true, 16});
			list[261].valid = true; list[261].action = 0;
			list[262].push({true, 17}); list[262].push({true, 18}); list[262].push({true, 19});
			list[262].valid = true; list[262].action = 0;
			list[263].push({true, 20}); list[263].push({true, 21}); list[263].push({true, 22});
			list[263].valid = true; list[263].action = 0;
			list[297].push({true, 23}); list[297].push({true, 8}); list[297].valid = true; list[297].action = 0;
			list[298].push({true, 23}); list[298].push({true, 8}); list[298].valid = true; list[298].action = 0;
			list[306].push({false, 12}); list[306].push({true, 24}); list[306].push({false, 13});
			list[306].push({true, 37}); list[306].push({true, 38}); list[306].push({true, 25});
			list[306].valid = true; list[306].action = 0;
			list[308].push({true, 26}); list[308].push({true, 37}); list[308].push({true, 38});
			list[308].push({true, 27}); list[308].push({true, 28}); list[308].push({true, 29});
			list[308].push({true, 30}); list[308].valid = true; list[308].action = 0;
			list[310].push({true, 31}); list[310].push({true, 37}); list[310].push({true, 38});
			list[310].push({true, 32}); list[310].valid = true; list[310].action = 0;
			list[349].push({true, 33}); list[349].push({true, 37}); list[349].push({true, 38});
			list[349].push({true, 34}); list[349].valid = true; list[349].action = 0;
			list[353].push({true, 35}); list[353].push({true, 41}); list[353].push({true, 36});
			list[353].valid = true; list[353].action = 0;
			list[381].push({false, 3}); list[381].valid = true; list[381].action = 0;
			list[423].push({false, 3}); list[423].valid = true; list[423].action = 2;
			list[469].push({false, 7}); list[469].valid = true; list[469].action = 0;
			list[512].push({false, 8}); list[512].valid = true; list[512].action = 3;
			list[554].push({false, 8}); list[554].valid = true; list[554].action = 4;
			list[595].push({false, 7}); list[595].valid = true; list[595].action = 0;
			list[639].push({false, 9}); list[639].valid = true; list[639].action = 5;
			list[679].push({false, 7}); list[679].valid = true; list[679].action = 0;
			list[724].push({false, 10}); list[724].valid = true; list[724].action = 6;
			list[759].push({false, 3}); list[759].valid = true; list[759].action = 0;
			list[805].push({false, 7}); list[805].valid = true; list[805].action = 0;
			list[851].push({false, 11}); list[851].valid = true; list[851].action = 6;
			list[885].push({false, 3}); list[885].valid = true; list[885].action = 0;
			list[931].push({false, 7}); list[931].valid = true; list[931].action = 0;
			list[969].push({false, 3}); list[969].valid = true; list[969].action = 7;
			list[970].push({false, 4}); list[970].valid = true; list[970].action = 0;
			list[1011].push({false, 3}); list[1011].valid = true; list[1011].action = 8;
			list[1057].push({false, 7}); list[1057].valid = true; list[1057].action = 0;
			list[1106].push({false, 14}); list[1106].valid = true; list[1106].action = 9;
			list[1141].push({false, 7}); list[1141].valid = true; list[1141].action = 0;
			list[1191].push({false, 15}); list[1191].valid = true; list[1191].action = 6;
			list[1221].push({false, 3}); list[1221].valid = true; list[1221].action = 0;
			list[1267].push({false, 7}); list[1267].valid = true; list[1267].action = 0;
			list[1318].push({false, 16}); list[1318].valid = true; list[1318].action = 9;
			list[1351].push({false, 7}); list[1351].valid = true; list[1351].action = 0;
			list[1399].push({false, 13}); list[1399].valid = true; list[1399].action = 9;
			list[1435].push({false, 7}); list[1435].valid = true; list[1435].action = 0;
			list[1487].push({false, 17}); list[1487].valid = true; list[1487].action = 5;
			list[1519].push({false, 7}); list[1519].valid = true; list[1519].action = 0;
			list[1557].push({false, 3}); list[1557].valid = true; list[1557].action = 10;
			list[1559].push({false, 5}); list[1559].valid = true; list[1559].action = 11;
			list[1560].push({false, 6}); list[1560].valid = true; list[1560].action = 12;
			list[1599].push({true, 39}); list[1599].push({true, 38}); list[1599].valid = true; list[1599].action = 0;
			list[1601].push({true, 39}); list[1601].push({true, 38}); list[1601].valid = true; list[1601].action = 0;
			list[1602].push({true, 39}); list[1602].push({true, 38}); list[1602].valid = true; list[1602].action = 0;
			list[1603].valid = true; list[1603].action = 15;
			list[1608].push({false, 12}); list[1608].push({true, 40}); list[1608].push({true, 38});
			list[1608].valid = true; list[1608].action = 0;
			list[1641].push({false, 3}); list[1641].valid = true; list[1641].action = 10;
			list[1643].push({false, 5}); list[1643].valid = true; list[1643].action = 11;
			list[1644].push({false, 6}); list[1644].valid = true; list[1644].action = 12;
			list[1683].push({false, 3}); list[1683].valid = true; list[1683].action = 10;
			list[1725].push({false, 3}); list[1725].valid = true; list[1725].action = 0;
			list[1727].push({false, 5}); list[1727].valid = true; list[1727].action = 0;
			list[1728].push({false, 6}); list[1728].valid = true; list[1728].action = 0;
		}

		nik_ce cprod_type & production(csymbol_type & row, ctoken_type col) const
			{ return list[row.token() * col_size + col]; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

