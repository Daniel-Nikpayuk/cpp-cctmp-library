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

// type system (concord):

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
		using size_type             = SizeType;
		using concord_type          = resolve_concord_type<size_type, size_type, concord_size_pack_0>;
		using icon_type             = cctmp::icon<size_type>;
		using mode_type             = cctmp::mode<size_type>;
		using sign_type             = cctmp::sign<size_type>;

		using empty_cmethod_type    = cctmp::resolve_cmethod < concord_type , cctmp::empty_cmethod     >;
		using empty_method_type     = cctmp::resolve_method  < concord_type , cctmp::empty_method      >;

		using ring_cmethod_type     = cctmp::resolve_cmethod < concord_type , cctmp::ring_cmethod      >;
		using ring_method_type      = cctmp::resolve_method  < concord_type , cctmp::ring_method       >;

		using char_cmethod_type     = cctmp::resolve_cmethod < concord_type , cctmp::utf8_char_cmethod >;
		using char_method_type      = cctmp::resolve_method  < concord_type , cctmp::utf8_char_method  >;

		using tuple_cmethod_type    = cctmp::resolve_cmethod < concord_type , cctmp::tuple_cmethod     >;
		using tuple_method_type     = cctmp::resolve_method  < concord_type , cctmp::tuple_method      >;

		using cotuple_cmethod_type  = cctmp::resolve_cmethod < concord_type , cctmp::cotuple_cmethod   >;
		using cotuple_method_type   = cctmp::resolve_method  < concord_type , cctmp::cotuple_method    >;

		using function_cmethod_type = cctmp::resolve_cmethod < concord_type , cctmp::function_cmethod  >;
		using function_method_type  = cctmp::resolve_method  < concord_type , cctmp::function_method   >;

		using list_cmethod_type     = cctmp::resolve_cmethod < concord_type , cctmp::list_cmethod      >;
		using list_method_type      = cctmp::resolve_method  < concord_type , cctmp::list_method       >;

		using space_cmethod_type    = cctmp::resolve_cmethod < concord_type , cctmp::space_cmethod     >;
		using space_method_type     = cctmp::resolve_method  < concord_type , cctmp::space_method      >;

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

			// function:

				constexpr auto function_cmethod() const
					{ return value.template cequip<function_cmethod_type>(); }

				constexpr auto function_method()
					{ return value.template equip<function_method_type>(); }

				constexpr auto function_cglyph(const icon_type & icon) const
					{ return function_cmethod().glyph_ctext(icon); }

			// list:

				constexpr auto list_cmethod() const
					{ return value.template cequip<list_cmethod_type>(); }

				constexpr auto list_method()
					{ return value.template equip<list_method_type>(); }

				constexpr auto list_cglyph(const icon_type & icon) const
					{ return list_cmethod().glyph_ctext(icon); }

			// space:

				constexpr auto space_cmethod() const
					{ return value.template cequip<space_cmethod_type>(); }

				constexpr auto space_method()
					{ return value.template equip<space_method_type>(); }

				constexpr auto space_cglyph(const icon_type & icon) const
					{ return space_cmethod().glyph_ctext(icon); }

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

			// function:

				constexpr auto function_cimage(const sign_type & sign) const
					{ return function_cmethod().image_ctext(sign); }

			// list:

				constexpr auto list_cimage(const sign_type & sign) const
					{ return list_cmethod().image_ctext(sign); }

			// space:

				constexpr auto space_cimage(const sign_type & sign) const
					{ return space_cmethod().image_ctext(sign); }
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

			empty_sign_1      = empty_method.define_value(empty_icon);
			empty_sign_2      = empty_method.define_value(empty_icon);
		}
	};

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
			ring8_icon       = ring_method.declare_type(8); // duplicate.

			ring4_sign_1     = ring_method.define_value(ring4_icon, 5);

			ring8_sign_1     = ring_method.define_value(ring8_icon, 7);
			ring8_sign_2     = ring_method.define_value(ring8_icon, 7);
			ring8_sign_3     = ring_method.define_value(ring8_icon, 8);
		}
	};

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

		//	char1_sign_1     = char_method.define_value(char1_icon,                   0x24);
		//	char2_sign_1     = char_method.define_value(char2_icon,             0xc2, 0xa2);
		//	char3_sign_1     = char_method.define_value(char3_icon,       0xe2, 0x82, 0xac);
		//	char4_sign_1     = char_method.define_value(char4_icon, 0xf0, 0xa4, 0xad, 0xa2);
						// examples taken from:
						// https://www.unicode.mayastudios.com/examples/utf8.html
		}
	};

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

			ring1_sign_1      = ring_method .define_value(ring1_icon, 8);
			ring4_sign_1      = ring_method .define_value(ring4_icon, 5);
			ring8_sign_1      = ring_method .define_value(ring8_icon, 7);

			sign_type args[3] = { ring1_sign_1 , ring4_sign_1 , ring8_sign_1 };
			tuple_sign_1      = tuple_method.define_value(tuple_icon, args);
		}
	};

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

			ring1_sign_1        = ring_method   .define_value(ring4_icon, 8);
			ring4_sign_1        = ring_method   .define_value(ring4_icon, 5);
			ring8_sign_1        = ring_method   .define_value(ring8_icon, 7);

			cotuple_sign_1      = cotuple_method.define_value(cotuple_icon, 0, ring1_sign_1);
			cotuple_sign_2      = cotuple_method.define_value(cotuple_icon, 1, ring4_sign_1);
			cotuple_sign_3      = cotuple_method.define_value(cotuple_icon, 2, ring8_sign_1);
		}
	};

