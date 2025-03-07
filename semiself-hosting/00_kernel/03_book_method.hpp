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

// book method:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// method:

/***********************************************************************************************************************/

// immutable:

	template<template<typename> typename PageCMethod, template<typename> typename TextCMethod, typename Base>
	class book_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename facade::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= icon<size_type>;
			using icon_type_ref		= typename alias<icon_type>::type_ref;
			using icon_ctype_ref		= typename alias<icon_type>::ctype_ref;

			using sign_type			= sign<size_type>;
			using sign_type_ref		= typename alias<sign_type>::type_ref;
			using sign_ctype_ref		= typename alias<sign_type>::ctype_ref;

		protected:

			using page_cmethod_type		= typename model_type::template
								page_cmethod_type<PageCMethod>;

			using text_csubmethod_type	= typename model_type::template
								text_csubmethod_type<TextCMethod>;

		protected:

			nik_ces void total_act(size_type & n, size_ctype m) { n += m; }
			nik_ces void   max_act(size_type & n, size_ctype m) { if (n < m) { n = m; } }

		public:

			nik_ce book_cmethod_disjoint() : base{} { }
			nik_ce book_cmethod_disjoint(const facade & f) : base{f} { }

			// page:

				nik_ce auto page_cmethod(size_ctype n) const
					{ return base::model->template page_cequip<page_cmethod_type>(n); }

			// text:

				nik_ce auto text_csubmethod(size_ctype start, size_ctype finish) const
				{
					auto cival = base::model->template text_csubequip<text_csubmethod_type>();
					cival.mid_set(start, finish);

					return cival;
				}

				nik_ce auto text_csubmethod(const page_cmethod_type & page_cival, size_ctype index) const
				{
					auto npage = page_cival.citer(index);

					return text_csubmethod(npage->start(), npage->finish());
				}

			// find:

				nik_ce bool found(size_ctype mark, size_ctype n) const
					{ return (n < page_cmethod(mark).size()); }
	};

/***********************************************************************************************************************/

