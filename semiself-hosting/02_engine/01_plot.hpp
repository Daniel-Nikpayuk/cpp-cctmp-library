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

/***********************************************************************************************************************/

// entry:

	template<typename SizeType>
	class plot_entry
	{
		public:

			using size_type		= typename alias<SizeType>::type;
			using size_ctype	= typename alias<SizeType>::ctype;

		protected:

			size_type initial;
			size_type terminal;

		public:

			nik_ce plot_entry() : initial{}, terminal{} { }

			nik_ce size_type start  () const { return initial; }
			nik_ce size_type finish () const { return terminal; }

			nik_ce void set_start  (size_ctype i) { initial = i; }
			nik_ce void set_finish (size_ctype t) { terminal = t; }
	};

/***********************************************************************************************************************/

// proto:

		// text: circumstantial semantics separate from page.

	template<typename PageArray, typename TextArray>
	class protoplot
	{
		public:

			using page_array_type		= typename alias<PageArray>::type;
			using page_array_type_ptr	= typename alias<PageArray>::type_ptr;
			using page_array_type_cptr	= typename alias<PageArray>::type_cptr;
			using page_array_type_ref	= typename alias<PageArray>::type_ref;

			using page_array_ctype		= typename alias<PageArray>::ctype;
			using page_array_ctype_ptr	= typename alias<PageArray>::ctype_ptr;
			using page_array_ctype_cptr	= typename alias<PageArray>::ctype_cptr;
			using page_array_ctype_ref	= typename alias<PageArray>::ctype_ref;

			using page_type			= typename page_array_type::type;
			using page_type_ptr		= typename page_array_type::type_ptr;
			using page_type_cptr		= typename page_array_type::type_cptr;
			using page_type_ref		= typename page_array_type::type_ref;

			using page_ctype		= typename page_array_type::ctype;
			using page_ctype_ptr		= typename page_array_type::ctype_ptr;
			using page_ctype_cptr		= typename page_array_type::ctype_cptr;
			using page_ctype_ref		= typename page_array_type::ctype_ref;

			using text_array_type		= typename alias<TextArray>::type;
			using text_array_type_ptr	= typename alias<TextArray>::type_ptr;
			using text_array_type_cptr	= typename alias<TextArray>::type_cptr;
			using text_array_type_ref	= typename alias<TextArray>::type_ref;

			using text_array_ctype		= typename alias<TextArray>::ctype;
			using text_array_ctype_ptr	= typename alias<TextArray>::ctype_ptr;
			using text_array_ctype_cptr	= typename alias<TextArray>::ctype_cptr;
			using text_array_ctype_ref	= typename alias<TextArray>::ctype_ref;

			using text_type			= typename text_array_type::type;
			using text_type_ptr		= typename text_array_type::type_ptr;
			using text_type_cptr		= typename text_array_type::type_cptr;
			using text_type_ref		= typename text_array_type::type_ref;

			using text_ctype		= typename text_array_type::ctype;
			using text_ctype_ptr		= typename text_array_type::ctype_ptr;
			using text_ctype_cptr		= typename text_array_type::ctype_cptr;
			using text_ctype_ref		= typename text_array_type::ctype_ref;

			using size_type			= typename text_array_type::size_type;
			using size_ctype		= typename text_array_type::size_ctype;

		protected:

			page_array_type page;
			text_array_type text;

		public:

			nik_ce protoplot() { }

			template<typename P, auto N, typename T, auto M>
			nik_ce protoplot(const P (&p)[N], const T (&t)[M]) : page{p}, text{t} { }

			nik_ce page_array_ctype_ref cpage() const { return page; }
			nik_ce text_array_ctype_ref ctext() const { return text; }

			nik_ce size_type start  (size_ctype n) const { return page[n].start(); }
			nik_ce size_type finish (size_ctype n) const { return page[n].finish(); }

			// initial:

				nik_ce text_ctype_ptr cbegin(size_ctype n) const { return text.citer(start(n)); }

				nik_ce size_type left_size(size_ctype n, text_ctype_cptr i) const
					{ return i - cbegin(n); }

				nik_ce text_ctype_ptr citer (size_ctype n, size_ctype m) const { return cbegin(n) + m; }
				nik_ce text_ctype_ref cat   (size_ctype n, size_ctype m) const { return cbegin(n)[m]; }

				template<typename In, typename End>
				nik_ce bool equal(size_ctype n, In in, End end) const
					{ return text.equal(start(n), in, end); }

				template<typename In, typename End>
				nik_ce bool not_equal(size_ctype n, In in, End end) const
					{ return text.not_equal(start(n), in, end); }

			// terminal:

				nik_ce size_type size (size_ctype n) const { return finish(n) - start(n); }
				nik_ce size_type max  (size_ctype n) const { return size(n) - 1; }

				nik_ce text_ctype_ptr cend  (size_ctype n) const { return text.citer(finish(n)); }
				nik_ce text_ctype_ptr clast (size_ctype n) const { return cend(n) - 1; }

				nik_ce size_type right_size(size_ctype n, text_ctype_cptr i) const
					{ return cend(n) - i; }

				nik_ce bool is_empty  (size_ctype n) const { return (size(n) == 0); }
				nik_ce bool not_empty (size_ctype n) const { return (size(n) != 0); }
	};

