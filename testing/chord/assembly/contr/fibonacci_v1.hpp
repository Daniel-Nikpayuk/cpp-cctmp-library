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
	struct T_contr_object_chord_fibonacci_v1
	{
		using size_type = SizeType;

		constexpr static size_type value[][5] =
		{
			{   0,   0,   0,   0,   1 }, 
			{  13,   2,   5,   0,   1 }, 
			{  12,   3,   0,   1,   1 }, 
			{  12,   0,   0,   0,   1 }, 
			{  18,   0, 109,   0,   1 }, 
			{   0,   0,   0,   0,   1 }, 
			{  12,   3,   2,   2,   1 }, 
			{  12,   0,   0,   0,   1 }, 
			{  17,   5,   9,   0,   4 }, 
			{   0,   0,   0,   0,   1 }, 
			{   9,   1,   0,  11,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  17,   5,  13,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  11,   3,   1,   0,   1 }, 
			{  11,   8,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{   7,   5,  18,   0,   4 }, 
			{   0,   0,   0,   0,   1 }, 
			{   3,   0, 120, 121,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  11,   3,   4,   0,   1 }, 
			{  15,   1,   0,   0,   1 }, 
			{  19,   0, 102,   0,   1 }, 
			{  17,   5,  25,   0,   4 }, 
			{   0,   0,   0,   0,   1 }, 
			{   9,   1,   0,  11,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  17,   5,  29,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  11,   3,   1,   0,   1 }, 
			{  11,   8,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{   7,   5,  34,   0,   4 }, 
			{   0,   0,   0,   0,   1 }, 
			{   3,   0, 162, 163,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  11,   3,   4,   0,   1 }, 
			{  15,   1,   0,   0,   1 }, 
			{  19,   0,   0,   0,   1 }, 
			{  17,   5,  41,   0,   4 }, 
			{   0,   0,   0,   0,   1 }, 
			{   9,   1,   0,  25,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  17,   5,  45,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  11,   3,   1,   0,   1 }, 
			{  11,   8,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  11,   3,   4,   0,   1 }, 
			{  15,   1,   0,   0,   1 }, 
			{  11,   3,   2,   0,   1 }, 
			{  11,  11,   0,   0,   1 }, 
			{  17,   5,  54,   0,   4 }, 
			{   0,   0,   0,   0,   1 }, 
			{   9,   1,   0,  25,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  17,   5,  58,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  11,   3,   2,   0,   1 }, 
			{  11,   8,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  11,   3,   4,   0,   1 }, 
			{  15,   1,   0,   0,   1 }, 
			{  11,   3,   3,   0,   1 }, 
			{  11,  11,   0,   0,   1 }, 
			{  14,   2,   5,   0,   1 }, 
			{  17,   5,  68,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  11,   3,   2,   0,   1 }, 
			{  11,   8,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  11,   9,   1,   4,   1 }, 
			{  16,   1,   0,   0,   1 }, 
			{  11,   3,   2,   0,   1 }, 
			{  11,  11,   0,   0,   1 }, 
			{  14,   2,   5,   0,   1 }, 
			{  17,   5,  78,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  11,   3,   3,   0,   1 }, 
			{  11,   8,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  11,   9,   1,   4,   1 }, 
			{  16,   1,   0,   0,   1 }, 
			{  11,   3,   3,   0,   1 }, 
			{  11,  11,   0,   0,   1 }, 
			{  17,   5,  87,   0,   4 }, 
			{   0,   0,   0,   0,   1 }, 
			{   9,   1,   0,  19,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  17,   5,  91,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  11,   3,   2,   0,   1 }, 
			{  11,   8,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  17,   5,  96,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  11,   3,   3,   0,   1 }, 
			{  11,   8,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  11,   3,   4,   0,   1 }, 
			{  15,   1,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{   7,   1, 104,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  10,   6,   0,   0,   1 }, 
			{   3,   2, 345, 346,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  11,   9,   1,   1,   1 }, 
			{  16,   1,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 } 
		};

	}; template<typename SizeType>
		constexpr auto contr_object_chord_fibonacci_v1 = cctmp::U_store_T
		<
			T_contr_object_chord_fibonacci_v1<SizeType>
		>;

