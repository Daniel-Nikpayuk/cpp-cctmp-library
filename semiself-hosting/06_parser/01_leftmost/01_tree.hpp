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

// leftmost script:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array:

/***********************************************************************************************************************/

// interface:

	template<typename Type, typename SizeType, SizeType Size>
	class leftmost_script_array : public unique_array<Type, SizeType, Size>
	{
		public:
			using base		= unique_array<Type, SizeType, Size>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			nik_ce leftmost_script_array() : base{} { }
	};

/***********************************************************************************************************************/

// trait:

	template<typename Type, typename SizeType, SizeType Size>
	struct leftmost_script_array_trait
	{
		using size_type		= typename alias<SizeType>::type;
		using size_ctype	= typename alias<SizeType>::ctype;

		using type		= leftmost_script_array<Type, size_type, Size>;
		using type_ref		= typename alias<type>::type_ref;
		using ctype		= typename alias<type>::ctype;
		using ctype_ref		= typename alias<type>::ctype_ref;
	};

	// syntactic sugar:

		template<typename Type, typename SizeType, SizeType Size>
		using lsa_trait = leftmost_script_array_trait<Type, SizeType, Size>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// plot:

/***********************************************************************************************************************/

// interface:

	template
	<
		typename PageType, typename TextType, typename SizeType,
		SizeType PageSize, SizeType TextSize = PageSize
	>
	class leftmost_script_plot : public engine::unique_plot<PageType, TextType, SizeType, PageSize, TextSize>
	{
		public:
			using base		= engine::unique_plot<PageType, TextType, SizeType, PageSize, TextSize>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			nik_ce leftmost_script_plot() : base{} { }
	};

/***********************************************************************************************************************/

// trait:

	template<typename Type, typename SizeType, SizeType PageSize, SizeType TextSize = PageSize>
	struct leftmost_script_plot_trait
	{
		using size_type		= typename alias<SizeType>::type;
		using size_ctype	= typename alias<SizeType>::ctype;

		using page_type		= engine::plot_entry<size_type>;
		using text_type		= Type;

		using type		= leftmost_script_plot<page_type, text_type, size_type, PageSize, TextSize>;
		using type_ref		= typename alias<type>::type_ref;
		using ctype		= typename alias<type>::ctype;
		using ctype_ref		= typename alias<type>::ctype_ref;
	};

	// syntactic sugar:

		template<typename Type, typename SizeType, SizeType PageSize, SizeType TextSize>
		using lsp_trait = leftmost_script_plot_trait<Type, SizeType, PageSize, TextSize>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// yield (production):

/***********************************************************************************************************************/

// body:

	template<typename SizeType>
	class leftmost_script_yield_body : public engine::parser_entry_body<SizeType>
	{
		public:

			using base		= engine::parser_entry_body<SizeType>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			nik_ce leftmost_script_yield_body() : base{} { }
			nik_ce leftmost_script_yield_body(size_ctype l) : base{l} { }
	};

/***********************************************************************************************************************/

// page:

	template<typename SizeType>
	class leftmost_script_yield_page : public engine::parser_entry_page<SizeType>
	{
		public:

			using base		= engine::parser_entry_page<SizeType>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		protected:

			bool quoted;

		public:

			nik_ce leftmost_script_yield_page() : base{}, quoted{} { }

			nik_ce bool is_quoted() const { return quoted; }

			nik_ce void set_quoted(bool q) { quoted = q; }
	};

/***********************************************************************************************************************/

// text:

	template<typename SizeType>
	class leftmost_script_yield_text : public engine::parser_entry_text<SizeType>
	{
		public:

			using base		= engine::parser_entry_text<SizeType>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			nik_ce leftmost_script_yield_text() : base{} { }
			nik_ce leftmost_script_yield_text(bool const n, size_ctype i) : base{n, i} { }
	};

/***********************************************************************************************************************/

