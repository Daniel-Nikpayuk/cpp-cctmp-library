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
//#include<cstdlib>

/***********************************************************************************************************************/

#include"define_macros.hpp"

#include"include/00_kernel.hpp"
#include"include/01_inventory.hpp"

#include"undef_macros.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

	template<typename... Ts>
	constexpr auto push_copy(Ts... vs)
	{
		using seq_type = sequence<int, gindex_type, sizeof...(Ts)>;

		seq_type s;
		(s.push(vs), ...);

		return s;
	}

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		constexpr auto s0 = push_copy(1, 2, 3, 4, 5);
		constexpr auto s1 = push_copy(1, 2, 3, 4, 5);

		auto val = kernel_different_v0<gindex_type>(s0.cbegin(), s0.cend(), s1.cbegin());
		printf("%s\n", val ? "different" : "same");

		return 0;
	}

