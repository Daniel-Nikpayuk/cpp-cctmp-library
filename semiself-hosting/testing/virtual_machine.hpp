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

// virtual machine (type system):

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// main at:

	template<typename T>
	auto main_at(T n, int argc, char *argv[], T def = 0) -> T
	{
		auto pos = n + 1;

		if (pos < argc) return atoi(argv[pos]);
		else            return def;
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
		using MI		= cctmp::MachineInstr;
		using MP		= cctmp::MachinePolicy;

		// square:

			constexpr static size_type square_contr[32] =
			{
				MI::program         , 6 ,            0 , 2 , // line 0: action,  lines, atomic,   next
				MI::define_argument , 0 ,            0 , 1 , // line 1: action,  index,  start, finish
				MI::function        , 6 , MP::to_stack , 1 , // line 2: action, inline, policy,   next
				MI::argument        , 1 , MP::to_stack , 1 , // line 3: action, inline, policy,   next
				MI::argument        , 1 , MP::to_stack , 1 , // line 4: action, inline, policy,   next
				MI::apply           , 0 , MP::to_carry , 0 , // line 5: action, offset, policy,   next
			// multiply:
				MI::program         , 2 ,            1 , 1 , // line 6: action,  lines, atomic,   next
				MI::multiply        , 0 , MP::to_carry , 0   // line 7: action, offset, policy,   next
			};

		// sum of squares:

			constexpr static size_type sum_of_sq_contr[84] =
			{
				MI::program         , 11 ,            0 , 3 ,	// 00
				MI::define_argument ,  0 ,            0 , 1 ,	// 01 x
				MI::define_argument ,  1 ,            1 , 2 ,	// 02 y
				MI::function        , 19 , MP::to_stack , 1 ,	// 03 +      0
				MI::function        , 11 , MP::to_stack , 1 ,	// 04 square 1
				MI::argument        ,  1 , MP::to_stack , 1 ,	// 05 x      2
				MI::apply           ,  1 , MP::to_stack , 1 ,	// 06
				MI::function        , 11 , MP::to_stack , 1 ,	// 07 square 1
				MI::argument        ,  2 , MP::to_stack , 1 ,	// 08 y      2
				MI::apply           ,  2 , MP::to_stack , 1 ,	// 09
				MI::apply           ,  0 , MP::to_carry , 0 ,	// 10
			// square:
				MI::program         ,  6 ,            0 , 2 ,	// 11
				MI::define_argument ,  0 ,            0 , 1 ,	// 12 z
				MI::function        , 17 , MP::to_stack , 1 ,	// 13 * 0
				MI::argument        , 12 , MP::to_stack , 1 ,	// 14 z 1
				MI::argument        , 12 , MP::to_stack , 1 ,	// 15 z 2
				MI::apply           ,  0 , MP::to_carry , 0 ,	// 16
			// multiply:
				MI::program         ,  2 ,            1 , 1 ,	// 17
				MI::multiply        ,  0 , MP::to_carry , 0 ,	// 18
			// add:
				MI::program         ,  2 ,            1 , 1 ,	// 19
				MI::add             ,  0 , MP::to_carry , 0	// 20
			};

		// factorial:

			constexpr static size_type factorial_contr[96] =
			{
				MI::program         , 16 ,            0 , 2 ,	// 00
				MI::define_argument ,  0 ,            0 , 1 ,	// 01 n
				MI::function        , 20 , MP::to_stack , 1 ,	// 02 = 0
				MI::argument        ,  1 , MP::to_stack , 1 ,	// 03 n 1
				MI::constant        ,  0 , MP::to_stack , 1 ,	// 04 0 2
				MI::apply           ,  0 , MP::to_carry , 1 ,	// 05
				MI::branch          , 22 ,            0 , 1 ,	// 06 1
				MI::function        , 16 , MP::to_stack , 1 ,	// 07 * 0
				MI::argument        ,  1 , MP::to_stack , 1 ,	// 08 n 1
				MI::function        ,  0 , MP::to_stack , 1 ,	// 09 f 2
				MI::function        , 18 , MP::to_stack , 1 ,	// 10 - 3
				MI::argument        ,  1 , MP::to_stack , 1 ,	// 11 n 4
				MI::constant        ,  1 , MP::to_stack , 1 ,	// 12 1 5
				MI::apply           ,  3 , MP::to_stack , 1 ,	// 13
				MI::apply           ,  2 , MP::to_stack , 1 ,	// 14
				MI::apply           ,  0 , MP::to_carry , 0 ,	// 15
			// multiply:
				MI::program         ,  2 ,            1 , 1 ,	// 16
				MI::multiply        ,  0 , MP::to_carry , 0 ,	// 17
			// subtract:
				MI::program         ,  2 ,            1 , 1 ,	// 18
				MI::subtract        ,  0 , MP::to_carry , 0 ,	// 19
			// equal:
				MI::program         ,  2 ,            1 , 1 ,	// 20
				MI::equal           ,  0 , MP::to_carry , 0 ,	// 21
			// one:
				MI::program         ,  2 ,            1 , 1 ,	// 22
				MI::constant        ,  1 , MP::to_carry , 0	// 23
			};

		// fibonacci:

			constexpr static size_type fibonacci_contr[116] =
			{
				MI::program         , 21 ,            0 , 2 ,	// 00
				MI::define_argument ,  0 ,            0 , 1 ,	// 01 n
				MI::function        , 25 , MP::to_stack , 1 ,	// 02 < 0
				MI::argument        ,  1 , MP::to_stack , 1 ,	// 03 n 1
				MI::constant        ,  2 , MP::to_stack , 1 ,	// 04 2 2
				MI::apply           ,  0 , MP::to_carry , 1 ,	// 05
				MI::branch          , 27 ,            0 , 1 ,	// 06 1
				MI::function        , 21 , MP::to_stack , 1 ,	// 07 + 0
				MI::function        ,  0 , MP::to_stack , 1 ,	// 08 f 1
				MI::function        , 23 , MP::to_stack , 1 ,	// 09 - 2
				MI::argument        ,  1 , MP::to_stack , 1 ,	// 10 n 3
				MI::constant        ,  1 , MP::to_stack , 1 ,	// 11 1 4
				MI::apply           ,  2 , MP::to_stack , 1 ,	// 12
				MI::apply           ,  1 , MP::to_stack , 1 ,	// 13
				MI::function        ,  0 , MP::to_stack , 1 ,	// 14 f 2
				MI::function        , 23 , MP::to_stack , 1 ,	// 15 - 3
				MI::argument        ,  1 , MP::to_stack , 1 ,	// 16 n 4
				MI::constant        ,  2 , MP::to_stack , 1 ,	// 17 2 5
				MI::apply           ,  3 , MP::to_stack , 1 ,	// 18
				MI::apply           ,  2 , MP::to_stack , 1 ,	// 19
				MI::apply           ,  0 , MP::to_carry , 0 ,	// 20
			// add:
				MI::program         ,  2 ,            1 , 1 ,	// 21
				MI::add             ,  0 , MP::to_carry , 0 ,	// 22
			// subtract:
				MI::program         ,  2 ,            1 , 1 ,	// 23
				MI::subtract        ,  0 , MP::to_carry , 0 ,	// 24
			// less than:
				MI::program         ,  2 ,            1 , 1 ,	// 25
				MI::l_than          ,  0 , MP::to_carry , 0 ,	// 26
			// one:
				MI::program         ,  2 ,            1 , 1 ,	// 27
				MI::constant        ,  1 , MP::to_carry , 0	// 28
			};

		icon_type ring8_icon;
		icon_type unary_icon;
		icon_type binary_icon;

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

			square_sign          = function_method.define_abstract( unary_icon,    square_contr);
			sum_of_sq_sign       = function_method.define_abstract(binary_icon, sum_of_sq_contr);
			factorial_sign       = function_method.define_abstract( unary_icon, factorial_contr);
			fibonacci_sign       = function_method.define_abstract( unary_icon, fibonacci_contr);
		}

		constexpr auto eval_cmethod() const { return base::value.template cequip<eval_cmethod_type>(); }
	};

	constexpr auto function_test_0 = concord_test_function<unsigned long>{};

	// square:

		template<typename size_type>
		constexpr auto square(size_type const v)
		{
			auto eval_cmethod = function_test_0.eval_cmethod();
			eval_cmethod      . apply(function_test_0.square_sign, {v});

			return eval_cmethod.rtn_cat(0);
		}

	// sum of squares:

		template<typename size_type>
		constexpr auto sum_of_squares(size_type const v1, size_type const v2)
		{
			auto eval_cmethod = function_test_0.eval_cmethod();
			eval_cmethod      . apply(function_test_0.sum_of_sq_sign, {v1, v2});

			return eval_cmethod.rtn_cat(0);
		}

	// factorial:

		template<typename size_type>
		constexpr auto factorial(size_type const v)
		{
			auto eval_cmethod = function_test_0.eval_cmethod();
			eval_cmethod      . apply(function_test_0.factorial_sign, {v});

			return eval_cmethod.rtn_cat(0);
		}

	// fibonacci:

		template<typename size_type>
		constexpr auto fibonacci(size_type const v)
		{
			auto eval_cmethod = function_test_0.eval_cmethod();
			eval_cmethod      . apply(function_test_0.fibonacci_sign, {v});

			return eval_cmethod.rtn_cat(0);
		}

	// test:

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

		// square:

			static_assert(square<unsigned long>(5) == 25);

			printf("%lu\n", square<unsigned long>(5));

		// sum of squares:

			static_assert(sum_of_squares<unsigned long>(3, 7) == 58);

			printf("%lu\n", sum_of_squares<unsigned long>(3, 7));

		// factorial:

			static_assert(factorial<unsigned long>(5) == 120);

			printf("%lu\n", factorial<unsigned long>(5));

		// fibonacci:

			static_assert(fibonacci<unsigned long>(8) == 34);

			printf("%lu\n", fibonacci<unsigned long>(8));
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

