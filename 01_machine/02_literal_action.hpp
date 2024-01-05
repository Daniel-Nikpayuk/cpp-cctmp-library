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

// literal action:

namespace machine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, gkey_type, auto...> struct T_literal_action;

	// syntactic sugar:

		template<auto name, auto note, typename... Ts>
		nik_ce auto literal_action(Ts... vs) // requires template deduction <>:
			{ return T_literal_action<name, note>::template result<>(vs...); }

		template<auto name, auto note>
		nik_ce auto literal_offset = T_literal_action<name, note>::offset;

/***********************************************************************************************************************/

// names:

	struct LiteralActionName
	{
		enum : gkey_type // convenience for default params.
			{ identity = 0, id = identity, resolve, dimension };

	}; using LAN = LiteralActionName;

/***********************************************************************************************************************/

// notes:

	struct LiteralActionNote
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			dimension
		};

	}; using LAT = LiteralActionNote;

/***********************************************************************************************************************/

// resolve:

	// id:

		template<auto... filler>
		struct T_literal_action<LAN::resolve, LAT::id, filler...>
		{
			nik_ces gindex_type offset = 3 * machine_offset<MAN::push, MAT::instr>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex begin, cindex end)
			{
				machine_action<MAN::push, MAT::instr>(contr, LN::id, LT::id);
				machine_action<MAN::push, MAT::instr>(contr, LN::resolve, note, begin, end);
				machine_action<MAN::push, MAT::instr>(contr, LN::halt, LT::first);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

