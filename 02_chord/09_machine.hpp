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

// machine:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

	nik_ce auto _read_only_					= cctmp::_read_only_;

// refactor to an earlier file:

	nik_ce auto U_null_Vs					= cctmp::U_null_Vs;

	template<auto... Vs>
	using T_pack_Vs						= cctmp::T_pack_Vs<Vs...>;

	template<auto... Vs>
	nik_ce auto cons_					= cctmp::cons_<Vs...>;

	nik_ce auto _par_left_					= cctmp::_par_left_;
	nik_ce auto _par_right_					= cctmp::_par_right_;

	template<auto... Vs>
	nik_ce auto right_					= cctmp::right_<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, gkey_type, auto...> struct T_machine;

/***********************************************************************************************************************/

// names:

	struct MachineName
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			first , jump    , select , reselect ,
			right , replace , pad ,
			call  , recall  ,
			dimension
		};
	};

	using MN = MachineName;

/***********************************************************************************************************************/

// notes:

	struct MachineNote
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			go_to , branch , segment , void_f ,
			dimension
		};
	};

	using MT = MachineNote;

/***********************************************************************************************************************/

// instructions:

	struct MachineInstr { enum : gkey_type { name = 0, note, pos, dimension }; };

	using MI = MachineInstr;

/***********************************************************************************************************************/

// dispatch:

	template<auto static_contr, auto _index = 0>
	struct MachineDispatch
	{
		nik_ces auto & contr = member_value_U<static_contr>;

		// defaults:

			nik_ces gindex_type initial_index = _index;

		// accessors:

			nik_ces const auto & instr(gcindex_type i) { return contr[i]; }

		// navigators:

			nik_ces gkey_type   next_name  (gcindex_type i) { return contr[i+1][MI::name]; }
			nik_ces gkey_type   next_note  (gcindex_type i) { return contr[i+1][MI::note]; }
			nik_ces gindex_type next_index (gcindex_type i) { return i+1; }
	};

	template<auto static_contr, auto _index = 0>
	using MD = MachineDispatch<static_contr, _index>;

/***********************************************************************************************************************/

