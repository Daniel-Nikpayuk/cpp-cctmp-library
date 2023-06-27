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

// syntax:

namespace chord {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

	nik_ce auto _zero					= cctmp::_zero;
	nik_ce auto _one					= cctmp::_one;
	nik_ce auto _two					= cctmp::_two;
	nik_ce auto _three					= cctmp::_three;
	nik_ce auto _four					= cctmp::_four;
	nik_ce auto _five					= cctmp::_five;
	nik_ce auto _six					= cctmp::_six;
	nik_ce auto _seven					= cctmp::_seven;
	nik_ce auto _eight					= cctmp::_eight;
	nik_ce auto _nine					= cctmp::_nine;
	nik_ce auto _ten					= cctmp::_ten;

	template<auto U>
	nik_ce auto & member_value_U				= cctmp::member_value_U<U>;

	template<auto U>
	using T_store_U						= cctmp::T_store_U<U>;

	template<auto... Vs>
	using T_pack_Vs						= cctmp::T_pack_Vs<Vs...>;

	template<auto U>
	using member_type_U					= cctmp::member_type_U<U>;

	template<auto Op, auto... Vs>
	nik_ce auto eval					= cctmp::eval<Op, Vs...>;

	nik_ce auto _equal_					= cctmp::_equal_;
	nik_ce auto _par_segment_				= cctmp::_par_segment_;

	nik_ce auto _level_append_0_action_			= cctmp::_level_append_0_action_;
	nik_ce auto _level_1_append_action_			= cctmp::_level_1_append_action_;

	using gckey_type					= cctmp::gckey_type;

	using strlit_type					= cctmp::strlit_type;
	using cstrlit_type					= cctmp::cstrlit_type;
	using cstrlit_ref					= cctmp::cstrlit_ref;
	nik_ce auto U_strlit_type				= cctmp::U_strlit_type;

	template<typename T, typename S = gindex_type>
	using citerator						= cctmp::citerator<T, S>;

	using cguider						= cctmp::cguider;
	using cguider_ctype_ref					= cctmp::cguider_ctype_ref;

	using action_type					= cctmp::action_type;
	nik_ce auto U_action_type				= cctmp::U_action_type;

	using AN						= cctmp::AN;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// scanner:

/***********************************************************************************************************************/

// level:

	struct Level { enum : gkey_type { entry = 0, line, dimension }; };

/***********************************************************************************************************************/

// scanner:

	class T_generic_assembly_scanner
	{
		public:

			using T_lexer		= T_generic_assembly_lexer;
			using Token		= typename T_lexer::Token;

			// how many of these are actually needed?

			struct Total
			{
				enum : gkey_type
				{
					arg        = Level::dimension  ,
					jump       , replace  , tag    ,
					identifier , mu_table , quote  , vo_id ,
					assign     , apply    , copy   , paste , re_turn ,
					label      , test     , branch , go_to ,
					dimension
				};
			};

		private:

			// casting prevents template<auto> + unnamed enum issues:

			using current_type	= cctmp::sequence < gindex_type , (gindex_type) Level::dimension >;
			using max_type		= cctmp::sequence < gindex_type , (gindex_type) Level::dimension >;
			using total_type	= cctmp::sequence < gindex_type , (gindex_type) Total::dimension >;

			current_type current;

		public:

			max_type max;
			total_type total;

			nik_ce T_generic_assembly_scanner(lexeme l)
			{
				current.fullsize();
				max.fullsize();
				total.fullsize();

				while (l.not_empty())
				{
					T_lexer::lex(l.retract());

					switch (l.token)
					{
						case Token::statement  : { update_semicolon   (); break; }
						case Token::identifier : { update_identifier  (); break; }
						case Token::mu_table   : { update_punctuation (); break; }
						case Token::quote      : { update_quote       (); break; }
						case Token::copy       : { update_period      (); break; }
						case Token::paste      : { update_underscore  (); break; }
						case Token::assign     : { update_octothorpe  (); break; }
						case Token::apply      : { update_equal       (); break; }
						case Token::re_turn    : { update_return      (); break; }
						case Token::label      : { update_label       (); break; }
						case Token::vo_id      : { update_void        (); break; }
						case Token::test       : { update_test        (); break; }
						case Token::branch     : { update_branch      (); break; }
						case Token::go_to      : { update_goto        (); break; }
					}
				}

				update_accept();
			}

