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

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

	template<typename T>
	nik_ce auto U_store_T					= cctmp::U_store_T<T>;

	template<typename T>
	nik_ce auto U_restore_T					= cctmp::U_restore_T<T>;

	template<auto... Vs>
	nik_ce auto U_pack_Vs					= cctmp::U_pack_Vs<Vs...>;

	nik_ce auto U_null_Vs					= cctmp::U_null_Vs;

	nik_ce auto _id_					= cctmp::_id_;

	nik_ce auto _same_					= cctmp::_same_;

	template<auto p, auto Op, auto... Vs>
	nik_ce auto unpack_					= cctmp::unpack_<p, Op, Vs...>;

	using ccontr_type					= cctmp::ccontr_type;

	nik_ce auto _par_at_					= cctmp::_par_at_;
	nik_ce auto _par_left_					= cctmp::_par_left_;
	nik_ce auto _par_right_					= cctmp::_par_right_;

	template<auto... Vs>
	nik_ce auto instruction					= cctmp::instruction<Vs...>;

	template<auto... Vs>
	nik_ce auto controller					= cctmp::controller<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, auto...> struct T_chain;

/***********************************************************************************************************************/

// names:

	struct ChainName
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			first , select , front , at , map , mapwise , apply , applywise ,
			dimension
		};
	};

	using CN = ChainName;

/***********************************************************************************************************************/

// instructions:

	struct ChainInstr
	{
		enum : gkey_type
		{
			size = 0,
			name , pos ,
			dimension
		};
	};

	using CI = ChainInstr;

/***********************************************************************************************************************/

// dispatch:

	struct ChainDispatch
	{
		// defaults:

			nik_ces gindex_type initial_index = _zero;

		// accessors:

			nik_ces auto instr(ccontr_type c, gcindex_type i) { return c[i]; }

		// navigators:

			nik_ces gkey_type   next_name  (ccontr_type c, gcindex_type i) { return c[i+1][CI::name]; }
			nik_ces gindex_type next_index (ccontr_type  , gcindex_type i) { return i+1; }
	};

	using CD = ChainDispatch;

/***********************************************************************************************************************/

// start:

	struct T_chain_start
	{
		nik_ces auto i = CD::initial_index;

		template<auto c, auto l, typename... Ts>
		nik_ces auto result(Ts... vs) { return NIK_CHAIN_TS(c, i, l, Ts...)(vs...); }
	};

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_chain<CN::first, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, l), typename T0, typename... Ts>
		nik_ces auto result(T0 v0, Ts... vs) { return v0; }
	};

/***********************************************************************************************************************/

