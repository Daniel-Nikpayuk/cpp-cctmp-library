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

	template<typename T_ast, typename T_pdtt, typename T_syntax, auto StaticSource>
	struct GenericPDA
	{
		nik_ces auto src		= T_store_U<StaticSource>::value;
		nik_ces auto ast		= T_ast::value;
		nik_ces auto tt			= T_pdtt::value;

		using stack_type		= Stack<src.stack_size>;
		using src_type			= decltype(src);
		using char_type			= typename src_type::char_type;
		using string_type		= typename src_type::string_type;
		using T_dfa			= typename src_type::T_dfa;

		using ast_type			= decltype(ast);
		using NAction			= typename ast_type::NAction;
		using TAction			= typename ast_type::TAction;

		stack_type stack;
		token_type front;
		string_type letter;
		lexeme word;
		Production production;

		T_syntax syntax;

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

			if (n != NAction::nop)
			{
				auto update = ast.nonterminal[n];

				update(syntax, word);
			}
		}

		nik_ce void terminal_update_action()
		{
			auto n = tt.action(word.value);

			if (n != TAction::nop)
			{
				auto update = ast.terminal[n];

				update(syntax, word);
			}
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic assembly:

/***********************************************************************************************************************/

// attributes:

	using context_type  = gkey_type;
	using ccontext_type = context_type const;

/***********************************************************************************************************************/

// context:

	struct Context
	{
		enum : context_type
		{
			none = 0,
			function, label, test, branch, instruction, apply, go_to, re_turn,
			dimension
		};
	};

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

		context_type kind;
		entry_type array[length];
		centry_type *begin;
		entry_type *entry;

		nik_ce Line() : kind{}, array{}, begin{array}, entry{array} { }

		nik_ce auto size() const { return (entry - begin); }
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

		line_type array[length];
		cline_type *begin;
		line_type *line;

		nik_ce Page() : array{}, begin{array}, line{array} { }

		nik_ce auto size() const { return (line - begin); }
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

		locus_type array[length];
		clocus_type *begin;
		locus_type *locus;

		nik_ce Note() : array{}, begin{array}, locus{array} { }

		nik_ce auto size() const { return (locus - begin); }
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

		using page_type			= Page<char_type, src.line_size, src.max_entry_size>;
		using cpage_type		= page_type const;
		using block_type		= Note<char_type, src.block_size>;
		using cblock_type		= block_type const;
		using lookup_type		= Note<char_type, src.max_ident_size>;
		using clookup_type		= lookup_type const;

		page_type page;
		block_type block;
		lookup_type lookup;

		nik_ce TableOfContents() : page{}, block{}, lookup{} { }

		nik_ce void increment_block  () { ++(block.locus     ); }
		nik_ce void increment_lookup () { ++(lookup.locus    ); }
		nik_ce void increment_line   () { ++(page.line       ); }
		nik_ce void increment_entry  () { ++(page.line->entry); }

		nik_ce auto & entry() { return *(page.line->entry); }

		nik_ce void copy(clexeme & l)
		{
			page.line->entry->begin = l.start;
			page.line->entry->end   = l.finish;
			page.line->entry->token = l.value;
		}
	};

/***********************************************************************************************************************/

