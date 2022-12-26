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

	// select and mutate differ by the ability to auto deduce the function type.

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machination:

	// Definition: A liner (trampoliner) is a nest-resulted struct that either returns
	// its value of interest, or a machination with the same structure as its input.
	// It is expected that all other nest-resulted structs are defined from such liners.

	// Both T_block and T_machine are implementations of such liners.

/***********************************************************************************************************************/

// struct:

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

// grammar:

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
			recall , halt , jump ,
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
			make    , apply ,
			if_zero , dec   ,
			eval    , pause , debug ,
			dimension
		};
	};

	using PT = PraxisNote;

/***********************************************************************************************************************/

// instructions:

	struct PraxisInstr
	{
		using type	= gcindex_type*;
		using ctype	= type const;

		enum Position : gkey_type
		{
			size = 0,
			name , note , pos ,
			dimension
		};

		nik_ces gindex_type length (ctype i) { return i[size]; }
	};

	using PI		= PraxisInstr;
	using instr_type	= typename PI::type;
	using cinstr_type	= typename PI::ctype;

	template<auto... Vs>
	nik_ce instr_type instruction = array<gcindex_type, sizeof...(Vs), Vs...>;

/***********************************************************************************************************************/

// controllers:

	struct PraxisContr
	{
		using type	= cinstr_type*;
		using ctype	= type const;

		enum Position : gkey_type
		{
			size = 0,
			dimension
		};

		nik_ces gindex_type length (ctype c) { return c[size][PI::size]; }
	};

	using PC         	= PraxisContr;
	using contr_type	= typename PC::type;
	using ccontr_type	= typename PC::ctype;

	template<auto... Vs>
	nik_ce contr_type controller = array<cinstr_type, array<gcindex_type, sizeof...(Vs)>, Vs...>;

/***********************************************************************************************************************/

// dispatch:

	struct PraxisDispatch
	{
		// defaults:

			nik_ces gindex_type _2_N		= _2_6;
			nik_ces gdepth_type initial_depth	= 500;
			nik_ces gindex_type initial_index	= _zero;

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
		template<auto _2_N, NIK_PRAXIS_PARAMS(d, c, i, n, Vs), template<auto...> typename B, auto... Hs>
		nik_ces auto _result(nik_avp(B<Hs...>*)) { return NIK_PRAXIS(_2_N, d, c, i, n, Vs)(Hs...); }

		template<auto d, auto p, auto _2_N, auto c, auto i, auto n, auto...Vs>
		nik_ces auto result = _result<_2_N, d, c, i, n, Vs...>(p);

	}; nik_ce auto U_praxis_restart = U_custom_T<T_praxis_restart>;

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
			template<auto...> typename B0, auto W, auto... Ws,
			typename Heap1, typename Heap2, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<W, Ws...>*), Heap1 H1, Heap2 H2, Heaps... Hs)
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

// fold:

/***********************************************************************************************************************/

// id:

	NIK_DEFINE_PRAXIS_FOLD_ID_2_N(6)

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

// halt:

/***********************************************************************************************************************/

// eval:

	template<gindex_type _2_N>
	struct T_praxis<PN::halt, PT::eval, _2_N>
	{
		template
		<
			NIK_PRAXIS_PARAMS(d, c, i, n, Vs),
			template<auto...> typename B0, auto W, auto... Ws, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<W, Ws...>*), Heaps... Hs)
		{
			nik_ce auto ins	= PD::instr(c, i);
			nik_ce auto Op  = eval<W, ins[PI::pos], Ws...>;

			return eval<Op, Vs...>;
		}
	};

/***********************************************************************************************************************/

