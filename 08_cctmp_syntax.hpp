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

// scanner:

/***********************************************************************************************************************/

// analyzer:

	struct T_generic_assembly_analyzer
	{
		using T_lexer = T_generic_assembly_lexer;

		// how many of these are actually needed?

		gindex_type pad_entry_size  , entry_size   , line_size   ;
		gindex_type dependency_size , replace_size , graph_size  ;
		gindex_type identifier_size , mutable_size , quote_size  , void_size   ;
		gindex_type assign_size     , apply_size   , copy_size   , paste_size  , return_size ;
		gindex_type label_size      , test_size    , branch_size , goto_size   ;

		nik_ce T_generic_assembly_analyzer(gstring_type b, gstring_type e) :

			pad_entry_size   {            },
			entry_size       {            },
			line_size        {            },

			dependency_size  {            },
			replace_size     {            },
			graph_size       {            },

			identifier_size  {            },
			mutable_size     {            },
			quote_size       {            },
			void_size        {            },

			assign_size      {            },
			apply_size       {            },
			copy_size        {            },
			paste_size       {            },
			return_size      {            },

			label_size       {            },
			test_size        {            },
			branch_size      {            },
			goto_size        {            }

			{
				gindex_type cur_entry_size = _zero;

				lexeme l;

				while (b != e)
				{
					T_lexer::lex(l, b, e);

					switch (l.token)
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
						case '#': {                    ++assign_size     ; break; }
						case '=': {                    ++apply_size      ; break; }
						case 'r': {                    ++return_size     ; break; }
						case 'l': {                    ++label_size      ; break; }
						case 'v': { ++cur_entry_size ; ++void_size       ; break; }
						case 't': { ++cur_entry_size ; ++test_size       ; break; }
						case 'b': {                    ++branch_size     ; break; }
						case 'g': {                    ++goto_size       ; break; }
					}

					b = l.finish;
				}

				dependency_size = goto_size       + branch_size  ;
				graph_size      = dependency_size + label_size   ;
				replace_size    = assign_size     + apply_size   - copy_size ;
				pad_entry_size  = entry_size      + replace_size ;
			}
	};

/***********************************************************************************************************************/

// interface:

	template<auto static_source>
	struct T_generic_assembly_scanner
	{
		nik_ces auto src   = member_value_U<static_source>;
		nik_ces auto value = T_generic_assembly_analyzer(src.begin(), src.end() - 1);
	};

/***********************************************************************************************************************/
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
				define , assign , apply , re_turn , test , branch , go_to , label ,
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
				carg , marg , var , copy , paste , recurse , label , jump , env ,
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
			nik_ces bool is_env     (sign_type s) { return (s == env    ); }
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

		nik_ce Line() : kind{}, array{}, start{array}, entry{array},
				has_void{}, has_paste{}, has_lookup{} { }

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

		bool has_local_copy;

		nik_ce Page() : array{}, start{array}, line{array}, has_local_copy{} { }

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

