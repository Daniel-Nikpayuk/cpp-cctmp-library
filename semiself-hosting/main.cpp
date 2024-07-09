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
#include"include/01_inventory.hpp"
#include"include/02_engine.hpp"
#include"include/03_fileput.hpp"
#include"include/04_chord.hpp"
#include"include/05_hustle.hpp"

#include"undef_macros.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		using size_type		= gindex_type;
		using literal_type	= engine::literal<size_type, size_type>;
		using strlit_type	= engine::string_literal<const char, size_type>;

		using lexer_table_type	= inventory::lexer_transition_table_hustle<size_type>;
		using lexer_state_type	= engine::lexer_state
					<
						typename lexer_table_type::State,
						typename lexer_table_type::Charset,
						const char*, size_type
					>;
		using lexer_policy_type	= hustle::lexer_policy
					<
						typename lexer_table_type::State,
						typename lexer_table_type::Charset,
						char, size_type
					>;

		constexpr auto table	= literal_type
					{
						lexer_table_type::value,
						lexer_table_type::value + lexer_table_type::seq.size()
					};
		constexpr auto strlit0	= strlit_type{"hi there everybody!"};

		auto lexer = lexer_state_type{table, strlit0.cbegin(), strlit0.cend()};

		while (lexer.not_end())
		{
			lexer.template lex<lexer_policy_type>();

			for (auto k = lexer.cbegin(); k != lexer.ccurrent(); ++k)
				printf("%c", *k);

			printf("\n");
		}

		return 0;
	}

