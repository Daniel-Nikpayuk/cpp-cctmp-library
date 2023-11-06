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

	// syntactic sugar:

		template<auto name, auto note, typename... Ts>
		nik_ce auto chain_action(Ts... vs) // requires template deduction <>:
			{ return T_chain_action<name, note>::template result<>(vs...); }

/***********************************************************************************************************************/

// names:

	struct ChainActionName
	{
		enum : gkey_type // convenience for default params.
		{
			identity = 0, id = identity,
			generic, begin, arg, list, recurse, lookup, non, end,
			dimension
		};

	}; using CAN = ChainActionName;

/***********************************************************************************************************************/

// notes:

	struct ChainActionNote
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			arg, list, recurse, lookup, non, dimension
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

// generic:

	// arg:

		template<auto... filler>
		struct T_chain_action<CAN::generic, CAT::arg, filler...>
		{
			nik_ces gindex_type offset = 2;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex arg_at)
			{
				contr->set_inc_instr(CN::copy, CT::select, 1, arg_at);
				contr->set_inc_instr(CN::copy, note);
			}

		}; template<typename... Ts>
			nik_ce auto chain_action_arg(Ts... vs)
				{ return chain_action<CAN::generic, CAT::arg>(vs...); }

	// list:

		template<auto... filler>
		struct T_chain_action<CAN::generic, CAT::list, filler...>
		{
			nik_ces gindex_type offset = 1;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex list_at)
				{ contr->set_inc_instr(CN::list, note, 1, list_at); }

		}; template<typename... Ts>
			nik_ce auto chain_action_list(Ts... vs)
				{ return chain_action<CAN::generic, CAT::list>(vs...); }

	// recurse:

		template<auto... filler>
		struct T_chain_action<CAN::generic, CAT::recurse, filler...>
		{
			nik_ces gindex_type offset = 1;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
				{ contr->set_inc_instr(CN::list, note, 1, contr->rec_at); }

		}; template<typename... Ts>
			nik_ce auto chain_action_recurse(Ts... vs)
				{ return chain_action<CAN::generic, CAT::recurse>(vs...); }

	// lookup:

		template<auto... filler>
		struct T_chain_action<CAN::generic, CAT::lookup, filler...>
		{
			nik_ces gindex_type offset = 2 + T_lookup_action<LAN::find, LAT::id>::offset;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex begin, cindex end)
			{
				contr->set_inc_instr(CN::list, CT::select, 1, contr->env_at);

				contr->push_machine(CN::lookup, note, contr->str_at);
				lookup_action<LAN::find, LAT::id>(contr, begin, end);
				contr->pop_machine();
			}

		}; template<typename... Ts>
			nik_ce auto chain_action_lookup(Ts... vs)
				{ return chain_action<CAN::generic, CAT::lookup>(vs...); }

	// offset:

		template<auto... notes>
		nik_ce auto chain_action_offset = (... + T_chain_action<CAN::generic, notes>::offset);

/***********************************************************************************************************************/

// begin:

	// id:

		template<auto... filler>
		struct T_chain_action<CAN::begin, CAT::id, filler...>
		{
			nik_ces gindex_type offset = 1;

			template<typename Contr>
			nik_ces void result(Contr *contr) { contr->set_inc_instr(CN::id, CT::id); }
		};

/***********************************************************************************************************************/

// arg:

	// arg:

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::arg, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::arg, CAT::arg>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at, cindex arg_at)
			{
				chain_action_arg(contr, CT::pull, func_at);
				chain_action_arg(contr, CT::apply, arg_at);
			}
		};

	// list:

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::list, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::arg, CAT::list>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at, cindex arg_at)
			{
				chain_action_arg(contr, CT::pull, func_at);
				chain_action_list(contr, CT::apply, arg_at);
			}
		};

	// recurse:

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::recurse, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::arg, CAT::recurse>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at)
			{
				chain_action_arg(contr, CT::pull, func_at);
				chain_action_recurse(contr, CT::apply);
			}
		};

	// lookup:

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::lookup, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::arg, CAT::lookup>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at, cindex begin, cindex end)
			{
				chain_action_arg(contr, CT::pull, func_at);
				chain_action_lookup(contr, CT::apply, begin, end);
			}
		};

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::non, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::arg>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at)
				{ chain_action_arg(contr, CT::pull, func_at); }
		};

/***********************************************************************************************************************/

// list:

	// arg:

		template<auto... filler>
		struct T_chain_action<CAN::list, CAT::arg, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::list, CAT::arg>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at, cindex arg_at)
			{
				chain_action_list(contr, CT::pull, func_at);
				chain_action_arg(contr, CT::apply, arg_at);
			}
		};

	// list:

		template<auto... filler>
		struct T_chain_action<CAN::list, CAT::list, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::list, CAT::list>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at, cindex arg_at)
			{
				chain_action_list(contr, CT::pull, func_at);
				chain_action_list(contr, CT::apply, arg_at);
			}
		};

	// recurse:

		template<auto... filler>
		struct T_chain_action<CAN::list, CAT::recurse, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::list, CAT::recurse>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at)
			{
				chain_action_list(contr, CT::pull, func_at);
				chain_action_recurse(contr, CT::apply);
			}
		};

	// lookup:

		template<auto... filler>
		struct T_chain_action<CAN::list, CAT::lookup, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::list, CAT::lookup>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at, cindex begin, cindex end)
			{
				chain_action_list(contr, CT::pull, func_at);
				chain_action_lookup(contr, CT::apply, begin, end);
			}
		};

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::list, CAT::non, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::list>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex func_at)
				{ chain_action_list(contr, CT::pull, func_at); }
		};

/***********************************************************************************************************************/

// recurse:

	// arg:

		template<auto... filler>
		struct T_chain_action<CAN::recurse, CAT::arg, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::recurse, CAT::arg>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_at)
			{
				chain_action_recurse(contr, CT::pull);
				chain_action_arg(contr, CT::apply, arg_at);
			}
		};

	// list:

		template<auto... filler>
		struct T_chain_action<CAN::recurse, CAT::list, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::recurse, CAT::list>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_at)
			{
				chain_action_recurse(contr, CT::pull);
				chain_action_list(contr, CT::apply, arg_at);
			}
		};

	// recurse:

		template<auto... filler>
		struct T_chain_action<CAN::recurse, CAT::recurse, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::recurse, CAT::recurse>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr)
			{
				chain_action_recurse(contr, CT::pull);
				chain_action_recurse(contr, CT::apply);
			}
		};

	// lookup:

		template<auto... filler>
		struct T_chain_action<CAN::recurse, CAT::lookup, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::recurse, CAT::lookup>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex begin, cindex end)
			{
				chain_action_recurse(contr, CT::pull);
				chain_action_lookup(contr, CT::apply, begin, end);
			}
		};

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::recurse, CAT::non, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::recurse>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ chain_action_recurse(contr, CT::pull); }
		};

/***********************************************************************************************************************/

// lookup:

	// arg:

		template<auto... filler>
		struct T_chain_action<CAN::lookup, CAT::arg, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::lookup, CAT::arg>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex begin, cindex end, cindex arg_at)
			{
				chain_action_lookup(contr, CT::pull, begin, end);
				chain_action_arg(contr, CT::apply, arg_at);
			}
		};

	// list:

		template<auto... filler>
		struct T_chain_action<CAN::lookup, CAT::list, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::lookup, CAT::list>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex begin, cindex end, cindex arg_at)
			{
				chain_action_lookup(contr, CT::pull, begin, end);
				chain_action_list(contr, CT::apply, arg_at);
			}
		};

	// recurse:

		template<auto... filler>
		struct T_chain_action<CAN::lookup, CAT::recurse, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::lookup, CAT::recurse>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex begin, cindex end)
			{
				chain_action_lookup(contr, CT::pull, begin, end);
				chain_action_recurse(contr, CT::apply);
			}
		};

	// lookup:

		template<auto... filler>
		struct T_chain_action<CAN::lookup, CAT::lookup, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::lookup, CAT::lookup>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr,
				cindex func_begin, cindex func_end, cindex arg_begin, cindex arg_end)
			{
				chain_action_lookup(contr, CT::pull, func_begin, func_end);
				chain_action_lookup(contr, CT::apply, arg_begin, arg_end);
			}
		};

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::lookup, CAT::non, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::lookup>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex begin, cindex end)
				{ chain_action_lookup(contr, CT::pull, begin, end); }
		};

/***********************************************************************************************************************/

// non:

	// arg: (id arg; allows the user to conceptualize composition before application)

		template<auto... filler>
		struct T_chain_action<CAN::non, CAT::arg, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::arg>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_at)
				{ chain_action_arg(contr, CT::push, arg_at); }
		};

	// list: (id list; allows the user to conceptualize composition before application)

		template<auto... filler>
		struct T_chain_action<CAN::non, CAT::list, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::list>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex list_at)
				{ chain_action_list(contr, CT::push, list_at); }
		};

	// recurse: (id list; allows the user to conceptualize composition before application)

		template<auto... filler>
		struct T_chain_action<CAN::non, CAT::recurse, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::recurse>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ chain_action_recurse(contr, CT::push); }
		};

	// lookup: (id lookup; allows the user to conceptualize composition before application)

		template<auto... filler>
		struct T_chain_action<CAN::non, CAT::lookup, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::lookup>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex begin, cindex end)
				{ chain_action_lookup(contr, CT::push, begin, end); }
		};

	// non: (not applicable)

/***********************************************************************************************************************/

// end:

	// id:

		template<auto... filler>
		struct T_chain_action<CAN::end, CAT::id, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<CAT::arg> + 1;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_end, cindex note)
			{
				chain_action_arg(contr, CT::drop, arg_end);

				contr->set_inc_instr(CN::halt, note);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

