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

// type system:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// experimental:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// logo cstart:

	// main:

		using cmethod0 = resolve_cmethod<decltype(start0), print_cmethod>;

		auto print0 = start0.template cequip<cmethod0>();

		print0.as_set(); // prints: { 0, 5, 12, 15, 20 }

