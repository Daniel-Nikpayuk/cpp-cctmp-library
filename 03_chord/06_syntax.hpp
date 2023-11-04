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

// syntax:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	template<auto U>
	using member_type_U					= cctmp::member_type_U<U>;

	template<typename Type, auto Size>
	using sequence						= cctmp::sequence<Type, Size>;

// machine:

	template<auto... Vs>
	using T_machine_contr					= machine::T_machine_contr<Vs...>;

	template<auto... Vs>
	using T_lookup_action					= machine::T_lookup_action<Vs...>;

	template<auto... Vs>
	using T_chain_action					= machine::T_chain_action<Vs...>;

	template<auto... Vs>
	using T_cycle_action					= machine::T_cycle_action<Vs...>;

	template<auto... Vs>
	using T_assembly_action					= machine::T_assembly_action<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// abstract syntax tree:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// entries:

/***********************************************************************************************************************/

// arg:

	template<typename CharType>
	struct T_arg_entry : public generator::T_icon<CharType>
	{
		using base	= generator::T_icon<CharType>;
		using cbase	= base const;

		nik_ce T_arg_entry() : base{} { }
	};

	using arg_entry = T_arg_entry<gchar_type>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tree:

/***********************************************************************************************************************/

// interface:

	template<auto static_scanned>
	struct T_chord_assembly_ast
	{
		using type			= T_chord_assembly_ast;
		using T_lexer			= T_chord_assembly_lexer;
		using Token			= typename T_lexer::Token;

		using scanned_type		= member_type_U<static_scanned>;
		using Total			= typename scanned_type::Total;
		using Cap			= typename scanned_type::Cap;

		nik_ces auto & src		= T_store_U<static_scanned>::src;
		nik_ces auto & scanned		= member_value_U<static_scanned>;
		nik_ces auto padding		= scanned.total[Total::pad];
		nik_ces auto stack_size		= 2;

		using contr_type		= T_machine_contr<100, stack_size>; // 100: debugging.
		using cindex			= typename contr_type::cindex;

		using arg_seq			= sequence<arg_entry, scanned.arg_size>;

		enum : gkey_type
		{
			rec_at = 0,
			str_at,
			env_at,

			dimension
		};

		contr_type contr;

		bool has_copy;
		bool has_paste;
		arg_entry name;
		arg_seq arg;

		gindex_type left;
		lexeme word;

		nik_ce T_chord_assembly_ast(cindex o = 10) : // o = 10 is temporary.
			contr{o}, has_copy{}, has_paste{}, left{} { }

		// copy/paste:

			nik_ce void set_copy          () { has_copy = true; }
			nik_ce void update_copy_paste () { has_paste = has_copy; has_copy = false; }

		//	nik_ce bool has_replace() const { return !has_copy && left; }
			nik_ce cindex paste_offset() const { return has_paste ? _one : _zero; }

		// name:

			nik_ce auto match_name  (clexeme *l) const { return name.same(l); }
			nik_ce void append_name (clexeme *l) { name.copy(l); }

		// arg:

			nik_ce auto arg_size   () const { return arg.size(); }
			nik_ce auto arg_offset () const { return arg.size() + padding; }

			nik_ce auto match_arguments(clexeme *l) const
				{ return arg.citerate().find(l->left_cselect()); }

			nik_ce void push_arg(clexeme *l)
			{
				arg.end()->copy(l);
				arg.upsize();
			}

			nik_ce void append_arg(clexeme *l)
			{
				auto k = match_arguments(l);

				if (k.is_end()) push_arg(l);
				else { } // error.
			}

		// (generic) action:

			template<auto name, auto note, typename... Ts>
			nik_ce void assembly_action(Ts... vs)
				{ T_assembly_action<name, note>::template result<>(&contr, vs...); }

			template<auto name, auto note, typename... Ts>
			nik_ce void chain_action(Ts... vs)
				{ T_chain_action<name, note>::template result<>(&contr, vs...); }

			template<auto name, auto note, typename... Ts>
			nik_ce void lookup_action(Ts... vs)
				{ T_lookup_action<name, note>::template result<>(&contr, vs...); }

		// (generic) lookup:

			nik_ce void begin_lookup(cindex name0, cindex note0, cindex name1, cindex note1)
			{
				contr.set_inc_instr(name0, note0, 1, env_at);
				contr.push_machine(name1, note1, str_at);

				contr.set_inc_instr(LN::id, LT::id);
			}

			nik_ce void end_lookup() { contr.pop_machine(); }

			nik_ce void find_lookup(clexeme *l)
			{
				cindex begin = l->cbegin() - src.cbegin();
				cindex end   = src.cend() - l->ccurrent();
				cindex halt  = contr.initial + 4; // redesign: read in?
				cindex loop  = contr.initial + 0; // redesign: read in?

				lookup_action< LAN::loop , LAT::id >(begin, end, halt, loop);
				lookup_action< LAN::halt , LAT::id >();
			}

		// (generic) chain:

			nik_ce void begin_chain(cindex name, cindex note)
			{
				contr.push_machine(name, note);

				contr.set_inc_instr(CN::id, CT::id);
			}

			nik_ce void end_chain() { contr.pop_machine(); }

			nik_ce void pull_chain(cindex index)
			{
				cindex arg_at = index + paste_offset();

				chain_action<CAN::arg, CAT::non>(arg_at);
			}

			nik_ce void push_chain(cindex index)
			{
				cindex arg_at = index + paste_offset();

				chain_action<CAN::non, CAT::arg>(arg_at);
			}

			nik_ce void arg_chain(cindex index)
			{
				push_chain(index);

				chain_action< CAN::drop , CAT::halting >(arg_offset());
				chain_action< CAN::base , CAT::halting >(CT::first);
			}

			nik_ce void name_chain()
			{
				chain_action< CAN::list , CAT::non     >(rec_at);
				chain_action< CAN::base , CAT::halting >(CT::front);
			}

		// (generic) assembly:

			nik_ce void origin_assembly() { contr.set_inc_instr(AN::id, AT::id); }

			nik_ce void begin_assembly_chain() { begin_chain(AN::chain, AT::call_f); }
			nik_ce void end_assembly_chain() { end_chain(); }

		// chain:

			nik_ce void begin_chain_lookup (cindex note) { begin_lookup(CN::list, CT::select, CN::lookup, note); }
			nik_ce void end_chain_lookup   () { end_lookup(); }

			nik_ce void find_chain_lookup(clexeme *l) { find_lookup(l); }

			nik_ce void cons_chain_lookup(clexeme *l, cindex note)
			{
				begin_chain_lookup(note);
				find_chain_lookup(l);
				end_chain_lookup();
			}

			nik_ce void identifier_chain(cindex index) { push_chain(index); }
			nik_ce void recurse_chain() { name_chain(); }

			nik_ce void maybe_chain_chain_lookup(clexeme *l, cindex note)
			{
				if (match_name(l)) recurse_chain();
				else cons_chain_lookup(l, note);
			}

		// assembly:

			nik_ce void begin_assembly_lookup () { begin_lookup(AN::select, AT::list, AN::lookup, AT::call_f); }
			nik_ce void end_assembly_lookup   () { end_lookup(); }

			nik_ce void find_assembly_lookup (clexeme *l) { find_lookup(l); }
			nik_ce void arg_assembly_chain   (cindex index) { arg_chain(index); }
			nik_ce void name_assembly_chain  () { name_chain(); }

			nik_ce void cons_assembly_lookup(clexeme *l)
			{
				begin_assembly_lookup();
				find_assembly_lookup(l);
				end_assembly_lookup();
			}

			nik_ce void identifier_assembly_chain(cindex index)
			{
				begin_assembly_chain();
				arg_assembly_chain(index);
				end_assembly_chain();
			}

			nik_ce void recurse_assembly_chain()
			{
				begin_assembly_chain();
				name_assembly_chain();
				end_assembly_chain();
			}

			nik_ce void maybe_assembly_chain_lookup(clexeme *l)
			{
				if (match_name(l)) recurse_assembly_chain();
				else cons_assembly_lookup(l);
			}

			nik_ce void replace_assembly_arg()
			{
			//	if (has_replace())
				if (!has_copy)
				{
					contr.set_inc_instr(AN::reselect, AT::id, 1, left);
					contr.set_inc_instr(AN::replace, AT::id);
				}
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

