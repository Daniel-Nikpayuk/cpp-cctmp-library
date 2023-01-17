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
		using char_type	= CharType;

		const char_type *begin;
		const char_type *end;

		gindex_type line;  // bool line_inc indicating the number of statements matched ?
		gindex_type block; // bool block_inc indicating if a new block was entered ?

	//	The parser doesn't need to know the returned policy, it can determine it from the token.
	//	gkey_type error;
		gkey_type token;

		nik_ce node() :

			begin {    },
			end   {    },
			line  {    },
			block {    },
			token {    }

			{ }

		nik_ce node(const char_type *b, const char_type *e, gindex_type _l, gindex_type _b, gkey_type _t) :

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
		using string_type		= char_type const *;
		using cstring_type		= string_type const;
		using size_type			= decltype(Size);
		using entry			= node<CharType>;

		nik_ces size_type size		= Size;

		cstring_type string;
		cstring_type finish;

		entry syntax[size];
		size_type syntax_size; // current size

		nik_ce source(const CharType (&s)[Size]) :

			string      { s        },
			finish      { s + size },

			syntax      {          },
			syntax_size { _zero    }

			{ parse(); }

		nik_ce void parse()
		{
			entry *current		= syntax;
			gindex_type line	= _zero;
			gindex_type block	= _zero;
			gkey_type token		= LexerToken::invalid;
		}
	};

/***********************************************************************************************************************/

// count statements:

		// skips whitespace as a side effect.

/*
	nik_ce gstring_type count_statements(gindex_type & count, gstring_type b, gstring_type e)
	{
		b = skip_whitespace(b, e);

		while (*b == ';')
		{
			++count;
			b = skip_whitespace(++b, e);
		}

		return b;
	}
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_generics

