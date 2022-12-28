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

// control:

/***********************************************************************************************************************/

// instructions:

	using instr_type  = gcindex_type*;
	using cinstr_type = instr_type const;

	template<auto... Vs>
	nik_ce instr_type instruction = array<gcindex_type, sizeof...(Vs), Vs...>;

/***********************************************************************************************************************/

// controllers:

	using contr_type  = cinstr_type*;
	using ccontr_type = contr_type const;

	template<auto... Vs>
	nik_ce contr_type controller = array<cinstr_type, array<gcindex_type, sizeof...(Vs)>, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machination:

		// Definition: A liner (trampoliner) is a nest-resulted struct that either returns
		// its value of interest, or a machination with the same structure as its input.
		// It is expected that all other nest-resulted structs are defined from such liners.

		// Both T_praxis and T_machine are implementations of such liners.

	template<typename U, typename P>
	struct machination
	{
		U u;
		P p;

		nik_ce machination(const U & _u, const P & _p) : u{_u}, p{_p} { }
	};

/***********************************************************************************************************************/

// is machination:

	template<typename T>
	nik_ce bool is_machination = false;

	template<typename U, typename P> nik_ce bool is_machination <       machination<U, P>   > = true;
	template<typename U, typename P> nik_ce bool is_machination < const machination<U, P>   > = true;
	template<typename U, typename P> nik_ce bool is_machination < const machination<U, P> & > = true;

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
			halt , jump ,
			pad , push , left , sift , fold ,
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
			pause   , debug , front , first , rest ,
			if_zero , dec   ,
			make    , apply ,
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

// pack:

	nik_ce auto _pack_null_			= U_pack_Vs <                    >;
	nik_ce auto _pack_first_		= U_pack_Vs < _first_            >;
	nik_ce auto _pack_second_		= U_pack_Vs < _second_           >;
	nik_ce auto _pack_second_first_		= U_pack_Vs < _second_ , _first_ >;

/***********************************************************************************************************************/

// padding:

	template<gindex_type n, auto V = U_null_Vs, auto b = H_id>
	nik_ce auto padding = eval<_pad_, b, V, n>;

	nik_ce gindex_type required_padding(gcindex_type size, gcindex_type _2_N)
	{
		gcindex_type remainder = size % _2_N;

		if (remainder == 0) return 0;
		else                return _2_N - remainder;
	}

	nik_ce gindex_type conditional_padding(gcindex_type pos, gcindex_type size, gcindex_type _2_N)
	{
		gcindex_type remainder = size % _2_N;

		if (remainder == 0) return 0;
		else
		{
			gcindex_type p_block = pos  / _2_N;
			gcindex_type s_block = size / _2_N;

			if (p_block != s_block) return 0;
			else                    return _2_N - remainder;
		}
	}

/***********************************************************************************************************************/

// start:

	struct T_praxis_start
	{
		nik_ces auto _2_N = PD::_2_N;
		nik_ces auto d    = PD::initial_depth;
		nik_ces auto i    = PD::initial_index;

		template<auto c, auto n, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs) { return NIK_PRAXIS(_2_N, d, c, i, n, Vs)(Hs...); }

	}; nik_ce auto U_praxis_start = U_custom_T<T_praxis_start>;

/***********************************************************************************************************************/

// restart:

	struct T_praxis_restart
	{
		template<NIK_PRAXIS_CONTROLS(d, c, i, n), auto _2_N, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs) { return NIK_PRAXIS(_2_N, d, c, i, n, Vs)(Hs...); }

	}; nik_ce auto U_praxis_restart = U_custom_T<T_praxis_restart>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

/***********************************************************************************************************************/

// pause:

	template<gindex_type _2_N>
	struct T_praxis<PN::halt, PT::pause, _2_N>
	{
		template<NIK_PRAXIS_CONTROLS(d, c, i, n), auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto p = U_pack_Vs<U_restore_T<Heaps>...>;

			return machination(U_praxis_restart, U_pack_Vs<p, c, i, n, _2_N, Vs...>);
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
			nik_ce auto cs = eval<_to_tuple_, d, c, i, n, _2_N>;
			nik_ce auto rs = eval<_to_tuple_, Vs...>;
			nik_ce auto hs = eval<_to_tuple_, U_restore_T<Heaps>...>;

			return eval<_to_tuple_, cs, rs, hs>;
		}
	};

/***********************************************************************************************************************/

