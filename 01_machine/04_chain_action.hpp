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

// chain action:

namespace machine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

/***********************************************************************************************************************/

// generic:

	// list:

		template<auto... filler>
		struct T_chain_action<CAN::generic, CAT::list, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex list_at)
				{ machine_action<MAN::push, MAT::instr>(contr, CN::list, note, list_at); }
		};

	// arg:

		template<auto... filler>
		struct T_chain_action<CAN::generic, CAT::arg, filler...>
		{
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

		template<auto... filler>
		struct T_chain_action<CAN::generic, CAT::literal, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note0, cindex str_at, cindex note1, cindex begin, cindex end)
			{
				machine_action< MAN::delay   , MAT::call >(contr, CN::literal, note0, str_at);
				literal_action< LAN::resolve , LAT::id   >(contr, note1, begin, end);
				machine_action< MAN::force   , MAT::call >(contr);
			}

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note0, cindex note1, cindex begin, cindex end)
				{ result(contr, note0, contr->src_at, note1, begin, end); }
		};

	// lookup:

		template<auto... filler>
		struct T_chain_action<CAN::generic, CAT::lookup, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex pos, cindex num)
			{
				machine_action<MAN::push, MAT::instr>(contr, CN::list, CT::push, contr->env_at);
				machine_action<MAN::push, MAT::instr>(contr, CN::lookup, note, pos, num);
			}
		};

/***********************************************************************************************************************/

// pairs:

	// catN:

		template<gkey_type note0, gkey_type note1, auto... filler>
		struct T_chain_action<CAN::catN, note0, note1, filler...>
		{
			template<typename Contr, typename... Ts>
			nik_ces void result(Contr *contr, Ts... vs)
				{ chain_action<CAN::generic, note0>(contr, note1, vs...); }
		};

	// cat0 x catN:

		template<gkey_type note0, gkey_type note1, auto... filler>
		struct T_chain_action<CAN::cat0_x_catN, note0, note1, filler...>
		{
			template<typename Contr, typename... Ts>
			nik_ces void result(Contr *contr, Ts... vs)
			{
				chain_action<CAN::generic, note0>(contr, CT::push);
				chain_action<CAN::generic, note1>(contr, CT::back, vs...);
			}
		};

	// cat1 x catN:

		template<gkey_type note0, gkey_type note1, auto... filler>
		struct T_chain_action<CAN::cat1_x_catN, note0, note1, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr, typename... Ts>
			nik_ces void result(Contr *contr, cindex v0, Ts... vs)
			{
				chain_action<CAN::generic, note0>(contr, CT::push, v0);
				chain_action<CAN::generic, note1>(contr, CT::back, vs...);
			}
		};

	// cat2 x catN:

		template<gkey_type note0, gkey_type note1, auto... filler>
		struct T_chain_action<CAN::cat2_x_catN, note0, note1, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr, typename... Ts>
			nik_ces void result(Contr *contr, cindex v0, cindex v1, Ts... vs)
			{
				chain_action<CAN::generic, note0>(contr, CT::push, v0, v1);
				chain_action<CAN::generic, note1>(contr, CT::back, vs...);
			}
		};

/***********************************************************************************************************************/

// id:

	// begin:

		template<auto... filler>
		struct T_chain_action<CAN::id, CAT::begin, filler...>
		{
			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::push, MAT::instr>(contr, CN::id, CT::id); }
		};

	// end:

		template<auto... filler>
		struct T_chain_action<CAN::id, CAT::end, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
				{ machine_action<MAN::push, MAT::instr>(contr, CN::halt, note); }
		};

/***********************************************************************************************************************/

// apply:

	// begin:

		template<auto... filler>
		struct T_chain_action<CAN::apply, CAT::begin, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
			{
				machine_action<MAN::delay , MAT::call  >(contr, CN::sub_chain, note);
				  chain_action<CAN::id    , CAT::begin >(contr);
			}
		};

	// end:

		template<auto... filler>
		struct T_chain_action<CAN::apply, CAT::end, filler...>
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
		struct T_chain_action<CAN::eval, CAT::begin, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
			{
				 machine_action< MAN::delay , MAT::call  >(contr, CN::sub_asm, note);
				assembly_action< AAN::eval  , AAT::begin >(contr);
			}
		};

	// end:

		template<auto... filler>
		struct T_chain_action<CAN::eval, CAT::end, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
			{
				assembly_action< AAN::eval  , AAT::end  >(contr, note);
				 machine_action< MAN::force , MAT::call >(contr);
			}
		};

/***********************************************************************************************************************/

// pull:

	// list, arg, lookup:

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::pull, note, filler...> :
			public T_chain_action<CAN::catN, note, CT::pull, filler...> { };

/***********************************************************************************************************************/

// push:

	// list, arg, lookup:

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::push, note, filler...> :
			public T_chain_action<CAN::catN, note, CT::push, filler...> { };

/***********************************************************************************************************************/

// back:

	// list, arg, literal, lookup:

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::back, note, filler...> :
			public T_chain_action<CAN::catN, note, CT::back, filler...> { };

/***********************************************************************************************************************/

// list:

	// list, arg, literal, lookup:

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::list, note, filler...> :
			public T_chain_action<CAN::cat1_x_catN, CAT::list, note, filler...> { };

/***********************************************************************************************************************/

// arg:

	// list, arg, literal, lookup:

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::arg, note, filler...> :
			public T_chain_action<CAN::cat1_x_catN, CAT::arg, note, filler...> { };

/***********************************************************************************************************************/

// lookup:

	// list, arg, literal, lookup:

		template<gkey_type note, auto... filler>
		struct T_chain_action<CAN::lookup, note, filler...> :
			public T_chain_action<CAN::cat2_x_catN, CAT::lookup, note, filler...> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

