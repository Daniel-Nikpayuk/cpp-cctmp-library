/************************************************************************************************************************
**
** Copyright 2022-2023 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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
#include"01_cctmp_argument.hpp"
#include"02_cctmp_parameter.hpp"
#include"03_cctmp_praxis.hpp"
#include"04_cctmp_machine.hpp"
#include"05_cctmp_assembly.hpp"
#include"06_cctmp_lexer.hpp"
#include"07_cctmp_parser.hpp"
//#include"08_cctmp_algorithm.hpp"

#include"undef_macros.hpp"

/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

//	constexpr auto _sq_       = arg_compose<_multiply_, _arg_at_<0>, _arg_at_<0>>;

//	constexpr auto sum_of_sq0 = arg_subpose<_add_, _sq_, _sq_>;
//	constexpr auto sum_of_sq1 = arg_compose<_add_, _apply_at_<_sq_, 0>, _apply_at_<_sq_, 1>>;

//	constexpr auto val0       = T_store_U<sum_of_sq0>::template result<>(3, 4);
//	constexpr auto val1       = T_store_U<sum_of_sq1>::template result<>(3, 4);

/***********************************************************************************************************************/

	constexpr T_goto_dfa dfa;

	constexpr char str[] = "goto";
	constexpr auto val = dfa.lex(str, str + 4);

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		printf("%d\n", val.token);

	//	printf("%d\n", val0); // prints: 25
	//	printf("%d\n", val1); // prints: 25

		return 0;
	}

