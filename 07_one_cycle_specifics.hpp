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
	using AOP						= typename cctmp::AOP;

	template<auto U> using T_store_U			= typename cctmp::template T_store_U<U>;
	template<auto... Vs> using T_pack_Vs			= typename cctmp::template T_pack_Vs<Vs...>;

	nik_ce auto _zero					= cctmp::_zero;
	nik_ce auto _one					= cctmp::_one;
	nik_ce auto _two					= cctmp::_two;
	nik_ce auto _three					= cctmp::_three;
	nik_ce auto _four					= cctmp::_four;
	nik_ce auto _five					= cctmp::_five;

	nik_ce auto _id_					= cctmp::_id_;
	nik_ce auto _equal_					= cctmp::_equal_;
	nik_ce auto _assign_					= cctmp::_assign_;
	nik_ce auto _dereference_				= cctmp::_dereference_;

	nik_ce auto U_similar					= cctmp::U_similar;
	nik_ce auto U_map					= cctmp::U_map;
	nik_ce auto U_custom					= cctmp::U_custom;

	template<typename T> nik_ce auto U_store_T		= cctmp::template U_store_T<T>;
	template<template<auto...> class B>
	nik_ce auto U_store_B					= cctmp::template U_store_B<B>;

	template<auto... Vs> nik_ce auto U_pack_Vs		= cctmp::template U_pack_Vs<Vs...>;

	template<auto... Vs> nik_ce auto _constant_		= cctmp::template _constant_<Vs...>;
	template<auto... Vs> nik_ce auto _increment_		= cctmp::template _increment_<Vs...>;
	template<auto... Vs> nik_ce auto _decrement_		= cctmp::template _decrement_<Vs...>;

	template<auto... Vs> nik_ce auto alias			= cctmp::template alias<Vs...>;
	template<auto... Vs> nik_ce auto unpack_		= cctmp::template unpack_<Vs...>;

	template<auto... Vs> nik_ce auto U_partial		= cctmp::template U_partial<Vs...>;
	template<auto... Vs> nik_ce auto H_partial		= cctmp::template H_partial<Vs...>;
	nik_ce auto H_partial_similar				= H_partial<U_similar>;

	template<auto... Vs> nik_ce auto pack_write		= cctmp_functional::template pack_write<Vs...>;

	nik_ce auto _d_assign_i_				= cctmp_generics::template _argcompose_
								<
									_assign_, _dereference_, _id_
								>;

	template<auto... Vs> nik_ce auto _argcompose_		= cctmp_generics::template _argcompose_<Vs...>;
	template<auto... Vs> nik_ce auto _side_			= cctmp_generics::template _side_<Vs...>;

	nik_ce auto  H_repeat_specification			= cctmp_one_cycle_generics::H_repeat_specification;
	nik_ce auto  H_map_specification			= cctmp_one_cycle_generics::H_map_specification;
	nik_ce auto  H_fold_specification			= cctmp_one_cycle_generics::H_fold_specification;
	nik_ce auto  H_find_first_specification			= cctmp_one_cycle_generics::H_find_first_specification;
	nik_ce auto  H_find_all_specification			= cctmp_one_cycle_generics::H_find_all_specification;
	nik_ce auto  H_zip_specification			= cctmp_one_cycle_generics::H_zip_specification;
	nik_ce auto  H_fasten_specification			= cctmp_one_cycle_generics::H_fasten_specification;
	nik_ce auto  H_glide_specification			= cctmp_one_cycle_generics::H_glide_specification;

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

	template<auto f> struct _pre_end_prev				{ nik_ces auto value = f; };
	template<auto f> struct _end_prev				{ nik_ces auto value = f; };

	template<auto f> struct _end_next				{ nik_ces auto value = f; };
	template<auto f> struct _post_end_next				{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _pre_end_prev_			= U_store_T<_pre_end_prev<f>>;
	template<auto f> nik_ce auto _end_prev_				= U_store_T<_end_prev<f>>;

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

		template<auto f> struct _precycle			{ nik_ces auto value = f; };
		template<auto f> struct _cycle				{ nik_ces auto value = f; };
		template<auto f> struct _postcycle			{ nik_ces auto value = f; };
		template<auto f> struct _match				{ nik_ces auto value = f; };
		template<auto f> struct _postmatch			{ nik_ces auto value = f; };
		template<auto f> struct _done				{ nik_ces auto value = f; };

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

		template<auto f> struct _out				{ nik_ces auto value = f; };
		template<auto f> struct _aux				{ nik_ces auto value = f; };
		template<auto f> struct _in				{ nik_ces auto value = f; };
		template<auto f> struct _car_in				{ nik_ces auto value = f; };
		template<auto f> struct _cdr_in				{ nik_ces auto value = f; };
		template<auto f> struct _end				{ nik_ces auto value = f; };

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

	using Ival = Interval;

	template<auto ival> nik_ce auto is_left_open			= (ival[0] == '(');
	template<auto ival> nik_ce auto is_right_closed			= (ival[1] == ']');

	// out:

		template<auto... Vs> struct _out_ival			{ };
		template<auto... Vs> nik_ce auto _out_ival_		= U_store_T<_out_ival<Vs...>>;

	// in:

		template<auto... Vs> struct _in_ival			{ };
		template<auto... Vs> nik_ce auto _in_ival_		= U_store_T<_in_ival<Vs...>>;

	// type:

		template<auto f> struct _type				{ nik_ces auto value = f; };
		template<auto f> nik_ce auto _type_			= U_store_T<_type<f>>;

	// next:

		template<auto f> struct _next				{ nik_ces auto value = f; };
		template<auto f> nik_ce auto _next_			= U_store_T<_next<f>>;

	// prev:

		template<auto f> struct _prev				{ nik_ces auto value = f; };
		template<auto f> nik_ce auto _prev_			= U_store_T<_prev<f>>;

/***********************************************************************************************************************/

// break:

	// id:

		template<auto... Vs> struct _break			{ };
		template<auto... Vs> nik_ce auto _break_		= U_store_T<_break<Vs...>>;

	// op:

		template<auto f> struct _op				{ nik_ces auto value = f; };
		template<auto f> nik_ce auto _op_			= U_store_T<_op<f>>;

	// arg:

		template<auto f> struct _out_arg			{ nik_ces auto value = f; };
		template<auto f> struct _aux_arg			{ nik_ces auto value = f; };
		template<auto f> struct _in_arg				{ nik_ces auto value = f; };
		template<auto f> struct _car_in_arg			{ nik_ces auto value = f; };
		template<auto f> struct _cdr_in_arg			{ nik_ces auto value = f; };
		template<auto f> struct _end_arg			{ nik_ces auto value = f; };

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

// tag operators:

/***********************************************************************************************************************/

// value:

	struct T_tag_value
	{
		template<auto UTag>
		nik_ces auto result = T_store_U<UTag>::value;

	}; nik_ce auto U_tag_value = U_store_T<T_tag_value>;

	template<auto UTag>
	nik_ce auto tag_value = T_tag_value::template result<UTag>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tag translators:

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

/***********************************************************************************************************************/

	template<key_type, typename...> struct T_label;
	template<key_type, typename...> struct T_position;
	template<key_type, typename...> struct T_cycle;
	template<key_type, typename...> struct T_precycle;
	template<key_type, typename...> struct T_postcycle;

	template<key_type Key, auto... Vs> using etc_label			= T_label<Key, T_store_U<Vs>...>;
	template<key_type Key, auto... Vs> using etc_position			= T_position<Key, T_store_U<Vs>...>;
	template<key_type Key, auto... Vs> using etc_cycle			= T_cycle<Key, T_store_U<Vs>...>;

	template<key_type Key, typename... Ts> using etc_precycle		= T_precycle<Key, Ts...>;
	template<key_type Key, typename... Ts> using etc_postcycle		= T_postcycle<Key, Ts...>;

/***********************************************************************************************************************/

// repeat:

	template
	<
		typename label,
		typename position,
		typename precycle,
		typename cycle,
		typename postcycle
	>
	nik_ce auto etc_repeat = U_pack_Vs
	<
		label::precycle,
		label::cycle,
		label::postcycle,

		position::out,
		position::end,
		position::in,

		precycle::pre_out_next,

		cycle::loop_predicate,
		cycle::assign_function,
		cycle::out_next,

		postcycle::post_assign_function
	>;

/***********************************************************************************************************************/

// map:

	template
	<
		typename label,
		typename position,
		typename precycle,
		typename cycle,
		typename postcycle
	>
	nik_ce auto etc_map = U_pack_Vs
	<
		label::precycle,
		label::cycle,
		label::postcycle,

		position::out,
		position::in,
		position::end,

		precycle::pre_end_prev,
		precycle::pre_out_next,
		precycle::pre_in_next,

		cycle::loop_predicate,
		cycle::assign_function,
		cycle::out_next,
		cycle::in_next,

		postcycle::post_assign_function,
		postcycle::post_out_next,
		postcycle::post_in_next,
		postcycle::post_end_next
	>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// label:

/***********************************************************************************************************************/

// id:

	template<auto precycle, auto cycle, auto postcycle>
	struct T_label<TR::id, _label<precycle, cycle, postcycle>>
	{
		nik_ces auto precycle_value	= tag_value<precycle>;
		nik_ces auto cycle_value	= tag_value<cycle>;
		nik_ces auto postcycle_value	= tag_value<postcycle>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// position:

/***********************************************************************************************************************/

// repeat:

	template<auto out, auto end, auto in>
	struct T_label<TR::repeat, _position<out, end, in>>
	{
		nik_ces auto out_value		= tag_value<out>;
		nik_ces auto end_value		= tag_value<end>;
		nik_ces auto in_value		= tag_value<in>;
	};

/***********************************************************************************************************************/

// map:

	template<auto out, auto in, auto end>
	struct T_label<TR::map, _position<out, in, end>>
	{
		nik_ces auto out_value		= tag_value<out>;
		nik_ces auto in_value		= tag_value<in>;
		nik_ces auto end_value		= tag_value<end>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cycle:

/***********************************************************************************************************************/

// repeat:

	template
	<
		auto type, auto  next,
		auto  op0, auto arg01, auto arg02,
		auto  op1, auto arg11, auto arg12
	>
	struct T_cycle
	<
		TR::repeat,

		_out_ival < type , next          >,
		_break    < op0  , arg01 , arg02 >,
		_action   < op1  , arg11 , arg12 >
	>
	{
		nik_ces auto break_op			= tag_value<op0>;
		nik_ces auto break_out_arg		= tag_value<arg01>;
		nik_ces auto break_end_arg		= tag_value<arg02>;
		nik_ces auto loop_predicate_value	= _argcompose_<break_op, break_out_arg, break_end_arg>;

		nik_ces auto action_op			= tag_value<op1>;
		nik_ces auto action_out_arg		= tag_value<arg11>;
		nik_ces auto action_in_arg		= tag_value<arg12>;
		nik_ces auto action_function		= _argcompose_<action_op, action_out_arg, action_in_arg>;
		nik_ces auto assign_function_value	= _side_<action_function>;

		nik_ces auto out_next_value		= tag_value<next>;

		nik_ces auto out_ival			= tag_value<type>;
		nik_ces auto out_ival_is_left_open	= is_left_open<out_ival>;
		nik_ces auto out_ival_is_right_closed	= is_right_closed<out_ival>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// precycle:

/***********************************************************************************************************************/

	template<typename cycle>
	struct T_precycle<TR::repeat, cycle>
	{
		nik_ces auto pre_out_next = alias
		<
			AOP::if_then_else,
			cycle::out_ival_is_left_open,
			cycle::out_next_value,
			_id_
		>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// postcycle:

/***********************************************************************************************************************/

	template<typename cycle>
	struct T_postcycle<TR::repeat, cycle>
	{
		nik_ces auto post_assign_function = alias
		<
			AOP::if_then_else,
			cycle::out_ival_is_right_closed,
			cycle::assign_function_value,
			_id_
		>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// interpretations:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// direct:

/***********************************************************************************************************************/

// to values:

	template<auto p, auto Op = U_tag_value>
	nik_ce auto direct_to_values = unpack_
	<
		p,
		U_partial
		<
			U_map,
			U_partial<U_custom, Op>
		>
	>;

/***********************************************************************************************************************/

// to spec:

	template<auto direct, auto H_spec>
	nik_ce auto direct_to_spec = alias
	<
		AOP::list_to_template,
		direct_to_values<direct>,
		H_spec
	>;

/***********************************************************************************************************************/

// write:

	template<auto defs, auto... Vs>
	nik_ce auto direct_write = pack_write<H_partial_similar, defs, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// conceptual:

/***********************************************************************************************************************/

// write:

	// temporary:

	template<auto defs, auto... Vs>
	nik_ce auto conceptual_write = defs;

//	template<auto defs, auto... Vs>
//	nik_ce auto conceptual_write = pack_write<H_partial_similar, defs, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// repeat:

/***********************************************************************************************************************/

// direct:

	// default:

		nik_ce auto direct_repeat_defaults = U_pack_Vs
		<
			_precycle_label_       < _zero         >,
			_cycle_label_          < _one          >,
			_postcycle_label_      < _two          >,

			_out_position_         < _zero         >,
			_end_position_         < _one          >,
			_in_position_          < _two          >,

			_pre_out_next_         < _id_          >,

			_loop_predicate_       < _equal_       >,
			_assign_function_      < _d_assign_i_  >,
			_out_next_             < _increment_<> >,

			_post_assign_function_ < _id_          >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_repeat = direct_to_spec
		<
			direct_write<direct_repeat_defaults, Vs...>,
			H_repeat_specification
		>;

/***********************************************************************************************************************/

// conceptual:

	// default:

		nik_ces auto conceptual_repeat_defaults = U_pack_Vs
		<
			_label_
			<
				_precycle_  < _zero         >,
				_cycle_     < _one          >,
				_postcycle_ < _two          >
			>,
			_position_
			<
				_out_       < _zero         >,
				_end_       < _one          >,
				_in_        < _two          >
			>,
			_out_ival_
			<
				_type_      < Ival::closing >,
				_next_      < _increment_<> >
			>,
			_break_
			<
				_op_        < _equal_       >,
				_out_arg_   < _id_          >,
				_end_arg_   < _id_          >
			>,
			_action_
			<
				_op_        < _assign_      >,
				_out_arg_   < _dereference_ >,
				_in_arg_    < _id_          >
			>
		>;

	// spec:

		template<auto label, auto position, auto out_ival, auto break_, auto action>
		nik_ce auto _conceptual_repeat(nik_avp(T_pack_Vs<label, position, out_ival, break_, action>*))
		{
			using label_etc			= etc_label<TR::id, label>;
			using position_etc		= etc_position<TR::repeat, position>;
			using cycle_etc			= etc_cycle<TR::repeat, out_ival, break_, action>;
			using precycle_etc		= etc_precycle<TR::repeat, cycle_etc>;
			using postcycle_etc		= etc_postcycle<TR::repeat, cycle_etc>;

			return etc_repeat
			<
				label_etc,
				position_etc,
				precycle_etc,
				cycle_etc,
				postcycle_etc
			>;
		}

		template<auto p>
		nik_ce auto let_conceptual_repeat = alias
		<
			AOP::list_to_template, _conceptual_repeat(p), H_repeat_specification
		>;

		template<auto... Vs>
		nik_ce auto conceptual_repeat = let_conceptual_repeat
		<
			conceptual_write<conceptual_repeat_defaults, Vs...>
		>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// map:

/***********************************************************************************************************************/

// direct:

	// default:

		nik_ce auto direct_map_defaults = U_pack_Vs
		<
			_precycle_label_       < _zero         >,
			_cycle_label_          < _one          >,
			_postcycle_label_      < _two          >,

			_out_position_         < _zero         >,
			_in_position_          < _one          >,
			_end_position_         < _two          >,

			_pre_end_prev_         < _id_          >,
			_pre_out_next_         < _id_          >,
			_pre_in_next_          < _id_          >,

			_loop_predicate_       < _equal_       >,
			_assign_function_      < _d_assign_i_  >,
			_out_next_             < _increment_<> >,
			_in_next_              < _increment_<> >,

			_post_assign_function_ < _id_          >,
			_post_out_next_        < _id_          >,
			_post_in_next_         < _id_          >,
			_post_end_next_        < _id_          >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_map = direct_to_spec
		<
			direct_write<direct_map_defaults, Vs...>,
			H_map_specification
		>;

/***********************************************************************************************************************/

// conceptual:

		//	0. If bidirectional and last, reverse iterate end.
		//	1. For each left endpoint, if open, then iterate.
		//	2. Evaluate the common (closing) loop.
		//	3. If there exists any right endpoint, which is closed, then act/combine.
		//	4. If (3), then for each right endpoint, when open, iterate.
		//	5. If bidirectional and last, iterate end to reset.

	//	lift < end , end_prev_<Spec> , end >,	// boolean_before_loop < is_end_prev_before_<Spec>
	//	lift < out , out_next_<Spec> , out >,	// boolean_before_loop < is_out_next_before_<Spec>
	//	lift < in  , in_next_<Spec>  , in  >,	// boolean_before_loop < is_in_next_before_<Spec>


	//	lift < out , act_func_<Spec>   , in  >,	// boolean_after_loop < is_act_func_after_<Spec>
	//	lift < out , out_next_<Spec>   , out >,	// boolean_after_loop < is_out_next_after_<Spec>
	//	lift < in  , in_next_<Spec>    , in  >,	// boolean_after_loop < is_in_next_after_<Spec>
	//	lift < end , end_next_<Spec>   , end >,	// boolean_after_loop < is_end_next_after_<Spec>

		nik_ces auto conceptual_map_defaults = U_pack_Vs
		<
			_label_
			<
				_precycle_  < _zero         >,
				_cycle_     < _one          >,
				_postcycle_ < _two          >
			>,
			_position_
			<
				_out_       < _zero         >,
				_in_        < _one          >,
				_end_       < _two          >
			>,
			_out_ival_
			<
				_type_      < Ival::closing >,
				_next_      < _increment_<> >
			>,
			_in_ival_
			<
				_type_      < Ival::closing >,
				_next_      < _increment_<> >,
				_prev_      < _decrement_<> >
			>,
			_break_
			<
				_op_        < _equal_       >,
				_in_arg_    < _id_          >,
				_end_arg_   < _id_          >
			>,
			_action_
			<
				_op_        < _assign_      >,
				_out_arg_   < _dereference_ >,
				_in_arg_    < _dereference_ >
			>
		>;

		template<auto label, auto position, auto out_ival, auto in_ival, auto break_, auto action>
		nik_ce auto _conceptual_map(nik_avp(T_pack_Vs<label, position, out_ival, in_ival, break_, action>*))
		{
			using label_etc			= etc_label<TR::id, label>;
			using position_etc		= etc_position<TR::map, position>;
			using cycle_etc			= etc_cycle<TR::map, out_ival, in_ival, break_, action>;
			using precycle_etc		= etc_precycle<TR::map, cycle_etc>;
			using postcycle_etc		= etc_postcycle<TR::map, cycle_etc>;

			return etc_map
			<
				label_etc,
				position_etc,
				precycle_etc,
				cycle_etc,
				postcycle_etc
			>;
		}

		template<auto p>
		nik_ce auto let_conceptual_map = alias
		<
			AOP::list_to_template, _conceptual_map(p), H_map_specification
		>;

		template<auto... Vs>
		nik_ce auto conceptual_map = let_conceptual_map
		<
			conceptual_write<conceptual_map_defaults, Vs...>
		>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/

// direct:

	// default:

		nik_ce auto direct_fold_defaults = U_pack_Vs
		<
			_precycle_label_        < _zero         >,
			_cycle_label_           < _one          >,
			_postcycle_label_       < _two          >,

			_out_position_          < _zero         >,
			_in_position_           < _one          >,
			_end_position_          < _two          >,

			_pre_in_next_           < _id_          >,

			_loop_predicate_        < _equal_       >,
			_combine_function_      < _id_          >,
			_in_next_               < _increment_<> >,

			_post_combine_function_ < _id_          >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_fold = direct_to_spec
		<
			direct_write<direct_fold_defaults, Vs...>,
			H_fold_specification
		>;

/***********************************************************************************************************************/

// conceptual:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (find) first:

/***********************************************************************************************************************/

// direct:

	// default:

		nik_ce auto direct_find_first_defaults = U_pack_Vs
		<
			_precycle_label_        < _zero             >,
			_cycle_label_           < _one              >,
			_match_label_           < _two              >,
			_postcycle_label_       < _three            >,
			_done_label_            < _four             >,

			_out_position_          < _zero             >,
			_in_position_           < _one              >,
			_end_position_          < _two              >,

			_pre_in_next_           < _id_              >,

			_loop_predicate_        < _equal_           >,
			_act_predicate_         < _constant_<false> >,
			_in_next_               < _increment_<>     >,

			_match_assign_function_ < _d_assign_i_      >,
			_match_out_next_        < _increment_<>     >,

			_post_act_predicate_    < _constant_<false> >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_find_first = direct_to_spec
		<
			direct_write<direct_find_first_defaults, Vs...>,
			H_find_first_specification
		>;

/***********************************************************************************************************************/

// conceptual:


/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (find) all:

/***********************************************************************************************************************/

// direct:

	// default:

		nik_ce auto direct_find_all_defaults = U_pack_Vs
		<
			_precycle_label_            < _zero             >,
			_cycle_label_               < _one              >,
			_match_label_               < _two              >,
			_postcycle_label_           < _three            >,
			_postmatch_label_           < _four             >,
			_done_label_                < _five             >,

			_out_position_              < _zero             >,
			_in_position_               < _one              >,
			_end_position_              < _two              >,

			_pre_in_next_               < _id_              >,

			_loop_predicate_            < _equal_           >,
			_act_predicate_             < _constant_<false> >,
			_in_next_                   < _increment_<>     >,

			_match_assign_function_     < _d_assign_i_      >,
			_match_out_next_            < _increment_<>     >,
			 _match_in_next_            < _increment_<>     >,

			_post_act_predicate_        < _constant_<false> >,

			_postmatch_assign_function_ < _d_assign_i_      >,
			_postmatch_out_next_        < _increment_<>     >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_find_all = direct_to_spec
		<
			direct_write<direct_find_all_defaults, Vs...>,
			H_find_all_specification
		>;

/***********************************************************************************************************************/

// conceptual:



/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// zip (bimap):

/***********************************************************************************************************************/

// direct:

	// default:

		nik_ce auto direct_zip_defaults = U_pack_Vs
		<
			_precycle_label_       < _zero         >,
			_cycle_label_          < _one          >,
			_postcycle_label_      < _two          >,

			_out_position_         < _zero         >,
			_car_in_position_      < _one          >,
			_cdr_in_position_      < _two          >,
			_end_position_         < _three        >,

			_pre_end_prev_         < _id_          >,
			_pre_out_next_         < _id_          >,
			_pre_car_in_next_      < _id_          >,
			_pre_cdr_in_next_      < _id_          >,

			_loop_predicate_       < _equal_       >,
			_act_function_         < _id_          >,
			_assign_function_      < _d_assign_i_  >,
			_out_next_             < _increment_<> >,
			_car_in_next_          < _increment_<> >,
			_cdr_in_next_          < _increment_<> >,

			_post_act_function_    < _id_          >,
			_post_assign_function_ < _id_          >,
			_post_out_next_        < _id_          >,
			_post_car_in_next_     < _id_          >,
			_post_cdr_in_next_     < _id_          >,
			_post_end_next_        < _id_          >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_zip = direct_to_spec
		<
			direct_write<direct_zip_defaults, Vs...>,
			H_zip_specification
		>;

/***********************************************************************************************************************/

// conceptual:

		//	0. If bidirectional and last, reverse iterate end.
		//	1. For each left endpoint, if open, then iterate.
		//	2. Evaluate the common (closing) loop.
		//	3. If there exists any right endpoint, which is closed, then act/combine.
		//	4. If (3), then for each right endpoint, when open, iterate.
		//	5. If bidirectional and last, iterate end to reset.

	//	lift < end , end_prev_<Spec> , end >,	// boolean_before_loop < is_end_prev_before_<Spec>
	//	lift < out , out_next_<Spec> , out >,	// boolean_before_loop < is_out_next_before_<Spec>
	//	lift < in  , in_next_<Spec>  , in  >,	// boolean_before_loop < is_in_next_before_<Spec>


	//	lift < out , act_func_<Spec>   , in  >,	// boolean_after_loop < is_act_func_after_<Spec>
	//	lift < out , out_next_<Spec>   , out >,	// boolean_after_loop < is_out_next_after_<Spec>
	//	lift < in  , in_next_<Spec>    , in  >,	// boolean_after_loop < is_in_next_after_<Spec>
	//	lift < end , end_next_<Spec>   , end >,	// boolean_after_loop < is_end_next_after_<Spec>

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fasten (zip with a carry):

/***********************************************************************************************************************/

// direct:

	// default:

		nik_ce auto direct_fasten_defaults = U_pack_Vs
		<
			_precycle_label_        < _zero             >,
			_cycle_label_           < _one              >,
			_postcycle_label_       < _two              >,

			_out_position_          < _zero             >,
			_aux_position_          < _one              >,
			_in_position_           < _two              >,
			_car_in_position_       < _three            >,
			_cdr_in_position_       < _four             >,
			_end_position_          < _five             >,

			_pre_end_prev_          < _id_              >,
			_pre_out_next_          < _id_              >,
			_pre_car_in_next_       < _id_              >,
			_pre_cdr_in_next_       < _id_              >,

			_loop_predicate_        < _equal_           >,
			_act_function_          < _id_              >,
			_assign_function_       < _d_assign_i_      >,
			_aux_next_              < _constant_<false> >,
			_combine_function_      < _id_              >,
			_in_next_               < _constant_<false> >,
			_out_next_              < _increment_<>     >,
			_car_in_next_           < _increment_<>     >,
			_cdr_in_next_           < _increment_<>     >,

			_post_act_function_     < _id_              >,
			_post_assign_function_  < _id_              >,
			_post_combine_function_ < _id_              >,
			_post_out_next_         < _id_              >,
			_post_car_in_next_      < _id_              >,
			_post_cdr_in_next_      < _id_              >,
			_post_end_next_         < _id_              >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_fasten = direct_to_spec
		<
			direct_write<direct_fasten_defaults, Vs...>,
			H_fasten_specification
		>;

/***********************************************************************************************************************/

// conceptual:

		//	0. If bidirectional and last, reverse iterate end.
		//	1. For each left endpoint, if open, then iterate.
		//	2. Evaluate the common (closing) loop.
		//	3. If there exists any right endpoint, which is closed, then act/combine.
		//	4. If (3), then for each right endpoint, when open, iterate.
		//	5. If bidirectional and last, iterate end to reset.

	//	lift < end , end_prev_<Spec> , end >,	// boolean_before_loop < is_end_prev_before_<Spec>
	//	lift < out , out_next_<Spec> , out >,	// boolean_before_loop < is_out_next_before_<Spec>
	//	lift < in  , in_next_<Spec>  , in  >,	// boolean_before_loop < is_in_next_before_<Spec>


	//	lift < out , act_func_<Spec>   , in  >,	// boolean_after_loop < is_act_func_after_<Spec>
	//	lift < out , out_next_<Spec>   , out >,	// boolean_after_loop < is_out_next_after_<Spec>
	//	lift < in  , in_next_<Spec>    , in  >,	// boolean_after_loop < is_in_next_after_<Spec>
	//	lift < end , end_next_<Spec>   , end >,	// boolean_after_loop < is_end_next_after_<Spec>

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// glide (bifold):

/***********************************************************************************************************************/

// direct:

	// default:

		nik_ce auto direct_glide_defaults = U_pack_Vs
		<
			_precycle_label_        < _zero         >,
			_cycle_label_           < _one          >,
			_postcycle_label_       < _two          >,

			_out_position_          < _zero         >,
			_car_in_position_       < _one          >,
			_cdr_in_position_       < _two          >,
			_end_position_          < _three        >,

			_pre_end_prev_          < _id_          >,
			_pre_car_in_next_       < _id_          >,
			_pre_cdr_in_next_       < _id_          >,

			_loop_predicate_        < _equal_       >,
			_act_function_          < _id_          >,
			_combine_function_      < _id_          >,
			_car_in_next_           < _increment_<> >,
			_cdr_in_next_           < _increment_<> >,

			_post_act_function_     < _id_          >,
			_post_combine_function_ < _id_          >,
			_post_car_in_next_      < _id_          >,
			_post_cdr_in_next_      < _id_          >,
			_post_end_next_         < _id_          >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_glide = direct_to_spec
		<
			direct_write<direct_glide_defaults, Vs...>,
			H_glide_specification
		>;

/***********************************************************************************************************************/

// conceptual:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_one_cycle_specs

