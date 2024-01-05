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

	using CI						= machine::CI;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// abstract syntax tree:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// clipboard:

/***********************************************************************************************************************/

// clip:

	template<typename Type>
	class T_clip
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

			nik_ce T_clip() : inject{}, car{}, cdr{} { }

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

// interface:

	template<typename CharType, typename Type, typename SrcType>
	struct T_clipboard
	{
		using cindex		= Type;
		using src_type		= SrcType;
		using clip_type		= T_clip<Type>;
		using cselect		= cselector<CharType, gindex_type>;

		const src_type & src;

		clip_type op;
		clip_type val;
		clip_type left;

		gindex_type sub_pos;

		nik_ce T_clipboard(const src_type & s) : src{s}, sub_pos{} { }

		// src:

			nik_ce auto start  (const cselect & s) const { return s.cbegin() - src.cbegin(); }
			nik_ce auto finish (const cselect & s) const { return src.cend() - s.cend(); }

			nik_ce auto as_cselect(const clip_type & v) const
				{ return src.cselect(v.start(), v.finish()); }

		// op:

			nik_ce auto op_cselect() const { return as_cselect(op); }
			nik_ce void set_op_lookup(const cselect & s) { op.set_lookup(start(s), finish(s)); }

		// val:

			nik_ce auto val_cselect() const { return as_cselect(val); }
			nik_ce void set_val_lookup(const cselect & s) { val.set_lookup(start(s), finish(s)); }

		// left:

			nik_ce auto left_cselect() const { return as_cselect(left); }
			nik_ce void set_left_unknown(const cselect & s) { left.set_unknown(start(s), finish(s)); }

		// subarg:

			nik_ce cindex sub_at() const { return sub_pos; }

			nik_ce void set_sub (cindex n)     { sub_pos  = n; }
			nik_ce void inc_sub (cindex n = 1) { sub_pos += n; }
	};

	template<typename Type, typename SrcType>
	using clipboard = T_clipboard<gchar_type, Type, SrcType>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// linkage:

/***********************************************************************************************************************/

// link:

	template<typename CharType>
	struct T_link : public generator::T_icon<CharType>
	{
		using base	= generator::T_icon<CharType>;
		using cbase	= base const;

		gindex_type line_pos;

		nik_ce T_link() : base{}, line_pos{} { }

		// line:

			nik_ce gcindex_type line_at() const { return line_pos; }
			nik_ce void set_line(gcindex_type n) { line_pos = n; }
	};

/***********************************************************************************************************************/

// interface:

	template<typename CharType, gindex_type Size>
	struct T_linkage : public sequence<T_link<CharType>, Size>
	{
		using entry		= T_link<CharType>;
		using base		= sequence<entry, Size>;
		using cbase		= base const;
		using cselect		= cselector<CharType, gindex_type>;

		nik_ce T_linkage() : base{} { }

		// enclosure:

			nik_ce auto match(const cselect & s) const
				{ return base::citerate().find(s); }

			nik_ce void push(const cselect & s, gcindex_type n)
			{
				base::end()->copy(s);
				base::end()->set_line(n);
				base::upsize();
			}

			nik_ce void append(const cselect & s, gcindex_type n)
				{ if (match(s).is_end()) push(s, n); }
	};

	template<auto Size>
	using linkage = T_linkage<gchar_type, Size>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// signature:

/***********************************************************************************************************************/

// sign:

	template<typename CharType>
	struct T_sign : public generator::T_icon<CharType>
	{
		using base	= generator::T_icon<CharType>;
		using cbase	= base const;

		bool inject;
		gindex_type compound_pos;

		nik_ce T_sign() : base{}, inject{}, compound_pos{} { }

		// compound:

			nik_ce bool is_compound() const { return inject; }
			nik_ce gcindex_type compound_at() const { return compound_pos; }
			nik_ce void set_compound(gcindex_type n) { compound_pos = n; inject = true; }
	};

/***********************************************************************************************************************/

