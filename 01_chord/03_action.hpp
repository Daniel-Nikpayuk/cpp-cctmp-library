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

		// atomics:

			label, branch, go_to, tail, mvalue, lvalue, copy, first_line, new_line,

		// rules:

			rvalue, svalue, paste, quote, morph, cycle,
			define_name, define_arg, accept, re_turn, go_into,
			voidication, conditional, assignment, application,

		// morph:

			morph_value, morph_id, morph_deref, morph_inc, morph_dec,

		// cycle:

			// action:

			cycle_action_value, cycle_action_id, cycle_action_deref,

			// param:

			cycle_param_upsize, cycle_param_mutate, cycle_param_loop_pred,
			cycle_param_2args, cycle_param_1arg, cycle_param_value, cycle_param_id, cycle_param_deref,

			// ival:

			cycle_ival_action, cycle_ival_fixed, cycle_ival_left_closed,
			cycle_ival_left_open, cycle_ival_right_closed, cycle_ival_right_open,

			// iter:

			cycle_iter_inc_dec, cycle_iter_dec_inc, cycle_iter_upsize,
			cycle_iter_pair, cycle_iter_none, cycle_iter_value, cycle_iter_void,

			// tonic:

			cycle_tonic_inc_dec, cycle_tonic_dec_inc,
			cycle_tonic_pair, cycle_tonic_none, cycle_tonic_value, cycle_tonic_void,

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

// atomics:

/***********************************************************************************************************************/

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

// tail:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::tail, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

// m(utable) value:

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

// l(eft) value:

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

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// rules:

/***********************************************************************************************************************/

// r(ight) value:

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

// s(tatic) value:

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

// morph:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::morph, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->set_morph(l); }
	};

// cycle:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::cycle, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->set_cycle(l); }
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

// return:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::re_turn, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->set_kind(Context::re_turn); }
	};

// go into:

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

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// morph:

/***********************************************************************************************************************/

// value:

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

// id:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::morph_id, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->morph_known(Morph::id); }
	};

// deref:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::morph_deref, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->morph_known(Morph::deref); }
	};

// inc:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::morph_inc, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->morph_known(Morph::inc); }
	};

// dec:

	template<auto... filler>
	struct T_chord_assembly_translation_action<CAAN::morph_dec, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->morph_known(Morph::dec); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cycle:

/***********************************************************************************************************************/

// action:

	// value:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_action_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto k = t->match_arguments(l);
				if (k.not_end()) t->cycle_action_identifier(l, k.left_size());
				else t->cycle_action_unknown(l);
			}
		};

	// id:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_action_id, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_action_known(Morph::id); }
		};

	// deref:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_action_deref, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_action_known(Morph::deref); }
		};

/***********************************************************************************************************************/

// param:

	// upsize:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_param_upsize, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_level.last()->param_upsize(); }
		};

	// mutate:

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

	// loop pred:

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

	// 2args:

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

	// 1arg:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_param_1arg, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_param_known(Morph::deref); }
		};

	// value:

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

	// id:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_param_id, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_param_known(Morph::id); }
		};

	// deref:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_param_deref, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_param_known(Morph::deref); }
		};

/***********************************************************************************************************************/

// interval:

	// action:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_ival_action, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto action_size   = t->cycle_level.last()->action.size();
				auto interval_size = t->cycle_level.last()->interval.size();

				for (auto k = action_size; k != interval_size; ++k)
					t->cycle_action_known(Morph::deref);
			}
		};

	// fixed:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_ival_fixed, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->cycle_level.last()->set_fixed();

				t->cycle_level.last()->iter_upsize();
				t->cycle_iter_known(Morph::id);
				t->cycle_iter_known(Morph::id);
			}
		};

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

/***********************************************************************************************************************/

// iterator:

	// inc dec:

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

	// dec inc:

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

	// upsize:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_iter_upsize, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_level.last()->iter_upsize(); }
		};

	// pair:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_iter_pair, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->cycle_level.last()->iter_upsize();
				t->cycle_iter_known(Morph::inc);
				t->cycle_iter_known(Morph::dec);
			}
		};

	// none:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_iter_none, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ }
		};

	// value:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_iter_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				// if (l == id) t->cycle_level.last()->set_none();
				// else
				// {
					auto k = t->match_arguments(l);
					if (k.not_end()) t->cycle_iter_identifier(l, k.left_size());
					else t->cycle_iter_unknown(l);
				// }
			}
		};

	// void:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_iter_void, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_level.last()->set_void(); }
		};

/***********************************************************************************************************************/

// tonic:

	// inc dec:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_tonic_inc_dec, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->cycle_tonic_known(Morph::inc);
				t->cycle_tonic_known(Morph::dec);
			}
		};

	// dec inc:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_tonic_dec_inc, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->cycle_tonic_known(Morph::dec);
				t->cycle_tonic_known(Morph::inc);
			}
		};

	// pair:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_tonic_pair, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto k = t->cycle_level.last()->iterator.last();

				t->cycle_level.last()->tonic_iter = *k;
				t->cycle_level.last()->set_lead();
			}
		};

	// none:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_tonic_none, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ }
		};

	// value:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_tonic_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				// if (l == id) t->cycle_level.last()->tonic_set_none();
				// else
				// {
					auto k = t->match_arguments(l);
					if (k.not_end()) t->cycle_tonic_identifier(l, k.left_size());
					else t->cycle_tonic_unknown(l);
				// }
			}
		};

	// void:

		template<auto... filler>
		struct T_chord_assembly_translation_action<CAAN::cycle_tonic_void, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->cycle_level.last()->tonic_set_void(); }
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

