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

// constant:

/***********************************************************************************************************************/

// [0-10]:

	using key_type  = unsigned char;
	using ckey_type = key_type const;

	nik_ces key_type _zero		=   0;
	nik_ces key_type _one		=   1;
	nik_ces key_type _two		=   2;
	nik_ces key_type _three		=   3;
	nik_ces key_type _four		=   4;
	nik_ces key_type _five		=   5;
	nik_ces key_type _six		=   6;
	nik_ces key_type _seven		=   7;
	nik_ces key_type _eight		=   8;
	nik_ces key_type _nine		=   9;
	nik_ces key_type _ten		=  10;

// [2^0-2^9]:

	using index_type  = unsigned short;
	using cindex_type = index_type const;

	nik_ces index_type _2_0		=   1;
	nik_ces index_type _2_1		=   2;
	nik_ces index_type _2_2		=   4;
	nik_ces index_type _2_3		=   8;
	nik_ces index_type _2_4		=  16;
	nik_ces index_type _2_5		=  32;
	nik_ces index_type _2_6		=  64;
	nik_ces index_type _2_7		= 128;
	nik_ces index_type _2_8		= 256;
	nik_ces index_type _2_9		= 512;

	using depth_type  = unsigned short;
	using cdepth_type = depth_type const;

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
/***********************************************************************************************************************/

// packs:

/***********************************************************************************************************************/

// auto:

	template<auto...> struct T_store_Vs { };

	template<auto... Vs>
	nik_ce auto U_pack_Vs = store<T_store_Vs<Vs...>*>;

	nik_ce auto U_null_Vs = U_pack_Vs<>;

// typename:

	template<typename... Ts>
	nik_ce auto U_pack_Ts = U_pack_Vs<U_store_T<Ts>...>;

	nik_ce auto U_null_Ts = U_null_Vs;

// auto template:

	template<template<auto...> class> struct T_store_B { };

	template<template<auto...> class B>
	nik_ce auto U_store_B = U_store_T<T_store_B<B>>;

	template<template<auto...> class... Bs>
	nik_ce auto U_pack_Bs = U_pack_Vs<U_store_B<Bs>...>;

	nik_ce auto U_null_Bs = U_null_Vs;

// typename template:

	template<template<typename...> class> struct T_store_A { };

	template<template<typename...> class A>
	nik_ce auto U_store_A = U_store_T<T_store_A<A>>;

	template<template<typename...> class... As>
	nik_ce auto U_pack_As = U_pack_Vs<U_store_A<As>...>;

	nik_ce auto U_null_As = U_null_Vs;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

/***********************************************************************************************************************/

	template<typename... Ts> struct tuple { };

	template<typename T, typename... Ts>
	struct tuple<T, Ts...>
	{
		T value;
		tuple<Ts...> rest;

		nik_ce tuple(const T & v, const Ts &... vs) : value{v}, rest{vs...} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array:

	template<typename Type, Type... Vs>
	nik_ce Type array[] = { Vs... };

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// functions:

/***********************************************************************************************************************/

// reflection:

	template<typename> struct FunctionModule;

	template<typename OutType, typename... InTypes>
	struct FunctionModule<OutType(*)(InTypes...)>
	{
		nik_ces auto f_type	= U_store_T<OutType(*)(InTypes...)>;
		nik_ces auto arity	= sizeof...(InTypes);
		nik_ces auto out_type	= U_store_T<OutType>;
		nik_ces auto in_types	= U_pack_Ts<InTypes...>;
	};

	template<auto f>
	nik_ce auto f_type = FunctionModule<decltype(f)>::f_type;

	template<auto f>
	nik_ce auto arity = FunctionModule<decltype(f)>::arity;

	template<auto f>
	using T_out_type = T_store_U<FunctionModule<decltype(f)>::out_type>;

	template<auto f>
	nik_ce auto out_type = FunctionModule<decltype(f)>::out_type;

	template<auto f>
	nik_ce auto in_types = FunctionModule<decltype(f)>::in_types;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// overload:

	template<key_type, key_type, auto... filler> struct T_overload;

	template<key_type Key, key_type Op, auto... Vs>
	nik_ce auto U_overload = U_store_T<T_overload<Key, Op, Vs...>>;

/***********************************************************************************************************************/

	struct Overload
	{
		nik_ces key_type function			=  0;
		nik_ces key_type higher_order			=  1;
		nik_ces key_type alias				=  2;
	};

	// function:

		template<key_type Op>
		using T_function = T_overload<Overload::function, Op>;

		template<key_type Op>
		nik_ce auto U_function_T = U_store_T<T_function<Op>>;

	// higher order:

		template<key_type Op, auto... Ws>
		using T_higher_order = T_overload<Overload::higher_order, Op, Ws...>;

		template<key_type Op, auto... Ws>
		nik_ce auto U_higher_order_T = U_store_T<T_higher_order<Op, Ws...>>;

	// alias:

		template<key_type Op, auto... Ws>
		using T_alias = T_overload<Overload::alias, Op, Ws...>;

		template<key_type Op, auto... Ws>
		nik_ce auto U_alias_T = U_store_T<T_alias<Op, Ws...>>;

/***********************************************************************************************************************/

// dispatch:

	template<auto... Vs>
	nik_ce auto overload = U_pack_Vs<Vs...>;

	template<key_type Op, nik_vp(op)(T_overload<Overload::function, Op>*), auto... Vs>
	nik_ce auto overload<op, Vs...> = T_function<Op>::template result<decltype(Vs)...>(Vs...);

	template<key_type Op, auto... Ws, nik_vp(op)(T_overload<Overload::higher_order, Op, Ws...>*), auto... Vs>
	nik_ce auto overload<op, Vs...> = T_higher_order<Op, Ws...>::template result<decltype(Vs)...>(Vs...);

	template<key_type Op, auto... Ws, nik_vp(op)(T_overload<Overload::alias, Op, Ws...>*), auto... Vs>
	nik_ce auto overload<op, Vs...> = T_alias<Op, Ws...>::template result<Vs...>;

/***********************************************************************************************************************/

// operator:

	struct Operator
	{
		// function:

			// basis:

			nik_ces key_type id				=  0;

			// comparison:

			nik_ces key_type equal				=  1;
			nik_ces key_type not_equal			=  2;

			nik_ces key_type less_than			=  3;
			nik_ces key_type less_than_or_equal		=  4;
			nik_ces key_type greater_than			=  5;
			nik_ces key_type greater_than_or_equal		=  6;

			// logical:

			nik_ces key_type not_				=  7;
			nik_ces key_type and_				=  8;
			nik_ces key_type or_				=  9;
			nik_ces key_type implies			= 10;
			nik_ces key_type equivalent			= 11;

			// arithmetic:

			nik_ces key_type add				= 12;
			nik_ces key_type subtract			= 13;
			nik_ces key_type multiply			= 14;
			nik_ces key_type divide				= 15;
			nik_ces key_type modulo				= 16;

			// bitwise:

			nik_ces key_type upshift			= 17;
			nik_ces key_type downshift			= 18;

			// algebraic:

			nik_ces key_type tuple				= 19;

			// mutation:

			nik_ces key_type assign				= 20;
			nik_ces key_type dereference			= 21;

			// block:

			nik_ces key_type filter				= 22;

		// higher order:

			// basis:

			nik_ces key_type cast				=  0;
			nik_ces key_type constant			=  1;

			nik_ces key_type apply				=  2;
			nik_ces key_type bind				=  3;
			nik_ces key_type curry				=  4;

			// comparison:

			nik_ces key_type match				=  5;

			// curried:

				// comparison:

				nik_ces key_type is_equal		=  6;
				nik_ces key_type is_zero		=  7;

				// arithmetic:

				nik_ces key_type increment		=  8;
				nik_ces key_type decrement		=  9;

		// alias:

			// basis:

			nik_ces key_type type_to_const			=  0;

			nik_ces key_type list_to_array			=  1;
			nik_ces key_type array_to_list			=  2;

			nik_ces key_type template_to_list		=  3;
			nik_ces key_type list_to_template		=  4;

			// comparison:

			nik_ces key_type same				=  5;
			nik_ces key_type csame				=  6;
			nik_ces key_type is_int_type			=  7;
			nik_ces key_type not_int_type			=  8;

			// functional:

			nik_ces key_type to_list			=  9;
			nik_ces key_type length				= 10;
			nik_ces key_type map				= 11;

			nik_ces key_type is_null			= 12;
			nik_ces key_type car				= 13;
			nik_ces key_type cdr				= 14;
			nik_ces key_type cadr				= 15;
			nik_ces key_type find				= 16;

			// variadic:

			nik_ces key_type zip				= 17;
			nik_ces key_type unite				= 18;
			nik_ces key_type cons				= 19;
			nik_ces key_type push				= 20;
			nik_ces key_type unpack				= 21;

			// grammatical:

			nik_ces key_type custom				= 22;
			nik_ces key_type procedure			= 23;
			nik_ces key_type method				= 24;
			nik_ces key_type tailor				= 25;

			nik_ces key_type partial			= 26;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// function:

/***********************************************************************************************************************/

// basis:

	// id:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::id, filler...>
		{
			template<typename T>
			nik_ces auto result(T v) { return v; }

		}; nik_ce auto _id_ = U_function_T<Operator::id>;

/***********************************************************************************************************************/

// comparison:

	// equal:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... == vs); }

		}; nik_ce auto _equal_ = U_function_T<Operator::equal>;

	// not_equal:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::not_equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... != vs); }

		}; nik_ce auto _not_equal_ = U_function_T<Operator::not_equal>;

	// less_than:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::less_than, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... < vs); }

		}; nik_ce auto _less_than_ = U_function_T<Operator::less_than>;

	// less_than_or_equal:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::less_than_or_equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... <= vs); }

		}; nik_ce auto _less_than_or_equal_ = U_function_T<Operator::less_than_or_equal>;

	// greater_than:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::greater_than, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... > vs); }

		}; nik_ce auto _greater_than_ = U_function_T<Operator::greater_than>;

	// greater_than_or_equal:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::greater_than_or_equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... >= vs); }

		}; nik_ce auto _greater_than_or_equal_ = U_function_T<Operator::greater_than_or_equal>;

