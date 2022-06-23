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

/***********************************************************************************************************************/

	struct Overload
	{
		nik_ces key_type function			=  0;
		nik_ces key_type curried			=  1;
		nik_ces key_type alias				=  2;

		// defaults to alias:

		template<key_type Key, key_type Op, auto... Vs>
		nik_ces auto result = T_overload<Key, Op>::template result<Vs...>;
	};

	// function:

		template<key_type Op>
		using T_function = T_overload<Overload::function, Op>;

		template<key_type Op>
		nik_ce auto U_function_T = U_store_T<T_function<Op>>;

	// curried:

		template<key_type Op, auto... Ws>
		using T_curried = T_overload<Overload::curried, Op, Ws...>;

		template<key_type Op, auto... Ws>
		nik_ce auto U_curried_T = U_store_T<T_curried<Op, Ws...>>;

	// alias:

		template<key_type Op>
		using T_alias = T_overload<Overload::alias, Op>;

		template<key_type Op>
		nik_ce auto U_alias_T = U_store_T<T_alias<Op>>;

	// specializations:

		template<key_type Op, auto... Vs>
		nik_ce auto Overload::result<Overload::function, Op, Vs...> =
			T_function<Op>::template result<decltype(Vs)...>(Vs...);

		template<key_type Op, auto... Ws, nik_vp(c)(auto_pack<Ws...>*), auto... Vs>
		nik_ce auto Overload::result<Overload::curried, Op, c, Vs...> =
			T_curried<Op, Ws...>::template result<decltype(Vs)...>(Vs...);

	//	template<key_type Op, auto... Vs>
	//	nik_ce auto Overload::result<Overload::prealias, Op, Vs...> =
	//		T_alias<Op>::template result<Vs...>;

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

			// algebraic:

			nik_ces key_type product			= 17;

		// curried:

			// basis:

			nik_ces key_type constant			=  0;

			// comparison:

			nik_ces key_type is_equal			=  1;
			nik_ces key_type is_zero			=  2;

			// bitwise:

			nik_ces key_type upshift			=  3;
			nik_ces key_type downshift			=  4;

			// arithmetic:

			nik_ces key_type increment			=  5;
			nik_ces key_type decrement			=  6;

			// computational:

			nik_ces key_type apply				=  7;
			nik_ces key_type bind				=  8;

		// alias:

			// basis:

			nik_ces key_type first				=  0;
			nik_ces key_type to_same			=  1;

			// comparison:

			nik_ces key_type same				=  2;
			nik_ces key_type is_same			=  3;
			nik_ces key_type csame				=  4;
			nik_ces key_type is_csame			=  5;

			// functional:

			nik_ces key_type length				=  6;
			nik_ces key_type map				=  7;
			nik_ces key_type zip				=  8;

			nik_ces key_type is_null			=  9;
			nik_ces key_type cons				= 10;
			nik_ces key_type push				= 11;
			nik_ces key_type car				= 12;
			nik_ces key_type cdr				= 13;
			nik_ces key_type cadr				= 14;
			nik_ces key_type unite				= 15;
			nik_ces key_type find				= 16;
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

	// algebraic:

		// pair:

			template<auto... filler>
			struct T_overload<Overload::function, Operator::product, filler...>
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) { return pair<Ts...>(vs...); }

			}; nik_ce auto _product_ = U_function_T<Operator::product>;

/***********************************************************************************************************************/

