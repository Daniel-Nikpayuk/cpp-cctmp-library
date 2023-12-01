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

// cycle state:

namespace machine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	nik_ce auto _id_				= cctmp::_id_;

	template<auto Op, typename T>
	using modify_type				= cctmp::modify_type<Op, T>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, gkey_type, auto...> struct T_cycle;

/***********************************************************************************************************************/

// names:

	struct CycleName
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			halt, next, lookup, loop,
			dimension
		};
	};

	using YN = CycleName;

/***********************************************************************************************************************/

// notes:

	struct CycleNote
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			first, select, assign, effect, car, cdr,
			dimension
		};
	};

	using YT = CycleNote;

/***********************************************************************************************************************/

// instructions:

	using YI = cctmp::Instr;

/***********************************************************************************************************************/

// dispatch:

	template<auto static_contr, auto _index = 0, auto _carop = _id_, auto _cdrop = _id_>
	struct CycleDispatch : public MachineDispatch<static_contr, YI, _index>
	{
		// defaults:

			nik_ces gindex_type initial_carop = _carop;
			nik_ces gindex_type initial_cdrop = _cdrop;
	};

	template<auto static_contr, auto _index = 0, auto _carop = _id_, auto _cdrop = _id_>
	using YD = CycleDispatch<static_contr, _index, _carop, _cdrop>;

/***********************************************************************************************************************/

// cons:

	template<auto c, auto i>
	struct T_cycle_cons
	{
		template<auto l, auto t, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto f = YD<c>::initial_carop;
			nik_ce auto g = YD<c>::initial_cdrop;

			return NIK_CYCLE_TS(c, i, f, g, l, t, Ts...)(vs...);
		}

	}; template<auto c, auto i>
		nik_ce auto U_cycle_cons = U_store_T<T_cycle_cons<c, i>>;

/***********************************************************************************************************************/

// start:

	struct T_cycle_start
	{
		template<auto c, auto l, auto t, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto i = YD<c>::initial_index;
			nik_ce auto f = YD<c>::initial_carop;
			nik_ce auto g = YD<c>::initial_cdrop;

			return NIK_CYCLE_TS(c, i, f, g, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_cycle<YN::halt, YT::first, filler...>
	{
		template<NIK_CYCLE_PARAMS(c, i, f, g, l, t), typename T0, typename... Ts>
		nik_ces auto result(T0 v0, Ts... vs) -> T0 { return v0; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// next:

/***********************************************************************************************************************/

// select:

	template<auto... filler>
	struct T_cycle<YN::next, YT::select, filler...>
	{
		template<NIK_CYCLE_PARAMS(c, i, f, g, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n  = YD<c>::pos(i);
			nik_ce auto p0 = eval<_par_left_ , n, U_store_T<Ts>...>;
			nik_ce auto p1 = eval<_par_right_, n, U_store_T<Ts>...>;

			return NIK_CYCLE_TEMPLATE(c, i), p0, p1
				NIK_CYCLE_RESULT_TS(c, i, f, g, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// assign:

	template
	<
		template<auto...> typename B0,         auto... LUs, nik_vp(p0)(B0<   LUs...>*),
		template<auto...> typename B1, auto U, auto... RUs, nik_vp(p1)(B1<U, RUs...>*)
	>
	struct T_cycle<YN::next, YT::assign, p0, p1>
	{
		using T = T_store_U<U>;

		template<NIK_CYCLE_PARAMS(c, i, f, g, l, t), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T v, T_store_U<RUs>... rvs)
		{
			using next_type  = modify_type<_to_pointer_, decltype(T_store_U<f>::template result<T>)>;
			nik_ce auto next = (next_type) T_store_U<f>::template result<T>; // c style cast.

			return NIK_CYCLE_3TS
				(c, i, f, g, l, t, T_store_U<LUs>..., T, T_store_U<RUs>...)(lvs..., next(v), rvs...);
		}
	};

/***********************************************************************************************************************/

// effect:

	template
	<
		template<auto...> typename B0,         auto... LUs, nik_vp(p0)(B0<   LUs...>*),
		template<auto...> typename B1, auto U, auto... RUs, nik_vp(p1)(B1<U, RUs...>*)
	>
	struct T_cycle<YN::next, YT::effect, p0, p1>
	{
		using T = T_store_U<U>;

		template<NIK_CYCLE_PARAMS(c, i, f, g, l, t), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T v, T_store_U<RUs>... rvs)
		{
			using next_type  = modify_type<_to_pointer_, decltype(T_store_U<f>::template result<T>)>;
			nik_ce auto next = (next_type) T_store_U<f>::template result<T>; // c style cast.

			next(v);

			return NIK_CYCLE_3TS
				(c, i, f, g, l, t, T_store_U<LUs>..., T, T_store_U<RUs>...)(lvs..., v, rvs...);
		}
	};

/***********************************************************************************************************************/

// car:

	template
	<
		template<auto...> typename B0,         auto... LUs, nik_vp(p0)(B0<   LUs...>*),
		template<auto...> typename B1, auto U, auto... RUs, nik_vp(p1)(B1<U, RUs...>*)
	>
	struct T_cycle<YN::next, YT::car, p0, p1>
	{
		using T = T_store_U<U>;

		template<NIK_CYCLE_PARAMS(c, i, f, g, l, t), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T v, T_store_U<RUs>... rvs)
		{
			nik_ce auto nf = U_restore_T<T>;

			return NIK_CYCLE_3TS
				(c, i, nf, g, l, t, T_store_U<LUs>..., T, T_store_U<RUs>...)(lvs..., v, rvs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lookup:

/***********************************************************************************************************************/

// car:

	template<template<auto...> typename B, auto... fs, nik_vp(env)(B<fs...>*)>
	struct T_cycle<YN::lookup, YT::car, env>
	{
		template<NIK_CYCLE_PARAMS(c, i, f, g, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni  = YD<c>::pos(i);
			nik_ce auto n   = YD<c>::num(i);
			nik_ce auto str = at_<l, n>;
			nik_ce auto nf  = T_lookup_istart::template result<c, ni, str>(fs...);

			return NIK_CYCLE_TS(c, i, nf, g, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// cdr:

	template<template<auto...> typename B, auto... fs, nik_vp(env)(B<fs...>*)>
	struct T_cycle<YN::lookup, YT::cdr, env>
	{
		template<NIK_CYCLE_PARAMS(c, i, f, g, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni  = YD<c>::pos(i);
			nik_ce auto n   = YD<c>::num(i);
			nik_ce auto str = at_<l, n>;
			nik_ce auto ng  = T_lookup_istart::template result<c, ni, str>(fs...);

			return NIK_CYCLE_TS(c, i, f, ng, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// loop:

/***********************************************************************************************************************/

// effect:

	template<auto... filler>
	struct T_cycle<YN::loop, YT::effect, filler...>
	{
		template<NIK_CYCLE_PARAMS(c, i, f, g, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			using pred_type  = modify_type<_to_pointer_, decltype(T_store_U<f>::template result<Ts...>)>;
			nik_ce auto pred = (pred_type) T_store_U<f>::template result<Ts...>; // c style cast.

			using func_type  = modify_type<_to_pointer_, decltype(T_store_U<g>::template result<Ts...>)>;
			nik_ce auto func = (func_type) T_store_U<g>::template result<Ts...>; // c style cast.

			while (pred(vs...)) func(vs...);

			return NIK_CYCLE_TS(c, i, f, g, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

