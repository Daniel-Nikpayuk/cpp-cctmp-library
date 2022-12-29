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

// machine:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, gkey_type, gindex_type, auto...> struct T_machine;

	template<auto Name, auto Note, auto _2_N, auto... Vs>
	nik_ce auto U_machine = U_store_T<T_machine<Name, Note, _2_N, Vs...>>;

	nik_ce auto H_machine = U_store_B<T_machine>;

/***********************************************************************************************************************/

// names:

	struct MachineName
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			halt   , restart , jump   ,
			lookup , split   , params , action , compel ,
			dimension
		};
	};

	using MN = MachineName;

/***********************************************************************************************************************/

// notes:

	struct MachineNote
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.

			pause , debug  , eval  ,
			test  , value  , regs  ,
			go_to , branch , call  ,
			front , back   ,
			copy  , mutate , paste , cut ,
			dimension
		};
	};

	using MT = MachineNote;

/***********************************************************************************************************************/

// modes:

	struct MachineMode
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.

			unit , all ,
			dimension
		};
	};

	using MM = MachineMode;

/***********************************************************************************************************************/

// instructions:

	struct MachineInstr
	{
		enum Position : gkey_type
		{
			size = 0,
			name , note      ,
			pos  , dec = pos , mov = pos ,
			ctn  , syn       , key       , act
		};

		nik_ces gindex_type length (cinstr_type i)  { return i[size]; }
	};

	using MI = MachineInstr;

/***********************************************************************************************************************/

// controllers:

	struct MachineContr
	{
		enum Position : gkey_type
		{
			size = 0
		};

		nik_ces gindex_type length (ccontr_type l) { return l[size][MI::size]; }
	};

	using MC = MachineContr;

/***********************************************************************************************************************/

// dispatch:

	struct MachineDispatch
	{
		// defaults:

			nik_ces gindex_type _2_N          = _2_6;
			nik_ces gdepth_type initial_depth = 500;
			nik_ces gkey_type   initial_mode  = MM::id;
			nik_ces gindex_type initial_index = _zero;

		// accessors:

			nik_ces auto instr(ccontr_type c, gcindex_type i)
				{ return c[i]; }

		// navigators:

			nik_ces gkey_type next_name(gcdepth_type d, gckey_type m, ccontr_type c, gcindex_type i)
			{
				if      (d == 0)      return MN::halt;
				else if (m == MM::id) return c[i+1][MI::name];
				else                  return MN::restart;
			}

			nik_ces gkey_type next_note(gcdepth_type d, gckey_type m, ccontr_type c, gcindex_type i)
			{
				if      (d == 0)        return MT::pause;
				else if (m == MM::id)   return c[i+1][MI::note];
				else if (m == MM::unit) return MT::value;
				else                    return MT::regs;
			}

			nik_ces gdepth_type next_depth(gcdepth_type d)
				{ return d - bool{d != 0}; }

			nik_ces gindex_type next_index(gcdepth_type d, gckey_type m, gcindex_type i)
				{ return i + bool{d != 0 && m == MM::id}; }
	};

	using MD = MachineDispatch;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// start:

	struct T_machine_start
	{
		nik_ces auto _2_N = MD::_2_N;
		nik_ces auto m    = MD::initial_mode;
		nik_ces auto i    = MD::initial_index;

		template<auto d, auto c, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs) { return NIK_MACHINE(_2_N, d, m, c, i, Vs)(Hs...); }

	}; nik_ce auto U_machine_start = U_custom_T<T_machine_start>;

/***********************************************************************************************************************/

// restart:

	struct T_machine_restart
	{
		template<NIK_MACHINE_CONTROLS(d, m, c, i), auto _2_N, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs) { return NIK_MACHINE(_2_N, d, m, c, i, Vs)(Hs...); }

	}; nik_ce auto U_machine_restart = U_store_T<T_machine_restart>;

/***********************************************************************************************************************/

// revalue (try restart):

	struct T_machine_revalue
	{
		nik_ces auto d  = MD::initial_depth;
		nik_ces auto H0 = U_pack_Vs<_at_, _car_>;

		template<auto h = _zero>
		nik_ces auto contr = controller
		<
			instruction < MN::restart , MT::test     >,
			instruction < MN::halt    , MT::eval , h >
		>;

		template<auto V>
		nik_ces auto result = T_machine_start::template result<d, contr<>, V>(H0);
	};

/***********************************************************************************************************************/

