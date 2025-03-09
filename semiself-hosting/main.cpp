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
#include<new>

/***********************************************************************************************************************/

#include"define_macros.hpp"

#include"include/00_kernel.hpp"
#include"include/01_machine.hpp"
#include"include/02_method.hpp"

#include"undef_macros.hpp"

#include"testing/printer.hpp"
#include"testing/type_system.hpp"
#include"testing/proof_oriented_programming.hpp"
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

	int main(int argc, char *argv[])
	{
		using tuple_type = tuple<int, float, char>;

		tuple_type tuple{main_at(0, argc, argv), 2.718, 'e'};

		printf("%d\n", tuple.at<0>());
		printf("%f\n", tuple.at<1>());
		printf("%c\n", tuple.at<2>());

		printf("\n");

		printf("%d\n", tuple.at_squared<0>());
		printf("%f\n", tuple.at_squared<1>());
		printf("%c\n", tuple.at_squared<2>());

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

		return 0;
	}

