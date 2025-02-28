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

// composite:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// glyph:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class glyph_space_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		protected:

			nik_ces size_type row_length	= 2;
			nik_ces size_type length	= row_length * base::col_length;

		public:

			nik_ce glyph_space_cmethod_disjoint() : base{} { }
			nik_ce glyph_space_cmethod_disjoint(const facade & f) : base{f} { }

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
		using glyph_space_cmethod =
			glyph_space_cmethod_disjoint <
			glyph_cmethod_disjoint       < Facade >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class glyph_space_method_disjoint : public Base
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

			nik_ce glyph_space_method_disjoint() : base{} { }
			nik_ce glyph_space_method_disjoint(const facade & f) : base{f} { }

		protected:

			nik_ce void copy_program(text_submethod_type & text_ival, icon_ctype_ref sub_icon)
			{
				base::make_line_program(text_ival, base::row_length);

				text_ival[1][GlyphNote::instr] = GlyphInstr::custom;
				text_ival[1][GlyphNote::mark ] = sub_icon.mark ();
				text_ival[1][GlyphNote::index] = sub_icon.index();
			}

			nik_ce void instantiate(
				const page_method_type & page_ival, icon_type_ref icon, icon_ctype_ref sub_icon)
			{
				auto text_ival = base::text_submethod(page_ival, icon.index());
				text_ival      . set_dimension(base::row_length, base::col_length);

				copy_program(text_ival, sub_icon);
			}

		public:

			// declare:

				nik_ce size_type declare_space() { return base::page().expand(); }

				nik_ce auto declare(size_ctype space, icon_ctype_ref sub_icon)
				{
					auto page_ival = base::page_method(space);
					auto icon      = base::allocate(page_ival, space, base::length);

					if (base::not_fail(icon)) { instantiate(page_ival, icon, sub_icon); }

					return icon;
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using glyph_space_method =
			glyph_space_method_disjoint  <
			glyph_space_cmethod_disjoint <
			glyph_method_disjoint        <
			glyph_cmethod_disjoint       < Facade >>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// image:

/***********************************************************************************************************************/

// immutable (symbolic):

	template<typename Base>
	class image_space_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

		public:

			nik_ce image_space_cmethod_disjoint() : base{} { }
			nik_ce image_space_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using image_space_cmethod =
			image_space_cmethod_disjoint <
			image_cmethod_disjoint       < Facade >>;

/***********************************************************************************************************************/

// mutable (symbolic):

	template<typename Base>
	class image_space_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

		public:

			nik_ce image_space_method_disjoint() : base{} { }
			nik_ce image_space_method_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using image_space_method =
			image_space_method_disjoint  <
			image_space_cmethod_disjoint <
			image_method_disjoint        <
			image_cmethod_disjoint       < Facade >>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// symbol:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class symbol_space_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce symbol_space_cmethod_disjoint() : base{} { }
			nik_ce symbol_space_cmethod_disjoint(const facade & f) : base{f} { }

			// sub(ordinate) icon:

				nik_ce auto sub_icon(icon_ctype_ref icon) const
					{ return base::glyph_cmethod().sub_icon(icon); }
	};

	// syntactic sugar:

		template<typename Facade>
		using symbol_space_cmethod =
			symbol_space_cmethod_disjoint <
			corpus_cmethod_disjoint       < glyph_space_cmethod , image_space_cmethod , Facade >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class symbol_space_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce symbol_space_method_disjoint() : base{} { }
			nik_ce symbol_space_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_space() { return base::glyph_method().declare_space(); }

				nik_ce auto declare_type(size_ctype space, icon_ctype_ref sub_icon)
					{ return base::glyph_method().declare(space, sub_icon); }
	};

	// syntactic sugar:

		template<typename Facade>
		using symbol_space_method =
			symbol_space_method_disjoint  <
			symbol_space_cmethod_disjoint <
			corpus_method_disjoint        < glyph_space_method  , image_space_method  ,
			corpus_cmethod_disjoint       < glyph_space_cmethod , image_space_cmethod , Facade >>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// concord:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class concord_space_cmethod_disjoint : public Base
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

			using tuple_cmethod_type	= resolve_cmethod<model_type, concord_tuple_cmethod>;
			using cotuple_cmethod_type	= resolve_cmethod<model_type, concord_cotuple_cmethod>;

			tuple_cmethod_type   tuple_cmethod;
			cotuple_cmethod_type cotuple_cmethod;

		protected:

			nik_ce auto tuple_sign(sign_ctype_ref sign) const
				{ return cotuple_cmethod.sub_sign(sub_sign(sign)); }

		public:

			nik_ce concord_space_cmethod_disjoint() : base{} { }
			nik_ce concord_space_cmethod_disjoint(const facade & f) :
				base{f},
				tuple_cmethod   { base::model->template cequip<tuple_cmethod_type  >() },
				cotuple_cmethod { base::model->template cequip<cotuple_cmethod_type>() }
				{ }

			// sub(ordinate) icon:

				nik_ce auto sub_icon(icon_ctype_ref icon) const
					{ return base::symbol_cmethod().sub_icon(icon); }

			// sub(ordinate) sign:

				nik_ce auto sub_sign(sign_ctype_ref sign) const
				{
					auto text_cival   = base::image_ctext(sign);
					size_ctype start  = text_cival[ImageList::point];
					size_ctype finish = start + 2;
					auto record_cival = base::record_csubmethod();
					record_cival      . mid_set(start, finish);

					return base::symbol_cmethod().
						image_cmethod().make_sign(record_cival[0], record_cival[1]);
				}

				nik_ce auto car_sign(sign_ctype_ref sign) const
					{ return tuple_cmethod.sub_sign(tuple_sign(sign), 0); }

				nik_ce auto cdr_sign(sign_ctype_ref sign) const
					{ return tuple_cmethod.sub_sign(tuple_sign(sign), 1); }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_space_cmethod =
			concord_space_cmethod_disjoint <
			concord_cmethod_disjoint       < symbol_space_cmethod , array_csubmethod , Facade >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_space_method_disjoint : public Base
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

		public:

			nik_ce concord_space_method_disjoint() : base{} { }
			nik_ce concord_space_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_space() { return base::symbol_method().declare_space(); }

				nik_ce auto declare_type(size_ctype space, icon_ctype_ref sub_icon)
					{ return base::symbol_method().declare_type(space, sub_icon); }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_space_method =
			concord_space_method_disjoint  <
			concord_space_cmethod_disjoint <
			concord_method_disjoint        < symbol_space_method  , array_submethod  ,
			concord_cmethod_disjoint       < symbol_space_cmethod , array_csubmethod , Facade >>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