// select:

	template<auto... filler>
	struct T_chain<CN::select, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, l), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ins = CD::instr(c, i);
			nik_ce auto n   = ins[CI::pos];
			nik_ce auto p   = unpack_<l, _par_at_, n>;

			return NIK_CHAIN_TEMPLATE(c, i), p
				NIK_CHAIN_RESULT_TS(c, i, l, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// front:

	template<auto... filler>
	struct T_chain<CN::front, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, l), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ins = CD::instr(c, i);
			nik_ce auto n   = ins[CI::pos];
			nik_ce auto p0  = eval<_par_left_ , n, U_store_T<Ts>...>;
			nik_ce auto p1  = eval<_par_right_, n, U_store_T<Ts>...>;

			return NIK_CHAIN_TEMPLATE(c, i), p0, p1
				NIK_CHAIN_RESULT_TS(c, i, l, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// at:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto... RUs, nik_vp(p1)(B1<RUs...>*)
	>
	struct T_chain<CN::at, p0, p1>
	{
		template<NIK_CHAIN_PARAMS(c, i, l), typename TN, typename... Ts>
		nik_ces auto at(T_store_U<LUs>... lvs, TN vn, Ts... vs)
			{ return NIK_CHAIN_TS(c, i, l, TN)(vn); }

		template<NIK_CHAIN_PARAMS(c, i, l), typename... Ts>
		nik_ces auto result(Ts... vs) { return at<c, i, l, T_store_U<RUs>...>(vs...); }
	};

/***********************************************************************************************************************/

// map:

	template<auto f>
	struct T_chain<CN::map, f>
	{
		template<NIK_CHAIN_PARAMS(c, i, l), typename... Ts>
		nik_ces auto result(Ts... vs)
			{ return NIK_CHAIN(c, i, l)(T_store_U<f>::template result<Ts>(vs)...); }
	};

/***********************************************************************************************************************/

// mapwise:

	template<template<auto...> typename B, auto... fs, nik_vp(p)(B<fs...>*)>
	struct T_chain<CN::mapwise, p>
	{
		template<NIK_CHAIN_PARAMS(c, i, l), typename... Ts>
		nik_ces auto result(Ts... vs)
			{ return NIK_CHAIN(c, i, l)(T_store_U<fs>::template result<Ts>(vs)...); }
	};

/***********************************************************************************************************************/

// apply:

	template<auto f>
	struct T_chain<CN::apply, f>
	{
		template<NIK_CHAIN_PARAMS(c, i, l), typename... Ts>
		nik_ces auto result(Ts... vs)
			{ return NIK_CHAIN(c, i, l)(T_store_U<f>::template result<Ts...>(vs...)); }
	};

/***********************************************************************************************************************/

// applywise:

	template<template<auto...> typename B, auto... fs, nik_vp(p)(B<fs...>*)>
	struct T_chain<CN::applywise, p>
	{
		template<NIK_CHAIN_PARAMS(c, i, l), typename... Ts>
		nik_ces auto result(Ts... vs)
			{ return NIK_CHAIN(c, i, l)(T_store_U<fs>::template result<Ts...>(vs...)...); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// at:

	// conceptually, modularizing out (division of labour) arg_at (focused on the registers)
	// from the arbitrary function application (separate out compose and apply) is a better
	// design, but given the nature of variadics the following might be more performant?

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// apply:

/***********************************************************************************************************************/

// function:

	template<auto f, auto n>
	struct T_apply_at
	{
		nik_ces auto lookup     = U_pack_Vs<f>;
		nik_ces auto contr      = controller
					<
						instruction< CN::front  , n     >,
						instruction< CN::at             >,
						instruction< CN::select , _zero >,
						instruction< CN::apply          >,
						instruction< CN::first          >
					>;

		template<typename... Ts>
		nik_ces auto result(Ts... vs)
			{ return T_chain_start::template result<contr, lookup, Ts...>(vs...); }
	};

/***********************************************************************************************************************/

// id (optimized):

	template<auto n>
	struct T_apply_at<_id_, n>
	{
		nik_ces auto lookup     = U_null_Vs;
		nik_ces auto contr      = controller
					<
						instruction< CN::front , n >,
						instruction< CN::at        >,
						instruction< CN::first     >
					>;

		template<typename... Ts>
		nik_ces auto result(Ts... vs)
			{ return T_chain_start::template result<contr, lookup, Ts...>(vs...); }
	};

/***********************************************************************************************************************/

// syntactic sugar:

	template<auto f, auto n>
	nik_ce auto _apply_at_ = U_store_T<T_apply_at<f, n>>;

	template<auto n>
	nik_ce auto _arg_at_ = _apply_at_<_id_, n>;

	template<auto n, typename... Ts>
	nik_ce auto arg_at(Ts... vs) { return T_apply_at<_id_, n>::template result<Ts...>(vs...); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ref:

	template<auto...> struct T_ref_at;

/***********************************************************************************************************************/

// position:

	template<auto n>
	struct T_ref_at<n>
	{
		template<typename... Ts>
		nik_ces auto & result(Ts... vs)
		{
			nik_ce auto p0  = eval<_par_left_ , n, U_store_T<Ts>...>;
			nik_ce auto p1  = eval<_par_right_, n, U_store_T<Ts>...>;

			return T_ref_at<p0, p1>::template result<Ts...>(vs...);
		}
	};

/***********************************************************************************************************************/

// pair:

	template
	<
		template<auto...> typename B0, auto... LUs, nik_vp(p0)(B0<LUs...>*),
		template<auto...> typename B1, auto... RUs, nik_vp(p1)(B1<RUs...>*)
	>
	struct T_ref_at<p0, p1>
	{
		template<typename TN, typename... Ts>
		nik_ces auto & ref_at(T_store_U<LUs>... lvs, TN vn, Ts... vs) { return vn; }

		template<typename... Ts>
		nik_ces auto & result(Ts... vs) { return ref_at<T_store_U<RUs>...>(vs...); }
	};

/***********************************************************************************************************************/

// syntactic sugar:

	template<auto n>
	nik_ce auto _ref_at_ = U_store_T<T_ref_at<n>>;

	template<auto n, typename... Ts>
	nik_ce auto & ref_at(Ts... vs) { return T_ref_at<n>::template result<Ts...>(vs...); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// composition:

	// todo:

		// 1. allow composition with void functions (change _appoint_ to void).

/***********************************************************************************************************************/

// subpose:

	template<auto f, auto... gs>
	struct T_subpose
	{
		template<typename... Ts>
		nik_ces auto result(Ts... vs)
			{ return T_store_U<f>::template result<>(T_store_U<gs>::template result<Ts>(vs)...); }

	}; template<auto f, auto... gs>
		nik_ce auto _subpose_ = U_store_T<T_subpose<f, gs...>>;

/***********************************************************************************************************************/

// compose:

	template<auto f, auto... gs>
	struct T_compose
	{
		template<typename... Ts>
		nik_ces auto result(Ts... vs)
			{ return T_store_U<f>::template result<>(T_store_U<gs>::template result<Ts...>(vs...)...); }

	}; template<auto f, auto... gs>
		nik_ce auto _compose_ = U_store_T<T_compose<f, gs...>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