// interface:

	template
	<
		typename BodyType, typename PageType, typename TextType, typename SizeType,
		SizeType BodySize, SizeType PageSize, SizeType TextSize = PageSize
	>
	class leftmost_script_yield	: public engine::corpus
					<
						BodyType, PageType, TextType, SizeType,
						BodySize, PageSize, TextSize
					>
	{
		public:
			using base		= engine::corpus
						<
							BodyType, PageType, TextType, SizeType,
							BodySize, PageSize, TextSize
						>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		protected:

			size_type latest;

		public:

			nik_ce leftmost_script_yield() : base{}, latest{} { }

			nik_ce size_type current() const { return latest; }

			nik_ce void set_current(size_ctype l) { latest = l; }
	};

/***********************************************************************************************************************/

// trait:

	template<typename SizeType, SizeType BodySize, SizeType PageSize, SizeType TextSize = PageSize>
	struct leftmost_script_yield_trait
	{
		using size_type		= typename alias<SizeType>::type;
		using size_ctype	= typename alias<SizeType>::ctype;

		using body_type		= leftmost_script_yield_body<size_type>;
		using page_type		= leftmost_script_yield_page<size_type>;
		using text_type		= leftmost_script_yield_text<size_type>;

		using type		= leftmost_script_yield
					<
						body_type , page_type , text_type , size_type ,
						BodySize  , PageSize  , TextSize
					>;
		using type_ref		= typename alias<type>::type_ref;
		using ctype		= typename alias<type>::ctype;
		using ctype_ref		= typename alias<type>::ctype_ref;
	};

	// syntactic sugar:

		template<typename SizeType, SizeType BodySize, SizeType PageSize, SizeType TextSize = PageSize>
		using lsy_trait = leftmost_script_yield_trait<SizeType, BodySize, PageSize, TextSize>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// leftmost parser:

/***********************************************************************************************************************/

// trait:

	template<typename String, typename ScriptSizeTrait>
	struct leftmost_script_trait
	{
		using char_type			= typename String::type;
		using char_ctype		= typename String::ctype;

		using size_type			= typename String::size_type;
		using size_ctype		= typename String::size_ctype;

		nik_ces size_type n_size	= ScriptSizeTrait::nonterminal_size;
		nik_ces size_type t_size	= ScriptSizeTrait::terminal_size;
		nik_ces size_type a_size	= ScriptSizeTrait::action_size;

		nik_ces size_type qp_size	= ScriptSizeTrait::quoted_page_size;
		nik_ces size_type qt_size	= ScriptSizeTrait::quoted_text_size;

		nik_ces size_type sp_size	= ScriptSizeTrait::symbol_page_size;
		nik_ces size_type st_size	= ScriptSizeTrait::symbol_text_size;

		nik_ces size_type gb_size	= ScriptSizeTrait::yield_body_size;
		nik_ces size_type gp_size	= ScriptSizeTrait::yield_page_size;
		nik_ces size_type gt_size	= ScriptSizeTrait::yield_text_size;

		using nonterminal_trait		= lsa_trait < size_type , size_type , n_size >;
		using terminal_trait		= lsa_trait < size_type , size_type , t_size >;
		using action_trait		= lsa_trait < size_type , size_type , a_size >;

		using quoted_trait		= lsp_trait < char_type , size_type , qp_size , qt_size >;
		using symbol_trait		= lsp_trait < char_type , size_type , sp_size , st_size >;

		using yield_trait		= lsy_trait < size_type , gb_size , gp_size , gt_size >;
	};

/***********************************************************************************************************************/