/***********************************************************************************************************************/

// logical:

	// not_:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::not_, filler...>
		{
			template<typename T>
			nik_ces auto result(T v) { return !v; }

		}; nik_ce auto _not_ = U_function_T<Operator::not_>;

	// and_:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::and_, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... && vs); }

		}; nik_ce auto _and_ = U_function_T<Operator::and_>;

	// or_:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::or_, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... || vs); }

		}; nik_ce auto _or_ = U_function_T<Operator::or_>;

	// implies:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::implies, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return (!v1 || v2); }

		}; nik_ce auto _implies_ = U_function_T<Operator::implies>;

	// equivalent:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::equivalent, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return ((!v1 || v2) && (v1 || !v2)); }

		}; nik_ce auto _equivalent_ = U_function_T<Operator::equivalent>;

/***********************************************************************************************************************/

// arithmetic:

	// add:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::add, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... + vs); }

		}; nik_ce auto _add_ = U_function_T<Operator::add>;

	// subtract:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::subtract, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... - vs); }

		}; nik_ce auto _subtract_ = U_function_T<Operator::subtract>;

	// multiply:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::multiply, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... * vs); }

		}; nik_ce auto _multiply_ = U_function_T<Operator::multiply>;

	// divide:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::divide, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... / vs); }

		}; nik_ce auto _divide_ = U_function_T<Operator::divide>;

	// modulo:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::modulo, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... % vs); }

		}; nik_ce auto _modulo_ = U_function_T<Operator::modulo>;

