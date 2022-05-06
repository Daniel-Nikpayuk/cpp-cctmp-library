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
#include"0_backend.hpp"
#include"1_frontend.hpp"
#include"2_programs.hpp"
#include"undef_macros.hpp"

/***********************************************************************************************************************/

	using uint_type = unsigned long long;

/***********************************************************************************************************************/

//	list length = 204:

//	gcc - 20.12s
//	clang - 2m4.21s

	struct add
	{
		template<auto x, auto y>
		constexpr static auto result = x + y;
	};

	int main(int argc, char *argv[])
	{
	//	printf("%llu\n", cctmp_program::factorial_v0<uint_type{20}>);
	//	printf("%llu\n", cctmp_program::factorial_v1<uint_type{20}>);

	//	printf("%llu\n", cctmp_program::fibonacci_v0<uint_type{13}>);

//			gcc compile time:		gcc run time:
//			                                
//			                                377
//			                                
//			real	0m0.382s                real	0m0.001s
//			user	0m0.304s                user	0m0.001s
//			sys	0m0.044s                sys	0m0.000s
//			                                
//			clang compile time:             clang run time:
//			                                
//			                                377
//			                                
//			real	0m0.675s                real	0m0.001s
//			user	0m0.638s                user	0m0.000s
//			sys	0m0.038s                sys	0m0.001s

	//	printf("%llu\n", cctmp_program::segment_v0<uint_type{10}>);

		constexpr auto p = cctmp::U_pack_Vs
		<
		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

			99, 0, 5, 41
		>;

		printf("%llu\n", cctmp_program::fold_v0<cctmp::U_store_T<add>, uint_type{0}, p>);
	//	printf("%llu\n", cctmp_program::left_v0<84, p>);
	//	printf("%llu\n", cctmp_program::merge_sort_v0<p>);

	//	printf("%d\n", cctmp::segment<500, 10>);

	//	printf("%d\n", cctmp::sifter<500, 5,       17, 9, 3, 5, 12, -509, 0>);

	//	constexpr auto x = cctmp::filter<500, 1,       17, 9, 3, 5, 12, -509, 0>;

	//	printf("%d, %d\n", x.v1, x.v2);

		return 0;
	}

