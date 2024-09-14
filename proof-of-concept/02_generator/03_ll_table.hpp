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

// ll(1) table:

namespace generator {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	using cctmp::_subarray_same_;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser generator:

/***********************************************************************************************************************/

// sifter:

	template<typename Type, auto Size>
	class T_sifter
	{
		private:

			using type			= Type;
			using type_ptr			= type*;
			using sequence_type		= sequence<type_ptr, Size>;

			bool is_0;
			sequence_type sequence_0;
			sequence_type sequence_1;

		public:

			nik_ce T_sifter() : is_0{} { }

		protected:

			nik_ce auto & current()
			{
				if (is_0) return sequence_0;
				else      return sequence_1;
			}

		public:

			nik_ce bool not_empty () { return current().not_empty(); }
			nik_ce void clear     () { current().clear(); }
			nik_ce void toggle    () { is_0 = not is_0; }
			nik_ce auto iterate   () { return current().iterate(); }

			nik_ce void push(type_ptr ptr) { current().push(ptr); }

			nik_ce auto reset()
			{
				auto i = iterate();

				toggle();
				clear();

				return i;
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// first:

	template<auto> struct T_body_first;
	template<auto> struct T_head_first;

/***********************************************************************************************************************/

// definition:

	template<auto static_parsed>
	struct T_first_definition
	{
		nik_ces auto & parsed		= member_value_U<static_parsed>;

		using head_first_type		= T_head_first<static_parsed>;
		using head_first_ptr		= head_first_type*;
		using head_first_seq		= sequence<head_first_type, parsed.head_size()>;

		using body_first_type		= T_body_first<static_parsed>;
		using body_first_seq		= sequence<body_first_type, parsed.body_size()>;

		using terminal_type		= sequence<gindex_type, parsed.term_size>;

		using sifter_type		= T_sifter<body_first_type, parsed.body_size()>;
		using sifter_ptr		= sifter_type*;
	};

/***********************************************************************************************************************/

// locus:

	template<auto static_parsed>
	struct T_first_locus
	{
		nik_ces auto & parsed		= member_value_U<static_parsed>;

		using definition		= T_first_definition<static_parsed>;
		using head_first_ptr		= typename definition::head_first_ptr;
		using sifter_ptr		= typename definition::sifter_ptr;

		bool is_empty;
		action_type action;
		head_first_ptr global;
		head_first_ptr local;
		cguider pivot;
		cguider current;
		sifter_ptr sifter;

		nik_ce T_first_locus() : is_empty{}, action{}, global{}, local{}, sifter{} { }

		nik_ce void set_global  (head_first_ptr    p) { global  = p; }
		nik_ce void set_local   (head_first_ptr    p) { local   = p; }
		nik_ce void set_pivot   (cguider_ctype_ref g) { pivot   = g; }
		nik_ce void set_current (cguider_ctype_ref g) { current = g; }
		nik_ce void set_sifter  (sifter_ptr        s) { sifter  = s; }

		nik_ce const auto & current_symbol () const { return parsed.symbol_at(current.next()); }
		nik_ce const auto & current_body   () const { return parsed.body_at(current); }
		nik_ce const auto current_index    () const { return current_symbol().index; }

		nik_ce auto & current_first () { return global[current_index()]; }

		nik_ce auto & local_terminal   () { return local->terminal; }
		nik_ce auto & current_terminal () { return current_first().terminal; }

		nik_ce const auto local_index () const { return local - global; }
	};

/***********************************************************************************************************************/

// body:

	template<auto static_parsed>
	struct T_body_first
	{
		using locus_type		= T_first_locus<static_parsed>;
		using definition		= typename locus_type::definition;
		using terminal_type		= typename definition::terminal_type;

		locus_type locus;
		terminal_type terminal;

		nik_ce T_body_first() { }

		nik_ce void initialize()
		{
			auto & current_symbol = locus.current_symbol();

			if (current_symbol.is_nonterminal()) locus.sifter->push(this);
			else terminal_initialize();
		}

		nik_ce void terminal_initialize()
		{
			auto & current_body = locus.current_body();
			auto sym_iter_index = ~locus.current.next();

			if (current_body.is_empty) locus.local->has_empty = true;
			else
			{
				terminal.unite(sym_iter_index);
				locus.local->terminal.unite(terminal.cselect());
			}

			locus.local->one_less();
		}

		nik_ce void sift()
		{
			auto & current_symbol = locus.current_symbol();
			auto sym_iter_index   = ~locus.current.next();

			if (current_symbol.is_nonterminal()) nonterminal_sift();
			else
			{
				terminal.unite(sym_iter_index);
				locus.local->terminal.unite(terminal.cselect());
				locus.local->one_less();
			}
		}

		nik_ce void nonterminal_sift()
		{
			auto & current_first = locus.current_first();

			if (current_first.is_unresolved()) locus.sifter->push(this);
			else resolved_nonterminal_sift();
		}

		nik_ce void resolved_nonterminal_sift()
		{
			auto & current_first = locus.current_first();
			auto & current_term  = locus.current_terminal();

			terminal.unite(current_term.cselect());

			if (current_first.has_empty)
			{
				locus.sifter->push(this);
				++locus.current;
			}
			else
			{
				locus.local->terminal.unite(terminal.cselect());
				locus.local->one_less();
			}
		}
	};

/***********************************************************************************************************************/

// head:

	template<auto static_parsed>
	struct T_head_first
	{
		using definition	= T_first_definition<static_parsed>;
		using terminal_type	= typename definition::terminal_type;

		gindex_type unresolved;
		terminal_type terminal;
		bool has_empty;

		nik_ce T_head_first() : unresolved{}, has_empty{} { }

		nik_ce bool is_unresolved () const { return (unresolved != 0); }
		nik_ce void one_less      () { if (unresolved) --unresolved; }
	};

/***********************************************************************************************************************/

// interface:

	template<auto static_parsed>
	struct T_parser_generator_first
	{
		nik_ces auto & parsed		= member_value_U<static_parsed>;

		using definition		= T_first_definition<static_parsed>;
		using head_first_ptr		= typename definition::head_first_ptr;
		using head_first_seq		= typename definition::head_first_seq;
		using body_first_seq		= typename definition::body_first_seq;
		using sifter_type		= typename definition::sifter_type;

		head_first_seq head_first;
		body_first_seq body_first;
		sifter_type sifter;

		nik_ce T_parser_generator_first() { head_first.fullsize(); }

		nik_ce void initialize(head_first_ptr lh_first, cguider_ctype_ref body_iter)
		{
			auto & locus = body_first.end()->locus;
			auto & body  = parsed.body_at(body_iter);

			locus.is_empty = body.is_empty;
			locus.action   = body.action;

			locus.set_global  (head_first.begin());
			locus.set_local   (lh_first);
			locus.set_pivot   (body_iter);
			locus.set_current (body_iter);
			locus.set_sifter  (&sifter);

			body_first.upsize();
			body_first.last()->initialize();
		}

		nik_ce void sift_once () { for (auto i = sifter.reset(); i.not_end(); ++i) (*i)->sift(); }
		nik_ce void sift_all  () { while (sifter.not_empty()) sift_once(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// follow:

	template<auto> struct T_symbol_follow;
	template<auto> struct T_body_follow;
	template<auto> struct T_head_follow;

/***********************************************************************************************************************/

// definition:

	template<auto static_parsed>
	struct T_follow_definition
	{
		nik_ces auto & parsed		= member_value_U<static_parsed>;
		nik_ces auto sym_follow_size	= parsed.symbol_total - parsed.term_size;

		using head_first_type		= T_head_first<static_parsed>;
		using head_first_ptr		= head_first_type*;
		using chead_first_ptr		= head_first_type const*;

		using head_follow_type		= T_head_follow<static_parsed>;
		using head_follow_ptr		= head_follow_type*;
		using head_follow_seq		= sequence<head_follow_type, parsed.head_size()>;

		using body_follow_type		= T_body_follow<static_parsed>;
		using body_follow_seq		= sequence<body_follow_type, parsed.body_size()>;

		using symbol_follow_type	= T_symbol_follow<static_parsed>;
		using symbol_follow_seq		= sequence<symbol_follow_type, sym_follow_size>;
		using symbol_follow_seq_ptr	= symbol_follow_seq*;

		using terminal_type		= sequence<gindex_type, parsed.term_size>;
		using terminal_ptr		= terminal_type*;

		using sifter_type		= T_sifter<symbol_follow_type, sym_follow_size>;
		using sifter_ptr		= sifter_type*;
	};

/***********************************************************************************************************************/

// locus:

	template<auto static_parsed>
	struct T_follow_locus
	{
		nik_ces auto & parsed		= member_value_U<static_parsed>;

		using definition		= T_follow_definition<static_parsed>;
		using chead_first_ptr		= typename definition::chead_first_ptr;
		using head_follow_ptr		= typename definition::head_follow_ptr;
		using sifter_ptr		= typename definition::sifter_ptr;

		chead_first_ptr first;
		head_follow_ptr global;
		head_follow_ptr local;
		cguider pivot;
		cguider current;
		sifter_ptr sifter;

		nik_ce T_follow_locus() : first{}, global{}, local{}, sifter{} { }

		nik_ce void set_first   (chead_first_ptr   p) { first   = p; }
		nik_ce void set_global  (head_follow_ptr   p) { global  = p; }
		nik_ce void set_local   (head_follow_ptr   p) { local   = p; }
		nik_ce void set_pivot   (cguider_ctype_ref g) { pivot   = g; }
		nik_ce void set_current (cguider_ctype_ref g) { current = g; }
		nik_ce void set_sifter  (sifter_ptr        s) { sifter  = s; }

		nik_ce const auto & pivot_symbol   () const { return parsed.symbol_at(pivot.next()); }
		nik_ce const auto & current_symbol () const { return parsed.symbol_at(current.next()); }

		nik_ce const auto local_index   () const { return local - global; }
		nik_ce const auto pivot_index   () const { return pivot_symbol().index; }
		nik_ce const auto current_index () const { return current_symbol().index; }

		nik_ce auto & pivot_follow   () { return global[pivot_index()]; }
		nik_ce auto & current_follow () { return global[current_index()]; }

		nik_ce auto & local_terminal   () { return local->terminal; }
		nik_ce auto & pivot_terminal   () { return pivot_follow().terminal; }
		nik_ce auto & current_terminal () { return current_follow().terminal; }
	};

/***********************************************************************************************************************/

// symbol:

	template<auto static_parsed>
	struct T_symbol_follow
	{
		using locus_type = T_follow_locus<static_parsed>;

		locus_type locus;

		nik_ce T_symbol_follow() { }

		nik_ce void set_locus(const locus_type & l)
		{
			locus = l;
			locus.set_current(l.pivot);
			++locus.current;
		}

		nik_ce void initialize()
		{
			auto & current = locus.current;

			while (current.not_end())
				if (not_end_resolve()) break;

			if (current.is_end()) is_end_resolve();
		}

		nik_ce bool not_end_resolve()
		{
			bool success          = true;
			auto & pivot_terminal = locus.pivot_terminal();
			auto & current_symbol = locus.current_symbol();
			auto current_index    = current_symbol.index;

			if (current_symbol.is_terminal()) pivot_terminal.unite(~locus.current.next());
			else
			{
				auto & current_first          = locus.first[current_index];
				auto & current_first_terminal = current_first.terminal;

				pivot_terminal.unite(current_first_terminal.cselect());

				if (current_first.has_empty)
				{
					success = false;
					++locus.current;
				}
			}

			return success;
		}

		nik_ce void is_end_resolve()
		{
			if (locus.pivot_index() != locus.local_index())
			{
				locus.pivot_follow().one_more();
				locus.sifter->push(this);
			}
		}

		nik_ce void end_resolve() // assumes no "follow" cycles exist.
		{
			if (locus.local->is_unresolved()) locus.sifter->push(this);
			else
			{
				auto & local_terminal = locus.local_terminal();
				auto & pivot_terminal = locus.pivot_terminal();

				pivot_terminal.unite(local_terminal.cselect());
				if (locus.local->has_prompt) locus.pivot_follow().has_prompt = true;

				locus.pivot_follow().one_less();
			}
		}
	};

/***********************************************************************************************************************/

// body:

	template<auto static_parsed>
	struct T_body_follow
	{
		using locus_type		= T_follow_locus<static_parsed>;
		using definition		= typename locus_type::definition;
		using symbol_follow_seq_ptr	= typename definition::symbol_follow_seq_ptr;

		locus_type locus;
		symbol_follow_seq_ptr symbol_follow_seq;

		nik_ce T_body_follow() : symbol_follow_seq{} { }

		nik_ce void set_symbol(symbol_follow_seq_ptr p) { symbol_follow_seq = p; }

		nik_ce void resolve()
		{
			for (auto & pivot = locus.pivot; pivot.not_end(); ++pivot)
			{
				auto & symbol = locus.pivot_symbol();

				if (symbol.is_nonterminal()) resolve_symbol();
			}
		}

		nik_ce void resolve_symbol()
		{
			auto sym_follow = symbol_follow_seq->end();

			sym_follow->set_locus(locus);
			sym_follow->initialize();

			symbol_follow_seq->upsize();
		}
	};

/***********************************************************************************************************************/

// head:

	template<auto static_parsed>
	struct T_head_follow
	{
		using definition	= T_follow_definition<static_parsed>;
		using terminal_type	= typename definition::terminal_type;

		gindex_type unresolved;
		terminal_type terminal;
		bool has_prompt;

		nik_ce T_head_follow() : unresolved{}, has_prompt{} { }

		nik_ce bool is_unresolved () const { return (unresolved != 0); }
		nik_ce void one_more      () { ++unresolved; }
		nik_ce void one_less      () { if (unresolved) --unresolved; }
	};

/***********************************************************************************************************************/

// interface:

	template<auto static_parsed>
	struct T_parser_generator_follow
	{
		nik_ces auto & parsed		= member_value_U<static_parsed>;

		using definition		= T_follow_definition<static_parsed>;
		using chead_first_ptr		= typename definition::chead_first_ptr;
		using head_follow_ptr		= typename definition::head_follow_ptr;
		using head_follow_seq		= typename definition::head_follow_seq;
		using body_follow_seq		= typename definition::body_follow_seq;
		using symbol_follow_seq		= typename definition::symbol_follow_seq;
		using sifter_type		= typename definition::sifter_type;

		head_follow_seq head_follow;
		body_follow_seq body_follow;
		symbol_follow_seq symbol_follow;
		sifter_type sifter;

		nik_ce T_parser_generator_follow() { head_follow.fullsize(); }

		nik_ce void initialize(head_follow_ptr lh_follow, cguider_ctype_ref body_iter, chead_first_ptr gh_first)
		{
			auto & locus = body_follow.end()->locus;

			locus.set_first  (gh_first);
			locus.set_global (head_follow.begin());
			locus.set_local  (lh_follow);
			locus.set_pivot  (body_iter);
			locus.set_sifter (&sifter);

			body_follow.end()->set_symbol(&symbol_follow);
			body_follow.upsize();
		}

		nik_ce void resolve_all () { for (auto k = body_follow.iterate(); k.not_end(); ++k) k->resolve(); }
		nik_ce void sift_once   () { for (auto i = sifter.reset(); i.not_end(); ++i) (*i)->end_resolve(); }
		nik_ce void sift_all    () { while (sifter.not_empty()) sift_once(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// targeter:

/***********************************************************************************************************************/

// interface:

	template<auto static_parsed>
	struct T_parser_generator_targeter
	{
		nik_ces auto & parsed		= member_value_U<static_parsed>;
		nik_ces auto & start_str	= T_store_U<static_parsed>::start_str;
		nik_ces auto & hierarchy	= parsed.hierarchy;

		using first_type		= T_parser_generator_first<static_parsed>;
		using head_first_ptr		= typename first_type::head_first_ptr;

		using follow_type		= T_parser_generator_follow<static_parsed>;
		using head_follow_ptr		= typename follow_type::head_follow_ptr;

		first_type first;
		follow_type follow;
		gindex_type start_index;

		nik_ce T_parser_generator_targeter(): start_index{}
		{
			initialize_first_follow();

			first.sift_all();

			follow.resolve_all();
			follow.sift_all();
		}

		nik_ce void initialize_first_follow()
		{
			auto i = first.head_first.begin(); 
			auto j = follow.head_follow.begin(); 

			for (auto k = hierarchy.cguide(); k.not_end(); ++k)
				initialize_first_follow_head(k.next(), i++, j++);
		}

		nik_ce void initialize_first_follow_head(cguider head_iter, head_first_ptr lh_first, head_follow_ptr lh_follow)
		{
			const auto gh_first = first.head_first.cbegin();

			initialize_unresolved(lh_first, head_iter);
			initialize_prompt(lh_follow, head_iter);

			for (; head_iter.not_end(); ++head_iter)
			{
				auto body_iter = head_iter.next();

				first.initialize(lh_first, body_iter);
				follow.initialize(lh_follow, body_iter, gh_first);
			}
		}

		nik_ce void initialize_unresolved(head_first_ptr lh_first, cguider_ctype_ref head_iter)
			{ lh_first->unresolved = head_iter.crelative_size(); }

		nik_ce void initialize_prompt(head_follow_ptr lh_follow, cguider_ctype_ref head_iter)
		{
			auto & head   = parsed.head_at(head_iter);
			auto & symbol = parsed.symbol_level[head.index];

			lh_follow->has_prompt = cctmp::apply<_subarray_same_<>>(symbol, start_str.cselect());

			if (lh_follow->has_prompt) start_index = follow.head_follow.left_size(lh_follow); 
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// targeted:

/***********************************************************************************************************************/

// interface:

	template<auto static_parsed>
	struct T_parser_generator_targeted
	{
		nik_ces auto & parsed		= member_value_U<static_parsed>;
		nik_ces auto value		= T_parser_generator_targeter<static_parsed>{};
		nik_ces auto start_index	= value.start_index;
		using type			= modify_type<_from_reference_, decltype(value)>;
		using first_definition		= T_first_definition<static_parsed>;
		using follow_definition		= T_follow_definition<static_parsed>;

	}; template<auto static_parsed>
		nik_ce auto _parser_generator_targeted_ = U_store_T<T_parser_generator_targeted<static_parsed>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// metapiler (cfg -> pda transition table):

/***********************************************************************************************************************/

// guider to symbol:

	template<auto static_targeted>
	struct T_guider_to_symbol
	{
		nik_ces auto & targeted = member_value_U<static_targeted>;
		nik_ces auto & parsed   = targeted.parsed;

		nik_ces auto result(cguider_ctype_ref g)
		{
			auto & symbol = parsed.symbol_at(g.next());

			return symbol_type{symbol.sign, symbol.index};
		}
	};
	
/***********************************************************************************************************************/

// interface:

	template<auto static_targeted>
	struct T_parser_generator_metapiler
	{
		nik_ces auto & targeted			= member_value_U<static_targeted>;
		nik_ces auto & parsed			= targeted.parsed;
		nik_ces auto & first			= targeted.first;
		nik_ces auto & follow			= targeted.follow;

		nik_ces auto & body_first		= first.body_first;
		nik_ces auto & head_follow		= follow.head_follow;

		nik_ces auto start_index		= targeted.start_index;
		nik_ces auto row_size			= parsed.head_size();
		nik_ces auto col_size			= parsed.grammar_size;
		nik_ces auto prod_size			= parsed.symbol_max;

		using first_definition			= typename T_store_U<static_targeted>::first_definition;
		using follow_definition			= typename T_store_U<static_targeted>::follow_definition;
		using cbody_first_ptr			= typename first_definition::body_first_type const*;
		using cterminal_ptr			= typename first_definition::terminal_type const*;
		using GuiderToSymbol			= T_guider_to_symbol<static_targeted>;

		using prod_type				= Production<prod_size>;
		using cprod_type			= prod_type const;
		using list_type				= sequence<prod_type, row_size * col_size>;

		// add action information.

		list_type list; // list instead of table due to clang bug.
		bool ambiguous;

		nik_ce T_parser_generator_metapiler() : ambiguous{}
		{
			list.fullsize();

			for (auto body = body_first.cbegin(); body != body_first.cend(); ++body)
				if (body->locus.is_empty) set_empty_entry(body);
				else set_entries(body, &body->terminal);
		}

		nik_ce void set_empty_entry(cbody_first_ptr body)
		{
			auto & local_follow = head_follow[body->locus.local_index()];

			set_entries(body, &local_follow.terminal);

			if (local_follow.has_prompt) set_prompt_entry(body);
		}

		nik_ce void set_prompt_entry(cbody_first_ptr body)
		{
			gindex_type row = body->locus.local_index();
			gindex_type pos = get_pos(row, parsed.prompt_token);

			if (list[pos].valid) ambiguous = true;
			else
			{
				list[pos].valid = true;
				list[pos].action = body->locus.action;
			}
		}

		nik_ce void set_entries(cbody_first_ptr body, cterminal_ptr terminal)
		{
			for (auto term = terminal->citerate(); term.not_end(); ++term)
				set_entry(body, *term);
		}

		nik_ce void set_entry(cbody_first_ptr body, gindex_type term_pos)
		{
			auto pos = get_pos(body, term_pos);
			auto act = body->locus.action;

			if (list[pos].valid) ambiguous = true;
			else if (body->locus.is_empty)
			{
				list[pos].valid = true;
				list[pos].action = act;
			}
			else
			{
				auto & pivot = body->locus.pivot;
				list[pos].template map<GuiderToSymbol>(pivot, act);
			}
		}

		nik_ce gindex_type get_pos(gindex_type row, gindex_type col) const
			{ return row * col_size + col; }

		nik_ce gindex_type get_pos(cbody_first_ptr body, gindex_type term_pos) const
		{
			gindex_type row = body->locus.local_index();
			gindex_type col = parsed.symbol_level[term_pos].index;

			return get_pos(row, col);
		}

		nik_ce cprod_type & production(csymbol_type & row, ctoken_type col) const
			{ return list[row.token() * col_size + col]; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic:

/***********************************************************************************************************************/

// transition table:

	template<typename T_grammar>
	struct T_generic_tt
	{
		nik_ces auto static_src			= _static_callable_<T_grammar::source>;
		nik_ces auto static_grammar	 	= U_store_T<T_grammar>;
		nik_ces auto static_scanned		= _parser_generator_scanned_<static_src>;
		nik_ces auto static_parsed		= _parser_generator_parsed_<static_scanned, static_grammar>;
		nik_ces auto static_targeted		= _parser_generator_targeted_<static_parsed>;
	};

/***********************************************************************************************************************/

// pushdown automata:

	template<typename T_grammar>
	struct T_generic_pda : public T_parser_generator_metapiler<T_generic_tt<T_grammar>::static_targeted>
	{
		using T_tt = T_generic_tt<T_grammar>;
		using base = T_parser_generator_metapiler<T_tt::static_targeted>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace generator

