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
//#include"include/03_encoding.hpp"
//#include"include/04_fileput.hpp"
//#include"include/05_lexer.hpp"
//#include"include/06_parser.hpp"
//#include"include/07_chord.hpp"
//#include"include/08_hustle.hpp"

#include"undef_macros.hpp"

//#include"testing/diagnostic.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

//	using size_type = gindex_type;
//	using text_type = int;
//	using page_type = engine::plot_page_type<size_type>;
//	using plot_type = engine::plot<page_type, text_type, size_type, 2, 2>;

//	constexpr auto make_plot()
//	{
//		auto p = plot_type{};

	//	p.upsize();

	//	p.begin()->upsize();

//		return p;
//	}

//	constexpr auto plot0 = make_plot();

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	for (auto k = plot0.cbegin(); k != plot0.cend(); ++k);
	//		printf("%d ", k->size());

	//	printf("\n");

	//	constexpr auto parsed = parser_main();

	//	printf("nonterminal size: %d\n", parsed.ctree().cscript().cnonterminal().size());
	//	printf("symbol size: %d\n", parsed.ctree().cscript().csymbol().cpage().size());

	//	printf("%f\n", inventory_square_root_v0<gindex_type>(2.0));

	//	auto arr0 = array<int, gindex_type, 5>{{1, 2, 3, 4, 5}};
	//	auto arr1 = array<int, gindex_type, 5>{{1, 2, 3, 0, 5}};

	//	printf("%d\n", inventory_different_v0<gindex_type>(arr0.cbegin(), arr0.cend(), arr1.cbegin()));

		return 0;
	}