// curried:

	// basis:

		// constant:

			template<auto V>
			struct T_overload<Overload::curried, Operator::constant, V>
			{
				template<typename... Ts>
				nik_ces auto result(Ts...) { return V; }

			}; template<auto V>
				nik_ce auto _constant_ = U_curried_T<Operator::constant, V>;

	// comparison:

		// is_equal:

			template<auto V>
			struct T_overload<Overload::curried, Operator::is_equal, V>
			{
				using T_equal = T_function<Operator::equal>;

				template<typename... Ts>
				nik_ces auto result(Ts... vs)
					{ return T_equal::template result<decltype(V), Ts...>(V, vs...); }

			}; template<auto V>
				nik_ce auto _is_equal_ = U_curried_T<Operator::is_equal, V>;

		// is_zero:

			nik_ce auto _is_zero_ = _is_equal_<_zero>;

	// bitwise:

		// upshift:

			template<auto V>
			struct T_overload<Overload::curried, Operator::upshift, V>
			{
				template<typename T>
				nik_ces auto result(T v) { return (v << V); }

			}; template<auto V = _one>
				nik_ce auto _upshift_ = U_curried_T<Operator::upshift, V>;

		// downshift:

			template<auto V>
			struct T_overload<Overload::curried, Operator::downshift, V>
			{
				template<typename T>
				nik_ces auto result(T v) { return (v >> V); }

			}; template<auto V = _one>
				nik_ce auto _downshift_ = U_curried_T<Operator::downshift, V>;

	// arithmetic:

		// increment:

			template<auto V>
			struct T_overload<Overload::curried, Operator::increment, V>
			{
				template<typename T>
				nik_ces auto result(T v) { return v + V; }

			}; template<auto V = _one>
				nik_ce auto _increment_ = U_curried_T<Operator::increment, V>;

		// decrement:

			template<auto V>
			struct T_overload<Overload::curried, Operator::decrement, V>
			{
				template<typename T>
				nik_ces auto result(T v) { return v - V; }

			}; template<auto V = _one>
				nik_ce auto _decrement_ = U_curried_T<Operator::decrement, V>;

	// computational:

		// apply:

			template<auto f>
			struct T_overload<Overload::curried, Operator::apply, f>
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) { return f(vs...); }

			}; template<auto f>
				nik_ce auto _apply_ = U_curried_T<Operator::apply, f>;

		// bind:

			template<auto f, auto... ps>
			struct T_overload<Overload::curried, Operator::bind, f, ps...>
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs)
					{ return T_store_U<f>::template result<ps..., Ts...>(vs...); }

			}; template<auto f, auto... ps>
				nik_ce auto _bind_ = U_curried_T<Operator::bind, f, ps...>;

/***********************************************************************************************************************/

// alias (variable template):

	template<key_type Op, auto... Vs>
	nik_ce auto alias = U_pack_Vs<Op, Vs...>;

	// functional:

		template<auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
		nik_ce auto alias<Operator::length, p> = sizeof...(Vs);

		template<auto Key, auto Op, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
		nik_ce auto alias<Operator::map, Key, Op, p> = U_pack_Vs<Overload::template result<Key, Op, Vs>...>;

		template<auto Op, auto c, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
		nik_ce auto alias<Operator::map, Overload::curried, Op, c, p> = U_pack_Vs
		<
			Overload::template result<Overload::curried, Op, c, Vs>...
		>;

		template
		<
			auto Key, auto Op,
			auto... Vs, nik_vp(p0)(auto_pack<Vs...>*),
			auto... Ws, nik_vp(p1)(auto_pack<Ws...>*)
		>
		nik_ce auto alias<Operator::zip, Key, Op, p0, p1> = U_pack_Vs
		<
			Overload::template result<Key, Op, Vs, Ws>...
		>;

		// curried zip: Not yet implemented.

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

/***********************************************************************************************************************/

