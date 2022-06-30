/************************************************************************************************************************
**
** Copyright 2021-2022 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

namespace cpp_one_cycle_specs {

	template<auto U> using T_store_U			= typename cctmp::template T_store_U<U>;

	nik_ce auto _id_					= cctmp::_id_;
	nik_ce auto _equal_					= cctmp::_equal_;

	nik_ce auto _deref_assign_				= cctmp_generics::_deref_assign_;

	template<typename T> nik_ce auto U_store_T		= cctmp::template U_store_T<T>;

	template<auto... Vs> nik_ce auto _increment_		= cctmp::template _increment_<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// specifications:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// traits/policies:

/***********************************************************************************************************************/

// argument:

	enum struct Argument
	{
		direct,
		deref,

		dimension // filler
	};

/***********************************************************************************************************************/

// interval:

	enum struct Interval
	{
		open,
		closing,
		closed,
		opening,

		dimension // filler
	};

/***********************************************************************************************************************/

// direction:

	enum struct Direction
	{
		forward,
		backward,

		dimension // filler
	};

/***********************************************************************************************************************/

// axis:

	enum struct Axis
	{
		unidirectional,
		bidirectional,

		dimension // filler
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// algorithm filters (level 1):

/***********************************************************************************************************************/

/*
	template<NLMember... Ms>			struct _map		{ };

	template<typename T>				struct _type		{ };
	template<Interval V>				struct _ival		{ };
	template<Axis V>				struct _axis		{ };
	template<auto UFunc>				struct _peek		{ };

	template<auto... Members>			struct _members		{ };
	template<typename... Attrs>			struct _attrs		{ };
	template<typename... Specs>			struct _specs		{ };

	template<auto UFunc, typename Args>		struct _value		{ };
	template<auto UFunc, typename Args>		struct _next		{ };
	template<auto UFunc, typename Args>		struct _prev		{ };
	template<auto UFunc, typename Args>		struct _test		{ };
	template<auto UFunc, typename Args>		struct _apply		{ };
	template<auto UFunc, typename Args>		struct _assign		{ };
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// repeat:

/***********************************************************************************************************************/

// specification:

	template
	<
		auto PrecycleLabel, auto CycleLabel, auto PostcycleLabel,
		auto OutPosition, auto EndPosition, auto InPosition,
		auto LoopPredicate,
		auto ActFunction, auto PostActFunction,
		auto PreOutNext, auto OutNext
	>
	struct T_repeat_specification
	{
		nik_ces auto  precycle_label		=  PrecycleLabel;
		nik_ces auto     cycle_label		=     CycleLabel;
		nik_ces auto postcycle_label		= PostcycleLabel;

		nik_ces auto out_position		= OutPosition;
		nik_ces auto end_position		= EndPosition;
		nik_ces auto  in_position		=  InPosition;

		nik_ces auto loop_predicate		= LoopPredicate;

		nik_ces auto      act_function		=     ActFunction;
		nik_ces auto post_act_function		= PostActFunction;

		nik_ces auto pre_out_next		= PreOutNext;
		nik_ces auto     out_next		=    OutNext;
	};
	
	template
	<
		auto PrecycleLabel, auto CycleLabel, auto PostcycleLabel,
		auto OutPosition, auto EndPosition, auto InPosition,
		auto LoopPredicate,
		auto ActFunction, auto PostActFunction,
		auto PreOutNext, auto OutNext
	>
	nik_ce auto U_repeat_specification = U_store_T
	<
		T_repeat_specification
		<
			PrecycleLabel, CycleLabel, PostcycleLabel,
			OutPosition, EndPosition, InPosition,
			LoopPredicate,
			ActFunction, PostActFunction,
			PreOutNext, OutNext
		>
	>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// interpretations:

/***********************************************************************************************************************/

// direct:

	template
	<
		auto loop_predicate		= _equal_,

		auto      act_function		= _deref_assign_,
		auto post_act_function		= _id_,

		auto pre_out_next		= _id_,
		auto     out_next		= _increment_<>,

		auto out_position		= 0,
		auto end_position		= 1,
		auto  in_position		= 2,

		auto  precycle_label		= 0,
		auto     cycle_label		= 1,
		auto postcycle_label		= 2
	>
	nik_ce auto direct_repeat = U_repeat_specification
	<
		 precycle_label,
		    cycle_label,
		postcycle_label,

		out_position,
		end_position,
		 in_position,

		loop_predicate,

		     act_function,
		post_act_function,

		pre_out_next,
		    out_next
	>;

// default:

	struct RepeatDefaultSpecification
	{
/*
	template
	<
		auto LoopSpec		= _loop_predicate
					<
					    _op   , _equal_
					>,
		auto ActSpec		= _act_function
					<
					    _op   , _assign_           ,
					    _arg  , Argument::deref    ,
					    _arg  , Argument::direct
					>,
		auto OutSpec		= _out_next
					<
					    _dir  , Direction::forward ,
					    _inc  , _one               ,
					    _ival , Interval::closing
					>

		auto out_position	= 0,
		auto end_position	= 1,
		auto  in_position	= 2,

		auto  precycle_label	= 0,
		auto     cycle_label	= 1,
		auto postcycle_label	= 2
	>
	using conceptual_repeat = RepeatSpecification
	<
		 precycle_label,
		    cycle_label,
		postcycle_label,

		out_position,
		end_position,
		 in_position,

		repeat_default_loop<LoopSpec, OutSpec>,

		repeat_default_function<ActSpec>,
		repeat_default_post_function<ActSpec>,

		repeat_default_pre_next<OutSpec>,
		repeat_default_next<OutSpec>
	>;
*/

		template<auto... Vs>
		nik_ces auto result()
		{
		}
	};

	template<auto... Vs>
	using repeat_default = T_store_U<RepeatDefaultSpecification::template result<Vs...>()>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// map:

		//	0. If bidirectional and last, reverse iterate end.
		//	1. For each left endpoint, if open, then iterate.
		//	2. Evaluate the common (closing) loop.
		//	3. If there exists any right endpoint, which is closed, then act/combine.
		//	4. If (3), then for each right endpoint, when open, iterate.
		//	5. If bidirectional and last, iterate end to reset.

	struct MapSpecification
	{
	//	lift < end , end_prev_<Spec> , end >,	// boolean_before_loop < is_end_prev_before_<Spec>
	//	lift < out , out_next_<Spec> , out >,	// boolean_before_loop < is_out_next_before_<Spec>
	//	lift < in  , in_next_<Spec>  , in  >,	// boolean_before_loop < is_in_next_before_<Spec>


	//	lift < out , act_func_<Spec>   , in  >,	// boolean_after_loop < is_act_func_after_<Spec>
	//	lift < out , out_next_<Spec>   , out >,	// boolean_after_loop < is_out_next_after_<Spec>
	//	lift < in  , in_next_<Spec>    , in  >,	// boolean_after_loop < is_in_next_after_<Spec>
	//	lift < end , end_next_<Spec>   , end >,	// boolean_after_loop < is_end_next_after_<Spec>
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find:

/***********************************************************************************************************************/

// (find) first:

/***********************************************************************************************************************/

// (find) all:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// zip (bimap):

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fasten:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// glide (bifold):

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cpp_one_cycle_specs

