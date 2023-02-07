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

// parser:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automata:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// attributes:

	using symbol_type  = gchar_type;
	using csymbol_type = symbol_type const;

	using action_type  = gindex_type;
	using caction_type = action_type const;

/***********************************************************************************************************************/

// token kind:

	struct TokenKind
	{
		enum : gkey_type
		{
			nontoken = 0,
			nonterminal, terminal,
			dimension
		};
	};

/***********************************************************************************************************************/

// body:

	struct Body
	{
		using size_type  = gindex_type;
		using csize_type = size_type const;

		csymbol_type *symbol;
		size_type size;

		nik_ce Body()                                : symbol{    }, size{    } { }
		nik_ce Body(csymbol_type *_b, csize_type _s) : symbol{ _b }, size{ _s } { }
	};

/***********************************************************************************************************************/

// production:

	struct Production
	{
		Body body;
		action_type action;

		nik_ce Production()                                 : body{    }, action{    } { }
		nik_ce Production(const Body & _b, caction_type _a) : body{ _b }, action{ _a } { }
	};

/***********************************************************************************************************************/

// stack:

	template<auto Size>
	struct Stack
	{
		nik_ces auto length		= Size;
		using size_type			= decltype(Size);

		token_type token[length];
		token_type *current;
		ctoken_type *end;

		nik_ce Stack(ctoken_type s) : token{}, current{token}, end{token + length}
		{
			*   current = '\0';
			* ++current = s;
		}

		nik_ce ctoken_type & front() const { return *current; }
		nik_ce  token_type & front()       { return *current; }

		nik_ce void pop() { if (current != token) --current; }

		nik_ce void push(gcstring_type b, size_type size)
		{
			auto k = b + size;
			while (k != b) *++current = *--k;
		}
	};

/***********************************************************************************************************************/

