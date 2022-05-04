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
	constexpr contr_type block_program = controller
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
		nik_ces auto U_Segment_v0 = U_store_T<T_Segment_v0>;

		template<auto d, auto n>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, MT::id, block_program<>, MachineDispatch::initial_index)

		NIK_END_MACHINE(U_pack_Vs<U_Segment_v0, n>);
	};

	template<auto n>
	constexpr auto segment_v0 = Segment_v0::template result<MachineDispatch::initial_depth, n>;

// at:

	struct T_At_v0
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = p;
	};

	template<auto d, auto n, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto T_At_v0::result<d, n, p> = NIK_BLOCK(BN::sifter, d, 9, n, Vs);

	struct At_v0
	{
		nik_ces auto U_At_v0 = U_store_T<T_At_v0>;

		template<auto d, auto n, auto p>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, MT::id, block_program<>, MachineDispatch::initial_index)

		NIK_END_MACHINE(U_pack_Vs<U_At_v0, n, p>);
	};

	template<auto n, auto p>
	constexpr auto at_v0 = At_v0::template result<MachineDispatch::initial_depth, n, p>;

// cut:

// left:

	struct T_Left_v0
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = p;
	};

	template<auto d, auto n, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto T_Left_v0::result<d, n, p> = NIK_BLOCK(BN::left, d, 9, n, Vs)(U_null_Vs);

	struct Left_v0
	{
		nik_ces auto U_Left_v0 = U_store_T<T_Left_v0>;

		template<auto d, auto n, auto p>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, MT::id, block_program<>, MachineDispatch::initial_index)

		NIK_END_MACHINE(U_pack_Vs<U_Left_v0, n, p>);
	};

	template<auto n, auto p>
	constexpr auto left_v0 = Left_v0::template result<MachineDispatch::initial_depth, n, p>;

// right:

	struct T_Right_v0
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = p;
	};

	template<auto d, auto n, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto T_Right_v0::result<d, n, p> = NIK_BLOCK(BN::right, d, 9, n, Vs);

	struct Right_v0
	{
		nik_ces auto U_Right_v0 = U_store_T<T_Right_v0>;

		template<auto d, auto n, auto p>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, MT::id, block_program<>, MachineDispatch::initial_index)

		NIK_END_MACHINE(U_pack_Vs<U_Right_v0, n, p>);
	};

	template<auto n, auto p>
	constexpr auto right_v0 = Right_v0::template result<MachineDispatch::initial_depth, n, p>;

// fold:

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

			key_type n			=  0,
			key_type p			=  1,

			// constants:

			key_type is_zero		=  0,
			key_type multiply		=  1,
			key_type decrement		=  2,

			// labels:

			key_type exit_case		= 16
		>
		nik_ces contr_type program = controller
		<
			copy   < _constant , is_zero   >,
			copy   < _register , n         >,
			apply  <                       >,
			branch < exit_case             >,

			copy   < _constant , multiply  >,
			copy   < _register , n         >,
			copy   < _register , p         >,
			action <                       >,
			cut    < _register , p         >,
			paste  < _register             >,

			copy   < _constant , decrement >,
			copy   < _register , n         >,
			apply  <                       >,
			cut    < _register , n         >,
			paste  < _register             >,

			cycle  <                       >,

			// exit_case:

			copy   < _register , p         >,
			value  <                       >
		>;

		template<typename T> nik_ces bool is_zero(T n) { return (n == 0); }
		template<typename T> nik_ces T multiply(T m, T n) { return m*n; }
		template<typename T> nik_ces T decrement(T n) { return n-1; }

		template<auto d, auto n>
		nik_ces auto result = start<d, program<>, n, decltype(n){_one}>
		(
			U_pack_Vs
			<
				is_zero<decltype(n)>,
				Overload::multiply,
				decrement<decltype(n)>
			>
		);
	};

	template<auto n>
	constexpr auto factorial_v0 = Factorial_v0::template result<MachineDispatch::initial_depth, n>;

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
			key_type is_zero		=  2,
			key_type multiply		=  3,

			// labels:

			key_type exit_case		= 14
		>
		nik_ces contr_type program = controller
		<
			copy   < _constant , is_zero   >,
			copy   < _register , n         >,
			apply  <                       >,
			branch < exit_case             >,

			copy   < _constant , factorial >,
			copy   < _register , m         >,
			compel <                       >,
			cut    < _register , m         >,
			paste  < _register             >,

			copy   < _constant , multiply  >,
			copy   < _register , n         >,
			copy   < _register , m         >,
			action <                       >,
			value  <                       >,

			// exit_case:

			copy   < _constant , one       >,
			value  <                       >
		>;

		template<typename T> nik_ces bool is_zero(T n) { return (n == 0); }

		template<auto d, auto n>
		nik_ces auto result = start<d, program<>, n, n-1>
		(
			U_pack_Vs
			<
				decltype(n){_one},
				U_store_T<Factorial_v1>,
				is_zero<decltype(n)>,
				Overload::multiply
			>
		);
	};

	template<auto n>
	constexpr auto factorial_v1 = Factorial_v1::template result<MachineDispatch::initial_depth, n>;

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

