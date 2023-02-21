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

// assembler:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic assembly:

/***********************************************************************************************************************/

// attributes:

	using context_type  = gkey_type;
	using ccontext_type = context_type const;

/***********************************************************************************************************************/

// context:

	struct Context
	{
		enum : context_type
		{
			none = 0,
			function , label , test , branch , apply , go_to , re_turn ,
			dimension
		};
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
		gindex_type index;

		nik_ce Entry() : start{}, finish{}, token{}, index{} { }
	};

/***********************************************************************************************************************/

// line:

	template<typename CharType, auto Size>
	struct Line
	{
		using entry_type		= Entry<CharType>;
		using centry_type		= entry_type const;

		nik_ces auto length		= Size;

		context_type kind;
		entry_type array[length];
		centry_type *start;
		entry_type *entry;
		gindex_type offset;

		nik_ce Line() : kind{}, array{}, start{array}, entry{array}, offset{} { }

		nik_ce auto begin () const { return start; }
		nik_ce auto end   () const { return entry; }
		nik_ce auto size  () const { return (entry - start); }
	};

/***********************************************************************************************************************/

// page:

	template<typename CharType, auto LineSize, auto EntrySize>
	struct Page
	{
		using char_type			= CharType;
		using line_type			= Line<char_type, EntrySize>;
		using cline_type		= line_type const;

		nik_ces auto entry_size		= EntrySize;
		nik_ces auto length		= LineSize;

		bool is_offset;
		line_type array[length];
		cline_type *start;
		line_type *line;

		nik_ce Page() : is_offset{}, array{}, start{array}, line{array} { }

		nik_ce auto begin () const { return start; }
		nik_ce auto end   () const { return line; }
		nik_ce auto size  () const { return (line - start); }
	};

/***********************************************************************************************************************/

// subpage:

	template<typename PageType, auto LineSize>
	struct Subpage
	{
		using char_type			= typename PageType::char_type;
		using locus_type		= Line<char_type, PageType::entry_size>*; // mutable intention.
		using clocus_type		= locus_type const;

		nik_ces auto length		= LineSize;

		locus_type array[length];
		clocus_type *start;
		locus_type *locus;

		nik_ce Subpage() : array{}, start{array}, locus{array} { }

		nik_ce auto begin () const { return start; }
		nik_ce auto end   () const { return locus; }
		nik_ce auto size  () const { return (locus - start); }
	};

/***********************************************************************************************************************/

// table of contents:

	template<auto StaticSource>
	struct TableOfContents
	{
		nik_ces auto src		= T_store_U<StaticSource>::value;

		using src_type			= decltype(src);
		using char_type			= typename src_type::char_type;
		using string_type		= typename src_type::string_type;
		using cstring_type		= typename src_type::cstring_type;

		using page_type			= Page<char_type, src.line_size, src.entry_size>;

		using label_type		= Subpage < page_type , src.label_size  >;
		using goto_type			= Subpage < page_type , src.goto_size   >;
		using branch_type		= Subpage < page_type , src.branch_size >;
		using depend_type		= Subpage < page_type , src.depend_size >;
		using graph_type		= Subpage < page_type , src.graph_size  >;
		using param_type		= Subpage < page_type , src.param_size  >;

		page_type page;
		label_type label;
		goto_type go_to;
		branch_type branch;
		depend_type depend;
		graph_type graph;
		param_type param;

		gindex_type arg_index;
		gindex_type label_index;

		nik_ce TableOfContents() :

			page{}, label{}, go_to{}, branch{}, graph{}, param{}, arg_index{}, label_index{} { }

		nik_ce void increment_entry  () { ++(page.line->entry); }
		nik_ce void increment_line   () { ++(page.line       ); }
		nik_ce void increment_label  () { ++(label.locus     ); }
		nik_ce void increment_goto   () { ++(go_to.locus     ); }
		nik_ce void increment_branch () { ++(branch.locus    ); }
		nik_ce void increment_depend () { ++(depend.locus    ); }
		nik_ce void increment_graph  () { ++(graph.locus     ); }
		nik_ce void increment_param  () { ++(param.locus     ); }

		nik_ce auto & entry() { return *(page.line->entry); }

		nik_ce void copy(clexeme & l)
		{
			page.line->entry->start  = l.start;
			page.line->entry->finish = l.finish;
			page.line->entry->token  = l.value;
		}

		nik_ce auto match_identifier(string_type b, cstring_type e) // doesn't yet account for "._"
		{
			using size_type	= gindex_type; // temporary policy.
			auto k		= page.begin()->begin();

			while (k != page.begin()->entry)
			{
				if (ptr_diff_equal<size_type>(k->start, k->finish, b, e)) break;

				++k;
			}

			return k;
		}

		nik_ce auto match_label(string_type b, cstring_type e) // doesn't yet account for "._"
		{
			using size_type	= gindex_type; // temporary policy.
			auto k		= label.begin();

			while (k != label.end())
			{
				auto j = (*k)->begin();
				if (ptr_diff_equal<size_type>(j->start, j->finish - 1, b, e)) break;

				++k;
			}

			return k;
		}

		nik_ce auto param_at(gindex_type m, gindex_type n) const { return param.array[m]->array[n]; }
		nik_ce auto param_size(gindex_type m) const { return param.array[m]->size(); }
		nik_ce auto offset_at(gindex_type n) const { return page.array[n].offset; }
	};

