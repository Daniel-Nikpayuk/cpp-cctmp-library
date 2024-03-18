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

// meta assembly:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// names:		// notes:

	//	id        00	//	id       00
	//	halt      01	//	first    01
	//	boolean   02	//	first_rw 02
	//	n_number  03	//	port     03
	//	r_number  04	//	select   04
	//	character 05	//	read     05
	//	string    06	//	front    06
	//	literal   07	//	back     07
	//	list      08	//	back_ro  08
	//	lookup    09	//	back_rw  09
	//	arg       10	//	ante     10
	//	pad       11	//	conse    11
	//	pound     12	//	push     12
	//	apply     13	//	pull     13
	//	bind      14	//	drop     14
	//	eval      15	//	verse    15
	//	goto      16	//	side     16
	//	branch    17	//	replace  17
	//	invert    18

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	template<auto static_contr>
	void print_controller(int b = 0, int e = member_value_U<static_contr>.size())
	{
		constexpr auto & contr = member_value_U<static_contr>;

		for (auto k = b; k != e; ++k)
		{
			auto s = (k < 10) ? "  " : (k < 100) ? " " : "";
			printf("line %s%d -", s, k);

			for (auto j = 0; j != Instr::dimension; ++j)
			{
				auto v = contr[k][j];
				auto t = (v < 10) ? "  " : (v < 100) ? " " : "";

				printf(" %s%d", t, v);
			}

			printf("\n");
		}
	}

/***********************************************************************************************************************/

	// "(define (factorial n)         "
	// "  (if (= n 0)                 "
	// "    1                         "
	// "    (* n (factorial (- n 1))) "
	// "  )                           "
	// ")                             "

	// line   0 -   0   0   0   0   1
	// line   1 -   2   2   1   0   1 // pad , select
	// line   2 -   2   3   0   0   1 // pad , front
	// line   3 -   7   4   4   0   5 // (= n 0) -> =
	// line   4 -   0   0   0   0   1
	// line   5 -   3  10   2   0   1
	// line   6 -   4   1   1   5   1
	// line   7 -   1   1   0   0   1
	// line   8 -   7   4   9   0   5 // (= n 0) -> n
	// line   9 -   0   0   0   0   1
	// line  10 -   2   6   1   0   1
	// line  11 -   2   3   0   0   1
	// line  12 -   1   1   0   0   1
	// line  13 -   7   4  14   0   7 // (= n 0) -> 0
	// line  14 -   0   0   0   0   1
	// line  15 -   5   1  16   0   4
	// line  16 -   0   0   0   0   1
	// line  17 -   2   3  41  42   1
	// line  18 -   1   1   0   0   1
	// line  19 -   1   1   0   0   1
	// line  20 -   3   2   2   0   1 // arg   , select 2
	// line  21 -   9   1   0   0   1 // apply , first
	// line  22 -   6  11  30   0   1 // jump  , invert (if true continue (goto 30))
	// line  23 -   7   1  24   0   7 // 1 -> 1
	// line  24 -   0   0   0   0   1
	// line  25 -   5   1  26   0   4
	// line  26 -   0   0   0   0   1
	// line  27 -   2   3  64  65   1
	// line  28 -   1   1   0   0   1
	// line  29 -   1   1   0   0   1
	// line  30 -   6   9  64   0   1 // goto 64
	// line  31 -   7   4  32   0   5 // (* n (factorial (- n 1))) -> *
	// line  32 -   0   0   0   0   1
	// line  33 -   3  10   2   0   1
	// line  34 -   4   1   1  12   1
	// line  35 -   1   1   0   0   1
	// line  36 -   7   4  37   0   5 // (* n (factorial (- n 1))) -> n
	// line  37 -   0   0   0   0   1
	// line  38 -   2   6   1   0   1
	// line  39 -   2   3   0   0   1
	// line  40 -   1   1   0   0   1
	// line  41 -   5   4   0   0   1 // pound , back (factorial)
	// line  42 -   7   4  43   0   5 // (* n (factorial (- n 1))) -> -
	// line  43 -   0   0   0   0   1
	// line  44 -   3  10   2   0   1
	// line  45 -   4   1   1  11   1
	// line  46 -   1   1   0   0   1
	// line  47 -   7   4  48   0   5 // (* n (factorial (- n 1))) -> n
	// line  48 -   0   0   0   0   1
	// line  49 -   2   6   1   0   1
	// line  50 -   2   3   0   0   1
	// line  51 -   1   1   0   0   1
	// line  52 -   7   4  53   0   7 // (* n (factorial (- n 1))) -> 1
	// line  53 -   0   0   0   0   1
	// line  54 -   5   1  55   0   4
	// line  55 -   0   0   0   0   1
	// line  56 -   2   3 115 116   1
	// line  57 -   1   1   0   0   1
	// line  58 -   1   1   0   0   1
	// line  59 -   3   2   5   0   1 // arg   , select 5
	// line  60 -   9   4   0   0   1 // apply , back
	// line  61 -   3   2   4   0   1 // arg   , select 4
	// line  62 -  10   4   0   0   1 // bind  , back
	// line  63 -   3   2   2   0   1 // arg   , select 2
	// line  64 -   9   1   0   0   1 // apply , first
	// line  65 -   1   1   0   0   1 // halt  , first

