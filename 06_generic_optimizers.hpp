/************************************************************************************************************************
**
** Copyright 2022 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// generic optimizers:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// loop (not yet implemented):

//	template<auto p, auto f>
//	struct T_lift<FN::loop, p, f>
//	{
//		template<auto pass, typename... Ts>
//		nik_ces auto result(Ts... vs)
//		{
//			auto vals = tuple(vs...);

//			while (p(vals)) f(vals); // f updates vals as a side effect.

//			return tuple_apply<pass>(vals); // tuple apply returns vals back into
							// a variadic pack, and applies pass
							// as a continuation passing function.
//		}
//	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

