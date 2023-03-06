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

// (generic) stack:

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
		action_type action_name;

		nik_ce Production()                                 : body{    }, action_name{    } { }
		nik_ce Production(const Body & _b, caction_type _a) : body{ _b }, action_name{ _a } { }
	};

/***********************************************************************************************************************/

// interface:

	template<auto Size>
	struct Stack
	{
		nik_ces auto length		= Size;
		using size_type			= decltype(Size);

		token_type token[length];
		ctoken_type *start;
		token_type *current;
		ctoken_type *finish;

		nik_ce Stack(ctoken_type s) : token{}, start{token}, current{token}, finish{token + length}
		{
			*   current = '\0';
			* ++current = s;
		}

		nik_ce ctoken_type & front() const { return *current; }
		nik_ce  token_type & front()       { return *current; }

		nik_ce void pop() { if (current != start) --current; }

		nik_ce void push(gcstring_type b, size_type size)
		{
			auto k = b + size;
			while (k != b) *++current = *--k;
		}

		nik_ce auto begin () const { return start;  }
		nik_ce auto end   () const { return finish; }
		nik_ce auto size  () const { return length; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic parser:

/***********************************************************************************************************************/

// interface:

	template<typename T_action, typename T_ast, typename T_pda, auto StaticSource>
	struct T_generic_parser
	{
		nik_ces auto src	= T_store_U<StaticSource>::value;
		nik_ces auto pda	= T_pda::value;
		nik_ces auto act	= T_action::value;

		using stack_type	= Stack<src.stack_size>;
		using src_type		= decltype(src);
		using char_type		= typename src_type::char_type;
		using string_type	= typename src_type::string_type;
		using T_lexer		= typename src_type::T_lexer;

		using act_type		= decltype(act);
		using NAction		= typename act_type::NAction;
		using TAction		= typename act_type::TAction;

		stack_type stack;
		token_type front;
		string_type letter;
		lexeme word;
		Production production;

		T_ast tree;

		nik_ce T_generic_parser(bool p = true) :

			stack      { T_pda::nonterminal_start         },
			front      { stack.front()                    },
			letter     { src.string                       },
			word       { T_lexer::lex(letter, src.finish) },
			production {                                  },

			tree       {                                  }

			{ if (p) parse(); }

		nik_ce void parse()
		{
			while (*stack.current != '\0')
			{
				switch (T_pda::token_kind(front))
				{
					case TokenKind::nonterminal : { nonterminal(); break; }
					case TokenKind::terminal    : {    terminal(); break; }
					default                     : {       error(); break; }
				}

				front = stack.front();
			}

			// temporary code location:

			auto n = pda.action_name(*stack.current);
			auto update = act.terminal_action(n);
			update(tree, word);
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
			production = pda.production(front, word.value);
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
			word   = T_lexer::lex(letter, src.finish);
		}

		nik_ce void terminal_update_stack()
		{
			stack.pop();
		}

		nik_ce void nonterminal_update_action()
		{
			auto n = production.action_name;

			if (n != NAction::nop)
			{
				auto update = act.nonterminal_action(n);

				update(tree, word, stack);
			}
		}

		nik_ce void terminal_update_action()
		{
			auto n = pda.action_name(word.value);

			if (n != TAction::nop)
			{
				auto update = act.terminal_action(n);

				update(tree, word);
			}
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic assembly:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pushdown automaton:

/***********************************************************************************************************************/

// transition table:

	struct T_generic_assembly_pdtt
	{
		using ArraySize	= T_store_U<_array_size_>;

		struct Nonterminal
		{
			struct Action
			{
				enum : action_type
				{
					nop = 0,
					new_definition      , new_coordinate       ,
					new_conditional     , new_application      ,
					recover_instr_label , recover_instr_return ,
					dimension
				};
			};

			nik_ces gchar_type symbol[] = "VMOJINTECBS";

			nik_ces auto size   = ArraySize::template result<>(symbol) - 1;
			nik_ces auto finish = symbol + size;
			nik_ces auto start  = 'S';

		}; using NAction = typename Nonterminal::Action;

		struct Terminal
		{
			struct Action
			{
				enum : action_type
				{
					nop = 0,
					resolve_identifier ,
					resolve_paste      ,
					resolve_copy       ,
					resolve_test       ,
					resolve_branch     ,
					resolve_goto       ,
					resolve_return     ,
					resolve_label      ,
					resolve_mutable    ,
					resolve_quote      ,
					resolve_statement  ,
					resolve_accept     ,
					dimension
				};
			};

			nik_ces gchar_type symbol[] = ";i!q=._lgtbr";

			nik_ces auto size   = ArraySize::template result<>(symbol); // recognizes '\0'.
			nik_ces auto finish = symbol + size;

		}; using TAction = typename Terminal::Action;

		template<auto Size>
		nik_ces Production transition(gcchar_type (&str)[Size], caction_type action = NAction::nop)
		{
			auto body = Body(str, Size - 1);

			return Production{ body , action };
		}

		Production table[Nonterminal::size][Terminal::size];
		action_type list[Terminal::size];

		nik_ce T_generic_assembly_pdtt() : table{}, list{}
		{
			table_entry('S',  'i') = transition( "iN;BC"   , NAction::new_definition       );
			table_entry('N',  'i') = transition( "iN"                                      );
			table_entry('N',  ';') = transition( ""                                        );
			table_entry('C',  'l') = transition( "BC"                                      );
			table_entry('C', '\0') = transition( ""                                        );
			table_entry('B',  'l') = transition( "l;E"     , NAction::new_coordinate       );
			table_entry('E',  'i') = transition( "IJgi;"                                   );
			table_entry('E',  '!') = transition( "IJgi;"                                   );
			table_entry('E',  '.') = transition( "IJgi;"                                   );
			table_entry('E',  't') = transition( "IJgi;"                                   );
			table_entry('E',  'r') = transition( "rM;"                                     );
			table_entry('J',  'i') = transition( "IJ"                                      );
			table_entry('J',  '!') = transition( "IJ"                                      );
			table_entry('J',  '.') = transition( "IJ"                                      );
			table_entry('J',  't') = transition( "IJ"                                      );
			table_entry('J',  'g') = transition( ""                                        );
			table_entry('J',  'l') = transition( ""        , NAction::recover_instr_label  );
			table_entry('J',  'r') = transition( ""        , NAction::recover_instr_return );
			table_entry('I',  'i') = transition( "T=OV;"   , NAction::new_application      );
			table_entry('I',  '!') = transition( "T=OV;"   , NAction::new_application      );
			table_entry('I',  '.') = transition( "T=OV;"   , NAction::new_application      );
			table_entry('I',  't') = transition( "tOV;bi;" , NAction::new_conditional      );
			table_entry('V',  'i') = transition( "MV"                                      );
			table_entry('V',  '!') = transition( "MV"                                      );
			table_entry('V',  'q') = transition( "MV"                                      );
			table_entry('V',  '_') = transition( "MV"                                      );
			table_entry('V',  ';') = transition( ""                                        );
			table_entry('T',  'i') = transition( "i"                                       );
			table_entry('T',  '!') = transition( "!i"                                      );
			table_entry('T',  '.') = transition( "."                                       );
			table_entry('O',  'i') = transition( "i"                                       );
			table_entry('O',  'q') = transition( "q"                                       );
			table_entry('M',  'i') = transition( "i"                                       );
			table_entry('M',  '!') = transition( "!i"                                      );
			table_entry('M',  'q') = transition( "q"                                       );
			table_entry('M',  '_') = transition( "_"                                       );

			list_entry( 'i') = TAction::resolve_identifier ;
			list_entry( '!') = TAction::resolve_mutable    ;
			list_entry( '_') = TAction::resolve_paste      ;
			list_entry( '.') = TAction::resolve_copy       ;
			list_entry( 't') = TAction::resolve_test       ;
			list_entry( 'b') = TAction::resolve_branch     ;
			list_entry( 'g') = TAction::resolve_goto       ;
			list_entry( 'r') = TAction::resolve_return     ;
			list_entry( 'l') = TAction::resolve_label      ;
			list_entry( ';') = TAction::resolve_statement  ;
			list_entry( 'q') = TAction::resolve_quote      ;
			list_entry('\0') = TAction::resolve_accept     ;
		}

		nik_ce Production & table_entry(gcchar_type row_c, gcchar_type col_c)
		{
			auto row = numeric_find_pos(row_c, Nonterminal::symbol, Nonterminal::finish);
			auto col = numeric_find_pos(col_c,    Terminal::symbol,    Terminal::finish);

			return table[row][col];
		}

		nik_ce const Production & production(gcchar_type row_c, gcchar_type col_c) const
		{
			auto row = numeric_find_pos(row_c, Nonterminal::symbol, Nonterminal::finish);
			auto col = numeric_find_pos(col_c,    Terminal::symbol,    Terminal::finish);

			return table[row][col];
		}

		nik_ce action_type & list_entry(gcchar_type loc_c)
		{
			auto loc = numeric_find_pos(loc_c, Terminal::symbol, Terminal::finish);

			return list[loc];
		}

		nik_ce caction_type & action_name(gcchar_type loc_c) const
		{
			auto loc = numeric_find_pos(loc_c, Terminal::symbol, Terminal::finish);

			return list[loc];
		}
	};

/***********************************************************************************************************************/

// interface:

	struct T_generic_assembly_pda
	{
		using T_pdtt				= T_generic_assembly_pdtt;

		nik_ces auto value			= T_pdtt{};
		nik_ces auto nonterminal_symbol		= T_pdtt::Nonterminal::symbol;
		nik_ces auto nonterminal_finish		= T_pdtt::Nonterminal::finish;
		nik_ces auto nonterminal_start		= T_pdtt::Nonterminal::start;
		nik_ces auto terminal_symbol		= T_pdtt::Terminal::symbol;
		nik_ces auto terminal_finish		= T_pdtt::Terminal::finish;

		nik_ces bool is_nonterminal(ctoken_type t)
		{
			auto loc = numeric_find(t, nonterminal_symbol, nonterminal_finish);

			return (loc != nonterminal_finish);
		}

		nik_ces bool is_terminal(ctoken_type t)
		{
			auto loc = numeric_find(t, terminal_symbol, terminal_finish);

			return (loc != terminal_finish);
		}

		nik_ces auto token_kind(ctoken_type t)
		{
			if      (is_nonterminal(t)) return TokenKind::nonterminal;
			else if (is_terminal(t)   ) return TokenKind::terminal;
			else                        return TokenKind::nontoken;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// abstract syntax tree:

/***********************************************************************************************************************/

// attributes:

	// context:

		using context_type  = gkey_type;
		using ccontext_type = context_type const;

		struct Context
		{
			enum : context_type
			{
				none = 0,
				define , apply , re_turn , test , branch , go_to , label ,
				dimension
			};
		};

	// sign:

		using sign_type  = gkey_type;
		using csign_type = sign_type const;

		struct Sign // tokens are syntactic, signs are semantic.
		{
			enum : sign_type
			{
				na = 0,
				carg , marg, var , copy , paste , recurse , label , jump , lookup ,
				dimension
			};

			nik_ces bool is_carg    (sign_type s) { return (s == carg   ); }
			nik_ces bool is_marg    (sign_type s) { return (s == marg   ); }
			nik_ces bool is_var     (sign_type s) { return (s == var    ); }
			nik_ces bool is_copy    (sign_type s) { return (s == copy   ); }
			nik_ces bool is_paste   (sign_type s) { return (s == paste  ); }
			nik_ces bool is_recurse (sign_type s) { return (s == recurse); }
			nik_ces bool is_label   (sign_type s) { return (s == label  ); }
			nik_ces bool is_jump    (sign_type s) { return (s == jump   ); }
			nik_ces bool is_lookup  (sign_type s) { return (s == lookup ); }
		};

/***********************************************************************************************************************/

// entry:

	template<typename CharType>
	struct Entry
	{
		using char_type		= CharType;
		using cchar_type	= char_type const;

		cchar_type *start;
		cchar_type *finish;

		token_type token;
		sign_type sign;
		gindex_type index;

		nik_ce Entry() : start{}, finish{}, token{}, sign{}, index{} { }
	};

/***********************************************************************************************************************/

// line:

	template<typename CharType, auto Size>
	struct Line
	{
		using entry_type		= Entry<CharType>;
		using centry_type		= entry_type const;

		nik_ces auto length		= Size;

		entry_type array[length];
		centry_type *start;
		entry_type *entry;

		context_type kind;
		bool has_void; // currently allows discard.
		bool has_paste;
		bool has_lookup;
		bool has_arg_op;

		nik_ce Line() : kind{}, array{}, start{array}, entry{array},
				has_void{}, has_paste{}, has_lookup{}, has_arg_op{} { }

		nik_ce auto begin () const { return start; }
		nik_ce auto end   () const { return entry; }
		nik_ce auto size  () const { return (entry - start); }
	};

/***********************************************************************************************************************/

// page:

	template<typename CharType, auto LineSize, auto EntrySize>
	struct Page
	{
		using line_type			= Line<CharType, EntrySize>;
		using cline_type		= line_type const;

		nik_ces auto entry_size		= EntrySize;
		nik_ces auto length		= LineSize;

		line_type array[length];
		cline_type *start;
		line_type *line;

		bool has_local_side;
		bool has_local_copy;

		nik_ce Page() : array{}, start{array}, line{array}, has_local_side{}, has_local_copy{} { }

		nik_ce auto begin () const { return start; }
		nik_ce auto end   () const { return line; }
		nik_ce auto size  () const { return (line - start); }
	};

/***********************************************************************************************************************/

// subpage:

	template<typename, auto> struct Subpage;

	template<typename CharType, auto LineSize, auto EntrySize, auto Size>
	struct Subpage<Page<CharType, LineSize, EntrySize>, Size>
	{
		using locus_type		= Line<CharType, EntrySize>*; // mutable intention.
		using clocus_type		= locus_type const;

		nik_ces auto length		= Size;

		locus_type array[length];
		clocus_type *start;
		locus_type *locus;

		nik_ce Subpage() : array{}, start{array}, locus{array} { }

		nik_ce auto begin () const { return start; }
		nik_ce auto end   () const { return locus; }
		nik_ce auto size  () const { return (locus - start); }
	};

/***********************************************************************************************************************/

// source:

	template<typename CharType, auto Size>
	struct T_generic_assembly_source
	{
		using T_lexer			= T_generic_assembly_lexer;

		using char_type			= CharType;
		using cchar_type		= char_type const;
		using string_type		= cchar_type*;
		using cstring_type		= string_type const;
		using size_type			= decltype(Size);

		nik_ces size_type length	= Size - 1;

		cstring_type string;
		cstring_type finish;

		// how many of these are actually needed?

		gindex_type pad_entry_size  , entry_size   , line_size   , stack_size  ;
		gindex_type dependency_size , replace_size , graph_size  ;
		gindex_type identifier_size , mutable_size , quote_size  ;
		gindex_type assign_size     , copy_size    , paste_size  , return_size ;
		gindex_type label_size      , test_size    , branch_size , goto_size   ;

		nik_ce T_generic_assembly_source(const CharType (&s)[Size]) :

			string           { s          },
			finish           { s + length },

			pad_entry_size   {            },
			entry_size       {            },
			line_size        {            },
			stack_size       {            },

			dependency_size  {            },
			replace_size     {            },
			graph_size       {            },

			identifier_size  {            },
			mutable_size     {            },
			quote_size       {            },

			assign_size      {            },
			copy_size        {            },
			paste_size       {            },
			return_size      {            },

			label_size       {            },
			test_size        {            },
			branch_size      {            },
			goto_size        {            }

			{
				auto k = string;

				gindex_type cur_entry_size = _zero;

				while (k != finish)
				{
					auto l = T_lexer::lex(k, finish);

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
						case 'i': { ++cur_entry_size ; ++identifier_size ; break; }
						case '!': {                    ++mutable_size    ; break; }
						case 'q': { ++cur_entry_size ; ++quote_size      ; break; }
						case '.': { ++cur_entry_size ; ++copy_size       ; break; }
						case '_': { ++cur_entry_size ; ++paste_size      ; break; }
						case '=': {                    ++assign_size     ; break; }
						case 'r': {                    ++return_size     ; break; }
						case 'l': {                    ++label_size      ; break; }
						case 't': { ++cur_entry_size ; ++test_size       ; break; }
						case 'b': {                    ++branch_size     ; break; }
						case 'g': {                    ++goto_size       ; break; }
					}

					++stack_size;
					k = l.finish;
				}

				dependency_size = goto_size       + branch_size;
				graph_size      = dependency_size + label_size;
				replace_size    = assign_size     - copy_size;
				pad_entry_size  = entry_size      + replace_size;
			}
	};

/***********************************************************************************************************************/

// interface (table of contents):

	template<auto StaticSource>
	struct T_generic_assembly_ast
	{
		nik_ces auto src	= T_store_U<StaticSource>::value;

		using src_type		= decltype(src);
		using char_type		= typename src_type::char_type;
		using string_type	= typename src_type::string_type;
		using cstring_type	= typename src_type::cstring_type;

		using page_type		= Page<char_type, src.line_size, src.pad_entry_size>;
		using line_type		= typename page_type::line_type;
		using entry_type	= typename line_type::entry_type;
		using centry_type	= typename line_type::centry_type;

		using label_type	= Subpage < page_type , src.label_size      >;
		using goto_type		= Subpage < page_type , src.goto_size       >;
		using branch_type	= Subpage < page_type , src.branch_size     >;
		using depend_type	= Subpage < page_type , src.dependency_size >;
		using graph_type	= Subpage < page_type , src.graph_size      >;
		using lookup_type	= Subpage < page_type , src.line_size       >;

		page_type page;
		label_type label;
		goto_type go_to;
		branch_type branch;
		depend_type depend;
		graph_type graph;
		lookup_type lookup;

		gindex_type arg_index;
		gindex_type label_index;

		nik_ce T_generic_assembly_ast() :

			page{}, label{}, go_to{}, branch{}, graph{}, lookup{}, arg_index{}, label_index{} { }

		// match:

			nik_ce auto is_arg_match(centry_type *k) const { return (k != page.begin()->end()); }

			nik_ce auto match_name(string_type b, cstring_type e)
			{
				auto k = page.begin()->begin();

				return ptr_diff_equal(k->start, k->finish, b, e);
			}

			nik_ce auto match_arguments(string_type b, cstring_type e)
			{
				auto l = page.begin();
				auto k = l->begin() + 1; // args, not name.

				while (k != l->end())
				{
					if (ptr_diff_equal(k->start, k->finish, b, e)) break;

					++k;
				}

				return k;
			}

			nik_ce auto match_label(string_type b, cstring_type e)
			{
				auto k = label.begin();

				while (k != label.end())
				{
					auto j = (*k)->begin();
					if (ptr_diff_equal(j->start, j->finish - 1, b, e)) break;

					++k;
				}

				return k;
			}

		// local:

			nik_ce auto has_side() const { return page.has_local_side; }
			nik_ce auto has_copy() const { return page.has_local_copy; }

			nik_ce void set_side   () { page.has_local_side = true  ; }
			nik_ce void unset_side () { page.has_local_side = false ; }

			nik_ce void set_copy   () { page.has_local_copy = true  ; }
			nik_ce void unset_copy () { page.has_local_copy = false ; }

		// entry:

			nik_ce auto current_start_at  (gcindex_type pos) const { return page.line->array[pos].start; }
			nik_ce auto current_finish_at (gcindex_type pos) const { return page.line->array[pos].finish; }
			nik_ce auto current_sign_at   (gcindex_type pos) const { return page.line->array[pos].sign; }
			nik_ce auto current_index_at  (gcindex_type pos) const { return page.line->array[pos].index; }

			nik_ce void set_arg_start  (cstring_type start)  { page.array[_zero].entry->start  = start; }
			nik_ce void set_arg_finish (cstring_type finish) { page.array[_zero].entry->finish = finish; }
			nik_ce void set_arg_sign   (csign_type sign)     { page.array[_zero].entry->sign   = sign; }
			nik_ce void set_arg_index  (gcindex_type index)  { page.array[_zero].entry->index  = index; }

			nik_ce void set_current_sign_at(gcindex_type pos, csign_type sign)
				{ page.line->array[pos].sign = sign; }

			nik_ce void set_current_index_at(gcindex_type pos, gcindex_type index)
				{ page.line->array[pos].index = index; }

			nik_ce void set_current_entry(clexeme & l, csign_type sign, gcindex_type index = _zero)
			{
				auto entry = page.line->entry;

				entry->start  = l.start;
				entry->finish = l.finish;
				entry->token  = l.value;
				entry->sign   = sign;
				entry->index  = index;
			}

		// line:

			nik_ce auto kind() const { return page.line->kind; }
			nik_ce void set_kind(ccontext_type k) { page.line->kind = k; }

			nik_ce auto has_void   () const { return page.line->has_void; }
			nik_ce auto has_paste  () const { return page.line->has_paste; }
			nik_ce auto has_lookup () const { return page.line->has_lookup; }
			nik_ce auto has_arg_op () const { return page.line->has_arg_op; }

			nik_ce void set_void   () { page.line->has_void   = true  ; }
			nik_ce void set_paste  () { page.line->has_paste  = true  ; }
			nik_ce void set_lookup () { page.line->has_lookup = true  ; }
			nik_ce void set_arg_op () { page.line->has_arg_op = true  ; }

		// increment:

			nik_ce void increment_arg_index () { ++arg_index          ; }
			nik_ce void increment_arg_entry () { ++page.array[0].entry; }
			nik_ce void increment_entry     () { ++page.line->entry   ; }
			nik_ce void increment_line      () { ++page.line          ; }
			nik_ce void increment_label     () { ++label.locus        ; }
			nik_ce void increment_goto      () { ++go_to.locus        ; }
			nik_ce void increment_branch    () { ++branch.locus       ; }
			nik_ce void increment_depend    () { ++depend.locus       ; }
			nik_ce void increment_graph     () { ++graph.locus        ; }
			nik_ce void increment_lookup    () { ++lookup.locus       ; }

		// bookmark:

			nik_ce void bookmark_lookup     () { *lookup.locus = page.line; }
			nik_ce void bookmark_graph      () { *graph.locus  = page.line; }
			nik_ce void bookmark_dependency () { *depend.locus = page.line; }
			nik_ce void bookmark_branch     () { *branch.locus = page.line; }
			nik_ce void bookmark_goto       () { *go_to.locus  = page.line; }
			nik_ce void bookmark_label      () { *label.locus  = page.line; }

		// update:

			nik_ce void update_lookup()
			{
				if (!page.line->has_lookup)
					{ set_lookup(); bookmark_lookup(); increment_lookup(); }
			}

			nik_ce void update_copy_paste()
				{ if (page.has_local_copy) { set_paste(); unset_copy(); } }

		// lookup:

			nik_ce auto lookup_entry_start(gindex_type m, gindex_type n) const
				{ return lookup.array[m]->array[n].start; }

			nik_ce auto lookup_entry_finish(gindex_type m, gindex_type n) const
				{ return lookup.array[m]->array[n].finish; }

			nik_ce auto lookup_entry_sign(gindex_type m, gindex_type n) const
				{ return lookup.array[m]->array[n].sign; }

			nik_ce auto lookup_entry_index(gindex_type m, gindex_type n) const
				{ return lookup.array[m]->array[n].index; }

			nik_ce auto lookup_line_void(gindex_type n) const
				{ return lookup.array[n]->has_void; }

			nik_ce auto lookup_line_shift(gindex_type n) const
			{
				auto kind  = lookup.array[n]->kind;
				auto shift = (kind == Context::apply || kind == Context::test);

				return shift ? _one : _zero;
			}

			nik_ce auto lookup_line_size(gindex_type n) const
			{
				auto size  = lookup.array[n]->size();
				auto shift = lookup_line_shift(n);

				return size - shift;
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser:

/***********************************************************************************************************************/

// interface:

	template<template<typename, typename> typename T_translator>
	struct T_generic_assembly_parser
	{
		using T_pda = T_generic_assembly_pda;

		template<auto static_src>
		struct parser
		{
			nik_ces auto src	= T_store_U<static_src>::value;
			using T_stack		= Stack<src.stack_size>;
			using T_ast		= T_generic_assembly_ast<static_src>;
			using T_action		= T_translator<T_ast, T_stack>;
			nik_ces auto value     	= T_generic_parser<T_action, T_ast, T_pda, static_src>{};
		};

		template<auto SourceCallable>
		nik_ces auto parse = parser<_static_object_<SourceCallable>>::value;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