		private:

			nik_ce void update_punctuation () { ++total[Total::mu_table]; }
			nik_ce void update_octothorpe  () { ++total[Total::assign  ]; }
			nik_ce void update_equal       () { ++total[Total::apply   ]; }
			nik_ce void update_return      () { ++total[Total::re_turn ]; }
			nik_ce void update_branch      () { ++total[Total::branch  ]; }
			nik_ce void update_goto        () { ++total[Total::go_to   ]; }

			nik_ce void update_semicolon () {      update_entry_max(); ++total[Level::line ]; }
			nik_ce void update_label     () {   ++total[Total::label]; ++total[Level::entry]; }
			nik_ce void update_void      () { ++current[Level::entry]; ++total[Total::vo_id]; }
			nik_ce void update_test      () { ++current[Level::entry]; ++total[Total::test ]; }

			nik_ce void update_identifier()
			{
				++current[Level::entry];
				++total[Total::identifier];
				++total[Level::entry];
			}

			nik_ce void update_quote()
			{
				++current[Level::entry];
				++total[Total::quote];
				++total[Level::entry];
			}

			nik_ce void update_period()
			{
				++current[Level::entry];
				++total[Total::copy];
				++total[Level::entry];
			}

			nik_ce void update_underscore()
			{
				++current[Level::entry];
				++total[Total::paste];
				++total[Level::entry];
			}

			nik_ce void update_max(gckey_type level)
			{
				if (current[level] > max[level]) max[level] = current[level];
				current[level] = _zero;
			}

			nik_ce void update_entry_max () { update_max(Level::entry); }
			nik_ce void update_line_max  () { update_max(Level::line); } // redundant ? (total == max)

			nik_ce void update_accept()
			{
				total[Total::jump   ] = total[Total::go_to ] + total[Total::branch ] ;
				total[Total::tag    ] = total[Total::jump  ] + total[Total::label  ] ;
				total[Total::replace] = total[Total::assign] +
						        total[Total::apply ] - total[Total::copy   ] ;
				total[Total::arg    ] = max  [Level::entry ] + total[Total::replace] ;
			}
	};

/***********************************************************************************************************************/

// interface:

	template<auto static_source>
	struct T_generic_assembly_scanned
	{
		nik_ces auto src	= member_value_U<static_source>;
		nik_ces auto value	= T_generic_assembly_scanner(src.cselect());
		using type		= decltype(value);

		using Token			= typename type::Token;
		nik_ces auto invalid_token	= Token::invalid;
		nik_ces auto prompt_token	= Token::prompt;
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
				assign , apply , re_turn , test , branch , go_to , label ,
				dimension
			};

