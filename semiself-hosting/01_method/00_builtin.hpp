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

// builtin:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// concord:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class builtin_cmethod_disjoint : public Base
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

			nik_ces size_type row_length	= 3;
			nik_ces size_type col_length	= 3;
			nik_ces size_type glyph_length	= row_length * col_length;

		public:

			nik_ce builtin_cmethod_disjoint() : base{} { }
			nik_ce builtin_cmethod_disjoint(const facade & f) : base{f} { }

			// sub(ordinate) sign:

				nik_ce size_type cvalue(sign_ctype_ref sign) const
					{ return base::crecord().cat(base::image_cfield(sign, ImageBuiltin::point)); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class builtin_method_disjoint : public Base
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

			using glyph_field_type		= array<size_type, size_type, base::glyph_length>;
			using glyph_field_method_type	= resolve_submethod<glyph_field_type, table_submethod>;

			using image_field_type		= array<size_type, size_type, ImageBuiltin::dimension>;

			// glyph:

				nik_ce auto glyph_make_field()
				{
					auto field = glyph_field_type{};
					field      . fullsize();

					return field;
				}

				nik_ce auto glyph_make_table(glyph_field_type & field)
				{
					auto table = field.template subequip<glyph_field_method_type>();
					table      . full_set();
					table      . set_dimension(base::row_length, base::col_length);

					return table;
				}

			// image:

				nik_ce auto image_make_field()
				{
					auto field = image_field_type{};
					field      . fullsize();

					return field;
				}

		protected:

			// declare:

				template<typename T>
				nik_ce auto declare_type(size_ctype mark, const T & field)
				{
					size_ctype index = base::glyph_find(mark, field);

					if (base::glyph_found(mark, index))
						{ return base::glyph_make_icon(mark, index); }

					return base::glyph_declare(BookMark::builtin, field);
				}

				nik_ce auto declare_meta(icon_ctype_ref icon, size_ctype time, size_ctype point)
				{
					auto field = image_make_field();
					field      . fullsize();

					field[ImageBuiltin::index] = icon.index();
					field[ImageBuiltin::time ] = time;
					field[ImageBuiltin::point] = point;

					return base::image_declare(BookMark::builtin, field);
				}

				nik_ce auto declare_abstract(icon_ctype_ref icon)
					{ return declare_meta(icon, ImageTime::abstract, base::record().expand(1)); }

			// define:

				nik_ce void define_abstract(sign_ctype_ref sign, size_ctype value)
					{ base::record_copy(sign, ImageBuiltin::point, value); }

		public:

			nik_ce builtin_method_disjoint() : base{} { }
			nik_ce builtin_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_type(size_ctype instr, size_ctype bytes)
				{
					auto field = glyph_make_field();
					auto table = glyph_make_table(field);

					base::glyph_set_program (table, base::row_length);
					base::glyph_set_routine (table, instr);
					base::glyph_set_meta    (table, bytes);

					return declare_type(BookMark::builtin, field);
				}

				nik_ce auto declare_concrete(icon_ctype_ref icon, size_ctype addr)
					{ return declare_meta(icon, ImageTime::concrete, addr); }

			// define:

				nik_ce auto define_abstract(icon_ctype_ref icon, size_ctype value)
				{
					auto sign = declare_abstract(icon);

					define_abstract(sign, value);

					return sign;
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// empty:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class empty_cmethod_disjoint : public Base
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

			nik_ces size_type byte_size	= 0;

		public:

			nik_ce empty_cmethod_disjoint() : base{} { }
			nik_ce empty_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using empty_cmethod =
			empty_cmethod_disjoint   <
			builtin_cmethod_disjoint <
			concord_cmethod_disjoint < Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class empty_method_disjoint : public Base
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

			// declare:

				nik_ce auto declare_meta(icon_ctype_ref icon, size_ctype time)
				{
					auto field = typename base::image_field_type{};
					field      . upsize(ImageEmpty::dimension);

					field[ImageEmpty::index] = icon.index();
					field[ImageEmpty::time ] = time;

					return base::image_declare(BookMark::builtin, field);
				}

		public:

			nik_ce empty_method_disjoint() : base{} { }
			nik_ce empty_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_type()
				{
					auto field = base::glyph_make_field();
					auto table = base::glyph_make_table(field);

					base::glyph_set_program (table, base::row_length);
					base::glyph_set_routine (table, GlyphInstr::empty);
					base::glyph_set_meta    (table, base::byte_size);

					return base::declare_type(BookMark::builtin, field);
				}

			// define:

				nik_ce auto define_abstract(icon_ctype_ref icon)
					{ return declare_meta(icon, ImageTime::abstract); }
	};

	// syntactic sugar:

		template<typename Facade>
		using empty_method =
			empty_method_disjoint    <
			empty_cmethod_disjoint   <
			builtin_method_disjoint  <
			builtin_cmethod_disjoint <
			concord_method_disjoint  <
			concord_cmethod_disjoint < Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ring:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class ring_cmethod_disjoint : public Base
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

		public:

			nik_ce ring_cmethod_disjoint() : base{} { }
			nik_ce ring_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using ring_cmethod =
			ring_cmethod_disjoint    <
			builtin_cmethod_disjoint <
			concord_cmethod_disjoint < Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class ring_method_disjoint : public Base
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

		public:

			nik_ce ring_method_disjoint() : base{} { }
			nik_ce ring_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_type(size_ctype bytes)
					{ return base::declare_type(GlyphInstr::ring, bytes); }
	};

	// syntactic sugar:

		template<typename Facade>
		using ring_method =
			ring_method_disjoint     <
			ring_cmethod_disjoint    <
			builtin_method_disjoint  <
			builtin_cmethod_disjoint <
			concord_method_disjoint  <
			concord_cmethod_disjoint < Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// flex:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class flex_cmethod_disjoint : public Base
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

		public:

			nik_ce flex_cmethod_disjoint() : base{} { }
			nik_ce flex_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using flex_cmethod =
			flex_cmethod_disjoint    <
			builtin_cmethod_disjoint <
			concord_cmethod_disjoint < Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class flex_method_disjoint : public Base
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

		public:

			nik_ce flex_method_disjoint() : base{} { }
			nik_ce flex_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_type(size_ctype bytes)
					{ return base::declare_type(GlyphInstr::flex, bytes); }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_flex_method =
			flex_method_disjoint     <
			flex_cmethod_disjoint    <
			builtin_method_disjoint  <
			builtin_cmethod_disjoint <
			concord_method_disjoint  <
			concord_cmethod_disjoint < Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// utf8_char:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class utf8_char_cmethod_disjoint : public Base
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

		public:

			nik_ce utf8_char_cmethod_disjoint() : base{} { }
			nik_ce utf8_char_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using utf8_char_cmethod =
			utf8_char_cmethod_disjoint <
			builtin_cmethod_disjoint   <
			concord_cmethod_disjoint   < Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class utf8_char_method_disjoint : public Base
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

		public:

			nik_ce utf8_char_method_disjoint() : base{} { }
			nik_ce utf8_char_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_type(size_ctype bytes)
					{ return base::declare_type(GlyphInstr::utf8_char, bytes); }

			// define:

				nik_ce auto define_abstract(icon_ctype_ref icon, size_ctype char1)
				{
					auto sign = base::declare_abstract(icon);

					return sign;
				}

				nik_ce auto define_abstract(icon_ctype_ref icon, size_ctype char1, size_ctype char2)
				{
					auto sign = base::declare_abstract(icon);

					return sign;
				}

				nik_ce auto define_abstract(icon_ctype_ref icon,
					size_ctype char1, size_ctype char2, size_ctype char3)
				{
					auto sign = base::declare_abstract(icon);

					return sign;
				}

				nik_ce auto define_abstract(icon_ctype_ref icon,
					size_ctype char1, size_ctype char2, size_ctype char3, size_ctype char4)
				{
					auto sign = base::declare_abstract(icon);

					return sign;
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using utf8_char_method =
			utf8_char_method_disjoint  <
			utf8_char_cmethod_disjoint <
			builtin_method_disjoint    <
			builtin_cmethod_disjoint   <
			concord_method_disjoint    <
			concord_cmethod_disjoint   < Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

