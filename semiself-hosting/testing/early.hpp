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
/***********************************************************************************************************************/

// experimental:

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

	constexpr auto U_int_rref = U_store_T<int&&>;

	constexpr void test(T_store_U<U_int_rref>) { }

		printf("%d\n", test);

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

/***********************************************************************************************************************/

// array:

		using  arr_type =  array<int, gindex_type, 5>;
		using carr_type = carray<int, gindex_type>;

		constexpr int a[] = {1, 2, 3, 4, 5};

	// rvalue:

		constexpr auto a0 = carr_type{a};
		constexpr auto a1 =  arr_type{a};
		constexpr auto a2 =  arr_type{{1, 2, 3, 4, 5}};

	// lvalue:

		constexpr int l0[] = {1, 2, 3, 4, 5};

		arr_type a1{l0};

	// mutable:

		a1[4] = 6;
		a1.downsize();
		a1.push(5);

	// print:

		printf("%d\n", arr_type::length());
		printf("%d\n", a0.size());

		printf("%d\n", a1.size());
		printf("%sequal\n", (a0 == a2) ? "" : "not ");

		printf("%d\n", a0.origin()[3]);
		printf("%d\n", a0.size());
		printf("%d\n", a0[0]);
		printf("%d\n", a0[1]);
		printf("%d\n", a0[2]);
		printf("%d\n", a0[3]);
		printf("%d\n", a0[4]);

/***********************************************************************************************************************/

// unique array:

		using arr_type = unique_array<int, gindex_type, 5>;

		constexpr auto a0 = arr_type{{1, 2, 1, 3, 1}};

		printf("unique array size: %d\n", a0.size());

		printf("unique array: ");
		for (auto k = a0.cbegin(); k != a0.cend(); ++k) printf("%d, ", *k);
		printf("\n");

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

// tuple:

		using tuple_type = tuple<gindex_type, int, float, char>;

		auto tup = tuple_type{1, 2.0, 'c'};

		tup.template set_value<1>(3.0);

		printf("%d\n", tup.cvalue<0>());
		printf("%f\n", tup.cvalue<1>());
		printf("%c\n", tup.cvalue<2>());

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// inventory:

/***********************************************************************************************************************/

// different:

		constexpr auto s0 = array<int, gindex_type, 5>( {1, 2, 3, 4, 5} );
		constexpr auto s1 = array<int, gindex_type, 5>( {1, 2, 3, 4, 5} );

		auto val = inventory_different_v0<gindex_type>(s0.cbegin(), s0.cend(), s1.cbegin());
		printf("%s\n", val ? "different" : "same");

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// grammar test:

	struct entry
	{
		int x;
		int y;

		constexpr entry() : x{}, y{} { }

		template<typename T>
		constexpr entry(const T (&a)[2]) : x{a[0]}, y{a[1]} { }
	};

	struct plot
	{
		using array_type = array<entry, unsigned long, 3>;

		array_type arr;

		template<typename T>
		constexpr plot(const T (&a)[3]) : arr{a} { }
	};

	constexpr int arrlit0[][2] =
	{
		{ 0 , 1 },
		{ 2 , 3 },
		{ 4 , 5 }
	};

		plot p0{arrlit0};

		printf("%d\n", p0.arr[1].y);

/***********************************************************************************************************************/

// plot array:

	constexpr auto make_plot_array()
	{
		using size_type = gindex_type;
		using page_type = engine::plot_page_type<size_type>;

		using arr0_type = array<int, size_type, 5>;
		using arr1_type = array<page_type, size_type, 1>;

		using type_pack = T_pack_Ts<int, page_type>;
		using size_pack = T_pack_Vs<5, 1>;
		using plot_type = engine::plot<type_pack, size_pack, size_type>;

		auto a0 = arr0_type{{1, 2, 3, 4, 5}};
		auto a1 = arr1_type{{page_type{0, 5, 5}}};
		auto p  = plot_type{a0, a1};

		p.method().at(3) = 6; // {1, 2, 3, 6, 5}

		return p;
	}

	constexpr auto plot_array_0 = make_plot_array();

		auto method0 = plot_array_0.cmethod();

		for (auto k = method0.cbegin(); k != method0.cend(); ++k)
			printf("%d ", *k);

		printf("\n");

