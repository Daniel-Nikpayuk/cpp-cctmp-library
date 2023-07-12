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

	template<typename T>
	using T_restore_T					= cctmp::T_restore_T<T>;

	nik_ce auto U_null_Vs					= cctmp::U_null_Vs;

	nik_ce auto _car_					= cctmp::_car_;
	nik_ce auto _cadr_					= cctmp::_cadr_;
	nik_ce auto _read_only_					= cctmp::_read_only_;

	template<auto n, typename... Ts>
	using type_at						= cctmp::type_at<n, Ts...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// dependencies:

	// conceptually, modularizing out (division of labour) arg_at (focused on the registers)
	// from the arbitrary function application (separate out compose and apply) is a better
	// design, but given the nature of variadics the following might be more performant?

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// at:

/***********************************************************************************************************************/

// apply:

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

	// syntactic sugar:

		template<auto f, auto n>
		nik_ce auto _apply_at_ = U_store_T<T_apply_at<f, n>>;

		template<auto n>
		nik_ce auto _arg_at_ = _apply_at_<_id_, n>;

		template<auto n, typename... Ts>
		nik_ce auto arg_at(Ts... vs) { return T_apply_at<_id_, n>::template result<Ts...>(vs...); }

/***********************************************************************************************************************/

// ref:

	template<auto...> struct T_ref_at;

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

	// syntactic sugar:

		template<auto n>
		nik_ce auto _ref_at_ = U_store_T<T_ref_at<n>>;

		template<auto n, typename... Ts>
		nik_ce auto & ref_at(Ts... vs) { return T_ref_at<n>::template result<Ts...>(vs...); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cast:

/***********************************************************************************************************************/

// modify at:

	template<auto t, auto n, typename T>
	struct T_modify_at
	{
		using Type = modify_type<t, T>;

		template<typename... Ts>
		nik_ces auto result(Ts... vs) // -> Type
			{ return (Type) T_apply_at<_id_, n>::template result<Ts...>(vs...); }
	};

	template<auto t, auto n, typename T>
	struct T_modify_at<t, n, T&>
	{
		using Type = modify_type<t, T&>;

		template<typename... Ts>
		nik_ces auto result(Ts... vs) -> Type&
			{ return (Type) T_ref_at<n>::template result<Ts...>(vs...); }
	};

/***********************************************************************************************************************/

// cast at:

	template<auto t, auto n, typename... Ts>
	struct T_cast_at : public T_modify_at<t, n, type_at<n, Ts...>> { };

	// (lookup) pack:

		template<auto, auto> struct T_cast_lookup { };

		template<auto Key, auto Map>
		nik_ce auto U_cast_lookup = cctmp::store<T_cast_lookup<Key, Map>*>;

	// lookup:

		// cast:

			template
			<
				auto t,
				auto key, auto static_frame, nik_vp(p)(T_cast_lookup<key, static_frame>*),
				typename... Types
			>
			struct T_cast_at<t, p, Types...>
			{
				nik_ces auto & frame = member_value_U<static_frame>;
				nik_ces auto   value = frame.template map<key>();

				template<typename... Ts>
				nik_ces auto result(Ts... vs) { return value; }
			};

		// chord:

			template
			<
				auto t,
				auto sign, auto pos, auto static_parsed, auto env,
				nik_vp(value)(T_one_cycle<sign, pos, static_parsed, env>*),
				typename... Types
			>
			struct T_cast_at<t, value, Types...>
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) { return value; }
			};

	// function:

		template<auto f, typename... Ts>
		using T_cast_op = T_cast_at<_id_, f, Ts...>;

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
			pair , front , go_to , branch , segment , value , side , void_f ,
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
			{ return (T_store_U<s>) v0; }
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
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename BoolType, typename... Ts>
		nik_ces auto result(BoolType v, Ts... vs) -> T_store_U<s>
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

// pair:

	template<auto... filler>
	struct T_machine<MN::select, MT::pair, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n   = ins[MI::pos];
			nik_ce auto p   = unpack_<l, _par_at_, n>;
			nik_ce auto p0  = unpack_<p, _car_>;
			nik_ce auto p1  = unpack_<p, _cadr_>;

			return NIK_MACHINE_TEMPLATE(c, i), p0, p1
				NIK_MACHINE_RESULT_TS(s, c, i, l, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/

// front:

	template<auto... filler>
	struct T_machine<MN::select, MT::front, filler...>
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

// front:

	template<auto... filler>
	struct T_machine<MN::reselect, MT::front, filler...>
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

	template
	<
		template<auto...> typename B0, auto f, auto... ns, nik_vp(p0)(B0<f, ns...>*),
		template<auto...> typename B1, auto... ts, nik_vp(p1)(B1<ts...>*)
	>
	struct T_machine<MN::call, MT::id, p0, p1>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			auto U     = T_cast_op<f, Ts...>::template result<Ts...>(vs...);
			auto val   = T_restore_T<decltype(U)>::template result<> // does not propagate references.
					(T_cast_at<ts, ns, Ts...>::template result<Ts...>(vs...)...);
			using TVal = modify_type<_read_only_, decltype(val)>;

			return NIK_MACHINE_2TS(s, c, i, l, TVal, Ts...)((TVal) val, vs...);
		}
	};

