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

// translation action:

	template<action_type, auto...> struct T_chord_assembly_translation_action;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// name:

	struct ChordAssemblyActionName
	{
		enum : action_type
		{
			nop = AN::nop,

			define_name, define_arg,
			end_arg, new_line, first_line,
			label, branch, go_to, go_into, re_turn,
			application, voidication, conditional, assignment,
			copy, paste, quote, lvalue, mvalue, rvalue,
			accept,

			repeat, fold, find, sift, map, zip, glide, fasten,
			param_upsize, param_action, param_mutate, param_loop_pred,
			param_value, param_deref, param_id, param_2args, param_1arg,
			iter_upsize, iter_next, iter_pair, iter_inc, iter_dec, iter_inc_dec,
			iter_dec_inc, iter_value, iter_deref, iter_id, iter_none,
			left_closed, left_open, right_closed, right_open,

			dimension
		};

	}; using CAAN = ChordAssemblyActionName;

/***********************************************************************************************************************/

// nop:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::nop, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l) { }
	};

// define name:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::define_name, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->append_name(l); }
	};

// define arg:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::define_arg, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->append_arg(l); }
	};

// end arg:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::end_arg, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->set_arity(); }
	};

// first line:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::first_line, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->first_line(); }
	};

// new line:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::new_line, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->append_line();
			t->update_copy_paste();
		}
	};

// label:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::label, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->set_kind(Context::label);
			t->append_entry(l, Sign::label, t->label.size());
			t->tag_label();
		}
	};

// branch:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::branch, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->set_kind(Context::branch);
			t->append_entry(l, Sign::jump);
			t->tag_branch();
		}
	};

// goto:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::go_to, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->set_kind(Context::go_to);
			t->append_entry(l, Sign::jump);
			t->tag_goto();
		}
	};

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::go_into, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			lexeme k = *l;
			t->set_kind(Context::go_to);
			t->append_entry(&--k, Sign::jump);
			t->tag_goto();
			t->append_line();
		}
	};

// return:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::re_turn, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->set_kind(Context::re_turn); }
	};

// application:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::application, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->set_kind(Context::apply);
			t->update_lookup();
		}
	};

// voidication:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::voidication, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->set_kind(Context::apply);
			t->set_void();
			t->update_lookup();
		}
	};

// conditional:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::conditional, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->set_kind(Context::test);
			t->append_entry(l, Sign::copy);
			t->update_lookup();
		}
	};

// assignment:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::assignment, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->set_kind(Context::assign);
			t->update_lookup();
		}
	};

// copy:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::copy, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->append_entry(l, Sign::copy);
			t->set_copy();
		}
	};

// paste:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::paste, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->append_entry(l, Sign::paste); }
	};

// quote:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::quote, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

// accept:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::accept, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->resolve_lookup();
			t->resolve_jump();
		}
	};

/***********************************************************************************************************************/

// value:

	// l(eft):

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::lvalue, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto k = t->match_arguments(l);
				if (k.not_end()) t->lvalue_identifier(l, k.left_size());
				else t->lvalue_unknown(l);
			}
		};

	// m(utable):

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::mvalue, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto k = t->match_arguments(l);
				if (k.not_end()) t->mvalue_identifier(l, k.left_size());
				else { } // error
			}
		};

	// r(ight):

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::rvalue, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto k = t->match_arguments(l);
				if (k.not_end()) t->rvalue_identifier(l, k.left_size());
				else t->rvalue_unknown(l);
			}
		};

/***********************************************************************************************************************/

// chord:

	// repeat:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::repeat, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->set_chord(l, Sign::repeat); }
		};

	// fold:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::fold, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->set_chord(l, Sign::fold); }
		};

	// find:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::find, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->set_chord(l, Sign::find); }
		};

	// sift:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::sift, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->set_chord(l, Sign::sift); }
		};

	// map:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::map, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->set_chord(l, Sign::map); }
		};

	// zip:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::zip, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->set_chord(l, Sign::zip); }
		};

	// glide:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::glide, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->set_chord(l, Sign::glide); }
		};

	// fasten:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::fasten, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->set_chord(l, Sign::fasten); }
		};

