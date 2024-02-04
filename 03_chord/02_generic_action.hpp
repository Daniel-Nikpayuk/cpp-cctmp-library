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

// generic action:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// subsource:

/***********************************************************************************************************************/

// interface:

	struct T_chord_subsource
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

	}; nik_ce auto _chord_subsource_ = U_store_T<T_chord_subsource>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// action:

/***********************************************************************************************************************/

// nop:

	template<auto... filler>
	struct T_chord_translation_action<CAAN::nop, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l) { }
	};

/***********************************************************************************************************************/

// main:

	// name:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::main_name, filler...>
		{
			nik_ces auto pad_size = 1;

			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->main_name(l->left_cselect());
				t->main_begin(pad_size);
			}
		};

	// arg:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::main_arg, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->define_op_arg(l->left_cselect()); }
		};

	// return:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::main_return, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->main_end(); }
		};

/***********************************************************************************************************************/

// declare:

	// op:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::declare_op, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->declare_op_name(l->left_cselect()); }
		};

/***********************************************************************************************************************/

// define:

	// arg:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::define_arg, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->define_arg_name(l->left_cselect()); }
		};

/***********************************************************************************************************************/

// left:

	// value:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::left_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->delay_replace(l->left_cselect()); }
		};

	// copy:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::left_copy, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->copy_replace(); }
		};

/***********************************************************************************************************************/

// apply:

	// end:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::apply_end, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->apply_end();
				t->force_replace();
			}
		};

/***********************************************************************************************************************/

// assign:

	// end:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::assign_end, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->force_replace(); }
		};

/***********************************************************************************************************************/

// subop:

	// value:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::subop_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->apply_begin(l->left_cselect()); }
		};

	// paste:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::subop_paste, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
			}
		};

	// quote:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::subop_quote, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
			}
		};

/***********************************************************************************************************************/

// subarg:

	// value:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::subarg_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->return_lookup(l->left_cselect()); }
		};

	// paste:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::subarg_paste, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
			}
		};

	// quote:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::subarg_quote, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
			}
		};

/***********************************************************************************************************************/

// mutarg:

	// value:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::mutarg_value, filler...>
		{
			nik_ces bool mute = true;

			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->return_lookup(l->left_cselect(), mute); }
		};

/***********************************************************************************************************************/

// unit:

	// value:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::unit_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->return_lookup(l->left_cselect()); }
		};

	// paste:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::unit_paste, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				// do nothing ?
			}
		};

	// quote:

		template<auto... filler>
		struct T_chord_translation_action<CAAN::unit_quote, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

