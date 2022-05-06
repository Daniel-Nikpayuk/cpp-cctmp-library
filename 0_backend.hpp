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

		nik_ces key_type equal				=  1;
		nik_ces key_type not_equal			=  2;
		nik_ces key_type less_than			=  3;
		nik_ces key_type less_than_or_equal		=  4;
		nik_ces key_type greater_than			=  5;
		nik_ces key_type greater_than_or_equal		=  6;

		nik_ces key_type is_zero			=  7;
		nik_ces key_type is_value			=  8;

		// logical:

		nik_ces key_type and_				=  9;
		nik_ces key_type or_				= 10;

		// bitwise:

		nik_ces key_type upshift			= 11;
		nik_ces key_type downshift			= 12;

		// arithmetic:

		nik_ces key_type add				= 13;
		nik_ces key_type subtract			= 14;
		nik_ces key_type multiply			= 15;
		nik_ces key_type divide				= 16;
		nik_ces key_type modulo				= 17;

		nik_ces key_type increment			= 18;
		nik_ces key_type decrement			= 19;

		// functional:

		nik_ces key_type is_null			= 20;
		nik_ces key_type cons				= 21;
		nik_ces key_type push				= 22;
		nik_ces key_type car				= 23;
		nik_ces key_type cdr				= 24;
		nik_ces key_type cat				= 25;

		template<auto Op, auto... Vs>
		nik_ces auto apply = U_pack_Vs<Op, Vs...>;
	};

	// comparison:

	template<auto... Vs> constexpr auto Overload::apply < Overload::equal                 , Vs...> = (... == Vs);
	template<auto... Vs> constexpr auto Overload::apply < Overload::not_equal             , Vs...> = (... != Vs);
	template<auto... Vs> constexpr auto Overload::apply < Overload::less_than             , Vs...> = (... <  Vs);
	template<auto... Vs> constexpr auto Overload::apply < Overload::less_than_or_equal    , Vs...> = (... <= Vs);
	template<auto... Vs> constexpr auto Overload::apply < Overload::greater_than          , Vs...> = (... >  Vs);
	template<auto... Vs> constexpr auto Overload::apply < Overload::greater_than_or_equal , Vs...> = (... >= Vs);

	template<auto... Vs> constexpr auto Overload::apply < Overload::is_zero               , Vs...> = (... && (Vs == 0));
	template<auto V, auto... Vs> constexpr auto Overload::apply < Overload::is_value , V  , Vs...> = (... && (Vs == V));

	// logical:

	template<auto... Vs> constexpr auto Overload::apply < Overload::and_                  , Vs...> = (... && Vs);
	template<auto... Vs> constexpr auto Overload::apply < Overload::or_                   , Vs...> = (... || Vs);

	// bitwise:

	template<auto... Vs> constexpr auto Overload::apply < Overload::upshift               , Vs...> = (... << Vs);
	template<auto... Vs> constexpr auto Overload::apply < Overload::downshift             , Vs...> = (... >> Vs);

	// arithmetic:

	template<auto... Vs> constexpr auto Overload::apply < Overload::add                   , Vs...> = (... +  Vs);
	template<auto... Vs> constexpr auto Overload::apply < Overload::subtract              , Vs...> = (... -  Vs);
	template<auto... Vs> constexpr auto Overload::apply < Overload::multiply              , Vs...> = (... *  Vs);
	template<auto... Vs> constexpr auto Overload::apply < Overload::divide                , Vs...> = (... /  Vs);
	template<auto... Vs> constexpr auto Overload::apply < Overload::modulo                , Vs...> = (... %  Vs);

	template<auto V>     constexpr auto Overload::apply < Overload::increment             , V    > = V+1;
	template<auto V>     constexpr auto Overload::apply < Overload::decrement             , V    > = V-1;

	// functional:

	template<auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto Overload::apply < Overload::is_null , p > = (sizeof...(Vs) == 0);

	template<auto V0, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto Overload::apply < Overload::cons , V0, p > = U_pack_Vs<V0, Vs...>;

	template<auto V0, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto Overload::apply < Overload::push , V0, p > = U_pack_Vs<Vs..., V0>;

	template<auto V0, auto... Vs, nik_vp(p)(auto_pack<V0, Vs...>*)>
	constexpr auto Overload::apply < Overload::car , p > = V0;

	template<auto V0, auto... Vs, nik_vp(p)(auto_pack<V0, Vs...>*)>
	constexpr auto Overload::apply < Overload::cdr , p > = U_pack_Vs<Vs...>;

	template<auto... Vs, nik_vp(p0)(auto_pack<Vs...>*), auto... Ws, nik_vp(p1)(auto_pack<Ws...>*)>
	constexpr auto Overload::apply < Overload::cat , p0, p1 > = U_pack_Vs<Vs..., Ws...>;

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

			nik_ces key_type copy_r_pos			=  4;
			nik_ces key_type copy_c_pos			=  5;
			nik_ces key_type copy_a_pos			=  6;

			nik_ces key_type cut_r_pos			=  7;
			nik_ces key_type cut_a_pos			=  8;

			nik_ces key_type paste_r_all			=  9;
			nik_ces key_type paste_a_all			= 10;

			nik_ces key_type go_to				= 11;
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

			nik_ces key_type internal			=  1;

			nik_ces key_type apply				=  2;
			nik_ces key_type alias				=  3;
			nik_ces key_type action				=  4;

			nik_ces key_type block1				=  5;
			nik_ces key_type block2				=  6;
			nik_ces key_type compel				=  7;
			nik_ces key_type propel				=  8;

			nik_ces key_type pause				=  9;
			nik_ces key_type value				= 10;

			nik_ces key_type insert_at_h0_back		= 11;
			nik_ces key_type insert_at_hs_front		= 12;

			nik_ces key_type conditional			= 13;
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

		nik_ces index_type length     (type i)			{ return i[size]; }
		nik_ces bool       is_optimal (cindex_type n)		{ return (n < _eight); }
	};

	using MI							= MachineInstr;
	using instr_type						= typename MI::type;

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

	using T_program			= MachineDispatch;
	constexpr auto U_program	= U_store_T<T_program>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// block:

	template<key_type...> struct block;

