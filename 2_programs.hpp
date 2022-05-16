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

// programs:

namespace cctmp_program
{
	using namespace cctmp;

// variable:

	struct Variable
	{
		nik_ces auto m		= MT::id;
		nik_ces auto i		= MachineDispatch::initial_index;
		nik_ces auto ctn	= MI::value;

		template<auto d, auto rtn, auto n, auto h0, auto c = controller<variable<n, rtn, ctn>>>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i) NIK_END_MACHINE(h0, U_null_Vs, U_null_Vs);
	};

// function:

	struct Function
	{
		nik_ces auto m		= MT::id;
		nik_ces auto i		= MachineDispatch::initial_index;
		nik_ces auto ctn	= MI::value;

		template<auto d, auto rtn, auto n, auto h0, auto c = controller<function<n, rtn, ctn>>>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i) NIK_END_MACHINE(h0, U_null_Vs, U_null_Vs);
	};

// compel:

	struct Compel
	{
		nik_ces auto m		= MT::id;
		nik_ces auto i		= MachineDispatch::initial_index;
		nik_ces auto ctn	= MI::value;

		template<auto d, auto h0, auto dec = _three, auto c = controller<compel<ctn, dec>>>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i) NIK_END_MACHINE(h0, U_null_Vs, U_null_Vs);
	};
}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// block:

namespace cctmp_program
{

// at:

	struct At_v0
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = Variable::template result<d, BN::sifter, n, p>;
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	constexpr auto at_v0 = At_v0::template result<d, n, p>;

// left:

	struct Left_v0
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = Function::template result<d, BN::left, n, p>;
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	constexpr auto left_v0 = Left_v0::template result<d, n, p>;

// right:

	struct Right_v0
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = Variable::template result<d, BN::right, n, p>;
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	constexpr auto right_v0 = Right_v0::template result<d, n, p>;

// cut:

	struct Cut_v0
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = Function::template result<d, BN::filter, n, p>;
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	constexpr auto cut_v0 = Cut_v0::template result<d, n, p>;

// split:

	struct Split_v0
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = Function::template result<d, BN::split, n, p>;
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	constexpr auto split_v0 = Split_v0::template result<d, n, p>;

// segment:

	struct T_Segment_v0
	{
		template<auto d, auto n>
		nik_ces auto result = block
		<
			BN::segment,
			BlockDispatch::next_note(d, n),
			BlockDispatch::next_length_9(d, n)

		>::template result
		<
			BlockDispatch::next_depth(d),
			BlockDispatch::next_index_9(d, n)
		>;
	};

	constexpr auto U_Segment_v0 = U_store_T<T_Segment_v0>;

	struct Segment_v0
	{
		template<auto d, auto n>
		nik_ces auto result = Compel::template result<d, U_pack_Vs<U_Segment_v0, n>>;
	};

	template<auto n, auto d = MachineDispatch::initial_depth>
	constexpr auto segment_v0 = Segment_v0::template result<d, n>;

// fold:

	struct T_Fold_v0
	{
		template<auto d, auto op, auto V, auto l>
		nik_ces auto result = V;
	};

	template<auto d, auto op, auto V, auto... Vs, nik_vp(l)(auto_pack<Vs...>*)>
	constexpr auto T_Fold_v0::result<d, op, V, l> = block
	<
		BN::fold,
		BlockDispatch::next_note(d, sizeof...(Vs)),
		BlockDispatch::next_length_9(d, sizeof...(Vs))

	>::template result
	<
		BlockDispatch::next_depth(d),
		BlockDispatch::next_index_9(d, sizeof...(Vs)),
		V, Vs...
	>(op);

	constexpr auto U_Fold_v0 = U_store_T<T_Fold_v0>;

	struct Fold_v0
	{
		template<auto d, auto op, auto V, auto l>
		nik_ces auto result = Compel::template result<d, U_pack_Vs<U_Fold_v0, op, V, l>>;
	};

	template<auto op, auto V, auto l, auto d = MachineDispatch::initial_depth>
	constexpr auto fold_v0 = Fold_v0::template result<d, op, V, l>;
}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// mutators:

/***********************************************************************************************************************/

namespace cctmp_program
{
// version 0:

	// erase:

		struct Erase_v0
		{
			template<index_type n>
			nik_ces contr_type program = controller
			<
				function  < n , BN::filter >,
				shift     <                >,
				unite     <     _value     >
			>;

			nik_ces auto m = MT::id;
			nik_ces auto i = MachineDispatch::initial_index;

			template<auto d, auto n, auto p, auto c = program<n>>
			nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i) NIK_END_MACHINE(p, U_null_Vs, U_null_Vs);
		};

		template<auto n, auto p, auto d = MachineDispatch::initial_depth>
		constexpr auto erase_v0 = Erase_v0::template result<d, n, p>;

	// insert:

		struct Insert_v0
		{
			template<index_type n, key_type v = 0>
			nik_ces contr_type program = controller
			<
				function  < n , BN::split >,
				shift     <               >,
				copy      < v , _register >,
				unite     <     _value    >
			>;

			nik_ces auto m = MT::id;
			nik_ces auto i = MachineDispatch::initial_index;

			template<auto d, auto v, auto n, auto p, auto c = program<n>>
			nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i), v NIK_END_MACHINE(p, U_null_Vs, U_null_Vs);
		};

		constexpr auto U_Insert_v0 = U_store_T<Insert_v0>;

		template<auto v, auto n, auto p, auto d = MachineDispatch::initial_depth>
		constexpr auto insert_v0 = Insert_v0::template result<d, v, n, p>;

	// replace:

		struct Replace_v0
		{
			template<index_type n, key_type v = 0>
			nik_ces contr_type program = controller
			<
				function  < n , BN::filter >,
				shift     <                >,
				copy      < v , _register  >,
				unite     <     _value     >
			>;

			nik_ces auto m = MT::id;
			nik_ces auto i = MachineDispatch::initial_index;

			template<auto d, auto v, auto n, auto p, auto c = program<n>>
			nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i), v NIK_END_MACHINE(p, U_null_Vs, U_null_Vs);
		};

		template<auto v, auto n, auto p, auto d = MachineDispatch::initial_depth>
		constexpr auto replace_v0 = Replace_v0::template result<d, v, n, p>;
}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// insert sort:

/***********************************************************************************************************************/

namespace cctmp_program
{
// version 0:

	template<auto insert, auto cmp, auto... Vs>
	constexpr auto sort(nik_vp(l)(auto_pack<Vs...>*))
	{
		constexpr auto d		= MachineDispatch::initial_depth;
		constexpr auto list		= U_restore_T<decltype(l)>;
		constexpr auto n		= Overload::template result<Overload::find, cmp, list, insert>;

						// bad design: does not compose well with trampolining.
		constexpr auto sp		= NIK_FUNCTION_BLOCK(9, d, BN::split, n, Vs)(U_null_Vs);

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

// version 1:

	template<auto cmp = less_than_op<>>
	struct T_InsertSort_v1
	{
		template<key_type insert = 0, key_type p = 1, key_type v = 2>
		nik_ces contr_type program = controller
		<
			find   <                    >,
			copy   < insert , _register >,
			copy   < v      , _register >,
			shift  <                    >,
			copy   < p      , _register >,
			compel <          _value    >
		>;

		nik_ces auto m = MT::id;
		nik_ces auto i = MachineDispatch::initial_index;

		template<auto d, auto p, auto v, auto c = program<>>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i),

			U_Insert_v0, p, v

		NIK_END_MACHINE(U_pack_Vs<cmp, p, v>, U_null_Vs, U_null_Vs);
	};

	template<auto cmp = less_than_op<>>
	constexpr auto U_InsertSort_v1 = U_store_T<T_InsertSort_v1<cmp>>;

	template<auto list, auto insert, auto cmp = less_than_op<>, auto d = MachineDispatch::initial_depth>
	constexpr auto insert_sort_v1 = T_InsertSort_v1<cmp>::template result<d, list, insert>;
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

			copy      < p , _register , _value >
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
			shift    <                       >,
			multiply <             _value    >,

			// exit_case:

			copy     < one       , _constant , _value >
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

		/*
		 * (LOC, param) (VAR, [n, _register, 0]) (VAR, [p, _register, 1]) (;)
		 * (LOC, const) (VAR, [is_zero, _constant, 0]) (VAR, [multiply, _constant, 1]) (VAR, [decrement, _constant, 2]) (;)
		 * (LOC, arg) (;)
		 * (LABEL, start) (;)
		 * (IF) (LP) (VAR, is_zero) (VAR, n) (RP) (INSTR, goto) (LABEL, exit_case) (;)
		 * (VAR, p) (=) (VAR, multiply) (VAR, n) (VAR, p) (;)
		 * (VAR, n) (=) (VAR, decrement) (VAR, n) (;)
		 * (INSTR, goto) (LABEL, start) (;)
		 * (LABEL, exit_case) (;)
		 * (INSTR, return) (VAR, p) (;)
		*/


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
			key_type m1			=  1,
			key_type m2			=  2,

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
			copy   < m2        , _register >,
			compel <                       >,

			copy   < fibonacci , _constant >,
			copy   < m1        , _register >,
			compel <                       >,

			shift  <                       >,
			add    <             _value    >,

			// exit_case:

			copy   < one       , _constant , _value >
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

/*
	struct Fibonacci_v1
	{
		template
		<
			// registers:

			key_type n			=  0,
			key_type m1			=  1,
			key_type m2			=  2,

			// constants:

			key_type one			=  0,
			key_type fibonacci		=  1,
			key_type is_0_or_1		=  2,

			// labels:

			key_type exit_case		= 13
		>
		nik_ces contr_type program = controller
		<
			copy      < is_memoized , _constant >,
			copy      < n           , _constant >,
			shift     <                         >,
			apply     <                         >,
			branch    <               look_case >,

			copy      < fibonacci   , _constant >,
			copy      < m2          , _register >,
			compel    <                         >,

			copy      < fibonacci   , _constant >,
			copy      < m1          , _register >,
			compel    <                         >,

			copy      < _zero       , _memoized >,
			copy      < _one        , _memoized >,
			add       <               _value    >,

			// look_case:

			// exit_case:

			copy   < one       , _constant , _value >
		>;

		template<typename T> nik_ces bool is_0_or_1(T n) { return (n == 0) || (n == 1); }

		template<auto d, auto n>
		nik_ces auto result = start<d, program<>, n, n-1, n-2>
		(
			U_pack_Vs
			<
				decltype(n){_one},
				U_store_T<Fibonacci_v1>,
				is_0_or_1<decltype(n)>
			>
		);
	};

	template<auto n, auto d = MachineDispatch::initial_depth>
	constexpr auto fibonacci_v1 = Fibonacci_v0::template result<d, n>;
*/
}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

