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

// array:

/***********************************************************************************************************************/

/*
// map:

	template<auto f, auto a, auto l, auto Op, auto s, auto U, auto S>
	nik_ce auto array_map_ = eval<_array_apply_, Op, U, S, s, _multimap_<_arg_deref_<f>>, a, l>;

// fold:

	template<auto f, auto init, auto a, auto l, auto Op, auto U, auto S>
	nik_ce auto array_fold_ = eval<_array_apply_, Op, U, S, U_pack_Vs<0>, _multifold_<_arg_deref_<f>, init>, a, l>;

// find:

//	template<auto p, auto a, auto l, auto Op, auto U, auto S>
//	nik_ce auto array_find_ = eval<_array_apply_, Op, U, S, _multifind<_arg_deref_<p>>, a, l>;
*/

// sift:

/*
// -> V:

	template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
	nik_ce auto V_sift(nik_vp(indices)(T_pack_Vs<Is...>*))
	{
		nik_ce auto Size	= Leng + 1;
		nik_ce auto arr		= ArrayModule::template apply<Type, Size, IteratorModule::Sift, Leng, p>(Arr);
		nik_ce auto leng	= arr.value[Leng];

		if nik_ce (leng != sizeof...(Is)) return arr;
		else return array<Type, arr.value[Is]...>;
	}

	template<typename Type, auto p, auto Arr, auto Leng, auto I0, auto... Is>
	nik_ce auto V_sift(nik_vp(indices)(T_pack_Vs<I0, Is...>*))
	{
		nik_ce auto Size	= sizeof...(Is) + 1;
		nik_ce auto arr		= apply<Type, Size, IteratorModule::Sift, Leng, p>(Arr);

		return array<Type, arr.value[Is]...>;
	}

// -> U:

	template<typename Type, auto p, auto Arr, auto Leng, auto I0, auto... Is>
	nik_ce auto U_sift(nik_vp(indices)(T_pack_Vs<I0, Is...>*))
	{
		nik_ce auto Size	= sizeof...(Is) + 1;
		nik_ce auto arr		= apply<Type, Size, IteratorModule::Sift, Leng, p>(Arr);

		return U_pack_Vs<arr.value[Is]...>;
	}
*/

	// subsequence:

/*
// -> V:

	template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
	nik_ce auto V_subsequence(nik_vp(indices)(T_pack_Vs<Is...>*))
		{ return V_apply<Type, IteratorModule::Sift, Arr>(U_pack_Vs<Leng, sizeof...(Is), p>, indices); }

// -> U:

	template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
	nik_ce auto U_subsequence(nik_vp(indices)(T_pack_Vs<Is...>*))
		{ return U_apply<Type, IteratorModule::Sift, Arr>(U_pack_Vs<Leng, sizeof...(Is), p>, indices); }
*/

// zip:

/*
// generic:

// -> V:

	template<typename Type, auto f, auto Arr1, auto Leng1, auto Arr2, typename Indices>
	nik_ce auto V_zip(Indices indices)
		{ return V_apply<Type, IteratorModule::Zip, Arr1, Arr2>(U_pack_Vs<Leng1, f>, indices); }

// -> U:

	template<typename Type, auto f, auto Arr1, auto Leng1, auto Arr2, typename Indices>
	nik_ce auto U_zip(Indices indices)
		{ return U_apply<Type, IteratorModule::Zip, Arr1, Arr2>(U_pack_Vs<Leng1, f>, indices); }
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// character sets:

	using global_char_type		= char;
	using gchar_type		= global_char_type;
	using gcchar_type		= global_char_type const;

	using global_string_type	= gcchar_type*;
	using gstring_type		= global_string_type;
	using cgstring_type		= global_string_type const;

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

// recognizers:

/***********************************************************************************************************************/

