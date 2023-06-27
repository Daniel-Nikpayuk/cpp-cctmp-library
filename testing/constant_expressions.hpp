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
#include"04_cctmp_interpreter.hpp"
#include"05_cctmp_machine.hpp"
#include"06_cctmp_relation.hpp"
#include"07_cctmp_graph.hpp"
#include"08_cctmp_lexer.hpp"
#include"09_cctmp_syntax.hpp"
#include"10_cctmp_parser.hpp"
#include"11_cctmp_generator.hpp"

#include"undef_macros.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

	template<typename, auto> struct CEArray;
	template<typename, auto> struct Array;

	template<typename T, auto N>
	void print_array(const CEArray<T, N> & arr)
	{
		for (auto k = arr.cbegin(); k != arr.cend(); ++k) printf("%d ", (int) *k);

		printf("\n");
	}

	template<typename T, auto N>
	void print_array(const Array<T, N> & arr)
	{
		for (auto k = arr.cbegin(); k != arr.cend(); ++k) printf("%d ", (int) *k);

		printf("\n");
	}

	template<typename T, auto N>
	void print_array_2(const CEArray<T, N> & arr)
	{
		for (auto k = arr.cbegin(); k != arr.cend(); ++k) print_array(*k);

		printf("\n");
	}

	template<typename T, auto N>
	void print_array_2(const Array<T, N> & arr)
	{
		for (auto k = arr.cbegin(); k != arr.cend(); ++k) print_array(*k);

		printf("\n");
	}

/***********************************************************************************************************************/


	template<typename Type, auto N>
	struct CEArray
	{
		Type initial[N];
		unsigned long long terminal;

		constexpr CEArray() : initial{}, terminal{} { }

		constexpr const auto size() const { return terminal; }
		constexpr const Type* cbegin () const { return initial; }
		constexpr const Type* cend   () const { return initial + terminal; }
		constexpr Type* begin () { return initial; }
		constexpr Type* end   () { return initial + terminal; }
		constexpr const Type & operator [] (int pos) const { return initial[pos]; }
		constexpr Type & operator [] (int pos) { return initial[pos]; }
	};

	template<typename Type, auto N>
	struct Array
	{
		Type initial[N];
		Type *terminal;

		constexpr Array() : initial{}, terminal{initial} { }

		constexpr const auto size() const { return terminal - initial; }
		constexpr const Type* cbegin () const { return initial; }
		constexpr const Type* cend   () const { return terminal; }
		constexpr Type* begin () { return initial; }
		constexpr Type* end   () { return terminal; }
		constexpr const Type & operator [] (int pos) const { return initial[pos]; }
		constexpr Type & operator [] (int pos) { return initial[pos]; }
	};


/***********************************************************************************************************************/

	template<typename Type>
	struct CSubarray
	{
		const Type *start;
		const Type *finish;

		constexpr CSubarray() : start{}, finish{} { }
		constexpr CSubarray(const Type *s, const Type *f) :
			start{s}, finish{f} { }

		constexpr const Type* cbegin () const { return start; }
		constexpr const Type* cend   () const { return finish; }
	};

	template<typename Type>
	struct Subarray : public CSubarray<Type>
	{
		using base = CSubarray<Type>;

		constexpr Subarray() : base{} { }
		constexpr Subarray(const Type *s, const Type *f) :
			base{(Type*) s, (Type*) f} { }

		constexpr Type* begin () { return (Type*) base::start; }
		constexpr Type* end   () { return (Type*) base::finish; }
	};

/***********************************************************************************************************************/

	template<typename Type, auto N>
	constexpr auto array_2(const Array<Type, N> & a)
	{
	//	  Array <   Array<Type,N>, N> arr{}; // error: pointer to subobject of arr is not a constant expression.
	//	  Array < CEArray<Type,N>, N> arr{}; // error: pointer to subobject of arr is not a constant expression.
	//	CEArray <   Array<Type,N>, N> arr{}; // error: pointer to subobject of arr is not a constant expression.
		CEArray < CEArray<Type,N>, N> arr{}; // works!

		return arr;
	}

/***********************************************************************************************************************/

	constexpr auto arr   = Array<int, 10>{};
	constexpr auto arr_2 = array_2(arr);
	constexpr auto size  = arr_2[5].size();

