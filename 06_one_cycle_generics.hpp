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

namespace cctmp_one_cycle_generics {

	template<auto U> using T_store_U				= typename cctmp::template T_store_U<U>;
	template<typename... Ts> using tuple				= typename cctmp::template tuple<Ts...>;

	nik_ce auto _return_						= cctmp_generics::_return_;

	template<typename T> nik_ce auto U_store_T			= cctmp::template U_store_T<T>;
	template<template<auto...> class B> nik_ce auto U_store_B	= cctmp::template U_store_B<B>;

	template<auto V> nik_ce auto _constant_				= cctmp::template _constant_<V>;
	template<auto V> nik_ce auto _is_equal_				= cctmp::template _is_equal_<V>;

	nik_ce auto _cp_						= cctmp_generics::_cp_;
	nik_ce auto _ps_						= cctmp_generics::_ps_;

	template<auto V> nik_ce auto label				= cctmp_generics::template label<V>;
	template<auto V> nik_ce auto branch				= cctmp_generics::template branch<V>;
	template<auto V> nik_ce auto go_to				= cctmp_generics::template go_to<V>;

	template<auto... Vs> nik_ce auto lift				= cctmp_generics::template lift<Vs...>;
	template<auto... Vs> nik_ce auto test				= cctmp_generics::template test<Vs...>;
	template<auto... Vs> nik_ce auto parse				= cctmp_generics::template parse<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// label specs:

/***********************************************************************************************************************/

	template<auto S> nik_ce auto  precycle_			= T_store_U<S>::precycle_label;
	template<auto S> nik_ce auto     cycle_			= T_store_U<S>::cycle_label;
	template<auto S> nik_ce auto postcycle_			= T_store_U<S>::postcycle_label;
	template<auto S> nik_ce auto     match_			= T_store_U<S>::match_label;
	template<auto S> nik_ce auto postmatch_			= T_store_U<S>::postmatch_label;
	template<auto S> nik_ce auto      done_			= T_store_U<S>::done_label;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// argument specs:

/***********************************************************************************************************************/

// out:

	template<auto S> nik_ce auto out_			= T_store_U<S>::out_position;

	template<auto S> nik_ce auto pre_out_next_		= T_store_U<S>::pre_out_next;
	template<auto S> nik_ce auto out_next_			= T_store_U<S>::out_next;
	template<auto S> nik_ce auto match_out_next_		= T_store_U<S>::match_out_next;
	template<auto S> nik_ce auto post_out_next_		= T_store_U<S>::post_out_next;
	template<auto S> nik_ce auto postmatch_out_next_	= T_store_U<S>::postmatch_out_next;

/***********************************************************************************************************************/

// aux:

	template<auto S> nik_ce auto aux_			= T_store_U<S>::aux_position;

	template<auto S> nik_ce auto aux_next_			= T_store_U<S>::aux_next;

/***********************************************************************************************************************/

// in:

	template<auto S> nik_ce auto in_			= T_store_U<S>::in_position;

	template<auto S> nik_ce auto pre_in_next_		= T_store_U<S>::pre_in_next;
	template<auto S> nik_ce auto in_next_			= T_store_U<S>::in_next;
	template<auto S> nik_ce auto match_in_next_		= T_store_U<S>::match_in_next;
	template<auto S> nik_ce auto post_in_next_		= T_store_U<S>::post_in_next;

/***********************************************************************************************************************/

// car in:

	template<auto S> nik_ce auto car_in_			= T_store_U<S>::car_in_position;

	template<auto S> nik_ce auto pre_car_in_next_		= T_store_U<S>::pre_car_in_next;
	template<auto S> nik_ce auto car_in_next_		= T_store_U<S>::car_in_next;
	template<auto S> nik_ce auto post_car_in_next_		= T_store_U<S>::post_car_in_next;

/***********************************************************************************************************************/

// cdr in:

	template<auto S> nik_ce auto cdr_in_			= T_store_U<S>::cdr_in_position;

	template<auto S> nik_ce auto pre_cdr_in_next_		= T_store_U<S>::pre_cdr_in_next;
	template<auto S> nik_ce auto cdr_in_next_		= T_store_U<S>::cdr_in_next;
	template<auto S> nik_ce auto post_cdr_in_next_		= T_store_U<S>::post_cdr_in_next;

/***********************************************************************************************************************/

// end:

