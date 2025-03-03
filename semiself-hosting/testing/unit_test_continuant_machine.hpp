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

	constexpr auto identity_contr = cctmp::U_store_T<static_identity_test<unsigned long>>;

	template<typename T>
	constexpr auto identity(T v)
		{ return cctmp::T_metapile_apply<identity_contr, U_null_Vs, U_null_Vs>::template result(0, v); }

/***********************************************************************************************************************/

// square:

	constexpr auto square_contr = cctmp::U_store_T<static_square_test<unsigned long>>;

	template<typename T>
	constexpr auto square(T v)
		{ return cctmp::T_metapile_apply<square_contr, U_null_Vs, U_null_Vs>::template result(0, v); }

/***********************************************************************************************************************/

// sum of squares:

	constexpr auto sum_of_sqs_contr = cctmp::U_store_T<static_sum_of_sqs_test<unsigned long>>;

/*
	template<typename T>
	constexpr auto sum_of_sqs(T v1, T v2)
		{ return cctmp::T_metapile_apply<sum_of_sqs_contr, U_null_Vs, U_null_Vs>::template result(0, v1, v2); }
*/

/***********************************************************************************************************************/

// factorial:

	constexpr auto factorial_contr = cctmp::U_store_T<static_factorial_test<unsigned long>>;

/*
	template<typename T>
	constexpr auto factorial(T v)
		{ return cctmp::T_metapile_apply<factorial_contr, U_null_Vs, U_null_Vs>::template result(0, v); }
*/

/***********************************************************************************************************************/

// fibonacci:

	constexpr auto fibonacci_contr = cctmp::U_store_T<static_fibonacci_test<unsigned long>>;

/*
	template<typename T>
	constexpr auto fibonacci(T v)
		{ return cctmp::T_metapile_apply<fibonacci_contr, U_null_Vs, U_null_Vs>::template result(0, v); }
*/

/***********************************************************************************************************************/

// test:

	void continuant_machine_test()
	{
		// identity:

			static_assert(identity<unsigned long>(5) == 5);

			printf("%lu\n", identity<unsigned long>(5));

		// square:

			static_assert(square<unsigned long>(5) == 25);

			printf("%lu\n", square<unsigned long>(5));
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

