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

// grammar:

	// convention: classes/structs that begin with "T_" are meant
	// to be associated with the auto ~ typename equivalence.

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// store:

/***********************************************************************************************************************/

// T -> U:

	template<typename T> nik_ce void store(T) { }

	template<typename T> nik_ce auto U_store_T      = store<T*>;
	template<typename T> nik_ce auto U_store_T<T&>  = store<T&>;
	template<typename T> nik_ce auto U_store_T<T&&> = store<T&&>;

// U -> T:

	template<typename T> struct store_match                     { using result = T; };
	template<typename T> struct store_match<void(*const&)(T&&)> { using result = T&&; };
	template<typename T> struct store_match<void(*const&)(T&)>  { using result = T&; };
	template<typename T> struct store_match<void(*const&)(T*)>  { using result = T; };

	template<typename T>
	using T_restore_T = typename store_match<T const&>::result;

	template<typename T>
	nik_ce auto U_restore_T = U_store_T<T_restore_T<T>>;

	template<auto U>
	using T_store_U = T_restore_T<decltype(U)>;

/***********************************************************************************************************************/

// constant:

	// void:

		nik_ce auto U_void = U_store_T<void>;

	// builtin:

		nik_ce auto U_bool = U_store_T<bool>;
		nik_ce auto U_char = U_store_T<char>;

	// unsigned:

		nik_ce auto U_unsigned_char			= U_store_T < unsigned char      >;
		nik_ce auto U_unsigned_short			= U_store_T < unsigned short     >;
		nik_ce auto U_unsigned_int			= U_store_T < unsigned int       >;
		nik_ce auto U_unsigned_long			= U_store_T < unsigned long      >;
		nik_ce auto U_unsigned_long_long		= U_store_T < unsigned long long >;

	// signed:

		nik_ce auto U_signed_char			= U_store_T < signed char      >;
		nik_ce auto U_signed_short			= U_store_T < signed short     >;
		nik_ce auto U_signed_int			= U_store_T < signed int       >;
		nik_ce auto U_signed_long			= U_store_T < signed long      >;
		nik_ce auto U_signed_long_long			= U_store_T < signed long long >;

	// auto:

		nik_ce auto U_auto_bool				= U_store_T < decltype( false ) >;
		nik_ce auto U_auto_char				= U_store_T < decltype(  '\0' ) >;
		nik_ce auto U_auto_int				= U_store_T < decltype(    0  ) >;
		nik_ce auto U_auto_float			= U_store_T < decltype(  0.0  ) >;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// packs:

/***********************************************************************************************************************/

// auto:

	template<auto...> struct T_pack_Vs; // intentionally undefined.
	using T_null_Vs = T_pack_Vs<>;

	template<auto... Vs>
	nik_ce auto U_pack_Vs = store<T_pack_Vs<Vs...>*>;
	nik_ce auto U_null_Vs = U_pack_Vs<>;

// typename:

	template<typename... Ts>
	nik_ce auto U_pack_Ts = U_pack_Vs<U_store_T<Ts>...>;
	nik_ce auto U_null_Ts = U_null_Vs;

// auto template:

	template<template<auto...> typename> struct T_store_B { };

	template<template<auto...> typename B>
	nik_ce auto U_store_B = U_store_T<T_store_B<B>>;

	template<template<auto...> typename... Bs>
	nik_ce auto U_pack_Bs = U_pack_Vs<U_store_B<Bs>...>;
	nik_ce auto U_null_Bs = U_null_Vs;

	nik_ce auto H_id = U_store_B<T_pack_Vs>;

// typename template:

	template<template<typename...> typename> struct T_store_A { };

	template<template<typename...> typename A>
	nik_ce auto U_store_A = U_store_T<T_store_A<A>>;

	template<template<typename...> typename... As>
	nik_ce auto U_pack_As = U_pack_Vs<U_store_A<As>...>;
	nik_ce auto U_null_As = U_null_Vs;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// static:

/***********************************************************************************************************************/

// callable:

	template<auto Callable>
	struct T_static_callable
	{
		nik_ces auto value = Callable();
		using type         = decltype(value);

	}; template<auto Callable>
		nik_ce auto _static_callable_ = U_store_T<T_static_callable<Callable>>;

/***********************************************************************************************************************/

// member value:

	template<typename T>
	nik_ce auto & member_value_T = T::value;

	template<auto U>
	nik_ce auto & member_value_U = member_value_T<T_store_U<U>>;

// member type:

	template<typename T>
	using member_type_T = typename T::type;

	template<auto U>
	using member_type_U = member_type_T<T_store_U<U>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// types:

/***********************************************************************************************************************/

