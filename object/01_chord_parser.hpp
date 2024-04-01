/************************************************************************************************************************
**
** Copyright 2022-2024 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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
	struct T_chord_pda
	{
		using ActName			= typename T_grammar::ActName;
		using T_lexer			= typename T_grammar::T_lexer;
		using Token			= typename T_grammar::Token;

		nik_ces auto start_index	= 0;
		nik_ces auto row_size		= 112;
		nik_ces auto col_size		= 48;

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

		nik_ce T_chord_pda() : ambiguous{}
		{
			list.fullsize();

			list[5].push({false, 5}); list[5].push({true, 2}); list[5].push({true, 1});
			list[5].push({false, 14}); list[5].push({true, 3}); list[5].push({true, 11});
			list[5].valid = true; list[5].action = 0;
			list[6].push({true, 3}); list[6].push({true, 11}); list[6].valid = true; list[6].action = 0;
			list[54].push({true, 2}); list[54].push({true, 1}); list[54].valid = true; list[54].action = 0;
			list[62].valid = true; list[62].action = 0;
			list[102].push({false, 6}); list[102].valid = true; list[102].action = 1;
			list[150].push({true, 4}); list[150].push({true, 6}); list[150].push({true, 9});
			list[150].push({true, 5}); list[150].valid = true; list[150].action = 0;
			list[198].push({false, 6}); list[198].valid = true; list[198].action = 2;
			list[254].push({false, 14}); list[254].valid = true; list[254].action = 0;
			list[291].valid = true; list[291].action = 0;
			list[294].push({true, 7}); list[294].push({true, 6}); list[294].valid = true; list[294].action = 0;
			list[302].valid = true; list[302].action = 0;
			list[342].push({false, 6}); list[342].valid = true; list[342].action = 5;
			list[398].push({false, 14}); list[398].valid = true; list[398].action = 6;
			list[435].push({false, 3}); list[435].push({true, 10}); list[435].valid = true; list[435].action = 0;
			list[446].valid = true; list[446].action = 0;
			list[486].push({false, 6}); list[486].valid = true; list[486].action = 7;
			list[543].push({true, 12}); list[543].push({true, 13}); list[543].valid = true; list[543].action = 3;
			list[591].push({true, 14}); list[591].push({true, 15}); list[591].push({true, 16});
			list[591].valid = true; list[591].action = 0;
			list[626].valid = true; list[626].action = 4;
			list[639].push({true, 12}); list[639].push({true, 13}); list[639].valid = true; list[639].action = 0;
			list[687].push({false, 15}); list[687].valid = true; list[687].action = 10;
			list[734].push({false, 14}); list[734].valid = true; list[734].action = 0;
			list[774].push({true, 18}); list[774].push({true, 17}); list[774].valid = true; list[774].action = 0;
			list[777].push({true, 18}); list[777].push({true, 17}); list[777].valid = true; list[777].action = 0;
			list[778].push({true, 18}); list[778].push({true, 17}); list[778].valid = true; list[778].action = 0;
			list[779].push({true, 18}); list[779].push({true, 17}); list[779].valid = true; list[779].action = 0;
			list[784].push({false, 16}); list[784].push({true, 52}); list[784].push({true, 8});
			list[784].valid = true; list[784].action = 0;
			list[786].push({true, 18}); list[786].push({true, 17}); list[786].valid = true; list[786].action = 0;
			list[788].push({true, 18}); list[788].push({true, 17}); list[788].valid = true; list[788].action = 0;
			list[790].push({true, 18}); list[790].push({true, 17}); list[790].valid = true; list[790].action = 0;
			list[818].valid = true; list[818].action = 0;
			list[822].push({true, 18}); list[822].push({true, 17}); list[822].valid = true; list[822].action = 0;
			list[825].push({true, 18}); list[825].push({true, 17}); list[825].valid = true; list[825].action = 0;
			list[826].push({true, 18}); list[826].push({true, 17}); list[826].valid = true; list[826].action = 0;
			list[827].push({true, 18}); list[827].push({true, 17}); list[827].valid = true; list[827].action = 0;
			list[831].valid = true; list[831].action = 0;
			list[832].push({false, 16}); list[832].push({true, 52}); list[832].push({true, 8});
			list[832].valid = true; list[832].action = 0;
			list[833].push({true, 23}); list[833].push({true, 24}); list[833].push({true, 25});
			list[833].valid = true; list[833].action = 0;
			list[834].push({true, 18}); list[834].push({true, 17}); list[834].valid = true; list[834].action = 0;
			list[836].push({true, 18}); list[836].push({true, 17}); list[836].valid = true; list[836].action = 0;
			list[838].push({true, 18}); list[838].push({true, 17}); list[838].valid = true; list[838].action = 0;
			list[870].push({true, 19}); list[870].push({true, 20}); list[870].valid = true; list[870].action = 0;
			list[873].push({true, 29}); list[873].push({true, 31}); list[873].push({true, 30});
			list[873].push({true, 32}); list[873].valid = true; list[873].action = 0;
			list[874].push({true, 33}); list[874].push({true, 35}); list[874].push({true, 34});
			list[874].push({true, 36}); list[874].valid = true; list[874].action = 0;
			list[875].push({true, 19}); list[875].push({true, 20}); list[875].valid = true; list[875].action = 0;
			list[882].push({false, 18}); list[882].push({true, 37}); list[882].push({false, 19});
			list[882].push({true, 48}); list[882].push({true, 38}); list[882].push({true, 49});
			list[882].push({true, 39}); list[882].valid = true; list[882].action = 0;
			list[884].push({true, 21}); list[884].push({true, 22}); list[884].valid = true; list[884].action = 0;
			list[886].push({true, 40}); list[886].push({true, 48}); list[886].push({true, 49});
			list[886].push({true, 41}); list[886].valid = true; list[886].action = 0;
			list[918].push({false, 6}); list[918].valid = true; list[918].action = 17;
			list[923].push({false, 11}); list[923].valid = true; list[923].action = 18;
			list[979].push({true, 42}); list[979].push({true, 48}); list[979].push({true, 49});
			list[979].push({true, 43}); list[979].valid = true; list[979].action = 0;
			list[983].push({true, 46}); list[983].push({true, 52}); list[983].push({true, 47});
			list[983].valid = true; list[983].action = 0;
			list[1028].push({true, 44}); list[1028].push({true, 48}); list[1028].push({true, 49});
			list[1028].push({true, 45}); list[1028].valid = true; list[1028].action = 0;
			list[1077].push({true, 26}); list[1077].push({true, 27}); list[1077].push({true, 28});
			list[1077].valid = true; list[1077].action = 0;
			list[1121].push({false, 17}); list[1121].valid = true; list[1121].action = 0;
			list[1158].push({false, 6}); list[1158].valid = true; list[1158].action = 11;
			list[1214].push({false, 14}); list[1214].valid = true; list[1214].action = 0;
			list[1269].push({false, 21}); list[1269].valid = true; list[1269].action = 0;
			list[1302].push({false, 6}); list[1302].valid = true; list[1302].action = 12;
			list[1358].push({false, 14}); list[1358].valid = true; list[1358].action = 0;
			list[1401].push({false, 9}); list[1401].valid = true; list[1401].action = 0;
			list[1446].push({true, 31}); list[1446].push({true, 30}); list[1446].valid = true; list[1446].action = 0;
			list[1454].valid = true; list[1454].action = 0;
			list[1494].push({false, 6}); list[1494].valid = true; list[1494].action = 13;
			list[1550].push({false, 14}); list[1550].valid = true; list[1550].action = 0;
			list[1594].push({false, 10}); list[1594].valid = true; list[1594].action = 14;
			list[1638].push({true, 35}); list[1638].push({true, 34}); list[1638].valid = true; list[1638].action = 0;
			list[1646].valid = true; list[1646].action = 0;
			list[1686].push({false, 6}); list[1686].valid = true; list[1686].action = 16;
			list[1742].push({false, 14}); list[1742].valid = true; list[1742].action = 15;
			list[1782].push({false, 6}); list[1782].valid = true; list[1782].action = 21;
			list[1830].valid = true; list[1830].action = 22;
			list[1831].valid = true; list[1831].action = 22;
			list[1832].valid = true; list[1832].action = 22;
			list[1836].valid = true; list[1836].action = 22;
			list[1837].valid = true; list[1837].action = 22;
			list[1838].valid = true; list[1838].action = 22;
			list[1842].valid = true; list[1842].action = 22;
			list[1886].push({false, 14}); list[1886].valid = true; list[1886].action = 19;
			list[1942].push({false, 22}); list[1942].valid = true; list[1942].action = 20;
			list[1982].push({false, 14}); list[1982].valid = true; list[1982].action = 19;
			list[2035].push({false, 19}); list[2035].valid = true; list[2035].action = 0;
			list[2078].push({false, 14}); list[2078].valid = true; list[2078].action = 19;
			list[2132].push({false, 20}); list[2132].valid = true; list[2132].action = 18;
			list[2174].push({false, 14}); list[2174].valid = true; list[2174].action = 19;
			list[2231].push({false, 23}); list[2231].valid = true; list[2231].action = 0;
			list[2270].push({false, 14}); list[2270].valid = true; list[2270].action = 23;
			list[2310].push({false, 6}); list[2310].valid = true; list[2310].action = 24;
			list[2316].push({false, 12}); list[2316].valid = true; list[2316].action = 25;
			list[2317].push({false, 13}); list[2317].valid = true; list[2317].action = 26;
			list[2358].push({true, 50}); list[2358].push({true, 49}); list[2358].valid = true; list[2358].action = 0;
			list[2359].push({true, 50}); list[2359].push({true, 49}); list[2359].valid = true; list[2359].action = 0;
			list[2360].push({true, 50}); list[2360].push({true, 49}); list[2360].valid = true; list[2360].action = 0;
			list[2364].push({true, 50}); list[2364].push({true, 49}); list[2364].valid = true; list[2364].action = 0;
			list[2365].push({true, 50}); list[2365].push({true, 49}); list[2365].valid = true; list[2365].action = 0;
			list[2366].valid = true; list[2366].action = 0;
			list[2370].push({false, 18}); list[2370].push({true, 51}); list[2370].push({true, 49});
			list[2370].valid = true; list[2370].action = 0;
			list[2406].push({false, 6}); list[2406].valid = true; list[2406].action = 27;
			list[2407].push({true, 53}); list[2407].valid = true; list[2407].action = 0;
			list[2408].push({true, 53}); list[2408].valid = true; list[2408].action = 0;
			list[2412].push({false, 12}); list[2412].valid = true; list[2412].action = 28;
			list[2413].push({false, 13}); list[2413].valid = true; list[2413].action = 29;
			list[2454].push({false, 6}); list[2454].valid = true; list[2454].action = 30;
			list[2502].push({false, 6}); list[2502].valid = true; list[2502].action = 31;
			list[2503].push({true, 53}); list[2503].valid = true; list[2503].action = 0;
			list[2504].push({true, 53}); list[2504].valid = true; list[2504].action = 0;
			list[2508].push({false, 12}); list[2508].valid = true; list[2508].action = 32;
			list[2509].push({false, 13}); list[2509].valid = true; list[2509].action = 33;
			list[2536].push({true, 59}); list[2536].valid = true; list[2536].action = 0;
			list[2537].push({true, 59}); list[2537].valid = true; list[2537].action = 0;
			list[2538].push({true, 59}); list[2538].valid = true; list[2538].action = 0;
			list[2539].push({true, 70}); list[2539].valid = true; list[2539].action = 0;
			list[2540].push({true, 70}); list[2540].valid = true; list[2540].action = 0;
			list[2541].push({true, 70}); list[2541].valid = true; list[2541].action = 0;
			list[2542].push({true, 70}); list[2542].valid = true; list[2542].action = 0;
			list[2543].push({true, 70}); list[2543].valid = true; list[2543].action = 0;
			list[2551].push({true, 54}); list[2551].push({true, 55}); list[2551].valid = true; list[2551].action = 0;
			list[2552].push({true, 54}); list[2552].push({true, 55}); list[2552].valid = true; list[2552].action = 0;
			list[2599].push({false, 7}); list[2599].valid = true; list[2599].action = 34;
			list[2600].push({false, 8}); list[2600].valid = true; list[2600].action = 35;
			list[2644].push({false, 4}); list[2644].push({true, 56}); list[2644].valid = true; list[2644].action = 0;
			list[2646].valid = true; list[2646].action = 8;
			list[2647].valid = true; list[2647].action = 8;
			list[2648].valid = true; list[2648].action = 8;
			list[2652].valid = true; list[2652].action = 8;
			list[2653].valid = true; list[2653].action = 8;
			list[2654].valid = true; list[2654].action = 8;
			list[2658].valid = true; list[2658].action = 8;
			list[2694].push({false, 6}); list[2694].valid = true; list[2694].action = 9;
			list[2760].valid = true; list[2760].action = 37;
			list[2769].push({false, 33}); list[2769].push({true, 58}); list[2769].push({false, 34});
			list[2769].valid = true; list[2769].action = 0;
			list[2791].push({false, 7}); list[2791].valid = true; list[2791].action = 36;
			list[2872].push({false, 40}); list[2872].push({true, 57}); list[2872].push({true, 60});
			list[2872].push({true, 62}); list[2872].push({true, 64}); list[2872].push({true, 61});
			list[2872].valid = true; list[2872].action = 0;
			list[2873].push({false, 41}); list[2873].push({true, 57}); list[2873].push({true, 60});
			list[2873].push({true, 63}); list[2873].push({true, 66}); list[2873].push({true, 61});
			list[2873].valid = true; list[2873].action = 0;
			list[2874].push({false, 42}); list[2874].push({true, 57}); list[2874].push({true, 60});
			list[2874].push({true, 62}); list[2874].push({true, 68}); list[2874].push({true, 61});
			list[2874].valid = true; list[2874].action = 0;
			list[2904].push({false, 24}); list[2904].valid = true; list[2904].action = 38;
			list[2953].push({false, 25}); list[2953].valid = true; list[2953].action = 39;
			list[2982].push({false, 6}); list[2982].valid = true; list[2982].action = 40;
			list[3003].push({false, 27}); list[3003].valid = true; list[3003].action = 40;
			list[3004].push({false, 28}); list[3004].valid = true; list[3004].action = 40;
			list[3006].push({false, 30}); list[3006].valid = true; list[3006].action = 40;
			list[3007].push({false, 31}); list[3007].valid = true; list[3007].action = 40;
			list[3030].push({true, 62}); list[3030].valid = true; list[3030].action = 41;
			list[3051].push({true, 62}); list[3051].valid = true; list[3051].action = 41;
			list[3052].push({true, 62}); list[3052].valid = true; list[3052].action = 41;
			list[3054].push({true, 62}); list[3054].valid = true; list[3054].action = 41;
			list[3055].push({true, 62}); list[3055].valid = true; list[3055].action = 41;
			list[3079].push({true, 65}); list[3079].push({true, 64}); list[3079].valid = true; list[3079].action = 0;
			list[3097].valid = true; list[3097].action = 0;
			list[3127].push({false, 7}); list[3127].valid = true; list[3127].action = 42;
			list[3174].push({true, 67}); list[3174].push({true, 66}); list[3174].valid = true; list[3174].action = 0;
			list[3193].valid = true; list[3193].action = 0;
			list[3195].push({true, 67}); list[3195].push({true, 66}); list[3195].valid = true; list[3195].action = 0;
			list[3196].push({true, 67}); list[3196].push({true, 66}); list[3196].valid = true; list[3196].action = 0;
			list[3198].push({true, 67}); list[3198].push({true, 66}); list[3198].valid = true; list[3198].action = 0;
			list[3199].push({true, 67}); list[3199].push({true, 66}); list[3199].valid = true; list[3199].action = 0;
			list[3222].push({false, 6}); list[3222].valid = true; list[3222].action = 43;
			list[3243].push({false, 27}); list[3243].valid = true; list[3243].action = 43;
			list[3244].push({false, 28}); list[3244].valid = true; list[3244].action = 43;
			list[3246].push({false, 30}); list[3246].valid = true; list[3246].action = 43;
			list[3247].push({false, 31}); list[3247].valid = true; list[3247].action = 43;
			list[3270].push({true, 69}); list[3270].push({true, 68}); list[3270].valid = true; list[3270].action = 0;
			list[3289].valid = true; list[3289].action = 45;
			list[3318].push({false, 6}); list[3318].valid = true; list[3318].action = 44;
			list[3403].push({false, 43}); list[3403].push({true, 57}); list[3403].push({true, 72});
			list[3403].push({true, 91}); list[3403].push({true, 98}); list[3403].valid = true; list[3403].action = 0;
			list[3404].push({false, 44}); list[3404].push({true, 57}); list[3404].push({true, 72});
			list[3404].push({true, 90}); list[3404].push({true, 91}); list[3404].push({true, 99});
			list[3404].valid = true; list[3404].action = 0;
			list[3405].push({false, 45}); list[3405].push({true, 57}); list[3405].push({true, 71});
			list[3405].push({true, 93}); list[3405].push({true, 91}); list[3405].push({true, 100});
			list[3405].valid = true; list[3405].action = 0;
			list[3406].push({false, 46}); list[3406].push({true, 57}); list[3406].push({true, 72});
			list[3406].push({true, 93}); list[3406].push({true, 91}); list[3406].push({true, 101});
			list[3406].valid = true; list[3406].action = 0;
			list[3407].push({false, 47}); list[3407].push({true, 57}); list[3407].push({true, 72});
			list[3407].push({true, 93}); list[3407].push({true, 91}); list[3407].push({true, 102});
			list[3407].valid = true; list[3407].action = 0;
			list[3432].push({true, 73}); list[3432].push({true, 79}); list[3432].push({true, 74});
			list[3432].push({true, 82}); list[3432].push({true, 74}); list[3432].push({true, 84});
			list[3432].push({true, 74}); list[3432].push({true, 87}); list[3432].push({true, 75});
			list[3432].valid = true; list[3432].action = 0;
			list[3480].push({true, 73}); list[3480].push({true, 82}); list[3480].push({true, 74});
			list[3480].push({true, 84}); list[3480].push({true, 74}); list[3480].push({true, 87});
			list[3480].push({true, 75}); list[3480].valid = true; list[3480].action = 0;
			list[3528].push({false, 24}); list[3528].valid = true; list[3528].action = 46;
			list[3578].push({false, 26}); list[3578].valid = true; list[3578].action = 47;
			list[3625].push({false, 25}); list[3625].valid = true; list[3625].action = 47;
			list[3654].push({false, 6}); list[3654].valid = true; list[3654].action = 48;
			list[3675].push({false, 27}); list[3675].valid = true; list[3675].action = 48;
			list[3676].push({false, 28}); list[3676].valid = true; list[3676].action = 48;
			list[3702].push({true, 76}); list[3702].valid = true; list[3702].action = 0;
			list[3723].push({true, 76}); list[3723].valid = true; list[3723].action = 0;
			list[3724].push({true, 76}); list[3724].valid = true; list[3724].action = 0;
			list[3726].push({false, 30}); list[3726].valid = true; list[3726].action = 48;
			list[3727].push({false, 31}); list[3727].valid = true; list[3727].action = 48;
			list[3750].push({false, 6}); list[3750].valid = true; list[3750].action = 49;
			list[3771].push({false, 27}); list[3771].valid = true; list[3771].action = 49;
			list[3772].push({false, 28}); list[3772].valid = true; list[3772].action = 49;
			list[3798].push({true, 77}); list[3798].push({true, 80}); list[3798].valid = true; list[3798].action = 50;
			list[3819].push({true, 77}); list[3819].push({true, 80}); list[3819].valid = true; list[3819].action = 50;
			list[3820].push({true, 77}); list[3820].push({true, 80}); list[3820].valid = true; list[3820].action = 50;
			list[3822].push({true, 77}); list[3822].push({true, 80}); list[3822].valid = true; list[3822].action = 50;
			list[3823].push({true, 77}); list[3823].push({true, 80}); list[3823].valid = true; list[3823].action = 50;
			list[3846].push({true, 78}); list[3846].push({true, 81}); list[3846].valid = true; list[3846].action = 0;
			list[3866].valid = true; list[3866].action = 51;
			list[3867].push({true, 78}); list[3867].push({true, 81}); list[3867].valid = true; list[3867].action = 0;
			list[3868].push({true, 78}); list[3868].push({true, 81}); list[3868].valid = true; list[3868].action = 0;
			list[3894].push({true, 78}); list[3894].valid = true; list[3894].action = 0;
			list[3914].valid = true; list[3914].action = 52;
			list[3915].push({true, 78}); list[3915].valid = true; list[3915].action = 0;
			list[3916].push({true, 78}); list[3916].valid = true; list[3916].action = 0;
			list[3942].push({true, 76}); list[3942].push({true, 83}); list[3942].valid = true; list[3942].action = 53;
			list[3962].valid = true; list[3962].action = 54;
			list[3963].push({true, 76}); list[3963].push({true, 83}); list[3963].valid = true; list[3963].action = 53;
			list[3964].push({true, 76}); list[3964].push({true, 83}); list[3964].valid = true; list[3964].action = 53;
			list[3990].push({true, 78}); list[3990].push({true, 83}); list[3990].valid = true; list[3990].action = 0;
			list[4010].valid = true; list[4010].action = 55;
			list[4011].push({true, 78}); list[4011].push({true, 83}); list[4011].valid = true; list[4011].action = 0;
			list[4012].push({true, 78}); list[4012].push({true, 83}); list[4012].valid = true; list[4012].action = 0;
			list[4038].push({true, 77}); list[4038].push({true, 85}); list[4038].valid = true; list[4038].action = 56;
			list[4058].valid = true; list[4058].action = 57;
			list[4059].push({true, 77}); list[4059].push({true, 85}); list[4059].valid = true; list[4059].action = 56;
			list[4060].push({true, 77}); list[4060].push({true, 85}); list[4060].valid = true; list[4060].action = 56;
			list[4062].push({true, 77}); list[4062].push({true, 85}); list[4062].valid = true; list[4062].action = 56;
			list[4063].push({true, 77}); list[4063].push({true, 85}); list[4063].valid = true; list[4063].action = 56;
			list[4086].push({true, 78}); list[4086].push({true, 86}); list[4086].valid = true; list[4086].action = 0;
			list[4106].valid = true; list[4106].action = 58;
			list[4107].push({true, 78}); list[4107].push({true, 86}); list[4107].valid = true; list[4107].action = 0;
			list[4108].push({true, 78}); list[4108].push({true, 86}); list[4108].valid = true; list[4108].action = 0;
			list[4134].push({true, 78}); list[4134].valid = true; list[4134].action = 0;
			list[4154].valid = true; list[4154].action = 59;
			list[4155].push({true, 78}); list[4155].valid = true; list[4155].action = 0;
			list[4156].push({true, 78}); list[4156].valid = true; list[4156].action = 0;
			list[4182].push({true, 77}); list[4182].push({true, 88}); list[4182].valid = true; list[4182].action = 60;
			list[4201].valid = true; list[4201].action = 61;
			list[4203].push({true, 77}); list[4203].push({true, 88}); list[4203].valid = true; list[4203].action = 60;
			list[4204].push({true, 77}); list[4204].push({true, 88}); list[4204].valid = true; list[4204].action = 60;
			list[4206].push({true, 77}); list[4206].push({true, 88}); list[4206].valid = true; list[4206].action = 60;
			list[4207].push({true, 77}); list[4207].push({true, 88}); list[4207].valid = true; list[4207].action = 60;
			list[4230].push({true, 78}); list[4230].push({true, 89}); list[4230].valid = true; list[4230].action = 0;
			list[4249].valid = true; list[4249].action = 62;
			list[4251].push({true, 78}); list[4251].push({true, 89}); list[4251].valid = true; list[4251].action = 0;
			list[4252].push({true, 78}); list[4252].push({true, 89}); list[4252].valid = true; list[4252].action = 0;
			list[4278].push({true, 78}); list[4278].valid = true; list[4278].action = 0;
			list[4297].valid = true; list[4297].action = 63;
			list[4299].push({true, 78}); list[4299].valid = true; list[4299].action = 0;
			list[4300].push({true, 78}); list[4300].valid = true; list[4300].action = 0;
			list[4353].push({true, 94}); list[4353].push({true, 104}); list[4353].push({true, 95});
			list[4353].valid = true; list[4353].action = 0;
			list[4355].push({true, 94}); list[4355].push({true, 104}); list[4355].push({true, 95});
			list[4355].valid = true; list[4355].action = 0;
			list[4401].push({true, 94}); list[4401].push({true, 104}); list[4401].push({false, 39});
			list[4401].push({true, 108}); list[4401].push({true, 96}); list[4401].valid = true; list[4401].action = 0;
			list[4403].push({true, 94}); list[4403].push({true, 104}); list[4403].push({false, 39});
			list[4403].push({true, 108}); list[4403].push({true, 96}); list[4403].valid = true; list[4403].action = 0;
			list[4449].push({true, 94}); list[4449].push({true, 104}); list[4449].push({true, 97});
			list[4449].valid = true; list[4449].action = 0;
			list[4451].push({true, 94}); list[4451].push({true, 104}); list[4451].push({true, 97});
			list[4451].valid = true; list[4451].action = 0;
			list[4501].push({false, 37}); list[4501].push({false, 38}); list[4501].valid = true; list[4501].action = 64;
			list[4545].push({false, 33}); list[4545].valid = true; list[4545].action = 65;
			list[4547].push({false, 35}); list[4547].valid = true; list[4547].action = 66;
			list[4594].push({false, 34}); list[4594].valid = true; list[4594].action = 67;
			list[4596].push({false, 36}); list[4596].valid = true; list[4596].action = 68;
			list[4642].push({false, 34}); list[4642].valid = true; list[4642].action = 69;
			list[4644].push({false, 36}); list[4644].valid = true; list[4644].action = 70;
			list[4690].push({false, 34}); list[4690].valid = true; list[4690].action = 71;
			list[4692].push({false, 36}); list[4692].valid = true; list[4692].action = 72;
			list[4718].valid = true; list[4718].action = 73;
			list[4741].push({true, 93}); list[4741].push({true, 98}); list[4741].valid = true; list[4741].action = 0;
			list[4766].valid = true; list[4766].action = 74;
			list[4785].push({true, 103}); list[4785].push({true, 99}); list[4785].valid = true; list[4785].action = 0;
			list[4787].push({true, 103}); list[4787].push({true, 99}); list[4787].valid = true; list[4787].action = 0;
			list[4789].push({true, 103}); list[4789].push({true, 99}); list[4789].valid = true; list[4789].action = 0;
			list[4814].valid = true; list[4814].action = 75;
			list[4833].push({true, 103}); list[4833].push({true, 100}); list[4833].valid = true; list[4833].action = 0;
			list[4835].push({true, 103}); list[4835].push({true, 100}); list[4835].valid = true; list[4835].action = 0;
			list[4837].push({true, 103}); list[4837].push({true, 100}); list[4837].valid = true; list[4837].action = 0;
			list[4862].valid = true; list[4862].action = 76;
			list[4881].push({true, 103}); list[4881].push({true, 101}); list[4881].valid = true; list[4881].action = 0;
			list[4883].push({true, 103}); list[4883].push({true, 101}); list[4883].valid = true; list[4883].action = 0;
			list[4885].push({true, 103}); list[4885].push({true, 101}); list[4885].valid = true; list[4885].action = 0;
			list[4910].valid = true; list[4910].action = 77;
			list[4929].push({true, 103}); list[4929].push({true, 102}); list[4929].valid = true; list[4929].action = 0;
			list[4931].push({true, 103}); list[4931].push({true, 102}); list[4931].valid = true; list[4931].action = 0;
			list[4933].push({true, 103}); list[4933].push({true, 102}); list[4933].valid = true; list[4933].action = 0;
			list[4977].push({true, 92}); list[4977].valid = true; list[4977].action = 0;
			list[4979].push({true, 92}); list[4979].valid = true; list[4979].action = 0;
			list[4981].push({true, 93}); list[4981].valid = true; list[4981].action = 0;
			list[4998].push({true, 105}); list[4998].push({false, 26}); list[4998].push({true, 107});
			list[4998].valid = true; list[4998].action = 0;
			list[5021].push({true, 105}); list[5021].push({false, 26}); list[5021].push({true, 107});
			list[5021].valid = true; list[5021].action = 0;
			list[5022].push({false, 30}); list[5022].push({false, 26}); list[5022].push({false, 31});
			list[5022].valid = true; list[5022].action = 78;
			list[5023].push({false, 31}); list[5023].push({false, 26}); list[5023].push({false, 30});
			list[5023].valid = true; list[5023].action = 79;
			list[5026].valid = true; list[5026].action = 80;
			list[5028].valid = true; list[5028].action = 80;
			list[5031].valid = true; list[5031].action = 80;
			list[5046].push({false, 6}); list[5046].valid = true; list[5046].action = 81;
			list[5069].push({false, 29}); list[5069].push({true, 106}); list[5069].valid = true; list[5069].action = 0;
			list[5094].push({false, 6}); list[5094].valid = true; list[5094].action = 82;
			list[5142].push({true, 105}); list[5142].valid = true; list[5142].action = 0;
			list[5165].push({true, 105}); list[5165].valid = true; list[5165].action = 0;
			list[5168].push({false, 32}); list[5168].valid = true; list[5168].action = 83;
			list[5190].push({true, 109}); list[5190].push({false, 26}); list[5190].push({true, 111});
			list[5190].valid = true; list[5190].action = 0;
			list[5213].push({true, 109}); list[5213].push({false, 26}); list[5213].push({true, 111});
			list[5213].valid = true; list[5213].action = 0;
			list[5214].push({false, 30}); list[5214].push({false, 26}); list[5214].push({false, 31});
			list[5214].valid = true; list[5214].action = 84;
			list[5215].push({false, 31}); list[5215].push({false, 26}); list[5215].push({false, 30});
			list[5215].valid = true; list[5215].action = 85;
			list[5218].valid = true; list[5218].action = 86;
			list[5220].valid = true; list[5220].action = 86;
			list[5238].push({false, 6}); list[5238].valid = true; list[5238].action = 87;
			list[5261].push({false, 29}); list[5261].push({true, 110}); list[5261].valid = true; list[5261].action = 0;
			list[5286].push({false, 6}); list[5286].valid = true; list[5286].action = 88;
			list[5334].push({true, 109}); list[5334].valid = true; list[5334].action = 0;
			list[5357].push({true, 109}); list[5357].valid = true; list[5357].action = 0;
			list[5360].push({false, 32}); list[5360].valid = true; list[5360].action = 89;
		}

		nik_ce cprod_type & production(csymbol_type & row, ctoken_type col) const
			{ return list[row.token() * col_size + col]; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

