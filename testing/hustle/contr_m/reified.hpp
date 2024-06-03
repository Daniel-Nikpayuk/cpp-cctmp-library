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

// reified:

	// manually created assembly controller to test if:

		// "(define (main n)         "
		// "  ((if (= n 0) + *) 2 3) "
		// ")                        "

	// will actually dispatch (branch) and compile.

/***********************************************************************************************************************/

// object:

	template<typename SizeType>
	struct T_contr_object_hustle
	{
		using size_type = SizeType;

		using AN = assembly::AN;
		using AT = assembly::AT;

		constexpr static size_type value[][8] =
		{

	/* line   0 */	{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
	/* line   1 */	{ AN::hash       , AT::id        ,   5,   0,   0,   0,   0,   1 },
	/* line   2 */	{ AN::pad        , AT::select    ,   0,   1,   0,   0,   0,   1 },
	/* line   3 */	{ AN::pad        , AT::id        ,   0,   0,   0,   0,   0,   1 },
	/* line   4 */	{ AN::go_to      , AT::id        ,  35,   0,   0,   0,   0,   1 }, // <- index 35 was 33.

	/* line   5 */	{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },

	/* line   6 */	{ AN::eval       , AT::back      ,   7,   0,   0,   0,   0,   4 }, // =
	/* line   7 */	{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
	/* line   8 */	{ AN::lookup     , AT::first     ,   0,   7,   0,   0,   0,   1 },
	/* line   9 */	{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },

	/* line  10 */	{ AN::eval       , AT::back      ,  11,   0,   0,   0,   0,   5 }, // n
	/* line  11 */	{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
	/* line  12 */	{ AN::arg        , AT::select    ,   1,   0,   0,   0,   0,   1 },
	/* line  13 */	{ AN::arg        , AT::drop      ,   0,   0,   0,   0,   0,   1 },
	/* line  14 */	{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },

	/* line  15 */	{ AN::type       , AT::n_number  ,   0,   0,   0,   0,   0,   1 }, // 0
	/* line  16 */	{ AN::literal    , AT::back      ,   0,   0,   0,   0,   0,   1 },

	/* line  17 */	{ AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1 },
	/* line  18 */	{ AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1 },

	/* line  19 */	{ AN::invert     , AT::id        ,  24,   0,   0,   0,   0,   1 }, // ante

	/* line  20 */	{ AN::eval       , AT::back      ,  21,   0,   0,   0,   0,   4 }, // +
	/* line  21 */	{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
	/* line  22 */	{ AN::lookup     , AT::first     ,   0,  12,   0,   0,   0,   1 },
	/* line  23 */	{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },

	/* line  24 */	{ AN::go_to      , AT::id        ,  28,   0,   0,   0,   0,   1 }, // conse

	/* line  25 */	{ AN::eval       , AT::back      ,  26,   0,   0,   0,   0,   4 }, // *
	/* line  26 */	{ AN::id         , AT::id        ,   0,   0,   0,   0,   0,   1 },
	/* line  27 */	{ AN::lookup     , AT::first     ,   0,  14,   0,   0,   0,   1 },
	/* line  28 */	{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },

	/* line  29 */	{ AN::type       , AT::n_number  ,   0,   0,   0,   0,   0,   1 }, // 2
	/* line  30 */	{ AN::literal    , AT::back      ,   2,   0,   0,   0,   0,   1 },

	/* line  31 */	{ AN::type       , AT::n_number  ,   0,   0,   0,   0,   0,   1 }, // 3
	/* line  32 */	{ AN::literal    , AT::back      ,   3,   0,   0,   0,   0,   1 },

	/* line  33 */	{ AN::arg        , AT::select    ,   2,   0,   0,   0,   0,   1 }, // <- line inserted.
	/* line  34 */	{ AN::apply      , AT::first     ,   0,   0,   0,   0,   0,   1 }, // <- line inserted.

	/* line  35 */	{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 },

	/* line  36 */	{ AN::arg        , AT::verse     ,   1,   1,   0,   0,   0,   1 },
	/* line  37 */	{ AN::bind       , AT::first     ,   0,   0,   0,   0,   0,   1 }, // <- was AT::back
	/* line  38 */	{ AN::halt       , AT::first     ,   0,   0,   0,   0,   0,   1 }

		};

	}; template<typename SizeType>
		constexpr auto contr_object_hustle = cctmp::U_store_T
		<
			T_contr_object_hustle<SizeType>
		>;

// square:

	// v0:

		template<typename SizeType, typename T>
		constexpr void unit_test_hustle(T v)
		{
			using T_hustle_fast_apply = hustle::T_fast_apply
			<
				contr_object_hustle<SizeType>,
				_hustle_test_func, cctmp::null_env, T
			>;

			auto val = T_hustle_fast_apply::result(v);
			printf("%d\n", val);
		}

	//	unit_test_hustle<gindex_type>(0);

