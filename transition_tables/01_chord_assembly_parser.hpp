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

		nik_ces auto start_index	= 9;
		nik_ces auto row_size		= 62;
		nik_ces auto col_size		= 40;

		nik_ces auto prod_size		= cctmp::string_literal("<B|B|U|U|B|B>").size(); // needs refining.

		nik_ces auto stack_finish	= symbol_type{cctmp::Sign::terminal, Token::prompt};
		nik_ces auto stack_start	= symbol_type{cctmp::Sign::nonterminal, start_index};

		nik_ces auto stack_size		= cctmp::literal("6<B|B|U|U|B|B>YPZ{}YPZYP,PZV;HGO").size(); // needs refining.
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

			list[8].push({false, 8});
			list[8].valid = true;
			list[8].action = 6;
			list[43].push({false, 3});
			list[43].valid = true;
			list[43].action = 7;
			list[83].push({false, 3});
			list[83].valid = true;
			list[83].action = 8;
			list[123].push({false, 3});
			list[123].valid = true;
			list[123].action = 19;
			list[163].push({false, 3});
			list[163].valid = true;
			list[163].action = 18;
			list[164].push({false, 4});
			list[164].valid = true;
			list[164].action = 15;
			list[207].push({false, 7});
			list[207].valid = true;
			list[207].action = 5;
			list[247].push({false, 7});
			list[247].valid = true;
			list[247].action = 4;
			list[288].valid = true;
			list[288].action = 4;
			list[323].push({false, 3});
			list[323].valid = true;
			list[323].action = 20;
			list[325].push({false, 5});
			list[325].valid = true;
			list[325].action = 16;
			list[326].push({false, 6});
			list[326].valid = true;
			list[326].action = 17;
			list[352].push({true, 19});
			list[352].valid = true;
			list[352].action = 0;
			list[353].push({true, 19});
			list[353].valid = true;
			list[353].action = 0;
			list[354].push({true, 19});
			list[354].valid = true;
			list[354].action = 0;
			list[355].push({true, 19});
			list[355].valid = true;
			list[355].action = 0;
			list[356].push({true, 19});
			list[356].valid = true;
			list[356].action = 0;
			list[357].push({true, 19});
			list[357].valid = true;
			list[357].action = 0;
			list[358].push({true, 19});
			list[358].valid = true;
			list[358].action = 0;
			list[359].push({true, 19});
			list[359].valid = true;
			list[359].action = 0;
			list[363].push({false, 3});
			list[363].push({true, 10});
			list[363].push({true, 5});
			list[363].push({true, 11});
			list[363].push({true, 12});
			list[363].valid = true;
			list[363].action = 1;
			list[403].push({false, 3});
			list[403].push({true, 10});
			list[403].valid = true;
			list[403].action = 2;
			list[407].valid = true;
			list[407].action = 3;
			list[448].push({true, 0});
			list[448].push({true, 6});
			list[448].push({true, 13});
			list[448].valid = true;
			list[448].action = 0;
			list[482].valid = true;
			list[482].action = 21;
			list[488].push({true, 7});
			list[488].push({true, 11});
			list[488].push({true, 12});
			list[488].valid = true;
			list[488].action = 0;
			list[523].push({true, 16});
			list[523].push({true, 6});
			list[523].push({true, 14});
			list[523].push({true, 15});
			list[523].valid = true;
			list[523].action = 0;
			list[524].push({true, 16});
			list[524].push({true, 6});
			list[524].push({true, 14});
			list[524].push({true, 15});
			list[524].valid = true;
			list[524].action = 0;
			list[529].push({false, 9});
			list[529].push({true, 8});
			list[529].push({false, 7});
			list[529].valid = true;
			list[529].action = 10;
			list[531].push({true, 16});
			list[531].push({true, 6});
			list[531].push({true, 14});
			list[531].push({true, 15});
			list[531].valid = true;
			list[531].action = 0;
			list[533].push({true, 16});
			list[533].push({true, 6});
			list[533].push({true, 14});
			list[533].push({true, 15});
			list[533].valid = true;
			list[533].action = 0;
			list[535].push({true, 16});
			list[535].push({true, 6});
			list[535].push({true, 14});
			list[535].push({true, 15});
			list[535].valid = true;
			list[535].action = 0;
			list[563].push({true, 16});
			list[563].push({true, 6});
			list[563].push({true, 14});
			list[563].valid = true;
			list[563].action = 0;
			list[564].push({true, 16});
			list[564].push({true, 6});
			list[564].push({true, 14});
			list[564].valid = true;
			list[564].action = 0;
			list[568].valid = true;
			list[568].action = 0;
			list[569].valid = true;
			list[569].action = 0;
			list[570].valid = true;
			list[570].action = 0;
			list[571].push({true, 16});
			list[571].push({true, 6});
			list[571].push({true, 14});
			list[571].valid = true;
			list[571].action = 0;
			list[573].push({true, 16});
			list[573].push({true, 6});
			list[573].push({true, 14});
			list[573].valid = true;
			list[573].action = 0;
			list[575].push({true, 16});
			list[575].push({true, 6});
			list[575].push({true, 14});
			list[575].valid = true;
			list[575].action = 0;
			list[608].push({true, 0});
			list[608].push({true, 6});
			list[608].push({true, 13});
			list[608].valid = true;
			list[608].action = 9;
			list[609].push({false, 9});
			list[609].push({true, 8});
			list[609].push({false, 7});
			list[609].valid = true;
			list[609].action = 10;
			list[610].push({false, 10});
			list[610].push({true, 2});
			list[610].push({false, 7});
			list[610].valid = true;
			list[610].action = 0;
			list[643].push({true, 4});
			list[643].push({true, 17});
			list[643].valid = true;
			list[643].action = 0;
			list[644].push({true, 4});
			list[644].push({true, 17});
			list[644].valid = true;
			list[644].action = 0;
			list[651].push({false, 11});
			list[651].push({true, 3});
			list[651].push({false, 12});
			list[651].push({true, 8});
			list[651].push({true, 18});
			list[651].valid = true;
			list[651].action = 12;
			list[653].push({false, 13});
			list[653].push({true, 8});
			list[653].push({true, 18});
			list[653].push({true, 6});
			list[653].push({false, 14});
			list[653].push({true, 1});
			list[653].valid = true;
			list[653].action = 13;
			list[655].push({false, 15});
			list[655].push({true, 8});
			list[655].push({true, 18});
			list[655].valid = true;
			list[655].action = 12;
			list[692].push({false, 12});
			list[692].push({true, 8});
			list[692].push({true, 18});
			list[692].valid = true;
			list[692].action = 11;
			list[696].push({false, 16});
			list[696].push({true, 8});
			list[696].valid = true;
			list[696].action = 14;
			list[723].push({true, 8});
			list[723].push({true, 18});
			list[723].valid = true;
			list[723].action = 0;
			list[725].push({true, 8});
			list[725].push({true, 18});
			list[725].valid = true;
			list[725].action = 0;
			list[726].push({true, 8});
			list[726].push({true, 18});
			list[726].valid = true;
			list[726].action = 0;
			list[727].valid = true;
			list[727].action = 0;
			list[731].push({false, 11});
			list[731].push({true, 3});
			list[731].push({true, 18});
			list[731].valid = true;
			list[731].action = 0;
			list[752].push({true, 8});
			list[752].push({true, 18});
			list[752].valid = true;
			list[752].action = 0;
			list[753].push({true, 8});
			list[753].push({true, 18});
			list[753].valid = true;
			list[753].action = 0;
			list[754].push({true, 8});
			list[754].push({true, 18});
			list[754].valid = true;
			list[754].action = 0;
			list[755].push({true, 8});
			list[755].push({true, 18});
			list[755].valid = true;
			list[755].action = 0;
			list[756].push({true, 8});
			list[756].push({true, 18});
			list[756].valid = true;
			list[756].action = 0;
			list[757].push({true, 8});
			list[757].push({true, 18});
			list[757].valid = true;
			list[757].action = 0;
			list[758].push({true, 8});
			list[758].push({true, 18});
			list[758].valid = true;
			list[758].action = 0;
			list[759].push({true, 8});
			list[759].push({true, 18});
			list[759].valid = true;
			list[759].action = 0;
			list[792].push({false, 32});
			list[792].push({true, 20});
			list[792].push({true, 40});
			list[792].push({false, 29});
			list[792].push({false, 30});
			list[792].valid = true;
			list[792].action = 22;
			list[793].push({false, 33});
			list[793].push({true, 24});
			list[793].push({true, 46});
			list[793].push({true, 47});
			list[793].valid = true;
			list[793].action = 26;
			list[794].push({false, 34});
			list[794].push({true, 21});
			list[794].push({false, 29});
			list[794].push({false, 30});
			list[794].push({true, 41});
			list[794].valid = true;
			list[794].action = 23;
			list[795].push({false, 35});
			list[795].push({true, 22});
			list[795].push({true, 42});
			list[795].push({true, 43});
			list[795].valid = true;
			list[795].action = 24;
			list[796].push({false, 36});
			list[796].push({true, 23});
			list[796].push({true, 44});
			list[796].push({true, 45});
			list[796].valid = true;
			list[796].action = 25;
			list[797].push({false, 37});
			list[797].push({true, 25});
			list[797].push({true, 48});
			list[797].push({true, 49});
			list[797].push({true, 50});
			list[797].valid = true;
			list[797].action = 27;
			list[798].push({false, 38});
			list[798].push({true, 26});
			list[798].push({false, 29});
			list[798].push({false, 30});
			list[798].push({true, 51});
			list[798].push({true, 52});
			list[798].valid = true;
			list[798].action = 28;
			list[799].push({false, 39});
			list[799].push({true, 27});
			list[799].push({true, 53});
			list[799].push({false, 29});
			list[799].push({false, 30});
			list[799].push({true, 54});
			list[799].push({true, 55});
			list[799].valid = true;
			list[799].action = 29;
			list[817].push({false, 17});
			list[817].push({true, 28});
			list[817].push({false, 19});
			list[817].push({true, 34});
			list[817].push({false, 19});
			list[817].push({true, 35});
			list[817].push({false, 18});
			list[817].valid = true;
			list[817].action = 0;
			list[857].push({false, 17});
			list[857].push({true, 30});
			list[857].push({false, 19});
			list[857].push({true, 34});
			list[857].push({false, 19});
			list[857].push({true, 35});
			list[857].push({false, 18});
			list[857].valid = true;
			list[857].action = 0;
			list[897].push({false, 17});
			list[897].push({true, 31});
			list[897].push({false, 19});
			list[897].push({true, 34});
			list[897].push({false, 19});
			list[897].push({true, 35});
			list[897].push({false, 18});
			list[897].valid = true;
			list[897].action = 0;
			list[937].push({false, 17});
			list[937].push({true, 31});
			list[937].push({false, 19});
			list[937].push({true, 34});
			list[937].push({false, 19});
			list[937].push({true, 35});
			list[937].push({false, 18});
			list[937].valid = true;
			list[937].action = 0;
			list[977].push({false, 17});
			list[977].push({true, 28});
			list[977].push({false, 19});
			list[977].push({true, 34});
			list[977].push({false, 19});
			list[977].push({true, 35});
			list[977].push({false, 18});
			list[977].valid = true;
			list[977].action = 0;
			list[1017].push({false, 17});
			list[1017].push({true, 29});
			list[1017].push({false, 19});
			list[1017].push({true, 34});
			list[1017].push({false, 19});
			list[1017].push({true, 35});
			list[1017].push({false, 18});
			list[1017].valid = true;
			list[1017].action = 0;
			list[1057].push({false, 17});
			list[1057].push({true, 29});
			list[1057].push({false, 19});
			list[1057].push({true, 30});
			list[1057].push({false, 19});
			list[1057].push({true, 34});
			list[1057].push({false, 19});
			list[1057].push({true, 35});
			list[1057].push({false, 18});
			list[1057].valid = true;
			list[1057].action = 0;
			list[1097].push({false, 17});
			list[1097].push({true, 29});
			list[1097].push({false, 19});
			list[1097].push({true, 32});
			list[1097].push({false, 19});
			list[1097].push({true, 33});
			list[1097].push({false, 19});
			list[1097].push({true, 33});
			list[1097].push({false, 19});
			list[1097].push({true, 34});
			list[1097].push({false, 19});
			list[1097].push({true, 35});
			list[1097].push({false, 18});
			list[1097].valid = true;
			list[1097].action = 0;
			list[1123].push({true, 39});
			list[1123].push({true, 37});
			list[1123].valid = true;
			list[1123].action = 30;
			list[1139].valid = true;
			list[1139].action = 31;
			list[1140].push({true, 39});
			list[1140].push({true, 37});
			list[1140].valid = true;
			list[1140].action = 30;
			list[1141].push({true, 39});
			list[1141].push({true, 37});
			list[1141].valid = true;
			list[1141].action = 30;
			list[1163].push({true, 38});
			list[1163].push({true, 36});
			list[1163].valid = true;
			list[1163].action = 30;
			list[1203].push({true, 38});
			list[1203].push({true, 36});
			list[1203].valid = true;
			list[1203].action = 30;
			list[1243].push({true, 39});
			list[1243].push({true, 37});
			list[1243].valid = true;
			list[1243].action = 30;
			list[1260].push({true, 39});
			list[1260].push({true, 37});
			list[1260].valid = true;
			list[1260].action = 30;
			list[1261].push({true, 39});
			list[1261].push({true, 37});
			list[1261].valid = true;
			list[1261].action = 30;
			list[1283].push({true, 38});
			list[1283].push({true, 36});
			list[1283].valid = true;
			list[1283].action = 30;
			list[1323].push({true, 39});
			list[1323].push({true, 37});
			list[1323].valid = true;
			list[1323].action = 30;
			list[1340].push({true, 39});
			list[1340].push({true, 37});
			list[1340].valid = true;
			list[1340].action = 30;
			list[1341].push({true, 39});
			list[1341].push({true, 37});
			list[1341].valid = true;
			list[1341].action = 30;
			list[1363].push({true, 38});
			list[1363].push({true, 36});
			list[1363].valid = true;
			list[1363].action = 30;
			list[1379].valid = true;
			list[1379].action = 32;
			list[1403].push({true, 38});
			list[1403].push({true, 36});
			list[1403].valid = true;
			list[1403].action = 30;
			list[1418].valid = true;
			list[1418].action = 33;
			list[1443].push({true, 39});
			list[1443].push({true, 37});
			list[1443].valid = true;
			list[1443].action = 0;
			list[1458].valid = true;
			list[1458].action = 37;
			list[1459].valid = true;
			list[1459].action = 37;
			list[1460].push({true, 39});
			list[1460].push({true, 37});
			list[1460].valid = true;
			list[1460].action = 0;
			list[1461].push({true, 39});
			list[1461].push({true, 37});
			list[1461].valid = true;
			list[1461].action = 0;
			list[1483].push({true, 39});
			list[1483].valid = true;
			list[1483].action = 0;
			list[1498].valid = true;
			list[1498].action = 38;
			list[1499].valid = true;
			list[1499].action = 38;
			list[1500].push({true, 39});
			list[1500].valid = true;
			list[1500].action = 0;
			list[1501].push({true, 39});
			list[1501].valid = true;
			list[1501].action = 0;
			list[1523].push({false, 3});
			list[1523].valid = true;
			list[1523].action = 34;
			list[1563].push({false, 3});
			list[1563].valid = true;
			list[1563].action = 34;
			list[1580].push({false, 20});
			list[1580].valid = true;
			list[1580].action = 36;
			list[1581].push({false, 21});
			list[1581].valid = true;
			list[1581].action = 35;
			list[1625].push({true, 60});
			list[1625].push({true, 56});
			list[1625].push({false, 31});
			list[1625].push({true, 61});
			list[1625].valid = true;
			list[1625].action = 0;
			list[1627].push({true, 60});
			list[1627].push({true, 56});
			list[1627].push({false, 31});
			list[1627].push({true, 61});
			list[1627].valid = true;
			list[1627].action = 0;
			list[1665].push({true, 60});
			list[1665].push({true, 56});
			list[1665].push({false, 31});
			list[1665].push({true, 61});
			list[1665].valid = true;
			list[1665].action = 0;
			list[1667].push({true, 60});
			list[1667].push({true, 56});
			list[1667].push({false, 31});
			list[1667].push({true, 61});
			list[1667].valid = true;
			list[1667].action = 0;
			list[1705].push({true, 60});
			list[1705].push({true, 56});
			list[1705].push({true, 61});
			list[1705].valid = true;
			list[1705].action = 0;
			list[1707].push({true, 60});
			list[1707].push({true, 56});
			list[1707].push({true, 61});
			list[1707].valid = true;
			list[1707].action = 0;
			list[1745].push({true, 60});
			list[1745].push({true, 56});
			list[1745].push({false, 31});
			list[1745].push({true, 61});
			list[1745].valid = true;
			list[1745].action = 0;
			list[1747].push({true, 60});
			list[1747].push({true, 56});
			list[1747].push({false, 31});
			list[1747].push({true, 61});
			list[1747].valid = true;
			list[1747].action = 0;
			list[1785].push({true, 60});
			list[1785].push({true, 56});
			list[1785].push({true, 61});
			list[1785].valid = true;
			list[1785].action = 0;
			list[1787].push({true, 60});
			list[1787].push({true, 56});
			list[1787].push({true, 61});
			list[1787].valid = true;
			list[1787].action = 0;
			list[1825].push({true, 60});
			list[1825].push({true, 56});
			list[1825].push({false, 31});
			list[1825].push({true, 61});
			list[1825].valid = true;
			list[1825].action = 0;
			list[1827].push({true, 60});
			list[1827].push({true, 56});
			list[1827].push({false, 31});
			list[1827].push({true, 61});
			list[1827].valid = true;
			list[1827].action = 0;
			list[1865].push({true, 60});
			list[1865].push({true, 57});
			list[1865].push({true, 61});
			list[1865].valid = true;
			list[1865].action = 0;
			list[1867].push({true, 60});
			list[1867].push({true, 57});
			list[1867].push({true, 61});
			list[1867].valid = true;
			list[1867].action = 0;
			list[1905].push({true, 60});
			list[1905].push({true, 57});
			list[1905].push({false, 31});
			list[1905].push({true, 57});
			list[1905].push({true, 61});
			list[1905].valid = true;
			list[1905].action = 0;
			list[1907].push({true, 60});
			list[1907].push({true, 57});
			list[1907].push({false, 31});
			list[1907].push({true, 57});
			list[1907].push({true, 61});
			list[1907].valid = true;
			list[1907].action = 0;
			list[1945].push({true, 60});
			list[1945].push({true, 57});
			list[1945].push({true, 61});
			list[1945].valid = true;
			list[1945].action = 0;
			list[1947].push({true, 60});
			list[1947].push({true, 57});
			list[1947].push({true, 61});
			list[1947].valid = true;
			list[1947].action = 0;
			list[1985].push({true, 60});
			list[1985].push({true, 57});
			list[1985].push({true, 61});
			list[1985].valid = true;
			list[1985].action = 0;
			list[1987].push({true, 60});
			list[1987].push({true, 57});
			list[1987].push({true, 61});
			list[1987].valid = true;
			list[1987].action = 0;
			list[2025].push({true, 60});
			list[2025].push({true, 57});
			list[2025].push({false, 31});
			list[2025].push({true, 57});
			list[2025].push({true, 61});
			list[2025].valid = true;
			list[2025].action = 0;
			list[2027].push({true, 60});
			list[2027].push({true, 57});
			list[2027].push({false, 31});
			list[2027].push({true, 57});
			list[2027].push({true, 61});
			list[2027].valid = true;
			list[2027].action = 0;
			list[2065].push({true, 60});
			list[2065].push({true, 57});
			list[2065].push({true, 61});
			list[2065].valid = true;
			list[2065].action = 0;
			list[2067].push({true, 60});
			list[2067].push({true, 57});
			list[2067].push({true, 61});
			list[2067].valid = true;
			list[2067].action = 0;
			list[2105].push({true, 60});
			list[2105].push({true, 57});
			list[2105].push({false, 31});
			list[2105].push({true, 57});
			list[2105].push({true, 61});
			list[2105].valid = true;
			list[2105].action = 0;
			list[2107].push({true, 60});
			list[2107].push({true, 57});
			list[2107].push({false, 31});
			list[2107].push({true, 57});
			list[2107].push({true, 61});
			list[2107].valid = true;
			list[2107].action = 0;
			list[2145].push({true, 60});
			list[2145].push({true, 57});
			list[2145].push({true, 61});
			list[2145].valid = true;
			list[2145].action = 0;
			list[2147].push({true, 60});
			list[2147].push({true, 57});
			list[2147].push({true, 61});
			list[2147].valid = true;
			list[2147].action = 0;
			list[2185].push({true, 60});
			list[2185].push({true, 57});
			list[2185].push({true, 61});
			list[2185].valid = true;
			list[2185].action = 0;
			list[2187].push({true, 60});
			list[2187].push({true, 57});
			list[2187].push({true, 61});
			list[2187].valid = true;
			list[2187].action = 0;
			list[2225].push({true, 60});
			list[2225].push({true, 57});
			list[2225].push({false, 31});
			list[2225].push({true, 57});
			list[2225].push({true, 61});
			list[2225].valid = true;
			list[2225].action = 0;
			list[2227].push({true, 60});
			list[2227].push({true, 57});
			list[2227].push({false, 31});
			list[2227].push({true, 57});
			list[2227].push({true, 61});
			list[2227].valid = true;
			list[2227].action = 0;
			list[2243].push({true, 59});
			list[2243].valid = true;
			list[2243].action = 39;
			list[2260].push({true, 59});
			list[2260].valid = true;
			list[2260].action = 39;
			list[2261].push({true, 59});
			list[2261].valid = true;
			list[2261].action = 39;
			list[2262].push({false, 22});
			list[2262].valid = true;
			list[2262].action = 42;
			list[2263].push({false, 23});
			list[2263].valid = true;
			list[2263].action = 43;
			list[2266].valid = true;
			list[2266].action = 40;
			list[2268].valid = true;
			list[2268].action = 40;
			list[2271].valid = true;
			list[2271].action = 40;
			list[2283].push({true, 59});
			list[2283].push({false, 19});
			list[2283].push({true, 58});
			list[2283].valid = true;
			list[2283].action = 39;
			list[2300].push({true, 59});
			list[2300].push({false, 19});
			list[2300].push({true, 58});
			list[2300].valid = true;
			list[2300].action = 39;
			list[2301].push({true, 59});
			list[2301].push({false, 19});
			list[2301].push({true, 58});
			list[2301].valid = true;
			list[2301].action = 39;
			list[2302].push({false, 22});
			list[2302].push({false, 19});
			list[2302].push({false, 23});
			list[2302].valid = true;
			list[2302].action = 44;
			list[2303].push({false, 23});
			list[2303].push({false, 19});
			list[2303].push({false, 22});
			list[2303].valid = true;
			list[2303].action = 45;
			list[2306].valid = true;
			list[2306].action = 41;
			list[2308].valid = true;
			list[2308].action = 41;
			list[2311].valid = true;
			list[2311].action = 41;
			list[2323].push({true, 59});
			list[2323].valid = true;
			list[2323].action = 0;
			list[2340].push({true, 59});
			list[2340].valid = true;
			list[2340].action = 0;
			list[2341].push({true, 59});
			list[2341].valid = true;
			list[2341].action = 0;
			list[2344].push({false, 24});
			list[2344].valid = true;
			list[2344].action = 49;
			list[2363].push({false, 3});
			list[2363].valid = true;
			list[2363].action = 46;
			list[2380].push({false, 20});
			list[2380].valid = true;
			list[2380].action = 48;
			list[2381].push({false, 21});
			list[2381].valid = true;
			list[2381].action = 47;
			list[2425].push({false, 25});
			list[2425].valid = true;
			list[2425].action = 50;
			list[2427].push({false, 27});
			list[2427].valid = true;
			list[2427].action = 51;
			list[2466].push({false, 26});
			list[2466].valid = true;
			list[2466].action = 52;
			list[2468].push({false, 28});
			list[2468].valid = true;
			list[2468].action = 53;
		}

		nik_ce cprod_type & production(csymbol_type & row, ctoken_type col) const
			{ return list[row.token() * col_size + col]; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

