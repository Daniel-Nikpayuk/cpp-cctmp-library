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

	using key_type						= typename cctmp::key_type;
	using AOP						= typename cctmp::AOP;

	template<auto U> using T_store_U			= typename cctmp::template T_store_U<U>;

	nik_ce auto _zero					= cctmp::_zero;
	nik_ce auto _one					= cctmp::_one;
	nik_ce auto _two					= cctmp::_two;
	nik_ce auto _three					= cctmp::_three;
	nik_ce auto _four					= cctmp::_four;
	nik_ce auto _five					= cctmp::_five;

	nik_ce auto _id_					= cctmp::_id_;
	nik_ce auto _equal_					= cctmp::_equal_;
	nik_ce auto _assign_					= cctmp::_assign_;
	nik_ce auto _dereference_				= cctmp::_dereference_;

	nik_ce auto U_similar					= cctmp::U_similar;
	nik_ce auto U_map					= cctmp::U_map;
	nik_ce auto U_custom					= cctmp::U_custom;

	template<typename T> nik_ce auto U_store_T		= cctmp::template U_store_T<T>;

	template<auto... Vs> nik_ce auto U_pack_Vs		= cctmp::template U_pack_Vs<Vs...>;

	template<auto... Vs> nik_ce auto _constant_		= cctmp::template _constant_<Vs...>;
	template<auto... Vs> nik_ce auto _increment_		= cctmp::template _increment_<Vs...>;

	template<auto... Vs> nik_ce auto alias			= cctmp::template alias<Vs...>;
	template<auto... Vs> nik_ce auto unpack_		= cctmp::template unpack_<Vs...>;

	template<auto... Vs> nik_ce auto U_partial		= cctmp::template U_partial<Vs...>;
	template<auto... Vs> nik_ce auto H_partial		= cctmp::template H_partial<Vs...>;
	nik_ce auto H_partial_similar				= H_partial<U_similar>;

	template<auto... Vs> nik_ce auto pack_write		= cctmp_functional::template pack_write<Vs...>;

	nik_ce auto _d_assign_i_				= cctmp_generics::template _argcompose_
								<
									_assign_, _dereference_, _id_
								>;

	template<auto... Vs> nik_ce auto _side_			= cctmp_generics::template _side_<Vs...>;

	nik_ce auto  H_repeat_specification			= cctmp_one_cycle_generics::H_repeat_specification;
	nik_ce auto  H_map_specification			= cctmp_one_cycle_generics::H_map_specification;
	nik_ce auto  H_fold_specification			= cctmp_one_cycle_generics::H_fold_specification;
	nik_ce auto  H_find_first_specification			= cctmp_one_cycle_generics::H_find_first_specification;
	nik_ce auto  H_find_all_specification			= cctmp_one_cycle_generics::H_find_all_specification;
	nik_ce auto  H_zip_specification			= cctmp_one_cycle_generics::H_zip_specification;
	nik_ce auto  H_fasten_specification			= cctmp_one_cycle_generics::H_fasten_specification;
	nik_ce auto  H_glide_specification			= cctmp_one_cycle_generics::H_glide_specification;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tags:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// direct:

/***********************************************************************************************************************/

// label:

	template<auto f> struct _precycle_label				{ nik_ces auto value = f; };
	template<auto f> struct _cycle_label				{ nik_ces auto value = f; };
	template<auto f> struct _postcycle_label			{ nik_ces auto value = f; };

	template<auto f> struct _match_label				{ nik_ces auto value = f; };
	template<auto f> struct _postmatch_label			{ nik_ces auto value = f; };

	template<auto f> struct _done_label				{ nik_ces auto value = f; };

	//

	template<auto f> nik_ce auto _precycle_label_			= U_store_T<_precycle_label<f>>;
	template<auto f> nik_ce auto _cycle_label_			= U_store_T<_cycle_label<f>>;
	template<auto f> nik_ce auto _postcycle_label_			= U_store_T<_postcycle_label<f>>;

	template<auto f> nik_ce auto _match_label_			= U_store_T<_match_label<f>>;
	template<auto f> nik_ce auto _postmatch_label_			= U_store_T<_postmatch_label<f>>;

	template<auto f> nik_ce auto _done_label_			= U_store_T<_done_label<f>>;

/***********************************************************************************************************************/

