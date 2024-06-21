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
	struct T_contr_object_chord_factorial_v5
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
			{ AN::go_to      , AT::id        ,  54,   0,   0,   0,   0,   1 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,   7,   0,   0,   0,   0,   4 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::lookup     , AT::first     ,   0,  12,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,  11,   0,   0,   0,   0,   5 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   1,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1 },
			{ AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::branch     , AT::id        ,  18,   0,   0,   0,   0,   1 },
			{ AN::go_to      , AT::id        ,  21,   0,   0,   0,   0,   1 },
			{ AN::type       , AT::push      ,   0,   0,   0,   0,   0,   1 },
			{ AN::literal    , AT::first     ,   1,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,  23,   0,   0,   0,   0,   4 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::lookup     , AT::first     ,   0,  25,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,  27,   0,   0,   0,   0,   5 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   1,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1 },
			{ AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::pound      , AT::port      ,   5,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,  35,   0,   0,   0,   0,   3 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::verse     ,   1,   2,   0,   0,   0,   1 },
			{ AN::bind       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,  40,   0,   0,   0,   0,   4 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::lookup     , AT::first     ,   0,  21,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,  44,   0,   0,   0,   0,   5 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   1,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::eval       , AT::back      ,  49,   0,   0,   0,   0,   3 },
			{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1 },
			{ AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::arg        , AT::verse     ,   1,   1,   0,   0,   0,   1 },
			{ AN::bind       , AT::first     ,   0,   0,   0,   0,   0,   1 },
			{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }
		};

	}; template<typename SizeType>
		constexpr auto contr_object_chord_factorial_v5 = cctmp::U_store_T
		<
			T_contr_object_chord_factorial_v5<SizeType>
		>;

