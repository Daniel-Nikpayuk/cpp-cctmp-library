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

/*
	constexpr auto _hustle_test_func()
	{
		return source
	        (
			"(define (main a n)             "
			"  (define (range k)            "
			"    (if (= k n) nil            "
			"      (cons k (range (+ k 1))) " // cannot be resolved at metacompile time.
			"    )                          " // a, n, k are referenced as args in the verse.
			"  )                            "
			"  (tuple (range a))            " // return: tuple{a, a+1, a+2, a+3, ..., a+(n-1)}
			")                              "
		);					  // accumulating a temporary constexpr controller
	}						  // is problematic because the calling contexts
*/
							  // are temporary as well, and so the actual
							  // content gets lost unless you return actual
							  // values, but that's problematic because
							  // of C++17's restrictions on NTTPs.
							  // actual C++ data structures might
							  // be the only way.

							  // then again:
							  // (cons a (cons (+ a 1) (cons (+ (+ a 1) 1) ...)))
							  // this would be a list of valid expressions.

/***********************************************************************************************************************/

	// data structure internal representation is as follows:

		// To represent a pair, the first element is the location in the variadic pack.
		// the second element is the adjacent location in the variadic pack.
		// the second element, when referring to another pair holds a "pointer" (T_pack<index>)
		// to the next pair.

		// when you cons, you check if the second arg is a pair. If so, add the pointer.

	constexpr auto _hustle_test_func()
	{
		return source
	        (
			"(define (main m n)               "
			"  (define (range k l)            "
			"    (if (= m k) l                " 
			"      (range (- k 1) (cons k l)) "
			"    )                            "
			"  )                              "
			"  (list-to-tuple (range n nil))  "
			")                                "
		);
	}

/***********************************************************************************************************************/

	constexpr auto _Nil_ = U_store_T<void>;

	struct T_cons
	{
		template<typename T0, typename T1>
		constexpr static auto result(T0 v0, T1 v1) { return pair<T0, T1>{v0, v1}; }

	}; constexpr auto _Cons_ = U_store_T<T_cons>;

	struct T_car
	{
		template<typename P>
		constexpr static auto result(P p) { return p.v0; }

	}; constexpr auto _Car_ = U_store_T<T_car>;

	constexpr auto _hustle_test_func()
	{
		return source
	        (
			"(define (main n)     "
			"  (Car (Cons n Nil)) "
			")                    "

			, binding( "Nil"  , _Nil_  )
			, binding( "Cons" , _Cons_ )
			, binding( "Car"  , _Car_  )
		);
	}

/***********************************************************************************************************************/

	//	return source // direct style:		// continuation passing style:
	//	(
	//		"(define (main n)         "		"(define (main& n k)          "
	//		"  ((if (= n 0) + *) 2 3) "		"  (=& n 0 (lambda (b)        "
	//		")                        "		"    (if& b +& *& (lambda (f) "
	//	);                                 		"      (f 2 3 k))))))         "

			// works:

			//	"(define (main n)              "
			//	"  (define x (if (= n 0) 2 3)) "
			//	"  x                           "
			//	")                             "

			// doesn't yet work:

			//	"(define (main n)              "
			//	"  (define x (if (= n 0) + *)) "
			//	"  (x 2 3)                     "
			//	")                             "

			//	"(define (main n)              "
			//	"  (define x 2)                "
			//	"  (define y n)                "
			//	"  x                           "
			//	")                             "

/***********************************************************************************************************************/

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
	constexpr auto sqrt(T x) { return sqrt_iter<T>(x, 1.0); }

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

/***********************************************************************************************************************/

// atomic (7, 8?):

	// literal (boolean):

		// line   5 - AN::id         AT::id          0   0   0   0   0   1
		// line   6 - AN::type       AT::boolean     0   0   0   0   0   1
		// line   7 - AN::literal    AT::first       1   0   0   0   0   1
		// line   8 - AN::halt       AT::first       0   0   0   0   0   1

	// literal (character):

		// line   5 - AN::id         AT::id          0   0   0   0   0   1
		// line   6 - AN::type       AT::character   0   0   0   0   0   1
		// line   7 - AN::literal    AT::first      99   0   0   0   0   1
		// line   8 - AN::halt       AT::first       0   0   0   0   0   1

	// literal (n number):

		// line   5 - AN::id         AT::id          0   0   0   0   0   1
		// line   6 - AN::type       AT::n_number    0   0   0   0   0   1
		// line   7 - AN::literal    AT::first       5   0   0   0   0   1
		// line   8 - AN::halt       AT::first       0   0   0   0   0   1

	// literal (r number):

		// line   5 - AN::id         AT::id          0   0   0   0   0   1
		// line   6 - AN::type       AT::r_number    0   0   0   0   0   1
		// line   7 - AN::floating   AT::first       5   0  10   0   0   1
		// line   8 - AN::halt       AT::first       0   0   0   0   0   1

	// literal (t number):

		// line   5 - AN::id         AT::id          0   0   0   0   0   1
		// line   6 - AN::type       AT::push        0   0   0   0   0   1
		// line   7 - AN::literal    AT::first       5   0   0   0   0   1
		// line   8 - AN::halt       AT::first       0   0   0   0   0   1

	// variable (universe):

		// line   7 - AN::id         AT::id          0   0   0   0   0   1
		// line   8 - AN::arg        AT::select      1   0   0   0   0   1
		// line   9 - AN::arg        AT::drop        0   0   0   0   0   1
		// line  10 - AN::halt       AT::first       0   0   0   0   0   1

	// variable (import):

		// line   7 - AN::id         AT::id          0   0   0   0   0   1
		// line   8 - AN::lookup     AT::first       0   0   0   0   0   1
		// line   9 - AN::halt       AT::first       0   0   0   0   0   1

	// assign ?

// compound:

	// replace ?

	// pair:

	// type:

	// apply:

	// bind:

	// if then else:

	// define:

	// define type:

/***********************************************************************************************************************/

