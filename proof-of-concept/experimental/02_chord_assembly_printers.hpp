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

// chord assembly printers:

namespace generator {

	using namespace cctmp;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// chord assembly:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// scanner:

/***********************************************************************************************************************/

// parsed:

	template<auto static_grammar, auto callable_source>
	struct chord_assembly_scanner_parsed_printer
	{
		private:

			using T_grammar					= T_store_U<static_grammar>;
			using CASAN					= chord::CASAN;
			using T_ast					= chord::T_chord_assembly_scanner_ast;
			using Total					= typename T_ast::Total;
			using Capacity					= typename T_ast::Cap;

			template<auto ss, auto sg>
			constexpr static auto U_static_pg_parsed	= U_store_T<T_parser_generator_parsed<ss, sg>>;

			constexpr static auto static_pg_src		= _static_callable_<T_grammar::source>;
			constexpr static auto static_pg_scanned		= U_store_T<T_parser_generator_scanned<static_pg_src>>;
			constexpr static auto static_pg_parsed		= U_static_pg_parsed<static_pg_scanned, static_grammar>;

			//

			template<auto st, auto ss>
			constexpr static auto U_static_parsed		= U_store_T<chord::T_chord_assembly_scanner_parsed<st, ss>>;

			constexpr static auto static_pair		= _static_callable_<callable_source>;
			constexpr static auto static_src		= _static_car_<static_pair>;
			constexpr static auto static_parsed		= U_static_parsed<static_pg_parsed, static_src>;

			constexpr static auto & parsed			= member_value_U<static_parsed>;

		public:

			chord_assembly_scanner_parsed_printer() { }

			void print_total()
			{
				printf("total\n\n");

				printf("line  : %hu\n", parsed.total[ Total::line  ]);
				printf("arg   : %hu\n", parsed.total[ Total::arg   ]);
				printf("pad   : %hu\n", parsed.total[ Total::pad   ]);
				printf("tree  : %hu\n", parsed.total[ Total::tree  ]);
				printf("label : %hu\n", parsed.total[ Total::label ]);
				printf("jump  : %hu\n", parsed.total[ Total::jump  ]);
				printf("morph : %hu\n", parsed.total[ Total::morph ]);
				printf("cycle : %hu\n", parsed.total[ Total::cycle ]);

				printf("\n");
			}

