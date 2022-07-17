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

// functional:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

namespace cctmp_functional {

	using key_type						= typename cctmp::key_type;
	using index_type					= typename cctmp::index_type;
	using AOP						= typename cctmp::AOP;
	using BN						= typename cctmp::BN;
	using BD						= typename cctmp::BD;
	using MD						= typename cctmp::MD;

	using T_block_variable					= typename cctmp::T_block_variable;
	using T_block_function					= typename cctmp::T_block_function;
	using T_block_segment					= typename cctmp::T_block_segment;
	using T_block_fold					= typename cctmp::T_block_fold;
	using T_block_parse					= typename cctmp::T_block_parse;
	using T_block_cascade					= typename cctmp::T_block_cascade;
	using T_start						= typename cctmp::T_start;

	template<auto... Vs> using T_pack_Vs			= typename cctmp::template T_pack_Vs<Vs...>;
	template<template<auto...> class... Bs> using T_store_B	= typename cctmp::template T_store_B<Bs...>;
	template<auto... Vs> using T_overload			= typename cctmp::template T_overload<Vs...>;
	template<typename... Ts> using tuple			= typename cctmp::template tuple<Ts...>;

	nik_ce auto _zero					= cctmp::_zero;
	nik_ce auto _one					= cctmp::_one;

	nik_ce auto U_null_Vs					= cctmp::U_null_Vs;

	nik_ce auto _h1						= cctmp::_h1;
	nik_ce auto _h1_pair					= cctmp::_h1_pair;
	nik_ce auto _register					= cctmp::_register;
	nik_ce auto _argument					= cctmp::_argument;
	nik_ce auto _constant					= cctmp::_constant;
	nik_ce auto _value					= cctmp::_value;

	nik_ce auto _custom					= cctmp::_custom;
	nik_ce auto _method					= cctmp::_method;

	nik_ce auto H_curry_equal				= cctmp::template H_curry<cctmp::_equal_>;
	nik_ce auto H_curry_less_than				= cctmp::template H_curry<cctmp::_less_than_>;

	nik_ce auto U_to_list					= cctmp::U_to_list;
	nik_ce auto U_length					= cctmp::U_length;
	nik_ce auto U_car					= cctmp::U_car;
	nik_ce auto U_find					= cctmp::U_find;
	nik_ce auto U_custom					= cctmp::U_custom;
	nik_ce auto U_tailor					= cctmp::U_tailor;

	nik_ce auto U_block_filter				= cctmp::U_block_filter;
	nik_ce auto U_block_split				= cctmp::U_block_split;
	nik_ce auto U_block_left				= cctmp::U_block_left;
	nik_ce auto U_block_alter				= cctmp::U_block_alter;

	nik_ce auto H_partial_same				= cctmp::template H_partial<cctmp::U_same>;

	template<typename T> nik_ce auto U_store_T		= cctmp::template U_store_T<T>;
	template<auto... Vs> nik_ce auto U_pack_Vs		= cctmp::template U_pack_Vs<Vs...>;

	template<auto... Vs> nik_ce auto overload		= cctmp::template overload<Vs...>;
	template<auto... Vs> nik_ce auto alias			= cctmp::template alias<Vs...>;

	template<auto... Vs> nik_ce auto U_partial		= cctmp::template U_partial<Vs...>;

	template<auto... Vs> nik_ce auto find_			= cctmp::template find_<Vs...>;
	template<auto... Vs> nik_ce auto unpack_		= cctmp::template unpack_<Vs...>;

