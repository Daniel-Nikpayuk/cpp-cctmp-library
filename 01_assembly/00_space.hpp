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

// space:

namespace assembly {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	template<typename T>
	nik_ce auto U_store_T					= cctmp::U_store_T<T>;

	template<auto U>
	using T_store_U						= cctmp::T_store_U<U>;

	template<template<auto...> typename B>
	nik_ce auto U_store_B					= cctmp::U_store_B<B>;

	template<typename T>
	using T_restore_T					= cctmp::T_restore_T<T>;

	template<auto... Vs>
	nik_ce auto U_pack_Vs					= cctmp::U_pack_Vs<Vs...>;

	nik_ce auto U_null_Vs					= cctmp::U_null_Vs;

	template<auto U>
	using member_type_U					= cctmp::member_type_U<U>;

	nik_ce auto H_id					= cctmp::H_id;

	template<auto V> nik_ce auto _static_callable_		= cctmp::_static_callable_<V>;
	template<auto V> nik_ce auto _static_car_		= cctmp::_static_car_<V>;
	template<auto V> nik_ce auto _static_cdr_		= cctmp::_static_cdr_<V>;

	template<auto U>
	nik_ce auto & member_value_U				= cctmp::member_value_U<U>;

	using gcbool_type					= cctmp::gcbool_type;
	using gchar_type					= cctmp::gchar_type;
	using gcchar_type					= cctmp::gcchar_type;
	using gkey_type						= cctmp::gkey_type;
	using gindex_type					= cctmp::gindex_type;
	using gcindex_type					= cctmp::gcindex_type;

	nik_ce auto U_gindex_type				= cctmp::U_gindex_type;
	nik_ce auto U_auto_bool					= cctmp::U_auto_bool;
	nik_ce auto U_auto_char					= cctmp::U_auto_char;
	nik_ce auto U_auto_int					= cctmp::U_auto_int;
	nik_ce auto U_auto_float				= cctmp::U_auto_float;

	template<auto U>
	nik_ce auto _cast_					= cctmp::_cast_<U>;

	template<auto... Vs>
	nik_ce auto _subarray_match_				= cctmp::_subarray_match_<Vs...>;

	template<auto... Us>
	nik_ce auto _string_to_builtin_				= cctmp::_string_to_builtin_<Us...>;

	template<auto... Vs>
	nik_ce auto eval					= cctmp::eval<Vs...>;

	template<auto Op, typename T>
	using modify_type					= cctmp::modify_type<Op, T>;

	nik_ce auto _from_const_				= cctmp::_from_const_;
	nik_ce auto _from_pointer_				= cctmp::_from_pointer_;
	nik_ce auto _from_reference_				= cctmp::_from_reference_;
	nik_ce auto _to_list_					= cctmp::_to_list_;
	nik_ce auto _cons_					= cctmp::_cons_;

	template<auto... Vs>
	nik_ce auto unpack_					= cctmp::unpack_<Vs...>;

	template<auto V>
	nik_ce auto is_null_					= cctmp::is_null_<V>;

	template<auto V>
	nik_ce auto car_					= cctmp::car_<V>;

	template<auto... Vs> nik_ce auto stem_			= cctmp::stem_<Vs...>;

	template<typename T>
	nik_ce auto U_custom_T					= cctmp::U_custom_T<T>;

	template<typename T, auto S>
	using sequence						= cctmp::sequence<T, S>;

	template<typename T, auto S>
	using unit_stack					= cctmp::unit_stack<T, S>;

	nik_ce auto _par_left_					= cctmp::_par_left_;
	nik_ce auto _par_right_					= cctmp::_par_right_;

	template<auto... Vs>
	nik_ce auto at_						= cctmp::at_<Vs...>;

	template<auto... Vs>
	nik_ce auto segment_					= cctmp::segment_<Vs...>;

	nik_ce auto H_env_lookup				= cctmp::H_env_lookup;
	nik_ce auto H_env_tuple					= cctmp::H_env_tuple;

	template<auto... Vs>
	using T_machine_contr					= cctmp::T_machine_contr<Vs...>;

	template<auto... Vs>
	using T_machine_action					= cctmp::T_machine_action<Vs...>;

	using MAN						= cctmp::MAN;
	using MAT						= cctmp::MAT;

	// syntactic sugar:

		template<auto U>
		using from_cptr = T_store_U<eval<_from_const_, eval<_from_pointer_, U>>>;

		template<auto U> // assumes U is a pointer type.
		using to_mptr = from_cptr<U> *;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

	template<gkey_type, gkey_type, auto...> struct T_assembly;

/***********************************************************************************************************************/

// names:

	struct AssemblyName
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			halt    ,
			type    , literal    , floating , string , lookup , arg  ,
			pad     , hash       , pound    , apply  , bind   , eval ,
			go_to   , branch     , invert   , loop   ,
			cycle   , next       , set      ,
			out_ins , out_in_ins ,
			dimension
		};
	};

	using AN = AssemblyName;

