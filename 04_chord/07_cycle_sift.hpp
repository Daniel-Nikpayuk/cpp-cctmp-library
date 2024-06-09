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

