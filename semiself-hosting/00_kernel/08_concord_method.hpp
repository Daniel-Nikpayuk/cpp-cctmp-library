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

// concord method:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// builtin:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class concord_builtin_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce concord_builtin_cmethod_disjoint() : base{} { }
			nik_ce concord_builtin_cmethod_disjoint(const facade & f) : base{f} { }

			// point:

				nik_ce auto cpoint(sign_ctype_ref sign)
					{ return base::symbol_cmethod().image_ctext_at(ImageBuiltin::point); }

			// value:

				nik_ce size_type cvalue(sign_ctype_ref sign)
					{ return base::record_csubmethod().cat(cpoint(sign)); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_builtin_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		protected:

			nik_ce auto declare_image(icon_ctype_ref icon, size_ctype time, size_ctype point)
				{ return base::symbol_method().declare_image(icon, time, point); }

		public:

			nik_ce concord_builtin_method_disjoint() : base{} { }
			nik_ce concord_builtin_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_type(size_ctype instr, size_ctype bytes)
					{ return base::symbol_method().declare_type(instr, bytes); }

				nik_ce auto declare_abstract(icon_ctype_ref icon)
					{ return declare_image(icon, ImageTime::abstract, base::record().expand(1)); }

				nik_ce auto declare_concrete(icon_ctype_ref icon)
					{ return declare_image(icon, ImageTime::concrete, base::record().expand(1)); }

			// define:

				nik_ce auto define_abstract(icon_ctype_ref icon, size_ctype value)
				{
					auto point       = base::record().expand(1); // unit_size
					auto sign        = declare_image(icon, ImageTime::abstract, point);
					auto record_ival = base::record_submethod();

					record_ival[point] = value;

					return sign;
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ring:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class concord_ring_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce concord_ring_cmethod_disjoint() : base{} { }
			nik_ce concord_ring_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_ring_cmethod =
			concord_ring_cmethod_disjoint    <
			concord_builtin_cmethod_disjoint <
			concord_cmethod_disjoint         < symbol_builtin_cmethod , array_csubmethod , Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_ring_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce concord_ring_method_disjoint() : base{} { }
			nik_ce concord_ring_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_type(size_ctype bytes)
					{ return base::declare_type(GlyphInstr::ring, bytes); }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_ring_method =
			concord_ring_method_disjoint     <
			concord_ring_cmethod_disjoint    <
			concord_builtin_method_disjoint  <
			concord_builtin_cmethod_disjoint <
			concord_method_disjoint          < symbol_builtin_method  , array_submethod  ,
			concord_cmethod_disjoint         < symbol_builtin_cmethod , array_csubmethod , Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// flex:

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class concord_tuple_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce concord_tuple_cmethod_disjoint() : base{} { }
			nik_ce concord_tuple_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_tuple_cmethod =
			concord_tuple_cmethod_disjoint <
			concord_cmethod_disjoint       < symbol_tuple_cmethod , array_csubmethod , Facade >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_tuple_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce concord_tuple_method_disjoint() : base{} { }
			nik_ce concord_tuple_method_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_tuple_method =
			concord_tuple_method_disjoint  <
			concord_tuple_cmethod_disjoint <
			concord_method_disjoint        < symbol_tuple_method  , array_submethod  ,
			concord_cmethod_disjoint       < symbol_tuple_cmethod , array_csubmethod , Facade >>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cotuple:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class concord_cotuple_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce concord_cotuple_cmethod_disjoint() : base{} { }
			nik_ce concord_cotuple_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_cotuple_cmethod =
			concord_cotuple_cmethod_disjoint <
			concord_cmethod_disjoint         < symbol_cotuple_cmethod , array_csubmethod , Facade >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_cotuple_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce concord_cotuple_method_disjoint() : base{} { }
			nik_ce concord_cotuple_method_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_cotuple_method =
			concord_cotuple_method_disjoint  <
			concord_cotuple_cmethod_disjoint <
			concord_method_disjoint          < symbol_cotuple_method  , array_submethod  ,
			concord_cmethod_disjoint         < symbol_cotuple_cmethod , array_csubmethod , Facade >>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// function:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class concord_function_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		protected:

			using contr_type		= typename model_type::template
								record_csubmethod_type<table_csubmethod>;

		public:

			nik_ce concord_function_cmethod_disjoint() : base{} { }
			nik_ce concord_function_cmethod_disjoint(const facade & f) : base{f} { }

		protected:

			// contr:

				nik_ce auto get_contr(sign_ctype_ref sign) const
				{
					auto sit_cival = base::symbol_cmethod().image_cmethod().text_csubmethod(sign);
					auto rec_cival = base::model->template record_csubequip<contr_type>();

					size_ctype length   = base::crecord().cat(sit_cival[ImageFunction::length]);
					size_ctype start    = sit_cival[ImageFunction::point];
					size_ctype finish   = start + length;
					size_ctype row_size = (length >> 2);
					size_ctype col_size = 4;

					rec_cival.mid_set(start, finish);
					rec_cival.set_dimension(row_size, col_size);

					return rec_cival;
				}

			//	nik_ce auto contr_ctext(sign_ctype_ref sign) const
			//		{ return base::symbol_cmethod().image_cmethod().text_csubmethod(sign); }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_function_cmethod =
			concord_function_cmethod_disjoint <
			concord_cmethod_disjoint          < symbol_function_cmethod , array_csubmethod , Facade >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_function_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		protected:

			nik_ce auto declare_image(
				icon_ctype_ref icon, size_ctype time, size_ctype length, size_ctype point)
					{ return base::symbol_method().declare_image(icon, time, length, point); }

		public:

			nik_ce concord_function_method_disjoint() : base{} { }
			nik_ce concord_function_method_disjoint(const facade & f) : base{f} { }

			// declare:

				template<auto N>
				nik_ce auto declare_type(const icon_type (&t)[N])
				{
					using array_type = array<icon_type, size_type, N>;

					return base::symbol_method().declare_type(array_type{t});
				}

				nik_ce auto declare_abstract(icon_ctype_ref icon, size_ctype n)
				{
					auto length = base::record().expand(1);
					auto point  = base::record().expand(n);

					return declare_image(icon, ImageTime::abstract, length, point);
				}

				nik_ce auto declare_concrete(icon_ctype_ref icon, size_ctype n)
				{
					auto length = base::record().expand(1);
					auto point  = base::record().expand(n);

					return declare_image(icon, ImageTime::concrete, length, point);
				}

			// define:

				template<auto N>
				nik_ce auto define_abstract(icon_ctype_ref icon, const size_type (&cc_asm)[N])
				{
					auto length      = base::record().expand(1);
					auto point       = base::record().expand(N);
					auto sign        = declare_image(icon, ImageTime::abstract, length, point);
					auto record_ival = base::record_submethod();

					record_ival[length] = N;

						// requires type check.
					for (size_type k = 0; k != N; ++k, ++point)
						{ record_ival[point] = cc_asm[k]; }

					return sign;
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_function_method =
			concord_function_method_disjoint  <
			concord_function_cmethod_disjoint <
			concord_method_disjoint           < symbol_function_method  , array_submethod  ,
			concord_cmethod_disjoint          < symbol_function_cmethod , array_csubmethod , Facade >>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// list:

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// identity:

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// exists:

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// forall:

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

