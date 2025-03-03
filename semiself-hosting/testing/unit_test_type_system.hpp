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

		//	print_array(*_test_0.value.csymbol()->cglyph()->ctext());
		//	print_array(*_test_0.value.csymbol()->cimage()->ctext());

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
			ring8_icon       = ring_method.declare_type(8); // duplicate.

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

// function:

	template<typename SizeType>
	struct concord_test_function : public concord_test<SizeType>
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
				CI::define_argument , 0 ,            0 , 1 , // 01
				CI::argument        , 1 , CP::to_carry , 0   // 02
			};

		// square:

			constexpr static size_type square_contr[36] =
			{
				CI::program         , 7 ,            0 , 3 , // 00: action,  lines, atomic,   next
				CI::define_argument , 0 ,            0 , 1 , // 01: action,  index,  start, finish
				CI::split           , 2 ,            0 , 3 , // 02: action, global,  start, finish
				CI::function        , 7 , CP::to_stack , 1 , // 03: action, inline, policy,   next
				CI::argument        , 1 , CP::to_stack , 1 , // 04: action, inline, policy,   next
				CI::argument        , 1 , CP::to_stack , 1 , // 05: action, inline, policy,   next
				CI::apply           , 2 , CP::to_carry , 0 , // 06: action, inline, policy,   next
			// multiply:
				CI::program         , 2 ,            1 , 1 , // 07: action,  lines, atomic,   next
				CI::multiply        , 0 , CP::to_carry , 0   // 08: action,   none, policy,   next
			};

		// sum of squares:

			constexpr static size_type sum_of_sq_contr[84] =
			{
				CI::program         , 11 ,            0 , 3 ,	// 00
				CI::define_argument ,  0 ,            0 , 1 ,	// 01 x
				CI::define_argument ,  1 ,            1 , 2 ,	// 02 y
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
				CI::define_argument ,  0 ,            0 , 1 ,	// 12 z
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
				CI::define_argument ,  0 ,            0 , 1 ,	// 01 n
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
				CI::define_argument ,  0 ,            0 , 1 ,	// 01 n
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

		constexpr concord_test_function()
		{
			auto ring_method     = base::ring_method();
			auto function_method = base::function_method();

			ring8_icon           = ring_method    .declare_type(8);
			unary_icon           = function_method.declare_type({ ring8_icon, ring8_icon });
			binary_icon          = function_method.declare_type({ ring8_icon, ring8_icon, ring8_icon });

			identity_sign        = function_method.define_abstract( unary_icon,  identity_contr);
			square_sign          = function_method.define_abstract( unary_icon,    square_contr);
			sum_of_sq_sign       = function_method.define_abstract(binary_icon, sum_of_sq_contr);
			factorial_sign       = function_method.define_abstract( unary_icon, factorial_contr);
			fibonacci_sign       = function_method.define_abstract( unary_icon, fibonacci_contr);
		}

		constexpr auto eval_cmethod() const { return base::value.template cequip<eval_cmethod_type>(); }
	};

	constexpr auto function_test_0 = concord_test_function<unsigned long>{};

	void concord_function_test()
	{
		// glyph:

			print_array(function_test_0.function_cglyph(function_test_0.unary_icon));
			print_array(function_test_0.function_cglyph(function_test_0.binary_icon));

			printf("\n");

		// image:

			print_array(function_test_0.function_cimage(function_test_0.square_sign));
			print_array(function_test_0.function_cimage(function_test_0.sum_of_sq_sign));
			print_array(function_test_0.function_cimage(function_test_0.factorial_sign));
			print_array(function_test_0.function_cimage(function_test_0.fibonacci_sign));

			printf("\n");
	}

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

		//	empty_sign          = empty_method.define_abstract(empty_icon);
		//	string_sign         = space_method.define_abstract(string_icon, empty_sign);

		//	for (size_type k = 0; k != 5; ++k)
		//	{
		//		ring8_sign = ring_method.define_abstract(ring8_icon, k);
		//		space_sign  = space_method.define_abstract(space_icon, ring8_sign, space_sign);
		//	}
		}

		constexpr auto to_icon(const mode_type & mode) const
			{ return base::space_cmethod().to_icon(mode); }
	};

	constexpr auto space_test_0 = concord_test_space<unsigned long>{};

	void concord_space_test()
	{
		// glyph:

			print_array(space_test_0.ring_cglyph(space_test_0.to_icon(space_test_0.char_mode)));
		//	print_array(space_test_0.ring_cglyph(space_test_0.string_mode));

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

/***********************************************************************************************************************/
/***********************************************************************************************************************/