// interface (table of contents):

	template<auto static_scanner>
	struct T_generic_assembly_ast
	{
		nik_ces auto scanner	= member_value_U<static_scanner>;

		using page_type		= Page<gchar_type, scanner.line_size, scanner.pad_entry_size>;
		using line_type		= typename page_type::line_type;
		using entry_type	= typename line_type::entry_type;
		using centry_type	= typename line_type::centry_type;

		using label_type	= Subpage < page_type , scanner.label_size      >;
		using goto_type		= Subpage < page_type , scanner.goto_size       >;
		using branch_type	= Subpage < page_type , scanner.branch_size     >;
		using depend_type	= Subpage < page_type , scanner.dependency_size >;
		using graph_type	= Subpage < page_type , scanner.graph_size      >;
		using lookup_type	= Subpage < page_type , scanner.line_size       >;

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

			page{}, label{}, go_to{}, branch{}, // progression{},
			graph{}, lookup{}, arg_index{}, label_index{} { }

		// match:

			nik_ce auto is_arg_match(centry_type *k) const { return (k != page.begin()->end()); }

			nik_ce auto match_name(gstring_type b, gcstring_type e)
			{
				auto k = page.begin()->begin();

				return ptr_diff_equal(k->start, k->finish, b, e);
			}

			nik_ce auto match_arguments(gstring_type b, gcstring_type e)
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

			nik_ce auto match_label(gstring_type b, gcstring_type e)
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

			nik_ce auto has_copy   () const { return page.has_local_copy ; }

			nik_ce void set_copy   () { page.has_local_copy = true  ; }
			nik_ce void unset_copy () { page.has_local_copy = false ; }

		// entry:

			nik_ce auto current_start_at  (gcindex_type pos) const { return page.line->array[pos].start; }
			nik_ce auto current_finish_at (gcindex_type pos) const { return page.line->array[pos].finish; }
			nik_ce auto current_sign_at   (gcindex_type pos) const { return page.line->array[pos].sign; }
			nik_ce auto current_index_at  (gcindex_type pos) const { return page.line->array[pos].index; }

			nik_ce void set_arg_start  (gcstring_type start)  { page.array[_zero].entry->start  = start; }
			nik_ce void set_arg_finish (gcstring_type finish) { page.array[_zero].entry->finish = finish; }
			nik_ce void set_arg_sign   (csign_type sign)     { page.array[_zero].entry->sign   = sign; }
			nik_ce void set_arg_index  (gcindex_type index)  { page.array[_zero].entry->index  = index; }

			nik_ce void set_current_sign_at(gcindex_type pos, csign_type sign)
				{ page.line->array[pos].sign = sign; }

			nik_ce void set_current_index_at(gcindex_type pos, gcindex_type index)
				{ page.line->array[pos].index = index; }

			nik_ce void set_current_sign(csign_type sign)
				{ page.line->entry->sign = sign; }

			nik_ce void set_current_entry(clexeme & l, csign_type sign, gcindex_type index = _zero)
			{
				auto entry = page.line->entry;

				entry->start  = l.start;
				entry->finish = l.finish;
				entry->token  = l.token;
				entry->sign   = sign;
				entry->index  = index;
			}

		// line:

			nik_ce auto kind() const { return page.line->kind; }
			nik_ce void set_kind(ccontext_type k) { page.line->kind = k; }

			nik_ce auto has_void   () const { return page.line->has_void; }
			nik_ce auto has_paste  () const { return page.line->has_paste; }
			nik_ce auto has_lookup () const { return page.line->has_lookup; }

			nik_ce void set_void   () { page.line->has_void   = true  ; }
			nik_ce void set_paste  () { page.line->has_paste  = true  ; }
			nik_ce void set_lookup () { page.line->has_lookup = true  ; }

		// increment:

			nik_ce void increment_arg_index   () { ++arg_index          ; }
			nik_ce void increment_label_index () { ++label_index        ; }
			nik_ce void increment_arg_entry   () { ++page.array[0].entry; }
			nik_ce void increment_entry       () { ++page.line->entry   ; }
			nik_ce void increment_line        () { ++page.line          ; }
			nik_ce void increment_label       () { ++label.locus        ; }
			nik_ce void increment_goto        () { ++go_to.locus        ; }
			nik_ce void increment_branch      () { ++branch.locus       ; }
			nik_ce void increment_depend      () { ++depend.locus       ; }
			nik_ce void increment_graph       () { ++graph.locus        ; }
			nik_ce void increment_lookup      () { ++lookup.locus       ; }

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

			nik_ce auto lookup_line_assign(gindex_type n) const
				{ return (lookup.array[n]->kind == Context::assign); }

			nik_ce auto lookup_line_void(gindex_type n) const
				{ return lookup.array[n]->has_void; }

			nik_ce auto lookup_line_shift(gindex_type n) const
			{
				auto kind  = lookup.array[n]->kind;
				auto shift = kind == Context::assign ||
					     kind == Context::apply  ||
					     kind == Context::test   ;

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

	template<typename T_ast, template<typename, typename> typename T_translator>
	struct T_generic_assembly_parser
	{
		using T_lexer		= T_generic_assembly_lexer;
		using T_pda		= T_generic_assembly_pda;
		using parseme_type	= parseme<T_ast>;

		parseme_type value;

		nik_ce T_generic_assembly_parser(gcstring_type b, gcstring_type e) : value{}
			{ parse(value, b, e); }

		nik_ces void parse(parseme_type & p, gcstring_type b, gcstring_type e)
		{
			using T_stack  = Stack<T_pda::stack_size>;
			using T_action = T_translator<T_ast, T_stack>;

			T_generic_parser<T_action, T_ast, T_pda, T_lexer>::parse(p, b, e);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

