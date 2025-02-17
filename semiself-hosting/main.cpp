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

		constexpr static size_type result[28] =
		{
			MI::program         , 5 ,            0 , 1 ,	// line 0: action,  lines, atomic, next
			MI::function        , 5 , MP::to_stack , 1 ,	// line 1: action, inline, policy, next
			MI::memory_to_stack , 0 ,            1 , 1 ,	// line 2: action,  begin,    end, next
			MI::memory_to_stack , 0 ,            1 , 1 ,	// line 3: action,  begin,    end, next
			MI::apply           , 0 , MP::to_carry , 0 ,	// line 4: action,  begin, policy, next

		// multiply:

			MI::program         , 2 ,            1 , 1 ,	// line 5: action,  lines, atomic, next
			MI::multiply        , 0 , MP::to_carry , 0	// line 6: action,  begin, policy, next
		};
	};

/***********************************************************************************************************************/

// sum of squares:

	template<typename MI, typename MP, typename SizeType>
	struct sum_of_squares_contr
	{
		using size_type = SizeType;

		constexpr static size_type result[72] =
		{
			MI::program         ,  9 ,            0 , 1 ,	// 00
			MI::function        , 16 , MP::to_stack , 1 ,	// 01
			MI::function        ,  9 , MP::to_stack , 1 ,	// 02
			MI::memory_to_stack ,  0 ,            1 , 1 ,	// 03
			MI::apply           ,  1 , MP::to_stack , 1 ,	// 04
			MI::function        ,  9 , MP::to_stack , 1 ,	// 05
			MI::memory_to_stack ,  1 ,            2 , 1 ,	// 06
			MI::apply           ,  2 , MP::to_stack , 1 ,	// 07
			MI::apply           ,  0 , MP::to_carry , 0 ,	// 08

		// square:

			MI::program         ,  5 ,            0 , 1 ,	// 09
			MI::function        , 14 , MP::to_stack , 1 ,	// 10
			MI::memory_to_stack ,  0 ,            1 , 1 ,	// 11
			MI::memory_to_stack ,  0 ,            1 , 1 ,	// 12
			MI::apply           ,  0 , MP::to_carry , 0 ,	// 13

		// multiply:

			MI::program         ,  2 ,            1 , 1 ,	// 14
			MI::multiply        ,  0 , MP::to_carry , 0 ,	// 15

		// add:

			MI::program         ,  2 ,            1 , 1 ,	// 16
			MI::add             ,  0 , MP::to_carry , 0	// 17
		};
	};

/***********************************************************************************************************************/

	template<typename size_type>
	constexpr auto eval_sq_test(size_type const v)
	{
		using eval_type   = eval<size_type, size_type, 100, 10, 10, 10>;
		using method_type = resolve_method<eval_type, eval_method>;
		using sq_contr    = square_contr<MachineInstr, MachinePolicy, size_type>;

		auto eval_value   = eval_type{sq_contr::result};
		auto eval_method  = eval_value.template equip<method_type>();

		return eval_method.run({v});
	}

	constexpr auto carry_sq = eval_sq_test<unsigned long>(5);

/***********************************************************************************************************************/

	template<typename size_type>
	constexpr auto eval_sum_of_sqs_test(size_type const v1, size_type const v2)
	{
		using eval_type        = eval<size_type, size_type, 100, 10, 10, 10>;
		using method_type      = resolve_method<eval_type, eval_method>;
		using sum_of_sqs_contr = sum_of_squares_contr<MachineInstr, MachinePolicy, size_type>;

		auto eval_value        = eval_type{sum_of_sqs_contr::result};
		auto eval_method       = eval_value.template equip<method_type>();

		return eval_method.run({v1, v2});
	}

	constexpr auto carry_sum_of_sqs = eval_sum_of_sqs_test<unsigned long>(3, 7);

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		// square:

			static_assert(carry_sq.cat(0) == 25);

		// sum of squares:

			static_assert(carry_sum_of_sqs.cat(0) == 58);

		return 0;
	}

