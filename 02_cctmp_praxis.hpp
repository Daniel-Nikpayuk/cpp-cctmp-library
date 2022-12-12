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

// praxis:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

/***********************************************************************************************************************/

// instructions:

	using instr_type  = gcindex_type*;
	using cinstr_type = instr_type const;

	struct PraxisInstr
	{
		enum Position : gkey_type
		{
			size = 0,
			name , note , subject , pos = subject , jmp = subject ,
			dimension
		};

		nik_ces gindex_type length(cinstr_type i) { return i[size]; }
	};

	using PI = PraxisInstr;

	template<auto... Vs>
	nik_ce instr_type instruction = array<gindex_type, sizeof...(Vs), Vs...>;

/***********************************************************************************************************************/

// controllers:

	using contr_type  = cinstr_type*;
	using ccontr_type = contr_type const;

	struct PraxisContr
	{
		enum Position : gkey_type
		{
			size = 0,
			dimension
		};

		nik_ces gindex_type length(ccontr_type l) { return l[size][PI::size]; }
	};

	using PC = PraxisContr;

	template<auto... Vs>
	nik_ce contr_type controller = array<instr_type, array<gindex_type, sizeof...(Vs)>, Vs...>;

/***********************************************************************************************************************/

// dispatch:

	struct PraxisDisp
	{
		// defaults:

			nik_ces gindex_type initial_index = _zero;

		// accessors:

			nik_ces auto instr(ccontr_type c, gcindex_type i) { return c[i]; }

		// navigators:

			nik_ces   gkey_type next_name  (ccontr_type c, gcindex_type i) { return c[i+1][PI::name]; }
			nik_ces   gkey_type next_note  (ccontr_type c, gcindex_type i) { return c[i+1][PI::note]; }
			nik_ces gindex_type next_index (ccontr_type  , gcindex_type i) { return i + 1; }
	};

	using PD = PraxisDisp;

/***********************************************************************************************************************/

// padding:

	template<gindex_type n, auto V = U_null_Vs, auto b = H_id>
	nik_ce auto padding = eval<_pad_, b, V, n>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// grammar:

	template<gkey_type, gkey_type, gkey_type, auto...> struct T_praxis;

	template<auto Syn, auto Name, auto Note, auto... Vs>
	nik_ce auto U_praxis = U_store_T<T_praxis<Syn, Name, Note, Vs...>>;

	// argument:

		template<auto Name, auto Note, auto... Vs>
		using T_praxis_arg = T_praxis<Shape::argument, Name, Note, Vs...>;

		template<auto Name, auto Note, auto... Vs>
		nik_ce auto U_praxis_arg = U_praxis<Shape::argument, Name, Note, Vs...>;

	// parameter:

		template<auto Name, auto Note, auto... Vs>
		using T_praxis_param = T_praxis<Shape::parameter, Name, Note, Vs...>;

		template<auto Name, auto Note, auto... Vs>
		nik_ce auto U_praxis_param = U_praxis<Shape::parameter, Name, Note, Vs...>;

/***********************************************************************************************************************/

// names:

	struct PraxisName
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			pad , select  , mutate , drop   , rotate , reset ,
			at  , replace , erase  , insert ,
			dimension
		};
	};

	using PN = PraxisName;

/***********************************************************************************************************************/

// notes:

	struct PraxisNote
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			conditional , block , recurse ,
			_2_0 , _2_1 , _2_2 , _2_3 , _2_4 , _2_5 , _2_6 , _2_7 , _2_8 , _2_9 ,
			dimension
		};

		nik_ces gindex_type _2_N_from_note(gkey_type n) { return array_2_N[n - _2_0]; }
	};

	using PT = PraxisNote;

/***********************************************************************************************************************/

// start:

/*
	struct T_praxis_start
	{
		nik_ces auto i = PD::initial_index;

		template<typename S, auto l, auto c, auto... Vs, typename... Ts>
		nik_ces auto result(Ts... vs) { return NIK_PRAXIS(S, l, c, i, Vs)(vs...); }

	}; nik_ce auto U_praxis_start = U_custom_T<T_praxis_start>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pad:

/***********************************************************************************************************************/

// (unpack):

	template<auto... Cs, nik_vp(p)(T_pack_Vs<Cs...>*)>
	struct T_praxis<Shape::argument, PN::pad, PT::id, p>
	{
		template<auto cont, auto... Vs, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			using T_cont = T_store_U<cont>;

			return T_cont::template result<Vs...>(vs..., Cs...);
		}
	};

/***********************************************************************************************************************/

