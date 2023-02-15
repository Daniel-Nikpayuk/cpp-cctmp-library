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

// at:

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		printf("%d\n", unpack_<p, _2_6_at_, 511>);

		// load:   gcc - 0.43s  /  clang - 1.16s

		// N = 3:  gcc - 0.57s  /  clang - 1.92s
		// N = 4:  gcc - 0.49s  /  clang - 1.56s
		// N = 5:  gcc - 0.45s  /  clang - 1.43s
		// N = 6:  gcc - 0.45s  /  clang - 1.33s
		// N = 7:  gcc - 0.46s  /  clang - 1.32s
		// N = 8:  gcc - 0.53s  /  clang - 1.37s
		// N = 9:  gcc - 0.62s  /  clang - 1.54s

		// adjusted:

		// N = 3:  gcc - 0.14s  /  clang - 0.76s
		// N = 4:  gcc - 0.06s  /  clang - 0.40s
		// N = 5:  gcc - 0.02s  /  clang - 0.27s
		// N = 6:  gcc - 0.02s  /  clang - 0.17s
		// N = 7:  gcc - 0.03s  /  clang - 0.16s
		// N = 8:  gcc - 0.10s  /  clang - 0.21s
		// N = 9:  gcc - 0.19s  /  clang - 0.38s

		printf("%d\n", unpack_<p, _2_6_erase_, 511>);

		// load:   gcc - 0.43s  /  clang - 1.16s

		// N = 3:  gcc - 0.76s  /  clang - 2.71s
		// N = 4:  gcc - 0.63s  /  clang - 1.93s
		// N = 5:  gcc - 0.51s  /  clang - 1.59s
		// N = 6:  gcc - 0.48s  /  clang - 1.41s
		// N = 7:  gcc - 0.50s  /  clang - 1.40s
		// N = 8:  gcc - 0.60s  /  clang - 1.43s
		// N = 9:  gcc - 0.73s  /  clang - 1.62s

		return 0;
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// mutate:

/***********************************************************************************************************************/

// tuple:

	template<typename... Ts>
	constexpr auto print_tuple(const tuple<Ts...> & t)
	{
		if constexpr (sizeof...(Ts) == 0) printf("\n");
		else
		{
			printf("%d, ", t.value);

			print_tuple(t.rest);
		}
	}

// unit:

	template<auto n, typename T, typename... Ts>
	constexpr auto unit_replace(T v, Ts... vs)
	{
		constexpr auto s = U_store_T<tuple<Ts...>>;

		return arg_replace<s, PT::_2_6, n, _to_tuple_>(v, vs...);
	}

/***********************************************************************************************************************/

// segment:

	template<auto n, auto... Vs>
	constexpr auto _segment()
	{
		if constexpr (n == 0) return U_pack_Vs<n, Vs...>;
		else                  return _segment<n-1, n, Vs...>();
	}

	template<auto n>
	constexpr auto segment = _segment<n>();

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

// united:

	// Not currently needed, keeping for possible later use.

/***********************************************************************************************************************/

// insert:

/*
	struct TP_united_insert
	{
		nik_ces key_type exit_case = 4;

		nik_ces auto c = controller
		<
			custom < _h1_pair            >,
			branch <           exit_case >,
			write  < _zero   , _argument >,
			compel < _custom , _value    >,

			// exit_case:

			value  < _zero   , _register >
		>;

		template<auto d, auto HEq, auto HCmp, auto V, auto... Vs>
		nik_ces auto _result()
		{
			nik_ce auto R0 = U_pack_Vs<Vs...>;
			nik_ce auto H0 = U_pack_Vs<UP_match, HEq, V, Vs...>;
			nik_ce auto H1 = U_null_Vs;
			nik_ce auto H2 = U_null_Vs;
			nik_ce auto A0 = U_pack_Vs<UP_ordered_insert, HCmp, V, Vs...>;

			return T_start::template result<d, c, R0>(H0, H1, H2, A0);
		}

		template<auto d, auto HEq, auto HCmp, auto V, auto... Vs>
		nik_ces auto result = _result<d, HEq, HCmp, V, Vs...>();

	}; nik_ce auto UP_united_insert = U_store_T<TP_united_insert>;

	template<auto HEq, auto HCmp, auto V, auto... Vs>
	nik_ce auto pack_united_insert = TP_united_insert::template result<MD::initial_depth, HEq, HCmp, V, Vs...>;

	template<auto p, auto V, auto HEq = H_curry_equal, auto HCmp = H_curry_less_than, auto d = MD::initial_depth>
	nik_ce auto list_united_insert = unpack_<p, U_custom, UP_united_insert, d, HEq, HCmp, V>;
*/

/***********************************************************************************************************************/

// monoid:

/*
	template<auto HEq = H_curry_equal, auto HCmp = H_curry_less_than>
	struct TP_united_monoid
	{
		template<auto d, auto p, auto V>
		nik_ces auto result = unpack_<p, U_custom, UP_united_insert, d, HEq, HCmp, V>;

	}; template<auto HEq = H_curry_equal, auto HCmp = H_curry_less_than>
		nik_ce auto UP_united_monoid = U_store_T<TP_united_monoid<HEq, HCmp>>;
*/

/***********************************************************************************************************************/

// (fold) union:

/*
	struct TP_united_fold
	{
		template<auto d, auto HEq, auto HCmp, auto V, auto... Vs>
		nik_ces auto result = TP_cascade::template result<d, UP_united_monoid<HEq, HCmp>, V, Vs...>;

	}; nik_ce auto UP_united_fold = U_store_T<TP_united_fold>;

	template<auto HEq, auto HCmp, auto V, auto... Vs>
	nik_ce auto pack_united_fold = TP_united_fold::template result<MD::initial_depth, HEq, HCmp, V, Vs...>;

	template
	<
		auto p,
		auto HEq = H_curry_equal, auto HCmp = H_curry_less_than,
		auto V = U_null_Vs, auto d = MD::initial_depth
	>
	nik_ce auto list_united_fold = unpack_<p, U_custom, UP_united_fold, d, HEq, HCmp, V>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// compare:

	// Not currently needed, keeping for possible later use.
	// Doesn't scale performantly for frequent comparisons.

/***********************************************************************************************************************/

