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

// type system:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// experimental:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// table:

		auto a10 = arr_type{a};

		using submethod1 = resolve_submethod<arr_type, table_submethod>;

		auto m11 = a10.template subequip<submethod1>();

		m11.mid_set(1, 5);
	//	m11.left_set(4);
	//	m11.right_shift(1);
		m11.set_sizes(2, 2);

		printf("%d " , m11[0][0]);
		printf("%d\n", m11[0][1]);
		printf("%d " , m11[1][0]);
		printf("%d\n", m11[1][1]);

/***********************************************************************************************************************/

// plot:

	constexpr auto make_plot()
	{
		using size_type = unsigned long;
		using plot_type = plot<size_type, size_type, 5, 7, 3, 5>;
		using method0   = resolve_method<plot_type, array_method>;

		auto rtn_plot   = plot_type{};
		auto subarr0    = rtn_plot.template equip<method0>(0);

		subarr0.fullsize();
		subarr0[0] = 5;
		subarr0[1] = 7;
		subarr0[2] = 2;
		subarr0[3] = 3;
		subarr0[4] = 4;

		return rtn_plot;
	}

	constexpr auto plot0 = make_plot();

	// main:

		using cmethod0 = resolve_cmethod<decltype(plot0), print_cmethod>;

		auto print0 = plot0.template cequip<cmethod0>(0);

		print0.as_set(); // prints: { 0, 5, 12, 15, 20 }

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// concord:

	// main:

		print_array(*test0.value.csymbol()->cglyph()->ctext());
		print_array(*test0.value.csymbol()->cimage()->ctext());
		print_array(*test0.value.crecord());

/***********************************************************************************************************************/

// pack:

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

/***********************************************************************************************************************/

// ring (unique):

	template<typename SizeType>
	struct concord_test
	{
		using size_type         = SizeType;
		using concord_type      = resolve_concord_type<size_type, size_type, concord_pack_0, 100>;
		using icon_type         = icon<size_type>;
		using sign_type         = sign<size_type>;

		using ring_cmethod_type = resolve_cmethod < concord_type, concord_ring_cmethod >;
		using ring_method_type  = resolve_method  < concord_type, concord_ring_method  >;

		concord_type value;

		icon_type ring1_icon;
		icon_type ring4_icon;

		sign_type ring1_sign1;
		sign_type ring1_sign2;
		sign_type ring1_sign3;
		sign_type ring4_sign1;

		constexpr concord_test()
		{
			auto ring_method = value.template equip<ring_method_type>();

			ring1_icon       = ring_method.declare_type(1);
		//	ring4_icon       = ring_method.declare_type(4);

			ring1_sign1      = ring_method.define_abstract(ring1_icon, 5);
			ring1_sign2      = ring_method.define_abstract(ring1_icon, 6);
			ring1_sign3      = ring_method.define_abstract(ring1_icon, 5);
		//	ring4_sign1      = ring_method.define_abstract(ring4_icon, 6);
		}

		// glyph:

			constexpr auto ring_cglyph(const icon_type & icon) const
				{ return value.template cequip<ring_cmethod_type>().glyph_ctext(icon); }

		// image:

			constexpr auto ring_cimage(const sign_type & sign) const
				{ return value.template cequip<ring_cmethod_type>().image_ctext(sign); }
	};

	constexpr auto test0 = concord_test<unsigned long>{};

	void print_test_types()
	{
		print_array(test0.ring_cglyph(test0.ring1_icon));
	//	print_array(test0.ring_cglyph(test0.ring4_icon));

		printf("\n");
	}

	void print_test_images()
	{
		print_array(test0.ring_cimage(test0.ring1_sign1));
		print_array(test0.ring_cimage(test0.ring1_sign2));
		print_array(test0.ring_cimage(test0.ring1_sign3));
	//	print_array(test0.ring_cimage(test0.ring4_sign1));

		printf("\n");
	}

/***********************************************************************************************************************/