// pause:

	template<gindex_type _2_N>
	struct T_praxis<PN::halt, PT::pause, _2_N>
	{
		template<NIK_PRAXIS_CONTROLS(d, c, i, n), auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto p = U_pack_Vs<U_restore_T<Heaps>...>;

			return machination(U_praxis_restart, U_pack_Vs<p, _2_N, c, i, n, Vs...>);
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
			nik_ce auto cs = eval<_to_tuple_, _2_N, d, c, i, n>;
			nik_ce auto rs = eval<_to_tuple_, Vs...>;
			nik_ce auto hs = eval<_to_tuple_, U_restore_T<Heaps>...>;

			return eval<_to_tuple_, cs, rs, hs>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// algorithm:

	template<gkey_type, gkey_type, auto...> struct T_algorithm;

	template<auto Syn, auto Name, auto... Vs>
	nik_ce auto U_algorithm = U_store_T<T_algorithm<Syn, Name, Vs...>>;

/***********************************************************************************************************************/

// argument:

	template<auto Key, auto... Vs>       using T_algorithm_argument = T_algorithm<Shape::argument, Key, Vs...>;
	template<auto Key, auto... Vs> nik_ce auto U_algorithm_argument = U_algorithm<Shape::argument, Key, Vs...>;

// parameter:

	template<auto Key, auto... Vs>       using T_algorithm_parameter = T_algorithm<Shape::parameter, Key, Vs...>;
	template<auto Key, auto... Vs> nik_ce auto U_algorithm_parameter = U_algorithm<Shape::parameter, Key, Vs...>;

/***********************************************************************************************************************/

// names:

	struct AlgorithmName
	{
		enum : gkey_type
		{
			identity = 0, id = identity, // convenience for default params.
			left , at , replace , insert , erase ,
			fold ,
			sift ,
			dimension
		};
	};

	using AN = AlgorithmName;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parameter:

/***********************************************************************************************************************/

// left:

	template<auto _2_N>
	struct T_algorithm<Shape::parameter, AN::left, _2_N>
	{
		nik_ces auto H0 = U_pack_Vs<_at_, _list_<>>;
		nik_ces auto H1 = U_null_Vs;
		nik_ces auto H2 = U_null_Vs;

		template<auto p, auto l, auto h = _zero, auto loop = _zero, auto done = _three>
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
			instruction < PN::halt , PT::eval    , h    >
		>;

		template<auto n, auto s, auto... Vs>
		nik_ces auto _result()
		{
			nik_ce auto k = n / _2_N;
			nik_ce auto j = n % _2_N;
			nik_ce auto p = conditional_padding(n, s, _2_N);

			nik_ce auto b = (k != 0 && j == 0);
			nik_ce auto m = k - b;
			nik_ce auto l = b ? _2_N : j;
			nik_ce auto c = contr<p, l>;

			return T_praxis_start::template result<c, m, Vs...>(H0, H1, H2);
		}

		template<auto n, auto... Vs>
		nik_ces auto result = _result<n, sizeof...(Vs), Vs...>();

	}; template<auto _2_N = _2_6>
		nik_ce auto _par_left_ = U_custom_T<T_algorithm_parameter<AN::left, _2_N>>;

/***********************************************************************************************************************/

// fold:

/*
	template<auto _2_N>
	struct T_algorithm<Shape::parameter, AN::fold, _2_N>
	{
		template<auto op>
		nik_ces auto H0 = U_pack_Vs<_at_, op, _car_>;
		nik_ces auto H1 = U_null_Vs;
		nik_ces auto H2 = U_null_Vs;

		template<auto p, auto l, auto u = _zero, auto h = _one, auto loop = _two, auto done = _five>
		nik_ces auto contr = controller
		<
			instruction < PN::pad  , PT::make    , p    >,
			instruction < PN::pad  , PT::apply          >,
			instruction < PN::jump , PT::if_zero , done >,
			instruction < PN::fold , PT::id      , l    >,
			instruction < PN::jump , PT::dec     , loop >,
			instruction < PN::fold , PT::id      , u    >,
			instruction < PN::halt , PT::eval    , h    >
		>;

		template<auto n, auto op, auto s, auto... Vs>
		nik_ces auto _result()
		{
			nik_ce auto k = n / _2_N;
			nik_ce auto j = n % _2_N;
			nik_ce auto p = required_padding(s, _2_N);

			nik_ce auto b = (k != 0 && j == 0);
			nik_ce auto m = k - b;
			nik_ce auto l = b ? _2_N : j;
			nik_ce auto c = contr<p, l>;

			return T_praxis_start::template result<c, m, Vs...>(H0<op>, H1, H2);
		}

		template<auto n, auto op, auto... Vs>
		nik_ces auto result = _result<n, op, sizeof...(Vs), Vs...>();

	}; template<auto _2_N = _2_6>
		nik_ce auto _par_fold_ = U_custom_T<T_algorithm_parameter<AN::fold, _2_N>>;
*/

/***********************************************************************************************************************/

// sift:

/*
	template<auto _2_N>
	struct T_algorithm<Shape::parameter, AN::sift, _2_N>
	{
		template<auto op, auto sop>
		nik_ces auto H0 = U_pack_Vs<_at_, op, sop, _list_<>>;
		nik_ces auto H1 = U_null_Vs;
		nik_ces auto H2 = U_null_Vs;

		template<auto p, auto l = _zero, auto u = _one, auto h = _two, auto loop = _two, auto done = _six>
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
			instruction < PN::halt , PT::eval    , h    >
		>;

		template<auto n, auto op, auto sop, auto s, auto... Vs>
		nik_ces auto _result()
		{
			nik_ce auto k = n / _2_N;
			nik_ce auto j = n % _2_N;
			nik_ce auto p = required_padding(s, _2_N);

			nik_ce auto b = (k != 0 && j == 0);
			nik_ce auto m = k - b;
			nik_ce auto l = b ? _2_N : j;
			nik_ce auto c = contr<p, l>;

			return T_praxis_start::template result<c, m, Vs...>(H0<op, sop>, H1, H2);
		}

		template<auto n, auto op, auto... Vs>
		nik_ces auto result = _result<n, op, sop, sizeof...(Vs), Vs...>();

	}; template<auto _2_N = _2_6>
		nik_ce auto _par_sift_ = U_custom_T<T_algorithm_parameter<AN::sift, _2_N>>;
*/

/***********************************************************************************************************************/

// unit (generic):

	template<gkey_type Name, auto... Ws>
	struct T_algorithm<Shape::parameter, Name, Ws...>
	{
		template<auto n, auto... Vs>
		nik_ces auto result = T_algorithm_parameter
		<
			Name,
			eval<_par_left_<>, n, U_store_T<decltype(Vs)>...>,
			Ws...

		>::template result<Vs...>;

	}; template<auto Name, auto... Vs>
		nik_ce auto _par_unit_ = U_custom_T<T_algorithm_parameter<Name, Vs...>>;

/***********************************************************************************************************************/

// at:

	template<template<auto...> typename B, auto... LUs, nik_vp(p)(B<LUs...>*)>
	struct T_algorithm<Shape::parameter, AN::at, p>
	{
		template<T_store_U<LUs>... LVs, auto VN, auto... Vs>
		nik_ces auto result = VN;

	}; nik_ce auto _par_at_ = _par_unit_<AN::at>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// argument:

/***********************************************************************************************************************/

// unit (generic):

	template<gkey_type Name, auto... Vs>
	struct T_algorithm<Shape::argument, Name, Vs...>
	{
		template<auto n, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto p = eval<_par_left_<>, n, U_store_T<Ts>...>;

			return T_algorithm_argument<Name, p, Vs...>::result(vs...);
		}

	}; template<auto Name, auto... Vs>
		nik_ce auto _arg_unit_ = U_custom_T<T_algorithm_argument<Name, Vs...>>;

