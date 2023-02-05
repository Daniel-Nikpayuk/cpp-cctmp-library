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
		nik_ces auto src	= T_store_U<StaticSource>::value;
		nik_ces auto tt		= T_pdtt::value;
		nik_ces auto action	= T_ast::template action<T_syntax>;

		using stack_type	= Stack<src.stack_size>;
		using src_type		= decltype(src);
		using char_type		= typename src_type::char_type;
		using string_type	= typename src_type::string_type;
		using T_dfa		= typename src_type::T_dfa;
		using Action    	= typename T_ast::Action;

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

			if (n != Action::nop) action[n](syntax, word);
		}

		nik_ce void terminal_update_action()
		{
			// terminal action referencing toc.line.begin.
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

	// source is made up of lines, each line made up of entries.
	// lines can also be grouped as blocks which make up the source.
	// could call a grouping of lines a page. <-- relevant content between "...".

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

	//	gindex_type kind;
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

// block:

	template<auto Size>
	struct Block
	{
		nik_ces auto length = Size;

		gindex_type label[length];
		gcindex_type *begin;
		gindex_type *current;

		nik_ce Block() : label{}, begin{label}, current{label} { }

		nik_ce auto size() const { return (current - begin); }
	};

/***********************************************************************************************************************/

// lookup:

	template<typename CharType, auto Size>
	struct Lookup
	{
		using char_type			= CharType;
		using cchar_type		= char_type const;
		using locus_type		= Entry<char_type> const*;
		using clocus_type		= locus_type const;

		nik_ces auto length = Size;

		locus_type locus[length];
		clocus_type *begin;
		locus_type *current;

		nik_ce Lookup() : locus{}, begin{locus}, current{locus} { }

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
		using block_type		= Block<src.block_size>;
		using cblock_type		= block_type const;
		using lookup_type		= Lookup<char_type, src.max_ident_size>;
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
		template<typename TOC> nik_ces void nop(TOC & toc, clexeme & l) { }

		template<typename TOC>
		nik_ces void function_begin(TOC & toc, clexeme & l)
		{
		//	toc.copy(l);
		//	toc.increment_entry();
		}

		template<typename TOC>
		nik_ces void function_arg(TOC & toc, clexeme & l)
		{
		//	toc.copy(l);
		//	toc.increment_entry();
		}

		template<typename TOC>
		nik_ces void function_end(TOC & toc, clexeme & l)
		{
		//	toc.increment_line();
		}

		template<typename TOC>
		nik_ces void label_begin(TOC & toc, clexeme & l)
		{
		}

		template<typename TOC>
		nik_ces void test_copy(TOC & toc, clexeme & l)
		{
		}

		template<typename TOC>
		nik_ces void goto_begin(TOC & toc, clexeme & l)
		{
		}

		template<typename TOC>
		nik_ces void return_begin(TOC & toc, clexeme & l)
		{
		}

		template<typename TOC>
		nik_ces void apply_paste(TOC & toc, clexeme & l)
		{
		}

		template<typename TOC>
		nik_ces void apply_begin(TOC & toc, clexeme & l)
		{
		}

		template<typename TOC>
		nik_ces void apply_assign(TOC & toc, clexeme & l)
		{
		}

		template<typename TOC>
		nik_ces void apply_copy(TOC & toc, clexeme & l)
		{
		}

		template<typename TOC>
		nik_ces void apply_end(TOC & toc, clexeme & l)
		{
		}

		template<typename TOC>
		nik_ces void assign_name(TOC & toc, clexeme & l)
		{
		}
	};

	// interface:

		struct T_generic_assembly_ast
		{
			struct Action
			{
				enum : action_type
				{
					nop = 0,
					function_begin , function_arg , function_end ,
				        label_begin    , test_copy    , goto_begin   , return_begin ,
				        apply_paste    , apply_begin  , apply_assign , apply_copy   , apply_end ,
				        assign_name    ,
					dimension
				};
			};

			template<typename TOC>
			using toc_type = void(*)(TOC &, clexeme &);

			template<typename TOC>
			nik_ces toc_type<TOC> action[] =
			{
				GenericAssemblyAST::template nop            <TOC>,
				GenericAssemblyAST::template function_begin <TOC>,
				GenericAssemblyAST::template function_arg   <TOC>,
				GenericAssemblyAST::template function_end   <TOC>,
				GenericAssemblyAST::template label_begin    <TOC>,
				GenericAssemblyAST::template test_copy      <TOC>,
				GenericAssemblyAST::template goto_begin     <TOC>,
				GenericAssemblyAST::template return_begin   <TOC>,
				GenericAssemblyAST::template apply_paste    <TOC>,
				GenericAssemblyAST::template apply_begin    <TOC>,
				GenericAssemblyAST::template apply_assign   <TOC>,
				GenericAssemblyAST::template apply_copy     <TOC>,
				GenericAssemblyAST::template apply_end      <TOC>,
				GenericAssemblyAST::template assign_name    <TOC>
			};
		};

/***********************************************************************************************************************/

// transition table:

	struct GenericAssemblyPDTT
	{
		using ArraySize = T_store_U<_array_size_>;
		using Action    = typename T_generic_assembly_ast::Action;

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
		nik_ces Production transition(gcchar_type (&str)[Size], caction_type action = Action::nop)
		{
			auto body = Body(str, Size - 1);

			return Production{ body , action };
		}

		Production table[Nonterminal::size][Terminal::size];

		nik_ce GenericAssemblyPDTT() : table{}
		{
			table_entry('S',  'i') = transition( "P;R"                             );
			table_entry('P',  'i') = transition( "iN"     , Action::function_begin );
			table_entry('N',  'i') = transition( "iN"     , Action::function_arg   );
			table_entry('N',  ';') = transition( ""       , Action::function_end   );
			table_entry('R',  'l') = transition( "BC"                              );
			table_entry('B',  'l') = transition( "l;E"    , Action::label_begin    );
			table_entry('L',  't') = transition( "IJ"                              );
			table_entry('L',  'i') = transition( "IJ"                              );
			table_entry('L',  '.') = transition( "IJ"                              );
			table_entry('E',  't') = transition( "Lgi;"                            );
			table_entry('E',  'i') = transition( "Lgi;"                            );
			table_entry('E',  '.') = transition( "Lgi;"                            );
			table_entry('E',  'r') = transition( "JrM;"                            );
			table_entry('C',  'l') = transition( "BC"                              );
			table_entry('C', '\0') = transition( ""                                );
			table_entry('I',  't') = transition( "tF;bi;" , Action::test_copy      );
			table_entry('I',  'i') = transition( "T=F;"                            );
			table_entry('I',  '.') = transition( "T=F;"                            );
			table_entry('J',  't') = transition( "IJ"                              );
			table_entry('J',  'g') = transition( ""       , Action::goto_begin     );
			table_entry('J',  'r') = transition( ""       , Action::return_begin   );
			table_entry('J',  'i') = transition( "IJ"                              );
			table_entry('J',  '.') = transition( "IJ"                              );
			table_entry('M',  'i') = transition( "i"      , Action::assign_name    );
			table_entry('M',  '_') = transition( "_"      , Action::apply_paste    );
			table_entry('F',  'i') = transition( "iV"     , Action::apply_begin    );
			table_entry('T',  'i') = transition( "i"      , Action::apply_assign   );
			table_entry('T',  '.') = transition( "."      , Action::apply_copy     );
			table_entry('V',  'i') = transition( "MV"                              );
			table_entry('V',  '_') = transition( "MV"                              );
			table_entry('V',  ';') = transition( ""       , Action::apply_end      ); // if test,
		}										 // branch action.

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

// compile:

/***********************************************************************************************************************/

	template<auto SourceCallable>
	nik_ce auto _compile()
	{
		nik_ce auto pda = T_generic_assembly_pda::parse<SourceCallable>;

		return pda;
	}

	template<auto SourceCallable>
	nik_ce auto compile = _compile<SourceCallable>();

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