// alias:

	template<key_type Op, auto... filler>
	struct T_overload<Overload::alias, Op, filler...>
	{
		template<auto... Vs>
		nik_ces auto result = alias<Op, Vs...>;
	};

	// basis:

		nik_ce auto _first_		= U_alias_T < Operator::first   >;
		nik_ce auto _to_same_		= U_alias_T < Operator::to_same >;

	// comparison:

		nik_ce auto _same_		= U_alias_T < Operator::same     >;
		nik_ce auto _is_same_		= U_alias_T < Operator::is_same  >;
	//	nik_ce auto _csame_		= U_alias_T < Operator::csame    >;
	//	nik_ce auto _is_csame_		= U_alias_T < Operator::is_csame >;

	// functional:

		nik_ce auto _length_		= U_alias_T < Operator::length  >;
		nik_ce auto _map_		= U_alias_T < Operator::map     >;
		nik_ce auto _zip_		= U_alias_T < Operator::zip     >;
		nik_ce auto _is_null_		= U_alias_T < Operator::is_null >;
		nik_ce auto _cons_		= U_alias_T < Operator::cons    >;
		nik_ce auto _push_		= U_alias_T < Operator::push    >;
		nik_ce auto _car_		= U_alias_T < Operator::car     >;
		nik_ce auto _cdr_		= U_alias_T < Operator::cdr     >;
		nik_ce auto _cadr_		= U_alias_T < Operator::cadr    >;
		nik_ce auto _unite_		= U_alias_T < Operator::unite   >;

		// find:

			template<auto... filler>
			struct T_overload<Overload::alias, Operator::find, filler...>
			{
				using cbool = bool const;

				nik_ces auto match(cbool *b, cindex_type size)
				{
					cbool *k = b;
					cbool *e = b + size;

					while (k != e && !*k) ++k;

					return k - b;
				}

				template<key_type Key, key_type Op, auto... Vs>
				nik_ces auto result = U_pack_Vs<Key, Op, Vs...>;

			}; nik_ce auto _find_ = U_alias_T<Operator::find>;

			template<auto... filler>
				template<key_type Key, key_type Op, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
			nik_ce auto T_overload<Overload::alias, Operator::find, filler...>::
				result<Key, Op, p> = T_alias<Operator::find>::match
			(
				array<bool, Overload::template result<Key, Op, Vs>...>, sizeof...(Vs)
			);

			template<auto... filler> template<auto Op, auto c, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
			nik_ce auto T_overload<Overload::alias, Operator::find, filler...>::
				result<Overload::curried, Op, c, p> = T_alias<Operator::find>::match
			(
				array<bool, Overload::template result<Overload::curried, Op, c, Vs>...>, sizeof...(Vs)
			);

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machination:

/***********************************************************************************************************************/

// struct:

	template<typename T1, typename T2>
	struct machination
	{
		T1 s1;
		T2 s2;

		nik_ce machination(const T1 & _s1, const T2 & _s2) : s1{_s1}, s2{_s2} { }
	};

/***********************************************************************************************************************/

// is machination:

	template<typename T>
	nik_ce bool is_machination = false;

	template<typename T1, typename T2> nik_ce bool is_machination <       machination<T1, T2>   > = true;
	template<typename T1, typename T2> nik_ce bool is_machination < const machination<T1, T2>   > = true;
	template<typename T1, typename T2> nik_ce bool is_machination < const machination<T1, T2> & > = true;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

	template<key_type, key_type, key_type...> struct machine;

/***********************************************************************************************************************/

// names:

	struct MachineName
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

	using MN = MachineName;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// notes:

/***********************************************************************************************************************/

	struct MachineNote
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

	using MT = MachineNote;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// instructions:

/***********************************************************************************************************************/

	struct MachineInstr
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

	using MI			= MachineInstr;
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
/***********************************************************************************************************************/

// controllers:

/***********************************************************************************************************************/

	struct MachineContr
	{
		using type					= instr_type const * const;

		nik_ces key_type size				= 0;

		nik_ces index_type length (type l)		{ return l[size][MI::size]; }
	};

	using MC		= MachineContr;
	using contr_type	= typename MC::type;

	template<instr_type... Vs>
	nik_ce contr_type controller = array<instr_type, array<index_type, sizeof...(Vs)>, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// dispatch:

	struct MachineDispatch
	{
		// defaults:

			nik_ces depth_type initial_depth = 500;
			nik_ces index_type initial_index = _zero;

		// accessors:

			nik_ces auto instr(contr_type c, cindex_type i)
				{ return c[i]; }

		// navigators:

			nik_ces key_type next_name(cdepth_type d, ckey_type m, contr_type c, cindex_type i)
			{
				if (d == 0)		return MN::halt;
				else if (m != MT::id)	return MN::recall;
				else			return c[i+1][MI::name];
			}

			nik_ces key_type next_note(cdepth_type d, ckey_type m, contr_type c, cindex_type i)
			{
				if (d == 0)		return MT::pause;
				else if (m != MT::id)	return m;
				else			return c[i+1][MI::note];
			}

			nik_ces depth_type next_depth(cdepth_type d)
				{ return d - bool{d != 0}; }

			nik_ces index_type next_index(cdepth_type d, ckey_type m, contr_type, cindex_type i)
				{ return i + bool{d != 0 && m == MT::id}; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// block:

	template<key_type...> struct block;

/***********************************************************************************************************************/

// names:

	struct BlockName
	{
		nik_ces key_type id		=  0;

		nik_ces key_type variable	=  1;
		nik_ces key_type function	=  2;

		nik_ces key_type segment	=  3;
		nik_ces key_type argument	=  4;

		nik_ces key_type fold		=  5;
		nik_ces key_type cascade	=  6;

		nik_ces key_type sifter		=  7;
		nik_ces key_type right		=  8;
		nik_ces key_type lookup		=  9;

		nik_ces key_type filter		= 10;
		nik_ces key_type left		= 11;
		nik_ces key_type split		= 12;
	};

	using BN = BlockName;

/***********************************************************************************************************************/

// notes:

	struct BlockNote
	{
		nik_ces key_type id		= 0;

		nik_ces key_type pause		= 1;
		nik_ces key_type halt		= 2;
		nik_ces key_type pass		= 3;
	};

	using BT = BlockNote;

/***********************************************************************************************************************/

// dispatch:

	struct BlockDispatch
	{
		// length:

		nik_ces key_type max_length_0(cindex_type n) { if (n >= _2_0) return 0; else return _zero; }
		nik_ces key_type max_length_1(cindex_type n) { if (n >= _2_1) return 1; else return max_length_0(n); }
		nik_ces key_type max_length_2(cindex_type n) { if (n >= _2_2) return 2; else return max_length_1(n); }
		nik_ces key_type max_length_3(cindex_type n) { if (n >= _2_3) return 3; else return max_length_2(n); }
		nik_ces key_type max_length_4(cindex_type n) { if (n >= _2_4) return 4; else return max_length_3(n); }
		nik_ces key_type max_length_5(cindex_type n) { if (n >= _2_5) return 5; else return max_length_4(n); }
		nik_ces key_type max_length_6(cindex_type n) { if (n >= _2_6) return 6; else return max_length_5(n); }
		nik_ces key_type max_length_7(cindex_type n) { if (n >= _2_7) return 7; else return max_length_6(n); }
		nik_ces key_type max_length_8(cindex_type n) { if (n >= _2_8) return 8; else return max_length_7(n); }
		nik_ces key_type max_length_9(cindex_type n) { if (n >= _2_9) return 9; else return max_length_8(n); }

		// index:

		nik_ces index_type max_index_0(cindex_type n) { if (n >= _2_0) return _2_0; else return _zero; }
		nik_ces index_type max_index_1(cindex_type n) { if (n >= _2_1) return _2_1; else return max_index_0(n); }
		nik_ces index_type max_index_2(cindex_type n) { if (n >= _2_2) return _2_2; else return max_index_1(n); }
		nik_ces index_type max_index_3(cindex_type n) { if (n >= _2_3) return _2_3; else return max_index_2(n); }
		nik_ces index_type max_index_4(cindex_type n) { if (n >= _2_4) return _2_4; else return max_index_3(n); }
		nik_ces index_type max_index_5(cindex_type n) { if (n >= _2_5) return _2_5; else return max_index_4(n); }
		nik_ces index_type max_index_6(cindex_type n) { if (n >= _2_6) return _2_6; else return max_index_5(n); }
		nik_ces index_type max_index_7(cindex_type n) { if (n >= _2_7) return _2_7; else return max_index_6(n); }
		nik_ces index_type max_index_8(cindex_type n) { if (n >= _2_8) return _2_8; else return max_index_7(n); }
		nik_ces index_type max_index_9(cindex_type n) { if (n >= _2_9) return _2_9; else return max_index_8(n); }

		// note:

			nik_ces key_type next_note(cdepth_type d, cindex_type n)
			{
				if      (d == 0) return BT::pause;
				else if (n == 0) return BT::halt;
				else             return BT::pass;
			}

		// length:

			NIK_BLOCK_DISPATCH_NEXT_LENGTH(0)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(1)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(2)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(3)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(4)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(5)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(6)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(7)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(8)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(9)

		// depth:

			nik_ces depth_type next_depth(cdepth_type d)
				{ return d - bool{d != 0}; }

		// index:

			NIK_BLOCK_DISPATCH_NEXT_INDEX(0)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(1)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(2)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(3)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(4)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(5)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(6)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(7)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(8)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(9)
	};

/***********************************************************************************************************************/

// halters:

	// sifter:

		template<key_type... filler>
		struct block<BN::sifter, filler...>
		{
			template<auto V0, auto... Vs>
			nik_ces auto result = V0;
		};

	// right:

		template<key_type... filler>
		struct block<BN::right, filler...>
		{
			template<auto... Vs>
			nik_ces auto result = U_pack_Vs<Vs...>;
		};

	// lookup:

		template<key_type... filler>
		struct block<BN::lookup, filler...>
		{
			template<auto V0, auto... Vs>
			nik_ces auto result = Overload::template result
			<
				Overload::alias, Operator::cadr, V0
			>;
		};

	// filter:

		template<key_type... filler>
		struct block<BN::filter, filler...>
		{
			template<auto V0, auto... Vs, typename Pack>
			nik_ces auto result(Pack p) { return pair(p, U_pack_Vs<Vs...>); }
		};

	// left:

		template<key_type... filler>
		struct block<BN::left, filler...>
		{
			template<auto... Vs, typename Pack>
			nik_ces auto result(Pack p) { return p; }
		};

	// split:

		template<key_type... filler>
		struct block<BN::split, filler...>
		{
			template<auto... Vs, typename Pack>
			nik_ces auto result(Pack p) { return pair(p, U_pack_Vs<Vs...>); }
		};

/***********************************************************************************************************************/

// variable:

	template<key_type... filler>
	struct block<BN::variable, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto rtn, auto... Vs>
		nik_ces auto result = machination(U_pack_Vs<rtn>, U_pack_Vs<n, Vs...>);
	};

	template<key_type... filler>
	struct block<BN::variable, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto rtn, auto... Vs>
		nik_ces auto result = block<rtn>::template result<Vs...>;
	};

	NIK_DEFINE_BLOCK_VARIABLE_PASS(0)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(1)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(2)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(3)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(4)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(5)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(6)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(7)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(8)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(9)

