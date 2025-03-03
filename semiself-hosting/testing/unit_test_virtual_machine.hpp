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

// virtual machine (type system):

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// identity:

	template<typename size_type>
	constexpr auto vm_identity(size_type const v)
	{
		constexpr auto function = concord_test_vm_function<size_type>{};

		auto eval_cmethod = function.eval_cmethod();
		eval_cmethod      . apply(function.identity_sign, {v});

		return eval_cmethod.rtn_cat(0);
	}

/***********************************************************************************************************************/

// square:

	template<typename size_type>
	constexpr auto vm_square(size_type const v)
	{
		constexpr auto function = concord_test_vm_function<size_type>{};

		auto eval_cmethod = function.eval_cmethod();
		eval_cmethod      . apply(function.square_sign, {v});

		return eval_cmethod.rtn_cat(0);
	}

/***********************************************************************************************************************/

// sum of squares:

	template<typename size_type>
	constexpr auto vm_sum_of_sq(size_type const v1, size_type const v2)
	{
		constexpr auto function = concord_test_vm_function<size_type>{};

		auto eval_cmethod = function.eval_cmethod();
		eval_cmethod      . apply(function.sum_of_sq_sign, {v1, v2});

		return eval_cmethod.rtn_cat(0);
	}

/***********************************************************************************************************************/

// factorial:

	template<typename size_type>
	constexpr auto vm_factorial(size_type const v)
	{
		constexpr auto function = concord_test_vm_function<size_type>{};

		auto eval_cmethod = function.eval_cmethod();
		eval_cmethod      . apply(function.factorial_sign, {v});

		return eval_cmethod.rtn_cat(0);
	}

/***********************************************************************************************************************/

// fibonacci:

	template<typename size_type>
	constexpr auto vm_fibonacci(size_type const v)
	{
		constexpr auto function = concord_test_vm_function<size_type>{};

		auto eval_cmethod = function.eval_cmethod();
		eval_cmethod      . apply(function.fibonacci_sign, {v});

		return eval_cmethod.rtn_cat(0);
	}

/***********************************************************************************************************************/

// test:

	void virtual_machine_test()
	{
		// identity:

			static_assert(vm_identity<unsigned long>(5) == 5);

			printf("%lu\n", vm_identity<unsigned long>(5));

		// square:

			static_assert(vm_square<unsigned long>(5) == 25);

			printf("%lu\n", vm_square<unsigned long>(5));

		// sum of squares:

			static_assert(vm_sum_of_sq<unsigned long>(3, 7) == 58);

			printf("%lu\n", vm_sum_of_sq<unsigned long>(3, 7));

		// factorial:

			static_assert(vm_factorial<unsigned long>(5) == 120);

			printf("%lu\n", vm_factorial<unsigned long>(5));

		// fibonacci:

			static_assert(vm_fibonacci<unsigned long>(8) == 34);

			printf("%lu\n", vm_fibonacci<unsigned long>(8));
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

