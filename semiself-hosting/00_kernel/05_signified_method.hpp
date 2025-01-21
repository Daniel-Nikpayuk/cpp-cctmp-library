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

// ring:

/***********************************************************************************************************************/

// names:

	struct SignifiedRing
	{
		enum : gkey_type
		{
			start, bytes,
			dimension
		};
	};

	using DRing = SignifiedRing;

/***********************************************************************************************************************/

// immutable:

	template<typename Facade>
	class signified_ring_cmethod : public Facade
	{
		public:

			using base			= Facade;
			using model_type		= typename Facade::model_type;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using icon_type			= icon<size_type>;
			using icon_ctype_ref		= typename alias<icon_type>::ctype_ref;

		protected:

			nik_ces size_type bytes		= 1;

			using page_cmethod_type		= typename model_type::page_cmethod_type;
			using text_cmethod_type		= typename model_type::text_cmethod_type;

			page_cmethod_type page_cmethod;
			text_cmethod_type text_cmethod;

		public:

			nik_ce signified_ring_cmethod() : base{}, page_cmethod{}, text_cmethod{} { }

			nik_ce signified_ring_cmethod(const Facade & f) :

				base{f},
				page_cmethod{page_cequip(Logo::ringN)},
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
				nik_ce auto ring_icon(size_ctype pos) const { return icon_type{Logo::ringN, pos}; }

			// find:

				nik_ce bool found(size_ctype n) const
					{ return (n != page_cmethod.size()); }

				nik_ce auto find(size_ctype start) const
				{
					auto in = page_cmethod.cbegin();

					while (in != page_cmethod.cend())
					{
						auto text_csubmethod = text_csubequip(*in);

						bool same_start = (text_csubmethod[DRing::start] == start);
						bool same_bytes = (text_csubmethod[DRing::bytes] == bytes);

							// refactor through variadic same ?
						if (same_start && same_bytes) { break; } else { ++in; }
					}

					return in;
				}

				nik_ce size_type left_find(size_ctype start) const
					{ return find(start) - page_cmethod.cbegin(); }
	};

	// syntactic sugar:

		template<typename Facade>
		using dring_cmethod = signified_ring_cmethod<Facade>;

/***********************************************************************************************************************/

// mutable:

	template<typename Facade>
	class signified_ring_method : public signified_ring_cmethod<Facade>
	{
		public:

			using base			= signified_ring_cmethod<Facade>;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		protected:

			nik_ce bool overlay_base() { return base::overlay(Logo::ringN, DRing::dimension); }

		public:

			nik_ce signified_ring_method() : base{} { }
			nik_ce signified_ring_method(const Facade & f) : base{f} { }

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
					if (not overlay_base()) return base::fail_icon();

					return base::ring_icon(base::page_cmethod.max());
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using dring_method = signified_ring_method<Facade>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// flex:

/***********************************************************************************************************************/

// :

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

