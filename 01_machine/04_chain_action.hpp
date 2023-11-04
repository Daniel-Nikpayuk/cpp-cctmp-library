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

// chain action:

namespace machine {

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
			{ identity = 0, id = identity, base, drop, non, arg, list, lookup, in_types, dimension };

	}; using CAN = ChainActionName;

/***********************************************************************************************************************/

// notes:

	struct ChainActionNote
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			halting, non, arg, list, lookup, in_types, dimension
		};

	}; using CAT = ChainActionNote;

/***********************************************************************************************************************/

// instructions:

//	struct ChainActionInstr
//	{
//		enum : gkey_type { pos0 = 0, pos1, pos2, pos3, dimension };
//		enum : gkey_type { name = 0, note };

//	}; using CAI = ChainActionInstr;

/***********************************************************************************************************************/

// offset:

//	using ChainActionOffset = cctmp::ActionOffset;
//	using CAO               = cctmp::ActionOffset;

/***********************************************************************************************************************/

// size:

//	using T_chain_contr_size = cctmp::T_contr_size<T_chain_action, CAI, CAO>;

/***********************************************************************************************************************/

// base:

	// id:

		template<auto... filler>
		struct T_chain_action<CAN::base, CAT::id, filler...>
		{
			nik_ces gindex_type offset[] = {0, 1};

			template<typename Contr>
			nik_ces void result(Contr *contr) { contr->set_inc_instr(CN::id, CT::id); }
		};

	// halting:

		template<auto... filler>
		struct T_chain_action<CAN::base, CAT::halting, filler...>
		{
			nik_ces gindex_type offset[] = {0, 1};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note) { contr->set_inc_instr(CN::halt, note); }
		};

/***********************************************************************************************************************/

// drop:

	// halting:

		template<auto... filler>
		struct T_chain_action<CAN::drop, CAT::halting, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_end)
			{
				contr->set_inc_instr(CN::copy, CT::select, 1, arg_end);
				contr->set_inc_instr(CN::drop, CT::front);
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

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_at)
			{
				contr->set_inc_instr(CN::copy, CT::select, 1, arg_at);
				contr->set_inc_instr(CN::copy, CT::push);
			}
		};

	// list: (id list; allows the user to conceptualize composition before application)

		template<auto... filler>
		struct T_chain_action<CAN::non, CAT::list, filler...>
		{
			nik_ces gindex_type offset[] = {0, 1};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex list_at)
				{ contr->set_inc_instr(CN::list, CT::push, 1, list_at); }
		};

	// lookup: (id lookup; allows the user to conceptualize composition before application)

		template<auto... filler>
		struct T_chain_action<CAN::non, CAT::lookup, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex env, cindex subindex, cindex list_str)
			{
				contr->set_inc_instr(CN::list, CT::select, 1, env);
				contr->set_inc_instr(CN::lookup, CT::push, 1, subindex, list_str);
			}
		};

	// in types: (not currently relevant)

/***********************************************************************************************************************/

// arg:

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::non, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at)
			{
				contr->set_inc_instr(CN::copy, CT::select, 1, func_at);
				contr->set_inc_instr(CN::copy, CT::pull);
			}
		};

	// arg:

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::arg, filler...>
		{
			nik_ces gindex_type offset[] = {0, 4};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at, cindex arg_at)
			{
				contr->set_inc_instr(CN::copy, CT::select, 1, func_at);
				contr->set_inc_instr(CN::copy, CT::pull);
				contr->set_inc_instr(CN::copy, CT::select, 1, arg_at);
				contr->set_inc_instr(CN::copy, CT::apply);
			}
		};

	// list:

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::list, filler...>
		{
			nik_ces gindex_type offset[] = {0, 3};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at, cindex arg_at)
			{
				contr->set_inc_instr(CN::copy, CT::select, 1, func_at);
				contr->set_inc_instr(CN::copy, CT::pull);
				contr->set_inc_instr(CN::list, CT::apply, 1, arg_at);
			}
		};

	// lookup:

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::lookup, filler...>
		{
			nik_ces gindex_type offset[] = {0, 4};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at, cindex env, cindex subindex, cindex list_str)
			{
				contr->set_inc_instr(CN::copy   , CT::select , 1 , func_at);
				contr->set_inc_instr(CN::copy   , CT::pull);
				contr->set_inc_instr(CN::list   , CT::select , 1 , env);
				contr->set_inc_instr(CN::lookup , CT::apply  , 1 , subindex, list_str);
			}
		};

	// in types: (not currently relevant)

