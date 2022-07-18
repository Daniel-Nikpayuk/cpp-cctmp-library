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

	nik_ce auto _zero					= cctmp::_zero;
	nik_ce auto _one					= cctmp::_one;
	nik_ce auto _two					= cctmp::_two;
	nik_ce auto _three					= cctmp::_three;
	nik_ce auto _four					= cctmp::_four;
	nik_ce auto _five					= cctmp::_five;

	template<auto... Vs> using T_pack_Vs			= typename cctmp::template T_pack_Vs<Vs...>;

	nik_ce auto _equal_					= cctmp::_equal_;
	nik_ce auto _assign_					= cctmp::_assign_;
	nik_ce auto _dereference_				= cctmp::_dereference_;

	template<auto... Vs> nik_ce auto _constant_		= cctmp::template _constant_<Vs...>;
	template<auto... Vs> nik_ce auto _increment_		= cctmp::template _increment_<Vs...>;
	template<auto... Vs> nik_ce auto _decrement_		= cctmp::template _decrement_<Vs...>;

	nik_ce auto _list_id_					= cctmp::_list_id_;
	nik_ce auto _similar_					= cctmp::_similar_;
	nik_ce auto _map_					= cctmp::_map_;

	template<auto... Vs> nik_ce auto unpack_		= cctmp::template unpack_<Vs...>;

	using MD						= typename cctmp::MD;

	template<auto... Vs> nik_ce auto UP_unpack		= cctmp_functional::template UP_unpack<Vs...>;

	using TP_write						= typename cctmp_functional::TP_write;
	using TP_merge						= typename cctmp_functional::TP_merge;

	nik_ce auto _d_assign_i_				= cctmp_generics::template _argcompose_
								<
									_assign_, _dereference_, _id_
								>;

	nik_ce auto H_repeat_specification			= cctmp_one_cycle_generics::H_repeat_specification;
	nik_ce auto H_map_specification				= cctmp_one_cycle_generics::H_map_specification;
	nik_ce auto H_fold_specification			= cctmp_one_cycle_generics::H_fold_specification;
	nik_ce auto H_find_first_specification			= cctmp_one_cycle_generics::H_find_first_specification;
	nik_ce auto H_find_all_specification			= cctmp_one_cycle_generics::H_find_all_specification;
	nik_ce auto H_zip_specification				= cctmp_one_cycle_generics::H_zip_specification;
	nik_ce auto H_fasten_specification			= cctmp_one_cycle_generics::H_fasten_specification;
	nik_ce auto H_glide_specification			= cctmp_one_cycle_generics::H_glide_specification;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// conveniences:

/***********************************************************************************************************************/

// list_id:

	template<auto p>
	nik_ce auto list_id = overload<_list_id_, p>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// interpretations:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// direct:

/***********************************************************************************************************************/

// to spec:

	template<auto direct, auto H_spec>
	nik_ce auto direct_to_spec = unpack_<direct, _map_, H_spec, U_member_value>;

/***********************************************************************************************************************/

// write:

	// direct:

	struct T_direct_write
	{
		template<auto d, auto defs, auto... Vs>
		nik_ces auto result = TP_write::template result<d, list_id<defs>, _similar_, defs, Vs...>;

	}; nik_ce auto U_direct_write = U_store_T<T_direct_write>;

	template<auto defs, auto... Vs>
	nik_ce auto direct_write = T_direct_write::template result<MD::initial_depth, defs, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// conceptual:

/***********************************************************************************************************************/

// write:

	struct T_conceptual_write
	{
		template<auto d, auto defs, auto... Vs>
		nik_ces auto result = TP_merge::template result
		<
			d, list_id<defs>, _similar_, UP_unpack<U_direct_write>, defs, Vs...
		>;

	}; nik_ce auto U_conceptual_write = U_store_T<T_conceptual_write>;

	template<auto defs, auto... Vs>
	nik_ce auto conceptual_write = T_conceptual_write::template result<MD::initial_depth, defs, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// repeat:

/***********************************************************************************************************************/

// direct:

	// default:

		nik_ce auto direct_repeat_defaults = U_pack_Vs
		<
			_precycle_label_       < _zero         >,
			_cycle_label_          < _one          >,
			_postcycle_label_      < _two          >,

			_out_position_         < _zero         >,
			_end_position_         < _one          >,
			_in_position_          < _two          >,

			_pre_out_next_         < _id_          >,

			_loop_predicate_       < _equal_       >,
			_assign_function_      < _d_assign_i_  >,
			_out_next_             < _increment_<> >,

			_post_assign_function_ < _id_          >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_repeat = direct_to_spec
		<
			direct_write<direct_repeat_defaults, Vs...>,
			H_repeat_specification
		>;

/***********************************************************************************************************************/

// conceptual:

	// default:

		nik_ces auto conceptual_repeat_defaults = U_pack_Vs
		<
			_label_
			<
				_precycle_  < _zero         >,
				_cycle_     < _one          >,
				_postcycle_ < _two          >
			>,
			_position_
			<
				_out_       < _zero         >,
				_end_       < _one          >,
				_in_        < _two          >
			>,
			_out_ival_
			<
				_type_      < _closing      >,
				_next_      < _increment_<> >
			>,
			_break_
			<
				_op_        < _equal_       >,
				_out_arg_   < _id_          >,
				_end_arg_   < _id_          >
			>,
			_action_
			<
				_op_        < _assign_      >,
				_out_arg_   < _dereference_ >,
				_in_arg_    < _id_          >
			>
		>;

	// spec:

		template<auto label, auto position, auto out_ival, auto break_, auto action>
		nik_ce auto _conceptual_repeat(nik_avp(T_pack_Vs<label, position, out_ival, break_, action>*))
		{
			using label_etc		= T_tr<T_label, TR::repeat, label>;
			using position_etc	= T_tr<T_position, TR::repeat, position>;
			using cycle_etc		= T_tr<T_cycle, TR::repeat, out_ival, break_, action>;
			using precycle_etc	= T_tr<T_precycle, TR::repeat,  U_store_T<cycle_etc>>;
			using postcycle_etc	= T_tr<T_postcycle, TR::repeat, U_store_T<cycle_etc>>;

			return overload
			<
				_map_, H_repeat_specification, U_member_value,

				label_etc::precycle,
				label_etc::cycle,
				label_etc::postcycle,

				position_etc::out,
				position_etc::end,
				position_etc::in,

				precycle_etc::pre_out_next,

				cycle_etc::loop_predicate,
				cycle_etc::assign_function,
				cycle_etc::out_next,

				postcycle_etc::post_assign_function
			>;
		}

		template<auto... Vs>
		nik_ce auto conceptual_repeat = _conceptual_repeat
		(
			conceptual_write<conceptual_repeat_defaults, Vs...>
		);

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// map:

/***********************************************************************************************************************/

// direct:

	// default:

/*
		nik_ce auto direct_map_defaults = U_pack_Vs
		<
			_precycle_label_       < _zero         >,
			_cycle_label_          < _one          >,
			_postcycle_label_      < _two          >,

			_out_position_         < _zero         >,
			_in_position_          < _one          >,
			_end_position_         < _two          >,

			_pre_end_next_         < _id_          >,
			_pre_out_next_         < _id_          >,
			_pre_in_next_          < _id_          >,

			_loop_predicate_       < _equal_       >,
			_assign_function_      < _d_assign_i_  >,
			_out_next_             < _increment_<> >,
			_in_next_              < _increment_<> >,

			_post_assign_function_ < _id_          >,
			_post_out_next_        < _id_          >,
			_post_end_next_        < _id_          >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_map = direct_to_spec
		<
			direct_write<direct_map_defaults, Vs...>,
			H_map_specification
		>;
*/

