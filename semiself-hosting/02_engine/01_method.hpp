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

// method:

namespace cctmp  {
namespace engine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// model:

	template<typename...> class plot_cmodel;
	template<typename...> class plot_model;

/***********************************************************************************************************************/

// immutable:

	template<auto... Us, typename SizeType>
	class plot_cmodel<T_pack_Vs<Us...>, SizeType> : public ctuple<SizeType, carray<T_store_U<Us>, SizeType>...>
	{
		public:

			using base		= ctuple<SizeType, carray<T_store_U<Us>, SizeType>...>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			template<size_type n>
			using level_type = typename base::template sub_type<n>::type;

			nik_ces size_type apex  () { return base::length() - 1; }
			nik_ces size_type order () { return apex() - 1; }

		public:

			nik_ce plot_cmodel() : base{} { }
			nik_ce plot_cmodel(const carray<T_store_U<Us>, SizeType> &... as) : base{as...} { }

			template<size_ctype n>
			nik_ce auto cbegin() const { return base::template cvalue<n>().cbegin(); }
	};

	// syntactic sugar:

		template<typename... Ts, typename SizeType>
		nik_ces auto make_plot_cmodel(const carray<Ts, SizeType> &... as)
			{ return plot_cmodel<T_pack_Vs<U_store_T<Ts>...>, SizeType>{as...}; }

/***********************************************************************************************************************/

// mutable:

	template<auto... Us, auto... Sizes, typename SizeType>
	class plot_model<T_pack_Vs<Us...>, T_pack_Vs<Sizes...>, SizeType> :
		public tuple<SizeType, array<T_store_U<Us>, SizeType, Sizes>...>
	{
		public:

			using base		= tuple<SizeType, array<T_store_U<Us>, SizeType, Sizes>...>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			template<size_type n>
			using level_type = typename base::template sub_type<n>::type;

			nik_ces size_type apex  () { return base::length() - 1; }
			nik_ces size_type order () { return apex() - 1; }

		public:

			nik_ce plot_model() : base{} { }
			nik_ce plot_model(const array<T_store_U<Us>, SizeType, Sizes> &... as) : base{as...} { }

			template<size_ctype n>
			nik_ce auto cbegin() const { return base::template cvalue<n>().cbegin(); }

			template<size_ctype n>
			nik_ce auto begin() { return base::template value<n>().begin(); }
	};

	// syntactic sugar:

		template<typename... Ts, typename SizeType, auto... Is>
		nik_ces auto make_plot_model(const array<Ts, SizeType, Is> &... as)
			{ return plot_model<T_pack_Vs<U_store_T<Ts>...>, T_pack_Vs<Is...>, SizeType>{as...}; }

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// form:

/***********************************************************************************************************************/

// immutable:

	template<typename Model, gkey_type Order>
	class plot_cform
	{
		public:

			using model_type		= typename alias<Model>::type;
			using model_type_ptr		= typename alias<Model>::type_ptr;
			using model_type_cptr		= typename alias<Model>::type_cptr;
			using model_type_ref		= typename alias<Model>::type_ref;

			using model_ctype		= typename alias<Model>::ctype;
			using model_ctype_ptr		= typename alias<Model>::ctype_ptr;
			using model_ctype_cptr		= typename alias<Model>::ctype_cptr;
			using model_ctype_ref		= typename alias<Model>::ctype_ref;

			using page_type			= typename Model::template level_type<Order + 1>;
			using page_type_ptr		= typename alias<page_type>::type_ptr;
			using page_type_cptr		= typename alias<page_type>::type_cptr;
			using page_type_ref		= typename alias<page_type>::type_ref;

			using page_ctype		= typename alias<page_type>::ctype;
			using page_ctype_ptr		= typename alias<page_type>::ctype_ptr;
			using page_ctype_cptr		= typename alias<page_type>::ctype_cptr;
			using page_ctype_ref		= typename alias<page_type>::ctype_ref;

			using text_type			= typename Model::template level_type<Order>;
			using text_type_ptr		= typename alias<text_type>::type_ptr;
			using text_type_cptr		= typename alias<text_type>::type_cptr;
			using text_type_ref		= typename alias<text_type>::type_ref;

