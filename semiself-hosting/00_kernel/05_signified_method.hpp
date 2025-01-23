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

// signified method:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// base:

/***********************************************************************************************************************/

// immutable:

	template<typename Base, typename Base::size_type Name, typename Base::size_type Dimension>
	class signified_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename facade::model_type;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;
			using size_ctype_ptr		= typename alias<size_type>::ctype_ptr;
			using size_ctype_cptr		= typename alias<size_type>::ctype_cptr;

			using icon_type			= icon<size_type>;
			using icon_ctype_ref		= typename alias<icon_type>::ctype_ref;

		protected:

			nik_ces size_type name		= Name;
			nik_ces size_type dimension	= Dimension;
			nik_ces size_type bytes		= 1;

			using page_cmethod_type		= typename model_type::page_cmethod_type;
			using text_cmethod_type		= typename model_type::text_cmethod_type;

			page_cmethod_type page_cmethod;
			text_cmethod_type text_cmethod;

		public:

			nik_ce signified_cmethod_disjoint() : base{}, page_cmethod{}, text_cmethod{} { }
			nik_ce signified_cmethod_disjoint(const facade & f) :

				base{f},
				page_cmethod{page_cequip(name)},
				text_cmethod{text_cequip()}
				{ }

			nik_ce size_type byte_size() const { return bytes; }

			// page:

				nik_ce auto page_cequip(size_ctype n) const
					{ return base::model->page_cequip(n); }

			// text:

				nik_ce auto text_cequip() const { return base::model->text_cequip(); }

				 // unsafe, does not test against name().

				nik_ce auto text_csubequip(size_ctype n) const
					{ return base::model->text_csubequip(n); }

				nik_ce auto page_to_text_cequip(size_ctype n) const
					{ return text_csubequip(page_cmethod[n]); }

				nik_ce auto icon_to_text_cequip(icon_ctype_ref i) const
					{ return page_to_text_cequip(i.index()); }

			// icon:

				nik_ce auto fail_icon() const { return icon_type{Logo::fail, 0}; }
				nik_ce auto make_icon(size_ctype pos) const { return icon_type{name, pos}; }

			// find:

				nik_ce bool found(size_ctype n) const
					{ return (n != page_cmethod.size()); }

				template<typename T, auto N>
				nik_ce auto find(const T (&field)[N]) const
				{
					auto in = page_cmethod.cbegin();

					while (in != page_cmethod.cend())
					{
						auto text_csubmethod = text_csubequip(*in);

						bool same{true};
						for (size_type k = 0; same && (k != N); ++k)
							{ same = (text_csubmethod[k] == field[k]); }

						if (same) { break; } else { ++in; }
					}

					return in;
				}

				template<typename T, auto N>
				nik_ce size_type left_find(const T (&field)[N]) const
					{ return find(field) - page_cmethod.cbegin(); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class signified_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		protected:

			nik_ce bool facade_overlay() { return facade::overlay(base::name, base::dimension); }

		public:

			nik_ce signified_method_disjoint() : base{} { }
			nik_ce signified_method_disjoint(const facade & f) : base{f} { }

			// text:

				 // unsafe, does not test against name().

				nik_ce auto text_subequip(size_ctype n)
					{ return base::model->text_subequip(n); }

				nik_ce auto page_to_text_equip(size_ctype n)
					{ return text_subequip(base::page_cmethod[n]); }

				nik_ce auto icon_to_text_equip(icon_ctype_ref i)
					{ return page_to_text_equip(i.index()); }

			// overlay:

				nik_ce auto overlay()
				{
					if (not facade_overlay()) return base::fail_icon();

					return base::make_icon(base::page_cmethod.max());
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// builtin:

/***********************************************************************************************************************/

// names:

	struct SignifiedBuiltin
	{
		enum : gkey_type
		{
			start, bytes,
			dimension
		};
	};

	using DBuiltin = SignifiedBuiltin;

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class signified_builtin_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using icon_type			= icon<size_type>;
			using icon_ctype_ref		= typename alias<icon_type>::ctype_ref;

		public:

			nik_ce signified_builtin_cmethod_disjoint() : base{} { }
			nik_ce signified_builtin_cmethod_disjoint(const facade & f) : base{f} { }

			// find:

				nik_ce size_type left_find(size_ctype start) const
					{ return base::left_find({start, base::bytes}); }
	};

	// syntactic sugar:

		template<typename Facade, auto Name>
		using dbuiltin_cmethod =
			signified_builtin_cmethod_disjoint <
			signified_cmethod_disjoint         < Facade, Name, DBuiltin::dimension >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class signified_builtin_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		public:

			nik_ce signified_builtin_method_disjoint() : base{} { }
			nik_ce signified_builtin_method_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade, auto Name>
		using dbuiltin_method =
			signified_builtin_method_disjoint  <
			signified_builtin_cmethod_disjoint <
			signified_method_disjoint          <
			signified_cmethod_disjoint         < Facade, Name, DBuiltin::dimension >>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ring:

/***********************************************************************************************************************/

// names:

	using DRing = DBuiltin;

/***********************************************************************************************************************/

// immutable:

	// syntactic sugar:

		template<typename Facade>
		using dring_cmethod = dbuiltin_cmethod<Facade, Logo::ringN>;

/***********************************************************************************************************************/

// mutable:

	// syntactic sugar:

		template<typename Facade>
		using dring_method = dbuiltin_method<Facade, Logo::ringN>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// flex:

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// utf8 char:

/***********************************************************************************************************************/

// names:

	using DUtf8Char = DBuiltin;

/***********************************************************************************************************************/

// immutable:

	// syntactic sugar:

		template<typename Facade>
		using dutf8_char_cmethod = dbuiltin_cmethod<Facade, Logo::utf8_charN>;

/***********************************************************************************************************************/

// mutable:

	// syntactic sugar:

		template<typename Facade>
		using dutf8_char_method = dbuiltin_method<Facade, Logo::utf8_charN>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cotuple:

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

