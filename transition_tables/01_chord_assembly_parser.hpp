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

		nik_ces auto start_index	= 10;
		nik_ces auto row_size		= 69;
		nik_ces auto col_size		= 43;

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

			list[8].push({false, 8}); list[8].valid = true; list[8].action = 6;
			list[46].push({false, 3}); list[46].valid = true; list[46].action = 7;
			list[89].push({false, 3}); list[89].valid = true; list[89].action = 8;
			list[132].push({false, 3}); list[132].valid = true; list[132].action = 19;
			list[175].push({false, 3}); list[175].valid = true; list[175].action = 18;
			list[176].push({false, 4}); list[176].valid = true; list[176].action = 15;
			list[222].push({false, 7}); list[222].valid = true; list[222].action = 5;
			list[265].push({false, 7}); list[265].valid = true; list[265].action = 4;
			list[309].valid = true; list[309].action = 4;
			list[347].push({false, 3}); list[347].valid = true; list[347].action = 20;
			list[349].push({false, 5}); list[349].valid = true; list[349].action = 16;
			list[350].push({false, 6}); list[350].valid = true; list[350].action = 17;
			list[376].push({true, 20}); list[376].valid = true; list[376].action = 23;
			list[377].push({true, 20}); list[377].valid = true; list[377].action = 23;
			list[378].push({true, 20}); list[378].valid = true; list[378].action = 23;
			list[379].push({true, 24}); list[379].valid = true; list[379].action = 29;
			list[380].push({true, 24}); list[380].valid = true; list[380].action = 29;
			list[381].push({true, 24}); list[381].valid = true; list[381].action = 29;
			list[382].push({true, 24}); list[382].valid = true; list[382].action = 29;
			list[383].push({true, 24}); list[383].valid = true; list[383].action = 29;
			list[384].push({true, 24}); list[384].valid = true; list[384].action = 29;
			list[385].push({true, 24}); list[385].valid = true; list[385].action = 29;
			list[386].push({true, 24}); list[386].valid = true; list[386].action = 29;
			list[390].push({false, 3}); list[390].valid = true; list[390].action = 21;
			list[392].push({false, 5}); list[392].valid = true; list[392].action = 16;
			list[393].push({false, 6}); list[393].valid = true; list[393].action = 17;
			list[419].push({true, 20}); list[419].valid = true; list[419].action = 23;
			list[420].push({true, 20}); list[420].valid = true; list[420].action = 23;
			list[421].push({true, 20}); list[421].valid = true; list[421].action = 23;
			list[422].push({true, 24}); list[422].valid = true; list[422].action = 29;
			list[423].push({true, 24}); list[423].valid = true; list[423].action = 29;
			list[424].push({true, 24}); list[424].valid = true; list[424].action = 29;
			list[425].push({true, 24}); list[425].valid = true; list[425].action = 29;
			list[426].push({true, 24}); list[426].valid = true; list[426].action = 29;
			list[427].push({true, 24}); list[427].valid = true; list[427].action = 29;
			list[428].push({true, 24}); list[428].valid = true; list[428].action = 29;
			list[429].push({true, 24}); list[429].valid = true; list[429].action = 29;
			list[433].push({false, 3}); list[433].push({true, 11}); list[433].push({true, 5});
			list[433].push({true, 12}); list[433].push({true, 13}); list[433].valid = true; list[433].action = 1;
			list[476].push({false, 3}); list[476].push({true, 11}); list[476].valid = true; list[476].action = 2;
			list[480].valid = true; list[480].action = 3;
			list[524].push({true, 0}); list[524].push({true, 6}); list[524].push({true, 14});
			list[524].valid = true; list[524].action = 0;
			list[561].valid = true; list[561].action = 22;
			list[567].push({true, 7}); list[567].push({true, 12}); list[567].push({true, 13});
			list[567].valid = true; list[567].action = 0;
			list[605].push({true, 17}); list[605].push({true, 6}); list[605].push({true, 15});
			list[605].push({true, 16}); list[605].valid = true; list[605].action = 0;
			list[606].push({true, 17}); list[606].push({true, 6}); list[606].push({true, 15});
			list[606].push({true, 16}); list[606].valid = true; list[606].action = 0;
			list[611].push({false, 9}); list[611].push({true, 8}); list[611].push({false, 7});
			list[611].valid = true; list[611].action = 10;
			list[613].push({true, 17}); list[613].push({true, 6}); list[613].push({true, 15});
			list[613].push({true, 16}); list[613].valid = true; list[613].action = 0;
			list[615].push({true, 17}); list[615].push({true, 6}); list[615].push({true, 15});
			list[615].push({true, 16}); list[615].valid = true; list[615].action = 0;
			list[617].push({true, 17}); list[617].push({true, 6}); list[617].push({true, 15});
			list[617].push({true, 16}); list[617].valid = true; list[617].action = 0;
			list[648].push({true, 17}); list[648].push({true, 6}); list[648].push({true, 15});
			list[648].valid = true; list[648].action = 0;
			list[649].push({true, 17}); list[649].push({true, 6}); list[649].push({true, 15});
			list[649].valid = true; list[649].action = 0;
			list[653].valid = true; list[653].action = 0;
			list[654].valid = true; list[654].action = 0;
			list[655].valid = true; list[655].action = 0;
			list[656].push({true, 17}); list[656].push({true, 6}); list[656].push({true, 15});
			list[656].valid = true; list[656].action = 0;
			list[658].push({true, 17}); list[658].push({true, 6}); list[658].push({true, 15});
			list[658].valid = true; list[658].action = 0;
			list[660].push({true, 17}); list[660].push({true, 6}); list[660].push({true, 15});
			list[660].valid = true; list[660].action = 0;
			list[696].push({true, 0}); list[696].push({true, 6}); list[696].push({true, 14});
			list[696].valid = true; list[696].action = 9;
			list[697].push({false, 9}); list[697].push({true, 8}); list[697].push({false, 7});
			list[697].valid = true; list[697].action = 10;
			list[698].push({false, 10}); list[698].push({true, 2}); list[698].push({false, 7});
			list[698].valid = true; list[698].action = 0;
			list[734].push({true, 4}); list[734].push({true, 18}); list[734].valid = true; list[734].action = 0;
			list[735].push({true, 4}); list[735].push({true, 18}); list[735].valid = true; list[735].action = 0;
			list[742].push({false, 11}); list[742].push({true, 3}); list[742].push({false, 12});
			list[742].push({true, 9}); list[742].push({true, 19}); list[742].valid = true; list[742].action = 12;
			list[744].push({false, 13}); list[744].push({true, 9}); list[744].push({true, 19});
			list[744].push({true, 6}); list[744].push({false, 14}); list[744].push({true, 1});
			list[744].valid = true; list[744].action = 13;
			list[746].push({false, 15}); list[746].push({true, 9}); list[746].push({true, 19});
			list[746].valid = true; list[746].action = 12;
			list[786].push({false, 12}); list[786].push({true, 9}); list[786].push({true, 19});
			list[786].valid = true; list[786].action = 11;
			list[790].push({false, 16}); list[790].push({true, 8}); list[790].valid = true; list[790].action = 14;
			list[820].push({true, 8}); list[820].push({true, 19}); list[820].valid = true; list[820].action = 0;
			list[822].push({true, 8}); list[822].push({true, 19}); list[822].valid = true; list[822].action = 0;
			list[823].push({true, 8}); list[823].push({true, 19}); list[823].valid = true; list[823].action = 0;
			list[824].valid = true; list[824].action = 0;
			list[828].push({false, 11}); list[828].push({true, 3}); list[828].push({true, 19});
			list[828].valid = true; list[828].action = 0;
			list[849].push({true, 8}); list[849].push({true, 19}); list[849].valid = true; list[849].action = 0;
			list[850].push({true, 8}); list[850].push({true, 19}); list[850].valid = true; list[850].action = 0;
			list[851].push({true, 8}); list[851].push({true, 19}); list[851].valid = true; list[851].action = 0;
			list[852].push({true, 8}); list[852].push({true, 19}); list[852].valid = true; list[852].action = 0;
			list[853].push({true, 8}); list[853].push({true, 19}); list[853].valid = true; list[853].action = 0;
			list[854].push({true, 8}); list[854].push({true, 19}); list[854].valid = true; list[854].action = 0;
			list[855].push({true, 8}); list[855].push({true, 19}); list[855].valid = true; list[855].action = 0;
			list[856].push({true, 8}); list[856].push({true, 19}); list[856].valid = true; list[856].action = 0;
			list[857].push({true, 8}); list[857].push({true, 19}); list[857].valid = true; list[857].action = 0;
			list[858].push({true, 8}); list[858].push({true, 19}); list[858].valid = true; list[858].action = 0;
			list[859].push({true, 8}); list[859].push({true, 19}); list[859].valid = true; list[859].action = 0;
			list[892].push({false, 32}); list[892].push({false, 17}); list[892].push({true, 21});
			list[892].push({true, 21}); list[892].push({true, 22}); list[892].push({false, 18});
			list[892].valid = true; list[892].action = 0;
			list[893].push({false, 33}); list[893].push({false, 17}); list[893].push({true, 21});
			list[893].push({true, 21}); list[893].push({true, 22}); list[893].push({false, 18});
			list[893].valid = true; list[893].action = 0;
			list[894].push({false, 34}); list[894].push({false, 17}); list[894].push({true, 21});
			list[894].push({true, 21}); list[894].push({true, 22}); list[894].push({false, 18});
			list[894].valid = true; list[894].action = 0;
			list[906].push({false, 3}); list[906].valid = true; list[906].action = 24;
			list[949].push({true, 23}); list[949].push({true, 22}); list[949].valid = true; list[949].action = 0;
			list[964].valid = true; list[964].action = 0;
			list[966].push({true, 23}); list[966].push({true, 22}); list[966].valid = true; list[966].action = 0;
			list[967].push({true, 23}); list[967].push({true, 22}); list[967].valid = true; list[967].action = 0;
			list[968].push({true, 23}); list[968].push({true, 22}); list[968].valid = true; list[968].action = 0;
			list[969].push({true, 23}); list[969].push({true, 22}); list[969].valid = true; list[969].action = 0;
			list[992].push({false, 3}); list[992].valid = true; list[992].action = 24;
			list[1009].push({false, 20}); list[1009].valid = true; list[1009].action = 25;
			list[1010].push({false, 21}); list[1010].valid = true; list[1010].action = 26;
			list[1011].push({false, 22}); list[1011].valid = true; list[1011].action = 27;
			list[1012].push({false, 23}); list[1012].valid = true; list[1012].action = 28;
			list[1067].push({false, 35}); list[1067].push({true, 25}); list[1067].push({true, 45});
			list[1067].push({false, 29}); list[1067].push({false, 30}); list[1067].valid = true; list[1067].action = 0;
			list[1068].push({false, 36}); list[1068].push({true, 29}); list[1068].push({true, 51});
			list[1068].push({true, 52}); list[1068].valid = true; list[1068].action = 0;
			list[1069].push({false, 37}); list[1069].push({true, 26}); list[1069].push({false, 29});
			list[1069].push({false, 30}); list[1069].push({true, 46}); list[1069].valid = true; list[1069].action = 0;
			list[1070].push({false, 38}); list[1070].push({true, 27}); list[1070].push({true, 47});
			list[1070].push({true, 48}); list[1070].valid = true; list[1070].action = 0;
			list[1071].push({false, 39}); list[1071].push({true, 28}); list[1071].push({true, 49});
			list[1071].push({true, 50}); list[1071].valid = true; list[1071].action = 0;
			list[1072].push({false, 40}); list[1072].push({true, 30}); list[1072].push({true, 53});
			list[1072].push({true, 54}); list[1072].push({true, 55}); list[1072].valid = true; list[1072].action = 0;
			list[1073].push({false, 41}); list[1073].push({true, 31}); list[1073].push({false, 29});
			list[1073].push({false, 30}); list[1073].push({true, 56}); list[1073].push({true, 57});
			list[1073].valid = true; list[1073].action = 0;
			list[1074].push({false, 42}); list[1074].push({true, 32}); list[1074].push({true, 58});
			list[1074].push({false, 29}); list[1074].push({false, 30}); list[1074].push({true, 59});
			list[1074].push({true, 60}); list[1074].valid = true; list[1074].action = 0;
			list[1092].push({false, 17}); list[1092].push({true, 33}); list[1092].push({false, 19});
			list[1092].push({true, 39}); list[1092].push({false, 19}); list[1092].push({true, 40});
			list[1092].push({false, 18}); list[1092].valid = true; list[1092].action = 0;
			list[1135].push({false, 17}); list[1135].push({true, 35}); list[1135].push({false, 19});
			list[1135].push({true, 39}); list[1135].push({false, 19}); list[1135].push({true, 40});
			list[1135].push({false, 18}); list[1135].valid = true; list[1135].action = 0;
			list[1178].push({false, 17}); list[1178].push({true, 36}); list[1178].push({false, 19});
			list[1178].push({true, 39}); list[1178].push({false, 19}); list[1178].push({true, 40});
			list[1178].push({false, 18}); list[1178].valid = true; list[1178].action = 0;
			list[1221].push({false, 17}); list[1221].push({true, 36}); list[1221].push({false, 19});
			list[1221].push({true, 39}); list[1221].push({false, 19}); list[1221].push({true, 40});
			list[1221].push({false, 18}); list[1221].valid = true; list[1221].action = 0;
			list[1264].push({false, 17}); list[1264].push({true, 33}); list[1264].push({false, 19});
			list[1264].push({true, 39}); list[1264].push({false, 19}); list[1264].push({true, 40});
			list[1264].push({false, 18}); list[1264].valid = true; list[1264].action = 0;
			list[1307].push({false, 17}); list[1307].push({true, 34}); list[1307].push({false, 19});
			list[1307].push({true, 39}); list[1307].push({false, 19}); list[1307].push({true, 40});
			list[1307].push({false, 18}); list[1307].valid = true; list[1307].action = 0;
			list[1350].push({false, 17}); list[1350].push({true, 34}); list[1350].push({false, 19});
			list[1350].push({true, 35}); list[1350].push({false, 19}); list[1350].push({true, 39});
			list[1350].push({false, 19}); list[1350].push({true, 40}); list[1350].push({false, 18});
			list[1350].valid = true; list[1350].action = 0;
			list[1393].push({false, 17}); list[1393].push({true, 34}); list[1393].push({false, 19});
			list[1393].push({true, 37}); list[1393].push({false, 19}); list[1393].push({true, 38});
			list[1393].push({false, 19}); list[1393].push({true, 38}); list[1393].push({false, 19});
			list[1393].push({true, 39}); list[1393].push({false, 19}); list[1393].push({true, 40});
			list[1393].push({false, 18}); list[1393].valid = true; list[1393].action = 0;
			list[1422].push({true, 44}); list[1422].push({true, 42}); list[1422].valid = true; list[1422].action = 30;
			list[1438].valid = true; list[1438].action = 31;
			list[1439].push({true, 44}); list[1439].push({true, 42}); list[1439].valid = true; list[1439].action = 30;
			list[1440].push({true, 44}); list[1440].push({true, 42}); list[1440].valid = true; list[1440].action = 30;
			list[1465].push({true, 43}); list[1465].push({true, 41}); list[1465].valid = true; list[1465].action = 30;
			list[1508].push({true, 43}); list[1508].push({true, 41}); list[1508].valid = true; list[1508].action = 30;
			list[1551].push({true, 44}); list[1551].push({true, 42}); list[1551].valid = true; list[1551].action = 30;
			list[1568].push({true, 44}); list[1568].push({true, 42}); list[1568].valid = true; list[1568].action = 30;
			list[1569].push({true, 44}); list[1569].push({true, 42}); list[1569].valid = true; list[1569].action = 30;
			list[1594].push({true, 43}); list[1594].push({true, 41}); list[1594].valid = true; list[1594].action = 30;
			list[1637].push({true, 44}); list[1637].push({true, 42}); list[1637].valid = true; list[1637].action = 30;
			list[1654].push({true, 44}); list[1654].push({true, 42}); list[1654].valid = true; list[1654].action = 30;
			list[1655].push({true, 44}); list[1655].push({true, 42}); list[1655].valid = true; list[1655].action = 30;
			list[1680].push({true, 43}); list[1680].push({true, 41}); list[1680].valid = true; list[1680].action = 30;
			list[1696].valid = true; list[1696].action = 32;
			list[1723].push({true, 43}); list[1723].push({true, 41}); list[1723].valid = true; list[1723].action = 30;
			list[1738].valid = true; list[1738].action = 33;
			list[1766].push({true, 44}); list[1766].push({true, 42}); list[1766].valid = true; list[1766].action = 0;
			list[1781].valid = true; list[1781].action = 37;
			list[1782].valid = true; list[1782].action = 37;
			list[1783].push({true, 44}); list[1783].push({true, 42}); list[1783].valid = true; list[1783].action = 0;
			list[1784].push({true, 44}); list[1784].push({true, 42}); list[1784].valid = true; list[1784].action = 0;
			list[1809].push({true, 44}); list[1809].valid = true; list[1809].action = 0;
			list[1824].valid = true; list[1824].action = 38;
			list[1825].valid = true; list[1825].action = 38;
			list[1826].push({true, 44}); list[1826].valid = true; list[1826].action = 0;
			list[1827].push({true, 44}); list[1827].valid = true; list[1827].action = 0;
			list[1852].push({false, 3}); list[1852].valid = true; list[1852].action = 34;
			list[1895].push({false, 3}); list[1895].valid = true; list[1895].action = 34;
			list[1912].push({false, 20}); list[1912].valid = true; list[1912].action = 36;
			list[1913].push({false, 21}); list[1913].valid = true; list[1913].action = 35;
			list[1960].push({true, 66}); list[1960].push({true, 61}); list[1960].push({true, 68});
			list[1960].push({true, 67}); list[1960].valid = true; list[1960].action = 0;
			list[1962].push({true, 66}); list[1962].push({true, 61}); list[1962].push({true, 68});
			list[1962].push({true, 67}); list[1962].valid = true; list[1962].action = 0;
			list[2003].push({true, 66}); list[2003].push({true, 61}); list[2003].push({true, 68});
			list[2003].push({true, 67}); list[2003].valid = true; list[2003].action = 0;
			list[2005].push({true, 66}); list[2005].push({true, 61}); list[2005].push({true, 68});
			list[2005].push({true, 67}); list[2005].valid = true; list[2005].action = 0;
			list[2046].push({true, 66}); list[2046].push({true, 61}); list[2046].push({true, 67});
			list[2046].valid = true; list[2046].action = 0;
			list[2048].push({true, 66}); list[2048].push({true, 61}); list[2048].push({true, 67});
			list[2048].valid = true; list[2048].action = 0;
			list[2089].push({true, 66}); list[2089].push({true, 61}); list[2089].push({true, 68});
			list[2089].push({true, 67}); list[2089].valid = true; list[2089].action = 0;
			list[2091].push({true, 66}); list[2091].push({true, 61}); list[2091].push({true, 68});
			list[2091].push({true, 67}); list[2091].valid = true; list[2091].action = 0;
			list[2132].push({true, 66}); list[2132].push({true, 61}); list[2132].push({true, 67});
			list[2132].valid = true; list[2132].action = 0;
			list[2134].push({true, 66}); list[2134].push({true, 61}); list[2134].push({true, 67});
			list[2134].valid = true; list[2134].action = 0;
			list[2175].push({true, 66}); list[2175].push({true, 61}); list[2175].push({true, 68});
			list[2175].push({true, 67}); list[2175].valid = true; list[2175].action = 0;
			list[2177].push({true, 66}); list[2177].push({true, 61}); list[2177].push({true, 68});
			list[2177].push({true, 67}); list[2177].valid = true; list[2177].action = 0;
			list[2218].push({true, 66}); list[2218].push({true, 62}); list[2218].push({true, 67});
			list[2218].valid = true; list[2218].action = 0;
			list[2220].push({true, 66}); list[2220].push({true, 62}); list[2220].push({true, 67});
			list[2220].valid = true; list[2220].action = 0;
			list[2261].push({true, 66}); list[2261].push({true, 62}); list[2261].push({true, 68});
			list[2261].push({true, 63}); list[2261].push({true, 67}); list[2261].valid = true; list[2261].action = 0;
			list[2263].push({true, 66}); list[2263].push({true, 62}); list[2263].push({true, 68});
			list[2263].push({true, 63}); list[2263].push({true, 67}); list[2263].valid = true; list[2263].action = 0;
			list[2304].push({true, 66}); list[2304].push({true, 62}); list[2304].push({true, 67});
			list[2304].valid = true; list[2304].action = 0;
			list[2306].push({true, 66}); list[2306].push({true, 62}); list[2306].push({true, 67});
			list[2306].valid = true; list[2306].action = 0;
			list[2347].push({true, 66}); list[2347].push({true, 62}); list[2347].push({true, 67});
			list[2347].valid = true; list[2347].action = 0;
			list[2349].push({true, 66}); list[2349].push({true, 62}); list[2349].push({true, 67});
			list[2349].valid = true; list[2349].action = 0;
			list[2390].push({true, 66}); list[2390].push({true, 62}); list[2390].push({true, 68});
			list[2390].push({true, 63}); list[2390].push({true, 67}); list[2390].valid = true; list[2390].action = 0;
			list[2392].push({true, 66}); list[2392].push({true, 62}); list[2392].push({true, 68});
			list[2392].push({true, 63}); list[2392].push({true, 67}); list[2392].valid = true; list[2392].action = 0;
			list[2433].push({true, 66}); list[2433].push({true, 62}); list[2433].push({true, 67});
			list[2433].valid = true; list[2433].action = 0;
			list[2435].push({true, 66}); list[2435].push({true, 62}); list[2435].push({true, 67});
			list[2435].valid = true; list[2435].action = 0;
			list[2476].push({true, 66}); list[2476].push({true, 62}); list[2476].push({true, 68});
			list[2476].push({true, 63}); list[2476].push({true, 67}); list[2476].valid = true; list[2476].action = 0;
			list[2478].push({true, 66}); list[2478].push({true, 62}); list[2478].push({true, 68});
			list[2478].push({true, 63}); list[2478].push({true, 67}); list[2478].valid = true; list[2478].action = 0;
			list[2519].push({true, 66}); list[2519].push({true, 62}); list[2519].push({true, 67});
			list[2519].valid = true; list[2519].action = 0;
			list[2521].push({true, 66}); list[2521].push({true, 62}); list[2521].push({true, 67});
			list[2521].valid = true; list[2521].action = 0;
			list[2562].push({true, 66}); list[2562].push({true, 62}); list[2562].push({true, 67});
			list[2562].valid = true; list[2562].action = 0;
			list[2564].push({true, 66}); list[2564].push({true, 62}); list[2564].push({true, 67});
			list[2564].valid = true; list[2564].action = 0;
			list[2605].push({true, 66}); list[2605].push({true, 62}); list[2605].push({true, 68});
			list[2605].push({true, 63}); list[2605].push({true, 67}); list[2605].valid = true; list[2605].action = 0;
			list[2607].push({true, 66}); list[2607].push({true, 62}); list[2607].push({true, 68});
			list[2607].push({true, 63}); list[2607].push({true, 67}); list[2607].valid = true; list[2607].action = 0;
			list[2626].push({true, 65}); list[2626].valid = true; list[2626].action = 39;
			list[2643].push({true, 65}); list[2643].valid = true; list[2643].action = 39;
			list[2644].push({true, 65}); list[2644].valid = true; list[2644].action = 39;
			list[2645].push({false, 22}); list[2645].valid = true; list[2645].action = 43;
			list[2646].push({false, 23}); list[2646].valid = true; list[2646].action = 44;
			list[2649].valid = true; list[2649].action = 40;
			list[2651].valid = true; list[2651].action = 40;
			list[2654].valid = true; list[2654].action = 40;
			list[2669].push({true, 65}); list[2669].push({false, 19}); list[2669].push({true, 64});
			list[2669].valid = true; list[2669].action = 39;
			list[2686].push({true, 65}); list[2686].push({false, 19}); list[2686].push({true, 64});
			list[2686].valid = true; list[2686].action = 39;
			list[2687].push({true, 65}); list[2687].push({false, 19}); list[2687].push({true, 64});
			list[2687].valid = true; list[2687].action = 39;
			list[2688].push({false, 22}); list[2688].push({false, 19}); list[2688].push({false, 23});
			list[2688].valid = true; list[2688].action = 45;
			list[2689].push({false, 23}); list[2689].push({false, 19}); list[2689].push({false, 22});
			list[2689].valid = true; list[2689].action = 46;
			list[2692].valid = true; list[2692].action = 41;
			list[2694].valid = true; list[2694].action = 41;
			list[2697].valid = true; list[2697].action = 41;
			list[2712].push({true, 65}); list[2712].push({false, 19}); list[2712].push({true, 64});
			list[2712].valid = true; list[2712].action = 39;
			list[2729].push({true, 65}); list[2729].push({false, 19}); list[2729].push({true, 64});
			list[2729].valid = true; list[2729].action = 39;
			list[2730].push({true, 65}); list[2730].push({false, 19}); list[2730].push({true, 64});
			list[2730].valid = true; list[2730].action = 39;
			list[2731].push({false, 22}); list[2731].push({false, 19}); list[2731].push({false, 23});
			list[2731].valid = true; list[2731].action = 45;
			list[2732].push({false, 23}); list[2732].push({false, 19}); list[2732].push({false, 22});
			list[2732].valid = true; list[2732].action = 46;
			list[2735].valid = true; list[2735].action = 42;
			list[2737].valid = true; list[2737].action = 42;
			list[2755].push({true, 65}); list[2755].valid = true; list[2755].action = 0;
			list[2772].push({true, 65}); list[2772].valid = true; list[2772].action = 0;
			list[2773].push({true, 65}); list[2773].valid = true; list[2773].action = 0;
			list[2776].push({false, 24}); list[2776].valid = true; list[2776].action = 50;
			list[2798].push({false, 3}); list[2798].valid = true; list[2798].action = 47;
			list[2815].push({false, 20}); list[2815].valid = true; list[2815].action = 49;
			list[2816].push({false, 21}); list[2816].valid = true; list[2816].action = 48;
			list[2863].push({false, 25}); list[2863].valid = true; list[2863].action = 51;
			list[2865].push({false, 27}); list[2865].valid = true; list[2865].action = 52;
			list[2907].push({false, 26}); list[2907].valid = true; list[2907].action = 53;
			list[2909].push({false, 28}); list[2909].valid = true; list[2909].action = 54;
			list[2955].push({false, 31}); list[2955].valid = true; list[2955].action = 55;
		}

		nik_ce cprod_type & production(csymbol_type & row, ctoken_type col) const
			{ return list[row.token() * col_size + col]; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

