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

// conditional:

namespace assembly {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// go to:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::go_to, AT::id, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);

			return NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_TS(c, ni, l, t, r, Ts...)
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
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);

			if (v) return NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_2TS(c, ni, l, t, r, T, Ts...)
					(v, vs...);

			else   return NIK_ASSEMBLY_TEMPLATE(c,  i)
				::NIK_ASSEMBLY_RESULT_2TS(c,  i, l, t, r, T, Ts...)
					(v, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// invert:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::invert, AT::id, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);

			if (v) return NIK_ASSEMBLY_TEMPLATE(c,  i)
				::NIK_ASSEMBLY_RESULT_2TS(c,  i, l, t, r, T, Ts...)
					(v, vs...);

			else   return NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_2TS(c, ni, l, t, r, T, Ts...)
					(v, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// loop:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::loop, AT::id, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto mi = AD<c>::num(i);

			while (NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_TS(c, ni, l, t, r, Ts...)
					(vs...)) // predicate

				NIK_ASSEMBLY_TEMPLATE(c, mi)
					::NIK_ASSEMBLY_RESULT_TS(c, mi, l, t, r, Ts*...)
						(&vs...); // side

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, l, t, r, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cycle:

/***********************************************************************************************************************/

// front:

	template<auto... filler>
	struct T_assembly<AN::cycle, AT::front, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);

			NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_TS(c, ni, l, t, r, Ts*...)
					(&vs...); // next

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, l, t, r, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// id:

	template<auto p0, auto p1, auto... filler>
	struct T_assembly<AN::cycle, AT::id, p0, p1, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto mi = AD<c>::num(i);

			while (NIK_ASSEMBLY_TEMPLATE_2WS(c, ni, p0, p1)
				::NIK_ASSEMBLY_RESULT_TS(c, ni, l, t, r, Ts...)
					(vs...)) // predicate

				NIK_ASSEMBLY_TEMPLATE_2WS(c, mi, p0, p1)
					::NIK_ASSEMBLY_RESULT_TS(c, mi, l, t, r, Ts*...)
						(&vs...); // side

			return NIK_ASSEMBLY_TEMPLATE_2WS(c, i, p0, p1)
				::NIK_ASSEMBLY_RESULT_TS(c, i, l, t, r, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// find:

/*
	template<auto p0, auto p1, auto... filler>
	struct T_assembly<AN::cycle, AT::find, p0, p1, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>	// various optimized machines can be
		nik_ces auto result(Ts... vs)					// refactored now using aux0, aux1, ...
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto mi = AD<c>::num(i);
			nik_ce auto li = AD<c>::aux0(i);

			while (NIK_ASSEMBLY_TEMPLATE_2WS(c, ni, p0, p1)
				::NIK_ASSEMBLY_RESULT_TS(c, ni, l, t, r, Ts...)
					(vs...)) // predicate

				if (NIK_ASSEMBLY_TEMPLATE_2WS(c, mi, p0, p1)
					::NIK_ASSEMBLY_RESULT_TS(c, mi, l, t, r, Ts...)
						(vs...)) break; // match

				else NIK_ASSEMBLY_TEMPLATE_2WS(c, li, p0, p1)
						::NIK_ASSEMBLY_RESULT_TS(c, li, l, t, r, Ts*...)
							(&vs...); // next

			return NIK_ASSEMBLY_TEMPLATE_2WS(c, i, p0, p1)
				::NIK_ASSEMBLY_RESULT_TS(c, i, l, t, r, Ts...)
					(vs...);
		}
	};
*/

/***********************************************************************************************************************/

// act(ion):

	template<auto p0, auto p1, auto... filler>
	struct T_assembly<AN::cycle, AT::act, p0, p1, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);

			NIK_ASSEMBLY_TEMPLATE_2WS(c, ni, p0, p1)
				::NIK_ASSEMBLY_RESULT_TS(c, ni, l, t, r, Ts*...)
					(&vs...); // action

			return NIK_ASSEMBLY_TEMPLATE_2WS(c, i, p0, p1)
				::NIK_ASSEMBLY_RESULT_TS(c, i, l, t, r, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template<auto p0, auto p1, auto... filler>
	struct T_assembly<AN::cycle, AT::back, p0, p1, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);

			NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_TS(c, ni, l, t, r, Ts*...)
					(&vs...); // next

			return NIK_ASSEMBLY_TEMPLATE_2WS(c, i, p0, p1)
				::NIK_ASSEMBLY_RESULT_TS(c, i, l, t, r, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// side:

	template<auto p0, auto p1, auto... filler>
	struct T_assembly<AN::cycle, AT::side, p0, p1, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto mi = AD<c>::num(i);

			NIK_ASSEMBLY_TEMPLATE_2WS(c, ni, p0, p1)
				::NIK_ASSEMBLY_RESULT_TS(c, ni, l, t, r, Ts...)
					(vs...); // action

			NIK_ASSEMBLY_TEMPLATE(c, mi)
				::NIK_ASSEMBLY_RESULT_TS(c, mi, l, t, r, Ts...)
					(vs...); // next
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// next:

/***********************************************************************************************************************/

// cont(inue):

/*
	template
	<
		template<auto...> typename B0,          auto... LUs, nik_vp(p0)(B0<    LUs...>*),
		template<auto...> typename B1,          auto... MUs, nik_vp(p1)(B1<    MUs...>*),
		template<auto...> typename B2, auto RU, auto... RUs, nik_vp(p2)(B2<RU, RUs...>*),
		auto... filler
	>
	struct T_assembly<AN::next, AT::cont, p0, p1, p2, filler...>
	{
		using RT = T_store_U<RU>;
		using T  = to_mptr<RU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<MUs>... mvs, RT rv, T_store_U<RUs>... rvs)
		{
			nik_ce auto ni   = AD<c>::pos(i);
			nik_ce auto n    = AD<c>::num(i);
			nik_ce auto np1  = cctmp::U_pack_Ts<T>;
			nik_ce auto nnp1 = eval<_par_left_ , n, MUs..., RU, RUs...>;
			nik_ce auto nnp2 = eval<_par_right_, n, MUs..., RU, RUs...>;

			NIK_ASSEMBLY_TEMPLATE_2WS(c, ni, p0, np1)
				::NIK_ASSEMBLY_RESULT_2TS(c, ni, l, t, r, T_store_U<LUs>..., T)
					(lvs..., const_cast<T>(rv)); // iter

			return NIK_ASSEMBLY_TEMPLATE_3WS(c, i, p0, nnp1, nnp2)
				::NIK_ASSEMBLY_RESULT_4TS(c, i, l, t, r,
					T_store_U<LUs>..., T_store_U<MUs>..., RT, T_store_U<RUs>...)
						(lvs..., mvs..., rv, rvs...);
		}
	};
*/

	template
	<
		template<auto...> typename B0,          auto... LUs, nik_vp(p0)(B0<    LUs...>*),
		template<auto...> typename B1,          auto... MUs, nik_vp(p1)(B1<    MUs...>*),
		template<auto...> typename B2, auto RU, auto... RUs, nik_vp(p2)(B2<RU, RUs...>*),
		auto... filler
	>
	struct T_assembly<AN::next, AT::cont, p0, p1, p2, filler...>
	{
		using RT = T_store_U<RU>;
		using  T = to_mptr<RU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<MUs>... mvs, RT rv, T_store_U<RUs>... rvs)
		{
			nik_ce auto ni   = AD<c>::pos(i);
			nik_ce auto n    = AD<c>::num(i);
			nik_ce auto np1  = cctmp::U_pack_Ts<T>;
			nik_ce auto nnp1 = eval<_par_left_ , n, MUs..., RU, RUs...>;
			nik_ce auto nnp2 = eval<_par_right_, n, MUs..., RU, RUs...>;

			NIK_ASSEMBLY_TEMPLATE_2WS(c, ni, p0, np1)
				::NIK_ASSEMBLY_RESULT_2TS(c, ni, l, t, r, T_store_U<LUs>..., T)
					(lvs..., const_cast<T>(rv)); // iter

			return NIK_ASSEMBLY_TEMPLATE_3WS(c, i, p0, nnp1, nnp2)
				::NIK_ASSEMBLY_RESULT_4TS(c, i, l, t, r,
					T_store_U<LUs>..., T_store_U<MUs>..., RT, T_store_U<RUs>...)
						(lvs..., mvs..., rv, rvs...);
		}
	};

/***********************************************************************************************************************/

// end:

	template<auto p0, auto p1, auto p2, auto... filler>
	struct T_assembly<AN::next, AT::end, p0, p1, p2, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
			{ } // do nothing.
	};

