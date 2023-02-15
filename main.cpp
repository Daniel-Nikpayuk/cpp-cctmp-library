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
#include"08_cctmp_optimizer.hpp"
#include"09_cctmp_metapiler.hpp"

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
/***********************************************************************************************************************/

// factorial:

/***********************************************************************************************************************/

	template<typename Instr>
	void print_target_instr(const Instr *instr)
	{
		auto size = instr[0];

		for (auto k = instr + 1; k != instr + size + 1; ++k) printf("%d ", (int) *k);

		printf("\n");
	}

	template<typename Contr>
	void print_target_contr(const Contr & contr)
	{
		for (auto k = contr.begin(); k != contr.end(); ++k) print_target_instr(*k);
	}

	template<typename Position>
	void print_target_position(const Position & pos)
	{
		for (auto k = pos.begin(); k != pos.end(); ++k) printf("%d ", (int) *k);

		printf("\n");
	}

/***********************************************************************************************************************/

	template<typename Instr>
	void print_metapiler_instr(const Instr *instr)
	{
		auto size = instr[0];

		for (auto k = instr + 1; k != instr + size + 1; ++k) printf("%d ", (int) *k);

		printf("\n");
	}

	template<typename Contr>
	void print_metapiler_contr(const Contr *contr)
	{
		auto size = contr[0][0];

		for (auto k = contr + 1; k != contr + size + 1; ++k) print_metapiler_instr(*k);
	}

/***********************************************************************************************************************/

	constexpr auto factorial_source()
	{
		return source
		(
		 	"factorial p n    ;"

			"loop:            ;"
		 	"test is_zero n   ;"
			"branch done      ;"
			"p = multiply p n ;"
			"n = decrement n  ;"
			"goto loop        ;"

			"done:            ;"
			"return p         ;"
		);
	}

	template<typename T>
	constexpr auto factorial(T v)
	{
		using T_factorial = T_generic_assembly_metapiler<factorial_source>;

		return T_factorial::template result<T>(T(1), v);
	}

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		static_assert(factorial(5) == 120);

	//	printf("%d\n", factorial(5));
	//	print_target_contr(factorial.instr);
	//	print_target_position(factorial.position);
	//	print_metapiler_contr(factorial);

		return 0;
	}

