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

// argument:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// empty:

	struct T_empty
	{
		template<typename... Ts>
		nik_ces auto result(Ts... vs) { return (sizeof...(Ts) == 0); }

	}; nik_ce auto U_empty = U_store_T<T_empty>;

/***********************************************************************************************************************/

// at:

	template<auto...> struct T_at;

	template
	<
		         auto... LUs, nik_vp(p0)(T_pack_Vs<    LUs...>*),
		auto RU, auto... RUs, nik_vp(p1)(T_pack_Vs<RU, RUs...>*),
		auto... filler
	>
	struct T_at<p0, p1, filler...>
	{
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<RU> rv, T_store_U<RUs>... rvs)
			{ return rv; }

	}; template<auto... Vs>
		nik_ce auto U_at = U_store_T<T_at<Vs...>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

