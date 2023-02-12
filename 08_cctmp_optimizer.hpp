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
		nik_ces auto param	= toc.param;

		nik_ces auto length	= (page.length - toc.label.size() - 1) // decrement definition and label lines.

					// decrement to prevent double counting:
	    		 		+ ( (2 - 1) * src.copy_size    )
					+ ( (4 - 1) * src.replace_size )
					+ ( (3 - 1) * src.return_size  );

		template<auto n, template<auto...> typename B, auto... Is>
		nik_ces auto inner_pack(nik_avp(B<Is...>*))
		{
			return U_pack_Vs
			<
				param.array[n]->array[Is].index...
			>;
		}

		template<template<auto...> typename B, auto... Is>
		nik_ces auto size_pack(nik_avp(B<Is...>*))
		{
			return U_pack_Vs
			<
				eval<_par_segment_, param.array[Is]->size()>...
			>;
		}

		template<auto... Is, auto... Js>
		nik_ces auto to_pack(nik_avp(T_pack_Vs<Is...>*), nik_avp(T_pack_Vs<Js...>*))
		{
			return U_pack_Vs
			<
				inner_pack<Is>(Js)...
			>;
		}

		nik_ces auto param_seg = eval<_par_segment_, param.size()>;
		nik_ces auto size_seg  = size_pack(param_seg);
		nik_ces auto lookup    = to_pack(param_seg, size_seg);

	//	template<auto n, auto... Vs, template<auto...> typename B, auto... Is>
	//	nik_ces auto to_instruction(nik_avp(B<Is...>*))
	//	{
	//		nik_ce auto k = page.begin() + n;
	//		nik_ce auto l = *k;

	//		return instruction<Vs..., l.array[Is]...>;
	//	}

		instr_type contr[length];
		cinstr_type *start;
		instr_type *line;

		gindex_type locs[length];
		gindex_type *locs_iter;
		gindex_type position;

		nik_ce GenericAssemblyTarget() :

			contr{}, start{contr}, line{contr}, locs{}, locs_iter{locs}, position{}

		{
			for (auto k = page.begin(); k != page.end(); ++k)
			{
				switch (k->kind)
				{
					case Context::test:
					{
						*(line++) = instruction< AN::select , AT::id >; // op
						*(line++) = instruction< AN::call   , AT::id >;

						*locs_iter  = get_pos(k, 1); // op
						 locs_iter += 2;

						break;
					}
					case Context::apply:
					{
						*(line++) = instruction< AN::select  , AT::id    >; // op 
						*(line++) = instruction< AN::call    , AT::id    >;
						*(line++) = instruction< AN::select  , AT::front >; // rep
						*(line++) = instruction< AN::replace , AT::id    >;

						*locs_iter  = get_pos(k, 1); // op
						 locs_iter += 2;
						*locs_iter  = get_pos(k, 0); // rep
						 locs_iter += 2;

						break;
					}
					case Context::branch: // have to keep track of the implicit label locations:
					{
						*(line++) = instruction< AN::jump , AT::branch >; // Done = 3

						++locs_iter;

						break;
					}
					case Context::go_to:
					{
						*(line++) = instruction< AN::jump , AT::go_to >; // Loop = 0

						++locs_iter;

						break;
					}
					case Context::re_turn:
					{
						*(line++) = instruction< AN::select , AT::front >; // rep
						*(line++) = instruction< AN::right  , AT::id    >;
						*(line++) = instruction< AN::first  , AT::id    >;

						*locs_iter  = get_pos(k, 0); // rep
						 locs_iter += 3;

						break;
					}
				}
			}
		}

		template<typename PageIter>
		nik_ce gindex_type get_pos(PageIter k, gindex_type n)
		{
			auto val = k->array[n].index;
			if (val == _one) val = position++;

			return val;
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