/***********************************************************************************************************************/

// bitwise:

	// upshift:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::upshift, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return (v1 << v2); }

		}; nik_ce auto _upshift_ = U_function_T<Operator::upshift>;

	// downshift:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::downshift, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return (v1 >> v2); }

		}; nik_ce auto _downshift_ = U_function_T<Operator::downshift>;

/***********************************************************************************************************************/

// algebraic:

	// tuple:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::tuple, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return tuple<Ts...>(vs...); }

		}; nik_ce auto _tuple_ = U_function_T<Operator::tuple>;

// mutation:

	// assign:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::assign, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return v1 = v2; }

		}; nik_ce auto _assign_ = U_function_T<Operator::assign>;

	// dereference:

		template<auto... filler>
		struct T_overload<Overload::function, Operator::dereference, filler...>
		{
			template<typename T>
			nik_ces auto & result(T v) { return *v; }

		}; nik_ce auto _dereference_ = U_function_T<Operator::dereference>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// higher order:

/***********************************************************************************************************************/

// basis:

	// cast:

		template<typename Type, nik_vp(V)(Type*)>
		struct T_overload<Overload::higher_order, Operator::cast, V>
		{
			template<typename T>
			nik_ces auto result(T v) { return Type(v); }

		}; template<auto V>
			nik_ce auto _cast_ = U_higher_order_T<Operator::cast, V>;

	// to_bool:

		nik_ce auto _to_bool_ = _cast_<U_store_T<bool>>;

	// constant:

		template<auto V>
		struct T_overload<Overload::higher_order, Operator::constant, V>
		{
			template<typename... Ts>
			nik_ces auto result(Ts...) { return V; }

		}; template<auto V>
			nik_ce auto _constant_ = U_higher_order_T<Operator::constant, V>;

	// apply:

		template<auto f>
		struct T_overload<Overload::higher_order, Operator::apply, f>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return f(vs...); }

		}; template<auto f>
			nik_ce auto _apply_ = U_higher_order_T<Operator::apply, f>;

	// bind:

		template<auto f, auto... ps>
		struct T_overload<Overload::higher_order, Operator::bind, f, ps...>
		{
			using F = T_store_U<f>;

			template<typename... Ts>
			nik_ces auto result(Ts... vs)
				{ return F::template result<ps..., Ts...>(vs...); }

		}; template<auto f, auto... ps>
			nik_ce auto _bind_ = U_higher_order_T<Operator::bind, f, ps...>;

	// curry:

		template<auto f, auto... Vs>
		struct T_overload<Overload::higher_order, Operator::curry, f, Vs...>
		{
			using F = T_store_U<f>;

			template<typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				return F::template result<decltype(Vs)..., Ts...>(Vs..., vs...);
			}

		}; template<auto f, auto... Vs>
			nik_ce auto _curry_ = U_higher_order_T<Operator::curry, f, Vs...>;

		// auto template:

			template<auto... Ws>
			struct B_curry
			{
				template<auto... Vs>
				using result = T_higher_order<Operator::curry, Ws..., Vs...>;

			}; template<auto... Ws>
				nik_ce auto H_curry = U_store_B<B_curry<Ws...>::template result>;

/***********************************************************************************************************************/

// comparison:

	// match:

		template<auto p>
		struct T_overload<Overload::higher_order, Operator::match, p>
		{
			using P = T_store_U<p>;

			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2)
			{
				T1 in  = v1;
				T1 end = v1 + v2;

				while (in != end && !P::result(*in)) ++in;

				return in - v1;
			}

		}; template<auto p = _to_bool_>
			nik_ce auto _match_ = U_higher_order_T<Operator::match, p>;

/***********************************************************************************************************************/

