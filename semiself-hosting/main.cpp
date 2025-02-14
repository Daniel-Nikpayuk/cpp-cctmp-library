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

	constexpr auto concord_add_test()
	{
		using size_type     = unsigned long;
		using glyph_pack    = cctmp::T_pack_Vs<36, 3>;
		using space_pack    = cctmp::T_pack_Vs<36, 3>;
		using image_pack    = cctmp::T_pack_Vs<36, 3>;
		using concord_type  = concord<size_type, size_type, glyph_pack, space_pack, image_pack, 3>;
		using method_type   = resolve_method<concord_type, concord_ring_method>;

		auto concord_value  = concord_type{};
		auto concord_method = concord_value.template equip<method_type>();
		auto out_sign       = concord_method.declare_abstract (8);
		auto in1_sign       = concord_method.define_abstract  (8, 2);
		auto in2_sign       = concord_method.define_abstract  (8, 3);

		return concord_value;
	}

	constexpr auto concord0 = concord_add_test();

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		print_array(*concord0.csymbol()->cglyph()->ctext());
		print_array(*concord0.csymbol()->cimage()->ctext());
		print_array(*concord0.crecord());

		return 0;
	}

