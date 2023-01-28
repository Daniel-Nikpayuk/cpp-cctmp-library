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
/***********************************************************************************************************************/

// generic assembly:

/***********************************************************************************************************************/

// transition table:

	struct GenericAssemblyPDTT
	{
		using ArraySize = T_store_U<_array_size_>;

		struct Nonterminal
		{
			nik_ces gchar_type symbol[] = "SPNRCBELJIFVTM";

			nik_ces auto size = ArraySize::template result<>(symbol) - 1;
			nik_ces auto end  = symbol + size;
		};

		struct Terminal
		{
			nik_ces gchar_type symbol[] = "ltbgri._=;e$";

			nik_ces auto size = ArraySize::template result<>(symbol) - 1;
			nik_ces auto end  = symbol + size;
		};

		Transition table[Nonterminal::size][Terminal::size];

		nik_ce Transition & table_entry(gcchar_type row_c, gcchar_type col_c)
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
			table_entry('S', 'i') = transition("P;R"   );
			table_entry('P', 'i') = transition("iN"    );
			table_entry('N', 'i') = transition("iN"    );
			table_entry('N', ';') = transition("e"     );
			table_entry('R', 'l') = transition("BC"    );
			table_entry('C', 'l') = transition("BC"    );
			table_entry('C', '$') = transition("e"     );
			table_entry('B', 'l') = transition("l;LE"  );
			table_entry('E', 'g') = transition("gi"    );
			table_entry('E', 'r') = transition("rM"    );
			table_entry('L', 't') = transition("IJ"    );
			table_entry('L', 'i') = transition("IJ"    );
			table_entry('L', '.') = transition("IJ"    );
			table_entry('J', 't') = transition("IJ"    );
			table_entry('J', 'g') = transition("e"     );
			table_entry('J', 'r') = transition("e"     );
			table_entry('J', 'i') = transition("IJ"    );
			table_entry('J', '.') = transition("IJ"    );
			table_entry('I', 't') = transition("tF;bi;");
			table_entry('I', 'i') = transition("T=F;"  );
			table_entry('I', '.') = transition("T=F;"  );
			table_entry('F', 'i') = transition("iV"    );
			table_entry('V', 'i') = transition("MV"    );
			table_entry('V', '_') = transition("MV"    );
			table_entry('V', ';') = transition("e"     );
			table_entry('T', 'i') = transition("i"     );
			table_entry('T', '.') = transition("."     );
			table_entry('M', 'i') = transition("i"     );
			table_entry('M', '_') = transition("_"     );
		}
	};

/***********************************************************************************************************************/

// automaton:

	struct T_generic_assembly_pdtt
	{
		nik_ces auto value = GenericAssemblyPDTT{};
	};

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

// preamble:

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

		nik_ce Stack() : token{}, current{token}, end{token + length} { }

		nik_ce void pop() { --current; }

		nik_ce void push(gcstring_type b, gstring_type k)
		{
			auto size = (k - b);
			auto rest = (end - current);

			if (size <= rest) while (k != b) *(current++) = *--k;
		}
	};

	// recurse over the stack:

		// If the front token is terminal, confirm it's also the first lexed string token.
		// If it's not it's an error, otherwise drop it from the stack, iterate to the next lexed string token.

		// If the front token is nonterminal, reference the transition table using it and the first lexed
		// string token. Replace-push the token on the stack with the production body (updating the current
		// stack position), and perform the semantic action (translation). Iterate to the next lexed string token.

		// Continue.

/***********************************************************************************************************************/

// automaton:

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

	template<auto SourceCallable>
	struct GenericAssemblyPDA
	{
		nik_ces auto static_src	= _static_object_<SourceCallable>;
		nik_ces auto src	= T_store_U<static_src>::value;

		using T_dfa		= T_generic_assembly_dfa;
		using src_type		= decltype(src);
		using char_type		= typename src_type::char_type;
		using stack_type	= Stack<src.stack_size>;
		using toc_type		= TableOfContents
					<
						char_type,
						src.block_size, src.max_line_size, src.max_entry_size
					>;

		stack_type stack;
		toc_type toc;

		nik_ce GenericAssemblyPDA() :

			toc   {       },
			stack {       }

		{
		//	entry *current		= syntax;
		//	gindex_type line	= _zero;
		//	gindex_type block	= _zero;

		//	for (auto k = string; k != finish; ++current, ++size)
		//	{
		//		auto l   = T_dfa::lex(k, finish);
		//		*current = entry{l.start, l.finish, line, block, l.value};

		//		k = l.finish;
		//	}
		}
	};

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
/***********************************************************************************************************************/

} // namespace cctmp