// curried:

	// comparison:

		// is_equal:

			template<auto V>
			nik_ce auto _is_equal_ = _curry_<_equal_, V>;

		// is_zero:

			nik_ce auto _is_zero_ = _is_equal_<_zero>;

	// arithmetic:

		// increment:

			template<auto V = _one>
			nik_ce auto _increment_ = _curry_<_add_, V>;

		// decrement:

			template<auto V = _one>
			nik_ce auto _decrement_ = _curry_<_subtract_, V>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// alias (variable template):

	// Assumes variadic input, for pack input see "Operator::unpack".

/***********************************************************************************************************************/

// specializations:

	template<key_type Op, auto... Vs>
	nik_ce auto alias = U_pack_Vs<Op, Vs...>;

	template<auto V0, auto V1> nik_ce auto alias<Operator::same, V0, V1> = false;
	template<auto V>           nik_ce auto alias<Operator::same, V , V > = true;

	template<auto V>                         nik_ce auto alias<Operator::is_int_type, V> = false;
	template<nik_vp(V)(unsigned char     *)> nik_ce auto alias<Operator::is_int_type, V> = true;
	template<nik_vp(V)(  signed char     *)> nik_ce auto alias<Operator::is_int_type, V> = true;
	template<nik_vp(V)(unsigned short    *)> nik_ce auto alias<Operator::is_int_type, V> = true;
	template<nik_vp(V)(  signed short    *)> nik_ce auto alias<Operator::is_int_type, V> = true;
	template<nik_vp(V)(unsigned int      *)> nik_ce auto alias<Operator::is_int_type, V> = true;
	template<nik_vp(V)(  signed int      *)> nik_ce auto alias<Operator::is_int_type, V> = true;
	template<nik_vp(V)(unsigned long     *)> nik_ce auto alias<Operator::is_int_type, V> = true;
	template<nik_vp(V)(  signed long     *)> nik_ce auto alias<Operator::is_int_type, V> = true;
	template<nik_vp(V)(unsigned long long*)> nik_ce auto alias<Operator::is_int_type, V> = true;
	template<nik_vp(V)(  signed long long*)> nik_ce auto alias<Operator::is_int_type, V> = true;

	template<template<auto...> typename B, auto... Vs, nik_vp(p)(B<Vs...>*)>
	nik_ce auto alias<Operator::template_to_list, p> = U_pack_Vs<Vs...>;

	template
	<
		auto... Vs, nik_vp(p)(T_store_Vs<Vs...>*),
		template<auto...> typename B, nik_vp(b)(T_store_B<B>*)
	>
	nik_ce auto alias<Operator::list_to_template, p, b> = U_store_T<B<Vs...>>;

	template<auto Op, auto... Ws, nik_vp(p)(T_store_Vs<Ws...>*), auto... Vs>
	nik_ce auto alias<Operator::zip, Op, p, Vs...> = U_pack_Vs<overload<Op, Ws, Vs>...>;

	template
	<
		auto... Xs, nik_vp(p0)(T_store_Vs<Xs...>*),
		auto... Ws, nik_vp(p1)(T_store_Vs<Ws...>*),
		auto... Vs
	>
	nik_ce auto alias<Operator::unite, p0, p1, Vs...> = U_pack_Vs<Xs..., Vs..., Ws...>;

	template<auto... Ws, nik_vp(p)(T_store_Vs<Ws...>*), auto Op, auto... Vs>
	nik_ce auto alias<Operator::unpack, p, Op, Vs...> = overload<Op, Vs..., Ws...>;

	template<auto Op, auto... Ws, nik_vp(p)(T_store_Vs<Ws...>*), auto... Vs>
	nik_ce auto alias<Operator::method, Op, p, Vs...> = T_store_U<Op>::template result<Ws...>(Vs...);

	template<auto Op, auto... Ws, nik_vp(p)(T_store_Vs<Ws...>*), auto... Vs>
	nik_ce auto alias<Operator::tailor, Op, p, Vs...> = T_store_U<Op>::template result<Vs...>(Ws...);

/***********************************************************************************************************************/

