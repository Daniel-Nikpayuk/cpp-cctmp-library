/************************************************************************************************************************
**
** Copyright 2022-2024 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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
	nik_ce auto replace_					= cctmp::replace_<Vs...>;

	template<auto... Vs>
	nik_ce auto segment_					= cctmp::segment_<Vs...>;

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
			halt , pad       ,
			arg  , list      ,
			jump , sub_chain , sub_asm ,
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
			first   , select  ,
			front   , back    ,
			pull    , push    ,
			drop    , replace ,
			go_to   , branch  , invert ,
			call_f  , void_f  ,
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

// compound:

	// global:

		template<auto c>
		struct T_assembly_compound<c>
		{
			template<auto s, auto i, auto j, auto l, auto t, typename... Ts>
			nik_ces auto result(Ts... vs) -> T_store_U<s>
				{ return NIK_ASSEMBLY_TS(s, c, i, j, l, t, Ts...)(vs...); }

			template<auto s, auto i, auto l, auto t, typename... Ts>
			nik_ces auto result(Ts... vs) -> T_store_U<s>
			{
				nik_ce auto j = AD<c>::initial_count;

				return result<s, i, j, l, t, Ts...>(vs...);
			}

			template<auto s, auto l, auto t, typename... Ts>
			nik_ces auto result(Ts... vs) -> T_store_U<s>
			{
				nik_ce auto i = AD<c>::initial_index;
				nik_ce auto j = AD<c>::initial_count;

				return result<s, i, j, l, t, Ts...>(vs...);
			}
		};

	// local:

		template<auto c, auto i>
		struct T_assembly_compound<c, i>
		{
			nik_ces auto j = AD<c>::initial_count;

			template<auto s, auto l, auto t, typename... Ts>
			nik_ces auto result(Ts... vs) -> T_store_U<s>
				{ return NIK_ASSEMBLY_TS(s, c, i, j, l, t, Ts...)(vs...); }
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
		nik_ces auto result(T0 v0, Ts... vs) -> T_store_U<s>
			{ return v0; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pad:

/***********************************************************************************************************************/

// select:

	template<auto... filler>
	struct T_assembly<AN::pad, AT::select, filler...>
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

// front:

	template<template<auto...> typename B, auto... Is, nik_vp(p)(B<Is...>*)>
	struct T_assembly<AN::pad, AT::front, p>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto nt = cons_<t, U_store_T<decltype(Is)>...>;

			return NIK_ASSEMBLY_2TS
				(s, c, i, j, l, nt, decltype(Is)..., Ts...)
					(Is..., vs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template<template<auto...> typename B, auto... Is, nik_vp(p)(B<Is...>*)>
	struct T_assembly<AN::pad, AT::back, p>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto nt = push_<t, U_store_T<decltype(Is)>...>;

			return NIK_ASSEMBLY_2TS
				(s, c, i, j, l, nt, Ts..., decltype(Is)...)
					(vs..., Is...);
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

// drop:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto... RUs, nik_vp(p1)(B1<RUs...>*)
	>
	struct T_assembly<AN::arg, AT::drop, p0, p1>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<RUs>... rvs) -> T_store_U<s>
		{
			nik_ce auto nt = right_<t, sizeof...(LUs)>;

			return NIK_ASSEMBLY_TS(s, c, i, j, l, nt, T_store_U<RUs>...)(rvs...);
		}
	};

/***********************************************************************************************************************/

// replace:

	template
	<
		template<auto...> typename B0, auto LU, auto... LUs, nik_vp(p0)(B0<LU, LUs...>*),
		template<auto...> typename B1, auto RU, auto... RUs, nik_vp(p1)(B1<RU, RUs...>*)
	>
	struct T_assembly<AN::arg, AT::replace, p0, p1>
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

// list:

/***********************************************************************************************************************/

// push:

	template<auto... filler>
	struct T_assembly<AN::list, AT::push, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto n  = AD<c>::pos(i);
			nik_ce auto nj = at_<l, n>;

			return NIK_ASSEMBLY_TS(s, c, i, nj, l, t, Ts...)(vs...);
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

// invert:

	template<auto... filler>
	struct T_assembly<AN::jump, AT::invert, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ni = AD<c>::pos(i);

			if (v) return NIK_ASSEMBLY_2TS(s, c,  i, j, l, t, T, Ts...)(v, vs...);
			else   return NIK_ASSEMBLY_2TS(s, c, ni, j, l, t, T, Ts...)(v, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sub chain:

/***********************************************************************************************************************/

// call_f:

	template<auto... filler>
	struct T_assembly<AN::sub_chain, AT::call_f, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ni = AD<c>::pos(i);
			       auto nv = T_chain_compound<c>::template result<ni, l, t, T, Ts...>(v, vs...);

			nik_ce auto nU = U_store_T<decltype(nv)>;
			nik_ce auto nt = replace_<t, _zero, nU>;
			using nT       = read_only<nU>;

			return NIK_ASSEMBLY_2TS(s, c, i, j, l, nt, nT, Ts...)(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// void_f:

	template<auto... filler>
	struct T_assembly<AN::sub_chain, AT::void_f, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ni = AD<c>::pos(i);

			T_chain_compound<c>::template result<ni, l, t, Ts...>(vs...);

			return NIK_ASSEMBLY_TS(s, c, i, j, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sub as(se)m(bly):

/***********************************************************************************************************************/

// call_f:

	template<auto... filler>
	struct T_assembly<AN::sub_asm, AT::call_f, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ni = AD<c>::pos(i);
			       auto nv = T_assembly_compound<c>::template result<s, ni, l, t, T, Ts...>(v, vs...);

			nik_ce auto nU = U_store_T<decltype(nv)>;
			nik_ce auto nt = replace_<t, _zero, nU>;
			using nT       = read_only<nU>;

			return NIK_ASSEMBLY_2TS(s, c, i, j, l, nt, nT, Ts...)(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// void_f:

	template<auto... filler>
	struct T_assembly<AN::sub_asm, AT::void_f, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ni = AD<c>::pos(i);

			T_assembly_compound<c>::template result<s, ni, l, t, Ts...>(vs...);

			return NIK_ASSEMBLY_TS(s, c, i, j, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

