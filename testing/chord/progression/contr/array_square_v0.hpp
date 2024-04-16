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
	struct T_contr_object_chord_array_square_v0
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
			{ AN::go_to      , AT::id        , 102,   0,   0,   0,   0,   1 }, 
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::go_to      , AT::id        ,  83,   0,   0,   0,   0,   1 }, 
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::go_to      , AT::id        ,  78,   0,   0,   0,   0,   1 }, 
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
			{ AN::arg        , AT::select    ,   4,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::select    ,   6,   0,   0,   0,   0,   1 }, 
			{ AN::apply      , AT::back      ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::select    ,   5,   0,   0,   0,   0,   1 }, 
			{ AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::eval       , AT::back      ,  30,   0,   0,   0,   0,   4 }, 
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::lookup     , AT::first     ,   1,   5,   0,   0,   0,   1 }, 
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::eval       , AT::back      ,  34,   1,   0,   0,   0,   5 }, 
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::select    ,   4,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::eval       , AT::back      ,  39,   0,   0,   0,   0,   5 }, 
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::select    ,   5,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::select    ,   6,   0,   0,   0,   0,   1 }, 
			{ AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::eval       , AT::back      ,  48,   0,   0,   0,   0,   4 }, 
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::lookup     , AT::first     ,   1,  13,   0,   0,   0,   1 }, 
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::eval       , AT::back      ,  52,   0,   0,   0,   0,   5 }, 
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::select    ,   4,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::eval       , AT::back      ,  57,   0,   0,   0,   0,   5 }, 
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::select    ,   5,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::select    ,   6,   0,   0,   0,   0,   1 }, 
			{ AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::next       , AT::inc       ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::next       , AT::dec       ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::out_in_ins , AT::pred      ,  46,   0,   0,   0,   0,   1 }, 
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::out_in_ins , AT::act_mut   ,   9,  28,   0,   0,   0,   1 }, 
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::verse     ,   4,   4,   0,   0,   0,   1 }, 
			{ AN::next       , AT::cont      ,  64,   1,   0,   0,   0,   1 }, 
			{ AN::next       , AT::cont      ,  64,   3,   0,   0,   0,   1 }, 
			{ AN::next       , AT::end       ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::cycle      , AT::side      ,  70,  72,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::select    ,   4,   0,   0,   0,   0,   1 }, 
			{ AN::cycle      , AT::id        ,  68,  77,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::drop      ,   4,   0,   0,   0,   0,   1 }, 
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::eval       , AT::back      ,  85,   1,   0,   0,   0,   5 }, 
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::select    ,   1,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::eval       , AT::back      ,  90,   0,   0,   0,   0,   5 }, 
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::eval       , AT::back      ,  95,   0,   0,   0,   0,   5 }, 
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::select    ,   3,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::select    ,   4,   0,   0,   0,   0,   1 }, 
			{ AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::arg        , AT::verse     ,   1,   1,   0,   0,   0,   1 }, 
			{ AN::bind       , AT::first     ,   0,   0,   0,   0,   0,   1 }, 
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 } 
		};

	}; template<typename SizeType>
		constexpr auto contr_object_chord_array_square_v0 = cctmp::U_store_T
		<
			T_contr_object_chord_array_square_v0<SizeType>
		>;

