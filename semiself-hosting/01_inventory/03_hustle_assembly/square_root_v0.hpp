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
	struct T_contr_object_hustle_square_root_v0
	{
		using size_type = SizeType;

		using AN = MN;
		using AT = MT;

		constexpr static size_type rowsize = 186;

		constexpr static size_type value[] =
		{
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::hash       , AT::id        ,   5,   0,   0,   0,   0,   1,
			AN::pad        , AT::select    ,   0,   1,   0,   0,   0,   1,
			AN::pad        , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::go_to      , AT::id        , 182,   0,   0,   0,   0,   1,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::go_to      , AT::id        ,  24,   0,   0,   0,   0,   1,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,   9,   0,   0,   0,   0,   4,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::lookup     , AT::first     ,   0,   3,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  13,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  18,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   3,   0,   0,   0,   0,   1,
			AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::go_to      , AT::id        ,  58,   0,   0,   0,   0,   1,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  28,   0,   0,   0,   0,   4,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::lookup     , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  32,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::type       , AT::n_number  ,   0,   0,   0,   0,   0,   1,
			AN::literal    , AT::back      ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   3,   0,   0,   0,   0,   1,
			AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::invert     , AT::id        ,  52,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  42,   0,   0,   0,   0,   4,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::lookup     , AT::first     ,   0,   2,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  46,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   3,   0,   0,   0,   0,   1,
			AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::go_to      , AT::id        ,  57,   0,   0,   0,   0,   1,
			AN::eval       , AT::first     ,  54,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::go_to      , AT::id        ,  93,   0,   0,   0,   0,   1,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  62,   0,   0,   0,   0,   4,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::lookup     , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::pound      , AT::id        ,  26,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  67,   0,   0,   0,   0,   4,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::lookup     , AT::first     ,   0,   2,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::pound      , AT::id        ,   7,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  72,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::verse     ,   2,   6,   0,   0,   0,   1,
			AN::bind       , AT::back      ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  79,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   1,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   5,   0,   0,   0,   0,   1,
			AN::apply      , AT::back      ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::verse     ,   2,   4,   0,   0,   0,   1,
			AN::bind       , AT::back      ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  88,   0,   0,   0,   0,   4,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::lookup     , AT::first     ,   0,   5,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   3,   0,   0,   0,   0,   1,
			AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::go_to      , AT::id        , 120,   0,   0,   0,   0,   1,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      ,  97,   0,   0,   0,   0,   4,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::lookup     , AT::first     ,   0,   4,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      , 101,   0,   0,   0,   0,   4,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::lookup     , AT::first     ,   0,   1,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      , 105,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      , 110,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   3,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   5,   0,   0,   0,   0,   1,
			AN::apply      , AT::back      ,   0,   0,   0,   0,   0,   1,
			AN::type       , AT::n_number  ,   0,   0,   0,   0,   0,   1,
			AN::literal    , AT::back      ,   2,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   4,   0,   0,   0,   0,   1,
			AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::go_to      , AT::id        , 147,   0,   0,   0,   0,   1,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::pound      , AT::id        ,  95,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      , 125,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      , 130,   0,   0,   0,   0,   4,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::lookup     , AT::first     ,   0,   4,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      , 134,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   1,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      , 139,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   5,   0,   0,   0,   0,   1,
			AN::apply      , AT::back      ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::verse     ,   2,   3,   0,   0,   0,   1,
			AN::bind       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::go_to      , AT::id        , 176,   0,   0,   0,   0,   1,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::pound      , AT::id        ,  60,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      , 152,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::verse     ,   2,   3,   0,   0,   0,   1,
			AN::bind       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::invert     , AT::id        , 164,   0,   0,   0,   0,   1,
			AN::eval       , AT::first     , 160,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::go_to      , AT::id        , 175,   0,   0,   0,   0,   1,
			AN::pound      , AT::port      , 149,   0,   0,   0,   0,   1,
			AN::pound      , AT::id        , 122,   0,   0,   0,   0,   1,
			AN::eval       , AT::back      , 168,   0,   0,   0,   0,   5,
			AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1,
			AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::verse     ,   2,   4,   0,   0,   0,   1,
			AN::bind       , AT::back      ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::verse     ,   2,   3,   0,   0,   0,   1,
			AN::bind       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::pound      , AT::port      , 149,   0,   0,   0,   0,   1,
			AN::type       , AT::push      ,   0,   0,   0,   0,   0,   1,
			AN::literal    , AT::back      ,   1,   0,   0,   0,   0,   1,
			AN::arg        , AT::verse     ,   2,   2,   0,   0,   0,   1,
			AN::bind       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::arg        , AT::verse     ,   1,   1,   0,   0,   0,   1,
			AN::bind       , AT::first     ,   0,   0,   0,   0,   0,   1,
			AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1
		};

	}; template<typename SizeType>
		constexpr auto contr_object_hustle_square_root_v0 = U_store_T
		<
			T_contr_object_hustle_square_root_v0<SizeType>
		>;

/***********************************************************************************************************************/

// subtract:

	struct T_hustle_subtract
	{
		using F = T_store_U<_subtract_>;

		template<typename T>
		constexpr static auto result(T v) { return -v; }

		template<typename... Ts>
		constexpr static auto result(Ts... vs) { return F::template result<Ts...>(vs...); }

	}; constexpr auto _hustle_subtract_ = U_store_T<T_hustle_subtract>;

/***********************************************************************************************************************/

// env:

	template<typename SizeType>
	struct T_static_env_hustle_square_root_v0
	{
		constexpr static auto value = env_tuple<SizeType>
		(
			_less_than_       ,

			_add_             ,
			_hustle_subtract_ ,
			_multiply_        ,
			_divide_          ,

			0.0001
		);

	}; template<typename SizeType>
		constexpr auto env_hustle_square_root_v0 = U_store_T<T_static_env_hustle_square_root_v0<SizeType>>;

/***********************************************************************************************************************/

// unit:

	template<typename SizeType, typename T>
	constexpr T inventory_square_root_v0(T x)
	{
		using T_apply = T_metapile_apply
		<
			SizeType, contr_object_hustle_square_root_v0<SizeType>,
			env_hustle_square_root_v0<SizeType>, U_pack_Ts<T>
		>;

		return T_apply::result(x);
	}

}} // namespace cctmp::inventory

