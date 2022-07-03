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

	template<auto... Vs> using auto_pack			= typename cctmp::template auto_pack<Vs...>;
	template<typename... Ts> using tuple			= typename cctmp::template tuple<Ts...>;
	template<auto... Vs> using block			= typename cctmp::template block<Vs...>;

	nik_ce auto _zero					= cctmp::_zero;

	nik_ce auto U_null_Vs					= cctmp::U_null_Vs;

	nik_ce auto _h1						= cctmp::_h1;
	nik_ce auto _register					= cctmp::_register;
	nik_ce auto _argument					= cctmp::_argument;
	nik_ce auto _value					= cctmp::_value;

	nik_ce auto _less_than_					= cctmp::_less_than_;

	nik_ce auto U_same					= cctmp::U_same;
	nik_ce auto U_length					= cctmp::U_length;
	nik_ce auto U_find					= cctmp::U_find;

	template<typename T> nik_ce auto U_store_T		= cctmp::template U_store_T<T>;
	template<auto... Vs> nik_ce auto U_pack_Vs		= cctmp::template U_pack_Vs<Vs...>;

	template<auto... Vs> nik_ce auto _curry_		= cctmp::template _curry_<Vs...>;
	template<auto... Vs> nik_ce auto U_custom		= cctmp::template U_custom<Vs...>;

	template<auto... Vs> nik_ce auto unpack_		= cctmp::template unpack_<Vs...>;

	template<auto... Vs> nik_ce auto unite			= cctmp::template unite<Vs...>;
	template<auto... Vs> nik_ce auto unpack			= cctmp::template unpack<Vs...>;
	template<auto... Vs> nik_ce auto function		= cctmp::template function<Vs...>;
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
		template<auto d, auto n, auto p>
		nik_ces auto result = cctmp::variable_start<d, n, BN::sifter>(p);

	}; nik_ce auto U_at = U_store_T<T_at>;

	template<auto n, auto p, auto d = MD::initial_depth>
	nik_ce auto at = T_at::template result<d, n, p>;

// left:

	struct T_left
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = cctmp::function_start<d, n, BN::left>(p);

	}; nik_ce auto U_left = U_store_T<T_left>;

	template<auto n, auto p, auto d = MD::initial_depth>
	nik_ce auto left = T_left::template result<d, n, p>;

// right:

	struct T_right
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = cctmp::variable_start<d, n, BN::right>(p);

	}; nik_ce auto U_right = U_store_T<T_right>;

	template<auto n, auto p, auto d = MD::initial_depth>
	nik_ce auto right = T_right::template result<d, n, p>;

// cut:

	struct T_cut
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = cctmp::function_start<d, n, BN::filter>(p);

	}; nik_ce auto U_cut = U_store_T<T_cut>;

	template<auto n, auto p, auto d = MD::initial_depth>
	nik_ce auto cut = T_cut::template result<d, n, p>;

// split:

	struct T_split
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = cctmp::function_start<d, n, BN::split>(p);

	}; nik_ce auto U_split = U_store_T<T_split>;

	template<auto n, auto p, auto d = MD::initial_depth>
	nik_ce auto split = T_split::template result<d, n, p>;

// segment:

	struct T_block_segment
	{
		template<auto d, auto n, auto m>
		nik_ces auto result = NIK_BEGIN_BLOCK(9, segment, d, n), m NIK_END_BLOCK;

	}; nik_ce auto U_block_segment = U_store_T<T_block_segment>;

	struct T_segment
	{
		template<auto d, auto n, auto m, auto dec = 3>
		nik_ces auto result = cctmp::compel_start<d, dec>(U_pack_Vs<U_block_segment, n, m>);

	}; nik_ce auto U_segment = U_store_T<T_segment>;

	template<auto n, auto m = index_type{0}, auto dec = 3, auto d = MD::initial_depth>
	nik_ce auto segment = T_segment::template result<d, n, m, dec>;

// fold:

	struct T_block_fold
	{
		template<auto d, auto op, auto V, auto l>
		nik_ces auto result = V;

	}; nik_ce auto U_block_fold = U_store_T<T_block_fold>;

	template<auto d, auto op, auto V, auto... Vs, nik_vp(l)(auto_pack<Vs...>*)>
	nik_ce auto T_block_fold::result<d, op, V, l> = NIK_FOLD_BLOCK(d, sizeof...(Vs), op, V, Vs);

	struct T_fold
	{
		template<auto d, auto op, auto V, auto l, auto dec = 3>
		nik_ces auto result = cctmp::compel_start<d, dec>(U_pack_Vs<U_block_fold, op, V, l>);

	}; nik_ce auto U_fold = U_store_T<T_fold>;

	template<auto op, auto V, auto l, auto dec = 3, auto d = MD::initial_depth>
	nik_ce auto fold = T_fold::template result<d, op, V, l, dec>;

// parse (fold with one lookahead):

	struct T_block_parse
	{
		template<auto d, auto op, auto V, auto l>
		nik_ces auto result = V;

	}; nik_ce auto U_block_parse = U_store_T<T_block_parse>;

	template<auto d, auto op, auto V, auto... Vs, nik_vp(l)(auto_pack<Vs...>*)>
	nik_ce auto T_block_parse::result<d, op, V, l> = NIK_PARSE_BLOCK(d, sizeof...(Vs)-1, op, V, Vs);

	struct T_parse
	{
		template<auto d, auto op, auto V, auto l, auto dec = 3>
		nik_ces auto result = cctmp::compel_start<d, dec>(U_pack_Vs<U_block_parse, op, V, l>);

	}; nik_ce auto U_parse = U_store_T<T_parse>;

	template<auto op, auto V, auto l, auto dec = 3, auto d = MD::initial_depth>
	nik_ce auto parse = T_parse::template result<d, op, V, l, dec>;

