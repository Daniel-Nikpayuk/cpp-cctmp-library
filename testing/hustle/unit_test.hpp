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

// unit test:

#include"contr/square_v0.hpp"
#include"contr/sum_of_squares_v0.hpp"
#include"contr/sum_of_squares_v1.hpp"
#include"contr/factorial_v0.hpp"
#include"contr/factorial_v1.hpp"
#include"contr/factorial_v2.hpp"
#include"contr/fibonacci_v0.hpp"
#include"contr/square_root_v0.hpp"
#include"contr/square_root_v1.hpp"

#include"inventory.hpp"

/***********************************************************************************************************************/

// square:

	// v0:

		template<typename SizeType, typename T>
		constexpr void unit_test_hustle_square_v0(T v)
		{
			using T_hustle_fast_apply = hustle::T_fast_apply
			<
				contr_object_hustle_square_v0<SizeType>,
				_hustle_square_v0, cctmp::null_env, T
			>;

			auto val = T_hustle_fast_apply::result(v);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// sum of squares:

	// v0:

		template<typename SizeType, typename T>
		constexpr void unit_test_hustle_sum_of_squares_v0(T v0, T v1)
		{
			using T_hustle_fast_apply = hustle::T_fast_apply
			<
				contr_object_hustle_sum_of_squares_v0<SizeType>,
				_hustle_sum_of_squares_v0, cctmp::null_env, T
			>;

			auto val = T_hustle_fast_apply::result(v0, v1);
			printf("%d\n", val);
		}

	// v1:

		template<typename SizeType, typename T>
		constexpr void unit_test_hustle_sum_of_squares_v1(T v0, T v1)
		{
			using T_hustle_fast_apply = hustle::T_fast_apply
			<
				contr_object_hustle_sum_of_squares_v1<SizeType>,
				_hustle_sum_of_squares_v1, cctmp::null_env, T
			>;

			auto val = T_hustle_fast_apply::result(v0, v1);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// factorial:

	// v0:

		template<typename SizeType, typename T>
		constexpr void unit_test_hustle_factorial_v0(T v)
		{
			using T_hustle_fast_apply = hustle::T_fast_apply
			<
				contr_object_hustle_factorial_v0<SizeType>,
				_hustle_factorial_v0, cctmp::null_env, T
			>;

			auto val = T_hustle_fast_apply::result(v);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// factorial:

	// v1:

		template<typename SizeType, typename T>
		constexpr void unit_test_hustle_factorial_v1(T v)
		{
			using T_hustle_fast_apply = hustle::T_fast_apply
			<
				contr_object_hustle_factorial_v1<SizeType>,
				_hustle_factorial_v1, cctmp::null_env, T
			>;

			auto val = T_hustle_fast_apply::result(v);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// factorial:

	// v2:

		template<typename SizeType, typename T>
		constexpr void unit_test_hustle_factorial_v2(T v)
		{
			using T_hustle_fast_apply = hustle::T_fast_apply
			<
				contr_object_hustle_factorial_v2<SizeType>,
				_hustle_factorial_v2, cctmp::null_env, T
			>;

			auto val = T_hustle_fast_apply::result(v);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// fibonacci:

	// v0:

		template<typename SizeType, typename T>
		constexpr void unit_test_hustle_fibonacci_v0(T v)
		{
			using T_hustle_fast_apply = hustle::T_fast_apply
			<
				contr_object_hustle_fibonacci_v0<SizeType>,
				_hustle_fibonacci_v0, cctmp::null_env, T
			>;

			auto val = T_hustle_fast_apply::result(v);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// square root:

	// v0:

		template<typename SizeType, typename T>
		constexpr void unit_test_hustle_square_root_v0(T v)
		{
			using T_hustle_fast_apply = hustle::T_fast_apply
			<
				contr_object_hustle_square_root_v0<SizeType>,
				_hustle_square_root_v0, cctmp::null_env, T
			>;

			auto val = T_hustle_fast_apply::result(v);
			printf("%1.11f\n", val);
		}

	// v1:

		template<typename SizeType, typename T>
		constexpr void unit_test_hustle_square_root_v1(T v)
		{
			using T_hustle_fast_apply = hustle::T_fast_apply
			<
				contr_object_hustle_square_root_v1<SizeType>,
				_hustle_square_root_v1, cctmp::null_env, T
			>;

			auto val = T_hustle_fast_apply::result(v);
			printf("%1.11f\n", val);
		}

