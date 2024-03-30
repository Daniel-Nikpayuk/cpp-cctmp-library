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

#include"contr/convolution_v0.hpp"

#include"inventory.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/

// convolution:

	// v0:

		template<typename SizeType, typename T, typename S0, typename S1>
		constexpr void unit_test_chord_convolution_v0(T v, const S0 & s0, const S1 & s1)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_convolution_v0<SizeType>,
				_chord_convolution_v0, cctmp::null_env, T*
			>;

			T_chord_fast_apply::template result<T*>(&v, s0.cbegin(), s0.cend(), s1.cbegin());
			printf("%d\n", v);
		}