// automaton:

	template<typename T_pdtt, typename T_ast, typename T_syntax, auto StaticSource>
	struct GenericPDA
	{
		nik_ces auto src		= T_store_U<StaticSource>::value;
		nik_ces auto tt			= T_pdtt::value;
		nik_ces auto nta		= T_ast::Nonterminal::template action<T_syntax>;
		nik_ces auto ta			= T_ast::Terminal::template action<T_syntax>;

		using stack_type		= Stack<src.stack_size>;
		using src_type			= decltype(src);
		using char_type			= typename src_type::char_type;
		using string_type		= typename src_type::string_type;
		using T_dfa			= typename src_type::T_dfa;
		using NTA		    	= typename T_ast::Nonterminal;
		using TA		    	= typename T_ast::Terminal;

		stack_type stack;
		token_type front;
		string_type letter;
		lexeme word;
		Production production;

		T_syntax syntax;
		// context_type context; // ? Context::open, Context::closed.

		nik_ce GenericPDA(bool p = true) :

			stack      { T_pdtt::nt_start               },
			front      { stack.front()                  },
			letter     { src.string                     },
			word       { T_dfa::lex(letter, src.finish) },
			production {                                },

			syntax     {                                }

			{ if (p) parse(); }

		nik_ce void parse()
		{
			while (*stack.current != '\0')
			{
				switch (T_pdtt::token_kind(front))
				{
					case TokenKind::nonterminal: nonterminal(); break;
					case TokenKind::terminal:       terminal(); break;
					default:                           error(); break;
				}

				front = stack.front();
			}
		}

		nik_ce void nonterminal()
		{
			update_production();
			nonterminal_update_stack();
			nonterminal_update_action();
		}

		nik_ce void terminal()
		{
			if (front != word.value) ; // error.
			else
			{
				terminal_update_action();
				update_word();
				terminal_update_stack();
			}
		}

		nik_ce void error()
		{
			// nothing yet.
		}

		nik_ce void update_production()
		{
			production = tt.production(front, word.value);
			// if (production == empty) error;
		}

		nik_ce void nonterminal_update_stack()
		{
			stack.pop();
			stack.push(production.body.symbol, production.body.size);
		}

		nik_ce void update_word()
		{
			letter = word.finish;
			word   = T_dfa::lex(letter, src.finish);
		}

		nik_ce void terminal_update_stack()
		{
			stack.pop();
		}

		nik_ce void nonterminal_update_action()
		{
			auto n = production.action;

			if (n != NTA::nop) nta[n](syntax, word);
		}

		nik_ce void terminal_update_action()
		{
			auto n = TA::find_pos(word.value);

			if (n != TA::nop) ta[n](syntax, word);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic assembly:

/***********************************************************************************************************************/

// entry:

	template<typename CharType>
	struct Entry
	{
		using char_type		= CharType;
		using cchar_type	= char_type const;

		cchar_type *begin;
		cchar_type *end;

		token_type token;
		gindex_type index;

		nik_ce Entry() : begin{}, end{}, token{}, index{} { }
	};

/***********************************************************************************************************************/

// line:

	template<typename CharType, auto Size>
	struct Line
	{
		using char_type			= CharType;
		using cchar_type		= char_type const;
		using entry_type		= Entry<char_type>;
		using centry_type		= entry_type const;

		nik_ces auto length		= Size;

	//	context_type kind;
		entry_type entry[length];
		centry_type *begin;
		 entry_type *current;

		nik_ce Line() : entry{}, begin{entry}, current{entry} { }

		nik_ce auto size() const { return (current - begin); }
	};

/***********************************************************************************************************************/

// page:

	template<typename CharType, auto LineSize, auto EntrySize>
	struct Page
	{
		using char_type			= CharType;
		using cchar_type		= char_type const;
		using line_type			= Line<char_type, EntrySize>;
		using cline_type		= line_type const;

		nik_ces auto length		= LineSize;

		line_type line[length];
		cline_type *begin;
		line_type *current;

		nik_ce Page() : line{}, begin{line}, current{line} { }

		nik_ce auto size() const { return (current - begin); }
	};

/***********************************************************************************************************************/

// note:

	template<typename CharType, auto Size>
	struct Note
	{
		using char_type			= CharType;
		using cchar_type		= char_type const;
		using locus_type		= Entry<char_type> const*;
		using clocus_type		= locus_type const;

		nik_ces auto length		= Size;

		locus_type locus[length];
		clocus_type *begin;
		locus_type *current;

		nik_ce Note() : locus{}, begin{locus}, current{locus} { }

		nik_ce auto size() const { return (current - begin); }
	};

/***********************************************************************************************************************/

// table of contents:

	template<auto StaticSource>
	struct TableOfContents
	{
		nik_ces auto src		= T_store_U<StaticSource>::value;

		using src_type			= decltype(src);
		using char_type			= typename src_type::char_type;
		using cchar_type		= typename src_type::cchar_type;

		using page_type			= Page<char_type, src.max_line_size, src.max_entry_size>;
		using cpage_type		= page_type const;
		using block_type		= Note<char_type, src.block_size>;
		using cblock_type		= block_type const;
		using lookup_type		= Note<char_type, src.max_ident_size>;
		using clookup_type		= lookup_type const;

		page_type page;
		block_type block;
		lookup_type lookup;

		nik_ce TableOfContents() : page{}, block{}, lookup{} { }

	//	nik_ce void increment_block () { ++(current                  ); }
	//	nik_ce void increment_line  () { ++(current->current         ); }
	//	nik_ce void increment_entry () { ++(current->current->current); }

	//	nik_ce auto & entry() { return *(current->current->current); }

	//	nik_ce void copy(clexeme & l)
	//	{
	//		current->current->current->begin = l.start;
	//		current->current->current->end   = l.finish;
	//		current->current->current->token = l.value;
	//	}
	};

/***********************************************************************************************************************/

// abstract syntax tree:

	struct GenericAssemblyAST
	{
		using ArraySize = T_store_U<_array_size_>;

		struct Nonterminal
		{
			nik_ces gchar_type symbol[] = "VMJIFNTECBLRPS";

			nik_ces auto size  = ArraySize::template result<>(symbol) - 1;
			nik_ces auto end   = symbol + size;
			nik_ces auto start = 'S';

			template<typename TOC> nik_ces void nop(TOC & toc, clexeme & l) { }

			template<typename TOC>
			nik_ces void new_function(TOC & toc, clexeme & l)
			{
			//	toc.copy(l);
			//	toc.increment_entry();
			}

			template<typename TOC>
			nik_ces void new_block(TOC & toc, clexeme & l)
			{
			}

			template<typename TOC>
			nik_ces void new_conditional(TOC & toc, clexeme & l)
			{
			}

			template<typename TOC>
			nik_ces void new_instruction(TOC & toc, clexeme & l)
			{
			}
		};

		struct Terminal
		{
			nik_ces gchar_type symbol[] = ";i=._lgtbr";

			nik_ces auto size = ArraySize::template result<>(symbol); // recognizes '\0'.
			nik_ces auto end  = symbol + size;

			template<typename TOC> nik_ces void nop(TOC & toc, clexeme & l) { }

			template<typename TOC>
			nik_ces void begin_line_definition(TOC & toc, clexeme & l)
			{
			}

			template<typename TOC>
			nik_ces void begin_line_label(TOC & toc, clexeme & l)
			{
			}

			template<typename TOC>
			nik_ces void begin_line_test(TOC & toc, clexeme & l)
			{
			}

			template<typename TOC>
			nik_ces void begin_line_branch(TOC & toc, clexeme & l)
			{
			}

			template<typename TOC>
			nik_ces void begin_line_apply(TOC & toc, clexeme & l)
			{
			}

			template<typename TOC>
			nik_ces void begin_line_goto(TOC & toc, clexeme & l)
			{
			}

			template<typename TOC>
			nik_ces void begin_line_return(TOC & toc, clexeme & l)
			{
			}

			template<typename TOC>
			nik_ces void end_line(TOC & toc, clexeme & l)
			{
			}

			template<typename TOC>
			nik_ces void new_entry_variable(TOC & toc, clexeme & l)
			{
			}

			template<typename TOC>
			nik_ces void new_entry_label(TOC & toc, clexeme & l)
			{
			}

			template<typename TOC>
			nik_ces void new_entry_identifier(TOC & toc, clexeme & l)
			{
			}

			template<typename TOC>
			nik_ces void new_entry_copier(TOC & toc, clexeme & l)
			{
			}

			template<typename TOC>
			nik_ces void new_entry_paster(TOC & toc, clexeme & l)
			{
			}

			template<typename TOC>
			nik_ces void accept(TOC & toc, clexeme & l)
			{
			}
		};
	};

	// interface:

		struct T_generic_assembly_ast
		{
			template<typename TOC>
			using toc_type = void(*)(TOC &, clexeme &);

			struct Nonterminal
			{
				using AST_NT = typename GenericAssemblyAST::Nonterminal;

				enum : action_type
				{
					nop = 0,
					new_function , new_block , new_conditional , new_instruction ,
					dimension
				};

				template<typename TOC>
				nik_ces toc_type<TOC> action[] =
				{
					AST_NT::template nop             <TOC>,
					AST_NT::template new_function    <TOC>,
					AST_NT::template new_block       <TOC>,
					AST_NT::template new_conditional <TOC>,
					AST_NT::template new_instruction <TOC>
				};
			};

			struct Terminal
			{
				using AST_T    = typename GenericAssemblyAST::Terminal;
				using ArrayEnd = T_store_U<_array_end_>;

				enum : action_type
				{
					nop = 0,
					begin_line_definition , begin_line_label , begin_line_test  ,
					begin_line_branch     , begin_line_apply , begin_line_goto  , begin_line_return ,
					end_line              ,
					new_entry_variable    , new_entry_label  ,
					new_entry_identifier  , new_entry_copier , new_entry_paster ,
					accept                ,
					dimension
				};

				template<typename TOC>
				nik_ces toc_type<TOC> action[] =
				{
					AST_T::template nop                   <TOC>,

					AST_T::template begin_line_definition <TOC>,
					AST_T::template begin_line_label      <TOC>,
					AST_T::template begin_line_test       <TOC>,
					AST_T::template begin_line_branch     <TOC>,
					AST_T::template begin_line_apply      <TOC>,
					AST_T::template begin_line_goto       <TOC>,
					AST_T::template begin_line_return     <TOC>,

					AST_T::template end_line              <TOC>,

					AST_T::template new_entry_variable    <TOC>,
					AST_T::template new_entry_label       <TOC>,
					AST_T::template new_entry_identifier  <TOC>,
					AST_T::template new_entry_copier      <TOC>,
					AST_T::template new_entry_paster      <TOC>,

					AST_T::template accept                <TOC>
				};

				nik_ces auto symbol	= AST_T::symbol;
				nik_ces auto end	= ArrayEnd::template result<>(AST_T::symbol);

				nik_ces auto find_pos(gcchar_type n) { return numeric_find_pos(n, symbol, end); }
			};
		};

/***********************************************************************************************************************/

// transition table:

	struct GenericAssemblyPDTT
	{
		using Nonterminal	= typename GenericAssemblyAST::Nonterminal;
		using Terminal		= typename GenericAssemblyAST::Terminal;
		using Action		= typename T_generic_assembly_ast::Nonterminal;

		template<auto Size>
		nik_ces Production transition(gcchar_type (&str)[Size], caction_type action = Action::nop)
		{
			auto body = Body(str, Size - 1);

			return Production{ body , action };
		}

		Production table[Nonterminal::size][Terminal::size];

		nik_ce GenericAssemblyPDTT() : table{}
		{
			table_entry('S',  'i') = transition( "P;R"                              );
			table_entry('P',  'i') = transition( "iN"     , Action::new_function    );
			table_entry('N',  'i') = transition( "iN"                               );
			table_entry('N',  ';') = transition( ""                                 );
			table_entry('R',  'l') = transition( "BC"                               );
			table_entry('B',  'l') = transition( "l;E"    , Action::new_block       );
			table_entry('L',  't') = transition( "IJ"                               );
			table_entry('L',  'i') = transition( "IJ"                               );
			table_entry('L',  '.') = transition( "IJ"                               );
			table_entry('E',  't') = transition( "Lgi;"                             );
			table_entry('E',  'i') = transition( "Lgi;"                             );
			table_entry('E',  '.') = transition( "Lgi;"                             );
			table_entry('E',  'r') = transition( "JrM;"                             );
			table_entry('C',  'l') = transition( "BC"                               );
			table_entry('C', '\0') = transition( ""                                 );
			table_entry('I',  't') = transition( "tF;bi;" , Action::new_conditional );
			table_entry('I',  'i') = transition( "T=F;"   , Action::new_instruction );
			table_entry('I',  '.') = transition( "T=F;"                             );
			table_entry('J',  't') = transition( "IJ"                               );
			table_entry('J',  'g') = transition( ""                                 );
			table_entry('J',  'r') = transition( ""                                 );
			table_entry('J',  'i') = transition( "IJ"                               );
			table_entry('J',  '.') = transition( "IJ"                               );
			table_entry('M',  'i') = transition( "i"                                );
			table_entry('M',  '_') = transition( "_"                                );
			table_entry('F',  'i') = transition( "iV"                               );
			table_entry('T',  'i') = transition( "i"                                );
			table_entry('T',  '.') = transition( "."                                );
			table_entry('V',  'i') = transition( "MV"                               );
			table_entry('V',  '_') = transition( "MV"                               );
			table_entry('V',  ';') = transition( ""                                 );
		}

		nik_ce Production & table_entry(gcchar_type row_c, gcchar_type col_c)
		{
			auto row = numeric_find_pos(row_c, Nonterminal::symbol, Nonterminal::end);
			auto col = numeric_find_pos(col_c,    Terminal::symbol,    Terminal::end);

			return table[row][col];
		}

		nik_ce const Production & production(gcchar_type row_c, gcchar_type col_c) const
		{
			auto row = numeric_find_pos(row_c, Nonterminal::symbol, Nonterminal::end);
			auto col = numeric_find_pos(col_c,    Terminal::symbol,    Terminal::end);

			return table[row][col];
		}
	};

	// interface:

		struct T_generic_assembly_pdtt
		{
			nik_ces auto value		= GenericAssemblyPDTT{};
			nik_ces auto nt_symbol		= GenericAssemblyPDTT::Nonterminal::symbol;
			nik_ces auto nt_end		= GenericAssemblyPDTT::Nonterminal::end;
			nik_ces auto nt_start		= GenericAssemblyPDTT::Nonterminal::start;
			nik_ces auto t_symbol		= GenericAssemblyPDTT::Terminal::symbol;
			nik_ces auto t_end		= GenericAssemblyPDTT::Terminal::end;

			nik_ces auto token_kind(ctoken_type t)
			{
				if      (numeric_find(t, nt_symbol, nt_end) != nt_end) return TokenKind::nonterminal;
				else if (numeric_find(t,  t_symbol,  t_end) !=  t_end) return TokenKind::terminal;
				else                                                   return TokenKind::nontoken;
			}
		};

/***********************************************************************************************************************/

// automaton:

	struct T_generic_assembly_pda
	{
		using T_pdtt = T_generic_assembly_pdtt;
		using T_ast  = T_generic_assembly_ast;

		template<auto static_src>
		struct parser
		{
			using T_syntax		= TableOfContents<static_src>;
			nik_ces auto value     	= GenericPDA<T_pdtt, T_ast, T_syntax, static_src>{};
		};

		template<auto SourceCallable>
		nik_ces auto parse = parser<_static_object_<SourceCallable>>::value;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

