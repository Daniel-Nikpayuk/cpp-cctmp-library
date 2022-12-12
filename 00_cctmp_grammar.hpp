/************************************************************************************************************************
**
** Copyright 2022 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

	template<typename T> nik_ces void store(T) { };

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

		nik_ce sequence() : value{} { }
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

// grammar:

	// The design privileges modularizing names, not grammar.
	// As such, names are specified as enums within structs
	// rather than enum structs.

/***********************************************************************************************************************/

// shapes:

	struct Shape
	{
		enum : gkey_type
		{
			argument = 0,
			parameter
		};
	};

/***********************************************************************************************************************/

// patterns:

	struct Pattern
	{
		enum : gkey_type
		{
			overload = 0,
			higher_order , continuation , iterator ,
			abstract     , access       , list     ,
			boolean      , number       ,
			pointer      , reference    , array    ,
			function     , sequence     , tuple    ,
			identity
		};
	};

/***********************************************************************************************************************/

// operators:

	// overload:

		struct Overload
		{
			enum : gkey_type
			{
				// basis:

					id = 0,

				// comparison:

					equal        , not_equal             ,
					less_than    , less_than_or_equal    ,
					greater_than , greater_than_or_equal ,

				// logical:

					not_ , and_ , or_ , implies , equivalent ,

				// arithmetic:

					add , subtract , multiply , divide , modulo ,

				// bitwise:

					upshift , downshift ,

				// mutation:

					assign , dereference
			};
		};

	// higher order:

		struct HigherOrder
		{
			enum : gkey_type
			{
				// basis:

					cast = 0,
					constant , wrap , bind , curry
			};
		};

	// continuation:

		struct Continuation
		{
			enum : gkey_type
			{
				// passers:

					first = 0,
					second , map , apply
			};
		};

	// iterator:

		struct Iterator
		{
			enum : gkey_type
			{
				// near linear:

					multimap = 0,
					multifold , multifind , multisift
			};
		};

	// abstract:

		struct Abstract
		{
			enum : gkey_type
			{
				// basis:

					nop = 0,

				// comparison:

					same ,

				// variadic:

					is_null , length , car , cadr , at, find
			};
		};

	// access:

		struct Access
		{
			enum : gkey_type
			{
				// basis:

					is_const = 0,
					add_const , remove_const , to_const , from_const ,

				// comparison:

					csame
			};
		};

	// list:

		struct List
		{
			enum : gkey_type
			{
				// basis:

					name = 0,

				// comparison:

					similar ,

				// variadic:

					to_list   ,
					f0_unpack , f1_unpack , f2_unpack ,
					b0_unpack , b1_unpack , b2_unpack ,
					rename    ,

				// functional:

					pad , cdr , map , zip , unite , cons , push
			};
		};

	// boolean:

		struct Boolean
		{
			enum : gkey_type
			{
				// basis:

					if_then_else = 0
			};
		};

	// number:

		struct Number
		{
			enum : gkey_type
			{
				// basis:

					is_unsigned = 0,
					not_unsigned , is_signed , not_signed , is_integer , not_integer
			};
		};

	// pointer:

		struct Pointer
		{
			enum : gkey_type
			{
				// basis:

					is = 0,
					add , remove , to , from
			};
		};

	// reference:

		struct Reference
		{
			enum : gkey_type
			{
				// basis:

					is = 0,
					add , remove , to , from
			};
		};

	// array:

		struct Array
		{
			enum : gkey_type
			{
				// meta:

					is = 0,
					type , size ,

				// basis:

					to_array , begin , last , end , apply ,

				// 2^N:

					log_floor
			};
		};

	// function:

		struct Function
		{
			enum : gkey_type
			{
				// meta:

					type = 0,
					arity , out_type , in_types ,

				// call:

					custom , nested , procedure , method , tailor
			};
		};

	// sequence:

		struct Sequence
		{
			enum : gkey_type
			{
				// meta:

					is = 0,
					type , size ,

				// basis:

					to_sequence , begin , last , end , apply
			};
		};

	// tuple:

		struct Tuple
		{
			enum : gkey_type
			{
				// meta:

					is = 0,
					type , size ,

				// basis:

					to_tuple
			};
		};

	// identity:

		struct Identity
		{
			enum : gkey_type
			{
				// list to:

					list_to_array = 0,

				// array to:

					array_to_list
			};
		};

