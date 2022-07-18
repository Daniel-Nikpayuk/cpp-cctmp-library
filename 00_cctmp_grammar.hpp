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

// array:

	template<typename Type, Type... Vs>
	nik_ce Type array[] = { Vs... };

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

// grammar:

	template<key_type, auto, auto...> struct T_grammar;

	template<key_type Key, key_type Op, auto... Ws>
	nik_ce auto U_grammar = U_store_T<T_grammar<Key, Op, Ws...>>;

/***********************************************************************************************************************/

// names:

	struct Grammar
	{
		nik_ces key_type function		= 0;
		nik_ces key_type higher_order		= 1;
		nik_ces key_type alias			= 2;
	};

/***********************************************************************************************************************/

// overload:

	// Specializations are defined in the alias subsection,
	// otherwise this defaults to calling variable templates.

	template<auto Op, auto... Vs>
	nik_ce auto overload = T_store_U<Op>::template result<Vs...>;

// function:

	template<key_type Op>
	using T_function = T_grammar<Grammar::function, Op>;

	template<key_type Op>
	nik_ce auto U_function = U_store_T<T_function<Op>>;

// higher order:

	template<key_type Op, auto... Ws>
	using T_higher_order = T_grammar<Grammar::higher_order, Op, Ws...>;

	template<key_type Op, auto... Ws>
	nik_ce auto U_higher_order = U_store_T<T_higher_order<Op, Ws...>>;

// alias:

	// Allows for the currying of overloads.

	template<auto Op, auto... Ws>
	struct T_grammar<Grammar::alias, Op, Ws...>
	{
		template<auto... Vs>
		nik_ces auto result = overload<Op, Ws..., Vs...>;
	};

	template<auto Op, auto... Ws>
	using T_alias = T_grammar<Grammar::alias, Op, Ws...>;

	template<auto Op, auto... Ws>
	nik_ce auto U_alias = U_store_T<T_alias<Op, Ws...>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// function:

/***********************************************************************************************************************/

// operator:

	struct Function
	{
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
	};

/***********************************************************************************************************************/

// basis:

	// id:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::id, filler...>
		{
			template<typename T>
			nik_ces auto result(T v) { return v; }

		}; nik_ce auto _id_ = U_function<Function::id>;

/***********************************************************************************************************************/

// comparison:

	// equal:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... == vs); }

		}; nik_ce auto _equal_ = U_function<Function::equal>;

	// not_equal:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::not_equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... != vs); }

		}; nik_ce auto _not_equal_ = U_function<Function::not_equal>;

	// less_than:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::less_than, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... < vs); }

		}; nik_ce auto _less_than_ = U_function<Function::less_than>;

	// less_than_or_equal:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::less_than_or_equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... <= vs); }

		}; nik_ce auto _less_than_or_equal_ = U_function<Function::less_than_or_equal>;

	// greater_than:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::greater_than, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... > vs); }

		}; nik_ce auto _greater_than_ = U_function<Function::greater_than>;

	// greater_than_or_equal:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::greater_than_or_equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... >= vs); }

		}; nik_ce auto _greater_than_or_equal_ = U_function<Function::greater_than_or_equal>;

/***********************************************************************************************************************/

// logical:

	// not_:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::not_, filler...>
		{
			template<typename T>
			nik_ces auto result(T v) { return !v; }

		}; nik_ce auto _not_ = U_function<Function::not_>;

	// and_:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::and_, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... && vs); }

		}; nik_ce auto _and_ = U_function<Function::and_>;

	// or_:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::or_, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... || vs); }

		}; nik_ce auto _or_ = U_function<Function::or_>;

	// implies:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::implies, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return (!v1 || v2); }

		}; nik_ce auto _implies_ = U_function<Function::implies>;

	// equivalent:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::equivalent, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return ((!v1 || v2) && (v1 || !v2)); }

		}; nik_ce auto _equivalent_ = U_function<Function::equivalent>;

/***********************************************************************************************************************/

// arithmetic:

	// add:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::add, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... + vs); }

		}; nik_ce auto _add_ = U_function<Function::add>;

	// subtract:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::subtract, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... - vs); }

		}; nik_ce auto _subtract_ = U_function<Function::subtract>;

	// multiply:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::multiply, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... * vs); }

		}; nik_ce auto _multiply_ = U_function<Function::multiply>;

	// divide:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::divide, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... / vs); }

		}; nik_ce auto _divide_ = U_function<Function::divide>;

	// modulo:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::modulo, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... % vs); }

		}; nik_ce auto _modulo_ = U_function<Function::modulo>;

/***********************************************************************************************************************/