/*
	struct TP_compare
	{
		template<auto key, auto act>
		nik_ces auto c = controller
		<
			find   <                         >,
			write  < _zero ,       _argument >,
			find   <                         >,
			stage  <                         >,
			action < key   , act , _value    >
		>;

		template<auto d, auto V0, auto V1, auto... Vs, auto key, auto act, template<auto...> class B>
		nik_ces auto _result(nik_avp(T_overload<key, act>*), nik_avp(T_store_B<B>*))
		{
			nik_ce auto Pred0 = U_store_T<B<V0>>;
			nik_ce auto Pred1 = U_store_T<B<V1>>;

			nik_ce auto H0    = U_pack_Vs<Pred1, Vs...>;
			nik_ce auto H1    = U_null_Vs;
			nik_ce auto H2    = U_null_Vs;
			nik_ce auto A0    = U_pack_Vs<Pred0, Vs...>;

			return T_start::template result<d, c<key, act>>(H0, H1, H2, A0);
		}

		template<auto d, auto Op, auto H, auto V0, auto V1, auto... Vs>
		nik_ces auto result = _result<d, V0, V1, Vs...>(Op, H);

	}; nik_ce auto UP_compare = U_store_T<TP_compare>;

	template<auto Op, auto H, auto V0, auto V1, auto... Vs>
	nik_ce auto pack_compare = TP_compare::template result<MD::initial_depth, Op, H, V0, V1, Vs...>;

	template<auto p, auto Op, auto V0, auto V1, auto H = H_partial_same, auto d = MD::initial_depth>
	nik_ce auto list_compare = unpack_<p, U_custom, UP_compare, d, Op, H, V0, V1>;
*/

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

	//	constexpr auto p = U_pack_Vs
	//	<
	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,

	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,

	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,

	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,
	//		0, 3, 4, 5, 9,  0, 3, 4, 5, 9,

	//		0, 3, 4, 5, 9
	//	>;

	//	printf("%s\n"  , eval<_same_, U_char, U_char> ? "true" : "false");
	//	printf("%s\n"  , eval<_same_, U_char, U_void> ? "true" : "false");

	//	printf("%d\n"  , cctmp_algorithm::pack_at<4,  0, 3, 4, 5, 9>);
	//	printf("%d\n"  , cctmp_algorithm::list_at<p, 4>);
	//	printf("%llu\n", cctmp_algorithm::pack_left<5,  0, 3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_algorithm::list_left<p, 5>);
	//	printf("%llu\n", cctmp_algorithm::pack_right<5,  0, 3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_algorithm::list_right<p, 0>);

	//	constexpr auto p_split = cctmp_algorithm::pack_split<2,  0, 3, 4, 5, 9>;
	//	printf("%llu, %llu\n", tuple_value<0>(p_split), tuple_value<1>(p_split));
	//	constexpr auto l_split = cctmp_algorithm::list_split<p, 4>;
	//	printf("%llu, %llu\n", tuple_value<0>(l_split), tuple_value<1>(l_split));

	//	constexpr auto p_cut = cctmp_algorithm::pack_cut<2,  0, 3, 4, 5, 9>;
	//	printf("%llu, %llu\n", tuple_value<0>(p_cut), tuple_value<1>(p_cut));
	//	constexpr auto l_cut = cctmp_algorithm::list_cut<p, 3>;
	//	printf("%llu, %llu\n", tuple_value<0>(l_cut), tuple_value<1>(l_cut));

	//	constexpr auto p_alter = cctmp_algorithm::pack_alter<2,  0, 3, 4, 5, 9>;
	//	constexpr auto l_alter = unpack_<tuple_value<0>(p_alter), _car_>;
	//	constexpr auto r_alter = unpack_<tuple_value<0>(p_alter), _cadr_>;
	//	printf("%llu, %llu, %llu\n", l_alter, r_alter, tuple_value<1>(p_alter));
	//	constexpr auto p_alter = cctmp_algorithm::list_alter<p, 3>;
	//	constexpr auto l_alter = unpack_<tuple_value<0>(p_alter), _car_>;
	//	constexpr auto r_alter = unpack_<tuple_value<0>(p_alter), _cadr_>;
	//	printf("%llu, %llu, %llu\n", l_alter, r_alter, tuple_value<1>(p_alter));

	//	printf("%llu\n", cctmp_algorithm::segment<unsigned{10}>);

	//	printf("%d\n", cctmp_algorithm::pack_sifter<_is_greater_than_<4>, 0, 3, 4, 5, 9>);
	//	printf("%d\n", cctmp_algorithm::list_sifter<p, _is_greater_than_<4>>);

	//	printf("%d\n", cctmp_algorithm::pack_fold<_add_, 0, 3, 4, 5, 9>);
	//	printf("%d\n", cctmp_algorithm::list_fold<p, _add_, 0>);

	//	printf("%llu\n", cctmp_algorithm::pack_erase<1,  0, 3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_algorithm::list_erase<p, 1>);
	//	printf("%llu\n", cctmp_algorithm::pack_insert<1, 7,  0, 3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_algorithm::list_insert<p, 1, 7>);
	//	printf("%llu\n", cctmp_algorithm::pack_replace<1, 7,   0, 3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_algorithm::list_replace<p, 1, 7>);

	//	printf("%llu\n", cctmp_algorithm::pack_ordered_insert<_less_than_, 1,    0, 3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_algorithm::list_ordered_insert<p, 1>);

	//	printf("%llu\n", cctmp_algorithm::pack_ordered_replace<_less_than_, 2,  0, 3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_algorithm::list_ordered_replace<p, 2>);

	//	printf("%llu\n", cctmp_algorithm::pack_sort<_less_than_, U_null_Vs, 0, 3, 4, 5, 9>);
	//	printf("%llu\n", cctmp_algorithm::list_sort<p>);		// gcc 2.854s / clang 7.166s

	//	printf("%llu\n", cctmp_functional::pack_union<H_curry_equal, H_curry_less_than, U_null_Vs, 9,    3, 4, 5, 9>);

	//	constexpr auto def_specs	= U_pack_Vs<0, 1, 2, 3, 4, 5>;
	//	constexpr auto specs0		= U_pack_Vs<3, 5, 0>;
	//	printf("%llu\n", cctmp_functional::list_fill<def_specs, specs0>);

	//	constexpr auto p0  = cctmp_one_cycle_generics::direct_repeat_defaults;
	//	constexpr auto cmp = H_partial<U_custom, cctmp_one_cycle_generics::U_tag_compare, MD::initial_depth, _less_than_>;
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

// (direct/conceptual) interpretation tests:

	template<auto... Vs>
	constexpr auto U_pack_Vs = cctmp::template U_pack_Vs<Vs...>;

	template<typename B, typename E>
	void print_array(B b, E e)
	{
		while (b != e)
		{
			printf("%d, ", *b);
			++b;
		}
	}

/***********************************************************************************************************************/

// functions:

	constexpr int sq(int x)					{ return x*x; }
	constexpr auto _sq_					= cctmp::template _apply_<sq>;

	constexpr int mod_add(int x, int y)			{ return (x+y) % 10; }
	constexpr auto _mod_add_				= cctmp::template _apply_<mod_add>;

	constexpr int carry0_add(int o, int i1, int i2)		{ return (o < i1); }
	constexpr auto _carry0_add_				= cctmp::template _apply_<carry0_add>;

	constexpr int carry1_add(int o, int i, bool a)		{ return a || (i == 1 && o == 0); }
	constexpr auto _carry1_add_				= cctmp::template _apply_<carry1_add>;

	constexpr auto _id_			= cctmp::_id_;
	constexpr auto _add_			= cctmp::_add_;
	constexpr auto _is_25_			= cctmp::template _is_equal_<25>;
	constexpr auto _assign_			= cctmp::_assign_;
	constexpr auto _deref_			= cctmp::_dereference_;

	constexpr auto _add_dd_			= cctmp_generics::template _argcompose_<_add_, _deref_, _deref_>;
	constexpr auto _is_25_d_		= cctmp_generics::template _argcompose_<_is_25_, _deref_>;
	constexpr auto _mod_add_di_		= cctmp_generics::template _argcompose_<_mod_add_, _deref_, _id_>;
	constexpr auto _mod_add_dd_		= cctmp_generics::template _argcompose_<_mod_add_, _deref_, _deref_>;

	constexpr auto _carry0_add_ddd_		= cctmp_generics::template _argcompose_<_carry0_add_, _deref_, _deref_, _deref_>;
	constexpr auto _carry1_add_dii_		= cctmp_generics::template _argcompose_<_carry1_add_, _deref_, _id_, _id_>;

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

/***********************************************************************************************************************/