/***********************************************************************************************************************/

// names:

	struct BlockName
	{
		nik_ces key_type id		=  0;

		nik_ces key_type segment	=  1;
		nik_ces key_type sifter		=  2;
		nik_ces key_type filter		=  3;

		nik_ces key_type at		=  4;
		nik_ces key_type cut		=  5;
		nik_ces key_type left		=  6;
		nik_ces key_type right		=  7;

		nik_ces key_type fold		=  8;
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

// sifter:

	template<key_type... filler>
	struct block<BN::sifter, BT::pause, _zero, filler...>
	{
		nik_ces auto s1 = U_pack_Vs<BN::sifter>;

		template<auto d, auto n, auto... Vs>
		nik_ces auto result = machination(s1, U_pack_Vs<n, Vs...>);
	};

	template<key_type... filler>
	struct block<BN::sifter, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto V0, auto...>
		nik_ces auto result = V0;
	};

	NIK_DEFINE_BLOCK_SIFTER_PASS(0)
	NIK_DEFINE_BLOCK_SIFTER_PASS(1)
	NIK_DEFINE_BLOCK_SIFTER_PASS(2)
	NIK_DEFINE_BLOCK_SIFTER_PASS(3)
	NIK_DEFINE_BLOCK_SIFTER_PASS(4)
	NIK_DEFINE_BLOCK_SIFTER_PASS(5)
	NIK_DEFINE_BLOCK_SIFTER_PASS(6)
	NIK_DEFINE_BLOCK_SIFTER_PASS(7)
	NIK_DEFINE_BLOCK_SIFTER_PASS(8)
	NIK_DEFINE_BLOCK_SIFTER_PASS(9)