/***********************************************************************************************************************/

// function:

	template<key_type... filler>
	struct block<BN::function, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto rtn, auto... Vs, typename Pack>
		nik_ces auto result(Pack p)
		{
			return machination(U_pack_Vs<rtn>, U_pack_Vs<U_restore_T<Pack>, n, Vs...>);
		}
	};

	template<key_type... filler>
	struct block<BN::function, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto rtn, auto... Vs, typename Pack>
		nik_ces auto result(Pack p) { return block<rtn>::template result<Vs...>(p); }
	};

	NIK_DEFINE_BLOCK_FUNCTION_PASS(0)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(1)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(2)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(3)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(4)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(5)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(6)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(7)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(8)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(9)

/***********************************************************************************************************************/

// segment:

	template<key_type... filler>
	struct block<BN::segment, BT::pause, _zero, filler...>
	{
		nik_ces auto s1 = U_pack_Vs<BN::segment>;

		template<auto d, auto n, auto m, auto... Vs>
		nik_ces auto result = machination(s1, U_pack_Vs<n, m, Vs...>);
	};

	template<key_type... filler>
	struct block<BN::segment, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto m, auto... Vs>
		nik_ces auto result = U_pack_Vs<decltype(m){m+Vs}...>;
	};

	NIK_DEFINE_BLOCK_SEGMENT_PASS(0)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(1)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(2)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(3)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(4)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(5)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(6)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(7)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(8)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(9)

