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

// tree:

namespace cctmp  {
namespace parser {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// leftmost tree:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// char plot:

/***********************************************************************************************************************/

// interface:

	template<typename CharType, typename SizeType, SizeType PageSize, SizeType TextSize = PageSize>
	struct leftmost_tree_char_plot
	{
		using char_type		= typename alias<CharType>::type;
		using char_ctype	= typename alias<CharType>::ctype;

		using size_type		= typename alias<SizeType>::type;
		using size_ctype	= typename alias<SizeType>::ctype;

		using page_type		= engine::plot_entry<size_type>;
		using text_type		= char_type;

		using type		= engine::unique_plot<page_type, text_type, size_type, PageSize, TextSize>;
		using type_ref		= typename alias<type>::type_ref;
		using ctype		= typename alias<type>::ctype;
		using ctype_ref		= typename alias<type>::ctype_ref;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// grammar:

/***********************************************************************************************************************/

// body:

	template<typename SizeType>
	class leftmost_tree_grammar_body : public engine::parser_entry_body<SizeType>
	{
		public:

			using base		= engine::parser_entry_body<SizeType>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			nik_ce leftmost_tree_grammar_body() : base{} { }
			nik_ce leftmost_tree_grammar_body(size_ctype l) : base{l} { }
	};

/***********************************************************************************************************************/

// page:

	template<typename SizeType>
	class leftmost_tree_grammar_page : public engine::parser_entry_page<SizeType>
	{
		public:

			using base		= engine::parser_entry_page<SizeType>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			nik_ce leftmost_tree_grammar_page() : base{} { }
	};

/***********************************************************************************************************************/

// text:

	template<typename SizeType>
	class leftmost_tree_grammar_text : public engine::parser_entry_text<SizeType>
	{
		public:

			using base		= engine::parser_entry_text<SizeType>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			nik_ce leftmost_tree_grammar_text() : base{} { }
			nik_ce leftmost_tree_grammar_text(bool const n, size_ctype i) : base{n, i} { }
	};

/***********************************************************************************************************************/

// interface:

	template<typename SizeType, SizeType BodySize, SizeType PageSize, SizeType TextSize = PageSize>
	struct leftmost_tree_grammar
	{
		using size_type		= typename alias<SizeType>::type;
		using size_ctype	= typename alias<SizeType>::ctype;

		using body_type		= leftmost_tree_grammar_body<size_type>;
		using page_type		= leftmost_tree_grammar_page<size_type>;
		using text_type		= leftmost_tree_grammar_text<size_type>;

		using type		= engine::corpus
					<
						body_type , page_type , text_type , size_type ,
						BodySize  , PageSize  , TextSize
					>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// leftmost parser:

/***********************************************************************************************************************/

// trait:

	template<typename String, typename TreeSizeTrait>
	struct leftmost_tree_trait
	{
		using char_type			= typename String::char_type;
		using char_ctype		= typename String::char_ctype;

		using size_type			= typename String::size_type;
		using size_ctype		= typename String::size_ctype;

		nik_ces size_type np_size	= TreeSizeTrait::nonterminal_page_size;
		nik_ces size_type nt_size	= TreeSizeTrait::nonterminal_text_size;

		nik_ces size_type tp_size	= TreeSizeTrait::terminal_page_size;
		nik_ces size_type tt_size	= TreeSizeTrait::terminal_text_size;

		nik_ces size_type ap_size	= TreeSizeTrait::action_page_size;
		nik_ces size_type at_size	= TreeSizeTrait::action_text_size;

		nik_ces size_type gb_size	= TreeSizeTrait::grammar_body_size;
		nik_ces size_type gp_size	= TreeSizeTrait::grammar_page_size;
		nik_ces size_type gt_size	= TreeSizeTrait::grammar_text_size;

