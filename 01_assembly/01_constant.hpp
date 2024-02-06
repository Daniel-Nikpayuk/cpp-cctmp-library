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

// routines:

/***********************************************************************************************************************/

// divisor:

	template<typename T>
	nik_ce auto divisor(T v)
	{
		T n{1};

		while (--v != 0) n *= 10;

		return n;
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_assembly<AN::halt, AT::first, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T
			{ return v; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// boolean:

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_assembly<AN::boolean, AT::first, filler...>
	{
		using csize_type = gcbool_type;

		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto nv = AD<c>::pos(i);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, csize_type, Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template<auto... filler>
	struct T_assembly<AN::boolean, AT::back, filler...>
	{
		using csize_type = gcbool_type;

		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto nv = AD<c>::pos(i);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, Ts..., csize_type)
					(vs..., nv);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// n_number:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::n_number, AT::id, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			auto b  = v.cbegin() + AD<c>::pos(i);
			auto e  = v.cbegin() + AD<c>::num(i);
			auto nv = cctmp::apply<_string_to_builtin_<>>(b, e);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, decltype(nv) const, Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// port:

	template<auto... filler>
	struct T_assembly<AN::n_number, AT::port, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			using size_type  = T_store_U<r>;
			using csize_type = size_type const;

			auto b  = v.cbegin() + AD<c>::pos(i);
			auto e  = v.cbegin() + AD<c>::num(i);
			auto nv = cctmp::apply<_string_to_builtin_<r>>(b, e);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, csize_type, Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// r_number:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::r_number, AT::id, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			auto b  = v.cbegin() + AD<c>::pos(i);
			auto e  = v.cbegin() + AD<c>::num(i);
			auto k  = cctmp::apply<_subarray_match_<>>(b, e, '.');
			auto nn = cctmp::apply<_string_to_builtin_<U_auto_float>>(b, k);
			auto nr = cctmp::apply<_string_to_builtin_<U_auto_float>>(k+1, e);
			auto nv = nn + nr/divisor(e-k);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, decltype(nv), Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// port:

	template<auto... filler>
	struct T_assembly<AN::r_number, AT::port, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			using size_type  = T_store_U<r>;
			using csize_type = size_type const;

			auto b  = v.cbegin() + AD<c>::pos(i);
			auto e  = v.cbegin() + AD<c>::num(i);
			auto k  = cctmp::apply<_subarray_match_<>>(b, e, '.');
			auto nn = cctmp::apply<_string_to_builtin_<r>>(b, k);
			auto nr = cctmp::apply<_string_to_builtin_<r>>(k+1, e);
			auto nv = nn + nr/divisor(e-k);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, csize_type, Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// character:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::character, AT::id, filler...>
	{
		using char_type  = T_store_U<U_auto_char>;
		using cchar_type = char_type const;

		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			auto b  = v.cbegin() + AD<c>::pos(i) + 1;
			auto nv = static_cast<char_type>(*b);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, cchar_type, Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// port:

	template<auto... filler>
	struct T_assembly<AN::character, AT::port, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			using char_type  = T_store_U<r>;
			using cchar_type = char_type const;

			auto b  = v.cbegin() + AD<c>::pos(i) + 1;
			auto nv = static_cast<char_type>(*b);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, cchar_type, Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// string:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::string, AT::id, filler...>
	{
		using char_type = T_store_U<U_auto_char>;

		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto n   = AD<c>::pos(i);
			nik_ce auto m   = AD<c>::num(i);
			using seq_type  = sequence<char_type, (m - n)>;
			using cseq_type = seq_type const;

			auto b = v.cbegin() + n;
			auto e = v.cbegin() + m;

			seq_type nv;
			for (auto k = b; k != e; ++k) nv.push(*k);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, cseq_type, Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// port:

	template<auto... filler>
	struct T_assembly<AN::string, AT::port, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto n   = AD<c>::pos(i);
			nik_ce auto m   = AD<c>::num(i);
			using char_type = T_store_U<r>;
			using seq_type  = sequence<char_type, (m - n)>;
			using cseq_type = seq_type const;

			auto b = v.cbegin() + n;
			auto e = v.cbegin() + m;

			seq_type nv;
			for (auto k = b; k != e; ++k) nv.push(*k);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, cseq_type, Ts...)
					(nv, vs...);
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
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto n  = AD<c>::num(i);
			nik_ce auto s  = member_value_U<at_<j, n>>;
			nik_ce auto nv = NIK_ASSEMBLY_TEMPLATE(c, ni)
			       			::NIK_ASSEMBLY_RESULT_TS(c, ni, j, l, t, r, decltype(s))
							(s);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, decltype(nv), Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template<auto... filler>
	struct T_assembly<AN::literal, AT::back, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto n  = AD<c>::num(i);
			nik_ce auto s  = member_value_U<at_<j, n>>;
			nik_ce auto nv = NIK_ASSEMBLY_TEMPLATE(c, ni)
			       			::NIK_ASSEMBLY_RESULT_TS(c, ni, j, l, t, r, decltype(s))
							(s);

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, Ts..., decltype(nv))
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
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n = AD<c>::pos(i);
			nik_ce auto p = at_<j, n>;

			return NIK_ASSEMBLY_TEMPLATE_WS(c, i, p)
				::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, r, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template<auto... filler>
	struct T_assembly<AN::list, AT::back, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n  = AD<c>::pos(i);
			nik_ce auto nv = at_<j, n>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, Ts..., decltype(nv))
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
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto   n  = AD<c>::pos(i);
			nik_ce auto   m  = AD<c>::num(i);
			nik_ce auto & t0 = member_value_U<l>;
			nik_ce auto & t1 = t0.template cvalue<n>();
			nik_ce auto   nv = t1.template cvalue<m>();

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, decltype(nv), Ts...)
					(nv, vs...);
		}
	};

