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

// chain:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, gkey_type, auto...> struct T_chain;

/***********************************************************************************************************************/

// names:

	struct ChainName
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			halt, pad, sift, copy, lup, ext, typ, pose,
			dimension
		};
	};

	using CN = ChainName;

/***********************************************************************************************************************/

// notes:

	struct ChainNote
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			first, tuple, apply, select, copy, push, pull, tail, proj, map,
			dimension
		};
	};

	using CT = ChainNote;

/***********************************************************************************************************************/

// instructions:

	struct ChainInstr
	{
		enum Position : gkey_type { name = 0, note, pos, num, dimension };
		enum Policy   : gkey_type { back = 0, front };
	};

	using CI = ChainInstr;

/***********************************************************************************************************************/

// dispatch:

	template<auto static_contr, auto _index = 0, auto _count = 0, auto _size = _2_6>
	struct ChainDispatch
	{
		nik_ces auto & contr = member_value_U<static_contr>;

		// defaults:

			nik_ces gindex_type initial_index = _index;
			nik_ces gindex_type initial_count = _count;
			nik_ces gindex_type block_size    = _size;

		// accessors:

			nik_ces const auto & instr(gcindex_type i) { return contr[i]; }

		// navigators:

			nik_ces gkey_type   next_name  (gcindex_type i) { return contr[i+1][CI::name]; }
			nik_ces gkey_type   next_note  (gcindex_type i) { return contr[i+1][CI::note]; }
			nik_ces gindex_type next_index (gcindex_type i) { return i+1; }
	};

	template<auto static_contr, auto _index = 0, auto _count = 0, auto _size = _2_6>
	using CD = ChainDispatch<static_contr, _index, _count, _size>;

/***********************************************************************************************************************/

// start:

	struct T_chain_start
	{
		template<auto c, auto l, auto t, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto i = CD<c>::initial_index;
			nik_ce auto j = CD<c>::initial_count;

			return NIK_CHAIN_TS(c, i, j, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// halt:

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_chain<CN::halt, CT::first, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename T0, typename... Ts>
		nik_ces auto result(T0 v0, Ts... vs) -> T0 { return v0; }
	};

/***********************************************************************************************************************/

// tuple:

	template<auto... filler>
	struct T_chain<CN::halt, CT::tuple, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) { return tuple<Ts...>(vs...); }
	};

/***********************************************************************************************************************/

// apply:

	template<auto... filler>
	struct T_chain<CN::halt, CT::apply, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) { return T_store_U<j>::template result<Ts...>(vs...); }
						// direct member call required to preserve reference semantics.
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pad:

/***********************************************************************************************************************/

