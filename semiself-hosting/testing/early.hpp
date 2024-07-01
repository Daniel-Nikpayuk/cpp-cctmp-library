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

// early:

/***********************************************************************************************************************/

// left:

		constexpr auto l0 = right_
		<
			0,

			0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,
			0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,
			0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,
			0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,
			0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,

			0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,
			0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,
			0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,
			0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,
			0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 1, 2, 3, 4,  5, 6, 7, 8, 9,

			0, 1, 2, 3, 4,  5, 6, 7, 8, 9,    0, 11, 2, 3, 4,  5, 6, 7, 8, 9
		>;

		printf("%d\n", l0);

/***********************************************************************************************************************/

// segment:

		constexpr auto l0 = segment_<100>;

		printf("%d\n", l0);

/***********************************************************************************************************************/

// tuple:

	// make, value, size, empty:

		auto tup = LambdaTuple::make(1, 2.0, 'c');

		printf("%d\n", LambdaTuple::template value<0>(tup));
		printf("%f\n", LambdaTuple::template value<1>(tup));
		printf("%c\n", LambdaTuple::template value<2>(tup));

		printf("%lu\n", LambdaTuple::size(tup));
		printf("%s\n", LambdaTuple::empty(tup) ? "is empty" : "not empty");

	// make, catenate size, value:

		constexpr auto lt1 = LambdaTuple::make(1, 2, 3);
		constexpr auto lt2 = LambdaTuple::make(4, 5, 6);

		constexpr auto cat = LambdaTuple::catenate(lt1, lt2);

		printf("%lu\n", LambdaTuple::size(cat));

		printf("%d\n", LambdaTuple::template value<0>(cat));
		printf("%d\n", LambdaTuple::template value<1>(cat));
		printf("%d\n", LambdaTuple::template value<2>(cat));
		printf("%d\n", LambdaTuple::template value<3>(cat));
		printf("%d\n", LambdaTuple::template value<4>(cat));
		printf("%d\n", LambdaTuple::template value<5>(cat));

/***********************************************************************************************************************/

// frame:

		constexpr auto f = frame
		(
			U_gcchar_type, U_gindex_type,

			gbinding("zero"  , 0),
			gbinding("one"   , 1),
			gbinding("two"   , 2),
			gbinding("three" , 3),
			gbinding("four"  , 4),
			gbinding("five"  , 5)
		);

		printf("%s\n", LambdaTuple::value<0>(f)[4].origin());
		printf("%d\n", LambdaTuple::value<4>(LambdaTuple::value<1>(f)));

/***********************************************************************************************************************/

// different:

		constexpr auto s0 = push_sequence(1, 2, 3, 4, 5);
		constexpr auto s1 = push_sequence(1, 2, 3, 4, 5);

		auto val = inventory_different_v0<gindex_type>(s0.cbegin(), s0.cend(), s1.cbegin());
		printf("%s\n", val ? "different" : "same");

/***********************************************************************************************************************/

// stack:

	// push:

		template<typename... Ts>
		constexpr auto push_stack(Ts... vs)
		{
			using stack_type = engine::T_stack<gindex_type, sizeof...(Ts)>;

			stack_type s;
			(s.push(vs), ...);

			return s;
		}

	// print:

		template<typename Stack>
		constexpr void print_stack(const Stack & s)
		{
			for (auto k = s.cbegin(); k != s.cend(); k += 2) printf("%hu, ", *k);

			printf("\n");
		}

	// pop print:

		template<typename Stack>
		constexpr void pop_print_stack(Stack & s)
		{
			while (s.not_empty()) printf("%hu, ", s.pop());

			printf("\n");
		}

	// test:

		constexpr auto s0 = push_stack(1, 2, 3, 4, 5);
		          auto s1 = s0;

		print_stack(s0);
		pop_print_stack(s1);

/***********************************************************************************************************************/

// env:

	// string, value:

	template<typename StrLitType>
	struct test_model_env_str_num
	{
		using strlit_type		= StrLitType;
		using env_type			= engine::model_environment_string_number
						<
							char, gindex_type, gindex_type, 6, 21
						>;

		constexpr static auto word0	= strlit_type{ "hi"    };
		constexpr static auto word1	= strlit_type{ "there" };
		constexpr static auto word2	= strlit_type{ "how"   };
		constexpr static auto word3	= strlit_type{ "are"   };
		constexpr static auto word4	= strlit_type{ "you"   };
		constexpr static auto word5	= strlit_type{ "there" };

		env_type env;

		constexpr test_model_env_str_num()
		{
			env.push_binding(word0.cbegin(), word0.cend(), 1); // hi
			env.push_binding(word1.cbegin(), word1.cend(), 2); // there
			env.push_binding(word2.cbegin(), word2.cend(), 3); // how
			env.push_binding(word3.cbegin(), word3.cend(), 4); // are
			env.push_binding(word4.cbegin(), word4.cend(), 5); // you
			env.push_binding(word5.cbegin(), word5.cend(), 6); // there
		}
	};

		using strlit_type = engine::string_literal<const char, gindex_type>;

		constexpr auto test0  = test_model_env_str_num<strlit_type>{};
		constexpr auto record = test0.env.find_value(strlit_type{"there"}.cbegin());

		printf("%s\n", record.is_empty() ? "empty" : "not empty");
		printf("%hu\n", *record);
		printf("%hu\n", test0.env.get_value(record));

