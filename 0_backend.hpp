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

// backend:

namespace cctmp {

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

// module:

	template<key_type...>
	struct module
	{
		nik_ces key_type id			=  0;

		nik_ces key_type store			=  1;
		nik_ces key_type array			=  2;
		nik_ces key_type array_struct		=  3;
	};

	using Module = module<>;

/***********************************************************************************************************************/

	template<key_type... filler>
	struct module<Module::store, filler...>
	{
		// to:

			template<typename T> nik_ces void store(T) { };

		// from:

			template<typename T> struct match			{ using result = T; };
			template<typename T> struct match<void(*)(T&)>		{ using result = T&; };
			template<typename T> struct match<void(*const)(T&)>	{ using result = T&; };
			template<typename T> struct match<void(*)(T*)>		{ using result = T; };
			template<typename T> struct match<void(*const)(T*)>	{ using result = T; };
	};

	using StoreModule = module<Module::store>;

// T -> U:

	template<typename T>
	constexpr auto U_store_T = StoreModule::store<T*>;

	template<typename T>
	constexpr auto U_store_T<T&> = StoreModule::store<T&>;

// U -> T:

	template<typename T>
	using T_restore_T = typename StoreModule::match<T>::result;

	template<typename T>
	constexpr auto U_restore_T = U_store_T<T_restore_T<T>>;

	template<auto U>
	using T_store_U = T_restore_T<decltype(U)>;

// auto pack:

	template<auto...> struct auto_pack { };

	template<auto... Vs>
	constexpr auto U_pack_Vs = StoreModule::store<auto_pack<Vs...>*>;

	constexpr auto U_null_Vs = U_pack_Vs<>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pair:

	template<typename T1, typename T2>
	struct pair
	{
		T1 v1;
		T2 v2;

		constexpr pair(const T1 & _v1, const T2 & _v2) : v1{_v1}, v2{_v2} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array:

	template<typename Type, Type... Vs>
	constexpr Type array[] = { Vs... };

/***********************************************************************************************************************/

// U -> V:

	template<typename Type, auto... Vs>
	constexpr auto V_array_U(nik_avp(auto_pack<Vs...>*))
		{ return array<Type, Vs...>; }

// V -> U:

	template<auto Arr, auto... Is>
	constexpr auto U_array_V(nik_avp(auto_pack<Is...>*))
		{ return U_pack_Vs<Arr[Is]...>; }

/***********************************************************************************************************************/

// module:

	template<key_type... filler>
	struct module<Module::array, filler...>
	{
		// copy:

			struct Copy
			{
				template<typename OutIter, typename InIter, typename EndIter>
				nik_ces void result(OutIter out, InIter in, EndIter end)
					{ while (in != end) *(out++) = *(in++); }
			};

		// sequence:

			struct Sequence
			{
				template<auto f, typename OutIter, typename InIter, typename EndIter>
				nik_ces void result(OutIter out, InIter in, EndIter end)
					{ while (in != end) *(out++) = f(in++); }
			};

		// map:

			struct Map
			{
				template<auto f, typename OutIter, typename InIter, typename EndIter>
				nik_ces void result(OutIter out, InIter in, EndIter end)
					{ while (in != end) *(out++) = f(*(in++)); }
			};

		// fold:

			struct Fold
			{
				template<auto f, auto init, typename OutIter, typename InIter, typename EndIter>
				nik_ces void result(OutIter out, InIter in, EndIter end)
				{
					*out = init;

					while (in != end) *out = f(*out, *(in++));
				}
			};

		// find:

			struct Find
			{
				template<auto Size, auto p, typename OutIter, typename InIter, typename EndIter>
				nik_ces void result(OutIter out, InIter in, EndIter end)
				{
					*out = Size;
					InIter in0 = in;

					while ((*out == Size) && (in != end)) if (p(*in)) *out = (in++) - in0;
				}
			};

		// sift:

			struct Sift
			{
				template<auto p, typename OutIter, typename InIter, typename EndIter>
				nik_ces void result(OutIter out, InIter in, EndIter end)
				{
					OutIter out0 = out++;
					InIter   in0 = in;

					while (in != end) if (p(*in)) *(out++) = (in++) - in0;

					*out0 = out - out0;
				}
			};

		// (deducible) sift:

		// zip:

			struct Zip
			{
				template<auto f, typename OutIter, typename In1Iter, typename End1Iter, typename In2Iter>
				nik_ces void result(OutIter out, In1Iter in1, End1Iter end1, In2Iter in2)
					{ while (in1 != end1) *(out++) = f(*(in1++), *(in2++)); }
			};
	};

	using ArrayModule = module<Module::array>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array struct:

	template<typename Type, auto Size>
	struct ArrayStruct
	{
		Type value[Size];
	};

/***********************************************************************************************************************/

// module:

	template<key_type... filler>
	struct module<Module::array_struct, filler...>
	{
		// type:

			template<typename Type, auto Size>
			nik_ces auto type(const ArrayStruct<Type, Size> &) { return U_store_T<Type>; }

		// size:

			template<typename Type, auto Size>
			nik_ces auto size(const ArrayStruct<Type, Size> &) { return Size; }

		// begin:

			template<typename Type, auto Size>
			nik_ces auto begin(ArrayStruct<Type, Size> & arr) { return arr.value; }

		// end:

			template<typename Type, auto Size>
			nik_ces auto end(ArrayStruct<Type, Size> & arr) { return arr.value + Size; }

		// apply:

			template
			<
				typename Type, auto Size,
				typename F, auto InSize, auto... Params,
				typename InType, typename... InTypes
			>
			nik_ces auto apply(InType in, InTypes... ins)
			{
				ArrayStruct<Type, Size> arr{};

				F::template result<Params...>(begin(arr), in, in + InSize, ins...);

				return arr;
			}

		// sift:

			template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
			nik_ces auto sift(nik_vp(indices)(auto_pack<Is...>*))
			{
				constexpr auto Size	= Leng + 1;
				constexpr auto arr	= apply<Type, Size, ArrayModule::Sift, Leng, p>(Arr);
				constexpr auto leng	= arr.value[Leng];

				if constexpr (leng != sizeof...(Is)) return arr;
				else return array<Type, arr.value[Is]...>;
			}
	};

	using ArrayStructModule = module<Module::array_struct>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// near linear apply:

