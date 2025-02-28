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
/***********************************************************************************************************************/

} // namespace cctmp

