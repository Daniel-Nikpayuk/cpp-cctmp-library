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

// inventory:

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

// space:

/***********************************************************************************************************************/

// square:

	// v0:

		constexpr auto _chord_square_v0()
		{
			return cctmp::source
			(
				"main x           ;"

				"body:            ;"
				". = multiply x x ;"
				"return _         ;"
			);
		}

	// v1:

		constexpr auto _chord_square_v1()
		{
			return cctmp::source
			(
				"main x                        ;"

				"vars:                         ;"
				"declare sq                    ;"

				"defs:                         ;"
				"sq # argpose[1]{multiply 0 0} ;"

				"body:                         ;"
				". = sq x                      ;"
				"return _                      ;"
			);
		}

/***********************************************************************************************************************/

// sum of squares:

	// v0:

		constexpr auto _chord_sum_of_squares_v0()
		{
			return cctmp::source
		        (
				"main x y         ;"
		
				"body:            ;"
				"x = multiply x x ;"
				"y = multiply y y ;"
				". = add      x y ;"
				"return _         ;"
			);
		}

	// v1:

		constexpr auto _chord_sum_of_squares_v1()
		{
			return cctmp::source
		        (
				"main x y                             ;"
		
				"vars:                                ;"
				"declare sq sum_of_sq                 ;"
		
				"defs:                                ;"
				"sq        # argpose[1]{multiply 0 0} ;"
				"sum_of_sq # subpose[2]{add sq sq}    ;"
		
				"body:                                ;"
				". = sum_of_sq x y                    ;"
				"return _                             ;"
			);
		}

/***********************************************************************************************************************/

// twice:

	// v0:

		constexpr auto _chord_twice_v0()
		{
			return cctmp::source
			(
				"main x                         ;"

				"vars:                          ;"
				"declare twice                  ;"

				"defs:                          ;"
				"twice # curry[1]{multiply two} ;"

				"body:                          ;"
				". = twice x                    ;"
				"return _                       ;"

				, cctmp::binding( "two" , 2 )
			);
		}

/***********************************************************************************************************************/

// plus n:

	// v0:

		constexpr auto _chord_plus_n_v0()
		{
			return cctmp::source
			(
				"main m n                ;"

				"vars:                   ;"
				"declare add_n           ;"

				"defs:                   ;"
				"add_n # curry[1]{add n} ;"

				"body:                   ;"
				". = add_n m             ;"
				"return _                ;"
			);
		}

/***********************************************************************************************************************/

// two_x_sqd:

	// v0:

		constexpr auto _chord_two_x_sqd_v0()
		{
			return cctmp::source
		        (
				"main x                                ;"

				"vars:                                 ;"
				"declare sq sum_of_sq two_x_sqd        ;"

				"defs:                                 ;"
				"sq        # argpose[1]{multiply 0 0}  ;"
				"sum_of_sq # subpose[2]{add sq sq}     ;"
				"two_x_sqd # argpose[1]{sum_of_sq 0 0} ;"

				"body:                                 ;"
				". = two_x_sqd x                       ;"
				"return _                              ;"
			);
		}

/***********************************************************************************************************************/

// x_sqd_plus_y4:

	// v0:

		constexpr auto _chord_x_sqd_plus_y4_v0()
		{
			return cctmp::source
		        (
				"main x y                                 ;"

				"vars:                                    ;"
				"declare sq sum_of_sq y4_plus_x_sqd       ;"

				"defs:                                    ;"
				"           sq # argpose[1]{multiply 0 0} ;"
				"    sum_of_sq # subpose[2]{add sq sq}    ;"
				"            y = sq y                     ;"
				"y4_plus_x_sqd # curry[1]{sum_of_sq y}    ;"

				"body:                                    ;"
				". = y4_plus_x_sqd x                      ;"
				"return _                                 ;"
			);
		}

/***********************************************************************************************************************/

// x^5 + 1:

	// v0:

		constexpr auto _chord_x_to5_plus1_v0()
		{
			return cctmp::source
			(
				"main x y               ;"

				"body:                  ;"
				"y # one                ;"
				". = multiply x x x x x ;"
				". = add _ y            ;"
				"return _               ;"

				, cctmp::binding("one", 1)
			);
		}

/***********************************************************************************************************************/

// reassign:

	// v0:

		constexpr auto _chord_reassign_v0()
		{
			return cctmp::source
			(
				"main x y           ;"

				"body:              ;"
				"  x # y            ;"
				"  return x         ;"
			);
		}

