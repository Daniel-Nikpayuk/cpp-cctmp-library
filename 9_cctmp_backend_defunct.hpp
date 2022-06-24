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

// backend:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// overload:

	struct Overload
	{
		template<key_type Op, auto... Vs>
		nik_ces auto result = U_pack_Vs<Op, Vs...>;
	};

/***********************************************************************************************************************/

	// comparison:

	template<auto... Vs> nik_ce auto same_op			= U_pack_Vs<Overload::same, Vs...>;

	template<auto... Vs> nik_ce auto equal_op			= U_pack_Vs<Overload::equal, Vs...>;
	template<auto... Vs> nik_ce auto not_equal_op			= U_pack_Vs<Overload::not_equal, Vs...>;
	template<auto... Vs> nik_ce auto less_than_op			= U_pack_Vs<Overload::less_than, Vs...>;
	template<auto... Vs> nik_ce auto less_than_or_equal_op		= U_pack_Vs<Overload::less_than_or_equal, Vs...>;
	template<auto... Vs> nik_ce auto greater_than_op		= U_pack_Vs<Overload::greater_than, Vs...>;
	template<auto... Vs> nik_ce auto greater_than_or_equal_op	= U_pack_Vs<Overload::greater_than_or_equal, Vs...>;

	template<auto... Vs> nik_ce auto is_zero_op			= U_pack_Vs<Overload::is_zero, Vs...>;
	template<auto... Vs> nik_ce auto is_value_op			= U_pack_Vs<Overload::is_value, Vs...>;

	// logical:

	template<auto... Vs> nik_ce auto not__op			= U_pack_Vs<Overload::not_, Vs...>;
	template<auto... Vs> nik_ce auto and__op			= U_pack_Vs<Overload::and_, Vs...>;
	template<auto... Vs> nik_ce auto or__op				= U_pack_Vs<Overload::or_, Vs...>;

	// bitwise:

	template<auto... Vs> nik_ce auto upshift_op			= U_pack_Vs<Overload::upshift, Vs...>;
	template<auto... Vs> nik_ce auto downshift_op			= U_pack_Vs<Overload::downshift, Vs...>;

	// arithmetic:

	template<auto... Vs> nik_ce auto add_op				= U_pack_Vs<Overload::add, Vs...>;
	template<auto... Vs> nik_ce auto subtract_op			= U_pack_Vs<Overload::subtract, Vs...>;
	template<auto... Vs> nik_ce auto multiply_op			= U_pack_Vs<Overload::multiply, Vs...>;
	template<auto... Vs> nik_ce auto divide_op			= U_pack_Vs<Overload::divide, Vs...>;
	template<auto... Vs> nik_ce auto modulo_op			= U_pack_Vs<Overload::modulo, Vs...>;

	template<auto... Vs> nik_ce auto increment_op			= U_pack_Vs<Overload::increment, Vs...>;
	template<auto... Vs> nik_ce auto decrement_op			= U_pack_Vs<Overload::decrement, Vs...>;

	// algebraic:

	template<auto... Vs> nik_ce auto product_op			= U_pack_Vs<Overload::product, Vs...>;

	// computational:

	template<auto... Vs> nik_ce auto apply_op			= U_pack_Vs<Overload::apply, Vs...>;
	template<auto... Vs> nik_ce auto alias_op			= U_pack_Vs<Overload::alias, Vs...>;

	// functional:

	template<auto... Vs> nik_ce auto length_op			= U_pack_Vs<Overload::length, Vs...>;
	template<auto... Vs> nik_ce auto map_op				= U_pack_Vs<Overload::map, Vs...>;
	template<auto... Vs> nik_ce auto zip_op				= U_pack_Vs<Overload::zip, Vs...>;

	template<auto... Vs> nik_ce auto is_null_op			= U_pack_Vs<Overload::is_null, Vs...>;
	template<auto... Vs> nik_ce auto cons_op			= U_pack_Vs<Overload::cons, Vs...>;
	template<auto... Vs> nik_ce auto push_op			= U_pack_Vs<Overload::push, Vs...>;
	template<auto... Vs> nik_ce auto car_op				= U_pack_Vs<Overload::car, Vs...>;
	template<auto... Vs> nik_ce auto cdr_op				= U_pack_Vs<Overload::cdr, Vs...>;
	template<auto... Vs> nik_ce auto unite_op			= U_pack_Vs<Overload::unite, Vs...>;
	template<auto... Vs> nik_ce auto find_op			= U_pack_Vs<Overload::find, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

