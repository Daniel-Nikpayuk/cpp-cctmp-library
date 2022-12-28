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

	// Arbitrary template<auto...> typename B input for greater utility,
	// U_pack_Vs for internal output for greater generality.

	// H0: Holds operators.
	// H1: Holds stack parameters.
	// H2: Holds stack arguments.
	// H3: Holds return values.
	// H4: Holds constants.
	// H5: Holds memoization tables (if applicable).

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
			halt  , jump , restart ,
			front , args , action  , compel ,
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

			pause  , debug  , list ,
			go_to  , branch ,
			value  , params ,
			index  , call   , recall , mutate ,
			dimension
		};
	};

	using MT = MachineNote;

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

		nik_ces gindex_type length     (cinstr_type i)  { return i[size]; }
		nik_ces bool        is_optimal (gcindex_type n) { return (n < _eight); }
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
			nik_ces gindex_type initial_index = _zero;

		// accessors:

			nik_ces auto instr(ccontr_type c, gcindex_type i)
				{ return c[i]; }

		// navigators:

			nik_ces gkey_type next_name(gcdepth_type d, gckey_type m, gckey_type t, ccontr_type c, gcindex_type i)
			{
				if      (d == 0)      return MN::halt;
				else if (m == MN::id) return c[i+1][MI::name];
				else if (t == MT::id) return m;
				else                  return MN::restart;
			}

			nik_ces gkey_type next_note(gcdepth_type d, gckey_type m, gckey_type t, ccontr_type c, gcindex_type i)
			{
				if      (d == 0)      return MT::pause;
				else if (m == MN::id) return c[i+1][MI::note];
				else if (t == MT::id) return MT::recall;
				else                  return t;
			}

			nik_ces gdepth_type next_depth(gcdepth_type d)
				{ return d - bool{d != 0}; }

			nik_ces gindex_type next_index(gcdepth_type d, gckey_type m, gckey_type t, gcindex_type i)
				{ return i + bool{d != 0 && m == MN::id && t == MT::id}; }
	};

	using MD = MachineDispatch;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// start:

	struct T_machine_start
	{
		nik_ces auto _2_N = MD::_2_N;
		nik_ces auto d    = MD::initial_depth;
		nik_ces auto m    = MN::id;
		nik_ces auto t    = MT::id;
		nik_ces auto i    = MD::initial_index;

		template<auto c, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs) { return NIK_MACHINE(_2_N, d, m, t, c, i, Vs)(Hs...); }

	}; nik_ce auto U_machine_start = U_custom_T<T_machine_start>;

/***********************************************************************************************************************/

// restart:

	struct T_machine_restart
	{
		template<NIK_MACHINE_CONTROLS(d, m, t, c, i), auto _2_N, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs) { return NIK_MACHINE(_2_N, d, m, t, c, i, Vs)(Hs...); }

	}; nik_ce auto U_machine_restart = U_store_T<T_machine_restart>;

/***********************************************************************************************************************/

// recall:

	struct T_machine_recall
	{
		template<auto d, typename T, template<auto...> typename B, auto p, auto... Ps>
		nik_ces auto _result(T, nik_avp(B<p, Ps...>*))
		{
			return eval<_tailor_, U_restore_T<T>, p, d, Ps...>;
		}

		template<auto d, typename T>
		nik_ces auto result(T v)
		{
			if nik_ce (is_machination<T>) return _result<d>(v.u, v.p);
			else return v;
		}

	}; nik_ce auto U_machine_recall = U_store_T<T_machine_recall>;

/***********************************************************************************************************************/

// left:

	struct T_machine_left
	{
		template<auto n>
		nik_ces auto contr = controller
		<
			instruction < MN::front , MT::call , n >,
			instruction < MN::halt  , MT::list     >
		>;

		template<auto n, auto... Vs>
		nik_ces auto result = T_machine_start::template result<contr<n>, Vs...>();

	}; nik_ce auto _par_left_ = U_custom_T<T_machine_left>;

/***********************************************************************************************************************/

// at:

	struct T_machine_at
	{
		template<auto n>
		nik_ces auto contr = controller
		<
			instruction < MN::front , MT::call  , n >,
			instruction < MN::halt  , MT::value     >
		>;

		template<auto n, auto... Vs>
		nik_ces auto result = T_machine_start::template result<contr<n>, Vs...>();

	}; nik_ce auto _par_at_ = U_custom_T<T_machine_at>;

/***********************************************************************************************************************/

// apply:

	struct T_machine_apply
	{
		template<auto n>
		nik_ces auto contr = controller
		<
			instruction < MN::args   , MT::index     >,
			instruction < MN::args   , MT::call      >,
			instruction < MN::compel , MT::call  , n >//,
		//	instruction < MN::halt   , MT::first     >
		>;

		template<auto n, auto... Vs>
		nik_ces auto result = T_machine_start::template result<contr<n + 1>, Vs...>();

	}; nik_ce auto _par_apply_ = U_custom_T<T_machine_apply>;

