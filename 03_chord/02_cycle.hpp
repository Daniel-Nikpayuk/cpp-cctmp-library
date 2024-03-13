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
/***********************************************************************************************************************/

// interval:

/***********************************************************************************************************************/

// interface:

	template<typename SizeType>
	struct T_chord_interval
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;
		using iter_type		= T_chord_iterator<size_type>;
		using Iter		= typename iter_type::Iter;

		struct Ival		{ enum : size_type { tone, root, dimension }; };
		struct Point		{ enum : size_type { fixed, closed, open, dimension }; };
		struct Chord		{ enum : size_type { major, augmented, diminished, minor, dimension }; };

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
			nik_ce auto is_left_open    () const { return (left == Point::open); }

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
	};

/***********************************************************************************************************************/

// intervals:

	// major: all right open, tones align centre (with tonic).
	// augmented: root right open, at least one tone right closed. right closed tones align left (of tonic).
			// there are 3 algorithm dispatch cases:
				// 1) tonic: tonic is reversible.
					// a) move tonic prev.
					// b) march (move) root and tones.
					// c) update (move) root and tones.
					// d) update tonic next.
				// 2) tone: tonic is not reversible, but all left tones are reversible.
					// a) march root and tones.
					// b) backdate (move) said tones.
				// 3) peek: tonic is not reversible, and at least one left tone is not reversible.
					// a) peekmarch (move) root and tones.
					// b) update root and tones.

	// diminished: all right closed, tones align centre (with tonic).
	// minor: root right closed, at least one tone right open. right open tones align right (of tonic).

	template<typename SizeType, SizeType Size>
	struct T_chord_intervals : public sequence<T_chord_interval<SizeType>, Size>
	{
		using base		= sequence<T_chord_interval<SizeType>, Size>;
		using interval_type	= typename base::type;
		using size_type		= typename interval_type::size_type;
		using csize_type	= typename interval_type::csize_type;
		using Iter		= typename interval_type::Iter;

		struct Chord		{ enum : size_type { none, major, augmented, diminished, minor, dimension }; };

		size_type init;
		size_type chord;
		bool before;
		bool action;
		bool after;
		bool tones;

		nik_ce T_chord_intervals() :
			init{Chord::none}, chord{Chord::none}, before{}, action{}, after{}, tones{}
				{ }

		// init:

			nik_ce void set_init(csize_type n) { init = n; }

		// chord:

			nik_ce auto is_major      () const { return (chord == Chord::major); }
			nik_ce auto is_augmented  () const { return (chord == Chord::augmented); }
			nik_ce auto is_diminished () const { return (chord == Chord::diminished); }
			nik_ce auto is_minor      () const { return (chord == Chord::minor); }

			nik_ce auto is_tonic(csize_type root) const
				{ return (base::operator[](root).tonic_iter.size() == 2); }

			nik_ce auto is_tone() const { return tones; }

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

			nik_ce void resolve_chord() { update_chord(init); }

		// tones:

			nik_ce void update_tones(const bool b) { tones = tones && b; }

		// ival:

			nik_ce auto has_left_next() const { return before; }
			nik_ce auto has_right_action() const { return (is_diminished() || is_minor()); }
			nik_ce auto has_right_next() const { return is_minor(); }

			nik_ce void set_fixed()
			{
				base::last()->set_left_fixed();
				base::last()->set_right_fixed();
			}

			nik_ce void set_left_closed () { base::last()->set_left_closed(); }
			nik_ce void set_left_open   () { base::last()->set_left_open(); before = true; }

			nik_ce void set_init_closed()
			{
				base::last()->set_right_closed();
				set_init(Chord::diminished);
			}

			nik_ce void set_init_open()
			{
				base::last()->set_right_open();
				set_init(Chord::major);
				update_tones(base::last()->note_iter.size() == 2);
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
				update_tones(base::last()->note_iter.size() == 2);
			}

		// note:

			nik_ce auto not_fixed(csize_type n) const
				{ return base::operator[](n).not_fixed(); }

			nik_ce auto is_left_open(csize_type n) const
				{ return base::operator[](n).is_left_open(); }

			nik_ce auto is_right_open(csize_type n) const
				{ return base::operator[](n).is_right_open(); }

			nik_ce auto note_iter(csize_type n, csize_type m) const
				{ return base::operator[](n).note_iter[m]; }

			nik_ce auto note_iter(csize_type m) const
				{ return note_iter(base::max(), m); }

			nik_ce auto note_pos(csize_type n, csize_type m) const
				{ return note_iter(n, m).get_pos(); }

			nik_ce auto note_pos(csize_type m) const
				{ return note_iter(m).get_pos(); }

			nik_ce void push_note(csize_type p, const bool s = false)
				{ base::last()->push_note(p, s); }

		// tonic:

			nik_ce void push_tonic()
			{
				const auto & next = base::last()->note_iter[Iter::next];
				const auto & prev = base::last()->note_iter[Iter::prev];

				base::last()->push_tonic(next.get_pos(), next.get_side());
				base::last()->push_tonic(prev.get_pos(), prev.get_side());
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cycle:

/***********************************************************************************************************************/

// repeat:

	template<typename SizeType>
	struct T_chord_repeat
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		struct Ival		{ enum : size_type { out, ins, dimension }; };
		struct Sign		{ enum : size_type { out, end, ins, dimension }; };

		template<typename AST>
		nik_ces void define_cycle_before(AST *t)
		{
		}

		template<typename AST>
		nik_ces void define_cycle_loop(AST *t)
		{
		}

		template<typename AST>
		nik_ces void define_cycle_after(AST *t)
		{
		}

		template<typename AST>
		nik_ces void define_cycle(AST *t)
		{
			define_cycle_before (t);
			define_cycle_loop   (t);
			define_cycle_after  (t);

			t->define_cycle();
		}
	};

/***********************************************************************************************************************/

// map:

	template<typename SizeType>
	struct T_chord_map
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		struct Ival		{ enum : size_type { out, in, ins, dimension }; };
		struct Sign		{ enum : size_type { out, in, end, ins, dimension }; };

		template<typename AST>
		nik_ces void define_cycle_before(AST *t)
		{
		}

		template<typename AST>
		nik_ces void define_cycle_loop(AST *t)
		{
		}

		template<typename AST>
		nik_ces void define_cycle_after(AST *t)
		{
		}

		template<typename AST>
		nik_ces void define_cycle(AST *t)
		{
			define_cycle_before (t);
			define_cycle_loop   (t);
			define_cycle_after  (t);

			t->define_cycle();
		}
	};