/***********************************************************************************************************************/

// back:

	template<auto... filler>
	struct T_assembly<AN::lookup, AT::back, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto   n  = AD<c>::pos(i);
			nik_ce auto   m  = AD<c>::num(i);
			nik_ce auto & t0 = member_value_U<l>;
			nik_ce auto & t1 = t0.template cvalue<n>();
			nik_ce auto   nv = t1.template cvalue<m>();

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_2TS(c, i, j, l, t, r, Ts..., decltype(nv))
					(vs..., nv);
		}
	};

/***********************************************************************************************************************/

// push:

	template<auto... filler>
	struct T_assembly<AN::lookup, AT::push, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto   n  = AD<c>::pos(i);
			nik_ce auto   m  = AD<c>::num(i);
			nik_ce auto & t0 = member_value_U<l>;
			nik_ce auto & t1 = t0.template cvalue<n>();
			nik_ce auto   nr = t1.template cvalue<m>();

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, nr, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// type:

/***********************************************************************************************************************/

// push:

	template<auto... filler>
	struct T_assembly<AN::type, AT::push, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n  = AD<c>::pos(i);
			nik_ce auto nr = at_<t, n>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, nr, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// pull:

	template<auto... filler>
	struct T_assembly<AN::type, AT::pull, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto nr = at_<t, r>;

			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, nr, Ts...)
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
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n  = AD<c>::pos(i);
			nik_ce auto p0 = eval<_par_left_ , n, U_store_T<Ts>...>;
			nik_ce auto p1 = eval<_par_right_, n, U_store_T<Ts>...>;

			return NIK_ASSEMBLY_TEMPLATE_2WS(c, i, p0, p1)
				::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, r, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/

// verse:

	template<auto... filler>
	struct T_assembly<AN::arg, AT::verse, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto n  = AD<c>::pos(i);
			nik_ce auto m  = AD<c>::num(i);
			nik_ce auto p  = eval<_par_left_ , m, U_store_T<Ts>...>;
			nik_ce auto p0 = unpack_<p, _par_left_, n>;
			nik_ce auto p1 = unpack_<p, _par_right_, n>;
			nik_ce auto p2 = eval<_par_right_, m, U_store_T<Ts>...>;

			return NIK_ASSEMBLY_TEMPLATE_3WS(c, i, p0, p1, p2)
				::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, r, Ts...)
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
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<RUs>... rvs)
		{
			return NIK_ASSEMBLY_TEMPLATE(c, i)
				::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, r, T_store_U<RUs>...)
					(rvs...);
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

		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(LT lv, T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs)
		{
			return NIK_ASSEMBLY_TEMPLATE(c, i)::NIK_ASSEMBLY_RESULT_4TS
				(c, i, j, l, t, r, LT, T_store_U<LUs>..., LT, T_store_U<RUs>...)
					(lv, lvs..., lv, rvs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace assembly

