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
#include"08_cctmp_compiler.hpp"
//#include"09_cctmp_algorithm.hpp"

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

	constexpr auto factorial_source()
	{
		return source
		(
		 	"factorial p n    ;"		// na:index{0} lookup:index{1} copy:index{2} paste:index{3}
					    		//	factorial:index{4} p:index{5} n:index{6} ;:index{}
					    		// indices are offset to include "na", "lookup", "copy", "paste".

			"loop:            ;"		// loop::index{1} ;:index{}
		 	"test is_zero n   ;"		// test:index{2} is_zero:index{1} n:index{6} ;:index{}
			"branch done      ;"		// branch:index{} done:index{2} ;:index{}
			"p = multiply p n ;"		// p:index{5} =:index{} multiply:index{1} p:index{5} n:index{6} ;:index{}
					    		// count: the number of args for unpacking.
			"n = decrement n  ;"		// n:index{6} =:index{} decrement:index{1} n:index{6} ;:index{}
					    		// count: the number of args for unpacking.
			"goto loop        ;"		// goto:index{} loop:index{1} ;:index{}

			"done:            ;"		// done::index{2} ;:index{}
			"return p         ;"		// return:index{} p:index{5} ;:index{}
		);
	}

	constexpr auto factorial = compile<factorial_source>;

/***********************************************************************************************************************/

	template<typename Entry>
	void print_entry(const Entry & entry)
	{
		for (auto k = entry.begin; k != entry.end; ++k) printf("%c", *k);

		printf("{%d} ", (int) entry.index);
	}

	template<typename Line>
	void print_line(const Line & line)
	{
		for (auto k = line.begin; k != line.entry; ++k) print_entry(*k);

		printf("\n");
	}

	template<typename Page>
	void print_page(const Page & page)
	{
		for (auto k = page.begin; k != page.line; ++k) print_line(*k);
	}

/***********************************************************************************************************************/

	template<typename Note>
	void print_note(const Note & note)
	{
		for (auto k = note.begin; k != note.locus; ++k) print_entry(**k);

		printf("\n");
	}

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
	//	print_note(factorial.syntax.label);
	//	print_note(factorial.syntax.go_to);
	//	print_note(factorial.syntax.branch);
		print_page(factorial.syntax.page);

		return 0;
	}

