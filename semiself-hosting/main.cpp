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

#include"undef_macros.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

/*
	constexpr auto make_ring()
	{
		using size_type = unsigned long;
		using logo_type = logo<size_type, size_type, 5, 7, 3, 5>;
		using method0   = resolve_method<logo_type, ring_method>;

		auto rtn_logo   = plot_type{};
		auto ring0      = rtn_logo.template equip<method0>(0);

		ring0.();

		return rtn_logo;
	}

	constexpr auto logo0 = make_logo();
*/

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	using cmethod0 = resolve_cmethod<decltype(logo0), print_cmethod>;

	//	auto print0 = logo0.template cequip<cmethod0>(0);

	//	print0.as_set(); // prints: { 0, 5, 12, 15, 20 }

		return 0;
	}