// bitwise:

	// upshift:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::upshift, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return (v1 << v2); }

		}; nik_ce auto _upshift_ = U_function<Function::upshift>;

	// downshift:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::downshift, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return (v1 >> v2); }

		}; nik_ce auto _downshift_ = U_function<Function::downshift>;

/***********************************************************************************************************************/

// algebraic:

	// tuple:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::tuple, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return tuple<Ts...>(vs...); }

		}; nik_ce auto _tuple_ = U_function<Function::tuple>;

// mutation:

	// assign:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::assign, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return v1 = v2; }

		}; nik_ce auto _assign_ = U_function<Function::assign>;

	// dereference:

		template<auto... filler>
		struct T_grammar<Grammar::function, Function::dereference, filler...>
		{
			template<typename T>
			nik_ces auto & result(T v) { return *v; }

		}; nik_ce auto _dereference_ = U_function<Function::dereference>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// higher order:

/***********************************************************************************************************************/

	struct HigherOrder
	{
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
	};

/***********************************************************************************************************************/

// basis:

	// cast:

		template<typename Type, nik_vp(V)(Type*)>
		struct T_grammar<Grammar::higher_order, HigherOrder::cast, V>
		{
			template<typename T>
			nik_ces auto result(T v) { return Type(v); }

		}; template<auto V>
			nik_ce auto _cast_ = U_higher_order<HigherOrder::cast, V>;

	// to_bool:

		nik_ce auto _to_bool_ = _cast_<U_store_T<bool>>;

	// constant:

		template<auto V>
		struct T_grammar<Grammar::higher_order, HigherOrder::constant, V>
		{
			template<typename... Ts>
			nik_ces auto result(Ts...) { return V; }

		}; template<auto V>
			nik_ce auto _constant_ = U_higher_order<HigherOrder::constant, V>;

	// apply:

		template<auto f>
		struct T_grammar<Grammar::higher_order, HigherOrder::apply, f>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return f(vs...); }

		}; template<auto f>
			nik_ce auto _apply_ = U_higher_order<HigherOrder::apply, f>;

	// bind:

		template<auto f, auto... ps>
		struct T_grammar<Grammar::higher_order, HigherOrder::bind, f, ps...>
		{
			using F = T_store_U<f>;

			template<typename... Ts>
			nik_ces auto result(Ts... vs)
				{ return F::template result<ps..., Ts...>(vs...); }

		}; template<auto f, auto... ps>
			nik_ce auto _bind_ = U_higher_order<HigherOrder::bind, f, ps...>;

	// curry:

		template<auto f, auto... Vs>
		struct T_grammar<Grammar::higher_order, HigherOrder::curry, f, Vs...>
		{
			using F = T_store_U<f>;

			template<typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				return F::template result<decltype(Vs)..., Ts...>(Vs..., vs...);
			}

		}; template<auto f, auto... Vs>
			nik_ce auto _curry_ = U_higher_order<HigherOrder::curry, f, Vs...>;

/***********************************************************************************************************************/

// comparison:

	// match:

		template<auto p>
		struct T_grammar<Grammar::higher_order, HigherOrder::match, p>
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
			nik_ce auto _match_ = U_higher_order<HigherOrder::match, p>;

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

	// Assumes variadic input, for pack input see "Alias::unpack".

/***********************************************************************************************************************/

	struct Alias
	{
		// grammatical:

			nik_ces key_type custom				=  0;
			nik_ces key_type nested				=  1;
			nik_ces key_type procedure			=  2;
			nik_ces key_type method				=  3;
			nik_ces key_type tailor				=  4;

		// basis:

			nik_ces key_type type_to_const			=  5;
			nik_ces key_type if_then_else			=  6;
			nik_ces key_type list_id			=  7;

		// comparison:

			nik_ces key_type same				=  8;
			nik_ces key_type csame				=  9;
			nik_ces key_type similar			= 10;
			nik_ces key_type is_int_type			= 11;
			nik_ces key_type not_int_type			= 12;

		// functional:

			nik_ces key_type to_list			= 13;
			nik_ces key_type array_to_list			= 14;
			nik_ces key_type to_array			= 15;
			nik_ces key_type to_tuple			= 16;

			nik_ces key_type is_null			= 17;
			nik_ces key_type length				= 18;

			nik_ces key_type car				= 19;
			nik_ces key_type cdr				= 20;
			nik_ces key_type cadr				= 21;

			nik_ces key_type map				= 22;
			nik_ces key_type find				= 23;

		// variadic:

			nik_ces key_type f0_unpack			= 24;
			nik_ces key_type f1_unpack			= 25;
			nik_ces key_type f2_unpack			= 26;

			nik_ces key_type b0_unpack			= 27;
			nik_ces key_type b1_unpack			= 28;
			nik_ces key_type b2_unpack			= 29;

			nik_ces key_type list_to_list			= 30;
			nik_ces key_type list_to_array			= 31;

			nik_ces key_type zip				= 32;
			nik_ces key_type unite				= 33;
			nik_ces key_type cons				= 34;
			nik_ces key_type push				= 35;
	};

