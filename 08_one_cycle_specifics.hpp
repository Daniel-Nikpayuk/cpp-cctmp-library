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

	template<key_type Name, key_type Note, typename... Ts> struct T_etc;
	template<key_type Name, key_type Note, typename... Ts> nik_ce auto U_etc = U_store_T<T_etc<Name, Note, Ts...>>;

// tr:

	template<key_type Name, key_type Note, auto... Vs> using T_tr		= T_etc<Name, Note, T_store_U<Vs>...>;
	template<key_type Name, key_type Note, auto... Vs> nik_ce auto U_tr	= U_store_T<T_tr<Name, Note, Vs...>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// names:

	struct ConfigurationName
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

	using CN = ConfigurationName;

/***********************************************************************************************************************/

// note:

	struct ConfigurationNote
	{
		nik_ces key_type id			=  0;

		nik_ces key_type label			=  1;
		nik_ces key_type position		=  2;

		nik_ces key_type ival			=  3;
		nik_ces key_type axis			=  4;
		nik_ces key_type ivals			=  5;

		nik_ces key_type cycle			=  6;
		nik_ces key_type precycle		=  7;
		nik_ces key_type postcycle		=  8;
	};

	using CT = ConfigurationNote;

/***********************************************************************************************************************/

// ival:

	// id:

		template<auto Note>
		struct T_etc<CN::id, CT::ival, _note<Note>>
		{
			nik_ces auto is_left_open	= ival < TT::is_left_open    , Note >;
			nik_ces auto is_right_open	= ival < TT::is_right_open   , Note >;
			nik_ces auto is_right_closed	= ival < TT::is_right_closed , Note >;
		};

/***********************************************************************************************************************/

