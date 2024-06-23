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

// container:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// environment:

/***********************************************************************************************************************/

// at:

	template<auto n, auto... filler>
	struct T_at<n, filler...>
	{
		template<typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto p0 = left_  <n, U_store_T<Ts>...>;
			nik_ce auto p1 = right_ <n, U_store_T<Ts>...>;

			return T_at<p0, p1>::result(vs...);
		}
	};

/***********************************************************************************************************************/

// lambda tuple:

	struct LambdaTuple
	{
		template<typename... Ts>
		nik_ces auto make(Ts... vs)
			{ return [vs...](auto U){ return T_restore_T<decltype(U)>::template result<Ts...>(vs...); }; }

		template<        typename LT> nik_ces auto empty(LT lt) { return lt(U_empty); }
		template<auto n, typename LT> nik_ces auto value(LT lt) { return lt(U_at<n>); }
	};

/***********************************************************************************************************************/

// binding:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