// basis:

	// type to const:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::type_to_const, filler...>
		{
			template<auto U>
			nik_ces auto result = U_store_T<T_store_U<U> const>;

		}; nik_ce auto U_type_to_const = U_alias_T<Operator::type_to_const>;

	// list to array:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::list_to_array, filler...>
		{
			template<auto U, auto... Vs>
			nik_ces auto result = array<T_store_U<U>, Vs...>;

		}; nik_ce auto U_list_to_array = U_alias_T<Operator::list_to_array>;

	// from array:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::array_to_list, filler...>
		{
			template<auto A, auto... Is>
			nik_ces auto result = U_pack_Vs<A[Is]...>;

		}; nik_ce auto U_array_to_list = U_alias_T<Operator::array_to_list>;

	// template to list:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::template_to_list, filler...>
		{
			template<auto p>
			nik_ces auto result = alias<Operator::template_to_list, p>;

		}; nik_ce auto U_template_to_list = U_alias_T<Operator::template_to_list>;

	// list to template:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::list_to_template, filler...>
		{
			template<auto p, auto b>
			nik_ces auto result = alias<Operator::list_to_template, p, b>;

		}; nik_ce auto U_list_to_template = U_alias_T<Operator::list_to_template>;

	// same:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::same, filler...>
		{
			template<auto V0, auto V1>
			nik_ces auto result = alias<Operator::same, V0, V1>;

		}; nik_ce auto U_same = U_alias_T<Operator::same>;

	// csame:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::csame, filler...>
		{
			using T_type_to_const = T_alias<Operator::type_to_const>;

			template<auto V0, auto V1>
			nik_ces auto result = alias
			<
				Operator::same,
				T_type_to_const::template result<V0>,
				T_type_to_const::template result<V1>
			>;

		}; nik_ce auto U_csame = U_alias_T<Operator::csame>;

	// is_int_type:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::is_int_type, filler...>
		{
			template<auto V>
			nik_ces auto result = alias<Operator::is_int_type, V>;

		}; nik_ce auto U_is_int_type = U_alias_T<Operator::is_int_type>;

	// not_int_type:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::not_int_type, filler...>
		{
			template<auto V>
			nik_ces auto result = ! alias<Operator::is_int_type, V>;

		}; nik_ce auto U_not_int_type = U_alias_T<Operator::not_int_type>;

/***********************************************************************************************************************/

// functional:

	// to list:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::to_list, filler...>
		{
			template<auto... Vs>
			nik_ces auto result = U_pack_Vs<Vs...>;

		}; nik_ce auto U_to_list = U_alias_T<Operator::to_list>;

	// length:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::length, filler...>
		{
			template<auto... Vs>
			nik_ces auto result = sizeof...(Vs);

		}; nik_ce auto U_length = U_alias_T<Operator::length>;

	// map:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::map, filler...>
		{
			template<auto Op, auto... Vs>
			nik_ces auto result = U_pack_Vs<overload<Op, Vs>...>;

		}; nik_ce auto U_map = U_alias_T<Operator::map>;

	// is_null:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::is_null, filler...>
		{
			template<auto... Vs>
			nik_ces auto result = (sizeof...(Vs) == 0);

		}; nik_ce auto U_is_null = U_alias_T<Operator::is_null>;

	// car:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::car, filler...>
		{
			template<auto V0, auto... Vs>
			nik_ces auto result = V0;

		}; nik_ce auto U_car = U_alias_T<Operator::car>;

	// cdr:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::cdr, filler...>
		{
			template<auto V0, auto... Vs>
			nik_ces auto result = U_pack_Vs<Vs...>;

		}; nik_ce auto U_cdr = U_alias_T<Operator::cdr>;

	// cadr:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::cadr, filler...>
		{
			template<auto V0, auto V1, auto... Vs>
			nik_ces auto result = V1;

		}; nik_ce auto U_cadr = U_alias_T<Operator::cadr>;

	// find:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::find, filler...>
		{
			nik_ces auto match = T_higher_order<Operator::match, _to_bool_>::template result
			<
				bool const*, index_type
			>;

			template<auto Op, auto... Vs>
			nik_ces auto result = match(array<bool const, overload<Op, Vs>...>, sizeof...(Vs));

		}; nik_ce auto U_find = U_alias_T<Operator::find>;

