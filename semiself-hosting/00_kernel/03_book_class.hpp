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

// book class:

namespace cctmp {

	// refactor typedefs with macros:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// plot:

/***********************************************************************************************************************/

// start:

	template<typename SizeType, SizeType Size>
	class plot_start : public array<SizeType, SizeType, Size>
	{
		public:

			using base			= array<SizeType, SizeType, Size>;
			using cfacade_type		= typename base::cfacade_type;
			using facade_type		= typename base::facade_type;

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

		protected:

			nik_ce void initialize(ctype_ptr in, ctype_cptr end)
			{
				base::fullsize();

				type sum = 0;

				for (auto k = base::begin(); in != end; ++k, ++in)
				{
					 *k  = sum;
					sum +=  *in;
				}
			}

		public:

			nik_ce plot_start() : base{} { }

			nik_ce plot_start(const array<SizeType, SizeType, Size> & i) : base{}
				{ initialize(i.cbegin(), i.cend()); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, SizeType... Sizes>
	class plot_model
	{
		public:

			using facade			= plot_model; // method compatible.

			using initial_type		= array<Type, SizeType, (... + Sizes)>;
			using terminal_type		= array<SizeType, SizeType, sizeof...(Sizes)>;
			using start_type		= plot_start<SizeType, sizeof...(Sizes)>;

			using type			= typename initial_type::type;
			using type_ptr			= typename initial_type::type_ptr;
			using type_cptr			= typename initial_type::type_cptr;
			using type_ref			= typename initial_type::type_ref;

			using ctype			= typename initial_type::ctype;
			using ctype_ptr			= typename initial_type::ctype_ptr;
			using ctype_cptr		= typename initial_type::ctype_cptr;
			using ctype_ref			= typename initial_type::ctype_ref;

			using citer_type		= typename initial_type::citer_type;
			using citer_type_ptr		= typename initial_type::citer_type_ptr;
			using citer_type_cptr		= typename initial_type::citer_type_cptr;
			using citer_type_ref		= typename initial_type::citer_type_ref;

			using citer_ctype		= typename initial_type::citer_ctype;
			using citer_ctype_ptr		= typename initial_type::citer_ctype_ptr;
			using citer_ctype_cptr		= typename initial_type::citer_ctype_cptr;
			using citer_ctype_ref		= typename initial_type::citer_ctype_ref;

			using iter_type			= typename initial_type::iter_type;
			using iter_type_ptr		= typename initial_type::iter_type_ptr;
			using iter_type_cptr		= typename initial_type::iter_type_cptr;
			using iter_type_ref		= typename initial_type::iter_type_ref;

			using iter_ctype		= typename initial_type::iter_ctype;
			using iter_ctype_ptr		= typename initial_type::iter_ctype_ptr;
			using iter_ctype_cptr		= typename initial_type::iter_ctype_cptr;
			using iter_ctype_ref		= typename initial_type::iter_ctype_ref;

			using cderef_type		= typename initial_type::cderef_type;
			using cderef_type_ptr		= typename initial_type::cderef_type_ptr;
			using cderef_type_cptr		= typename initial_type::cderef_type_cptr;
			using cderef_type_ref		= typename initial_type::cderef_type_ref;

			using cderef_ctype		= typename initial_type::cderef_ctype;
			using cderef_ctype_ptr		= typename initial_type::cderef_ctype_ptr;
			using cderef_ctype_cptr		= typename initial_type::cderef_ctype_cptr;
			using cderef_ctype_ref		= typename initial_type::cderef_ctype_ref;

			using deref_type		= typename initial_type::deref_type;
			using deref_type_ptr		= typename initial_type::deref_type_ptr;
			using deref_type_cptr		= typename initial_type::deref_type_cptr;
			using deref_type_ref		= typename initial_type::deref_type_ref;

			using deref_ctype		= typename initial_type::deref_ctype;
			using deref_ctype_ptr		= typename initial_type::deref_ctype_ptr;
			using deref_ctype_cptr		= typename initial_type::deref_ctype_cptr;
			using deref_ctype_ref		= typename initial_type::deref_ctype_ref;

			using size_type			= typename initial_type::size_type;
			using size_ctype		= typename initial_type::size_ctype;

		protected:

			nik_ces auto capacity		= terminal_type{{ Sizes... }};
			nik_ces auto start		= start_type{capacity};

		public:

			nik_ces size_type length(size_ctype n) { return capacity[n]; }

		protected:

			initial_type initial;
			terminal_type terminal;

		public:

			nik_ce plot_model() { terminal.fullsize(); } // too restrictive.

			// initial:

				nik_ce ctype_ptr cbegin(size_ctype n) const { return initial.citer(start[n]); }
				nik_ce  type_ptr  begin(size_ctype n)       { return initial. iter(start[n]); }

			// terminal:

				nik_ce size_type size(size_ctype n) const { return terminal[n]; }
				nik_ce void set_size(size_ctype n, size_ctype m) { terminal[n] = m; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// facade:

/***********************************************************************************************************************/

// immutable:

	template<typename Model>
	class plot_cfacade
	{
		public:

			using facade			= plot_cfacade; // method compatible.

			using model_type		= Model;
			using model_ctype_ptr		= typename alias<model_type>::ctype_ptr;
			using model_ctype_cptr		= typename alias<model_type>::ctype_cptr;

			using type			= typename model_type::type;
			using type_ptr			= typename model_type::type_ptr;
			using type_cptr			= typename model_type::type_cptr;
			using type_ref			= typename model_type::type_ref;

			using ctype			= typename model_type::ctype;
			using ctype_ptr			= typename model_type::ctype_ptr;
			using ctype_cptr		= typename model_type::ctype_cptr;
			using ctype_ref			= typename model_type::ctype_ref;

			using citer_type		= typename model_type::citer_type;
			using citer_type_ptr		= typename model_type::citer_type_ptr;
			using citer_type_cptr		= typename model_type::citer_type_cptr;
			using citer_type_ref		= typename model_type::citer_type_ref;

			using citer_ctype		= typename model_type::citer_ctype;
			using citer_ctype_ptr		= typename model_type::citer_ctype_ptr;
			using citer_ctype_cptr		= typename model_type::citer_ctype_cptr;
			using citer_ctype_ref		= typename model_type::citer_ctype_ref;

			using cderef_type		= typename model_type::cderef_type;
			using cderef_type_ptr		= typename model_type::cderef_type_ptr;
			using cderef_type_cptr		= typename model_type::cderef_type_cptr;
			using cderef_type_ref		= typename model_type::cderef_type_ref;

			using cderef_ctype		= typename model_type::cderef_ctype;
			using cderef_ctype_ptr		= typename model_type::cderef_ctype_ptr;
			using cderef_ctype_cptr		= typename model_type::cderef_ctype_cptr;
			using cderef_ctype_ref		= typename model_type::cderef_ctype_ref;

			using size_type			= typename model_type::size_type;
			using size_ctype		= typename model_type::size_ctype;

		protected:

			model_ctype_ptr model;
			size_type locus;

		public:

			nik_ce plot_cfacade() : model{}, locus{} { }
			nik_ce plot_cfacade(model_ctype_cptr m, size_ctype l) : model{m}, locus{l} { }

			// initial:

				nik_ce citer_type cbegin() const { return model->cbegin(locus); }

			// terminal:

				nik_ce size_type size() const { return model->size(locus); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Model>
	class plot_facade
	{
		public:

			using facade			= plot_facade; // method compatible.

			using model_type		= Model;
			using model_type_ptr		= typename alias<model_type>::type_ptr;
			using model_type_cptr		= typename alias<model_type>::type_cptr;

			using type			= typename model_type::type;
			using type_ptr			= typename model_type::type_ptr;
			using type_cptr			= typename model_type::type_cptr;
			using type_ref			= typename model_type::type_ref;

			using ctype			= typename model_type::ctype;
			using ctype_ptr			= typename model_type::ctype_ptr;
			using ctype_cptr		= typename model_type::ctype_cptr;
			using ctype_ref			= typename model_type::ctype_ref;

			using citer_type		= typename model_type::citer_type;
			using citer_type_ptr		= typename model_type::citer_type_ptr;
			using citer_type_cptr		= typename model_type::citer_type_cptr;
			using citer_type_ref		= typename model_type::citer_type_ref;

			using citer_ctype		= typename model_type::citer_ctype;
			using citer_ctype_ptr		= typename model_type::citer_ctype_ptr;
			using citer_ctype_cptr		= typename model_type::citer_ctype_cptr;
			using citer_ctype_ref		= typename model_type::citer_ctype_ref;

			using iter_type			= typename model_type::iter_type;
			using iter_type_ptr		= typename model_type::iter_type_ptr;
			using iter_type_cptr		= typename model_type::iter_type_cptr;
			using iter_type_ref		= typename model_type::iter_type_ref;

			using iter_ctype		= typename model_type::iter_ctype;
			using iter_ctype_ptr		= typename model_type::iter_ctype_ptr;
			using iter_ctype_cptr		= typename model_type::iter_ctype_cptr;
			using iter_ctype_ref		= typename model_type::iter_ctype_ref;

			using cderef_type		= typename model_type::cderef_type;
			using cderef_type_ptr		= typename model_type::cderef_type_ptr;
			using cderef_type_cptr		= typename model_type::cderef_type_cptr;
			using cderef_type_ref		= typename model_type::cderef_type_ref;

			using cderef_ctype		= typename model_type::cderef_ctype;
			using cderef_ctype_ptr		= typename model_type::cderef_ctype_ptr;
			using cderef_ctype_cptr		= typename model_type::cderef_ctype_cptr;
			using cderef_ctype_ref		= typename model_type::cderef_ctype_ref;

			using deref_type		= typename model_type::deref_type;
			using deref_type_ptr		= typename model_type::deref_type_ptr;
			using deref_type_cptr		= typename model_type::deref_type_cptr;
			using deref_type_ref		= typename model_type::deref_type_ref;

			using deref_ctype		= typename model_type::deref_ctype;
			using deref_ctype_ptr		= typename model_type::deref_ctype_ptr;
			using deref_ctype_cptr		= typename model_type::deref_ctype_cptr;
			using deref_ctype_ref		= typename model_type::deref_ctype_ref;

			using size_type			= typename model_type::size_type;
			using size_ctype		= typename model_type::size_ctype;

		protected:

			model_type_ptr model;
			size_type locus;

		public:

			nik_ce plot_facade() : model{}, locus{} { }
			nik_ce plot_facade(model_type_cptr m, size_ctype l) : model{m}, locus{l} { }

			nik_ce size_type length() const { return model->length(locus); }

			// initial:

				nik_ce citer_type cbegin() const { return model->cbegin(locus); }
				nik_ce  iter_type  begin()       { return model-> begin(locus); }

			// terminal:

				nik_ce size_type size() const { return model->size(locus); }
				nik_ce void set_size(size_ctype n) { model->set_size(locus, n); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// interface:

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, SizeType... Sizes>
	class plot : public plot_model<Type, SizeType, Sizes...>
//	class plot : public array_method<plot_model<Type, SizeType, Sizes...>> // array_method plot_model ?
	{
		public:

			using model			= plot_model<Type, SizeType, Sizes...>;
			using base			= model;
		//	using base			= array_method<model>;
			using cfacade_type		= plot_cfacade<model>;
			using facade_type		= plot_facade<model>;
		//	using cmethod_type		= array_cmethod<cfacade_type>;
		//	using method_type		= array_method<facade_type>;

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

			nik_ce plot() : base{} { }

			// equip:

				template<typename CMethod>
				nik_ce auto cequip(size_ctype n) const -> CMethod
					{ return cfacade_type{static_cast<model const*>(this), n}; }

				template<typename Method>
				nik_ce auto equip(size_ctype n) -> Method
					{ return facade_type{static_cast<model*>(this), n}; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// book:

/***********************************************************************************************************************/

// instructions:

	struct BookInstruction
	{
		enum : gkey_type
		{
			program, push, apply,
			empty, ring, flex, utf8_char, tuple, cotuple, function, null, list,
			identity, l_than, l_than_or_eq, g_than, g_than_or_eq, dependent, custom,
			exists, forall, type, value, arg,

			dimension
		};
	};

	using BInstr = BookInstruction;

/***********************************************************************************************************************/

// kinds:

	struct BookKind
	{
		enum : gkey_type
		{
			builtin,
			tuple, cotuple, function, list, compare, exists, forall,
			space,

			dimension
		};
	};

	using Book = BookKind;

/***********************************************************************************************************************/

// names:

		// should an enum type be added?

	struct BookName
	{
		enum : gkey_type
		{
			ringN, flexN, utf8_charN,							// builtin
			tuple, cotuple, function,
			null, list,									// list
			identity, less_than, less_than_or_equal, greater_than, greater_than_or_equal,	// compare
			exists, forall,
			custom, space,

			dimension, fail // fail is currently symbolic only, should this change?
					// probably better to define it as custom in a given space.
		};
	};

	using Gram = BookName;

/***********************************************************************************************************************/

// note:

	template<typename SizeType>
	class note
	{
		public:

			using size_type		= typename alias<SizeType>::type;
			using size_ctype	= typename alias<SizeType>::ctype;

		protected:

			size_type tag;
			size_type position;

		public:

			nik_ce note() : tag{}, position{} { }
			nik_ce note(size_ctype t, size_ctype p) : tag{t}, position{p} { }

			// tag:

				nik_ce bool is_fail  () const { return (tag == Gram::fail); }
				nik_ce bool not_fail () const { return (tag != Gram::fail); }

				nik_ce size_type kind() const { return tag; }
				nik_ce void set_kind(size_ctype t) { tag = t; }

			// position:

				nik_ce size_type index() const { return position; }
				nik_ce void set_index(size_ctype p) { position = p; }
	};

/***********************************************************************************************************************/

// icon:

	template<typename SizeType>
	struct icon : public note<SizeType>
	{
		using base		= note<SizeType>;

		using size_type		= typename base::size_type;
		using size_ctype	= typename base::size_ctype;

		nik_ce icon() : base{} { }
		nik_ce icon(size_ctype t, size_ctype p) : base{t, p} { }
	};

/***********************************************************************************************************************/

// sign:

	template<typename SizeType>
	struct sign : public note<SizeType>
	{
		using base		= note<SizeType>;

		using size_type		= typename base::size_type;
		using size_ctype	= typename base::size_ctype;

		nik_ce sign() : base{} { }
		nik_ce sign(size_ctype t, size_ctype p) : base{t, p} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// model:

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, SizeType Size, SizeType... Sizes>
	class book_model
	{
		public:

			using facade			= book_model; // method compatible.

			using page_type			= plot<SizeType, SizeType, Sizes...>;
			using page_type_ptr		= typename alias<page_type>::type_ptr;
			using page_ctype_ptr		= typename alias<page_type>::ctype_ptr;

			using text_type			= array<Type, SizeType, Size>;
			using text_type_ptr		= typename alias<text_type>::type_ptr;
			using text_ctype_ptr		= typename alias<text_type>::ctype_ptr;

			using type			= typename text_type::type;
			using type_ptr			= typename text_type::type_ptr;
			using type_cptr			= typename text_type::type_cptr;
			using type_ref			= typename text_type::type_ref;

			using ctype			= typename text_type::ctype;
			using ctype_ptr			= typename text_type::ctype_ptr;
			using ctype_cptr		= typename text_type::ctype_cptr;
			using ctype_ref			= typename text_type::ctype_ref;

			using size_type			= typename text_type::size_type;
			using size_ctype		= typename text_type::size_ctype;

		public:

		//	using page_cmethod_type		= resolve_cmethod<page_type, array_cmethod>;
		//	using page_method_type		= resolve_method <page_type,  array_method>;

		//	template<template<typename> typename CMethod = array_cmethod>
		//	using text_cmethod = resolve_cmethod<text_type, CMethod>;

		//	template<template<typename> typename Method = array_method>
		//	using text_method = resolve_method<text_type, Method>;

		//	using text_cmethod_type		= text_cmethod<>;
		//	using text_method_type		= text_method<>;

		//	using text_csubmethod_type	= text_cmethod<array_csubmethod>;
		//	using text_submethod_type	= text_method<array_submethod>;

		protected:

			page_type _page;
			text_type _text;

		public:

			nik_ce book_model() { }

			// page:

				nik_ce page_ctype_ptr cpage() const { return &_page; }
				nik_ce  page_type_ptr  page()       { return &_page; }

				template<typename CMethod>
				nik_ce auto page_cequip(size_ctype n) const
					{ return _page.template cequip<CMethod>(n); }

				template<typename Method>
				nik_ce auto page_equip(size_ctype n)
					{ return _page.template equip<Method>(n); }

			// text:

				nik_ce text_ctype_ptr ctext() const { return &_text; }
				nik_ce  text_type_ptr  text()       { return &_text; }

				template<typename CMethod>
				nik_ce auto text_cequip() const
					{ return _text.template cequip<CMethod>(); }

				template<typename Method>
				nik_ce auto text_equip()
					{ return _text.template equip<Method>(); }

			//	nik_ce auto text_csubequip(size_ctype n) const
			//		{ return _text.template right_cequip<text_csubmethod_type>(n); }

			//	nik_ce auto text_subequip(size_ctype n)
			//		{ return _text.template right_equip<text_submethod_type>(n); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// facade:

/***********************************************************************************************************************/

// immutable:

	template<typename Model>
	class book_cfacade
	{
		public:

			using facade			= book_cfacade; // method compatible.

			using model_type		= Model;
			using model_ctype_ptr		= typename alias<model_type>::ctype_ptr;
			using model_ctype_cptr		= typename alias<model_type>::ctype_cptr;

			using page_type			= typename model_type::page_type;
			using page_ctype_ref		= typename alias<page_type>::ctype_ref;

			using text_type			= typename model_type::text_type;
			using text_ctype_ref		= typename alias<text_type>::ctype_ref;

			using size_type			= typename model_type::size_type;
			using size_ctype		= typename model_type::size_ctype;

		protected:

			model_ctype_ptr model;

		public:

			nik_ce book_cfacade() : model{} { }
			nik_ce book_cfacade(model_ctype_cptr m) : model{m} { }

			// page:

				nik_ce page_ctype_ref cpage() const { return *model->cpage(); }

			// text:

				nik_ce text_ctype_ref ctext() const { return *model->ctext(); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Model>
	class book_facade
	{
		public:

			using facade			= book_facade; // method compatible.

			using model_type		= Model;
			using model_type_ptr		= typename alias<model_type>::type_ptr;
			using model_type_cptr		= typename alias<model_type>::type_cptr;

			using page_type			= typename model_type::page_type;
			using page_type_ref		= typename alias<page_type>::type_ref;
			using page_ctype_ref		= typename alias<page_type>::ctype_ref;

			using text_type			= typename model_type::text_type;
			using text_type_ref		= typename alias<text_type>::type_ref;
			using text_ctype_ref		= typename alias<text_type>::ctype_ref;

			using size_type			= typename model_type::size_type;
			using size_ctype		= typename model_type::size_ctype;

		protected:

			model_type_ptr model;

		protected:

			nik_ce bool overlay(size_ctype kind, size_ctype n)
			{
				auto page_method = model->page_equip(kind);

				if (page_method.is_full() || ctext().lacks_capacity(n)) return false;

				page_method.push(text().expand(n));

				return true;
			}

		public:

			nik_ce book_facade() : model{} { }
			nik_ce book_facade(model_type_cptr m) : model{m} { }

			// page:

				nik_ce page_ctype_ref cpage() const { return *model->cpage(); }
				nik_ce  page_type_ref  page()       { return *model-> page(); }

			// text:

				nik_ce text_ctype_ref ctext() const { return *model->ctext(); }
				nik_ce  text_type_ref  text()       { return *model-> text(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// interface:

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, SizeType Size, SizeType... Sizes>
	class book : public book_model<Type, SizeType, Size, Sizes...>
	{
		public:

			using base			= book_model<Type, SizeType, Size, Sizes...>;
			using model			= base;
			using cfacade_type		= book_cfacade<model>;
			using facade_type		= book_facade<model>;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce book() : base{} { }

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

