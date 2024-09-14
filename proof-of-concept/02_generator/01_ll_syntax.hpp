/************************************************************************************************************************
**
** Copyright 2022-2024 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// ll(1) syntax:

namespace generator {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	using cctmp::T_pack_Vs;
	using cctmp::member_type_U;
	using cctmp::gckey_type;
	using cctmp::gcindex_type;

	using cctmp::_two;
	using cctmp::segment_;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic syntax tree:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// action:

	using action_type		= gindex_type;
	using caction_type		= action_type const;
	nik_ce auto U_action_type	= U_store_T<action_type>;

	template<action_type, action_type, auto...> struct T_action; // no default definition.

	template<auto Kind, auto Name, auto... Vs>
	nik_ce auto U_action = U_store_T<T_action<Kind, Name, Vs...>>;

	struct ActionName
	{
		enum : action_type
		{
			nop = 0,

			dimension
		};

	}; using AN = ActionName;

/***********************************************************************************************************************/

// syntax:

	struct GenericActionKind
	{
		enum : action_type
		{
			level,
			level_0, level_1, level_2,
			dimension
		};

	}; using GAK = GenericActionKind;

	struct GenericActionName
	{
		enum : action_type
		{
			append, append_N,
			append_0, append_1, append_2,

			dimension
		};

	}; using GAN = GenericActionName;

/***********************************************************************************************************************/

// level:

	template<auto Name, auto... Vs>
	nik_ce auto U_level_action = U_action<GAK::level, Name, Vs...>;

	// append:

		// 0:

			template<auto... filler>
			struct T_action<GAK::level, GAN::append_0, filler...>
			{
				template<typename AST, typename Level>
				nik_ces void result(AST *tree, Level *level)
				{
					tree->hierarchy.append(tree->current, level->size());
					level->upsize();
				}

			}; nik_ce auto _level_append_0_action_ = U_level_action<GAN::append_0>;

		// 1:

			template<auto... filler>
			struct T_action<GAK::level, GAN::append_1, filler...>
			{
				template<typename AST, typename Level>
				nik_ces void result(AST *tree, Level *level)
				{
					-tree->current;
					cctmp::apply<_level_append_0_action_>(tree, level);
					++tree->current;
					+tree->current;
				}

			}; nik_ce auto _level_append_1_action_ = U_level_action<GAN::append_1>;

		// (N):

			template<auto... actions>
			struct T_action<GAK::level, GAN::append_N, actions...>
			{
				template<typename AST, typename... Levels>
				nik_ces void result(AST *tree, Levels*... levels)
				{
					-tree->current;
					(cctmp::apply<actions>(tree, levels), ...);
					+tree->current;
				}

			}; template<auto... actions>
				nik_ce auto _level_append_N_action_ = U_level_action<GAN::append_N, actions...>;

/***********************************************************************************************************************/

// level 0:

	template<auto Name>
	nik_ce auto U_level_0_action = U_action<GAK::level_0, Name>;

/***********************************************************************************************************************/

// level 1:

	template<auto Name>
	nik_ce auto U_level_1_action = U_action<GAK::level_1, Name>;

	// append:

		template<auto... filler>
		struct T_action<GAK::level_1, GAN::append, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *tree)
				{ cctmp::apply<_level_append_1_action_>(tree, tree->level_1); }

		}; nik_ce auto _level_1_append_action_ = U_level_1_action<GAN::append>;

/***********************************************************************************************************************/

// level 2:

	template<auto Name>
	nik_ce auto U_level_2_action = U_action<GAK::level_2, Name>;

	// append:

		template<auto... filler>
		struct T_action<GAK::level_2, GAN::append, filler...>
		{
			nik_ces auto action = _level_append_N_action_
			<
				_level_append_1_action_, _level_append_0_action_
			>;

			template<typename AST>
			nik_ces void result(AST *tree)
				{ cctmp::apply<action>(tree, tree->level_2, tree->level_1); }

		}; nik_ce auto _level_2_append_action_ = U_level_2_action<GAN::append>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic translation action:

/***********************************************************************************************************************/

