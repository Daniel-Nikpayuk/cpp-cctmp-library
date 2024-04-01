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

//#include"contr/initialize_v0.hpp"
//#include"contr/array_square_v0.hpp"
//#include"contr/vector_add_v0.hpp"
//#include"contr/array_add_v0.hpp"
#include"contr/sum_v0.hpp"
#include"contr/dot_product_v0.hpp"
#include"contr/convolution_v0.hpp"
//#include"contr/first_less_than_five_v0.hpp"
//#include"contr/all_less_than_five_v0.hpp"
//#include"contr/change_of_base_printer_v0.hpp"
//#include"contr/array_printer_v0.hpp"

#include"inventory.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// repeat:

/***********************************************************************************************************************/

// initialize:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// map:

/***********************************************************************************************************************/

// array_square:
// vector_add:
// array_add:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/

// sum:

	// v0:

		template<typename SizeType, typename T>
		constexpr void unit_test_chord_sum_v0(T v, T b, T e)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_sum_v0<SizeType>,
				_chord_sum_v0, cctmp::null_env, T*
			>;

			T_chord_fast_apply::template result<T*>(&v, b, e);
			printf("%d\n", v);
		}

/***********************************************************************************************************************/

// dot product:

	// v0:

		template<typename SizeType, typename T, typename S0, typename S1>
		constexpr void unit_test_chord_dot_product_v0(T v, const S0 & s0, const S1 & s1)
		{
			using T_chord_fast_apply = chord::T_fast_apply
			<
				contr_object_chord_dot_product_v0<SizeType>,
				_chord_dot_product_v0, cctmp::null_env, T*
			>;

			T_chord_fast_apply::template result<T*>(&v, s0.cbegin(), s0.cend(), s1.cbegin());
			printf("%d\n", v);
		}

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

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find:

/***********************************************************************************************************************/

// first_less_than_five:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sift:

/***********************************************************************************************************************/

// all_less_than_five:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// progressions:

/***********************************************************************************************************************/

// change_of_base_printer:
// array_printer:

