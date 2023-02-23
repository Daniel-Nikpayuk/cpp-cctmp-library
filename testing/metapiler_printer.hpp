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
				case MT::value     : { str = "MT::value    " ; break; }
				case MT::value17   : { str = "MT::value17  " ; break; }
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
			nik_ces auto param  = syntax.param;

			template<typename EntryType>
			void print_entry(const EntryType & entry)
			{
				for (auto k = entry.start; k != entry.finish; ++k) printf("%c", *k);

				printf("{%d} ", (int) entry.index);
			}

			template<typename LineType>
			void print_line(const LineType & line)
			{
				printf("| %hu | ", line.offset);

				for (auto k = line.begin(); k != line.end(); ++k) print_entry(*k);

				printf("\n");
			}

		public:

			syntax_printer() { }

			void print_page  () { for (auto k = page.begin(); k != page.end(); ++k) print_line(*k); }
			void print_param () { for (auto k = param.begin(); k != param.end(); ++k) print_line(**k); }
	};

/***********************************************************************************************************************/

	template<auto SourceCallable>
	struct target_printer
	{
		private:

			nik_ces auto target    = T_generic_assembly_target<SourceCallable>::value;
			nik_ces auto toc       = target.toc;
			nik_ces auto contr     = target.instr;
			nik_ces auto extension = target.extension;
			nik_ces auto position  = target.position;
			nik_ces auto lookup    = target.lookup;

			template<typename Instr>
			void print_instr(const Instr *instr, gcindex_type pos)
			{
				auto offset   = machine_printer::offset(pos);

				auto name     = instr[MI::name];
				auto name_str = machine_printer::name(name);

				auto note     = instr[MI::note];
				auto note_str = machine_printer::note(note);

				auto ext      = extension.array[pos];
				auto val      = position.array[pos];

				printf("%s%hu    %s    %s    ", offset, pos, name_str, note_str);

				if (ext) printf("%d", val);

				printf("\n");
			}

			template<auto row, auto col>
			void print_row_col(nik_avp(T_pack_Vs<row, col>*))
			{
				nik_ce auto offset = toc.param_offset(row);

				printf("| %hu | <%hu, %hu> ", offset, (gindex_type) row, (gindex_type) col);
			}

			template<auto f, auto... Vs>
			void print_inner_lookup(nik_avp(T_pack_Vs<f, Vs...>*))
			{
				print_row_col(f);
				(printf("%hu ", (gindex_type) Vs), ...);
				printf("\n");
			}

			template<auto... Vs>
			void unpack_lookup(nik_avp(T_pack_Vs<Vs...>*)) { (print_inner_lookup(Vs), ...); }

		public:

			target_printer() { }

			void print_controller()
			{
				auto pos = 0;

				for (auto k = contr.begin(); k != contr.end(); ++k, ++pos) print_instr(*k, pos);
			}

			void print_lookup() { unpack_lookup(lookup); }
	};

/***********************************************************************************************************************/

	template<auto SourceCallable>
	struct metapiler_printer
	{
		private:

			nik_ces auto metapiler = T_generic_assembly_metapiler<SourceCallable>{};
			nik_ces auto contr     = metapiler.contr;
			nik_ces auto lookup    = metapiler.template lookup<false>;

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

			template<auto f, auto... Vs>
			void print_inner_lookup(nik_avp(T_pack_Vs<f, Vs...>*))
			{
				printf("%s ", parameter_printer::template op_name<f>());
				(printf("%hu ", Vs), ...);
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

