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

/***********************************************************************************************************************/

// interface:

	template<typename CharType, gindex_type Size, gindex_type AnonSize = 1>
	struct T_signature : public sequence<T_signature_entry<CharType>, Size + AnonSize>
	{
		nik_ces auto length		= Size + AnonSize;

		using entry			= T_signature_entry<CharType>;
		using base			= sequence<entry, length>;
		using cbase			= base const;

		gcindex_type pad;
		entry name;

		nik_ce T_signature(gcindex_type p) : base{}, pad{p} { base::upsize(AnonSize); }

		// name:

			nik_ce auto match_name (clexeme *l) const { return name.same(l); }
			nik_ce void push_name  (clexeme *l) { name.copy(l); }

		// arg:

			nik_ce auto padding  () const { return pad + 1; }
			nik_ce auto dropsize () const { return length; }

			nik_ce auto match(clexeme *l) const
				{ return base::citerate().find(l->left_cselect()); }

			nik_ce void push(clexeme *l)
			{
				base::end()->copy(l);
				base::upsize();
			}

			nik_ce void push(clexeme & l) { push(&l); }

			nik_ce void append(clexeme *l)
			{
				if (match(l).is_end()) push(l);
				else { } // error.
			}
	};

	template<auto Size>
	using signature = T_signature<gchar_type, Size>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// procedure:

/***********************************************************************************************************************/

// entry:

	template<typename CharType>
	struct T_capture_entry : public generator::T_icon<CharType>
	{
		using base	= generator::T_icon<CharType>;
		using cbase	= base const;

		gindex_type sign_pos;

		nik_ce T_capture_entry() : base{}, sign_pos{} { }

		// signature:

			nik_ce gcindex_type sign_at() const { return sign_pos; }
			nik_ce void set_sign(gcindex_type n) { sign_pos = n; }
	};

/***********************************************************************************************************************/

// capture:

	template<typename CharType, gindex_type Size>
	struct T_capture : public sequence<T_capture_entry<CharType>, Size>
	{
		using entry	= T_capture_entry<CharType>;
		using base	= sequence<entry, Size>;
		using cbase	= base const;

		gindex_type arg_size;

		nik_ce T_capture() : base{}, arg_size{} { }

		// arity:

			nik_ce void set_arity(gcindex_type n) { arg_size = n; }
			nik_ce gcindex_type arity() const { return arg_size; }

		// arg:

			nik_ce auto match(clexeme *l) const
				{ return base::citerate().find(l->left_cselect()); }

			nik_ce void push(clexeme *l, gcindex_type n)
			{
				base::end()->copy(l);
				base::end()->set_sign(n);
				base::upsize();
			}

			nik_ce void append(clexeme *l, gcindex_type n)
				{ if (match(l).is_end()) push(l, n); }

			nik_ce void unite(const T_capture & c)
				{ base::unite(c.cbegin(), c.cend()); }
	};

/***********************************************************************************************************************/

// interface:

	template<typename CharType, gindex_type Subsize, gindex_type Size>
	struct T_procedure : public sequence<T_capture<CharType, Subsize>, Size>
	{
		using entry	= T_capture<CharType, Subsize>;
		using base	= sequence<entry, Size>;
		using cbase	= base const;

		nik_ce T_procedure() : base{} { }

		nik_ce gcindex_type allocate() { base::upsize(); return base::max(); }
	};

	template<auto Subsize, auto Size>
	using procedure = T_procedure<gchar_type, Subsize, Size>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// value:

/***********************************************************************************************************************/

