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

// signifier method:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ring:

/***********************************************************************************************************************/

// names:

	struct SignifierRing
	{
		enum : gkey_type
		{
			name, bits,
			dimension
		};
	};

	using RRing = SignifierRing;

/***********************************************************************************************************************/

// immutable:

	template<typename Facade>
	class signifier_ring_cmethod : public Facade
	{
		public:

			using base			= Facade;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using gram_type			= gram<size_type>;
			using gram_ctype_ref		= typename alias<gram_type>::ctype_ref;

		public:

			nik_ce signifier_ring_cmethod() : base{} { }
			nik_ce signifier_ring_cmethod(const Facade & f) : base{f} { }

			// text:

				 // unsafe, does not test against name().

				nik_ce auto ctext_right_equip(gram_ctype_ref g)
				{
					auto page_cmethod = base::cpage_equip(Logo::ring);

					return base::ctext_right_equip(page_cmethod[g.get_index()]);
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using rring_cmethod = signifier_ring_cmethod<Facade>;

/***********************************************************************************************************************/

// mutable:

	template<typename Facade>
	class signifier_ring_method : public signifier_ring_cmethod<Facade>
	{
		public:

			using base			= signifier_ring_cmethod<Facade>;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using gram_type			= typename base::gram_type;
			using gram_ctype_ref		= typename base::gram_ctype_ref;

		protected:

			nik_ce bool overlay_base() { return base::overlay(Logo::ring, RRing::dimension); }

			nik_ce auto initialize_base()
				{ return base::initialize_last(Logo::ring, RRing::name, Logo::ring); }

			nik_ce auto fail_gram() const { return gram_type{Logo::fail, 0}; }
			nik_ce auto ring_gram(size_ctype pos) const { return gram_type{Logo::ring, pos}; }

		public:

			nik_ce signifier_ring_method() : base{} { }
			nik_ce signifier_ring_method(const Facade & f) : base{f} { }

			// mutable:

				nik_ce auto initialize()
				{
					if (not overlay_base()) return fail_gram();

					return ring_gram(initialize_base());
				}

				// text:

					 // unsafe, does not test against name().

					nik_ce auto text_right_equip(gram_ctype_ref g)
					{
						auto page_cmethod = base::cpage_equip(Logo::ring);

						return base::text_right_equip(page_cmethod[g.get_index()]);
					}
	};

	// syntactic sugar:

		template<typename Facade>
		using rring_method = signifier_ring_method<Facade>;

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