	template<auto S> nik_ce auto end_			= T_store_U<S>::end_position;

	template<auto S> nik_ce auto pre_end_prev_		= T_store_U<S>::pre_end_prev;
	template<auto S> nik_ce auto end_prev_			= T_store_U<S>::end_prev;

	template<auto S> nik_ce auto end_next_			= T_store_U<S>::end_next;
	template<auto S> nik_ce auto post_end_next_		= T_store_U<S>::post_end_next;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// operator specs:

/***********************************************************************************************************************/

// loop:

	template<auto S> nik_ce auto loop_pred_			= T_store_U<S>::loop_predicate;

/***********************************************************************************************************************/

// act:

	template<auto S> nik_ce auto act_pred_			= T_store_U<S>::act_predicate;
	template<auto S> nik_ce auto post_act_pred_		= T_store_U<S>::post_act_predicate;

	template<auto S> nik_ce auto act_func_			= T_store_U<S>::act_function;
	template<auto S> nik_ce auto post_act_func_		= T_store_U<S>::post_act_function;

/***********************************************************************************************************************/

// combine:

	template<auto S> nik_ce auto combine_func_		= T_store_U<S>::combine_function;
	template<auto S> nik_ce auto post_combine_func_		= T_store_U<S>::post_combine_function;

/***********************************************************************************************************************/

// assign:

	template<auto S> nik_ce auto assign_func_		= T_store_U<S>::assign_function;
	template<auto S> nik_ce auto post_assign_func_		= T_store_U<S>::post_assign_function;
	template<auto S> nik_ce auto match_assign_func_		= T_store_U<S>::match_assign_function;
	template<auto S> nik_ce auto postmatch_assign_func_	= T_store_U<S>::postmatch_assign_function;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// functional algorithms:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// repeat:

/***********************************************************************************************************************/

// algo:

	template<auto S>
	struct T_repeat
	{
		nik_ces auto object = parse
		<
			label<precycle_<S>>,

				lift   < out_<S> ,     pre_out_next_<S> , out_<S>           >,

			label<cycle_<S>>,

				test   <                  loop_pred_<S> , out_<S> , end_<S> >,
				branch <                  postcycle_<S>                     >,
				lift   < out_<S> ,      assign_func_<S> ,  in_<S>           >,
				lift   < out_<S> ,         out_next_<S> , out_<S>           >,
				go_to  <                      cycle_<S>                     >,

			label<postcycle_<S>>,

				lift   < out_<S> , post_assign_func_<S> ,  in_<S>           >,

				_return_
		>;

		template<typename OutType, typename EndType, typename InType>
		nik_ces auto result(OutType b, EndType e, InType c)
		{
			return cctmp_generics::template call<object, OutType>(b, e, c);
		}

	}; template<auto S>
		nik_ce auto _repeat_ = U_store_T<T_repeat<S>>;

/***********************************************************************************************************************/

// spec:

	template
	<
		auto PrecycleLabel, auto CycleLabel, auto PostcycleLabel,
		auto OutPosition, auto EndPosition, auto InPosition,
		auto PreOutNext,
		auto LoopPredicate, auto AssignFunction, auto OutNext,
		auto PostAssignFunction
	>
	struct T_repeat_specification
	{
		nik_ces auto  precycle_label		=  PrecycleLabel;
		nik_ces auto     cycle_label		=     CycleLabel;
		nik_ces auto postcycle_label		= PostcycleLabel;

		nik_ces auto out_position		= OutPosition;
		nik_ces auto end_position		= EndPosition;
		nik_ces auto  in_position		=  InPosition;

		nik_ces auto pre_out_next		= PreOutNext;

		nik_ces auto   loop_predicate		=   LoopPredicate;
		nik_ces auto assign_function		= AssignFunction;
		nik_ces auto    out_next		=    OutNext;

		nik_ces auto post_assign_function	= PostAssignFunction;
	};

	nik_ce auto H_repeat_specification = U_store_B<T_repeat_specification>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// map:

/***********************************************************************************************************************/

// algo:

	template<auto S>
	struct T_map
	{
		nik_ces auto object = parse
		<
			label<precycle_<S>>,

				lift   < end_<S> ,     pre_end_prev_<S> , end_<S>           >,
				lift   < out_<S> ,     pre_out_next_<S> , out_<S>           >,
				lift   <  in_<S> ,      pre_in_next_<S> ,  in_<S>           >,

