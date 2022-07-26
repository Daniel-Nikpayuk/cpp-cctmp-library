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

	template<auto... Vs> nik_ce auto _constant_		= cctmp::template _constant_<Vs...>;

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

		nik_ces key_type found			=  6;
		nik_ces key_type postfound		=  7;
		nik_ces key_type done			=  8;
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

// post match predicate:

	template<auto is_post_match_predicate, typename cycle>
	nik_ce auto tr_post_match_predicate = if_then_else
	<
		is_post_match_predicate,
		cycle::match_predicate,
		_constant_<false>
	>;

/***********************************************************************************************************************/

// post action function:

	template<auto is_post_action_function, typename cycle>
	nik_ce auto tr_post_action_function = if_then_else
	<
		is_post_action_function,
		cycle::action_function,
		_id_
	>;

/***********************************************************************************************************************/

// post combine function:

	template<auto is_post_combine_function, typename cycle>
	nik_ce auto tr_post_combine_function = if_then_else
	<
		is_post_combine_function,
		cycle::combine_function,
		_id_
	>;

/***********************************************************************************************************************/

// post mutate function:

	template<auto is_post_mutate_function, typename cycle>
	nik_ce auto tr_post_mutate_function = if_then_else
	<
		is_post_mutate_function,
		cycle::mutate_function,
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
		_mutate < _Op1_ , _Arg11_ , _Arg12_ >
	>
	{
		nik_ces auto loop_predicate	= tr_argcompose  < _Op0_ , _Arg01_ , _Arg02_ >;
		nik_ces auto mutate_function	= tr_sidecompose < _Op1_ , _Arg11_ , _Arg12_ >;

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
		nik_ces auto post_mutate_function = tr_post_mutate_function<Chord::out::ival::is_right_closed, Cycle>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold (ray):

/***********************************************************************************************************************/

// label:

	template<typename Label>
	struct T_accord<AN::fold, AT::label, Label> : public T_accord<AN::repeat, AT::label, Label> { };

/***********************************************************************************************************************/

// position:

	template<auto _Out_, auto _In_, auto _End_>
	struct T_accord<AN::fold, AT::position, _position<_Out_, _In_, _End_>>
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
		AN::fold, AT::cycle, Chord,

		_break   < _Op0_ , _Arg01_ , _Arg02_ >,
		_combine < _Op1_ , _Arg11_ , _Arg12_ >
	>
	{
		nik_ces auto loop_predicate	= tr_argcompose < _Op0_ , _Arg01_ , _Arg02_ >;
		nik_ces auto combine_function	= tr_argcompose < _Op1_ , _Arg11_ , _Arg12_ >;

		nik_ces auto in_next		= Chord::in::axis::next;
	};

/***********************************************************************************************************************/

// precycle:

	template<typename Chord>
	struct T_accord<AN::fold, AT::precycle, Chord>
	{
		nik_ces auto pre_in_next = tr_pre_note_next<typename Chord::in>;
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename Chord, typename Cycle>
	struct T_accord<AN::fold, AT::postcycle, Chord, Cycle>
	{
		nik_ces auto post_combine_function = tr_post_combine_function<Chord::in::ival::is_right_closed, Cycle>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find first (ray):

/***********************************************************************************************************************/

// label:

	template<auto _Precycle_, auto _Cycle_, auto _Postcycle_, auto _Found_, auto _Done_>
	struct T_accord<AN::find_first, AT::label, _label<_Precycle_, _Cycle_, _Postcycle_, _Found_, _Done_>>
	{
		// should static assert against tagnames.

		nik_ces auto precycle		= tag_value <  _Precycle_ >;
		nik_ces auto cycle		= tag_value <     _Cycle_ >;
		nik_ces auto postcycle		= tag_value < _Postcycle_ >;
		nik_ces auto found		= tag_value <     _Found_ >;
		nik_ces auto done		= tag_value <      _Done_ >;
	};

/***********************************************************************************************************************/

// position:

	template<typename Position>
	struct T_accord<AN::find_first, AT::position, Position> : public T_accord<AN::fold, AT::position, Position> { };

/***********************************************************************************************************************/

// cycle:

	template
	<
		typename Chord,

		auto _Op0_, auto _Arg01_, auto _Arg02_,
		auto _Op1_, auto _Arg11_
	>
	struct T_accord
	<
		AN::find_first, AT::cycle, Chord,

		_break < _Op0_ , _Arg01_ , _Arg02_ >,
		_match < _Op1_ , _Arg11_           >
	>
	{
		nik_ces auto loop_predicate	= tr_argcompose < _Op0_ , _Arg01_ , _Arg02_ >;
		nik_ces auto match_predicate	= tr_argcompose < _Op1_ , _Arg11_           >;

		nik_ces auto in_next		= Chord::in::axis::next;
	};

/***********************************************************************************************************************/

// precycle:

	template<typename Chord>
	struct T_accord<AN::find_first, AT::precycle, Chord>
	{
		nik_ces auto pre_in_next = tr_pre_note_next<typename Chord::in>;
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename Chord, typename Cycle>
	struct T_accord<AN::find_first, AT::postcycle, Chord, Cycle>
	{
		nik_ces auto post_match_predicate = tr_post_match_predicate<Chord::in::ival::is_right_closed, Cycle>;
	};

/***********************************************************************************************************************/

// found:

	template<auto _Op_, auto _Arg1_, auto _Arg2_, auto _Next_>
	struct T_accord
	<
		AN::find_first, AT::found,

		_mutate   < _Op_ , _Arg1_ , _Arg2_ >,
		_out_iter <                 _Next_ >
	>
	{
		nik_ces auto found_mutate_function	= tr_sidecompose < _Op_ , _Arg1_ , _Arg2_ >;

		nik_ces auto found_out_next		= tag_value < _Next_ >;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find all (ray):

/***********************************************************************************************************************/

// label:

	template<auto _Precycle_, auto _Cycle_, auto _Postcycle_, auto _Found_, auto _Postfound_, auto _Done_>
	struct T_accord<AN::find_all, AT::label, _label<_Precycle_, _Cycle_, _Postcycle_, _Found_, _Postfound_, _Done_>>
	{
		// should static assert against tagnames.

		nik_ces auto precycle		= tag_value <  _Precycle_ >;
		nik_ces auto cycle		= tag_value <     _Cycle_ >;
		nik_ces auto postcycle		= tag_value < _Postcycle_ >;
		nik_ces auto found		= tag_value <     _Found_ >;
		nik_ces auto postfound		= tag_value < _Postfound_ >;
		nik_ces auto done		= tag_value <      _Done_ >;
	};

/***********************************************************************************************************************/

// position:

	template<typename Position>
	struct T_accord<AN::find_all, AT::position, Position> : public T_accord<AN::fold, AT::position, Position> { };

/***********************************************************************************************************************/

// cycle:

	template
	<
		typename Chord,

		auto _Op0_, auto _Arg01_, auto _Arg02_,
		auto _Op1_, auto _Arg11_
	>
	struct T_accord
	<
		AN::find_all, AT::cycle, Chord,

		_break < _Op0_ , _Arg01_ , _Arg02_ >,
		_match < _Op1_ , _Arg11_           >
	>
	{
		nik_ces auto loop_predicate	= tr_argcompose < _Op0_ , _Arg01_ , _Arg02_ >;
		nik_ces auto match_predicate	= tr_argcompose < _Op1_ , _Arg11_           >;

		nik_ces auto in_next		= Chord::in::axis::next;
	};

/***********************************************************************************************************************/

// precycle:

	template<typename Chord>
	struct T_accord<AN::find_all, AT::precycle, Chord>
	{
		nik_ces auto pre_in_next = tr_pre_note_next<typename Chord::in>;
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename Chord, typename Cycle>
	struct T_accord<AN::find_all, AT::postcycle, Chord, Cycle>
	{
		nik_ces auto post_match_predicate = tr_post_match_predicate<Chord::in::ival::is_right_closed, Cycle>;
	};

/***********************************************************************************************************************/

// found:

	template<typename Chord, auto _Op_, auto _Arg1_, auto _Arg2_, auto _Next_>
	struct T_accord
	<
		AN::find_all, AT::found, Chord,

		_mutate   < _Op_ , _Arg1_ , _Arg2_ >,
		_out_iter <                 _Next_ >
	>
	{
		nik_ces auto found_mutate_function	= tr_sidecompose < _Op_ , _Arg1_ , _Arg2_ >;

		nik_ces auto found_out_next		= tag_value < _Next_ >;
		nik_ces auto found_in_next		= Chord::in::axis::next;
	};

/***********************************************************************************************************************/

// postfound:

	template<typename Found>
	struct T_accord<AN::find_all, AT::postfound, Found>
	{
		nik_ces auto postfound_mutate_function	= Found::found_mutate_function;

		nik_ces auto postfound_out_next		= Found::found_out_next;
	};

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

	template<typename Position>
	struct T_accord<AN::map, AT::position, Position> : public T_accord<AN::fold, AT::position, Position> { };

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
		_mutate < _Op1_ , _Arg11_ , _Arg12_ >
	>
	{
		private:

			using in		= typename Chord::in;
			using quality		= typename Chord::quality;

		public:

			nik_ces auto loop_predicate	= tr_loopcompose < _Op0_ , _Arg01_ , _Arg02_ , in , quality >;
			nik_ces auto mutate_function	= tr_sidecompose < _Op1_ , _Arg11_ , _Arg12_                >;

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
			nik_ces auto is_post_mutate		= in_is_right_closed || loop_broke_early;

		public:

			nik_ces auto post_mutate_function	= tr_post_mutate_function<is_post_mutate, Cycle>;

			nik_ces auto post_out_next = tr_post_tone_next  < typename Chord::out , typename Chord::quality >;
			nik_ces auto post_in_next  = tr_post_note_next  < loop_broke_early    , typename Chord::in      >;
			nik_ces auto post_end_next = tr_post_tonic_next < typename Chord::in  , typename Chord::quality >;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// zip (line):

/***********************************************************************************************************************/

// label:

	template<typename Label>
	struct T_accord<AN::zip, AT::label, Label> : public T_accord<AN::repeat, AT::label, Label> { };

/***********************************************************************************************************************/

// position:

	template<auto _Out_, auto _CarIn_, auto _CdrIn_, auto _End_>
	struct T_accord<AN::zip, AT::position, _position<_Out_, _CarIn_, _CdrIn_, _End_>>
	{
		// should static assert against tagnames.

		nik_ces auto out	= tag_value <   _Out_ >;
		nik_ces auto car_in	= tag_value < _CarIn_ >;
		nik_ces auto cdr_in	= tag_value < _CdrIn_ >;
		nik_ces auto end	= tag_value <   _End_ >;
	};

/***********************************************************************************************************************/

// cycle:

	template
	<
		typename Chord,

		auto _Op0_, auto _Arg01_, auto _Arg02_,
		auto _Op1_, auto _Arg11_, auto _Arg12_,
		auto _Op2_, auto _Arg21_, auto _Arg22_
	>
	struct T_accord
	<
		AN::zip, AT::cycle, Chord,

		_break  < _Op0_ , _Arg01_ , _Arg02_ >,
		_action < _Op1_ , _Arg11_ , _Arg12_ >,
		_mutate < _Op2_ , _Arg21_ , _Arg22_ >
	>
	{
		private:

			using cdr_in		= typename Chord::cdr_in;
			using quality		= typename Chord::quality;

		public:

			nik_ces auto loop_predicate	= tr_loopcompose < _Op0_ , _Arg01_ , _Arg02_ , cdr_in , quality >;
			nik_ces auto action_function	= tr_argcompose  < _Op1_ , _Arg11_ , _Arg12_                    >;
			nik_ces auto mutate_function	= tr_sidecompose < _Op2_ , _Arg21_ , _Arg22_                    >;

			nik_ces auto out_next		= Chord::out::axis::next;
			nik_ces auto car_in_next	= Chord::car_in::axis::next;
			nik_ces auto cdr_in_next	= Chord::cdr_in::axis::next;
	};

/***********************************************************************************************************************/

// precycle:

	template<typename Chord>
	struct T_accord<AN::zip, AT::precycle, Chord>
	{
		nik_ces auto pre_end_prev	= tr_pre_tonic_prev < typename Chord::cdr_in , typename Chord::quality >;
		nik_ces auto pre_out_next	= tr_pre_note_next  < typename Chord::out                              >;
		nik_ces auto pre_car_in_next	= tr_pre_note_next  < typename Chord::car_in                           >;
		nik_ces auto pre_cdr_in_next	= tr_pre_note_next  < typename Chord::cdr_in                           >;
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename Chord, typename Cycle>
	struct T_accord<AN::zip, AT::postcycle, Chord, Cycle>
	{
		private:

			nik_ces auto cdr_in_is_right_closed	= Chord::cdr_in::ival::is_right_closed;
			nik_ces auto loop_broke_early		= Chord::quality::augmented::is_early;
			nik_ces auto is_post_operate		= cdr_in_is_right_closed || loop_broke_early;

		public:

			nik_ces auto post_action_function	= tr_post_action_function < is_post_operate , Cycle >;
			nik_ces auto post_mutate_function	= tr_post_mutate_function < is_post_operate , Cycle >;

		nik_ces auto post_out_next    = tr_post_tone_next  < typename Chord::out    , typename Chord::quality >;
		nik_ces auto post_car_in_next = tr_post_tone_next  < typename Chord::car_in , typename Chord::quality >;
		nik_ces auto post_cdr_in_next = tr_post_note_next  < loop_broke_early       , typename Chord::cdr_in  >;
		nik_ces auto post_end_next    = tr_post_tonic_next < typename Chord::cdr_in , typename Chord::quality >;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fasten (line):

/***********************************************************************************************************************/

// label:

	template<typename Label>
	struct T_accord<AN::fasten, AT::label, Label> : public T_accord<AN::repeat, AT::label, Label> { };

/***********************************************************************************************************************/

// position:

	template<auto _Out_, auto _Aux_, auto _In_, auto _CarIn_, auto _CdrIn_, auto _End_>
	struct T_accord<AN::fasten, AT::position, _position<_Out_, _Aux_, _In_, _CarIn_, _CdrIn_, _End_>>
	{
		// should static assert against tagnames.

		nik_ces auto out	= tag_value <   _Out_ >;
		nik_ces auto aux	= tag_value <   _Aux_ >;
		nik_ces auto in		= tag_value <    _In_ >;
		nik_ces auto car_in	= tag_value < _CarIn_ >;
		nik_ces auto cdr_in	= tag_value < _CdrIn_ >;
		nik_ces auto end	= tag_value <   _End_ >;
	};

/***********************************************************************************************************************/

// cycle:

	template
	<
		typename Chord,

		auto _Op0_, auto _Arg01_, auto _Arg02_,
		auto _Op1_, auto _Arg11_, auto _Arg12_,
		auto _Op2_, auto _Arg21_, auto _Arg22_,
		auto _Op3_, auto _Arg31_, auto _Arg32_,
		auto _Op4_, auto _Arg41_, auto _Arg42_, auto _Arg43_,
		auto _Op5_, auto _Arg51_, auto _Arg52_, auto _Arg53_
	>
	struct T_accord
	<
		AN::fasten, AT::cycle, Chord,

		_break    < _Op0_ , _Arg01_ , _Arg02_           >,
		_action   < _Op1_ , _Arg11_ , _Arg12_           >,
		_combine  < _Op2_ , _Arg21_ , _Arg22_           >,
		_mutate   < _Op3_ , _Arg31_ , _Arg32_           >,
		_in_iter  < _Op4_ , _Arg41_ , _Arg42_ , _Arg43_ >,
		_aux_iter < _Op5_ , _Arg51_ , _Arg52_ , _Arg53_ >
	>
	{
		private:

			using cdr_in		= typename Chord::cdr_in;
			using quality		= typename Chord::quality;

		public:

			nik_ces auto loop_predicate	= tr_loopcompose < _Op0_ , _Arg01_ , _Arg02_ , cdr_in , quality >;
			nik_ces auto action_function	= tr_argcompose  < _Op1_ , _Arg11_ , _Arg12_                    >;
			nik_ces auto combine_function	= tr_argcompose  < _Op2_ , _Arg21_ , _Arg22_                    >;
			nik_ces auto mutate_function	= tr_sidecompose < _Op3_ , _Arg31_ , _Arg32_                    >;
			nik_ces auto in_next		= tr_argcompose  < _Op4_ , _Arg41_ , _Arg42_ , _Arg43_          >;
			nik_ces auto aux_next		= tr_argcompose  < _Op5_ , _Arg51_ , _Arg52_ , _Arg53_          >;

			nik_ces auto out_next		= Chord::out::axis::next;
			nik_ces auto car_in_next	= Chord::car_in::axis::next;
			nik_ces auto cdr_in_next	= Chord::cdr_in::axis::next;
	};

/***********************************************************************************************************************/

// precycle:

	template<typename Chord>
	struct T_accord<AN::fasten, AT::precycle, Chord>
	{
		nik_ces auto pre_end_prev	= tr_pre_tonic_prev < typename Chord::cdr_in , typename Chord::quality >;
		nik_ces auto pre_out_next	= tr_pre_note_next  < typename Chord::out                              >;
		nik_ces auto pre_car_in_next	= tr_pre_note_next  < typename Chord::car_in                           >;
		nik_ces auto pre_cdr_in_next	= tr_pre_note_next  < typename Chord::cdr_in                           >;
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename Chord, typename Cycle>
	struct T_accord<AN::fasten, AT::postcycle, Chord, Cycle>
	{
		private:

			nik_ces auto cdr_in_is_right_closed	= Chord::cdr_in::ival::is_right_closed;
			nik_ces auto loop_broke_early		= Chord::quality::augmented::is_early;
			nik_ces auto is_post_operate		= cdr_in_is_right_closed || loop_broke_early;

		public:

			nik_ces auto post_action_function	= tr_post_action_function  < is_post_operate , Cycle >;
			nik_ces auto post_combine_function	= tr_post_combine_function < is_post_operate , Cycle >;
			nik_ces auto post_mutate_function	= tr_post_mutate_function  < is_post_operate , Cycle >;

		nik_ces auto post_out_next    = tr_post_tone_next  < typename Chord::out    , typename Chord::quality >;
		nik_ces auto post_car_in_next = tr_post_tone_next  < typename Chord::car_in , typename Chord::quality >;
		nik_ces auto post_cdr_in_next = tr_post_note_next  < loop_broke_early       , typename Chord::cdr_in  >;
		nik_ces auto post_end_next    = tr_post_tonic_next < typename Chord::cdr_in , typename Chord::quality >;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// glide (line):

/***********************************************************************************************************************/

// label:

	template<typename Label>
	struct T_accord<AN::glide, AT::label, Label> : public T_accord<AN::repeat, AT::label, Label> { };

/***********************************************************************************************************************/

// position:

	template<typename Position>
	struct T_accord<AN::glide, AT::position, Position> : public T_accord<AN::zip, AT::position, Position> { };

/***********************************************************************************************************************/

// cycle:

	template
	<
		typename Chord,

		auto _Op0_, auto _Arg01_, auto _Arg02_,
		auto _Op1_, auto _Arg11_, auto _Arg12_,
		auto _Op2_, auto _Arg21_, auto _Arg22_
	>
	struct T_accord
	<
		AN::glide, AT::cycle, Chord,

		_break   < _Op0_ , _Arg01_ , _Arg02_ >,
		_action  < _Op1_ , _Arg11_ , _Arg12_ >,
		_combine < _Op2_ , _Arg21_ , _Arg22_ >
	>
	{
		private:

			using cdr_in		= typename Chord::cdr_in;
			using quality		= typename Chord::quality;

		public:

			nik_ces auto loop_predicate	= tr_loopcompose < _Op0_ , _Arg01_ , _Arg02_ , cdr_in , quality >;
			nik_ces auto action_function	= tr_argcompose  < _Op1_ , _Arg11_ , _Arg12_ >;
			nik_ces auto combine_function	= tr_argcompose  < _Op2_ , _Arg21_ , _Arg22_ >;

			nik_ces auto car_in_next	= Chord::car_in::axis::next;
			nik_ces auto cdr_in_next	= Chord::cdr_in::axis::next;
	};

/***********************************************************************************************************************/

// precycle:

	template<typename Chord>
	struct T_accord<AN::glide, AT::precycle, Chord>
	{
		nik_ces auto pre_end_prev	= tr_pre_tonic_prev < typename Chord::cdr_in , typename Chord::quality >;
		nik_ces auto pre_car_in_next	= tr_pre_note_next  < typename Chord::car_in                           >;
		nik_ces auto pre_cdr_in_next	= tr_pre_note_next  < typename Chord::cdr_in                           >;
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename Chord, typename Cycle>
	struct T_accord<AN::glide, AT::postcycle, Chord, Cycle>
	{
		private:

			nik_ces auto cdr_in_is_right_closed	= Chord::cdr_in::ival::is_right_closed;
			nik_ces auto loop_broke_early		= Chord::quality::augmented::is_early;
			nik_ces auto is_post_operate		= cdr_in_is_right_closed || loop_broke_early;

		public:

			nik_ces auto post_action_function	= tr_post_action_function  < is_post_operate , Cycle >;
			nik_ces auto post_combine_function	= tr_post_combine_function < is_post_operate , Cycle >;

		nik_ces auto post_car_in_next = tr_post_tone_next  < typename Chord::car_in , typename Chord::quality >;
		nik_ces auto post_cdr_in_next = tr_post_note_next  < loop_broke_early       , typename Chord::cdr_in  >;
		nik_ces auto post_end_next    = tr_post_tonic_next < typename Chord::cdr_in , typename Chord::quality >;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_one_cycle_generics

