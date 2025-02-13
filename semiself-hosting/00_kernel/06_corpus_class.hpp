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

// corpus class:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// corpus:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// model:

	template<typename...> class corpus_model;

/***********************************************************************************************************************/

// mutable:

	template
	<
		typename Type, typename SizeType,
		auto GSize, auto... GSizes,
		auto SSize, auto... SSizes,
		auto ISize, auto... ISizes
	>
	class corpus_model
	<
		Type, SizeType,
		T_pack_Vs<GSize, GSizes...>,
		T_pack_Vs<SSize, SSizes...>,
		T_pack_Vs<ISize, ISizes...>
	>
	{
		public:

			using facade			= corpus_model; // method compatible.

			using glyph_type		= book<Type, SizeType, GSize + SSize, GSizes..., SSizes...>;
			using glyph_type_ptr		= typename alias<glyph_type>::type_ptr;
			using glyph_ctype_ptr		= typename alias<glyph_type>::ctype_ptr;

			using image_type		= book<Type, SizeType, ISize, ISizes...>;
			using image_type_ptr		= typename alias<image_type>::type_ptr;
			using image_ctype_ptr		= typename alias<image_type>::ctype_ptr;

			nik_using_name_scope_type	( type, image_type)
			nik_using_name_scope_ctype	(ctype, image_type)

			nik_using_size_type		(image_type)

		public:

			template<template<typename> typename CMethod>
			using glyph_cmethod_type = resolve_cmethod<glyph_type, CMethod>;

			template<template<typename> typename Method>
			using glyph_method_type = resolve_method<glyph_type, Method>;

			template<template<typename> typename CMethod>
			using image_cmethod_type = resolve_cmethod<image_type, CMethod>;

			template<template<typename> typename Method>
			using image_method_type = resolve_method<image_type, Method>;

		protected:

			glyph_type _glyph;
			image_type _image;

		public:

			nik_ce corpus_model()
			{
				_glyph.page().upslot(sizeof...(GSizes));
				_image.page().upslot(sizeof...(ISizes));
			}

			// glyph:

				nik_ce glyph_ctype_ptr cglyph() const { return &_glyph; }
				nik_ce  glyph_type_ptr  glyph()       { return &_glyph; }

				template<typename CMethod>
				nik_ce auto glyph_cequip() const { return _glyph.template cequip<CMethod>(); }

				template<typename Method>
				nik_ce auto glyph_equip() { return _glyph.template equip<Method>(); }

			// image:

				nik_ce image_ctype_ptr cimage() const { return &_image; }
				nik_ce  image_type_ptr  image()       { return &_image; }

				template<typename CMethod>
				nik_ce auto image_cequip() const { return _image.template cequip<CMethod>(); }

				template<typename Method>
				nik_ce auto image_equip() { return _image.template equip<Method>(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// facade:

/***********************************************************************************************************************/

// immutable:

	template<typename Model>
	class corpus_cfacade
	{
		public:

			using facade			= corpus_cfacade; // method compatible.

			using model_type		= Model;
			using model_ctype_ptr		= typename alias<model_type>::ctype_ptr;
			using model_ctype_cptr		= typename alias<model_type>::ctype_cptr;

			using glyph_type		= typename model_type::glyph_type;
			using glyph_ctype_ref		= typename alias<glyph_type>::ctype_ref;

			using image_type		= typename model_type::image_type;
			using image_ctype_ref		= typename alias<image_type>::ctype_ref;

			nik_using_size_type		(model_type)

		protected:

			model_ctype_ptr model;

		public:

			nik_ce corpus_cfacade() : model{} { }
			nik_ce corpus_cfacade(model_ctype_cptr m) : model{m} { }

			// glyph:

				nik_ce glyph_ctype_ref cglyph() const { return *model->cglyph(); }

			// image:

				nik_ce image_ctype_ref cimage() const { return *model->cimage(); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Model>
	class corpus_facade
	{
		public:

			using facade			= corpus_facade; // method compatible.

			using model_type		= Model;
			using model_type_ptr		= typename alias<model_type>::type_ptr;
			using model_type_cptr		= typename alias<model_type>::type_cptr;

			using glyph_type		= typename model_type::glyph_type;
			using glyph_type_ref		= typename alias<glyph_type>::type_ref;
			using glyph_ctype_ref		= typename alias<glyph_type>::ctype_ref;

			using image_type		= typename model_type::image_type;
			using image_type_ref		= typename alias<image_type>::type_ref;
			using image_ctype_ref		= typename alias<image_type>::ctype_ref;

			nik_using_size_type		(model_type)

		protected:

			model_type_ptr model;

		public:

			nik_ce corpus_facade() : model{} { }
			nik_ce corpus_facade(model_type_cptr m) : model{m} { }

			// glyph:

				nik_ce glyph_ctype_ref cglyph() const { return *model->cglyph(); }
				nik_ce  glyph_type_ref  glyph()       { return *model-> glyph(); }

			// image:

				nik_ce image_ctype_ref cimage() const { return *model->cimage(); }
				nik_ce  image_type_ref  image()       { return *model-> image(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// interface:

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, typename GlyphPack, typename SpacePack, typename ImagePack>
	class corpus : public corpus_model<Type, SizeType, GlyphPack, SpacePack, ImagePack>
	{
		public:

			using glyph_pack		= GlyphPack;
			using space_pack		= SpacePack;
			using image_pack		= ImagePack;
			using base			= corpus_model
							<
								Type, SizeType, glyph_pack, space_pack, image_pack
							>;
			using model			= base;
			using cfacade_type		= corpus_cfacade<model>;
			using facade_type		= corpus_facade<model>;

			nik_using_size_type		(base)

		public:

			nik_ce corpus() : base{} { }

			// equip:

				template<typename CMethod>
				nik_ce auto cequip() const -> CMethod
					{ return cfacade_type{static_cast<model const*>(this)}; }

				template<typename Method>
				nik_ce auto equip() -> Method
					{ return facade_type{static_cast<model*>(this)}; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// method:

/***********************************************************************************************************************/

// immutable:

	template<typename Base, template<typename> typename GlyphCMethod, template<typename> typename ImageCMethod>
	class corpus_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model			= typename base::model_type;

			nik_using_size_type		(base)

			using icon_type			= icon<size_type>;
			using icon_ctype_ref		= typename alias<icon_type>::ctype_ref;

			using sign_type			= sign<size_type>;
			using sign_ctype_ref		= typename alias<sign_type>::ctype_ref;

		protected:

			using glyph_cmethod_type	= typename model::template glyph_cmethod_type<GlyphCMethod>;
			using image_cmethod_type	= typename model::template image_cmethod_type<ImageCMethod>;

			glyph_cmethod_type glyph_cmethod;
			image_cmethod_type image_cmethod;

		public:

			nik_ce corpus_cmethod_disjoint() : base{}, glyph_cmethod{}, image_cmethod{} { }
			nik_ce corpus_cmethod_disjoint(const facade & f) :

				base{f},
				glyph_cmethod{base::model->template glyph_cequip<glyph_cmethod_type>()},
				image_cmethod{base::model->template image_cequip<image_cmethod_type>()}
				{ }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base, template<typename> typename GlyphMethod, template<typename> typename ImageMethod>
	class corpus_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model			= typename base::model_type;

			nik_using_size_type		(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		protected:

			using glyph_method_type		= typename model::template glyph_method_type<GlyphMethod>;
			using image_method_type		= typename model::template image_method_type<ImageMethod>;

			glyph_method_type glyph_method;
			image_method_type image_method;

		public:

			nik_ce corpus_method_disjoint() : base{}, glyph_method{}, image_method{} { }
			nik_ce corpus_method_disjoint(const facade & f) :

				base{f},
				glyph_method{base::model->template glyph_equip<glyph_method_type>()},
				image_method{base::model->template image_equip<image_method_type>()}
				{ }
	};

	// syntactic sugar:

		template
		<
			typename Facade,
			template<typename> typename GlyphCMethod,
			template<typename> typename ImageCMethod
		>
		using corpus_cmethod =
			corpus_cmethod_disjoint < Facade, GlyphCMethod, ImageCMethod >;

	// syntactic sugar:

		template
		<
			typename Facade,
			template<typename> typename GlyphCMethod,
			template<typename> typename ImageCMethod,
			template<typename> typename  GlyphMethod,
			template<typename> typename  ImageMethod
		>
		using corpus_method =
			corpus_method_disjoint  <
			corpus_cmethod_disjoint < Facade, GlyphCMethod, ImageCMethod >, GlyphMethod, ImageMethod >;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

