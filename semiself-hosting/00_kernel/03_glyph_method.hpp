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

			nik_ces size_type col_length	= 3;

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

			// text:

				nik_ce auto text_csubmethod(icon_ctype_ref icon) const
					{ return base::text_csubmethod(base::page_cmethod(icon.mark()), icon.index()); }

			// find:

					// assumes page and note_page match.
				nik_ce size_type find_from_previous(icon_ctype_ref icon) const
				{
					auto page_cival = base::page_cmethod(icon.mark());
					auto npage      = page_cival.citer(icon.index());
					auto text_cival = base::text_csubmethod(npage->start(), npage->finish());

					for (auto k = page_cival.cbegin(); k != npage; ++k)
					{
						auto b = base::ctext().citer(k->start ());
						auto e = base::ctext().citer(k->finish());

						if (text_cival.equal(0, b, e))
							{ return page_cival.left_size(k); }
					}

					return icon.index();
				}

			// program:

				template<typename T> // this needs to check for recusive types!
				nik_ce size_type total_bytes(const T & v)
				{
					size_type total = 0;

					for (auto k = v.cbegin(); k != v.cend(); ++k)
					{
						auto text_cival = text_csubmethod(*k);
						text_cival      . set_dimension(3, 3);

						size_ctype n = sizeof(size_type);
						size_ctype b = text_cival[2][GlyphMeta::bytes];
						size_ctype m = static_cast<bool>(b % n);

						total += ((b / n) + m) * n;
					}

					return total;
				}

				template<typename T> // this needs to check for recusive types!
				nik_ce size_type max_push(const T & v, size_ctype n)
				{
					size_type max = 0;

					for (auto k = v.cbegin(); k != v.cend(); ++k)
					{
						auto text_cival = text_csubmethod(*k);
						text_cival      . set_dimension(3, 3);

						size_ctype current = text_cival[2][n];

						if (current > max) { max = current; }
					}

					return max;
				}

				template<typename T>
				nik_ce size_type max_bytes(const T & v) { return max_push(v, GlyphMeta::bytes); }

				template<typename T>
				nik_ce size_type max_universe(const T & v) { return max_push(v, GlyphMeta::universe); }
	};

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

			nik_ce void pop_page_if(const page_method_type & page_ival, icon_type_ref icon)
			{
				size_ctype pos = base::find_from_previous(icon);

				if (base::found_from_previous(pos, icon.index()))
				{
					icon.set_index(pos);

					base::deallocate_last(page_ival);
				}
			}

		public:

			nik_ce glyph_method_disjoint() : base{} { }
			nik_ce glyph_method_disjoint(const facade & f) : base{f} { }

			nik_ce void make_line_program(text_submethod_type & text_ival,
				size_ctype lines, size_ctype code = GlyphCode::valid)
			{
				nik_ce size_type line = 0;

				text_ival[line][GlyphProg::instr] = GlyphInstr::program;
				text_ival[line][GlyphProg::lines] = lines;
				text_ival[line][GlyphProg::code ] = code;
			}

			nik_ce void make_line_routine(text_submethod_type & text_ival,
				size_ctype instr, size_ctype arity = 0, size_ctype local = 0)
			{
				nik_ce size_type line = 1;

				text_ival[line][GlyphRout::instr] = instr;
				text_ival[line][GlyphRout::arity] = arity;
				text_ival[line][GlyphRout::local] = local;
			}

			nik_ce void make_line_meta(text_submethod_type & text_ival,
				size_ctype bytes, size_ctype universe = 0)
			{
				nik_ce size_type line = 2;

				text_ival[line][GlyphMeta::instr   ] = GlyphInstr::push;
				text_ival[line][GlyphMeta::bytes   ] = bytes;
				text_ival[line][GlyphMeta::universe] = universe;
			}

			nik_ce void set_program_type(
				text_submethod_type & text_ival, size_ctype line, size_ctype mark, size_ctype index)
			{
				text_ival[line][GlyphNote::instr] = GlyphInstr::type;
				text_ival[line][GlyphNote::mark ] = mark;
				text_ival[line][GlyphNote::index] = index;
			}

			// text:

				using base::text_submethod;

				nik_ce auto text_submethod(icon_ctype_ref icon)
					{ return base::text_submethod(base::page_cmethod(icon.mark()), icon.index()); }

			// allocate:

				nik_ce auto allocate(page_method_type & page_ival, size_ctype mark, size_ctype n)
				{
					if (base::allocate(page_ival, n))
						{ return base::make_icon(mark, page_ival.max()); }
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

		protected:

			using page_cmethod_type		= typename base::page_cmethod_type;
			using text_csubmethod_type	= typename base::text_csubmethod_type;

		public:

			nik_ce glyph_builtin_cmethod_disjoint() : base{} { }
			nik_ce glyph_builtin_cmethod_disjoint(const facade & f) : base{f} { }
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

			using page_cmethod_type		= typename base::page_cmethod_type;
			using page_method_type		= typename base::page_method_type;

			using text_csubmethod_type	= typename base::text_csubmethod_type;
			using text_submethod_type	= typename base::text_submethod_type;

			nik_ces size_type row_length	= 3;
			nik_ces size_type length	= row_length * base::col_length;

		public:

			nik_ce glyph_builtin_method_disjoint() : base{} { }
			nik_ce glyph_builtin_method_disjoint(const facade & f) : base{f} { }

		protected:

			nik_ce void copy_program(text_submethod_type & text_ival, size_ctype instr, size_ctype bytes)
			{
				base::make_line_program (text_ival, row_length);
				base::make_line_routine (text_ival, instr);
				base::make_line_meta    (text_ival, bytes, 0);
			}

			nik_ce void instantiate(const page_method_type & page_ival,
				icon_type_ref icon, size_ctype instr, size_ctype bytes)
			{
				auto text_ival = base::text_submethod(page_ival, icon.index());
				text_ival      . set_dimension(row_length, base::col_length);

				copy_program(text_ival, instr, bytes);

				base::pop_page_if(page_ival, icon);
			}

		public:

			// declare:

				nik_ce auto declare(size_ctype instr, size_ctype bytes)
				{
					auto page_ival = base::page_method(BookMark::builtin);
					auto icon      = base::allocate(page_ival, BookMark::builtin, length);

					if (base::not_fail(icon)) { instantiate(page_ival, icon, instr, bytes); }

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

// composite:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class glyph_composite_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		protected:

			using page_cmethod_type		= typename base::page_cmethod_type;
			using text_csubmethod_type	= typename base::text_csubmethod_type;

			nik_ces size_type type_offset	= 3;

		public:

			nik_ce glyph_composite_cmethod_disjoint() : base{} { }
			nik_ce glyph_composite_cmethod_disjoint(const facade & f) : base{f} { }

			// sub(ordinate) icon:

				nik_ce auto sub_icon(icon_ctype_ref icon, size_ctype n) const
				{
					auto text_cival  = base::text_csubmethod(icon);
					size_ctype rows  = text_cival.cat(GlyphProg::lines); // optimization.
					text_cival       . set_dimension(rows, base::col_length);

					size_ctype row   = n + type_offset;
					size_ctype mark  = text_cival[row][GlyphNote::mark ];
					size_ctype index = text_cival[row][GlyphNote::index];

					return base::make_icon(mark, index);
				}
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class glyph_composite_method_disjoint : public Base
	{
		public:

			using base			= Base;
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

		public:

			nik_ce glyph_composite_method_disjoint() : base{} { }
			nik_ce glyph_composite_method_disjoint(const facade & f) : base{f} { }

		protected:

			template<size_type Instr, typename T>
			nik_ce void copy_program(text_submethod_type & text_ival,
				size_ctype row_length, const T & v, size_ctype bytes, size_ctype universe)
			{
				base::make_line_program (text_ival, row_length);
				base::make_line_routine (text_ival, Instr);
				base::make_line_meta    (text_ival, bytes, universe);
			}

			template<size_type Instr, typename T>
			nik_ce void instantiate(const page_method_type & page_ival, icon_type_ref icon,
				size_ctype row_length, const T & v, size_ctype bytes, size_ctype universe)
			{
				auto text_ival = base::text_submethod(page_ival, icon.index());
				text_ival      . set_dimension(row_length, base::col_length);

				copy_program<Instr>(text_ival, row_length, v, bytes, universe);

				size_type line = 3;
				for (auto k = v.cbegin(); k != v.cend(); ++k, ++line)
					{ base::set_program_type(text_ival, line, k->mark(), k->index()); }

				base::pop_page_if(page_ival, icon);
			}

		public:

			template<size_type Mark, size_type Instr, typename T>
			nik_ce auto declare_type(const T & v, size_ctype bytes, size_ctype universe)
			{
				auto page_ival    = base::page_method(Mark);
				size_ctype rows   = v.size() + 3;
				size_ctype length = rows * base::col_length;
				auto icon         = base::allocate(page_ival, Mark, length);

				if (base::not_fail(icon))
					{ instantiate<Instr>(page_ival, icon, rows, v, bytes, universe); }

				return icon;
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class glyph_tuple_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		public:

			nik_ce glyph_tuple_cmethod_disjoint() : base{} { }
			nik_ce glyph_tuple_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using glyph_tuple_cmethod =
			glyph_tuple_cmethod_disjoint     <
			glyph_composite_cmethod_disjoint <
			glyph_cmethod_disjoint           < Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class glyph_tuple_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		public:

			nik_ce glyph_tuple_method_disjoint() : base{} { }
			nik_ce glyph_tuple_method_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using glyph_tuple_method =
			glyph_tuple_method_disjoint      <
			glyph_tuple_cmethod_disjoint     <
			glyph_composite_method_disjoint  <
			glyph_composite_cmethod_disjoint <
			glyph_method_disjoint            <
			glyph_cmethod_disjoint           < Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cotuple:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class glyph_cotuple_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		public:

			nik_ce glyph_cotuple_cmethod_disjoint() : base{} { }
			nik_ce glyph_cotuple_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using glyph_cotuple_cmethod =
			glyph_cotuple_cmethod_disjoint   <
			glyph_composite_cmethod_disjoint <
			glyph_cmethod_disjoint           < Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class glyph_cotuple_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		public:

			nik_ce glyph_cotuple_method_disjoint() : base{} { }
			nik_ce glyph_cotuple_method_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using glyph_cotuple_method =
			glyph_cotuple_method_disjoint    <
			glyph_cotuple_cmethod_disjoint   <
			glyph_composite_method_disjoint  <
			glyph_composite_cmethod_disjoint <
			glyph_method_disjoint            <
			glyph_cmethod_disjoint           < Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// function:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class glyph_function_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		public:

			nik_ce glyph_function_cmethod_disjoint() : base{} { }
			nik_ce glyph_function_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using glyph_function_cmethod =
			glyph_function_cmethod_disjoint  <
			glyph_composite_cmethod_disjoint <
			glyph_cmethod_disjoint           < Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class glyph_function_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		public:

			nik_ce glyph_function_method_disjoint() : base{} { }
			nik_ce glyph_function_method_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using glyph_function_method =
			glyph_function_method_disjoint   <
			glyph_function_cmethod_disjoint  <
			glyph_composite_method_disjoint  <
			glyph_composite_cmethod_disjoint <
			glyph_method_disjoint            <
			glyph_cmethod_disjoint           < Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// list:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class glyph_list_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		protected:

			nik_ces size_type row_length	= 4;
			nik_ces size_type length	= row_length * base::col_length;

		public:

			nik_ce glyph_list_cmethod_disjoint() : base{} { }
			nik_ce glyph_list_cmethod_disjoint(const facade & f) : base{f} { }

			// sub(ordinate) icon:

				nik_ce auto sub_icon(icon_ctype_ref icon) const
				{
					auto text_cival  = base::text_csubmethod(icon);
					text_cival       . set_dimension(row_length, base::col_length);

					size_ctype mark  = text_cival[3][GlyphNote::mark ];
					size_ctype index = text_cival[3][GlyphNote::index];

					return base::make_icon(mark, index);
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using glyph_list_cmethod =
			glyph_list_cmethod_disjoint <
			glyph_cmethod_disjoint      < Facade >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class glyph_list_method_disjoint : public Base
	{
		public:

			using base			= Base;
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

		public:

			nik_ce glyph_list_method_disjoint() : base{} { }
			nik_ce glyph_list_method_disjoint(const facade & f) : base{f} { }

		protected:

			nik_ce void copy_program(text_submethod_type & text_ival, icon_ctype_ref sub_icon)
			{
				size_ctype bytes = 17; // update using sub_icon.

				base::make_line_program (text_ival, base::row_length);
				base::make_line_routine (text_ival, GlyphInstr::list);
				base::make_line_meta    (text_ival, bytes, 0);
			}

			nik_ce void instantiate(
				const page_method_type & page_ival, icon_type_ref icon, icon_ctype_ref sub_icon)
			{
				auto text_ival = base::text_submethod(page_ival, icon.index());
				text_ival      . set_dimension(base::row_length, base::col_length);

				copy_program(text_ival, sub_icon);
				text_ival[3][GlyphNote::instr] = GlyphInstr::type;

				base::pop_page_if(page_ival, icon);
			}

		public:

			// declare:

				nik_ce auto declare(icon_ctype_ref sub_icon)
				{
					auto page_ival = base::page_method(BookMark::recurse);
					auto icon      = base::allocate(page_ival, BookMark::recurse, base::length);

					if (base::not_fail(icon)) { instantiate(page_ival, icon, sub_icon); }

					return icon;
				}

			// recurse:

				nik_ce void recurse(icon_ctype_ref icon, icon_ctype_ref sub_icon)
				{
					auto text_ival = base::text_submethod(icon);
					text_ival      . set_dimension(base::row_length, base::col_length);

					text_ival[3][GlyphNote::mark ] = sub_icon.mark ();
					text_ival[3][GlyphNote::index] = sub_icon.index();
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using glyph_list_method =
			glyph_list_method_disjoint  <
			glyph_list_cmethod_disjoint <
			glyph_method_disjoint       <
			glyph_cmethod_disjoint      < Facade >>>>;

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

