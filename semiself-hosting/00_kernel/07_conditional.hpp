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

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// go to:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_machine<MN::go_to, MT::id, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = MD<c>::pos(i);

			return NIK_MACHINE_TEMPLATE(c, ni)
				::NIK_MACHINE_RESULT_TS(c, ni, l, t, r, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// branch:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_machine<MN::branch, MT::id, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto ni = MD<c>::pos(i);

			if (v) return NIK_MACHINE_TEMPLATE(c, ni)
				::NIK_MACHINE_RESULT_TS(c, ni, l, t, r, T, Ts...)
					(v, vs...);

			else   return NIK_MACHINE_TEMPLATE(c,  i)
				::NIK_MACHINE_RESULT_TS(c,  i, l, t, r, T, Ts...)
					(v, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// invert:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_machine<MN::invert, MT::id, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto ni = MD<c>::pos(i);

			if (v) return NIK_MACHINE_TEMPLATE(c,  i)
				::NIK_MACHINE_RESULT_TS(c,  i, l, t, r, T, Ts...)
					(v, vs...);

			else   return NIK_MACHINE_TEMPLATE(c, ni)
				::NIK_MACHINE_RESULT_TS(c, ni, l, t, r, T, Ts...)
					(v, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// loop:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_machine<MN::loop, MT::id, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = MD<c>::pos(i);
			nik_ce auto mi = MD<c>::num(i);

			while (NIK_MACHINE_TEMPLATE(c, ni)
				::NIK_MACHINE_RESULT_TS(c, ni, l, t, r, Ts...)
					(vs...)) // predicate

				NIK_MACHINE_TEMPLATE(c, mi)
					::NIK_MACHINE_RESULT_TS(c, mi, l, t, r, Ts*...)
						(&vs...); // side

			return NIK_MACHINE_TEMPLATE(c, i)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cycle:

/***********************************************************************************************************************/

// front:

	template<auto... filler>
	struct T_machine<MN::cycle, MT::front, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = MD<c>::pos(i);

			NIK_MACHINE_TEMPLATE(c, ni)
				::NIK_MACHINE_RESULT_TS(c, ni, l, t, r, Ts*...)
					(&vs...); // next

			return NIK_MACHINE_TEMPLATE(c, i)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template<auto p0, auto p1, auto... filler>
	struct T_machine<MN::cycle, MT::back, p0, p1, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = MD<c>::pos(i);

			NIK_MACHINE_TEMPLATE(c, ni)
				::NIK_MACHINE_RESULT_TS(c, ni, l, t, r, Ts*...)
					(&vs...); // next

			return NIK_MACHINE_TEMPLATE_WS(c, i, p0, p1)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// drop:

	template
	<
		template<auto...> typename B0, auto LU, auto... LUs, nik_vp(p0)(B0<LU, LUs...>*),
		template<auto...> typename B1, auto OU, auto... IUs,
		nik_vp(p1)(B1<OU, IUs...>*), auto... filler
	>
	struct T_machine<MN::cycle, MT::drop, p0, p1, filler...>
	{
		using LT  = T_store_U<LU>;
		using Out = T_store_U<OU>;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(LT lv, T_store_U<LUs>... lvs, Out out, T_store_U<IUs>... ins)
		{
			return NIK_MACHINE_TEMPLATE(c, i)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r,
					Out, T_store_U<LUs>..., Out, T_store_U<IUs>...)
						(out, lvs..., out, ins...);
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
	struct T_machine<MN::next, MT::id, p0, p1, p2, filler...>
	{
		using RT = T_store_U<RU>;
		using  T = to_mptr<RU>;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<MUs>... mvs, RT rv, T_store_U<RUs>... rvs)
		{
			nik_ce auto ni  = MD<c>::pos(i);
			nik_ce auto np1 = cctmp::U_pack_Ts<T>;

			NIK_MACHINE_TEMPLATE_WS(c, ni, p0, np1)
				::NIK_MACHINE_RESULT_TS(c, ni, l, t, r, T_store_U<LUs>..., T)
					(lvs..., const_cast<T>(rv)); // iter

			return NIK_MACHINE_TEMPLATE(c, i)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r,
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
	struct T_machine<MN::next, MT::side, p0, p1, filler...>
	{
		using RT = T_store_U<RU>;
		using  T = modify_type<_from_pointer_, RT>;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, RT rv)
		{
			nik_ce auto ni = MD<c>::pos(i);
			nik_ce auto mi = MD<c>::num(i);

			auto nv = NIK_MACHINE_TEMPLATE(c, ni)
				::NIK_MACHINE_RESULT_TS(c, ni, l, t, r, T_store_U<LUs>..., T)
					(lvs..., *rv); // action

			NIK_MACHINE_TEMPLATE(c, mi)
				::NIK_MACHINE_RESULT_TS(c, mi, l, t, r, T_store_U<LUs>..., RT, decltype(nv))
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
	struct T_machine<MN::next, MT::inc, p0, p1, filler...>
	{
		using RT = T_store_U<RU>;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
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
	struct T_machine<MN::next, MT::dec, p0, p1, filler...>
	{
		using RT = T_store_U<RU>;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
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
	struct T_machine<MN::set, MT::id, p0, p1, filler...>
	{
		using RT0 = T_store_U<RU0>;
		using RT1 = T_store_U<RU1>;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
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
	struct T_machine<MN::repeat, MT::id, p0, p1, filler...>
	{
		static_assert(sizeof...(IUs), "{ MN::repeat, MT::id } requires at least one in argument.");

		using Out = T_store_U<OU>;
		using End = T_store_U<EU>;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Out out, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = MD<c>::pos(i);  // predicate
			nik_ce auto mi = MD<c>::num(i);  // action
			nik_ce auto li = MD<c>::aux0(i); // mutate
			nik_ce auto ki = MD<c>::aux1(i); // next

			while (NIK_MACHINE_TEMPLATE(c, ni)
				::NIK_MACHINE_RESULT_TS(c, ni, l, t, r, T_store_U<LUs>..., Out, End)
					(lvs..., out, end)) // predicate
			{
				auto nv = NIK_MACHINE_TEMPLATE(c, mi)
					::NIK_MACHINE_RESULT_TS(c, mi, l, t, r, T_store_U<LUs>..., T_store_U<IUs>...)
						(lvs..., ins...); // action

				NIK_MACHINE_TEMPLATE(c, li)
					::NIK_MACHINE_RESULT_TS(c, li, l, t, r, T_store_U<LUs>..., Out, decltype(nv))
						(lvs..., out, nv); // mutate

				NIK_MACHINE_TEMPLATE(c, ki)
					::NIK_MACHINE_RESULT_TS(c, ki, l, t, r,
						T_store_U<LUs>..., Out*, End*, T_store_U<IUs>*...)
							(lvs..., &out, &end, &ins...); // next
			}

			return NIK_MACHINE_TEMPLATE_WS(c, i, p0, p1)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r,
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
	struct T_machine<MN::repeat, MT::back, p0, p1, filler...>
	{
		static_assert(sizeof...(IUs), "{ MN::repeat, MT::id } requires at least one in argument.");

		using Out = T_store_U<OU>;
		using End = T_store_U<EU>;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Out out, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = MD<c>::pos(i); // action
			nik_ce auto mi = MD<c>::num(i); // mutate

			auto nv = NIK_MACHINE_TEMPLATE(c, ni)
				::NIK_MACHINE_RESULT_TS(c, ni, l, t, r, T_store_U<LUs>..., T_store_U<IUs>...)
					(lvs..., ins...); // action

			NIK_MACHINE_TEMPLATE(c, mi)
				::NIK_MACHINE_RESULT_TS(c, mi, l, t, r, T_store_U<LUs>..., Out, decltype(nv))
					(lvs..., out, nv); // mutate

			return NIK_MACHINE_TEMPLATE_WS(c, i, p0, p1)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r,
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
	struct T_machine<MN::map, MT::id, p0, p1, filler...>
	{
		using Out = T_store_U<OU>;
		using In  = T_store_U<IU>;
		using End = T_store_U<EU>;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Out out, In in, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = MD<c>::pos(i);  // predicate
			nik_ce auto mi = MD<c>::num(i);  // action
			nik_ce auto li = MD<c>::aux0(i); // mutate
			nik_ce auto ki = MD<c>::aux1(i); // next

			while (NIK_MACHINE_TEMPLATE(c, ni)
				::NIK_MACHINE_RESULT_TS(c, ni, l, t, r, T_store_U<LUs>..., In, End)
					(lvs..., in, end)) // predicate
			{
				auto nv = NIK_MACHINE_TEMPLATE(c, mi)
					::NIK_MACHINE_RESULT_TS(c, mi, l, t, r, T_store_U<LUs>..., In, T_store_U<IUs>...)
						(lvs..., in, ins...); // action

				NIK_MACHINE_TEMPLATE(c, li)
					::NIK_MACHINE_RESULT_TS(c, li, l, t, r, T_store_U<LUs>..., Out, decltype(nv))
						(lvs..., out, nv); // mutate

				NIK_MACHINE_TEMPLATE(c, ki)
					::NIK_MACHINE_RESULT_TS(c, ki, l, t, r,
						T_store_U<LUs>..., Out*, In*, End*, T_store_U<IUs>*...)
							(lvs..., &out, &in, &end, &ins...); // next
			}

			return NIK_MACHINE_TEMPLATE_WS(c, i, p0, p1)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r,
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
	struct T_machine<MN::map, MT::back, p0, p1, filler...>
	{
		using Out = T_store_U<OU>;
		using In  = T_store_U<IU>;
		using End = T_store_U<EU>;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Out out, In in, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = MD<c>::pos(i);  // action
			nik_ce auto mi = MD<c>::num(i);  // mutate

			auto nv = NIK_MACHINE_TEMPLATE(c, ni)
				::NIK_MACHINE_RESULT_TS(c, ni, l, t, r, T_store_U<LUs>..., In, T_store_U<IUs>...)
					(lvs..., in, ins...); // action

			NIK_MACHINE_TEMPLATE(c, mi)
				::NIK_MACHINE_RESULT_TS(c, mi, l, t, r, T_store_U<LUs>..., Out, decltype(nv))
					(lvs..., out, nv); // mutate

			return NIK_MACHINE_TEMPLATE_WS(c, i, p0, p1)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r,
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
	struct T_machine<MN::fold, MT::id, p0, p1, filler...>
	{
		using Out = T_store_U<OU>;
		using In  = T_store_U<IU>;
		using End = T_store_U<EU>;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Out out, In in, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = MD<c>::pos(i);  // predicate
			nik_ce auto mi = MD<c>::num(i);  // action
			nik_ce auto li = MD<c>::aux0(i); // combine
			nik_ce auto ki = MD<c>::aux1(i); // mutate
			nik_ce auto ji = MD<c>::aux2(i); // next

			while (NIK_MACHINE_TEMPLATE(c, ni)
				::NIK_MACHINE_RESULT_TS(c, ni, l, t, r, T_store_U<LUs>..., In, End)
					(lvs..., in, end)) // predicate
			{
				auto nv = NIK_MACHINE_TEMPLATE(c, mi)
					::NIK_MACHINE_RESULT_TS(c, mi, l, t, r, T_store_U<LUs>..., In, T_store_U<IUs>...)
						(lvs..., in, ins...); // action

				auto mv = NIK_MACHINE_TEMPLATE(c, li)
					::NIK_MACHINE_RESULT_TS(c, li, l, t, r, T_store_U<LUs>..., Out, decltype(nv))
						(lvs..., out, nv); // combine

				NIK_MACHINE_TEMPLATE(c, ki)
					::NIK_MACHINE_RESULT_TS(c, ki, l, t, r, T_store_U<LUs>..., Out, decltype(mv))
						(lvs..., out, mv); // mutate

				NIK_MACHINE_TEMPLATE(c, ji)
					::NIK_MACHINE_RESULT_TS(c, ji, l, t, r,
						T_store_U<LUs>..., Out*, In*, End*, T_store_U<IUs>*...)
							(lvs..., &out, &in, &end, &ins...); // next
			}

			return NIK_MACHINE_TEMPLATE_WS(c, i, p0, p1)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r,
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
	struct T_machine<MN::fold, MT::back, p0, p1, filler...>
	{
		using Out = T_store_U<OU>;
		using In  = T_store_U<IU>;
		using End = T_store_U<EU>;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Out out, In in, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = MD<c>::pos(i);  // action
			nik_ce auto mi = MD<c>::num(i);  // combine
			nik_ce auto li = MD<c>::aux0(i); // mutate

			auto nv = NIK_MACHINE_TEMPLATE(c, ni)
				::NIK_MACHINE_RESULT_TS(c, ni, l, t, r, T_store_U<LUs>..., In, T_store_U<IUs>...)
					(lvs..., in, ins...); // action

			auto mv = NIK_MACHINE_TEMPLATE(c, mi)
				::NIK_MACHINE_RESULT_TS(c, mi, l, t, r, T_store_U<LUs>..., Out, decltype(nv))
					(lvs..., out, nv); // combine

			NIK_MACHINE_TEMPLATE(c, li)
				::NIK_MACHINE_RESULT_TS(c, li, l, t, r, T_store_U<LUs>..., Out, decltype(mv))
					(lvs..., out, mv); // mutate

			return NIK_MACHINE_TEMPLATE_WS(c, i, p0, p1)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r,
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
	struct T_machine<MN::find, MT::id, p0, p1, filler...>
	{
		using LT  = T_store_U<LU>;
		using Out = T_store_U<OU>;
		using In  = T_store_U<IU>;
		using End = T_store_U<EU>;

		using MIn = from_const<IU>; // currently a hack, requires improved type checking.

			// error: modifying a const object ‘in’ is not allowed in a constant expression

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(LT lv, T_store_U<LUs>... lvs, Out out, MIn in, End end, from_const<IUs>... ins)
	//	nik_ces auto result(LT lv, T_store_U<LUs>... lvs, Out out, In in, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = MD<c>::pos(i);  // predicate
			nik_ce auto mi = MD<c>::num(i);  // match
			nik_ce auto li = MD<c>::aux0(i); // mutate
			nik_ce auto ki = MD<c>::aux1(i); // cond (next)
			nik_ce auto ji = MD<c>::aux2(i); // next

			bool match{false};

			while (NIK_MACHINE_TEMPLATE_WS(c, ni, p0, p1)
				::NIK_MACHINE_RESULT_TS(c, ni, l, t, r, LT, T_store_U<LUs>..., In, End)
					(lv, lvs..., in, end)) // predicate
			{
				if (NIK_MACHINE_TEMPLATE_WS(c, mi, p0, p1)
					::NIK_MACHINE_RESULT_TS(c, mi, l, t, r,
						LT, T_store_U<LUs>..., In, T_store_U<IUs>...)
							(lv, lvs..., in, ins...)) // match
				{
					NIK_MACHINE_TEMPLATE_WS(c, li, p0, p1)
						::NIK_MACHINE_RESULT_TS(c, li, l, t, r,
							LT, T_store_U<LUs>..., Out, In)
								(lv, lvs..., out, in); // mutate

					NIK_MACHINE_TEMPLATE(c, ki)
						::NIK_MACHINE_RESULT_TS(c, ki, l, t, r, LT, T_store_U<LUs>..., Out*)
							(lv, lvs..., &out); // cond (next)

					match = true;
					break;
				}

				NIK_MACHINE_TEMPLATE(c, ji)
					::NIK_MACHINE_RESULT_TS(c, ji, l, t, r,
						LT, T_store_U<LUs>..., Out*, In*, End*, T_store_U<IUs>*...)
							(lv, lvs..., &out, &in, &end, &ins...); // next
			}

			return NIK_MACHINE_TEMPLATE_WS(c, i, p0, p1)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r,
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
	struct T_machine<MN::find, MT::back, p0, p1, filler...>
	{
		using LT  = T_store_U<LU>;
		using Out = T_store_U<OU>;
		using In  = T_store_U<IU>;
		using End = T_store_U<EU>;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(LT lv, T_store_U<LUs>... lvs, Out out, In in, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = MD<c>::pos(i);  // match
			nik_ce auto mi = MD<c>::num(i);  // mutate
			nik_ce auto li = MD<c>::aux0(i); // cond (next)

			// no match
			if (lv && NIK_MACHINE_TEMPLATE_WS(c, ni, p0, p1)
					::NIK_MACHINE_RESULT_TS(c, ni, l, t, r,
						LT, T_store_U<LUs>..., In, T_store_U<IUs>...)
							(lv, lvs..., in, ins...)) // match
			{
				NIK_MACHINE_TEMPLATE_WS(c, mi, p0, p1)
					::NIK_MACHINE_RESULT_TS(c, mi, l, t, r,
						LT, T_store_U<LUs>..., Out, In, T_store_U<IUs>...)
							(lv, lvs..., out, in, ins...); // mutate

				NIK_MACHINE_TEMPLATE_WS(c, li, p0, p1)
					::NIK_MACHINE_RESULT_TS(c, li, l, t, r, LT, T_store_U<LUs>..., Out*)
						(lv, lvs..., &out); // cond (next)
			}

			return NIK_MACHINE_TEMPLATE_WS(c, i, p0, p1)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r,
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
	struct T_machine<MN::sift, MT::id, p0, p1, filler...>
	{
		using Out = T_store_U<OU>;
		using In  = T_store_U<IU>;
		using End = T_store_U<EU>;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Out out, In in, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = MD<c>::pos(i);  // predicate
			nik_ce auto mi = MD<c>::num(i);  // match
			nik_ce auto li = MD<c>::aux0(i); // mutate
			nik_ce auto ki = MD<c>::aux1(i); // cond (next)
			nik_ce auto ji = MD<c>::aux2(i); // next

			while (NIK_MACHINE_TEMPLATE_WS(c, ni, p0, p1)
				::NIK_MACHINE_RESULT_TS(c, ni, l, t, r, T_store_U<LUs>..., In, End)
					(lvs..., in, end)) // predicate
			{
				if (NIK_MACHINE_TEMPLATE_WS(c, mi, p0, p1)
					::NIK_MACHINE_RESULT_TS(c, mi, l, t, r,
						T_store_U<LUs>..., In, T_store_U<IUs>...)
							(lvs..., in, ins...)) // match
				{
					NIK_MACHINE_TEMPLATE_WS(c, li, p0, p1)
						::NIK_MACHINE_RESULT_TS(c, li, l, t, r,
							T_store_U<LUs>..., Out, In, T_store_U<IUs>...)
								(lvs..., out, in, ins...); // mutate

					NIK_MACHINE_TEMPLATE(c, ki)
						::NIK_MACHINE_RESULT_TS(c, ki, l, t, r, T_store_U<LUs>..., Out*)
							(lvs..., &out); // cond (next)
				}

				NIK_MACHINE_TEMPLATE(c, ji)
					::NIK_MACHINE_RESULT_TS(c, ji, l, t, r,
						T_store_U<LUs>..., Out*, In*, End*, T_store_U<IUs>*...)
							(lvs..., &out, &in, &end, &ins...); // next
			}

			return NIK_MACHINE_TEMPLATE_WS(c, i, p0, p1)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r,
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
	struct T_machine<MN::sift, MT::back, p0, p1, filler...>
	{
		using Out = T_store_U<OU>;
		using In  = T_store_U<IU>;
		using End = T_store_U<EU>;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Out out, In in, End end, T_store_U<IUs>... ins)
		{
			nik_ce auto ni = MD<c>::pos(i);  // match
			nik_ce auto mi = MD<c>::num(i);  // mutate
			nik_ce auto li = MD<c>::aux0(i); // cond (next)

			if (NIK_MACHINE_TEMPLATE_WS(c, ni, p0, p1)
				::NIK_MACHINE_RESULT_TS(c, ni, l, t, r,
					T_store_U<LUs>..., In, T_store_U<IUs>...)
						(lvs..., in, ins...)) // match
			{
				NIK_MACHINE_TEMPLATE_WS(c, mi, p0, p1)
					::NIK_MACHINE_RESULT_TS(c, mi, l, t, r,
						T_store_U<LUs>..., Out, In, T_store_U<IUs>...)
							(lvs..., out, in, ins...); // mutate

				NIK_MACHINE_TEMPLATE_WS(c, li, p0, p1)
					::NIK_MACHINE_RESULT_TS(c, li, l, t, r, T_store_U<LUs>..., Out)
						(lvs..., out); // cond (next)
			}

			return NIK_MACHINE_TEMPLATE_WS(c, i, p0, p1)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r,
					T_store_U<LUs>..., Out, In, End, T_store_U<IUs>...)
						(lvs..., out, in, end, ins...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