// at:

	struct T_machine_at
	{
		nik_ces auto d  = MD::initial_depth;
		nik_ces auto H0 = U_pack_Vs<_at_, _car_>;

		template<auto n, auto h = _zero>
		nik_ces auto contr = controller
		<
			instruction < MN::split  , MT::call , n >,
			instruction < MN::split  , MT::id       >,
			instruction < MN::params , MT::copy     >,
			instruction < MN::halt   , MT::eval , h >
		>;

		template<auto n, auto... Vs>
		nik_ces auto result = T_machine_start::template result<d, contr<n>, Vs...>(H0);

	}; nik_ce auto _par_at_ = U_custom_T<T_machine_at>;

/***********************************************************************************************************************/

// apply:

	struct T_machine_apply
	{
		nik_ces auto d = MD::initial_depth;

		template<auto Inds, auto Op>
		nik_ces auto H0 = U_pack_Vs<_at_, Inds, Op, _car_>;

		template<auto i = _zero, auto o = _one, auto h = _two>
		nik_ces auto contr = controller
		<
			instruction < MN::lookup , MT::id   , i >,
			instruction < MN::params , MT::call     >,
			instruction < MN::compel , MT::call , o >,
			instruction < MN::halt   , MT::eval , h >
		>;

		template<auto Inds, auto Op, auto... Vs>
		nik_ces auto result = T_machine_start::template result<d, contr<>, Vs...>(H0<Inds, Op>);
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

/***********************************************************************************************************************/

// pause:

	template<gindex_type _2_N>
	struct T_machine<MN::halt, MT::pause, _2_N>
	{
		template<NIK_MACHINE_CONTROLS(d, m, c, i), auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto ps = U_pack_Vs<m, c, i, _2_N, Vs...>;
			nik_ce auto hs = U_pack_Vs<U_restore_T<Heaps>...>;

			return machination(U_machine_restart, ps, hs);
		}
	};

/***********************************************************************************************************************/

// debug:

	template<gindex_type _2_N>
	struct T_machine<MN::halt, MT::debug, _2_N>
	{
		template<NIK_MACHINE_PARAMS(d, m, c, i, Vs), typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto cs = eval<_to_tuple_, d, m, c, i, _2_N>;
			nik_ce auto rs = eval<_to_tuple_, Vs...>;
			nik_ce auto hs = eval<_to_tuple_, U_restore_T<Heaps>...>;

			return eval<_to_tuple_, cs, rs, hs>;
		}
	};

/***********************************************************************************************************************/

// eval:

	template<gindex_type _2_N>
	struct T_machine<MN::halt, MT::eval, _2_N>
	{
		template
		<
			NIK_MACHINE_CONTROLS(d, m, c, i), auto... Vs,
			template<auto...> typename B0, auto W, auto... Ws, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<W, Ws...>*), Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto Op  = eval<W, ins[MI::pos], Ws...>;

			return eval<Op, Vs...>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// restart:

/***********************************************************************************************************************/

// test:

		// Should assume (m == MM::id):

	template<gindex_type _2_N>
	struct T_machine<MN::restart, MT::test, _2_N>
	{
		template<NIK_MACHINE_CONTROLS(d, m, c, i), auto V, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			if nik_ce (is_machination<decltype(V)>)

				return NIK_MACHINE(_2_N, d, MM::unit, c, i, Vs)(V.op, V.ps, V.hs, Hs...);
			else
				return NIK_MACHINE_BEGIN(_2_N, d, m, c, i),

					V, Vs...

				NIK_MACHINE_END(Hs...);
		}
	};

/***********************************************************************************************************************/

// value:

		// Should assume (m == MM::unit):

	template<gindex_type _2_N>
	struct T_machine<MN::restart, MT::value, _2_N>
	{
		template
		<
			NIK_MACHINE_PARAMS(d, m, c, i, Vs),
			typename Op,
			template<auto...> typename BP, auto... ps,
			template<auto...> typename BH, auto... hs,
			typename... Heaps
		>
		nik_ces auto result(Op op, nik_avp(BP<ps...>*), nik_avp(BH<hs...>*), Heaps... Hs)
		{
			nik_ce auto sd = MD::next_depth(d);
			nik_ce auto V  = T_restore_T<Op>::template result<sd, ps...>(hs...);

			if nik_ce (is_machination<decltype(V)>)

				return NIK_MACHINE(_2_N, d, m, c, i, Vs)(V.op, V.ps, V.hs, Hs...);
			else
				return NIK_MACHINE_BEGIN(_2_N, d, MM::id, c, i),

					V, Vs...

				NIK_MACHINE_END(Hs...);
		}
	};

/***********************************************************************************************************************/

