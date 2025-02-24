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

// concord class:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// concord:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// model:

	template<typename> class concord_cfacade;
	template<typename> class concord_facade;

/***********************************************************************************************************************/

// mutable:

	template
	<
		typename Type, typename SizeType,
		typename GlyphPack, typename SpacePack, typename ImagePack,
		SizeType Size
	>
	class concord
	{
		public:

			using facade			= concord; // method compatible.
			using cfacade_type		= concord_cfacade<concord>;
			using facade_type		= concord_facade<concord>;

			using symbol_type		= corpus<SizeType, SizeType, GlyphPack, SpacePack, ImagePack>;
			using symbol_type_ptr		= typename alias<symbol_type>::type_ptr;
			using symbol_ctype_ptr		= typename alias<symbol_type>::ctype_ptr;

			using record_type		= array<Type, SizeType, Size>;
			using record_type_ptr		= typename alias<record_type>::type_ptr;
			using record_ctype_ptr		= typename alias<record_type>::ctype_ptr;

			nik_using_name_scope_type	( type, record_type)
			nik_using_name_scope_ctype	(ctype, record_type)

			nik_using_size_type_scope	(record_type)

		public:

			template<template<typename> typename CMethod>
			using symbol_cmethod_type = resolve_cmethod<symbol_type, CMethod>;

			template<template<typename> typename Method>
			using symbol_method_type = resolve_method<symbol_type, Method>;

			template<template<typename> typename CMethod>
			using record_csubmethod_type = resolve_csubmethod<record_type, CMethod>;

			template<template<typename> typename Method>
			using record_submethod_type = resolve_submethod<record_type, Method>;

		protected:

			symbol_type _symbol;
			record_type _record;
			size_type   _memory; // optimization: by design is a member array of the logic class.

		public:

			nik_ce concord() : _memory{} { }

			// equip:

				template<typename CMethod>
				nik_ce auto cequip() const -> CMethod
					{ return cfacade_type{static_cast<concord const*>(this)}; }

				template<typename Method>
				nik_ce auto equip() -> Method
					{ return facade_type{static_cast<concord*>(this)}; }

			// symbol:

				nik_ce symbol_ctype_ptr csymbol() const { return &_symbol; }
				nik_ce  symbol_type_ptr  symbol()       { return &_symbol; }

				template<typename CMethod>
				nik_ce auto symbol_cequip() const { return _symbol.template cequip<CMethod>(); }

				template<typename Method>
				nik_ce auto symbol_equip() { return _symbol.template equip<Method>(); }

			// record:

				nik_ce record_ctype_ptr crecord() const { return &_record; }
				nik_ce  record_type_ptr  record()       { return &_record; }

				template<typename CMethod>
				nik_ce auto record_csubequip() const { return _record.template csubequip<CMethod>(); }

				template<typename Method>
				nik_ce auto record_subequip() { return _record.template subequip<Method>(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// facade:

/***********************************************************************************************************************/

// immutable:

	template<typename Model>
	class concord_cfacade
	{
		public:

			using facade			= concord_cfacade; // method compatible.

			using model_type		= Model;
			using model_ctype_ptr		= typename alias<model_type>::ctype_ptr;
			using model_ctype_cptr		= typename alias<model_type>::ctype_cptr;

			using symbol_type		= typename model_type::symbol_type;
			using symbol_ctype_ref		= typename alias<symbol_type>::ctype_ref;

			using record_type		= typename model_type::record_type;
			using record_ctype_ref		= typename alias<record_type>::ctype_ref;

			nik_using_size_type_scope	(model_type)

		protected:

			model_ctype_ptr model;

		public:

			nik_ce concord_cfacade() : model{} { }
			nik_ce concord_cfacade(model_ctype_cptr m) : model{m} { }

			// symbol:

				nik_ce symbol_ctype_ref csymbol() const { return *model->csymbol(); }

			// record:

				nik_ce record_ctype_ref crecord() const { return *model->crecord(); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Model>
	class concord_facade
	{
		public:

			using facade			= concord_facade; // method compatible.

			using model_type		= Model;
			using model_type_ptr		= typename alias<model_type>::type_ptr;
			using model_type_cptr		= typename alias<model_type>::type_cptr;

			using symbol_type		= typename model_type::symbol_type;
			using symbol_type_ref		= typename alias<symbol_type>::type_ref;
			using symbol_ctype_ref		= typename alias<symbol_type>::ctype_ref;

			using record_type		= typename model_type::record_type;
			using record_type_ref		= typename alias<record_type>::type_ref;
			using record_ctype_ref		= typename alias<record_type>::ctype_ref;

			nik_using_size_type_scope	(model_type)

		protected:

			model_type_ptr model;

		public:

			nik_ce concord_facade() : model{} { }
			nik_ce concord_facade(model_type_cptr m) : model{m} { }

			// symbol:

				nik_ce symbol_ctype_ref csymbol() const { return *model->csymbol(); }
				nik_ce  symbol_type_ref  symbol()       { return *model-> symbol(); }

			// record:

				nik_ce record_ctype_ref crecord() const { return *model->crecord(); }
				nik_ce  record_type_ref  record()       { return *model-> record(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// method:

/***********************************************************************************************************************/

// immutable:

	template<template<typename> typename SymbolCMethod, template<typename> typename RecordCMethod, typename Base>
	class concord_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= icon<size_type>;
			using icon_ctype_ref		= typename alias<icon_type>::ctype_ref;

			using sign_type			= sign<size_type>;
			using sign_ctype		= typename alias<sign_type>::ctype;
			using sign_ctype_ref		= typename alias<sign_type>::ctype_ref;

		protected:

			using symbol_cmethod_type	= typename model_type::template
								symbol_cmethod_type<SymbolCMethod>;
			using record_csubmethod_type	= typename model_type::template
								record_csubmethod_type<RecordCMethod>;

		public:

			nik_ce concord_cmethod_disjoint() : base{} { }
			nik_ce concord_cmethod_disjoint(const facade & f) : base{f} { }

			// symbol:

				nik_ce auto symbol_cmethod() const
					{ return base::model->template symbol_cequip<symbol_cmethod_type>(); }

				nik_ce auto type(sign_ctype_ref sign) { return symbol_cmethod().to_icon(sign); }

			// (glyph):

				nik_ce auto glyph_ctext(icon_ctype_ref icon) const
					{ return symbol_cmethod().glyph_ctext(icon); }

				nik_ce auto glyph_ctext(sign_ctype_ref sign) const
					{ return symbol_cmethod().glyph_ctext(sign); }

				nik_ce size_type glyph_ctext(icon_ctype_ref icon, size_ctype n) const
					{ return symbol_cmethod().glyph_ctext(icon, n); }

				nik_ce size_type glyph_ctext(sign_ctype_ref sign, size_ctype n) const
					{ return symbol_cmethod().glyph_ctext(sign, n); }

				template<typename T>
				nik_ce size_type total_bytes(const T & v) const
					{ return symbol_cmethod().total_bytes(v); }

				template<typename T>
				nik_ce size_type max_bytes(const T & v) const
					{ return symbol_cmethod().max_bytes(v); }

				template<typename T>
				nik_ce size_type max_universe(const T & v) const
					{ return symbol_cmethod().max_universe(v); }

			// (image):

				nik_ce auto image_ctext(sign_ctype_ref sign) const
					{ return symbol_cmethod().image_ctext(sign); }

				nik_ce size_type image_ctext(sign_ctype_ref sign, size_ctype n) const
					{ return symbol_cmethod().image_ctext(sign, n); }

			// record:

				nik_ce auto record_csubmethod() const
					{ return base::model->template record_csubequip<record_csubmethod_type>(); }

				nik_ce auto record_ctext(sign_ctype_ref sign, size_ctype point, size_ctype n = 1) const
				{
					size_ctype start  = image_ctext(sign, point);
					size_ctype finish = start + n;
					auto record_cival = record_csubmethod();

					record_cival.mid_set(start, finish);

					return record_cival;
				}
	};

/***********************************************************************************************************************/

// mutable:

	template<template<typename> typename SymbolMethod, template<typename> typename RecordMethod, typename Base>
	class concord_method_disjoint : public Base
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

			using symbol_method_type	= typename model_type::template
								symbol_method_type<SymbolMethod>;
			using record_submethod_type	= typename model_type::template
								record_submethod_type<RecordMethod>;

		public:

			nik_ce concord_method_disjoint() : base{} { }
			nik_ce concord_method_disjoint(const facade & f) : base{f} { }

			// symbol:

				nik_ce auto symbol_method()
					{ return base::model->template symbol_equip<symbol_method_type>(); }

			// (glyph):

				nik_ce auto glyph_text(icon_ctype_ref icon)
					{ return symbol_method().glyph_text(icon); }

				nik_ce auto glyph_text(sign_ctype_ref sign)
					{ return symbol_method().glyph_text(sign); }

				nik_ce size_type glyph_text(icon_ctype_ref icon, size_ctype n)
					{ return symbol_method().glyph_text(icon, n); }

				nik_ce size_type glyph_text(sign_ctype_ref sign, size_ctype n)
					{ return symbol_method().glyph_text(sign, n); }

			// (image):

				nik_ce auto image_text(sign_ctype_ref sign)
					{ return symbol_method().image_text(sign); }

				nik_ce size_type image_text(sign_ctype_ref sign, size_ctype n)
					{ return symbol_method().image_text(sign, n); }

			// record:

				nik_ce auto record_submethod()
					{ return base::model->template record_subequip<record_submethod_type>(); }

				nik_ce auto record_text(sign_ctype_ref sign, size_ctype point, size_ctype n = 1)
				{
					size_ctype start  = base::image_ctext(sign, point);
					size_ctype finish = start + n;
					auto record_ival  = record_submethod();

					record_ival.mid_set(start, finish);

					return record_ival;
				}

				nik_ce void record_copy(sign_ctype_ref sign, size_ctype point, size_ctype value)
					{ base::record().copy(base::image_ctext(sign, point), value); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

