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

// lookup action:

namespace machine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, gkey_type, auto...> struct T_lookup_action;

	// syntactic sugar:

		template<auto name, auto note, typename... Ts>
		nik_ce auto lookup_action(Ts... vs) // requires template deduction <>:
			{ return T_lookup_action<name, note>::template result<>(vs...); }

		template<auto name, auto note>
		nik_ce auto lookup_offset = T_lookup_action<name, note>::offset;

/***********************************************************************************************************************/

// names:

	struct LookupActionName
	{
		enum : gkey_type // convenience for default params.
			{ identity = 0, id = identity, find, dimension };

	}; using LAN = LookupActionName;

/***********************************************************************************************************************/

// notes:

	struct LookupActionNote
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			dimension
		};

	}; using LAT = LookupActionNote;

/***********************************************************************************************************************/

// find:

	// id:

		template<auto... filler>
		struct T_lookup_action<LAN::find, LAT::id, filler...>
		{
			nik_ces gindex_type offset = 6 * machine_offset<MAN::set, MAT::inc>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex begin, cindex end)
			{
				cindex loop = contr->initial;
				cindex halt = loop + 4;

				machine_action<MAN::set, MAT::inc>(contr, LN::id       , LT::id    );
				machine_action<MAN::set, MAT::inc>(contr, LN::jump     , LT::empty , 1 , halt        );
				machine_action<MAN::set, MAT::inc>(contr, LN::contains , LT::id    , 1 , begin , end );
				machine_action<MAN::set, MAT::inc>(contr, LN::jump     , LT::loop  , 1 , loop        );
				machine_action<MAN::set, MAT::inc>(contr, LN::halt     , LT::map   );
				machine_action<MAN::set, MAT::inc>(contr, LN::halt     , LT::empty );
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

