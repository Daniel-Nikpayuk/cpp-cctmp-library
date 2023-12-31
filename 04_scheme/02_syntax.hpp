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

// syntax:

namespace scheme {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	template<auto U>
	using T_store_U						= cctmp::T_store_U<U>;

	template<auto U>
	using member_type_U					= cctmp::member_type_U<U>;

	template<typename Type, auto Size>
	using sequence						= cctmp::sequence<Type, Size>;

// machine:

	template<auto... Vs>
	using T_machine_contr					= machine::T_machine_contr<Vs...>;

	using CI						= machine::CI;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// abstract syntax tree:

/***********************************************************************************************************************/

// interface:

	template<auto static_source, auto contr_size, auto stack_size, auto model_size>
	struct T_scheme_ast
	{
		nik_ces auto & src	= member_value_U<static_source>;
		using src_ptr		= typename member_type_U<static_source>::ctype_cptr;

		using contr_type	= T_machine_contr<contr_size, stack_size>;
		using cindex		= typename contr_type::cindex;

		using model_type	= machine::T_env_model<gchar_type, gindex_type, model_size>;
		using size_type		= typename model_type::size_type;
		using env_type		= typename model_type::list_type;
		using variadic		= typename model_type::variadic_type;

		enum : gkey_type
		{
			rec_at = 0,
			src_at,
			env_at,
			str_at,

			dimension
		};

		contr_type contr;
		model_type model;
		size_type arg_size;
		env_type env;

		nik_ce T_scheme_ast() :

			contr{rec_at, src_at, env_at, str_at},
			model{member_value_U<static_source>}, arg_size{1}, env{model.null_env()}

			{ }

		// (generic) action:

			template<auto name, auto note, typename... Ts> // temporary ?
			nik_ce void machine_action(Ts... vs) { machine::machine_action<name, note>(&contr, vs...); }

			template<auto name, auto note, typename... Ts>
			nik_ce void literal_action(Ts... vs) { machine::literal_action<name, note>(&contr, vs...); }

			template<auto name, auto note, typename... Ts>
			nik_ce void chain_action(Ts... vs) { machine::chain_action<name, note>(&contr, vs...); }

			template<auto name, auto note, typename... Ts>
			nik_ce void assembly_action(Ts... vs) { machine::assembly_action<name, note>(&contr, vs...); }

		// source:

			nik_ce auto left_size(src_ptr i) const { return i - src.origin(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace scheme