// tuple:

	template<typename SizeType>
	struct concord_test
	{
		using size_type          = SizeType;
		using concord_type       = resolve_concord_type<size_type, size_type, concord_pack_0, 100>;
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

	// main:

		print_test_types();
		print_test_images();
		print_array(*test0.value.crecord());

/***********************************************************************************************************************/

// cotuple:

	template<typename SizeType>
	struct concord_test
	{
		using size_type            = SizeType;
		using concord_type         = resolve_concord_type<size_type, size_type, concord_pack_0, 100>;
		using icon_type            = icon<size_type>;
		using sign_type            = sign<size_type>;

		using ring_cmethod_type    = resolve_cmethod < concord_type, concord_ring_cmethod    >;
		using ring_method_type     = resolve_method  < concord_type, concord_ring_method     >;
		using tuple_cmethod_type   = resolve_cmethod < concord_type, concord_tuple_cmethod   >;
		using tuple_method_type    = resolve_method  < concord_type, concord_tuple_method    >;
		using cotuple_cmethod_type = resolve_cmethod < concord_type, concord_cotuple_cmethod >;
		using cotuple_method_type  = resolve_method  < concord_type, concord_cotuple_method  >;

		concord_type value;

		icon_type ring1_icon;
		icon_type ring4_icon;
		icon_type ring8_icon;

		sign_type ring1_sign1;
		sign_type ring4_sign1;
		sign_type ring8_sign1;

		icon_type tuple1_icon;
		sign_type tuple1_sign;

		icon_type cotuple1_icon;
		sign_type cotuple1_sign;

		constexpr concord_test()
		{
			auto ring_method    = value.template equip<ring_method_type>();
			auto tuple_method   = value.template equip<tuple_method_type>();
			auto cotuple_method = value.template equip<cotuple_method_type>();

			ring1_icon          = ring_method.declare_type(1);
			ring4_icon          = ring_method.declare_type(4);
			ring8_icon          = ring_method.declare_type(8);

			ring1_sign1         = ring_method.define_abstract(ring1_icon, 5);
			ring4_sign1         = ring_method.define_abstract(ring4_icon, 6);
			ring8_sign1         = ring_method.define_abstract(ring8_icon, 7);

		//	tuple1_icon         = tuple_method.declare_type({ ring1_icon, ring4_icon, ring8_icon });
		//	tuple1_sign         = tuple_method.define_abstract(
		//				tuple1_icon, {ring1_sign1, ring4_sign1, ring8_sign1});

			cotuple1_icon       = cotuple_method.declare_type({ ring1_icon, ring4_icon, ring8_icon });
			cotuple1_sign       = cotuple_method.define_abstract(cotuple1_icon, 1, ring4_sign1);
		}

		// glyph:

			constexpr auto ring_cglyph(const icon_type & icon) const
				{ return value.template cequip<ring_cmethod_type>().glyph_ctext(icon); }

			constexpr auto tuple_cglyph(const icon_type & icon) const
				{ return value.template cequip<tuple_cmethod_type>().glyph_ctext(icon); }

			constexpr auto cotuple_cglyph(const icon_type & icon) const
				{ return value.template cequip<cotuple_cmethod_type>().glyph_ctext(icon); }

		// image:

			constexpr auto ring_cimage(const sign_type & sign) const
				{ return value.template cequip<ring_cmethod_type>().image_ctext(sign); }

			constexpr auto tuple_cimage(const sign_type & sign) const
				{ return value.template cequip<tuple_cmethod_type>().image_ctext(sign); }

			constexpr auto cotuple_cimage(const sign_type & sign) const
				{ return value.template cequip<cotuple_cmethod_type>().image_ctext(sign); }
	};

	constexpr auto test0 = concord_test<unsigned long>{};

	void print_test_types()
	{
		print_array(test0.ring_cglyph(test0.ring1_icon));
		print_array(test0.ring_cglyph(test0.ring4_icon));
		print_array(test0.ring_cglyph(test0.ring8_icon));

	//	print_array(test0.tuple_cglyph(test0.tuple1_icon));

		print_array(test0.cotuple_cglyph(test0.cotuple1_icon));

		printf("\n");
	}

	void print_test_images()
	{
		print_array(test0.ring_cimage(test0.ring1_sign1));
		print_array(test0.ring_cimage(test0.ring4_sign1));
		print_array(test0.ring_cimage(test0.ring8_sign1));

	//	print_array(test0.tuple_cimage(test0.tuple1_sign));

		print_array(test0.cotuple_cimage(test0.cotuple1_sign));

		printf("\n");
	}

/***********************************************************************************************************************/

// list (experimental):

	template<typename SizeType>
	struct concord_test
	{
		using size_type            = SizeType;
		using glyph_pack           = cctmp::T_pack_Vs<100, 10, 10, 10, 10, 10>;
		using space_pack           = cctmp::T_pack_Vs<  0,  0,  0,  0,  0,  0>;
		using image_pack           = cctmp::T_pack_Vs<100, 10, 10, 10, 10, 10>;
		using concord_type         = concord<size_type, size_type, glyph_pack, space_pack, image_pack, 100>;
		using icon_type            = icon<size_type>;
		using sign_type            = sign<size_type>;

		using empty_cmethod_type   = resolve_cmethod < concord_type, concord_empty_cmethod   >;
		using empty_method_type    = resolve_method  < concord_type, concord_empty_method    >;
		using ring_cmethod_type    = resolve_cmethod < concord_type, concord_ring_cmethod    >;
		using ring_method_type     = resolve_method  < concord_type, concord_ring_method     >;
		using tuple_cmethod_type   = resolve_cmethod < concord_type, concord_tuple_cmethod   >;
		using tuple_method_type    = resolve_method  < concord_type, concord_tuple_method    >;
		using cotuple_cmethod_type = resolve_cmethod < concord_type, concord_cotuple_cmethod >;
		using cotuple_method_type  = resolve_method  < concord_type, concord_cotuple_method  >;

		concord_type value;

		icon_type empty_icon;
		icon_type ring8_icon;

		sign_type empty_sign;
		sign_type ring8_sign;

		icon_type tuple_icon;
		sign_type tuple_sign;

		icon_type cotuple_icon;
		sign_type cotuple_sign;

		icon_type list_icon;

		constexpr concord_test()
		{
			auto empty_method   = value.template equip<empty_method_type>();
			auto ring_method    = value.template equip<ring_method_type>();
			auto tuple_method   = value.template equip<tuple_method_type>();
			auto cotuple_method = value.template equip<cotuple_method_type>();

			empty_icon          = empty_method.declare_type();
			ring8_icon          = ring_method.declare_type(8);

			empty_sign          = empty_method.define_abstract(empty_icon);
			ring8_sign          = ring_method.define_abstract(ring8_icon, 7);

			tuple_icon          = tuple_method.declare_type({ ring8_icon , list_icon });
			tuple_sign          = tuple_method.define_abstract(tuple_icon, { ring8_sign , list_icon });

			cotuple_icon        = cotuple_method.declare_type({ empty_icon , tuple_icon });
			cotuple_sign0       = cotuple_method.define_abstract(cotuple_icon, 0, empty_sign);
			cotuple_sign1       = cotuple_method.define_abstract(cotuple_icon, 1, tuple_sign);
		}

		// glyph:

			constexpr auto ring_cglyph(const icon_type & icon) const
				{ return value.template cequip<ring_cmethod_type>().glyph_ctext(icon); }

			constexpr auto tuple_cglyph(const icon_type & icon) const
				{ return value.template cequip<tuple_cmethod_type>().glyph_ctext(icon); }

			constexpr auto cotuple_cglyph(const icon_type & icon) const
				{ return value.template cequip<cotuple_cmethod_type>().glyph_ctext(icon); }

		// image:

			constexpr auto ring_cimage(const sign_type & sign) const
				{ return value.template cequip<ring_cmethod_type>().image_ctext(sign); }

			constexpr auto tuple_cimage(const sign_type & sign) const
				{ return value.template cequip<tuple_cmethod_type>().image_ctext(sign); }

			constexpr auto cotuple_cimage(const sign_type & sign) const
				{ return value.template cequip<cotuple_cmethod_type>().image_ctext(sign); }
	};

	constexpr auto test0 = concord_test<unsigned long>{};

	void print_test_types()
	{
		print_array(test0.ring_cglyph(test0.ring1_icon));
		print_array(test0.ring_cglyph(test0.ring4_icon));
		print_array(test0.ring_cglyph(test0.ring8_icon));

	//	print_array(test0.tuple_cglyph(test0.tuple1_icon));

		print_array(test0.cotuple_cglyph(test0.cotuple1_icon));

		printf("\n");
	}

	void print_test_images()
	{
		print_array(test0.ring_cimage(test0.ring1_sign1));
		print_array(test0.ring_cimage(test0.ring4_sign1));
		print_array(test0.ring_cimage(test0.ring8_sign1));

	//	print_array(test0.tuple_cimage(test0.tuple1_sign));

		print_array(test0.cotuple_cimage(test0.cotuple1_sign));

		printf("\n");
	}

/***********************************************************************************************************************/

