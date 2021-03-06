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

	nik_ce auto _zero					= cctmp::_zero;
	nik_ce auto _one					= cctmp::_one;
	nik_ce auto _two					= cctmp::_two;
	nik_ce auto _three					= cctmp::_three;
	nik_ce auto _four					= cctmp::_four;
	nik_ce auto _five					= cctmp::_five;

	nik_ce auto _equal_					= cctmp::_equal_;
	nik_ce auto _tuple_					= cctmp::_tuple_;
	nik_ce auto _assign_					= cctmp::_assign_;
	nik_ce auto _dereference_				= cctmp::_dereference_;

	template<auto... Vs> nik_ce auto _increment_		= cctmp::template _increment_<Vs...>;
	template<auto... Vs> nik_ce auto _decrement_		= cctmp::template _decrement_<Vs...>;

	nik_ce auto _list_id_					= cctmp::_list_id_;
	nik_ce auto _similar_					= cctmp::_similar_;
	nik_ce auto _map_					= cctmp::_map_;

	template<auto... Vs> nik_ce auto to_list_		= cctmp::template to_list_<Vs...>;

	using MD						= typename cctmp::MD;

	template<auto... Vs> nik_ce auto UP_unpack		= cctmp_functional::template UP_unpack<Vs...>;

	using TP_write						= typename cctmp_functional::TP_write;
	using TP_merge						= typename cctmp_functional::TP_merge;

	nik_ce auto _d_assign_i_				= cctmp_generics::template _argcompose_
								<
									_assign_, _dereference_, _id_
								>;

	nik_ce auto H_repeat_specification			= cctmp_one_cycle_assembly::H_repeat_specification;
	nik_ce auto H_map_specification				= cctmp_one_cycle_assembly::H_map_specification;
	nik_ce auto H_fold_specification			= cctmp_one_cycle_assembly::H_fold_specification;
	nik_ce auto H_find_first_specification			= cctmp_one_cycle_assembly::H_find_first_specification;
	nik_ce auto H_find_all_specification			= cctmp_one_cycle_assembly::H_find_all_specification;
	nik_ce auto H_zip_specification				= cctmp_one_cycle_assembly::H_zip_specification;
	nik_ce auto H_fasten_specification			= cctmp_one_cycle_assembly::H_fasten_specification;
	nik_ce auto H_glide_specification			= cctmp_one_cycle_assembly::H_glide_specification;

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

// operators:

/***********************************************************************************************************************/

// member value:

	struct T_member_value
	{
		template<auto U>
		nik_ces auto result = T_store_U<U>::value;

	}; nik_ce auto U_member_value = U_store_T<T_member_value>;

	template<auto U>
	nik_ce auto member_value = T_member_value::template result<U>;

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

// (conceptual) defaults:

/***********************************************************************************************************************/

// label:

	nik_ce auto _default_label_ =_label_
	<
		_precycle_  < _zero         >,
		_cycle_     < _one          >,
		_postcycle_ < _two          >
	>;

// unary position:

	nik_ce auto _default_unary_position_ = _position_
	<
		_out_       < _zero         >,
		_in_        < _one          >,
		_end_       < _two          >
	>;

// binary position:

	nik_ce auto _default_binary_position_ = _position_
	<
		_out_       < _zero         >,
		_car_in_    < _one          >,
		_cdr_in_    < _two          >,
		_end_       < _three        >
	>;

// out_iter:

	nik_ce auto _default_out_iter_ = _out_iter_
	<
		_ival_      < _closing      >,
		_next_      < _increment_<> >,
		_prev_      < _decrement_<> >
	>;

// in_iter:

	nik_ce auto _default_in_iter_ = _in_iter_
	<
		_ival_      < _closing      >,
		_next_      < _increment_<> >,
		_prev_      < _decrement_<> >
	>;

