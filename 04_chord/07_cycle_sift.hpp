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

// sift:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// resolution:

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// translation:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// major:

/***********************************************************************************************************************/

// precycle:

/***********************************************************************************************************************/

// cycle:

/***********************************************************************************************************************/

// postcycle:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// augmented tonic:

/***********************************************************************************************************************/

// precycle:

/***********************************************************************************************************************/

// cycle:

/***********************************************************************************************************************/

// postcycle:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// augmented tone:

/***********************************************************************************************************************/

// precycle:

/***********************************************************************************************************************/

// cycle:

/***********************************************************************************************************************/

// postcycle:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// augmented peek:

/***********************************************************************************************************************/

// precycle:

/***********************************************************************************************************************/

// cycle:

/***********************************************************************************************************************/

// postcycle:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// diminished:

/***********************************************************************************************************************/

// precycle:

/***********************************************************************************************************************/

// cycle:

/***********************************************************************************************************************/

// postcycle:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// minor:

/***********************************************************************************************************************/

// precycle:

/***********************************************************************************************************************/

// cycle:

/***********************************************************************************************************************/

// postcycle:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// one cycle:

/***********************************************************************************************************************/

// define iter:

	template<typename SizeType>
	struct T_chord_define_iter
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		// init(ialize):

			template<typename AST>
			nik_ces void init(AST *t, csize_type n)
			{
				t->iterate[n] = t->contr.current(1);

				t->assembly_id_begin();
			}

		// term(inalize):

			template<typename AST>
			nik_ces void term(AST *t) { t->assembly_push_instr(AN::halt, AT::none); }

		// note:

			template<typename AST>
			nik_ces void note(AST *t, csize_type ival_pos, csize_type n, csize_type arg_pos)
			{
				auto ni = t->interval.note_contr_pos(ival_pos, n);

				t->note_next_assembly(arg_pos);
				t->assembly_push_instr(AN::next, AT::id, ni);
			}

			template<typename AST>
			nik_ces void note_next(AST *t, csize_type ival_pos, csize_type arg_pos)
				{ note(t, ival_pos, AST::Iter::next, arg_pos); }

			template<typename AST>
			nik_ces void note_prev(AST *t, csize_type ival_pos, csize_type arg_pos)
				{ note(t, ival_pos, AST::Iter::prev, arg_pos); }

		// tonic:

			template<typename AST>
			nik_ces void tonic(AST *t, csize_type ival_pos, csize_type n, csize_type arg_pos)
			{
				auto ni = t->interval.tonic_contr_pos(ival_pos, n);

				t->note_next_assembly(arg_pos);
				t->assembly_push_instr(AN::next, AT::id, ni);
			}

			template<typename AST>
			nik_ces void tonic_next(AST *t, csize_type ival_pos, csize_type arg_pos)
				{ tonic(t, ival_pos, AST::Iter::next, arg_pos); }

			template<typename AST>
			nik_ces void tonic_prev(AST *t, csize_type ival_pos, csize_type arg_pos)
				{ tonic(t, ival_pos, AST::Iter::prev, arg_pos); }
	};

/***********************************************************************************************************************/