// direct:

	constexpr auto _match_predicate_is_25_d_	= cctmp_one_cycle_generics::template _match_predicate_<_is_25_d_>;
	constexpr auto _action_function_add_dd_		= cctmp_one_cycle_generics::template _action_function_<_add_dd_>;
	constexpr auto _combine_function_add_		= cctmp_one_cycle_generics::template _combine_function_<_add_>;
	constexpr auto _d_mutate_function_id_		= cctmp_one_cycle_generics::template _mutate_function_<_d_assign_i_>;
	constexpr auto _d_mutate_function_sq_		= cctmp_one_cycle_generics::template _mutate_function_<_d_assign_sq_>;

	constexpr auto _action_function_mod_add_dd_	= cctmp_one_cycle_generics::template _action_function_<_mod_add_dd_>;
	constexpr auto _combine_function_mod_add_di_	= cctmp_one_cycle_generics::template _combine_function_<_mod_add_di_>;
	constexpr auto _aux_next_carry0_add_ddd_	= cctmp_one_cycle_generics::template _aux_next_<_carry0_add_ddd_>;
	constexpr auto _in_next_carry1_add_dii_		= cctmp_one_cycle_generics::template _in_next_<_carry1_add_dii_>;

// conceptual:

	constexpr auto _closed				= cctmp_one_cycle_generics::_closed;
	constexpr auto _closed_ival_			= cctmp_one_cycle_generics::template _ival_<_closed>;
	constexpr auto _closed_out_iter_		= cctmp_one_cycle_generics::template _out_iter_<_closed_ival_>;

	constexpr auto _op_is_25_			= cctmp_one_cycle_generics::template _op_<_is_25_>;
	constexpr auto _op_add_				= cctmp_one_cycle_generics::template _op_<_add_>;
	constexpr auto _op_mod_add_			= cctmp_one_cycle_generics::template _op_<_mod_add_>;
	constexpr auto _op_carry0_add_			= cctmp_one_cycle_generics::template _op_<_carry0_add_>;
	constexpr auto _op_carry1_add_			= cctmp_one_cycle_generics::template _op_<_carry1_add_>;
	constexpr auto _in_arg_id_			= cctmp_one_cycle_generics::template _in_arg_<_id_>;
	constexpr auto _in_arg_sq_			= cctmp_one_cycle_generics::template _in_arg_<_sq_>;

	constexpr auto _match_is_25_			= cctmp_one_cycle_generics::template _match_<_op_is_25_>;
	constexpr auto _action_add_			= cctmp_one_cycle_generics::template _action_<_op_add_>;
	constexpr auto _action_mod_add_			= cctmp_one_cycle_generics::template _action_<_op_mod_add_>;
	constexpr auto _combine_add_			= cctmp_one_cycle_generics::template _combine_<_op_add_>;
	constexpr auto _combine_mod_add_		= cctmp_one_cycle_generics::template _combine_<_op_mod_add_>;
	constexpr auto _combine_add_in_arg_id_		= cctmp_one_cycle_generics::template _combine_<_op_add_, _in_arg_id_>;

	constexpr auto _mutate_in_arg_id_		= cctmp_one_cycle_generics::template _mutate_<_in_arg_id_>;
	constexpr auto _mutate_in_arg_sq_		= cctmp_one_cycle_generics::template _mutate_<_in_arg_sq_>;

	constexpr auto _aux_iter_carry0_add_		= cctmp_one_cycle_generics::template _aux_iter_<_op_carry0_add_>;
	constexpr auto _in_iter_carry1_add_		= cctmp_one_cycle_generics::template _in_iter_<_op_carry1_add_>;

/***********************************************************************************************************************/

// repeat:

//	constexpr auto repeat_dspec		= cctmp_one_cycle_generics::template direct_repeat<>;
//	using Td_repeat				= typename cctmp_one_cycle_assembly::template T_repeat<repeat_dspec>;

//	constexpr auto repeat_cspec		= cctmp_one_cycle_generics::template conceptual_repeat<_closed_out_iter_>;
//	using Tc_repeat				= typename cctmp_one_cycle_assembly::template T_repeat<repeat_cspec>;

// map:

//	constexpr auto map_dspec_id_		= cctmp_one_cycle_generics::template direct_map<>;
//	constexpr auto map_dspec_sq_		= cctmp_one_cycle_generics::template direct_map<_d_mutate_function_sq_>;
//	using Td_map_id				= typename cctmp_one_cycle_assembly::template T_map<map_dspec_id_>;
//	using Td_map_sq				= typename cctmp_one_cycle_assembly::template T_map<map_dspec_sq_>;

//	constexpr auto map_cspec_id_		= cctmp_one_cycle_generics::template conceptual_map<_mutate_in_arg_id_>;
//	constexpr auto map_cspec_sq_		= cctmp_one_cycle_generics::template conceptual_map<_mutate_in_arg_sq_>;
//	using Tc_map_id				= typename cctmp_one_cycle_assembly::template T_map<map_cspec_id_>;
//	using Tc_map_sq				= typename cctmp_one_cycle_assembly::template T_map<map_cspec_sq_>;

// fold:

//	constexpr auto fold_dspec_add_		= cctmp_one_cycle_generics::template direct_fold<_combine_function_add_>;
//	using Td_fold_add			= typename cctmp_one_cycle_assembly::template T_fold<fold_dspec_add_>;

//	constexpr auto fold_cspec_add_		= cctmp_one_cycle_generics::template conceptual_fold<_combine_add_in_arg_id_>;
//	using Tc_fold_add			= typename cctmp_one_cycle_assembly::template T_fold<fold_cspec_add_>;

// find first:

//	constexpr auto find_first_dspec_is_25_	= cctmp_one_cycle_generics::template direct_find_first<_match_predicate_is_25_d_>;
//	using Td_find_first_is_25		= typename cctmp_one_cycle_assembly::template T_find_first<find_first_dspec_is_25_>;

//	constexpr auto find_first_cspec_is_25_	= cctmp_one_cycle_generics::template conceptual_find_first<_match_is_25_>;
//	using Tc_find_first_is_25		= typename cctmp_one_cycle_assembly::template T_find_first<find_first_cspec_is_25_>;

// find all:

//	constexpr auto find_all_dspec_is_25_	= cctmp_one_cycle_generics::template direct_find_all<_match_predicate_is_25_d_>;
//	using Td_find_all_is_25			= typename cctmp_one_cycle_assembly::template T_find_all<find_all_dspec_is_25_>;

//	constexpr auto find_all_cspec_is_25_	= cctmp_one_cycle_generics::template conceptual_find_all<_match_is_25_>;
//	using Tc_find_all_is_25			= typename cctmp_one_cycle_assembly::template T_find_all<find_all_cspec_is_25_>;

// zip:

//	constexpr auto zip_dspec_add_		= cctmp_one_cycle_generics::template direct_zip
//						<
//							_action_function_add_dd_, _d_mutate_function_id_
//						>;
//	using Td_zip_add			= typename cctmp_one_cycle_assembly::template T_zip<zip_dspec_add_>;

//	constexpr auto zip_cspec_add_		= cctmp_one_cycle_generics::template conceptual_zip<_action_add_>;
//	using Tc_zip_add			= typename cctmp_one_cycle_assembly::template T_zip<zip_cspec_add_>;

// fasten:

//	constexpr auto fasten_dspec_add_	= cctmp_one_cycle_generics::template direct_fasten
//						<
//							_action_function_mod_add_dd_, _combine_function_mod_add_di_,
//							_aux_next_carry0_add_ddd_, _in_next_carry1_add_dii_
//						>;
//	using Td_fasten_mod_add			= typename cctmp_one_cycle_assembly::template T_fasten<fasten_dspec_add_>;

//	constexpr auto fasten_cspec_add_	= cctmp_one_cycle_generics::template conceptual_fasten
//						<
//							_action_mod_add_, _combine_mod_add_,
//							_aux_iter_carry0_add_, _in_iter_carry1_add_
//						>;
//	using Tc_fasten_mod_add			= typename cctmp_one_cycle_assembly::template T_fasten<fasten_cspec_add_>;

// glide:

//	constexpr auto glide_dspec_add_		= cctmp_one_cycle_generics::template direct_glide
//						<
//							_action_function_add_dd_, _combine_function_add_
//						>;
//	using Td_glide_add			= typename cctmp_one_cycle_assembly::template T_glide<glide_dspec_add_>;

//	constexpr auto glide_cspec_add_		= cctmp_one_cycle_generics::template conceptual_glide
//						<
//							_action_add_, _combine_add_
//						>;
//	using Tc_glide_add			= typename cctmp_one_cycle_assembly::template T_glide<glide_cspec_add_>;

/***********************************************************************************************************************/

	//	int size = 10;//argc;

	//	int  arr[size];
	//	int  arr_id[size];
	//	int  arr_sq[size];
	//	int* arr_ptr[size];

// repeat:

	//	Td_repeat::result(arr, arr+size, argc);
	//	print_array(arr, arr+size);

	//	Tc_repeat::result(arr, arr+size, argc);
	//	print_array(arr, arr+size);

// map:

	//	Td_map_id::template result(arr_id, 0, size);
	//	print_array(arr_id, arr_id+size);

	//	Td_map_sq::template result(arr_sq, 0, size);
	//	print_array(arr_sq, arr_sq+size);

	//	Tc_map_id::template result(arr_id, 0, size);
	//	print_array(arr_id, arr_id+size);

	//	Tc_map_sq::template result(arr_sq, 0, size);
	//	print_array(arr_sq, arr_sq+size);

// fold:

	//	auto dval = Td_fold_add::template result(0, 1, size);
	//	printf("%d\n", dval);

	//	auto cval = Tc_fold_add::template result(0, 1, size);
	//	printf("%d\n", cval);

// find first:

	//	Td_map_sq::template result(arr_sq, 0, size);

	//	auto dval = Td_find_first_is_25::template result(arr_ptr, arr_sq, arr_sq+size);
	//	printf("%ld\n", dval - arr_ptr);
	//	printf("%ld\n", *arr_ptr - arr_sq);

	//	auto cval = Tc_find_first_is_25::template result(arr_ptr, arr_sq, arr_sq+size);
	//	printf("%ld\n", cval - arr_ptr);
	//	printf("%ld\n", *arr_ptr - arr_sq);

// find all:

	//	Td_map_sq::template result(arr_sq, 0, size);
	//	arr_sq[3] = 25;
	//	arr_sq[8] = 25;

	//	auto dval = Td_find_all_is_25::template result(arr_ptr, arr_sq, arr_sq+size);
	//	printf("%ld\n", dval - arr_ptr);
	//	printf("%ld\n", arr_ptr[0] - arr_sq);
	//	printf("%ld\n", arr_ptr[1] - arr_sq);
	//	printf("%ld\n", arr_ptr[2] - arr_sq);

	//	auto cval = Tc_find_all_is_25::template result(arr_ptr, arr_sq, arr_sq+size);
	//	printf("%ld\n", cval - arr_ptr);
	//	printf("%ld\n", arr_ptr[0] - arr_sq);
	//	printf("%ld\n", arr_ptr[1] - arr_sq);
	//	printf("%ld\n", arr_ptr[2] - arr_sq);

// zip:

	//	Td_map_id::template result(arr_id, 0, size);
	//	Td_map_sq::template result(arr_sq, 0, size);

	//	Td_zip_add::template result(arr, arr_id, arr_sq, arr_sq+size);
	//	print_array(arr, arr+size);

	//	Tc_map_id::template result(arr_id, 0, size);
	//	Tc_map_sq::template result(arr_sq, 0, size);

	//	Tc_zip_add::template result(arr, arr_id, arr_sq, arr_sq+size);
	//	print_array(arr, arr+size);

// fasten:

	//	int mod_size = 3;
	//	int arr_mod_add[mod_size];
	//	int arr_134[] = { 4, 3, 1 };
	//	int arr_379[] = { 9, 7, 3 };

	//	Td_fasten_mod_add::template result(arr_mod_add, 0, 0, arr_134, arr_379, arr_379+mod_size);
	//	printf("%d%d%d\n", arr_mod_add[2], arr_mod_add[1], arr_mod_add[0]);

	//	Tc_fasten_mod_add::template result(arr_mod_add, 0, 0, arr_134, arr_379, arr_379+mod_size);
	//	printf("%d%d%d\n", arr_mod_add[2], arr_mod_add[1], arr_mod_add[0]);

// glide:

	//	Td_map_id::template result(arr_id, 0, size);
	//	Td_map_sq::template result(arr_sq, 0, size);

	//	auto dval = Td_glide_add::template result(0, arr_id, arr_sq, arr_sq+size);
	//	printf("%d\n", dval);

	//	auto cval = Tc_glide_add::template result(0, arr_id, arr_sq, arr_sq+size);
	//	printf("%d\n", cval);

/***********************************************************************************************************************/

// half digit division (baseline):

	unsigned d = 10;

	unsigned long x0[] = { 1, 1 };
	unsigned *x1 = (unsigned*) x0;
	unsigned *i = x1 + 2;

	unsigned q[4];
	for (unsigned *k = q; k < q + 4; ++k) *k = 0;
	unsigned *j = q;

	unsigned long r = 0;
	unsigned *hl = (unsigned*) &r;

	unsigned low = 0;
	unsigned high = 1;

	while (i > x1)
	{
		hl[low] = *i;

		if (r >= d)
		{
			*j = r / d;
			hl[low] = r % d;
			hl[high] = 0;
		}
		else
		{
			hl[high] = hl[low];
			hl[low] = 0;
		}

		--i;

		if (hl[high] == 0)
		{
			hl[high] = hl[low];
			hl[low] = 0;
			++j;
		}
	}

		hl[low] = *i;

		*j = r / d;
		r %= d;

		++j;

	printf("quotient: ");

	for (unsigned *k = q; k < q + (j - q); ++k) printf("%u, ", *k);
	printf("\n");

	printf("remainder: %lu\n", r);

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// make static experiments:

/***********************************************************************************************************************/

// doesn't work:

/*
	template<typename Type>
	constexpr auto remake_array(Type(*f)())
	{
		constexpr auto val = f();

		return val;
	}

	constexpr auto g = []() { return 12; }; // doesn't work

	constexpr auto val = remake_array(g);
*/

/***********************************************************************************************************************/

// doesn't work:

/*
	template<typename... Cs>
	constexpr auto make_array(Cs... cs)
	{
		return array<int, (constexpr) cs()...>;
	}

	struct value
	{
		int v;

		constexpr value(int V) : v{V} { }

		constexpr int operator () () { return v; }
	};

	constexpr auto int_array = make_array // doesn't work
	(
		value (   5 ),
		value (   7 ),
		value (   3 ),
		value ( -14 ),
		value (   0 ),
		value (   9 )
	);
*/

/***********************************************************************************************************************/

// works, but is too limited:

/*
	template<int(*callable)()>
	constexpr auto make_array()
	{
		constexpr auto val = array<int, callable()>;

		return val;
	}

	constexpr auto f = []() { return 9; };

	constexpr auto int_array = make_array
	<
		f
	>();
*/

/***********************************************************************************************************************/

// works:

	template<auto f>
	constexpr auto remake_array()
	{
		constexpr auto val = f();

		return val.key[0];
	}

	template<auto f>
	constexpr auto make_array()
	{
		constexpr auto out_type = cctmp::out_type<f>;

		constexpr auto val = remake_array<f>();

		return val;
	}

	constexpr auto f() { return binding("is_zero", _is_zero_); }

	constexpr auto int_array = make_array<f>();

/***********************************************************************************************************************/