// select:

	template<auto... filler>
	struct T_chain<CN::pad, CT::select, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto & ins = CD<c>::instr(i);
			nik_ce auto n     = ins[CI::pos];
			nik_ce auto p     = pad_<_na_, n>;

			return NIK_CHAIN_TEMPLATE(c, i), p
				NIK_CHAIN_RESULT_TS(c, i, j, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// push:

	template<template<auto...> typename B, auto... Vs, nik_vp(p)(B<Vs...>*)>
	struct T_chain<CN::pad, CT::push, p>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
			{ return NIK_CHAIN_2TS(c, i, j, l, t, Ts..., decltype(Vs)...)(vs..., Vs...); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// copy:

/***********************************************************************************************************************/

// proj(ection):

	template<template<auto...> typename B, auto... Vs, nik_vp(p)(B<Vs...>*)>
	struct T_chain<CN::copy, CT::proj, p>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return NIK_CHAIN_TEMPLATE(c, i), Vs...
				NIK_CHAIN_RESULT_TS(c, i, j, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// select:

	template<auto... filler>
	struct T_chain<CN::copy, CT::select, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto & ins = CD<c>::instr(i);
			nik_ce auto n     = ins[CI::pos];
			nik_ce auto p0    = eval<_par_left_ , n, U_store_T<Ts>...>;
			nik_ce auto p1    = eval<_par_right_, n, U_store_T<Ts>...>;

			return NIK_CHAIN_TEMPLATE(c, i), p0, p1
				NIK_CHAIN_RESULT_TS(c, i, j, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// push:

	template
	<
		template<auto...> typename B0,          auto... LUs, nik_vp(p0)(B0<    LUs...>*),
		template<auto...> typename B1, auto RU, auto... RUs, nik_vp(p1)(B1<RU, RUs...>*)
	>
	struct T_chain<CN::copy, CT::push, p0, p1>
	{
		using RT = T_store_U<RU>;

		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs)
		{
			return NIK_CHAIN_4TS
				(c, i, j, l, t, T_store_U<LUs>..., RT, T_store_U<RUs>..., RT)(lvs..., rv, rvs..., rv);
		}
	};

/***********************************************************************************************************************/

// pull:

	template
	<
		template<auto...> typename B0,          auto... LUs, nik_vp(p0)(B0<    LUs...>*),
		template<auto...> typename B1, auto RU, auto... RUs, nik_vp(p1)(B1<RU, RUs...>*)
	>
	struct T_chain<CN::copy, CT::pull, p0, p1>
	{
		using RT	= T_store_U<RU>;
		nik_ces auto nj	= U_restore_T<RT>;

		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs)
		{
			return NIK_CHAIN_3TS
				(c, i, nj, l, t, T_store_U<LUs>..., RT, T_store_U<RUs>...)(lvs..., rv, rvs...);
		}
	};

/***********************************************************************************************************************/

// apply:

	template
	<
		template<auto...> typename B0,          auto... LUs, nik_vp(p0)(B0<    LUs...>*),
		template<auto...> typename B1, auto RU, auto... RUs, nik_vp(p1)(B1<RU, RUs...>*)
	>
	struct T_chain<CN::copy, CT::apply, p0, p1>
	{
		using RT = T_store_U<RU>;

		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts> // equals sizeof...(Ts).
		nik_ces auto result(T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs)
		{
			using f_type  = modify_type<_to_pointer_, decltype(T_store_U<j>::template result<RT>)>;
			nik_ce auto f = (f_type) T_store_U<j>::template result<RT>;
			nik_ce auto F = eval<_function_out_type_, f>;

			return NIK_CHAIN_4TS
				(c, i, j, l, t, T_store_U<LUs>..., RT, T_store_U<RUs>..., T_store_U<F>)
					(lvs..., rv, rvs..., f(rv));
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lup:

/***********************************************************************************************************************/

// push:

	template<auto... filler>
	struct T_chain<CN::lup, CT::push, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto & ins = CD<c>::instr(i);
			nik_ce auto n     = ins[CI::pos];
			nik_ce auto v     = at_<l, n>;

			return NIK_CHAIN_2TS(c, i, j, l, t, Ts..., decltype(v))(vs..., v);
		}
	};

/***********************************************************************************************************************/

// pull:

	template<auto... filler>
	struct T_chain<CN::lup, CT::pull, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto & ins = CD<c>::instr(i);
			nik_ce auto n     = ins[CI::pos];
			nik_ce auto nj    = at_<l, n>;

			return NIK_CHAIN_TS(c, i, nj, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// apply:

	template<auto... filler>
	struct T_chain<CN::lup, CT::apply, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto & ins = CD<c>::instr(i);
			nik_ce auto n     = ins[CI::pos];
			nik_ce auto v     = at_<l, n>;
			nik_ce auto f     = T_store_U<j>::template result<decltype(v)>;
			nik_ce auto F     = eval<_function_out_type_, f>;

			return NIK_CHAIN_2TS(c, i, j, l, t, Ts..., T_store_U<F>)(vs..., f(v));
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ext:

/***********************************************************************************************************************/

// push:

	template<auto U>
	struct T_chain<CN::ext, CT::push, U>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto & ins = CD<c>::instr(i);
			nik_ce auto n     = ins[CI::pos];
			nik_ce auto m     = ins[CI::num];
			nik_ce auto v     = T_store_U<U>::template result<n, m, l, t>();

			return NIK_CHAIN_2TS(c, i, j, l, t, Ts..., decltype(v))(vs..., v);
		}
	};

/***********************************************************************************************************************/

// pull:

	template<auto U>
	struct T_chain<CN::ext, CT::pull, U>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto & ins = CD<c>::instr(i);
			nik_ce auto n     = ins[CI::pos];
			nik_ce auto m     = ins[CI::num];
			nik_ce auto nj    = T_store_U<U>::template result<n, m, l, t>();

			return NIK_CHAIN_TS(c, i, nj, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// apply:

	template<auto U>
	struct T_chain<CN::ext, CT::apply, U>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto & ins = CD<c>::instr(i);
			nik_ce auto n     = ins[CI::pos];
			nik_ce auto m     = ins[CI::num];
			nik_ce auto v     = T_store_U<U>::template result<n, m, l, t>();
			nik_ce auto f     = T_store_U<j>::template result<decltype(v)>;
			nik_ce auto F     = eval<_function_out_type_, f>;

			return NIK_CHAIN_2TS(c, i, j, l, t, Ts..., T_store_U<F>)(vs..., f(v));
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// typ:

/***********************************************************************************************************************/

// push:

	template<auto... filler>
	struct T_chain<CN::typ, CT::push, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto & ins = CD<c>::instr(i);
			nik_ce auto n     = ins[CI::pos];
			nik_ce auto v     = at_<t, n>;

			return NIK_CHAIN_2TS(c, i, j, l, t, Ts..., decltype(v))(vs..., v);
		}
	};