/***********************************************************************************************************************/

// at:

	template<template<auto...> typename B, auto... LUs, nik_vp(p)(B<LUs...>*)>
	struct T_algorithm<Shape::argument, AN::at, p>
	{
		template<typename TN, typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, TN vn, Ts... vs) { return vn; }

	}; nik_ce auto _arg_at_ = _arg_unit_<AN::at>;

	// syntactic sugar:

		template<auto n, typename... Ts>
		nik_ce auto arg_at(Ts... vs) { return T_algorithm_argument<AN::at>::template result<n>(vs...); }

/***********************************************************************************************************************/

// replace:

	template<template<auto...> typename B, auto... LUs, nik_vp(p)(B<LUs...>*), auto c>
	struct T_algorithm<Shape::argument, AN::replace, p, c>
	{
		using C = T_store_U<c>;

		template<typename T, typename TN, typename... Ts>
		nik_ces auto result(T v, T_store_U<LUs>... lvs, TN vn, Ts... vs) { return C::result(lvs..., v, vs...); }

	}; template<auto cont>
		nik_ce auto _arg_replace_ = _arg_unit_<AN::replace, cont>;

	// syntactic sugar:

		template<auto cont, auto n, typename... Ts>
		nik_ce auto arg_replace(Ts... vs)
		{
			return T_algorithm_argument<AN::replace, cont>::template result<n>(vs...);
		}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

