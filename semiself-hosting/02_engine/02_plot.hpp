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

// plot:

namespace cctmp  {
namespace engine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// plot:

	template<typename...> class cplot;
	template<typename...> class plot;

/***********************************************************************************************************************/

// page type:

	template<typename SizeType>
	class plot_page_type
	{
		public:

			using size_type		= typename alias<SizeType>::type;
			using size_ctype	= typename alias<SizeType>::ctype;

		protected:

			size_type initial;
			size_type terminal;
			size_type length;

		public:

			nik_ce plot_page_type() :
				initial{}, terminal{}, length{} { }

			nik_ce plot_page_type(size_ctype i, size_ctype t, size_ctype l) :
				initial{i}, terminal{t}, length{l} { }

			nik_ce bool operator == (const plot_page_type & s) const
				{ return (terminal == s.terminal); }

			nik_ce bool operator != (const plot_page_type & s) const
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

// immutable:

	template<auto... Us, typename SizeType>
	class cplot<T_pack_Vs<Us...>, SizeType> : public plot_cmodel<T_pack_Vs<Us...>, SizeType>
	{
		public:

			using base			= plot_cmodel<T_pack_Vs<Us...>, SizeType>;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using cfacade_type		= plot_cfacade<cplot, base::order()>;
			using cmethod_type		= array_cmethod<cfacade_type>;

		public:

			nik_ce cplot() : base{} { }
			nik_ce cplot(const carray<T_store_U<Us>, SizeType> &... as) : base{as...} { }

			// equip:

				template<typename CMethod>
				nik_ce auto cequip() const -> CMethod
					{ return cfacade_type{this, base::template cbegin<base::apex()>()}; }

			// method:

				nik_ce auto cmethod() const { return cequip<cmethod_type>(); }
	};

/***********************************************************************************************************************/

// mutable:

	template<auto... Us, auto... Sizes, typename SizeType>
	class plot<T_pack_Vs<Us...>, T_pack_Vs<Sizes...>, SizeType> :
		public plot_model<T_pack_Vs<Us...>, T_pack_Vs<Sizes...>, SizeType>
	{
		public:

			using base			= plot_model<T_pack_Vs<Us...>, T_pack_Vs<Sizes...>, SizeType>;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using cfacade_type		= plot_cfacade<plot, base::order()>;
			using cmethod_type		= array_cmethod<cfacade_type>;

			using facade_type		= plot_facade<plot, base::order()>;
			using method_type		= array_method<facade_type>;

		public:

			nik_ce plot() : base{} { }
			nik_ce plot(const array<T_store_U<Us>, SizeType, Sizes> &... as) : base{as...} { }

			// equip:

				template<typename CMethod>
				nik_ce auto cequip() const -> CMethod
					{ return cfacade_type{this, base::template cbegin<base::apex()>()}; }

				template<typename Method>
				nik_ce auto equip() -> Method
					{ return facade_type{this, base::template begin<base::apex()>()}; }

			// method:

				nik_ce auto cmethod () const { return cequip< cmethod_type >(); }
				nik_ce auto  method ()       { return  equip<  method_type >(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// plottable (method):

/***********************************************************************************************************************/

// immutable:

/*
	template<typename Plot, typename SizeType, SizeType RowSize, SizeType ColSize>
	class plottable_cmethod : public Plot
	{
		public:

			using base			= Plot;

			using text_array_type		= typename base::text_array_type;
			using text_array_type_ptr	= typename base::text_array_type_ptr;
			using text_array_type_cptr	= typename base::text_array_type_cptr;
			using text_array_type_ref	= typename base::text_array_type_ref;

			using text_array_ctype		= typename base::text_array_ctype;
			using text_array_ctype_ptr	= typename base::text_array_ctype_ptr;
			using text_array_ctype_cptr	= typename base::text_array_ctype_cptr;
			using text_array_ctype_ref	= typename base::text_array_ctype_ref;

			using text_type			= typename base::text_type;
			using text_type_ptr		= typename base::text_type_ptr;
			using text_type_cptr		= typename base::text_type_cptr;
			using text_type_ref		= typename base::text_type_ref;

			using text_ctype		= typename base::text_ctype;
			using text_ctype_ptr		= typename base::text_ctype_ptr;
			using text_ctype_cptr		= typename base::text_ctype_cptr;
			using text_ctype_ref		= typename base::text_ctype_ref;

			using page_array_type		= typename base::page_array_type;
			using page_array_type_ptr	= typename base::page_array_type_ptr;
			using page_array_type_cptr	= typename base::page_array_type_cptr;
			using page_array_type_ref	= typename base::page_array_type_ref;

			using page_array_ctype		= typename base::page_array_ctype;
			using page_array_ctype_ptr	= typename base::page_array_ctype_ptr;
			using page_array_ctype_cptr	= typename base::page_array_ctype_cptr;
			using page_array_ctype_ref	= typename base::page_array_ctype_ref;

			using page_type			= typename base::page_type;
			using page_type_ptr		= typename base::page_type_ptr;
			using page_type_cptr		= typename base::page_type_cptr;
			using page_type_ref		= typename base::page_type_ref;

			using page_ctype		= typename base::page_ctype;
			using page_ctype_ptr		= typename base::page_ctype_ptr;
			using page_ctype_cptr		= typename base::page_ctype_cptr;
			using page_ctype_ref		= typename base::page_ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ces size_type row_length () { return RowSize; }
			nik_ces size_type col_length () { return ColSize; }

		protected:

			nik_ce size_type row_start(size_ctype n) const { return n * ColSize; }
			nik_ce size_type col_start(size_ctype n, size_ctype m) const { return row_start(n) + m; }

		public:

			nik_ce plottable_cmethod() : base{} { }

			template<typename T, auto N, typename P, auto M>
			nik_ce plottable_cmethod(const T (&t)[N], const P (&p)[M]) : base{t, p} { }

			nik_ce page_ctype_ptr row_cbegin(size_ctype n) const
				{ return base::cpage().citer(row_start(n)); }

			nik_ce page_ctype_ptr row_cend  (size_ctype n) const { return row_cbegin(n + 1); }
			nik_ce page_ctype_ptr row_clast (size_ctype n) const { return row_cend(n) - 1; }

			nik_ce page_ctype_ptr operator [] (size_ctype n) const { return row_cbegin(n); }
	};
*/

/***********************************************************************************************************************/

// mutable:

/*
	template<typename Plot, typename SizeType, SizeType RowSize, SizeType ColSize>
	class plottable_method	: public plottable_cmethod<Plot, SizeType, RowSize, ColSize>
	{
		public:

			using base			= plottable_cmethod<Plot, SizeType, RowSize, ColSize>;

			using text_array_type		= typename base::text_array_type;
			using text_array_type_ptr	= typename base::text_array_type_ptr;
			using text_array_type_cptr	= typename base::text_array_type_cptr;
			using text_array_type_ref	= typename base::text_array_type_ref;

			using text_array_ctype		= typename base::text_array_ctype;
			using text_array_ctype_ptr	= typename base::text_array_ctype_ptr;
			using text_array_ctype_cptr	= typename base::text_array_ctype_cptr;
			using text_array_ctype_ref	= typename base::text_array_ctype_ref;

			using text_type			= typename base::text_type;
			using text_type_ptr		= typename base::text_type_ptr;
			using text_type_cptr		= typename base::text_type_cptr;
			using text_type_ref		= typename base::text_type_ref;

			using text_ctype		= typename base::text_ctype;
			using text_ctype_ptr		= typename base::text_ctype_ptr;
			using text_ctype_cptr		= typename base::text_ctype_cptr;
			using text_ctype_ref		= typename base::text_ctype_ref;

			using page_array_type		= typename base::page_array_type;
			using page_array_type_ptr	= typename base::page_array_type_ptr;
			using page_array_type_cptr	= typename base::page_array_type_cptr;
			using page_array_type_ref	= typename base::page_array_type_ref;

			using page_array_ctype		= typename base::page_array_ctype;
			using page_array_ctype_ptr	= typename base::page_array_ctype_ptr;
			using page_array_ctype_cptr	= typename base::page_array_ctype_cptr;
			using page_array_ctype_ref	= typename base::page_array_ctype_ref;

			using page_type			= typename base::page_type;
			using page_type_ptr		= typename base::page_type_ptr;
			using page_type_cptr		= typename base::page_type_cptr;
			using page_type_ref		= typename base::page_type_ref;

			using page_ctype		= typename base::page_ctype;
			using page_ctype_ptr		= typename base::page_ctype_ptr;
			using page_ctype_cptr		= typename base::page_ctype_cptr;
			using page_ctype_ref		= typename base::page_ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce plottable_method() : base{} { }

			template<typename T, auto N, typename P, auto M>
			nik_ce plottable_method(const T (&t)[N], const P (&p)[M]) : base{t, p} { }

			using base::base::page;
			using base::base::text;

			using base::operator [];

		//	nik_ce page_type_ptr row_begin (size_ctype n) { return page().iter(base::row_start(n)); }
		//	nik_ce page_type_ptr row_end   (size_ctype n) { return row_begin(n + 1); }
		//	nik_ce page_type_ptr row_last  (size_ctype n) { return row_end(n) - 1; }

		//	nik_ce page_type_ptr operator [] (size_ctype n) { return row_begin(n); }

		//	template<typename F, typename In, typename End>
		//	nik_ce void setmap(size_ctype n, size_ctype m, F f, In in, End end)
		//		{ base::base::setmap(base::col_start(n, m), f, in, end); }
	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// plottable:

/***********************************************************************************************************************/

// immutable:

/*
	template<typename Page, typename Text, typename SizeType, SizeType RowSize, SizeType ColSize>
	class cplottable : public plottable_cmethod<cplot<Page, Text, SizeType>, SizeType, RowSize, ColSize>
	{
		public:

			using plot_type			= cplot<Page, Text, SizeType>;
			using base			= plottable_cmethod<plot_type, SizeType, RowSize, ColSize>;

			using text_array_type		= typename base::text_array_type;
			using text_array_type_ptr	= typename base::text_array_type_ptr;
			using text_array_type_cptr	= typename base::text_array_type_cptr;
			using text_array_type_ref	= typename base::text_array_type_ref;

			using text_array_ctype		= typename base::text_array_ctype;
			using text_array_ctype_ptr	= typename base::text_array_ctype_ptr;
			using text_array_ctype_cptr	= typename base::text_array_ctype_cptr;
			using text_array_ctype_ref	= typename base::text_array_ctype_ref;

			using text_type			= typename base::text_type;
			using text_type_ptr		= typename base::text_type_ptr;
			using text_type_cptr		= typename base::text_type_cptr;
			using text_type_ref		= typename base::text_type_ref;

			using text_ctype		= typename base::text_ctype;
			using text_ctype_ptr		= typename base::text_ctype_ptr;
			using text_ctype_cptr		= typename base::text_ctype_cptr;
			using text_ctype_ref		= typename base::text_ctype_ref;

			using page_array_type		= typename base::page_array_type;
			using page_array_type_ptr	= typename base::page_array_type_ptr;
			using page_array_type_cptr	= typename base::page_array_type_cptr;
			using page_array_type_ref	= typename base::page_array_type_ref;

			using page_array_ctype		= typename base::page_array_ctype;
			using page_array_ctype_ptr	= typename base::page_array_ctype_ptr;
			using page_array_ctype_cptr	= typename base::page_array_ctype_cptr;
			using page_array_ctype_ref	= typename base::page_array_ctype_ref;

			using page_type			= typename base::page_type;
			using page_type_ptr		= typename base::page_type_ptr;
			using page_type_cptr		= typename base::page_type_cptr;
			using page_type_ref		= typename base::page_type_ref;

			using page_ctype		= typename base::page_ctype;
			using page_ctype_ptr		= typename base::page_ctype_ptr;
			using page_ctype_cptr		= typename base::page_ctype_cptr;
			using page_ctype_ref		= typename base::page_ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce cplottable() : base{} { }

			template<typename T, auto N, typename P, auto M>
			nik_ce cplottable(const T (&t)[N], const P (&p)[M]) : base{t, p} { }
	};
*/

/***********************************************************************************************************************/

// mutable:

/*
	template
	<
		typename Text, typename Page, typename SizeType,
		SizeType TextSize, SizeType RowSize, SizeType ColSize
	>
	class plottable	: public plottable_method
			<
				plot<Page, Text, SizeType, TextSize, RowSize * ColSize>,
				SizeType, RowSize, ColSize
			>
	{
		public:

			using plot_type			= plot<Text, Page, SizeType, TextSize, RowSize * ColSize>;
			using base			= plottable_method<plot_type, SizeType, RowSize, ColSize>;

			using text_array_type		= typename base::text_array_type;
			using text_array_type_ptr	= typename base::text_array_type_ptr;
			using text_array_type_cptr	= typename base::text_array_type_cptr;
			using text_array_type_ref	= typename base::text_array_type_ref;

			using text_array_ctype		= typename base::text_array_ctype;
			using text_array_ctype_ptr	= typename base::text_array_ctype_ptr;
			using text_array_ctype_cptr	= typename base::text_array_ctype_cptr;
			using text_array_ctype_ref	= typename base::text_array_ctype_ref;

			using text_type			= typename base::text_type;
			using text_type_ptr		= typename base::text_type_ptr;
			using text_type_cptr		= typename base::text_type_cptr;
			using text_type_ref		= typename base::text_type_ref;

			using text_ctype		= typename base::text_ctype;
			using text_ctype_ptr		= typename base::text_ctype_ptr;
			using text_ctype_cptr		= typename base::text_ctype_cptr;
			using text_ctype_ref		= typename base::text_ctype_ref;

			using page_array_type		= typename base::page_array_type;
			using page_array_type_ptr	= typename base::page_array_type_ptr;
			using page_array_type_cptr	= typename base::page_array_type_cptr;
			using page_array_type_ref	= typename base::page_array_type_ref;

			using page_array_ctype		= typename base::page_array_ctype;
			using page_array_ctype_ptr	= typename base::page_array_ctype_ptr;
			using page_array_ctype_cptr	= typename base::page_array_ctype_cptr;
			using page_array_ctype_ref	= typename base::page_array_ctype_ref;

			using page_type			= typename base::page_type;
			using page_type_ptr		= typename base::page_type_ptr;
			using page_type_cptr		= typename base::page_type_cptr;
			using page_type_ref		= typename base::page_type_ref;

			using page_ctype		= typename base::page_ctype;
			using page_ctype_ptr		= typename base::page_ctype_ptr;
			using page_ctype_cptr		= typename base::page_ctype_cptr;
			using page_ctype_ref		= typename base::page_ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce plottable() : base{} { }

			template<typename T, auto N, typename P, auto M>
			nik_ce plottable(const T (&t)[N], const P (&p)[M]) : base{t, p} { }
	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::engine

