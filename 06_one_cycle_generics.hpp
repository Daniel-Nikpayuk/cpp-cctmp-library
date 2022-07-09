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

	template<auto U> using T_store_U			= typename cctmp::template T_store_U<U>;

	nik_ce auto _return_					= cctmp_generics::_return_;

	template<typename T> nik_ce auto U_store_T		= cctmp::template U_store_T<T>;

	template<auto V> nik_ce auto _constant_			= cctmp::template _constant_<V>;
	template<auto V> nik_ce auto _is_equal_			= cctmp::template _is_equal_<V>;

	template<auto V> nik_ce auto label			= cctmp_generics::template label<V>;
	template<auto V> nik_ce auto branch			= cctmp_generics::template branch<V>;
	template<auto V> nik_ce auto go_to			= cctmp_generics::template go_to<V>;

	template<auto... Vs> nik_ce auto lift			= cctmp_generics::template lift<Vs...>;
	template<auto... Vs> nik_ce auto test			= cctmp_generics::template test<Vs...>;
	template<auto... Vs> nik_ce auto parse			= cctmp_generics::template parse<Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// label specs:

/***********************************************************************************************************************/

	template<auto S> nik_ce auto  precycle_			= T_store_U<S>::precycle_label;
	template<auto S> nik_ce auto     cycle_			= T_store_U<S>::cycle_label;
	template<auto S> nik_ce auto postcycle_			= T_store_U<S>::postcycle_label;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// argument specs:

/***********************************************************************************************************************/

// out:

	template<auto S> using out_type_			= typename T_store_U<S>::out_type;

	template<auto S> nik_ce auto out_			= T_store_U<S>::out_position;

	template<auto S> nik_ce auto pre_out_next_		= T_store_U<S>::pre_out_next;
	template<auto S> nik_ce auto out_next_			= T_store_U<S>::out_next;
	template<auto S> nik_ce auto post_out_next_		= T_store_U<S>::post_out_next;

/***********************************************************************************************************************/

// in:

	template<auto S> using in_type_				= typename T_store_U<S>::in_type;

	template<auto S> nik_ce auto in_			= T_store_U<S>::in_position;

	template<auto S> nik_ce auto pre_in_next_		= T_store_U<S>::pre_in_next;
	template<auto S> nik_ce auto in_next_			= T_store_U<S>::in_next;
	template<auto S> nik_ce auto post_in_next_		= T_store_U<S>::post_in_next;

/***********************************************************************************************************************/

// car in:

	template<auto S> using car_in_type_			= typename T_store_U<S>::car_in_type;

	template<auto S> nik_ce auto car_in_			= T_store_U<S>::car_in_position;

	template<auto S> nik_ce auto pre_car_in_next_		= T_store_U<S>::pre_car_in_next;
	template<auto S> nik_ce auto car_in_next_		= T_store_U<S>::car_in_next;
	template<auto S> nik_ce auto post_car_in_next_		= T_store_U<S>::post_car_in_next;

/***********************************************************************************************************************/

// cdr in:

	template<auto S> using cdr_in_type_			= typename T_store_U<S>::cdr_in_type;

	template<auto S> nik_ce auto cdr_in_			= T_store_U<S>::cdr_in_position;

	template<auto S> nik_ce auto pre_cdr_in_next_		= T_store_U<S>::pre_cdr_in_next;
	template<auto S> nik_ce auto cdr_in_next_		= T_store_U<S>::cdr_in_next;
	template<auto S> nik_ce auto post_cdr_in_next_		= T_store_U<S>::post_cdr_in_next;

/***********************************************************************************************************************/

// end:

	template<auto S> using end_type_			= typename T_store_U<S>::end_type;

	template<auto S> nik_ce auto end_			= T_store_U<S>::end_position;

	template<auto S> nik_ce auto pre_end_prev_		= T_store_U<S>::pre_end_prev;
	template<auto S> nik_ce auto end_prev_			= T_store_U<S>::end_prev;

	template<auto S> nik_ce auto end_next_			= T_store_U<S>::end_next;
	template<auto S> nik_ce auto post_end_next_		= T_store_U<S>::post_end_next;

/***********************************************************************************************************************/

