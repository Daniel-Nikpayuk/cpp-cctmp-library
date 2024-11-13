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

// diagnostic:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser:

	using namespace cctmp;

/***********************************************************************************************************************/

// diagnostic:

	template<typename Table, typename Tree, typename Lexer, typename Lexer::size_type Size>
	class parser_diagnostic : public engine::parser<Table, Tree, Lexer, Size>
	{
		public:

			using base			= engine::parser<Table, Tree, Lexer, Size>;

			using table_type		= typename base::table_type;
			using table_type_ptr		= typename base::table_type_ptr;
			using table_type_cptr		= typename base::table_type_cptr;
			using table_type_ref		= typename base::table_type_ref;

			using table_ctype		= typename base::table_ctype;
			using table_ctype_ptr		= typename base::table_ctype_ptr;
			using table_ctype_cptr		= typename base::table_ctype_cptr;
			using table_ctype_ref		= typename base::table_ctype_ref;

			using tree_type			= typename base::tree_type;
			using tree_type_ptr		= typename base::tree_type_ptr;
			using tree_type_cptr		= typename base::tree_type_cptr;
			using tree_type_ref		= typename base::tree_type_ref;

			using tree_ctype		= typename base::tree_ctype;
			using tree_ctype_ptr		= typename base::tree_ctype_ptr;
			using tree_ctype_cptr		= typename base::tree_ctype_cptr;
			using tree_ctype_ref		= typename base::tree_ctype_ref;

			using lexer_type		= typename base::lexer_type;
			using lexer_type_ptr		= typename base::lexer_type_ptr;
			using lexer_type_cptr		= typename base::lexer_type_cptr;
			using lexer_type_ref		= typename base::lexer_type_ref;

			using lexer_ctype		= typename base::lexer_ctype;
			using lexer_ctype_ptr		= typename base::lexer_ctype_ptr;
			using lexer_ctype_cptr		= typename base::lexer_ctype_cptr;
			using lexer_ctype_ref		= typename base::lexer_ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using stack_type		= typename base::stack_type;
			using stack_type_ptr		= typename base::stack_type_ptr;
			using stack_type_cptr		= typename base::stack_type_cptr;
			using stack_type_ref		= typename base::stack_type_ref;

			using stack_ctype		= typename base::stack_ctype;
			using stack_ctype_ptr		= typename base::stack_ctype_ptr;
			using stack_ctype_cptr		= typename base::stack_ctype_cptr;
			using stack_ctype_ref		= typename base::stack_ctype_ref;

		public:

			constexpr parser_diagnostic() { }

			constexpr parser_diagnostic(table_ctype_ref t, tree_ctype_ref r, lexer_ctype_ref l, size_ctype s) :
				base{t, r, l, s} { }

			table_type_ref table () { return base::table; }
			 tree_type_ref tree  () { return base::tree; }
			lexer_type_ref lexer () { return base::lexer; }
			stack_type_ref stack () { return base::stack; }

		protected:

			constexpr void print_stack()
			{
				auto s = base::cstack();

				printf("stack: ");
				while (s.not_empty())
				{
					auto sym = s.pop();

					printf("%c%d ", sym.is_nonterminal() ? 'n' : 't', sym.symbol());
				}
				printf("| ");
			}

			constexpr void print_string()
			{
				printf("string: ");
				if (base::clexer().not_end()) printf("t%d ", base::clexer().token());
				printf("| ");
			}

			constexpr void print_action()
			{
				auto row    = base::cstack().row();
				auto col    = base::clexer().column();
				auto action = base::ctable().cat(row, col).action();

				if (base::cstack().is_nonterminal() && action)
					{ printf("action: %d", action); }

				printf("\n");
			}

			constexpr void print_internals()
			{
				print_stack  ();
				print_string ();
				print_action ();
			}

		public:

			constexpr void translate()
			{
				lexer().find();

				while (base::unfinished())
				{
					print_internals();

					base::dispatch(base::clexer().column(), base::clexer().token());
				}

				exit();
			}

			constexpr void exit()
			{
				print_internals();

				base::exit();

				print_internals();
			}
	};

	template<typename String, typename TreeSizeTrait, typename String::size_type StackSize>
	constexpr auto make_leftmost_parser_diagnostic(const string_literal<const char, typename String::size_type> & s)
	{
		using script_trait_type		= parser::leftmost_tree_trait<String, TreeSizeTrait>;
		using script_type		= parser::leftmost_parser_tree<script_trait_type>;
		using action			= parser::leftmost_parser_action;

		using lexer_trait_type		= parser::lexer_trait<String>;
		using lexer_type		= parser::lexer<lexer_trait_type>;

		using parser_trait_type		= parser::leftmost_parser_trait<lexer_trait_type>;
		using table_type		= typename parser_trait_type::table_type;
		using table_instance		= parser::leftmost_parser_table<parser_trait_type>;

		using tree_type			= engine::parser_tree<script_type, lexer_type, TreeSizeTrait::size>;
		using parser_type		= parser_diagnostic
						<
							table_type, tree_type, lexer_type, StackSize
						>;

		auto tree	= tree_type
				{{
					action::nop                          <script_type, lexer_type>,
					action::push_unique_head             <script_type, lexer_type>,
					action::push_empty_next_body         <script_type, lexer_type>,
					action::push_next_body               <script_type, lexer_type>,
					action::push_identifier_current_body <script_type, lexer_type>,
					action::push_next_action             <script_type, lexer_type>,
					action::push_identifier_next_action  <script_type, lexer_type>,
					action::push_literal_next_action     <script_type, lexer_type>
				}};
		auto lexer	= parser::make_lexer<String>(s);
		auto start	= parser_trait_type::Nonterminal::start;

		return parser_type{table_instance::value, tree, lexer, start};
	}

/***********************************************************************************************************************/

// main:

	constexpr auto parser_main()
	{
		using char_type			= unsigned char;
		using size_type			= gindex_type;

		constexpr auto cfg		= engine::LambdaTuple::second(parser::leftmost_cfg<size_type>);

		using string_type		= encoding::utf8_char_array<char_type, size_type, cfg.size()>;
		using tree_size_trait		= parser::leftmost_tree_size_trait<string_type>;
		constexpr size_type stack_size	= 10;

		auto parser = make_leftmost_parser_diagnostic
				<string_type, tree_size_trait, stack_size>(cfg);

		parser.translate();

		return parser;
	}

