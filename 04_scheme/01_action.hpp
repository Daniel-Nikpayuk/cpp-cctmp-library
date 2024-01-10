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

namespace scheme {

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

	// chain:

		using CN					= machine::CN;
		using CT					= machine::CT;
		using CAN					= machine::CAN;
		using CAT					= machine::CAT;

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

	}; nik_ce auto _scheme_subsource_ = U_store_T<T_scheme_subsource>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// translation action:

	template<action_type, auto...> struct T_scheme_translation_action;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// name:

	struct SchemeAssemblyActionName
	{
		enum : action_type
		{
			nop = generator::AN::nop,

			// define:

				define_begin,
				define_end,
				define_name,
				define_arg,

			// return:

				return_boolean,
				return_number,
				return_character,
				return_string,
				return_lookup,

			// if:

				if_pred,
				if_ante,
				if_conse,
				if_end,

			// op:

				op_lookup,
				op_return,

			// dimension:

				dimension
		};

	}; using SAAN = SchemeAssemblyActionName;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

/***********************************************************************************************************************/

// interface:

	template<typename AST>
	struct T_scheme_ta :
		public generator::T_generic_translation_action<T_scheme_translation_action, AST, SAAN>
			{ };

	// interface:

		template<typename AST>
		struct T_scheme_action
		{
			using T_ast		= AST;

			nik_ces auto value	= T_scheme_ta<AST>{};
			using type		= decltype(value);
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// nop:

	template<auto... filler>
	struct T_scheme_translation_action<SAAN::nop, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l) { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// define:

	// begin:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::define_begin, filler...>
		{
			nik_ces auto pad_size = 1;

			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->template assembly_action<AAN::id, AAT::begin>();
				t->template assembly_action<AAN::pad, AAT::id>(pad_size, AT::front);
			}
		};

	// end:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::define_end, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->template assembly_action<AAN::id, AAT::end>(AT::first); }
		};

	// name:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::define_name, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				using pound_var_type = typename AST::pound_var_type;

				auto val = pound_var_type{0};
				t->model.define_compound(l->left_cselect(), val, t->cur_env);
			}
		};

	// arg:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::define_arg, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				using arg_var_type = typename AST::arg_var_type;

				auto val = arg_var_type{t->arg_size++};
				t->model.define_variable(l->left_cselect(), val, t->cur_env);
			}
		};

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
		struct T_scheme_translation_action<SAAN::return_boolean, filler...> :
			public T_literal_return_action<LT::boolean> { };

	// number:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::return_number, filler...> :
			public T_literal_return_action<LT::number> { };

	// character:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::return_character, filler...> :
			public T_literal_return_action<LT::character> { };

	// string:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::return_string, filler...> :
			public T_literal_return_action<LT::string> { };

	// lookup:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::return_lookup, filler...>
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

	// pred:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::if_pred, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->is_test = true; }
		};

	// ante:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::if_ante, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->is_test = false;
				t->template assembly_action<AAN::invert, AAT::begin>();
			}
		};

	// conse:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::if_conse, filler...>
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
		struct T_scheme_translation_action<SAAN::if_end, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				using Instr  = cctmp::Instr;
				using Policy = typename AST::contr_type::Policy;
				t->template assembly_action<AAN::go_to, AAT::end>();
			}
		};

/***********************************************************************************************************************/

// op:

	// lookup:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::op_lookup, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto str    = l->left_cselect();
				auto record = t->lookup_variable(str);
				auto pound  = (record.v0 && t->model.is_compound(record.v1));
			//	auto pound  = cctmp::apply<cctmp::_subarray_same_<>>(str, cctmp::strlit_type{"factorial"});
				auto policy = t->ret_policy;

				t->ret_policy = AT::back;
				t->call.push(pound, t->arg_size++, policy);
				t->lookup_variable_action(str, record, t->ret_policy);
			}
		};

	// return:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::op_return, filler...>
		{
			using cindex = gindex_type;

			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto pop    = t->call.pop();
				auto name   = pop[0] ? AN::bind : AN::apply;
				auto drop   = pop[1];
				auto revert = pop[2];
				auto policy = t->is_test ? AT::first : revert;

				t->ret_policy = revert;
				t->arg_size   = drop + (policy == AT::back);
				t->template machine_action<MAN::push, MAT::instr>(AN::arg , AT::select, drop);
				t->template machine_action<MAN::push, MAT::instr>(name    , policy);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace scheme

