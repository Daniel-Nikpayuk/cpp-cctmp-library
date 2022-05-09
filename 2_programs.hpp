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

namespace cctmp_program { using namespace cctmp; }

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// block:

namespace cctmp_program
{
	template<key_type dec = _two>
	constexpr contr_type compel_program = controller
	<
		compel < dec >,
		value  <     >
	>;

/***********************************************************************************************************************/

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

	struct Segment_v0
	{
		nik_ces auto m			= MT::id;
		nik_ces auto c			= compel_program<>;
		nik_ces auto i			= MachineDispatch::initial_index;
		nik_ces auto U_Segment_v0	= U_store_T<T_Segment_v0>;

		template<auto d, auto n>
		nik_ces auto result		= NIK_BEGIN_MACHINE(d, m, c, i)
							NIK_END_MACHINE(U_pack_Vs<U_Segment_v0, n>);
	};

	template<auto n, auto d = MachineDispatch::initial_depth>
	constexpr auto segment_v0 = Segment_v0::template result<d, n>;

// at:

	struct T_At_v0
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = p;
	};

	template<auto d, auto n, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto T_At_v0::result<d, n, p> = NIK_VARIABLE_BLOCK(9, d, BN::sifter, n, Vs);

	struct At_v0
	{
		nik_ces auto m		= MT::id;
		nik_ces auto c		= compel_program<>;
		nik_ces auto i		= MachineDispatch::initial_index;
		nik_ces auto U_At_v0	= U_store_T<T_At_v0>;

		template<auto d, auto n, auto p>
		nik_ces auto result	= NIK_BEGIN_MACHINE(d, m, c, i)
						NIK_END_MACHINE(U_pack_Vs<U_At_v0, n, p>);
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	constexpr auto at_v0 = At_v0::template result<d, n, p>;

// cut:

// left:

	struct T_Left_v0
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = p;
	};

	template<auto d, auto n, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto T_Left_v0::result<d, n, p> = NIK_FUNCTION_BLOCK(9, d, BN::left, n, Vs)(U_null_Vs);

	struct Left_v0
	{
		nik_ces auto m		= MT::id;
		nik_ces auto c		= compel_program<>;
		nik_ces auto i		= MachineDispatch::initial_index;
		nik_ces auto U_Left_v0	= U_store_T<T_Left_v0>;

		template<auto d, auto n, auto p>
		nik_ces auto result	= NIK_BEGIN_MACHINE(d, m, c, i)
						NIK_END_MACHINE(U_pack_Vs<U_Left_v0, n, p>);
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	constexpr auto left_v0 = Left_v0::template result<d, n, p>;

// right:

	struct T_Right_v0
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = p;
	};

	template<auto d, auto n, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto T_Right_v0::result<d, n, p> = NIK_VARIABLE_BLOCK(9, d, BN::right, n, Vs);

	struct Right_v0
	{
		nik_ces auto m		= MT::id;
		nik_ces auto c		= compel_program<>;
		nik_ces auto i		= MachineDispatch::initial_index;
		nik_ces auto U_Right_v0	= U_store_T<T_Right_v0>;

		template<auto d, auto n, auto p>
		nik_ces auto result	= NIK_BEGIN_MACHINE(d, m, c, i)
						NIK_END_MACHINE(U_pack_Vs<U_Right_v0, n, p>);
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	constexpr auto right_v0 = Right_v0::template result<d, n, p>;

// split:

	struct T_Split_v0
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = p;
	};

	template<auto d, auto n, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto T_Split_v0::result<d, n, p> = NIK_FUNCTION_BLOCK(9, d, BN::split, n, Vs)(U_null_Vs);

	struct Split_v0
	{
		nik_ces auto m		= MT::id;
		nik_ces auto c		= compel_program<>;
		nik_ces auto i		= MachineDispatch::initial_index;
		nik_ces auto U_Split_v0	= U_store_T<T_Split_v0>;

		template<auto d, auto n, auto p>
		nik_ces auto result	= NIK_BEGIN_MACHINE(d, m, c, i)
						NIK_END_MACHINE(U_pack_Vs<U_Split_v0, n, p>);
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	constexpr auto split_v0 = Split_v0::template result<d, n, p>;

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

	struct Fold_v0
	{
		nik_ces auto m		= MT::id;
		nik_ces auto c		= compel_program<>;
		nik_ces auto i		= MachineDispatch::initial_index;
		nik_ces auto U_Fold_v0	= U_store_T<T_Fold_v0>;

		template<auto d, auto op, auto V, auto l>
		nik_ces auto result	= NIK_BEGIN_MACHINE(d, m, c, i)
						NIK_END_MACHINE(U_pack_Vs<U_Fold_v0, op, V, l>);
	};

	template<auto op, auto V, auto l, auto d = MachineDispatch::initial_depth>
	constexpr auto fold_v0 = Fold_v0::template result<d, op, V, l>;
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

			copy      < p , _register >,
			value     <               >
		>;

		template<auto d, auto n>
		nik_ces auto result = start<d, program<>, n, decltype(n){_one}>();
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

			key_type exit_case		= 12
		>
		nik_ces contr_type program = controller
		<
			copy     < n         , _register >,
			is_zero  <                       >,
			branch   <             exit_case >,

			copy     < factorial , _constant >,
			copy     < m         , _register >,
			compel   <                       >,
			cut      < m         , _register >,
			paste    <             _register >,

			copy     < n         , _register >,
			copy     < m         , _register >,
			multiply <                       >,
			value    <                       >,

			// exit_case:

			copy     < one       , _constant >,
			value    <                       >
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

			key_type exit_case		= 18
		>
		nik_ces contr_type program = controller
		<
			copy   < is_0_or_1 , _constant >,
			copy   < n         , _register >,
			apply  <                       >,
			branch <             exit_case >,

			copy   < fibonacci , _constant >,
			copy   < m1        , _register >,
			compel <                       >,
			cut    < m1        , _register >,
			paste  <             _register >,

			copy   < fibonacci , _constant >,
			copy   < m2        , _register >,
			compel <                       >,
			cut    < m2        , _register >,
			paste  <             _register >,

			copy   < m1        , _register >,
			copy   < m2        , _register >,
			add    <                       >,
			value  <                       >,

			// exit_case:

			copy   < one       , _constant >,
			value  <                       >
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
}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// insert sort:

/***********************************************************************************************************************/

namespace cctmp_program
{
// version 0:

	constexpr index_type first(const bool *k, const bool *e)
	{
		const bool *b = k;

		while (k != e && !*k) ++k;

		return k - b;
	}

	template<auto insert, auto... Vs, key_type Op, auto... F>
	constexpr auto sort(nik_avp(auto_pack<Vs...>*), nik_avp(auto_pack<Op, F...>*))
	{
		constexpr auto arr		= array<bool, Overload::template result<Op, F..., insert, Vs>...>;
		constexpr index_type size	= sizeof...(Vs);

		constexpr auto d		= MachineDispatch::initial_depth;
		constexpr auto n		= first(arr, arr + size);

						// bad design: does not compose well with trampolining.
		constexpr auto sp		= NIK_FUNCTION_BLOCK(9, d, BN::split, n, Vs)(U_null_Vs);

		return Overload::template result<Overload::unite, sp.v1, insert, sp.v2>;
	}

	template<auto LT = U_pack_Vs<Overload::less_than>>
	struct T_InsertSort_v0
	{
		template<auto list, auto insert>
		nik_ces auto result = sort<insert>(list, LT);
	};

	template<auto LT = U_pack_Vs<Overload::less_than>>
	constexpr auto U_InsertSort_v0 = U_store_T<T_InsertSort_v0<LT>>;

	template<auto insert, auto list, auto LT = U_pack_Vs<Overload::less_than>>
	constexpr auto insert_sort_v0 = T_InsertSort_v0<LT>::template result<insert, list>;
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
		auto comp	= U_pack_Vs<Overload::less_than>,
		auto d		= MachineDispatch::initial_depth
	>
	constexpr auto sort_v0 = Fold_v0::template result
	<
		d,
		U_pack_Vs<Overload::alias, U_InsertSort_v0<comp>>,
		U_null_Vs,
		l
	>;
}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

