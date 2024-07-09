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

	template<auto Op, typename T>
	using modify_type						= cctmp::modify_type<Op, T>;

	nik_ce auto _from_reference_					= cctmp::_from_reference_;

	using strlit_type						= cctmp::strlit_type;
	using cstrlit_ref						= cctmp::cstrlit_ref;

	nik_ce auto U_strlit_type					= cctmp::U_strlit_type;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// context-free grammar:

	template<typename CharType, auto M, auto N>
	nik_ce auto context_free_grammar(const CharType (&srt)[M], const CharType (&str)[N])
	{
		return cctmp::pair(cctmp::string_literal(srt), cctmp::string_literal(str));
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic transition table:

/***********************************************************************************************************************/

// symbol:

	class Symbol
	{
		bool nonterminal;
		token_type order;

		public:

			nik_ce Symbol() : nonterminal{}, order{} { }
			nik_ce Symbol(bool n, token_type o) : nonterminal{n}, order{o} { }
			nik_ce Symbol(csign_type n, ctoken_type o) : // defaults to terminal.
				nonterminal{Sign::is_nonterminal(n)}, order{o} { }

			nik_ce bool is_terminal() const { return !nonterminal; }
			nik_ce bool is_nonterminal() const { return nonterminal; }

			nik_ce token_type token() const { return order; }

			nik_ce bool operator == (const Symbol & s) const
				{ return (s.nonterminal == nonterminal) && (s.order == order); }

			nik_ce bool operator != (const Symbol & s) const
				{ return (s.nonterminal != nonterminal) || (s.order != order); }
	};

	using symbol_type		= Symbol;
	using symbol_ref		= symbol_type&;
	using csymbol_type		= symbol_type const;
	using csymbol_ref		= csymbol_type&;
	nik_ce auto U_symbol_type	= U_store_T<symbol_type>;
	nik_ce auto U_csymbol_type	= U_store_T<csymbol_type>;

/***********************************************************************************************************************/

// production:

	template<gindex_type Size>
	struct Production : public sequence<symbol_type, Size>
	{
		using base = sequence<symbol_type, Size>;

		bool valid;
		action_type action;

		nik_ce Production() : base{}, valid{}, action{AN::nop} { }

		template<typename F>
		nik_ce void map(cguider g, caction_type act)
		{
			while (g.not_end()) base::push(F::result(g++));

			valid  = true;
			action = act;
		}

		template<typename F>
		nik_ce void map(cstrlit_ref str, caction_type act)
		{
			for (auto k = str.cbegin(); k != str.cend(); ++k) base::push(F::result(*k));

			valid  = true;
			action = act;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ll(1):

/***********************************************************************************************************************/

// stack:

	template<gindex_type Size>
	struct Stack : public sequence<symbol_type, Size>
	{
		using base		= sequence<symbol_type, Size>;
		using cselector_type	= typename base::cselector_type;

		nik_ce Stack(csymbol_ref s, csymbol_ref f) : base{}
		{
			base::push(f);
			front() = s;
		}

		nik_ce csymbol_ref front() const { return *base::cend(); }
		nik_ce  symbol_ref front()       { return *base::end(); }

		nik_ce void pop() { if (base::not_empty()) base::downsize(); }

		nik_ce void push(const cselector_type & s)
			{ for (auto e = s.cend(); e != s.cbegin();) *++base::terminal = *--e; }
	};

/***********************************************************************************************************************/

// parseme:

	template<typename T_ast>
	struct T_parseme
	{
		using cselector_type	= cselector<char>;
		using ccselector_type	= cselector_type const;
		using ccselector_ref	= ccselector_type&;

		cselector_type str;
		lexeme word;
		T_ast tree;

		nik_ce T_parseme() { }
		nik_ce T_parseme(ccselector_ref s) : str{s}, word{s} { }
	};

/***********************************************************************************************************************/

// parsoid:

	template<gindex_type StackSize, gindex_type ProdSize>
	struct T_parsoid
	{
		using stack_type	= Stack<StackSize>;
		using prod_type		= Production<ProdSize> const*;

		stack_type stack;
		prod_type prod;
		action_type action;

		nik_ce T_parsoid(csymbol_ref stack_start, csymbol_ref stack_finish) :

			stack{stack_start, stack_finish}, prod{}, action{} { }
	};

/***********************************************************************************************************************/

// interface:

	template<typename T_action, typename T_pda>
	struct T_generic_parser
	{
		nik_ces auto & act	= member_value_T<T_action>;
		nik_ces auto pda	= T_pda{};

		using T_ast		= typename T_action::T_ast;
		using T_lexer		= typename T_pda::T_lexer;
		using ActName		= typename T_pda::ActName;

		using parseme_type	= T_parseme<T_ast>;
		using parseme_ref	= parseme_type&;
		using cparseme_type	= parseme_type const;
		using cparseme_ref	= cparseme_type&;

		using parsoid_type	= T_parsoid<T_pda::stack_size, T_pda::prod_size>;
		using parsoid_ref	= parsoid_type&;
		using cparsoid_type	= parsoid_type const;
		using cparsoid_ref	= cparsoid_type&;

		enum End : gkey_type { string_only = 0, stack_only, both, dimension };

		nik_ces void parse(parseme_ref p, parsoid_ref q)
		{
			T_lexer::lex(p.word);

			while (not_string_end(p) && not_stack_end(q)) dispatch(p, q);

			end_dispatch(p, q);
		}

		nik_ces bool  is_string_end (cparseme_ref p) { return p.word.is_empty(); }
		nik_ces bool not_string_end (cparseme_ref p) { return p.word.not_empty(); }

		nik_ces bool  is_stack_end (cparsoid_ref q) { return q.stack.is_empty(); }
		nik_ces bool not_stack_end (cparsoid_ref q) { return q.stack.not_empty(); }

		nik_ces void dispatch(parseme_ref p, parsoid_ref q)
		{
			if (q.stack.front().is_nonterminal()) nonterminal(p, q);
			else terminal(p, q);
		}

		nik_ces auto end_dispatch_index(cparseme_ref p, cparsoid_ref q)
			{ return (is_string_end(p) + 2*is_stack_end(q)) - 1; }

		nik_ces void end_dispatch(parseme_ref p, parsoid_ref q)
		{
			switch (end_dispatch_index(p, q))
			{
				case End::string_only : { end_dispatch_string_only (p, q); break; }
				case End::stack_only  : { end_dispatch_stack_only  (p, q); break; }
				case End::both        : { end_dispatch_both        (p, q); break; }
			}
		}

		nik_ces void end_dispatch_string_only(parseme_ref p, parsoid_ref q)
		{
			p.word.token = T_lexer::Token::prompt;
			while (not_stack_end(q)) dispatch(p, q);

			// (q.stack.front() == T_pda::stack_finish);
		}

		nik_ces void end_dispatch_stack_only(parseme_ref p, parsoid_ref q)
		{
		}

		nik_ces void end_dispatch_both(parseme_ref p, parsoid_ref q)
		{
		}

		// nonterminal:

			nik_ces bool is_nonterminal_err(cparsoid_ref q)
				{ return !q.prod->valid; }

			nik_ces void nonterminal(parseme_ref p, parsoid_ref q)
			{
				update_production(p, q);

				if (is_nonterminal_err(q)) nonterminal_report(p, q);
				else
				{
					nonterminal_update_stack(q);
					nonterminal_update_action(p, q);
				}
			}

			nik_ces void update_production(cparseme_ref p, parsoid_ref q)
				{ q.prod = &pda.production(q.stack.front(), p.word.token); }

			nik_ces void nonterminal_update_stack(parsoid_ref q)
			{
				q.stack.pop();
				q.stack.push(q.prod->cselect());
			}

			nik_ces void nonterminal_update_action(parseme_ref p, cparsoid_ref q)
			{
				caction_type n = q.prod->action;

				if (n > ActName::nop) act.apply(n, p.tree, p.word);
			}

			nik_ces void nonterminal_report(cparseme_ref p, cparsoid_ref q)
				{ } // nothing yet.

		// terminal:

			nik_ces bool is_terminal_err(cparseme_ref p, cparsoid_ref q)
				{ return (p.word.token != q.stack.front().token()); }

			nik_ces void terminal(parseme_ref p, parsoid_ref q)
			{
				if (is_terminal_err(p, q)) terminal_report(p, q);
				else
				{
					update_word(p);
					terminal_update_stack(q);
				}
			}

			nik_ces void update_word(parseme_ref p)
				{ T_lexer::lex(p.word.retract()); }

			nik_ces void terminal_update_stack(parsoid_ref q)
				{ q.stack.pop(); }

			nik_ces void terminal_report(cparseme_ref p, cparsoid_ref q)
				{ } // nothing yet.
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace engine

