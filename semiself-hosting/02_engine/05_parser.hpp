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

// pushdown automata:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parse table:

/***********************************************************************************************************************/

// page:

	template<typename SizeType>
	class parse_table_page : public plot_entry<SizeType>
	{
		public:

			using base		= plot_entry<SizeType>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		protected:

			size_type act_pos;

		public:

			nik_ce parse_table_page() : base{}, act_pos{} { }

			nik_ce size_type action() const { return act_pos; }

			nik_ce void set_action(size_ctype a) { act_pos = a; }
	};

/***********************************************************************************************************************/

// text:

	template<typename SizeType>
	class parse_table_text
	{
		public:

			using size_type		= typename alias<SizeType>::type;
			using size_ctype	= typename alias<SizeType>::ctype;

		protected:

			bool nonterm;
			size_type index;

		public:

			nik_ce parse_table_text() : nonterm{}, index{} { }
			nik_ce parse_table_text(bool const n, size_ctype i) : nonterm{n}, index{i} { }

			nik_ce bool is_nonterminal () const { return nonterm; }
			nik_ce size_type symbol    () const { return index; }

			nik_ce void set_terminality (bool const n) { nonterm = n; }
			nik_ce void set_symbol      (size_ctype i) { index = i; }

			nik_ce bool operator == (const parse_table_text & t) const
				{ return (t.nonterm == nonterm) && (t.index == index); }

			nik_ce bool operator != (const parse_table_text & t) const
				{ return (t.nonterm != nonterm) || (t.index != index); }
	};

/***********************************************************************************************************************/

// interface:

	// instead of inheriting directly from plottable, create a sparse plot -> sparse plottable.

	template<typename SizeType, SizeType RowSize, SizeType ColSize>
	class parse_table	: public sparse_plottable
				<
					parse_table_page<SizeType>,
					parse_table_text<SizeType>,
					SizeType, RowSize, ColSize
				>
	{
		public:

			using base		= sparse_plottable
						<
							parse_table_page<SizeType>,
							parse_table_text<SizeType>,
							SizeType, RowSize, ColSize
						>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			nik_ce parse_table() : base{} { }

			template<typename I, auto N, typename P, auto M, typename T, auto L>
			nik_ce parse_table(const I (&i)[N], const P (&p)[M], const T (&t)[L]) : base{i, p, t} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser:

/***********************************************************************************************************************/

// stack:

	template<typename SizeType, SizeType Size>
	class parser_stack : public stack<parse_table_text<SizeType>, SizeType, Size>
	{
		public:

			using text_type			= parse_table_text<SizeType>;
			using base			= stack<text_type, SizeType, Size>;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce parser_stack(size_ctype start) { base::push(text_type{true, start}); }

			nik_ce bool is_nonterminal() const { return base::operator * ().is_nonterminal(); }

			nik_ce size_type row() const { return base::operator * ().symbol(); }

			template<typename In, typename End>
			nik_ce void replace(In in, End end)
			{
				base::pull();

				while (in != end) base::push(*--in);
			}
	};

/***********************************************************************************************************************/

		// a single type array with variable length elements:

			// array[n] = void lambda(memory_structure m) { ... }

		// and if we use this idea to generate:

			// abstract_machine_state[n] = void lambda(memory_structure m) { ... }

		// it then leads to:

			// parser_transition_table[m, n] = void lambda(syntax_tree t) { ... }

// action:

		// keep generic (defer) within the parser itself.
		// this is so the tree and action array stay modular.

		// as for semantic clusters, design to pass actions into inherited tree.
		// this is so we can build actions external to the class itself (for example using a DSL).
		// how best to do this though?

	template<typename Tree, typename SizeType>
	class parser_action
	{
		public:

			using tree_type		= typename alias<Tree>::type;

			using size_type		= typename alias<SizeType>::type;
			using size_ctype	= typename alias<SizeType>::ctype;

		protected:

		//	lookup_type lookup[Size];
		//	tree_type tree;

		public:

			nik_ce parser_action() { }
	};

/***********************************************************************************************************************/

// state:

		// we need a stack class to update its productions, and direct us to the transition table row.
		// we need a lexer class to handle the current word and direct us to the transition table column.
		// we need an action class with an action lookup table and a tree to apply the action to the word.

		// do we need a table class on its own? Given the production indirection, it seems reasonable.

		// Once we have the current table entry, we check if the entry is valid, if so we update the stack,
		// and apply an action if there is one.
		// add a Table { position } enum class to keep the table access generic.

/*
	template<typename LexerType, typename TableType, typename ActionType, typename SizeType, SizeType Size>
	class parser_state
	{
		public:

			using size_type		= SizeType;
			using size_ctype	= size_type const;

			using stack_type	= parser_stack<size_type, Size>;

			using lexer_type	= LexerType;
			using lexer_ctype	= lexer_type const;
			using lexer_ctype_ref	= lexer_ctype &;

			using table_type	= TableType;
			using table_ctype	= table_type const;
			using table_ctype_ref	= table_ctype &;

			using action_type	= ActionType;
			using action_ctype	= action_type const;
			using action_ctype_ref	= action_ctype &;

		protected:

			stack_type stack;
			lexer_type lexer;
			table_ctype table;
			action_type action;

		public:

			nik_ce parser_state(lexer_ctype_ref l, table_ctype_ref t, action_ctype_ref a) :
				lexer{l}, table{t}, action{a}
					{ }

		protected:

		public:

	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::engine

