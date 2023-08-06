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

	template<auto U>
	using member_type_U					= cctmp::member_type_U<U>;

	nik_ce auto _level_append_0_action_			= cctmp::_level_append_0_action_;
	nik_ce auto _level_1_append_action_			= cctmp::_level_1_append_action_;

	using cstrlit_ref					= cctmp::cstrlit_ref;

	using cguider						= cctmp::cguider;

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
				assign , apply , vo_id , test , re_turn , label , branch , go_to ,
				dimension
			};

			nik_ces bool is_assign (context_type c) { return (c == assign  ); }
			nik_ces bool is_apply  (context_type c) { return (c == apply   ); }
			nik_ces bool is_test   (context_type c) { return (c == test    ); }
			nik_ces bool is_void   (context_type c) { return (c == vo_id   ); }
			nik_ces bool is_return (context_type c) { return (c == re_turn ); }
			nik_ces bool is_label  (context_type c) { return (c == label   ); }
			nik_ces bool is_branch (context_type c) { return (c == branch  ); }
			nik_ces bool is_goto   (context_type c) { return (c == go_to   ); }
		};

	// sign:

		using sign_type  = gkey_type;
		using csign_type = sign_type const;

		struct Sign // tokens are syntactic, signs are semantic.
		{
			enum : sign_type
			{
				na = 0,
				label, jump, recurse,
				env, constant_arg, mutable_arg, static_arg,
				copy, paste, morph, cycle,
				dimension
			};

			nik_ces bool is_label        (sign_type s) { return (s == label        ); }
			nik_ces bool is_jump         (sign_type s) { return (s == jump         ); }
			nik_ces bool is_recurse      (sign_type s) { return (s == recurse      ); }
			nik_ces bool is_env          (sign_type s) { return (s == env          ); }
			nik_ces bool is_constant_arg (sign_type s) { return (s == constant_arg ); }
			nik_ces bool is_mutable_arg  (sign_type s) { return (s == mutable_arg  ); }
			nik_ces bool is_static_arg   (sign_type s) { return (s == static_arg   ); }
			nik_ces bool is_copy         (sign_type s) { return (s == copy         ); }
			nik_ces bool is_paste        (sign_type s) { return (s == paste        ); }
			nik_ces bool is_morph        (sign_type s) { return (s == morph        ); }
			nik_ces bool is_cycle        (sign_type s) { return (s == cycle        ); }
		};

	// link:

		struct Link
		{
			enum : gindex_type
			{
				none = 0,
				tree, morph, cycle_param, cycle_iter,
				dimension
			};

			nik_ces bool is_tree        (sign_type s) { return (s == tree       ); }
			nik_ces bool is_morph       (sign_type s) { return (s == morph      ); }
			nik_ces bool is_cycle_param (sign_type s) { return (s == cycle_param); }
			nik_ces bool is_cycle_iter  (sign_type s) { return (s == cycle_iter ); }
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// levels:

/***********************************************************************************************************************/

// line:

	struct level_line
	{
		context_type kind;

		bool has_paste;
		bool has_link;

		nik_ce level_line() :

			kind{Context::none},
			has_paste{}, has_link{} { }
	};

/***********************************************************************************************************************/

// entry:

	template<typename CharType>
	struct T_level_entry : public cctmp::T_icon<CharType>
	{
		using base = cctmp::T_icon<CharType>;

		sign_type sign;
		gindex_type index;

		nik_ce T_level_entry() : sign{}, index{} { }
		nik_ce T_level_entry(cstrlit_ref s) : base{s.cbegin(), s.cend()}, sign{}, index{} { }
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

// link:

	template<typename Type, auto Size>
	class T_level_link : public cctmp::sequence<Type, Size>
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
			nik_ce void update_shift() { offset = (!is_void() && !is_return()); }

		public:

			nik_ce T_level_link() : position{}, difference{}, offset{}, line{} { }

			nik_ce void initialize(const cguider & g, const level_line & l)
			{
				position = g.pos();
				line     = &l;
			}

			nik_ce gindex_type size() const { return difference; }

			nik_ce void update(ctype_cptr origin)
			{
				cguider line_iter{origin, position};

				update_shift();
				update_size(line_iter.size());

				for (line_iter += offset; line_iter.not_end(); ++line_iter)
					base::push(~line_iter.next());
			}

		// line:

			nik_ce bool is_assign () const { return Context::is_assign (line->kind); }
			nik_ce bool is_return () const { return Context::is_return (line->kind); }
			nik_ce bool is_apply  () const { return Context::is_apply  (line->kind); }
			nik_ce bool is_void   () const { return Context::is_void   (line->kind); }
			nik_ce bool is_test   () const { return Context::is_test   (line->kind); }
	};

	template<auto Size>
	using level_link = T_level_link<gindex_type, Size>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// morph:

/***********************************************************************************************************************/

// names:

	struct Morph
	{
		// unary:

			nik_ces auto id    = strlit_type("id");
			nik_ces auto deref = strlit_type("dereference");
			nik_ces auto inc   = strlit_type("increment");
			nik_ces auto dec   = strlit_type("decrement");

		// binary:

			nik_ces auto appoint   = strlit_type("appoint");
			nik_ces auto not_equal = strlit_type("not_equal");
	};

/***********************************************************************************************************************/

// level:

	template<typename CharType, gindex_type Size>
	struct T_level_morph
	{
		using parameter_type = cctmp::sequence<level_entry, Size>;

		token_type token;
		parameter_type parameter;

		nik_ce T_level_morph() : token{} { }

	// token:

		nik_ce void set_token(ctoken_type t) { token = t; }

	// param:

		nik_ce void append(clexeme *l, csign_type s, gindex_type i = 0)
		{
			parameter.end()->copy(l);
			parameter.end()->sign = s;
			parameter.end()->index = i;
			parameter.upsize();
		}

		nik_ce void append(cstrlit_ref l, csign_type s, gindex_type i = 0)
		{
			parameter.push(l);
			parameter.last()->sign = s;
			parameter.last()->index = i;
		}
	};

	template<auto Size>
	using level_morph = T_level_morph<gchar_type, Size>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cycle:

/***********************************************************************************************************************/

// iterator:

	template<typename CharType>
	struct T_level_iterator : public T_level_entry<CharType>
	{
		using base = T_level_entry<CharType>;

		bool is_none;
		bool is_void;

		nik_ce T_level_iterator() : base{}, is_none{}, is_void{} { }
		nik_ce T_level_iterator(cstrlit_ref s) : base{s}, is_none{}, is_void{} { }
	};

	using level_iterator = T_level_iterator<gchar_type>;

/***********************************************************************************************************************/

// interval:

	struct level_ival
	{
		enum : gkey_type { na, closed, open, dimension };

		bool is_lead;
		bool is_fixed;
		gkey_type left;
		gkey_type right;

		nik_ce level_ival() : is_lead{}, is_fixed{}, left{}, right{} { }

		nik_ce bool is_left_closed  () const { return (left  == closed); }
		nik_ce bool is_left_open    () const { return (left  == open); }
		nik_ce bool is_right_closed () const { return (right == closed); }
		nik_ce bool is_right_open   () const { return (right == open); }
	};

	using Ival = level_ival;

/***********************************************************************************************************************/

// level:

	template<typename CharType, gindex_type CycleSize>
	class T_level_cycle
	{
		nik_ces auto Size	= CycleSize + 1;

		using level_iter	= T_level_iterator<CharType>;

		using action_entry	= cctmp::sequence < level_entry , Size >;
		using param_entry	= cctmp::sequence < level_entry , 3    >;
		using iter_entry	= cctmp::sequence < level_iter  , 2    >;

		using parameter_type	= cctmp::sequence < param_entry , 3    >;
		using interval_type	= cctmp::sequence < level_ival  , Size >;
		using iterator_type	= cctmp::sequence < iter_entry  , Size >;

		public:

		token_type token;
		action_entry action;
		parameter_type parameter;
		interval_type interval;
		iterator_type iterator;
		iter_entry tonic_iter;

			nik_ce T_level_cycle() : token{} { }

		// token:

			nik_ce void set_token(ctoken_type t) { token = t; }

		protected:

		// append:

			template<typename Seq>
			nik_ce void append(Seq *seq, clexeme *l, csign_type s, gindex_type i = 0)
			{
				seq->end()->copy(l);
				seq->end()->sign = s;
				seq->end()->index = i;
				seq->upsize();
			}

			template<typename Seq>
			nik_ce void append(Seq *seq, cstrlit_ref l, csign_type s, gindex_type i = 0)
			{
				seq->push(l);
				seq->last()->sign = s;
				seq->last()->index = i;
			}

		public:

		// action:

			nik_ce void action_append(clexeme *l, csign_type s, gindex_type i = 0)
				{ append(&action, l, s, i); }

			nik_ce void action_append(cstrlit_ref l, csign_type s, gindex_type i = 0)
				{ append(&action, l, s, i); }

		// param:

			nik_ce void param_upsize() { parameter.upsize(); }

			nik_ce void param_append(clexeme *l, csign_type s, gindex_type i = 0)
				{ append(parameter.last(), l, s, i); }

			nik_ce void param_append(cstrlit_ref l, csign_type s, gindex_type i = 0)
				{ append(parameter.last(), l, s, i); }

		// iter:

			nik_ce void iter_upsize() { iterator.upsize(); }

			nik_ce void set_none() { iterator.last()->last()->is_none = true; }
			nik_ce void set_void() { iterator.last()->last()->is_void = true; }

			nik_ce void iter_append(clexeme *l, csign_type s, gindex_type i = 0)
				{ append(iterator.last(), l, s, i); }

			nik_ce void iter_append(cstrlit_ref l, csign_type s, gindex_type i = 0)
				{ append(iterator.last(), l, s, i); }

			nik_ce bool is_reversible(gindex_type pos) const { return (iterator[pos].size() == 2); }

		// tonic:

			nik_ce void tonic_append(clexeme *l, csign_type s, gindex_type i = 0)
				{ append(&tonic_iter, l, s, i); }

			nik_ce void tonic_append(cstrlit_ref l, csign_type s, gindex_type i = 0)
				{ append(&tonic_iter, l, s, i); }

			nik_ce void tonic_set_none() { tonic_iter.last()->is_none = true; }
			nik_ce void tonic_set_void() { tonic_iter.last()->is_void = true; }

			nik_ce bool tonic_is_reversible() const { return (tonic_iter.size() == 2); }

		// ival:

			nik_ce void set_fixed() { interval.end()->is_fixed = true; interval.upsize(); }
			nik_ce void set_left(gckey_type i) { interval.end()->left = i; }
			nik_ce void set_right(gckey_type i) { interval.end()->right = i; interval.upsize(); }
			nik_ce void set_lead() { interval.end()->is_lead = true; }
	};

	template<auto Size>
	using level_cycle = T_level_cycle<gchar_type, Size>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tree (table of contents):

/***********************************************************************************************************************/

// interface:

	template<auto static_scanned>
	struct T_chord_assembly_ast
	{
		using T_lexer			= T_chord_assembly_lexer;
		using Token			= typename T_lexer::Token;
		using scanned_type		= member_type_U<static_scanned>;
		using Total			= typename scanned_type::Total;
		using Cap			= typename scanned_type::Cap;

		nik_ces auto & scanned		= member_value_U<static_scanned>;
		nik_ces auto padding		= scanned.total[Total::pad];

		using hierarchy_type		= cctmp::T_hierarchy<gindex_type{3}, scanned.hierarchy_size>;
		using cnavigator_type		= typename hierarchy_type::cnavigator_type;
		using navigator_type		= typename hierarchy_type::navigator_type;

		using level_link_type		= level_link  < scanned.capacity[Cap::tree]  >;
		using level_morph_type		= level_morph < scanned.capacity[Cap::morph] >;
		using level_cycle_type		= level_cycle < scanned.capacity[Cap::cycle] >;

		using level_line_seq		= cctmp::sequence < level_line       , scanned.total[Total::line ] >;
		using level_entry_seq		= cctmp::sequence < level_entry      , scanned.total[Total::tree ] >;
		using level_link_seq		= cctmp::sequence < level_link_type  , scanned.total[Total::line ] >;
		using level_morph_seq		= cctmp::sequence < level_morph_type , scanned.total[Total::morph] >;
		using level_cycle_seq		= cctmp::sequence < level_cycle_type , scanned.total[Total::cycle] >;
		using level_arg_seq		= cctmp::sequence < level_arg        , scanned.arg_size            >;
		using level_tag_seq		= cctmp::sequence < level_tag        , scanned.tag_size            >;

		using label_seq			= cctmp::subsequence < level_tag , scanned.total[Total::label] >;
		using jump_seq			= cctmp::subsequence < level_tag , scanned.total[Total::jump ] >;

		hierarchy_type hierarchy;
		navigator_type current;
		level_line_seq line_level;
		level_entry_seq entry_level;
		level_link_seq link_level;
		level_tag_seq tag_level;
		level_arg_seq arg_level;
		level_morph_seq morph_level;
		level_cycle_seq cycle_level;

		level_line_seq *level_1;
		level_entry_seq *level_0;

		label_seq label;
		jump_seq jump;

		level_arg name;
		lexeme lexed;
		bool has_local_copy;

		nik_ce T_chord_assembly_ast() :

			hierarchy{scanned.total[Total::line], scanned.capacity[Cap::tree], gindex_type{0}},
			current{hierarchy.origin()},
			level_0{&entry_level},
			level_1{&line_level},
			has_local_copy{} { }

		// local:

			nik_ce auto line_size   () const { return line_level.size()   ; }
			nik_ce auto entry_size  () const { return entry_level.size()  ; }
			nik_ce auto arg_size    () const { return arg_level.size()    ; }

			nik_ce auto has_copy   () const { return has_local_copy; }

			nik_ce void set_copy   () { has_local_copy = true  ; }
			nik_ce void unset_copy () { has_local_copy = false ; }

			nik_ce void update_copy_paste()
				{ if (has_local_copy) { set_paste(); unset_copy(); } }

			nik_ce const auto & line_at  (const cguider & g) const { return line_level  [~g]; }
			nik_ce const auto & entry_at (const cguider & g) const { return entry_level [~g]; }

		// line:

			nik_ce void first_line()
			{
				cctmp::apply<_level_append_0_action_>(this, level_1);
				+current;
			}

			nik_ce void append_line() { cctmp::apply<_level_1_append_action_>(this); }

			nik_ce auto kind      (const cguider & g) const { return line_at(g).kind; }
			nik_ce auto has_void  (const cguider & g) const { return (kind(g) == Context::vo_id); }
			nik_ce auto has_paste (const cguider & g) const { return line_at(g).has_paste; }
			nik_ce auto has_link  (const cguider & g) const { return line_at(g).has_link; }

			nik_ce void set_kind(ccontext_type k) { line_level.last()->kind = k; }

			nik_ce void set_void  () { line_level.last()->kind      = Context::vo_id; }
			nik_ce void set_paste () { line_level.last()->has_paste = true; }
			nik_ce void set_link  () { line_level.last()->has_link  = true; }

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

		// link:

			nik_ce const auto & link_entry(gcindex_type n, gcindex_type m) const
				{ return entry_level[link_level[n][m]]; }

			nik_ce auto link_entry_sign(gcindex_type n, gcindex_type m) const
				{ return link_entry(n, m).sign; }

			nik_ce auto link_entry_index(gcindex_type n, gcindex_type m) const
				{ return link_entry(n, m).index; }

			nik_ce void update_link()
				{ if (!line_level.last()->has_link) { set_link(); push_link(); } }

			nik_ce void push_link()
			{
				auto g = current.cguide();
				link_level.end()->initialize(g, line_at(g));
				link_level.upsize();
			}

			nik_ce void resolve_link()
			{
				for (auto k = link_level.begin(); k != link_level.end(); ++k)
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
				{ append_entry(l, Sign::constant_arg, index); }

			nik_ce void lvalue_variable(clexeme *l)
			{
				append_entry(l, Sign::constant_arg, arg_size());
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

			nik_ce void _value_unknown(clexeme *l)
			{
				auto j = match_name(l);
				auto s = j ? Sign::recurse : Sign::env;

				append_entry(l, s);
				update_link();
			}

		// mvalue:

			nik_ce void mvalue_identifier(clexeme *l, gcindex_type index)
				{ _value_identifier(l, Sign::mutable_arg, index); }

		// rvalue:

			nik_ce void rvalue_identifier(clexeme *l, gcindex_type index)
				{ _value_identifier(l, Sign::constant_arg, index); }

			nik_ce void rvalue_unknown(clexeme *l)
				{ _value_unknown(l); }

		// svalue:

			nik_ce void svalue_identifier(clexeme *l, gcindex_type index)
				{ _value_identifier(l, Sign::static_arg, index); }

			nik_ce void svalue_unknown(clexeme *l)
				{ _value_unknown(l); }

		// morph:

			nik_ce void set_morph(clexeme *l)
			{
				append_entry(l, Sign::morph, morph_level.size());
				morph_level.end()->set_token(l->token);
				morph_level.upsize();
			}

			nik_ce void morph_identifier(clexeme *l, gindex_type index)
				{ morph_level.last()->append(l, Sign::static_arg, index); }

			nik_ce void morph_unknown(clexeme *l) // Sign::recurse ?
				{ morph_level.last()->append(l, Sign::env, Link::morph); }

			nik_ce void morph_known(cstrlit_ref s)
				{ morph_level.last()->append(s, Sign::env, Link::morph); }

		// cycle:

			nik_ce void set_cycle(clexeme *l)
			{
				append_entry(l, Sign::cycle, cycle_level.size());
				cycle_level.end()->set_token(l->token);
				cycle_level.upsize();
			}

			// action:

			nik_ce void cycle_action_identifier(clexeme *l, gindex_type index)
				{ cycle_level.last()->action_append(l, Sign::static_arg, index); }

			nik_ce void cycle_action_unknown(clexeme *l)
				{ cycle_level.last()->action_append(l, Sign::env, Link::cycle_param); }

			nik_ce void cycle_action_known(cstrlit_ref s)
				{ cycle_level.last()->action_append(s, Sign::env, Link::cycle_param); }

			// param:

			nik_ce void cycle_param_identifier(clexeme *l, gindex_type index)
				{ cycle_level.last()->param_append(l, Sign::static_arg, index); }

			nik_ce void cycle_param_unknown(clexeme *l)
				{ cycle_level.last()->param_append(l, Sign::env, Link::cycle_param); }

			nik_ce void cycle_param_known(cstrlit_ref s)
				{ cycle_level.last()->param_append(s, Sign::env, Link::cycle_param); }

			// iter:

			nik_ce void cycle_iter_identifier(clexeme *l, gindex_type index)
				{ cycle_level.last()->iter_append(l, Sign::static_arg, index); }

			nik_ce void cycle_iter_unknown(clexeme *l)
				{ cycle_level.last()->iter_append(l, Sign::env, Link::cycle_iter); }

			nik_ce void cycle_iter_known(cstrlit_ref s)
				{ cycle_level.last()->iter_append(s, Sign::env, Link::cycle_iter); }

			// tonic:

			nik_ce void cycle_tonic_identifier(clexeme *l, gindex_type index)
				{ cycle_level.last()->tonic_append(l, Sign::static_arg, index); }

			nik_ce void cycle_tonic_unknown(clexeme *l)
				{ cycle_level.last()->tonic_append(l, Sign::env, Link::cycle_iter); }

			nik_ce void cycle_tonic_known(cstrlit_ref s)
				{ cycle_level.last()->tonic_append(s, Sign::env, Link::cycle_iter); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

