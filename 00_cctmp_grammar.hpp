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

// grammar:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// store:

/***********************************************************************************************************************/

// T -> U:

	template<typename T> nik_ces void store(T) { }

	template<typename T>
	nik_ce auto U_store_T = store<T*>;

	template<typename T>
	nik_ce auto U_store_T<T&> = store<T&>;

// U -> T:

	template<typename T> struct store_match				{ using result = T; };
	template<typename T> struct store_match<void(*)(T&)>		{ using result = T&; };
	template<typename T> struct store_match<void(*const)(T&)>	{ using result = T&; };
	template<typename T> struct store_match<void(*)(T*)>		{ using result = T; };
	template<typename T> struct store_match<void(*const)(T*)>	{ using result = T; };

	template<typename T>
	using T_restore_T = typename store_match<T>::result;

	template<typename T>
	nik_ce auto U_restore_T = U_store_T<T_restore_T<T>>;

	template<auto U>
	using T_store_U = T_restore_T<decltype(U)>;

/***********************************************************************************************************************/

// constant:

	// void:

		nik_ce auto U_void = U_store_T<void>;
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

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// packs:

/***********************************************************************************************************************/

// auto:

	template<auto...> struct T_pack_Vs { };

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

// types:

/***********************************************************************************************************************/

// subnumbers:

	// bool:

		using global_bool_type		= bool;
		using gbool_type		= global_bool_type;
		using gcbool_type		= global_bool_type const;

	// [0-10]:

		using global_key_type		= unsigned char;
		using gkey_type			= global_key_type;
		using gckey_type		= global_key_type const;

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

/***********************************************************************************************************************/

// array:

	template<typename Type, Type... Vs>
	nik_ce Type array[] = { Vs... };

	nik_ce gindex_type array_2_N[] = { _2_0, _2_1, _2_2, _2_3, _2_4, _2_5, _2_6, _2_7, _2_8, _2_9 };

/***********************************************************************************************************************/

// sequence:

	template<typename Type, auto Size>
	struct sequence
	{
		Type value[Size];
		decltype(Size) length;

		nik_ce sequence() : value{}, length{} { }
	//	nik_ce sequence(const Type (&s)[Size]) : value{s} { }
	};

/***********************************************************************************************************************/

// tuple:

	template<typename... Ts>
	struct tuple
	{
		nik_ce tuple(Ts... vs) { }
	};

	template<typename T, typename... Ts>
	struct tuple<T, Ts...>
	{
		T value;
		tuple<Ts...> rest;

		nik_ce tuple(T v, Ts... vs) : value{v}, rest{vs...} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

		// The design privileges modularizing names, not grammar.
		// As such, names are specified as enums within structs
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
			argument , parameter
		};
	};

	// argument:

		// no default definition.

		template<auto Key, auto... Vs>       using T_argument = T_grammar<Shape::argument, Key, Vs...>;
		template<auto Key, auto... Vs> nik_ce auto U_argument = U_grammar<Shape::argument, Key, Vs...>;

	// parameter:

		template<gkey_type Key, gkey_type Op, auto... Vs>
		struct T_grammar<Shape::parameter, Key, Op, Vs...> { }; // empty default definition.

		template<auto Key, auto... Vs>       using T_parameter = T_grammar<Shape::parameter, Key, Vs...>;
		template<auto Key, auto... Vs> nik_ce auto U_parameter = U_grammar<Shape::parameter, Key, Vs...>;

/***********************************************************************************************************************/

// patterns:

	struct Pattern
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			overload , higher_order ,
			abstract , access       , list     ,
			boolean  , number       , pointer  , reference ,
			array    , function     , sequence , tuple     ,
			dimension
		};
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// operators:

/***********************************************************************************************************************/

