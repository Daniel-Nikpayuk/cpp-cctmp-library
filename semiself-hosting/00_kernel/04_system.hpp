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

// system:

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
/***********************************************************************************************************************/

// logo model:

/***********************************************************************************************************************/

// page type:

	template<typename SizeType>
	class logo_page_type
	{
		public:

			using size_type		= typename alias<SizeType>::type;
			using size_ctype	= typename alias<SizeType>::ctype;

		protected:

			size_type initial;
			size_type terminal;
			size_type length;

		public:

			nik_ce logo_page_type() :
				initial{}, terminal{}, length{} { }

			nik_ce logo_page_type(size_ctype i, size_ctype t, size_ctype l) :
				initial{i}, terminal{t}, length{l} { }

			nik_ce bool operator == (const logo_page_type & s) const
				{ return (terminal == s.terminal); }

			nik_ce bool operator != (const logo_page_type & s) const
				{ return not operator == (s); }

			// initial:

				nik_ce size_type start() const { return initial; }
				nik_ce void set_start(size_ctype i) { initial = i; }

			// terminal:

				nik_ce size_type size() const { return terminal; }
				nik_ce void set_size(size_ctype t) { terminal = t; }

			// length:

				nik_ce size_type capacity() const { return length; }
				nik_ce void set_capacity(size_ctype l) { length = l; }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, SizeType Size, SizeType... Sizes>
	class logo_model
	{
		public:

			using initial_type		= array<Type, SizeType, Size>;
			using initial_type_ref		= typename alias<initial_type>::type_ref;
			using initial_ctype_ref		= typename alias<initial_type>::ctype_ref;

			using type			= typename initial_type::type;
			using type_ptr			= typename initial_type::type_ptr;
			using type_cptr			= typename initial_type::type_cptr;
			using type_ref			= typename initial_type::type_ref;

			using ctype			= typename initial_type::ctype;
			using ctype_ptr			= typename initial_type::ctype_ptr;
			using ctype_cptr		= typename initial_type::ctype_cptr;
			using ctype_ref			= typename initial_type::ctype_ref;

			using size_type			= typename initial_type::size_type;
			using size_ctype		= typename initial_type::size_ctype;

			using page_type			= logo_page_type<size_type>;
			using terminal_type		= plot<page_type, size_type, Sizes...>;

		protected:

			using term_cmethod		= resolve_cmethod<terminal_type, array_cmethod>;
			using term_method		= resolve_method<terminal_type, array_method>;

			initial_type initial;
			terminal_type terminal;

		public:

			nik_ce logo_model() { }

			// page:

				nik_ce auto cpage(size_ctype n) const
					{ return terminal.template cequip<term_cmethod>(n); }

				nik_ce auto page(size_ctype n)
					{ return terminal.template equip<term_method>(n); }

			// text:

				nik_ce initial_ctype_ref ctext() const { return initial; }
				nik_ce  initial_type_ref  text()       { return initial; }
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

			nik_ce logo_cfacade() : model{}, locus{} { }
			nik_ce logo_cfacade(model_ctype_cptr m, size_ctype l) : model{m}, locus{l} { }

			// initial:

				nik_ce citer_type cbegin() const { return model->cbegin(); }

			// terminal:

				nik_ce size_type size() const { return model->size(); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Model>
	class logo_facade
	{
		public:

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

		public:

			nik_ces size_type length() { return Model::length(); }

		protected:

			model_type_ptr model;
			size_type locus;

		public:

			nik_ce logo_facade() : model{}, locus{} { }
			nik_ce logo_facade(model_type_cptr m, size_ctype l) : model{m}, locus{l} { }

			// initial:

			//	nik_ce citer_type cbegin() const { return model->cbegin(locus); }
			//	nik_ce  iter_type  begin()       { return model-> begin(locus); }

			// terminal:

			//	nik_ce size_type size() const { return model->size(locus); }
			//	nik_ce void set_size(size_ctype n) { model->set_size(locus, n); }

			// initial:

			//	nik_ce citer_type cbegin() const { return model->cbegin(); }
			//	nik_ce  iter_type  begin()       { return model-> begin(); }

			// terminal:

			//	nik_ce size_type size() const { return model->size(); }
			//	nik_ce void set_size(size_ctype n) { model->set_size(n); }
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
				nik_ce auto cequip(size_ctype n = 0) const -> CMethod
					{ return cfacade_type{static_cast<model const*>(this), n}; }

				template<typename Method>
				nik_ce auto equip(size_ctype n = 0) -> Method
					{ return facade_type{static_cast<model*>(this), n}; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

