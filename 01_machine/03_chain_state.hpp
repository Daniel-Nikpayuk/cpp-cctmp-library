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

// chain state:

	// rename "chain" to "apply", then "subapply" to clarify this machine space intent ?

namespace machine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	template<auto U>
	using T_store_U							= cctmp::T_store_U<U>;

	template<auto... Vs>
	nik_ce auto eval						= cctmp::eval<Vs...>;

	nik_ce auto _to_pointer_					= cctmp::_to_pointer_;
	nik_ce auto _function_out_type_					= cctmp::_function_out_type_;

	template<auto Op, typename T>
	using modify_type						= cctmp::modify_type<Op, T>;

	template<auto... Vs>
	nik_ce auto at_							= cctmp::at_<Vs...>;

	nik_ce auto _par_left_						= cctmp::_par_left_;
	nik_ce auto _par_right_						= cctmp::_par_right_;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, gkey_type, auto...> struct T_chain;

/***********************************************************************************************************************/

// names:

	struct ChainName
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			halt, arg, list, lookup, conduct,
			dimension
		};
	};

	using CN = ChainName;

/***********************************************************************************************************************/

// notes:

	struct ChainNote
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			first, all, drop, apply, bind, select, push, pull,
			dimension
		};
	};

	using CT = ChainNote;

/***********************************************************************************************************************/

// instructions:

	using CI = cctmp::Instr;

/***********************************************************************************************************************/

// dispatch:

	template<auto static_contr, auto _index = 0, auto _count = 0>
	struct ChainDispatch : public MachineDispatch<static_contr, CI, _index>
	{
		// defaults:

			nik_ces gindex_type initial_count = _count;
	};

	template<auto static_contr, auto _index = 0, auto _count = 0>
	using CD = ChainDispatch<static_contr, _index, _count>;

/***********************************************************************************************************************/

// cons:

	template<auto c, auto i>
	struct T_chain_cons
	{
		template<auto l, auto t, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto j = sizeof...(Ts);
			nik_ce auto k = CD<c>::initial_count;

			return NIK_CHAIN_TS(c, i, j, k, l, t, Ts...)(vs...);
		}

	}; template<auto c, auto i>
		nik_ce auto U_chain_cons = U_store_T<T_chain_cons<c, i>>;

/***********************************************************************************************************************/

// start:

	struct T_chain_start
	{
		template<auto c, auto l, auto t, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto i = CD<c>::initial_index;
			nik_ce auto j = sizeof...(Ts);
			nik_ce auto k = CD<c>::initial_count;

			return NIK_CHAIN_TS(c, i, j, k, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// istart:

	struct T_chain_istart
	{
		template<auto c, auto i, auto l, auto t, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto j = sizeof...(Ts);
			nik_ce auto k = CD<c>::initial_count;

			return NIK_CHAIN_TS(c, i, j, k, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_chain<CN::halt, CT::first, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, k, l, t), typename T0, typename... Ts>
		nik_ces auto result(T0 v0, Ts... vs) -> T0 { return v0; }
	};

/***********************************************************************************************************************/

// all:

	template<auto... filler>
	struct T_chain<CN::halt, CT::all, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, k, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) { return cctmp::tuple<Ts...>(vs...); }
	};

/***********************************************************************************************************************/

// drop:

	template<auto... filler>
	struct T_chain<CN::halt, CT::drop, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, k, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) { return k; }
	};

/***********************************************************************************************************************/

// apply:

	template<auto... filler>
	struct T_chain<CN::halt, CT::apply, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, k, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) { return T_store_U<k>::template result<Ts...>(vs...); }
						// direct member call required to preserve reference semantics.
	};

/***********************************************************************************************************************/

// bind:

	template<auto... filler>
	struct T_chain<CN::halt, CT::bind, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, k, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) { return T_store_U<k>::template result<l, t, Ts...>(vs...); }
						// direct member call required to preserve reference semantics.
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// arg:

/***********************************************************************************************************************/

// select:

	template<auto... filler>
	struct T_chain<CN::arg, CT::select, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, k, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n  = CD<c>::pos(i);
			nik_ce auto p0 = eval<_par_left_ , n, U_store_T<Ts>...>;
			nik_ce auto p1 = eval<_par_right_, n, U_store_T<Ts>...>;

			return NIK_CHAIN_TEMPLATE(c, i), p0, p1
				NIK_CHAIN_RESULT_TS(c, i, j, k, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// drop:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto... RUs, nik_vp(p1)(B1<RUs...>*)
	>
	struct T_chain<CN::arg, CT::drop, p0, p1>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, k, l, t), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<RUs>... rvs)
			{ return NIK_CHAIN_TS(c, i, j, k, l, t, T_store_U<RUs>...)(rvs...); }
	};

/***********************************************************************************************************************/

// push:

	template
	<
		template<auto...> typename B0,          auto... LUs, nik_vp(p0)(B0<    LUs...>*),
		template<auto...> typename B1, auto RU, auto... RUs, nik_vp(p1)(B1<RU, RUs...>*)
	>
	struct T_chain<CN::arg, CT::push, p0, p1>
	{
		using RT = T_store_U<RU>;

		template<NIK_CHAIN_PARAMS(c, i, j, k, l, t), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs)
		{
			return NIK_CHAIN_4TS
				(c, i, j, k, l, t, T_store_U<LUs>..., RT, T_store_U<RUs>..., RT)
					(lvs..., rv, rvs..., rv);
		}
	};

/***********************************************************************************************************************/

