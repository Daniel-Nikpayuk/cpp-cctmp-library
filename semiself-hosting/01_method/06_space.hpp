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

// space:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// concord:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class space_cmethod_disjoint : public Base
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

			nik_ces size_type row_custom	= 1;
			nik_ces size_type row_overt	= 2;
			nik_ces size_type row_length	= 3;
			nik_ces size_type length	= row_length * base::col_length;

		public:

			nik_ce space_cmethod_disjoint() : base{} { }
			nik_ce space_cmethod_disjoint(const facade & f) : base{f} { }

			// sub(ordinate) icon:

				nik_ce auto sub_icon(icon_ctype_ref icon) const
					{ return base::glyph_sub_icon(icon, row_custom); }

				nik_ce auto overt_icon(icon_ctype_ref icon) const
					{ return base::glyph_sub_icon(icon, row_overt); }
	};

	// syntactic sugar:

		template<typename Facade>
		using space_cmethod =
			space_cmethod_disjoint   <
			concord_cmethod_disjoint < Facade >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class space_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using mode_type			= typename base::mode_type;
			using mode_ctype_ref		= typename base::mode_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype		= typename base::sign_ctype;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce space_method_disjoint() : base{} { }
			nik_ce space_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_space() { return base::glyph_declare_space(); }

				nik_ce auto declare_type(size_ctype space, icon_ctype_ref sub_icon)
				{
					auto field = base::template glyph_make_field<base::length>();
					auto table = base::template glyph_make_table<base::length>
							(field, base::row_length, base::col_length);

					size_ctype custom_mark  = sub_icon.mark ();
					size_ctype custom_index = sub_icon.index();

					size_ctype overt_mark   = sub_icon.mark (); // update.
					size_ctype overt_index  = sub_icon.index(); // update.

					base::glyph_set_program (table, base::row_length);
					base::glyph_set_note    (table, base::row_custom, custom_mark, custom_index);
					base::glyph_set_note    (table, base::row_overt, overt_mark, overt_index);

					auto icon = base::glyph_declare(space, field);

					return mode_type{icon.mark(), icon.index()};
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using space_method =
			space_method_disjoint    <
			space_cmethod_disjoint   <
			concord_method_disjoint  <
			concord_cmethod_disjoint < Facade >>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

