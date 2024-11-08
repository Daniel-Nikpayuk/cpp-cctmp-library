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

// sparse plot:

namespace cctmp  {
namespace engine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sparse plot:

/***********************************************************************************************************************/

// proto:

	template<typename IconArray, typename Arc>
	class protosparse_plot
	{
		public:

			using icon_array_type		= typename alias<IconArray>::type;
			using icon_array_type_ptr	= typename alias<IconArray>::type_ptr;
			using icon_array_type_cptr	= typename alias<IconArray>::type_cptr;
			using icon_array_type_ref	= typename alias<IconArray>::type_ref;

			using icon_array_ctype		= typename alias<IconArray>::ctype;
			using icon_array_ctype_ptr	= typename alias<IconArray>::ctype_ptr;
			using icon_array_ctype_cptr	= typename alias<IconArray>::ctype_cptr;
			using icon_array_ctype_ref	= typename alias<IconArray>::ctype_ref;

			using icon_type			= typename icon_array_type::type;
			using icon_type_ptr		= typename icon_array_type::type_ptr;
			using icon_type_cptr		= typename icon_array_type::type_cptr;
			using icon_type_ref		= typename icon_array_type::type_ref;

			using icon_ctype		= typename icon_array_type::ctype;
			using icon_ctype_ptr		= typename icon_array_type::ctype_ptr;
			using icon_ctype_cptr		= typename icon_array_type::ctype_cptr;
			using icon_ctype_ref		= typename icon_array_type::ctype_ref;

			using arc_type			= typename alias<Arc>::type;
			using arc_type_ptr		= typename alias<Arc>::type_ptr;
			using arc_type_cptr		= typename alias<Arc>::type_cptr;
			using arc_type_ref		= typename alias<Arc>::type_ref;

			using arc_ctype			= typename alias<Arc>::ctype;
			using arc_ctype_ptr		= typename alias<Arc>::ctype_ptr;
			using arc_ctype_cptr		= typename alias<Arc>::ctype_cptr;
			using arc_ctype_ref		= typename alias<Arc>::ctype_ref;

			using page_array_type		= typename arc_type::page_array_type;
			using page_array_type_ptr	= typename arc_type::page_array_type_ptr;
			using page_array_type_cptr	= typename arc_type::page_array_type_cptr;
			using page_array_type_ref	= typename arc_type::page_array_type_ref;

			using page_array_ctype		= typename arc_type::page_array_ctype;
			using page_array_ctype_ptr	= typename arc_type::page_array_ctype_ptr;
			using page_array_ctype_cptr	= typename arc_type::page_array_ctype_cptr;
			using page_array_ctype_ref	= typename arc_type::page_array_ctype_ref;

			using page_type			= typename arc_type::page_type;
			using page_type_ptr		= typename arc_type::page_type_ptr;
			using page_type_cptr		= typename arc_type::page_type_cptr;
			using page_type_ref		= typename arc_type::page_type_ref;

			using page_ctype		= typename arc_type::page_ctype;
			using page_ctype_ptr		= typename arc_type::page_ctype_ptr;
			using page_ctype_cptr		= typename arc_type::page_ctype_cptr;
			using page_ctype_ref		= typename arc_type::page_ctype_ref;

			using text_array_type		= typename arc_type::text_array_type;
			using text_array_type_ptr	= typename arc_type::text_array_type_ptr;
			using text_array_type_cptr	= typename arc_type::text_array_type_cptr;
			using text_array_type_ref	= typename arc_type::text_array_type_ref;

			using text_array_ctype		= typename arc_type::text_array_ctype;
			using text_array_ctype_ptr	= typename arc_type::text_array_ctype_ptr;
			using text_array_ctype_cptr	= typename arc_type::text_array_ctype_cptr;
			using text_array_ctype_ref	= typename arc_type::text_array_ctype_ref;

			using text_type			= typename arc_type::text_type;
			using text_type_ptr		= typename arc_type::text_type_ptr;
			using text_type_cptr		= typename arc_type::text_type_cptr;
			using text_type_ref		= typename arc_type::text_type_ref;

			using text_ctype		= typename arc_type::text_ctype;
			using text_ctype_ptr		= typename arc_type::text_ctype_ptr;
			using text_ctype_cptr		= typename arc_type::text_ctype_cptr;
			using text_ctype_ref		= typename arc_type::text_ctype_ref;