// generic charset:

	template<auto Size>
	nik_ce bool matches_charset(gcchar_type c, gcchar_type (&charset)[Size])
	{
		bool no_match = true;

		for (gstring_type i = charset; no_match && i != charset + Size; ++i)
			no_match = (*i != c);

		return !no_match;
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

	nik_ce gstring_type skip_whitespace(gstring_type b, gstring_type e)
	{
		while (b != e && matches_whitespace(*b)) ++b;

		return b;
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// attributes:

/***********************************************************************************************************************/

	struct LexerName
	{
		enum : gkey_type
		{
			empty = 0,
			initial ,
			dimension
		};
	};

	struct LexerToken
	{
		enum : gkey_type
		{
			invalid = 0,

			statement , period     , underscore , equal   ,
			test      , go_to      , branch     , re_turn ,
			label     , identifier ,
		};
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// state:

/***********************************************************************************************************************/

	struct state
	{
		gkey_type name;
		gkey_type token;

		nik_ce state() :
			name{LexerName::empty}, token{LexerToken::invalid} { }

		nik_ce state(gckey_type _v, gckey_type _t) :
			name{_v}, token{_t} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lexeme:

/***********************************************************************************************************************/

	struct lexeme
	{
		gstring_type start;
		gstring_type finish;

		gkey_type token;

		nik_ce lexeme() :

			start  {                     },
			finish {                     },
			token  { LexerToken::invalid }

			{ }

		nik_ce lexeme(gstring_type _s, gstring_type _f, gckey_type _t) :

			start  { _s },
			finish { _f },
			token  { _t }

			{ }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// deterministic finite automata:

/***********************************************************************************************************************/

// charset:

/*
	template<typename CharType, auto String, auto Size>
	nik_ce auto dfa_equiv_classes()
	{
		Array<CharType, Size> arr{};

		return tuple(arr, size);
	}

	template<typename CharType, auto String, auto Size>
	nik_ce auto dfa_charset()
	{
		nik_ce auto tup		= dfa_equiv_classes<CharType, String, Size>();
		nik_ce auto charset	= tuple_value<0>(tup).value; // fix design.
		nik_ce auto seg		= segment<tuple_value<1>(tup)>;

		return unpack_<seg, _array_to_list_, H_id, charset>;
	}

	template<typename CharType, CharType... Chars>
	nik_ce auto make_dfa_charset = dfa_charset<CharType, array<CharType, Chars...>, sizeof...(Chars)>();
*/

/***********************************************************************************************************************/

// charset map:

/*
	template<typename KeyType, auto... Keys>
	nik_ce gkey_type charset_map(KeyType k)
	{
		nik_ce auto key0	= array<KeyType, Keys...>;
		nik_ce auto key_size	= sizeof...(Keys);
		KeyType const *key	= key0;

		while (key != key0 + key_size)
		{
			if (k == *key) break;

			++key;
		}

		return (key - key0) + 1;
	}

	template<typename KeyType, auto... Keys>
	nik_ce gkey_type make_charset_map(nik_avp(*)(Maps...))
	{
		nik_ce auto key0	= array<KeyType, Keys...>;
		nik_ce auto key_size	= sizeof...(Keys);
		KeyType const *key	= key0;

		while (key != key0 + key_size)
		{
			if (k == *key) break;

			++key;
		}

		return (key - key0) + 1;
	}
*/

/***********************************************************************************************************************/

// (generic) keyword:

/*
	template<auto...> struct KeywordDFA;

		// Assumes CharsetMap will return a non-zero index for each
		// character (equivalence) class, and will otherwise return
		// zero (for any other character).

	template<typename CharType, CharType... Chars, nik_vp(Pack)(T_pack_Vs<Chars...>*), gkey_type Token>
	struct KeywordDFA<Pack, Token>
	{
		nik_ces auto      charset				= make_dfa_charset<CharType, Chars...>;
		nik_ces gkey_type charset_size				= eval<_length_, charset> + 1;
		nik_ces gkey_type (*charset_map)(gcchar_type c)		= make_charset_map(charset);

		nik_ces gkey_type row_size				= sizeof...(Chars);
		nik_ces gkey_type name_size				= row_size + 2;

		nik_ces auto col					= array<gkey_type, charset_map(Chars)...>;

		// table:

			state table[name_size][charset_size];

			nik_ce KeywordDFA() : table{} // initializes the empty state.
			{
				for (gkey_type row_pos = 1; row_pos != row_size; ++row_pos)
				{
					gkey_type col_pos   = col[row_pos - 1];
					gkey_type next_name = row_pos + 1;

					table[row_pos][col_pos] = state{next_name, LexerToken::invalid};
				}

				gkey_type row_pos   = row_size;
				gkey_type col_pos   = col[row_pos - 1];
				gkey_type next_name = row_pos + 1;

				table[row_pos][col_pos] = state{next_name, Token};
			}

			nik_ce const state & move(const state & s, gcchar_type c) const
			{
				return table[s.name][charset_map(c)];
			}

			nik_ce lexeme lex(gstring_type b, gstring_type e) const
			{
				b = skip_whitespace(b, e);
				gstring_type m = b;

				state s = state{LexerName::initial, LexerToken::invalid};

				while (m != e && s.name != LexerName::empty) s = move(s, *(m++));

				return lexeme{b, m, s.token};
			}
	};

	template<auto U_dfa>
	nik_ce bool recognized_by(lexeme & c)
	{
		using DFA = T_store_U<U_dfa>;

		DFA dfa{};

		return true;
	}
*/

/***********************************************************************************************************************/

// statement:

/*
	nik_ce gkey_type statement_charset_map(gcchar_type c)
	{
		if      (c == ';') return 1;
		else               return 0;
	}

	nik_ce auto statement_charset	= U_pack_Vs<';'>;
	using T_statement_dfa		= KeywordDFA<1, statement_charset, statement_charset_map, LexerToken::statement>;
	nik_ce auto U_statement_dfa	= U_store_T<T_statement_dfa>;
*/

/***********************************************************************************************************************/

// period:

/*
	nik_ce gkey_type period_charset_map(gcchar_type c)
	{
		if      (c == '.') return 1;
		else               return 0;
	}

	nik_ce auto period_charset	= U_pack_Vs<'.'>;
	using T_period_dfa		= KeywordDFA<1, period_charset, period_charset_map, LexerToken::period>;
	nik_ce auto U_period_dfa	= U_store_T<T_period_dfa>;
*/

/***********************************************************************************************************************/

// underscore:

/*
	nik_ce gkey_type underscore_charset_map(gcchar_type c)
	{
		if      (c == '_') return 1;
		else               return 0;
	}

	nik_ce auto underscore_charset	= U_pack_Vs<'_'>;
	using T_underscore_dfa		= KeywordDFA<1, underscore_charset, underscore_charset_map, LexerToken::underscore>;
	nik_ce auto U_underscore_dfa	= U_store_T<T_underscore_dfa>;
*/

/***********************************************************************************************************************/

// equal:

/*
	nik_ce gkey_type equal_charset_map(gcchar_type c)
	{
		if      (c == '=') return 1;
		else               return 0;
	}

	nik_ce auto equal_charset	= U_pack_Vs<'='>;
	using T_equal_dfa		= KeywordDFA<1, equal_charset, equal_charset_map, LexerToken::equal>;
	nik_ce auto U_equal_dfa		= U_store_T<T_equal_dfa>;
*/

/***********************************************************************************************************************/

// test:

/*
	nik_ce gkey_type test_charset_map(gcchar_type c)
	{
		if      (c == 't') return 1;
		else if (c == 'e') return 2;
		else if (c == 's') return 3;
		else               return 0;
	}

	nik_ce auto test_charset	= U_pack_Vs<'t', 'e', 's', 't'>;
	nik_ce auto test_charset_map0	= U_pack_Vs<'t', 'e', 's'>;
	using T_test_dfa		= KeywordDFA<3, test_charset, test_charset_map, LexerToken::test>;
	nik_ce auto U_test_dfa		= U_store_T<T_test_dfa>;
*/

/***********************************************************************************************************************/

// goto:

/*
	nik_ce gkey_type goto_charset_map(gcchar_type c)
	{
		if      (c == 'g') return 1;
		else if (c == 'o') return 2;
		else if (c == 't') return 3;
		else               return 0;
	}

	nik_ce auto goto_charset	= U_pack_Vs<'g', 'o', 't', 'o'>;
	using T_goto_dfa		= KeywordDFA<3, goto_charset, goto_charset_map, LexerToken::go_to>;
	nik_ce auto U_goto_dfa		= U_store_T<T_goto_dfa>;
*/

/***********************************************************************************************************************/

// branch:

/*
	nik_ce gkey_type branch_charset_map(gcchar_type c)
	{
		if      (c == 'b') return 1;
		else if (c == 'r') return 2;
		else if (c == 'a') return 3;
		else if (c == 'n') return 4;
		else if (c == 'c') return 5;
		else if (c == 'h') return 6;
		else               return 0;
	}

	nik_ce auto branch_charset	= U_pack_Vs<'b', 'r', 'a', 'n', 'c', 'h'>;
	using T_branch_dfa		= KeywordDFA<6, branch_charset, branch_charset_map, LexerToken::branch>;
	nik_ce auto U_branch_dfa	= U_store_T<T_branch_dfa>;
*/

/***********************************************************************************************************************/

// return:

/*
	nik_ce gkey_type return_charset_map(gcchar_type c)
	{
		if      (c == 'r') return 1;
		else if (c == 'e') return 2;
		else if (c == 't') return 3;
		else if (c == 'u') return 4;
		else if (c == 'n') return 5;
		else               return 0;
	}

	nik_ce auto return_charset	= U_pack_Vs<'r', 'e', 't', 'u', 'r', 'n'>;
	using T_return_dfa		= KeywordDFA<5, return_charset, return_charset_map, LexerToken::re_turn>;
	nik_ce auto U_return_dfa	= U_store_T<T_return_dfa>;
*/

/***********************************************************************************************************************/

// generic assembly:

/*
	struct GenericAssemblyDFA
	{
		// name:

			nik_ces gkey_type name_empty				= 0;
			nik_ces gkey_type name_initial				= 1;

			nik_ces gkey_type name_underscore_latin_alphanumeric	= 2;
			nik_ces gkey_type name_ulan 				= name_underscore_latin_alphanumeric;
			nik_ces gkey_type name_colon				= 3;

			nik_ces gkey_type name_size				= 4;

		// state:

			nik_ces state state_empty     { name_empty   , LexerToken::invalid    };
			nik_ces state state_initial   { name_initial , LexerToken::invalid    };

			nik_ces state state_ulan      { name_ulan    , LexerToken::identifier };
			nik_ces state state_colon     { name_colon   , LexerToken::label      };

		// charset:

			nik_ces gkey_type charset_any				= 0;

			nik_ces gkey_type charset_underscore_latin_alphabet	= 1;
			nik_ces gkey_type charset_ula				= charset_underscore_latin_alphabet;
			nik_ces gkey_type charset_digit				= 2;
			nik_ces gkey_type charset_colon				= 3;

			nik_ces gkey_type charset_size				= 4;

			nik_ces gkey_type charset(gcchar_type c)
			{
				if      (matches_digit(c)                    ) return charset_digit;
				else if (matches_underscore_latin_alphabet(c)) return charset_ula;
				else if (c == ':'                            ) return charset_colon;
				else                                           return charset_any;
			}

		// table:

			state table[name_size][charset_size];

			nik_ce GenericAssemblyDFA() : table{}
			{
				table [ name_initial ][ charset_ula   ] = state_ulan;

				table [ name_ulan    ][ charset_ula   ] = state_ulan;
				table [ name_ulan    ][ charset_digit ] = state_ulan;
				table [ name_ulan    ][ charset_colon ] = state_colon;
			}

			nik_ce auto move(const state & s, gcchar_type c) const
			{
				return table[s.name][charset(c)];
			}

			nik_ce auto lex(gstring_type b, gstring_type e) const
			{
				lexeme current{b, e, LexerToken::invalid};

				if      (recognized_by< U_statement_dfa  >(current)) statement_action  (current);
				else if (recognized_by< U_period_dfa     >(current)) period_action     (current);
				else if (recognized_by< U_underscore_dfa >(current)) underscore_action (current);
				else if (recognized_by< U_equal_dfa      >(current)) equal_action      (current);

				else if (recognized_by< U_test_dfa       >(current)) test_action       (current);
				else if (recognized_by< U_goto_dfa       >(current)) goto_action       (current);
				else if (recognized_by< U_branch_dfa     >(current)) branch_action     (current);
				else if (recognized_by< U_return_dfa     >(current)) return_action     (current);

				else                                                 lex_action        (current);

				return current;
			}

			nik_ce void statement_action(lexeme & c) const
			{
			//	auto statement_lexeme = statement_dfa.lex(c.start, c.finish);

			//	if (_lexeme.token == LexerToken::) ;
			}

			nik_ce void period_action(lexeme & c) const
			{
			//	auto period_lexeme = period_dfa.lex(c.start, c.finish);
			}

			nik_ce void underscore_action(lexeme & c) const
			{
			//	auto underscore_lexeme = underscore_dfa.lex(c.start, c.finish);
			}

			nik_ce void equal_action(lexeme & c) const
			{
			//	auto equal_lexeme = equal_dfa.lex(c.start, c.finish);
			}

			nik_ce void test_action(lexeme & c) const
			{
			//	auto test_lexeme = test_dfa.lex(c.start, c.finish);
			}

			nik_ce void goto_action(lexeme & c) const
			{
			//	auto goto_lexeme = goto_dfa.lex(c.start, c.finish);
			}

			nik_ce void branch_action(lexeme & c) const
			{
			//	auto branch_lexeme = branch_dfa.lex(c.start, c.finish);
			}

			nik_ce void return_action(lexeme & c) const
			{
			//	auto return_lexeme = return_dfa.lex(c.start, c.finish);
			}

			nik_ce void lex_action(lexeme & c) const
			{
			//	gstring_type m = b;

			//	state s = state{LexerName::initial, LexerToken::invalid};

			//	while (m != e && s.name != LexerName::empty) s = move(s, *(m++));
			}
	};

	nik_ce auto generic_assembly_dfa = GenericAssemblyDFA{};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_generics