// filter:

	template<key_type... filler>
	struct block<BN::filter, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto... Vs, typename Pack>
		nik_ces auto result(Pack p)
		{
			constexpr auto s1 = U_pack_Vs<BN::filter, U_restore_T<Pack>>; // it's probably this!

			return machination(s1, U_pack_Vs<n, Vs...>);
		}
	};

	template<key_type... filler>
	struct block<BN::filter, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto V0, auto... Vs, typename Pack>
		nik_ces auto result(Pack p) { return pair(p, U_pack_Vs<Vs...>); }
	};

	NIK_DEFINE_BLOCK_FILTER_PASS(0)
	NIK_DEFINE_BLOCK_FILTER_PASS(1)
	NIK_DEFINE_BLOCK_FILTER_PASS(2)
	NIK_DEFINE_BLOCK_FILTER_PASS(3)
	NIK_DEFINE_BLOCK_FILTER_PASS(4)
	NIK_DEFINE_BLOCK_FILTER_PASS(5)
	NIK_DEFINE_BLOCK_FILTER_PASS(6)
	NIK_DEFINE_BLOCK_FILTER_PASS(7)
	NIK_DEFINE_BLOCK_FILTER_PASS(8)
	NIK_DEFINE_BLOCK_FILTER_PASS(9)

// at:

// cut:

// left:

	template<key_type... filler>
	struct block<BN::left, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto... Vs, typename Pack>
		nik_ces auto result(Pack p)
		{
			constexpr auto s1 = U_pack_Vs<BN::left, U_restore_T<Pack>>;

			return machination(s1, U_pack_Vs<n, Vs...>);
		}
	};

	template<key_type... filler>
	struct block<BN::left, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto... Vs, typename Pack>
		nik_ces auto result(Pack p) { return p; }
	};

	NIK_DEFINE_BLOCK_LEFT_PASS(0)
	NIK_DEFINE_BLOCK_LEFT_PASS(1)
	NIK_DEFINE_BLOCK_LEFT_PASS(2)
	NIK_DEFINE_BLOCK_LEFT_PASS(3)
	NIK_DEFINE_BLOCK_LEFT_PASS(4)
	NIK_DEFINE_BLOCK_LEFT_PASS(5)
	NIK_DEFINE_BLOCK_LEFT_PASS(6)
	NIK_DEFINE_BLOCK_LEFT_PASS(7)
	NIK_DEFINE_BLOCK_LEFT_PASS(8)
	NIK_DEFINE_BLOCK_LEFT_PASS(9)

// right:

	template<key_type... filler>
	struct block<BN::right, BT::pause, _zero, filler...>
	{
		nik_ces auto s1 = U_pack_Vs<BN::right>;

		template<auto d, auto n, auto... Vs>
		nik_ces auto result = machination(s1, U_pack_Vs<n, Vs...>);
	};

	template<key_type... filler>
	struct block<BN::right, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto... Vs>
		nik_ces auto result = U_pack_Vs<Vs...>;
	};

	NIK_DEFINE_BLOCK_RIGHT_PASS(0)
	NIK_DEFINE_BLOCK_RIGHT_PASS(1)
	NIK_DEFINE_BLOCK_RIGHT_PASS(2)
	NIK_DEFINE_BLOCK_RIGHT_PASS(3)
	NIK_DEFINE_BLOCK_RIGHT_PASS(4)
	NIK_DEFINE_BLOCK_RIGHT_PASS(5)
	NIK_DEFINE_BLOCK_RIGHT_PASS(6)
	NIK_DEFINE_BLOCK_RIGHT_PASS(7)
	NIK_DEFINE_BLOCK_RIGHT_PASS(8)
	NIK_DEFINE_BLOCK_RIGHT_PASS(9)

