/************************************************************************************************************************
**
** Copyright 2022-2024 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// machination:

		// Definition: A liner (trampoliner) is a nest-resulted struct that either returns
		// its value of interest, or a machination with the same structure as its input.
		// It is expected that all other nest-resulted structs are defined from such liners.

		// Both T_praxis and T_interpreter are implementations of such liners.

	template<typename Mach, typename Param, typename Heap>
	struct machination
	{
		Mach mach;
		Param param;
		Heap heap;

		nik_ce machination(const Mach & m, const Param & p, const Heap & h) :
			mach{m}, param{p}, heap{h} { }
	};

/***********************************************************************************************************************/

// is machination:

	template<typename T>
	nik_ce bool is_machination = false;

	template<typename M, typename P, typename H>
	nik_ce bool is_machination<machination<M, P, H>> = true;

	template<typename M, typename P, typename H>
	nik_ce bool is_machination<machination<M, P, H> const> = true;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, gkey_type, auto...> struct T_praxis;

	template<auto Name, auto Note, auto... Vs>
	nik_ce auto U_praxis = U_store_T<T_praxis<Name, Note, Vs...>>;

/***********************************************************************************************************************/

// names:

	struct PraxisName
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			halt, mach, pad, count, left, segment, fold, sift,
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
			pause, debug, first, heap, front,
			iter, select, copy, push, pull, proj, tail,
			dimension
		};
	};

	using PT = PraxisNote;

/***********************************************************************************************************************/

// instructions:

	struct PraxisInstr
	{
		enum Position : gkey_type { name = 0, note, pos, num, dimension };
		enum Policy   : gkey_type { back = 0, front };
	};

	using PI = PraxisInstr;

/***********************************************************************************************************************/

// dispatch:

	template<auto static_contr, auto _count = 0, auto _index = 0, auto _depth = 500, auto _size = _2_6>
	struct PraxisDispatch
	{
		nik_ces auto & contr = member_value_U<static_contr>;

		// defaults:

			nik_ces gindex_type initial_count = _count;
			nik_ces gindex_type initial_index = _index;
			nik_ces gdepth_type initial_depth = _depth;
			nik_ces gindex_type block_size    = _size;

		// accessors:

			nik_ces const auto & instr(gcindex_type i) { return contr[i]; }

		// navigators:

			nik_ces gkey_type next_name(gcdepth_type d, gcindex_type i)
			{
				if (d == 0) return PN::halt;
				else        return contr[i+1][PI::name];
			}

			nik_ces gkey_type next_note(gcdepth_type d, gcindex_type i)
			{
				if (d == 0) return PT::pause;
				else        return contr[i+1][PI::note];
			}

			nik_ces gdepth_type next_depth(gcdepth_type d)
				{ return d - bool{d != 0}; }

			nik_ces gindex_type next_index(gcdepth_type d, gcindex_type i)
				{ return i + bool{d != 0}; }
	};

	template<auto static_contr, auto _count = 0, auto _index = 0, auto _depth = 500, auto _size = _2_6>
	using PD = PraxisDispatch<static_contr, _count, _index, _depth, _size>;

/***********************************************************************************************************************/

// start:

	struct T_praxis_start
	{
		template<auto d, auto c, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto i = PD<c>::initial_index;
			nik_ce auto j = PD<c>::initial_count;

			return NIK_PRAXIS(d, c, i, j, Vs)(Hs...);
		}

	}; nik_ce auto U_praxis_start = U_custom_T<T_praxis_start>;

/***********************************************************************************************************************/

// jstart:

	struct T_praxis_jstart
	{
		template<auto d, auto c, auto j, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto i = PD<c>::initial_index;

			return NIK_PRAXIS(d, c, i, j, Vs)(Hs...);
		}

	}; nik_ce auto U_praxis_jstart = U_custom_T<T_praxis_jstart>;

/***********************************************************************************************************************/

// restart:

	struct T_praxis_restart
	{
		template<NIK_PRAXIS_CONTROLS(d, c, i, j), auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs) { return NIK_PRAXIS(d, c, i, j, Vs)(Hs...); }

	}; nik_ce auto U_praxis_restart = U_store_T<T_praxis_restart>; // expected to be a store.

