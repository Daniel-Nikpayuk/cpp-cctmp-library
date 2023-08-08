/************************************************************************************************************************
**
** Copyright 2022-2023 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// control:

/***********************************************************************************************************************/

// instructions:

	using instr_type  = gcindex_type*;
	using cinstr_type = instr_type const;

	template<auto... Vs>
	nik_ce instr_type instruction = array<gcindex_type, sizeof...(Vs), Vs...>;

	struct T_instr
	{
		template<auto... Vs>
		nik_ces auto result = instruction<Vs...>;

	}; nik_ce auto _instr_ = U_custom_T<T_instr>;

/***********************************************************************************************************************/

// controllers:

	using contr_type  = cinstr_type*;
	using ccontr_type = contr_type const;

	template<auto... Vs>
	nik_ce contr_type controller = array<cinstr_type, array<gcindex_type, sizeof...(Vs)>, Vs...>;

	struct T_contr
	{
		template<auto... Vs>
		nik_ces auto result = controller<Vs...>;

	}; nik_ce auto _contr_ = U_custom_T<T_contr>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machination:

		// Definition: A liner (trampoliner) is a nest-resulted struct that either returns
		// its value of interest, or a machination with the same structure as its input.
		// It is expected that all other nest-resulted structs are defined from such liners.

		// Both T_praxis and T_machine are implementations of such liners.

	template<typename Weights, typename Params, typename Heaps>
	struct machination
	{
		Weights ws;
		Params ps;
		Heaps hs;

		nik_ce machination(const Weights & _ws, const Params & _ps, const Heaps & _hs) :
			ws{_ws}, ps{_ps}, hs{_hs} { }
	};

	template<auto ws, auto ps, auto hs>
	nik_ce auto make_machination() { return machination(ws, ps, hs); }

/***********************************************************************************************************************/

// is machination:

	template<typename T>
	nik_ce bool is_machination = false;

	template<typename W, typename P, typename H>
	nik_ce bool is_machination<machination<W, P, H>(*)()> = true;

	template<typename W, typename P, typename H>
	nik_ce bool is_machination<machination<W, P, H>(*const)()> = true;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, gkey_type, gindex_type, auto...> struct T_praxis;

	template<auto Name, auto Note, auto _2_N, auto... Vs>
	nik_ce auto U_praxis = U_store_T<T_praxis<Name, Note, _2_N, Vs...>>;

/***********************************************************************************************************************/

// names:

	struct PraxisName
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			halt , jump , subset  ,
			decl , pad  , push    ,
			left , fold , segment , sift ,
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
			pause   , action , debug ,
			front   , first  , rest  ,
			if_zero , dec    , make  ,
			dimension
		};
	};

	using PT = PraxisNote;

/***********************************************************************************************************************/

// instructions:

	struct PraxisInstr
	{
		enum Position : gkey_type
		{
			size = 0,
			name , note , pos ,
			dimension
		};

		nik_ces gindex_type length (cinstr_type i) { return i[size]; }
	};

	using PI = PraxisInstr;

/***********************************************************************************************************************/

// controllers:

	struct PraxisContr
	{
		enum Position : gkey_type
		{
			size = 0,
			dimension
		};

		nik_ces gindex_type length (ccontr_type c) { return c[size][PI::size]; }
	};

	using PC = PraxisContr;

/***********************************************************************************************************************/

// dispatch:

	struct PraxisDispatch
	{
		// defaults:

			nik_ces gindex_type _2_N          = _2_6;
			nik_ces gdepth_type initial_depth = 500;
			nik_ces gindex_type initial_index = _zero;

		// accessors:

			nik_ces auto instr(ccontr_type c, gcindex_type i)
				{ return c[i]; }

		// navigators:

			nik_ces gkey_type next_name(gcdepth_type d, ccontr_type c, gcindex_type i)
			{
				if (d == 0) return PN::halt;
				else        return c[i+1][PI::name];
			}

			nik_ces gkey_type next_note(gcdepth_type d, ccontr_type c, gcindex_type i)
			{
				if (d == 0) return PT::pause;
				else        return c[i+1][PI::note];
			}

			nik_ces gdepth_type next_depth(gcdepth_type d)
				{ return d - bool{d != 0}; }

			nik_ces gindex_type next_index(gcdepth_type d, gcindex_type i)
				{ return i + bool{d != 0}; }
	};

	using PD = PraxisDispatch;

