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

// backend 0:

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

	template<auto...> struct auto_pack { };

	template<auto... Vs>
	nik_ce auto U_pack_Vs = store<auto_pack<Vs...>*>;

	nik_ce auto U_null_Vs = U_pack_Vs<>;

// typename:

	template<typename...> struct typename_pack { };

	template<typename... Ts>
	nik_ce auto U_pack_Ts = store<typename_pack<Ts...>*>;

	nik_ce auto U_null_Ts = U_pack_Ts<>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pair:

	template<typename T1, typename T2>
	struct pair
	{
		T1 v1;
		T2 v2;

		nik_ce pair(const T1 & _v1, const T2 & _v2) : v1{_v1}, v2{_v2} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array:

	template<typename Type, Type... Vs>
	nik_ce Type array[] = { Vs... };

/***********************************************************************************************************************/

// U -> V:

	template<typename Type, auto... Vs>
	nik_ce auto V_array_U(nik_avp(auto_pack<Vs...>*))
		{ return array<Type, Vs...>; }

// V -> U:

	template<auto Arr, auto... Is>
	nik_ce auto U_array_V(nik_avp(auto_pack<Is...>*))
		{ return U_pack_Vs<Arr[Is]...>; }

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

			nik_ces key_type product			= 19;

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

			nik_ces key_type first				=  0;
			nik_ces key_type to_const			=  1;

			// comparison:

			nik_ces key_type same				=  2;
			nik_ces key_type csame				=  3;
			nik_ces key_type is_int_type			=  4;

			// functional:

			nik_ces key_type length				=  5;
			nik_ces key_type map				=  6;
			nik_ces key_type zip				=  7;

			nik_ces key_type is_null			=  8;
			nik_ces key_type cons				=  9;
			nik_ces key_type push				= 10;
			nik_ces key_type car				= 11;
			nik_ces key_type cdr				= 12;
			nik_ces key_type cadr				= 13;
			nik_ces key_type unite				= 14;
			nik_ces key_type find				= 15;

			// modular:

			nik_ces key_type custom				= 16;
	};

/***********************************************************************************************************************/

// function:

	// basis:

		// id:

			template<auto... filler>
			struct T_overload<Overload::function, Operator::id, filler...>
			{
				template<typename T>
				nik_ces auto result(T v) { return v; }

			}; nik_ce auto _id_ = U_function_T<Operator::id>;

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

	// algebraic:

		// pair:

			template<auto... filler>
			struct T_overload<Overload::function, Operator::product, filler...>
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) { return pair<Ts...>(vs...); }

			}; nik_ce auto _product_ = U_function_T<Operator::product>;

/***********************************************************************************************************************/

// higher order:

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

