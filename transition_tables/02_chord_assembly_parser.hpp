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
		nik_ces auto row_size		= 57;
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

			list[3].push({true, 9}); list[3].push({true, 1}); list[3].push({true, 11});
			list[3].push({true, 2}); list[3].push({true, 3}); list[3].valid = true; list[3].action = 0;
			list[46].push({true, 10}); list[46].push({true, 1}); list[46].valid = true; list[46].action = 0;
			list[51].valid = true; list[51].action = 0;
			list[95].push({true, 12}); list[95].push({true, 14}); list[95].push({true, 4});
			list[95].valid = true; list[95].action = 0;
			list[131].valid = true; list[131].action = 0;
			list[138].push({true, 2}); list[138].push({true, 3}); list[138].valid = true; list[138].action = 0;
			list[175].push({true, 7}); list[175].push({true, 5}); list[175].push({true, 6});
			list[175].valid = true; list[175].action = 0;
			list[177].push({true, 7}); list[177].push({true, 5}); list[177].push({true, 6});
			list[177].valid = true; list[177].action = 0;
			list[182].push({true, 15}); list[182].push({true, 41}); list[182].push({true, 16});
			list[182].valid = true; list[182].action = 0;
			list[185].push({true, 7}); list[185].push({true, 5}); list[185].push({true, 6});
			list[185].valid = true; list[185].action = 0;
			list[187].push({true, 7}); list[187].push({true, 5}); list[187].push({true, 6});
			list[187].valid = true; list[187].action = 0;
			list[189].push({true, 7}); list[189].push({true, 5}); list[189].push({true, 6});
			list[189].valid = true; list[189].action = 0;
			list[218].push({true, 7}); list[218].push({true, 5}); list[218].valid = true; list[218].action = 0;
			list[220].push({true, 7}); list[220].push({true, 5}); list[220].valid = true; list[220].action = 0;
			list[224].valid = true; list[224].action = 0;
			list[225].valid = true; list[225].action = 0;
			list[226].valid = true; list[226].action = 0;
			list[227].valid = true; list[227].action = 0;
			list[228].push({true, 7}); list[228].push({true, 5}); list[228].valid = true; list[228].action = 0;
			list[230].push({true, 7}); list[230].push({true, 5}); list[230].valid = true; list[230].action = 0;
			list[232].push({true, 7}); list[232].push({true, 5}); list[232].valid = true; list[232].action = 0;
			list[267].push({true, 13}); list[267].push({true, 14}); list[267].push({true, 7});
			list[267].push({true, 5}); list[267].push({true, 6}); list[267].valid = true; list[267].action = 0;
			list[268].push({true, 15}); list[268].push({true, 41}); list[268].push({true, 16});
			list[268].valid = true; list[268].action = 0;
			list[269].push({true, 17}); list[269].push({true, 18}); list[269].push({true, 19});
			list[269].valid = true; list[269].action = 0;
			list[270].push({true, 20}); list[270].push({true, 21}); list[270].push({true, 22});
			list[270].valid = true; list[270].action = 0;
			list[304].push({true, 23}); list[304].push({true, 8}); list[304].valid = true; list[304].action = 0;
			list[306].push({true, 23}); list[306].push({true, 8}); list[306].valid = true; list[306].action = 0;
			list[314].push({false, 13}); list[314].push({true, 24}); list[314].push({false, 14});
			list[314].push({true, 37}); list[314].push({true, 38}); list[314].push({true, 25});
			list[314].valid = true; list[314].action = 0;
			list[316].push({true, 26}); list[316].push({true, 37}); list[316].push({true, 38});
			list[316].push({true, 27}); list[316].push({true, 28}); list[316].push({true, 29});
			list[316].push({true, 30}); list[316].valid = true; list[316].action = 0;
			list[318].push({true, 31}); list[318].push({true, 37}); list[318].push({true, 38});
			list[318].push({true, 32}); list[318].valid = true; list[318].action = 0;
			list[358].push({true, 33}); list[358].push({true, 37}); list[358].push({true, 38});
			list[358].push({true, 34}); list[358].valid = true; list[358].action = 0;
			list[362].push({true, 35}); list[362].push({true, 41}); list[362].push({true, 36});
			list[362].valid = true; list[362].action = 0;
			list[390].push({false, 3}); list[390].valid = true; list[390].action = 1;
			list[433].push({false, 3}); list[433].valid = true; list[433].action = 2;
			list[481].push({false, 8}); list[481].valid = true; list[481].action = 3;
			list[525].push({false, 9}); list[525].valid = true; list[525].action = 4;
			list[568].push({false, 9}); list[568].valid = true; list[568].action = 5;
			list[610].push({false, 8}); list[610].valid = true; list[610].action = 0;
			list[655].push({false, 10}); list[655].valid = true; list[655].action = 6;
			list[696].push({false, 8}); list[696].valid = true; list[696].action = 7;
			list[742].push({false, 11}); list[742].valid = true; list[742].action = 8;
			list[777].push({false, 3}); list[777].valid = true; list[777].action = 9;
			list[825].push({false, 8}); list[825].valid = true; list[825].action = 10;
			list[872].push({false, 12}); list[872].valid = true; list[872].action = 11;
			list[906].push({false, 3}); list[906].valid = true; list[906].action = 12;
			list[954].push({false, 8}); list[954].valid = true; list[954].action = 13;
			list[992].push({false, 3}); list[992].valid = true; list[992].action = 14;
			list[994].push({false, 5}); list[994].valid = true; list[994].action = 15;
			list[1035].push({false, 3}); list[1035].valid = true; list[1035].action = 16;
			list[1083].push({false, 8}); list[1083].valid = true; list[1083].action = 17;
			list[1133].push({false, 15}); list[1133].valid = true; list[1133].action = 18;
			list[1169].push({false, 8}); list[1169].valid = true; list[1169].action = 19;
			list[1220].push({false, 16}); list[1220].valid = true; list[1220].action = 20;
			list[1250].push({false, 3}); list[1250].valid = true; list[1250].action = 21;
			list[1298].push({false, 8}); list[1298].valid = true; list[1298].action = 22;
			list[1350].push({false, 17}); list[1350].valid = true; list[1350].action = 23;
			list[1384].push({false, 8}); list[1384].valid = true; list[1384].action = 24;
			list[1433].push({false, 14}); list[1433].valid = true; list[1433].action = 27;
			list[1470].push({false, 8}); list[1470].valid = true; list[1470].action = 28;
			list[1523].push({false, 18}); list[1523].valid = true; list[1523].action = 25;
			list[1556].push({false, 8}); list[1556].valid = true; list[1556].action = 26;
			list[1594].push({false, 3}); list[1594].valid = true; list[1594].action = 29;
			list[1597].push({false, 6}); list[1597].valid = true; list[1597].action = 30;
			list[1598].push({false, 7}); list[1598].valid = true; list[1598].action = 31;
			list[1637].push({true, 39}); list[1637].push({true, 38}); list[1637].valid = true; list[1637].action = 0;
			list[1640].push({true, 39}); list[1640].push({true, 38}); list[1640].valid = true; list[1640].action = 0;
			list[1641].push({true, 39}); list[1641].push({true, 38}); list[1641].valid = true; list[1641].action = 0;
			list[1642].valid = true; list[1642].action = 0;
			list[1647].push({false, 13}); list[1647].push({true, 40}); list[1647].push({true, 38});
			list[1647].valid = true; list[1647].action = 0;
			list[1680].push({false, 3}); list[1680].valid = true; list[1680].action = 32;
			list[1683].push({false, 6}); list[1683].valid = true; list[1683].action = 33;
			list[1684].push({false, 7}); list[1684].valid = true; list[1684].action = 34;
			list[1723].push({false, 3}); list[1723].valid = true; list[1723].action = 35;
			list[1766].push({false, 3}); list[1766].valid = true; list[1766].action = 36;
			list[1769].push({false, 6}); list[1769].valid = true; list[1769].action = 37;
			list[1770].push({false, 7}); list[1770].valid = true; list[1770].action = 38;
			list[1798].push({true, 42}); list[1798].valid = true; list[1798].action = 39;
			list[1799].push({true, 42}); list[1799].valid = true; list[1799].action = 39;
			list[1800].push({true, 42}); list[1800].valid = true; list[1800].action = 39;
			list[1841].push({false, 35}); list[1841].push({false, 28}); list[1841].push({true, 43});
			list[1841].push({false, 29}); list[1841].push({true, 45}); list[1841].push({true, 44});
			list[1841].push({true, 47}); list[1841].push({true, 46}); list[1841].valid = true; list[1841].action = 0;
			list[1842].push({false, 36}); list[1842].push({false, 28}); list[1842].push({true, 43});
			list[1842].push({false, 29}); list[1842].push({true, 49}); list[1842].push({true, 44});
			list[1842].push({true, 51}); list[1842].push({true, 50}); list[1842].valid = true; list[1842].action = 0;
			list[1843].push({false, 37}); list[1843].push({false, 28}); list[1843].push({true, 43});
			list[1843].push({false, 29}); list[1843].push({true, 53}); list[1843].push({true, 44});
			list[1843].push({true, 55}); list[1843].push({true, 54}); list[1843].valid = true; list[1843].action = 0;
			list[1853].push({false, 4}); list[1853].valid = true; list[1853].action = 41;
			list[1895].push({false, 3}); list[1895].valid = true; list[1895].action = 42;
			list[1914].push({false, 22}); list[1914].valid = true; list[1914].action = 43;
			list[1915].push({false, 23}); list[1915].valid = true; list[1915].action = 44;
			list[1917].push({false, 25}); list[1917].valid = true; list[1917].action = 45;
			list[1918].push({false, 26}); list[1918].valid = true; list[1918].action = 46;
			list[1967].push({false, 32}); list[1967].valid = true; list[1967].action = 47;
			list[2011].push({false, 33}); list[2011].valid = true; list[2011].action = 48;
			list[2025].push({true, 48}); list[2025].push({true, 47}); list[2025].valid = true; list[2025].action = 0;
			list[2054].valid = true; list[2054].action = 0;
			list[2068].push({false, 4}); list[2068].valid = true; list[2068].action = 49;
			list[2139].push({false, 32}); list[2139].valid = true; list[2139].action = 50;
			list[2183].push({false, 33}); list[2183].valid = true; list[2183].action = 51;
			list[2196].push({true, 52}); list[2196].push({true, 51}); list[2196].valid = true; list[2196].action = 0;
			list[2215].push({true, 52}); list[2215].push({true, 51}); list[2215].valid = true; list[2215].action = 0;
			list[2216].push({true, 52}); list[2216].push({true, 51}); list[2216].valid = true; list[2216].action = 0;
			list[2218].push({true, 52}); list[2218].push({true, 51}); list[2218].valid = true; list[2218].action = 0;
			list[2219].push({true, 52}); list[2219].push({true, 51}); list[2219].valid = true; list[2219].action = 0;
			list[2226].valid = true; list[2226].action = 0;
			list[2239].push({false, 3}); list[2239].valid = true; list[2239].action = 52;
			list[2258].push({false, 22}); list[2258].valid = true; list[2258].action = 53;
			list[2259].push({false, 23}); list[2259].valid = true; list[2259].action = 54;
			list[2261].push({false, 25}); list[2261].valid = true; list[2261].action = 55;
			list[2262].push({false, 26}); list[2262].valid = true; list[2262].action = 56;
			list[2311].push({false, 32}); list[2311].valid = true; list[2311].action = 57;
			list[2355].push({false, 33}); list[2355].valid = true; list[2355].action = 58;
			list[2368].push({true, 56}); list[2368].push({true, 55}); list[2368].valid = true; list[2368].action = 0;
			list[2398].valid = true; list[2398].action = 0;
			list[2411].push({false, 3}); list[2411].valid = true; list[2411].action = 59;
		}

		nik_ce cprod_type & production(csymbol_type & row, ctoken_type col) const
			{ return list[row.token() * col_size + col]; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