/***********************************************************************************************************************/

// function (continuation constructing):

	template<typename SizeType>
	struct concord_test_cc_function : public concord_test<SizeType>
	{
		using base		= concord_test<SizeType>;
		using concord_type	= typename base::concord_type;

		using size_type		= SizeType;
		using icon_type		= typename base::icon_type;
		using sign_type		= typename base::sign_type;
		using CI		= cctmp::CompoundInstr;
		using CP		= cctmp::CompoundPolicy;

		// identity:

			constexpr static size_type identity_contr[12] =
			{
				CI::program         , 3 ,            0 , 2 , // 00
				CI::argument_specs  , 0 ,            0 , 1 , // 01
				CI::argument        , 1 , CP::to_carry , 0   // 02
			};

		// square:

			constexpr static size_type square_contr[32] =
			{
				CI::program         , 6 ,            0 , 2 , // 00: action,  lines, atomic,   next
				CI::argument_specs  , 0 ,            0 , 1 , // 01: action,  index,  start, finish
				CI::function        , 6 , CP::to_stack , 1 , // 02: action, inline, policy,   next
				CI::argument        , 1 , CP::to_stack , 1 , // 03: action, inline, policy,   next
				CI::argument        , 1 , CP::to_stack , 1 , // 04: action, inline, policy,   next
				CI::apply           , 2 , CP::to_carry , 0 , // 05: action, offset, policy,   next
			// multiply:
				CI::program         , 2 ,            1 , 1 , // 06: action,  lines, atomic,   next
				CI::multiply        , 0 , CP::to_carry , 0   // 07: action,   none, policy,   next
			};

		// sum of squares:

			constexpr static size_type sum_of_sq_contr[84] =
			{
				CI::program         , 11 ,            0 , 3 ,	// 00
				CI::argument_specs  ,  0 ,            0 , 1 ,	// 01 x
				CI::argument_specs  ,  1 ,            1 , 2 ,	// 02 y
				CI::function        , 19 , CP::to_stack , 1 ,	// 03 +      0
				CI::function        , 11 , CP::to_stack , 1 ,	// 04 square 1
				CI::argument        ,  1 , CP::to_stack , 1 ,	// 05 x      2
				CI::apply           ,  4 , CP::to_stack , 1 ,	// 06
				CI::function        , 11 , CP::to_stack , 1 ,	// 07 square 1
				CI::argument        ,  2 , CP::to_stack , 1 ,	// 08 y      2
				CI::apply           ,  5 , CP::to_stack , 1 ,	// 09
				CI::apply           ,  3 , CP::to_carry , 0 ,	// 10
			// square:
				CI::program         ,  6 ,            0 , 2 ,	// 11
				CI::argument_specs  ,  0 ,            0 , 1 ,	// 12 z
				CI::function        , 17 , CP::to_stack , 1 ,	// 13 * 0
				CI::argument        , 12 , CP::to_stack , 1 ,	// 14 z 1
				CI::argument        , 12 , CP::to_stack , 1 ,	// 15 z 2
				CI::apply           ,  2 , CP::to_carry , 0 ,	// 16
			// multiply:
				CI::program         ,  2 ,            1 , 1 ,	// 17
				CI::multiply        ,  0 , CP::to_carry , 0 ,	// 18
			// add:
				CI::program         ,  2 ,            1 , 1 ,	// 19
				CI::add             ,  0 , CP::to_carry , 0	// 20
			};

		// factorial:

			constexpr static size_type factorial_contr[100] =
			{
				CI::program         , 17 ,            0 , 3 ,	// 00
				CI::function_specs  ,  0 ,            0 , 0 ,	// 01 f
				CI::argument_specs  ,  0 ,            0 , 1 ,	// 02 n
				CI::function        , 21 , CP::to_stack , 1 ,	// 03 = 0
				CI::argument        ,  2 , CP::to_stack , 1 ,	// 04 n 1
				CI::constant        ,  0 , CP::to_stack , 1 ,	// 05 0 2
				CI::apply           ,  2 , CP::to_carry , 1 ,	// 06
				CI::branch          , 23 ,            0 , 1 ,	// 07 1
				CI::function        , 17 , CP::to_stack , 1 ,	// 08 * 0
				CI::argument        ,  2 , CP::to_stack , 1 ,	// 09 n 1
				CI::recursive       ,  1 , CP::to_stack , 1 ,	// 10 f 2
				CI::function        , 19 , CP::to_stack , 1 ,	// 11 - 3
				CI::argument        ,  2 , CP::to_stack , 1 ,	// 12 n 4
				CI::constant        ,  1 , CP::to_stack , 1 ,	// 13 1 5
				CI::apply           ,  5 , CP::to_stack , 1 ,	// 14
				CI::apply           ,  4 , CP::to_stack , 1 ,	// 15
				CI::apply           ,  2 , CP::to_carry , 0 ,	// 16
			// multiply:
				CI::program         ,  2 ,            1 , 1 ,	// 17
				CI::multiply        ,  0 , CP::to_carry , 0 ,	// 18
			// subtract:
				CI::program         ,  2 ,            1 , 1 ,	// 19
				CI::subtract        ,  0 , CP::to_carry , 0 ,	// 20
			// equal:
				CI::program         ,  2 ,            1 , 1 ,	// 21
				CI::equal           ,  0 , CP::to_carry , 0 ,	// 22
			// one:
				CI::program         ,  2 ,            1 , 1 ,	// 23
				CI::constant        ,  1 , CP::to_carry , 0	// 24
			};

		// fibonacci:

			constexpr static size_type fibonacci_contr[120] =
			{
				CI::program         , 22 ,            0 , 3 ,	// 00
				CI::function_specs  ,  0 ,            0 , 0 ,	// 01 f
				CI::argument_specs  ,  0 ,            0 , 1 ,	// 02 n
				CI::function        , 26 , CP::to_stack , 1 ,	// 03 < 0
				CI::argument        ,  2 , CP::to_stack , 1 ,	// 04 n 1
				CI::constant        ,  2 , CP::to_stack , 1 ,	// 05 2 2
				CI::apply           ,  2 , CP::to_carry , 1 ,	// 06
				CI::branch          , 28 ,            0 , 1 ,	// 07 1
				CI::function        , 22 , CP::to_stack , 1 ,	// 08 + 0
				CI::recursive       ,  1 , CP::to_stack , 1 ,	// 09 f 1
				CI::function        , 24 , CP::to_stack , 1 ,	// 10 - 2
				CI::argument        ,  2 , CP::to_stack , 1 ,	// 11 n 3
				CI::constant        ,  1 , CP::to_stack , 1 ,	// 12 1 4
				CI::apply           ,  4 , CP::to_stack , 1 ,	// 13
				CI::apply           ,  3 , CP::to_stack , 1 ,	// 14
				CI::recursive       ,  1 , CP::to_stack , 1 ,	// 15 f 2
				CI::function        , 24 , CP::to_stack , 1 ,	// 16 - 3
				CI::argument        ,  2 , CP::to_stack , 1 ,	// 17 n 4
				CI::constant        ,  2 , CP::to_stack , 1 ,	// 18 2 5
				CI::apply           ,  5 , CP::to_stack , 1 ,	// 19
				CI::apply           ,  4 , CP::to_stack , 1 ,	// 20
				CI::apply           ,  2 , CP::to_carry , 0 ,	// 21
			// add:
				CI::program         ,  2 ,            1 , 1 ,	// 22
				CI::add             ,  0 , CP::to_carry , 0 ,	// 23
			// subtract:
				CI::program         ,  2 ,            1 , 1 ,	// 24
				CI::subtract        ,  0 , CP::to_carry , 0 ,	// 25
			// less than:
				CI::program         ,  2 ,            1 , 1 ,	// 26
				CI::l_than          ,  0 , CP::to_carry , 0 ,	// 27
			// one:
				CI::program         ,  2 ,            1 , 1 ,	// 28
				CI::constant        ,  1 , CP::to_carry , 0	// 29
			};

		icon_type ring8_icon;
		icon_type unary_icon;
		icon_type binary_icon;

		sign_type identity_sign;
		sign_type square_sign;
		sign_type sum_of_sq_sign;
		sign_type factorial_sign;
		sign_type fibonacci_sign;

		constexpr concord_test_cc_function()
		{
			auto ring_method     = base::ring_method();
			auto function_method = base::function_method();

			ring8_icon           = ring_method    .declare_type(8);
			unary_icon           = function_method.declare_type({ ring8_icon, ring8_icon });
			binary_icon          = function_method.declare_type({ ring8_icon, ring8_icon, ring8_icon });

			identity_sign        = function_method.define_value( unary_icon,  identity_contr);
			square_sign          = function_method.define_value( unary_icon,    square_contr);
			sum_of_sq_sign       = function_method.define_value(binary_icon, sum_of_sq_contr);
			factorial_sign       = function_method.define_value( unary_icon, factorial_contr);
			fibonacci_sign       = function_method.define_value( unary_icon, fibonacci_contr);
		}
	};