	template<auto... Vs> nik_ce auto find			= cctmp::template find<Vs...>;
	template<auto... Vs> nik_ce auto compel			= cctmp::template compel<Vs...>;
	template<auto... Vs> nik_ce auto custom			= cctmp::template custom<Vs...>;
	template<auto... Vs> nik_ce auto unite			= cctmp::template unite<Vs...>;
	template<auto... Vs> nik_ce auto action			= cctmp::template action<Vs...>;
	template<auto... Vs> nik_ce auto cut			= cctmp::template cut<Vs...>;
	template<auto... Vs> nik_ce auto copy			= cctmp::template copy<Vs...>;
	template<auto... Vs> nik_ce auto write			= cctmp::template write<Vs...>;
	template<auto... Vs> nik_ce auto paste			= cctmp::template paste<Vs...>;
	template<auto... Vs> nik_ce auto branch			= cctmp::template branch<Vs...>;
	template<auto... Vs> nik_ce auto value			= cctmp::template value<Vs...>;
	template<auto...> nik_ce auto stage			= cctmp::template stage<>;

	template<auto... Vs> nik_ce auto controller		= cctmp::template controller<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// block:

	template<auto Op>
	struct TP_unpack
	{
		template<auto d, auto p, auto... Vs>
		nik_ces auto result = unpack_<p, U_custom, Op, d, Vs...>;

	}; template<auto Op>
		nik_ce auto UP_unpack = U_store_T<TP_unpack<Op>>;

/***********************************************************************************************************************/

// at:

	struct TP_at
	{
		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_block_variable::template result<d, n, U_car, Vs...>;

	}; nik_ce auto UP_at = U_store_T<TP_at>;

	using TL_at		= TP_unpack<UP_at>;
	nik_ce auto UL_at	= UP_unpack<UP_at>;

	template<auto n, auto... Vs>
	nik_ce auto pack_at = TP_at::template result<MD::initial_depth, n, Vs...>;

	template<auto p, auto n, auto d = MD::initial_depth>
	nik_ce auto list_at = TL_at::template result<d, p, n>;

// left:

	struct TP_left
	{
		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_block_function::template result<d, U_null_Vs, n, U_block_left, Vs...>;

	}; nik_ce auto UP_left = U_store_T<TP_left>;

	using TL_left		= TP_unpack<UP_left>;
	nik_ce auto UL_left	= UP_unpack<UP_left>;

	template<auto n, auto... Vs>
	nik_ce auto pack_left = TP_left::template result<MD::initial_depth, n, Vs...>;

	template<auto p, auto n, auto d = MD::initial_depth>
	nik_ce auto list_left = TL_left::template result<d, p, n>;

// right:

	struct TP_right
	{
		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_block_variable::template result<d, n, U_to_list, Vs...>;

	}; nik_ce auto UP_right = U_store_T<TP_right>;

	using TL_right		= TP_unpack<UP_right>;
	nik_ce auto UL_right	= UP_unpack<UP_right>;

	template<auto n, auto... Vs>
	nik_ce auto pack_right = TP_right::template result<MD::initial_depth, n, Vs...>;

	template<auto p, auto n, auto d = MD::initial_depth>
	nik_ce auto list_right = TL_right::template result<d, p, n>;

// split:

	struct TP_split
	{
		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_block_function::template result<d, U_null_Vs, n, U_block_split, Vs...>;

	}; nik_ce auto UP_split = U_store_T<TP_split>;

	using TL_split		= TP_unpack<UP_split>;
	nik_ce auto UL_split	= UP_unpack<UP_split>;

	template<auto n, auto... Vs>
	nik_ce auto pack_split = TP_split::template result<MD::initial_depth, n, Vs...>;

	template<auto p, auto n, auto d = MD::initial_depth>
	nik_ce auto list_split = TL_split::template result<d, p, n>;

// cut:

	struct TP_cut
	{
		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_block_function::template result<d, U_null_Vs, n, U_block_filter, Vs...>;

	}; nik_ce auto UP_cut = U_store_T<TP_cut>;

	using TL_cut		= TP_unpack<UP_cut>;
	nik_ce auto UL_cut	= UP_unpack<UP_cut>;

	template<auto n, auto... Vs>
	nik_ce auto pack_cut = TP_cut::template result<MD::initial_depth, n, Vs...>;

	template<auto p, auto n, auto d = MD::initial_depth>
	nik_ce auto list_cut = TL_cut::template result<d, p, n>;

// amend:

	struct TP_amend
	{
		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_block_function::template result<d, U_null_Vs, n, U_block_alter, Vs...>;

	}; nik_ce auto UP_amend = U_store_T<TP_amend>;

	using TL_amend		= TP_unpack<UP_amend>;
	nik_ce auto UL_amend	= UP_unpack<UP_amend>;

	template<auto n, auto... Vs>
	nik_ce auto pack_amend = TP_amend::template result<MD::initial_depth, n, Vs...>;

	template<auto p, auto n, auto d = MD::initial_depth>
	nik_ce auto list_amend = TL_amend::template result<d, p, n>;

// segment:

	using T_segment		= T_block_segment;
	nik_ce auto U_segment	= U_store_T<T_segment>;

	template<auto n, auto s = index_type{0}>
	nik_ce auto segment = T_segment::template result<MD::initial_depth, n, s>;

// fold:

	struct TP_fold
	{
		template<auto d, auto op, auto V, auto... Vs>
		nik_ces auto result = T_block_fold::template result<d, sizeof...(Vs), op, V, Vs...>;

	}; nik_ce auto UP_fold = U_store_T<TP_fold>;

	using TL_fold		= TP_unpack<UP_fold>;
	nik_ce auto UL_fold	= UP_unpack<UP_fold>;

	template<auto op, auto V, auto... Vs>
	nik_ce auto pack_fold = TP_fold::template result<MD::initial_depth, op, V, Vs...>;

	template<auto p, auto op, auto V, auto d = MD::initial_depth>
	nik_ce auto list_fold = TL_fold::template result<d, p, op, V>;

// parse (fold with one lookahead):

	struct TP_parse
	{
		template<auto d, auto op, auto V, auto... Vs>
		nik_ces auto result = T_block_parse::template result<d, sizeof...(Vs)-1, op, V, Vs...>;

	}; nik_ce auto UP_parse = U_store_T<TP_parse>;

	using TL_parse		= TP_unpack<UP_parse>;
	nik_ce auto UL_parse	= UP_unpack<UP_parse>;

	template<auto op, auto V, auto... Vs>
	nik_ce auto pack_parse = TP_parse::template result<MD::initial_depth, op, V, Vs...>;

	template<auto p, auto op, auto V, auto d = MD::initial_depth>
	nik_ce auto list_parse = TL_parse::template result<d, p, op, V>;

// cascade:

	struct TP_cascade
	{
		template<auto d, auto op, auto V, auto... Vs>
		nik_ces auto result = T_block_cascade::template result<d, sizeof...(Vs), op, V, Vs...>;

	}; nik_ce auto UP_cascade = U_store_T<TP_cascade>;

	using TL_cascade	= TP_unpack<UP_cascade>;
	nik_ce auto UL_cascade	= UP_unpack<UP_cascade>;

	template<auto op, auto V, auto... Vs>
	nik_ce auto pack_cascade = TP_cascade::template result<MD::initial_depth, op, V, Vs...>;

	template<auto p, auto op, auto V, auto d = MD::initial_depth>
	nik_ce auto list_cascade = TL_cascade::template result<d, p, op, V>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// mutators:

/***********************************************************************************************************************/

// erase:

	struct TP_erase
	{
		nik_ces auto c = controller
		<
			compel < _custom , _h1_pair >,
			stage  <                    >,
			unite  <             _value >
		>;

		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_start::template result<d, c>(U_pack_Vs<UP_cut, n, Vs...>, U_null_Vs, U_null_Vs);

	}; nik_ce auto UP_erase = U_store_T<TP_erase>;

	using TL_erase		= TP_unpack<UP_erase>;
	nik_ce auto UL_erase	= UP_unpack<UP_erase>;

	template<auto n, auto... Vs>
	nik_ce auto pack_erase = TP_erase::template result<MD::initial_depth, n, Vs...>;

	template<auto p, auto n, auto d = MD::initial_depth>
	nik_ce auto list_erase = TL_erase::template result<d, p, n>;

// mutate (generic):

