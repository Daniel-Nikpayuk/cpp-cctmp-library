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

#include"testing/printer.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

	constexpr auto make_ring()
	{
		using size_type = unsigned long;
		using logo_type = logo<size_type, size_type, 20, 5, 7, 3, 5>;
		using method0   = resolve_method<logo_type, logo_ring_method>;

		auto logo_val   = logo_type{};
		auto ring_m     = logo_val.template equip<method0>();

		ring_m.overlay(8);

		return logo_val;
	}

	constexpr auto logo0 = make_ring();

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		using cmethod0 = resolve_cmethod<typename decltype(logo0)::base::initial_type, print_cmethod>;

		auto print0 = logo0.ctext()->template cequip<cmethod0>();

		print0.as_set(); // prints: { 0, 8, 0 }

		return 0;
	}

