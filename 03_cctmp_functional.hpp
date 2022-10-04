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

	template<typename T> nik_ce auto U_store_T		= cctmp::template U_store_T<T>;
	template<auto... Vs> nik_ce auto U_pack_Vs		= cctmp::template U_pack_Vs<Vs...>;

	using index_type					= typename cctmp::index_type;

	nik_ce auto _zero					= cctmp::_zero;
	nik_ce auto _one					= cctmp::_one;
	nik_ce auto _two					= cctmp::_two;

	template<auto... Vs> nik_ce auto overload		= cctmp::template overload<Vs...>;
	template<auto... Vs> nik_ce auto U_alias		= cctmp::template U_alias<Vs...>;

	nik_ce auto U_null_Vs					= cctmp::U_null_Vs;
	nik_ce auto H_id					= cctmp::H_id;

	nik_ce auto _less_than_					= cctmp::_less_than_;

	nik_ce auto _if_then_else_				= cctmp::_if_then_else_;
	nik_ce auto _same_					= cctmp::_same_;
	nik_ce auto _to_tuple_					= cctmp::_to_tuple_;
	nik_ce auto _unite_					= cctmp::_unite_;

	nik_ce auto U_block_car					= cctmp::U_block_car;

	template<auto... Vs> nik_ce auto U_block_left		= cctmp::template U_block_left<Vs...>;
	template<auto... Vs> nik_ce auto U_block_right		= cctmp::template U_block_right<Vs...>;
	template<auto... Vs> nik_ce auto U_block_split		= cctmp::template U_block_split<Vs...>;
	template<auto... Vs> nik_ce auto U_block_cut		= cctmp::template U_block_cut<Vs...>;
	template<auto... Vs> nik_ce auto U_block_alter		= cctmp::template U_block_alter<Vs...>;

	using T_block_variable					= typename cctmp::T_block_variable;
	using T_block_function					= typename cctmp::T_block_function;
	using T_block_segment					= typename cctmp::T_block_segment;
	using T_block_sifter					= typename cctmp::T_block_sifter;
	using T_block_fold					= typename cctmp::T_block_fold;
	using T_block_parse					= typename cctmp::T_block_parse;
	using T_block_cascade					= typename cctmp::T_block_cascade;
	using T_start						= typename cctmp::T_start;

	template<auto... Vs> nik_ce auto unpack_		= cctmp::template unpack_<Vs...>;
	template<auto... Vs> nik_ce auto find_			= cctmp::template find_<Vs...>;

	using MD						= typename cctmp::MD;

	nik_ce auto _h1_pair					= cctmp::_h1_pair;
	nik_ce auto _register					= cctmp::_register;
	nik_ce auto _argument					= cctmp::_argument;
	nik_ce auto _constant					= cctmp::_constant;
	nik_ce auto _value					= cctmp::_value;

	nik_ce auto _all					= cctmp::_all;

	nik_ce auto _nested					= cctmp::_nested;

	template<auto... Vs> nik_ce auto find			= cctmp::template find<Vs...>;
	template<auto... Vs> nik_ce auto f2_unpack		= cctmp::template f2_unpack<Vs...>;
	template<auto... Vs> nik_ce auto unite			= cctmp::template unite<Vs...>;

	template<auto... Vs> nik_ce auto compel			= cctmp::template compel<Vs...>;

	template<auto... Vs> nik_ce auto copy			= cctmp::template copy<Vs...>;
	template<auto... Vs> nik_ce auto write			= cctmp::template write<Vs...>;
	template<auto... Vs> nik_ce auto cut			= cctmp::template cut<Vs...>;
	template<auto... Vs> nik_ce auto paste			= cctmp::template paste<Vs...>;
	template<auto... Vs> nik_ce auto stage			= cctmp::template stage<Vs...>;

	template<auto... Vs> nik_ce auto controller		= cctmp::template controller<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// block:

	template<auto Op>
	struct TP_unpack
	{
		template<auto d, auto p, auto... Vs>
		nik_ces auto result = unpack_<p, Op, d, Vs...>;

	}; template<auto Op>
		nik_ce auto UP_unpack = U_store_T<TP_unpack<Op>>;

