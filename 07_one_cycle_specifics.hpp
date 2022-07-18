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

	using key_type						= typename cctmp::key_type;

	template<auto U> using T_store_U			= typename cctmp::template T_store_U<U>;

	template<typename T> nik_ce auto U_store_T		= cctmp::template U_store_T<T>;
	template<auto... Vs> nik_ce auto U_pack_Vs		= cctmp::template U_pack_Vs<Vs...>;

	template<auto... Vs> nik_ce auto overload		= cctmp::template overload<Vs...>;

	nik_ce auto _id_					= cctmp::_id_;

	nik_ce auto _same_					= cctmp::_same_;
	nik_ce auto _if_then_else_				= cctmp::_if_then_else_;

	template<auto... Vs> nik_ce auto _argcompose_		= cctmp_generics::template _argcompose_<Vs...>;
	template<auto... Vs> nik_ce auto _side_			= cctmp_generics::template _side_<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// conveniences:

/***********************************************************************************************************************/

// same:

	template<auto V0, auto V1>
	nik_ce auto same = overload<_same_, V0, V1>;

// if_then_else:

	template<auto p, auto a, auto c>
	nik_ce auto if_then_else = overload<_if_then_else_, p, a, c>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/


// operators:

/***********************************************************************************************************************/

// member value:

	struct T_member_value
	{
		template<auto U>
		nik_ces auto result = T_store_U<U>::value;

	}; nik_ce auto U_member_value = U_store_T<T_member_value>;

	template<auto U>
	nik_ce auto member_value = T_member_value::template result<U>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tags:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// direct:

/***********************************************************************************************************************/

// label:

	template<auto f> struct _precycle_label				{ nik_ces auto value = f; };
	template<auto f> struct _cycle_label				{ nik_ces auto value = f; };
	template<auto f> struct _postcycle_label			{ nik_ces auto value = f; };

	template<auto f> struct _match_label				{ nik_ces auto value = f; };
	template<auto f> struct _postmatch_label			{ nik_ces auto value = f; };

	template<auto f> struct _done_label				{ nik_ces auto value = f; };

	//

	template<auto f> nik_ce auto _precycle_label_			= U_store_T<_precycle_label<f>>;
	template<auto f> nik_ce auto _cycle_label_			= U_store_T<_cycle_label<f>>;
	template<auto f> nik_ce auto _postcycle_label_			= U_store_T<_postcycle_label<f>>;

	template<auto f> nik_ce auto _match_label_			= U_store_T<_match_label<f>>;
	template<auto f> nik_ce auto _postmatch_label_			= U_store_T<_postmatch_label<f>>;

	template<auto f> nik_ce auto _done_label_			= U_store_T<_done_label<f>>;

/***********************************************************************************************************************/

