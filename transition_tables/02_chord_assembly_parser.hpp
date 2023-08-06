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

// generic assembly:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// grammar:

/***********************************************************************************************************************/

/*
	struct T_chord_assembly_grammar
	{
		using ActName		= GAAN;
		using T_lexer		= T_chord_assembly_lexer;
		using Token		= typename T_lexer::Token;
		nik_ces auto size	= Token::dimension;

		nik_ces auto source()
		{
			return cctmp::context_free_grammar
			(
			// start:

				"S",

			// rules: (letters - ABCD FGHIJKLMN  QRSTUV    )

				"L -> l               : label       ;"
				"B -> i               : branch      ;"
				"G -> i               : goto        ;"
				"M -> i               : mvalue      ;"
				"C -> i               : lvalue      ;"
				"  -> .               : copy        ;"
				"R -> i               : rvalue      ;"
				"  -> _               : paste       ;"
				"  -> q               : quote       ;"
				"F -> \\;             : first_line  ;"
				"N -> \\;             : new_line    ;"
				"Q -> e               : new_line    ;"

				"S -> i A F T U       : define_name ;"
				"A -> i A             : define_arg  ;"
				"  -> e               : end_arg     ;"
				"T -> L N H                         ;"
				"U -> Q T U                         ;"
				"  -> e               : accept      ;"
				"H -> I N J K                       ;"
				"  -> r R \\;         : return      ;"
				"J -> I N J                         ;"
				"  -> e                             ;"
				"K -> g G \\;                       ;"
				"  -> r R \\;         : return      ;"
				"  -> L N H           : go_into     ;"
				"I -> C D                           ;"
				"  -> ! M \\= R V     : voidication ;"
				"  -> t R V N b B     : conditional ;"
				"  -> v R V           : voidication ;"
				"D -> # R             : assignment  ;"
				"  -> \\= R V         : application ;"
				"V -> R V                           ;"
				"  -> ! M V                         ;"
				"  -> e                             ;"
			);
		}

		nik_ces auto map = cctmp::table
		(
			U_strlit_type, U_token_type,

			sxt_pair(   " " , Token::invalid    ),
			sxt_pair(   "$" , Token::prompt     ),
			sxt_pair(   "i" , Token::identifier ),
			sxt_pair(   "." , Token::copy       ),
			sxt_pair(   "_" , Token::paste      ),
			sxt_pair(   "q" , Token::quote      ),
			sxt_pair( "\\;" , Token::statement  ),
			sxt_pair(   "l" , Token::label      ),
			sxt_pair(   "r" , Token::re_turn    ),
			sxt_pair(   "g" , Token::go_to      ),
			sxt_pair(   "!" , Token::mu_table   ),
			sxt_pair( "\\=" , Token::apply      ),
			sxt_pair(   "t" , Token::test       ),
			sxt_pair(   "b" , Token::branch     ),
			sxt_pair(   "v" , Token::vo_id      ),
			sxt_pair(   "#" , Token::assign     ),
			sxt_pair(   "e" , Token::empty      )
		);

		nik_ces auto action = cctmp::table
		(
			U_strlit_type, U_action_type,

			sxa_pair( "define_name" , ActName::define_name ),
			sxa_pair( "define_arg"  , ActName::define_arg  ),
			sxa_pair( "end_arg"     , ActName::end_arg     ),
			sxa_pair( "first_line"  , ActName::first_line  ),
			sxa_pair( "new_line"    , ActName::new_line    ),
			sxa_pair( "label"       , ActName::label       ),
			sxa_pair( "branch"      , ActName::branch      ),
			sxa_pair( "goto"        , ActName::go_to       ),
			sxa_pair( "go_into"     , ActName::go_into     ),
			sxa_pair( "return"      , ActName::re_turn     ),
			sxa_pair( "application" , ActName::application ),
			sxa_pair( "voidication" , ActName::voidication ),
			sxa_pair( "conditional" , ActName::conditional ),
			sxa_pair( "assignment"  , ActName::assignment  ),
			sxa_pair( "lvalue"      , ActName::lvalue      ),
			sxa_pair( "mvalue"      , ActName::mvalue      ),
			sxa_pair( "rvalue"      , ActName::rvalue      ),
			sxa_pair( "copy"        , ActName::copy        ),
			sxa_pair( "paste"       , ActName::paste       ),
			sxa_pair( "quote"       , ActName::quote       ),
			sxa_pair( "accept"      , ActName::accept      )
		);
	};
*/

	//	nik_ces auto prod_size		= cctmp::string_literal("tRVNbB").size();
	//	nik_ces auto stack_size		= cctmp::literal("tRVNbBNJK;U").size();

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automaton:

/***********************************************************************************************************************/

// interface:

	template<typename T_grammar>
	struct T_chord_assembly_pda
	{
		using ActName			= typename T_grammar::ActName;
		using T_lexer			= typename T_grammar::T_lexer;
		using Token			= typename T_grammar::Token;

		nik_ces auto start_index	= 11;
		nik_ces auto row_size		= 53;
		nik_ces auto col_size		= 42;

		nik_ces auto prod_size		= cctmp::string_literal("<A|C|M|L>").size(); // needs refining.

		nik_ces auto stack_finish	= symbol_type{cctmp::Sign::terminal, Token::prompt};
		nik_ces auto stack_start	= symbol_type{cctmp::Sign::nonterminal, start_index};

		nik_ces auto stack_size		= cctmp::literal("F<A|C|M|L>YPZ{}YPZYP,PZV;HGO").size(); // needs refining.
							// literal is intentional.
							// this is the longest possible sentential.

		using prod_type				= cctmp::Production<prod_size>;
		using cprod_type			= prod_type const;
		using list_type				= cctmp::sequence<prod_type, row_size * col_size>;

		list_type list; // list instead of table due to clang bug.
		bool ambiguous;

		nik_ce T_chord_assembly_pda() : ambiguous{}
		{
			list.fullsize();

			list[8].push({false, 8}); list[8].valid = true; list[8].action = 1;
			list[45].push({false, 3}); list[45].valid = true; list[45].action = 2;
			list[87].push({false, 3}); list[87].valid = true; list[87].action = 3;
			list[129].push({false, 3}); list[129].valid = true; list[129].action = 4;
			list[171].push({false, 3}); list[171].valid = true; list[171].action = 5;
			list[213].push({false, 3}); list[213].valid = true; list[213].action = 6;
			list[214].push({false, 4}); list[214].valid = true; list[214].action = 7;
			list[259].push({false, 7}); list[259].valid = true; list[259].action = 8;
			list[301].push({false, 7}); list[301].valid = true; list[301].action = 9;
			list[344].valid = true; list[344].action = 9;
			list[381].push({false, 3}); list[381].valid = true; list[381].action = 10;
			list[383].push({false, 5}); list[383].valid = true; list[383].action = 12;
			list[384].push({false, 6}); list[384].valid = true; list[384].action = 13;
			list[412].push({true, 21}); list[412].valid = true; list[412].action = 14;
			list[413].push({true, 21}); list[413].valid = true; list[413].action = 14;
			list[414].push({true, 21}); list[414].valid = true; list[414].action = 14;
			list[415].push({true, 24}); list[415].valid = true; list[415].action = 15;
			list[416].push({true, 24}); list[416].valid = true; list[416].action = 15;
			list[417].push({true, 24}); list[417].valid = true; list[417].action = 15;
			list[418].push({true, 24}); list[418].valid = true; list[418].action = 15;
			list[419].push({true, 24}); list[419].valid = true; list[419].action = 15;
			list[423].push({false, 3}); list[423].valid = true; list[423].action = 11;
			list[425].push({false, 5}); list[425].valid = true; list[425].action = 12;
			list[426].push({false, 6}); list[426].valid = true; list[426].action = 13;
			list[454].push({true, 21}); list[454].valid = true; list[454].action = 14;
			list[455].push({true, 21}); list[455].valid = true; list[455].action = 14;
			list[456].push({true, 21}); list[456].valid = true; list[456].action = 14;
			list[457].push({true, 24}); list[457].valid = true; list[457].action = 15;
			list[458].push({true, 24}); list[458].valid = true; list[458].action = 15;
			list[459].push({true, 24}); list[459].valid = true; list[459].action = 15;
			list[460].push({true, 24}); list[460].valid = true; list[460].action = 15;
			list[461].push({true, 24}); list[461].valid = true; list[461].action = 15;
			list[465].push({false, 3}); list[465].push({true, 12}); list[465].push({true, 6});
			list[465].push({true, 13}); list[465].push({true, 14}); list[465].valid = true; list[465].action = 16;
			list[507].push({false, 3}); list[507].push({true, 12}); list[507].valid = true; list[507].action = 17;
			list[511].valid = true; list[511].action = 0;
			list[554].push({true, 0}); list[554].push({true, 7}); list[554].push({true, 15});
			list[554].valid = true; list[554].action = 0;
			list[590].valid = true; list[590].action = 18;
			list[596].push({true, 8}); list[596].push({true, 13}); list[596].push({true, 14});
			list[596].valid = true; list[596].action = 0;
			list[633].push({true, 18}); list[633].push({true, 7}); list[633].push({true, 16});
			list[633].push({true, 17}); list[633].valid = true; list[633].action = 0;
			list[634].push({true, 18}); list[634].push({true, 7}); list[634].push({true, 16});
			list[634].push({true, 17}); list[634].valid = true; list[634].action = 0;
			list[639].push({false, 9}); list[639].push({true, 9}); list[639].push({false, 7});
			list[639].valid = true; list[639].action = 19;
			list[642].push({true, 18}); list[642].push({true, 7}); list[642].push({true, 16});
			list[642].push({true, 17}); list[642].valid = true; list[642].action = 0;
			list[644].push({true, 18}); list[644].push({true, 7}); list[644].push({true, 16});
			list[644].push({true, 17}); list[644].valid = true; list[644].action = 0;
			list[646].push({true, 18}); list[646].push({true, 7}); list[646].push({true, 16});
			list[646].push({true, 17}); list[646].valid = true; list[646].action = 0;
			list[675].push({true, 18}); list[675].push({true, 7}); list[675].push({true, 16});
			list[675].valid = true; list[675].action = 0;
			list[676].push({true, 18}); list[676].push({true, 7}); list[676].push({true, 16});
			list[676].valid = true; list[676].action = 0;
			list[680].valid = true; list[680].action = 0;
			list[681].valid = true; list[681].action = 0;
			list[682].valid = true; list[682].action = 0;
			list[683].valid = true; list[683].action = 0;
			list[684].push({true, 18}); list[684].push({true, 7}); list[684].push({true, 16});
			list[684].valid = true; list[684].action = 0;
			list[686].push({true, 18}); list[686].push({true, 7}); list[686].push({true, 16});
			list[686].valid = true; list[686].action = 0;
			list[688].push({true, 18}); list[688].push({true, 7}); list[688].push({true, 16});
			list[688].valid = true; list[688].action = 0;
			list[722].push({true, 0}); list[722].push({true, 7}); list[722].push({true, 18});
			list[722].push({true, 7}); list[722].push({true, 16}); list[722].push({true, 17});
			list[722].valid = true; list[722].action = 20;
			list[723].push({false, 9}); list[723].push({true, 9}); list[723].push({false, 7});
			list[723].valid = true; list[723].action = 19;
			list[724].push({false, 10}); list[724].push({true, 2}); list[724].push({false, 7});
			list[724].valid = true; list[724].action = 0;
			list[725].push({false, 11}); list[725].push({true, 3}); list[725].push({false, 7});
			list[725].valid = true; list[725].action = 0;
			list[759].push({true, 5}); list[759].push({true, 19}); list[759].valid = true; list[759].action = 0;
			list[760].push({true, 5}); list[760].push({true, 19}); list[760].valid = true; list[760].action = 0;
			list[768].push({false, 12}); list[768].push({true, 4}); list[768].push({false, 13});
			list[768].push({true, 10}); list[768].push({true, 20}); list[768].valid = true; list[768].action = 21;
			list[770].push({false, 14}); list[770].push({true, 10}); list[770].push({true, 20});
			list[770].push({true, 7}); list[770].push({false, 15}); list[770].push({true, 1});
			list[770].valid = true; list[770].action = 22;
			list[772].push({false, 16}); list[772].push({true, 10}); list[772].push({true, 20});
			list[772].valid = true; list[772].action = 21;
			list[811].push({false, 13}); list[811].push({true, 10}); list[811].push({true, 20});
			list[811].valid = true; list[811].action = 24;
			list[815].push({false, 17}); list[815].push({true, 9}); list[815].valid = true; list[815].action = 23;
			list[843].push({true, 9}); list[843].push({true, 20}); list[843].valid = true; list[843].action = 0;
			list[845].push({true, 9}); list[845].push({true, 20}); list[845].valid = true; list[845].action = 0;
			list[846].push({true, 9}); list[846].push({true, 20}); list[846].valid = true; list[846].action = 0;
			list[847].valid = true; list[847].action = 0;
			list[852].push({false, 12}); list[852].push({true, 4}); list[852].push({true, 20});
			list[852].valid = true; list[852].action = 0;
			list[874].push({true, 9}); list[874].push({true, 20}); list[874].valid = true; list[874].action = 0;
			list[875].push({true, 9}); list[875].push({true, 20}); list[875].valid = true; list[875].action = 0;
			list[876].push({true, 9}); list[876].push({true, 20}); list[876].valid = true; list[876].action = 0;
			list[877].push({true, 9}); list[877].push({true, 20}); list[877].valid = true; list[877].action = 0;
			list[878].push({true, 9}); list[878].push({true, 20}); list[878].valid = true; list[878].action = 0;
			list[879].push({true, 9}); list[879].push({true, 20}); list[879].valid = true; list[879].action = 0;
			list[880].push({true, 9}); list[880].push({true, 20}); list[880].valid = true; list[880].action = 0;
			list[881].push({true, 9}); list[881].push({true, 20}); list[881].valid = true; list[881].action = 0;
			list[916].push({false, 34}); list[916].push({false, 18}); list[916].push({true, 23});
			list[916].push({true, 23}); list[916].push({true, 22}); list[916].push({false, 19});
			list[916].valid = true; list[916].action = 0;
			list[917].push({false, 35}); list[917].push({false, 18}); list[917].push({true, 23});
			list[917].push({true, 23}); list[917].push({true, 22}); list[917].push({false, 19});
			list[917].valid = true; list[917].action = 0;
			list[918].push({false, 36}); list[918].push({false, 18}); list[918].push({true, 23});
			list[918].push({true, 23}); list[918].push({true, 22}); list[918].push({false, 19});
			list[918].valid = true; list[918].action = 0;
			list[927].push({true, 23}); list[927].push({true, 22}); list[927].valid = true; list[927].action = 0;
			list[943].valid = true; list[943].action = 0;
			list[945].push({true, 23}); list[945].push({true, 22}); list[945].valid = true; list[945].action = 0;
			list[946].push({true, 23}); list[946].push({true, 22}); list[946].valid = true; list[946].action = 0;
			list[948].push({true, 23}); list[948].push({true, 22}); list[948].valid = true; list[948].action = 0;
			list[949].push({true, 23}); list[949].push({true, 22}); list[949].valid = true; list[949].action = 0;
			list[969].push({false, 3}); list[969].valid = true; list[969].action = 25;
			list[987].push({false, 21}); list[987].valid = true; list[987].action = 26;
			list[988].push({false, 22}); list[988].valid = true; list[988].action = 27;
			list[990].push({false, 24}); list[990].valid = true; list[990].action = 28;
			list[991].push({false, 25}); list[991].valid = true; list[991].action = 29;
			list[1045].push({false, 37}); list[1045].push({true, 25}); list[1045].push({true, 42});
			list[1045].push({true, 37}); list[1045].valid = true; list[1045].action = 0;
			list[1046].push({false, 38}); list[1046].push({true, 25}); list[1046].push({true, 41});
			list[1046].push({true, 42}); list[1046].push({true, 39}); list[1046].valid = true; list[1046].action = 0;
			list[1047].push({false, 39}); list[1047].push({true, 26}); list[1047].push({true, 38});
			list[1047].push({true, 42}); list[1047].push({true, 39}); list[1047].valid = true; list[1047].action = 0;
			list[1048].push({false, 40}); list[1048].push({true, 25}); list[1048].push({true, 41});
			list[1048].push({true, 42}); list[1048].push({true, 39}); list[1048].valid = true; list[1048].action = 0;
			list[1049].push({false, 41}); list[1049].push({true, 25}); list[1049].push({true, 41});
			list[1049].push({true, 42}); list[1049].push({true, 39}); list[1049].valid = true; list[1049].action = 0;
			list[1068].push({false, 18}); list[1068].push({true, 27}); list[1068].push({false, 20});
			list[1068].push({true, 31}); list[1068].push({false, 20}); list[1068].push({true, 32});
			list[1068].push({false, 19}); list[1068].valid = true; list[1068].action = 0;
			list[1110].push({false, 18}); list[1110].push({true, 27}); list[1110].push({false, 20});
			list[1110].push({true, 30}); list[1110].push({false, 20}); list[1110].push({true, 31});
			list[1110].push({false, 20}); list[1110].push({true, 32}); list[1110].push({false, 19});
			list[1110].valid = true; list[1110].action = 0;
			list[1137].push({true, 29}); list[1137].push({true, 28}); list[1137].valid = true; list[1137].action = 0;
			list[1154].valid = true; list[1154].action = 0;
			list[1155].push({true, 29}); list[1155].push({true, 28}); list[1155].valid = true; list[1155].action = 0;
			list[1156].push({true, 29}); list[1156].push({true, 28}); list[1156].valid = true; list[1156].action = 0;
			list[1179].push({true, 29}); list[1179].push({true, 28}); list[1179].valid = true; list[1179].action = 0;
			list[1196].valid = true; list[1196].action = 0;
			list[1197].push({true, 29}); list[1197].push({true, 28}); list[1197].valid = true; list[1197].action = 0;
			list[1198].push({true, 29}); list[1198].push({true, 28}); list[1198].valid = true; list[1198].action = 0;
			list[1221].push({false, 3}); list[1221].valid = true; list[1221].action = 30;
			list[1239].push({false, 21}); list[1239].valid = true; list[1239].action = 31;
			list[1240].push({false, 22}); list[1240].valid = true; list[1240].action = 32;
			list[1263].push({true, 35}); list[1263].push({true, 33}); list[1263].valid = true; list[1263].action = 33;
			list[1305].push({true, 35}); list[1305].push({true, 33}); list[1305].valid = true; list[1305].action = 33;
			list[1322].valid = true; list[1322].action = 34;
			list[1347].push({true, 35}); list[1347].push({true, 33}); list[1347].valid = true; list[1347].action = 33;
			list[1363].valid = true; list[1363].action = 35;
			list[1389].push({true, 36}); list[1389].push({true, 34}); list[1389].valid = true; list[1389].action = 0;
			list[1405].valid = true; list[1405].action = 36;
			list[1406].valid = true; list[1406].action = 36;
			list[1407].push({true, 36}); list[1407].push({true, 34}); list[1407].valid = true; list[1407].action = 0;
			list[1408].push({true, 36}); list[1408].push({true, 34}); list[1408].valid = true; list[1408].action = 0;
			list[1431].push({true, 36}); list[1431].valid = true; list[1431].action = 0;
			list[1447].valid = true; list[1447].action = 37;
			list[1448].valid = true; list[1448].action = 37;
			list[1449].push({true, 36}); list[1449].valid = true; list[1449].action = 0;
			list[1450].push({true, 36}); list[1450].valid = true; list[1450].action = 0;
			list[1473].push({false, 3}); list[1473].valid = true; list[1473].action = 38;
			list[1515].push({false, 3}); list[1515].valid = true; list[1515].action = 38;
			list[1533].push({false, 21}); list[1533].valid = true; list[1533].action = 39;
			list[1534].push({false, 22}); list[1534].valid = true; list[1534].action = 40;
			list[1557].valid = true; list[1557].action = 41;
			list[1559].valid = true; list[1559].action = 41;
			list[1560].valid = true; list[1560].action = 41;
			list[1561].valid = true; list[1561].action = 41;
			list[1566].valid = true; list[1566].action = 41;
			list[1585].push({true, 38}); list[1585].push({true, 37}); list[1585].valid = true; list[1585].action = 0;
			list[1588].valid = true; list[1588].action = 41;
			list[1589].valid = true; list[1589].action = 41;
			list[1590].valid = true; list[1590].action = 41;
			list[1591].valid = true; list[1591].action = 41;
			list[1592].valid = true; list[1592].action = 41;
			list[1593].valid = true; list[1593].action = 41;
			list[1594].valid = true; list[1594].action = 41;
			list[1595].valid = true; list[1595].action = 41;
			list[1627].push({false, 31}); list[1627].push({false, 32}); list[1627].valid = true; list[1627].action = 42;
			list[1641].valid = true; list[1641].action = 41;
			list[1643].valid = true; list[1643].action = 41;
			list[1644].valid = true; list[1644].action = 41;
			list[1645].valid = true; list[1645].action = 41;
			list[1650].valid = true; list[1650].action = 41;
			list[1665].push({true, 40}); list[1665].push({true, 39}); list[1665].valid = true; list[1665].action = 0;
			list[1667].push({true, 40}); list[1667].push({true, 39}); list[1667].valid = true; list[1667].action = 0;
			list[1669].push({true, 40}); list[1669].push({true, 39}); list[1669].valid = true; list[1669].action = 0;
			list[1672].valid = true; list[1672].action = 41;
			list[1673].valid = true; list[1673].action = 41;
			list[1674].valid = true; list[1674].action = 41;
			list[1675].valid = true; list[1675].action = 41;
			list[1676].valid = true; list[1676].action = 41;
			list[1677].valid = true; list[1677].action = 41;
			list[1678].valid = true; list[1678].action = 41;
			list[1679].valid = true; list[1679].action = 41;
			list[1707].push({true, 41}); list[1707].valid = true; list[1707].action = 0;
			list[1709].push({true, 41}); list[1709].valid = true; list[1709].action = 0;
			list[1711].push({true, 38}); list[1711].valid = true; list[1711].action = 0;
			list[1749].push({true, 43}); list[1749].push({true, 45}); list[1749].push({true, 44});
			list[1749].valid = true; list[1749].action = 0;
			list[1751].push({true, 43}); list[1751].push({true, 45}); list[1751].push({true, 44});
			list[1751].valid = true; list[1751].action = 0;
			list[1791].push({true, 43}); list[1791].push({true, 45}); list[1791].push({false, 33});
			list[1791].push({true, 49}); list[1791].push({true, 44}); list[1791].valid = true; list[1791].action = 0;
			list[1793].push({true, 43}); list[1793].push({true, 45}); list[1793].push({false, 33});
			list[1793].push({true, 49}); list[1793].push({true, 44}); list[1793].valid = true; list[1793].action = 0;
			list[1833].push({false, 27}); list[1833].valid = true; list[1833].action = 43;
			list[1835].push({false, 29}); list[1835].valid = true; list[1835].action = 44;
			list[1876].push({false, 28}); list[1876].valid = true; list[1876].action = 45;
			list[1878].push({false, 30}); list[1878].valid = true; list[1878].action = 46;
			list[1893].push({true, 47}); list[1893].push({false, 20}); list[1893].push({true, 46});
			list[1893].valid = true; list[1893].action = 49;
			list[1913].push({true, 47}); list[1913].push({false, 20}); list[1913].push({true, 46});
			list[1913].valid = true; list[1913].action = 49;
			list[1914].push({false, 24}); list[1914].push({false, 20}); list[1914].push({false, 25});
			list[1914].valid = true; list[1914].action = 47;
			list[1915].push({false, 25}); list[1915].push({false, 20}); list[1915].push({false, 24});
			list[1915].valid = true; list[1915].action = 48;
			list[1918].valid = true; list[1918].action = 50;
			list[1920].valid = true; list[1920].action = 50;
			list[1923].valid = true; list[1923].action = 50;
			list[1935].push({true, 47}); list[1935].valid = true; list[1935].action = 0;
			list[1955].push({true, 47}); list[1955].valid = true; list[1955].action = 0;
			list[1958].push({false, 26}); list[1958].valid = true; list[1958].action = 51;
			list[1977].push({false, 3}); list[1977].valid = true; list[1977].action = 52;
			list[1997].push({false, 23}); list[1997].push({true, 48}); list[1997].valid = true; list[1997].action = 0;
			list[2019].push({false, 3}); list[2019].valid = true; list[2019].action = 53;
			list[2061].push({true, 51}); list[2061].push({false, 20}); list[2061].push({true, 50});
			list[2061].valid = true; list[2061].action = 0;
			list[2081].push({true, 51}); list[2081].push({false, 20}); list[2081].push({true, 50});
			list[2081].valid = true; list[2081].action = 0;
			list[2082].push({false, 24}); list[2082].push({false, 20}); list[2082].push({false, 25});
			list[2082].valid = true; list[2082].action = 54;
			list[2083].push({false, 25}); list[2083].push({false, 20}); list[2083].push({false, 24});
			list[2083].valid = true; list[2083].action = 55;
			list[2086].valid = true; list[2086].action = 56;
			list[2088].valid = true; list[2088].action = 56;
			list[2103].push({true, 51}); list[2103].valid = true; list[2103].action = 0;
			list[2123].push({true, 51}); list[2123].valid = true; list[2123].action = 0;
			list[2126].push({false, 26}); list[2126].valid = true; list[2126].action = 57;
			list[2145].push({false, 3}); list[2145].valid = true; list[2145].action = 58;
			list[2165].push({false, 23}); list[2165].push({true, 52}); list[2165].valid = true; list[2165].action = 0;
			list[2187].push({false, 3}); list[2187].valid = true; list[2187].action = 59;
		}

		nik_ce cprod_type & production(csymbol_type & row, ctoken_type col) const
			{ return list[row.token() * col_size + col]; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