/***********************************************************************************************************************/

// replace:

	template<auto n>
	nik_ce auto U_replace_contr = U_pack_Vs
	<
		instruction < MN::front , MT::call   , n >,
		instruction < MN::args  , MT::mutate     >
	>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

/***********************************************************************************************************************/

// pause:

	template<gindex_type _2_N>
	struct T_machine<MN::halt, MT::pause, _2_N>
	{
		template<NIK_MACHINE_PARAMS(d, m, t, c, i, Vs), typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto p = U_pack_Vs<U_restore_T<Heaps>...>;

			return machination(U_machine_restart, U_pack_Vs<p, m, t, c, i, _2_N, Vs...>);
		}
	};

/***********************************************************************************************************************/

// debug:

	template<gindex_type _2_N>
	struct T_machine<MN::halt, MT::debug, _2_N>
	{
		template<NIK_MACHINE_PARAMS(d, m, t, c, i, Vs), typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto cs = eval<_to_tuple_, d, m, t, c, i, _2_N>;
			nik_ce auto rs = eval<_to_tuple_, Vs...>;
			nik_ce auto hs = eval<_to_tuple_, U_restore_T<Heaps>...>;

			return eval<_to_tuple_, cs, rs, hs>;
		}
	};

/***********************************************************************************************************************/

// list:

	template<gindex_type _2_N>
	struct T_machine<MN::halt, MT::list, _2_N>
	{
		template<NIK_MACHINE_CONTROLS(d, m, t, c, i), auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			return U_pack_Vs<Vs...>;
		}
	};

/***********************************************************************************************************************/

// value:

	template
	<
		gindex_type _2_N,
		auto... LUs, nik_vp(p )(T_pack_Vs<LUs...>*),
		auto...  Hs, nik_vp(hs)(T_pack_Vs<Hs...>* )
	>
	struct T_machine<MN::halt, MT::value, _2_N, p, hs>
	{
		template<NIK_MACHINE_CONTROLS(d, m, t, c, i), T_store_U<LUs>... LVs, auto VN, auto... Vs>
		nik_ces auto result = VN;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// jump:

/***********************************************************************************************************************/

// go to:

	template<gindex_type _2_N>
	struct T_machine<MN::jump, MT::go_to, _2_N>
	{
		template<NIK_MACHINE_PARAMS(d, m, t, c, i, Vs), typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto ni	= ins[MI::pos];

			return NIK_MACHINE(_2_N, d, m, t, c, ni, Vs)(Hs...);
		}
	};

/***********************************************************************************************************************/

