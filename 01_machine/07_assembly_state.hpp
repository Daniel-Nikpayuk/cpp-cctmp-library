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
	nik_ce auto push_					= cctmp::push_<Vs...>;

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
			halt  , pad   , jump    ,
			arg   , list  , lookup  , 
			chain , right , replace ,
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
			first   , segment  ,
			go_to   , branch   ,
			recurse ,
			select  ,
			call_f  , void_f   ,
			cons_f  ,
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
	struct AssemblyDispatch : public MachineDispatch<static_contr, AI, _index>
	{
		// defaults:

			nik_ces gindex_type initial_count = _count;
	};

	template<auto static_contr, auto _index = 0, auto _count = 0>
	using AD = AssemblyDispatch<static_contr, _index, _count>;

/***********************************************************************************************************************/

// cons:

	template<auto s, auto c, auto i>
	struct T_assembly_cons
	{
		template<auto l, auto t, typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto j = AD<c>::initial_count;

			return NIK_ASSEMBLY_TS(s, c, i, j, l, t, Ts...)(vs...);
		}

	}; template<auto s, auto c, auto i>
		nik_ce auto U_assembly_cons = U_store_T<T_assembly_cons<s, c, i>>;

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

	template<template<auto...> typename B, auto I0, auto... Is, nik_vp(p)(B<I0, Is...>*)>
	struct T_assembly<AN::pad, AT::id, p>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto rt = push_<t, U_store_T<decltype(Is)>...>;
			nik_ce auto nt = cons_<rt, U_store_T<decltype(I0)>>;

			return NIK_ASSEMBLY_3TS
				(s, c, i, j, l, nt, decltype(I0), Ts..., decltype(Is)...)
					(I0, vs..., Is...);
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

			if (v) return NIK_ASSEMBLY_2TS(s, c, ni, j, l, t, T, Ts...)(v, vs...);
			else   return NIK_ASSEMBLY_2TS(s, c,  i, j, l, t, T, Ts...)(v, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// arg:

/***********************************************************************************************************************/

// select:

	template<auto... filler>
	struct T_assembly<AN::arg, AT::select, filler...>
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
/***********************************************************************************************************************/

// list:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::list, AT::id, filler...>
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

// recurse:

	template<auto... filler>
	struct T_assembly<AN::list, AT::recurse, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto n  = AD<c>::pos(i);
			nik_ce auto nv = at_<l, n>;

			nik_ce auto nU = U_store_T<decltype(nv)>;
			nik_ce auto nt = cons_<t, nU>;
			using nT       = modify_type<_read_only_, decltype(nv)>;

			return NIK_ASSEMBLY_2TS(s, c, i, j, l, nt, nT, Ts...)(nv, vs...);
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
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ni  = AD<c>::pos(i);
			nik_ce auto n   = AD<c>::num(i);
			nik_ce auto str = at_<l, n>;
			nik_ce auto nv  = T_lookup_istart::template result<c, ni, str>(fs...);

			nik_ce auto nU  = U_store_T<decltype(nv)>;
			nik_ce auto nt  = replace_<t, _zero, nU>;
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
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ni = AD<c>::pos(i);
			       auto nv = T_chain_istart::template result<c, ni, l, t>(v, vs...);

			nik_ce auto nU = U_store_T<decltype(nv)>;
			nik_ce auto nt = replace_<t, _zero, nU>;
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

// cons_f:

	template<auto... filler>
	struct T_assembly<AN::chain, AT::cons_f, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto nv = U_chain_cons<c, ni>;

			nik_ce auto nU = U_store_T<decltype(nv)>;
			nik_ce auto nt = replace_<t, _zero, nU>;
			using nT       = modify_type<_read_only_, decltype(nv)>;

			return NIK_ASSEMBLY_2TS(s, c, i, j, l, nt, nT, Ts...)(nv, vs...);
		}
	};

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
			nik_ce auto nt = replace_<t, sizeof...(LUs) + 1, t0>;

			return NIK_ASSEMBLY_4TS
				(s, c, i, j, l, nt, LT, T_store_U<LUs>..., LT, T_store_U<RUs>...)
					(lv, lvs..., lv, rvs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