// axis:

	// unidirectional:

		template<auto Next>
		struct T_etc<CN::id, CT::axis, _next<Next>>
		{
			nik_ces auto next = Next;
		};

	// bidirectional:

		template<auto Next, auto Prev>
		struct T_etc<CN::id, CT::axis, _next<Next>, _prev<Prev>>
		{
			nik_ces auto prev = Prev;
			nik_ces auto next = Next;
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// repeat (singular):

/***********************************************************************************************************************/

// label:

	template<auto _Precycle_, auto _Cycle_, auto _Postcycle_>
	struct T_etc<CN::repeat, CT::label, _label<_Precycle_, _Cycle_, _Postcycle_>>
	{
		nik_ces auto precycle	= tag_value <  _Precycle_ >;
		nik_ces auto cycle	= tag_value <     _Cycle_ >;
		nik_ces auto postcycle	= tag_value < _Postcycle_ >;
	};

/***********************************************************************************************************************/

// position:

	template<auto _Out_, auto _End_, auto _In_>
	struct T_etc<CN::repeat, CT::position, _position<_Out_, _End_, _In_>>
	{
		nik_ces auto out	= tag_value < _Out_ >;
		nik_ces auto end	= tag_value < _End_ >;
		nik_ces auto in		= tag_value <  _In_ >;
	};

/***********************************************************************************************************************/

// ivals:

	template<auto _Note_, auto _Next_>
	struct T_etc<CN::repeat, CT::ivals, _out_ival<_Note_, _Next_>>
	{
		nik_ces auto out_ival	= U_tr < CN::id, CT::ival, _Note_ >;
		nik_ces auto out_axis	= U_tr < CN::id, CT::axis, _Next_ >;
	};

/***********************************************************************************************************************/

// cycle:

	template
	<
		auto _Op0_, auto _Arg01_, auto _Arg02_,
		auto _Op1_, auto _Arg11_, auto _Arg12_,

		typename Ivals
	>
	struct T_etc
	<
		CN::repeat, CT::cycle,

		_break  < _Op0_ , _Arg01_ , _Arg02_ >,
		_action < _Op1_ , _Arg11_ , _Arg12_ >,

		Ivals
	>
	{
		nik_ces auto loop_predicate	= cycle < TT::argcompose  , _Op0_, _Arg01_, _Arg02_ >;
		nik_ces auto assign_function	= cycle < TT::sidecompose , _Op1_, _Arg11_, _Arg12_ >;

		nik_ces auto out_next		= axis_next < Ivals::out_axis >;
	};

/***********************************************************************************************************************/

// precycle:

	template<typename Ivals>
	struct T_etc<CN::repeat, CT::precycle, Ivals>
	{
		nik_ces auto pre_out_next = precycle < TT::note_next , Ivals::out_ival , Ivals::out_axis >;
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename Ivals, typename Cycle>
	struct T_etc<CN::repeat, CT::postcycle, Ivals, Cycle>
	{
		nik_ces auto is_post_assign_function	= is_right_closed<Ivals::out_ival>;
		nik_ces auto post_assign_function	= postcycle
							<
								TT::assign_function,
								is_post_assign_function, U_store_T<Cycle>
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
	struct T_etc<CN::map, CT::label, Label> : public T_label<CN::repeat, Label> { };

/***********************************************************************************************************************/

// position:

	template<auto _Out_, auto _In_, auto _End_>
	struct T_etc<CN::map, CT::position, _position<_Out_, _In_, _End_>>
	{
		nik_ces auto out	= tag_value < _Out_ >;
		nik_ces auto in		= tag_value <  _In_ >;
		nik_ces auto end	= tag_value < _End_ >;
	};

/***********************************************************************************************************************/

// ival:

	template
	<
		auto _OutNote_, auto _OutNext_, auto _OutPrev_,
		auto  _InNote_, auto  _InNext_, auto  _InPrev_
	>
	struct T_etc
	<
		CN::map, CT::ivals,

		_out_ival < _OutNote_ , _OutNext_ , _OutPrev_ >,
		 _in_ival <  _InNote_ ,  _InNext_ ,  _InPrev_ >
	>
	{
		nik_ces auto out_ival	= U_tr < CN::id, CT::ival, _OutNote_             >;
		nik_ces auto out_axis	= U_tr < CN::id, CT::axis, _OutNext_ , _OutPrev_ >;

		nik_ces auto in_ival	= U_tr < CN::id, CT::ival,  _InNote_             >;
		nik_ces auto in_axis	= U_tr < CN::id, CT::axis,  _InNext_ ,  _InPrev_ >;
	};

/***********************************************************************************************************************/

// axis:

	template<typename Ivals>
	struct T_etc<CN::map, CT::axis, Ivals>
	{
		nik_ces auto is_last       = axis < TT::is_last            , Ivals::in_ival , Ivals::out_ival >;
		nik_ces auto is_primary	   = axis < TT::is_primary_last    , is_last        , Ivals::in_ival  >;

		nik_ces auto closed_rights = axis < TT::only_closed_rights , Ivals::out_ival >;

		nik_ces auto is_secondary  = axis < TT::is_secondary_last  , is_last , is_primary, closed_rights >;
		nik_ces auto is_tertiary   = axis < TT::is_tertiary_last   , is_last , is_primary, is_secondary  >;
	};

/***********************************************************************************************************************/

// cycle:

	template
	<
		auto _Op0_, auto _Arg01_, auto _Arg02_,
		auto _Op1_, auto _Arg11_, auto _Arg12_,

		typename Axis, typename Ivals
	>
	struct T_etc
	<
		CN::map, CT::cycle,

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

		nik_ces auto loop_arg			= cycle<TT::peek, Axis::is_tertiary, Ivals::in_axis, _Arg01_>;

		nik_ces auto loop_predicate		= cycle < TT::argcompose  , _Op0_ , loop_arg , _Arg02_ >;
		nik_ces auto assign_function		= cycle < TT::sidecompose , _Op1_ , _Arg11_  , _Arg12_ >;

		nik_ces auto out_next			= axis_next < Ivals::out_axis >;
		nik_ces auto in_next			= axis_next < Ivals::in_axis  >;
	};

/***********************************************************************************************************************/

// precycle:

	template<typename Axis, typename Ivals>
	struct T_etc<CN::map, CT::precycle, Axis, Ivals>
	{
		nik_ces auto pre_end_next = precycle < TT::tonic_prev , Axis::is_primary_last , Ivals::in_axis  >;
		nik_ces auto pre_out_next = precycle < TT::note_next  , Ivals::out_ival       , Ivals::out_axis >;
		nik_ces auto pre_in_next  = precycle < TT::note_next  , Ivals::in_ival        , Ivals::in_axis  >;
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename Axis, typename Ivals, typename Cycle>
	struct T_etc<CN::map, CT::postcycle, Axis, Ivals, Cycle>
	{
		nik_ces auto is_post_assign		= axis
							<
								TT::is_post_assign_function, Axis::is_last,
								Axis::is_secondary_last, Ivals::in_ival
							>;
		nik_ces auto is_post_root_next		= axis
							<
								TT::is_post_root_next,
								Ivals::is_primary_last, Ivals::is_tertiary_last
							>;

		nik_ces auto post_assign_function = postcycle<TT::assign_function, is_post_assign, U_store_T<Cycle>>;

	//	nik_ces auto post_out_next = postcycle < TT::tone_next  , U_store_T<Axis>       , U_store_T<Ivals> >;
		nik_ces auto post_in_next  = postcycle < TT::note_next  , is_post_root_next     , Ivals::in_axis   >;
		nik_ces auto post_end_prev = postcycle < TT::tonic_next , Axis::is_primary_last , Ivals::in_axis   >;
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