// overload:

	struct Overload
	{
		enum : gkey_type
		{
			// basis:

				id = 0, identity = id, // convenience for default params.

			// bitwise:

				upshift , downshift ,

			// mutation:

				assign , dereference ,

			dimension
		};
	};

	// argument:

		template<auto... Vs> using T_arg_overload		= T_argument<Pattern::overload, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_overload		= U_argument<Pattern::overload, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_overload		= T_parameter<Pattern::overload, Vs...>;
		template<auto... Vs> nik_ce auto U_par_overload		= U_parameter<Pattern::overload, Vs...>;

/***********************************************************************************************************************/

// higher order:

	struct HigherOrder
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.

			// basis:

				cast , constant , wrap , bind , curry ,

			dimension
		};
	};

	// argument:

		template<auto... Vs> using T_arg_higher_order		= T_argument<Pattern::higher_order, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_higher_order	= U_argument<Pattern::higher_order, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_higher_order		= T_parameter<Pattern::higher_order, Vs...>;
		template<auto... Vs> nik_ce auto U_par_higher_order	= U_parameter<Pattern::higher_order, Vs...>;

/***********************************************************************************************************************/

// abstract:

	struct Abstract
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.

			// basis:

				nop ,

			// comparison:

				same ,

			// variadic:

				is_null , length , car , cadr ,

			dimension
		};
	};

	// argument:

		template<auto... Vs> using T_arg_abstract		= T_argument<Pattern::abstract, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_abstract		= U_argument<Pattern::abstract, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_abstract		= T_parameter<Pattern::abstract, Vs...>;
		template<auto... Vs> nik_ce auto U_par_abstract		= U_parameter<Pattern::abstract, Vs...>;

/***********************************************************************************************************************/

// access:

	struct Access
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.

			// basis:

				is_const  ,
				add_const , remove_const , to_const , from_const ,

			// comparison:

				csame ,

			dimension
		};
	};

	// argument:

		template<auto... Vs> using T_arg_access			= T_argument<Pattern::access, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_access		= U_argument<Pattern::access, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_access			= T_parameter<Pattern::access, Vs...>;
		template<auto... Vs> nik_ce auto U_par_access		= U_parameter<Pattern::access, Vs...>;

/***********************************************************************************************************************/

// list:

	struct List
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.

			// basis:

				name ,

			// comparison:

				similar ,

			// variadic:

				to_list , b0_unpack , rename ,

			// functional:

				pad , cdr , map , zip , unite , cons , push ,

			dimension
		};
	};

	// argument:

		template<auto... Vs> using T_arg_list			= T_argument<Pattern::list, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_list		= U_argument<Pattern::list, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_list			= T_parameter<Pattern::list, Vs...>;
		template<auto... Vs> nik_ce auto U_par_list		= U_parameter<Pattern::list, Vs...>;

/***********************************************************************************************************************/

// boolean:

	struct Boolean
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.

			// basis:

				if_then_else ,

			// lazy:

				stem , costem , distem ,

			// logical:

				not_ , and_ , or_ , implies , equivalent ,

			// propositional:

				and_wise ,

			dimension
		};
	};

	// argument:

		template<auto... Vs> using T_arg_boolean		= T_argument<Pattern::boolean, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_boolean		= U_argument<Pattern::boolean, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_boolean		= T_parameter<Pattern::boolean, Vs...>;
		template<auto... Vs> nik_ce auto U_par_boolean		= U_parameter<Pattern::boolean, Vs...>;

/***********************************************************************************************************************/

// number:

	struct Number
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.

			// basis:

				is_unsigned , not_unsigned ,
				is_signed   , not_signed   ,
				is_integer  , not_integer  ,

			// comparison:

				equal        , not_equal             ,
				less_than    , less_than_or_equal    ,
				greater_than , greater_than_or_equal ,

			// arithmetic:

				add , subtract , multiply , divide , modulo ,

			dimension
		};
	};

	// argument:

		template<auto... Vs> using T_arg_number			= T_argument<Pattern::number, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_number		= U_argument<Pattern::number, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_number			= T_parameter<Pattern::number, Vs...>;
		template<auto... Vs> nik_ce auto U_par_number		= U_parameter<Pattern::number, Vs...>;