/***********************************************************************************************************************/

// grammar:

	template<gkey_type, gkey_type, gkey_type, auto...> struct T_grammar; // no default definition.

	template<auto Syn, auto Key, auto... Vs>
	nik_ce auto U_grammar = U_store_T<T_grammar<Syn, Key, Vs...>>;

// argument:

	// no default definition.

	template<auto Key, auto... Vs>       using T_argument = T_grammar<Shape::argument, Key, Vs...>;
	template<auto Key, auto... Vs> nik_ce auto U_argument = U_grammar<Shape::argument, Key, Vs...>;

// parameter:

	template<gkey_type Key, gkey_type Op, auto... Vs>
	struct T_grammar<Shape::parameter, Key, Op, Vs...> { }; // empty default definition.

	template<auto Key, auto... Vs>       using T_parameter = T_grammar<Shape::parameter, Key, Vs...>;
	template<auto Key, auto... Vs> nik_ce auto U_parameter = U_grammar<Shape::parameter, Key, Vs...>;

	template<auto Key, auto Op> nik_ce void parameter() { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// alias:

/***********************************************************************************************************************/

// overload:

	// argument:

		template<auto... Vs> using T_arg_overload		= T_argument<Pattern::overload, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_overload		= U_argument<Pattern::overload, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_overload		= T_parameter<Pattern::overload, Vs...>;
		template<auto... Vs> nik_ce auto U_par_overload		= U_parameter<Pattern::overload, Vs...>;

/***********************************************************************************************************************/

// higher order:

	// argument:

		template<auto... Vs> using T_arg_higher_order		= T_argument<Pattern::higher_order, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_higher_order	= U_argument<Pattern::higher_order, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_higher_order		= T_parameter<Pattern::higher_order, Vs...>;
		template<auto... Vs> nik_ce auto U_par_higher_order	= U_parameter<Pattern::higher_order, Vs...>;

/***********************************************************************************************************************/

// continuation:

	// argument:

		template<auto... Vs> using T_arg_continuation		= T_argument<Pattern::continuation, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_continuation	= U_argument<Pattern::continuation, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_continuation		= T_parameter<Pattern::continuation, Vs...>;
		template<auto... Vs> nik_ce auto U_par_continuation	= U_parameter<Pattern::continuation, Vs...>;

/***********************************************************************************************************************/

// iterator:

	// argument:

		template<auto... Vs> using T_arg_iterator		= T_argument<Pattern::iterator, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_iterator		= U_argument<Pattern::iterator, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_iterator		= T_parameter<Pattern::iterator, Vs...>;
		template<auto... Vs> nik_ce auto U_par_iterator		= U_parameter<Pattern::iterator, Vs...>;

/***********************************************************************************************************************/

// abstract:

	// argument:

		template<auto... Vs> using T_arg_abstract		= T_argument<Pattern::abstract, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_abstract		= U_argument<Pattern::abstract, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_abstract		= T_parameter<Pattern::abstract, Vs...>;
		template<auto... Vs> nik_ce auto U_par_abstract		= U_parameter<Pattern::abstract, Vs...>;

/***********************************************************************************************************************/

// access:

	// argument:

		template<auto... Vs> using T_arg_access			= T_argument<Pattern::access, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_access		= U_argument<Pattern::access, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_access			= T_parameter<Pattern::access, Vs...>;
		template<auto... Vs> nik_ce auto U_par_access		= U_parameter<Pattern::access, Vs...>;

/***********************************************************************************************************************/

// list:

	// argument:

		template<auto... Vs> using T_arg_list			= T_argument<Pattern::list, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_list		= U_argument<Pattern::list, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_list			= T_parameter<Pattern::list, Vs...>;
		template<auto... Vs> nik_ce auto U_par_list		= U_parameter<Pattern::list, Vs...>;

/***********************************************************************************************************************/

// boolean:

	// argument:

		template<auto... Vs> using T_arg_boolean		= T_argument<Pattern::boolean, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_boolean		= U_argument<Pattern::boolean, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_boolean		= T_parameter<Pattern::boolean, Vs...>;
		template<auto... Vs> nik_ce auto U_par_boolean		= U_parameter<Pattern::boolean, Vs...>;

/***********************************************************************************************************************/

// number:

	// argument:

		template<auto... Vs> using T_arg_number			= T_argument<Pattern::number, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_number		= U_argument<Pattern::number, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_number			= T_parameter<Pattern::number, Vs...>;
		template<auto... Vs> nik_ce auto U_par_number		= U_parameter<Pattern::number, Vs...>;

/***********************************************************************************************************************/

// pointer:

	// argument:

		template<auto... Vs> using T_arg_pointer		= T_argument<Pattern::pointer, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_pointer		= U_argument<Pattern::pointer, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_pointer		= T_parameter<Pattern::pointer, Vs...>;
		template<auto... Vs> nik_ce auto U_par_pointer		= U_parameter<Pattern::pointer, Vs...>;

/***********************************************************************************************************************/

// reference:

	// argument:

		template<auto... Vs> using T_arg_reference		= T_argument<Pattern::reference, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_reference	= U_argument<Pattern::reference, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_reference		= T_parameter<Pattern::reference, Vs...>;
		template<auto... Vs> nik_ce auto U_par_reference	= U_parameter<Pattern::reference, Vs...>;

/***********************************************************************************************************************/

// array:

	// argument:

		template<auto... Vs> using T_arg_array			= T_argument<Pattern::array, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_array		= U_argument<Pattern::array, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_array			= T_parameter<Pattern::array, Vs...>;
		template<auto... Vs> nik_ce auto U_par_array		= U_parameter<Pattern::array, Vs...>;

/***********************************************************************************************************************/

// function:

	// argument:

		template<auto... Vs> using T_arg_function		= T_argument<Pattern::function, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_function		= U_argument<Pattern::function, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_function		= T_parameter<Pattern::function, Vs...>;
		template<auto... Vs> nik_ce auto U_par_function		= U_parameter<Pattern::function, Vs...>;

/***********************************************************************************************************************/

// sequence:

	// argument:

		template<auto... Vs> using T_arg_sequence		= T_argument<Pattern::sequence, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_sequence		= U_argument<Pattern::sequence, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_sequence		= T_parameter<Pattern::sequence, Vs...>;
		template<auto... Vs> nik_ce auto U_par_sequence		= U_parameter<Pattern::sequence, Vs...>;

/***********************************************************************************************************************/

// tuple:

	// argument:

		template<auto... Vs> using T_arg_tuple			= T_argument<Pattern::tuple, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_tuple		= U_argument<Pattern::tuple, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_tuple			= T_parameter<Pattern::tuple, Vs...>;
		template<auto... Vs> nik_ce auto U_par_tuple		= U_parameter<Pattern::tuple, Vs...>;

/***********************************************************************************************************************/

// identity:

	// argument:

		template<auto... Vs> using T_arg_identity		= T_argument<Pattern::identity, Vs...>;
		template<auto... Vs> nik_ce auto U_arg_identity		= U_argument<Pattern::identity, Vs...>;

	// parameter:

		template<auto... Vs> using T_par_identity		= T_parameter<Pattern::identity, Vs...>;
		template<auto... Vs> nik_ce auto U_par_identity		= U_parameter<Pattern::identity, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// overload:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// argument:

/***********************************************************************************************************************/

// basis:

	// id:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::id, filler...>
		{
			template<typename T>
			nik_ces auto result(T v) { return v; }

		}; nik_ce auto _id_ = U_arg_overload<Overload::id>;

/***********************************************************************************************************************/

// comparison:

	// equal:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... == vs); }

		}; nik_ce auto _equal_ = U_arg_overload<Overload::equal>;

	// not_equal:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::not_equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... != vs); }

		}; nik_ce auto _not_equal_ = U_arg_overload<Overload::not_equal>;

	// less_than:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::less_than, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... < vs); }

		}; nik_ce auto _less_than_ = U_arg_overload<Overload::less_than>;

	// less_than_or_equal:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::less_than_or_equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... <= vs); }

		}; nik_ce auto _less_than_or_equal_ = U_arg_overload<Overload::less_than_or_equal>;

	// greater_than:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::greater_than, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... > vs); }

		}; nik_ce auto _greater_than_ = U_arg_overload<Overload::greater_than>;

	// greater_than_or_equal:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::greater_than_or_equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... >= vs); }

		}; nik_ce auto _greater_than_or_equal_ = U_arg_overload<Overload::greater_than_or_equal>;

	// syntactic sugar:

		nik_ce auto _lt_		= _less_than_;
		nik_ce auto _gt_		= _greater_than_;
		nik_ce auto _lt_or_eq_		= _less_than_or_equal_;
		nik_ce auto _gt_or_eq_		= _greater_than_or_equal_;

