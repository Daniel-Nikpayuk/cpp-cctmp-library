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
		nik_ces auto page	= toc.page;
		nik_ces auto depend	= toc.depend;
		nik_ces auto param	= toc.param;

		nik_ces auto offset	= _five;
		nik_ces auto length	= ( 1 * src.goto_size    )
					+ ( 1 * src.branch_size  )
					+ ( 2 * src.test_size    )
					+ ( 2 * src.period_size  )
					+ ( 3 * src.return_size  ) // upper bound: (1 * size <= 3 * size)
					+ ( 4 * src.replace_size );

		using instr_type	= sequence    < gcindex_type* , length          >;
		using label_type	= sequence    < gindex_type   , src.label_size  >;
		using extension_type	= sequence    < bool          , length          >;
		using position_type	= sequence    < gindex_type   , length          >;
		using lookpos_type	= subsequence < gindex_type   , src.param_size  >;
		using labpos_type	= subsequence < gindex_type   , src.depend_size >;

		template<auto row, auto col>
		nik_ces auto adjust_index()
		{
			nik_ce auto index       = toc.param_at(row, col).index;
			nik_ce auto line_offset = toc.offset_at(row);
			nik_ce auto adjset      = offset - line_offset;

			if constexpr      (index == _one  ) return U_pack_Vs<row, col>;
			else if constexpr (index == _three) return _zero;
			else                                return index - adjset;
		}

		template<auto n, auto... Is>
		nik_ces auto inner_pack(nik_avp(T_pack_Vs<Is...>*))
			{ return U_pack_Vs<adjust_index<n, Is>()...>; }

		template<auto... Is>
		nik_ces auto size_pack(nik_avp(T_pack_Vs<Is...>*))
			{ return U_pack_Vs<eval<_par_segment_, toc.param_size(Is) - 1, _one>...>; }

		template<auto... Is, auto... Js>
		nik_ces auto to_pack(nik_avp(T_pack_Vs<Is...>*), nik_avp(T_pack_Vs<Js...>*))
			{ return U_pack_Vs<inner_pack<Is>(Js)...>; }

		nik_ces auto param_to_pack()
		{
			nik_ce auto param_seg = eval<_par_segment_, param.size()>;
			nik_ce auto size_seg  = size_pack(param_seg);

			return to_pack(param_seg, size_seg);
		}

		nik_ces auto lookup = param_to_pack();

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

			for (auto k = page.begin(); k != page.end(); ++k)
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
						*(instr.value++)    = instruction< AN::select , AT::id >;
						*(instr.value++)    = instruction< AN::call   , AT::id >;

						*extension.value    = true;
						extension.value    += 2;

						*(lookpos.locus++)  = position.value;
						position.value     += 2;

						break;
					}
					case Context::apply:
					{
						*(instr.value++) = instruction< AN::select , AT::id >;

						if (k->offset == 1) *(instr.value++) = instruction< AN::recall , AT::id >;
						else                *(instr.value++) = instruction< AN::call   , AT::id >;

						*extension.value    = true;
						extension.value    += 2;

						*(lookpos.locus++)  = position.value;
						position.value     += 2;

						auto index = k->begin()->index;

						if (index >= offset) // replace:
						{
							*(instr.value++)  = instruction< AN::select  , AT::front >;
							*(instr.value++)  = instruction< AN::replace , AT::id    >;

							*extension.value  = true;
							extension.value  += 2;

							*position.value   = (index - offset);
							position.value   += 2;
						}

						break;
					}
					case Context::branch:
					{
						*(instr.value++)   = instruction< AN::jump , AT::branch >;

						*extension.value   = true;
						extension.value   += 1;

						*(labpos.locus++)  = position.value;
						position.value    += 1;

						break;
					}
					case Context::go_to:
					{
						*(instr.value++)   = instruction< AN::jump , AT::go_to >;

						*extension.value   = true;
						extension.value   += 1;

						*(labpos.locus++)  = position.value;
						position.value    += 1;

						break;
					}
					case Context::re_turn:
					{
						auto index = k->begin()->index;

						if (index == _one) // lookup:
						{
							*(instr.value++)    = instruction< AN::select , AT::id    >;
							*(instr.value++)    = instruction< AN::call   , AT::value >;

							*extension.value    = true;
							extension.value    += 2;

							*(lookpos.locus++)  = position.value;
							position.value     += 2;
						}
						else if (index >= offset) // replace:
						{
							*(instr.value++)  = instruction< AN::select , AT::front >;
							*(instr.value++)  = instruction< AN::right  , AT::id    >;

							*extension.value  = true;
							extension.value  += 2;

							*position.value   = (index - offset);
							position.value   += 2;
						}

						*(instr.value++) = instruction< AN::first , AT::id >;

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

			auto line = depend.begin();
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

