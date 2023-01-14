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
//#include"07_cctmp_parser.hpp"
//#include"08_cctmp_algorithm.hpp"

#include"undef_macros.hpp"

/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

	struct T_square
	{
		template<typename T>
		constexpr static auto result(T x) { return x*x; }

	}; constexpr auto _sq_ = U_store_T<T_square>;

//	constexpr auto sum_of_sq = arg_subpose<_add_, _sq_, _sq_>;
//	constexpr auto sum_of_sq = arg_compose<_add_, _apply_at_<_sq_, 0>, _apply_at_<_sq_, 1>>;

//	constexpr auto val = T_store_U<sum_of_sq>::template result<>(3, 4);

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	printf("%d\n", T_store_U<sum_of_sq>::template result<>(argc, 4));
	//	printf("%d\n", val);

		return 0;
	}