			label<cycle_<S>>,

				test   <                  loop_pred_<S> ,  in_<S> , end_<S> >,
				branch <                  postcycle_<S>                     >,
				lift   < out_<S> ,      assign_func_<S> ,  in_<S>           >,
				lift   < out_<S> ,         out_next_<S> , out_<S>           >,
				lift   <  in_<S> ,          in_next_<S> ,  in_<S>           >,
				go_to  <                      cycle_<S>                     >,

			label<postcycle_<S>>,

				lift   < out_<S> , post_assign_func_<S> ,  in_<S>           >,
				lift   < out_<S> ,    post_out_next_<S> , out_<S>           >,
				lift   <  in_<S> ,     post_in_next_<S> ,  in_<S>           >,
				lift   < end_<S> ,    post_end_next_<S> , end_<S>           >,

				_return_
		>;

		template<typename OutType, typename InType, typename EndType>
		nik_ces auto result(OutType o, InType i, EndType e)
		{
			return cctmp_generics::template call<object, OutType>(o, i, e);
		}

	}; template<auto S>
		nik_ce auto _map_ = U_store_T<T_map<S>>;

/***********************************************************************************************************************/

// spec:

	template
	<
		auto PrecycleLabel, auto CycleLabel, auto PostcycleLabel,
		auto OutPosition, auto InPosition, auto EndPosition,
		auto PreEndPrev, auto PreOutNext, auto PreInNext,
		auto LoopPredicate, auto AssignFunction, auto OutNext, auto InNext,
		auto PostAssignFunction, auto PostOutNext, auto PostInNext, auto PostEndNext
	>
	struct T_map_specification
	{
		nik_ces auto  precycle_label		=  PrecycleLabel;
		nik_ces auto     cycle_label		=     CycleLabel;
		nik_ces auto postcycle_label		= PostcycleLabel;

		nik_ces auto out_position		= OutPosition;
		nik_ces auto  in_position		=  InPosition;
		nik_ces auto end_position		= EndPosition;

		nik_ces auto pre_end_prev		= PreEndPrev;
		nik_ces auto pre_out_next		= PreOutNext;
		nik_ces auto  pre_in_next		= PreInNext;

		nik_ces auto   loop_predicate		=   LoopPredicate;
		nik_ces auto assign_function		= AssignFunction;
		nik_ces auto    out_next		=    OutNext;
		nik_ces auto     in_next		=     InNext;

		nik_ces auto post_assign_function	= PostAssignFunction;
		nik_ces auto post_out_next		=    PostOutNext;
		nik_ces auto  post_in_next		=     PostInNext;
		nik_ces auto post_end_next		=    PostEndNext;
	};

	nik_ce auto H_map_specification = U_store_B<T_map_specification>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/

// algo:

	template<auto S>
	struct T_fold
	{
		nik_ces auto object = parse
		<
			label<precycle_<S>>,

				lift   <  in_<S> ,       pre_in_next_<S> ,  in_<S>           >,

			label<cycle_<S>>,

				test   <                   loop_pred_<S> ,  in_<S> , end_<S> >,
				branch <                   postcycle_<S>                     >,
				lift   < out_<S> ,      combine_func_<S> , out_<S> ,  in_<S> >,
				lift   <  in_<S> ,           in_next_<S> ,  in_<S>           >,
				go_to  <                       cycle_<S>                     >,

			label<postcycle_<S>>,

				lift   < out_<S> , post_combine_func_<S> , out_<S> ,  in_<S> >,

				_return_
		>;

		template<typename OutType, typename InType, typename EndType>
		nik_ces auto result(OutType o, InType i, EndType e)
		{
			return cctmp_generics::template call<object, OutType>(o, i, e);
		}

	}; template<auto S>
		nik_ce auto _fold_ = U_store_T<T_fold<S>>;

/***********************************************************************************************************************/

// spec:

	template
	<
		auto PrecycleLabel, auto CycleLabel, auto PostcycleLabel,
		auto OutPosition, auto InPosition, auto EndPosition,
		auto PreInNext,
		auto LoopPredicate, auto CombineFunction, auto InNext,
		auto PostCombineFunction
	>
	struct T_fold_specification
	{
		nik_ces auto  precycle_label		=  PrecycleLabel;
		nik_ces auto     cycle_label		=     CycleLabel;
		nik_ces auto postcycle_label		= PostcycleLabel;

