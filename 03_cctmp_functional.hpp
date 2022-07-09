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

	nik_ce auto H_partial_same				= cctmp::template H_partial<cctmp::U_same>;

	template<typename T> nik_ce auto U_store_T		= cctmp::template U_store_T<T>;
	template<auto... Vs> nik_ce auto U_pack_Vs		= cctmp::template U_pack_Vs<Vs...>;

	template<auto... Vs> nik_ce auto overload		= cctmp::template overload<Vs...>;

	template<auto... Vs> nik_ce auto U_partial		= cctmp::template U_partial<Vs...>;

	template<auto... Vs> nik_ce auto find_			= cctmp::template find_<Vs...>;
	template<auto... Vs> nik_ce auto unpack_		= cctmp::template unpack_<Vs...>;

	template<auto... Vs> nik_ce auto find			= cctmp::template find<Vs...>;
	template<auto... Vs> nik_ce auto compel			= cctmp::template compel<Vs...>;
	template<auto... Vs> nik_ce auto custom			= cctmp::template custom<Vs...>;
	template<auto... Vs> nik_ce auto unite			= cctmp::template unite<Vs...>;
	template<auto... Vs> nik_ce auto action			= cctmp::template action<Vs...>;
	template<auto... Vs> nik_ce auto copy			= cctmp::template copy<Vs...>;
	template<auto... Vs> nik_ce auto write			= cctmp::template write<Vs...>;
	template<auto... Vs> nik_ce auto branch			= cctmp::template branch<Vs...>;
	template<auto... Vs> nik_ce auto value			= cctmp::template value<Vs...>;
	template<auto...> nik_ce auto stage			= cctmp::template stage<>;

	template<auto... Vs> nik_ce auto controller		= cctmp::template controller<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// block:

/***********************************************************************************************************************/

// at:

	struct T_at
	{
		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_block_variable::template result<d, n, U_car, Vs...>;

	}; nik_ce auto U_at = U_store_T<T_at>;

	template<auto n, auto... Vs>
	nik_ce auto pack_at = T_at::template result<MD::initial_depth, n, Vs...>;

	template<auto p, auto n, auto d = MD::initial_depth>
	nik_ce auto list_at = unpack_<p, U_custom, U_at, d, n>;

// left:

	struct T_left
	{
		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_block_function::template result<d, U_null_Vs, n, U_block_left, Vs...>;

	}; nik_ce auto U_left = U_store_T<T_left>;

	template<auto n, auto... Vs>
	nik_ce auto pack_left = T_left::template result<MD::initial_depth, n, Vs...>;

	template<auto p, auto n, auto d = MD::initial_depth>
	nik_ce auto list_left = unpack_<p, U_custom, U_left, d, n>;

// right:

	struct T_right
	{
		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_block_variable::template result<d, n, U_to_list, Vs...>;

	}; nik_ce auto U_right = U_store_T<T_right>;

	template<auto n, auto... Vs>
	nik_ce auto pack_right = T_right::template result<MD::initial_depth, n, Vs...>;

	template<auto p, auto n, auto d = MD::initial_depth>
	nik_ce auto list_right = unpack_<p, U_custom, U_right, d, n>;

// split:

	struct T_split
	{
		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_block_function::template result<d, U_null_Vs, n, U_block_split, Vs...>;

	}; nik_ce auto U_split = U_store_T<T_split>;

	template<auto n, auto... Vs>
	nik_ce auto pack_split = T_split::template result<MD::initial_depth, n, Vs...>;

	template<auto p, auto n, auto d = MD::initial_depth>
	nik_ce auto list_split = unpack_<p, U_custom, U_split, d, n>;

// cut:

	struct T_cut
	{
		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_block_function::template result<d, U_null_Vs, n, U_block_filter, Vs...>;

	}; nik_ce auto U_cut = U_store_T<T_cut>;

	template<auto n, auto... Vs>
	nik_ce auto pack_cut = T_cut::template result<MD::initial_depth, n, Vs...>;

	template<auto p, auto n, auto d = MD::initial_depth>
	nik_ce auto list_cut = unpack_<p, U_custom, U_cut, d, n>;