/***********************************************************************************************************************/

// translation action:

	struct GenericAssemblyTA
	{
		struct Nonterminal
		{
			struct Name
			{
				enum : action_type
				{
					nop = 0,
					new_function    , new_block        , new_conditional , new_application ,
					sub_instr_label , sub_instr_return ,
					dimension
				};
			};

			template<typename TOC, typename S>
			nik_ces void nop(TOC & toc, clexeme & l, S & s) { }

			template<typename TOC, typename S>
			nik_ces void new_function(TOC & toc, clexeme & l, S & s)
			{
				toc.page.line->kind = Context::function;
				toc.arg_index = _four; // offset to include: na, lookup, copy, paste.
			}

			template<typename TOC, typename S>
			nik_ces void new_block(TOC & toc, clexeme & l, S & s)
			{
				toc.page.line->kind = Context::label;

				*toc.graph.locus    = toc.page.line;
				*toc.label.locus    = toc.page.line;

				toc.increment_graph();
				toc.increment_label();
			}

			template<typename TOC, typename S>
			nik_ces void new_conditional(TOC & toc, clexeme & l, S & s)
			{
				toc.page.line->kind = Context::test;

				*toc.param.locus    = toc.page.line;

				toc.increment_param();
			}

			template<typename TOC, typename S>
			nik_ces void new_application(TOC & toc, clexeme & l, S & s)
			{
				toc.page.line->kind = Context::apply;

				*toc.param.locus    = toc.page.line;

				toc.increment_param();
			}

			template<typename TOC, typename S> // can assume "gi;" is the current stack front.
			nik_ces void sub_instr_label(TOC & toc, clexeme & l, S & s)
			{
				*(s.current    ) = 'l';
				*(s.current - 1) = ';';
				*(s.current - 2) = 'E';

				new_block(toc, l, s);
			}

			template<typename TOC, typename S> // can assume "gi;" is the current stack front.
			nik_ces void sub_instr_return(TOC & toc, clexeme & l, S & s)
			{
				*(s.current    ) = 'r';
				*(s.current - 1) = 'M';
				*(s.current - 2) = ';';
			}
		};

		struct Terminal
		{
			struct Name
			{
				enum : action_type
				{
					nop = 0,
					resolve_identifier ,
					resolve_underscore ,
					resolve_period     ,
					resolve_test       ,
					resolve_branch     ,
					resolve_goto       ,
					resolve_return     ,
					resolve_label      ,
					resolve_statement  ,
					resolve_accept     ,
					dimension
				};
			};

			template<typename TOC>
			nik_ces void nop(TOC & toc, clexeme & l) { }

		// resolve:

			template<typename TOC>
			nik_ces void resolve_identifier(TOC & toc, clexeme & l)
			{
				switch (toc.page.line->kind)
				{
					case Context::function : { identifier_argument_entry (toc, l); break; }
					case Context::apply    : { identifier_apply_entry    (toc, l); break; }
					case Context::test     : { identifier_test_entry     (toc, l); break; }
					case Context::branch   : { identifier_branch_entry   (toc, l); break; }
					case Context::go_to    : { identifier_goto_entry     (toc, l); break; }
					case Context::re_turn  : { identifier_return_entry   (toc, l); break; }
				}

				toc.increment_entry();
			}

			template<typename TOC>
			nik_ces void resolve_underscore(TOC & toc, clexeme & l)
			{
				switch (toc.page.line->kind)
				{
					case Context::apply : { underscore_apply_entry (toc, l); break; }
					case Context::test  : { underscore_test_entry  (toc, l); break; }
				}

				toc.increment_entry();
			}

			template<typename TOC>
			nik_ces void resolve_period(TOC & toc, clexeme & l)
			{
				switch (toc.page.line->kind)
				{
					case Context::apply : { period_apply_entry (toc, l); break; }
				}

				toc.increment_entry();
			}

			template<typename TOC>
			nik_ces void resolve_test(TOC & toc, clexeme & l)
			{
				toc.copy(l);
				toc.entry().index = _two; // signifies a copy.
				toc.increment_entry();
			}

			template<typename TOC>
			nik_ces void resolve_branch(TOC & toc, clexeme & l)
			{
				toc.page.line->kind = Context::branch;

				*toc.graph.locus    = toc.page.line;
				*toc.depend.locus   = toc.page.line;
				*toc.branch.locus   = toc.page.line;

				toc.increment_graph();
				toc.increment_depend();
				toc.increment_branch();
			}

			template<typename TOC>
			nik_ces void resolve_goto(TOC & toc, clexeme & l)
			{
				toc.page.line->kind = Context::go_to;

				*toc.graph.locus    = toc.page.line;
				*toc.depend.locus   = toc.page.line;
				*toc.go_to.locus    = toc.page.line;

				toc.increment_graph();
				toc.increment_depend();
				toc.increment_goto();
			}

			template<typename TOC>
			nik_ces void resolve_return(TOC & toc, clexeme & l)
			{
				toc.page.line->kind = Context::re_turn;
			}

			template<typename TOC>
			nik_ces void resolve_label(TOC & toc, clexeme & l)
			{
				toc.copy(l);
				toc.entry().index = toc.label_index++;
				toc.increment_entry();
			}

			template<typename TOC>
			nik_ces void resolve_statement(TOC & toc, clexeme & l)
			{
				toc.increment_line();
				if (toc.page.is_offset)
				{
					toc.page.line->offset = 1;
					toc.page.is_offset    = false;
				}
			}

			template<typename TOC, typename SubpageType>
			nik_ces void resolve_subpage(TOC & toc, SubpageType & subpage)
			{
				for (auto k = subpage.begin(); k != subpage.end(); ++k)
				{
					auto j = (*k)->begin();
					auto l = toc.match_label(j->start, j->finish);
					if (l == toc.label.end()) ; // error
					else (*k)->array->index = (*l)->begin()->index;
				}
			}

			template<typename TOC>
			nik_ces void resolve_accept(TOC & toc, clexeme & l)
			{
				resolve_subpage(toc, toc.go_to);
				resolve_subpage(toc, toc.branch);
			}

		// identifier:

			template<typename TOC>
			nik_ces void identifier_argument_entry(TOC & toc, clexeme & l)
			{
				toc.copy(l);
				toc.entry().index = toc.arg_index++;
			}

			template<typename TOC>
			nik_ces void identifier_apply_entry(TOC & toc, clexeme & l)
			{
				toc.copy(l);

				auto k = toc.match_identifier(l.start, l.finish);
				if (k != toc.page.begin()->entry) toc.entry().index = k->index;
				else toc.entry().index = _one;
			}

			template<typename TOC>
			nik_ces void identifier_test_entry(TOC & toc, clexeme & l)
			{
				toc.copy(l);

				auto k = toc.match_identifier(l.start, l.finish);
				if (k != toc.page.begin()->entry) toc.entry().index = k->index;
				else toc.entry().index = _one;
			}

			template<typename TOC>
			nik_ces void identifier_branch_entry(TOC & toc, clexeme & l)
			{
				toc.copy(l);
			}

			template<typename TOC>
			nik_ces void identifier_goto_entry(TOC & toc, clexeme & l)
			{
				toc.copy(l);
			}

			template<typename TOC>
			nik_ces void identifier_return_entry(TOC & toc, clexeme & l)
			{
				toc.copy(l);

				auto k = toc.match_identifier(l.start, l.finish);
				if (k == toc.page.begin()->entry) ; // error
				else toc.entry().index = k->index;
			}

		// underscore:

			template<typename TOC>
			nik_ces void underscore_apply_entry(TOC & toc, clexeme & l)
			{
				toc.copy(l);
				toc.entry().index = _three; // signifies a paste.
			}

			template<typename TOC>
			nik_ces void underscore_test_entry(TOC & toc, clexeme & l)
			{
				toc.copy(l);
				toc.entry().index = _three; // signifies a paste.
			}

		// period:

			template<typename TOC>
			nik_ces void period_apply_entry(TOC & toc, clexeme & l)
			{
				toc.copy(l);
				toc.entry().index  = _two; // signifies a copy.
				toc.page.is_offset = true;
			}
		};
	};

