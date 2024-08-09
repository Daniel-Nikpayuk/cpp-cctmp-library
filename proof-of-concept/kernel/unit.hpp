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

// unit test:

#include"contr/different_v0.hpp"

#include"inventory.hpp"

/***********************************************************************************************************************/

// different:

	// v0:

		template<typename SizeType, typename In, typename End, typename In1>
		constexpr bool kernel_different_v0(In in, End end, In1 in1)
		{
			using rtn_type = unsigned char;

			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_different_v0<SizeType>,
				_chord_different_v0, cctmp::null_env, rtn_type
			>;

			return T_chord_fast_apply::result(rtn_type{0}, in, end, in1);
		}

/***********************************************************************************************************************/

// same:

	// v0:

		template<typename SizeType, typename In, typename End, typename In1>
		constexpr bool kernel_same_v0(In in, End end, In1 in1)
			{ return not kernel_different_v0<SizeType, In, End, In1>(in, end, in1); }

/***********************************************************************************************************************/

// square root:

	// v0:

		template<typename SizeType, typename T>
		constexpr void unit_test_hustle_square_root_v0(T x)
		{
			using T_hustle_fast_apply = hustle::T_fast_apply
			<
				contr_object_hustle_square_root_v0<SizeType>,
				_hustle_square_root_v0, cctmp::null_env, T
			>;

			auto val = T_hustle_fast_apply::result(x);
			printf("%1.11f\n", val);
		}