/***********************************************************************************************************************/

// value:

	template
	<
		template<auto...> typename B0, auto n, nik_vp(p0)(B0<n>*),
		template<auto...> typename B1, auto t, nik_vp(p1)(B1<t>*)
	>
	struct T_machine<MN::call, MT::value, p0, p1>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
					 // does not propagate references.
			auto val   = T_cast_at<t, n, Ts...>::template result<Ts...>(vs...);
			using TVal = modify_type<_read_only_, decltype(val)>;

			return NIK_MACHINE_2TS(s, c, i, l, TVal, Ts...)((TVal) val, vs...);
		}
	};

/***********************************************************************************************************************/

// side:

	template
	<
		template<auto...> typename B0, auto f, auto... ns, nik_vp(p0)(B0<f, ns...>*),
		template<auto...> typename B1, auto... ts, nik_vp(p1)(B1<ts...>*)
	>
	struct T_machine<MN::call, MT::side, p0, p1>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			auto U     = T_cast_op<f, Ts...>::template result<Ts...>(vs...);
			auto val   = T_restore_T<decltype(U)>::template result<> // does not propagate references.
					(T_cast_at<ts, ns, Ts...>::template result<Ts...>(vs...)...);
			using TVal = modify_type<_read_only_, decltype(val)>;

			return NIK_MACHINE_2TS(s, c, i, l, TVal, Ts...)((TVal) val, vs...);
		}
	};

/***********************************************************************************************************************/

// void_f:

	template
	<
		template<auto...> typename B0, auto f, auto... ns, nik_vp(p0)(B0<f, ns...>*),
		template<auto...> typename B1, auto... ts, nik_vp(p1)(B1<ts...>*)
	>
	struct T_machine<MN::call, MT::void_f, p0, p1>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			auto U = T_cast_op<f, Ts...>::template result<Ts...>(vs...);

			T_restore_T<decltype(U)>::template result<>
				(T_cast_at<ts, ns, Ts...>::template result<Ts...>(vs...)...);

			return NIK_MACHINE_TS(s, c, i, l, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// recall:

/***********************************************************************************************************************/

// id:

	template
	<
		template<auto...> typename B0, auto f, auto... ns, nik_vp(p0)(B0<f, ns...>*),
		template<auto...> typename B1, auto... ts, nik_vp(p1)(B1<ts...>*)
	>
	struct T_machine<MN::recall, MT::id, p0, p1>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			auto U     = T_cast_op<f, T, Ts...>::template result<T, Ts...>(v, vs...);
			auto val   = T_restore_T<decltype(U)>::template result<> // does not propagate references.
					(T_cast_at<ts, ns, T, Ts...>::template result<T, Ts...>(v, vs...)...);
			using TVal = modify_type<_read_only_, decltype(val)>;

			return NIK_MACHINE_2TS(s, c, i, l, TVal, Ts...)((TVal) val, vs...);
		}
	};

/***********************************************************************************************************************/

// value:

	template
	<
		template<auto...> typename B0, auto n, nik_vp(p0)(B0<n>*),
		template<auto...> typename B1, auto t, nik_vp(p1)(B1<t>*)
	>
	struct T_machine<MN::recall, MT::value, p0, p1>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
					// does not propagate references.
			auto val   = T_cast_at<t, n, T, Ts...>::template result<T, Ts...>(v, vs...);
			using TVal = modify_type<_read_only_, decltype(val)>;

			return NIK_MACHINE_2TS(s, c, i, l, TVal, Ts...)((TVal) val, vs...);
		}
	};

/***********************************************************************************************************************/

// side:

	template
	<
		template<auto...> typename B0, auto f, auto... ns, nik_vp(p0)(B0<f, ns...>*),
		template<auto...> typename B1, auto... ts, nik_vp(p1)(B1<ts...>*)
	>
	struct T_machine<MN::recall, MT::side, p0, p1>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			auto U     = T_cast_op<f, T, Ts...>::template result<T, Ts...>(v, vs...);
			auto val   = T_restore_T<decltype(U)>::template result<> // does not propagate references.
					(T_cast_at<ts, ns, T, Ts...>::template result<T, Ts...>(v, vs...)...);
			using TVal = modify_type<_read_only_, decltype(val)>;

			return NIK_MACHINE_2TS(s, c, i, l, TVal, Ts...)(val, vs...);
		}
	};

/***********************************************************************************************************************/

// void_f:

	template
	<
		template<auto...> typename B0, auto f, auto... ns, nik_vp(p0)(B0<f, ns...>*),
		template<auto...> typename B1, auto... ts, nik_vp(p1)(B1<ts...>*)
	>
	struct T_machine<MN::recall, MT::void_f, p0, p1>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			auto U = T_cast_op<f, T, Ts...>::template result<T, Ts...>(v, vs...);

			T_restore_T<decltype(U)>::template result<>
				(T_cast_at<ts, ns, T, Ts...>::template result<T, Ts...>(v, vs...)...);

			return NIK_MACHINE_TS(s, c, i, l, Ts...)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord
