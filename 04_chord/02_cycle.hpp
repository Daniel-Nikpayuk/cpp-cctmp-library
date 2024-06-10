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

// cycle:

namespace chord {

	// progression paradigm:

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
		bool alt_mutate;

		nik_ce T_chord_iterator() : contr_pos{}, alt_mutate{} { }

		nik_ce void reset() { push(0, false); }

		nik_ce void push(csize_type p, const bool m)
		{
			contr_pos  = p;
			alt_mutate = m;
		}

		// contr pos:

			nik_ce auto get_contr_pos() const { return contr_pos; }
			nik_ce void set_contr_pos(csize_type p) { contr_pos = p; }

		// alt mutate:

			nik_ce auto is_alt_mutate() const { return alt_mutate; }
			nik_ce void set_alt_mutate() { alt_mutate = true; }
	};

/***********************************************************************************************************************/

// iterators:

	template<typename SizeType>
	struct T_chord_iterators
	{
		using iterator_type	= T_chord_iterator<SizeType>;
		using size_type		= typename iterator_type::size_type;
		using csize_type	= typename iterator_type::csize_type;

		struct Iter		{ enum : size_type { next, prev, dimension }; };

		bool inhabited;
		bool reversible;
		iterator_type next_iter;
		iterator_type prev_iter;

		nik_ce T_chord_iterators() : inhabited{}, reversible{} { }

		nik_ce void reset()
		{
			inhabited  = false;
			reversible = false;

			next_iter.reset();
			prev_iter.reset();
		}

		nik_ce bool is_inhabited() const { return inhabited; }
		nik_ce void set_inhabited() { inhabited = true; }

		nik_ce bool is_reversible() const { return reversible; }
		nik_ce void set_reversible() { reversible = true; }

		nik_ce const auto & operator [] (const bool n) const { return n ? prev_iter : next_iter; }

		nik_ce void push_inhabited(csize_type p, const bool m)
		{
			next_iter.push(p, m);
			set_inhabited();
		}

		nik_ce void push_reversible(csize_type p, const bool m)
		{
			prev_iter.push(p, m);
			set_reversible();
		}

		nik_ce void push(csize_type p, const bool m)
		{
			if      (not inhabited ) push_inhabited  (p, m);
			else if (not reversible) push_reversible (p, m);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// interval:

/***********************************************************************************************************************/

// interface:

	template<typename SizeType>
	struct T_chord_interval
	{
		using iters_type	= T_chord_iterators<SizeType>;
		using size_type		= typename iters_type::size_type;
		using csize_type	= typename iters_type::csize_type;
		using Iter		= typename iters_type::Iter;

		struct Point		{ enum : size_type { fixed, closed, open, dimension }; };

		size_type left_pt;
		size_type right_pt;
		iters_type notes;
		iters_type tonics;

		nik_ce T_chord_interval() : left_pt{Point::fixed}, right_pt{Point::fixed} { }

		nik_ce void reset()
		{
			left_pt  = Point::fixed;
			right_pt = Point::fixed;

			notes.reset();
			tonics.reset();
		}
	
		// point:

			nik_ce auto not_left_fixed  () const { return (left_pt  != Point::fixed); }
			nik_ce auto not_right_fixed () const { return (right_pt != Point::fixed); }
			nik_ce auto not_fixed       () const { return (not_left_fixed() && not_right_fixed()); }
								// [> (cond interval) is not fixed.

			nik_ce auto is_left_open    () const { return (left_pt  == Point::open); }
			nik_ce auto is_right_open   () const { return (right_pt == Point::open); }
			nik_ce auto is_right_closed () const { return (right_pt == Point::closed); }

			nik_ce void set_left  (csize_type p) { left_pt = p; }
			nik_ce void set_right (csize_type p) { right_pt = p; }

			nik_ce void set_left_fixed   () { set_left  (Point::fixed  ); }
			nik_ce void set_left_closed  () { set_left  (Point::closed ); }
			nik_ce void set_left_open    () { set_left  (Point::open   ); }
			nik_ce void set_right_fixed  () { set_right (Point::fixed  ); }
			nik_ce void set_right_closed () { set_right (Point::closed ); }
			nik_ce void set_right_open   () { set_right (Point::open   ); }

		// notes:

			nik_ce bool is_note_reversible() const { return notes.is_reversible(); }

			nik_ce void push_note(csize_type p, const bool m) { notes.push(p, m); }

		// tonics:

			nik_ce bool is_tonic_reversible() const { return tonics.is_reversible(); }

			nik_ce void push_tonic(csize_type p, const bool m) { tonics.push(p, m); }
	};

/***********************************************************************************************************************/

// intervals:

	template<typename SizeType, SizeType Size>
	struct T_chord_intervals
	{
		using interval_type	= T_chord_interval<SizeType>;
		using interval_seq	= sequence<interval_type, Size>;
		using size_type		= typename interval_type::size_type;
		using csize_type	= typename interval_type::csize_type;
		using Iter		= typename interval_type::Iter;

		struct Chord		{ enum : size_type { none, major, augmented, diminished, minor, dimension }; };
		struct Augment		{ enum : size_type { none, tonic, tone, peek, dimension }; };
		struct Ival		{ enum : size_type { out, in, ins, dimension }; };

		size_type chord;
		size_type augment;
		bool has_left_open;
		bool tone_augment_avail;

		interval_seq interval;

		nik_ce T_chord_intervals() :
			chord{Chord::none}, augment{Augment::none}, has_left_open{}, tone_augment_avail{true}
				{ }

		nik_ce auto size() const { return interval.size(); }
		nik_ce void upsize() { interval.upsize(); }

		nik_ce void reset()
		{
			chord   = Chord::none;
			augment = Augment::none;

			has_left_open      = false;
			tone_augment_avail = true;

			for (auto k = interval.begin(); k != interval.end(); ++k) k->reset();
			interval.clear();
		}

		// iter:

			// note:

				nik_ce auto note_iter(csize_type n, const bool m) const
					{ return interval[n].notes[m]; }

				nik_ce auto note_iter(const bool m) const
					{ return note_iter(interval.max(), m); }

				nik_ce auto note_contr_pos(csize_type n, const bool m) const
					{ return note_iter(n, m).get_contr_pos(); }

				nik_ce auto note_contr_pos(const bool m) const
					{ return note_iter(m).get_contr_pos(); }

			// tonic:

				nik_ce auto tonic_iter(csize_type n, const bool m) const
					{ return interval[n].tonics[m]; }

				nik_ce auto tonic_iter(const bool m) const
					{ return tonic_iter(interval.max(), m); }

				nik_ce auto tonic_contr_pos(csize_type n, const bool m) const
					{ return tonic_iter(n, m).get_contr_pos(); }

				nik_ce auto tonic_contr_pos(const bool m) const
					{ return tonic_iter(m).get_contr_pos(); }

				nik_ce auto is_tonic_reversible(csize_type n) const
					{ return interval[n].is_tonic_reversible(); }

		// chord:

			nik_ce auto is_none       () const { return (chord == Chord::none); }
			nik_ce auto is_major      () const { return (chord == Chord::major); }
			nik_ce auto is_augmented  () const { return (chord == Chord::augmented); }
			nik_ce auto is_diminished () const { return (chord == Chord::diminished); }
			nik_ce auto is_minor      () const { return (chord == Chord::minor); }

			nik_ce void set_chord(csize_type n) { chord = n; }

			nik_ce void update_chord(csize_type n)
			{
				if      (is_major      ()) update_chord_major(n);
				else if (is_diminished ()) update_chord_diminished(n);
			}

			nik_ce void update_chord_major(csize_type n)
				{ if (n != Chord::major) chord = Chord::augmented; }

			nik_ce void update_chord_diminished(csize_type n)
				{ if (n != Chord::diminished) chord = Chord::minor; }

		// augment:

			nik_ce auto is_tonic () const { return (augment == Augment::tonic); }
			nik_ce auto is_tone  () const { return (augment == Augment::tone); }
			nik_ce auto is_peek  () const { return (augment == Augment::peek); }

			nik_ce void update_tone_augment(csize_type n)
				{ tone_augment_avail = tone_augment_avail && interval[n].is_note_reversible(); }

			nik_ce void update_tone_augment() { update_tone_augment(interval.max()); }

			nik_ce void resolve_augment(csize_type root)
			{
				if      (is_tonic_reversible(root)) augment = Augment::tonic;
				else if (tone_augment_avail       ) augment = Augment::tone;
				else                                augment = Augment::peek;
			}

		// resolution:

			nik_ce auto is_augmented_tonic () const { return is_augmented() && is_tonic(); }
			nik_ce auto is_augmented_tone  () const { return is_augmented() && is_tone(); }
			nik_ce auto is_augmented_peek  () const { return is_augmented() && is_peek(); }

			nik_ce auto has_left_next () const { return has_left_open; }
			nik_ce auto has_left_prev () const { return is_augmented_tonic(); }

		// interval (random access):

			nik_ce auto not_fixed       (csize_type n) const { return interval[n].not_fixed(); }
			nik_ce auto is_left_open    (csize_type n) const { return interval[n].is_left_open(); }
			nik_ce auto is_right_open   (csize_type n) const { return interval[n].is_right_open(); }
			nik_ce auto is_right_closed (csize_type n) const { return interval[n].is_right_closed(); }

			nik_ce auto baseline_chord  (csize_type n) const
				{ return is_right_closed(n) ? Chord::diminished : Chord::major; }

		// set (construct):

			// fixed:

				nik_ce void set_fixed()
				{
					interval.last()->set_left_fixed();
					interval.last()->set_right_fixed();
				}

			// match:

				nik_ce void set_match()
				{
					interval.last()->set_left_closed();
					interval.last()->set_right_fixed();
				}

			// ival:

				nik_ce void set_ival_left_closed()
					{ interval.last()->set_left_closed(); }

				nik_ce void set_ival_left_open()
				{
					interval.last()->set_left_open();
					has_left_open = true;
				}

				nik_ce void set_ival_right_closed()
				{
					interval.last()->set_right_closed();
					update_chord(Chord::diminished);
				}

				nik_ce void set_ival_right_open()
				{
					interval.last()->set_right_open();
					update_chord(Chord::major);
					update_tone_augment();
				}

			// pre ival:

				nik_ce void set_pre_ival_right_closed()
					{ interval.last()->set_right_closed(); }

				nik_ce void set_pre_ival_right_open()
					{ interval.last()->set_right_open(); }

			// root (establishes the baseline chord):

				nik_ce void set_root_right_closed()
				{
					interval.last()->set_right_closed();
					set_chord(Chord::diminished);
				}

				nik_ce void set_root_right_open()
				{
					interval.last()->set_right_open();
					set_chord(Chord::major);
				}

			// post root:

				nik_ce void set_post_root_right_closed()
				{
					set_root_right_closed();
					update_chord(baseline_chord(Ival::out));
				}

				nik_ce void set_post_root_right_open()
				{
					set_root_right_open();
					update_chord(baseline_chord(Ival::out));
					update_tone_augment(Ival::out);
				}

			// push note:

				nik_ce void push_note(csize_type p, const bool m = false)
					{ interval.last()->push_note(p, m); }

			// push tonic:

				nik_ce void push_tonic()
				{
					const auto & next = interval.last()->notes.next_iter;
					const auto & prev = interval.last()->notes.prev_iter;

					interval.last()->push_tonic(next.get_contr_pos(), next.is_alt_mutate());
					interval.last()->push_tonic(prev.get_contr_pos(), prev.is_alt_mutate());
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// internal (construct):

/***********************************************************************************************************************/

// interface:

	template<typename SizeType>
	struct T_internal
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		template<typename AST>
		nik_ces void initialize(AST *t, csize_type iter)
		{
	      		t->iterate[iter] = t->contr.current(1);

		      	t->assembly_id_begin();
		}

		template<typename AST>
		nik_ces void terminalize(AST *t) { t->assembly_push_instr(AN::halt, AT::none); }

		// note:

			template<typename AST>
			nik_ces void define_note(AST *t, csize_type ival_pos, csize_type arg_pos, csize_type dir)
			{
				auto ni = t->interval.note_contr_pos(ival_pos, dir);

				t->note_next_assembly(arg_pos);
				t->assembly_push_instr(AN::next, AT::id, ni);
			}

		// tonic:

			template<typename AST>
			nik_ces void define_tonic(AST *t, csize_type ival_pos, csize_type arg_pos, csize_type dir)
			{
				auto ni = t->interval.tonic_contr_pos(ival_pos, dir);

				t->note_next_assembly(arg_pos);
				t->assembly_push_instr(AN::next, AT::id, ni);
			}

		// next:

			// note:

				template<typename AST>
				nik_ces void define_next_note(AST *t, csize_type ival_pos, csize_type arg_pos)
					{ define_note(t, ival_pos, arg_pos, AST::Iter::next); }

			// tonic:

				template<typename AST>
				nik_ces void define_next_tonic(AST *t, csize_type ival_pos, csize_type arg_pos)
					{ define_tonic(t, ival_pos, arg_pos, AST::Iter::next); }

		// prev:

			// note:

				template<typename AST>
				nik_ces void define_prev_note(AST *t, csize_type ival_pos, csize_type arg_pos)
					{ define_note(t, ival_pos, arg_pos, AST::Iter::prev); }

			// tonic:

				template<typename AST>
				nik_ces void define_prev_tonic(AST *t, csize_type ival_pos, csize_type arg_pos)
					{ define_tonic(t, ival_pos, arg_pos, AST::Iter::prev); }
	};

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_internal_precycle : public T_internal<SizeType>
	{
		using base		= T_internal<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		template<typename AST>
		nik_ces void initialize(AST *t) { base::initialize(t, AST::Iterate::preloop); }

		template<typename AST>
		nik_ces void initialize_if(AST *t) { if (t->interval.has_left_next()) initialize(t); }

		template<typename AST>
		nik_ces void terminalize_if(AST *t) { if (t->interval.has_left_next()) base::terminalize(t); }

		// next note:

			template<typename AST>
			nik_ces void define_next_note_if(AST *t, csize_type ival_pos, csize_type arg_pos)
				{ if (t->interval.is_left_open(ival_pos)) base::define_next_note(t, ival_pos, arg_pos); }

		// next notes:

			template<typename AST>
			nik_ces void define_next_note_ifs(AST *t, csize_type ival_beg, size_type arg_pos)
			{
				for (auto ival_pos = ival_beg; ival_pos != t->interval.size(); ++ival_pos)
					define_next_note_if(t, ival_pos, arg_pos++);
			}

			template<typename AST>
			nik_ces void define_next_note_ifs_fast(AST *t, csize_type ival_beg, size_type arg_pos)
				{ if (t->interval.has_left_next()) define_next_note_ifs(t, ival_beg, arg_pos); }
	};

/***********************************************************************************************************************/

// cycle:

	template<typename SizeType>
	struct T_internal_cycle : public T_internal<SizeType>
	{
		using base		= T_internal<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		template<typename AST>
		nik_ces void initialize(AST *t) { base::initialize(t, AST::Iterate::loop); }

		template<typename AST>
		nik_ces void initialize_cond(AST *t) { base::initialize(t, AST::Iterate::cond); }

		// next note:

			template<typename AST>
			nik_ces void define_next_note_if(AST *t, csize_type ival_pos, csize_type arg_pos)
				{ if (t->interval.not_fixed(ival_pos)) base::define_next_note(t, ival_pos, arg_pos); }

		// next notes:

			template<typename AST>
			nik_ces void define_next_note_ifs(AST *t, csize_type ival_beg, size_type arg_pos)
			{
				for (auto ival_pos = ival_beg; ival_pos != t->interval.size(); ++ival_pos)
					define_next_note_if(t, ival_pos, arg_pos++);
			}
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename SizeType>
	struct T_internal_postcycle : public T_internal<SizeType>
	{
		using base		= T_internal<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		template<typename AST>
		nik_ces void initialize(AST *t) { base::initialize(t, AST::Iterate::postloop); }

		// next note:

			template<typename AST>
			nik_ces void define_next_note_if(AST *t, csize_type ival_pos, csize_type arg_pos)
				{ if (t->interval.is_right_open(ival_pos)) base::define_next_note(t, ival_pos, arg_pos); }

		// prev note:

			template<typename AST>
			nik_ces void define_prev_note_if(AST *t, csize_type ival_pos, csize_type arg_pos)
				{ if (t->interval.is_right_closed(ival_pos)) base::define_prev_note(t, ival_pos, arg_pos); }

		// next notes:

			template<typename AST>
			nik_ces void define_next_note_ifs(AST *t, csize_type ival_beg, size_type arg_pos)
			{
				for (auto ival_pos = ival_beg; ival_pos != t->interval.size(); ++ival_pos)
					define_next_note_if(t, ival_pos, arg_pos++);
			}

		// prev notes:

			template<typename AST>
			nik_ces void define_prev_note_ifs(AST *t, csize_type ival_beg, size_type arg_pos)
			{
				for (auto ival_pos = ival_beg; ival_pos != t->interval.size(); ++ival_pos)
					define_prev_note_if(t, ival_pos, arg_pos++);
			}
	};

/***********************************************************************************************************************/

// routine:

	template<template<typename> typename Chord, typename SizeType>
	struct T_internal_routine
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		using major		= typename Chord<SizeType>::major;
		using tonic		= typename Chord<SizeType>::tonic;
		using tone		= typename Chord<SizeType>::tone;
		using peek		= typename Chord<SizeType>::peek;
		using diminished	= typename Chord<SizeType>::diminished;
		using minor		= typename Chord<SizeType>::minor;

		// major:

			template<typename AST>
			nik_ces void define_major(AST *t)
			{
				major :: precycle  :: define(t);
				major :: cycle     :: define(t);
				major :: postcycle :: define(t);
			}

		// (augmented) tonic:

			template<typename AST>
			nik_ces void define_tonic(AST *t)
			{
				tonic :: precycle  :: define(t);
				tonic :: cycle     :: define(t);
				tonic :: postcycle :: define(t);
			}

		// (augmented) tone:

			template<typename AST>
			nik_ces void define_tone(AST *t)
			{
				tone :: precycle  :: define(t);
				tone :: cycle     :: define(t);
				tone :: postcycle :: define(t);
			}

		// (augmented) peek:

			template<typename AST>
			nik_ces void define_peek(AST *t)
			{
				peek :: precycle  :: define(t);
				peek :: cycle     :: define(t);
				peek :: postcycle :: define(t);
			}

		// augmented:

			template<typename AST>
			nik_ces void define_augmented(AST *t, csize_type root_pos)
			{
				t->interval.resolve_augment(root_pos);

				if      (t->interval.is_tonic ()) define_tonic (t);
				else if (t->interval.is_tone  ()) define_tone  (t);
				else if (t->interval.is_peek  ()) define_peek  (t);
			}

		// diminished:

			template<typename AST>
			nik_ces void define_diminished(AST *t)
			{
				diminished :: precycle  :: define(t);
				diminished :: cycle     :: define(t);
				diminished :: postcycle :: define(t);
			}

		// minor:

			template<typename AST>
			nik_ces void define_minor(AST *t)
			{
				minor :: precycle  :: define(t);
				minor :: cycle     :: define(t);
				minor :: postcycle :: define(t);
			}

		template<typename AST>
		nik_ces void define(AST *t, csize_type root_pos)
		{
			if      (t->interval.is_major      ()) define_major      (t);
			else if (t->interval.is_augmented  ()) define_augmented  (t, root_pos);
			else if (t->interval.is_diminished ()) define_diminished (t);
			else if (t->interval.is_minor      ()) define_minor      (t);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// construct:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_construct_precycle
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		// notes:

			template<typename AST>
			nik_ces void define_notes(AST *t)
			{
				auto ni = t->iterate[AST::Iterate::preloop];

				t->assembly_push_instr(AN::cycle, AT::front, ni);
			}

			template<typename AST>
			nik_ces void define_notes_if(AST *t)
				{ if (t->interval.has_left_next()) define_notes(t); }

		// prepack:

			template<typename AST>
			nik_ces void define_prepack(AST *t)
				{ t->assembly_push_instr(AN::arg, AT::select, t->verse.size()); }
	};

/***********************************************************************************************************************/

// cycle:

	template<typename SizeType>
	struct T_construct_cycle
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		// pred act mut note:

			template<typename AST>
			nik_ces void define_pred_act_mut_note(AST *t, csize_type name)
			{
				auto ni = t->get_predicate ();
				auto mi = t->get_action    ();
				auto li = t->get_mutate    ();
				auto ki = t->iterate[AST::Iterate::loop];

				t->assembly_push_instr(name, AT::id, ni, mi, li, ki);
			}

		// pred act comb mut note:

			template<typename AST>
			nik_ces void define_pred_act_comb_mut_note(AST *t, csize_type name)
			{
				auto ni = t->get_predicate ();
				auto mi = t->get_action    ();
				auto li = t->get_combine   ();
				auto ki = t->get_mutate    ();
				auto ji = t->iterate[AST::Iterate::loop];

				t->assembly_push_instr(name, AT::id, ni, mi, li, ki, ji);
			}

		// pred mat mut cond note:

			template<typename AST>
			nik_ces void define_pred_mat_mut_cond_note(AST *t, csize_type name)
			{
				auto ni = t->get_predicate ();
				auto mi = t->get_action    ();
				auto li = t->get_mutate    ();
				auto ki = t->iterate[AST::Iterate::cond];
				auto ji = t->iterate[AST::Iterate::loop];

				t->assembly_push_instr(name, AT::id, ni, mi, li, ki, ji);
			}
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename SizeType>
	struct T_construct_postcycle
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		// act mut:

			template<typename AST>
			nik_ces void define_act_mut(AST *t, csize_type name)
			{
				auto ni = t->get_action ();
				auto mi = t->get_mutate ();

				t->assembly_push_instr(name, AT::back, ni, mi);
			}

		// act comb mut:

			template<typename AST>
			nik_ces void define_act_comb_mut(AST *t, csize_type name)
			{
				auto ni = t->get_action  ();
				auto mi = t->get_combine ();
				auto li = t->get_mutate  ();

				t->assembly_push_instr(name, AT::back, ni, mi, li);
			}

		// mat mut cond:

			template<typename AST>
			nik_ces void define_mat_mut_cond(AST *t, csize_type name)
			{
				auto ni = t->get_action ();
				auto mi = t->get_mutate ();
				auto li = t->iterate[AST::Iterate::cond];

				t->assembly_push_instr(name, AT::back, ni, mi, li);
			}

		// notes:

			template<typename AST>
			nik_ces void define_notes(AST *t)
			{
				auto ni = t->iterate[AST::Iterate::postloop];

				t->assembly_push_instr(AN::cycle, AT::back, ni);
			}
	};

/***********************************************************************************************************************/

// routine:

	template<template<typename> typename Chord, typename SizeType>
	struct T_construct_routine
	{
		using major		= typename Chord<SizeType>::major;
		using tonic		= typename Chord<SizeType>::tonic;
		using tone		= typename Chord<SizeType>::tone;
		using peek		= typename Chord<SizeType>::peek;
		using diminished	= typename Chord<SizeType>::diminished;
		using minor		= typename Chord<SizeType>::minor;

		// major:

			template<typename AST>
			nik_ces void define_major(AST *t)
			{
				major :: precycle  :: define(t);
				major :: cycle     :: define(t);
				major :: postcycle :: define(t);
			}

		// (augmented) tonic:

			template<typename AST>
			nik_ces void define_tonic(AST *t)
			{
				tonic :: precycle  :: define(t);
				tonic :: cycle     :: define(t);
				tonic :: postcycle :: define(t);
			}

		// (augmented) tone:

			template<typename AST>
			nik_ces void define_tone(AST *t)
			{
				tone :: precycle  :: define(t);
				tone :: cycle     :: define(t);
				tone :: postcycle :: define(t);
			}

		// (augmented) peek:

			template<typename AST>
			nik_ces void define_peek(AST *t)
			{
				peek :: precycle  :: define(t);
				peek :: cycle     :: define(t);
				peek :: postcycle :: define(t);
			}

		// augmented:

			template<typename AST>
			nik_ces void define_augmented(AST *t)
			{
				if      (t->interval.is_tonic ()) define_tonic (t);
				else if (t->interval.is_tone  ()) define_tone  (t);
				else if (t->interval.is_peek  ()) define_peek  (t);
			}

		// diminished:

			template<typename AST>
			nik_ces void define_diminished(AST *t)
			{
				diminished :: precycle  :: define(t);
				diminished :: cycle     :: define(t);
				diminished :: postcycle :: define(t);
			}

		// minor:

			template<typename AST>
			nik_ces void define_minor(AST *t)
			{
				minor :: precycle  :: define(t);
				minor :: cycle     :: define(t);
				minor :: postcycle :: define(t);
			}

		template<typename AST>
		nik_ces void define(AST *t)
		{
			if      (t->interval.is_major      ()) define_major      (t);
			else if (t->interval.is_augmented  ()) define_augmented  (t);
			else if (t->interval.is_diminished ()) define_diminished (t);
			else if (t->interval.is_minor      ()) define_minor      (t);

			t->assembly_push_instr(AN::cycle, AT::drop);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

