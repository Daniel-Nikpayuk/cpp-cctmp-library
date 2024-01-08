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

// metapiler:

namespace scheme {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	template<typename T>
	nik_ce auto U_store_T					= cctmp::U_store_T<T>;

	template<template<auto...> typename B>
	nik_ce auto U_store_B					= cctmp::U_store_B<B>;

	template<auto... Vs>
	nik_ce auto U_pack_Vs					= cctmp::U_pack_Vs<Vs...>;

	template<typename... Ts>
	nik_ce auto U_pack_Ts					= cctmp::U_pack_Ts<Ts...>;

	template<auto V>
	nik_ce auto _static_callable_				= cctmp::_static_callable_<V>;

	template<auto V>
	nik_ce auto _static_car_				= cctmp::_static_car_<V>;

	template<auto V>
	nik_ce auto _static_cdr_				= cctmp::_static_cdr_<V>;

	template<auto f>
	nik_ce auto _wrap_					= cctmp::_wrap_<f>;

	nik_ce auto H_id					= cctmp::H_id;
	nik_ce auto _from_const_				= cctmp::_from_const_;
	nik_ce auto _to_list_					= cctmp::_to_list_;
	nik_ce auto _cons_					= cctmp::_cons_;

	template<auto... Vs>
	nik_ce auto car_					= cctmp::car_<Vs...>;

	template<auto... Vs>
	nik_ce auto cdr_					= cctmp::cdr_<Vs...>;

	template<auto... Vs>
	nik_ce auto push_					= cctmp::push_<Vs...>;

	template<auto... Vs>
	nik_ce auto unpack_					= cctmp::unpack_<Vs...>;

	template<auto... Vs>
	nik_ce auto map_					= cctmp::map_<Vs...>;

	template<auto... Vs>
	nik_ce auto stem_					= cctmp::stem_<Vs...>;

	nik_ce auto _read_only_					= cctmp::_read_only_;

	nik_ce auto operator_frame				= cctmp::operator_frame;
	nik_ce auto H_env_lookup				= cctmp::H_env_lookup;
	nik_ce auto H_env_tuple					= cctmp::H_env_tuple;

// machine:

	template<auto... Vs>
	using T_assembly_compound				= machine::T_assembly_compound<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

/***********************************************************************************************************************/

// p(arser )g(enerator):

	struct T_scheme_pg_static_space
	{
		// grammar:

			using T_grammar			= T_scheme_grammar;
			nik_ces auto grammar		= U_store_T<T_grammar>;
			nik_ces auto source		= _static_callable_<T_grammar::source>;

		// scanned:

			using T_scanned			= generator::T_parser_generator_scanned<source>;
			nik_ces auto scanned		= U_store_T<T_scanned>;

		// parsed:

			using T_parsed			= generator::T_parser_generator_parsed<scanned, grammar>;
			nik_ces auto parsed		= U_store_T<T_parsed>;
	};

/***********************************************************************************************************************/

// interface:

	template<auto static_source, auto env_lookup, auto contr_size, auto stack_size, auto model_size>
	struct T_scheme_static_space
	{
		// pg:

			nik_ces auto pg_parsed		= T_scheme_pg_static_space::parsed;

		// parsed:

			using T_parsed			= T_scheme_parsed
							<
								pg_parsed, static_source, env_lookup,
								contr_size, stack_size, model_size
							>;
			nik_ces auto parsed		= U_store_T<T_parsed>;
	};

	// syntactic sugar:

		template<auto static_source, auto env_lookup, auto contr_size, auto stack_size, auto model_size>
		nik_ce auto U_scheme_static_space = U_store_T
		<
			T_scheme_static_space<static_source, env_lookup, contr_size, stack_size, model_size>
		>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// function:

/***********************************************************************************************************************/

// subsource:

	struct T_scheme_subsource
	{
		nik_ces auto value			= cctmp::string_literal
							{
								"equal"
								"add"
								"multiply"
								"subtract"
								"divide"
							};
		using type				= decltype(value);

