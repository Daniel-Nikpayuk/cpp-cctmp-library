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

// repeat:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// spec:

/***********************************************************************************************************************/

// interface:

	template<typename SizeType>
	struct T_repeat_signature
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		enum : size_type { out, end, ins, dimension };
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// internal (construct):

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_repeat_internal_precycle : public T_internal_precycle<SizeType>
	{
		using base		= T_internal_precycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Sign		= T_repeat_signature<size_type>;

		template<typename AST>
		nik_ces void define(AST *t)
		{
			base::initialize_if       (t);
			base::define_next_note_if (t , AST::Ival::out , Sign::out );
			base::terminalize_if      (t);
		}
	};

/***********************************************************************************************************************/

// cycle:

	template<typename SizeType>
	struct T_repeat_internal_cycle : public T_internal_cycle<SizeType>
	{
		using base		= T_internal_cycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Sign		= T_repeat_signature<size_type>;

		template<typename AST>
		nik_ces void define(AST *t)
		{
			base::initialize           (t);
			base::define_next_note     (t , AST::Ival::out , Sign::out );
			base::define_next_note_ifs (t , AST::Ival::ins , Sign::ins );
			base::terminalize          (t);
		}
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename SizeType>
	struct T_repeat_internal_postcycle
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		template<typename AST>
		nik_ces void define(AST *t) { } // do nothing.
	};

	// syntactic sugar:

		template<typename SizeType>
		using T_repeat_internal_not_applicable = T_repeat_internal_postcycle<SizeType>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// major:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_repeat_internal_major_precycle : public T_repeat_internal_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_repeat_internal_major_cycle : public T_repeat_internal_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_repeat_internal_major_postcycle : public T_repeat_internal_postcycle<SizeType> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (augmented) tonic:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_repeat_internal_tonic_precycle : public T_repeat_internal_not_applicable<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_repeat_internal_tonic_cycle : public T_repeat_internal_not_applicable<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_repeat_internal_tonic_postcycle : public T_repeat_internal_not_applicable<SizeType> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (augmented) tone:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_repeat_internal_tone_precycle : public T_repeat_internal_not_applicable<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_repeat_internal_tone_cycle : public T_repeat_internal_not_applicable<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_repeat_internal_tone_postcycle : public T_repeat_internal_not_applicable<SizeType> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (augmented) peek:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_repeat_internal_peek_precycle : public T_repeat_internal_not_applicable<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_repeat_internal_peek_cycle : public T_repeat_internal_not_applicable<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_repeat_internal_peek_postcycle : public T_repeat_internal_not_applicable<SizeType> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// diminished:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_repeat_internal_diminished_precycle : public T_repeat_internal_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_repeat_internal_diminished_cycle : public T_repeat_internal_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_repeat_internal_diminished_postcycle : public T_repeat_internal_postcycle<SizeType> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// minor:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_repeat_internal_minor_precycle : public T_repeat_internal_not_applicable<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_repeat_internal_minor_cycle : public T_repeat_internal_not_applicable<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_repeat_internal_minor_postcycle : public T_repeat_internal_not_applicable<SizeType> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// routine:

/***********************************************************************************************************************/