/***********************************************************************************************************************/

// grammatical:

	// function:

		template<key_type Op, nik_vp(op)(T_function<Op>*), auto... Vs>
		nik_ce auto overload<op, Vs...> = T_function<Op>::template result<decltype(Vs)...>(Vs...);

	// higher order:

		template<key_type Op, auto... Ws, nik_vp(op)(T_higher_order<Op, Ws...>*), auto... Vs>
		nik_ce auto overload<op, Vs...> = T_higher_order<Op, Ws...>::template result<decltype(Vs)...>(Vs...);

	// alias (optimization):

		template<auto Op, auto... Ws, nik_vp(op)(T_alias<Op, Ws...>*), auto... Vs>
		nik_ce auto overload<op, Vs...> = overload<Op, Ws..., Vs...>;

/***********************************************************************************************************************/

// specializations:

	// custom:

		// In appearance this is redundant, but is in fact necessary for compile time register machines.

		template<auto Op, auto... Vs>
		nik_ce auto overload<Alias::custom, Op, Vs...> = T_store_U<Op>::template result<Vs...>;

		nik_ce auto _custom_ = Alias::custom;

	// nested:

		template<auto d, auto Op, auto... Vs>
		nik_ce auto overload<Alias::nested, d, Op, Vs...> = T_store_U<Op>::template result<d, Vs...>;

		nik_ce auto _nested_ = Alias::nested;

	// procedure:

		template<auto Op, auto... Vs>
		nik_ce auto overload<Alias::procedure, Op, Vs...> = T_store_U<Op>::result(Vs...);

		nik_ce auto _procedure_ = Alias::procedure;

	// method:

		template<auto Op, template<auto...> typename B, auto... Ws, nik_vp(p)(B<Ws...>*), auto... Vs>
		nik_ce auto overload<Alias::method, Op, p, Vs...> = T_store_U<Op>::template result<Ws...>(Vs...);

		nik_ce auto _method_ = Alias::method;

	// tailor:

		template<auto Op, template<auto...> typename B, auto... Ws, nik_vp(p)(B<Ws...>*), auto... Vs>
		nik_ce auto overload<Alias::tailor, Op, p, Vs...> = T_store_U<Op>::template result<Vs...>(Ws...);

		nik_ce auto _tailor_ = Alias::tailor;

/***********************************************************************************************************************/

// basis:

	// type to const:

		template<auto U>
		nik_ce auto overload<Alias::type_to_const, U> = U_store_T<T_store_U<U> const>;

		nik_ce auto _type_to_const_ = Alias::type_to_const;

	// if then else:

		template<auto ante, auto conse> nik_ce auto overload<Alias::if_then_else, true , ante, conse> = ante;
		template<auto ante, auto conse> nik_ce auto overload<Alias::if_then_else, false, ante, conse> = conse;

		nik_ce auto _if_then_else_ = Alias::if_then_else;

	// list id:

		template<template<auto...> typename B, auto... Vs, nik_vp(p)(B<Vs...>*)>
		nik_ce auto overload<Alias::list_id, p> = U_store_B<B>;

		nik_ce auto _list_id_ = Alias::list_id;

/***********************************************************************************************************************/