/***********************************************************************************************************************/

// side:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto    RU , nik_vp(p1)(B1<RU    >*),
		auto... filler
	>
	struct T_assembly<AN::next, AT::side, p0, p1, filler...>
	{
		using RT = T_store_U<RU>;
		using  T = modify_type<_from_pointer_, RT>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, RT rv)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto mi = AD<c>::num(i);

			auto nv = NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_2TS(c, ni, l, t, r, T_store_U<LUs>..., T)
					(lvs..., *rv); // action

			NIK_ASSEMBLY_TEMPLATE(c, mi)
				::NIK_ASSEMBLY_RESULT_3TS(c, mi, l, t, r, T_store_U<LUs>..., RT, decltype(nv))
					(lvs..., rv, nv); // mutate
		}
	};

/***********************************************************************************************************************/

// inc(rement):

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto    RU , nik_vp(p1)(B1<RU    >*),
		auto... filler
	>
	struct T_assembly<AN::next, AT::inc, p0, p1, filler...>
	{
		using RT = T_store_U<RU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, RT rv)
			{ ++*rv; }
	};

/***********************************************************************************************************************/

// dec(rement):

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto    RU , nik_vp(p1)(B1<RU    >*),
		auto... filler
	>
	struct T_assembly<AN::next, AT::dec, p0, p1, filler...>
	{
		using RT = T_store_U<RU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, RT rv)
			{ --*rv; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// set:

/***********************************************************************************************************************/

// id:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto RU0, auto RU1, nik_vp(p1)(B1<RU0, RU1>*),
		auto... filler
	>
	struct T_assembly<AN::set, AT::id, p0, p1, filler...>
	{
		using RT0 = T_store_U<RU0>;
		using RT1 = T_store_U<RU1>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, RT0 rv0, RT1 rv1)
			{ *rv0 = rv1; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// out, ins:

/***********************************************************************************************************************/

// pred(icate):

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto OU, auto EU, auto... IUs,
		nik_vp(p1)(B1<OU, EU, IUs...>*), auto... filler
	>
	struct T_assembly<AN::out_ins, AT::pred, p0, p1, filler...>
	{
		using Out = T_store_U<OU>;
		using End = T_store_U<EU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Out out, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = AD<c>::pos(i);

			return NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_3TS(c, ni, l, t, r, T_store_U<LUs>..., Out, End)
					(lvs..., out, end);
		}
	};

/***********************************************************************************************************************/

// act(ion) mut(ate):

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto OU, auto EU, auto... IUs,
		nik_vp(p1)(B1<OU, EU, IUs...>*), auto... filler
	>
	struct T_assembly<AN::out_ins, AT::act_mut, p0, p1, filler...>
	{
		using Out = T_store_U<OU>;
		using End = T_store_U<EU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>*... lvs, Out* out, End* end, T_store_U<IUs>*... ins)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto mi = AD<c>::num(i);

			auto nv = NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_2TS(c, ni, l, t, r, T_store_U<LUs>..., T_store_U<IUs>...)
					(*lvs..., *ins...); // action

			NIK_ASSEMBLY_TEMPLATE(c, mi)
				::NIK_ASSEMBLY_RESULT_3TS(c, mi, l, t, r, T_store_U<LUs>..., Out, decltype(nv))
					(*lvs..., *out, nv); // mutate
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// out, in, ins:

/***********************************************************************************************************************/

// pred(icate):

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto OU, auto IU, auto EU, auto... IUs,
		nik_vp(p1)(B1<OU, IU, EU, IUs...>*), auto... filler
	>
	struct T_assembly<AN::out_in_ins, AT::pred, p0, p1, filler...>
	{
		using Out = T_store_U<OU>;
		using In  = T_store_U<IU>;
		using End = T_store_U<EU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Out out, In in, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = AD<c>::pos(i);

			return NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_3TS(c, ni, l, t, r, T_store_U<LUs>..., In, End)
					(lvs..., in, end);
		}
	};