// pull:

	template
	<
		template<auto...> typename B0,          auto... LUs, nik_vp(p0)(B0<    LUs...>*),
		template<auto...> typename B1, auto RU, auto... RUs, nik_vp(p1)(B1<RU, RUs...>*)
	>
	struct T_chain<CN::arg, CT::pull, p0, p1>
	{
		using RT	= T_store_U<RU>;
		nik_ces auto nk	= U_restore_T<RT>;

		template<NIK_CHAIN_PARAMS(c, i, j, k, l, t), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs)
		{
			return NIK_CHAIN_3TS
				(c, i, j, nk, l, t, T_store_U<LUs>..., RT, T_store_U<RUs>...)
					(lvs..., rv, rvs...);
		}
	};

/***********************************************************************************************************************/

// apply:

	template
	<
		template<auto...> typename B0,          auto... LUs, nik_vp(p0)(B0<    LUs...>*),
		template<auto...> typename B1, auto RU, auto... RUs, nik_vp(p1)(B1<RU, RUs...>*)
	>
	struct T_chain<CN::arg, CT::apply, p0, p1>
	{
		using RT = T_store_U<RU>;

		template<NIK_CHAIN_PARAMS(c, i, j, k, l, t), typename... Ts> // equals sizeof...(Ts).
		nik_ces auto result(T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs)
		{
			using f_type  = modify_type<_to_pointer_, decltype(T_store_U<k>::template result<RT>)>;
			nik_ce auto f = (f_type) T_store_U<k>::template result<RT>;
			nik_ce auto F = eval<_function_out_type_, f>;

			return NIK_CHAIN_4TS
				(c, i, j, k, l, t, T_store_U<LUs>..., RT, T_store_U<RUs>..., T_store_U<F>)
					(lvs..., rv, rvs..., f(rv));
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// list:

/***********************************************************************************************************************/

// select:

	template<auto... filler>
	struct T_chain<CN::list, CT::select, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, k, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n = CD<c>::pos(i);
			nik_ce auto p = at_<l, n>;

			return NIK_CHAIN_TEMPLATE(c, i), p
				NIK_CHAIN_RESULT_TS(c, i, j, k, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// push:

	template<auto... filler>
	struct T_chain<CN::list, CT::push, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, k, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n = CD<c>::pos(i);
			nik_ce auto v = at_<l, n>;

			return NIK_CHAIN_2TS(c, i, j, k, l, t, Ts..., decltype(v))(vs..., v);
		}
	};

/***********************************************************************************************************************/

// pull:

	template<auto... filler>
	struct T_chain<CN::list, CT::pull, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, k, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n  = CD<c>::pos(i);
			nik_ce auto nk = at_<l, n>;

			return NIK_CHAIN_TS(c, i, j, nk, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// apply:

	template<auto... filler>
	struct T_chain<CN::list, CT::apply, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, k, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n = CD<c>::pos(i);
			nik_ce auto v = at_<l, n>;
			nik_ce auto f = T_store_U<k>::template result<decltype(v)>;
			nik_ce auto F = eval<_function_out_type_, f>;

			return NIK_CHAIN_2TS(c, i, j, k, l, t, Ts..., T_store_U<F>)(vs..., f(v));
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lookup:

/***********************************************************************************************************************/

// push:

	template<template<auto...> typename B, auto... fs, nik_vp(env)(B<fs...>*)>
	struct T_chain<CN::lookup, CT::push, env>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, k, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni  = CD<c>::pos(i);
			nik_ce auto n   = CD<c>::num(i);
			nik_ce auto str = at_<l, n>;
			nik_ce auto v   = T_lookup_istart::template result<c, ni, str>(fs...);

			return NIK_CHAIN_2TS(c, i, j, k, l, t, Ts..., decltype(v))(vs..., v);
		}
	};

/***********************************************************************************************************************/

// pull:

	template<template<auto...> typename B, auto... fs, nik_vp(env)(B<fs...>*)>
	struct T_chain<CN::lookup, CT::pull, env>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, k, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni  = CD<c>::pos(i);
			nik_ce auto n   = CD<c>::num(i);
			nik_ce auto str = at_<l, n>;
			nik_ce auto nk  = T_lookup_istart::template result<c, ni, str>(fs...);

			return NIK_CHAIN_TS(c, i, j, nk, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// apply:

	template<template<auto...> typename B, auto... fs, nik_vp(env)(B<fs...>*)>
	struct T_chain<CN::lookup, CT::apply, env>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, k, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni  = CD<c>::pos(i);
			nik_ce auto n   = CD<c>::num(i);
			nik_ce auto str = at_<l, n>;
			nik_ce auto v   = T_lookup_istart::template result<c, ni, str>(fs...);

			nik_ce auto f   = T_store_U<k>::template result<decltype(v)>;
			nik_ce auto F   = eval<_function_out_type_, f>;

			return NIK_CHAIN_2TS(c, i, j, k, l, t, Ts..., T_store_U<F>)(vs..., f(v));
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// conduct:

/***********************************************************************************************************************/

// push:

	template<auto... filler>
	struct T_chain<CN::conduct, CT::push, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, k, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = CD<c>::pos(i);
			nik_ce auto v  = U_chain_cons<c, ni>;

			return NIK_CHAIN_2TS(c, i, j, k, l, t, Ts..., decltype(v))(vs..., v);
		}
	};

/***********************************************************************************************************************/

// pull:

	template<auto... filler>
	struct T_chain<CN::conduct, CT::pull, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, k, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = CD<c>::pos(i);
			nik_ce auto nk = U_chain_cons<c, ni>;

			return NIK_CHAIN_TS(c, i, j, nk, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