	// -> V:

		template<typename Type, typename F, auto... As, auto... Ps, auto... Is>
		constexpr auto V_apply(nik_avp(auto_pack<Ps...>*), nik_avp(auto_pack<Is...>*))
		{
			constexpr auto Size	= sizeof...(Is);
			constexpr auto arr	= ArrayStructModule::template apply<Type, Size, F, Ps...>(As...);

			return array<Type, arr.value[Is]...>;
		}

	// -> U:

		template<typename Type, typename F, auto... As, auto... Ps, auto... Is>
		constexpr auto U_apply(nik_avp(auto_pack<Ps...>*), nik_avp(auto_pack<Is...>*))
		{
			constexpr auto Size	= sizeof...(Is);
			constexpr auto arr	= ArrayStructModule::apply<Type, Size, F, Ps...>(As...);

			return U_pack_Vs<arr.value[Is]...>;
		}

/***********************************************************************************************************************/

// sequence:

	// -> V:

		template<typename Type, auto f, auto Leng, typename Indices>
		constexpr auto V_sequence(Indices indices)
			{ return V_apply<Type, ArrayModule::Sequence, decltype(Leng){0}>(U_pack_Vs<Leng, f>, indices); }

	// -> U:

		template<typename Type, auto f, auto Leng, typename Indices>
		constexpr auto U_sequence(Indices indices)
			{ return U_apply<Type, ArrayModule::Sequence, decltype(Leng){0}>(U_pack_Vs<Leng, f>, indices); }

/***********************************************************************************************************************/

// map:

	// -> V:

		template<typename Type, auto f, auto Arr, auto Leng, typename Indices>
		constexpr auto V_map(Indices indices)
			{ return V_apply<Type, ArrayModule::Map, Arr>(U_pack_Vs<Leng, f>, indices); }

	// -> U:

		template<typename Type, auto f, auto Arr, auto Leng, typename Indices>
		constexpr auto U_map(Indices indices)
			{ return U_apply<Type, ArrayModule::Map, Arr>(U_pack_Vs<Leng, f>, indices); }

/***********************************************************************************************************************/

// fold:

	// -> V:

		template<typename Type, auto f, auto init, auto Arr, auto Leng>
		constexpr auto V_fold()
			{ return V_apply<Type, ArrayModule::Fold, Arr>(U_pack_Vs<Leng, f, init>, U_pack_Vs<0>); }

	// -> U:

		template<typename Type, auto f, auto init, auto Arr, auto Leng>
		constexpr auto U_fold()
			{ return U_apply<Type, ArrayModule::Fold, Arr>(U_pack_Vs<Leng, f, init>, U_pack_Vs<0>); }

/***********************************************************************************************************************/

// find:

	// -> V:

		template<typename Type, auto p, auto Arr, auto Leng>
		constexpr auto V_find()
			{ return V_apply<Type, ArrayModule::Find, Arr>(U_pack_Vs<Leng, Leng, p>, U_pack_Vs<0>); }

	// -> U:

		template<typename Type, auto p, auto Arr, auto Leng>
		constexpr auto U_find()
			{ return U_apply<Type, ArrayModule::Find, Arr>(U_pack_Vs<Leng, Leng, p>, U_pack_Vs<0>); }

/***********************************************************************************************************************/

// sift:

	// -> V:

		template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
		constexpr auto V_sift(nik_vp(indices)(auto_pack<Is...>*))
		{
			constexpr auto Size	= Leng + 1;
			constexpr auto arr	= ArrayStructModule::template apply<Type, Size, ArrayModule::Sift, Leng, p>(Arr);
			constexpr auto leng	= arr.value[Leng];

			if constexpr (leng != sizeof...(Is)) return arr;
			else return array<Type, arr.value[Is]...>;
		}

/*
		template<typename Type, auto p, auto Arr, auto Leng, auto I0, auto... Is>
		constexpr auto V_sift(nik_vp(indices)(auto_pack<I0, Is...>*))
		{
			constexpr auto Size	= sizeof...(Is) + 1;
			constexpr auto arr	= apply<Type, Size, ArrayModule::Sift, Leng, p>(Arr);

			return array<Type, arr.value[Is]...>;
		}
*/

	// -> U:

/*
		template<typename Type, auto p, auto Arr, auto Leng, auto I0, auto... Is>
		constexpr auto U_sift(nik_vp(indices)(auto_pack<I0, Is...>*))
		{
			constexpr auto Size	= sizeof...(Is) + 1;
			constexpr auto arr	= apply<Type, Size, ArrayModule::Sift, Leng, p>(Arr);

			return U_pack_Vs<arr.value[Is]...>;
		}
*/

/***********************************************************************************************************************/

// subsequence:

/*
	// -> V:

		template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
		constexpr auto V_subsequence(nik_vp(indices)(auto_pack<Is...>*))
			{ return V_apply<Type, ArrayModule::Sift, Arr>(U_pack_Vs<Leng, sizeof...(Is), p>, indices); }

	// -> U:

		template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
		constexpr auto U_subsequence(nik_vp(indices)(auto_pack<Is...>*))
			{ return U_apply<Type, ArrayModule::Sift, Arr>(U_pack_Vs<Leng, sizeof...(Is), p>, indices); }
*/

/***********************************************************************************************************************/

// zip:

	// -> V:

		template<typename Type, auto f, auto Arr1, auto Leng1, auto Arr2, typename Indices>
		constexpr auto V_zip(Indices indices)
			{ return V_apply<Type, ArrayModule::Zip, Arr1, Arr2>(U_pack_Vs<Leng1, f>, indices); }

	// -> U:

		template<typename Type, auto f, auto Arr1, auto Leng1, auto Arr2, typename Indices>
		constexpr auto U_zip(Indices indices)
			{ return U_apply<Type, ArrayModule::Zip, Arr1, Arr2>(U_pack_Vs<Leng1, f>, indices); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// overload:

	struct Overload
	{
		nik_ces key_type id				=  0;

		// comparision:

		nik_ces key_type same				=  1;

		nik_ces key_type equal				=  2;
		nik_ces key_type not_equal			=  3;
		nik_ces key_type less_than			=  4;
		nik_ces key_type less_than_or_equal		=  5;
		nik_ces key_type greater_than			=  6;
		nik_ces key_type greater_than_or_equal		=  7;

		nik_ces key_type is_zero			=  8;
		nik_ces key_type is_value			=  9;

		// logical:

		nik_ces key_type not_				= 10;
		nik_ces key_type and_				= 11;
		nik_ces key_type or_				= 12;

		// bitwise:

		nik_ces key_type upshift			= 13;
		nik_ces key_type downshift			= 14;

		// arithmetic:

		nik_ces key_type add				= 15;
		nik_ces key_type subtract			= 16;
		nik_ces key_type multiply			= 17;
		nik_ces key_type divide				= 18;
		nik_ces key_type modulo				= 19;

		nik_ces key_type increment			= 20;
		nik_ces key_type decrement			= 21;

		// algebraic:

		nik_ces key_type product			= 22;

		// computational:

		nik_ces key_type apply				= 23;
		nik_ces key_type alias				= 24;

		// functional:

		nik_ces key_type length				= 25;
		nik_ces key_type map				= 26;
		nik_ces key_type zip				= 27;

		nik_ces key_type is_null			= 28;
		nik_ces key_type cons				= 29;
		nik_ces key_type push				= 30;
		nik_ces key_type car				= 31;
		nik_ces key_type cdr				= 32;
		nik_ces key_type cadr				= 33;
		nik_ces key_type unite				= 34;
		nik_ces key_type find				= 35;

		nik_ces index_type match(const bool *k, cindex_type size)
		{
			const bool *b = k;
			const bool *e = k + size;

			while (k != e && !*k) ++k;

			return k - b;
		}

		template<key_type Op, auto... Vs>
		nik_ces auto result = U_pack_Vs<Op, Vs...>;
	};

	// comparison:

	template<auto V0, auto V1> constexpr auto Overload::result < Overload::same , V0, V1 > = false;
	template<auto V>           constexpr auto Overload::result < Overload::same , V, V   > = true;

	template<auto... Vs> constexpr auto Overload::result < Overload::equal                 , Vs...> = (... == Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::not_equal             , Vs...> = (... != Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::less_than             , Vs...> = (... <  Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::less_than_or_equal    , Vs...> = (... <= Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::greater_than          , Vs...> = (... >  Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::greater_than_or_equal , Vs...> = (... >= Vs);

	template<auto... Vs> constexpr auto Overload::result < Overload::is_zero               , Vs...> = (... && (Vs == 0));
	template<auto V, auto... Vs> constexpr auto Overload::result < Overload::is_value , V  , Vs...> = (... && (Vs == V));

	// logical:

	template<auto V> constexpr auto Overload::result < Overload::not_                      , V    > = !V;
	template<auto... Vs> constexpr auto Overload::result < Overload::and_                  , Vs...> = (... && Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::or_                   , Vs...> = (... || Vs);

	// bitwise:

	template<auto... Vs> constexpr auto Overload::result < Overload::upshift               , Vs...> = (... << Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::downshift             , Vs...> = (... >> Vs);

	// arithmetic:

	template<auto... Vs> constexpr auto Overload::result < Overload::add                   , Vs...> = (... +  Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::subtract              , Vs...> = (... -  Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::multiply              , Vs...> = (... *  Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::divide                , Vs...> = (... /  Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::modulo                , Vs...> = (... %  Vs);

	template<auto V>     constexpr auto Overload::result < Overload::increment             , V    > = V+1;
	template<auto V>     constexpr auto Overload::result < Overload::decrement             , V    > = V-1;

	// algebraic:

	template<auto V0, auto V1> constexpr auto Overload::result < Overload::product      , V0 , V1 > = pair(V0, V1);

	// computational:

	template<auto F, auto... Vs>
	constexpr auto Overload::result < Overload::apply , F , Vs... > = F(Vs...);

	template<auto F, auto... Vs>
	constexpr auto Overload::result < Overload::alias , F , Vs... > = T_store_U<F>::template result<Vs...>;

	// functional:

	template<auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto Overload::result < Overload::length , p > = sizeof...(Vs);

	template
	<
		auto Op, auto... F, nik_vp(op)(auto_pack<Op, F...>*),
		auto... Vs, nik_vp(p)(auto_pack<Vs...>*)
	>
	constexpr auto Overload::result < Overload::map , op , p > = U_pack_Vs
	<
		Overload::template result<Op, F..., Vs>...
	>;

	template
	<
		auto Op, auto... F, nik_vp(op)(auto_pack<Op, F...>*),
		auto... Vs, nik_vp(p0)(auto_pack<Vs...>*),
		auto... Ws, nik_vp(p1)(auto_pack<Ws...>*)
	>
	constexpr auto Overload::result < Overload::zip , op , p0 , p1 > = U_pack_Vs
	<
		Overload::template result<Op, F..., Vs, Ws>...
	>;

	template<auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto Overload::result < Overload::is_null , p > = (sizeof...(Vs) == 0);

	template<auto V0, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto Overload::result < Overload::cons , V0, p > = U_pack_Vs<V0, Vs...>;

	template<auto V0, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto Overload::result < Overload::push , V0, p > = U_pack_Vs<Vs..., V0>;

	template<auto V0, auto... Vs, nik_vp(p)(auto_pack<V0, Vs...>*)>
	constexpr auto Overload::result < Overload::car , p > = V0;

	template<auto V0, auto... Vs, nik_vp(p)(auto_pack<V0, Vs...>*)>
	constexpr auto Overload::result < Overload::cdr , p > = U_pack_Vs<Vs...>;

	template<auto V0, auto V1, auto... Vs, nik_vp(p)(auto_pack<V0, V1, Vs...>*)>
	constexpr auto Overload::result < Overload::cadr , p > = V1;

	template<auto... Vs, nik_vp(p0)(auto_pack<Vs...>*), auto... Ws, nik_vp(p1)(auto_pack<Ws...>*), auto... Xs>
	constexpr auto Overload::result < Overload::unite , p0, p1, Xs... > = U_pack_Vs<Vs..., Xs..., Ws...>;

	template
	<
		auto Op, auto... F, nik_vp(op)(auto_pack<Op, F...>*),
		auto... Vs, nik_vp(p)(auto_pack<Vs...>*),
		auto... Ws
	>
	constexpr auto Overload::result < Overload::find , op , p , Ws... > = Overload::match
	(
		array<bool, Overload::template result<Op, F..., Ws..., Vs>...>, sizeof...(Vs)
	);

/***********************************************************************************************************************/

	// comparision:

	template<auto... Vs> constexpr auto same_op			= U_pack_Vs<Overload::same, Vs...>;

	template<auto... Vs> constexpr auto equal_op			= U_pack_Vs<Overload::equal, Vs...>;
	template<auto... Vs> constexpr auto not_equal_op		= U_pack_Vs<Overload::not_equal, Vs...>;
	template<auto... Vs> constexpr auto less_than_op		= U_pack_Vs<Overload::less_than, Vs...>;
	template<auto... Vs> constexpr auto less_than_or_equal_op	= U_pack_Vs<Overload::less_than_or_equal, Vs...>;
	template<auto... Vs> constexpr auto greater_than_op		= U_pack_Vs<Overload::greater_than, Vs...>;
	template<auto... Vs> constexpr auto greater_than_or_equal_op	= U_pack_Vs<Overload::greater_than_or_equal, Vs...>;

	template<auto... Vs> constexpr auto is_zero_op			= U_pack_Vs<Overload::is_zero, Vs...>;
	template<auto... Vs> constexpr auto is_value_op			= U_pack_Vs<Overload::is_value, Vs...>;

	// logical:

	template<auto... Vs> constexpr auto not__op			= U_pack_Vs<Overload::not_, Vs...>;
	template<auto... Vs> constexpr auto and__op			= U_pack_Vs<Overload::and_, Vs...>;
	template<auto... Vs> constexpr auto or__op			= U_pack_Vs<Overload::or_, Vs...>;

	// bitwise:

	template<auto... Vs> constexpr auto upshift_op			= U_pack_Vs<Overload::upshift, Vs...>;
	template<auto... Vs> constexpr auto downshift_op		= U_pack_Vs<Overload::downshift, Vs...>;

	// arithmetic:

	template<auto... Vs> constexpr auto add_op			= U_pack_Vs<Overload::add, Vs...>;
	template<auto... Vs> constexpr auto subtract_op			= U_pack_Vs<Overload::subtract, Vs...>;
	template<auto... Vs> constexpr auto multiply_op			= U_pack_Vs<Overload::multiply, Vs...>;
	template<auto... Vs> constexpr auto divide_op			= U_pack_Vs<Overload::divide, Vs...>;
	template<auto... Vs> constexpr auto modulo_op			= U_pack_Vs<Overload::modulo, Vs...>;

	template<auto... Vs> constexpr auto increment_op		= U_pack_Vs<Overload::increment, Vs...>;
	template<auto... Vs> constexpr auto decrement_op		= U_pack_Vs<Overload::decrement, Vs...>;

	// algebraic:

	template<auto... Vs> constexpr auto product_op			= U_pack_Vs<Overload::product, Vs...>;

	// computational:

	template<auto... Vs> constexpr auto apply_op			= U_pack_Vs<Overload::apply, Vs...>;
	template<auto... Vs> constexpr auto alias_op			= U_pack_Vs<Overload::alias, Vs...>;

	// functional:

	template<auto... Vs> constexpr auto length_op			= U_pack_Vs<Overload::length, Vs...>;
	template<auto... Vs> constexpr auto map_op			= U_pack_Vs<Overload::map, Vs...>;
	template<auto... Vs> constexpr auto zip_op			= U_pack_Vs<Overload::zip, Vs...>;

	template<auto... Vs> constexpr auto is_null_op			= U_pack_Vs<Overload::is_null, Vs...>;
	template<auto... Vs> constexpr auto cons_op			= U_pack_Vs<Overload::cons, Vs...>;
	template<auto... Vs> constexpr auto push_op			= U_pack_Vs<Overload::push, Vs...>;
	template<auto... Vs> constexpr auto car_op			= U_pack_Vs<Overload::car, Vs...>;
	template<auto... Vs> constexpr auto cdr_op			= U_pack_Vs<Overload::cdr, Vs...>;
	template<auto... Vs> constexpr auto unite_op			= U_pack_Vs<Overload::unite, Vs...>;
	template<auto... Vs> constexpr auto find_op			= U_pack_Vs<Overload::find, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machination:

	template<typename T1, typename T2>
	struct machination
	{
		T1 s1;
		T2 s2;

		constexpr machination(const T1 & _s1, const T2 & _s2) : s1{_s1}, s2{_s2} { }
	};

/***********************************************************************************************************************/

// is machination:

	template<typename T>
	constexpr bool is_machination = false;

	template<typename T1, typename T2> constexpr bool is_machination <       machination<T1, T2>   > = true;
	template<typename T1, typename T2> constexpr bool is_machination < const machination<T1, T2>   > = true;
	template<typename T1, typename T2> constexpr bool is_machination < const machination<T1, T2> & > = true;

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
		nik_ces key_type act					= 5;

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

	constexpr auto _register	= MI::_register;
	constexpr auto _junction	= MI::_junction;
	constexpr auto _constant	= MI::_constant;
	constexpr auto _argument	= MI::_argument;

	constexpr auto _h0		= MI::h0;
	constexpr auto _h0_write	= MI::h0_write;
	constexpr auto _h1		= MI::h1;
	constexpr auto _h1_pair		= MI::h1_pair;
	constexpr auto _value		= MI::value;

	template<index_type... Vs>
	constexpr instr_type instruction = array<index_type, sizeof...(Vs), Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// controllers:

/***********************************************************************************************************************/

	struct MachineContr
	{
		using type						= instr_type const * const;

		nik_ces key_type size					= 0;

		nik_ces index_type length (type l)			{ return l[size][MI::size]; }
	};

	using MC								= MachineContr;
	using contr_type							= typename MC::type;

	template<instr_type... Vs>
	constexpr contr_type controller = array<instr_type, array<index_type, sizeof...(Vs)>, Vs...>;

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
		nik_ces key_type fold		=  4;
		nik_ces key_type cascade	=  5;

		nik_ces key_type sifter		=  6;
		nik_ces key_type right		=  7;
		nik_ces key_type lookup		=  8;

		nik_ces key_type filter		=  9;
		nik_ces key_type left		= 10;
		nik_ces key_type split		= 11;
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
			nik_ces auto result = Overload::template result<Overload::cadr, V0>;
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
		nik_ces auto result(Pack p) { return machination(U_pack_Vs<rtn>, U_pack_Vs<U_restore_T<Pack>, n, Vs...>); }
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

		template<auto d, auto n, auto... Vs>
		nik_ces auto result = machination(s1, U_pack_Vs<n, Vs...>);
	};

	template<key_type... filler>
	struct block<BN::segment, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto... Vs>
		nik_ces auto result = U_pack_Vs<Vs...>;
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

// (action) fold:

	template<key_type... filler>
	struct block<BN::fold, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto V, auto... Vs, auto Op, auto... F>
		nik_ces auto result(nik_vp(m)(auto_pack<Op, F...>*)) { return machination(m, U_pack_Vs<n, V, Vs...>); }
	};

	template<key_type... filler>
	struct block<BN::fold, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto V, auto... Vs, auto Op, auto... F>
		nik_ces auto result(nik_vp(m)(auto_pack<Op, F...>*)) { return V; }
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
			constexpr auto val = T_store_U<Op>::template result<d, V, V0>;

			if constexpr (is_machination<decltype(val)>)

				return machination(U_pack_Vs<Op>, U_pack_Vs<BT::id, n, val.s1, val.s2, Vs...>);
			else
				return NIK_CASCADE_BLOCK(d, n, Op, val, Vs);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// call/recall:

/***********************************************************************************************************************/

// action:

	// call:

		template<key_type... filler>
		struct machine<MN::call, MT::action, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto... Xs, typename... Heaps>
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::dec];

				if constexpr (n >= d) // analogous to returning a machination.

					return NIK_MACHINE(0, MT::action, c, i, Vs)(H0, H1, Hs...);
				else
				{
					constexpr auto ctn = ins[MI::ctn];
					constexpr auto act = ins[MI::act];
					constexpr auto val = Overload::template result<act, Ws...>;

					if constexpr (ctn == MI::h1)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

					else if constexpr (ctn == MI::h1_pair)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
					else
						return val;
				}
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::action, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto... Xs, typename... Heaps>
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::dec];

				if constexpr (n >= d) // analogous to returning a machination.

					return NIK_MACHINE(0, MT::action, c, i, Vs)(H0, H1, Hs...);
				else
				{
					constexpr auto ctn	= ins[MI::ctn];
					constexpr auto act	= ins[MI::act];
					constexpr auto val	= Overload::template result<act, Ws...>;

					if constexpr (ctn == MI::h1)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

					else if constexpr (ctn == MI::h1_pair)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
					else
						return val;
				}
			}
		};

/***********************************************************************************************************************/

// copy:

	// register:

		template<key_type... filler>
		struct machine<MN::call, MT::copy_r_pos, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, typename... Heaps>
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), Heaps... Hs)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::pos];
				constexpr auto ctn	= ins[MI::ctn];
				constexpr auto val	= NIK_VARIABLE_BLOCK(3, d, n, BN::sifter, Vs);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.s1, val.s2, H0, Hs...);

				else if constexpr (ctn == MI::h0)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, Hs...);

				else if constexpr (ctn == MI::h0_write)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(val, Hs...);
				else
					return val;
			}
		};

