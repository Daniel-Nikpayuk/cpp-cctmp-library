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

// hustle:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automaton:

/***********************************************************************************************************************/

// interface:

	template<typename T_grammar>
	struct T_hustle_pda
	{
		using ActName			= typename T_grammar::ActName;
		using T_lexer			= typename T_grammar::T_lexer;
		using Token			= typename T_grammar::Token;

		nik_ces auto start_index	= 0;
		nik_ces auto row_size		= 40;
		nik_ces auto col_size		= 38;

		nik_ces auto prod_size		= cctmp::string_literal("d(S)TB").size(); // needs refining.

		nik_ces auto stack_finish	= symbol_type{generator::Sign::terminal, Token::prompt};
		nik_ces auto stack_start	= symbol_type{generator::Sign::nonterminal, start_index};

		nik_ces auto stack_size		= cctmp::literal("F{C|A|M|P}YPZ<>YPZYP,PZV;HGO").size(); // needs refining.
							// literal is intentional.
							// this is the longest possible sentential.
							// might need updating.

		using prod_type			= generator::Production<prod_size>;
		using cprod_type		= prod_type const;
		using list_type			= cctmp::array<prod_type, row_size * col_size>;

		list_type list; // list instead of table due to clang bug.
		bool ambiguous;

		nik_ce T_hustle_pda() : ambiguous{}
		{
			list.fullsize();

			list[27].push({false, 27}); list[27].push({true, 1}); list[27].push({false, 28});
			list[27].valid = true; list[27].action = 0;
			list[57].push({false, 19}); list[57].push({true, 3}); list[57].push({true, 2});
			list[57].push({false, 27}); list[57].push({true, 4}); list[57].push({false, 28});
			list[57].valid = true; list[57].action = 0;
			list[63].push({true, 4}); list[63].valid = true; list[63].action = 0;
			list[81].push({true, 3}); list[81].push({true, 2}); list[81].valid = true; list[81].action = 0;
			list[103].valid = true; list[103].action = 0;
			list[119].push({false, 5}); list[119].valid = true; list[119].action = 1;
			list[177].push({false, 25}); list[177].push({false, 27}); list[177].push({true, 5});
			list[177].push({false, 28}); list[177].push({true, 10}); list[177].push({true, 8});
			list[177].valid = true; list[177].action = 0;
			list[195].push({false, 5}); list[195].push({true, 6}); list[195].valid = true; list[195].action = 2;
			list[233].push({true, 7}); list[233].push({true, 6}); list[233].valid = true; list[233].action = 0;
			list[256].valid = true; list[256].action = 0;
			list[271].push({false, 5}); list[271].valid = true; list[271].action = 4;
			list[309].push({true, 17}); list[309].push({true, 9}); list[309].valid = true; list[309].action = 9;
			list[312].push({true, 17}); list[312].push({true, 9}); list[312].valid = true; list[312].action = 9;
			list[313].push({true, 17}); list[313].push({true, 9}); list[313].valid = true; list[313].action = 9;
			list[314].push({true, 17}); list[314].push({true, 9}); list[314].valid = true; list[314].action = 9;
			list[315].push({true, 17}); list[315].push({true, 9}); list[315].valid = true; list[315].action = 9;
			list[316].push({true, 17}); list[316].push({true, 9}); list[316].valid = true; list[316].action = 9;
			list[317].push({true, 17}); list[317].push({true, 9}); list[317].valid = true; list[317].action = 9;
			list[331].push({true, 17}); list[331].push({true, 9}); list[331].valid = true; list[331].action = 9;
			list[333].push({true, 17}); list[333].push({true, 9}); list[333].valid = true; list[333].action = 9;
			list[334].push({true, 17}); list[334].push({true, 9}); list[334].valid = true; list[334].action = 9;
			list[335].push({true, 17}); list[335].push({true, 9}); list[335].valid = true; list[335].action = 9;
			list[336].push({true, 17}); list[336].push({true, 9}); list[336].valid = true; list[336].action = 9;
			list[337].push({true, 17}); list[337].push({true, 9}); list[337].valid = true; list[337].action = 9;
			list[338].push({true, 17}); list[338].push({true, 9}); list[338].valid = true; list[338].action = 9;
			list[339].push({true, 17}); list[339].push({true, 9}); list[339].valid = true; list[339].action = 9;
			list[340].push({true, 17}); list[340].push({true, 9}); list[340].valid = true; list[340].action = 9;
			list[341].push({true, 17}); list[341].push({true, 9}); list[341].valid = true; list[341].action = 9;
			list[347].push({true, 17}); list[347].push({true, 9}); list[347].valid = true; list[347].action = 0;
			list[350].push({true, 17}); list[350].push({true, 9}); list[350].valid = true; list[350].action = 0;
			list[351].push({true, 17}); list[351].push({true, 9}); list[351].valid = true; list[351].action = 0;
			list[352].push({true, 17}); list[352].push({true, 9}); list[352].valid = true; list[352].action = 0;
			list[353].push({true, 17}); list[353].push({true, 9}); list[353].valid = true; list[353].action = 0;
			list[354].push({true, 17}); list[354].push({true, 9}); list[354].valid = true; list[354].action = 0;
			list[355].push({true, 17}); list[355].push({true, 9}); list[355].valid = true; list[355].action = 0;
			list[369].push({true, 17}); list[369].push({true, 9}); list[369].valid = true; list[369].action = 0;
			list[370].valid = true; list[370].action = 3;
			list[371].push({true, 17}); list[371].push({true, 9}); list[371].valid = true; list[371].action = 0;
			list[372].push({true, 17}); list[372].push({true, 9}); list[372].valid = true; list[372].action = 0;
			list[373].push({true, 17}); list[373].push({true, 9}); list[373].valid = true; list[373].action = 0;
			list[374].push({true, 17}); list[374].push({true, 9}); list[374].valid = true; list[374].action = 0;
			list[375].push({true, 17}); list[375].push({true, 9}); list[375].valid = true; list[375].action = 0;
			list[376].push({true, 17}); list[376].push({true, 9}); list[376].valid = true; list[376].action = 0;
			list[377].push({true, 17}); list[377].push({true, 9}); list[377].valid = true; list[377].action = 0;
			list[378].push({true, 17}); list[378].push({true, 9}); list[378].valid = true; list[378].action = 0;
			list[379].push({true, 17}); list[379].push({true, 9}); list[379].valid = true; list[379].action = 0;
			list[383].push({false, 3}); list[383].push({true, 11}); list[383].valid = true; list[383].action = 0;
			list[385].valid = true; list[385].action = 5;
			list[388].valid = true; list[388].action = 5;
			list[389].valid = true; list[389].action = 5;
			list[390].valid = true; list[390].action = 5;
			list[391].valid = true; list[391].action = 5;
			list[392].valid = true; list[392].action = 5;
			list[393].valid = true; list[393].action = 5;
			list[407].valid = true; list[407].action = 5;
			list[409].valid = true; list[409].action = 5;
			list[410].valid = true; list[410].action = 5;
			list[411].valid = true; list[411].action = 5;
			list[412].valid = true; list[412].action = 5;
			list[413].valid = true; list[413].action = 5;
			list[414].valid = true; list[414].action = 5;
			list[415].valid = true; list[415].action = 5;
			list[416].valid = true; list[416].action = 5;
			list[417].valid = true; list[417].action = 5;
			list[423].push({false, 5}); list[423].valid = true; list[423].action = 6;
			list[464].push({true, 13}); list[464].push({true, 15}); list[464].valid = true; list[464].action = 0;
			list[465].push({true, 13}); list[465].push({true, 15}); list[465].valid = true; list[465].action = 0;
			list[466].push({true, 13}); list[466].push({true, 15}); list[466].valid = true; list[466].action = 0;
			list[467].push({true, 13}); list[467].push({true, 15}); list[467].valid = true; list[467].action = 0;
			list[468].push({true, 13}); list[468].push({true, 15}); list[468].valid = true; list[468].action = 0;
			list[469].push({true, 13}); list[469].push({true, 15}); list[469].valid = true; list[469].action = 0;
			list[502].push({false, 8}); list[502].valid = true; list[502].action = 14;
			list[503].push({false, 9}); list[503].valid = true; list[503].action = 15;
			list[504].push({false, 10}); list[504].valid = true; list[504].action = 16;
			list[505].push({false, 11}); list[505].valid = true; list[505].action = 17;
			list[506].push({false, 12}); list[506].valid = true; list[506].action = 18;
			list[507].push({false, 13}); list[507].valid = true; list[507].action = 19;
			list[537].push({false, 5}); list[537].valid = true; list[537].action = 20;
			list[561].push({false, 29}); list[561].valid = true; list[561].action = 20;
			list[562].push({false, 30}); list[562].valid = true; list[562].action = 20;
			list[563].push({false, 31}); list[563].valid = true; list[563].action = 20;
			list[564].push({false, 32}); list[564].valid = true; list[564].action = 20;
			list[565].push({false, 33}); list[565].valid = true; list[565].action = 20;
			list[566].push({false, 34}); list[566].valid = true; list[566].action = 20;
			list[567].push({false, 35}); list[567].valid = true; list[567].action = 20;
			list[568].push({false, 36}); list[568].valid = true; list[568].action = 20;
			list[569].push({false, 37}); list[569].valid = true; list[569].action = 20;
			list[574].push({false, 4}); list[574].push({true, 16}); list[574].valid = true; list[574].action = 0;
			list[575].valid = true; list[575].action = 12;
			list[578].valid = true; list[578].action = 12;
			list[579].valid = true; list[579].action = 12;
			list[580].valid = true; list[580].action = 12;
			list[581].valid = true; list[581].action = 12;
			list[582].valid = true; list[582].action = 12;
			list[583].valid = true; list[583].action = 12;
			list[597].valid = true; list[597].action = 12;
			list[598].valid = true; list[598].action = 12;
			list[599].valid = true; list[599].action = 12;
			list[600].valid = true; list[600].action = 12;
			list[601].valid = true; list[601].action = 12;
			list[602].valid = true; list[602].action = 12;
			list[603].valid = true; list[603].action = 12;
			list[604].valid = true; list[604].action = 12;
			list[605].valid = true; list[605].action = 12;
			list[606].valid = true; list[606].action = 12;
			list[607].valid = true; list[607].action = 12;
			list[613].push({false, 5}); list[613].valid = true; list[613].action = 13;
			list[651].push({true, 14}); list[651].valid = true; list[651].action = 0;
			list[654].push({true, 12}); list[654].valid = true; list[654].action = 0;
			list[655].push({true, 12}); list[655].valid = true; list[655].action = 0;
			list[656].push({true, 12}); list[656].valid = true; list[656].action = 0;
			list[657].push({true, 12}); list[657].valid = true; list[657].action = 0;
			list[658].push({true, 12}); list[658].valid = true; list[658].action = 0;
			list[659].push({true, 12}); list[659].valid = true; list[659].action = 0;
			list[673].push({false, 27}); list[673].push({true, 18}); list[673].push({false, 28});
			list[673].valid = true; list[673].action = 0;
			list[675].push({true, 14}); list[675].valid = true; list[675].action = 0;
			list[676].push({true, 14}); list[676].valid = true; list[676].action = 0;
			list[677].push({true, 14}); list[677].valid = true; list[677].action = 0;
			list[678].push({true, 14}); list[678].valid = true; list[678].action = 0;
			list[679].push({true, 14}); list[679].valid = true; list[679].action = 0;
			list[680].push({true, 14}); list[680].valid = true; list[680].action = 0;
			list[681].push({true, 14}); list[681].valid = true; list[681].action = 0;
			list[682].push({true, 14}); list[682].valid = true; list[682].action = 0;
			list[683].push({true, 14}); list[683].valid = true; list[683].action = 0;
			list[689].push({true, 28}); list[689].push({true, 29}); list[689].valid = true; list[689].action = 0;
			list[692].push({true, 12}); list[692].valid = true; list[692].action = 0;
			list[693].push({true, 12}); list[693].valid = true; list[693].action = 0;
			list[694].push({true, 12}); list[694].valid = true; list[694].action = 0;
			list[695].push({true, 12}); list[695].valid = true; list[695].action = 0;
			list[696].push({true, 12}); list[696].valid = true; list[696].action = 0;
			list[697].push({true, 12}); list[697].valid = true; list[697].action = 0;
			list[698].push({true, 31}); list[698].push({true, 32}); list[698].push({true, 33});
			list[698].push({true, 34}); list[698].push({true, 35}); list[698].valid = true; list[698].action = 0;
			list[704].push({false, 20}); list[704].push({true, 36}); list[704].push({true, 37});
			list[704].valid = true; list[704].action = 0;
			list[707].push({false, 23}); list[707].push({true, 19}); list[707].valid = true; list[707].action = 0;
			list[708].push({false, 24}); list[708].push({true, 17}); list[708].valid = true; list[708].action = 0;
			list[709].push({false, 25}); list[709].push({true, 20}); list[709].valid = true; list[709].action = 0;
			list[710].push({false, 26}); list[710].push({true, 38}); list[710].push({true, 39});
			list[710].valid = true; list[710].action = 0;
			list[711].push({true, 28}); list[711].push({true, 29}); list[711].valid = true; list[711].action = 0;
			list[713].push({true, 28}); list[713].push({true, 29}); list[713].valid = true; list[713].action = 0;
			list[714].push({true, 28}); list[714].push({true, 29}); list[714].valid = true; list[714].action = 0;
			list[715].push({true, 28}); list[715].push({true, 29}); list[715].valid = true; list[715].action = 0;
			list[716].push({true, 28}); list[716].push({true, 29}); list[716].valid = true; list[716].action = 0;
			list[717].push({true, 28}); list[717].push({true, 29}); list[717].valid = true; list[717].action = 0;
			list[718].push({true, 28}); list[718].push({true, 29}); list[718].valid = true; list[718].action = 0;
			list[719].push({true, 28}); list[719].push({true, 29}); list[719].valid = true; list[719].action = 0;
			list[720].push({true, 28}); list[720].push({true, 29}); list[720].valid = true; list[720].action = 0;
			list[721].push({true, 28}); list[721].push({true, 29}); list[721].valid = true; list[721].action = 0;
			list[727].push({true, 17}); list[727].push({true, 19}); list[727].valid = true; list[727].action = 0;
			list[730].push({true, 17}); list[730].push({true, 19}); list[730].valid = true; list[730].action = 0;
			list[731].push({true, 17}); list[731].push({true, 19}); list[731].valid = true; list[731].action = 0;
			list[732].push({true, 17}); list[732].push({true, 19}); list[732].valid = true; list[732].action = 0;
			list[733].push({true, 17}); list[733].push({true, 19}); list[733].valid = true; list[733].action = 0;
			list[734].push({true, 17}); list[734].push({true, 19}); list[734].valid = true; list[734].action = 0;
			list[735].push({true, 17}); list[735].push({true, 19}); list[735].valid = true; list[735].action = 0;
			list[749].push({true, 17}); list[749].push({true, 19}); list[749].valid = true; list[749].action = 0;
			list[750].valid = true; list[750].action = 0;
			list[751].push({true, 17}); list[751].push({true, 19}); list[751].valid = true; list[751].action = 0;
			list[752].push({true, 17}); list[752].push({true, 19}); list[752].valid = true; list[752].action = 0;
			list[753].push({true, 17}); list[753].push({true, 19}); list[753].valid = true; list[753].action = 0;
			list[754].push({true, 17}); list[754].push({true, 19}); list[754].valid = true; list[754].action = 0;
			list[755].push({true, 17}); list[755].push({true, 19}); list[755].valid = true; list[755].action = 0;
			list[756].push({true, 17}); list[756].push({true, 19}); list[756].valid = true; list[756].action = 0;
			list[757].push({true, 17}); list[757].push({true, 19}); list[757].valid = true; list[757].action = 0;
			list[758].push({true, 17}); list[758].push({true, 19}); list[758].valid = true; list[758].action = 0;
			list[759].push({true, 17}); list[759].push({true, 19}); list[759].valid = true; list[759].action = 0;
			list[765].push({true, 36}); list[765].push({true, 37}); list[765].valid = true; list[765].action = 0;
			list[787].push({false, 27}); list[787].push({true, 21}); list[787].push({false, 28});
			list[787].push({true, 26}); list[787].push({true, 24}); list[787].valid = true; list[787].action = 0;
			list[803].push({false, 5}); list[803].push({true, 22}); list[803].valid = true; list[803].action = 7;
			list[841].push({true, 23}); list[841].push({true, 22}); list[841].valid = true; list[841].action = 0;
			list[864].valid = true; list[864].action = 0;
			list[879].push({false, 5}); list[879].valid = true; list[879].action = 8;
			list[917].push({true, 17}); list[917].push({true, 25}); list[917].valid = true; list[917].action = 9;
			list[920].push({true, 17}); list[920].push({true, 25}); list[920].valid = true; list[920].action = 9;
			list[921].push({true, 17}); list[921].push({true, 25}); list[921].valid = true; list[921].action = 9;
			list[922].push({true, 17}); list[922].push({true, 25}); list[922].valid = true; list[922].action = 9;
			list[923].push({true, 17}); list[923].push({true, 25}); list[923].valid = true; list[923].action = 9;
			list[924].push({true, 17}); list[924].push({true, 25}); list[924].valid = true; list[924].action = 9;
			list[925].push({true, 17}); list[925].push({true, 25}); list[925].valid = true; list[925].action = 9;
			list[939].push({true, 17}); list[939].push({true, 25}); list[939].valid = true; list[939].action = 9;
			list[941].push({true, 17}); list[941].push({true, 25}); list[941].valid = true; list[941].action = 9;
			list[942].push({true, 17}); list[942].push({true, 25}); list[942].valid = true; list[942].action = 9;
			list[943].push({true, 17}); list[943].push({true, 25}); list[943].valid = true; list[943].action = 9;
			list[944].push({true, 17}); list[944].push({true, 25}); list[944].valid = true; list[944].action = 9;
			list[945].push({true, 17}); list[945].push({true, 25}); list[945].valid = true; list[945].action = 9;
			list[946].push({true, 17}); list[946].push({true, 25}); list[946].valid = true; list[946].action = 9;
			list[947].push({true, 17}); list[947].push({true, 25}); list[947].valid = true; list[947].action = 9;
			list[948].push({true, 17}); list[948].push({true, 25}); list[948].valid = true; list[948].action = 9;
			list[949].push({true, 17}); list[949].push({true, 25}); list[949].valid = true; list[949].action = 9;
			list[955].push({true, 17}); list[955].push({true, 25}); list[955].valid = true; list[955].action = 0;
			list[958].push({true, 17}); list[958].push({true, 25}); list[958].valid = true; list[958].action = 0;
			list[959].push({true, 17}); list[959].push({true, 25}); list[959].valid = true; list[959].action = 0;
			list[960].push({true, 17}); list[960].push({true, 25}); list[960].valid = true; list[960].action = 0;
			list[961].push({true, 17}); list[961].push({true, 25}); list[961].valid = true; list[961].action = 0;
			list[962].push({true, 17}); list[962].push({true, 25}); list[962].valid = true; list[962].action = 0;
			list[963].push({true, 17}); list[963].push({true, 25}); list[963].valid = true; list[963].action = 0;
			list[977].push({true, 17}); list[977].push({true, 25}); list[977].valid = true; list[977].action = 0;
			list[978].valid = true; list[978].action = 10;
			list[979].push({true, 17}); list[979].push({true, 25}); list[979].valid = true; list[979].action = 0;
			list[980].push({true, 17}); list[980].push({true, 25}); list[980].valid = true; list[980].action = 0;
			list[981].push({true, 17}); list[981].push({true, 25}); list[981].valid = true; list[981].action = 0;
			list[982].push({true, 17}); list[982].push({true, 25}); list[982].valid = true; list[982].action = 0;
			list[983].push({true, 17}); list[983].push({true, 25}); list[983].valid = true; list[983].action = 0;
			list[984].push({true, 17}); list[984].push({true, 25}); list[984].valid = true; list[984].action = 0;
			list[985].push({true, 17}); list[985].push({true, 25}); list[985].valid = true; list[985].action = 0;
			list[986].push({true, 17}); list[986].push({true, 25}); list[986].valid = true; list[986].action = 0;
			list[987].push({true, 17}); list[987].push({true, 25}); list[987].valid = true; list[987].action = 0;
			list[991].push({false, 3}); list[991].push({true, 27}); list[991].valid = true; list[991].action = 0;
			list[993].valid = true; list[993].action = 0;
			list[996].valid = true; list[996].action = 0;
			list[997].valid = true; list[997].action = 0;
			list[998].valid = true; list[998].action = 0;
			list[999].valid = true; list[999].action = 0;
			list[1000].valid = true; list[1000].action = 0;
			list[1001].valid = true; list[1001].action = 0;
			list[1015].valid = true; list[1015].action = 0;
			list[1017].valid = true; list[1017].action = 0;
			list[1018].valid = true; list[1018].action = 0;
			list[1019].valid = true; list[1019].action = 0;
			list[1020].valid = true; list[1020].action = 0;
			list[1021].valid = true; list[1021].action = 0;
			list[1022].valid = true; list[1022].action = 0;
			list[1023].valid = true; list[1023].action = 0;
			list[1024].valid = true; list[1024].action = 0;
			list[1025].valid = true; list[1025].action = 0;
			list[1031].push({false, 5}); list[1031].valid = true; list[1031].action = 11;
			list[1069].push({true, 14}); list[1069].valid = true; list[1069].action = 21;
			list[1091].push({false, 27}); list[1091].push({true, 18}); list[1091].push({false, 28});
			list[1091].valid = true; list[1091].action = 22;
			list[1093].push({true, 14}); list[1093].valid = true; list[1093].action = 21;
			list[1094].push({true, 14}); list[1094].valid = true; list[1094].action = 21;
			list[1095].push({true, 14}); list[1095].valid = true; list[1095].action = 21;
			list[1096].push({true, 14}); list[1096].valid = true; list[1096].action = 21;
			list[1097].push({true, 14}); list[1097].valid = true; list[1097].action = 21;
			list[1098].push({true, 14}); list[1098].valid = true; list[1098].action = 21;
			list[1099].push({true, 14}); list[1099].valid = true; list[1099].action = 21;
			list[1100].push({true, 14}); list[1100].valid = true; list[1100].action = 21;
			list[1101].push({true, 14}); list[1101].valid = true; list[1101].action = 21;
			list[1107].push({true, 17}); list[1107].push({true, 30}); list[1107].valid = true; list[1107].action = 24;
			list[1110].push({true, 17}); list[1110].push({true, 30}); list[1110].valid = true; list[1110].action = 24;
			list[1111].push({true, 17}); list[1111].push({true, 30}); list[1111].valid = true; list[1111].action = 24;
			list[1112].push({true, 17}); list[1112].push({true, 30}); list[1112].valid = true; list[1112].action = 24;
			list[1113].push({true, 17}); list[1113].push({true, 30}); list[1113].valid = true; list[1113].action = 24;
			list[1114].push({true, 17}); list[1114].push({true, 30}); list[1114].valid = true; list[1114].action = 24;
			list[1115].push({true, 17}); list[1115].push({true, 30}); list[1115].valid = true; list[1115].action = 24;
			list[1129].push({true, 17}); list[1129].push({true, 30}); list[1129].valid = true; list[1129].action = 24;
			list[1130].valid = true; list[1130].action = 25;
			list[1131].push({true, 17}); list[1131].push({true, 30}); list[1131].valid = true; list[1131].action = 24;
			list[1132].push({true, 17}); list[1132].push({true, 30}); list[1132].valid = true; list[1132].action = 24;
			list[1133].push({true, 17}); list[1133].push({true, 30}); list[1133].valid = true; list[1133].action = 24;
			list[1134].push({true, 17}); list[1134].push({true, 30}); list[1134].valid = true; list[1134].action = 24;
			list[1135].push({true, 17}); list[1135].push({true, 30}); list[1135].valid = true; list[1135].action = 24;
			list[1136].push({true, 17}); list[1136].push({true, 30}); list[1136].valid = true; list[1136].action = 24;
			list[1137].push({true, 17}); list[1137].push({true, 30}); list[1137].valid = true; list[1137].action = 24;
			list[1138].push({true, 17}); list[1138].push({true, 30}); list[1138].valid = true; list[1138].action = 24;
			list[1139].push({true, 17}); list[1139].push({true, 30}); list[1139].valid = true; list[1139].action = 24;
			list[1145].push({true, 17}); list[1145].push({true, 30}); list[1145].valid = true; list[1145].action = 0;
			list[1148].push({true, 17}); list[1148].push({true, 30}); list[1148].valid = true; list[1148].action = 0;
			list[1149].push({true, 17}); list[1149].push({true, 30}); list[1149].valid = true; list[1149].action = 0;
			list[1150].push({true, 17}); list[1150].push({true, 30}); list[1150].valid = true; list[1150].action = 0;
			list[1151].push({true, 17}); list[1151].push({true, 30}); list[1151].valid = true; list[1151].action = 0;
			list[1152].push({true, 17}); list[1152].push({true, 30}); list[1152].valid = true; list[1152].action = 0;
			list[1153].push({true, 17}); list[1153].push({true, 30}); list[1153].valid = true; list[1153].action = 0;
			list[1167].push({true, 17}); list[1167].push({true, 30}); list[1167].valid = true; list[1167].action = 0;
			list[1168].valid = true; list[1168].action = 23;
			list[1169].push({true, 17}); list[1169].push({true, 30}); list[1169].valid = true; list[1169].action = 0;
			list[1170].push({true, 17}); list[1170].push({true, 30}); list[1170].valid = true; list[1170].action = 0;
			list[1171].push({true, 17}); list[1171].push({true, 30}); list[1171].valid = true; list[1171].action = 0;
			list[1172].push({true, 17}); list[1172].push({true, 30}); list[1172].valid = true; list[1172].action = 0;
			list[1173].push({true, 17}); list[1173].push({true, 30}); list[1173].valid = true; list[1173].action = 0;
			list[1174].push({true, 17}); list[1174].push({true, 30}); list[1174].valid = true; list[1174].action = 0;
			list[1175].push({true, 17}); list[1175].push({true, 30}); list[1175].valid = true; list[1175].action = 0;
			list[1176].push({true, 17}); list[1176].push({true, 30}); list[1176].valid = true; list[1176].action = 0;
			list[1177].push({true, 17}); list[1177].push({true, 30}); list[1177].valid = true; list[1177].action = 0;
			list[1192].push({false, 14}); list[1192].valid = true; list[1192].action = 26;
			list[1221].push({true, 14}); list[1221].valid = true; list[1221].action = 0;
			list[1224].push({true, 12}); list[1224].valid = true; list[1224].action = 0;
			list[1225].push({true, 12}); list[1225].valid = true; list[1225].action = 0;
			list[1226].push({true, 12}); list[1226].valid = true; list[1226].action = 0;
			list[1227].push({true, 12}); list[1227].valid = true; list[1227].action = 0;
			list[1228].push({true, 12}); list[1228].valid = true; list[1228].action = 0;
			list[1229].push({true, 12}); list[1229].valid = true; list[1229].action = 0;
			list[1243].push({false, 27}); list[1243].push({true, 18}); list[1243].push({false, 28});
			list[1243].valid = true; list[1243].action = 0;
			list[1245].push({true, 14}); list[1245].valid = true; list[1245].action = 0;
			list[1246].push({true, 14}); list[1246].valid = true; list[1246].action = 0;
			list[1247].push({true, 14}); list[1247].valid = true; list[1247].action = 0;
			list[1248].push({true, 14}); list[1248].valid = true; list[1248].action = 0;
			list[1249].push({true, 14}); list[1249].valid = true; list[1249].action = 0;
			list[1250].push({true, 14}); list[1250].valid = true; list[1250].action = 0;
			list[1251].push({true, 14}); list[1251].valid = true; list[1251].action = 0;
			list[1252].push({true, 14}); list[1252].valid = true; list[1252].action = 0;
			list[1253].push({true, 14}); list[1253].valid = true; list[1253].action = 0;
			list[1259].push({true, 17}); list[1259].valid = true; list[1259].action = 27;
			list[1262].push({true, 17}); list[1262].valid = true; list[1262].action = 27;
			list[1263].push({true, 17}); list[1263].valid = true; list[1263].action = 27;
			list[1264].push({true, 17}); list[1264].valid = true; list[1264].action = 27;
			list[1265].push({true, 17}); list[1265].valid = true; list[1265].action = 27;
			list[1266].push({true, 17}); list[1266].valid = true; list[1266].action = 27;
			list[1267].push({true, 17}); list[1267].valid = true; list[1267].action = 27;
			list[1281].push({true, 17}); list[1281].valid = true; list[1281].action = 27;
			list[1283].push({true, 17}); list[1283].valid = true; list[1283].action = 27;
			list[1284].push({true, 17}); list[1284].valid = true; list[1284].action = 27;
			list[1285].push({true, 17}); list[1285].valid = true; list[1285].action = 27;
			list[1286].push({true, 17}); list[1286].valid = true; list[1286].action = 27;
			list[1287].push({true, 17}); list[1287].valid = true; list[1287].action = 27;
			list[1288].push({true, 17}); list[1288].valid = true; list[1288].action = 27;
			list[1289].push({true, 17}); list[1289].valid = true; list[1289].action = 27;
			list[1290].push({true, 17}); list[1290].valid = true; list[1290].action = 27;
			list[1291].push({true, 17}); list[1291].valid = true; list[1291].action = 27;
			list[1297].push({true, 17}); list[1297].valid = true; list[1297].action = 28;
			list[1300].push({true, 17}); list[1300].valid = true; list[1300].action = 28;
			list[1301].push({true, 17}); list[1301].valid = true; list[1301].action = 28;
			list[1302].push({true, 17}); list[1302].valid = true; list[1302].action = 28;
			list[1303].push({true, 17}); list[1303].valid = true; list[1303].action = 28;
			list[1304].push({true, 17}); list[1304].valid = true; list[1304].action = 28;
			list[1305].push({true, 17}); list[1305].valid = true; list[1305].action = 28;
			list[1319].push({true, 17}); list[1319].valid = true; list[1319].action = 28;
			list[1321].push({true, 17}); list[1321].valid = true; list[1321].action = 28;
			list[1322].push({true, 17}); list[1322].valid = true; list[1322].action = 28;
			list[1323].push({true, 17}); list[1323].valid = true; list[1323].action = 28;
			list[1324].push({true, 17}); list[1324].valid = true; list[1324].action = 28;
			list[1325].push({true, 17}); list[1325].valid = true; list[1325].action = 28;
			list[1326].push({true, 17}); list[1326].valid = true; list[1326].action = 28;
			list[1327].push({true, 17}); list[1327].valid = true; list[1327].action = 28;
			list[1328].push({true, 17}); list[1328].valid = true; list[1328].action = 28;
			list[1329].push({true, 17}); list[1329].valid = true; list[1329].action = 28;
			list[1358].valid = true; list[1358].action = 29;
			list[1373].push({false, 5}); list[1373].valid = true; list[1373].action = 0;
			list[1411].push({true, 17}); list[1411].valid = true; list[1411].action = 0;
			list[1414].push({true, 17}); list[1414].valid = true; list[1414].action = 0;
			list[1415].push({true, 17}); list[1415].valid = true; list[1415].action = 0;
			list[1416].push({true, 17}); list[1416].valid = true; list[1416].action = 0;
			list[1417].push({true, 17}); list[1417].valid = true; list[1417].action = 0;
			list[1418].push({true, 17}); list[1418].valid = true; list[1418].action = 0;
			list[1419].push({true, 17}); list[1419].valid = true; list[1419].action = 0;
			list[1433].push({true, 17}); list[1433].valid = true; list[1433].action = 0;
			list[1435].push({true, 17}); list[1435].valid = true; list[1435].action = 0;
			list[1436].push({true, 17}); list[1436].valid = true; list[1436].action = 0;
			list[1437].push({true, 17}); list[1437].valid = true; list[1437].action = 0;
			list[1438].push({true, 17}); list[1438].valid = true; list[1438].action = 0;
			list[1439].push({true, 17}); list[1439].valid = true; list[1439].action = 0;
			list[1440].push({true, 17}); list[1440].valid = true; list[1440].action = 0;
			list[1441].push({true, 17}); list[1441].valid = true; list[1441].action = 0;
			list[1442].push({true, 17}); list[1442].valid = true; list[1442].action = 0;
			list[1443].push({true, 17}); list[1443].valid = true; list[1443].action = 0;
			list[1449].push({true, 17}); list[1449].valid = true; list[1449].action = 0;
			list[1452].push({true, 17}); list[1452].valid = true; list[1452].action = 0;
			list[1453].push({true, 17}); list[1453].valid = true; list[1453].action = 0;
			list[1454].push({true, 17}); list[1454].valid = true; list[1454].action = 0;
			list[1455].push({true, 17}); list[1455].valid = true; list[1455].action = 0;
			list[1456].push({true, 17}); list[1456].valid = true; list[1456].action = 0;
			list[1457].push({true, 17}); list[1457].valid = true; list[1457].action = 0;
			list[1471].push({true, 17}); list[1471].valid = true; list[1471].action = 0;
			list[1473].push({true, 17}); list[1473].valid = true; list[1473].action = 0;
			list[1474].push({true, 17}); list[1474].valid = true; list[1474].action = 0;
			list[1475].push({true, 17}); list[1475].valid = true; list[1475].action = 0;
			list[1476].push({true, 17}); list[1476].valid = true; list[1476].action = 0;
			list[1477].push({true, 17}); list[1477].valid = true; list[1477].action = 0;
			list[1478].push({true, 17}); list[1478].valid = true; list[1478].action = 0;
			list[1479].push({true, 17}); list[1479].valid = true; list[1479].action = 0;
			list[1480].push({true, 17}); list[1480].valid = true; list[1480].action = 0;
			list[1481].push({true, 17}); list[1481].valid = true; list[1481].action = 0;
			list[1487].push({true, 17}); list[1487].valid = true; list[1487].action = 0;
			list[1490].push({true, 17}); list[1490].valid = true; list[1490].action = 0;
			list[1491].push({true, 17}); list[1491].valid = true; list[1491].action = 0;
			list[1492].push({true, 17}); list[1492].valid = true; list[1492].action = 0;
			list[1493].push({true, 17}); list[1493].valid = true; list[1493].action = 0;
			list[1494].push({true, 17}); list[1494].valid = true; list[1494].action = 0;
			list[1495].push({true, 17}); list[1495].valid = true; list[1495].action = 0;
			list[1509].push({true, 17}); list[1509].valid = true; list[1509].action = 0;
			list[1511].push({true, 17}); list[1511].valid = true; list[1511].action = 0;
			list[1512].push({true, 17}); list[1512].valid = true; list[1512].action = 0;
			list[1513].push({true, 17}); list[1513].valid = true; list[1513].action = 0;
			list[1514].push({true, 17}); list[1514].valid = true; list[1514].action = 0;
			list[1515].push({true, 17}); list[1515].valid = true; list[1515].action = 0;
			list[1516].push({true, 17}); list[1516].valid = true; list[1516].action = 0;
			list[1517].push({true, 17}); list[1517].valid = true; list[1517].action = 0;
			list[1518].push({true, 17}); list[1518].valid = true; list[1518].action = 0;
			list[1519].push({true, 17}); list[1519].valid = true; list[1519].action = 0;
		}

		nik_ce cprod_type & production(csymbol_type & row, ctoken_type col) const
			{ return list[row.token() * col_size + col]; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