			nik_ces bool is_assign (context_type c) { return (c == assign  ); }
			nik_ces bool is_apply  (context_type c) { return (c == apply   ); }
			nik_ces bool is_return (context_type c) { return (c == re_turn ); }
			nik_ces bool is_test   (context_type c) { return (c == test    ); }
			nik_ces bool is_branch (context_type c) { return (c == branch  ); }
			nik_ces bool is_goto   (context_type c) { return (c == go_to   ); }
			nik_ces bool is_label  (context_type c) { return (c == label   ); }
		};

	// sign:

		using sign_type  = gkey_type;
		using csign_type = sign_type const;

		struct Sign // tokens are syntactic, signs are semantic.
		{
			enum : sign_type
			{
				na = 0,
				carg , marg , copy , paste , recurse , label , jump , env ,
				dimension
			};

			nik_ces bool is_carg    (sign_type s) { return (s == carg   ); }
			nik_ces bool is_marg    (sign_type s) { return (s == marg   ); }
			nik_ces bool is_copy    (sign_type s) { return (s == copy   ); }
			nik_ces bool is_paste   (sign_type s) { return (s == paste  ); }
			nik_ces bool is_recurse (sign_type s) { return (s == recurse); }
			nik_ces bool is_label   (sign_type s) { return (s == label  ); }
			nik_ces bool is_jump    (sign_type s) { return (s == jump   ); }
			nik_ces bool is_env     (sign_type s) { return (s == env    ); }
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// levels:

/***********************************************************************************************************************/

// line:

	struct level_line
	{
		context_type kind;

		bool has_void; // currently allows discard.
		bool has_paste;
		bool has_lookup;

		nik_ce level_line() : kind{}, has_void{}, has_paste{}, has_lookup{} { }
	};

/***********************************************************************************************************************/

// entry:

	template<typename CharType>
	struct T_level_entry : public cctmp::T_icon<CharType>
	{
		sign_type sign;
		gindex_type index;

		nik_ce T_level_entry() : sign{}, index{} { }
	};

	using level_entry = T_level_entry<gchar_type>;

/***********************************************************************************************************************/

// tag:

	struct level_tag
	{
		gindex_type entry;
		gindex_type index;

		nik_ce level_tag() : entry{}, index{} { }
	};

/***********************************************************************************************************************/

// arg:

	template<typename CharType>
	struct T_level_arg : public cctmp::T_icon<CharType>
	{
		using base	= cctmp::T_icon<CharType>;
		using cbase	= base const;

		nik_ce T_level_arg() : base{} { }
	};

	using level_arg = T_level_arg<gchar_type>;

/***********************************************************************************************************************/

// env:

	template<typename Type, auto Size>
	class T_level_env : public cctmp::sequence<Type, Size>
	{
		protected:

			using base		= cctmp::sequence<Type, Size>;
			using cline_ptr		= level_line const*;

		public:

			using type		= typename base::type;
			using ctype		= typename base::ctype;
			using ctype_cptr	= typename base::ctype_cptr;

		protected:

			type position;
			type difference;
			type offset;

			cline_ptr line;

		private:

			nik_ce void update_size(gindex_type s) { difference = s - offset; }
			nik_ce void update_shift() { offset = !is_void() && !is_return(); }

		public:

			nik_ce T_level_env() : position{}, difference{}, offset{}, line{} { }

			nik_ce void initialize(const cguider & g, const level_line & l)
			{
				position = g.pos();
				line     = &l;
			}

			nik_ce gindex_type size  () const { return difference; }

			nik_ce void update(ctype_cptr origin)
			{
				cguider line_iter{origin, position};

				update_shift();
				update_size(line_iter.size());

				for (line_iter += offset; line_iter.not_end(); ++line_iter)
					base::push(~line_iter.next());
			}

		// line:

			nik_ce bool is_assign () const { return Context::is_assign(line->kind); }
			nik_ce bool is_return () const { return Context::is_return(line->kind); }
			nik_ce bool is_void   () const { return line->has_void; }
	};

	template<auto Size>
	using level_env = T_level_env<gindex_type, Size>;

/***********************************************************************************************************************/

// interface (tree; table of contents):

	template<auto static_scanned>
	struct T_generic_assembly_ast
	{
		using scanned_type		= member_type_U<static_scanned>;
		using T_lexer			= T_generic_assembly_lexer;
		using Token			= typename T_lexer::Token;
		using Total			= typename T_generic_assembly_scanner::Total;

		nik_ces auto & scanned		= member_value_U<static_scanned>;
		nik_ces auto invalid_token	= T_store_U<static_scanned>::invalid_token;
		nik_ces auto prompt_token	= T_store_U<static_scanned>::prompt_token;

		nik_ces gindex_type label_total		= scanned.total[Total::label];
		nik_ces gindex_type go_into_total	= label_total;

		nik_ces gindex_type entry_total		= scanned.total[Level::entry] + go_into_total;
		nik_ces gindex_type line_total		= scanned.total[Level::line] + go_into_total;
		nik_ces gindex_type rline_total		= line_total - 1; // rest (non arg) lines.

		nik_ces gindex_type jump_total		= scanned.total[Total::jump] + go_into_total;
		nik_ces gindex_type tag_total		= scanned.total[Total::tag] + go_into_total;
		nik_ces gindex_type arg_total		= scanned.total[Total::arg];

		nik_ces gindex_type entry_max		= scanned.max[Level::entry];
		nik_ces gindex_type line_max		= line_total; // rline_total ?

		nik_ces gindex_type level_2_size	= line_max + 3;
		nik_ces gindex_type level_1_size	= line_total * (entry_max + 3);
		nik_ces gindex_type level_0_size	= entry_total * 3;

		nik_ces gindex_type hierarchy_length	= level_0_size + level_1_size + level_2_size;

		using hierarchy_type			= cctmp::T_hierarchy < gindex_type{3} , hierarchy_length >;
		using cnavigator_type			= typename hierarchy_type::cnavigator_type;
		using navigator_type			= typename hierarchy_type::navigator_type;

		using level_lookup			= level_env<entry_max>;

		using level_line_type			= cctmp::sequence < level_line   , rline_total >;
		using level_entry_type			= cctmp::sequence < level_entry  , entry_total >;
		using level_lookup_type			= cctmp::sequence < level_lookup , rline_total >;
		using level_tag_type			= cctmp::sequence < level_tag    , tag_total   >;
		using level_arg_type			= cctmp::sequence < level_arg    , arg_total   >;

		using label_type			= cctmp::subsequence < level_tag , label_total >;
		using jump_type				= cctmp::subsequence < level_tag , jump_total  >;

		hierarchy_type hierarchy;
		navigator_type current;
		level_line_type line_level;
		level_entry_type entry_level;
		level_lookup_type lookup_level;
		level_tag_type tag_level;
		level_arg_type arg_level;
		level_arg name;

		level_line_type *level_1;
		level_entry_type *level_0;

		label_type label;
		jump_type jump;

		lexeme lexed;
		gindex_type arity;
		bool has_local_copy;

		nik_ce T_generic_assembly_ast() :

			hierarchy{line_max, entry_max, gindex_type{0}}, current{hierarchy.origin()},
			level_0{&entry_level}, level_1{&line_level},
			arity{}, has_local_copy{} { }

		// local:

			nik_ce auto line_size   () const { return line_level.size()   ; }
			nik_ce auto entry_size  () const { return entry_level.size()  ; }
			nik_ce auto arg_size    () const { return arg_level.size()    ; }
			nik_ce auto pad_size    () const { return arg_size() - arity  ; }

			nik_ce auto has_copy   () const { return has_local_copy; }

			nik_ce void set_copy   () { has_local_copy = true  ; }
			nik_ce void unset_copy () { has_local_copy = false ; }

			nik_ce void update_copy_paste()
				{ if (has_local_copy) { set_paste(); unset_copy(); } }

			nik_ce void set_arity  () { arity = arg_level.size(); }

			nik_ce const auto & line_at  (const cguider & g) const { return line_level  [~g]; }
			nik_ce const auto & entry_at (const cguider & g) const { return entry_level [~g]; }

		// line:

			nik_ce void first_line()
			{
				cctmp::apply<_level_append_0_action_>(this, level_1);
				+current;
			}

			nik_ce void append_line() { cctmp::apply<_level_1_append_action_>(this); }

			nik_ce auto kind       (const cguider & g) const { return line_at(g).kind; }
			nik_ce auto has_void   (const cguider & g) const { return line_at(g).has_void; }
			nik_ce auto has_paste  (const cguider & g) const { return line_at(g).has_paste; }
			nik_ce auto has_lookup (const cguider & g) const { return line_at(g).has_lookup; }

			nik_ce void set_kind(ccontext_type k) { line_level.last()->kind = k; }

			nik_ce void set_void   () { line_level.last()->has_void   = true; }
			nik_ce void set_paste  () { line_level.last()->has_paste  = true; }
			nik_ce void set_lookup () { line_level.last()->has_lookup = true; }

		// entry:

			nik_ce void set_current_entry(clexeme *l, csign_type sign, gcindex_type index = _zero)
			{
				entry_level.end()->copy(l);
				entry_level.end()->sign  = sign;
				entry_level.end()->index = index;
			}

			nik_ce void append_entry(clexeme *l, csign_type sign, gcindex_type index = _zero)
			{
				set_current_entry(l, sign, index);
				cctmp::apply<_level_append_0_action_>(this, level_0);
			}

		// name:

			nik_ce auto match_name  (clexeme *l) { return name.same(l); }
			nik_ce void append_name (clexeme *l) { name.copy(l); }

		// arg:

			nik_ce auto match_arguments(clexeme *l)
				{ return arg_level.citerate().find(l->left_cselect()); }

			nik_ce void push_arg(clexeme *l)
			{
				arg_level.end()->copy(l);
				arg_level.upsize();
			}

			nik_ce void append_arg(clexeme *l)
			{
				auto k = match_arguments(l);

				if (k.is_end()) push_arg(l);
				else { } // error.
			}

		// lookup:

			nik_ce const auto & lookup_entry(gcindex_type n, gcindex_type m) const
				{ return entry_level[lookup_level[n][m]]; }

			nik_ce auto lookup_entry_sign(gcindex_type n, gcindex_type m) const
				{ return lookup_entry(n, m).sign; }

			nik_ce auto lookup_entry_index(gcindex_type n, gcindex_type m) const
				{ return lookup_entry(n, m).index; }

			nik_ce void update_lookup()
				{ if (!line_level.last()->has_lookup) { set_lookup(); push_lookup(); } }

			nik_ce void push_lookup()
			{
				auto g = current.cguide();
				lookup_level.end()->initialize(g, line_at(g));
				lookup_level.upsize();
			}

			nik_ce void resolve_lookup()
			{
				for (auto k = lookup_level.begin(); k != lookup_level.end(); ++k)
					k->update(hierarchy.origin());
			}

		// tag:

			nik_ce auto match_label(const level_entry & jump_entry)
			{
				auto label_iter = label.citerate();

				for (; label_iter.not_end(); ++label_iter)
				{
					auto label_entry = entry_level[(*label_iter)->entry];
					label_entry.downright();

					if (jump_entry.same(label_entry)) break;
				}

				return label_iter;
			}

			template<typename TagSeq>
			nik_ce void subtag(TagSeq & t)
			{
				tag_level.end()->entry = entry_level.max();
				t.push(tag_level.end());
				tag_level.upsize();
			}

			nik_ce void tag_label  () { tag_level.end()->index = label.size(); subtag(label); }
			nik_ce void tag_goto   () { subtag(jump); }
			nik_ce void tag_branch () { subtag(jump); }

			nik_ce void resolve_jump()
			{
				for (auto k = jump.cbegin(); k != jump.cend(); ++k)
				{
					auto & entry = entry_level[(*k)->entry];
					auto j = match_label(entry);
					if (j.not_end()) entry.index = (*j)->index;
					else { } // error
				}
			}

		// lvalue:

			nik_ce void lvalue_identifier(clexeme *l, gcindex_type index)
				{ append_entry(l, Sign::carg, index); }

			nik_ce void lvalue_variable(clexeme *l)
			{
				append_entry(l, Sign::carg, arg_size());
				push_arg(l);
			}

			nik_ce void lvalue_unknown(clexeme *l)
			{
				if (!match_name(l)) lvalue_variable(l);
				else { } // error: Sign::recurse
			}

		// _value:

			nik_ce void _value_identifier(clexeme *l, sign_type sign, gcindex_type index)
			{
				auto shift = line_level.last()->has_paste ? _one : _zero;
				append_entry(l, sign, index + shift);
			}

		// mvalue:

			nik_ce void mvalue_identifier(clexeme *l, gcindex_type index)
				{ _value_identifier(l, Sign::marg, index); }

		// rvalue:

			nik_ce void rvalue_identifier(clexeme *l, gcindex_type index)
				{ _value_identifier(l, Sign::carg, index); }

			nik_ce void rvalue_unknown(clexeme *l)
			{
				auto j = match_name(l);
				auto s = j ? Sign::recurse : Sign::env;

				append_entry(l, s);
				update_lookup();
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// translation action:

	template<action_type, auto...> struct T_generic_assembly_translation_action;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// name:

	struct GenericAssemblyActionName
	{
		enum : action_type
		{
			nop = AN::nop,

			define_name, define_arg,
			end_arg, new_line, first_line,
			label, branch, go_to, go_into, re_turn,
			application, voidication, conditional, assignment,
			lvalue, mvalue, rvalue,
			copy, paste, quote,
			accept,

			dimension
		};

	}; using GAAN = GenericAssemblyActionName;

/***********************************************************************************************************************/

// nop:

	template<auto... filler>
	struct T_generic_assembly_translation_action<GAAN::nop, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l) { }
	};

// define name:

	template<auto... filler>
	struct T_generic_assembly_translation_action<GAAN::define_name, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->append_name(l); }
	};

