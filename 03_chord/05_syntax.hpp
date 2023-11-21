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
	using T_store_U						= cctmp::T_store_U<U>;

	template<auto U>
	using member_type_U					= cctmp::member_type_U<U>;

	template<typename Type, auto Size>
	using sequence						= cctmp::sequence<Type, Size>;

// machine:

	template<auto... Vs>
	using T_machine_contr					= machine::T_machine_contr<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// abstract syntax tree:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// signature:

/***********************************************************************************************************************/

// entry:

	template<typename CharType>
	struct T_signature_entry : public generator::T_icon<CharType>
	{
		using base	= generator::T_icon<CharType>;
		using cbase	= base const;

		bool compound;
		gindex_type proc_pos;

		nik_ce T_signature_entry() : base{}, compound{}, proc_pos{} { }

		// compound:

			nik_ce bool is_compound() const { return compound; }
			nik_ce void set_compound() { compound = true; }

		// procedure:

			nik_ce gcindex_type proc_at() const { return proc_pos; }
			nik_ce void set_proc(gcindex_type n) { proc_pos = n; }
	};

	using signature_entry = T_signature_entry<gchar_type>;

/***********************************************************************************************************************/

// interface:

	template<typename CharType, gindex_type Size>
	struct T_signature : public sequence<T_signature_entry<CharType>, Size>
	{
		using entry	= T_signature_entry<CharType>;
		using base	= sequence<entry, Size>;
		using cbase	= base const;

		gcindex_type pad;
		entry name;

		nik_ce T_signature(gcindex_type p) : base{}, pad{p} { }

		// name:

			nik_ce auto match_name (clexeme *l) const { return name.same(l); }
			nik_ce void push_name  (clexeme *l) { name.copy(l); }

		// arg:

			nik_ce auto anon_at  () const { return Size; }
			nik_ce auto padding  () const { return pad + 1; } // + anon.
			nik_ce auto dropsize () const { return Size + 1; } // + anon.

			nik_ce auto match(clexeme *l) const
				{ return base::citerate().find(l->left_cselect()); }

			nik_ce void push(clexeme *l)
			{
				base::end()->copy(l);
				base::upsize();
			}

			nik_ce void append(clexeme *l)
			{
				auto k = match(l);

				if (k.is_end()) push(l);
				else { } // error.
			}
	};

	template<auto Size>
	using signature = T_signature<gchar_type, Size>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// procedure:

/***********************************************************************************************************************/

// capture:

	template<gindex_type Size>
	struct T_capture : public sequence<gindex_type, Size>
	{
		using base	= sequence<gindex_type, Size>;
		using cbase	= base const;

		gindex_type arg_size;

		nik_ce T_capture() : base{}, arg_size{} { }

		// arity:

			nik_ce void set_arity(gcindex_type n) { arg_size = n; }
			nik_ce gcindex_type arity() const { return arg_size; }
	};

/***********************************************************************************************************************/