// fold:

	template<key_type... filler>
	struct block<BN::fold, BT::pause, _zero, filler...>
	{
		nik_ces auto s1 = U_pack_Vs<BN::fold>;

		template<auto d, auto n, auto Op, auto V, auto... Vs>
		nik_ces auto result = machination(s1, U_pack_Vs<n, Op, V, Vs...>);
	};

	template<key_type... filler>
	struct block<BN::fold, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto Op, auto V, auto... Vs>
		nik_ces auto result = V;
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
/***********************************************************************************************************************/

// recall:

/***********************************************************************************************************************/

// internal:

	template<key_type... filler>
	struct machine<MN::recall, MT::internal, filler...>
	{
		template
		<
			NIK_CONTR_PARAMS, auto... Vs,
			auto _m, auto _c, auto _i, auto... _Vs,
			auto... _Hs
		>
		nik_ces auto result
		(
			nik_avp(auto_pack<_m, _c, _i, _Vs...>*),
			nik_avp(auto_pack<_Hs...>*)
		)
		{
			constexpr auto val = NIK_MACHINE(d, _m, _c, _i, _Vs)(_Hs...);

			if constexpr (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::internal, c, i, Vs)(val.s1, val.s2);
			else
				return val;
		}
	};

/***********************************************************************************************************************/

// apply:

	template<key_type... filler>
	struct machine<MN::recall, MT::apply, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto Op, auto... Ws, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Op, Ws...>*), Heaps... Hs)
		{
			constexpr auto ins	= MachineDispatch::instr(c, i);
			constexpr auto n	= ins[MI::dec];

			if constexpr (n >= d) // analogous to returning a machination.

				return NIK_MACHINE(0, MT::apply, c, i, Vs)(H0, Hs...);
			else
			{
				constexpr auto val = Op(Ws...);

				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<val>, Hs...);
			}
		}
	};

/***********************************************************************************************************************/

// alias:

	template<key_type... filler>
	struct machine<MN::recall, MT::alias, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto Op, auto... Ws, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Op, Ws...>*), Heaps... Hs)
		{
			constexpr auto ins	= MachineDispatch::instr(c, i);
			constexpr auto n	= ins[MI::dec];

			if constexpr (n >= d) // analogous to returning a machination.

				return NIK_MACHINE(0, MT::alias, c, i, Vs)(H0, Hs...);
			else
			{
				constexpr auto val = T_store_U<Op>::template result<Ws...>;

				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<val>, Hs...);
			}
		}
	};

/***********************************************************************************************************************/

// action:

	template<key_type... filler>
	struct machine<MN::recall, MT::action, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto Op, auto... Ws, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Op, Ws...>*), Heaps... Hs)
		{
			constexpr auto ins	= MachineDispatch::instr(c, i);
			constexpr auto n	= ins[MI::dec];

			if constexpr (n >= d) // analogous to returning a machination.

				return NIK_MACHINE(0, MT::action, c, i, Vs)(H0, Hs...);
			else
			{
				constexpr auto val = Overload::template apply<Op, Ws...>;

				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<val>, Hs...);
			}
		}
	};

/***********************************************************************************************************************/

// block1:

	template<key_type... filler>
	struct machine<MN::recall, MT::block1, filler...>
	{
		template
		<
			NIK_CONTR_PARAMS, auto... Vs,
			auto name, auto n, auto... _Vs,
			auto... Ws, typename... Heaps
		>
		nik_ces auto result
		(
			nik_avp(auto_pack<name>*),
			nik_avp(auto_pack<n, _Vs...>*),
			nik_vp(H0)(auto_pack<Ws...>*),
			Heaps... Hs
		)
		{
			constexpr auto val = NIK_BLOCK(name, d, 3, n, _Vs);

			if constexpr (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::block1, c, i, Vs)(val.s1, val.s2, H0, Hs...);
			else
				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, Hs...);
		}
	};

/***********************************************************************************************************************/

