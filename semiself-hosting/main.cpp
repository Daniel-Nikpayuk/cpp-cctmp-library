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
#include<cstdlib>

/***********************************************************************************************************************/

#include"define_macros.hpp"

#include"include/00_kernel.hpp"
#include"include/01_machine.hpp"
#include"include/02_method.hpp"

#include"undef_macros.hpp"

#include"testing/printer.hpp"
#include"testing/type_system.hpp"
//#include"testing/unit_test_type_system.hpp"
//#include"testing/unit_test_continuant_machine.hpp"
//#include"testing/unit_test_virtual_machine.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

// main at:

	template<typename T>
	auto main_at(T n, int argc, char *argv[], T def = 0) -> T
	{
		auto pos = n + 1;

		if (pos < argc) return atoi(argv[pos]);
		else            return def;
	}

/***********************************************************************************************************************/

/*
	template<typename T>
	constexpr auto square(T v)
	{
		constexpr auto square_contr = cctmp::U_store_T<static_square_test<unsigned long>>;

		return cctmp::T_metapile_apply<square_contr, U_null_Vs, U_null_Vs>::template result(0, v);
	}
*/

	template<typename size_type>
	constexpr auto square(size_type const v)
	{
		constexpr auto function_test_0 = concord_test_function<size_type>{};
		auto eval_cmethod = function_test_0.eval_cmethod();
		eval_cmethod      . apply(function_test_0.square_sign, {v});

		return eval_cmethod.rtn_cat(0);
	}

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	concord_empty_test      ();
	//	concord_ring_test       ();
	//	concord_utf8_char_test  ();
	//	concord_tuple_test      ();
	//	concord_cotuple_test    ();
	//	concord_function_test   ();
	//	concord_list_test       ();
	//	concord_space_test      ();

	//	continuant_machine_test ();
	//	virtual_machine_test    ();

		printf("%lu\n", square<unsigned long>(main_at(0, argc, argv)));

		return 0;
	}

