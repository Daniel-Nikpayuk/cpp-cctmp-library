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

		complex_number() : x{}, y{} { }
		complex_number(const float _x, const float _y) : x{_x}, y{_y} { }

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

// print:

	void print_complex(const complex_number & c) { printf("(%f, %f)\n", c.x, c.y); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic assembly:

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
		{ return generic_assembly_apply<_x_to5_plus1_v0, T>(x, T(0)); }

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
		{ return generic_assembly_apply<_factorial_v0, T>(v); }

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
		{ return generic_assembly_apply<_fibonacci_v0, T>(v, T(0), T(0)); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