	// junction:

		template<key_type... filler>
		struct machine<MN::call, MT::copy_j_pos, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto... Xs, typename... Heaps>
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::pos];
				constexpr auto ctn	= ins[MI::ctn];
				constexpr auto val	= NIK_VARIABLE_BLOCK(3, d, n, BN::sifter, Xs);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.s1, val.s2, H0, H1, Hs...);

				else if constexpr (ctn == MI::h0)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, H1, Hs...);

				else if constexpr (ctn == MI::h0_write)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(val, H1, Hs...);
				else
					return val;
			}
		};

	// constant:

		template<key_type... filler>
		struct machine<MN::call, MT::copy_c_pos, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto... Ws, typename Heap1, auto... Ys, typename... Args
			>
			nik_ces auto result
			(
				nik_vp(H0)(auto_pack<Ws...>*), Heap1 H1,
				nik_vp(H2)(auto_pack<Ys...>*), Args... As
			)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::pos];
				constexpr auto ctn	= ins[MI::ctn];
				constexpr auto val	= NIK_VARIABLE_BLOCK(3, d, n, BN::sifter, Ys);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.s1, val.s2, H0, H1, H2, As...);

				else if constexpr (ctn == MI::h0)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, H1, H2, As...);

				else if constexpr (ctn == MI::h0_write)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(val, H1, H2, As...);
				else
					return val;
			}
		};

	// argument:

		template<key_type... filler>
		struct machine<MN::call, MT::copy_a_pos, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto... Ws, typename Heap1, typename Heap2, typename... Args
			>
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), Heap1 H1, Heap2 H2, Args... As)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::pos];
				constexpr auto ctn	= ins[MI::ctn];
				constexpr auto val	= NIK_VARIABLE_BLOCK(3, d, n, BN::sifter, U_restore_T<Args>);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.s1, val.s2, H0, H1, H2, As...);

				else if constexpr (ctn == MI::h0)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, H1, H2, As...);

				else if constexpr (ctn == MI::h0_write)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(val, H1, H2, As...);
				else
					return val;
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::copy, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto rtn, auto n, auto... _Vs,
				auto... Ws, typename... Heaps
			>
			nik_ces auto result
			(
				nik_avp(auto_pack<rtn>*), nik_avp(auto_pack<n, _Vs...>*),
				nik_vp(H0)(auto_pack<Ws...>*), Heaps... Hs
			)
			{
				constexpr auto ins = MachineDispatch::instr(c, i);
				constexpr auto ctn = ins[MI::ctn];
				constexpr auto val = NIK_VARIABLE_BLOCK(3, d, n, rtn, _Vs);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.s1, val.s2, H0, Hs...);

				else if constexpr (ctn == MI::h0)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, Hs...);

				else if constexpr (ctn == MI::h0_write)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(val, Hs...);
				else
					return val;
			}
		};