//	template<auto n>
//	constexpr auto factorial_v2 = Factorial_v2::template result<MachineDispatch::initial_depth, n>;
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
			key_type add			=  3,

			// labels:

			key_type exit_case		= 19
		>
		nik_ces contr_type program = controller
		<
			copy   < _constant , is_0_or_1 >,
			copy   < _register , n         >,
			apply  <                       >,
			branch < exit_case             >,

			copy   < _constant , fibonacci >,
			copy   < _register , m1        >,
			compel <                       >,
			cut    < _register , m1        >,
			paste  < _register             >,

			copy   < _constant , fibonacci >,
			copy   < _register , m2        >,
			compel <                       >,
			cut    < _register , m2        >,
			paste  < _register             >,

			copy   < _constant , add       >,
			copy   < _register , m1        >,
			copy   < _register , m2        >,
			action <                       >,
			value  <                       >,

			// exit_case:

			copy   < _constant , one       >,
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
				is_0_or_1<decltype(n)>,
				Overload::add
			>
		);
	};

	template<auto n>
	constexpr auto fibonacci_v0 = Fibonacci_v0::template result<MachineDispatch::initial_depth, n>;
}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// unite sort:

/***********************************************************************************************************************/

namespace cctmp_program
{
// version 0:

	struct UniteSort_v0
	{
		template
		<
			// registers:

			index_type l_front	=  0,
			index_type r_front	=  1,

			// constants:

			index_type is_null	=  0,
			index_type less_than	=  1,
			index_type car		=  2,
			index_type cdr		=  3,
			index_type push		=  4,
			index_type cat		=  5,

			// arguments:

			index_type out_list	=  0,
			index_type left_list	=  1,
			index_type right_list	=  2,

			// labels:

			index_type loop_l	=  0,
			index_type loop_r	= 35,
			index_type done_l	= 47,
			index_type done_r	= 52
		>
		nik_ces contr_type program = controller
		<
			// loop_l:

			copy   < _constant , is_null    >,
			copy   < _argument , left_list  >,
			action <                        >,
			branch < done_l                 >,

			copy   < _constant , is_null    >,
			copy   < _argument , right_list >,
			action <                        >,
			branch < done_r                 >,

			copy   < _constant , car        >,
			copy   < _argument , left_list  >,
			action <                        >,
			cut    < _register , l_front    >,
			paste  < _register              >,

			copy   < _constant , car        >,
			copy   < _argument , right_list >,
			action <                        >,
			cut    < _register , r_front    >,
			paste  < _register              >,

			copy   < _constant , less_than  >,
			copy   < _register , l_front    >,
			copy   < _register , r_front    >,
			action <                        >,
			branch < loop_r                 >,

			copy   < _constant , push       >,
			copy   < _register , r_front    >,
			copy   < _argument , out_list   >,
			action <                        >,
			cut    < _argument , out_list   >,
			paste  < _argument              >,

			copy   < _constant , cdr        >,
			copy   < _argument , right_list >,
			action <                        >,
			cut    < _argument , right_list >,
			paste  < _argument              >,

			cycle  <                        >,