/***********************************************************************************************************************/

// padding:

	struct PraxisPadding
	{
		nik_ces void _na_() { }

		nik_ces auto _is_na_ = _alias_<_same_, _na_>;

		nik_ces gindex_type conditional(gcindex_type pos, gcindex_type _2_N, gcindex_type size)
		{
			gcindex_type remainder = size % _2_N;

			if (remainder == _zero) return _zero;
			else
			{
				gcindex_type p_block = pos  / _2_N;
				gcindex_type s_block = size / _2_N;

				if (p_block != s_block) return _zero;
				else                    return _2_N - remainder;
			}
		}

		nik_ces gindex_type required(gcindex_type _2_N, gcindex_type size)
		{
			if (size == _zero) return _2_N;
			else
			{
				gcindex_type remainder = size % _2_N;

				if (remainder == _zero) return _zero;
				else                    return _2_N - remainder;
			}
		}

		template<gindex_type n, auto V = _na_, auto b = H_id>
		nik_ces auto result = eval<_pad_, b, V, n>;
	};

	using PP = PraxisPadding;

/***********************************************************************************************************************/

// pack:

	nik_ce auto _pack_null_ = U_pack_Vs <       >;
	nik_ce auto _pack_car_  = U_pack_Vs < _car_ >;

	template<auto Ops>
	struct T_pack_filter
	{
		template<auto... Vs>
		nik_ces auto result = if_then_else_
		<
			eval<_and_wise_, Ops, Vs...>, _pack_car_, _pack_null_
		>;

	}; template<auto Ops>
		nik_ce auto _pack_filter_ = U_custom_T<T_pack_filter<Ops>>;

/***********************************************************************************************************************/

// start:

	struct T_praxis_start
	{
		nik_ces auto _2_N = PD::_2_N;
		nik_ces auto i    = PD::initial_index;

		template<auto d, auto c, auto n, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs) { return NIK_PRAXIS(_2_N, d, c, i, n, Vs)(Hs...); }

	}; nik_ce auto U_praxis_start = U_custom_T<T_praxis_start>;

/***********************************************************************************************************************/

// restart:

	template<auto... Ws>
	struct T_praxis_restart
	{
		template<NIK_PRAXIS_CONTROLS(d, c, i, n), auto _2_N, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			return NIK_PRAXIS_TEMPLATE(d, c, i),

				_2_N, Ws...

			NIK_PRAXIS_RESULT(d, c, i, n, Vs)(Hs...);
		}

	}; template<auto... Ws> // expected to be a store:
		nik_ce auto U_praxis_restart = U_store_T<T_praxis_restart<Ws...>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// dependencies:

/***********************************************************************************************************************/

// apply:

	template<auto Op, auto n = _one>
	struct T_praxis_apply
	{
		nik_ces auto _2_N = PD::_2_N;
		nik_ces auto i    = PD::initial_index;
		nik_ces auto c    = controller
		<
			instruction < PN::halt , PT::action >
		>;

		template<auto d, auto... Vs>
		nik_ces auto result = NIK_PRAXIS_BEGIN(_2_N, d, c, i, n),

			Op, Vs...

		NIK_PRAXIS_END();

	}; template<auto Op, auto n = _one>
		nik_ce auto _praxis_ = U_custom_T<T_praxis_apply<Op, n>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

/***********************************************************************************************************************/

// pause:

	template<gindex_type _2_N, auto... Ws>
	struct T_praxis<PN::halt, PT::pause, _2_N, Ws...>
	{
		template<NIK_PRAXIS_CONTROLS(d, c, i, n), auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto ps = U_pack_Vs<c, i, n, _2_N, Vs...>;
			nik_ce auto hs = U_pack_Vs<U_restore_T<Heaps>...>;

			return make_machination<U_praxis_restart<Ws...>, ps, hs>;
		}
	};

/***********************************************************************************************************************/

// action:

	template<gindex_type _2_N, auto... Ws>
	struct T_praxis<PN::halt, PT::action, _2_N, Ws...>
	{
		template<NIK_PRAXIS_CONTROLS(d, c, i, n), auto Op, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			if nik_ce (n <= d) return eval<Op, Vs...>;
			else
			{
				nik_ce auto ps = U_pack_Vs<c, i-1, n, _2_N, Op, Vs...>;
				nik_ce auto hs = U_pack_Vs<U_restore_T<Heaps>...>;

				return make_machination<U_praxis_restart<Ws...>, ps, hs>;
			}
		}
	};

