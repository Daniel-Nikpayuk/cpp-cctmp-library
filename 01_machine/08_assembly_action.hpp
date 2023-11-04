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

/***********************************************************************************************************************/

// names:

	struct AssemblyActionName
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			base, pad, replace, assign, apply, jump, re_turn, dimension
		};

	}; using AAN = AssemblyActionName;

/***********************************************************************************************************************/

// notes:

	struct AssemblyActionNote
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			halting, dimension
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

// base:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::base, AAT::id, filler...>
		{
			nik_ces gindex_type offset[] = {0, 1};

			template<typename Contr>
			nik_ces void result(Contr *contr) { contr->set_inc_instr(AN::id, AT::id); }
		};

	// halting:

		template<auto... filler>
		struct T_assembly_action<AAN::base, AAT::halting, filler...>
		{
			nik_ces gindex_type offset[] = {0, 1};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note) { contr->set_inc_instr(AN::halt, note); }
		};

/***********************************************************************************************************************/

// pad:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::pad, AAT::id, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex padding)
			{
				contr->set_instr_pos(padding);

				contr->add_marked_instr(AN::pad, AT::segment);
				contr->set_inc_instr(AN::pad, AT::id);
			}
		};

/***********************************************************************************************************************/

// replace:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::replace, AAT::id, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2}; // update

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex is_carg, cindex arg_at)
			{
				if (is_carg)
				{
					contr->set_inc_instr(AN::reselect, AT::id, 1, arg_at);
					contr->set_inc_instr(AN::replace, AT::id);
				}
				// else if Sign::is_copy do nothing.
			}
		};

/***********************************************************************************************************************/

// assign:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::assign, AAT::id, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2}; // update

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex )
			{
			//	contr->set_inc_instr(AN::select     , AT::extend , 1 , ins[AAI::pos0] , ins[AAI::pos1]);
			//	contr->set_inc_instr(ins[AAI::pos2] , AT::id     , 1 , ins[AAI::pos3] );
			}
		};

/***********************************************************************************************************************/

// apply:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::apply, AAT::id, filler...>
		{
			nik_ces gindex_type offset[] = {0, 2}; // update

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex )
			{
			//	contr->set_inc_instr(AN::select     , AT::extend , 1 , ins[AAI::pos0] , ins[AAI::pos1]);
			//	contr->set_inc_instr(ins[AAI::pos2] , AT::id     , 1 , ins[AAI::pos3] );
			}
		};

	// void:

	//	template<auto... filler>
	//	struct T_assembly_action<AAN::apply, AAT::vo_id, filler...>
	//	{
	//		nik_ces gindex_type offset[] = {0, 2}; // update

	//		template<typename Contr>
	//		nik_ces void result(Contr *contr, cindex )
	//		{
	//			auto & iter = contr->line_iter;
	//			auto name   = contr->call_name(iter);

	//			contr->add_link(); // if (toc.has_link(iter)) ?
	//			contr->add_marked_instr(name, AT::void_f);
	//		}
	//	};

	// test:

	//	template<auto... filler>
	//	struct T_assembly_action<AAN::apply, AAT::test, filler...>
	//	{
	//		nik_ces gindex_type offset[] = {0, 2}; // update

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

// jump:

	// id:

	//	template<auto... filler>
	//	struct T_assembly_action<AAN::jump, AAT::id, filler...>
	//	{
	//		nik_ces gindex_type offset[] = {0, 2}; // update

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
	//		nik_ces gindex_type offset[] = {0, 2}; // update

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
	//		nik_ces gindex_type offset[] = {0, 2}; // update

	//		template<typename Contr>
	//		nik_ces void result(Contr *contr, cindex )
	//		{
	//			contr->add_jump();

	//			contr->add_marked_instr(AN::jump, AT::go_to);
	//		}
	//	};

/***********************************************************************************************************************/

// return:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::re_turn, AAT::id, filler...>
		{
			nik_ces gindex_type offset[] = {0, 3};

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex )
			{
			//	contr->set_inc_instr(AN::select     , AT::extend , 1 , ins[AAI::pos0] , ins[AAI::pos1]);
			//	contr->set_inc_instr(ins[AAI::pos2] , AT::id     , 1 , ins[AAI::pos3] );
			//	contr->set_inc_instr(AN::halt       , AT::first  );
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