/***********************************************************************************************************************/

// at:

	struct TP_at
	{
		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_block_variable::template result<d, n, U_block_car, Vs...>;

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
		template<auto d, auto n, auto b, auto... Vs>
		nik_ces auto result = T_block_function::template result<d, U_null_Vs, n, U_block_left<b>, Vs...>;

	}; nik_ce auto UP_left = U_store_T<TP_left>;

	using TL_left		= TP_unpack<UP_left>;
	nik_ce auto UL_left	= UP_unpack<UP_left>;

	template<auto n, auto... Vs>
	nik_ce auto pack_left = TP_left::template result<MD::initial_depth, n, H_id, Vs...>;

	template<auto p, auto n, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_left = TL_left::template result<d, p, n, b>;

// right:

	struct TP_right
	{
		template<auto d, auto n, auto b, auto... Vs>
		nik_ces auto result = T_block_variable::template result<d, n, U_block_right<b>, Vs...>;

	}; nik_ce auto UP_right = U_store_T<TP_right>;

	using TL_right		= TP_unpack<UP_right>;
	nik_ce auto UL_right	= UP_unpack<UP_right>;

	template<auto n, auto... Vs>
	nik_ce auto pack_right = TP_right::template result<MD::initial_depth, n, H_id, Vs...>;

	template<auto p, auto n, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_right = TL_right::template result<d, p, n, b>;

// split:

	struct TP_split
	{
		template<auto d, auto n, auto bl, auto br, auto... Vs>
		nik_ces auto result = T_block_function::template result<d, U_null_Vs, n, U_block_split<bl, br>, Vs...>;

	}; nik_ce auto UP_split = U_store_T<TP_split>;

	using TL_split		= TP_unpack<UP_split>;
	nik_ce auto UL_split	= UP_unpack<UP_split>;

	template<auto n, auto... Vs>
	nik_ce auto pack_split = TP_split::template result<MD::initial_depth, n, H_id, H_id, Vs...>;

	template<auto p, auto n, auto bl = H_id, auto br = H_id, auto d = MD::initial_depth>
	nik_ce auto list_split = TL_split::template result<d, p, n, bl, br>;

// cut:

	struct TP_cut
	{
		template<auto d, auto n, auto bl, auto br, auto... Vs>
		nik_ces auto result = T_block_function::template result<d, U_null_Vs, n, U_block_cut<bl, br>, Vs...>;

	}; nik_ce auto UP_cut = U_store_T<TP_cut>;

	using TL_cut		= TP_unpack<UP_cut>;
	nik_ce auto UL_cut	= UP_unpack<UP_cut>;

	template<auto n, auto... Vs>
	nik_ce auto pack_cut = TP_cut::template result<MD::initial_depth, n, H_id, H_id, Vs...>;

	template<auto p, auto n, auto bl = H_id, auto br = H_id, auto d = MD::initial_depth>
	nik_ce auto list_cut = TL_cut::template result<d, p, n, bl, br>;

// alter:

	struct TP_alter
	{
		template<auto d, auto n, auto bl, auto br, auto bp, auto... Vs>
		nik_ces auto result = T_block_function::template result<d, U_null_Vs, n, U_block_alter<bl, br, bp>, Vs...>;

	}; nik_ce auto UP_alter = U_store_T<TP_alter>;

	using TL_alter		= TP_unpack<UP_alter>;
	nik_ce auto UL_alter	= UP_unpack<UP_alter>;

	template<auto n, auto... Vs>
	nik_ce auto pack_alter = TP_alter::template result<MD::initial_depth, n, H_id, H_id, H_id, Vs...>;

	template<auto p, auto n, auto bl = H_id, auto br = H_id, auto bp = H_id, auto d = MD::initial_depth>
	nik_ce auto list_alter = TL_alter::template result<d, p, n, bl, br, bp>;

