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

// concord:

	//	print_array(*test0.value.csymbol()->cglyph()->ctext());
	//	print_array(*test0.value.csymbol()->cimage()->ctext());

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// size pack:

	template<typename SizeType>
	struct concord_size_pack_0
	{
		using size_type            				= SizeType;

		constexpr static size_type concord_size			= 1000;

		constexpr static size_type glyph_size			= 1000;

		constexpr static size_type space_size			=   50;
		constexpr static size_type space_0			=   10;
		constexpr static size_type space_1			=   10;
		constexpr static size_type space_2			=   10;

		constexpr static size_type image_size			=  500;

		constexpr static size_type book_builtin			=  100;
		constexpr static size_type book_tuple			=   10;
		constexpr static size_type book_cotuple			=   10;
		constexpr static size_type book_function		=   10;
		constexpr static size_type book_recurse			=    5;
		constexpr static size_type book_identity		=  100;
		constexpr static size_type book_l_than			=   50;
		constexpr static size_type book_l_than_or_eq		=   50;
		constexpr static size_type book_r_than			=   50;
		constexpr static size_type book_r_than_or_eq		=   50;
		constexpr static size_type book_exists			=  100;
		constexpr static size_type book_forall			=  100;
		constexpr static size_type book_message			=  100;

		using glyph_pack = cctmp::T_pack_Vs
		<
			glyph_size		,
			book_builtin		,
			book_tuple		,
			book_cotuple		,
			book_function		,
			book_recurse		,
			book_identity		,
			book_l_than		,
			book_l_than_or_eq	,
			book_r_than		,
			book_r_than_or_eq	,
			book_exists		,
			book_forall		,
			book_message
		>;

		using space_pack = cctmp::T_pack_Vs
		<
			space_size		,
			space_0			,
			space_1			,
			space_2
		>;

		using image_pack = cctmp::T_pack_Vs
		<
			image_size		,
			book_builtin		,
			book_tuple		,
			book_cotuple		,
			book_function		,
			book_recurse		,
			book_identity		,
			book_l_than		,
			book_l_than_or_eq	,
			book_r_than		,
			book_r_than_or_eq	,
			book_exists		,
			book_forall		,
			book_message
		>;
	};

	template<typename type, typename size_type, template<typename> typename concord_pack>
	using resolve_concord_type = cctmp::concord
	<
		type, size_type,
		typename concord_pack<size_type>::glyph_pack,
		typename concord_pack<size_type>::space_pack,
		typename concord_pack<size_type>::image_pack,
		concord_pack<size_type>::concord_size
	>;

/***********************************************************************************************************************/

