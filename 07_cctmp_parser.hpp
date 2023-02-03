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

// source:

/***********************************************************************************************************************/

	template<typename CharType, auto Size>
	struct source
	{
		using T_dfa			= T_generic_assembly_dfa;

		using char_type			= CharType;
		using cchar_type		= char_type const;
		using string_type		= cchar_type*;
		using cstring_type		= string_type const;
		using size_type			= decltype(Size);

		nik_ces size_type length	= Size - 1;

		cstring_type string;
		cstring_type finish;

		gindex_type max_entry_size;
		gindex_type max_ident_size;
		gindex_type max_line_size;

		gindex_type block_size;
		gindex_type stack_size;

		nik_ce source(const CharType (&s)[Size]) :

			string         { s          },
			finish         { s + length },

			max_entry_size { _zero      },
			max_ident_size { _zero      },
			max_line_size  { _zero      },

			block_size     { _one       },
			stack_size     { _zero      }

			{
				auto k = string;

				gindex_type cur_entry_size = _zero;
				gindex_type cur_line_size  = _zero;

				while (k != finish)
				{
					auto l = T_dfa::lex(k, finish);

					switch (l.value)
					{
						case 'i':
						{
							++cur_entry_size;
							++max_ident_size;
							break;
						}
						case ';':
						{
							if (cur_entry_size > max_entry_size)
								max_entry_size = cur_entry_size;
							cur_entry_size = _zero;
							++cur_line_size;
							break;
						}
						case 'l':
						{
							if (cur_line_size > max_line_size)
								max_line_size = cur_line_size;
							++cur_entry_size;
							cur_line_size = _zero;
							++block_size;
							break;
						}
					}

					++stack_size;
					k = l.finish;
				}
			}
	};

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
			nonterminal,
			terminal,
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

		nik_ce Body() :

			symbol {    },
			size   {    }

			{ }

		nik_ce Body(csymbol_type *_b, csize_type _s) :

			symbol { _b },
			size   { _s }

			{ }
	};

/***********************************************************************************************************************/

// production:

	struct Production
	{
		Body body;
		action_type action;

		nik_ce Production() :

			body   {    },
			action {    }

			{ }

		nik_ce Production(const Body & _b, caction_type _a) :

			body   { _b },
			action { _a }

			{ }
	};

/***********************************************************************************************************************/

