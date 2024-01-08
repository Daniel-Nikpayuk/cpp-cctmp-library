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

				if_ante,
				if_conse,
				if_end,

			// op:

				op_begin,
				op_end,
				op_lookup,
				op_add,
				op_multiply,
				op_subtract,
				op_divide,
				op_arg,

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
				{ } // nothing yet.
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

	// boolean:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::return_boolean, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto b = t->left_size(l->cbegin());
				auto e = t->left_size(l->ccurrent());

				t->template assembly_action<AAN::literal, AAT::id>(LT::boolean, b, e);
			}
		};

	// number:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::return_number, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto b = t->left_size(l->cbegin());
				auto e = t->left_size(l->ccurrent());

				t->template assembly_action<AAN::literal, AAT::id>(LT::number, b, e);
			}
		};

	// character:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::return_character, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto b = t->left_size(l->cbegin());
				auto e = t->left_size(l->ccurrent());

				t->template assembly_action<AAN::literal, AAT::id>(LT::character, b, e);
			}
		};

	// string:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::return_string, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto b = t->left_size(l->cbegin());
				auto e = t->left_size(l->ccurrent());

				t->template assembly_action<AAN::literal, AAT::id>(LT::string, b, e);
			}
		};

	// lookup:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::return_lookup, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->asm_lookup_variable(l->left_cselect()); }
		};

/***********************************************************************************************************************/

// if:

	// ante:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::if_ante, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->template assembly_action<AAN::invert, AAT::begin>(); }
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

	// begin:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::op_begin, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ }//t->template chain_action<AAN::eval, AAT::begin>(); }
		};

	// end:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::op_end, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ }//t->template chain_action<AAN::eval, AAT::end>(); }
		};

	// lookup:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::op_lookup, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l) { }
		};

	// add:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::op_add, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l) { }
		};

	// multiply:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::op_multiply, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l) { }
		};

	// subtract:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::op_subtract, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l) { }
		};

	// divide:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::op_divide, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l) { }
		};

	// arg:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::op_arg, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l) { }
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace scheme