			void print_capacity()
			{
				printf("capacity\n\n");

				printf("tree  : %hu\n", parsed.capacity[ Capacity::tree  ]);
				printf("morph : %hu\n", parsed.capacity[ Capacity::morph ]);
				printf("cycle : %hu\n", parsed.capacity[ Capacity::cycle ]);

				printf("\n");
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parsed:

/***********************************************************************************************************************/

// interface:

	template<auto static_grammar, auto callable_source>
	struct chord_assembly_parsed_printer
	{
	//	private:
		public:

			using T_grammar					= T_store_U<static_grammar>;
			using Token					= typename T_grammar::Token;
			using strlit_type				= string_literal<>;
			using cstrlit_type				= strlit_type const;
			using cstrlit_ref				= cstrlit_type&;

			// pg parsed:

			template<auto ss, auto sg>
			constexpr static auto U_static_pg_parsed	= U_store_T<T_parser_generator_parsed<ss, sg>>;

			constexpr static auto static_pg_src		= _static_callable_<T_grammar::source>;
			constexpr static auto static_pg_scanned		= U_store_T<T_parser_generator_scanned<static_pg_src>>;
			constexpr static auto static_pg_parsed		= U_static_pg_parsed<static_pg_scanned, static_grammar>;

			// scanned:

			template<auto st, auto ss>
			constexpr static auto U_static_scanned		= U_store_T<chord::T_chord_assembly_scanner_parsed<st, ss>>;

			constexpr static auto static_pair		= _static_callable_<callable_source>;
			constexpr static auto static_src		= _static_car_<static_pair>;
			constexpr static auto static_scanned		= U_static_scanned<static_pg_parsed, static_src>;

			// parsed:

			template<auto st, auto ss>
			constexpr static auto U_static_parsed		= U_store_T<chord::T_chord_assembly_parsed<st, ss>>;

			constexpr static auto static_parsed		= U_static_parsed<static_pg_parsed, static_scanned>;

			using parsed_type				= member_type_U<static_parsed>;
			using cnavigator_type				= typename parsed_type::toc_type::cnavigator_type;
			using pair_type					= pair<bool, gindex_type>;
			using cpair_type				= pair_type const;
			using cpair_ref					= cpair_type&;

			constexpr static auto & parsed			= member_value_U<static_parsed>;
		//	constexpr static auto & link 			= parsed.toc.link_level;

			pair_type ind(gindex_type i, bool b = true) { return pair_type{b, i}; }

		public:

			template<typename ArgType>
			void print_arg_info(const ArgType & arg, gckey_type spacing, cpair_ref p)
			{
				auto sub = _zero;

				auto size = sub + arg.size();
				if (spacing > size) generic_printer::print_spacing(spacing - size);

				generic_printer::print_string(arg);

				if (p.v0) printf("{%d}", (int) p.v1);
			}

			template<typename EntryType>
			void print_entry_info(const EntryType & entry, gckey_type spacing)
			{
				auto str = "";
				auto sub = _zero;

				switch (entry.sign)
				{
					case chord::Sign::na           : { str = " "     ; sub = 1; break; }
					case chord::Sign::constant_arg : { str = "carg"  ; sub = 4; break; }
					case chord::Sign::mutable_arg  : { str = "marg"  ; sub = 4; break; }
					case chord::Sign::static_arg   : { str = "sarg"  ; sub = 4; break; }
					case chord::Sign::copy         : { str = "."     ; sub = 1; break; }
					case chord::Sign::paste        : { str = "_"     ; sub = 1; break; }
					case chord::Sign::recurse      : { str = "rec"   ; sub = 3; break; }
					case chord::Sign::label        : { str = "l"     ; sub = 1; break; }
					case chord::Sign::jump         : { str = "jump"  ; sub = 4; break; }
					case chord::Sign::env          : { str = "env"   ; sub = 3; break; }
					case chord::Sign::morph        : { str = "morph" ; sub = 5; break; }
					case chord::Sign::cycle        : { str = "cycle" ; sub = 5; break; }

					case chord::Sign::dimension : { str = "dim" ; sub = 3; break; }
				}

				auto size = sub + entry.size();
				if (spacing > size) generic_printer::print_spacing(spacing - size);

				generic_printer::print_string(entry);

				auto print_right  = chord::Sign::is_constant_arg (entry.sign)
						 || chord::Sign::is_mutable_arg  (entry.sign)
						 || chord::Sign::is_static_arg   (entry.sign)
						 || chord::Sign::is_paste        (entry.sign)
						 || chord::Sign::is_label        (entry.sign)
						 || chord::Sign::is_jump         (entry.sign)
						 || chord::Sign::is_morph        (entry.sign)
						 || chord::Sign::is_cycle        (entry.sign);

				auto env_str   = "";
				auto print_env = false;
				if (chord::Sign::is_env(entry.sign))
				{
					switch (entry.index)
					{
						case chord::Link::tree        : { env_str = "tree" ; print_env = true; break; }
						case chord::Link::morph       : { env_str = "morp" ; print_env = true; break; }
						case chord::Link::cycle_param : { env_str = "para" ; print_env = true; break; }
						case chord::Link::cycle_iter  : { env_str = "iter" ; print_env = true; break; }
					}
				}

				if (print_right)    printf("{%s|%d}", str, (int) entry.index);
				else if (print_env) printf("{%s|%s}", str, env_str);
				else                printf("{%s}", str);
			}

			template<typename LineType>
			void print_line_info(const LineType & line, gckey_type spacing)
			{
				auto str = "";

				switch (line.kind)
				{
					case chord::Context::none    : { str = "      "; break; }
					case chord::Context::assign  : { str = "assign"; break; }
					case chord::Context::re_turn : { str = "return"; break; }
					case chord::Context::apply   : { str = "apply "; break; }
					case chord::Context::vo_id   : { str = "void  "; break; }
					case chord::Context::test    : { str = "test  "; break; }
					case chord::Context::label   : { str = "label "; break; }
					case chord::Context::branch  : { str = "branch"; break; }
					case chord::Context::go_to   : { str = "goto  "; break; }
				}

			//	auto str0 = line.has_link  ? "link"  : "    " ;
				auto str1 = line.has_paste ? "paste" : "     ";

			//	printf("|%s|%s|%s| ", str, str0, str1);
				printf("|%s|%s| ", str, str1);
			}

			template<typename FuncType>
			void print_morphism(const FuncType & func, gckey_type spacing)
			{
				for (auto k = func.cbegin(); k != func.cend(); ++k)
				{
					generic_printer::print_spacing(1);
					print_entry_info(*k, spacing);
				}
			}

		//	template<typename CycleType>
		//	void print_cycle_parameter(const CycleType & cycle, gckey_type spacing)
		//	{
		//		auto & parameter = cycle.parameter;

		//		printf(" |");
		//		print_morphism(cycle.action, spacing);

		//		for (auto k = parameter.cbegin(); k != parameter.cend(); ++k)
		//		{
		//			printf(" |");
		//			print_morphism(*k, spacing);
		//		}
		//	}

		//	template<typename K, typename J, typename CycleType>
		//	void print_interval(K k, J j, const CycleType & cycle, gckey_type spacing)
		//	{
		//		auto lstr = (k->left  == chord::Ival::closed) ? '[' : '(';
		//		auto rstr = (k->right == chord::Ival::closed) ? ']' : ')';

		//		printf(" %c", lstr);
		//		print_morphism(*j, spacing);
		//		if (k->is_lead)
		//		{
		//			printf(",");
		//		//	print_morphism(cycle.tonic_iter, spacing); // currently not working.
		//		}
		//		printf(" %c ", rstr);
		//	}

		//	template<typename CycleType>
		//	void print_cycle_interval(const CycleType & cycle, gckey_type spacing)
		//	{
		//		auto & interval = cycle.interval;
		//		auto & iterator = cycle.iterator;

		//		auto j = iterator.cbegin();

		//		for (auto k = interval.cbegin(); k != interval.cend(); ++k, ++j)
		//			if (k->is_fixed) printf(" { id{env|iter} } ");
		//			else print_interval(k, j, cycle, spacing);
		//	}

		//	template<typename MorphType>
		//	void print_morph_info(const MorphType & morph, gckey_type spacing)
		//	{
		//		auto str = "";
		//		auto sub =  0;

		//		switch (morph.token)
		//		{
		//			case Token::argpose : { str = "argpose" ; sub = 7; break; }
		//			case Token::subpose : { str = "subpose" ; sub = 7; break; }
		//			case Token::curry   : { str = "curry"   ; sub = 5; break; }
		//		}

		//		if (spacing > sub) generic_printer::print_spacing(spacing - sub);
		//		printf("%s", str);

		//		print_morphism(morph.parameter, spacing);
		//		printf("\n");
		//	}

		//	template<typename CycleType>
		//	void print_cycle_info(const CycleType & cycle, gckey_type spacing)
		//	{
		//		auto str = "";
		//		auto sub =  0;

		//		switch (cycle.token)
		//		{
		//			case Token::repeat : { str = "repeat" ; sub = 6; break; }
		//			case Token::map    : { str = "map"    ; sub = 3; break; }
		//			case Token::fold   : { str = "fold"   ; sub = 4; break; }
		//			case Token::find   : { str = "find"   ; sub = 4; break; }
		//			case Token::sift   : { str = "sift"   ; sub = 4; break; }
		//		}

		//		if (spacing > sub) generic_printer::print_spacing(spacing - sub);
		//		printf("%s", str);

		//		print_cycle_parameter (cycle, spacing);
		//		printf("\n\t");
		//		print_cycle_interval  (cycle, spacing);
		//	}

		public:

			chord_assembly_parsed_printer() { }

			void print_args(gckey_type spacing)
			{
				printf("definition:");
				generic_printer::print_spacing(10);
				print_arg_info(parsed.name, spacing, ind(0, false));

				auto & arg_level = parsed.arg_level;
				for (auto k = arg_level.citerate(); k.not_end(); ++k)
				{
					printf(" ");
					print_arg_info(*k, spacing, ind(k.left_size()));
				}

				printf("\n");
			}

			void print_entries(cguider line_iter, gckey_type spacing)
			{
				for (; line_iter.not_end(); ++line_iter)
				{
					auto entry_iter	= line_iter.next();
					auto & entry	= parsed.toc.entry_at(entry_iter);

					printf(" ");
					print_entry_info(entry, spacing);
				}

				printf("\n");
			}

			void print_hierarchy(gckey_type spacing = _zero)
			{
				printf("\n");

				for (auto origin = parsed.toc.hierarchy.cguide(); origin.not_end(); ++origin)
				{
					auto line_iter	= origin.next();
					auto & line	= parsed.toc.line_at(line_iter);

					print_line_info(line, spacing);

					print_entries(line_iter, spacing);
				}
			}

			void print_tree(gckey_type spacing = _zero)
			{
				print_args(spacing);
				print_hierarchy(spacing);
			}

		//	void print_link(gckey_type spacing = _zero)
		//	{
		//		auto & entry_level = parsed.toc.entry_level;

		//		for (auto k = link.cbegin(); k != link.cend(); ++k)
		//		{
		//			for (auto e = k->cbegin(); e != k->cend(); ++e)
		//			{
		//				printf(" ");
		//				print_entry_info(entry_level[*e], spacing);
		//			}

		//			printf("\n");
		//		}

		//		printf("\n");
		//	}

			void print_morph(gckey_type spacing = _zero)
			{
			//	auto & morph = parsed.morph_level;

			//	printf("\n");

			//	for (auto k = morph.cbegin(); k != morph.cend(); ++k)
			//		print_morph_info(*k, spacing);

			//	printf("\n");
			}

			void print_cycle(gckey_type spacing = _zero)
			{
			//	auto & cycle = parsed.cycle_level;

			//	printf("\n");

			//	for (auto k = cycle.cbegin(); k != cycle.cend(); ++k)
			//		print_cycle_info(*k, spacing);

			//	printf("\n");
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// targeted:

/***********************************************************************************************************************/

// machine:

	struct machine_printer
	{
		using MN = machine::AN;
		using MT = machine::AT;

		constexpr static auto offset(gcindex_type num)
		{
			if      (num <  10) return "  ";
			else if (num < 100) return  " ";
			else                return   "";
		}

		constexpr static auto name(gcindex_type name)
		{
			auto str = "unknown      ";

			switch (name)
			{
				case MN::id        : { str = "MN::id       " ; break; }
				case MN::halt      : { str = "MN::halt     " ; break; }
				case MN::jump      : { str = "MN::jump     " ; break; }
				case MN::select    : { str = "MN::select   " ; break; }
				case MN::reselect  : { str = "MN::reselect " ; break; }
				case MN::right     : { str = "MN::right    " ; break; }
				case MN::replace   : { str = "MN::replace  " ; break; }
				case MN::pad       : { str = "MN::pad      " ; break; }
				case MN::call      : { str = "MN::call     " ; break; }
				case MN::recall    : { str = "MN::recall   " ; break; }
				case MN::dimension : { str = "MN::dimension" ; break; }
			}

			return str;
		}

		constexpr static auto note(gcindex_type note)
		{
			auto str = "unknown      ";

			switch (note)
			{
				case MT::id        : { str = "MT::id       " ; break; }
				case MT::first     : { str = "MT::first    " ; break; }
				case MT::go_to     : { str = "MT::go_to    " ; break; }
				case MT::branch    : { str = "MT::branch   " ; break; }
				case MT::segment   : { str = "MT::segment  " ; break; }
				case MT::void_f    : { str = "MT::void_f   " ; break; }
				case MT::dimension : { str = "MT::dimension" ; break; }
			}

			return str;
		}
	};

/***********************************************************************************************************************/

// interface:

/*
	template<auto callable_source>
	struct chord_assembly_targeted_printer
	{
		private:

			constexpr static auto static_pair	= _static_callable_<callable_source>;
			constexpr static auto static_src	= _static_car_<static_pair>;
			constexpr static auto static_targeted	= U_store_T<chord::T_chord_assembly_targeted<static_src>>;

			constexpr static auto & targeted	= member_value_U<static_targeted>;
			constexpr static auto & contr		= targeted.contr;

			using MI				= machine::AI;

			template<typename InstrType>
			void print_instr(const InstrType & instr, gcindex_type line)
			{
				auto offset   = machine_printer::offset(line);

				auto name     = instr[MI::name];
				auto name_str = machine_printer::name(name);

				auto note     = instr[MI::note];
				auto note_str = machine_printer::note(note);

				printf("%s%hu|    %s    %s    ", offset, line, name_str, note_str);

				if (instr.size() == targeted.instr_length) printf("%d", instr[MI::pos]);

				printf("\n");
			}

		public:

			chord_assembly_targeted_printer() { }

			void print_controller()
			{
				for (auto k = contr.cbegin(); k != contr.cend(); ++k)
					print_instr(*k, contr.left_size(k));
			}
	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// metapiler:

/***********************************************************************************************************************/

// parameter:

/*
	struct parameter_printer
	{
		template<auto f>
		constexpr static auto op_name()
		{
			if      constexpr (eval<_same_, f, _id_                    >) return "_id_                   ";
			else if constexpr (eval<_same_, f, _nop_                   >) return "_nop_                  ";
			else if constexpr (eval<_same_, f, _upshift_               >) return "_upshift_              ";
			else if constexpr (eval<_same_, f, _downshift_             >) return "_downshift_            ";

			else if constexpr (eval<_same_, f, _appoint_               >) return "_appoint_              ";
			else if constexpr (eval<_same_, f, _dereference_           >) return "_dereference_          ";
			else if constexpr (eval<_same_, f, _to_bool_               >) return "_to_bool_              ";

			else if constexpr (eval<_same_, f, _not_                   >) return "_not_                  ";
			else if constexpr (eval<_same_, f, _and_                   >) return "_and_                  ";
			else if constexpr (eval<_same_, f, _or_                    >) return "_or_                   ";
			else if constexpr (eval<_same_, f, _implies_               >) return "_implies_              ";
			else if constexpr (eval<_same_, f, _equivalent_            >) return "_equivalent_           ";

			else if constexpr (eval<_same_, f, _equal_                 >) return "_equal_                ";
			else if constexpr (eval<_same_, f, _is_zero_               >) return "_is_zero_              ";
			else if constexpr (eval<_same_, f, _not_equal_             >) return "_not_equal_            ";
			else if constexpr (eval<_same_, f, _less_than_             >) return "_less_than_            ";
			else if constexpr (eval<_same_, f, _less_than_or_equal_    >) return "_less_than_or_equal_   ";
			else if constexpr (eval<_same_, f, _greater_than_          >) return "_greater_than_         ";
			else if constexpr (eval<_same_, f, _greater_than_or_equal_ >) return "_greater_than_or_equal_";

			else if constexpr (eval<_same_, f, _add_                   >) return "_add_                  ";
			else if constexpr (eval<_same_, f, _subtract_              >) return "_subtract_             ";
			else if constexpr (eval<_same_, f, _multiply_              >) return "_multiply_             ";
			else if constexpr (eval<_same_, f, _divide_                >) return "_divide_               ";
			else if constexpr (eval<_same_, f, _modulo_                >) return "_modulo_               ";

			else if constexpr (eval<_same_, f, _increment_<1>          >) return "_increment_            ";
			else if constexpr (eval<_same_, f, _increment_<-1>         >) return "_decrement_            ";

			else if constexpr (eval<_same_, f, _is_array_              >) return "_is_array_             ";
			else if constexpr (eval<_same_, f, _array_type_            >) return "_array_type_           ";
			else if constexpr (eval<_same_, f, _array_size_            >) return "_array_size_           ";
			else if constexpr (eval<_same_, f, _array_begin_           >) return "_array_begin_          ";
			else if constexpr (eval<_same_, f, _array_last_            >) return "_array_last_           ";
			else if constexpr (eval<_same_, f, _array_end_             >) return "_array_end_            ";
			else if constexpr (eval<_same_, f, _log_floor_             >) return "_log_floor_            ";

			else if constexpr (eval<_same_, f, _subarray_size_         >) return "_subarray_size_        ";

			else if constexpr (eval<_same_, f, _is_sequence_           >) return "_is_sequence_          ";
			else if constexpr (eval<_same_, f, _sequence_type_         >) return "_sequence_type_        ";
			else if constexpr (eval<_same_, f, _sequence_length_       >) return "_sequence_length_      ";

			else                                                          return "(?)                    ";
		}
	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace generator

