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

		template<auto name, auto note>
		nik_ce auto chain_offset = T_chain_action<name, note>::offset;

/***********************************************************************************************************************/

// names:

	struct ChainActionName
	{
		enum : gkey_type // convenience for default params.
		{
			identity = 0, id = identity,
			generic, non_x_catN, catN_x_non,
			cat0_x_catN, cat1_x_catN, cat2_x_catN,
			begin, non, recurse, arg, list, lookup, end,
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
			sub, non, recurse, arg, list, lookup,
			dimension
		};

	}; using CAT = ChainActionNote;

/***********************************************************************************************************************/

// generic:

	// non (offset only):

		template<auto... filler>
		struct T_chain_action<CAN::generic, CAT::non, filler...> { nik_ces gindex_type offset = 0; };

	// recurse:

		template<auto... filler>
		struct T_chain_action<CAN::generic, CAT::recurse, filler...>
		{
			nik_ces gindex_type offset = machine_offset<MAN::set, MAT::inc>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
				{ machine_action<MAN::set, MAT::inc>(contr, CN::list, note, 1, contr->rec_at); }
		};

	// list:

		template<auto... filler>
		struct T_chain_action<CAN::generic, CAT::list, filler...>
		{
			nik_ces gindex_type offset = machine_offset<MAN::set, MAT::inc>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex list_at)
				{ machine_action<MAN::set, MAT::inc>(contr, CN::list, note, 1, list_at); }
		};

	// arg:

		template<auto... filler>
		struct T_chain_action<CAN::generic, CAT::arg, filler...>
		{
			nik_ces gindex_type offset = 2 * machine_offset<MAN::set, MAT::inc>;

			using cindex = gcindex_type;
			using cbool  = gcbool_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex arg_at, cbool mutate = false)
			{
				machine_action<MAN::set, MAT::inc>(contr, CN::arg, CT::select, 1, arg_at);
				machine_action<MAN::set, MAT::inc>(contr, CN::arg, note, 1, mutate);
			}
		};

	// lookup:

		template<auto... filler>
		struct T_chain_action<CAN::generic, CAT::lookup, filler...>
		{
			nik_ces gindex_type offset	= machine_offset< MAN::set  , MAT::inc >
							+ machine_offset< MAN::push , MAT::id  >
							+  lookup_offset< LAN::find , LAT::id  >
							+ machine_offset< MAN::pop  , MAT::id  > ;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex begin, cindex end)
			{
				machine_action< MAN::set  , MAT::inc >(contr, CN::list, CT::select, 1, contr->env_at);
				machine_action< MAN::push , MAT::id  >(contr, CN::lookup, note, contr->str_at);
				 lookup_action< LAN::find , LAT::id  >(contr, begin, end);
				machine_action< MAN::pop  , MAT::id  >(contr);
			}
		};

	// offset:

		template<auto... notes>
		nik_ce auto chain_action_offset = (... + T_chain_action<CAN::generic, notes>::offset);

/***********************************************************************************************************************/

// pairs:

	// non x catN:

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::non_x_catN, note, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<note>;

			using cindex = gcindex_type;

			template<typename Contr, typename... Ts>
			nik_ces void result(Contr *contr, Ts... vs)
				{ chain_action<CAN::generic, note>(contr, CT::push, vs...); }
		};

	// catN x non:

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::catN_x_non, note, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<note>;

			using cindex = gcindex_type;

			template<typename Contr, typename... Ts>
			nik_ces void result(Contr *contr, Ts... vs)
				{ chain_action<CAN::generic, note>(contr, CT::pull, vs...); }
		};

	// cat0 x catN:

		template<gkey_type note0, gkey_type note1, auto... filler>
		struct T_chain_action<CAN::cat0_x_catN, note0, note1, filler...>
		{
			nik_ces gindex_type offset = 2 * chain_action_offset<note0, note1>;

			using cindex = gcindex_type;

			template<typename Contr, typename... Ts>
			nik_ces void result(Contr *contr, Ts... vs)
			{
				chain_action<CAN::generic, note0>(contr, CT::pull);
				chain_action<CAN::generic, note1>(contr, CT::push, vs...);
			}
		};

	// cat1 x catN:

		template<gkey_type note0, gkey_type note1, auto... filler>
		struct T_chain_action<CAN::cat1_x_catN, note0, note1, filler...>
		{
			nik_ces gindex_type offset = 2 * chain_action_offset<note0, note1>;

			using cindex = gcindex_type;

			template<typename Contr, typename... Ts>
			nik_ces void result(Contr *contr, cindex v0, Ts... vs)
			{
				chain_action<CAN::generic, note0>(contr, CT::pull, v0);
				chain_action<CAN::generic, note1>(contr, CT::push, vs...);
			}
		};

	// cat2 x catN:

		template<gkey_type note0, gkey_type note1, auto... filler>
		struct T_chain_action<CAN::cat2_x_catN, note0, note1, filler...>
		{
			nik_ces gindex_type offset = 2 * chain_action_offset<note0, note1>;

			using cindex = gcindex_type;

			template<typename Contr, typename... Ts>
			nik_ces void result(Contr *contr, cindex v0, cindex v1, Ts... vs)
			{
				chain_action<CAN::generic, note0>(contr, CT::pull, v0, v1);
				chain_action<CAN::generic, note1>(contr, CT::push, vs...);
			}
		};