// id:

	template<gkey_type Note, auto... filler>
	struct T_praxis<Shape::argument, PN::pad, Note, filler...>
	{
		template<auto N>
		using T_pad = T_praxis_arg<PN::pad, PT::id, padding<N>>;

		nik_ces gindex_type id   (gindex_type _2_N, gindex_type Size) { return (Size % _2_N); }
		nik_ces gindex_type cond (gindex_type _2_N, gindex_type Size) { return (Size > _2_N) ? _2_N : Size; }
		nik_ces auto n = (Note == PT::conditional) ? cond : id;

		template<auto _2_N_Note, auto... Vs, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto _2_N = PT::_2_N_from_note(_2_N_Note);
			nik_ce auto Size = sizeof...(Ts);
			nik_ce auto N    = _2_N - n(_2_N, Size);

			return T_pad<N>::template result<Vs...>(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// unit:

/***********************************************************************************************************************/

// pre:

	template
	<
		gkey_type Name, gkey_type Note, auto F1,
		template<auto...> typename FB, auto... FF0s,
		template<auto...> typename BB, auto... BF0s
	>
	nik_ce auto praxis_arg_preunit(nik_vp(FP)(FB<FF0s...>*), nik_vp(BP)(BB<BF0s...>*))
		{ return U_praxis_arg<Name, Note, FF0s..., F1, BF0s...>; }

// using:

	template<gkey_type Name, gkey_type Note, auto n, auto F0, auto F1, auto m = PT::_2_N_from_note(Note)>
	using praxis_arg_unit = T_store_U
	<
		praxis_arg_preunit<Name, Note, F1>(padding<n, F0>, padding<m - (n + 1), F0>)
	>;

// pack:

	nik_ce auto _pack_null_  = U_pack_Vs <         >;
	nik_ce auto _pack_first_ = U_pack_Vs < _first_ >;

// 2^N:

	NIK_DEFINE_PRAXIS_ARGUMENT_UNIT(64)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// select:

/***********************************************************************************************************************/

// 2^N:

		// This definition is required to be separate from
		// the following *mutate* to allow for auto deduction.

	NIK_DEFINE_PRAXIS_ARGUMENT_SELECT(6)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// mutate:

/***********************************************************************************************************************/

// 2^N:

	NIK_DEFINE_PRAXIS_ARGUMENT_MUTATE(6)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// drop:

/***********************************************************************************************************************/

// 2^N:

	NIK_DEFINE_PRAXIS_ARGUMENT_DROP(6)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// rotate:

/***********************************************************************************************************************/

// 2^N:

	NIK_DEFINE_PRAXIS_ARGUMENT_ROTATE(6)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// at:

/***********************************************************************************************************************/

// 2^N:

	template<gkey_type Note, auto... filler>
	struct T_praxis<Shape::argument, PN::at, Note, filler...>
	{
		nik_ces auto _2_N = PT::_2_N_from_note(Note);

		template<gindex_type r>
		using T_at = T_praxis_arg<PN::select, Note, r, _pack_null_, _pack_first_>;

		template<auto r, auto... Vs, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return T_at<r>::template result<Vs...>(vs...);
		}
	};

/***********************************************************************************************************************/

// block:

	template<auto... filler>
	struct T_praxis<Shape::argument, PN::at, PT::block, filler...>
	{
		template<auto Note, auto... Vs, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto at = U_praxis_arg<PN::at, Note>;

			return T_praxis_arg<PN::pad, PT::id>::template result<Note, at, Vs...>(vs...);
		}
	};

	// syntactic sugar:

		template<auto Note, auto r, typename... Ts>
		nik_ce auto block_at(Ts... vs) // needs to do its own bounds check now that it pads.
		{
			return T_praxis_arg<PN::at, PT::block>::template result<Note, r, _first_>(vs...);
		}

/***********************************************************************************************************************/

// recurse:

	// at = drop ->  conditional pad -> pad -> select -> first
	//      drop -> (conditional pad -> pad -> select -> first)

	template<auto... filler>
	struct T_praxis<Shape::argument, PN::at, PT::recurse, filler...>
	{
		using T_pad                      = T_praxis_arg<PN::pad, PT::conditional>;
		nik_ces auto pad                 = U_praxis_arg<PN::pad, PT::conditional>;
		template<auto Note> using T_drop = T_praxis_arg<PN::drop, Note>;

		template<auto Note, auto n, auto... Vs, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto _2_N = PT::_2_N_from_note(Note);
			nik_ce auto q    = n / _2_N;
			nik_ce auto r    = n % _2_N;
			nik_ce auto at   = U_praxis_arg<PN::at, Note>;

			if constexpr (q)

				return T_drop<Note>::template result<q-1, pad, Note, at, r, Vs...>(vs...);
			else
				return T_pad::template result<Note, at, r, Vs...>(vs...);
		}
	};

	// syntactic sugar:

		template<auto Note, auto n, typename... Ts>
		nik_ce auto at(Ts... vs) // needs to do its own bounds check now that it pads.
		{
			return T_praxis_arg<PN::at, PT::recurse>::template result<Note, n, _first_>(vs...);
		}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// replace:

/***********************************************************************************************************************/

// block:

/***********************************************************************************************************************/

// recurse:

	// <mutate> = pad -> rotate -> mutate -> rotate -> reset -> cont

/***********************************************************************************************************************/
/***********************************************************************************************************************/

/*
	struct T_assembly_cont
	{
		template<auto s, auto l, auto c, auto i, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			using S = T_store_U<s>;

			return NIK_ASSEMBLY(S, l, c, i)(vs...);
		}
	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