// interface:

	template<typename Type>
	class T_value
	{
		public:

			using cindex		= Type;
			using selector_type	= cselector<gindex_type, gindex_type>;

			struct Kind { enum : gkey_type { id = 0, sign, recurse, lookup, unknown, dimension }; };

		private:

			gindex_type inject;
			gindex_type car;
			gindex_type cdr;

		public:

			nik_ce T_value() : inject{}, car{}, cdr{} { }

			// kind:

				nik_ce cindex kind() const { return inject; }

				nik_ce void set(cindex i, cindex a = 0, cindex d = 0)
				{
					inject = i;
					car    = a;
					cdr    = d;
				}

				nik_ce void reset() { set(Kind::id); }

			// sign:

				nik_ce cindex arg_at() const { return car; }

				nik_ce void set_sign(cindex n) { set(Kind::sign, n); }

			// recurse:

				nik_ce void set_recurse() { set(Kind::recurse); }

			// lookup:

				nik_ce cindex start  () const { return car; }
				nik_ce cindex finish () const { return cdr; }

				nik_ce void set_lookup(cindex a, cindex d) { set(Kind::lookup, a, d); }

			// unknown:

				nik_ce bool is_unknown() const { return (inject == Kind::unknown); }

				nik_ce void set_unknown(cindex a, cindex d) { set(Kind::unknown, a, d); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// clipboard:

/***********************************************************************************************************************/

// interface:

	template<typename Type, typename SrcType>
	struct T_clipboard
	{
		using cindex   = Type;
		using src_type = SrcType;
		using val_type = T_value<Type>;
		using Kind     = typename val_type::Kind;

		const src_type & src;

		val_type op;
		val_type val;
		val_type left;
		lexeme word;

		gindex_type sub_pos;

		nik_ce T_clipboard(const src_type & s) : src{s}, sub_pos{} { }

		// src:

			nik_ce auto start  (clexeme *l) const { return l->cbegin() - src.cbegin(); }
			nik_ce auto finish (clexeme *l) const { return src.cend() - l->ccurrent(); }

			nik_ce auto as_lexeme(const val_type & v) const
			{
				auto s = src.cselect(v.start(), v.finish());

				return lexeme{s} + s.size();
			}

		// op:

			nik_ce auto op_lexeme() const { return as_lexeme(op); }

			nik_ce void set_op_lookup(clexeme *l) { op.set_lookup(start(l), finish(l)); }

		// val:

			nik_ce auto val_lexeme() const { return as_lexeme(val); }

			nik_ce void set_val_lookup(clexeme *l) { val.set_lookup(start(l), finish(l)); }

		// left:

			nik_ce auto left_lexeme() const { return as_lexeme(left); }

			nik_ce void set_left_unknown(clexeme *l)
			{
				word = *l;
				left.set_unknown(start(l), finish(l));
			}

		// subarg:

			nik_ce cindex sub_at() const { return sub_pos; }

			nik_ce void set_sub (cindex n)     { sub_pos  = n; }
			nik_ce void inc_sub (cindex n = 1) { sub_pos += n; }
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
		using src_type			= typename T_store_U<static_scanned>::src_type;
		using Global			= typename scanned_type::Global;
		using Local			= typename scanned_type::Local;

		nik_ces auto & scanned		= member_value_U<static_scanned>;
		nik_ces auto initial		= scanned.global[Global::assembly];
		nik_ces auto offset		= scanned.global[Global::offset];
		nik_ces auto substack		= 2;

		using contr_type		= T_machine_contr<scanned.global[Global::total], substack>;
		using cindex			= typename contr_type::cindex;

		using signature_type		= signature<scanned.global[Global::arg]>;
		using procedure_type		= procedure<5, 5>; // 5, 5 for prototyping.
		using clipboard_type		= T_clipboard<cindex, src_type>;
		using val_type			= typename clipboard_type::val_type;
		using Kind			= typename clipboard_type::Kind;

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
			line{T_store_U<static_scanned>::src},
			vars{scanned.global[Global::pad]} { }

		// (generic) action:

			template<auto name, auto note, typename... Ts>
			nik_ce void lookup_action(Ts... vs) { machine::lookup_action<name, note>(&contr, vs...); }

			template<auto name, auto note, typename... Ts>
			nik_ce void chain_action(Ts... vs) { machine::chain_action<name, note>(&contr, vs...); }

			template<auto name, auto note, typename... Ts>
			nik_ce void assembly_action(Ts... vs) { machine::assembly_action<name, note>(&contr, vs...); }

		// replace:

			nik_ce void non_zero_replace(cindex n)
				{ if (n != 0) assembly_action<AAN::replace, AAT::id>(n); }

		// vars:

			nik_ce bool is_compound(cindex n) const { return vars[n].is_compound(); }

			nik_ce void assign_unknown()
			{
				vars.push(line.left_lexeme());
				line.left.set_sign(vars.max());
			}

		// val:

			nik_ce bool is_sign     (const val_type & v) const { return (v.kind() == Kind::sign); }
			nik_ce bool is_compound (const val_type & v) const { return is_sign(v) && is_compound(v.arg_at()); }

		// op:

			nik_ce void set_op(clexeme *l)
			{
				auto k = vars.match(l);

				if      (k.not_end())        line.op.set_sign(k.left_size());
				else if (vars.match_name(l)) line.op.set_recurse();
				else                         line.set_op_lookup(l);
			}

			nik_ce void def_op_action(cindex n)
			{
				switch (line.op.kind())
				{
					case Kind::sign    : { op_action_sign   (n); break; }
					case Kind::recurse : { op_action_recurse( ); break; }
					case Kind::lookup  : { op_action_lookup ( ); break; }
				}
			}

			nik_ce void op_action_sign(cindex n)
				{ chain_action<CAN::arg, CAT::non>(n); }

			nik_ce void op_action_recurse()
				{ chain_action<CAN::recurse, CAT::non>(); }

			nik_ce void op_action_lookup()
				{ chain_action<CAN::lookup, CAT::non>(line.op.start(), line.op.finish()); }

			nik_ce void op_action() { def_op_action(line.op.arg_at()); }

			nik_ce bool op_is_sign     () const { return is_sign(line.op); }
			nik_ce bool op_is_compound () const { return is_compound(line.op); }
			nik_ce auto op_note        () const { return op_is_compound() ? CT::bind : CT::apply; }

			nik_ce void op_capture_action()
			{
				if (op_is_compound())
				{
					const auto & sign_ent = vars[line.op.arg_at()];
					const auto & capture  = proc[sign_ent.proc_at()];

					for (auto k = capture.cbegin(); k != capture.cend(); ++k)
						chain_action<CAN::non, CAT::arg>(k->sign_at());
				}

				op_action();
			}

		// value:

			nik_ce void set_val(clexeme *l)
			{
				auto k = vars.match(l);

				if      (k.not_end())        line.val.set_sign(k.left_size());
				else if (vars.match_name(l)) line.val.set_recurse();
				else                         line.set_val_lookup(l);
			}

			nik_ce void val_action()
			{
				switch (line.val.kind())
				{
					case Kind::sign    : { val_action_sign   (); break; }
					case Kind::recurse : { val_action_recurse(); break; }
					case Kind::lookup  : { val_action_lookup (); break; }
				}
			}

			nik_ce auto val_capture_action()		// be mindful that a reconstructed
			{						// lexeme differs from its original.
				auto val_lexeme = line.val_lexeme();
				proc.last()->append(&val_lexeme, line.val.arg_at());
				auto k = proc.last()->match(&val_lexeme);

				return k.left_size();
			}

			nik_ce void val_action_sign()
				{ chain_action<CAN::non, CAT::arg>(line.val.arg_at()); }

			nik_ce void val_action_recurse()
				{ chain_action<CAN::non, CAT::recurse>(); }

			nik_ce void val_action_lookup()
				{ chain_action<CAN::non, CAT::lookup>(line.val.start(), line.val.finish()); }

			nik_ce bool val_is_sign     () const { return is_sign(line.val); }
			nik_ce bool val_is_compound () const { return is_compound(line.val); }

		// unit:

			nik_ce void unit_action()
			{
				switch (line.val.kind())
				{
					case Kind::sign    : { unit_action_sign   (); break; }
					case Kind::recurse : { unit_action_recurse(); break; }
					case Kind::lookup  : { unit_action_lookup (); break; }
				}
			}

			nik_ce void unit_action_sign()
				{ assembly_action<AAN::unit, AAT::value>(line.val.arg_at()); }

			nik_ce void unit_action_recurse()
				{ assembly_action<AAN::unit, AAT::recurse>(); }

			nik_ce void unit_action_lookup()
				{ assembly_action<AAN::unit, AAT::lookup>(line.val.start(), line.val.finish()); }

		// subop:

			nik_ce void subop_capture_action()
			{
				proc_capture_val();
				subop_action();
			}

			nik_ce void proc_capture_val()
			{
				if (val_is_compound())
				{
					const auto & sign_ent = vars[line.val.arg_at()];

					proc.last()->unite(proc[sign_ent.proc_at()]);
				}
			}

			nik_ce void subop_action()
			{
				switch (line.val.kind())
				{
					case Kind::sign    : { subop_action_sign   (); break; }
					case Kind::recurse : { subop_action_recurse(); break; }
					case Kind::lookup  : { subop_action_lookup (); break; }
				}

				line.inc_sub();
			}

			nik_ce void subop_action_sign() // (x y sq ...)
			{
				auto subop_at = proc.last()->arity() + val_capture_action();

				chain_action<CAN::begin, CAT::sub>(CT::push);

				if (val_is_compound()) subop_compound_action_sign(subop_at);
				else subop_atomic_action_sign(subop_at);

				auto cap_size = 1; // we need to know (the final) last size in advance.
				auto note = val_is_compound() ? CT::bind : CT::apply;
				auto arg_drop = proc.last()->arity() + cap_size + line.sub_at();
				chain_action<CAN::end, CAT::sub>(arg_drop, note);
			}

				nik_ce void subop_compound_action_sign(cindex subop_at)
				{
					chain_action<CAN::arg, CAT::arg>(subop_at, line.sub_at());

					const auto & sign_ent = vars[line.val.arg_at()]; // refactor (start)
					const auto & capture  = proc[sign_ent.proc_at()];

					for (auto k = capture.cbegin(); k != capture.cend(); ++k)
						chain_action<CAN::non, CAT::arg>(k->sign_at()); // refactor (end)
				}

				nik_ce void subop_atomic_action_sign(cindex subop_at)
					{ chain_action<CAN::arg, CAT::arg>(subop_at, line.sub_at()); }

			nik_ce void subop_action_recurse()
				{ chain_action<CAN::recurse, CAT::arg>(line.sub_at()); }

			nik_ce void subop_action_lookup()
			{
				auto s = line.val.start();
				auto f = line.val.finish();
				auto a = line.sub_at();

				chain_action<CAN::lookup, CAT::arg>(s, f, a);
			}

		// subval:

			nik_ce void subval_capture_action()
			{
				switch (line.val.kind())
				{
					case Kind::sign    : { subval_action_sign   (); break; }
					case Kind::recurse : {    val_action_recurse(); break; }
					case Kind::lookup  : {    val_action_lookup (); break; }
				}
			}

			nik_ce void subval_action_sign()
			{
				auto subval_at = proc.last()->arity() + val_capture_action();

				chain_action<CAN::non, CAT::arg>(subval_at);
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

