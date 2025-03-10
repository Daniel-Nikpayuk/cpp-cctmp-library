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

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// plot:

	// We encode scope restrictions into the class itself as a means of partitioning a contiguous structure.
	// It allows us to simulate a plot: An array of dynamic length arrays, all the same type.

	template<typename> class plot_cfacade;
	template<typename> class plot_facade;

/***********************************************************************************************************************/

// (scope) policy:

	template<typename Array>
	class plot_policy
	{
		public:

			using array_type		= Array;

			nik_using_name_scope_type	( type, array_type)
			nik_using_name_scope_ctype	(ctype, array_type)

			nik_using_size_type_scope	(array_type)

		protected:

			array_type _start;
			array_type _slot;

		protected:

			nik_ce void initialize_start(ctype_ptr in, ctype_cptr end)
			{
				_start.fullsize();
				partial_sum_start(in, end);
			}

			nik_ce void partial_sum_start(ctype_ptr in, ctype_cptr end)
			{
				type sum = 0;

				for (auto k = _start.begin(); in != end; ++k, ++in)
				{
					 *k  = sum;
					sum +=  *in;
				}
			}

			nik_ce void initialize_slot(ctype_ptr in, ctype_cptr end)
			{
				_slot.fullsize();
				_slot.copy(0, in, end);
			}

		public:

			nik_ce plot_policy() { }

			template<typename T, auto N>
			nik_ce plot_policy(const T (&a)[N])
			{
				initialize_start (a, a + N);
				initialize_slot  (a, a + N);
			}

			// start:

				nik_ce size_type start(size_ctype n) const { return _start[n]; }

			// slot:

				nik_ce size_type length(size_ctype n) const { return _slot[n]; }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, SizeType... Sizes>
	class plot
	{
		public:

			using facade			= plot; // method compatible.
			using cfacade_type		= plot_cfacade<plot>;
			using facade_type		= plot_facade<plot>;

			using initial_type		= array<Type, SizeType, (... + Sizes)>;
			using terminal_type		= array<SizeType, SizeType, sizeof...(Sizes)>;
			using policy_type		= plot_policy<terminal_type>;

			nik_using_name_scope_type	( type, initial_type)
			nik_using_name_scope_ctype	(ctype, initial_type)

			nik_using_name_scope_member	( iter_type, initial_type,  iter_type)
			nik_using_name_scope_member	(iter_ctype, initial_type, iter_ctype)

			nik_using_name_scope_member	( citer_type, initial_type,  citer_type)
			nik_using_name_scope_member	(citer_ctype, initial_type, citer_ctype)

			nik_using_name_scope_member	( deref_type, initial_type,  deref_type)
			nik_using_name_scope_member	(deref_ctype, initial_type, deref_ctype)

			nik_using_name_scope_member	( cderef_type, initial_type,  cderef_type)
			nik_using_name_scope_member	(cderef_ctype, initial_type, cderef_ctype)

			nik_using_size_type_scope	(initial_type)

		protected:

			nik_ces auto policy		= policy_type{{ Sizes... }};

		public:

			nik_ces size_type length(size_ctype n) { return policy.length(n); }

		protected:

			initial_type initial;
			terminal_type terminal;

		public:

			nik_ce plot() { }

			// equip:

					// submethods lack access to push.

				template<typename CMethod>
				nik_ce auto cequip(size_ctype n) const -> CMethod
					{ return cfacade_type{static_cast<plot const*>(this), n}; }

				template<typename Method>
				nik_ce auto equip(size_ctype n) -> Method
					{ return facade_type{static_cast<plot*>(this), n}; }

			// initial:

				nik_ce ctype_ptr cbegin(size_ctype n) const { return initial.citer(policy.start(n)); }
				nik_ce  type_ptr  begin(size_ctype n)       { return initial. iter(policy.start(n)); }

			// terminal:

				nik_ce size_type size(size_ctype n) const { return terminal[n]; }

				nik_ce void set_size(size_ctype n, size_ctype m)
					{ if (m <= length(n)) terminal[n] = m; }

				nik_ce void upslot(size_ctype n = 1)
					{ if (terminal.has_capacity(n)) terminal.upsize(n); }

				nik_ce size_type expand(size_ctype n = 1)
				{
					if (terminal.has_capacity(n)) { return terminal.expand(n); }
					else // error:
					{
						return terminal.size();
					}
				}
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

			nik_using_name_scope_type	( type, model_type)
			nik_using_name_scope_ctype	(ctype, model_type)

			nik_using_name_scope_member	( iter_type, model_type,  iter_type)
			nik_using_name_scope_member	(iter_ctype, model_type, iter_ctype)

			nik_using_name_scope_member	( citer_type, model_type,  citer_type)
			nik_using_name_scope_member	(citer_ctype, model_type, citer_ctype)

			nik_using_name_scope_member	( deref_type, model_type,  deref_type)
			nik_using_name_scope_member	(deref_ctype, model_type, deref_ctype)

			nik_using_name_scope_member	( cderef_type, model_type,  cderef_type)
			nik_using_name_scope_member	(cderef_ctype, model_type, cderef_ctype)

			nik_using_size_type_scope	(model_type)

		protected:

			model_ctype_ptr model;
			size_type locus;

		public:

			nik_ce plot_cfacade() : model{}, locus{} { }
			nik_ce plot_cfacade(model_ctype_cptr m, size_ctype l) : model{m}, locus{l} { }

			nik_ce size_type slot() const { return locus; }
			nik_ce void set_slot(size_ctype l) { locus = l; }

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

			nik_using_name_scope_type	( type, model_type)
			nik_using_name_scope_ctype	(ctype, model_type)

			nik_using_name_scope_member	( iter_type, model_type,  iter_type)
			nik_using_name_scope_member	(iter_ctype, model_type, iter_ctype)

			nik_using_name_scope_member	( citer_type, model_type,  citer_type)
			nik_using_name_scope_member	(citer_ctype, model_type, citer_ctype)

			nik_using_name_scope_member	( deref_type, model_type,  deref_type)
			nik_using_name_scope_member	(deref_ctype, model_type, deref_ctype)

			nik_using_name_scope_member	( cderef_type, model_type,  cderef_type)
			nik_using_name_scope_member	(cderef_ctype, model_type, cderef_ctype)

			nik_using_size_type_scope	(model_type)

		protected:

			model_type_ptr model;
			size_type locus;

		public:

			nik_ce plot_facade() : model{}, locus{} { }
			nik_ce plot_facade(model_type_cptr m, size_ctype l) : model{m}, locus{l} { }

			nik_ce size_type slot() const { return locus; }
			nik_ce void set_slot(size_ctype l) { locus = l; }

			nik_ce size_type length() const { return model->length(locus); }

			// initial:

				nik_ce citer_type cbegin() const { return model->cbegin(locus); }
				nik_ce  iter_type  begin()       { return model-> begin(locus); }

			// terminal:

				nik_ce size_type size() const { return model->size(locus); }
				nik_ce void set_size(size_ctype n) { model->set_size(locus, n); }
				nik_ce void upslot(size_ctype n = 1) { model->upslot(n); }
				nik_ce size_type expand(size_ctype n = 1) { model->expand(n); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// book:

/***********************************************************************************************************************/

// note:

	template<typename SizeType>
	class note
	{
		public:

			nik_using_size_type_alias(SizeType)

		protected:

			size_type _mark;
			size_type _index;

		public:

			nik_ce note() : _mark{}, _index{} { }
			nik_ce note(size_ctype m, size_ctype i) : _mark{m}, _index{i} { }

			// mark:

				nik_ce size_type mark() const { return _mark; }
				nik_ce void set_mark(size_ctype m) { _mark = m; }

			// index:

				nik_ce size_type index() const { return _index; }
				nik_ce void set_index(size_ctype i) { _index = i; }
	};

/***********************************************************************************************************************/

// icon (glyph):

	template<typename SizeType>
	struct icon : public note<SizeType>
	{
		using base			= note<SizeType>;

		nik_using_size_type_scope	(base)

		nik_ce icon() : base{} { }
		nik_ce icon(size_ctype t, size_ctype p) : base{t, p} { }

		bool operator == (const icon & i) const
		{
			size_ctype mark  = base::mark ();
			size_ctype index = base::index();

			return ((mark == i.mark()) && (index == i.index()));
		}
	};

/***********************************************************************************************************************/

// sign (image):

	template<typename SizeType>
	struct sign : public note<SizeType>
	{
		using base			= note<SizeType>;

		nik_using_size_type_scope	(base)

		nik_ce sign() : base{} { }
		nik_ce sign(size_ctype t, size_ctype p) : base{t, p} { }

		bool operator == (const sign & s) const
		{
			size_ctype mark  = base::mark ();
			size_ctype index = base::index();

			return ((mark == s.mark()) && (index == s.index()));
		}
	};

/***********************************************************************************************************************/

// mode (custom):

	template<typename SizeType>
	struct mode : public note<SizeType>
	{
		using base			= note<SizeType>;

		nik_using_size_type_scope	(base)

		nik_ce mode() : base{} { }
		nik_ce mode(size_ctype t, size_ctype p) : base{t, p} { }

		bool operator == (const mode & s) const
		{
			size_ctype mark  = base::mark ();
			size_ctype index = base::index();

			return ((mark == s.mark()) && (index == s.index()));
		}
	};

/***********************************************************************************************************************/

// marks:

		// should an enum type be added?

	struct BookMark
	{
		enum : genum_type
		{
			builtin, tuple, cotuple, function, recurse,
			identity, l_than, l_than_or_eq, g_than, g_than_or_eq,
			exists, forall,

			dimension
		};
	};

/***********************************************************************************************************************/

// spaces:

	struct SpaceMsg { enum : genum_type { fail, dimension }; }; // fail as custom type within the message space.

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// model:

	template<typename> class book_cfacade;
	template<typename> class book_facade;

/***********************************************************************************************************************/

// interval:

	template<typename SizeType>
	class book_interval
	{
		public:

			nik_using_size_type_alias(SizeType)

		protected:

			size_type _start;
			size_type _finish;

		public:

			nik_ce book_interval() : _start{}, _finish{} { }
			nik_ce book_interval(size_ctype s, size_ctype f) : _start{s}, _finish{f} { }

			nik_ce size_type size() const { return _finish - _start; }

			// start:

				nik_ce size_type start() const { return _start; }
				nik_ce void set_start(size_ctype s) { _start = s; }

			// finish:

				nik_ce size_type finish() const { return _finish; }
				nik_ce void set_finish(size_ctype f) { _finish = f; }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, SizeType Size, SizeType... Sizes>
	class book
	{
		public:

			using facade			= book; // method compatible.
			using cfacade_type		= book_cfacade<book>;
			using facade_type		= book_facade<book>;

			using ival_type			= book_interval<SizeType>;
			using page_type			= plot<ival_type, SizeType, Sizes...>;
			using page_type_ptr		= typename alias<page_type>::type_ptr;
			using page_ctype_ptr		= typename alias<page_type>::ctype_ptr;

			using text_type			= array<Type, SizeType, Size>;
			using text_type_ptr		= typename alias<text_type>::type_ptr;
			using text_ctype_ptr		= typename alias<text_type>::ctype_ptr;

			nik_using_name_scope_type	( type, text_type)
			nik_using_name_scope_ctype	(ctype, text_type)

			nik_using_size_type_scope	(text_type)

		public:

			template<template<typename> typename CMethod>
			using page_cmethod_type = resolve_cmethod<page_type, CMethod>;

			template<template<typename> typename Method>
			using page_method_type = resolve_method<page_type, Method>;

			template<template<typename> typename CMethod>
			using text_csubmethod_type = resolve_csubmethod<text_type, CMethod>;

			template<template<typename> typename Method>
			using text_submethod_type = resolve_submethod<text_type, Method>;

		protected:

			page_type _page;
			text_type _text;

		public:

			nik_ce book() { }

			// equip:

				template<typename CMethod>
				nik_ce auto cequip() const -> CMethod
					{ return cfacade_type{static_cast<book const*>(this)}; }

				template<typename Method>
				nik_ce auto equip() -> Method
					{ return facade_type{static_cast<book*>(this)}; }

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
				nik_ce auto text_csubequip() const
					{ return _text.template csubequip<CMethod>(); }

				template<typename Method>
				nik_ce auto text_subequip()
					{ return _text.template subequip<Method>(); }
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

			nik_using_name_scope_type	( type, model_type)
			nik_using_name_scope_ctype	(ctype, model_type)

			nik_using_size_type_scope	(model_type)

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

			nik_using_name_scope_type	( type, model_type)
			nik_using_name_scope_ctype	(ctype, model_type)

			nik_using_size_type_scope	(model_type)

		protected:

			model_type_ptr model;

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
/***********************************************************************************************************************/

} // namespace cctmp