// front:

	template<gindex_type _2_N>
	struct T_praxis<PN::halt, PT::front, _2_N>
	{
		template<NIK_PRAXIS_PARAMS(d, c, i, n, Vs), typename Heap0, typename Heap1, typename... Heaps>
		nik_ces auto result(Heap0 H0, Heap1 H1, Heaps... Hs)
		{
			return H1;
		}
	};

/***********************************************************************************************************************/

// first:

	template<gindex_type _2_N>
	struct T_praxis<PN::halt, PT::first, _2_N>
	{
		template<NIK_PRAXIS_CONTROLS(d, c, i, n), auto V, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			return V;
		}
	};

/***********************************************************************************************************************/

// rest:

	template<gindex_type _2_N>
	struct T_praxis<PN::halt, PT::rest, _2_N>
	{
		template
		<
			NIK_PRAXIS_CONTROLS(d, c, i, n), auto V, auto... Vs,
			template<auto...> typename B0, auto W, auto... Ws, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<W, Ws...>*), Heaps... Hs)
		{
			nik_ce auto ins	= PD::instr(c, i);
			nik_ce auto b   = eval<W, ins[PI::pos], Ws...>;

			return to_list_<b, Vs...>;
		}
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

// push:

/***********************************************************************************************************************/

// id:

	NIK_DEFINE_PRAXIS_PUSH_ID_2_N(6)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pad:

/***********************************************************************************************************************/

// make:

	template<gindex_type _2_N>
	struct T_praxis<PN::pad, PT::make, _2_N>
	{
		template
		<
			NIK_PRAXIS_PARAMS(d, c, i, n, Vs),
			typename Heap0, typename Heap1, typename Heap2, typename... Heaps
		>
		nik_ces auto result(Heap0 H0, Heap1 H1, Heap2 H2, Heaps... Hs)
		{
			nik_ce auto ins = PD::instr(c, i);
			nik_ce auto nH2 = padding<ins[PI::pos]>;

			return NIK_PRAXIS(_2_N, d, c, i, n, Vs)(H0, H1, nH2, Hs...);
		}
	};

/***********************************************************************************************************************/

