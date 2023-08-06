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

		nik_ces auto start_index	= 12;
		nik_ces auto row_size		= 44;
		nik_ces auto col_size		= 42;

		nik_ces auto prod_size		= cctmp::string_literal("<A|C|B|B>").size();

		nik_ces auto stack_finish	= symbol_type{cctmp::Sign::terminal, Token::prompt};
		nik_ces auto stack_start	= symbol_type{cctmp::Sign::nonterminal, start_index};

		nik_ces auto stack_size		= cctmp::literal("F<A|C|B|B>YPZ{}YPZYP,PZV;HGO").size(); // needs refining.
							// literal is intentional.
							// this is the longest possible sentential.

		using prod_type				= cctmp::Production<prod_size>;
		using cprod_type			= prod_type const;
		using list_type				= cctmp::sequence<prod_type, row_size * col_size>;

		list_type list; // list instead of table due to clang bug.
		bool ambiguous;

		nik_ce T_chord_assembly_scanner_pda() : ambiguous{}
		{
			list.fullsize();

			list[3].push({false, 3}); list[3].valid = true; list[3].action = 1;
			list[46].push({false, 4}); list[46].valid = true; list[46].action = 1;
			list[89].push({false, 5}); list[89].valid = true; list[89].action = 1;
			list[140].push({false, 14}); list[140].valid = true; list[140].action = 1;
			list[174].push({false, 6}); list[174].valid = true; list[174].action = 1;
			list[218].push({false, 8}); list[218].valid = true; list[218].action = 2;
			list[267].push({false, 15}); list[267].valid = true; list[267].action = 3;
			list[304].push({false, 10}); list[304].valid = true; list[304].action = 3;
			list[347].push({false, 11}); list[347].valid = true; list[347].action = 3;
			list[385].push({false, 7}); list[385].valid = true; list[385].action = 4;
			list[423].push({true, 0}); list[423].valid = true; list[423].action = 5;
			list[424].push({true, 1}); list[424].valid = true; list[424].action = 6;
			list[465].push({true, 0}); list[465].valid = true; list[465].action = 0;
			list[467].push({true, 2}); list[467].valid = true; list[467].action = 0;
			list[468].push({true, 4}); list[468].valid = true; list[468].action = 0;
			list[496].push({true, 22}); list[496].valid = true; list[496].action = 7;
			list[497].push({true, 22}); list[497].valid = true; list[497].action = 7;
			list[498].push({true, 22}); list[498].valid = true; list[498].action = 7;
			list[499].push({true, 25}); list[499].valid = true; list[499].action = 8;
			list[500].push({true, 25}); list[500].valid = true; list[500].action = 8;
			list[501].push({true, 25}); list[501].valid = true; list[501].action = 8;
			list[502].push({true, 25}); list[502].valid = true; list[502].action = 8;
			list[503].push({true, 25}); list[503].valid = true; list[503].action = 8;
			list[507].push({false, 3}); list[507].push({true, 13}); list[507].push({false, 7});
			list[507].push({true, 14}); list[507].push({true, 15}); list[507].valid = true; list[507].action = 0;
			list[549].push({false, 3}); list[549].push({true, 13}); list[549].valid = true; list[549].action = 9;
			list[553].valid = true; list[553].action = 0;
			list[596].push({true, 5}); list[596].push({true, 9}); list[596].push({true, 16});
			list[596].valid = true; list[596].action = 0;
			list[632].valid = true; list[632].action = 10;
			list[638].push({true, 14}); list[638].push({true, 15}); list[638].valid = true; list[638].action = 0;
			list[675].push({true, 19}); list[675].push({true, 9}); list[675].push({true, 17});
			list[675].push({true, 18}); list[675].valid = true; list[675].action = 0;
			list[676].push({true, 19}); list[676].push({true, 9}); list[676].push({true, 17});
			list[676].push({true, 18}); list[676].valid = true; list[676].action = 0;
			list[681].push({false, 9}); list[681].push({true, 11}); list[681].push({true, 9});
			list[681].valid = true; list[681].action = 11;
			list[684].push({true, 19}); list[684].push({true, 9}); list[684].push({true, 17});
			list[684].push({true, 18}); list[684].valid = true; list[684].action = 0;
			list[686].push({true, 19}); list[686].push({true, 9}); list[686].push({true, 17});
			list[686].push({true, 18}); list[686].valid = true; list[686].action = 0;
			list[688].push({true, 19}); list[688].push({true, 9}); list[688].push({true, 17});
			list[688].push({true, 18}); list[688].valid = true; list[688].action = 0;
			list[717].push({true, 19}); list[717].push({true, 9}); list[717].push({true, 17});
			list[717].valid = true; list[717].action = 0;
			list[718].push({true, 19}); list[718].push({true, 9}); list[718].push({true, 17});
			list[718].valid = true; list[718].action = 0;
			list[722].valid = true; list[722].action = 0;
			list[723].valid = true; list[723].action = 0;
			list[724].valid = true; list[724].action = 0;
			list[725].valid = true; list[725].action = 0;
			list[726].push({true, 19}); list[726].push({true, 9}); list[726].push({true, 17});
			list[726].valid = true; list[726].action = 0;
			list[728].push({true, 19}); list[728].push({true, 9}); list[728].push({true, 17});
			list[728].valid = true; list[728].action = 0;
			list[730].push({true, 19}); list[730].push({true, 9}); list[730].push({true, 17});
			list[730].valid = true; list[730].action = 0;
			list[764].push({true, 5}); list[764].push({true, 9}); list[764].push({true, 19});
			list[764].push({true, 9}); list[764].push({true, 17}); list[764].push({true, 18});
			list[764].valid = true; list[764].action = 12;
			list[765].push({false, 9}); list[765].push({true, 11}); list[765].push({true, 9});
			list[765].valid = true; list[765].action = 11;
			list[766].push({true, 7}); list[766].push({true, 0}); list[766].push({true, 9});
			list[766].valid = true; list[766].action = 0;
			list[767].push({true, 8}); list[767].push({true, 0}); list[767].push({true, 9});
			list[767].valid = true; list[767].action = 0;
			list[801].push({true, 10}); list[801].push({true, 20}); list[801].valid = true; list[801].action = 0;
			list[802].push({true, 10}); list[802].push({true, 20}); list[802].valid = true; list[802].action = 0;
			list[810].push({false, 12}); list[810].push({true, 0}); list[810].push({false, 13});
			list[810].push({true, 21}); list[810].valid = true; list[810].action = 6;
			list[812].push({true, 3}); list[812].push({true, 11}); list[812].push({true, 21});
			list[812].push({true, 9}); list[812].push({true, 6}); list[812].push({true, 0});
			list[812].valid = true; list[812].action = 6;
			list[814].push({false, 16}); list[814].push({true, 11}); list[814].push({true, 21});
			list[814].valid = true; list[814].action = 6;
			list[853].push({false, 13}); list[853].push({true, 11}); list[853].push({true, 21});
			list[853].valid = true; list[853].action = 0;
			list[857].push({false, 17}); list[857].push({true, 11}); list[857].valid = true; list[857].action = 0;
			list[885].push({true, 11}); list[885].push({true, 21}); list[885].valid = true; list[885].action = 0;
			list[887].push({true, 11}); list[887].push({true, 21}); list[887].valid = true; list[887].action = 0;
			list[888].push({true, 11}); list[888].push({true, 21}); list[888].valid = true; list[888].action = 0;
			list[889].valid = true; list[889].action = 0;
			list[894].push({false, 12}); list[894].push({true, 0}); list[894].push({true, 21});
			list[894].valid = true; list[894].action = 0;
			list[916].push({true, 11}); list[916].push({true, 21}); list[916].valid = true; list[916].action = 0;
			list[917].push({true, 11}); list[917].push({true, 21}); list[917].valid = true; list[917].action = 0;
			list[918].push({true, 11}); list[918].push({true, 21}); list[918].valid = true; list[918].action = 0;
			list[919].push({true, 11}); list[919].push({true, 21}); list[919].valid = true; list[919].action = 0;
			list[920].push({true, 11}); list[920].push({true, 21}); list[920].valid = true; list[920].action = 0;
			list[921].push({true, 11}); list[921].push({true, 21}); list[921].valid = true; list[921].action = 0;
			list[922].push({true, 11}); list[922].push({true, 21}); list[922].valid = true; list[922].action = 0;
			list[923].push({true, 11}); list[923].push({true, 21}); list[923].valid = true; list[923].action = 0;
			list[958].push({false, 34}); list[958].push({false, 18}); list[958].push({true, 23});
			list[958].push({false, 19}); list[958].valid = true; list[958].action = 0;
			list[959].push({false, 35}); list[959].push({false, 18}); list[959].push({true, 23});
			list[959].push({false, 19}); list[959].valid = true; list[959].action = 0;
			list[960].push({false, 36}); list[960].push({false, 18}); list[960].push({true, 23});
			list[960].push({false, 19}); list[960].valid = true; list[960].action = 0;
			list[969].push({true, 24}); list[969].push({true, 23}); list[969].valid = true; list[969].action = 13;
			list[985].valid = true; list[985].action = 14;
			list[987].push({true, 24}); list[987].push({true, 23}); list[987].valid = true; list[987].action = 13;
			list[988].push({true, 24}); list[988].push({true, 23}); list[988].valid = true; list[988].action = 13;
			list[990].push({true, 24}); list[990].push({true, 23}); list[990].valid = true; list[990].action = 13;
			list[991].push({true, 24}); list[991].push({true, 23}); list[991].valid = true; list[991].action = 13;
			list[1011].push({false, 3}); list[1011].valid = true; list[1011].action = 0;
			list[1029].push({false, 21}); list[1029].valid = true; list[1029].action = 0;
			list[1030].push({false, 22}); list[1030].valid = true; list[1030].action = 0;
			list[1032].push({false, 24}); list[1032].valid = true; list[1032].action = 0;
			list[1033].push({false, 25}); list[1033].valid = true; list[1033].action = 0;
			list[1087].push({false, 37}); list[1087].push({true, 26}); list[1087].push({true, 37});
			list[1087].push({true, 34}); list[1087].valid = true; list[1087].action = 0;
			list[1088].push({false, 38}); list[1088].push({true, 26}); list[1088].push({true, 36});
			list[1088].push({true, 37}); list[1088].push({true, 34}); list[1088].valid = true; list[1088].action = 0;
			list[1089].push({false, 39}); list[1089].push({true, 27}); list[1089].push({true, 38});
			list[1089].push({true, 37}); list[1089].push({true, 34}); list[1089].valid = true; list[1089].action = 0;
			list[1090].push({false, 40}); list[1090].push({true, 26}); list[1090].push({true, 36});
			list[1090].push({true, 37}); list[1090].push({true, 34}); list[1090].valid = true; list[1090].action = 0;
			list[1091].push({false, 41}); list[1091].push({true, 26}); list[1091].push({true, 36});
			list[1091].push({true, 37}); list[1091].push({true, 34}); list[1091].valid = true; list[1091].action = 0;
			list[1110].push({false, 18}); list[1110].push({true, 28}); list[1110].push({false, 20});
			list[1110].push({true, 30}); list[1110].push({false, 20}); list[1110].push({true, 30});
			list[1110].push({false, 19}); list[1110].valid = true; list[1110].action = 0;
			list[1152].push({false, 18}); list[1152].push({true, 28}); list[1152].push({false, 20});
			list[1152].push({true, 29}); list[1152].push({false, 20}); list[1152].push({true, 30});
			list[1152].push({false, 20}); list[1152].push({true, 30}); list[1152].push({false, 19});
			list[1152].valid = true; list[1152].action = 0;
			list[1179].push({true, 33}); list[1179].push({true, 28}); list[1179].valid = true; list[1179].action = 0;
			list[1196].valid = true; list[1196].action = 0;
			list[1197].push({true, 33}); list[1197].push({true, 28}); list[1197].valid = true; list[1197].action = 0;
			list[1198].push({true, 33}); list[1198].push({true, 28}); list[1198].valid = true; list[1198].action = 0;
			list[1221].push({false, 3}); list[1221].push({true, 31}); list[1221].valid = true; list[1221].action = 0;
			list[1263].push({false, 3}); list[1263].push({true, 31}); list[1263].valid = true; list[1263].action = 0;
			list[1279].valid = true; list[1279].action = 0;
			list[1280].valid = true; list[1280].action = 0;
			list[1305].push({true, 33}); list[1305].push({true, 32}); list[1305].valid = true; list[1305].action = 0;
			list[1321].valid = true; list[1321].action = 0;
			list[1322].valid = true; list[1322].action = 0;
			list[1323].push({true, 33}); list[1323].push({true, 32}); list[1323].valid = true; list[1323].action = 0;
			list[1324].push({true, 33}); list[1324].push({true, 32}); list[1324].valid = true; list[1324].action = 0;
			list[1347].push({true, 33}); list[1347].valid = true; list[1347].action = 0;
			list[1363].valid = true; list[1363].action = 0;
			list[1364].valid = true; list[1364].action = 0;
			list[1365].push({true, 33}); list[1365].valid = true; list[1365].action = 0;
			list[1366].push({true, 33}); list[1366].valid = true; list[1366].action = 0;
			list[1389].push({false, 3}); list[1389].valid = true; list[1389].action = 0;
			list[1407].push({false, 21}); list[1407].valid = true; list[1407].action = 0;
			list[1408].push({false, 22}); list[1408].valid = true; list[1408].action = 0;
			list[1431].valid = true; list[1431].action = 16;
			list[1433].valid = true; list[1433].action = 16;
			list[1434].valid = true; list[1434].action = 16;
			list[1435].valid = true; list[1435].action = 16;
			list[1440].valid = true; list[1440].action = 16;
			list[1455].push({true, 35}); list[1455].push({true, 34}); list[1455].valid = true; list[1455].action = 15;
			list[1457].push({true, 35}); list[1457].push({true, 34}); list[1457].valid = true; list[1457].action = 15;
			list[1459].push({true, 35}); list[1459].push({true, 34}); list[1459].valid = true; list[1459].action = 15;
			list[1462].valid = true; list[1462].action = 16;
			list[1463].valid = true; list[1463].action = 16;
			list[1464].valid = true; list[1464].action = 16;
			list[1465].valid = true; list[1465].action = 16;
			list[1466].valid = true; list[1466].action = 16;
			list[1467].valid = true; list[1467].action = 16;
			list[1468].valid = true; list[1468].action = 16;
			list[1469].valid = true; list[1469].action = 16;
			list[1497].push({true, 36}); list[1497].valid = true; list[1497].action = 0;
			list[1499].push({true, 36}); list[1499].valid = true; list[1499].action = 0;
			list[1501].push({true, 38}); list[1501].valid = true; list[1501].action = 0;
			list[1539].push({true, 39}); list[1539].push({true, 41}); list[1539].push({true, 40});
			list[1539].valid = true; list[1539].action = 0;
			list[1541].push({true, 39}); list[1541].push({true, 41}); list[1541].push({true, 40});
			list[1541].valid = true; list[1541].action = 0;
			list[1581].push({true, 39}); list[1581].push({true, 41}); list[1581].push({false, 33});
			list[1581].push({true, 41}); list[1581].push({true, 40}); list[1581].valid = true; list[1581].action = 15;
			list[1583].push({true, 39}); list[1583].push({true, 41}); list[1583].push({false, 33});
			list[1583].push({true, 41}); list[1583].push({true, 40}); list[1583].valid = true; list[1583].action = 15;
			list[1627].push({false, 31}); list[1627].push({false, 32}); list[1627].valid = true; list[1627].action = 0;
			list[1665].push({false, 27}); list[1665].valid = true; list[1665].action = 0;
			list[1667].push({false, 29}); list[1667].valid = true; list[1667].action = 0;
			list[1708].push({false, 28}); list[1708].valid = true; list[1708].action = 0;
			list[1710].push({false, 30}); list[1710].valid = true; list[1710].action = 0;
			list[1725].push({true, 43}); list[1725].push({false, 20}); list[1725].push({true, 42});
			list[1725].valid = true; list[1725].action = 0;
			list[1745].push({true, 43}); list[1745].push({false, 20}); list[1745].push({true, 42});
			list[1745].valid = true; list[1745].action = 0;
			list[1746].push({false, 24}); list[1746].push({false, 20}); list[1746].push({false, 25});
			list[1746].valid = true; list[1746].action = 0;
			list[1747].push({false, 25}); list[1747].push({false, 20}); list[1747].push({false, 24});
			list[1747].valid = true; list[1747].action = 0;
			list[1750].valid = true; list[1750].action = 0;
			list[1752].valid = true; list[1752].action = 0;
			list[1755].valid = true; list[1755].action = 0;
			list[1767].push({true, 43}); list[1767].valid = true; list[1767].action = 0;
			list[1787].push({true, 43}); list[1787].valid = true; list[1787].action = 0;
			list[1790].push({false, 26}); list[1790].valid = true; list[1790].action = 0;
			list[1809].push({false, 3}); list[1809].valid = true; list[1809].action = 0;
			list[1829].push({false, 23}); list[1829].push({false, 3}); list[1829].valid = true; list[1829].action = 0;
		}

		nik_ce cprod_type & production(csymbol_type & row, ctoken_type col) const
			{ return list[row.token() * col_size + col]; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