		nik_ces auto out_position		= OutPosition;
		nik_ces auto  in_position		=  InPosition;
		nik_ces auto end_position		= EndPosition;

		nik_ces auto  pre_in_next		= PreInNext;

		nik_ces auto    loop_predicate		=    LoopPredicate;
		nik_ces auto combine_function		= CombineFunction;
		nik_ces auto      in_next		=      InNext;

		nik_ces auto post_combine_function	= PostCombineFunction;
	};

	nik_ce auto H_fold_specification = U_store_B<T_fold_specification>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (find) first:

/***********************************************************************************************************************/

// algo:

		// If the in iterator is privileged for all interval types,
		// then the out iterator is restricted to being an opening interval,
		// so as to indicate whether or not a match was found.

	template<auto S>
	struct T_find_first
	{
		nik_ces auto object = parse
		<
			label<precycle_<S>>,

				lift   <  in_<S> ,       pre_in_next_<S> ,  in_<S>           >,

			label<cycle_<S>>,

				test   <                   loop_pred_<S> ,  in_<S> , end_<S> >,
				branch <                   postcycle_<S>                     >,
				test   <                    act_pred_<S> ,  in_<S>           >,
				branch <                       match_<S>                     >,
				lift   <  in_<S> ,           in_next_<S> ,  in_<S>           >,
				go_to  <                       cycle_<S>                     >,

			label<match_<S>>,

				lift   < out_<S> , match_assign_func_<S> ,  in_<S>           >,
				lift   < out_<S> ,    match_out_next_<S> , out_<S>           >,
				go_to  <                        done_<S>                     >,

			label<postcycle_<S>>,

				test   <               post_act_pred_<S> ,  in_<S>           >,
				branch <                       match_<S>                     >,

			label<done_<S>>,

				_return_
		>;

		template<typename OutType, typename InType, typename EndType>
		nik_ces auto result(OutType o, InType i, EndType e)
		{
			return cctmp_generics::template call<object, OutType>(o, i, e);
		}

	}; template<auto S>
		nik_ce auto _find_first_ = U_store_T<T_find_first<S>>;

/***********************************************************************************************************************/

// spec:

	template
	<
		auto PrecycleLabel, auto CycleLabel, auto MatchLabel, auto PostcycleLabel, auto DoneLabel,
		auto OutPosition, auto InPosition, auto EndPosition,
		auto PreInNext,
		auto LoopPredicate, auto ActPredicate, auto InNext,
		auto MatchAssignFunction, auto MatchOutNext,
		auto PostActPredicate
	>
	struct T_find_first_specification
	{
		nik_ces auto  precycle_label		=  PrecycleLabel;
		nik_ces auto     cycle_label		=     CycleLabel;
		nik_ces auto     match_label		=     MatchLabel;
		nik_ces auto postcycle_label		= PostcycleLabel;
		nik_ces auto      done_label		=      DoneLabel;

		nik_ces auto out_position		= OutPosition;
		nik_ces auto  in_position		=  InPosition;
		nik_ces auto end_position		= EndPosition;

		nik_ces auto  pre_in_next		= PreInNext;

		nik_ces auto loop_predicate		= LoopPredicate;
		nik_ces auto  act_predicate		=  ActPredicate;
		nik_ces auto   in_next			=   InNext;

		nik_ces auto match_assign_function	= MatchAssignFunction;
		nik_ces auto    match_out_next		=    MatchOutNext;

		nik_ces auto post_act_predicate		= PostActPredicate;
	};

	nik_ce auto H_find_first_specification = U_store_B<T_find_first_specification>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (find) all:

/***********************************************************************************************************************/

// algo:

		// If the in iterator is privileged for all interval types,
		// then the out iterator is restricted to being an opening interval,
		// so as to indicate whether or not a match was found.

	template<auto S>
	struct T_find_all
	{
		nik_ces auto object = parse
		<
			label<precycle_<S>>,

				lift   <  in_<S> ,           pre_in_next_<S> ,  in_<S>           >,

			label<cycle_<S>>,

				test   <                       loop_pred_<S> ,  in_<S> , end_<S> >,
				branch <                       postcycle_<S>                     >,
				test   <                        act_pred_<S> ,  in_<S>           >,
				branch <                           match_<S>                     >,
				lift   <  in_<S> ,               in_next_<S> ,  in_<S>           >,
				go_to  <                           cycle_<S>                     >,

