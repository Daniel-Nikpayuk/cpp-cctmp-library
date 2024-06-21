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

// square:

	// v0:

		constexpr auto _hustle_square_v0()
		{
			return cctmp::source
		        (
				"(define (main n)          "
				"  (define (sq m) (* m m)) "
				"  (sq n)                  "
				")                         "
			);
		}

/***********************************************************************************************************************/

// sum of squares:

	// v0:

		constexpr auto _hustle_sum_of_squares_v0()
		{
			return cctmp::source
		        (
				"(define (main m n)                                "
				"  (define (sq x) (* x x))                         "
				"  (define (sum-of-squares x y) (+ (sq x) (sq y))) "
				"  (sum-of-squares m n)                            "
				")                                                 "
			);
		}

	// v1:

		constexpr auto _hustle_sum_of_squares_v1()
		{
			return cctmp::source
		        (
				"(define (main m n)             "
				"  (define (sum-of-squares x y) "
				"    (define (sq z) (* z z))    "
				"    (+ (sq x) (sq y))          "
				"  )                            "
				"  (sum-of-squares m n)         "
				")                              "
			);
		}

/***********************************************************************************************************************/

// factorial:

	// v0:

		constexpr auto _hustle_factorial_v0()
		{
			return cctmp::source
		        (
				"(type T                         "
				"  (define (factorial n) -> T    "
				"    (if (= n 0)                 "
				"      1:T                       "
				"      (* n (factorial (- n 1))) "
				"    )                           "
				"  )                             "
				")                               "
			);
		}

	// v1:

		constexpr auto _hustle_factorial_v1()
		{
			return cctmp::source
		        (
				"(type T                           "
				"  (define (main n)                "
				"    (define (factorial k) -> T    "
				"      (if (= k 0)                 "
				"        1:T                       "
				"        (* k (factorial (- k 1))) "
				"      )                           "
				"    )                             "
				"    (factorial n)                 "
				"  )                               "
				")                                 "
			);
		}

	// v2:

		constexpr auto _hustle_factorial_v2()
		{
			return cctmp::source
		        (
				"(type T                             "
				"  (define (main n)                  "
				"    (define (factorial k p) -> T    "
				"      (if (= k 0)                   "
				"        p                           "
				"        (factorial (- k 1) (* k p)) "
				"      )                             "
				"    )                               "
				"    (factorial n 1:T)               "
				"  )                                 "
				")                                   "
			);
		}

/***********************************************************************************************************************/

// fibonacci:

	// v0:

		constexpr auto _hustle_fibonacci_v0()
		{
			return cctmp::source
		        (
				"(type T                               "
				"  (define (fib n) -> T                "
				"    (if (< n 2)                       "
				"      1:T                             "
				"      (+ (fib (- n 1)) (fib (- n 2))) "
				"    )                                 "
				"  )                                   "
				")                                     "
			);
		}

/***********************************************************************************************************************/

// square root:

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

				, cctmp::binding( "tolerance" , 0.0001 )
			);
		}

	// v1:

		constexpr auto _hustle_square_root_v1()
		{
			return cctmp::source
		        (
				"(type T                                                                       "
				"  (define (sqrt x)                                                            "
				"    (define (square y) (* y y))                                               "
				"    (define (abs y) (if (< y zero) (- y) y))                                  "
				"    (define (good-enough? guess y) (< (abs (- (square guess) y)) tolerance))  "
				"    (define (average y z) (/ (+ y z) two))                                    "
				"    (define (improve guess y) (average guess (/ y guess)))                    "

				"    (define (sqrt-iter guess y) -> T                                          "
				"      (if (good-enough? guess y) guess (sqrt-iter (improve guess y) y))       "
				"    )                                                                         "

				"    (sqrt-iter one x)                                                         "
				"  )                                                                           "
				")                                                                             "

				, cctmp::binding( "tolerance" , 0.0001 )
			);
		}

