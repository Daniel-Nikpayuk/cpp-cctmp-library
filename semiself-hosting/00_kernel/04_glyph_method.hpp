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

// glyph method:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// instructions:

	struct GlyphInstr
	{
		enum : gkey_type
		{
			program, push, apply,
			empty, ring, flex, utf8_char, tuple, cotuple, function, null, list,
			identity, l_than, l_than_or_eq, g_than, g_than_or_eq, dependent, custom,
			exists, forall, type, value, arg,

			dimension
		};
	};

/***********************************************************************************************************************/

// fields:

	struct GlyphProg { enum : gkey_type { instr, lines,     code, next, dimension }; };
	struct GlyphRout { enum : gkey_type { instr, arity,    local, next, dimension }; };
	struct GlyphMeta { enum : gkey_type { instr, bytes, universe, next, dimension }; };

/***********************************************************************************************************************/

// codes:

	struct GlyphCode
	{
		enum : gkey_type
		{
			valid, invalid, // will be refined and extended as needed.

			dimension
		};
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// base:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class glyph_cmethod_disjoint : public book_cmethod_disjoint<Base, array_cmethod, table_csubmethod>
	{
		public:

			using base			= book_cmethod_disjoint<Base, array_cmethod, table_csubmethod>;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		protected:

			nik_ces auto col_length	= size_type{4};

		public:

			nik_ce glyph_cmethod_disjoint() : base{} { }
			nik_ce glyph_cmethod_disjoint(const facade & f) : base{f} { }

			// icon:

				nik_ce auto make_icon(size_type n, size_ctype m) const { return icon_type{n, m}; }

			// fail:

				nik_ce bool is_fail(icon_ctype_ref n) const
				{
					return false;
				}

				nik_ce bool not_fail(icon_ctype_ref n) const { return not is_fail(n); }

				nik_ce auto fail_icon()
				{
					// fail icon should construct
					// a fail message type/value.

					return make_icon(0, 0);
				}

			// type check:

			//	template<typename T, typename... Ts>
			//	nik_ce bool same_types(size_ctype n, const T l, const Ts... rs) const
			//		{ return same_methods(n, page_to_text_cequip(l), page_to_text_cequip(rs)...); }

			//	template<typename T, typename... Ts>
			//	nik_ce bool same_methods(size_ctype n, const T & l, const Ts &... rs) const
			//	{
			//		for (size_type k = 0; k != n; ++k)
			//			{ if (different_values(l[k], rs[k]...)) return false; }

			//		return true;
			//	}

			//	template<typename T, typename... Ts>
			//	nik_ce bool different_values(const T l, const Ts... rs) const
			//		{ return (... || (l != rs)); }

			// text:

					// safe version should reset dimensions.
				nik_ce auto fast_set_ctext_from_icon(icon_ctype_ref icon)
				{
					base::fast_set_cpage_chapter(icon.mark());
					base::fast_set_ctext_from_page(icon.index());
				}

					// needs to test against subtext.
				nik_ce void fast_set_ctext_dim(size_ctype r, size_ctype c)
					{ base::text_csubmethod.fast_set_dimension(r, c); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class glyph_method_disjoint : public book_method_disjoint<Base, array_method, table_submethod>
	{
		public:

			using base			= book_method_disjoint<Base, array_method, table_submethod>;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		public:

			nik_ce glyph_method_disjoint() : base{} { }
			nik_ce glyph_method_disjoint(const facade & f) : base{f} { }

			nik_ce void make_line_program(size_ctype lines, size_ctype code = GlyphCode::valid)
			{
				nik_ce size_type line = 0;

				base::text_submethod[line][GlyphProg::instr] = GlyphInstr::program;
				base::text_submethod[line][GlyphProg::lines] = lines;
				base::text_submethod[line][GlyphProg::code ] = code;
				base::text_submethod[line][GlyphProg::next ] = 1;
			}

			nik_ce void make_line_routine(size_ctype instr, size_ctype arity = 0, size_ctype local = 0)
			{
				nik_ce size_type line = 1;

				base::text_submethod[line][GlyphRout::instr] = instr;
				base::text_submethod[line][GlyphRout::arity] = arity;
				base::text_submethod[line][GlyphRout::local] = local;
				base::text_submethod[line][GlyphRout::next ] = 1;
			}

			nik_ce void make_line_meta(size_ctype bytes, size_ctype universe = 0, size_ctype next = 1)
			{
				nik_ce size_type line = 2;

				base::text_submethod[line][GlyphMeta::instr   ] = GlyphInstr::push;
				base::text_submethod[line][GlyphMeta::bytes   ] = bytes;
				base::text_submethod[line][GlyphMeta::universe] = universe;
				base::text_submethod[line][GlyphMeta::next    ] = next;
			}

			// text:

					// safe version should reset dimensions.
				nik_ce auto fast_set_text_from_icon(icon_ctype_ref icon)
				{
					base::fast_set_page_chapter(icon.mark());
					base::fast_set_text_from_page(icon.index());
				}

					// needs to test against subtext.
				nik_ce void fast_set_text_dim(size_ctype r, size_ctype c)
					{ base::text_submethod.fast_set_dimension(r, c); }

			// allocate:

				nik_ce auto allocate(size_ctype n, size_ctype m)
				{
					if (base::allocate(n, m))
						{ return base::make_icon(n, base::page_cmethod.max()); }
					else    { return base::fail_icon(); }
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// builtin:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class glyph_builtin_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		public:

			nik_ce glyph_builtin_cmethod_disjoint() : base{} { }
			nik_ce glyph_builtin_cmethod_disjoint(const facade & f) : base{f} { }

			// find:

			//	nik_ce size_type left_find(size_ctype bits) const
			//		{ return base::left_find({base::name, (bits >> 3)}); }
	};

	// syntactic sugar:

		template<typename Facade>
		using glyph_builtin_cmethod =
			glyph_builtin_cmethod_disjoint <
			glyph_cmethod_disjoint         < Facade >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class glyph_builtin_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		protected:

			nik_ces size_type row_length	= 3;
			nik_ces size_type length	= row_length * base::col_length;

		public:

			nik_ce glyph_builtin_method_disjoint() : base{} { }
			nik_ce glyph_builtin_method_disjoint(const facade & f) : base{f} { }

			nik_ce void copy_program(size_ctype instr, size_ctype bytes)
			{
				base::make_line_program (row_length);
				base::make_line_routine (instr);
				base::make_line_meta    (bytes, 0, 0);
			}

			nik_ce void instantiate(icon_type_ref icon, size_ctype instr, size_ctype bytes)
			{
				base::fast_set_text_dim(row_length, base::col_length);

				copy_program(instr, bytes);

				size_ctype pos = base::find_from_previous(icon.mark(), icon.index());

				if (base::found_from_previous(pos, icon.index()))
				{
					icon.set_index(pos);

					base::fast_deallocate_last(); // reset text as well (non fast) ?
				}
			}

			nik_ce auto declare(size_ctype instr, size_ctype bytes)
			{
				auto icon = base::allocate(BookMark::builtin, length);

				if (base::not_fail(icon)) { instantiate(icon, instr, bytes); }

				return icon;
			}
	};

	// syntactic sugar:

		template<typename Facade>
		using glyph_builtin_method =
			glyph_builtin_method_disjoint  <
			glyph_builtin_cmethod_disjoint <
			glyph_method_disjoint          <
			glyph_cmethod_disjoint         < Facade >>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// empty:

/***********************************************************************************************************************/

// immutable:

	template<typename Facade>
	class glyph_empty_cmethod : public glyph_builtin_cmethod<Facade>
	{
		public:

			using base			= glyph_builtin_cmethod<Facade>;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

		public:

			nik_ce glyph_empty_cmethod() : base{} { }
			nik_ce glyph_empty_cmethod(const facade & f) : base{f} { }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Facade>
	class glyph_empty_method : public glyph_builtin_method<Facade>
	{
		public:

			using base			= glyph_builtin_method<Facade>;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

		public:

			nik_ce glyph_empty_method() : base{} { }
			nik_ce glyph_empty_method(const facade & f) : base{f} { }

			nik_ce auto declare(size_ctype bytes) { return base::declare(GlyphInstr::empty, bytes); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ring:

/***********************************************************************************************************************/

// immutable:

	template<typename Facade>
	class glyph_ring_cmethod : public glyph_builtin_cmethod<Facade>
	{
		public:

			using base			= glyph_builtin_cmethod<Facade>;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

		public:

			nik_ce glyph_ring_cmethod() : base{} { }
			nik_ce glyph_ring_cmethod(const facade & f) : base{f} { }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Facade>
	class glyph_ring_method : public glyph_builtin_method<Facade>
	{
		public:

			using base			= glyph_builtin_method<Facade>;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

		public:

			nik_ce glyph_ring_method() : base{} { }
			nik_ce glyph_ring_method(const facade & f) : base{f} { }

			nik_ce auto declare(size_ctype bytes) { return base::declare(GlyphInstr::ring, bytes); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// flex:

/***********************************************************************************************************************/

// immutable:

	template<typename Facade>
	class glyph_flex_cmethod : public glyph_builtin_cmethod<Facade>
	{
		public:

			using base			= glyph_builtin_cmethod<Facade>;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

		public:

			nik_ce glyph_flex_cmethod() : base{} { }
			nik_ce glyph_flex_cmethod(const facade & f) : base{f} { }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Facade>
	class glyph_flex_method : public glyph_builtin_method<Facade>
	{
		public:

			using base			= glyph_builtin_method<Facade>;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

		public:

			nik_ce glyph_flex_method() : base{} { }
			nik_ce glyph_flex_method(const facade & f) : base{f} { }

			nik_ce auto declare(size_ctype bytes) { return base::declare(GlyphInstr::flex, bytes); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// utf8 char:

/***********************************************************************************************************************/

// immutable:

	template<typename Facade>
	class glyph_utf8_char_cmethod : public glyph_builtin_cmethod<Facade>
	{
		public:

			using base			= glyph_builtin_cmethod<Facade>;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

		public:

			nik_ce glyph_utf8_char_cmethod() : base{} { }
			nik_ce glyph_utf8_char_cmethod(const facade & f) : base{f} { }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Facade>
	class glyph_utf8_char_method : public glyph_builtin_method<Facade>
	{
		public:

			using base			= glyph_builtin_method<Facade>;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

		public:

			nik_ce glyph_utf8_char_method() : base{} { }
			nik_ce glyph_utf8_char_method(const facade & f) : base{f} { }

			nik_ce auto declare(size_ctype bytes) { return base::declare(GlyphInstr::utf8_char, bytes); }
	};

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