/***********************************************************************************************************************/

// cut:

	// register:

		template<key_type... filler>
		struct machine<MN::call, MT::cut_r_pos, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, typename Heap0, auto X0, auto... Xs, typename... Heaps>
			nik_ces auto result(Heap0 H0, nik_vp(H1)(auto_pack<X0, Xs...>*), Heaps... Hs)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::pos];
				constexpr auto val	= NIK_FUNCTION_BLOCK(3, d, n, BN::filter, Vs)(U_null_Vs);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::cut, c, i, Vs)(val.s1, val.s2, H1, Hs...);
				else
				{
					constexpr auto h0 = Overload::template result<Overload::unite, val.v1, val.v2, X0>;

					return NIK_MACHINE(d, MT::id, c, i, Vs)(h0, U_pack_Vs<Xs...>, Hs...);
				}
			}
		};

	// argument:

		template<key_type... filler>
		struct machine<MN::call, MT::cut_a_pos, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				typename Heap0, auto X0, auto... Xs, typename Heap2, typename... Args
			>
			nik_ces auto result(Heap0 H0, nik_vp(H1)(auto_pack<X0, Xs...>*), Heap2 H2, Args... As)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::pos];
				constexpr auto val	= NIK_FUNCTION_BLOCK(3, d, n, BN::filter, U_restore_T<Args>)(U_null_Vs);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::cut, c, i, Vs)(val.s1, val.s2, H1, H2, As...);
				else
				{
					constexpr auto h0 = Overload::template result<Overload::unite, val.v1, val.v2, X0>;

					return NIK_MACHINE(d, MT::id, c, i, Vs)(h0, U_pack_Vs<Xs...>, H2, As...);
				}
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::cut, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto rtn, auto pack, auto n, auto... _Vs,
				auto X0, auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_avp(auto_pack<rtn>*), nik_avp(auto_pack<pack, n, _Vs...>*),
				nik_vp(H1)(auto_pack<X0, Xs...>*), Heaps... Hs
			)
			{
				constexpr auto val = NIK_FUNCTION_BLOCK(3, d, n, rtn, _Vs)(pack);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::cut, c, i, Vs)(val.s1, val.s2, H1, Hs...);
				else
				{
					constexpr auto h0 = Overload::template result<Overload::unite, val.v1, val.v2, X0>;

					return NIK_MACHINE(d, MT::id, c, i, Vs)(h0, U_pack_Vs<Xs...>, Hs...);
				}
			}
		};