/***********************************************************************************************************************/

// argument:

	template<key_type... filler>
	struct block<BN::argument, BT::pause, _zero, filler...>
	{
		template<bool V>
		nik_ces auto result_assert() { return V; }

		template<auto d, auto n, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			static_assert(result_assert<bool{d != 0}>(), "argument nesting depth exceeded!");
		}
	};

	template<key_type... filler>
	struct block<BN::argument, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) { return v; }
	};

	NIK_DEFINE_BLOCK_ARGUMENT_PASS(0)
	NIK_DEFINE_BLOCK_ARGUMENT_PASS(1)
	NIK_DEFINE_BLOCK_ARGUMENT_PASS(2)
	NIK_DEFINE_BLOCK_ARGUMENT_PASS(3)
	NIK_DEFINE_BLOCK_ARGUMENT_PASS(4)
	NIK_DEFINE_BLOCK_ARGUMENT_PASS(5)
	NIK_DEFINE_BLOCK_ARGUMENT_PASS(6)
	NIK_DEFINE_BLOCK_ARGUMENT_PASS(7)
	NIK_DEFINE_BLOCK_ARGUMENT_PASS(8)
	NIK_DEFINE_BLOCK_ARGUMENT_PASS(9)

/***********************************************************************************************************************/

// (action) fold:

	template<key_type... filler>
	struct block<BN::fold, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto Key, auto Op, auto V, auto... Vs, auto... cs>
		nik_ces auto result(nik_vp(c)(auto_pack<cs...>*))
		{
			return machination(c, U_pack_Vs<n, Key, Op, V, Vs...>);
		}
	};

	template<key_type... filler>
	struct block<BN::fold, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto Key, auto Op, auto V, auto... Vs, auto... cs>
		nik_ces auto result(nik_vp(c)(auto_pack<cs...>*)) { return V; }
	};

	NIK_DEFINE_BLOCK_FOLD_PASS(0)
	NIK_DEFINE_BLOCK_FOLD_PASS(1)
	NIK_DEFINE_BLOCK_FOLD_PASS(2)
	NIK_DEFINE_BLOCK_FOLD_PASS(3)
	NIK_DEFINE_BLOCK_FOLD_PASS(4)
	NIK_DEFINE_BLOCK_FOLD_PASS(5)
	NIK_DEFINE_BLOCK_FOLD_PASS(6)
	NIK_DEFINE_BLOCK_FOLD_PASS(7)
	NIK_DEFINE_BLOCK_FOLD_PASS(8)
	NIK_DEFINE_BLOCK_FOLD_PASS(9)

/***********************************************************************************************************************/

// cascade (compel fold):

	template<key_type... filler>
	struct block<BN::cascade, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto Op, auto V, auto... Vs>
		nik_ces auto result()
		{
			return machination(U_pack_Vs<Op>, U_pack_Vs<BT::pause, n, V, Vs...>);
		}
	};

	template<key_type... filler>
	struct block<BN::cascade, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto Op, auto V, auto... Vs>
		nik_ces auto result() { return V; }
	};

	template<key_type... filler>
	struct block<BN::cascade, BT::pass, _zero, filler...>
	{
		template<auto d, auto n, auto Op, auto V, auto V0, auto... Vs>
		nik_ces auto result()
		{
			nik_ce auto val = T_store_U<Op>::template result<d, V, V0>;

			if nik_ce (is_machination<decltype(val)>)

				return machination(U_pack_Vs<Op>, U_pack_Vs<BT::id, n, val.s1, val.s2, Vs...>);
			else
				return NIK_CASCADE_BLOCK(d, n, Op, val, Vs);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