// subnumbers:

	// bool:

		using global_bool_type		= bool;
		using gbool_type		= global_bool_type;
		using gbool_ctype		= global_bool_type const;
		nik_ce auto U_gbool_type	= U_store_T<gbool_type>;
		nik_ce auto U_gbool_ctype	= U_store_T<gbool_ctype>;

	// [0-10]:

		using global_key_type		= unsigned char;
		using gkey_type			= global_key_type;
		using gkey_ctype		= global_key_type const;
		nik_ce auto U_gkey_type		= U_store_T<gkey_type>;
		nik_ce auto U_gkey_ctype	= U_store_T<gkey_ctype>;

		nik_ce gkey_type _zero		=   0;
		nik_ce gkey_type _one		=   1;
		nik_ce gkey_type _two		=   2;
		nik_ce gkey_type _three		=   3;
		nik_ce gkey_type _four		=   4;
		nik_ce gkey_type _five		=   5;
		nik_ce gkey_type _six		=   6;
		nik_ce gkey_type _seven		=   7;
		nik_ce gkey_type _eight		=   8;
		nik_ce gkey_type _nine		=   9;
		nik_ce gkey_type _ten		=  10;

	// [2^0-2^9]:

		using global_index_type		= unsigned short;
		using gindex_type		= global_index_type;
		using gindex_ctype		= global_index_type const;
		nik_ce auto U_gindex_type	= U_store_T<gindex_type>;
		nik_ce auto U_gindex_ctype	= U_store_T<gindex_ctype>;

		nik_ce gindex_type _2_0		=   1;
		nik_ce gindex_type _2_1		=   2;
		nik_ce gindex_type _2_2		=   4;
		nik_ce gindex_type _2_3		=   8;
		nik_ce gindex_type _2_4		=  16;
		nik_ce gindex_type _2_5		=  32;
		nik_ce gindex_type _2_6		=  64;
		nik_ce gindex_type _2_7		= 128;
		nik_ce gindex_type _2_8		= 256;
		nik_ce gindex_type _2_9		= 512;

		using global_depth_type		= unsigned short;
		using gdepth_type		= global_depth_type;
		using gdepth_ctype		= global_depth_type const;
		nik_ce auto U_gdepth_type	= U_store_T<gdepth_type>;
		nik_ce auto U_gdepth_ctype	= U_store_T<gdepth_ctype>;

/***********************************************************************************************************************/

// strings:

	using global_char_type		= char;
	using gchar_type		= global_char_type;
	using gchar_ctype		= global_char_type const;
	nik_ce auto U_gchar_type	= U_store_T<gchar_type>;
	nik_ce auto U_gchar_ctype	= U_store_T<gchar_ctype>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

		// The design privileges modularizing names, not grammar.
		// Given this, names are specified as enums within structs
		// rather than enum structs.

	template<gkey_type, gkey_type, gkey_type, auto...> struct T_grammar; // no default definition.

	template<auto Syn, auto Key, auto... Vs>
	nik_ce auto U_grammar = U_store_T<T_grammar<Syn, Key, Vs...>>;

/***********************************************************************************************************************/

// shapes:

	struct Shape
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			argument , parameter ,
			dimension
		};
	};

/***********************************************************************************************************************/

// patterns:

	struct Pattern
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			overload , number ,
			abstract , access , boolean , pointer ,
			dimension
		};
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// argument:

	// no default definition.

	template<auto Key, auto... Vs>       using T_argument = T_grammar<Shape::argument, Key, Vs...>;
	template<auto Key, auto... Vs> nik_ce auto U_argument = U_grammar<Shape::argument, Key, Vs...>;

/***********************************************************************************************************************/

// overload:

	template<auto... Vs> using T_arg_overload		= T_argument<Pattern::overload, Vs...>;
	template<auto... Vs> nik_ce auto U_arg_overload		= U_argument<Pattern::overload, Vs...>;

// number:

	template<auto... Vs> using T_arg_number			= T_argument<Pattern::number, Vs...>;
	template<auto... Vs> nik_ce auto U_arg_number		= U_argument<Pattern::number, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parameter:

	template<gkey_type Key, gkey_type Op, auto... Vs>
	struct T_grammar<Shape::parameter, Key, Op, Vs...> { }; // empty default definition.

	template<auto Key, auto... Vs>       using T_parameter = T_grammar<Shape::parameter, Key, Vs...>;
	template<auto Key, auto... Vs> nik_ce auto U_parameter = U_grammar<Shape::parameter, Key, Vs...>;

/***********************************************************************************************************************/

// abstract:

	template<auto... Vs> using T_par_abstract		= T_parameter<Pattern::abstract, Vs...>;
	template<auto... Vs> nik_ce auto U_par_abstract		= U_parameter<Pattern::abstract, Vs...>;

