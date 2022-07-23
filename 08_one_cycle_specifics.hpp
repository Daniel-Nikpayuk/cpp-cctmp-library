/************************************************************************************************************************
**
** Copyright 2021-2022 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

namespace cctmp_one_cycle_specs {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// etc:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// names:

	struct TranslatorName
	{
		nik_ces key_type id		= 0;

		// singular:

		nik_ces key_type repeat		= 1;
		nik_ces key_type fold		= 2;
		nik_ces key_type find_first	= 3;
		nik_ces key_type find_all	= 4;

		// plural:

		nik_ces key_type map		= 5;
		nik_ces key_type zip		= 6;
		nik_ces key_type fasten		= 7;
		nik_ces key_type glide		= 8;
	};

	using TN = TranslatorName;

/***********************************************************************************************************************/

// structs:

	template<key_type, typename...> struct T_label;
	template<key_type, typename...> struct T_position;

	template<key_type, typename...> struct T_ival;
	template<key_type, typename...> struct T_axis;

	template<key_type, typename...> struct T_ivals;

	template<key_type, typename...> struct T_cycle;
	template<key_type, typename...> struct T_precycle;
	template<key_type, typename...> struct T_postcycle;

/***********************************************************************************************************************/

// etc:

	template<template<key_type, typename...> class Etc, key_type Key, typename... Ts>
	using T_etc = Etc<Key, Ts...>;

	template<template<key_type, typename...> class Etc, key_type Key, typename... Ts>
	nik_ce auto U_etc = U_store_T<T_etc<Etc, Key, Ts...>>;

// tr:

	template<template<key_type, typename...> class Etc, key_type Key, auto... Vs>
	using T_tr = Etc<Key, T_store_U<Vs>...>;

	template<template<key_type, typename...> class Etc, key_type Key, auto... Vs>
	nik_ce auto U_tr = U_store_T<T_tr<Etc, Key, Vs...>>;

/***********************************************************************************************************************/

// ival:

	// id:

		template<typename _Note>
		struct T_ival<TR::id, _Note>
		{
			nik_ces auto is_left_open	= U_etc < T_is_left_open    , TR::id , _Note >;
			nik_ces auto is_right_open	= U_etc < T_is_right_open   , TR::id , _Note >;
			nik_ces auto is_right_closed	= U_etc < T_is_right_closed , TR::id , _Note >;
		};

/***********************************************************************************************************************/