/***********************************************************************************************************************/

// notes:

	struct AssemblyNote
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			first   , front     , back     ,
			boolean , character , n_number , r_number ,
			port    , select    ,
			push    , pull      , drop     ,
			verse   , side      , replace  ,
			pred    , find      ,
			act     , act_mut   , comb_mut ,
			cont    , end       ,
			inc     , dec       ,
			dimension
		};
	};

	using AT = AssemblyNote;

/***********************************************************************************************************************/

// instructions:

	using AI = cctmp::Instr;

/***********************************************************************************************************************/

// dispatch:

	template<auto static_contr, auto _index = 0>
	using AD = cctmp::MachineDispatch<static_contr, AI, _index>;

/***********************************************************************************************************************/

// compound:

	template<auto...> struct T_assembly_compound;

	// untyped:

		template<auto c, auto i>
		struct T_assembly_compound<c, i>
		{
			template<auto l, auto t, auto r, typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				return NIK_ASSEMBLY_TEMPLATE(c, i)
					::NIK_ASSEMBLY_RESULT_TS(c, i, l, t, r, Ts...)
						(vs...);
			}
		};

	// typed:

		template<auto s, auto c, auto i>
		struct T_assembly_compound<s, c, i>
		{
			using S = T_store_U<s>;

			template<auto l, auto t, auto r, typename... Ts>
			nik_ces auto result(Ts... vs) -> S
			{
				return NIK_ASSEMBLY_TEMPLATE(c, i)
					::NIK_ASSEMBLY_RESULT_TS(c, i, l, t, r, Ts...)
						(vs...);
			}
		};

	// syntactic sugar:

		template<auto... Vs>
		nik_ce auto U_assembly_compound = U_store_T<T_assembly_compound<Vs...>>;

		nik_ce auto H_assembly_compound = U_store_B<T_assembly_compound>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

/***********************************************************************************************************************/

// p(arser )g(enerator):

	template<typename T_grammar, template<auto...> typename B_scanned, template<auto...> typename B_parsed>
	struct T_pg_static_space
	{
		// grammar:

			nik_ces auto grammar		= U_store_T<T_grammar>;
			nik_ces auto source		= _static_callable_<T_grammar::source>;

		// scanned:

			using T_scanned			= B_scanned<source>;
			nik_ces auto scanned		= U_store_T<T_scanned>;

		// parsed:

			using T_parsed			= B_parsed<scanned, grammar>;
			nik_ces auto parsed		= U_store_T<T_parsed>;
	};

/***********************************************************************************************************************/

// interface:

	template
	<
		typename T_grammar, template<auto...> typename B_pg_scanned,
		template<auto...> typename B_pg_parsed, template<auto...> typename B_parsed
	>
	struct T_static_space
	{

		// pg:

			using T_pg_space		= T_pg_static_space<T_grammar, B_pg_scanned, B_pg_parsed>;
			nik_ces auto pg_parsed		= T_pg_space::parsed;

		// parsed:

			using T_parsed			= B_parsed<pg_parsed>;
			nik_ces auto parsed		= U_store_T<T_parsed>;
	};

	// syntactic sugar:

		template
		<
			typename T_grammar, template<auto...> typename B_pg_scanned,
			template<auto...> typename B_pg_parsed, template<auto...> typename B_parsed
		>
		nik_ce auto U_static_space = U_store_T
		<
			T_static_space<T_grammar, B_pg_scanned, B_pg_parsed, B_parsed>
		>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// metapile:

/***********************************************************************************************************************/

// contr:

	template<auto space>
	struct T_metapile_static_contr
	{
		nik_ces auto static_parsed	= T_store_U<space>::parsed;
		nik_ces auto & parsed		= member_value_U<static_parsed>;

		nik_ces auto & value		= parsed.contr;
		using type			= modify_type<_from_reference_, decltype(value)>;

	}; template<auto space>
		nik_ce auto _metapile_contr_ = U_store_T<T_metapile_static_contr<space>>;

/***********************************************************************************************************************/

