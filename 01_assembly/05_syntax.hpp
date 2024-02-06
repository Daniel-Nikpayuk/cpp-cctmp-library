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

namespace assembly {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tree:

/***********************************************************************************************************************/

// interface:

	template<auto static_source, auto static_env_lookup, auto contr_size, auto stack_size, auto model_size>
	struct T_syntax_tree
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
		using csize_type		= typename model_type::csize_type;
		using mrec_type			= typename model_type::record_type;
		using env_type			= typename model_type::list_type;
		using param_var_type		= typename model_type::parameter_type;
		using arg_var_type		= typename model_type::variadic_type;
		using pound_var_type		= typename model_type::compound_type;
		using Compound			= typename pound_var_type::Compound;

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
		size_type cur_entry;
		size_type cur_arity;
		bool cur_mute;
		cselect repl_name;
		size_type repl_pos;
		size_type lit_name;
		size_type lit_pos;
		size_type lit_num;
		size_type pad_pos;
		size_type pad_num;
		size_type ret_note;
		size_type verse_size;
		size_type arg_size;
		size_type count;

		nik_ce T_syntax_tree() :

			contr{src_at, str_at},
			model{src}, cur_env{model.null_env()},
			cur_entry{}, cur_arity{}, cur_mute{},
			repl_pos{}, lit_name{}, lit_pos{}, lit_num{},
			pad_pos{}, pad_num{}, ret_note{AT::first},
			verse_size{}, arg_size{}, count{}

			{ inc_env(); }

		// action:

			template<auto name, auto note, typename... Ts>
			nik_ce void assembly_action(Ts... vs)
				{ assembly::assembly_action<name, note>(&contr, vs...); }

		// source:

			nik_ce auto left_size(src_ptr i) const { return i - src.origin(); }

		// env:

			nik_ce auto inc_env() { cur_env = model.extend_environment(cur_env); }

			nik_ce auto push_env()
			{
				auto v = cur_env;

				inc_env();

				return v;
			}

		// count:

			nik_ce void reset_count() { count = 0; }

		// verse:

			nik_ce auto arg_pos(cindex n) const { return verse_size + n; }
			nik_ce void inc_args(cindex n = 1) { arg_size += n; }
			nik_ce void inc_args_if(cindex n = 1) { if (ret_note == AT::back) inc_args(n); }

			nik_ce auto reset_args()
			{
				auto v = arg_size;

				arg_size = verse_size;

				return v;
			}

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

		// param:

			nik_ce void param_type(const cselect & s)
				{ model.define_parameter(s, param_var_type{count++}, cur_env); }

		// main:

			nik_ce void main_name(const cselect & s)
			{
				auto left = 0;
				auto ins  = 0;
				auto val  = pound_var_type(left, ins);
				cur_entry = model.define_compound(s, val, cur_env);

				inc_verse();
			}

			nik_ce void main_begin()
			{
				auto pos = 0;
				auto pad = 1;

				assembly_action< AAN::id  , AAT::begin >();
				assembly_action< AAN::pad , AAT::id    >(pos, pad);
			}

			nik_ce void main_end() { assembly_action<AAN::id, AAT::end>(AT::first); }

		// port:

			// op:

				nik_ce void op_port_lookup(const cselect & s)
				{
					auto record = lookup_variable(s);

					if (mrec_match(record))
					{
						auto entry = mrec_entry(record);
						auto pos   = model.parameter_pos(entry);

						model.set_value(cur_entry, Compound::kind, 1); // magic number.
						model.set_value(cur_entry, Compound::port, pos);
					}
					else { } // error.
				}

			// arg:

				nik_ce void port_lookup(const cselect & s)
				{
					auto record = lookup_variable(s);

					if (mrec_match(record))
					{
						auto entry = mrec_entry(record);
						auto pos   = model.parameter_pos(entry);

						force_literal_return(pos);
					}
					else { } // error.
				}

		// declare:

			nik_ce void declare_op_name(const cselect & s)
				{ model.define_compound(s, cur_env); }

		// define:

			// op:

				nik_ce void define_op_name(const cselect & s)
				{
					auto left = verse_size;
					auto ins  = contr.current(2);
					auto val  = pound_var_type(left, ins);
					auto env  = push_env();
					cur_entry = model.define_compound(s, val, env);

					pound.push(reset_args(), left, env);
				}

				nik_ce void define_op_arity(cindex value) { cur_arity = value; }

				nik_ce void define_op_arg(const cselect & s)
					{ model.define_variable(s, arg_var_type{push_verse()}, cur_env); }

				nik_ce void define_op_begin()
				{
					assembly_action< AAN::go_to , AAT::begin >();
					assembly_action< AAN::id    , AAT::begin >();
				}

				nik_ce void define_op_end()
				{
					auto pop   = pound.pop();
					arg_size   = pop[0];
					verse_size = pop[1];
					cur_env    = pop[2];

					assembly_action< AAN::id    , AAT::end >(AT::first);
					assembly_action< AAN::go_to , AAT::end >();
				}

			// arg:

				nik_ce void define_arg_variable(const cselect & s, cindex pos)
					{ model.define_variable(s, arg_var_type{pos}, cur_env); }

				nik_ce void define_arg_variable(const cselect & s)
					{ define_arg_variable(s, push_verse()); }

				nik_ce void define_arg_names(cindex pos, cindex pad_size)
					{ assembly_action<AAN::pad, AAT::id>(pos, pad_size); }

				nik_ce void define_arg_name(const cselect & s, cindex pad_size = 1)
				{
					auto pos = push_verse();

					define_arg_variable(s, pos);
					define_arg_names(pos, pad_size);
				}

		// refine:

			// op:

				nik_ce void refine_op_name(const cselect & s)
				{
					auto record = lookup_variable(s);

					if (mrec_match(record))
					{
						auto left = verse_size;
						auto ins  = contr.current(2);
						auto env  = push_env();
						cur_entry = mrec_entry(record);

						model.set_value(cur_entry, Compound::left, left);
						model.set_value(cur_entry, Compound::ins, ins);
						pound.push(reset_args(), left, env);
					}
					else { } // error.
				}

				nik_ce void refine_op_args() { inc_args(cur_arity); }

		// apply:

			nik_ce bool is_compound(const mrec_type & record) const
				{ return (mrec_match(record) && model.is_compound(mrec_entry(record))); }

			nik_ce void apply_begin(const cselect & s)
			{
				auto record    = lookup_variable(s);
				auto is_pound  = is_compound(record);
				auto cret_note = ret_note;
				auto centry    = cur_entry;

				ret_note       = AT::back;
				cur_entry      = mrec_entry(record);
				call.push(is_pound, push_args(), cret_note, centry);
				lookup_variable_action(s, record, ret_note);
			}

			nik_ce void apply_end()
			{
				auto pop  = call.pop();
				auto note = pop[0] ? AT::verse : AT::select;
				auto name = pop[0] ? AN::bind : AN::apply;
				auto drop = pop[1];

				auto left = model.get_value(cur_entry, Compound::left);
				auto pos  = pop[0] ? left : drop;
				auto num  = pop[0] ? drop : 0;

				ret_note  = pop[2];
				cur_entry = pop[3];
				arg_size  = drop + (ret_note == AT::back);

				assembly_action<AAN::push, AAT::instr>(AN::arg, note, pos, num);
				assembly_action<AAN::push, AAT::instr>(name, ret_note); // AT::side ?
			}

		// replace:

			nik_ce void copy_replace() { repl_pos = 0; }

			nik_ce void delay_replace(const cselect & s)
			{
				repl_name = s;
				auto record = lookup_variable(s);

				if (mrec_match(record)) delay_match_replace(mrec_entry(record));
				else { } // error.
			}

