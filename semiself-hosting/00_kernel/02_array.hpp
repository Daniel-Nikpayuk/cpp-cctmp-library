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

// array:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// model (base):

/***********************************************************************************************************************/

// immutable:

	template<typename Type, typename SizeType>
	class array_cmodel
	{
		public:

			using type			= typename alias<Type>::type;
			using type_ptr			= typename alias<Type>::type_ptr;
			using type_cptr			= typename alias<Type>::type_cptr;
			using type_ref			= typename alias<Type>::type_ref;

			using ctype			= typename alias<Type>::ctype;
			using ctype_ptr			= typename alias<Type>::ctype_ptr;
			using ctype_cptr		= typename alias<Type>::ctype_cptr;
			using ctype_ref			= typename alias<Type>::ctype_ref;

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

			using size_type			= typename alias<SizeType>::type;
			using size_ctype		= typename alias<SizeType>::ctype;

		protected:

			ctype_ptr  initial; // compile time compatible.
			size_type terminal; // compile time compatible.

		protected:

			nik_ce void assign(ctype_cptr i, size_ctype t) // inheritance convenience.
			{
				 initial = i;
				terminal = t;
			}

		public:

			nik_ce array_cmodel() : initial{}, terminal{} { }

			// initial:

				nik_ce citer_type cbegin() const { return initial; }

			// terminal:

				nik_ce size_type size() const { return terminal; }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, SizeType Size>
	class array_model
	{
		public:

			using type			= typename alias<Type>::type;
			using type_ptr			= typename alias<Type>::type_ptr;
			using type_cptr			= typename alias<Type>::type_cptr;
			using type_ref			= typename alias<Type>::type_ref;

			using ctype			= typename alias<Type>::ctype;
			using ctype_ptr			= typename alias<Type>::ctype_ptr;
			using ctype_cptr		= typename alias<Type>::ctype_cptr;
			using ctype_ref			= typename alias<Type>::ctype_ref;

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

			using size_type			= typename alias<SizeType>::type;
			using size_ctype		= typename alias<SizeType>::ctype;

		public:

			nik_ces size_type length() { return Size; }

		protected:

			type initial[Size]; // compile time compatible.
			size_type terminal; // compile time compatible.

		public:

			nik_ce array_model() : initial{}, terminal{} { }

			// initial:

				nik_ce citer_type cbegin() const { return initial; }
				nik_ce iter_type begin() { return initial; }

			// terminal:

				nik_ce size_type size() const { return terminal; }
				nik_ce void set_size(size_ctype n) { terminal = n; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array:

/***********************************************************************************************************************/

// immutable:

	template<typename Type, typename SizeType>
	class carray : public array_cmethod<array_cmodel<Type, SizeType>>
	{
		public:

			using sub_base		= array_cmodel<Type, SizeType>;
			using base		= array_cmethod<sub_base>;

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

			nik_ce carray() : base{} { }
			nik_ce carray(ctype_cptr i, size_ctype t) : base{} { base::assign(i, t); }

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
	class array : public array_method<array_model<Type, SizeType, Size>>
	{
		public:

			using sub_base		= array_model<Type, SizeType, Size>;
			using base		= array_method<sub_base>;

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