// interface:

	template<typename SizeType>
	struct concord_test
	{
		using size_type            = SizeType;
		using concord_type         = resolve_concord_type<size_type, size_type, concord_size_pack_0>;
		using icon_type            = cctmp::icon<size_type>;
		using sign_type            = cctmp::sign<size_type>;

		using empty_cmethod_type   = cctmp::resolve_cmethod < concord_type , cctmp::empty_cmethod     >;
		using empty_method_type    = cctmp::resolve_method  < concord_type , cctmp::empty_method      >;

		using ring_cmethod_type    = cctmp::resolve_cmethod < concord_type , cctmp::ring_cmethod      >;
		using ring_method_type     = cctmp::resolve_method  < concord_type , cctmp::ring_method       >;

		using char_cmethod_type    = cctmp::resolve_cmethod < concord_type , cctmp::utf8_char_cmethod >;
		using char_method_type     = cctmp::resolve_method  < concord_type , cctmp::utf8_char_method  >;

		using tuple_cmethod_type   = cctmp::resolve_cmethod < concord_type , cctmp::tuple_cmethod     >;
		using tuple_method_type    = cctmp::resolve_method  < concord_type , cctmp::tuple_method      >;

		using cotuple_cmethod_type = cctmp::resolve_cmethod < concord_type , cctmp::cotuple_cmethod   >;
		using cotuple_method_type  = cctmp::resolve_method  < concord_type , cctmp::cotuple_method    >;

	//	using list_cmethod_type    = cctmp::resolve_cmethod < concord_type , cctmp::list_cmethod      >;
	//	using list_method_type     = cctmp::resolve_method  < concord_type , cctmp::list_method       >;

	//	using space_cmethod_type   = cctmp::resolve_cmethod < concord_type , cctmp::space_cmethod     >;
	//	using space_method_type    = cctmp::resolve_method  < concord_type , cctmp::space_method      >;

		concord_type value;

		constexpr concord_test() { }

		// glyph:

			// empty:

				constexpr auto empty_cmethod() const
					{ return value.template cequip<empty_cmethod_type>(); }

				constexpr auto empty_method()
					{ return value.template equip<empty_method_type>(); }

				constexpr auto empty_cglyph(const icon_type & icon) const
					{ return empty_cmethod().glyph_ctext(icon); }

			// ring:

				constexpr auto ring_cmethod() const
					{ return value.template cequip<ring_cmethod_type>(); }

				constexpr auto ring_method()
					{ return value.template equip<ring_method_type>(); }

				constexpr auto ring_cglyph(const icon_type & icon) const
					{ return ring_cmethod().glyph_ctext(icon); }

			// utf8 char:

				constexpr auto char_cmethod() const
					{ return value.template cequip<char_cmethod_type>(); }

				constexpr auto char_method()
					{ return value.template equip<char_method_type>(); }

				constexpr auto char_cglyph(const icon_type & icon) const
					{ return char_cmethod().glyph_ctext(icon); }

			// tuple:

				constexpr auto tuple_cmethod() const
					{ return value.template cequip<tuple_cmethod_type>(); }

				constexpr auto tuple_method()
					{ return value.template equip<tuple_method_type>(); }

				constexpr auto tuple_cglyph(const icon_type & icon) const
					{ return tuple_cmethod().glyph_ctext(icon); }

			// cotuple:

				constexpr auto cotuple_cmethod() const
					{ return value.template cequip<cotuple_cmethod_type>(); }

				constexpr auto cotuple_method()
					{ return value.template equip<cotuple_method_type>(); }

				constexpr auto cotuple_cglyph(const icon_type & icon) const
					{ return cotuple_cmethod().glyph_ctext(icon); }

			// list:

			//	constexpr auto list_cmethod() const
			//		{ return value.template cequip<list_cmethod_type>(); }

			//	constexpr auto list_method()
			//		{ return value.template equip<list_method_type>(); }

			//	constexpr auto list_cglyph(const icon_type & icon) const
			//		{ return list_cmethod().glyph_ctext(icon); }

			// space:

			//	constexpr auto space_cmethod() const
			//		{ return value.template cequip<space_cmethod_type>(); }

			//	constexpr auto space_method()
			//		{ return value.template equip<space_method_type>(); }

			//	constexpr auto space_cglyph(const icon_type & icon) const
			//		{ return space_cmethod().glyph_ctext(icon); }

		// image:

			// empty:

				constexpr auto empty_cimage(const sign_type & sign) const
					{ return empty_cmethod().image_ctext(sign); }

			// ring:

				constexpr auto ring_cimage(const sign_type & sign) const
					{ return ring_cmethod().image_ctext(sign); }

			// utf8 char:

				constexpr auto char_cimage(const sign_type & sign) const
					{ return char_cmethod().image_ctext(sign); }

			// tuple:

				constexpr auto tuple_cimage(const sign_type & sign) const
					{ return tuple_cmethod().image_ctext(sign); }

			// cotuple:

				constexpr auto cotuple_cimage(const sign_type & sign) const
					{ return cotuple_cmethod().image_ctext(sign); }

			// list:

			//	constexpr auto list_cimage(const sign_type & sign) const
			//		{ return list_cmethod().image_ctext(sign); }

			// space:

			//	constexpr auto space_cimage(const sign_type & sign) const
			//		{ return space_cmethod().image_ctext(sign); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// test:

/***********************************************************************************************************************/

// empty (unique):

	template<typename SizeType>
	struct concord_test_empty : public concord_test<SizeType>
	{
		using base		= concord_test<SizeType>;
		using size_type		= SizeType;
		using icon_type		= typename base::icon_type;
		using sign_type		= typename base::sign_type;

		icon_type empty_icon;

		sign_type empty_sign_1;
		sign_type empty_sign_2;

		constexpr concord_test_empty()
		{
			auto empty_method = base::empty_method();

			empty_icon        = empty_method.declare_type();

			empty_sign_1      = empty_method.define_abstract(empty_icon);
			empty_sign_2      = empty_method.define_abstract(empty_icon);
		}
	};

	constexpr auto empty_test_0 = concord_test_empty<unsigned long>{};

	void concord_empty_test()
	{
		// glyph:

			print_array(empty_test_0.empty_cglyph(empty_test_0.empty_icon));

			printf("\n");

		// image:

			print_array(empty_test_0.empty_cimage(empty_test_0.empty_sign_1));
			print_array(empty_test_0.empty_cimage(empty_test_0.empty_sign_2));

			printf("\n");

		// value:

			auto crecord = empty_test_0.empty_cmethod().crecord();

			if (crecord.not_empty()) { print_array(crecord); }
			else                     { printf("empty");      }

			printf("\n");
	}

/***********************************************************************************************************************/

// ring (unique):

	template<typename SizeType>
	struct concord_test_ring : public concord_test<SizeType>
	{
		using base		= concord_test<SizeType>;
		using size_type		= SizeType;
		using icon_type		= typename base::icon_type;
		using sign_type		= typename base::sign_type;

		icon_type ring4_icon;
		icon_type ring8_icon;

		sign_type ring4_sign_1;

		sign_type ring8_sign_1;
		sign_type ring8_sign_2;
		sign_type ring8_sign_3;

		constexpr concord_test_ring()
		{
			auto ring_method = base::ring_method();

			ring4_icon       = ring_method.declare_type(4);
			ring8_icon       = ring_method.declare_type(8);

			ring4_sign_1     = ring_method.define_abstract(ring4_icon, 5);

			ring8_sign_1     = ring_method.define_abstract(ring8_icon, 7);
			ring8_sign_2     = ring_method.define_abstract(ring8_icon, 7);
			ring8_sign_3     = ring_method.define_abstract(ring8_icon, 8);
		}
	};

	constexpr auto ring_test_0 = concord_test_ring<unsigned long>{};

	void concord_ring_test()
	{
		// glyph:

			print_array(ring_test_0.ring_cglyph(ring_test_0.ring4_icon));
			print_array(ring_test_0.ring_cglyph(ring_test_0.ring8_icon));

			printf("\n");

		// image:

			print_array(ring_test_0.ring_cimage(ring_test_0.ring4_sign_1));
			print_array(ring_test_0.ring_cimage(ring_test_0.ring8_sign_1));
			print_array(ring_test_0.ring_cimage(ring_test_0.ring8_sign_2));
			print_array(ring_test_0.ring_cimage(ring_test_0.ring8_sign_3));

			printf("\n");

		// value:

			printf("%lu ", ring_test_0.ring_cmethod().cvalue(ring_test_0.ring4_sign_1));
			printf("%lu ", ring_test_0.ring_cmethod().cvalue(ring_test_0.ring8_sign_1));
			printf("%lu ", ring_test_0.ring_cmethod().cvalue(ring_test_0.ring8_sign_2));
			printf("%lu ", ring_test_0.ring_cmethod().cvalue(ring_test_0.ring8_sign_3));

			printf("\n");
	}

/***********************************************************************************************************************/

// utf8 char (unique):

	template<typename SizeType>
	struct concord_test_utf8_char : public concord_test<SizeType>
	{
		using base		= concord_test<SizeType>;
		using size_type		= SizeType;
		using icon_type		= typename base::icon_type;
		using sign_type		= typename base::sign_type;

		icon_type char1_icon;
		icon_type char2_icon;
		icon_type char3_icon;
		icon_type char4_icon;

		sign_type char1_sign_1;
		sign_type char2_sign_1;
		sign_type char3_sign_1;
		sign_type char4_sign_1;

		constexpr concord_test_utf8_char()
		{
			auto char_method = base::char_method();

			char1_icon       = char_method.declare_type(1);
			char2_icon       = char_method.declare_type(2);
			char3_icon       = char_method.declare_type(3);
			char4_icon       = char_method.declare_type(4);

			char1_sign_1     = char_method.define_abstract(char1_icon,                   0x24);
			char2_sign_1     = char_method.define_abstract(char2_icon,             0xc2, 0xa2);
			char3_sign_1     = char_method.define_abstract(char3_icon,       0xe2, 0x82, 0xac);
			char4_sign_1     = char_method.define_abstract(char4_icon, 0xf0, 0xa4, 0xad, 0xa2);
						// examples taken from:
						// https://www.unicode.mayastudios.com/examples/utf8.html
		}
	};

	constexpr auto char_test_0 = concord_test_utf8_char<unsigned long>{};

	void concord_utf8_char_test()
	{
		// glyph:

			print_array(char_test_0.char_cglyph(char_test_0.char1_icon));
			print_array(char_test_0.char_cglyph(char_test_0.char2_icon));
			print_array(char_test_0.char_cglyph(char_test_0.char3_icon));
			print_array(char_test_0.char_cglyph(char_test_0.char4_icon));

			printf("\n");

		// image:

			print_array(char_test_0.char_cimage(char_test_0.char1_sign_1));
			print_array(char_test_0.char_cimage(char_test_0.char2_sign_1));
			print_array(char_test_0.char_cimage(char_test_0.char3_sign_1));
			print_array(char_test_0.char_cimage(char_test_0.char4_sign_1));

			printf("\n");

		// value:

			printf("%lu ", char_test_0.char_cmethod().cvalue(char_test_0.char1_sign_1));
			printf("%lu ", char_test_0.char_cmethod().cvalue(char_test_0.char2_sign_1));
			printf("%lu ", char_test_0.char_cmethod().cvalue(char_test_0.char3_sign_1));
			printf("%lu ", char_test_0.char_cmethod().cvalue(char_test_0.char4_sign_1));

			printf("\n");
	}

/***********************************************************************************************************************/

// tuple:

	template<typename SizeType>
	struct concord_test_tuple : public concord_test<SizeType>
	{
		using base		= concord_test<SizeType>;
		using size_type		= SizeType;
		using icon_type		= typename base::icon_type;
		using sign_type		= typename base::sign_type;

		icon_type ring1_icon;
		icon_type ring4_icon;
		icon_type ring8_icon;
		icon_type tuple_icon;

		sign_type ring1_sign_1;
		sign_type ring4_sign_1;
		sign_type ring8_sign_1;
		sign_type tuple_sign_1;

		constexpr concord_test_tuple()
		{
			auto ring_method  = base::ring_method();
			auto tuple_method = base::tuple_method();

			ring1_icon        = ring_method .declare_type(1);
			ring4_icon        = ring_method .declare_type(4);
			ring8_icon        = ring_method .declare_type(8);
			tuple_icon        = tuple_method.declare_type({ ring1_icon, ring4_icon, ring8_icon });

			ring1_sign_1      = ring_method .define_abstract(ring1_icon, 8);
			ring4_sign_1      = ring_method .define_abstract(ring4_icon, 5);
			ring8_sign_1      = ring_method .define_abstract(ring8_icon, 7);

			sign_type args[3] = { ring1_sign_1 , ring4_sign_1 , ring8_sign_1 };
			tuple_sign_1      = tuple_method.define_abstract(tuple_icon, args);
		}
	};

	constexpr auto tuple_test_0 = concord_test_tuple<unsigned long>{};

	void concord_tuple_test()
	{
		// glyph:

			print_array(tuple_test_0.ring_cglyph(tuple_test_0.ring1_icon));
			print_array(tuple_test_0.ring_cglyph(tuple_test_0.ring4_icon));
			print_array(tuple_test_0.ring_cglyph(tuple_test_0.ring8_icon));
			print_array(tuple_test_0.ring_cglyph(tuple_test_0.tuple_icon));

			printf("\n");

		// image:

			print_array(tuple_test_0.ring_cimage(tuple_test_0.ring1_sign_1));
			print_array(tuple_test_0.ring_cimage(tuple_test_0.ring4_sign_1));
			print_array(tuple_test_0.ring_cimage(tuple_test_0.ring8_sign_1));
			print_array(tuple_test_0.ring_cimage(tuple_test_0.tuple_sign_1));

			printf("\n");

		// sign:

			auto s0 = tuple_test_0.tuple_cmethod().sub_sign(tuple_test_0.tuple_sign_1, 0);
			auto s1 = tuple_test_0.tuple_cmethod().sub_sign(tuple_test_0.tuple_sign_1, 1);
			auto s2 = tuple_test_0.tuple_cmethod().sub_sign(tuple_test_0.tuple_sign_1, 2);

		// value:

			printf("%lu ", tuple_test_0.ring_cmethod().cvalue(s0));
			printf("%lu ", tuple_test_0.ring_cmethod().cvalue(s1));
			printf("%lu ", tuple_test_0.ring_cmethod().cvalue(s2));

			printf("\n");
	}

/***********************************************************************************************************************/

// cotuple:

	template<typename SizeType>
	struct concord_test_cotuple : public concord_test<SizeType>
	{
		using base		= concord_test<SizeType>;
		using size_type		= SizeType;
		using icon_type		= typename base::icon_type;
		using sign_type		= typename base::sign_type;

		icon_type ring1_icon;
		icon_type ring4_icon;
		icon_type ring8_icon;
		icon_type cotuple_icon;

		sign_type ring1_sign_1;
		sign_type ring4_sign_1;
		sign_type ring8_sign_1;
		sign_type cotuple_sign_1;
		sign_type cotuple_sign_2;
		sign_type cotuple_sign_3;

		constexpr concord_test_cotuple()
		{
			auto ring_method    = base::ring_method();
			auto cotuple_method = base::cotuple_method();

			ring1_icon          = ring_method   .declare_type(1);
			ring4_icon          = ring_method   .declare_type(4);
			ring8_icon          = ring_method   .declare_type(8);
			cotuple_icon        = cotuple_method.declare_type({ ring1_icon, ring4_icon, ring8_icon });

			ring1_sign_1        = ring_method   .define_abstract(ring4_icon, 8);
			ring4_sign_1        = ring_method   .define_abstract(ring4_icon, 5);
			ring8_sign_1        = ring_method   .define_abstract(ring8_icon, 7);

			cotuple_sign_1      = cotuple_method.define_abstract(cotuple_icon, 0, ring1_sign_1);
			cotuple_sign_2      = cotuple_method.define_abstract(cotuple_icon, 1, ring4_sign_1);
			cotuple_sign_3      = cotuple_method.define_abstract(cotuple_icon, 2, ring8_sign_1);
		}
	};

	constexpr auto cotuple_test_0 = concord_test_cotuple<unsigned long>{};

	void concord_cotuple_test()
	{
		// glyph:

			print_array(cotuple_test_0.ring_cglyph(cotuple_test_0.ring1_icon));
			print_array(cotuple_test_0.ring_cglyph(cotuple_test_0.ring4_icon));
			print_array(cotuple_test_0.ring_cglyph(cotuple_test_0.ring8_icon));
			print_array(cotuple_test_0.ring_cglyph(cotuple_test_0.cotuple_icon));

			printf("\n");

		// image:

			print_array(cotuple_test_0.ring_cimage(cotuple_test_0.ring1_sign_1));
			print_array(cotuple_test_0.ring_cimage(cotuple_test_0.ring4_sign_1));
			print_array(cotuple_test_0.ring_cimage(cotuple_test_0.ring8_sign_1));
			print_array(cotuple_test_0.ring_cimage(cotuple_test_0.cotuple_sign_1));

			printf("\n");

		// sign:

			auto s1 = cotuple_test_0.cotuple_cmethod().sub_sign(cotuple_test_0.cotuple_sign_1);
			auto s2 = cotuple_test_0.cotuple_cmethod().sub_sign(cotuple_test_0.cotuple_sign_2);
			auto s3 = cotuple_test_0.cotuple_cmethod().sub_sign(cotuple_test_0.cotuple_sign_3);

		// value:

			printf("%lu ", cotuple_test_0.ring_cmethod().cvalue(s1));
			printf("%lu ", cotuple_test_0.ring_cmethod().cvalue(s2));
			printf("%lu ", cotuple_test_0.ring_cmethod().cvalue(s3));

			printf("\n");
	}

/***********************************************************************************************************************/

// list:

/*
	template<typename SizeType>
	struct concord_test_list : public concord_test<SizeType>
	{
		using base		= concord_test<SizeType>;
		using size_type		= SizeType;
		using icon_type		= typename base::icon_type;
		using sign_type		= typename base::sign_type;

		icon_type empty_icon;
		icon_type ring8_icon;
		icon_type list_icon;

		sign_type empty_sign;
		sign_type ring8_sign;
		sign_type list_sign;

		constexpr concord_test_list()
		{
			auto empty_method = base::empty_method();
			auto ring_method  = base::ring_method();
			auto list_method  = base::list_method();

			empty_icon        = empty_method.declare_type();
			ring8_icon        = ring_method .declare_type(8);
			list_icon         = list_method .declare_type(ring8_icon);

			empty_sign        = empty_method.define_abstract(empty_icon);
			list_sign         = list_method .define_abstract(list_icon, empty_sign);

			for (size_type k = 0; k != 5; ++k)
			{
				ring8_sign = ring_method.define_abstract(ring8_icon, k);
				list_sign  = list_method.define_abstract(list_icon, ring8_sign, list_sign);
			}
		}
	};

	constexpr auto list_test_0 = concord_test_list<unsigned long>{};

	void concord_list_test()
	{
		// glyph:

			print_array(list_test_0.ring_cglyph(list_test_0.list_icon));

			printf("\n");

		// image:

			print_array(list_test_0.ring_cimage(list_test_0.list_sign));

			printf("\n");

		// value:

			auto ring_cmethod = list_test_0.ring_cmethod();
			auto list_cmethod = list_test_0.list_cmethod();
			auto l_sign       = list_test_0.list_sign;

			for (auto k = 0; k != 5; ++k)
			{
				auto r_sign = list_cmethod.car_sign(l_sign);
				     l_sign = list_cmethod.cdr_sign(l_sign);

				printf("%lu ", ring_cmethod.cvalue(r_sign));
			}

			printf("\n");
	}
*/

/***********************************************************************************************************************/

// space:

/*
	template<typename SizeType>
	struct concord_test_space : public concord_test<SizeType>
	{
		using base		= concord_test<SizeType>;
		using size_type		= SizeType;
		using icon_type		= typename base::icon_type;
		using sign_type		= typename base::sign_type;

		size_type unicode_space;

		icon_type empty_icon;
		icon_type char1_icon;
		icon_type char2_icon;
		icon_type char3_icon;
		icon_type char4_icon;
		icon_type cotuple_icon;
		icon_type char_icon;
		icon_type list_icon;
		icon_type string_icon;

		sign_type empty_sign;
		sign_type char_sign;
		sign_type string_sign;

		constexpr concord_test_space() : unicode_space{}
		{
			auto empty_method   = base::empty_method   ();
			auto char_method    = base::char_method    ();
			auto cotuple_method = base::cotuple_method ();
			auto list_method    = base::list_method    ();
			auto space_method   = base::space_method   ();

			empty_icon          = empty_method.declare_type();
			char1_icon          = char_method .declare_type(1);
			char2_icon          = char_method .declare_type(2);
			char3_icon          = char_method .declare_type(3);
			char4_icon          = char_method .declare_type(4);

			unicode_space       = space_method.declare_space();
			icon_type chars[4]  = { char1_icon, char2_icon, char3_icon, char4_icon };
			cotuple_icon        = cotuple_method.declare_type(chars);
			char_icon           = space_method  .declare_type(unicode_space, cotuple_icon);
			list_icon           = list_method   .declare_type(char_icon);
			string_icon         = space_method  .declare_type(unicode_space, list_icon);

			empty_sign          = empty_method.define_abstract(empty_icon);
		//	string_sign         = space_method.define_abstract(string_icon, empty_sign);

		//	for (size_type k = 0; k != 5; ++k)
		//	{
		//		ring8_sign = ring_method.define_abstract(ring8_icon, k);
		//		space_sign  = space_method.define_abstract(space_icon, ring8_sign, space_sign);
		//	}
		}
	};

	constexpr auto space_test_0 = concord_test_space<unsigned long>{};

	void concord_space_test()
	{
		// glyph:

			print_array(space_test_0.ring_cglyph(space_test_0.char_icon));
			print_array(space_test_0.ring_cglyph(space_test_0.string_icon));

			printf("\n");

		// image:

		//	print_array(space_test_0.ring_cimage(space_test_0.string_sign));

		//	printf("\n");

		// value:

		//	auto ring_cmethod  = space_test_0.ring_cmethod();
		//	auto space_cmethod = space_test_0.space_cmethod();
		//	auto l_sign        = space_test_0.space_sign;

		//	for (auto k = 0; k != 5; ++k)
		//	{
		//		auto r_sign = space_cmethod.car_sign(l_sign);
		//		     l_sign = space_cmethod.cdr_sign(l_sign);

		//		printf("%lu ", ring_cmethod.cvalue(r_sign));
		//	}

		//	printf("\n");
	}
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