/***********************************************************************************************************************/

// variadic:

	// zip:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::zip, filler...>
		{
			template<auto Op, auto p, auto... Vs>
			nik_ces auto result = alias<Operator::zip, Op, p, Vs...>;

		}; nik_ce auto U_zip = U_alias_T<Operator::zip>;

	// unite:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::unite, filler...>
		{
			template<auto p0, auto p1, auto... Vs>
			nik_ces auto result = alias<Operator::unite, p0, p1, Vs...>;

		}; nik_ce auto U_unite = U_alias_T<Operator::unite>;

	// cons:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::cons, filler...>
		{
			template<auto p, auto... Vs>
			nik_ces auto result = alias<Operator::unite, U_null_Vs, p, Vs...>;

		}; nik_ce auto U_cons = U_alias_T<Operator::cons>;

	// push:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::push, filler...>
		{
			template<auto p, auto... Vs>
			nik_ces auto result = alias<Operator::unite, p, U_null_Vs, Vs...>;

		}; nik_ce auto U_push = U_alias_T<Operator::push>;

	// unpack:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::unpack, filler...>
		{
			template<auto p, auto Op, auto... Vs>
			nik_ces auto result = alias<Operator::unpack, p, Op, Vs...>;

		}; nik_ce auto U_unpack = U_alias_T<Operator::unpack>;

/***********************************************************************************************************************/

// grammatical:

	// custom:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::custom, filler...>
		{
			template<auto Op, auto... Vs>
			nik_ces auto result = T_store_U<Op>::template result<Vs...>;

		}; nik_ce auto U_custom = U_alias_T<Operator::custom>;

	// procedure:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::procedure, filler...>
		{
			template<auto Op, auto... Vs>
			nik_ces auto result = T_store_U<Op>::result(Vs...);

		}; nik_ce auto U_procedure = U_alias_T<Operator::procedure>;

	// method:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::method, filler...>
		{
			template<auto... Vs>
			nik_ces auto result = alias<Operator::method, Vs...>;

		}; nik_ce auto U_method = U_alias_T<Operator::method>;

	// tailor:

		template<auto... filler>
		struct T_overload<Overload::alias, Operator::tailor, filler...>
		{
			template<auto... Vs>
			nik_ces auto result = alias<Operator::tailor, Vs...>;

		}; nik_ce auto U_tailor = U_alias_T<Operator::tailor>;

	// partial:

		template<auto... Ws>
		struct T_overload<Overload::alias, Operator::partial, Ws...>
		{
			template<auto... Vs>
			nik_ces auto result = overload<Ws..., Vs...>;

		}; template<auto... Ws>
			nik_ce auto U_partial = U_alias_T<Operator::partial, Ws...>;

		// auto template:

			template<auto... Ws>
			struct B_partial
			{
				template<auto... Vs>
				using result = T_alias<Operator::partial, Ws..., Vs...>;

			}; template<auto... Ws>
				nik_ce auto H_partial = U_store_B<B_partial<Ws...>::template result>;

/***********************************************************************************************************************/

// syntactic sugar:

	template<auto Op, auto... Vs>
	nik_ce auto map_ = T_alias<Operator::map>::template result<Op, Vs...>;

	template<auto Op, auto... Vs>
	nik_ce auto find_ = T_alias<Operator::find>::template result<Op, Vs...>;

	template<auto Op, auto p, auto... Vs>
	nik_ce auto zip_ = T_alias<Operator::zip>::template result<Op, p, Vs...>;

	template<auto p, auto Op, auto... Vs>
	nik_ce auto unpack_ = T_alias<Operator::unpack>::template result<p, Op, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

