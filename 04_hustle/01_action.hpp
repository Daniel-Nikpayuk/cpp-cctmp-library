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

// assembly action:

namespace hustle {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	template<typename T>
	nik_ce auto U_store_T					= cctmp::U_store_T<T>;

// assembly:

	using AN						= assembly::AN;
	using AT						= assembly::AT;
	using AAN						= assembly::AAN;
	using AAT						= assembly::AAT;

// generator:

	using action_type					= generator::action_type;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// subsource:

	struct T_hustle_subsource
	{
		nik_ces auto value			= cctmp::string_literal
							{
								"false"
								"true"
							};
		using type				= decltype(value);

		nik_ces gindex_type false_start		= 0;
		nik_ces gindex_type false_size		= 5;
		nik_ces gindex_type false_finish	= value.size() - (false_start + false_size);
		nik_ces auto false_cselect		= value.cselect(false_start, false_finish);

		nik_ces gindex_type true_start		= false_start + false_size;
		nik_ces gindex_type true_size		= 4;
		nik_ces gindex_type true_finish		= value.size() - (true_start + true_size);
		nik_ces auto true_cselect		= value.cselect(true_start, true_finish);

	}; nik_ce auto _hustle_subsource_ = U_store_T<T_hustle_subsource>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// translation action:

	template<action_type, auto...> struct T_hustle_translation_action;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// name:

	struct HustleAssemblyActionName
	{
		enum : action_type
		{
			nop = generator::AN::nop,

			// main:

				main_begin,
				main_end,
				main_name,
				main_arg,
			// define:

				define_name,
				define_arg,
				define_body,
				define_end,

			// port:

				port_lookup,
				port_number,

			// return:

				return_number,
				return_character,
				return_string,
				return_false,
				return_true,
				return_lookup,

			// pred:

				pred_end,

			// if:

				if_deduce,
				if_lookup,
				if_number,
				if_ante,
				if_conse,
				if_end,

			// op:

				op_lookup,
				op_return,

			// dimension:

				dimension
		};

	}; using HAAN = HustleAssemblyActionName;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

/***********************************************************************************************************************/

// interface:

	template<typename AST>
	struct T_hustle_ta :
		public generator::T_generic_translation_action<T_hustle_translation_action, AST, HAAN>
			{ };

	// interface:

		template<typename AST>
		struct T_hustle_action
		{
			using T_ast		= AST;

			nik_ces auto value	= T_hustle_ta<AST>{};
			using type		= decltype(value);
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// nop:

	template<auto... filler>
	struct T_hustle_translation_action<HAAN::nop, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l) { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// main:

	// begin:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::main_begin, filler...>
		{
			nik_ces auto pad_size = 1;

			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->template assembly_action< AAN::id  , AAT::begin >();
				t->template assembly_action< AAN::pad , AAT::id    >(pad_size, AT::front);

				t->inc_verse(pad_size);
			}
		};

	// end:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::main_end, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->template assembly_action<AAN::id, AAT::end>(AT::first); }
		};

	// name:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::main_name, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				using pound_var_type = typename AST::pound_var_type;

				auto left = 0;
				auto ins  = 0;
				auto val  = pound_var_type(left, ins, t->cur_env);
				t->entry  = t->model.define_compound(l->left_cselect(), val, t->cur_env);
			}
		};

	// arg:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::main_arg, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				using arg_var_type = typename AST::arg_var_type;

				auto val = arg_var_type{t->push_verse()};
				t->model.define_variable(l->left_cselect(), val, t->cur_env);
			}
		};

/***********************************************************************************************************************/

// define:

	// name:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::define_name, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				using pound_var_type = typename AST::pound_var_type;

				auto left = t->verse_size;
				auto ins  = t->contr.current(2);
				auto args = t->arg_size;
				auto val  = pound_var_type(left, ins, t->cur_env);
				auto env  = t->extend_env();
				t->entry  = t->model.define_compound(l->left_cselect(), val, env);

				t->reset_args();
				t->pound.push(args, left, env);
			}
		};

	// arg:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::define_arg, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				using arg_var_type = typename AST::arg_var_type;

				auto val = arg_var_type{t->push_verse()};
				t->model.define_variable(l->left_cselect(), val, t->cur_env);
			}
		};

	// body:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::define_body, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->template assembly_action< AAN::go_to , AAT::begin >();
				t->template assembly_action< AAN::id    , AAT::begin >();
			}
		};

	// end:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::define_end, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				using Policy = typename AST::contr_type::Policy;

				auto pop      = t->pound.pop();
				t->arg_size   = pop[0];
				t->verse_size = pop[1];
				t->cur_env    = pop[2];

				t->template assembly_action< AAN::id    , AAT::end >(AT::first);
				t->template assembly_action< AAN::go_to , AAT::end >();
			}
		};

/***********************************************************************************************************************/