			using text_ctype		= typename alias<text_type>::ctype;
			using text_ctype_ptr		= typename alias<text_type>::ctype_ptr;
			using text_ctype_cptr		= typename alias<text_type>::ctype_cptr;
			using text_ctype_ref		= typename alias<text_type>::ctype_ref;

			using size_type			= typename Model::size_type;
			using size_ctype		= typename Model::size_ctype;

		protected:

			model_ctype_ptr model;
			 page_ctype_ptr  leaf;

		protected:

			template<typename Method, typename Facade, typename Pointer>
			nik_ce Method pivot(Pointer p) const { return Facade{model, p}; }

		public:

			nik_ce plot_cform() : model{}, leaf{} { }
			nik_ce plot_cform(model_ctype_ptr m, page_ctype_cptr p) : model{m}, leaf{p} { }

			nik_ce bool comparable(const plot_cform & f) const { return (*model == *f.model); }

			nik_ce page_ctype_ptr cpage() const { return leaf; }
			nik_ce text_ctype_ptr ctext() const { return model->template cbegin<Order>() + leaf->start(); }

			// terminal:

				nik_ce size_type size() const { return leaf->size(); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Model, gkey_type Order>
	class plot_form
	{
		public:

			using model_type		= typename alias<Model>::type;
			using model_type_ptr		= typename alias<Model>::type_ptr;
			using model_type_cptr		= typename alias<Model>::type_cptr;
			using model_type_ref		= typename alias<Model>::type_ref;

			using model_ctype		= typename alias<Model>::ctype;
			using model_ctype_ptr		= typename alias<Model>::ctype_ptr;
			using model_ctype_cptr		= typename alias<Model>::ctype_cptr;
			using model_ctype_ref		= typename alias<Model>::ctype_ref;

			using page_type			= typename Model::template level_type<Order + 1>;
			using page_type_ptr		= typename alias<page_type>::type_ptr;
			using page_type_cptr		= typename alias<page_type>::type_cptr;
			using page_type_ref		= typename alias<page_type>::type_ref;

			using page_ctype		= typename alias<page_type>::ctype;
			using page_ctype_ptr		= typename alias<page_type>::ctype_ptr;
			using page_ctype_cptr		= typename alias<page_type>::ctype_cptr;
			using page_ctype_ref		= typename alias<page_type>::ctype_ref;

			using text_type			= typename Model::template level_type<Order>;
			using text_type_ptr		= typename alias<text_type>::type_ptr;
			using text_type_cptr		= typename alias<text_type>::type_cptr;
			using text_type_ref		= typename alias<text_type>::type_ref;

			using text_ctype		= typename alias<text_type>::ctype;
			using text_ctype_ptr		= typename alias<text_type>::ctype_ptr;
			using text_ctype_cptr		= typename alias<text_type>::ctype_cptr;
			using text_ctype_ref		= typename alias<text_type>::ctype_ref;

			using size_type			= typename Model::size_type;
			using size_ctype		= typename Model::size_ctype;

		protected:

			model_type_ptr model;
			 page_type_ptr  leaf;

		protected:

			template<typename Method, typename Facade, typename Pointer>
			nik_ce Method pivot(Pointer p) const { return Facade{model, p}; }

		public:

			nik_ce plot_form() : model{}, leaf{} { }
			nik_ce plot_form(model_type_ptr m, page_type_cptr p) : model{m}, leaf{p} { }

			nik_ce bool comparable(const plot_form & f) const { return (*model == *f.model); }

			nik_ce page_ctype_ptr cpage() const { return leaf; }
			nik_ce text_ctype_ptr ctext() const { return model->template cbegin<Order>() + leaf->start(); }

			nik_ce page_type_ptr page() { return leaf; }
			nik_ce text_type_ptr text() { return model->template begin<Order>() + leaf->start(); }

			// terminal:

				nik_ce size_type size() const { return leaf->size(); }
				nik_ce void set_size(size_ctype n) { return leaf->set_size(n); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cfacade:

	template<typename> class citerator_method;
	template<typename> class  iterator_method;

/***********************************************************************************************************************/

// N >= 1:

	template<typename Model, gkey_type Order>
	class plot_cfacade : public plot_cform<Model, Order>
	{
		protected:

			using level_cfacade		= plot_cfacade;
			using level_cmethod		= array_cmethod<level_cfacade>;

			using below_cfacade		= plot_cfacade<Model, Order - 1>;
			using below_cmethod		= array_cmethod<below_cfacade>;

		public:

			using base			= plot_cform<Model, Order>;

			using model_type		= typename base::model_type;
			using model_type_ptr		= typename base::model_type_ptr;
			using model_type_cptr		= typename base::model_type_cptr;
			using model_type_ref		= typename base::model_type_ref;

			using model_ctype		= typename base::model_ctype;
			using model_ctype_ptr		= typename base::model_ctype_ptr;
			using model_ctype_cptr		= typename base::model_ctype_cptr;
			using model_ctype_ref		= typename base::model_ctype_ref;

			using type			= typename base::text_type;
			using type_ptr			= typename base::text_type_ptr;
			using type_cptr			= typename base::text_type_cptr;
			using type_ref			= typename base::text_type_ref;

			using ctype			= typename base::text_ctype;
			using ctype_ptr			= typename base::text_ctype_ptr;
			using ctype_cptr		= typename base::text_ctype_cptr;
			using ctype_ref			= typename base::text_ctype_ref;

			using citer_type		= citerator_method<level_cmethod>;
			using citer_type_ptr		= typename alias<citer_type>::type_ptr;
			using citer_type_cptr		= typename alias<citer_type>::type_cptr;
			using citer_type_ref		= typename alias<citer_type>::type_ref;

			using citer_ctype		= typename alias<citer_type>::ctype;
			using citer_ctype_ptr		= typename alias<citer_type>::ctype_ptr;
			using citer_ctype_cptr		= typename alias<citer_type>::ctype_cptr;
			using citer_ctype_ref		= typename alias<citer_type>::ctype_ref;

			using cderef_type		= below_cmethod;
			using cderef_type_ptr		= typename alias<cderef_type>::type_ptr;
			using cderef_type_cptr		= typename alias<cderef_type>::type_cptr;
			using cderef_type_ref		= typename alias<cderef_type>::type_ref;

			using cderef_ctype		= typename alias<cderef_type>::ctype;
			using cderef_ctype_ptr		= typename alias<cderef_type>::ctype_ptr;
			using cderef_ctype_cptr		= typename alias<cderef_type>::ctype_cptr;
			using cderef_ctype_ref		= typename alias<cderef_type>::ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce plot_cfacade() : base{} { }
			nik_ce plot_cfacade(model_ctype_ptr m, typename base::page_ctype_cptr p) : base{m, p} { }

			nik_ce auto pivot(typename base::page_ctype_cptr p) const -> level_cmethod
				{ return base::template pivot<level_cmethod, level_cfacade>(p); }

			// initial:

				nik_ce citer_type cbegin() const
				{
					return citer_type
						{ base::template pivot<below_cmethod, below_cfacade>(base::ctext()) };
				}
	};

/***********************************************************************************************************************/

// 0:

	template<typename Model>
	class plot_cfacade<Model, 0> : public plot_cform<Model, 0>
	{
		public:

			using base			= plot_cform<Model, 0>;

			using model_type		= typename base::model_type;
			using model_type_ptr		= typename base::model_type_ptr;
			using model_type_cptr		= typename base::model_type_cptr;
			using model_type_ref		= typename base::model_type_ref;

			using model_ctype		= typename base::model_ctype;
			using model_ctype_ptr		= typename base::model_ctype_ptr;
			using model_ctype_cptr		= typename base::model_ctype_cptr;
			using model_ctype_ref		= typename base::model_ctype_ref;

			using type			= typename base::text_type;
			using type_ptr			= typename base::text_type_ptr;
			using type_cptr			= typename base::text_type_cptr;
			using type_ref			= typename base::text_type_ref;

			using ctype			= typename base::text_ctype;
			using ctype_ptr			= typename base::text_ctype_ptr;
			using ctype_cptr		= typename base::text_ctype_cptr;
			using ctype_ref			= typename base::text_ctype_ref;

			using citer_type		= typename alias<ctype_ptr>::type;
			using citer_type_ptr		= typename alias<ctype_ptr>::type_ptr;
			using citer_type_cptr		= typename alias<ctype_ptr>::type_cptr;
			using citer_type_ref		= typename alias<ctype_ptr>::type_ref;

			using citer_ctype		= typename alias<ctype_ptr>::ctype;
			using citer_ctype_ptr		= typename alias<ctype_ptr>::ctype_ptr;
			using citer_ctype_cptr		= typename alias<ctype_ptr>::ctype_cptr;
			using citer_ctype_ref		= typename alias<ctype_ptr>::ctype_ref;

			using cderef_type		= typename alias<ctype>::type;
			using cderef_type_ptr		= typename alias<ctype>::type_ptr;
			using cderef_type_cptr		= typename alias<ctype>::type_cptr;
			using cderef_type_ref		= typename alias<ctype>::type_ref;

			using cderef_ctype		= typename alias<ctype>::ctype;
			using cderef_ctype_ptr		= typename alias<ctype>::ctype_ptr;
			using cderef_ctype_cptr		= typename alias<ctype>::ctype_cptr;
			using cderef_ctype_ref		= typename alias<ctype>::ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		protected:

			using level_cfacade		= plot_cfacade;
			using level_cmethod		= array_cmethod<level_cfacade>;

		public:

			nik_ce plot_cfacade() : base{} { }
			nik_ce plot_cfacade(model_ctype_ptr m, typename base::page_ctype_cptr p) : base{m, p} { }

			nik_ce level_cmethod pivot(typename base::page_ctype_cptr p) const
				{ return base::template pivot<level_cmethod, level_cfacade>(p); }

			// initial:

				nik_ce citer_type cbegin() const { return base::ctext(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// facade:

/***********************************************************************************************************************/

// N >= 1:

	template<typename Model, gkey_type Order>
	class plot_facade : public plot_form<Model, Order>
	{
		protected:

			using level_cfacade		= plot_cfacade<Model, Order>;
			using level_cmethod		= array_cmethod<level_cfacade>;

			using level_facade		= plot_facade;
			using level_method		= array_method<level_facade>;

			using below_cfacade		= plot_cfacade<Model, Order - 1>;
			using below_cmethod		= array_cmethod<below_cfacade>;

			using below_facade		= plot_facade<Model, Order - 1>;
			using below_method		= array_method<below_facade>;

		public:

			using base			= plot_form<Model, Order>;

			using model_type		= typename base::model_type;
			using model_type_ptr		= typename base::model_type_ptr;
			using model_type_cptr		= typename base::model_type_cptr;
			using model_type_ref		= typename base::model_type_ref;

			using model_ctype		= typename base::model_ctype;
			using model_ctype_ptr		= typename base::model_ctype_ptr;
			using model_ctype_cptr		= typename base::model_ctype_cptr;
			using model_ctype_ref		= typename base::model_ctype_ref;

			using type			= typename base::text_type;
			using type_ptr			= typename base::text_type_ptr;
			using type_cptr			= typename base::text_type_cptr;
			using type_ref			= typename base::text_type_ref;

			using ctype			= typename base::text_ctype;
			using ctype_ptr			= typename base::text_ctype_ptr;
			using ctype_cptr		= typename base::text_ctype_cptr;
			using ctype_ref			= typename base::text_ctype_ref;

			using citer_type		= citerator_method<level_cmethod>;
			using citer_type_ptr		= typename alias<citer_type>::type_ptr;
			using citer_type_cptr		= typename alias<citer_type>::type_cptr;
			using citer_type_ref		= typename alias<citer_type>::type_ref;

			using citer_ctype		= typename alias<citer_type>::ctype;
			using citer_ctype_ptr		= typename alias<citer_type>::ctype_ptr;
			using citer_ctype_cptr		= typename alias<citer_type>::ctype_cptr;
			using citer_ctype_ref		= typename alias<citer_type>::ctype_ref;

			using iter_type			= iterator_method<level_method>;
			using iter_type_ptr		= typename alias<iter_type>::type_ptr;
			using iter_type_cptr		= typename alias<iter_type>::type_cptr;
			using iter_type_ref		= typename alias<iter_type>::type_ref;

			using iter_ctype		= typename alias<iter_type>::ctype;
			using iter_ctype_ptr		= typename alias<iter_type>::ctype_ptr;
			using iter_ctype_cptr		= typename alias<iter_type>::ctype_cptr;
			using iter_ctype_ref		= typename alias<iter_type>::ctype_ref;

			using cderef_type		= below_cmethod;
			using cderef_type_ptr		= typename alias<cderef_type>::type_ptr;
			using cderef_type_cptr		= typename alias<cderef_type>::type_cptr;
			using cderef_type_ref		= typename alias<cderef_type>::type_ref;

			using cderef_ctype		= typename alias<cderef_type>::ctype;
			using cderef_ctype_ptr		= typename alias<cderef_type>::ctype_ptr;
			using cderef_ctype_cptr		= typename alias<cderef_type>::ctype_cptr;
			using cderef_ctype_ref		= typename alias<cderef_type>::ctype_ref;

			using deref_type		= below_method;
			using deref_type_ptr		= typename alias<deref_type>::type_ptr;
			using deref_type_cptr		= typename alias<deref_type>::type_cptr;
			using deref_type_ref		= typename alias<deref_type>::type_ref;

			using deref_ctype		= typename alias<deref_type>::ctype;
			using deref_ctype_ptr		= typename alias<deref_type>::ctype_ptr;
			using deref_ctype_cptr		= typename alias<deref_type>::ctype_cptr;
			using deref_ctype_ref		= typename alias<deref_type>::ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce plot_facade() : base{} { }
			nik_ce plot_facade(model_type_ptr m, typename base::page_type_cptr p) : base{m, p} { }

			nik_ce level_cmethod pivot(typename base::page_ctype_cptr p) const
				{ return base::template pivot<level_cmethod, level_cfacade>(p); }

			nik_ce level_method pivot(typename base::page_type_cptr p) const
				{ return base::template pivot<level_method, level_facade>(p); }

			// initial:

				nik_ce citer_type cbegin() const
				{
					return citer_type
						{ base::template pivot<below_cmethod, below_cfacade>(base::ctext()) };
				}

				nik_ce iter_type begin()
				{
					return iter_type
						{ base::template pivot<below_method, below_facade>(base::text()) };
				}
	};

/***********************************************************************************************************************/

// 0:

	template<typename Model>
	class plot_facade<Model, 0> : public plot_form<Model, 0>
	{
		public:

			using base			= plot_form<Model, 0>;

			using model_type		= typename base::model_type;
			using model_type_ptr		= typename base::model_type_ptr;
			using model_type_cptr		= typename base::model_type_cptr;
			using model_type_ref		= typename base::model_type_ref;

			using model_ctype		= typename base::model_ctype;
			using model_ctype_ptr		= typename base::model_ctype_ptr;
			using model_ctype_cptr		= typename base::model_ctype_cptr;
			using model_ctype_ref		= typename base::model_ctype_ref;

			using type			= typename base::text_type;
			using type_ptr			= typename base::text_type_ptr;
			using type_cptr			= typename base::text_type_cptr;
			using type_ref			= typename base::text_type_ref;

			using ctype			= typename base::text_ctype;
			using ctype_ptr			= typename base::text_ctype_ptr;
			using ctype_cptr		= typename base::text_ctype_cptr;
			using ctype_ref			= typename base::text_ctype_ref;

			using citer_type		= typename alias<ctype_ptr>::type;
			using citer_type_ptr		= typename alias<ctype_ptr>::type_ptr;
			using citer_type_cptr		= typename alias<ctype_ptr>::type_cptr;
			using citer_type_ref		= typename alias<ctype_ptr>::type_ref;

			using citer_ctype		= typename alias<ctype_ptr>::ctype;
			using citer_ctype_ptr		= typename alias<ctype_ptr>::ctype_ptr;
			using citer_ctype_cptr		= typename alias<ctype_ptr>::ctype_cptr;
			using citer_ctype_ref		= typename alias<ctype_ptr>::ctype_ref;

			using iter_type			= typename alias<type_ptr>::type;
			using iter_type_ptr		= typename alias<type_ptr>::type_ptr;
			using iter_type_cptr		= typename alias<type_ptr>::type_cptr;
			using iter_type_ref		= typename alias<type_ptr>::type_ref;

			using iter_ctype		= typename alias<type_ptr>::ctype;
			using iter_ctype_ptr		= typename alias<type_ptr>::ctype_ptr;
			using iter_ctype_cptr		= typename alias<type_ptr>::ctype_cptr;
			using iter_ctype_ref		= typename alias<type_ptr>::ctype_ref;

			using cderef_type		= typename alias<ctype>::type;
			using cderef_type_ptr		= typename alias<ctype>::type_ptr;
			using cderef_type_cptr		= typename alias<ctype>::type_cptr;
			using cderef_type_ref		= typename alias<ctype>::type_ref;

			using cderef_ctype		= typename alias<ctype>::ctype;
			using cderef_ctype_ptr		= typename alias<ctype>::ctype_ptr;
			using cderef_ctype_cptr		= typename alias<ctype>::ctype_cptr;
			using cderef_ctype_ref		= typename alias<ctype>::ctype_ref;

			using deref_type		= typename alias<type>::type;
			using deref_type_ptr		= typename alias<type>::type_ptr;
			using deref_type_cptr		= typename alias<type>::type_cptr;
			using deref_type_ref		= typename alias<type>::type_ref;

			using deref_ctype		= typename alias<type>::ctype;
			using deref_ctype_ptr		= typename alias<type>::ctype_ptr;
			using deref_ctype_cptr		= typename alias<type>::ctype_cptr;
			using deref_ctype_ref		= typename alias<type>::ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		protected:

			using level_cfacade		= plot_cfacade<Model, 0>;
			using level_cmethod		= array_cmethod<level_cfacade>;

			using level_facade		= plot_facade;
			using level_method		= array_method<level_facade>;

		public:

			nik_ce plot_facade() : base{} { }
			nik_ce plot_facade(model_type_ptr m, typename base::page_type_cptr p) : base{m, p} { }

			nik_ce level_cmethod pivot(typename base::page_ctype_cptr p) const
				{ return base::template pivot<level_cmethod, level_cfacade>(p); }

			nik_ce level_method pivot(typename base::page_type_cptr p) const
				{ return base::template pivot<level_method, level_facade>(p); }

			// initial:

				nik_ce citer_type cbegin() const { return base::ctext(); }
				nik_ce iter_type   begin()       { return base:: text(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// iterator:

/***********************************************************************************************************************/

// immutable:

	template<typename ArrayMethod>
	class citerator_method
	{
		public:

			using cderef_type		= typename ArrayMethod::cderef_type;
			using cderef_type_ptr		= typename ArrayMethod::cderef_type_ptr;
			using cderef_type_cptr		= typename ArrayMethod::cderef_type_cptr;
			using cderef_type_ref		= typename ArrayMethod::cderef_type_ref;

			using cderef_ctype		= typename ArrayMethod::cderef_ctype;
			using cderef_ctype_ptr		= typename ArrayMethod::cderef_ctype_ptr;
			using cderef_ctype_cptr		= typename ArrayMethod::cderef_ctype_cptr;
			using cderef_ctype_ref		= typename ArrayMethod::cderef_ctype_ref;

			using size_type			= typename ArrayMethod::size_type;
			using size_ctype		= typename ArrayMethod::size_ctype;

		protected:

			cderef_type sub;

		protected:

			nik_ce auto sub_increment(size_ctype n = 1) const { return sub.pivot(sub.cpage() + n); }
			nik_ce auto sub_decrement(size_ctype n = 1) const { return sub.pivot(sub.cpage() - n); }

			nik_ce void cincrement(size_ctype n = 1) { sub = sub_increment(n); }
			nik_ce void cdecrement(size_ctype n = 1) { sub = sub_decrement(n); }

			nik_ce auto post_cincrement(size_ctype n = 1) -> citerator_method
				{ citerator_method post{*this}; cincrement(n); return post; }

			nik_ce auto post_cdecrement(size_ctype n = 1) -> citerator_method
				{ citerator_method post{*this}; cdecrement(n); return post; }

		public:

			nik_ce citerator_method() : sub{} { }
			nik_ce citerator_method(cderef_ctype_ref s) : sub{s} { }

			// immutable:

				nik_ce bool comparable(const citerator_method & i) const
					{ return sub.comparable(i.sub); }

				nik_ce bool operator == (const citerator_method & i) const
					{ return (sub.cpage() == i.sub.cpage()); }

				nik_ce bool operator != (const citerator_method & i) const
					{ return not operator == (i); }

				nik_ce cderef_ctype_ref operator  * () const { return sub; }
				nik_ce cderef_ctype_ptr operator -> () const { return &sub; }

				nik_ce citerator_method operator + (size_ctype n) const
					{ return citerator_method{sub_increment(n)}; }

				nik_ce citerator_method operator - (size_ctype n) const
					{ return citerator_method{sub_decrement(n)}; }

			// mutable:

				nik_ce citerator_method & operator ++ (   ) { cincrement(); return *this; }
				nik_ce citerator_method   operator ++ (int) { return post_cincrement(); }

				nik_ce citerator_method & operator -- (   ) { cdecrement(); return *this; }
				nik_ce citerator_method   operator -- (int) { return post_cdecrement(); }

				nik_ce citerator_method & operator += (size_ctype n) { cincrement(n); return *this; }
				nik_ce citerator_method & operator -= (size_ctype n) { cdecrement(n); return *this; }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename ArrayMethod>
	class iterator_method // does not inherit from citerator method.
	{
		public:

			using deref_type		= typename ArrayMethod::deref_type;
			using deref_type_ptr		= typename ArrayMethod::deref_type_ptr;
			using deref_type_cptr		= typename ArrayMethod::deref_type_cptr;
			using deref_type_ref		= typename ArrayMethod::deref_type_ref;

			using deref_ctype		= typename ArrayMethod::deref_ctype;
			using deref_ctype_ptr		= typename ArrayMethod::deref_ctype_ptr;
			using deref_ctype_cptr		= typename ArrayMethod::deref_ctype_cptr;
			using deref_ctype_ref		= typename ArrayMethod::deref_ctype_ref;

			using size_type			= typename ArrayMethod::size_type;
			using size_ctype		= typename ArrayMethod::size_ctype;

		protected:

			deref_type sub;

		protected:

			nik_ce auto sub_increment(size_ctype n = 1) { return sub.pivot(sub.page() + n); }
			nik_ce auto sub_decrement(size_ctype n = 1) { return sub.pivot(sub.page() - n); }

			nik_ce void increment(size_ctype n = 1) { sub = sub_increment(n); }
			nik_ce void decrement(size_ctype n = 1) { sub = sub_decrement(n); }

			nik_ce auto post_increment(size_ctype n = 1) -> iterator_method
				{ iterator_method post{*this}; increment(n); return post; }

			nik_ce auto post_decrement(size_ctype n = 1) -> iterator_method
				{ iterator_method post{*this}; decrement(n); return post; }

		public:

			nik_ce iterator_method() : sub{} { }
			nik_ce iterator_method(deref_ctype_ref s) : sub{s} { }

			// immutable:

				nik_ce bool comparable(const iterator_method & i) const
					{ return sub.comparable(i.sub); }

				nik_ce bool operator == (const iterator_method & i) const
					{ return (sub.cpage() == i.sub.cpage()); }

				nik_ce bool operator != (const iterator_method & i) const
					{ return not operator == (i); }

				nik_ce iterator_method operator + (size_ctype n) const
					{ return iterator_method{sub_increment(n)}; }

				nik_ce iterator_method operator - (size_ctype n) const
					{ return iterator_method{sub_decrement(n)}; }

			// mutable:

				nik_ce iterator_method & operator ++ (   ) { increment(); return *this; }
				nik_ce iterator_method   operator ++ (int) { return post_increment(); }

				nik_ce iterator_method & operator -- (   ) { decrement(); return *this; }
				nik_ce iterator_method   operator -- (int) { return post_decrement(); }

				nik_ce iterator_method & operator += (size_ctype n) { increment(n); return *this; }
				nik_ce iterator_method & operator -= (size_ctype n) { decrement(n); return *this; }

				nik_ce deref_type_ref operator  * () { return sub; }
				nik_ce deref_type_ptr operator -> () { return &sub; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::engine

