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

/***********************************************************************************************************************/

// names:

	struct MachineName
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.

			call        , recall      ,
			paste_r_all , paste_a_all ,
			stage       , jump        , memoize ,
			halt
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

			pause  , debug  ,
			left   , sift   , fold   ,
			go_to  , branch ,
			action , compel , propel ,
			lookup , insert
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

			nik_ces gkey_type next_name(gcdepth_type d, gckey_type m, ccontr_type c, gcindex_type i)
			{
				if (d == 0)           return MN::halt;
				else if (m != MT::id) return MN::recall;
				else                  return c[i+1][MI::name];
			}

			nik_ces gkey_type next_note(gcdepth_type d, gckey_type m, ccontr_type c, gcindex_type i)
			{
				if (d == 0)           return MT::pause;
				else if (m != MT::id) return m;
				else                  return c[i+1][MI::note];
			}

			nik_ces gdepth_type next_depth(gcdepth_type d)
				{ return d - bool{d != 0}; }

			nik_ces gindex_type next_index(gcdepth_type d, gckey_type m, gcindex_type i)
				{ return i + bool{d != 0 && m == MT::id}; }
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
		nik_ces auto m    = MT::id;
		nik_ces auto i    = MD::initial_index;

		template<auto c, auto... Vs, typename... Heaps>
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

// halt:

/***********************************************************************************************************************/

// pause:

	template<gindex_type _2_N>
	struct T_machine<MN::halt, MT::pause, _2_N>
	{
		template<NIK_MACHINE_PARAMS(d, m, c, i, Vs), typename... Heaps>
		nik_ces auto result(Heaps...)
		{
			nik_ce auto p = U_pack_Vs<U_restore_T<Heaps>...>;

			return machination(U_machine_restart, U_pack_Vs<p, m, c, i, _2_N, Vs...>);
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
			nik_ce auto cs = eval<_to_tuple_, d, m, c, i>;
			nik_ce auto rs = eval<_to_tuple_, Vs...>;
			nik_ce auto hs = eval<_to_tuple_, U_restore_T<Heaps>...>;

			return eval<_to_tuple_, cs, rs, hs>;
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

			return NIK_MACHINE(_2_N, d, MT::id, c, ni, Vs)(Hs...);
		}
	};

