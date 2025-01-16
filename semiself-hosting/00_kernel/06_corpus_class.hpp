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

			nik_ce plot_model() { terminal.fullsize(); }

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

			using model_ctype_ptr		= typename alias<Model>::ctype_ptr;
			using model_ctype_cptr		= typename alias<Model>::ctype_cptr;

			using type			= typename Model::type;
			using type_ptr			= typename Model::type_ptr;
			using type_cptr			= typename Model::type_cptr;
			using type_ref			= typename Model::type_ref;

			using ctype			= typename Model::ctype;
			using ctype_ptr			= typename Model::ctype_ptr;
			using ctype_cptr		= typename Model::ctype_cptr;
			using ctype_ref			= typename Model::ctype_ref;

			using citer_type		= typename Model::citer_type;
			using citer_type_ptr		= typename Model::citer_type_ptr;
			using citer_type_cptr		= typename Model::citer_type_cptr;
			using citer_type_ref		= typename Model::citer_type_ref;

			using citer_ctype		= typename Model::citer_ctype;
			using citer_ctype_ptr		= typename Model::citer_ctype_ptr;
			using citer_ctype_cptr		= typename Model::citer_ctype_cptr;
			using citer_ctype_ref		= typename Model::citer_ctype_ref;

			using cderef_type		= typename Model::cderef_type;
			using cderef_type_ptr		= typename Model::cderef_type_ptr;
			using cderef_type_cptr		= typename Model::cderef_type_cptr;
			using cderef_type_ref		= typename Model::cderef_type_ref;

			using cderef_ctype		= typename Model::cderef_ctype;
			using cderef_ctype_ptr		= typename Model::cderef_ctype_ptr;
			using cderef_ctype_cptr		= typename Model::cderef_ctype_cptr;
			using cderef_ctype_ref		= typename Model::cderef_ctype_ref;

			using size_type			= typename Model::size_type;
			using size_ctype		= typename Model::size_ctype;

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

			using model_type_ptr		= typename alias<Model>::type_ptr;
			using model_type_cptr		= typename alias<Model>::type_cptr;

			using type			= typename Model::type;
			using type_ptr			= typename Model::type_ptr;
			using type_cptr			= typename Model::type_cptr;
			using type_ref			= typename Model::type_ref;

			using ctype			= typename Model::ctype;
			using ctype_ptr			= typename Model::ctype_ptr;
			using ctype_cptr		= typename Model::ctype_cptr;
			using ctype_ref			= typename Model::ctype_ref;

			using citer_type		= typename Model::citer_type;
			using citer_type_ptr		= typename Model::citer_type_ptr;
			using citer_type_cptr		= typename Model::citer_type_cptr;
			using citer_type_ref		= typename Model::citer_type_ref;

			using citer_ctype		= typename Model::citer_ctype;
			using citer_ctype_ptr		= typename Model::citer_ctype_ptr;
			using citer_ctype_cptr		= typename Model::citer_ctype_cptr;
			using citer_ctype_ref		= typename Model::citer_ctype_ref;

			using iter_type			= typename Model::iter_type;
			using iter_type_ptr		= typename Model::iter_type_ptr;
			using iter_type_cptr		= typename Model::iter_type_cptr;
			using iter_type_ref		= typename Model::iter_type_ref;

			using iter_ctype		= typename Model::iter_ctype;
			using iter_ctype_ptr		= typename Model::iter_ctype_ptr;
			using iter_ctype_cptr		= typename Model::iter_ctype_cptr;
			using iter_ctype_ref		= typename Model::iter_ctype_ref;

			using cderef_type		= typename Model::cderef_type;
			using cderef_type_ptr		= typename Model::cderef_type_ptr;
			using cderef_type_cptr		= typename Model::cderef_type_cptr;
			using cderef_type_ref		= typename Model::cderef_type_ref;

			using cderef_ctype		= typename Model::cderef_ctype;
			using cderef_ctype_ptr		= typename Model::cderef_ctype_ptr;
			using cderef_ctype_cptr		= typename Model::cderef_ctype_cptr;
			using cderef_ctype_ref		= typename Model::cderef_ctype_ref;

			using deref_type		= typename Model::deref_type;
			using deref_type_ptr		= typename Model::deref_type_ptr;
			using deref_type_cptr		= typename Model::deref_type_cptr;
			using deref_type_ref		= typename Model::deref_type_ref;

			using deref_ctype		= typename Model::deref_ctype;
			using deref_ctype_ptr		= typename Model::deref_ctype_ptr;
			using deref_ctype_cptr		= typename Model::deref_ctype_cptr;
			using deref_ctype_ref		= typename Model::deref_ctype_ref;

			using size_type			= typename Model::size_type;
			using size_ctype		= typename Model::size_ctype;

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