/***********************************************************************************************************************/

// function (virtual machine):

	template<typename SizeType>
	struct concord_test_vm_function : public concord_test<SizeType>
	{
		using base		= concord_test<SizeType>;
		using concord_type	= typename base::concord_type;
		using eval_cmethod_type	= cctmp::resolve_eval_cmethod<concord_type, 10, 10, 10>;

		using size_type		= SizeType;
		using icon_type		= typename base::icon_type;
		using sign_type		= typename base::sign_type;
		using CI		= cctmp::CompoundInstr;
		using CP		= cctmp::CompoundPolicy;

		// identity:

			constexpr static size_type identity_contr[12] =
			{
				CI::program         , 3 ,            0 , 2 , // 00
				CI::argument_specs  , 0 ,            0 , 1 , // 01
				CI::argument        , 1 , CP::to_carry , 0   // 02
			};

		// square:

			constexpr static size_type square_contr[32] =
			{
				CI::program         , 6 ,            0 , 2 , // 00: action,  lines, atomic,   next
				CI::argument_specs  , 0 ,            0 , 1 , // 01: action,  index,  start, finish
				CI::function        , 6 , CP::to_stack , 1 , // 02: action, inline, policy,   next
				CI::argument        , 1 , CP::to_stack , 1 , // 03: action, inline, policy,   next
				CI::argument        , 1 , CP::to_stack , 1 , // 04: action, inline, policy,   next
				CI::apply           , 0 , CP::to_carry , 0 , // 05: action, offset, policy,   next
			// multiply:
				CI::program         , 2 ,            1 , 1 , // 06: action,  lines, atomic,   next
				CI::multiply        , 0 , CP::to_carry , 0   // 07: action,   none, policy,   next
			};

		// sum of squares:

			constexpr static size_type sum_of_sq_contr[84] =
			{
				CI::program         , 11 ,            0 , 3 ,	// 00
				CI::argument_specs  ,  0 ,            0 , 1 ,	// 01 x
				CI::argument_specs  ,  1 ,            1 , 2 ,	// 02 y
				CI::function        , 19 , CP::to_stack , 1 ,	// 03 +      0
				CI::function        , 11 , CP::to_stack , 1 ,	// 04 square 1
				CI::argument        ,  1 , CP::to_stack , 1 ,	// 05 x      2
				CI::apply           ,  1 , CP::to_stack , 1 ,	// 06
				CI::function        , 11 , CP::to_stack , 1 ,	// 07 square 1
				CI::argument        ,  2 , CP::to_stack , 1 ,	// 08 y      2
				CI::apply           ,  2 , CP::to_stack , 1 ,	// 09
				CI::apply           ,  0 , CP::to_carry , 0 ,	// 10
			// square:
				CI::program         ,  6 ,            0 , 2 ,	// 11
				CI::argument_specs  ,  0 ,            0 , 1 ,	// 12 z
				CI::function        , 17 , CP::to_stack , 1 ,	// 13 * 0
				CI::argument        , 12 , CP::to_stack , 1 ,	// 14 z 1
				CI::argument        , 12 , CP::to_stack , 1 ,	// 15 z 2
				CI::apply           ,  0 , CP::to_carry , 0 ,	// 16
			// multiply:
				CI::program         ,  2 ,            1 , 1 ,	// 17
				CI::multiply        ,  0 , CP::to_carry , 0 ,	// 18
			// add:
				CI::program         ,  2 ,            1 , 1 ,	// 19
				CI::add             ,  0 , CP::to_carry , 0	// 20
			};

		// factorial:

			constexpr static size_type factorial_contr[96] =
			{
				CI::program         , 16 ,            0 , 2 ,	// 00
				CI::argument_specs  ,  0 ,            0 , 1 ,	// 01 n
				CI::function        , 20 , CP::to_stack , 1 ,	// 02 = 0
				CI::argument        ,  1 , CP::to_stack , 1 ,	// 03 n 1
				CI::constant        ,  0 , CP::to_stack , 1 ,	// 04 0 2
				CI::apply           ,  0 , CP::to_carry , 1 ,	// 05
				CI::branch          , 22 ,            0 , 1 ,	// 06 1
				CI::function        , 16 , CP::to_stack , 1 ,	// 07 * 0
				CI::argument        ,  1 , CP::to_stack , 1 ,	// 08 n 1
				CI::function        ,  0 , CP::to_stack , 1 ,	// 09 f 2
				CI::function        , 18 , CP::to_stack , 1 ,	// 10 - 3
				CI::argument        ,  1 , CP::to_stack , 1 ,	// 11 n 4
				CI::constant        ,  1 , CP::to_stack , 1 ,	// 12 1 5
				CI::apply           ,  3 , CP::to_stack , 1 ,	// 13
				CI::apply           ,  2 , CP::to_stack , 1 ,	// 14
				CI::apply           ,  0 , CP::to_carry , 0 ,	// 15
			// multiply:
				CI::program         ,  2 ,            1 , 1 ,	// 16
				CI::multiply        ,  0 , CP::to_carry , 0 ,	// 17
			// subtract:
				CI::program         ,  2 ,            1 , 1 ,	// 18
				CI::subtract        ,  0 , CP::to_carry , 0 ,	// 19
			// equal:
				CI::program         ,  2 ,            1 , 1 ,	// 20
				CI::equal           ,  0 , CP::to_carry , 0 ,	// 21
			// one:
				CI::program         ,  2 ,            1 , 1 ,	// 22
				CI::constant        ,  1 , CP::to_carry , 0	// 23
			};

		// fibonacci:

			constexpr static size_type fibonacci_contr[116] =
			{
				CI::program         , 21 ,            0 , 2 ,	// 00
				CI::argument_specs  ,  0 ,            0 , 1 ,	// 01 n
				CI::function        , 25 , CP::to_stack , 1 ,	// 02 < 0
				CI::argument        ,  1 , CP::to_stack , 1 ,	// 03 n 1
				CI::constant        ,  2 , CP::to_stack , 1 ,	// 04 2 2
				CI::apply           ,  0 , CP::to_carry , 1 ,	// 05
				CI::branch          , 27 ,            0 , 1 ,	// 06 1
				CI::function        , 21 , CP::to_stack , 1 ,	// 07 + 0
				CI::function        ,  0 , CP::to_stack , 1 ,	// 08 f 1
				CI::function        , 23 , CP::to_stack , 1 ,	// 09 - 2
				CI::argument        ,  1 , CP::to_stack , 1 ,	// 10 n 3
				CI::constant        ,  1 , CP::to_stack , 1 ,	// 11 1 4
				CI::apply           ,  2 , CP::to_stack , 1 ,	// 12
				CI::apply           ,  1 , CP::to_stack , 1 ,	// 13
				CI::function        ,  0 , CP::to_stack , 1 ,	// 14 f 2
				CI::function        , 23 , CP::to_stack , 1 ,	// 15 - 3
				CI::argument        ,  1 , CP::to_stack , 1 ,	// 16 n 4
				CI::constant        ,  2 , CP::to_stack , 1 ,	// 17 2 5
				CI::apply           ,  3 , CP::to_stack , 1 ,	// 18
				CI::apply           ,  2 , CP::to_stack , 1 ,	// 19
				CI::apply           ,  0 , CP::to_carry , 0 ,	// 20
			// add:
				CI::program         ,  2 ,            1 , 1 ,	// 21
				CI::add             ,  0 , CP::to_carry , 0 ,	// 22
			// subtract:
				CI::program         ,  2 ,            1 , 1 ,	// 23
				CI::subtract        ,  0 , CP::to_carry , 0 ,	// 24
			// less than:
				CI::program         ,  2 ,            1 , 1 ,	// 25
				CI::l_than          ,  0 , CP::to_carry , 0 ,	// 26
			// one:
				CI::program         ,  2 ,            1 , 1 ,	// 27
				CI::constant        ,  1 , CP::to_carry , 0	// 28
			};

		icon_type ring8_icon;
		icon_type unary_icon;
		icon_type binary_icon;

		sign_type identity_sign;
		sign_type square_sign;
		sign_type sum_of_sq_sign;
		sign_type factorial_sign;
		sign_type fibonacci_sign;

		constexpr concord_test_vm_function()
		{
			auto ring_method     = base::ring_method();
			auto function_method = base::function_method();

			ring8_icon           = ring_method    .declare_type(8);
			unary_icon           = function_method.declare_type({ ring8_icon, ring8_icon });
			binary_icon          = function_method.declare_type({ ring8_icon, ring8_icon, ring8_icon });

			identity_sign        = function_method.define_value( unary_icon,  identity_contr);
			square_sign          = function_method.define_value( unary_icon,    square_contr);
			sum_of_sq_sign       = function_method.define_value(binary_icon, sum_of_sq_contr);
			factorial_sign       = function_method.define_value( unary_icon, factorial_contr);
			fibonacci_sign       = function_method.define_value( unary_icon, fibonacci_contr);
		}

		constexpr auto eval_cmethod() const { return base::value.template cequip<eval_cmethod_type>(); }
	};