	template<auto Part>
	struct TP_mutate
	{
		nik_ces auto c = controller
		<
			compel < _custom , _h1_pair  >,
			stage  <                     >,
			copy   < _zero   , _register >,
			unite  <             _value  >
		>;

		template<auto d, auto n, auto V, auto... Vs>
		nik_ces auto result = T_start::template result<d, c, V>(U_pack_Vs<Part, n, Vs...>, U_null_Vs, U_null_Vs);
	};

// insert:

	using TP_insert		= TP_mutate<UP_split>;
	nik_ce auto UP_insert	= U_store_T<TP_insert>;

	using TL_insert		= TP_unpack<UP_insert>;
	nik_ce auto UL_insert	= UP_unpack<UP_insert>;

	template<auto n, auto V, auto... Vs>
	nik_ce auto pack_insert = TP_insert::template result<MD::initial_depth, n, V, Vs...>;

	template<auto p, auto n, auto V, auto d = MD::initial_depth>
	nik_ce auto list_insert = TL_insert::template result<d, p, n, V>;

// replace:

	using TP_replace	= TP_mutate<UP_cut>;
	nik_ce auto UP_replace	= U_store_T<TP_replace>;

	using TL_replace	= TP_unpack<UP_replace>;
	nik_ce auto UL_replace	= UP_unpack<UP_replace>;

	template<auto n, auto V, auto... Vs>
	nik_ce auto pack_replace = TP_replace::template result<MD::initial_depth, n, V, Vs...>;

	template<auto p, auto n, auto V, auto d = MD::initial_depth>
	nik_ce auto list_replace = TL_replace::template result<d, p, n, V>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ordered:

/***********************************************************************************************************************/

// mutate (generic):

	template<auto Part>
	struct TP_ordered_mutate
	{
		nik_ces auto c = controller
		<
			find   <                     >,
			copy   < _zero   , _constant >,
			stage  <                     >,
			compel < _custom , _h1_pair  >,
			stage  <                     >,
			copy   < _zero   , _register >,
			unite  <           _value    >
		>;

		template<auto d, auto V, auto... Vs, template<auto...> class B>
		nik_ces auto _result(nik_avp(T_store_B<B>*))
		{
			nik_ce auto Pred = U_store_T<B<V>>;
			nik_ce auto H0   = U_pack_Vs<Pred, Vs...>;
			nik_ce auto H1   = U_pack_Vs<Vs...>;
			nik_ce auto H2   = U_pack_Vs<Part>;

			return T_start::template result<d, c, V>(H0, H1, H2);
		}

		template<auto d, auto H, auto V, auto... Vs>
		nik_ces auto result = _result<d, V, Vs...>(H);

	}; template<auto Part>
		nik_ce auto UP_ordered_mutate = U_store_T<TP_ordered_mutate<Part>>;

/***********************************************************************************************************************/

// insert:

	using TP_ordered_insert		= TP_ordered_mutate<UP_split>;
	nik_ce auto UP_ordered_insert	= U_store_T<TP_ordered_insert>;

	using TL_ordered_insert		= TP_unpack<UP_ordered_insert>;
	nik_ce auto UL_ordered_insert	= UP_unpack<UP_ordered_insert>;

	template<auto H, auto V, auto... Vs>
	nik_ce auto pack_ordered_insert = TP_ordered_insert::template result<MD::initial_depth, H, V, Vs...>;

	template<auto p, auto V, auto H = H_curry_less_than, auto d = MD::initial_depth>
	nik_ce auto list_ordered_insert = TL_ordered_insert::template result<d, p, H, V>;

/***********************************************************************************************************************/

// replace:

	using TP_ordered_replace	= TP_ordered_mutate<UP_cut>;
	nik_ce auto UP_ordered_replace	= U_store_T<TP_ordered_replace>;

	using TL_ordered_replace	= TP_unpack<UP_ordered_replace>;
	nik_ce auto UL_ordered_replace	= UP_unpack<UP_ordered_replace>;

