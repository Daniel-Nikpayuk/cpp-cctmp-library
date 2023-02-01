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
						if (cur_entry_size > max_entry_size) max_entry_size = cur_entry_size;
						cur_entry_size = _zero;
						++cur_line_size;
						break;
					}
					case 'l':
					{
						if (cur_line_size > max_line_size) max_line_size = cur_line_size;
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

/***********************************************************************************************************************/

// derivation:

	template<typename T_pdtt, typename T_syntax, auto StaticSource, auto Size>
	struct GenericDPDA
	{
		nik_ces auto src	= T_store_U<StaticSource>::value;
		nik_ces auto tt		= T_pdtt::value;
		nik_ces auto length     = Size;

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

		char_type derivation[length];
		char_type *current;

		nik_ce GenericDPDA() :

			stack      { T_pdtt::nt_start               },
			front      { stack.front()                  },
			letter     { src.string                     },
			word       { T_dfa::lex(letter, src.finish) },
			production {                                },

			syntax     {                                },

			derivation {            },
			current    { derivation }

		{
			parse();
			derive_end();
		}

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

			derive_stack();
			derive_tokens();
			derive_production();

			stack.pop();
			stack.push(production.body.symbol, production.body.size);

			// production.action();
		}

		nik_ce void terminal()
		{
			derive_stack();
			derive_tokens();
			derive_newline();

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

		nik_ce void derive_newline() { *(current++) = '\n'; }
		nik_ce void derive_symline() { *(current++) =  '$'; } // A visual substitute for '\0'.
		nik_ce void derive_endline() { *(current++) = '\0'; }

		nik_ce void derive_pad(int s)
		{
			for (int k = 0; k < s; ++k) *(current++) = ' ';
		}

		nik_ce void derive_stack()
		{
			auto k = stack.current;
			derive_pad(14 - (k - stack.token));
			while (k != stack.token) *(current++) = *(k--);
			derive_symline();
		}

		nik_ce void derive_tokens()
		{
			derive_pad(4);
			auto k = word.finish;
			auto count = 32;
			while (k != src.finish)
			{
				auto w = T_dfa::lex(k, src.finish);
				k = w.finish;
				--count;
			}

			k = word.finish;
			derive_pad(count);

			if (word.value != '\0') *(current++) = word.value;
			else derive_pad(1);
			while (k != src.finish)
			{
				auto w = T_dfa::lex(k, src.finish);
				*(current++) = w.value;
				k = w.finish;
			}
			derive_symline();
		}

		nik_ce void derive_production()
		{
			const Body & b = production.body;
			derive_pad(4);
			*(current++) = front;
			*(current++) = ' ';
			*(current++) = (word.value == '\0') ? '$' : word.value;
			*(current++) = ' ';
			*(current++) = '-';
			*(current++) = '>';
			*(current++) = ' ';
			auto s = 6 - b.size;
			if (b.size == 0) *(current++) = 'e';
			else for (auto k = b.symbol; k != b.symbol + b.size; ++current, ++k) *current = *k;
			derive_pad(s);
			*(current++) = '\n';
		}

		nik_ce void derive_end()
		{
			derive_stack();
			derive_tokens();
			derive_endline();
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

// transition table:

	struct GenericAssemblyPDTT
	{
		using ArraySize = T_store_U<_array_size_>;

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

		Production table[Nonterminal::size][Terminal::size];

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

		template<auto Size>
		nik_ce Production transition(gcchar_type (&str)[Size], caction_type action = _zero)
		{
			auto body = Body(str, Size - 1);

			return Production{ body , action };
		}

		nik_ce GenericAssemblyPDTT() : table{}
		{
			table_entry('S',  'i') = transition("P;R"   );
			table_entry('P',  'i') = transition("iN"    );
			table_entry('N',  'i') = transition("iN"    );
			table_entry('N',  ';') = transition(""      );
			table_entry('R',  'l') = transition("BC"    );
			table_entry('B',  'l') = transition("l;E"   );
			table_entry('L',  't') = transition("IJ"    );
			table_entry('L',  'i') = transition("IJ"    );
			table_entry('L',  '.') = transition("IJ"    );
			table_entry('E',  't') = transition("Lgi;"  );
			table_entry('E',  'i') = transition("Lgi;"  );
			table_entry('E',  '.') = transition("Lgi;"  );
			table_entry('E',  'r') = transition("JrM;"  );
			table_entry('C',  'l') = transition("BC"    );
			table_entry('C', '\0') = transition(""      );
			table_entry('I',  't') = transition("tF;bi;");
			table_entry('I',  'i') = transition("T=F;"  );
			table_entry('I',  '.') = transition("T=F;"  );
			table_entry('J',  't') = transition("IJ"    );
			table_entry('J',  'g') = transition(""      );
			table_entry('J',  'r') = transition(""      );
			table_entry('J',  'i') = transition("IJ"    );
			table_entry('J',  '.') = transition("IJ"    );
			table_entry('M',  'i') = transition("i"     );
			table_entry('M',  '_') = transition("_"     );
			table_entry('F',  'i') = transition("iV"    );
			table_entry('T',  'i') = transition("i"     );
			table_entry('T',  '.') = transition("."     );
			table_entry('V',  'i') = transition("MV"    );
			table_entry('V',  '_') = transition("MV"    );
			table_entry('V',  ';') = transition(""      );
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

/***********************************************************************************************************************/

// derivation:

	template<auto SourceCallable, auto Size = 5'000>
	struct T_generic_assembly_dpda
	{
		nik_ces auto static_src	= _static_object_<SourceCallable>;
		using src_type		= decltype(T_store_U<static_src>::value);
		using T_syntax		= TableOfContents<static_src>;

		nik_ces auto value      = GenericDPDA<T_generic_assembly_pdtt, T_syntax, static_src, Size>{};
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// compile:

/***********************************************************************************************************************/

	template<auto SourceCallable>
	nik_ce auto _compile()
	{
		nik_ce auto pda = T_generic_assembly_dpda<SourceCallable>::value;

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

