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
	struct concord_pack_0
	{
		using size_type            				= SizeType;

		constexpr static size_type glyph_size			= 100;
		constexpr static size_type glyph_builtin		=  10;
		constexpr static size_type glyph_tuple			=  10;
		constexpr static size_type glyph_cotuple		=  10;
		constexpr static size_type glyph_function		=  10;
		constexpr static size_type glyph_recurse		=  10;
		constexpr static size_type glyph_identity		=  10;
		constexpr static size_type glyph_l_than			=  10;
		constexpr static size_type glyph_l_than_or_eq		=  10;
		constexpr static size_type glyph_r_than			=  10;
		constexpr static size_type glyph_r_than_or_eq		=  10;
		constexpr static size_type glyph_exists			=  10;
		constexpr static size_type glyph_forall			=  10;
		constexpr static size_type glyph_message		=  10;

		using glyph_pack = cctmp::T_pack_Vs
		<
			glyph_size		,
			glyph_builtin		,
			glyph_tuple		,
			glyph_cotuple		,
			glyph_function		,
			glyph_recurse		,
			glyph_identity		,
			glyph_l_than		,
			glyph_l_than_or_eq	,
			glyph_r_than		,
			glyph_r_than_or_eq	,
			glyph_exists		,
			glyph_forall		,
			glyph_message
		>;

		constexpr static size_type space_size			= 100;
		constexpr static size_type space_0			=  10;
		constexpr static size_type space_1			=  10;
		constexpr static size_type space_2			=  10;

		using space_pack = cctmp::T_pack_Vs
		<
			space_size		,
			space_0			,
			space_1			,
			space_2
		>;

		constexpr static size_type image_size			= 100;
		constexpr static size_type image_builtin		=  10;
		constexpr static size_type image_tuple			=  10;
		constexpr static size_type image_cotuple		=  10;
		constexpr static size_type image_function		=  10;
		constexpr static size_type image_recurse		=  10;
		constexpr static size_type image_identity		=  10;
		constexpr static size_type image_l_than			=  10;
		constexpr static size_type image_l_than_or_eq		=  10;
		constexpr static size_type image_r_than			=  10;
		constexpr static size_type image_r_than_or_eq		=  10;
		constexpr static size_type image_exists			=  10;
		constexpr static size_type image_forall			=  10;
		constexpr static size_type image_message		=  10;

		using image_pack = cctmp::T_pack_Vs
		<
			image_size		,
			image_builtin		,
			image_tuple		,
			image_cotuple		,
			image_function		,
			image_recurse		,
			image_identity		,
			image_l_than		,
			image_l_than_or_eq	,
			image_r_than		,
			image_r_than_or_eq	,
			image_exists		,
			image_forall		,
			image_message
		>;
	};

	template<typename type, typename size_type, template<typename> typename concord_pack, size_type length>
	using resolve_concord_type = concord
	<
		type, size_type,
		typename concord_pack<size_type>::glyph_pack,
		typename concord_pack<size_type>::space_pack,
		typename concord_pack<size_type>::image_pack,
		length
	>;

	template<typename SizeType>
	struct concord_test
	{
		using size_type          = SizeType;
		using concord_type       = resolve_concord_type<size_type, size_type, concord_pack_0, 200>;
		using icon_type          = icon<size_type>;
		using sign_type          = sign<size_type>;

		using empty_cmethod_type = resolve_cmethod < concord_type , concord_empty_cmethod >;
		using empty_method_type  = resolve_method  < concord_type , concord_empty_method  >;
		using ring_cmethod_type  = resolve_cmethod < concord_type , concord_ring_cmethod  >;
		using ring_method_type   = resolve_method  < concord_type , concord_ring_method   >;
		using list_cmethod_type  = resolve_cmethod < concord_type , concord_list_cmethod  >;
		using list_method_type   = resolve_method  < concord_type , concord_list_method   >;

		concord_type value;

		icon_type empty_icon;
		icon_type ring8_icon;
		icon_type list_ring8_icon;

		sign_type empty_sign;
		sign_type ring8_sign1;
		sign_type list_ring8_sign1;
		sign_type list_ring8_sign2;

		constexpr concord_test()
		{
			auto empty_method = value.template equip<empty_method_type>();
			auto ring_method  = value.template equip<ring_method_type>();
			auto list_method  = value.template equip<list_method_type>();

			empty_icon        = empty_method.declare_type();
			ring8_icon        = ring_method .declare_type(8);
			list_ring8_icon   = list_method .declare_type(ring8_icon);

			empty_sign        = empty_method.define_abstract(empty_icon);
			ring8_sign1       = ring_method .define_abstract(ring8_icon, 7);
			list_ring8_sign1  = list_method .define_abstract(list_ring8_icon, ring8_sign1, empty_sign);

			auto ring8_sign   = ring_method.define_abstract(ring8_icon, 0);
			list_ring8_sign2  = list_method.define_abstract(list_ring8_icon, ring8_sign, empty_sign);

			for (size_type k = 1; k != 5; ++k)
			{
				ring8_sign       = ring_method.define_abstract(ring8_icon, k);
				list_ring8_sign2 = list_method.define_abstract
							(list_ring8_icon, ring8_sign, list_ring8_sign2);
			}
		}

		// glyph:

			constexpr auto ring_cglyph(const icon_type & icon) const
				{ return value.template cequip<ring_cmethod_type>().glyph_ctext(icon); }

			constexpr auto list_cglyph(const icon_type & icon) const
				{ return value.template cequip<list_cmethod_type>().glyph_ctext(icon); }

		// image:

			constexpr auto ring_cmethod() const
				{ return value.template cequip<ring_cmethod_type>(); }

			constexpr auto ring_cimage(const sign_type & sign) const
				{ return ring_cmethod().image_ctext(sign); }

			constexpr auto list_cmethod() const
				{ return value.template cequip<list_cmethod_type>(); }

			constexpr auto list_cimage(const sign_type & sign) const
				{ return list_cmethod().image_ctext(sign); }
	};

	constexpr auto test0 = concord_test<unsigned long>{};

	void print_test_types()
	{
		print_array(test0.ring_cglyph(test0.empty_icon));
		print_array(test0.ring_cglyph(test0.ring8_icon));
		print_array(test0.list_cglyph(test0.list_ring8_icon));

		printf("\n");
	}

	void print_test_images()
	{
		print_array(test0.ring_cimage(test0.empty_sign));
		print_array(test0.ring_cimage(test0.ring8_sign1));
		print_array(test0.ring_cimage(test0.list_ring8_sign1));

		printf("\n");
	}

	void print_test_list_values()
	{
		auto ring_cival = test0.ring_cmethod();
		auto list_cival = test0.list_cmethod();
		auto list_sign  = test0.list_ring8_sign2;

		for (auto k = 0; k != 5; ++k)
		{
			printf("%lu ", ring_cival.cvalue(list_cival.car_sign(list_sign)));

			list_sign = list_cival.cdr_sign(list_sign);
		}

		printf("\n");
	}

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		print_test_types();
		print_test_images();
	//	print_array(*test0.value.crecord());
		print_test_list_values();

		return 0;
	}