// conditional grammar:

		template
		<
			auto Note, auto op0,
			auto... Ps, nik_vp(p)(T_pack_Vs<Ps...>*),
			auto... Hs, nik_vp(h)(T_pack_Vs<Hs...>*)
		>
		nik_ce auto generic_block_contr<Note, op0, p, h> = controller
		<
			eval<Ps, instruction < BN::pad  , BT::back          >>... ,
			         instruction < BN::turn , Note      , _zero >     ,
			         instruction < BN::sift , Note              >     ,
			eval<Hs, instruction < BN::heap , BT::front         >>... ,
			         instruction < BN::halt , BT::eval  , op0   >
		>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ordered:

/***********************************************************************************************************************/

// mutate (generic):

/*
	template<auto Part>
	struct TP_ordered_mutate
	{
		nik_ces auto c = controller
		<
			find   <                     >,
			copy   < _zero   , _constant >,
			stage  <           _all      >,
			compel < _nested , _h1_pair  >,
			copy   < _one    , _constant >,
			stage  <           _all      >,
			copy   < _zero   , _register >,
			unite  <           _value    >
		>;

		template<auto d, auto b, auto Pred, auto V, auto... Vs>
		nik_ces auto result = T_start::template result<d, c, V>
		(
			U_pack_Vs<_alias_<Pred, V>, Vs...>,
			U_pack_Vs<H_id, H_id, Vs...>,
			U_pack_Vs<Part, b>
		);

	}; template<auto Part>
		nik_ce auto UP_ordered_mutate = U_custom_T<TP_ordered_mutate<Part>>;
*/

/***********************************************************************************************************************/

// insert:

/*
	using TP_ordered_insert		= TP_ordered_mutate<UP_split>;
	nik_ce auto UP_ordered_insert	= U_custom_T<TP_ordered_insert>;

	using TL_ordered_insert		= TP_unpack<UP_ordered_insert>;
	nik_ce auto UL_ordered_insert	= UP_unpack<UP_ordered_insert>;

	template<auto Pred, auto V, auto... Vs>
	nik_ce auto pack_ordered_insert = TP_ordered_insert::template result<MD::initial_depth, H_id, Pred, V, Vs...>;

	template<auto p, auto V, auto Pred = _less_than_, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_ordered_insert = TL_ordered_insert::template result<d, p, b, Pred, V>;
*/

/***********************************************************************************************************************/

// replace:

/*
	using TP_ordered_replace	= TP_ordered_mutate<UP_cut>;
	nik_ce auto UP_ordered_replace	= U_custom_T<TP_ordered_replace>;

	using TL_ordered_replace	= TP_unpack<UP_ordered_replace>;
	nik_ce auto UL_ordered_replace	= UP_unpack<UP_ordered_replace>;

	template<auto Pred, auto V, auto... Vs>
	nik_ce auto pack_ordered_replace = TP_ordered_replace::template result<MD::initial_depth, H_id, Pred, V, Vs...>;

	template<auto p, auto V, auto Pred = _less_than_, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_ordered_replace = TL_ordered_replace::template result<d, p, b, Pred, V>;
*/

/***********************************************************************************************************************/

// monoid:

/*
	template<auto Part, auto Pred = _less_than_, auto b = H_id>
	struct TP_ordered_monoid
	{
		template<auto d, auto p, auto V>
		nik_ces auto result = unpack_<p, UP_ordered_mutate<Part>, d, b, Pred, V>;

	}; template<auto Part, auto Pred = _less_than_, auto b = H_id>
		nik_ce auto UP_ordered_monoid = U_custom_T<TP_ordered_monoid<Part, Pred, b>>;
*/

/***********************************************************************************************************************/

// fold:

/*
	template<auto Part>
	struct TP_ordered_fold
	{
		template<auto d, auto b, auto Pred, auto V, auto... Vs>
		nik_ces auto result = TP_cascade::template result<d, UP_ordered_monoid<Part, Pred, b>, V, Vs...>;

	}; template<auto Part>
		nik_ce auto UP_ordered_fold = U_custom_T<TP_ordered_fold<Part>>;
*/

/***********************************************************************************************************************/

// sort:

/*
	using TP_sort		= TP_ordered_fold<UP_split>;
	nik_ce auto UP_sort	= U_custom_T<TP_sort>;

	using TL_sort		= TP_unpack<UP_sort>;
	nik_ce auto UL_sort	= UP_unpack<UP_sort>;

	template<auto Pred, auto V, auto... Vs>
	nik_ce auto pack_sort = TP_sort::template result<MD::initial_depth, H_id, Pred, V, Vs...>;

	template<auto p, auto Pred = _less_than_, auto V = U_null_Vs, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_sort = TL_sort::template result<d, p, b, Pred, V>;
*/

/***********************************************************************************************************************/

// write:

/*
	using TP_write		= TP_ordered_fold<UP_cut>;
	nik_ce auto UP_write	= U_custom_T<TP_write>;

	using TL_write		= TP_unpack<UP_write>;
	nik_ce auto UL_write	= UP_unpack<UP_write>;

	template<auto Pred, auto V, auto... Vs>
	nik_ce auto pack_write = TP_write::template result<MD::initial_depth, H_id, Pred, V, Vs...>;

	template<auto p, auto Pred = _less_than_, auto V = U_null_Vs, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_write = TL_write::template result<d, p, b, Pred, V>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// modify:

/***********************************************************************************************************************/

/*
	struct TP_modify
	{
		nik_ces auto c = controller
		<
			find      <                     >,
			copy      < _zero   , _constant >,
			stage     <           _all      >,
			compel    < _nested , _h1_pair  >,
			stage     <                     >,
			paste     <           _register >,
			write     < _zero   , _argument >,
			stage     <                     >,
			compel    < _nested             >,
			copy      < _zero   , _register >,
			copy      < _one    , _constant >,
			copy      < _two    , _constant >,
			stage     <                     >,
			f2_unpack <           _value    >
		>;

		template<auto d, auto b, auto Pred, auto Op, auto V, auto... Vs>
		nik_ces auto result = T_start::template result<d, c>
		(
		 	U_pack_Vs<_alias_<Pred, V>, Vs...>,
			U_pack_Vs<H_id, H_id, H_id, Vs...>,
			U_pack_Vs<UP_alter, _unite_, b>,
			U_pack_Vs<Op, V>
		);

	}; nik_ce auto UP_modify = U_custom_T<TP_modify>;
*/

/***********************************************************************************************************************/

// monoid:

/*
	template<auto Op, auto Pred = _same_, auto b = H_id>
	struct TP_modify_monoid
	{
		template<auto d, auto p, auto V>
		nik_ces auto result = unpack_<p, UP_modify, d, b, Pred, Op, V>;

	}; template<auto Op, auto Pred = _same_, auto b = H_id>
		nik_ce auto UP_modify_monoid = U_custom_T<TP_modify_monoid<Op, Pred, b>>;
*/

/***********************************************************************************************************************/

// fold:

/*
	struct TP_modify_fold
	{
		template<auto d, auto b, auto Pred, auto Op, auto V, auto... Vs>
		nik_ces auto result = TP_cascade::template result<d, UP_modify_monoid<Op, Pred, b>, V, Vs...>;

	}; nik_ce auto UP_modify_fold = U_custom_T<TP_modify_fold>;
*/

/***********************************************************************************************************************/

// merge:

/*
	using TP_merge		= TP_modify_fold;
	nik_ce auto UP_merge	= U_custom_T<TP_merge>;

	using TL_merge		= TP_unpack<UP_merge>;
	nik_ce auto UL_merge	= UP_unpack<UP_merge>;

	template<auto Pred, auto Op, auto V, auto... Vs>
	nik_ce auto pack_merge = TP_merge::template result<MD::initial_depth, H_id, Pred, Op, V, Vs...>;

	template<auto p, auto Op, auto Pred = _same_, auto V = U_null_Vs, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_merge = TL_merge::template result<d, p, b, Pred, Op, V>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// match:

	// This operator is intended for use within machine tests, with the _h1_pair option.

/***********************************************************************************************************************/

/*
	struct TP_match
	{
		template<auto Pred, auto V, auto... Vs>
		nik_ces auto _result()
		{
			nik_ce auto pos  = find_<_alias_<Pred, V>, Vs...>;
			nik_ce auto size = sizeof...(Vs);

			return eval<_to_tuple_, bool{pos < size}, pos>;
		}

		template<auto Pred, auto V, auto... Vs>
		nik_ces auto result = _result<Pred, V, Vs...>();

	}; nik_ce auto UP_match = U_custom_T<TP_match>;

	struct TL_match
	{
		template<auto p, auto Pred, auto V>
		nik_ces auto result = unpack_<p, UP_match, Pred, V>;

	}; nik_ce auto UL_match = U_custom_T<TL_match>;

	template<auto Pred, auto V, auto... Vs>
	nik_ce auto pack_match = TP_match::template result<Pred, V, Vs...>;

	template<auto p, auto V, auto Pred = _same_>
	nik_ce auto list_match = TL_match::template result<p, Pred, V>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lookup:

/***********************************************************************************************************************/

/*
	struct TP_lookup
	{

	}; nik_ce auto UP_lookup = U_custom_T<TP_lookup>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

/***********************************************************************************************************************/

// value:

/*
	template<gindex_type n, typename... Ts>
	nik_ce auto & tuple_value(tuple<Ts...> & t) { return NIK_TUPLE_BLOCK(3, 500, n, Ts)(t); }

	template<gindex_type n, typename... Ts>
	nik_ce const auto & tuple_value(const tuple<Ts...> & t) { return NIK_TUPLE_BLOCK(3, 500, n, Ts)(t); }
*/

/***********************************************************************************************************************/

// to list:

/*
	template<auto b, auto c>
	nik_ce auto return_tuple_to_list()
	{
		nik_ce auto t = c();

		return to_list_<b, tuple_value<Is>(t)...>;
	}

	template<auto b, auto c>
	nik_ce auto constexpr_tuple_to_list()
	{
		nik_ce auto types = c();

		return return_tuple_to_list<c>();
	}

	template<auto b, auto c>
	nik_ce auto callable_tuple_to_list = constexpr_tuple_to_list<b, c>()
*/

/***********************************************************************************************************************/

	// GCC 11 does not accept this (clang 14 does):

/*
	template<gindex_type _2_N, template<auto...> typename B, auto... LUs, nik_vp(p)(B<LUs...>*)>
	struct T_machine<MN::halt, MT::value, _2_N, p>
	{
		template
		<
			NIK_MACHINE_CONTROLS(d, m, c, i),
			T_store_U<LUs>... LVs, auto VN, auto... Vs,
			typename... Heaps
		>
		nik_ces auto result(Heaps... Hs)
		{
			return VN;
		}
	};
*/

/***********************************************************************************************************************/

// apply:

	struct T_machine_nary_apply
	{
		template<auto Inds, auto Op>
		constexpr static auto H0 = U_pack_Vs<_car_, Inds, Op>;

		template<auto l = _one, auto n = _one>
		constexpr static auto contr = controller
		<
			instruction < MN::call , MT::compel , l , n >,
			instruction < MN::halt , MT::eval           >
		>;

		template<auto d, auto Op, auto Inds, auto... Vs>
		constexpr static auto result = T_machine_start::template result<d, contr<>, Vs...>(H0<Inds, Op>);
	};

	struct T_machine_binary_apply
	{
		constexpr static auto d    = MD::initial_depth;
		constexpr static auto regs = T_machine_get::regs;
		constexpr static auto heap = T_machine_get::heap;
		constexpr static auto bs   = U_pack_Vs < heap , regs  , regs >;
		constexpr static auto ns   = U_pack_Vs < _two , _zero , _one >;
		constexpr static auto Inds = U_pack_Vs<bs, ns>;

		template<auto Op, auto V0, auto V1>
		constexpr static auto result = T_machine_nary_apply::template result<d-1, Op, Inds, V0, V1>;

	}; constexpr auto _binary_apply_ = U_custom_T<T_machine_binary_apply>;

	constexpr auto _prax_add_      = _praxis_< _add_      >;
	constexpr auto _prax_multiply_ = _praxis_< _multiply_ >;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (recursive eval):

	// In general defer to the compile time register machine,
	// but there are occassions where this might be preferred.

/***********************************************************************************************************************/

	template<auto... Vs>
	nik_ce auto reval = eval<reval<Vs>...>;

	template<auto V>
	nik_ce auto reval<V> = V;

	template<auto... Vs, nik_vp(alias)(T_alias<Vs...>*)>
	nik_ce auto reval<alias> = eval<reval<Vs>...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

	constexpr auto list0 = U_pack_Vs<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11>;
	constexpr auto list1 = U_pack_Vs<3, 10, 4, 0, 7, 8, 5, 6, 9, 1, 2, 11>;
	constexpr auto list2 = U_pack_Vs
	<
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,

		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,

		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		0, 1, 2, 3, 44
	>;

//	constexpr auto val = unpack_<list0, _par_fold_, _add_, 0>;
//	constexpr auto val = unpack_<list1, _par_fold_, _add_, 0>;

	constexpr auto ops = U_pack_Vs<_is_less_than_<5>, _constant_<true>>;
//	constexpr auto val = unpack_<list0, _par_sift_, ops>;
//	constexpr auto val = unpack_<list1, _par_sift_, ops>;
//	constexpr auto val = unpack_<list2, _par_sift_, ops>;

//	constexpr auto val = unpack_<list0, _par_at_, 4>;
//	constexpr auto val = unpack_<list1, _par_at_, 4>;
//	constexpr auto val = unpack_<list2, _dpar_at_, 15, 164>;

//	constexpr auto val = unpack_<list0, _par_replace_, 4, 4>;
//	constexpr auto val = unpack_<list1, _par_replace_, 4, 4>;
//	constexpr auto val = unpack_<list2, _par_replace_, 4, 4>;

//	constexpr auto val = unpack_<list0, _par_insert_, 0, 4>;
//	constexpr auto val = unpack_<list1, _par_insert_, 0, 4>;
//	constexpr auto val = unpack_<list2, _par_insert_, 0, 4>;

//	constexpr auto val = unpack_<list0, _par_erase_, 4>;
//	constexpr auto val = unpack_<list1, _par_erase_, 4>;
//	constexpr auto val = unpack_<list2, _par_erase_, 4>;

//	constexpr auto val = eval<_par_insert_sort_<_less_than_>, list0, 5>;
//	constexpr auto val = eval<_par_insert_sort_<_less_than_>, list1, 5>;
//	constexpr auto val = eval<_par_insert_sort_<_less_than_>, list2, 5>;

//	constexpr auto val = unpack_<list0, _par_sort_<_less_than_>>;
//	constexpr auto val = unpack_<list1, _par_sort_<_less_than_>>;
//	constexpr auto val = unpack_<list2, _par_sort_<_less_than_>>;

//	constexpr auto val = unpack_<list0, _part_sort_<_less_than_>>;
//	constexpr auto val = unpack_<list1, _part_sort_<_less_than_>>;
//	constexpr auto val = unpack_<list2, _part_sort_<_less_than_>>;

/***********************************************************************************************************************/

