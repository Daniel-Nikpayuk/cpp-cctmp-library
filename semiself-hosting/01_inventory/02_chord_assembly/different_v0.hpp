/************************************************************************************************************************
**
** Copyright 2022-2024 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

namespace cctmp     {
namespace inventory {

// object:

	template<typename SizeType>
	struct T_contr_object_chord_different_v0
	{
		using size_type = SizeType;

		using AN = MN;
		using AT = MT;

		constexpr static size_type rowsize = 121;

		constexpr static size_type value[] =
		{
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::hash       , AT::port      ,   5,   0,   0,   0,   0,   1,
			AN::pad        , AT::select    ,   0,   1,   0,   0,   0,   1,
			AN::pad        , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::go_to      , AT::id        , 117,   0,   0,   0,   0,   1,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::go_to      , AT::id        ,  92,   0,   0,   0,   0,   1,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::go_to      , AT::id        ,  88,   0,   0,   0,   0,   1,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  11,   0,   0,   0,   0,   4,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::lookup     , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  15,   0,   0,   0,   0,   4,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::lookup     , AT::first     ,   0,   1,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  19,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   5,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   8,   0,   0,   0,   0,   1,
			AN::apply      , AT::back      ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  26,   0,   0,   0,   0,   4,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::lookup     , AT::first     ,   0,   1,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  30,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   6,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   9,   0,   0,   0,   0,   1,
			AN::apply      , AT::back      ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   7,   0,   0,   0,   0,   1,
			AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  41,   0,   0,   0,   0,   4,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::lookup     , AT::first     ,   0,   2,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  45,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   5,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  50,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   6,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   7,   0,   0,   0,   0,   1,
			AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  59,   0,   0,   0,   0,   4,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::lookup     , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  63,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   5,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  68,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   6,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   7,   0,   0,   0,   0,   1,
			AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::next       , AT::inc       ,   0,   0,   0,   0,   0,   1,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::next       , AT::dec       ,   0,   0,   0,   0,   0,   1,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::verse     ,   5,   5,   0,   0,   0,   1,
			AN::next       , AT::id        ,  75,   0,   0,   0,   0,   1,
			AN::halt       , AT::none      ,   0,   0,   0,   0,   0,   1,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::verse     ,   5,   6,   0,   0,   0,   1,
			AN::next       , AT::id        ,  75,   0,   0,   0,   0,   1,
			AN::arg        , AT::verse     ,   5,   8,   0,   0,   0,   1,
			AN::next       , AT::id        ,  75,   0,   0,   0,   0,   1,
			AN::halt       , AT::none      ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   5,   0,   0,   0,   0,   1,
			AN::find       , AT::id        ,  57,   9,  39,  79,  83,   1,
			AN::cycle      , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::pound      , AT::id        ,   7,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  95,   1,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   1,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      , 100,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      , 105,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   3,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      , 110,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   4,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::verse     ,   5,   5,   0,   0,   0,   1,
			AN::bind       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::verse     ,   1,   1,   0,   0,   0,   1,
			AN::bind       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1
		};

	}; template<typename SizeType>
		constexpr auto contr_object_chord_different_v0 = U_store_T
		<
			T_contr_object_chord_different_v0<SizeType>
		>;

/***********************************************************************************************************************/

// env:

	template<typename SizeType>
	struct T_static_env_chord_different_v0
	{
		constexpr static auto value = env_tuple<SizeType>
		(
			_not_equal_   ,
			_dereference_ ,
			_first_       ,
			_id_
		);

	}; template<typename SizeType>
		constexpr auto env_chord_different_v0 = U_store_T<T_static_env_chord_different_v0<SizeType>>;

/***********************************************************************************************************************/

// unit:

	template<typename SizeType, typename In, typename End, typename In1>
	constexpr bool inventory_different_v0(In in, End end, In1 in1)
	{
		using rtn_type = unsigned char;

		using T_apply = T_metapile_apply
		<
			SizeType, contr_object_chord_different_v0<SizeType>,
			env_chord_different_v0<SizeType>, U_pack_Ts<rtn_type>
		>;

		return T_apply::result(rtn_type{0}, in, end, in1);
	}

/***********************************************************************************************************************/

// same:

	template<typename SizeType, typename In, typename End, typename In1>
	constexpr bool inventory_same_v0(In in, End end, In1 in1)
		{ return not inventory_different_v0<SizeType, In, End, In1>(in, end, in1); }

}} // namespace cctmp::inventory