// regs:

		// Should assume (m == MM::all):

	template<gindex_type _2_N>
	struct T_machine<MN::restart, MT::regs, _2_N>
	{
		nik_ces auto sc  = T_machine_revalue::template contr<>;
		nik_ces auto sH0 = T_machine_revalue::H0;

		template<NIK_MACHINE_CONTROLS(d, m, c, i), auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto has_machination = eval<_or_, is_machination<decltype(Vs)>...>;

			if nik_ce (has_machination)
			{
				nik_ce auto sd = MD::next_depth(d);

				return NIK_MACHINE_BEGIN(_2_N, d, m, c, i),

				       T_machine_start::template result<sd, sc, Vs>(sH0)...

				NIK_MACHINE_END(Hs...);
			}
			else return NIK_MACHINE(_2_N, d, MM::id, c, i, Vs)(Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// jump:

/***********************************************************************************************************************/

// go to:

	template<gindex_type _2_N>
	struct T_machine<MN::jump, MT::go_to, _2_N>
	{
		template<NIK_MACHINE_PARAMS(d, m, c, i, Vs), typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto ni	= ins[MI::pos];

			return NIK_MACHINE(_2_N, d, m, c, ni, Vs)(Hs...);
		}
	};

/***********************************************************************************************************************/

// branch:

	template<gindex_type _2_N>
	struct T_machine<MN::jump, MT::branch, _2_N>
	{
		template
		<
			NIK_MACHINE_PARAMS(d, m, c, i, Vs),
			typename Heap0, template<auto...> typename B1, auto X0, auto... Xs, typename... Heaps
		>
		nik_ces auto result(Heap0 H0, nik_vp(H1)(B1<X0, Xs...>*), Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto ni	= X0 ? ins[MI::pos] : i;
			nik_ce auto nH1 = U_store_T<B1<Xs...>>;

			return NIK_MACHINE(_2_N, d, m, c, ni, Vs)(H0, nH1, Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lookup:

/***********************************************************************************************************************/

// id:

	template<gindex_type _2_N>
	struct T_machine<MN::lookup, MT::id, _2_N>
	{
		template
		<
			NIK_MACHINE_PARAMS(d, m, c, i, Vs),
			template<auto...> typename B0, auto W, auto... Ws, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<W, Ws...>*), Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto nH  = eval<W, ins[MI::pos], Ws...>;

			return NIK_MACHINE(_2_N, d, m, c, i, Vs)(nH, H0, Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// split:

/***********************************************************************************************************************/

// call:

		// Should assume (m == MM::id):

	template<gindex_type _2_N>
	struct T_machine<MN::split, MT::call, _2_N>
	{
		template<NIK_MACHINE_PARAMS(d, m, c, i, Vs), typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto sd  = MD::next_depth(d);
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto lc	= left_controls(ins[MI::pos], sizeof...(Vs), _2_N);
			nik_ce auto sc  = left_controls::template contr<lc.pad, lc.pos>;
			nik_ce auto V   = T_praxis_start::template result
					<
						sd, sc, lc.push, U_store_T<decltype(Vs)>...

					>(lc.h0, lc.h1, lc.h2);

			if nik_ce (is_machination<decltype(V)>)

				return NIK_MACHINE(_2_N, d, MM::unit, c, i, Vs)(V.op, V.ps, V.hs, Hs...);
			else
				return NIK_MACHINE_BEGIN(_2_N, d, m, c, i),

					V, Vs...

				NIK_MACHINE_END(Hs...);
		}
	};

/***********************************************************************************************************************/

// id:

		// Should assume (m == MM::id):

	template<gindex_type _2_N>
	struct T_machine<MN::split, MT::id, _2_N>
	{
		template<NIK_MACHINE_CONTROLS(d, m, c, i), auto V, auto...Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto hs = U_pack_Vs<U_restore_T<Heaps>...>;

			return NIK_MACHINE_L(_2_N, d, m, c, i),

				V, hs

			NIK_MACHINE_M(d, m, c, i),

				Vs...

			NIK_MACHINE_R;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// params:

/***********************************************************************************************************************/

// front:

	template
	<
		gindex_type _2_N,
		template<auto...> typename LB, auto... LUs, nik_vp(ps)(LB<LUs...>*),
		template<auto...> typename HB, auto...  Hs, nik_vp(hs)(HB< Hs...>*)
	>
	struct T_machine<MN::params, MT::front, _2_N, ps, hs>
	{
		template
		<
			NIK_MACHINE_CONTROLS(d, m, c, i),
			T_store_U<LUs>... LVs, auto... Vs
		>
		nik_ces auto result = NIK_MACHINE_BEGIN(_2_N, d, m, c, i),

			LVs...

		NIK_MACHINE_END(Hs...);
	};

/***********************************************************************************************************************/

// back:

	template
	<
		gindex_type _2_N,
		template<auto...> typename LB, auto... LUs, nik_vp(ps)(LB<LUs...>*),
		template<auto...> typename HB, auto...  Hs, nik_vp(hs)(HB< Hs...>*)
	>
	struct T_machine<MN::params, MT::back, _2_N, ps, hs>
	{
		template
		<
			NIK_MACHINE_CONTROLS(d, m, c, i),
			T_store_U<LUs>... LVs, auto... Vs
		>
		nik_ces auto result = NIK_MACHINE_BEGIN(_2_N, d, m, c, i),

			Vs...

		NIK_MACHINE_END(Hs...);
	};

/***********************************************************************************************************************/

// copy:

	template
	<
		gindex_type _2_N,
		template<auto...> typename LB, auto... LUs, nik_vp(ps)(LB<LUs...>*),
		template<auto...> typename HB, auto...  Hs, nik_vp(hs)(HB< Hs...>*)
	>
	struct T_machine<MN::params, MT::copy, _2_N, ps, hs>
	{
		template
		<
			NIK_MACHINE_CONTROLS(d, m, c, i),
			T_store_U<LUs>... LVs, auto VN, auto... Vs
		>
		nik_ces auto result = NIK_MACHINE_BEGIN(_2_N, d, m, c, i),

			VN, LVs..., VN, Vs...

		NIK_MACHINE_END(Hs...);
	};

/***********************************************************************************************************************/

// mutate:

	template
	<
		gindex_type _2_N,
		template<auto...> typename LB, auto U, auto... LUs, nik_vp(ps)(LB<U, LUs...>*),
		template<auto...> typename HB,         auto...  Hs, nik_vp(hs)(HB<    Hs...>*)
	>
	struct T_machine<MN::params, MT::mutate, _2_N, ps, hs>
	{
		template
		<
			NIK_MACHINE_CONTROLS(d, m, c, i),
			T_store_U<U> V, T_store_U<LUs>... LVs, auto VN, auto... Vs
		>
		nik_ces auto result = NIK_MACHINE_BEGIN(_2_N, d, m, c, i),

			LVs..., V, Vs...

		NIK_MACHINE_END(Hs...);
	};

/***********************************************************************************************************************/

// paste:

	template
	<
		gindex_type _2_N,
		template<auto...> typename LB, auto U, auto... LUs, nik_vp(ps)(LB<U, LUs...>*),
		template<auto...> typename HB,         auto...  Hs, nik_vp(hs)(HB<    Hs...>*)
	>
	struct T_machine<MN::params, MT::paste, _2_N, ps, hs>
	{
		template
		<
			NIK_MACHINE_CONTROLS(d, m, c, i),
			T_store_U<U> V, T_store_U<LUs>... LVs, auto... Vs
		>
		nik_ces auto result = NIK_MACHINE_BEGIN(_2_N, d, m, c, i),

			LVs..., V, Vs...

		NIK_MACHINE_END(Hs...);
	};

/***********************************************************************************************************************/

// cut:

	template
	<
		gindex_type _2_N,
		template<auto...> typename LB, auto U, auto... LUs, nik_vp(ps)(LB<U, LUs...>*),
		template<auto...> typename HB,         auto...  Hs, nik_vp(hs)(HB<    Hs...>*)
	>
	struct T_machine<MN::params, MT::cut, _2_N, ps, hs>
	{
		template
		<
			NIK_MACHINE_CONTROLS(d, m, c, i),
			T_store_U<LUs>... LVs, auto VN, auto... Vs
		>
		nik_ces auto result = NIK_MACHINE_BEGIN(_2_N, d, m, c, i),

			LVs..., Vs...

		NIK_MACHINE_END(Hs...);
	};

/***********************************************************************************************************************/

// call:

	template<gindex_type _2_N>
	struct T_machine<MN::params, MT::call, _2_N>
	{
		template<auto n>
		nik_ces auto sc = T_machine_at::template contr<n>;

		template
		<
			NIK_MACHINE_CONTROLS(d, m, c, i), auto... Vs,
			template<auto...> typename B, auto... ns, typename... Heaps
		>
		nik_ces auto result(nik_avp(B<ns...>*), Heaps... Hs)
		{
			nik_ce auto sd = MD::next_depth(d);

			return NIK_MACHINE_BEGIN(_2_N, d, MM::all, c, i),

			       T_machine_start::template result<sd, sc<ns>, Vs...>()...

			NIK_MACHINE_END(Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// compel:

/***********************************************************************************************************************/


/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/

/*
	template<auto _2_N>
	struct T_algorithm<Shape::parameter, GN::fold, _2_N>
	{
		template<auto op>
		nik_ces auto H0 = U_pack_Vs<_at_, op, _car_>;
		nik_ces auto H1 = U_null_Vs;
		nik_ces auto H2 = U_null_Vs;

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
		nik_ce auto _par_fold_ = U_custom_T<T_algorithm_parameter<GN::fold, _2_N>>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sift:

/***********************************************************************************************************************/

/*
	template<auto _2_N>
	struct T_algorithm<Shape::parameter, GN::sift, _2_N>
	{
		template<auto op, auto sop>
		nik_ces auto H0 = U_pack_Vs<_at_, op, sop, _list_<>>;
		nik_ces auto H1 = U_null_Vs;
		nik_ces auto H2 = U_null_Vs;

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
		nik_ce auto _par_sift_ = U_custom_T<T_algorithm_parameter<GN::sift, _2_N>>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// action:

/***********************************************************************************************************************/

// call:

/*
	template<gindex_type _2_N>
	struct T_machine<MN::call, MT::action, _2_N>
	{
		template
		<
			NIK_MACHINE_PARAMS(d, m, c, i, Vs),
			template<auto...> typename B0, auto... Ws,
			template<auto...> typename B1, auto... Xs,
			typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<Ws...>*), nik_vp(H1)(B1<Xs...>*), Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n	= ins[MI::dec];

			if nik_ce (n >= d) // analogous to returning a machination.

				return NIK_MACHINE(_2_N, 0, MT::action, c, i, Vs)(H0, H1, Hs...);
			else
			{
				nik_ce auto ctn = ins[MI::ctn];
				nik_ce auto syn = ins[MI::syn];
				nik_ce auto key = ins[MI::key];
				nik_ce auto act = ins[MI::act];
				nik_ce auto val = eval<U_grammar<syn, key, act>, Ws...>;

				if nik_ce (ctn == MI::h1)

					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

				else if nik_ce (ctn == MI::h1_pair)

					return NIK_MACHINE(_2_N, d, MT::id, c, i, Vs)
					(
						U_null_Vs, U_pack_Vs
						<
							tuple_value<0>(val),
							tuple_value<1>(val), Xs...

						>, Hs...
					);
				else
					return val;
			}
		}
	};
*/

/***********************************************************************************************************************/

// recall:

/*
	template<gindex_type _2_N>
	struct T_machine<MN::recall, MT::action, _2_N>
	{
		template
		<
			NIK_MACHINE_PARAMS(d, m, c, i, Vs),
			template<auto...> typename B0, auto... Ws,
			template<auto...> typename B1, auto... Xs,
			typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<Ws...>*), nik_vp(H1)(B1<Xs...>*), Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n	= ins[MI::dec];

			if nik_ce (n >= d) // analogous to returning a machination.

				return NIK_MACHINE(_2_N, 0, MT::action, c, i, Vs)(H0, H1, Hs...);
			else
			{
				nik_ce auto ctn	= ins[MI::ctn];
				nik_ce auto syn = ins[MI::syn];
				nik_ce auto key	= ins[MI::key];
				nik_ce auto act	= ins[MI::act];
				nik_ce auto val = eval<U_grammar<syn, key, act>, Ws...>;

				if nik_ce (ctn == MI::h1)

					return NIK_MACHINE(_2_N, d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

				else if nik_ce (ctn == MI::h1_pair)

					return NIK_MACHINE(_2_N, d, MT::id, c, i, Vs)
					(
						U_null_Vs, U_pack_Vs
						<
							tuple_value<0>(val),
							tuple_value<1>(val), Xs...

						>, Hs...
					);
				else
					return val;
			}
		}
	};
*/

/***********************************************************************************************************************/

// left:

	struct T_machine_left
	{
		nik_ces auto d  = MD::initial_depth;
		nik_ces auto H0 = U_pack_Vs<_at_, _to_list_>;

		template<auto n, auto h = _zero>
		nik_ces auto contr = controller
		<
			instruction < MN::split  , MT::call  , n >,
			instruction < MN::split  , MT::id        >,
			instruction < MN::params , MT::front     >,
			instruction < MN::halt   , MT::eval  , h >
		>;

		template<auto n, auto... Vs>
		nik_ces auto result = T_machine_start::template result<d, contr<n>, Vs...>(H0);

	}; nik_ce auto _par_left_ = U_custom_T<T_machine_left>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