// start:

	struct T_machine_start
	{
		template<auto s, auto c, auto l, auto t, typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto i = MD<c>::initial_index;

			return NIK_MACHINE_TS(s, c, i, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// first:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_machine<MN::first, MT::id, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, t), typename T0, typename... Ts>
		nik_ces auto result(T0 v0, Ts... vs) -> T_store_U<s> { return static_cast<T_store_U<s>>(v0); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// jump:

/***********************************************************************************************************************/

// go to:

	template<auto... filler>
	struct T_machine<MN::jump, MT::go_to, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto & ins = MD<c>::instr(i);
			nik_ce auto ni    = ins[MI::pos];

			return NIK_MACHINE_TS(s, c, ni, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// branch:

	template<auto... filler>
	struct T_machine<MN::jump, MT::branch, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto & ins = MD<c>::instr(i);
			nik_ce auto ni    = ins[MI::pos];
			nik_ce auto nt    = right_<t, _one>;

			if (v) return NIK_MACHINE_TS(s, c, ni, l, nt, Ts...)(vs...);
			else   return NIK_MACHINE_TS(s, c,  i, l, nt, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// select:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_machine<MN::select, MT::id, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto & ins = MD<c>::instr(i);
			nik_ce auto n     = ins[MI::pos];
			nik_ce auto p0    = eval<_par_left_ , n, U_store_T<Ts>...>;
			nik_ce auto p1    = eval<_par_right_, n, U_store_T<Ts>...>;

			return NIK_MACHINE_TEMPLATE(c, i), p0, p1
				NIK_MACHINE_RESULT_TS(s, c, i, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// reselect:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_machine<MN::reselect, MT::id, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto & ins = MD<c>::instr(i);
			nik_ce auto n     = ins[MI::pos];
			nik_ce auto p0    = eval<_par_left_ , n+1, U_store_T<T>, U_store_T<Ts>...>;
			nik_ce auto p1    = eval<_par_right_, n, U_store_T<Ts>...>;

			return NIK_MACHINE_TEMPLATE(c, i), p0, p1
				NIK_MACHINE_RESULT_2TS(s, c, i, l, t, T, Ts...)(v, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// right:

/***********************************************************************************************************************/

// id:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto... RUs, nik_vp(p1)(B1<RUs...>*)
	>
	struct T_machine<MN::right, MT::id, p0, p1>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, t), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<RUs>... rvs) -> T_store_U<s>
		{
			nik_ce auto nt = right_<t, sizeof...(LUs)>;

			return NIK_MACHINE_TS(s, c, i, l, nt, T_store_U<RUs>...)(rvs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// replace:

/***********************************************************************************************************************/

// id:

	template
	<
		template<auto...> typename B0, auto LU, auto... LUs, nik_vp(p0)(B0<LU, LUs...>*),
		template<auto...> typename B1, auto RU, auto... RUs, nik_vp(p1)(B1<RU, RUs...>*)
	>
	struct T_machine<MN::replace, MT::id, p0, p1>
	{
		using LT = T_store_U<LU>;
		using RT = T_store_U<RU>;

		template<NIK_MACHINE_PARAMS(s, c, i, l, t), typename... Ts>
		nik_ces auto result(LT lv, T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs) -> T_store_U<s>
		{
			nik_ce auto t0 = car_<t>;
			nik_ce auto rt = right_<t, _one>;
			nik_ce auto nt = replace_<rt, sizeof...(LUs), t0>;

			return NIK_MACHINE_3TS
				(s, c, i, l, nt, T_store_U<LUs>..., LT, T_store_U<RUs>...)(lvs..., lv, rvs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pad:

/***********************************************************************************************************************/

// segment:

	template<auto... filler>
	struct T_machine<MN::pad, MT::segment, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto & ins = MD<c>::instr(i);
			nik_ce auto n     = ins[MI::pos];
			nik_ce auto p     = segment_<n>;

			return NIK_MACHINE_TEMPLATE(c, i), p
				NIK_MACHINE_RESULT_TS(s, c, i, l, t, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// id:

	template<template<auto...> typename B, auto... Is, nik_vp(p)(B<Is...>*)>
	struct T_machine<MN::pad, MT::id, p>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto nt = cons_<t, U_store_T<decltype(Is)>...>;

			return NIK_MACHINE_2TS(s, c, i, l, nt, Ts..., decltype(Is)...)(vs..., Is...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// call:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_machine<MN::call, MT::id, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto & ins = MD<c>::instr(i);
			nik_ce auto n     = ins[MI::pos];

			auto val   = T_lookup_line<c, l>::template result<n, t, Ts...>(vs...);
			using TVal = modify_type<_read_only_, decltype(val)>;

			nik_ce auto nt = cons_<t, U_store_T<decltype(val)>>;

			return NIK_MACHINE_2TS(s, c, i, l, nt, TVal, Ts...)(static_cast<TVal>(val), vs...);
		}
	};

/***********************************************************************************************************************/

// void_f:

	template<auto... filler>
	struct T_machine<MN::call, MT::void_f, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, t), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto & ins = MD<c>::instr(i);
			nik_ce auto n     = ins[MI::pos];

			T_lookup_line<c, l>::template result<n, t, Ts...>(vs...);

			nik_ce auto nt = right_<t, _one>;

			return NIK_MACHINE_TS(s, c, i, l, nt, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// recall:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_machine<MN::recall, MT::id, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto & ins = MD<c>::instr(i);
			nik_ce auto n     = ins[MI::pos];

			auto val   = T_lookup_line<c, l>::template result<n, t, T, Ts...>(v, vs...);
			using TVal = modify_type<_read_only_, decltype(val)>;

			nik_ce auto nt = cons_<t, U_store_T<decltype(val)>>;

			return NIK_MACHINE_2TS(s, c, i, l, nt, TVal, Ts...)(static_cast<TVal>(val), vs...);
		}
	};

/***********************************************************************************************************************/

// void_f:

	template<auto... filler>
	struct T_machine<MN::recall, MT::void_f, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, t), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto & ins = MD<c>::instr(i);
			nik_ce auto n     = ins[MI::pos];

			T_lookup_line<c, l>::template result<n, t, T, Ts...>(v, vs...);

			nik_ce auto nt = right_<t, _one>;

			return NIK_MACHINE_TS(s, c, i, l, nt, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

