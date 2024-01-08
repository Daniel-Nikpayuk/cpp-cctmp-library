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

// syntax:

namespace scheme {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	template<auto U>
	using T_store_U						= cctmp::T_store_U<U>;

	template<auto... Vs>
	using T_pack_Vs						= cctmp::T_pack_Vs<Vs...>;

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

	template<auto static_source, auto static_env_lookup, auto contr_size, auto stack_size, auto model_size>
	struct T_scheme_ast
	{
		nik_ces auto & src		= member_value_U<static_source>;
		using src_ptr			= typename member_type_U<static_source>::ctype_cptr;
		using cselect			= typename member_type_U<static_source>::cselector_type;

		nik_ces auto & cmodel		= member_value_U<static_env_lookup>;
		using path_type			= typename member_type_U<static_env_lookup>::path_type;

		using contr_type		= T_machine_contr<contr_size, stack_size>;
		using cindex			= typename contr_type::cindex;

		using model_type		= machine::T_env_model<gchar_type, gindex_type, model_size>;
		using size_type			= typename model_type::size_type;
		using env_type			= typename model_type::list_type;
		using look_var_type		= typename model_type::constant_type;
		using arg_var_type		= typename model_type::variadic_type;
		using pound_var_type		= typename model_type::compound_type;

		enum : gkey_type
		{
			src_at = 0,
			str_at,
			env_at,

			dimension
		};

		contr_type contr;
		model_type model;
		size_type arg_size;
		env_type cur_env;

		nik_ce T_scheme_ast() :

			contr{src_at, str_at, env_at},
			model{src}, arg_size{1}, cur_env{model.null_env()}

			{ initialize(); }

		nik_ce void initialize() // t->model.extend_environment(t->env) ?
			{ cur_env = model.cons(model.null_frame(), cur_env); }

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

		// lookup:

			// chain:

				nik_ce void chain_lookup_variable(const cselect & s)
				{
					auto record = model.lookup_variable(s, cur_env);

					if (record.v0) chain_lookup_model(record.v1);
					else chain_lookup_cmodel(s);
				}

					nik_ce void chain_lookup_model(cindex entry)
					{
						if (model.is_compound(entry)) chain_lookup_compound(entry);
						else chain_lookup_variadic(entry);
					}

						nik_ce void chain_lookup_compound(cindex entry)
						{
						}

						nik_ce void chain_lookup_variadic(cindex entry)
						{
							auto pos = model.variadic_pos(entry);

						//	chain_action<CAN::lookup, CAT::variable>(pos);
						}

					nik_ce void chain_lookup_cmodel(const cselect & s)
					{
						auto record = cmodel.match_variable(s);

						if (record.v0) chain_lookup_match(record.v1);
						else chain_lookup_error(s);
					}

						nik_ce void chain_lookup_match(const path_type & p)
						{
							auto pos = p.v0;
							auto num = p.v1;

						//	chain_action<CAN::lookup, CAT::parameter>(pos, num);
						}

						nik_ce void chain_lookup_error(const cselect & s)
							{ } // nothing yet.

			// asm:

				nik_ce void asm_lookup_variable(const cselect & s)
				{
					auto record = model.lookup_variable(s, cur_env);

					if (record.v0) asm_lookup_model(record.v1);
					else asm_lookup_cmodel(s);
				}

					nik_ce void asm_lookup_model(cindex entry)
					{
						if (model.is_compound(entry)) asm_lookup_compound(entry);
						else asm_lookup_variadic(entry);
					}

						nik_ce void asm_lookup_compound(cindex entry)
						{
						}

						nik_ce void asm_lookup_variadic(cindex entry)
						{
							auto pos = model.variadic_pos(entry);

							assembly_action<AAN::lookup, AAT::variable>(pos);
						}

					nik_ce void asm_lookup_cmodel(const cselect & s)
					{
						auto record = cmodel.match_variable(s);

						if (record.v0) asm_lookup_match(record.v1);
						else asm_lookup_error(s);
					}

						nik_ce void asm_lookup_match(const path_type & p)
						{
							auto pos = p.v0;
							auto num = p.v1;

							assembly_action<AAN::lookup, AAT::parameter>(pos, num);
						}

						nik_ce void asm_lookup_error(const cselect & s)
							{ } // nothing yet.
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace scheme

