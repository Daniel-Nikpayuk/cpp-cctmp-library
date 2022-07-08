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

namespace cctmp_one_cycle_specs {

	using AOP							= typename cctmp::AOP;
	using MD							= typename cctmp::MD;

	template<auto U> using T_store_U				= typename cctmp::template T_store_U<U>;

	nik_ce auto _zero						= cctmp::_zero;
	nik_ce auto _one						= cctmp::_one;
	nik_ce auto _two						= cctmp::_two;

	nik_ce auto _id_						= cctmp::_id_;
	nik_ce auto _equal_						= cctmp::_equal_;
	nik_ce auto _less_than_						= cctmp::_less_than_;

	nik_ce auto U_same						= cctmp::U_same;
	nik_ce auto U_custom						= cctmp::U_custom;
	nik_ce auto U_map						= cctmp::U_map;

	nik_ce auto _deref_assign_					= cctmp_generics::_deref_assign_;

	template<typename T> nik_ce auto U_store_T			= cctmp::template U_store_T<T>;
	template<template<auto...> class B> nik_ce auto U_store_B	= cctmp::template U_store_B<B>;

	template<auto... Vs> nik_ce auto U_pack_Vs			= cctmp::template U_pack_Vs<Vs...>;

	template<auto... Vs> nik_ce auto _increment_			= cctmp::template _increment_<Vs...>;

	template<auto... Vs> nik_ce auto alias				= cctmp::template alias<Vs...>;
	template<auto... Vs> nik_ce auto unpack_			= cctmp::template unpack_<Vs...>;

	template<auto... Vs> nik_ce auto U_partial			= cctmp::template U_partial<Vs...>;
	template<auto... Vs> nik_ce auto H_partial			= cctmp::template H_partial<Vs...>;
	nik_ce auto H_partial_same					= H_partial<U_same>;

	using T_sort							= typename cctmp_functional::T_sort;

	nik_ce auto U_cut						= cctmp_functional::U_cut;

	template<auto... Vs> nik_ce auto list_fill			= cctmp_functional::template list_fill<Vs...>;
	template<auto... Vs> nik_ce auto list_compare			= cctmp_functional::template list_compare<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tags:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// direct:

/***********************************************************************************************************************/

// label:

