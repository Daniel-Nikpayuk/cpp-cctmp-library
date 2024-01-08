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

// assembly action:

namespace machine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

/***********************************************************************************************************************/

// pad:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::pad, AAT::id, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex pad_size, cindex note)
			{
				machine_action<MAN::push, MAT::instr>(contr, AN::pad, AT::select, pad_size);
				machine_action<MAN::push, MAT::instr>(contr, AN::pad, note);
			}
		};

/***********************************************************************************************************************/

// arg:

	// replace:

		template<auto... filler>
		struct T_assembly_action<AAN::arg, AAT::replace, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_at)
			{
				machine_action<MAN::push, MAT::instr>(contr, AN::arg, AT::select, arg_at);
				machine_action<MAN::push, MAT::instr>(contr, AN::arg, AT::replace);
			}
		};

/***********************************************************************************************************************/

// goto:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::go_to, AAT::id, filler...>
		{
			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::push, MAT::instr>(contr, AN::jump, AT::go_to); }
		};

	// begin:

		template<auto... filler>
		struct T_assembly_action<AAN::go_to, AAT::begin, filler...>
		{
			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::delay, MAT::jump>(contr, AN::jump, AT::go_to); }
		};

	// end:

		template<auto... filler>
		struct T_assembly_action<AAN::go_to, AAT::end, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex offset = 0)
				{ machine_action<MAN::force, MAT::jump>(contr, offset); }
		};

/***********************************************************************************************************************/

// branch:

	// begin:

		template<auto... filler>
		struct T_assembly_action<AAN::branch, AAT::begin, filler...>
		{
			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::delay, MAT::jump>(contr, AN::jump, AT::branch); }
		};

	// end:

		template<auto... filler>
		struct T_assembly_action<AAN::branch, AAT::end, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex offset = 0)
				{ machine_action<MAN::force, MAT::jump>(contr, offset); }
		};

/***********************************************************************************************************************/

// invert:

	// begin:

		template<auto... filler>
		struct T_assembly_action<AAN::invert, AAT::begin, filler...>
		{
			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::delay, MAT::jump>(contr, AN::jump, AT::invert); }
		};

	// end:

		template<auto... filler>
		struct T_assembly_action<AAN::invert, AAT::end, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex offset = 0)
				{ machine_action<MAN::force, MAT::jump>(contr, offset); }
		};

/***********************************************************************************************************************/

// id:

	// begin:

		template<auto... filler>
		struct T_assembly_action<AAN::id, AAT::begin, filler...>
		{
			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::push, MAT::instr>(contr, AN::id, AT::id); }
		};

	// end:

		template<auto... filler>
		struct T_assembly_action<AAN::id, AAT::end, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
				{ machine_action<MAN::push, MAT::instr>(contr, AN::halt, note); }
		};

/***********************************************************************************************************************/

// apply:

	// begin:

		template<auto... filler>
		struct T_assembly_action<AAN::apply, AAT::begin, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
			{
				machine_action< MAN::delay , MAT::call  >(contr, AN::sub_chain, note);
				  chain_action< CAN::id    , CAT::begin >(contr);
			}
		};

	// end:

		template<auto... filler>
		struct T_assembly_action<AAN::apply, AAT::end, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_drop, cindex note)
			{
				if (arg_drop)
				  chain_action< CAN::generic , CAT::arg  >(contr, CT::drop, arg_drop);

				  chain_action< CAN::id      , CAT::end  >(contr, note);
				machine_action< MAN::force   , MAT::call >(contr);
			}
		};

/***********************************************************************************************************************/

// eval:

	// begin:

		template<auto... filler>
		struct T_assembly_action<AAN::eval, AAT::begin, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
			{
				 machine_action< MAN::delay , MAT::call  >(contr, AN::sub_asm, note);
				assembly_action< AAN::id    , AAT::begin >(contr);
			}
		};

	// end:

		template<auto... filler>
		struct T_assembly_action<AAN::eval, AAT::end, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
			{
				assembly_action< AAN::id    , AAT::end  >(contr, note);
				 machine_action< MAN::force , MAT::call >(contr);
			}
		};

/***********************************************************************************************************************/

// literal:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::literal, AAT::id, filler...>
		{
			using cindex = gcindex_type;

			nik_ces cindex arg_drop = 0;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex str_at, cindex note, cindex begin, cindex end)
			{
				assembly_action< AAN::apply   , AAT::begin   >(contr, AT::call_f);
				   chain_action< CAN::generic , CAT::literal >(contr, CT::first, str_at, note, begin, end);
				assembly_action< AAN::apply   , AAT::end     >(contr, arg_drop, CT::first);
			}

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex begin, cindex end)
				{ result(contr, contr->src_at, note, begin, end); }
		};

/***********************************************************************************************************************/

// lookup:

	// variable:

		template<auto... filler>
		struct T_assembly_action<AAN::lookup, AAT::variable, filler...>
		{
			using cindex = gcindex_type;

			nik_ces cindex arg_drop = 0;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_at)
			{
				assembly_action< AAN::apply   , AAT::begin >(contr, AT::call_f);
				   chain_action< CAN::generic , CAT::arg   >(contr, CT::drop, arg_at);
				assembly_action< AAN::apply   , AAT::end   >(contr, arg_drop, CT::first);
			}
		};

	// parameter:

		template<auto... filler>
		struct T_assembly_action<AAN::lookup, AAT::parameter, filler...>
		{
			using cindex = gcindex_type;

			nik_ces cindex arg_drop = 0;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex pos, cindex num)
			{
				assembly_action< AAN::apply   , AAT::begin  >(contr, AT::call_f);
				   chain_action< CAN::generic , CAT::lookup >(contr, CT::first, pos, num);
				assembly_action< AAN::apply   , AAT::end    >(contr, arg_drop, CT::first);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

