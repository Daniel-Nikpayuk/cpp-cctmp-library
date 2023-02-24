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

// optimizer:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// linker:

/***********************************************************************************************************************/

// target:

	template<auto SourceCallable>
	struct GenericAssemblyTarget
	{
		nik_ces auto pda	= T_generic_assembly_pda::template parse<SourceCallable>;
		nik_ces auto src	= pda.src;
		nik_ces auto toc	= pda.syntax;

		using Sign		= typename GenericAssemblyTA::Sign;

		nik_ces auto length	= ( 1 * src.goto_size    )
					+ ( 1 * src.branch_size  )
					+ ( 2 * src.test_size    )
					+ ( 2 * src.period_size  )
					+ ( 3 * src.return_size  ) // upper bound: (1 * size <= 3 * size)
					+ ( 4 * src.replace_size );

		using instr_type	= sequence    < gcindex_type* , length            >;
		using label_type	= sequence    < gindex_type   , src.label_size    >;
		using extension_type	= sequence    < bool          , length            >;
		using position_type	= sequence    < gindex_type   , length            >;
		using lookpos_type	= subsequence < gindex_type   , toc.lookup.size() >;
		using labpos_type	= subsequence < gindex_type   , src.depend_size   >;

		template<auto row, auto col>
		nik_ces auto adjust_index()
		{
			nik_ce auto index  = toc.lookup_entry(row, col).index;
			nik_ce auto adjset = Sign::dimension - toc.lookup_line_offset(row);

			if constexpr      (Sign::is_paste(index)  ) return _zero;
			else if constexpr (Sign::is_replace(index)) return index - adjset;
			else                                        return U_pack_Vs<row, col>;
		}

		template<auto n, auto... Is>
		nik_ces auto inner_pack(nik_avp(T_pack_Vs<Is...>*))
			{ return U_pack_Vs<adjust_index<n, Is>()...>; }

		template<auto... Is>
		nik_ces auto size_pack(nik_avp(T_pack_Vs<Is...>*))
			{ return U_pack_Vs<eval<_par_segment_, toc.lookup_line_size(Is), toc.lookup_line_shift(Is)>...>; }

		template<auto... Is, auto... Js>
		nik_ces auto to_pack(nik_avp(T_pack_Vs<Is...>*), nik_avp(T_pack_Vs<Js...>*))
			{ return U_pack_Vs<inner_pack<Is>(Js)...>; }

		nik_ces auto toc_lookup_to_pack()
		{
			nik_ce auto t_lookup_seg = eval<_par_segment_, toc.lookup.size()>;
			nik_ce auto size_seg     = size_pack(t_lookup_seg);

			return to_pack(t_lookup_seg, size_seg);
		}

		nik_ces auto lookup = toc_lookup_to_pack();

		instr_type instr;
		label_type label;
		extension_type extension;
		position_type position;
		lookpos_type lookpos;
		labpos_type labpos;

		nik_ce GenericAssemblyTarget() : instr{}, label{}, extension{}, position{}, lookpos{}, labpos{}

			{ translate(); resolve(); }

		nik_ce void translate()
		{
			// can check if function calls are redundant and refactor,
			// but it also might not be necessary if the compiler optimizes.

			for (auto k = toc.page.begin(); k != toc.page.end(); ++k)
			{
				switch (k->kind)
				{
					case Context::label:
					{
						label.array[k->begin()->index] = instr.size();

						break;
					}
					case Context::test:
					{
						*(instr.value++)    = instruction< MN::select , MT::id >;
						*(instr.value++)    = instruction< MN::call   , MT::id >;

						*extension.value    = true;
						extension.value    += 2;

						if (k->has_lookup) *(lookpos.locus++) = position.value;

						position.value     += 2;

						break;
					}
					case Context::apply:
					{
						*(instr.value++) = instruction< MN::select , MT::id >;

						if (k->has_offset) *(instr.value++) = instruction< MN::recall , MT::id >;
						else               *(instr.value++) = instruction< MN::call   , MT::id >;

						*extension.value    = true;
						extension.value    += 2;

						if (k->has_lookup) *(lookpos.locus++) = position.value;

						position.value     += 2;

						auto index = k->begin()->index;

						if (Sign::is_replace(index))
						{
							*(instr.value++)  = instruction< MN::select  , MT::front >;
							*(instr.value++)  = instruction< MN::replace , MT::id    >;

							*extension.value  = true;
							extension.value  += 2;

							*position.value   = (index - Sign::dimension);
							position.value   += 2;
						}

						break;
					}
					case Context::branch:
					{
						*(instr.value++)   = instruction< MN::jump , MT::branch >;

						*extension.value   = true;
						extension.value   += 1;

						*(labpos.locus++)  = position.value;
						position.value    += 1;

						break;
					}
					case Context::go_to:
					{
						*(instr.value++)   = instruction< MN::jump , MT::go_to >;

						*extension.value   = true;
						extension.value   += 1;

						*(labpos.locus++)  = position.value;
						position.value    += 1;

						break;
					}
					case Context::re_turn:
					{
						auto index = k->begin()->index;

						if (Sign::is_lookup(index))
						{
							*(instr.value++)    = instruction< MN::select , MT::id >;
							*(instr.value++)    = instruction< MN::call   , MT::id >;

							*extension.value    = true;
							extension.value    += 2;

							if (k->has_lookup) *(lookpos.locus++) = position.value;

							position.value     += 2;
						}
						else if (Sign::is_replace(index))
						{
							*(instr.value++)  = instruction< MN::select , MT::front >;
							*(instr.value++)  = instruction< MN::right  , MT::id    >;

							*extension.value  = true;
							extension.value  += 2;

							*position.value   = (index - Sign::dimension);
							position.value   += 2;
						}

						*(instr.value++) = instruction< MN::first , MT::id >;

						extension.value += 1;
						position.value  += 1;

						break;
					}
				}
			}
		}

		nik_ce void resolve()
		{
			auto num = 0;
			for (auto k = lookpos.begin(); k != lookpos.end(); ++k, ++num) **k = num;

			auto line = toc.depend.begin();
			for (auto k = labpos.begin(); k != labpos.end(); ++k, ++line)
				**k = label.array[(*line)->begin()->index];
		}
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