// function:

	// param upsize:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::param_upsize, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->chord_level.last()->param_upsize(); }
		};

	// param action:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::param_action, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->chord_level.last()->param_upsize();
				t->chord_level.last()->set_param_val(ChordFunc::id);
				t->chord_level.last()->set_param_val(ChordFunc::deref);
			}
		};

	// param mutate:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::param_mutate, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->chord_level.last()->param_upsize();
				t->chord_level.last()->set_param_val(ChordFunc::appoint);
				t->chord_level.last()->set_param_val(ChordFunc::id);
				t->chord_level.last()->set_param_val(ChordFunc::id);
			}
		};

	// param loop pred:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::param_loop_pred, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->chord_level.last()->param_upsize();
				t->chord_level.last()->set_param_val(ChordFunc::not_equal);
				t->chord_level.last()->set_param_val(ChordFunc::id);
				t->chord_level.last()->set_param_val(ChordFunc::id);
			}
		};

	// param value:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::param_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->chord_level.last()->set_param_val(l); }
		};

	// param deref:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::param_deref, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->chord_level.last()->set_param_val(ChordFunc::deref); }
		};

	// param id:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::param_id, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->chord_level.last()->set_param_val(ChordFunc::id); }
		};

	// param 2args:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::param_2args, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->chord_level.last()->set_param_val(ChordFunc::deref);
				t->chord_level.last()->set_param_val(ChordFunc::deref);
			}
		};

	// param 1arg:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::param_1arg, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->chord_level.last()->set_param_val(ChordFunc::deref); }
		};

// iterator:

	// iter upsize:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::iter_upsize, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->chord_level.last()->iter_upsize(); }
		};

	// iter next:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::iter_next, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->chord_level.last()->iter_upsize();
				t->chord_level.last()->set_iter_val(ChordFunc::inc);
			}
		};

	// iter pair:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::iter_pair, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->chord_level.last()->iter_upsize();
				t->chord_level.last()->set_iter_val(ChordFunc::inc);
				t->chord_level.last()->set_iter_val(ChordFunc::dec);
			}
		};

	// iter inc:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::iter_inc, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->chord_level.last()->iter_upsize();
				t->chord_level.last()->set_iter_val(ChordFunc::inc);
			}
		};

	// iter dec:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::iter_dec, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->chord_level.last()->iter_upsize();
				t->chord_level.last()->set_iter_val(ChordFunc::dec);
			}
		};

	// iter inc dec:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::iter_inc_dec, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->chord_level.last()->iter_upsize();
				t->chord_level.last()->set_iter_val(ChordFunc::inc);
				t->chord_level.last()->set_iter_val(ChordFunc::dec);
			}
		};

	// iter dec inc:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::iter_dec_inc, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->chord_level.last()->iter_upsize();
				t->chord_level.last()->set_iter_val(ChordFunc::dec);
				t->chord_level.last()->set_iter_val(ChordFunc::inc);
			}
		};

	// iter value:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::iter_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->chord_level.last()->set_iter_val(l); }
		};

	// iter deref:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::iter_deref, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->chord_level.last()->set_iter_val(ChordFunc::deref); }
		};

	// iter id:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::iter_id, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->chord_level.last()->set_iter_val(ChordFunc::id); }
		};

	// iter none:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::iter_none, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ }
		};

// interval:

	// left closed:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::left_closed, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->chord_level.last()->set_left(Ival::closed); }
		};

	// left open:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::left_open, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->chord_level.last()->set_left(Ival::open); }
		};

	// right closed:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::right_closed, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->chord_level.last()->set_right(Ival::closed); }
		};

	// right open:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::right_open, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->chord_level.last()->set_right(Ival::open); }
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// interface:

	template<typename AST>
	struct T_chord_assembly_ta :
		public cctmp::T_generic_translation_action<T_chord_assembly_translation_action, AST, CAAN>
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

