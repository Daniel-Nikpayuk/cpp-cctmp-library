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

// metapiler printer:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parameter:

/***********************************************************************************************************************/

	struct parameter_printer
	{
		template<auto f>
		nik_ces auto op_name()
		{
			if      constexpr (eval<_same_, f, _id_                    >) return "_id_                   ";
			else if constexpr (eval<_same_, f, _upshift_               >) return "_upshift_              ";
			else if constexpr (eval<_same_, f, _downshift_             >) return "_downshift_            ";

			else if constexpr (eval<_same_, f, _assign_                >) return "_assign_               ";
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

			else if constexpr (eval<_same_, f, _is_sequence_           >) return "_is_sequence_          ";
			else if constexpr (eval<_same_, f, _sequence_type_         >) return "_sequence_type_        ";
			else if constexpr (eval<_same_, f, _sequence_size_         >) return "_sequence_size_        ";
			else if constexpr (eval<_same_, f, _to_sequence_           >) return "_to_sequence_          ";
			else if constexpr (eval<_same_, f, _sequence_begin_        >) return "_sequence_begin_       ";
			else if constexpr (eval<_same_, f, _sequence_last_         >) return "_sequence_last_        ";
			else if constexpr (eval<_same_, f, _sequence_end_          >) return "_sequence_end_         ";

			else if constexpr (eval<_same_, f, _is_tuple_              >) return "_is_tuple_             ";
			else if constexpr (eval<_same_, f, _tuple_type_            >) return "_tuple_type_           ";
			else if constexpr (eval<_same_, f, _tuple_size_            >) return "_tuple_size_           ";
			else if constexpr (eval<_same_, f, _to_tuple_              >) return "_to_tuple_             ";

			else                                                          return "other                  ";
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

/***********************************************************************************************************************/

	struct machine_printer
	{
		nik_ces auto offset(gcindex_type num)
		{
			if      (num <  10) return "  ";
			else if (num < 100) return  " ";
			else                return   "";
		}

		nik_ces auto name(gcindex_type name)
		{
			auto str = "unknown      ";

			switch (name)
			{
				case MN::id        : { str = "MN::id       " ; break; }
				case MN::first     : { str = "MN::first    " ; break; }
				case MN::jump      : { str = "MN::jump     " ; break; }
				case MN::select    : { str = "MN::select   " ; break; }
				case MN::right     : { str = "MN::right    " ; break; }
				case MN::replace   : { str = "MN::replace  " ; break; }
				case MN::call      : { str = "MN::call     " ; break; }
				case MN::recall    : { str = "MN::recall   " ; break; }
				case MN::loop      : { str = "MN::loop     " ; break; }
				case MN::dimension : { str = "MN::dimension" ; break; }
			}

			return str;
		}

		nik_ces auto note(gcindex_type note)
		{
			auto str = "unknown      ";

			switch (note)
			{
				case MT::id        : { str = "MT::id       " ; break; }
				case MT::front     : { str = "MT::front    " ; break; }
				case MT::go_to     : { str = "MT::go_to    " ; break; }
				case MT::branch    : { str = "MT::branch   " ; break; }
				case MT::pair      : { str = "MT::pair     " ; break; }
				case MT::side      : { str = "MT::side     " ; break; }
				case MT::dimension : { str = "MT::dimension" ; break; }
			}

			return str;
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// syntax:

/***********************************************************************************************************************/

	template<auto SourceCallable>
	struct syntax_printer
	{
		private:

			nik_ces auto src    = T_generic_assembly_pda::template parse<SourceCallable>;
			nik_ces auto syntax = src.syntax;
			nik_ces auto page   = syntax.page;
			nik_ces auto lookup = syntax.lookup;

			void print_spacing(gckey_type size) { for (auto k = 0; k != size; ++k) printf(" "); }

			template<typename StringType>
			void print_string(const StringType *start, const StringType *finish)
				{ for (auto k = start; k != finish; ++k) printf("%c", *k); }

			template<typename EntryType>
			void print_entry(const EntryType & entry, gckey_type spacing)
			{
				auto str = "";
				auto sub = _zero;

				switch (entry.sign)
				{
					case Sign::na        : { str = " "      ; sub = 1; break; }
					case Sign::arg       : { str = "arg"    ; sub = 3; break; }
					case Sign::copy      : { str = "copy"   ; sub = 4; break; }
					case Sign::paste     : { str = "paste"  ; sub = 5; break; }
					case Sign::recurse   : { str = "recurse"; sub = 7; break; }
					case Sign::label     : { str = "label"  ; sub = 5; break; }
					case Sign::jump      : { str = "jump"   ; sub = 4; break; }
					case Sign::lookup    : { str = "lookup" ; sub = 6; break; }
					case Sign::dimension : { str = "dim"    ; sub = 3; break; }
				}

				auto size = sub + (entry.finish - entry.start);
				if (spacing > size) print_spacing(spacing - size);

				print_string(entry.start, entry.finish);

				auto print_right  = Sign::is_arg   (entry.sign)
						 || Sign::is_paste (entry.sign)
						 || Sign::is_label (entry.sign)
						 || Sign::is_jump  (entry.sign);

				if (print_right) printf("{%s|%d}", str, (int) entry.index);
				else             printf("{%s| }", str);
			}

			template<typename LineType>
			void print_line(const LineType & line, gckey_type spacing)
			{
				auto l_str = line.has_lookup ? "lookup" : "      ";
				auto r_str = line.has_paste  ? "paste"  : "     " ;

				printf("|%s|%s| ", l_str, r_str);

				for (auto k = line.begin(); k != line.end(); ++k) print_entry(*k, spacing);

				printf("\n");
			}

		public:

			syntax_printer() { }

			void print_page(gckey_type spacing = _zero)
			{
				for (auto k = page.begin(); k != page.end(); ++k) print_line(*k, spacing);
			}

			void print_lookup(gckey_type spacing = _zero)
			{
				for (auto k = lookup.begin(); k != lookup.end(); ++k) print_line(**k, spacing);
			}
	};

/***********************************************************************************************************************/

	template<auto SourceCallable>
	struct target_printer
	{
		private:

			nik_ces auto target	= T_generic_assembly_target<SourceCallable>::value;
			nik_ces auto contr	= target.contr;

			using Instr		= typename decltype(target)::Instr;

			template<typename InstrType>
			void print_instr(const InstrType & instr, gcindex_type line)
			{
				auto offset   = machine_printer::offset(line);

				auto name     = instr.array[Instr::name];
				auto name_str = machine_printer::name(name);

				auto note     = instr.array[Instr::note];
				auto note_str = machine_printer::note(note);

				auto size     = instr.size();
				auto value    = instr.array[Instr::pos];

				printf("%s%hu    %s    %s    ", offset, line, name_str, note_str);

				if (size == target.instr_length) printf("%d", value);

				printf("\n");
			}

		public:

			target_printer() { }

			void print_controller()
			{
				for (auto k = contr.begin(); k != contr.end(); ++k)
					print_instr(*k, k - contr.begin());
			}
	};

/***********************************************************************************************************************/

	template<auto SourceCallable>
	struct metapiler_printer
	{
		private:

			nik_ces auto metapiler = T_generic_assembly_metapiler<SourceCallable>{};
			nik_ces auto contr     = metapiler.contr;
			nik_ces auto lookup    = metapiler.template resolve_lookup<false>;

			template<typename Instr>
			void print_instr(const Instr *instr, gcindex_type pos)
			{
				auto offset   = machine_printer::offset(pos);

				auto name     = instr[MI::name];
				auto name_str = machine_printer::name(name);

				auto note     = instr[MI::note];
				auto note_str = machine_printer::note(note);

				printf("%s%hu    %s    %s    ", offset, pos, name_str, note_str);

				if (instr[MI::size] == 3) printf("%d", instr[MI::pos]);

				printf("\n");
			}

			void print_lookup_value(gcindex_type val) { printf("%hu ", val); }

			template<auto V>
			void print_lookup_value(nik_avp(T_pack_Vs<V>*)) { printf("(%hu) ", V); }

			template<auto f, auto... Vs>
			void print_inner_lookup(nik_avp(T_pack_Vs<f, Vs...>*))
			{
				printf("%s ", parameter_printer::template op_name<f>());
				(print_lookup_value(Vs), ...);
				printf("\n");
			}

			template<auto... Vs>
			void unpack_lookup(nik_avp(T_pack_Vs<Vs...>*)) { (print_inner_lookup(Vs), ...); }

		public:

			metapiler_printer() { }

			void print_controller()
			{
				auto pos  = 0;
				auto size = contr[0][0];

				for (auto k = contr + 1; k != contr + size + 1; ++k, ++pos) print_instr(*k, pos);
			}

			void print_lookup() { unpack_lookup(lookup); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

