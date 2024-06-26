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

// inventory:

/***********************************************************************************************************************/

// different:

	// v0:

		constexpr auto _chord_different_v0()
		{
			return cctmp::source
			(
				"main out in end in1                              ;"

				"vars:                                            ;"
				"  declare diff                                   ;"

				"defs:                                            ;"
				"  diff # find[2]{not_equal|first @ @|} [> [,) [) ;"

				"body:                                            ;"
				"  . = diff !out in end in1                       ;"
				"  return _                                       ;"

				, cctmp::binding( "not_equal" , cctmp::_not_equal_   )
				, cctmp::binding( "*"         , cctmp::_dereference_ )
				, cctmp::binding( "first"     , cctmp::_first_       )
				, cctmp::binding( "@"         , cctmp::_id_          )
			);
		}

