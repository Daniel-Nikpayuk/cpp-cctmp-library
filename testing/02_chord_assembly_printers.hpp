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

// chord assembly printers:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// chord assembly:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parsed:

/***********************************************************************************************************************/

// interface:

	template<auto static_grammar, auto callable_source>
	struct chord_assembly_parsed_printer
	{
		private:

			using T_grammar					= T_store_U<static_grammar>;
			using Token					= typename T_grammar::Token;
			using strlit_type				= string_literal<>;
			using cstrlit_type				= strlit_type const;
			using cstrlit_ref				= cstrlit_type&;

			template<auto ss, auto sg>
			constexpr static auto U_static_pg_parsed	= U_store_T<T_parser_generator_parsed<ss, sg>>;

			constexpr static auto static_pg_src		= _static_callable_<T_grammar::source>;
			constexpr static auto static_pg_scanned		= U_store_T<T_parser_generator_scanned<static_pg_src>>;
			constexpr static auto static_pg_parsed		= U_static_pg_parsed<static_pg_scanned, static_grammar>;

			//

			template<auto st, auto ss>
			constexpr static auto U_static_parsed		= U_store_T<chord::T_chord_assembly_parsed<st, ss>>;

			constexpr static auto static_src		= _static_callable_<callable_source>;
			constexpr static auto static_scanned		= U_store_T<chord::T_chord_assembly_scanned<static_src>>;
			constexpr static auto static_parsed		= U_static_parsed<static_pg_parsed, static_scanned>;

			using parsed_type				= member_type_U<static_parsed>;
			using cnavigator_type				= typename parsed_type::cnavigator_type;
			using pair_type					= pair<bool, gindex_type>;
			using cpair_type				= pair_type const;
			using cpair_ref					= cpair_type&;

			constexpr static auto & parsed			= member_value_U<static_parsed>;
			constexpr static auto & lookup 			= parsed.lookup_level;

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
					case chord::Sign::na      : { str = " "    ; sub = 1; break; }
					case chord::Sign::carg    : { str = "carg" ; sub = 4; break; }
					case chord::Sign::marg    : { str = "marg" ; sub = 4; break; }
					case chord::Sign::copy    : { str = "."    ; sub = 1; break; }
					case chord::Sign::paste   : { str = "_"    ; sub = 1; break; }
					case chord::Sign::recurse : { str = "rec"  ; sub = 3; break; }
					case chord::Sign::label   : { str = "l"    ; sub = 1; break; }
					case chord::Sign::jump    : { str = "jump" ; sub = 4; break; }
					case chord::Sign::env     : { str = "env"  ; sub = 3; break; }

					case chord::Sign::repeat : { str = "chord" ; sub = 5; break; }
					case chord::Sign::fold   : { str = "chord" ; sub = 5; break; }
					case chord::Sign::find   : { str = "chord" ; sub = 5; break; }
					case chord::Sign::sift   : { str = "chord" ; sub = 5; break; }
					case chord::Sign::map    : { str = "chord" ; sub = 5; break; }
					case chord::Sign::zip    : { str = "chord" ; sub = 5; break; }
					case chord::Sign::fasten : { str = "chord" ; sub = 5; break; }
					case chord::Sign::glide  : { str = "chord" ; sub = 5; break; }

					case chord::Sign::dimension : { str = "dim" ; sub = 3; break; }
				}

				auto size = sub + entry.size();
				if (spacing > size) generic_printer::print_spacing(spacing - size);

				generic_printer::print_string(entry);

				auto print_right  = chord::Sign::is_carg  (entry.sign)
						 || chord::Sign::is_marg  (entry.sign)
						 || chord::Sign::is_paste (entry.sign)
						 || chord::Sign::is_label (entry.sign)
						 || chord::Sign::is_jump  (entry.sign)

						 || chord::Sign::is_repeat (entry.sign)
						 || chord::Sign::is_fold   (entry.sign)
						 || chord::Sign::is_find   (entry.sign)
						 || chord::Sign::is_sift   (entry.sign)
						 || chord::Sign::is_map    (entry.sign)
						 || chord::Sign::is_zip    (entry.sign)
						 || chord::Sign::is_fasten (entry.sign)
						 || chord::Sign::is_glide  (entry.sign);

				if (print_right) printf("{%s|%d}", str, (int) entry.index);
				else             printf("{%s}", str);
			}

			template<typename LineType>
			void print_line_info(const LineType & line, gckey_type spacing)
			{
				auto str = "";

				switch (line.kind)
				{
					case chord::Context::none    : { str = "      "; break; }
					case chord::Context::assign  : { str = "assign"; break; }
					case chord::Context::apply   : { str = "apply "; break; }
					case chord::Context::test    : { str = "test  "; break; }
					case chord::Context::label   : { str = "label "; break; }
					case chord::Context::branch  : { str = "branch"; break; }
					case chord::Context::go_to   : { str = "goto  "; break; }
					case chord::Context::re_turn : { str = "return"; break; }
				}

				auto str0 = line.has_lookup ? "lookup": "      ";
				auto str1 = line.has_paste  ? "paste" : "     " ;
				auto str2 = line.has_void   ? "void"  : "    "  ;

				printf("|%s|%s|%s|%s| ", str, str0, str1, str2);
			}

			template<typename FuncType>
			void print_chord_function(const FuncType & func, gckey_type spacing)
			{
				for (auto k = func.cbegin(); k != func.cend(); ++k)
				{
					generic_printer::print_spacing(1);
					generic_printer::print_string(*k);
				}
			}

			template<typename ChordType>
			void print_chord_parameter(const ChordType & chord, gckey_type spacing)
			{
				auto & parameter = chord.parameter;

				for (auto k = parameter.cbegin(); k != parameter.cend(); ++k)
				{
					printf(" |");
					print_chord_function(*k, spacing);
				}
			}

			template<typename ChordType>
			void print_chord_iterator(const ChordType & chord, gckey_type spacing)
			{
				auto & iterator = chord.iterator;

				for (auto k = iterator.cbegin(); k != iterator.cend(); ++k)
					print_chord_function(*k, spacing);
			}

			template<typename ChordType>
			void print_chord_interval(const ChordType & chord, gckey_type spacing)
			{
				auto & interval = chord.interval;

				for (auto k = interval.cbegin(); k != interval.cend(); ++k)
				{
					auto lstr = (k->left  == chord::Ival::closed) ? '[' : '(';
					auto rstr = (k->right == chord::Ival::closed) ? ']' : ')';

					printf(" %c", lstr);
					print_chord_iterator(chord, spacing);
					printf(" %c ", rstr);
				}
			}

			template<typename ChordType>
			void print_chord_info(const ChordType & chord, gckey_type spacing)
			{
				auto str = "";
				auto sub =  0;

				switch (chord.token)
				{
					case Token::repeat : { str = "repeat" ; sub =  6; break; }
					case Token::fold   : { str = "fold"   ; sub =  4; break; }
					case Token::find   : { str = "find"   ; sub = 10; break; }
					case Token::sift   : { str = "sift"   ; sub =  8; break; }
					case Token::map    : { str = "map"    ; sub =  3; break; }
					case Token::zip    : { str = "zip"    ; sub =  3; break; }
					case Token::fasten : { str = "fasten" ; sub =  6; break; }
					case Token::glide  : { str = "glide"  ; sub =  5; break; }
				}

				if (spacing > sub) generic_printer::print_spacing(spacing - sub);
				printf("%s", str);

				print_chord_parameter (chord, spacing);
				print_chord_interval  (chord, spacing);
			}

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
					auto & entry	= parsed.entry_at(entry_iter);

					printf(" ");
					print_entry_info(entry, spacing);
				}

				printf("\n");
			}

			void print_hierarchy(gckey_type spacing = _zero)
			{
				printf("\n");

				for (auto origin = parsed.hierarchy.cguide(); origin.not_end(); ++origin)
				{
					auto line_iter	= origin.next();
					auto & line	= parsed.line_at(line_iter);

					print_line_info(line, spacing);

					print_entries(line_iter, spacing);
				}
			}

			void print_tree(gckey_type spacing = _zero)
			{
				print_args(spacing);
				print_hierarchy(spacing);
			}

			void print_lookup(gckey_type spacing = _zero)
			{
				auto & entry_level = parsed.entry_level;

				for (auto k = lookup.cbegin(); k != lookup.cend(); ++k)
				{
					for (auto e = k->cbegin(); e != k->cend(); ++e)
						print_entry_info(entry_level[*e], spacing);

					printf("\n");
				}

				printf("\n");
			}

			void print_chord(gckey_type spacing = _zero)
			{
				auto & chord = parsed.chord_level;

				printf("\n");

				for (auto k = chord.cbegin(); k != chord.cend(); ++k)
					print_chord_info(*k, spacing);

				printf("\n");
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// targeted:

/***********************************************************************************************************************/

// machine:

	struct machine_printer
	{
		using MN = chord::MN;
		using MT = chord::MT;

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
				case MN::first     : { str = "MN::first    " ; break; }
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
				case MT::front     : { str = "MT::front    " ; break; }
				case MT::go_to     : { str = "MT::go_to    " ; break; }
				case MT::branch    : { str = "MT::branch   " ; break; }
				case MT::segment   : { str = "MT::segment  " ; break; }
				case MT::pair      : { str = "MT::pair     " ; break; }
				case MT::value     : { str = "MT::value    " ; break; }
				case MT::side      : { str = "MT::side     " ; break; }
				case MT::void_f    : { str = "MT::void_f   " ; break; }
				case MT::dimension : { str = "MT::dimension" ; break; }
			}

			return str;
		}
	};

