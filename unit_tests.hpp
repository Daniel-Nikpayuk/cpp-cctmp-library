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
	constexpr auto sort(nik_vp(l)(T_store_Vs<Vs...>*))
	{
		constexpr auto d		= MachineDispatch::initial_depth;
		constexpr auto list		= U_restore_T<decltype(l)>;
		constexpr auto n		= Overload::template result<Overload::find, cmp, list, insert>;

						// bad design: does not compose well with trampolining.
		constexpr auto sp		= NIK_FUNCTION_BLOCK(9, d, n, BN::split, Vs)(U_null_Vs);

		return Overload::template result<Overload::unite, sp.v1, sp.v2, insert>;
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
	nik_ce auto explore_line(nik_avp(T_store_Vs<words...>*))
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
	nik_ce auto explore(nik_avp(T_store_Vs<deps, lines...>*))
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
/***********************************************************************************************************************/

} // case studies