/***********************************************************************************************************************/

// machinate:

	struct T_praxis_machinate
	{
		template
		<
			auto d, typename U_mach,
			template<auto...> typename BP, auto c, auto... ps,
			template<auto...> typename BH, auto... hs
		>
		nik_ces auto result(U_mach m, nik_vp(p)(BP<c, ps...>*), nik_vp(h)(BH<hs...>*))
		{
			if nik_ce (d == 0) return machination(m, p, h);

			nik_ce auto nd = PD<c>::next_depth(d);
			nik_ce auto v  = T_restore_T<U_mach>::template result<nd, c, ps...>(hs...);

			if nik_ce (not is_machination<decltype(v)>) return v;
			else return T_praxis_machinate::template result<nd>(v.mach, v.param, v.heap);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

/***********************************************************************************************************************/

// pause:

	template<auto... filler>
	struct T_praxis<PN::halt, PT::pause, filler...>
	{
		template<NIK_PRAXIS_CONTROLS(d, c, i, j), auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto param = U_pack_Vs<c, i, j, Vs...>;
			nik_ce auto heap  = U_pack_Vs<U_restore_T<Heaps>...>;

			return machination(U_praxis_restart, param, heap);
		}
	};

/***********************************************************************************************************************/

// debug:

	template<auto... filler>
	struct T_praxis<PN::halt, PT::debug, filler...>
	{
		template<NIK_PRAXIS_CONTROLS(d, c, i, j), auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto cs = list_<d, c, i, j>;
			nik_ce auto rs = list_<Vs...>;
			nik_ce auto hs = list_<U_restore_T<Heaps>...>;

			return list_<cs, rs, hs>;
		}
	};

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_praxis<PN::halt, PT::first, filler...>
	{
		template<NIK_PRAXIS_CONTROLS(d, c, i, j), auto V, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs) { return V; }
	};

/***********************************************************************************************************************/

// heap:

	template<auto... filler>
	struct T_praxis<PN::halt, PT::heap, filler...>
	{
		template
		<
			NIK_PRAXIS_CONTROLS(d, c, i, j), auto... Vs,
			template<auto...> typename B0, auto... Ws, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<Ws...>*), Heaps... Hs) { return U_store_T<B0<Vs...>>; }
	};

/***********************************************************************************************************************/

