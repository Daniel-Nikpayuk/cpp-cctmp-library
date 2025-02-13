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

// book:

/***********************************************************************************************************************/

// note:

	template<typename SizeType>
	class note
	{
		public:

			nik_using_size_type_alias(SizeType)

		protected:

			size_type tag;
			size_type position;

		public:

			nik_ce note() : tag{}, position{} { }
			nik_ce note(size_ctype t, size_ctype p) : tag{t}, position{p} { }

			// tag:

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

		nik_using_size_type	(base)

		nik_ce icon() : base{} { }
		nik_ce icon(size_ctype t, size_ctype p) : base{t, p} { }
	};

/***********************************************************************************************************************/

// sign:

	template<typename SizeType>
	struct sign : public note<SizeType>
	{
		using base		= note<SizeType>;

		nik_using_size_type	(base)

		nik_ce sign() : base{} { }
		nik_ce sign(size_ctype t, size_ctype p) : base{t, p} { }
	};

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

	using BookInstr = BookInstruction;

/***********************************************************************************************************************/

// codes:

	struct BookCode
	{
		enum : gkey_type
		{
			valid, invalid, // will be refined and extended as needed.

			dimension
		};
	};

/***********************************************************************************************************************/

// slots:

		// should an enum type be added?

	struct BookSlot
	{
		enum : gkey_type
		{
			builtin, tuple, cotuple, function, list,
			identity, l_than, l_than_or_eq, g_than, g_than_or_eq,
			exists, forall, space,

			dimension
		};
	};

/***********************************************************************************************************************/

// fields:

	struct BookProg { enum : gkey_type { instr, lines,     code, next, dimension }; };
	struct BookKind { enum : gkey_type { instr, arity,    local, next, dimension }; };
	struct BookMeta { enum : gkey_type { instr, bytes, universe, next, dimension }; };

/***********************************************************************************************************************/

