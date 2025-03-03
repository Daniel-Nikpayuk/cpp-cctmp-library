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

// continuant machine (type system):

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	constexpr auto U_null_Vs = cctmp::U_null_Vs;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// static:

/***********************************************************************************************************************/

// identity:

	template<typename T>
	constexpr auto cc_identity(T v)
	{
		constexpr auto contr = cctmp::U_store_T<static_identity_test<concord_test_cc_function, T>>;

		return cctmp::T_metapile_apply<contr, U_null_Vs, U_null_Vs>::template result<T>(v);
	}

/***********************************************************************************************************************/

// square:

	template<typename T>
	constexpr auto cc_square(T v)
	{
		constexpr auto contr = cctmp::U_store_T<static_square_test<concord_test_cc_function, T>>;

		return cctmp::T_metapile_apply<contr, U_null_Vs, U_null_Vs>::template result<T>(v);
	}

/***********************************************************************************************************************/

// sum of squares:

	template<typename T>
	constexpr auto cc_sum_of_sq(T v1, T v2)
	{
		constexpr auto contr = cctmp::U_store_T<static_sum_of_sq_test<concord_test_cc_function, T>>;

		return cctmp::T_metapile_apply<contr, U_null_Vs, U_null_Vs>::template result<T, T>(v1, v2);
	}

/***********************************************************************************************************************/

// factorial:

	template<typename T>
	constexpr auto cc_factorial(T v)
	{
		constexpr auto contr = cctmp::U_store_T<static_factorial_test<concord_test_cc_function, T>>;
		constexpr auto types = cctmp::U_pack_Ts<T>;

		return cctmp::T_metapile_recurse<contr, U_null_Vs, types>::template result<T>(v);
	}

/***********************************************************************************************************************/

// fibonacci:

	template<typename T>
	constexpr auto cc_fibonacci(T v)
	{
		constexpr auto contr = cctmp::U_store_T<static_fibonacci_test<concord_test_cc_function, T>>;
		constexpr auto types = cctmp::U_pack_Ts<T>;

		return cctmp::T_metapile_recurse<contr, U_null_Vs, types>::template result<T>(v);
	}

/***********************************************************************************************************************/

// test:

	void continuant_machine_test()
	{
		// identity:

			static_assert(cc_identity<unsigned long>(5) == 5);

			printf("%lu\n", cc_identity<unsigned long>(5));

		// square:

			static_assert(cc_square<unsigned long>(5) == 25);

			printf("%lu\n", cc_square<unsigned long>(5));

		// sum of squares:

			static_assert(cc_sum_of_sq<unsigned long>(3, 4) == 25);

			printf("%lu\n", cc_sum_of_sq<unsigned long>(3, 4));

		// factorial:

			static_assert(cc_factorial<unsigned long>(5) == 120);

			printf("%lu\n", cc_factorial<unsigned long>(5));

		// fibonacci:

			static_assert(cc_fibonacci<unsigned long>(8) == 34);

			printf("%lu\n", cc_fibonacci<unsigned long>(8));
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