// interface:

	template<template<auto...> typename TA, typename AST, typename AN>
	struct T_generic_translation_action
	{
		template<auto Name>
		nik_ces auto action	= TA<Name>::template result<AST>;
		using action_type	= void(*)(AST*, clexeme*);

		nik_ces auto segment	= segment_<AN::dimension>;

		template<auto... Is>
		nik_ces void set_entries(nik_avp(T_pack_Vs<Is...>*), action_type (&l)[AN::dimension])
			{ ((l[Is] = action<Is>), ...); }

		action_type list[AN::dimension];

		nik_ce T_generic_translation_action() : list{}

			{ set_entries(segment, list); }

		nik_ce void apply(gcindex_type pos, AST & t, clexeme & l) const
			{ list[pos](&t, &l); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser generator:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// scanner:

/***********************************************************************************************************************/

// level:

	struct Level { enum : gkey_type { symbol, body, head, action, dimension }; };

/***********************************************************************************************************************/

// interface:

	class T_parser_generator_scanner
	{
		public:

			using T_lexer		= T_parser_generator_lexer;
			using Token		= typename T_lexer::Token;

		private:

			struct Scope { enum : gkey_type { is_front, is_arrow, is_action, dimension }; };

			nik_ces gindex_type max_size	= _two; // symbol, body.

			using scope_type		= cctmp::sequence<bool, static_cast<gindex_type>(Scope::dimension)>;
			using current_type		= cctmp::sequence<gindex_type, max_size>;
			using max_type			= cctmp::sequence<gindex_type, max_size>;
			using total_type		= cctmp::sequence<gindex_type, static_cast<gindex_type>(Level::dimension)>;

			scope_type scope;
			current_type current;

		public:

			max_type max;
			total_type total;

			nik_ce T_parser_generator_scanner(lexeme l)
			{
				scope.fullsize();
				current.fullsize();
				max.fullsize();
				total.fullsize();

				update_semicolon();

				while (l.not_empty())
				{
					T_lexer::lex(l.retract());

					switch (l.token)
					{
						case Token::identifier : { update_identifier (); break; }
						case Token::semicolon  : { update_semicolon  (); break; }
						case Token::arrow      : { update_arrow      (); break; }
						case Token::colon      : { update_colon      (); break; }
						case Token::empty      : { update_empty      (); break; }
					}
				}

				update_body_max();
			}

		private:

			nik_ce void update_semicolon()
			{
				update_symbol_max();
				scope[Scope::is_front] = true;
				scope[Scope::is_arrow] = false;
				scope[Scope::is_action] = false;
			}

			nik_ce void update_colon()
			{
				scope[Scope::is_arrow] = false;
				scope[Scope::is_action] = true;
			}

			nik_ce void update_arrow()
			{
				++current[Level::body];
				++total  [Level::body];

				scope[Scope::is_front] = false;
				scope[Scope::is_arrow] = true;
			}

			nik_ce void update_identifier()
			{
				if (scope[Scope::is_front])
				{
					update_body_max();
					++total[Level::head];
				}
				else if (scope[Scope::is_arrow])
				{
					++current[Level::symbol];
					++total[Level::symbol];
				}
				else if (scope[Scope::is_action]) ++total[Level::action];
			}

			nik_ce void update_empty()
			{
				if (scope[Scope::is_arrow])
				{
					++current[Level::symbol];
					++total[Level::symbol];
				}
			}

			nik_ce void update_max(gckey_type level)
			{
				if (current[level] > max[level]) max[level] = current[level];
				current[level] = _zero;
			}

			nik_ce void update_symbol_max () { update_max(Level::symbol); }
			nik_ce void update_body_max   () { update_max(Level::body); }
	};

/***********************************************************************************************************************/

// interface:

	template<auto static_source>
	struct T_parser_generator_scanned
	{
		nik_ces auto & src_pair		= member_value_U<static_source>;
		nik_ces auto & start_str	= src_pair.v0;
		nik_ces auto & src		= src_pair.v1;
		nik_ces auto value		= T_parser_generator_scanner{src.cselect()};
		using type			= decltype(value);

		using Token			= typename type::Token;
		nik_ces auto invalid_token	= Token::invalid;
		nik_ces auto prompt_token	= Token::prompt;

	}; template<auto static_source>
		nik_ce auto _parser_generator_scanned_ = U_store_T<T_parser_generator_scanned<static_source>>;

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
				produce , alias ,
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
				terminal , nonterminal ,
				dimension
			};

			nik_ces bool is_terminal    (csign_type s) { return (s == Sign::terminal); }
			nik_ces bool is_nonterminal (csign_type s) { return (s == Sign::nonterminal); }
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// icon:

/***********************************************************************************************************************/

	template<typename Type, typename SizeType = gindex_type>
	class T_icon : public cselector<Type, SizeType>
	{
		protected:

			using base		= cselector<Type, SizeType>;

		public:

			using type		= typename base::type;
			using type_ptr		= typename base::type_ptr;
			using type_ref		= typename base::type_ref;
			using type_cptr		= typename base::type_cptr;

			using ctype		= typename base::ctype;
			using ctype_ptr		= typename base::ctype_ptr;
			using ctype_cptr	= typename base::ctype_cptr;
			using ctype_ref		= typename base::ctype_ref;

			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

		public:

			nik_ce T_icon() : base{} { }
			nik_ce T_icon(ctype_cptr s, ctype_cptr f) : base{s, f} { }

			nik_ce bool operator == (const T_icon<Type, SizeType> & i) const
				{ return cctmp::apply<cctmp::_subarray_same_<>>(*this, i); }

			nik_ce bool operator != (const T_icon<Type, SizeType> & i) const
				{ return !cctmp::apply<cctmp::_subarray_same_<>>(*this, i); }

				// deprecate in the long run.
			nik_ce void copy(const T_lexeme<Type> *l)
			{
				base::start  = l->cbegin();
				base::finish = l->ccurrent();
			}

			nik_ce void copy(const cselector<Type, SizeType> & s)
			{
				base::start  = s.cbegin();
				base::finish = s.cend();
			}

			nik_ce T_icon & find(ctype_ref v)
				{ base::start = cctmp::apply<base::_find_>(base::start, base::finish, v); return *this; }

			template<typename T>
			nik_ce T_icon & find(const T & v)
				{ base::start = cctmp::apply<base::_find_same_>(base::start, base::finish, v); return *this; }

			nik_ce auto contains(ctype_ref v) const { T_icon i{*this}; return i.find(v); }

			template<typename T>
			nik_ce auto contains(const T & v) const
				{ T_icon i{*this}; return i.template find<T const&>(v); }

				// deprecate in the long run.
			nik_ce bool same(const T_lexeme<Type> *l) const
				{ return cctmp::apply<cctmp::_subarray_same_<>>(*this, l->left_cselect()); }

			nik_ce bool same(const cselector<Type, SizeType> & s) const
				{ return cctmp::apply<cctmp::_subarray_same_<>>(*this, s); }

			nik_ce bool same(const T_icon<Type, SizeType> & i) const
				{ return cctmp::apply<cctmp::_subarray_same_<>>(*this, i); }
	};

	using icon  = T_icon<gchar_type>;
	using cicon = icon const;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// levels:

/***********************************************************************************************************************/

// symbol:

	template<typename CharType>
	struct T_level_symbol : public T_icon<CharType>
	{
		using base	= T_icon<CharType>;
		using cbase	= base const;

		sign_type sign;
		gindex_type index;

		nik_ce T_level_symbol() : base{}, sign{}, index{} { }

		nik_ce bool is_terminal() const { return Sign::is_terminal(sign); }
		nik_ce bool is_nonterminal() const { return Sign::is_nonterminal(sign); }
	};

	using level_symbol	= T_level_symbol<gchar_type>;
	using level_csymbol	= level_symbol const;

/***********************************************************************************************************************/

// body:

	struct level_body
	{
		bool is_empty;
		gindex_type action;

		nik_ce level_body() : is_empty{}, action{AN::nop} { }
	};

/***********************************************************************************************************************/

// head:

	struct level_head
	{
		bool has_empty;
		gindex_type index;

		nik_ce level_head() : has_empty{}, index{} { }
		nik_ce level_head(gcindex_type i) : has_empty{}, index{i} { }
	};

/***********************************************************************************************************************/

// interface (tree):

	template<auto static_scanned, auto static_grammar>
	struct T_parser_generator_ast
	{
		using scanned_type			= member_type_U<static_scanned>;
		using T_lexer				= T_parser_generator_lexer;
		using Token				= typename T_lexer::Token;
		using T_grammar				= T_store_U<static_grammar>;
		using ActName				= typename T_grammar::ActName;

		nik_ces auto & scanned			= member_value_U<static_scanned>;
		nik_ces auto & start_str		= T_store_U<static_scanned>::start_str;
		nik_ces auto invalid_token		= T_store_U<static_scanned>::invalid_token;
		nik_ces auto prompt_token		= T_store_U<static_scanned>::prompt_token;

		nik_ces auto grammar_size		= T_grammar::size;
		nik_ces auto & grammar_map		= T_grammar::map;
		nik_ces auto & grammar_action		= T_grammar::action;

		nik_ces gindex_type symbol_total	= scanned.total[Level::symbol];
		nik_ces gindex_type body_total		= scanned.total[Level::body];
		nik_ces gindex_type head_total		= scanned.total[Level::head];
		nik_ces gindex_type action_total	= scanned.total[Level::action];
		nik_ces gindex_type action_length	= ActName::dimension;

		nik_ces gindex_type symbol_max		= scanned.max[Level::symbol];
		nik_ces gindex_type body_max		= scanned.max[Level::body];
		nik_ces gindex_type head_max		= head_total;

		nik_ces gindex_type level_3_size	= head_max + 3;
		nik_ces gindex_type level_2_size	= head_total * (body_max + 3);
		nik_ces gindex_type level_1_size	= body_total * (symbol_max + 3);
		nik_ces gindex_type level_0_size	= symbol_total * 3;

		nik_ces gindex_type hierarchy_length	= level_0_size + level_1_size + level_2_size + level_3_size;

		using hierarchy_type			= T_hierarchy<gindex_type{4}, hierarchy_length>;
		using cnavigator_type			= typename hierarchy_type::cnavigator_type;
		using navigator_type			= typename hierarchy_type::navigator_type;

		using level_head_type			= cctmp::sequence < level_head   , head_total    >;
		using level_body_type			= cctmp::sequence < level_body   , body_total    >;
		using level_symbol_type			= cctmp::sequence < level_symbol , symbol_total  >;
		using level_action_type			= cctmp::sequence < level_symbol , action_length >;

		using level_head_ptr			= level_head_type*;
		using level_body_ptr			= level_body_type*;
		using level_symbol_ptr			= level_symbol_type*;
		using level_action_ptr			= level_action_type*;

		hierarchy_type hierarchy;
		navigator_type current;
		level_head_type head_level;
		level_body_type body_level;
		level_symbol_type symbol_level;
		level_action_type action_level;

		level_head_ptr level_2;
		level_body_ptr level_1;
		level_symbol_ptr level_0;

		lexeme lexed;
		gindex_type term_size;
		gindex_type empty_size;
		gindex_type nonterm_index;

		nik_ce T_parser_generator_ast() :

			hierarchy{head_max, body_max, symbol_max, static_cast<gindex_type>(0)},
			current{hierarchy.origin()},
			level_0{&symbol_level}, level_1{&body_level}, level_2{&head_level},
			term_size{}, empty_size{}, nonterm_index{}

			{ action_level.upsize(AN::dimension); }

		// symbol:

		nik_ce auto head_size   () const { return head_level.size(); }
		nik_ce auto body_size   () const { return body_level.size(); }
		nik_ce auto symbol_size () const { return symbol_level.size(); }
		nik_ce auto action_size () const { return action_level.size(); }

		nik_ce const auto & head_at   (const cguider & g) const { return head_level   [~g]; }
		nik_ce const auto & body_at   (const cguider & g) const { return body_level   [~g]; }
		nik_ce const auto & symbol_at (const cguider & g) const { return symbol_level [~g]; }
		nik_ce const auto & action_at (const cguider & g) const { return action_level [~g]; }

		nik_ce const auto & head_at   (const cnavigator_type & n) const { return head_level   [~n]; }
		nik_ce const auto & body_at   (const cnavigator_type & n) const { return body_level   [~n]; }
		nik_ce const auto & symbol_at (const cnavigator_type & n) const { return symbol_level [~n]; }
		nik_ce const auto & action_at (const cnavigator_type & n) const { return action_level [~n]; }

		nik_ce void increment_empty    () { ++empty_size; }
		nik_ce void set_body_is_empty  () { body_level.last()->is_empty = true; }
		nik_ce void set_head_has_empty () { head_level.last()->has_empty = true; }

		nik_ce void new_head() { cctmp::apply<_level_append_0_action_>(this, level_2); }
		nik_ce void new_body() { cctmp::apply<_level_append_0_action_>(this, level_1); }

		nik_ce void push_nonterminal()
		{
			auto k   = unite_symbol(&lexed);
			k->sign  = Sign::nonterminal;
			k->index = head_level.size() - 1;

			head_level.last()->index = k.left_size();
		}

		nik_ce void append_front()
		{
			new_head();
			+current;

			new_body();
			+current;

			push_nonterminal();
		}

		nik_ce void append_body() { cctmp::apply<_level_1_append_action_>(this); }
		nik_ce void append_head()
		{
			cctmp::apply<_level_2_append_action_>(this);
			push_nonterminal();
		}

		nik_ce void push_symbol(clexeme *l)
		{
			symbol_level.end()->copy(l);
			symbol_level.end()->sign = Sign::terminal; // default.
			symbol_level.upsize();
		}

		nik_ce auto unite_symbol(clexeme *l)
		{
			auto c = symbol_level.iterate().find(l->left_cselect());

			if (c.is_end()) push_symbol(l);

			return c;
		}

		nik_ce void append_symbol(clexeme *l)
		{
			auto k = unite_symbol(l);
			hierarchy.append(current, k.left_size());
		}

		nik_ce void push_action(clexeme *l)
		{
			action_level.end()->copy(l);
			action_level.upsize();
		}

		nik_ce auto unite_action(clexeme *l)
		{
			auto c = (action_level.iterate() += AN::dimension);

			if (c.find(l->left_cselect()).is_end()) push_action(l);

			return c;
		}

		nik_ce void assign_action(action_type act)
		{
			auto & body = body_level[~current];
			body.action = act;
		}

		nik_ce void append_action(clexeme *l) // doesn't account for <accept>.
		{
			auto k = unite_action(l);

			action_type act = grammar_action.slookup(*k, AN::nop);

			assign_action(act);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// translation action:

	template<action_type, auto...> struct T_parser_generator_translation_action;

/***********************************************************************************************************************/

// name:

	struct ParserGeneratorActionName
	{
		enum : action_type
		{
			nop = AN::nop,

			l_value , r_value , m_value , a_value ,
			front   , head    , body    , accept  ,

			dimension
		};

	}; using PGAN = ParserGeneratorActionName;

/***********************************************************************************************************************/

// nop:

	template<auto... filler>
	struct T_parser_generator_translation_action<PGAN::nop, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l) { }
	};

// value:

	// l(eft):

		template<auto... filler>
		struct T_parser_generator_translation_action<PGAN::l_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->lexed = *l; }
		};

	// r(ight):

		template<auto... filler>
		struct T_parser_generator_translation_action<PGAN::r_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->append_symbol(l); }
		};

	// (e)m(pty):

		template<auto... filler>
		struct T_parser_generator_translation_action<PGAN::m_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
			{
				t->increment_empty();
				t->set_body_is_empty();
				t->set_head_has_empty();
				t->append_symbol(l);
			}
		};

	// a(ction):

		template<auto... filler>
		struct T_parser_generator_translation_action<PGAN::a_value, filler...>
		{
			template<typename AST>
			nik_ces void result(AST *t, clexeme *l)
				{ t->append_action(l); }
		};

// front:

	template<auto... filler>
	struct T_parser_generator_translation_action<PGAN::front, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->append_front(); }
	};

// head:

	template<auto... filler>
	struct T_parser_generator_translation_action<PGAN::head, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->append_head(); }
	};

// body:

	template<auto... filler>
	struct T_parser_generator_translation_action<PGAN::body, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
			{ t->append_body(); }
	};

// accept:

	template<auto... filler>
	struct T_parser_generator_translation_action<PGAN::accept, filler...>
	{
		template<typename AST>
		nik_ces void result(AST *t, clexeme *l)
		{
			for (auto k = t->symbol_level.begin(); k != t->symbol_level.end(); ++k)
				if (k->is_terminal())
					k->index = t->grammar_map.slookup(*k, t->invalid_token);

			t->term_size = t->symbol_size() - t->head_size();
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// interface:

/***********************************************************************************************************************/

	template<typename AST>
	struct T_parser_generator_ta :
		public T_generic_translation_action<T_parser_generator_translation_action, AST, PGAN>
			{ };

	// interface:

		template<typename AST>
		struct T_parser_generator_action
		{
			using T_ast		= AST;

			nik_ces auto value	= T_parser_generator_ta<AST>{};
			using type		= decltype(value);
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace generator

