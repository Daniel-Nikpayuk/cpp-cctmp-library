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
#include"contr/square_v1.hpp"
#include"contr/sum_of_squares_v0.hpp"
#include"contr/sum_of_squares_v1.hpp"
#include"contr/twice_v0.hpp"
#include"contr/plus_n_v0.hpp"
#include"contr/two_x_sqd_v0.hpp"
#include"contr/x_sqd_plus_y4_v0.hpp"
#include"contr/x_to5_plus1_v0.hpp"
#include"contr/reassign_v0.hpp"
#include"contr/if_then_else_v0.hpp"
#include"contr/semidynamic_typing_v0.hpp"
#include"contr/semidynamic_typing_v1.hpp"
#include"contr/binary_dispatch_v0.hpp"
#include"contr/binary_dispatch_v1.hpp"
#include"contr/factorial_v0.hpp"
#include"contr/factorial_v1.hpp"
#include"contr/factorial_v2.hpp"
#include"contr/factorial_v3.hpp"
#include"contr/factorial_v4.hpp"
#include"contr/factorial_v5.hpp"
#include"contr/fibonacci_v0.hpp"
#include"contr/fibonacci_v1.hpp"
#include"contr/fall_fact_2_v0.hpp"
#include"contr/fall_fact_2_v1.hpp"
//#include"contr/void_effects_v0.hpp"
//#include"contr/side_effects_v0.hpp"

#include"inventory.hpp"

/***********************************************************************************************************************/

