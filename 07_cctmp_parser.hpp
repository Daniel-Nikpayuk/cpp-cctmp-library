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

// cctmp:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// node:

/***********************************************************************************************************************/

	// lexemes should hold enough info for the parser to:

	// 1) build an error report.
	// 2) build a table of contents (syntax tree), referencing the given lexemes;
	//    referencing lines and blocks. Specific lexemes will want to reference
	//    variable and label assigned values.
	// 3) build a variable lookup table.
	// 4) build a label lookup table.
	// 5) parse according to the tokens (and thus the context free grammar) to validate the source code.
	// 6) Hold symbolic type info to determine dependencies/errors.

	template<typename CharType>
	struct node
	{
		using char_type		= CharType;
		using cchar_type	= char_type const;

		cchar_type *begin;
		cchar_type *end;

		gindex_type line;  // bool line_inc indicating the number of statements matched ?
		gindex_type block; // bool block_inc indicating if a new block was entered ?

	//	The parser doesn't need to know the returned policy, it can determine it from the token.
	//	gkey_type error;
		token_type token;

		nik_ce node() :

			begin {    },
			end   {    },
			line  {    },
			block {    },
			token {    }

			{ }

		nik_ce node(cchar_type *b, cchar_type *e, gcindex_type _l, gcindex_type _b, ctoken_type _t) :

			begin {  b },
			end   {  e },
			line  { _l },
			block { _b },
			token { _t }

			{ }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// source:

/***********************************************************************************************************************/

	template<typename CharType, auto Size>
	struct source
	{
		using char_type			= CharType;
		using cchar_type		= char_type const;
		using string_type		= cchar_type*;
		using cstring_type		= string_type const;
		using size_type			= decltype(Size);

		nik_ces size_type length	= Size - 1;
		nik_ces auto dfa		= GenericAssemblyDFA{};

		cstring_type string;
		cstring_type finish;

		gindex_type max_entry_size;
		gindex_type max_ident_size;
		gindex_type max_line_size;
		gindex_type block_size;

		nik_ce source(const CharType (&s)[Size]) :

			string         { s          },
			finish         { s + length },

			max_entry_size { _zero      },
			max_ident_size { _zero      },
			max_line_size  { _zero      },
			block_size     { _one       }

		{
			auto k = string;

			gindex_type entry_size = _zero;
			gindex_type line_size  = _zero;

			while (k != finish)
			{
				auto l = dfa.lex(k, finish);

				if (l.value == TokenName::identifier)
				{
					++entry_size;
					++max_ident_size;
				}
				else if (l.value == TokenName::statement)
				{
					if (entry_size > max_entry_size) max_entry_size = entry_size;
					entry_size = _zero;
					++line_size;
				}
				else if (l.value == TokenName::label)
				{
					if (line_size > max_line_size) max_line_size = line_size;
					++entry_size;
					line_size = _zero;
					++block_size;
				}

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

	template<typename CharType, auto BlockSize, auto LineSize, auto EntrySize>
	struct table_of_contents
	{
		using char_type			= CharType;
		using cchar_type		= char_type const;
		using string_type		= cchar_type*;
		using cstring_type		= string_type const;
		using block_type		= Block<char_type, LineSize, EntrySize>;
		using size_type			= decltype(BlockSize);

		nik_ces size_type length	= BlockSize;
		nik_ces auto dfa		= GenericAssemblyDFA{};

		cstring_type string;
		cstring_type finish;

		block_type syntax[length];
		size_type size; // current size

		nik_ce table_of_contents(const CharType *s, const CharType *f) :

			string { s     },
			finish { f     },

			syntax {       },
			size   { _zero }

		{
		//	entry *current		= syntax;
		//	gindex_type line	= _zero;
		//	gindex_type block	= _zero;

		//	for (auto k = string; k != finish; ++current, ++size)
		//	{
		//		auto l   = dfa.lex(k, finish);
		//		*current = entry{l.start, l.finish, line, block, l.value};

		//		k = l.finish;
		//	}
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parse:

/***********************************************************************************************************************/

	template<auto callable>
	nik_ce auto _parse()
	{
		nik_ce auto src = callable();

		using char_type = typename decltype(src)::char_type;
		using TOC = table_of_contents<char_type, src.block_size, src.max_line_size, src.max_entry_size>;

		return TOC(src.string, src.finish);
	}

	template<auto callable>
	nik_ce auto parse = _parse<callable>();

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

} // cctmp_generics