// branch:

	template<gindex_type _2_N>
	struct T_machine<MN::jump, MT::branch, _2_N>
	{
		template
		<
			NIK_MACHINE_PARAMS(d, m, t, c, i, Vs),
			typename Heap0, template<auto...> typename B1, bool X0, auto... Xs, typename... Heaps
		>
		nik_ces auto result(Heap0 H0, nik_vp(H1)(B1<X0, Xs...>*), Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto ni	= X0 ? ins[MI::pos] : i;

			return NIK_MACHINE(_2_N, d, m, t, c, ni, Vs)(H0, U_pack_Vs<Xs...>, Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// restart:

/***********************************************************************************************************************/

// value:

	template<gindex_type _2_N>
	struct T_machine<MN::restart, MT::value, _2_N>
	{
		template
		<
			NIK_MACHINE_PARAMS(d, m, t, c, i, Vs),
			typename T, template<auto...> typename B, auto p, auto... Ps,
			typename... Heaps
		>
		nik_ces auto result(T, nik_avp(B<p, Ps...>*), Heaps... Hs)
		{
			nik_ce auto op  = U_restore_T<T>;
			nik_ce auto nd  = MD::next_depth(d);
			nik_ce auto val = eval<_tailor_, op, p, nd, Ps...>;

			if nik_ce (is_machination<decltype(val)>)

				return NIK_MACHINE(_2_N, d, m, t, c, i, Vs)(val.u, val.p, Hs...);
			else
				return NIK_MACHINE_BEGIN(_2_N, d, m, MT::id, c, i),

					val, Vs...

				NIK_MACHINE_END(Hs...);
		}
	};

/***********************************************************************************************************************/

// args:

	template<gindex_type _2_N>
	struct T_machine<MN::restart, MT::params, _2_N>
	{
		using T_or = T_store_U<_or_>;

		template<NIK_MACHINE_CONTROLS(d, m, t, c, i), auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto has_machination = T_or::result(is_machination<decltype(Vs)>...);

			if nik_ce (has_machination)
			{
				return NIK_MACHINE_BEGIN(_2_N, d, m, t, c, i),

				       T_machine_recall::template result<d>(Vs)...

				NIK_MACHINE_END(Hs...);
			}
			else return NIK_MACHINE(_2_N, d, MN::id, MT::id, c, i, Vs)(Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// front:

/***********************************************************************************************************************/

// call:

	template<gindex_type _2_N>
	struct T_machine<MN::front, MT::call, _2_N>
	{
		template<NIK_MACHINE_PARAMS(d, m, t, c, i, Vs), typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto lc	= left_controls(ins[MI::pos], sizeof...(Vs), _2_N);
			nik_ce auto sc  = left_controls::template contr<lc.pad, lc.pos>;
			nik_ce auto val = T_praxis_start::template result
					<
						sc, lc.push, U_store_T<decltype(Vs)>...

					>(lc.h0, lc.h1, lc.h2);

			if nik_ce (is_machination<decltype(val)>)

				return NIK_MACHINE(_2_N, d, MN::front, MT::value, c, i, Vs)(val.u, val.p, Hs...);
			else
				return NIK_MACHINE_BEGIN(_2_N, d, MN::front, MT::id, c, i),

					val, Vs...

				NIK_MACHINE_END(Hs...);
		}
	};

/***********************************************************************************************************************/

// recall:

	template<gindex_type _2_N>
	struct T_machine<MN::front, MT::recall, _2_N>
	{
		nik_ces auto nm = MN::id;

		template<NIK_MACHINE_CONTROLS(d, m, t, c, i), auto V, auto...Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto name = MD::next_name(d, nm, t, c, i);
			nik_ce auto note = MD::next_note(d, nm, t, c, i);
			nik_ce auto nd   = MD::next_depth(d);
			nik_ce auto ni   = MD::next_index(d, nm, i);
			nik_ce auto hs   = U_pack_Vs<U_restore_T<Heaps>...>;
			nik_ce auto cont = eval<_to_list_, H_machine, name, note, _2_N, V, hs>;

			// this is an extra nesting depth call!

			return T_store_U<cont>::template result<nd, nm, t, c, ni, Vs...>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// args:

/***********************************************************************************************************************/

// index:

	template<gindex_type _2_N>
	struct T_machine<MN::args, MT::index, _2_N>
	{
		template
		<
			NIK_MACHINE_PARAMS(d, m, t, c, i, Vs),
			template<auto...> typename B0, auto W, auto... Ws, typename Heap1, typename... Heaps
		>
		nik_ces auto result(nik_vp(H0)(B0<W, Ws...>*), Heap1 H1, Heaps... Hs)
		{
			nik_ce auto ins	= PD::instr(c, i);
			nik_ce auto nH1 = eval<W, ins[PI::pos], Ws...>;

			return NIK_MACHINE(_2_N, d, m, t, c, i, Vs)(H0, nH1, Hs...);
		}
	};

/***********************************************************************************************************************/

// call:

	template<gindex_type _2_N>
	struct T_machine<MN::args, MT::call, _2_N>
	{
		template<auto n>
		nik_ces auto nc = T_machine_at::template contr<n>;
		nik_ces auto nd = MD::initial_depth;
		nik_ces auto nm = MN::id;
		nik_ces auto nt = MN::id;
		nik_ces auto ni = MD::initial_index;

		template
		<
			NIK_MACHINE_CONTROLS(d, m, t, c, i), auto... Vs,
			typename Heap0, template<auto...> typename B1, auto... Xs, typename... Heaps
		>
		nik_ces auto result(Heap0 H0, nik_vp(H1)(B1<Xs...>*), Heaps... Hs)
		{
			nik_ce auto nH1 = U_store_T<B1<>>;

			return NIK_MACHINE_BEGIN(_2_N, d, m, MT::params, c, i),

			       T_machine_restart::template result<nd, nm, nt, nc<Xs>, ni, _2_N, Vs...>()...

			NIK_MACHINE_END(H0, nH1, Hs...);
		}
	};

/***********************************************************************************************************************/

// mutate:

	template
	<
		gindex_type _2_N,
		auto U, auto... LUs, void(*p)(T_pack_Vs<U, LUs...>*),
		auto... Hs, void(*hs)(T_pack_Vs<Hs...>*)
	>
	struct T_machine<MN::args, MT::mutate, _2_N, p, hs>
	{
		template
		<
			NIK_MACHINE_CONTROLS(d, m, t, c, i),
			T_store_U<U> V, T_store_U<LUs>... LVs, auto VN, auto... Vs
		>
		nik_ces auto result = NIK_MACHINE_BEGIN(_2_N, d, m, t, c, i), LVs..., V, Vs...>(Hs...);
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// apply:

/***********************************************************************************************************************/


/***********************************************************************************************************************/

// fold:

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

// sift:

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
			NIK_MACHINE_PARAMS(d, m, t, c, i, Vs),
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
			NIK_MACHINE_PARAMS(d, m, t, c, i, Vs),
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
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

