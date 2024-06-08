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

// fold:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// spec:

/***********************************************************************************************************************/

// interface:

	template<typename SizeType>
	struct T_fold_signature
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		enum : size_type { out, in, end, ins, dimension };
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// resolution:

/***********************************************************************************************************************/

// interface:

	template<typename SizeType>
	struct T_chord_resolution_fold : public T_chord_resolution<SizeType>
	{
		using base		= T_chord_resolution<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

	//	template<typename AST>
	//	nik_ces auto (AST *t)
	//	{
	//	}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// internal (construct):

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_fold_internal_precycle : public T_internal_precycle<SizeType>
	{
		using base		= T_internal_precycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Sign		= T_fold_signature<size_type>;

		template<typename AST>
		nik_ces void define_if(AST *t)
		{
			base::initialize_if        (t);
			base::define_next_note_if  (t, AST::Ival::in, Sign::in);
			base::define_next_notes_if (t, AST::Ival::ins, Sign::ins);
			base::terminalize_if       (t);
		}
	};

/***********************************************************************************************************************/

// cycle:

	template<typename SizeType>
	struct T_fold_internal_cycle : public T_internal_cycle<SizeType>
	{
		using base		= T_internal_cycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Sign		= T_fold_signature<size_type>;

		template<typename AST>
		nik_ces void define_if(AST *t)
		{
			base::initialize        (t);
			base::define_next_note  (t, AST::Ival::in, Sign::in);
			base::define_next_notes (t, AST::Ival::ins, Sign::ins);
			base::terminalize       (t);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// major:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_fold_internal_major_precycle : public T_fold_internal_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_fold_internal_major_cycle : public T_fold_internal_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_fold_internal_major_postcycle
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		template<typename AST>
		nik_ces void define_if(AST *t) { } // do nothing.
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (augmented) tonic:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_fold_internal_tonic_precycle : public T_internal_precycle<SizeType>
	{
		using base		= T_internal_precycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Sign		= T_fold_signature<size_type>;

		template<typename AST>
		nik_ces void define_if(AST *t)
		{
			base::initialize           (t);
			base::define_next_note_if  (t, AST::Ival::in  , Sign::in  );
			base::define_next_notes_if (t, AST::Ival::ins , Sign::ins );
		//	base::define_prev_tonic    (t, AST::Ival::in  , Sign::end );
			base::terminalize          (t);
		}
	};

/***********************************************************************************************************************/

// cycle:

	template<typename SizeType>
	struct T_fold_internal_tonic_cycle : public T_fold_internal_cycle<SizeType> { };

/***********************************************************************************************************************/

// postcycle:

	template<typename SizeType>
	struct T_fold_internal_tonic_postcycle : public T_internal_postcycle<SizeType>
	{
		using base		= T_internal_postcycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Sign		= T_fold_signature<size_type>;

		template<typename AST>
		nik_ces void define_if(AST *t)
		{
			base::initialize        (t);
			base::define_next_note  (t, AST::Ival::in  , Sign::in  );
			base::define_next_notes (t, AST::Ival::ins , Sign::ins );
		//	base::define_next_tonic (t, AST::Ival::in  , Sign::end );
			base::terminalize       (t);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (augmented) tone:

/***********************************************************************************************************************/

// precycle:

/***********************************************************************************************************************/

// cycle:

	template<typename SizeType>
	struct T_fold_internal_tone_cycle : public T_fold_internal_cycle<SizeType> { };

/***********************************************************************************************************************/

// postcycle:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (augmented) peek:

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

	template<typename SizeType>
	struct T_fold_internal_diminished_precycle : public T_fold_internal_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_fold_internal_diminished_cycle : public T_fold_internal_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_fold_internal_diminished_postcycle
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		template<typename AST>
		nik_ces void define_if(AST *t) { } // do nothing.
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// minor:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_fold_internal_minor_precycle : public T_fold_internal_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_fold_internal_minor_cycle : public T_fold_internal_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_fold_internal_minor_postcycle : public T_internal_postcycle<SizeType>
	{
		using base		= T_internal_postcycle<SizeType>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Sign		= T_fold_signature<size_type>;

		template<typename AST>
		nik_ces void define_if(AST *t)
		{
			base::initialize        (t);
			base::define_next_notes (t, AST::Ival::ins, Sign::ins);
			base::terminalize       (t);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// routine:

/***********************************************************************************************************************/

// interface:

	template<typename SizeType>
	struct T_fold_internal_routine
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		// major:

			using major_precycle		= T_fold_internal_major_precycle  <SizeType>;
			using major_cycle		= T_fold_internal_major_cycle     <SizeType>;
			using major_postcycle		= T_fold_internal_major_postcycle <SizeType>;

			template<typename AST>
			nik_ces void define_major(AST *t)
			{
				major_precycle  ::define_if(t);
				major_cycle     ::define_if(t);
				major_postcycle ::define_if(t);
			}

		// (augmented) tonic:

			using tonic_precycle		= T_fold_internal_tonic_precycle  <SizeType>;
			using tonic_cycle		= T_fold_internal_tonic_cycle     <SizeType>;
			using tonic_postcycle		= T_fold_internal_tonic_postcycle <SizeType>;

			template<typename AST>
			nik_ces void define_tonic(AST *t)
			{
				tonic_precycle  ::define_if(t);
				tonic_cycle     ::define_if(t);
				tonic_postcycle ::define_if(t);
			}

		// (augmented) tone:

		//	using tone_precycle		= T_fold_internal_tone_precycle  <SizeType>;
		//	using tone_cycle		= T_fold_internal_tone_cycle     <SizeType>;
		//	using tone_postcycle		= T_fold_internal_tone_postcycle <SizeType>;

			template<typename AST>
			nik_ces void define_tone(AST *t)
			{
			//	tone_precycle  ::define_if(t);
			//	tone_cycle     ::define_if(t);
			//	tone_postcycle ::define_if(t);
			}

		// (augmented) peek:

		//	using peek_precycle		= T_fold_internal_peek_precycle  <SizeType>;
		//	using peek_cycle		= T_fold_internal_peek_cycle     <SizeType>;
		//	using peek_postcycle		= T_fold_internal_peek_postcycle <SizeType>;

			template<typename AST>
			nik_ces void define_peek(AST *t)
			{
			//	peek_precycle  ::define_if(t);
			//	peek_cycle     ::define_if(t);
			//	peek_postcycle ::define_if(t);
			}

		// augmented:

			template<typename AST>
			nik_ces void define_augmented(AST *t)
			{
				t->interval.resolve_augment(AST::Ival::in);

				if      (t->interval.is_tonic ()) define_tonic (t);
				else if (t->interval.is_tone  ()) define_tone  (t);
				else if (t->interval.is_peek  ()) define_peek  (t);
			}

		// diminished:

			using diminished_precycle	= T_fold_internal_diminished_precycle  <SizeType>;
			using diminished_cycle		= T_fold_internal_diminished_cycle     <SizeType>;
			using diminished_postcycle	= T_fold_internal_diminished_postcycle <SizeType>;

			template<typename AST>
			nik_ces void define_diminished(AST *t)
			{
				diminished_precycle  ::define_if(t);
				diminished_cycle     ::define_if(t);
				diminished_postcycle ::define_if(t);
			}

		// minor:

			using minor_precycle		= T_fold_internal_minor_precycle  <SizeType>;
			using minor_cycle		= T_fold_internal_minor_cycle     <SizeType>;
			using minor_postcycle		= T_fold_internal_minor_postcycle <SizeType>;

			template<typename AST>
			nik_ces void define_minor(AST *t)
			{
				minor_precycle  ::define_if(t);
				minor_cycle     ::define_if(t);
				minor_postcycle ::define_if(t);
			}

		template<typename AST>
		nik_ces void define(AST *t)
		{
			if      (t->interval.is_major      ()) define_major      (t);
			else if (t->interval.is_augmented  ()) define_augmented  (t);
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
	struct T_fold_construct_precycle
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		template<typename AST>
		nik_ces void define_notes(AST *t)
		{
			auto ni = t->iterate[AST::Iterate::preloop];

			t->assembly_push_instr(AN::cycle, AT::front, ni);
		}

		template<typename AST>
		nik_ces void define(AST *t)
		{
			if (t->interval.has_left_next()) define_notes(t);

			t->assembly_push_instr(AN::arg, AT::select, t->verse.size());
		}
	};

/***********************************************************************************************************************/

// cycle:

	template<typename SizeType>
	struct T_fold_construct_cycle
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		template<typename AST>
		nik_ces void define(AST *t)
		{
			auto ni = t->get_predicate ();
			auto mi = t->get_action    ();
			auto li = t->get_combine   ();
			auto ki = t->get_mutate    ();
			auto ji = t->iterate[AST::Iterate::loop];

			t->assembly_push_instr(AN::fold, AT::id, ni, mi, li, ki, ji);
		}
	};

/***********************************************************************************************************************/

// postcycle:

	template<typename SizeType>
	struct T_fold_construct_postcycle
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		template<typename AST>
		nik_ces void define(AST *t)
		{
			auto ni = t->get_action  ();
			auto mi = t->get_combine ();
			auto li = t->get_mutate  ();

			t->assembly_push_instr(AN::fold, AT::back, ni, mi, li);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// major:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_fold_construct_major_precycle : public T_fold_construct_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_fold_construct_major_cycle : public T_fold_construct_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_fold_construct_major_postcycle
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

/***********************************************************************************************************************/

// cycle:

/***********************************************************************************************************************/

// postcycle:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (augmented) tone:

/***********************************************************************************************************************/

// precycle:

/***********************************************************************************************************************/

// cycle:

/***********************************************************************************************************************/

// postcycle:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (augmented) peek:

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

	template<typename SizeType>
	struct T_fold_construct_diminished_precycle : public T_fold_construct_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_fold_construct_diminished_cycle : public T_fold_construct_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_fold_construct_diminished_postcycle : public T_fold_construct_postcycle<SizeType> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// minor:

/***********************************************************************************************************************/

// precycle:

	template<typename SizeType>
	struct T_fold_construct_minor_precycle : public T_fold_construct_precycle<SizeType> { };

// cycle:

	template<typename SizeType>
	struct T_fold_construct_minor_cycle : public T_fold_construct_cycle<SizeType> { };

// postcycle:

	template<typename SizeType>
	struct T_fold_construct_minor_postcycle
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		template<typename AST>
		nik_ces void define(AST *t) { } // do nothing.
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// routine:

/***********************************************************************************************************************/

// interface:

	template<typename SizeType>
	struct T_fold_construct_routine
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		// major:

			using major_precycle		= T_fold_construct_major_precycle  <SizeType>;
			using major_cycle		= T_fold_construct_major_cycle     <SizeType>;
			using major_postcycle		= T_fold_construct_major_postcycle <SizeType>;

			template<typename AST>
			nik_ces void define_major(AST *t)
			{
				major_precycle  ::define(t);
				major_cycle     ::define(t);
				major_postcycle ::define(t);
			}

		// (augmented) tonic:

		//	using tonic_precycle		= T_fold_construct_tonic_precycle  <SizeType>;
		//	using tonic_cycle		= T_fold_construct_tonic_cycle     <SizeType>;
		//	using tonic_postcycle		= T_fold_construct_tonic_postcycle <SizeType>;

			template<typename AST>
			nik_ces void define_tonic(AST *t)
			{
			//	tonic_precycle  ::define(t);
			//	tonic_cycle     ::define(t);
			//	tonic_postcycle ::define(t);
			}

		// (augmented) tone:

		//	using tone_precycle		= T_fold_construct_tone_precycle  <SizeType>;
		//	using tone_cycle		= T_fold_construct_tone_cycle     <SizeType>;
		//	using tone_postcycle		= T_fold_construct_tone_postcycle <SizeType>;

			template<typename AST>
			nik_ces void define_tone(AST *t)
			{
			//	tone_precycle  ::define(t);
			//	tone_cycle     ::define(t);
			//	tone_postcycle ::define(t);
			}

		// (augmented) peek:

		//	using peek_precycle		= T_fold_construct_peek_precycle  <SizeType>;
		//	using peek_cycle		= T_fold_construct_peek_cycle     <SizeType>;
		//	using peek_postcycle		= T_fold_construct_peek_postcycle <SizeType>;

			template<typename AST>
			nik_ces void define_peek(AST *t)
			{
			//	peek_precycle  ::define(t);
			//	peek_cycle     ::define(t);
			//	peek_postcycle ::define(t);
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

			using diminished_precycle	= T_fold_construct_diminished_precycle  <SizeType>;
			using diminished_cycle		= T_fold_construct_diminished_cycle     <SizeType>;
			using diminished_postcycle	= T_fold_construct_diminished_postcycle <SizeType>;

			template<typename AST>
			nik_ces void define_diminished(AST *t)
			{
				diminished_precycle  ::define(t);
				diminished_cycle     ::define(t);
				diminished_postcycle ::define(t);
			}

		// minor:

			using minor_precycle		= T_fold_construct_minor_precycle  <SizeType>;
			using minor_cycle		= T_fold_construct_minor_cycle     <SizeType>;
			using minor_postcycle		= T_fold_construct_minor_postcycle <SizeType>;

			template<typename AST>
			nik_ces void define_minor(AST *t)
			{
				minor_precycle  ::define(t);
				minor_cycle     ::define(t);
				minor_postcycle ::define(t);
			}

		template<typename AST>
		nik_ces void define(AST *t)
		{
			if      (t->interval.is_major      ()) define_major      (t);
			else if (t->interval.is_augmented  ()) define_augmented  (t);
			else if (t->interval.is_diminished ()) define_diminished (t);
			else if (t->interval.is_minor      ()) define_minor      (t);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