/***********************************************************************************************************************/

// logical:

	// not_:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::not_, filler...>
		{
			template<typename T>
			nik_ces auto result(T v) { return !v; }

		}; nik_ce auto _not_ = U_arg_overload<Overload::not_>;

	// and_:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::and_, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... && vs); }

		}; nik_ce auto _and_ = U_arg_overload<Overload::and_>;

	// or_:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::or_, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... || vs); }

		}; nik_ce auto _or_ = U_arg_overload<Overload::or_>;

	// implies:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::implies, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return (!v1 || v2); }

		}; nik_ce auto _implies_ = U_arg_overload<Overload::implies>;

	// equivalent:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::equivalent, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return ((!v1 || v2) && (v1 || !v2)); }

		}; nik_ce auto _equivalent_ = U_arg_overload<Overload::equivalent>;

/***********************************************************************************************************************/

// arithmetic:

	// add:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::add, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... + vs); }

		}; nik_ce auto _add_ = U_arg_overload<Overload::add>;

	// subtract:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::subtract, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... - vs); }

		}; nik_ce auto _subtract_ = U_arg_overload<Overload::subtract>;

	// multiply:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::multiply, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... * vs); }

		}; nik_ce auto _multiply_ = U_arg_overload<Overload::multiply>;

	// divide:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::divide, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... / vs); }

		}; nik_ce auto _divide_ = U_arg_overload<Overload::divide>;

	// modulo:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::modulo, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... % vs); }

		}; nik_ce auto _modulo_ = U_arg_overload<Overload::modulo>;

