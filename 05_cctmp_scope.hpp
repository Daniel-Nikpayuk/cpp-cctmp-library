/************************************************************************************************************************
**
** Copyright 2022-2023 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// scope:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// selector:

/***********************************************************************************************************************/

// immutable:

	template<typename Type, typename SizeType>
	class cselector
	{
		public:

			using type			= Type;
			using type_ptr			= type*;
			using type_ref			= type&;
			using type_cptr			= type_ptr const;

			using ctype			= type const;
			using ctype_ptr			= ctype*;
			using ctype_cptr		= ctype_ptr const;
			using ctype_ref			= ctype&;

			using size_type			= SizeType;
			using csize_type		= size_type const;

		protected:

			nik_ces auto _find_		= _subarray_match_<>;
			nik_ces auto _find_same_	= _subarray_match_same_<>;

			ctype_ptr start;
			ctype_ptr finish;

		public:

			nik_ce cselector() : start{}, finish{} { }
			nik_ce cselector(ctype_cptr s, ctype_cptr f) : start{s}, finish{f} { }
			nik_ce cselector(const cselector *s) : start{s->start}, finish{s->finish} { }

			nik_ce auto cselect(csize_type lnum, csize_type rnum) const
				{ return cselector{start + lnum, finish - rnum}; }
			nik_ce auto cselect() const { return cselect(0, 0); } // for move semantics and inheritance.

			nik_ce auto size      () const { return (finish - start); }
			nik_ce bool is_empty  () const { return (start == finish); }
			nik_ce bool not_empty () const { return (start != finish); }

			nik_ce auto left_size  (ctype_cptr i) const { return i - start; }
			nik_ce auto right_size (ctype_cptr i) const { return finish - i; }

			nik_ce ctype_ptr cbegin () const { return start; }
			nik_ce ctype_ptr clast  () const { return finish - 1; }
			nik_ce ctype_ptr cend   () const { return finish; }

			nik_ce void clear() { finish = start; }
			nik_ce void upleft(csize_type num = 1) { start += num; }
			nik_ce void downleft(csize_type num = 1) { start -= num; }
			nik_ce void upright(csize_type num = 1) { finish += num; }
			nik_ce void downright(csize_type num = 1) { finish -= num; }

			nik_ce const cselector & find(ctype_ref v)
				{ start = apply<_find_>(start, finish, v); return *this; }

			template<typename T>
			nik_ce const cselector & find(const T & v)
				{ start = apply<_find_same_>(start, finish, v); return *this; }

			nik_ce auto contains(ctype_ref v) const { cselector s{*this}; return s.find(v); }

			template<typename T>
			nik_ce auto contains(const T & v) const
				{ cselector s{*this}; return s.template find<T const&>(v); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType>
	class selector : public cselector<Type, SizeType>
	{	
		protected:

			using base		= cselector<Type, SizeType>;

		public:

			using type		= typename base::type;
			using type_ptr		= typename base::type_ptr;
			using type_ref		= typename base::type_ref;
			using type_cptr		= typename base::type_cptr;

			using ctype		= typename base::ctype;
			using ctype_ptr		= typename base::ctype_ptr;
			using ctype_cptr	= typename base::ctype_cptr;
			using ctype_ref		= typename base::ctype_ref;

			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

			nik_ce selector() : base{} { }
			nik_ce selector(type_cptr s, type_cptr f) : base{(ctype_cptr) s, (ctype_cptr) f} { }
			nik_ce selector(const selector *s) : base{s} { }

			nik_ce auto select(csize_type lnum, csize_type rnum) const
				{ return selector{base::start + lnum, base::finish - rnum}; }
			nik_ce auto select() const { return select(0, 0); } // for move semantics and inheritance.

			nik_ce type_ptr begin () { return (type_ptr) base::cbegin(); }
			nik_ce type_ptr last  () { return (type_ptr) base::clast(); }
			nik_ce type_ptr end   () { return (type_ptr) base::cend(); }

			nik_ce void pushleft(ctype_ref v) { *begin() = v; base::downleft(); }
			nik_ce void pushright(ctype_ref v) { *end() = v; base::upright(); }

			nik_ce type popleft() { auto v = *begin(); base::upleft(); return v; }
			nik_ce type popright() { auto v = *end(); base::downright(); return v; }

			nik_ce selector & find(ctype_ref v)
				{ base::start = apply<base::_find_>(base::start, base::finish, v); return *this; }

			template<typename T>
			nik_ce selector & find(const T & v)
				{ base::start = apply<base::_find_same_>(base::start, base::finish, v); return *this; }

			nik_ce auto contains(ctype_ref v) const { selector s{*this}; return s.find(v); }

			template<typename T>
			nik_ce auto contains(const T & v) const
				{ selector s{*this}; return s.template find<T const&>(v); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// iterator:

/***********************************************************************************************************************/

// immutable:

	template<typename Type, typename SizeType>
	class citerator : public cselector<Type, SizeType>
	{
		protected:

			using base		= cselector<Type, SizeType>;

		public:

			using type		= typename base::type;
			using type_ptr		= typename base::type_ptr;
			using type_ref		= typename base::type_ref;
			using type_cptr		= typename base::type_cptr;

			using ctype		= typename base::ctype;
			using ctype_ptr		= typename base::ctype_ptr;
			using ctype_cptr	= typename base::ctype_cptr;
			using ctype_ref		= typename base::ctype_ref;

			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

		protected:

			ctype_ptr current;

		public:

			nik_ce citerator() : base{}, current{} { }
			nik_ce citerator(ctype_cptr s, ctype_cptr f) : base{s, f}, current{s} { }
			nik_ce citerator(ctype_cptr s, ctype_cptr f, ctype_cptr c) : base{s, f}, current{c} { }
			nik_ce citerator(const citerator *i) : base{i}, current{i->current} { }

			nik_ce auto citerate(csize_type lnum, csize_type rnum) const
				{ return citerator{base::start + lnum, base::finish - rnum}; }
			nik_ce auto citerate() const { return citerate(0, 0); } // for move semantics / inheritance.

			nik_ce auto left_cselect(csize_type lnum, csize_type rnum) const
				{ return cselector{base::start + lnum, current - rnum}; }
			nik_ce auto left_cselect() const { return left_cselect(0, 0); }

			nik_ce auto right_cselect(csize_type lnum, csize_type rnum) const
				{ return cselector{current + lnum, base::finish - rnum}; }
			nik_ce auto right_cselect() const { return right_cselect(0, 0); }

			nik_ce auto left_citerate(csize_type lnum, csize_type rnum) const
				{ return citerator{base::start + lnum, current - rnum}; }
			nik_ce auto left_citerate() const { return left_citerate(0, 0); }

			nik_ce auto right_citerate(csize_type lnum, csize_type rnum) const
				{ return citerator{current + lnum, base::finish - rnum}; }
			nik_ce auto right_citerate() const { return right_citerate(0, 0); }

			nik_ce bool is_begin   () const { return (current == base::start); }
			nik_ce bool not_begin  () const { return (current != base::start); }

			nik_ce bool is_end     () const { return (current == base::finish); }
			nik_ce bool not_end    () const { return (current != base::finish); }

			nik_ce auto left_size  () const { return base::left_size(current); }
			nik_ce auto right_size () const { return base::right_size(current); }

			nik_ce ctype_ptr ccurrent() const { return current; }

			nik_ce const citerator & find(ctype_ref v)
				{ current = apply<base::_find_>(base::start, base::finish, v); return *this; }

			template<typename T>
			nik_ce const citerator & find(const T & v)
				{ current = apply<base::_find_same_>(base::start, base::finish, v); return *this; }

			nik_ce const citerator & left_find(ctype_ref v)
				{ current = apply<base::_find_>(base::start, current, v); return *this; }

			template<typename T>
			nik_ce const citerator & left_find(const T & v)
				{ current = apply<base::_find_same_>(base::start, current, v); return *this; }

			nik_ce const citerator & right_find(ctype_ref v)
				{ current = apply<base::_find_>(current, base::finish, v); return *this; }

			template<typename T>
			nik_ce const citerator & right_find(const T & v)
				{ current = apply<base::_find_same_>(current, base::finish, v); return *this; }

			nik_ce auto contains(ctype_ref v) const { citerator i{*this}; return i.find(v); }

			template<typename T>
			nik_ce auto contains(const T & v) const
				{ citerator i{*this}; return i.template find<T const&>(v); }

			nik_ce auto left_contains(ctype_ref v) const { citerator i{*this}; return i.left_find(v); }

			template<typename T>
			nik_ce auto left_contains(const T & v) const
				{ citerator i{*this}; return i.template left_find<T const&>(v); }

			nik_ce auto right_contains(ctype_ref v) const { citerator i{*this}; return i.right_find(v); }

			template<typename T>
			nik_ce auto right_contains(const T & v) const
				{ citerator i{*this}; return i.template right_find<T const&>(v); }

			nik_ce ctype_ptr operator -> () const { return  current; }
			nik_ce ctype_ref operator  * () const { return *current; }

			nik_ce citerator & operator -= (csize_type num) { current -= num; return *this; }
			nik_ce citerator & operator += (csize_type num) { current += num; return *this; }
			nik_ce citerator & operator -- () { --current; return *this; }
			nik_ce citerator & operator ++ () { ++current; return *this; }

			nik_ce citerator operator  - (csize_type num) { citerator i{*this}; return i -= num; }
			nik_ce citerator operator  + (csize_type num) { citerator i{*this}; return i += num; }
			nik_ce citerator operator -- (int) { citerator i{*this}; --current; return i; }
			nik_ce citerator operator ++ (int) { citerator i{*this}; ++current; return i; }

			nik_ce ctype_ptr cptr_at(csize_type pos) const { return base::start + pos; }
			nik_ce ctype_ref cref_at(csize_type pos) const { return *cptr_at(pos); }

			nik_ce ctype_ref cvalue(ctype_ref v) const { return (current != 0) ? *current : v; }

			nik_ce void pivot(csize_type pos) { current = cptr_at(pos); }

			nik_ce void step(csize_type pos)
			{
				if (pos < base::size()) pivot(pos);
				else current = base::finish;
			}

			nik_ce void backward(csize_type num = 1)
			{
				if (num < left_size()) operator -= (num);
				else current = base::start;
			}

			nik_ce void forward(csize_type num = 1)
			{
				if (num < right_size()) operator += (num);
				else current = base::finish;
			}
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType>
	class iterator : public citerator<Type, SizeType>
	{
		protected:

			using base			= citerator<Type, SizeType>;

		public:

			using type			= typename base::type;
			using type_ptr			= typename base::type_ptr;
			using type_ref			= typename base::type_ref;
			using type_cptr			= typename base::type_cptr;

			using ctype			= typename base::ctype;
			using ctype_ptr			= typename base::ctype_ptr;
			using ctype_cptr		= typename base::ctype_cptr;
			using ctype_ref			= typename base::ctype_ref;

			using size_type			= typename base::size_type;
			using csize_type		= typename base::csize_type;

			using cselector_type		= typename base::base;
			using cselector_ctype		= cselector_type const;
			using cselector_ctype_ptr	= cselector_ctype*;
			using cselector_ctype_cptr	= cselector_ctype_ptr const;

			nik_ce iterator() : base{} { }
			nik_ce iterator(type_cptr s, type_cptr f) : base{(ctype_ptr) s, (ctype_ptr) f} { }
			nik_ce iterator(type_cptr s, type_cptr f, type_cptr c) :
				base{(ctype_ptr) s, (ctype_ptr) f, (ctype_ptr) c} { }
			nik_ce iterator(const iterator *i) : base{i} { }

			nik_ce auto iterate(csize_type lnum, csize_type rnum) const
				{ return iterator{base::start + lnum, base::finish - rnum}; }
			nik_ce auto iterate() const { return iterate(0, 0); } // for move semantics / inheritance.

			nik_ce auto left_select(csize_type lnum, csize_type rnum) const
				{ return selector{base::start + lnum, base::current - rnum}; }
			nik_ce auto left_select() const { return left_select(0, 0); }

			nik_ce auto right_select(csize_type lnum, csize_type rnum) const
				{ return selector{base::current + lnum, base::finish - rnum}; }
			nik_ce auto right_select() const { return right_select(0, 0); }

			nik_ce auto left_iterate(csize_type lnum, csize_type rnum) const
				{ return iterator{base::start + lnum, base::current - rnum}; }
			nik_ce auto left_iterate() const { return left_iterate(0, 0); }

			nik_ce auto right_iterate(csize_type lnum, csize_type rnum) const
				{ return iterator{base::current + lnum, base::finish - rnum}; }
			nik_ce auto right_iterate() const { return right_iterate(0, 0); }

			nik_ce iterator & find(ctype_ref v)
				{ base::current = apply<base::_find_>(base::start, base::finish, v); return *this; }

			template<typename T>
			nik_ce iterator & find(const T & v)
				{ base::current = apply<base::_find_same_>(base::start, base::finish, v); return *this; }

			nik_ce iterator & left_find(ctype_ref v)
				{ base::current = apply<base::_find_>(base::start, base::current, v); return *this; }

			template<typename T>
			nik_ce iterator & left_find(const T & v)
				{ base::current = apply<base::_find_same_>(base::start, base::current, v); return *this; }

			nik_ce iterator & right_find(ctype_ref v)
				{ base::current = apply<base::_find_>(base::current, base::finish, v); return *this; }

			template<typename T>
			nik_ce iterator & right_find(const T & v)
				{ base::current = apply<base::_find_same_>(base::current, base::finish, v); return *this; }

			nik_ce auto contains(ctype_ref v) const { iterator i{*this}; return i.find(v); }

			template<typename T>
			nik_ce auto contains(const T & v) const { iterator i{*this}; return i.template find<T const&>(v); }

			nik_ce auto left_contains(ctype_ref v) const { iterator i{*this}; return i.left_find(v); }

			template<typename T>
			nik_ce auto left_contains(const T & v) const
				{ iterator i{*this}; return i.template left_find<T const&>(v); }

			nik_ce auto right_contains(ctype_ref v) const { iterator i{*this}; return i.right_find(v); }

			template<typename T>
			nik_ce auto right_contains(const T & v) const
				{ iterator i{*this}; return i.template right_find<T const&>(v); }

			nik_ce type_ptr operator -> () { return (type_ptr) base::operator -> (); }
			nik_ce type_ref operator  * () { return (type_ref) base::operator  * (); }

			nik_ce iterator & operator -= (csize_type num) { base::operator -= (num); return *this; }
			nik_ce iterator & operator += (csize_type num) { base::operator += (num); return *this; }
			nik_ce iterator & operator -- () { base::operator -- (); return *this; }
			nik_ce iterator & operator ++ () { base::operator ++ (); return *this; }

			nik_ce iterator operator  - (csize_type num) { iterator i{*this}; return i -= num; }
			nik_ce iterator operator  + (csize_type num) { iterator i{*this}; return i += num; }
			nik_ce iterator operator -- (int) { iterator i{*this}; base::operator -- (); return i; }
			nik_ce iterator operator ++ (int) { iterator i{*this}; base::operator ++ (); return i; }

			nik_ce type_ptr ptr_at(csize_type pos) { return (type_ptr) base::cptr_at(pos); }
			nik_ce type_ref ref_at(csize_type pos) { return (type_ref) base::cref_at(pos); }

			nik_ce type_ref value(type_ref v) { return (type_ref) base::cvalue((ctype_ref) v); }

			nik_ce type_ptr begin   () { return (type_ptr) base::cbegin(); }
			nik_ce type_ptr current () { return (type_ptr) base::current; }
			nik_ce type_ptr last    () { return (type_ptr) base::clast(); }
			nik_ce type_ptr end     () { return (type_ptr) base::cend(); }

			nik_ce void pushleft(ctype_ref v) { *begin() = v; base::downleft(); }
			nik_ce void pushright(ctype_ref v) { *end() = v; base::upright(); }

			nik_ce type popleft() { auto v = *begin(); base::upleft(); return v; }
			nik_ce type popright() { auto v = *end(); base::downright(); return v; }

			nik_ce void copy(cselector_ctype_cptr s)
			{
				for (auto k = s->cbegin(); base::not_end() && k != s->cend(); ++k)
				{
					if (base::is_end()) break;

					operator  * () = *k;
					operator ++ ();
				}
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// literal:

/***********************************************************************************************************************/

// interface:

	template<typename Type, typename SizeType>
	struct literal
	{
		using citerator_type	= citerator<Type, SizeType>;
		using cselector_type	= cselector<Type, SizeType>;

		using type		= typename citerator_type::type;
		using ctype		= typename citerator_type::ctype;
		using ctype_ptr		= typename citerator_type::ctype_ptr;
		using ctype_cptr	= typename citerator_type::ctype_cptr;
		using ctype_ref		= typename citerator_type::ctype_ref;

		using size_type		= SizeType;
		using csize_type	= size_type const;

		ctype_ptr start;
		ctype_ptr finish;

		nik_ces ctype empty[] = { };

		template<auto N>
		nik_ce literal(const Type (&s)[N]) : start{s}, finish{s + N} { }

		nik_ce literal() : start{empty}, finish{empty} { }
		nik_ce literal(ctype_cptr s, ctype_cptr f) : start{s}, finish{f} { }

		nik_ce auto size() const { return finish - start; }

		nik_ce ctype_ptr cbegin () const { return start; }
		nik_ce ctype_ptr clast  () const { return finish - 1; }
		nik_ce ctype_ptr cend   () const { return finish; }

		nik_ce ctype_ref operator [] (csize_type pos) const { return start[pos]; }

		nik_ce bool operator == (const literal<Type, SizeType> & l) const
			{ return apply<_subarray_same_<>>(*this, l); }

		nik_ce bool operator != (const literal<Type, SizeType> & l) const
			{ return !apply<_subarray_same_<>>(*this, l); }

		nik_ce cselector_type cselect(csize_type lnum, csize_type rnum) const
			{ return cselector_type{start + lnum, finish - rnum}; }
		nik_ce cselector_type cselect() const { return cselect(0, 0); }

		nik_ce citerator_type citerate(csize_type lnum, csize_type rnum) const
			{ return citerator_type{start + lnum, finish - rnum}; }
		nik_ce citerator_type citerate() const { return citerate(0, 0); }
	};

/***********************************************************************************************************************/

// string:

	template<typename Type, typename SizeType>
	struct string_literal : public literal<Type, SizeType>
	{
		using base		= literal<Type, SizeType>;

		using citerator_type	= typename base::citerator_type;
		using cselector_type	= typename base::cselector_type;

		using type		= typename base::type;
		using ctype		= typename base::ctype;
		using ctype_ptr		= typename base::ctype_ptr;
		using ctype_cptr	= typename base::ctype_cptr;
		using ctype_ref		= typename base::ctype_ref;

		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		template<auto N>
		nik_ce string_literal(const Type (&s)[N]) : base{s, s + (N-1)} { }

		nik_ce string_literal() : base{} { } // maybe.

		nik_ce bool operator == (const string_literal<Type, SizeType> & s) const
			{ return apply<_subarray_same_<>>(*this, s); }

		nik_ce bool operator != (const string_literal<Type, SizeType> & s) const
			{ return !apply<_subarray_same_<>>(*this, s); }
	};

	using strlit_type		= string_literal<>;
	using cstrlit_type		= strlit_type const;
	using cstrlit_ref		= cstrlit_type&;
	nik_ce auto U_strlit_type	= U_store_T<strlit_type>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

