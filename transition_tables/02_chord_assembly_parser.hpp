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

		nik_ces auto start_index	= 0;
		nik_ces auto row_size		= 55;
		nik_ces auto col_size		= 43;

		nik_ces auto prod_size		= 8;//cctmp::string_literal("<A|C|M|L>").size(); // needs refining.

		nik_ces auto stack_finish	= symbol_type{generator::Sign::terminal, Token::prompt};
		nik_ces auto stack_start	= symbol_type{generator::Sign::nonterminal, start_index};

		nik_ces auto stack_size		= cctmp::literal("F<A|C|M|L>YPZ{}YPZYP,PZV;HGO").size(); // needs refining.
							// literal is intentional.
							// this is the longest possible sentential.

		using prod_type				= generator::Production<prod_size>;
		using cprod_type			= prod_type const;
		using list_type				= cctmp::sequence<prod_type, row_size * col_size>;

		list_type list; // list instead of table due to clang bug.
		bool ambiguous;

		nik_ce T_chord_assembly_pda() : ambiguous{}
		{
			list.fullsize();

			list[3].push({true, 8}); list[3].push({true, 1}); list[3].push({true, 10});
			list[3].push({true, 2}); list[3].push({true, 3}); list[3].valid = true; list[3].action = 0;
			list[46].push({true, 9}); list[46].push({true, 1}); list[46].valid = true; list[46].action = 0;
			list[51].valid = true; list[51].action = 0;
			list[95].push({true, 11}); list[95].push({true, 12}); list[95].push({true, 4});
			list[95].valid = true; list[95].action = 0;
			list[131].valid = true; list[131].action = 0;
			list[138].push({true, 2}); list[138].push({true, 3}); list[138].valid = true; list[138].action = 0;
			list[175].push({true, 6}); list[175].push({true, 5}); list[175].valid = true; list[175].action = 0;
			list[177].push({true, 6}); list[177].push({true, 5}); list[177].valid = true; list[177].action = 0;
			list[182].push({true, 13}); list[182].push({true, 39}); list[182].push({true, 14});
			list[182].valid = true; list[182].action = 0;
			list[185].push({true, 6}); list[185].push({true, 5}); list[185].valid = true; list[185].action = 0;
			list[187].push({true, 6}); list[187].push({true, 5}); list[187].valid = true; list[187].action = 0;
			list[189].push({true, 6}); list[189].push({true, 5}); list[189].valid = true; list[189].action = 0;
			list[217].valid = true; list[217].action = 5;
			list[218].push({true, 6}); list[218].push({true, 5}); list[218].valid = true; list[218].action = 0;
			list[220].push({true, 6}); list[220].push({true, 5}); list[220].valid = true; list[220].action = 0;
			list[224].valid = true; list[224].action = 5;
			list[225].push({true, 13}); list[225].push({true, 39}); list[225].push({true, 14});
			list[225].valid = true; list[225].action = 0;
			list[226].push({true, 15}); list[226].push({true, 16}); list[226].push({true, 17});
			list[226].valid = true; list[226].action = 0;
			list[227].push({true, 18}); list[227].push({true, 19}); list[227].push({true, 20});
			list[227].valid = true; list[227].action = 0;
			list[228].push({true, 6}); list[228].push({true, 5}); list[228].valid = true; list[228].action = 0;
			list[230].push({true, 6}); list[230].push({true, 5}); list[230].valid = true; list[230].action = 0;
			list[232].push({true, 6}); list[232].push({true, 5}); list[232].valid = true; list[232].action = 0;
			list[261].push({true, 21}); list[261].push({true, 7}); list[261].valid = true; list[261].action = 0;
			list[263].push({true, 21}); list[263].push({true, 7}); list[263].valid = true; list[263].action = 0;
			list[271].push({false, 13}); list[271].push({true, 22}); list[271].push({false, 14});
			list[271].push({true, 35}); list[271].push({true, 36}); list[271].push({true, 23});
			list[271].valid = true; list[271].action = 0;
			list[273].push({true, 24}); list[273].push({true, 35}); list[273].push({true, 36});
			list[273].push({true, 25}); list[273].push({true, 26}); list[273].push({true, 27});
			list[273].push({true, 28}); list[273].valid = true; list[273].action = 0;
			list[275].push({true, 29}); list[275].push({true, 35}); list[275].push({true, 36});
			list[275].push({true, 30}); list[275].valid = true; list[275].action = 0;
			list[315].push({true, 31}); list[315].push({true, 35}); list[315].push({true, 36});
			list[315].push({true, 32}); list[315].valid = true; list[315].action = 0;
			list[319].push({true, 33}); list[319].push({true, 39}); list[319].push({true, 34});
			list[319].valid = true; list[319].action = 0;
			list[347].push({false, 3}); list[347].valid = true; list[347].action = 1;
			list[390].push({false, 3}); list[390].valid = true; list[390].action = 2;
			list[438].push({false, 8}); list[438].valid = true; list[438].action = 3;
			list[482].push({false, 9}); list[482].valid = true; list[482].action = 4;
			list[524].push({false, 8}); list[524].valid = true; list[524].action = 0;
			list[569].push({false, 10}); list[569].valid = true; list[569].action = 6;
			list[610].push({false, 8}); list[610].valid = true; list[610].action = 7;
			list[656].push({false, 11}); list[656].valid = true; list[656].action = 8;
			list[691].push({false, 3}); list[691].valid = true; list[691].action = 9;
			list[739].push({false, 8}); list[739].valid = true; list[739].action = 10;
			list[786].push({false, 12}); list[786].valid = true; list[786].action = 11;
			list[820].push({false, 3}); list[820].valid = true; list[820].action = 12;
			list[868].push({false, 8}); list[868].valid = true; list[868].action = 13;
			list[906].push({false, 3}); list[906].valid = true; list[906].action = 14;
			list[908].push({false, 5}); list[908].valid = true; list[908].action = 15;
			list[949].push({false, 3}); list[949].valid = true; list[949].action = 16;
			list[997].push({false, 8}); list[997].valid = true; list[997].action = 17;
			list[1047].push({false, 15}); list[1047].valid = true; list[1047].action = 18;
			list[1083].push({false, 8}); list[1083].valid = true; list[1083].action = 19;
			list[1134].push({false, 16}); list[1134].valid = true; list[1134].action = 20;
			list[1164].push({false, 3}); list[1164].valid = true; list[1164].action = 21;
			list[1212].push({false, 8}); list[1212].valid = true; list[1212].action = 22;
			list[1264].push({false, 17}); list[1264].valid = true; list[1264].action = 23;
			list[1298].push({false, 8}); list[1298].valid = true; list[1298].action = 24;
			list[1347].push({false, 14}); list[1347].valid = true; list[1347].action = 27;
			list[1384].push({false, 8}); list[1384].valid = true; list[1384].action = 28;
			list[1437].push({false, 18}); list[1437].valid = true; list[1437].action = 25;
			list[1470].push({false, 8}); list[1470].valid = true; list[1470].action = 26;
			list[1508].push({false, 3}); list[1508].valid = true; list[1508].action = 29;
			list[1511].push({false, 6}); list[1511].valid = true; list[1511].action = 30;
			list[1512].push({false, 7}); list[1512].valid = true; list[1512].action = 31;
			list[1551].push({true, 37}); list[1551].push({true, 36}); list[1551].valid = true; list[1551].action = 0;
			list[1554].push({true, 37}); list[1554].push({true, 36}); list[1554].valid = true; list[1554].action = 0;
			list[1555].push({true, 37}); list[1555].push({true, 36}); list[1555].valid = true; list[1555].action = 0;
			list[1556].valid = true; list[1556].action = 0;
			list[1561].push({false, 13}); list[1561].push({true, 38}); list[1561].push({true, 36});
			list[1561].valid = true; list[1561].action = 0;
			list[1594].push({false, 3}); list[1594].valid = true; list[1594].action = 32;
			list[1597].push({false, 6}); list[1597].valid = true; list[1597].action = 33;
			list[1598].push({false, 7}); list[1598].valid = true; list[1598].action = 34;
			list[1637].push({false, 3}); list[1637].valid = true; list[1637].action = 35;
			list[1680].push({false, 3}); list[1680].valid = true; list[1680].action = 36;
			list[1683].push({false, 6}); list[1683].valid = true; list[1683].action = 37;
			list[1684].push({false, 7}); list[1684].valid = true; list[1684].action = 38;
			list[1712].push({true, 40}); list[1712].valid = true; list[1712].action = 39;
			list[1713].push({true, 40}); list[1713].valid = true; list[1713].action = 39;
			list[1714].push({true, 40}); list[1714].valid = true; list[1714].action = 39;
			list[1755].push({false, 35}); list[1755].push({false, 28}); list[1755].push({true, 41});
			list[1755].push({false, 29}); list[1755].push({true, 43}); list[1755].push({true, 42});
			list[1755].push({true, 45}); list[1755].push({true, 44}); list[1755].valid = true; list[1755].action = 0;
			list[1756].push({false, 36}); list[1756].push({false, 28}); list[1756].push({true, 41});
			list[1756].push({false, 29}); list[1756].push({true, 47}); list[1756].push({true, 42});
			list[1756].push({true, 49}); list[1756].push({true, 48}); list[1756].valid = true; list[1756].action = 0;
			list[1757].push({false, 37}); list[1757].push({false, 28}); list[1757].push({true, 41});
			list[1757].push({false, 29}); list[1757].push({true, 51}); list[1757].push({true, 42});
			list[1757].push({true, 53}); list[1757].push({true, 52}); list[1757].valid = true; list[1757].action = 0;
			list[1767].push({false, 4}); list[1767].valid = true; list[1767].action = 41;
			list[1809].push({false, 3}); list[1809].valid = true; list[1809].action = 42;
			list[1828].push({false, 22}); list[1828].valid = true; list[1828].action = 43;
			list[1829].push({false, 23}); list[1829].valid = true; list[1829].action = 44;
			list[1831].push({false, 25}); list[1831].valid = true; list[1831].action = 45;
			list[1832].push({false, 26}); list[1832].valid = true; list[1832].action = 46;
			list[1881].push({false, 32}); list[1881].valid = true; list[1881].action = 47;
			list[1925].push({false, 33}); list[1925].valid = true; list[1925].action = 48;
			list[1939].push({true, 46}); list[1939].push({true, 45}); list[1939].valid = true; list[1939].action = 0;
			list[1968].valid = true; list[1968].action = 0;
			list[1982].push({false, 4}); list[1982].valid = true; list[1982].action = 49;
			list[2053].push({false, 32}); list[2053].valid = true; list[2053].action = 50;
			list[2097].push({false, 33}); list[2097].valid = true; list[2097].action = 51;
			list[2110].push({true, 50}); list[2110].push({true, 49}); list[2110].valid = true; list[2110].action = 0;
			list[2129].push({true, 50}); list[2129].push({true, 49}); list[2129].valid = true; list[2129].action = 0;
			list[2130].push({true, 50}); list[2130].push({true, 49}); list[2130].valid = true; list[2130].action = 0;
			list[2132].push({true, 50}); list[2132].push({true, 49}); list[2132].valid = true; list[2132].action = 0;
			list[2133].push({true, 50}); list[2133].push({true, 49}); list[2133].valid = true; list[2133].action = 0;
			list[2140].valid = true; list[2140].action = 0;
			list[2153].push({false, 3}); list[2153].valid = true; list[2153].action = 52;
			list[2172].push({false, 22}); list[2172].valid = true; list[2172].action = 53;
			list[2173].push({false, 23}); list[2173].valid = true; list[2173].action = 54;
			list[2175].push({false, 25}); list[2175].valid = true; list[2175].action = 55;
			list[2176].push({false, 26}); list[2176].valid = true; list[2176].action = 56;
			list[2225].push({false, 32}); list[2225].valid = true; list[2225].action = 57;
			list[2269].push({false, 33}); list[2269].valid = true; list[2269].action = 58;
			list[2282].push({true, 54}); list[2282].push({true, 53}); list[2282].valid = true; list[2282].action = 0;
			list[2312].valid = true; list[2312].action = 0;
			list[2325].push({false, 3}); list[2325].valid = true; list[2325].action = 59;
		}

		nik_ce cprod_type & production(csymbol_type & row, ctoken_type col) const
			{ return list[row.token() * col_size + col]; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

