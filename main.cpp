/************************************************************************************************************************
**
** Copyright 2022 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

//#include<cstdio>
#include<stdio.h>

/***********************************************************************************************************************/

//#define NIK_DEFINE_2_9_BLOCKS

#include"define_macros.hpp"

#include"00_cctmp_grammar.hpp"
#include"01_cctmp_eval.hpp"
#include"02_cctmp_block.hpp"
//#include"03_cctmp_machine.hpp"
///#include"04_cctmp_algorithm.hpp"

//#include"05_generic_grammar.hpp"
//#include"06_generic_lexer.hpp"
//#include"07_generic_parser.hpp"
//#include"08_generic_assembly.hpp"

//#include"_one_cycle_generics.hpp"
//#include"_one_cycle_accords.hpp"
//#include"_one_cycle_options.hpp"
//#include"_one_cycle_lexer.hpp"
//#include"_one_cycle_parser.hpp"
//#include"_one_cycle_specifics.hpp"

//#include"_byte_ring.hpp"
//#include"_byte_array_ring.hpp"
//#include"_cryptography.hpp"
//#include"_linear_algebra.hpp"
//#include"_signal_processing.hpp"

#include"undef_macros.hpp"

/***********************************************************************************************************************/

	constexpr char pair_factorial[] = 

		"factorial n p    ;"

		"loop:            ;"
		"is_zero n        ;"
		"branch done      ;"
		"p = multiply n p ;"
		"n = dec n        ;"
		"goto loop        ;"

		"done:            ;"
		"return p         ;"

		;

/***********************************************************************************************************************/

	using namespace cctmp;

		constexpr auto p = U_pack_Vs
		<
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,

		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,

		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,

		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,

		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
		//	0, 3, 4, 5, 9,  0, 3, 4, 5, 9,    0, 3, 4, 5, 9,  0, 3, 4, 5, 9,

			0, 3, 4, 5, 9//,  0, 3, 4, 5, 9,    0, 11
		>;

/***********************************************************************************************************************/

//	constexpr int arr[] = { 1, 2, 3, 3, 2, 4 };

//	constexpr auto seg = U_pack_Vs< 0, 1, 2, 3, 4, 5 >;
//	constexpr auto val = array_map_<_increment_<1>, arr, 6, _list_<>, seg, U_signed_int, 6>;
//	constexpr auto val = array_fold_<_add_, 0, arr, 6, _nop_, U_signed_int, 6>;

		constexpr auto _2_6_at_		= _2_N_at_      < BT::_2_6 >; // for testing.
		constexpr auto _2_6_erase_	= _2_N_erase_   < BT::_2_6 >; // for testing.
		constexpr auto _2_6_replace_	= _2_N_replace_ < BT::_2_6 >; // for testing.
		constexpr auto _2_6_insert_	= _2_N_insert_  < BT::_2_6 >; // for testing.

	int main(int argc, char *argv[])
	{
	//	printf("%d\n", padder<0>);
	//	printf("%d\n", unpack_<p, _2_6_at_, 511>);
	//	printf("%d\n", unpack_<p, _2_9_erase_, 511>);
	//	printf("%d\n", unpack_<p, _2_6_replace_, 3, 7>);
	//	printf("%d\n", unpack_<p, _2_6_insert_, 4, 7>);

		return 0;
	}

	//	printf("%d\n", eval<_2_6_at_, 4,  3, 4, 1, 9, 5>);

	//	printf("%llu\n", cctmp_algorithm::list_sort<p>);		// gcc 2.854s / clang 7.166s
