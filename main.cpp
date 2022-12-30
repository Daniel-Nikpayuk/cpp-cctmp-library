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

#include<cstdio>

/***********************************************************************************************************************/

#include"define_macros.hpp"

#include"00_cctmp_grammar.hpp"
#include"01_cctmp_argument.hpp"
#include"02_cctmp_parameter.hpp"
#include"03_cctmp_praxis.hpp"
#include"04_cctmp_machine.hpp"
//#include"05_cctmp_assembly.hpp"
//#include"06_cctmp_lexer.hpp"
//#include"07_cctmp_parser.hpp"
//#include"08_cctmp_algorithm.hpp"

#include"undef_macros.hpp"

/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

/*
	constexpr auto val = eval
	<
		_par_at_, 164,

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

	constexpr auto val = arg_at<164>
	(
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
	);
*/

//	constexpr auto val = eval<_par_at_, 0,   0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11>;

/***********************************************************************************************************************/

	struct T_machine_binary_apply
	{
		constexpr static auto d    = MD::initial_depth;
		constexpr static auto regs = T_machine_get::regs;
		constexpr static auto heap = T_machine_get::heap;
		constexpr static auto bs   = U_pack_Vs < heap , regs  , regs >;
		constexpr static auto ns   = U_pack_Vs < _two , _zero , _one >;
		constexpr static auto inds = U_pack_Vs<bs, ns>;
		constexpr static auto c    = T_machine_apply::template contr<>;

		template<auto Op, auto V0, auto V1>
		constexpr static auto result = T_machine_start::template
						result<d, c, V0, V1>(T_machine_apply::template H0<inds, Op>);

	}; constexpr auto _binary_apply_ = U_custom_T<T_machine_binary_apply>;

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		printf("%d\n", eval<_binary_apply_, _add_, 2, 3>);
		printf("%d\n", eval<_binary_apply_, _multiply_, 2, 3>);

	//	printf("%d\n", val);

		return 0;
	}

