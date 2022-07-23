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
	nik_ce auto _and_					= cctmp::_and_;
	nik_ce auto _or_					= cctmp::_or_;

	nik_ce auto _same_					= cctmp::_same_;
	nik_ce auto _if_then_else_				= cctmp::_if_then_else_;

	template<auto... Vs> nik_ce auto _argcompose_		= cctmp_generics::template _argcompose_<Vs...>;
	template<auto... Vs> nik_ce auto _side_			= cctmp_generics::template _side_<Vs...>;

	template<auto... Vs> nik_ce auto pack_sifter		= cctmp_functional::template pack_sifter<Vs...>;

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

		template<auto... Vs> struct _out_iter			{ };
		template<auto... Vs> nik_ce auto _out_iter_		= U_store_T<_out_iter<Vs...>>;

	// in:

		template<auto... Vs> struct _in_iter			{ };
		template<auto... Vs> nik_ce auto _in_iter_		= U_store_T<_in_iter<Vs...>>;

	// ival:

		template<auto f> struct _ival				{ };
		template<auto f> nik_ce auto _ival_			= U_store_T<_ival<f>>;

	// next:

		template<auto f> struct _next				{ };
		template<auto f> nik_ce auto _next_			= U_store_T<_next<f>>;

	// prev:

		template<auto f> struct _prev				{ };
		template<auto f> nik_ce auto _prev_			= U_store_T<_prev<f>>;

/***********************************************************************************************************************/

// break:

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

// translate:

	template<auto... Vs>
	nik_ce auto translate = U_pack_Vs<Vs...>;

/***********************************************************************************************************************/

// names:

	struct TranslateName
	{
		nik_ces key_type id		= 0;

		// base:

		nik_ces key_type tag		= 1;
		nik_ces key_type ival		= 2;
		nik_ces key_type axis		= 3;
		nik_ces key_type cycle		= 4;
		nik_ces key_type precycle	= 5;
		nik_ces key_type postcycle	= 6;
	};

	using TN = TranslateName;

/***********************************************************************************************************************/

// notes:

	struct TranslateNote
	{
		nik_ces key_type id				=  0;

		nik_ces key_type value				=  1;

		nik_ces key_type is_left_open			=  2;
		nik_ces key_type is_right_open			=  3;
		nik_ces key_type is_right_closed		=  4;

		nik_ces key_type next				=  5;

		nik_ces key_type is_last			=  6;
		nik_ces key_type is_primary_last		=  7;
		nik_ces key_type only_closed_rights		=  8;
		nik_ces key_type is_secondary_last		=  9;
		nik_ces key_type is_tertiary_last		= 10;

		nik_ces key_type is_post_assign_function	= 11;
		nik_ces key_type is_post_note_next		= 12;
		nik_ces key_type is_post_root_next		= 13;
		nik_ces key_type is_post_tone_prev		= 14;

		nik_ces key_type argcompose			= 15;
		nik_ces key_type sidecompose			= 16;
		nik_ces key_type peek				= 17;

		nik_ces key_type tonic_prev			= 18;
		nik_ces key_type note_next			= 19;

		nik_ces key_type assign_function		= 20;
		nik_ces key_type tone_next			= 21;
		nik_ces key_type tonic_next			= 22;
	};

	using TT = TranslateNote;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// etc (conveniences):

/***********************************************************************************************************************/

// ival:

	// is left open:

		template<auto ival_etc>
		nik_ce auto is_left_open = T_store_U<ival_etc>::is_left_open;

	// is right open:

		template<auto ival_etc>
		nik_ce auto is_right_open = T_store_U<ival_etc>::is_right_open;

	// is right closed:

		struct T_is_right_closed 
		{
			template<auto ival_etc>
			nik_ces auto result = T_store_U<ival_etc>::is_right_closed;

		}; nik_ce auto U_is_right_closed = U_store_T<T_is_right_closed>;

		template<auto ival_etc>
		nik_ce auto is_right_closed = T_is_right_closed::template result<ival_etc>;

/***********************************************************************************************************************/

// axis:

	// prev:

		template<auto axis_etc>
		nik_ce auto axis_prev = T_store_U<axis_etc>::prev;

	// next:

		template<auto axis_etc>
		nik_ce auto axis_next = T_store_U<axis_etc>::next;

	// is bidirectional:

		template<auto axis_etc>
		nik_ce auto is_bidirectional = !same<axis_prev<axis_etc>, _id_>;

