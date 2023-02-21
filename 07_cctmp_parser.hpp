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
			nonterminal , terminal ,
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

	template<typename T_ast, typename T_pdtt, typename T_syntax, auto StaticSource>
	struct GenericPDA
	{
		nik_ces auto src		= T_store_U<StaticSource>::value;
		nik_ces auto ast		= T_ast::value;
		nik_ces auto tt			= T_pdtt::value;

		using stack_type		= Stack<src.stack_size>;
		using src_type			= decltype(src);
		using char_type			= typename src_type::char_type;
		using string_type		= typename src_type::string_type;
		using T_dfa			= typename src_type::T_dfa;

		using ast_type			= decltype(ast);
		using NAction			= typename ast_type::NAction;
		using TAction			= typename ast_type::TAction;

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
					case TokenKind::nonterminal : { nonterminal(); break; }
					case TokenKind::terminal    : {    terminal(); break; }
					default                     : {       error(); break; }
				}

				front = stack.front();
			}

			// temporary code location:

			auto n = tt.action(*stack.current);
			auto update = ast.terminal[n];
			update(syntax, word);
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

			if (n != NAction::nop)
			{
				auto update = ast.nonterminal[n];

				update(syntax, word, stack);
			}
		}

		nik_ce void terminal_update_action()
		{
			auto n = tt.action(word.value);

			if (n != TAction::nop)
			{
				auto update = ast.terminal[n];

				update(syntax, word);
			}
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic assembly:

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

		gindex_type entry_size;
		gindex_type line_size;
		gindex_type stack_size;

		gindex_type ident_size;
		gindex_type assign_size;
		gindex_type label_size;
		gindex_type goto_size;
		gindex_type test_size;
		gindex_type branch_size;
		gindex_type period_size;
		gindex_type return_size;

		gindex_type copy_size;
		gindex_type replace_size;
		gindex_type depend_size;
		gindex_type graph_size;
		gindex_type param_size;

		nik_ce source(const CharType (&s)[Size]) :

			string         { s          },
			finish         { s + length },

			entry_size     { _one       },
			line_size      { _one       },
			stack_size     {            },

			ident_size     {            },
			assign_size    {            },
			label_size     {            },
			goto_size      {            },
			test_size      {            },
			branch_size    {            },
			period_size    {            },
			return_size    {            },

			copy_size      {            },
			replace_size   {            },
			depend_size    {            },
			graph_size     {            },
			param_size     {            }

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
							if (cur_entry_size > entry_size)
								entry_size = cur_entry_size;
							cur_entry_size = _zero;
							++line_size;
							break;
						}
						case 'i': { ++cur_entry_size ; ++ident_size  ; break; }
						case '=': {                    ++assign_size ; break; }
						case 'l': {                    ++label_size  ; break; }
						case 'g': {                    ++goto_size   ; break; }
						case 't': { ++cur_entry_size ; ++test_size   ; break; }
						case 'b': {                    ++branch_size ; break; }
						case '.': { ++cur_entry_size ; ++period_size ; break; }
						case 'r': {                    ++return_size ; break; }
					}

					++stack_size;
					k = l.finish;
				}

				copy_size     = test_size   + period_size;
				replace_size  = assign_size - period_size;
				depend_size   = goto_size   + branch_size;
				graph_size    = depend_size + label_size;
				param_size    = copy_size   + replace_size;
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

