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
//#include"03_cctmp_algorithm.hpp"

#include"undef_macros.hpp"

/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

// tuple:

	template<typename... Ts>
	constexpr auto print_tuple(const tuple<Ts...> & t)
	{
		if constexpr (sizeof...(Ts) == 0) printf("\n");
		else
		{
			printf("%d, ", t.value);

			print_tuple(t.rest);
		}
	}

// unit:

	template<auto n, typename T, typename... Ts>
	constexpr auto unit_replace(T v, Ts... vs) // arg_block size 64 has a bug!
	{
		constexpr auto s = U_store_T<tuple<Ts...>>;

		return arg_replace<s, n, _to_tuple_>(v, vs...);
	}

	template<auto n, typename T, typename... Ts>
	constexpr auto unit_insert(T v, Ts... vs)
	{
		constexpr auto s = U_store_T<tuple<T, Ts...>>;

		return arg_insert<s, n, _to_tuple_>(v, vs...);
	}

	template<auto n, typename T0, typename... Ts>
	constexpr auto unit_erase(T0 v0, Ts... vs)
	{
		constexpr auto s = U_store_T<tuple<Ts...>>;

		return arg_erase<s, n, _to_tuple_>(U_null_Vs, v0, vs...);
	}

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	printf("%d\n", arg_at<63>
	//	(
	//		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	//		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	//		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	//		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	//		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,

	//		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	//		0, 1, 2, 33
	//	));

	//	auto val = unit_replace <6>(-1,    0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
	//	auto val = unit_insert  <6>(-1,    0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
	//	auto val = unit_erase   <6>(       0, 1, 2, 3, 4, 5, 6, 7, 8, 9);

	//	auto val = unit_replace<63>
	//	(-1,
	//	     	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	//	     	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	//	     	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	//	     	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	//	     	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,

	//	     	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	//	     	0, 1, 2, 3
	//	);

	//	print_tuple(val);

		return 0;
	}