// script:

	template<typename Trait>
	class leftmost_parser_script
	{
		public:

			using nonterminal_trait		= typename Trait::nonterminal_trait;
			using nonterminal_type		= typename nonterminal_trait::type;
			using nonterminal_type_ref	= typename nonterminal_trait::type_ref;
			using nonterminal_ctype		= typename nonterminal_trait::ctype;
			using nonterminal_ctype_ref	= typename nonterminal_trait::ctype_ref;

			using terminal_trait		= typename Trait::terminal_trait;
			using terminal_type		= typename terminal_trait::type;
			using terminal_type_ref		= typename terminal_trait::type_ref;
			using terminal_ctype		= typename terminal_trait::ctype;
			using terminal_ctype_ref	= typename terminal_trait::ctype_ref;

			using action_trait		= typename Trait::action_trait;
			using action_type		= typename action_trait::type;
			using action_type_ref		= typename action_trait::type_ref;
			using action_ctype		= typename action_trait::ctype;
			using action_ctype_ref		= typename action_trait::ctype_ref;

			using quoted_trait		= typename Trait::quoted_trait;
			using quoted_type		= typename quoted_trait::type;
			using quoted_type_ref		= typename quoted_trait::type_ref;
			using quoted_ctype		= typename quoted_trait::ctype;
			using quoted_ctype_ref		= typename quoted_trait::ctype_ref;

			using symbol_trait		= typename Trait::symbol_trait;
			using symbol_type		= typename symbol_trait::type;
			using symbol_type_ref		= typename symbol_trait::type_ref;
			using symbol_ctype		= typename symbol_trait::ctype;
			using symbol_ctype_ref		= typename symbol_trait::ctype_ref;

			using yield_trait		= typename Trait::yield_trait;
			using yield_type		= typename yield_trait::type;
			using yield_type_ref		= typename yield_trait::type_ref;
			using yield_ctype		= typename yield_trait::ctype;
			using yield_ctype_ref		= typename yield_trait::ctype_ref;

		protected:

			nonterminal_type nonterm;
			   terminal_type    term;
			     action_type     act;
			     quoted_type   quote;
			     symbol_type     sym;
			      yield_type    prod;

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

			// quoted:

				nik_ce quoted_ctype_ref cquoted () const { return quote; }
				nik_ce quoted_type_ref   quoted ()       { return quote; }

			// symbol:

				nik_ce symbol_ctype_ref csymbol () const { return sym; }
				nik_ce symbol_type_ref   symbol ()       { return sym; }

			// yield:

				nik_ce yield_ctype_ref cyield () const { return prod; }
				nik_ce yield_type_ref   yield ()       { return prod; }
	};

/***********************************************************************************************************************/

// action:

	struct leftmost_parser_action
	{
		// nop:

			template<typename Script, typename Lexer>
			nik_ces void nop(Script & s, const Lexer & l) { }

		// push symbol head upsize body:

			template<typename Script, typename Lexer>
			nik_ces void push_symbol_head_upsize_body(Script & s, const Lexer & l)
			{
				auto pos = s.symbol().left_find_push(l.cbegin(), l.ccurrent());

				s.yield().set_current(pos);
			}

		// upsize body:

			template<typename Script, typename Lexer>
			nik_ces void upsize_body(Script & s, const Lexer & l)
			{
				// 1. get yield current.
				// 2. set current page as empty.
				// 3. upsize current yield body.
			}

		// set body empty:

			template<typename Script, typename Lexer>
			nik_ces void set_body_empty(Script & s, const Lexer & l)
			{
				// 1. get yield current.
				// 2. upsize current yield body.
			}

		// push symbol body:

			template<typename Script, typename Lexer>
			nik_ces void push_symbol_body(Script & s, const Lexer & l)
			{
				// 1. get yield current.
				// 2. push to current page.
				// 3. defer non/term identification.
				// 4. update current yield body.
			}

		// push symbol action:

			template<typename Script, typename Lexer>
			nik_ces void push_symbol_action(Script & s, const Lexer & l)
			{
			}

		// push quoted action:

			template<typename Script, typename Lexer>
			nik_ces void push_quoted_action(Script & s, const Lexer & l)
			{
			}

		// resolve symbol:

			template<typename Script, typename Lexer>
			nik_ces void resolve_symbol(Script & s, const Lexer & l)
			{
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::parser

