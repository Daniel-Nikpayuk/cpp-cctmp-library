/************************************************************************************************************************
**
** Copyright 2022 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// case studies:

namespace cctmp_case_studies
{

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// insert sort:

/***********************************************************************************************************************/

namespace cctmp_program
{
// version 0:

	template<auto insert, auto cmp, auto... Vs>
	constexpr auto sort(nik_vp(l)(T_pack_Vs<Vs...>*))
	{
		constexpr auto d		= MachineDispatch::initial_depth;
		constexpr auto list		= U_restore_T<decltype(l)>;
		constexpr auto n		= OL::template result<OL::find, cmp, list, insert>;

						// bad design: does not compose well with trampolining.
		constexpr auto sp		= NIK_FUNCTION_BLOCK(9, d, n, BN::split, Vs)(U_null_Vs);

		return OL::template result<OL::unite, sp.v1, sp.v2, insert>;
	}

	template<auto cmp = less_than_op<>>
	struct T_InsertSort_v0
	{
		template<auto list, auto insert>
		nik_ces auto result = sort<insert, cmp>(list);
	};

	template<auto cmp = less_than_op<>>
	constexpr auto U_InsertSort_v0 = U_store_T<T_InsertSort_v0<cmp>>;

	template<auto list, auto insert, auto cmp = less_than_op<>>
	constexpr auto insert_sort_v0 = T_InsertSort_v0<cmp>::template result<list, insert>;
}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sort:

/***********************************************************************************************************************/

namespace cctmp_program
{
// version 0:

	// less rigorous (l has a max length), but is fast!

	template
	<
		auto l,
		auto cmp	= less_than_op<>,
		auto d		= MachineDispatch::initial_depth
	>
	constexpr auto sort_v0 = Fold_v0::template result
	<
		d,
		alias_op<U_InsertSort_v0<cmp>>,
		U_null_Vs,
		l
	>;

// version 1:

	// A bit more rigorous, but almost twice as slow as v0.

	template
	<
		auto l,
		auto cmp	= less_than_op<>,
		auto d		= MachineDispatch::initial_depth
	>
	constexpr auto sort_v1 = Fold_v0::template result
	<
		d,
		alias_op<U_InsertSort_v1<cmp>, d>,
		U_null_Vs,
		l
	>;
}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// factorial:

	//	printf("%llu\n", cctmp_program::factorial_v0<uint_type{20}>);
	//	printf("%llu\n", cctmp_program::factorial_v1<uint_type{20}>);

/***********************************************************************************************************************/

namespace cctmp_program
{
// version 0:

	struct Factorial_v0
	{
		template
		<
			// registers:

			key_type n		=  0,
			key_type p		=  1,

			// labels:

			key_type exit_case	= 13
		>
		nik_ces contr_type program = controller
		<
			copy      < n , _register >,
			is_zero   <               >,
			branch    <     exit_case >,

			copy      < n , _register >,
			copy      < p , _register >,
			multiply  <               >,
			cut       < p , _register >,
			paste     <     _register >,

			copy      < n , _register >,
			decrement <               >,
			cut       < n , _register >,
			paste     <     _register >,

			cycle     <               >,

			// exit_case:

			value     < p , _register >
		>;

		template<auto d, auto n>
		nik_ces auto result = start<d, program<>, n, decltype(n){_one}>(U_null_Vs);
	};

	template<auto n, auto d = MachineDispatch::initial_depth>
	constexpr auto factorial_v0 = Factorial_v0::template result<d, n>;

// version 1:

	struct Factorial_v1
	{
		template
		<
			// registers:

			key_type n			=  0,
			key_type m			=  1,

			// constants:

			key_type one			=  0,
			key_type factorial		=  1,

			// labels:

			key_type exit_case		=  9
		>
		nik_ces contr_type program = controller
		<
			copy     < n         , _register >,
			is_zero  <                       >,
			branch   <             exit_case >,

