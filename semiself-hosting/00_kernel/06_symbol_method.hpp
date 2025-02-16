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

// ring:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class symbol_ring_cmethod_disjoint : public Base
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

			nik_ce symbol_ring_cmethod_disjoint() : base{} { }
			nik_ce symbol_ring_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using symbol_ring_cmethod =
			symbol_ring_cmethod_disjoint <
			corpus_cmethod < Facade, glyph_ring_cmethod, image_ring_cmethod >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class symbol_ring_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		protected:

		//	nik_ces size_type goffset	= GRing::dimension;

		public:

			nik_ce symbol_ring_method_disjoint() : base{} { }
			nik_ce symbol_ring_method_disjoint(const facade & f) : base{f} { }

		public:

			// same types:

			//	template<typename T, typename... Ts>
			//	nik_ce bool same_types(const T & l, const Ts &... rs)
			//		{ return base::glyph_method.same_types(goffset, l.index(), rs.index()...); }

		protected:

			nik_ce auto declare_image(icon_ctype_ref icon, size_ctype time, size_ctype point)
			{
				if (base::glyph_cmethod.is_fail(icon)) { return base::image_cmethod.fail_sign(); }

				return base::image_method.declare(icon, time, point);
			}

		public:

			// point:

				nik_ce size_type get_abstract_point(sign_ctype_ref sign)
					{ return base::image_cmethod.get(sign, ImageRing::point); }

			// declare:

				nik_ce auto declare(size_ctype bytes) { return base::glyph_method.declare(bytes); }

				nik_ce auto declare(size_ctype bytes, size_ctype time, size_ctype point)
					{ return declare_image(declare(bytes), time, point); }
	};

	// syntactic sugar:

		template<typename Facade>
		using symbol_ring_method =
			symbol_ring_method_disjoint  <
			symbol_ring_cmethod_disjoint <
			corpus_method < Facade, glyph_ring_cmethod, image_ring_cmethod,
						 glyph_ring_method,  image_ring_method >>>;

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
			symbol_tuple_cmethod_disjoint <
			corpus_cmethod < Facade, glyph_tuple_cmethod, image_tuple_cmethod >>;

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
			symbol_tuple_method_disjoint  <
			symbol_tuple_cmethod_disjoint <
			corpus_method < Facade, glyph_tuple_cmethod, image_tuple_cmethod,
						 glyph_tuple_method,  image_tuple_method >>>;

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
			symbol_cotuple_cmethod_disjoint <
			corpus_cmethod < Facade, glyph_cotuple_cmethod, image_cotuple_cmethod >>;

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
			symbol_cotuple_method_disjoint  <
			symbol_cotuple_cmethod_disjoint <
			corpus_method < Facade, glyph_cotuple_cmethod, image_cotuple_cmethod,
						 glyph_cotuple_method,  image_cotuple_method >>>;

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
			symbol_function_cmethod_disjoint <
			corpus_cmethod < Facade, glyph_function_cmethod, image_function_cmethod >>;

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
			symbol_function_method_disjoint  <
			symbol_function_cmethod_disjoint <
			corpus_method < Facade, glyph_function_cmethod, image_function_cmethod,
						 glyph_function_method,  image_function_method >>>;

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

