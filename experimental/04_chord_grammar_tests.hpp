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

// chord grammar tests:

namespace chord {

	constexpr auto _add_		= cctmp::_add_;
	constexpr auto _multiply_	= cctmp::_multiply_;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

	void grammar_tests()
	{

	// case studies:

		constexpr auto _1_0i        = complex_number(1, 0);
		constexpr auto _0_1i        = complex_number(0, 1);
		constexpr auto _1_2i        = complex_number(1, 2);
		constexpr auto _m3f_4fi     = complex_number(-3.0, 4.0);
		constexpr auto _m4f_4fi     = complex_number(-4.0, 4.0);

		constexpr auto comp_sq_v0      = square_v0(_1_2i);
		constexpr auto comp_sq_v1      = square_v1(_1_2i);
		constexpr auto comp_sum_sqs_v0 = sum_of_squares_v0(_1_2i, _0_1i);
		constexpr auto int_sum_sqs_v0  = sum_of_squares_v0(3, 4);
		constexpr auto comp_sum_sqs_v1 = sum_of_squares_v1(_1_2i, _0_1i);
		constexpr auto int_sum_sqs_v1  = sum_of_squares_v1(3, 4);
		constexpr auto int_twice_v0    = twice_v0(5);
		constexpr auto polynom_val     = x_to5_plus1_v0(2);
		constexpr auto reassign_val    = reassign_v0(2, 17);
		constexpr auto semidyntyp0     = semidynamic_typing_v0(_0_1i, 17);
		constexpr auto semidyntyp1     = semidynamic_typing_v0(_1_0i, 17);
		constexpr auto semidyntyp2     = semidynamic_typing_v1(_0_1i, 17);
		constexpr auto semidyntyp3     = semidynamic_typing_v1(_1_0i, 17);
		constexpr auto bin_dis_val0    = binary_dispatch_v0(0, _add_, _multiply_, 5, 6);
		constexpr auto bin_dis_val1    = binary_dispatch_v0(1, _add_, _multiply_, 5, 6);
		constexpr auto bin_dis_val2    = binary_dispatch_v1(0, _add_, _multiply_, 5, 6);
		constexpr auto bin_dis_val3    = binary_dispatch_v1(1, _add_, _multiply_, 5, 6);

		static_assert(comp_sq_v0      == _m3f_4fi);
		static_assert(comp_sq_v1      == _m3f_4fi);
		static_assert(comp_sum_sqs_v0 == _m4f_4fi);
		static_assert(int_sum_sqs_v0  == 25);
		static_assert(comp_sum_sqs_v1 == _m4f_4fi);
		static_assert(int_sum_sqs_v1  == 25);
		static_assert(int_twice_v0    == 10);
		static_assert(polynom_val     == 33);
		static_assert(reassign_val    == 17);
		static_assert(semidyntyp0     == 18);
		static_assert(semidyntyp1     == 5);
		static_assert(semidyntyp2     == 18);
		static_assert(semidyntyp3     == 5);
		static_assert(bin_dis_val0    == 11);
		static_assert(bin_dis_val1    == 30);
		static_assert(bin_dis_val2    == 11);
		static_assert(bin_dis_val3    == 30);

	// factorial:

		static_assert(factorial_v0(0) ==     1);
		static_assert(factorial_v1(3) ==     6);
		static_assert(factorial_v2(5) ==   120);
		static_assert(factorial_v3(7) ==  5040);
		static_assert(factorial_v4(8) == 40320);

	// fibonacci:

		static_assert(fibonacci_v0(7) ==   21);
		static_assert(fibonacci_v1(8) ==   34);

	// falling factorial:

		constexpr auto fall_val0 = fall_fact_2_v0<true>(7);
		constexpr auto fall_val1 = fall_fact_2_v1<true>(7);

		static_assert(fall_val0 == 42);
		static_assert(fall_val1 == 42);

	// void effects:

		int vf_n = 5, *vf_ptr = &vf_n;

		void_effects_v0(vf_ptr);

		printf("%d\n", *vf_ptr); // prints: 3

	// side effects:

		int sf_n = 5, *sf_ptr = &sf_n;

		side_effects_v0(sf_ptr);

		printf("%d\n", *sf_ptr); // prints: 3
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

