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

// object:

	template<typename SizeType>
	struct T_contr_object_chord_array_add_v0
	{
		using size_type = SizeType;

		using AN = assembly::AN;
		using AT = assembly::AT;

		constexpr static size_type value[][8] =
		{
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::hash       , AT::port      ,   5,   0,   0,   0,   0,   1 },
			{ AN::pad        , AT::select    ,   0,   1,   0,   0,   0,   1 },
			{ AN::pad        , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::go_to      , AT::id        , 129,   0,   0,   0,   0,   1 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::go_to      , AT::id        ,  99,   0,   0,   0,   0,   1 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::go_to      , AT::id        ,  93,   0,   0,   0,   0,   1 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,  11,   0,   0,   0,   0,   4 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::lookup     , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,  15,   0,   0,   0,   0,   4 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::lookup     , AT::first     ,   1,  27,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,  19,   0,   0,   0,   0,   5 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   6,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,  10,   0,   0,   0,   0,   1 },
			{ AN::apply      , AT::back      ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,  26,   0,   0,   0,   0,   4 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::lookup     , AT::first     ,   1,  27,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,  30,   0,   0,   0,   0,   5 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   7,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,  11,   0,   0,   0,   0,   1 },
			{ AN::apply      , AT::back      ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,  37,   0,   0,   0,   0,   5 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   8,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   9,   0,   0,   0,   0,   1 },
			{ AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,  46,   0,   0,   0,   0,   4 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::lookup     , AT::first     ,   1,   5,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,  50,   1,   0,   0,   0,   5 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   6,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,  55,   0,   0,   0,   0,   5 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   7,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   8,   0,   0,   0,   0,   1 },
			{ AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,  64,   0,   0,   0,   0,   4 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::lookup     , AT::first     ,   1,  13,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,  68,   0,   0,   0,   0,   5 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   6,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,  73,   0,   0,   0,   0,   5 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   7,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   8,   0,   0,   0,   0,   1 },
			{ AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::next       , AT::inc       ,   0,   0,   0,   0,   0,   1 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::next       , AT::dec       ,   0,   0,   0,   0,   0,   1 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::none      ,   0,   0,   0,   0,   0,   1 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::verse     ,   6,   6,   0,   0,   0,   1 },
			{ AN::next       , AT::id        ,  80,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::verse     ,   6,   7,   0,   0,   0,   1 },
			{ AN::next       , AT::id        ,  80,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::verse     ,   6,   9,   0,   0,   0,   1 },
			{ AN::next       , AT::id        ,  80,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::none      ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   6,   0,   0,   0,   0,   1 },
			{ AN::map        , AT::id        ,  62,   9,  44,  86,   0,   1 },
			{ AN::map        , AT::back      ,   9,  44,   0,   0,   0,   1 },
			{ AN::arg        , AT::drop      ,   6,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::pound      , AT::id        ,   7,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      , 102,   1,   0,   0,   0,   5 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   1,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      , 107,   0,   0,   0,   0,   5 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      , 112,   0,   0,   0,   0,   5 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   3,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      , 117,   0,   0,   0,   0,   5 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   4,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      , 122,   1,   0,   0,   0,   5 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   5,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::verse     ,   6,   6,   0,   0,   0,   1 },
			{ AN::bind       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::verse     ,   1,   1,   0,   0,   0,   1 },
			{ AN::bind       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }
		};

	}; template<typename SizeType>
		constexpr auto contr_object_chord_array_add_v0 = cctmp::U_store_T
		<
			T_contr_object_chord_array_add_v0<SizeType>
		>;

