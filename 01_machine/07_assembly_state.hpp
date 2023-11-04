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

// assembly state:

namespace machine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	nik_ce auto _zero					= cctmp::_zero;
	nik_ce auto _one					= cctmp::_one;

	template<auto... Vs>
	nik_ce auto to_list_					= cctmp::to_list_<Vs...>;

	template<auto... Vs>
	nik_ce auto car_					= cctmp::car_<Vs...>;

	template<auto... Vs>
	nik_ce auto cons_					= cctmp::cons_<Vs...>;

	template<auto... Vs>
	nik_ce auto right_					= cctmp::right_<Vs...>;

	template<auto... Vs>
	nik_ce auto replace_					= cctmp::replace_<Vs...>;

	template<auto... Vs>
	nik_ce auto segment_					= cctmp::segment_<Vs...>;

	nik_ce auto _read_only_					= cctmp::_read_only_;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, gkey_type, auto...> struct T_assembly;

/***********************************************************************************************************************/

// names:

	struct AssemblyName
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			halt   , pad      , jump ,
			select , reselect ,
			lookup , 
			chain  , rechain  ,
			right  , replace  ,
			dimension
		};
	};

	using AN = AssemblyName;

/***********************************************************************************************************************/

// notes:

	struct AssemblyNote
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			first, segment, go_to, branch, list, call_f, void_f,
			dimension
		};
	};

	using AT = AssemblyNote;

/***********************************************************************************************************************/

// instructions:

	using AI = cctmp::Instr;

/***********************************************************************************************************************/

// dispatch:

	template<auto static_contr, auto _index = 0, auto _count = 0>
	struct AssemblyDispatch
	{
		nik_ces auto & contr = member_value_U<static_contr>;
		using cindex         = gcindex_type;

		// defaults:

			nik_ces gindex_type initial_index = _index;
			nik_ces gindex_type initial_count = _count;

		// accessors:

			nik_ces const auto & instr(cindex i) { return contr[i]; }
			nik_ces gindex_type value(cindex i, cindex n) { return contr[i][n]; }

			nik_ces gindex_type pos (cindex i) { return value(i, AI::pos); }
			nik_ces gindex_type num (cindex i) { return value(i, AI::num); }

		// navigators:

			nik_ces gindex_type next_offset (cindex i) { return value(i, AI::next); }
			nik_ces gindex_type next_index  (cindex i) { return i + next_offset(i); }

			nik_ces gkey_type next_name (cindex i) { return value(next_index(i), AI::name); }
			nik_ces gkey_type next_note (cindex i) { return value(next_index(i), AI::note); }
	};

	template<auto static_contr, auto _index = 0, auto _count = 0>
	using AD = AssemblyDispatch<static_contr, _index, _count>;

/***********************************************************************************************************************/

