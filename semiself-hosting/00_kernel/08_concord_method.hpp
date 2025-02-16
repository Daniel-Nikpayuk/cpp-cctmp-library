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

// ring:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class concord_ring_cmethod_disjoint : public Base
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

			nik_ce concord_ring_cmethod_disjoint() : base{} { }
			nik_ce concord_ring_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_ring_cmethod =
			concord_ring_cmethod_disjoint <
			concord_cmethod < Facade, symbol_ring_cmethod, array_csubmethod >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_ring_method_disjoint : public Base
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

			nik_ce concord_ring_method_disjoint() : base{} { }
			nik_ce concord_ring_method_disjoint(const facade & f) : base{f} { }

			// initialization:

				// declare:

				nik_ce auto declare(size_ctype bytes, size_ctype time)
				{
					size_ctype point = base::record().expand(1); // unit_size

					return base::symbol_method.declare(bytes, time, point);
				}

				nik_ce auto declare_abstract(size_ctype bytes)
					{ return declare(bytes, ImageTime::abstract); }

				nik_ce auto declare_concrete(size_ctype bytes)
					{ return declare(bytes, ImageTime::concrete); }

				nik_ce auto define_abstract(size_ctype bytes, size_ctype value)
				{
					auto sign  = declare_abstract(bytes);
					auto point = base::symbol_method.get_abstract_point(sign);

					base::record_submethod[point] = value;

					return sign;
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_ring_method =
			concord_ring_method_disjoint  <
			concord_ring_cmethod_disjoint <
			concord_method < Facade, symbol_ring_cmethod, array_csubmethod,
						  symbol_ring_method,  array_submethod >>>;

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
			concord_cmethod < Facade, symbol_tuple_cmethod, array_csubmethod >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_tuple_method_disjoint : public Base
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

			nik_ce concord_tuple_method_disjoint() : base{} { }
			nik_ce concord_tuple_method_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_tuple_method =
			concord_tuple_method_disjoint  <
			concord_tuple_cmethod_disjoint <
			concord_method < Facade, symbol_tuple_cmethod, array_csubmethod,
						  symbol_tuple_method,  array_submethod >>>;

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
			concord_cmethod < Facade, symbol_cotuple_cmethod, array_csubmethod >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_cotuple_method_disjoint : public Base
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

			nik_ce concord_cotuple_method_disjoint() : base{} { }
			nik_ce concord_cotuple_method_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_cotuple_method =
			concord_cotuple_method_disjoint  <
			concord_cotuple_cmethod_disjoint <
			concord_method < Facade, symbol_cotuple_cmethod, array_csubmethod,
						  symbol_cotuple_method,  array_submethod >>>;

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

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce concord_function_cmethod_disjoint() : base{} { }
			nik_ce concord_function_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_function_cmethod =
			concord_function_cmethod_disjoint <
			concord_cmethod < Facade, symbol_function_cmethod, array_csubmethod >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_function_method_disjoint : public Base
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

			nik_ce concord_function_method_disjoint() : base{} { }
			nik_ce concord_function_method_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_function_method =
			concord_function_method_disjoint  <
			concord_function_cmethod_disjoint <
			concord_method < Facade, symbol_function_cmethod, array_csubmethod,
						  symbol_function_method,  array_submethod >>>;

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