/***********************************************************************************************************************/

// begin:

	// id:

		template<auto... filler>
		struct T_chain_action<CAN::begin, CAT::id, filler...>
		{
			nik_ces gindex_type offset = machine_offset<MAN::set, MAT::inc>;

			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::set, MAT::inc>(contr, CN::id, CT::id); }
		};

	// sub:

		template<auto... filler>
		struct T_chain_action<CAN::begin, CAT::sub, filler...>
		{
			nik_ces gindex_type offset	= machine_offset< MAN::push , MAT::id  >
							+ machine_offset< MAN::set  , MAT::inc > ;

			using cindex = gcindex_type;


			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
			{
				machine_action< MAN::push , MAT::id  >(contr, CN::subchain, note);
				machine_action< MAN::set  , MAT::inc >(contr, CN::id, CT::id);
			}
		};

/***********************************************************************************************************************/

// recurse:

	// recurse, list, arg, lookup:

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::recurse, note, filler...> :
			public T_chain_action<CAN::cat0_x_catN, CAT::recurse, note, filler...> { };

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::recurse, CAT::non, filler...> :
			public T_chain_action<CAN::catN_x_non, CAT::recurse, filler...> { };

/***********************************************************************************************************************/

// list:

	// recurse, list, arg, lookup:

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::list, note, filler...> :
			public T_chain_action<CAN::cat1_x_catN, CAT::list, note, filler...> { };

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::list, CAT::non, filler...> :
			public T_chain_action<CAN::catN_x_non, CAT::list, filler...> { };

/***********************************************************************************************************************/

// arg:

	// recurse, list, arg, lookup:

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::arg, note, filler...> :
			public T_chain_action<CAN::cat1_x_catN, CAT::arg, note, filler...> { };

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::non, filler...> :
			public T_chain_action<CAN::catN_x_non, CAT::arg, filler...> { };

/***********************************************************************************************************************/

// lookup:

	// recurse, list, arg, lookup:

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::lookup, note, filler...> :
			public T_chain_action<CAN::cat2_x_catN, CAT::lookup, note, filler...> { };

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::lookup, CAT::non, filler...> :
			public T_chain_action<CAN::catN_x_non, CAT::lookup, filler...> { };

/***********************************************************************************************************************/

// non:

	// recurse, list, arg, lookup: (id *; allows the user to conceptualize composition before application)

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::non, note, filler...> :
			public T_chain_action<CAN::non_x_catN, note, filler...> { };

	// non: (not applicable)

/***********************************************************************************************************************/

// end:

	// id:

		template<auto... filler>
		struct T_chain_action<CAN::end, CAT::id, filler...>
		{
			nik_ces gindex_type offset	= chain_action_offset<CAT::arg>
							+ machine_offset<MAN::set, MAT::inc> ;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_drop, cindex note)
			{
				  chain_action<CAN::generic, CAT::arg>(contr, CT::drop, arg_drop);
				machine_action<MAN::set, MAT::inc>(contr, CN::halt, note);
			}
		};

	// sub:

		template<auto... filler>
		struct T_chain_action<CAN::end, CAT::sub, filler...>
		{
			nik_ces gindex_type offset	= chain_offset<CAN::end, CAT::id>
							+ machine_offset<MAN::pop, MAT::id> ;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_drop, cindex note)
			{
				  chain_action<CAN::end, CAT::id>(contr, arg_drop, note);
				machine_action<MAN::pop, MAT::id>(contr);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