			label<match_<S>>,

				lift   < out_<S> ,     match_assign_func_<S> ,  in_<S>           >,
				lift   < out_<S> ,        match_out_next_<S> , out_<S>           >,
				lift   <  in_<S> ,         match_in_next_<S> ,  in_<S>           >,
				go_to  <                           cycle_<S>                     >,

			label<postcycle_<S>>,

				test   <                   post_act_pred_<S> ,  in_<S>           >,
				branch <                       postmatch_<S>                     >,
				go_to  <                            done_<S>                     >,

			label<postmatch_<S>>,

				lift   < out_<S> , postmatch_assign_func_<S> ,  in_<S>           >,
				lift   < out_<S> ,    postmatch_out_next_<S> , out_<S>           >,

			label<done_<S>>,

				_return_
		>;

		template<typename OutType, typename InType, typename EndType>
		nik_ces auto result(OutType o, InType i, EndType e)
		{
			return cctmp_generics::template call<object, OutType>(o, i, e);
		}

	}; template<auto S>
		nik_ce auto _find_all_ = U_store_T<T_find_all<S>>;

/***********************************************************************************************************************/

// spec:

	template
	<
		auto PrecycleLabel, auto CycleLabel, auto MatchLabel, auto PostcycleLabel, auto PostmatchLabel, auto DoneLabel,
		auto OutPosition, auto InPosition, auto EndPosition,
		auto PreInNext,
		auto LoopPredicate, auto ActPredicate, auto InNext,
		auto MatchAssignFunction, auto MatchOutNext, auto MatchInNext,
		auto PostActPredicate,
		auto PostmatchAssignFunction, auto PostmatchOutNext
	>
	struct T_find_all_specification
	{
		nik_ces auto  precycle_label		=  PrecycleLabel;
		nik_ces auto     cycle_label		=     CycleLabel;
		nik_ces auto     match_label		=     MatchLabel;
		nik_ces auto postcycle_label		= PostcycleLabel;
		nik_ces auto postmatch_label		= PostmatchLabel;
		nik_ces auto      done_label		=      DoneLabel;

		nik_ces auto out_position		= OutPosition;
		nik_ces auto  in_position		=  InPosition;
		nik_ces auto end_position		= EndPosition;

		nik_ces auto  pre_in_next		= PreInNext;

		nik_ces auto loop_predicate		= LoopPredicate;
		nik_ces auto  act_predicate		=  ActPredicate;
		nik_ces auto   in_next			=   InNext;

		nik_ces auto match_assign_function	= MatchAssignFunction;
		nik_ces auto    match_out_next		=    MatchOutNext;
		nik_ces auto     match_in_next		=     MatchInNext;

		nik_ces auto post_act_predicate		= PostActPredicate;

		nik_ces auto postmatch_assign_function	= PostmatchAssignFunction;
		nik_ces auto    postmatch_out_next	=    PostmatchOutNext;
	};

	nik_ce auto H_find_all_specification = U_store_B<T_find_all_specification>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// zip (bimap):

/***********************************************************************************************************************/

// algo:

	template<auto S>
	struct T_zip
	{
		nik_ces auto object = parse
		<
			label<precycle_<S>>,

				lift   <    end_<S> ,     pre_end_prev_<S> ,    end_<S>              >,
				lift   <    out_<S> ,     pre_out_next_<S> ,    out_<S>              >,
				lift   < car_in_<S> ,  pre_car_in_next_<S> , car_in_<S>              >,
				lift   < cdr_in_<S> ,  pre_cdr_in_next_<S> , cdr_in_<S>              >,

			label<cycle_<S>>,

				test   <                     loop_pred_<S> , cdr_in_<S> ,    end_<S> >,
				branch <                     postcycle_<S>                           >,
				lift   <    _cp_    ,         act_func_<S> , car_in_<S> , cdr_in_<S> >,
				lift   <    out_<S> ,      assign_func_<S> ,    _ps_                 >,
				lift   <    out_<S> ,         out_next_<S> ,    out_<S>              >,
				lift   < car_in_<S> ,      car_in_next_<S> , car_in_<S>              >,
				lift   < cdr_in_<S> ,      cdr_in_next_<S> , cdr_in_<S>              >,
				go_to  <                         cycle_<S>                           >,

