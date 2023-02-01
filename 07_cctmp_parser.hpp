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

// parser read:

	struct ParserRead
	{
		enum : gkey_type
		{
			next,
			peek
		};
	};

	using PRead = ParserRead;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic assembly:

	using symbol_type  = gchar_type;
	using csymbol_type = symbol_type const;

	using action_type  = gindex_type;
	using caction_type = action_type const;

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

	template<typename CharType, auto BlockSize, auto LineSize, auto EntrySize>
	struct TableOfContents
	{
		using char_type			= CharType;
		using cchar_type		= char_type const;
		using block_type		= Block<char_type, LineSize, EntrySize>;
		using size_type			= decltype(BlockSize);

		nik_ces size_type length	= BlockSize;

		block_type block[length];
		size_type size; // current size

		nik_ce TableOfContents() : block{}, size{} { }
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

// transition:

	struct Transition
	{
		Body body;
		action_type action;

		nik_ce Transition() :

			body   {    },
			action {    }

			{ }

		nik_ce Transition(const Body & _b, caction_type _a) :

			body   { _b },
			action { _a }

			{ }
	};

/***********************************************************************************************************************/

// transition table:

	struct GenericAssemblyPDTT
	{
		using ArraySize = T_store_U<_array_size_>;

		struct Nonterminal
		{
			nik_ces gchar_type symbol[] = "SPNRCBELJIFVTM";

			nik_ces auto size  = ArraySize::template result<>(symbol) - 1;
			nik_ces auto end   = symbol + size;
			nik_ces auto start = *symbol;
		};

		struct Terminal
		{
			nik_ces gchar_type symbol[] = "ltbgri._=;e";

			nik_ces auto size = ArraySize::template result<>(symbol); // recognizes '\0'.
			nik_ces auto end  = symbol + size;
		};

		Transition table[Nonterminal::size][Terminal::size];

		nik_ce Transition & set_entry(gcchar_type row_c, gcchar_type col_c)
		{
			auto row = numeric_find_pos(row_c, Nonterminal::symbol, Nonterminal::end);
			auto col = numeric_find_pos(col_c,    Terminal::symbol,    Terminal::end);

			return table[row][col];
		}

		nik_ce const Transition & get_entry(gcchar_type row_c, gcchar_type col_c) const
		{
			auto row = numeric_find_pos(row_c, Nonterminal::symbol, Nonterminal::end);
			auto col = numeric_find_pos(col_c,    Terminal::symbol,    Terminal::end);

			return table[row][col];
		}

		template<auto Size>
		nik_ce Transition transition(gcchar_type (&str)[Size], caction_type action = _zero)
		{
			auto body = Body(str, Size - 1);

			return Transition{ body , action };
		}

		nik_ce GenericAssemblyPDTT() : table{}
		{
			set_entry('S',  'i') = transition("P;R"   );
			set_entry('P',  'i') = transition("iN"    );
			set_entry('N',  'i') = transition("iN"    );
			set_entry('N',  ';') = transition(""      );
			set_entry('R',  'l') = transition("BC"    );
			set_entry('B',  'l') = transition("l;E"   );
			set_entry('L',  't') = transition("IJ"    );
			set_entry('L',  'i') = transition("IJ"    );
			set_entry('L',  '.') = transition("IJ"    );
			set_entry('E',  't') = transition("Lgi;"  );
			set_entry('E',  'i') = transition("Lgi;"  );
			set_entry('E',  '.') = transition("Lgi;"  );
			set_entry('E',  'r') = transition("JrM;"  );
			set_entry('C',  'l') = transition("BC"    );
			set_entry('C', '\0') = transition(""      );
			set_entry('I',  't') = transition("tF;bi;");
			set_entry('I',  'i') = transition("T=F;"  );
			set_entry('I',  '.') = transition("T=F;"  );
			set_entry('J',  't') = transition("IJ"    );
			set_entry('J',  'g') = transition(""      );
			set_entry('J',  'r') = transition(""      );
			set_entry('J',  'i') = transition("IJ"    );
			set_entry('J',  '.') = transition("IJ"    );
			set_entry('M',  'i') = transition("i"     );
			set_entry('M',  '_') = transition("_"     );
			set_entry('F',  'i') = transition("iV"    );
			set_entry('T',  'i') = transition("i"     );
			set_entry('T',  '.') = transition("."     );
			set_entry('V',  'i') = transition("MV"    );
			set_entry('V',  '_') = transition("MV"    );
			set_entry('V',  ';') = transition(""      );
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

// debug:

	template<auto SourceCallable, auto Size = 5'000>
	struct DebugGenericAssemblyPDA
	{
		nik_ces auto static_src	= _static_object_<SourceCallable>;
		nik_ces auto src	= T_store_U<static_src>::value;
		nik_ces auto tt		= T_generic_assembly_pdtt::value;
		nik_ces auto length     = Size;

		using transition_table	= T_generic_assembly_pdtt;
		using src_type		= decltype(src);
		using T_dfa		= typename src_type::T_dfa;
		using char_type		= typename src_type::char_type;
		using cchar_type	= typename src_type::cchar_type;
		using string_type	= typename src_type::string_type;
		using cstring_type	= typename src_type::cstring_type;
		using stack_type	= Stack<src.stack_size>;
		using toc_type		= TableOfContents
					<
						char_type,
						src.block_size, src.max_line_size, src.max_entry_size
					>;

		stack_type stack;
		token_type front;
		string_type letter;
		lexeme word;
		Transition entry;

		toc_type toc;

		char_type derivation[length];
		char_type *debug;

		nik_ce DebugGenericAssemblyPDA() :

			stack    { transition_table::nt_start      },
			front    {                                 },
			letter   { src.string                      },
			word     { T_dfa::lex(letter, src.finish)  },
			entry    {                                 },

			toc      {                                 },

			derivation {            },
			debug      { derivation }

		{
			debug_newline();
			parse();
			debug_end();
		}

		nik_ce void parse()
		{
			while (*stack.current != '\0')
			{
				front = stack.front();

				switch (transition_table::token_kind(front))
				{
					case TokenKind::nonterminal: nonterminal(); break;
					case TokenKind::terminal:       terminal(); break;
					default:                           error(); break;
				}
			}
		}

		nik_ce void nonterminal()
		{
			entry = tt.get_entry(front, word.value);
			// if (entry == empty) error;

			debug_stack();
			debug_tokens();
			debug_production();

			stack.pop();
			stack.push(entry.body.symbol, entry.body.size);

			// entry.action();
		}

		nik_ce void terminal()
		{
			debug_stack();
			debug_tokens();
			debug_newline();

			if (front != word.value) ; // error.
			else
			{
				letter = word.finish;
				word    = T_dfa::lex(letter, src.finish);

				stack.pop();
			}
		}

		nik_ce void error()
		{
			// nothing yet.
		}

		nik_ce void debug_newline() { *(debug++) = '\n'; }
		nik_ce void debug_symline() { *(debug++) =  '$'; } // A visual substitute for '\0'.
		nik_ce void debug_endline() { *(debug++) = '\0'; }

		nik_ce void debug_pad(int s)
		{
			for (int k = 0; k < s; ++k) *(debug++) = ' ';
		}

		nik_ce void debug_stack()
		{
			auto k = stack.current;
			debug_pad(14 - (k - stack.token));
			while (k != stack.token) *(debug++) = *(k--);
			debug_symline();
		}

		nik_ce void debug_tokens()
		{
			debug_pad(4);
			auto k = word.finish;
			auto count = 32;
			while (k != src.finish)
			{
				auto w = T_dfa::lex(k, src.finish);
				k = w.finish;
				--count;
			}

			k = word.finish;
			debug_pad(count);

			if (word.value != '\0') *(debug++) = word.value;
			else debug_pad(1);
			while (k != src.finish)
			{
				auto w = T_dfa::lex(k, src.finish);
				*(debug++) = w.value;
				k = w.finish;
			}
			debug_symline();
		}

		nik_ce void debug_production()
		{
			const Body & b = entry.body;
			debug_pad(4);
			*(debug++) = front;
			*(debug++) = ' ';
			*(debug++) = (word.value == '\0') ? '$' : word.value;
			*(debug++) = ' ';
			*(debug++) = '-';
			*(debug++) = '>';
			*(debug++) = ' ';
			auto s = 6 - b.size;
			if (b.size == 0) *(debug++) = 'e';
			else for (auto k = b.symbol; k != b.symbol + b.size; ++debug, ++k) *debug = *k;
			debug_pad(s);
			*(debug++) = '\n';
		}

		nik_ce void debug_end()
		{
			debug_stack();
			debug_tokens();
			debug_newline();
			debug_endline();
		}
	};

	// interface:

		template<auto SourceCallable>
		struct T_generic_assembly_pda
		{
			nik_ces auto value = DebugGenericAssemblyPDA<SourceCallable>{};
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// compile:

/***********************************************************************************************************************/

	template<auto SourceCallable>
	nik_ce auto _compile()
	{
		nik_ce auto pda = T_generic_assembly_pda<SourceCallable>::value;

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