	template<auto H, auto V, auto... Vs>
	nik_ce auto pack_ordered_replace = TP_ordered_replace::template result<MD::initial_depth, H, V, Vs...>;

	template<auto p, auto V, auto H = H_curry_less_than, auto d = MD::initial_depth>
	nik_ce auto list_ordered_replace = TL_ordered_replace::template result<d, p, H, V>;

/***********************************************************************************************************************/

// monoid:

	template<auto P, auto H = H_curry_less_than>
	struct TP_ordered_monoid
	{
		template<auto d, auto p, auto V>
		nik_ces auto result = unpack_<p, U_custom, UP_ordered_mutate<P>, d, H, V>;

	}; template<auto P, auto H = H_curry_less_than>
		nik_ce auto UP_ordered_monoid = U_store_T<TP_ordered_monoid<P, H>>;

/***********************************************************************************************************************/

// fold:

	template<auto P>
	struct TP_ordered_fold
	{
		template<auto d, auto H, auto V, auto... Vs>
		nik_ces auto result = TP_cascade::template result<d, UP_ordered_monoid<P, H>, V, Vs...>;

	}; template<auto P>
		nik_ce auto UP_ordered_fold = U_store_T<TP_ordered_fold<P>>;

/***********************************************************************************************************************/

// sort:

	using TP_sort		= TP_ordered_fold<UP_split>;
	nik_ce auto UP_sort	= U_store_T<TP_sort>;

	using TL_sort		= TP_unpack<UP_sort>;
	nik_ce auto UL_sort	= UP_unpack<UP_sort>;

	template<auto H, auto V, auto... Vs>
	nik_ce auto pack_sort = TP_sort::template result<MD::initial_depth, H, V, Vs...>;

	template<auto p, auto H = H_curry_less_than, auto V = U_null_Vs, auto d = MD::initial_depth>
	nik_ce auto list_sort = TL_sort::template result<d, p, H, V>;

/***********************************************************************************************************************/

// write:

	using TP_write		= TP_ordered_fold<UP_cut>;
	nik_ce auto UP_write	= U_store_T<TP_write>;

	using TL_write		= TP_unpack<UP_write>;
	nik_ce auto UL_write	= UP_unpack<UP_write>;

	template<auto H, auto V, auto... Vs>
	nik_ce auto pack_write = TP_write::template result<MD::initial_depth, H, V, Vs...>;

	template<auto p, auto H = H_curry_less_than, auto V = U_null_Vs, auto d = MD::initial_depth>
	nik_ce auto list_write = TL_write::template result<d, p, H, V>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// modify:

/***********************************************************************************************************************/

	struct TP_modify
	{
		nik_ces auto c = controller
		<
			find   <                     >, // j0 <- Pred, Vs...
			copy   < _zero   , _constant >, // H0 <- UP_amend
			stage  <                     >, // H0 <- UP_amend, j0, Vs...
			compel < _custom , _h1_pair  >, // <l, r>, j1
			cut    < _zero   , _register >,
			paste  <           _register >, // A0 <- l, r
			write  < _zero   , _argument >, // H0 <- Op, V
			stage  <                     >, // H0 <- Op, V, j1
			compel < _custom             >, // j2
			write  < _zero   , _register >, // l, r
			stage  <                     >, // l, r, j2

//		 cctmp::debug  <                     >,

			unite  <           _value    >
		>;

