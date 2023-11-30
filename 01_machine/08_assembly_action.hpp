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
			begin, pad, jump, apply, unit, morph, replace, end, dimension
		};

	}; using AAN = AssemblyActionName;

/***********************************************************************************************************************/

// notes:

	struct AssemblyActionNote
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			begin, branch, go_to, value, recurse, lookup, cons, end, dimension
		};

	}; using AAT = AssemblyActionNote;

/***********************************************************************************************************************/

// begin:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::begin, AAT::id, filler...>
		{
			nik_ces gindex_type offset = machine_offset<MAN::set, MAT::inc>;

			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::set, MAT::inc>(contr, AN::id, AT::id); }
		};

/***********************************************************************************************************************/

// pad:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::pad, AAT::id, filler...>
		{
			nik_ces gindex_type offset = 2 * machine_offset<MAN::set, MAT::inc>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex pad_size)
			{
				machine_action<MAN::set, MAT::inc>(contr, AN::pad, AT::segment, 1, pad_size);
				machine_action<MAN::set, MAT::inc>(contr, AN::pad, AT::id);
			}
		};

/***********************************************************************************************************************/

// jump:

	// bran:

		template<auto... filler>
		struct T_assembly_action<AAN::jump, AAT::branch, filler...>
		{
			nik_ces gindex_type offset = machine_offset<MAN::set, MAT::inc>;

			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::set, MAT::inc>(contr, AN::jump, AT::branch); }
		};

	// goto:

		template<auto... filler>
		struct T_assembly_action<AAN::jump, AAT::go_to, filler...>
		{
			nik_ces gindex_type offset = machine_offset<MAN::set, MAT::inc>;

			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::set, MAT::inc>(contr, AN::jump, AT::go_to); }
		};

/***********************************************************************************************************************/

// apply:

	// begin:

		template<auto... filler>
		struct T_assembly_action<AAN::apply, AAT::begin, filler...>
		{
			nik_ces gindex_type offset	= machine_offset< MAN::push , MAT::id  >
							+ machine_offset< MAN::set  , MAT::inc > ;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
			{
				machine_action< MAN::push , MAT::id  >(contr, AN::chain, note);
				machine_action< MAN::set  , MAT::inc >(contr, CN::id, CT::id);
			}
		};

	// end:

		template<auto... filler>
		struct T_assembly_action<AAN::apply, AAT::end, filler...>
		{
			nik_ces gindex_type offset	=   chain_offset< CAN::end , CAT::id >
							+ machine_offset< MAN::pop , MAT::id > ;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_drop, cindex note)
			{
				  chain_action< CAN::end , CAT::id >(contr, arg_drop, note);
				machine_action< MAN::pop , MAT::id >(contr);
			}
		};

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
			nik_ces gindex_type offset	= machine_offset< MAN::push , MAT::id  >
							+ machine_offset< MAN::set  , MAT::inc >
							+   chain_offset< CAN::end  , CAT::id  >
							+ machine_offset< MAN::pop  , MAT::id  > ;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_drop)
			{
				machine_action< MAN::push , MAT::id  >(contr, AN::chain, AT::call_f);
				machine_action< MAN::set  , MAT::inc >(contr, CN::id, CT::id);
				  chain_action< CAN::end  , CAT::id  >(contr, arg_drop, CT::first);
				machine_action< MAN::pop  , MAT::id  >(contr);
			}
		};

	// recurse:

		template<auto... filler>
		struct T_assembly_action<AAN::unit, AAT::recurse, filler...>
		{
			nik_ces gindex_type offset = machine_offset<MAN::set, MAT::inc>;

			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::set, MAT::inc>(contr, AN::list, AT::recurse, 1, contr->rec_at); }
		};

	// lookup:

		template<auto... filler>
		struct T_assembly_action<AAN::unit, AAT::lookup, filler...>
		{
			nik_ces gindex_type offset	= machine_offset< MAN::set  , MAT::inc >
							+ machine_offset< MAN::push , MAT::id  >
							+  lookup_offset< LAN::find , LAT::id  >
							+ machine_offset< MAN::pop  , MAT::id  > ;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex begin, cindex end)
			{
				machine_action< MAN::set  , MAT::inc >(contr, AN::list, AT::id, 1, contr->env_at);
				machine_action< MAN::push , MAT::id  >(contr, AN::lookup, AT::call_f, contr->str_at);
				 lookup_action< LAN::find , LAT::id  >(contr, begin, end);
				machine_action< MAN::pop  , MAT::id  >(contr);
			}
		};

/***********************************************************************************************************************/

// replace:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::replace, AAT::id, filler...>
		{
			nik_ces gindex_type offset = 2 * machine_offset<MAN::set, MAT::inc>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_at)
			{
				machine_action<MAN::set, MAT::inc>(contr, AN::arg, AT::select, 1, arg_at);
				machine_action<MAN::set, MAT::inc>(contr, AN::replace, AT::id);
			}
		};

/***********************************************************************************************************************/

// end:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::end, AAT::id, filler...>
		{
			nik_ces gindex_type offset = machine_offset<MAN::set, MAT::inc>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
				{ machine_action<MAN::set, MAT::inc>(contr, AN::halt, note); }
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