// mutable:

	template<template<typename> typename PageMethod, template<typename> typename TextMethod, typename Base>
	class book_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;
			using ival_type			= typename model_type::ival_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_type_ref		= typename base::sign_type_ref;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		protected:

			using page_cmethod_type		= typename base::page_cmethod_type;
			using page_method_type		= typename model_type::template
								page_method_type<PageMethod>;

			using text_csubmethod_type	= typename base::text_csubmethod_type;
			using text_submethod_type	= typename model_type::template
								text_submethod_type<TextMethod>;

		protected:

				nik_ce void push_page(page_method_type & page_ival, size_ctype n)
				{
					size_ctype start  = base::text().expand(n);
					size_ctype finish = start + n;

					page_ival.push(ival_type{start, finish});
				}

				nik_ce bool allocate(page_method_type & page_ival, size_ctype n)
				{
					if (page_ival.is_full() || base::ctext().lacks_capacity(n)) return false;

					push_page(page_ival, n);

					return true;
				}

		public:

			nik_ce book_method_disjoint() : base{} { }
			nik_ce book_method_disjoint(const facade & f) : base{f} { }

			// page:

				nik_ce auto page_method(size_ctype n)
					{ return base::model->template page_equip<page_method_type>(n); }

			// text:

				nik_ce auto text_submethod(size_ctype start, size_ctype finish)
				{
					auto ival = base::model->template text_subequip<text_submethod_type>();
					ival.mid_set(start, finish);

					return ival;
				}

				nik_ce auto text_submethod(const page_cmethod_type & page_cival, size_ctype index)
				{
					auto npage = page_cival.citer(index);

					return text_submethod(npage->start(), npage->finish());
				}

				nik_ce auto text_submethod(const page_method_type & page_ival, size_ctype index)
				{
					auto npage = page_ival.citer(index);

					return text_submethod(npage->start(), npage->finish());
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// glyph:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// instr(uctions):

	struct GlyphInstr
	{
		enum : genum_type
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

	struct GlyphProg { enum : genum_type { instr, lines,     code, dimension }; };
	struct GlyphRout { enum : genum_type { instr, arity,    local, dimension }; };
	struct GlyphMeta { enum : genum_type { instr, bytes, universe, dimension }; };
	struct GlyphNote { enum : genum_type { instr,  mark,    index, dimension }; };

/***********************************************************************************************************************/

// codes:

	struct GlyphCode
	{
		enum : genum_type
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

	template<typename Base> // inheritance as {glyph, image} optimization.
	class glyph_cmethod_disjoint : public book_cmethod_disjoint<array_cmethod, table_csubmethod, Base>
	{
		public:

			using base			= book_cmethod_disjoint<array_cmethod, table_csubmethod, Base>;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		protected:

			using page_cmethod_type		= typename base::page_cmethod_type;
			using text_csubmethod_type	= typename base::text_csubmethod_type;

		public:

			nik_ces size_type row_program	= 0;
			nik_ces size_type row_routine	= 1;
			nik_ces size_type row_meta	= 2;
			nik_ces size_type row_body	= 3;

			nik_ces size_type col_length	= 3;

		protected:

			template<auto act, typename T> // this needs to check for recusive types!
			nik_ce size_type fold(const T & v, size_ctype col) const
			{
				size_type n = 0;

				for (auto k = v.cbegin(); k != v.cend(); ++k)
				{
					auto text_cival = text_csubmethod(*k);
					size_ctype m    = text_cival[row_meta][col];

					act(n, m);
				}

				return n;
			}

		public:

			nik_ce glyph_cmethod_disjoint() : base{} { }
			nik_ce glyph_cmethod_disjoint(const facade & f) : base{f} { }

			// icon:

				nik_ce auto make_icon(size_type n, size_ctype m) const { return icon_type{n, m}; }

			// fail:

				nik_ce bool is_fail(icon_ctype_ref icon) const
				{
					return false;
				}

				nik_ce bool not_fail(icon_ctype_ref icon) const { return not is_fail(icon); }

				nik_ce auto fail_icon()
				{
					// fail icon should construct
					// a fail message type/value.

					return make_icon(0, 0);
				}

			// text:

				nik_ce auto text_csubmethod(icon_ctype_ref icon) const
				{
					auto page_cival       = base::page_cmethod(icon.mark());
					auto text_cival       = base::text_csubmethod(page_cival, icon.index());
					size_ctype row_length = text_cival.cat(GlyphProg::lines); // optimization.
					text_cival            . set_dimension(row_length, col_length);

					return text_cival;
				}

			// field:

				nik_ce auto text_cfield(icon_ctype_ref icon, size_ctype row, size_ctype col) const
					{ return text_csubmethod(icon).cat(row, col); }

			// compare:

				nik_ce bool is_instr(icon_ctype_ref icon, size_ctype instr) const
					{ return (text_cfield(row_routine, GlyphRout::instr) == instr); }

				nik_ce bool is_custom(icon_ctype_ref icon) const
					{ return (icon.mark() >= BookMark::dimension); }

				nik_ce bool equal(icon_ctype_ref icon1, icon_ctype_ref icon2) const
				{
					auto text_cival1 = text_csubmethod(icon1);
					auto text_cival2 = text_csubmethod(icon2);

					return text_cival1.equal(0, text_cival2.cbegin(), text_cival2.cend());
				}

			// sub(ordinate) icon:

				nik_ce auto sub_icon(icon_ctype_ref icon, size_ctype row) const
				{
					auto text_cival  = text_csubmethod(icon);
					size_ctype mark  = text_cival[row][GlyphNote::mark ];
					size_ctype index = text_cival[row][GlyphNote::index];

					return make_icon(mark, index);
				}

			// find:

				template<typename T> // assumes page and <note> page match.
				nik_ce size_type find(size_ctype mark, const T & v) const
				{
					auto page_cival = base::page_cmethod(mark);

					for (size_type pos = 0; pos != page_cival.size(); ++pos)
					{
						auto text_cival = base::text_csubmethod(page_cival, pos);

						if (text_cival.equal(0, v.cbegin(), v.cend())) { return pos; }
					}

					return page_cival.size();
				}

			// total:

				template<typename T>
				nik_ce size_type total_bytes(const T & v) const
					{ return fold<base::total_act>(v, GlyphMeta::bytes); }

			// max:

				template<typename T>
				nik_ce size_type max_bytes(const T & v) const
					{ return fold<base::max_act>(v, GlyphMeta::bytes); }

				template<typename T>
				nik_ce size_type max_universe(const T & v) const
					{ return fold<base::max_act>(v, GlyphMeta::universe); }
	};

	// syntactic sugar:

		template<typename Facade>
		using glyph_cmethod =
			glyph_cmethod_disjoint < Facade >;

/***********************************************************************************************************************/

// mutable:

	template<typename Base> // inheritance as {glyph, image} optimization.
	class glyph_method_disjoint : public book_method_disjoint<array_method, table_submethod, Base>
	{
		public:

			using base			= book_method_disjoint<array_method, table_submethod, Base>;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		protected:

			using page_cmethod_type		= typename base::page_cmethod_type;
			using page_method_type		= typename base::page_method_type;

			using text_csubmethod_type	= typename base::text_csubmethod_type;
			using text_submethod_type	= typename base::text_submethod_type;

		protected:

			// allocate:

				nik_ce auto allocate(page_method_type & page_ival, size_ctype mark, size_ctype n)
				{
					if (base::allocate(page_ival, n))
						{ return base::make_icon(mark, page_ival.max()); }
					else    { return base::fail_icon(); }
				}

		public:

			nik_ce glyph_method_disjoint() : base{} { }
			nik_ce glyph_method_disjoint(const facade & f) : base{f} { }

			// text:

				using base::text_submethod;

				nik_ce auto text_submethod(icon_ctype_ref icon)
				{
					auto page_cival       = base::page_cmethod(icon.mark());
					auto text_ival        = base::text_submethod(page_cival, icon.index());
					size_ctype row_length = text_ival.cat(GlyphProg::lines); // optimization.
					text_ival             . set_dimension(row_length, base::col_length);

					return text_ival;
				}

			// field:

				nik_ce void set_field(icon_ctype_ref icon, size_ctype row, size_ctype col, size_ctype v)
					{ text_submethod(icon).copy(row, col, v); }

			// instr:

				template<typename T>
				nik_ce void set_program(T & table,
					size_ctype lines, size_ctype code = GlyphCode::valid)
				{
					table[base::row_program][GlyphProg::instr] = GlyphInstr::program;
					table[base::row_program][GlyphProg::lines] = lines;
					table[base::row_program][GlyphProg::code ] = code;
				}

				template<typename T>
				nik_ce void set_routine(T & table,
					size_ctype instr, size_ctype arity = 0, size_ctype local = 0)
				{
					table[base::row_routine][GlyphRout::instr] = instr;
					table[base::row_routine][GlyphRout::arity] = arity;
					table[base::row_routine][GlyphRout::local] = local;
				}

				template<typename T>
				nik_ce void set_meta(T & table,
					size_ctype bytes, size_ctype universe = 0)
				{
					table[base::row_meta][GlyphMeta::instr   ] = GlyphInstr::push;
					table[base::row_meta][GlyphMeta::bytes   ] = bytes;
					table[base::row_meta][GlyphMeta::universe] = universe;
				}

				template<typename T>
				nik_ce void set_note(T & table,
					size_ctype row, size_ctype mark, size_ctype index)
				{
					table[row][GlyphNote::instr] = GlyphInstr::type;
					table[row][GlyphNote::mark ] = mark ;
					table[row][GlyphNote::index] = index;
				}

			// declare:

				nik_ce size_type declare() { return base::page().expand(); } // space

				template<typename T>
				nik_ce auto declare(size_ctype mark, const T & field)
				{
					auto page_ival = base::page_method(mark);
					auto icon      = allocate(page_ival, mark, field.size());

					if (base::not_fail(icon))
					{
						auto text_ival = text_submethod(page_ival, icon.index());

						text_ival.copy(0, field.cbegin(), field.cend());
					}

					return icon;
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using glyph_method =
			glyph_method_disjoint  <
			glyph_cmethod_disjoint < Facade >>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// image:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// empty (base):

	struct ImageEmpty { enum : genum_type { index, units, dimension }; };

	using IE = ImageEmpty;

/***********************************************************************************************************************/

// mark:

	struct ImageBuiltin  : public IE { enum : genum_type { units = IE::units,         point, dimension }; };
	struct ImageTuple    : public IE { enum : genum_type { units = IE::units, length, point, dimension }; };
	struct ImageCotuple  : public IE { enum : genum_type { units = IE::units, inject, point, dimension }; };
	struct ImageFunction : public IE { enum : genum_type { units = IE::units, length, point, dimension }; };
	struct ImageList     : public IE { enum : genum_type { units = IE::units,         point, dimension }; };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// base:

/***********************************************************************************************************************/

// immutable:

	template<typename Base> // inheritance as {glyph, image} optimization.
	class image_cmethod_disjoint : public book_cmethod_disjoint<array_cmethod, array_csubmethod, Base>
	{
		public:

			using base			= book_cmethod_disjoint<array_cmethod, array_csubmethod, Base>;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_type_ref		= typename base::sign_type_ref;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		protected:

			using page_cmethod_type		= typename base::page_cmethod_type;
			using text_csubmethod_type	= typename base::text_csubmethod_type;

		protected:

			template<auto act, typename T> // this needs to check for recusive types!
			nik_ce size_type fold(const T & v, size_ctype pos) const
			{
				size_type n = 0;

				for (auto k = v.cbegin(); k != v.cend(); ++k)
				{
					auto text_cival = text_csubmethod(*k);
					size_ctype m    = text_cival[pos];

					act(n, m);
				}

				return n;
			}

		public:

			nik_ce image_cmethod_disjoint() : base{} { }
			nik_ce image_cmethod_disjoint(const facade & f) : base{f} { }

			// sign:

				nik_ce auto make_sign(size_type n, size_ctype m) const { return sign_type{n, m}; }

			// fail:

				nik_ce bool is_fail(sign_ctype_ref sign) const
				{
					return false;
				}

				nik_ce bool not_fail(sign_ctype_ref sign) const { return not is_fail(sign); }

				nik_ce auto fail_sign()
				{
					// fail sign should construct
					// a fail message type/value.

					return make_sign(0, 0);
				}

			// text:

				nik_ce auto text_csubmethod(sign_ctype_ref sign) const
					{ return base::text_csubmethod(base::page_cmethod(sign.mark()), sign.index()); }

			// field:

				nik_ce auto text_cfield(sign_ctype_ref sign, size_ctype n) const
					{ return text_csubmethod(sign).cat(n); }

			// compare:

				nik_ce bool equal(sign_ctype_ref sign1, sign_ctype_ref sign2) const
				{
					auto text_cival1 = text_csubmethod(sign1);
					auto text_cival2 = text_csubmethod(sign2);

					return text_cival1.equal(0, text_cival2.cbegin(), text_cival2.cend());
				}

			// total:

				template<typename T>
				nik_ce size_type total_units(const T & v) const
					{ return fold<base::total_act>(v, ImageEmpty::units); }

			// max:

				template<typename T>
				nik_ce size_type max_units(const T & v) const
					{ return fold<base::max_act>(v, ImageEmpty::units); }
	};

	// syntactic sugar:

		template<typename Facade>
		using image_cmethod =
			image_cmethod_disjoint < Facade >;

/***********************************************************************************************************************/

// mutable:

	template<typename Base> // inheritance as {glyph, image} optimization.
	class image_method_disjoint : public book_method_disjoint<array_method, array_submethod, Base>
	{
		public:

			using base			= book_method_disjoint<array_method, array_submethod, Base>;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_type_ref		= typename base::sign_type_ref;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		protected:

			using page_cmethod_type		= typename base::page_cmethod_type;
			using page_method_type		= typename base::page_method_type;

			using text_csubmethod_type	= typename base::text_csubmethod_type;
			using text_submethod_type	= typename base::text_submethod_type;

		protected:

			// allocate:

				nik_ce auto allocate(page_method_type & page_ival, size_ctype mark, size_ctype n)
				{
					if (base::allocate(page_ival, n))
						{ return base::make_sign(mark, page_ival.max()); }
					else    { return base::fail_sign(); }
				}

		public:

			nik_ce image_method_disjoint() : base{} { }
			nik_ce image_method_disjoint(const facade & f) : base{f} { }

			// text:

				using base::text_submethod;

				nik_ce auto text_submethod(sign_ctype_ref sign)
					{ return base::text_submethod(base::page_cmethod(sign.mark()), sign.index()); }

			// declare:

				template<typename T>
				nik_ce auto declare(size_ctype mark, const T & field)
				{
					auto page_ival = base::page_method(mark);
					auto sign      = allocate(page_ival, mark, field.size());

					if (base::not_fail(sign))
					{
						auto text_ival = text_submethod(page_ival, sign.index());

						text_ival.copy(0, field.cbegin(), field.cend());
					}

					return sign;
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using image_method =
			image_method_disjoint  <
			image_cmethod_disjoint < Facade >>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

