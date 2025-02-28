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

			// sub(ordinate) icon:

				nik_ce auto sub_icon(icon_ctype_ref icon, size_ctype n) const
					{ return base::glyph_cmethod().sub_icon(icon, n); }
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

				template<size_type Mark, size_type Instr, typename T>
				nik_ce auto declare_type(const T & v, size_ctype bytes, size_ctype universe)
				{
					return base::glyph_method().template
						declare_type<Mark, Instr>(v, bytes, universe);
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

// immutable:

	template<typename Base>
	class symbol_list_cmethod_disjoint : public Base
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

			nik_ce symbol_list_cmethod_disjoint() : base{} { }
			nik_ce symbol_list_cmethod_disjoint(const facade & f) : base{f} { }

			// sub(ordinate) icon:

				nik_ce auto sub_icon(icon_ctype_ref icon) const
					{ return base::glyph_cmethod().sub_icon(icon); }
	};

	// syntactic sugar:

		template<typename Facade>
		using symbol_list_cmethod =
			symbol_list_cmethod_disjoint <
			corpus_cmethod_disjoint      < glyph_list_cmethod , image_list_cmethod , Facade >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class symbol_list_method_disjoint : public Base
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

			nik_ce symbol_list_method_disjoint() : base{} { }
			nik_ce symbol_list_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_type(icon_ctype_ref icon)
					{ return base::glyph_method().declare(icon); }

			// recurse:

				nik_ce auto recurse_type(icon_ctype_ref icon, icon_ctype_ref sub_icon)
					{ return base::glyph_method().recurse(icon, sub_icon); }
	};

	// syntactic sugar:

		template<typename Facade>
		using symbol_list_method =
			symbol_list_method_disjoint  <
			symbol_list_cmethod_disjoint <
			corpus_method_disjoint       < glyph_list_method  , image_list_method  ,
			corpus_cmethod_disjoint      < glyph_list_cmethod , image_list_cmethod , Facade >>>>;

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

// space:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class symbol_space_cmethod_disjoint : public Base
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

			nik_ce symbol_space_cmethod_disjoint() : base{} { }
			nik_ce symbol_space_cmethod_disjoint(const facade & f) : base{f} { }

			// sub(ordinate) icon:

				nik_ce auto sub_icon(icon_ctype_ref icon) const
					{ return base::glyph_cmethod().sub_icon(icon); }
	};

	// syntactic sugar:

		template<typename Facade>
		using symbol_space_cmethod =
			symbol_space_cmethod_disjoint <
			corpus_cmethod_disjoint       < glyph_space_cmethod , image_space_cmethod , Facade >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class symbol_space_method_disjoint : public Base
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

			nik_ce symbol_space_method_disjoint() : base{} { }
			nik_ce symbol_space_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_space() { return base::glyph_method().declare_space(); }

				nik_ce auto declare_type(size_ctype space, icon_ctype_ref sub_icon)
					{ return base::glyph_method().declare(space, sub_icon); }
	};

	// syntactic sugar:

		template<typename Facade>
		using symbol_space_method =
			symbol_space_method_disjoint  <
			symbol_space_cmethod_disjoint <
			corpus_method_disjoint        < glyph_space_method  , image_space_method  ,
			corpus_cmethod_disjoint       < glyph_space_cmethod , image_space_cmethod , Facade >>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