// port:

	// lookup:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::port_lookup, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				using Compound = typename AST::pound_var_type::Compound;
				auto record    = t->cmodel.match_variable(l->left_cselect());

				if (t->cmrec_match(record))
				{
					auto path = t->cmrec_entry(record);

					t->model.set_value(t->entry, Compound::kind, 1); // magic number.
					t->model.set_value(t->entry, Compound::port, path.v0);
					t->model.set_value(t->entry, Compound::aux , path.v1);
				}
				else { } // error.
			}
		};

	// number:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::port_number, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				using Compound = typename AST::pound_var_type::Compound;

				t->model.set_value(t->entry, Compound::kind, 2); // magic number.
				t->model.set_value(t->entry, Compound::port, l->to_number());
			}
		};

/***********************************************************************************************************************/

// return:

	template<auto lit_name, auto... filler>
	struct T_literal_return_action
	{
		using cindex = gindex_type;

		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			auto b = t->left_size(l->cbegin());
			auto e = t->left_size(l->ccurrent());

			t->template assembly_action<AAN::literal, AAT::id>(t->ret_note, lit_name, b, e);
			t->inc_args_if();
		}
	};

	// number:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::return_number, filler...> :
			public T_literal_return_action<AN::number> { };

	// character:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::return_character, filler...> :
			public T_literal_return_action<AN::character> { };

	// string:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::return_string, filler...> :
			public T_literal_return_action<AN::string> { };

	// false:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::return_false, filler...>
		{
			using cindex = gindex_type;

			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->template assembly_action<AAN::push, AAT::instr>(AN::boolean, t->ret_note, false);
				t->inc_args_if();
			}
		};

	// true:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::return_true, filler...>
		{
			using cindex = gindex_type;

			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->template assembly_action<AAN::push, AAT::instr>(AN::boolean, t->ret_note, true);
				t->inc_args_if();
			}
		};

	// lookup:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::return_lookup, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->lookup_variable_action(l->left_cselect(), t->ret_note);
				t->inc_args_if();
			}
		};

/***********************************************************************************************************************/

// pred:

	// end:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::pred_end, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto contr_pos = t->contr.current();
				auto instr_pos = cctmp::Instr::note;
				auto value     = AT::first;

				t->contr.set_instr_value(contr_pos, instr_pos, value);
			}
		};

/***********************************************************************************************************************/

// if:

	// deduce:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::if_deduce, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->asm_note = AT::id; }
		};

	// lookup:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::if_lookup, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto record = t->cmodel.match_variable(l->left_cselect());
				auto path   = t->cmrec_entry(record);

				t->asm_note = AT::pull;
				t->asm_pos  = path.v0;
				t->asm_num  = path.v1;
			}
		};

	// number:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::if_number, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->asm_note = AT::port;
				t->asm_num  = l->to_number();
			}
		};

	// ante:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::if_ante, filler...>
		{
			template<typename AST>
			nik_ces void lookup(AST *t)
				{ t->template assembly_action<AAN::invert, AAT::lookup>(t->asm_pos, t->asm_num); }

			template<typename AST>
			nik_ces void number(AST *t)
				{ t->template assembly_action<AAN::invert, AAT::begin>(AT::port, t->asm_num); }

			template<typename AST>
			nik_ces void deduce(AST *t)
				{ t->template assembly_action<AAN::invert, AAT::begin>(AT::id); }

			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				if      (t->asm_note == AT::pull) lookup(t);
				else if (t->asm_note == AT::port) number(t);
				else                              deduce(t);
			}
		};

	// conse:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::if_conse, filler...>
		{
			nik_ces auto offset = 1;

			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->template assembly_action< AAN::invert , AAT::end   >(offset);
				t->template assembly_action< AAN::go_to  , AAT::begin >();
			}
		};

	// end:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::if_end, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->template assembly_action<AAN::go_to, AAT::end>(); }
		};

/***********************************************************************************************************************/

// op:

	// lookup:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::op_lookup, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto str       = l->left_cselect();
				auto record    = t->lookup_variable(str);
				auto is_pound  = t->is_compound(record);
				auto cret_note = t->ret_note;
				auto centry    = t->entry;

				t->ret_note    = AT::back;
				t->entry       = t->mrec_entry(record);
				t->call.push(is_pound, t->push_args(), cret_note, centry);
				t->lookup_variable_action(str, record, t->ret_note);
			}
		};

	// return:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::op_return, filler...>
		{
			using cindex = gindex_type;

			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				using Compound = typename AST::pound_var_type::Compound;

				auto pop      = t->call.pop();
				auto note     = pop[0] ? AT::verse : AT::select;
				auto name     = pop[0] ? AN::bind : AN::apply;
				auto drop     = pop[1];
				auto ret_note = pop[2];

				auto left     = t->model.get_value(t->entry, Compound::left);
				auto pos      = pop[0] ? left : drop;
				auto num      = pop[0] ? drop : 0;

				t->ret_note   = ret_note;
				t->entry      = pop[3];
				t->arg_size   = drop + (ret_note == AT::back);

				t->template assembly_action<AAN::push, AAT::instr>(AN::arg, note, pos, num);
				t->template assembly_action<AAN::push, AAT::instr>(name, ret_note);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace hustle