/***********************************************************************************************************************/

// variable:

	// call:

		template<key_type... filler>
		struct machine<MN::call, MT::variable, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto n, auto... Xs, typename... Heaps> 
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<n, Xs...>*), Heaps... Hs)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto rtn	= ins[MI::rtn];
				constexpr auto ctn	= ins[MI::ctn];
				constexpr auto val	= NIK_VARIABLE_BLOCK(9, d, n, rtn, Ws);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::variable, c, i, Vs)(val.s1, val.s2, H1, Hs...);

				else if constexpr (ctn == MI::h1)

					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

				else if constexpr (ctn == MI::h1_pair)

					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
				else
					return val;
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::variable, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto rtn, auto n, auto... _Vs,
				auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_avp(auto_pack<rtn>*), nik_avp(auto_pack<n, _Vs...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				constexpr auto ins = MachineDispatch::instr(c, i);
				constexpr auto ctn = ins[MI::ctn];
				constexpr auto val = NIK_VARIABLE_BLOCK(9, d, n, rtn, _Vs);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::variable, c, i, Vs)(val.s1, val.s2, H1, Hs...);

				else if constexpr (ctn == MI::h1)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

				else if constexpr (ctn == MI::h1_pair)

					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
				else
					return val;
			}
		};

/***********************************************************************************************************************/

// function:

	// call:

		template<key_type... filler>
		struct machine<MN::call, MT::function, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto n, auto... Xs, typename... Heaps>
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<n, Xs...>*), Heaps... Hs)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto rtn	= ins[MI::rtn];
				constexpr auto ctn	= ins[MI::ctn];
				constexpr auto val	= NIK_FUNCTION_BLOCK(9, d, n, rtn, Ws)(U_null_Vs);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::function, c, i, Vs)(val.s1, val.s2, H1, Hs...);

				else if constexpr (ctn == MI::h1 || ctn == MI::h1_pair)

					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
				else
					return val;
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::function, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto rtn, auto pack, auto n, auto... _Vs,
				auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_avp(auto_pack<rtn>*), nik_avp(auto_pack<pack, n, _Vs...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				constexpr auto val = NIK_FUNCTION_BLOCK(9, d, n, rtn, _Vs)(pack);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::function, c, i, Vs)(val.s1, val.s2, H1, Hs...);
				else
					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
			}
		};

/***********************************************************************************************************************/

// cascade:

	// call:

		template<key_type... filler>
		struct machine<MN::call, MT::cascade, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto Op, auto W0, auto... Ws, auto n, auto... Xs, typename... Heaps>
			nik_ces auto result(nik_vp(H0)(auto_pack<Op, W0, Ws...>*), nik_vp(H1)(auto_pack<n, Xs...>*), Heaps... Hs)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto rtn	= ins[MI::rtn];
				constexpr auto ctn	= ins[MI::ctn];
				constexpr auto val	= NIK_CASCADE_BLOCK(d, n, Op, W0, Ws);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::cascade, c, i, Vs)(val.s1, val.s2, H1, Hs...);

				else if constexpr (ctn == MI::h1)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);
				else
					return val;
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::cascade, filler...>
		{
			// BT::id:

			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				typename OpType, auto n, auto _s1, auto _s2, auto... _Vs,
				auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				OpType op, nik_avp(auto_pack<BT::id, n, _s1, _s2, _Vs...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				constexpr auto _c	= controller<instruction<MN::call, MT::internal>>;
				constexpr auto _i	= MachineDispatch::initial_index;
				constexpr auto val	= NIK_BEGIN_MACHINE(d, MT::internal, _c, _i)
								NIK_END_MACHINE(_s1, _s2);

				if constexpr (is_machination<decltype(val)>)
				{
					constexpr auto s2 = U_pack_Vs<BT::id, n, val.s1, val.s2, _Vs...>;

					return NIK_MACHINE(d, MT::cascade, c, i, Vs)(op, s2, H1, Hs...);
				}
				else
					return NIK_MACHINE(d, MT::cascade, c, i, Vs)
						(op, U_pack_Vs<BT::pause, n, val, _Vs...>, H1, Hs...);
			}

			// BT::pause:

			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto Op, auto n, auto _V, auto... _Vs,
				auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_avp(auto_pack<Op>*), nik_avp(auto_pack<BT::pause, n, _V, _Vs...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				constexpr auto val = NIK_CASCADE_BLOCK(d, n, Op, _V, _Vs);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::cascade, c, i, Vs)(val.s1, val.s2, H1, Hs...);
				else
					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);
			}
		};