/***********************************************************************************************************************/

// fold:

	template<typename SizeType>
	struct T_chord_fold
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		struct Ival		{ enum : size_type { out, in, ins, dimension }; };
		struct Sign		{ enum : size_type { out, in, end, ins, dimension }; };

		template<typename AST>
		nik_ces void define_pred(AST *t)
		{
			auto ni = t->get_predicate();

			t->cycle_id[AST::CycleId::predicate] = t->contr.current(1);
			t->template assembly_action<AAN::id, AAT::begin>();
			t->template assembly_action<AAN::push, AAT::instr>(AN::fold, AT::pred, ni);
		}

		template<typename AST>
		nik_ces void define_action(AST *t)
		{
			auto ni = t->get_action();
			auto mi = t->get_combine();
			auto li = t->get_mutate();

			t->cycle_side[AST::CycleSide::action] = t->contr.current(1);
			t->template assembly_action<AAN::id, AAT::begin>();
			t->template assembly_action<AAN::push, AAT::instr>(AN::fold, AT::act, ni, mi, 2);
			t->template assembly_action<AAN::push, AAT::instr>(li, 0);
		}

		template<typename AST>
		nik_ces void define_next(AST *t)
		{
			auto out_pos = t->verse.size();
			auto  in_pos = out_pos + Sign::in;
			auto ins_pos = out_pos + Sign::ins;

			t->define_next_begin (in_pos);
			t->define_next_cont  (Ival::in, ins_pos);
			t->define_next_rest  (Ival::ins, ins_pos);
			t->define_next_end   ();
		}

		// before:

			template<typename AST>
			nik_ces void define_cycle_before(AST *t)
				{ if (t->interval.has_left_next()) dispatch_cycle_before(t); }

			template<typename AST>
			nik_ces void dispatch_cycle_before(AST *t)
			{
				if (t->interval.is_left_open(Ival::in)) define_cycle_before_in  (t);
				else                                    define_cycle_before_ins (t);
			}

			template<typename AST>
			nik_ces void define_cycle_before_in(AST *t)
			{
				auto out_pos = t->verse.size();
				auto  in_pos = out_pos + Sign::in;
				auto ins_pos = out_pos + Sign::ins;

				t->define_before_begin (in_pos);
				t->define_before_cont  (Ival::in, ins_pos);
				t->define_before_rest  (Ival::ins, ins_pos);
				t->define_before_end   ();
			}

			template<typename AST>
			nik_ces void define_cycle_before_ins(AST *t)
			{
				auto out_pos  = t->verse.size();
				auto ins_pos  = out_pos + Sign::ins;
				auto ival_pos = find_cycle_before(t);
				auto sign_pos = out_pos + ival_pos + 1;

				t->define_before_begin (sign_pos);
				t->define_before_rest  (ival_pos, ins_pos);
				t->define_before_end   ();
			}

			template<typename AST>
			nik_ces auto find_cycle_before(AST *t)
			{
				size_type k = Ival::ins;

				while (k != t->interval.size())
					if (t->interval.is_left_open(k)) break;
					else ++k;

				return k;
			}

		// loop:

			template<typename AST>
			nik_ces void define_cycle_loop(AST *t)
			{
				define_pred   (t);
				define_action (t);
				define_next   (t);
			}

		// after:

			template<typename AST>
			nik_ces void define_cycle_after(AST *t)
			{
				if      (t->interval.is_augmented())  define_cycle_after_augmented  (t);
				else if (t->interval.is_diminished()) define_cycle_after_diminished (t);
				else                                  define_cycle_after_minor      (t);
			}

			template<typename AST>
			nik_ces void define_cycle_after_augmented(AST *t)
			{
				if      (t->interval.is_tonic(Ival::in)) define_cycle_after_tonic (t);
				else if (t->interval.is_tone())          define_cycle_after_tone  (t);
				else                                     define_cycle_after_peek  (t);
			}

			template<typename AST>
			nik_ces void define_cycle_after_tonic(AST *t)
			{
			}

			template<typename AST>
			nik_ces void define_cycle_after_tone(AST *t)
			{
			}

			template<typename AST>
			nik_ces void define_cycle_after_peek(AST *t)
			{
			}

			template<typename AST>
			nik_ces void define_cycle_after_diminished(AST *t)
			{
				t->cycle_back[AST::CycleBack::action] = t->cycle_side[AST::CycleSide::action];
			}

			template<typename AST>
			nik_ces void define_cycle_after_minor(AST *t)
			{
			}

		// cycle:

			template<typename AST>
			nik_ces void define_cycle(AST *t)
			{
				define_cycle_before (t);
				define_cycle_loop   (t);
				define_cycle_after  (t);

				t->define_cycle();
			}
	};

/***********************************************************************************************************************/

// find:

	template<typename SizeType>
	struct T_chord_find
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		struct Ival		{ enum : size_type { out, in, ins, dimension }; };
		struct Sign		{ enum : size_type { out, in, end, ins, dimension }; };

		template<typename AST>
		nik_ces void define_cycle_before(AST *t)
		{
		}

		template<typename AST>
		nik_ces void define_cycle_loop(AST *t)
		{
		}

		template<typename AST>
		nik_ces void define_cycle_after(AST *t)
		{
		}

		template<typename AST>
		nik_ces void define_cycle(AST *t)
		{
			define_cycle_before (t);
			define_cycle_loop   (t);
			define_cycle_after  (t);

			t->define_cycle();
		}
	};

/***********************************************************************************************************************/

// sift:

	template<typename SizeType>
	struct T_chord_sift
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		struct Ival		{ enum : size_type { out, in, ins, dimension }; };
		struct Sign		{ enum : size_type { out, in, end, ins, dimension }; };

		template<typename AST>
		nik_ces void define_cycle_before(AST *t)
		{
		}

		template<typename AST>
		nik_ces void define_cycle_loop(AST *t)
		{
		}

		template<typename AST>
		nik_ces void define_cycle_after(AST *t)
		{
		}

		template<typename AST>
		nik_ces void define_cycle(AST *t)
		{
			define_cycle_before (t);
			define_cycle_loop   (t);
			define_cycle_after  (t);

			t->define_cycle();
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