// interface:

	template<gindex_type Subsize, gindex_type Size>
	struct T_procedure : public sequence<T_capture<Subsize>, Size>
	{
		using entry	= T_capture<Subsize>;
		using base	= sequence<entry, Size>;
		using cbase	= base const;

		nik_ce T_procedure() : base{} { }

		nik_ce gcindex_type add() { base::upsize(); return base::max(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// value:

/***********************************************************************************************************************/

// interface:

	template<typename Type>
	class T_value
	{
		public:

			using cindex = Type;

			struct Kind { enum : gkey_type { id = 0, sign, recurse, lookup, dimension }; };

		private:

			gindex_type order;
			gindex_type arg_pos;
			gindex_type initial;
			gindex_type terminal;
			bool compound;

		public:

			nik_ce T_value() : order{}, arg_pos{}, initial{}, terminal{}, compound{} { }

			nik_ce void set_sign(cindex n, bool c = false)
			{
				order    = Kind::sign;
				arg_pos  = n;
				compound = c;
			}

			nik_ce void set_recurse() { order = Kind::recurse; }

			nik_ce void set_lookup(cindex i, cindex t)
			{
				order    = Kind::lookup;
				initial  = i;
				terminal = t;
			}

			nik_ce cindex kind   () const { return order; }
			nik_ce cindex arg_at () const { return arg_pos; }
			nik_ce cindex start  () const { return initial; }
			nik_ce cindex finish () const { return terminal; }

			nik_ce bool is_compound() const { return compound; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// left value:

/***********************************************************************************************************************/

// interface:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// clipboard:

/***********************************************************************************************************************/

// interface:

	template<typename Type>
	struct T_clipboard
	{
		using cindex   = Type;
		using val_type = T_value<Type>;
		using Kind     = typename val_type::Kind;

		bool has_unknown;

		val_type op;
		val_type val;

		gindex_type arg_pos;
		gindex_type sub_pos;
		lexeme left;

		nik_ce T_clipboard() : has_unknown{}, arg_pos{}, sub_pos{} { }

		// op:

			nik_ce void set_op_sign(cindex n, bool c = false) { op.set_sign(n, c); }
			nik_ce void set_op_recurse() { op.set_recurse(); }
			nik_ce void set_op_lookup(cindex i, cindex t) { op.set_lookup(i, t); }

			nik_ce auto op_note() const { return op.is_compound() ? CT::bind : CT::apply; }

		// val:

			nik_ce void set_val_sign(cindex n) { val.set_sign(n); }
			nik_ce void set_val_recurse() { val.set_recurse(); }
			nik_ce void set_val_lookup(cindex i, cindex t) { val.set_lookup(i, t); }

		// (sub)arg:

			nik_ce void set_arg (cindex n)     { arg_pos  = n; }
			nik_ce void set_sub (cindex n)     { sub_pos  = n; }
			nik_ce void inc_sub (cindex n = 1) { sub_pos += n; }

			nik_ce cindex arg_at() const { return arg_pos; }
			nik_ce cindex sub_at() const { return sub_pos; }

		// left:

			nik_ce bool left_unknown() const { return has_unknown; }
			nik_ce void set_unknown(clexeme *l)
			{
				left        = *l;
				has_unknown = true;
			}

			nik_ce clexeme* left_ptr() const { return &left; }
			nik_ce void reset() { has_unknown = false; }
	};

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
		using Global			= typename scanned_type::Global;
		using Local			= typename scanned_type::Local;

		nik_ces auto & src		= T_store_U<static_scanned>::src;
		nik_ces auto & scanned		= member_value_U<static_scanned>;
		nik_ces auto initial		= scanned.global[Global::assembly];
		nik_ces auto offset		= scanned.global[Global::offset];
		nik_ces auto substack		= 2;

		using contr_type		= T_machine_contr<scanned.global[Global::total], substack>;
		using cindex			= typename contr_type::cindex;

		using clipboard_type		= T_clipboard<cindex>;
		using signature_type		= signature<scanned.global[Global::arg]>;
		using procedure_type		= T_procedure<5, 5>; // 5, 5 for prototyping.

		enum : gkey_type
		{
			rec_at = 0,
			str_at,
			env_at,

			dimension
		};

		contr_type contr;

		clipboard_type line;
		signature_type vars;
		procedure_type proc;

		nik_ce T_chord_assembly_ast() :

			contr{rec_at, str_at, env_at, initial, offset},
			vars{scanned.global[Global::pad]} { }

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

			nik_ce void set_op(clexeme *l)
			{
				auto k = vars.match(l);

				if      (k.not_end())        line.set_op_sign(k.left_size(), k->is_compound());
				else if (vars.match_name(l)) line.set_op_recurse();
				else                         line.set_op_lookup(lexeme_start(l), lexeme_finish(l));
			}

			nik_ce void def_op_action(cindex arg_at)
			{
				using Kind = typename clipboard_type::Kind;

				const auto & op = line.op;

				switch (op.kind())
				{
					case Kind::sign    : chain_action<CAN::arg, CAT::non>(arg_at);
					break;
					case Kind::recurse : chain_action<CAN::recurse, CAT::non>();
					break;
					case Kind::lookup  : chain_action<CAN::lookup, CAT::non>(op.start(), op.finish());
					break;
				}
			}

			nik_ce void op_action() { def_op_action(line.op.arg_at()); }

			nik_ce bool op_is_compound() const
			{
				using Kind = typename clipboard_type::Kind;

				const auto & op = line.op;

				return (op.kind() == Kind::sign) && (vars[op.arg_at()].is_compound());
			}

		// capture:

			nik_ce void op_capture_action()
			{
				if (op_is_compound())
				{
					const auto & capture = proc[line.op.arg_at()];

					for (auto k = capture.cbegin(); k != capture.cend(); ++k)
						chain_action<CAN::non, CAT::arg>(*k);
				}

				op_action();
			}

		// value:

			nik_ce void set_val(clexeme *l)
			{
				auto k = vars.match(l);

				if      (k.not_end())        line.set_val_sign(k.left_size());
				else if (vars.match_name(l)) line.set_val_recurse();
				else                         line.set_val_lookup(lexeme_start(l), lexeme_finish(l));
			}

			nik_ce void val_action()
			{
				using Kind = typename clipboard_type::Kind;

				const auto & val = line.val;

				switch (val.kind())
				{
					case Kind::sign    : chain_action<CAN::non, CAT::arg>(val.arg_at());
					break;
					case Kind::recurse : chain_action<CAN::non, CAT::recurse>();
					break;
					case Kind::lookup  : chain_action<CAN::non, CAT::lookup>(val.start(), val.finish());
					break;
				}
			}

		// unit:

			nik_ce void unit_action()
			{
				using Kind = typename clipboard_type::Kind;

				const auto & val = line.val;

				switch (val.kind())
				{
					case Kind::sign    : assembly_action<AAN::unit, AAT::value>(val.arg_at());
					break;
					case Kind::recurse : assembly_action<AAN::unit, AAT::recurse>();
					break;
					case Kind::lookup  : assembly_action<AAN::unit, AAT::lookup>(val.start(), val.finish());
					break;
				}
			}

		// subop:

			nik_ce void subop_action()
			{
				using Kind = typename clipboard_type::Kind;

				const auto & val = line.val;

				switch (val.kind())
				{
					case Kind::sign    : chain_action<CAN::arg, CAT::arg>(val.arg_at(), line.sub_at());
					break;
					case Kind::recurse : chain_action<CAN::recurse, CAT::arg>(line.sub_at());
					break;
					case Kind::lookup  : chain_action<CAN::lookup, CAT::arg>
								(val.start(), val.finish(), line.sub_at());
					break;
				}

				line.inc_sub();
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