			copy     < factorial , _constant >,
			copy     < m         , _register >,
			compel   <                       >,

			copy     < n         , _register >,
			lift     <                       >,
			multiply <             _value    >,

			// exit_case:

			value    < one       , _constant >
		>;

		template<auto d, auto n>
		nik_ces auto result = start<d, program<>, n, n-1>
		(
			U_pack_Vs
			<
				decltype(n){_one},
				U_store_T<Factorial_v1>
			>
		);
	};

	template<auto n, auto d = MachineDispatch::initial_depth>
	constexpr auto factorial_v1 = Factorial_v1::template result<d, n>;

// version 2:

	struct Factorial_v2
	{
		nik_ces char source[] =

			" param: n p                        ;"
			" const: is_zero multiply decrement ;"
			"   arg:                            ;"

			" start:                            ;"
			"   if (is_zero n) then stop        ;"
			"   p = multiply n p                ;"
			"   n = decrement n                 ;"
			"   goto start:                     ;"

			" stop:                             ;"
			"   return p                        ;"
		;

	//	template<typename T> nik_ces bool is_zero(T n) { return (n == 0); }
	//	template<typename T> nik_ces T multiply(T m, T n) { return m*n; }
	//	template<typename T> nik_ces T decrement(T n) { return n-1; }

	//	template<auto d, auto n>
	//	nik_ces auto result = start<d, program<>, n, decltype(n){_one}>
	//	(
	//		U_pack_Vs
	//		<
	//			is_zero<decltype(n)>,
	//			multiply<decltype(n)>,
	//			decrement<decltype(n)>
	//		>
	//	);
	};

//	template<auto n, auto d = MachineDispatch::initial_depth>
//	constexpr auto factorial_v2 = Factorial_v2::template result<d, n>;
}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fibonacci:

	//	printf("%llu\n", cctmp_program::fibonacci_v0<uint_type{43}>);	// gcc 1.767s / clang 5.641s
	//	printf("%llu\n", cctmp_program::fibonacci_v1<uint_type{43}>);	// gcc 0.599s / clang 1.300s

	//	printf("%llu\n", cctmp_program::fibonacci_v0<uint_type{70}>);	// gcc > 10m / clang ~ who knows (4x 10m)
	//	printf("%llu\n", cctmp_program::fibonacci_v1<uint_type{92}>);	// gcc 1.462s / clang 3.492s

/***********************************************************************************************************************/

namespace cctmp_program
{
// version 0:

	struct Fibonacci_v0
	{
		template
		<
			// registers:

			key_type n			=  0,
			key_type n1			=  1,
			key_type n2			=  2,

			// constants:

			key_type one			=  0,
			key_type fibonacci		=  1,
			key_type is_0_or_1		=  2,

			// labels:

			key_type exit_case		= 12
		>
		nik_ces contr_type program = controller
		<
			copy   < is_0_or_1 , _constant >,
			copy   < n         , _register >,
			apply  <                       >,
			branch <             exit_case >,

			copy   < fibonacci , _constant >,
			copy   < n2        , _register >,
			compel <                       >,

			copy   < fibonacci , _constant >,
			copy   < n1        , _register >,
			compel <                       >,

			lift   <                       >,
			add    <             _value    >,

			// exit_case:

			value  < one       , _constant >
		>;

		template<typename T> nik_ces bool is_0_or_1(T n) { return (n == 0) || (n == 1); }

		template<auto d, auto n>
		nik_ces auto result = start<d, program<>, n, n-1, n-2>
		(
			U_pack_Vs
			<
				decltype(n){_one},
				U_store_T<Fibonacci_v0>,
				is_0_or_1<decltype(n)>
			>
		);
	};

	template<auto n, auto d = MachineDispatch::initial_depth>
	constexpr auto fibonacci_v0 = Fibonacci_v0::template result<d, n>;

// version 1:

	struct MemFib_v0
	{
		template
		<
			// registers:

			key_type n			=  0,
			key_type n1			=  1,
			key_type n2			=  2,

			// constants:

			key_type mem_fib		=  0,

			// arguments:

			key_type mem_table		=  0,

			// labels:

			key_type found_case		= 17
		>
		nik_ces contr_type program = controller
		<
			mem_lookup <               found_case >,

			copy       < mem_fib     , _constant  >,
			copy       < n2          , _register  >,
			copy       < mem_table   , _argument  >,
			compel     <               _h1_pair   >,
			cut        < mem_table   , _argument  >,
			paste      <               _argument  >,

			copy       < mem_fib     , _constant  >,
			copy       < n1          , _register  >,
			copy       < mem_table   , _argument  >,
			compel     <               _h1_pair   >,
			cut        < mem_table   , _argument  >,
			paste      <               _argument  >,

			lift       <                          >,
			add        <                          >,

			copy       < n           , _register  >,
			mem_insert <                          >,

			// found_case:

			variable   <               BN::lookup >,
			copy       < mem_table   , _argument  >,
			copy       < _zero       , _junction  >,
			product    <                   _value >
		>;

		nik_ces auto m = MT::id;
		nik_ces auto c = program<>;
		nik_ces auto i = MachineDispatch::initial_index;
		nik_ces auto f = U_store_T<MemFib_v0>;

		template<typename IntType>
		nik_ces auto t = U_pack_Vs
		<
			U_pack_Vs<IntType{1}, IntType{1}>,
			U_pack_Vs<IntType{0}, IntType{1}>
		>;

		template<auto d, auto n, auto mem_table = t<decltype(n)>>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i),

			n, n-1, n-2

		NIK_END_MACHINE
		(
			U_pack_Vs<n>, U_null_Vs,
			U_pack_Vs<f>, mem_table
		);
	};

	template<auto n, auto d = MachineDispatch::initial_depth>
	constexpr auto fibonacci_v1 = MemFib_v0::template result<d, n>.v2;
}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// non-recursive:

/***********************************************************************************************************************/

	template
	<
		index_type x = 0,
		index_type y = 1,
		index_type z = 2
	>
	nik_ce auto non_recursive_algo = endodrop
	<
		signature<int, int, int>,

		lift < z    , _constant_<2>            >,
		lift < y    , _multiply_    , z    , y >,
		lift < _cp_ , _multiply_    , x    , x >,
		lift < _cp_ , _add_         , _ps_ , y >,

		_return_
	>;

	nik_ce int x_squared_plus_two_y(int x, int y) { return non_recursive_algo<>(x, y, 0); }

/***********************************************************************************************************************/

