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

// cycle find:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// spec:

/***********************************************************************************************************************/

// interface:

	template<typename SizeType>
	struct T_find_signature
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		enum : size_type { out, in, end, ins, dimension };
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// internal (construct):

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_find_internal_precycle : public T_internal_precycle<SizeType>
	{
		using base		= T_internal_precycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Sign		= T_find_signature<size_type>;

		template<typename AST>
		nik_ces void define(AST *t)
		{
			base::initialize_if             (t);
			base::define_next_note_if       (t , AST::Ival::in  , Sign::in  );
			base::define_next_note_ifs_fast (t , AST::Ival::ins , Sign::ins );
			base::terminalize_if            (t);
		}
	};

/***********************************************************************************************************************/

// cycle:

	template<typename SizeType>
	struct T_find_internal_cycle : public T_internal_cycle<SizeType>
	{
		using base		= T_internal_cycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Sign		= T_find_signature<size_type>;

		template<typename AST>
		nik_ces void define(AST *t)
		{
			base::initialize_cond      (t);
			base::define_next_note     (t , AST::Ival::out , Sign::out );
			base::terminalize          (t);

			base::initialize           (t);
			base::define_next_note     (t , AST::Ival::in  , Sign::in  );
			base::define_next_note_ifs (t , AST::Ival::ins , Sign::ins );
			base::terminalize          (t);
		}
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename SizeType>
	struct T_find_internal_postcycle
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		template<typename AST>
		nik_ces void define(AST *t) { } // do nothing.
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// major:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_find_internal_major_precycle : public T_find_internal_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_find_internal_major_cycle : public T_find_internal_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_find_internal_major_postcycle : public T_find_internal_postcycle<SizeType> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (augmented) tonic:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_find_internal_tonic_precycle : public T_internal_precycle<SizeType>
	{
		using base		= T_internal_precycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Sign		= T_find_signature<size_type>;

		template<typename AST>
		nik_ces void define(AST *t)
		{
			base::initialize           (t);
			base::define_next_note_if  (t , AST::Ival::in  , Sign::in  );
			base::define_next_note_ifs (t , AST::Ival::ins , Sign::ins );
			base::define_prev_tonic    (t , AST::Ival::in  , Sign::end );
			base::terminalize          (t);
		}
	};

// cycle:

	template<typename SizeType>
	struct T_find_internal_tonic_cycle : public T_find_internal_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_find_internal_tonic_postcycle : public T_internal_postcycle<SizeType>
	{
		using base		= T_internal_postcycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Sign		= T_find_signature<size_type>;

		template<typename AST>
		nik_ces void define(AST *t)
		{
			base::initialize           (t);
			base::define_next_note     (t , AST::Ival::in  , Sign::in  );
			base::define_next_note_ifs (t , AST::Ival::ins , Sign::ins );
			base::define_next_tonic    (t , AST::Ival::in  , Sign::end );
			base::terminalize          (t);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (augmented) tone:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_find_internal_tone_precycle : public T_find_internal_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_find_internal_tone_cycle : public T_find_internal_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_find_internal_tone_postcycle : public T_internal_postcycle<SizeType>
	{
		using base		= T_internal_postcycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Sign		= T_find_signature<size_type>;

		template<typename AST>
		nik_ces void define(AST *t)
		{
			base::initialize           (t);
			base::define_prev_note_ifs (t , AST::Ival::ins , Sign::ins );
			base::terminalize          (t);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (augmented) peek:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_find_internal_peek_precycle : public T_find_internal_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_find_internal_peek_cycle : public T_find_internal_cycle<SizeType>
	{
		using base		= T_find_internal_cycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Sign		= T_find_signature<size_type>;

		template<typename AST>
		nik_ces void define(AST *t) // fix after dsl engine overhaul!
		{
		//	base::define(t);

		//	auto pred_ni = t->get_predicate();
		//	auto next_ni = t->interval.note_contr_pos(AST::Ival::in, AST::Iter::next);

		//	nik_ce auto arity = 2;

		//	t->set_predicate();
		//	t->act_subpose_begin(arity);

		//	t->set_routine();
		//	t->apply_pound_begin(pred_ni);
		//	t->lookup_return(s); // would need to be streamlined.

		//	t->subpose_value(t->cselect_id());
		//	t->subpose_value(t->cselect_id());
		//	t->act_subpose_end();
		}
	};

// postcycle:

	template<typename SizeType>
	struct T_find_internal_peek_postcycle : public T_internal_postcycle<SizeType>
	{
		using base		= T_internal_postcycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Sign		= T_find_signature<size_type>;

		template<typename AST>
		nik_ces void define(AST *t)
		{
			base::initialize           (t);
			base::define_next_note     (t , AST::Ival::in  , Sign::in  );
			base::define_next_note_ifs (t , AST::Ival::ins , Sign::ins );
			base::terminalize          (t);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// diminished:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_find_internal_diminished_precycle : public T_find_internal_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_find_internal_diminished_cycle : public T_find_internal_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_find_internal_diminished_postcycle : public T_find_internal_postcycle<SizeType> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// minor:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_find_internal_minor_precycle : public T_find_internal_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_find_internal_minor_cycle : public T_find_internal_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_find_internal_minor_postcycle : public T_internal_postcycle<SizeType>
	{
		using base		= T_internal_postcycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Sign		= T_find_signature<size_type>;

		template<typename AST>
		nik_ces void define(AST *t)
		{
			base::initialize           (t);
			base::define_next_note_ifs (t , AST::Ival::ins , Sign::ins );
			base::terminalize          (t);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// routine:

/***********************************************************************************************************************/

// major:

	template<typename SizeType>
	struct T_find_internal_routine_major
	{
		using precycle		= T_find_internal_major_precycle  <SizeType>;
		using cycle		= T_find_internal_major_cycle     <SizeType>;
		using postcycle		= T_find_internal_major_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// tonic:

	template<typename SizeType>
	struct T_find_internal_routine_tonic
	{
		using precycle		= T_find_internal_tonic_precycle  <SizeType>;
		using cycle		= T_find_internal_tonic_cycle     <SizeType>;
		using postcycle		= T_find_internal_tonic_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// tone:

	template<typename SizeType>
	struct T_find_internal_routine_tone
	{
		using precycle		= T_find_internal_tone_precycle  <SizeType>;
		using cycle		= T_find_internal_tone_cycle     <SizeType>;
		using postcycle		= T_find_internal_tone_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// peek:

	template<typename SizeType>
	struct T_find_internal_routine_peek
	{
		using precycle		= T_find_internal_peek_precycle  <SizeType>;
		using cycle		= T_find_internal_peek_cycle     <SizeType>;
		using postcycle		= T_find_internal_peek_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// diminished:

	template<typename SizeType>
	struct T_find_internal_routine_diminished
	{
		using precycle		= T_find_internal_diminished_precycle  <SizeType>;
		using cycle		= T_find_internal_diminished_cycle     <SizeType>;
		using postcycle		= T_find_internal_diminished_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// minor:

	template<typename SizeType>
	struct T_find_internal_routine_minor
	{
		using precycle		= T_find_internal_minor_precycle  <SizeType>;
		using cycle		= T_find_internal_minor_cycle     <SizeType>;
		using postcycle		= T_find_internal_minor_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// interface:

	template<typename SizeType>
	struct T_find_internal_routine
	{
		using major		= T_find_internal_routine_major      <SizeType>;

		using tonic		= T_find_internal_routine_tonic      <SizeType>;
		using tone		= T_find_internal_routine_tone       <SizeType>;
		using peek		= T_find_internal_routine_peek       <SizeType>;

		using diminished	= T_find_internal_routine_diminished <SizeType>;
		using minor		= T_find_internal_routine_minor      <SizeType>;
	};

	template<typename SizeType>
	using T_find_internal = T_internal_routine<T_find_internal_routine, SizeType>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// construct:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_find_construct_precycle : public T_construct_precycle<SizeType>
	{
		using base		= T_construct_precycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		template<typename AST>
		nik_ces void define(AST *t)
		{
			base::define_notes_if (t);
			base::define_prepack  (t);
		}
	};

/***********************************************************************************************************************/

// cycle:

	template<typename SizeType>
	struct T_find_construct_cycle : public T_construct_cycle<SizeType>
	{
		using base		= T_construct_cycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		template<typename AST>
		nik_ces void define(AST *t) { base::define_pred_mat_mut_cond_note(t, AN::find); }
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename SizeType>
	struct T_find_construct_postcycle : public T_construct_postcycle<SizeType>
	{
		using base		= T_construct_postcycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		template<typename AST>
		nik_ces void define(AST *t)
		{
			base::define_mat_mut_cond (t, AN::find);
			base::define_notes        (t);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// major:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_find_construct_major_precycle : public T_find_construct_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_find_construct_major_cycle : public T_find_construct_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_find_construct_major_postcycle
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		template<typename AST>
		nik_ces void define(AST *t) { } // do nothing.
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (augmented) tonic:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_find_construct_tonic_precycle : public T_construct_precycle<SizeType>
	{
		using base		= T_construct_precycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		template<typename AST>
		nik_ces void define(AST *t)
		{
			base::define_notes   (t);
			base::define_prepack (t);
		}
	};

// cycle:

	template<typename SizeType>
	struct T_find_construct_tonic_cycle : public T_find_construct_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_find_construct_tonic_postcycle : public T_find_construct_postcycle<SizeType> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (augmented) tone:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_find_construct_tone_precycle : public T_find_construct_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_find_construct_tone_cycle : public T_find_construct_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_find_construct_tone_postcycle : public T_construct_postcycle<SizeType>
	{
		using base		= T_construct_postcycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		template<typename AST>
		nik_ces void define(AST *t) { base::define_notes(t); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (augmented) peek:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_find_construct_peek_precycle : public T_find_construct_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_find_construct_peek_cycle : public T_find_construct_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_find_construct_peek_postcycle : public T_find_construct_postcycle<SizeType> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// diminished:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_find_construct_diminished_precycle : public T_find_construct_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_find_construct_diminished_cycle : public T_find_construct_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_find_construct_diminished_postcycle : public T_construct_postcycle<SizeType>
	{
		using base		= T_construct_postcycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		template<typename AST>
		nik_ces void define(AST *t) { base::define_mat_mut_cond(t, AN::find); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// minor:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_find_construct_minor_precycle : public T_find_construct_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_find_construct_minor_cycle : public T_find_construct_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_find_construct_minor_postcycle : public T_construct_postcycle<SizeType>
	{
		using base		= T_construct_postcycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		template<typename AST>
		nik_ces void define(AST *t)
		{
			base::define_mat_mut_cond (t, AN::find);
			base::define_notes        (t);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// routine:

/***********************************************************************************************************************/

// major:

	template<typename SizeType>
	struct T_find_construct_routine_major
	{
		using precycle		= T_find_construct_major_precycle  <SizeType>;
		using cycle		= T_find_construct_major_cycle     <SizeType>;
		using postcycle		= T_find_construct_major_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// tonic:

	template<typename SizeType>
	struct T_find_construct_routine_tonic
	{
		using precycle		= T_find_construct_tonic_precycle  <SizeType>;
		using cycle		= T_find_construct_tonic_cycle     <SizeType>;
		using postcycle		= T_find_construct_tonic_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// tone:

	template<typename SizeType>
	struct T_find_construct_routine_tone
	{
		using precycle		= T_find_construct_tone_precycle  <SizeType>;
		using cycle		= T_find_construct_tone_cycle     <SizeType>;
		using postcycle		= T_find_construct_tone_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// peek:

	template<typename SizeType>
	struct T_find_construct_routine_peek
	{
		using precycle		= T_find_construct_peek_precycle  <SizeType>;
		using cycle		= T_find_construct_peek_cycle     <SizeType>;
		using postcycle		= T_find_construct_peek_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// diminished:

	template<typename SizeType>
	struct T_find_construct_routine_diminished
	{
		using precycle		= T_find_construct_diminished_precycle  <SizeType>;
		using cycle		= T_find_construct_diminished_cycle     <SizeType>;
		using postcycle		= T_find_construct_diminished_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// minor:

	template<typename SizeType>
	struct T_find_construct_routine_minor
	{
		using precycle		= T_find_construct_minor_precycle  <SizeType>;
		using cycle		= T_find_construct_minor_cycle     <SizeType>;
		using postcycle		= T_find_construct_minor_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// interface:

	template<typename SizeType>
	struct T_find_construct_routine
	{
		using major		= T_find_construct_routine_major      <SizeType>;

		using tonic		= T_find_construct_routine_tonic      <SizeType>;
		using tone		= T_find_construct_routine_tone       <SizeType>;
		using peek		= T_find_construct_routine_peek       <SizeType>;

		using diminished	= T_find_construct_routine_diminished <SizeType>;
		using minor		= T_find_construct_routine_minor      <SizeType>;
	};

	template<typename SizeType>
	using T_find_construct = T_construct_routine<T_find_construct_routine, SizeType>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

