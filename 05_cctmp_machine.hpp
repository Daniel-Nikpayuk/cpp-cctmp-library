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

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// dependencies:

/***********************************************************************************************************************/

// params (syntactic sugar):

	nik_ce auto _dpar_at_		= U_custom_T<T_interpreter_params< IT::back   , _car_           >>;
	nik_ce auto _dpar_left_		= U_custom_T<T_interpreter_params< IT::front  , _list_<>        >>;
	nik_ce auto _dpar_replace_	= U_custom_T<T_interpreter_params< IT::mutate , _list_<> , _one >>;

	nik_ce auto _par_at_		= _alias_< _dpar_at_      , ID::initial_depth >;
	nik_ce auto _par_left_		= _alias_< _dpar_left_    , ID::initial_depth >;
	nik_ce auto _par_replace_	= _alias_< _dpar_replace_ , ID::initial_depth >;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// chain:

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

			nik_ces auto instr(ccontr_type c, gcindex_type i)
				{ return c[i]; }

		// navigators:

			nik_ces gkey_type next_name(ccontr_type c, gcindex_type i)
				{ return c[i+1][CI::name]; }

			nik_ces gindex_type next_index(ccontr_type, gcindex_type i)
				{ return i+1; }
	};

	using CD = ChainDispatch;

/***********************************************************************************************************************/

// start:

	struct T_chain_start
	{
		nik_ces auto i = CD::initial_index;

		template<auto c, auto l, auto... Vs, typename... Ts>
		nik_ces auto result(Ts... vs)
			{ return NIK_CHAIN(c, i, l, Vs)(vs...); }
	};

/***********************************************************************************************************************/

// first:

	template<auto... filler>
	struct T_chain<CN::first, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, l, Vs), typename T0, typename... Ts>
		nik_ces auto result(T0 v0, Ts... vs) { return v0; }
	};

/***********************************************************************************************************************/

