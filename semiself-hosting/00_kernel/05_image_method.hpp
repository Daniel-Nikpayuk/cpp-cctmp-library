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

	struct ImageTime { enum : gkey_type { abstract, concrete, dimension }; };

/***********************************************************************************************************************/

// base:

	struct ImageBase { enum : gkey_type { mark, index, dimension }; };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// base:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class image_cmethod_disjoint : public book_cmethod_disjoint<Base, array_cmethod, array_csubmethod, sign>
	{
		public:

			using base		= book_cmethod_disjoint<Base, array_cmethod, array_csubmethod, sign>;
			using facade		= typename base::facade;

			nik_using_size_type	(base)

			using icon_type		= icon<size_type>;
			using icon_type_ref	= typename alias<icon_type>::type_ref;
			using icon_ctype_ref	= typename alias<icon_type>::ctype_ref;

			using sign_type		= typename base::note_type;
			using sign_type_ref	= typename base::note_type_ref;
			using sign_ctype_ref	= typename base::note_ctype_ref;

		public:

			nik_ce image_cmethod_disjoint() : base{} { }
			nik_ce image_cmethod_disjoint(const facade & f) : base{f} { }

			// fail:

				nik_ce bool is_fail(sign_ctype_ref n) const
				{
					return false;
				}

				nik_ce bool not_fail(sign_ctype_ref n) const { return not is_fail(n); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class image_method_disjoint : public book_method_disjoint<Base, array_method, array_submethod>
	{
		public:

			using base		= book_method_disjoint<Base, array_method, array_submethod>;
			using facade		= typename base::facade;

			nik_using_size_type	(base)

			using icon_type		= typename base::icon_type;
			using icon_type_ref	= typename base::icon_type_ref;
			using icon_ctype_ref	= typename base::icon_ctype_ref;

			using sign_type		= typename base::sign_type;
			using sign_type_ref	= typename base::sign_type_ref;
			using sign_ctype_ref	= typename base::sign_ctype_ref;

		public:

			nik_ce image_method_disjoint() : base{} { }
			nik_ce image_method_disjoint(const facade & f) : base{f} { }

			nik_ce void set_iconography(icon_ctype_ref icon)
			{
				base::text_submethod[ImageBase::mark ] = icon.mark ();
				base::text_submethod[ImageBase::index] = icon.index();
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// builtin:

	struct ImageBuiltin
	{
		enum : gkey_type { mark = ImageBase::mark, index = ImageBase::index, time, point, dimension };
	};

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class image_builtin_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type		(base)

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

			nik_using_size_type		(base)

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
				base::set_iconography(icon);

				base::text_submethod[ImageBuiltin::time ] = time;
				base::text_submethod[ImageBuiltin::point] = point;
			}

			nik_ce auto declare(icon_ctype_ref icon, size_ctype time, size_ctype point)
			{
				auto sign = base::allocate(BookMark::builtin, length);

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

// empty:

	using ImageEmpty = ImageBuiltin;

/***********************************************************************************************************************/

// immutable:

	template<typename Facade>
	class image_empty_cmethod : public image_builtin_cmethod<Facade>
	{
		public:

			using base			= image_builtin_cmethod<Facade>;
			using facade			= typename base::facade;

			nik_using_size_type		(base)

		public:

			nik_ce image_empty_cmethod() : base{} { }
			nik_ce image_empty_cmethod(const facade & f) : base{f} { }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Facade>
	class image_empty_method : public image_builtin_method<Facade>
	{
		public:

			using base			= image_builtin_method<Facade>;
			using facade			= typename base::facade;

			nik_using_size_type		(base)

		public:

			nik_ce image_empty_method() : base{} { }
			nik_ce image_empty_method(const facade & f) : base{f} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ring:

	using ImageRing = ImageBuiltin;

/***********************************************************************************************************************/

// immutable:

	template<typename Facade>
	class image_ring_cmethod : public image_builtin_cmethod<Facade>
	{
		public:

			using base			= image_builtin_cmethod<Facade>;
			using facade			= typename base::facade;

			nik_using_size_type		(base)

		public:

			nik_ce image_ring_cmethod() : base{} { }
			nik_ce image_ring_cmethod(const facade & f) : base{f} { }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Facade>
	class image_ring_method : public image_builtin_method<Facade>
	{
		public:

			using base			= image_builtin_method<Facade>;
			using facade			= typename base::facade;

			nik_using_size_type		(base)

		public:

			nik_ce image_ring_method() : base{} { }
			nik_ce image_ring_method(const facade & f) : base{f} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// flex:

	using ImageFlex = ImageBuiltin;

/***********************************************************************************************************************/

// immutable:

	template<typename Facade>
	class image_flex_cmethod : public image_builtin_cmethod<Facade>
	{
		public:

			using base			= image_builtin_cmethod<Facade>;
			using facade			= typename base::facade;

			nik_using_size_type		(base)

		public:

			nik_ce image_flex_cmethod() : base{} { }
			nik_ce image_flex_cmethod(const facade & f) : base{f} { }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Facade>
	class image_flex_method : public image_builtin_method<Facade>
	{
		public:

			using base			= image_builtin_method<Facade>;
			using facade			= typename base::facade;

			nik_using_size_type		(base)

		public:

			nik_ce image_flex_method() : base{} { }
			nik_ce image_flex_method(const facade & f) : base{f} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// utf8 char:

	using ImageUtf8Char = ImageBuiltin;

/***********************************************************************************************************************/

// immutable:

	template<typename Facade>
	class image_utf8_char_cmethod : public image_builtin_cmethod<Facade>
	{
		public:

			using base			= image_builtin_cmethod<Facade>;
			using facade			= typename base::facade;

			nik_using_size_type		(base)

		public:

			nik_ce image_utf8_char_cmethod() : base{} { }
			nik_ce image_utf8_char_cmethod(const facade & f) : base{f} { }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Facade>
	class image_utf8_char_method : public image_builtin_method<Facade>
	{
		public:

			using base			= image_builtin_method<Facade>;
			using facade			= typename base::facade;

			nik_using_size_type		(base)

		public:

			nik_ce image_utf8_char_method() : base{} { }
			nik_ce image_utf8_char_method(const facade & f) : base{f} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

	struct ImageTuple
	{
		enum : gkey_type { mark = ImageBase::mark, index = ImageBase::index, length, start, dimension };
	};

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cotuple:

	struct ImageCotuple
	{
		enum : gkey_type
		{
			mark = ImageBase::mark, index = ImageBase::index, length, injection, start, dimension
		};
	};

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// function:

/***********************************************************************************************************************/

// :

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

