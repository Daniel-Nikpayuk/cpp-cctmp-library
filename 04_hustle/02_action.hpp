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

// action:

namespace hustle {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// subsource:

/***********************************************************************************************************************/

// interface:

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

// action:

/***********************************************************************************************************************/

// nop:

	template<auto... filler>
	struct T_hustle_translation_action<HAAN::nop, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l) { }
	};

/***********************************************************************************************************************/

// param:

	// type:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::param_type, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->param_type(l->left_cselect()); }
		};

/***********************************************************************************************************************/

// main:

	// name:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::main_name, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->main_name(l->left_cselect()); }
		};

	// arg:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::main_arg, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->define_op_arg(l->left_cselect()); }
		};

	// begin:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::main_begin, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->main_begin(); }
		};

	// end:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::main_end, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->main_end(); }
		};

/***********************************************************************************************************************/

// define:

	// name:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::define_name, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->define_op_name(l->left_cselect()); }
		};

	// arg:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::define_arg, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->define_op_arg(l->left_cselect()); }
		};

	// begin:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::define_begin, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->define_op_begin(); }
		};

	// end:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::define_end, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->define_op_end(); }
		};

/***********************************************************************************************************************/

// op port:

	// lookup:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::op_port_lookup, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->op_port_lookup(l->left_cselect()); }
		};

/***********************************************************************************************************************/

// port:

	// deduce:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::port_deduce, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->force_literal_return(); }
		};

	// lookup:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::port_lookup, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->port_lookup(l->left_cselect()); }
		};

/***********************************************************************************************************************/

// return:

	// false:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::return_false, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->delay_boolean_return(false); }
		};

	// true:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::return_true, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->delay_boolean_return(true); }
		};

	// (literal name):

		template<auto lit_name, auto... filler>
		struct T_literal_return_action
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->delay_literal_return(lit_name, l->cbegin(), l->ccurrent()); }
		};

	// n_number:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::return_n_number, filler...> :
			public T_literal_return_action<AN::n_number> { };

	// r_number:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::return_r_number, filler...> :
			public T_literal_return_action<AN::r_number> { };

	// character:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::return_character, filler...> :
			public T_literal_return_action<AN::character> { };

	// string:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::return_string, filler...> :
			public T_literal_return_action<AN::string> { };

	// lookup:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::return_lookup, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->lookup_return(l->left_cselect()); }
		};

/***********************************************************************************************************************/

// apply:

	// begin oper(ator):

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::apply_begin_oper, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->apply_begin(l->left_cselect()); }
		};

	// begin expr(ession):

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::apply_begin_expr, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->apply_begin(); }
		};

	// end:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::apply_end, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->apply_end(); }
		};

	// patch:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::apply_patch, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->apply_patch(); }
		};

	// call:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::apply_call, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->apply_call(); }
		};

/***********************************************************************************************************************/

// if:

	// begin:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::if_begin, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->if_pred_begin(); }
		};

	// ante:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::if_ante, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->if_pred_end();
				t->if_ante_begin();
			}
		};

	// conse:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::if_conse, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->if_ante_end();
				t->if_conse_begin();
			}
		};

	// end:

		template<auto... filler>
		struct T_hustle_translation_action<HAAN::if_end, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->if_conse_end(); }
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace hustle