// branch:

	template<gindex_type _2_N>
	struct T_machine<MN::jump, MT::branch, _2_N>
	{
		template
		<
			NIK_MACHINE_PARAMS(d, m, c, i, Vs),
			typename Heap0, template<auto...> typename B1, bool X0, auto... Xs, typename... Heaps
		>
		nik_ces auto result(Heap0 H0, nik_vp(H1)(B1<X0, Xs...>*), Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto ni	= X0 ? ins[MI::pos] : i;

			return NIK_MACHINE(_2_N, d, MT::id, c, ni, Vs)(H0, U_pack_Vs<Xs...>, Hs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// left:

/***********************************************************************************************************************/

// call:

	template<gindex_type _2_N>
	struct T_machine<MN::call, MT::left, _2_N>
	{
		nik_ces auto h0 = U_null_Vs;
		nik_ces auto h1 = U_null_Vs;
		nik_ces auto h2 = U_null_Vs;

		template<NIK_MACHINE_PARAMS(d, m, c, i, Vs), typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n	= ins[MI::pos];
			nik_ce auto s   = sizeof...(Vs);

			nik_ce auto k0  = n / _2_N;
			nik_ce auto j0  = n % _2_N;
			nik_ce auto p   = conditional_padding(n, s, _2_N);

			nik_ce auto b   = (k0 != 0 && j0 == 0);
			nik_ce auto k   = k0 - b;
			nik_ce auto j   = b ? _2_N : j0;
			nik_ce auto sc  = left_contr<p, j>;

			nik_ce auto val = T_praxis_start::template result<sc, k, Vs...>(h0, h1, h2);

			if nik_ce (is_machination<decltype(val)>)

				return NIK_MACHINE(_2_N, d, MT::left, c, i, Vs)(val.u, val.p, Hs...);
			else
				return NIK_MACHINE_TEMPLATE(_2_N, d, m, c, i),

					val

				NIK_MACHINE_RESULT(d, m, c, i, Vs)(Hs...);
		}
	};

/***********************************************************************************************************************/

// recall:

	template<gindex_type _2_N>
	struct T_machine<MN::recall, MT::left, _2_N>
	{
		template
		<
			NIK_MACHINE_PARAMS(d, m, c, i, Vs),
			typename T, template<auto...> typename B, auto p, auto... Ps,
			typename... Heaps
		>
		nik_ces auto result(T, nik_avp(B<p, Ps...>*), Heaps... Hs)
		{
			nik_ce auto op  = U_restore_T<T>;
			nik_ce auto val = eval<_tailor_, op, p, d, Ps...>;

			if nik_ce (is_machination<decltype(val)>)

				return NIK_MACHINE(_2_N, d, MT::left, c, i, Vs)(val.u, val.p, Hs...);
			else
				return NIK_MACHINE_TEMPLATE(_2_N, d, m, c, i),

					val

				NIK_MACHINE_RESULT(d, m, c, i, Vs)(Hs...);
		}
	};

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

//	template<auto _2_N = _2_6>
//	nik_ce auto _par_left_ = U_custom_T<T_algorithm_parameter<GN::left, _2_N>>;

// unit (generic):

/*
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
*/

/***********************************************************************************************************************/

// at:

/*
	template<template<auto...> typename B, auto... LUs, nik_vp(p)(B<LUs...>*)>
	struct T_algorithm<Shape::parameter, GN::at, p>
	{
		template<T_store_U<LUs>... LVs, auto VN, auto... Vs>
		nik_ces auto result = VN;

	}; nik_ce auto _par_at_ = _par_unit_<GN::at>;
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
/***********************************************************************************************************************/

// compel:

/***********************************************************************************************************************/

// call:

/*
	template<gindex_type _2_N>
	struct T_machine<MN::call, MT::compel, _2_N>
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

				return NIK_MACHINE(_2_N, 0, MT::compel, c, i, Vs)(H0, H1, Hs...);
			else
			{
				nik_ce auto ctn	= ins[MI::ctn];
				nik_ce auto syn = ins[MI::syn];
				nik_ce auto key = ins[MI::key];
				nik_ce auto act = ins[MI::act];
				nik_ce auto nd	= d+1-n;
				nik_ce auto val = eval<U_grammar<syn, key, act>, nd, Ws...>;

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(_2_N, d, MT::propel, c, i, Vs)
						(val.u, val.p, H1, Hs...);

				else if nik_ce (ctn == MI::h1)

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

// recall:

/*
	template<gindex_type _2_N>
	struct T_machine<MN::recall, MT::compel, _2_N>
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

				return NIK_MACHINE(_2_N, 0, MT::compel, c, i, Vs)(H0, H1, Hs...);
			else
			{
				nik_ce auto ctn	= ins[MI::ctn];
				nik_ce auto syn = ins[MI::syn];
				nik_ce auto key = ins[MI::key];
				nik_ce auto act = ins[MI::act];
				nik_ce auto nd	= d+1-n;
				nik_ce auto val = eval<U_grammar<syn, key, act>, nd, Ws...>;

				if nik_ce (is_machination<decltype(val)>)

					return NIK_MACHINE(_2_N, d, MT::propel, c, i, Vs)
						(val.u, val.p, H1, Hs...);

				else if nik_ce (ctn == MI::h1)

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

// propel:

	// No direct call.

/***********************************************************************************************************************/

// recall:

/*
	template<gindex_type _2_N>
	struct T_machine<MN::recall, MT::propel, _2_N>
	{
		template
		<
			NIK_MACHINE_PARAMS(d, m, c, i, Vs),
			typename _U, template<auto...> typename B, auto... _Ws,
			template<auto...> typename B1, auto... Xs, typename... Heaps
		>
		nik_ces auto result(_U, nik_avp(B<_Ws...>*), nik_vp(H1)(B1<Xs...>*), Heaps... Hs)
		{
			nik_ce auto ins = MD::instr(c, i);
			nik_ce auto ctn = ins[MI::ctn];
			nik_ce auto val = T_restore_T<_U>::template result<d, _Ws...>;

			if nik_ce (is_machination<decltype(val)>)

				return NIK_MACHINE(_2_N, d, MT::propel, c, i, Vs)
					(val.u, val.p, H1, Hs...);

			else if nik_ce (ctn == MI::h1)

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
	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// memoize:

/***********************************************************************************************************************/

// lookup:

	template<gindex_type _2_N>
	struct T_machine<MN::memoize, MT::lookup, _2_N>
	{
		struct T_same_car
		{
			template<auto W, auto Z>
			nik_ces auto result = eval<_same_, W, unpack_<Z, _car_>>;

		}; nik_ces auto _same_car_ = U_custom_T<T_same_car>;

		template
		<
			NIK_MACHINE_PARAMS(d, m, c, i, Vs),
			template<auto...> typename B0, auto W0,
			template<auto...> typename B1, auto... Xs, typename Heap2,
			template<auto...> typename B3, auto... Zs, typename... Args
		>
		nik_ces auto result(nik_vp(H0)(B0<W0>*), nik_vp(H1)(B1<Xs...>*), Heap2 H2, nik_vp(A0)(B3<Zs...>*), Args... As)
		{
			nik_ce auto size = sizeof...(Zs);
			nik_ce auto pos	 = find_<_alias_<_same_car_, W0>, Zs...>;

			if nik_ce (pos == size)

				return NIK_MACHINE(_2_N, d, MT::id, c, i, Vs)(U_null_Vs, H1, H2, A0, As...);
			else
			{
				nik_ce auto ins = MD::instr(c, i);
				nik_ce auto ni  = ins[MI::pos];

				return NIK_MACHINE(_2_N, d, MT::id, c, ni, Vs)(A0, U_pack_Vs<pos, Xs...>, H2, A0, As...);
			}
		}
	};

/***********************************************************************************************************************/

// insert:

	template<gindex_type _2_N>
	struct T_machine<MN::memoize, MT::insert, _2_N>
	{
		template
		<
			NIK_MACHINE_PARAMS(d, m, c, i, Vs), template<auto...> typename B0, auto W0,
			template<auto...> typename B1, auto X0, auto... Xs, typename Heap2,
			template<auto...> typename B3, auto... Zs, typename... Args
		>
		nik_ces auto result
		(
			nik_vp(H0)(B0<W0>*), nik_vp(H1)(B1<X0, Xs...>*), Heap2 H2, nik_vp(A0)(B3<Zs...>*), Args... As
		)
		{
			nik_ce auto Z0 = U_pack_Vs<W0, X0>;
			nik_ce auto a0 = U_pack_Vs<Z0, Zs...>;

			return eval<_to_tuple_, a0, X0>;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lookup:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// default:

	nik_ce auto default_machine_lookup()
	{
		return table
		(
		 	U_char,

			binding( "same"              , _same_              ),
			binding( "is_null"           , _is_null_           ),
			binding( "length"            , _length_            ),
			binding( "car"               , _car_               ),
			binding( "nop"               , _nop_               ),
			binding( "cadr"              , _cadr_              ),
			binding( "at"                , _at_                ),
			binding( "find"              , _find_              ),

			binding( "is_const"          , _is_const_          ),
			binding( "add_const"         , _add_const_         ),
			binding( "remove_const"      , _remove_const_      ),
			binding( "to_const"          , _to_const_          ),
			binding( "from_const"        , _from_const_        ),

			binding( "csame"             , _csame_             ),
			binding( "name"              , _name_              ),
			binding( "similar"           , _similar_           ),
			binding( "to_list"           , _to_list_           ),
			binding( "f0_unpack"         , _f0_unpack_         ),
			binding( "f1_unpack"         , _f1_unpack_         ),
			binding( "f2_unpack"         , _f2_unpack_         ),
			binding( "b0_unpack"         , _b0_unpack_         ),
			binding( "b1_unpack"         , _b1_unpack_         ),
			binding( "b2_unpack"         , _b2_unpack_         ),
			binding( "rename"            , _rename_            ),
			binding( "pad"               , _pad_               ),
			binding( "cdr"               , _cdr_               ),
			binding( "map"               , _map_               ),
			binding( "zip"               , _zip_               ),
			binding( "unite"             , _unite_             ),
			binding( "cons"              , _cons_              ),
			binding( "push"              , _push_              ),

			binding( "if_then_else"      , _if_then_else_      ),

			binding( "is_unsigned"       , _is_unsigned_       ),
			binding( "not_unsigned"      , _not_unsigned_      ),
			binding( "is_signed"         , _is_signed_         ),
			binding( "not_signed"        , _not_signed_        ),
			binding( "is_integer"        , _is_integer_        ),
			binding( "not_integer"       , _not_integer_       ),

			binding( "is_pointer"        , _is_pointer_        ),
			binding( "add_pointer"       , _add_pointer_       ),
			binding( "remove_pointer"    , _remove_pointer_    ),
			binding( "to_pointer"        , _to_pointer_        ),
			binding( "from_pointer"      , _from_pointer_      ),

			binding( "is_reference"      , _is_reference_      ),
			binding( "add_reference"     , _add_reference_     ),
			binding( "remove_reference"  , _remove_reference_  ),
			binding( "to_reference"      , _to_reference_      ),
			binding( "from_reference"    , _from_reference_    ),

			binding( "to_array"          , _to_array_          ),
			binding( "array_apply"       , _array_apply_       ),

			binding( "function_type"     , _function_type_     ),
			binding( "function_arity"    , _function_arity_    ),
			binding( "function_out_type" , _function_out_type_ ),
			binding( "function_in_types" , _function_in_types_ ),

			binding( "custom"            , _custom_            ),
			binding( "nested"            , _nested_            ),
			binding( "procedure"         , _procedure_         ),
			binding( "method"            , _method_            ),
			binding( "tailor"            , _tailor_            ),

			binding( "list_to_array"     , _list_to_array_     ),
			binding( "array_to_list"     , _array_to_list_     )
		);
	};

	nik_ce auto default_machine_environment = make_environment<default_machine_lookup>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