	template<auto f> struct _precycle_label			{ nik_ces auto value = f; };
	template<auto f> struct _cycle_label			{ nik_ces auto value = f; };
	template<auto f> struct _postcycle_label		{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _precycle_label_		= U_store_T<_precycle_label<f>>;
	template<auto f> nik_ce auto _cycle_label_		= U_store_T<_cycle_label<f>>;
	template<auto f> nik_ce auto _postcycle_label_		= U_store_T<_postcycle_label<f>>;

/***********************************************************************************************************************/

// position:

	template<auto f> struct _out_position			{ nik_ces auto value = f; };
	template<auto f> struct _in_position			{ nik_ces auto value = f; };
	template<auto f> struct _car_in_position		{ nik_ces auto value = f; };
	template<auto f> struct _cdr_in_position		{ nik_ces auto value = f; };
	template<auto f> struct _end_position			{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _out_position_		= U_store_T<_out_position<f>>;
	template<auto f> nik_ce auto _in_position_		= U_store_T<_in_position<f>>;
	template<auto f> nik_ce auto _car_in_position_		= U_store_T<_car_in_position<f>>;
	template<auto f> nik_ce auto _cdr_in_position_		= U_store_T<_cdr_in_position<f>>;
	template<auto f> nik_ce auto _end_position_		= U_store_T<_end_position<f>>;

/***********************************************************************************************************************/

// out:

	template<auto f> struct _pre_out_next			{ nik_ces auto value = f; };
	template<auto f> struct _out_next			{ nik_ces auto value = f; };
	template<auto f> struct _post_out_next			{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _pre_out_next_		= U_store_T<_pre_out_next<f>>;
	template<auto f> nik_ce auto _out_next_			= U_store_T<_out_next<f>>;
	template<auto f> nik_ce auto _post_out_next_		= U_store_T<_post_out_next<f>>;

/***********************************************************************************************************************/

// in:

	template<auto f> struct _pre_in_next			{ nik_ces auto value = f; };
	template<auto f> struct _in_next			{ nik_ces auto value = f; };
	template<auto f> struct _post_in_next			{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _pre_in_next_		= U_store_T<_pre_in_next<f>>;
	template<auto f> nik_ce auto _in_next_			= U_store_T<_in_next<f>>;
	template<auto f> nik_ce auto _post_in_next_		= U_store_T<_post_in_next<f>>;

/***********************************************************************************************************************/

// car in:

	template<auto f> struct _pre_car_in_next		{ nik_ces auto value = f; };
	template<auto f> struct _car_in_next			{ nik_ces auto value = f; };
	template<auto f> struct _post_car_in_next		{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _pre_car_in_next_		= U_store_T<_pre_car_in_next<f>>;
	template<auto f> nik_ce auto _car_in_next_		= U_store_T<_car_in_next<f>>;
	template<auto f> nik_ce auto _post_car_in_next_		= U_store_T<_post_car_in_next<f>>;

/***********************************************************************************************************************/

// cdr in:

	template<auto f> struct _pre_cdr_in_next		{ nik_ces auto value = f; };
	template<auto f> struct _cdr_in_next			{ nik_ces auto value = f; };
	template<auto f> struct _post_cdr_in_next		{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _pre_cdr_in_next_		= U_store_T<_pre_cdr_in_next<f>>;
	template<auto f> nik_ce auto _cdr_in_next_		= U_store_T<_cdr_in_next<f>>;
	template<auto f> nik_ce auto _post_cdr_in_next_		= U_store_T<_post_cdr_in_next<f>>;

/***********************************************************************************************************************/

// end:

	template<auto f> struct _pre_end_prev			{ nik_ces auto value = f; };
	template<auto f> struct _end_prev			{ nik_ces auto value = f; };

	template<auto f> struct _end_next			{ nik_ces auto value = f; };
	template<auto f> struct _post_end_next			{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _pre_end_prev_		= U_store_T<_pre_end_prev<f>>;
	template<auto f> nik_ce auto _end_prev_			= U_store_T<_end_prev<f>>;

	template<auto f> nik_ce auto _end_next_			= U_store_T<_end_next<f>>;
	template<auto f> nik_ce auto _post_end_next_		= U_store_T<_post_end_next<f>>;

/***********************************************************************************************************************/

// loop:

	template<auto f> struct _loop_predicate			{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _loop_predicate_		= U_store_T<_loop_predicate<f>>;

/***********************************************************************************************************************/

// value:

	template<auto f> struct _value_predicate		{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _value_predicate_		= U_store_T<_value_predicate<f>>;

/***********************************************************************************************************************/

// act:

	template<auto f> struct _act_predicate			{ nik_ces auto value = f; };
	template<auto f> struct _act_function			{ nik_ces auto value = f; };
	template<auto f> struct _post_act_function		{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _act_predicate_		= U_store_T<_act_predicate<f>>;
	template<auto f> nik_ce auto _act_function_		= U_store_T<_act_function<f>>;
	template<auto f> nik_ce auto _post_act_function_	= U_store_T<_post_act_function<f>>;

/***********************************************************************************************************************/

// combine:

	template<auto f> struct _combine_function		{ nik_ces auto value = f; };
	template<auto f> struct _post_combine_function		{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _combine_function_		= U_store_T<_combine_function<f>>;
	template<auto f> nik_ce auto _post_combine_function_	= U_store_T<_post_combine_function<f>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tag operators:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// comparison:

/***********************************************************************************************************************/

// order:

	nik_ce auto tag_order = U_pack_Vs
	<
		// label:

			U_store_B < _precycle_label        >,
			U_store_B < _cycle_label           >,
			U_store_B < _postcycle_label       >,

		// position:

			U_store_B < _out_position          >,
			U_store_B < _in_position           >,
			U_store_B < _car_in_position       >,
			U_store_B < _cdr_in_position       >,
			U_store_B < _end_position          >,

		// out:

			U_store_B < _pre_out_next          >,
			U_store_B < _out_next              >,
			U_store_B < _post_out_next         >,

		// in:

			U_store_B < _pre_in_next           >,
			U_store_B < _in_next               >,
			U_store_B < _post_in_next          >,

		// car in:

			U_store_B < _pre_car_in_next       >,
			U_store_B < _car_in_next           >,
			U_store_B < _post_car_in_next      >,

		// cdr in:

			U_store_B < _pre_cdr_in_next       >,
			U_store_B < _cdr_in_next           >,
			U_store_B < _post_cdr_in_next      >,

		// end:

			U_store_B < _pre_end_prev          >,
			U_store_B < _end_prev              >,

			U_store_B < _end_next              >,
			U_store_B < _post_end_next         >,

		// loop:

			U_store_B < _loop_predicate        >,

		// value:

			U_store_B < _value_predicate       >,

		// act:

			U_store_B < _act_predicate         >,
			U_store_B < _act_function          >,
			U_store_B < _post_act_function     >,

		// combine:

			U_store_B < _combine_function      >,
			U_store_B < _post_combine_function >
	>;

/***********************************************************************************************************************/

// compare:

	struct T_tag_compare
	{
		template<auto d, auto Op, auto V0, auto V1>
		nik_ces auto result = list_compare
		<
			tag_order, Op,
			alias<AOP::template_id, V0>,
			alias<AOP::template_id, V1>,
			H_partial_same, d
		>;

	}; nik_ce auto U_tag_compare = U_store_T<T_tag_compare>;

	template<auto Op, auto V0, auto V1, auto d = MD::initial_depth>
	nik_ce auto tag_compare = T_tag_compare::template result<d, Op, V0, V1>;

/***********************************************************************************************************************/

// equal:

	constexpr auto H_tag_equal = H_partial<U_custom, U_tag_compare, MD::initial_depth, _equal_>;

// less than:

	constexpr auto H_tag_less_than = H_partial<U_custom, U_tag_compare, MD::initial_depth, _less_than_>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// value:

	struct T_tag_value
	{
		template<auto UTag>
		nik_ces auto result = T_store_U<UTag>::value;

	}; nik_ce auto U_tag_value = U_store_T<T_tag_value>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// specifications:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// direct:

/***********************************************************************************************************************/

// to values:

	template<auto p>
	nik_ce auto direct_to_values = unpack_
	<
		p,
		U_partial
		<
			U_map,
			U_partial<U_custom, U_tag_value>
		>
	>;

/***********************************************************************************************************************/

// to spec:

	template<auto spec, auto H_spec>
	nik_ce auto direct_to_spec = alias
	<
		AOP::list_to_template,
		direct_to_values<spec>,
		H_spec
	>;

/***********************************************************************************************************************/

// write:

	template<auto defs, auto... Vs>
	nik_ce auto direct_write = T_sort::template result
	<
		MD::initial_depth, H_tag_equal, U_cut, defs, Vs...
	>;

/***********************************************************************************************************************/

// fill:

	template<auto defs, auto... Vs>
	nik_ce auto direct_fill = list_fill
	<
		defs,
		U_pack_Vs<Vs...>,
		H_tag_equal,
		H_tag_less_than
	>;

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
/***********************************************************************************************************************/

// repeat:

/***********************************************************************************************************************/

// specification:

	template
	<
		auto PrecycleLabel, auto CycleLabel, auto PostcycleLabel,
		auto OutPosition, auto InPosition, auto EndPosition,
		auto PreOutNext, auto OutNext, auto LoopPredicate,
		auto ActFunction, auto PostActFunction
	>
	struct T_repeat_specification
	{
		nik_ces auto  precycle_label		=  PrecycleLabel;
		nik_ces auto     cycle_label		=     CycleLabel;
		nik_ces auto postcycle_label		= PostcycleLabel;

		nik_ces auto out_position		= OutPosition;
		nik_ces auto  in_position		=  InPosition;
		nik_ces auto end_position		= EndPosition;

		nik_ces auto pre_out_next		= PreOutNext;
		nik_ces auto     out_next		=    OutNext;

		nik_ces auto loop_predicate		= LoopPredicate;

		nik_ces auto      act_function		=     ActFunction;
		nik_ces auto post_act_function		= PostActFunction;
	};

	nik_ce auto H_repeat_specification = U_store_B<T_repeat_specification>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// interpretations:

/***********************************************************************************************************************/

// direct:

	// defaults:

		// manually sorted for compile time performance.

		nik_ce auto direct_repeat_defaults = U_pack_Vs
		<
			_precycle_label_    < _zero          >,
			_cycle_label_       < _one           >,
			_postcycle_label_   < _two           >,

			_out_position_      < _zero          >,
			_in_position_       < _two           >,
			_end_position_      < _one           >,

			_pre_out_next_      < _id_           >,
			_out_next_          < _increment_<>  >,

			_loop_predicate_    < _equal_        >,

			_act_function_      < _deref_assign_ >,
			_post_act_function_ < _id_           >
		>;

	// repeat:

		template<auto... Vs>
		nik_ce auto direct_repeat = direct_to_spec
		<
			direct_write<direct_repeat_defaults, Vs...>,
			H_repeat_specification
		>;

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

} // cctmp_one_cycle_specs

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
*/

