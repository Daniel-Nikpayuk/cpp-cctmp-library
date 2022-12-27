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

// algorithm:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// algorithm:

	template<gkey_type, gkey_type, auto...> struct T_algorithm;

	template<auto Syn, auto Name, auto... Vs>
	nik_ce auto U_algorithm = U_store_T<T_algorithm<Syn, Name, Vs...>>;

/***********************************************************************************************************************/

// argument:

	template<auto Key, auto... Vs>       using T_algorithm_argument = T_algorithm<Shape::argument, Key, Vs...>;
	template<auto Key, auto... Vs> nik_ce auto U_algorithm_argument = U_algorithm<Shape::argument, Key, Vs...>;

// parameter:

	template<auto Key, auto... Vs>       using T_algorithm_parameter = T_algorithm<Shape::parameter, Key, Vs...>;
	template<auto Key, auto... Vs> nik_ce auto U_algorithm_parameter = U_algorithm<Shape::parameter, Key, Vs...>;

/***********************************************************************************************************************/

// names:

	struct AlgorithmName
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			dimension
		};
	};

	using GN = AlgorithmName;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parameter:

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// argument:

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

