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

		template<auto name, auto note>
		nik_ce auto assembly_offset = T_assembly_action<name, note>::offset;

/***********************************************************************************************************************/

// names:

	struct AssemblyActionName
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			begin, pad, go_to, branch, invert, apply, eval, literal, lookup, replace, end,
			dimension
		};

	}; using AAN = AssemblyActionName;

/***********************************************************************************************************************/

// notes:

	struct AssemblyActionNote
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			begin, end, recurse,
			dimension
		};

	}; using AAT = AssemblyActionNote;

/***********************************************************************************************************************/

// begin:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::begin, AAT::id, filler...>
		{
			nik_ces gindex_type offset = machine_offset<MAN::push, MAT::instr>;

			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::push, MAT::instr>(contr, AN::id, AT::id); }
		};

/***********************************************************************************************************************/

// end:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::end, AAT::id, filler...>
		{
			nik_ces gindex_type offset = machine_offset<MAN::push, MAT::instr>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
				{ machine_action<MAN::push, MAT::instr>(contr, AN::halt, note); }
		};

/***********************************************************************************************************************/

// pad:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::pad, AAT::id, filler...>
		{
			nik_ces gindex_type offset = 2 * machine_offset<MAN::push, MAT::instr>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex pad_size)
			{
				machine_action<MAN::push, MAT::instr>(contr, AN::pad, AT::segment, pad_size);
				machine_action<MAN::push, MAT::instr>(contr, AN::pad, AT::id);
			}
		};

/***********************************************************************************************************************/

// goto:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::go_to, AAT::id, filler...>
		{
			nik_ces gindex_type offset = machine_offset<MAN::push, MAT::instr>;

			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::push, MAT::instr>(contr, AN::jump, AT::go_to); }
		};

/***********************************************************************************************************************/

// branch:

	// begin:

		template<auto... filler>
		struct T_assembly_action<AAN::branch, AAT::begin, filler...>
		{
			nik_ces gindex_type offset = machine_offset<MAN::delay, MAT::jump>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::delay, MAT::jump>(contr, AN::jump, AT::branch); }
		};

	// end:

		template<auto... filler>
		struct T_assembly_action<AAN::branch, AAT::end, filler...>
		{
			nik_ces gindex_type offset = machine_offset<MAN::force, MAT::jump>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::force, MAT::jump>(contr); }
		};

/***********************************************************************************************************************/

// invert:

	// begin:

		template<auto... filler>
		struct T_assembly_action<AAN::invert, AAT::begin, filler...>
		{
			nik_ces gindex_type offset = machine_offset<MAN::delay, MAT::jump>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::delay, MAT::jump>(contr, AN::jump, AT::invert); }
		};

	// end:

		template<auto... filler>
		struct T_assembly_action<AAN::invert, AAT::end, filler...>
		{
			nik_ces gindex_type offset = machine_offset<MAN::force, MAT::jump>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::force, MAT::jump>(contr); }
		};

/***********************************************************************************************************************/

// apply:

	// begin:

		template<auto... filler>
		struct T_assembly_action<AAN::apply, AAT::begin, filler...>
		{
			nik_ces gindex_type offset	= machine_offset< MAN::delay , MAT::call  >
							+ machine_offset< MAN::push  , MAT::instr > ;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
			{
				machine_action< MAN::delay , MAT::call  >(contr, AN::chain, note);
				machine_action< MAN::push  , MAT::instr >(contr, CN::id, CT::id);
			}
		};

	// end:

		template<auto... filler>
		struct T_assembly_action<AAN::apply, AAT::end, filler...>
		{
			nik_ces gindex_type offset	=   chain_offset< CAN::end   , CAT::id   >
							+ machine_offset< MAN::force , MAT::call > ;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_drop, cindex note)
			{
				  chain_action< CAN::end   , CAT::id   >(contr, arg_drop, note);
				machine_action< MAN::force , MAT::call >(contr);
			}
		};

	// void:

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

// eval:

	// begin:

		template<auto... filler>
		struct T_assembly_action<AAN::eval, AAT::begin, filler...>
		{
			nik_ces gindex_type offset	= machine_offset< MAN::delay , MAT::call  >
							+ machine_offset< MAN::push  , MAT::instr > ;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
			{
				machine_action< MAN::delay , MAT::call  >(contr, AN::sub_asm, note);
				machine_action< MAN::push  , MAT::instr >(contr, AN::id, AT::id);
			}
		};

	// end:

		template<auto... filler>
		struct T_assembly_action<AAN::eval, AAT::end, filler...>
		{
			nik_ces gindex_type offset	= assembly_offset< AAN::end   , AAT::id   >
							+  machine_offset< MAN::force , MAT::call > ;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
			{
				assembly_action< AAN::end   , AAT::id   >(contr, note);
				 machine_action< MAN::force , MAT::call >(contr);
			}
		};

/***********************************************************************************************************************/

// literal:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::literal, AAT::id, filler...>
		{
			nik_ces gindex_type offset	= machine_offset< MAN::delay   , MAT::call >
							+ literal_offset< LAN::resolve , LAT::id   >
							+ machine_offset< MAN::force   , MAT::call > ;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex str_at, cindex note, cindex begin, cindex end)
			{
				machine_action< MAN::delay   , MAT::call >(contr, AN::literal, AT::call_f, str_at);
				literal_action< LAN::resolve , LAT::id   >(contr, note, begin, end);
				machine_action< MAN::force   , MAT::call >(contr);
			}

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex begin, cindex end)
				{ result(contr, contr->src_at, note, begin, end); }
		};

/***********************************************************************************************************************/

// lookup:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::lookup, AAT::id, filler...>
		{
			nik_ces gindex_type offset = 2 * machine_offset<MAN::push, MAT::instr>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_at)
			{
				assembly_action< AAN::eval , AAT::begin >(contr, AT::call_f);
				 machine_action< MAN::push , MAT::instr >(contr, AN::arg, AT::select, arg_at);
				 machine_action< MAN::push , MAT::instr >(contr, AN::right, AT::id);
				assembly_action< AAN::eval , AAT::end   >(contr, AT::first);
			}
		};

	// recurse:

		template<auto... filler>
		struct T_assembly_action<AAN::lookup, AAT::recurse, filler...>
		{
			nik_ces gindex_type offset = machine_offset<MAN::push, MAT::instr>;

			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::push, MAT::instr>(contr, AN::list, AT::recurse, contr->rec_at); }
		};

/***********************************************************************************************************************/

// replace:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::replace, AAT::id, filler...>
		{
			nik_ces gindex_type offset = 2 * machine_offset<MAN::push, MAT::instr>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_at)
			{
				machine_action<MAN::push, MAT::instr>(contr, AN::arg, AT::select, arg_at);
				machine_action<MAN::push, MAT::instr>(contr, AN::replace, AT::id);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