// front:

	template<auto... filler>
	struct T_praxis<PN::halt, PT::front, filler...>
	{
		template<NIK_PRAXIS_PARAMS(d, c, i, j, Vs), typename Heap0, typename... Heaps>
		nik_ces auto result(Heap0 H0, Heaps... Hs) { return H0; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// mach:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_praxis<PN::mach, PT::id, filler...>
	{
		template<NIK_PRAXIS_PARAMS(d, c, i, j, Vs), typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto v = NIK_PRAXIS(d, c, i, j, Vs)(U_restore_T<Heaps>...);

			if nik_ce (not is_machination<decltype(v)>) return v;
			else
			{
				nik_ce auto nd = PD<c>::next_depth(d);

				return T_praxis_machinate::template result<nd>(v.mach, v.param, v.heap);
			}
		}
	};

/***********************************************************************************************************************/

// iter(ate):

	template<auto... filler>
	struct T_praxis<PN::mach, PT::iter, filler...>
	{
		template<NIK_PRAXIS_CONTROLS(d, c, i, j), auto... Vs, typename Heap0, typename Heap1, typename... Heaps>
		nik_ces auto result(Heap0, Heap1, Heaps... Hs)
		{
			nik_ce auto & ins = PD<c>::instr(i);
			nik_ce auto n     = ins[PI::pos];
			nik_ce auto Op    = U_restore_T<Heap1>;

			if nik_ce (d < n)
			{
				nik_ce auto param = U_pack_Vs<c, i, j, Vs...>;
				nik_ce auto H0    = U_restore_T<Heap0>;
				nik_ce auto heap  = U_pack_Vs<H0, Op, U_restore_T<Heaps>...>;

				return machination(U_praxis_restart, param, heap);
			}
			else
			{
				nik_ce auto v = eval<Op, Vs...>;

				if nik_ce (not is_machination<decltype(v)>) return v;
				else
				{
					nik_ce auto nd = PD<c>::next_depth(d);

					return T_praxis_machinate::template result<nd>(v.mach, v.param, v.heap);
				}
			}
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pad:

/***********************************************************************************************************************/

// not applicable:

	struct T_not_applicable { };

	nik_ce auto _na_ = U_store_T<T_not_applicable>; // intended to be compatible with variadic args:

	template<auto V>
	nik_ce bool not_na = not eval<_same_, V, _na_>;

	template<auto U>
	nik_ce bool not_na_type = not eval<_same_, U, U_store_T<decltype(_na_)>>;

/***********************************************************************************************************************/

// select:

	template<auto... filler>
	struct T_praxis<PN::pad, PT::select, filler...>
	{
		template<NIK_PRAXIS_PARAMS(d, c, i, j, Vs), typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto & ins = PD<c>::instr(i);
			nik_ce auto n     = ins[PI::pos];
			nik_ce auto p     = pad_<_na_, n>;

			return NIK_PRAXIS(d, c, i, j, Vs)(p, Hs...);
		}
	};

/***********************************************************************************************************************/

// copy:

	template<auto... filler>
	struct T_praxis<PN::pad, PT::copy, filler...>
	{
		template<NIK_PRAXIS_CONTROLS(d, c, i, j), auto V, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			return NIK_PRAXIS_BEGIN(d, c, i, j),

				V, Vs..., V

			NIK_PRAXIS_END(Hs...);
		}
	};

/***********************************************************************************************************************/

// push:

	template<auto... filler>
	struct T_praxis<PN::pad, PT::push, filler...>
	{
		template
		<
			NIK_PRAXIS_CONTROLS(d, c, i, j), auto... Vs,
			template<auto...> typename B0, auto... Ws, typename... Heaps
		>
		nik_ces auto result(nik_avp(B0<Ws...>*), Heaps... Hs)
		{
			return NIK_PRAXIS_BEGIN(d, c, i, j),

				Vs..., Ws...

			NIK_PRAXIS_END(Hs...);
		}
	};

/***********************************************************************************************************************/

// pull:

	template<auto... filler>
	struct T_praxis<PN::pad, PT::pull, filler...>
	{
		template
		<
			NIK_PRAXIS_CONTROLS(d, c, i, j), auto... Vs,
			template<auto...> typename B0, auto... Ws, typename... Heaps
		>
		nik_ces auto result(nik_avp(B0<Ws...>*), Heaps... Hs)
		{
			nik_ce auto nH0 = U_store_T<B0<>>;

			return NIK_PRAXIS_BEGIN(d, c, i, j),

				Ws..., Vs...

			NIK_PRAXIS_END(nH0, Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// count:

/***********************************************************************************************************************/

// copy:

	template<auto... filler>
	struct T_praxis<PN::count, PT::copy, filler...>
	{
		template<NIK_PRAXIS_CONTROLS(d, c, i, j), auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			return NIK_PRAXIS_BEGIN(d, c, i, j),

				j, Vs...

			NIK_PRAXIS_END(Hs...);
		}
	};

/***********************************************************************************************************************/

// proj:

	template<auto... filler>
	struct T_praxis<PN::count, PT::proj, filler...>
	{
		template<NIK_PRAXIS_CONTROLS(d, c, i, j), auto V0, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			return NIK_PRAXIS_BEGIN(d, c, i, j),

				j, Vs...

			NIK_PRAXIS_END(Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// left:

/***********************************************************************************************************************/

// 2^N:

	// heap:

		NIK_DEFINE_PRAXIS_LEFT_HEAP_2_N(6)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// segment:

/***********************************************************************************************************************/

// 2^N:

	// push:

		NIK_DEFINE_PRAXIS_SEGMENT_PUSH_2_N(6)

	// pull:

		NIK_DEFINE_PRAXIS_SEGMENT_PULL_2_N(6)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/

// 2^N:

	// id:

		NIK_DEFINE_PRAXIS_FOLD_ID_2_N(6)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sift:

/***********************************************************************************************************************/

// sifters:

	nik_ce auto _drop_ = U_pack_Vs<      >;
	nik_ce auto _keep_ = U_pack_Vs< true >;

/***********************************************************************************************************************/

// splitters:

	// pair:

		template<gindex_type n0, gindex_type n1, typename S0, typename S1>
		nik_ce auto pair_splitter(S0, S1)
		{
			nik_ce auto p0 = pad_<U_restore_T<S0>, n0>;
			nik_ce auto p1 = pad_<U_restore_T<S1>, n1>;

			return unite_<p0, p1>;
		}

	// triple:

		template<gindex_type n0, auto n1, auto n2, typename S0, typename S1, typename S2>
		nik_ce auto triple_splitter(S0, S1, S2)
		{
			nik_ce auto p0 = pad_<U_restore_T<S0>, n0>;
			nik_ce auto p1 = pair_splitter<n1, n2>(U_restore_T<S1>, U_restore_T<S2>);

			return unite_<p0, p1>;
		}

/***********************************************************************************************************************/

// select:

	template<auto... filler>
	struct T_praxis<PN::sift, PT::select, filler...>
	{
		template<NIK_PRAXIS_PARAMS(d, c, i, j, Vs), typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto & ins = PD<c>::instr(i);
			nik_ce auto n0    = ins[PI::pos];
			nik_ce auto n1    = PD<c>::block_size - n0;
			nik_ce auto s0    = if_then_else_<ins[PI::num], _keep_, _drop_>;
			nik_ce auto s1    = if_then_else_<ins[PI::num], _drop_, _keep_>;
			nik_ce auto p     = pair_splitter<n0, n1>(s0, s1);

			return NIK_PRAXIS(d, c, i, j, Vs)(p, Hs...);
		}
	};

/***********************************************************************************************************************/

// tail:

	template<auto... filler> // can select be refactored as tail?
	struct T_praxis<PN::sift, PT::tail, filler...>
	{
		template<NIK_PRAXIS_PARAMS(d, c, i, j, Vs), typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto & ins = PD<c>::instr(i);
			nik_ce auto n0    = ins[PI::pos];
			nik_ce auto n1    = ins[PI::num] - n0;
			nik_ce auto n2    = PD<c>::block_size - n1 - n0;
			nik_ce auto p     = triple_splitter<n0, n1, n2>(_drop_, _keep_, _drop_);

			return NIK_PRAXIS(d, c, i, j, Vs)(p, Hs...);
		}
	};

/***********************************************************************************************************************/

// proj(ection):

	template<auto... filler>
	struct T_praxis<PN::sift, PT::proj, filler...>
	{
		template<NIK_PRAXIS_PARAMS(d, c, i, j, Vs), template<auto...> typename B, auto... ps, typename... Heaps>
		nik_ces auto result(nik_avp(B<ps...>*), Heaps... Hs)
			{ return NIK_PRAXIS(d, c, i, j, Vs)(ps..., Hs...); }
	};

/***********************************************************************************************************************/

// iter(ate):

	template<auto... filler>
	struct T_praxis<PN::sift, PT::iter, filler...>
	{
		template<NIK_PRAXIS_PARAMS(d, c, i, j, Vs), typename Heap0, typename Heap1, typename... Heaps>
		nik_ces auto result(Heap0 H0, Heap1 H1, Heaps... Hs)
			{ return NIK_PRAXIS(d, c, i, j, Vs)(H0, Hs...); }
	};

/***********************************************************************************************************************/

// 2^N:

	// id:

		NIK_DEFINE_PRAXIS_SIFT_ID_2_N(6)

	// heap:

		NIK_DEFINE_PRAXIS_SIFT_HEAP_2_N(6)

	// pull:

		NIK_DEFINE_PRAXIS_SIFT_PULL_2_N(6)

	// push:

		NIK_DEFINE_PRAXIS_SIFT_PUSH_2_N(6)

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

