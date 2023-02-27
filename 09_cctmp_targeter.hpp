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

// targeter:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// target:

	template<auto SourceCallable>
	struct GenericAssemblyTarget
	{
		nik_ces auto pda = T_generic_assembly_pda::template parse<SourceCallable>;
		nik_ces auto src = pda.src;
		nik_ces auto toc = pda.syntax;

		struct Instr { enum : gkey_type { name = 0, note  , pos }; };
		struct Mark  { enum : gkey_type { none = 0, value       }; };

		nik_ces auto instr_length	= _three;
		nik_ces auto length		= ( 1 * src.goto_size    )
						+ ( 1 * src.branch_size  )
						+ ( 2 * src.test_size    )
						+ ( 2 * src.period_size  )
						+ ( 3 * src.return_size  ) // upper bound: (1 * size <= 3 * size)
						+ ( 4 * src.replace_size );

		using label_type		= sequence    < gindex_type , src.label_size    >;
		using instr_type		= sequence    < gindex_type , instr_length      >;
		using contr_type		= sequence    < instr_type  , length            >;
		using contr_lookup_type		= subsequence < instr_type  , toc.lookup.size() >;
		using contr_jump_type		= subsequence < instr_type  , src.depend_size   >;
		using cline_type		= typename decltype(toc.page)::cline_type;

		label_type label;
		contr_type contr;
		contr_lookup_type contr_lookup;
		contr_jump_type contr_jump;

		nik_ce GenericAssemblyTarget() :

			label{}, contr{}, contr_lookup{}, contr_jump{}

			{ translate(); resolve_lookup(); resolve_jump(); }

		nik_ce void translate()
		{
			// can check if function calls are redundant and refactor,
			// but it also might not be necessary if the compiler optimizes.

			for (auto k = toc.page.begin(); k != toc.page.end(); ++k)
			{
				switch (k->kind)
				{
					case Context::label   : { add_label_instr  (*k); break; }
					case Context::test    : { add_test_instr   (*k); break; }
					case Context::apply   : { add_apply_instr  (*k); break; }
					case Context::branch  : { add_branch_instr (*k); break; }
					case Context::go_to   : { add_goto_instr   (*k); break; }
					case Context::re_turn : { add_return_instr (*k); break; }
				}
			}
		}

		nik_ce auto call_name      (cline_type & l) const { return l.has_paste ? MN::recall : MN::call; }
		nik_ce auto first_sign     (cline_type & l) const { return l.begin()->sign; }
		nik_ce auto first_index    (cline_type & l) const { return l.begin()->index; }
		nik_ce auto set_label_line (cline_type & l)       { label.array[first_index(l)] = contr.size(); }

		nik_ce void increment_instr () { ++contr.value; }
		nik_ce void increment_value () { ++contr.value->value; }

		nik_ce void increment_value (gcindex_type value) { *(contr.value->value++) = value; }
		nik_ce void set_instr_pos   (gcindex_type value) { contr.value->array[Instr::pos] = value; }

		// add:

			nik_ce void add_instr(gckey_type name, gckey_type note, gckey_type m = Mark::none)
			{
				increment_value(name);
				increment_value(note);
				if (m == Mark::value) increment_value();

				increment_instr();
			}

			nik_ce void add_lookup () { *(contr_lookup.locus++) = contr.value; }
			nik_ce void add_jump   () { *(contr_jump.locus++  ) = contr.value; }

			nik_ce void add_label_instr(cline_type & l) { set_label_line(l); }

			nik_ce void add_test_instr(cline_type & l)
			{
				if (l.has_lookup) add_lookup();

				add_instr(MN::select, MT::id, Mark::value);
				add_instr(call_name(l), MT::id);
			}

			nik_ce void add_apply_instr(cline_type & l)
			{
				if (l.has_lookup) add_lookup();

				add_instr(MN::select, MT::id, Mark::value);
				add_instr(call_name(l), MT::id);

				auto sign = first_sign(l);

				if (Sign::is_arg(sign))
				{
					set_instr_pos(first_index(l));

					add_instr(MN::select, MT::front, Mark::value);
					add_instr(MN::replace, MT::id);
				}
				else if (Sign::is_var(sign))
				{
					add_instr(MN::rotate, MT::id);
				}
			}

			nik_ce void add_branch_instr(cline_type & l)
			{
				add_jump();

				add_instr(MN::jump, MT::branch, Mark::value);
			}

			nik_ce void add_goto_instr(cline_type & l)
			{
				add_jump();

				add_instr(MN::jump, MT::go_to, Mark::value);
			}

			nik_ce void add_return_instr(cline_type & l)
			{
				auto sign = first_sign(l);

				if (Sign::is_arg(sign))
				{
					set_instr_pos(first_index(l));

					add_instr(MN::select, MT::front, Mark::value);
					add_instr(MN::right, MT::id);
				}
				else if (Sign::is_lookup(sign))
				{
					add_lookup();

					add_instr(MN::select, MT::id, Mark::value);
					add_instr(MN::call, MT::id);
				}

				add_instr(MN::first , MT::id);
			}

		// resolve:

			nik_ce void resolve_lookup()
			{
				auto num = 0;
				for (auto k = contr_lookup.begin(); k != contr_lookup.end(); ++k, ++num)
					(*k)->array[Instr::pos] = num;
			}

			nik_ce void resolve_jump()
			{
				auto line = toc.depend.begin();
				for (auto k = contr_jump.begin(); k != contr_jump.end(); ++k, ++line)
					(*k)->array[Instr::pos] = label.array[(*line)->begin()->index];
			}

		// instr:

			nik_ce auto instr_size(gindex_type n) const
				{ return contr.array[n].size(); }

			nik_ce auto instr_at(gindex_type m, gindex_type n) const
				{ return contr.array[m].array[n]; }
	};

/***********************************************************************************************************************/

// automaton:

	template<auto SourceCallable>
	struct T_generic_assembly_target
	{
		nik_ces auto value = GenericAssemblyTarget<SourceCallable>{};
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tail call:

/***********************************************************************************************************************/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