// define note:

	template<typename SizeType>
	struct T_chord_define_note
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		using define_iter	= T_chord_define_iter<size_type>;

		// ival:

			template<typename Prog, typename AST>
			nik_ces csize_type ival_out(AST *t) { return Prog::Ival::out; }

			template<typename Prog, typename AST>
			nik_ces csize_type ival_in(AST *t) { return Prog::Ival::in; }

			template<typename Prog, typename AST>
			nik_ces csize_type ival_ins(AST *t) { return Prog::Ival::ins; }

			template<typename Prog, typename AST>
			nik_ces csize_type ival_root(AST *t) { return Prog::Ival::root; }

		// sign:

			template<typename Prog, typename AST>
			nik_ces csize_type sign_out(AST *t) { return Prog::Sign::out; }

			template<typename Prog, typename AST>
			nik_ces csize_type sign_in(AST *t) { return Prog::Sign::in; }

			template<typename Prog, typename AST>
			nik_ces csize_type sign_ins(AST *t) { return Prog::Sign::ins; }

			template<typename Prog, typename AST>
			nik_ces csize_type sign_end(AST *t) { return Prog::Sign::end; }

		// match:

			template<typename Pred, typename Prog, typename AST>
			nik_ces auto match_ins(AST *t)
			{
				bool match = false;

				for (auto ival_pos = ival_ins<Prog>(t); ival_pos != t->interval.size(); ++ival_pos)
					if (Pred::result(t, ival_pos)) { match = true; break; }

				return match;
			}

		// next:

			template<typename Prog, typename AST>
			nik_ces void next_out(AST *t) { define_iter::note_next(t, ival_out<Prog>(t), sign_out<Prog>(t)); }

			template<typename Prog, typename AST>
			nik_ces void next_in(AST *t) { define_iter::note_next(t, ival_in<Prog>(t), sign_in<Prog>(t)); }

			template<typename Prog, typename AST>
			nik_ces void next_end(AST *t) { define_iter::note_next(t, ival_root<Prog>(t), sign_end<Prog>(t)); }

		// prev:

			template<typename Prog, typename AST>
			nik_ces void prev_out(AST *t) { define_iter::note_prev(t, ival_out<Prog>(t), sign_out<Prog>(t)); }

			template<typename Prog, typename AST>
			nik_ces void prev_in(AST *t) { define_iter::note_prev(t, ival_in<Prog>(t), sign_in<Prog>(t)); }

			template<typename Prog, typename AST>
			nik_ces void prev_end(AST *t) { define_iter::tonic_prev(t, ival_root<Prog>(t), sign_end<Prog>(t)); }
	};

/***********************************************************************************************************************/

// define note if:

	template<typename SizeType>
	struct T_chord_define_note_if
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		using define_iter	= T_chord_define_iter<size_type>;
		using define_note	= T_chord_define_note<size_type>;

		// next:

			template<typename Pred, typename Prog, typename AST>
			nik_ces void next_out(AST *t)
			{
				auto ival_pos = define_note::template ival_out<Prog>(t);

				if (Pred::result(t, ival_pos)) define_note::template next_out<Prog>(t);
			}

			template<typename Pred, typename Prog, typename AST>
			nik_ces void next_in(AST *t)
			{
				auto ival_pos = define_note::template ival_in<Prog>(t);

				if (Pred::result(t, ival_pos)) define_note::template next_in<Prog>(t);
			}

			template<typename Pred, typename Prog, typename AST>
			nik_ces void next_end(AST *t) { if (Pred::result(t)) define_note::template next_end<Prog>(t); }

			template<typename Pred, typename Prog, typename AST>
			nik_ces void next_ins(AST *t)
			{
				auto has_next_ins = define_note::template match_ins<Pred, Prog>(t);

				if (has_next_ins)
				{
					auto ival_beg = define_note::template ival_ins<Prog>(t);
					auto sign_pos = define_note::template sign_ins<Prog>(t);

					for (auto ival_pos = ival_beg; ival_pos != t->interval.size(); ++ival_pos)
						if (Pred::result(t, ival_pos))
							define_iter::note_next(t, ival_pos, sign_pos++);
				}
			}

		// prev:

			template<typename Pred, typename Prog, typename AST>
			nik_ces void prev_out(AST *t)
			{
				auto ival_pos = define_note::template ival_out<Prog>(t);

				if (Pred::result(t, ival_pos)) define_note::template prev_out<Prog>(t);
			}

			template<typename Pred, typename Prog, typename AST>
			nik_ces void prev_in(AST *t)
			{
				auto ival_pos = define_note::template ival_in<Prog>(t);

				if (Pred::result(t, ival_pos)) define_note::template prev_in<Prog>(t);
			}

			template<typename Pred, typename Prog, typename AST>
			nik_ces void prev_end(AST *t) { if (Pred::result(t)) define_note::template prev_end<Prog>(t); }

			template<typename Pred, typename Prog, typename AST>
			nik_ces void prev_ins(AST *t)
			{
				auto has_prev_ins = define_note::template match_ins<Pred, Prog>(t);

				if (has_prev_ins)
				{
					auto ival_beg = define_note::template ival_ins<Prog>(t);
					auto sign_pos = define_note::template sign_ins<Prog>(t);

					for (auto ival_pos = ival_beg; ival_pos != t->interval.size(); ++ival_pos)
						if (Pred::result(t, ival_pos))
							define_iter::note_prev(t, ival_pos, sign_pos++);
				}
			}
	};

