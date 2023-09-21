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

// action:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, gkey_type, auto...> struct T_chain_action;

/***********************************************************************************************************************/

// names:

	struct ChainActionName
	{
		enum : gkey_type // convenience for default params.
			{ identity = 0, id = identity, base, pose, non, arg, lup, ext, typ, dimension };

	}; using CAN = ChainActionName;

/***********************************************************************************************************************/

// notes:

	struct ChainActionNote
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			padding, rolling, winding, halting, non, arg, lup, ext, typ, dimension
		};

	}; using CAT = ChainActionNote;

/***********************************************************************************************************************/

// instructions:

	struct ChainActionInstr
	{
		enum : gkey_type { cond = 0, name, note, dimension };
		enum : gkey_type { pos0 = 0, pos1, pos2, pos3, pos4, pos5 };

	}; using CAI = ChainActionInstr;

/***********************************************************************************************************************/

// offset:

	using ChainActionOffset = PraxisActionOffset;
	using CAO               = ChainActionOffset;

/***********************************************************************************************************************/

// base:

	// id:

		template<auto... filler>
		struct T_chain_action<CAN::base, CAT::id, filler...>
		{
			nik_ces gindex_type offset[] = {0, 1};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins) { contr->add_instr(CN::id, CT::id); }
		};

	// padding:

		template<auto... filler>
		struct T_chain_action<CAN::base, CAT::padding, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::pad, CT::select, ins[CAI::pos0]);
				contr->add_instr(CN::pad, CT::push);
			}
		};

	// halting:

		template<auto... filler>
		struct T_chain_action<CAN::base, CAT::halting, filler...>
		{
			nik_ces gindex_type offset[] = {0, 1};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins) { contr->add_instr(CN::halt, ins[CAI::pos0]); }
		};

/***********************************************************************************************************************/

// pose:

	// halting:

		template<auto... filler>
		struct T_chain_action<CAN::pose, CAT::halting, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::copy, CT::select, ins[CAI::pos0]);
				contr->add_instr(CN::pose, CT::tail);
			}
		};

/***********************************************************************************************************************/

// non:

	// non: (not applicable)

	// arg: (id arg; allows the user to conceptualize composition before application)

		template<auto... filler>
		struct T_chain_action<CAN::non, CAT::arg, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::copy, CT::select, ins[CAI::pos0]);
				contr->add_instr(CN::copy, CT::push);
			}
		};

	// lup: (id lup; allows the user to conceptualize composition before application)

		template<auto... filler>
		struct T_chain_action<CAN::non, CAT::lup, filler...>
		{
			nik_ces gindex_type offset[] = {0, 1};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
				{ contr->add_instr(CN::lup, CT::push, ins[CAI::pos0]); }
		};

	// ext: (id ext; allows the user to conceptualize composition before application)

		template<auto... filler>
		struct T_chain_action<CAN::non, CAT::ext, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::pose, CT::select, ins[CAI::pos0]);
				contr->add_instr(CN::ext, CT::push, ins[CAI::pos1], ins[CAI::pos2]);
			}
		};

	// typ: (id typ; allows the user to conceptualize composition before application)

		template<auto... filler>
		struct T_chain_action<CAN::non, CAT::typ, filler...>
		{
			nik_ces gindex_type offset[] = {0, 1};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
				{ contr->add_instr(CN::typ, CT::push, ins[CAI::pos0]); }
		};

/***********************************************************************************************************************/

// arg:

	// non: (composer only, add instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::non, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::copy, CT::select, ins[CAI::pos0]);
				contr->add_instr(CN::copy, CT::pull);
			}
		};

	// arg:

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::arg, filler...>
		{
			nik_ces gindex_type offset[] = {0, 4};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::copy, CT::select, ins[CAI::pos0]);
				contr->add_instr(CN::copy, CT::pull);
				contr->add_instr(CN::copy, CT::select, ins[CAI::pos1]);
				contr->add_instr(CN::copy, CT::apply);
			}
		};

	// lup:

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::lup, filler...>
		{
			nik_ces gindex_type offset[] = {0, 3};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::copy, CT::select, ins[CAI::pos0]);
				contr->add_instr(CN::copy, CT::pull);
				contr->add_instr(CN::lup, CT::apply, ins[CAI::pos1]);
			}
		};

	// ext:

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::ext, filler...>
		{
			nik_ces gindex_type offset[] = {0, 4};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::copy, CT::select, ins[CAI::pos0]);
				contr->add_instr(CN::copy, CT::pull);
				contr->add_instr(CN::pose, CT::select, ins[CAI::pos1]);
				contr->add_instr(CN::ext, CT::apply, ins[CAI::pos2], ins[CAI::pos3]);
			}
		};

	// typ:

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::typ, filler...>
		{
			nik_ces gindex_type offset[] = {0, 3};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::copy, CT::select, ins[CAI::pos0]);
				contr->add_instr(CN::copy, CT::pull);
				contr->add_instr(CN::typ, CT::apply, ins[CAI::pos1]);
			}
		};

/***********************************************************************************************************************/

