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
/***********************************************************************************************************************/

// next:

/***********************************************************************************************************************/

// id:

	template
	<
		template<auto...> typename B0,          auto... LUs, nik_vp(p0)(B0<    LUs...>*),
		template<auto...> typename B1,          auto... MUs, nik_vp(p1)(B1<    MUs...>*),
		template<auto...> typename B2, auto RU, auto... RUs, nik_vp(p2)(B2<RU, RUs...>*),
		auto... filler
	>
	struct T_assembly<AN::next, AT::id, p0, p1, p2, filler...>
	{
		using RT = T_store_U<RU>;
		using  T = to_mptr<RU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<MUs>... mvs, RT rv, T_store_U<RUs>... rvs)
		{
			nik_ce auto ni  = AD<c>::pos(i);
			nik_ce auto np1 = cctmp::U_pack_Ts<T>;

			NIK_ASSEMBLY_TEMPLATE_2WS(c, ni, p0, np1)
				::NIK_ASSEMBLY_RESULT_2TS(c, ni, l, t, r, T_store_U<LUs>..., T)
					(lvs..., const_cast<T>(rv)); // iter

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_4TS(c, i, l, t, r,
					T_store_U<LUs>..., T_store_U<MUs>..., RT, T_store_U<RUs>...)
						(lvs..., mvs..., rv, rvs...);
		}
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

// repeat:

/***********************************************************************************************************************/

// id:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto OU, auto EU, auto... IUs,
		nik_vp(p1)(B1<OU, EU, IUs...>*), auto... filler
	>
	struct T_assembly<AN::repeat, AT::id, p0, p1, filler...>
	{
		static_assert(sizeof...(IUs), "{ AN::repeat, AT::id } requires at least one in argument.");

		using Out = T_store_U<OU>;
		using End = T_store_U<EU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Out out, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = AD<c>::pos(i);  // predicate
			nik_ce auto mi = AD<c>::num(i);  // action
			nik_ce auto li = AD<c>::aux0(i); // mutate
			nik_ce auto ki = AD<c>::aux1(i); // next

			while (NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_3TS(c, ni, l, t, r, T_store_U<LUs>..., Out, End)
					(lvs..., out, end)) // predicate
			{
				auto nv = NIK_ASSEMBLY_TEMPLATE(c, mi)
					::NIK_ASSEMBLY_RESULT_2TS(c, mi, l, t, r, T_store_U<LUs>..., T_store_U<IUs>...)
						(lvs..., ins...); // action

				NIK_ASSEMBLY_TEMPLATE(c, li)
					::NIK_ASSEMBLY_RESULT_3TS(c, li, l, t, r, T_store_U<LUs>..., Out, decltype(nv))
						(lvs..., out, nv); // mutate

				NIK_ASSEMBLY_TEMPLATE(c, ki)
					::NIK_ASSEMBLY_RESULT_4TS(c, ki, l, t, r,
						T_store_U<LUs>..., Out*, End, T_store_U<IUs>*...)
							(lvs..., &out, end, &ins...); // next
			}

			return NIK_ASSEMBLY_TEMPLATE_2WS(c, i, p0, p1)
				::NIK_ASSEMBLY_RESULT_4TS(c, i, l, t, r,
					T_store_U<LUs>..., Out, End, T_store_U<IUs>...)
						(lvs..., out, end, ins...);
		}
	};

/***********************************************************************************************************************/

