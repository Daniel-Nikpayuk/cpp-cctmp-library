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

			nik_ces size_type row_length	= base::row_body;
			nik_ces size_type glyph_length	= row_length * base::col_length;

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

			nik_ces size_type bytes_to_units(size_ctype bytes)
			{
				size_ctype unit_size   = sizeof(size_type);
				size_ctype is_multiple = static_cast<bool>(bytes % unit_size);

				return ((bytes / unit_size) + is_multiple);
			}

		protected:

			using glyph_field_type		= array<size_type, size_type, base::glyph_length>;

			// glyph:

				nik_ce auto glyph_make_field()
					{ return base::template glyph_make_field<base::glyph_length>(); }

				nik_ce auto glyph_make_table(glyph_field_type & field)
				{
					return base::template
						glyph_make_table<base::glyph_length>
							(field, base::row_length, base::col_length);
				}

			// image:

				using base::image_make_field;

				nik_ce auto image_make_field()
					{ return base::template image_make_field<ImageBuiltin::dimension>(); }

		protected:

			// declare:

				nik_ce auto declare_meta(icon_ctype_ref icon, size_ctype units, size_ctype point)
				{
					auto field = image_make_field();
					field      . fullsize();

					field[ImageBuiltin::index] = icon.index();
					field[ImageBuiltin::units] = units;
					field[ImageBuiltin::point] = point;

					return base::image_declare(BookMark::builtin, field);
				}

				nik_ce auto declare_value(icon_ctype_ref icon)
				{
					size_ctype bytes = base::glyph_cfield(icon, base::row_meta, GlyphMeta::bytes);
					size_ctype units = bytes_to_units(bytes);
					size_ctype point = base::record().expand(units);

					return declare_meta(icon, units, point);
				}

			// define:

				nik_ce void define_value(sign_ctype_ref sign, size_ctype value)
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

					return base::glyph_declare(BookMark::builtin, field);
				}

			// define:

				nik_ce auto define_value(icon_ctype_ref icon, size_ctype value)
				{
					auto sign = declare_value(icon);

					define_value(sign, value);

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

				nik_ce auto declare_meta(icon_ctype_ref icon)
				{
					auto field = base::template image_make_field<ImageEmpty::dimension>();

					field[ImageEmpty::index] = icon.index();

					return base::image_declare(BookMark::builtin, field);
				}

		public:

			nik_ce empty_method_disjoint() : base{} { }
			nik_ce empty_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_type()
					{ return base::declare_type(GlyphInstr::empty, base::byte_size); }

			// define:

				nik_ce auto define_value(icon_ctype_ref icon) { return declare_meta(icon); }
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

// utf8 char:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class utf8_char_cmethod_disjoint : public Base
	{
		public:

			using base				= Base;
			using facade				= typename base::facade;
			using model_type			= typename base::model_type;

			nik_using_size_type_scope		(base)

			using icon_type				= typename base::icon_type;
			using icon_ctype_ref			= typename base::icon_ctype_ref;

			using sign_type				= typename base::sign_type;
			using sign_ctype_ref			= typename base::sign_ctype_ref;

		protected:

			// byte range:

				nik_ces size_type max_byte	= 4;

				struct Range
				{
					enum : size_type
					{
						x00_x7f, xc2_xdf, xe0_xe0, xe1_xec, xed_xed,
						xee_xef, xf0_xf0, xf1_xf3, xf4_xf4,

						dimension
					};
				};

				struct Byte        { enum : size_type { b1, e1, b2, e2, b3, e3, b4, e4, dimension }; };
				using range_type   = table<size_type, size_type, Range::dimension, Byte::dimension>;
				nik_ces auto range = range_type
				{{
				//	  b1   e1     b2   e2     b3   e3     b4   e4
					0x00,0x7f , 0x00,0x7f , 0x00,0x7f , 0x00,0x7f , // 0 - char1
					0xc2,0xdf , 0x80,0xbf , 0x00,0x7f , 0x00,0x7f , // 1 - char2
					0xe0,0xe0 , 0xa0,0xbf , 0x80,0xbf , 0x00,0x7f , // 2 - char3
					0xe1,0xec , 0x80,0xbf , 0x80,0xbf , 0x00,0x7f , // 3 - char3
					0xed,0xed , 0x80,0x9f , 0x80,0xbf , 0x00,0x7f , // 4 - char3
					0xee,0xef , 0x80,0xbf , 0x80,0xbf , 0x00,0x7f , // 5 - char3
					0xf0,0xf0 , 0x90,0xbf , 0x80,0xbf , 0x80,0xbf , // 6 - char4
					0xf1,0xf3 , 0x80,0xbf , 0x80,0xbf , 0x80,0xbf , // 7 - char4
					0xf4,0xf4 , 0x80,0x8f , 0x80,0xbf , 0x80,0xbf   // 8 - char4
				}};

			// code point:

				struct Point
				{
					enum : size_type
					{
						x000000_x00007f, // 0 - char1
						x000080_x0007ff, // 1 - char2
						x000800_x000fff, // 2 - char3
						x001000_x00cfff, // 3 - char3
						x00d000_x00d7ff, // 4 - char3
						x00e000_x00ffff, // 5 - char3
						x010000_x03ffff, // 6 - char4
						x040000_x0fffff, // 7 - char4
						x100000_x10ffff, // 8 - char4

						dimension
					};
				};

				struct Code        { enum : size_type { b, e, dimension }; };
				using point_type   = table<size_type, size_type, Point::dimension, Code::dimension>;
				nik_ces auto point = point_type
				{{
					0x000000 , 0x00007f , // 0 - char1
					0x000080 , 0x0007ff , // 1 - char2
					0x000800 , 0x000fff , // 2 - char3
					0x001000 , 0x00cfff , // 3 - char3
					0x00d000 , 0x00d7ff , // 4 - char3
					0x00e000 , 0x00ffff , // 5 - char3
					0x010000 , 0x03ffff , // 6 - char4
					0x040000 , 0x0fffff , // 7 - char4
					0x100000 , 0x10ffff   // 8 - char4
				}};

		public:

			nik_ce utf8_char_cmethod_disjoint() : base{} { }
			nik_ce utf8_char_cmethod_disjoint(const facade & f) : base{f} { }

			// byte range:

				nik_ces bool in_range(size_ctype v, size_ctype n, size_ctype s, size_ctype f)
					{ return (range[n][s] <= v && v <= range[n][f]); }

				nik_ces bool is_byte1_valid(size_ctype v, size_ctype n)
					{ return base::in_range(v, n, Byte::b1, Byte::e1); }

				nik_ces bool is_byte2_valid(size_ctype v, size_ctype n)
					{ return base::in_range(v, n, Byte::b2, Byte::e2); }

				nik_ces bool is_byte3_valid(size_ctype v, size_ctype n)
					{ return base::in_range(v, n, Byte::b3, Byte::e3); }

				nik_ces bool is_byte4_valid(size_ctype v, size_ctype n)
					{ return base::in_range(v, n, Byte::b4, Byte::e4); }

			// code point:

				nik_ces bool on_point(size_ctype v, size_ctype n)
					{ return (point[n][Code::b] <= v && v <= point[n][Code::e]); }
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

				template<typename In, typename End>
				nik_ce auto define_value(icon_ctype_ref icon, In in, End end)
				{
					auto sign = base::declare_value(icon);

					size_ctype length = end - in;
					auto text_ival    = base::record_text(sign, ImageBuiltin::point, length);
					text_ival         . copy(0, in, end);

					return sign;
				}

				template<auto N>
				nik_ce auto define_value(icon_ctype_ref icon, size_ctype (&v)[N])
					{ return define_value(icon, v, v + N); }
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

