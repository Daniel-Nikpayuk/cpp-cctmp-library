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

	template<typename T> nik_ce auto U_store_T		= cctmp::template U_store_T<T>;

	template<auto... Vs> nik_ce auto _side_			= cctmp_generics::template _side_<Vs...>;

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

// translator:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// names:

/***********************************************************************************************************************/

	struct Translator
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

	using TR = Translator;

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

	// endpoints:

		template<auto Ival>
		struct T_is_left_open<TR::id, _ival<Ival>>	{ nik_ces auto value = (Ival[0] == '('); };

		template<auto Ival>
		struct T_is_right_open<TR::id, _ival<Ival>>	{ nik_ces auto value = (Ival[1] == ')'); };

		template<auto Ival>
		struct T_is_right_closed<TR::id, _ival<Ival>>	{ nik_ces auto value = (Ival[1] == ']'); };

/***********************************************************************************************************************/

// axis:

	// next:

		template<auto Op> struct T_next<TR::id, _prev<Op>> { nik_ces auto value = Op; };
		template<auto Op> struct T_next<TR::id, _next<Op>> { nik_ces auto value = Op; };

	// is last:

		template<typename RootIval, typename... ToneIvals>
		struct T_is_last<TR::id, RootIval, ToneIvals...>
		{
			nik_ces auto root_is_right_open		= member_value<RootIval::is_right_open>;
			nik_ces auto tones_have_right_closed	= (... || member_value<ToneIvals::is_right_closed>);
			nik_ces auto value			= root_is_right_open && tones_have_right_closed;
		};

	// is primary last:

		template<typename IsLast, typename RootAxis>
		struct T_is_primary_last<TR::id, IsLast, RootAxis>
		{
			nik_ces auto value = IsLast::value && !same<member_value<RootAxis::prev>, _id_>;
		};

	// is secondary last:

		template<typename IsLast, typename IsPrimaryLast, typename... RightClosedToneAxes>
		struct T_is_secondary_last<TR::id, IsLast, IsPrimaryLast, RightClosedToneAxes...>
		{
			nik_ces auto is_last_but_not_primary	= IsLast::value && !IsPrimaryLast::value;
			nik_ces auto tones_all_bidirectional	= (... && !same<member_value<RightClosedToneAxes::prev>, _id_>);
			nik_ces auto value			= is_last_but_not_primary && tones_all_bidirectional;
		};

	// is tertiary last:

		template<typename IsLast, typename IsPrimaryLast, typename IsSecondaryLast>
		struct T_is_tertiary_last<TR::id, IsLast, IsPrimaryLast, IsSecondaryLast>
		{
			nik_ces auto value = IsLast::value && !IsPrimaryLast::value && !IsSecondaryLast::value;
		};

	// is post assign function:

		template<typename IsLast, typename IsSecondaryLast, typename RootIval>
		struct T_is_post_assign_function<TR::id, IsLast, IsSecondaryLast, RootIval>
		{
			nik_ces auto root_is_right_closed		= member_value<RootIval::is_right_closed>;
			nik_ces auto is_primary_or_tertiary_last	= IsLast::value && !IsSecondaryLast::value;
			nik_ces auto value				= root_is_right_closed || is_primary_or_tertiary_last;
		};

	// is post note next:

		template<typename RootIval, typename NoteIval>
		struct T_is_post_note_next<TR::id, RootIval, NoteIval>
		{
			nik_ces auto root_is_right_closed	= member_value<RootIval::is_right_closed>;
			nik_ces auto note_is_right_open		= member_value<NoteIval::is_right_open>;
			nik_ces auto value			= root_is_right_closed && note_is_right_open;
		};

	// is post root next:

		template<typename IsPrimaryLast, typename IsTertiaryLast>
		struct T_is_post_root_next<TR::id, IsPrimaryLast, IsTertiaryLast>
		{
			nik_ces auto value = IsPrimaryLast::value && IsTertiaryLast::value;
		};

	// is post tone prev:

		template<typename IsSecondaryLast, typename ToneIval>
		struct T_is_post_tone_prev<TR::id, IsSecondaryLast, ToneIval>
		{
			nik_ces auto tone_is_right_closed	= member_value<ToneIval::is_right_closed>;
			nik_ces auto value			= IsSecondaryLast::value && tone_is_right_closed;
		};

/***********************************************************************************************************************/

// cycle:

	// note next:

		template<typename NoteAxis>
		struct T_note_next<TR::id, NoteAxis> { nik_ces auto value = member_value<NoteAxis::next>; };

/***********************************************************************************************************************/

// precycle:

	// tonic prev:

		template<typename IsPrimaryLast, typename RootAxis>
		struct T_pre_tonic_prev<TR::id, IsPrimaryLast, RootAxis>
		{
			nik_ces auto value = if_then_else
			<
				IsPrimaryLast::value,
				member_value<RootAxis::prev>,
				_id_
			>;
		};

	// note next:

		template<typename NoteIval, typename NoteAxis>
		struct T_pre_note_next<TR::id, NoteIval, NoteAxis>
		{
			nik_ces auto value = if_then_else
			<
				member_value<NoteIval::is_left_open>,
				member_value<NoteAxis::next>,
				_id_
			>;
		};

/***********************************************************************************************************************/

// postcycle:

	// assign function:

		template<typename IsPostAssignFunction, typename Cycle>
		struct T_post_assign_function<TR::id, Cycle>
		{
			nik_ces auto value = if_then_else
			<
				IsPostAssignFunction::value,
				member_value<Cycle::assign_func>,
				_id_
			>;
		};

	// note next:

		template<typename IsPostNoteNext, typename NoteAxis>
		struct T_post_note_next<TR::id, IsPostNext, NoteAxis>
		{
			nik_ces auto value = if_then_else
			<
				IsPostNoteNext::value,
				member_value<NoteAxis::next>,
				_id_
			>;
		};

	// tonic next:

		template<typename IsPrimaryLast, typename RootAxis>
		struct T_post_tonic_next<TR::id, IsPrimaryLast, RootAxis>
		{
			nik_ces auto value = if_then_else
			<
				IsPrimaryLast::value,
				member_value<RootAxis::next>,
				_id_
			>;
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// repeat (singular):

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
/***********************************************************************************************************************/

// map (plural):

/***********************************************************************************************************************/

// loop predicate:

	template<typename IsTertiary, typename InAxis, auto Op, auto InArg, auto EndArg>
	struct T_loop_predicate<TR::map, IsTertiary, InAxis, _op<Op>, _in_arg<InArg>, _end_arg<EndArg>>
	{
		nik_ces auto in_arg	= if_then_else<IsTertiary::value, member_value<InAxis::next>, InArg>;
		nik_ces auto value	= _argcompose_<Op, in_arg, EndArg>;
	};

/***********************************************************************************************************************/

// assign function:

	template<typename Op, typename OutArg, typename InArg>
	struct T_assign_function<TR::map, Op, OutArg, InArg> : public T_assign_function<TR::repeat, Op, OutArg, InArg> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_one_cycle_specs

