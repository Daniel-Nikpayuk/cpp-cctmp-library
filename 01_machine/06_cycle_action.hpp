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

// instructions:

//	struct CycleActionInstr
//	{
//		enum : gkey_type { pos0 = 0, pos1, pos2, pos3, dimension };
//		enum : gkey_type { name = 0, note };

//	}; using YAI = CycleActionInstr;

/***********************************************************************************************************************/

// offset:

//	using CycleActionOffset = cctmp::ActionOffset;
//	using YAO               = cctmp::ActionOffset;

/***********************************************************************************************************************/

// size:

//	using T_cycle_contr_size = cctmp::T_contr_size<T_cycle_action, CAI, CAO>;

/***********************************************************************************************************************/

// base:

	// id:

		template<auto... filler>
		struct T_cycle_action<YAN::base, YAT::id, filler...>
		{
			nik_ces gindex_type offset[] = {0, 1};

			template<typename Contr>
			nik_ces void result(Contr *contr) { contr->set_inc_instr(YN::id, YT::id); }
		};

	// halting:

		template<auto... filler>
		struct T_cycle_action<YAN::base, YAT::halting, filler...>
		{
			nik_ces gindex_type offset[] = {0, 1};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note) { contr->set_inc_instr(YN::halt, note); }
		};

/***********************************************************************************************************************/

// next:

	// sarg:

		template<auto... filler>
		struct T_cycle_action<YAN::next, YAT::sarg, filler...>
		{
			nik_ces gindex_type offset[] = {0, 4};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at, cindex arg_at, cindex note)
			{
				contr->set_inc_instr( YN::next , YT::select , 1 , func_at );
				contr->set_inc_instr( YN::next , YT::car    , 1 );
				contr->set_inc_instr( YN::next , YT::select , 1 , arg_at );
				contr->set_inc_instr( YN::next , note       , 1 ); // YT::effect, YT::assign.
			}
		};

	// env:

		template<auto... filler>
		struct T_cycle_action<YAN::next, YAT::env, filler...>
		{
			nik_ces gindex_type offset[] = {0, 4};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex subindex, cindex list_str, cindex arg_at, cindex note)
			{
				contr->set_inc_instr( YN::lookup , YT::car    , 1 , subindex , list_str );
				contr->set_inc_instr( YN::next   , YT::car    , 1 );
				contr->set_inc_instr( YN::next   , YT::select , 1 , arg_at );
				contr->set_inc_instr( YN::next   , note       , 1 ); // YT::effect, YT::assign.
			}
		};

/***********************************************************************************************************************/

// loop:

	// id:

		template<auto... filler>
		struct T_cycle_action<YAN::loop, YAT::id, filler...>
		{
			nik_ces gindex_type offset[] = {0, 4};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex car_start, cindex cdr_start, cindex list_str)
			{
				contr->set_inc_instr( YN::lookup , YT::car    , 1 , car_start , list_str );
				contr->set_inc_instr( YN::lookup , YT::cdr    , 1 , cdr_start , list_str );
				contr->set_inc_instr( YN::loop   , YT::effect , 1 );
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

