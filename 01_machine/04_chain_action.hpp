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
			begin, end, non, recurse, arg, list,
			boolean, number, character, string,
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
			sub, non, recurse, arg, list,
			literal, boolean, number, character, string,
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
			nik_ces gindex_type offset = machine_offset<MAN::push, MAT::instr>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
				{ machine_action<MAN::push, MAT::instr>(contr, CN::list, note, contr->rec_at); }
		};

	// list:

		template<auto... filler>
		struct T_chain_action<CAN::generic, CAT::list, filler...>
		{
			nik_ces gindex_type offset = machine_offset<MAN::push, MAT::instr>;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex list_at)
				{ machine_action<MAN::push, MAT::instr>(contr, CN::list, note, list_at); }
		};

	// arg:

		template<auto... filler>
		struct T_chain_action<CAN::generic, CAT::arg, filler...>
		{
			nik_ces gindex_type offset = 2 * machine_offset<MAN::push, MAT::instr>;

			using cindex = gcindex_type;
			using cbool  = gcbool_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex arg_at, cbool mutate = false)
			{
				machine_action<MAN::push, MAT::instr>(contr, CN::arg, CT::select, arg_at);
				machine_action<MAN::push, MAT::instr>(contr, CN::arg, note, mutate);
			}
		};

	// literal:

		template<gkey_type note1, auto... filler>
		struct T_chain_action<CAN::generic, CAT::literal, note1, filler...>
		{
			nik_ces gindex_type offset	= machine_offset< MAN::delay   , MAT::call >
							+ literal_offset< LAN::resolve , LAT::id   >
							+ machine_offset< MAN::force   , MAT::call > ;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note0, cindex str_at, cindex begin, cindex end)
			{
				machine_action< MAN::delay   , MAT::call >(contr, CN::literal, note0, str_at);
				literal_action< LAN::resolve , LAT::id   >(contr, note1, begin, end);
				machine_action< MAN::force   , MAT::call >(contr);
			}

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note0, cindex begin, cindex end)
				{ result(contr, note0, contr->src_at, begin, end); }
		};

		// boolean, number, character, string:

			template<auto... filler>
			struct T_chain_action<CAN::generic, CAT::boolean, filler...> :
				public T_chain_action<CAN::generic, CAT::literal, LT::boolean, filler...> { };

			template<auto... filler>
			struct T_chain_action<CAN::generic, CAT::number, filler...> :
				public T_chain_action<CAN::generic, CAT::literal, LT::number, filler...> { };

			template<auto... filler>
			struct T_chain_action<CAN::generic, CAT::character, filler...> :
				public T_chain_action<CAN::generic, CAT::literal, LT::character, filler...> { };

			template<auto... filler>
			struct T_chain_action<CAN::generic, CAT::string, filler...> :
				public T_chain_action<CAN::generic, CAT::literal, LT::string, filler...> { };

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
			nik_ces gindex_type offset = machine_offset<MAN::push, MAT::instr>;

			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::push, MAT::instr>(contr, CN::id, CT::id); }
		};

	// sub:

		template<auto... filler>
		struct T_chain_action<CAN::begin, CAT::sub, filler...>
		{
			nik_ces gindex_type offset	= machine_offset< MAN::delay , MAT::call  >
							+ machine_offset< MAN::push  , MAT::instr > ;

			using cindex = gcindex_type;


			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
			{
				machine_action<MAN::delay , MAT::call  >(contr, CN::subchain, note);
				machine_action<MAN::push  , MAT::instr >(contr, CN::id, CT::id);
			}
		};

/***********************************************************************************************************************/

// end:

	// id:

		template<auto... filler>
		struct T_chain_action<CAN::end, CAT::id, filler...>
		{
			nik_ces gindex_type offset	= chain_action_offset<CAT::arg>
							+ machine_offset<MAN::push, MAT::instr> ;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_drop, cindex note)
			{
				  chain_action< CAN::generic , CAT::arg   >(contr, CT::drop, arg_drop);
				machine_action< MAN::push    , MAT::instr >(contr, CN::halt, note);
			}
		};

	// sub:

		template<auto... filler>
		struct T_chain_action<CAN::end, CAT::sub, filler...>
		{
			nik_ces gindex_type offset	= chain_offset<CAN::end, CAT::id>
							+ machine_offset<MAN::force, MAT::call> ;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_drop, cindex note)
			{
				  chain_action< CAN::end   , CAT::id   >(contr, arg_drop, note);
				machine_action< MAN::force , MAT::call >(contr);
			}
		};

/***********************************************************************************************************************/

// recurse:

	// recurse, list, arg, boolean, number, character, string:

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::recurse, note, filler...> :
			public T_chain_action<CAN::cat0_x_catN, CAT::recurse, note, filler...> { };

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::recurse, CAT::non, filler...> :
			public T_chain_action<CAN::catN_x_non, CAT::recurse, filler...> { };

/***********************************************************************************************************************/

// list:

	// recurse, list, arg, boolean, number, character, string:

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::list, note, filler...> :
			public T_chain_action<CAN::cat1_x_catN, CAT::list, note, filler...> { };

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::list, CAT::non, filler...> :
			public T_chain_action<CAN::catN_x_non, CAT::list, filler...> { };

/***********************************************************************************************************************/

// arg:

	// recurse, list, arg, boolean, number, character, string:

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::arg, note, filler...> :
			public T_chain_action<CAN::cat1_x_catN, CAT::arg, note, filler...> { };

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::non, filler...> :
			public T_chain_action<CAN::catN_x_non, CAT::arg, filler...> { };

/***********************************************************************************************************************/

// boolean:

	// recurse, list, arg, boolean, number, character, string:

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::boolean, note, filler...> :
			public T_chain_action<CAN::cat2_x_catN, CAT::boolean, note, filler...> { };

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::boolean, CAT::non, filler...> :
			public T_chain_action<CAN::catN_x_non, CAT::boolean, filler...> { };

/***********************************************************************************************************************/

// number:

	// recurse, list, arg, boolean, number, character, string:

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::number, note, filler...> :
			public T_chain_action<CAN::cat2_x_catN, CAT::number, note, filler...> { };

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::number, CAT::non, filler...> :
			public T_chain_action<CAN::catN_x_non, CAT::number, filler...> { };

/***********************************************************************************************************************/

// character:

	// recurse, list, arg, boolean, number, character, string:

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::character, note, filler...> :
			public T_chain_action<CAN::cat2_x_catN, CAT::character, note, filler...> { };

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::character, CAT::non, filler...> :
			public T_chain_action<CAN::catN_x_non, CAT::character, filler...> { };

/***********************************************************************************************************************/

// string:

	// recurse, list, arg, boolean, number, character, string:

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::string, note, filler...> :
			public T_chain_action<CAN::cat2_x_catN, CAT::string, note, filler...> { };

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::string, CAT::non, filler...> :
			public T_chain_action<CAN::catN_x_non, CAT::string, filler...> { };

/***********************************************************************************************************************/

// non:

	// recurse, list, arg, boolean, number, character, string:
	// (id *; allows the user to conceptualize composition before application)

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::non, note, filler...> :
			public T_chain_action<CAN::non_x_catN, note, filler...> { };

	// non: (not applicable)

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

