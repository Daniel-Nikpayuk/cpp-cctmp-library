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
	struct T_contr_object_chord_factorial_v4
	{
		using size_type = SizeType;

		constexpr static size_type value[][8] =
		{
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   9,   8,   5,   0,   0,   0,   0,   1 }, 
			{   8,   9,   0,   1,   0,   0,   0,   1 }, 
			{   8,   0,   0,   0,   0,   0,   0,   1 }, 
			{  14,   0,  66,   0,   0,   0,   0,   1 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   8,   9,   2,   1,   0,   0,   0,   1 }, 
			{   8,   0,   0,   0,   0,   0,   0,   1 }, 
			{   2,  10,   0,   0,   0,   0,   0,   1 }, 
			{   3,   1,   1,   0,   0,   0,   0,   1 }, 
			{   7,   9,   2,   0,   0,   0,   0,   1 }, 
			{   7,  15,   0,   0,   0,   0,   0,   1 }, 
			{  13,   3,  13,   0,   0,   0,   0,   4 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   6,   1,   0,  12,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{  13,   3,  17,   0,   0,   0,   0,   5 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   1,   0,   0,   0,   0,   1 }, 
			{   7,  12,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   3,   0,   0,   0,   0,   1 }, 
			{  11,   1,   0,   0,   0,   0,   0,   1 }, 
			{  15,   0,  59,   0,   0,   0,   0,   1 }, 
			{  13,   3,  25,   0,   0,   0,   0,   4 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   6,   1,   0,  25,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{  13,   3,  29,   0,   0,   0,   0,   5 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   1,   0,   0,   0,   0,   1 }, 
			{   7,  12,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   3,   0,   0,   0,   0,   1 }, 
			{  11,   1,   0,   0,   0,   0,   0,   1 }, 
			{  10,   8,   5,   0,   0,   0,   0,   1 }, 
			{  13,   3,  37,   0,   0,   0,   0,   3 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{   7,  13,   1,   3,   0,   0,   0,   1 }, 
			{  12,   1,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   2,   0,   0,   0,   0,   1 }, 
			{   7,  15,   0,   0,   0,   0,   0,   1 }, 
			{  13,   3,  44,   0,   0,   0,   0,   4 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   6,   1,   0,  21,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{  13,   3,  48,   0,   0,   0,   0,   5 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   1,   0,   0,   0,   0,   1 }, 
			{   7,  12,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{  13,   3,  53,   0,   0,   0,   0,   5 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   2,   0,   0,   0,   0,   1 }, 
			{   7,  12,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   3,   0,   0,   0,   0,   1 }, 
			{  11,   1,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{  13,   1,  61,   0,   0,   0,   0,   5 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   2,   0,   0,   0,   0,   1 }, 
			{   7,  12,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{   7,  13,   1,   1,   0,   0,   0,   1 }, 
			{  12,   1,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 } 
		};

	}; template<typename SizeType>
		constexpr auto contr_object_chord_factorial_v4 = cctmp::U_store_T
		<
			T_contr_object_chord_factorial_v4<SizeType>
		>;

