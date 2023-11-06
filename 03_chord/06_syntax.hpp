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
			contr{rec_at, str_at, env_at, o}, has_copy{}, has_paste{}, left{} { }

		// copy/paste:

			nik_ce void set_copy          () { has_copy = true; }
			nik_ce void update_copy_paste () { has_paste = has_copy; has_copy = false; }

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

		// lexeme:

			nik_ce auto lexeme_start  (clexeme *l) const { return l->cbegin() - src.cbegin(); }
			nik_ce auto lexeme_finish (clexeme *l) const { return src.cend() - l->ccurrent(); }

		// (generic) action:

			template<auto name, auto note, typename... Ts>
			nik_ce void lookup_action(Ts... vs) { machine::lookup_action<name, note>(&contr, vs...); }

			template<auto name, auto note, typename... Ts>
			nik_ce void chain_action(Ts... vs) { machine::chain_action<name, note>(&contr, vs...); }

			template<auto name, auto note, typename... Ts>
			nik_ce void assembly_action(Ts... vs) { machine::assembly_action<name, note>(&contr, vs...); }

		// op:

			nik_ce void op_identifier(cindex index)
			{
				cindex op_at = index + paste_offset();

				chain_action<CAN::arg, CAT::non>(op_at);
			}

			nik_ce void op_recurse() { chain_action<CAN::recurse, CAT::non>(); }

			nik_ce void op_lookup(clexeme *l)
			{
				cindex start  = lexeme_start(l);
				cindex finish = lexeme_finish(l);

				chain_action<CAN::lookup, CAT::non>(start, finish);
			}

			nik_ce void op_action()
			{
				clexeme *l = &word;
				auto k = match_arguments(l);

				if      (k.not_end())   op_identifier(k.left_size());
				else if (match_name(l)) op_recurse();
				else                    op_lookup(l);
			}

		// value:

			nik_ce void value_identifier(cindex index)
			{
				cindex value_at = index + paste_offset();

				chain_action<CAN::non, CAT::arg>(value_at);
			}

			nik_ce void value_recurse() { chain_action<CAN::non, CAT::recurse>(); }

			nik_ce void value_lookup(clexeme *l)
			{
				cindex start  = lexeme_start(l);
				cindex finish = lexeme_finish(l);

				chain_action<CAN::non, CAT::lookup>(start, finish);
			}

			nik_ce void value_action(clexeme *l)
			{
				auto k = match_arguments(l);

				if      (k.not_end())   value_identifier(k.left_size());
				else if (match_name(l)) value_recurse();
				else                    value_lookup(l);
			}

		// unit:

			nik_ce void unit_identifier(cindex index)
			{
				cindex unit_at = index + paste_offset();

				assembly_action<AAN::unit, AAT::value>(unit_at);
			}

			nik_ce void unit_recurse() { assembly_action<AAN::unit, AAT::recurse>(); }

			nik_ce void unit_lookup(clexeme *l)
			{
				cindex start  = lexeme_start(l);
				cindex finish = lexeme_finish(l);

				assembly_action<AAN::unit, AAT::lookup>(start, finish);
			}

			nik_ce void unit_action(clexeme *l)
			{
				auto k = match_arguments(l);

				if      (k.not_end())   unit_identifier(k.left_size());
				else if (match_name(l)) unit_recurse();
				else                    unit_lookup(l);
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