			// loop_r:

			copy   < _constant , push       >,
			copy   < _register , l_front    >,
			copy   < _argument , out_list   >,
			action <                        >,
			cut    < _argument , out_list   >,
			paste  < _argument              >,

			copy   < _constant , cdr        >,
			copy   < _argument , left_list  >,
			action <                        >,
			cut    < _argument , left_list  >,
			paste  < _argument              >,

			cycle  <                        >,

			// done_l:

			copy   < _constant , cat        >,
			copy   < _argument , out_list   >,
			copy   < _argument , right_list >,
			action <                        >,
			value  <                        >,

			// done_r:

			copy   < _constant , cat        >,
			copy   < _argument , out_list   >,
			copy   < _argument , left_list  >,
			action <                        >,
			value  <                        >
		>;

		template<auto d, auto l, auto r>
		nik_ces auto result = start<d, program<>, _zero, _zero>
		(
			U_pack_Vs
			<
				Overload::is_null,
				Overload::less_than,
				Overload::car,
				Overload::cdr,
				Overload::push,
				Overload::cat
			>,

			U_null_Vs, l, r
		);
	};

	template<auto l, auto r>
	constexpr auto unite_sort_v0 = UniteSort_v0::template result<MachineDispatch::initial_depth, l, r>;
}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// merge sort:

/***********************************************************************************************************************/

namespace cctmp_program
{
// version 0:

	struct T_at_most_one
	{
		template<auto p>
		nik_ces auto result = true;
	};

	template<auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto T_at_most_one::result<p> = (sizeof...(Vs) <= 1);

	struct T_half_size
	{
		template<auto p>
		nik_ces auto result = 0;
	};

	template<auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto T_half_size::result<p> = sizeof...(Vs) / 2;

	struct MergeSort_v0
	{
		template
		<
			// registers:

			index_type position	=  0,

			// constants:

			index_type at_most_one	=  0,
			index_type half_size	=  1,
			index_type left		=  2,
			index_type right	=  3,
			index_type unite_sort	=  4,
			index_type merge_sort	=  5,

			// arguments:

			index_type left_list	=  0,
			index_type right_list	=  1,

			// labels:

			index_type exit_case	= 36
		>
		nik_ces contr_type program = controller
		<
			copy   < _constant , at_most_one >,
			copy   < _argument , right_list  >,
			alias  <                         >,
			branch < exit_case               >,

			copy   < _constant , half_size   >,
			copy   < _argument , right_list  >,
			alias  <                         >,
			cut    < _register , position    >,
			paste  < _register               >,

			copy   < _constant , left        >,
			copy   < _register , position    >,
			copy   < _argument , right_list  >,
			compel <                         >,
			cut    < _argument , left_list   >,
			paste  < _argument               >,

			copy   < _constant , right       >,
			copy   < _register , position    >,
			copy   < _argument , right_list  >,
			compel <                         >,
			cut    < _argument , right_list  >,
			paste  < _argument               >,

			copy   < _constant , merge_sort  >,
			copy   < _argument , left_list   >,
			compel <                         >,
			cut    < _argument , left_list   >,
			paste  < _argument               >,

			copy   < _constant , merge_sort  >,
			copy   < _argument , right_list  >,
			compel <                         >,
			cut    < _argument , right_list  >,
			paste  < _argument               >,

			copy   < _constant , unite_sort  >,
			copy   < _argument , left_list   >,
			copy   < _argument , right_list  >,
			compel <                         >,
			value  <                         >,

			// exit_case:

			copy   < _argument , right_list  >,
			value  <                         >
		>;

		template<auto d, auto p>
		nik_ces auto result = start<d, program<>, _zero>
		(
			U_pack_Vs
			<
				U_store_T<T_at_most_one>,
				U_store_T<T_half_size>,
				U_store_T<Left_v0>,
				U_store_T<Right_v0>,
				U_store_T<UniteSort_v0>,
				U_store_T<MergeSort_v0>
			>,

			U_null_Vs, p
		);
	};

	template<auto p>
	constexpr auto merge_sort_v0 = MergeSort_v0::template result<MachineDispatch::initial_depth, p>;
}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