			using size_type			= typename arc_type::size_type;
			using size_ctype		= typename arc_type::size_ctype;

		protected:

			icon_array_type icon;
			arc_type arc;

		public:

			nik_ce protosparse_plot() { }

			template<typename I, auto N, typename P, auto M, typename T, auto L>
			nik_ce protosparse_plot(const I (&i)[N], const P (&p)[M], const T (&t)[L]) :
				icon{i}, arc{p, t}
					{ }

			nik_ce icon_array_ctype_ref cicon () const { return icon; }
			nik_ce        arc_ctype_ref carc  () const { return arc; }

			nik_ce page_array_ctype_ref cpage () const { return arc.cpage(); }
			nik_ce text_array_ctype_ref ctext () const { return arc.ctext(); }

			nik_ce bool is_none  (size_ctype n) const { return (icon[n] == 0); }
			nik_ce bool not_none (size_ctype n) const { return (icon[n] != 0); }

			// initial:

				nik_ce text_ctype_ptr cbegin(size_ctype n) const { return arc.cbegin(icon[n]); }

				nik_ce size_type left_size(size_ctype n, text_ctype_cptr i) const
					{ return i - cbegin(n); }

				nik_ce text_ctype_ptr citer (size_ctype n, size_ctype m) const { return cbegin(n) + m; }
				nik_ce text_ctype_ref cat   (size_ctype n, size_ctype m) const { return cbegin(n)[m]; }

				template<typename In, typename End>
				nik_ce bool equal(size_ctype n, In in, End end) const
					{ return arc.equal(icon[n], in, end); }

				template<typename In, typename End>
				nik_ce bool not_equal(size_ctype n, In in, End end) const
					{ return arc.not_equal(icon[n], in, end); }

			// terminal:

				nik_ce size_type size (size_ctype n) const { return arc.size(icon[n]); }
				nik_ce size_type max  (size_ctype n) const { return size(n) - 1; }

				nik_ce text_ctype_ptr cend  (size_ctype n) const { return arc.cend(icon[n]); }
				nik_ce text_ctype_ptr clast (size_ctype n) const { return cend(n) - 1; }

				nik_ce size_type right_size(size_ctype n, text_ctype_cptr i) const
					{ return cend(n) - i; }

				nik_ce bool is_empty  (size_ctype n) const { return (size(n) == 0); }
				nik_ce bool not_empty (size_ctype n) const { return (size(n) != 0); }
	};

/***********************************************************************************************************************/

// literal:

	template<typename Page, typename Text, typename SizeType>
	class sparse_plot_literal	: public protosparse_plot
					<
						array_literal < SizeType        , SizeType >,
						 plot_literal < Page     , Text , SizeType >
					>
	{
		public:

			using icon_array_type		= array_literal < SizeType        , SizeType >;
			using plot_type			=  plot_literal < Page     , Text , SizeType >;
			using base			= protosparse_plot<icon_array_type, plot_type>;

			using icon_array_type_ptr	= typename base::icon_array_type_ptr;
			using icon_array_type_cptr	= typename base::icon_array_type_cptr;
			using icon_array_type_ref	= typename base::icon_array_type_ref;

			using icon_array_ctype		= typename base::icon_array_ctype;
			using icon_array_ctype_ptr	= typename base::icon_array_ctype_ptr;
			using icon_array_ctype_cptr	= typename base::icon_array_ctype_cptr;
			using icon_array_ctype_ref	= typename base::icon_array_ctype_ref;

			using icon_type			= typename base::icon_type;
			using icon_type_ptr		= typename base::icon_type_ptr;
			using icon_type_cptr		= typename base::icon_type_cptr;
			using icon_type_ref		= typename base::icon_type_ref;

			using icon_ctype		= typename base::icon_ctype;
			using icon_ctype_ptr		= typename base::icon_ctype_ptr;
			using icon_ctype_cptr		= typename base::icon_ctype_cptr;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using arc_type			= typename base::arc_type;
			using arc_type_ptr		= typename base::arc_type_ptr;
			using arc_type_cptr		= typename base::arc_type_cptr;
			using arc_type_ref		= typename base::arc_type_ref;

			using arc_ctype			= typename base::arc_ctype;
			using arc_ctype_ptr		= typename base::arc_ctype_ptr;
			using arc_ctype_cptr		= typename base::arc_ctype_cptr;
			using arc_ctype_ref		= typename base::arc_ctype_ref;

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

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce sparse_plot_literal() : base{} { }

			template<typename I, auto N, typename P, auto M, typename T, auto L>
			nik_ce sparse_plot_literal(const I (&i)[N], const P (&p)[M], const T (&t)[L]) :
				base{i, p, t} { }
	};

/***********************************************************************************************************************/

// interface:

	template
	<
		typename Page, typename Text, typename SizeType,
		SizeType IconSize, SizeType PageSize, SizeType TextSize = PageSize
	>
	class sparse_plot	: public protosparse_plot // PageSize <= TextSize
				<
					array < SizeType        , SizeType            , IconSize >,
					 plot < Page     , Text , SizeType , PageSize , TextSize >
				>
	{
		public:

			using icon_array_type		= array < SizeType        , SizeType            , IconSize >;
			using plot_type			=  plot < Page     , Text , SizeType , PageSize , TextSize >;
			using base			= protosparse_plot<icon_array_type, plot_type>;

			using icon_array_type_ptr	= typename base::icon_array_type_ptr;
			using icon_array_type_cptr	= typename base::icon_array_type_cptr;
			using icon_array_type_ref	= typename base::icon_array_type_ref;

			using icon_array_ctype		= typename base::icon_array_ctype;
			using icon_array_ctype_ptr	= typename base::icon_array_ctype_ptr;
			using icon_array_ctype_cptr	= typename base::icon_array_ctype_cptr;
			using icon_array_ctype_ref	= typename base::icon_array_ctype_ref;

			using icon_type			= typename base::icon_type;
			using icon_type_ptr		= typename base::icon_type_ptr;
			using icon_type_cptr		= typename base::icon_type_cptr;
			using icon_type_ref		= typename base::icon_type_ref;

			using icon_ctype		= typename base::icon_ctype;
			using icon_ctype_ptr		= typename base::icon_ctype_ptr;
			using icon_ctype_cptr		= typename base::icon_ctype_cptr;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using arc_type			= typename base::arc_type;
			using arc_type_ptr		= typename base::arc_type_ptr;
			using arc_type_cptr		= typename base::arc_type_cptr;
			using arc_type_ref		= typename base::arc_type_ref;

			using arc_ctype			= typename base::arc_ctype;
			using arc_ctype_ptr		= typename base::arc_ctype_ptr;
			using arc_ctype_cptr		= typename base::arc_ctype_cptr;
			using arc_ctype_ref		= typename base::arc_ctype_ref;

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

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce sparse_plot() : base{}
				{ arc().push(base::ctext().origin(), base::ctext().origin()); }

			template<typename I, auto N, typename P, auto M, typename T, auto L>
			nik_ce sparse_plot(const I (&i)[N], const P (&p)[M], const T (&t)[L]) : base{i, p, t} { }

			nik_ce icon_array_type_ref icon () { return base::icon; }
			nik_ce        arc_type_ref arc  () { return base::arc; }

			nik_ce page_array_type_ref page () { return arc().page(); }
			nik_ce text_array_type_ref text () { return arc().text(); }

			// mutable:

				nik_ce text_type_ptr begin(size_ctype n) { return arc().begin(base::cicon().cat(n)); }

				nik_ce text_type_ptr iter (size_ctype n, size_ctype m) { return begin(n) + m; }
				nik_ce text_type_ref at   (size_ctype n, size_ctype m) { return begin(n)[m]; }

				nik_ce text_type_ptr end  (size_ctype n) { return arc().end(base::cicon().cat(n)); }
				nik_ce text_type_ptr last (size_ctype n) { return end(n) - 1; }

				template<typename In, typename End>
				nik_ce void push(size_ctype n, In in, End end)
				{
					arc().push(in, end);
					icon().at(n) = base::cpage().size();
				}

				template<typename F, typename In, typename End>
				nik_ce void pushmap(size_ctype n, F f, In in, End end)
				{
					arc().pushmap(f, in, end);
					icon().at(n) = base::cpage().size();
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sparse plottable:

/***********************************************************************************************************************/

// proto:

	template<typename SparsePlot, typename SizeType, SizeType RowSize, SizeType ColSize>
	class protosparse_plottable : public SparsePlot
	{
		public:

			using base			= SparsePlot;

			using icon_array_type		= typename base::icon_array_type;
			using icon_array_type_ptr	= typename base::icon_array_type_ptr;
			using icon_array_type_cptr	= typename base::icon_array_type_cptr;
			using icon_array_type_ref	= typename base::icon_array_type_ref;

			using icon_array_ctype		= typename base::icon_array_ctype;
			using icon_array_ctype_ptr	= typename base::icon_array_ctype_ptr;
			using icon_array_ctype_cptr	= typename base::icon_array_ctype_cptr;
			using icon_array_ctype_ref	= typename base::icon_array_ctype_ref;

			using icon_type			= typename base::icon_type;
			using icon_type_ptr		= typename base::icon_type_ptr;
			using icon_type_cptr		= typename base::icon_type_cptr;
			using icon_type_ref		= typename base::icon_type_ref;

			using icon_ctype		= typename base::icon_ctype;
			using icon_ctype_ptr		= typename base::icon_ctype_ptr;
			using icon_ctype_cptr		= typename base::icon_ctype_cptr;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using arc_type			= typename base::arc_type;
			using arc_type_ptr		= typename base::arc_type_ptr;
			using arc_type_cptr		= typename base::arc_type_cptr;
			using arc_type_ref		= typename base::arc_type_ref;

			using arc_ctype			= typename base::arc_ctype;
			using arc_ctype_ptr		= typename base::arc_ctype_ptr;
			using arc_ctype_cptr		= typename base::arc_ctype_cptr;
			using arc_ctype_ref		= typename base::arc_ctype_ref;

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

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		protected:

			nik_ce size_type row_start(size_ctype n) const { return n * ColSize; }
			nik_ce size_type col_start(size_ctype n, size_ctype m) const { return row_start(n) + m; }

			nik_ce size_type page_position(size_ctype n, size_ctype m) const
				{ return base::cicon().cat(col_start(n, m)); }

		public:

			nik_ce protosparse_plottable() : base{} { }

			template<typename I, auto N, typename P, auto M, typename T, auto L>
			nik_ce protosparse_plottable(const I (&i)[N], const P (&p)[M], const T (&t)[L]) :
				base{i, p, t} { }

			using base::cicon;
			using base::carc;

			using base::cpage;
			using base::ctext;

			nik_ce size_type row_length () const { return RowSize; }
			nik_ce size_type col_length () const { return ColSize; }

			nik_ce bool is_none(size_ctype n, size_ctype m) const
				{ return base::is_none(col_start(n, m)); }

			nik_ce bool not_none(size_ctype n, size_ctype m) const
				{ return base::not_none(col_start(n, m)); }

			nik_ce page_ctype_ref cat(size_ctype n, size_ctype m) const
				{ return cpage().cat(page_position(n, m)); }

			nik_ce page_ctype_ref cbegin(size_ctype n, size_ctype m) const
				{ return carc().cbegin(page_position(n, m)); }

			nik_ce page_ctype_ref cend(size_ctype n, size_ctype m) const
				{ return carc().cend(page_position(n, m)); }
	};

/***********************************************************************************************************************/

// literal:

	template<typename Page, typename Text, typename SizeType, SizeType RowSize, SizeType ColSize>
	class sparse_plottable_literal	: public protosparse_plottable
					<
						sparse_plot_literal<Page, Text, SizeType>, SizeType, RowSize, ColSize
					>
	{
		public:

			using plot_type			= sparse_plot_literal<Page, Text, SizeType>;
			using base			= protosparse_plottable<plot_type, SizeType, RowSize, ColSize>;

			using icon_array_type		= typename base::icon_array_type;
			using icon_array_type_ptr	= typename base::icon_array_type_ptr;
			using icon_array_type_cptr	= typename base::icon_array_type_cptr;
			using icon_array_type_ref	= typename base::icon_array_type_ref;

			using icon_array_ctype		= typename base::icon_array_ctype;
			using icon_array_ctype_ptr	= typename base::icon_array_ctype_ptr;
			using icon_array_ctype_cptr	= typename base::icon_array_ctype_cptr;
			using icon_array_ctype_ref	= typename base::icon_array_ctype_ref;

			using icon_type			= typename base::icon_type;
			using icon_type_ptr		= typename base::icon_type_ptr;
			using icon_type_cptr		= typename base::icon_type_cptr;
			using icon_type_ref		= typename base::icon_type_ref;

			using icon_ctype		= typename base::icon_ctype;
			using icon_ctype_ptr		= typename base::icon_ctype_ptr;
			using icon_ctype_cptr		= typename base::icon_ctype_cptr;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using arc_type			= typename base::arc_type;
			using arc_type_ptr		= typename base::arc_type_ptr;
			using arc_type_cptr		= typename base::arc_type_cptr;
			using arc_type_ref		= typename base::arc_type_ref;

			using arc_ctype			= typename base::arc_ctype;
			using arc_ctype_ptr		= typename base::arc_ctype_ptr;
			using arc_ctype_cptr		= typename base::arc_ctype_cptr;
			using arc_ctype_ref		= typename base::arc_ctype_ref;

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

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce sparse_plottable_literal() : base{} { }

			template<typename I, auto N, typename P, auto M, typename T, auto L>
			nik_ce sparse_plottable_literal(const I (&i)[N], const P (&p)[M], const T (&t)[L]) :
				base{i, p, t} { }
	};

/***********************************************************************************************************************/

// interface:

	template<typename Page, typename Text, typename SizeType, SizeType RowSize, SizeType ColSize>
	class sparse_plottable	: public protosparse_plottable
				<
					sparse_plot<Page, Text, SizeType, RowSize * ColSize, RowSize * ColSize>,
					SizeType, RowSize, ColSize
				>
	{
		public:

			using plot_type			= sparse_plot
							<
								Page, Text, SizeType,
								RowSize * ColSize, RowSize * ColSize
							>;
			using base			= protosparse_plottable<plot_type, SizeType, RowSize, ColSize>;

			using icon_array_type		= typename base::icon_array_type;
			using icon_array_type_ptr	= typename base::icon_array_type_ptr;
			using icon_array_type_cptr	= typename base::icon_array_type_cptr;
			using icon_array_type_ref	= typename base::icon_array_type_ref;

			using icon_array_ctype		= typename base::icon_array_ctype;
			using icon_array_ctype_ptr	= typename base::icon_array_ctype_ptr;
			using icon_array_ctype_cptr	= typename base::icon_array_ctype_cptr;
			using icon_array_ctype_ref	= typename base::icon_array_ctype_ref;

			using icon_type			= typename base::icon_type;
			using icon_type_ptr		= typename base::icon_type_ptr;
			using icon_type_cptr		= typename base::icon_type_cptr;
			using icon_type_ref		= typename base::icon_type_ref;

			using icon_ctype		= typename base::icon_ctype;
			using icon_ctype_ptr		= typename base::icon_ctype_ptr;
			using icon_ctype_cptr		= typename base::icon_ctype_cptr;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using arc_type			= typename base::arc_type;
			using arc_type_ptr		= typename base::arc_type_ptr;
			using arc_type_cptr		= typename base::arc_type_cptr;
			using arc_type_ref		= typename base::arc_type_ref;

			using arc_ctype			= typename base::arc_ctype;
			using arc_ctype_ptr		= typename base::arc_ctype_ptr;
			using arc_ctype_cptr		= typename base::arc_ctype_cptr;
			using arc_ctype_ref		= typename base::arc_ctype_ref;

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

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce sparse_plottable() : base{} { }

			template<typename I, auto N, typename P, auto M, typename T, auto L>
			nik_ce sparse_plottable(const I (&i)[N], const P (&p)[M], const T (&t)[L]) : base{i, p, t} { }

			nik_ce icon_array_type_ref icon () { return base::base::icon(); }
			nik_ce        arc_type_ref arc  () { return base::base::arc(); }

			nik_ce page_array_type_ref page () { return base::base::page(); }
			nik_ce text_array_type_ref text () { return base::base::text(); }

			nik_ce page_type_ref at(size_ctype n, size_ctype m)
				{ return page().at(base::page_position(n, m)); }

			template<typename F, typename In, typename End>
			nik_ce void setmap(size_ctype n, size_ctype m, F f, In in, End end)
				{ base::pushmap(base::col_start(n, m), f, in, end); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::engine