/***********************************************************************************************************************/

// plot matrix:

	constexpr auto make_plot_array()
	{
		using size_type = gindex_type;
		using page_type = engine::plot_page_type<size_type>;

		using arr0_type = array<int, size_type, 9>;
		using arr1_type = array<page_type, size_type, 3>;
		using arr2_type = array<page_type, size_type, 1>;

		using type_pack = T_pack_Ts<int, page_type, page_type>;
		using size_pack = T_pack_Vs<9, 3, 1>;
		using plot_type = engine::plot<type_pack, size_pack, size_type>;

		auto a0 = arr0_type{{1, 2, 3, 4, 5, 6, 7, 8, 9}};
		auto a1 = arr1_type{{page_type{0, 3, 3}, page_type{3, 3, 3}, page_type{6, 3, 3}}};
		auto a2 = arr2_type{{page_type{0, 3, 3}}};
		auto p  = plot_type{a0, a1, a2};

	//	p.method().at(3) = 6; // {1, 2, 3, 6, 5}

		return p;
	}

	constexpr auto plot_array_0 = make_plot_array();

		auto method0 = plot_array_0.cmethod();

		for (auto j = method0.cbegin(); j != method0.cend(); ++j)
		{
			for (auto k = j->cbegin(); k != j->cend(); ++k)
				printf("%d ", *k);

			printf("\n");
		}

/***********************************************************************************************************************/

// plot:

	using size_type = gindex_type;
	using text_type = int;
	using page_type = engine::plot_page_type<size_type>;
	using plot_type = engine::plot<text_type, page_type, size_type, 2, 2>;

	constexpr auto make_plot()
	{
		auto p = plot_type{};

		p.upsize();

		p.begin()->upsize();

		return p;
	}

	constexpr auto plot0 = make_plot();

		for (auto k = plot0.cbegin(); k != plot0.cend(); ++k)
			printf("%d ", k->size());

		printf("\n");

/***********************************************************************************************************************/

// plot literal:

		struct plot_lit0
		{
			using char_type		= char;
			using size_type		= unsigned;
			using entry_type	= engine::plot_entry<size_type>;
			using plotlit_type	= engine::plot_literal<entry_type, char_type, size_type>;

			constexpr static entry_type entry[] =
			{
				entry_type{ 0,  2},
				entry_type{ 2,  7},
				entry_type{ 7, 10},
				entry_type{10, 13},
				entry_type{13, 17}
			};

			constexpr static char_type value[] =
			{
				'h', 'i',
				't', 'h', 'e', 'r', 'e',
				'h', 'o', 'w',
				'a', 'r', 'e',
				'y', 'o', 'u', '?'
			};

			constexpr static auto strlist = plotlit_type{entry, value};
		};

		constexpr auto & strlist0 = plot_lit0::strlist;

		printf("%u\n", strlist0.size(0));
		printf("%u\n", strlist0.size(1));
		printf("%u\n", strlist0.size(2));
		printf("%u\n", strlist0.size(3));
		printf("%u\n", strlist0.size(4));

		for (auto k = 0; k != 5; ++k)
		{
			for (auto j = strlist0.cbegin(k); j != strlist0.cend(k); ++j)
			{
				printf("%c", *j);
			}

			printf("\n");
		}

/***********************************************************************************************************************/

// lambda tuple:

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

// ascii:

	// char:

		auto c0 = encoding::ascii_char<unsigned char, gindex_type>{'_'};
		auto c1 = encoding::ascii_char<unsigned char, gindex_type>{255};

		c0.validate();
		c1.validate();

		printf("c0 is %svalid\n", c0.is_valid() ? "" : "in");
		printf("c1 is %svalid\n", c1.is_valid() ? "" : "in");

	// string:

		using ascii_string_type = encoding::ascii_string<unsigned char, gindex_type, 20>;

		auto str0 = ascii_string_type{"abc" "d"    "ef"};
		auto str1 = ascii_string_type{"abc" "\xff" "ef"};

		str0.validate();
		str1.validate();

		printf("str0 is %svalid\n", str0.is_valid() ? "" : "in");
		printf("str1 is %svalid\n", str1.is_valid() ? "" : "in");

		for (auto k = 0; k != str0.size(); ++k) printf("%c", str0[k].value());
		printf("\n");

