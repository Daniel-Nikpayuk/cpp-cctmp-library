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

	struct MachineInstr
	{
		enum : gkey_type
		{
			size = 0,
			name , note , pos ,
			dimension
		};
	};

	using MI = MachineInstr;

/***********************************************************************************************************************/

// dispatch:

	struct MachineDispatch
	{
		// defaults:

			nik_ces gindex_type initial_index = _zero;

		// accessors:

			nik_ces auto instr(ccontr_type c, gcindex_type i) { return c[i]; }

			template<typename T>
			nik_ces auto instr(nik_avp(T*), gcindex_type i) { return T::instr(i); }

		// navigators:

			nik_ces gkey_type   next_name  (ccontr_type c, gcindex_type i) { return c[i+1][MI::name]; }
			nik_ces gkey_type   next_note  (ccontr_type c, gcindex_type i) { return c[i+1][MI::note]; }
			nik_ces gindex_type next_index (ccontr_type  , gcindex_type i) { return i+1; }

			template<typename T>
			nik_ces gkey_type next_name(nik_avp(T*), gcindex_type i) { return T::next_name(i); }

			template<typename T>
			nik_ces gkey_type next_note(nik_avp(T*), gcindex_type i) { return T::next_note(i); }

			template<typename T>
			nik_ces gindex_type next_index(nik_avp(T*), gcindex_type i) { return T::next_index(i); }
	};

	using MD = MachineDispatch;

/***********************************************************************************************************************/

// start:

	struct T_machine_start
	{
		nik_ces auto i = MD::initial_index;

		template<auto s, auto c, auto l, typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
			{ return NIK_MACHINE_TS(s, c, i, l, Ts...)(vs...); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// first:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_machine<MN::first, MT::id, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename T0, typename... Ts>
		nik_ces auto result(T0 v0, Ts... vs) -> T_store_U<s>
			{ return static_cast<T_store_U<s>>((T_store_U<s>) v0); } // c style cast
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// jump:

/***********************************************************************************************************************/

// go to:

	template<auto... filler>
	struct T_machine<MN::jump, MT::go_to, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins = MD::instr(c, i);
			nik_ce auto ni  = ins[MI::pos];

			return NIK_MACHINE_TS(s, c, ni, l, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// branch:

	template<auto... filler>
	struct T_machine<MN::jump, MT::branch, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins = MD::instr(c, i);
			nik_ce auto ni  = ins[MI::pos];

			if (v) return NIK_MACHINE_TS(s, c, ni, l, Ts...)(vs...);
			else   return NIK_MACHINE_TS(s, c,  i, l, Ts...)(vs...);
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
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n   = ins[MI::pos];
			nik_ce auto p0  = eval<_par_left_ , n, U_store_T<Ts>...>;
			nik_ce auto p1  = eval<_par_right_, n, U_store_T<Ts>...>;

			return NIK_MACHINE_TEMPLATE(c, i), p0, p1
				NIK_MACHINE_RESULT_TS(s, c, i, l, Ts...)(vs...);
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
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n   = ins[MI::pos];
			nik_ce auto p0  = eval<_par_left_ , n, U_store_T<Ts>...>;
			nik_ce auto p1  = eval<_par_right_, n, U_store_T<Ts>...>;

			return NIK_MACHINE_TEMPLATE(c, i), p0, p1
				NIK_MACHINE_RESULT_2TS(s, c, i, l, T, Ts...)(v, vs...);
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
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename... Ts>
		nik_ces auto right(T_store_U<LUs>... lvs, Ts... vs) -> T_store_U<s>
			{ return NIK_MACHINE_TS(s, c, i, l, Ts...)(vs...); }

		template<NIK_MACHINE_PARAMS(s, c, i, l), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
			{ return right<s, c, i, l, T_store_U<RUs>...>(vs...); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// replace:

/***********************************************************************************************************************/

// id:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto... RUs, nik_vp(p1)(B1<RUs...>*)
	>
	struct T_machine<MN::replace, MT::id, p0, p1>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename T, typename TN, typename... Ts>
		nik_ces auto replace(T v, T_store_U<LUs>... lvs, TN vn, Ts... vs) -> T_store_U<s>
			{ return NIK_MACHINE_3TS(s, c, i, l, T_store_U<LUs>..., T, Ts...)(lvs..., v, vs...); }

		template<NIK_MACHINE_PARAMS(s, c, i, l), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
			{ return replace<s, c, i, l, T, T_store_U<RUs>...>(v, vs...); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pad:

/***********************************************************************************************************************/

// segment:

	template<auto... filler>
	struct T_machine<MN::pad, MT::segment, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n   = ins[MI::pos];
			nik_ce auto p   = eval<_par_segment_, n>;

			return NIK_MACHINE_TEMPLATE(c, i), p
				NIK_MACHINE_RESULT_TS(s, c, i, l, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// id:

	template<template<auto...> typename B, auto... Is, nik_vp(p)(B<Is...>*)>
	struct T_machine<MN::pad, MT::id, p>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
			{ return NIK_MACHINE_2TS(s, c, i, l, Ts..., decltype(Is)...)(vs..., Is...); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// call:

	// Although it is tempting to narratively define internal calls using chains, one of the advantages
	// of these machines is that each has a clarity of purpose---chains would obscure this design.

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_machine<MN::call, MT::id, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n	= ins[MI::pos];

			auto val	= T_lookup_line<c, l>::template result<n, Ts...>(vs...);
			using TVal	= modify_type<_read_only_, decltype(val)>;

			return NIK_MACHINE_2TS(s, c, i, l, TVal, Ts...)((TVal) val, vs...);
		}
	};

/***********************************************************************************************************************/

// void_f:

	template<auto... filler>
	struct T_machine<MN::call, MT::void_f, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins = MD::instr(c, i);
			nik_ce auto n   = ins[MI::pos];

			T_lookup_line<c, l>::template result<n, Ts...>(vs...);

			return NIK_MACHINE_TS(s, c, i, l, Ts...)(vs...);
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
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n	= ins[MI::pos];

			auto val	= T_lookup_line<c, l>::template result<n, T, Ts...>(v, vs...);
			using TVal	= modify_type<_read_only_, decltype(val)>;

			return NIK_MACHINE_2TS(s, c, i, l, TVal, Ts...)((TVal) val, vs...);
		}
	};

/***********************************************************************************************************************/

// void_f:

	template<auto... filler>
	struct T_machine<MN::recall, MT::void_f, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins = MD::instr(c, i);
			nik_ce auto n   = ins[MI::pos];

			T_lookup_line<c, l>::template result<n, T, Ts...>(v, vs...);

			return NIK_MACHINE_TS(s, c, i, l, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