// comparison:

	// same:

		template<auto V0, auto V1> nik_ce auto overload<Alias::same, V0, V1> = false;
		template<auto V>           nik_ce auto overload<Alias::same, V , V > = true;

		nik_ce auto _same_ = Alias::same;

	// csame:

		template<auto V0, auto V1>
		nik_ce auto overload<Alias::csame, V0, V1> = overload
		<
			Alias::same,
			overload<Alias::type_to_const, V0>,
			overload<Alias::type_to_const, V1>
		>;

		nik_ce auto _csame_ = Alias::csame;

	// similar:

		template<auto V0, auto V1>
		nik_ce auto overload<Alias::similar, V0, V1> = overload
		<
			Alias::same,
			overload<Alias::list_id, V0>,
			overload<Alias::list_id, V1>
		>;

		nik_ce auto _similar_ = Alias::similar;

	// is_int_type:

		template<auto V>                         nik_ce auto overload<Alias::is_int_type, V> = false;
		template<nik_vp(V)(unsigned char     *)> nik_ce auto overload<Alias::is_int_type, V> = true;
		template<nik_vp(V)(  signed char     *)> nik_ce auto overload<Alias::is_int_type, V> = true;
		template<nik_vp(V)(unsigned short    *)> nik_ce auto overload<Alias::is_int_type, V> = true;
		template<nik_vp(V)(  signed short    *)> nik_ce auto overload<Alias::is_int_type, V> = true;
		template<nik_vp(V)(unsigned int      *)> nik_ce auto overload<Alias::is_int_type, V> = true;
		template<nik_vp(V)(  signed int      *)> nik_ce auto overload<Alias::is_int_type, V> = true;
		template<nik_vp(V)(unsigned long     *)> nik_ce auto overload<Alias::is_int_type, V> = true;
		template<nik_vp(V)(  signed long     *)> nik_ce auto overload<Alias::is_int_type, V> = true;
		template<nik_vp(V)(unsigned long long*)> nik_ce auto overload<Alias::is_int_type, V> = true;
		template<nik_vp(V)(  signed long long*)> nik_ce auto overload<Alias::is_int_type, V> = true;

		nik_ce auto _is_int_type_ = Alias::is_int_type;

	// not_int_type:

		template<auto V>
		nik_ce auto overload<Alias::not_int_type, V> = not(overload<Alias::is_int_type, V>);

		nik_ce auto _not_int_type_ = Alias::not_int_type;

/***********************************************************************************************************************/

// functional:

	// to list:

		template<template<auto...> typename B, nik_vp(b)(T_store_B<B>*), auto... Vs>
		nik_ce auto overload<Alias::to_list, b, Vs...> = U_store_T<B<Vs...>>;

		nik_ce auto _to_list_ = Alias::to_list;

	// array to list:

		template<auto b, auto a, auto... Vs>
		nik_ce auto overload<Alias::array_to_list, b, a, Vs...> = overload<Alias::to_list, b, a[Vs]...>;

		nik_ce auto _array_to_list_ = Alias::array_to_list;

	// to array:

		template<auto U, auto... Vs>
		nik_ce auto overload<Alias::to_array, U, Vs...> = array<T_store_U<U>, Vs...>;

		nik_ce auto _to_array_ = Alias::to_array;

	// to tuple:

		template<auto... Vs>
		nik_ce auto overload<Alias::to_tuple, Vs...> = tuple<decltype(Vs)...>(Vs...);

		nik_ce auto _to_tuple_ = Alias::to_tuple;

	// is_null:

		template<auto... Vs>
		nik_ce auto overload<Alias::is_null, Vs...> = (sizeof...(Vs) == 0);

		nik_ce auto _is_null_ = Alias::is_null;

	// length:

		template<auto... Vs>
		nik_ce auto overload<Alias::length, Vs...> = sizeof...(Vs);

		nik_ce auto _length_ = Alias::length;

	// car:

		template<auto V0, auto... Vs>
		nik_ce auto overload<Alias::car, V0, Vs...> = V0;

		nik_ce auto _car_ = Alias::car;

	// cdr:

		template<auto b, auto V0, auto... Vs>
		nik_ce auto overload<Alias::cdr, b, V0, Vs...> = overload<Alias::to_list, b, Vs...>;

		nik_ce auto _cdr_ = Alias::cdr;

	// cadr:

		template<auto V0, auto V1, auto... Vs>
		nik_ce auto overload<Alias::cadr, V0, V1, Vs...> = V1;

		nik_ce auto _cadr_ = Alias::cadr;

	// map:

		template<auto b, auto Op, auto... Vs>
		nik_ce auto overload<Alias::map, b, Op, Vs...> = overload<Alias::to_list, b, overload<Op, Vs>...>;

		nik_ce auto _map_ = Alias::map;

	// find:

		using cbool_ptr = bool const*;

		template<auto Op, auto... Vs>
		nik_ce auto overload<Alias::find, Op, Vs...> = overload
		<
			_match_<>,
			cbool_ptr{array<bool const, overload<Op, Vs>...>},
			index_type{sizeof...(Vs)}
		>;

		nik_ce auto _find_ = Alias::find;

/***********************************************************************************************************************/