// block2:

	template<key_type... filler>
	struct machine<MN::recall, MT::block2, filler...>
	{
		template
		<
			NIK_CONTR_PARAMS, auto... Vs,
			auto name, auto p, auto n, auto... _Vs,
			typename... Heaps
		>
		nik_ces auto result
		(
			nik_avp(auto_pack<name, p>*),
			nik_avp(auto_pack<n, _Vs...>*),
			Heaps... Hs
		)
		{
			constexpr auto val = NIK_BLOCK(name, d, 3, n, _Vs)(p);

			if constexpr (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::block2, c, i, Vs)(val.s1, val.s2, Hs...);
			else
				return NIK_MACHINE(d, MT::id, c, i, Vs)(val.v1, val.v2, Hs...);
		}
	};

/***********************************************************************************************************************/

// compel:

	template<key_type... filler>
	struct machine<MN::recall, MT::compel, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto Op, auto... Ws, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Op, Ws...>*), Heaps... Hs)
		{
			constexpr auto ins	= MachineDispatch::instr(c, i);
			constexpr auto n	= ins[MI::dec];

			if constexpr (n >= d) // analogous to returning a machination.

				return NIK_MACHINE(0, MT::compel, c, i, Vs)(H0, Hs...);
			else
			{
				constexpr auto nd  = d+1-n;
				constexpr auto val = T_store_U<Op>::template result<nd, Ws...>;

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::propel, c, i, Vs)(val.s1, val.s2, Hs...);
				else
					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<val>, Hs...);
			}
		}
	};

/***********************************************************************************************************************/

// propel:

	template<key_type... filler>
	struct machine<MN::recall, MT::propel, filler...>
	{
		template
		<
			NIK_CONTR_PARAMS, auto... Vs,
			auto _m, auto _c, auto _i, auto... _Vs,
			auto... _Hs, typename... Heaps
		>
		nik_ces auto result
		(
			nik_avp(auto_pack<_m, _c, _i, _Vs...>*),
			nik_avp(auto_pack<_Hs...>*),
			Heaps... Hs
		)
		{
			constexpr auto val = NIK_MACHINE(d, _m, _c, _i, _Vs)(_Hs...);

			if constexpr (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::propel, c, i, Vs)(val.s1, val.s2, Hs...);
			else
				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<val>, Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// call:

/***********************************************************************************************************************/

// apply:

	template<key_type... filler>
	struct machine<MN::call, MT::apply, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto Op, auto... Ws, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Op, Ws...>*), Heaps... Hs)
		{
			constexpr auto ins	= MachineDispatch::instr(c, i);
			constexpr auto n	= ins[MI::dec];

			if constexpr (n >= d) // analogous to returning a machination.

				return NIK_MACHINE(0, MT::apply, c, i, Vs)(H0, Hs...);
			else
			{
				constexpr auto val = Op(Ws...);

				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<val>, Hs...);
			}
		}
	};

/***********************************************************************************************************************/

// alias:

	template<key_type... filler>
	struct machine<MN::call, MT::alias, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto Op, auto... Ws, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Op, Ws...>*), Heaps... Hs)
		{
			constexpr auto ins	= MachineDispatch::instr(c, i);
			constexpr auto n	= ins[MI::dec];

			if constexpr (n >= d) // analogous to returning a machination.

				return NIK_MACHINE(0, MT::alias, c, i, Vs)(H0, Hs...);
			else
			{
				constexpr auto val = T_store_U<Op>::template result<Ws...>;

				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<val>, Hs...);
			}
		}
	};

/***********************************************************************************************************************/

// action:

	template<key_type... filler>
	struct machine<MN::call, MT::action, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto Op, auto... Ws, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Op, Ws...>*), Heaps... Hs)
		{
			constexpr auto ins	= MachineDispatch::instr(c, i);
			constexpr auto n	= ins[MI::dec];

			if constexpr (n >= d) // analogous to returning a machination.

				return NIK_MACHINE(0, MT::action, c, i, Vs)(H0, Hs...);
			else
			{
				constexpr auto val = Overload::template apply<Op, Ws...>;

				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<val>, Hs...);
			}
		}
	};

/***********************************************************************************************************************/