// alias (variable template):

	template<key_type Op, auto... Vs>
	nik_ce auto alias = U_pack_Vs<Op, Vs...>;

	// basis:

		template<auto V, auto... Vs>
		nik_ce auto alias<Operator::first, V, Vs...> = V;

		template<typename T, nik_vp(V)(T*)>
		nik_ce auto alias<Operator::to_const, V> = U_store_T<T const>;

		template<typename T, nik_vp(V)(T&)>
		nik_ce auto alias<Operator::to_const, V> = U_store_T<T const &>;

	// comparison:

		template<auto V0, auto V1>
		nik_ce auto alias<Operator::same, V0, V1> = false;

		template<auto V>
		nik_ce auto alias<Operator::same, V, V> = true;

		template<auto V0, auto V1>
		nik_ce auto alias<Operator::csame, V0, V1> = alias
		<
			Operator::same,
			alias<Operator::to_const, V0>,
			alias<Operator::to_const, V1>
		>;

		template<auto V> nik_ce auto alias<Operator::is_int_type, V> = false;

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

	// functional:

		template<auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
		nik_ce auto alias<Operator::length, p> = sizeof...(Vs);

		template<auto op, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
		nik_ce auto alias<Operator::map, op, p> = U_pack_Vs<overload<op, Vs>...>;

		template
		<
			auto op,
			auto... Vs, nik_vp(p0)(auto_pack<Vs...>*),
			auto... Ws, nik_vp(p1)(auto_pack<Ws...>*)
		>
		nik_ce auto alias<Operator::zip, op, p0, p1> = U_pack_Vs<overload<op, Vs, Ws>...>;

		template<auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
		nik_ce auto alias<Operator::is_null, p> = (sizeof...(Vs) == 0);

		template<auto V0, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
		nik_ce auto alias<Operator::cons, V0, p> = U_pack_Vs<V0, Vs...>;

		template<auto V0, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
		nik_ce auto alias<Operator::push, V0, p> = U_pack_Vs<Vs..., V0>;

		template<auto V0, auto... Vs, nik_vp(p)(auto_pack<V0, Vs...>*)>
		nik_ce auto alias<Operator::car, p> = V0;

		template<auto V0, auto... Vs, nik_vp(p)(auto_pack<V0, Vs...>*)>
		nik_ce auto alias<Operator::cdr, p> = U_pack_Vs<Vs...>;

		template<auto V0, auto V1, auto... Vs, nik_vp(p)(auto_pack<V0, V1, Vs...>*)>
		nik_ce auto alias<Operator::cadr, p> = V1;

		template
		<
			auto... Vs, nik_vp(p0)(auto_pack<Vs...>*),
			auto... Ws, nik_vp(p1)(auto_pack<Ws...>*),
			auto... Xs
		>
		nik_ce auto alias<Operator::unite, p0, p1, Xs...> = U_pack_Vs<Vs..., Xs..., Ws...>;

		template<auto op, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
		nik_ce auto alias<Operator::find, op, p> = T_higher_order<Operator::match, _to_bool_>::result
		(
			array<bool, overload<op, Vs>...>, sizeof...(Vs)
		);

		template<auto Op, auto... Vs>
		nik_ce auto alias<Operator::custom, Op, Vs...> = T_store_U<Op>::template result<Vs...>;

/***********************************************************************************************************************/

