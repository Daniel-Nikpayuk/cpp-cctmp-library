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

namespace assembly {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

/***********************************************************************************************************************/

// none:

	template<auto... filler>
	struct T_assembly<AN::halt, AT::none, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs) { } // do nothing.
	};

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_assembly<AN::halt, AT::first, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T
			{ return v; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// type:

/***********************************************************************************************************************/

// boolean:

	template<auto... filler>
	struct T_assembly<AN::type, AT::boolean, filler...>
	{
		nik_ces auto nr = U_auto_bool;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, l, t, nr, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// character:

	template<auto... filler>
	struct T_assembly<AN::type, AT::character, filler...>
	{
		nik_ces auto nr = U_auto_char;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, l, t, nr, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// n_number:

	template<auto... filler>
	struct T_assembly<AN::type, AT::n_number, filler...>
	{
		nik_ces auto nr = U_auto_int;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, l, t, nr, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// r_number:

	template<auto... filler>
	struct T_assembly<AN::type, AT::r_number, filler...>
	{
		nik_ces auto nr = U_auto_float;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, l, t, nr, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// push:

	template<auto... filler>
	struct T_assembly<AN::type, AT::push, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n  = AD<c>::pos(i);
			nik_ce auto nr = at_<t, n>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, l, t, nr, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// pull:

	template<auto... filler>
	struct T_assembly<AN::type, AT::pull, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto nr = at_<t, r>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, l, t, nr, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// literal:

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_assembly<AN::literal, AT::first, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			using size_type  = T_store_U<r>;
			using csize_type = size_type const;

			nik_ce size_type nv = AD<c>::pos(i);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, l, t, r, csize_type, Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template<auto... filler>
	struct T_assembly<AN::literal, AT::back, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			using size_type  = T_store_U<r>;
			using csize_type = size_type const;

			nik_ce size_type nv = AD<c>::pos(i);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, l, t, r, Ts..., csize_type)
					(vs..., nv);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// floating:

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_assembly<AN::floating, AT::first, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			using size_type  = T_store_U<r>;
			using csize_type = size_type const;

			nik_ce size_type nn = AD<c>::pos(i);
			nik_ce size_type nm = AD<c>::num(i);
			nik_ce size_type nd = AD<c>::aux0(i);
			nik_ce size_type nv = nn + nm/nd;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, l, t, r, csize_type, Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template<auto... filler>
	struct T_assembly<AN::floating, AT::back, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			using size_type  = T_store_U<r>;
			using csize_type = size_type const;

			nik_ce size_type nn = AD<c>::pos(i);
			nik_ce size_type nm = AD<c>::num(i);
			nik_ce size_type nd = AD<c>::aux0(i);
			nik_ce size_type nv = nn + nm/nd;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, l, t, r, Ts..., csize_type)
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
	struct T_assembly<AN::lookup, AT::first, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto   n  = AD<c>::pos(i);
			nik_ce auto   m  = AD<c>::num(i);
			nik_ce auto & t0 = member_value_U<l>;
			nik_ce auto & t1 = t0.template cvalue<n>();
			nik_ce auto   nv = t1.template cvalue<m>();

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, l, t, r, decltype(nv), Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template<auto... filler>
	struct T_assembly<AN::lookup, AT::back, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto   n  = AD<c>::pos(i);
			nik_ce auto   m  = AD<c>::num(i);
			nik_ce auto & t0 = member_value_U<l>;
			nik_ce auto & t1 = t0.template cvalue<n>();
			nik_ce auto   nv = t1.template cvalue<m>();

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, l, t, r, Ts..., decltype(nv))
					(vs..., nv);
		}
	};

/***********************************************************************************************************************/

// push:

	template<auto... filler>
	struct T_assembly<AN::lookup, AT::push, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto   n  = AD<c>::pos(i);
			nik_ce auto   m  = AD<c>::num(i);
			nik_ce auto & t0 = member_value_U<l>;
			nik_ce auto & t1 = t0.template cvalue<n>();
			nik_ce auto   nr = t1.template cvalue<m>();

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, l, t, nr, Ts...)
					(vs...);
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
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n  = AD<c>::pos(i);
			nik_ce auto p0 = eval<_par_left_ , n, U_store_T<Ts>...>;
			nik_ce auto p1 = eval<_par_right_, n, U_store_T<Ts>...>;

			return NIK_ASSEMBLY_TEMPLATE_2WS(c, i, p0, p1)
				::NIK_ASSEMBLY_RESULT_TS(c, i, l, t, r, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// verse:

	template<auto... filler>
	struct T_assembly<AN::arg, AT::verse, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n  = AD<c>::pos(i);
			nik_ce auto m  = AD<c>::num(i);
			nik_ce auto p  = eval<_par_left_ , m, U_store_T<Ts>...>;
			nik_ce auto p0 = unpack_<p, _par_left_, n>;
			nik_ce auto p1 = unpack_<p, _par_right_, n>;
			nik_ce auto p2 = eval<_par_right_, m, U_store_T<Ts>...>;

			return NIK_ASSEMBLY_TEMPLATE_3WS(c, i, p0, p1, p2)
				::NIK_ASSEMBLY_RESULT_TS(c, i, l, t, r, Ts...)
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
	struct T_assembly<AN::arg, AT::drop, p0, p1, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<RUs>... rvs)
		{
			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, l, t, r, T_store_U<RUs>...)
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
	struct T_assembly<AN::arg, AT::replace, p0, p1, filler...>
	{
		using LT = T_store_U<LU>;
		using RT = T_store_U<RU>;

		template<NIK_ASSEMBLY_PARAMS(c, i, l, t, r), typename... Ts>
		nik_ces auto result(LT lv, T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs)
		{
			return NIK_ASSEMBLY_TEMPLATE(c, i)::NIK_ASSEMBLY_RESULT_4TS
				(c, i, l, t, r, LT, T_store_U<LUs>..., LT, T_store_U<RUs>...)
					(lv, lvs..., lv, rvs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace assembly