/***********************************************************************************************************************/

// if then else:

	// v0:

		constexpr auto _chord_if_then_else_v0()
		{
			return cctmp::source
			(
				"main pred ante conse   ;"

				"body:                  ;"
				"  test equal pred zero ;"
				"  branch alt           ;"
				"  return conse         ;"

				"alt:                   ;"
				"  return ante          ;"
			);
		}

/***********************************************************************************************************************/

// semidynamic typing:

	// v0:

		constexpr auto _chord_semidynamic_typing_v0()
		{
			return cctmp::source
			(
				"type T                     ;"
				"main c complex_one n       ;"

				"body:                      ;"
				"  test equal c complex_one ;"
				"  branch set_c_to_five     ;"
				"  c = increment n          ;" // { c = increment c; } would error.
				"  return c                 ;"

				"set_c_to_five:             ;"
				"  c # 5:T                  ;"
				"  return c                 ;"
			);
		}

	// v1:

		constexpr auto _chord_semidynamic_typing_v1()
		{
			return cctmp::source
			(
				"type T                 ;"
				"main c n               ;"

				"body:                  ;"
				"  test equal c _1_0i   ;"
				"  branch set_c_to_five ;"
				"  c = increment n      ;" // { c = increment c; } would error.
				"  return c             ;"

				"set_c_to_five:         ;"
				"  c # 5:T              ;"
				"  return c             ;"
			);
		}

/***********************************************************************************************************************/

