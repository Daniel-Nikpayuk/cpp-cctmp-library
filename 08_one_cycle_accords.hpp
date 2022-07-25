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

	template<auto... Vs> nik_ce auto U_pack_Vs		= cctmp::template U_pack_Vs<Vs...>;

	nik_ce auto _if_then_else_				= cctmp::_if_then_else_;
	nik_ce auto _car_					= cctmp::_car_;

	template<auto... Vs> nik_ce auto unpack_		= cctmp::template unpack_<Vs...>;

	template<auto... Vs> nik_ce auto _argcompose_		= cctmp_generics::template _argcompose_<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// conveniences:

/***********************************************************************************************************************/

// if_then_else:

	template<auto p, auto a, auto c>
	nik_ce auto if_then_else = overload<_if_then_else_, p, a, c>;

// tag value:

	template<auto t>
	nik_ce auto tag_value = unpack_<t, _car_>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// accord:

	template<key_type Name, key_type Note, typename... Ts> struct T_accord;

	template<key_type Name, key_type Note, typename... Ts>
	nik_ce auto U_accord = U_store_T<T_accord<Name, Note, Ts...>>;

	template<key_type Name, key_type Note, auto... Vs>
	using T_accord_ = T_accord<Name, Note, T_store_U<Vs>...>;

	template<key_type Name, key_type Note, auto... Vs>
	nik_ce auto U_accord_ = U_store_T<T_accord_<Name, Note, Vs...>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// names:

	struct AccordName
	{
		nik_ces key_type id		= 0;

		// ray:

		nik_ces key_type repeat		= 1;
		nik_ces key_type fold		= 2;
		nik_ces key_type find_first	= 3;
		nik_ces key_type find_all	= 4;

		// line:

		nik_ces key_type map		= 5;
		nik_ces key_type zip		= 6;
		nik_ces key_type fasten		= 7;
		nik_ces key_type glide		= 8;
	};

	using AN = AccordName;

/***********************************************************************************************************************/

// note:

	struct AccordNote
	{
		nik_ces key_type id			=  0;

		nik_ces key_type label			=  1;
		nik_ces key_type position		=  2;

		nik_ces key_type cycle			=  3;
		nik_ces key_type precycle		=  4;
		nik_ces key_type postcycle		=  5;
	};

	using AT = AccordNote;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// translators:

/***********************************************************************************************************************/

// argcompose:

	template<auto... op_tags>
	nik_ce auto tr_argcompose = _argcompose_<tag_value<op_tags>...>;

/***********************************************************************************************************************/

// side argcompose:

	template<auto... op_tags>
	nik_ce auto tr_sidecompose = _side_<tr_argcompose<op_tags...>>;

/***********************************************************************************************************************/

// peek value:

	template<auto arg, typename root, typename quality>
	nik_ce auto _peek_value()
	{
		if nik_ce (quality::augmented::is_peek) return _argcompose_<arg, root::axis::next>;
		else                                    return arg;
	}

	template<auto arg_tag, typename root, typename quality>
	nik_ce auto peek_value = _peek_value<tag_value<arg_tag>, root, quality>();

/***********************************************************************************************************************/

// loop argcompose:

	template<auto op_tag, auto arg1_tag, auto arg2_tag, typename root, typename quality>
	nik_ce auto tr_loopcompose = _argcompose_
	<
		 tag_value <   op_tag                  >,
		peek_value < arg1_tag , root , quality >,
		 tag_value < arg2_tag                  >
	>;

/***********************************************************************************************************************/

// pre tonic prev:

	template<typename root, typename quality>
	nik_ce auto tr_pre_tonic_prev = if_then_else
	<
		quality::augmented::is_root,
		root::axis::prev,
		_id_
	>;

/***********************************************************************************************************************/

// pre note next:

	template<typename note>
	nik_ce auto tr_pre_note_next = if_then_else
	<
		note::ival::is_left_open,
		note::axis::next,
		_id_
	>;

/***********************************************************************************************************************/

// post assign function:

	template<auto is_post_assign_function, typename cycle>
	nik_ce auto tr_post_assign_function = if_then_else
	<
		is_post_assign_function,
		cycle::assign_function,
		_id_
	>;

/***********************************************************************************************************************/

// post note next:

	template<auto is_post_note_next, typename note>
	nik_ce auto tr_post_note_next = if_then_else
	<
		is_post_note_next,
		note::axis::next,
		_id_
	>;

/***********************************************************************************************************************/

// post tone next:

	template<typename tone, typename quality>
	nik_ce auto _post_tone_next()
	{
		nik_ce auto is_prev	= quality::augmented::is_tone && tone::ival::is_right_closed;
		nik_ce auto maybe_next	= quality::minor::holds       || quality::augmented::is_early;
		nik_ce auto is_next	= maybe_next                  && tone::ival::is_right_open;

		if nik_ce      (is_prev) return tone::axis::prev;
		else if nik_ce (is_next) return tone::axis::next;
		else                     return _id_;
	}

	template<typename tone, typename quality>
	nik_ce auto tr_post_tone_next = _post_tone_next<tone, quality>();

/***********************************************************************************************************************/

// post tonic next:

	template<typename root, typename quality>
	nik_ce auto tr_post_tonic_next = if_then_else
	<
		quality::augmented::is_root,
		root::axis::next,
		_id_
	>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// repeat (ray):

/***********************************************************************************************************************/