			label<postcycle_<S>>,

				lift   <    _cp_    ,    post_act_func_<S> , car_in_<S> , cdr_in_<S> >,
				lift   <    out_<S> , post_assign_func_<S> ,    _ps_                 >,
				lift   <    out_<S> ,    post_out_next_<S> ,    out_<S>              >,
				lift   < car_in_<S> , post_car_in_next_<S> , car_in_<S>              >,
				lift   < cdr_in_<S> , post_cdr_in_next_<S> , cdr_in_<S>              >,
				lift   <    end_<S> ,    post_end_next_<S> ,    end_<S>              >,

				_return_
		>;

		template<typename OutType, typename CarInType, typename CdrInType, typename EndType>
		nik_ces auto result(OutType o, CarInType i1, CdrInType i2, EndType e2)
		{
			return cctmp_generics::template call<object, OutType>(o, i1, i2, e2);
		}

	}; template<auto S>
		nik_ce auto _zip_ = U_store_T<T_zip<S>>;

/***********************************************************************************************************************/

// spec:

	template
	<
		auto PrecycleLabel, auto CycleLabel, auto PostcycleLabel,
		auto OutPosition, auto CarInPosition, auto CdrInPosition, auto EndPosition,
		auto PreEndPrev, auto PreOutNext, auto PreCarInNext, auto PreCdrInNext,
		auto LoopPredicate, auto ActFunction, auto AssignFunction, auto OutNext, auto CarInNext, auto CdrInNext,
		auto PostActFunction, auto PostAssignFunction,
			auto PostOutNext, auto PostCarInNext, auto PostCdrInNext, auto PostEndNext
	>
	struct T_zip_specification
	{
		nik_ces auto  precycle_label		=  PrecycleLabel;
		nik_ces auto     cycle_label		=     CycleLabel;
		nik_ces auto postcycle_label		= PostcycleLabel;

		nik_ces auto    out_position		=   OutPosition;
		nik_ces auto car_in_position		= CarInPosition;
		nik_ces auto cdr_in_position		= CdrInPosition;
		nik_ces auto    end_position		=   EndPosition;

		nik_ces auto    pre_end_prev		=   PreEndPrev;
		nik_ces auto    pre_out_next		=   PreOutNext;
		nik_ces auto pre_car_in_next		= PreCarInNext;
		nik_ces auto pre_cdr_in_next		= PreCdrInNext;

		nik_ces auto   loop_predicate		=   LoopPredicate;
		nik_ces auto    act_function		=    ActFunction;
		nik_ces auto assign_function		= AssignFunction;
		nik_ces auto    out_next		=    OutNext;
		nik_ces auto car_in_next		=  CarInNext;
		nik_ces auto cdr_in_next		=  CdrInNext;

		nik_ces auto    post_act_function	=    PostActFunction;
		nik_ces auto post_assign_function	= PostAssignFunction;
		nik_ces auto    post_out_next		=    PostOutNext;
		nik_ces auto post_car_in_next		=  PostCarInNext;
		nik_ces auto post_cdr_in_next		=  PostCdrInNext;
		nik_ces auto    post_end_next		=    PostEndNext;
	};

	nik_ce auto H_zip_specification = U_store_B<T_zip_specification>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fasten (zip with a carry):

/***********************************************************************************************************************/

// algo:

	template<auto S>
	struct T_fasten
	{
		nik_ces auto object = parse
		<
			label<precycle_<S>>,

				lift   <    end_<S> ,      pre_end_prev_<S> ,    end_<S>                           >,
				lift   <    out_<S> ,      pre_out_next_<S> ,    out_<S>                           >,
				lift   < car_in_<S> ,   pre_car_in_next_<S> , car_in_<S>                           >,
				lift   < cdr_in_<S> ,   pre_cdr_in_next_<S> , cdr_in_<S>                           >,

			label<cycle_<S>>,

