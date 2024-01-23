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

	template<typename T>
	using T_restore_T					= cctmp::T_restore_T<T>;

	template<template<auto...> typename B>
	nik_ce auto U_store_B					= cctmp::U_store_B<B>;

	nik_ce auto _zero					= cctmp::_zero;
	nik_ce auto _one					= cctmp::_one;

	nik_ce auto _to_list_					= cctmp::_to_list_;

	template<auto... Vs>
	nik_ce auto to_list_					= cctmp::to_list_<Vs...>;

	template<auto... Vs>
	nik_ce auto unpack_					= cctmp::unpack_<Vs...>;

	template<auto... Vs>
	nik_ce auto car_					= cctmp::car_<Vs...>;

	nik_ce auto _par_left_					= cctmp::_par_left_;
	nik_ce auto _par_right_					= cctmp::_par_right_;

	template<auto... Vs>
	nik_ce auto left_					= cctmp::left_<Vs...>;

	template<auto... Vs>
	nik_ce auto at_						= cctmp::at_<Vs...>;

	template<auto... Vs>
	nik_ce auto replace_					= cctmp::replace_<Vs...>;

	template<auto... Vs>
	nik_ce auto segment_					= cctmp::segment_<Vs...>;

	template<typename... Ts>
	using tuple						= cctmp::tuple<Ts...>;

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
			halt    , pad    ,
			go_to   , branch , invert ,
			literal , list   , lookup , arg  ,
			pound   , apply  , bind   , eval ,
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
			first , select ,
			front , back   ,
			push  , drop   ,
			verse , side   ,
			dimension
		};
	};

	using AT = AssemblyNote;

/***********************************************************************************************************************/

// instructions:

	using AI = cctmp::Instr;

/***********************************************************************************************************************/

// dispatch:

	template<auto static_contr, auto _index = 0>
	using AD = MachineDispatch<static_contr, AI, _index>;

/***********************************************************************************************************************/

// compound:

	template<auto c, auto i>
	struct T_assembly_compound
	{
		template<auto j, auto l, auto t, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, Ts...)
					(vs...);
		}

			// temporary ?
		template<auto s, auto j, auto l, auto t, typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, Ts...)
					(vs...);
		}

	}; template<auto... Vs>
		nik_ce auto U_assembly_compound = U_store_T<T_assembly_compound<Vs...>>;

	// syntactic sugar:

		nik_ce auto H_assembly_compound = U_store_B<T_assembly_compound>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_assembly<AN::halt, AT::first, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename T0, typename... Ts>
		nik_ces auto result(T0 v0, Ts... vs) -> T0
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
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n = AD<c>::pos(i);
			nik_ce auto p = segment_<n>;

			return NIK_ASSEMBLY_TEMPLATE_WS(c, i, p)
				::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// front:

	template<template<auto...> typename B, auto... Is, nik_vp(p)(B<Is...>*), auto... filler>
	struct T_assembly<AN::pad, AT::front, p, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, decltype(Is) const..., Ts...)
					(Is..., vs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template<template<auto...> typename B, auto... Is, nik_vp(p)(B<Is...>*), auto... filler>
	struct T_assembly<AN::pad, AT::back, p, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, Ts..., decltype(Is) const...)
					(vs..., Is...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// go to:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::go_to, AT::id, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);

			return NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_TS(c, ni, j, l, t, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// branch:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::branch, AT::id, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);

			if (v) return NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_2TS(c, ni, j, l, t, T, Ts...)
					(v, vs...);

			else   return NIK_ASSEMBLY_TEMPLATE(c,  i)
				::NIK_ASSEMBLY_RESULT_2TS(c,  i, j, l, t, T, Ts...)
					(v, vs...);
		}
	};

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// invert:

/***********************************************************************************************************************/

// id:

/*
	template<auto... filler>
	struct T_assembly<AN::invert, AT::id, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);

			if (v) return NIK_ASSEMBLY_TEMPLATE(c,  i)
				::NIK_ASSEMBLY_RESULT_2TS(c,  i, j, l, t, T, Ts...)
					(v, vs...);

			else   return NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_2TS(c, ni, j, l, t, T, Ts...)
					(v, vs...);
		}
	};
*/

/***********************************************************************************************************************/

// :

	template<auto... filler>
	struct T_assembly<AN::invert, AT::id, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);

			if (v) return NIK_ASSEMBLY_TEMPLATE(c,  i)
					::NIK_ASSEMBLY_RESULT_2TS(c,  i, j, l, t, T, Ts...)(v, vs...);
			else
			{
				using ante_type = decltype
				(
					NIK_ASSEMBLY_TEMPLATE(c,  i)
						::NIK_ASSEMBLY_RESULT_2TS(c,  i, j, l, t, T, Ts...)(v, vs...)
				);

				return static_cast<ante_type>
				(
					NIK_ASSEMBLY_TEMPLATE(c, ni)
						::NIK_ASSEMBLY_RESULT_2TS(c, ni, j, l, t, T, Ts...)
							(v, vs...)
				);
			}
		}
	};

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// literal:

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_assembly<AN::literal, AT::first, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto n  = AD<c>::num(i);
			nik_ce auto s  = at_<j, n>;
			nik_ce auto nv = T_literal_compound<s, c>::template result<ni>();

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, decltype(nv), Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template<auto... filler>
	struct T_assembly<AN::literal, AT::back, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto n  = AD<c>::num(i);
			nik_ce auto s  = at_<j, n>;
			nik_ce auto nv = T_literal_compound<s, c>::template result<ni>();

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, Ts..., decltype(nv))
					(vs..., nv);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// list:

/***********************************************************************************************************************/

// select:

	template<auto... filler>
	struct T_assembly<AN::list, AT::select, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n = AD<c>::pos(i);
			nik_ce auto p = at_<j, n>;

			return NIK_ASSEMBLY_TEMPLATE_WS(c, i, p)
				::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template<auto... filler>
	struct T_assembly<AN::list, AT::back, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n  = AD<c>::pos(i);
			nik_ce auto nv = at_<j, n>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, Ts..., decltype(nv))
					(vs..., nv);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lookup:

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_assembly<AN::lookup, AT::first, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto   n  = AD<c>::pos(i);
			nik_ce auto   m  = AD<c>::num(i);
			nik_ce auto & t0 = member_value_U<l>;
			nik_ce auto & t1 = t0.template cvalue<n>();
			nik_ce auto   nv = t1.template cvalue<m>();

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, decltype(nv), Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template<auto... filler>
	struct T_assembly<AN::lookup, AT::back, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto   n  = AD<c>::pos(i);
			nik_ce auto   m  = AD<c>::num(i);
			nik_ce auto & t0 = member_value_U<l>;
			nik_ce auto & t1 = t0.template cvalue<n>();
			nik_ce auto   nv = t1.template cvalue<m>();

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, Ts..., decltype(nv))
					(vs..., nv);
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
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n  = AD<c>::pos(i);
			nik_ce auto p0 = eval<_par_left_ , n, U_store_T<Ts>...>;
			nik_ce auto p1 = eval<_par_right_, n, U_store_T<Ts>...>;

			return NIK_ASSEMBLY_TEMPLATE_2WS(c, i, p0, p1)
				::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// verse:

	template<auto... filler>
	struct T_assembly<AN::arg, AT::verse, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n  = AD<c>::pos(i);
			nik_ce auto m  = AD<c>::num(i);
			nik_ce auto p  = eval<_par_left_ , m, U_store_T<Ts>...>;
			nik_ce auto p0 = unpack_<p, _par_left_, n>;
			nik_ce auto p1 = unpack_<p, _par_right_, n>;
			nik_ce auto p2 = eval<_par_right_, m, U_store_T<Ts>...>;

			return NIK_ASSEMBLY_TEMPLATE_3WS(c, i, p0, p1, p2)
				::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, Ts...)
					(vs...);
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
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<RUs>... rvs)
		{
			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, T_store_U<RUs>...)
					(rvs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (com)pound:

/***********************************************************************************************************************/

// back:

	template<auto... filler>
	struct T_assembly<AN::pound, AT::back, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto nv = U_assembly_compound<c, ni>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, Ts..., decltype(nv))
					(vs..., nv);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// apply:

/***********************************************************************************************************************/

// first:

	template
	<
		template<auto...> typename B0, auto LU, auto... LUs, nik_vp(p0)(B0<LU, LUs...>*),
		template<auto...> typename B1, auto RU, auto... RUs, nik_vp(p1)(B1<RU, RUs...>*)
	>
	struct T_assembly<AN::apply, AT::first, p0, p1>
	{
		using LT = T_store_U<LU>;
		using RT = T_store_U<RU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(LT lv, T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs)
		{
			       auto nv = T_restore_T<RT>::template result<T_store_U<RUs>...>(rvs...);

			nik_ce auto nU = U_store_T<decltype(nv)>;
			using nT       = read_only<nU>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, nT, T_store_U<LUs>...)
					(nv, lvs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template
	<
		template<auto...> typename B0,          auto... LUs, nik_vp(p0)(B0<    LUs...>*),
		template<auto...> typename B1, auto RU, auto... RUs, nik_vp(p1)(B1<RU, RUs...>*)
	>
	struct T_assembly<AN::apply, AT::back, p0, p1>
	{
		using RT = T_store_U<RU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs)
		{
			       auto nv = T_restore_T<RT>::template result<T_store_U<RUs>...>(rvs...);

			nik_ce auto nU = U_store_T<decltype(nv)>;
			using nT       = read_only<nU>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, T_store_U<LUs>..., nT)
					(lvs..., nv);
		}
	};

/***********************************************************************************************************************/

// side:

	template
	<
		template<auto...> typename B0,          auto... LUs, nik_vp(p0)(B0<    LUs...>*),
		template<auto...> typename B1, auto RU, auto... RUs, nik_vp(p1)(B1<RU, RUs...>*)
	>
	struct T_assembly<AN::apply, AT::side, p0, p1>
	{
		using RT = T_store_U<RU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs)
		{
			T_restore_T<RT>::template result<T_store_U<RUs>...>(rvs...);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, T_store_U<LUs>...)
					(lvs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// bind:

/***********************************************************************************************************************/

// first:

	template
	<
		template<auto...> typename B0, auto LU, auto... LUs, nik_vp(p0)(B0<LU, LUs...>*),
		template<auto...> typename B1,          auto... MUs, nik_vp(p1)(B1<    MUs...>*),
		template<auto...> typename B2, auto RU, auto... RUs, nik_vp(p2)(B2<RU, RUs...>*)
	>
	struct T_assembly<AN::bind, AT::first, p0, p1, p2>
	{
		using LT = T_store_U<LU>;
		using RT = T_store_U<RU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(LT lv, T_store_U<LUs>... lvs, T_store_U<MUs>... mvs, RT rv, T_store_U<RUs>... rvs)
		{
			nik_ce auto n  = AD<c>::num(i);
			nik_ce auto s  = cctmp::U_gindex_type; // temporary.
			       auto nv = T_restore_T<RT>::template
					 	result<s, j, l, t, LT, T_store_U<LUs>..., T_store_U<RUs>...>
							(lv, lvs..., rvs...);

			nik_ce auto nU = U_store_T<decltype(nv)>;
			using nT       = read_only<nU>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_3TS(c, i, j, l, t, nT, T_store_U<LUs>..., T_store_U<MUs>...)
					(nv, lvs..., mvs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template
	<
		template<auto...> typename B0,          auto... LUs, nik_vp(p0)(B0<    LUs...>*),
		template<auto...> typename B1,          auto... MUs, nik_vp(p1)(B1<    MUs...>*),
		template<auto...> typename B2, auto RU, auto... RUs, nik_vp(p2)(B2<RU, RUs...>*)
	>
	struct T_assembly<AN::bind, AT::back, p0, p1, p2>
	{
		using RT = T_store_U<RU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<MUs>... mvs, RT rv, T_store_U<RUs>... rvs)
		{
			nik_ce auto n  = AD<c>::num(i);
			nik_ce auto s  = cctmp::U_gindex_type; // temporary.
			       auto nv = T_restore_T<RT>::template
					 	result<s, j, l, t, T_store_U<LUs>..., T_store_U<RUs>...>
							(lvs..., rvs...);

			nik_ce auto nU = U_store_T<decltype(nv)>;
			using nT       = read_only<nU>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_3TS(c, i, j, l, t, T_store_U<LUs>..., T_store_U<MUs>..., nT)
					(lvs..., mvs..., nv);
		}
	};

/***********************************************************************************************************************/

// side:

	template
	<
		template<auto...> typename B0,          auto... LUs, nik_vp(p0)(B0<    LUs...>*),
		template<auto...> typename B1,          auto... MUs, nik_vp(p1)(B1<    MUs...>*),
		template<auto...> typename B2, auto RU, auto... RUs, nik_vp(p2)(B2<RU, RUs...>*)
	>
	struct T_assembly<AN::bind, AT::side, p0, p1, p2>
	{
		using RT = T_store_U<RU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<MUs>... mvs, RT rv, T_store_U<RUs>... rvs)
		{
			nik_ce auto n = AD<c>::num(i);

			T_restore_T<RT>::template
			 	result<j, l, t, T_store_U<LUs>..., T_store_U<RUs>...>
					(lvs..., rvs...);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, T_store_U<LUs>..., T_store_U<MUs>...)
					(lvs..., mvs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// eval:

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_assembly<AN::eval, AT::first, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);
			       auto nv = NIK_ASSEMBLY_TEMPLATE(c, ni)
			       			::NIK_ASSEMBLY_RESULT_2TS(c, ni, j, l, t, T, Ts...)(v, vs...);

			nik_ce auto nU = U_store_T<decltype(nv)>;
			using nT       = read_only<nU>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, nT, Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template<auto... filler>
	struct T_assembly<AN::eval, AT::back, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);
			       auto nv = NIK_ASSEMBLY_TEMPLATE(c, ni)
			       			::NIK_ASSEMBLY_RESULT_TS(c, ni, j, l, t, Ts...)(vs...);

			nik_ce auto nU = U_store_T<decltype(nv)>;
			using nT       = read_only<nU>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, Ts..., nT)
					(vs..., nv);
		}
	};

/***********************************************************************************************************************/

// side:

	template<auto... filler>
	struct T_assembly<AN::eval, AT::side, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);

			NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_TS(c, ni, j, l, t, Ts...)(vs...);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace machine