// compel:

	template<key_type... filler>
	struct machine<MN::call, MT::compel, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto Op, auto... Ws, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Op, Ws...>*), Heaps... Hs)
		{
			constexpr auto ins	= MachineDispatch::instr(c, i);
			constexpr auto n	= ins[MI::dec];

			if constexpr (n >= d) // analogous to returning a machination.

				return NIK_MACHINE(0, MT::compel, c, i, Vs)(H0, Hs...);
			else
			{
				constexpr auto nd  = d+1-n;
				constexpr auto val = T_store_U<Op>::template result<nd, Ws...>;

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::propel, c, i, Vs)(val.s1, val.s2, Hs...);
				else
					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<val>, Hs...);
			}
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

// value:

	template<key_type... filler>
	struct machine<MN::halt, MT::value, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto val, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<val>*), Heaps...)
		{
			return val;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// copy:

/***********************************************************************************************************************/

// register:

	template<key_type... filler>
	struct machine<MN::copy_r_pos, MT::insert_at_h0_back, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), Heaps... Hs)
		{
			constexpr auto ins	= MachineDispatch::instr(c, i);
			constexpr auto n	= ins[MI::pos];
			constexpr auto val	= NIK_BLOCK(BN::sifter, d, 3, n, Vs);

			if constexpr (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::block1, c, i, Vs)(val.s1, val.s2, H0, Hs...);
			else
				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, Hs...);
		}
	};

// constant:

	template<key_type... filler>
	struct machine<MN::copy_c_pos, MT::insert_at_h0_back, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto... Xs, typename... Args>
		nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<Xs...>*), Args... As)
		{
			constexpr auto ins	= MachineDispatch::instr(c, i);
			constexpr auto n	= ins[MI::pos];
			constexpr auto val	= NIK_BLOCK(BN::sifter, d, 3, n, Xs);

			if constexpr (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::block1, c, i, Vs)(val.s1, val.s2, H0, H1, As...);
			else
				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, H1, As...);
		}
	};

// argument:

	template<key_type... filler>
	struct machine<MN::copy_a_pos, MT::insert_at_h0_back, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, typename Heap1, typename... Args>
		nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), Heap1 H1, Args... As)
		{
			constexpr auto ins	= MachineDispatch::instr(c, i);
			constexpr auto n	= ins[MI::pos];
			constexpr auto val	= NIK_BLOCK(BN::sifter, d, 3, n, U_restore_T<Args>);

			if constexpr (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::block1, c, i, Vs)(val.s1, val.s2, H0, H1, As...);
			else
				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, H1, As...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cut:

/***********************************************************************************************************************/

// register:

	template<key_type... filler>
	struct machine<MN::cut_r_pos, MT::insert_at_hs_front, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			constexpr auto ins	= MachineDispatch::instr(c, i);
			constexpr auto n	= ins[MI::pos];
			constexpr auto val	= NIK_BLOCK(BN::filter, d, 3, n, Vs)(U_null_Vs);

			if constexpr (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::block2, c, i, Vs)(val.s1, val.s2, Hs...);
			else
				return NIK_MACHINE(d, MT::id, c, i, Vs)(val.v1, val.v2, Hs...);
		}
	};

// argument:

	template<key_type... filler>
	struct machine<MN::cut_a_pos, MT::insert_at_hs_front, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, typename Heap0, typename Heap1, typename... Args>
		nik_ces auto result(Heap0 H0, Heap1 H1, Args... As)
		{
			constexpr auto ins	= MachineDispatch::instr(c, i);
			constexpr auto n	= ins[MI::pos];
			constexpr auto val	= NIK_BLOCK(BN::filter, d, 3, n, U_restore_T<Args>)(U_null_Vs);

			if constexpr (is_machination<decltype(val)>)

				return NIK_MACHINE(d, MT::block2, c, i, Vs)(val.s1, val.s2, H0, H1, As...);
			else
				return NIK_MACHINE(d, MT::id, c, i, Vs)(val.v1, val.v2, H0, H1, As...);
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
		template
		<
			NIK_CONTR_PARAMS, auto... Vs,
			auto... Ls, auto... Rs, auto val,
			typename... Heaps
		>
		nik_ces auto result
		(
			nik_avp(auto_pack<Ls...>*),
			nik_avp(auto_pack<Rs...>*),
			nik_vp(H0)(auto_pack<val>*),
			Heaps... Hs
		)
		{
			return NIK_BEGIN_MACHINE(d, MT::id, c, i),

				Ls..., val, Rs...

			NIK_END_MACHINE(U_null_Vs, Hs...);
		}
	};

