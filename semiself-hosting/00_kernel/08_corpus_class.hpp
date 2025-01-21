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

	// in order to apply functions internal to a given type system,
	// they have to be known before the use of the type system itself.
	// this is a metacompile time that precedes metarun time.

	// in order to achieve this, type systems should be designed
	// to accept metacompile time type data as well as its metarun time data.
	// defining "apply" to accept such metacompile time objects as template parameters
	// is likely the most expressive approach while maintaining the type system forms.

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// model:

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, typename SymbolPack, typename ImagePack, SizeType Size>
	class corpus_model
	{
		public:

			using facade			= corpus_model; // method compatible.

			using record_type		= semiotic<SizeType, SizeType, SymbolPack, ImagePack>;
			using record_type_ptr		= typename alias<record_type>::type_ptr;
			using record_ctype_ptr		= typename alias<record_type>::ctype_ptr;

			using memory_type		= array<Type, SizeType, Size>;
			using memory_type_ptr		= typename alias<memory_type>::type_ptr;
			using memory_ctype_ptr		= typename alias<memory_type>::ctype_ptr;

			using type			= typename memory_type::type;
			using type_ptr			= typename memory_type::type_ptr;
			using type_cptr			= typename memory_type::type_cptr;
			using type_ref			= typename memory_type::type_ref;

			using ctype			= typename memory_type::ctype;
			using ctype_ptr			= typename memory_type::ctype_ptr;
			using ctype_cptr		= typename memory_type::ctype_cptr;
			using ctype_ref			= typename memory_type::ctype_ref;

			using size_type			= typename memory_type::size_type;
			using size_ctype		= typename memory_type::size_ctype;

		public:

			using record_cmethod_type	= resolve_cmethod<record_type, sring_cmethod>;
			using record_method_type	= resolve_method <record_type,  sring_method>;

			using memory_cmethod_type	= resolve_cmethod<memory_type, array_cmethod>;
			using memory_method_type	= resolve_method <memory_type,  array_method>;

			using memory_csubmethod_type	= resolve_csubmethod<memory_type, array_csubmethod>;
			using memory_submethod_type	= resolve_submethod <memory_type,  array_submethod>;

		protected:

			record_type logic;
			memory_type value;

		public:

			nik_ce corpus_model() { }

			// logic:

				nik_ce record_ctype_ptr crecord() const { return &logic; }
				nik_ce  record_type_ptr  record()       { return &logic; }

				nik_ce auto record_cequip() const
					{ return logic.template cequip<record_cmethod_type>(); }

				nik_ce auto record_equip()
					{ return logic.template equip<record_method_type>(); }

			// value:

				nik_ce memory_ctype_ptr cmemory() const { return &value; }
				nik_ce  memory_type_ptr  memory()       { return &value; }

				nik_ce auto memory_cequip() const
					{ return value.template cequip<memory_cmethod_type>(); }

				nik_ce auto memory_equip()
					{ return value.template equip<memory_method_type>(); }

				nik_ce auto memory_csubequip(size_ctype n) const
					{ return value.template right_cequip<memory_csubmethod_type>(n); }

				nik_ce auto memory_subequip(size_ctype n)
					{ return value.template right_equip<memory_submethod_type>(n); }
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

			using record_type		= typename model_type::record_type;
			using record_ctype_ref		= typename alias<record_type>::ctype_ref;

			using memory_type		= typename model_type::memory_type;
			using memory_ctype_ref		= typename alias<memory_type>::ctype_ref;

			using size_type			= typename model_type::size_type;
			using size_ctype		= typename model_type::size_ctype;

		protected:

			model_ctype_ptr model;

		public:

			nik_ce corpus_cfacade() : model{} { }
			nik_ce corpus_cfacade(model_ctype_cptr m) : model{m} { }

			// record:

				nik_ce record_ctype_ref crecord() const { return *model->crecord(); }

			// memory:

				nik_ce memory_ctype_ref cmemory() const { return *model->cmemory(); }
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

			using record_type		= typename model_type::record_type;
			using record_type_ref		= typename alias<record_type>::type_ref;
			using record_ctype_ref		= typename alias<record_type>::ctype_ref;

			using memory_type		= typename model_type::memory_type;
			using memory_type_ref		= typename alias<memory_type>::type_ref;
			using memory_ctype_ref		= typename alias<memory_type>::ctype_ref;

			using size_type			= typename model_type::size_type;
			using size_ctype		= typename model_type::size_ctype;

		protected:

			model_type_ptr model;

		public:

			nik_ce corpus_facade() : model{} { }
			nik_ce corpus_facade(model_type_cptr m) : model{m} { }

			// record:

				nik_ce record_ctype_ref crecord() const { return *model->crecord(); }
				nik_ce  record_type_ref  record()       { return *model-> record(); }

			// memory:

				nik_ce memory_ctype_ref cmemory() const { return *model->cmemory(); }
				nik_ce  memory_type_ref  memory()       { return *model-> memory(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// corpus:

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, typename SymbolPack, typename ImagePack, SizeType Size>
	class corpus : public corpus_model<Type, SizeType, SymbolPack, ImagePack, Size>
	{
		public:

			using base			= corpus_model<Type, SizeType, SymbolPack, ImagePack, Size>;
			using model			= base;
			using cfacade_type		= corpus_cfacade<model>;
			using facade_type		= corpus_facade<model>;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

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
/***********************************************************************************************************************/

} // namespace cctmp

