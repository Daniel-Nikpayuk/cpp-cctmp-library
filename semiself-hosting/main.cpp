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
#include"include/01_automata.hpp"

#include"undef_macros.hpp"

#include"testing/printer.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

// test:

	template<typename SizeType>
	struct concord_test
	{
		using size_type          = SizeType;
		using glyph_pack         = cctmp::T_pack_Vs<100, 10, 10, 10, 10, 10>;
		using space_pack         = cctmp::T_pack_Vs<  0,  0,  0,  0,  0,  0>;
		using image_pack         = cctmp::T_pack_Vs<100, 10, 10, 10, 10, 10>;
		using concord_type       = concord<size_type, size_type, glyph_pack, space_pack, image_pack, 100>;
		using icon_type          = icon<size_type>;
		using sign_type          = sign<size_type>;

		using ring_cmethod_type  = resolve_cmethod < concord_type, concord_ring_cmethod  >;
		using ring_method_type   = resolve_method  < concord_type, concord_ring_method   >;
		using tuple_cmethod_type = resolve_cmethod < concord_type, concord_tuple_cmethod >;
		using tuple_method_type  = resolve_method  < concord_type, concord_tuple_method  >;

		concord_type value;

		icon_type ring1_icon;
		icon_type ring4_icon;
		icon_type ring8_icon;

		sign_type ring1_sign1;
		sign_type ring4_sign1;
		sign_type ring8_sign1;

		icon_type tuple1_icon;
		sign_type tuple1_sign;

		constexpr concord_test()
		{
			auto ring_method  = value.template equip<ring_method_type>();
			auto tuple_method = value.template equip<tuple_method_type>();

			ring1_icon        = ring_method.declare_type(1);
			ring4_icon        = ring_method.declare_type(4);
			ring8_icon        = ring_method.declare_type(8);

			ring1_sign1       = ring_method.define_abstract(ring1_icon, 5);
			ring4_sign1       = ring_method.define_abstract(ring4_icon, 6);
			ring8_sign1       = ring_method.define_abstract(ring8_icon, 7);

			tuple1_icon       = tuple_method.declare_type({ ring1_icon, ring4_icon, ring8_icon });
			tuple1_sign       = tuple_method.define_abstract(
						tuple1_icon, {ring1_sign1, ring4_sign1, ring8_sign1});
		}

		// glyph:

			constexpr auto ring_cglyph(const icon_type & icon) const
				{ return value.template cequip<ring_cmethod_type>().glyph_ctext(icon); }

			constexpr auto tuple_cglyph(const icon_type & icon) const
				{ return value.template cequip<tuple_cmethod_type>().glyph_ctext(icon); }

		// image:

			constexpr auto ring_cimage(const sign_type & sign) const
				{ return value.template cequip<ring_cmethod_type>().image_ctext(sign); }

			constexpr auto tuple_cimage(const sign_type & sign) const
				{ return value.template cequip<tuple_cmethod_type>().image_ctext(sign); }
	};

	constexpr auto test0 = concord_test<unsigned long>{};

	void print_test_types()
	{
		print_array(test0.ring_cglyph(test0.ring1_icon));
		print_array(test0.ring_cglyph(test0.ring4_icon));
		print_array(test0.ring_cglyph(test0.ring8_icon));

		print_array(test0.tuple_cglyph(test0.tuple1_icon));

		printf("\n");
	}

	void print_test_images()
	{
		print_array(test0.ring_cimage(test0.ring1_sign1));
		print_array(test0.ring_cimage(test0.ring4_sign1));
		print_array(test0.ring_cimage(test0.ring8_sign1));

		print_array(test0.tuple_cimage(test0.tuple1_sign));

		printf("\n");
	}

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		print_test_types();
		print_test_images();
		print_array(*test0.value.crecord());

		return 0;
	}

