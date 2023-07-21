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

// parser generator printers:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// spacing:

/***********************************************************************************************************************/

// interface:

	template<auto static_grammar>
	struct parser_generator_spacing
	{
		using T_grammar				= T_store_U<static_grammar>;
		using spacing_type			= pair<gkey_type, gkey_type>;

		template<auto ss, auto sg>
		constexpr static auto U_static_parsed	= U_store_T<T_parser_generator_parsed<ss, sg>>;

		constexpr static auto static_src	= _static_callable_<T_grammar::source>;
		constexpr static auto static_scanned	= U_store_T<T_parser_generator_scanned<static_src>>;
		constexpr static auto static_parsed	= U_static_parsed<static_scanned, static_grammar>;

		using parsed_type			= member_type_U<static_parsed>;
		using cnavigator_type			= typename parsed_type::cnavigator_type;

		constexpr static auto & parsed	  	= member_value_U<static_parsed>;
		constexpr static auto & cfg	 	= parsed.hierarchy;
		constexpr static auto cfg_nav		= cnavigator_type{cfg.origin()};

		constexpr static auto get_nonterminal_spacing()
		{
			auto spacing = spacing_type{_zero, _zero};

			for (auto j = parsed.head_level.cbegin(); j != parsed.head_level.cend(); ++j)
			{
				auto index     = j->index;
				const auto & k = parsed.symbol_level[index];
				auto size_v0   = k.size();
				auto size_v1   = generic_printer::get_digit_spacing(index);

				if (size_v0 > spacing.v0) spacing.v0 = size_v0;
				if (size_v1 > spacing.v1) spacing.v1 = size_v1;
			}

			return spacing;
		}

		constexpr static auto get_body_spacing(cnavigator_type & n)
		{
			auto spacing = spacing_type{_zero, _zero};

			for (+n; n.not_end(); ++n)
			{
				const auto & k = parsed.symbol_at(n);
				auto size_v0   = k.size();
				auto size_v1   = generic_printer::get_digit_spacing(~n);

				if (size_v0 > spacing.v0) spacing.v0 = size_v0;
				if (size_v1 > spacing.v1) spacing.v1 = size_v1;
			}

			-n;

			return spacing;
		}

		constexpr static auto get_body_set_spacing(cnavigator_type & n)
		{
			auto spacing = spacing_type{_zero, _zero};

			for (+n; n.not_end(); ++n)
			{
				auto size = get_body_spacing(n);

				if (size.v0 > spacing.v0) spacing.v0 = size.v0;
				if (size.v1 > spacing.v1) spacing.v1 = size.v1;
			}

			-n;

			return spacing;
		}

		constexpr static auto get_nonterm_body_spacing()
		{
			auto spacing = spacing_type{_zero, _zero};

			for (auto n = cfg_nav; n.not_end(); ++n)
			{
				auto size = get_body_set_spacing(n);

				if (size.v0 > spacing.v0) spacing.v0 = size.v0;
				if (size.v1 > spacing.v1) spacing.v1 = size.v1;
			}

			return spacing;
		}

		constexpr static auto nonterminal_spacing  = get_nonterminal_spacing();
		constexpr static auto nonterm_body_spacing = get_nonterm_body_spacing();
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parsed:

/***********************************************************************************************************************/

// interface:

	template<auto static_grammar>
	struct parser_generator_parsed_printer
	{
		public:

			using spacing		= parser_generator_spacing<static_grammar>;
			using spacing_type	= typename spacing::spacing_type;
			using cnavigator_type	= typename spacing::cnavigator_type;

			constexpr static auto & nonterminal_spacing	= spacing::nonterminal_spacing;
			constexpr static auto & nonterm_body_spacing	= spacing::nonterm_body_spacing;

			constexpr static auto & parsed	  		= spacing::parsed;
			constexpr static auto & cfg_nav			= spacing::cfg_nav;

			constexpr static void print_symbol
				(const level_symbol & symbol, gindex_type index, const spacing_type & spacing)
			{
				auto length = symbol.size();
				generic_printer::print_spacing(spacing.v0 - length);
				generic_printer::print_string(symbol);

				auto str = "";
				switch (symbol.sign)
				{
					case Sign::na          : { str = " "; break; }
					case Sign::terminal    : { str = "t"; break; }
					case Sign::nonterminal : { str = "n"; break; }
					case Sign::dimension   : { str = "d"; break; }
				}
			    	printf("{%s|", str);

				auto is_print_right = symbol.is_terminal()
						   || symbol.is_nonterminal();

				if (is_print_right)
				{
					auto size = generic_printer::get_digit_spacing(index);
					generic_printer::print_spacing(spacing.v1 - size);
					printf("%hu", index);
				}
				else generic_printer::print_spacing(spacing.v1);

			    	printf("}");
				generic_printer::print_spacing(_two);
			}

			void print_symbol(cnavigator_type & n, const spacing_type & spacing)
			{
				+n;
			//	print_symbol(parsed.symbol_at(n), ~n, spacing);
				auto & symbol = parsed.symbol_at(n);
				print_symbol(symbol, symbol.index, spacing);
				-n;
			}

			void print_nonterminal(cnavigator_type & h, const spacing_type & spacing)
			{
				auto head   = parsed.head_at(+h);
				auto symbol = parsed.symbol_level[head.index];
				auto length = symbol.size();
				auto size   = generic_printer::get_digit_spacing(~h);

				generic_printer::print_spacing(spacing.v0 + _one - length);
				generic_printer::print_string(symbol);
				printf("{");
				generic_printer::print_spacing(spacing.v1 - size);
				printf("%hu} -> ", symbol.index);
				-h;
			}

			void print_body(cnavigator_type & n, gckey_type margin, const spacing_type & spacing)
			{
				generic_printer::print_spacing(margin);
				for (+n; n.not_end(); ++n) print_symbol(n, spacing);
				printf("\n");
				-n;
			}

			void print_head(cnavigator_type & h, cnavigator_type & n) // body_set = n, symbol = h
			{
				auto margin  = nonterminal_spacing.v0 + nonterminal_spacing.v1 + _seven;
				auto spacing = nonterm_body_spacing;

				print_nonterminal(h, nonterminal_spacing);
				print_body(+n, _zero, spacing);

				for (++n; n.not_end(); ++n) print_body(n, margin, spacing);
				printf("\n");
				-n;
			}

		public:

			parser_generator_parsed_printer() { }

			void print_head()
			{
				auto spacing = nonterm_body_spacing;
				for (auto k = parsed.head_level.cbegin(); k != parsed.head_level.cend(); ++k)
					print_symbol(parsed.symbol_level[k->index], k->index, spacing);

				printf("\n");
			}

			void print_symbols()
			{
				auto spacing = nonterm_body_spacing;
				for (auto k = parsed.symbol_level.cbegin(); k != parsed.symbol_level.cend(); ++k)
					print_symbol(*k, parsed.symbol_level.left_size(k), spacing);
			}

			void print_actions()
			{
				auto spacing = spacing_type{12, 2};
				for (auto k = parsed.action_level.cbegin(); k != parsed.action_level.cend(); ++k)
				{
					print_symbol(*k, k->index, spacing);
					printf("\n");
				}
			}

			void print_cfg()
			{
				auto h = cfg_nav;
				for (auto n = cfg_nav; n.not_end(); ++h, ++n) print_head(h, n);
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// targeted:

/***********************************************************************************************************************/

// interface:

	template<auto static_grammar>
	struct parser_generator_targeted_printer
	{
		public:

			using parsed_printer	= parser_generator_parsed_printer<static_grammar>;
			using spacing		= typename parsed_printer::spacing;
			using T_targeted	= T_parser_generator_targeted<spacing::static_parsed>;

			constexpr static auto & nonterm_body_spacing	= spacing::nonterm_body_spacing;
			constexpr static auto static_parsed		= spacing::static_parsed;
			constexpr static auto static_targeted		= U_store_T<T_targeted>;

			constexpr static auto & parsed	  		= member_value_U<static_parsed>;
			constexpr static auto & targeter		= member_value_U<static_targeted>;

		public:

			parser_generator_targeted_printer() { }

			void print_nonterm_symbol_first()
			{
				auto & first = parsed.symbol_level;
				auto spacing = nonterm_body_spacing;

				for (auto k = first.cbegin(); k != first.cend(); ++k)
				if (k->is_nonterminal())
				{
					parsed_printer::print_symbol(*k, k->index, spacing);
					printf("\n");
				}
			}

			void print_head_symbol_first()
			{
				auto & first = parsed.head_level;
				auto spacing = nonterm_body_spacing;

				for (auto k = first.cbegin(); k != first.cend(); ++k)
				{
					auto & symbol = parsed.symbol_level[k->index];
					parsed_printer::print_symbol(symbol, first.left_size(k), spacing);
					printf("\n");
				}
			}

			template<bool is_first, typename Type>
			void print_targeter_head(const Type & value)
			{
				auto spacing = nonterm_body_spacing;

				for (auto k = value.cbegin(); k != value.cend(); ++k)
				{
					auto & term = k->terminal;
					auto & head = parsed.head_level[value.left_size(k)];
					auto & nonterm = parsed.symbol_level[head.index];

					parsed_printer::print_symbol(nonterm, head.index, spacing);
				//	if constexpr (is_first) printf("| %hu | %s |", k->unresolved, k->has_empty ? "e" : " ");
				//	else printf("| %hu | %s |", k->unresolved, k->has_prompt ? "$" : " ");
					if constexpr (is_first) printf("| %s |", k->has_empty ? "e" : " ");
					else printf("| %s |", k->has_prompt ? "$" : " ");

					for (auto j = term.cbegin(); j != term.cend(); ++j)
						parsed_printer::print_symbol(parsed.symbol_level[*j], *j, spacing);

					printf("\n");
				}
			}

			template<typename Type>
			void print_targeter_body(const Type & value)
			{
				auto spacing = nonterm_body_spacing;

				for (auto k = value.cbegin(); k != value.cend(); ++k)
				{
					auto & term = k->terminal;
					auto iter   = k->locus.pivot;

					while (iter.not_end())
					{
						auto i = iter;
						+i;
						parsed_printer::print_symbol(parsed.symbol_at(i), ~i, spacing);
						++iter;
					}

					printf(" -> ");

					for (auto j = term.cbegin(); j != term.cend(); ++j)
						parsed_printer::print_symbol(parsed.symbol_level[*j], *j, spacing);

					printf("\n");
				}
			}

			void print_head_first() { print_targeter_head<true>(targeter.first.head_first); }
			void print_body_first() { print_targeter_body(targeter.first.body_first); }

			void print_head_follow() { print_targeter_head<false>(targeter.follow.head_follow); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// transition table:

/***********************************************************************************************************************/

// interface:

	template<auto static_grammar>
	struct parser_generator_tt_printer
	{
		public:

			using targeted_printer	= parser_generator_targeted_printer<static_grammar>;
			using parsed_printer	= typename targeted_printer::parsed_printer;
			using spacing		= typename targeted_printer::spacing;
			using spacing_type	= typename spacing::spacing_type;

			constexpr static auto static_parsed		= targeted_printer::static_parsed;
			constexpr static auto static_targeted		= targeted_printer::static_targeted;

			constexpr static auto & parsed	  		= targeted_printer::parsed;
			constexpr static auto tr_table			= T_parser_generator_metapiler<static_targeted>{};

			using T_parser    = typename T_store_U<static_parsed>::T_parser;
			using T_pda       = typename T_parser::T_pda;

		public:

			parser_generator_tt_printer() { }

			bool inc_row_col(pair<gindex_type, gindex_type> & pos)
			{
				bool next_row = pos.v1 + 1 == tr_table.col_size;

				if (next_row)
				{
					++pos.v0;
					pos.v1 = 0;
				}
				else ++pos.v1;

				return next_row;
			}

			template<typename ProdPtr, typename Seq>
			void tr_table_string(ProdPtr k, Seq & str) // needs to be updated:
			{
				str.clear();

				char tok;

				for (auto j = k->cbegin(); j != k->cend(); ++j)
				{
					if (j->is_terminal())
					{
						auto & l = parsed.grammar_map.rlookup(j->token(), "?");
						gindex_type pos = (l[0] == '\\');
						tok = l[pos];
					}
					else tok = parsed.symbol_level[parsed.head_level[j->token()].index].cbegin()[0];

					str.push(tok);
				}

				str.push('\0');
			}

			void print_tr_table(gindex_type offset = T_pda::prod_size + 2, gkey_type sp = 7)
			{
				constexpr auto & list    = tr_table.list;
				constexpr auto prod_size = tr_table.prod_size;
				constexpr auto row_size  = tr_table.row_size;
				constexpr auto col_size  = tr_table.col_size;

				auto spacing = spacing_type{sp, 2};
				auto pos     = pair<gindex_type, gindex_type>{0, 0};

				sequence<char, prod_size> str;

				for (auto k = list.cbegin(); k != list.cend(); ++k, inc_row_col(pos))
				{
					auto   head_pos = parsed.head_level[pos.v0].index;
					auto & head_sym = parsed.symbol_level[head_pos];

					auto &  col_str = parsed.grammar_map.rlookup(pos.v1, "");
					auto        act = k->action;

					tr_table_string(k, str);

					if (k->valid)
					{
						printf("\t");
						generic_printer::print_noback_string(head_sym);
						generic_printer::print_spacing(1);
						generic_printer::print_noback_string(col_str);
						printf(" -> %s", str.cbegin());
						generic_printer::print_spacing(offset - str.size());

						if (act > ActionName::nop)
						{
							auto & act_str = parsed.grammar_action.rlookup(act, "");

							printf(": ");
							generic_printer::print_string(act_str);
						}

						printf("\n");
					}
				}
			}

			void print_num_tr_table()
			{
				constexpr auto & list = tr_table.list;

				printf("\t\tnik_ces auto start_index\t= %hu;\n", tr_table.start_index);
				printf("\t\tnik_ces auto row_size\t\t= %hu;\n", tr_table.row_size);
				printf("\t\tnik_ces auto col_size\t\t= %hu;\n", tr_table.col_size);
				printf("\n");

				for (auto k = list.cbegin(); k != list.cend(); ++k)
				{
					if (k->valid)
					{
						gindex_type num	= list.left_size(k);

						printf("\t\t\t");
						unsigned count = 0; 

						for (auto j = k->cbegin(); j != k->cend(); ++j)
						{
							auto j_str = j->is_nonterminal() ? "true" : "false";
							auto j_tok = j->token();

							printf("list[%hu].push({%s, %hu});", num, j_str, j_tok);

							count = ((count + 1) % 3);

							if (count) printf(" ");
							else printf("\n\t\t\t");
						}

						printf("list[%hu].valid = true; ", num);
						printf("list[%hu].action = %hu;\n" , num, k->action);
					}
				}
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

