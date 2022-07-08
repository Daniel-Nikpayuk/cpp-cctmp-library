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

// frontend:

namespace cctmp {

	/*
	 * (LOC, param) (VAR, [n, _register, 0]) (VAR, [p, _register, 1]) (;)
	 * (LOC, const) (VAR, [is_zero, _constant, 0]) (VAR, [multiply, _constant, 1]) (VAR, [decrement, _constant, 2]) (;)
	 * (LOC, arg) (;)
	 * (LABEL, start) (;)
	 * (IF) (LP) (VAR, is_zero) (VAR, n) (RP) (INSTR, goto) (LABEL, exit_case) (;)
	 * (VAR, p) (=) (VAR, multiply) (VAR, n) (VAR, p) (;)
	 * (VAR, n) (=) (VAR, decrement) (VAR, n) (;)
	 * (INSTR, goto) (LABEL, start) (;)
	 * (LABEL, exit_case) (;)
	 * (INSTR, return) (VAR, p) (;)
	*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pointer module:

/***********************************************************************************************************************/

	struct PointerModule
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

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array struct:

	template<typename Type, auto Size>
	struct Array
	{
		Type value[Size];
	};

/***********************************************************************************************************************/

// array module:

	struct ArrayModule
	{
		// type:

			template<typename Type, auto Size>
			nik_ces auto type(const Array<Type, Size> &) { return U_store_T<Type>; }

		// size:

			template<typename Type, auto Size>
			nik_ces auto size(const Array<Type, Size> &) { return Size; }

		// begin:

			template<typename Type, auto Size>
			nik_ces auto begin(Array<Type, Size> & arr) { return arr.value; }

		// end:

			template<typename Type, auto Size>
			nik_ces auto end(Array<Type, Size> & arr) { return arr.value + Size; }

		// apply:

			template
			<
				typename Type, auto Size,
				typename F, auto InSize, auto... Params,
				typename InType, typename... InTypes
			>
			nik_ces auto apply(InType in, InTypes... ins)
			{
				Array<Type, Size> arr{};

				F::template result<Params...>(begin(arr), in, in + InSize, ins...);

				return arr;
			}

		// sift:

			template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
			nik_ces auto sift(nik_vp(indices)(T_pack_Vs<Is...>*))
			{
				nik_ce auto Size	= Leng + 1;
				nik_ce auto arr	= apply<Type, Size, PointerModule::Sift, Leng, p>(Arr);
				nik_ce auto leng	= arr.value[Leng];

				if nik_ce (leng != sizeof...(Is)) return arr;
				else return array<Type, arr.value[Is]...>;
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// near linear apply:

	// -> V:

		template<typename Type, typename F, auto... As, auto... Ps, auto... Is>
		nik_ce auto V_apply(nik_avp(T_pack_Vs<Ps...>*), nik_avp(T_pack_Vs<Is...>*))
		{
			nik_ce auto Size	= sizeof...(Is);
			nik_ce auto arr		= ArrayModule::template apply<Type, Size, F, Ps...>(As...);

			return array<Type, arr.value[Is]...>;
		}

	// -> U:

		template<typename Type, typename F, auto... As, auto... Ps, auto... Is>
		nik_ce auto U_apply(nik_avp(T_pack_Vs<Ps...>*), nik_avp(T_pack_Vs<Is...>*))
		{
			nik_ce auto Size	= sizeof...(Is);
			nik_ce auto arr		= ArrayModule::apply<Type, Size, F, Ps...>(As...);

			return U_pack_Vs<arr.value[Is]...>;
		}

/***********************************************************************************************************************/

// sequence:

	// -> V:

		template<typename Type, auto f, auto Leng, typename Indices>
		nik_ce auto V_sequence(Indices indices)
			{ return V_apply<Type, PointerModule::Sequence, decltype(Leng){0}>(U_pack_Vs<Leng, f>, indices); }

	// -> U:

		template<typename Type, auto f, auto Leng, typename Indices>
		nik_ce auto U_sequence(Indices indices)
			{ return U_apply<Type, PointerModule::Sequence, decltype(Leng){0}>(U_pack_Vs<Leng, f>, indices); }

/***********************************************************************************************************************/

// map:

	// -> V:

		template<typename Type, auto f, auto Arr, auto Leng, typename Indices>
		nik_ce auto V_map(Indices indices)
			{ return V_apply<Type, PointerModule::Map, Arr>(U_pack_Vs<Leng, f>, indices); }

	// -> U:

		template<typename Type, auto f, auto Arr, auto Leng, typename Indices>
		nik_ce auto U_map(Indices indices)
			{ return U_apply<Type, PointerModule::Map, Arr>(U_pack_Vs<Leng, f>, indices); }

/***********************************************************************************************************************/

// fold:

	// -> V:

		template<typename Type, auto f, auto init, auto Arr, auto Leng>
		nik_ce auto V_fold()
			{ return V_apply<Type, PointerModule::Fold, Arr>(U_pack_Vs<Leng, f, init>, U_pack_Vs<0>); }

	// -> U:

		template<typename Type, auto f, auto init, auto Arr, auto Leng>
		nik_ce auto U_fold()
			{ return U_apply<Type, PointerModule::Fold, Arr>(U_pack_Vs<Leng, f, init>, U_pack_Vs<0>); }

/***********************************************************************************************************************/

// find:

	// -> V:

		template<typename Type, auto p, auto Arr, auto Leng>
		nik_ce auto V_find()
			{ return V_apply<Type, PointerModule::Find, Arr>(U_pack_Vs<Leng, Leng, p>, U_pack_Vs<0>); }

	// -> U:

		template<typename Type, auto p, auto Arr, auto Leng>
		nik_ce auto U_find()
			{ return U_apply<Type, PointerModule::Find, Arr>(U_pack_Vs<Leng, Leng, p>, U_pack_Vs<0>); }

/***********************************************************************************************************************/

// sift:

	// -> V:

		template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
		nik_ce auto V_sift(nik_vp(indices)(T_pack_Vs<Is...>*))
		{
			nik_ce auto Size	= Leng + 1;
			nik_ce auto arr		= ArrayModule::template apply<Type, Size, PointerModule::Sift, Leng, p>(Arr);
			nik_ce auto leng	= arr.value[Leng];

			if nik_ce (leng != sizeof...(Is)) return arr;
			else return array<Type, arr.value[Is]...>;
		}

/*
		template<typename Type, auto p, auto Arr, auto Leng, auto I0, auto... Is>
		nik_ce auto V_sift(nik_vp(indices)(T_pack_Vs<I0, Is...>*))
		{
			nik_ce auto Size	= sizeof...(Is) + 1;
			nik_ce auto arr		= apply<Type, Size, PointerModule::Sift, Leng, p>(Arr);

			return array<Type, arr.value[Is]...>;
		}
*/

	// -> U:

/*
		template<typename Type, auto p, auto Arr, auto Leng, auto I0, auto... Is>
		nik_ce auto U_sift(nik_vp(indices)(T_pack_Vs<I0, Is...>*))
		{
			nik_ce auto Size	= sizeof...(Is) + 1;
			nik_ce auto arr		= apply<Type, Size, PointerModule::Sift, Leng, p>(Arr);

			return U_pack_Vs<arr.value[Is]...>;
		}
*/

/***********************************************************************************************************************/

// subsequence:

/*
	// -> V:

		template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
		nik_ce auto V_subsequence(nik_vp(indices)(T_pack_Vs<Is...>*))
			{ return V_apply<Type, PointerModule::Sift, Arr>(U_pack_Vs<Leng, sizeof...(Is), p>, indices); }

	// -> U:

		template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
		nik_ce auto U_subsequence(nik_vp(indices)(T_pack_Vs<Is...>*))
			{ return U_apply<Type, PointerModule::Sift, Arr>(U_pack_Vs<Leng, sizeof...(Is), p>, indices); }
*/

/***********************************************************************************************************************/

// zip:

	// -> V:

		template<typename Type, auto f, auto Arr1, auto Leng1, auto Arr2, typename Indices>
		nik_ce auto V_zip(Indices indices)
			{ return V_apply<Type, PointerModule::Zip, Arr1, Arr2>(U_pack_Vs<Leng1, f>, indices); }

	// -> U:

		template<typename Type, auto f, auto Arr1, auto Leng1, auto Arr2, typename Indices>
		nik_ce auto U_zip(Indices indices)
			{ return U_apply<Type, PointerModule::Zip, Arr1, Arr2>(U_pack_Vs<Leng1, f>, indices); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