// position:

	template<auto f> struct _out_position				{ nik_ces auto value = f; };
	template<auto f> struct _aux_position				{ nik_ces auto value = f; };
	template<auto f> struct _in_position				{ nik_ces auto value = f; };
	template<auto f> struct _car_in_position			{ nik_ces auto value = f; };
	template<auto f> struct _cdr_in_position			{ nik_ces auto value = f; };
	template<auto f> struct _end_position				{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _out_position_			= U_store_T<_out_position<f>>;
	template<auto f> nik_ce auto _aux_position_			= U_store_T<_aux_position<f>>;
	template<auto f> nik_ce auto _in_position_			= U_store_T<_in_position<f>>;
	template<auto f> nik_ce auto _car_in_position_			= U_store_T<_car_in_position<f>>;
	template<auto f> nik_ce auto _cdr_in_position_			= U_store_T<_cdr_in_position<f>>;
	template<auto f> nik_ce auto _end_position_			= U_store_T<_end_position<f>>;

/***********************************************************************************************************************/

// out:

	template<auto f> struct _pre_out_next				{ nik_ces auto value = f; };
	template<auto f> struct _out_next				{ nik_ces auto value = f; };
	template<auto f> struct _post_out_next				{ nik_ces auto value = f; };
	template<auto f> struct _match_out_next				{ nik_ces auto value = f; };
	template<auto f> struct _postmatch_out_next			{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _pre_out_next_			= U_store_T<_pre_out_next<f>>;
	template<auto f> nik_ce auto _out_next_				= U_store_T<_out_next<f>>;
	template<auto f> nik_ce auto _post_out_next_			= U_store_T<_post_out_next<f>>;
	template<auto f> nik_ce auto _match_out_next_			= U_store_T<_match_out_next<f>>;
	template<auto f> nik_ce auto _postmatch_out_next_		= U_store_T<_postmatch_out_next<f>>;

/***********************************************************************************************************************/

// aux:

	template<auto f> struct _aux_next				{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _aux_next_				= U_store_T<_aux_next<f>>;

/***********************************************************************************************************************/

// in:

	template<auto f> struct _pre_in_next				{ nik_ces auto value = f; };
	template<auto f> struct _in_next				{ nik_ces auto value = f; };
	template<auto f> struct _post_in_next				{ nik_ces auto value = f; };
	template<auto f> struct _match_in_next				{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _pre_in_next_			= U_store_T<_pre_in_next<f>>;
	template<auto f> nik_ce auto _in_next_				= U_store_T<_in_next<f>>;
	template<auto f> nik_ce auto _post_in_next_			= U_store_T<_post_in_next<f>>;
	template<auto f> nik_ce auto _match_in_next_			= U_store_T<_match_in_next<f>>;

/***********************************************************************************************************************/

// car in:

	template<auto f> struct _pre_car_in_next			{ nik_ces auto value = f; };
	template<auto f> struct _car_in_next				{ nik_ces auto value = f; };
	template<auto f> struct _post_car_in_next			{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _pre_car_in_next_			= U_store_T<_pre_car_in_next<f>>;
	template<auto f> nik_ce auto _car_in_next_			= U_store_T<_car_in_next<f>>;
	template<auto f> nik_ce auto _post_car_in_next_			= U_store_T<_post_car_in_next<f>>;

/***********************************************************************************************************************/

// cdr in:

	template<auto f> struct _pre_cdr_in_next			{ nik_ces auto value = f; };
	template<auto f> struct _cdr_in_next				{ nik_ces auto value = f; };
	template<auto f> struct _post_cdr_in_next			{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _pre_cdr_in_next_			= U_store_T<_pre_cdr_in_next<f>>;
	template<auto f> nik_ce auto _cdr_in_next_			= U_store_T<_cdr_in_next<f>>;
	template<auto f> nik_ce auto _post_cdr_in_next_			= U_store_T<_post_cdr_in_next<f>>;

/***********************************************************************************************************************/

// end:

	template<auto f> struct _pre_end_next				{ nik_ces auto value = f; };
	template<auto f> struct _end_next				{ nik_ces auto value = f; };
	template<auto f> struct _post_end_next				{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _pre_end_next_			= U_store_T<_pre_end_next<f>>;
	template<auto f> nik_ce auto _end_next_				= U_store_T<_end_next<f>>;
	template<auto f> nik_ce auto _post_end_next_			= U_store_T<_post_end_next<f>>;

/***********************************************************************************************************************/

// loop:

	template<auto f> struct _loop_predicate				{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _loop_predicate_			= U_store_T<_loop_predicate<f>>;

/***********************************************************************************************************************/

// act:

	template<auto f> struct _act_predicate				{ nik_ces auto value = f; };
	template<auto f> struct _post_act_predicate			{ nik_ces auto value = f; };

	template<auto f> struct _act_function				{ nik_ces auto value = f; };
	template<auto f> struct _post_act_function			{ nik_ces auto value = f; };

	//

	template<auto f> nik_ce auto _act_predicate_			= U_store_T<_act_predicate<f>>;
	template<auto f> nik_ce auto _post_act_predicate_		= U_store_T<_post_act_predicate<f>>;

	template<auto f> nik_ce auto _act_function_			= U_store_T<_act_function<f>>;
	template<auto f> nik_ce auto _post_act_function_		= U_store_T<_post_act_function<f>>;

/***********************************************************************************************************************/

// combine:

	template<auto f> struct _combine_function			{ nik_ces auto value = f; };
	template<auto f> struct _post_combine_function			{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _combine_function_			= U_store_T<_combine_function<f>>;
	template<auto f> nik_ce auto _post_combine_function_		= U_store_T<_post_combine_function<f>>;

/***********************************************************************************************************************/

// assign:

	// requires a _side_ tag to lift properly.

	template<auto f> struct _assign_function			{ nik_ces auto value = _side_<f>; };
	template<auto f> struct _post_assign_function			{ nik_ces auto value = _side_<f>; };
	template<auto f> struct _match_assign_function			{ nik_ces auto value = _side_<f>; };
	template<auto f> struct _postmatch_assign_function		{ nik_ces auto value = _side_<f>; };

	template<auto f> nik_ce auto _assign_function_			= U_store_T<_assign_function<f>>;
	template<auto f> nik_ce auto _post_assign_function_		= U_store_T<_post_assign_function<f>>;
	template<auto f> nik_ce auto _match_assign_function_		= U_store_T<_match_assign_function<f>>;
	template<auto f> nik_ce auto _postmatch_assign_function_	= U_store_T<_postmatch_assign_function<f>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// conceptual:

/***********************************************************************************************************************/

// label:

	// id:

		template<auto... Vs> struct _label			{ };

		template<auto... Vs> nik_ce auto _label_		= U_store_T<_label<Vs...>>;

	// location:

		template<auto f> struct _precycle			{ };
		template<auto f> struct _cycle				{ };
		template<auto f> struct _postcycle			{ };
		template<auto f> struct _match				{ };
		template<auto f> struct _postmatch			{ };
		template<auto f> struct _done				{ };

		template<auto f> nik_ce auto _precycle_			= U_store_T<_precycle<f>>;
		template<auto f> nik_ce auto _cycle_			= U_store_T<_cycle<f>>;
		template<auto f> nik_ce auto _postcycle_		= U_store_T<_postcycle<f>>;
		template<auto f> nik_ce auto _match_			= U_store_T<_match<f>>;
		template<auto f> nik_ce auto _postmatch_		= U_store_T<_postmatch<f>>;
		template<auto f> nik_ce auto _done_			= U_store_T<_done<f>>;

/***********************************************************************************************************************/

// position:

	// id:

		template<auto... Vs> struct _position			{ };

		template<auto... Vs> nik_ce auto _position_		= U_store_T<_position<Vs...>>;

	// location:

		template<auto f> struct _out				{ };
		template<auto f> struct _aux				{ };
		template<auto f> struct _in				{ };
		template<auto f> struct _car_in				{ };
		template<auto f> struct _cdr_in				{ };
		template<auto f> struct _end				{ };

		template<auto f> nik_ce auto _out_			= U_store_T<_out<f>>;
		template<auto f> nik_ce auto _in_			= U_store_T<_in<f>>;
		template<auto f> nik_ce auto _aux_			= U_store_T<_aux<f>>;
		template<auto f> nik_ce auto _car_in_			= U_store_T<_car_in<f>>;
		template<auto f> nik_ce auto _cdr_in_			= U_store_T<_cdr_in<f>>;
		template<auto f> nik_ce auto _end_			= U_store_T<_end<f>>;

/***********************************************************************************************************************/

// interval:

	struct Interval
	{
		nik_ces char open	[] = "()";
		nik_ces char closing	[] = "[)";
		nik_ces char closed	[] = "[]";
		nik_ces char opening	[] = "(]";
	};

	nik_ce auto _open	= Interval::open;
	nik_ce auto _closing	= Interval::closing;
	nik_ce auto _closed	= Interval::closed;
	nik_ce auto _opening	= Interval::opening;

	// out:

		template<auto... Vs> struct _out_ival			{ };
		template<auto... Vs> nik_ce auto _out_ival_		= U_store_T<_out_ival<Vs...>>;

	// in:

		template<auto... Vs> struct _in_ival			{ };
		template<auto... Vs> nik_ce auto _in_ival_		= U_store_T<_in_ival<Vs...>>;

	// type:

		template<auto f> struct _type				{ };
		template<auto f> nik_ce auto _type_			= U_store_T<_type<f>>;

	// next:

		template<auto f> struct _next				{ };
		template<auto f> nik_ce auto _next_			= U_store_T<_next<f>>;

	// prev:

		template<auto f> struct _prev				{ };
		template<auto f> nik_ce auto _prev_			= U_store_T<_prev<f>>;

/***********************************************************************************************************************/

// break:

	struct Break
	{
		nik_ces key_type primary	= 0;
		nik_ces key_type secondary	= 1;
		nik_ces key_type tertiary	= 2;
	};

	// id:

		template<auto... Vs> struct _break			{ };
		template<auto... Vs> nik_ce auto _break_		= U_store_T<_break<Vs...>>;

	// op:

		template<auto f> struct _op				{ };
		template<auto f> nik_ce auto _op_			= U_store_T<_op<f>>;

	// arg:

		template<auto f> struct _out_arg			{ };
		template<auto f> struct _aux_arg			{ };
		template<auto f> struct _in_arg				{ };
		template<auto f> struct _car_in_arg			{ };
		template<auto f> struct _cdr_in_arg			{ };
		template<auto f> struct _end_arg			{ };

		template<auto f> nik_ce auto _out_arg_			= U_store_T<_out_arg<f>>;
		template<auto f> nik_ce auto _in_arg_			= U_store_T<_in_arg<f>>;
		template<auto f> nik_ce auto _aux_arg_			= U_store_T<_aux_arg<f>>;
		template<auto f> nik_ce auto _car_in_arg_		= U_store_T<_car_in_arg<f>>;
		template<auto f> nik_ce auto _cdr_in_arg_		= U_store_T<_cdr_in_arg<f>>;
		template<auto f> nik_ce auto _end_arg_			= U_store_T<_end_arg<f>>;

/***********************************************************************************************************************/

// action:

	// id:

		template<auto... Vs> struct _action			{ };
		template<auto... Vs> nik_ce auto _action_		= U_store_T<_action<Vs...>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// translators:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// names:

/***********************************************************************************************************************/

	struct Translator
	{
		nik_ces key_type id		= 0;

		nik_ces key_type repeat		= 1;
		nik_ces key_type map		= 2;
		nik_ces key_type fold		= 3;
		nik_ces key_type find_first	= 4;
		nik_ces key_type find_all	= 5;
		nik_ces key_type zip		= 6;
		nik_ces key_type fasten		= 7;
		nik_ces key_type glide		= 8;
	};

	using TR = Translator;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// etc:

	template<template<key_type, typename...> class T_etc, key_type Key, auto... Vs>
	using T_tr = T_etc<Key, T_store_U<Vs>...>;

	template<template<key_type, typename...> class T_etc, key_type Key, auto... Vs>
	nik_ce auto tr_ = U_store_T<T_tr<T_etc, Key, Vs...>>;

/***********************************************************************************************************************/

// atomic:

	// labels:

		template<key_type, typename...> struct T_cycle;
		template<key_type, typename...> struct T_precycle;
		template<key_type, typename...> struct T_postcycle;
		template<key_type, typename...> struct T_match;
		template<key_type, typename...> struct T_postmatch;
		template<key_type, typename...> struct T_done;

	// positions:

		template<key_type, typename...> struct T_out;
		template<key_type, typename...> struct T_aux;
		template<key_type, typename...> struct T_in;
		template<key_type, typename...> struct T_car_in;
		template<key_type, typename...> struct T_cdr_in;
		template<key_type, typename...> struct T_end;

	// ival:

		template<key_type, typename...> struct T_is_left_open;
		template<key_type, typename...> struct T_is_right_closed;
		template<key_type, typename...> struct T_is_right_open;

		template<key_type, typename...> struct T_is_primary;
		template<key_type, typename...> struct T_is_secondary;
		template<key_type, typename...> struct T_is_tertiary;

	// cycle:

		template<key_type, typename...> struct T_loop_predicate;
		template<key_type, typename...> struct T_assign_function;
		template<key_type, typename...> struct T_next;

	// precycle:

		template<key_type, typename...> struct T_pre_next;

	// postcycle:

		template<key_type, typename...> struct T_post_assign_function;
		template<key_type, typename...> struct T_post_next;

// composite:

		template<key_type, typename...> struct T_label;
		template<key_type, typename...> struct T_position;

		template<key_type, typename...> struct T_ival;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// id:

/***********************************************************************************************************************/

// labels:

	template<auto Precycle  > struct T_precycle  <TR::id,  _precycle<Precycle  >> { nik_ces auto value = Precycle; };
	template<auto Cycle     > struct T_cycle     <TR::id,     _cycle<Cycle     >> { nik_ces auto value = Cycle; };
	template<auto Postcycle > struct T_postcycle <TR::id, _postcycle<Postcycle >> { nik_ces auto value = Postcycle; };
	template<auto Match     > struct T_match     <TR::id,     _match<Match     >> { nik_ces auto value = Match; };
	template<auto Postmatch > struct T_postmatch <TR::id, _postmatch<Postmatch >> { nik_ces auto value = Postmatch; };
	template<auto Done      > struct T_done      <TR::id,      _done<Done      >> { nik_ces auto value = Done; };

/***********************************************************************************************************************/

// positions:

	template<auto Out   > struct T_out    <TR::id, _out    <Out   >> { nik_ces auto value = Out; };
	template<auto Aux   > struct T_aux    <TR::id, _aux    <Aux   >> { nik_ces auto value = Aux; };
	template<auto In    > struct T_in     <TR::id, _in     <In    >> { nik_ces auto value = In; };
	template<auto CarIn > struct T_car_in <TR::id, _car_in <CarIn >> { nik_ces auto value = CarIn; };
	template<auto CdrIn > struct T_cdr_in <TR::id, _cdr_in <CdrIn >> { nik_ces auto value = CdrIn; };
	template<auto End   > struct T_end    <TR::id, _end    <End   >> { nik_ces auto value = End; };

/***********************************************************************************************************************/

// ival:

	// type:

		template<auto Ival>
		struct T_is_left_open<TR::id, _type<Ival>>
		{
			nik_ces auto value = (Ival[0] == '(');
		};

		template<auto Ival>
		struct T_is_right_closed<TR::id, _type<Ival>>
		{
			nik_ces auto value = (Ival[1] == ']');
		};

		template<auto Ival>
		struct T_is_right_open<TR::id, _type<Ival>>
		{
			nik_ces auto value = (Ival[1] == ')');
		};

	// is primary:

	//	template<typename Prev, typename IsPeek>
	//	struct T_is_primary<TR::id, Prev, IsPeek>
	//	{
	//		nik_ces auto is_last	= !same<Prev::value, _id_> && IsPeek::value;
	//		nik_ces auto value	=  if_then_else<is_last, Prev::value, _id_>;
	//	};

	// is tertiary:

		template<typename Ival, typename... Ivals>
		struct T_is_tertiary<TR::id, Ival, Ivals...>
		{
			nik_ces auto value = (Ival::value[1] == ')') && (... || (Ivals::value[1] == ']'));
		};

	// next:

		template<auto Op>
		struct T_next<TR::id, _prev<Op>>
		{
			nik_ces auto value = Op;
		};

		template<auto Op>
		struct T_next<TR::id, _next<Op>>
		{
			nik_ces auto value = Op;
		};

/***********************************************************************************************************************/

// precycle:

	// next:

		template<typename IsLeftOpen, typename Next>
		struct T_pre_next<TR::id, IsLeftOpen, Next>
		{
			nik_ces auto value = if_then_else<IsLeftOpen::value, Next::value, _id_>;
		};

/***********************************************************************************************************************/

// postcycle:

	// assign function:

		template<typename IsRightClosed, typename AssignFunc>
		struct T_post_assign_function<TR::id, IsRightClosed, AssignFunc>
		{
			nik_ces auto value = if_then_else<IsRightClosed::value, AssignFunc::value, _id_>;
		};

	// next:

		template<typename Ival0, typename Ival1, typename Next1>
		struct T_post_next<TR::id, Ival0, Ival1, Next1>
		{
			nik_ces auto is_next	= Ival0::is_right_closed::value && Ival1::is_right_open::value;
			nik_ces auto value	= if_then_else<is_next, Next1::value, _id_>;
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// repeat:

/***********************************************************************************************************************/

// label:

	template<auto _Precycle_, auto _Cycle_, auto _Postcycle_>
	struct T_label<TR::repeat, _label<_Precycle_, _Cycle_, _Postcycle_>>
	{
		nik_ces auto precycle		= tr_<  T_precycle, TR::id,  _Precycle_ >;
		nik_ces auto cycle		= tr_<     T_cycle, TR::id,     _Cycle_ >;
		nik_ces auto postcycle		= tr_< T_postcycle, TR::id, _Postcycle_ >;
	};

/***********************************************************************************************************************/

// position:

	template<auto _Out_, auto _End_, auto _In_>
	struct T_position<TR::repeat, _position<_Out_, _End_, _In_>>
	{
		nik_ces auto out	= tr_< T_out, TR::id, _Out_ >;
		nik_ces auto end	= tr_< T_end, TR::id, _End_ >;
		nik_ces auto in		= tr_<  T_in, TR::id,  _In_ >;
	};

/***********************************************************************************************************************/

// ival:

	template<auto _Type_, auto _Next_>
	struct T_ival<TR::repeat, _out_ival<_Type_, _Next_>>
	{
		nik_ces auto is_left_open	= tr_< T_is_left_open    , TR::id , _Type_ >;
		nik_ces auto is_right_closed	= tr_< T_is_right_closed , TR::id , _Type_ >;
		nik_ces auto is_right_open	= tr_< T_is_right_open   , TR::id , _Type_ >;
		nik_ces auto next		= tr_< T_next, TR::id, _Next_ >;
	};

/***********************************************************************************************************************/

// loop predicate:

	template<auto Op, auto OutArg, auto EndArg>
	struct T_loop_predicate<TR::repeat, _op<Op>, _out_arg<OutArg>, _end_arg<EndArg>>
	{
		nik_ces auto value = _argcompose_<Op, OutArg, EndArg>;
	};

/***********************************************************************************************************************/

// assign function:

	template<auto Op, auto OutArg, auto InArg>
	struct T_assign_function<TR::repeat, _op<Op>, _out_arg<OutArg>, _in_arg<InArg>>
	{
		nik_ces auto f		= _argcompose_<Op, OutArg, InArg>;
		nik_ces auto value	= _side_<f>;
	};

/***********************************************************************************************************************/

// cycle:

	template
	<
		auto _Op0_, auto _Arg01_, auto _Arg02_,
		auto _Op1_, auto _Arg11_, auto _Arg12_,

		typename Ival
	>
	struct T_cycle
	<
		TR::repeat,

		_break  < _Op0_ , _Arg01_ , _Arg02_ >,
		_action < _Op1_ , _Arg11_ , _Arg12_ >,

		Ival
	>
	{
		nik_ces auto loop_predicate		= tr_< T_loop_predicate , TR::repeat, _Op0_, _Arg01_, _Arg02_ >;
		nik_ces auto assign_function		= tr_< T_assign_function, TR::repeat, _Op1_, _Arg11_, _Arg12_ >;
		nik_ces auto out_next			= Ival::next;
	};

/***********************************************************************************************************************/

// precycle:

	template<typename Ival>
	struct T_precycle<TR::repeat, Ival>
	{
		nik_ces auto pre_out_next = tr_<T_pre_next, TR::id, Ival::is_left_open, Ival::next>;
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename Ival, typename Cycle>
	struct T_postcycle<TR::repeat, Ival, Cycle>
	{
		nik_ces auto post_assign_function = tr_
		<
			T_post_assign_function, TR::id, Ival::is_right_closed, Cycle::assign_function
		>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// map:

/***********************************************************************************************************************/

// label:

	template<typename Label>
	struct T_label<TR::map, Label> : public T_label<TR::repeat, Label> { };

/***********************************************************************************************************************/

// position:

	template<auto _Out_, auto _In_, auto _End_>
	struct T_position<TR::map, _position<_Out_, _In_, _End_>>
	{
		nik_ces auto out	= tr_< T_out, TR::id, _Out_ >;
		nik_ces auto in		= tr_<  T_in, TR::id,  _In_ >;
		nik_ces auto end	= tr_< T_end, TR::id, _End_ >;
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
		nik_ces auto out_is_left_open		= tr_< T_is_left_open    , TR::id , _OutType_ >;
		nik_ces auto out_prev			= tr_< T_next, TR::id, _OutPrev_ >;
		nik_ces auto out_next			= tr_< T_next, TR::id, _OutNext_ >;

		nik_ces auto in_is_left_open		= tr_< T_is_left_open    , TR::id , _InType_ >;
		nik_ces auto in_is_right_closed		= tr_< T_is_right_closed , TR::id , _InType_ >;
		nik_ces auto in_is_right_open		= tr_< T_is_right_open   , TR::id , _InType_ >;
		nik_ces auto in_prev			= tr_< T_next, TR::id, _InPrev_ >;
		nik_ces auto in_next			= tr_< T_next, TR::id, _InNext_ >;

	//	nik_ces auto is_primary			= tr_< T_is_primary   , TR::id, in_ival, out_ival >;
	//	nik_ces auto is_secondary		= tr_< T_is_secondary , TR::id, in_ival, out_ival >;
	//	nik_ces auto is_tertiary		= tr_< T_is_tertiary  , TR::id, in_ival, out_ival >;
	};

/***********************************************************************************************************************/

// loop predicate:

	template<typename IsTertiary, typename InNext, auto Op, auto InArg, auto EndArg>
	struct T_loop_predicate<TR::map, IsTertiary, InNext, _op<Op>, _in_arg<InArg>, _end_arg<EndArg>>
	{
		nik_ces auto in_arg	= IsTertiary::value ? InNext::value : InArg;
		nik_ces auto value	= _argcompose_<Op, in_arg, EndArg>;
	};

/***********************************************************************************************************************/

// assign function:

	template<typename Op, typename OutArg, typename InArg>
	struct T_assign_function<TR::map, Op, OutArg, InArg> : public T_assign_function<TR::repeat, Op, OutArg, InArg> { };

/***********************************************************************************************************************/

// cycle:

	template
	<
		auto _Op0_, auto _Arg01_, auto _Arg02_,
		auto _Op1_, auto _Arg11_, auto _Arg12_,

		typename Ival
	>
	struct T_cycle
	<
		TR::map,

		_break  < _Op0_ , _Arg01_ , _Arg02_ >,
		_action < _Op1_ , _Arg11_ , _Arg12_ >,

		Ival
	>
	{
		//	0. All intervals are tethered to the one with an explicitly declared endpoint.
		//	1. If prev and peek, reverse iterate end precycle.
		//	2. For each left endpoint, if open, iterate precycle.
		//	3. Evaluate the common (closing) loop, peeking if necessary.
		//	4. If the subject iterator is right closed, then assign postcycle.
		//	5. If (4), then for each other right endpoint, when open, iterate postcycle.
		//	6. If prev and peek, iterate end to reset postcycle.

		nik_ces auto loop_predicate		= tr_
							<
								T_loop_predicate, TR::map,
								Ival::is_tertiary, Ival::in_next,
								_Op0_, _Arg01_, _Arg02_
							>;
		nik_ces auto assign_function		= tr_< T_assign_function, TR::map, _Op1_, _Arg11_, _Arg12_ >;
		nik_ces auto out_next			= Ival::out_next;
		nik_ces auto in_next			= Ival::in_next;
	};

/***********************************************************************************************************************/

// precycle:

	template<typename Ival>
	struct T_precycle<TR::map, Ival>
	{
		nik_ces auto pre_end_next = tr_< T_pre_next, TR::id, Ival::is_primary       , Ival::in_prev  >;
		nik_ces auto pre_out_next = tr_< T_pre_next, TR::id, Ival::out_is_left_open , Ival::out_next >;
		nik_ces auto pre_in_next  = tr_< T_pre_next, TR::id, Ival::in_is_left_open  , Ival::in_next  >;
	};

/***********************************************************************************************************************/

// postcycle:

/*
	template<typename Ival, typename Cycle>
	struct T_postcycle<TR::map, Ival, Cycle>
	{
		nik_ces auto post_assign_function = tr_
		<
			T_post_assign_function, TR::id, cycle::in_ival, cycle::assign_function
		>;

		nik_ces auto post_out_next = tr_<T_post_next, TR::id, cycle::in_ival, cycle::out_ival, cycle::out_next>;
		nik_ces auto post_end_next = tr_<T_post_next, TR::id, cycle::in_ival, cycle::end_ival, cycle::end_next>;
	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find first:

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find all:

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// zip:

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fasten:

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// glide:

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_one_cycle_specs

