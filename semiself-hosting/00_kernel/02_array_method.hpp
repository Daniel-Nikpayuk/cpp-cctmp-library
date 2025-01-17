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

// array method:

	// these methods are intended for compile time, as such they avoid multiple inheritance.

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// container:

/***********************************************************************************************************************/

// resolve:

	// immutable:

		template<typename Container, template<typename> typename CMethod>
		using resolve_csubmethod = CMethod<typename Container::csubfacade_type>;

		template<typename Container, template<typename> typename CMethod>
		using resolve_cmethod = CMethod<typename Container::cfacade_type>;

	// mutable:

		template<typename Container, template<typename> typename Method>
		using resolve_submethod = Method<typename Container::subfacade_type>;

		template<typename Container, template<typename> typename Method>
		using resolve_method = Method<typename Container::facade_type>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// subarray:

/***********************************************************************************************************************/

// immutable:

	// assumptions:

		// base:: { type, citer_type, cderef_type, size_type }
		// base:: { cbegin() }

	template<typename Base>
	class subarray_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			using type			= typename base::type;
			using type_ptr			= typename base::type_ptr;
			using type_cptr			= typename base::type_cptr;
			using type_ref			= typename base::type_ref;

			using ctype			= typename base::ctype;
			using ctype_ptr			= typename base::ctype_ptr;
			using ctype_cptr		= typename base::ctype_cptr;
			using ctype_ref			= typename base::ctype_ref;

			using citer_type		= typename base::citer_type;
			using citer_ctype_ref		= typename base::citer_ctype_ref;

			using cderef_type		= typename base::cderef_type;
			using cderef_type_ptr		= typename base::cderef_type_ptr;
			using cderef_type_cptr		= typename base::cderef_type_cptr;
			using cderef_type_ref		= typename base::cderef_type_ref;

			using cderef_ctype		= typename base::cderef_ctype;
			using cderef_ctype_ptr		= typename base::cderef_ctype_ptr;
			using cderef_ctype_cptr		= typename base::cderef_ctype_cptr;
			using cderef_ctype_ref		= typename base::cderef_ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce subarray_cmethod_disjoint() : base{} { }
			nik_ce subarray_cmethod_disjoint(const facade & f) : base{f} { }

			// initial:

				nik_ce citer_type citer(size_ctype n) const { return base::cbegin() + n; }

				nik_ce size_type left_size(citer_ctype_ref i) const { return i - base::cbegin(); }

				nik_ce cderef_ctype_ref cat(size_ctype n) const { return *citer(n); }

				template<typename In, typename End>
				nik_ce bool equal(size_ctype n, In in, End end) const
				{
					for (citer_type out = citer(n); in != end; ++out, ++in)
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

				nik_ce cderef_ctype_ref operator [] (size_ctype n) const { return cat(n); }

			// terminal:

				nik_ce size_type max() const { return base::size() - 1; }

				nik_ce citer_type cend  () const { return citer(base::size()); }
				nik_ce citer_type clast () const { return cend() - 1; }

				nik_ce size_type right_size(citer_ctype_ref i) const { return cend() - i; }

				nik_ce bool is_empty  () const { return (base::size() == 0); }
				nik_ce bool not_empty () const { return (base::size() != 0); }

				nik_ce citer_type find(ctype_ref v) const
				{
					citer_type in = base::cbegin();

					while (in != cend()) { if (*in == v) { break; } else { ++in; } }

					return in;
				}

				nik_ce size_type left_find(ctype_ref v) const { return left_size(find(v)); }
				nik_ce size_type right_find(ctype_ref v) const { return right_size(find(v)); }
				nik_ce bool contains(ctype_ref v) const { return (find(v) != cend()); }
				nik_ce bool omits(ctype_ref v) const { return not contains(v); }
	};

/***********************************************************************************************************************/

