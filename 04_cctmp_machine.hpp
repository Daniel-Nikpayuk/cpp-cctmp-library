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
			halt   , restart ,
			call   , jump    ,
			params , select  ,
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
			pause  , debug  , eval   ,
			praxis , propel , compel , cascade ,
			value  , values , go_to  , branch  ,
			front  , back   , cut    , copy    , paste , mutate ,
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
			retry , unit , all ,
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
			name , note , pos , num ,
			dimension
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

		// alias:

			template<auto Op>
			nik_ces auto with_initial_depth = _alias_<Op, initial_depth>;

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
				else if (m == MM::all)  return MT::values;
				else                    return MT::id;
			}

			nik_ces gdepth_type next_depth(gcdepth_type d)
				{ return d - bool{d != 0}; }

			nik_ces gindex_type next_index(gcdepth_type d, gckey_type m, gcindex_type i)
				{ return i + bool{d != 0 && m == MM::id}; }
	};

	using MD = MachineDispatch;

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
/***********************************************************************************************************************/

// dependencies:

/***********************************************************************************************************************/

// revalue (conditional restart):

	struct T_machine_revalue
	{
		nik_ces auto  d = MD::initial_depth;
		nik_ces auto H0 = U_pack_Vs<_car_>;

		template<auto...>
		nik_ces auto contr = controller
		<
			instruction < MN::restart , MT::value >,
			instruction < MN::halt    , MT::eval  >
		>;

		template<auto V>
		nik_ces auto result = T_machine_start::template result<d, contr<>, V>(H0);
	};

/***********************************************************************************************************************/

// params (generic):

	template<auto Note, auto Eval, auto offset = _zero>
	struct T_machine_params
	{
		nik_ces auto sH0 = U_null_Vs;
		nik_ces auto  H0 = U_pack_Vs<Eval, sH0>;

		template<auto n>
		nik_ces auto contr = controller
		<
			instruction < MN::call   , MT::praxis , PN::left , n + offset >,
			instruction < MN::params , MT::id                             >,
			instruction < MN::params , Note                               >,
			instruction < MN::halt   , MT::eval                           >
		>;

		template<auto d, auto n, auto... Vs>
		nik_ces auto result = T_machine_start::template result<d, contr<n>, Vs...>(H0);

	}; using T_machine_at = T_machine_params<MT::copy, _car_>;

/***********************************************************************************************************************/

// get:

	struct T_machine_get
	{
		template<auto n>
		nik_ces auto contr = controller
		<
			instruction < MN::call , MT::propel , n >,
			instruction < MN::halt , MT::eval       >
		>;

		nik_ces auto U_at  = U_store_T<T_machine_at>;
		nik_ces auto U_get = U_store_T<T_machine_get>;
		nik_ces auto regs  = false;
		nik_ces auto heap  = true;

		template<auto b>
		nik_ces auto U_machine = if_then_else_<b, U_get, U_at>;

		template<auto b>
		using T_machine = T_store_U<U_machine<b>>;

		template<auto b, auto n>
		nik_ces auto result = T_machine<b>::template contr<n>;
	};

/***********************************************************************************************************************/

// apply:

	struct T_machine_apply
	{
		template<auto Inds, auto Op>
		nik_ces auto H0 = U_pack_Vs<_car_, Inds, Op>;

		template<auto l = _one, auto n = _one>
		nik_ces auto contr = controller
		<
			instruction < MN::call   , MT::propel , l >,
			instruction < MN::select , MT::value      >,
			instruction < MN::select , MT::values     >,
			instruction < MN::call   , MT::eval   , n >,
			instruction < MN::halt   , MT::eval       >
		>;

		template<auto d, auto Inds, auto Op, auto... Vs>
		nik_ces auto result = T_machine_start::template result<d, contr<>, Vs...>(H0<Inds, Op>);
	};

/***********************************************************************************************************************/
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
		template<NIK_MACHINE_CONTROLS(d, m, c, i), auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto cs = list_<d, m, c, i, _2_N>;
			nik_ce auto rs = list_<Vs...>;
			nik_ce auto hs = list_<U_restore_T<Heaps>...>;

			return list_<cs, rs, hs>;
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
			template<auto...> typename B0, auto Op, auto... Ws, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<Op, Ws...>*), Heaps... Hs)
			{ return eval<Op, Vs...>; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// restart:

/***********************************************************************************************************************/

// id:

	template<gindex_type _2_N>
	struct T_machine<MN::restart, MT::id, _2_N>
	{
		template
		<
			NIK_MACHINE_CONTROLS(d, m, c, i), auto... Vs,
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

				return NIK_MACHINE_BEGIN(_2_N, d, MM::retry, c, i),

					Vs...

				NIK_MACHINE_END(V.op, V.ps, V.hs, Hs...);
			else
				return NIK_MACHINE_BEGIN(_2_N, d, MM::id, c, i),

					V, Vs...

				NIK_MACHINE_END(Hs...);
		}
	};

/***********************************************************************************************************************/