/***********************************************************************************************************************/

		//	"(define (main n)          "
		//	"  (define (sq m) (* m m)) "
		//	"  (sq n)                  "
		//	")                         "

		//	"(define (main m n)                                "
		//	"  (define (sq x) (* x x))                         "
		//	"  (define (sum-of-squares x y) (+ (sq x) (sq y))) "
		//	"  (sum-of-squares m n)                            "
		//	")                                                 "

		//	"(define (main m n)             "
		//	"  (define (sum-of-squares x y) "
		//	"    (define (sq z) (* z z))    "
		//	"    (+ (sq x) (sq y))          "
		//	"  )                            "
		//	"  (sum-of-squares m n)         "
		//	")                              "

		//	"(type T                         "
		//	"  (define (factorial n) -> T    "
		//	"    (if (= n 0)                 "
		//	"      1:T                       "
		//	"      (* n (factorial (- n 1))) "
		//	"    )                           "
		//	"  )                             "
		//	")                               "

		//	"(type T                               "
		//	"  (define (fib n) -> T                "
		//	"    (if (< n 2)                       "
		//	"      1:T                             "
		//	"      (+ (fib (- n 1)) (fib (- n 2))) "
		//	"    )                                 "
		//	"  )                                   "
		//	")                                     "

		//	"(type T                           "
		//	"  (define (main n)                "
		//	"    (define (factorial k) -> T    "
		//	"      (if (= k 0)                 "
		//	"        1:T                       "
		//	"        (* k (factorial (- k 1))) "
		//	"      )                           "
		//	"    )                             "
		//	"    (factorial n)                 "
		//	"  )                               "
		//	")                                 "

		//	"(type T                             "
		//	"  (define (main n)                  "
		//	"    (define (factorial k p) -> T    "
		//	"      (if (= k 0)                   "
		//	"        p                           "
		//	"        (factorial (- k 1) (* k p)) "
		//	"      )                             "
		//	"    )                               "
		//	"    (factorial n 1:T)               "
		//	"  )                                 "
		//	")                                   "

		//	"(type T                                        "
		//	"  (define (sqrt x)                             "
		//	"    (define (square y) (* y y))                "
		//	"    (define (abs y) (if (< y zero) (- y) y))   "
		//	"    (define (good-enough? guess y)             "
		//	"      (< (abs (- (square guess) y)) tolerance) "
		//	"    )                                          "
		//	"    (define (average y z) (/ (+ y z) two))     "
		//	"    (define (improve guess y)                  "
		//	"      (average guess (/ y guess))              "
		//	"    )                                          "
		//	"    (define (sqrt-iter guess y) -> T           "
		//	"      (if (good-enough? guess y)               "
		//	"        guess                                  "
		//	"        (sqrt-iter (improve guess y) y)        "
		//	"      )                                        "
		//	"    )                                          "
		//	"    (sqrt-iter one x)                          "
		//	"  )                                            "
		//	")                                              "

		//	"(type T                                                                    "
		//	"  (define (sqrt x)                                                         "

		//	"    (define (square y) (* y y))                                            "
		//	"    (define (abs y) (if (< y 0) (- y) y))                                  "
		//	"    (define (good-enough? guess) (< (abs (- (square guess) x)) tolerance)) "

		//	"    (define (average y z) (/ (+ y z) 2))                                   "
		//	"    (define (improve guess) (average guess (/ x guess)) )                  "

		//	"    (define (sqrt-iter guess) -> T                                         "
		//	"      (if (good-enough? guess) guess (sqrt-iter (improve guess)))          "
		//	"    )                                                                      "

		//	"    (sqrt-iter 1:T)                                                        "
		//	"  )                                                                        "
		//	")                                                                          "

	template<typename T>
	constexpr auto sqrt_iter(T x, T guess) -> T
	{
		auto tolerance		= 0.0001;
		auto square		= [](T y){ return y * y; };
		auto abs		= [](T y){ return (y < 0) ? -y : y; };
		auto good_enough	= [&](T g) { return (abs(square(g) - x) < tolerance); };

		auto average		= [](T y, T z){ return (y + z) / 2; };
		auto improve		= [&](T g){ return average(g, x/g); };

		if (good_enough(guess)) return guess;
		else return sqrt_iter(x, improve(guess));
	}

	template<typename T>
	constexpr auto sqrt(T x) { return sqrt_iter(x, 1.0); }

/***********************************************************************************************************************/

// hustle:

	constexpr auto _hustle_test_func()
	{
		return source
	        (

			, binding("T", 0)
		);
	}

	template<typename... OutTs>
	struct hustle_test_op
	{
		constexpr static auto OutUs = U_pack_Ts<OutTs...>;

		template<typename... Ts>
		constexpr static auto result(Ts... vs)
			{ return hustle::hustle_apply<_hustle_test_func, null_env, OutUs>(vs...); }

	}; template<typename... OutTs>
		constexpr auto _hustle_test_op_ = U_store_T<hustle_test_op<OutTs...>>;

/***********************************************************************************************************************/

	struct T_arg
	{
		using CN		= machine::CN;
		using CT		= machine::CT;
		using ninstr_type	= gindex_type[5];

		constexpr static ninstr_type value[] =
		{
			{ CN::id   , CT::id     , 0 , 0 , 1 },
			{ CN::arg  , CT::select , 1 , 0 , 1 },
			{ CN::arg  , CT::drop   , 0 , 0 , 1 },
			{ CN::halt , CT::first  , 0 , 0 , 1 }
		};

	}; constexpr auto U_arg = U_store_T<T_arg>;

/***********************************************************************************************************************/

	struct T_val
	{
		using CN		= machine::CN;
		using CT		= machine::CT;
		using ninstr_type	= gindex_type[5];

		constexpr static ninstr_type value[] =
		{
			{ CN::id   , CT::id     , 0 , 0 , 1 },
			{ CN::list , CT::push   , 9 , 0 , 1 },
			{ CN::list , CT::select , 0 , 0 , 1 },
			{ CN::halt , CT::first  , 0 , 0 , 1 }
		};

	}; constexpr auto U_val = U_store_T<T_val>;

