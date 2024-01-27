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
	using triple_stack					= cctmp::triple_stack<T, S>;

	template<typename T, auto S>
	using quad_stack					= cctmp::quad_stack<T, S>;

	template<typename Type, auto Size>
	using sequence						= cctmp::sequence<Type, Size>;

	template<auto... Vs>
	using T_machine_contr					= cctmp::T_machine_contr<Vs...>;

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
		using cmpath_type		= typename member_type_U<static_env_lookup>::path_type;
		using cmrec_type		= typename member_type_U<static_env_lookup>::record_type;

		using contr_type		= T_machine_contr<contr_size, stack_size>;
		using cindex			= typename contr_type::cindex;

		using model_type		= cctmp::T_env_model<gchar_type, gindex_type, model_size>;
		using size_type			= typename model_type::size_type;
		using mrec_type			= typename model_type::record_type;
		using env_type			= typename model_type::list_type;
		using look_var_type		= typename model_type::constant_type;
		using arg_var_type		= typename model_type::variadic_type;
		using pound_var_type		= typename model_type::compound_type;

		using pound_stack		= triple_stack <size_type, stack_size>; // make stack sizes
		using call_stack		= quad_stack   <size_type, stack_size>; // independent?

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
		env_type cur_env;
		size_type entry;
		size_type asm_note;
		size_type asm_pos;
		size_type asm_num;
		size_type verse_size;
		size_type arg_size;
		size_type ret_note;
		bool is_pound;

		nik_ce T_hustle_ast() :

			contr{src_at, str_at},
			model{src}, cur_env{model.extend_environment(model.null_env())},
			entry{}, asm_note{}, asm_pos{}, asm_num{}, verse_size{},
			arg_size{}, ret_note{AT::first}, is_pound{false}

			{ }

		nik_ce auto extend_env()
		{
			auto env = cur_env;
			cur_env  = model.extend_environment(cur_env);

			return env;
		}

		// action:

			template<auto name, auto note, typename... Ts>
			nik_ce void assembly_action(Ts... vs) { assembly::assembly_action<name, note>(&contr, vs...); }

		// source:

			nik_ce auto left_size(src_ptr i) const { return i - src.origin(); }

		// verse:

			nik_ce void reset_args() { arg_size = verse_size; }
			nik_ce void inc_args(cindex n = 1) { arg_size += n; }
			nik_ce void inc_args_if(cindex n = 1) { if (ret_note == AT::back) inc_args(n); }

			nik_ce auto push_args(cindex n = 1)
			{
				auto v = arg_size;

				inc_args(n);

				return v;
			}

			nik_ce void inc_verse(cindex n = 1)
			{
				verse_size += n;
				inc_args(n);
			}

			nik_ce auto push_verse(cindex n = 1)
			{
				auto v = verse_size;

				inc_verse(n);

				return v;
			}

		// lookup:

			nik_ce auto mrec_match(const mrec_type & record) const { return record.v0; }
			nik_ce auto mrec_entry(const mrec_type & record) const { return record.v1; }

			nik_ce auto cmrec_match(const cmrec_type & record) const { return record.v0; }
			nik_ce auto cmrec_entry(const cmrec_type & record) const { return record.v1; }

			nik_ce auto lookup_variable(const cselect & s)
				{ return model.lookup_variable(s, cur_env); }

			nik_ce void lookup_variable_action(const cselect & s, const mrec_type & record, cindex note)
			{
				if (mrec_match(record)) lookup_model_action(mrec_entry(record), note);
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
					auto kind   = model.compound_kind(entry);
					auto origin = model.compound_origin(entry);

					if      (kind == 0) lookup_pound_action (entry, origin);
					else if (kind == 1) lookup_pull_action  (entry, origin);
					else if (kind == 2) lookup_port_action  (entry, origin);
				}

				nik_ce void lookup_pound_action(cindex entry, cindex pos)
					{ assembly_action<AAN::push, AAT::instr>(AN::pound, AT::id, pos); }

				nik_ce void lookup_pull_action(cindex entry, cindex pos)
				{
					auto pos0 = model.compound_port (entry);
					auto num0 = model.compound_aux  (entry);

					assembly_action<AAN::push, AAT::instr>(AN::lookup, AT::push, pos0, num0);
					assembly_action<AAN::push, AAT::instr>(AN::pound, AT::pull, pos);
				}

				nik_ce void lookup_port_action(cindex entry, cindex pos)
				{
					auto num = model.compound_port(entry);

					assembly_action<AAN::push, AAT::instr>(AN::pound, AT::port, pos, num);
				}

				nik_ce void lookup_variadic_action(cindex entry, cindex note)
				{
					auto pos = model.variadic_pos(entry);

					assembly_action<AAN::lookup, AAT::variable>(note, pos);
				}

			nik_ce void lookup_cmodel_action(const cselect & s, cindex note)
			{
				auto record = cmodel.match_variable(s);

				if (cmrec_match(record)) lookup_match_action(cmrec_entry(record), note);
				else lookup_error_action(s);
			}

				nik_ce void lookup_match_action(const cmpath_type & p, cindex note)
				{
					auto pos = p.v0;
					auto num = p.v1;

					assembly_action<AAN::lookup, AAT::parameter>(note, pos, num);
				}

				nik_ce void lookup_error_action(const cselect & s)
					{ } // nothing yet.

		// pound:

			nik_ce bool is_compound(const mrec_type & record) const
				{ return (mrec_match(record) && model.is_compound(mrec_entry(record))); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace hustle

