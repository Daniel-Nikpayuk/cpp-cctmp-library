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

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// prerequisites:

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

		const bool operator == (const complex_number & c) const
		{
			return (x == c.x && y == c.y);
		}

		const bool operator != (const complex_number & c) const
		{
			return (x != c.x || y != c.y);
		}

		const complex_number operator + (const complex_number & c) const
		{
			return complex_number(x + c.x, y + c.y);
		}

		const complex_number operator * (const complex_number & c) const
		{
			auto x0 = x * c.x;
			auto x1 = y * c.y;

			auto y0 = x * c.y;
			auto y1 = y * c.x;

			return complex_number(x0 - x1, y0 + y1);
		}
	};

/***********************************************************************************************************************/

	constexpr auto make_complex(const float x, const float y) { return complex_number(x, y); }
	constexpr auto _make_complex_ = _wrap_<make_complex>;

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
// lookup assignment      :
// copy/paste assignment  :
// variable assignment    :

// operator lookup        :
// operand lookup         :

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

	template<typename T>
	constexpr auto square_v0(T v)
		{ return generic_assembly_apply<_square_v0, T>(v); }

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

	template<typename T>
	constexpr auto sum_of_squares_v0(T x, T y)
		{ return generic_assembly_apply<_sum_of_squares_v0, T>(x, y); }

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
			"y = one                ;"
			". = multiply x x x x x ;"
			". = add _ y            ;"
			"return _               ;"
		);
	}

	template<typename T>
	constexpr auto x_to5_plus1_v0(T x)
	{
		constexpr auto l0 = default_constant_lookup;

		return generic_assembly_apply<_x_to5_plus1_v0, T, l0>(x, T(0));
	}

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
			"  x = y            ;"
			"  return x         ;"
		);
	}

	template<typename T1, typename T2>
	constexpr auto reassign_v0(T1 x, T2 y)
		{ return generic_assembly_apply<_reassign_v0, T2>(x, y); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// semidynamic typing:

/***********************************************************************************************************************/

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
			"  c = five                 ;"
			"  return c                 ;"
		);
	}

	constexpr auto semidynamic_typing_v0(const complex_number & c, int n)
	{
		constexpr auto c1 = complex_number(1, 0);
		constexpr auto l0 = default_constant_lookup;

		return generic_assembly_apply<_semidynamic_typing_v0, int, l0>(c, c1, n);
	}

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

	template<typename T>
	constexpr auto factorial_v0(T v)
	{
		constexpr auto l0 = default_constant_lookup;

		return generic_assembly_apply<_factorial_v0, T, l0>(v);
	}

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

	template<typename T>
	constexpr auto factorial_v1(T v)
		{ return generic_assembly_apply<_factorial_v1, T>(v, T(1)); }

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

	template<typename T>
	constexpr auto factorial_v2(T v)
		{ return generic_assembly_apply<_factorial_v2, T>(T(1), v); }

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

	template<typename T>
	constexpr auto factorial_v3(T v)
		{ return generic_assembly_apply<_factorial_v3, T>(T(1), v); }

/***********************************************************************************************************************/

// version 4:

	constexpr auto _factorial_v4()
	{
		return source
		(
			"factorial n      ;"

			"body:            ;"
			"p = one          ;"
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

	template<typename T>
	constexpr auto factorial_v4(T v)
	{
		constexpr auto l0 = default_constant_lookup;

		return generic_assembly_apply<_factorial_v4, T, l0>(v);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fibonacci:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _fibonacci_v0()
	{
		return source
		(
			"fibonacci n n1 n2           ;"

			"body:                       ;"
			"test equal n zero           ;"
			"branch done                 ;"
			"test equal n one            ;"
			"branch done                 ;"
			"n1 = decrement n            ;"
			"n2 = decrement n1           ;"
			"n1 = fibonacci n1 zero zero ;"
			"n2 = fibonacci n2 zero zero ;"
			".  = add n1 n2              ;"
			"return _                    ;"

			"done:                       ;"
			"return one                  ;"
		);
	}

	template<typename T>
	constexpr auto fibonacci_v0(T v)
	{
		constexpr auto l0 = default_constant_lookup;

		return generic_assembly_apply<_fibonacci_v0, T, l0>(v, T(0), T(0));
	}

/***********************************************************************************************************************/

// version 1:

	constexpr auto _fibonacci_v1()
	{
		return source
		(
			"fibonacci n       ;"

			"body:             ;"
			"test equal n zero ;"
			"branch done       ;"
			"test equal n one  ;"
			"branch done       ;"
			"n1 = decrement n  ;"
			"n2 = decrement n1 ;"
			"n1 = fibonacci n1 ;"
			"n2 = fibonacci n2 ;"
			".  = add n1 n2    ;"
			"return _          ;"

			"done:             ;"
			"return one        ;"
		);
	}

	template<typename T>
	constexpr auto fibonacci_v1(T v)
	{
		constexpr auto l0 = default_constant_lookup;

		return generic_assembly_apply<_fibonacci_v1, T, l0>(v);
	}

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
			"  !x = assign _    ;"
			"  return x         ;"
		);
	}

	template<typename T>
	constexpr auto side_effects_v0(T x)
		{ return generic_assembly_apply<_side_effects_v0, T>(x, 2); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// falling factorial (exponent 2):

/***********************************************************************************************************************/

// frame:

	template<auto side_dec>
	constexpr auto fall_fact_2_frame()
	{
		return cctmp::table
		(
		 	cctmp::U_char,

			cctmp::binding( "side_dec" , side_dec )
		);
	};

/***********************************************************************************************************************/

// version 0:

	struct T_ptr_side_dec
	{
		template<typename T>
		constexpr static auto result(T x)
		{
			auto y = *x;

			*x = *x - 1;

			return y;
		}

	}; constexpr auto _ptr_side_dec_ = U_store_T<T_ptr_side_dec>;

	constexpr auto fall_fact_2_ptr_lookup = cctmp::make_frame<fall_fact_2_frame<_ptr_side_dec_>>;

	template<bool punct>
	constexpr auto _fall_fact_2_ptr_v0()
	{
		if constexpr (punct)

			return source
			(
				"fall_fact_2 x       ;"

				"body:               ;"
				"  v = side_dec !x   ;" // works!
				"  . = dereference x ;"
				"  . = multiply v _  ;"
				"  return _          ;"
			);
		else
			return source
			(
				"fall_fact_2 x       ;"

				"body:               ;"
				"  v = side_dec x    ;" // error: read only.
				"  . = dereference x ;"
				"  . = multiply v _  ;"
				"  return _          ;"
			);
	}

	template<bool punct, typename T>
	constexpr auto fall_fact_2_ptr_v0(T x)
	{
		constexpr auto src = _fall_fact_2_ptr_v0<punct>;
		constexpr auto l0  = fall_fact_2_ptr_lookup;

		return generic_assembly_apply<src, T, l0>(&x);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

