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

	template<typename SizeType, SizeType RowSize, SizeType ColSize>
	class parse_table	: public sparse_plottable
				<
					parse_table_page<SizeType>,
					parse_table_text<SizeType>,
					SizeType, RowSize, ColSize
				>
	{
		public:

			using page_type		= parse_table_page < SizeType >;
			using text_type		= parse_table_text < SizeType >;
			using base		= sparse_plottable<page_type, text_type, SizeType, RowSize, ColSize>;

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

			nik_ce bool is_nonterminal() const { return base::value().is_nonterminal(); }

			nik_ce size_type row() const { return base::value().symbol(); }

			template<typename In, typename End>
			nik_ce void replace(In in, End end)
			{
				base::pull();

				while (in != end) base::push(*--in);
			}
	};

/***********************************************************************************************************************/

// tree:

	template<typename Tree, typename SizeType, SizeType Size>
	class parser_tree
	{
		public:

			using tree_type			= typename alias<Tree>::type;
			using tree_type_ptr		= typename alias<Tree>::type_ptr;
			using tree_type_cptr		= typename alias<Tree>::type_cptr;
			using tree_type_ref		= typename alias<Tree>::type_ref;

			using tree_ctype		= typename alias<Tree>::ctype;
			using tree_ctype_ptr		= typename alias<Tree>::ctype_ptr;
			using tree_ctype_cptr		= typename alias<Tree>::ctype_cptr;
			using tree_ctype_ref		= typename alias<Tree>::ctype_ref;

			using lexeme_type		= typename tree_type::lexeme_type;
			using lexeme_type_ptr		= typename tree_type::lexeme_type_ptr;
			using lexeme_type_cptr		= typename tree_type::lexeme_type_cptr;
			using lexeme_type_ref		= typename tree_type::lexeme_type_ref;

			using lexeme_ctype		= typename tree_type::lexeme_ctype;
			using lexeme_ctype_ptr		= typename tree_type::lexeme_ctype_ptr;
			using lexeme_ctype_cptr		= typename tree_type::lexeme_ctype_cptr;
			using lexeme_ctype_ref		= typename tree_type::lexeme_ctype_ref;

			using Action			= void(*)(tree_type_ref, lexeme_ctype_ref);

			using action_type		= typename alias<Action>::type;
			using action_type_ptr		= typename alias<Action>::type_ptr;
			using action_type_cptr		= typename alias<Action>::type_cptr;
			using action_type_ref		= typename alias<Action>::type_ref;

			using action_ctype		= typename alias<Action>::ctype;
			using action_ctype_ptr		= typename alias<Action>::ctype_ptr;
			using action_ctype_cptr		= typename alias<Action>::ctype_cptr;
			using action_ctype_ref		= typename alias<Action>::ctype_ref;

			using action_array_type		= cctmp::array<action_ctype, SizeType, Size>;
			using action_array_type_ptr	= typename alias<action_array_type>::type_ptr;
			using action_array_type_cptr	= typename alias<action_array_type>::type_cptr;
			using action_array_type_ref	= typename alias<action_array_type>::type_ref;

			using size_type			= typename alias<SizeType>::type;
			using size_ctype		= typename alias<SizeType>::ctype;

		protected:

			tree_type tree;
			action_array_type action;

		public:

			nik_ce parser_tree(action_ctype (&a)[Size]) : action{a} { }

			nik_ce void apply_action(size_ctype n, lexeme_ctype_ref l) { action[n](*this, l); }
	};

/***********************************************************************************************************************/

// state:

	// how best to implement the lexer relative to the parser?

		// we need a stack class to update its productions, and direct us to the transition table row.
		// we need a lexer class to handle the current word and direct us to the transition table column.
		// we need an action class with an action lookup table and a tree to apply the action to the word.

		// do we need a table class on its own? Given the production indirection, it seems reasonable.

		// Once we have the current table entry, we check if the entry is valid, if so we update the stack,
		// and apply an action if there is one.
		// add a Table { position } enum class to keep the table access generic.

/*
	template<typename Table, typename Lexer, typename Tree, typename Stack, typename SizeType, SizeType Size>
	class parser_state
	{
		public:

			using lexer_type		= parser_lexer<Lexer, SizeType>;
			using lexer_type_ptr		= typename alias<lexer_type>::type_ptr;
			using lexer_type_cptr		= typename alias<lexer_type>::type_cptr;
			using lexer_type_ref		= typename alias<lexer_type>::type_ref;

			using lexer_ctype		= typename alias<lexer_type>::ctype;
			using lexer_ctype_ptr		= typename alias<lexer_type>::ctype_ptr;
			using lexer_ctype_cptr		= typename alias<lexer_type>::ctype_cptr;
			using lexer_ctype_ref		= typename alias<lexer_type>::ctype_ref;

		//	using strlit_type		= typename lexer_type::strlit_type;
		//	using strlit_type_ptr		= typename lexer_type::strlit_type_ptr;
		//	using strlit_type_cptr		= typename lexer_type::strlit_type_cptr;
		//	using strlit_type_ref		= typename lexer_type::strlit_type_ref;

		//	using strlit_ctype		= typename lexer_type::strlit_ctype;
		//	using strlit_ctype_ptr		= typename lexer_type::strlit_ctype_ptr;
		//	using strlit_ctype_cptr		= typename lexer_type::strlit_ctype_cptr;
		//	using strlit_ctype_ref		= typename lexer_type::strlit_ctype_ref;

			using stack_type		= parser_stack<SizeType, Size>;
			using stack_type_ptr		= typename alias<stack_type>::type_ptr;
			using stack_type_cptr		= typename alias<stack_type>::type_cptr;
			using stack_type_ref		= typename alias<stack_type>::type_ref;

			using stack_ctype		= typename alias<stack_type>::ctype;
			using stack_ctype_ptr		= typename alias<stack_type>::ctype_ptr;
			using stack_ctype_cptr		= typename alias<stack_type>::ctype_cptr;
			using stack_ctype_ref		= typename alias<stack_type>::ctype_ref;

			using tree_type			= parser_tree<Tree, SizeType, Size>;
			using tree_type_ptr		= typename alias<tree_type>::type_ptr;
			using tree_type_cptr		= typename alias<tree_type>::type_cptr;
			using tree_type_ref		= typename alias<tree_type>::type_ref;

			using tree_ctype		= typename alias<tree_type>::ctype;
			using tree_ctype_ptr		= typename alias<tree_type>::ctype_ptr;
			using tree_ctype_cptr		= typename alias<tree_type>::ctype_cptr;
			using tree_ctype_ref		= typename alias<tree_type>::ctype_ref;

			using size_type			= typename alias<SizeType>::type;
			using size_ctype		= typename alias<SizeType>::ctype;

		protected:

			lexer_type lexer;
			 tree_type tree;
			stack_type stack;

		public:

			nik_ce parser_state() { }

		//	nik_ce parser_state(strlit_ctype_ref strlit) :
		//		lexer{strlit.cbegin(), strlit.cend()}
		//			{ }

			template<typename In, typename End>
			nik_ce parser_state(In in, End end) : lexer{in, end} { }

		public:

			nik_ce void translate()
			{
	//			while (lexer.not_end())
	//			{
	//				if (lexer.find())
	//					for (auto k = lexer.cbegin(); k != lexer.ccurrent(); ++k)
	//						printf("%c", *k);

	//				printf("\n");
	//			}
			}

	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::engine