/***********************************************************************************************************************/

// act(ion) mut(ate):

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto OU, auto IU, auto EU, auto... IUs,
		nik_vp(p1)(B1<OU, IU, EU, IUs...>*), auto... filler
	>
	struct T_assembly<AN::out_in_ins, AT::act_mut, p0, p1, filler...>
	{
		using Out = T_store_U<OU>;
		using In  = T_store_U<IU>;
		using End = T_store_U<EU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>*... lvs, Out* out, In* in, End* end, T_store_U<IUs>*... ins)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto mi = AD<c>::num(i);

			auto nv = NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_3TS(c, ni, l, t, r, T_store_U<LUs>..., In, T_store_U<IUs>...)
					(*lvs..., *in, *ins...); // action

			NIK_ASSEMBLY_TEMPLATE(c, mi)
				::NIK_ASSEMBLY_RESULT_3TS(c, mi, l, t, r, T_store_U<LUs>..., Out, decltype(nv))
					(*lvs..., *out, nv); // mutate
		}
	};

/***********************************************************************************************************************/

// comb(ine) mut(ate):

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto OU, auto IU, auto EU, auto... IUs,
		nik_vp(p1)(B1<OU, IU, EU, IUs...>*), auto... filler
	>
	struct T_assembly<AN::out_in_ins, AT::comb_mut, p0, p1, filler...>
	{
		using Out = T_store_U<OU>;
		using In  = T_store_U<IU>;
		using End = T_store_U<EU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>*... lvs, Out* out, In* in, End* end, T_store_U<IUs>*... ins)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto mi = AD<c>::num(i);
			nik_ce auto li = AD<c>::aux0(i);

			auto nv = NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_3TS(c, ni, l, t, r, T_store_U<LUs>..., In, T_store_U<IUs>...)
					(*lvs..., *in, *ins...); // action

			auto mv = NIK_ASSEMBLY_TEMPLATE(c, mi)
				::NIK_ASSEMBLY_RESULT_3TS(c, mi, l, t, r, T_store_U<LUs>..., Out, decltype(nv))
					(*lvs..., *out, nv); // combine

			NIK_ASSEMBLY_TEMPLATE(c, li)
				::NIK_ASSEMBLY_RESULT_3TS(c, li, l, t, r, T_store_U<LUs>..., Out, decltype(mv))
					(*lvs..., *out, mv); // mutate
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace assembly