// interface:

	template<typename CharType, gindex_type Size, gindex_type AnonSize = 1>
	struct T_signature : public sequence<T_sign<CharType>, Size + AnonSize>
	{
		nik_ces auto length		= Size + AnonSize;

		using entry			= T_sign<CharType>;
		using base			= sequence<entry, length>;
		using cbase			= base const;
		using cselect			= cselector<CharType, gindex_type>;

		gcindex_type pad;
		entry name;

		nik_ce T_signature(gcindex_type p) : base{}, pad{p} { base::upsize(AnonSize); }

		// name:

			nik_ce auto match_name (const cselect & s) const { return name.same(s); }
			nik_ce void push_name  (const cselect & s) { name.copy(s); }

		// arg:

			nik_ce auto padding  () const { return pad + 1; }
			nik_ce auto dropsize () const { return length; }

			nik_ce auto match(const cselect & s) const
				{ return base::citerate().find(s); }

			nik_ce void push(const cselect & s)
			{
				base::end()->copy(s);
				base::upsize();
			}

			nik_ce void append(const cselect & s)
			{
				if (match(s).is_end()) push(s);
				else { } // error.
			}
	};

	template<auto Size>
	using signature = T_signature<gchar_type, Size>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// composition:

/***********************************************************************************************************************/

// record:

	struct T_record
	{
		gcindex_type arity;
		gcindex_type cap_size;
		gcindex_type dropsize;

		nik_ce T_record(gcindex_type a, gcindex_type c) :
			arity{a}, cap_size{c}, dropsize{static_cast<gindex_type>(a + c)} { }
	};

/***********************************************************************************************************************/

// capture:

	template<typename CharType>
	struct T_capture : public generator::T_icon<CharType>
	{
		using base	= generator::T_icon<CharType>;
		using cbase	= base const;

		gindex_type sign_pos; // required when creating a function application.

		nik_ce T_capture() : base{}, sign_pos{} { }

		// signature:

			nik_ce gcindex_type sign_at() const { return sign_pos; }
			nik_ce void set_sign(gcindex_type n) { sign_pos = n; }
	};

/***********************************************************************************************************************/

// compound:

	template<typename CharType, gindex_type Size>
	struct T_compound : public sequence<T_capture<CharType>, Size>
	{
		using entry	= T_capture<CharType>;
		using base	= sequence<entry, Size>;
		using cbase	= base const;
		using cselect	= cselector<CharType, gindex_type>;

		struct Kind { enum : gkey_type { morph = 0, cycle, dimension }; };

		gindex_type inject;
		gindex_type arg_size;
		gindex_type cycle_pos;

		nik_ce T_compound() : base{}, inject{}, arg_size{}, cycle_pos{} { }

		// arity:

			nik_ce gcindex_type arity() const { return arg_size; }
			nik_ce void set_arity(gcindex_type n) { arg_size = n; }

		// record:

			nik_ce const T_record record() const { return T_record{arg_size, base::size()}; }

		// kind:

			nik_ce gcindex_type kind() const { return inject; }

		// cycle:

			nik_ce gcindex_type cycle_at() const { return cycle_pos; }
			nik_ce void set_cycle(gcindex_type n) { cycle_pos = n; inject = Kind::cycle; }

		// arg:

			nik_ce auto match(const cselect & s) const
				{ return base::citerate().find(s); }

			nik_ce void push(const cselect & s, gcindex_type n)
			{
				base::end()->copy(s);
				base::end()->set_sign(n);
				base::upsize();
			}

			nik_ce void append(const cselect & s, gcindex_type n)
				{ if (match(s).is_end()) push(s, n); }

			nik_ce void capture(const T_compound & c)
				{ base::unite(c.cbegin(), c.cend()); }
	};

/***********************************************************************************************************************/

// interface:

	template<typename CharType, gindex_type Subsize, gindex_type Size>
	struct T_composition : public sequence<T_compound<CharType, Subsize>, Size>
	{
		using entry	= T_compound<CharType, Subsize>;
		using base	= sequence<entry, Size>;
		using cbase	= base const;
		using Kind	= typename entry::Kind;

		nik_ce T_composition() : base{} { }

		nik_ce gcindex_type allocate() { base::upsize(); return base::max(); }
	};

	template<auto Subsize, auto Size>
	using composition = T_composition<gchar_type, Subsize, Size>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// progression:

/***********************************************************************************************************************/

// interval:

	struct T_interval
	{
		struct Kind { enum : gkey_type { fixed = 0, closed, open, dimension }; };

		gindex_type left;
		gindex_type right;

		nik_ce T_interval() : left{}, right{} { }
	};

/***********************************************************************************************************************/

