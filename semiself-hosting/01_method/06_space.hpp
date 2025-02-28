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

			using tuple_cmethod_type	= resolve_cmethod<model_type, tuple_cmethod>;
			using cotuple_cmethod_type	= resolve_cmethod<model_type, cotuple_cmethod>;

			tuple_cmethod_type   tuple_cmethod;
			cotuple_cmethod_type cotuple_cmethod;

		protected:

			nik_ce auto tuple_sign(sign_ctype_ref sign) const
				{ return cotuple_cmethod.sub_sign(sub_sign(sign)); }

		public:

			nik_ce space_cmethod_disjoint() : base{} { }
			nik_ce space_cmethod_disjoint(const facade & f) :
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

			using sign_type			= typename base::sign_type;
			using sign_ctype		= typename base::sign_ctype;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce space_method_disjoint() : base{} { }
			nik_ce space_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_space() { return base::symbol_method().declare_space(); }

				nik_ce auto declare_type(size_ctype space, icon_ctype_ref sub_icon)
					{ return base::symbol_method().declare_type(space, sub_icon); }
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