// argument:

	template<key_type... filler>
	struct machine<MN::paste_a_all, MT::id, filler...>
	{
		template
		<
			NIK_CONTR_PARAMS, auto... Vs,
			auto... Ls, auto... Rs, auto val,
			typename Heap1, typename... Args
		>
		nik_ces auto result
		(
			nik_avp(auto_pack<Ls...>*),
			nik_avp(auto_pack<Rs...>*),
			nik_vp(H0)(auto_pack<val>*),
			Heap1 H1, Args... As
		)
		{
			return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, H1, Ls..., val, Rs...);
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
		template<NIK_CONTR_PARAMS, auto... Vs, bool cond, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<cond>*), Heaps... Hs)
		{
			constexpr auto ins	= MachineDispatch::instr(c, i);
			constexpr auto ni	= cond ? ins[MI::pos] : i;

			return NIK_MACHINE(d, MT::id, c, ni, Vs)(U_null_Vs, Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	constexpr key_type _register	= 0;
	constexpr key_type _constant	= 1;
	constexpr key_type _argument	= 2;

	constexpr auto copy_name(ckey_type l)
	{
		if      (l == _register) return MN::copy_r_pos;
		else if (l == _constant) return MN::copy_c_pos;
		else                     return MN::copy_a_pos;
	}

	constexpr auto cut_name(ckey_type l)
	{
		if   (l == _register) return MN::cut_r_pos;
		else                  return MN::cut_a_pos;
	}

	constexpr auto paste_name(ckey_type l)
	{
		if   (l == _register) return MN::paste_r_all;
		else                  return MN::paste_a_all;
	}

	template<key_type...>
	constexpr instr_type value = instruction<MN::halt, MT::value>;

	template<key_type loc, index_type pos>
	constexpr instr_type copy = instruction<copy_name(loc), MT::insert_at_h0_back, pos>;

	template<key_type loc, index_type pos>
	constexpr instr_type cut = instruction<cut_name(loc), MT::insert_at_hs_front, pos>;

	template<key_type loc>
	constexpr instr_type paste = instruction<paste_name(loc), MT::id>;

	template<key_type...>
	constexpr instr_type cycle = instruction<MN::go_to, MT::id, _zero>;

	template<key_type label>
	constexpr instr_type branch = instruction<MN::go_to, MT::conditional, label>;

	template<depth_type dec = _one>
	constexpr instr_type apply = instruction<MN::call, MT::apply, dec>;

	template<depth_type dec = _two>
	constexpr instr_type alias = instruction<MN::call, MT::alias, dec>;

	template<depth_type dec = _one>
	constexpr instr_type action = instruction<MN::call, MT::action, dec>;

	template<depth_type dec = _two>
	constexpr instr_type compel = instruction<MN::call, MT::compel, dec>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// start:

	template<auto d, auto c, auto... Vs, typename... Heaps>
	constexpr auto start(Heaps... Hs)
	{
		constexpr auto m	= MT::id;
		constexpr auto i	= MachineDispatch::initial_index;

		constexpr auto s1	= U_pack_Vs<m, c, i, Vs...>;
		constexpr auto s2	= U_pack_Vs<U_null_Vs, U_restore_T<Heaps>...>;

		return NIK_MACHINE(d, MT::internal, c, i, Vs)(s1, s2);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

/***********************************************************************************************************************/
/***********************************************************************************************************************/