// routine:

	struct T_routine
	{
		struct Kind { enum : gkey_type { comb , act , mut , pred , dimension }; };

		nik_ces gindex_type length = Kind::dimension;

		sequence<gindex_type, length> locus;
		sequence<gindex_type, length> pound;

		nik_ce T_routine() { }

		// subcontr:

			nik_ce gcindex_type subcontr_at(gcindex_type m) const { return locus[m]; }

				nik_ce gcindex_type comb_subcontr () const { return subcontr_at(Kind::comb); }
				nik_ce gcindex_type act_subcontr  () const { return subcontr_at(Kind::act ); }
				nik_ce gcindex_type mut_subcontr  () const { return subcontr_at(Kind::mut ); }
				nik_ce gcindex_type pred_subcontr () const { return subcontr_at(Kind::pred); }

			nik_ce void push_subcontr(gcindex_type n) { locus.push(n); }

		// compound:

			nik_ce gcindex_type compound_at(gcindex_type m) const { return pound[m]; }

				nik_ce gcindex_type comb_compound () const { return compound_at(Kind::comb); }
				nik_ce gcindex_type act_compound  () const { return compound_at(Kind::act ); }
				nik_ce gcindex_type mut_compound  () const { return compound_at(Kind::mut ); }
				nik_ce gcindex_type pred_compound () const { return compound_at(Kind::pred); }

			nik_ce void push_compound(gcindex_type n) { pound.push(n); }
	};

/***********************************************************************************************************************/

// cycle:

	template<gindex_type Size>
	struct T_cycle : public sequence<T_interval, Size>
	{
		using entry		= T_interval;
		using base		= sequence<entry, Size>;
		using cbase		= base const;
		using routine_type	= T_routine;
		using IvalKind		= typename entry::Kind;
		using RoutKind		= typename routine_type::Kind;

		gindex_type pound_pos;
		gindex_type root_pos;
		routine_type routine;

		nik_ce T_cycle() : base{}, pound_pos{}, root_pos{} { }

		// compound:

			nik_ce gcindex_type compound_at() const { return pound_pos; }
			nik_ce void set_compound(gcindex_type n) { pound_pos = n; }

		// root:

			nik_ce gcindex_type root_at() const { return root_pos; }
			nik_ce void set_root(gcindex_type n) { root_pos = n; }
	};

/***********************************************************************************************************************/