/***********************************************************************************************************************/

// compel:

	// call:

		template<key_type... filler>
		struct machine<MN::call, MT::compel, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto Op, auto... Ws, auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_vp(H0)(auto_pack<Op, Ws...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::dec];

				if constexpr (n >= d) // analogous to returning a machination.

					return NIK_MACHINE(0, MT::compel, c, i, Vs)(H0, H1, Hs...);
				else
				{
					constexpr auto ctn	= ins[MI::ctn];
					constexpr auto nd	= d+1-n;
					constexpr auto val	= T_store_U<Op>::template result<nd, Ws...>;

					if constexpr (is_machination<decltype(val)>)

						return NIK_MACHINE(d, MT::propel, c, i, Vs)(val.s1, val.s2, H1, Hs...);

					else if constexpr (ctn == MI::h1)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

					else if constexpr (ctn == MI::h1_pair)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
					else
						return val;
				}
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::compel, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto Op, auto... Ws, auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_vp(H0)(auto_pack<Op, Ws...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::dec];

				if constexpr (n >= d) // analogous to returning a machination.

					return NIK_MACHINE(0, MT::compel, c, i, Vs)(H0, H1, Hs...);
				else
				{
					constexpr auto ctn	= ins[MI::ctn];
					constexpr auto nd	= d+1-n;
					constexpr auto val	= T_store_U<Op>::template result<nd, Ws...>;

					if constexpr (is_machination<decltype(val)>)

						return NIK_MACHINE(d, MT::propel, c, i, Vs)(val.s1, val.s2, H1, Hs...);

					else if constexpr (ctn == MI::h1)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

					else if constexpr (ctn == MI::h1_pair)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
					else
						return val;
				}
			}
		};

/***********************************************************************************************************************/

// propel:

	// call: No direct call.

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::propel, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto _m, auto _c, auto _i, auto... _Vs,
				auto... _Hs, auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_avp(auto_pack<_m, _c, _i, _Vs...>*), nik_avp(auto_pack<_Hs...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				constexpr auto ins = MachineDispatch::instr(c, i);
				constexpr auto ctn = ins[MI::ctn];
				constexpr auto val = NIK_MACHINE(d, _m, _c, _i, _Vs)(_Hs...);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::propel, c, i, Vs)(val.s1, val.s2, H1, Hs...);

				else if constexpr (ctn == MI::h1)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

				else if constexpr (ctn == MI::h1_pair)

					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
				else
					return val;
			}
		};

/***********************************************************************************************************************/

// internal:

	// call:

		template<key_type... filler>
		struct machine<MN::call, MT::internal, filler...>
		{
			template<NIK_CONTR_PARAMS, auto _m, auto _c, auto _i, auto... Vs, typename... Heaps>
			nik_ces auto result(Heaps...)
			{
				constexpr auto val = NIK_MACHINE(d, _m, _c, _i, Vs)(U_restore_T<Heaps>...);

				if constexpr (is_machination<decltype(val)>)

					return NIK_BEGIN_MACHINE(d, MT::internal, c, i) NIK_END_MACHINE(val.s1, val.s2);
				else
					return val;
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::internal, filler...>
		{
			template<NIK_CONTR_PARAMS, auto _m, auto _c, auto _i, auto... _Vs, auto... _Hs>
			nik_ces auto result(nik_avp(auto_pack<_m, _c, _i, _Vs...>*), nik_avp(auto_pack<_Hs...>*))
			{
				constexpr auto val = NIK_MACHINE(d, _m, _c, _i, _Vs)(_Hs...);

				if constexpr (is_machination<decltype(val)>)

					return NIK_BEGIN_MACHINE(d, MT::internal, c, i) NIK_END_MACHINE(val.s1, val.s2);
				else
					return val;
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halters:

/***********************************************************************************************************************/

// pause:

	template<key_type... filler>
	struct machine<MN::halt, MT::pause, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps...)
		{
			constexpr auto s1 = U_pack_Vs<m, c, i, Vs...>;
			constexpr auto s2 = U_pack_Vs<U_restore_T<Heaps>...>;

			return machination(s1, s2);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// move:

/***********************************************************************************************************************/

// junction:

	template<key_type... filler>
	struct machine<MN::move_j_all, MT::id, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto... Xs, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs)
		{
			return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., Xs...>, U_null_Vs, Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// paste:

/***********************************************************************************************************************/

// register:

	template<key_type... filler>
	struct machine<MN::paste_r_all, MT::id, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), Heaps... Hs)
		{
			return NIK_MACHINE(d, MT::id, c, i, Ws)(U_null_Vs, Hs...);
		}
	};

// argument:

	template<key_type... filler>
	struct machine<MN::paste_a_all, MT::id, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, typename Heap1, typename Heap2, typename... Args>
		nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), Heap1 H1, Heap2 H2, Args... As)
		{
			return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, H1, H2, Ws...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// go to:

/***********************************************************************************************************************/

// id:

	template<key_type... filler>
	struct machine<MN::go_to, MT::id, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			constexpr auto ins	= MachineDispatch::instr(c, i);
			constexpr auto ni	= ins[MI::pos];

			return NIK_MACHINE(d, MT::id, c, ni, Vs)(Hs...);
		}
	};

