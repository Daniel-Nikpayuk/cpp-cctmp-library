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

// container:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array (method):

	// assumptions:

		// initial  {}; static_cast< initial_ctype_ptr >(  initial);
		// terminal {}; static_cast<         size_type >(*terminal);

		// terminal  = N;
		// terminal += N; ++terminal; terminal++;
		// terminal -= N; --terminal; terminal--;

/***********************************************************************************************************************/

// immutable:

	template<typename InitialTrait, typename TerminalTrait, typename SizeType>
	class array_cmethod
	{
		public:

			using initial_cotype		= typename InitialTrait::cotype;

			using initial_mode		= typename InitialTrait::mode;
			using initial_mode_ptr		= typename InitialTrait::mode_ptr;
			using initial_mode_cptr		= typename InitialTrait::mode_cptr;
			using initial_mode_ref		= typename InitialTrait::mode_ref;

			using initial_type		= typename InitialTrait::type;
			using initial_type_ptr		= typename InitialTrait::type_ptr;
			using initial_type_cptr		= typename InitialTrait::type_cptr;
			using initial_type_ref		= typename InitialTrait::type_ref;

			using initial_ctype		= typename InitialTrait::ctype;
			using initial_ctype_ptr		= typename InitialTrait::ctype_ptr;
			using initial_ctype_cptr	= typename InitialTrait::ctype_cptr;
			using initial_ctype_ref		= typename InitialTrait::ctype_ref;

			using terminal_cotype		= typename TerminalTrait::cotype;

			using terminal_mode		= typename TerminalTrait::mode;
			using terminal_mode_ptr		= typename TerminalTrait::mode_ptr;
			using terminal_mode_cptr	= typename TerminalTrait::mode_cptr;
			using terminal_mode_ref		= typename TerminalTrait::mode_ref;

			using terminal_type		= typename TerminalTrait::type;
			using terminal_type_ptr		= typename TerminalTrait::type_ptr;
			using terminal_type_cptr	= typename TerminalTrait::type_cptr;
			using terminal_type_ref		= typename TerminalTrait::type_ref;

			using terminal_ctype		= typename TerminalTrait::ctype;
			using terminal_ctype_ptr	= typename TerminalTrait::ctype_ptr;
			using terminal_ctype_cptr	= typename TerminalTrait::ctype_cptr;
			using terminal_ctype_ref	= typename TerminalTrait::ctype_ref;

			using size_type			= typename alias<SizeType>::type;
			using size_ctype		= typename alias<SizeType>::ctype;

		protected:

			 initial_cotype  initial; // compile time compatible.
			terminal_cotype terminal; // compile time compatible.

		public:

			nik_ce array_cmethod()
				: initial{}, terminal{} { }

			// initial:

				nik_ce initial_ctype_ptr cbegin() const
					{ return static_cast<initial_ctype_ptr>(initial); }

				nik_ce initial_ctype_ptr origin() const { return cbegin(); }

				nik_ce size_type left_size(initial_ctype_cptr i) const { return i - cbegin(); }

				nik_ce initial_ctype_ptr citer (size_ctype n) const { return cbegin() + n; }
				nik_ce initial_ctype_ref cat   (size_ctype n) const { return cbegin()[n]; }

				nik_ce initial_ctype_ptr find(initial_ctype_ref v) const
				{
					initial_ctype_ptr in = cbegin();

					while (in != cend()) { if (*in == v) { break; } else { ++in; } }

					return in;
				}

				nik_ce size_type left_find(initial_ctype_ref v) const { return left_size(find(v)); }
				nik_ce bool contains(initial_ctype_ref v) const { return (find(v) != cend()); }
				nik_ce bool omits(initial_ctype_ref v) const { return not contains(v); }

				template<typename In, typename End>
				nik_ce bool equal(size_ctype n, In in, End end) const
				{
					for (initial_ctype_ptr out = citer(n); in != end; ++out, ++in)
						{ if (*out != *in) { return false; } }

					return true;
				}

				template<typename In, typename End>
				nik_ce bool not_equal(size_ctype n, In in, End end) const
					{ return not equal(n, in, end); }

				template<typename T>
				nik_ce bool operator == (const T & v) const
					{ return equal(0, v.cbegin(), v.cend()); }

				template<typename T>
				nik_ce bool operator != (const T & v) const
					{ return not_equal(0, v.cbegin(), v.cend()); }

				nik_ce initial_ctype_ref operator [] (size_ctype n) const { return cat(n); }

			// terminal:

				nik_ce size_type size () const { return static_cast<size_type>(*terminal); }
				nik_ce size_type max  () const { return size() - 1; }

				nik_ce initial_ctype_ptr cend  () const { return citer(size()); }
				nik_ce initial_ctype_ptr clast () const { return cend() - 1; }

				nik_ce size_type right_size(initial_ctype_cptr i) const { return cend() - i; }

				nik_ce size_type right_find(initial_ctype_ref v) const { return right_size(find(v)); }

				nik_ce bool is_empty  () const { return (size() == 0); }
				nik_ce bool not_empty () const { return (size() != 0); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename InitialTrait, typename TerminalTrait, typename SizeType, SizeType Size>
	class array_method : public array_cmethod<InitialTrait, TerminalTrait, SizeType>
	{
		public:

			using base			= array_cmethod<InitialTrait, TerminalTrait, SizeType>;

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

			nik_ces size_type length() { return Size; }

		public:

			nik_ce array_method() : base{} { }

			template<typename T, auto N>
			nik_ce array_method(const T (&a)[N]) { push(a, a + N); }

			// immutable:

				using base::operator [];
				using base::left_size;
				using base::right_size;

			// mutable:

				nik_ce initial_type_ptr begin()
					{ return static_cast<initial_type_ptr>(base::initial); }

				nik_ce size_type left_size(initial_type_cptr i) const { return i - begin(); }

				nik_ce initial_type_ptr iter (size_ctype n) { return begin() + n; }
				nik_ce initial_type_ref at   (size_ctype n) { return begin()[n]; }

				nik_ce initial_type_ptr end  () { return iter(base::size()); }
				nik_ce initial_type_ptr last () { return end() - 1; }

				nik_ce size_type right_size(initial_type_cptr i) const { return end() - i; }

				nik_ce initial_type_ref operator [] (size_ctype n) { return at(n); }

				nik_ce void clear() { *base::terminal = 0; }
				nik_ce void fullsize() { *base::terminal = Size; }
				nik_ce void upsize(size_ctype n = 1) { *base::terminal += n; }
				nik_ce void downsize(size_ctype n = 1) { *base::terminal -= n; }

				nik_ce void push(initial_ctype_ref v)
					{ size_ctype s = base::size(); upsize(); *iter(s) = v; }

				nik_ce initial_type pop() { downsize(); return *iter(base::size()); }

				template<typename In, typename End>
				nik_ce void push(In in, End end) { while (in != end) { push(*in++); } }

				template<typename F, typename In, typename End>
				nik_ce void pushmap(F, In in, End end)
					{ while (in != end) { push(T_restore_T<F>::result(*in++)); } }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// iterator (method):

	// assumptions:

		// auto i = sub.initial() (+ : -) sub.offset(n);
		// auto t = sub.terminal() (+ : -) n;
		// subarray_type{i, t};

/***********************************************************************************************************************/

// immutable:

	template<typename Subarray>
	class citerator_method
	{
		public:

			using subarray_type		= typename alias<Subarray>::type;
			using subarray_type_ptr		= typename alias<Subarray>::type_ptr;
			using subarray_type_cptr	= typename alias<Subarray>::type_cptr;
			using subarray_type_ref		= typename alias<Subarray>::type_ref;

			using subarray_ctype		= typename alias<Subarray>::ctype;
			using subarray_ctype_ptr	= typename alias<Subarray>::ctype_ptr;
			using subarray_ctype_cptr	= typename alias<Subarray>::ctype_cptr;
			using subarray_ctype_ref	= typename alias<Subarray>::ctype_ref;

			using initial_type		= typename subarray_type::initial_type;
			using initial_type_ptr		= typename subarray_type::initial_type_ptr;
			using initial_type_cptr		= typename subarray_type::initial_type_cptr;
			using initial_type_ref		= typename subarray_type::initial_type_ref;

			using initial_ctype		= typename subarray_type::initial_ctype;
			using initial_ctype_ptr		= typename subarray_type::initial_ctype_ptr;
			using initial_ctype_cptr	= typename subarray_type::initial_ctype_cptr;
			using initial_ctype_ref		= typename subarray_type::initial_ctype_ref;

			using terminal_type		= typename subarray_type::terminal_type;
			using terminal_type_ptr		= typename subarray_type::terminal_type_ptr;
			using terminal_type_cptr	= typename subarray_type::terminal_type_cptr;
			using terminal_type_ref		= typename subarray_type::terminal_type_ref;

			using terminal_ctype		= typename subarray_type::terminal_ctype;
			using terminal_ctype_ptr	= typename subarray_type::terminal_ctype_ptr;
			using terminal_ctype_cptr	= typename subarray_type::terminal_ctype_cptr;
			using terminal_ctype_ref	= typename subarray_type::terminal_ctype_ref;

			using size_type			= typename subarray_type::size_type;
			using size_ctype		= typename subarray_type::size_ctype;

		protected:

			subarray_type sub;
			size_ctype block;

		protected:

			nik_ce size_type offset(size_ctype n) const { return n * block; }

			nik_ce void cincrement(size_ctype n = 1)
				{ sub = subarray_type{sub.cinitial() + offset(n), sub.cterminal() + n}; }

			nik_ce void cdecrement(size_ctype n = 1)
				{ sub = subarray_type{sub.cinitial() - offset(n), sub.cterminal() - n}; }

			nik_ce auto post_cincrement(size_ctype n = 1) -> citerator_method
				{ citerator_method post{*this}; cincrement(n); return post; }

			nik_ce auto post_cdecrement(size_ctype n = 1) -> citerator_method
				{ citerator_method post{*this}; cdecrement(n); return post; }

		public:

			nik_ce citerator_method() :
				block{} { }

			nik_ce citerator_method(initial_ctype_cptr i, terminal_ctype_cptr t, size_ctype b) :
				sub{i, t}, block{b} { }

			// immutable:

				nik_ce bool comparible(const citerator_method & i) const
					{ return (block == i.block); }

				nik_ce bool operator == (const citerator_method & i) const
					{ return (sub.cinitial() == i.sub.cinitial()); }

				nik_ce bool operator != (const citerator_method & i) const
					{ return not operator == (i); }

				nik_ce subarray_ctype_ref operator  * () const { return sub; }
				nik_ce subarray_ctype_ptr operator -> () const { return &sub; }

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

	template<typename Subarray>
	class iterator_method // does not inherit from citerator method: cannot assume they have the same subarrays.
	{
		public:

			using subarray_type		= typename alias<Subarray>::type;
			using subarray_type_ptr		= typename alias<Subarray>::type_ptr;
			using subarray_type_cptr	= typename alias<Subarray>::type_cptr;
			using subarray_type_ref		= typename alias<Subarray>::type_ref;

			using subarray_ctype		= typename alias<Subarray>::ctype;
			using subarray_ctype_ptr	= typename alias<Subarray>::ctype_ptr;
			using subarray_ctype_cptr	= typename alias<Subarray>::ctype_cptr;
			using subarray_ctype_ref	= typename alias<Subarray>::ctype_ref;

			using initial_type		= typename subarray_type::initial_type;
			using initial_type_ptr		= typename subarray_type::initial_type_ptr;
			using initial_type_cptr		= typename subarray_type::initial_type_cptr;
			using initial_type_ref		= typename subarray_type::initial_type_ref;

			using initial_ctype		= typename subarray_type::initial_ctype;
			using initial_ctype_ptr		= typename subarray_type::initial_ctype_ptr;
			using initial_ctype_cptr	= typename subarray_type::initial_ctype_cptr;
			using initial_ctype_ref		= typename subarray_type::initial_ctype_ref;

			using terminal_type		= typename subarray_type::terminal_type;
			using terminal_type_ptr		= typename subarray_type::terminal_type_ptr;
			using terminal_type_cptr	= typename subarray_type::terminal_type_cptr;
			using terminal_type_ref		= typename subarray_type::terminal_type_ref;

			using terminal_ctype		= typename subarray_type::terminal_ctype;
			using terminal_ctype_ptr	= typename subarray_type::terminal_ctype_ptr;
			using terminal_ctype_cptr	= typename subarray_type::terminal_ctype_cptr;
			using terminal_ctype_ref	= typename subarray_type::terminal_ctype_ref;

			using size_type			= typename subarray_type::size_type;
			using size_ctype		= typename subarray_type::size_ctype;

		protected:

			subarray_type sub;
			size_ctype block;

		protected:

			nik_ce size_type offset(size_ctype n) const { return n * block; }

			nik_ce void increment(size_ctype n = 1)
				{ sub = subarray_type{sub.initial() + offset(n), sub.terminal() + n}; }

			nik_ce void decrement(size_ctype n = 1)
				{ sub = subarray_type{sub.initial() - offset(n), sub.terminal() - n}; }

			nik_ce auto post_increment(size_ctype n = 1) -> iterator_method
				{ iterator_method post{*this}; increment(n); return post; }

			nik_ce auto post_decrement(size_ctype n = 1) -> iterator_method
				{ iterator_method post{*this}; decrement(n); return post; }

		public:

			nik_ce iterator_method() :
				block{} { }

			nik_ce iterator_method(initial_type_cptr i, terminal_type_cptr t, size_ctype b) :
				sub{i, t}, block{b} { }

			// immutable:

				nik_ce bool comparible(const iterator_method & i) const
					{ return (block == i.block); }

				nik_ce bool operator == (const iterator_method & i) const
					{ return (sub.initial() == i.sub.initial()); }

				nik_ce bool operator != (const iterator_method & i) const
					{ return not operator == (i); }

			// mutable:

				nik_ce iterator_method & operator ++ (   ) { increment(); return *this; }
				nik_ce iterator_method   operator ++ (int) { return post_increment(); }

				nik_ce iterator_method & operator -- (   ) { decrement(); return *this; }
				nik_ce iterator_method   operator -- (int) { return post_decrement(); }

				nik_ce iterator_method & operator += (size_ctype n) { increment(n); return *this; }
				nik_ce iterator_method & operator -= (size_ctype n) { decrement(n); return *this; }

				nik_ce subarray_type_ref operator  * () { return sub; }
				nik_ce subarray_type_ptr operator -> () { return &sub; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// table (method):

/***********************************************************************************************************************/

// immutable:

	template<typename Base, typename SizeType, SizeType RowSize, SizeType ColSize>
	class table_cmethod : public Base
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

			nik_ces size_type row_length () { return RowSize; }
			nik_ces size_type col_length () { return ColSize; }

		public:

			nik_ce table_cmethod() : base{} { }

			template<typename T, auto N>
			nik_ce table_cmethod(const T (&a)[N]) : base{a} { }

			nik_ce ctype_ptr row_cbegin (size_ctype n) const { return base::citer(n * ColSize); }
			nik_ce ctype_ptr row_cend   (size_ctype n) const { return row_cbegin(n + 1); }
			nik_ce ctype_ptr row_clast  (size_ctype n) const { return row_cend(n) - 1; }

			nik_ce ctype_ptr operator [] (size_ctype n) const { return row_cbegin(n); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base, typename SizeType, SizeType RowSize, SizeType ColSize>
	class table_method : public table_cmethod<Base, SizeType, RowSize, ColSize>
	{
		public:

			using base		= table_cmethod<Base, SizeType, RowSize, ColSize>;

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

			nik_ce table_method() : base{} { }

			template<typename T, auto N>
			nik_ce table_method(const T (&a)[N]) : base{a} { }

			using base::operator [];

			nik_ce type_ptr row_begin (size_ctype n) { return base::iter(n * ColSize); }
			nik_ce type_ptr row_end   (size_ctype n) { return row_begin(n + 1); }
			nik_ce type_ptr row_last  (size_ctype n) { return row_end(n) - 1; }

			nik_ce type_ptr operator [] (size_ctype n) { return row_begin(n); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array:

/***********************************************************************************************************************/

// immutable:

	template<typename Type, typename SizeType>
	class carray	: public array_cmethod
			<
				image_trait < Type const* ,     Type const ,     Type >,
				image_trait < SizeType[1] , SizeType const , SizeType >,
				SizeType
			>
	{
		public:

			using init_trait	= image_trait < Type const* ,     Type const ,     Type >;
			using term_trait	= image_trait < SizeType[1] , SizeType const , SizeType >;
			using base		= array_cmethod<init_trait, term_trait, SizeType>;

			using type		= typename base::initial_type;
			using type_ptr		= typename base::initial_type_ptr;
			using type_cptr		= typename base::initial_type_cptr;
			using type_ref		= typename base::initial_type_ref;

			using ctype		= typename base::initial_ctype;
			using ctype_ptr		= typename base::initial_ctype_ptr;
			using ctype_cptr	= typename base::initial_ctype_cptr;
			using ctype_ref		= typename base::initial_ctype_ref;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		protected:

			nik_ce void assign(ctype_cptr i, size_ctype t)
			{
				 base:: initial = i;
				*base::terminal = t;
			}

		public:

			nik_ce carray() : base{} { }
			nik_ce carray(ctype_cptr i, size_ctype t) : base{} { assign(i, t); }

			template<auto N>
			nik_ce carray(const Type (&a)[N]) : carray{a, N} { }
	};

/***********************************************************************************************************************/

// string (literal):

	template<typename Type, typename SizeType>
	struct cstring : public carray<Type, SizeType>
	{
		using base		= carray<Type, SizeType>;

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

		nik_ce cstring() : base{} { }

		template<auto N>
		nik_ce cstring(const Type (&s)[N]) : base{s, N-1} { }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, SizeType Size>
	class array	: public array_method
			<
				image_trait <  Type[Size] ,     Type ,     Type >,
				image_trait < SizeType[1] , SizeType , SizeType >,
				SizeType, Size
			>
	{
		public:

			using init_trait	= image_trait<  Type[Size] ,     Type ,     Type >;
			using term_trait	= image_trait< SizeType[1] , SizeType , SizeType >;
			using base		= array_method<init_trait, term_trait, SizeType, Size>;

			using type		= typename base::initial_type;
			using type_ptr		= typename base::initial_type_ptr;
			using type_cptr		= typename base::initial_type_cptr;
			using type_ref		= typename base::initial_type_ref;

			using ctype		= typename base::initial_ctype;
			using ctype_ptr		= typename base::initial_ctype_ptr;
			using ctype_cptr	= typename base::initial_ctype_cptr;
			using ctype_ref		= typename base::initial_ctype_ref;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			nik_ce array() : base{} { }

			template<typename T, auto N>
			nik_ce array(const T (&a)[N]) : base{a} { }
	};

/***********************************************************************************************************************/

// unique:

	template<typename Type, typename SizeType, SizeType Size>
	class unique_array : public array<Type, SizeType, Size>
	{
		public:

			using base		= array<Type, SizeType, Size>;

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

			nik_ce unique_array() : base{} { }

			template<typename T, auto N>
			nik_ce unique_array(const T (&a)[N]) : base{} { push(a, a + N); }

			nik_ce void push(ctype_ref v) { if (base::omits(v)) { base::push(v); } }

			template<typename In, typename End>
			nik_ce void push(In in, End end) { while (in != end) { push(*in++); } }

			template<typename F, typename In, typename End>
			nik_ce void pushmap(F, In in, End end)
				{ while (in != end) { push(T_restore_T<F>::result(*in++)); } }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// table:

/***********************************************************************************************************************/

// immutable:

	template<typename Type, typename SizeType, SizeType RowSize, SizeType ColSize>
	class ctable : public table_cmethod<carray<Type, SizeType>, SizeType, RowSize, ColSize>
	{
		public:

			using subbase		= carray<Type, SizeType>;
			using base		= table_cmethod<subbase, SizeType, RowSize, ColSize>;

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

			nik_ce ctable() : base{} { }

			template<typename T, auto N>
			nik_ce ctable(const T (&a)[N]) : base{a} { }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, SizeType RowSize, SizeType ColSize>
	class table : public table_method<array<Type, SizeType, RowSize * ColSize>, SizeType, RowSize, ColSize>
	{
		public:

			using subbase		= array<Type, SizeType, RowSize * ColSize>;
			using base		= table_method<subbase, SizeType, RowSize, ColSize>;

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

			nik_ce table() : base{} { }

			template<typename T, auto N>
			nik_ce table(const T (&a)[N]) : base{a} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

