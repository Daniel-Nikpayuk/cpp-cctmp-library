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

// iterator:

/***********************************************************************************************************************/

// interface:

	template<typename SizeType>
	struct T_chord_iterator
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		size_type contr_pos;
		bool side;

		nik_ce T_chord_iterator() : contr_pos{}, side{} { }
		nik_ce T_chord_iterator(csize_type p, const bool s) : contr_pos{p}, side{s} { }

		// pos:

			nik_ce auto get_contr_pos() const { return contr_pos; }
			nik_ce void set_contr_pos(csize_type p) { contr_pos = p; }

		// side:

			nik_ce auto get_side() const { return side; }
			nik_ce void set_side(const bool s) { side = s; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// interval:

/***********************************************************************************************************************/

// interface:

	template<typename SizeType>
	struct T_chord_interval
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		struct Ival		{ enum : size_type { tone, root, dimension }; };
		struct Point		{ enum : size_type { fixed, closed, open, dimension }; };
		struct Iter		{ enum : size_type { next, prev, dimension }; };

		using iter_type		= T_chord_iterator<size_type>;
		using iter_seq		= sequence<iter_type, static_cast<size_type>(Iter::dimension)>;

		size_type ival;
		size_type left;
		size_type right;

		iter_seq note_iter;
		iter_seq tonic_iter;

		nik_ce T_chord_interval() :
			ival{Ival::tone}, left{Point::fixed}, right{Point::fixed}
				{ }

		nik_ce bool is_tone   () const { return (ival == Ival::tone); }
		nik_ce bool is_root   () const { return (ival == Ival::root); }
		nik_ce bool has_tonic () const { return (ival == Ival::root); }

		// ival:

			nik_ce auto not_left_fixed  () const { return (left  != Point::fixed); }
			nik_ce auto not_right_fixed () const { return (right != Point::fixed); }
			nik_ce auto not_fixed       () const { return (not_left_fixed() && not_right_fixed()); }

			nik_ce auto is_left_open    () const { return (left  == Point::open); }
			nik_ce auto is_right_open   () const { return (right == Point::open); }
			nik_ce auto is_right_closed () const { return (right == Point::closed); }

			nik_ce void set_left  (csize_type p) { left = p; }
			nik_ce void set_right (csize_type p) { right = p; }

			nik_ce void set_left_fixed   () { set_left(Point::fixed);   }
			nik_ce void set_left_closed  () { set_left(Point::closed);  }
			nik_ce void set_left_open    () { set_left(Point::open);    }
			nik_ce void set_right_fixed  () { set_right(Point::fixed);  }
			nik_ce void set_right_closed () { set_right(Point::closed); }
			nik_ce void set_right_open   () { set_right(Point::open);   }

		// note:

			nik_ce void push_note(csize_type p, const bool s = false)
				{ note_iter.push(iter_type{p, s}); }

		// tonic:

			nik_ce void push_tonic(csize_type p, const bool s = false)
			{
				ival = Ival::root;
				tonic_iter.push(iter_type{p, s});
			}

		// iter:

			nik_ce bool is_note_reversible  () const { return (note_iter.size() == 2); }
			nik_ce bool is_tonic_reversible () const { return (tonic_iter.size() == 2); }
	};

/***********************************************************************************************************************/

