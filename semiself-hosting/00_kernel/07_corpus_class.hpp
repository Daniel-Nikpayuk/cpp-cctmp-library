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

		protected:

			record_type logic;
			memory_type value;

		public:

			nik_ce corpus_model() { }

			// logic:

				nik_ce record_ctype_ptr crecord() const { return &logic; }
				nik_ce  record_type_ptr  record()       { return &logic; }

			// value:

				nik_ce memory_ctype_ptr cmemory() const { return &value; }
				nik_ce  memory_type_ptr  memory()       { return &value; }
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

			using record_type		= typename Model::record_type;
			using record_ctype		= typename alias<record_type>::ctype;
			using record_ctype_ptr		= typename alias<record_type>::ctype_ptr;
			using record_ctype_cptr		= typename alias<record_type>::ctype_cptr;
			using record_ctype_ref		= typename alias<record_type>::ctype_ref;

			using memory_type		= typename Model::memory_type;
			using memory_ctype		= typename alias<memory_type>::ctype;
			using memory_ctype_ptr		= typename alias<memory_type>::ctype_ptr;
			using memory_ctype_cptr		= typename alias<memory_type>::ctype_cptr;
			using memory_ctype_ref		= typename alias<memory_type>::ctype_ref;

			using size_type			= typename Model::size_type;
			using size_ctype		= typename Model::size_ctype;

		protected:

			record_ctype_ptr logic;
			memory_ctype_ptr value;

		public:

			nik_ce corpus_cfacade() : logic{}, value{} { }
			nik_ce corpus_cfacade(record_ctype_cptr l, memory_ctype_cptr v) : logic{l}, value{v} { }

			// logic:

				nik_ce record_ctype_ref crecord() const { return *logic; }

			// value:

				nik_ce memory_ctype_ref cmemory() const { return *value; }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Model>
	class corpus_facade
	{
		public:

			using facade			= corpus_facade; // method compatible.

			using record_type		= typename Model::record_type;
			using record_type_ptr		= typename alias<record_type>::type_ptr;
			using record_type_cptr		= typename alias<record_type>::type_cptr;
			using record_type_ref		= typename alias<record_type>::type_ref;
			using record_ctype_ref		= typename alias<record_type>::ctype_ref;

			using memory_type		= typename Model::memory_type;
			using memory_type_ptr		= typename alias<memory_type>::type_ptr;
			using memory_type_cptr		= typename alias<memory_type>::type_cptr;
			using memory_type_ref		= typename alias<memory_type>::type_ref;
			using memory_ctype_ref		= typename alias<memory_type>::ctype_ref;

			using size_type			= typename Model::size_type;
			using size_ctype		= typename Model::size_ctype;

		protected:

			record_type_ptr logic;
			memory_type_ptr value;

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

			nik_ce corpus_facade() : logic{}, value{} { }
			nik_ce corpus_facade(record_type_cptr l, memory_type_cptr v) : logic{l}, value{v} { }

			// logic:

				nik_ce record_ctype_ref crecord() const { return *logic; }
				nik_ce  record_type_ref  record()       { return *logic; }

			// value:

				nik_ce memory_ctype_ref cmemory() const { return *value; }
				nik_ce  memory_type_ref  memory()       { return *value; }
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

			nik_ce corpus() : base{} { }

			// equip:

				template<typename CMethod>
				nik_ce auto cequip() const -> CMethod
					{ return cfacade_type{base::crecord(), base::cmemory()}; }

				template<typename Method>
				nik_ce auto equip() -> Method
					{ return facade_type{base::record(), base::memory()}; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