// plot:

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, SizeType... Sizes>
	class plot : public array_method<plot_model<Type, SizeType, Sizes...>>
	{
		public:

			using model			= plot_model<Type, SizeType, Sizes...>;
			using base			= array_method<model>;
			using cfacade_type		= plot_cfacade<model>;
			using facade_type		= plot_facade<model>;
			using cmethod_type		= array_cmethod<cfacade_type>;
			using method_type		= array_method<facade_type>;

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

// logo model:

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, SizeType Size, SizeType... Sizes>
	class logo_model
	{
		public:

			using facade			= logo_model; // method compatible.

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

		protected:

			page_type above;
			text_type below;

		public:

			nik_ce logo_model() { }

			// above:

				nik_ce page_ctype_ptr cpage() const { return &above; }
				nik_ce  page_type_ptr  page()       { return &above; }

			// below:

				nik_ce text_ctype_ptr ctext() const { return &below; }
				nik_ce  text_type_ptr  text()       { return &below; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// facade:

/***********************************************************************************************************************/

// immutable:

	template<typename Model>
	class logo_cfacade
	{
		public:

			using facade			= logo_cfacade; // method compatible.

			using page_type			= typename Model::page_type;
			using page_ctype		= typename alias<page_type>::ctype;
			using page_ctype_ptr		= typename alias<page_type>::ctype_ptr;
			using page_ctype_cptr		= typename alias<page_type>::ctype_cptr;
			using page_ctype_ref		= typename alias<page_type>::ctype_ref;

			using text_type			= typename Model::text_type;
			using text_ctype		= typename alias<text_type>::ctype;
			using text_ctype_ptr		= typename alias<text_type>::ctype_ptr;
			using text_ctype_cptr		= typename alias<text_type>::ctype_cptr;
			using text_ctype_ref		= typename alias<text_type>::ctype_ref;

			using size_type			= typename Model::size_type;
			using size_ctype		= typename Model::size_ctype;

		protected:

			page_ctype_ptr above;
			text_ctype_ptr below;

		public:

			nik_ce logo_cfacade() : above{}, below{} { }
			nik_ce logo_cfacade(page_ctype_cptr a, text_ctype_cptr b) : above{a}, below{b} { }

			// above:

				nik_ce page_ctype_ref cpage() const { return *above; }

			// below:

				nik_ce text_ctype_ref ctext() const { return *below; }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Model>
	class logo_facade
	{
		public:

			using facade			= logo_facade; // method compatible.

			using page_type			= typename Model::page_type;
			using page_type_ptr		= typename alias<page_type>::type_ptr;
			using page_type_cptr		= typename alias<page_type>::type_cptr;
			using page_type_ref		= typename alias<page_type>::type_ref;
			using page_ctype_ref		= typename alias<page_type>::ctype_ref;

			using text_type			= typename Model::text_type;
			using text_type_ptr		= typename alias<text_type>::type_ptr;
			using text_type_cptr		= typename alias<text_type>::type_cptr;
			using text_type_ref		= typename alias<text_type>::type_ref;
			using text_ctype_ref		= typename alias<text_type>::ctype_ref;

			using size_type			= typename Model::size_type;
			using size_ctype		= typename Model::size_ctype;

		protected:

			page_type_ptr above;
			text_type_ptr below;

		protected:

			using page_cmethod		= resolve_cmethod<page_type, array_cmethod>;
			using page_method		= resolve_method <page_type,  array_method>;

			using text_cmethod		= resolve_cmethod<text_type, array_cmethod>;
			using text_method		= resolve_method <text_type,  array_method>;

			using subtext_cmethod		= resolve_csubmethod<text_type, subarray_cmethod>;
			using subtext_method		= resolve_submethod <text_type,  subarray_method>;

			// above:

				nik_ce auto cpage_equip(size_ctype n) const
					{ return above->template cequip<page_cmethod>(n); }

				nik_ce auto page_equip(size_ctype n) const
					{ return above->template equip<page_method>(n); }

			// below:

				nik_ce auto ctext_equip() const
					{ return below->template cequip<text_cmethod>(); }

				nik_ce auto text_equip() const
					{ return below->template equip<text_method>(); }

				nik_ce auto ctext_right_equip(size_ctype n) const
					{ return below->template right_cequip<subtext_cmethod>(n); }

				nik_ce auto text_right_equip(size_ctype n) const
					{ return below->template right_equip<subtext_method>(n); }

		protected:

			nik_ce bool overlay(size_ctype kind, size_ctype n)
			{
				auto above_method = page_equip(kind);

				if (above_method.is_full() || below->lacks_capacity(n)) return false;

				above_method.push(below->expand(n));

				return true;
			}

			nik_ce size_type initialize_last(size_ctype kind, size_ctype tag)
			{
				auto above_cmethod = cpage_equip(kind);
				auto below_method  = text_right_equip(*above_cmethod.clast());
				below_method[tag]  = kind;

				return above_cmethod.max();
			}

		public:

			nik_ce logo_facade() : above{}, below{} { }
			nik_ce logo_facade(page_type_cptr a, text_type_cptr b) : above{a}, below{b} { }

			// above:

				nik_ce page_ctype_ref cpage() const { return *above; }
				nik_ce  page_type_ref  page()       { return *above; }

			// below:

				nik_ce text_ctype_ref ctext() const { return *below; }
				nik_ce  text_type_ref  text()       { return *below; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// logo:

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, SizeType Size, SizeType... Sizes>
	class logo : public logo_model<Type, SizeType, Size, Sizes...>
	{
		public:

			using base			= logo_model<Type, SizeType, Size, Sizes...>;
			using model			= base;
			using cfacade_type		= logo_cfacade<model>;
			using facade_type		= logo_facade<model>;

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

			nik_ce logo() : base{} { }

			// equip:

				template<typename CMethod>
				nik_ce auto cequip() const -> CMethod
					{ return cfacade_type{base::cpage(), base::ctext()}; }

				template<typename Method>
				nik_ce auto equip() -> Method
					{ return facade_type{base::page(), base::text()}; }
	};

/***********************************************************************************************************************/

// ring:

	template<typename SizeType>
	struct Logo
	{
		using size_type		= typename alias<SizeType>::type;
		using size_ctype	= typename alias<SizeType>::ctype;

		using ring_type		= logo<size_type, size_type, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0>;
		using ring_method	= resolve_method<ring_type, logo_ring_method>;

		nik_ces auto ring(size_ctype n)
		{
			auto ring_value  = ring_type{};
			auto global_ring = ring_value.template equip<ring_method>();
			auto ring_gram   = global_ring.initialize();

			// test if ring_gram is fail.
			auto local_ring  = global_ring.text_right_equip(ring_gram);

			local_ring[LogoRing::bits] = n;

			return ring_value;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// target:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// system:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// corpus:

	// in order to apply functions internal to a given type system,
	// they have to be known before the use of the type system itself.
	// this is a metacompile time that precedes metarun time.
	// in order to achieve this, type systems should be designed
	// to accept metacompile time type data as well as its metarun time data.

	// instead, just get the apply method to accept metacompile time type system objects,
	// as well as sagement objects. this way you can apply accordingly, while still maintaining
	// the type system forms.

/***********************************************************************************************************************/

// judgment:

/***********************************************************************************************************************/

// interface:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

