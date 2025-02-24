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

// symbol method:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// builtin:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class symbol_builtin_cmethod_disjoint : public Base
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

			nik_ce symbol_builtin_cmethod_disjoint() : base{} { }
			nik_ce symbol_builtin_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using symbol_builtin_cmethod =
			symbol_builtin_cmethod_disjoint <
			corpus_cmethod_disjoint         < glyph_builtin_cmethod , image_builtin_cmethod , Facade >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class symbol_builtin_method_disjoint : public Base
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

			nik_ce symbol_builtin_method_disjoint() : base{} { }
			nik_ce symbol_builtin_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_type(size_ctype instr, size_ctype bytes)
					{ return base::glyph_method().declare(instr, bytes); }

				template<typename T>
				nik_ce auto declare_image(icon_ctype_ref icon, T & field)
				{
					return base::template
						declare_image<BookMark::builtin, ImageBuiltin::dimension>(icon, field);
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using symbol_builtin_method =
			symbol_builtin_method_disjoint  <
			symbol_builtin_cmethod_disjoint <
			corpus_method_disjoint          < glyph_builtin_method  , image_builtin_method  ,
			corpus_cmethod_disjoint         < glyph_builtin_cmethod , image_builtin_cmethod , Facade >>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// composite:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class symbol_composite_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce symbol_composite_cmethod_disjoint() : base{} { }
			nik_ce symbol_composite_cmethod_disjoint(const facade & f) : base{f} { }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class symbol_composite_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce symbol_composite_method_disjoint() : base{} { }
			nik_ce symbol_composite_method_disjoint(const facade & f) : base{f} { }

			// declare:

				template<size_type Mark, typename T>
				nik_ce auto declare_type(const T & v, size_ctype bytes, size_ctype universe)
				{
					return base::glyph_method().template
						declare_type<Mark>(v, bytes, universe);
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class symbol_tuple_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce symbol_tuple_cmethod_disjoint() : base{} { }
			nik_ce symbol_tuple_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using symbol_tuple_cmethod =
			symbol_tuple_cmethod_disjoint     <
			symbol_composite_cmethod_disjoint <
			corpus_cmethod_disjoint           < glyph_tuple_cmethod , image_tuple_cmethod , Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class symbol_tuple_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce symbol_tuple_method_disjoint() : base{} { }
			nik_ce symbol_tuple_method_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using symbol_tuple_method =
			symbol_tuple_method_disjoint      <
			symbol_tuple_cmethod_disjoint     <
			symbol_composite_method_disjoint  <
			symbol_composite_cmethod_disjoint <
			corpus_method_disjoint            < glyph_tuple_method  , image_tuple_method  ,
			corpus_cmethod_disjoint           < glyph_tuple_cmethod , image_tuple_cmethod , Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cotuple:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class symbol_cotuple_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce symbol_cotuple_cmethod_disjoint() : base{} { }
			nik_ce symbol_cotuple_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using symbol_cotuple_cmethod =
			symbol_cotuple_cmethod_disjoint   <
			symbol_composite_cmethod_disjoint <
			corpus_cmethod_disjoint           < glyph_cotuple_cmethod , image_cotuple_cmethod , Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class symbol_cotuple_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce symbol_cotuple_method_disjoint() : base{} { }
			nik_ce symbol_cotuple_method_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using symbol_cotuple_method =
			symbol_cotuple_method_disjoint    <
			symbol_cotuple_cmethod_disjoint   <
			symbol_composite_method_disjoint  <
			symbol_composite_cmethod_disjoint <
			corpus_method_disjoint            < glyph_cotuple_method  , image_cotuple_method  ,
			corpus_cmethod_disjoint           < glyph_cotuple_cmethod , image_cotuple_cmethod , Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// function:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class symbol_function_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce symbol_function_cmethod_disjoint() : base{} { }
			nik_ce symbol_function_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using symbol_function_cmethod =
			symbol_function_cmethod_disjoint  <
			symbol_composite_cmethod_disjoint <
			corpus_cmethod_disjoint           < glyph_function_cmethod , image_function_cmethod , Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class symbol_function_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce symbol_function_method_disjoint() : base{} { }
			nik_ce symbol_function_method_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using symbol_function_method =
			symbol_function_method_disjoint   <
			symbol_function_cmethod_disjoint  <
			symbol_composite_method_disjoint  <
			symbol_composite_cmethod_disjoint <
			corpus_method_disjoint            < glyph_function_method  , image_function_method  ,
			corpus_cmethod_disjoint           < glyph_function_cmethod , image_function_cmethod , Facade >>>>>>;

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

