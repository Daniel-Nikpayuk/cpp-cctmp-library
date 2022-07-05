/************************************************************************************************************************
**
** Copyright 2022 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

/***********************************************************************************************************************/

#include"define_macros.hpp"
#include"00_cctmp_grammar.hpp"
#include"01_cctmp_block.hpp"
#include"02_cctmp_machine.hpp"
#include"03_cctmp_functional.hpp"
//#include"04_cctmp_front.hpp"
//#include"05_generic_assembly.hpp"
//#include"06_one_cycle_generics.hpp"
//#include"07_one_cycle_specifics.hpp"
//#include"08_domain_specifics.hpp"
//#include"09_big_numbers.hpp"
//#include"10_cryptography.hpp"
//#include"11_numerical.hpp"
//#include"12_signal_processing.hpp"
#include"undef_macros.hpp"

/***********************************************************************************************************************/

	using namespace cctmp;
//	using namespace cctmp_generics;

/***********************************************************************************************************************/

	constexpr void print_array(int *b, const int *e)
	{
		while (b != e)
		{
			printf("%d, ", *b);
			++b;
		}

		printf("end\n");
	}

	constexpr void repeat_array(int *b, const int *e, int v)
	{
		while (b != e) *(b++) = v;
	}

/***********************************************************************************************************************/

	constexpr auto p = U_pack_Vs
	<
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,
	//	16, 7, 12, 3, 1,  200, 99, 0, 5, 41,

		99, 0, 5, 41
	>;

/***********************************************************************************************************************/

//	constexpr auto direct_spec = cpp_one_cycle_specs::template direct_repeat<>;

	int main(int argc, char *argv[])
	{
	//	printf("%s\n", call<Overload::same, U_char, U_char> ? "true" : "false");
	//	printf("%llu\n", call<Overload::map, cctmp::template increment_op<>, p>);
	//	printf("%hu\n", call<Overload::find, cctmp::template is_zero_op<>, p>);

	//	printf("%d\n",   cctmp_functional::at<0, p>);
	//	printf("%llu\n", cctmp_functional::left<0, p>);
	//	printf("%llu\n", cctmp_functional::split<2, p>);
	//	printf("%llu\n", cctmp_functional::segment<unsigned{10}>);

	//	printf("%llu\n", cctmp_functional::erase<0, p>);
	//	printf("%llu\n", cctmp_functional::insert<7, 4, p>);
	//	printf("%llu\n", cctmp_functional::replace<7, 1, p>);

	//	printf("%llu\n", cctmp_functional::fold<cctmp::template add_op<>, uint_type{0}, p>);

	//	printf("%llu\n", cctmp_functional::insert_sort<p, 3>);
	//	printf("%llu\n", cctmp_functional::sort<p>);	// gcc 1.717s / clang 4.199s
								// gcc 1.344s / clang 3.568s

	//	int size = 10;
	//	int arr[size];
	//	cpp_one_cycle_generics::T_repeat<direct_spec>::result(arr, arr+size, argc);
	//	repeat_array(arr, arr+size, argc);
	//	print_array(arr, arr+size);

		return 0;
	}

