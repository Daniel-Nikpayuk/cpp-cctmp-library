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

			using gram_type		= gram<size_type>;
			using icon_type		= icon<size_type>;

		protected:

			size_type tag;
			size_type rposition;
			size_type dposition;

		public:

			nik_ce sign() : tag{}, rposition{}, dposition{} { }
			nik_ce sign(size_ctype t, size_ctype r, size_ctype d) :
				tag{t}, rposition{r}, dposition{d} { }

			// tag:

				nik_ce size_type kind() const { return tag; }
				nik_ce void set_kind(size_ctype t) { tag = t; }

			// rposition:

				nik_ce size_type rindex() const { return rposition; }
				nik_ce void set_rindex(size_ctype r) { rposition = r; }

			// dposition:

				nik_ce size_type dindex() const { return dposition; }
				nik_ce void set_dindex(size_ctype d) { dposition = d; }

			// to icon:

				nik_ce auto to_gram() const { return gram_type{tag, rposition}; }
				nik_ce auto to_icon() const { return icon_type{tag, dposition}; }
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

		public:

			using signifier_cmethod_type	= resolve_cmethod<signifier_type, rring_cmethod>;
			using signifier_method_type	= resolve_method <signifier_type,  rring_method>;

			using signified_cmethod_type	= resolve_cmethod<signified_type, dring_cmethod>;
			using signified_method_type	= resolve_method <signified_type,  dring_method>;

		protected:

			signifier_type symbol;
			signified_type image;

		public:

			nik_ce semiotic_model() { }

			// symbol:

				nik_ce signifier_ctype_ptr csignifier() const { return &symbol; }
				nik_ce  signifier_type_ptr  signifier()       { return &symbol; }

				nik_ce auto signifier_cequip() const
					{ return symbol.template cequip<signifier_cmethod_type>(); }

				nik_ce auto signifier_equip()
					{ return symbol.template equip<signifier_method_type>(); }

			// image:

				nik_ce signified_ctype_ptr csignified() const { return &image; }
				nik_ce  signified_type_ptr  signified()       { return &image; }

				nik_ce auto signified_cequip() const
					{ return image.template cequip<signifier_cmethod_type>(); }

				nik_ce auto signified_equip()
					{ return image.template equip<signifier_method_type>(); }
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

			using model_type		= Model;
			using model_ctype_ptr		= typename alias<model_type>::ctype_ptr;
			using model_ctype_cptr		= typename alias<model_type>::ctype_cptr;

			using signifier_type		= typename model_type::signifier_type;
			using signifier_ctype_ref	= typename alias<signifier_type>::ctype_ref;

			using signified_type		= typename model_type::signified_type;
			using signified_ctype_ref	= typename alias<signified_type>::ctype_ref;

			using size_type			= typename model_type::size_type;
			using size_ctype		= typename model_type::size_ctype;

		protected:

			model_ctype_ptr model;

		public:

			nik_ce semiotic_cfacade() : model{} { }
			nik_ce semiotic_cfacade(model_ctype_cptr m) : model{m} { }

			// symbol:

				nik_ce signifier_ctype_ref csignifier() const { return *model->csignifier(); }

			// image:

				nik_ce signified_ctype_ref csignified() const { return *model->csignified(); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Model>
	class semiotic_facade
	{
		public:

			using facade			= semiotic_facade; // method compatible.

			using model_type		= Model;
			using model_type_ptr		= typename alias<model_type>::type_ptr;
			using model_type_cptr		= typename alias<model_type>::type_cptr;

			using signifier_type		= typename model_type::signifier_type;
			using signifier_type_ref	= typename alias<signifier_type>::type_ref;
			using signifier_ctype_ref	= typename alias<signifier_type>::ctype_ref;

			using signified_type		= typename model_type::signified_type;
			using signified_type_ref	= typename alias<signified_type>::type_ref;
			using signified_ctype_ref	= typename alias<signified_type>::ctype_ref;

			using size_type			= typename model_type::size_type;
			using size_ctype		= typename model_type::size_ctype;

		protected:

			model_type_ptr model;

		public:

			nik_ce semiotic_facade() : model{} { }
			nik_ce semiotic_facade(model_type_cptr m) : model{m} { }

			// signifier:

				nik_ce signifier_ctype_ref csignifier() const { return *model->csignifier(); }
				nik_ce  signifier_type_ref  signifier()       { return *model-> signifier(); }

			// signified:

				nik_ce signified_ctype_ref csignified() const { return *model->csignified(); }
				nik_ce  signified_type_ref  signified()       { return *model-> signified(); }
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

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce semiotic() : base{} { }

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
/***********************************************************************************************************************/

} // namespace cctmp