				test   <                      loop_pred_<S> , cdr_in_<S> ,    end_<S>              >,
				branch <                      postcycle_<S>                                        >,
				lift   <    _cp_    ,          act_func_<S> , car_in_<S> , cdr_in_<S>              >,
				lift   <    out_<S> ,       assign_func_<S> ,    _ps_                              >,
				lift   <    aux_<S> ,          aux_next_<S> ,    out_<S> , car_in_<S> , cdr_in_<S> >,
				lift   <    _cp_    ,      combine_func_<S> ,    out_<S> ,     in_<S>              >,
				lift   <    out_<S> ,       assign_func_<S> ,    _ps_                              >,
				lift   <     in_<S> ,           in_next_<S> ,    out_<S> ,     in_<S> ,    aux_<S> >,
				lift   <    out_<S> ,          out_next_<S> ,    out_<S>                           >,
				lift   < car_in_<S> ,       car_in_next_<S> , car_in_<S>                           >,
				lift   < cdr_in_<S> ,       cdr_in_next_<S> , cdr_in_<S>                           >,
				go_to  <                          cycle_<S>                                        >,

			label<postcycle_<S>>,

				lift   <    _cp_    ,     post_act_func_<S> , car_in_<S> , cdr_in_<S>              >,
				lift   <    out_<S> ,  post_assign_func_<S> ,    _ps_                              >,
				lift   <    _cp_    , post_combine_func_<S> ,    out_<S> ,  in_<S>                 >,
				lift   <    out_<S> ,  post_assign_func_<S> ,    _ps_                              >,
				lift   <    out_<S> ,     post_out_next_<S> ,    out_<S>                           >,
				lift   < car_in_<S> ,  post_car_in_next_<S> , car_in_<S>                           >,
				lift   < cdr_in_<S> ,  post_cdr_in_next_<S> , cdr_in_<S>                           >,
				lift   <    end_<S> ,     post_end_next_<S> ,    end_<S>                           >,

				_return_
		>;

		template
		<
			typename OutType, typename AuxType, typename InType,
			typename CarInType, typename CdrInType, typename EndType
		>
		nik_ces auto result(OutType o, AuxType a, InType i, CarInType i1, CdrInType i2, EndType e2)
		{
			return cctmp_generics::template call<object, OutType>(o, a, i, i1, i2, e2);
		}

	}; template<auto S>
		nik_ce auto _fasten_ = U_store_T<T_fasten<S>>;

/***********************************************************************************************************************/

// spec:

	template
	<
		auto PrecycleLabel, auto CycleLabel, auto PostcycleLabel,
		auto OutPosition, auto AuxPosition, auto InPosition, auto CarInPosition, auto CdrInPosition, auto EndPosition,
		auto PreEndPrev, auto PreOutNext, auto PreCarInNext, auto PreCdrInNext,
		auto LoopPredicate, auto ActFunction, auto AssignFunction, auto AuxNext, auto CombineFunction, auto InNext,
			auto OutNext, auto CarInNext, auto CdrInNext,
		auto PostActFunction, auto PostAssignFunction, auto PostCombineFunction,
			auto PostOutNext, auto PostCarInNext, auto PostCdrInNext, auto PostEndNext
	>
	struct T_fasten_specification
	{
		nik_ces auto  precycle_label		=  PrecycleLabel;
		nik_ces auto     cycle_label		=     CycleLabel;
		nik_ces auto postcycle_label		= PostcycleLabel;

		nik_ces auto    out_position		=   OutPosition;
		nik_ces auto    aux_position		=   AuxPosition;
		nik_ces auto     in_position		=    InPosition;
		nik_ces auto car_in_position		= CarInPosition;
		nik_ces auto cdr_in_position		= CdrInPosition;
		nik_ces auto    end_position		=   EndPosition;

		nik_ces auto    pre_end_prev		=   PreEndPrev;
		nik_ces auto    pre_out_next		=   PreOutNext;
		nik_ces auto pre_car_in_next		= PreCarInNext;
		nik_ces auto pre_cdr_in_next		= PreCdrInNext;

		nik_ces auto    loop_predicate		=    LoopPredicate;
		nik_ces auto     act_function		=     ActFunction;
		nik_ces auto  assign_function		=  AssignFunction;
		nik_ces auto     aux_next		=     AuxNext;
		nik_ces auto combine_function		= CombineFunction;
		nik_ces auto      in_next		=      InNext;
		nik_ces auto     out_next		=     OutNext;
		nik_ces auto  car_in_next		=   CarInNext;
		nik_ces auto  cdr_in_next		=   CdrInNext;

		nik_ces auto     post_act_function	=     PostActFunction;
		nik_ces auto  post_assign_function	=  PostAssignFunction;
		nik_ces auto post_combine_function	= PostCombineFunction;
		nik_ces auto     post_out_next		=     PostOutNext;
		nik_ces auto  post_car_in_next		=   PostCarInNext;
		nik_ces auto  post_cdr_in_next		=   PostCdrInNext;
		nik_ces auto     post_end_next		=     PostEndNext;
	};

