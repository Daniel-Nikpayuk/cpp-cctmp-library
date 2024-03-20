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
	struct T_contr_object_chord_factorial_v2
	{
		using size_type = SizeType;

		constexpr static size_type value[][5] =
		{
			{   0,   0,   0,   0,   1 }, 
			{  13,   2,   5,   0,   1 }, 
			{  12,   3,   0,   1,   1 }, 
			{  12,   0,   0,   0,   1 }, 
			{  18,   0,  69,   0,   1 }, 
			{   0,   0,   0,   0,   1 }, 
			{  17,   5,   7,   0,   4 }, 
			{   0,   0,   0,   0,   1 }, 
			{   9,   1,   0,  12,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  17,   5,  11,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  11,   3,   2,   0,   1 }, 
			{  11,   8,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  11,   3,   3,   0,   1 }, 
			{  15,   1,   0,   0,   1 }, 
			{  19,   0,  62,   0,   1 }, 
			{  17,   5,  19,   0,   4 }, 
			{   0,   0,   0,   0,   1 }, 
			{   9,   1,   0,  21,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  17,   5,  23,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  11,   3,   1,   0,   1 }, 
			{  11,   8,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  17,   5,  28,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  11,   3,   2,   0,   1 }, 
			{  11,   8,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  11,   3,   3,   0,   1 }, 
			{  15,   1,   0,   0,   1 }, 
			{  11,   3,   1,   0,   1 }, 
			{  11,  11,   0,   0,   1 }, 
			{  17,   5,  37,   0,   4 }, 
			{   0,   0,   0,   0,   1 }, 
			{   9,   1,   0,  25,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  17,   5,  41,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  11,   3,   2,   0,   1 }, 
			{  11,   8,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  11,   3,   3,   0,   1 }, 
			{  15,   1,   0,   0,   1 }, 
			{  11,   3,   2,   0,   1 }, 
			{  11,  11,   0,   0,   1 }, 
			{  14,   2,   5,   0,   1 }, 
			{  17,   5,  51,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  11,   3,   1,   0,   1 }, 
			{  11,   8,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  17,   5,  56,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  11,   3,   2,   0,   1 }, 
			{  11,   8,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  11,   9,   1,   3,   1 }, 
			{  16,   1,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  17,   1,  64,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  11,   3,   1,   0,   1 }, 
			{  11,   8,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  11,   9,   1,   1,   1 }, 
			{  16,   1,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 } 
		};

	}; template<typename SizeType>
		constexpr auto contr_object_chord_factorial_v2 = cctmp::U_store_T
		<
			T_contr_object_chord_factorial_v2<SizeType>
		>;

