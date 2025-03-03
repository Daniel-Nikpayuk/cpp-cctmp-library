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

// parser:

namespace cctmp  {
namespace engine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// context-free grammar:

	template<typename SizeType>
	nik_ce auto context_free_grammar
	(
		const string_literal<const char, SizeType> & start,
		const string_literal<const char, SizeType> & grammar

	) { return pair(start, grammar); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automata:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser entry:

/***********************************************************************************************************************/

// corpus:

	//	protected:

	//		nik_ce void push_finish(size_ctype n, size_ctype text_start)
	//		{
	//			size_ctype text_finish  = base::ctext().size();
	//			size_ctype page_current = base::finish(n);

	//			body().at(n).upsize();

	//			page().at(page_current).set_start  (text_start);
	//			page().at(page_current).set_finish (text_finish);
	//		}

	//		nik_ce void set_finish(size_ctype n, size_ctype m, size_ctype text_start)
	//		{
	//			size_ctype text_finish  = base::ctext().size();
	//			size_ctype page_current = base::start(n) + m;

	//			page().at(page_current).set_start  (text_start);
	//			page().at(page_current).set_finish (text_finish);
	//		}

			//	template<typename In, typename End>
			//	nik_ce void push(size_ctype n, In in, End end)
			//	{
			//		size_ctype text_start = base::ctext().size();

			//		text().push(in, end);
			//		push_finish(n, text_start);
			//	}

			//	template<typename F, typename In, typename End>
			//	nik_ce void pushmap(size_ctype n, F f, In in, End end)
			//	{
			//		size_ctype text_start = base::ctext().size();

			//		text().pushmap(f, in, end);
			//		push_finish(n, text_start);
			//	}

			//	template<typename F, typename In, typename End>
			//	nik_ce void setmap(size_ctype n, size_ctype m, F f, In in, End end)
			//	{
			//		size_ctype text_start = base::ctext().size();

			//		text().pushmap(f, in, end);
			//		set_finish(n, m, text_start);
			//	}

/***********************************************************************************************************************/

// body:

	template<typename SizeType>
	class parser_entry_body : public corpus_entry<SizeType>
	{
		public:

			using base		= corpus_entry<SizeType>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			nik_ce parser_entry_body() : base{} { }
			nik_ce parser_entry_body(size_ctype l) : base{l} { }
	};

/***********************************************************************************************************************/

// page:

	template<typename SizeType>
	class parser_entry_page : public plot_entry<SizeType>
	{
		public:

			using base		= plot_entry<SizeType>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		protected:

			size_type act_pos;

		public:

			nik_ce parser_entry_page() : base{}, act_pos{} { }

			nik_ce size_type action() const { return act_pos; }

			nik_ce void set_action(size_ctype a) { act_pos = a; }
	};

/***********************************************************************************************************************/

// text:

	template<typename SizeType>
	class parser_entry_text
	{
		public:

			using size_type		= typename alias<SizeType>::type;
			using size_ctype	= typename alias<SizeType>::ctype;

		protected:

			bool nonterm;
			size_type index;

		public:

			nik_ce parser_entry_text() : nonterm{}, index{} { }
			nik_ce parser_entry_text(bool const n, size_ctype i) : nonterm{n}, index{i} { }

			nik_ce bool is_nonterminal () const { return nonterm; }
			nik_ce size_type symbol    () const { return index; }

			nik_ce void set_terminality (bool const n) { nonterm = n; }
			nik_ce void set_symbol      (size_ctype i) { index = i; }

			nik_ce bool operator == (const parser_entry_text & t) const
				{ return (t.nonterm == nonterm) && (t.index == index); }

			nik_ce bool operator != (const parser_entry_text & t) const
				{ return (t.nonterm != nonterm) || (t.index != index); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser table:

/***********************************************************************************************************************/

// page:

	template<typename SizeType>
	class parser_table_page : public parser_entry_page<SizeType>
	{
		public:

			using base		= parser_entry_page<SizeType>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			nik_ce parser_table_page() : base{} { }
	};

/***********************************************************************************************************************/

// text:

	template<typename SizeType>
	class parser_table_text : public parser_entry_text<SizeType>
	{
		public:

			using base		= parser_entry_text<SizeType>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			nik_ce parser_table_text() : base{} { }
			nik_ce parser_table_text(bool const n, size_ctype i) : base{n, i} { }
	};

/***********************************************************************************************************************/

// interface:

	template<typename SizeType, SizeType RowSize, SizeType ColSize>
	class parser_table	: public sparse_plottable
				<
					parser_table_page<SizeType>,
					parser_table_text<SizeType>,
					SizeType, RowSize, ColSize
				>
	{
		public:

			using page_type		= parser_table_page < SizeType >;
			using text_type		= parser_table_text < SizeType >;
			using base		= sparse_plottable<page_type, text_type, SizeType, RowSize, ColSize>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		protected:

			size_type row_pos;
			size_type col_pos;

		public:

			nik_ce parser_table() : base{}, row_pos{}, col_pos{} { }

			template<typename I, auto N, typename P, auto M, typename T, auto L>
			nik_ce parser_table(const I (&i)[N], const P (&p)[M], const T (&t)[L]) : base{i, p, t} { }

			nik_ce bool  is_valid () const { return base:: not_none (row_pos, col_pos); }
			nik_ce bool not_valid () const { return base::  is_none (row_pos, col_pos); }

			nik_ce size_type row () const { return row_pos; }
			nik_ce size_type col () const { return col_pos; }

			nik_ce auto action () const { return base::cat(row_pos, col_pos).action(); }

			nik_ce auto cbegin () const { return base::cbegin (row_pos, col_pos); }
			nik_ce auto cend   () const { return base::cend   (row_pos, col_pos); }

			nik_ce void move(size_ctype n, size_ctype m)
			{
				row_pos = n;
				col_pos = m;
			}

			template<typename F, typename In, typename End>
			nik_ce void push_entry(size_ctype n, size_ctype m, F f, In in, End end, size_ctype a)
			{
				base::setmap(n, m, f, in, end);
				base::at(n, m).set_action(a);
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser tree:

/***********************************************************************************************************************/

// interface:

	template<typename Script, typename Lexer, typename Lexer::size_type Size>
	class parser_tree // script_size_type <= lexer_size_type
	{
		public:

			using script_type		= typename alias<Script>::type;
			using script_type_ptr		= typename alias<Script>::type_ptr;
			using script_type_cptr		= typename alias<Script>::type_cptr;
			using script_type_ref		= typename alias<Script>::type_ref;

			using script_ctype		= typename alias<Script>::ctype;
			using script_ctype_ptr		= typename alias<Script>::ctype_ptr;
			using script_ctype_cptr		= typename alias<Script>::ctype_cptr;
			using script_ctype_ref		= typename alias<Script>::ctype_ref;

			using lexer_type		= typename alias<Lexer>::type;
			using lexer_type_ptr		= typename alias<Lexer>::type_ptr;
			using lexer_type_cptr		= typename alias<Lexer>::type_cptr;
			using lexer_type_ref		= typename alias<Lexer>::type_ref;

			using lexer_ctype		= typename alias<Lexer>::ctype;
			using lexer_ctype_ptr		= typename alias<Lexer>::ctype_ptr;
			using lexer_ctype_cptr		= typename alias<Lexer>::ctype_cptr;
			using lexer_ctype_ref		= typename alias<Lexer>::ctype_ref;

			using size_type			= typename Lexer::size_type;
			using size_ctype		= typename Lexer::size_ctype;

			using Action			= void(*)(script_type_ref, lexer_ctype_ref);

			using action_type		= typename alias<Action>::type;
			using action_type_ptr		= typename alias<Action>::type_ptr;
			using action_type_cptr		= typename alias<Action>::type_cptr;
			using action_type_ref		= typename alias<Action>::type_ref;

			using action_ctype		= typename alias<Action>::ctype;
			using action_ctype_ptr		= typename alias<Action>::ctype_ptr;
			using action_ctype_cptr		= typename alias<Action>::ctype_cptr;
			using action_ctype_ref		= typename alias<Action>::ctype_ref;

			using action_array_type		= array<action_type, size_type, Size>;
			using action_array_type_ptr	= typename alias<action_array_type>::type_ptr;
			using action_array_type_cptr	= typename alias<action_array_type>::type_cptr;
			using action_array_type_ref	= typename alias<action_array_type>::type_ref;

		protected:

			script_type script;
			action_array_type action;

		public:

			nik_ce parser_tree(action_ctype (&a)[Size]) : action{a} { }

			nik_ce script_ctype_ref cscript() const { return script; }

			nik_ce bool  is_nop (size_ctype n) const { return (n == 0); }
			nik_ce bool not_nop (size_ctype n) const { return (n != 0); }

			nik_ce void fast_apply(size_ctype n, lexer_ctype_ref l) { action[n](script, l); }

			nik_ce void apply(size_ctype n, lexer_ctype_ref l)
				{ if (not_nop(n)) { fast_apply(n, l); } }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser:

/***********************************************************************************************************************/

// stack:

	template<typename SizeType, SizeType Size>
	class parser_stack : public stack<parser_table_text<SizeType>, SizeType, Size>
	{
		public:

			using text_type			= parser_table_text<SizeType>;
			using base			= stack<text_type, SizeType, Size>;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce parser_stack(size_ctype start) { base::push(text_type{true, start}); }

			nik_ce bool is_nonterminal() const { return base::value().is_nonterminal(); }

			nik_ce size_type token () const { return base::value().symbol(); }
			nik_ce size_type row   () const { return token(); }

			template<typename In, typename End>
			nik_ce void replace(In in, End end)
			{
				base::pull();

				while (end != in) { base::push(*--end); }
			}
	};

/***********************************************************************************************************************/

// interface:

	template<typename Table, typename Tree, typename Lexer, typename Lexer::size_type Size>
	class parser // table_size_type, tree_size_type <= lexer_size_type
	{
		public:

			using table_type		= typename alias<Table>::type;
			using table_type_ptr		= typename alias<Table>::type_ptr;
			using table_type_cptr		= typename alias<Table>::type_cptr;
			using table_type_ref		= typename alias<Table>::type_ref;

			using table_ctype		= typename alias<Table>::ctype;
			using table_ctype_ptr		= typename alias<Table>::ctype_ptr;
			using table_ctype_cptr		= typename alias<Table>::ctype_cptr;
			using table_ctype_ref		= typename alias<Table>::ctype_ref;

			using tree_type			= typename alias<Tree>::type;
			using tree_type_ptr		= typename alias<Tree>::type_ptr;
			using tree_type_cptr		= typename alias<Tree>::type_cptr;
			using tree_type_ref		= typename alias<Tree>::type_ref;

			using tree_ctype		= typename alias<Tree>::ctype;
			using tree_ctype_ptr		= typename alias<Tree>::ctype_ptr;
			using tree_ctype_cptr		= typename alias<Tree>::ctype_cptr;
			using tree_ctype_ref		= typename alias<Tree>::ctype_ref;

			using lexer_type		= typename alias<Lexer>::type;
			using lexer_type_ptr		= typename alias<Lexer>::type_ptr;
			using lexer_type_cptr		= typename alias<Lexer>::type_cptr;
			using lexer_type_ref		= typename alias<Lexer>::type_ref;

			using lexer_ctype		= typename alias<Lexer>::ctype;
			using lexer_ctype_ptr		= typename alias<Lexer>::ctype_ptr;
			using lexer_ctype_cptr		= typename alias<Lexer>::ctype_cptr;
			using lexer_ctype_ref		= typename alias<Lexer>::ctype_ref;

			using size_type			= typename Lexer::size_type;
			using size_ctype		= typename Lexer::size_ctype;

			using stack_type		= parser_stack<size_type, Size>;
			using stack_type_ptr		= typename alias<stack_type>::type_ptr;
			using stack_type_cptr		= typename alias<stack_type>::type_cptr;
			using stack_type_ref		= typename alias<stack_type>::type_ref;

			using stack_ctype		= typename alias<stack_type>::ctype;
			using stack_ctype_ptr		= typename alias<stack_type>::ctype_ptr;
			using stack_ctype_cptr		= typename alias<stack_type>::ctype_cptr;
			using stack_ctype_ref		= typename alias<stack_type>::ctype_ref;

		protected:

			using Token			= typename Lexer::Token;

			enum Exit : size_type		{ none, lexer_only, stack_only, both, dimension };

			table_type table;
			 tree_type tree;
			lexer_type lexer;
			stack_type stack;

		public:

			nik_ce parser() { }

			nik_ce parser(table_ctype_ref t, tree_ctype_ref r, lexer_ctype_ref l, size_ctype s) :
				table{t}, tree{r}, lexer{l}, stack{s} { }

			table_ctype_ref ctable () const { return table; }
			 tree_ctype_ref ctree  () const { return tree; }
			lexer_ctype_ref clexer () const { return lexer; }
			stack_ctype_ref cstack () const { return stack; }

		public:

			nik_ce bool unfinished() const { return (lexer.not_end() && stack.not_empty()); }

			nik_ce void translate()
			{
				lexer.find();

				while (unfinished()) { dispatch(lexer.column(), lexer.token()); }

				exit();
			}

			nik_ce void dispatch(size_ctype col, size_ctype tok)
			{
				if (stack.is_nonterminal()) { nonterminal (col); }
				else                        {    terminal (tok); }
			}

			// nonterminal:

				nik_ce bool is_nonterminal_err() const
					{ return table.not_valid(); }

				nik_ce void nonterminal(size_ctype col)
				{
					table.move(stack.row(), col);

					if (is_nonterminal_err()) { nonterminal_report(); }
					else
					{
						nonterminal_stack  ();
						nonterminal_action ();
					}
				}

				nik_ce void nonterminal_report()
					{ } // nothing yet.

				nik_ce void nonterminal_stack()
					{ stack.replace(table.cbegin(), table.cend()); }

				nik_ce void nonterminal_action()
					{ tree.apply(table.action(), lexer); }

			// terminal:

				nik_ce bool is_terminal_err(size_ctype tok) const
					{ return (tok != stack.token()); }

				nik_ce void terminal(size_ctype tok)
				{
					if (is_terminal_err(tok)) { terminal_report(); }
					else
					{
						terminal_stack ();
						terminal_lexer ();
					}
				}

				nik_ce void terminal_report()
					{ } // nothing yet.

				nik_ce void terminal_stack () { stack.pull(); }
				nik_ce void terminal_lexer () { lexer.find(); }

			// exit:

				nik_ce size_type exit_index() const
				{
					if (lexer.not_end()) { return exit_index_lexer (); }
					else                 { return exit_index_stack (); }
				}

				nik_ce size_type exit_index_lexer() const
				{
					if (stack.not_empty()) { return Exit::both;       }
					else                   { return Exit::lexer_only; }
				}

				nik_ce size_type exit_index_stack() const
				{
					if (stack.not_empty()) { return Exit::stack_only; }
					else                   { return Exit::none;       }
				}

				nik_ce void exit()
				{
					switch (exit_index())
					{
						case Exit::lexer_only : { exit_lexer_only (); break; }
						case Exit::stack_only : { exit_stack_only (); break; }
						case Exit::both       : { exit_both       (); break; }
						case Exit::none       : { exit_none       (); break; }
					}
				}

				nik_ce void exit_lexer_only()
				{
				}

				nik_ce void exit_stack_only() { dispatch(Token::prompt, Token::prompt); }

				nik_ce void exit_both()
					{ } // nothing yet.

				nik_ce void exit_none()
					{ } // nothing yet.
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::engine