// binary dispatch:

	// v0:

		constexpr auto _chord_binary_dispatch_v0()
		{
			return cctmp::source
			(
				"main n g h x y             ;"

				"vars:                      ;"
				"define f                   ;"

				"body:                      ;"
				"  test equal n 0           ;"
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

	// v1:

		constexpr auto _chord_binary_dispatch_v1()
		{
			return cctmp::source
			(
				"main n g h x y             ;"

				"vars:                      ;"
				"define f                   ;"

				"body:                      ;"
				"  f # h                    ;"
				"  test equal n 0           ;"
				"  branch to_g              ;"
				"goto done                  ;"

				"to_g:                      ;"
				"  f # g                    ;"

				"done:                      ;"
				"  . = f x y                ;"
				"  return _                 ;"
			);
		}

/***********************************************************************************************************************/

// factorial:

	// v0:

		constexpr auto _chord_factorial_v0()
		{
			return cctmp::source
			(
				"type T             ;"
				"factorial n -> T   ;"

				"body:              ;"
				"  test equal n 0   ;"
				"  branch done      ;"
				"  . = subtract n 1 ;"
				"  . = factorial _  ;"
				"  . = multiply n _ ;"
				"  return _         ;"

				"done:              ;"
				"  return 1:T       ;"
			);
		}

	// v1:

		constexpr auto _chord_factorial_v1()
		{
			return cctmp::source
			(
				"type T               ;"
				"factorial n one -> T ;"

				"body:                ;"
				"test is_zero n       ;"
				"branch done          ;"
				". = decrement n      ;"
				". = factorial _ one  ;"
				". = multiply n _     ;"
				"return _             ;"

				"done:                ;"
				"return one           ;"
			);
		}

	// v2:

		constexpr auto _chord_factorial_v2()
		{
			return cctmp::source
			(
				"type T             ;"
				"factorial p n -> T ;"

				"body:              ;"
				"test is_zero n     ;"
				"branch done        ;"
				"p = multiply p n   ;"
				"n = decrement n    ;"
				". = factorial p n  ;"
				"return _           ;"

				"done:              ;"
				"return p           ;"
			);
		}

	// v3:

		constexpr auto _chord_factorial_v3()
		{
			return cctmp::source
			(
				"main p n         ;"

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

	// v4:

		constexpr auto _chord_factorial_v4()
		{
			return cctmp::source
			(
				"type T           ;"
				"factorial n -> T ;"

				"vars:            ;"
				"define p         ;"

				"body:            ;"
				"p # 1:T          ;"
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

	// v5:

		constexpr auto _chord_factorial_v5()
		{
			return cctmp::source
			(
				"type T           ;"
				"factorial n -> T ;"

				"body:            ;"
				"test is_zero n   ;"
				"branch done      ;"
				"goto cont        ;"

				"done:            ;"
				"return 1:T       ;"

				"cont:            ;"
				". = decrement n  ;"
				". = factorial _  ;"
				". = multiply n _ ;"
				"return _         ;"
			);
		}

/***********************************************************************************************************************/

// fibonacci:

	// v0:

		constexpr auto _chord_fibonacci_v0()
		{
			return cctmp::source
			(
				"type T                  ;"
				"fibonacci n n1 n2 -> T  ;"

				"body:                   ;"
				"  test equal n 0        ;"
				"  branch done           ;"
				"  test equal n 1        ;"
				"  branch done           ;"
				"  n1 = decrement n      ;"
				"  n2 = decrement n1     ;"
				"  n1 = fibonacci n1 0 0 ;"
				"  n2 = fibonacci n2 0 0 ;"
				"  .  = add n1 n2        ;"
				"  return _              ;"

				"done:                   ;"
				"  return 1:T            ;"
			);
		}

	// v1:

		constexpr auto _chord_fibonacci_v1()
		{
			return cctmp::source
			(
				"type T              ;"
				"fibonacci n -> T    ;"

				"vars:               ;"
				"define n1 n2        ;"

				"body:               ;"
				"  test equal n 0    ;"
				"  branch done       ;"
				"  test equal n 1    ;"
				"  branch done       ;"
				"  n1 = decrement n  ;"
				"  n2 = decrement n1 ;"
				"  n1 = fibonacci n1 ;"
				"  n2 = fibonacci n2 ;"
				"  .  = add n1 n2    ;"
				"  return _          ;"

				"done:               ;"
				"  return 1:T        ;"
			);
		}

/***********************************************************************************************************************/

// falling factorial (exponent 2):

	// v0 (pointer):

		struct T_ptr_side_dec
		{
			template<typename T>
			constexpr static auto result(T x)
			{
				auto v = *x;

				*x = *x - 1;

				return v;
			}

		}; constexpr auto _ptr_side_dec_ = cctmp::U_store_T<T_ptr_side_dec>;

		template<bool punct>
		constexpr auto _chord_fall_fact_2_v0()
		{
			if constexpr (punct)

				return cctmp::source
				(
					"fall_fact_2 x       ;"

					"vars:               ;"
					"  define v          ;"

					"body:               ;"
					"  v = side_dec !x   ;" // works!
					"  . = dereference x ;"
					"  . = multiply v _  ;"
					"  return _          ;"

					, cctmp::binding( "side_dec" , _ptr_side_dec_ )
				);
			else
				return cctmp::source
				(
					"fall_fact_2 x       ;"

					"vars:               ;"
					"  define v          ;"

					"body:               ;"
					"  v = side_dec x    ;" // error: read only.
					"  . = dereference x ;"
					"  . = multiply v _  ;"
					"  return _          ;"

					, cctmp::binding( "side_dec" , _ptr_side_dec_ )
				);
		}

	// v1 (reference):

		struct T_ref_side_dec
		{
			template<typename T>
			constexpr static auto result(T & x)
			{
				auto v = x;

				x = x - 1;

				return v;
			}

		}; constexpr auto _ref_side_dec_ = cctmp::U_store_T<T_ref_side_dec>;

		template<bool punct>
		constexpr auto _chord_fall_fact_2_v1()
		{
			if constexpr (punct)

				return cctmp::source
				(
					"fall_fact_2 x       ;"

					"vars:               ;"
					"  define v          ;"

					"body:               ;"
					"  v = side_dec !x   ;" // works!
					"  . = multiply v x  ;"
					"  return _          ;"

					, cctmp::binding( "side_dec" , _ref_side_dec_ )
				);
			else
				return cctmp::source
				(
					"fall_fact_2 x       ;"

					"vars:               ;"
					"  define v          ;"

					"body:               ;"
					"  v = side_dec x    ;" // error: read only.
					"  . = multiply v x  ;"
					"  return _          ;"

					, cctmp::binding( "side_dec" , _ref_side_dec_ )
				);
		}

/***********************************************************************************************************************/

// void effects:

	// v0:

		constexpr auto _chord_void_effects_v0()
		{
			return cctmp::source
			(
				"f x y               ;"

				"body:               ;"
				"  . = increment y   ;"
				"  void appoint !x _ ;"
				"  return x          ;"
			);
		}

/***********************************************************************************************************************/

// side effects:

	// v0:

		constexpr auto _chord_side_effects_v0()
		{
			return cctmp::source
			(
				"f x y              ;"

				"body:              ;"
				"   . = increment y ;"
				"  !x = appoint _   ;"
				"  return x         ;"
			);
		}

