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

// semiotic class:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sign:

	template<typename SizeType>
	class sign
	{
		public:

			using size_type		= typename alias<SizeType>::type;
			using size_ctype	= typename alias<SizeType>::ctype;

		protected:

			size_type kind;
			size_type type_index;
			size_type image_index;

		public:

			nik_ce sign() : kind{}, type_index{}, image_index{} { }
			nik_ce sign(size_ctype k, size_ctype t, size_ctype i) :
				kind{k}, type_index{t}, image_index{i} { }

			// kind:

				nik_ce size_type get_kind() const { return kind; }
				nik_ce void set_kind(size_ctype k) { kind = k; }

			// type index:

				nik_ce size_type get_type_index() const { return type_index; }
				nik_ce void set_type_index(size_ctype t) { type_index = t; }

			// image index:

				nik_ce size_type get_image_index() const { return image_index; }
				nik_ce void set_image_index(size_ctype i) { image_index = i; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// model:

	template<typename...> class semiotic_model;

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, auto RSize, auto... RSizes, auto DSize, auto... DSizes>
	class semiotic_model<Type, SizeType, T_pack_Vs<RSize, RSizes...>, T_pack_Vs<DSize, DSizes...>>
	{
		public:

			using facade			= semiotic_model; // method compatible.

			using signifier_type		= logo<Type, SizeType, RSize, RSizes...>;
			using signifier_type_ptr	= typename alias<signifier_type>::type_ptr;
			using signifier_ctype_ptr	= typename alias<signifier_type>::ctype_ptr;

			using signified_type		= logo<Type, SizeType, DSize, DSizes...>;
			using signified_type_ptr	= typename alias<signified_type>::type_ptr;
			using signified_ctype_ptr	= typename alias<signified_type>::ctype_ptr;

			using type			= typename signified_type::type;
			using type_ptr			= typename signified_type::type_ptr;
			using type_cptr			= typename signified_type::type_cptr;
			using type_ref			= typename signified_type::type_ref;

			using ctype			= typename signified_type::ctype;
			using ctype_ptr			= typename signified_type::ctype_ptr;
			using ctype_cptr		= typename signified_type::ctype_cptr;
			using ctype_ref			= typename signified_type::ctype_ref;

			using size_type			= typename signified_type::size_type;
			using size_ctype		= typename signified_type::size_ctype;

		protected:

			signifier_type symbol;
			signified_type image;

		public:

			nik_ce semiotic_model() { }

			// symbol:

				nik_ce signifier_ctype_ptr csignifier() const { return &symbol; }
				nik_ce  signifier_type_ptr  signifier()       { return &symbol; }

			// image:

				nik_ce signified_ctype_ptr csignified() const { return &image; }
				nik_ce  signified_type_ptr  signified()       { return &image; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// facade:

/***********************************************************************************************************************/

// immutable:

	template<typename Model>
	class semiotic_cfacade
	{
		public:

			using facade			= semiotic_cfacade; // method compatible.

			using signifier_type		= typename Model::signifier_type;
			using signifier_ctype		= typename alias<signifier_type>::ctype;
			using signifier_ctype_ptr	= typename alias<signifier_type>::ctype_ptr;
			using signifier_ctype_cptr	= typename alias<signifier_type>::ctype_cptr;
			using signifier_ctype_ref	= typename alias<signifier_type>::ctype_ref;

			using signified_type		= typename Model::signified_type;
			using signified_ctype		= typename alias<signified_type>::ctype;
			using signified_ctype_ptr	= typename alias<signified_type>::ctype_ptr;
			using signified_ctype_cptr	= typename alias<signified_type>::ctype_cptr;
			using signified_ctype_ref	= typename alias<signified_type>::ctype_ref;

			using size_type			= typename Model::size_type;
			using size_ctype		= typename Model::size_ctype;

		protected:

			signifier_ctype_ptr symbol;
			signified_ctype_ptr image;

		public:

			nik_ce semiotic_cfacade() : symbol{}, image{} { }
			nik_ce semiotic_cfacade(signifier_ctype_cptr s, signified_ctype_cptr i) :
				symbol{s}, image{i} { }

			// symbol:

				nik_ce signifier_ctype_ref csignifier() const { return *symbol; }

			// image:

				nik_ce signified_ctype_ref csignified() const { return *image; }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Model>
	class semiotic_facade
	{
		public:

			using facade			= semiotic_facade; // method compatible.

			using signifier_type		= typename Model::signifier_type;
			using signifier_type_ptr	= typename alias<signifier_type>::type_ptr;
			using signifier_type_cptr	= typename alias<signifier_type>::type_cptr;
			using signifier_type_ref	= typename alias<signifier_type>::type_ref;
			using signifier_ctype_ref	= typename alias<signifier_type>::ctype_ref;

			using signified_type		= typename Model::signified_type;
			using signified_type_ptr	= typename alias<signified_type>::type_ptr;
			using signified_type_cptr	= typename alias<signified_type>::type_cptr;
			using signified_type_ref	= typename alias<signified_type>::type_ref;
			using signified_ctype_ref	= typename alias<signified_type>::ctype_ref;

			using size_type			= typename Model::size_type;
			using size_ctype		= typename Model::size_ctype;

		protected:

			signifier_type_ptr symbol;
			signified_type_ptr image;

		protected:

		//	using page_cmethod		= resolve_cmethod<page_type, array_cmethod>;
		//	using page_method		= resolve_method <page_type,  array_method>;

		//	using text_cmethod		= resolve_cmethod<text_type, array_cmethod>;
		//	using text_method		= resolve_method <text_type,  array_method>;

		//	using subtext_cmethod		= resolve_csubmethod<text_type, subarray_cmethod>;
		//	using subtext_method		= resolve_submethod <text_type,  subarray_method>;

			// above:

			//	nik_ce auto cpage_equip(size_ctype n) const
			//		{ return above->template cequip<page_cmethod>(n); }

			//	nik_ce auto page_equip(size_ctype n) const
			//		{ return above->template equip<page_method>(n); }

			// below:

			//	nik_ce auto ctext_equip() const
			//		{ return below->template cequip<text_cmethod>(); }

			//	nik_ce auto text_equip() const
			//		{ return below->template equip<text_method>(); }

			//	nik_ce auto ctext_right_equip(size_ctype n) const
			//		{ return below->template right_cequip<subtext_cmethod>(n); }

			//	nik_ce auto text_right_equip(size_ctype n) const
			//		{ return below->template right_equip<subtext_method>(n); }

		public:

			nik_ce semiotic_facade() : symbol{}, image{} { }
			nik_ce semiotic_facade(signifier_type_cptr s, signified_type_cptr i) :
				symbol{s}, image{i} { }

			// symbol:

				nik_ce signifier_ctype_ref csignifier() const { return *symbol; }
				nik_ce  signifier_type_ref  signifier()       { return *symbol; }

			// image:

				nik_ce signified_ctype_ref csignified() const { return *image; }
				nik_ce  signified_type_ref  signified()       { return *image; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// semiotic:

	template<typename...> class semiotic;

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, auto RSize, auto... RSizes, auto DSize, auto... DSizes>
	class semiotic<Type, SizeType, T_pack_Vs<RSize, RSizes...>, T_pack_Vs<DSize, DSizes...>> :
		public semiotic_model<Type, SizeType, T_pack_Vs<RSize, RSizes...>, T_pack_Vs<DSize, DSizes...>>
	{
		public:

			using symbol_pack		= T_pack_Vs<RSize, RSizes...>;
			using image_pack		= T_pack_Vs<DSize, DSizes...>;
			using base			= semiotic_model<Type, SizeType, symbol_pack, image_pack>;
			using model			= base;
			using cfacade_type		= semiotic_cfacade<model>;
			using facade_type		= semiotic_facade<model>;

			using type			= typename base::type;
			using type_ptr			= typename base::type_ptr;
			using type_cptr			= typename base::type_cptr;
			using type_ref			= typename base::type_ref;

			using ctype			= typename base::ctype;
			using ctype_ptr			= typename base::ctype_ptr;
			using ctype_cptr		= typename base::ctype_cptr;
			using ctype_ref			= typename base::ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce semiotic() : base{} { }

			// equip:

				template<typename CMethod>
				nik_ce auto cequip() const -> CMethod
					{ return cfacade_type{base::csignifier(), base::csignified()}; }

				template<typename Method>
				nik_ce auto equip() -> Method
					{ return facade_type{base::signifier(), base::signified()}; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

