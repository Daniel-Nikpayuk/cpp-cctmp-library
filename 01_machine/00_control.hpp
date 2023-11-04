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

		gindex_type initial;
		gindex_type current;
		gindex_type free;
		gindex_type offset;

		stack_type init_stack; 
		stack_type curr_stack; 

		nik_ce T_machine_contr(cindex o) :

			base{}, initial{}, current{}, free{o}, offset{o}, init_stack{}, curr_stack{}

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

			nik_ce void set_inc_instr(cindex name, cindex note, cindex next = 1, cindex pos = 0, cindex num = 0)
			{
				set_instr(name, note, next, pos, num);
				inc_instr();
			}

		// machine:

			nik_ce void push_machine(cindex name, cindex note, cindex num = 0)
			{
				set_inc_instr(name, note, 1, free, num);

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

// base:

/*
	template<gindex_type length>
	struct T_chain_subpose_env_contr : public sequence<instr_type, length>
	{
		using base		= sequence<instr_type, length>;
		using cindex		= gcindex_type;

		template<auto name, auto note>
		nik_ces auto action = chain_action_f<name, note, T_chain_subpose_env_contr>;

		template<auto name, auto note>
		nik_ces auto lookup_action = lookup_action_f<name, note, T_chain_subpose_env_contr>;

		gcbool_type *is_id;
		gindex_type arg_size;
		gindex_type subindex;
		gindex_type begin;
		gindex_type end;

		nik_ce T_chain_subpose_env_contr(gcbool_type *ii, cindex s, cindex b = 0, cindex e = 0) :
			base{}, is_id{ii}, arg_size{s}, subindex{}, begin{b}, end{e}
			{
				add_initial_instrs   ();
				add_composand_instrs ();
				add_composer_instrs  ();
				add_halting_instrs   ();

				add_lookup_contr     ();
			}

		nik_ce void add_instr(cindex name, cindex note, cindex next = 1, cindex pos = 0, cindex num = 0)
		{
			base::end()->push(name);
			base::end()->push(note);
			base::end()->push(next);
			base::end()->push(pos);
			base::end()->push(num);

			base::upsize();
		}

		nik_ce void add_initial_instrs() { action<CAN::base, CAT::id>(this); }

		nik_ce void add_composand_instrs()
		{
			for (gindex_type k = 0; k != arg_size; ++k)
				if (is_id[k]) add_id_composand_instr(k);
				else add_not_id_composand_instr(k);
		}

		nik_ce void add_id_composand_instr    (cindex k) { action<CAN::non, CAT::arg>(this, k); }
		nik_ce void add_not_id_composand_instr(cindex k) { action<CAN::list, CAT::arg>(this, k, k); }

		nik_ce void add_composer_instrs()
		{
			subindex = 1 + 3*arg_size + 2 + 2 + 1;
			action<CAN::lookup, CAT::non>(this, arg_size + 1, subindex, arg_size);
		}

		nik_ce void add_halting_instrs()
		{
			action<CAN::drop, CAT::halting>(this, arg_size);
			action<CAN::base, CAT::halting>(this, CT::apply);
		}

		// lookup:

		nik_ce void add_lookup_contr()
		{
			lookup_action<LAN::base, LAN::id>(this);

			cindex halt = subindex + 4;
			cindex loop = subindex + 0;

			lookup_action<LAN::loop, LAN::id>(this, begin, end, halt, loop);

			lookup_action<LAN::halt, LAN::id>(this);
		}
	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