// segment:

	using T_segment		= T_block_segment;
	nik_ce auto U_segment	= U_store_T<T_segment>;

	template<auto n, auto s = index_type{0}, auto b = H_id>
	nik_ce auto segment = T_segment::template result<MD::initial_depth, n, b, s>;

// sifter:

	struct TP_sifter
	{
		template<auto d, auto b, auto op, auto... Vs>
		nik_ces auto result = T_block_sifter::template _result<d, sizeof...(Vs), b, Vs...>
		(
			overload
			<
				_if_then_else_,
				overload<op, Vs>,
				U_pack_Vs<U_null_Vs>,
				U_null_Vs
			>...
		);

	}; nik_ce auto UP_sifter = U_store_T<TP_sifter>;

	using TL_sifter		= TP_unpack<UP_sifter>;
	nik_ce auto UL_sifter	= UP_unpack<UP_sifter>;

	template<auto op, auto... Vs>
	nik_ce auto pack_sifter = TP_sifter::template result<MD::initial_depth, H_id, op, Vs...>;

	template<auto p, auto op, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_sifter = TL_sifter::template result<d, p, b, op>;

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
			compel < _nested , _h1_pair  >,
			copy   < _zero   , _constant >,
			stage  <           _all      >,
			unite  <           _value    >
		>;

		template<auto d, auto n, auto b, auto... Vs>
		nik_ces auto result = T_start::template result<d, c>
		(
			U_pack_Vs<UP_cut, n, H_id, H_id, Vs...>,
			U_null_Vs,
			U_pack_Vs<b>
		);

	}; nik_ce auto UP_erase = U_store_T<TP_erase>;

	using TL_erase		= TP_unpack<UP_erase>;
	nik_ce auto UL_erase	= UP_unpack<UP_erase>;

	template<auto n, auto... Vs>
	nik_ce auto pack_erase = TP_erase::template result<MD::initial_depth, n, H_id, Vs...>;

	template<auto p, auto n, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_erase = TL_erase::template result<d, p, n, b>;

// mutate (generic):

	template<auto Part>
	struct TP_mutate
	{
		nik_ces auto c = controller
		<
			compel < _nested , _h1_pair  >,
			copy   < _zero   , _constant >,
			stage  <           _all      >,
			copy   < _zero   , _register >,
			unite  <           _value    >
		>;

		template<auto d, auto n, auto b, auto V, auto... Vs>
		nik_ces auto result = T_start::template result<d, c, V>
		(
			U_pack_Vs<Part, n, H_id, H_id, Vs...>,
			U_null_Vs,
			U_pack_Vs<b>
		);
	};

// insert:

	using TP_insert		= TP_mutate<UP_split>;
	nik_ce auto UP_insert	= U_store_T<TP_insert>;

	using TL_insert		= TP_unpack<UP_insert>;
	nik_ce auto UL_insert	= UP_unpack<UP_insert>;

	template<auto n, auto V, auto... Vs>
	nik_ce auto pack_insert = TP_insert::template result<MD::initial_depth, n, H_id, V, Vs...>;

	template<auto p, auto n, auto V, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_insert = TL_insert::template result<d, p, n, b, V>;

// replace:

	using TP_replace	= TP_mutate<UP_cut>;
	nik_ce auto UP_replace	= U_store_T<TP_replace>;

	using TL_replace	= TP_unpack<UP_replace>;
	nik_ce auto UL_replace	= UP_unpack<UP_replace>;

	template<auto n, auto V, auto... Vs>
	nik_ce auto pack_replace = TP_replace::template result<MD::initial_depth, n, H_id, V, Vs...>;

	template<auto p, auto n, auto V, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_replace = TL_replace::template result<d, p, n, b, V>;

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
			stage  <           _all      >,
			compel < _nested , _h1_pair  >,
			copy   < _one    , _constant >,
			stage  <           _all      >,
			copy   < _zero   , _register >,
			unite  <           _value    >
		>;

		template<auto d, auto b, auto Pred, auto V, auto... Vs>
		nik_ces auto result = T_start::template result<d, c, V>
		(
			U_pack_Vs<U_alias<Pred, V>, Vs...>,
			U_pack_Vs<H_id, H_id, Vs...>,
			U_pack_Vs<Part, b>
		);

	}; template<auto Part>
		nik_ce auto UP_ordered_mutate = U_store_T<TP_ordered_mutate<Part>>;