// l(ook)up:

	// non: (composer only, add instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::lup, CAT::non, filler...>
		{
			nik_ces gindex_type offset[] = {0, 1};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
				{ contr->add_instr(CN::lup, CT::pull, ins[CAI::pos0]); }
		};

	// arg:

		template<auto... filler>
		struct T_chain_action<CAN::lup, CAT::arg, filler...>
		{
			nik_ces gindex_type offset[] = {0, 3};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::lup, CT::pull, ins[CAI::pos0]);
				contr->add_instr(CN::copy, CT::select, ins[CAI::pos1]);
				contr->add_instr(CN::copy, CT::apply);
			}
		};

	// lup:

		template<auto... filler>
		struct T_chain_action<CAN::lup, CAT::lup, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::lup, CT::pull, ins[CAI::pos0]);
				contr->add_instr(CN::lup, CT::apply, ins[CAI::pos1]);
			}
		};

	// ext:

		template<auto... filler>
		struct T_chain_action<CAN::lup, CAT::ext, filler...>
		{
			nik_ces gindex_type offset[] = {0, 3};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::lup, CT::pull, ins[CAI::pos0]);
				contr->add_instr(CN::pose, CT::select, ins[CAI::pos1]);
				contr->add_instr(CN::ext, CT::apply, ins[CAI::pos2], ins[CAI::pos3]);
			}
		};

	// typ:

		template<auto... filler>
		struct T_chain_action<CAN::lup, CAT::typ, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::lup, CT::pull, ins[CAI::pos0]);
				contr->add_instr(CN::typ, CT::apply, ins[CAI::pos1]);
			}
		};

/***********************************************************************************************************************/

// ext(ended):

	// non: (composer only, add instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::ext, CAT::non, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::pose, CT::select, ins[CAI::pos0]);
				contr->add_instr(CN::ext, CT::pull, ins[CAI::pos1], ins[CAI::pos2]);
			}
		};

	// arg:

		template<auto... filler>
		struct T_chain_action<CAN::ext, CAT::arg, filler...>
		{
			nik_ces gindex_type offset[] = {0, 4};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::pose, CT::select, ins[CAI::pos0]);
				contr->add_instr(CN::ext, CT::pull, ins[CAI::pos1], ins[CAI::pos2]);
				contr->add_instr(CN::copy, CT::select, ins[CAI::pos3]);
				contr->add_instr(CN::copy, CT::apply);
			}
		};

	// lup:

		template<auto... filler>
		struct T_chain_action<CAN::ext, CAT::lup, filler...>
		{
			nik_ces gindex_type offset[] = {0, 3};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::pose, CT::select, ins[CAI::pos0]);
				contr->add_instr(CN::ext, CT::pull, ins[CAI::pos1], ins[CAI::pos2]);
				contr->add_instr(CN::lup, CT::apply, ins[CAI::pos3]);
			}
		};

	// ext:

		template<auto... filler>
		struct T_chain_action<CAN::ext, CAT::ext, filler...>
		{
			nik_ces gindex_type offset[] = {0, 4};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::pose, CT::select, ins[CAI::pos0]);
				contr->add_instr(CN::ext, CT::pull, ins[CAI::pos1], ins[CAI::pos2]);
				contr->add_instr(CN::pose, CT::select, ins[CAI::pos3]);
				contr->add_instr(CN::ext, CT::apply, ins[CAI::pos4], ins[CAI::pos5]);
			}
		};

	// typ:

		template<auto... filler>
		struct T_chain_action<CAN::ext, CAT::typ, filler...>
		{
			nik_ces gindex_type offset[] = {0, 3};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::pose, CT::select, ins[CAI::pos0]);
				contr->add_instr(CN::ext, CT::pull, ins[CAI::pos1], ins[CAI::pos2]);
				contr->add_instr(CN::typ, CT::apply, ins[CAI::pos3]);
			}
		};

/***********************************************************************************************************************/

// typ(es):

	// non: (composer only, add instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::typ, CAT::non, filler...>
		{
			nik_ces gindex_type offset[] = {0, 1};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
				{ contr->add_instr(CN::typ, CT::pull, ins[CAI::pos0]); }
		};

	// arg:

		template<auto... filler>
		struct T_chain_action<CAN::typ, CAT::arg, filler...>
		{
			nik_ces gindex_type offset[] = {0, 3};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::typ, CT::pull, ins[CAI::pos0]);
				contr->add_instr(CN::copy, CT::select, ins[CAI::pos1]);
				contr->add_instr(CN::copy, CT::apply);
			}
		};

	// lup:

		template<auto... filler>
		struct T_chain_action<CAN::typ, CAT::lup, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::typ, CT::pull, ins[CAI::pos0]);
				contr->add_instr(CN::lup, CT::apply, ins[CAI::pos1]);
			}
		};

	// ext:

		template<auto... filler>
		struct T_chain_action<CAN::typ, CAT::ext, filler...>
		{
			nik_ces gindex_type offset[] = {0, 3};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::typ, CT::pull, ins[CAI::pos0]);
				contr->add_instr(CN::pose, CT::select, ins[CAI::pos1]);
				contr->add_instr(CN::ext, CT::apply, ins[CAI::pos2], ins[CAI::pos3]);
			}
		};

	// typ:

		template<auto... filler>
		struct T_chain_action<CAN::typ, CAT::typ, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			template<typename Contr, typename Ins>
			nik_ces void result(Contr *contr, Ins & ins)
			{
				contr->add_instr(CN::typ, CT::pull, ins[CAI::pos0]);
				contr->add_instr(CN::typ, CT::apply, ins[CAI::pos1]);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