/***********************************************************************************************************************/

// list:

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::list, CAT::non, filler...>
		{
			nik_ces gindex_type offset[] = {0, 1};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at)
				{ contr->set_inc_instr(CN::list, CT::pull, 1, func_at); }
		};

	// arg:

		template<auto... filler>
		struct T_chain_action<CAN::list, CAT::arg, filler...>
		{
			nik_ces gindex_type offset[] = {0, 3};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at, cindex arg_at)
			{
				contr->set_inc_instr(CN::list, CT::pull, 1, func_at);
				contr->set_inc_instr(CN::copy, CT::select, 1, arg_at);
				contr->set_inc_instr(CN::copy, CT::apply);
			}
		};

	// list:

		template<auto... filler>
		struct T_chain_action<CAN::list, CAT::list, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at, cindex arg_at)
			{
				contr->set_inc_instr(CN::list, CT::pull, 1, func_at);
				contr->set_inc_instr(CN::list, CT::apply, 1, arg_at);
			}
		};

	// lookup:

		template<auto... filler>
		struct T_chain_action<CAN::list, CAT::lookup, filler...>
		{
			nik_ces gindex_type offset[] = {0, 3};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at, cindex env, cindex subindex, cindex list_str)
			{
				contr->set_inc_instr(CN::list, CT::pull, 1, func_at);
				contr->set_inc_instr(CN::list, CT::select, 1, env);
				contr->set_inc_instr(CN::lookup, CT::apply, 1, subindex, list_str);
			}
		};

	// in types: (not currently relevant)

/***********************************************************************************************************************/

// lookup:

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::lookup, CAT::non, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex env, cindex subindex, cindex list_str)
			{
				contr->set_inc_instr(CN::list, CT::select, 1, env);
				contr->set_inc_instr(CN::lookup, CT::pull, 1, subindex, list_str);
			}
		};

	// arg:

		template<auto... filler>
		struct T_chain_action<CAN::lookup, CAT::arg, filler...>
		{
			nik_ces gindex_type offset[] = {0, 4};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex env, cindex subindex, cindex list_str, cindex arg_at)
			{
				contr->set_inc_instr(CN::list, CT::select, 1, env);
				contr->set_inc_instr(CN::lookup, CT::pull, 1, subindex, list_str);
				contr->set_inc_instr(CN::copy, CT::select, 1, arg_at);
				contr->set_inc_instr(CN::copy, CT::apply);
			}
		};

	// list:

		template<auto... filler>
		struct T_chain_action<CAN::lookup, CAT::list, filler...>
		{
			nik_ces gindex_type offset[] = {0, 3};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex env, cindex subindex, cindex list_str, cindex arg_at)
			{
				contr->set_inc_instr(CN::list, CT::select, 1, env);
				contr->set_inc_instr(CN::lookup, CT::pull, 1, subindex, list_str);
				contr->set_inc_instr(CN::list, CT::apply, 1, arg_at);
			}
		};

	// lookup:

		template<auto... filler>
		struct T_chain_action<CAN::lookup, CAT::lookup, filler...>
		{
			nik_ces gindex_type offset[] = {0, 4};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr,
				cindex func_env, cindex func_index, cindex func_str,
					cindex arg_env, cindex arg_index, cindex arg_str)
			{
				contr->set_inc_instr(CN::list, CT::select, 1, func_env);
				contr->set_inc_instr(CN::lookup, CT::pull, 1, func_index, func_str);
				contr->set_inc_instr(CN::list, CT::select, 1, arg_env);
				contr->set_inc_instr(CN::lookup, CT::apply, 1, arg_index, arg_str);
			}
		};

	// in types: (not currently relevant)

/***********************************************************************************************************************/

// in types:

	// non: (not currently relevant)

	// arg: (not currently relevant)

	// list: (not currently relevant)

	// lookup: (not currently relevant)

	// in types: (not currently relevant)

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

