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
		struct Iterate		{ enum : size_type { preloop, loop, postloop, cond, dimension }; };
		struct Memoize		{ enum : size_type { inc, dec, dimension }; };

		using routine_seq	= sequence<size_type, static_cast<size_type>(Routine::dimension)>;
		using iterate_seq	= sequence<size_type, static_cast<size_type>(Iterate::dimension)>;
		using memoize_seq	= sequence<size_type, static_cast<size_type>(Memoize::dimension)>;
		using interval_seq	= T_chord_intervals<size_type, model_base::length>; // make size independent?
		using Iter		= typename interval_seq::Iter;
		using Ival		= typename interval_seq::Ival;

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

		//	template<typename Prog>
		//	nik_ce void resolve_interval() { interval.resolve_chord(Prog::Ival::root); }

		// internal:

		//	template<typename Prog>
		//	nik_ce void define_internal()
		//	{
		//		Prog::define_internal_action(this);
		//		internal_defs_end();
		//	}

		// cycle:

		//	template<typename Prog>
		//	nik_ce void define_cycle()
		//	{
		//		define_cycle_before      ();
		//		define_cycle_loop<Prog>  ();
		//		define_cycle_after<Prog> ();
		//		interval.reset           ();
		//	}

			// before:

			//	nik_ce void define_cycle_before()
			//	{
			//		auto b = interval.has_left_next() || interval.has_left_prev();
			//		auto s = base::verse.size();

			//		if (b) define_cycle_front();
			//		base::assembly_push_instr(AN::arg, AT::select, s);
			//	}

			//	nik_ce void define_cycle_front()
			//	{
			//		auto ni = iterate[Iterate::front];

			//		base::assembly_push_instr(AN::cycle, AT::front, ni);
			//	}

			// loop:

			//	template<typename Prog>
			//	nik_ce void define_cycle_loop() { Prog::define_loop_action(this); }

			// after:

			//	template<typename Prog>
			//	nik_ce void define_cycle_after()
			//	{
			//		auto a = interval.has_right_action();
			//		auto b = interval.has_right_next() || interval.has_right_prev();
			//		auto s = base::verse.size();

			//		if (a) Prog::define_back_action(this);
			//		if (b) define_cycle_back_next();
			//		base::assembly_push_instr(AN::arg, AT::drop, s);
			//		base::first_return();
			//	}

			//	nik_ce void define_cycle_back_next()
			//	{
			//		auto ni = iterate[Iterate::back];

			//		base::assembly_push_instr(AN::cycle, AT::back, ni);
			//	}

		// functional:

			nik_ce void define_repeat()
			{
				T_repeat_internal<size_type>::define(this, Ival::out);
				internal_defs_end();

				T_repeat_construct<size_type>::define(this);
				interval.reset();
			}

			nik_ce void define_map()
			{
				T_map_internal<size_type>::define(this, Ival::in);
				internal_defs_end();

				T_map_construct<size_type>::define(this);
				interval.reset();
			}

			nik_ce void define_fold()
			{
				T_fold_internal<size_type>::define(this, Ival::in);
				internal_defs_end();

				T_fold_construct<size_type>::define(this);
				interval.reset();
			}

			nik_ce void define_find()
			{
				T_find_internal<size_type>::define(this, Ival::in);
				internal_defs_end();

				T_find_construct<size_type>::define(this);
				interval.reset();
			}

			nik_ce void define_sift()
			{
				T_sift_internal<size_type>::define(this, Ival::in);
				internal_defs_end();

				T_sift_construct<size_type>::define(this);
				interval.reset();
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

