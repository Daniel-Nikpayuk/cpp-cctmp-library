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

// image method:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// times:

	struct ImageTime { enum : genum_type { abstract, concrete, dimension }; };

/***********************************************************************************************************************/

// base:

	struct ImageBase { enum : genum_type { mark, index, dimension }; };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// base:

/***********************************************************************************************************************/

// immutable:

	template<typename Base> // inheritance as {glyph, image} optimization.
	class image_cmethod_disjoint : public book_cmethod_disjoint<array_cmethod, array_csubmethod, Base>
	{
		public:

			using base			= book_cmethod_disjoint<array_cmethod, array_csubmethod, Base>;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_type_ref		= typename base::sign_type_ref;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		protected:

			using page_cmethod_type		= typename base::page_cmethod_type;
			using text_csubmethod_type	= typename base::text_csubmethod_type;

		public:

			nik_ce image_cmethod_disjoint() : base{} { }
			nik_ce image_cmethod_disjoint(const facade & f) : base{f} { }

			// sign:

				nik_ce auto make_sign(size_type n, size_ctype m) const { return sign_type{n, m}; }

			// fail:

				nik_ce bool is_fail(sign_ctype_ref n) const
				{
					return false;
				}

				nik_ce bool not_fail(sign_ctype_ref n) const { return not is_fail(n); }

				nik_ce auto fail_sign()
				{
					// fail sign should construct
					// a fail message type/value.

					return make_sign(0, 0);
				}

			// text:

					// safe version should reset dimensions.
				nik_ce void fast_set_ctext_from_sign(sign_ctype_ref sign)
				{
					base::fast_set_cpage_chapter(sign.mark());
					base::fast_set_ctext_from_page(sign.index());
				}

				nik_ce size_type fast_ctext_at(size_ctype n) const
					{ return base::text_csubmethod[n]; }

				nik_ce size_type ctext_at(sign_ctype_ref sign, size_ctype n)
				{
					fast_set_ctext_from_sign(sign);

					return fast_ctext_at(n);
				}
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base> // inheritance as {glyph, image} optimization.
	class image_method_disjoint : public book_method_disjoint<array_method, array_submethod, Base>
	{
		public:

			using base			= book_method_disjoint<array_method, array_submethod, Base>;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_type_ref		= typename base::sign_type_ref;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce image_method_disjoint() : base{} { }
			nik_ce image_method_disjoint(const facade & f) : base{f} { }

			nik_ce void set_icon_fields(icon_ctype_ref icon)
			{
				base::text_submethod[ImageBase::mark ] = icon.mark ();
				base::text_submethod[ImageBase::index] = icon.index();
			}

			// text:

					// safe version should reset dimensions.
				nik_ce void fast_set_text_from_sign(sign_ctype_ref sign)
				{
					base::fast_set_page_chapter(sign.mark());
					base::fast_set_text_from_page(sign.index());
				}

			// allocate:

				nik_ce auto allocate(size_ctype n, size_ctype m)
				{
					if (base::allocate(n, m))
						{ return base::make_sign(n, base::page_cmethod.max()); }
					else    { return base::fail_sign(); }
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// builtin:

	struct ImageBuiltin
	{
		enum : genum_type { mark = ImageBase::mark, index = ImageBase::index, time, point, dimension };
	};

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class image_builtin_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_type_ref		= typename base::sign_type_ref;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce image_builtin_cmethod_disjoint() : base{} { }
			nik_ce image_builtin_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using image_builtin_cmethod =
			image_builtin_cmethod_disjoint <
			image_cmethod_disjoint         < Facade >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class image_builtin_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_type_ref		= typename base::sign_type_ref;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		protected:

			nik_ces size_type length	= ImageBuiltin::dimension;
			nik_ces size_type unit_length	= 1;

		public:

			nik_ce image_builtin_method_disjoint() : base{} { }
			nik_ce image_builtin_method_disjoint(const facade & f) : base{f} { }

		//	nik_ce size_type unit_size() const { return unit_length; }

			nik_ce void instantiate(icon_ctype_ref icon, size_ctype time, size_ctype point)
			{
				base::set_icon_fields(icon);

				base::text_submethod[ImageBuiltin::time ] = time;
				base::text_submethod[ImageBuiltin::point] = point;
			}

			nik_ce auto declare(icon_ctype_ref icon, size_ctype time, size_ctype point)
			{
				auto sign = base::allocate(icon.mark(), length);

				if (base::not_fail(sign)) { instantiate(icon, time, point); }

				return sign;
			}
	};

	// syntactic sugar:

		template<typename Facade>
		using image_builtin_method =
			image_builtin_method_disjoint  <
			image_builtin_cmethod_disjoint <
			image_method_disjoint          <
			image_cmethod_disjoint         < Facade >>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

	struct ImageTuple
	{
		enum : genum_type { mark = ImageBase::mark, index = ImageBase::index, length, start, dimension };
	};

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class image_tuple_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_type_ref		= typename base::sign_type_ref;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce image_tuple_cmethod_disjoint() : base{} { }
			nik_ce image_tuple_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using image_tuple_cmethod =
			image_tuple_cmethod_disjoint <
			image_cmethod_disjoint          < Facade >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class image_tuple_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_type_ref		= typename base::sign_type_ref;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce image_tuple_method_disjoint() : base{} { }
			nik_ce image_tuple_method_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using image_tuple_method =
			image_tuple_method_disjoint  <
			image_tuple_cmethod_disjoint <
			image_method_disjoint           <
			image_cmethod_disjoint          < Facade >>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cotuple:

	struct ImageCotuple
	{
		enum : genum_type
		{
			mark = ImageBase::mark, index = ImageBase::index, length, injection, start, dimension
		};
	};

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class image_cotuple_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_type_ref		= typename base::sign_type_ref;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce image_cotuple_cmethod_disjoint() : base{} { }
			nik_ce image_cotuple_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using image_cotuple_cmethod =
			image_cotuple_cmethod_disjoint <
			image_cmethod_disjoint         < Facade >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class image_cotuple_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_type_ref		= typename base::sign_type_ref;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce image_cotuple_method_disjoint() : base{} { }
			nik_ce image_cotuple_method_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using image_cotuple_method =
			image_cotuple_method_disjoint  <
			image_cotuple_cmethod_disjoint <
			image_method_disjoint          <
			image_cmethod_disjoint         < Facade >>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// function:

	struct ImageFunction
	{
		enum : genum_type
		{
			mark = ImageBase::mark, index = ImageBase::index, time, length, point, dimension
		};
	};

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class image_function_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_type_ref		= typename base::sign_type_ref;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce image_function_cmethod_disjoint() : base{} { }
			nik_ce image_function_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using image_function_cmethod =
			image_function_cmethod_disjoint <
			image_cmethod_disjoint          < Facade >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class image_function_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_type_ref		= typename base::sign_type_ref;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce image_function_method_disjoint() : base{} { }
			nik_ce image_function_method_disjoint(const facade & f) : base{f} { }

			nik_ce void instantiate(icon_ctype_ref icon, size_ctype time, size_ctype length, size_ctype point)
			{
				base::set_icon_fields(icon);

				base::text_submethod[ImageFunction::time  ] = time;
				base::text_submethod[ImageFunction::length] = length;
				base::text_submethod[ImageFunction::point ] = point;
			}

			nik_ce auto declare(icon_ctype_ref icon, size_ctype time, size_ctype length, size_ctype point)
			{
				auto sign = base::allocate(icon.mark(), 5);

				if (base::not_fail(sign)) { instantiate(icon, time, length, point); }

				return sign;
			}
	};

	// syntactic sugar:

		template<typename Facade>
		using image_function_method =
			image_function_method_disjoint  <
			image_function_cmethod_disjoint <
			image_method_disjoint           <
			image_cmethod_disjoint          < Facade >>>>;

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

