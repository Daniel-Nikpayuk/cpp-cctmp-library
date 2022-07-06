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

	template<auto... Vs> using T_store_Vs			= typename cctmp::template T_store_Vs<Vs...>;
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

	nik_ce auto _less_than_					= cctmp::_less_than_;

	nik_ce auto U_same					= cctmp::U_same;
	nik_ce auto U_to_list					= cctmp::U_to_list;
	nik_ce auto U_length					= cctmp::U_length;
	nik_ce auto U_car					= cctmp::U_car;
	nik_ce auto U_find					= cctmp::U_find;
	nik_ce auto U_custom					= cctmp::U_custom;
	nik_ce auto U_tailor					= cctmp::U_tailor;

	nik_ce auto U_block_filter				= cctmp::U_block_filter;
	nik_ce auto U_block_split				= cctmp::U_block_split;
	nik_ce auto U_block_left				= cctmp::U_block_left;

	template<typename T> nik_ce auto U_store_T		= cctmp::template U_store_T<T>;
	template<auto... Vs> nik_ce auto U_pack_Vs		= cctmp::template U_pack_Vs<Vs...>;

	template<auto... Vs> nik_ce auto overload		= cctmp::template overload<Vs...>;

	template<auto... Vs> nik_ce auto _curry_		= cctmp::template _curry_<Vs...>;

	template<auto... Vs> nik_ce auto U_partial		= cctmp::template U_partial<Vs...>;

	template<auto... Vs> nik_ce auto find_			= cctmp::template find_<Vs...>;
	template<auto... Vs> nik_ce auto unpack_		= cctmp::template unpack_<Vs...>;

	template<auto... Vs> nik_ce auto find			= cctmp::template find<Vs...>;
	template<auto... Vs> nik_ce auto compel			= cctmp::template compel<Vs...>;
	template<auto... Vs> nik_ce auto unite			= cctmp::template unite<Vs...>;
	template<auto... Vs> nik_ce auto unpack			= cctmp::template unpack<Vs...>;
	template<auto... Vs> nik_ce auto copy			= cctmp::template copy<Vs...>;
	template<auto... Vs> nik_ce auto write			= cctmp::template write<Vs...>;
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

// insert:

	struct T_insert
	{
		nik_ces auto c = controller
		<
			compel < _custom , _h1_pair  >,
			stage  <                     >,
			copy   < _zero   , _register >,
			unite  <             _value  >
		>;

		template<auto d, auto n, auto V, auto... Vs>
		nik_ces auto result = T_start::template result<d, c, V>(U_pack_Vs<U_split, n, Vs...>, U_null_Vs, U_null_Vs);

	}; nik_ce auto U_insert = U_store_T<T_insert>;

	template<auto n, auto V, auto... Vs>
	nik_ce auto pack_insert = T_insert::template result<MD::initial_depth, n, V, Vs...>;

	template<auto p, auto n, auto V, auto d = MD::initial_depth>
	nik_ce auto list_insert = unpack_<p, U_custom, U_insert, d, n, V>;

// replace:

	struct T_replace
	{
		nik_ces auto c = controller
		<
			compel < _custom , _h1_pair  >,
			stage  <                     >,
			copy   < _zero   , _register >,
			unite  <             _value  >
		>;

		template<auto d, auto n, auto V, auto... Vs>
		nik_ces auto result = T_start::template result<d, c, V>(U_pack_Vs<U_cut, n, Vs...>, U_null_Vs, U_null_Vs);

	}; nik_ce auto U_replace = U_store_T<T_replace>;

	template<auto n, auto V, auto... Vs>
	nik_ce auto pack_replace = T_replace::template result<MD::initial_depth, n, V, Vs...>;

	template<auto p, auto n, auto V, auto d = MD::initial_depth>
	nik_ce auto list_replace = unpack_<p, U_custom, U_replace, d, n, V>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sort:

/***********************************************************************************************************************/

// insert:

	struct T_insert_sort
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

		template<auto d, auto cmp, auto V, auto... Vs>
		nik_ces auto result = T_start::template result<d, c, V>
		(
			U_pack_Vs < _curry_<cmp, V>, Vs... >,
			U_pack_Vs < Vs...                  >,
			U_pack_Vs < U_split                >
		);

	}; nik_ce auto U_insert_sort = U_store_T<T_insert_sort>;

	template<auto cmp, auto V, auto... Vs>
	nik_ce auto pack_insert_sort = T_insert_sort::template result<MD::initial_depth, cmp, V, Vs...>;

	template<auto p, auto V, auto cmp = _less_than_, auto d = MD::initial_depth>
	nik_ce auto list_insert_sort = unpack_<p, U_custom, U_insert_sort, d, cmp, V>;

/***********************************************************************************************************************/

// monoid:

	template<auto cmp = _less_than_>
	struct T_monoid_sort
	{
		template<auto d, auto p, auto V>
		nik_ces auto result = unpack_<p, U_custom, U_insert_sort, d, cmp, V>;

	}; template<auto cmp = _less_than_>
		nik_ce auto U_monoid_sort = U_store_T<T_monoid_sort<cmp>>;

/***********************************************************************************************************************/

// (fold) sort:

	struct T_sort
	{
		template<auto d, auto cmp, auto... Vs>
		nik_ces auto result = T_cascade::template result<d, U_monoid_sort<cmp>, U_null_Vs, Vs...>;

	}; nik_ce auto U_sort = U_store_T<T_sort>;

	template<auto cmp, auto... Vs>
	nik_ce auto pack_sort = T_sort::template result<MD::initial_depth, cmp, Vs...>;

	template<auto p, auto cmp = _less_than_, auto d = MD::initial_depth>
	nik_ce auto list_sort = unpack_<p, U_custom, U_sort, d, cmp>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lookup:

/***********************************************************************************************************************/

// match:

	struct T_lookup
	{
		template<auto V, auto... Vs>
		nik_ces auto match()
		{
			nik_ce auto pos  = find_<U_partial<U_same, V>, Vs...>;
			nik_ce auto size = sizeof...(Vs);

			return tuple<bool, decltype(pos)>(bool{pos < size}, pos);
		}

		template<auto V, auto... Vs>
		nik_ces auto result = match<V, Vs...>();

	}; nik_ce auto U_lookup = U_store_T<T_lookup>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_functional