/***********************************************************************************************************************/

// static:

	// identity:

		template<template<typename> typename concord_test_function, typename SizeType>
		struct static_identity_test
		{
			constexpr static auto value		= concord_test_function<SizeType>{};
			using type				= decltype(value);

			using concord_type			= typename type::concord_type;
			using size_type				= typename concord_type::size_type;
			using size_ctype			= typename concord_type::size_ctype;

			constexpr static auto & function	= value.identity_sign;
		};

	// square:

		template<template<typename> typename concord_test_function, typename SizeType>
		struct static_square_test
		{
			constexpr static auto value		= concord_test_function<SizeType>{};
			using type				= decltype(value);

			using concord_type			= typename type::concord_type;
			using size_type				= typename concord_type::size_type;
			using size_ctype			= typename concord_type::size_ctype;

			constexpr static auto & function	= value.square_sign;
		};

	// sum of squares:

		template<template<typename> typename concord_test_function, typename SizeType>
		struct static_sum_of_sq_test
		{
			constexpr static auto value		= concord_test_function<SizeType>{};
			using type				= decltype(value);

			using concord_type			= typename type::concord_type;
			using size_type				= typename concord_type::size_type;
			using size_ctype			= typename concord_type::size_ctype;

			constexpr static auto & function	= value.sum_of_sq_sign;
		};

	// factorial:

		template<template<typename> typename concord_test_function, typename SizeType>
		struct static_factorial_test
		{
			constexpr static auto value		= concord_test_function<SizeType>{};
			using type				= decltype(value);

			using concord_type			= typename type::concord_type;
			using size_type				= typename concord_type::size_type;
			using size_ctype			= typename concord_type::size_ctype;

			constexpr static auto & function	= value.factorial_sign;
		};

	// fibonacci:

		template<template<typename> typename concord_test_function, typename SizeType>
		struct static_fibonacci_test
		{
			constexpr static auto value		= concord_test_function<SizeType>{};
			using type				= decltype(value);

			using concord_type			= typename type::concord_type;
			using size_type				= typename concord_type::size_type;
			using size_ctype			= typename concord_type::size_ctype;

			constexpr static auto & function	= value.fibonacci_sign;
		};

