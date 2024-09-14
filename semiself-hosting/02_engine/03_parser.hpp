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

namespace engine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// plot table:

/***********************************************************************************************************************/

// stance:

	template<typename SizeType>
	class parse_table_stance
	{
		public:

			using size_type		= typename alias<SizeType>::type;
			using size_ctype	= typename alias<SizeType>::ctype;

		protected:

			bool nonterm;
			size_type index;

		public:

			nik_ce parse_table_stance() : nonterm{}, index{} { }
			nik_ce parse_table_stance(bool const n, size_ctype i) : nonterm{n}, index{i} { }

			nik_ce bool is_nonterminal () const { return nonterm; }
			nik_ce size_type symbol    () const { return index; }

			nik_ce void set_terminality (bool const n) { nonterm = n; }
			nik_ce void set_symbol      (size_ctype i) { index = i; }
	};

/***********************************************************************************************************************/

// entry:

	template<typename SizeType>
	class parse_table_entry : public plot_entry<SizeType>
	{
		public:

			using base		= plot_entry<SizeType>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		protected:

			bool valid;
			size_type act_pos;

		public:

			nik_ce parse_table_entry() : base{}, valid{}, act_pos{} { }

			nik_ce bool is_valid    () const { return valid; }
			nik_ce size_type action () const { return act_pos; }

			nik_ce void set_valid  (            ) { valid = true; }
			nik_ce void set_action (size_ctype a) { act_pos = a; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automata:

/***********************************************************************************************************************/

// symbol:

/*
	template<typename SizeType>
	class parser_symbol
	{
		public:

			using size_type		= SizeType;
			using size_ctype	= size_type const;

			nik_ces auto terminal    (size_ctype n) { return parser_symbol{false , n}; }
			nik_ces auto nonterminal (size_ctype n) { return parser_symbol{true  , n}; }

		protected:

			bool order;
			size_type position;

		public:

			nik_ce parser_symbol() : order{}, position{} { }
			nik_ce parser_symbol(const bool o, size_ctype p) : order{o}, position{p} { }

			nik_ce bool is_nonterminal() const { return order; }
			nik_ce bool is_terminal() const { return !order; }

			nik_ce size_type index() const { return position; }

			nik_ce bool operator == (const parser_symbol & s) const
				{ return (s.order == order) && (s.position == position); }

			nik_ce bool operator != (const parser_symbol & s) const
				{ return (s.order != order) || (s.position != position); }
	};
*/

/***********************************************************************************************************************/

// stack:

/*
	template<typename SizeType, SizeType Size>
	class parser_stack
	{
		public:

			using symbol_type		= parser_symbol<SizeType>;
			using symbol_ctype		= symbol_type const;
			using symbol_ctype_ref		= symbol_ctype &;

			using size_type			= typename symbol_type::size_type;
			using size_ctype		= typename symbol_type::size_ctype;

			using stack_type		= stack<symbol_type, SizeType, Size>;

		protected:

			stack_type stack;

		public:

			nik_ce parser_stack(size_ctype start) { stack.push(symbol_type::nonterminal(start)); }

			nik_ce bool is_nonterminal () const { return (*stack).is_nonterminal(); }
			nik_ce bool is_terminal    () const { return (*stack).is_terminal(); }

			nik_ce size_type row() const { return (*stack).index(); }

			nik_ce void push(symbol_ctype_ref s) { stack.push(s); }

			template<typename In, typename End>
			nik_ce void replace(In in, End end)
			{
				stack.pull();

				while (in != end) stack.push(*--in);
			}
	};
*/

/***********************************************************************************************************************/

// table:

		// a table should have 3 components:

			// a table that indexes entries, 0 being the no entry.
			// an array of entries, consisting of body { start , finish },
			//   and an action index, 0 being the nop action.
			// an array of production symbols, representing dynamic length production bodies,
			//   symbols consisting of a terminality index, and name index.

/*
	template<typename TableLiteralType, typename ProductionLiteralType, typename SizeType>
	class parser_table
	{
		public:

			using tablit_type		= TableLiteralType;
			using tablit_ctype		= tablit_type const;
			using tablit_ctype_ref		= tablit_ctype &;

			using prodlit_type		= ProductionLiteralType;
			using prodlit_ctype		= prodlit_type const;
			using prodlit_ctype_ref		= prodlit_ctype &;

			using size_type			= SizeType;
			using size_ctype		= size_type const;

		protected:

			tablit_ctype table;
			prodlit_ctype production;

		public:

			nik_ce parser_table(tablit_ctype_ref t, prodlit_ctype_ref p) :
				table{t}, production{p}
					{ }

		protected:

		public:

			nik_ce bool is_valid(size_ctype n) const { return ; }
			nik_ce size_type action_index(size_ctype n) const { return ; }
	};
*/

/***********************************************************************************************************************/

// action:

/*
	class parser_action
	{
		public:

		protected:

		//	lookup_type lookup[Size];
		//	tree_type tree;

		public:

			nik_ce parser_action() { }

	};
*/

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

} // namespace engine