/***********************************************************************************************************************/

// cycle:

	// assign function:

		template<auto cycle_etc>
		nik_ce auto assign_function = T_store_U<cycle_etc>::assign_function;

	// peek:

		template<auto is_tertiary_last, typename RootAxis, template<auto> typename Tag, auto RootArg>
		nik_ce auto dispatch_peek(nik_avp(RootAxis*), nik_avp(Tag<RootArg>*))
		{
			if nik_ce (is_tertiary_last) return _argcompose_<RootArg, RootAxis::next>;
			else                         return RootArg;
		}

/***********************************************************************************************************************/

// postcycle:

	// tone next:

/*
		template<auto is_secondary_last, typename ToneAxis>
		nik_ce auto dispatch_tone_next(nik_avp(ToneAxis*))
		{
			if nik_ce (is_secondary_last)
			{
				return _argcompose_<RootArg, RootAxis::next>;
			}
			else
			{
			}
		}

	template<auto is_secondary_last, auto tone_axis_etc>
	nik_ce auto translate<TN::postcycle, TT::tone_next, is_secondary_last, tone_axis_etc> = if_then_else
	<
		is_post_note_next, axis_next<note_axis_etc>, _id_
	>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tag:

/***********************************************************************************************************************/

// value:

	template<template<auto> typename Tag, auto Value, nik_vp(t)(Tag<Value>*)>
	nik_ce auto translate<TN::tag, TT::value, t> = Value;

	// syntactic sugar:

		template<auto tag>
		nik_ce auto tag_value = translate<TN::tag, TT::value, tag>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ival:

	template<auto... Vs>
	nik_ces auto ival = translate<TN::ival, Vs...>;

/***********************************************************************************************************************/

// is left open:

	template<auto ival>
	nik_ce auto translate<TN::ival, TT::is_left_open, ival>		= (ival[0] == '(');

/***********************************************************************************************************************/

// is right open:

	template<auto ival>
	nik_ce auto translate<TN::ival, TT::is_right_open, ival>	= (ival[1] == ')');

/***********************************************************************************************************************/

// is right closed:

	template<auto ival>
	nik_ce auto translate<TN::ival, TT::is_right_closed, ival>	= (ival[1] == ']');

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// axis:

	template<auto... Vs>
	nik_ces auto axis = translate<TN::axis, Vs...>;

/***********************************************************************************************************************/

// is last:

	template<auto root_ival_etc, auto... tone_ival_etcs>
	nik_ce auto translate<TN::axis, TT::is_last, root_ival_etc, tone_ival_etcs...> =
		is_right_open<root_ival_etc> && overload<_or_, is_right_closed<tone_ival_etcs>...>;

/***********************************************************************************************************************/

// is primary last:

	template<auto is_last, auto root_axis_etc>
	nik_ce auto translate<TN::axis, TT::is_primary_last, is_last, root_axis_etc> =
		is_last && is_bidirectional<root_axis_etc>;

/***********************************************************************************************************************/

// only closed rights:

	template<auto... ival_etcs>
	nik_ce auto translate<TN::axis, TT::only_closed_rights, ival_etcs...> =
		pack_sifter<U_is_right_closed, ival_etcs...>;

/***********************************************************************************************************************/

// is secondary last:

		// if p is empty, then !is_last

	template
	<
		auto is_last, auto is_primary_last,
		template<auto...> typename B, auto... right_closed_tone_axis_etcs,
		nik_vp(p)(B<right_closed_tone_axis_etcs...>*)
	>
	nik_ce auto translate<TN::axis, TT::is_secondary_last, is_last, is_primary_last, p> =
		overload<_and_, is_last, !is_primary_last, is_bidirectional<right_closed_tone_axis_etcs>...>;

/***********************************************************************************************************************/

// is tertiary last:

	template<auto is_last, auto is_primary_last, auto is_secondary_last>
	nik_ce auto translate<TN::axis, TT::is_tertiary_last, is_last, is_primary_last, is_secondary_last> =
		is_last && !is_primary_last && !is_secondary_last;

/***********************************************************************************************************************/

// is post assign function:

	template<auto is_last, auto is_secondary_last, auto root_ival_etc>
	nik_ce auto translate<TN::axis, TT::is_post_assign_function, is_last, is_secondary_last, root_ival_etc> =
		is_right_closed<root_ival_etc> || (is_last && !is_secondary_last);

/***********************************************************************************************************************/

// is post note next:

	template<auto root_ival_etc, auto note_ival_etc>
	nik_ce auto translate<TN::axis, TT::is_post_note_next, root_ival_etc, note_ival_etc> =
		is_right_closed<root_ival_etc> && is_right_open<note_ival_etc>;

/***********************************************************************************************************************/

// is post root next:

	template<auto is_primary_last, auto is_tertiary_last>
	nik_ce auto translate<TN::axis, TT::is_post_root_next, is_primary_last, is_tertiary_last> =
		is_primary_last || is_tertiary_last;

/***********************************************************************************************************************/

// is post tone prev:

	template<auto is_secondary_last, auto tone_ival_etc>
	nik_ce auto translate<TN::axis, TT::is_post_tone_prev, is_secondary_last, tone_ival_etc> =
		is_secondary_last && is_right_closed<tone_ival_etc>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cycle:

	template<auto... Vs>
	nik_ces auto cycle = translate<TN::cycle, Vs...>;

/***********************************************************************************************************************/

// argcompose:

	template<auto... op_tags>
	nik_ce auto translate<TN::cycle, TT::argcompose, op_tags...> = _argcompose_<tag_value<op_tags>...>;

/***********************************************************************************************************************/

// side argcompose:

	template<auto... op_tags>
	nik_ce auto translate<TN::cycle, TT::sidecompose, op_tags...> = _side_<_argcompose_<tag_value<op_tags>...>>;

/***********************************************************************************************************************/

// peek:

	template<auto is_tertiary, auto root_axis_etc, auto root_arg_tag>
	nik_ce auto translate<TN::cycle, TT::peek, is_tertiary, root_axis_etc, root_arg_tag> = dispatch_peek
	<
		is_tertiary

	>(root_axis_etc, root_arg_tag);

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// precycle:

	template<auto... Vs>
	nik_ces auto precycle = translate<TN::precycle, Vs...>;

/***********************************************************************************************************************/

// tonic prev:

	template<auto is_primary_last, auto root_axis_etc>
	nik_ce auto translate<TN::precycle, TT::tonic_prev, is_primary_last, root_axis_etc> = if_then_else
	<
		is_primary_last, axis_prev<root_axis_etc>, _id_
	>;

/***********************************************************************************************************************/

// note next:

	template<auto note_ival_etc, auto note_axis_etc>
	nik_ce auto translate<TN::precycle, TT::note_next, note_ival_etc, note_axis_etc> = if_then_else
	<
		is_left_open<note_ival_etc>, axis_next<note_axis_etc>, _id_
	>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// postcycle:

	template<auto... Vs>
	nik_ces auto postcycle = translate<TN::postcycle, Vs...>;

/***********************************************************************************************************************/

// assign function:

	template<auto is_post_assign_function, auto cycle_etc>
	nik_ce auto translate<TN::postcycle, TT::assign_function, is_post_assign_function, cycle_etc> = if_then_else
	<
		is_post_assign_function, assign_function<cycle_etc>, _id_
	>;

/***********************************************************************************************************************/

// note (root) next:

	template<auto is_post_note_next, auto note_axis_etc>
	nik_ce auto translate<TN::postcycle, TT::note_next, is_post_note_next, note_axis_etc> = if_then_else
	<
		is_post_note_next, axis_next<note_axis_etc>, _id_
	>;

/***********************************************************************************************************************/

// tone next:

//	template<auto is_secondary_last, auto tone_axis_etc>
//	nik_ce auto translate<TN::postcycle, TT::tone_next, is_secondary_last, tone_axis_etc> = if_then_else
//	<
//		is_post_note_next, axis_next<note_axis_etc>, _id_
//	>;

	// if not last:

		// if root is right closed and tone is right open, then next.

	// if last:

		// if (primary or tertiary) and tone is right open, then next.
		// if secondary and tone is right closed, then prev.

/***********************************************************************************************************************/

// tonic next:

	// is this accurate ? is primary or tertiary ?

	template<auto is_primary_last, auto root_axis_etc>
	nik_ce auto translate<TN::postcycle, TT::tonic_next, is_primary_last, root_axis_etc> = if_then_else
	<
		is_primary_last, axis_next<root_axis_etc>, _id_
	>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_one_cycle_specs

