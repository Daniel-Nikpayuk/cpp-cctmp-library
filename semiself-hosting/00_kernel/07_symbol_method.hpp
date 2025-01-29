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

// symbol method:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ring:

/***********************************************************************************************************************/

// immutable:

	template<typename Facade>
	class symbol_ring_cmethod : public Facade
	{
		public:

			using base			= Facade;
			using model_type		= typename Facade::model_type;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		protected:

			using glyph_cmethod_type	= typename model_type::glyph_cmethod_type;
			using image_cmethod_type	= typename model_type::image_cmethod_type;

			glyph_cmethod_type glyph_cmethod;
			image_cmethod_type image_cmethod;

		public:

			nik_ce symbol_ring_cmethod() : base{}, glyph_cmethod{}, image_cmethod{} { }
			nik_ce symbol_ring_cmethod(const Facade & f) :

				base{f},
				glyph_cmethod{glyph_cequip()},
				image_cmethod{image_cequip()}
				{ }

			// glyph:

				nik_ce auto glyph_cequip() { return base::model->glyph_cequip(); }

			// image:

				nik_ce auto image_cequip() { return base::model->image_cequip(); }
	};

	// syntactic sugar:

		template<typename Facade>
		using sring_cmethod = symbol_ring_cmethod<Facade>;

/***********************************************************************************************************************/

// mutable:

	template<typename Facade>
	class symbol_ring_method : public symbol_ring_cmethod<Facade>
	{
		public:

			using base			= symbol_ring_cmethod<Facade>;
			using model_type		= typename base::model_type;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using icon_type			= icon<size_type>;
			using icon_ctype_ref		= typename alias<icon_type>::ctype_ref;

			using sign_type			= sign<size_type>;
			using sign_ctype_ref		= typename alias<sign_type>::ctype_ref;

		protected:

			nik_ces size_type goffset	= GRing::dimension;

			using glyph_method_type		= typename model_type::glyph_method_type;
			using image_method_type		= typename model_type::image_method_type;

			glyph_method_type glyph_method;
			image_method_type image_method;

		protected:

			// glyph:

				nik_ce void initialize_glyph(icon_ctype_ref icon, size_ctype bytes)
				{
					auto glyph_submethod = glyph_method.icon_to_text_equip(icon);

						// name is redundant, bits is now bytes.
						// each types specifies to which universe it belongs.
						// has free (glyph).
					glyph_submethod[GRing::name ] = Gram::ringN;
					glyph_submethod[GRing::bytes] = bytes;
				}

				nik_ce auto instantiate_glyph(size_ctype bytes)
				{
					auto icon = glyph_method.overlay();

					if (icon.not_fail()) { initialize_glyph(icon, bytes); }

					return icon;
				}

				nik_ce auto declare_glyph(size_ctype bytes)
				{
					size_ctype pos = glyph_method.left_find(bytes);

					if (glyph_method.found(pos)) { return glyph_method.make_icon(pos); }
					else                         { return instantiate_glyph(bytes); }
				}

			// image:

				nik_ce void initialize_image(sign_ctype_ref sign, size_ctype start)
				{
					auto image_submethod = image_method.sign_to_text_equip(sign);

						// have "abstract" and "concrete" as fields.

						// bytes is now moved to type info.
						// type_pos (rindex?).
						// bound: is_symbolic, start.
						// has free (image) (index?).

					image_submethod[IRing::start] = start;
					image_submethod[IRing::bytes] = image_method.byte_size();
				}

				nik_ce auto instantiate_image(size_ctype start)
				{
					auto sign = image_method.overlay();

					if (sign.not_fail()) { initialize_image(sign, start); }

					return sign;
				}

				nik_ce auto declare_image(size_ctype start)
				{
					size_ctype pos = image_method.left_find(start);

					if (image_method.found(pos)) { return image_method.fail_sign(); }
					else                         { return instantiate_image(start); }
				}

		public:

			nik_ce symbol_ring_method() : base{}, glyph_method{}, image_method{} { }
			nik_ce symbol_ring_method(const Facade & f) :

				base{f},
				glyph_method{glyph_equip()},
				image_method{image_equip()}
				{ }

			// glyph:

				nik_ce auto glyph_equip() { return base::model->glyph_equip(); }

			// image:

				nik_ce auto image_equip() { return base::model->image_equip(); }

			// initialization:

				nik_ce auto declare(size_ctype bits, size_ctype offset)
				{
					auto icon = declare_glyph(bits);
					auto sign = declare_image(offset);
					auto kind = (icon.not_fail() && sign.not_fail()) ? Gram::ringN : Gram::fail;

					return sign;
				}

			// same types:

				template<typename T, typename... Ts>
				nik_ce bool same_types(const T & l, const Ts &... rs)
					{ return glyph_method.same_types(goffset, l.index(), rs.index()...); }
	};

	// syntactic sugar:

		template<typename Facade>
		using sring_method = symbol_ring_method<Facade>;

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