// apply:

	template<gindex_type _2_N>
	struct T_praxis<PN::pad, PT::apply, _2_N>
	{
		template
		<
			NIK_PRAXIS_CONTROLS(d, c, i, n), auto... Vs,
			typename Heap0, typename Heap1, template<auto...> typename B2, auto... Ys,
			typename... Heaps
		>
		nik_ces auto result(Heap0 H0, Heap1 H1, nik_vp(H2)(B2<Ys...>*), Heaps... Hs)
		{
			nik_ce auto nH2 = U_store_T<B2<>>;

			return NIK_PRAXIS_BEGIN(_2_N, d, c, i, n),

				Vs..., Ys...

			NIK_PRAXIS_END(H0, H1, nH2, Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// left:

/***********************************************************************************************************************/

// make:

	template<gindex_type _2_N>
	struct T_praxis<PN::left, PT::make, _2_N>
	{
		nik_ces auto p0 = _pack_first_;
		nik_ces auto p1 = _pack_null_;

		template
		<
			NIK_PRAXIS_PARAMS(d, c, i, n, Vs),
			typename Heap0, typename Heap1, typename Heap2, typename... Heaps
		>
		nik_ces auto result(Heap0 H0, Heap1 H1, Heap2 H2, Heaps... Hs)
		{
			nik_ce auto ins = PD::instr(c, i);
			nik_ce auto k   = ins[PI::pos];
			nik_ce auto f0  = padding<k, p0>;
			nik_ce auto f1  = padding<_2_N-k, p1>;
			nik_ce auto nH2 = eval<_unite_, H_id, f0, f1>;

			return NIK_PRAXIS(_2_N, d, c, i, n, Vs)(H0, H1, nH2, Hs...);
		}
	};

/***********************************************************************************************************************/

// apply:

	template<gindex_type _2_N>
	struct T_praxis<PN::left, PT::apply, _2_N>
	{
		template
		<
			NIK_PRAXIS_PARAMS(d, c, i, n, Vs),
			typename Heap0, typename Heap1, template<auto...> typename B2, auto... Ys,
			typename... Heaps
		>
		nik_ces auto result(Heap0 H0, Heap1 H1, nik_vp(H2)(B2<Ys...>*), Heaps... Hs)
		{
			nik_ce auto nH2 = U_store_T<B2<>>;

			return NIK_PRAXIS_TEMPLATE(_2_N, d, c, i),

				Ys...

			NIK_PRAXIS_RESULT(d, c, i, n, Vs)(H0, H1, nH2, Hs...);
		}
	};

/***********************************************************************************************************************/

// id:

	NIK_DEFINE_PRAXIS_LEFT_ID_2_N(6)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sift:

/***********************************************************************************************************************/

// apply:

	NIK_DEFINE_PRAXIS_SIFT_APPLY_2_N(6)

/***********************************************************************************************************************/

// id:

	NIK_DEFINE_PRAXIS_SIFT_ID_2_N(6)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/

// id:

	NIK_DEFINE_PRAXIS_FOLD_ID_2_N(6)

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// controls:

/***********************************************************************************************************************/

// left:

	struct left_controls
	{
		nik_ces auto h0 = U_null_Vs;
		nik_ces auto h1 = U_null_Vs;
		nik_ces auto h2 = U_null_Vs;

		template<auto p, auto l, auto loop = _zero, auto done = _three>
		nik_ces auto contr = controller
		<
			instruction < PN::jump , PT::if_zero , done >,
			instruction < PN::push , PT::id             >,
			instruction < PN::jump , PT::dec     , loop >,
			instruction < PN::pad  , PT::make    , p    >,
			instruction < PN::pad  , PT::apply          >,
			instruction < PN::left , PT::make    , l    >,
			instruction < PN::left , PT::apply          >,
			instruction < PN::left , PT::id             >,
			instruction < PN::halt , PT::front          >
		>;

		gindex_type push;
		gindex_type pad;
		gindex_type pos;

		nik_ce left_controls(gcindex_type n, gcindex_type s, gcindex_type _2_N) : push{}, pad{}, pos{}
		{
			gcindex_type k = n / _2_N;
			gcindex_type j = n % _2_N;
			gcindex_type b = (k != 0 && j == 0);

			push = k - b;
			pad  = conditional_padding(n, s, _2_N);
			pos  = b ? _2_N : j;
		}
	};

/***********************************************************************************************************************/

// sift:

	struct sift_controls
	{
		nik_ces auto h0 = U_null_Vs;
		nik_ces auto h1 = U_null_Vs;
		nik_ces auto h2 = U_null_Vs;

		template<auto p, auto l = _zero, auto u = _one, auto loop = _two, auto done = _six>
		nik_ces auto contr = controller
		<
			instruction < PN::pad  , PT::make    , p    >,
			instruction < PN::pad  , PT::apply          >,
			instruction < PN::jump , PT::if_zero , done >,
			instruction < PN::sift , PT::apply   , l    >,
			instruction < PN::sift , PT::id             >,
			instruction < PN::jump , PT::dec     , loop >,
			instruction < PN::sift , PT::apply   , u    >,
			instruction < PN::sift , PT::id             >,
			instruction < PN::halt , PT::rest           >
		>;

		gindex_type push;
		gindex_type pad;
		gindex_type pos;

		nik_ce sift_controls(gcindex_type n, gcindex_type s, gcindex_type _2_N) : push{}, pad{}, pos{}
		{
			gcindex_type k = n / _2_N;
			gcindex_type j = n % _2_N;
			gcindex_type b = (k != 0 && j == 0);

			push = k - b;
			pad  = conditional_padding(n, s, _2_N);
			pos  = b ? _2_N : j;
		}
	};

/***********************************************************************************************************************/

// fold:

	struct fold_controls
	{
		nik_ces auto h0 = U_null_Vs;
		nik_ces auto h1 = U_null_Vs;
		nik_ces auto h2 = U_null_Vs;

		template<auto p, auto l, auto u = _zero, auto loop = _two, auto done = _five>
		nik_ces auto contr = controller
		<
			instruction < PN::pad  , PT::make    , p    >,
			instruction < PN::pad  , PT::apply          >,
			instruction < PN::jump , PT::if_zero , done >,
			instruction < PN::fold , PT::id      , l    >,
			instruction < PN::jump , PT::dec     , loop >,
			instruction < PN::fold , PT::id      , u    >,
			instruction < PN::halt , PT::first          >
		>;

		gindex_type push;
		gindex_type pad;
		gindex_type pos;

		nik_ce fold_controls(gcindex_type n, gcindex_type s, gcindex_type _2_N) : push{}, pad{}, pos{}
		{
			gcindex_type k = n / _2_N;
			gcindex_type j = n % _2_N;
			gcindex_type b = (k != 0 && j == 0);

			push = k - b;
			pad  = conditional_padding(n, s, _2_N);
			pos  = b ? _2_N : j;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