/***********************************************************************************************************************/

// unicode:

	// utf8 char:

		auto c0 = encoding::utf8_char<unsigned char, gindex_type>{' '};
		auto c1 = encoding::utf8_char<unsigned char, gindex_type>{255};

		c0.validate();
		c1.validate();

		printf("c0 is %svalid\n", c0.is_valid() ? "" : "in");
		printf("c1 is %svalid\n", c1.is_valid() ? "" : "in");

		printf("c0 is %swhitespace\n", c0.to_ascii().is_whitespace() ? "" : "not ");
		printf("c1 is %swhitespace\n", c1.to_ascii().is_whitespace() ? "" : "not ");

	// utf8 char array:

		using utf8_char_array_type = encoding::utf8_char_array<unsigned char, gindex_type, 20>;

		auto char_arr = utf8_char_array_type{"abcあde"};

		for (auto k = 0; k != char_arr.size(); ++k) printf("%s", char_arr[k].cstr_array().origin());
		printf("\n");

	// utf8 string:

		using utf8_string_type = encoding::utf8_string<unsigned char, gindex_type, 20>;

		auto str = utf8_string_type{"abcあde"};

		str.validate();

		printf("str is %svalid\n", str.is_valid() ? "" : "in");

		auto char_arr = str.char_array();

		for (auto k = 0; k != char_arr.size(); ++k) printf("%s", char_arr[k].cstr_array().origin());
		printf("\n");

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser generator:

/***********************************************************************************************************************/

// lexer:

	// keyword:

		using utf8_char_array_type = encoding::utf8_char_array<unsigned char, gindex_type, 20>;
		using lexer_trait_type     = parser::lexer_trait<utf8_char_array_type>;
		using lexer_keyword_type   = parser::lexer_keyword<lexer_trait_type>;

		constexpr auto char_arr    = utf8_char_array_type{"empty"};
		constexpr bool match0      = lexer_keyword_type::empty_short .match(char_arr.cbegin(), char_arr.cend());
		constexpr bool match1      = lexer_keyword_type::empty_long  .match(char_arr.cbegin(), char_arr.cend());

		printf("empty short is a %smatch\n" , match0 ? "" : "non");
		printf("empty long is a %smatch\n"  , match1 ? "" : "non");

/***********************************************************************************************************************/

// transition table:

	for (auto row = 0; row != parser::lltr_table::value.row_length(); ++row)
	{
		for (auto col = 0; col != parser::lltr_table::value.col_length(); ++col)
		{
			const bool is_valid = parser::lltr_table::value.not_none(row, col);

			printf(" ");
			printf("%d, ", is_valid);

			if (is_valid)
			{
				printf("%d, ", parser::lltr_table::value.cat(row, col).start    ());
				printf("%d, ", parser::lltr_table::value.cat(row, col).finish   ());
				printf("%d, ", parser::lltr_table::value.cat(row, col).action   ());
			}

			printf("\n");
		}

		printf("\n");
	}

/***********************************************************************************************************************/

// lexer:

	constexpr auto lexer_main()
	{
		using utf8_char_array_type = encoding::utf8_char_array<unsigned char, gindex_type, 50>;

		auto lexer = parser::make_lexer<utf8_char_array_type>("More of this please!");
		auto arr   = array<char, gindex_type, 100>{};

		while (lexer.not_end())
		{
			if (lexer.find())
			{
				for (auto k = lexer.cbegin(); k != lexer.ccurrent(); ++k)
				{
					auto cstr = k->cstr_array();

					arr.push(cstr.cbegin(), cstr.clast());
				}
			}

			arr.push(' ');
		}

		return arr;
	}

		constexpr auto lexed_array = lexer_main();

		for (auto k = lexed_array.cbegin(); k != lexed_array.cend(); ++k) { printf("%c", *k); }
		printf("\n");

/***********************************************************************************************************************/

// parser:

	// see diagnostic.hpp

	// diagnostic:

		parser_diagnostic();

	// main:

		constexpr auto parsed = parser_main();

		printf("nonterminal size: %d\n", parsed.ctree().cscript().cnonterminal().size());
		printf("symbol size: %d\n", parsed.ctree().cscript().csymbol().cpage().size());