// conditional:

	template<key_type... filler>
	struct machine<MN::go_to, MT::conditional, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, typename Heap0, bool X0, auto... Xs, typename... Heaps>
		nik_ces auto result(Heap0 H0, nik_vp(H1)(auto_pack<X0, Xs...>*), Heaps... Hs)
		{
			constexpr auto ins	= MachineDispatch::instr(c, i);
			constexpr auto ni	= X0 ? ins[MI::pos] : i;

			return NIK_MACHINE(d, MT::id, c, ni, Vs)(H0, U_pack_Vs<Xs...>, Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// memoize:

/***********************************************************************************************************************/

// lookup:

	template<key_type... filler>
	struct machine<MN::memoize, MT::lookup, filler...>
	{
		template<auto W, auto Z>
		nik_ces bool match = Overload::template result
		<
			Overload::same, W,
			Overload::template result<Overload::car, Z>
		>;

		template
		<
			NIK_CONTR_PARAMS, auto... Vs,
			auto W0, auto... Xs, typename Heap2, auto... Zs, typename... Args
		>
		nik_ces auto result
		(
			nik_vp(H0)(auto_pack<W0>*),
			nik_vp(H1)(auto_pack<Xs...>*), Heap2 H2,
			nik_vp(A0)(auto_pack<Zs...>*), Args... As
		)
		{
			constexpr auto size	= sizeof...(Zs);
			constexpr auto arr	= array<bool, match<W0, Zs>...>;
			constexpr auto pos	= Overload::match(arr, size);

			if constexpr (pos == size)

				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, H1, H2, A0, As...);
			else
			{
				constexpr auto ins = MachineDispatch::instr(c, i);
				constexpr auto ni  = ins[MI::pos];

				return NIK_MACHINE(d, MT::id, c, ni, Vs)(A0, U_pack_Vs<pos, Xs...>, H2, A0, As...);
			}
		}
	};

/***********************************************************************************************************************/

// insert:

	template<key_type... filler>
	struct machine<MN::memoize, MT::insert, filler...>
	{
		template
		<
			NIK_CONTR_PARAMS, auto... Vs,
			auto W0, auto X0, auto... Xs, typename Heap2, auto... Zs, typename... Args
		>
		nik_ces auto result
		(
			nik_vp(H0)(auto_pack<W0>*),
			nik_vp(H1)(auto_pack<X0, Xs...>*), Heap2 H2,
			nik_vp(A0)(auto_pack<Zs...>*), Args... As
		)
		{
			constexpr auto Z0 = U_pack_Vs<W0, X0>;
			constexpr auto a0 = U_pack_Vs<Z0, Zs...>;

			return pair(a0, X0);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// instructions:

	template<key_type act, key_type ctn = _h1, depth_type dec = _two> // reverse order for user friendliness:
	constexpr instr_type action = instruction<MN::call, MT::action, dec, ctn, act>;

		// comparision:

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto same = action<Overload::same, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto equal = action<Overload::equal, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto not_equal = action<Overload::not_equal, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto less_than = action<Overload::less_than, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto less_than_or_equal = action<Overload::less_than_or_equal, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto greater_than = action<Overload::greater_than, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto greater_than_or_equal = action<Overload::greater_than_or_equal, ctn, dec>;

		//

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto is_zero = action<Overload::is_zero, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto is_value = action<Overload::is_value, ctn, dec>;

		// logical:

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto not_ = action<Overload::not_, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto and_ = action<Overload::and_, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto or_ = action<Overload::or_, ctn, dec>;

		// bitwise:

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto upshift = action<Overload::upshift, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto downshift = action<Overload::downshift, ctn, dec>;

		// arithmetic:

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto add = action<Overload::add, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto subtract = action<Overload::subtract, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto multiply = action<Overload::multiply, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto divide = action<Overload::divide, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto modulo = action<Overload::modulo, ctn, dec>;

		//

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto increment = action<Overload::increment, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto decrement = action<Overload::decrement, ctn, dec>;

		// algebraic:

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto product = action<Overload::product, ctn, dec>;

		// computational:

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto apply = action<Overload::apply, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _three>
		constexpr auto alias = action<Overload::alias, ctn, dec>;

		// functional:

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto length = action<Overload::length, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto map = action<Overload::map, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto zip = action<Overload::zip, ctn, dec>;

		//

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto is_null = action<Overload::is_null, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto cons = action<Overload::cons, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto push = action<Overload::push, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto car = action<Overload::car, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto cdr = action<Overload::cdr, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto unite = action<Overload::unite, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto find = action<Overload::find, ctn, dec>;

	template<index_type pos, key_type loc, key_type ctn = _h0> // reverse order for user friendliness.
	constexpr instr_type copy = instruction<MN::call, MI::copy_note(loc), pos, ctn>;

		template<index_type pos, key_type loc>
		constexpr instr_type write = copy<pos, loc, _h0_write>;

		template<index_type pos, key_type loc>
		constexpr instr_type value = copy<pos, loc, _value>;

	template<index_type pos, key_type loc> // reverse order for user friendliness.
	constexpr instr_type cut = instruction<MN::call, MI::cut_note(loc), pos>;

	template<key_type rtn, key_type ctn = _h1>
	constexpr instr_type variable = instruction<MN::call, MT::variable, rtn, ctn>;

	template<key_type rtn, key_type ctn = _h1>
	constexpr instr_type function = instruction<MN::call, MT::function, rtn, ctn>;

	template<key_type rtn, key_type ctn = _h1>
	constexpr instr_type cascade = instruction<MN::call, MT::cascade, rtn, ctn>;

	template<key_type ctn = _h1, depth_type dec = _two>
	constexpr instr_type compel = instruction<MN::call, MT::compel, dec, ctn>;

	template<key_type...>
	constexpr instr_type internal = instruction<MN::call, MT::internal>;

	template<key_type...>
	constexpr instr_type lift  = instruction<MN::move_j_all, MT::id>;

	template<key_type loc>
	constexpr instr_type paste = instruction<MI::paste_name(loc), MT::id>;

	template<key_type...>
	constexpr instr_type cycle = instruction<MN::go_to, MT::id, _zero>;

	template<key_type pos>
	constexpr instr_type branch = instruction<MN::go_to, MT::conditional, pos>;

	template<key_type pos>
	constexpr instr_type mem_lookup = instruction<MN::memoize, MT::lookup, pos>;

	template<key_type...>
	constexpr instr_type mem_insert = instruction<MN::memoize, MT::insert>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// start:

	template<auto d, auto prog, auto... Vs, typename CHeap, typename... Args>
	constexpr auto start(CHeap ch, Args... As)
	{
		constexpr auto m	= MT::id;
		constexpr auto c	= controller<internal<>>;
		constexpr auto i	= MachineDispatch::initial_index;

		return NIK_BEGIN_MACHINE(d, m, c, i),

				m, prog, i, Vs...

		NIK_END_MACHINE(U_null_Vs, U_null_Vs, ch, As...);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

/***********************************************************************************************************************/
/***********************************************************************************************************************/