/***********************************************************************************************************************/

// literal:

	template<typename Page, typename Text, typename SizeType>
	class plot_literal	: public protoplot
				<
					array_literal < Page , SizeType >,
					array_literal < Text , SizeType >
				>
	{
		public:

			using page_array_type		= array_literal < Page , SizeType >;
			using text_array_type		= array_literal < Text , SizeType >;
			using base			= protoplot<page_array_type, text_array_type>;

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

			nik_ce plot_literal() : base{} { }

			template<typename P, auto N, typename T, auto M>
			nik_ce plot_literal(const P (&p)[N], const T (&t)[M]) : base{p, t} { }
	};

/***********************************************************************************************************************/

// interface:

	template<typename Page, typename Text, typename SizeType, SizeType PageSize, SizeType TextSize = PageSize>
	class plot	: public protoplot // PageSize <= TextSize
			<
				array < Page , SizeType , PageSize >,
				array < Text , SizeType , TextSize >
			>
	{
		public:

			using page_array_type		= array < Page , SizeType , PageSize >;
			using text_array_type		= array < Text , SizeType , TextSize >;
			using base			= protoplot<page_array_type, text_array_type>;

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

			nik_ce void push_finish(size_ctype start)
			{
				size_ctype finish = base::ctext().size();

				page().upsize();
				page().last()->set_start  (start);
				page().last()->set_finish (finish);
			}

			nik_ce void set_finish(size_ctype n, size_ctype start)
			{
				size_ctype finish = base::ctext().size();

				page().at(n).set_start  (start);
				page().at(n).set_finish (finish);
			}

		public:

			nik_ce plot() : base{} { }

			template<typename P, auto N, typename T, auto M>
			nik_ce plot(const P (&p)[N], const T (&t)[M]) : base{p, t} { }

			nik_ce page_array_type_ref page() { return base::page; }
			nik_ce text_array_type_ref text() { return base::text; }

			// mutable:

				nik_ce text_type_ptr begin(size_ctype n) { return text().iter(base::start(n)); }

				nik_ce text_type_ptr iter (size_ctype n, size_ctype m) { return begin(n) + m; }
				nik_ce text_type_ref at   (size_ctype n, size_ctype m) { return begin(n)[m]; }

				nik_ce text_type_ptr end  (size_ctype n) { return text().iter(base::finish(n)); }
				nik_ce text_type_ptr last (size_ctype n) { return end(n) - 1; }

				template<typename In, typename End>
				nik_ce void push(In in, End end)
				{
					size_ctype start = base::ctext().size();

					text().push(in, end);
					push_finish(start);
				}

				template<typename F, typename In, typename End>
				nik_ce void pushmap(F f, In in, End end)
				{
					size_ctype start = base::ctext().size();

					text().pushmap(f, in, end);
					push_finish(start);
				}

				template<typename F, typename In, typename End>
				nik_ce void setmap(size_ctype n, F f, In in, End end)
				{
					size_ctype start = base::ctext().size();

					text().pushmap(f, in, end);
					set_finish(n, start);
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// plottable:

/***********************************************************************************************************************/

// proto:

	template<typename Plot, typename SizeType, SizeType RowSize, SizeType ColSize>
	class protoplottable : public Plot
	{
		public:

			using base			= Plot;

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

		public:

			nik_ce protoplottable() : base{} { }

			template<typename P, auto N, typename T, auto M>
			nik_ce protoplottable(const P (&p)[N], const T (&t)[M]) : base{p, t} { }

			using base::cpage;
			using base::ctext;

			nik_ce size_type row_length () const { return RowSize; }
			nik_ce size_type col_length () const { return ColSize; }

			nik_ce page_ctype_ptr row_cbegin (size_ctype n) const { return cpage().citer(row_start(n)); }
			nik_ce page_ctype_ptr row_cend   (size_ctype n) const { return row_cbegin(n + 1); }
			nik_ce page_ctype_ptr row_clast  (size_ctype n) const { return row_cend(n) - 1; }

			nik_ce page_ctype_ptr operator [] (size_ctype n) const { return row_cbegin(n); }
	};

/***********************************************************************************************************************/

// literal:

	template<typename Page, typename Text, typename SizeType, SizeType RowSize, SizeType ColSize>
	class plottable_literal	: public protoplottable
				<
					plot_literal<Page, Text, SizeType>, SizeType, RowSize, ColSize
				>
	{
		public:

			using plot_type			= plot_literal<Page, Text, SizeType>;
			using base			= protoplottable<plot_type, SizeType, RowSize, ColSize>;

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

			nik_ce plottable_literal() : base{} { }

			template<typename P, auto N, typename T, auto M>
			nik_ce plottable_literal(const P (&p)[N], const T (&t)[M]) : base{p, t} { }

			nik_ce bool operator == (const plottable_literal & l) const
				{ return base::equal(0, l.cbegin(), l.cend()); }

			nik_ce bool operator != (const plottable_literal & l) const
				{ return base::not_equal(0, l.cbegin(), l.cend()); }
	};

/***********************************************************************************************************************/

// interface:

	template<typename Page, typename Text, typename SizeType, SizeType RowSize, SizeType ColSize>
	class plottable	: public protoplottable
			<
				plot<Page, Text, SizeType, RowSize * ColSize>, SizeType, RowSize, ColSize
			>
	{
		public:

			using plot_type			= plot<Page, Text, SizeType, RowSize * ColSize>;
			using base			= protoplottable<plot_type, SizeType, RowSize, ColSize>;

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

			nik_ce plottable() : base{} { }

			template<typename P, auto N, typename T, auto M>
			nik_ce plottable(const P (&p)[N], const T (&t)[M]) : base{p, t} { }

			using base::base::page;
			using base::base::text;

			using base::operator [];

			nik_ce page_type_ptr row_begin(size_ctype n)
				{ return page().iter(base::row_start(n)); }

			nik_ce page_type_ptr row_end  (size_ctype n) { return row_begin(n + 1); }
			nik_ce page_type_ptr row_last (size_ctype n) { return row_end(n) - 1; }

			nik_ce page_type_ptr operator [] (size_ctype n) { return row_begin(n); }

			template<typename F, typename In, typename End>
			nik_ce void setmap(size_ctype n, size_ctype m, F f, In in, End end)
				{ base::base::setmap(base::col_start(n, m), f, in, end); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::engine