/***********************************************************************************************************************/

// insert:

	using TP_ordered_insert		= TP_ordered_mutate<UP_split>;
	nik_ce auto UP_ordered_insert	= U_store_T<TP_ordered_insert>;

	using TL_ordered_insert		= TP_unpack<UP_ordered_insert>;
	nik_ce auto UL_ordered_insert	= UP_unpack<UP_ordered_insert>;

	template<auto Pred, auto V, auto... Vs>
	nik_ce auto pack_ordered_insert = TP_ordered_insert::template result<MD::initial_depth, H_id, Pred, V, Vs...>;

	template<auto p, auto V, auto Pred = _less_than_, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_ordered_insert = TL_ordered_insert::template result<d, p, b, Pred, V>;

/***********************************************************************************************************************/

// replace:

	using TP_ordered_replace	= TP_ordered_mutate<UP_cut>;
	nik_ce auto UP_ordered_replace	= U_store_T<TP_ordered_replace>;

	using TL_ordered_replace	= TP_unpack<UP_ordered_replace>;
	nik_ce auto UL_ordered_replace	= UP_unpack<UP_ordered_replace>;

	template<auto Pred, auto V, auto... Vs>
	nik_ce auto pack_ordered_replace = TP_ordered_replace::template result<MD::initial_depth, H_id, Pred, V, Vs...>;

	template<auto p, auto V, auto Pred = _less_than_, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_ordered_replace = TL_ordered_replace::template result<d, p, b, Pred, V>;

/***********************************************************************************************************************/

// monoid:

	template<auto Part, auto Pred = _less_than_, auto b = H_id>
	struct TP_ordered_monoid
	{
		template<auto d, auto p, auto V>
		nik_ces auto result = unpack_<p, UP_ordered_mutate<Part>, d, b, Pred, V>;

	}; template<auto Part, auto Pred = _less_than_, auto b = H_id>
		nik_ce auto UP_ordered_monoid = U_store_T<TP_ordered_monoid<Part, Pred, b>>;

/***********************************************************************************************************************/

// fold:

	template<auto Part>
	struct TP_ordered_fold
	{
		template<auto d, auto b, auto Pred, auto V, auto... Vs>
		nik_ces auto result = TP_cascade::template result<d, UP_ordered_monoid<Part, Pred, b>, V, Vs...>;

	}; template<auto Part>
		nik_ce auto UP_ordered_fold = U_store_T<TP_ordered_fold<Part>>;

/***********************************************************************************************************************/

// sort:

	using TP_sort		= TP_ordered_fold<UP_split>;
	nik_ce auto UP_sort	= U_store_T<TP_sort>;

	using TL_sort		= TP_unpack<UP_sort>;
	nik_ce auto UL_sort	= UP_unpack<UP_sort>;

	template<auto Pred, auto V, auto... Vs>
	nik_ce auto pack_sort = TP_sort::template result<MD::initial_depth, H_id, Pred, V, Vs...>;

	template<auto p, auto Pred = _less_than_, auto V = U_null_Vs, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_sort = TL_sort::template result<d, p, b, Pred, V>;

/***********************************************************************************************************************/

// write:

	using TP_write		= TP_ordered_fold<UP_cut>;
	nik_ce auto UP_write	= U_store_T<TP_write>;

	using TL_write		= TP_unpack<UP_write>;
	nik_ce auto UL_write	= UP_unpack<UP_write>;

	template<auto Pred, auto V, auto... Vs>
	nik_ce auto pack_write = TP_write::template result<MD::initial_depth, H_id, Pred, V, Vs...>;

	template<auto p, auto Pred = _less_than_, auto V = U_null_Vs, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_write = TL_write::template result<d, p, b, Pred, V>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// modify:

/***********************************************************************************************************************/

	struct TP_modify
	{
		nik_ces auto c = controller
		<
			find      <                     >,
			copy      < _zero   , _constant >,
			stage     <           _all      >,
			compel    < _nested , _h1_pair  >,
			stage     <                     >,
			paste     <           _register >,
			write     < _zero   , _argument >,
			stage     <                     >,
			compel    < _nested             >,
			copy      < _zero   , _register >,
			copy      < _one    , _constant >,
			copy      < _two    , _constant >,
			stage     <                     >,
			f2_unpack <           _value    >
		>;

		template<auto d, auto b, auto Pred, auto Op, auto V, auto... Vs>
		nik_ces auto result = T_start::template result<d, c>
		(
		 	U_pack_Vs<U_alias<Pred, V>, Vs...>,
			U_pack_Vs<H_id, H_id, H_id, Vs...>,
			U_pack_Vs<UP_alter, _unite_, b>,
			U_pack_Vs<Op, V>
		);

	}; nik_ce auto UP_modify = U_store_T<TP_modify>;

/***********************************************************************************************************************/

// monoid:

	template<auto Op, auto Pred = _same_, auto b = H_id>
	struct TP_modify_monoid
	{
		template<auto d, auto p, auto V>
		nik_ces auto result = unpack_<p, UP_modify, d, b, Pred, Op, V>;

	}; template<auto Op, auto Pred = _same_, auto b = H_id>
		nik_ce auto UP_modify_monoid = U_store_T<TP_modify_monoid<Op, Pred, b>>;

/***********************************************************************************************************************/

// fold:

	struct TP_modify_fold
	{
		template<auto d, auto b, auto Pred, auto Op, auto V, auto... Vs>
		nik_ces auto result = TP_cascade::template result<d, UP_modify_monoid<Op, Pred, b>, V, Vs...>;

	}; nik_ce auto UP_modify_fold = U_store_T<TP_modify_fold>;

/***********************************************************************************************************************/

// merge:

	using TP_merge		= TP_modify_fold;
	nik_ce auto UP_merge	= U_store_T<TP_merge>;

	using TL_merge		= TP_unpack<UP_merge>;
	nik_ce auto UL_merge	= UP_unpack<UP_merge>;

	template<auto Pred, auto Op, auto V, auto... Vs>
	nik_ce auto pack_merge = TP_merge::template result<MD::initial_depth, H_id, Pred, Op, V, Vs...>;

	template<auto p, auto Op, auto Pred = _same_, auto V = U_null_Vs, auto b = H_id, auto d = MD::initial_depth>
	nik_ce auto list_merge = TL_merge::template result<d, p, b, Pred, Op, V>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// match:

	// This operator is intended for use within machine tests, with the _h1_pair option.

/***********************************************************************************************************************/

	struct TP_match
	{
		template<auto Pred, auto V, auto... Vs>
		nik_ces auto _result()
		{
			nik_ce auto pos  = find_<U_alias<Pred, V>, Vs...>;
			nik_ce auto size = sizeof...(Vs);

			return overload<_to_tuple_, bool{pos < size}, pos>;
		}

		template<auto Pred, auto V, auto... Vs>
		nik_ces auto result = _result<Pred, V, Vs...>();

	}; nik_ce auto UP_match = U_store_T<TP_match>;

	struct TL_match
	{
		template<auto p, auto Pred, auto V>
		nik_ces auto result = unpack_<p, UP_match, Pred, V>;

	}; nik_ce auto UL_match = U_store_T<TL_match>;

	template<auto Pred, auto V, auto... Vs>
	nik_ce auto pack_match = TP_match::template result<Pred, V, Vs...>;

	template<auto p, auto V, auto Pred = _same_>
	nik_ce auto list_match = TL_match::template result<p, Pred, V>;

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

