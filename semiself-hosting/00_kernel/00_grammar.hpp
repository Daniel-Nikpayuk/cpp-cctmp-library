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

	template<typename T> nik_ce auto U_store_T     = store<T*>;
	template<typename T> nik_ce auto U_store_T<T&> = store<T&>;

// U -> T:

	template<typename T> struct store_match                    { using result = T; };
	template<typename T> struct store_match<void(*const&)(T&)> { using result = T&; };
	template<typename T> struct store_match<void(*const&)(T*)> { using result = T; };

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
		using gcbool_type		= global_bool_type const;
		nik_ce auto U_gbool_type	= U_store_T<gbool_type>;
		nik_ce auto U_gcbool_type	= U_store_T<gcbool_type>;

	// [0-10]:

		using global_key_type		= unsigned char;
		using gkey_type			= global_key_type;
		using gckey_type		= global_key_type const;
		nik_ce auto U_gkey_type		= U_store_T<gkey_type>;
		nik_ce auto U_gckey_type	= U_store_T<gckey_type>;

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
		using gcindex_type		= global_index_type const;
		nik_ce auto U_gindex_type	= U_store_T<gindex_type>;
		nik_ce auto U_gcindex_type	= U_store_T<gcindex_type>;

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
		using gcdepth_type		= global_depth_type const;
		nik_ce auto U_gdepth_type	= U_store_T<gdepth_type>;
		nik_ce auto U_gcdepth_type	= U_store_T<gcdepth_type>;

/***********************************************************************************************************************/

// strings:

	using global_char_type		= char;
	using gchar_type		= global_char_type;
	using gcchar_type		= global_char_type const;
	nik_ce auto U_gchar_type	= U_store_T<gchar_type>;
	nik_ce auto U_gcchar_type	= U_store_T<gcchar_type>;

/***********************************************************************************************************************/

// array:

	template<typename Type, Type... Vs>
	nik_ce Type array[] = { Vs... };

	nik_ce gindex_type array_2_N[] = { _2_0, _2_1, _2_2, _2_3, _2_4, _2_5, _2_6, _2_7, _2_8, _2_9 };

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

// structure:

/***********************************************************************************************************************/

// sequence:

	template<typename Type, typename SizeType, SizeType Size>
	class sequence
	{
		public:

			using type		= Type;
			using type_ptr		= type*;
			using type_cptr		= type_ptr const;
			using type_ref		= type&;

			using ctype		= type const;
			using ctype_ptr		= ctype*;
			using ctype_cptr	= ctype_ptr const;
			using ctype_ref		= ctype&;

			using size_type		= SizeType;
			using size_ctype	= size_type const;

		protected:

			type initial[Size];
			size_type terminal; // compile time compatible.

		public:

			nik_ce sequence() : initial{}, terminal{} { }

		//	nik_ce sequence(const sequence & s) : initial{}, terminal{} { push(s.cbegin(), s.cend()); }

			template<typename T, auto N>
			nik_ce sequence(const T (&s)[N]) : initial{}, terminal{} { push(s, s + N); }

			// immutable:

				nik_ce size_type length () const { return Size; }
				nik_ce ctype_ptr origin () const { return initial; }
				nik_ce size_type size   () const { return terminal; }
				nik_ce size_type max    () const { return size() - 1; }

				nik_ce bool is_empty  () const { return (terminal == 0); }
				nik_ce bool not_empty () const { return (terminal != 0); }

				nik_ce ctype_ptr citer(size_ctype n) const { return initial + n; }

				nik_ce auto left_size  (ctype_cptr i) const { return i - initial; }
				nik_ce auto right_size (ctype_cptr i) const { return cend() - i; }

				nik_ce ctype_ptr cbegin () const { return initial; }
				nik_ce ctype_ptr clast  () const { return cend(terminal) - 1; }
				nik_ce ctype_ptr cend   () const { return citer(terminal); }

				nik_ce ctype_ref operator [] (size_ctype pos) const { return initial[pos]; }

			// mutable:

				nik_ce type_ptr iter(size_ctype n) { return initial + n; }

				nik_ce void clear() { terminal = 0; }
				nik_ce void fullsize() { terminal = Size; }
				nik_ce void upsize(size_ctype num = 1) { terminal += num; }
				nik_ce void downsize(size_ctype num = 1) { terminal -= num; }
				nik_ce void push(ctype_ref v) { *iter(terminal++) = v; }
				nik_ce type pop() { return *iter(--terminal); }

				nik_ce type_ptr begin () { return initial; }
				nik_ce type_ptr last  () { return end() - 1; }
				nik_ce type_ptr end   () { return iter(terminal); }

				nik_ce type_ref operator [] (size_ctype pos) { return initial[pos]; }

				template<typename In, typename End>
				nik_ce void push(In in, End end) { while (in != end) push(*in++); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