// segment:

	using T_segment		= T_block_segment;
	nik_ce auto U_segment	= U_store_T<T_segment>;

	template<auto n, auto s = index_type{0}>
	nik_ce auto segment = T_segment::template result<MD::initial_depth, n, s>;

// fold:

	struct T_fold
	{
		template<auto d, auto op, auto V, auto... Vs>
		nik_ces auto result = T_block_fold::template result<d, sizeof...(Vs), op, V, Vs...>;

	}; nik_ce auto U_fold = U_store_T<T_fold>;

	template<auto op, auto V, auto... Vs>
	nik_ce auto pack_fold = T_fold::template result<MD::initial_depth, op, V, Vs...>;

	template<auto p, auto op, auto V, auto d = MD::initial_depth>
	nik_ce auto list_fold = unpack_<p, U_custom, U_fold, d, op, V>;

// parse (fold with one lookahead):

	struct T_parse
	{
		template<auto d, auto op, auto V, auto... Vs>
		nik_ces auto result = T_block_parse::template result<d, sizeof...(Vs)-1, op, V, Vs...>;

	}; nik_ce auto U_parse = U_store_T<T_parse>;

	template<auto op, auto V, auto... Vs>
	nik_ce auto pack_parse = T_parse::template result<MD::initial_depth, op, V, Vs...>;

	template<auto p, auto op, auto V, auto d = MD::initial_depth>
	nik_ce auto list_parse = unpack_<p, U_custom, U_parse, d, op, V>;

// cascade:

	struct T_cascade
	{
		template<auto d, auto op, auto V, auto... Vs>
		nik_ces auto result = T_block_cascade::template result<d, sizeof...(Vs), op, V, Vs...>;

	}; nik_ce auto U_cascade = U_store_T<T_cascade>;

	template<auto op, auto V, auto... Vs>
	nik_ce auto pack_cascade = T_cascade::template result<MD::initial_depth, op, V, Vs...>;

	template<auto p, auto op, auto V, auto d = MD::initial_depth>
	nik_ce auto list_cascade = unpack_<p, U_custom, U_cascade, d, op, V>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// mutators:

/***********************************************************************************************************************/

// erase:

	struct T_erase
	{
		nik_ces auto c = controller
		<
			compel < _custom , _h1_pair >,
			stage  <                    >,
			unite  <             _value >
		>;

		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_start::template result<d, c>(U_pack_Vs<U_cut, n, Vs...>, U_null_Vs, U_null_Vs);

	}; nik_ce auto U_erase = U_store_T<T_erase>;

	template<auto n, auto... Vs>
	nik_ce auto pack_erase = T_erase::template result<MD::initial_depth, n, Vs...>;

	template<auto p, auto n, auto d = MD::initial_depth>
	nik_ce auto list_erase = unpack_<p, U_custom, U_erase, d, n>;

// mutate (generic):

	template<auto Part>
	struct T_mutate
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

	using T_insert		= T_mutate<U_split>;
	nik_ce auto U_insert	= U_store_T<T_insert>;

	template<auto n, auto V, auto... Vs>
	nik_ce auto pack_insert = T_insert::template result<MD::initial_depth, n, V, Vs...>;

	template<auto p, auto n, auto V, auto d = MD::initial_depth>
	nik_ce auto list_insert = unpack_<p, U_custom, U_insert, d, n, V>;

// replace:

	using T_replace		= T_mutate<U_cut>;
	nik_ce auto U_replace	= U_store_T<T_replace>;

	template<auto n, auto V, auto... Vs>
	nik_ce auto pack_replace = T_replace::template result<MD::initial_depth, n, V, Vs...>;

	template<auto p, auto n, auto V, auto d = MD::initial_depth>
	nik_ce auto list_replace = unpack_<p, U_custom, U_replace, d, n, V>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ordered:

/***********************************************************************************************************************/

// mutate (generic):

	template<auto Part>
	struct T_ordered_mutate
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
		nik_ce auto U_ordered_mutate = U_store_T<T_ordered_mutate<Part>>;

/***********************************************************************************************************************/