/***********************************************************************************************************************/

// interface:

	template<auto callable_source>
	struct chord_assembly_targeted_printer
	{
		private:

			constexpr static auto static_src	= _static_callable_<callable_source>;
			constexpr static auto static_scanned	= U_store_T<chord::T_chord_assembly_scanned<static_src>>;
			constexpr static auto static_targeted	= U_store_T<chord::T_chord_assembly_targeted<static_scanned>>;

			constexpr static auto & targeted	= member_value_U<static_targeted>;
			constexpr static auto & contr		= targeted.contr;

			using MI				= chord::MI;

			template<typename InstrType>
			void print_instr(const InstrType & instr, gcindex_type line)
			{
				auto offset   = machine_printer::offset(line);

				auto name     = instr[MI::name];
				auto name_str = machine_printer::name(name);

				auto note     = instr[MI::note];
				auto note_str = machine_printer::note(note);

				auto size     = instr.size();
				auto value    = instr[MI::pos];

				printf("%s%hu|    %s    %s    ", offset, line, name_str, note_str);

				if (size == targeted.instr_length) printf("%d", value);

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

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// metapiler:

/***********************************************************************************************************************/

// parameter:

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
			else if constexpr (eval<_same_, f, _array_length_          >) return "_array_length_         ";
			else if constexpr (eval<_same_, f, _array_begin_           >) return "_array_begin_          ";
			else if constexpr (eval<_same_, f, _array_last_            >) return "_array_last_           ";
			else if constexpr (eval<_same_, f, _array_end_             >) return "_array_end_            ";
			else if constexpr (eval<_same_, f, _log_floor_             >) return "_log_floor_            ";

			else if constexpr (eval<_same_, f, _subarray_length_       >) return "_subarray_length_      ";

			else if constexpr (eval<_same_, f, _is_sequence_           >) return "_is_sequence_          ";
			else if constexpr (eval<_same_, f, _sequence_type_         >) return "_sequence_type_        ";
			else if constexpr (eval<_same_, f, _sequence_length_       >) return "_sequence_length_      ";

			else                                                          return "(?)                    ";
		}
	};