// intervals:

	// major: all intervals right open, tone notes align centre (with tonic note).
	// augmented: root interval right open, at least one tone interval right closed.
	//            right closed tone notes align left (of tonic note).
			// there are 3 algorithm dispatch cases:
				// 1) tonic: tonic note is reversible.
					// a) move tonic note prev.
					// b) march (move) root and tone notes.
					// c) update (move) root and tone notes.
					// d) update tonic note next.
				// 2) tone: tonic note is not reversible,
				//          but all left aligned tone notes are reversible.
					// a) march root and tone notes.
					// b) backdate (move) left aligned tone notes.
				// 3) peek: tonic note is not reversible,
				//          and at least one left aligned tone note is not reversible.
					// a) peekmarch (move) root and tone notes.
					// b) update root and tone notes.
	// diminished: all intervals right closed, tone notes align centre (with tonic note).
	// minor: root interval right closed, at least one tone interval right open.
	//        right open tone notes align right (of tonic note).

	template<typename SizeType, SizeType Size>
	struct T_chord_intervals : public sequence<T_chord_interval<SizeType>, Size>
	{
		using base		= sequence<T_chord_interval<SizeType>, Size>;
		using interval_type	= typename base::type;
		using size_type		= typename interval_type::size_type;
		using csize_type	= typename interval_type::csize_type;
		using Iter		= typename interval_type::Iter;

		struct Augmented	{ enum : size_type { tonic, tone, peek, dimension }; };
		struct Chord		{ enum : size_type { none, major, augmented, diminished, minor, dimension }; };

		size_type augmented;
		size_type init;
		size_type chord;
		bool has_left_open;
		bool is_tone_augmented;

		nik_ce T_chord_intervals() :
			base{}, augmented{Augmented::peek}, init{Chord::none}, chord{Chord::none},
			has_left_open{}, is_tone_augmented{}
				{ }

		// reset:

			nik_ce void reset()
			{
				for (auto k = base::begin(); k != base::end(); ++k)
				{
					k->note_iter.clear();
					k->tonic_iter.clear();
				}

				base::clear();

				augmented         = Augmented::peek;
				init              = Chord::none;
				chord             = Chord::none;
				has_left_open     = false;
				is_tone_augmented = false;
			}

		// ival (random access):

			nik_ce auto not_fixed(csize_type n) const
				{ return base::operator[](n).not_fixed(); }

			nik_ce auto is_left_open(csize_type n) const
				{ return base::operator[](n).is_left_open(); }

			nik_ce auto is_right_open(csize_type n) const
				{ return base::operator[](n).is_right_open(); }

			nik_ce auto is_right_closed(csize_type n) const
				{ return base::operator[](n).is_right_closed(); }

		// ival (last):

			nik_ce void set_fixed()
			{
				base::last()->set_left_fixed();
				base::last()->set_right_fixed();
			}

			nik_ce void set_left_closed () { base::last()->set_left_closed(); }
			nik_ce void set_left_open   () { base::last()->set_left_open(); has_left_open = true; }

			nik_ce void set_init_closed()
			{
				base::last()->set_right_closed();
				set_init(Chord::diminished);
			}

			nik_ce void set_init_open()
			{
				base::last()->set_right_open();
				set_init(Chord::major);
				update_tone_augmented();
			}

			nik_ce void set_root_closed()
			{
				base::last()->set_right_closed();
				set_chord(Chord::diminished);
			}

			nik_ce void set_root_open()
			{
				base::last()->set_right_open();
				set_chord(Chord::major);
			}

			nik_ce void set_rest_closed()
			{
				base::last()->set_right_closed();
				update_chord(Chord::diminished);
			}

			nik_ce void set_rest_open()
			{
				base::last()->set_right_open();
				update_chord(Chord::major);
				update_tone_augmented();
			}

			nik_ce void push_note(csize_type p, const bool s = false)
				{ base::last()->push_note(p, s); }

			nik_ce void push_tonic()
			{
				const auto & next = base::last()->note_iter[Iter::next];
				const auto & prev = base::last()->note_iter[Iter::prev];

				base::last()->push_tonic(next.get_contr_pos(), next.get_side());
				base::last()->push_tonic(prev.get_contr_pos(), prev.get_side());
			}

		// iter:

			// note:

				nik_ce auto note_iter(csize_type n, csize_type m) const
					{ return base::operator[](n).note_iter[m]; }

				nik_ce auto note_iter(csize_type m) const
					{ return note_iter(base::max(), m); }

				nik_ce auto note_contr_pos(csize_type n, csize_type m) const
					{ return note_iter(n, m).get_contr_pos(); }

				nik_ce auto note_contr_pos(csize_type m) const
					{ return note_iter(m).get_contr_pos(); }

			// tonic:

				nik_ce auto tonic_iter(csize_type n, csize_type m) const
					{ return base::operator[](n).tonic_iter[m]; }

				nik_ce auto tonic_iter(csize_type m) const
					{ return tonic_iter(base::max(), m); }

				nik_ce auto tonic_contr_pos(csize_type n, csize_type m) const
					{ return tonic_iter(n, m).get_contr_pos(); }

				nik_ce auto tonic_contr_pos(csize_type m) const
					{ return tonic_iter(m).get_contr_pos(); }

				nik_ce auto is_tonic_reversible(csize_type n) const
					{ return base::operator[](n).is_tonic_reversible(); }

		// augmented:

			nik_ce auto is_tonic () const { return (augmented == Augmented::tonic); }
			nik_ce auto is_tone  () const { return (augmented == Augmented::tone); }
			nik_ce auto is_peek  () const { return (augmented == Augmented::peek); }

			nik_ce void update_tone_augmented()
				{ is_tone_augmented = is_tone_augmented && base::last()->is_note_reversible(); }

			nik_ce void resolve_augmented(csize_type root)
			{
				if      (is_tonic_reversible(root)) augmented = Augmented::tonic;
				else if (is_tone_augmented        ) augmented = Augmented::tone;
				else                                augmented = Augmented::peek;
			}

		// init:

			nik_ce void set_init(csize_type n) { init = n; }

		// chord:

			nik_ce auto is_major      () const { return (chord == Chord::major); }
			nik_ce auto is_augmented  () const { return (chord == Chord::augmented); }
			nik_ce auto is_diminished () const { return (chord == Chord::diminished); }
			nik_ce auto is_minor      () const { return (chord == Chord::minor); }

			nik_ce void set_chord(csize_type n) { chord = n; }

			nik_ce void update_chord(csize_type n)
			{
				if      (is_diminished()) update_chord_diminished(n);
				else if (is_major())      update_chord_major(n);
			}

			nik_ce void update_chord_diminished(csize_type n)
				{ if (n != Chord::diminished) chord = Chord::minor; }

			nik_ce void update_chord_major(csize_type n)
				{ if (n != Chord::major) chord = Chord::augmented; }

			nik_ce void resolve_chord(csize_type root)
			{
				update_chord(init);

				if (is_augmented()) resolve_augmented(root);
			}

		// next:

			nik_ce auto is_augmented_tonic () const { return is_augmented() && is_tonic(); }
			nik_ce auto is_augmented_peek  () const { return is_augmented() && is_peek(); }

			nik_ce auto has_left_next      () const { return has_left_open; }
			nik_ce auto has_left_prev      () const { return is_augmented_tonic(); }

			nik_ce auto has_right_action() const
			{
				if (is_augmented()) return not is_tone  ();
				else                return not is_major ();
			}

			nik_ce auto has_right_next() const
			{
				if (is_augmented()) return not is_tone  ();
				else                return     is_minor ();
			}

			nik_ce auto has_right_prev() const { return is_augmented() && is_tone(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tree:

/***********************************************************************************************************************/

// interface:

	template<auto... Vs> 
	struct T_chord_syntax_tree : public assembly::T_syntax_tree<Vs...>
	{
		using base		= assembly::T_syntax_tree<Vs...>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;
		using cselect		= typename base::cselect;
		using model_type	= typename base::model_type;
		using ModelEntry	= typename base::ModelEntry;

		using clist_type	= typename model_type::clist_type;
		using model_base	= typename model_type::base;
		using model_subbase	= typename model_base::base;

		struct ChordEntry	{ enum : size_type { label = ModelEntry::dimension, jump, dimension }; };
		struct JumpEntry	{ enum : size_type { pos   = ModelEntry::init, dimension }; };
		struct Routine		{ enum : size_type { combine, action, mutate, predicate, dimension }; };
		struct Iterate		{ enum : size_type { front, loop, back, dimension }; };
		struct Memoize		{ enum : size_type { inc, dec, dimension }; };

		using routine_seq	= sequence<size_type, static_cast<size_type>(Routine::dimension)>;
		using iterate_seq	= sequence<size_type, static_cast<size_type>(Iterate::dimension)>;
		using memoize_seq	= sequence<size_type, static_cast<size_type>(Memoize::dimension)>;
		using interval_seq	= T_chord_intervals<size_type, model_base::length>; // make size independent?
		using Iter		= typename interval_seq::Iter;

		model_type jump;
		routine_seq routine;
		iterate_seq iterate;
		memoize_seq memoize;
		interval_seq interval;

		nik_ce T_chord_syntax_tree() : base{}, jump{base::src}
		{
			routine.fullsize();
			iterate.fullsize();
			memoize.fullsize();
		}

		// cselect:

			nik_ce auto cselect_id        () const { return cctmp::string_literal("@").cselect(); }
			nik_ce auto cselect_first     () const { return cctmp::string_literal("first").cselect(); }
			nik_ce auto cselect_deref     () const { return cctmp::string_literal("*").cselect(); }
			nik_ce auto cselect_appoint   () const { return cctmp::string_literal("appoint").cselect(); }
			nik_ce auto cselect_not_equal () const { return cctmp::string_literal("not_equal").cselect(); }
			nik_ce auto cselect_inc       () const { return cctmp::string_literal("+").cselect(); }
			nik_ce auto cselect_dec       () const { return cctmp::string_literal("-").cselect(); }

		// label:

			nik_ce void define_label(const cselect & s)
			{
				csize_type pos = base::contr.current();

				if (base::model.lookup_variable(s)) { } // error.
				else base::model.define_variable(s, {ChordEntry::label, pos});
			}

		// jump:

			nik_ce void delay_define_jump(const cselect & s, csize_type name)
			{
				csize_type pos = base::contr.current(1);

				jump.define_variable(s, {ChordEntry::jump, pos});
				base::assembly_push_instr(name, AT::id);
			}

			nik_ce void delay_define_goto   (const cselect & s) { delay_define_jump(s, AN::go_to); }
			nik_ce void delay_define_branch (const cselect & s) { delay_define_jump(s, AN::branch); }

			nik_ce void force_define_jumps()
			{
				for (auto k = jump.env_origin(); jump.not_null(k); k = jump.cdr(k))
					force_define_frames(jump.car(k));
			}

			nik_ce void force_define_frames(clist_type frame)
			{
				for (auto k = frame; jump.not_null(k); k = jump.cdr(k))
					force_define_bindings(jump.car(k));
			}

			nik_ce void force_define_bindings(clist_type binding)
			{
				if (base::model.lookup_variable(jump.get_name(binding)))
				{
					auto entry = jump.cdr(binding);
					auto pos   = static_cast<model_subbase>(jump).get_value(entry, JumpEntry::pos);
					auto value = base::model.get_value(JumpEntry::pos);

					base::contr.set_instr_value(pos, cctmp::Instr::pos, value);
				}
				else { } // error.
			}

		// morph:

			nik_ce void morph_op_begin(const cselect & s)
			{
				base::force_define_compound(s);
				base::force_define_arity();
				base::define_op_begin();
			}

			nik_ce void morph_op_end()
			{
				base::apply_end();
				base::define_op_end();
			}

			nik_ce void morph_op_range() { base::count.reset(); }

			nik_ce void morph_op_return(const cselect & s)
			{
				base::apply_begin(s);
				base::lookup_return(s);
			}

		// subpose:

			nik_ce void subpose_value(const cselect & s, const bool mute = false)
			{
				auto is_id = cctmp::apply<_subarray_same_<>>(s, cselect_id());

				if (is_id) subpose_value_id(mute);
				else       subpose_value_apply(s, mute);
			}

			nik_ce void subpose_value_id(const bool mute)
			{
				base::back_lookup_return(base::count.inc_size(), mute);
				base::stage.upsize();
			}

			nik_ce void subpose_value_apply(const cselect & s, const bool mute)
			{
				base::apply_begin(s);
				base::lookup_return(s);
				subpose_value_id(mute);
				base::apply_end();
			}

		// routine:

			nik_ce auto get_combine   () const { return routine[Routine::combine  ]; }
			nik_ce auto get_action    () const { return routine[Routine::action   ]; }
			nik_ce auto get_mutate    () const { return routine[Routine::mutate   ]; }
			nik_ce auto get_predicate () const { return routine[Routine::predicate]; }

			nik_ce void set_combine   () { base::count.cache(Routine::combine  ); }
			nik_ce void set_action    () { base::count.cache(Routine::action   ); }
			nik_ce void set_mutate    () { base::count.cache(Routine::mutate   ); }
			nik_ce void set_predicate () { base::count.cache(Routine::predicate); }

			nik_ce void set_routine() { routine[base::count.cache()] = base::contr.current(); }

			nik_ce void internal_defs_begin () { base::template assembly_action<AAN::go_to, AAT::begin>(); }
			nik_ce void internal_defs_end   () { base::template assembly_action<AAN::go_to, AAT::end>(); }

		// action:

			nik_ce void act_subpose_begin(csize_type n)
			{
				base::push_verse_stage();
				base::force_define_arity(n);
				base::template assembly_action<AAN::id, AAT::begin>();
				morph_op_range();
			}

			nik_ce void act_subpose_end()
			{
				base::apply_end();
				base::verse.current.pop();
				base::stage.current.pop();
				base::first_return();
			}

			nik_ce void act_subpose_op(const cselect & s)
			{
				set_routine();
				morph_op_return(s);
			}

			nik_ce void act_subpose_values(const cselect & s, csize_type b = 0, csize_type e = 2)
				{ for (auto k = b; k != e; ++k) subpose_value(s); }

		// iterator:

			nik_ce void note_next_assembly(csize_type arg_pos)
			{
				auto pos = base::verse.size();
				auto num = base::verse.size() + arg_pos;

				base::assembly_push_instr(AN::arg, AT::verse, pos, num);
			}

			nik_ce void note_push_assembly(csize_type note)
			{
				base::template assembly_action<AAN::id, AAT::begin>();
				base::assembly_push_instr(AN::next, note);
			}

			// value:

				nik_ce void note_push_value(const cselect & s)
				{
					auto name = AN::next;
					auto note = AT::side;
					auto act  = base::contr.current(1);
					auto mut  = get_mutate();

					act_subpose_begin(1);
					morph_op_return(s);
					subpose_value_id(false); // mute ?
					act_subpose_end();

					interval.push_note(base::contr.current(1));

					base::template assembly_action<AAN::id, AAT::begin>();
					base::assembly_push_instr(name, note, act, mut);
				}

			// memoize:

				nik_ce void note_push_memoize(csize_type pos, csize_type note)
				{
					if (memoize[pos]) note_push_memoize_interval(pos);
					else              note_push_memoize_assembly(pos, note);
				}

				nik_ce void note_push_memoize_interval(csize_type pos)
					{ interval.push_note(memoize[pos]); }

				nik_ce void note_push_memoize_assembly(csize_type pos, csize_type note)
				{
					memoize[pos] = base::contr.current(1);

					note_push_memoize_interval(pos);
					note_push_assembly(note);
				}

			// inc, dec:

				nik_ce void note_push_inc() { note_push_memoize(Memoize::inc, AT::inc); }
				nik_ce void note_push_dec() { note_push_memoize(Memoize::dec, AT::dec); }

			// tonic:

				nik_ce void tonic_push() { interval.push_tonic(); }

		// interval:

			template<typename Prog>
			nik_ce void resolve_interval() { interval.resolve_chord(Prog::Ival::root); }

		// internal:

			template<typename Prog>
			nik_ce void define_internal()
			{
				Prog::define_internal_action(this);
				internal_defs_end();
			}

		// cycle:

			template<typename Prog>
			nik_ce void define_cycle()
			{
				define_cycle_before      ();
				define_cycle_loop<Prog>  ();
				define_cycle_after<Prog> ();
				interval.reset           ();
			}

			// before:

				nik_ce void define_cycle_before()
				{
					auto b = interval.has_left_next() || interval.has_left_prev();
					auto s = base::verse.size();

					if (b) define_cycle_front();
					base::assembly_push_instr(AN::arg, AT::select, s);
				}

				nik_ce void define_cycle_front()
				{
					auto ni = iterate[Iterate::front];

					base::assembly_push_instr(AN::cycle, AT::front, ni);
				}

			// loop:

				template<typename Prog>
				nik_ce void define_cycle_loop() { Prog::define_loop_action(this); }

			// after:

				template<typename Prog>
				nik_ce void define_cycle_after()
				{
					auto a = interval.has_right_action();
					auto b = interval.has_right_next() || interval.has_right_prev();
					auto s = base::verse.size();

					if (a) Prog::define_back_action(this);
					if (b) define_cycle_back_next();
					base::assembly_push_instr(AN::arg, AT::drop, s);
					base::first_return();
				}

				nik_ce void define_cycle_back_next()
				{
					auto ni = iterate[Iterate::back];

					base::assembly_push_instr(AN::cycle, AT::back, ni);
				}

		// functional:

			nik_ce void define_repeat()
			{
				using Prog = T_chord_repeat<size_type>;

				resolve_interval<Prog>();
				define_internal<Prog>();
				define_cycle<Prog>();
			}

			nik_ce void define_map()
			{
				using Prog = T_chord_map<size_type>;

				resolve_interval<Prog>();
				define_internal<Prog>();
				define_cycle<Prog>();
			}

			nik_ce void define_fold()
			{
				using Prog = T_chord_fold<size_type>;

				resolve_interval<Prog>();
				define_internal<Prog>();
				define_cycle<Prog>();
			}

			nik_ce void define_find()
			{
				using Prog = T_chord_find<size_type>;

				resolve_interval<Prog>();
				define_internal<Prog>();
				define_cycle<Prog>();
			}

			nik_ce void define_sift()
			{
				using Prog = T_chord_sift<size_type>;

				resolve_interval<Prog>();
				define_internal<Prog>();
				define_cycle<Prog>();
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automaton:

/***********************************************************************************************************************/

// interface:

#ifdef NIK_CHORD_PARSER
#include NIK_CHORD_PARSER_OBJ
#else

	template<typename T_grammar>
	struct T_chord_pda : public generator::T_generic_pda<T_grammar>
	{
		using base			= generator::T_generic_pda<T_grammar>;
		using ActName			= typename T_grammar::ActName;
		using T_lexer			= typename T_grammar::T_lexer;
		using Token			= typename T_grammar::Token;

		nik_ces auto prod_size		= cctmp::string_literal("{C|A|M|P}").size(); // needs refining.

		nik_ces auto stack_start	= symbol_type{generator::Sign::nonterminal, base::start_index};
		nik_ces auto stack_finish	= symbol_type{generator::Sign::terminal, Token::prompt};

		nik_ces auto stack_size		= cctmp::literal("F{C|A|M|P}YPZ<>YPZYP,PZV;HGO").size(); // needs refining.
							// literal is intentional.
							// this is the longest possible sentential.
							// might need updating.
	};

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser:

/***********************************************************************************************************************/

// interface:

	template<auto static_pg_parsed, typename T_action, typename T_grammar>
	struct T_chord_parser
	{
		using T_ast		= typename T_action::T_ast;
		using T_pda		= T_chord_pda<T_grammar>;
		using T_parser		= generator::T_generic_parser<T_action, T_pda>;
		using parseme_type	= generator::T_parseme<T_ast>;
		using parsoid_type	= generator::T_parsoid<T_pda::stack_size, T_pda::prod_size>;

		nik_ces auto & pda	= T_parser::pda; static_assert(!pda.ambiguous, "ambiguous cfg!");

		parseme_type parseme;
		parsoid_type parsoid;

		nik_ce T_chord_parser(const cselector<char> & s) :

			parseme(s), parsoid{T_pda::stack_start, T_pda::stack_finish}

			{ parse(parseme, parsoid); }

		nik_ces void parse(parseme_type & p, parsoid_type & q)
			{ T_parser::parse(p, q); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parsed:

/***********************************************************************************************************************/

// translation action:

	template<action_type, auto...> struct T_chord_translation_action;

	template<typename AST>
	struct T_chord_ta :
		public generator::T_generic_translation_action<T_chord_translation_action, AST, CAAN>
			{ };

	// interface:

		template<typename AST>
		struct T_chord_action
		{
			using T_ast		= AST;

			nik_ces auto value	= T_chord_ta<AST>{};
			using type		= decltype(value);
		};

/***********************************************************************************************************************/

// interface:

	template
	<
		auto static_pg_parsed, auto static_source, auto static_env_lookup,
		auto contr_size, auto stack_size, auto model_size
	>
	struct T_chord_parsed
	{
		using T_ast			= T_chord_syntax_tree
						<
							static_source, static_env_lookup,
							contr_size, stack_size, model_size
						>;
		using T_action			= T_chord_action<T_ast>;
		using T_grammar			= T_chord_grammar;
		using T_parser			= T_chord_parser<static_pg_parsed, T_action, T_grammar>;

		nik_ces auto & src		= member_value_U<static_source>;
		nik_ces auto parser		= T_parser{src.cselect()};
		nik_ces auto & value		= parser.parseme.tree;
		using type			= modify_type<_from_reference_, decltype(value)>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