// insert:

	using T_ordered_insert		= T_ordered_mutate<U_split>;
	nik_ce auto U_ordered_insert	= U_store_T<T_ordered_insert>;

	template<auto H, auto V, auto... Vs>
	nik_ce auto pack_ordered_insert = T_ordered_insert::template result<MD::initial_depth, H, V, Vs...>;

	template<auto p, auto V, auto H = H_curry_less_than, auto d = MD::initial_depth>
	nik_ce auto list_ordered_insert = unpack_<p, U_custom, U_ordered_insert, d, H, V>;

/***********************************************************************************************************************/

// replace:

	using T_ordered_replace		= T_ordered_mutate<U_cut>;
	nik_ce auto U_ordered_replace	= U_store_T<T_ordered_replace>;

	template<auto H, auto V, auto... Vs>
	nik_ce auto pack_ordered_replace = T_ordered_replace::template result<MD::initial_depth, H, V, Vs...>;

	template<auto p, auto V, auto H = H_curry_less_than, auto d = MD::initial_depth>
	nik_ce auto list_ordered_replace = unpack_<p, U_custom, U_ordered_replace, d, H, V>;

/***********************************************************************************************************************/

// monoid:

	template<auto P, auto H = H_curry_less_than>
	struct T_ordered_monoid
	{
		template<auto d, auto p, auto V>
		nik_ces auto result = unpack_<p, U_custom, U_ordered_mutate<P>, d, H, V>;

	}; template<auto P, auto H = H_curry_less_than>
		nik_ce auto U_ordered_monoid = U_store_T<T_ordered_monoid<P, H>>;

/***********************************************************************************************************************/

// fold:

	template<auto P>
	struct T_ordered_fold
	{
		template<auto d, auto H, auto V, auto... Vs>
		nik_ces auto result = T_cascade::template result<d, U_ordered_monoid<P, H>, V, Vs...>;

	}; template<auto P>
		nik_ce auto U_ordered_fold = U_store_T<T_ordered_fold<P>>;

/***********************************************************************************************************************/

// sort:

	using T_sort		= T_ordered_fold<U_split>;
	nik_ce auto U_sort	= U_store_T<T_sort>;

	template<auto H, auto V, auto... Vs>
	nik_ce auto pack_sort = T_sort::template result<MD::initial_depth, H, V, Vs...>;

	template<auto p, auto H = H_curry_less_than, auto V = U_null_Vs, auto d = MD::initial_depth>
	nik_ce auto list_sort = unpack_<p, U_custom, U_sort, d, H, V>;

/***********************************************************************************************************************/

// write:

	using T_write		= T_ordered_fold<U_cut>;
	nik_ce auto U_write	= U_store_T<T_write>;

	template<auto H, auto V, auto... Vs>
	nik_ce auto pack_write = T_write::template result<MD::initial_depth, H, V, Vs...>;

	template<auto p, auto H = H_curry_less_than, auto V = U_null_Vs, auto d = MD::initial_depth>
	nik_ce auto list_write = unpack_<p, U_custom, U_write, d, H, V>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// match:

	// This operator is intended for use within machine tests, with the _h1_pair option.

/***********************************************************************************************************************/

	struct T_match
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

	}; nik_ce auto U_match = U_store_T<T_match>;

	template<auto H, auto V, auto... Vs>
	nik_ce auto pack_match = T_match::template result<H, V, Vs...>;

	template<auto p, auto H = H_partial_same>
	nik_ce auto list_match = unpack_<p, U_custom, U_match, H>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lookup:

/***********************************************************************************************************************/

/*
	struct T_lookup
	{

	}; nik_ce auto U_lookup = U_store_T<T_lookup>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// united:

	// Not currently needed, keeping for possible later use.

/***********************************************************************************************************************/

// insert:

/*
	struct T_united_insert
	{
		nik_ces key_type exit_case = 4;

		nik_ces auto c = controller
		<
			custom < _h1_pair            >,
			branch <           exit_case >,
			write  < _zero   , _argument >,
			compel < _custom , _value    >,

			// exit_case:

			value  < _zero   , _register >
		>;

		template<auto d, auto HEq, auto HCmp, auto V, auto... Vs>
		nik_ces auto _result()
		{
			nik_ce auto R0 = U_pack_Vs<Vs...>;
			nik_ce auto H0 = U_pack_Vs<U_match, HEq, V, Vs...>;
			nik_ce auto H1 = U_null_Vs;
			nik_ce auto H2 = U_null_Vs;
			nik_ce auto A0 = U_pack_Vs<U_ordered_insert, HCmp, V, Vs...>;

			return T_start::template result<d, c, R0>(H0, H1, H2, A0);
		}

		template<auto d, auto HEq, auto HCmp, auto V, auto... Vs>
		nik_ces auto result = _result<d, HEq, HCmp, V, Vs...>();

	}; nik_ce auto U_united_insert = U_store_T<T_united_insert>;

	template<auto HEq, auto HCmp, auto V, auto... Vs>
	nik_ce auto pack_united_insert = T_united_insert::template result<MD::initial_depth, HEq, HCmp, V, Vs...>;

	template<auto p, auto V, auto HEq = H_curry_equal, auto HCmp = H_curry_less_than, auto d = MD::initial_depth>
	nik_ce auto list_united_insert = unpack_<p, U_custom, U_united_insert, d, HEq, HCmp, V>;
*/

/***********************************************************************************************************************/

// monoid:

/*
	template<auto HEq = H_curry_equal, auto HCmp = H_curry_less_than>
	struct T_united_monoid
	{
		template<auto d, auto p, auto V>
		nik_ces auto result = unpack_<p, U_custom, U_united_insert, d, HEq, HCmp, V>;

	}; template<auto HEq = H_curry_equal, auto HCmp = H_curry_less_than>
		nik_ce auto U_united_monoid = U_store_T<T_united_monoid<HEq, HCmp>>;
*/

/***********************************************************************************************************************/

// (fold) union:

/*
	struct T_united_fold
	{
		template<auto d, auto HEq, auto HCmp, auto V, auto... Vs>
		nik_ces auto result = T_cascade::template result<d, U_united_monoid<HEq, HCmp>, V, Vs...>;

	}; nik_ce auto U_united_fold = U_store_T<T_united_fold>;

	template<auto HEq, auto HCmp, auto V, auto... Vs>
	nik_ce auto pack_united_fold = T_united_fold::template result<MD::initial_depth, HEq, HCmp, V, Vs...>;

	template
	<
		auto p,
		auto HEq = H_curry_equal, auto HCmp = H_curry_less_than,
		auto V = U_null_Vs, auto d = MD::initial_depth
	>
	nik_ce auto list_united_fold = unpack_<p, U_custom, U_united_fold, d, HEq, HCmp, V>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// compare:

	// Not currently needed, keeping for possible later use.
	// Doesn't scale performantly for frequent comparisons.

/***********************************************************************************************************************/

/*
	struct T_compare
	{
		template<auto key, auto act>
		nik_ces auto c = controller
		<
			find   <                         >,
			write  < _zero ,       _argument >,
			find   <                         >,
			stage  <                         >,
			action < key   , act , _value    >
		>;

		template<auto d, auto V0, auto V1, auto... Vs, auto key, auto act, template<auto...> class B>
		nik_ces auto _result(nik_avp(T_overload<key, act>*), nik_avp(T_store_B<B>*))
		{
			nik_ce auto Pred0 = U_store_T<B<V0>>;
			nik_ce auto Pred1 = U_store_T<B<V1>>;

			nik_ce auto H0    = U_pack_Vs<Pred1, Vs...>;
			nik_ce auto H1    = U_null_Vs;
			nik_ce auto H2    = U_null_Vs;
			nik_ce auto A0    = U_pack_Vs<Pred0, Vs...>;

			return T_start::template result<d, c<key, act>>(H0, H1, H2, A0);
		}

		template<auto d, auto Op, auto H, auto V0, auto V1, auto... Vs>
		nik_ces auto result = _result<d, V0, V1, Vs...>(Op, H);

	}; nik_ce auto U_compare = U_store_T<T_compare>;

	template<auto Op, auto H, auto V0, auto V1, auto... Vs>
	nik_ce auto pack_compare = T_compare::template result<MD::initial_depth, Op, H, V0, V1, Vs...>;

	template<auto p, auto Op, auto V0, auto V1, auto H = H_partial_same, auto d = MD::initial_depth>
	nik_ce auto list_compare = unpack_<p, U_custom, U_compare, d, Op, H, V0, V1>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_functional

