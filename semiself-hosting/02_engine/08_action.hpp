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

// action:

namespace cctmp  {
namespace engine {

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

			push, delay, force, generic,
			arg, lookup, literal,
			pad, eval, back, replace,
			go_to, branch, invert,

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
			instr, jump, call,
			arg, lookup, literal,
			replace, begin, end,
			variable, parameter,
			dimension
		};

	}; using AAT = AssemblyActionNote;

/***********************************************************************************************************************/

// push:

	// instr:

		template<auto... filler>
		struct T_assembly_action<AAN::push, AAT::instr, filler...> :
			public T_machine_action<MAN::push, MAT::instr> { };

/***********************************************************************************************************************/

// delay:

	// jump:

		template<auto... filler>
		struct T_assembly_action<AAN::delay, AAT::jump, filler...> :
			public T_machine_action<MAN::delay, MAT::jump> { };

	// call:

		template<auto... filler>
		struct T_assembly_action<AAN::delay, AAT::call, filler...> :
			public T_machine_action<MAN::delay, MAT::call> { };

/***********************************************************************************************************************/

// force:

	// jump:

		template<auto... filler>
		struct T_assembly_action<AAN::force, AAT::jump, filler...> :
			public T_machine_action<MAN::force, MAT::jump> { };

	// call:

		template<auto... filler>
		struct T_assembly_action<AAN::force, AAT::call, filler...> :
			public T_machine_action<MAN::force, MAT::call> { };

/***********************************************************************************************************************/

// generic:

	// arg:

		template<auto... filler>
		struct T_assembly_action<AAN::generic, AAT::arg, filler...>
		{
			using cindex = gcindex_type;
			using cbool  = gcbool_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex arg_at)
			{
				assembly_action<AAN::push, AAT::instr>(contr, AN::arg, AT::select, arg_at);
				assembly_action<AAN::push, AAT::instr>(contr, AN::arg, note);
			}
		};

	// lookup:

		template<auto... filler>
		struct T_assembly_action<AAN::generic, AAT::lookup, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex pos, cindex num)
				{ assembly_action<AAN::push, AAT::instr>(contr, AN::lookup, note, pos, num); }
		};

/***********************************************************************************************************************/

// pad:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::pad, AAT::id, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_at, cindex pad_size)
			{
				assembly_action<AAN::push, AAT::instr>(contr, AN::pad, AT::select, arg_at, pad_size);
				assembly_action<AAN::push, AAT::instr>(contr, AN::pad, AT::id);
			}
		};

/***********************************************************************************************************************/

// id:

	// begin:

		template<auto... filler>
		struct T_assembly_action<AAN::id, AAT::begin, filler...>
		{
			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ assembly_action<AAN::push, AAT::instr>(contr, AN::id, AT::id); }
		};

	// end:

		template<auto... filler>
		struct T_assembly_action<AAN::id, AAT::end, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note)
				{ assembly_action<AAN::push, AAT::instr>(contr, AN::halt, note); }
		};

/***********************************************************************************************************************/

// literal:

	// begin:

	//	template<auto... filler>
	//	struct T_assembly_action<AAN::literal, AAT::begin, filler...>
	//	{
	//		using cindex = gcindex_type;

	//		template<typename Contr>
	//		nik_ces void result(Contr *contr, cindex note, cindex str_at)
	//		{
	//			assembly_action< AAN::delay , AAT::call  >(contr, AN::literal, note, str_at);
	//			assembly_action< AAN::id    , AAT::begin >(contr);
	//		}
	//	};

	// end:

	//	template<auto... filler>
	//	struct T_assembly_action<AAN::literal, AAT::end, filler...>
	//	{
	//		using cindex = gcindex_type;

	//		template<typename Contr>
	//		nik_ces void result(Contr *contr, cindex arg_drop, cindex note)
	//		{
	//			if (arg_drop)
	//			assembly_action< AAN::generic , AAT::arg  >(contr, AT::drop, arg_drop);

	//			assembly_action< AAN::id      , AAT::end  >(contr, note);
	//			assembly_action< AAN::force   , AAT::call >(contr);
	//		}
	//	};

	// id:

	//	template<auto... filler>
	//	struct T_assembly_action<AAN::literal, AAT::id, filler...>
	//	{
	//		using cindex = gcindex_type;

	//		nik_ces cindex arg_drop = 0;

	//		template<typename Contr>
	//		nik_ces void result(Contr *contr,
	//			cindex note, cindex str_at, cindex name, cindex begin, cindex end)
	//		{
	//			assembly_action< AAN::literal , AAT::begin >(contr, note, str_at);
	//			assembly_action< AAN::solve   , AAT::id    >(contr, name, begin, end);
	//			assembly_action< AAN::literal , AAT::end   >(contr, arg_drop, AT::first);
	//		}

	//		template<typename Contr>
	//		nik_ces void result(Contr *contr, cindex note, cindex name, cindex begin, cindex end)
	//			{ result(contr, note, contr->src_at, name, begin, end); }
	//	};

	// literal:

	//	template<auto... filler>
	//	struct T_assembly_action<AAN::literal, AAT::literal, filler...>
	//	{
	//		using cindex = gcindex_type;

	//		nik_ces cindex arg_drop = 0;

	//		template<typename Contr>
	//		nik_ces void result(Contr *contr,
	//			cindex note, cindex str_at, cindex typ_at, cindex name, cindex begin, cindex end)
	//		{
	//			assembly_action< AAN::literal , AAT::begin >(contr, note, str_at);
	//			assembly_action< AAN::resolve , AAT::id    >(contr, typ_at, name, begin, end);
	//			assembly_action< AAN::literal , AAT::end   >(contr, arg_drop, AT::first);
	//		}

	//		template<typename Contr>
	//		nik_ces void result(Contr *contr,
	//			cindex note, cindex typ_at, cindex name, cindex begin, cindex end)
	//				{ result(contr, note, contr->src_at, typ_at, name, begin, end); }
	//	};

/***********************************************************************************************************************/

// eval:

	// begin:

		template<auto... filler>
		struct T_assembly_action<AAN::eval, AAT::begin, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex mute)
			{
				assembly_action< AAN::delay , AAT::call  >(contr, AN::eval, note, mute);
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
				assembly_action< AAN::force   , AAT::call >(contr);
			}
		};

/***********************************************************************************************************************/

// lookup:

	// variable:

		template<auto... filler>
		struct T_assembly_action<AAN::lookup, AAT::variable, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex mute, cindex pos)
			{
				assembly_action< AAN::eval , AAT::begin >(contr, note, mute);
				assembly_action< AAN::eval , AAT::end   >(contr, pos, AT::first);
			}
		};

	// parameter:

		template<auto... filler>
		struct T_assembly_action<AAN::lookup, AAT::parameter, filler...>
		{
			using cindex = gcindex_type;

			nik_ces cindex mute     = 0;
			nik_ces cindex arg_drop = 0;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex pos, cindex num)
			{
				assembly_action< AAN::eval    , AAT::begin  >(contr, note, mute);
				assembly_action< AAN::generic , AAT::lookup >(contr, AT::first, pos, num);
				assembly_action< AAN::eval    , AAT::end    >(contr, arg_drop, AT::first);
			}
		};

/***********************************************************************************************************************/

// replace:

	// id:

		template<auto... filler>
		struct T_assembly_action<AAN::replace, AAT::id, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex arg_at)
			{
				assembly_action<AAN::push, AAT::instr>(contr, AN::arg, AT::select, arg_at);
				assembly_action<AAN::push, AAT::instr>(contr, AN::arg, AT::replace);
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
				{ assembly_action<AAN::push, AAT::instr>(contr, AN::go_to, AT::id); }
		};

	// begin:

		template<auto... filler>
		struct T_assembly_action<AAN::go_to, AAT::begin, filler...>
		{
			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ assembly_action<AAN::delay, AAT::jump>(contr, AN::go_to, AT::id); }
		};

	// end:

		template<auto... filler>
		struct T_assembly_action<AAN::go_to, AAT::end, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex offset = 0)
				{ assembly_action<AAN::force, AAT::jump>(contr, offset); }
		};

/***********************************************************************************************************************/

// branch:

	// begin:

		template<auto... filler>
		struct T_assembly_action<AAN::branch, AAT::begin, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex num = 0)
				{ assembly_action<AAN::delay, AAT::jump>(contr, AN::branch, note); }
		};

	// end:

		template<auto... filler>
		struct T_assembly_action<AAN::branch, AAT::end, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex offset = 0)
				{ assembly_action<AAN::force, AAT::jump>(contr, offset); }
		};

/***********************************************************************************************************************/

// invert:

	// begin:

		template<auto... filler>
		struct T_assembly_action<AAN::invert, AAT::begin, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex note, cindex num = 0)
				{ assembly_action<AAN::delay, AAT::jump>(contr, AN::invert, note); }
		};

	// end:

		template<auto... filler>
		struct T_assembly_action<AAN::invert, AAT::end, filler...>
		{
			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex offset = 0)
				{ assembly_action<AAN::force, AAT::jump>(contr, offset); }
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::engine