// interface:

	template<gindex_type Subsize, gindex_type Size>
	struct T_progression : public sequence<T_cycle<Subsize>, Size>
	{
		using entry		= T_cycle<Subsize>;
		using base		= sequence<entry, Size>;
		using cbase		= base const;
		using routine_type	= typename entry::routine_type;
		using Kind		= typename entry::IvalKind;

		nik_ce T_progression() : base{} { }

		nik_ce gcindex_type allocate() { base::upsize(); return base::max(); }

		// subroutine:

			nik_ce const routine_type & csubroutine() const { return base::last()->routine; }
			nik_ce routine_type & subroutine() { return base::last()->routine; }
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

											// 1000 for prototyping.
		using contr_type		= T_machine_contr<scanned.global[Global::total] + 1000, substack>;
		using cindex			= typename contr_type::cindex;

		using drop_tag_type		= sequence<gindex_type, 5>; // 5 for prototyping.
		using linkage_type		= linkage<5>; // 5 for prototyping.

		using clipboard_type		= clipboard<cindex, src_type>;
		using cselect			= typename clipboard_type::cselect;

		using clip_type			= typename clipboard_type::clip_type;
		using ClipKind			= typename clip_type::Kind;

		using signature_type		= signature<scanned.global[Global::arg]>;
		using composition_type		= composition<5, 25>; // 5, 25 for prototyping.
		using progression_type		= T_progression<5, 5>; // 5, 5 for prototyping.

		enum : gkey_type
		{
			rec_at = 0,
			str_at,
			env_at,
			aux_at,

			dimension
		};

		contr_type contr;
		linkage_type label;
		linkage_type jump;
		drop_tag_type drop;
		clipboard_type line;
		signature_type vars;
		composition_type pound;
		progression_type cycle;

		nik_ce T_chord_assembly_ast() :

			contr{rec_at, str_at, env_at, aux_at, initial, offset},
			line{T_store_U<static_scanned>::src},
			vars{scanned.global[Global::pad]} { }

		// (generic) action:

			template<auto name, auto note, typename... Ts> // temporary ?
			nik_ce void machine_action(Ts... vs) { machine::machine_action<name, note>(&contr, vs...); }

			template<auto name, auto note, typename... Ts>
			nik_ce void lookup_action(Ts... vs) { machine::lookup_action<name, note>(&contr, vs...); }

			template<auto name, auto note, typename... Ts>
			nik_ce void chain_action(Ts... vs) { machine::chain_action<name, note>(&contr, vs...); }

			template<auto name, auto note, typename... Ts>
			nik_ce void assembly_action(Ts... vs) { machine::assembly_action<name, note>(&contr, vs...); }

		// replace:

			nik_ce void non_zero_replace(cindex n)
				{ if (n != 0) assembly_action<AAN::replace, AAT::id>(n); }

		// linkage:

			nik_ce void tag_arg_drops(cindex cap_size)
			{
				for (auto k = drop.cbegin(); k != drop.cend(); ++k)
					contr[*k][CI::pos] += cap_size;
			}

			nik_ce void tag_label_jumps()
			{
				for (auto j = jump.cbegin(); j != jump.cend(); ++j)
				{
					auto k = label.match(*j);

					if (k.not_end()) contr[j->line_at()][CI::pos] = k->line_at();
					else { } // error.
				}
			}

		// signature:

			nik_ce const auto & sign_entry(const clip_type & c) const { return vars[c.arg_at()]; }

			nik_ce void assign_unknown()
			{
				vars.push(line.left_cselect());
				line.left.set_sign(vars.max());
			}

		// composition:

			nik_ce const auto & compound_at(const clip_type & c) const
				{ return pound[sign_entry(c).compound_at()]; }

			nik_ce void push_compound() { vars.last()->set_compound(pound.allocate()); }

		// progression:

			nik_ce void push_cycle()
			{
				push_compound();
				pound.last()->set_cycle(cycle.allocate());
				cycle.last()->set_compound(pound.max());
			}

		// clipboard:

			nik_ce bool is_sign(const clip_type & c) const
				{ return (c.kind() == ClipKind::sign); }

			nik_ce bool is_compound(const clip_type & c) const
				{ return sign_entry(c).is_compound(); }

			nik_ce bool is_sign_compound(const clip_type & c) const
				{ return is_sign(c) && is_compound(c); }

			nik_ce void paste_compound(const clip_type & c)
			{
				if (is_sign_compound(c))
				{
					const auto & compound = compound_at(c);

					for (auto k = compound.cbegin(); k != compound.cend(); ++k)
						chain_action<CAN::non, CAT::arg>(k->sign_at());
				}
			}

			nik_ce void paste_compound(const clip_type & c, cindex arity)
			{
				if (is_sign_compound(c))
				{
					const auto & compound = compound_at(c);

					for (auto k = compound.cbegin(); k != compound.cend(); ++k)
					{
						auto j = pound.last()->match(*k);
						auto cap_at = arity + j.left_size();

						chain_action<CAN::non, CAT::arg>(cap_at);
					}
				}
			}

		// (clip) op:

			nik_ce bool op_is_sign          () const { return is_sign(line.op); }
			nik_ce bool op_is_compound      () const { return is_compound(line.op); }
			nik_ce bool op_is_sign_compound () const { return is_sign_compound(line.op); }
			nik_ce auto op_note             () const { return op_is_sign_compound() ? CT::bind : CT::apply; }

			nik_ce void copy_op(const cselect & s)
			{
				auto k = vars.match(s);

				if      (k.not_end())        line.op.set_sign(k.left_size());
				else if (vars.match_name(s)) line.op.set_recurse();
				else                         line.set_op_lookup(s);
			}

			nik_ce void capture_op()
			{
				if (op_is_sign())
				{
					auto op_cselect = line.op_cselect();
					pound.last()->append(op_cselect, line.op.arg_at());

					if (op_is_compound())
						pound.last()->capture(compound_at(line.op));
				}
			}

			nik_ce void paste_op(cindex n)
			{
				switch (line.op.kind())
				{
					case ClipKind::sign    : { paste_op_sign    (n); break; }
					case ClipKind::recurse : { paste_op_recurse ( ); break; }
					case ClipKind::lookup  : { paste_op_lookup  ( ); break; }
				}
			}

				nik_ce void paste_op_sign(cindex n)
					{ chain_action<CAN::arg, CAT::non>(n); }

				nik_ce void paste_op_recurse()
					{ chain_action<CAN::recurse, CAT::non>(); }

				nik_ce void paste_op_lookup()
					{ chain_action<CAN::lookup, CAT::non>(line.op.start(), line.op.finish()); }

			nik_ce void paste_atomic_op() { paste_op(line.op.arg_at()); }

			nik_ce void paste_compound_op()
			{
				paste_compound(line.op);
				paste_atomic_op();
			}

		// (clip) val:

			nik_ce bool val_is_sign          () const { return is_sign(line.val); }
			nik_ce bool val_is_compound      () const { return is_compound(line.val); }
			nik_ce bool val_is_sign_compound () const { return is_sign_compound(line.val); }

			nik_ce void copy_val(const cselect & s)
			{
				auto k = vars.match(s);

				if      (k.not_end())        line.val.set_sign(k.left_size());
				else if (vars.match_name(s)) line.val.set_recurse();
				else                         line.set_val_lookup(s);
			}

			nik_ce auto capture_match_val()
			{
				auto val_cselect = line.val_cselect();
				pound.last()->append(val_cselect, line.val.arg_at());
				auto k = pound.last()->match(val_cselect);

				return k.left_size();
			}

			nik_ce void paste_val()
			{
				switch (line.val.kind())
				{
					case ClipKind::sign    : { paste_val_sign    (); break; }
					case ClipKind::recurse : { paste_val_recurse (); break; }
					case ClipKind::lookup  : { paste_val_lookup  (); break; }
				}
			}

				nik_ce void paste_val_sign(const bool mutate = false)
					{ chain_action<CAN::non, CAT::arg>(line.val.arg_at(), mutate); }

				nik_ce void paste_val_recurse()
					{ chain_action<CAN::non, CAT::recurse>(); }

				nik_ce void paste_val_lookup()
					{ chain_action<CAN::non, CAT::lookup>(line.val.start(), line.val.finish()); }

		// (val) mutation:

			nik_ce void paste_val_mut()
			{
				if (line.val.kind() == ClipKind::sign) paste_val_sign(true);
				else { } // error.
			}

		// (val) unit:

			nik_ce void paste_val_unit()
			{
				switch (line.val.kind())
				{
					case ClipKind::sign    : { paste_val_unit_sign    (); break; }
					case ClipKind::recurse : { paste_val_unit_recurse (); break; }
					case ClipKind::lookup  : { paste_val_unit_lookup  (); break; }
				}
			}

				nik_ce void paste_val_unit_sign()
					{ assembly_action<AAN::unit, AAT::value>(line.val.arg_at()); }

				nik_ce void paste_val_unit_recurse()
					{ assembly_action<AAN::unit, AAT::recurse>(); }

				nik_ce void paste_val_unit_lookup()
					{ assembly_action<AAN::unit, AAT::lookup>(line.val.start(), line.val.finish()); }

		// subop:

			nik_ce void paste_compound_subop(cindex arity)
			{
				paste_compound(line.op, arity);
				paste_op(arity); // optimization: arity is the first position following the args.
			}

		// subval:

			nik_ce auto subval_capture_at() { return pound.last()->arity() + capture_match_val(); }

			nik_ce void paste_subval()
			{
				switch (line.val.kind())
				{
					case ClipKind::sign    : { paste_subval_sign (); break; }
					case ClipKind::recurse : { paste_val_recurse (); break; }
					case ClipKind::lookup  : { paste_val_lookup  (); break; }
				}
			}

				nik_ce void paste_subval_sign()
					{ chain_action<CAN::non, CAT::arg>(subval_capture_at()); }

		// argop:

			nik_ce void capture_argop()
				{ if (val_is_sign_compound()) pound.last()->capture(compound_at(line.val)); }

			nik_ce void paste_argop()
			{
				switch (line.val.kind())
				{
					case ClipKind::sign    : { paste_argop_sign   (); break; }
					case ClipKind::recurse : { paste_argop_recurse(); break; }
					case ClipKind::lookup  : { paste_argop_lookup (); break; }
				}

				line.inc_sub();
			}

				nik_ce void paste_argop_sign()
				{
					chain_action<CAN::begin , CAT::sub >(CT::push);
					chain_action<CAN::arg   , CAT::arg >(subval_capture_at(), line.sub_at());

					paste_compound(line.val);
					drop.push(contr.instr_at()); // defers arg_drop.

					auto note = val_is_sign_compound() ? CT::bind : CT::apply;
					auto init_arg_drop = pound.last()->arity() + line.sub_at();
					chain_action<CAN::end, CAT::sub>(init_arg_drop, note);
				}

				nik_ce void paste_argop_recurse()
					{ chain_action<CAN::recurse, CAT::arg>(line.sub_at()); }

				nik_ce void paste_argop_lookup()
				{
					auto s = line.val.start();
					auto f = line.val.finish();
					auto a = line.sub_at();

					chain_action<CAN::lookup, CAT::arg>(s, f, a);
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

