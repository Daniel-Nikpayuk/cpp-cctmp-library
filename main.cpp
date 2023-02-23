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

#include<cstdio>

/***********************************************************************************************************************/

#include"define_macros.hpp"

#include"00_cctmp_grammar.hpp"
#include"01_cctmp_argument.hpp"
#include"02_cctmp_parameter.hpp"
#include"03_cctmp_praxis.hpp"
#include"04_cctmp_interpreter.hpp"
#include"05_cctmp_machine.hpp"
#include"06_cctmp_lexer.hpp"
#include"07_cctmp_parser.hpp"
#include"08_cctmp_assembler.hpp"
#include"09_cctmp_optimizer.hpp"
#include"10_cctmp_metapiler.hpp"

//#include"testing/metapiler_printer.hpp"

#include"undef_macros.hpp"

/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (generic) square:

/***********************************************************************************************************************/

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

	void print_complex(const complex_number & c) { printf("(%f, %f)\n", c.x, c.y); }

/***********************************************************************************************************************/

	constexpr auto square_source()
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
	constexpr auto square(T v)
	{
		using T_square = T_generic_assembly_metapiler<square_source>;

		return T_square::template result<T>(v);
	}

/***********************************************************************************************************************/

	constexpr auto sum_of_squares_source()
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
	constexpr auto sum_of_squares(T x, T y)
	{
		using T_sum_of_squares = T_generic_assembly_metapiler<sum_of_squares_source>;

		return T_sum_of_squares::template result<T>(x, y);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// factorial:

/***********************************************************************************************************************/

	constexpr auto factorial_source()
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
	constexpr auto factorial(T v)
	{
		using T_factorial = T_generic_assembly_metapiler<factorial_source>;

		return T_factorial::template result<T>(v, T(1));
	}

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		print_complex(square(complex_number(1, 2))); // prints: (-3.000000, 4.000000)
		print_complex(sum_of_squares(complex_number(1, 2), complex_number(0, 1))); // prints: (-4.000000, 4.000000)
		printf("%d\n", sum_of_squares(3, 4)); // prints: 25

		static_assert(factorial(5) == 120);

		return 0;
	}

