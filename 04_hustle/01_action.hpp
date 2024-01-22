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

// machine:

	// machine (temporary?):

		using MAN					= machine::MAN;
		using MAT					= machine::MAT;

	// literal:

		using LN					= machine::LN;
		using LT					= machine::LT;
		using LAN					= machine::LAN;
		using LAT					= machine::LAT;

	// assembly:

		using AN					= machine::AN;
		using AT					= machine::AT;
		using AAN					= machine::AAN;
		using AAT					= machine::AAT;

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
		nik_ces auto equal_cselect		= value.cselect(equal_start, equal_finish);

		nik_ces gindex_type add_start		= equal_start + equal_size;
		nik_ces gindex_type add_size		= 3;
		nik_ces gindex_type add_finish		= value.size() - (add_start + add_size);
		nik_ces auto add_cselect		= value.cselect(add_start, add_finish);

		nik_ces gindex_type multiply_start	= add_start + add_size;
		nik_ces gindex_type multiply_size	= 8;
		nik_ces gindex_type multiply_finish	= value.size() - (multiply_start + multiply_size);
		nik_ces auto multiply_cselect		= value.cselect(multiply_start, multiply_finish);

		nik_ces gindex_type subtract_start	= multiply_start + multiply_size;
		nik_ces gindex_type subtract_size	= 8;
		nik_ces gindex_type subtract_finish	= value.size() - (subtract_start + subtract_size);
		nik_ces auto subtract_cselect		= value.cselect(subtract_start, subtract_finish);

		nik_ces gindex_type divide_start	= subtract_start + subtract_size;
		nik_ces gindex_type divide_size		= 6;
		nik_ces gindex_type divide_finish	= value.size() - (divide_start + divide_size);
		nik_ces auto divide_cselect		= value.cselect(divide_start, divide_finish);

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

			// type:

				type_number,
			//	type_zero,

			// return:

				return_boolean,
				return_number,
				return_character,
				return_string,
				return_lookup,

			// if:

				if_ante,
				if_conse,
				if_end,

			// pred:

				pred_end,

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
				t->template assembly_action< AAN::id   , AAT::begin >();
				t->template  machine_action< MAN::push , MAT::instr >(AN::arg, AT::push);
				t->template assembly_action< AAN::pad  , AAT::id    >(pad_size, AT::front);

				t->arg_size += pad_size;
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

				auto ins  = 0;
				auto left = t->verse_size;
				auto val  = pound_var_type(ins, left, t->cur_env);
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

				auto val = arg_var_type{t->verse_size++};
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

				auto ins   = t->contr.current(2);
				auto args  = t->arg_size;
				auto left  = t->verse_size;
				auto val   = pound_var_type(ins, left, t->cur_env);
				auto env   = t->extend_env();

				t->arg_size = 0;
				t->model.define_compound(l->left_cselect(), val, env);
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

				auto val = arg_var_type{t->verse_size++};
				t->model.define_variable(l->left_cselect(), val, t->cur_env);
			}
		};

	// body:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::define_body, filler...>
		{
			nik_ces auto pad_size = 1;

			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
			//	t->contr.delay_instr_value();

				t->template assembly_action< AAN::go_to , AAT::begin >();
				t->template assembly_action< AAN::id    , AAT::begin >();
				t->template  machine_action< MAN::push  , MAT::instr >(AN::arg, AT::push);
				t->template assembly_action< AAN::pad   , AAT::id    >(pad_size, AT::front);

				t->arg_size += pad_size;
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

			//	t->contr.force_instr_value(cctmp::Instr::next, Policy::relative);
			}
		};

/***********************************************************************************************************************/

// type:

	// number:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::type_number, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				using Compound = typename AST::pound_var_type::Compound;

				t->model.set_value(t->entry, Compound::typ_at, l->to_number());
			}
		};

	// zero:

	//	template<auto... filler>
	//	struct T_hustle_translation_action<HAAN::type_zero, filler...>
	//	{
	//		template<typename AST>
	//		nik_ces void result(AST *t, clexeme *l)
	//		{
	//			using Compound = typename AST::pound_var_type::Compound;

	//			t->model.set_value(t->entry, Compound::typ_at, 0);
	//		}
	//	};

/***********************************************************************************************************************/

// return:

	template<auto note, auto... filler>
	struct T_literal_return_action
	{
		using cindex = gindex_type;

		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			auto b = t->left_size(l->cbegin());
			auto e = t->left_size(l->ccurrent());

			t->template assembly_action<AAN::literal, AAT::id>(t->ret_policy, note, b, e);
			if (t->ret_policy == AT::back) ++t->arg_size;
		}
	};

	// boolean:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::return_boolean, filler...> :
			public T_literal_return_action<LT::boolean> { };

	// number:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::return_number, filler...> :
			public T_literal_return_action<LT::number> { };

	// character:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::return_character, filler...> :
			public T_literal_return_action<LT::character> { };

	// string:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::return_string, filler...> :
			public T_literal_return_action<LT::string> { };

	// lookup:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::return_lookup, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->lookup_variable_action(l->left_cselect(), t->ret_policy);
				if (t->ret_policy == AT::back) ++t->arg_size;
			}
		};

/***********************************************************************************************************************/

// if:

	// ante:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::if_ante, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->template assembly_action<AAN::invert, AAT::begin>(); }
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

// op:

	// lookup:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::op_lookup, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto str      = l->left_cselect();
				auto record   = t->lookup_variable(str);
				auto match    = record.v0;
				auto entry    = record.v1;
				auto is_pound = (match && t->model.is_compound(entry));
				auto policy   = t->ret_policy;

				t->ent.push(t->entry); // temporary.
				t->entry      = entry; // push/pop ?
				t->ret_policy = AT::back;
				t->call.push(is_pound, t->arg_size++, policy);
				t->lookup_variable_action(str, record, t->ret_policy);
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

				auto pop    = t->call.pop();
				auto name   = pop[0] ? AN::bind : AN::apply;
				auto drop   = pop[1];
				auto policy = pop[2];
				auto pos    = t->model.get_value(t->entry, Compound::typ_at);
				auto num    = t->model.get_value(t->entry, Compound::left);

				t->entry    = t->ent.pop(); // temporary.
				t->ret_policy = policy;
				t->arg_size   = drop + (policy == AT::back);
				t->template machine_action<MAN::push, MAT::instr>(AN::arg, AT::select, drop);
				t->template machine_action<MAN::push, MAT::instr>(name, policy, pos, num);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace hustle