// alias:

	template<key_type Op, auto... Ws>
	struct T_overload<Overload::alias, Op, Ws...>
	{
		template<auto... Vs>
		nik_ces auto result = alias<Op, Ws..., Vs...>;
	};

	// basis:

	template<auto... Vs> using T_first		= T_alias   < Operator::first       , Vs... >;
	template<auto... Vs> using T_to_const		= T_alias   < Operator::to_const    , Vs... >;

	template<auto... Vs> nik_ce auto U_first	= U_store_T < T_first               < Vs... > >;
	template<auto... Vs> nik_ce auto U_to_const	= U_store_T < T_to_const            < Vs... > >;

	// comparison:

	template<auto... Vs> using T_same		= T_alias   < Operator::same        , Vs... >;
	template<auto... Vs> using T_csame		= T_alias   < Operator::csame       , Vs... >;
	template<auto... Vs> using T_is_int_type	= T_alias   < Operator::is_int_type , Vs... >;

	template<auto... Vs> nik_ce auto U_same		= U_store_T < T_same                < Vs... > >;
	template<auto... Vs> nik_ce auto U_csame	= U_store_T < T_csame               < Vs... > >;
	template<auto... Vs> nik_ce auto U_is_int_type	= U_store_T < T_is_int_type         < Vs... > >;

	// functional:

	template<auto... Vs> using T_length		= T_alias   < Operator::length      , Vs... >;
	template<auto... Vs> using T_map		= T_alias   < Operator::map         , Vs... >;
	template<auto... Vs> using T_zip		= T_alias   < Operator::zip         , Vs... >;
	template<auto... Vs> using T_is_null		= T_alias   < Operator::is_null     , Vs... >;
	template<auto... Vs> using T_cons		= T_alias   < Operator::cons        , Vs... >;
	template<auto... Vs> using T_push		= T_alias   < Operator::push        , Vs... >;
	template<auto... Vs> using T_car		= T_alias   < Operator::car         , Vs... >;
	template<auto... Vs> using T_cdr		= T_alias   < Operator::cdr         , Vs... >;
	template<auto... Vs> using T_cadr		= T_alias   < Operator::cadr        , Vs... >;
	template<auto... Vs> using T_unite		= T_alias   < Operator::unite       , Vs... >;
	template<auto... Vs> using T_find		= T_alias   < Operator::find        , Vs... >;

	template<auto... Vs> nik_ce auto U_length	= U_store_T < T_length              < Vs... > >;
	template<auto... Vs> nik_ce auto U_map		= U_store_T < T_map                 < Vs... > >;
	template<auto... Vs> nik_ce auto U_zip		= U_store_T < T_zip                 < Vs... > >;
	template<auto... Vs> nik_ce auto U_is_null	= U_store_T < T_is_null             < Vs... > >;
	template<auto... Vs> nik_ce auto U_cons		= U_store_T < T_cons                < Vs... > >;
	template<auto... Vs> nik_ce auto U_push		= U_store_T < T_push                < Vs... > >;
	template<auto... Vs> nik_ce auto U_car		= U_store_T < T_car                 < Vs... > >;
	template<auto... Vs> nik_ce auto U_cdr		= U_store_T < T_cdr                 < Vs... > >;
	template<auto... Vs> nik_ce auto U_cadr		= U_store_T < T_cadr                < Vs... > >;
	template<auto... Vs> nik_ce auto U_unite	= U_store_T < T_unite               < Vs... > >;
	template<auto... Vs> nik_ce auto U_find		= U_store_T < T_find                < Vs... > >;

	// modular:

	template<auto... Vs> using T_custom		= T_alias   < Operator::custom      , Vs... >;

	template<auto... Vs> nik_ce auto U_custom	= U_store_T < T_custom              < Vs... > >;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// instructions:

/***********************************************************************************************************************/

// names:

	struct InstrName
	{
		nik_ces key_type id				=  0;
		nik_ces key_type identity			= id; // convenience for
								      // default params.

		nik_ces key_type recall				=  1;
		nik_ces key_type call				=  2;
		nik_ces key_type halt				=  3;

		nik_ces key_type move_j_all			=  4;

		nik_ces key_type paste_r_all			=  5;
		nik_ces key_type paste_a_all			=  6;

		nik_ces key_type go_to				=  7;

		nik_ces key_type memoize			=  8;
	};

	using MN = InstrName;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// notes:

/***********************************************************************************************************************/

	struct InstrNote
	{
		nik_ces key_type id				=  0;
		nik_ces key_type identity			= id;	// convenience for
									// default params.

		nik_ces key_type action				=  1;

		nik_ces key_type copy_r_pos			=  2;
		nik_ces key_type copy_j_pos			=  3;
		nik_ces key_type copy_c_pos			=  4;
		nik_ces key_type copy_a_pos			=  5;
		nik_ces key_type copy				=  6;

		nik_ces key_type cut_r_pos			=  7;
		nik_ces key_type cut_a_pos			=  8;
		nik_ces key_type cut				=  9;

		nik_ces key_type variable			= 10;
		nik_ces key_type function			= 11;
		nik_ces key_type cascade			= 12;
		nik_ces key_type compel				= 13;
		nik_ces key_type propel				= 14;
		nik_ces key_type internal			= 15;

		nik_ces key_type pause				= 16;

		nik_ces key_type conditional			= 17;

		nik_ces key_type lookup				= 18;
		nik_ces key_type insert				= 19;
	};

	using MT = InstrNote;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// instructions:

/***********************************************************************************************************************/

	struct InstrLocs
	{
		using type						= index_type const * const;

		nik_ces key_type size					= 0;
		nik_ces key_type name					= 1;
		nik_ces key_type note					= 2;

		nik_ces key_type pos					= 3;
		nik_ces key_type dec					= 3;
		nik_ces key_type rtn					= 3;

		nik_ces key_type ctn					= 4;
		nik_ces key_type key					= 5;
		nik_ces key_type act					= 6;

		// locations:

		nik_ces key_type _register				= 0;
		nik_ces key_type _junction				= 1;
		nik_ces key_type _constant				= 2;
		nik_ces key_type _argument				= 3;

		// actions:

		nik_ces key_type h0					= 0;
		nik_ces key_type h0_write				= 1;
		nik_ces key_type h1					= 2;
		nik_ces key_type h1_pair				= 3; // C++17 specific.
		nik_ces key_type value					= 4;

		nik_ces index_type length     (type i)			{ return i[size]; }
		nik_ces bool       is_optimal (cindex_type n)		{ return (n < _eight); }

		nik_ces auto copy_note(ckey_type l)
		{
			if      (l == _register) return MT::copy_r_pos;
			else if (l == _junction) return MT::copy_j_pos;
			else if (l == _constant) return MT::copy_c_pos;
			else                     return MT::copy_a_pos;
		}

		nik_ces auto cut_note(ckey_type l)
		{
			if   (l == _register) return MT::cut_r_pos;
			else                  return MT::cut_a_pos;
		}

		nik_ces auto paste_name(ckey_type l)
		{
			if   (l == _register) return MN::paste_r_all;
			else                  return MN::paste_a_all;
		}
	};

	using MI			= InstrLocs;
	using instr_type		= typename MI::type;

	nik_ce auto _register		= MI::_register;
	nik_ce auto _junction		= MI::_junction;
	nik_ce auto _constant		= MI::_constant;
	nik_ce auto _argument		= MI::_argument;

	nik_ce auto _h0			= MI::h0;
	nik_ce auto _h0_write		= MI::h0_write;
	nik_ce auto _h1			= MI::h1;
	nik_ce auto _h1_pair		= MI::h1_pair;
	nik_ce auto _value		= MI::value;

	template<index_type... Vs>
	nik_ce instr_type instruction = array<index_type, sizeof...(Vs), Vs...>;

/***********************************************************************************************************************/

