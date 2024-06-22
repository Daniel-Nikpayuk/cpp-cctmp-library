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

/*
	template<auto...> struct pack;

	template<        auto U        > auto operator + (pack<0, 0, U> &, pack< > &) -> pack<        U>  ;
	template<        auto U, auto V> auto operator + (pack<0, 0, U> &, pack<V> &) -> pack<  0, 0, U> &;
	template<        auto U, auto V> auto operator + (pack<0, 1, U> &, pack<V> &) -> pack<  0, 0, V> &;
	template<auto n, auto U, auto V> auto operator + (pack<n, 1, U> &, pack<V> &) -> pack<n-1, 1, U> &;

	template<auto n, auto... Vs>
	constexpr auto at = U_store_T<decltype((*(pack<n, 1, 0>*) 0 + ... + *(pack<Vs>*) 0) + *(pack<>*) 0)>;
*/

/***********************************************************************************************************************/

/*
	template<auto...> struct pack;

	template<        auto... Vs        > auto operator + (pack<0, Vs...> &, pack< > &) -> pack<     Vs...   >  ;
	template<        auto... Vs, auto V> auto operator + (pack<0, Vs...> &, pack<V> &) -> pack<  0, Vs...   > &;
	template<auto n, auto... Vs, auto V> auto operator + (pack<n, Vs...> &, pack<V> &) -> pack<n-1, Vs..., V> &;

	template<auto n, auto... Vs>
	constexpr auto left = U_store_T<decltype((*(pack<n>*) 0 + ... + *(pack<Vs>*) 0) + *(pack<>*) 0)>;
*/

/***********************************************************************************************************************/

/*
	template<auto...> struct pack;

	template<                auto... Vs> auto operator + (pack< > &, pack<0, Vs...> &) -> pack<        Vs...>  ;
	template<auto V,         auto... Vs> auto operator + (pack<V> &, pack<0, Vs...> &) -> pack<0  ,    Vs...> &;
	template<auto V, auto n, auto... Vs> auto operator + (pack<V> &, pack<n, Vs...> &) -> pack<n-1, V, Vs...> &;

	template<auto n, auto... Vs>
	constexpr auto right = U_store_T
	<
		decltype(*(pack<>*) 0 + (*(pack<Vs>*) 0 + ... + *(pack<decltype(n)(sizeof...(Vs))-n>*) 0))
	>;
*/

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	constexpr auto l0 = right_
	//	<
	//		0,

	//		0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,
	//		0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,
	//		0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,
	//		0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,
	//		0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,

	//		0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,
	//		0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,
	//		0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,
	//		0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,
	//		0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,

	//		0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 11, 2, 3, 4,  5, 6, 7, 8, 9
	//	>;

		constexpr auto l0 = segment_<200>;

		printf("%d\n", l0);

		return 0;
	}

