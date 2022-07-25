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

namespace cctmp_one_cycle_generics {

	using key_type						= typename cctmp::key_type;

	template<auto U> using T_store_U			= typename cctmp::template T_store_U<U>;
	template<auto... Vs> using T_pack_Vs			= typename cctmp::template T_pack_Vs<Vs...>;

	template<typename T> nik_ce auto U_store_T		= cctmp::template U_store_T<T>;

	template<auto... Vs> nik_ce auto overload		= cctmp::template overload<Vs...>;

	nik_ce auto _id_					= cctmp::_id_;
	nik_ce auto _and_					= cctmp::_and_;
	nik_ce auto _or_					= cctmp::_or_;

	nik_ce auto _same_					= cctmp::_same_;

	template<auto... Vs> nik_ce auto pack_sifter		= cctmp_functional::template pack_sifter<Vs...>;

	template<auto... Vs> nik_ce auto _side_			= cctmp_generics::template _side_<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// conveniences:

/***********************************************************************************************************************/

// same:

	template<auto V0, auto V1>
	nik_ce auto same = overload<_same_, V0, V1>;

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

// chord:

	// note:
		// ival:
			// left open, right open, right closed.
		// axis:
			// prev, next, potential.
	// quality:
		// major, minor, diminished,
		// augmented:
			// root, tone, peek.

	template<key_type, typename...> struct T_chord;

	template<key_type Key, typename... Ts> nik_ce auto U_chord	= U_store_T<T_chord<Key, Ts...>>;

	template<key_type Key,     auto... Vs> using       T_chord_	= T_chord<Key, T_store_U<Vs>...>;
	template<key_type Key,     auto... Vs> nik_ce auto U_chord_	= U_store_T<T_chord_<Key, Vs...>>;

/***********************************************************************************************************************/

// names:

	struct Chord
	{
		nik_ces key_type id			=  0;

		nik_ces key_type ival			=  1;
		nik_ces key_type axis			=  2;
		nik_ces key_type note			=  3;

		nik_ces key_type major			=  4;
		nik_ces key_type minor			=  5;
		nik_ces key_type diminished		=  6;
		nik_ces key_type augmented		=  7;
		nik_ces key_type quality		=  8;

		// ray:

		nik_ces key_type repeat			=  9;
		nik_ces key_type fold			= 10;
		nik_ces key_type find_first		= 11;
		nik_ces key_type find_all		= 12;

		// line:

		nik_ces key_type map			= 13;
		nik_ces key_type zip			= 14;
		nik_ces key_type fasten			= 15;
		nik_ces key_type glide			= 16;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// translators:

/***********************************************************************************************************************/

// is tone augmented:

	struct T_note_is_right_closed
	{
		template<auto tone>
		nik_ces auto result = T_store_U<tone>::ival::is_right_closed;

	}; nik_ce auto U_note_is_right_closed = U_store_T<T_note_is_right_closed>;

	template<auto holds, auto... right_closed_tones>
	nik_ce auto _is_tone_augmented(nik_avp(T_pack_Vs<right_closed_tones...>*))
	{
		return overload<_and_, holds, T_store_U<right_closed_tones>::axis::is_bidirectional...>;
	}

	template<auto holds, auto... tones>
	nik_ce auto tr_is_tone_augmented = _is_tone_augmented<holds>(pack_sifter<U_note_is_right_closed, tones...>);

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// note:

/***********************************************************************************************************************/

// ival:

	template<auto Ival>
	struct T_chord<Chord::ival, _ival<Ival>>
	{
		nik_ces auto is_left_open		= (Ival[0] == '(');
		nik_ces auto is_right_open		= (Ival[1] == ')');
		nik_ces auto is_right_closed		= (Ival[1] == ']');
	};

/***********************************************************************************************************************/

// axis:

	// ray:

		template<auto Next>
		struct T_chord<Chord::axis, _next<Next>>
		{
			nik_ces auto next		= Next;

			nik_ces auto is_bidirectional	= false;
		};

	// line:

		template<auto Next, auto Prev>
		struct T_chord<Chord::axis, _next<Next>, _prev<Prev>>
		{
			nik_ces auto prev		= Prev;
			nik_ces auto next		= Next;

			nik_ces auto is_bidirectional	= !same<Prev, _id_>;
		};

/***********************************************************************************************************************/

// composite:

	// ray:

		template<template<auto...> typename Tag, auto _Ival_, auto _Next_>
		struct T_chord<Chord::note, Tag<_Ival_, _Next_>>
		{
			// should static assert against tagnames.

			using ival = T_chord_ < Chord::ival , _Ival_ >;
			using axis = T_chord_ < Chord::axis , _Next_ >;
		};

	// line:

		template<template<auto...> typename Tag, auto _Ival_, auto _Next_, auto _Prev_>
		struct T_chord<Chord::note, Tag<_Ival_, _Next_, _Prev_>>
		{
			// should static assert against tagnames.

			using ival = T_chord_ < Chord::ival , _Ival_          >;
			using axis = T_chord_ < Chord::axis , _Next_ , _Prev_ >;
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// quality:

	// Terminology borrowed from { western } music theory:

		// (keeping the leftend point fixed as closed)

			//      major chord: [root, major 3rd); [perfect 5th) --- [root, tonic); [tone)
			//      minor chord: [root, minor 3rd]; [perfect 5th) --- [root, tonic]; [tone)

			// diminished chord: [root, minor 3rd]; [tritone    ] --- [root, tonic]; [tone]
			//  augmented chord: [root, major 3rd); [minor 6th  ] --- [root, tonic); [tone]

	// by interval:

		// { root, tonic ) ; { tone ) ---      major chord // aligns center
		// { root, tonic ) ; { tone ] ---  augmented chord // aligns left

		// { root, tonic ] ; { tone ) ---      minor chord // aligns right
		// { root, tonic ] ; { tone ] --- diminished chord // aligns center

	// by quality:

		//      major chord --- { root, tonic ) ; { tone ) // aligns centre
		//      minor chord --- { root, tonic ] ; { tone ) // aligns right

		// diminished chord --- { root, tonic ] ; { tone ] // aligns centre
		//  augmented chord --- { root, tonic ) ; { tone ] // aligns left

/***********************************************************************************************************************/

// major:

	template<typename... Notes>
	struct T_chord<Chord::major, Notes...>
	{
		nik_ces auto holds = overload<_and_, Notes::ival::is_right_open...>;
	};

/***********************************************************************************************************************/

// minor:

	template<typename Root, typename... Tones>
	struct T_chord<Chord::minor, Root, Tones...>
	{
		nik_ces auto holds = Root::ival::is_right_closed && overload<_or_, Tones::ival::is_right_open...>;
	};

/***********************************************************************************************************************/

// diminished:

	template<typename... Notes>
	struct T_chord<Chord::diminished, Notes...>
	{
		nik_ces auto holds = overload<_and_, Notes::ival::is_right_closed...>;
	};

/***********************************************************************************************************************/

// augmented:

	template<typename Root, typename... Tones>
	struct T_chord<Chord::augmented, Root, Tones...>
	{
		nik_ces auto holds	= Root::ival::is_right_open && overload<_or_, Tones::ival::is_right_closed...>;

		nik_ces auto is_root	= holds && Root::axis::is_bidirectional;
		nik_ces auto is_tone	= tr_is_tone_augmented<holds, U_store_T<Tones>...>;

		nik_ces auto is_peek	= holds && !is_root && !is_tone;
		nik_ces auto is_early	= is_root || is_peek;
	};

/***********************************************************************************************************************/

// composite:

	template<typename Root, typename... Tones>
	struct T_chord<Chord::quality, Root, Tones...>
	{
		using major		= T_chord < Chord::major      , Root , Tones... >;
		using minor		= T_chord < Chord::minor      , Root , Tones... >;
		using diminished	= T_chord < Chord::diminished , Root , Tones... >;
		using augmented		= T_chord < Chord::augmented  , Root , Tones... >;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// progressions:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// repeat (ray):

/***********************************************************************************************************************/

	template<typename OutIter>
	struct T_chord<Chord::repeat, OutIter>
	{
		using out = T_chord < Chord::note , OutIter >;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold (ray):

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find first (ray):

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find all (ray):

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// map (line):

/***********************************************************************************************************************/

	template<typename OutIter, typename InIter>
	struct T_chord<Chord::map, OutIter, InIter>
	{
		using out		= T_chord < Chord::note , OutIter >;
		using in		= T_chord < Chord::note ,  InIter >;

		using quality		= T_chord < Chord::quality , in , out >;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// zip (line):

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fasten (line):

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// glide (line):

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_one_cycle_generics