// value:

	template<gindex_type _2_N>
	struct T_machine<MN::restart, MT::value, _2_N>
	{
		template<NIK_MACHINE_CONTROLS(d, m, c, i), auto V, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			if nik_ce (is_machination<decltype(V)>)

				return NIK_MACHINE_BEGIN(_2_N, d, MM::retry, c, i),

					Vs...

				NIK_MACHINE_END(V.op, V.ps, V.hs, Hs...);
			else
				return NIK_MACHINE_BEGIN(_2_N, d, MM::id, c, i),

					V, Vs...

				NIK_MACHINE_END(Hs...);
		}
	};

/***********************************************************************************************************************/

// values:

	template<gindex_type _2_N>
	struct T_machine<MN::restart, MT::values, _2_N>
	{
		nik_ces auto sc  = T_machine_revalue::template contr<>;
		nik_ces auto sH0 = T_machine_revalue::H0;

		template<NIK_MACHINE_CONTROLS(d, m, c, i), auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto has_machination = eval<_or_, is_machination<decltype(Vs)>...>;

			if nik_ce (has_machination)

				return NIK_MACHINE_BEGIN(_2_N, d, MM::all, c, i),

				       T_machine_start::template result<MD::next_depth(d), sc, Vs>(sH0)...

				NIK_MACHINE_END(Hs...);
			else
				return NIK_MACHINE_BEGIN(_2_N, d, MM::id, c, i),

					Vs...

				NIK_MACHINE_END(Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// call:

/***********************************************************************************************************************/

// id:

	template<gindex_type _2_N>
	struct T_machine<MN::call, MT::eval, _2_N>
	{
		template<NIK_MACHINE_CONTROLS(d, m, c, i), auto Op, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto nd  = (ins[MI::pos] <= d) ? d : _zero; // machination short circuit.
			nik_ce auto sd  = MD::next_depth(nd);
			nik_ce auto V   = eval<Op, sd, Vs...>;

			return NIK_MACHINE_BEGIN(_2_N, nd, MM::unit, c, i),

				V, Vs...

			NIK_MACHINE_END(Hs...);
		}
	};

/***********************************************************************************************************************/

// praxis:

	template<gindex_type _2_N>
	struct T_machine<MN::call, MT::praxis, _2_N>
	{
		template
		<
			NIK_MACHINE_CONTROLS(d, m, c, i), auto... Vs,
			template<auto...> typename B0, auto W0, auto W1, auto... Ws, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<W0, W1, Ws...>*), Heaps... Hs)
		{
			nik_ce auto sd  = MD::next_depth(d);
			nik_ce auto ins = MD::instr(c, i);

			using Controls  = T_praxis_controls<ins[MI::pos], _2_N>;
			nik_ce auto sc  = Controls::template result<Controls, ins[MI::num], sizeof...(Vs)>();
			nik_ce auto V   = T_praxis_start::template result<sd, sc.c, sc.n, Vs...>(W1);

			return NIK_MACHINE_BEGIN(_2_N, d, MM::unit, c, i),

				V, Vs...

			NIK_MACHINE_END(H0, Hs...);
		}
	};

/***********************************************************************************************************************/

// propel:

	template<gindex_type _2_N>
	struct T_machine<MN::call, MT::propel, _2_N>
	{
		template<auto n>
		nik_ces auto contr = T_machine_at::template contr<n>;
		nik_ces auto sH0   = T_machine_at::H0;

		template
		<
			NIK_MACHINE_CONTROLS(d, m, c, i), auto... Vs,
			template<auto...> typename B0, auto... Ws, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<Ws...>*), Heaps... Hs)
		{
			nik_ce auto sd  = MD::next_depth(d);
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto sc  = contr<ins[MI::pos]>;
			nik_ce auto V   = T_machine_start::template result<sd, sc, Ws...>(sH0);

			return NIK_MACHINE_BEGIN(_2_N, d, MM::unit, c, i),

				V, Vs...

			NIK_MACHINE_END(H0, Hs...);
		}
	};

/***********************************************************************************************************************/

// compel:

		// Assumes (H0 == B0<_car_, Ws...>):

	template<gindex_type _2_N>
	struct T_machine<MN::call, MT::compel, _2_N>
	{
		template<auto l, auto n>
		nik_ces auto contr = T_machine_apply::template contr<l, n>;

		template<NIK_MACHINE_CONTROLS(d, m, c, i), auto... Vs, typename Heap0, typename... Heaps>
		nik_ces auto result(Heap0 H0, Heaps... Hs)
		{
			nik_ce auto sd  = MD::next_depth(d);
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto sc  = contr<ins[MI::pos], ins[MI::num]>;
			nik_ce auto sH0 = U_restore_T<Heap0>;
			nik_ce auto V   = T_machine_start::template result<sd, sc, Vs...>(sH0);

			return NIK_MACHINE_BEGIN(_2_N, d, MM::unit, c, i),

				V, Vs...

			NIK_MACHINE_END(H0, Hs...);
		}
	};

/***********************************************************************************************************************/