			nik_ce void delay_match_replace(cindex entry)
			{
				if (model.is_compound(entry)) repl_pos = 0;
				else repl_pos = model.variadic_pos(entry);
			}

			nik_ce void force_replace() { if (repl_pos) force_verse_replace(); }
			nik_ce void force_verse_replace() { assembly_action<AAN::replace, AAT::id>(repl_pos); }

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
					else if (kind == 1) lookup_port_action  (entry, origin);
				}

				nik_ce void lookup_pound_action(cindex entry, cindex pos)
					{ assembly_action<AAN::push, AAT::instr>(AN::pound, AT::id, pos); }

				nik_ce void lookup_port_action(cindex entry, cindex pos)
				{
					auto num = model.compound_port(entry);

					assembly_action<AAN::push, AAT::instr>(AN::pound, AT::port, pos, num);
				}

				nik_ce void lookup_variadic_action(cindex entry, cindex note)
				{
					auto pos = model.variadic_pos(entry);

					if (note == AT::back) lookup_variadic_back_action(pos);
					else lookup_variadic_first_action(pos);
				}

				nik_ce void lookup_variadic_back_action(cindex pos)
					{ assembly_action<AAN::lookup, AAT::variable>(AT::back, cur_mute, pos); }

				nik_ce void lookup_variadic_first_action(cindex pos)
				{
					const bool mute = false;
					assembly_action<AAN::lookup, AAT::variable>(AT::first, mute, pos);
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

		// literal:

			nik_ce void delay_literal_return(cindex name, src_ptr b_ptr, src_ptr e_ptr)
			{
				lit_name = name;
				lit_pos  = left_size(b_ptr);
				lit_num  = left_size(e_ptr);
			}

			nik_ce void force_literal_return()
			{
				assembly_action<AAN::literal, AAT::id>(ret_note, lit_name, lit_pos, lit_num);
				inc_args_if();
			}

			nik_ce void force_literal_return(cindex pos)
			{
				assembly_action<AAN::literal, AAT::literal>
					(ret_note, pos, lit_name, lit_pos, lit_num);

				inc_args_if();
			}

		// return:

			nik_ce void return_literal(cindex name, src_ptr b_ptr, src_ptr e_ptr)
			{
				delay_literal_return(name, b_ptr, e_ptr);
				force_literal_return();
			}

			nik_ce void return_boolean(const bool value)
			{
				assembly_action<AAN::push, AAT::instr>(AN::boolean, ret_note, value);
				inc_args_if();
			}

			nik_ce void return_n_number(cindex value)
			{
				assembly_action<AAN::push, AAT::instr>(AN::n_number, ret_note, value);
				inc_args_if();
			}

			nik_ce void return_r_number(cindex head, cindex tail)
			{
				assembly_action<AAN::push, AAT::instr>(AN::r_number, ret_note, head, tail);
				inc_args_if();
			}

			nik_ce void return_lookup(const cselect & s, const bool mute = false)
			{
				cur_mute = mute;
				lookup_variable_action(s, ret_note);
				cur_mute = false;
				inc_args_if();
			}

		// conditional:

			nik_ce void if_predicate()
			{
				auto contr_pos = contr.current();
				auto instr_pos = cctmp::Instr::note;
				auto value     = AT::first;

				contr.set_instr_value(contr_pos, instr_pos, value);
			}

			nik_ce void if_ante_begin() { assembly_action<AAN::invert, AAT::begin>(AT::id); }
			nik_ce void if_ante_end(cindex offset) { assembly_action<AAN::invert, AAT::end>(offset); }

			nik_ce void if_conse_begin () { assembly_action<AAN::go_to, AAT::begin>(); }
			nik_ce void if_conse_end   () { assembly_action<AAN::go_to, AAT::end>(); }

		// pad:

			nik_ce auto padding() const  { return pad_num; }
			nik_ce void reset_padding () { pad_num = 0; }
			nik_ce void inc_padding   () { ++pad_num; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace assembly

