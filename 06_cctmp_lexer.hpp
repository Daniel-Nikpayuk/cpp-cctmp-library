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

// lexer:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// character sets:

	using global_char_type		= char;
	using gchar_type		= global_char_type;
	using gcchar_type		= global_char_type const;

	using global_string_type	= gcchar_type*;
	using gstring_type		= global_string_type;
	using gcstring_type		= global_string_type const;

/***********************************************************************************************************************/

// generic:

	nik_ce gchar_type whitespace  [] = { ' ', '\t', '\n' };
	nik_ce gchar_type latin_digit [] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	nik_ce gchar_type latin_lowercase[] =
	{
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
		'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
		'u', 'v', 'w', 'x', 'y', 'z'
	};

	nik_ce gchar_type latin_uppercase[] =
	{
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
		'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X', 'Y', 'Z'
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// numeric:

/***********************************************************************************************************************/

// find:

	template<typename T, typename In, typename End>
	nik_ce auto numeric_find(T n, In k, End e)
	{
		while (k != e) if (*k == n) break; else ++k;

		return k;
	}

/***********************************************************************************************************************/

// find pos:

	template<typename T, typename In, typename End>
	nik_ce auto numeric_find_pos(T n, In b, End e)
	{
		auto k = numeric_find(n, b, e);

		return k - b;
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pointer:

/***********************************************************************************************************************/

	template<typename SizeType, typename Type1, typename Type2>
	nik_ce auto ptr_diff_equal(const Type1 *b1, const Type1 *e1, const Type2 *b2, const Type2 *e2)
	{
		using size_type = SizeType;

		const size_type size1 = e1 - b1;
		const size_type size2 = e2 - b2;

		bool equal = (size1 == size2);

		while (equal && b1 != e1) equal = (*(b1++) == *(b2++));

		return equal;
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// recognizers:

/***********************************************************************************************************************/

// matches:

	template<auto Size>
	nik_ce auto matches_charset(gcchar_type c, gcchar_type (&charset)[Size])
	{
		gcstring_type e = charset + Size;
		gcstring_type k = numeric_find(c, charset, e);

		return (k != e);
	}

/***********************************************************************************************************************/

// matches charset:

	// whitespace:

		nik_ce bool matches_whitespace(gcchar_type c) { return matches_charset(c, whitespace); }

	// digit (optimization):

		nik_ce bool matches_digit(gcchar_type c) { return ('0' <= c) && (c <= '9'); }

	// latin lowercase:

		nik_ce bool matches_latin_lowercase(gcchar_type c) { return matches_charset(c, latin_lowercase); }

	// latin uppercase:

		nik_ce bool matches_latin_uppercase(gcchar_type c) { return matches_charset(c, latin_uppercase); }

/***********************************************************************************************************************/

// matches identifier:

	nik_ce bool matches_underscore_latin_alphabet(gcchar_type c)
	{
		return (c == '_') || matches_latin_lowercase(c) || matches_latin_uppercase(c);
	}

	nik_ce bool matches_underscore_latin_alphanumeric(gcchar_type c)
	{
		return matches_digit(c) || matches_underscore_latin_alphabet(c);
	}

/***********************************************************************************************************************/

// skip whitespace:

	nik_ce gstring_type skip_whitespace(gstring_type b, gcstring_type e)
	{
		while (b != e && matches_whitespace(*b)) ++b;

		return b;
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// static:

/***********************************************************************************************************************/

// object:

	template<auto Callable>
	struct T_static_object
	{
		nik_ces auto value = Callable();

	}; template<auto Callable>
		nik_ce auto _static_object_ = U_store_T<T_static_object<Callable>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// attributes:

/***********************************************************************************************************************/

// state:

	using state_type  = gindex_type;
	using cstate_type = state_type const;

	struct StateName
	{
		using cstate_array = cstate_type*;

		enum : state_type
		{
			empty = 0,
			initial ,
			dimension
		};
	};

/***********************************************************************************************************************/

// token:

	using token_type  = gchar_type;
	using ctoken_type = token_type const;

	struct TokenName
	{
		enum : token_type
		{
			invalid = '\0',
			keyword_label_error,
			dimension
		};
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lexeme:

/***********************************************************************************************************************/

	struct lexeme
	{
		gstring_type  start;
		gstring_type finish;
		gindex_type   value;

		nik_ce lexeme() :

			start  { },
			finish { },
			value  { }

			{ }

		nik_ce lexeme(gcstring_type _s, gcstring_type _f, gcindex_type _v) :

			start  { _s },
			finish { _f },
			value  { _v }

			{ }
	};

	using clexeme = lexeme const;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// deterministic finite automata:

/***********************************************************************************************************************/

// recognize:

	template<typename T_dftt>
	nik_ce lexeme recognize(gstring_type b, gstring_type e)
	{
		nik_ce auto transition_table = T_dftt::value;

		gstring_type k = skip_whitespace(b, e);
		b = k;

		state_type s = StateName::initial;

		while (k != e)
		{
			auto ns = transition_table.move(s, *k);

			if (ns == StateName::empty) break;
			else
			{
				s = ns;
				++k;
			}
		}

		return lexeme{b, k, s};
	}

/***********************************************************************************************************************/

// recognizes:

	template<typename T_dfa>
	nik_ce gcbool_type recognizes(gstring_type b, gstring_type e)
	{
		auto l = T_dfa::lex(b, e);
		return (l.value != TokenName::invalid);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (generic) keyword:

/***********************************************************************************************************************/

// dfa charset:

	template<typename CharType, auto Size>
	struct dfa_charset
	{
		using char_type			= CharType;
		using string_type		= char_type const *;
		using size_type			= decltype(Size);

		nik_ces size_type length	= Size - 1;

		string_type string;
		char_type unique[length];
		char_type column[length];
		size_type size;

		nik_ce dfa_charset(const CharType (&s)[Size]) : string{s}, unique{}, column{}, size{}
		{
			string_type end = string + length;

			for (string_type j = string; j != end; ++j)
			{
				gcstring_type e = unique + size;
				gcstring_type k = numeric_find(*j, unique, e);

				if (k == e) unique[size++] = *j;
			}

			char_type *k = column;

			for (string_type j = string; j != end; ++j, ++k) *k = map(*j);
		}

			// Assumes map will return a non-zero index for each
			// character (equivalence) class, and will otherwise return
			// zero (for any other character).

		nik_ce gkey_type map(gcchar_type c) const
		{
			auto k = numeric_find_pos(c, unique, unique + size);

			if (k != size) return k + 1;
			else           return _zero;
		}
	};

/***********************************************************************************************************************/

// transition table:

	template<auto CharsetCallable>
	struct KeywordDFTT
	{
		nik_ces auto static_charset		= _static_object_<CharsetCallable>;
		nik_ces auto charset			= T_store_U<static_charset>::value;
		nik_ces gkey_type state_size		= charset.length + 2;
		nik_ces gkey_type charset_size		= charset.size + 1;

		state_type table[state_size][charset_size];

		nik_ce KeywordDFTT() : table{} // initializes the empty state.
		{
			for (gkey_type pos = StateName::initial; pos != charset.length + 1; ++pos)
				table[pos][charset.column[pos - 1]] = pos + 1;
		}

		nik_ce cstate_type & move(cstate_type s, gcchar_type c) const
		{
			return table[s][charset.map(c)];
		}
	};

	template<auto CharsetCallable>
	struct T_keyword_dftt
	{
		nik_ces auto value  = KeywordDFTT<CharsetCallable>{};
		nik_ces auto accept = value.charset.length + 1;
	};

/***********************************************************************************************************************/

// automaton:

	template<auto CharsetCallable, auto Token>
	struct T_keyword_dfa
	{
		using transition_table	= T_keyword_dftt<CharsetCallable>;
		nik_ces auto token	= Token;

		nik_ces lexeme lex(gstring_type b, gstring_type e)
		{
			auto l       = recognize<transition_table>(b, e);
			token_type t = (l.value == transition_table::accept) ? Token : TokenName::invalid;

			return lexeme{l.start, l.finish, (gindex_type) t};
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic assembly:

/***********************************************************************************************************************/

// transition table:

	struct GenericAssemblyDFTT
	{
		struct State
		{
			enum : state_type
			{
				empty   = StateName::empty,
				initial = StateName::initial,
				underscore_latin_alphanumeric,
				ulan    = underscore_latin_alphanumeric,
				semicolon,
				equal,
				period,
				colon,
				dimension
			};

			nik_ces state_type accept[] =
			{
				ulan      ,
				semicolon ,
				equal     ,
				period    ,
				colon
			};

			nik_ces token_type token[] =
			{
				'i' ,
				';' ,
				'=' ,
				'.' ,
				'l'
			};
		};

		struct Charset
		{
			enum : gkey_type
			{
				any = 0,
				underscore_latin_alphabet,
				ula = underscore_latin_alphabet,
				digit,
				semicolon,
				equal,
				period,
				colon,
				dimension
			};

			nik_ces gkey_type map(gcchar_type c)
			{
				if      (matches_underscore_latin_alphabet(c)) return Charset::ula;
				else if (matches_digit(c)                    ) return Charset::digit;
				else if (c == ';'                            ) return Charset::semicolon;
				else if (c == '='                            ) return Charset::equal;
				else if (c == '.'                            ) return Charset::period;
				else if (c == ':'                            ) return Charset::colon;
				else                                           return Charset::any;
			}
		};

		state_type table[State::dimension][Charset::dimension];

		nik_ce GenericAssemblyDFTT() : table{}
		{
			table [ State::initial ][ Charset::ula       ] = State::ulan;
			table [ State::initial ][ Charset::semicolon ] = State::semicolon;
			table [ State::initial ][ Charset::equal     ] = State::equal;
			table [ State::initial ][ Charset::period    ] = State::period;

			table [ State::ulan    ][ Charset::ula       ] = State::ulan;
			table [ State::ulan    ][ Charset::digit     ] = State::ulan;
			table [ State::ulan    ][ Charset::colon     ] = State::colon;
		}

		nik_ce cstate_type move(cstate_type s, gcchar_type c) const
		{
			return table[s][Charset::map(c)];
		}
	};

	// interface:

		struct T_generic_assembly_dftt
		{
			using ArrayEnd		= T_store_U< _array_end_  >;
			using ArraySize		= T_store_U< _array_size_ >;

			nik_ces auto value	= GenericAssemblyDFTT{};
			nik_ces auto accept	= GenericAssemblyDFTT::State::accept;
			nik_ces auto end	= ArrayEnd::template result<>(GenericAssemblyDFTT::State::accept);
			nik_ces auto size	= ArraySize::template result<>(GenericAssemblyDFTT::State::accept);
			nik_ces auto token	= GenericAssemblyDFTT::State::token;

			nik_ces auto underscore_charset () { return dfa_charset("_");      }
			nik_ces auto test_charset       () { return dfa_charset("test");   }
			nik_ces auto goto_charset       () { return dfa_charset("goto");   }
			nik_ces auto branch_charset     () { return dfa_charset("branch"); }
			nik_ces auto return_charset     () { return dfa_charset("return"); }

			nik_ces auto find_pos(cstate_type n) { return numeric_find_pos(n, accept, end); }
			nik_ces auto is_final(cstate_type n) { return (n != size); }
		};

/***********************************************************************************************************************/

// automaton:

	struct T_generic_assembly_dfa
	{
		using transition_table = T_generic_assembly_dftt;

		using T_underscore_dfa	= T_keyword_dfa< transition_table::underscore_charset , '_' >;
		using T_test_dfa	= T_keyword_dfa< transition_table::test_charset       , 't' >;
		using T_goto_dfa	= T_keyword_dfa< transition_table::goto_charset       , 'g' >;
		using T_branch_dfa	= T_keyword_dfa< transition_table::branch_charset     , 'b' >;
		using T_return_dfa	= T_keyword_dfa< transition_table::return_charset     , 'r' >;

		nik_ces lexeme lex(gstring_type b, gstring_type e)
		{
			auto l = recognize<transition_table>(b, e);
			auto n = transition_table::find_pos(l.value);

			token_type t = TokenName::invalid;
			if (transition_table::is_final(n)) t = transition_table::token[n];

			return keyword_check(l.start, l.finish, t);
		}

		nik_ces lexeme keyword_check(gstring_type b, gstring_type e, ctoken_type t)
		{
			token_type rt = t;

			switch (t)
			{
				case 'i':
				{
					ctoken_type t0 = keyword(b, e);
					rt = (t0 == TokenName::invalid) ? t : t0;
					break;
				}
				case 'l':
				{
					ctoken_type t0 = keyword(b, e - 1);
					ctoken_type t1 = TokenName::keyword_label_error;
					rt = (t0 == TokenName::invalid) ? t : t1;
					break;
				}
			}

			return lexeme{b, e, (gindex_type) rt};
		}

		nik_ces token_type keyword(gstring_type b, gstring_type e)
		{
			switch (e - b)
			{
				case 1  : { return keyword_1(b, e)    ; }
				case 4  : { return keyword_4(b, e)    ; }
				case 6  : { return keyword_6(b, e)    ; }
				default : { return TokenName::invalid ; }
			}
		}

		nik_ces token_type keyword_1(gstring_type b, gstring_type e)
		{
			if   (recognizes< T_underscore_dfa >(b, e)) return T_underscore_dfa::token;
			else                                        return TokenName::invalid;
		}

		nik_ces token_type keyword_4(gstring_type b, gstring_type e)
		{
			if      (recognizes< T_test_dfa >(b, e)) return T_test_dfa::token;
			else if (recognizes< T_goto_dfa >(b, e)) return T_goto_dfa::token;
			else                                     return TokenName::invalid;
		}

		nik_ces token_type keyword_6(gstring_type b, gstring_type e)
		{
			if      (recognizes< T_branch_dfa >(b, e)) return T_branch_dfa::token;
			else if (recognizes< T_return_dfa >(b, e)) return T_return_dfa::token;
			else                                       return TokenName::invalid;
		}
	};

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

		gindex_type line_size;
		gindex_type label_size;
		gindex_type goto_size;
		gindex_type branch_size;
		gindex_type copy_size;
		gindex_type replace_size;
		gindex_type return_size;
		gindex_type graph_size;
		gindex_type stack_size;

		nik_ce source(const CharType (&s)[Size]) :

			string         { s          },
			finish         { s + length },

			max_entry_size { _zero      },
			max_ident_size { _zero      },

			line_size      { _zero      },
			label_size     { _zero      },
			goto_size      { _zero      },
			branch_size    { _zero      },
			copy_size      { _zero      },
			replace_size   { _zero      },
			return_size    { _zero      },
			graph_size     { _zero      },
			stack_size     { _zero      }

			{
				auto k = string;

				gindex_type cur_entry_size = _zero;

				while (k != finish)
				{
					auto l = T_dfa::lex(k, finish);

					switch (l.value)
					{
						case ';':
						{
							if (cur_entry_size > max_entry_size)
								max_entry_size = cur_entry_size;
							cur_entry_size = _zero;
							++line_size;
							break;
						}
						case 'i': { ++cur_entry_size ; ++max_ident_size ; break; }
						case 'l': { ++cur_entry_size ; ++label_size     ; break; }
						case 'g': { ++cur_entry_size ; ++goto_size      ; break; }
						case 'b': { ++cur_entry_size ; ++branch_size    ; break; }
						case 't': { ++cur_entry_size ; ++copy_size      ; break; }
						case '=': {                    ++replace_size   ; break; }
						case 'r': {                    ++return_size    ; break; }
					}

					++stack_size;
					k = l.finish;
				}

				graph_size = label_size + goto_size + branch_size;
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

