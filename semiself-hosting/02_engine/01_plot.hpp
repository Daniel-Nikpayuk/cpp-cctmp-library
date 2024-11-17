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

// subarray:

/***********************************************************************************************************************/

// immutable:

	template<typename Initial, typename Terminal, typename SizeType>
	class plot_csubarray	: public array_cmethod
				<
					image_trait <  Initial const* ,  Initial const ,  Initial >,
					image_trait < Terminal const* , Terminal const , Terminal >,
					SizeType
				>
	{
		public:

			using init_trait		= image_trait <  Initial const* ,  Initial const ,  Initial >;
			using term_trait		= image_trait < Terminal const* , Terminal const , Terminal >;
			using base			= array_cmethod<init_trait, term_trait, SizeType>;

			using initial_type		= typename base::initial_type;
			using initial_type_ptr		= typename base::initial_type_ptr;
			using initial_type_cptr		= typename base::initial_type_cptr;
			using initial_type_ref		= typename base::initial_type_ref;

			using initial_ctype		= typename base::initial_ctype;
			using initial_ctype_ptr		= typename base::initial_ctype_ptr;
			using initial_ctype_cptr	= typename base::initial_ctype_cptr;
			using initial_ctype_ref		= typename base::initial_ctype_ref;

			using terminal_type		= typename base::terminal_type;
			using terminal_type_ptr		= typename base::terminal_type_ptr;
			using terminal_type_cptr	= typename base::terminal_type_cptr;
			using terminal_type_ref		= typename base::terminal_type_ref;

			using terminal_ctype		= typename base::terminal_ctype;
			using terminal_ctype_ptr	= typename base::terminal_ctype_ptr;
			using terminal_ctype_cptr	= typename base::terminal_ctype_cptr;
			using terminal_ctype_ref	= typename base::terminal_ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		protected:

			nik_ce void assign(initial_ctype_cptr i, terminal_ctype_cptr t)
			{
				base:: initial = i;
				base::terminal = t;
			}

		public:

			nik_ce plot_csubarray() :
				base{} { }

			nik_ce plot_csubarray(initial_ctype_cptr i, terminal_ctype_cptr t) :
				base{} { assign(i, t); }

			nik_ce  initial_ctype_ptr cinitial  () const { return base::initial; }
			nik_ce terminal_ctype_ptr cterminal () const { return base::terminal; }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Initial, typename Terminal, typename SizeType, SizeType Size>
	class plot_subarray	: public array_method
				<
					image_trait <  Initial* ,  Initial ,  Initial >,
					image_trait < Terminal* , Terminal , Terminal >,
					SizeType, Size
				>
	{
		public:

			using init_trait		= image_trait <  Initial* ,  Initial ,  Initial >;
			using term_trait		= image_trait < Terminal* , Terminal , Terminal >;
			using base			= array_method<init_trait, term_trait, SizeType, Size>;

			using initial_type		= typename base::initial_type;
			using initial_type_ptr		= typename base::initial_type_ptr;
			using initial_type_cptr		= typename base::initial_type_cptr;
			using initial_type_ref		= typename base::initial_type_ref;

			using initial_ctype		= typename base::initial_ctype;
			using initial_ctype_ptr		= typename base::initial_ctype_ptr;
			using initial_ctype_cptr	= typename base::initial_ctype_cptr;
			using initial_ctype_ref		= typename base::initial_ctype_ref;

			using terminal_type		= typename base::terminal_type;
			using terminal_type_ptr		= typename base::terminal_type_ptr;
			using terminal_type_cptr	= typename base::terminal_type_cptr;
			using terminal_type_ref		= typename base::terminal_type_ref;

			using terminal_ctype		= typename base::terminal_ctype;
			using terminal_ctype_ptr	= typename base::terminal_ctype_ptr;
			using terminal_ctype_cptr	= typename base::terminal_ctype_cptr;
			using terminal_ctype_ref	= typename base::terminal_ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		protected:

			nik_ce void assign(initial_type_cptr i, terminal_type_cptr t)
			{
				base:: initial = i;
				base::terminal = t;
			}

		public:

			nik_ce plot_subarray() : base{} { }
			nik_ce plot_subarray(initial_type_cptr i, terminal_type_cptr t) : base{} { assign(i, t); }

			nik_ce  initial_type_ptr initial  () const { return base::initial; }
			nik_ce terminal_type_ptr terminal () const { return base::terminal; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// iterator:

/***********************************************************************************************************************/

// immutable:

	template<typename Subarray>
	class plot_citerator : public citerator_method<Subarray>
	{
		public:

			using base			= citerator_method<Subarray>;

			using subarray_type		= typename base::subarray_type;
			using subarray_type_ptr		= typename base::subarray_type_ptr;
			using subarray_type_cptr	= typename base::subarray_type_cptr;
			using subarray_type_ref		= typename base::subarray_type_ref;

			using subarray_ctype		= typename base::subarray_ctype;
			using subarray_ctype_ptr	= typename base::subarray_ctype_ptr;
			using subarray_ctype_cptr	= typename base::subarray_ctype_cptr;
			using subarray_ctype_ref	= typename base::subarray_ctype_ref;

			using initial_type		= typename base::initial_type;
			using initial_type_ptr		= typename base::initial_type_ptr;
			using initial_type_cptr		= typename base::initial_type_cptr;
			using initial_type_ref		= typename base::initial_type_ref;

			using initial_ctype		= typename base::initial_ctype;
			using initial_ctype_ptr		= typename base::initial_ctype_ptr;
			using initial_ctype_cptr	= typename base::initial_ctype_cptr;
			using initial_ctype_ref		= typename base::initial_ctype_ref;

			using terminal_type		= typename base::terminal_type;
			using terminal_type_ptr		= typename base::terminal_type_ptr;
			using terminal_type_cptr	= typename base::terminal_type_cptr;
			using terminal_type_ref		= typename base::terminal_type_ref;

			using terminal_ctype		= typename base::terminal_ctype;
			using terminal_ctype_ptr	= typename base::terminal_ctype_ptr;
			using terminal_ctype_cptr	= typename base::terminal_ctype_cptr;
			using terminal_ctype_ref	= typename base::terminal_ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce plot_citerator() :
				base{} { }

			nik_ce plot_citerator(initial_ctype_cptr i, terminal_ctype_cptr t, size_ctype b) :
				base{i, t, b} { }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Subarray>
	class plot_iterator : public iterator_method<Subarray>
	{
		public:

			using base			= iterator_method<Subarray>;

			using subarray_type		= typename base::subarray_type;
			using subarray_type_ptr		= typename base::subarray_type_ptr;
			using subarray_type_cptr	= typename base::subarray_type_cptr;
			using subarray_type_ref		= typename base::subarray_type_ref;

			using subarray_ctype		= typename base::subarray_ctype;
			using subarray_ctype_ptr	= typename base::subarray_ctype_ptr;
			using subarray_ctype_cptr	= typename base::subarray_ctype_cptr;
			using subarray_ctype_ref	= typename base::subarray_ctype_ref;

			using initial_type		= typename base::initial_type;
			using initial_type_ptr		= typename base::initial_type_ptr;
			using initial_type_cptr		= typename base::initial_type_cptr;
			using initial_type_ref		= typename base::initial_type_ref;

			using initial_ctype		= typename base::initial_ctype;
			using initial_ctype_ptr		= typename base::initial_ctype_ptr;
			using initial_ctype_cptr	= typename base::initial_ctype_cptr;
			using initial_ctype_ref		= typename base::initial_ctype_ref;

			using terminal_type		= typename base::terminal_type;
			using terminal_type_ptr		= typename base::terminal_type_ptr;
			using terminal_type_cptr	= typename base::terminal_type_cptr;
			using terminal_type_ref		= typename base::terminal_type_ref;

			using terminal_ctype		= typename base::terminal_ctype;
			using terminal_ctype_ptr	= typename base::terminal_ctype_ptr;
			using terminal_ctype_cptr	= typename base::terminal_ctype_cptr;
			using terminal_ctype_ref	= typename base::terminal_ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce plot_iterator() :
				base{} { }

			nik_ce plot_iterator(initial_type_cptr i, terminal_type_cptr t, size_ctype b) :
				base{i, t, b} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// plot (method):

/***********************************************************************************************************************/

// page type:

	template<typename SizeType>
	class plot_page_type
	{
		public:

			using size_type		= typename alias<SizeType>::type;
			using size_ctype	= typename alias<SizeType>::ctype;

		protected:

			size_type terminal;

		public:

			nik_ce plot_page_type() : terminal{} { }
			nik_ce plot_page_type(size_ctype t) : terminal{t} { }

			nik_ce bool operator == (const plot_page_type & s) const
				{ return (terminal == s.terminal); }

			nik_ce bool operator != (const plot_page_type & s) const
				{ return not operator == (s); }

			nik_ce explicit operator size_type () const { return terminal; }

			nik_ce plot_page_type & operator ++ (   ) { ++terminal; return *this; }
			nik_ce plot_page_type   operator ++ (int) { return terminal++; }

			nik_ce plot_page_type & operator -- (   ) { --terminal; return *this; }
			nik_ce plot_page_type   operator -- (int) { return terminal--; }

			nik_ce plot_page_type & operator += (size_ctype n) { terminal += n; return *this; }
			nik_ce plot_page_type & operator -= (size_ctype n) { terminal -= n; return *this; }
	};

/***********************************************************************************************************************/

// immutable:

	template<typename TextArray, typename PageArray, typename Subarray>
	class plot_cmethod
	{
		public:

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

			using subarray_type		= typename alias<Subarray>::type;
			using subarray_type_ptr		= typename alias<Subarray>::type_ptr;
			using subarray_type_cptr	= typename alias<Subarray>::type_cptr;
			using subarray_type_ref		= typename alias<Subarray>::type_ref;

			using subarray_ctype		= typename alias<Subarray>::ctype;
			using subarray_ctype_ptr	= typename alias<Subarray>::ctype_ptr;
			using subarray_ctype_cptr	= typename alias<Subarray>::ctype_cptr;
			using subarray_ctype_ref	= typename alias<Subarray>::ctype_ref;

			using size_type			= typename text_array_type::size_type;
			using size_ctype		= typename text_array_type::size_ctype;

			nik_ces size_type text_length	= text_array_type::length();

			using citer_type		= plot_citerator<subarray_type>;
			using citer_type_ptr		= typename alias<citer_type>::type_ptr;
			using citer_type_cptr		= typename alias<citer_type>::type_cptr;
			using citer_type_ref		= typename alias<citer_type>::type_ref;

			using citer_ctype		= typename alias<citer_type>::ctype;
			using citer_ctype_ptr		= typename alias<citer_type>::ctype_ptr;
			using citer_ctype_cptr		= typename alias<citer_type>::ctype_cptr;
			using citer_ctype_ref		= typename alias<citer_type>::ctype_ref;

		protected:

			text_array_type text;
			page_array_type page;

		protected:

			nik_ce size_type offset() const { return size() * text_length; }

		public:

			nik_ce plot_cmethod() : text{}, page{} { }

			template<typename T, auto N, typename P, auto M>
			nik_ce plot_cmethod(const T (&t)[N], const P (&p)[M]) : text{t}, page{p} { }

			nik_ce text_array_ctype_ref ctext() const { return text; }
			nik_ce page_array_ctype_ref cpage() const { return page; }

			// initial:

				nik_ce citer_type cbegin() const
					{ return citer_type{text.cbegin(), page.cbegin(), text_length}; }

				nik_ce citer_type cend() const
					{ return citer_type{text.citer(offset()), page.cend(), text_length}; }

			// terminal:

				nik_ce size_type size() const { return page.size(); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename TextArray, typename PageArray, typename CSubarray, typename Subarray>
	class plot_method : public plot_cmethod<TextArray, PageArray, CSubarray>
	{
		public:

			using base			= plot_cmethod<TextArray, PageArray, CSubarray>;

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

			using subarray_type		= typename alias<Subarray>::type;
			using subarray_type_ptr		= typename alias<Subarray>::type_ptr;
			using subarray_type_cptr	= typename alias<Subarray>::type_cptr;
			using subarray_type_ref		= typename alias<Subarray>::type_ref;

			using subarray_ctype		= typename alias<Subarray>::ctype;
			using subarray_ctype_ptr	= typename alias<Subarray>::ctype_ptr;
			using subarray_ctype_cptr	= typename alias<Subarray>::ctype_cptr;
			using subarray_ctype_ref	= typename alias<Subarray>::ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using iter_type			= plot_iterator<subarray_type>;
			using iter_type_ptr		= typename alias<iter_type>::type_ptr;
			using iter_type_cptr		= typename alias<iter_type>::type_cptr;
			using iter_type_ref		= typename alias<iter_type>::type_ref;

			using iter_ctype		= typename alias<iter_type>::ctype;
			using iter_ctype_ptr		= typename alias<iter_type>::ctype_ptr;
			using iter_ctype_cptr		= typename alias<iter_type>::ctype_cptr;
			using iter_ctype_ref		= typename alias<iter_type>::ctype_ref;

		public:

			nik_ce plot_method() : base{} { }

			template<typename T, auto N, typename P, auto M>
			nik_ce plot_method(const T (&t)[N], const P (&p)[M]) : base{t, p} { }

			nik_ce text_array_type_ref text() { return base::text; }
			nik_ce page_array_type_ref page() { return base::page; }

			// immutable:

			// mutable:

				nik_ce iter_type begin()
					{ return iter_type{text().begin(), page().begin(), base::text_length}; }

				nik_ce iter_type end()
					{ return iter_type{text().iter(base::offset()), page().end(), base::text_length}; }

				nik_ce void upsize(size_ctype n = 1) { page().upsize(n); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// plottable (method):

/***********************************************************************************************************************/

// immutable:

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

			using base::cpage;
			using base::ctext;

		//	nik_ce page_ctype_ptr row_cbegin (size_ctype n) const { return cpage().citer(row_start(n)); }
		//	nik_ce page_ctype_ptr row_cend   (size_ctype n) const { return row_cbegin(n + 1); }
		//	nik_ce page_ctype_ptr row_clast  (size_ctype n) const { return row_cend(n) - 1; }

		//	nik_ce page_ctype_ptr operator [] (size_ctype n) const { return row_cbegin(n); }
	};

/***********************************************************************************************************************/

// mutable:

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

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// plot:

/***********************************************************************************************************************/

// immutable:

	template<typename Text, typename Page, typename SizeType>
	class cplot	: public plot_cmethod
			<
				carray         < Text        , SizeType >,
				carray         < Page        , SizeType >,
				plot_csubarray < Text , Page , SizeType >
			>
	{
		public:

			using text_array_type	= carray<Text, SizeType>;
			using page_array_type	= carray<Page, SizeType>;
			using csubarray_type	= plot_csubarray<Text, Page, SizeType>;
			using base		= plot_cmethod<text_array_type, page_array_type, csubarray_type>;

		public:

			nik_ce cplot() : base{} { }

			template<typename T, auto N, typename P, auto M>
			nik_ce cplot(const T (&t)[N], const P (&p)[M]) : base{t, p} { }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Text, typename Page, typename SizeType, SizeType TextSize, SizeType PageSize>
	class plot	: public plot_method
			<
				array          < Text        , SizeType , TextSize * PageSize >,
				array          < Page        , SizeType ,            PageSize >,
				plot_csubarray < Text , Page , SizeType                       >,
				plot_subarray  < Text , Page , SizeType , TextSize            >
			>
	{
		public:

			using text_array_type	= array<Text, SizeType, TextSize * PageSize>;
			using page_array_type	= array<Page, SizeType, PageSize>;
			using csubarray_type	= plot_csubarray<Text, Page, SizeType>;
			using subarray_type	= plot_subarray<Text, Page, SizeType, TextSize>;
			using base		= plot_method
						<
							text_array_type, page_array_type,
							csubarray_type, subarray_type
						>;

		public:

			nik_ce plot() : base{} { }

			template<typename T, auto N, typename P, auto M>
			nik_ce plot(const T (&t)[N], const P (&p)[M]) : base{t, p} { }
	};

/***********************************************************************************************************************/

// unique:

	template<typename Text, typename Page, typename SizeType, SizeType TextSize, SizeType PageSize>
	class unique_plot : public plot<Text, Page, SizeType, TextSize, PageSize>
	{
		public:

			using base			= plot<Text, Page, SizeType, TextSize, PageSize>;

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

			nik_ce unique_plot() : base{} { }

			template<typename T, auto N, typename P, auto M>
			nik_ce unique_plot(const T (&t)[N], const P (&p)[M]) : base{t, p} { }

			template<typename In, typename End>
			nik_ce void push(In in, End end)
				{ if (base::omits(in, end)) { base::push(in, end); } }

			template<typename In, typename End>
			nik_ce size_type left_find_push(In in, End end)
			{
				size_ctype pos = base::left_find(in, end);

				if (pos == base::cpage().size()) { base::push(in, end); }

				return pos;
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// plottable:

/***********************************************************************************************************************/

// immutable:

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

/***********************************************************************************************************************/

// mutable:

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

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::engine

