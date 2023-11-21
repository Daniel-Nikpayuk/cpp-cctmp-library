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

// cycle action:

namespace machine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, gkey_type, auto...> struct T_cycle_action;

	// syntactic sugar:

		template<auto name, auto note, typename... Ts>
		nik_ce auto cycle_action(Ts... vs) // requires template deduction <>:
			{ return T_cycle_action<name, note>::template result<>(vs...); }

		template<auto name, auto note>
		nik_ce auto cycle_offset = T_cycle_action<name, note>::offset;

/***********************************************************************************************************************/

// names:

	struct CycleActionName
	{
		enum : gkey_type // convenience for default params.
			{ identity = 0, id = identity, base, next, loop, dimension };

	}; using YAN = CycleActionName;

/***********************************************************************************************************************/

// notes:

	struct CycleActionNote
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			halting, sarg, env, dimension
		};

	}; using YAT = CycleActionNote;

/***********************************************************************************************************************/

// base:

	// id:

		template<auto... filler>
		struct T_cycle_action<YAN::base, YAT::id, filler...>
		{
			nik_ces gindex_type offset = machine_offset<MAN::set, MAT::inc>;

			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::set, MAT::inc>(contr, YN::id, YT::id); }
		};

	// halting:

		template<auto... filler>
		struct T_cycle_action<YAN::base, YAT::halting, filler...>
		{
			nik_ces gindex_type offset = machine_offset<MAN::set, MAT::inc>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
				{ machine_action<MAN::set, MAT::inc>(contr, YN::halt, note); }
		};

/***********************************************************************************************************************/

// next:

	// sarg:

		template<auto... filler>
		struct T_cycle_action<YAN::next, YAT::sarg, filler...>
		{
			nik_ces gindex_type offset = 4 * machine_offset<MAN::set, MAT::inc>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at, cindex arg_at, cindex note)
			{
				machine_action<MAN::set, MAT::inc>(contr, YN::next , YT::select , 1 , func_at );
				machine_action<MAN::set, MAT::inc>(contr, YN::next , YT::car    , 1 );
				machine_action<MAN::set, MAT::inc>(contr, YN::next , YT::select , 1 , arg_at );
				machine_action<MAN::set, MAT::inc>(contr, YN::next , note       , 1 ); // YT::effect, YT::assign.
			}
		};

	// env:

		template<auto... filler>
		struct T_cycle_action<YAN::next, YAT::env, filler...>
		{
			nik_ces gindex_type offset = 4 * machine_offset<MAN::set, MAT::inc>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex subindex, cindex list_str, cindex arg_at, cindex note)
			{
				machine_action<MAN::set, MAT::inc>(contr, YN::lookup , YT::car    , 1 , subindex , list_str );
				machine_action<MAN::set, MAT::inc>(contr, YN::next   , YT::car    , 1 );
				machine_action<MAN::set, MAT::inc>(contr, YN::next   , YT::select , 1 , arg_at );
				machine_action<MAN::set, MAT::inc>(contr, YN::next   , note       , 1 ); // YT::effect, YT::assign.
			}
		};

/***********************************************************************************************************************/

// loop:

	// id:

		template<auto... filler>
		struct T_cycle_action<YAN::loop, YAT::id, filler...>
		{
			nik_ces gindex_type offset = 3 * machine_offset<MAN::set, MAT::inc>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex car_start, cindex cdr_start, cindex list_str)
			{
				machine_action<MAN::set, MAT::inc>(contr, YN::lookup , YT::car    , 1 , car_start , list_str );
				machine_action<MAN::set, MAT::inc>(contr, YN::lookup , YT::cdr    , 1 , cdr_start , list_str );
				machine_action<MAN::set, MAT::inc>(contr, YN::loop   , YT::effect , 1 );
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