		template<auto d, auto Op, auto V, auto... Vs, template<auto...> class B>
		nik_ces auto _result(nik_avp(T_store_B<B>*))
		{
			nik_ce auto Pred = U_store_T<B<V>>;
			nik_ce auto R0   = U_null_Vs;
			nik_ce auto H0   = U_pack_Vs<Pred, Vs...>;
			nik_ce auto H1   = U_pack_Vs<Vs...>;
			nik_ce auto H2   = U_pack_Vs<UP_amend>;
			nik_ce auto A0   = U_pack_Vs<Op, V>;

		//	nik_ce auto ms   = T_start::template result<d, c, R0>(H0, H1, H2, A0);
		//	nik_ce auto cs   = cctmp::tuple_value<0>(ms);
		//	nik_ce auto rs   = cctmp::tuple_value<1>(ms);
		//	nik_ce auto hs   = cctmp::tuple_value<2>(ms);

		//	nik_ce auto h0   = cctmp::tuple_value<0>(hs);
		//	nik_ce auto h1   = cctmp::tuple_value<1>(hs);

		//	nik_ce auto val  = list_at<h1, 0>;

		//	return val;

		//	return T_start::template result<d, c, R0>(H0, H1, H2, A0);

			nik_ce auto p   = T_start::template result<d, c, R0>(H0, H1, H2, A0);
			nik_ce auto b   = alias<AOP::template_id, V>;

			return alias<AOP::list_to_template, p, b>; // it would be better to put it at the ordered_mutate level.
		}

		template<auto d, auto H, auto Op, auto V, auto... Vs>
		nik_ces auto result = _result<d, Op, V, Vs...>(H);

	}; nik_ce auto UP_modify = U_store_T<TP_modify>;

/***********************************************************************************************************************/

// monoid:

	template<auto H, auto Op>
	struct TP_modify_monoid
	{
		template<auto d, auto p, auto V>
		nik_ces auto result = unpack_<p, U_custom, UP_modify, d, H, Op, V>;

	}; template<auto H, auto Op>
		nik_ce auto UP_modify_monoid = U_store_T<TP_modify_monoid<H, Op>>;

/***********************************************************************************************************************/

// fold:

	struct TP_modify_fold
	{
		template<auto d, auto H, auto Op, auto V, auto... Vs>
		nik_ces auto result = TP_cascade::template result<d, UP_modify_monoid<H, Op>, V, Vs...>;

	}; nik_ce auto UP_modify_fold = U_store_T<TP_modify_fold>;

/***********************************************************************************************************************/

// merge:

	using TP_merge		= TP_modify_fold;
	nik_ce auto UP_merge	= U_store_T<TP_merge>;

	using TL_merge		= TP_unpack<UP_merge>;
	nik_ce auto UL_merge	= UP_unpack<UP_merge>;

	template<auto H, auto Op, auto V, auto... Vs>
	nik_ce auto pack_merge = TP_merge::template result<MD::initial_depth, H, Op, V, Vs...>;

	template<auto p, auto H, auto Op, auto V = U_null_Vs, auto d = MD::initial_depth>
	nik_ce auto list_merge = TL_merge::template result<d, p, H, Op, V>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// match:

	// This operator is intended for use within machine tests, with the _h1_pair option.

/***********************************************************************************************************************/

	struct TP_match
	{
		template<auto V, auto... Vs, template<auto...> class B>
		nik_ces auto _result(nik_avp(T_store_B<B>*))
		{
			nik_ce auto Pred = U_store_T<B<V>>;
			nik_ce auto pos  = find_<Pred, Vs...>;
			nik_ce auto size = sizeof...(Vs);

			return tuple<bool, decltype(pos)>(bool{pos < size}, pos);
		}

		template<auto H, auto V, auto... Vs>
		nik_ces auto result = _result<V, Vs...>(H);

	}; nik_ce auto UP_match = U_store_T<TP_match>;

	struct TL_match
	{
		template<auto p, auto H, auto V>
		nik_ces auto result = unpack_<p, U_custom, UP_match, H, V>;

	}; nik_ce auto UL_match = U_store_T<TL_match>;

	template<auto H, auto V, auto... Vs>
	nik_ce auto pack_match = TP_match::template result<H, V, Vs...>;

	template<auto p, auto V, auto H = H_partial_same>
	nik_ce auto list_match = TL_match::template result<p, H, V>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lookup:

/***********************************************************************************************************************/

/*
	struct TP_lookup
	{

	}; nik_ce auto UP_lookup = U_store_T<TP_lookup>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_functional

