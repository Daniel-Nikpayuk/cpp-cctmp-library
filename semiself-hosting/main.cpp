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

#include<cstdio>
//#include<cstdlib>

/***********************************************************************************************************************/

#include"define_macros.hpp"

#include"include/00_kernel.hpp"
#include"include/01_automata.hpp"

#include"undef_macros.hpp"

#include"testing/printer.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

// square:

	template<typename MI, typename MP, typename SizeType>
	struct square_contr
	{
		using size_type = SizeType;

		constexpr static size_type result[32] =
		{
			MI::program         , 6 ,            0 , 2 ,	// line 0: action,  lines, atomic,   next
			MI::define_argument , 0 ,            0 , 1 ,	// line 1: action,  index,  start, finish
			MI::function        , 6 , MP::to_stack , 1 ,	// line 2: action, inline, policy,   next
			MI::argument        , 1 , MP::to_stack , 1 ,	// line 3: action, inline, policy,   next
			MI::argument        , 1 , MP::to_stack , 1 ,	// line 4: action, inline, policy,   next
			MI::apply           , 0 , MP::to_carry , 0 ,	// line 5: action, offset, policy,   next

		// multiply:

			MI::program         , 2 ,            1 , 1 ,	// line 6: action,  lines, atomic,   next
			MI::multiply        , 0 , MP::to_carry , 0	// line 7: action, offset, policy,   next
		};
	};

	// test:

		template<typename size_type>
		constexpr auto square(size_type const v)
		{
			using eval_type   = eval<size_type, size_type, 100, 10, 10, 10>;
			using method_type = resolve_method<eval_type, eval_method>;
			using sq_contr    = square_contr<MachineInstr, MachinePolicy, size_type>;

			auto eval_value   = eval_type{sq_contr::result};
			auto eval_method  = eval_value.template equip<method_type>();
			auto carry_value  = eval_method.run({v});

			return carry_value[0];
		}

/***********************************************************************************************************************/

// sum of squares:

	template<typename MI, typename MP, typename SizeType>
	struct sum_of_squares_contr
	{
		using size_type = SizeType;

		constexpr static size_type result[84] =
		{
			MI::program         , 11 ,            0 , 3 ,	// 00
			MI::define_argument ,  0 ,            0 , 1 ,	// 01
			MI::define_argument ,  1 ,            1 , 2 ,	// 02
			MI::function        , 19 , MP::to_stack , 1 ,	// 03
			MI::function        , 11 , MP::to_stack , 1 ,	// 04
			MI::argument        ,  1 , MP::to_stack , 1 ,	// 05
			MI::apply           ,  1 , MP::to_stack , 1 ,	// 06
			MI::function        , 11 , MP::to_stack , 1 ,	// 07
			MI::argument        ,  2 , MP::to_stack , 1 ,	// 08
			MI::apply           ,  2 , MP::to_stack , 1 ,	// 09
			MI::apply           ,  0 , MP::to_carry , 0 ,	// 10

		// square:

			MI::program         ,  6 ,            0 , 2 ,	// 11
			MI::define_argument ,  0 ,            0 , 1 ,	// 12
			MI::function        , 17 , MP::to_stack , 1 ,	// 13
			MI::argument        , 12 , MP::to_stack , 1 ,	// 14
			MI::argument        , 12 , MP::to_stack , 1 ,	// 15
			MI::apply           ,  0 , MP::to_carry , 0 ,	// 16

		// multiply:

			MI::program         ,  2 ,            1 , 1 ,	// 17
			MI::multiply        ,  0 , MP::to_carry , 0 ,	// 18

		// add:

			MI::program         ,  2 ,            1 , 1 ,	// 19
			MI::add             ,  0 , MP::to_carry , 0	// 20
		};
	};

	// test:

		template<typename size_type>
		constexpr auto sum_of_squares(size_type const v1, size_type const v2)
		{
			using eval_type        = eval<size_type, size_type, 100, 10, 10, 10>;
			using method_type      = resolve_method<eval_type, eval_method>;
			using sum_of_sqs_contr = sum_of_squares_contr<MachineInstr, MachinePolicy, size_type>;

			auto eval_value        = eval_type{sum_of_sqs_contr::result};
			auto eval_method       = eval_value.template equip<method_type>();
			auto carry_value       = eval_method.run({v1, v2});

			return carry_value[0];
		}

/***********************************************************************************************************************/

// factorial:

	template<typename MI, typename MP, typename SizeType>
	struct factorial_contr
	{
		using size_type = SizeType;

		constexpr static size_type result[96] =
		{
			MI::program         , 16 ,            0 , 2 ,	// 00
			MI::define_argument ,  0 ,            0 , 1 ,	// 01
			MI::function        , 20 , MP::to_stack , 1 ,	// 02 = 0
			MI::argument        ,  1 , MP::to_stack , 1 ,	// 03 n 1
			MI::constant        ,  0 , MP::to_stack , 1 ,	// 04 0 2
			MI::apply           ,  0 , MP::to_carry , 1 ,	// 05
			MI::branch          , 22 ,            0 , 1 ,	// 06 1
			MI::function        , 16 , MP::to_stack , 1 ,	// 07 * 0
			MI::argument        ,  1 , MP::to_stack , 1 ,	// 08 n 1
			MI::function        ,  0 , MP::to_stack , 1 ,	// 09 f 2
			MI::function        , 18 , MP::to_stack , 1 ,	// 10 - 3
			MI::argument        ,  1 , MP::to_stack , 1 ,	// 11 n 4
			MI::constant        ,  1 , MP::to_stack , 1 ,	// 12 1 5
			MI::apply           ,  3 , MP::to_stack , 1 ,	// 13
			MI::apply           ,  2 , MP::to_stack , 1 ,	// 14
			MI::apply           ,  0 , MP::to_carry , 0 ,	// 15

		// multiply:

			MI::program         ,  2 ,            1 , 1 ,	// 16
			MI::multiply        ,  0 , MP::to_carry , 0 ,	// 17

		// subtract:

			MI::program         ,  2 ,            1 , 1 ,	// 18
			MI::subtract        ,  0 , MP::to_carry , 0 ,	// 19

		// equal:

			MI::program         ,  2 ,            1 , 1 ,	// 20
			MI::equal           ,  0 , MP::to_carry , 0 ,	// 21

		// one:

			MI::program         ,  2 ,            1 , 1 ,	// 22
			MI::constant        ,  1 , MP::to_carry , 0	// 23
		};
	};

	// test:

		template<typename size_type>
		constexpr auto factorial(size_type const v)
		{
			using eval_type   = eval<size_type, size_type, 100, 10, 10, 10>;
			using method_type = resolve_method<eval_type, eval_method>;
			using fact_contr  = factorial_contr<MachineInstr, MachinePolicy, size_type>;

			auto eval_value   = eval_type{fact_contr::result};
			auto eval_method  = eval_value.template equip<method_type>();
			auto carry_value  = eval_method.run({v});

			return carry_value[0];
		}

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		// square:

		//	static_assert(square<unsigned long>(5) == 25);

		//	printf("%lu\n", square<unsigned long>(5));

		// sum of squares:

		//	static_assert(sum_of_squares<unsigned long>(3, 7) == 58);

		//	printf("%lu\n", sum_of_squares<unsigned long>(3, 7));

		// factorial:

		//	static_assert(factorial<unsigned long>(5) == 25);

			printf("%lu\n", factorial<unsigned long>(5));

		return 0;
	}