//	constexpr auto f   = _pose_<_increment_<1>, _times_<2>>;
//	constexpr auto val = eval<f, 2>;

//	constexpr auto val = eval<_par_segment_, 10>;
//	constexpr auto val = eval<_binary_apply_, _prax_add_, 2, 3>;
//	constexpr auto val = eval<_binary_apply_, _prax_multiply_, 2, 3>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array:

/***********************************************************************************************************************/

/*
// map:

	template<auto f, auto a, auto l, auto Op, auto s, auto U, auto S>
	nik_ce auto array_map_ = eval<_array_apply_, Op, U, S, s, _multimap_<_arg_deref_<f>>, a, l>;

// fold:

	template<auto f, auto init, auto a, auto l, auto Op, auto U, auto S>
	nik_ce auto array_fold_ = eval<_array_apply_, Op, U, S, U_pack_Vs<0>, _multifold_<_arg_deref_<f>, init>, a, l>;

// find:

//	template<auto p, auto a, auto l, auto Op, auto U, auto S>
//	nik_ce auto array_find_ = eval<_array_apply_, Op, U, S, _multifind<_arg_deref_<p>>, a, l>;

// sift:

// -> V:

	template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
	nik_ce auto V_sift(nik_vp(indices)(T_pack_Vs<Is...>*))
	{
		nik_ce auto Size	= Leng + 1;
		nik_ce auto arr		= ArrayModule::template apply<Type, Size, IteratorModule::Sift, Leng, p>(Arr);
		nik_ce auto leng	= arr.value[Leng];

		if nik_ce (leng != sizeof...(Is)) return arr;
		else return array<Type, arr.value[Is]...>;
	}

	template<typename Type, auto p, auto Arr, auto Leng, auto I0, auto... Is>
	nik_ce auto V_sift(nik_vp(indices)(T_pack_Vs<I0, Is...>*))
	{
		nik_ce auto Size	= sizeof...(Is) + 1;
		nik_ce auto arr		= apply<Type, Size, IteratorModule::Sift, Leng, p>(Arr);

		return array<Type, arr.value[Is]...>;
	}

// -> U:

	template<typename Type, auto p, auto Arr, auto Leng, auto I0, auto... Is>
	nik_ce auto U_sift(nik_vp(indices)(T_pack_Vs<I0, Is...>*))
	{
		nik_ce auto Size	= sizeof...(Is) + 1;
		nik_ce auto arr		= apply<Type, Size, IteratorModule::Sift, Leng, p>(Arr);

		return U_pack_Vs<arr.value[Is]...>;
	}

	// subsequence:

// -> V:

	template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
	nik_ce auto V_subsequence(nik_vp(indices)(T_pack_Vs<Is...>*))
		{ return V_apply<Type, IteratorModule::Sift, Arr>(U_pack_Vs<Leng, sizeof...(Is), p>, indices); }

// -> U:

	template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
	nik_ce auto U_subsequence(nik_vp(indices)(T_pack_Vs<Is...>*))
		{ return U_apply<Type, IteratorModule::Sift, Arr>(U_pack_Vs<Leng, sizeof...(Is), p>, indices); }

// zip:

// generic:

// -> V:

	template<typename Type, auto f, auto Arr1, auto Leng1, auto Arr2, typename Indices>
	nik_ce auto V_zip(Indices indices)
		{ return V_apply<Type, IteratorModule::Zip, Arr1, Arr2>(U_pack_Vs<Leng1, f>, indices); }

// -> U:

	template<typename Type, auto f, auto Arr1, auto Leng1, auto Arr2, typename Indices>
	nik_ce auto U_zip(Indices indices)
		{ return U_apply<Type, IteratorModule::Zip, Arr1, Arr2>(U_pack_Vs<Leng1, f>, indices); }
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// case studies:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// factorial:

/***********************************************************************************************************************/

// baseline:

	template<typename T>
	constexpr auto pair_factorial_baseline(T p, T n)
	{
		if (n == 0) return p;
		else        return pair_factorial_baseline(p*n, n-1);
	}

	template<typename T>
	constexpr auto factorial_baseline(T n)
	{
		return pair_factorial_baseline(T(1), n);
	}

/***********************************************************************************************************************/

// source:

	template
	<
		auto p       = 0 , auto n        = 1  ,
		auto is_zero = 0 , auto multiply = 1  , auto decrement = 2 ,
		auto Loop    = 0 , auto Done     = 12
	>
	nik_ce auto pair_factorial_contr = controller
	<
	// Loop:
		instruction < AN::select  , AT::id     , is_zero   >, // get is_zero pack containing arg positions.
		instruction < AN::call    , AT::id                 >, // unpack and apply is_zero to args.

		instruction < AN::jump    , AT::branch , Done      >, // branch to Done label, continue otherwise.

		instruction < AN::select  , AT::id     , multiply  >, // get multiply [...].
		instruction < AN::call    , AT::id                 >, // unpack [...].
		instruction < AN::select  , AT::front  , p         >, // get left arg types before position p.
		instruction < AN::replace , AT::id                 >, // arg expand and replace at position p.

		instruction < AN::select  , AT::id     , decrement >, // get decrement [...].
		instruction < AN::call    , AT::id                 >, // unpack [...].
		instruction < AN::select  , AT::front  , n         >, // get left arg types [...].
		instruction < AN::replace , AT::id                 >, // arg expand [...].

		instruction < AN::jump    , AT::go_to  , Loop      >, // goto Loop.
	// Done:
		instruction < AN::select  , AT::front  , p         >, // get left arg types [...].
		instruction < AN::right   , AT::id                 >, // arg expand and drop the left args before p.
		instruction < AN::first   , AT::id                 >  // return the first element.
	>;

/***********************************************************************************************************************/

// lookup:

	template<auto p = 0, auto n = 1>
	nik_ce auto pair_factorial_lookup = U_pack_Vs
	<
		U_pack_Vs< _is_zero_      , n     >, // position: 0
		U_pack_Vs< _multiply_     , p , n >, // position: 1
		U_pack_Vs< _decrement_<1> , n     >  // position: 2
	>;

/***********************************************************************************************************************/

