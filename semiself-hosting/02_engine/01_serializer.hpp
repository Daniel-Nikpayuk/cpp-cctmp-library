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

// serializer:

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

		// text: circumstantial semantics separate from base.

	template<typename Base, typename Text>
	class protoplot : public Base
	{
		public:

			using base		= Base;

			using type		= typename base::type;
			using type_ptr		= typename base::type_ptr;
			using type_cptr		= typename base::type_cptr;
			using type_ref		= typename base::type_ref;

			using ctype		= typename base::ctype;
			using ctype_ptr		= typename base::ctype_ptr;
			using ctype_cptr	= typename base::ctype_cptr;
			using ctype_ref		= typename base::ctype_ref;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

			using text_type		= typename alias<Text>::type;
			using text_type_ptr	= typename alias<Text>::type_ptr;
			using text_type_ref	= typename alias<Text>::type_ref;
			using text_ctype_ptr	= typename alias<Text>::ctype_ptr;
			using text_ctype_cptr	= typename alias<Text>::ctype_cptr;
			using text_ctype_ref	= typename alias<Text>::ctype_ref;

		protected:

			text_type text;

			nik_ce size_type start  (size_ctype n) const { return base::operator [] (n).start(); }
			nik_ce size_type finish (size_ctype n) const { return base::operator [] (n).finish(); }

		public:

			nik_ce protoplot() { }

			template<typename P, auto N, typename T, auto M>
			nik_ce protoplot(const P (&p)[N], const T (&t)[M]) : base{p}, text{t} { }

			// initial:

				using base::origin;
				using base::cbegin;
				using base::citer;
				using base::left_size;
				using base::not_equal;
				using base::equal;

				nik_ce text_ctype_ptr origin(size_ctype n) const { return text.citer(start(n)); }
				nik_ce text_ctype_ptr cbegin(size_ctype n) const { return text.citer(start(n)); }

				nik_ce text_ctype_ptr citer(size_ctype n, size_ctype m) const
					{ return cbegin(n) + m; }

				nik_ce size_type left_size(size_ctype n, text_ctype_cptr i) const
					{ return i - cbegin(n); }

				nik_ce text_ctype_ref at(size_ctype n, size_ctype m) const { return cbegin(n)[m]; }

				template<typename In, typename End>
				nik_ce bool not_equal(size_ctype n, In in, End end) const
					{ return text.not_equal(start(n), in, end); }

				template<typename In, typename End>
				nik_ce bool equal(size_ctype n, In in, End end) const
					{ return text.equal(start(n), in, end); }

			// terminal:

				using base::size;
				using base::max;
				using base::is_empty;
				using base::not_empty;
				using base::cend;
				using base::clast;
				using base::right_size;

				nik_ce size_type size (size_ctype n) const { return finish(n) - start(n); }
				nik_ce size_type max  (size_ctype n) const { return size(n) - 1; }

				nik_ce bool is_empty  (size_ctype n) const { return (size(n) == 0); }
				nik_ce bool not_empty (size_ctype n) const { return (size(n) != 0); }

				nik_ce text_ctype_ptr cend  (size_ctype n) const { return text.citer(finish(n)); }
				nik_ce text_ctype_ptr clast (size_ctype n) const { return cend(n) - 1; }

				nik_ce size_type right_size(size_ctype n, text_ctype_cptr i) const
					{ return cend(n) - i; }
	};

/***********************************************************************************************************************/

