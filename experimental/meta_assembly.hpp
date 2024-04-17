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