// compilation:

	template<typename T>
	nik_ce auto factorial(T v)
	{
		nik_ce auto s = U_store_T<T>;
		nik_ce auto c = pair_factorial_contr<>;
		nik_ce auto l = pair_factorial_lookup<>;

		return T_assembly_start::template result<s, c, l>(T(1), v);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// arg map:

/***********************************************************************************************************************/

	template<typename B, typename E>
	void print_array(B b, E e)
	{
		while (b != e)
		{
			printf("%d, ", *b);
			++b;
		}
	}

/***********************************************************************************************************************/

	template<auto f>
	struct T_arg_map
	{
		constexpr static auto predicate = _not_equal_;
		constexpr static auto mutate    = arg_subpose<_assign_, _dereference_, f>;
		constexpr static auto next      = arg_subpose<_assign_, _id_, _increment_<>>;
		constexpr static auto multimap  = _multimap_<mutate, next, next>;

		template<auto out = _zero, auto in = _one, auto end = _two>
		constexpr static auto lookup = U_pack_Vs
		<
			U_pack_Vs
			<
				U_pack_Vs< predicate , in  , end >,
				U_pack_Vs< multimap  , out , in  >
			>
		>;

		template<auto n = _zero>
		constexpr static auto contr = controller
		<
			instruction< AN::select , AT::pair , n >,
			instruction< AN::loop   , AT::id       >,
			instruction< AN::first  , AT::id       >
		>;

		template<typename Out, typename In, typename End>
		constexpr static auto result(Out out, In in, End end)
		{
			constexpr auto s = U_store_T<Out>;

			return T_assembly_start::template result<s, contr<>, lookup<>>(out, in, end);
		}

	}; template<auto f>
		constexpr auto _arg_map_ = U_store_T<T_arg_map<f>>;

	constexpr auto range = _arg_map_<_id_>;

/***********************************************************************************************************************/

		int s = 10, x[s];

		for (int k = 0; k != argc; ++k) x[k] = k;

		print_array(x, x + argc);
	//	print_array(x, apply<range>(x, 0, argc));

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

	struct a_struct
	{
		gindex_type v;

		nik_ce a_struct(gcindex_type _v) : v{_v} { }

		template<auto V>
		nik_ces auto result() { return a_struct{V}; };
	};

	template<auto Size>
	struct b_struct
	{
		nik_ces auto size = Size; 

		const a_struct *v;

		nik_ce b_struct(const a_struct (&_v)[Size]) : v{_v} { }
		nik_ce b_struct(const a_struct *_v) : v{_v} { }
	};

	nik_ce auto unit_source()
	{
		return source
		(
		 	"add x y   ;"
			"goto done ;"
		);
	}

	template<typename Type, auto Op, auto... Vs>
	nik_ce Type to_array[] = { T_store_U<Op>::template result<Vs>()... };

//	template<typename Type, Type... Vs>
//	nik_ce Type array[] = { Vs... };

//	nik_ce a_struct a_struct_array[]

	template<auto arr>
	nik_ce auto first_val = arr[0];

	template<auto Callable>
	nik_ce auto make_array()
	{
		nik_ce auto src = Callable();
		nik_ce auto arr = to_array<a_struct, U_store_T<a_struct>, 1, 2>;
		nik_ce auto _a  = first_val<arr>;

		auto val = b_struct<2>(arr);

		return src.syntax[6].token;//_a.v;
	}

	nik_ce auto toc = make_array<unit_source>();

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser:

/***********************************************************************************************************************/

// automaton:

	// debugging:

		nik_ces gindex_type debug_end[] = // 32
		{
			  9,  11,  13, 18,		// factorial p n ;
			 23,  36,			// loop: ;
			 40,  48,  50, 54,		// test is_zero n ;
			 60,  65,  72,			// branch done ;
			 73,  75,  84,  86,  88, 90,	// p = multiply p n ;
			 91,  93, 103, 105, 108,	// n = decrement n ;
			112, 117, 126,			// goto loop ;
			131, 144,			// done: ;
			150, 152, 162			// return p ;
		};

	template<auto SourceCallable>
	struct GenericAssemblyPDA
	{
		nik_ces auto static_src	= _static_object_<SourceCallable>;
		nik_ces auto src	= T_store_U<static_src>::value;
		nik_ces auto tt		= T_generic_assembly_pdtt::value;

		using transition_table	= T_generic_assembly_pdtt;
		using src_type		= decltype(src);
		using T_dfa		= typename src_type::T_dfa;
		using char_type		= typename src_type::char_type;
		using stack_type	= Stack<src.stack_size>;
		using toc_type		= TableOfContents
					<
						char_type,
						src.block_size, src.max_line_size, src.max_entry_size
					>;

		stack_type stack;
		toc_type toc;

		lexeme word;
		bool lex_word;

		char_type derivation[10'000]; // for debugging.
		char_type *dcur; // for debugging.

		nik_ce GenericAssemblyPDA() :

			stack    { transition_table::nt_start },
			toc      {                            },
			word     {                            },
			lex_word { true                       },

			derivation {            }, // for debugging.
			dcur       { derivation }  // for debugging.
		{
			auto current = src.string;

			debug_before();

			while (*stack.current != '$')
			{
				lex_word = lex_word && (current != src.finish);
				auto sf  = stack.front();
				auto k   = transition_table::token_kind(sf);

				switch (k)
				{
					case TokenKind::nonterminal:
					{
						debug_stack();

						if (lex_word) word = T_dfa::lex(current, src.finish);
						auto tr = tt.get_entry(sf, word.value);

						debug_tokens(current);
						debug_production(word.value, tr.body);

						stack.push(tr.body.symbol, tr.body.size);

						lex_word = (tr.read == PRead::next);
						if (lex_word) current = word.finish;

						debug_read();

						// tr.action();
						break;
					}
					case TokenKind::terminal:
					{
						if (sf != 'e')
						{
							if (lex_word) word = T_dfa::lex(current, src.finish);
							lex_word = true;
						}

						debug_stack();
						debug_tokens(current);
						debug_pad(17);
						debug_read();

						// confirm (sf == l.value) ?
						if (sf != 'e') current = word.finish;
						stack.pop();
						break;
					}
					default:
					{
						// error.
						break;
					}
				}
			}

			debug_after();
		}

		nik_ce auto debug_pad(int s)
		{
			for (int k = 0; k < s; ++k) *(dcur++) = ' ';
		}

		nik_ce auto debug_before()
		{
			*(dcur++) = '\n';
		}

		nik_ce auto debug_stack()
		{
			auto k = stack.current + 1;
			debug_pad(14 - (k - stack.token));
			while (k != stack.token) *(dcur++) = *--k;
		}

		nik_ce auto debug_tokens(char_type const* b)
		{
			debug_pad(4);
			auto b0 = b;
			auto count = 32;
			while (b != src.finish)
			{
				auto w = T_dfa::lex(b, src.finish);
				b = w.finish;
				--count;
			}

			b = b0;
			debug_pad(count);
			while (b != src.finish)
			{
				auto w = T_dfa::lex(b, src.finish);
				*(dcur++) = w.value;
				b = w.finish;
			}
		}

		nik_ce auto debug_production(ctoken_type t, const Body & b)
		{
			debug_pad(4);
			auto sf = stack.front();
			*(dcur++) = sf; *(dcur++) = ' '; *(dcur++) = t;
			*(dcur++) = ' '; *(dcur++) = '-'; *(dcur++) = '>'; *(dcur++) = ' ';
			auto s = 6 - b.size;
			for (auto k = b.symbol; k != b.symbol + b.size; ++dcur, ++k) *dcur = *k;
			debug_pad(s);
		}

		nik_ce auto debug_read()//char_type const* const b)
		{
			debug_pad(4);
			if (lex_word)
			{
				*(dcur++) = 'n'; *(dcur++) = 'e';
				*(dcur++) = 'x'; *(dcur++) = 't';
			}
			else
			{
				*(dcur++) = 'p'; *(dcur++) = 'e';
				*(dcur++) = 'e'; *(dcur++) = 'k';
			}
			*(dcur++) = '\n';
		}

		nik_ce auto debug_after()
		{
			*(dcur++) = '\n'; *dcur = '\0';
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// print table of contents:

/***********************************************************************************************************************/

	template<typename EntryType>
	void print_entry(const EntryType & entry)
	{
		for (auto k = entry.start; k != entry.finish; ++k) printf("%c", *k);

		printf("{%d} ", (int) entry.index);
	}

	template<typename LineType>
	void print_line(const LineType & line)
	{
		for (auto k = line.begin(); k != line.end(); ++k) print_entry(*k);

		printf("\n");
	}

	template<typename PageType>
	void print_page(const PageType & page)
	{
		for (auto k = page.begin(); k != page.end(); ++k) print_line(*k);
	}

/***********************************************************************************************************************/

	template<typename ParamType>
	void print_param(const ParamType & param)
	{
		for (auto k = param.begin; k != param.locus; ++k) print_line(**k);
	}

	//	print_note(factorial.pda.syntax.label);
	//	print_note(factorial.pda.syntax.go_to);
	//	print_note(factorial.pda.syntax.branch);
	//	print_note(factorial.pda.syntax.lookup);
	//	print_page(factorial.pda.syntax.page);

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // case studies

