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
//#include"include/01_inventory.hpp"
#include"include/02_engine.hpp"
#include"include/03_encoding.hpp"
//#include"include/04_fileput.hpp"
//#include"include/05_lexer.hpp"
#include"include/06_parser.hpp"
//#include"include/07_chord.hpp"
//#include"include/08_hustle.hpp"

#include"undef_macros.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	auto c = encoding::utf8_char<char, gindex_type>{'_'};

	//	printf("%s whitespace\n", c.to_ascii().is_whitespace() ? "is" : "not");

	//	using utf8_apply = engine::utf8_apply<engine::Utf8Spec::x000000_x00007f>;

	//	const unsigned char utf8_str0[] = { 0x4d, 0xd0, 0xb0, 0xe4, 0xba, 0x8c, 0xf0, 0x90, 0x8c, 0x82 };

	//	printf("%d\n", utf8_apply::to_scalar(utf8_str0));

	//	printf("%f\n", inventory_square_root_v0<gindex_type>(2.0));

	//	auto arr0 = array<int, gindex_type, 5>{{1, 2, 3, 4, 5}};
	//	auto arr1 = array<int, gindex_type, 5>{{1, 2, 3, 0, 5}};

	//	printf("%d\n", inventory_different_v0<gindex_type>(arr0.cbegin(), arr0.cend(), arr1.cbegin()));

		return 0;
	}

