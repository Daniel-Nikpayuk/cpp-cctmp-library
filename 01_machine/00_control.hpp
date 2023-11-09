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

// control:

namespace machine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	using gkey_type						= cctmp::gkey_type;
	using gindex_type					= cctmp::gindex_type;
	using gcindex_type					= cctmp::gcindex_type;

	template<typename Type, auto Size>
	using sequence						= cctmp::sequence<Type, Size>;

	using Instr						= cctmp::Instr;
	using instr_type					= cctmp::instr_type;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

/***********************************************************************************************************************/

// stack:

	template<gindex_type size>
	struct T_machine_stack : public sequence<gindex_type, size>
	{
		using base	= sequence<gindex_type, size>;
		using cindex	= gcindex_type;

		gindex_type current;

		nik_ce T_machine_stack() : current{} { }

		nik_ce void push(cindex value)
		{
			current += base::not_empty();
			base::push(value);
		}

		nik_ce auto pop()
		{
			auto value = base::operator [] (current);

			base::downsize(base::not_empty());
			current -= base::not_empty();

			return value;
		}
	};

/***********************************************************************************************************************/

// interface:

	template<gindex_type length, gindex_type size>
	struct T_machine_contr : public sequence<instr_type, length>
	{
		using base		= sequence<instr_type, length>;
		using cindex		= gcindex_type;
		using stack_type	= T_machine_stack<size>;

		cindex rec_at;
		cindex str_at;
		cindex env_at;

		gindex_type initial;
		gindex_type current;
		gindex_type free;
		gindex_type offset;

		stack_type init_stack; 
		stack_type curr_stack; 

		nik_ce T_machine_contr(cindex r, cindex s, cindex e, cindex f, cindex o) :

			base{}, rec_at{r}, str_at{s}, env_at{e},
			initial{}, current{}, free{f}, offset{o}, init_stack{}, curr_stack{}

			{ base::fullsize(); }

		// instr:

			nik_ce void inc_instr() { ++current; }

			nik_ce void set_instr(cindex name, cindex note, cindex next = 1, cindex pos = 0, cindex num = 0)
			{
				base::operator [] (current)[Instr::name] = name;
				base::operator [] (current)[Instr::note] = note;
				base::operator [] (current)[Instr::next] = next;
				base::operator [] (current)[Instr::pos ] = pos ;
				base::operator [] (current)[Instr::num ] = num ;
			}

		// machine:

			nik_ce void push_machine()
			{
				init_stack.push(initial);
				curr_stack.push(current);

				initial  = free;
				current  = free;
				free    += offset;
			}

			nik_ce void pop_machine()
			{
				initial = init_stack.pop();
				current = curr_stack.pop();
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// action:

	template<gkey_type, gkey_type, auto...> struct T_machine_action;

	// syntactic sugar:

		template<auto name, auto note, typename... Ts>
		nik_ce auto machine_action(Ts... vs) // requires template deduction <>:
			{ return T_machine_action<name, note>::template result<>(vs...); }

		template<auto name, auto note>
		nik_ce auto machine_offset = T_machine_action<name, note>::offset;

/***********************************************************************************************************************/

// names:

	struct MachineActionName
	{
		enum : gkey_type // convenience for default params.
			{ identity = 0, id = identity, set, push, pop, dimension };

	}; using MAN = MachineActionName;

/***********************************************************************************************************************/

// notes:

	struct MachineActionNote
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			inc, dimension
		};

	}; using MAT = MachineActionNote;

/***********************************************************************************************************************/

// instructions:

//	struct MachineActionInstr
//	{
//		enum : gkey_type { pos0 = 0, pos1, pos2, pos3, dimension };
//		enum : gkey_type { name = 0, note };

//	}; using MAI = MachineActionInstr;

/***********************************************************************************************************************/

// offset:

//	using MachineActionOffset = cctmp::ActionOffset;
//	using MAO                 = cctmp::ActionOffset;

/***********************************************************************************************************************/

// size:

//	using T_machine_contr_size = cctmp::T_contr_size<T_machine_action, LAI, LAO>;

/***********************************************************************************************************************/

// set:

	// inc:

		template<auto... filler>
		struct T_machine_action<MAN::set, MAT::inc, filler...>
		{
			nik_ces gindex_type offset = 1;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr,
				cindex name, cindex note, cindex next = 1, cindex pos = 0, cindex num = 0)
			{
				contr->set_instr(name, note, next, pos, num);
				contr->inc_instr();
			}
		};

/***********************************************************************************************************************/

// push:

	// id:

		template<auto... filler>
		struct T_machine_action<MAN::push, MAT::id, filler...>
		{
			nik_ces gindex_type offset = 1;

			using cindex = gcindex_type;

			template<typename Contr>
			nik_ces void result(Contr *contr, cindex name, cindex note, cindex num = 0)
			{
				contr->set_instr(name, note, 1, contr->free, num);
				contr->inc_instr();
				contr->push_machine();
			}
		};

/***********************************************************************************************************************/

// pop:

	// id:

		template<auto... filler>
		struct T_machine_action<MAN::pop, MAT::id, filler...>
		{
			nik_ces gindex_type offset = 0;

			template<typename Contr>
			nik_ces void result(Contr *contr)
				{ contr->pop_machine(); }
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