// label:

	template<auto _Precycle_, auto _Cycle_, auto _Postcycle_>
	struct T_accord<AN::repeat, AT::label, _label<_Precycle_, _Cycle_, _Postcycle_>>
	{
		// should static assert against tagnames.

		nik_ces auto precycle		= tag_value <  _Precycle_ >;
		nik_ces auto cycle		= tag_value <     _Cycle_ >;
		nik_ces auto postcycle		= tag_value < _Postcycle_ >;
	};

/***********************************************************************************************************************/

// position:

	template<auto _Out_, auto _End_, auto _In_>
	struct T_accord<AN::repeat, AT::position, _position<_Out_, _End_, _In_>>
	{
		// should static assert against tagnames.

		nik_ces auto out	= tag_value < _Out_ >;
		nik_ces auto end	= tag_value < _End_ >;
		nik_ces auto in		= tag_value <  _In_ >;
	};

/***********************************************************************************************************************/

// cycle:

	template
	<
		typename Chord,

		auto _Op0_, auto _Arg01_, auto _Arg02_,
		auto _Op1_, auto _Arg11_, auto _Arg12_
	>
	struct T_accord
	<
		AN::repeat, AT::cycle, Chord,

		_break  < _Op0_ , _Arg01_ , _Arg02_ >,
		_action < _Op1_ , _Arg11_ , _Arg12_ >
	>
	{
		nik_ces auto loop_predicate	= tr_argcompose  < _Op0_, _Arg01_, _Arg02_ >;
		nik_ces auto assign_function	= tr_sidecompose < _Op1_, _Arg11_, _Arg12_ >;

		nik_ces auto out_next		= Chord::out::axis::next;
	};

/***********************************************************************************************************************/

// precycle:

	template<typename Chord>
	struct T_accord<AN::repeat, AT::precycle, Chord>
	{
		nik_ces auto pre_out_next = tr_pre_note_next<typename Chord::out>;
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename Chord, typename Cycle>
	struct T_accord<AN::repeat, AT::postcycle, Chord, Cycle>
	{
		nik_ces auto post_assign_function = tr_post_assign_function<Chord::out::ival::is_right_closed, Cycle>;
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

	// map:

		// { out ) ; { in, end ) ---      major chord // aligns center
		// { out ] ; { in, end ) ---  augmented chord // aligns left

		// { out ) ; { in, end ] ---      minor chord // aligns right
		// { out ] ; { in, end ] --- diminished chord // aligns center

		//	0. All intervals are tethered to the one with an explicitly declared endpoint.
		//	1. If prev and peek, reverse iterate end precycle.
		//	2. For each left endpoint, if open, iterate precycle.
		//	3. Evaluate the common (closing) loop, peeking if necessary.
		//	4. If the subject iterator is right closed, then assign postcycle.
		//	5. If (4), then for each other right endpoint, when open, iterate postcycle.
		//	6. If prev and peek, iterate end to reset postcycle.

/***********************************************************************************************************************/

// label:

	template<typename Label>
	struct T_accord<AN::map, AT::label, Label> : public T_accord<AN::repeat, AT::label, Label> { };

/***********************************************************************************************************************/

// position:

	template<auto _Out_, auto _In_, auto _End_>
	struct T_accord<AN::map, AT::position, _position<_Out_, _In_, _End_>>
	{
		// should static assert against tagnames.

		nik_ces auto out	= tag_value < _Out_ >;
		nik_ces auto in		= tag_value <  _In_ >;
		nik_ces auto end	= tag_value < _End_ >;
	};

/***********************************************************************************************************************/

// cycle:

	template
	<
		typename Chord,

		auto _Op0_, auto _Arg01_, auto _Arg02_,
		auto _Op1_, auto _Arg11_, auto _Arg12_
	>
	struct T_accord
	<
		AN::map, AT::cycle, Chord,

		_break  < _Op0_ , _Arg01_ , _Arg02_ >,
		_action < _Op1_ , _Arg11_ , _Arg12_ >
	>
	{
		private:

			using in		= typename Chord::in;
			using quality		= typename Chord::quality;

		public:

			nik_ces auto loop_predicate	= tr_loopcompose < _Op0_, _Arg01_ , _Arg02_ , in , quality >;
			nik_ces auto assign_function	= tr_sidecompose < _Op1_, _Arg11_ , _Arg12_                >;

			nik_ces auto out_next		= Chord::out::axis::next;
			nik_ces auto in_next		= Chord::in::axis::next;
	};

/***********************************************************************************************************************/

// precycle:

	template<typename Chord>
	struct T_accord<AN::map, AT::precycle, Chord>
	{
		nik_ces auto pre_end_prev	= tr_pre_tonic_prev < typename Chord::in  , typename Chord::quality >;
		nik_ces auto pre_out_next	= tr_pre_note_next  < typename Chord::out                           >;
		nik_ces auto pre_in_next	= tr_pre_note_next  < typename Chord::in                            >;
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename Chord, typename Cycle>
	struct T_accord<AN::map, AT::postcycle, Chord, Cycle>
	{
		private:

			nik_ces auto in_is_right_closed		= Chord::in::ival::is_right_closed;
			nik_ces auto loop_broke_early		= Chord::quality::augmented::is_early;
			nik_ces auto is_post_assign		= in_is_right_closed || loop_broke_early;

		public:

			nik_ces auto post_assign_function	= tr_post_assign_function<is_post_assign, Cycle>;

			nik_ces auto post_out_next = tr_post_tone_next  < typename Chord::out , typename Chord::quality >;
			nik_ces auto post_in_next  = tr_post_note_next  < loop_broke_early    , typename Chord::in      >;
			nik_ces auto post_end_next = tr_post_tonic_next < typename Chord::in  , typename Chord::quality >;
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

