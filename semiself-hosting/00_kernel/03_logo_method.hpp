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

// logo method:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// logo:

	// should an enum type be added?

/***********************************************************************************************************************/

// names:

	struct LogoName
	{
		enum : gkey_type
		{
			ring, flex, tuple, cotuple, function, null, list, identity, exists, forall, custom,

			dimension, fail // fail is symbolic only.
		};
	};

/***********************************************************************************************************************/

// gram:

	template<typename SizeType>
	class logo_gram
	{
		public:

			using size_type		= typename alias<SizeType>::type;
			using size_ctype	= typename alias<SizeType>::ctype;

		protected:

			size_type name;
			size_type index;

		public:

			nik_ce logo_gram() : name{}, index{} { }
			nik_ce logo_gram(size_ctype n, size_ctype i) : name{n}, index{i} { }

			// name:

				nik_ce size_type get_name() const { return name; }
				nik_ce void set_name(size_ctype n) { name = n; }

			// index:

				nik_ce size_type get_index() const { return index; }
				nik_ce void set_index(size_ctype i) { index = i; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ring:

/***********************************************************************************************************************/

// names:

	struct LogoRing
	{
		enum : gkey_type
		{
			name, bits,
			dimension
		};
	};

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

			using gram_type			= logo_gram<size_type>;
			using gram_ctype_ref		= typename alias<gram_type>::ctype_ref;

		protected:

			nik_ce bool overlay_base() { return base::overlay(LogoName::ring, LogoRing::dimension); }

			nik_ce auto initialize_base()
				{ return base::initialize_last(LogoName::ring, LogoRing::name); }

			nik_ce auto fail_gram() const { return gram_type{LogoName::fail, 0}; }
			nik_ce auto ring_gram(size_ctype pos) const { return gram_type{LogoName::ring, pos}; }

		public:

			nik_ce logo_ring_method() : base{} { }
			nik_ce logo_ring_method(const Facade & f) : base{f} { }

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
						auto page_cmethod = base::cpage_equip(LogoName::ring);

						return base::text_right_equip(page_cmethod[g.get_index()]);
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