// square:

	// v0:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_square_v0(T v)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_square_v0<SizeType>,
				_chord_square_v0, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(v);
			printf("%d\n", val);
		}

	// v1:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_square_v1(T v)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_square_v1<SizeType>,
				_chord_square_v1, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(v);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// sum of squares:

	// v0:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_sum_of_squares_v0(T v0, T v1)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_sum_of_squares_v0<SizeType>,
				_chord_sum_of_squares_v0, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(v0, v1);
			printf("%d\n", val);
		}

	// v1:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_sum_of_squares_v1(T v0, T v1)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_sum_of_squares_v1<SizeType>,
				_chord_sum_of_squares_v1, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(v0, v1);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// twice:

	// v0:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_twice_v0(T v)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_twice_v0<SizeType>,
				_chord_twice_v0, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(v);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// plus n:

	// v0:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_plus_n_v0(T v0, T v1)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_plus_n_v0<SizeType>,
				_chord_plus_n_v0, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(v0, v1);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// two_x_sqd:

	// v0:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_two_x_sqd_v0(T v)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_two_x_sqd_v0<SizeType>,
				_chord_two_x_sqd_v0, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(v);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// x_sqd_plus_y4:

	// v0:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_x_sqd_plus_y4_v0(T v0, T v1)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_x_sqd_plus_y4_v0<SizeType>,
				_chord_x_sqd_plus_y4_v0, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(v0, v1);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// x^5 + 1:

	// v0:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_x_to5_plus1_v0(T v0, T v1)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_x_to5_plus1_v0<SizeType>,
				_chord_x_to5_plus1_v0, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(v0, v1);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// reassign:

	// v0:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_reassign_v0(T v0, T v1)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_reassign_v0<SizeType>,
				_chord_reassign_v0, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(v0, v1);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// if then else:

	// v0:

		template<typename SizeType, typename T0, typename T>
		constexpr void unit_test_chord_if_then_else_v0(T0 v0, T v1, T v2)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_if_then_else_v0<SizeType>,
				_chord_if_then_else_v0, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(v0, v1, v2);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// semidynamic typing:

	// v0:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_semidynamic_typing_v0(complex_number c, T n)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_semidynamic_typing_v0<SizeType>,
				_chord_semidynamic_typing_v0, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(c, complex_number{1, 0}, n);
			printf("%d\n", val);
		}

	// v1:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_semidynamic_typing_v1(complex_number c, T n)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_semidynamic_typing_v1<SizeType>,
				_chord_semidynamic_typing_v1, cctmp::env<complex_constant_frame>, T
			>;

			auto val = T_chord_fast_apply::result(c, n);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// binary dispatch:

	// v0:

		template<typename SizeType, typename T0, typename T>
		constexpr void unit_test_chord_binary_dispatch_v0(T0 n, T x, T y)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_binary_dispatch_v0<SizeType>,
				_chord_binary_dispatch_v0, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(n, cctmp::_add_, cctmp::_multiply_, x, y);
			printf("%d\n", val);
		}

	// v1:

		template<typename SizeType, typename T0, typename T>
		constexpr void unit_test_chord_binary_dispatch_v1(T0 n, T x, T y)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_binary_dispatch_v1<SizeType>,
				_chord_binary_dispatch_v1, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(n, cctmp::_add_, cctmp::_multiply_, x, y);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// factorial:

	// v0:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_factorial_v0(T v)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_factorial_v0<SizeType>,
				_chord_factorial_v0, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(v);
			printf("%d\n", val);
		}

	// v1:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_factorial_v1(T v)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_factorial_v1<SizeType>,
				_chord_factorial_v1, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(v, T{1});
			printf("%d\n", val);
		}

	// v2:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_factorial_v2(T n)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_factorial_v2<SizeType>,
				_chord_factorial_v2, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(T{1}, n);
			printf("%d\n", val);
		}

	// v3:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_factorial_v3(T n)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_factorial_v3<SizeType>,
				_chord_factorial_v3, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(T{1}, n);
			printf("%d\n", val);
		}

	// v4:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_factorial_v4(T v)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_factorial_v4<SizeType>,
				_chord_factorial_v4, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(v);
			printf("%d\n", val);
		}

	// v5:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_factorial_v5(T v)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_factorial_v5<SizeType>,
				_chord_factorial_v5, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(v);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// fibonacci:

	// v0:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_fibonacci_v0(T n)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_fibonacci_v0<SizeType>,
				_chord_fibonacci_v0, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(n, T{0}, T{0});
			printf("%d\n", val);
		}

	// v1:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_fibonacci_v1(T v)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_fibonacci_v1<SizeType>,
				_chord_fibonacci_v1, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::result(v);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// falling factorial (exponent 2):

	// v0 (pointer):

		template<bool punct, typename SizeType, typename T>
		constexpr void unit_test_chord_fall_fact_2_v0(T v)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_fall_fact_2_v0<SizeType>,
				_chord_fall_fact_2_v0<punct>, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::template result<T*>(&v);
			printf("%d\n", val);
		}

	// v1 (reference):

		template<bool punct, typename SizeType, typename T>
		constexpr void unit_test_chord_fall_fact_2_v1(T v)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_fall_fact_2_v1<SizeType>,
				_chord_fall_fact_2_v1<punct>, cctmp::null_env, T
			>;

			auto val = T_chord_fast_apply::template result<T&>(v);
			printf("%d\n", val);
		}

/***********************************************************************************************************************/

// void effects:

	// v0:

	//	template<typename SizeType, typename T>
	//	constexpr void unit_test_chord_void_effects_v0(T v)
	//	{
	//		using T_chord_fast_apply = chord::T_fast_apply
	//		<
	//			contr_object_chord_void_effects_v0<SizeType>,
	//			_chord_void_effects_v0, cctmp::null_env, T
	//		>;

	//		auto val = T_chord_fast_apply::result(v);
	//		printf("%d\n", val);
	//	}

/***********************************************************************************************************************/

// side effects:

	// v0:

	//	template<typename SizeType, typename T>
	//	constexpr void unit_test_chord_side_effects_v0(T v)
	//	{
	//		using T_chord_fast_apply = chord::T_fast_apply
	//		<
	//			contr_object_chord_side_effects_v0<SizeType>,
	//			_chord_side_effects_v0, cctmp::null_env, T
	//		>;

	//		auto val = T_chord_fast_apply::result(v);
	//		printf("%d\n", val);
	//	}