// literal:

	template<typename Page, typename Text, typename SizeType>
	class plot_literal	: public protoplot
				<
					cctmp::array_literal < Page , SizeType >,
					cctmp::array_literal < Text , SizeType >
				>
	{
		public:

			using base		= protoplot
						<
							cctmp::array_literal < Page , SizeType >,
							cctmp::array_literal < Text , SizeType >
						>;

			using type		= typename base::type;
			using type_ptr		= typename base::type_ptr;
			using type_cptr		= typename base::type_cptr;
			using type_ref		= typename base::type_ref;

			using ctype		= typename base::ctype;
			using ctype_ptr		= typename base::ctype_ptr;
			using ctype_cptr	= typename base::ctype_cptr;
			using ctype_ref		= typename base::ctype_ref;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

			using text_type		= typename base::text_type;
			using text_type_ptr	= typename base::text_type_ptr;
			using text_type_ref	= typename base::text_type_ref;
			using text_ctype_ptr	= typename base::text_ctype_ptr;
			using text_ctype_cptr	= typename base::text_ctype_cptr;
			using text_ctype_ref	= typename base::text_ctype_ref;

		public:

			nik_ce plot_literal() { }

			template<typename P, auto N, typename T, auto M>
			nik_ce plot_literal(const P (&p)[N], const T (&t)[M]) : base{p, t} { }
	};

/***********************************************************************************************************************/