// cascade:

	template<gindex_type _2_N>
	struct T_machine<MN::call, MT::cascade, _2_N>
	{
		template
		<
			NIK_MACHINE_CONTROLS(d, m, c, i), auto V, auto V0, auto... Vs,
			template<auto...> typename B0, auto W0, auto W1, auto... Ws, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<W0, W1, Ws...>*), Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto nd  = (ins[MI::pos] <= d) ? d : _zero; // machination short circuit.
			nik_ce auto sd  = MD::next_depth(nd);
			nik_ce auto nV  = eval<W1, sd, V, V0>;

			return NIK_MACHINE_BEGIN(_2_N, nd, MM::unit, c, i),

				nV, Vs...

			NIK_MACHINE_END(H0, Hs...);
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
		template<NIK_MACHINE_CONTROLS(d, m, c, i), auto V, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto ni	= V ? ins[MI::pos] : i;

			return NIK_MACHINE_BEGIN(_2_N, d, m, c, ni),

				Vs...
				
			NIK_MACHINE_END(Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// params:

/***********************************************************************************************************************/

// id:

	template<gindex_type _2_N>
	struct T_machine<MN::params, MT::id, _2_N>
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

// front:

	template
	<
		gindex_type _2_N,
		template<auto...> typename LB, auto... LUs, nik_vp(ps)(LB<LUs...>*),
		template<auto...> typename HB, auto...  Hs, nik_vp(hs)(HB< Hs...>*)
	>
	struct T_machine<MN::params, MT::front, _2_N, ps, hs>
	{
		template<NIK_MACHINE_CONTROLS(d, m, c, i), T_store_U<LUs>... LVs, auto... Vs>
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
		template<NIK_MACHINE_CONTROLS(d, m, c, i), T_store_U<LUs>... LVs, auto... Vs>
		nik_ces auto result = NIK_MACHINE_BEGIN(_2_N, d, m, c, i),

			Vs...

		NIK_MACHINE_END(Hs...);
	};

/***********************************************************************************************************************/

// cut:

	template
	<
		gindex_type _2_N,
		template<auto...> typename LB, auto... LUs, nik_vp(ps)(LB<LUs...>*),
		template<auto...> typename HB, auto...  Hs, nik_vp(hs)(HB< Hs...>*)
	>
	struct T_machine<MN::params, MT::cut, _2_N, ps, hs>
	{
		template<NIK_MACHINE_CONTROLS(d, m, c, i), T_store_U<LUs>... LVs, auto VN, auto... Vs>
		nik_ces auto result = NIK_MACHINE_BEGIN(_2_N, d, m, c, i),

			LVs..., Vs...

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
		template<NIK_MACHINE_CONTROLS(d, m, c, i), T_store_U<LUs>... LVs, auto VN, auto... Vs>
		nik_ces auto result = NIK_MACHINE_BEGIN(_2_N, d, m, c, i),

			VN, LVs..., VN, Vs...

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
		template<NIK_MACHINE_CONTROLS(d, m, c, i), T_store_U<U> V, T_store_U<LUs>... LVs, auto... Vs>
		nik_ces auto result = NIK_MACHINE_BEGIN(_2_N, d, m, c, i),

			LVs..., V, Vs...

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
		template<NIK_MACHINE_CONTROLS(d, m, c, i), T_store_U<U> V, T_store_U<LUs>... LVs, auto VN, auto... Vs>
		nik_ces auto result = NIK_MACHINE_BEGIN(_2_N, d, m, c, i),

			LVs..., V, Vs...

		NIK_MACHINE_END(Hs...);
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// select:

/***********************************************************************************************************************/

// value:

	template<gindex_type _2_N>
	struct T_machine<MN::select, MT::value, _2_N>
	{
		template<NIK_MACHINE_CONTROLS(d, m, c, i), auto V, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto bs = unpack_<V, _car_>;
			nik_ce auto ns = unpack_<V, _cadr_>;

			return NIK_MACHINE_BEGIN(_2_N, d, m, c, i),

				Vs...

			NIK_MACHINE_END(bs, ns, Hs...);
		}
	};

/***********************************************************************************************************************/

// values:

		// Assumes (H0 == B0<_car_, Ws...>):

	template<gindex_type _2_N>
	struct T_machine<MN::select, MT::values, _2_N>
	{
		template<auto b, auto n>
		nik_ces auto sc = T_machine_get::template result<b, n>;

		template
		<
			NIK_MACHINE_CONTROLS(d, m, c, i), auto... Vs,
			template<auto...> typename BB, auto... bs,
			template<auto...> typename BN, auto... ns,
			typename Heap0, typename... Heaps
		>
		nik_ces auto result(nik_avp(BB<bs...>*), nik_avp(BN<ns...>*), Heap0 H0, Heaps... Hs)
		{
			nik_ce auto sd  = MD::next_depth(d);
			nik_ce auto sH0 = U_restore_T<Heap0>;

			return NIK_MACHINE_BEGIN(_2_N, d, MM::all, c, i),

			       T_machine_start::template result<sd, sc<bs, ns>, Vs...>(sH0)...

			NIK_MACHINE_END(H0, Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

