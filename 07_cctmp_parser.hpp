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
		gkey_type read;
		action_type action;

		nik_ce Transition() :

			body   {    },
			read   {    },
			action {    }

			{ }

		nik_ce Transition(const Body & _b, gckey_type _r, caction_type _a) :

			body   { _b },
			read   { _r },
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
			nik_ces gchar_type symbol[] = "ltbgri._=;e$";

			nik_ces auto size = ArraySize::template result<>(symbol) - 1;
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
		nik_ce Transition transition(gcchar_type (&str)[Size], gckey_type read, caction_type action = _zero)
		{
			auto body = Body(str, Size - 1);

			return Transition{ body , read , action };
		}

		nik_ce GenericAssemblyPDTT() : table{}
		{
			set_entry('S', 'i') = transition("P;R"   , PRead::next);
			set_entry('P', 'i') = transition("iN"    , PRead::peek);
			set_entry('N', 'i') = transition("iN"    , PRead::peek);
			set_entry('N', ';') = transition("e"     , PRead::peek);
			set_entry('R', 'l') = transition("BC"    , PRead::peek);
			set_entry('B', 'l') = transition("l;E"   , PRead::peek);
			set_entry('L', 't') = transition("IJ"    , PRead::peek);
			set_entry('L', 'i') = transition("IJ"    , PRead::next);
			set_entry('L', '.') = transition("IJ"    , PRead::next);
			set_entry('E', 't') = transition("Lgi;"  , PRead::peek);
			set_entry('E', 'i') = transition("Lgi;"  , PRead::peek);
			set_entry('E', '.') = transition("Lgi;"  , PRead::peek);
			set_entry('E', 'r') = transition("JrM;"  , PRead::peek);
			set_entry('C', 'l') = transition("BC"    , PRead::peek);
			set_entry('C', ';') = transition("e"     , PRead::peek);
			set_entry('I', 't') = transition("tF;bi;", PRead::peek);
			set_entry('I', 'i') = transition("T=F;"  , PRead::peek);
			set_entry('I', '.') = transition("T=F;"  , PRead::peek);
			set_entry('J', 't') = transition("IJ"    , PRead::peek);
			set_entry('J', 'g') = transition("e"     , PRead::peek);
			set_entry('J', 'r') = transition("e"     , PRead::peek);
			set_entry('J', 'i') = transition("IJ"    , PRead::peek);
			set_entry('J', '.') = transition("IJ"    , PRead::peek);
			set_entry('M', 'i') = transition("i"     , PRead::peek);
			set_entry('M', '_') = transition("_"     , PRead::next);
			set_entry('F', 'i') = transition("iV"    , PRead::next);
			set_entry('T', 'i') = transition("i"     , PRead::peek);
			set_entry('T', '.') = transition("."     , PRead::next);
			set_entry('V', 'i') = transition("MV"    , PRead::peek);
			set_entry('V', '_') = transition("MV"    , PRead::peek);
			set_entry('V', ';') = transition("e"     , PRead::peek);
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
			*   current = '$';
			* ++current = s;
		}

		nik_ce ctoken_type & front() const { return *current; }
		nik_ce token_type & front() { return *current; }

		nik_ce void pop() { if (current != token) --current; }

		nik_ce void push(gcstring_type b, size_type size)
		{
			auto k    = b + size;
			auto rest = (end - current);

			if (size <= rest) while (k != b) *(current++) = *--k;

			pop();
		}
	};

/***********************************************************************************************************************/

