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

// generic printers:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic:

/***********************************************************************************************************************/

// interface:

	struct generic_printer
	{
		constexpr static auto get_digit_spacing(gkey_type d)
		{
			auto size = _one;

			while (d /= _ten) ++size;

			return size;
		}

		constexpr static void print_spacing(gckey_type size) { for (auto k = 0; k != size; ++k) printf(" "); }

		template<typename Type>
		constexpr static void print_string(const Type & str)
			{ for (auto k = str.cbegin(); k != str.cend(); ++k) printf("%c", *k); }

		template<typename Type>
		constexpr static void print_noback_string(const Type & str)
		{
			for (auto k = str.cbegin(); k != str.cend(); ++k)
				if (*k != '\\') printf("%c", *k);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parser ss (stack/string):

/***********************************************************************************************************************/

// :

	template<typename T_action, typename T_pda>
	struct T_generic_parser_ss_printer : public T_generic_parser<T_action, T_pda>
	{
		using base					= T_generic_parser<T_action, T_pda>;
		using T_lexer					= typename base::T_lexer;
		using cparseme_ref				= typename base::cparseme_ref;
		using parseme_ref				= typename base::parseme_ref;
		using cparsoid_ref				= typename base::cparsoid_ref;
		using parsoid_ref				= typename base::parsoid_ref;

		using T_grammar					= T_parser_generator_grammar;
		using T_parser					= T_parser_generator_parser<T_action, T_grammar>;

		constexpr static auto & grammar_map		= T_grammar::map;

		// avoids T_pg_tt due to optimized printers:

		constexpr static auto static_src		= _static_callable_<T_grammar::source>;
		constexpr static auto static_grammar	 	= U_store_T<T_grammar>;
		constexpr static auto static_scanned		= _parser_generator_scanned_<static_src>;

		constexpr static auto & src			= T_store_U<static_scanned>::src;
		constexpr static auto parser			= T_parser{src.cselect()};
		constexpr static auto & pg_parsed		= parser.parseme.tree;

		//

		constexpr static void parse(parseme_ref p, parsoid_ref q)
		{
			T_lexer::lex(p.word);

			int k     = 0;
			int start = 0;//295;
			int depth = 303;//303;

			while ((k != depth) && base::not_string_end(p) && base::not_stack_end(q))
			{
				if (k >= start) print_current(p, q, k);

				base::dispatch(p, q);

				++k;
			}

			end_dispatch(p, q);
		}

		constexpr static void end_dispatch(parseme_ref p, parsoid_ref q)
		{
			switch (base::end_dispatch_index(p, q))
			{
				case base::End::string_only : { end_dispatch_string_only (p, q); break; }
				case base::End::stack_only  : { end_dispatch_stack_only  (p, q); break; }
				case base::End::both        : { end_dispatch_both        (p, q); break; }
			}
		}

		constexpr static void end_dispatch_string_only(parseme_ref p, parsoid_ref q)
		{
			p.word.token = T_lexer::Token::prompt;

			int k     = 301;
			int start = 301;
			int depth = 303;

			while ((k != depth) && base::not_stack_end(q))
			{
				if (k >= start) print_current(p, q, k);

				base::dispatch(p, q);

				++k;
			}

			if (k >= start) print_current(p, q, k);

			// (q.stack.front() == T_pda::stack_finish);
		}

		constexpr static void end_dispatch_stack_only(parseme_ref p, parsoid_ref q)
		{
		}

		constexpr static void end_dispatch_both(parseme_ref p, parsoid_ref q)
		{
		}

		// printers:

			constexpr static void print_current(cparseme_ref p, cparsoid_ref q, gindex_type k)
			{
				generic_printer::print_spacing(k < 10);
				printf("%hu| ", k);
				generic_printer::print_spacing(20 - q.stack.size());
				print_stack(q);

				auto wsp = words_size(p);
				generic_printer::print_spacing(30 - wsp);
				print_words(p);

				printf("\n");
			}

			//

			constexpr static void print_stack(cparsoid_ref q)
			{
				for (auto k = q.stack.cend(); k != q.stack.cbegin(); --k)
					print_stack_value(*k);

				print_stack_value(*q.stack.cbegin());
			}

			constexpr static void print_stack_value(csymbol_ref s)
			{
				if (s.is_nonterminal()) print_nonterminal_value(s);
				else print_terminal_value(s);
			}

			constexpr static void print_nonterminal_value(csymbol_ref s)
			{
				auto & head	= pg_parsed.head_level[s.token()];
				auto & symbol	= pg_parsed.symbol_level[head.index];

				generic_printer::print_noback_string(symbol);
			}

			constexpr static void print_terminal_value(csymbol_ref s)
			{
				generic_printer::print_noback_string(grammar_map.rlookup(s.token(), "?"));
			}

			//

			constexpr static auto words_size(cparseme_ref p)
			{
				auto size = 0;

				for (lexeme w = p.word; w.not_empty(); T_lexer::lex(w.retract()))
					++size;

				if (size < 20) return ++size;
				else return 20;
			}

			constexpr static void print_words(cparseme_ref p)
			{
				auto count = 0;

				for (lexeme w = p.word; count != 20 && w.not_empty() != 0; T_lexer::lex(w.retract()))
				{
					print_word_value(w.token);
					++count;
				}

				print_word_value(T_lexer::Token::prompt);
			}

			constexpr static void print_word_value(ctoken_type t)
			{
				generic_printer::print_noback_string(grammar_map.rlookup(t, "?"));
			}
	};

/***********************************************************************************************************************/

	template<typename T_action, typename T_grammar>
	struct T_parser_ss_printer
	{
		using T_ast		= typename T_action::T_ast;
		using T_pda		= T_parser_generator_pda<T_grammar>;
		using T_parser		= T_generic_parser_ss_printer<T_action, T_pda>;

		using parseme_type	= T_parseme<T_ast>;
		using parseme_ref	= parseme_type&;
		using cparseme_type	= parseme_type const;
		using cparseme_ref	= cparseme_type&;

		using parsoid_type	= T_parsoid<T_pda::stack_size, T_pda::prod_size>;
		using parsoid_ref	= parsoid_type&;
		using cparsoid_type	= parsoid_type const;
		using cparsoid_ref	= cparsoid_type&;

		parseme_type parseme;
		parsoid_type parsoid;

		constexpr T_parser_ss_printer(const cselector<char> & s) :

			parseme{s}, parsoid{T_pda::stack_start, T_pda::stack_finish}

			{ parse(parseme, parsoid); }

		constexpr void parse(parseme_ref p, parsoid_ref q)
			{ T_parser::parse(p, q); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