	nik_ce auto H_fasten_specification = U_store_B<T_fasten_specification>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// glide (bifold):

/***********************************************************************************************************************/

// algo:

	template<auto S>
	struct T_glide
	{
		nik_ces auto object = parse
		<
			label<precycle_<S>>,

				lift   <    end_<S> ,      pre_end_prev_<S> ,    end_<S>              >,
				lift   < car_in_<S> ,   pre_car_in_next_<S> , car_in_<S>              >,
				lift   < cdr_in_<S> ,   pre_cdr_in_next_<S> , cdr_in_<S>              >,

			label<cycle_<S>>,

				test   <                      loop_pred_<S> , cdr_in_<S> ,    end_<S> >,
				branch <                      postcycle_<S>                           >,
				lift   <    _cp_    ,          act_func_<S> , car_in_<S> , cdr_in_<S> >,
				lift   <    out_<S> ,      combine_func_<S> ,    out_<S> ,    _ps_    >,
				lift   < car_in_<S> ,       car_in_next_<S> , car_in_<S>              >,
				lift   < cdr_in_<S> ,       cdr_in_next_<S> , cdr_in_<S>              >,
				go_to  <                          cycle_<S>                           >,

			label<postcycle_<S>>,

				lift   <    _cp_    ,     post_act_func_<S> , car_in_<S> , cdr_in_<S> >,
				lift   <    out_<S> , post_combine_func_<S> ,    out_<S> ,    _ps_    >,
				lift   < car_in_<S> ,  post_car_in_next_<S> , car_in_<S>              >,
				lift   < cdr_in_<S> ,  post_cdr_in_next_<S> , cdr_in_<S>              >,
				lift   <    end_<S> ,     post_end_next_<S> ,    end_<S>              >,

				_return_
		>;

		template<typename OutType, typename CarInType, typename CdrInType, typename EndType>
		nik_ces auto result(OutType o, CarInType i1, CdrInType i2, EndType e2)
		{
			return cctmp_generics::template call<object, OutType>(o, i1, i2, e2);
		}

	}; template<auto S>
		nik_ce auto _glide_ = U_store_T<T_glide<S>>;

/***********************************************************************************************************************/

// spec:

	template
	<
		auto PrecycleLabel, auto CycleLabel, auto PostcycleLabel,
		auto OutPosition, auto CarInPosition, auto CdrInPosition, auto EndPosition,
		auto PreEndPrev, auto PreCarInNext, auto PreCdrInNext,
		auto LoopPredicate, auto ActFunction, auto CombineFunction, auto CarInNext, auto CdrInNext,
		auto PostActFunction, auto PostCombineFunction, auto PostCarInNext, auto PostCdrInNext, auto PostEndNext
	>
	struct T_glide_specification
	{
		nik_ces auto  precycle_label		=  PrecycleLabel;
		nik_ces auto     cycle_label		=     CycleLabel;
		nik_ces auto postcycle_label		= PostcycleLabel;

		nik_ces auto    out_position		=   OutPosition;
		nik_ces auto car_in_position		= CarInPosition;
		nik_ces auto cdr_in_position		= CdrInPosition;
		nik_ces auto    end_position		=   EndPosition;

		nik_ces auto    pre_end_prev		=   PreEndPrev;
		nik_ces auto pre_car_in_next		= PreCarInNext;
		nik_ces auto pre_cdr_in_next		= PreCdrInNext;

		nik_ces auto    loop_predicate		=    LoopPredicate;
		nik_ces auto     act_function		=     ActFunction;
		nik_ces auto combine_function		= CombineFunction;
		nik_ces auto  car_in_next		=   CarInNext;
		nik_ces auto  cdr_in_next		=   CdrInNext;

		nik_ces auto     post_act_function	=     PostActFunction;
		nik_ces auto post_combine_function	= PostCombineFunction;
		nik_ces auto  post_car_in_next		=   PostCarInNext;
		nik_ces auto  post_cdr_in_next		=   PostCdrInNext;
		nik_ces auto     post_end_next		=     PostEndNext;
	};

	nik_ce auto H_glide_specification = U_store_B<T_glide_specification>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_one_cycle_generics

