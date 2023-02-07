/************************************************************************************************************************
**
** Copyright 2022-2023 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// compiler:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// compile:

/***********************************************************************************************************************/

	template<auto SourceCallable>
	nik_ce auto _compile()
	{
		nik_ce auto pda = T_generic_assembly_pda::parse<SourceCallable>;

		return pda;
	}

	template<auto SourceCallable>
	nik_ce auto compile = _compile<SourceCallable>();

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