// automaton:

	// debugging:

		nik_ces gindex_type debug_end[] = // 32
		{
			  9,  11,  13, 18,		// factorial p n ;
			 23,  36,			// loop: ;
			 40,  48,  50, 54,		// test is_zero n ;
			 60,  65,  72,			// branch done ;
			 73,  75,  84,  86,  88, 90,	// p = multiply p n ;
			 91,  93, 103, 105, 108,	// n = decrement n ;
			112, 117, 126,			// goto loop ;
			131, 144,			// done: ;
			150, 152, 162			// return p ;
		};

	template<auto SourceCallable>
	struct GenericAssemblyPDA
	{
		nik_ces auto static_src	= _static_object_<SourceCallable>;
		nik_ces auto src	= T_store_U<static_src>::value;
		nik_ces auto tt		= T_generic_assembly_pdtt::value;

		using transition_table	= T_generic_assembly_pdtt;
		using src_type		= decltype(src);
		using T_dfa		= typename src_type::T_dfa;
		using char_type		= typename src_type::char_type;
		using stack_type	= Stack<src.stack_size>;
		using toc_type		= TableOfContents
					<
						char_type,
						src.block_size, src.max_line_size, src.max_entry_size
					>;

		stack_type stack;
		toc_type toc;

		lexeme word;
		bool lex_word;

		char_type derivation[10'000]; // for debugging.
		char_type *dcur; // for debugging.

		nik_ce GenericAssemblyPDA() :

			stack    { transition_table::nt_start },
			toc      {                            },
			word     {                            },
			lex_word { true                       },

			derivation {            }, // for debugging.
			dcur       { derivation }  // for debugging.
		{
			auto current = src.string;

			debug_before();

			while (*stack.current != '$')
			{
				lex_word = lex_word && (current != src.finish);
				auto sf  = stack.front();
				auto k   = transition_table::token_kind(sf);

				switch (k)
				{
					case TokenKind::nonterminal:
					{
						debug_stack();

						if (lex_word) word = T_dfa::lex(current, src.finish);
						auto tr = tt.get_entry(sf, word.value);

						debug_tokens(current);
						debug_production(word.value, tr.body);

						stack.push(tr.body.symbol, tr.body.size);

						lex_word = (tr.read == PRead::next);
						if (lex_word) current = word.finish;

						debug_read();

						// tr.action();
						break;
					}
					case TokenKind::terminal:
					{
						if (sf != 'e')
						{
							if (lex_word) word = T_dfa::lex(current, src.finish);
							lex_word = true;
						}

						debug_stack();
						debug_tokens(current);
						debug_pad(17);
						debug_read();

						// confirm (sf == l.value) ?
						if (sf != 'e') current = word.finish;
						stack.pop();
						break;
					}
					default:
					{
						// error.
						break;
					}
				}
			}

			debug_after();
		}

		nik_ce auto debug_pad(int s)
		{
			for (int k = 0; k < s; ++k) *(dcur++) = ' ';
		}

		nik_ce auto debug_before()
		{
			*(dcur++) = '\n';
		}

		nik_ce auto debug_stack()
		{
			auto k = stack.current + 1;
			debug_pad(14 - (k - stack.token));
			while (k != stack.token) *(dcur++) = *--k;
		}

		nik_ce auto debug_tokens(char_type const* b)
		{
			debug_pad(4);
			auto b0 = b;
			auto count = 32;
			while (b != src.finish)
			{
				auto w = T_dfa::lex(b, src.finish);
				b = w.finish;
				--count;
			}

			b = b0;
			debug_pad(count);
			while (b != src.finish)
			{
				auto w = T_dfa::lex(b, src.finish);
				*(dcur++) = w.value;
				b = w.finish;
			}
		}

		nik_ce auto debug_production(ctoken_type t, const Body & b)
		{
			debug_pad(4);
			auto sf = stack.front();
			*(dcur++) = sf; *(dcur++) = ' '; *(dcur++) = t;
			*(dcur++) = ' '; *(dcur++) = '-'; *(dcur++) = '>'; *(dcur++) = ' ';
			auto s = 6 - b.size;
			for (auto k = b.symbol; k != b.symbol + b.size; ++dcur, ++k) *dcur = *k;
			debug_pad(s);
		}

		nik_ce auto debug_read()//char_type const* const b)
		{
			debug_pad(4);
			if (lex_word)
			{
				*(dcur++) = 'n'; *(dcur++) = 'e';
				*(dcur++) = 'x'; *(dcur++) = 't';
			}
			else
			{
				*(dcur++) = 'p'; *(dcur++) = 'e';
				*(dcur++) = 'e'; *(dcur++) = 'k';
			}
			*(dcur++) = '\n';
		}

		nik_ce auto debug_after()
		{
			*(dcur++) = '\n'; *dcur = '\0';
		}
	};

	// interface:

		template<auto SourceCallable>
		struct T_generic_assembly_pda
		{
			nik_ces auto value = GenericAssemblyPDA<SourceCallable>{};
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parse:

/***********************************************************************************************************************/

	template<auto SourceCallable>
	nik_ce auto _parse()
	{
		nik_ce auto pda = T_generic_assembly_pda<SourceCallable>::value;

		return pda;
	}

	template<auto SourceCallable>
	nik_ce auto parse = _parse<SourceCallable>();

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

	nik_ce auto parsed_factorial_src = parse<factorial_source>;

/***********************************************************************************************************************/

/***********************************************************************************************************************/

	// parsing the string should be done in two rounds:

		// The first to collect memory allocation optimizers
		// such as block, max line, max entry, and distinct identifiers.
		// (if we're going to commit an extra parse cycle, we might as well
		//  collect as much relevant optimizing info as possible here)

		// the second round then builds the table of contents.

		// a line is an array of two arrays: begin entries, and end entries.
		// a block is an array of lines.
		// a table of contents is an array of blocks.

		// we can get the toc size (number of blocks) right away from the source.
		// if we want variable size blocks (numbers of lines) we have to statically build them first,
		// then cast those arrays as pointers.

	// lexemes should hold enough info for the parser to:

	// 1) build an error report.
	// 2) build a table of contents (syntax tree), referencing the given lexemes;
	//    referencing lines and blocks. Specific lexemes will want to reference
	//    variable and label assigned values.
	// 3) build a variable lookup table.
	// 4) build a label lookup table.
	// 5) parse according to the tokens (and thus the context free grammar) to validate the source code.
	// 6) Hold symbolic type info to determine dependencies/errors.

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