// position:

	template<auto f> struct _out_position				{ nik_ces auto value = f; };
	template<auto f> struct _aux_position				{ nik_ces auto value = f; };
	template<auto f> struct _in_position				{ nik_ces auto value = f; };
	template<auto f> struct _car_in_position			{ nik_ces auto value = f; };
	template<auto f> struct _cdr_in_position			{ nik_ces auto value = f; };
	template<auto f> struct _end_position				{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _out_position_			= U_store_T<_out_position<f>>;
	template<auto f> nik_ce auto _aux_position_			= U_store_T<_aux_position<f>>;
	template<auto f> nik_ce auto _in_position_			= U_store_T<_in_position<f>>;
	template<auto f> nik_ce auto _car_in_position_			= U_store_T<_car_in_position<f>>;
	template<auto f> nik_ce auto _cdr_in_position_			= U_store_T<_cdr_in_position<f>>;
	template<auto f> nik_ce auto _end_position_			= U_store_T<_end_position<f>>;

/***********************************************************************************************************************/

// out:

	template<auto f> struct _pre_out_next				{ nik_ces auto value = f; };
	template<auto f> struct _out_next				{ nik_ces auto value = f; };
	template<auto f> struct _post_out_next				{ nik_ces auto value = f; };
	template<auto f> struct _match_out_next				{ nik_ces auto value = f; };
	template<auto f> struct _postmatch_out_next			{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _pre_out_next_			= U_store_T<_pre_out_next<f>>;
	template<auto f> nik_ce auto _out_next_				= U_store_T<_out_next<f>>;
	template<auto f> nik_ce auto _post_out_next_			= U_store_T<_post_out_next<f>>;
	template<auto f> nik_ce auto _match_out_next_			= U_store_T<_match_out_next<f>>;
	template<auto f> nik_ce auto _postmatch_out_next_		= U_store_T<_postmatch_out_next<f>>;

/***********************************************************************************************************************/

// aux:

	template<auto f> struct _aux_next				{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _aux_next_				= U_store_T<_aux_next<f>>;

/***********************************************************************************************************************/

// in:

	template<auto f> struct _pre_in_next				{ nik_ces auto value = f; };
	template<auto f> struct _in_next				{ nik_ces auto value = f; };
	template<auto f> struct _post_in_next				{ nik_ces auto value = f; };
	template<auto f> struct _match_in_next				{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _pre_in_next_			= U_store_T<_pre_in_next<f>>;
	template<auto f> nik_ce auto _in_next_				= U_store_T<_in_next<f>>;
	template<auto f> nik_ce auto _post_in_next_			= U_store_T<_post_in_next<f>>;
	template<auto f> nik_ce auto _match_in_next_			= U_store_T<_match_in_next<f>>;

/***********************************************************************************************************************/

// car in:

	template<auto f> struct _pre_car_in_next			{ nik_ces auto value = f; };
	template<auto f> struct _car_in_next				{ nik_ces auto value = f; };
	template<auto f> struct _post_car_in_next			{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _pre_car_in_next_			= U_store_T<_pre_car_in_next<f>>;
	template<auto f> nik_ce auto _car_in_next_			= U_store_T<_car_in_next<f>>;
	template<auto f> nik_ce auto _post_car_in_next_			= U_store_T<_post_car_in_next<f>>;

/***********************************************************************************************************************/

// cdr in:

	template<auto f> struct _pre_cdr_in_next			{ nik_ces auto value = f; };
	template<auto f> struct _cdr_in_next				{ nik_ces auto value = f; };
	template<auto f> struct _post_cdr_in_next			{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _pre_cdr_in_next_			= U_store_T<_pre_cdr_in_next<f>>;
	template<auto f> nik_ce auto _cdr_in_next_			= U_store_T<_cdr_in_next<f>>;
	template<auto f> nik_ce auto _post_cdr_in_next_			= U_store_T<_post_cdr_in_next<f>>;

/***********************************************************************************************************************/

// end:

	template<auto f> struct _pre_end_prev				{ nik_ces auto value = f; };
	template<auto f> struct _end_prev				{ nik_ces auto value = f; };

	template<auto f> struct _end_next				{ nik_ces auto value = f; };
	template<auto f> struct _post_end_next				{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _pre_end_prev_			= U_store_T<_pre_end_prev<f>>;
	template<auto f> nik_ce auto _end_prev_				= U_store_T<_end_prev<f>>;

	template<auto f> nik_ce auto _end_next_				= U_store_T<_end_next<f>>;
	template<auto f> nik_ce auto _post_end_next_			= U_store_T<_post_end_next<f>>;

/***********************************************************************************************************************/

// loop:

	template<auto f> struct _loop_predicate				{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _loop_predicate_			= U_store_T<_loop_predicate<f>>;

/***********************************************************************************************************************/

// act:

	template<auto f> struct _act_predicate				{ nik_ces auto value = f; };
	template<auto f> struct _post_act_predicate			{ nik_ces auto value = f; };

	template<auto f> struct _act_function				{ nik_ces auto value = f; };
	template<auto f> struct _post_act_function			{ nik_ces auto value = f; };

	//

	template<auto f> nik_ce auto _act_predicate_			= U_store_T<_act_predicate<f>>;
	template<auto f> nik_ce auto _post_act_predicate_		= U_store_T<_post_act_predicate<f>>;

	template<auto f> nik_ce auto _act_function_			= U_store_T<_act_function<f>>;
	template<auto f> nik_ce auto _post_act_function_		= U_store_T<_post_act_function<f>>;

/***********************************************************************************************************************/

// combine:

	template<auto f> struct _combine_function			{ nik_ces auto value = f; };
	template<auto f> struct _post_combine_function			{ nik_ces auto value = f; };

	template<auto f> nik_ce auto _combine_function_			= U_store_T<_combine_function<f>>;
	template<auto f> nik_ce auto _post_combine_function_		= U_store_T<_post_combine_function<f>>;

/***********************************************************************************************************************/

// assign:

	template<auto f> struct _assign_function			{ nik_ces auto value = _side_<f>; };
	template<auto f> struct _post_assign_function			{ nik_ces auto value = _side_<f>; };
	template<auto f> struct _match_assign_function			{ nik_ces auto value = _side_<f>; };
	template<auto f> struct _postmatch_assign_function		{ nik_ces auto value = _side_<f>; };

	template<auto f> nik_ce auto _assign_function_			= U_store_T<_assign_function<f>>;
	template<auto f> nik_ce auto _post_assign_function_		= U_store_T<_post_assign_function<f>>;
	template<auto f> nik_ce auto _match_assign_function_		= U_store_T<_match_assign_function<f>>;
	template<auto f> nik_ce auto _postmatch_assign_function_	= U_store_T<_postmatch_assign_function<f>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// conceptual:

/***********************************************************************************************************************/

// label:

	// id:

		template<auto... Vs> struct _label			{ };
		template<auto... Vs> nik_ce auto _label_		= U_store_T<_label<Vs...>>;

	// location:

		template<auto... Vs> struct _precycle			{ };
		template<auto... Vs> struct _cycle			{ };
		template<auto... Vs> struct _postcycle			{ };
		template<auto... Vs> struct _match			{ };
		template<auto... Vs> struct _postmatch			{ };
		template<auto... Vs> struct _done			{ };

		template<auto... Vs> nik_ce auto _precycle_		= U_store_T<_precycle<Vs...>>;
		template<auto... Vs> nik_ce auto _cycle_		= U_store_T<_cycle<Vs...>>;
		template<auto... Vs> nik_ce auto _postcycle_		= U_store_T<_postcycle<Vs...>>;
		template<auto... Vs> nik_ce auto _match_		= U_store_T<_match<Vs...>>;
		template<auto... Vs> nik_ce auto _postmatch_		= U_store_T<_postmatch<Vs...>>;
		template<auto... Vs> nik_ce auto _done_			= U_store_T<_done<Vs...>>;

/***********************************************************************************************************************/

// position:

	// id:

		template<auto... Vs> struct _position			{ };
		template<auto... Vs> nik_ce auto _position_		= U_store_T<_position<Vs...>>;

	// location:

		template<auto... Vs> struct _out			{ };
		template<auto... Vs> struct _aux			{ };
		template<auto... Vs> struct _in				{ };
		template<auto... Vs> struct _car_in			{ };
		template<auto... Vs> struct _cdr_in			{ };
		template<auto... Vs> struct _end			{ };

		template<auto... Vs> nik_ce auto _out_			= U_store_T<_out<Vs...>>;
		template<auto... Vs> nik_ce auto _in_			= U_store_T<_in<Vs...>>;
		template<auto... Vs> nik_ce auto _aux_			= U_store_T<_aux<Vs...>>;
		template<auto... Vs> nik_ce auto _car_in_		= U_store_T<_car_in<Vs...>>;
		template<auto... Vs> nik_ce auto _cdr_in_		= U_store_T<_cdr_in<Vs...>>;
		template<auto... Vs> nik_ce auto _end_			= U_store_T<_end<Vs...>>;

/***********************************************************************************************************************/

// interval:

	// out:

		template<auto... Vs> struct _out_ival			{ };
		template<auto... Vs> nik_ce auto _out_ival_		= U_store_T<_out_ival<Vs...>>;

	// in:

		template<auto... Vs> struct _in_ival			{ };
		template<auto... Vs> nik_ce auto _in_ival_		= U_store_T<_in_ival<Vs...>>;

	// type:

		template<auto... Vs> struct _type			{ };
		template<auto... Vs> nik_ce auto _type_			= U_store_T<_type<Vs...>>;

	// next:

		template<auto... Vs> struct _next			{ };
		template<auto... Vs> nik_ce auto _next_			= U_store_T<_next<Vs...>>;

	// prev:

		template<auto... Vs> struct _prev			{ };
		template<auto... Vs> nik_ce auto _prev_			= U_store_T<_prev<Vs...>>;

/***********************************************************************************************************************/

// break:

	// id:

		template<auto... Vs> struct _break			{ };
		template<auto... Vs> nik_ce auto _break_		= U_store_T<_break<Vs...>>;

	// op:

		template<auto... Vs> struct _op				{ };
		template<auto... Vs> nik_ce auto _op_			= U_store_T<_op<Vs...>>;

	// arg:

		template<auto... Vs> struct _out_arg			{ };
		template<auto... Vs> struct _aux_arg			{ };
		template<auto... Vs> struct _in_arg			{ };
		template<auto... Vs> struct _car_in_arg			{ };
		template<auto... Vs> struct _cdr_in_arg			{ };
		template<auto... Vs> struct _end_arg			{ };

		template<auto... Vs> nik_ce auto _out_arg_		= U_store_T<_out_arg<Vs...>>;
		template<auto... Vs> nik_ce auto _in_arg_		= U_store_T<_in_arg<Vs...>>;
		template<auto... Vs> nik_ce auto _aux_arg_		= U_store_T<_aux_arg<Vs...>>;
		template<auto... Vs> nik_ce auto _car_in_arg_		= U_store_T<_car_in_arg<Vs...>>;
		template<auto... Vs> nik_ce auto _cdr_in_arg_		= U_store_T<_cdr_in_arg<Vs...>>;
		template<auto... Vs> nik_ce auto _end_arg_		= U_store_T<_end_arg<Vs...>>;

/***********************************************************************************************************************/

// action:

	// id:

		template<auto... Vs> struct _action			{ };
		template<auto... Vs> nik_ce auto _action_		= U_store_T<_action<Vs...>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tag operators:

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

// interpretations:

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

	template<auto direct, auto H_spec>
	nik_ce auto direct_to_spec = alias
	<
		AOP::list_to_template,
		direct_to_values<direct>,
		H_spec
	>;

/***********************************************************************************************************************/

// write:

	template<auto defs, auto... Vs>
	nik_ce auto direct_write = pack_write<H_partial_similar, defs, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// conceptual:

/***********************************************************************************************************************/

// interval:

	struct Interval
	{
		nik_ces char open	[] = "()";
		nik_ces char closing	[] = "[)";
		nik_ces char closed	[] = "[]";
		nik_ces char opening	[] = "(]";
	};

	using Ival = Interval;

/***********************************************************************************************************************/

// write:

//	template<auto defs, auto... Vs>
//	nik_ce auto conceptual_write = pack_write<H_partial_similar, defs, Vs...>;

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

		struct conceptual_repeat
		{
			nik_ces auto defaults = U_pack_Vs
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
					_type_      < Ival::closing >,
					_next_      < _increment_<> >,
					_prev_      < _id_          >
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
		};

	// spec:

	//	template<auto... Vs>
	//	nik_ce auto conceptual_repeat = direct_to_spec
	//	<
	//		direct_write<conceptual_repeat_defaults, Vs...>,
	//		H_repeat_specification
	//	>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// map:

/***********************************************************************************************************************/

// direct:

	// default:

		nik_ce auto direct_map_defaults = U_pack_Vs
		<
			_precycle_label_       < _zero         >,
			_cycle_label_          < _one          >,
			_postcycle_label_      < _two          >,

			_out_position_         < _zero         >,
			_in_position_          < _one          >,
			_end_position_         < _two          >,

			_pre_end_prev_         < _id_          >,
			_pre_out_next_         < _id_          >,
			_pre_in_next_          < _id_          >,

			_loop_predicate_       < _equal_       >,
			_assign_function_      < _d_assign_i_  >,
			_out_next_             < _increment_<> >,
			_in_next_              < _increment_<> >,

			_post_assign_function_ < _id_          >,
			_post_out_next_        < _id_          >,
			_post_in_next_         < _id_          >,
			_post_end_next_        < _id_          >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_map = direct_to_spec
		<
			direct_write<direct_map_defaults, Vs...>,
			H_map_specification
		>;

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

	//	struct conceptual_map
	//	{
	//		nik_ces auto defaults = U_pack_Vs
	//		<
	//			_label_
	//			<
	//				_precycle_  < _zero         >,
	//				_cycle_     < _one          >,
	//				_postcycle_ < _two          >,
	//			>,
	//			_position_
	//			<
	//				_out_       < _zero         >,
	//				_in_        < _one          >,
	//				_end_       < _two          >,
	//			>,
	//			_out_ival_
	//			<
	//				_type_      < Ival::closing >,
	//				_next_      < _increment_<> >
	//			>,
	//			_in_ival_
	//			<
	//				_type_      < Ival::closing >,
	//				_next_      < _increment_<> >,
	//				_prev_      < _decrement_<> >
	//			>,
	//			_break_
	//			<
	//				_op_        < _equal_       >,
	//				_in_arg_    < _id_          >,
	//				_end_arg_   < _id_          >
	//			>,
	//			_action_
	//			<
	//				_op_        < _assign_      >,
	//				_out_arg_   < _deref_       >,
	//				_in_arg_    < _deref_       >
	//			>
	//		>;
	//	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/

// direct:

	// default:

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

/***********************************************************************************************************************/

// conceptual:


/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (find) all:

/***********************************************************************************************************************/

// direct:

	// default:

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

/***********************************************************************************************************************/

// conceptual:



/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// zip (bimap):

/***********************************************************************************************************************/

// direct:

	// default:

		nik_ce auto direct_zip_defaults = U_pack_Vs
		<
			_precycle_label_       < _zero         >,
			_cycle_label_          < _one          >,
			_postcycle_label_      < _two          >,

			_out_position_         < _zero         >,
			_car_in_position_      < _one          >,
			_cdr_in_position_      < _two          >,
			_end_position_         < _three        >,

			_pre_end_prev_         < _id_          >,
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
			_post_cdr_in_next_     < _id_          >,
			_post_end_next_        < _id_          >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_zip = direct_to_spec
		<
			direct_write<direct_zip_defaults, Vs...>,
			H_zip_specification
		>;

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

			_pre_end_prev_          < _id_              >,
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
			_post_cdr_in_next_      < _id_              >,
			_post_end_next_         < _id_              >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_fasten = direct_to_spec
		<
			direct_write<direct_fasten_defaults, Vs...>,
			H_fasten_specification
		>;

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

		nik_ce auto direct_glide_defaults = U_pack_Vs
		<
			_precycle_label_        < _zero         >,
			_cycle_label_           < _one          >,
			_postcycle_label_       < _two          >,

			_out_position_          < _zero         >,
			_car_in_position_       < _one          >,
			_cdr_in_position_       < _two          >,
			_end_position_          < _three        >,

			_pre_end_prev_          < _id_          >,
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
			_post_cdr_in_next_      < _id_          >,
			_post_end_next_         < _id_          >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_glide = direct_to_spec
		<
			direct_write<direct_glide_defaults, Vs...>,
			H_glide_specification
		>;

/***********************************************************************************************************************/

// conceptual:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_one_cycle_specs