// interface:

	template<typename Page, typename Text, typename SizeType, SizeType Size>
	class plot	: public protoplot // array_size(Page) <= array_size(Text)
			<
				cctmp::array < Page , SizeType , Size >,
				cctmp::array < Text , SizeType , Size >
			>
	{
		public:

			using base		= protoplot
						<
							cctmp::array < Page , SizeType , Size >,
							cctmp::array < Text , SizeType , Size >
						>;

			using type		= typename base::type;
			using type_ptr		= typename base::type_ptr;
			using type_cptr		= typename base::type_cptr;
			using type_ref		= typename base::type_ref;

			using ctype		= typename base::ctype;
			using ctype_ptr		= typename base::ctype_ptr;
			using ctype_cptr	= typename base::ctype_cptr;
			using ctype_ref		= typename base::ctype_ref;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

			using text_type		= typename base::text_type;
			using text_type_ptr	= typename base::text_type_ptr;
			using text_type_ref	= typename base::text_type_ref;
			using text_ctype_ptr	= typename base::text_ctype_ptr;
			using text_ctype_cptr	= typename base::text_ctype_cptr;
			using text_ctype_ref	= typename base::text_ctype_ref;

		protected:

			nik_ce void push_finish(size_ctype start)
			{
				size_ctype finish = base::text.size();

				base::upsize();
				base::last()->set_start  (start);
				base::last()->set_finish (finish);
			}

			nik_ce void set_finish(size_ctype n, size_ctype start)
			{
				size_ctype finish = base::text.size();

				base::operator [] (n).set_start  (start);
				base::operator [] (n).set_finish (finish);
			}

		public:

			nik_ce plot() { }

			template<typename P, auto N, typename T, auto M>
			nik_ce plot(const P (&p)[N], const T (&t)[M]) : base{p, t} { }

			// mutable:

				using base::begin;
				using base::end;
				using base::last;
				using base::at;
				using base::iter;

				nik_ce text_type_ptr begin (size_ctype n) { return base::text.iter(base::start(n)); }
				nik_ce text_type_ptr end   (size_ctype n) { return base::text.iter(base::finish(n)); }
				nik_ce text_type_ptr last  (size_ctype n) { return end(n) - 1; }

				nik_ce text_type_ref at(size_ctype n, size_ctype m) { return begin(n)[m]; }

				nik_ce text_type_ptr iter(size_ctype n, size_ctype m) { return begin(n) + m; }

				template<typename In, typename End>
				nik_ce void push(In in, End end)
				{
					size_ctype start = base::text.size();

					base::text.push(in, end);
					push_finish(start);
				}

				template<typename F, typename In, typename End>
				nik_ce void pushmap(F f, In in, End end)
				{
					size_ctype start = base::text.size();

					base::text.pushmap(f, in, end);
					push_finish(start);
				}

				template<typename F, typename In, typename End>
				nik_ce void setmap(size_ctype n, F f, In in, End end)
				{
					size_ctype start = base::text.size();

					base::text.pushmap(f, in, end);
					set_finish(n, start);
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// plottable:

/***********************************************************************************************************************/

// proto:

	template<typename Base, typename SizeType, SizeType RowSize, SizeType ColSize>
	class protoplottable : public Base
	{
		public:

			using base		= Base;

			using type		= typename base::type;
			using type_ptr		= typename base::type_ptr;
			using type_cptr		= typename base::type_cptr;
			using type_ref		= typename base::type_ref;

			using ctype		= typename base::ctype;
			using ctype_ptr		= typename base::ctype_ptr;
			using ctype_cptr	= typename base::ctype_cptr;
			using ctype_ref		= typename base::ctype_ref;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			nik_ce protoplottable() { }

			template<typename P, auto N, typename T, auto M>
			nik_ce protoplottable(const P (&p)[N], const T (&t)[M]) : base{p, t} { }

			nik_ce size_type row_length () const { return RowSize; }
			nik_ce size_type col_length () const { return ColSize; }

			nik_ce ctype_ptr row_cbegin (size_ctype n) const { return base::citer(n * ColSize); }
			nik_ce ctype_ptr row_cend   (size_ctype n) const { return row_cbegin(n + 1); }
			nik_ce ctype_ptr row_clast  (size_ctype n) const { return row_cend(n) - 1; }

			nik_ce ctype_ptr operator [] (size_ctype n) const { return row_cbegin(n); }
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

			using subbase		= plot_literal<Page, Text, SizeType>;
			using base		= protoplottable<subbase, SizeType, RowSize, ColSize>;

			using type		= typename base::type;
			using type_ptr		= typename base::type_ptr;
			using type_cptr		= typename base::type_cptr;
			using type_ref		= typename base::type_ref;

			using ctype		= typename base::ctype;
			using ctype_ptr		= typename base::ctype_ptr;
			using ctype_cptr	= typename base::ctype_cptr;
			using ctype_ref		= typename base::ctype_ref;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			nik_ce plottable_literal() { }

			template<typename P, auto N, typename T, auto M>
			nik_ce plottable_literal(const P (&p)[N], const T (&t)[M]) : base{p, t} { }

			nik_ce bool operator != (const plottable_literal & l) const
				{ return base::not_equal(0, l.cbegin(), l.cend()); }

			nik_ce bool operator == (const plottable_literal & l) const
				{ return base::equal(0, l.cbegin(), l.cend()); }
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

			using subbase		= plot<Page, Text, SizeType, RowSize * ColSize>;
			using base		= protoplottable<subbase, SizeType, RowSize, ColSize>;

			using type		= typename base::type;
			using type_ptr		= typename base::type_ptr;
			using type_cptr		= typename base::type_cptr;
			using type_ref		= typename base::type_ref;

			using ctype		= typename base::ctype;
			using ctype_ptr		= typename base::ctype_ptr;
			using ctype_cptr	= typename base::ctype_cptr;
			using ctype_ref		= typename base::ctype_ref;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			nik_ce plottable() { }

			template<typename P, auto N, typename T, auto M>
			nik_ce plottable(const P (&p)[N], const T (&t)[M]) : base{p, t} { }

			using base::operator [];

			nik_ce type_ptr row_begin (size_ctype n) { return base::iter(n * ColSize); }
			nik_ce type_ptr row_end   (size_ctype n) { return row_begin(n + 1); }
			nik_ce type_ptr row_last  (size_ctype n) { return row_end(n) - 1; }

			nik_ce type_ptr operator [] (size_ctype n) { return row_begin(n); }

			template<typename F, typename In, typename End>
			nik_ce void setmap(size_ctype row, size_ctype col, F f, In in, End end)
				{ base::setmap(row * ColSize + col, f, in, end); }
	};

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

		public:

			nik_ce corpus_entry() : initial{}, terminal{} { }

			nik_ce size_type start  () const { return initial; }
			nik_ce size_type finish () const { return terminal; }

			nik_ce void set_start  (size_ctype i) { initial = i; }
			nik_ce void set_finish (size_ctype t) { terminal = t; }
	};

/***********************************************************************************************************************/

// proto:

		// text: circumstantial semantics separate from base.

	template<typename Base, typename Page, typename Text>
	class protocorpus : public Base
	{
		public:

			using base		= Base;

			using type		= typename base::type;
			using type_ptr		= typename base::type_ptr;
			using type_cptr		= typename base::type_cptr;
			using type_ref		= typename base::type_ref;

			using ctype		= typename base::ctype;
			using ctype_ptr		= typename base::ctype_ptr;
			using ctype_cptr	= typename base::ctype_cptr;
			using ctype_ref		= typename base::ctype_ref;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

			using page_type		= typename alias<Page>::type;
			using page_type_ptr	= typename alias<Page>::type_ptr;
			using page_type_ref	= typename alias<Page>::type_ref;
			using page_ctype_ptr	= typename alias<Page>::ctype_ptr;
			using page_ctype_cptr	= typename alias<Page>::ctype_cptr;
			using page_ctype_ref	= typename alias<Page>::ctype_ref;

			using text_type		= typename alias<Text>::type;
			using text_type_ptr	= typename alias<Text>::type_ptr;
			using text_type_ref	= typename alias<Text>::type_ref;
			using text_ctype_ptr	= typename alias<Text>::ctype_ptr;
			using text_ctype_cptr	= typename alias<Text>::ctype_cptr;
			using text_ctype_ref	= typename alias<Text>::ctype_ref;

		protected:

			page_type page;
			text_type text;

			nik_ce size_type start  (size_ctype n) const { return base::operator [] (n).start(); }
			nik_ce size_type finish (size_ctype n) const { return base::operator [] (n).finish(); }

		public:

			nik_ce protocorpus() { }

			template<typename B, auto N, typename P, auto M, typename T, auto L>
			nik_ce protocorpus(const B (&b)[N], const P (&p)[M], const T (&t)[L]) :
				base{b}, page{p}, text{t}
					{ }

			// initial:

			//	using base::origin;
			//	using base::cbegin;
			//	using base::citer;
			//	using base::left_size;
			//	using base::not_equal;
			//	using base::equal;

			//	nik_ce text_ctype_ptr origin(size_ctype n) const { return text.citer(start(n)); }
			//	nik_ce text_ctype_ptr cbegin(size_ctype n) const { return text.citer(start(n)); }

			//	nik_ce text_ctype_ptr citer(size_ctype n, size_ctype m) const
			//		{ return cbegin(n) + m; }

			//	nik_ce size_type left_size(size_ctype n, text_ctype_cptr i) const
			//		{ return i - cbegin(n); }

			//	nik_ce text_ctype_ref at(size_ctype n, size_ctype m) const { return cbegin(n)[m]; }

			//	template<typename In, typename End>
			//	nik_ce bool not_equal(size_ctype n, In in, End end) const
			//		{ return text.not_equal(start(n), in, end); }

			//	template<typename In, typename End>
			//	nik_ce bool equal(size_ctype n, In in, End end) const
			//		{ return text.equal(start(n), in, end); }

			// terminal:

			//	using base::size;
			//	using base::max;
			//	using base::is_empty;
			//	using base::not_empty;
			//	using base::cend;
			//	using base::clast;
			//	using base::right_size;

			//	nik_ce size_type size (size_ctype n) const { return finish(n) - start(n); }
			//	nik_ce size_type max  (size_ctype n) const { return size(n) - 1; }

			//	nik_ce bool is_empty  (size_ctype n) const { return (size(n) == 0); }
			//	nik_ce bool not_empty (size_ctype n) const { return (size(n) != 0); }

			//	nik_ce text_ctype_ptr cend  (size_ctype n) const { return text.citer(finish(n)); }
			//	nik_ce text_ctype_ptr clast (size_ctype n) const { return cend(n) - 1; }

			//	nik_ce size_type right_size(size_ctype n, text_ctype_cptr i) const
			//		{ return cend(n) - i; }
	};

/***********************************************************************************************************************/

// literal:

/***********************************************************************************************************************/

// interface:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::engine