/***********************************************************************************************************************/

// list:

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

			empty_sign        = empty_method.define_value(empty_icon);
			list_sign         = list_method .define_value(list_icon, empty_sign);

			for (size_type k = 0; k != 5; ++k)
			{
				ring8_sign = ring_method.define_value(ring8_icon, k);
				list_sign  = list_method.define_value(list_icon, ring8_sign, list_sign);
			}
		}
	};

/***********************************************************************************************************************/

// space:

	template<typename SizeType>
	struct concord_test_space : public concord_test<SizeType>
	{
		using base		= concord_test<SizeType>;
		using size_type		= SizeType;
		using icon_type		= typename base::icon_type;
		using mode_type		= typename base::mode_type;
		using sign_type		= typename base::sign_type;

		size_type unicode_space;

		icon_type empty_icon;
		icon_type char1_icon;
		icon_type char2_icon;
		icon_type char3_icon;
		icon_type char4_icon;
		icon_type cotuple_icon;
		icon_type list_icon;

		mode_type char_mode;
		mode_type string_mode;

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
			char_mode           = space_method  .declare_type(unicode_space, cotuple_icon);
		//	list_icon           = list_method   .declare_type(char_icon);
		//	string_mode         = space_method  .declare_type(unicode_space, list_icon);

		//	empty_sign          = empty_method.define_value(empty_icon);
		//	string_sign         = space_method.define_value(string_icon, empty_sign);

		//	for (size_type k = 0; k != 5; ++k)
		//	{
		//		ring8_sign = ring_method.define_value(ring8_icon, k);
		//		space_sign  = space_method.define_value(space_icon, ring8_sign, space_sign);
		//	}
		}

		constexpr auto to_icon(const mode_type & mode) const
			{ return base::space_cmethod().to_icon(mode); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

