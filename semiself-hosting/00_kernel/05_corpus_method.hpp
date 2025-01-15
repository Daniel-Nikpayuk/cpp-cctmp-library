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

// corpus method:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// logo:

/***********************************************************************************************************************/

// names:

	struct LogoName
	{
		enum : gkey_type
		{
			ring, flex, tuple, cotuple, function, null, list, identity, exists, forall, custom,
			dimension
		};
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ring:

/***********************************************************************************************************************/

// immutable:

	template<typename Facade>
	class logo_ring_cmethod : public Facade
	{
		public:

			using base			= Facade;

		//	using type			= typename base::type;
		//	using type_ptr			= typename base::type_ptr;
		//	using type_cptr			= typename base::type_cptr;
		//	using type_ref			= typename base::type_ref;

		//	using ctype			= typename base::ctype;
		//	using ctype_ptr			= typename base::ctype_ptr;
		//	using ctype_cptr		= typename base::ctype_cptr;
		//	using ctype_ref			= typename base::ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		protected:

		//	using page_cmethod		= typename base::above_cmethod;
		//	using text_cmethod		= typename base::below_cmethod;

		public:

			nik_ce logo_ring_cmethod() : base{} { }
			nik_ce logo_ring_cmethod(const Facade & f) : base{f} { }

			// :

			// :

			//	nik_ce size_type max() const { return base::size() - 1; }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Facade>
	class logo_ring_method : public logo_ring_cmethod<Facade>
	{
		public:

			using base			= logo_ring_cmethod<Facade>;

		//	using type			= typename base::type;
		//	using type_ptr			= typename base::type_ptr;
		//	using type_cptr			= typename base::type_cptr;
		//	using type_ref			= typename base::type_ref;

		//	using ctype			= typename base::ctype;
		//	using ctype_ptr			= typename base::ctype_ptr;
		//	using ctype_cptr		= typename base::ctype_cptr;
		//	using ctype_ref			= typename base::ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		protected:

		//	using page_cmethod		= typename base::page_cmethod;
		//	using page_method		= typename base::base::above_method;

		//	using text_cmethod		= typename base::text_cmethod;
		//	using text_method		= typename base::base::below_cmethod;

		public:

			nik_ce logo_ring_method() : base{} { }
			nik_ce logo_ring_method(const Facade & f) : base{f} { }

			// :

			// overlay:

				// overlay is just the overlay.
				// add in methods for setting the "field" values.

				nik_ce size_type overlay(size_ctype bits)
				{
					base::overlay(LogoName::ring);

					// text is_full ?

					// specifically make a subarray method (adjusts for size) ?

					auto offset = base::text().size();
					auto text_m = base::text().iter(offset);

					base::text().upsize(3);

					text_m[0] = LogoName::ring;
					text_m[1] = bits;

					return offset;
				}
	};

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