// back:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto OU, auto EU, auto... IUs,
		nik_vp(p1)(B1<OU, EU, IUs...>*), auto... filler
	>
	struct T_assembly<AN::repeat, AT::back, p0, p1, filler...>
	{
		static_assert(sizeof...(IUs), "{ AN::repeat, AT::id } requires at least one in argument.");

		using Out = T_store_U<OU>;
		using End = T_store_U<EU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Out out, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = AD<c>::pos(i);  // action
			nik_ce auto mi = AD<c>::num(i);  // mutate

			auto nv = NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_2TS(c, ni, l, t, r, T_store_U<LUs>..., T_store_U<IUs>...)
					(lvs..., ins...); // action

			NIK_ASSEMBLY_TEMPLATE(c, mi)
				::NIK_ASSEMBLY_RESULT_3TS(c, mi, l, t, r, T_store_U<LUs>..., Out, decltype(nv))
					(lvs..., out, nv); // mutate

			return NIK_ASSEMBLY_TEMPLATE_2WS(c, i, p0, p1)
				::NIK_ASSEMBLY_RESULT_4TS(c, i, l, t, r,
					T_store_U<LUs>..., Out, End, T_store_U<IUs>...)
						(lvs..., out, end, ins...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// map:

/***********************************************************************************************************************/

// id:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto OU, auto IU, auto EU, auto... IUs,
		nik_vp(p1)(B1<OU, IU, EU, IUs...>*), auto... filler
	>
	struct T_assembly<AN::map, AT::id, p0, p1, filler...>
	{
		using Out = T_store_U<OU>;
		using In  = T_store_U<IU>;
		using End = T_store_U<EU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Out out, In in, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = AD<c>::pos(i);  // predicate
			nik_ce auto mi = AD<c>::num(i);  // action
			nik_ce auto li = AD<c>::aux0(i); // mutate
			nik_ce auto ki = AD<c>::aux1(i); // next

			while (NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_3TS(c, ni, l, t, r, T_store_U<LUs>..., In, End)
					(lvs..., in, end)) // predicate
			{
				auto nv = NIK_ASSEMBLY_TEMPLATE(c, mi)
					::NIK_ASSEMBLY_RESULT_3TS(c, mi, l, t, r, T_store_U<LUs>..., In, T_store_U<IUs>...)
						(lvs..., in, ins...); // action

				NIK_ASSEMBLY_TEMPLATE(c, li)
					::NIK_ASSEMBLY_RESULT_3TS(c, li, l, t, r, T_store_U<LUs>..., Out, decltype(nv))
						(lvs..., out, nv); // mutate

				NIK_ASSEMBLY_TEMPLATE(c, ki)
					::NIK_ASSEMBLY_RESULT_5TS(c, ki, l, t, r,
						T_store_U<LUs>..., Out*, In*, End, T_store_U<IUs>*...)
							(lvs..., &out, &in, end, &ins...); // next
			}

			return NIK_ASSEMBLY_TEMPLATE_2WS(c, i, p0, p1)
				::NIK_ASSEMBLY_RESULT_5TS(c, i, l, t, r,
					T_store_U<LUs>..., Out, In, End, T_store_U<IUs>...)
						(lvs..., out, in, end, ins...);
		}
	};

/***********************************************************************************************************************/

// back:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto OU, auto IU, auto EU, auto... IUs,
		nik_vp(p1)(B1<OU, IU, EU, IUs...>*), auto... filler
	>
	struct T_assembly<AN::map, AT::back, p0, p1, filler...>
	{
		using Out = T_store_U<OU>;
		using In  = T_store_U<IU>;
		using End = T_store_U<EU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Out out, In in, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = AD<c>::pos(i);  // action
			nik_ce auto mi = AD<c>::num(i);  // mutate

			auto nv = NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_3TS(c, ni, l, t, r, T_store_U<LUs>..., In, T_store_U<IUs>...)
					(lvs..., in, ins...); // action

			NIK_ASSEMBLY_TEMPLATE(c, mi)
				::NIK_ASSEMBLY_RESULT_3TS(c, mi, l, t, r, T_store_U<LUs>..., Out, decltype(nv))
					(lvs..., out, nv); // mutate

			return NIK_ASSEMBLY_TEMPLATE_2WS(c, i, p0, p1)
				::NIK_ASSEMBLY_RESULT_5TS(c, i, l, t, r,
					T_store_U<LUs>..., Out, In, End, T_store_U<IUs>...)
						(lvs..., out, in, end, ins...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/

// id:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto OU, auto IU, auto EU, auto... IUs,
		nik_vp(p1)(B1<OU, IU, EU, IUs...>*), auto... filler
	>
	struct T_assembly<AN::fold, AT::id, p0, p1, filler...>
	{
		using Out = T_store_U<OU>;
		using In  = T_store_U<IU>;
		using End = T_store_U<EU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Out out, In in, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = AD<c>::pos(i);  // predicate
			nik_ce auto mi = AD<c>::num(i);  // action
			nik_ce auto li = AD<c>::aux0(i); // combine
			nik_ce auto ki = AD<c>::aux1(i); // mutate
			nik_ce auto ji = AD<c>::aux2(i); // next

			while (NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_3TS(c, ni, l, t, r, T_store_U<LUs>..., In, End)
					(lvs..., in, end)) // predicate
			{
				auto nv = NIK_ASSEMBLY_TEMPLATE(c, mi)
					::NIK_ASSEMBLY_RESULT_3TS(c, mi, l, t, r, T_store_U<LUs>..., In, T_store_U<IUs>...)
						(lvs..., in, ins...); // action

				auto mv = NIK_ASSEMBLY_TEMPLATE(c, li)
					::NIK_ASSEMBLY_RESULT_3TS(c, li, l, t, r, T_store_U<LUs>..., Out, decltype(nv))
						(lvs..., out, nv); // combine

				NIK_ASSEMBLY_TEMPLATE(c, ki)
					::NIK_ASSEMBLY_RESULT_3TS(c, ki, l, t, r, T_store_U<LUs>..., Out, decltype(mv))
						(lvs..., out, mv); // mutate

				NIK_ASSEMBLY_TEMPLATE(c, ji)
					::NIK_ASSEMBLY_RESULT_5TS(c, ji, l, t, r,
						T_store_U<LUs>..., Out*, In*, End*, T_store_U<IUs>*...)
							(lvs..., &out, &in, &end, &ins...); // next
			}

			return NIK_ASSEMBLY_TEMPLATE_2WS(c, i, p0, p1)
				::NIK_ASSEMBLY_RESULT_5TS(c, i, l, t, r,
					T_store_U<LUs>..., Out, In, End, T_store_U<IUs>...)
						(lvs..., out, in, end, ins...);
		}
	};

/***********************************************************************************************************************/

// back:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto OU, auto IU, auto EU, auto... IUs,
		nik_vp(p1)(B1<OU, IU, EU, IUs...>*), auto... filler
	>
	struct T_assembly<AN::fold, AT::back, p0, p1, filler...>
	{
		using Out = T_store_U<OU>;
		using In  = T_store_U<IU>;
		using End = T_store_U<EU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Out out, In in, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = AD<c>::pos(i);  // action
			nik_ce auto mi = AD<c>::num(i);  // combine
			nik_ce auto li = AD<c>::aux0(i); // mutate

			auto nv = NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_3TS(c, ni, l, t, r, T_store_U<LUs>..., In, T_store_U<IUs>...)
					(lvs..., in, ins...); // action

			auto mv = NIK_ASSEMBLY_TEMPLATE(c, mi)
				::NIK_ASSEMBLY_RESULT_3TS(c, mi, l, t, r, T_store_U<LUs>..., Out, decltype(nv))
					(lvs..., out, nv); // combine

			NIK_ASSEMBLY_TEMPLATE(c, li)
				::NIK_ASSEMBLY_RESULT_3TS(c, li, l, t, r, T_store_U<LUs>..., Out, decltype(mv))
					(lvs..., out, mv); // mutate

			return NIK_ASSEMBLY_TEMPLATE_2WS(c, i, p0, p1)
				::NIK_ASSEMBLY_RESULT_5TS(c, i, l, t, r,
					T_store_U<LUs>..., Out, In, End, T_store_U<IUs>...)
						(lvs..., out, in, end, ins...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find:

/***********************************************************************************************************************/

// id:

	template
	<
		template<auto...> typename B0, auto LU, auto... LUs, nik_vp(p0)(B0<LU, LUs...>*),
		template<auto...> typename B1, auto OU, auto IU, auto EU, auto... IUs,
		nik_vp(p1)(B1<OU, IU, EU, IUs...>*), auto... filler
	>
	struct T_assembly<AN::find, AT::id, p0, p1, filler...>
	{
		using LT  = T_store_U<LU>;
		using Out = T_store_U<OU>;
		using In  = T_store_U<IU>;
		using End = T_store_U<EU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(LT lv, T_store_U<LUs>... lvs, Out out, In in, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = AD<c>::pos(i);  // predicate
			nik_ce auto mi = AD<c>::num(i);  // match
			nik_ce auto li = AD<c>::aux0(i); // mutate
			nik_ce auto ki = AD<c>::aux1(i); // tone next
			nik_ce auto ji = AD<c>::aux2(i); // next

			bool match{false};

			while (NIK_ASSEMBLY_TEMPLATE_2WS(c, ni, p0, p1)
				::NIK_ASSEMBLY_RESULT_4TS(c, ni, l, t, r, LT, T_store_U<LUs>..., In, End)
					(lv, lvs..., in, end)) // predicate
			{
				if (NIK_ASSEMBLY_TEMPLATE_2WS(c, mi, p0, p1)
					::NIK_ASSEMBLY_RESULT_4TS(c, mi, l, t, r,
						LT, T_store_U<LUs>..., In, T_store_U<IUs>...)
							(lv, lvs..., in, ins...)) // match
				{
					NIK_ASSEMBLY_TEMPLATE_2WS(c, li, p0, p1)
						::NIK_ASSEMBLY_RESULT_5TS(c, li, l, t, r,
							LT, T_store_U<LUs>..., Out, In, T_store_U<IUs>...)
								(lv, lvs..., out, in, ins...); // mutate

					NIK_ASSEMBLY_TEMPLATE(c, ki)
						::NIK_ASSEMBLY_RESULT_3TS(c, ki, l, t, r, LT, T_store_U<LUs>..., Out)
							(lv, lvs..., out); // tone next

					match = true;
					break;
				}

				NIK_ASSEMBLY_TEMPLATE(c, ji)
					::NIK_ASSEMBLY_RESULT_6TS(c, ji, l, t, r,
						LT, T_store_U<LUs>..., Out, In, End, T_store_U<IUs>...)
							(lv, lvs..., out, in, end, ins...); // next
			}

			return NIK_ASSEMBLY_TEMPLATE_2WS(c, i, p0, p1)
				::NIK_ASSEMBLY_RESULT_6TS(c, i, l, t, r,
					gcbool_type, T_store_U<LUs>..., Out, In, End, T_store_U<IUs>...)
						(not match, lvs..., out, in, end, ins...);
		}
	};

/***********************************************************************************************************************/

// back:

	template
	<
		template<auto...> typename B0, auto LU, auto... LUs, nik_vp(p0)(B0<LU, LUs...>*),
		template<auto...> typename B1, auto OU, auto IU, auto EU, auto... IUs,
		nik_vp(p1)(B1<OU, IU, EU, IUs...>*), auto... filler
	>
	struct T_assembly<AN::find, AT::back, p0, p1, filler...>
	{
		using LT  = T_store_U<LU>;
		using Out = T_store_U<OU>;
		using In  = T_store_U<IU>;
		using End = T_store_U<EU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(LT lv, T_store_U<LUs>... lvs, Out out, In in, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = AD<c>::pos(i);  // match
			nik_ce auto mi = AD<c>::num(i);  // mutate
			nik_ce auto li = AD<c>::aux0(i); // tone next

			// no match
			if (lv && NIK_ASSEMBLY_TEMPLATE_2WS(c, ni, p0, p1)
					::NIK_ASSEMBLY_RESULT_4TS(c, ni, l, t, r,
						LT, T_store_U<LUs>..., In, T_store_U<IUs>...)
							(lv, lvs..., in, ins...)) // match
			{
				NIK_ASSEMBLY_TEMPLATE_2WS(c, mi, p0, p1)
					::NIK_ASSEMBLY_RESULT_5TS(c, mi, l, t, r,
						LT, T_store_U<LUs>..., Out, In, T_store_U<IUs>...)
							(lv, lvs..., out, in, ins...); // mutate

				NIK_ASSEMBLY_TEMPLATE_2WS(c, li, p0, p1)
					::NIK_ASSEMBLY_RESULT_3TS(c, li, l, t, r, LT, T_store_U<LUs>..., Out)
						(lv, lvs..., out); // tone next
			}

			return NIK_ASSEMBLY_TEMPLATE_2WS(c, i, p0, p1)
				::NIK_ASSEMBLY_RESULT_6TS(c, i, l, t, r,
					LT, T_store_U<LUs>..., Out, In, End, T_store_U<IUs>...)
						(lv, lvs..., out, in, end, ins...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sift:

/***********************************************************************************************************************/

// id:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto OU, auto IU, auto EU, auto... IUs,
		nik_vp(p1)(B1<OU, IU, EU, IUs...>*), auto... filler
	>
	struct T_assembly<AN::sift, AT::id, p0, p1, filler...>
	{
		using Out = T_store_U<OU>;
		using In  = T_store_U<IU>;
		using End = T_store_U<EU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Out out, In in, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = AD<c>::pos(i);  // predicate
			nik_ce auto mi = AD<c>::num(i);  // match
			nik_ce auto li = AD<c>::aux0(i); // mutate
			nik_ce auto ki = AD<c>::aux1(i); // tone next
			nik_ce auto ji = AD<c>::aux2(i); // next

			while (NIK_ASSEMBLY_TEMPLATE_2WS(c, ni, p0, p1)
				::NIK_ASSEMBLY_RESULT_3TS(c, ni, l, t, r, T_store_U<LUs>..., In, End)
					(lvs..., in, end)) // predicate
			{
				if (NIK_ASSEMBLY_TEMPLATE_2WS(c, mi, p0, p1)
					::NIK_ASSEMBLY_RESULT_3TS(c, mi, l, t, r,
						T_store_U<LUs>..., In, T_store_U<IUs>...)
							(lvs..., in, ins...)) // match
				{
					NIK_ASSEMBLY_TEMPLATE_2WS(c, li, p0, p1)
						::NIK_ASSEMBLY_RESULT_4TS(c, li, l, t, r,
							T_store_U<LUs>..., Out, In, T_store_U<IUs>...)
								(lvs..., out, in, ins...); // mutate

					NIK_ASSEMBLY_TEMPLATE(c, ki)
						::NIK_ASSEMBLY_RESULT_2TS(c, ki, l, t, r, T_store_U<LUs>..., Out)
							(lvs..., out); // tone next
				}

				NIK_ASSEMBLY_TEMPLATE(c, ji)
					::NIK_ASSEMBLY_RESULT_5TS(c, ji, l, t, r,
						T_store_U<LUs>..., Out, In, End, T_store_U<IUs>...)
							(lvs..., out, in, end, ins...); // next
			}

			return NIK_ASSEMBLY_TEMPLATE_2WS(c, i, p0, p1)
				::NIK_ASSEMBLY_RESULT_5TS(c, i, l, t, r,
					T_store_U<LUs>..., Out, In, End, T_store_U<IUs>...)
						(lvs..., out, in, end, ins...);
		}
	};

/***********************************************************************************************************************/

// back:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto OU, auto IU, auto EU, auto... IUs,
		nik_vp(p1)(B1<OU, IU, EU, IUs...>*), auto... filler
	>
	struct T_assembly<AN::sift, AT::back, p0, p1, filler...>
	{
		using Out = T_store_U<OU>;
		using In  = T_store_U<IU>;
		using End = T_store_U<EU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Out out, In in, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = AD<c>::pos(i);  // match
			nik_ce auto mi = AD<c>::num(i);  // mutate
			nik_ce auto li = AD<c>::aux0(i); // tone next

			if (NIK_ASSEMBLY_TEMPLATE_2WS(c, ni, p0, p1)
				::NIK_ASSEMBLY_RESULT_3TS(c, ni, l, t, r,
					T_store_U<LUs>..., In, T_store_U<IUs>...)
						(lvs..., in, ins...)) // match
			{
				NIK_ASSEMBLY_TEMPLATE_2WS(c, mi, p0, p1)
					::NIK_ASSEMBLY_RESULT_4TS(c, mi, l, t, r,
						T_store_U<LUs>..., Out, In, T_store_U<IUs>...)
							(lvs..., out, in, ins...); // mutate

				NIK_ASSEMBLY_TEMPLATE_2WS(c, li, p0, p1)
					::NIK_ASSEMBLY_RESULT_2TS(c, li, l, t, r, T_store_U<LUs>..., Out)
						(lvs..., out); // tone next
			}

			return NIK_ASSEMBLY_TEMPLATE_2WS(c, i, p0, p1)
				::NIK_ASSEMBLY_RESULT_5TS(c, i, l, t, r,
					T_store_U<LUs>..., Out, In, End, T_store_U<IUs>...)
						(lvs..., out, in, end, ins...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace assembly

