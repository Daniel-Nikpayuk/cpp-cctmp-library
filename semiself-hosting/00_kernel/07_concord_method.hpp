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

// concord method:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// method:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class concord_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= icon<size_type>;
			using icon_ctype_ref		= typename alias<icon_type>::ctype_ref;

			using mode_type			= mode<size_type>;
			using mode_ctype_ref		= typename alias<mode_type>::ctype_ref;

			using sign_type			= sign<size_type>;
			using sign_ctype		= typename alias<sign_type>::ctype;
			using sign_ctype_ref		= typename alias<sign_type>::ctype_ref;

		protected:

			using symbol_cmethod_type	= typename model_type::template
								symbol_cmethod_type<corpus_cmethod>;
			using record_csubmethod_type	= typename model_type::template
								record_csubmethod_type<array_csubmethod>;

			symbol_cmethod_type _symbol_cmethod;

		protected:

			nik_ces size_type row_program	= symbol_cmethod_type::row_program;
			nik_ces size_type row_routine	= symbol_cmethod_type::row_routine;
			nik_ces size_type row_meta	= symbol_cmethod_type::row_meta;
			nik_ces size_type row_body	= symbol_cmethod_type::row_body;

			nik_ces size_type col_length	= symbol_cmethod_type::col_length;

		public:

			nik_ce concord_cmethod_disjoint() : base{} { }
			nik_ce concord_cmethod_disjoint(const facade & f) :
				base{f},
				_symbol_cmethod{base::model->template symbol_cequip<symbol_cmethod_type>()}
				{ }

			// symbol:

				nik_ce auto symbol_cmethod() const { return _symbol_cmethod; }

				nik_ce auto to_icon(mode_ctype_ref mode) const
					{ return icon_type{mode.mark(), mode.index()}; }

				nik_ce auto to_icon(sign_ctype_ref sign) const
					{ return _symbol_cmethod.to_icon(sign); }

			// (glyph) icon:

				nik_ce auto glyph_make_icon(size_type n, size_ctype m) const
					{ return _symbol_cmethod.glyph_make_icon(n, m); }

			// (glyph) fail:

				nik_ce bool glyph_is_fail(icon_ctype_ref icon) const
					{ return _symbol_cmethod.glyph_is_fail(icon); }

				nik_ce bool glyph_is_fail(sign_ctype_ref sign) const
					{ return _symbol_cmethod.glyph_is_fail(to_icon(sign)); }

				nik_ce bool glyph_not_fail(icon_ctype_ref icon) const
					{ return _symbol_cmethod.glyph_not_fail(icon); }

				nik_ce bool glyph_not_fail(sign_ctype_ref sign) const
					{ return _symbol_cmethod.glyph_not_fail(to_icon(sign)); }

				nik_ce auto glyph_fail_icon()
					{ return _symbol_cmethod.glyph_fail_icon(); }

			// (glyph) text:

				nik_ce auto glyph_ctext(icon_ctype_ref icon) const
					{ return _symbol_cmethod.glyph_ctext(icon); }

				nik_ce auto glyph_ctext(sign_ctype_ref sign) const
					{ return glyph_ctext(to_icon(sign)); }

			// (glyph) field:

				nik_ce size_type glyph_cfield(icon_ctype_ref icon, size_ctype row, size_ctype col) const
					{ return _symbol_cmethod.glyph_cfield(icon, row, col); }

				nik_ce size_type glyph_cfield(sign_ctype_ref sign, size_ctype row, size_ctype col) const
					{ return glyph_cfield(to_icon(sign), row, col); }

			// (glyph) compare:

				nik_ce bool glyph_is_instr(icon_ctype_ref icon, size_ctype instr) const
					{ return _symbol_cmethod.glyph_is_instr(icon, instr); }

				nik_ce bool glyph_is_instr(sign_ctype_ref sign, size_ctype instr) const
					{ return glyph_is_instr(to_icon(sign), instr); }

				nik_ce bool glyph_is_custom(icon_ctype_ref icon) const
					{ return _symbol_cmethod.glyph_is_custom(icon); }

				nik_ce bool glyph_is_custom(sign_ctype_ref sign) const
					{ return glyph_is_custom(to_icon(sign)); }

				nik_ce bool glyph_equal(icon_ctype_ref icon1, icon_ctype_ref icon2) const
					{ return _symbol_cmethod.glyph_equal(icon1, icon2); }

				nik_ce bool glyph_equal(sign_ctype_ref sign1, sign_ctype_ref sign2) const
					{ return glyph_equal(to_icon(sign1), to_icon(sign2)); }

			// (glyph) sub(ordinate) icon:

				nik_ce auto glyph_sub_icon(icon_ctype_ref icon, size_ctype row) const
					{ return _symbol_cmethod.glyph_sub_icon(icon, row); }

				nik_ce auto glyph_sub_icon(sign_ctype_ref sign, size_ctype row) const
					{ return glyph_sub_icon(to_icon(sign), row); }

			// (glyph) find:

				nik_ce bool glyph_found(size_ctype mark, size_ctype n) const
					{ return _symbol_cmethod.glyph_found(mark, n); }

				template<typename T>
				nik_ce size_type glyph_find(size_ctype mark, const T & v) const
					{ return _symbol_cmethod.glyph_find(mark, v); }

			// (glyph) total:

				template<typename T>
				nik_ce size_type glyph_total_bytes(const T & v) const
					{ return _symbol_cmethod.glyph_total_bytes(v); }

			// (glyph) max:

				template<typename T>
				nik_ce size_type glyph_max_bytes(const T & v) const
					{ return _symbol_cmethod.glyph_max_bytes(v); }

				template<typename T>
				nik_ce size_type glyph_max_universe(const T & v) const
					{ return _symbol_cmethod.glyph_max_universe(v); }

			// image:	

				// nothing here.

			// (image) sign:

				nik_ce auto image_make_sign(size_type n, size_ctype m) const
					{ return _symbol_cmethod.image_make_sign(n, m); }

			// (image) fail:

				nik_ce bool image_is_fail(sign_ctype_ref sign) const
					{ return _symbol_cmethod.image_is_fail(sign); }

				nik_ce bool image_not_fail(sign_ctype_ref sign) const
					{ return _symbol_cmethod.image_not_fail(sign); }

				nik_ce auto image_fail_sign()
					{ return _symbol_cmethod.image_fail_sign(); }

			// (image) text:

				nik_ce auto image_ctext(sign_ctype_ref sign) const
					{ return _symbol_cmethod.image_ctext(sign); }

			// (image) field:

				nik_ce auto image_cfield(sign_ctype_ref sign, size_ctype n) const
					{ return _symbol_cmethod.image_cfield(sign, n); }

			// (image) compare:

				nik_ce bool image_equal(sign_ctype_ref sign1, sign_ctype_ref sign2) const
					{ return _symbol_cmethod.image_equal(sign1, sign2); }

			// (image) total:

				template<typename T>
				nik_ce size_type image_total_units(const T & v) const
					{ return _symbol_cmethod.image_total_units(v); }

			// (image) max:

				template<typename T>
				nik_ce size_type image_max_units(const T & v) const
					{ return _symbol_cmethod.image_max_units(v); }


			// record:

				nik_ce auto record_csubmethod() const
					{ return base::model->template record_csubequip<record_csubmethod_type>(); }

				template<typename T>
				nik_ce auto record_ctext(const T & text_cival, size_ctype point, size_ctype n = 1) const
				{
					size_ctype start  = text_cival[point];
					size_ctype finish = start + n;
					auto record_cival = record_csubmethod();
					record_cival      . mid_set(start, finish);

					return record_cival;
				}

				nik_ce auto record_ctext(sign_ctype_ref sign, size_ctype point, size_ctype n = 1) const
					{ return record_ctext(image_ctext(sign), point, n); }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_cmethod =
			concord_cmethod_disjoint < Facade >;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype		= typename base::sign_ctype;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		protected:

			template<size_type length>
			using glyph_field_type		= array<size_type, size_type, length>;

			template<size_type length>
			using glyph_field_method_type	= resolve_submethod<glyph_field_type<length>, table_submethod>;

			template<size_type length>
			using image_field_type		= array<size_type, size_type, length>;

			// glyph:

				template<size_type length>
				nik_ce auto glyph_make_field()
				{
					auto field = glyph_field_type<length>{};
					field      . fullsize();

					return field;
				}

				template<size_type length>
				nik_ce auto glyph_make_table(
					glyph_field_type<length> & field, size_ctype rows, size_ctype cols)
				{
					using method_type = glyph_field_method_type<length>;
					auto table        = field.template subequip<method_type>();
					table             . full_set();
					table             . set_dimension(rows, cols);

					return table;
				}

			// image:

				template<size_type length>
				nik_ce auto image_make_field()
				{
					auto field = image_field_type<length>{};
					field      . fullsize();

					return field;
				}

		protected:

			using symbol_method_type	= typename model_type::template
								symbol_method_type<corpus_method>;
			using record_submethod_type	= typename model_type::template
								record_submethod_type<array_submethod>;

			symbol_method_type _symbol_method;

		public:

			nik_ce concord_method_disjoint() : base{} { }
			nik_ce concord_method_disjoint(const facade & f) :
				base{f},
				_symbol_method{base::model->template symbol_equip<symbol_method_type>()}
				{ }

			// symbol:

				nik_ce auto symbol_method() { return _symbol_method; }

			// (glyph) text:

				nik_ce auto glyph_text(icon_ctype_ref icon)
					{ return _symbol_method.glyph_text(icon); }

				nik_ce auto glyph_text(sign_ctype_ref sign)
					{ return glyph_text(base::to_icon(sign)); }

			// (glyph) field:

				nik_ce void glyph_set_field(icon_ctype_ref icon,
					size_ctype row, size_ctype col, size_ctype v)
						{ _symbol_method.glyph_set_field(icon, row, col, v); }

				nik_ce void glyph_set_field(sign_ctype_ref sign,
					size_ctype row, size_ctype col, size_ctype v)
						{ glyph_set_field(base::to_icon(sign), row, col, v); }

			// (glyph) instr:

				template<typename T>
				nik_ce void glyph_set_program(T & table,
					size_ctype lines, size_ctype code = GlyphCode::valid)
						{ _symbol_method.glyph_set_program(table, lines, code); }

				template<typename T>
				nik_ce void glyph_set_routine(T & table,
					size_ctype instr, size_ctype arity = 0, size_ctype local = 0)
						{ _symbol_method.glyph_set_routine(table, instr, arity, local); }

				template<typename T>
				nik_ce void glyph_set_meta(T & table,
					size_ctype bytes, size_ctype universe = 0)
						{ _symbol_method.glyph_set_meta(table, bytes, universe); }

				template<typename T>
				nik_ce void glyph_set_note(T & table,
					size_ctype row, size_ctype mark, size_ctype index)
						{ _symbol_method.glyph_set_note(table, row, mark, index); }

			// (glyph) declare:

				nik_ce auto glyph_declare_space() { return _symbol_method.glyph_declare_space(); }

				template<typename T>
				nik_ce auto glyph_declare(size_ctype mark, const T & field)
				{
					size_ctype index = base::glyph_find(mark, field);

					if (base::glyph_found(mark, index))
						{ return base::glyph_make_icon(mark, index); }

					return _symbol_method.glyph_declare(mark, field);
				}

			// image:

				// nothing here.

			// (image) text:

				nik_ce auto image_text(sign_ctype_ref sign)
					{ return _symbol_method.image_text(sign); }

			// (image) declare:

				template<typename T>
				nik_ce auto image_declare(size_ctype mark, const T & field)
					{ return _symbol_method.image_declare(mark, field); }

			// record:

				nik_ce auto record_submethod()
					{ return base::model->template record_subequip<record_submethod_type>(); }

				template<typename T>
				nik_ce auto record_text(const T & text_cival, size_ctype point, size_ctype n = 1)
				{
					size_ctype start  = text_cival[point];
					size_ctype finish = start + n;
					auto record_ival  = record_submethod();
					record_ival       . mid_set(start, finish);

					return record_ival;
				}

				nik_ce auto record_text(sign_ctype_ref sign, size_ctype point, size_ctype n = 1)
					{ return record_text(base::image_ctext(sign), point, n); }

				nik_ce void record_copy(sign_ctype_ref sign, size_ctype point, size_ctype value)
					{ base::record().copy(base::image_cfield(sign, point), value); }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_method =
			concord_method_disjoint  <
			concord_cmethod_disjoint < Facade >>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

