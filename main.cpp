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

#include<cstdio>

/***********************************************************************************************************************/

#include"define_macros.hpp"

#include"00_cctmp_grammar.hpp"
#include"01_cctmp_argument.hpp"
#include"02_cctmp_parameter.hpp"
#include"03_cctmp_praxis.hpp"
#include"04_cctmp_machine.hpp"
#include"05_cctmp_assembly.hpp"
//#include"06_cctmp_lexer.hpp"
//#include"07_cctmp_parser.hpp"
//#include"08_cctmp_algorithm.hpp"

#include"undef_macros.hpp"

/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

	constexpr auto list0 = U_pack_Vs<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11>;
	constexpr auto list1 = U_pack_Vs<3, 10, 4, 0, 7, 8, 5, 6, 9, 1, 2, 11>;
	constexpr auto list2 = U_pack_Vs
	<
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,

		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,

		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		0, 1, 2, 3, 44
	>;

//	constexpr auto val = unpack_<list0, _par_fold_, _add_, 0>;
//	constexpr auto val = unpack_<list1, _par_fold_, _add_, 0>;

	constexpr auto ops = U_pack_Vs<_is_less_than_<5>, _constant_<true>>;
//	constexpr auto val = unpack_<list0, _par_sift_, ops>;
//	constexpr auto val = unpack_<list1, _par_sift_, ops>;
//	constexpr auto val = unpack_<list2, _par_sift_, ops>;

//	constexpr auto val = unpack_<list0, _par_at_, 4>;
//	constexpr auto val = unpack_<list1, _par_at_, 4>;
//	constexpr auto val = unpack_<list2, _dpar_at_, 15, 164>;

//	constexpr auto val = unpack_<list0, _par_replace_, 4, 4>;
//	constexpr auto val = unpack_<list1, _par_replace_, 4, 4>;
//	constexpr auto val = unpack_<list2, _par_replace_, 4, 4>;

//	constexpr auto val = unpack_<list0, _par_insert_, 0, 4>;
//	constexpr auto val = unpack_<list1, _par_insert_, 0, 4>;
//	constexpr auto val = unpack_<list2, _par_insert_, 0, 4>;

//	constexpr auto val = unpack_<list0, _par_erase_, 4>;
//	constexpr auto val = unpack_<list1, _par_erase_, 4>;
//	constexpr auto val = unpack_<list2, _par_erase_, 4>;

//	constexpr auto val = eval<_par_insert_sort_<_less_than_>, list0, 5>;
//	constexpr auto val = eval<_par_insert_sort_<_less_than_>, list1, 5>;
//	constexpr auto val = eval<_par_insert_sort_<_less_than_>, list2, 5>;

//	constexpr auto val = unpack_<list0, _par_sort_<_less_than_>>;
//	constexpr auto val = unpack_<list1, _par_sort_<_less_than_>>;
//	constexpr auto val = unpack_<list2, _par_sort_<_less_than_>>;

//	constexpr auto val = unpack_<list0, _part_sort_<_less_than_>>;
//	constexpr auto val = unpack_<list1, _part_sort_<_less_than_>>;
//	constexpr auto val = unpack_<list2, _part_sort_<_less_than_>>;

/***********************************************************************************************************************/

//	constexpr auto f   = _pose_<_increment_<1>, _times_<2>>;
//	constexpr auto val = eval<f, 2>;

//	constexpr auto val = eval<_par_segment_, 10>;
//	constexpr auto val = eval<_binary_apply_, _prax_add_, 2, 3>;
//	constexpr auto val = eval<_binary_apply_, _prax_multiply_, 2, 3>;

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	printf("%d\n", arg_at<0>(0, 1, 2, 3, 4, 5));
	//	printf("%d\n", val);

		return 0;
	}

