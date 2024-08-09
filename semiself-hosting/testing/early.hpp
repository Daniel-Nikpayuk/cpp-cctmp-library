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

// rvalue reference:

	template<auto N>
	constexpr auto replace_then_add(int (&&arr)[N], int pos, int val)
	{
		int sum = 0;

		arr[pos] = val;

		for (auto k = arr; k != arr + N; ++k) sum += *k;

		return sum;
	}

		printf("%d\n", replace_then_add({1, 2, 3, 4, 5}, 0, 10));

/***********************************************************************************************************************/

// array literal:

	struct contr
	{
		using lit_type = array_literal<int, gindex_type>;

		constexpr static int arr[] =
		{
			2, 7, 3, 4, 9, 5,
			1, 9, 3, 8, 7, 0,
			2, 2, 3, 3, 4, 5
		};

		constexpr static auto x = lit_type{arr};
	};

		printf("%d\n", contr::x[ 1]);
		printf("%d\n", contr::x[ 7]);
		printf("%d\n", contr::x[13]);

/***********************************************************************************************************************/

// array:

		using seq_type = array<int, gindex_type, 5>;

	// rvalue:

		constexpr auto s0 = seq_type{{1, 2, 3, 4, 5}};

	// lvalue:

		constexpr int l0[] = {1, 2, 3, 4, 5};

		seq_type s1{l0};

	// mutable:

		s1[4] = 6;
		s1.downsize();
		s1.push(5);

	// print:

		printf("%d\n", s0.size());

		printf("%s\n", (s0 == s1) ? "equal" : "not equal");

		printf("%d\n", s0.origin()[3]);
		printf("%d\n", s0.size());
		printf("%d\n", s0[0]);
		printf("%d\n", s0[1]);
		printf("%d\n", s0[2]);
		printf("%d\n", s0[3]);
		printf("%d\n", s0[4]);

/***********************************************************************************************************************/

// table literal:

	struct contr
	{
		using lit_type = table_literal<int, gindex_type, 3, 6>;

		constexpr static int arr[] =
		{
			2, 7, 3, 4, 9, 5,
			1, 9, 3, 8, 7, 0,
			2, 2, 3, 3, 4, 5
		};

		constexpr static auto x = lit_type{arr};
	};

		printf("%d\n", contr::x[0][1]);
		printf("%d\n", contr::x[1][1]);
		printf("%d\n", contr::x[2][1]);

/***********************************************************************************************************************/

// table:

		using table_type = table<int, gindex_type, 3, 6>;

		int arr[] =
		{
			2, 7, 3, 4, 9, 5,
			1, 9, 3, 8, 7, 0,
			2, 2, 3, 3, 4, 5
		};

		auto x = table_type{arr};

		x[1][1] = 5;

		printf("%d\n", x[0][1]);
		printf("%d\n", x[1][1]);
		printf("%d\n", x[2][1]);

/***********************************************************************************************************************/

// left:

		template<auto n>
		constexpr auto l0 = left_
		<
			n,

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

// different:

		constexpr auto s0 = array<int, gindex_type, 5>( {1, 2, 3, 4, 5} );
		constexpr auto s1 = array<int, gindex_type, 5>( {1, 2, 3, 4, 5} );

		auto val = inventory_different_v0<gindex_type>(s0.cbegin(), s0.cend(), s1.cbegin());
		printf("%s\n", val ? "different" : "same");

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

		constexpr auto f = engine::frame
		(
			U_gcchar_type, U_gindex_type,

			engine::gbinding("zero"  , 0),
			engine::gbinding("one"   , 1),
			engine::gbinding("two"   , 2),
			engine::gbinding("three" , 3),
			engine::gbinding("four"  , 4),
			engine::gbinding("five"  , 5)
		);

		printf("%s\n", engine::LambdaTuple::value<0>(f)[4].origin());
		printf("%d\n", engine::LambdaTuple::value<4>(engine::LambdaTuple::value<1>(f)));

/***********************************************************************************************************************/