// define arg:

	template<auto... filler>
	struct T_generic_assembly_translation_action<GAAN::define_arg, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->append_arg(l); }
	};

// end arg:

	template<auto... filler>
	struct T_generic_assembly_translation_action<GAAN::end_arg, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->set_arity(); }
	};

// first line:

	template<auto... filler>
	struct T_generic_assembly_translation_action<GAAN::first_line, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->first_line(); }
	};

// new line:

	template<auto... filler>
	struct T_generic_assembly_translation_action<GAAN::new_line, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->append_line();
			t->update_copy_paste();
		}
	};

// label:

	template<auto... filler>
	struct T_generic_assembly_translation_action<GAAN::label, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->set_kind(Context::label);
			t->append_entry(l, Sign::label, t->label.size());
			t->tag_label();
		}
	};

// branch:

	template<auto... filler>
	struct T_generic_assembly_translation_action<GAAN::branch, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->set_kind(Context::branch);
			t->append_entry(l, Sign::jump);
			t->tag_branch();
		}
	};

// goto:

	template<auto... filler>
	struct T_generic_assembly_translation_action<GAAN::go_to, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->set_kind(Context::go_to);
			t->append_entry(l, Sign::jump);
			t->tag_goto();
		}
	};

	template<auto... filler>
	struct T_generic_assembly_translation_action<GAAN::go_into, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			lexeme k = *l;
			t->set_kind(Context::go_to);
			t->append_entry(&--k, Sign::jump);
			t->tag_goto();
			t->append_line();
		}
	};