// access:

	template<auto... Vs> using T_par_access			= T_parameter<Pattern::access, Vs...>;
	template<auto... Vs> nik_ce auto U_par_access		= U_parameter<Pattern::access, Vs...>;

// boolean:

	template<auto... Vs> using T_par_boolean		= T_parameter<Pattern::boolean, Vs...>;
	template<auto... Vs> nik_ce auto U_par_boolean		= U_parameter<Pattern::boolean, Vs...>;

// pointer:

	template<auto... Vs> using T_par_pointer		= T_parameter<Pattern::pointer, Vs...>;
	template<auto... Vs> nik_ce auto U_par_pointer		= U_parameter<Pattern::pointer, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// structure:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// alias:

/***********************************************************************************************************************/

// interface:

	template<typename Type>
	struct alias
	{
		using type		= Type;
		using type_ptr		= type*;
		using type_cptr		= type_ptr const;
		using type_ref		= type&;

		using ctype		= type const;
		using ctype_ptr		= ctype*;
		using ctype_cptr	= ctype_ptr const;
		using ctype_ref		= ctype&;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array:

/***********************************************************************************************************************/

// proto:

	template<typename Model, typename Type, typename SizeType>
	class protoarray
	{
		public:

			using model_type	= Model;

			using type		= typename alias<Type>::type;
			using type_ptr		= typename alias<Type>::type_ptr;
			using type_cptr		= typename alias<Type>::type_cptr;
			using type_ref		= typename alias<Type>::type_ref;

			using ctype		= typename alias<Type>::ctype;
			using ctype_ptr		= typename alias<Type>::ctype_ptr;
			using ctype_cptr	= typename alias<Type>::ctype_cptr;
			using ctype_ref		= typename alias<Type>::ctype_ref;

			using size_type		= typename alias<SizeType>::type;
			using size_ctype	= typename alias<SizeType>::ctype;

		protected:

			model_type initial; // compile time compatible.
			size_type terminal; // compile time compatible.

		public:

			nik_ce protoarray() : initial{}, terminal{} { }

			// initial:

				nik_ce ctype_ptr origin () const { return initial; }
				nik_ce ctype_ptr cbegin () const { return initial; }

				nik_ce size_type left_size(ctype_cptr i) const { return i - initial; }

				nik_ce ctype_ptr citer (size_ctype n) const { return initial + n; }
				nik_ce ctype_ref cat   (size_ctype n) const { return initial[n]; }

				nik_ce ctype_ptr find(ctype_ref v) const
				{
					ctype_ptr in = cbegin();

					while (in != cend()) if (*in == v) break; else ++in;

					return in;
				}

				nik_ce size_type left_find(ctype_ref v) const { return left_size(find(v)); }
				nik_ce bool contains(ctype_ref v) const { return (find(v) != cend()); }

				template<typename In, typename End>
				nik_ce bool equal(size_ctype n, In in, End end) const
				{
					for (ctype_ptr out = citer(n); in != end; ++out, ++in)
						if (*out != *in) return false;

					return true;
				}

				template<typename In, typename End>
				nik_ce bool not_equal(size_ctype n, In in, End end) const
					{ return not equal(n, in, end); }

				nik_ce ctype_ref operator [] (size_ctype n) const { return cat(n); }

			// terminal:

				nik_ce size_type size () const { return terminal; }
				nik_ce size_type max  () const { return size() - 1; }

				nik_ce ctype_ptr cend  () const { return citer(terminal); }
				nik_ce ctype_ptr clast () const { return cend() - 1; }

				nik_ce size_type right_size(ctype_cptr i) const { return cend() - i; }

				nik_ce size_type right_find(ctype_ref v) const { return right_size(find(v)); }

				nik_ce bool is_empty  () const { return (terminal == 0); }
				nik_ce bool not_empty () const { return (terminal != 0); }
	};

/***********************************************************************************************************************/

// literal:

	template<typename Type, typename SizeType>
	class array_literal : public protoarray<Type const*, Type, SizeType>
	{
		public:

			using base		= protoarray<Type const*, Type, SizeType>;

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

		protected:

			nik_ces ctype empty[]	= { };

			nik_ce void set(ctype_cptr i, size_ctype t)
			{
				base::initial  = i;
				base::terminal = t;
			}

		public:

			nik_ce array_literal() { set(empty, 0); }
			nik_ce array_literal(ctype_cptr i, size_ctype t) { set(i, t); }

			template<auto N>
			nik_ce array_literal(const Type (&a)[N]) { set(a, N); }

			nik_ce bool operator == (const array_literal & l) const
				{ return base::equal(0, l.cbegin(), l.cend()); }

			nik_ce bool operator != (const array_literal & l) const
				{ return base::not_equal(0, l.cbegin(), l.cend()); }
	};

/***********************************************************************************************************************/

// string:

	template<typename Type, typename SizeType>
	struct string_literal : public array_literal<Type, SizeType>
	{
		using base		= array_literal<Type, SizeType>;

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

		template<auto N>
		nik_ce string_literal(const Type (&s)[N]) : base{s, N-1} { }

		nik_ce string_literal() : base{} { } // maybe.
	};

/***********************************************************************************************************************/

// interface:

	template<typename Type, typename SizeType, SizeType Size>
	class array : public protoarray<Type[Size], Type, SizeType>
	{
		public:

			using base		= protoarray<Type[Size], Type, SizeType>;

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

			nik_ce array() { }

			template<typename T, auto N>
			nik_ce array(const T (&a)[N]) { push(a, a + N); }

			// immutable:

				using base::operator [];

				nik_ce size_type length() const { return Size; }

				nik_ce bool operator == (const array & s) const
					{ return base::equal(0, s.cbegin(), s.cend()); }

				nik_ce bool operator != (const array & s) const
					{ return base::not_equal(0, s.cbegin(), s.cend()); }

			// mutable:

				nik_ce type_ptr begin () { return base::initial; }

				nik_ce type_ptr iter (size_ctype n) { return base::initial + n; }
				nik_ce type_ref at   (size_ctype n) { return base::initial[n]; }

				nik_ce type_ptr end  () { return iter(base::terminal); }
				nik_ce type_ptr last () { return end() - 1; }

				nik_ce type_ref operator [] (size_ctype n) { return at(n); }

				nik_ce void clear() { base::terminal = 0; }
				nik_ce void fullsize() { base::terminal = Size; }
				nik_ce void upsize(size_ctype n = 1) { base::terminal += n; }
				nik_ce void downsize(size_ctype n = 1) { base::terminal -= n; }

				nik_ce void push(ctype_ref v) { *iter(base::terminal++) = v; }
				nik_ce type pop() { return *iter(--base::terminal); }

				template<typename In, typename End>
				nik_ce void push(In in, End end) { while (in != end) push(*in++); }

				template<typename F, typename In, typename End>
				nik_ce void pushmap(F, In in, End end)
					{ while (in != end) push(T_restore_T<F>::result(*in++)); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// table:

/***********************************************************************************************************************/

// proto:

	template<typename Base, typename SizeType, SizeType RowSize, SizeType ColSize>
	class prototable : public Base
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

			nik_ce prototable() { }

			template<typename T, auto N>
			nik_ce prototable(const T (&a)[N]) : base{a} { }

			nik_ce size_type row_length () const { return RowSize; }
			nik_ce size_type col_length () const { return ColSize; }

			nik_ce ctype_ptr row_cbegin (size_ctype n) const { return base::citer(n * ColSize); }
			nik_ce ctype_ptr row_cend   (size_ctype n) const { return row_cbegin(n + 1); }
			nik_ce ctype_ptr row_clast  (size_ctype n) const { return row_cend(n) - 1; }

			nik_ce ctype_ptr operator [] (size_ctype n) const { return row_cbegin(n); }
	};

/***********************************************************************************************************************/

// literal:

	template<typename Type, typename SizeType, SizeType RowSize, SizeType ColSize>
	class table_literal : public prototable<array_literal<Type, SizeType>, SizeType, RowSize, ColSize>
	{
		public:

			using subbase		= array_literal<Type, SizeType>;
			using base		= prototable<subbase, SizeType, RowSize, ColSize>;

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

			nik_ce table_literal() { }

			template<typename T, auto N>
			nik_ce table_literal(const T (&a)[N]) : base{a} { }

			nik_ce bool operator == (const table_literal & l) const
				{ return base::equal(0, l.cbegin(), l.cend()); }

			nik_ce bool operator != (const table_literal & l) const
				{ return base::not_equal(0, l.cbegin(), l.cend()); }
	};

/***********************************************************************************************************************/

// interface:

	template<typename Type, typename SizeType, SizeType RowSize, SizeType ColSize>
	class table : public prototable<array<Type, SizeType, RowSize * ColSize>, SizeType, RowSize, ColSize>
	{
		public:

			using subbase		= array<Type, SizeType, RowSize * ColSize>;
			using base		= prototable<subbase, SizeType, RowSize, ColSize>;

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

			nik_ce table() { }

			template<typename T, auto N>
			nik_ce table(const T (&a)[N]) : base{a} { }

			using base::operator [];

			nik_ce type_ptr row_begin (size_ctype n) { return base::iter(n * ColSize); }
			nik_ce type_ptr row_end   (size_ctype n) { return row_begin(n + 1); }
			nik_ce type_ptr row_last  (size_ctype n) { return row_end(n) - 1; }

			nik_ce type_ptr operator [] (size_ctype n) { return row_begin(n); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