// overload:

		// reverse order for user friendliness:

	template<key_type key, key_type act, key_type ctn = _h1, depth_type dec = _two>
	nik_ce instr_type action = instruction<MN::call, MT::action, dec, ctn, key, act>;

		template<key_type act, key_type ctn = _h1, depth_type dec = _two>
		nik_ce instr_type f_action = action<Overload::function, act, ctn, dec>;

		template<key_type act, key_type ctn = _h1, depth_type dec = _two>
		nik_ce instr_type h_action = action<Overload::higher_order, act, ctn, dec>;

		template<key_type act, key_type ctn = _h1, depth_type dec = _two>
		nik_ce instr_type a_action = action<Overload::alias, act, ctn, dec>;

	// function:

		// comparison:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto equal = f_action<Operator::equal, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto not_equal = f_action<Operator::not_equal, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto less_than = f_action<Operator::less_than, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto less_than_or_equal = f_action<Operator::less_than_or_equal, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto greater_than = f_action<Operator::greater_than, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto greater_than_or_equal = f_action<Operator::greater_than_or_equal, ctn, dec>;

		// logical:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto not_ = f_action<Operator::not_, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto and_ = f_action<Operator::and_, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto or_ = f_action<Operator::or_, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto implies = f_action<Operator::implies, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto equivalent = f_action<Operator::equivalent, ctn, dec>;

		// arithmetic:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto add = f_action<Operator::add, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto subtract = f_action<Operator::subtract, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto multiply = f_action<Operator::multiply, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto divide = f_action<Operator::divide, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto modulo = f_action<Operator::modulo, ctn, dec>;

		// bitwise:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto upshift = f_action<Operator::upshift, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto downshift = f_action<Operator::downshift, ctn, dec>;

		// algebraic:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto product = f_action<Operator::product, ctn, dec>;

	// higher order:

		// computational:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto apply = h_action<Operator::apply, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _three>
		nik_ce auto bind = h_action<Operator::bind, ctn, dec>;

			// comparison:

			template<key_type ctn = _h1, depth_type dec = _two>
			nik_ce auto is_equal = h_action<Operator::is_equal, ctn, dec>;

			template<key_type ctn = _h1, depth_type dec = _two>
			nik_ce auto is_zero = h_action<Operator::is_zero, ctn, dec>;

			// arithmetic:

			template<key_type ctn = _h1, depth_type dec = _two>
			nik_ce auto increment = h_action<Operator::increment, ctn, dec>;

			template<key_type ctn = _h1, depth_type dec = _two>
			nik_ce auto decrement = h_action<Operator::decrement, ctn, dec>;

	// alias:

		// basis:

		// comparison:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto same = a_action<Operator::same, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto csame = a_action<Operator::csame, ctn, dec>;

		// functional:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto length = a_action<Operator::length, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto map = a_action<Operator::map, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto zip = a_action<Operator::zip, ctn, dec>;

		//

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto is_null = a_action<Operator::is_null, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto cons = a_action<Operator::cons, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto push = a_action<Operator::push, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto car = a_action<Operator::car, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto cdr = a_action<Operator::cdr, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto cadr = a_action<Operator::cadr, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto unite = a_action<Operator::unite, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto find = a_action<Operator::find, ctn, dec>;

		// modular:

		template<key_type ctn = _h1, depth_type dec = _two>
		nik_ce auto custom = a_action<Operator::custom, ctn, dec>;

/***********************************************************************************************************************/

// machine:

	template<index_type pos, key_type loc, key_type ctn = _h0> // reverse order for user friendliness.
	nik_ce instr_type copy = instruction<MN::call, MI::copy_note(loc), pos, ctn>;

		template<index_type pos, key_type loc>
		nik_ce instr_type write = copy<pos, loc, _h0_write>;

		template<index_type pos, key_type loc>
		nik_ce instr_type value = copy<pos, loc, _value>;

	template<index_type pos, key_type loc> // reverse order for user friendliness.
	nik_ce instr_type cut = instruction<MN::call, MI::cut_note(loc), pos>;

	template<key_type rtn, key_type ctn = _h1>
	nik_ce instr_type variable = instruction<MN::call, MT::variable, rtn, ctn>;

	template<key_type rtn, key_type ctn = _h1>
	nik_ce instr_type function = instruction<MN::call, MT::function, rtn, ctn>;

	template<key_type rtn, key_type ctn = _h1>
	nik_ce instr_type cascade = instruction<MN::call, MT::cascade, rtn, ctn>;

	template<key_type ctn = _h1, depth_type dec = _two>
	nik_ce instr_type compel = instruction<MN::call, MT::compel, dec, ctn>;

	template<key_type...>
	nik_ce instr_type internal = instruction<MN::call, MT::internal>;

	template<key_type...>
	nik_ce instr_type stage = instruction<MN::move_j_all, MT::id>;

	template<key_type loc>
	nik_ce instr_type paste = instruction<MI::paste_name(loc), MT::id>;

	template<key_type...>
	nik_ce instr_type cycle = instruction<MN::go_to, MT::id, _zero>;

	template<key_type pos>
	nik_ce instr_type branch = instruction<MN::go_to, MT::conditional, pos>;

	template<key_type pos>
	nik_ce instr_type mem_lookup = instruction<MN::memoize, MT::lookup, pos>;

	template<key_type...>
	nik_ce instr_type mem_insert = instruction<MN::memoize, MT::insert>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

