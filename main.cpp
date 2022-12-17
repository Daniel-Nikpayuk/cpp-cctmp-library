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

#include"define_macros.hpp"

#include"00_cctmp_grammar.hpp"
#include"01_cctmp_eval.hpp"
#include"02_cctmp_praxis.hpp"

#include"undef_macros.hpp"

/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	printf("%d\n", at<PT::_2_6, 63>
	//	(
	//		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	//		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	//		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	//		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	//		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,

	//		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	//		0, 1, 2, 3
	//	));

	//	auto val = repl<6>(-1,    0, 1, 2, 3, 4, 5, 6, 7, 8, 9);

		auto val = repl<69>
		(-1,
		     	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		     	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		     	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		     	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		     	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,

		     	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		     	0, 1, 2, 3, 4, 5, 6, 7, 8, 9
		);

	//	printf("%d\n", val);
		print_tuple(val);

		return 0;
	}