/***********************************************************************************************************************/

// debug:

	template<gindex_type _2_N>
	struct T_praxis<PN::halt, PT::debug, _2_N>
	{
		template<NIK_PRAXIS_CONTROLS(d, c, i, n), auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto cs = list_<d, c, i, n, _2_N>;
			nik_ce auto rs = list_<Vs...>;
			nik_ce auto hs = list_<U_restore_T<Heaps>...>;

			return list_<cs, rs, hs>;
		}
	};

/***********************************************************************************************************************/

// front:

	template<gindex_type _2_N>
	struct T_praxis<PN::halt, PT::front, _2_N>
	{
		template<NIK_PRAXIS_PARAMS(d, c, i, n, Vs), typename Heap0, typename... Heaps>
		nik_ces auto result(Heap0 H0, Heaps... Hs)
			{ return H0; }
	};

/***********************************************************************************************************************/

// first:

	template<gindex_type _2_N>
	struct T_praxis<PN::halt, PT::first, _2_N>
	{
		template<NIK_PRAXIS_CONTROLS(d, c, i, n), auto V, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
			{ return V; }
	};

/***********************************************************************************************************************/

// rest:

	template<gindex_type _2_N>
	struct T_praxis<PN::halt, PT::rest, _2_N>
	{
		template
		<
			NIK_PRAXIS_CONTROLS(d, c, i, n), auto V, auto... Vs,
			template<auto...> typename B0, auto b, auto... Ws, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<b, Ws...>*), Heaps... Hs)
			{ return to_list_<b, Vs...>; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// jump:

/***********************************************************************************************************************/

	template<gindex_type _2_N>
	struct T_praxis<PN::jump, PT::if_zero, _2_N>
	{
		template<NIK_PRAXIS_PARAMS(d, c, i, n, Vs), typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto ins	= PD::instr(c, i);
			nik_ce auto ni	= (n == 0) ? ins[PI::pos] : i;

			return NIK_PRAXIS(_2_N, d, c, ni, n, Vs)(Hs...);
		}
	};

/***********************************************************************************************************************/