// mutable:

	// assumptions:

		// base:: { iter_type, deref_type }
		// base:: { begin() }

	template<typename Base>
	class subarray_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			using type			= typename base::type;
			using type_ptr			= typename base::type_ptr;
			using type_cptr			= typename base::type_cptr;
			using type_ref			= typename base::type_ref;

			using ctype			= typename base::ctype;
			using ctype_ptr			= typename base::ctype_ptr;
			using ctype_cptr		= typename base::ctype_cptr;
			using ctype_ref			= typename base::ctype_ref;

			using iter_type			= typename base::iter_type;
			using iter_ctype_ref		= typename base::iter_ctype_ref;

			using deref_type		= typename base::deref_type;
			using deref_type_ptr		= typename base::deref_type_ptr;
			using deref_type_cptr		= typename base::deref_type_cptr;
			using deref_type_ref		= typename base::deref_type_ref;

			using deref_ctype		= typename base::deref_ctype;
			using deref_ctype_ptr		= typename base::deref_ctype_ptr;
			using deref_ctype_cptr		= typename base::deref_ctype_cptr;
			using deref_ctype_ref		= typename base::deref_ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce subarray_method_disjoint() : base{} { }
			nik_ce subarray_method_disjoint(const facade & f) : base{f} { }

			// immutable:

				using base::left_size;
				using base::right_size;
				using base::operator [];

			// mutable:

				nik_ce iter_type iter(size_ctype n) { return base::begin() + n; }

				nik_ce size_type left_size(iter_ctype_ref i) const { return i - base::begin(); }

				nik_ce iter_type end  () { return iter(base::size()); }
				nik_ce iter_type last () { return end() - 1; }

				nik_ce size_type right_size(iter_ctype_ref i) const { return end() - i; }

				nik_ce deref_type_ref at(size_ctype n) { return *iter(n); }

				nik_ce deref_type_ref operator [] (size_ctype n) { return at(n); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array:

/***********************************************************************************************************************/

// immutable:

	// assumptions:

		// base:: { size() }

	template<typename Base>
	class array_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			using type			= typename base::type;
			using type_ptr			= typename base::type_ptr;
			using type_cptr			= typename base::type_cptr;
			using type_ref			= typename base::type_ref;

			using ctype			= typename base::ctype;
			using ctype_ptr			= typename base::ctype_ptr;
			using ctype_cptr		= typename base::ctype_cptr;
			using ctype_ref			= typename base::ctype_ref;

			using citer_type		= typename base::citer_type;
			using citer_ctype_ref		= typename base::citer_ctype_ref;

			using cderef_type		= typename base::cderef_type;
			using cderef_type_ptr		= typename base::cderef_type_ptr;
			using cderef_type_cptr		= typename base::cderef_type_cptr;
			using cderef_type_ref		= typename base::cderef_type_ref;

			using cderef_ctype		= typename base::cderef_ctype;
			using cderef_ctype_ptr		= typename base::cderef_ctype_ptr;
			using cderef_ctype_cptr		= typename base::cderef_ctype_cptr;
			using cderef_ctype_ref		= typename base::cderef_ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce array_cmethod_disjoint() : base{} { }
			nik_ce array_cmethod_disjoint(const facade & f) : base{f} { }

			// initial:

				nik_ce citer_type origin() const { return base::cbegin(); }
	};

/***********************************************************************************************************************/

// mutable:

	// assumptions:

		// base:: { iter_type, deref_type }
		// base:: { length(), begin(), set_size(size_ctype) }

	template<typename Base>
	class array_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			using type			= typename base::type;
			using type_ptr			= typename base::type_ptr;
			using type_cptr			= typename base::type_cptr;
			using type_ref			= typename base::type_ref;

			using ctype			= typename base::ctype;
			using ctype_ptr			= typename base::ctype_ptr;
			using ctype_cptr		= typename base::ctype_cptr;
			using ctype_ref			= typename base::ctype_ref;

			using iter_type			= typename base::iter_type;
			using iter_ctype_ref		= typename base::iter_ctype_ref;

			using deref_type		= typename base::deref_type;
			using deref_type_ptr		= typename base::deref_type_ptr;
			using deref_type_cptr		= typename base::deref_type_cptr;
			using deref_type_ref		= typename base::deref_type_ref;

			using deref_ctype		= typename base::deref_ctype;
			using deref_ctype_ptr		= typename base::deref_ctype_ptr;
			using deref_ctype_cptr		= typename base::deref_ctype_cptr;
			using deref_ctype_ref		= typename base::deref_ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		protected:

			template<typename T, auto N>
			nik_ce void assign(const T (&a)[N])
			{
				clear();
				push(a, a + N);
			}

		public:

			nik_ce array_method_disjoint() : base{} { }
			nik_ce array_method_disjoint(const facade & f) : base{f} { }

			template<typename T, auto N>
			nik_ce array_method_disjoint(const T (&a)[N]) : base{} { assign(a); }

			// mutable:

				nik_ce size_type capacity() const { return base::length() - base::size(); }

				nik_ce bool has_capacity   (size_ctype n) const { return (n <= capacity()); }
				nik_ce bool lacks_capacity (size_ctype n) const { return not has_capacity(n); }

				nik_ce bool is_full  () const { return lacks_capacity(1); }
				nik_ce bool not_full () const { return has_capacity(1); }

				nik_ce void clear() { base::set_size(0); }
				nik_ce void fullsize() { base::set_size(base::length()); }
				nik_ce void upsize(size_ctype n = 1) { base::set_size(base::size() + n); }
				nik_ce void downsize(size_ctype n = 1) { base::set_size(base::size() - n); }

				nik_ce size_type expand(size_ctype n)
					{ size_ctype s = base::size(); base::set_size(s + n); return s; }

				nik_ce void push(ctype_ref v) { *base::iter(expand(1)) = v; }

				nik_ce deref_type pop() { downsize(); return *base::end(); }

				template<typename In, typename End>
				nik_ce void push(In in, End end) { while (in != end) { push(*in++); } }

				template<typename F, typename In, typename End>
				nik_ce void pushmap(F, In in, End end)
					{ while (in != end) { push(T_restore_T<F>::result(*in++)); } }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// unique:

/***********************************************************************************************************************/

// mutable:

	template<typename Facade>
	class unique_method : public array_method<Facade>
	{
		public:

			using base			= array_method<Facade>;

			using type			= typename base::type;
			using type_ptr			= typename base::type_ptr;
			using type_cptr			= typename base::type_cptr;
			using type_ref			= typename base::type_ref;

			using ctype			= typename base::ctype;
			using ctype_ptr			= typename base::ctype_ptr;
			using ctype_cptr		= typename base::ctype_cptr;
			using ctype_ref			= typename base::ctype_ref;

			using iter_type			= typename base::iter_type;
			using iter_ctype_ref		= typename base::iter_ctype_ref;

			using deref_type		= typename base::deref_type;
			using deref_type_ptr		= typename base::deref_type_ptr;
			using deref_type_cptr		= typename base::deref_type_cptr;
			using deref_type_ref		= typename base::deref_type_ref;

			using deref_ctype		= typename base::deref_ctype;
			using deref_ctype_ptr		= typename base::deref_ctype_ptr;
			using deref_ctype_cptr		= typename base::deref_ctype_cptr;
			using deref_ctype_ref		= typename base::deref_ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		protected:

			template<typename T, auto N>
			nik_ce void assign(const T (&a)[N])
			{
				base::clear();
				push(a, a + N);
			}

		public:

			nik_ce unique_method() : base{} { }
			nik_ce unique_method(const Facade & f) : base{f} { }

			template<typename T, auto N>
			nik_ce unique_method(const T (&a)[N]) : base{} { assign(a); }

			// mutable:

				nik_ce size_type left_find_push(ctype_ref v)
				{
					size_ctype pos = base::left_find(v);

					if (pos == base::size()) { base::push(v); }

					return pos;
				}

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

	template<typename Facade, typename Facade::size_type RowSize, typename Facade::size_type ColSize>
	class table_cmethod : public array_cmethod<Facade>
	{
		public:

			using base			= array_cmethod<Facade>;

			using type			= typename base::type;
			using type_ptr			= typename base::type_ptr;
			using type_cptr			= typename base::type_cptr;
			using type_ref			= typename base::type_ref;

			using ctype			= typename base::ctype;
			using ctype_ptr			= typename base::ctype_ptr;
			using ctype_cptr		= typename base::ctype_cptr;
			using ctype_ref			= typename base::ctype_ref;

			using citer_type		= typename base::citer_type;
			using citer_ctype_ref		= typename base::citer_ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ces size_type row_length () { return RowSize; }
			nik_ces size_type col_length () { return ColSize; }

		public:

			nik_ce table_cmethod() : base{} { }
			nik_ce table_cmethod(const Facade & f) : base{f} { }

			nik_ce citer_type row_cbegin (size_ctype n) const { return base::citer(n * ColSize); }
			nik_ce citer_type row_cend   (size_ctype n) const { return row_cbegin(n + 1); }
			nik_ce citer_type row_clast  (size_ctype n) const { return row_cend(n) - 1; }

			nik_ce citer_type operator [] (size_ctype n) const { return row_cbegin(n); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Facade, typename Facade::size_type RowSize, typename Facade::size_type ColSize>
	class table_method : public array_method<Facade>
	{
		public:

			using base			= array_method<Facade>;

			using type			= typename base::type;
			using type_ptr			= typename base::type_ptr;
			using type_cptr			= typename base::type_cptr;
			using type_ref			= typename base::type_ref;

			using ctype			= typename base::ctype;
			using ctype_ptr			= typename base::ctype_ptr;
			using ctype_cptr		= typename base::ctype_cptr;
			using ctype_ref			= typename base::ctype_ref;

			using citer_type		= typename base::citer_type;
			using citer_ctype_ref		= typename base::citer_ctype_ref;

			using iter_type			= typename base::iter_type;
			using iter_ctype_ref		= typename base::iter_ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ces size_type row_length () { return RowSize; }
			nik_ces size_type col_length () { return ColSize; }

		public:

			nik_ce table_method() : base{} { }
			nik_ce table_method(const Facade & f) : base{f} { }

			template<typename T, auto N>
			nik_ce table_method(const T (&a)[N]) : base::assign(a) { }

			nik_ce citer_type row_cbegin (size_ctype n) const { return base::citer(n * ColSize); }
			nik_ce citer_type row_cend   (size_ctype n) const { return row_cbegin(n + 1); }
			nik_ce citer_type row_clast  (size_ctype n) const { return row_cend(n) - 1; }

			nik_ce  iter_type row_begin  (size_ctype n)       { return base::iter(n * ColSize); }
			nik_ce  iter_type row_end    (size_ctype n)       { return row_begin(n + 1); }
			nik_ce  iter_type row_last   (size_ctype n)       { return row_end(n) - 1; }

			nik_ce citer_type operator [] (size_ctype n) const { return row_cbegin(n); }
			nik_ce  iter_type operator [] (size_ctype n)       { return row_begin(n); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