// axis:

	// unidirectional:

		template<typename _Next>
		struct T_axis<TR::id, _Next>
		{
			nik_ces auto next = U_etc < T_next , TR::id , _Next >;
		};

	// bidirectional:

		template<typename _Next, typename _Prev>
		struct T_axis<TR::id, _Next, _Prev>
		{
			nik_ces auto prev = U_etc < T_next , TR::id , _Prev >;
			nik_ces auto next = U_etc < T_next , TR::id , _Next >;
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// repeat (singular):

/***********************************************************************************************************************/

// label:

	template<auto _Precycle_, auto _Cycle_, auto _Postcycle_>
	struct T_label<TR::repeat, _label<_Precycle_, _Cycle_, _Postcycle_>>
	{
		nik_ces auto precycle	= U_tr <  T_precycle, TR::id,  _Precycle_ >;
		nik_ces auto cycle	= U_tr <     T_cycle, TR::id,     _Cycle_ >;
		nik_ces auto postcycle	= U_tr < T_postcycle, TR::id, _Postcycle_ >;
	};

/***********************************************************************************************************************/

// position:

	template<auto _Out_, auto _End_, auto _In_>
	struct T_position<TR::repeat, _position<_Out_, _End_, _In_>>
	{
		nik_ces auto out	= U_tr < T_out, TR::id, _Out_ >;
		nik_ces auto end	= U_tr < T_end, TR::id, _End_ >;
		nik_ces auto in		= U_tr <  T_in, TR::id,  _In_ >;
	};

/***********************************************************************************************************************/

// ivals:

	template<auto _Type_, auto _Next_>
	struct T_ivals<TR::repeat, _out_ival<_Type_, _Next_>>
	{
		nik_ces auto out_ival	= U_tr < T_ival, TR::id, _Type_ >;
		nik_ces auto out_axis	= U_tr < T_axis, TR::id, _Next_ >;
	};

/***********************************************************************************************************************/

// cycle:

	template
	<
		auto _Op0_, auto _Arg01_, auto _Arg02_,
		auto _Op1_, auto _Arg11_, auto _Arg12_,

		typename Ivals
	>
	struct T_cycle
	<
		TR::repeat,

		_break  < _Op0_ , _Arg01_ , _Arg02_ >,
		_action < _Op1_ , _Arg11_ , _Arg12_ >,

		Ivals
	>
	{
		nik_ces auto loop_predicate		= U_tr < T_loop_predicate , TR::repeat, _Op0_, _Arg01_, _Arg02_ >;
		nik_ces auto assign_function		= U_tr < T_assign_function, TR::repeat, _Op1_, _Arg11_, _Arg12_ >;

		nik_ces auto out_next			= U_tr < T_cycle_next, TR::id, Ivals::out_axis >;
	};

/***********************************************************************************************************************/

// precycle:

	template<typename Ivals>
	struct T_precycle<TR::repeat, Ivals>
	{
		nik_ces auto pre_out_next = U_tr<T_pre_next, TR::id, Ivals::out_ival, Ivals::out_axis>;
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename Ivals, typename Cycle>
	struct T_postcycle<TR::repeat, Ivals, Cycle>
	{
		nik_ces auto post_assign_function = U_tr
		<
			T_post_assign_function, TR::id, Ivals::out_ival, U_store_T<Cycle>
		>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold (singular):

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find first (singular):

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find all (singular):

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// map (plural):

/***********************************************************************************************************************/

// label:

	template<typename Label>
	struct T_label<TR::map, Label> : public T_label<TR::repeat, Label> { };

/***********************************************************************************************************************/

// position:

	template<auto _Out_, auto _In_, auto _End_>
	struct T_position<TR::map, _position<_Out_, _In_, _End_>>
	{
		nik_ces auto out	= U_tr < T_out, TR::id, _Out_ >;
		nik_ces auto in		= U_tr <  T_in, TR::id,  _In_ >;
		nik_ces auto end	= U_tr < T_end, TR::id, _End_ >;
	};

/***********************************************************************************************************************/

// ival:

	template
	<
		auto _OutType_, auto _OutNext_, auto _OutPrev_,
		auto  _InType_, auto  _InNext_, auto  _InPrev_
	>
	struct T_ival
	<
		TR::map,

		_out_ival < _OutType_ , _OutNext_ , _OutPrev_ >,
		 _in_ival <  _InType_ ,  _InNext_ ,  _InPrev_ >
	>
	{
		nik_ces auto out_ival	= U_tr < T_ival, TR::id, _OutType_             >;
		nik_ces auto out_axis	= U_tr < T_axis, TR::id, _OutNext_ , _OutPrev_ >;

		nik_ces auto in_ival	= U_tr < T_ival, TR::id,  _InType_             >;
		nik_ces auto in_axis	= U_tr < T_axis, TR::id,  _InNext_ ,  _InPrev_ >;
	};

/***********************************************************************************************************************/

// axis:

	template<typename Ivals>
	struct T_axis<TR::map, Ivals>
	{
		nik_ces auto is_last		= U_tr < T_is_last, TR::id , Ivals::in_ival , Ivals::out_ival >;

		nik_ces auto is_primary		= U_tr < T_is_primary   , TR::id, is_last , Ivals::in_ival              >;
		nik_ces auto is_secondary	= U_tr < T_is_secondary , TR::id, is_last , is_primary, Ivals::out_ival >;
		nik_ces auto is_tertiary	= U_tr < T_is_tertiary  , TR::id, is_last , is_primary, is_secondary    >;
	};

/***********************************************************************************************************************/

// cycle:

	template
	<
		auto _Op0_, auto _Arg01_, auto _Arg02_,
		auto _Op1_, auto _Arg11_, auto _Arg12_,

		typename Axis, typename Ivals
	>
	struct T_cycle
	<
		TR::map,

		_break  < _Op0_ , _Arg01_ , _Arg02_ >,
		_action < _Op1_ , _Arg11_ , _Arg12_ >,

		Axis, Ivals
	>
	{
		//	0. All intervals are tethered to the one with an explicitly declared endpoint.
		//	1. If prev and peek, reverse iterate end precycle.
		//	2. For each left endpoint, if open, iterate precycle.
		//	3. Evaluate the common (closing) loop, peeking if necessary.
		//	4. If the subject iterator is right closed, then assign postcycle.
		//	5. If (4), then for each other right endpoint, when open, iterate postcycle.
		//	6. If prev and peek, iterate end to reset postcycle.

		nik_ces auto loop_predicate		= U_tr
							<
								T_loop_predicate, TR::map,
								Axis::is_tertiary, Ivals::in_axis,
								_Op0_, _Arg01_, _Arg02_
							>;
		nik_ces auto assign_function		= U_tr< T_assign_function, TR::map, _Op1_, _Arg11_, _Arg12_ >;

		nik_ces auto out_next			= U_tr < T_cycle_next, TR::id, Ivals::out_axis >;
		nik_ces auto in_next			= U_tr < T_cycle_next, TR::id, Ivals::in_axis >;
	};

/***********************************************************************************************************************/

// precycle:

	template<typename Axis, typename Ivals>
	struct T_precycle<TR::map, Axis, Ivals>
	{
		nik_ces auto pre_end_next = U_tr < T_pre_t_prev , TR::id, Axis::is_primary , Ivals::in_axis  >;
		nik_ces auto pre_out_next = U_tr < T_pre_next   , TR::id, Ivals::out_ival  , Ivals::out_axis >;
		nik_ces auto pre_in_next  = U_tr < T_pre_next   , TR::id, Ivals::in_ival   , Ivals::in_axis  >;
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename Axis, typename Ivals, typename Cycle>
	struct T_postcycle<TR::map, Axis, Ivals, Cycle>
	{
		nik_ces auto post_assign_function = U_tr
		<
			T_post_assign_function, TR::id, Ivals::in_ival, U_store_T<Cycle>
		>;

		nik_ces auto post_out_next = U_tr <T_post_s_next , TR::id, Axis::is_secondary , U_store_T<Ivals> >;
		nik_ces auto post_in_next  = U_tr <T_post_p_next , TR::id, Axis::is_primary   , Ivals::in_axis   >;
		nik_ces auto post_end_prev = U_tr <T_post_t_next , TR::id, Axis::is_primary   , Ivals::in_axis   >;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// zip (plural):

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fasten (plural):

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// glide (plural):

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_one_cycle_specs