// stack:

	template<auto Size>
	struct Stack
	{
		using size_type			= decltype(Size);

		nik_ces size_type length	= Size;

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

	template<typename T_pdtt, typename T_syntax, auto StaticSource>
	struct GenericPDA
	{
		nik_ces auto src	= T_store_U<StaticSource>::value;
		nik_ces auto tt		= T_pdtt::value;

		using stack_type	= Stack<src.stack_size>;
		using src_type		= decltype(src);
		using char_type		= typename src_type::char_type;
		using string_type	= typename src_type::string_type;
		using T_dfa		= typename src_type::T_dfa;

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
			update_stack();
			update_action();
		}

		nik_ce void terminal()
		{
			if (front != word.value) ; // error.
			else
			{
				letter = word.finish;
				word   = T_dfa::lex(letter, src.finish);

				stack.pop();
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

		nik_ce void update_stack()
		{
			stack.pop();
			stack.push(production.body.symbol, production.body.size);
		}

		nik_ce void update_action()
		{
		}
	};

/***********************************************************************************************************************/

// derivation:

	template<typename T_pdtt, typename T_syntax, auto StaticSource, auto Size>
	struct GenericDPDA : public GenericPDA<T_pdtt, T_syntax, StaticSource>
	{
		using Base		= GenericPDA<T_pdtt, T_syntax, StaticSource>;
		nik_ces auto length     = Size;

		using char_type		= typename Base::char_type;
		using string_type	= typename Base::string_type;
		using T_dfa		= typename Base::T_dfa;

		char_type derivation[length];
		char_type *current;

		nik_ce GenericDPDA() :

			Base       { false      },
			derivation {            },
			current    { derivation }

			{ parse(); }

		nik_ce void parse()
		{
			while (*Base::stack.current != '\0')
			{
				switch (T_pdtt::token_kind(Base::front))
				{
					case TokenKind::nonterminal: nonterminal(); break;
					case TokenKind::terminal:       terminal(); break;
					default:                           error(); break;
				}

				Base::front = Base::stack.front();
			}

			update_end();
		}

		nik_ce void nonterminal()
		{
			Base::update_production();

			update_stack();
			update_tokens();
			update_production();

			Base::update_stack();
			Base::update_action();
		}

		nik_ce void terminal()
		{
			update_stack();
			update_tokens();
			update_newline();

			Base::terminal();
		}

		nik_ce void error()
		{
			// nothing yet.
		}

		nik_ce void update_newline() { *(current++) = '\n'; }
		nik_ce void update_symline() { *(current++) =  '$'; } // A visual substitute for '\0'.
		nik_ce void update_endline() { *(current++) = '\0'; }
		nik_ce void update_space  () { *(current++) =  ' '; }
		nik_ce void update_dash   () { *(current++) =  '-'; }
		nik_ce void update_gt     () { *(current++) =  '>'; }
		nik_ce void update_arrow  () { update_space(); update_dash(); update_gt(); update_space(); }

		nik_ce void update_pad(int s)
		{
			for (int k = 0; k < s; ++k) *(current++) = ' ';
		}

		nik_ce void update_stack()
		{
			auto k = Base::stack.current;
			update_pad(14 - (k - Base::stack.token));
			while (k != Base::stack.token) *(current++) = *(k--);
			update_symline();
		}

		nik_ce void update_tokens()
		{
			update_pad(4);
			auto k = Base::word.finish;
			auto count = 32;
			while (k != Base::src.finish)
			{
				auto w = T_dfa::lex(k, Base::src.finish);
				--count;
				k = w.finish;
			}

			k = Base::word.finish;
			update_pad(count);

			if (Base::word.value != '\0') *(current++) = Base::word.value;
			else update_pad(1);
			while (k != Base::src.finish)
			{
				auto w = T_dfa::lex(k, Base::src.finish);
				*(current++) = w.value;
				k = w.finish;
			}
			update_symline();
		}

		nik_ce void update_production()
		{
			const Body & b = Base::production.body;
			update_pad(4);
			*(current++) = Base::front;
			update_space();
			*(current++) = (Base::word.value == '\0') ? '$' : Base::word.value;
			update_arrow();
			auto s = 6 - b.size;
			if (b.size == 0) *(current++) = 'e';
			else for (auto k = b.symbol; k != b.symbol + b.size; ++current, ++k) *current = *k;
			update_pad(s);
			update_newline();
		}

		nik_ce void update_end()
		{
			update_stack();
			update_tokens();
			update_endline();
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

		nik_ce Entry() :

			begin {    },
			end   {    },
			token {    }

			{ }

		nik_ce Entry(cchar_type *b, cchar_type *e, ctoken_type _t) :

			begin {  b },
			end   {  e },
			token { _t }

			{ }
	};

/***********************************************************************************************************************/

// line:

	template<typename CharType, auto Size>
	struct Line
	{
		using char_type			= CharType;
		using cchar_type		= char_type const;
		using size_type			= decltype(Size);
		using entry_type		= Entry<char_type>;

		nik_ces size_type length	= Size;

		entry_type entry[length];
		size_type size; // current size

		nik_ce Line() : entry{}, size{} { }
	};

/***********************************************************************************************************************/

// block:

	template<typename CharType, auto LineSize, auto EntrySize>
	struct Block
	{
		using char_type			= CharType;
		using cchar_type		= char_type const;
		using size_type			= decltype(LineSize);
		using line_type			= Line<char_type, EntrySize>;

		nik_ces size_type length	= LineSize;

		line_type line[length];
		size_type size; // current size

		nik_ce Block() : line{}, size{} { }
	};

/***********************************************************************************************************************/

// table of contents:

	template<auto StaticSource>
	struct TableOfContents
	{
		nik_ces auto src		= T_store_U<StaticSource>::value;
		nik_ces auto length		= src.block_size;

		using src_type			= decltype(src);
		using char_type			= typename src_type::char_type;
		using cchar_type		= typename src_type::cchar_type;
		using block_type		= Block<char_type, src.max_line_size, src.max_entry_size>;
		using size_type			= decltype(length);

		block_type block[length];
		size_type size; // current size

		nik_ce TableOfContents() : block{}, size{} { }

	};

/***********************************************************************************************************************/

// abstract syntax tree:

	struct GenericAssemblyAST
	{
		struct Action
		{
			enum : action_type
			{
				nop = 0,
				function_name , function_arg , function_end ,
			        label_name    , test_copy    , goto_name    , return_name ,
			        apply_paste   , apply_name   , apply_assign , apply_copy  , apply_end ,
			        assign_name   ,
				dimension
			};
		};

		nik_ces auto function_name () { return 0; }
		nik_ces auto function_arg  () { return 0; }
		nik_ces auto function_end  () { return 0; }
		nik_ces auto label_name    () { return 0; }
		nik_ces auto test_copy     () { return 0; }
		nik_ces auto goto_name     () { return 0; }
		nik_ces auto return_name   () { return 0; }
		nik_ces auto apply_paste   () { return 0; }
		nik_ces auto apply_name    () { return 0; }
		nik_ces auto apply_assign  () { return 0; }
		nik_ces auto apply_copy    () { return 0; }
		nik_ces auto apply_end     () { return 0; }
		nik_ces auto assign_name   () { return 0; }
	};

/***********************************************************************************************************************/

// transition table:

	struct GenericAssemblyPDTT
	{
		using ArraySize = T_store_U<_array_size_>;
		using Action    = typename GenericAssemblyAST::Action;

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
			table_entry('S',  'i') = transition( "P;R"                            );
			table_entry('P',  'i') = transition( "iN"     , Action::function_name );
			table_entry('N',  'i') = transition( "iN"     , Action::function_arg  );
			table_entry('N',  ';') = transition( ""       , Action::function_end  );
			table_entry('R',  'l') = transition( "BC"                             );
			table_entry('B',  'l') = transition( "l;E"    , Action::label_name    );
			table_entry('L',  't') = transition( "IJ"                             );
			table_entry('L',  'i') = transition( "IJ"                             );
			table_entry('L',  '.') = transition( "IJ"                             );
			table_entry('E',  't') = transition( "Lgi;"                           );
			table_entry('E',  'i') = transition( "Lgi;"                           );
			table_entry('E',  '.') = transition( "Lgi;"                           );
			table_entry('E',  'r') = transition( "JrM;"                           );
			table_entry('C',  'l') = transition( "BC"                             );
			table_entry('C', '\0') = transition( ""                               );
			table_entry('I',  't') = transition( "tF;bi;" , Action::test_copy     );
			table_entry('I',  'i') = transition( "T=F;"                           );
			table_entry('I',  '.') = transition( "T=F;"                           );
			table_entry('J',  't') = transition( "IJ"                             );
			table_entry('J',  'g') = transition( ""       , Action::goto_name     );
			table_entry('J',  'r') = transition( ""       , Action::return_name   );
			table_entry('J',  'i') = transition( "IJ"                             );
			table_entry('J',  '.') = transition( "IJ"                             );
			table_entry('M',  'i') = transition( "i"      , Action::assign_name   );
			table_entry('M',  '_') = transition( "_"      , Action::apply_paste   );
			table_entry('F',  'i') = transition( "iV"     , Action::apply_name    );
			table_entry('T',  'i') = transition( "i"      , Action::apply_assign  );
			table_entry('T',  '.') = transition( "."      , Action::apply_copy    );
			table_entry('V',  'i') = transition( "MV"                             );
			table_entry('V',  '_') = transition( "MV"                             );
			table_entry('V',  ';') = transition( ""       , Action::apply_end     ); // if test,
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

		template<auto static_src>
		struct parser
		{
			using T_syntax		= TableOfContents<static_src>;
			nik_ces auto value      = GenericPDA<T_pdtt, T_syntax, static_src>{};
		};

		template<auto SourceCallable>
		nik_ces auto parse = parser<_static_object_<SourceCallable>>::value;
	};

/***********************************************************************************************************************/

// derivation:

	struct T_generic_assembly_dpda
	{
		using T_pdtt = T_generic_assembly_pdtt;

		template<auto static_src, auto Size>
		struct parser
		{
			using T_syntax		= TableOfContents<static_src>;
			nik_ces auto value      = GenericDPDA<T_pdtt, T_syntax, static_src, Size>{};
		};

		template<auto SourceCallable, auto Size = 5'000>
		nik_ces auto parse = parser<_static_object_<SourceCallable>, Size>::value;
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

// factorial:

/***********************************************************************************************************************/

	nik_ce auto factorial_source()
	{
		return source
		(
		 	"factorial p n    ;"

			"loop:            ;"
		 	"test is_zero n   ;"
			"branch done      ;"
			"p = multiply p n ;"
			"n = decrement n  ;"
			"goto loop        ;"

			"done:            ;"
			"return p         ;"
		);
	}

	nik_ce auto factorial = compile<factorial_source>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

