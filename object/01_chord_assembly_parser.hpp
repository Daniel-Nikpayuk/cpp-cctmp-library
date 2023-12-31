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
		nik_ces auto row_size		= 95;
		nik_ces auto col_size		= 43;

		nik_ces auto prod_size		= cctmp::string_literal("{C|A|M|P}").size(); // needs refining.

		nik_ces auto stack_finish	= symbol_type{generator::Sign::terminal, Token::prompt};
		nik_ces auto stack_start	= symbol_type{generator::Sign::nonterminal, start_index};

		nik_ces auto stack_size		= cctmp::literal("F{C|A|M|P}YPZ<>YPZYP,PZV;HGO").size(); // needs refining.
							// literal is intentional.
							// this is the longest possible sentential.
							// might need updating.

		using prod_type			= generator::Production<prod_size>;
		using cprod_type		= prod_type const;
		using list_type			= cctmp::sequence<prod_type, row_size * col_size>;

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
			list[131].valid = true; list[131].action = 1;
			list[138].push({true, 2}); list[138].push({true, 3}); list[138].valid = true; list[138].action = 0;
			list[175].push({true, 6}); list[175].push({true, 5}); list[175].valid = true; list[175].action = 0;
			list[177].push({true, 6}); list[177].push({true, 5}); list[177].valid = true; list[177].action = 0;
			list[182].push({true, 13}); list[182].push({true, 39}); list[182].push({true, 14});
			list[182].valid = true; list[182].action = 0;
			list[185].push({true, 6}); list[185].push({true, 5}); list[185].valid = true; list[185].action = 0;
			list[187].push({true, 6}); list[187].push({true, 5}); list[187].valid = true; list[187].action = 0;
			list[189].push({true, 6}); list[189].push({true, 5}); list[189].valid = true; list[189].action = 0;
			list[217].valid = true; list[217].action = 0;
			list[218].push({true, 6}); list[218].push({true, 5}); list[218].valid = true; list[218].action = 0;
			list[220].push({true, 6}); list[220].push({true, 5}); list[220].valid = true; list[220].action = 0;
			list[224].valid = true; list[224].action = 0;
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
			list[347].push({false, 3}); list[347].valid = true; list[347].action = 2;
			list[390].push({false, 3}); list[390].valid = true; list[390].action = 3;
			list[438].push({false, 8}); list[438].valid = true; list[438].action = 4;
			list[482].push({false, 9}); list[482].valid = true; list[482].action = 5;
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
			list[1715].push({true, 56}); list[1715].valid = true; list[1715].action = 40;
			list[1716].push({true, 56}); list[1716].valid = true; list[1716].action = 40;
			list[1717].push({true, 56}); list[1717].valid = true; list[1717].action = 40;
			list[1718].push({true, 56}); list[1718].valid = true; list[1718].action = 40;
			list[1719].push({true, 56}); list[1719].valid = true; list[1719].action = 40;
			list[1755].push({false, 35}); list[1755].push({true, 41}); list[1755].push({true, 46});
			list[1755].push({true, 43}); list[1755].push({true, 44}); list[1755].push({true, 47});
			list[1755].valid = true; list[1755].action = 0;
			list[1756].push({false, 36}); list[1756].push({true, 41}); list[1756].push({true, 50});
			list[1756].push({true, 43}); list[1756].push({true, 48}); list[1756].push({true, 51});
			list[1756].valid = true; list[1756].action = 0;
			list[1757].push({false, 37}); list[1757].push({true, 41}); list[1757].push({true, 54});
			list[1757].push({true, 43}); list[1757].push({true, 52}); list[1757].push({true, 55});
			list[1757].valid = true; list[1757].action = 0;
			list[1782].valid = true; list[1782].action = 41;
			list[1791].push({false, 28}); list[1791].push({true, 42}); list[1791].push({false, 29});
			list[1791].valid = true; list[1791].action = 0;
			list[1810].push({false, 4}); list[1810].valid = true; list[1810].action = 42;
			list[1852].push({false, 3}); list[1852].valid = true; list[1852].action = 43;
			list[1871].push({false, 22}); list[1871].valid = true; list[1871].action = 44;
			list[1872].push({false, 23}); list[1872].valid = true; list[1872].action = 45;
			list[1874].push({false, 25}); list[1874].valid = true; list[1874].action = 46;
			list[1875].push({false, 26}); list[1875].valid = true; list[1875].action = 47;
			list[1896].push({true, 45}); list[1896].push({true, 44}); list[1896].valid = true; list[1896].action = 0;
			list[1912].valid = true; list[1912].action = 0;
			list[1939].push({false, 4}); list[1939].valid = true; list[1939].action = 50;
			list[1997].push({false, 19}); list[1997].valid = true; list[1997].action = 48;
			list[2041].push({false, 20}); list[2041].valid = true; list[2041].action = 49;
			list[2067].push({true, 49}); list[2067].push({true, 48}); list[2067].valid = true; list[2067].action = 0;
			list[2084].valid = true; list[2084].action = 0;
			list[2086].push({true, 49}); list[2086].push({true, 48}); list[2086].valid = true; list[2086].action = 0;
			list[2087].push({true, 49}); list[2087].push({true, 48}); list[2087].valid = true; list[2087].action = 0;
			list[2089].push({true, 49}); list[2089].push({true, 48}); list[2089].valid = true; list[2089].action = 0;
			list[2090].push({true, 49}); list[2090].push({true, 48}); list[2090].valid = true; list[2090].action = 0;
			list[2110].push({false, 3}); list[2110].valid = true; list[2110].action = 53;
			list[2129].push({false, 22}); list[2129].valid = true; list[2129].action = 54;
			list[2130].push({false, 23}); list[2130].valid = true; list[2130].action = 55;
			list[2132].push({false, 25}); list[2132].valid = true; list[2132].action = 56;
			list[2133].push({false, 26}); list[2133].valid = true; list[2133].action = 57;
			list[2169].push({false, 19}); list[2169].valid = true; list[2169].action = 51;
			list[2213].push({false, 20}); list[2213].valid = true; list[2213].action = 52;
			list[2239].push({true, 53}); list[2239].push({true, 52}); list[2239].valid = true; list[2239].action = 0;
			list[2256].valid = true; list[2256].action = 0;
			list[2282].push({false, 3}); list[2282].valid = true; list[2282].action = 60;
			list[2341].push({false, 19}); list[2341].valid = true; list[2341].action = 58;
			list[2385].push({false, 20}); list[2385].valid = true; list[2385].action = 59;
			list[2446].push({false, 38}); list[2446].push({true, 41}); list[2446].push({true, 58});
			list[2446].push({true, 77}); list[2446].push({true, 90}); list[2446].valid = true; list[2446].action = 0;
			list[2447].push({false, 39}); list[2447].push({true, 41}); list[2447].push({true, 58});
			list[2447].push({true, 76}); list[2447].push({true, 77}); list[2447].push({true, 91});
			list[2447].valid = true; list[2447].action = 0;
			list[2448].push({false, 40}); list[2448].push({true, 41}); list[2448].push({true, 57});
			list[2448].push({true, 80}); list[2448].push({true, 77}); list[2448].push({true, 92});
			list[2448].valid = true; list[2448].action = 0;
			list[2449].push({false, 41}); list[2449].push({true, 41}); list[2449].push({true, 58});
			list[2449].push({true, 76}); list[2449].push({true, 77}); list[2449].push({true, 93});
			list[2449].valid = true; list[2449].action = 0;
			list[2450].push({false, 42}); list[2450].push({true, 41}); list[2450].push({true, 58});
			list[2450].push({true, 76}); list[2450].push({true, 77}); list[2450].push({true, 94});
			list[2450].valid = true; list[2450].action = 0;
			list[2470].push({true, 60}); list[2470].push({true, 64}); list[2470].push({true, 59});
			list[2470].push({true, 67}); list[2470].push({true, 59}); list[2470].push({true, 70});
			list[2470].push({true, 59}); list[2470].push({true, 73}); list[2470].push({true, 61});
			list[2470].valid = true; list[2470].action = 0;
			list[2513].push({true, 60}); list[2513].push({true, 67}); list[2513].push({true, 59});
			list[2513].push({true, 70}); list[2513].push({true, 59}); list[2513].push({true, 73});
			list[2513].push({true, 61}); list[2513].valid = true; list[2513].action = 61;
			list[2558].push({false, 21}); list[2558].valid = true; list[2558].action = 62;
			list[2599].push({false, 19}); list[2599].valid = true; list[2599].action = 63;
			list[2643].push({false, 20}); list[2643].valid = true; list[2643].action = 64;
			list[2669].push({false, 3}); list[2669].valid = true; list[2669].action = 65;
			list[2712].push({false, 3}); list[2712].valid = true; list[2712].action = 66;
			list[2731].push({false, 22}); list[2731].valid = true; list[2731].action = 67;
			list[2732].push({false, 23}); list[2732].valid = true; list[2732].action = 68;
			list[2755].push({true, 62}); list[2755].push({true, 65}); list[2755].valid = true; list[2755].action = 0;
			list[2798].push({true, 63}); list[2798].push({true, 66}); list[2798].valid = true; list[2798].action = 0;
			list[2816].valid = true; list[2816].action = 69;
			list[2817].push({true, 63}); list[2817].push({true, 66}); list[2817].valid = true; list[2817].action = 0;
			list[2818].push({true, 63}); list[2818].push({true, 66}); list[2818].valid = true; list[2818].action = 0;
			list[2841].push({true, 63}); list[2841].valid = true; list[2841].action = 0;
			list[2859].valid = true; list[2859].action = 70;
			list[2860].push({true, 63}); list[2860].valid = true; list[2860].action = 0;
			list[2861].push({true, 63}); list[2861].valid = true; list[2861].action = 0;
			list[2884].push({true, 69}); list[2884].push({true, 68}); list[2884].valid = true; list[2884].action = 0;
			list[2902].valid = true; list[2902].action = 71;
			list[2903].push({true, 69}); list[2903].push({true, 68}); list[2903].valid = true; list[2903].action = 0;
			list[2904].push({true, 69}); list[2904].push({true, 68}); list[2904].valid = true; list[2904].action = 0;
			list[2927].push({true, 63}); list[2927].push({true, 68}); list[2927].valid = true; list[2927].action = 0;
			list[2945].valid = true; list[2945].action = 72;
			list[2946].push({true, 63}); list[2946].push({true, 68}); list[2946].valid = true; list[2946].action = 0;
			list[2947].push({true, 63}); list[2947].push({true, 68}); list[2947].valid = true; list[2947].action = 0;
			list[2970].push({false, 3}); list[2970].valid = true; list[2970].action = 73;
			list[2989].push({false, 22}); list[2989].valid = true; list[2989].action = 74;
			list[2990].push({false, 23}); list[2990].valid = true; list[2990].action = 75;
			list[3013].push({true, 62}); list[3013].push({true, 71}); list[3013].valid = true; list[3013].action = 0;
			list[3031].valid = true; list[3031].action = 76;
			list[3056].push({true, 63}); list[3056].push({true, 72}); list[3056].valid = true; list[3056].action = 0;
			list[3074].valid = true; list[3074].action = 77;
			list[3075].push({true, 63}); list[3075].push({true, 72}); list[3075].valid = true; list[3075].action = 0;
			list[3076].push({true, 63}); list[3076].push({true, 72}); list[3076].valid = true; list[3076].action = 0;
			list[3099].push({true, 63}); list[3099].valid = true; list[3099].action = 0;
			list[3117].valid = true; list[3117].action = 78;
			list[3118].push({true, 63}); list[3118].valid = true; list[3118].action = 0;
			list[3119].push({true, 63}); list[3119].valid = true; list[3119].action = 0;
			list[3142].push({true, 62}); list[3142].push({true, 74}); list[3142].valid = true; list[3142].action = 0;
			list[3159].valid = true; list[3159].action = 79;
			list[3185].push({true, 63}); list[3185].push({true, 75}); list[3185].valid = true; list[3185].action = 0;
			list[3202].valid = true; list[3202].action = 80;
			list[3204].push({true, 63}); list[3204].push({true, 75}); list[3204].valid = true; list[3204].action = 0;
			list[3205].push({true, 63}); list[3205].push({true, 75}); list[3205].valid = true; list[3205].action = 0;
			list[3228].push({true, 63}); list[3228].valid = true; list[3228].action = 0;
			list[3245].valid = true; list[3245].action = 81;
			list[3247].push({true, 63}); list[3247].valid = true; list[3247].action = 0;
			list[3248].push({true, 63}); list[3248].valid = true; list[3248].action = 0;
			list[3296].push({true, 78}); list[3296].push({true, 82}); list[3296].push({true, 79});
			list[3296].valid = true; list[3296].action = 0;
			list[3298].push({true, 78}); list[3298].push({true, 82}); list[3298].push({true, 79});
			list[3298].valid = true; list[3298].action = 0;
			list[3339].push({true, 78}); list[3339].push({true, 82}); list[3339].push({false, 34});
			list[3339].push({true, 86}); list[3339].push({true, 79}); list[3339].valid = true; list[3339].action = 0;
			list[3341].push({true, 78}); list[3341].push({true, 82}); list[3341].push({false, 34});
			list[3341].push({true, 86}); list[3341].push({true, 79}); list[3341].valid = true; list[3341].action = 0;
			list[3382].push({false, 28}); list[3382].valid = true; list[3382].action = 82;
			list[3384].push({false, 30}); list[3384].valid = true; list[3384].action = 83;
			list[3426].push({false, 29}); list[3426].valid = true; list[3426].action = 84;
			list[3428].push({false, 31}); list[3428].valid = true; list[3428].action = 85;
			list[3472].push({false, 32}); list[3472].push({false, 33}); list[3472].valid = true; list[3472].action = 86;
			list[3511].push({true, 76}); list[3511].valid = true; list[3511].action = 0;
			list[3513].push({true, 76}); list[3513].valid = true; list[3513].action = 0;
			list[3515].push({true, 80}); list[3515].valid = true; list[3515].action = 0;
			list[3529].push({true, 84}); list[3529].push({false, 21}); list[3529].push({true, 83});
			list[3529].valid = true; list[3529].action = 89;
			list[3550].push({true, 84}); list[3550].push({false, 21}); list[3550].push({true, 83});
			list[3550].valid = true; list[3550].action = 89;
			list[3551].push({false, 25}); list[3551].push({false, 21}); list[3551].push({false, 26});
			list[3551].valid = true; list[3551].action = 87;
			list[3552].push({false, 26}); list[3552].push({false, 21}); list[3552].push({false, 25});
			list[3552].valid = true; list[3552].action = 88;
			list[3555].valid = true; list[3555].action = 90;
			list[3557].valid = true; list[3557].action = 90;
			list[3560].valid = true; list[3560].action = 90;
			list[3572].push({true, 84}); list[3572].valid = true; list[3572].action = 0;
			list[3593].push({true, 84}); list[3593].valid = true; list[3593].action = 0;
			list[3596].push({false, 27}); list[3596].valid = true; list[3596].action = 91;
			list[3615].push({false, 3}); list[3615].valid = true; list[3615].action = 92;
			list[3636].push({false, 24}); list[3636].push({true, 85}); list[3636].valid = true; list[3636].action = 0;
			list[3658].push({false, 3}); list[3658].valid = true; list[3658].action = 93;
			list[3701].push({true, 88}); list[3701].push({false, 21}); list[3701].push({true, 87});
			list[3701].valid = true; list[3701].action = 0;
			list[3722].push({true, 88}); list[3722].push({false, 21}); list[3722].push({true, 87});
			list[3722].valid = true; list[3722].action = 0;
			list[3723].push({false, 25}); list[3723].push({false, 21}); list[3723].push({false, 26});
			list[3723].valid = true; list[3723].action = 94;
			list[3724].push({false, 26}); list[3724].push({false, 21}); list[3724].push({false, 25});
			list[3724].valid = true; list[3724].action = 95;
			list[3727].valid = true; list[3727].action = 96;
			list[3729].valid = true; list[3729].action = 96;
			list[3744].push({true, 88}); list[3744].valid = true; list[3744].action = 0;
			list[3765].push({true, 88}); list[3765].valid = true; list[3765].action = 0;
			list[3768].push({false, 27}); list[3768].valid = true; list[3768].action = 97;
			list[3787].push({false, 3}); list[3787].valid = true; list[3787].action = 98;
			list[3808].push({false, 24}); list[3808].push({true, 89}); list[3808].valid = true; list[3808].action = 0;
			list[3830].push({false, 3}); list[3830].valid = true; list[3830].action = 99;
			list[3878].valid = true; list[3878].action = 100;
			list[3902].push({true, 80}); list[3902].push({true, 90}); list[3902].valid = true; list[3902].action = 0;
			list[3921].valid = true; list[3921].action = 101;
			list[3941].push({true, 81}); list[3941].push({true, 91}); list[3941].valid = true; list[3941].action = 0;
			list[3943].push({true, 81}); list[3943].push({true, 91}); list[3943].valid = true; list[3943].action = 0;
			list[3945].push({true, 81}); list[3945].push({true, 91}); list[3945].valid = true; list[3945].action = 0;
			list[3964].valid = true; list[3964].action = 102;
			list[3984].push({true, 81}); list[3984].push({true, 92}); list[3984].valid = true; list[3984].action = 0;
			list[3986].push({true, 81}); list[3986].push({true, 92}); list[3986].valid = true; list[3986].action = 0;
			list[3988].push({true, 81}); list[3988].push({true, 92}); list[3988].valid = true; list[3988].action = 0;
			list[4007].valid = true; list[4007].action = 103;
			list[4027].push({true, 81}); list[4027].push({true, 93}); list[4027].valid = true; list[4027].action = 0;
			list[4029].push({true, 81}); list[4029].push({true, 93}); list[4029].valid = true; list[4029].action = 0;
			list[4031].push({true, 81}); list[4031].push({true, 93}); list[4031].valid = true; list[4031].action = 0;
			list[4050].valid = true; list[4050].action = 104;
			list[4070].push({true, 81}); list[4070].push({true, 94}); list[4070].valid = true; list[4070].action = 0;
			list[4072].push({true, 81}); list[4072].push({true, 94}); list[4072].valid = true; list[4072].action = 0;
			list[4074].push({true, 81}); list[4074].push({true, 94}); list[4074].valid = true; list[4074].action = 0;
		}

		nik_ce cprod_type & production(csymbol_type & row, ctoken_type col) const
			{ return list[row.token() * col_size + col]; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