/***********************************************************************************************************************/

// pointer:

	struct Pointer
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.

			// basis:

				is  ,
				add , remove , to , from ,

			dimension
		};
	};

	// argument:

		template<auto... Vs> using T_arg_pointer		= T_argument<Pattern::pointer, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_pointer		= U_argument<Pattern::pointer, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_pointer		= T_parameter<Pattern::pointer, Vs...>;
		template<auto... Vs> nik_ce auto U_par_pointer		= U_parameter<Pattern::pointer, Vs...>;

/***********************************************************************************************************************/

// reference:

	struct Reference
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.

			// basis:

				is  ,
				add , remove , to , from ,

			dimension
		};
	};

	// argument:

		template<auto... Vs> using T_arg_reference		= T_argument<Pattern::reference, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_reference	= U_argument<Pattern::reference, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_reference		= T_parameter<Pattern::reference, Vs...>;
		template<auto... Vs> nik_ce auto U_par_reference	= U_parameter<Pattern::reference, Vs...>;

/***********************************************************************************************************************/

// array:

	struct Array
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.

			// meta:

				is   ,
				type , size ,

			// basis:

				to_array , begin , last , end , apply ,

			// 2^N:

				log_floor ,

			dimension
		};
	};

	// argument:

		template<auto... Vs> using T_arg_array			= T_argument<Pattern::array, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_array		= U_argument<Pattern::array, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_array			= T_parameter<Pattern::array, Vs...>;
		template<auto... Vs> nik_ce auto U_par_array		= U_parameter<Pattern::array, Vs...>;

/***********************************************************************************************************************/

// function:

	struct Function
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.

			// meta:

				type  ,
				arity , out_type , in_types ,

			// call:

				eval , procedure , method , tailor , alias , custom ,

			dimension
		};
	};

	// argument:

		template<auto... Vs> using T_arg_function		= T_argument<Pattern::function, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_function		= U_argument<Pattern::function, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_function		= T_parameter<Pattern::function, Vs...>;
		template<auto... Vs> nik_ce auto U_par_function		= U_parameter<Pattern::function, Vs...>;

/***********************************************************************************************************************/

// sequence:

	struct Sequence
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.

			// meta:

				is   ,
				type , size ,

			// basis:

				to_sequence , begin , last , end , apply ,

			dimension
		};
	};

	// argument:

		template<auto... Vs> using T_arg_sequence		= T_argument<Pattern::sequence, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_sequence		= U_argument<Pattern::sequence, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_sequence		= T_parameter<Pattern::sequence, Vs...>;
		template<auto... Vs> nik_ce auto U_par_sequence		= U_parameter<Pattern::sequence, Vs...>;

/***********************************************************************************************************************/

// tuple:

	struct Tuple
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.

			// meta:

				is   ,
				type , size ,

			// basis:

				to_tuple ,

			dimension
		};
	};

	// argument:

		template<auto... Vs> using T_arg_tuple			= T_argument<Pattern::tuple, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_tuple		= U_argument<Pattern::tuple, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_tuple			= T_parameter<Pattern::tuple, Vs...>;
		template<auto... Vs> nik_ce auto U_par_tuple		= U_parameter<Pattern::tuple, Vs...>;

/***********************************************************************************************************************/

// identity:

	struct Identity
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.

			// list to:

				list_to_array ,

			// array to:

				array_to_list ,

			dimension
		};
	};

	// argument:

		template<auto... Vs> using T_arg_identity		= T_argument<Pattern::identity, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_identity		= U_argument<Pattern::identity, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_identity		= T_parameter<Pattern::identity, Vs...>;
		template<auto... Vs> nik_ce auto U_par_identity		= U_parameter<Pattern::identity, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