// tacit:

	// square:

		struct T_square
		{
			template<typename T>
			nik_ces auto result(T v) { return v * v; }

		}; nik_ce auto _square_ = U_store_T<T_square>;

	// twice:

		struct T_twice
		{
			template<typename T>
			nik_ces auto result(T v) { return 2 * v; }

		}; nik_ce auto _twice_ = U_store_T<T_twice>;

	// f(x) = 2x^2+1 :

		nik_ce auto tacit_algo = endodrop
		<
			signature<float>,

			tacit < _square_      >,
			tacit < _twice_       >,
			tacit < _increment_<> >,

			_return_
		>;

		nik_ce float two_x_squared_plus_one(float x) { return tacit_algo(x); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (pair) factorial:

/***********************************************************************************************************************/

// version 0 (baseline):

	nik_ce u_type pair_factorial_v0(u_type n, u_type p)
	{
		if (n == 0) return p;
		else        return pair_factorial_v0(n-1, p*n);
	}

	nik_ce u_type factorial_v0(u_type n) { return pair_factorial_v0(n, 1); }

	// gcc -O3 / clang -O2:
	// bytes: 15768 / 15856
	// lines: 39 / 39

//	printf("%llu\n", cpp_cctmp_library_case_studies::factorial_v0(argc));

/***********************************************************************************************************************/

// version 1:

	struct T_factorial
	{
		nik_ces auto start	= 0;
		nik_ces auto done	= 1;

		nik_ces auto n		= 0;
		nik_ces auto p		= 1;

		nik_ces auto object = parse
		<
			label<start>,

				test   < _is_zero_ , n             >,
				branch < done                      >,

				lift   < p , _multiply_    , n , p >,
				lift   < n , _decrement_<> , n     >,

				go_to  < start                     >,

			label<done>,

				_value_<p>
		>;

		template<typename IntType>
		nik_ces auto result(IntType n)
		{
			return call<object, IntType>(n, IntType{1});
		}

	}; nik_ce auto _factorial_ = U_store_T<T_factorial>;

	nik_ce u_type factorial_v1(const u_type n) { return T_factorial::template result(n); }

	// gcc -O3 / clang -O2:
	// bytes: 16928 / 16048
	// lines: 103 / 99

//	printf("%llu\n", cpp_cctmp_library_case_studies::factorial_v1(argc));

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// weird factorial:

/***********************************************************************************************************************/

/*
	struct T_greater_than_24
	{
		template<typename T>
		nik_ces bool result(T v) { return (v > 24); }

	}; nik_ce auto _greater_than_24_ = U_store_T<T_greater_than_24>;

	struct WeirdFactorial
	{
		nik_ces u_type start (u_type n, u_type p) { return link<start, object>(n, p); }
		nik_ces u_type after (u_type n, u_type p) { return link<after, object>(n, p); }
		nik_ces u_type done  (u_type n, u_type p) { return link<done, object>(n, p); }

		nik_ces auto n = 0;
		nik_ces auto p = 1;

		nik_ces auto object = compile
		<
			label<start>,

				test   < _is_zero_ , n             >,
				branch < after                     >,

				lift   < p , _multiply_    , n , p >,
				lift   < n , _decrement_<> , n     >,

				go_to  < start                     >,

			label<after>,

				test   < _greater_than_24_     , p >,
				branch < done                      >,

				lift   < p , _multiply_    , p , p >,
				lift   < p , _decrement_<> , p     >,

				go_to  < start                     >,

			label<done>,

				_value_<p>
		>;
	};

	nik_ce u_type weird_factorial(u_type n) { return WeirdFactorial::start(n, 1); }
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// debugging:

/***********************************************************************************************************************/

/*
	template<auto word, auto... words>
	nik_ce auto explore_words()
	{
		printf("%d, ", word);

		if nik_ce (sizeof...(words) > 0) explore_words<words...>();
	}

	template<auto... words>
	nik_ce auto explore_line(nik_avp(T_pack_Vs<words...>*))
	{
		printf("%d: ", int{sizeof...(words)});

		printf("\n");
	//	explore_words<words...>();
	}

	template<auto line, auto... lines>
	nik_ce auto explore_lines()
	{
		explore_line(line);

		if nik_ce (sizeof...(lines) > 0) explore_lines<lines...>();
	}

	template<auto deps, auto... lines>
	nik_ce auto explore(nik_avp(T_pack_Vs<deps, lines...>*))
	{
		// deps:

			nik_ce auto dsize = deps[0][0] + 1;

			for (auto k = deps + 1; k != deps + dsize; ++k)
			{
				auto vertex = *k;
				auto vsize  = vertex[0] + 1;

				printf("%d: ", *vertex);

				for (auto j = vertex + 1; j != vertex + vsize; ++j) printf("%d, ", *j);

				printf("\n");
			}

		// lines:

			printf("\n");

			explore_lines<lines...>();
	}
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// comparison:

/***********************************************************************************************************************/

// order:

	nik_ce auto tag_order = U_pack_Vs
	<
		// label:

			U_store_B < _precycle_label        >,
			U_store_B < _cycle_label           >,
			U_store_B < _postcycle_label       >,

		// position:

			U_store_B < _out_position          >,
			U_store_B < _in_position           >,
			U_store_B < _car_in_position       >,
			U_store_B < _cdr_in_position       >,
			U_store_B < _end_position          >,

		// out:

			U_store_B < _pre_out_next          >,
			U_store_B < _out_next              >,
			U_store_B < _post_out_next         >,

		// in:

			U_store_B < _pre_in_next           >,
			U_store_B < _in_next               >,
			U_store_B < _post_in_next          >,

		// car in:

			U_store_B < _pre_car_in_next       >,
			U_store_B < _car_in_next           >,
			U_store_B < _post_car_in_next      >,

		// cdr in:

			U_store_B < _pre_cdr_in_next       >,
			U_store_B < _cdr_in_next           >,
			U_store_B < _post_cdr_in_next      >,

		// end:

			U_store_B < _pre_end_prev          >,
			U_store_B < _end_prev              >,

			U_store_B < _end_next              >,
			U_store_B < _post_end_next         >,

		// loop:

			U_store_B < _loop_predicate        >,

		// value:

			U_store_B < _value_predicate       >,

		// act:

			U_store_B < _act_predicate         >,
			U_store_B < _act_function          >,
			U_store_B < _post_act_function     >,

		// combine:

			U_store_B < _combine_function      >,
			U_store_B < _post_combine_function >
	>;

/***********************************************************************************************************************/

// compare:

	struct T_tag_compare
	{
		template<auto d, auto Op, auto V0, auto V1>
		nik_ces auto result = list_compare
		<
			tag_order, Op,
			alias<AOP::template_id, V0>,
			alias<AOP::template_id, V1>,
			H_partial_same, d
		>;

	}; nik_ce auto U_tag_compare = U_store_T<T_tag_compare>;

	template<auto Op, auto V0, auto V1, auto d = MD::initial_depth>
	nik_ce auto tag_compare = T_tag_compare::template result<d, Op, V0, V1>;

/***********************************************************************************************************************/

// dump:

	//	printf("%s\n", call<Overload::same, U_char, U_char> ? "true" : "false");
	//	printf("%llu\n", call<Overload::map, cctmp::template increment_op<>, p>);
	//	printf("%hu\n", call<Overload::find, cctmp::template is_zero_op<>, p>);

	//	printf("%d\n",   cctmp_functional::pack_at<0, 3, 4, 5, 9>);
	//	printf("%d\n",   cctmp_functional::list_at<p, 0>);
	//	printf("%llu\n", cctmp_functional::pack_left<0, 3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_functional::list_left<p, 0>);
	//	printf("%llu\n", cctmp_functional::pack_right<0, 3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_functional::list_right<p, 0>);

	//	constexpr auto p_cut = cctmp_functional::pack_cut<0, 3, 4, 5, 9>;
	//	printf("%llu, %llu\n", tuple_value<0>(p_cut), tuple_value<1>(p_cut));
	//	constexpr auto l_cut = cctmp_functional::list_cut<p, 3>;
	//	printf("%llu, %llu\n", tuple_value<0>(l_cut), tuple_value<1>(l_cut));

	//	constexpr auto p_split = cctmp_functional::pack_split<0, 3, 4, 5, 9>;
	//	printf("%llu, %llu\n", tuple_value<0>(p_split), tuple_value<1>(p_split));
	//	constexpr auto l_split = cctmp_functional::list_split<p, 4>;
	//	printf("%llu, %llu\n", tuple_value<0>(l_split), tuple_value<1>(l_split));

	//	printf("%llu\n", cctmp_functional::segment<unsigned{10}>);

	//	printf("%d\n", cctmp_functional::pack_fold<_add_, 0, 3, 4, 5, 9>);
	//	printf("%d\n", cctmp_functional::list_fold<p, _add_, 0>);

	//	printf("%llu\n", cctmp_functional::pack_erase<0, 3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_functional::list_erase<p, 0>);
	//	printf("%llu\n", cctmp_functional::pack_insert<0, 7,    3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_functional::list_insert<p, 0, 7>);
	//	printf("%llu\n", cctmp_functional::pack_replace<1, 7,    3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_functional::list_replace<p, 1, 7>);

	//	constexpr auto H_curry_equal		= H_curry<_equal_>;
	//	constexpr auto H_curry_less_than	= H_curry<_less_than_>;

	//	printf("%llu\n", cctmp_functional::pack_insert_sort<H_curry_less_than, 0,    3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_functional::list_insert_sort<p, 0>);

	//	printf("%llu\n", cctmp_functional::pack_sort<H_curry_less_than, U_null_Vs, 3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_functional::list_sort<p>);		// gcc 2.489s / clang 7.010s

	//	printf("%llu\n", cctmp_functional::pack_union<H_curry_equal, H_curry_less_than, U_null_Vs, 9,    3, 4, 5, 9>);

	//	constexpr auto def_specs	= U_pack_Vs<0, 1, 2, 3, 4, 5>;
	//	constexpr auto specs0		= U_pack_Vs<3, 5, 0>;
	//	printf("%llu\n", cctmp_functional::list_fill<def_specs, specs0>);

	//	constexpr auto p0  = cctmp_one_cycle_specs::direct_repeat_defaults;
	//	constexpr auto cmp = H_partial<U_custom, cctmp_one_cycle_specs::U_tag_compare, MD::initial_depth, _less_than_>;
	//	constexpr auto p  = cctmp_functional::list_sort<p0, cmp>;
	//	printf("%llu\n", p);

	//	constexpr auto tag0 = _pre_out_next_<_id_>;
	//	constexpr auto tag1 = _post_out_next_<_id_>;
	//	printf("%s\n", tag_compare<cctmp::_less_than_, tag1, tag0> ? "true" : "false");

/***********************************************************************************************************************/

// brainstorming:

//	auto val = repeat<"(out+, end]; out == end; *out = in">(out, end, in);
//	auto val = map<"[out+]; (in+, end+]; in == end; *out = *in">(out, in, end);

		// How to read this:

		// Map over two iterators "out" and "in", both unidirectional forward,
		// until "in" equals "end". The map action is an assignment taken by
		// dereferencing both "out" and "in" (assigning to "out"). Furthermore,
		// "in" is an *opening* interval "(]", meaning "in" increments once, then
		// the map action is applied iteratively until "end" is reached. The map action
		// is further applied to the "end" location itself. Beyond this, "out" is a *closed*
		// interval "[]", meaning the map action is applied to the initial "out" location,
		// applied iteratively, then applied to the last "out" location. Finally, "end" is
		// also unidirectional forward. This is relevant for some interval combinations of
		// "out/in" intervals where you alternatively need to either peek ahead from "in" or
		// you can simply decrement "end" temporarily, returning it once the loop is finished.

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// direct interpretation tests:

/***********************************************************************************************************************/

// functions:

/*
	constexpr int sq(int x)			{ return x*x; }
	constexpr auto _sq_			= cctmp::template _apply_<sq>;

	constexpr int mod_add(int x, int y)	{ return (x+y) % 10; }
	constexpr auto _mod_add_		= cctmp::template _apply_<mod_add>;

	constexpr int carry0_add_ddd(int *o, int *i1, int *i2) { return (*o < *i1); }
	constexpr int carry1_add_dii(int *o, int i, bool a) { return a || (i == 1 && *o == 0); }

	constexpr auto _carry0_add_ddd_		= cctmp::template _apply_<carry0_add_ddd>;
	constexpr auto _carry1_add_dii_		= cctmp::template _apply_<carry1_add_dii>;

	constexpr auto _id_			= cctmp::_id_;
	constexpr auto _add_			= cctmp::_add_;
	constexpr auto _is_25_			= cctmp::template _is_equal_<25>;
	constexpr auto _assign_			= cctmp::_assign_;
	constexpr auto _deref_			= cctmp::_dereference_;

	constexpr auto _add_dd_			= cctmp_generics::template _argcompose_<_add_, _deref_, _deref_>;
	constexpr auto _is_25_d_		= cctmp_generics::template _argcompose_<_is_25_, _deref_>;
	constexpr auto _mod_add_di_		= cctmp_generics::template _argcompose_<_mod_add_, _deref_, _id_>;
	constexpr auto _mod_add_dd_		= cctmp_generics::template _argcompose_<_mod_add_, _deref_, _deref_>;

	constexpr auto _d_assign_i_		= cctmp_generics::template _argcompose_<_assign_, _deref_, _id_>;
	constexpr auto _d_assign_sq_		= cctmp_generics::template _argcompose_<_assign_, _deref_, _sq_>;
	constexpr auto _d_assign_add_		= cctmp_generics::template _subcompose_
						<
							_assign_,

							U_pack_Vs < _deref_ , _add_           >,
							U_pack_Vs < 0       , U_pack_Vs<1, 2> >
						>;
	constexpr auto _d_assign_add_dd_	= cctmp_generics::template _argcompose_
						<
							_d_assign_add_, _id_, _deref_, _deref_
						>;
*/

/***********************************************************************************************************************/

/*
// repeat:

	constexpr auto repeat_dspec		= cctmp_one_cycle_specs::template direct_repeat<>;
	using T_repeat				= typename cctmp_one_cycle_generics::template T_repeat<repeat_dspec>;

// map:

	constexpr auto map_dspec_id_		= cctmp_one_cycle_specs::template direct_map<>;
	using T_map_id				= typename cctmp_one_cycle_generics::template T_map<map_dspec_id_>;

	constexpr auto _map_function_sq_	= cctmp_one_cycle_specs::template _assign_function_<_d_assign_sq_>;
	constexpr auto map_dspec_sq_		= cctmp_one_cycle_specs::template direct_map<_map_function_sq_>;
	using T_map_sq				= typename cctmp_one_cycle_generics::template T_map<map_dspec_sq_>;

// fold:

	constexpr auto _fold_function_add_	= cctmp_one_cycle_specs::template _combine_function_<_add_>;

	constexpr auto fold_dspec_add_		= cctmp_one_cycle_specs::template direct_fold<_fold_function_add_>;
	using T_fold_add			= typename cctmp_one_cycle_generics::template T_fold<fold_dspec_add_>;

// find first:

	constexpr auto _find_first_pred_is_25_	= cctmp_one_cycle_specs::template _act_predicate_<_is_25_d_>;
	constexpr auto find_first_dspec_is_25_	= cctmp_one_cycle_specs::template direct_find_first<_find_first_pred_is_25_>;
	using T_find_first_is_25		= typename cctmp_one_cycle_generics::template T_find_first<find_first_dspec_is_25_>;

// find all:

	constexpr auto find_all_dspec_is_25_	= cctmp_one_cycle_specs::template direct_find_all<_find_first_pred_is_25_>;
	using T_find_all_is_25			= typename cctmp_one_cycle_generics::template T_find_all<find_all_dspec_is_25_>;

// zip:

	constexpr auto _zip_function_add_	= cctmp_one_cycle_specs::template _act_function_<_add_dd_>;
	constexpr auto _zip_assign_		= cctmp_one_cycle_specs::template _assign_function_<_d_assign_i_>;
	constexpr auto zip_dspec_add_		= cctmp_one_cycle_specs::template direct_zip
						<
							_zip_function_add_, _zip_assign_
						>;
	using T_zip_add				= typename cctmp_one_cycle_generics::template T_zip<zip_dspec_add_>;

// fasten:

	constexpr auto _fasten_function_add_	= cctmp_one_cycle_specs::template _act_function_<_mod_add_dd_>;
	constexpr auto _fasten_combine_add_	= cctmp_one_cycle_specs::template _combine_function_<_mod_add_di_>;
	constexpr auto _fasten_aux_next_	= cctmp_one_cycle_specs::template _aux_next_<_carry0_add_ddd_>;
	constexpr auto _fasten_in_next_		= cctmp_one_cycle_specs::template _in_next_<_carry1_add_dii_>;
	constexpr auto fasten_dspec_add_	= cctmp_one_cycle_specs::template direct_fasten
						<
							_fasten_function_add_, _fasten_combine_add_,
							_fasten_aux_next_, _fasten_in_next_
						>;
	using T_fasten_mod_add			= typename cctmp_one_cycle_generics::template T_fasten<fasten_dspec_add_>;

// glide:

	constexpr auto _glide_function_add_	= cctmp_one_cycle_specs::template _act_function_<_add_dd_>;
	constexpr auto _glide_combine_add_	= cctmp_one_cycle_specs::template _combine_function_<_add_>;
	constexpr auto glide_dspec_add_		= cctmp_one_cycle_specs::template direct_glide
						<
							_glide_function_add_, _glide_combine_add_
						>;
	using T_glide_add			= typename cctmp_one_cycle_generics::template T_glide<glide_dspec_add_>;
*/

/***********************************************************************************************************************/

// tests:

	//	int size = 10;//argc;

	//	int  arr[size];
	//	int  arr_id[size];
	//	int  arr_sq[size];
	//	int* arr_ptr[size];

// repeat:

	//	repeat_array(arr, arr+size, argc);
	//	T_repeat::result(arr, arr+size, argc);
	//	print_array(arr, arr+size);

// map:

	//	T_map_id::template result(arr_id, 0, size);
	//	print_array(arr_id, arr_id+size);

	//	T_map_sq::template result(arr_sq, 0, size);
	//	print_array(arr_sq, arr_sq+size);

// fold:

	//	auto val = T_fold_add::template result(0, 0, size);
	//	printf("%d\n", val);

// find first:

	//	T_map_sq::template result(arr_sq, 0, size);

	//	auto val = T_find_first_is_25::template result(arr_ptr, arr_sq, arr_sq+size);
	//	printf("%ld\n", val - arr_ptr);
	//	printf("%ld\n", *arr_ptr - arr_sq);

// find all:

	//	T_map_sq::template result(arr_sq, 0, size);
	//	arr_sq[3] = 25;
	//	arr_sq[8] = 25;

	//	auto val = T_find_all_is_25::template result(arr_ptr, arr_sq, arr_sq+size);
	//	printf("%ld\n", val - arr_ptr);
	//	printf("%ld\n", arr_ptr[0] - arr_sq);
	//	printf("%ld\n", arr_ptr[1] - arr_sq);
	//	printf("%ld\n", arr_ptr[2] - arr_sq);

// zip:

	//	T_map_id::template result(arr_id, 0, size);
	//	T_map_sq::template result(arr_sq, 0, size);

	//	T_zip_add::template result(arr, arr_id, arr_sq, arr_sq+size);
	//	print_array(arr, arr+size);

// fasten:

	//	int mod_size = 3;
	//	int arr_mod_add[mod_size];
	//	int arr_134[] = { 4, 3, 1 };
	//	int arr_379[] = { 9, 7, 3 };

	//	T_fasten_mod_add::template result(arr_mod_add, 0, 0, arr_134, arr_379, arr_379+mod_size);
	//	printf("%d%d%d\n", arr_mod_add[2], arr_mod_add[1], arr_mod_add[0]);

// glide:

	//	T_map_id::template result(arr_id, 0, size);
	//	T_map_sq::template result(arr_sq, 0, size);

	//	auto val = T_glide_add::template result(0, arr_id, arr_sq, arr_sq+size);
	//	printf("%d\n", val);

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // case studies