// return:

	template<auto... filler>
	struct T_generic_assembly_translation_action<GAAN::re_turn, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->set_kind(Context::re_turn); }
	};

// application:

	template<auto... filler>
	struct T_generic_assembly_translation_action<GAAN::application, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->set_kind(Context::apply);
			t->update_lookup();
		}
	};

// voidication:

	template<auto... filler>
	struct T_generic_assembly_translation_action<GAAN::voidication, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->set_kind(Context::apply);
			t->set_void();
			t->update_lookup();
		}
	};

// conditional:

	template<auto... filler>
	struct T_generic_assembly_translation_action<GAAN::conditional, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->set_kind(Context::test);
			t->append_entry(l, Sign::copy);
			t->update_lookup();
		}
	};

// assignment:

	template<auto... filler>
	struct T_generic_assembly_translation_action<GAAN::assignment, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->set_kind(Context::assign);
			t->update_lookup();
		}
	};

// value:

	// l(eft):

		template<auto... filler>
		struct T_generic_assembly_translation_action<GAAN::lvalue, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto k = t->match_arguments(l);
				if (k.not_end()) t->lvalue_identifier(l, k.left_size());
				else t->lvalue_unknown(l);
			}
		};

	// m(utable):

		template<auto... filler>
		struct T_generic_assembly_translation_action<GAAN::mvalue, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto k = t->match_arguments(l);
				if (k.not_end()) t->mvalue_identifier(l, k.left_size());
				else { } // error
			}
		};

	// r(ight):

		template<auto... filler>
		struct T_generic_assembly_translation_action<GAAN::rvalue, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				auto k = t->match_arguments(l);
				if (k.not_end()) t->rvalue_identifier(l, k.left_size());
				else t->rvalue_unknown(l);
			}
		};

// copy:

	template<auto... filler>
	struct T_generic_assembly_translation_action<GAAN::copy, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->append_entry(l, Sign::copy);
			t->set_copy();
		}
	};

// paste:

	template<auto... filler>
	struct T_generic_assembly_translation_action<GAAN::paste, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->append_entry(l, Sign::paste); }
	};

// quote:

	template<auto... filler>
	struct T_generic_assembly_translation_action<GAAN::quote, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ } // nothing yet.
	};

// accept:

	template<auto... filler>
	struct T_generic_assembly_translation_action<GAAN::accept, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			t->resolve_lookup();
			t->resolve_jump();
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// interface:

	template<typename AST>
	struct T_generic_assembly_ta :
		public cctmp::T_generic_translation_action<T_generic_assembly_translation_action, AST, GAAN>
			{ };

	// interface:

		template<typename AST>
		struct T_generic_assembly_action
		{
			using T_ast		= AST;

			nik_ces auto value	= T_generic_assembly_ta<AST>{};
			using type		= decltype(value);
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