// car_in_iter:

	nik_ce auto _default_car_in_iter_ = _car_in_iter_
	<
		_ival_      < _closing      >,
		_next_      < _increment_<> >,
		_prev_      < _decrement_<> >
	>;

// cdr_in_iter:

	nik_ce auto _default_cdr_in_iter_ = _cdr_in_iter_
	<
		_ival_      < _closing      >,
		_next_      < _increment_<> >,
		_prev_      < _decrement_<> >
	>;

// unary break:

	nik_ce auto _default_unary_break_ = _break_
	<
		_op_        < _equal_       >,
		_in_arg_    < _id_          >,
		_end_arg_   < _id_          >
	>;

// binary break:

	nik_ce auto _default_binary_break_ = _break_
	<
		_op_         < _equal_       >,
		_cdr_in_arg_ < _id_          >,
		_end_arg_    < _id_          >
	>;

// binary action:

	nik_ce auto _default_binary_action_ = _action_
	<
		_op_         < _tuple_       >,
		_car_in_arg_ < _dereference_ >,
		_cdr_in_arg_ < _dereference_ >
	>;

// unary mutate:

	template<auto f = _dereference_>
	nik_ce auto _default_unary_mutate_ = _mutate_
	<
		_op_        < _assign_      >,
		_out_arg_   < _dereference_ >,
		_in_arg_    < f             >
	>;

// binary mutate:

	nik_ce auto _default_binary_mutate_ = _mutate_
	<
		_op_        < _assign_      >,
		_out_arg_   < _dereference_ >,
		_ps_arg_    < _id_          >
	>;

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
			_mutate_function_      < _d_assign_i_  >,
			_out_next_             < _increment_<> >,

			_post_mutate_function_ < _id_          >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_repeat = direct_to_spec
		<
			direct_write<direct_repeat_defaults, Vs...>, H_repeat_specification
		>;

/***********************************************************************************************************************/

