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

// corpus:

namespace cctmp  {
namespace engine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// corpus:

/***********************************************************************************************************************/

// entry:

	template<typename SizeType>
	class corpus_entry
	{
		public:

			using size_type		= typename alias<SizeType>::type;
			using size_ctype	= typename alias<SizeType>::ctype;

		protected:

			size_type initial;
			size_type terminal;
			size_type length;

		public:

			nik_ce corpus_entry() : initial{}, terminal{}, length{} { }

			nik_ce size_type start    () const { return initial; }
			nik_ce size_type finish   () const { return terminal; }
			nik_ce size_type capacity () const { return length; }

			nik_ce void set_start    (size_ctype i) { initial = i; }
			nik_ce void set_finish   (size_ctype t) { terminal = t; }
			nik_ce void set_capacity (size_ctype l) { length = l; }

			nik_ce void upsize(size_ctype n = 1) { terminal += n; } // needs to test capacity.
	};

/***********************************************************************************************************************/

// proto:

		// text: circumstantial semantics separate from page.

	template<typename BodyArray, typename PageArray, typename TextArray>
	class protocorpus
	{
		public:

			using body_array_type		= typename alias<BodyArray>::type;
			using body_array_type_ptr	= typename alias<BodyArray>::type_ptr;
			using body_array_type_cptr	= typename alias<BodyArray>::type_cptr;
			using body_array_type_ref	= typename alias<BodyArray>::type_ref;

			using body_array_ctype		= typename alias<BodyArray>::ctype;
			using body_array_ctype_ptr	= typename alias<BodyArray>::ctype_ptr;
			using body_array_ctype_cptr	= typename alias<BodyArray>::ctype_cptr;
			using body_array_ctype_ref	= typename alias<BodyArray>::ctype_ref;

			using body_type			= typename body_array_type::type;
			using body_type_ptr		= typename body_array_type::type_ptr;
			using body_type_cptr		= typename body_array_type::type_cptr;
			using body_type_ref		= typename body_array_type::type_ref;

			using body_ctype		= typename body_array_type::ctype;
			using body_ctype_ptr		= typename body_array_type::ctype_ptr;
			using body_ctype_cptr		= typename body_array_type::ctype_cptr;
			using body_ctype_ref		= typename body_array_type::ctype_ref;

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

			body_array_type body;
			page_array_type page;
			text_array_type text;

			nik_ce size_type start    (size_ctype n) const { return cbody().cat(n).start(); }
			nik_ce size_type finish   (size_ctype n) const { return cbody().cat(n).finish(); }
			nik_ce size_type capacity (size_ctype n) const { return cbody().cat(n).capacity(); }

		public:

			nik_ce protocorpus() { }

			template<typename B, auto N, typename P, auto M, typename T, auto L>
			nik_ce protocorpus(const B (&b)[N], const P (&p)[M], const T (&t)[L]) :
				body{b}, page{p}, text{t}
					{ }

			nik_ce body_array_ctype_ref cbody() const { return body; }
			nik_ce page_array_ctype_ref cpage() const { return page; }
			nik_ce text_array_ctype_ref ctext() const { return text; }

			nik_ce size_type start(size_ctype n, size_ctype m) const
				{ return page[start(n) + m].start(); }

			nik_ce size_type finish(size_ctype n, size_ctype m) const
				{ return page[start(n) + m].finish(); }

			// initial:

				nik_ce text_ctype_ptr cbegin(size_ctype n, size_ctype m) const
					{ return text.citer(start(n, m)); }

				nik_ce size_type left_size(size_ctype n, size_ctype m, text_ctype_cptr i) const
					{ return i - cbegin(n, m); }

				nik_ce text_ctype_ptr citer(size_ctype n, size_ctype m, size_ctype l) const
					{ return cbegin(n, m) + l; }

				nik_ce text_ctype_ref cat(size_ctype n, size_ctype m, size_ctype l) const
					{ return cbegin(n, m)[l]; }

				template<typename In, typename End>
				nik_ce bool equal(size_ctype n, size_ctype m, In in, End end) const
					{ return text.equal(start(n, m), in, end); }

				template<typename In, typename End>
				nik_ce bool not_equal(size_ctype n, size_ctype m, In in, End end) const
					{ return text.not_equal(start(n, m), in, end); }

			// terminal:

				nik_ce size_type size(size_ctype n, size_ctype m) const
					{ return finish(n, m) - start(n, m); }

				nik_ce size_type max(size_ctype n, size_ctype m) const { return size(n, m) - 1; }

				nik_ce text_ctype_ptr cend(size_ctype n, size_ctype m) const
					{ return text.citer(finish(n, m)); }

				nik_ce text_ctype_ptr clast(size_ctype n, size_ctype m) const { return cend(n, m) - 1; }

				nik_ce size_type right_size(size_ctype n, size_ctype m, text_ctype_cptr i) const
					{ return cend(n, m) - i; }

				nik_ce bool is_empty  (size_ctype n, size_ctype m) const { return (size(n, m) == 0); }
				nik_ce bool not_empty (size_ctype n, size_ctype m) const { return (size(n, m) != 0); }
	};

/***********************************************************************************************************************/

// literal:

	template<typename Body, typename Page, typename Text, typename SizeType>
	class corpus_literal	: public protocorpus
				<
					array_literal < Body , SizeType >,
					array_literal < Page , SizeType >,
					array_literal < Text , SizeType >
				>
	{
		public:

			using body_array_type		= array_literal < Body , SizeType >;
			using page_array_type		= array_literal < Page , SizeType >;
			using text_array_type		= array_literal < Text , SizeType >;
			using base			= protocorpus<body_array_type, page_array_type, text_array_type>;

			using body_array_type_ptr	= typename base::body_array_type_ptr;
			using body_array_type_cptr	= typename base::body_array_type_cptr;
			using body_array_type_ref	= typename base::body_array_type_ref;

			using body_array_ctype		= typename base::body_array_ctype;
			using body_array_ctype_ptr	= typename base::body_array_ctype_ptr;
			using body_array_ctype_cptr	= typename base::body_array_ctype_cptr;
			using body_array_ctype_ref	= typename base::body_array_ctype_ref;

			using body_type			= typename base::body_type;
			using body_type_ptr		= typename base::body_type_ptr;
			using body_type_cptr		= typename base::body_type_cptr;
			using body_type_ref		= typename base::body_type_ref;

			using body_ctype		= typename base::body_ctype;
			using body_ctype_ptr		= typename base::body_ctype_ptr;
			using body_ctype_cptr		= typename base::body_ctype_cptr;
			using body_ctype_ref		= typename base::body_ctype_ref;

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

			nik_ce corpus_literal() { }

			template<typename B, auto N, typename P, auto M, typename T, auto L>
			nik_ce corpus_literal(const B (&b)[N], const P (&p)[M], const T (&t)[L]) : base{b, p, t} { }
	};

/***********************************************************************************************************************/

// interface:

	template
	<
		typename Body, typename Page, typename Text, typename SizeType,
		SizeType BodySize, SizeType PageSize, SizeType TextSize = PageSize
	>
	class corpus	: public protocorpus // PageSize <= TextSize
			<
				array < Body , SizeType , BodySize >,
				array < Page , SizeType , PageSize >,
				array < Text , SizeType , TextSize >
			>
	{
		public:

			using body_array_type		= array < Body , SizeType , BodySize >;
			using page_array_type		= array < Page , SizeType , PageSize >;
			using text_array_type		= array < Text , SizeType , TextSize >;
			using base			= protocorpus<body_array_type, page_array_type, text_array_type>;

			using body_array_type_ptr	= typename base::body_array_type_ptr;
			using body_array_type_cptr	= typename base::body_array_type_cptr;
			using body_array_type_ref	= typename base::body_array_type_ref;

			using body_array_ctype		= typename base::body_array_ctype;
			using body_array_ctype_ptr	= typename base::body_array_ctype_ptr;
			using body_array_ctype_cptr	= typename base::body_array_ctype_cptr;
			using body_array_ctype_ref	= typename base::body_array_ctype_ref;

			using body_type			= typename base::body_type;
			using body_type_ptr		= typename base::body_type_ptr;
			using body_type_cptr		= typename base::body_type_cptr;
			using body_type_ref		= typename base::body_type_ref;

			using body_ctype		= typename base::body_ctype;
			using body_ctype_ptr		= typename base::body_ctype_ptr;
			using body_ctype_cptr		= typename base::body_ctype_cptr;
			using body_ctype_ref		= typename base::body_ctype_ref;

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

			nik_ce void push_finish(size_ctype n, size_ctype text_start)
			{
				size_ctype text_finish  = base::ctext().size();
				size_ctype page_current = base::finish(n);

				body().at(n).upsize();

				page().at(page_current).set_start  (text_start);
				page().at(page_current).set_finish (text_finish);
			}

			nik_ce void set_finish(size_ctype n, size_ctype m, size_ctype text_start)
			{
				size_ctype text_finish  = base::ctext().size();
				size_ctype page_current = base::start(n) + m;

				page().at(page_current).set_start  (text_start);
				page().at(page_current).set_finish (text_finish);
			}

		public:

			nik_ce corpus() : base{} { page().fullsize(); }

			template<typename B, auto N, typename P, auto M, typename T, auto L>
			nik_ce corpus(const B (&b)[N], const P (&p)[M], const T (&t)[L]) : base{b, p, t} { }

			nik_ce body_array_type_ref body() { return base::body; }
			nik_ce page_array_type_ref page() { return base::page; }
			nik_ce text_array_type_ref text() { return base::text; }

			// mutable:

				nik_ce text_type_ptr begin(size_ctype n, size_ctype m)
					{ return text().iter(base::start(n, m)); }

				nik_ce text_type_ptr iter(size_ctype n, size_ctype m, size_ctype l)
					{ return begin(n, m) + l; }

				nik_ce text_type_ref at(size_ctype n, size_ctype m, size_ctype l)
					{ return begin(n, m)[l]; }

				nik_ce text_type_ptr end(size_ctype n, size_ctype m)
					{ return text().iter(base::finish(n, m)); }

				nik_ce text_type_ptr last(size_ctype n, size_ctype m) { return end(n, m) - 1; }

				template<typename In, typename End>
				nik_ce void push(size_ctype n, In in, End end)
				{
					size_ctype text_start = base::ctext().size();

					text().push(in, end);
					push_finish(n, text_start);
				}

				template<typename F, typename In, typename End>
				nik_ce void pushmap(size_ctype n, F f, In in, End end)
				{
					size_ctype text_start = base::ctext().size();

					text().pushmap(f, in, end);
					push_finish(n, text_start);
				}

				template<typename F, typename In, typename End>
				nik_ce void setmap(size_ctype n, size_ctype m, F f, In in, End end)
				{
					size_ctype text_start = base::ctext().size();

					text().pushmap(f, in, end);
					set_finish(n, m, text_start);
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::engine

