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

// constant:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

/***********************************************************************************************************************/

// none:

	template<auto... filler>
	struct T_machine<MN::halt, MT::none, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs) { } // do nothing.
	};

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_machine<MN::halt, MT::first, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T
			{ return v; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// type:

/***********************************************************************************************************************/

// boolean:

	template<auto... filler>
	struct T_machine<MN::type, MT::boolean, filler...>
	{
		nik_ces auto nr = U_auto_bool;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return NIK_MACHINE_TEMPLATE(c, i)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, nr, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// character:

	template<auto... filler>
	struct T_machine<MN::type, MT::character, filler...>
	{
		nik_ces auto nr = U_auto_char;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return NIK_MACHINE_TEMPLATE(c, i)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, nr, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// n_number:

	template<auto... filler>
	struct T_machine<MN::type, MT::n_number, filler...>
	{
		nik_ces auto nr = U_auto_int;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return NIK_MACHINE_TEMPLATE(c, i)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, nr, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// r_number:

	template<auto... filler>
	struct T_machine<MN::type, MT::r_number, filler...>
	{
		nik_ces auto nr = U_auto_float;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return NIK_MACHINE_TEMPLATE(c, i)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, nr, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// push:

	template<auto... filler>
	struct T_machine<MN::type, MT::push, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n  = MD<c>::pos(i);
			nik_ce auto nr = at_<t, n>;

			return NIK_MACHINE_TEMPLATE(c, i)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, nr, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// pull:

	template<auto... filler>
	struct T_machine<MN::type, MT::pull, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto nr = at_<t, r>;

			return NIK_MACHINE_TEMPLATE(c, i)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, nr, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// literal:

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_machine<MN::literal, MT::first, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			using size_type  = T_store_U<r>;
			using size_ctype = size_type const;

			nik_ce size_type nv = MD<c>::pos(i);

			return NIK_MACHINE_TEMPLATE(c, i)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r, size_ctype, Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template<auto... filler>
	struct T_machine<MN::literal, MT::back, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			using size_type  = T_store_U<r>;
			using size_ctype = size_type const;

			nik_ce size_type nv = MD<c>::pos(i);

			return NIK_MACHINE_TEMPLATE(c, i)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r, Ts..., size_ctype)
					(vs..., nv);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// floating:

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_machine<MN::floating, MT::first, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			using size_type  = T_store_U<r>;
			using size_ctype = size_type const;

			nik_ce size_type nn = MD<c>::pos(i);
			nik_ce size_type nm = MD<c>::num(i);
			nik_ce size_type nd = MD<c>::aux0(i);
			nik_ce size_type nv = nn + nm/nd;

			return NIK_MACHINE_TEMPLATE(c, i)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r, size_ctype, Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template<auto... filler>
	struct T_machine<MN::floating, MT::back, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			using size_type  = T_store_U<r>;
			using size_ctype = size_type const;

			nik_ce size_type nn = MD<c>::pos(i);
			nik_ce size_type nm = MD<c>::num(i);
			nik_ce size_type nd = MD<c>::aux0(i);
			nik_ce size_type nv = nn + nm/nd;

			return NIK_MACHINE_TEMPLATE(c, i)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r, Ts..., size_ctype)
					(vs..., nv);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// string:

/***********************************************************************************************************************/

// first:

	// nothing yet.

/***********************************************************************************************************************/

// back:

	// nothing yet.

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lookup:

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_machine<MN::lookup, MT::first, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto   n  = MD<c>::pos(i);
			nik_ce auto   m  = MD<c>::num(i);
			nik_ce auto & t0 = member_value_U<l>;
			nik_ce auto & t1 = t0.template cvalue<n>();
			nik_ce auto   nv = t1.template cvalue<m>();

			return NIK_MACHINE_TEMPLATE(c, i)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r, decltype(nv), Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template<auto... filler>
	struct T_machine<MN::lookup, MT::back, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto   n  = MD<c>::pos(i);
			nik_ce auto   m  = MD<c>::num(i);
			nik_ce auto & t0 = member_value_U<l>;
			nik_ce auto & t1 = t0.template cvalue<n>();
			nik_ce auto   nv = t1.template cvalue<m>();

			return NIK_MACHINE_TEMPLATE(c, i)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r, Ts..., decltype(nv))
					(vs..., nv);
		}
	};

/***********************************************************************************************************************/

// push:

	template<auto... filler>
	struct T_machine<MN::lookup, MT::push, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto   n  = MD<c>::pos(i);
			nik_ce auto   m  = MD<c>::num(i);
			nik_ce auto & t0 = member_value_U<l>;
			nik_ce auto & t1 = t0.template cvalue<n>();
			nik_ce auto   nr = t1.template cvalue<m>();

			return NIK_MACHINE_TEMPLATE(c, i)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, nr, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// arg:

/***********************************************************************************************************************/

// select:

	template<auto... filler>
	struct T_machine<MN::arg, MT::select, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n  = MD<c>::pos(i);
			nik_ce auto p0 = left_  <n, U_store_T<Ts>...>;
			nik_ce auto p1 = right_ <n, U_store_T<Ts>...>;

			return NIK_MACHINE_TEMPLATE_WS(c, i, p0, p1)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// verse:

	template<auto... filler>
	struct T_machine<MN::arg, MT::verse, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n  = MD<c>::pos(i);
			nik_ce auto m  = MD<c>::num(i);
			nik_ce auto p  = left_  <m, U_store_T<Ts>...>;
			nik_ce auto p0 = left_  <p, n>;
			nik_ce auto p1 = right_ <p, n>;
			nik_ce auto p2 = right_ <m, U_store_T<Ts>...>;

			return NIK_MACHINE_TEMPLATE_WS(c, i, p0, p1, p2)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// drop:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto... RUs, nik_vp(p1)(B1<RUs...>*),
		auto... filler
	>
	struct T_machine<MN::arg, MT::drop, p0, p1, filler...>
	{
		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<RUs>... rvs)
		{
			return NIK_MACHINE_TEMPLATE(c, i)
				::NIK_MACHINE_RESULT_TS(c, i, l, t, r, T_store_U<RUs>...)
					(rvs...);
		}
	};

/***********************************************************************************************************************/

// replace:

	template
	<
		template<auto...> typename B0, auto LU, auto... LUs, nik_vp(p0)(B0<LU, LUs...>*),
		template<auto...> typename B1, auto RU, auto... RUs, nik_vp(p1)(B1<RU, RUs...>*),
		auto... filler
	>
	struct T_machine<MN::arg, MT::replace, p0, p1, filler...>
	{
		using LT = T_store_U<LU>;
		using RT = T_store_U<RU>;

		template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(LT lv, T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs)
		{
			return NIK_MACHINE_TEMPLATE(c, i)::NIK_MACHINE_RESULT_TS
				(c, i, l, t, r, LT, T_store_U<LUs>..., LT, T_store_U<RUs>...)
					(lv, lvs..., lv, rvs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