/***********************************************************************************************************************/

// bitwise:

	// upshift:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::upshift, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return (v1 << v2); }

		}; nik_ce auto _upshift_ = U_arg_overload<Overload::upshift>;

	// downshift:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::downshift, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return (v1 >> v2); }

		}; nik_ce auto _downshift_ = U_arg_overload<Overload::downshift>;

/***********************************************************************************************************************/

// mutation:

	// assign:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::assign, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return v1 = v2; }

		}; nik_ce auto _assign_ = U_arg_overload<Overload::assign>;

	// dereference:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::dereference, filler...>
		{
			template<typename T>
			nik_ces auto & result(T v) { return *v; }

		}; nik_ce auto _dereference_ = U_arg_overload<Overload::dereference>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// higher order:

/***********************************************************************************************************************/

// basis:

	// cast:

		template<typename Type, nik_vp(V)(Type*)>
		struct T_grammar<Shape::argument, Pattern::higher_order, HigherOrder::cast, V>
		{
			template<typename T>
			nik_ces auto result(T v) { return Type(v); }

		}; template<auto V>
			nik_ce auto _cast_ = U_arg_higher_order<HigherOrder::cast, V>;

		// to_bool (syntactic sugar):

			nik_ce auto _to_bool_ = _cast_<U_store_T<bool>>;

	// constant:

		template<auto V>
		struct T_grammar<Shape::argument, Pattern::higher_order, HigherOrder::constant, V>
		{
			template<typename... Ts>
			nik_ces auto result(Ts...) { return V; }

		}; template<auto V>
			nik_ce auto _constant_ = U_arg_higher_order<HigherOrder::constant, V>;

	// wrap:

		template<auto f>
		struct T_grammar<Shape::argument, Pattern::higher_order, HigherOrder::wrap, f>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return f(vs...); }

		}; template<auto f>
			nik_ce auto _wrap_ = U_arg_higher_order<HigherOrder::wrap, f>;

	// bind:

		template<auto f, auto... ps>
		struct T_grammar<Shape::argument, Pattern::higher_order, HigherOrder::bind, f, ps...>
		{
			using F = T_store_U<f>;

			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return F::template result<ps..., Ts...>(vs...); }

		}; template<auto f, auto... ps>
			nik_ce auto _bind_ = U_arg_higher_order<HigherOrder::bind, f, ps...>;

		// apply (syntactic sugar):

			template<auto f>
			nik_ce auto _apply_ = _bind_<f>;

	// curry:

		template<auto f, auto... Vs>
		struct T_grammar<Shape::argument, Pattern::higher_order, HigherOrder::curry, f, Vs...>
		{
			using F = T_store_U<f>;

			template<typename... Ts>
			nik_ces auto result(Ts... vs)
				{ return F::template result<decltype(Vs)..., Ts...>(Vs..., vs...); }

		}; template<auto f, auto... Vs>
			nik_ce auto _curry_ = U_arg_higher_order<HigherOrder::curry, f, Vs...>;

		// comparison (syntactic sugar):

			// is_equal:

				template<auto V>
				nik_ce auto _is_equal_ = _curry_<_equal_, V>;

			// is_zero:

				nik_ce auto _is_zero_ = _is_equal_<_zero>;

			// is_less_than:

				template<auto V> nik_ce auto _is_less_than_		= _curry_<_gt_, V>;
				template<auto V> nik_ce auto _is_lt_			= _curry_<_gt_, V>;

			// is_less_than_or_equal:

				template<auto V> nik_ce auto _is_less_than_or_equal_	= _curry_<_gt_or_eq_, V>;
				template<auto V> nik_ce auto _is_lt_or_eq_		= _curry_<_gt_or_eq_, V>;

			// is_greater_than:

				template<auto V> nik_ce auto _is_greater_than_		= _curry_<_lt_, V>;
				template<auto V> nik_ce auto _is_gt_			= _curry_<_lt_, V>;

			// is_greater_than_or_equal:

				template<auto V> nik_ce auto _is_greater_than_or_equal_	= _curry_<_lt_or_eq_, V>;
				template<auto V> nik_ce auto _is_gt_or_eq_		= _curry_<_lt_or_eq_, V>;

		// arithmetic (syntactic sugar):

			// increment:

				template<auto V = _one> nik_ce auto _increment_		= _curry_<_add_, V>;

			// decrement:

				// Note: _increment_<-V> often has greater type safety than _decrement_<V>.

				template<auto V = _one> nik_ce auto _decrement_		= _curry_<_subtract_, V>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// continuation:

/***********************************************************************************************************************/

// basis:

	// first:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::continuation, Continuation::first, filler...>
		{
			template<typename T0, typename... Ts>
			nik_ces auto result(T0 v0, Ts... vs) { return v0; }

		}; nik_ce auto _first_ = U_arg_continuation<Continuation::first>;

	// second:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::continuation, Continuation::second, filler...>
		{
			template<typename T0, typename T1, typename... Ts>
			nik_ces auto result(T0 v0, T1 v1, Ts... vs) { return v1; }

		}; nik_ce auto _second_ = U_arg_continuation<Continuation::second>;

	// map:

		template<auto c, auto f>
		struct T_grammar<Shape::argument, Pattern::continuation, Continuation::map, c, f>
		{
			using C = T_store_U<c>;
			using F = T_store_U<f>;

			template<typename... Ts>
			nik_ces auto result(Ts... vs)
				{ return C::result(F::template result<Ts>(vs)...); }

		}; template<auto c, auto f>
			nik_ce auto _arg_map_ = U_arg_continuation<Continuation::map, c, f>;

		// syntactic sugar:

			template<auto f>
			nik_ce auto _arg_deref_ = _arg_map_<f, _dereference_>;

	// apply:

		template<auto c, auto... fs>
		struct T_grammar<Shape::argument, Pattern::continuation, Continuation::apply, c, fs...>
		{
			using C = T_store_U<c>;

			template<typename... Ts>
			nik_ces auto result(Ts... vs)
				{ return C::result(T_store_U<fs>::template result<Ts>(vs)...); }
		};

		template<auto c, auto... fs>
		nik_ce auto _arg_apply_ = U_arg_continuation<Continuation::apply, c, fs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// iterator:

