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

// script:

namespace cctmp  {
namespace parser {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser script:

/***********************************************************************************************************************/

// leftmost:

	template<typename Nonterminal, typename Terminal, typename Action, typename Grammar>
	class leftmost_parser_script
	{
		public:

			using nonterminal_type		= typename alias<Nonterminal>::type;
			using nonterminal_type_ref	= typename alias<Nonterminal>::type_ref;

			using nonterminal_ctype		= typename alias<Nonterminal>::ctype;
			using nonterminal_ctype_ref	= typename alias<Nonterminal>::ctype_ref;

			using terminal_type		= typename alias<Terminal>::type;
			using terminal_type_ref		= typename alias<Terminal>::type_ref;

			using terminal_ctype		= typename alias<Terminal>::ctype;
			using terminal_ctype_ref	= typename alias<Terminal>::ctype_ref;

			using action_type		= typename alias<Action>::type;
			using action_type_ref		= typename alias<Action>::type_ref;

			using action_ctype		= typename alias<Action>::ctype;
			using action_ctype_ref		= typename alias<Action>::ctype_ref;

			using grammar_type		= typename alias<Grammar>::type;
			using grammar_type_ref		= typename alias<Grammar>::type_ref;

			using grammar_ctype		= typename alias<Grammar>::ctype;
			using grammar_ctype_ref		= typename alias<Grammar>::ctype_ref;

		protected:

			nonterminal_type nonterm;
			   terminal_type    term;
			     action_type     act;
			    grammar_type    gram;

		public:

			nik_ce leftmost_parser_script() { }

			// nonterminal:

				nik_ce nonterminal_ctype_ref cnonterminal () const { return nonterm; }
				nik_ce nonterminal_type_ref   nonterminal ()       { return nonterm; }

			// terminal:

				nik_ce terminal_ctype_ref cterminal () const { return term; }
				nik_ce terminal_type_ref   terminal ()       { return term; }

			// action:

				nik_ce action_ctype_ref caction () const { return act; }
				nik_ce action_type_ref   action ()       { return act; }

			// script:

				nik_ce grammar_ctype_ref cgrammar () const { return gram; }
				nik_ce grammar_type_ref   grammar ()       { return gram; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::parser