/***********************************************************************************************************************/

// interface:

	template<auto callable_source, auto... Frames>
	struct chord_assembly_metapiler_printer
	{
		private:

			constexpr static auto env	= U_pack_Vs<Frames...>;
			constexpr static auto metapiler	= chord::T_chord_assembly_metapiler<callable_source, env>{};
			constexpr static auto lookup	= metapiler.template resolve_lookup<false>;

			void print_f_pack_value(gcindex_type val) { printf("%hu ", val); }

			template<auto V>
			void print_f_pack_value(void(*)(T_pack_Vs<V>*)) { printf("(%hu) ", V); }

			template<typename T>
			void print_f_pack_value(T) { printf("(?) "); }

			template<auto f, auto... Vs>
			void print_f_pack(void(*)(T_pack_Vs<f, Vs...>*))
			{
				printf("%s ", parameter_printer::template op_name<f>());
				(print_f_pack_value(Vs), ...);
			}

			template<auto V>
			void print_t_pack_value()
			{
				if constexpr (eval<_same_, V, _read_only_>) printf("(ro) ");
				else                                        printf("(rw) ");
			}

			template<auto... Vs>
			void print_t_pack(void(*)(T_pack_Vs<Vs...>*))
			{
				(print_t_pack_value<Vs>(), ...);
			}

			template<auto f_pack, auto t_pack>
			void print_pair_lookup(void(*)(T_pack_Vs<f_pack, t_pack>*))
			{
				print_f_pack(f_pack);
				printf(" -> ");
				print_t_pack(t_pack);
				printf("\n");
			}

			template<auto... Vs>
			void unpack_lookup(void(*)(T_pack_Vs<Vs...>*)) { (print_pair_lookup(Vs), ...); }

		public:

			chord_assembly_metapiler_printer() { }

			void print_lookup() { unpack_lookup(lookup); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