// interface:

	template
	<
		typename T_grammar,
		template<auto...> typename B_pg_scanned,
		template<auto...> typename B_pg_parsed,
		template<auto...> typename B_parsed,

		auto callable_source,
		auto initial_env,

		auto contr_size =  512,
		auto stack_size =  512,
		auto model_size = 1024
	>
	struct T_metapile_static_space
	{
		nik_ces auto static_pair		= _static_callable_<callable_source>;
		nik_ces auto static_source		= _static_car_<static_pair>;
		nik_ces auto static_frame		= _static_cdr_<static_pair>;

		nik_ces bool sf_is_empty		= member_value_U<static_frame>.is_empty();
		nik_ces auto static_env			= stem_
							<
								sf_is_empty, initial_env,
								_cons_, H_id, initial_env, static_frame
							>;
		nik_ces auto static_env_lookup		= unpack_<static_env, _to_list_, H_env_lookup>;
		nik_ces auto static_env_tuple		= unpack_<static_env, _to_list_, H_env_tuple>;

		template<auto pg_parsed>
		using T_parsed				= B_parsed
							<
								pg_parsed, static_source, static_env_lookup,
								contr_size, stack_size, model_size
							>;

		nik_ces auto static_space		= U_static_space<T_grammar, B_pg_scanned, B_pg_parsed, T_parsed>;
		nik_ces auto static_contr		= _metapile_contr_<static_space>;
	};

	// syntactic sugar:

		template
		<
			typename T_grammar,
			template<auto...> typename B_pg_scanned,
			template<auto...> typename B_pg_parsed,
			template<auto...> typename B_parsed,

			auto callable_source,
			auto initial_env,

			auto contr_size =  512,
			auto stack_size =  512,
			auto model_size = 1024
		>
		nik_ce auto metapile = T_metapile_static_space
		<
			T_grammar, B_pg_scanned, B_pg_parsed, B_parsed,
			callable_source, initial_env, contr_size, stack_size, model_size

		>::static_contr;

/***********************************************************************************************************************/

// apply:

	template
	<
		typename T_grammar,
		template<auto...> typename B_pg_scanned,
		template<auto...> typename B_pg_parsed,
		template<auto...> typename B_parsed,

		auto callable_source,
		auto initial_env,
		auto out_types,

		auto contr_size =  512,
		auto stack_size =  512,
		auto model_size = 1024
	>
	struct T_metapile_apply
	{
		using metapile		= T_metapile_static_space
					<
						T_grammar, B_pg_scanned, B_pg_parsed, B_parsed,
						callable_source, initial_env, contr_size, stack_size, model_size
					>;
		nik_ces auto contr	= _metapile_contr_<metapile::static_space>;

		nik_ces auto lookup	= metapile::static_env_tuple;
		nik_ces auto zero	= gindex_type{0};

		template<typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return T_assembly_compound<contr, zero>::template
				result<lookup, out_types, zero, Ts...>(vs...);
		}
	};

/***********************************************************************************************************************/

// fast apply:

	template
	<
		auto contr,
		auto callable_source,
		auto initial_env,
		auto out_types,

		auto contr_size =  512,
		auto stack_size =  512,
		auto model_size = 1024
	>
	struct T_metapile_fast_apply
	{
		nik_ces auto static_pair	= _static_callable_<callable_source>;
		nik_ces auto static_source	= _static_car_<static_pair>;
		nik_ces auto static_frame	= _static_cdr_<static_pair>;

		nik_ces bool sf_is_empty	= member_value_U<static_frame>.is_empty();
		nik_ces auto static_env		= stem_
						<
							sf_is_empty, initial_env,
							_cons_, H_id, initial_env, static_frame
						>;
		nik_ces auto lookup		= unpack_<static_env, _to_list_, H_env_tuple>;
		nik_ces auto zero		= gindex_type{0};

		template<typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return T_assembly_compound<contr, zero>::template
				result<lookup, out_types, zero, Ts...>(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// read:

/***********************************************************************************************************************/

// only:

	template<auto...>
	struct T_read
	{
		// default:

			template<typename T>
			nik_ces auto only(nik_avp(T*)) { return U_store_T<T const>; }

		// pointer (recursive):

			template<typename T>
			using T_add_pointer_const = T*const;

			template<auto U>
			nik_ces auto add_pointer_const = U_store_T<T_add_pointer_const<T_store_U<U>>>;

			template<typename T>
			nik_ces auto only(nik_avp(T**))
				{ return add_pointer_const<only(U_store_T<T>)>; }

			template<typename T>
			nik_ces auto only(nik_avp(T*const*))
				{ return add_pointer_const<only(U_store_T<T>)>; }

		// reference (recursive):

			template<typename T>
			using T_add_reference_const = T&;

			template<auto U>
			nik_ces auto add_reference_const = U_store_T<T_add_reference_const<T_store_U<U>>>;

			template<typename T>
			nik_ces auto only(nik_avp(T&))
				{ return add_reference_const<only(U_store_T<T>)>; }
	};

	// syntactic sugar:

		template<bool V, typename T>
		using read_type = typename T_read<V, U_store_T<T>>::mtype;

/***********************************************************************************************************************/

// immutable:

	template<auto U, auto... filler>
	struct T_read<false, U, filler...>
	{
		protected:

			nik_ces auto U_mtype	= T_read<filler...>::only(U);

		public:

			using mtype		= T_store_U<U_mtype>;
	};

/***********************************************************************************************************************/

// mutable:

	template<auto U, auto... filler>
	struct T_read<true, U, filler...>
	{
		public:

			using mtype		= T_store_U<U>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace assembly