// translation action:

	struct GenericAssemblyTA
	{
		template<typename TOC> nik_ces void nop(TOC & toc, clexeme & l) { }

		struct Nonterminal
		{
			struct Name
			{
				enum : action_type
				{
					nop = 0,
					new_function , new_block , new_conditional , new_instruction ,
					dimension
				};
			};

			template<typename TOC>
			nik_ces void new_function(TOC & toc, clexeme & l)
			{
				toc.page.line->kind = Context::function;
			}

			template<typename TOC>
			nik_ces void new_block(TOC & toc, clexeme & l)
			{
				toc.page.line->kind = Context::label;
			}

			template<typename TOC>
			nik_ces void new_conditional(TOC & toc, clexeme & l)
			{
				toc.page.line->kind = Context::test;
			}

			template<typename TOC>
			nik_ces void new_instruction(TOC & toc, clexeme & l)
			{
				toc.page.line->kind = Context::instruction;
			}
		};

		//	list_entry( ' ') = TAction::begin_line_definition ;
		//	list_entry( ' ') = TAction::begin_line_apply      ;
		//	list_entry( ' ') = TAction::new_entry_variable    ;
		//	list_entry( ' ') = TAction::new_entry_label       ;

		struct Terminal
		{
			struct Name
			{
				enum : action_type
				{
					nop = 0,
					begin_line_definition , begin_line_label  ,
					begin_line_test       , begin_line_branch ,
					begin_line_apply      , begin_line_goto   , begin_line_return ,
					end_line              ,
					new_entry_variable    , new_entry_label   ,
					new_entry_identifier  , new_entry_copier  , new_entry_paster  ,
					accept                ,
					dimension
				};
			};

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
				toc.increment_line();
			}

			template<typename TOC>
			nik_ces void new_entry_variable(TOC & toc, clexeme & l)
			{
			}

			template<typename TOC>
			nik_ces void new_entry_label(TOC & toc, clexeme & l)
			{
				toc.copy(l);
			//	toc.index();
			}

			template<typename TOC>
			nik_ces void new_entry_identifier(TOC & toc, clexeme & l)
			{
				switch (toc.page.line->kind)
				{
					case Context::function: new_entry_variable (toc, l); break;
					case Context::label:    new_entry_label    (toc, l); break;
					case Context::test:
					{
						break;
					}
					case Context::branch:
					{
						break;
					}
					case Context::instruction:
					{
						break;
					}
					case Context::apply:
					{
						break;
					}
					case Context::go_to:
					{
						break;
					}
					case Context::re_turn:
					{
						break;
					}
				}

				toc.increment_entry();
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

/***********************************************************************************************************************/

// abstract syntax tree:

	template<typename TOC>
	struct GenericAssemblyAST
	{
		using toc_type		= void(*)(TOC &, clexeme &);
		using Nonterminal	= typename GenericAssemblyTA::Nonterminal;
		using NAction		= typename Nonterminal::Name;
		using Terminal		= typename GenericAssemblyTA::Terminal;
		using TAction		= typename Terminal::Name;

		toc_type nonterminal[NAction::dimension];
		toc_type    terminal[TAction::dimension];

		nik_ce GenericAssemblyAST() : nonterminal{}, terminal{}
		{
			nonterminal[ NAction::new_function    ] = GenericAssemblyTA::template nop       <TOC>;
			nonterminal[ NAction::new_function    ] = Nonterminal::template new_function    <TOC>;
			nonterminal[ NAction::new_block       ] = Nonterminal::template new_block       <TOC>;
			nonterminal[ NAction::new_conditional ] = Nonterminal::template new_conditional <TOC>;
			nonterminal[ NAction::new_instruction ] = Nonterminal::template new_instruction <TOC>;

			terminal[ TAction::nop                   ] = GenericAssemblyTA::template nop          <TOC>;
			terminal[ TAction::begin_line_definition ] = Terminal::template begin_line_definition <TOC>;
			terminal[ TAction::begin_line_label      ] = Terminal::template begin_line_label      <TOC>;
			terminal[ TAction::begin_line_test       ] = Terminal::template begin_line_test       <TOC>;
			terminal[ TAction::begin_line_branch     ] = Terminal::template begin_line_branch     <TOC>;
			terminal[ TAction::begin_line_apply      ] = Terminal::template begin_line_apply      <TOC>;
			terminal[ TAction::begin_line_goto       ] = Terminal::template begin_line_goto       <TOC>;
			terminal[ TAction::begin_line_return     ] = Terminal::template begin_line_return     <TOC>;
			terminal[ TAction::end_line              ] = Terminal::template end_line              <TOC>;
			terminal[ TAction::new_entry_variable    ] = Terminal::template new_entry_variable    <TOC>;
			terminal[ TAction::new_entry_label       ] = Terminal::template new_entry_label       <TOC>;
			terminal[ TAction::new_entry_identifier  ] = Terminal::template new_entry_identifier  <TOC>;
			terminal[ TAction::new_entry_copier      ] = Terminal::template new_entry_copier      <TOC>;
			terminal[ TAction::new_entry_paster      ] = Terminal::template new_entry_paster      <TOC>;
			terminal[ TAction::accept                ] = Terminal::template accept                <TOC>;
		}
	};

	// interface:

		template<typename TOC>
		struct T_generic_assembly_ast
		{
			nik_ces auto value = GenericAssemblyAST<TOC>{};
		};

/***********************************************************************************************************************/

// transition table:

	struct GenericAssemblyPDTT
	{
		using ArraySize = T_store_U<_array_size_>;
		using NAction   = typename GenericAssemblyTA::Nonterminal::Name;
		using TAction   = typename GenericAssemblyTA::Terminal::Name;

		struct Nonterminal
		{
			nik_ces gchar_type symbol[] = "VMJIFNTECBLRPS";

			nik_ces auto size  = ArraySize::template result<>(symbol) - 1;
			nik_ces auto end   = symbol + size;
			nik_ces auto start = 'S';
		};

		struct Terminal
		{
			nik_ces gchar_type symbol[] = ";i=._lgtbr";

			nik_ces auto size = ArraySize::template result<>(symbol); // recognizes '\0'.
			nik_ces auto end  = symbol + size;
		};

		template<auto Size>
		nik_ces Production transition(gcchar_type (&str)[Size], caction_type action = NAction::nop)
		{
			auto body = Body(str, Size - 1);

			return Production{ body , action };
		}

		Production table[Nonterminal::size][Terminal::size];
		action_type list[Terminal::size];

		nik_ce GenericAssemblyPDTT() : table{}, list{}
		{
			table_entry('S',  'i') = transition( "P;R"                               );
			table_entry('P',  'i') = transition( "iN"     , NAction::new_function    );
			table_entry('N',  'i') = transition( "iN"                                );
			table_entry('N',  ';') = transition( ""                                  );
			table_entry('R',  'l') = transition( "BC"                                );
			table_entry('B',  'l') = transition( "l;E"    , NAction::new_block       );
			table_entry('L',  't') = transition( "IJ"                                );
			table_entry('L',  'i') = transition( "IJ"                                );
			table_entry('L',  '.') = transition( "IJ"                                );
			table_entry('E',  't') = transition( "Lgi;"                              );
			table_entry('E',  'i') = transition( "Lgi;"                              );
			table_entry('E',  '.') = transition( "Lgi;"                              );
			table_entry('E',  'r') = transition( "JrM;"                              );
			table_entry('C',  'l') = transition( "BC"                                );
			table_entry('C', '\0') = transition( ""                                  );
			table_entry('I',  't') = transition( "tF;bi;" , NAction::new_conditional );
			table_entry('I',  'i') = transition( "T=F;"   , NAction::new_instruction );
			table_entry('I',  '.') = transition( "T=F;"                              );
			table_entry('J',  't') = transition( "IJ"                                );
			table_entry('J',  'g') = transition( ""                                  );
			table_entry('J',  'r') = transition( ""                                  );
			table_entry('J',  'i') = transition( "IJ"                                );
			table_entry('J',  '.') = transition( "IJ"                                );
			table_entry('M',  'i') = transition( "i"                                 );
			table_entry('M',  '_') = transition( "_"                                 );
			table_entry('F',  'i') = transition( "iV"                                );
			table_entry('T',  'i') = transition( "i"                                 );
			table_entry('T',  '.') = transition( "."                                 );
			table_entry('V',  'i') = transition( "MV"                                );
			table_entry('V',  '_') = transition( "MV"                                );
			table_entry('V',  ';') = transition( ""                                  );

			list_entry( 'l') = TAction::begin_line_label     ;
			list_entry( 't') = TAction::begin_line_test      ;
			list_entry( 'b') = TAction::begin_line_branch    ;
			list_entry( 'g') = TAction::begin_line_goto      ;
			list_entry( 'r') = TAction::begin_line_return    ;
			list_entry( ';') = TAction::end_line             ;
			list_entry( 'i') = TAction::new_entry_identifier ;
			list_entry( '.') = TAction::new_entry_copier     ;
			list_entry( '_') = TAction::new_entry_paster     ;
			list_entry('\0') = TAction::accept               ;
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

		nik_ce action_type & list_entry(gcchar_type loc_c)
		{
			auto loc = numeric_find_pos(loc_c, Terminal::symbol, Terminal::end);

			return list[loc];
		}

		nik_ce caction_type & action(gcchar_type loc_c) const
		{
			auto loc = numeric_find_pos(loc_c, Terminal::symbol, Terminal::end);

			return list[loc];
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

		template<auto static_src>
		struct parser
		{
			using T_syntax		= TableOfContents<static_src>;
			using T_ast		= T_generic_assembly_ast<T_syntax>;
			nik_ces auto value     	= GenericPDA<T_ast, T_pdtt, T_syntax, static_src>{};
		};

		template<auto SourceCallable>
		nik_ces auto parse = parser<_static_object_<SourceCallable>>::value;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

