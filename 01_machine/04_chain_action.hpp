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
			generic, begin, non, recurse, arg, list, lookup, end,
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
			non, recurse, arg, list, lookup, param,
			cat0_x_catN, catN_x_cat0,
			cat1_x_catN, cat2_x_catN,
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

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex arg_at)
			{
				machine_action<MAN::set, MAT::inc>(contr, CN::arg, CT::select, 1, arg_at);
				machine_action<MAN::set, MAT::inc>(contr, CN::arg, note);
			}
		};

	// lookup:

		template<auto... filler>
		struct T_chain_action<CAN::generic, CAT::lookup, filler...>
		{
			nik_ces gindex_type offset =	machine_offset< MAN::set  , MAT::inc > +
							machine_offset< MAN::push , MAT::id  > +
							 lookup_offset< LAN::find , LAT::id  > +
							machine_offset< MAN::pop  , MAT::id  > ;

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

// generic pair:

	// cat0 x catN (including non):

		template<auto note0, auto note1, auto... filler>
		struct T_chain_action<CAN::generic, CAT::cat0_x_catN, note0, note1, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<note0, note1>;

			using cindex = gcindex_type;

			template<typename Contr, typename... Ts>
			nik_ces void result(Contr *contr, Ts... vs)
			{
				nik_ce bool is_act0 = (note0 != CAT::non);
				nik_ce bool is_act1 = (note1 != CAT::non);
				nik_ce auto subnote = is_act0 ? CT::apply : CT::push;

				if nik_ce (is_act0) chain_action<CAN::generic, note0>(contr, CT::pull);
				if nik_ce (is_act1) chain_action<CAN::generic, note1>(contr, subnote, vs...);
			}
		};

	// catN x cat0 (including non, param):

		template<auto note0, auto note1, auto... filler>
		struct T_chain_action<CAN::generic, CAT::catN_x_cat0, note0, note1, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<note0, note1>;

			using cindex = gcindex_type;

			template<typename Contr, typename... Ts>
			nik_ces void result(Contr *contr, Ts... vs)
			{
				nik_ce bool is_act0 = (note0 != CAT::non);
				nik_ce bool is_act1 = (note1 != CAT::non) && (note1 != CAT::param);
				nik_ce auto subnote = is_act0 ? CT::apply : CT::push;

				if nik_ce (is_act0) chain_action<CAN::generic, note0>(contr, CT::pull, vs...);
				if nik_ce (is_act1) chain_action<CAN::generic, note1>(contr, subnote);
			}
		};

	// cat1 x catN:

		template<auto note0, auto note1, auto... filler>
		struct T_chain_action<CAN::generic, CAT::cat1_x_catN, note0, note1, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<note0, note1>;

			using cindex = gcindex_type;

			template<typename Contr, typename... Ts>
			nik_ces void result(Contr *contr, cindex v0, Ts... vs)
			{
				chain_action<CAN::generic, note0>(contr, CT::pull, v0);
				chain_action<CAN::generic, note1>(contr, CT::apply, vs...);
			}
		};

	// cat2 x catN:

		template<auto note0, auto note1, auto... filler>
		struct T_chain_action<CAN::generic, CAT::cat2_x_catN, note0, note1, filler...>
		{
			nik_ces gindex_type offset = chain_action_offset<note0, note1>;

			using cindex = gcindex_type;

			template<typename Contr, typename... Ts>
			nik_ces void result(Contr *contr, cindex v0, cindex v1, Ts... vs)
			{
				chain_action<CAN::generic, note0>(contr, CT::pull, v0, v1);
				chain_action<CAN::generic, note1>(contr, CT::apply, vs...);
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

/***********************************************************************************************************************/

// recurse:

	// recurse:

		template<auto... filler>
		struct T_chain_action<CAN::recurse, CAT::recurse, filler...> :
			public T_chain_action<CAN::generic, CAT::cat0_x_catN, CAT::recurse, CAT::recurse, filler...> { };

	// list:

		template<auto... filler>
		struct T_chain_action<CAN::recurse, CAT::list, filler...> :
			public T_chain_action<CAN::generic, CAT::cat0_x_catN, CAT::recurse, CAT::list, filler...> { };

	// arg:

		template<auto... filler>
		struct T_chain_action<CAN::recurse, CAT::arg, filler...> :
			public T_chain_action<CAN::generic, CAT::cat0_x_catN, CAT::recurse, CAT::arg, filler...> { };

	// lookup:

		template<auto... filler>
		struct T_chain_action<CAN::recurse, CAT::lookup, filler...> :
			public T_chain_action<CAN::generic, CAT::cat0_x_catN, CAT::recurse, CAT::lookup, filler...> { };

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::recurse, CAT::non, filler...> :
			public T_chain_action<CAN::generic, CAT::catN_x_cat0, CAT::recurse, CAT::non, filler...> { };

/***********************************************************************************************************************/

// list:

	// recurse:

		template<auto... filler>
		struct T_chain_action<CAN::list, CAT::recurse, filler...> :
			public T_chain_action<CAN::generic, CAT::cat1_x_catN, CAT::list, CAT::recurse, filler...> { };

	// list:

		template<auto... filler>
		struct T_chain_action<CAN::list, CAT::list, filler...> :
			public T_chain_action<CAN::generic, CAT::cat1_x_catN, CAT::list, CAT::list, filler...> { };

	// arg:

		template<auto... filler>
		struct T_chain_action<CAN::list, CAT::arg, filler...> :
			public T_chain_action<CAN::generic, CAT::cat1_x_catN, CAT::list, CAT::arg, filler...> { };

	// lookup:

		template<auto... filler>
		struct T_chain_action<CAN::list, CAT::lookup, filler...> :
			public T_chain_action<CAN::generic, CAT::cat1_x_catN, CAT::list, CAT::lookup, filler...> { };

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::list, CAT::non, filler...> :
			public T_chain_action<CAN::generic, CAT::catN_x_cat0, CAT::list, CAT::non, filler...> { };

/***********************************************************************************************************************/

// arg:

	// recurse:

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::recurse, filler...> :
			public T_chain_action<CAN::generic, CAT::cat1_x_catN, CAT::arg, CAT::recurse, filler...> { };

	// list:

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::list, filler...> :
			public T_chain_action<CAN::generic, CAT::cat1_x_catN, CAT::arg, CAT::list, filler...> { };

	// arg:

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::arg, filler...> :
			public T_chain_action<CAN::generic, CAT::cat1_x_catN, CAT::arg, CAT::arg, filler...> { };

	// lookup:

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::lookup, filler...> :
			public T_chain_action<CAN::generic, CAT::cat1_x_catN, CAT::arg, CAT::lookup, filler...> { };

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::arg, CAT::non, filler...> :
			public T_chain_action<CAN::generic, CAT::catN_x_cat0, CAT::arg, CAT::non, filler...> { };

/***********************************************************************************************************************/

// lookup:

	// recurse:

		template<auto... filler>
		struct T_chain_action<CAN::lookup, CAT::recurse, filler...> :
			public T_chain_action<CAN::generic, CAT::cat2_x_catN, CAT::lookup, CAT::recurse, filler...> { };

	// list:

		template<auto... filler>
		struct T_chain_action<CAN::lookup, CAT::list, filler...> :
			public T_chain_action<CAN::generic, CAT::cat2_x_catN, CAT::lookup, CAT::list, filler...> { };

	// arg:

		template<auto... filler>
		struct T_chain_action<CAN::lookup, CAT::arg, filler...> :
			public T_chain_action<CAN::generic, CAT::cat2_x_catN, CAT::lookup, CAT::arg, filler...> { };

	// lookup:

		template<auto... filler>
		struct T_chain_action<CAN::lookup, CAT::lookup, filler...> :
			public T_chain_action<CAN::generic, CAT::cat2_x_catN, CAT::lookup, CAT::lookup, filler...> { };

	// non: (composer only, add this instr at contr end)

		template<auto... filler>
		struct T_chain_action<CAN::lookup, CAT::non, filler...> :
			public T_chain_action<CAN::generic, CAT::catN_x_cat0, CAT::lookup, CAT::non, filler...> { };

/***********************************************************************************************************************/

// non:

	// recurse: (id recurse; allows the user to conceptualize composition before application)

		template<auto... filler>
		struct T_chain_action<CAN::non, CAT::recurse, filler...> :
			public T_chain_action<CAN::generic, CAT::cat0_x_catN, CAT::non, CAT::recurse, filler...> { };

	// list: (id list; allows the user to conceptualize composition before application)

		template<auto... filler>
		struct T_chain_action<CAN::non, CAT::list, filler...> :
			public T_chain_action<CAN::generic, CAT::cat0_x_catN, CAT::non, CAT::list, filler...> { };

	// arg: (id arg; allows the user to conceptualize composition before application)

		template<auto... filler>
		struct T_chain_action<CAN::non, CAT::arg, filler...> :
			public T_chain_action<CAN::generic, CAT::cat0_x_catN, CAT::non, CAT::arg, filler...> { };

	// lookup: (id lookup; allows the user to conceptualize composition before application)

		template<auto... filler>
		struct T_chain_action<CAN::non, CAT::lookup, filler...> :
			public T_chain_action<CAN::generic, CAT::cat0_x_catN, CAT::non, CAT::lookup, filler...> { };

	// non: (not applicable)

	// param: (not applicable)

/***********************************************************************************************************************/

// end:

	// id:

		template<auto... filler>
		struct T_chain_action<CAN::end, CAT::id, filler...>
		{
			nik_ces gindex_type offset =	 chain_action_offset< CAT::arg            > +
							      machine_offset< MAN::set , MAT::inc > ;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_drop, cindex note)
			{
				  chain_action< CAN::generic , CAT::arg >(contr, CT::drop, arg_drop);
				machine_action< MAN::set     , MAT::inc >(contr, CN::halt, note);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

