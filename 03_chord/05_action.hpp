/************************************************************************************************************************
**
** Copyright 2022-2023 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

	// lookup:

		using LN						= machine::LN;
		using LT						= machine::LT;
		using LAN						= machine::LAN;
		using LAT						= machine::LAT;

	// chain:

		using CN						= machine::CN;
		using CT						= machine::CT;
		using CAN						= machine::CAN;
		using CAT						= machine::CAT;

	// cycle:

		using YN						= machine::YN;
		using YT						= machine::YT;
		using YAN						= machine::YAN;
		using YAT						= machine::YAT;

	// assembly:

		using AN						= machine::AN;
		using AT						= machine::AT;
		using AAN						= machine::AAN;
		using AAT						= machine::AAT;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// translation action:

	template<action_type, auto...> struct T_chord_assembly_translation_action;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// name:

	struct ChordAssemblyActionName
	{
		enum : action_type
		{
			nop = generator::AN::nop,

			// asm:

				// function:

					asm_func_begin, asm_func_arg, asm_func_end,

				// label:

					asm_label_begin, asm_label_goto_begin,

				// return:

					asm_return_begin, asm_return_end,

				// goto:

					asm_goto_begin, asm_goto_value, asm_goto_end,

				// tail:

					asm_tail_begin, asm_tail_value, asm_tail_end,

				// left:

					asm_left_value, asm_left_copy,

				// swap:

					asm_swap_begin, asm_swap_end,

				// test:

					asm_test_begin, asm_test_end,

				// branch:

					asm_branch_begin, asm_branch_value, asm_branch_end,

				// void:

					asm_void_begin, asm_void_end,

				// assign:

					asm_assign_begin, asm_assign_end,

				// apply:

					asm_apply_begin, asm_apply_end,

				// op value:

					asm_op_value, asm_op_paste, asm_op_quote, asm_op_morph, asm_op_cycle,

				// arg value:

					asm_arg_value, asm_arg_paste, asm_arg_quote, asm_arg_morph, asm_arg_cycle,

				// mut value:

					asm_mut_value,

				// unit value:

					asm_unit_value, asm_unit_paste, asm_unit_quote, asm_unit_morph, asm_unit_cycle,

			// morph:

			// cycle:

			// dimension:

				dimension
		};

	}; using CAAN = ChordAssemblyActionName;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// nop:

/***********************************************************************************************************************/

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::nop, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l) { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// asm:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// function:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_func_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->append_name(l);
			t->template assembly_action<AAN::begin, AAT::id>();
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_func_arg, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->append_arg(l); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_func_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->template assembly_action<AAN::pad, AAT::id>(t->padding); }
	};

// label:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_label_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_label_goto_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

// return:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_return_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_return_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->template assembly_action<AAN::end, AAT::id>(AT::first);

			t->update_copy_paste();
		}
	};

// goto:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_goto_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_goto_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_goto_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

// tail:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_tail_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_tail_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_tail_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

// left:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_left_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			auto k = t->match_arguments(l);
			if (k.not_end()) t->left = k.left_size();
			else { } // error.
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_left_copy, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->set_copy(); }
	};

// swap:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_swap_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_swap_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->update_copy_paste();
		}
	};

// test:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_test_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_test_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->update_copy_paste();
		}
	};

// branch:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_branch_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_branch_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_branch_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

// void:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_void_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_void_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->update_copy_paste();
		}
	};

// assign:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_assign_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_assign_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->update_copy_paste();
		}
	};

// apply:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_apply_begin, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->template assembly_action<AAN::apply, AAT::begin>(); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_apply_end, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->op_action();

			t->template assembly_action< AAN::apply   , AAT::end >(t->arg_offset());
			t->template assembly_action< AAN::replace , AAT::id  >(!t->has_copy, t->left);

			t->update_copy_paste();
		}
	};

// op value:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_op_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->word = *l; }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_op_paste, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_op_quote, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_op_morph, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_op_cycle, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

// arg value:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_arg_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->value_action(l); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_arg_paste, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->template chain_action<CAN::non, CAT::arg>(_zero); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_arg_quote, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_arg_morph, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_arg_cycle, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

// mut value:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_mut_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
		}
	};

// unit value:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_unit_value, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->unit_action(l); }
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_unit_paste, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // do nothing given return end, assign end.
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_unit_quote, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_unit_morph, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::asm_unit_cycle, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// morph:

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cycle:

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// translation action:

/***********************************************************************************************************************/

// interface:

	template<typename AST>
	struct T_chord_assembly_ta :
		public generator::T_generic_translation_action<T_chord_assembly_translation_action, AST, CAAN>
			{ };

	// interface:

		template<typename AST>
		struct T_chord_assembly_action
		{
			using T_ast		= AST;

			nik_ces auto value	= T_chord_assembly_ta<AST>{};
			using type		= decltype(value);
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

