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
	struct T_contr_object_chord_factorial_v0
	{
		using size_type = SizeType;

		constexpr static size_type value[][5] =
		{
			{   0,   0,   0,   0,   1 }, 
			{  13,   2,   5,   0,   1 }, 
			{  12,   3,   0,   1,   1 }, 
			{  12,   0,   0,   0,   1 }, 
			{  18,   0,  64,   0,   1 }, 
			{   0,   0,   0,   0,   1 }, 
			{  17,   5,   7,   0,   4 }, 
			{   0,   0,   0,   0,   1 }, 
			{   9,   1,   0,  11,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  17,   5,  11,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  11,   3,   1,   0,   1 }, 
			{  11,   8,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{   7,   5,  16,   0,   4 }, 
			{   0,   0,   0,   0,   1 }, 
			{   3,   0,  75,  76,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  11,   3,   2,   0,   1 }, 
			{  15,   1,   0,   0,   1 }, 
			{  19,   0,  57,   0,   1 }, 
			{  17,   5,  23,   0,   4 }, 
			{   0,   0,   0,   0,   1 }, 
			{   9,   1,   0,  20,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  17,   5,  27,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  11,   3,   1,   0,   1 }, 
			{  11,   8,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{   7,   5,  32,   0,   4 }, 
			{   0,   0,   0,   0,   1 }, 
			{   3,   0, 117, 118,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  11,   3,   2,   0,   1 }, 
			{  15,   1,   0,   0,   1 }, 
			{  14,   2,   5,   0,   1 }, 
			{  17,   5,  39,   0,   3 }, 
			{   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  11,   9,   1,   2,   1 }, 
			{  16,   1,   0,   0,   1 }, 
			{  17,   5,  44,   0,   4 }, 
			{   0,   0,   0,   0,   1 }, 
			{   9,   1,   0,  21,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  17,   5,  48,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  11,   3,   1,   0,   1 }, 
			{  11,   8,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  17,   5,  53,   0,   3 }, 
			{   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  11,   3,   2,   0,   1 }, 
			{  15,   1,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{   7,   1,  59,   0,   5 }, 
			{   0,   0,   0,   0,   1 }, 
			{  10,   6,   0,   0,   1 }, 
			{   3,   2, 209, 210,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 }, 
			{  11,   9,   1,   1,   1 }, 
			{  16,   1,   0,   0,   1 }, 
			{   1,   1,   0,   0,   1 } 
		};

	}; template<typename SizeType>
		constexpr auto contr_object_chord_factorial_v0 = cctmp::U_store_T
		<
			T_contr_object_chord_factorial_v0<SizeType>
		>;