// variadic:

	// front (zero) unpack:

		template<template<auto...> typename B, auto... Ws, nik_vp(p)(B<Ws...>*), auto... Vs>
		nik_ce auto overload<Alias::f0_unpack, p, Vs...> = overload<Ws..., Vs...>;

		nik_ce auto _f0_unpack_ = Alias::f0_unpack;

	// front (one) unpack:

		template<template<auto...> typename B, auto... Ws, nik_vp(p)(B<Ws...>*), auto V0, auto... Vs>
		nik_ce auto overload<Alias::f1_unpack, p, V0, Vs...> = overload<V0, Ws..., Vs...>;

		nik_ce auto _f1_unpack_ = Alias::f1_unpack;

	// front (two) unpack:

		template<template<auto...> typename B, auto... Ws, nik_vp(p)(B<Ws...>*), auto V0, auto V1, auto... Vs>
		nik_ce auto overload<Alias::f2_unpack, p, V0, V1, Vs...> = overload<V0, V1, Ws..., Vs...>;

		nik_ce auto _f2_unpack_ = Alias::f2_unpack;

	// back (zero) unpack:

		template<template<auto...> typename B, auto... Ws, nik_vp(p)(B<Ws...>*), auto... Vs>
		nik_ce auto overload<Alias::b0_unpack, p, Vs...> = overload<Vs..., Ws...>;

		nik_ce auto _b0_unpack_ = Alias::b0_unpack;

	// back (one) unpack:

		template<template<auto...> typename B, auto W0, auto... Ws, nik_vp(p)(B<W0, Ws...>*), auto... Vs>
		nik_ce auto overload<Alias::b1_unpack, p, Vs...> = overload<W0, Vs..., Ws...>;

		nik_ce auto _b1_unpack_ = Alias::b1_unpack;

	// back (two) unpack:

		template<template<auto...> typename B, auto W0, auto W1, auto... Ws, nik_vp(p)(B<W0, W1, Ws...>*), auto... Vs>
		nik_ce auto overload<Alias::b2_unpack, p, Vs...> = overload<W0, W1, Vs..., Ws...>;

		nik_ce auto _b2_unpack_ = Alias::b2_unpack;

	// list to list:

		template<auto b, auto p>
		nik_ce auto overload<Alias::list_to_list, b, p> = overload<Alias::b0_unpack, p, Alias::to_list, b>;

		nik_ce auto _list_to_list_ = Alias::list_to_list;

	// list to array:

		template<auto U, auto p>
		nik_ce auto overload<Alias::list_to_array, U, p> = overload<Alias::b0_unpack, p, Alias::to_array, U>;

		nik_ce auto _list_to_array_ = Alias::list_to_array;

	// zip:

		template<auto b, auto Op, template<auto...> typename B, auto... Ws, nik_vp(p)(B<Ws...>*), auto... Vs>
		nik_ce auto overload<Alias::zip, b, Op, p, Vs...> = overload<Alias::to_list, b, overload<Op, Ws, Vs>...>;

		nik_ce auto _zip_ = Alias::zip;

	// unite (optimization):

		// alt == overload<_b0_unpack_, p2, _f2_unpack_, p1, _to_list_, b, Vs...>;

		template
		<
			auto b,
			template<auto...> typename B0, auto... Xs, nik_vp(p0)(B0<Xs...>*),
			template<auto...> typename B1, auto... Ws, nik_vp(p1)(B1<Ws...>*),
			auto... Vs
		>
		nik_ce auto overload<Alias::unite, b, p0, p1, Vs...> = overload<Alias::to_list, b, Xs..., Vs..., Ws...>;

		nik_ce auto _unite_ = Alias::unite;

	// cons:

		template<auto b, auto p, auto... Vs>
		nik_ce auto overload<Alias::cons, b, p, Vs...> = overload<Alias::unite, b, U_null_Vs, p, Vs...>;

		nik_ce auto _cons_ = Alias::cons;

	// push:

		template<auto b, auto p, auto... Vs>
		nik_ce auto overload<Alias::push, b, p, Vs...> = overload<Alias::unite, b, p, U_null_Vs, Vs...>;

		nik_ce auto _push_ = Alias::push;

/***********************************************************************************************************************/

// syntactic sugar:

	template<auto Op, auto... Vs>
	nik_ce auto listload_ = overload<Op, H_id, Vs...>;

	template<auto b, auto... Vs>
	nik_ce auto to_list_ = overload<Alias::to_list, b, Vs...>;

	template<auto p, auto Op, auto... Vs>
	nik_ce auto unpack_ = overload<Alias::b0_unpack, p, Op, Vs...>;

	template<auto b, auto Op, auto... Vs>
	nik_ce auto map_ = overload<Alias::map, b, Op, Vs...>;

	template<auto Op, auto... Vs>
	nik_ce auto find_ = overload<Alias::find, Op, Vs...>;

	template<auto b, auto Op, auto p, auto... Vs>
	nik_ce auto zip_ = overload<Alias::zip, b, Op, p, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