/***********************************************************************************************************************/

// pull:

	template<auto... filler>
	struct T_chain<CN::typ, CT::pull, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto & ins = CD<c>::instr(i);
			nik_ce auto n     = ins[CI::pos];
			nik_ce auto nj    = U_restore_T<T_store_U<at_<t, n>>>;

			return NIK_CHAIN_TS(c, i, nj, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// apply:

	template<auto... filler>
	struct T_chain<CN::typ, CT::apply, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto & ins = CD<c>::instr(i);
			nik_ce auto n     = ins[CI::pos];
			nik_ce auto v     = at_<t, n>;
			nik_ce auto f     = T_store_U<j>::template result<decltype(v)>;
			nik_ce auto F     = eval<_function_out_type_, f>;

			return NIK_CHAIN_2TS(c, i, j, l, t, Ts..., T_store_U<F>)(vs..., f(v));
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pose:

/***********************************************************************************************************************/

// tail:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto... RUs, nik_vp(p1)(B1<RUs...>*)
	>
	struct T_chain<CN::pose, CT::tail, p0, p1>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<RUs>... rvs)
			{ return NIK_CHAIN_TS(c, i, j, l, t, T_store_U<RUs>...)(rvs...); }
	};

/***********************************************************************************************************************/

// select:

	template<auto... filler>
	struct T_chain<CN::pose, CT::select, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto & ins = CD<c>::instr(i);
			nik_ce auto n     = ins[CI::pos];
			nik_ce auto p     = at_<l, n>;

			return NIK_CHAIN_TEMPLATE(c, i), p
				NIK_CHAIN_RESULT_TS(c, i, j, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// map:

		// dispatch fs against _id_ and reference semantics.

	template<template<auto...> typename B, auto... fs, nik_vp(p)(B<fs...>*)>
	struct T_chain<CN::pose, CT::map, p>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
			{ return NIK_CHAIN(c, i, j, l, t)(T_store_U<fs>::template result<Ts>(vs)...); }
				// direct member call required to preserve reference semantics.
	};

/***********************************************************************************************************************/

// apply:

		// dispatch fs against _id_ and reference semantics.

	template<template<auto...> typename B, auto... fs, nik_vp(p)(B<fs...>*)>
	struct T_chain<CN::pose, CT::apply, p>
	{
		template<NIK_CHAIN_PARAMS(c, i, j, l, t), typename... Ts>
		nik_ces auto result(Ts... vs)
			{ return NIK_CHAIN(c, i, j, l, t)(T_store_U<fs>::template result<Ts...>(vs...)...); }
				// direct member call required to preserve reference semantics.
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