// major:

	template<typename SizeType>
	struct T_repeat_internal_routine_major
	{
		using precycle		= T_repeat_internal_major_precycle  <SizeType>;
		using cycle		= T_repeat_internal_major_cycle     <SizeType>;
		using postcycle		= T_repeat_internal_major_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// tonic:

	template<typename SizeType>
	struct T_repeat_internal_routine_tonic
	{
		using precycle		= T_repeat_internal_tonic_precycle  <SizeType>;
		using cycle		= T_repeat_internal_tonic_cycle     <SizeType>;
		using postcycle		= T_repeat_internal_tonic_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// tone:

	template<typename SizeType>
	struct T_repeat_internal_routine_tone
	{
		using precycle		= T_repeat_internal_tone_precycle  <SizeType>;
		using cycle		= T_repeat_internal_tone_cycle     <SizeType>;
		using postcycle		= T_repeat_internal_tone_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// peek:

	template<typename SizeType>
	struct T_repeat_internal_routine_peek
	{
		using precycle		= T_repeat_internal_peek_precycle  <SizeType>;
		using cycle		= T_repeat_internal_peek_cycle     <SizeType>;
		using postcycle		= T_repeat_internal_peek_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// diminished:

	template<typename SizeType>
	struct T_repeat_internal_routine_diminished
	{
		using precycle		= T_repeat_internal_diminished_precycle  <SizeType>;
		using cycle		= T_repeat_internal_diminished_cycle     <SizeType>;
		using postcycle		= T_repeat_internal_diminished_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// minor:

	template<typename SizeType>
	struct T_repeat_internal_routine_minor
	{
		using precycle		= T_repeat_internal_minor_precycle  <SizeType>;
		using cycle		= T_repeat_internal_minor_cycle     <SizeType>;
		using postcycle		= T_repeat_internal_minor_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// interface:

	template<typename SizeType>
	struct T_repeat_internal_routine
	{
		using major		= T_repeat_internal_routine_major      <SizeType>;

		using tonic		= T_repeat_internal_routine_tonic      <SizeType>;
		using tone		= T_repeat_internal_routine_tone       <SizeType>;
		using peek		= T_repeat_internal_routine_peek       <SizeType>;

		using diminished	= T_repeat_internal_routine_diminished <SizeType>;
		using minor		= T_repeat_internal_routine_minor      <SizeType>;
	};

	template<typename SizeType>
	using T_repeat_internal = T_internal_routine<T_repeat_internal_routine, SizeType>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// construct:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_repeat_construct_precycle : public T_construct_precycle<SizeType>
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
	struct T_repeat_construct_cycle : public T_construct_cycle<SizeType>
	{
		using base		= T_construct_cycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		template<typename AST>
		nik_ces void define(AST *t) { base::define_pred_act_mut(t, AN::repeat); }
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename SizeType>
	struct T_repeat_construct_postcycle
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		template<typename AST>
		nik_ces void define(AST *t) { } // do nothing.
	};

	// syntactic sugar:

		template<typename SizeType>
		using T_repeat_construct_not_applicable = T_repeat_construct_postcycle<SizeType>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// major:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_repeat_construct_major_precycle : public T_repeat_construct_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_repeat_construct_major_cycle : public T_repeat_construct_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_repeat_construct_major_postcycle : public T_repeat_construct_postcycle<SizeType> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (augmented) tonic:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_repeat_construct_tonic_precycle : public T_repeat_construct_not_applicable<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_repeat_construct_tonic_cycle : public T_repeat_construct_not_applicable<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_repeat_construct_tonic_postcycle : public T_repeat_construct_not_applicable<SizeType> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (augmented) tone:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_repeat_construct_tone_precycle : public T_repeat_construct_not_applicable<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_repeat_construct_tone_cycle : public T_repeat_construct_not_applicable<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_repeat_construct_tone_postcycle : public T_repeat_construct_not_applicable<SizeType> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (augmented) peek:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_repeat_construct_peek_precycle : public T_repeat_construct_not_applicable<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_repeat_construct_peek_cycle : public T_repeat_construct_not_applicable<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_repeat_construct_peek_postcycle : public T_repeat_construct_not_applicable<SizeType> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// diminished:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_repeat_construct_diminished_precycle : public T_repeat_construct_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_repeat_construct_diminished_cycle : public T_repeat_construct_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_repeat_construct_diminished_postcycle : public T_construct_postcycle<SizeType>
	{
		using base		= T_construct_postcycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		template<typename AST>
		nik_ces void define(AST *t) { base::define_act_mut(t, AN::repeat); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// minor:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_repeat_construct_minor_precycle : public T_repeat_construct_not_applicable<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_repeat_construct_minor_cycle : public T_repeat_construct_not_applicable<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_repeat_construct_minor_postcycle : public T_repeat_construct_not_applicable<SizeType> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// routine:

/***********************************************************************************************************************/

// major:

	template<typename SizeType>
	struct T_repeat_construct_routine_major
	{
		using precycle		= T_repeat_construct_major_precycle  <SizeType>;
		using cycle		= T_repeat_construct_major_cycle     <SizeType>;
		using postcycle		= T_repeat_construct_major_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// tonic:

	template<typename SizeType>
	struct T_repeat_construct_routine_tonic
	{
		using precycle		= T_repeat_construct_tonic_precycle  <SizeType>;
		using cycle		= T_repeat_construct_tonic_cycle     <SizeType>;
		using postcycle		= T_repeat_construct_tonic_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// tone:

	template<typename SizeType>
	struct T_repeat_construct_routine_tone
	{
		using precycle		= T_repeat_construct_tone_precycle  <SizeType>;
		using cycle		= T_repeat_construct_tone_cycle     <SizeType>;
		using postcycle		= T_repeat_construct_tone_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// peek:

	template<typename SizeType>
	struct T_repeat_construct_routine_peek
	{
		using precycle		= T_repeat_construct_peek_precycle  <SizeType>;
		using cycle		= T_repeat_construct_peek_cycle     <SizeType>;
		using postcycle		= T_repeat_construct_peek_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// diminished:

	template<typename SizeType>
	struct T_repeat_construct_routine_diminished
	{
		using precycle		= T_repeat_construct_diminished_precycle  <SizeType>;
		using cycle		= T_repeat_construct_diminished_cycle     <SizeType>;
		using postcycle		= T_repeat_construct_diminished_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// minor:

	template<typename SizeType>
	struct T_repeat_construct_routine_minor
	{
		using precycle		= T_repeat_construct_minor_precycle  <SizeType>;
		using cycle		= T_repeat_construct_minor_cycle     <SizeType>;
		using postcycle		= T_repeat_construct_minor_postcycle <SizeType>;
	};

/***********************************************************************************************************************/

// interface:

	template<typename SizeType>
	struct T_repeat_construct_routine
	{
		using major		= T_repeat_construct_routine_major      <SizeType>;

		using tonic		= T_repeat_construct_routine_tonic      <SizeType>;
		using tone		= T_repeat_construct_routine_tone       <SizeType>;
		using peek		= T_repeat_construct_routine_peek       <SizeType>;

		using diminished	= T_repeat_construct_routine_diminished <SizeType>;
		using minor		= T_repeat_construct_routine_minor      <SizeType>;
	};

	template<typename SizeType>
	using T_repeat_construct = T_construct_routine<T_repeat_construct_routine, SizeType>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