// cascade:

	struct T_block_cascade
	{
		template<auto d, auto op, auto V, auto l>
		nik_ces auto result = V;

	}; nik_ce auto U_block_cascade = U_store_T<T_block_cascade>;

	template<auto d, auto op, auto V, auto... Vs, nik_vp(l)(auto_pack<Vs...>*)>
	nik_ce auto T_block_cascade::result<d, op, V, l> = NIK_CASCADE_BLOCK(d, sizeof...(Vs), op, V, Vs);

	struct T_cascade
	{
		template<auto d, auto op, auto V, auto l, auto dec = 3>
		nik_ces auto result = cctmp::compel_start<d, dec>(U_pack_Vs<U_block_cascade, op, V, l>);

	}; nik_ce auto U_cascade = U_store_T<T_cascade>;

	template<auto op, auto V, auto l, auto dec = 3, auto d = MD::initial_depth>
	nik_ce auto cascade = T_cascade::template result<d, op, V, l, dec>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// mutators:

/***********************************************************************************************************************/

// erase:

	struct T_erase
	{
		nik_ces auto c = controller
		<
			function < BN::filter >,
			stage    <            >,
			unite    <     _value >
		>;

		template<auto d, auto n, auto p>
		nik_ces auto result = cctmp::general_start<d, c>(p, U_pack_Vs<n>, U_null_Vs);

	}; nik_ce auto U_erase = U_store_T<T_erase>;

	template<auto n, auto p, auto d = MD::initial_depth>
	nik_ce auto erase = T_erase::template result<d, n, p>;

// insert:

	struct T_insert
	{
		nik_ces auto c = controller
		<
			function <         BN::split >,
			stage    <                   >,
			copy     < _zero , _register >,
			unite    <         _value    >
		>;

		template<auto d, auto v, auto n, auto p>
		nik_ces auto result = cctmp::general_start<d, c, v>(p, U_pack_Vs<n>, U_null_Vs);

	}; nik_ce auto U_insert = U_store_T<T_insert>;

	template<auto v, auto n, auto p, auto d = MD::initial_depth>
	nik_ce auto insert = T_insert::template result<d, v, n, p>;

// replace:

	struct T_replace
	{
		nik_ces auto c = controller
		<
			function <         BN::filter >,
			stage    <                    >,
			copy     < _zero , _register  >,
			unite    <         _value     >
		>;

		template<auto d, auto v, auto n, auto p>
		nik_ces auto result = cctmp::general_start<d, c, v>(p, U_pack_Vs<n>, U_null_Vs);

	}; nik_ce auto U_replace = U_store_T<T_replace>;

	template<auto v, auto n, auto p, auto d = MD::initial_depth>
	nik_ce auto replace = T_replace::template result<d, v, n, p>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sort:

/***********************************************************************************************************************/

// insert:

	template<auto cmp = _less_than_>
	struct T_insert_sort
	{
		nik_ces auto c = controller
		<
			unpack   <                   >,
			write    < _zero , _argument >,
			function <         BN::split >,
			stage    <                   >,
			copy     < _zero , _register >,
			unite    <         _value    >
		>;

		template<auto v, auto p>
		nik_ces auto h0 = U_pack_Vs<p, U_find, _curry_<cmp, v>>;

		template<auto d, auto p, auto v>
		nik_ces auto result = cctmp::general_start<d, c, v>(h0<v, p>, U_null_Vs, U_null_Vs, p);

	}; template<auto cmp = _less_than_>
		nik_ce auto U_insert_sort = U_store_T<T_insert_sort<cmp>>;

	template<auto list, auto insert, auto cmp = _less_than_, auto d = MD::initial_depth>
	nik_ce auto insert_sort = T_insert_sort<cmp>::template result<d, list, insert>;

// (sort):

	template
	<
		auto l,
		auto cmp	= _less_than_,
		auto d		= MD::initial_depth
	>
	nik_ce auto sort = T_cascade::template result
	<
		d,
		U_insert_sort<cmp>,
		U_null_Vs,
		l
	>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lookup:

/***********************************************************************************************************************/

// match:

	struct T_lookup_match
	{
		template<auto v, auto p>
		nik_ces auto match()
		{
			nik_ce auto pos  = unpack_<p, U_find, U_custom<U_same, v>>;
			nik_ce auto size = unpack_<p, U_length>;

			return tuple<bool, decltype(pos)>(bool{pos < size}, pos);
		}

		template<auto v, auto p>
		nik_ces auto result = match<v, p>();

	}; nik_ce auto U_lookup_match = U_store_T<T_lookup_match>;

/***********************************************************************************************************************/

// (lookup):

	struct T_lookup
	{
		template<auto d, auto p, auto v, auto dec = 3>
		nik_ces auto result = cctmp::compel_start<d, dec>(U_pack_Vs<U_lookup_match, v, p>);

	}; nik_ce auto U_lookup = U_store_T<T_lookup>;

	template<auto list, auto val, auto dec = 3, auto d = MD::initial_depth>
	nik_ce auto lookup = T_lookup::template result<d, list, val, dec>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_functional