// spaces:

	struct SpaceMsg { enum : gkey_type { fail, dimension }; }; // fail as custom type within the message space.

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// model:

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
	class book_model
	{
		public:

			using facade			= book_model; // method compatible.

			using ival_type			= book_interval<SizeType>;
			using page_type			= plot<ival_type, SizeType, Sizes...>;
			using page_type_ptr		= typename alias<page_type>::type_ptr;
			using page_ctype_ptr		= typename alias<page_type>::ctype_ptr;

			using text_type			= array<Type, SizeType, Size>;
			using text_type_ptr		= typename alias<text_type>::type_ptr;
			using text_ctype_ptr		= typename alias<text_type>::ctype_ptr;

			nik_using_name_scope_type	( type, text_type)
			nik_using_name_scope_ctype	(ctype, text_type)

			nik_using_size_type		(text_type)

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

			nik_using_size_type		(model_type)

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

			nik_using_size_type		(model_type)

		protected:

			using ival_type			= typename Model::ival_type;

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

			nik_using_size_type		(base)

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

// method:

/***********************************************************************************************************************/

// immutable:

	template
	<
		typename Base,
		template<typename> typename PageCMethod,
		template<typename> typename TextCMethod,
		template<typename> typename Note
	>
	class book_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model			= typename facade::model_type;

			nik_using_size_type		(base)

			using note_type			= Note<size_type>;
			using note_type_ref		= typename alias<note_type>::type_ref;
			using note_ctype_ref		= typename alias<note_type>::ctype_ref;

		protected:

			using page_cmethod_type		= typename model::template page_cmethod_type<PageCMethod>;
			using text_csubmethod_type	= typename model::template text_csubmethod_type<TextCMethod>;

			page_cmethod_type page_cmethod;
			text_csubmethod_type text_csubmethod;

		public:

			nik_ce book_cmethod_disjoint() : base{}, page_cmethod{}, text_csubmethod{} { }
			nik_ce book_cmethod_disjoint(const facade & f) :

				base{f},
				page_cmethod    {base::model->template page_cequip   <page_cmethod_type   >(0)},
				text_csubmethod {base::model->template text_csubequip<text_csubmethod_type>( )}
				{ }

			// page:

				nik_ce void set_chapter(size_ctype n) { page_cmethod.set_slot(n); }

			// text:

				nik_ce void set_text_dim(size_ctype r, size_ctype c) // assumes text is preset.
					{ text_csubmethod.set_dimension(r, c); }

				nik_ce void set_text_ival(size_ctype s, size_ctype f)
					{ text_csubmethod.mid_set(s, f); }

				nik_ce void set_text_from_page(size_ctype n) // assumes page is preset.
					{ set_text_ival(page_cmethod[n].start(), page_cmethod[n].finish()); }

				nik_ce auto set_text_from_note(note_ctype_ref n)
				{
					set_chapter(n.kind());
					set_text_from_page(n.index());
				}

			// note:

				nik_ce auto make_note(size_type n, size_ctype m) const { return note_type{n, m}; }

			// fail:

				nik_ce bool is_fail(note_ctype_ref n) const
				{
					return false;
				}

				nik_ce bool not_fail(note_ctype_ref n) const { return not is_fail(n); }

				nik_ce auto fail_note()
				{
					// fail note should construct
					// a fail message type/value.

					return note_type{0, 0};
				}

			// find:

				nik_ce bool found_from_previous(size_ctype n, note_ctype_ref note) const
					{ return (n != note.index()); }

				template<typename T, auto N> // assumes page and note_page match.
				nik_ce auto find_from_previous(note_ctype_ref n) const
				{
					auto npage = page_cmethod.citer(n.index());
					set_text_ival(npage->start(), npage->finish());

					for (auto k = page_cmethod.cbegin(); k != npage; ++k)
					{
						auto b = base::ctext().citer(k->start ());
						auto e = base::ctext().citer(k->finish());

						if (text_csubmethod.equal(0, b, e))
							{ return page_cmethod.left_size(k); }
					}

					return n.index();
				}
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base, template<typename> typename PageMethod, template<typename> typename TextMethod>
	class book_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model			= typename base::model_type;

			nik_using_size_type		(base)

			using ival_type			= typename base::ival_type;

			using note_type			= typename base::note_type;
			using note_ctype_ref		= typename base::note_ctype_ref;

		protected:

			using page_method_type		= typename model::template page_method_type<PageMethod>;
			using text_submethod_type	= typename model::template text_submethod_type<TextMethod>;

			page_method_type page_method;
			text_submethod_type text_submethod;

		public:

			nik_ce book_method_disjoint() : base{}, page_method{}, text_submethod{} { }
			nik_ce book_method_disjoint(const facade & f) :

				base{f},
				page_method    {base::model->template page_equip   <page_method_type   >(0)},
				text_submethod {base::model->template text_subequip<text_submethod_type>( )}
				{ }

			// page:

				nik_ce void set_chapter(size_ctype n)
				{
					base::set_chapter(n);
					page_method.set_slot(n);
				}

			// text:

				nik_ce void set_text_dim(size_ctype r, size_ctype c) // assumes text is preset.
				{
					base::set_text_dim(r, c);
					text_submethod.set_dimension(r, c);
				}

				nik_ce void set_text_ival(size_ctype s, size_ctype f)
				{
					base::set_text_ival(s, f);
					text_submethod.mid_set(s, f);
				}

				nik_ce void set_text_from_page(size_ctype n) // assumes page is preset.
					{ set_text_ival(base::page_cmethod[n].start(), base::page_cmethod[n].finish()); }

				nik_ce auto set_text_from_note(note_ctype_ref n)
				{
					set_chapter(n.kind());
					set_text_from_page(n.index());
				}

		protected:

				nik_ce bool overlay(size_ctype n, size_ctype m)
				{
					set_chapter(n);

					if (page_method.is_full() || base::ctext().lacks_capacity(m)) return false;

					page_method.push(ival_type{base::text().expand(m), m});

					return true;
				}

				nik_ce auto fast_deallocate_last()
				{
					base::text().downsize(base::page_cmethod.clast()->size());
					base::page().downsize();
				}

				nik_ce auto deallocate_last()
				{
					set_text_ival(0, 0);
					fast_deallocate_last();
				}

		public:

				nik_ce auto allocate(size_ctype n, size_ctype m)
				{
					if (not overlay(n, m)) return base::fail_note();

					set_text_from_page(base::page_cmethod.max());

					return base::make_note(n, base::page_cmethod.max());
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

