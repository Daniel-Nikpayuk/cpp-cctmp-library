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
					+ ( 3 * src.return_size  ) // currently only partially accurate: (times 1 or 3)
					+ ( 4 * src.replace_size );

		using instr_type	= sequence    < gcindex_type* , length          >;
		using label_type	= sequence    < gindex_type   , src.label_size  >;
		using position_type	= sequence    < gindex_type   , length          >;
		using lookpos_type	= subsequence < gindex_type   , src.param_size  >;
		using labpos_type	= subsequence < gindex_type   , src.depend_size >;

		nik_ces void _lookup_() { }

		nik_ces auto _is_lookup_ = _alias_<_same_, _lookup_>;

		template<auto index, bool has_paste>
		nik_ces auto adjust_index()
		{
			nik_ce auto adjset = offset + has_paste;

			if constexpr      (index == _one  ) return _lookup_;
			else if constexpr (index == _three) return _zero;
			else                                return index - adjset;
		}

		template<auto n, auto I0, auto... Is>
		nik_ces auto inner_pack(nik_avp(T_pack_Vs<I0, Is...>*)) // { first, rest... } <-- improve implementation design.
									// improve _segment_ maybe ?
			{ return U_pack_Vs<adjust_index<toc.param_at(n, Is).index, false>()...>; } // currently incomplete.

		template<auto... Is>
		nik_ces auto size_pack(nik_avp(T_pack_Vs<Is...>*))
			{ return U_pack_Vs<eval<_par_segment_, toc.param_size(Is)>...>; }

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
		position_type position;
		lookpos_type lookpos;
		labpos_type labpos;

		nik_ce GenericAssemblyTarget() : instr{}, label{}, position{}, lookpos{}, labpos{}

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
						*(instr.value++) = instruction< AN::select , AT::id >;
						*(instr.value++) = instruction< AN::call   , AT::id >;

						*(lookpos.locus++)  = position.value;
						position.value     += 2;

						break;
					}
					case Context::apply:
					{
						*(instr.value++) = instruction< AN::select , AT::id >;
						*(instr.value++) = instruction< AN::call   , AT::id >;

						*(lookpos.locus++)  = position.value;
						position.value     += 2;

						auto index = k->begin()->index;

						if (index != _two) // replace:
						{
							*(instr.value++) = instruction< AN::select  , AT::front >;
							*(instr.value++) = instruction< AN::replace , AT::id    >;

							*position.value     = (index - offset);
							position.value     += 2;
						}

						break;
					}
					case Context::branch:
					{
						*(instr.value++) = instruction< AN::jump , AT::branch >;

						*(labpos.locus++)  = position.value;
						position.value    += 1;

						break;
					}
					case Context::go_to:
					{
						*(instr.value++) = instruction< AN::jump , AT::go_to >;

						*(labpos.locus++)  = position.value;
						position.value    += 1;

						break;
					}
					case Context::re_turn:
					{
						auto index = k->begin()->index;

						if (index == _one) // lookup:
						{
							*(instr.value++) = instruction< AN::select , AT::id    >;
							*(instr.value++) = instruction< AN::call   , AT::value >;

							*(lookpos.locus++) = position.value;
						}
						else if (index != _three) // replace:
						{
							*(instr.value++) = instruction< AN::select , AT::front >;
							*(instr.value++) = instruction< AN::right  , AT::id    >;

							*position.value = (index - offset);
						}

						position.value += 2;

						*(instr.value++) = instruction< AN::first , AT::id >;

						position.value += 1;

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

#ifdef NIK_COMMENT

	// page:

				factorial{4} p{5} n{6}
				loop:{0}
		test   line -	test{2} is_zero{1} n{6}
		branch line -	done{1}
		apply  line -	p{5} multiply{1} p{5} n{6}
		apply  line -	n{6} decrement{1} n{6}
		goto   line -	loop{0}
				done:{1}
		return line -	p{5}

	// param:

				test{2} is_zero{1} n{6}
				p{5} multiply{1} p{5} n{6}
				n{6} decrement{1} n{6}

	// source:

		//		is_zero 0  Done  multiply 0 p 0  decrement 0 n 0  Loop  p 0 0 
		//		0       0  12    1        0 5 0  2         0 6 0  0     5 0 0
		// adjusted:	0       0  12    1        0 0 0  2         0 1 0  0     0 0 0

		template
		<
			auto p       = 0 , auto n        = 1  ,
			auto is_zero = 0 , auto multiply = 1  , auto decrement = 2 ,
			auto Loop    = 0 , auto Done     = 12
		>
		nik_ce auto pair_factorial_contr = controller
		<
		// Loop:
			instruction < AN::select  , AT::id     , is_zero   >, // get is_zero pack containing arg positions.
			instruction < AN::call    , AT::id                 >, // unpack and apply is_zero to args.

			instruction < AN::jump    , AT::branch , Done      >, // branch to Done label, continue otherwise.

			instruction < AN::select  , AT::id     , multiply  >, // get multiply [...].
			instruction < AN::call    , AT::id                 >, // unpack [...].
			instruction < AN::select  , AT::front  , p         >, // get left arg types before position p.
			instruction < AN::replace , AT::id                 >, // arg expand and replace at position p.

			instruction < AN::select  , AT::id     , decrement >, // get decrement [...].
			instruction < AN::call    , AT::id                 >, // unpack [...].
			instruction < AN::select  , AT::front  , n         >, // get left arg types [...].
			instruction < AN::replace , AT::id                 >, // arg expand [...].

			instruction < AN::jump    , AT::go_to  , Loop      >, // goto Loop.
		// Done:
			instruction < AN::select  , AT::front  , p         >, // get left arg types [...].
			instruction < AN::right   , AT::id                 >, // arg expand and drop the left args before p.
			instruction < AN::first   , AT::id                 >  // return the first element.
		>;

#endif

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

