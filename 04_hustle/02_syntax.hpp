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

namespace hustle {

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

	template<typename T, auto S>
	using unit_stack					= cctmp::unit_stack<T, S>; // temporary.

	template<typename T, auto S>
	using triple_stack					= cctmp::triple_stack<T, S>;

	template<typename Type, auto Size>
	using sequence						= cctmp::sequence<Type, Size>;

// machine:

	template<auto... Vs>
	using T_machine_contr					= machine::T_machine_contr<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// abstract syntax tree:

/***********************************************************************************************************************/

// interface:

	template<auto static_source, auto static_env_lookup, auto contr_size, auto stack_size, auto model_size>
	struct T_hustle_ast
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
		using record_type		= typename model_type::record_type;
		using env_type			= typename model_type::list_type;
		using look_var_type		= typename model_type::constant_type;
		using arg_var_type		= typename model_type::variadic_type;
		using pound_var_type		= typename model_type::compound_type;

		using pound_stack		= triple_stack <size_type, stack_size>; // make stack sizes
		using call_stack		= triple_stack <size_type, stack_size>; // independent?
		using entry_stack		= unit_stack <size_type, stack_size>; // temporary.

		enum : gkey_type
		{
			src_at = 0,
			str_at,

			dimension
		};

		contr_type contr;
		model_type model;
		pound_stack pound; 
		call_stack call; 
		entry_stack ent; // temporary.
		env_type cur_env;
		size_type entry;
		size_type verse_size;
		size_type arg_size;
		size_type ret_policy;
		bool is_pound;

		nik_ce T_hustle_ast() :

			contr{src_at, str_at},
			model{src}, cur_env{model.extend_environment(model.null_env())},
			entry{}, verse_size{}, arg_size{}, ret_policy{AT::first}, is_pound{false}

			{ }

		nik_ce auto extend_env()
		{
			auto env = cur_env;
			cur_env  = model.extend_environment(cur_env);

			return env;
		}

		// (generic) action:

			template<auto name, auto note, typename... Ts> // temporary ?
			nik_ce void machine_action(Ts... vs) { machine::machine_action<name, note>(&contr, vs...); }

			template<auto name, auto note, typename... Ts>
			nik_ce void literal_action(Ts... vs) { machine::literal_action<name, note>(&contr, vs...); }

			template<auto name, auto note, typename... Ts>
			nik_ce void assembly_action(Ts... vs) { machine::assembly_action<name, note>(&contr, vs...); }

		// source:

			nik_ce auto left_size(src_ptr i) const { return i - src.origin(); }

		// lookup:

			nik_ce auto lookup_variable(const cselect & s)
				{ return model.lookup_variable(s, cur_env); }

			nik_ce void lookup_variable_action(const cselect & s, const record_type & record, cindex note)
			{
				if (record.v0) lookup_model_action(record.v1, note);
				else lookup_cmodel_action(s, note);
			}

			nik_ce void lookup_variable_action(const cselect & s, cindex note)
				{ lookup_variable_action(s, lookup_variable(s), note); }

			nik_ce void lookup_model_action(cindex entry, cindex note)
			{
				if (model.is_compound(entry)) return lookup_compound_action(entry);
				else                          return lookup_variadic_action(entry, note);
			}

				nik_ce void lookup_compound_action(cindex entry)
				{
					auto origin = model.compound_origin(entry);
					auto left   = model.compound_left(entry);

					machine_action<MAN::push, MAT::instr>(AN::pound, AT::back, origin, left);
				}

				nik_ce void lookup_variadic_action(cindex entry, cindex note)
				{
					auto pos = model.variadic_pos(entry);

					assembly_action<AAN::lookup, AAT::variable>(note, pos);
				}

			nik_ce void lookup_cmodel_action(const cselect & s, cindex note)
			{
				auto record = cmodel.match_variable(s);

				if (record.v0) lookup_match_action(record.v1, note);
				else lookup_error_action(s);
			}

				nik_ce void lookup_match_action(const path_type & p, cindex note)
				{
					auto pos = p.v0;
					auto num = p.v1;

					assembly_action<AAN::lookup, AAT::parameter>(note, pos, num);
				}

				nik_ce void lookup_error_action(const cselect & s)
					{ } // nothing yet.
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace hustle