/***********************************************************************************************************************/

// extend pred if:

	template<typename SizeType>
	struct T_chord_extend_pred_if
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		using define_iter	= T_chord_define_iter<size_type>;
		using define_note	= T_chord_define_note<size_type>;

		// peek:

			template<typename Pred, typename Prog, typename AST>
			nik_ces void peek_in(AST *t)
			{
				// not yet implemented.
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// predicate:

/***********************************************************************************************************************/

// not fixed:

	struct T_chord_predicate_not_fixed
	{
		template<typename AST, typename T>
		nik_ces auto result(AST *t, T ival_pos) { return t->interval.not_fixed(ival_pos); }
	};

/***********************************************************************************************************************/

// is left open:

	struct T_chord_predicate_is_left_open
	{
		template<typename AST, typename T>
		nik_ces auto result(AST *t, T ival_pos) { return t->interval.is_left_open(ival_pos); }
	};

/***********************************************************************************************************************/

// is right open:

	struct T_chord_predicate_is_right_open
	{
		template<typename AST, typename T>
		nik_ces auto result(AST *t, T ival_pos) { return t->interval.is_right_open(ival_pos); }
	};

/***********************************************************************************************************************/

// is right closed:

	struct T_chord_predicate_is_right_closed
	{
		template<typename AST, typename T>
		nik_ces auto result(AST *t, T ival_pos) { return t->interval.is_right_closed(ival_pos); }
	};

/***********************************************************************************************************************/

// is augmented tonic:

	struct T_chord_predicate_is_augmented_tonic
	{
		template<typename AST>
		nik_ces auto result(AST *t) { return t->interval.is_augmented_tonic(); }
	};

/***********************************************************************************************************************/

// is augmented peek:

	struct T_chord_predicate_is_augmented_peek
	{
		template<typename AST>
		nik_ces auto result(AST *t) { return t->interval.is_augmented_peek(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// progression:

/***********************************************************************************************************************/

// repeat:

	template<typename SizeType>
	struct T_chord_repeat
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		using define_iter	= T_chord_define_iter    <size_type>;
		using define_note	= T_chord_define_note    <size_type>;
		using define_note_if	= T_chord_define_note_if <size_type>;

		using left_open		= T_chord_predicate_is_left_open;

		nik_ces size_type name	= AN::repeat;

		struct Ival { enum : size_type { out, root = out, ins, dimension }; };
		struct Sign { enum : size_type { out, end, ins, dimension }; };

		// internal:

			// precycle:

				template<typename AST>
				nik_ces void define_internal_precycle(AST *t)
				{
					// make conditional ?

					define_iter    ::init(t, AST::Iterate::front);
					define_note_if ::template next_out<left_open, T_chord_repeat>(t);
					define_iter    ::term(t);
				};

			// cycle:

				template<typename AST>
				nik_ces void define_internal_cycle(AST *t)
				{
					define_iter ::init(t, AST::Iterate::loop);
					define_note ::template next_out<T_chord_repeat>(t);
					define_iter ::term(t);
				};

			// postcycle:

				// not required.

			// action:

				template<typename AST>
				nik_ces void define_internal_action(AST *t)
				{
				//	define_internal_precycle (t);
					define_internal_cycle    (t);
				};

		// loop action:

			template<typename AST>
			nik_ces void define_loop_action(AST *t)
			{
				auto ni = t->get_predicate ();
				auto mi = t->get_action    ();
				auto li = t->get_mutate    ();
				auto ki = t->iterate[AST::Iterate::loop];

				t->assembly_push_instr(name, AT::id, ni, mi, li, ki);
			}

		// back action:

			template<typename AST>
			nik_ces void define_back_action(AST *t)
			{
				auto ni = t->get_action();
				auto mi = t->get_mutate();

				t->assembly_push_instr(name, AT::back, ni, mi);
			}
	};

/***********************************************************************************************************************/

// map:

	template<typename SizeType>
	struct T_chord_map
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		using define_iter	= T_chord_define_iter    <size_type>;
		using define_note	= T_chord_define_note    <size_type>;
		using define_note_if	= T_chord_define_note_if <size_type>;
		using extend_pred_if	= T_chord_extend_pred_if <size_type>;

		using not_fixed		= T_chord_predicate_not_fixed;
		using left_open		= T_chord_predicate_is_left_open;
		using right_open	= T_chord_predicate_is_right_open;
		using right_closed	= T_chord_predicate_is_right_closed;
		using aug_tonic		= T_chord_predicate_is_augmented_tonic;
		using aug_peek		= T_chord_predicate_is_augmented_peek;

		nik_ces size_type name	= AN::map;

		struct Ival { enum : size_type { out, in, root = in, ins, dimension }; };
		struct Sign { enum : size_type { out, in, end, ins, dimension }; };

		// internal:

			// precycle:

				template<typename AST>
				nik_ces void define_internal_precycle(AST *t)
				{
					define_iter    ::init(t, AST::Iterate::front);
					define_note_if ::template next_out < left_open , T_chord_map >(t);
					define_note_if ::template next_in  < left_open , T_chord_map >(t);
					define_note_if ::template next_ins < left_open , T_chord_map >(t);
					define_note_if ::template prev_end < aug_tonic , T_chord_map >(t);
					define_iter    ::term(t);
				};

			// cycle:

				template<typename AST>
				nik_ces void define_internal_cycle(AST *t)
				{
					define_iter    ::init(t, AST::Iterate::loop);
					define_note    ::template next_out<T_chord_map>(t);
					define_note    ::template next_in<T_chord_map>(t);
					define_note_if ::template next_ins<not_fixed, T_chord_map>(t);
					define_iter    ::term(t);

					extend_pred_if ::template peek_in<aug_peek, T_chord_map>(t);
				};

			// postcycle:

				// augmented:

					template<typename AST>
					nik_ces void define_internal_augmented_tone(AST *t)
						{ define_note_if::template prev_ins<right_closed, T_chord_map>(t); };

					template<typename AST>
					nik_ces void define_internal_augmented_not_tone(AST *t)
					{
						define_note_if ::template next_out<right_open, T_chord_map>(t);
						define_note    ::template next_in<T_chord_map>(t);
						define_note_if ::template next_ins<right_open, T_chord_map>(t);
						define_note_if ::template next_end<aug_tonic, T_chord_map>(t);
					};

					template<typename AST>
					nik_ces void define_internal_augmented(AST *t)
					{
						define_iter::init(t, AST::Iterate::back);

						if (t->interval.is_tone()) define_internal_augmented_tone     (t);
						else                       define_internal_augmented_not_tone (t);

						define_iter::term(t);
					};

				// minor:

					template<typename AST>
					nik_ces void define_internal_minor(AST *t)
					{
						define_iter    ::init(t, AST::Iterate::back);
						define_note_if ::template next_out<right_open, T_chord_map>(t);
						define_note_if ::template next_ins<right_open, T_chord_map>(t);
						define_iter    ::term(t);
					};

				template<typename AST>
				nik_ces void define_internal_postcycle(AST *t)
				{
					if      (t->interval.is_augmented ()) define_internal_augmented (t);
					else if (t->interval.is_minor     ()) define_internal_minor     (t);
				};

			// action:

				template<typename AST>
				nik_ces void define_internal_action(AST *t)
				{
					define_internal_precycle  (t);
					define_internal_cycle     (t);
					define_internal_postcycle (t);
				};

		// loop action:

			template<typename AST>
			nik_ces void define_loop_action(AST *t)
			{
				auto ni = t->get_predicate ();
				auto mi = t->get_action    ();
				auto li = t->get_mutate    ();
				auto ki = t->iterate[AST::Iterate::loop];

				t->assembly_push_instr(name, AT::id, ni, mi, li, ki);
			}

		// back action:

			template<typename AST>
			nik_ces void define_back_action(AST *t)
			{
				auto ni = t->get_action();
				auto mi = t->get_mutate();

				t->assembly_push_instr(name, AT::back, ni, mi);
			}
	};

/***********************************************************************************************************************/

// fold:

	template<typename SizeType>
	struct T_chord_fold
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		using define_iter	= T_chord_define_iter    <size_type>;
		using define_note	= T_chord_define_note    <size_type>;
		using define_note_if	= T_chord_define_note_if <size_type>;
		using extend_pred_if	= T_chord_extend_pred_if <size_type>;

		using not_fixed		= T_chord_predicate_not_fixed;
		using left_open		= T_chord_predicate_is_left_open;
		using right_open	= T_chord_predicate_is_right_open;
		using right_closed	= T_chord_predicate_is_right_closed;
		using aug_tonic		= T_chord_predicate_is_augmented_tonic;
		using aug_peek		= T_chord_predicate_is_augmented_peek;

		nik_ces size_type name	= AN::fold;

		struct Ival { enum : size_type { out, in, root = in, ins, dimension }; };
		struct Sign { enum : size_type { out, in, end, ins, dimension }; };

		// internal:

			// precycle:

				template<typename AST>
				nik_ces void define_internal_precycle(AST *t)
				{
					define_iter    ::init(t, AST::Iterate::front);
					define_note_if ::template next_in  < left_open , T_chord_fold >(t);
					define_note_if ::template next_ins < left_open , T_chord_fold >(t);
					define_note_if ::template prev_end < aug_tonic , T_chord_fold >(t);
					define_iter    ::term(t);
				};

			// cycle:

				template<typename AST>
				nik_ces void define_internal_cycle(AST *t)
				{
					define_iter    ::init(t, AST::Iterate::loop);
					define_note    ::template next_in<T_chord_fold>(t);
					define_note_if ::template next_ins<not_fixed, T_chord_fold>(t);
					define_iter    ::term(t);

					extend_pred_if ::template peek_in<aug_peek, T_chord_fold>(t);
				};

			// postcycle:

				// augmented:

					template<typename AST>
					nik_ces void define_internal_augmented_tone(AST *t)
						{ define_note_if::template prev_ins<right_closed, T_chord_fold>(t); };

					template<typename AST>
					nik_ces void define_internal_augmented_not_tone(AST *t)
					{
						define_note    ::template next_in<T_chord_fold>(t);
						define_note_if ::template next_ins<right_open, T_chord_fold>(t);
						define_note_if ::template next_end<aug_tonic, T_chord_fold>(t);
					};

					template<typename AST>
					nik_ces void define_internal_augmented(AST *t)
					{
						define_iter::init(t, AST::Iterate::back);

						if (t->interval.is_tone()) define_internal_augmented_tone     (t);
						else                       define_internal_augmented_not_tone (t);

						define_iter::term(t);
					};

				// minor:

					template<typename AST>
					nik_ces void define_internal_minor(AST *t)
					{
						define_iter    ::init(t, AST::Iterate::back);
						define_note_if ::template next_ins<right_open, T_chord_fold>(t);
						define_iter    ::term(t);
					};

				template<typename AST>
				nik_ces void define_internal_postcycle(AST *t)
				{
					if      (t->interval.is_augmented ()) define_internal_augmented (t);
					else if (t->interval.is_minor     ()) define_internal_minor     (t);
				};

			// action:

				template<typename AST>
				nik_ces void define_internal_action(AST *t)
				{
					define_internal_precycle  (t);
					define_internal_cycle     (t);
					define_internal_postcycle (t);
				};

		// loop action:

			template<typename AST>
			nik_ces void define_loop_action(AST *t)
			{
				auto ni = t->get_predicate ();
				auto mi = t->get_action    ();
				auto li = t->get_combine   ();
				auto ki = t->get_mutate    ();
				auto ji = t->iterate[AST::Iterate::loop];

				t->assembly_push_instr(name, AT::id, ni, mi, li, ki, ji);
			}

		// back action:

			template<typename AST>
			nik_ces void define_back_action(AST *t)
			{
				auto ni = t->get_action  ();
				auto mi = t->get_combine ();
				auto li = t->get_mutate  ();

				t->assembly_push_instr(name, AT::back, ni, mi, li);
			}
	};

/***********************************************************************************************************************/

// find:

	template<typename SizeType>
	struct T_chord_find
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		using define_iter	= T_chord_define_iter    <size_type>;
		using define_note	= T_chord_define_note    <size_type>;
		using define_note_if	= T_chord_define_note_if <size_type>;
		using extend_pred_if	= T_chord_extend_pred_if <size_type>;

		using not_fixed		= T_chord_predicate_not_fixed;
		using left_open		= T_chord_predicate_is_left_open;
		using right_open	= T_chord_predicate_is_right_open;
		using right_closed	= T_chord_predicate_is_right_closed;
		using aug_tonic		= T_chord_predicate_is_augmented_tonic;
		using aug_peek		= T_chord_predicate_is_augmented_peek;

		nik_ces size_type name	= AN::find;

		struct Ival { enum : size_type { out, in, root = in, ins, dimension }; };
		struct Sign { enum : size_type { out, in, end, ins, dimension }; };

		// internal:

			// precycle:

				template<typename AST>
				nik_ces void define_internal_precycle(AST *t)
				{
					define_iter    ::init(t, AST::Iterate::front);
					define_note_if ::template next_in  < left_open , T_chord_find >(t);
					define_note_if ::template next_ins < left_open , T_chord_find >(t);
					define_note_if ::template prev_end < aug_tonic , T_chord_find >(t);
					define_iter    ::term(t);
				};

			// cycle:

				template<typename AST>
				nik_ces void define_internal_cycle(AST *t)
				{
					define_iter    ::init(t, AST::Iterate::loop);
					define_note    ::template next_in<T_chord_find>(t);
					define_note_if ::template next_ins<not_fixed, T_chord_find>(t);
					define_iter    ::term(t);

					extend_pred_if ::template peek_in<aug_peek, T_chord_find>(t);
				};

			// postcycle:

				// augmented:

					template<typename AST>
					nik_ces void define_internal_augmented_tone(AST *t)
						{ define_note_if::template prev_ins<right_closed, T_chord_find>(t); };

					template<typename AST>
					nik_ces void define_internal_augmented_not_tone(AST *t)
					{
						define_note    ::template next_in<T_chord_find>(t);
						define_note_if ::template next_ins<right_open, T_chord_find>(t);
						define_note_if ::template next_end<aug_tonic, T_chord_find>(t);
					};

					template<typename AST>
					nik_ces void define_internal_augmented(AST *t)
					{
						define_iter::init(t, AST::Iterate::back);

						if (t->interval.is_tone()) define_internal_augmented_tone     (t);
						else                       define_internal_augmented_not_tone (t);

						define_iter::term(t);
					};

				// minor:

					template<typename AST>
					nik_ces void define_internal_minor(AST *t)
					{
						define_iter    ::init(t, AST::Iterate::back);
						define_note_if ::template next_ins<right_open, T_chord_find>(t);
						define_iter    ::term(t);
					};

				template<typename AST>
				nik_ces void define_internal_postcycle(AST *t)
				{
					if      (t->interval.is_augmented ()) define_internal_augmented (t);
					else if (t->interval.is_minor     ()) define_internal_minor     (t);
				};

			// action:

				template<typename AST>
				nik_ces void define_internal_action(AST *t)
				{
					define_internal_precycle  (t);
					define_internal_cycle     (t);
					define_internal_postcycle (t);
				};

		// loop action:

			template<typename AST>
			nik_ces void define_loop_action(AST *t)
			{
				auto ni = t->get_predicate ();
				auto mi = t->get_action    ();
				auto li = t->get_mutate    ();
				auto ki = t->iterate[AST::Iterate::loop]; // debugging, tone next (out).
				auto ji = t->iterate[AST::Iterate::loop];

				t->assembly_push_instr(name, AT::id, ni, mi, li, ki, ji);
			}

		// back action:

			template<typename AST>
			nik_ces void define_back_action(AST *t)
			{
				auto ni = t->get_action();
				auto mi = t->get_mutate();
				auto li = t->iterate[AST::Iterate::loop]; // debugging, tone next (out).

				t->assembly_push_instr(name, AT::back, ni, mi, li);
			}
	};

/***********************************************************************************************************************/

// sift:

	template<typename SizeType>
	struct T_chord_sift
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		using define_iter	= T_chord_define_iter    <size_type>;
		using define_note	= T_chord_define_note    <size_type>;
		using define_note_if	= T_chord_define_note_if <size_type>;
		using extend_pred_if	= T_chord_extend_pred_if <size_type>;

		using not_fixed		= T_chord_predicate_not_fixed;
		using left_open		= T_chord_predicate_is_left_open;
		using right_open	= T_chord_predicate_is_right_open;
		using right_closed	= T_chord_predicate_is_right_closed;
		using aug_tonic		= T_chord_predicate_is_augmented_tonic;
		using aug_peek		= T_chord_predicate_is_augmented_peek;

		nik_ces size_type name	= AN::sift;

		struct Ival { enum : size_type { out, in, root = in, ins, dimension }; };
		struct Sign { enum : size_type { out, in, end, ins, dimension }; };

		// internal:

			// precycle:

				template<typename AST>
				nik_ces void define_internal_precycle(AST *t)
				{
					define_iter    ::init(t, AST::Iterate::front);
					define_note_if ::template next_in  < left_open , T_chord_sift >(t);
					define_note_if ::template next_ins < left_open , T_chord_sift >(t);
					define_note_if ::template prev_end < aug_tonic , T_chord_sift >(t);
					define_iter    ::term(t);
				};

			// cycle:

				template<typename AST>
				nik_ces void define_internal_cycle(AST *t)
				{
					define_iter    ::init(t, AST::Iterate::loop);
					define_note    ::template next_in<T_chord_sift>(t);
					define_note_if ::template next_ins<not_fixed, T_chord_sift>(t);
					define_iter    ::term(t);

					extend_pred_if ::template peek_in<aug_peek, T_chord_sift>(t);
				};

			// postcycle:

				// augmented:

					template<typename AST>
					nik_ces void define_internal_augmented_tone(AST *t)
						{ define_note_if::template prev_ins<right_closed, T_chord_sift>(t); };

					template<typename AST>
					nik_ces void define_internal_augmented_not_tone(AST *t)
					{
						define_note    ::template next_in<T_chord_sift>(t);
						define_note_if ::template next_ins<right_open, T_chord_sift>(t);
						define_note_if ::template next_end<aug_tonic, T_chord_sift>(t);
					};

					template<typename AST>
					nik_ces void define_internal_augmented(AST *t)
					{
						define_iter::init(t, AST::Iterate::back);

						if (t->interval.is_tone()) define_internal_augmented_tone     (t);
						else                       define_internal_augmented_not_tone (t);

						define_iter::term(t);
					};

				// minor:

					template<typename AST>
					nik_ces void define_internal_minor(AST *t)
					{
						define_iter    ::init(t, AST::Iterate::back);
						define_note_if ::template next_ins<right_open, T_chord_sift>(t);
						define_iter    ::term(t);
					};

				template<typename AST>
				nik_ces void define_internal_postcycle(AST *t)
				{
					if      (t->interval.is_augmented ()) define_internal_augmented (t);
					else if (t->interval.is_minor     ()) define_internal_minor     (t);
				};

			// action:

				template<typename AST>
				nik_ces void define_internal_action(AST *t)
				{
					define_internal_precycle  (t);
					define_internal_cycle     (t);
					define_internal_postcycle (t);
				};

		// loop action:

			template<typename AST>
			nik_ces void define_loop_action(AST *t)
			{
				auto ni = t->get_predicate ();
				auto mi = t->get_action    ();
				auto li = t->get_mutate    ();
				auto ki = t->iterate[AST::Iterate::loop]; // debugging, tone next (out).
				auto ji = t->iterate[AST::Iterate::loop];

				t->assembly_push_instr(name, AT::id, ni, mi, li, ki, ji);
			}

		// back action:

			template<typename AST>
			nik_ces void define_back_action(AST *t)
			{
				auto ni = t->get_action();
				auto mi = t->get_mutate();
				auto li = t->iterate[AST::Iterate::loop]; // debugging, tone next (out).

				t->assembly_push_instr(name, AT::back, ni, mi, li);
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