// return:

	template<auto S> using return_type_			= typename T_store_U<S>::return_type;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// operator specs:

/***********************************************************************************************************************/

// loop:

	template<auto S> nik_ce auto loop_pred_			= T_store_U<S>::loop_predicate;

/***********************************************************************************************************************/

// value:

	template<auto S> nik_ce auto value_pred_		= T_store_U<S>::value_predicate;

/***********************************************************************************************************************/

// act:

	template<auto S> nik_ce auto act_pred_			= T_store_U<S>::act_predicate;

	template<auto S> nik_ce auto act_func_			= T_store_U<S>::act_function;
	template<auto S> nik_ce auto post_act_func_		= T_store_U<S>::post_act_function;

/***********************************************************************************************************************/

// combine:

	template<auto S> nik_ce auto combine_func_		= T_store_U<S>::combine_function;
	template<auto S> nik_ce auto post_combine_func_		= T_store_U<S>::post_combine_function;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// functional algorithms:

/***********************************************************************************************************************/

// repeat:

	template<auto S>
	struct T_repeat
	{
		nik_ces auto object = parse
		<
			label<precycle_<S>>,

				lift   < out_<S> ,  pre_out_next_<S> , out_<S>           >,

			label<cycle_<S>>,

				test   <               loop_pred_<S> , out_<S> , end_<S> >,
				branch <               postcycle_<S>                     >,
				lift   <                act_func_<S> , out_<S> ,  in_<S> >,
				lift   < out_<S> ,      out_next_<S> , out_<S>           >,
				go_to  <                   cycle_<S>                     >,

			label<postcycle_<S>>,

				lift   < out_<S> , post_act_func_<S> ,  in_<S>           >,

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

// map:

		//	0. If bidirectional and last, reverse iterate end.
		//	1. For each left endpoint, if open, then iterate.
		//	2. Evaluate the common (closing) loop.
		//	3. If there exists any right endpoint, which is closed, then act/combine.
		//	4. If (3), then for each right endpoint, when open, iterate.
		//	5. If bidirectional and last, iterate end to reset.

	template<auto S>
	struct T_map
	{
		nik_ces auto object = parse
		<
			label<precycle_<S>>,

				lift   < end_<S> ,  pre_end_prev_<S> , end_<S>           >,
				lift   < out_<S> ,  pre_out_next_<S> , out_<S>           >,
				lift   <  in_<S> ,   pre_in_next_<S> ,  in_<S>           >,

			label<cycle_<S>>,

				test   <               loop_pred_<S> ,  in_<S> , end_<S> >,
				branch <               postcycle_<S>                     >,
				lift   <                act_func_<S> , out_<S> ,  in_<S> >,
				lift   < out_<S> ,      out_next_<S> , out_<S>           >,
				lift   <  in_<S> ,       in_next_<S> ,  in_<S>           >,
				go_to  <                   cycle_<S>                     >,

			label<postcycle_<S>>,

				lift   <           post_act_func_<S> , out_<S> ,  in_<S> >,
				lift   < out_<S> , post_out_next_<S> , out_<S>           >,
				lift   <  in_<S> ,  post_in_next_<S> ,  in_<S>           >,
				lift   < end_<S> , post_end_next_<S> , end_<S>           >,

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

// fold:

	template<auto S>
	struct T_fold
	{
		nik_ces auto object = parse
		<
			label<precycle_<S>>,

				lift   <  in_<S> ,       pre_in_next_<S> , in_<S>           >,

			label<cycle_<S>>,

				test   <                   loop_pred_<S> , in_<S> , end_<S> >,
				branch <                   postcycle_<S>                    >,
				lift   < out_<S> ,      combine_func_<S> , in_<S>           >,
				lift   <  in_<S> ,           in_next_<S> , in_<S>           >,
				go_to  <                       cycle_<S>                    >,

			label<postcycle_<S>>,

				lift   < out_<S> , post_combine_func_<S> , in_<S>           >,

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
/***********************************************************************************************************************/

// find:

/***********************************************************************************************************************/

// message specs:

	// break:

		enum struct Break
		{
			pre_value,
			post_value,

			pre_act1,
			pre_act2,
			pre_act,
			post_act,

			pre_combine1,
			pre_combine2,
			pre_combine,
			post_combine,

			pre_next,
			post_next,

			dimension // filler
		};

	// predicates:

		// value:

			nik_ce auto _is_pre_value_				= _is_equal_<Break::pre_value>;
			nik_ce auto _is_post_value_				= _is_equal_<Break::post_value>;

		// act:

			nik_ce auto _is_pre_act_				= _is_equal_<Break::pre_act>;
			nik_ce auto _is_post_act_				= _is_equal_<Break::post_act>;

		// combine:

			nik_ce auto _is_pre_combine_				= _is_equal_<Break::pre_combine>;
			nik_ce auto _is_post_combine_				= _is_equal_<Break::post_combine>;

		// next:

			nik_ce auto _is_pre_next_				= _is_equal_<Break::pre_next>;
			nik_ce auto _is_post_next_				= _is_equal_<Break::post_next>;

	// constants:

		// value:

			nik_ce auto _br_pre_value_				= _constant_<Break::pre_value>;
			nik_ce auto _br_post_value_				= _constant_<Break::post_value>;

		// act:

			nik_ce auto _br_pre_act_				= _constant_<Break::pre_act>;
			nik_ce auto _br_post_act_				= _constant_<Break::post_act>;

		// combine:

			nik_ce auto _br_pre_combine_				= _constant_<Break::pre_combine>;
			nik_ce auto _br_post_combine_				= _constant_<Break::post_combine>;

		// next:

			nik_ce auto _br_pre_next_				= _constant_<Break::pre_next>;
			nik_ce auto _br_post_next_				= _constant_<Break::post_next>;

/***********************************************************************************************************************/

// (find) first:

/*
	template<auto S>
	struct T_find_first
	{
		nik_ces auto object = parse
		<
			label<precycle_<S>>,

				lift   <  in_<S> , pre_in_next_<S> ,  in_<S>           >,

			label<cycle_<S>>,

				test   <             loop_pred_<S> ,  in_<S> , end_<S> >,
				branch <             postcycle_<S>                     >,
				test   <              act_pred_<S> ,  in_<S>           >,
				branch <              postmatch                        >,
				lift   <  in_<S> ,     in_next_<S> ,  in_<S>           >,
				go_to  <                 cycle_<S>                     >,

			label<postcycle_<S>>,

				lift   < out_<S> ,    act_func_<S> , end_<S>           >,
				lift   < msg_<S> ,    msg_func_<S> , end_<S>           >,
				go_to  <                 done                          >,

			label<postmatch>,

				lift   < out_<S> ,    act_func_<S> ,  in_<S>           >,
				lift   < msg_<S> ,    msg_func_<S> ,  in_<S>           >,

			label<done>,

				_pair_ < out_<S> ,         msg_<S>                     >
		>;

		template<typename InType, typename EndType>
		nik_ces auto result(InType i, EndType e)
		{
			return cctmp_generics::template call<object, InType>(e, i, e);
		}

	}; template<auto S>
		nik_ce auto _find_first_ = U_store_T<T_find_first<S>>;
*/

/***********************************************************************************************************************/

// (find) all:

/*
	template<auto S>
	struct T_find_all
	{
		nik_ces auto object = parse
		<
			label<precycle_<S>>,

				lift   < end_<S> ,  pre_end_prev_<S> , end_<S>           >,
				lift   < out_<S> ,  pre_out_next_<S> , out_<S>           >,
				lift   <  in_<S> ,   pre_in_next_<S> ,  in_<S>           >,

			label<cycle_<S>>,

				test   <               loop_pred_<S> ,  in_<S> , end_<S> >,
				branch <               postcycle_<S>                     >,
				lift   < out_<S> ,    value_pred_<S> ,  in_<S>           >,
				test   <                act_pred_<S> ,  in_<S> , end_<S> >,
				branch <                actcycle                         >,
				go_to  <                nextcycle                        >,

			label<actcycle>,

				lift   < out_<S> ,      act_func_<S> ,  in_<S>           >,

			label<contcycle>,

				test   <                act_pred_<S> ,  in_<S> , end_<S> >,
				branch <                 nextcycle                       >,
				lift   <  in_<S> ,       in_next_<S> ,  in_<S>           >,
				go_to  <                   cycle_<S>                     >,

			label<nextcycle>,

				lift   < out_<S> ,      out_next_<S> , out_<S>           >,
				lift   <  in_<S> ,       in_next_<S> , in_<S>            >,
				go_to  <                   cycle_<S>                     >,

			label<postcycle_<S>>,

				lift   < out_<S> , post_act_func_<S> ,  in_<S>           >,
				lift   < out_<S> , post_out_next_<S> , out_<S>           >,
				lift   <  in_<S> ,  post_in_next_<S> ,  in_<S>           >,
				lift   < end_<S> , post_end_next_<S> , end_<S>           >,

				_return_
		>;

		template<typename OutType, typename InType, typename EndType>
		nik_ces auto result(OutType o, InType i, EndType e)
		{
			return cctmp_generics::template call<object, OutType>(o, i, e, false);
		}

	}; template<auto S>
		nik_ce auto _find_all_ = U_store_T<T_find_all<S>>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// zip (bimap):

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

				test   <                     loop_pred_<S> , car_in_<S> ,    end_<S> >,
				branch <                     postcycle_<S>                           >,
				lift   <    out_<S> ,         act_func_<S> , car_in_<S> , cdr_in_<S> >,
				lift   <    out_<S> ,         out_next_<S> ,    out_<S>              >,
				lift   < car_in_<S> ,      car_in_next_<S> , car_in_<S>              >,
				lift   < cdr_in_<S> ,      cdr_in_next_<S> , cdr_in_<S>              >,
				go_to  <                         cycle_<S>                           >,

			label<postcycle_<S>>,

				lift   <    out_<S> ,    post_act_func_<S> , car_in_<S> , cdr_in_<S> >,
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

// fasten:

	template<auto S>
	struct T_fasten
	{
		nik_ces auto object = parse
		<
			label<precycle_<S>>,

				lift   <    end_<S> ,      pre_end_prev_<S> ,    end_<S>              >,
				lift   <    out_<S> ,      pre_out_next_<S> ,    out_<S>              >,
				lift   < car_in_<S> ,   pre_car_in_next_<S> , car_in_<S>              >,
				lift   < cdr_in_<S> ,   pre_cdr_in_next_<S> , cdr_in_<S>              >,

			label<cycle_<S>>,

				test   <                      loop_pred_<S> , cdr_in_<S> ,    end_<S> >,
				branch <                      postcycle_<S>                           >,
				lift   <    out_<S> ,          act_func_<S> , car_in_<S> , cdr_in_<S> >,
				lift   <    out_<S> ,      combine_func_<S> , car_in_<S> , cdr_in_<S> >,
				lift   <    out_<S> ,          out_next_<S> ,    out_<S>              >,
				lift   < car_in_<S> ,       car_in_next_<S> , car_in_<S>              >,
				lift   < cdr_in_<S> ,       cdr_in_next_<S> , cdr_in_<S>              >,
				go_to  <                          cycle_<S>                           >,

			label<postcycle_<S>>,

				lift   <    out_<S> ,     post_act_func_<S> , car_in_<S> , cdr_in_<S> >,
				lift   <    out_<S> , post_combine_func_<S> , car_in_<S> , cdr_in_<S> >,
				lift   <    out_<S> ,     post_out_next_<S> ,    out_<S>              >,
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
		nik_ce auto _fasten_ = U_store_T<T_fasten<S>>;

/***********************************************************************************************************************/

// glide (bifold):

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
			//	lift   <    out_<S> ,          act_func_<S> ,     in_<S>              >,
				lift   <    out_<S> ,      combine_func_<S> ,    out_<S>              >,
				lift   < car_in_<S> ,       car_in_next_<S> , car_in_<S>              >,
				lift   < cdr_in_<S> ,       cdr_in_next_<S> , cdr_in_<S>              >,
				go_to  <                          cycle_<S>                           >,

			label<postcycle_<S>>,

				lift   <    out_<S> ,     post_act_func_<S> , car_in_<S> , cdr_in_<S> >,
				lift   <    out_<S> , post_combine_func_<S> ,    out_<S>              >,
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
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_one_cycle_generics