// conceptual:

	// default:

		nik_ce auto conceptual_repeat_defaults = U_pack_Vs
		<
			_default_label_,

			_position_
			<
				_out_       < _zero         >,
				_end_       < _one          >,
				_in_        < _two          >
			>,
			_out_iter_
			<
				_ival_      < _closing      >,
				_next_      < _increment_<> >
			>,
			_break_
			<
				_op_        < _equal_       >,
				_out_arg_   < _id_          >,
				_end_arg_   < _id_          >
			>,
			_mutate_
			<
				_op_        < _assign_      >,
				_out_arg_   < _dereference_ >,
				_in_arg_    < _id_          >
			>
		>;

	// spec:

		template<auto label, auto position, auto out_iter, auto break_, auto action>
		nik_ce auto _conceptual_repeat(nik_avp(T_pack_Vs<label, position, out_iter, break_, action>*))
		{
			nik_ce auto chord_etc	= U_chord_ < Chord::repeat , out_iter >;

			using T_label_etc	= T_accord_ < AN::repeat , AT::label    , label    >;
			using T_position_etc	= T_accord_ < AN::repeat , AT::position , position >;

			using T_cycle_etc	= T_accord_ < AN::repeat , AT::cycle , chord_etc , break_ , action >;
			nik_ce auto cycle_etc	= U_store_T < T_cycle_etc >;

			using T_precycle_etc	= T_accord_ < AN::repeat , AT::precycle  , chord_etc >;
			using T_postcycle_etc	= T_accord_ < AN::repeat , AT::postcycle , chord_etc , cycle_etc >;

			return to_list_
			<
				H_repeat_specification,
				T_label_etc::precycle, T_label_etc::cycle, T_label_etc::postcycle,
				T_position_etc::out, T_position_etc::end, T_position_etc::in,
				T_precycle_etc::pre_out_next,
				T_cycle_etc::loop_predicate, T_cycle_etc::mutate_function, T_cycle_etc::out_next,
				T_postcycle_etc::post_mutate_function
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
			_mutate_function_      < _d_assign_i_  >,
			_out_next_             < _increment_<> >,
			_in_next_              < _increment_<> >,

			_post_mutate_function_ < _id_          >,
			_post_out_next_        < _id_          >,
			_post_in_next_         < _id_          >,
			_post_end_next_        < _id_          >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_map = direct_to_spec
		<
			direct_write<direct_map_defaults, Vs...>, H_map_specification
		>;

/***********************************************************************************************************************/

// conceptual:

	// default:

		nik_ce auto conceptual_map_defaults = U_pack_Vs
		<
			_default_label_,
			_default_unary_position_,
			_default_out_iter_,
			_default_in_iter_,
			_default_unary_break_,
			_default_unary_mutate_<>
		>;

	// spec:

		template<auto label, auto position, auto out_iter, auto in_iter, auto break_, auto action>
		nik_ce auto _conceptual_map(nik_avp(T_pack_Vs<label, position, out_iter, in_iter, break_, action>*))
		{
			nik_ce auto chord_etc	= U_chord_ < Chord::map , out_iter , in_iter >;

			using T_label_etc	= T_accord_ < AN::map , AT::label    , label    >;
			using T_position_etc	= T_accord_ < AN::map , AT::position , position >;

			using T_cycle_etc	= T_accord_ < AN::map , AT::cycle , chord_etc , break_ , action >;
			nik_ce auto cycle_etc	= U_store_T < T_cycle_etc >;

			using T_precycle_etc	= T_accord_ < AN::map , AT::precycle  , chord_etc >;
			using T_postcycle_etc	= T_accord_ < AN::map , AT::postcycle , chord_etc , cycle_etc >;

			return to_list_
			<
				H_map_specification,
				T_label_etc::precycle, T_label_etc::cycle, T_label_etc::postcycle,
				T_position_etc::out, T_position_etc::in, T_position_etc::end,
				T_precycle_etc::pre_end_prev, T_precycle_etc::pre_out_next, T_precycle_etc::pre_in_next,
				T_cycle_etc::loop_predicate, T_cycle_etc::mutate_function,
					T_cycle_etc::out_next, T_cycle_etc::in_next,
				T_postcycle_etc::post_mutate_function, T_postcycle_etc::post_out_next,
					T_postcycle_etc::post_in_next, T_postcycle_etc::post_end_next
			>;
		}

		template<auto... Vs>
		nik_ce auto conceptual_map = _conceptual_map
		(
			conceptual_write<conceptual_map_defaults, Vs...>
		);

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
			direct_write<direct_fold_defaults, Vs...>, H_fold_specification
		>;

/***********************************************************************************************************************/

// conceptual:

	// default:

		nik_ce auto conceptual_fold_defaults = U_pack_Vs
		<
			_default_label_,
			_default_unary_position_,
			_in_iter_
			<
				_ival_      < _closing      >,
				_next_      < _increment_<> >
			>,
			_default_unary_break_,
			_combine_
			<
				_op_        < _tuple_       >,
				_out_arg_   < _id_          >,
				_in_arg_    < _dereference_ >
			>
		>;

	// spec:

		template<auto label, auto position, auto in_iter, auto break_, auto action>
		nik_ce auto _conceptual_fold(nik_avp(T_pack_Vs<label, position, in_iter, break_, action>*))
		{
			nik_ce auto chord_etc	= U_chord_ < Chord::fold , in_iter >;

			using T_label_etc	= T_accord_ < AN::fold , AT::label    , label    >;
			using T_position_etc	= T_accord_ < AN::fold , AT::position , position >;

			using T_cycle_etc	= T_accord_ < AN::fold , AT::cycle , chord_etc , break_ , action >;
			nik_ce auto cycle_etc	= U_store_T < T_cycle_etc >;

			using T_precycle_etc	= T_accord_ < AN::fold , AT::precycle  , chord_etc >;
			using T_postcycle_etc	= T_accord_ < AN::fold , AT::postcycle , chord_etc , cycle_etc >;

			return to_list_
			<
				H_fold_specification,
				T_label_etc::precycle, T_label_etc::cycle, T_label_etc::postcycle,
				T_position_etc::out, T_position_etc::in, T_position_etc::end,
				T_precycle_etc::pre_in_next,
				T_cycle_etc::loop_predicate, T_cycle_etc::combine_function, T_cycle_etc::in_next,
				T_postcycle_etc::post_combine_function
			>;
		}

		template<auto... Vs>
		nik_ce auto conceptual_fold = _conceptual_fold
		(
			conceptual_write<conceptual_fold_defaults, Vs...>
		);

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
			_postcycle_label_       < _two              >,
			_found_label_           < _three            >,
			_done_label_            < _four             >,

			_out_position_          < _zero             >,
			_in_position_           < _one              >,
			_end_position_          < _two              >,

			_pre_in_next_           < _id_              >,

			_loop_predicate_        < _equal_           >,
			_match_predicate_       < _constant_<false> >,
			_in_next_               < _increment_<>     >,

			_post_match_predicate_  < _constant_<false> >,

			_found_mutate_function_ < _d_assign_i_      >,
			_found_out_next_        < _increment_<>     >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_find_first = direct_to_spec
		<
			direct_write<direct_find_first_defaults, Vs...>, H_find_first_specification
		>;

/***********************************************************************************************************************/

// conceptual:

	// default:

		nik_ce auto conceptual_find_first_defaults = U_pack_Vs
		<
			_label_
			<
				_precycle_  < _zero             >,
				_cycle_     < _one              >,
				_postcycle_ < _two              >,
				_found_     < _three            >,
				_done_      < _four             >
			>,
			_default_unary_position_,
			_out_iter_
			<
				_next_      < _increment_<>     >
			>,
			_in_iter_
			<
				_ival_      < _closing          >,
				_next_      < _increment_<>     >
			>,
			_default_unary_break_,
			_match_
			<
				_op_        < _constant_<false> >,
				_in_arg_    < _dereference_     >
			>,
			_default_unary_mutate_<_id_>
		>;

	// spec:

		template<auto label, auto position, auto out_iter, auto in_iter, auto break_, auto match, auto mutate>
		nik_ce auto _conceptual_find_first
		(
			nik_avp(T_pack_Vs<label, position, out_iter, in_iter, break_, match, mutate>*)
		)
		{
			nik_ce auto chord_etc	= U_chord_ < Chord::find_first , in_iter >;

			using T_label_etc	= T_accord_ < AN::find_first , AT::label    , label    >;
			using T_position_etc	= T_accord_ < AN::find_first , AT::position , position >;

			using T_cycle_etc	= T_accord_ < AN::find_first , AT::cycle , chord_etc , break_ , match >;
			nik_ce auto cycle_etc	= U_store_T < T_cycle_etc >;

			using T_precycle_etc	= T_accord_ < AN::find_first , AT::precycle  , chord_etc             >;
			using T_postcycle_etc	= T_accord_ < AN::find_first , AT::postcycle , chord_etc , cycle_etc >;
			using T_found_etc	= T_accord_ < AN::find_first , AT::found     , mutate    , out_iter  >;

			return to_list_
			<
				H_find_first_specification,
				T_label_etc::precycle, T_label_etc::cycle, T_label_etc::postcycle,
					T_label_etc::found, T_label_etc::done,
				T_position_etc::out, T_position_etc::in, T_position_etc::end,
				T_precycle_etc::pre_in_next,
				T_cycle_etc::loop_predicate, T_cycle_etc::match_predicate, T_cycle_etc::in_next,
				T_postcycle_etc::post_match_predicate,
				T_found_etc::found_mutate_function, T_found_etc::found_out_next
			>;
		}

		template<auto... Vs>
		nik_ce auto conceptual_find_first = _conceptual_find_first
		(
			conceptual_write<conceptual_find_first_defaults, Vs...>
		);

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
			_postcycle_label_           < _two              >,
			_found_label_               < _three            >,
			_postfound_label_           < _four             >,
			_done_label_                < _five             >,

			_out_position_              < _zero             >,
			_in_position_               < _one              >,
			_end_position_              < _two              >,

			_pre_in_next_               < _id_              >,

			_loop_predicate_            < _equal_           >,
			_match_predicate_           < _constant_<false> >,
			_in_next_                   < _increment_<>     >,

			_post_match_predicate_      < _constant_<false> >,

			_found_mutate_function_     < _d_assign_i_      >,
			_found_out_next_            < _increment_<>     >,
			_found_in_next_             < _increment_<>     >,

			_postfound_mutate_function_ < _d_assign_i_      >,
			_postfound_out_next_        < _increment_<>     >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_find_all = direct_to_spec
		<
			direct_write<direct_find_all_defaults, Vs...>, H_find_all_specification
		>;

/***********************************************************************************************************************/

// conceptual:

	// default:

		nik_ce auto conceptual_find_all_defaults = U_pack_Vs
		<
			_label_
			<
				_precycle_  < _zero             >,
				_cycle_     < _one              >,
				_postcycle_ < _two              >,
				_found_     < _three            >,
				_postfound_ < _four             >,
				_done_      < _five             >
			>,
			_default_unary_position_,
			_out_iter_
			<
				_next_      < _increment_<>     >
			>,
			_in_iter_
			<
				_ival_      < _closing          >,
				_next_      < _increment_<>     >
			>,
			_default_unary_break_,
			_match_
			<
				_op_        < _constant_<false> >,
				_in_arg_    < _dereference_     >
			>,
			_default_unary_mutate_<_id_>
		>;

	// spec:

		template<auto label, auto position, auto out_iter, auto in_iter, auto break_, auto match, auto mutate>
		nik_ce auto _conceptual_find_all
		(
			nik_avp(T_pack_Vs<label, position, out_iter, in_iter, break_, match, mutate>*)
		)
		{
			nik_ce auto chord_etc	= U_chord_ < Chord::find_all , in_iter >;

			using T_label_etc	= T_accord_ < AN::find_all , AT::label    , label    >;
			using T_position_etc	= T_accord_ < AN::find_all , AT::position , position >;

			using T_cycle_etc	= T_accord_ < AN::find_all , AT::cycle , chord_etc , break_ , match >;
			nik_ce auto cycle_etc	= U_store_T < T_cycle_etc >;

			using T_precycle_etc	= T_accord_ < AN::find_all , AT::precycle  , chord_etc             >;
			using T_postcycle_etc	= T_accord_ < AN::find_all , AT::postcycle , chord_etc , cycle_etc >;

			using T_found_etc	= T_accord_ < AN::find_all , AT::found , chord_etc , mutate , out_iter >;
			nik_ce auto found_etc	= U_store_T < T_found_etc >;

			using T_postfound_etc	= T_accord_ < AN::find_all , AT::postfound , found_etc >;

			return to_list_
			<
				H_find_all_specification,
				T_label_etc::precycle, T_label_etc::cycle, T_label_etc::postcycle,
					T_label_etc::found, T_label_etc::postfound, T_label_etc::done,
				T_position_etc::out, T_position_etc::in, T_position_etc::end,
				T_precycle_etc::pre_in_next,
				T_cycle_etc::loop_predicate, T_cycle_etc::match_predicate, T_cycle_etc::in_next,
				T_postcycle_etc::post_match_predicate,
				T_found_etc::found_mutate_function, T_found_etc::found_out_next, T_found_etc::found_in_next,
				T_postfound_etc::postfound_mutate_function, T_postfound_etc::postfound_out_next
			>;
		}

		template<auto... Vs>
		nik_ce auto conceptual_find_all = _conceptual_find_all
		(
			conceptual_write<conceptual_find_all_defaults, Vs...>
		);

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

			_pre_end_next_         < _id_          >,
			_pre_out_next_         < _id_          >,
			_pre_car_in_next_      < _id_          >,
			_pre_cdr_in_next_      < _id_          >,

			_loop_predicate_       < _equal_       >,
			_action_function_      < _id_          >,
			_mutate_function_      < _d_assign_i_  >,
			_out_next_             < _increment_<> >,
			_car_in_next_          < _increment_<> >,
			_cdr_in_next_          < _increment_<> >,

			_post_action_function_ < _id_          >,
			_post_mutate_function_ < _id_          >,
			_post_out_next_        < _id_          >,
			_post_car_in_next_     < _id_          >,
			_post_cdr_in_next_     < _id_          >,
			_post_end_next_        < _id_          >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_zip = direct_to_spec
		<
			direct_write<direct_zip_defaults, Vs...>, H_zip_specification
		>;

/***********************************************************************************************************************/

// conceptual:

	// default:

		nik_ce auto conceptual_zip_defaults = U_pack_Vs
		<
			_default_label_,
			_default_binary_position_,
			_default_out_iter_,
			_default_car_in_iter_,
			_default_cdr_in_iter_,
			_default_binary_break_,
			_default_binary_action_,
			_default_binary_mutate_
		>;

	// spec:

		template
		<
			auto label, auto position, auto out_iter, auto car_in_iter,
			auto cdr_in_iter, auto break_, auto action, auto mutate
		>
		nik_ce auto _conceptual_zip
		(
			nik_avp(T_pack_Vs<label, position, out_iter, car_in_iter, cdr_in_iter, break_, action, mutate>*)
		)
		{
			nik_ce auto chord_etc	= U_chord_ < Chord::zip , out_iter , car_in_iter , cdr_in_iter >;

			using T_label_etc	= T_accord_ < AN::zip , AT::label    , label    >;
			using T_position_etc	= T_accord_ < AN::zip , AT::position , position >;

			using T_cycle_etc	= T_accord_ < AN::zip , AT::cycle , chord_etc , break_ , action , mutate >;
			nik_ce auto cycle_etc	= U_store_T < T_cycle_etc >;

			using T_precycle_etc	= T_accord_ < AN::zip , AT::precycle  , chord_etc >;
			using T_postcycle_etc	= T_accord_ < AN::zip , AT::postcycle , chord_etc , cycle_etc >;

			return to_list_
			<
				H_zip_specification,
				T_label_etc::precycle, T_label_etc::cycle, T_label_etc::postcycle,
				T_position_etc::out, T_position_etc::car_in, T_position_etc::cdr_in, T_position_etc::end,
				T_precycle_etc::pre_end_prev, T_precycle_etc::pre_out_next,
					T_precycle_etc::pre_car_in_next, T_precycle_etc::pre_cdr_in_next,
				T_cycle_etc::loop_predicate, T_cycle_etc::action_function, T_cycle_etc::mutate_function,
					T_cycle_etc::out_next, T_cycle_etc::car_in_next, T_cycle_etc::cdr_in_next,
				T_postcycle_etc::post_action_function, T_postcycle_etc::post_mutate_function,
					T_postcycle_etc::post_out_next, T_postcycle_etc::post_car_in_next,
					T_postcycle_etc::post_cdr_in_next, T_postcycle_etc::post_end_next
			>;
		}

		template<auto... Vs>
		nik_ce auto conceptual_zip = _conceptual_zip
		(
			conceptual_write<conceptual_zip_defaults, Vs...>
		);

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

			_pre_end_next_          < _id_              >,
			_pre_out_next_          < _id_              >,
			_pre_car_in_next_       < _id_              >,
			_pre_cdr_in_next_       < _id_              >,

			_loop_predicate_        < _equal_           >,
			_action_function_       < _id_              >,
			_mutate_function_       < _d_assign_i_      >,
			_aux_next_              < _constant_<false> >,
			_combine_function_      < _id_              >,
			_in_next_               < _constant_<false> >,
			_out_next_              < _increment_<>     >,
			_car_in_next_           < _increment_<>     >,
			_cdr_in_next_           < _increment_<>     >,

			_post_action_function_  < _id_              >,
			_post_mutate_function_  < _id_              >,
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
			direct_write<direct_fasten_defaults, Vs...>, H_fasten_specification
		>;

/***********************************************************************************************************************/

// conceptual:

	// default:

		nik_ce auto conceptual_fasten_defaults = U_pack_Vs
		<
			_default_label_,
			_position_
			<
				_out_       < _zero              >,
				_aux_       < _one               >,
				_in_        < _two               >,
				_car_in_    < _three             >,
				_cdr_in_    < _four              >,
				_end_       < _five              >
			>,
			_default_out_iter_,
			_default_car_in_iter_,
			_default_cdr_in_iter_,
			_default_binary_break_,
			_default_binary_action_,
			_combine_
			<
				_op_         < _tuple_           >,
				_out_arg_    < _dereference_     >,
				_in_arg_     < _id_              >
			>,
			_default_binary_mutate_,
			_in_iter_
			<
				_op_         < _constant_<false> >,
				_out_arg_    < _dereference_     >,
				_in_arg_     < _id_              >,
				_aux_arg_    < _id_              >
			>,
			_aux_iter_
			<
				_op_         < _constant_<false> >,
				_out_arg_    < _dereference_     >,
				_car_in_arg_ < _dereference_     >,
				_cdr_in_arg_ < _dereference_     >
			>
		>;

	// spec:

		template
		<
			auto label, auto position, auto out_iter, auto car_in_iter, auto cdr_in_iter,
			auto break_, auto action, auto combine, auto mutate, auto in_iter, auto aux_iter
		>
		nik_ce auto _conceptual_fasten
		(
			nik_avp(T_pack_Vs
			<
				label, position, out_iter, car_in_iter, cdr_in_iter,
				break_, action, combine, mutate, in_iter, aux_iter
			>*)
		)
		{
			nik_ce auto chord_etc	= U_chord_ < Chord::fasten , out_iter , car_in_iter , cdr_in_iter >;

			using T_label_etc	= T_accord_ < AN::fasten , AT::label    , label    >;
			using T_position_etc	= T_accord_ < AN::fasten , AT::position , position >;

			using T_cycle_etc	= T_accord_
						<
							AN::fasten , AT::cycle ,
							chord_etc  , break_    , action , combine , mutate , in_iter , aux_iter
						>;
			nik_ce auto cycle_etc	= U_store_T < T_cycle_etc >;

			using T_precycle_etc	= T_accord_ < AN::fasten , AT::precycle  , chord_etc >;
			using T_postcycle_etc	= T_accord_ < AN::fasten , AT::postcycle , chord_etc , cycle_etc >;

			return to_list_
			<
				H_fasten_specification,
				T_label_etc::precycle, T_label_etc::cycle, T_label_etc::postcycle,
				T_position_etc::out, T_position_etc::aux, T_position_etc::in,
					T_position_etc::car_in, T_position_etc::cdr_in, T_position_etc::end,
				T_precycle_etc::pre_end_prev, T_precycle_etc::pre_out_next,
					T_precycle_etc::pre_car_in_next, T_precycle_etc::pre_cdr_in_next,
				T_cycle_etc::loop_predicate, T_cycle_etc::action_function, T_cycle_etc::mutate_function,
					T_cycle_etc::aux_next, T_cycle_etc::combine_function, T_cycle_etc::in_next,
					T_cycle_etc::out_next, T_cycle_etc::car_in_next, T_cycle_etc::cdr_in_next,
				T_postcycle_etc::post_action_function, T_postcycle_etc::post_mutate_function,
					T_postcycle_etc::post_combine_function, T_postcycle_etc::post_out_next,
					T_postcycle_etc::post_car_in_next, T_postcycle_etc::post_cdr_in_next,
					T_postcycle_etc::post_end_next
			>;
		}

		template<auto... Vs>
		nik_ce auto conceptual_fasten = _conceptual_fasten
		(
			conceptual_write<conceptual_fasten_defaults, Vs...>
		);

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

			_pre_end_next_          < _id_          >,
			_pre_car_in_next_       < _id_          >,
			_pre_cdr_in_next_       < _id_          >,

			_loop_predicate_        < _equal_       >,
			_action_function_       < _id_          >,
			_combine_function_      < _id_          >,
			_car_in_next_           < _increment_<> >,
			_cdr_in_next_           < _increment_<> >,

			_post_action_function_  < _id_          >,
			_post_combine_function_ < _id_          >,
			_post_car_in_next_      < _id_          >,
			_post_cdr_in_next_      < _id_          >,
			_post_end_next_         < _id_          >
		>;

	// spec:

		template<auto... Vs>
		nik_ce auto direct_glide = direct_to_spec
		<
			direct_write<direct_glide_defaults, Vs...>, H_glide_specification
		>;

/***********************************************************************************************************************/

// conceptual:

	// default:

		nik_ce auto conceptual_glide_defaults = U_pack_Vs
		<
			_default_label_,
			_default_binary_position_,
			_default_car_in_iter_,
			_default_cdr_in_iter_,
			_default_binary_break_,
			_default_binary_action_,
			_combine_
			<
				_op_        < _tuple_       >,
				_out_arg_   < _id_          >,
				_ps_arg_    < _id_          >
			>
		>;

	// spec:

		template<auto label, auto position, auto car_in_iter, auto cdr_in_iter, auto break_, auto action, auto combine>
		nik_ce auto _conceptual_glide
		(
			nik_avp(T_pack_Vs<label, position, car_in_iter, cdr_in_iter, break_, action, combine>*)
		)
		{
			nik_ce auto chord_etc	= U_chord_ < Chord::glide , car_in_iter , cdr_in_iter >;

			using T_label_etc	= T_accord_ < AN::glide , AT::label    , label    >;
			using T_position_etc	= T_accord_ < AN::glide , AT::position , position >;

			using T_cycle_etc	= T_accord_ < AN::glide , AT::cycle , chord_etc , break_ , action , combine >;
			nik_ce auto cycle_etc	= U_store_T < T_cycle_etc >;

			using T_precycle_etc	= T_accord_ < AN::glide , AT::precycle  , chord_etc >;
			using T_postcycle_etc	= T_accord_ < AN::glide , AT::postcycle , chord_etc , cycle_etc >;

			return to_list_
			<
				H_glide_specification,
				T_label_etc::precycle, T_label_etc::cycle, T_label_etc::postcycle,
				T_position_etc::out, T_position_etc::car_in, T_position_etc::cdr_in, T_position_etc::end,
				T_precycle_etc::pre_end_prev, T_precycle_etc::pre_car_in_next, T_precycle_etc::pre_cdr_in_next,
				T_cycle_etc::loop_predicate, T_cycle_etc::action_function, T_cycle_etc::combine_function,
					T_cycle_etc::car_in_next, T_cycle_etc::cdr_in_next,
				T_postcycle_etc::post_action_function, T_postcycle_etc::post_combine_function,
					T_postcycle_etc::post_car_in_next, T_postcycle_etc::post_cdr_in_next,
					T_postcycle_etc::post_end_next
			>;
		}

		template<auto... Vs>
		nik_ce auto conceptual_glide = _conceptual_glide
		(
			conceptual_write<conceptual_glide_defaults, Vs...>
		);

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_one_cycle_generics

