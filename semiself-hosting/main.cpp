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

#include<cstdio>
#include<cstdlib>

/***********************************************************************************************************************/

#include"define_macros.hpp"

#include"include/00_meta.hpp"

#include"undef_macros.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		constexpr auto lt1 = LambdaTuple::make(1, 2, 3);
		constexpr auto lt2 = LambdaTuple::make(4, 5, 6);

		constexpr auto cat = LambdaTuple::catenate(lt1, lt2);

		printf("%lu\n", LambdaTuple::size(cat));

		printf("%d\n", LambdaTuple::template value<0>(cat));
		printf("%d\n", LambdaTuple::template value<1>(cat));
		printf("%d\n", LambdaTuple::template value<2>(cat));
		printf("%d\n", LambdaTuple::template value<3>(cat));
		printf("%d\n", LambdaTuple::template value<4>(cat));
		printf("%d\n", LambdaTuple::template value<5>(cat));

		//

		auto tup = LambdaTuple::make(1, 2.0, 'c');

		printf("%d\n", LambdaTuple::template value<0>(tup));
		printf("%f\n", LambdaTuple::template value<1>(tup));
		printf("%c\n", LambdaTuple::template value<2>(tup));

		printf("%lu\n", LambdaTuple::size(tup));
		printf("%s\n", LambdaTuple::empty(tup) ? "is empty" : "not empty");

		return 0;
	}

