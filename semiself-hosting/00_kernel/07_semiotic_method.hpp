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

// semiotic method:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ring:

/***********************************************************************************************************************/

// immutable:

	template<typename Facade>
	class semiotic_ring_cmethod : public Facade
	{
		public:

			using base			= Facade;
			using model_type		= typename Facade::model_type;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		protected:

			using signifier_cmethod_type	= typename model_type::signifier_cmethod_type;
			using signified_cmethod_type	= typename model_type::signified_cmethod_type;

			signifier_cmethod_type signifier_cmethod;
			signified_cmethod_type signified_cmethod;

		public:

			nik_ce semiotic_ring_cmethod() : base{}, signifier_cmethod{}, signified_cmethod{} { }
			nik_ce semiotic_ring_cmethod(const Facade & f) :

				base{f},
				signifier_cmethod{signifier_cequip()},
				signified_cmethod{signified_cequip()}
				{ }

			// signifier:

				nik_ce auto signifier_cequip() { return base::model->signifier_cequip(); }

			// signified:

				nik_ce auto signified_cequip() { return base::model->signified_cequip(); }
	};

	// syntactic sugar:

		template<typename Facade>
		using sring_cmethod = semiotic_ring_cmethod<Facade>;

/***********************************************************************************************************************/

// mutable:

	template<typename Facade>
	class semiotic_ring_method : public semiotic_ring_cmethod<Facade>
	{
		public:

			using base			= semiotic_ring_cmethod<Facade>;
			using model_type		= typename base::model_type;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using sign_type			= sign<size_type>;
			using sign_ctype_ref		= typename alias<sign_type>::ctype_ref;

			using gram_type			= typename sign_type::gram_type;
			using gram_ctype_ref		= typename alias<gram_type>::ctype_ref;

			using icon_type			= typename sign_type::icon_type;
			using icon_ctype_ref		= typename alias<icon_type>::ctype_ref;

		protected:

			nik_ces size_type roffset	= RRing::dimension;

			using signifier_method_type	= typename model_type::signifier_method_type;
			using signified_method_type	= typename model_type::signified_method_type;

			signifier_method_type signifier_method;
			signified_method_type signified_method;

		protected:

			// signifier:

				nik_ce void initialize_signifier(gram_ctype_ref gram, size_ctype bits)
				{
					auto signifier_submethod = signifier_method.gram_to_text_equip(gram);

					signifier_submethod[RRing::name] = Logo::ringN;
					signifier_submethod[RRing::bits] = bits;
				}

				nik_ce auto instantiate_signifier(size_ctype bits)
				{
					auto gram = signifier_method.overlay();

					if (gram.not_fail()) { initialize_signifier(gram, bits); }

					return gram;
				}

				nik_ce auto declare_signifier(size_ctype bits)
				{
					size_ctype pos = signifier_method.left_find(bits);

					if (signifier_method.found(pos)) { return signifier_method.ring_gram(pos); }
					else                             { return instantiate_signifier(bits); }
				}

			// signified:

				nik_ce void initialize_signified(icon_ctype_ref icon, size_ctype start)
				{
					auto signified_submethod = signified_method.icon_to_text_equip(icon);

					signified_submethod[DRing::start] = start;
					signified_submethod[DRing::bytes] = signified_method.byte_size();
				}

				nik_ce auto instantiate_signified(size_ctype start)
				{
					auto icon = signified_method.overlay();

					if (icon.not_fail()) { initialize_signified(icon, start); }

					return icon;
				}

				nik_ce auto declare_signified(size_ctype start)
				{
					size_ctype pos = signified_method.left_find(start);

					if (signified_method.found(pos)) { return signified_method.fail_icon(); }
					else                             { return instantiate_signified(start); }
				}

		public:

			nik_ce semiotic_ring_method() : base{}, signifier_method{}, signified_method{} { }
			nik_ce semiotic_ring_method(const Facade & f) :

				base{f},
				signifier_method{signifier_equip()},
				signified_method{signified_equip()}
				{ }

			// signifier:

				nik_ce auto signifier_equip() { return base::model->signifier_equip(); }

			// signified:

				nik_ce auto signified_equip() { return base::model->signified_equip(); }

			// initialization:

				nik_ce auto declare(size_ctype bits, size_ctype offset)
				{
					auto gram = declare_signifier(bits);
					auto icon = declare_signified(offset);
					auto kind = (gram.not_fail() && icon.not_fail()) ? Logo::ringN : Logo::fail;

					return sign_type{kind, gram.index(), icon.index()};
				}

			// same types:

				template<typename T, typename... Ts>
				nik_ce bool same_types(const T & l, const Ts &... rs)
					{ return signifier_method.same_types(roffset, l.rindex(), rs.rindex()...); }
	};

	// syntactic sugar:

		template<typename Facade>
		using sring_method = semiotic_ring_method<Facade>;

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