/***********************************************************************************************************************/

// abstract syntax tree:

	template<typename TOC, typename S>
	struct GenericAssemblyAST
	{
		using nonterminal_type		= void(*)(TOC &, clexeme &, S &);
		using terminal_type		= void(*)(TOC &, clexeme &);
		using Nonterminal		= typename GenericAssemblyTA::Nonterminal;
		using NAction			= typename Nonterminal::Name;
		using Terminal			= typename GenericAssemblyTA::Terminal;
		using TAction			= typename Terminal::Name;

		nonterminal_type nonterminal[NAction::dimension];
		   terminal_type    terminal[TAction::dimension];

		nik_ce GenericAssemblyAST() : nonterminal{}, terminal{}
		{
			nonterminal[ NAction::nop              ] = Nonterminal::template nop              <TOC, S>;
			nonterminal[ NAction::new_function     ] = Nonterminal::template new_function     <TOC, S>;
			nonterminal[ NAction::new_block        ] = Nonterminal::template new_block        <TOC, S>;
			nonterminal[ NAction::new_conditional  ] = Nonterminal::template new_conditional  <TOC, S>;
			nonterminal[ NAction::new_application  ] = Nonterminal::template new_application  <TOC, S>;
			nonterminal[ NAction::sub_instr_label  ] = Nonterminal::template sub_instr_label  <TOC, S>;
			nonterminal[ NAction::sub_instr_return ] = Nonterminal::template sub_instr_return <TOC, S>;

			terminal[ TAction::nop                 ] = Terminal::template nop                 <TOC>;
			terminal[ TAction::resolve_identifier  ] = Terminal::template resolve_identifier  <TOC>;
			terminal[ TAction::resolve_underscore  ] = Terminal::template resolve_underscore  <TOC>;
			terminal[ TAction::resolve_period      ] = Terminal::template resolve_period      <TOC>;
			terminal[ TAction::resolve_test        ] = Terminal::template resolve_test        <TOC>;
			terminal[ TAction::resolve_branch      ] = Terminal::template resolve_branch      <TOC>;
			terminal[ TAction::resolve_goto        ] = Terminal::template resolve_goto        <TOC>;
			terminal[ TAction::resolve_return      ] = Terminal::template resolve_return      <TOC>;
			terminal[ TAction::resolve_label       ] = Terminal::template resolve_label       <TOC>;
			terminal[ TAction::resolve_statement   ] = Terminal::template resolve_statement   <TOC>;
			terminal[ TAction::resolve_accept      ] = Terminal::template resolve_accept      <TOC>;
		}
	};

	// interface:

		template<typename TOC, typename S>
		struct T_generic_assembly_ast
		{
			nik_ces auto value = GenericAssemblyAST<TOC, S>{};
		};

