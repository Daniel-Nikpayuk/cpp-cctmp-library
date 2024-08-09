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

// different:

	// v0:

		constexpr auto _chord_different_v0()
		{
			return cctmp::source
			(
				"main out in end in1                              ;"

				"vars:                                            ;"
				"  declare diff                                   ;"

				"defs:                                            ;"
				"  diff # find[2]{not_equal|first @ @|} [> [,) [) ;"

				"body:                                            ;"
				"  . = diff !out in end in1                       ;"
				"  return _                                       ;"

				, cctmp::binding( "not_equal" , cctmp::_not_equal_   )
				, cctmp::binding( "*"         , cctmp::_dereference_ )
				, cctmp::binding( "first"     , cctmp::_first_       )
				, cctmp::binding( "@"         , cctmp::_id_          )
			);
		}

/***********************************************************************************************************************/

// square root:

	// subtract:

		struct T_hustle_subtract
		{
			using F = cctmp::T_store_U<cctmp::_subtract_>;

			template<typename T>
			constexpr static auto result(T v) { return -v; }

			template<typename... Ts>
			constexpr static auto result(Ts... vs) { return F::template result<Ts...>(vs...); }

		}; constexpr auto _hustle_subtract_ = cctmp::U_store_T<T_hustle_subtract>;

	// v0:

		constexpr auto _hustle_square_root_v0()
		{
			return cctmp::source
		        (
				"(type T                                                                    "
				"  (define (sqrt x)                                                         "

				"    (define (square y) (* y y))                                            "
				"    (define (abs y) (if (< y 0) (- y) y))                                  "
				"    (define (good-enough? guess) (< (abs (- (square guess) x)) tolerance)) "

				"    (define (average y z) (/ (+ y z) 2))                                   "
				"    (define (improve guess) (average guess (/ x guess)) )                  "

				"    (define (sqrt-iter guess) -> T                                         "
				"      (if (good-enough? guess) guess (sqrt-iter (improve guess)))          "
				"    )                                                                      "

				"    (sqrt-iter 1:T)                                                        "
				"  )                                                                        "
				")                                                                          "

				, cctmp::binding( "<"         , cctmp::_less_than_       )

				, cctmp::binding( "+"         , cctmp::_add_             )
				, cctmp::binding( "-"         ,        _hustle_subtract_ )
				, cctmp::binding( "*"         , cctmp::_multiply_        )
				, cctmp::binding( "/"         , cctmp::_divide_          )

				, cctmp::binding( "tolerance" , 0.0001                   )
			);
		}