		nik_ces gindex_type equal_start		= 0;
		nik_ces gindex_type equal_size		= 5;
		nik_ces gindex_type equal_finish	= value.size() - (equal_start + equal_size);

		nik_ces gindex_type add_start		= equal_start + equal_size;
		nik_ces gindex_type add_size		= 3;
		nik_ces gindex_type add_finish		= value.size() - (add_start + add_size);

		nik_ces gindex_type multiply_start	= add_start + add_size;
		nik_ces gindex_type multiply_size	= 8;
		nik_ces gindex_type multiply_finish	= value.size() - (multiply_start + multiply_size);

		nik_ces gindex_type subtract_start	= multiply_start + multiply_size;
		nik_ces gindex_type subtract_size	= 8;
		nik_ces gindex_type subtract_finish	= value.size() - (subtract_start + subtract_size);

		nik_ces gindex_type divide_start	= subtract_start + subtract_size;
		nik_ces gindex_type divide_size		= 6;
		nik_ces gindex_type divide_finish	= value.size() - (divide_start + divide_size);

	}; nik_ce auto _scheme_subsource_ = U_store_T<T_scheme_subsource>;

/***********************************************************************************************************************/

// contr:

	template<auto space>
	struct T_scheme_function_static_contr
	{
		nik_ces auto static_parsed	= T_store_U<space>::parsed;
		nik_ces auto & parsed		= member_value_U<static_parsed>;

		nik_ces auto & value		= parsed.contr;
		using type			= modify_type<_from_reference_, decltype(value)>;

	}; template<auto space>
		nik_ce auto _scheme_function_contr_ = U_store_T<T_scheme_function_static_contr<space>>;

/***********************************************************************************************************************/

// interface:

	template<auto...> struct T_scheme_function;

	template<auto space, auto links, auto out_type, auto... Us, nik_vp(cin_types)(T_pack_Vs<Us...>*)>
	struct T_scheme_function<space, links, out_type, cin_types>
	{
		nik_ces auto contr = _scheme_function_contr_<space>;
		using S            = T_store_U<out_type>;

		template<typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto in_types = U_pack_Ts<Ts...>;

			return T_assembly_compound<contr>::template result
			<
				out_type, links, in_types, T_store_U<Us>...

			>(vs...);
		}
	};

/***********************************************************************************************************************/

// apply:

	template<auto callable_source, auto initial_env, typename S, typename... Ts>
	nik_ce auto scheme_apply(Ts... vs)
	{
		nik_ce auto static_pair		= _static_callable_<callable_source>;
		nik_ce auto static_source	= _static_car_<static_pair>;
		nik_ce auto static_frame	= _static_cdr_<static_pair>;

		nik_ce auto op_env		= push_<initial_env, operator_frame>;
		nik_ce bool sf_is_empty		= member_value_U<static_frame>.is_empty();
		nik_ce auto static_env		= stem_<sf_is_empty, op_env, _cons_, H_id, op_env, static_frame>;
		nik_ce auto static_env_lookup	= unpack_<static_env, _to_list_, H_env_lookup>;
		nik_ce auto static_env_tuple	= unpack_<static_env, _to_list_, H_env_tuple>;

		nik_ce auto out_type		= U_store_T<S>;
		nik_ce auto rec_types		= U_pack_Vs<out_type>;
		nik_ce auto links		= U_pack_Vs<static_source, _scheme_subsource_, static_env_tuple, rec_types>;
		nik_ce auto in_types		= U_pack_Ts<Ts...>;
		nik_ce auto cin_types		= map_<in_types, _read_only_>;

		nik_ce auto contr_size		= 512;
		nik_ce auto stack_size		= 64;
		nik_ce auto model_size		= 1024;

		nik_ce auto space		= U_scheme_static_space
						<
							static_source, static_env_lookup,
							contr_size, stack_size, model_size
						>;
		using T_function		= T_scheme_function<space, links, out_type, cin_types>;

		return T_function::template result<Ts...>(vs...);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace scheme

