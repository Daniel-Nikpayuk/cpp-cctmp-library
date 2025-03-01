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

// concord:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class composite_cmethod_disjoint : public Base
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

			nik_ce composite_cmethod_disjoint() : base{} { }
			nik_ce composite_cmethod_disjoint(const facade & f) : base{f} { }

			// sub(ordinate) icon:

				nik_ce auto sub_icon(icon_ctype_ref icon, size_ctype n) const
					{ return base::glyph_sub_icon(icon, n); }

				nik_ce auto sub_icon(sign_ctype_ref sign, size_ctype n) const
					{ return base::glyph_sub_icon(sign, n); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class composite_method_disjoint : public Base
	{
		public:

			using base					= Base;
			using facade					= typename base::facade;
			using model_type				= typename base::model_type;

			nik_using_size_type_scope			(base)

			using icon_type					= typename base::icon_type;
			using icon_ctype_ref				= typename base::icon_ctype_ref;

			using sign_type					= typename base::sign_type;
			using sign_ctype				= typename base::sign_ctype;
			using sign_ctype_ref				= typename base::sign_ctype_ref;

		protected:

			template<size_type N> using icon_array_type	= array<icon_type, size_type, N>;
			template<size_type N> using sign_array_type	= array<sign_type, size_type, N>;

			// declare:

				template<typename T>
				nik_ce auto declare_type(
					size_ctype mark, size_ctype instr, size_ctype bytes, const T & icon_array)
				{
					nik_ce auto row_length = static_cast<size_type>(base::row_body + T::length());
					nik_ce auto length     = static_cast<size_type>(row_length * base::col_length);
					auto field             = base::template glyph_make_field<length>();
					auto table             = base::template glyph_make_table<length>
									(field, row_length, base::col_length);

					base::glyph_set_program (table, row_length);
					base::glyph_set_routine (table, instr);
					base::glyph_set_meta    (table, bytes, base::glyph_max_universe(icon_array));

					size_type line = base::row_body;
					for (auto k = icon_array.cbegin(); k != icon_array.cend(); ++k, ++line)
						{ base::glyph_set_note(table, line, k->mark(), k->index()); }

					return base::glyph_declare(mark, field);
				}

			// define:

				template<typename Record, typename T>
				nik_ce void define_abstract(Record & ival, const T & sign_array)
				{
					for (size_type k = 0; k != sign_array.size(); ++k)
					{
						ival[2*k  ] = sign_array[k].mark ();
						ival[2*k+1] = sign_array[k].index();
					}
				}

		public:

			nik_ce composite_method_disjoint() : base{} { }
			nik_ce composite_method_disjoint(const facade & f) : base{f} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class tuple_cmethod_disjoint : public Base
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

			nik_ce tuple_cmethod_disjoint() : base{} { }
			nik_ce tuple_cmethod_disjoint(const facade & f) : base{f} { }

			// sub(ordinate) sign:

				nik_ce auto sub_sign(sign_ctype_ref sign, size_ctype n) const
				{
					auto text_cival   = base::image_ctext(sign);
					size_ctype length = text_cival[ImageTuple::length];
					auto record_cival = base::record_ctext(text_cival, ImageTuple::point, length);
					size_ctype pos    = (n << 1);

					return sign_type{record_cival[pos], record_cival[pos+1]};
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using tuple_cmethod =
			tuple_cmethod_disjoint     <
			composite_cmethod_disjoint <
			concord_cmethod_disjoint   < Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class tuple_method_disjoint : public Base
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

			template<typename T>
			nik_ce auto declare_meta(icon_ctype_ref icon,
				size_ctype time, size_ctype length, size_ctype point, const T & sign_array)
			{
				auto field = base::template image_make_field<ImageTuple::dimension>();
				field      . fullsize();

				field[ImageTuple::index ] = icon.index();
				field[ImageTuple::time  ] = time;
				field[ImageTuple::units ] = base::image_total_units(sign_array);
				field[ImageTuple::length] = length;
				field[ImageTuple::point ] = point;

				return base::image_declare(BookMark::tuple, field);
			}

			template<typename T> // needs to type check.
			nik_ce auto declare_abstract(icon_ctype_ref icon, size_ctype length, const T & sign_array)
			{
				size_ctype point = base::record().expand(length);
							// only expand if not duplicate.

				return declare_meta(icon, ImageTime::abstract, length, point, sign_array);
			}

		public:

			nik_ce tuple_method_disjoint() : base{} { }
			nik_ce tuple_method_disjoint(const facade & f) : base{f} { }

			// declare:

				template<auto N>
				nik_ce auto declare_type(const icon_type (&t)[N])
				{
					auto icon_array  = typename base::template icon_array_type<N>{t};
					size_ctype bytes = base::glyph_total_bytes(icon_array);

					return base::declare_type(
						BookMark::tuple, GlyphInstr::tuple, bytes, icon_array);
				}

			//	nik_ce auto declare_concrete(icon_ctype_ref icon, size_ctype l_adder, size_ctype addr)
			//		{ return declare_image(icon, ImageTime::concrete, l_adder, addr); }

			// define:

				template<auto N>
				nik_ce auto define_abstract(icon_ctype_ref icon, sign_ctype (&v)[N])
				{
					auto sign_array   = typename base::template sign_array_type<N>{v};

					size_ctype length = (N << 1);
					auto sign         = declare_abstract(icon, length, sign_array);
					auto record_ival  = base::record_text(sign, ImageTuple::point, length);

					base::define_abstract(record_ival, sign_array);

					return sign;
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using tuple_method =
			tuple_method_disjoint      <
			tuple_cmethod_disjoint     <
			composite_method_disjoint  <
			composite_cmethod_disjoint <
			concord_method_disjoint    <
			concord_cmethod_disjoint   < Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cotuple:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class cotuple_cmethod_disjoint : public Base
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

			nik_ces size_type length	= 2;

		public:

			nik_ce cotuple_cmethod_disjoint() : base{} { }
			nik_ce cotuple_cmethod_disjoint(const facade & f) : base{f} { }

			// sub(ordinate) sign:

				nik_ce auto sub_sign(sign_ctype_ref sign) const
				{
					auto record_cival = base::record_ctext(sign, ImageTuple::point, length);

					return sign_type{record_cival[0], record_cival[1]};
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using cotuple_cmethod =
			cotuple_cmethod_disjoint   <
			composite_cmethod_disjoint <
			concord_cmethod_disjoint   < Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class cotuple_method_disjoint : public Base
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

			template<typename T>
			nik_ce auto declare_meta(icon_ctype_ref icon,
				size_ctype time, size_ctype inject, size_ctype point, const T & sign_array)
			{
				auto field = base::template image_make_field<ImageCotuple::dimension>();
				field      . fullsize();

				field[ImageCotuple::index ] = icon.index();
				field[ImageCotuple::time  ] = time;
				field[ImageCotuple::units ] = base::image_max_units(sign_array);
				field[ImageCotuple::inject] = inject;
				field[ImageCotuple::point ] = point;

				return base::image_declare(BookMark::cotuple, field);
			}

			template<typename T>
			nik_ce auto declare_abstract(icon_ctype_ref icon, const T & sign_array)
			{
				size_ctype inject = base::record().expand(1);
				size_ctype point  = base::record().expand(base::length);
							// only expand if not duplicate.

				return declare_meta(icon, ImageTime::abstract, inject, point, sign_array);
			}

		public:

			nik_ce cotuple_method_disjoint() : base{} { }
			nik_ce cotuple_method_disjoint(const facade & f) : base{f} { }

			// declare:

				template<auto N>
				nik_ce auto declare_type(const icon_type (&t)[N])
				{
					auto icon_array  = typename base::template icon_array_type<N>{t};
					size_ctype bytes = base::glyph_max_bytes(icon_array);

					return base::declare_type(
						BookMark::cotuple, GlyphInstr::cotuple, bytes, icon_array);
				}

			//	nik_ce auto declare_concrete(icon_ctype_ref icon, size_ctype inject, size_ctype addr)
			//		{ return declare_image(icon, ImageTime::concrete, inject, addr); }

			// define:

				nik_ce auto define_abstract(icon_ctype_ref icon, size_ctype inject, sign_ctype_ref s)
				{
					auto sign_array  = typename base::template sign_array_type<base::length>{{s}};
					auto sign        = declare_abstract(icon, sign_array);

					auto text_cival  = base::image_ctext(sign);
					base::record()   . copy(text_cival[ImageCotuple::inject], inject);
					auto record_ival = base::record_text(text_cival, ImageCotuple::point, base::length);

					base::define_abstract(record_ival, sign_array);

					return sign;
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using cotuple_method =
			cotuple_method_disjoint    <
			cotuple_cmethod_disjoint   <
			composite_method_disjoint  <
			composite_cmethod_disjoint <
			concord_method_disjoint    <
			concord_cmethod_disjoint   < Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

