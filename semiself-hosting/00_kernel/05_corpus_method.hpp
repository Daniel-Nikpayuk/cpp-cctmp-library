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

// method:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class corpus_cmethod_disjoint : public Base
	{
		public:

			using base				= Base;
			using facade				= typename base::facade;
			using model_type			= typename base::model_type;

			nik_using_size_type_scope		(base)

			using icon_type				= icon<size_type>;
			using icon_ctype_ref			= typename alias<icon_type>::ctype_ref;

			using sign_type				= sign<size_type>;
			using sign_ctype_ref			= typename alias<sign_type>::ctype_ref;

		protected:

			using glyph_cmethod_type		= typename model_type::template
									glyph_cmethod_type<glyph_cmethod>;
			using image_cmethod_type		= typename model_type::template
									image_cmethod_type<image_cmethod>;

			glyph_cmethod_type _glyph_cmethod;
			image_cmethod_type _image_cmethod;

		public:

			nik_ce corpus_cmethod_disjoint() : base{} { }
			nik_ce corpus_cmethod_disjoint(const facade & f) :
				base{f},
				_glyph_cmethod{base::model->template glyph_cequip<glyph_cmethod_type>()},
				_image_cmethod{base::model->template image_cequip<image_cmethod_type>()}
				{ }

			// glyph:

				nik_ce auto glyph_cmethod() const { return _glyph_cmethod; }

				nik_ce auto to_icon(sign_ctype_ref sign) const
					{ return icon_type{sign.mark(), image_ctext(sign).cat(ImageBase::index)}; }

			// (glyph) icon:

				nik_ce auto glyph_make_icon(size_type n, size_ctype m) const
					{ return _glyph_cmethod.make_icon(n, m); }

			// (glyph) fail:

				nik_ce bool glyph_is_fail(icon_ctype_ref icon) const
					{ return _glyph_cmethod.is_fail(icon); }

				nik_ce bool glyph_is_fail(sign_ctype_ref sign) const
					{ return _glyph_cmethod.is_fail(to_icon(sign)); }

				nik_ce bool glyph_not_fail(icon_ctype_ref icon) const
					{ return _glyph_cmethod.not_fail(icon); }

				nik_ce bool glyph_not_fail(sign_ctype_ref sign) const
					{ return _glyph_cmethod.not_fail(to_icon(sign)); }

				nik_ce auto glyph_fail_icon()
					{ return _glyph_cmethod.fail_icon(); }

			// (glyph) text:

				nik_ce auto glyph_ctext(icon_ctype_ref icon) const
					{ return _glyph_cmethod.text_csubmethod(icon); }

				nik_ce auto glyph_ctext(sign_ctype_ref sign) const
					{ return glyph_ctext(to_icon(sign)); }

			// (glyph) field:

				nik_ce size_type glyph_cfield(icon_ctype_ref icon, size_ctype row, size_ctype col) const
					{ return _glyph_cmethod.text_cfield(icon, row, col); }

				nik_ce size_type glyph_cfield(sign_ctype_ref sign, size_ctype row, size_ctype col) const
					{ return glyph_cfield(to_icon(sign), row, col); }

			// (glyph) compare:

				nik_ce bool glyph_is_instr(icon_ctype_ref icon, size_ctype instr) const
					{ return _glyph_cmethod.is_instr(icon, instr); }

				nik_ce bool glyph_is_instr(sign_ctype_ref sign, size_ctype instr) const
					{ return glyph_is_instr(to_icon(sign), instr); }

				nik_ce bool glyph_is_custom(icon_ctype_ref icon) const
					{ return _glyph_cmethod.is_custom(icon); }

				nik_ce bool glyph_is_custom(sign_ctype_ref sign) const
					{ return glyph_is_custom(to_icon(sign)); }

				nik_ce bool glyph_equal(icon_ctype_ref icon1, icon_ctype_ref icon2) const
					{ return _glyph_cmethod.equal(icon1, icon2); }

				nik_ce bool glyph_equal(sign_ctype_ref sign1, sign_ctype_ref sign2) const
					{ return glyph_equal(to_icon(sign1), to_icon(sign2)); }

			// (glyph) sub(ordinate) icon:

				nik_ce auto glyph_sub_icon(icon_ctype_ref icon, size_ctype row) const
					{ return _glyph_cmethod.sub_icon(icon, row); }

				nik_ce auto glyph_sub_icon(sign_ctype_ref sign, size_ctype row) const
					{ return glyph_sub_icon(to_icon(sign), row); }

			// (glyph) find:

				nik_ce bool glyph_found(size_ctype mark, size_ctype n) const
					{ return _glyph_cmethod.found(mark, n); }

				template<typename T>
				nik_ce size_type glyph_find(size_ctype mark, const T & v) const
					{ return _glyph_cmethod.find(mark, v); }

			// (glyph) total:

				template<typename T>
				nik_ce size_type glyph_total_bytes(const T & v) const
					{ return _glyph_cmethod.total_bytes(v); }

			// (glyph) max:

				template<typename T>
				nik_ce size_type glyph_max_bytes(const T & v) const
					{ return _glyph_cmethod.max_bytes(v); }

				template<typename T>
				nik_ce size_type glyph_max_universe(const T & v) const
					{ return _glyph_cmethod.max_universe(v); }

			// image:	

				nik_ce auto image_cmethod() const { return _image_cmethod; }

			// (image) sign:

				nik_ce auto image_make_sign(size_type n, size_ctype m) const
					{ return _image_cmethod.make_sign(n, m); }

			// (image) fail:

				nik_ce bool image_is_fail(sign_ctype_ref sign) const
					{ return _image_cmethod.is_fail(sign); }

				nik_ce bool image_not_fail(sign_ctype_ref sign) const
					{ return _image_cmethod.not_fail(sign); }

				nik_ce auto image_fail_sign()
					{ return _image_cmethod.fail_sign(); }

			// (image) text:

				nik_ce auto image_ctext(sign_ctype_ref sign) const
					{ return _image_cmethod.text_csubmethod(sign); }

			// (image) field:

				nik_ce auto image_cfield(sign_ctype_ref sign, size_ctype n) const
					{ return _image_cmethod.text_cfield(sign, n); }

			// (image) compare:

				nik_ce bool image_equal(sign_ctype_ref sign1, sign_ctype_ref sign2) const
					{ return _image_cmethod.equal(sign1, sign2); }
	};

	// syntactic sugar:

		template<typename Facade>
		using corpus_cmethod =
			corpus_cmethod_disjoint < Facade >;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class corpus_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		protected:

			using glyph_method_type		= typename model_type::template
								glyph_method_type<glyph_method>;
			using image_method_type		= typename model_type::template
								image_method_type<image_method>;

			glyph_method_type _glyph_method;
			image_method_type _image_method;

		public:

			nik_ce corpus_method_disjoint() : base{} { }
			nik_ce corpus_method_disjoint(const facade & f) :
				base{f},
				_glyph_method{base::model->template glyph_equip<glyph_method_type>()},
				_image_method{base::model->template image_equip<image_method_type>()}
				{ }

			// glyph:

				nik_ce auto glyph_method() { return _glyph_method; }

			// (glyph) text:

				nik_ce auto glyph_text(icon_ctype_ref icon)
					{ return _glyph_method.text_submethod(icon); }

				nik_ce auto glyph_text(sign_ctype_ref sign)
					{ return glyph_text(base::to_icon(sign)); }

			// (glyph) field:

				nik_ce void glyph_set_field(icon_ctype_ref icon,
					size_ctype row, size_ctype col, size_ctype v)
						{ _glyph_method.set_field(icon, row, col, v); }

				nik_ce void glyph_set_field(sign_ctype_ref sign,
					size_ctype row, size_ctype col, size_ctype v)
						{ glyph_set_field(base::to_icon(sign), row, col, v); }

			// (glyph) instr:

				template<typename T>
				nik_ce void glyph_set_program(T & table,
					size_ctype lines, size_ctype code = GlyphCode::valid)
						{ _glyph_method.set_program(table, lines, code); }

				template<typename T>
				nik_ce void glyph_set_routine(T & table,
					size_ctype instr, size_ctype arity = 0, size_ctype local = 0)
						{ _glyph_method.set_routine(table, instr, arity, local); }

				template<typename T>
				nik_ce void glyph_set_meta(T & table,
					size_ctype bytes, size_ctype universe = 0)
						{ _glyph_method.set_meta(table, bytes, universe); }

				template<typename T>
				nik_ce void glyph_set_note(T & table,
					size_ctype row, size_ctype mark, size_ctype index)
						{ _glyph_method.set_note(table, row, mark, index); }

			// (glyph) declare:

				template<typename T>
				nik_ce auto glyph_declare(size_ctype mark, const T & field)
					{ return _glyph_method.declare(mark, field); }

			// image:

				nik_ce auto image_method() { return _image_method; }

			// (image) text:

				nik_ce auto image_text(sign_ctype_ref sign)
					{ return _image_method.text_submethod(sign); }

			// (image) declare:

				template<typename T>
				nik_ce auto image_declare(size_ctype mark, const T & field)
					{ return _image_method.declare(mark, field); }
	};

	// syntactic sugar:

		template<typename Facade>
		using corpus_method =
			corpus_method_disjoint  <
			corpus_cmethod_disjoint < Facade >>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

