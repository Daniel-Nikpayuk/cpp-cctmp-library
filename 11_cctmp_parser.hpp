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

// ll(1) parser:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// context-free grammar:

	template<typename CharType, auto M, auto N>
	nik_ce auto context_free_grammar(const CharType (&srt)[M], const CharType (&str)[N])
	{
		return pair(string_literal(srt), string_literal(str));
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

// generic parser:

/***********************************************************************************************************************/

// stack:

/*
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
		{
			for (auto e = s.cend(); e != s.cbegin();)
				*(base::initial + ++base::terminal) = *--e;
		}
	};
*/

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

// parser generator:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// grammar:

/***********************************************************************************************************************/

	struct T_parser_generator_grammar
	{
		using ActName		= PGAN;
		using T_lexer		= T_parser_generator_lexer;
		using Token		= typename T_lexer::Token;
		nik_ces auto size	= Token::dimension;

		using sxt_pair		= pair<strlit_type, token_type>;
		using sxa_pair		= pair<strlit_type, action_type>;

		nik_ces auto source()
		{
			return context_free_grammar
			(
				"S",

				"S -> i F D     : l_value ;"
				"D -> i H D     : l_value ;"
				"  -> e         : accept  ;"
				"F -> a M A s B : front   ;"
				"  -> \\= I J K           ;"
				"H -> a M A s B : head    ;"
				"  -> \\= I J K           ;"
				"B -> a M A s B : body    ;"
				"  -> e                   ;"
				"M -> T N                 ;"
				"  -> m         : m_value ;"
				"N -> T N                 ;"
				"  -> e                   ;"
				"T -> i         : r_value ;"
				"A -> c C                 ;"
				"  -> e                   ;"
				"C -> i         : a_value ;"
				"J -> I J                 ;"
				"  -> e                   ;"
				"I -> i                   ;"
				"K -> s                   ;"
			);
		}

		nik_ces auto map = table
		(
			U_strlit_type, U_token_type,

			sxt_pair(   " " , Token::invalid    ),
			sxt_pair(   "e" , Token::empty      ),
			sxt_pair(   "$" , Token::prompt     ),
			sxt_pair(   "i" , Token::identifier ),
			sxt_pair(   "m" , Token::none       ),
			sxt_pair(   "a" , Token::arrow      ),
			sxt_pair( "\\=" , Token::equal      ),
			sxt_pair(   "c" , Token::colon      ),
			sxt_pair(   "s" , Token::semicolon  )
		);

		nik_ces auto action = table
		(
			U_strlit_type, U_action_type,

			sxa_pair( "l_value" , ActName::l_value ),
			sxa_pair( "m_value" , ActName::m_value ),
			sxa_pair( "r_value" , ActName::r_value ),
			sxa_pair( "a_value" , ActName::a_value ),
			sxa_pair( "front"   , ActName::front   ),
			sxa_pair( "head"    , ActName::head    ),
			sxa_pair( "body"    , ActName::body    ),
			sxa_pair( "accept"  , ActName::accept  )
		);

		struct Terminal
		{
			nik_ces auto symbol = table
			(
				U_gchar_type, U_token_type,

				pair( 'i' , Token::identifier ),
				pair( 'a' , Token::arrow      ),
				pair( ';' , Token::semicolon  ),
				pair( ':' , Token::colon      ),
				pair( 'm' , Token::empty      ),
				pair( '=' , Token::equal      ),
				pair( '$' , Token::prompt     )
			);

			nik_ces auto invalid   = Token::invalid;
			nik_ces auto dimension = Token::dimension;

			nik_ces auto stack_finish = symbol_type{Sign::terminal, Token::prompt};
		};

		struct Nonterminal
		{
			enum : token_type
			{
				start         = 0,
				rec_declare   ,
				front_declare ,
				head_declare  ,
				body_declare  ,
				disp_name     ,
				rec_name      ,
				tok_name      ,
				action        ,
				call          ,
				rec_alias     ,
				tok_alias     ,
				end_alias     ,
				invalid       ,
				dimension
			};

			nik_ces auto symbol = table
			(
				U_gchar_type, U_token_type,

				pair( 'S' , start         ),
				pair( 'D' , rec_declare   ),
				pair( 'F' , front_declare ),
				pair( 'H' , head_declare  ),
				pair( 'B' , body_declare  ),
				pair( 'M' , disp_name     ),
				pair( 'N' , rec_name      ),
				pair( 'T' , tok_name      ),
				pair( 'A' , action        ),
				pair( 'C' , call          ),
				pair( 'J' , rec_alias     ),
				pair( 'I' , tok_alias     ),
				pair( 'K' , end_alias     )
			);

			nik_ces auto stack_start = symbol_type{Sign::nonterminal, start};
		};
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automaton:

/***********************************************************************************************************************/

// char to symbol:

	template<typename T_grammar>
	struct T_char_to_symbol
	{
		using T = typename T_grammar::Terminal;
		using N = typename T_grammar::Nonterminal;

		nik_ces auto result(gcchar_type c)
		{
			auto s = Sign::terminal;
			auto t = T::symbol.lookup(c, T::invalid);

			if (t == T::invalid)
			{
				s = Sign::nonterminal;
				t = N::symbol.lookup(c, N::invalid);
			}

			return symbol_type{s, t};
		}
	};

/***********************************************************************************************************************/

// interface:

	template<typename T_grammar>
	struct T_parser_generator_pda
	{
		using T_lexer				= typename T_grammar::T_lexer;
		using ActName				= typename T_grammar::ActName;
		using Terminal				= typename T_grammar::Terminal;
		using Nonterminal			= typename T_grammar::Nonterminal;
		using CharToSymbol			= T_char_to_symbol<T_grammar>;

		nik_ces auto prod_size			= string_literal("aMAsB").size();
		using prod_type				= Production<prod_size>;
		using cprod_type			= prod_type const;

		nik_ces auto & stack_start		= Nonterminal::stack_start;
		nik_ces auto & stack_finish		= Terminal::stack_finish;
		nik_ces auto stack_size			= literal("TNAsBD").size(); // literal is intentional.
								// this literal is the longest possible sentential.

		prod_type list[Nonterminal::dimension * Terminal::dimension]; // list instead of table due to clang bug.

		nik_ce void set_entry(gcchar_type row_c, gcchar_type col_c, cstrlit_ref str, caction_type act = ActName::nop)
		{
			auto row = Nonterminal::symbol.lookup(row_c, Nonterminal::invalid);
			auto col = Terminal::symbol.lookup(col_c, Terminal::invalid);

			list[row * Terminal::dimension + col].template map<CharToSymbol>(str, act);
		}

		nik_ce T_parser_generator_pda() : list{}
		{
			set_entry( 'S' , 'i' , "iFD"   , ActName::l_value );
			set_entry( 'D' , 'i' , "iHD"   , ActName::l_value );
			set_entry( 'D' , '$' , ""      , ActName::accept  );
			set_entry( 'F' , 'a' , "aMA;B" , ActName::front   );
			set_entry( 'F' , '=' , "=IJK"                     );
			set_entry( 'H' , 'a' , "aMA;B" , ActName::head    );
			set_entry( 'H' , '=' , "=IJK"                     );
			set_entry( 'B' , 'i' , ""                         );
			set_entry( 'B' , 'a' , "aMA;B" , ActName::body    );
			set_entry( 'B' , '$' , ""                         );
			set_entry( 'M' , 'i' , "TN"                       );
			set_entry( 'M' , 'm' , "m"     , ActName::m_value );
			set_entry( 'N' , 'i' , "TN"                       );
			set_entry( 'N' , ';' , ""                         );
			set_entry( 'N' , ':' , ""                         );
			set_entry( 'T' , 'i' , "i"     , ActName::r_value );
			set_entry( 'A' , ';' , ""                         );
			set_entry( 'A' , ':' , ":C"                       );
			set_entry( 'C' , 'i' , "i"     , ActName::a_value );
			set_entry( 'J' , 'i' , "IJ"                       );
			set_entry( 'J' , ';' , ""                         );
			set_entry( 'I' , 'i' , "i"                        );
			set_entry( 'K' , ';' , ";"                        );
		}

		nik_ce cprod_type & production(csymbol_ref row, ctoken_type col) const
			{ return list[row.token() * Terminal::dimension + col]; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser:

/***********************************************************************************************************************/

// interface:

	template<typename T_action, typename T_grammar>
	struct T_parser_generator_parser
	{
		using T_ast		= typename T_action::T_ast;
		using T_pda		= T_parser_generator_pda<T_grammar>;
		using T_parser		= T_generic_parser<T_action, T_pda>;

		using parseme_type	= T_parseme<T_ast>;
		using parseme_ref	= parseme_type&;
		using cparseme_type	= parseme_type const;
		using cparseme_ref	= cparseme_type&;

		using parsoid_type	= T_parsoid<T_pda::stack_size, T_pda::prod_size>;
		using parsoid_ref	= parsoid_type&;
		using cparsoid_type	= parsoid_type const;
		using cparsoid_ref	= cparsoid_type&;

		parseme_type parseme;
		parsoid_type parsoid;

		nik_ce T_parser_generator_parser(const cselector<char> & s) :

			parseme{s}, parsoid{T_pda::stack_start, T_pda::stack_finish}

			{ parse(parseme, parsoid); }

		nik_ces void parse(parseme_ref p, parsoid_ref q)
			{ T_parser::parse(p, q); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parsed:

/***********************************************************************************************************************/

// interface:

	template<auto static_scanned, auto static_grammar>
	struct T_parser_generator_parsed
	{
		using T_ast			= T_parser_generator_ast<static_scanned, static_grammar>;
		using T_action			= T_parser_generator_action<T_ast>;
		using T_grammar			= T_parser_generator_grammar;
		using T_parser			= T_parser_generator_parser<T_action, T_grammar>;

		nik_ces auto & src		= T_store_U<static_scanned>::src;
		nik_ces auto parser		= T_parser(src.cselect());
		nik_ces auto & value		= parser.parseme.tree;
		nik_ces auto & start_str	= value.start_str;
		using type			= modify_type<_from_reference_, decltype(value)>;
	};

	template<auto static_scanned, auto static_grammar>
	nik_ce auto _parser_generator_parsed_ = U_store_T<T_parser_generator_parsed<static_scanned, static_grammar>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

