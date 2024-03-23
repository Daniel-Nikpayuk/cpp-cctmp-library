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
	struct T_contr_object_chord_void_effects_v0
	{
		using size_type = SizeType;

		constexpr static size_type value[][8] =
		{
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   9,   8,   5,   0,   0,   0,   0,   1 }, 
			{   8,   9,   0,   1,   0,   0,   0,   1 }, 
			{   8,   0,   0,   0,   0,   0,   0,   1 }, 
			{  14,   0,  35,   0,   0,   0,   0,   1 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{  13,   3,   7,   0,   0,   0,   0,   4 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   6,   1,   0,  24,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{  13,   3,  11,   0,   0,   0,   0,   5 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   2,   0,   0,   0,   0,   1 }, 
			{   7,  12,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   3,   0,   0,   0,   0,   1 }, 
			{  11,   1,   0,   0,   0,   0,   0,   1 }, 
			{  13,   3,  18,   0,   0,   0,   0,   4 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   6,   1,   0,   5,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{  13,   3,  22,   1,   0,   0,   0,   5 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   1,   0,   0,   0,   0,   1 }, 
			{   7,  12,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{  13,   3,  27,   0,   0,   0,   0,   3 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{  13,   3,  30,   0,   0,   0,   0,   5 }, 
			{   0,   0,   0,   0,   0,   0,   0,   1 }, 
			{   7,   9,   1,   0,   0,   0,   0,   1 }, 
			{   7,  12,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 }, 
			{   7,  13,   1,   1,   0,   0,   0,   1 }, 
			{  12,   3,   0,   0,   0,   0,   0,   1 }, 
			{   1,   1,   0,   0,   0,   0,   0,   1 } 
		};

	}; template<typename SizeType>
		constexpr auto contr_object_chord_void_effects_v0 = cctmp::U_store_T
		<
			T_contr_object_chord_void_effects_v0<SizeType>
		>;

