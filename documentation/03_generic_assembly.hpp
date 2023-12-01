/************************************************************************************************************************
**
** Copyright 2022-2023 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// case studies:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// prerequisites:

	constexpr auto constant_machine_frame			= cctmp::constant_machine_frame; 

/***********************************************************************************************************************/

// definitions:

//	#define NIK_UNIT_TEST_SQUARE_V0
//	#define NIK_UNIT_TEST_SQUARE_V1
//	#define NIK_UNIT_TEST_SUM_OF_SQUARES_V0
//	#define NIK_UNIT_TEST_SUM_OF_SQUARES_V1
//	#define NIK_UNIT_TEST_TWICE_V0
//	#define NIK_UNIT_TEST_PLUS_N_V0
//	#define NIK_UNIT_TEST_TWO_X_SQD_V0
//	#define NIK_UNIT_TEST_X_SQD_PLUS_Y4_V0

//	#define NIK_UNIT_TEST_X_TO5_PLUS1_V0
//	#define NIK_UNIT_TEST_REASSIGN_V0
//	#define NIK_UNIT_TEST_SEMIDYNAMIC_TYPING_V0
//	#define NIK_UNIT_TEST_SEMIDYNAMIC_TYPING_V1
//	#define NIK_UNIT_TEST_BINARY_DISPATCH_V0
//	#define NIK_UNIT_TEST_BINARY_DISPATCH_V1
//	#define NIK_UNIT_TEST_FACTORIAL_V0
//	#define NIK_UNIT_TEST_FACTORIAL_V1
//	#define NIK_UNIT_TEST_FACTORIAL_V2
//	#define NIK_UNIT_TEST_FACTORIAL_V3
//	#define NIK_UNIT_TEST_FACTORIAL_V4
//	#define NIK_UNIT_TEST_FIBONACCI_V0
//	#define NIK_UNIT_TEST_FIBONACCI_V1
//	#define NIK_UNIT_TEST_FALL_FACT_2_V0
//	#define NIK_UNIT_TEST_FALL_FACT_2_V1
//	#define NIK_UNIT_TEST_VOID_EFFECTS_V0
//	#define NIK_UNIT_TEST_SIDE_EFFECTS_V0

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// complex numbers:

/***********************************************************************************************************************/

// class:

	struct complex_number
	{
		float x;
		float y;

		constexpr complex_number() : x{}, y{} { }
		constexpr complex_number(const float _x, const float _y) : x{_x}, y{_y} { }

		constexpr const bool operator == (const complex_number & c) const
			{ return (x == c.x && y == c.y); }

		constexpr const bool operator != (const complex_number & c) const
			{ return (x != c.x || y != c.y); }

		constexpr const complex_number operator + (const complex_number & c) const
			{ return complex_number(x + c.x, y + c.y); }

		constexpr const complex_number operator * (const complex_number & c) const
		{
			auto x0 = x * c.x;
			auto x1 = y * c.y;

			auto y0 = x * c.y;
			auto y1 = y * c.x;

			return complex_number(x0 - x1, y0 + y1);
		}
	};

/***********************************************************************************************************************/

// frame:

	constexpr auto complex_constant_frame_callable()
	{
		return cctmp::frame
		(
			cctmp::U_char,

			cctmp::binding( "_0_0i" , complex_number{0, 0} ),
			cctmp::binding( "_1_0i" , complex_number{1, 0} ),
			cctmp::binding( "_0_1i" , complex_number{0, 1} )
		);
	};

	constexpr auto complex_constant_frame = cctmp::_static_callable_<complex_constant_frame_callable>;

/***********************************************************************************************************************/

// make:

	constexpr auto make_complex(const float x, const float y) { return complex_number(x, y); }
	constexpr auto _make_complex_ = cctmp::_wrap_<make_complex>;

/***********************************************************************************************************************/

