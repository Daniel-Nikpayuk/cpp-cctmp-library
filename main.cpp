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

	using Overload = cctmp::Overload;

	template<auto... Vs>
	constexpr auto call = Overload::template result<Vs...>;

	constexpr auto p = cctmp::U_pack_Vs
	<
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
		16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

		99, 0, 5, 41
	>;

	constexpr auto U_int	= cctmp::U_store_T<int>;
	constexpr auto U_char	= cctmp::U_store_T<char>;

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	printf("%s\n", call<Overload::same, U_char, U_char> ? "true" : "false");
	//	printf("%llu\n", call<Overload::map, cctmp::template increment_op<>, p>);
	//	printf("%hu\n", call<Overload::find, cctmp::template is_zero_op<>, p>);

	//	printf("%d\n", cctmp_program::at_v0<0, p>);
	//	printf("%llu\n", cctmp_program::left_v0<2, p>);
	//	printf("%llu\n", cctmp_program::split_v0<2, p>);
	//	printf("%llu\n", cctmp_program::segment_v0<uint_type{10}>);

	//	printf("%llu\n", cctmp_program::erase_v0<0, p>);
	//	printf("%llu\n", cctmp_program::insert_v0<7, 4, p>);
	//	printf("%llu\n", cctmp_program::replace_v0<7, 1, p>);

	//	printf("%llu\n", cctmp_program::fold_v0<cctmp::template add_op<>, uint_type{0}, p>);

	//	printf("%llu\n", cctmp_program::insert_sort_v0<p, 3>);
	//	printf("%llu\n", cctmp_program::sort_v0<p>);
	//	printf("%llu\n", cctmp_program::sort_v1<p>);
	//	printf("%llu\n", cctmp_program::sort_v2<p>);	// gcc 1.717s / clang 4.199s
								// gcc 1.344s / clang 3.568s

	//	printf("%llu\n", cctmp_program::factorial_v0<uint_type{20}>);
	//	printf("%llu\n", cctmp_program::factorial_v1<uint_type{20}>);

	//	printf("%llu\n", cctmp_program::fibonacci_v0<uint_type{43}>);	// gcc 1.767s / clang 5.641s
	//	printf("%d\n", cctmp_program::fibonacci_v1<uint_type{43}>);	// gcc 0.578s / clang 1.227s

		return 0;
	}

