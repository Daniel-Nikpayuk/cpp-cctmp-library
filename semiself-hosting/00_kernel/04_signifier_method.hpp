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
			using model_type		= typename Facade::model_type;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using gram_type			= gram<size_type>;
			using gram_ctype_ref		= typename alias<gram_type>::ctype_ref;

		protected:

			using pcmethod_type		= typename model_type::pcmethod_type;
			using tcmethod_type		= typename model_type::tcmethod_type;

			pcmethod_type pcmethod;
			tcmethod_type tcmethod;

		public:

			nik_ce signifier_ring_cmethod() : base{}, pcmethod{}, tcmethod{} { }
			nik_ce signifier_ring_cmethod(const Facade & f) :

				base{f},
				pcmethod{cpage_equip(Logo::ring)},
				tcmethod{ctext_equip()}
				{ }

			// page:

				nik_ce auto cpage_equip(size_ctype n) const
					{ return base::model->cpage_equip(n); }

			// text:

				nik_ce auto ctext_equip() const { return base::model->ctext_equip(); }

					// unsafe, does not test against name().

				nik_ce auto ctext_right_equip(size_ctype n) const
					{ return base::model->ctext_right_equip(n); }

				nik_ce auto page_to_ctext_equip(size_ctype n) const
					{ return ctext_right_equip(pcmethod[n]); }

				nik_ce auto gram_to_ctext_equip(gram_ctype_ref g) const
					{ return page_to_ctext_equip(g.index()); }

			// gram:

				nik_ce auto fail_gram() const { return gram_type{Logo::fail, 0}; }
				nik_ce auto ring_gram(size_ctype pos) const { return gram_type{Logo::ring, pos}; }

			// find:

				nik_ce bool found(size_ctype n) const
					{ return (n != pcmethod.size()); }

				nik_ce auto find(size_ctype bits) const
				{
					auto in = pcmethod.cbegin();

					while (in != pcmethod.cend())
					{
						auto sub_tcmethod = base::model->ctext_right_equip(*in);

						bool same_name = (sub_tcmethod[RRing::name] == Logo::ring);
						bool same_bits = (sub_tcmethod[RRing::bits] == bits);

							// refactor through variadic same ?
						if (same_name && same_bits) { break; } else { ++in; }
					}

					return in;
				}

				nik_ce size_type left_find(size_ctype bits) const
					{ return find(bits) - pcmethod.cbegin(); }

			// same:

				template<typename T, typename... Ts>
				nik_ce bool same_types(size_ctype n, const T l, const Ts... rs) const
					{ return same_methods(n, page_to_ctext_equip(l), page_to_ctext_equip(rs)...); }

				template<typename T, typename... Ts>
				nik_ce bool same_methods(size_ctype n, const T & l, const Ts &... rs) const
				{
					for (size_type k = 0; k != n; ++k)
						{ if (different_values(l[k], rs[k]...)) return false; }

					return true;
				}

				template<typename T, typename... Ts>
				nik_ce bool different_values(const T l, const Ts... rs) const
					{ return (... || (l != rs)); }
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
			using model_type		= typename base::model_type;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using gram_type			= typename base::gram_type;
			using gram_ctype_ref		= typename base::gram_ctype_ref;

		protected:

			nik_ce bool overlay_base() { return base::overlay(Logo::ring, RRing::dimension); }

		public:

			nik_ce signifier_ring_method() : base{} { }
			nik_ce signifier_ring_method(const Facade & f) : base{f} { }

			// text:

				 // unsafe, does not test against name().

				nik_ce auto text_right_equip(size_ctype n)
					{ return base::model->text_right_equip(n); }

				nik_ce auto page_to_text_equip(size_ctype n)
					{ return text_right_equip(base::pcmethod[n]); }

				nik_ce auto gram_to_text_equip(gram_ctype_ref g)
					{ return page_to_text_equip(g.index()); }

			// overlay:

				nik_ce auto overlay()
				{
					if (not overlay_base()) return base::fail_gram();

					return base::ring_gram(base::pcmethod.max());
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

