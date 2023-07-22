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
			copy, paste, quote, lvalue, mvalue, rvalue, svalue,
			accept,

			morph, morph_value, morph_id, morph_deref, morph_inc, morph_dec,

			cycle,
			cycle_param_upsize, cycle_param_action, cycle_param_mutate, cycle_param_loop_pred,
			cycle_param_value, cycle_param_deref, cycle_param_id, cycle_param_2args, cycle_param_1arg,
			cycle_iter_upsize, cycle_iter_next, cycle_iter_lpair, cycle_iter_rpair, cycle_iter_inc,
			cycle_iter_dec, cycle_iter_inc_dec, cycle_iter_dec_inc, cycle_iter_value, cycle_iter_deref,
			cycle_iter_id, cycle_iter_none, cycle_ival_left_closed, cycle_ival_left_open,
			cycle_ival_right_closed, cycle_ival_right_open, cycle_ival_lead,

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
			t->update_link();
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
			t->update_link();
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
			t->update_link();
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
			t->update_link();
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
			t->resolve_link();
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

	// s(tatic):

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::svalue, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto k = t->match_arguments(l);
				if (k.not_end()) t->svalue_identifier(l, k.left_size());
				else t->svalue_unknown(l);
			}
		};

/***********************************************************************************************************************/

// morph:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::morph, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->set_morph(l); }
	};

// parameter:

	// morph value:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::morph_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto k = t->match_arguments(l);
				if (k.not_end()) t->morph_identifier(l, k.left_size());
				else t->morph_unknown(l);
			}
		};

	// morph id:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::morph_id, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->morph_known(Morph::id); }
		};

	// morph deref:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::morph_deref, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->morph_known(Morph::deref); }
		};

	// morph inc:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::morph_inc, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->morph_known(Morph::inc); }
		};

	// morph dec:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::morph_dec, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->morph_known(Morph::dec); }
		};

/***********************************************************************************************************************/

// cycle:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cycle, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->set_cycle(l); }
	};

// parameter:

	// param upsize:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_param_upsize, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_level.last()->param_upsize(); }
		};

	// param action:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_param_action, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->cycle_level.last()->param_upsize();
				t->cycle_param_known(Morph::id);
				t->cycle_param_known(Morph::deref);
			}
		};

	// param mutate:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_param_mutate, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->cycle_level.last()->param_upsize();
				t->cycle_param_known(Morph::appoint);
				t->cycle_param_known(Morph::id);
				t->cycle_param_known(Morph::id);
			}
		};

	// param loop pred:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_param_loop_pred, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->cycle_level.last()->param_upsize();
				t->cycle_param_known(Morph::not_equal);
				t->cycle_param_known(Morph::id);
				t->cycle_param_known(Morph::id);
			}
		};

	// param value:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_param_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto k = t->match_arguments(l);
				if (k.not_end()) t->cycle_param_identifier(l, k.left_size());
				else t->cycle_param_unknown(l);
			}
		};

	// param deref:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_param_deref, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_param_known(Morph::deref); }
		};

	// param id:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_param_id, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_param_known(Morph::id); }
		};

	// param 2args:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_param_2args, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->cycle_param_known(Morph::deref);
				t->cycle_param_known(Morph::deref);
			}
		};

	// param 1arg:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_param_1arg, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_param_known(Morph::deref); }
		};

// iterator:

	// iter upsize:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_iter_upsize, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_level.last()->iter_upsize(); }
		};

	// iter next:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_iter_next, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->cycle_level.last()->iter_upsize();
				t->cycle_iter_known(Morph::inc);
			}
		};

	// iter l(eft) pair:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_iter_lpair, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->cycle_level.last()->iter_upsize();
				t->cycle_iter_known(Morph::inc);
				t->cycle_iter_known(Morph::dec);
			}
		};

	// iter r(ight) pair:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_iter_rpair, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto k = t->cycle_level.last()->iterator.last();

				t->cycle_level.last()->iterator.push(*k);
			}
		};

	// iter inc:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_iter_inc, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->cycle_level.last()->iter_upsize();
				t->cycle_iter_known(Morph::inc);
			}
		};

	// iter dec:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_iter_dec, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->cycle_level.last()->iter_upsize();
				t->cycle_iter_known(Morph::dec);
			}
		};

	// iter inc dec:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_iter_inc_dec, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->cycle_level.last()->iter_upsize();
				t->cycle_iter_known(Morph::inc);
				t->cycle_iter_known(Morph::dec);
			}
		};

	// iter dec inc:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_iter_dec_inc, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->cycle_level.last()->iter_upsize();
				t->cycle_iter_known(Morph::dec);
				t->cycle_iter_known(Morph::inc);
			}
		};

	// iter value:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_iter_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto k = t->match_arguments(l);
				if (k.not_end()) t->cycle_iter_identifier(l, k.left_size());
				else t->cycle_iter_unknown(l);
			}
		};

	// iter deref:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_iter_deref, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_iter_known(Morph::deref); }
		};

	// iter id:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_iter_id, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_iter_known(Morph::id); }
		};

	// iter none:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_iter_none, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ }
		};

// interval:

	// left closed:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_ival_left_closed, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_level.last()->set_left(Ival::closed); }
		};

	// left open:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_ival_left_open, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_level.last()->set_left(Ival::open); }
		};

	// right closed:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_ival_right_closed, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_level.last()->set_right(Ival::closed); }
		};

	// right open:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_ival_right_open, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_level.last()->set_right(Ival::open); }
		};

	// ival lead:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_ival_lead, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_level.last()->set_lead(); }
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