// lookup:

		constexpr auto lookup0 = engine::lookup
		(
			U_gindex_type, U_auto_int, U_auto_int,

			engine::pair(0, 5),
			engine::pair(1, 4),
			engine::pair(2, 3),
			engine::pair(3, 2),
			engine::pair(4, 1),
			engine::pair(5, 0)
		);

		printf("left 0: %d\n", lookup0.lfind(0, 6));
		printf("left 1: %d\n", lookup0.lfind(1, 6));
		printf("left 2: %d\n", lookup0.lfind(2, 6));
		printf("left 3: %d\n", lookup0.lfind(3, 6));
		printf("left 4: %d\n", lookup0.lfind(4, 6));
		printf("left 5: %d\n", lookup0.lfind(5, 6));
		printf("left 6: %d\n", lookup0.lfind(6, 6));

		printf("right 0: %d\n", lookup0.rfind(0, 6));
		printf("right 1: %d\n", lookup0.rfind(1, 6));
		printf("right 2: %d\n", lookup0.rfind(2, 6));
		printf("right 3: %d\n", lookup0.rfind(3, 6));
		printf("right 4: %d\n", lookup0.rfind(4, 6));
		printf("right 5: %d\n", lookup0.rfind(5, 6));
		printf("right 6: %d\n", lookup0.rfind(6, 6));

/***********************************************************************************************************************/

// stack:

	// push:

		template<typename S, typename T, auto N>
		constexpr auto push_stack(const T (&a)[N])
		{
			using stack_type = engine::stack<T, S, N>;

			stack_type s;

			for (auto k = a; k != a + N; ++k) s.push(*k);

			return s;
		}

	// print:

		template<typename Stack>
		constexpr void print_stack(const Stack & s)
		{
			for (auto k = s.cbegin(); k != s.cend(); ++k) printf("%d, ", k->car);

			printf("\n");
		}

	// pop print:

		template<typename Stack>
		constexpr void pop_print_stack(Stack & s)
		{
			while (s.not_empty()) printf("%d, ", s.pop());

			printf("\n");
		}

	// test:

		constexpr auto s0 = push_stack<short>({1, 2, 3, 4, 5});
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

/***********************************************************************************************************************/

// lexer hustle:

		using size_type		= gindex_type;
		using lit_type		= engine::literal<size_type, size_type>;
		using strlit_type	= engine::string_literal<const char, size_type>;

		using lexer_table_type	= inventory::lexer_transition_table_hustle<size_type>;
		using lexer_state_type	= engine::lexer_state
					<
						typename lexer_table_type::State,
						typename lexer_table_type::Charset,
						const char*, size_type
					>;
		using lexer_token_type  = hustle::lexer_token<size_type>;
		using lexer_policy_type	= hustle::lexer_policy
					<
						typename lexer_table_type::State,
						typename lexer_table_type::Charset,
						typename lexer_token_type::Token,
						char, size_type
					>;

		constexpr auto table	= lit_type
					{
						lexer_table_type::value,
						lexer_table_type::value + lexer_table_type::seq.size()
					};
		constexpr auto strlit0	= strlit_type{"hi there everybody!"};

		auto lexer = lexer_state_type{table, strlit0.cbegin(), strlit0.cend()};

		while (lexer.not_end())
		{
			lexer.initialize();
			if (lexer.template find<lexer_policy_type>())
				for (auto k = lexer.cbegin(); k != lexer.ccurrent(); ++k)
					printf("%c", *k);

			printf("\n");
		}

/***********************************************************************************************************************/

// hustle keyword:

		using size_type          = gindex_type;
		using strlit_type        = engine::string_literal<char, size_type>;
		using lexer_token_type   = hustle::lexer_token<size_type>;
		using lexer_keyword_type = hustle::lexer_keyword<typename lexer_token_type::Token, char, size_type>;

		constexpr auto if_str    = strlit_type{"if"};

		printf("%d\n", lexer_keyword_type::eq_.match(if_str.cbegin(), if_str.cend()));

/***********************************************************************************************************************/

// hustle lexer:

		using lexer_trait	= hustle::lexer_trait<char, gindex_type>;
		using lexer_table_type	= inventory::lexer_transition_table_hustle<lexer_trait>;
		using lexer_type	= hustle::lexer<lexer_trait>;

		using lit_type		= typename lexer_type::lit_type;
		using strlit_type	= engine::string_literal<typename lexer_type::char_ctype, typename lexer_type::size_type>;

		constexpr auto table	= lit_type
					{
						lexer_table_type::value,
						lexer_table_type::value + lexer_table_type::seq.size()
					};
		constexpr auto strlit0	= strlit_type{"hi there everybody!"};

		auto lexer = lexer_type{table, strlit0.cbegin(), strlit0.cend()};

		while (lexer.not_end())
		{
			if (lexer.find())
				for (auto k = lexer.cbegin(); k != lexer.ccurrent(); ++k)
					printf("%c", *k);

			printf("\n");
		}