// dec:

	template<gindex_type _2_N>
	struct T_praxis<PN::jump, PT::dec, _2_N>
	{
		template<NIK_PRAXIS_PARAMS(d, c, i, n, Vs), typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto ins	= PD::instr(c, i);
			nik_ce auto ni	= ins[PI::pos];
			nik_ce auto nn	= n - 1;

			return NIK_PRAXIS(_2_N, d, c, ni, nn, Vs)(Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// subset:

/***********************************************************************************************************************/

// make:

	template<gindex_type _2_N>
	struct T_praxis<PN::subset, PT::make, _2_N>
	{
		nik_ces auto p0 = _pack_car_;
		nik_ces auto p1 = _pack_null_;

		template<NIK_PRAXIS_PARAMS(d, c, i, n, Vs), typename Heap0, typename... Heaps>
		nik_ces auto result(Heap0 H0, Heaps... Hs)
		{
			nik_ce auto ins = PD::instr(c, i);
			nik_ce auto k   = ins[PI::pos];
			nik_ce auto f0  = PP::result<k, p0>;
			nik_ce auto f1  = PP::result<_2_N-k, p1>;
			nik_ce auto Fs  = eval<_unite_, H_id, f0, f1>;

			return NIK_PRAXIS(_2_N, d, c, i, n, Vs)(H0, Fs, Hs...);
		}
	};

/***********************************************************************************************************************/

// action:

	template<gindex_type _2_N>
	struct T_praxis<PN::subset, PT::action, _2_N>
	{
		template
		<
			NIK_PRAXIS_PARAMS(d, c, i, n, Vs),
			typename Heap0, template<auto...> typename B, auto... fs,
			typename... Heaps
		>
		nik_ces auto result(Heap0 H0, nik_avp(B<fs...>*), Heaps... Hs)
		{
			return NIK_PRAXIS_TEMPLATE(d, c, i),

				_2_N, fs...

			NIK_PRAXIS_RESULT(d, c, i, n, Vs)(H0, Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// decl(type):

/***********************************************************************************************************************/

// id:

	template<gindex_type _2_N>
	struct T_praxis<PN::decl, PT::id, _2_N>
	{
		template<NIK_PRAXIS_CONTROLS(d, c, i, n), auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			return NIK_PRAXIS_BEGIN(_2_N, d, c, i, n),

				U_store_T<decltype(Vs)>...

			NIK_PRAXIS_END(Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pad:

/***********************************************************************************************************************/

// make:

	template<gindex_type _2_N>
	struct T_praxis<PN::pad, PT::make, _2_N>
	{
		template<NIK_PRAXIS_PARAMS(d, c, i, n, Vs), typename Heap0, typename... Heaps>
		nik_ces auto result(Heap0 H0, Heaps... Hs)
		{
			nik_ce auto ins = PD::instr(c, i);
			nik_ce auto Pad = PP::result<ins[PI::pos]>;

			return NIK_PRAXIS(_2_N, d, c, i, n, Vs)(H0, Pad, Hs...);
		}
	};

/***********************************************************************************************************************/

// action:

	template<gindex_type _2_N>
	struct T_praxis<PN::pad, PT::action, _2_N>
	{
		template
		<
			NIK_PRAXIS_CONTROLS(d, c, i, n), auto... Vs,
			typename Heap0, template<auto...> typename B, auto... Cs,
			typename... Heaps
		>
		nik_ces auto result(Heap0 H0, nik_avp(B<Cs...>*), Heaps... Hs)
		{
			return NIK_PRAXIS_BEGIN(_2_N, d, c, i, n),

				Vs..., Cs...

			NIK_PRAXIS_END(H0, Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// 2^N:

/***********************************************************************************************************************/

// push:

	// id:

		NIK_DEFINE_PRAXIS_PUSH_ID_2_N(6)

/***********************************************************************************************************************/

// left:

	// id:

		NIK_DEFINE_PRAXIS_LEFT_ID_2_N(6)

/***********************************************************************************************************************/

// fold:

	// id:

		NIK_DEFINE_PRAXIS_FOLD_ID_2_N(6)

/***********************************************************************************************************************/

// segment:

	// action:

		NIK_DEFINE_PRAXIS_SEGMENT_ACTION_2_N(6)

	// id:

		NIK_DEFINE_PRAXIS_SEGMENT_ID_2_N(6)

/***********************************************************************************************************************/

// sift:

	// action:

		NIK_DEFINE_PRAXIS_SIFT_ACTION_2_N(6)

	// id:

		NIK_DEFINE_PRAXIS_SIFT_ID_2_N(6)

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// controls:

	// Need to decide a safety policy for when (sizeof...(Vs) == 0).

	template<gkey_type, gindex_type> struct T_praxis_controls;

	template<gindex_type _2_N>
	struct T_praxis_controls<PN::id, _2_N>
	{
		contr_type c;
		gindex_type n;

		nik_ce T_praxis_controls(ccontr_type _c, gcindex_type _n) : c{_c}, n{_n} { }
	};

/***********************************************************************************************************************/

// left:

	template<gindex_type _2_N>
	struct T_praxis_controls<PN::left, _2_N>
	{
		template<auto Pad, auto Pos, auto Loop = _one, auto Done = _four>
		nik_ces auto contr = controller
		<
			instruction < PN::decl   , PT::id             >,
			instruction < PN::jump   , PT::if_zero , Done >,
			instruction < PN::push   , PT::id             >,
			instruction < PN::jump   , PT::dec     , Loop >,
			instruction < PN::pad    , PT::make    , Pad  >,
			instruction < PN::pad    , PT::action         >,
			instruction < PN::subset , PT::make    , Pos  >,
			instruction < PN::subset , PT::action         >,
			instruction < PN::left   , PT::id             >,
			instruction < PN::halt   , PT::front          >
		>;

		template<typename Base, auto M, auto S>
		nik_ces auto result()
		{
			nik_ce auto ctr = Base(M, S);
			nik_ce auto c   = ctr.template contr<ctr.pad, ctr.pos>;

			return T_praxis_controls<PN::id, _2_N>(c, ctr.n);
		}

		gindex_type pad;
		gindex_type pos;
		gindex_type n;

		nik_ce T_praxis_controls(gcindex_type m, gcindex_type s) : pad{}, pos{}, n{}
		{
			gcindex_type k = m / _2_N;
			gcindex_type j = m % _2_N;
			gcbool_type  b = (k != 0 && j == 0);

			pad = PP::conditional(m, _2_N, s);
			pos = b ? _2_N : j;
			n   = k - b;
		}
	};

/***********************************************************************************************************************/

// fold:

	template<gindex_type _2_N>
	struct T_praxis_controls<PN::fold, _2_N>
	{
		template<auto Pad, auto Pos = _zero, auto Num = _one, auto Loop = _two, auto Done = _five>
		nik_ces auto contr = controller
		<
			instruction < PN::pad  , PT::make    , Pad  >,
			instruction < PN::pad  , PT::action         >,
			instruction < PN::jump , PT::if_zero , Done >,
			instruction < PN::fold , PT::id      , Pos  >,
			instruction < PN::jump , PT::dec     , Loop >,
			instruction < PN::fold , PT::id      , Num  >,
			instruction < PN::halt , PT::first          >
		>;

		template<typename Base, auto M, auto S>
		nik_ces auto result()
		{
			nik_ce auto ctr = Base(M, S);
			nik_ce auto c   = ctr.template contr<ctr.pad>;

			return T_praxis_controls<PN::id, _2_N>(c, ctr.n);
		}

		gindex_type pad;
		gindex_type n;

		nik_ce T_praxis_controls(gcindex_type m, gcindex_type s) : pad{}, n{}
		{
			gcindex_type k = m / _2_N;
			gcindex_type j = m % _2_N;
			gcbool_type  b = (k != 0 && j == 0);

			pad = PP::required(_2_N, m); // (m == s-1)
			n   = k - b;
		}
	};

/***********************************************************************************************************************/

// segment:

	template<gindex_type _2_N>
	struct T_praxis_controls<PN::segment, _2_N>
	{
		template<auto Pos, auto Loop = _zero, auto Done = _three>
		nik_ces auto contr = controller
		<
			instruction < PN::jump    , PT::if_zero , Done >,
			instruction < PN::segment , PT::action         >,
			instruction < PN::jump    , PT::dec     , Loop >,
			instruction < PN::subset  , PT::make    , Pos  >,
			instruction < PN::subset  , PT::action         >,
			instruction < PN::segment , PT::id             >,
			instruction < PN::halt    , PT::rest           >
		>;

		template<typename Base, auto M, auto S>
		nik_ces auto result()
		{
			nik_ce auto ctr = Base(M, S);
			nik_ce auto c   = ctr.template contr<ctr.pos>;

			return T_praxis_controls<PN::id, _2_N>(c, ctr.n);
		}

		gindex_type pos;
		gindex_type n;

		nik_ce T_praxis_controls(gcindex_type m, gcindex_type s) : pos{}, n{}
		{
			gcindex_type k = m / _2_N;
			gcindex_type j = m % _2_N;
			gcbool_type  b = (k != 0 && j == 0);

			pos = b ? _2_N : j;
			n   = k - b;
		}
	};

/***********************************************************************************************************************/

// sift:

	template<gindex_type _2_N>
	struct T_praxis_controls<PN::sift, _2_N>
	{
		template<auto Pad, auto Pos = _zero, auto Num = _one, auto Loop = _two, auto Done = _six>
		nik_ces auto contr = controller
		<
			instruction < PN::pad  , PT::make    , Pad  >,
			instruction < PN::pad  , PT::action         >,
			instruction < PN::jump , PT::if_zero , Done >,
			instruction < PN::sift , PT::action  , Pos  >,
			instruction < PN::sift , PT::id             >,
			instruction < PN::jump , PT::dec     , Loop >,
			instruction < PN::sift , PT::action  , Num  >,
			instruction < PN::sift , PT::id             >,
			instruction < PN::halt , PT::rest           >
		>;

		template<typename Base, auto M, auto S>
		nik_ces auto result()
		{
			nik_ce auto ctr = Base(M, S);
			nik_ce auto c   = ctr.template contr<ctr.pad>;

			return T_praxis_controls<PN::id, _2_N>(c, ctr.n);
		}

		gindex_type pad;
		gindex_type n;

		nik_ce T_praxis_controls(gcindex_type m, gcindex_type s) : pad{}, n{}
		{
			gcindex_type k = m / _2_N;
			gcindex_type j = m % _2_N;
			gcbool_type  b = (k != 0 && j == 0);

			pad = PP::required(_2_N, m); // (m == s-1)
			n   = k - b;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