/***********************************************************************************************************************/

// conceptual:

/*
		nik_ces auto conceptual_map_defaults = U_pack_Vs
		<
			_label_
			<
				_precycle_  < _zero         >,
				_cycle_     < _one          >,
				_postcycle_ < _two          >
			>,
			_position_
			<
				_out_       < _zero         >,
				_in_        < _one          >,
				_end_       < _two          >
			>,
			_out_ival_
			<
				_type_      < _closing      >,
				_next_      < _increment_<> >
			>,
			_in_ival_
			<
				_type_      < _closing      >,
				_next_      < _increment_<> >,
				_prev_      < _decrement_<> >
			>,
			_break_
			<
				_op_        < _equal_       >,
				_in_arg_    < _id_          >,
				_end_arg_   < _id_          >
			>,
			_action_
			<
				_op_        < _assign_      >,
				_out_arg_   < _dereference_ >,
				_in_arg_    < _dereference_ >
			>
		>;

		template<auto label, auto position, auto out_ival, auto in_ival, auto break_, auto action>
		nik_ce auto _conceptual_map(nik_avp(T_pack_Vs<label, position, out_ival, in_ival, break_, action>*))
		{
			nik_ce auto label_etc		= tr_<T_label, TR::id, label>;
			nik_ce auto position_etc	= tr_<T_position, TR::map, position>;
			nik_ce auto cycle_etc		= tr_<T_cycle, TR::map, out_ival, in_ival, break_, action>;
			nik_ce auto precycle_etc	= tr_<T_precycle, TR::map, cycle_etc>;
			nik_ce auto postcycle_etc	= tr_<T_postcycle, TR::map, cycle_etc>;

			return etc_map
			<
				label_etc,
				position_etc,
				precycle_etc,
				cycle_etc,
				postcycle_etc
			>;
		}

		template<auto p>
		nik_ce auto let_conceptual_map = alias
		<
			AOP::list_to_template, _conceptual_map(p), H_map_specification
		>;

		template<auto... Vs>
		nik_ce auto conceptual_map = let_conceptual_map
		<
			conceptual_write<conceptual_map_defaults, Vs...>
		>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/

// direct:

	// default:

/*
		nik_ce auto direct_fold_defaults = U_pack_Vs
		<
			_precycle_label_        < _zero         >,
			_cycle_label_           < _one          >,
			_postcycle_label_       < _two          >,

			_out_position_          < _zero         >,
			_in_position_           < _one          >,
			_end_position_          < _two          >,

			_pre_in_next_           < _id_          >,

			_loop_predicate_        < _equal_       >,
			_combine_function_      < _id_          >,
			_in_next_               < _increment_<> >,

			_post_combine_function_ < _id_          >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_fold = direct_to_spec
		<
			direct_write<direct_fold_defaults, Vs...>,
			H_fold_specification
		>;
*/

/***********************************************************************************************************************/

// conceptual:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (find) first:

/***********************************************************************************************************************/

// direct:

	// default:

/*
		nik_ce auto direct_find_first_defaults = U_pack_Vs
		<
			_precycle_label_        < _zero             >,
			_cycle_label_           < _one              >,
			_match_label_           < _two              >,
			_postcycle_label_       < _three            >,
			_done_label_            < _four             >,

			_out_position_          < _zero             >,
			_in_position_           < _one              >,
			_end_position_          < _two              >,

			_pre_in_next_           < _id_              >,

			_loop_predicate_        < _equal_           >,
			_act_predicate_         < _constant_<false> >,
			_in_next_               < _increment_<>     >,

			_match_assign_function_ < _d_assign_i_      >,
			_match_out_next_        < _increment_<>     >,

			_post_act_predicate_    < _constant_<false> >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_find_first = direct_to_spec
		<
			direct_write<direct_find_first_defaults, Vs...>,
			H_find_first_specification
		>;
*/

/***********************************************************************************************************************/

// conceptual:


/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (find) all:

/***********************************************************************************************************************/

// direct:

	// default:

/*
		nik_ce auto direct_find_all_defaults = U_pack_Vs
		<
			_precycle_label_            < _zero             >,
			_cycle_label_               < _one              >,
			_match_label_               < _two              >,
			_postcycle_label_           < _three            >,
			_postmatch_label_           < _four             >,
			_done_label_                < _five             >,

			_out_position_              < _zero             >,
			_in_position_               < _one              >,
			_end_position_              < _two              >,

			_pre_in_next_               < _id_              >,

			_loop_predicate_            < _equal_           >,
			_act_predicate_             < _constant_<false> >,
			_in_next_                   < _increment_<>     >,

			_match_assign_function_     < _d_assign_i_      >,
			_match_out_next_            < _increment_<>     >,
			 _match_in_next_            < _increment_<>     >,

			_post_act_predicate_        < _constant_<false> >,

			_postmatch_assign_function_ < _d_assign_i_      >,
			_postmatch_out_next_        < _increment_<>     >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_find_all = direct_to_spec
		<
			direct_write<direct_find_all_defaults, Vs...>,
			H_find_all_specification
		>;
*/

/***********************************************************************************************************************/

// conceptual:



/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// zip (bimap):

/***********************************************************************************************************************/

// direct:

	// default:

/*
		nik_ce auto direct_zip_defaults = U_pack_Vs
		<
			_precycle_label_       < _zero         >,
			_cycle_label_          < _one          >,
			_postcycle_label_      < _two          >,

			_out_position_         < _zero         >,
			_car_in_position_      < _one          >,
			_cdr_in_position_      < _two          >,
			_end_position_         < _three        >,

			_pre_end_next_         < _id_          >,
			_pre_out_next_         < _id_          >,
			_pre_car_in_next_      < _id_          >,
			_pre_cdr_in_next_      < _id_          >,

			_loop_predicate_       < _equal_       >,
			_act_function_         < _id_          >,
			_assign_function_      < _d_assign_i_  >,
			_out_next_             < _increment_<> >,
			_car_in_next_          < _increment_<> >,
			_cdr_in_next_          < _increment_<> >,

			_post_act_function_    < _id_          >,
			_post_assign_function_ < _id_          >,
			_post_out_next_        < _id_          >,
			_post_car_in_next_     < _id_          >,
			_post_end_next_        < _id_          >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_zip = direct_to_spec
		<
			direct_write<direct_zip_defaults, Vs...>,
			H_zip_specification
		>;
*/

/***********************************************************************************************************************/

// conceptual:

		//	0. If bidirectional and last, reverse iterate end.
		//	1. For each left endpoint, if open, then iterate.
		//	2. Evaluate the common (closing) loop.
		//	3. If there exists any right endpoint, which is closed, then act/combine.
		//	4. If (3), then for each right endpoint, when open, iterate.
		//	5. If bidirectional and last, iterate end to reset.

	//	lift < end , end_prev_<Spec> , end >,	// boolean_before_loop < is_end_prev_before_<Spec>
	//	lift < out , out_next_<Spec> , out >,	// boolean_before_loop < is_out_next_before_<Spec>
	//	lift < in  , in_next_<Spec>  , in  >,	// boolean_before_loop < is_in_next_before_<Spec>


	//	lift < out , act_func_<Spec>   , in  >,	// boolean_after_loop < is_act_func_after_<Spec>
	//	lift < out , out_next_<Spec>   , out >,	// boolean_after_loop < is_out_next_after_<Spec>
	//	lift < in  , in_next_<Spec>    , in  >,	// boolean_after_loop < is_in_next_after_<Spec>
	//	lift < end , end_next_<Spec>   , end >,	// boolean_after_loop < is_end_next_after_<Spec>

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fasten (zip with a carry):

/***********************************************************************************************************************/

// direct:

	// default:

/*
		nik_ce auto direct_fasten_defaults = U_pack_Vs
		<
			_precycle_label_        < _zero             >,
			_cycle_label_           < _one              >,
			_postcycle_label_       < _two              >,

			_out_position_          < _zero             >,
			_aux_position_          < _one              >,
			_in_position_           < _two              >,
			_car_in_position_       < _three            >,
			_cdr_in_position_       < _four             >,
			_end_position_          < _five             >,

			_pre_end_next_          < _id_              >,
			_pre_out_next_          < _id_              >,
			_pre_car_in_next_       < _id_              >,
			_pre_cdr_in_next_       < _id_              >,

			_loop_predicate_        < _equal_           >,
			_act_function_          < _id_              >,
			_assign_function_       < _d_assign_i_      >,
			_aux_next_              < _constant_<false> >,
			_combine_function_      < _id_              >,
			_in_next_               < _constant_<false> >,
			_out_next_              < _increment_<>     >,
			_car_in_next_           < _increment_<>     >,
			_cdr_in_next_           < _increment_<>     >,

			_post_act_function_     < _id_              >,
			_post_assign_function_  < _id_              >,
			_post_combine_function_ < _id_              >,
			_post_out_next_         < _id_              >,
			_post_car_in_next_      < _id_              >,
			_post_end_next_         < _id_              >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_fasten = direct_to_spec
		<
			direct_write<direct_fasten_defaults, Vs...>,
			H_fasten_specification
		>;
*/

/***********************************************************************************************************************/

// conceptual:

		//	0. If bidirectional and last, reverse iterate end.
		//	1. For each left endpoint, if open, then iterate.
		//	2. Evaluate the common (closing) loop.
		//	3. If there exists any right endpoint, which is closed, then act/combine.
		//	4. If (3), then for each right endpoint, when open, iterate.
		//	5. If bidirectional and last, iterate end to reset.

	//	lift < end , end_prev_<Spec> , end >,	// boolean_before_loop < is_end_prev_before_<Spec>
	//	lift < out , out_next_<Spec> , out >,	// boolean_before_loop < is_out_next_before_<Spec>
	//	lift < in  , in_next_<Spec>  , in  >,	// boolean_before_loop < is_in_next_before_<Spec>


	//	lift < out , act_func_<Spec>   , in  >,	// boolean_after_loop < is_act_func_after_<Spec>
	//	lift < out , out_next_<Spec>   , out >,	// boolean_after_loop < is_out_next_after_<Spec>
	//	lift < in  , in_next_<Spec>    , in  >,	// boolean_after_loop < is_in_next_after_<Spec>
	//	lift < end , end_next_<Spec>   , end >,	// boolean_after_loop < is_end_next_after_<Spec>

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// glide (bifold):

/***********************************************************************************************************************/

// direct:

	// default:

/*
		nik_ce auto direct_glide_defaults = U_pack_Vs
		<
			_precycle_label_        < _zero         >,
			_cycle_label_           < _one          >,
			_postcycle_label_       < _two          >,

			_out_position_          < _zero         >,
			_car_in_position_       < _one          >,
			_cdr_in_position_       < _two          >,
			_end_position_          < _three        >,

			_pre_end_next_          < _id_          >,
			_pre_car_in_next_       < _id_          >,
			_pre_cdr_in_next_       < _id_          >,

			_loop_predicate_        < _equal_       >,
			_act_function_          < _id_          >,
			_combine_function_      < _id_          >,
			_car_in_next_           < _increment_<> >,
			_cdr_in_next_           < _increment_<> >,

			_post_act_function_     < _id_          >,
			_post_combine_function_ < _id_          >,
			_post_car_in_next_      < _id_          >,
			_post_end_next_         < _id_          >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_glide = direct_to_spec
		<
			direct_write<direct_glide_defaults, Vs...>,
			H_glide_specification
		>;
*/

/***********************************************************************************************************************/

// conceptual:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_one_cycle_specs

