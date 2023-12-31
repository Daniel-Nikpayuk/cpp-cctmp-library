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

				define_name, define_arg,

			// continue:

				continue_boolean,
				continue_number,
				continue_character,
				continue_string,
				continue_lookup,

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

			// op:

				op_lookup,

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

	// name:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::define_name, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->template assembly_action<AAN::begin, AAT::id>();
				t->template assembly_action<AAN::pad, AAT::id>(t->arg_size);

				auto frame = t->model.cons(t->model.null_binding(), t->model.null_frame());
				t->env     = t->model.cons(frame, t->env); // t->model.extend_environment(t->env) ?
			}
		};

	// arg:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::define_arg, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				using variadic = typename AST::variadic;

				auto val = variadic{t->arg_size++};
				t->model.define_variable(l->left_cselect(), val, t->env);
			}
		};

/***********************************************************************************************************************/

// continue:

	// boolean:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::continue_boolean, filler...>
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
		struct T_scheme_translation_action<SAAN::continue_number, filler...>
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
		struct T_scheme_translation_action<SAAN::continue_character, filler...>
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
		struct T_scheme_translation_action<SAAN::continue_string, filler...>
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
		struct T_scheme_translation_action<SAAN::continue_lookup, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto rec = t->model.lookup_variable(l->left_cselect(), t->env);

				if (rec.v0)
				{
					auto pos = t->model.variadic_pos(rec.v1);

					t->template assembly_action<AAN::lookup, AAT::id>(pos);
				}
				// else error.
			}
		};

/***********************************************************************************************************************/

// return:

	// boolean:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::return_boolean, filler...>
		{
			using literal_action = T_scheme_translation_action<SAAN::continue_boolean, filler...>;

			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				literal_action::template result<AST>(t, l);
				t->template assembly_action<AAN::end, AAT::id>(AT::first);
			}
		};

	// number:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::return_number, filler...>
		{
			using literal_action = T_scheme_translation_action<SAAN::continue_number, filler...>;

			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				literal_action::template result<AST>(t, l);
				t->template assembly_action<AAN::end, AAT::id>(AT::first);
			}
		};

	// character:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::return_character, filler...>
		{
			using literal_action = T_scheme_translation_action<SAAN::continue_character, filler...>;

			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				literal_action::template result<AST>(t, l);
				t->template assembly_action<AAN::end, AAT::id>(AT::first);
			}
		};

	// string:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::return_string, filler...>
		{
			using literal_action = T_scheme_translation_action<SAAN::continue_string, filler...>;

			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				literal_action::template result<AST>(t, l);
				t->template assembly_action<AAN::end, AAT::id>(AT::first);
			}
		};

	// lookup:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::return_lookup, filler...>
		{
			using lookup_action = T_scheme_translation_action<SAAN::continue_lookup, filler...>;

			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				lookup_action::template result<AST>(t, l);
				t->template assembly_action<AAN::end, AAT::id>(AT::first);
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
				{ } // nothing yet.
		};

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
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->template assembly_action<AAN::invert, AAT::end>(); }
		};

/***********************************************************************************************************************/

// op:

	// lookup:

		template<auto... filler>
		struct T_scheme_translation_action<SAAN::op_lookup, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l) { }
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace scheme

