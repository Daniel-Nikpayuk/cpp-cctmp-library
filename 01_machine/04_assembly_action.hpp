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

// action:

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

			generic,
			aatN, aat0_x_aatN, aat1_x_aatN, aat2_x_aatN,
			list, arg, lookup, literal,
			back,

			pad,
			go_to, branch, invert,
			eval,

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
			list, arg, lookup, literal,
			replace,
			begin, end,
			variable, parameter,
			dimension
		};

	}; using AAT = AssemblyActionNote;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

/***********************************************************************************************************************/

// generic:

	// list:

		template<auto... filler>
		struct T_assembly_action<AAN::generic, AAT::list, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex list_at)
				{ machine_action<MAN::push, MAT::instr>(contr, AN::list, note, list_at); }
		};

	// arg:

		template<auto... filler>
		struct T_assembly_action<AAN::generic, AAT::arg, filler...>
		{
			using cindex = gcindex_type;
			using cbool  = gcbool_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex arg_at, cbool mutate = false)
			{
				machine_action<MAN::push, MAT::instr>(contr, AN::arg, AT::select, arg_at);
				machine_action<MAN::push, MAT::instr>(contr, AN::arg, note, mutate);
			}
		};

	// lookup:

		template<auto... filler>
		struct T_assembly_action<AAN::generic, AAT::lookup, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex pos, cindex num)
				{ machine_action<MAN::push, MAT::instr>(contr, AN::lookup, note, pos, num); }
		};

	// literal:

		template<auto... filler>
		struct T_assembly_action<AAN::generic, AAT::literal, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note0, cindex str_at, cindex note1, cindex begin, cindex end)
			{
				machine_action< MAN::delay   , MAT::call >(contr, AN::literal, note0, str_at);
				literal_action< LAN::resolve , LAT::id   >(contr, note1, begin, end);
				machine_action< MAN::force   , MAT::call >(contr);
			}

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note0, cindex note1, cindex begin, cindex end)
				{ result(contr, note0, contr->src_at, note1, begin, end); }
		};

/***********************************************************************************************************************/

// pairs:

	// aatN:

		template<gkey_type note0, gkey_type note1, auto... filler>
		struct T_assembly_action<AAN::aatN, note0, note1, filler...>
		{
			template<typename Contr, typename... Ts>
			nik_ces void result(Contr *contr, Ts... vs)
				{ assembly_action<AAN::generic, note0>(contr, note1, vs...); }
		};

	// aat0 x aatN:

		template<gkey_type note0, gkey_type note1, auto... filler>
		struct T_assembly_action<AAN::aat0_x_aatN, note0, note1, filler...>
		{
			template<typename Contr, typename... Ts>
			nik_ces void result(Contr *contr, Ts... vs)
			{
				assembly_action<AAN::generic, note0>(contr, AT::back);
				assembly_action<AAN::generic, note1>(contr, AT::back, vs...);
			}
		};

	// aat1 x aatN:

		template<gkey_type note0, gkey_type note1, auto... filler>
		struct T_assembly_action<AAN::aat1_x_aatN, note0, note1, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr, typename... Ts>
			nik_ces void result(Contr *contr, cindex v0, Ts... vs)
			{
				assembly_action<AAN::generic, note0>(contr, AT::back, v0);
				assembly_action<AAN::generic, note1>(contr, AT::back, vs...);
			}
		};

	// aat2 x aatN:

		template<gkey_type note0, gkey_type note1, auto... filler>
		struct T_assembly_action<AAN::aat2_x_aatN, note0, note1, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr, typename... Ts>
			nik_ces void result(Contr *contr, cindex v0, cindex v1, Ts... vs)
			{
				assembly_action<AAN::generic, note0>(contr, AT::back, v0, v1);
				assembly_action<AAN::generic, note1>(contr, AT::back, vs...);
			}
		};

/***********************************************************************************************************************/

// list:

	// list, arg, lookup, literal:

		template<gkey_type note, auto... filler>
		struct T_assembly_action<AAN::list, note, filler...> :
			public T_assembly_action<AAN::aat1_x_aatN, AAT::list, note, filler...> { };

/***********************************************************************************************************************/

// arg:

	// list, arg, lookup, literal:

		template<gkey_type note, auto... filler>
		struct T_assembly_action<AAN::arg, note, filler...> :
			public T_assembly_action<AAN::aat1_x_aatN, AAT::arg, note, filler...> { };

/***********************************************************************************************************************/

// lookup:

	// list, arg, lookup, literal:

		template<gkey_type note, auto... filler>
		struct T_assembly_action<AAN::lookup, note, filler...> :
			public T_assembly_action<AAN::aat2_x_aatN, AAT::lookup, note, filler...> { };

/***********************************************************************************************************************/

// back:

	// list, arg, lookup, literal:

		template<gkey_type note, auto... filler>
		struct T_assembly_action<AAN::back, note, filler...> :
			public T_assembly_action<AAN::aatN, note, AT::back, filler...> { };

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

// goto:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::go_to, AAT::id, filler...>
		{
			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::push, MAT::instr>(contr, AN::go_to, AT::id); }
		};

	// begin:

		template<auto... filler>
		struct T_assembly_action<AAN::go_to, AAT::begin, filler...>
		{
			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ machine_action<MAN::delay, MAT::jump>(contr, AN::go_to, AT::id); }
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
				{ machine_action<MAN::delay, MAT::jump>(contr, AN::branch, AT::id); }
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
				{ machine_action<MAN::delay, MAT::jump>(contr, AN::invert, AT::id); }
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

// eval:

	// begin:

		template<auto... filler>
		struct T_assembly_action<AAN::eval, AAT::begin, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
			{
				 machine_action< MAN::delay , MAT::call  >(contr, AN::eval, note);
				assembly_action< AAN::id    , AAT::begin >(contr);
			}
		};

	// end:

		template<auto... filler>
		struct T_assembly_action<AAN::eval, AAT::end, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_drop, cindex note)
			{
				if (arg_drop)
				assembly_action< AAN::generic , AAT::arg  >(contr, AT::drop, arg_drop);

				assembly_action< AAN::id      , AAT::end  >(contr, note);
				 machine_action< MAN::force   , MAT::call >(contr);
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
			nik_ces void result(Contr *contr,
				cindex note0, cindex str_at, cindex note1, cindex begin, cindex end)
			{
				assembly_action< AAN::eval    , AAT::begin   >(contr, note0);
				assembly_action< AAN::generic , AAT::literal >(contr, AT::first, str_at, note1, begin, end);
				assembly_action< AAN::eval    , AAT::end     >(contr, arg_drop, AT::first);
			}

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note0, cindex note1, cindex begin, cindex end)
				{ result(contr, note0, contr->src_at, note1, begin, end); }
		};

/***********************************************************************************************************************/

// lookup:

	// variable:

		template<auto... filler>
		struct T_assembly_action<AAN::lookup, AAT::variable, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex pos)
			{
				assembly_action< AAN::eval , AAT::begin >(contr, note);
				assembly_action< AAN::eval , AAT::end   >(contr, pos, AT::first);
			}
		};

	// parameter:

		template<auto... filler>
		struct T_assembly_action<AAN::lookup, AAT::parameter, filler...>
		{
			using cindex = gcindex_type;

			nik_ces cindex arg_drop = 0;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex pos, cindex num)
			{
				assembly_action< AAN::eval    , AAT::begin  >(contr, note);
				assembly_action< AAN::generic , AAT::lookup >(contr, AT::first, pos, num);
				assembly_action< AAN::eval    , AAT::end    >(contr, arg_drop, AT::first);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