/***********************************************************************************************************************/

// near linear:

	// multimap:

		template<auto f>
		struct T_grammar<Shape::argument, Pattern::iterator, Iterator::multimap, f>
		{
			using F = T_store_U<f>;

			template<typename Out, typename In, typename End, typename... Ins>
			nik_ces auto result(Out out, In in, End end, Ins... ins)
			{
				while (in != end)
				{
					*out = F::template result<In, Ins...>(in, ins...);
					++out; ++in; (++ins, ...);
				}

				return out;
			}

		}; template<auto f>
			nik_ce auto _multimap_ = U_arg_iterator<Iterator::multimap, f>;

	// multifold:

		template<auto f, auto init>
		struct T_grammar<Shape::argument, Pattern::iterator, Iterator::multifold, f, init>
		{
			using F = T_store_U<f>;

			template<typename Out, typename In, typename End, typename... Ins>
			nik_ces auto result(Out out, In in, End end, Ins... ins)
			{
				*out = init;

				while (in != end)
				{
					*out = F::template result<Out, In, Ins...>(out, in, ins...);
					++in; (++ins, ...);
				}

				return out;
			}

		}; template<auto f, auto init>
			nik_ce auto _multifold_ = U_arg_iterator<Iterator::multifold, f, init>;

	// multifind:

		template<auto p>
		struct T_grammar<Shape::argument, Pattern::iterator, Iterator::multifind, p>
		{
			using P = T_store_U<p>;

			template<typename In, typename End, typename... Ins>
			nik_ces auto result(In in, End end, Ins... ins)
			{
				while (in != end)
				{
					if (P::template result<In, Ins...>(in, ins...)) break;

					++in; (++ins, ...);
				}

				return in;
			}

		}; template<auto p>
			nik_ce auto _multifind_ = U_arg_iterator<Iterator::multifind, p>;

	// multisift:

		template<auto p>
		struct T_grammar<Shape::argument, Pattern::iterator, Iterator::multisift, p>
		{
			using P = T_store_U<p>;

			template<typename Out, typename In, typename End, typename... Ins>
			nik_ces auto result(Out out, In in, End end, Ins... ins)
			{
				while (in != end)
				{
					if (P::template result<In, Ins...>(in, ins...)) *(out++) = in;

					++in; (++ins, ...);
				}

				return out;
			}

		}; template<auto p>
			nik_ce auto _multisift_ = U_arg_iterator<Iterator::multisift, p>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array:

/***********************************************************************************************************************/

// meta:

	// is:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, Array::is, filler...>
		{
			template<typename T>         nik_ces auto result(T)       { return false; }
			template<typename T, auto S> nik_ces auto result(T(&)[S]) { return true; }

		}; nik_ce auto _is_array_ = U_arg_array<Array::is>;

	// type:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, Array::type, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(T(&)[S]) { return U_store_T<T>; }

		}; nik_ce auto _array_type_ = U_arg_array<Array::type>;

	// size:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, Array::size, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(T(&)[S]) { return S; }

		}; nik_ce auto _array_size_ = U_arg_array<Array::size>;

/***********************************************************************************************************************/

// basis:

	// begin:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, Array::begin, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(T(&a)[S]) { return a; }

		}; nik_ce auto _array_begin_ = U_arg_array<Array::begin>;

	// last:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, Array::last, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(T(&a)[S]) { return a + (S - 1); }

		}; nik_ce auto _array_last_ = U_arg_array<Array::last>;

	// end:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, Array::end, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(T(&a)[S]) { return a + S; }

		}; nik_ce auto _array_end_ = U_arg_array<Array::end>;

	// sift:

	//	template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
	//	nik_ces auto sift(nik_vp(indices)(T_pack_Vs<Is...>*))
	//	{
	//		nik_ce auto Size	= Leng + 1;
	//		nik_ce auto arr		= apply<Type, Size, IteratorModule::Sift, Leng, p>(Arr);
	//		nik_ce auto leng	= arr.value[Leng]; // [0] ?

	//		if nik_ce (leng != sizeof...(Is)) return arr;
	//		else return array<Type, arr.value[Is]...>;
	//	}