// print:

	void print_complex(const complex_number & c) { printf("(%f, %f)\n", c.x, c.y); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// features:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// labels                 :
// test/branch            :
// goto                   :

// application assignment :
// argument assignment    :
// environment assignment :
// copy/paste assignment  :
// variable assignment    :

// environment operator   :
// environment operand    :

// semidynamic typing     :

// single recursion       :
// general recursion      :

// mutability semantics   :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// square:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _square_v0()
	{
		return source
		(
			"square x         ;"

			"body:            ;"
			". = multiply x x ;"
			"return _         ;"
		);
	}

#ifdef NIK_UNIT_TEST_SQUARE_V0

	template<typename T>
	constexpr auto square_v0(T v)
		{ return chord_apply<_square_v0, cctmp::null_env, T>(v); }

#endif

/***********************************************************************************************************************/

// version 1:

	constexpr auto _square_v1()
	{
		return source
		(
			"square x                      ;"

			"definitions:                  ;"
			"sq # argpose[1]{multiply 0 0} ;"

			"body:                         ;"
			". = sq x                      ;"
			"return _                      ;"
		);
	}

#ifdef NIK_UNIT_TEST_SQUARE_V1

	template<typename T>
	constexpr auto square_v1(T v)
		{ return chord_apply<_square_v1, cctmp::null_env, T>(v); }

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sum of squares:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _sum_of_squares_v0()
	{
		return source
                (
			"sum_of_squares x y ;"

			"body:              ;"
			"x = multiply x x   ;"
			"y = multiply y y   ;"
			". = add      x y   ;"
			"return _           ;"
		);
	}

#ifdef NIK_UNIT_TEST_SUM_OF_SQUARES_V0

	template<typename T>
	constexpr auto sum_of_squares_v0(T x, T y)
		{ return chord_apply<_sum_of_squares_v0, cctmp::null_env, T>(x, y); }

#endif

/***********************************************************************************************************************/

// version 1:

	constexpr auto _sum_of_squares_v1()
	{
		return source
	        (
			"f x y                                ;"

			"definitions:                         ;"
			"sq        # argpose[1]{multiply 0 0} ;"
			"sum_of_sq # subpose[2]{add sq sq}    ;"

			"body:                                ;"
			". = sum_of_sq x y                    ;"
			"return _                             ;"
		);
	}

#ifdef NIK_UNIT_TEST_SUM_OF_SQUARES_V1

	template<typename T>
	constexpr auto sum_of_squares_v1(T x, T y)
		{ return chord_apply<_sum_of_squares_v1, cctmp::null_env, T>(x, y); }

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// twice:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _twice_v0()
	{
		return source
		(
			"twice x                     ;"

			"definitions:                ;"
			"tw # curry[1]{multiply two} ;"

			"body:                       ;"
			". = tw x                    ;"
			"return _                    ;"

			, cctmp::binding( "two" , 2 )
		);
	}

#ifdef NIK_UNIT_TEST_TWICE_V0

	template<typename T>
	constexpr auto twice_v0(T x)
		{ return chord_apply<_twice_v0, cctmp::null_env, T>(x); }

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// plus n:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _plus_n_v0()
	{
		return source
		(
			"plus_n m n              ;"

			"definitions:            ;"
			"add_n # curry[1]{add n} ;"

			"body:                   ;"
			". = add_n m             ;"
			"return _                ;"
		);
	}

#ifdef NIK_UNIT_TEST_PLUS_N_V0

	template<typename T>
	constexpr auto plus_n_v0(T m, T n)
		{ return chord_apply<_plus_n_v0, cctmp::null_env, T>(m, n); }

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// two_x_sqd:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _two_x_sqd_v0()
	{
		return source
	        (
			"f x                                   ;"

			"definitions:                          ;"
			"sq        # argpose[1]{multiply 0 0}  ;"
			"sum_of_sq # subpose[2]{add sq sq}     ;"
			"two_x_sqd # argpose[1]{sum_of_sq 0 0} ;"

			"body:                                 ;"
			". = two_x_sqd x                       ;"
			"return _                              ;"
		);
	}

#ifdef NIK_UNIT_TEST_TWO_X_SQD_V0

	template<typename T>
	constexpr auto two_x_sqd_v0(T x)
		{ return chord_apply<_two_x_sqd_v0, cctmp::null_env, T>(x); }

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// x_sqd_plus_y4:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _x_sqd_plus_y4_v0()
	{
		return source
	        (
			"f x y                                    ;"

			"definitions:                             ;"
			"           sq # argpose[1]{multiply 0 0} ;"
			"    sum_of_sq # subpose[2]{add sq sq}    ;"
			"            y = sq y                     ;"
			"y4_plus_x_sqd # curry[1]{sum_of_sq y}    ;"

			"body:                                    ;"
			". = y4_plus_x_sqd x                      ;"
			"return _                                 ;"
		);
	}

#ifdef NIK_UNIT_TEST_X_SQD_PLUS_Y4_V0

	template<typename T>
	constexpr auto x_sqd_plus_y4_v0(T x, T y)
		{ return chord_apply<_x_sqd_plus_y4_v0, cctmp::null_env, T>(x, y); }

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// x^5 + 1:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _x_to5_plus1_v0()
	{
		return source
		(
			"x_to5_plus1 x y        ;"

			"body:                  ;"
			"y # one                ;"
			". = multiply x x x x x ;"
			". = add _ y            ;"
			"return _               ;"
		);
	}

#ifdef NIK_UNIT_TEST_X_TO5_PLUS1_V0

	template<typename T>
	constexpr auto x_to5_plus1_v0(T x)
	{
		constexpr auto e0 = cctmp::env<constant_machine_frame>;

		return chord_apply<_x_to5_plus1_v0, e0, T>(x, T(0));
	}

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// reassign:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _reassign_v0()
	{
		return source
		(
			"f x y              ;"

			"body:              ;"
			"  x # y            ;"
			"  return x         ;"
		);
	}

#ifdef NIK_UNIT_TEST_REASSIGN_V0

	template<typename T1, typename T2>
	constexpr auto reassign_v0(T1 x, T2 y)
		{ return chord_apply<_reassign_v0, cctmp::null_env, T2>(x, y); }

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// semidynamic typing:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _semidynamic_typing_v0()
	{
		return source
		(
			"func c complex_one n       ;"

			"body:                      ;"
			"  test equal c complex_one ;"
			"  branch set_c_to_five     ;"
			"  c = increment n          ;" // { c = increment c; } would error.
			"  return c                 ;"

			"set_c_to_five:             ;"
			"  c # five                 ;"
			"  return c                 ;"
		);
	}

#ifdef NIK_UNIT_TEST_SEMIDYNAMIC_TYPING_V0

	constexpr auto semidynamic_typing_v0(const complex_number & c, int n)
	{
		constexpr auto c1 = complex_number(1, 0);
		constexpr auto e0 = cctmp::env<constant_machine_frame>;

		return chord_apply<_semidynamic_typing_v0, e0, int>(c, c1, n);
	}

#endif

/***********************************************************************************************************************/

// version 1:

	constexpr auto _semidynamic_typing_v1()
	{
		return source
		(
			"func c n               ;"

			"body:                  ;"
			"  test equal c _1_0i   ;"
			"  branch set_c_to_five ;"
			"  c = increment n      ;" // { c = increment c; } would error.
			"  return c             ;"

			"set_c_to_five:         ;"
			"  c # five             ;"
			"  return c             ;"
		);
	}

#ifdef NIK_UNIT_TEST_SEMIDYNAMIC_TYPING_V1

	constexpr auto semidynamic_typing_v1(const complex_number & c, int n)
	{
		constexpr auto e0 = cctmp::env<constant_machine_frame, complex_constant_frame>;

		return chord_apply<_semidynamic_typing_v1, e0, int>(c, n);
	}

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// binary dispatch:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _binary_dispatch_v0()
	{
		return source
		(
			"dispatch n g h x y         ;"

			"body:                      ;"
			"  test equal n zero        ;"
			"  branch to_g              ;"
			"  f # h                    ;"
			"goto done                  ;"

			"to_g:                      ;"
			"  f # g                    ;"

			"done:                      ;"
			"  . = f x y                ;"
			"  return _                 ;"
		);
	}

#ifdef NIK_UNIT_TEST_BINARY_DISPATCH_V0

	template<typename G, typename H, typename T>
	constexpr auto binary_dispatch_v0(int n, G g, H h, T x, T y)
	{
		constexpr auto e0 = cctmp::env<constant_machine_frame>;

		return chord_apply<_binary_dispatch_v0, e0, T>(n, g, h, x, y);
	}

#endif

/***********************************************************************************************************************/

// version 1:

	constexpr auto _binary_dispatch_v1()
	{
		return source
		(
			"dispatch n g h x y         ;"

			"body:                      ;"
			"  f # h                    ;"
			"  test equal n zero        ;"
			"  branch to_g              ;"
			"goto done                  ;"

			"to_g:                      ;"
			"  f # g                    ;"

			"done:                      ;"
			"  . = f x y                ;"
			"  return _                 ;"
		);
	}

#ifdef NIK_UNIT_TEST_BINARY_DISPATCH_V1

	template<typename G, typename H, typename T>
	constexpr auto binary_dispatch_v1(int n, G g, H h, T x, T y)
	{
		constexpr auto e0 = cctmp::env<constant_machine_frame>;

		return chord_apply<_binary_dispatch_v1, e0, T>(n, g, h, x, y);
	}

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// factorial:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _factorial_v0()
	{
		return source
		(
			"factorial n        ;"

			"body:              ;"
			"test equal n zero  ;"
			"branch done        ;"
			". = subtract n one ;"
			". = factorial _    ;"
			". = multiply n _   ;"
			"return _           ;"

			"done:              ;"
			"return one         ;"
		);
	}

#ifdef NIK_UNIT_TEST_FACTORIAL_V0

	template<typename T>
	constexpr auto factorial_v0(T v)
	{
		constexpr auto e0 = cctmp::env<constant_machine_frame>;

		return chord_apply<_factorial_v0, e0, T>(v);
	}

#endif

/***********************************************************************************************************************/

// version 1:

	constexpr auto _factorial_v1()
	{
		return source
		(
			"factorial n one     ;"

			"body:               ;"
			"test is_zero n      ;"
			"branch done         ;"
			". = decrement n     ;"
			". = factorial _ one ;"
			". = multiply n _    ;"
			"return _            ;"

			"done:               ;"
			"return one          ;"
		);
	}

#ifdef NIK_UNIT_TEST_FACTORIAL_V1

	template<typename T>
	constexpr auto factorial_v1(T v)
		{ return chord_apply<_factorial_v1, cctmp::null_env, T>(v, T(1)); }

#endif

/***********************************************************************************************************************/

// version 2:

	constexpr auto _factorial_v2()
	{
		return source
		(
			"factorial p n     ;"

			"body:             ;"
			"test is_zero n    ;"
			"branch done       ;"
			"p = multiply p n  ;"
			"n = decrement n   ;"
			". = factorial p n ;"
			"return _          ;"

			"done:             ;"
			"return p          ;"
		);
	}

#ifdef NIK_UNIT_TEST_FACTORIAL_V2

	template<typename T>
	constexpr auto factorial_v2(T v)
		{ return chord_apply<_factorial_v2, cctmp::null_env, T>(T(1), v); }

#endif

/***********************************************************************************************************************/

// version 3:

	constexpr auto _factorial_v3()
	{
		return source
		(
			"factorial p n    ;"

			"loop:            ;"
			"test is_zero n   ;"
			"branch done      ;"
			"p = multiply p n ;"
			"n = decrement n  ;"
			"goto loop        ;"

			"done:            ;"
			"return p         ;"
		);
	}

#ifdef NIK_UNIT_TEST_FACTORIAL_V3

	template<typename T>
	constexpr auto factorial_v3(T v)
		{ return chord_apply<_factorial_v3, cctmp::null_env, T>(T(1), v); }

#endif

/***********************************************************************************************************************/

// version 4:

	constexpr auto _factorial_v4()
	{
		return source
		(
			"factorial n      ;"

			"body:            ;"
			"p # one          ;"
			"test is_zero n   ;"
			"branch done      ;"
			". = decrement n  ;"
			"p = factorial _  ;"
			". = multiply n p ;"
			"return _         ;"

			"done:            ;"
			"return p         ;"
		);
	}

#ifdef NIK_UNIT_TEST_FACTORIAL_V4

	template<typename T>
	constexpr auto factorial_v4(T v)
	{
		constexpr auto e0 = cctmp::env<constant_machine_frame>;

		return chord_apply<_factorial_v4, e0, T>(v);
	}

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fibonacci:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _fibonacci_v0()
	{
		return source
		(
			"fibonacci n n1 n2             ;"

			"body:                         ;"
			"  test equal n zero           ;"
			"  branch done                 ;"
			"  test equal n one            ;"
			"  branch done                 ;"
			"  n1 = decrement n            ;"
			"  n2 = decrement n1           ;"
			"  n1 = fibonacci n1 zero zero ;"
			"  n2 = fibonacci n2 zero zero ;"
			"  .  = add n1 n2              ;"
			"  return _                    ;"

			"done:                         ;"
			"  return one                  ;"
		);
	}

#ifdef NIK_UNIT_TEST_FIBONACCI_V0

	template<typename T>
	constexpr auto fibonacci_v0(T v)
	{
		constexpr auto e0 = cctmp::env<constant_machine_frame>;

		return chord_apply<_fibonacci_v0, e0, T>(v, T(0), T(0));
	}

#endif

/***********************************************************************************************************************/

// version 1:

	constexpr auto _fibonacci_v1()
	{
		return source
		(
			"fibonacci n         ;"

			"definitions:        ;"
			"  n1 # zero         ;"
			"  n2 # zero         ;"

			"body:               ;"
			"  test equal n zero ;"
			"  branch done       ;"
			"  test equal n one  ;"
			"  branch done       ;"
			"  n1 = decrement n  ;"
			"  n2 = decrement n1 ;"
			"  n1 = fibonacci n1 ;"
			"  n2 = fibonacci n2 ;"
			"  .  = add n1 n2    ;"
			"  return _          ;"

			"done:               ;"
			"  return one        ;"
		);
	}

#ifdef NIK_UNIT_TEST_FIBONACCI_V1

	template<typename T>
	constexpr auto fibonacci_v1(T v)
	{
		constexpr auto e0 = cctmp::env<constant_machine_frame>;

		return chord_apply<_fibonacci_v1, e0, T>(v);
	}

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// falling factorial (exponent 2):

/***********************************************************************************************************************/

// version 0 (pointer):

	struct T_ptr_side_dec
	{
		template<typename T>
		constexpr static auto result(T x)
		{
			auto v = *x;

			*x = *x - 1;

			return v;
		}

	}; constexpr auto _ptr_side_dec_ = U_store_T<T_ptr_side_dec>;

	template<bool punct>
	constexpr auto _fall_fact_2_v0()
	{
		if constexpr (punct)

			return source
			(
				"fall_fact_2 x       ;"

				"definitions:        ;"
				"  v # zero          ;"

				"body:               ;"
				"  v = side_dec !x   ;" // works!
				"  . = dereference x ;"
				"  . = multiply v _  ;"
				"  return _          ;"

				, cctmp::binding( "side_dec" , _ptr_side_dec_ )
			);
		else
			return source
			(
				"fall_fact_2 x       ;"

				"definitions:        ;"
				"  v # zero          ;"

				"body:               ;"
				"  v = side_dec x    ;" // error: read only.
				"  . = dereference x ;"
				"  . = multiply v _  ;"
				"  return _          ;"

				, cctmp::binding( "side_dec" , _ptr_side_dec_ )
			);
	}

#ifdef NIK_UNIT_TEST_FALL_FACT_2_V0

	template<bool punct, typename T>
	constexpr auto fall_fact_2_v0(T x)
	{
		constexpr auto src = _fall_fact_2_v0<punct>;

		return chord_apply<src, cctmp::env<constant_machine_frame>, T>(&x);
	}

#endif

/***********************************************************************************************************************/

// version 1 (reference):

	struct T_ref_side_dec
	{
		template<typename T>
		constexpr static auto result(T & x)
		{
			auto v = x;

			x = x - 1;

			return v;
		}

	}; constexpr auto _ref_side_dec_ = U_store_T<T_ref_side_dec>;

	template<bool punct>
	constexpr auto _fall_fact_2_v1()
	{
		if constexpr (punct)

			return source
			(
				"fall_fact_2 x       ;"

				"definitions:        ;"
				"  v # zero          ;"

				"body:               ;"
				"  v = side_dec !x   ;" // works!
				"  . = multiply v x  ;"
				"  return _          ;"

				, cctmp::binding( "side_dec" , _ref_side_dec_ )
			);
		else
			return source
			(
				"fall_fact_2 x       ;"

				"definitions:        ;"
				"  v # zero          ;"

				"body:               ;"
				"  v = side_dec x    ;" // error: read only.
				"  . = multiply v x  ;"
				"  return _          ;"

				, cctmp::binding( "side_dec" , _ref_side_dec_ )
			);
	}

#ifdef NIK_UNIT_TEST_FALL_FACT_2_V1

	template<bool punct, typename T>
	constexpr auto fall_fact_2_v1(T x)
	{
		constexpr auto src = _fall_fact_2_v1<punct>;

		return chord_apply<src, cctmp::env<constant_machine_frame>, T, T&>(x);
	}

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// void effects:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _void_effects_v0()
	{
		return source
		(
			"f x y               ;"

			"body:               ;"
			"  . = increment y   ;"
			"  void appoint !x _ ;"
			"  return x          ;"
		);
	}

#ifdef NIK_UNIT_TEST_VOID_EFFECTS_V0

	template<typename T>
	constexpr auto void_effects_v0(T x)
		{ return chord_apply<_void_effects_v0, cctmp::null_env, T>(x, 2); }

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// side effects:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _side_effects_v0()
	{
		return source
		(
			"f x y              ;"

			"body:              ;"
			"   . = increment y ;"
			"  !x = appoint _   ;"
			"  return x         ;"
		);
	}

#ifdef NIK_UNIT_TEST_SIDE_EFFECTS_V0

	template<typename T>
	constexpr auto side_effects_v0(T x)
		{ return chord_apply<_side_effects_v0, cctmp::null_env, T>(x, 2); }

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

