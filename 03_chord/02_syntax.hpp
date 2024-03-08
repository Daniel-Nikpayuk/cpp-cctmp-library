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

// tree:

/***********************************************************************************************************************/

// interval:

	template<typename SizeType>
	struct T_chord_iterator
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		struct Iter		{ enum : size_type { next, prev, dimension }; };

		size_type pos;
		bool side;

		nik_ce T_chord_iterator() : pos{}, side{} { }
		nik_ce T_chord_iterator(csize_type p, const bool s) : pos{p}, side{s} { }

		// pos:

			nik_ce auto get_pos() const { return pos; }
			nik_ce void set_pos(csize_type p) { pos = p; }

		// side:

			nik_ce auto get_side() const { return side; }
			nik_ce void set_side(const bool s) { side = s; }
	};

/***********************************************************************************************************************/

// interval:

	template<typename SizeType>
	struct T_chord_interval
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;
		using iter_type		= T_chord_iterator<size_type>;
		using Iter		= typename iter_type::Iter;

		struct Ival		{ enum : size_type { tone, root, dimension }; };
		struct Point		{ enum : size_type { fixed, closed, open, dimension }; };

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

			nik_ce void set_left  (csize_type p) { left = p; }
			nik_ce void set_right (csize_type p) { right = p; }

			nik_ce void set_left_closed  () { set_left(Point::closed); }
			nik_ce void set_left_open    () { set_left(Point::open); }
			nik_ce void set_right_closed () { set_right(Point::closed); }
			nik_ce void set_right_open   () { set_right(Point::open); }

			nik_ce void set_fixed()
			{
				set_left(Point::fixed);
				set_right(Point::fixed);
			}

		// note:

			nik_ce void push_note(csize_type p, const bool s = false)
				{ note_iter.push(iter_type{p, s}); }

		// tonic:

			nik_ce void push_tonic(csize_type p, const bool s = false)
			{
				ival = Ival::root;
				tonic_iter.push(iter_type{p, s});
			}

			nik_ce void push_tonic()
			{
				const auto & next = note_iter[Iter::next];
				const auto & prev = note_iter[Iter::prev];

				push_tonic(next.get_pos(), next.get_side());
				push_tonic(prev.get_pos(), prev.get_side());
			}
	};

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
		struct CycleId		{ enum : size_type { predicate, side, dimension }; };
		struct CycleSide	{ enum : size_type { action, next, dimension }; };
		struct Routine		{ enum : size_type { combine, action, mutate, predicate, dimension }; };
		struct CycleNext	{ enum : size_type { inc, dec, dimension }; };

		using cycle_id_seq	= sequence<size_type, static_cast<size_type>(CycleId::dimension)>;
		using cycle_side_seq	= sequence<size_type, static_cast<size_type>(CycleSide::dimension)>;
		using cycle_next_seq	= sequence<size_type, static_cast<size_type>(CycleNext::dimension)>;
		using routine_seq	= sequence<size_type, static_cast<size_type>(Routine::dimension)>;
		using interval_type	= T_chord_interval<size_type>;
		using interval_seq	= sequence<interval_type, model_base::length>; // make size independent?

		model_type jump;
		cycle_id_seq cycle_id;
		cycle_side_seq cycle_side;
		cycle_next_seq cycle_next;
		routine_seq routine;
		interval_seq interval;

		nik_ce T_chord_syntax_tree() : base{}, jump{base::src}
		{
			cycle_id.fullsize   ();
			cycle_side.fullsize ();
			cycle_next.fullsize ();
			routine.fullsize    ();
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
				base::template assembly_action<AAN::push, AAT::instr>(name, AT::id);
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

		// interval:

		// iterator:

			nik_ce auto note_pos(csize_type n, csize_type m) const
				{ return interval[n].note_iter[m].get_pos(); }

			nik_ce auto note_last(csize_type m) const { return note_pos(interval.max(), m); }

			nik_ce void push_iter(csize_type pos, csize_type note)
			{
				if (cycle_next[pos]) push_iter_interval(pos);
				else                 push_iter_assembly(pos, note);
			}

			nik_ce void push_iter_interval(csize_type pos)
				{ interval.last()->push_note(cycle_next[pos]); }

			nik_ce void push_iter_assembly(csize_type pos, csize_type note)
			{
				cycle_next[pos] = base::contr.current(1);

				push_iter_interval(pos);
				push_iter_assembly(note);
			}

			nik_ce void push_iter_assembly(csize_type note)
			{
				base::template assembly_action< AAN::id   , AAT::begin >();
				base::template assembly_action< AAN::push , AAT::instr >(AN::next, note);
			}

			// fast:

				nik_ce void push_inc() { push_iter(CycleNext::inc, AT::inc); }
				nik_ce void push_dec() { push_iter(CycleNext::dec, AT::dec); }

			// tonic:

				nik_ce void push_tonic() { interval.last()->push_tonic(); }

		// cycle:

			nik_ce void define_precycle()
			{
				auto s = base::verse.size();

				base::template assembly_action<AAN::push, AAT::instr>(AN::arg, AT::select, s);
			}

			nik_ce void define_cycle()
			{
				auto ni = cycle_id[CycleId::predicate];
				auto mi = cycle_id[CycleId::side];

				base::template assembly_action<AAN::push, AAT::instr>(AN::cycle, AT::id, ni, mi);
			}

			nik_ce void define_postcycle()
			{
				auto s = base::verse.size();

				base::template assembly_action<AAN::push, AAT::instr>(AN::arg, AT::drop, s);
				base::first_return();
			}

			nik_ce void define_cycle_side()
			{
				auto ni = cycle_side[CycleSide::action];
				auto mi = cycle_side[CycleSide::next];

				cycle_id[CycleId::side] = base::contr.current(1);
				base::template assembly_action<AAN::id, AAT::begin>();
				base::template assembly_action<AAN::push, AAT::instr>(AN::cycle, AT::side, ni, mi);
			}

			nik_ce void define_loop()
			{
				define_cycle_side ();
				internal_defs_end ();
				define_precycle   ();
				define_cycle      ();
				define_postcycle  ();
			}

		// next:

			nik_ce void define_next_begin(csize_type arg_pos)
			{
				cycle_side[CycleSide::next] = base::contr.current(1);
				base::template assembly_action<AAN::id, AAT::begin>();
				base::template assembly_action<AAN::push, AAT::instr>(AN::arg, AT::select, arg_pos);
			}

			nik_ce void define_next_cont_fast(csize_type ival_pos, csize_type arg_pos)
			{
				auto ni = note_pos(ival_pos, 0);

				base::template assembly_action<AAN::push, AAT::instr>(AN::next, AT::cont, ni, arg_pos);
			}

			nik_ce void define_next_cont(csize_type ival_pos, csize_type arg_pos)
				{ if (interval[ival_pos].not_fixed()) define_next_cont_fast(ival_pos, arg_pos); }

			nik_ce void define_next_rest(csize_type b, csize_type n)
				{ for (auto k = b; k != interval.max(); ++k) define_next_cont(k, n + k); }

			nik_ce void define_next_end()
				{ base::template assembly_action<AAN::push, AAT::instr>(AN::next, AT::last, note_last(0)); }

		// repeat:

			nik_ce void define_repeat()
			{
			}

		// map:

			nik_ce void define_map()
			{
			}

		// fold:

			nik_ce void define_fold_pred()
			{
				auto ni = get_predicate();

				cycle_id[CycleId::predicate] = base::contr.current(1);
				base::template assembly_action<AAN::id, AAT::begin>();
				base::template assembly_action<AAN::push, AAT::instr>(AN::fold, AT::pred, ni);
			}

			nik_ce void define_fold_action()
			{
				auto ni = get_action();
				auto mi = get_combine();
				auto li = get_mutate();

				cycle_side[CycleSide::action] = base::contr.current(1);
				base::template assembly_action<AAN::id, AAT::begin>();
				base::template assembly_action<AAN::push, AAT::instr>(AN::fold, AT::act, ni, mi, 2);
				base::template assembly_action<AAN::push, AAT::instr>(li, 0);
			}

			nik_ce void define_fold_precycle()
			{
			}

			nik_ce void define_fold_cycle()
			{
				auto n = base::verse.size();
				auto l = n + 1; // in
				auto m = n + 3; // in1

				define_fold_pred   (    );
				define_fold_action (    );

				define_next_begin  (l   );
				define_next_cont   (1, m); // in
				define_next_rest   (2, m); // in1
				define_next_end    (    );
			}

			nik_ce void define_fold_postcycle()
			{
			}

			nik_ce void define_fold()
			{
				define_fold_precycle  ();
				define_fold_cycle     ();
				define_fold_postcycle ();

				define_loop();
			}

		// find:

			nik_ce void define_find()
			{
			}

		// sift:

			nik_ce void define_sift()
			{
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

