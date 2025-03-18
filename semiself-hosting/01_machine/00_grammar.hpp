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

		nik_ce auto U_unsigned_char		= U_store_T < unsigned char      >;
		nik_ce auto U_unsigned_short		= U_store_T < unsigned short     >;
		nik_ce auto U_unsigned_int		= U_store_T < unsigned int       >;
		nik_ce auto U_unsigned_long		= U_store_T < unsigned long      >;
		nik_ce auto U_unsigned_long_long	= U_store_T < unsigned long long >;

	// signed:

		nik_ce auto U_signed_char		= U_store_T < signed char      >;
		nik_ce auto U_signed_short		= U_store_T < signed short     >;
		nik_ce auto U_signed_int		= U_store_T < signed int       >;
		nik_ce auto U_signed_long		= U_store_T < signed long      >;
		nik_ce auto U_signed_long_long		= U_store_T < signed long long >;

	// auto:

		nik_ce auto U_auto_bool			= U_store_T < decltype( false ) >;
		nik_ce auto U_auto_char			= U_store_T < decltype(  '\0' ) >;
		nik_ce auto U_auto_int			= U_store_T < decltype(    0  ) >;
		nik_ce auto U_auto_float		= U_store_T < decltype(  0.0  ) >;

/***********************************************************************************************************************/

// operator:

	// comparison:

		template<typename... Ts> nik_ce auto U_equal			= U_store_T < T_equal        <Ts...> >;
		template<typename... Ts> nik_ce auto U_not_equal		= U_store_T < T_not_equal    <Ts...> >;
		template<typename... Ts> nik_ce auto U_l_than			= U_store_T < T_l_than       <Ts...> >;
		template<typename... Ts> nik_ce auto U_l_than_or_eq		= U_store_T < T_l_than_or_eq <Ts...> >;
		template<typename... Ts> nik_ce auto U_g_than			= U_store_T < T_g_than       <Ts...> >;
		template<typename... Ts> nik_ce auto U_g_than_or_eq		= U_store_T < T_g_than_or_eq <Ts...> >;

	// arithmetic:

		template<typename... Ts> nik_ce auto U_add			= U_store_T < T_add      <Ts...> >;
		template<typename... Ts> nik_ce auto U_subtract			= U_store_T < T_subtract <Ts...> >;
		template<typename... Ts> nik_ce auto U_multiply			= U_store_T < T_multiply <Ts...> >;
		template<typename... Ts> nik_ce auto U_divide			= U_store_T < T_divide   <Ts...> >;
		template<typename... Ts> nik_ce auto U_modulo			= U_store_T < T_modulo   <Ts...> >;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// packs:

/***********************************************************************************************************************/

// auto:

	using T_null_Vs = T_pack_Vs<>; // T_pack_Vs was defined in 00/00.

	template<auto... Vs>
	nik_ce auto U_pack_Vs = store<T_pack_Vs<Vs...>*>;
	nik_ce auto U_null_Vs = U_pack_Vs<>;

// typename:

	template<typename... Ts>
	nik_ce auto U_pack_Ts = U_pack_Vs<U_store_T<Ts>...>;
	nik_ce auto U_null_Ts = U_null_Vs;

	template<typename... Ts>
	using T_pack_Ts = T_store_U<U_pack_Ts<Ts...>>;

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

// cover:

	// this "friend" technique takes inspiration from Kris Jusiak's
	// CppCon 2024 talk "Template-less Metaprogramming in C++".

/***********************************************************************************************************************/

// V -> Y:

	template<auto V>
	struct T_normed
	{
		template<typename... Ts>
		nik_ce auto friend V_recover_Y(T_normed, Ts...);
	};

	template<auto V>
	struct T_cover_V
	{
		static void result();

		template<typename... Ts>
		nik_ce auto friend V_recover_Y(T_normed<result>, Ts...) { return V; }
	};

	template<auto     V> nik_ce auto Y_cover_V = T_cover_V<V>::result;
	template<typename T> nik_ce auto Y_cover_T = Y_cover_V<U_store_T<T>>;

	template<auto... Vs>
	nik_ce void(*Ys_cover_Vs[sizeof...(Vs)])() = { Y_cover_V<Vs>... };

	template<typename... Ts>
	nik_ce void(*Ys_cover_Ts[sizeof...(Ts)])() = { Y_cover_T<Ts>... };

// Y -> V:

	template<auto Y> nik_ce auto  V_cover_Y    = V_recover_Y(T_normed<Y>{});
	template<auto Y>        using T_cover_Y    = T_store_U<V_cover_Y<Y>>;

/***********************************************************************************************************************/

// at:

	template<auto n, auto... Vs>
	nik_ce auto at_ = V_cover_Y<Ys_cover_Vs<Vs...>[n]>;

	template<auto... Vs, nik_vp(p)(T_pack_Vs<Vs...>*), auto n>
	nik_ce auto at_<p, n> = at_<n, Vs...>;

	template<auto n, typename... Ts>
	using type_at = T_cover_Y<Ys_cover_Ts<Ts...>[n]>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

