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

	// C++17 tuple implemented using lambdas (make, get value):

		template<auto...> struct At;

		template
		<
			         auto... LUs, void(*p0)(T_pack_Vs<    LUs...>*),
			auto RU, auto... RUs, void(*p1)(T_pack_Vs<RU, RUs...>*),
			auto... filler
		>
		struct At<p0, p1, filler...>
		{
			using RT = T_store_U<RU>;

			constexpr static auto result(T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs) { return rv; }
		};

		template<auto n, typename... Ts>
		constexpr auto at(void(*)(T_pack_Vs<n>*), Ts... vs)
		{
			constexpr auto p0 = left_  <n, U_store_T<Ts>...>;
			constexpr auto p1 = right_ <n, U_store_T<Ts>...>;

			return At<p0, p1>::result(vs...);
		}

	// make:	

		template<typename... Ts>
		constexpr auto make_tuple(Ts... vs)
			{ return [=](auto v) { return at(U_restore_T<decltype(v)>, vs...); }; }

	// get value:

		template<auto n, typename T>
		constexpr auto get_value(T v) { return v(U_pack_Vs<n>); }

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		auto tup = make_tuple(1, 2.0, 'c');

		printf("%d\n", get_value<0>(tup));
		printf("%f\n", get_value<1>(tup));
		printf("%c\n", get_value<2>(tup));

		return 0;
	}