/***********************************************************************************************************************/

// transition table:

	struct GenericAssemblyPDTT
	{
		using ArraySize	= T_store_U<_array_size_>;
		using NAction	= typename GenericAssemblyTA::Nonterminal::Name;
		using TAction	= typename GenericAssemblyTA::Terminal::Name;

		struct Nonterminal
		{
			nik_ces gchar_type symbol[] = "VMJINTECBS";

			nik_ces auto size   = ArraySize::template result<>(symbol) - 1;
			nik_ces auto finish = symbol + size;
			nik_ces auto start  = 'S';
		};

		struct Terminal
		{
			nik_ces gchar_type symbol[] = ";i=._lgtbr";

			nik_ces auto size   = ArraySize::template result<>(symbol); // recognizes '\0'.
			nik_ces auto finish = symbol + size;
		};

		template<auto Size>
		nik_ces Production transition(gcchar_type (&str)[Size], caction_type action = NAction::nop)
		{
			auto body = Body(str, Size - 1);

			return Production{ body , action };
		}

		Production table[Nonterminal::size][Terminal::size];
		action_type list[Terminal::size];

		nik_ce GenericAssemblyPDTT() : table{}, list{}
		{
			table_entry('S',  'i') = transition( "iN;BC"   , NAction::new_function     );
			table_entry('N',  'i') = transition( "iN"                                  );
			table_entry('N',  ';') = transition( ""                                    );
			table_entry('C',  'l') = transition( "BC"                                  );
			table_entry('C', '\0') = transition( ""                                    );
			table_entry('B',  'l') = transition( "l;E"     , NAction::new_block        );
			table_entry('E',  'i') = transition( "IJgi;"                               );
			table_entry('E',  '.') = transition( "IJgi;"                               );
			table_entry('E',  't') = transition( "IJgi;"                               );
			table_entry('E',  'r') = transition( "rM;"                                 );
			table_entry('J',  'i') = transition( "IJ"                                  );
			table_entry('J',  '.') = transition( "IJ"                                  );
			table_entry('J',  't') = transition( "IJ"                                  );
			table_entry('J',  'g') = transition( ""                                    );
			table_entry('J',  'l') = transition( ""        , NAction::sub_instr_label  );
			table_entry('J',  'r') = transition( ""        , NAction::sub_instr_return );
			table_entry('I',  'i') = transition( "T=iV;"   , NAction::new_application  );
			table_entry('I',  '.') = transition( "T=iV;"   , NAction::new_application  );
			table_entry('I',  't') = transition( "tiV;bi;" , NAction::new_conditional  );
			table_entry('V',  'i') = transition( "MV"                                  );
			table_entry('V',  '_') = transition( "MV"                                  );
			table_entry('V',  ';') = transition( ""                                    );
			table_entry('T',  'i') = transition( "i"                                   );
			table_entry('T',  '.') = transition( "."                                   );
			table_entry('M',  'i') = transition( "i"                                   );
			table_entry('M',  '_') = transition( "_"                                   );

			list_entry( 'i') = TAction::resolve_identifier ;
			list_entry( '_') = TAction::resolve_underscore ;
			list_entry( '.') = TAction::resolve_period     ;
			list_entry( 't') = TAction::resolve_test       ;
			list_entry( 'b') = TAction::resolve_branch     ;
			list_entry( 'g') = TAction::resolve_goto       ;
			list_entry( 'r') = TAction::resolve_return     ;
			list_entry( 'l') = TAction::resolve_label      ;
			list_entry( ';') = TAction::resolve_statement  ;
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

		nik_ce caction_type & action(gcchar_type loc_c) const
		{
			auto loc = numeric_find_pos(loc_c, Terminal::symbol, Terminal::finish);

			return list[loc];
		}
	};

	// interface:

		struct T_generic_assembly_pdtt
		{
			nik_ces auto value		= GenericAssemblyPDTT{};
			nik_ces auto nt_symbol		= GenericAssemblyPDTT::Nonterminal::symbol;
			nik_ces auto nt_finish		= GenericAssemblyPDTT::Nonterminal::finish;
			nik_ces auto nt_start		= GenericAssemblyPDTT::Nonterminal::start;
			nik_ces auto t_symbol		= GenericAssemblyPDTT::Terminal::symbol;
			nik_ces auto t_finish		= GenericAssemblyPDTT::Terminal::finish;

			nik_ces auto token_kind(ctoken_type t)
			{
				if      (numeric_find(t, nt_symbol, nt_finish) != nt_finish) return TokenKind::nonterminal;
				else if (numeric_find(t,  t_symbol,  t_finish) !=  t_finish) return TokenKind::terminal;
				else                                                         return TokenKind::nontoken;
			}
		};

/***********************************************************************************************************************/

// automaton:

	struct T_generic_assembly_pda
	{
		using T_pdtt = T_generic_assembly_pdtt;

		template<auto static_src>
		struct parser
		{
			nik_ces auto src	= T_store_U<static_src>::value;
			using T_syntax		= TableOfContents<static_src>;
			using T_stack		= Stack<src.stack_size>;
			using T_ast		= T_generic_assembly_ast<T_syntax, T_stack>;
			nik_ces auto value     	= GenericPDA<T_ast, T_pdtt, T_syntax, static_src>{};
		};

		template<auto SourceCallable>
		nik_ces auto parse = parser<_static_object_<SourceCallable>>::value;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

