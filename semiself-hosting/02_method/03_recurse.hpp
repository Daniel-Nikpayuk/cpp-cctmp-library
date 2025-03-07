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

// recurse:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// concord:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class recurse_cmethod_disjoint : public Base
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

			using empty_cmethod_type	= resolve_cmethod<model_type,   empty_cmethod>;
			using tuple_cmethod_type	= resolve_cmethod<model_type,   tuple_cmethod>;
			using cotuple_cmethod_type	= resolve_cmethod<model_type, cotuple_cmethod>;

			empty_cmethod_type     empty_cmethod;
			tuple_cmethod_type     tuple_cmethod;
			cotuple_cmethod_type cotuple_cmethod;

		public:

			nik_ce recurse_cmethod_disjoint() : base{} { }
			nik_ce recurse_cmethod_disjoint(const facade & f) :
				base{f},
				empty_cmethod   { base::model->template cequip<  empty_cmethod_type>() },
				tuple_cmethod   { base::model->template cequip<  tuple_cmethod_type>() },
				cotuple_cmethod { base::model->template cequip<cotuple_cmethod_type>() }
				{ }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class recurse_method_disjoint : public Base
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

			using empty_method_type		= resolve_method<model_type,   empty_method>;
			using tuple_method_type		= resolve_method<model_type,   tuple_method>;
			using cotuple_method_type	= resolve_method<model_type, cotuple_method>;

			empty_method_type     empty_method;
			tuple_method_type     tuple_method;
			cotuple_method_type cotuple_method;

		public:

			nik_ce recurse_method_disjoint() : base{} { }
			nik_ce recurse_method_disjoint(const facade & f) :
				base{f},
				empty_method   { base::model->template equip<  empty_method_type>() },
				tuple_method   { base::model->template equip<  tuple_method_type>() },
				cotuple_method { base::model->template equip<cotuple_method_type>() }
				{ }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// list:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class list_cmethod_disjoint : public Base
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

			nik_ces size_type point_length	= 2;
			nik_ces size_type row_length	= 4;
			nik_ces size_type length	= row_length * base::col_length;

			nik_ce auto tuple_sign(sign_ctype_ref sign) const
				{ return base::cotuple_cmethod.sub_sign(sub_sign(sign)); }

		public:

			nik_ce list_cmethod_disjoint() : base{} { }
			nik_ce list_cmethod_disjoint(const facade & f) : base{f} { }

			// sub(ordinate) icon:

				nik_ce auto sub_icon(icon_ctype_ref icon) const
					{ return base::glyph_sub_icon(icon, base::row_body); }

			// sub(ordinate) sign:

				nik_ce auto sub_sign(sign_ctype_ref sign) const
				{
					auto record_cival = base::record_ctext(sign, ImageList::point, point_length);

					return sign_type{record_cival[0], record_cival[1]};
				}

				nik_ce auto car_sign(sign_ctype_ref sign) const
					{ return base::tuple_cmethod.sub_sign(tuple_sign(sign), 0); }

				nik_ce auto cdr_sign(sign_ctype_ref sign) const
					{ return base::tuple_cmethod.sub_sign(tuple_sign(sign), 1); }

				nik_ce auto cdr_sign(sign_type sign, size_type n) const
				{
					for (; n; --n) { sign = cdr_sign(sign); }

					return sign;
				}

				nik_ce auto car_sign(sign_type sign, size_type n) const
					{ return car_sign(cdr_sign(sign, n)); }
	};

	// syntactic sugar:

		template<typename Facade>
		using list_cmethod =
			list_cmethod_disjoint    <
			recurse_cmethod_disjoint <
			concord_cmethod_disjoint < Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class list_method_disjoint : public Base
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

			nik_ce auto declare_this_icon()
			{
				auto field = base::template glyph_make_field<base::length>();
				auto table = base::template glyph_make_table<base::length>
						(field, base::row_length, base::col_length);

				size_ctype bytes = 0; // update.

				base::glyph_set_program (table, base::row_length);
				base::glyph_set_routine (table, GlyphInstr::list);
				base::glyph_set_meta    (table, bytes);

				return base::glyph_declare(BookMark::recurse, field);
			}

			nik_ce void recurse_type(icon_ctype_ref icon, icon_ctype_ref sub_icon)
			{
				auto text_ival   = base::glyph_text(icon);
				size_ctype mark  = sub_icon.mark ();
				size_ctype index = sub_icon.index();

				base::glyph_set_note(text_ival, base::row_body, mark, index);
			}

			nik_ce auto declare_meta(icon_ctype_ref icon, size_ctype point)
			{
				auto field = base::template image_make_field<ImageList::dimension>();
				field      . fullsize();

				field[ImageList::index] = icon.index();
				field[ImageList::units] = 0;// update. base::image_max_units(sign_array);
				field[ImageList::point] = point;

				return base::image_declare(BookMark::recurse, field);
			}

			nik_ce auto declare_value(icon_ctype_ref icon)
			{
				size_ctype length = base::point_length;
				size_ctype point  = base::record().expand(base::point_length);
							// only expand if not duplicate.

				return declare_meta(icon, point);
			}

			nik_ce auto define_value(sign_ctype_ref sign, sign_ctype_ref sub_sign)
			{
				auto record_ival = base::record_text(sign, ImageList::point, base::point_length);
				record_ival[0]   = sub_sign.mark ();
				record_ival[1]   = sub_sign.index();

				return sign;
			}

		public:

			nik_ce list_method_disjoint() : base{} { }
			nik_ce list_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_type(icon_ctype_ref icon)
				{
					auto this_icon    = declare_this_icon();
					auto empty_icon   = base::empty_method  .declare_type();
					auto tuple_icon   = base::tuple_method  .declare_type({       icon ,  this_icon });
					auto cotuple_icon = base::cotuple_method.declare_type({ empty_icon , tuple_icon });

					recurse_type(this_icon, cotuple_icon);

					return this_icon;
				}

			// define:

				nik_ce auto define_value(icon_ctype_ref icon, sign_ctype_ref e)
				{
					auto cotuple_icon = base::sub_icon(icon);

					auto cotuple_sign = base::cotuple_method.define_value(cotuple_icon, 0, e);
					auto sign         = declare_value(icon);

					define_value(sign, cotuple_sign);

					return sign;
				}

				nik_ce auto define_value(icon_ctype_ref icon, sign_ctype_ref a, sign_ctype_ref d)
				{
					auto cotuple_icon = base::sub_icon(icon);
					auto tuple_icon   = base::cotuple_method.sub_icon(cotuple_icon, 1);

					auto tuple_sign   = base::tuple_method.define_value(tuple_icon, { a, d });
					auto cotuple_sign = base::cotuple_method.
								define_value(cotuple_icon, 1, tuple_sign);
					auto sign         = declare_value(icon);

					define_value(sign, cotuple_sign);

					return sign;
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using list_method =
			list_method_disjoint     <
			list_cmethod_disjoint    <
			recurse_method_disjoint  <
			recurse_cmethod_disjoint <
			concord_method_disjoint  <
			concord_cmethod_disjoint < Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