		using nonterminal		= leftmost_tree_char_plot<char_type, size_type, np_size, nt_size>;
		using terminal			= leftmost_tree_char_plot<char_type, size_type, tp_size, tt_size>;
		using action			= leftmost_tree_char_plot<char_type, size_type, ap_size, at_size>;
		using grammar			= leftmost_tree_grammar<size_type, gb_size, gp_size, gt_size>;
	};

/***********************************************************************************************************************/

// tree:

	template<typename Trait>
	class leftmost_parser_tree
	{
		public:

			using nonterminal_trait		= typename Trait::nonterminal;
			using nonterminal_type		= typename nonterminal_trait::type;
			using nonterminal_type_ref	= typename nonterminal_trait::type_ref;
			using nonterminal_ctype		= typename nonterminal_trait::ctype;
			using nonterminal_ctype_ref	= typename nonterminal_trait::ctype_ref;

			using terminal_trait		= typename Trait::terminal;
			using terminal_type		= typename terminal_trait::type;
			using terminal_type_ref		= typename terminal_trait::type_ref;
			using terminal_ctype		= typename terminal_trait::ctype;
			using terminal_ctype_ref	= typename terminal_trait::ctype_ref;

			using action_trait		= typename Trait::action;
			using action_type		= typename action_trait::type;
			using action_type_ref		= typename action_trait::type_ref;
			using action_ctype		= typename action_trait::ctype;
			using action_ctype_ref		= typename action_trait::ctype_ref;

			using grammar_trait		= typename Trait::grammar;
			using grammar_type		= typename grammar_trait::type;
			using grammar_type_ref		= typename grammar_trait::type_ref;
			using grammar_ctype		= typename grammar_trait::ctype;
			using grammar_ctype_ref		= typename grammar_trait::ctype_ref;

		protected:

			nonterminal_type nonterm;
			   terminal_type    term;
			     action_type     act;
			    grammar_type    gram;

		public:

			nik_ce leftmost_parser_tree() { }

			// nonterminal:

				nik_ce nonterminal_ctype_ref cnonterminal () const { return nonterm; }
				nik_ce nonterminal_type_ref   nonterminal ()       { return nonterm; }

			// terminal:

				nik_ce terminal_ctype_ref cterminal () const { return term; }
				nik_ce terminal_type_ref   terminal ()       { return term; }

			// action:

				nik_ce action_ctype_ref caction () const { return act; }
				nik_ce action_type_ref   action ()       { return act; }

			// grammar:

				nik_ce grammar_ctype_ref cgrammar () const { return gram; }
				nik_ce grammar_type_ref   grammar ()       { return gram; }
	};

/***********************************************************************************************************************/

// action:

	struct leftmost_parser_action
	{
		// nop:

			template<typename Script, typename Lexer>
			nik_ces void nop(Script & s, const Lexer & l) { }

		// push unique head:

			template<typename Script, typename Lexer>
			nik_ces void push_unique_head(Script & s, const Lexer & l)
				{ s.nonterminal().push(l.cbegin(), l.ccurrent()); }

		// push empty next body:

			template<typename Script, typename Lexer>
			nik_ces void push_empty_next_body(Script & s, const Lexer & l)
			{
			}

		// push next body:

			template<typename Script, typename Lexer>
			nik_ces void push_next_body(Script & s, const Lexer & l)
			{
			}

		// push identifier current body:

			template<typename Script, typename Lexer>
			nik_ces void push_identifier_current_body(Script & s, const Lexer & l)
			{
			}

		// push next action:

			template<typename Script, typename Lexer>
			nik_ces void push_next_action(Script & s, const Lexer & l)
			{
			}

		// push identifier next action:

			template<typename Script, typename Lexer>
			nik_ces void push_identifier_next_action(Script & s, const Lexer & l)
			{
			}

		// push literal next action:

			template<typename Script, typename Lexer>
			nik_ces void push_literal_next_action(Script & s, const Lexer & l)
			{
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::parser

