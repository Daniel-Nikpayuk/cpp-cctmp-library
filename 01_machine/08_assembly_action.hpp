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

// assembly action:

namespace machine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, gkey_type, auto...> struct T_assembly_action;

	// syntactic sugar:

		template<auto name, auto note, typename... Ts>
		nik_ce auto assembly_action(Ts... vs) // requires template deduction <>:
			{ return T_assembly_action<name, note>::template result<>(vs...); }

/***********************************************************************************************************************/

// names:

	struct AssemblyActionName
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			begin, pad, jump, apply, unit, replace, end, dimension
		};

	}; using AAN = AssemblyActionName;

/***********************************************************************************************************************/

// notes:

	struct AssemblyActionNote
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			begin, value, recurse, lookup, end, dimension
		};

	}; using AAT = AssemblyActionNote;

/***********************************************************************************************************************/

// instructions:

//	struct AssemblyActionInstr
//	{
//		enum : gkey_type { pos0 = 0, pos1, pos2, pos3, dimension };
//		enum : gkey_type { name = 0, note };

//	}; using AAI = AssemblyActionInstr;

/***********************************************************************************************************************/

// offset:

//	using AssemblyActionOffset = cctmp::ActionOffset;
//	using AAO                  = cctmp::ActionOffset;

/***********************************************************************************************************************/

// size:

//	using T_assembly_contr_size = cctmp::T_contr_size<T_assembly_action, AAI, AAO>;

/***********************************************************************************************************************/

// begin:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::begin, AAT::id, filler...>
		{
			nik_ces gindex_type offset = 1;

			template<typename Contr>
			nik_ces void result(Contr *contr) { contr->set_inc_instr(AN::id, AT::id); }
		};

/***********************************************************************************************************************/

// pad:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::pad, AAT::id, filler...>
		{
			nik_ces gindex_type offset = 2;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex pad_size)
			{
				contr->set_inc_instr(AN::pad, AT::segment, 1, pad_size);
				contr->set_inc_instr(AN::pad, AT::id);
			}
		};

/***********************************************************************************************************************/

// jump:

	// id:

	//	template<auto... filler>
	//	struct T_assembly_action<AAN::jump, AAT::id, filler...>
	//	{
	//		nik_ces gindex_type offset = 2; // update

	//		template<typename Contr>
	//		nik_ces void result(Contr *contr, cindex )
	//		{
	//			auto & iter = contr->line_iter;

	//			contr->set_label_line(iter);
	//		}
	//	};

	// bran:

	//	template<auto... filler>
	//	struct T_assembly_action<AAN::jump, AAT::branch, filler...>
	//	{
	//		nik_ces gindex_type offset = 2; // update

	//		template<typename Contr>
	//		nik_ces void result(Contr *contr, cindex )
	//		{
	//			contr->add_jump();

	//			contr->add_marked_instr(AN::jump, AT::branch);
	//		}
	//	};

	// goto:

	//	template<auto... filler>
	//	struct T_assembly_action<AAN::jump, AAT::go_to, filler...>
	//	{
	//		nik_ces gindex_type offset = 2; // update

	//		template<typename Contr>
	//		nik_ces void result(Contr *contr, cindex )
	//		{
	//			contr->add_jump();

	//			contr->add_marked_instr(AN::jump, AT::go_to);
	//		}
	//	};

/***********************************************************************************************************************/

// apply:

	// begin:

		template<auto... filler>
		struct T_assembly_action<AAN::apply, AAT::begin, filler...>
		{
			nik_ces gindex_type offset = 2;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr)
			{
				contr->push_machine(AN::chain, AT::call_f);
				contr->set_inc_instr(CN::id, CT::id);
			}
		};

	// end:

		template<auto... filler>
		struct T_assembly_action<AAN::apply, AAT::end, filler...>
		{
			nik_ces gindex_type offset = 2; // update

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_offset)
			{
				chain_action<CAN::end, CAT::id>(contr, arg_offset, CT::apply);
				contr->pop_machine();
			}
		};

/***********************************************************************************************************************/

// test:

	//	template<auto... filler>
	//	struct T_assembly_action<AAN::apply, AAT::test, filler...>
	//	{
	//		nik_ces gindex_type offset = 2; // update

	//		template<typename Contr>
	//		nik_ces void result(Contr *contr, cindex )
	//		{
	//			auto & iter = contr->line_iter;
	//			auto name   = contr->call_name(iter);

	//			contr->add_link(); // if (toc.has_link(iter)) ?
	//			contr->add_marked_instr(name, AT::id);
	//		}
	//	};

/***********************************************************************************************************************/

// void:

/***********************************************************************************************************************/

// swap:

	//	template<auto... filler>
	//	struct T_assembly_action<AAN::apply, AAT::vo_id, filler...>
	//	{
	//		nik_ces gindex_type offset = 2; // update

	//		template<typename Contr>
	//		nik_ces void result(Contr *contr, cindex )
	//		{
	//			auto & iter = contr->line_iter;
	//			auto name   = contr->call_name(iter);

	//			contr->add_link(); // if (toc.has_link(iter)) ?
	//			contr->add_marked_instr(name, AT::void_f);
	//		}
	//	};

/***********************************************************************************************************************/

// unit:

	// value:

		template<auto... filler>
		struct T_assembly_action<AAN::unit, AAT::value, filler...>
		{
			nik_ces gindex_type offset = 3;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_offset)
			{
				contr->push_machine(AN::chain, AT::call_f);
				contr->set_inc_instr(CN::id, CT::id);
				chain_action<CAN::end, CAT::id>(contr, arg_offset, CT::first);
				contr->pop_machine();
			}
		};

	// recurse:

		template<auto... filler>
		struct T_assembly_action<AAN::unit, AAT::recurse, filler...>
		{
			nik_ces gindex_type offset = 3;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ contr->set_inc_instr(AN::list, AT::recurse, 1, contr->rec_at); }
		};

	// lookup:

		template<auto... filler>
		struct T_assembly_action<AAN::unit, AAT::lookup, filler...>
		{
			nik_ces gindex_type offset = 2 + T_lookup_action<LAN::find, LAT::id>::offset;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex begin, cindex end)
			{
				contr->set_inc_instr(AN::list, AT::id, 1, contr->env_at);

				contr->push_machine(AN::lookup, AT::call_f, contr->str_at);
				lookup_action<LAN::find, LAT::id>(contr, begin, end);
				contr->pop_machine();
			}
		};

/***********************************************************************************************************************/

// replace:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::replace, AAT::id, filler...>
		{
			nik_ces gindex_type offset = 2; // update

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex not_copy, cindex arg_at)
			{
				if (not_copy)
				{
					contr->set_inc_instr(AN::list, AT::reselect, 1, arg_at);
					contr->set_inc_instr(AN::replace, AT::id);
				}
			}
		};

/***********************************************************************************************************************/

// end:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::end, AAT::id, filler...>
		{
			nik_ces gindex_type offset = 1;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note) { contr->set_inc_instr(AN::halt, note); }
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine
