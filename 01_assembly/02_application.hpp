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

// application:

namespace assembly {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pad:

/***********************************************************************************************************************/

// select:

	template<auto... filler>
	struct T_assembly<AN::pad, AT::select, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n  = AD<c>::pos(i);
			nik_ce auto m  = AD<c>::num(i);
			nik_ce auto p0 = eval<_par_left_ , n, U_store_T<Ts>...>;
			nik_ce auto p1 = eval<_par_right_, n, U_store_T<Ts>...>;
			nik_ce auto p2 = segment_<m>;

			return NIK_ASSEMBLY_TEMPLATE_3WS(c, i, p0, p1, p2)
				::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, r, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// id:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto... RUs, nik_vp(p1)(B1<RUs...>*),
		template<auto...> typename B2, auto...  Is, nik_vp(p2)(B2< Is...>*),
		auto... filler
	>
	struct T_assembly<AN::pad, AT::id, p0, p1, p2, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<RUs>... rvs)
		{
			return NIK_ASSEMBLY_TEMPLATE(c, i)::NIK_ASSEMBLY_RESULT_3TS
				(c, i, j, l, t, r, T_store_U<LUs>..., decltype(Is) const..., T_store_U<RUs>...)
					(lvs..., Is..., rvs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// hash:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::hash, AT::id, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto nv = U_assembly_compound<c, ni>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, decltype(nv), Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// port:

	template<auto... filler>
	struct T_assembly<AN::hash, AT::port, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto n  = AD<c>::num(i);
			nik_ce auto s  = at_<t, n>;
			nik_ce auto nv = U_assembly_compound<s, c, ni>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, decltype(nv), Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (com)pound:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::pound, AT::id, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto nv = U_assembly_compound<c, ni>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, Ts..., decltype(nv))
					(vs..., nv);
		}
	};

/***********************************************************************************************************************/

// port:

	template<auto... filler>
	struct T_assembly<AN::pound, AT::port, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto n  = AD<c>::num(i);
			nik_ce auto s  = at_<t, n>;
			nik_ce auto nv = U_assembly_compound<s, c, ni>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, Ts..., decltype(nv))
					(vs..., nv);
		}
	};

/***********************************************************************************************************************/

// pull:

/*
	template<auto... filler>
	struct T_assembly<AN::pound, AT::pull, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto s  = at_<t, r>;
			nik_ce auto nv = U_assembly_compound<s, c, ni>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, Ts..., decltype(nv))
					(vs..., nv);
		}
	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// eval:

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_assembly<AN::eval, AT::first, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto n  = AD<c>::num(i);
			       auto nv = NIK_ASSEMBLY_TEMPLATE(c, ni)
			       			::NIK_ASSEMBLY_RESULT_2TS(c, ni, j, l, t, r, T, Ts...)
							(v, vs...);

			using nT = decltype(nv);
			using mT = read_type<n, nT>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, mT, Ts...)
					(static_cast<mT>(nv), vs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template<auto... filler>
	struct T_assembly<AN::eval, AT::back, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto n  = AD<c>::num(i);
			       auto nv = NIK_ASSEMBLY_TEMPLATE(c, ni)
			       			::NIK_ASSEMBLY_RESULT_TS(c, ni, j, l, t, r, Ts...)
							(vs...);

			using nT = decltype(nv);
			using mT = read_type<n, nT>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, Ts..., mT)
					(vs..., static_cast<mT>(nv));
		}
	};

/***********************************************************************************************************************/

