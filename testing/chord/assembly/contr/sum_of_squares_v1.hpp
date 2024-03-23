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
	struct T_contr_object_chord_sum_of_squares_v1
	{
		using size_type = SizeType;

		constexpr static size_type value[][8] =
		{
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   9,   8,   5,   0,   0,   0,   0,   1 }, 
			{   8,   9,   0,   1,   0,   0,   0,   1 }, 
			{   8,   0,   0,   0,   0,   0,   0,   1 }, 
			{  14,   0,  64,   0,   0,   0,   0,   1 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{  14,   0,  24,   0,   0,   0,   0,   1 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{  13,   3,   9,   0,   0,   0,   0,   4 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   6,   1,   0,  21,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{  13,   3,  13,   0,   0,   0,   0,   5 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   3,   0,   0,   0,   0,   1 }, 
			{   7,  12,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{  13,   3,  18,   0,   0,   0,   0,   5 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   3,   0,   0,   0,   0,   1 }, 
			{   7,  12,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   4,   0,   0,   0,   0,   1 }, 
			{  11,   1,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{  14,   0,  49,   0,   0,   0,   0,   1 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{  13,   3,  28,   0,   0,   0,   0,   4 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   6,   1,   0,  19,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{  10,   0,   7,   0,   0,   0,   0,   1 }, 
			{  13,   3,  33,   0,   0,   0,   0,   5 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   3,   0,   0,   0,   0,   1 }, 
			{   7,  12,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{   7,  13,   3,   6,   0,   0,   0,   1 }, 
			{  12,   3,   0,   0,   0,   0,   0,   1 }, 
			{  10,   0,   7,   0,   0,   0,   0,   1 }, 
			{  13,   3,  41,   0,   0,   0,   0,   5 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   4,   0,   0,   0,   0,   1 }, 
			{   7,  12,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{   7,  13,   3,   7,   0,   0,   0,   1 }, 
			{  12,   3,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   5,   0,   0,   0,   0,   1 }, 
			{  11,   1,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{  10,   0,  26,   0,   0,   0,   0,   1 }, 
			{  13,   3,  52,   0,   0,   0,   0,   5 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   1,   0,   0,   0,   0,   1 }, 
			{   7,  12,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{  13,   3,  57,   0,   0,   0,   0,   5 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   2,   0,   0,   0,   0,   1 }, 
			{   7,  12,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{   7,  13,   3,   3,   0,   0,   0,   1 }, 
			{  12,   1,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{   7,  13,   1,   1,   0,   0,   0,   1 }, 
			{  12,   1,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 } 
		};

	}; template<typename SizeType>
		constexpr auto contr_object_chord_sum_of_squares_v1 = cctmp::U_store_T
		<
			T_contr_object_chord_sum_of_squares_v1<SizeType>
		>;