// start:

	struct T_assembly_start
	{
		template<auto s, auto c, auto l, auto t, typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto i = AD<c>::initial_index;
			nik_ce auto j = AD<c>::initial_count;

			return NIK_ASSEMBLY_TS(s, c, i, j, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_assembly<AN::halt, AT::first, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename T0, typename... Ts>
		nik_ces auto result(T0 v0, Ts... vs) -> T_store_U<s> { return v0; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pad:

/***********************************************************************************************************************/

// segment:

	template<auto... filler>
	struct T_assembly<AN::pad, AT::segment, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto n = AD<c>::pos(i);
			nik_ce auto p = segment_<n>;

			return NIK_ASSEMBLY_TEMPLATE(c, i), p
				NIK_ASSEMBLY_RESULT_TS(s, c, i, j, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// id:

	template<template<auto...> typename B, auto... Is, nik_vp(p)(B<Is...>*)>
	struct T_assembly<AN::pad, AT::id, p>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto nt = cons_<t, U_store_T<decltype(Is)>...>;

			return NIK_ASSEMBLY_2TS(s, c, i, j, l, nt, Ts..., decltype(Is)...)(vs..., Is...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// jump:

/***********************************************************************************************************************/

// go to:

	template<auto... filler>
	struct T_assembly<AN::jump, AT::go_to, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ni = AD<c>::pos(i);

			return NIK_ASSEMBLY_TS(s, c, ni, j, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// branch:

	template<auto... filler>
	struct T_assembly<AN::jump, AT::branch, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto nt = right_<t, _one>;

			if (v) return NIK_ASSEMBLY_TS(s, c, ni, j, l, nt, Ts...)(vs...);
			else   return NIK_ASSEMBLY_TS(s, c,  i, j, l, nt, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// select:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::select, AT::id, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto n  = AD<c>::pos(i);
			nik_ce auto p0 = eval<_par_left_ , n, U_store_T<Ts>...>;
			nik_ce auto p1 = eval<_par_right_, n, U_store_T<Ts>...>;

			return NIK_ASSEMBLY_TEMPLATE(c, i), p0, p1
				NIK_ASSEMBLY_RESULT_TS(s, c, i, j, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// list:

	template<auto... filler>
	struct T_assembly<AN::select, AT::list, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto n = AD<c>::pos(i);
			nik_ce auto p = at_<l, n>;

			return NIK_ASSEMBLY_TEMPLATE(c, i), p
				NIK_ASSEMBLY_RESULT_TS(s, c, i, j, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// reselect:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::reselect, AT::id, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto n  = AD<c>::pos(i);
			nik_ce auto p0 = eval<_par_left_ , n+1, U_store_T<T>, U_store_T<Ts>...>;
			nik_ce auto p1 = eval<_par_right_, n, U_store_T<Ts>...>;

			return NIK_ASSEMBLY_TEMPLATE(c, i), p0, p1
				NIK_ASSEMBLY_RESULT_2TS(s, c, i, j, l, t, T, Ts...)(v, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lookup:

/***********************************************************************************************************************/

// call_f:

	template<template<auto...> typename B, auto... fs, nik_vp(env)(B<fs...>*)>
	struct T_assembly<AN::lookup, AT::call_f, env>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ni  = AD<c>::pos(i);
			nik_ce auto n   = AD<c>::num(i);
			nik_ce auto str = at_<l, n>;
			nik_ce auto nv  = T_lookup_istart::template result<c, ni, str>(fs...);

			nik_ce auto nU  = U_store_T<decltype(nv)>;
			nik_ce auto nt  = cons_<t, nU>;
			using nT        = modify_type<_read_only_, decltype(nv)>;

			return NIK_ASSEMBLY_2TS(s, c, i, j, l, nt, nT, Ts...)(nv, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// chain:

/***********************************************************************************************************************/

// call_f:

	template<auto... filler>
	struct T_assembly<AN::chain, AT::call_f, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ni = AD<c>::pos(i);
			       auto nv = T_chain_istart::template result<c, ni, l, t>(vs...);

			nik_ce auto nU = U_store_T<decltype(nv)>;
			nik_ce auto nt = cons_<t, nU>;
			using nT       = modify_type<_read_only_, decltype(nv)>;

			return NIK_ASSEMBLY_2TS(s, c, i, j, l, nt, nT, Ts...)(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// void_f:

	template<auto... filler>
	struct T_assembly<AN::chain, AT::void_f, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ni = AD<c>::pos(i);

			T_chain_istart::template result<c, ni, l, t>(vs...);

			return NIK_ASSEMBLY_TS(s, c, i, j, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// rechain:

/***********************************************************************************************************************/

// call_f:

	template<auto... filler>
	struct T_assembly<AN::rechain, AT::call_f, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ni = AD<c>::pos(i);
			       auto nv = T_chain_istart::template result<c, ni, l, t>(v, vs...);

			nik_ce auto nU = U_store_T<decltype(nv)>;
			nik_ce auto nt = cons_<t, nU>;
			using nT       = modify_type<_read_only_, decltype(nv)>;

			return NIK_ASSEMBLY_2TS(s, c, i, j, l, nt, nT, Ts...)(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// void_f:

	template<auto... filler>
	struct T_assembly<AN::rechain, AT::void_f, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ni = AD<c>::pos(i);

			T_chain_istart::template result<c, ni, l, t>(v, vs...);

			return NIK_ASSEMBLY_TS(s, c, i, j, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// call:

/***********************************************************************************************************************/

// id:

//	template<auto... filler>
//	struct T_assembly<AN::call, AT::id, filler...>
//	{
//		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename... Ts>
//		nik_ces auto result(Ts... vs) -> T_store_U<s>
//		{
//			nik_ce auto n  = AD<c>::pos(i);
//			nik_ce auto F  = T_store_U<j>::template result<n, l, t>();

//			using f_type   = modify_type<_to_pointer_, decltype(T_store_U<F>::template result<Ts...>)>;
//			nik_ce auto f  = (f_type) T_store_U<F>::template result<Ts...>; // c style cast.
//			nik_ce auto OT = eval<_function_out_type_, f>;
//			nik_ce auto nt = cons_<t, OT>;
//			using v_type   = modify_type<_read_only_, T_store_U<OT>>;

//			return NIK_ASSEMBLY_2TS(s, c, i, j, l, nt, v_type, Ts...)(f(vs...), vs...);
//		}
//	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// right:

/***********************************************************************************************************************/

// id:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto... RUs, nik_vp(p1)(B1<RUs...>*)
	>
	struct T_assembly<AN::right, AT::id, p0, p1>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<RUs>... rvs) -> T_store_U<s>
		{
			nik_ce auto nt = right_<t, sizeof...(LUs)>;

			return NIK_ASSEMBLY_TS(s, c, i, j, l, nt, T_store_U<RUs>...)(rvs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// replace:

/***********************************************************************************************************************/

// id:

	template
	<
		template<auto...> typename B0, auto LU, auto... LUs, nik_vp(p0)(B0<LU, LUs...>*),
		template<auto...> typename B1, auto RU, auto... RUs, nik_vp(p1)(B1<RU, RUs...>*)
	>
	struct T_assembly<AN::replace, AT::id, p0, p1>
	{
		using LT = T_store_U<LU>;
		using RT = T_store_U<RU>;

		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename... Ts>
		nik_ces auto result(LT lv, T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs) -> T_store_U<s>
		{
			nik_ce auto t0 = car_<t>;
			nik_ce auto rt = right_<t, _one>;
			nik_ce auto nt = replace_<rt, sizeof...(LUs), t0>;

			return NIK_ASSEMBLY_3TS
				(s, c, i, j, l, nt, T_store_U<LUs>..., LT, T_store_U<RUs>...)(lvs..., lv, rvs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