/***********************************************************************************************************************/

// 2^N:

	// log floor:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, Array::log_floor, filler...>
		{
			nik_ces auto array_end = T_store_U<_array_end_>::result(array_2_N);

			nik_ces gkey_type result(gcindex_type n)
			{
				gcindex_type *k = array_end;

				while (--k != array_2_N) if (*k <= n) break;

				return k - array_2_N;
			}

		}; nik_ce auto _log_floor_ = U_arg_array<Array::log_floor>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sequence:

/***********************************************************************************************************************/

// meta:

	// is:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::sequence, Sequence::is, filler...>
		{
			template<typename T>         nik_ces auto result(T)                      { return false; }
			template<typename T, auto S> nik_ces auto result(const sequence<T, S> &) { return true; }

		}; nik_ce auto _is_sequence_ = U_arg_sequence<Sequence::is>;

	// type:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::sequence, Sequence::type, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(const sequence<T, S> &) { return U_store_T<T>; }

		}; nik_ce auto _sequence_type_ = U_arg_sequence<Sequence::type>;

	// size:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::sequence, Sequence::size, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(const sequence<T, S> &) { return S; }

		}; nik_ce auto _sequence_size_ = U_arg_sequence<Sequence::size>;

/***********************************************************************************************************************/

// basis:

	// cons:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::sequence, Sequence::to_sequence, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return sequence({vs...}); }

		}; nik_ce auto _to_sequence_ = U_arg_sequence<Sequence::to_sequence>;

	// begin:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::sequence, Sequence::begin, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(sequence<T, S> & s) { return s.value; }

			template<typename T, auto S>
			nik_ces auto result(const sequence<T, S> & s) { return s.value; }

		}; nik_ce auto _sequence_begin_ = U_arg_sequence<Sequence::begin>;

	// last:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::sequence, Sequence::last, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(sequence<T, S> & s) { return s.value + (S - 1); }

			template<typename T, auto S>
			nik_ces auto result(const sequence<T, S> & s) { return s.value + (S - 1); }

		}; nik_ce auto _sequence_last_ = U_arg_sequence<Sequence::last>;

	// end:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::sequence, Sequence::end, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(sequence<T, S> & s) { return s + S; }

			template<typename T, auto S>
			nik_ces auto result(const sequence<T, S> & s) { return s + S; }

		}; nik_ce auto _sequence_end_ = U_arg_sequence<Sequence::end>;

	// apply:

		template<auto U, auto S, auto f>
		struct T_grammar<Shape::argument, Pattern::sequence, Sequence::apply, U, S, f>
		{
			using T = T_store_U<U>;
			using F = T_store_U<f>;

			template<typename In, typename End, typename... Ins>
			nik_ces auto result(In in, End end, Ins... ins)
			{
				sequence<T, S> s{};

				F::template result<T*, In, End, Ins...>(s.value, in, end, ins...);

				return s;
			}

		}; template<auto U, auto S, auto f>
			nik_ce auto _sequence_apply_ = U_arg_sequence<Sequence::apply, U, S, f>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

/***********************************************************************************************************************/

// meta:

	// is:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::tuple, Tuple::is, filler...>
		{
			template<typename T>     nik_ces auto result(T)                    { return false; }
			template<typename... Ts> nik_ces auto result(const tuple<Ts...> &) { return true; }

		}; nik_ce auto _is_tuple_ = U_arg_tuple<Tuple::is>;

	// type:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::tuple, Tuple::type, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(const tuple<Ts...> &) { return U_pack_Ts<Ts...>; }

		}; nik_ce auto _tuple_type_ = U_arg_tuple<Tuple::type>;

	// size:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::tuple, Tuple::size, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(const tuple<Ts...> &) { return sizeof...(Ts); }

		}; nik_ce auto _tuple_size_ = U_arg_tuple<Tuple::size>;

/***********************************************************************************************************************/

// basis:

	// tuple:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::tuple, Tuple::to_tuple, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return tuple<Ts...>(vs...); }

		}; nik_ce auto _to_tuple_ = U_arg_tuple<Tuple::to_tuple>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