// side:

	template<auto... filler>
	struct T_assembly<AN::eval, AT::side, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);

			NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_TS(c, ni, j, l, t, r, Ts...)
					(vs...);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, r, Ts...)
					(vs...);
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
		template<auto...> typename B1, auto RU, auto... RUs, nik_vp(p1)(B1<RU, RUs...>*),
		auto... filler
	>
	struct T_assembly<AN::apply, AT::first, p0, p1, filler...>
	{
		using LT = T_store_U<LU>;
		using RT = T_store_U<RU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(LT lv, T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs)
		{
			auto  nv = T_restore_T<RT>::template result<T_store_U<RUs>...>(rvs...);
			using nT = decltype(nv);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, nT, T_store_U<LUs>...)
					(nv, lvs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template
	<
		template<auto...> typename B0,          auto... LUs, nik_vp(p0)(B0<    LUs...>*),
		template<auto...> typename B1, auto RU, auto... RUs, nik_vp(p1)(B1<RU, RUs...>*),
		auto... filler
	>
	struct T_assembly<AN::apply, AT::back, p0, p1, filler...>
	{
		using RT = T_store_U<RU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs)
		{
			auto  nv = T_restore_T<RT>::template result<T_store_U<RUs>...>(rvs...);
			using nT = decltype(nv);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, T_store_U<LUs>..., nT)
					(lvs..., nv);
		}
	};

/***********************************************************************************************************************/

// side:

	template
	<
		template<auto...> typename B0,          auto... LUs, nik_vp(p0)(B0<    LUs...>*),
		template<auto...> typename B1, auto RU, auto... RUs, nik_vp(p1)(B1<RU, RUs...>*),
		auto... filler
	>
	struct T_assembly<AN::apply, AT::side, p0, p1, filler...>
	{
		using RT = T_store_U<RU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs)
		{
			T_restore_T<RT>::template result<T_store_U<RUs>...>(rvs...);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, r, T_store_U<LUs>...)
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
		template<auto...> typename B2, auto RU, auto... RUs, nik_vp(p2)(B2<RU, RUs...>*),
		auto... filler
	>
	struct T_assembly<AN::bind, AT::first, p0, p1, p2, filler...>
	{
		using LT = T_store_U<LU>;
		using RT = T_store_U<RU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(LT lv, T_store_U<LUs>... lvs, T_store_U<MUs>... mvs, RT rv, T_store_U<RUs>... rvs)
		{
			auto  nv = T_restore_T<RT>::template
					result<j, l, t, r, LT, T_store_U<LUs>..., T_store_U<RUs>...>
						(lv, lvs..., rvs...);
			using nT = decltype(nv);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_3TS(c, i, j, l, t, r, nT, T_store_U<LUs>..., T_store_U<MUs>...)
					(nv, lvs..., mvs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template
	<
		template<auto...> typename B0,          auto... LUs, nik_vp(p0)(B0<    LUs...>*),
		template<auto...> typename B1,          auto... MUs, nik_vp(p1)(B1<    MUs...>*),
		template<auto...> typename B2, auto RU, auto... RUs, nik_vp(p2)(B2<RU, RUs...>*),
		auto... filler
	>
	struct T_assembly<AN::bind, AT::back, p0, p1, p2, filler...>
	{
		using RT = T_store_U<RU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<MUs>... mvs, RT rv, T_store_U<RUs>... rvs)
		{
			auto  nv = T_restore_T<RT>::template
				 	result<j, l, t, r, T_store_U<LUs>..., T_store_U<RUs>...>
						(lvs..., rvs...);
			using nT = decltype(nv);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_3TS(c, i, j, l, t, r, T_store_U<LUs>..., T_store_U<MUs>..., nT)
					(lvs..., mvs..., nv);
		}
	};

/***********************************************************************************************************************/

// side:

	template
	<
		template<auto...> typename B0,          auto... LUs, nik_vp(p0)(B0<    LUs...>*),
		template<auto...> typename B1,          auto... MUs, nik_vp(p1)(B1<    MUs...>*),
		template<auto...> typename B2, auto RU, auto... RUs, nik_vp(p2)(B2<RU, RUs...>*),
		auto... filler
	>
	struct T_assembly<AN::bind, AT::side, p0, p1, p2, filler...>
	{
		using RT = T_store_U<RU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<MUs>... mvs, RT rv, T_store_U<RUs>... rvs)
		{
			T_restore_T<RT>::template
				result<j, l, t, r, T_store_U<LUs>..., T_store_U<RUs>...>
					(lvs..., rvs...);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, T_store_U<LUs>..., T_store_U<MUs>...)
					(lvs..., mvs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace assembly