// select:

	template<auto... filler>
	struct T_chain<CN::select, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ins = CD::instr(c, i);
			nik_ce auto n   = ins[CI::pos];
			nik_ce auto p   = unpack_<l, _par_at_, n>;

			return NIK_CHAIN_TEMPLATE(c, i),

				p

			NIK_CHAIN_RESULT(c, i, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/

// front:

	template<auto... filler>
	struct T_chain<CN::front, filler...>
	{
		template<NIK_CHAIN_PARAMS(c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ins = CD::instr(c, i);
			nik_ce auto n   = ins[CI::pos];
			nik_ce auto p   = eval<_par_left_, n, U_store_T<Ts>...>;

			return NIK_CHAIN_TEMPLATE(c, i),

				p

			NIK_CHAIN_RESULT(c, i, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/

// at:

	template<template<auto...> typename B, auto... LUs, nik_vp(p)(B<LUs...>*)>
	struct T_chain<CN::at, p>
	{
		template<NIK_CHAIN_PARAMS(c, i, l, Vs), typename TN, typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, TN vn, Ts... vs)
		{
			return NIK_CHAIN(c, i, l, Vs)(vn);
		}
	};

/***********************************************************************************************************************/

// map:

	template<auto f>
	struct T_chain<CN::map, f>
	{
		template<NIK_CHAIN_PARAMS(c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return NIK_CHAIN(c, i, l, Vs)(T_store_U<f>::template result<>(vs)...);
		}
	};

/***********************************************************************************************************************/

// mapwise:

	template<template<auto...> typename B, auto... fs, nik_vp(p)(B<fs...>*)>
	struct T_chain<CN::mapwise, p>
	{
		template<NIK_CHAIN_PARAMS(c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return NIK_CHAIN(c, i, l, Vs)(T_store_U<fs>::template result<>(vs)...);
		}
	};

/***********************************************************************************************************************/

// apply:

	template<auto f>
	struct T_chain<CN::apply, f>
	{
		template<NIK_CHAIN_PARAMS(c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return NIK_CHAIN(c, i, l, Vs)(T_store_U<f>::template result<>(vs...));
		}
	};

/***********************************************************************************************************************/

// applywise:

	template<template<auto...> typename B, auto... fs, nik_vp(p)(B<fs...>*)>
	struct T_chain<CN::applywise, p>
	{
		template<NIK_CHAIN_PARAMS(c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return NIK_CHAIN(c, i, l, Vs)(T_store_U<fs>::template result<>(vs...)...);
		}
	};

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
			right , replace , rotate ,
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
			pair , front , go_to , branch , arg , side , void_f ,
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

			nik_ces auto instr(ccontr_type c, gcindex_type i)
				{ return c[i]; }

		// navigators:

			nik_ces gkey_type next_name(ccontr_type c, gcindex_type i)
				{ return c[i+1][MI::name]; }

			nik_ces gkey_type next_note(ccontr_type c, gcindex_type i)
				{ return c[i+1][MI::note]; }

			nik_ces gindex_type next_index(ccontr_type, gcindex_type i)
				{ return i+1; }
	};

	using MD = MachineDispatch;

/***********************************************************************************************************************/

// start:

	struct T_machine_start
	{
		nik_ces auto i = MD::initial_index;

		template<auto s, auto c, auto l, auto... Vs, typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
			{ return NIK_MACHINE(s, c, i, l, Vs)(vs...); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// dependencies:

	// conceptually, modularizing out (division of labour) arg_at (focused on the registers)
	// from the arbitrary function application (separate out compose and apply) is a better
	// design, but given the nature of variadics the following might be more performant?

/***********************************************************************************************************************/

// modify type:

	template<auto Op, typename T>
	using modify_type = T_store_U<eval<Op, U_store_T<T>>>;

/***********************************************************************************************************************/

// read only:

	struct T_read_only
	{
		// default:

			template<typename T>
			nik_ces auto _result(nik_avp(T*)) { return U_store_T<T const>; }

		// pointer (recursive):

			template<typename T>
			using T_add_pointer_const = T*const;

			template<auto U>
			nik_ces auto add_pointer_const = U_store_T<T_add_pointer_const<T_store_U<U>>>;

			template<typename T>
			nik_ces auto _result(nik_avp(T**)) { return add_pointer_const<_result(U_store_T<T>)>; }

			template<typename T>
			nik_ces auto _result(nik_avp(T*const*)) { return add_pointer_const<_result(U_store_T<T>)>; }

		// reference (recursive):

			template<typename T>
			using T_add_reference_const = T&;

			template<auto U>
			nik_ces auto add_reference_const = U_store_T<T_add_reference_const<T_store_U<U>>>;

			template<typename T>
			nik_ces auto _result(nik_avp(T&)) { return add_reference_const<_result(U_store_T<T>)>; }

		template<auto U>
		nik_ces auto result = _result(U);

	}; nik_ce auto _read_only_ = U_custom_T<T_read_only>;

/***********************************************************************************************************************/

// read write:

	struct T_read_write
	{
		// default (recursive):

			template<typename T>
			nik_ces auto _result(nik_avp(T*)) { return U_store_T<T>; }

			template<typename T>
			nik_ces auto _result(nik_avp(T const*)) { return U_store_T<T>; }

		// pointer (recursive):

			template<typename T>
			using T_add_pointer = T*;

			template<auto U>
			nik_ces auto add_pointer = U_store_T<T_add_pointer<T_store_U<U>>>;

			template<typename T>
			nik_ces auto _result(nik_avp(T**)) { return add_pointer<_result(U_store_T<T>)>; }

			template<typename T>
			nik_ces auto _result(nik_avp(T*const*)) { return add_pointer<_result(U_store_T<T>)>; }

		// reference:

			template<typename T>
			using T_add_reference = T&;

			template<auto U>
			nik_ces auto add_reference = U_store_T<T_add_reference<T_store_U<U>>>;

			template<typename T>
			nik_ces auto _result(nik_avp(T&)) { return add_reference<_result(U_store_T<T>)>; }

		template<auto U>
		nik_ces auto result = _result(U);

	}; nik_ce auto _read_write_ = U_custom_T<T_read_write>;

/***********************************************************************************************************************/

// cast type:

	template<auto t>
	struct T_cast_type
	{
		template<typename T>
		nik_ces T result(T v) { return v; }
	};

	template<>
	struct T_cast_type<_read_write_>
	{
		template<typename T>
		nik_ces auto result(T v) { return (modify_type<_read_write_, T>) v; }
	};

	// syntactic sugar:

		template<auto t, typename T>
		nik_ce auto cast_type(T v) { return T_cast_type<t>::template result<>(v); }

/***********************************************************************************************************************/

// apply at:

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
			{ return T_chain_start::template result<contr, lookup>(vs...); }
	};

	// id (optimized):

		// apply id:

			template<auto n>
			struct T_apply_id_at
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
					{ return T_chain_start::template result<contr, lookup>(vs...); }
			};

		// constant:

			template<typename C, nik_vp(p)(C*)>
			struct T_apply_id_at<p>
			{
				template<typename... Ts>
				nik_ces auto result(Ts... vs) { return C::template result<>(); }
			};

		template<auto n>
		struct T_apply_at<_id_, n>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return T_apply_id_at<n>::template result<>(vs...); }
		};

	// syntactic sugar:

		template<auto f, auto n>
		nik_ce auto _apply_at_ = U_store_T<T_apply_at<f, n>>;

		template<auto n>
		nik_ce auto _arg_at_ = _apply_at_<_id_, n>;

		template<auto n, typename... Ts>
		nik_ce auto arg_at(Ts... vs) { return T_apply_at<_id_, n>::template result<>(vs...); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// first:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_machine<MN::first, MT::id, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, Vs), typename T0, typename... Ts>
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
		template<NIK_MACHINE_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins = MD::instr(c, i);
			nik_ce auto ni  = ins[MI::pos];

			return NIK_MACHINE(s, c, ni, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/

// branch:

	template<auto... filler>
	struct T_machine<MN::jump, MT::branch, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, Vs), typename BoolType, typename... Ts>
		nik_ces auto result(BoolType v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins = MD::instr(c, i);
			nik_ce auto ni  = ins[MI::pos];

			if (v) return NIK_MACHINE(s, c, ni, l, Vs)(vs...);
			else   return NIK_MACHINE(s, c,  i, l, Vs)(vs...);
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
		template<NIK_MACHINE_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n   = ins[MI::pos];
			nik_ce auto p   = unpack_<l, _par_at_, n>;

			return NIK_MACHINE_TEMPLATE(c, i),

			       p

			NIK_MACHINE_RESULT(s, c, i, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/

// pair:

	template<auto... filler>
	struct T_machine<MN::select, MT::pair, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n   = ins[MI::pos];
			nik_ce auto p   = unpack_<l, _par_at_, n>;
			nik_ce auto p0  = unpack_<p, _car_>;
			nik_ce auto p1  = unpack_<p, _cadr_>;

			return NIK_MACHINE_TEMPLATE(c, i),

			       p0, p1

			NIK_MACHINE_RESULT(s, c, i, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/

// front:

	template<auto... filler>
	struct T_machine<MN::select, MT::front, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n   = ins[MI::pos];
			nik_ce auto p   = eval<_par_left_, n, U_store_T<Ts>...>;

			return NIK_MACHINE_TEMPLATE(c, i),

			       p

			NIK_MACHINE_RESULT(s, c, i, l, Vs)(vs...);
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
		template<NIK_MACHINE_PARAMS(s, c, i, l, Vs), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n   = ins[MI::pos];
			nik_ce auto p   = eval<_par_left_, n, U_store_T<Ts>...>;

			return NIK_MACHINE_TEMPLATE(c, i),

			       p

			NIK_MACHINE_RESULT(s, c, i, l, Vs)(v, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// right:

/***********************************************************************************************************************/

// id:

	template<template<auto...> typename B, auto... LUs, nik_vp(p)(B<LUs...>*)>
	struct T_machine<MN::right, MT::id, p>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, Ts... vs) -> T_store_U<s>
			{ return NIK_MACHINE(s, c, i, l, Vs)(vs...); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// replace:

/***********************************************************************************************************************/

// id:

	template<template<auto...> typename B, auto... LUs, nik_vp(p)(B<LUs...>*)>
	struct T_machine<MN::replace, MT::id, p>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, Vs), typename T, typename TN, typename... Ts>
		nik_ces auto result(T v, T_store_U<LUs>... lvs, TN vn, Ts... vs) -> T_store_U<s>
			{ return NIK_MACHINE(s, c, i, l, Vs)(lvs..., v, vs...); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// rotate:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_machine<MN::rotate, MT::id, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, Vs), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
			{ return NIK_MACHINE(s, c, i, l, Vs)(vs..., v); }
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
		template<NIK_MACHINE_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			auto val = T_store_U<f>::template result<>(cast_type<ts>(arg_at<ns>(vs...))...);

			return NIK_MACHINE(s, c, i, l, Vs)(val, vs...);
		}
	};

/***********************************************************************************************************************/

// arg:

	template<auto... filler>
	struct T_machine<MN::call, MT::arg, filler...>
	{
		template<NIK_MACHINE_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= MD::instr(c, i);
			nik_ce auto n   = ins[MI::pos];

			auto val = arg_at<n>(vs...);

			return NIK_MACHINE(s, c, i, l, Vs)(val, vs...);
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
		template<NIK_MACHINE_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			auto val = T_store_U<f>::template result<>(cast_type<ts>(arg_at<ns>(vs...))...);

			return NIK_MACHINE(s, c, i, l, Vs)(val, vs...);
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
		template<NIK_MACHINE_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			T_store_U<f>::template result<>(cast_type<ts>(arg_at<ns>(vs...))...);

			return NIK_MACHINE(s, c, i, l, Vs)(vs...);
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
		template<NIK_MACHINE_PARAMS(s, c, i, l, Vs), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			auto val = T_store_U<f>::template result<>(cast_type<ts>(arg_at<ns>(v, vs...))...);

			return NIK_MACHINE(s, c, i, l, Vs)(val, vs...);
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
		template<NIK_MACHINE_PARAMS(s, c, i, l, Vs), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			auto val = T_store_U<f>::template result<>(cast_type<ts>(arg_at<ns>(v, vs...))...);

			return NIK_MACHINE(s, c, i, l, Vs)(val, vs...);
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
		template<NIK_MACHINE_PARAMS(s, c, i, l, Vs), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<s>
		{
			T_store_U<f>::template result<>(cast_type<ts>(arg_at<ns>(v, vs...))...);

			return NIK_MACHINE(s, c, i, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// chord:

/***********************************************************************************************************************/

// pose:

	template<auto Name, auto f, auto gs_p>
	struct T_arg_pose
	{
		nik_ces auto lookup = U_pack_Vs<f, gs_p>;

		template<auto m = _zero, auto n = _one>
		nik_ces auto contr = controller
		<
			instruction< CN::select , n >,
			instruction< Name           >,
			instruction< CN::select , m >,
			instruction< CN::apply      >,
			instruction< CN::first      >
		>;

		template<typename... Ts>
		nik_ces auto result(Ts... vs) { return T_chain_start::template result<contr<>, lookup>(vs...); }

	}; template<auto Name, auto f, auto gs_p>
		nik_ce auto _arg_pose_ = U_store_T<T_arg_pose<Name, f, gs_p>>;

	// syntactic sugar:

		template<auto f, auto... gs>
		nik_ce auto arg_subpose = _arg_pose_<CN::mapwise, f, U_pack_Vs<gs...>>;

		template<auto f, auto... gs>
		nik_ce auto arg_compose = _arg_pose_<CN::applywise, f, U_pack_Vs<gs...>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// segment:

/***********************************************************************************************************************/

	struct T_interpreter_segment
	{
		nik_ces auto sH0 = U_pack_Vs<H_id>;
		nik_ces auto  H0 = U_pack_Vs<_car_, sH0>;

		template<auto n>
		nik_ces auto contr = controller
		<
			instruction < IN::call , IT::praxis , PN::segment , n >,
			instruction < IN::halt , IT::eval                     >
		>;

		template<auto d, auto n, auto m = _zero>
		nik_ces auto result = T_interpreter_start::template result<d, contr<n>, m>(H0);
	};

	nik_ce auto _dpar_segment_ = U_custom_T<T_interpreter_segment>;
	nik_ce auto  _par_segment_ = ID::template with_initial_depth<_dpar_segment_>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

