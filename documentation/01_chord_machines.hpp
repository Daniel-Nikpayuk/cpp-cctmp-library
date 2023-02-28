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

// chord machines:

namespace cctmp_chord {

// cctmp:

	nik_ce auto _id_          				= cctmp::_id_;
	nik_ce auto _nop_          				= cctmp::_nop_;
	nik_ce auto _first_          				= cctmp::_first_;
	nik_ce auto _equal_       				= cctmp::_equal_;
	nik_ce auto _assign_      				= cctmp::_assign_;
	nik_ce auto _dereference_      				= cctmp::_dereference_;

	template<typename T> nik_ce auto U_store_T		= cctmp::U_store_T<T>;
	template<auto... Vs> nik_ce auto _constant_		= cctmp::_constant_<Vs...>;
	template<auto... Vs> nik_ce auto _increment_		= cctmp::_increment_<Vs...>;
	template<auto... Vs> nik_ce auto arg_subpose		= cctmp::arg_subpose<Vs...>;

// conveniences:

	template<auto action>
	nik_ce auto _assign_d_d_ = arg_subpose
	<
		_assign_, _dereference_, arg_subpose<action, _dereference_>
	>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// repeat:

/***********************************************************************************************************************/

// algo:

	nik_ce auto repeat_algo()
	{
		return cctmp::source
		(
			"repeat out end in            ;"

			"precycle:                    ;"
			"   out = pre_out_next out    ;"

			"cycle:                       ;"
			"  test loop_pred out end     ;"
			"  branch postcycle           ;"
			"  !out = mutate_func in      ;"
			"   out = out_next out        ;"
			"  goto cycle                 ;"

			"postcycle:                   ;"
			"  !out = post_mutate_func in ;"
			"  return out                 ;"
		);
	}

/***********************************************************************************************************************/

// lookup:

	template
	<
		auto pre_out_next     = _id_          ,
		auto loop_pred        = _equal_       ,
		auto mutate_func      = _assign_      ,
		auto out_next         = _increment_<> ,
		auto post_mutate_func = _nop_
	>
	nik_ce auto repeat_frame()
	{
		return cctmp::table
		(
		 	cctmp::U_char,

			cctmp::binding( "pre_out_next"     , pre_out_next     ),
			cctmp::binding( "loop_pred"        , loop_pred        ),
			cctmp::binding( "mutate_func"      , mutate_func      ),
			cctmp::binding( "out_next"         , out_next         ),
			cctmp::binding( "post_mutate_func" , post_mutate_func )
		);
	};

	template<auto... Vs>
	nik_ce auto repeat_lookup = cctmp::make_frame<repeat_frame<Vs...>>;

/***********************************************************************************************************************/

// arg:

	template<auto lookup>
	struct T_repeat
	{
		template<typename OutType, typename EndType, typename InType>
		nik_ces auto result(OutType b, EndType e, InType c)
			{ return cctmp::generic_assembly_apply<repeat_algo, OutType, lookup>(b, e, c); }

	}; template<auto lookup>
		nik_ce auto _repeat_ = U_store_T<T_repeat<lookup>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// map:

/***********************************************************************************************************************/

// algo:

	nik_ce auto map_algo()
	{
		return cctmp::source
		(
			"map out in end               ;"

			"precycle:                    ;"
			"   end = pre_end_next end    ;"
			"   out = pre_out_next out    ;"
			"    in = pre_in_next in      ;"

			"cycle:                       ;"
			"  test loop_pred in end      ;"
			"  branch postcycle           ;"
			"  !out = mutate_func in      ;"
			"   out = out_next out        ;"
			"    in = in_next in          ;"
			"  goto cycle                 ;"

			"postcycle:                   ;"
			"  !out = post_mutate_func in ;"
			"   out = post_out_next out   ;"
			"    in = post_in_next in     ;"
			"   end = post_end_next end   ;"
			"  return out                 ;"
		);
	}

/***********************************************************************************************************************/

// lookup:

	template
	<
		auto action           = _id_                 ,

		auto pre_end_next     = _id_                 ,
		auto pre_out_next     = _id_                 ,
		auto pre_in_next      = _id_                 ,
		auto loop_pred        = _equal_              ,
		auto mutate_func      = _assign_d_d_<action> ,
		auto out_next         = _increment_<>        ,
		auto in_next          = _increment_<>        ,
		auto post_mutate_func = _nop_                ,
		auto post_out_next    = _id_                 ,
		auto post_in_next     = _id_                 ,
		auto post_end_next    = _id_
	>
	nik_ce auto map_frame()
	{
		return cctmp::table
		(
		 	cctmp::U_char,

			cctmp::binding( "pre_end_next"     , pre_end_next     ),
			cctmp::binding( "pre_out_next"     , pre_out_next     ),
			cctmp::binding( "pre_in_next"      , pre_in_next      ),
			cctmp::binding( "loop_pred"        , loop_pred        ),
			cctmp::binding( "mutate_func"      , mutate_func      ),
			cctmp::binding( "out_next"         , out_next         ),
			cctmp::binding( "in_next"          , in_next          ),
			cctmp::binding( "post_mutate_func" , post_mutate_func ),
			cctmp::binding( "post_out_next"    , post_out_next    ),
			cctmp::binding( "post_in_next"     , post_in_next     ),
			cctmp::binding( "post_end_next"    , post_end_next    )
		);
	};

	template<auto... Vs>
	nik_ce auto map_lookup = cctmp::make_frame<map_frame<Vs...>>;

/***********************************************************************************************************************/

// arg:

	template<auto lookup>
	struct T_map
	{
		template<typename OutType, typename InType, typename EndType>
		nik_ces auto result(OutType o, InType i, EndType e)
			{ return cctmp::generic_assembly_apply<map_algo, OutType, lookup>(o, i, e); }

	}; template<auto lookup>
		nik_ce auto _map_ = U_store_T<T_map<lookup>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/

// algo:

	nik_ce auto fold_algo()
	{
		return cctmp::source
		(
			"fold out in end                  ;"

			"precycle:                        ;"
			"   in = pre_in_next in           ;"

			"cycle:                           ;"
			"  test loop_pred in end          ;"
			"  branch postcycle               ;"
			"  out = combine_func out in      ;"
			"   in = in_next in               ;"
			"  goto cycle                     ;"

			"postcycle:                       ;"
			"  out = post_combine_func out in ;"
			"  return out                     ;"
		);
	}

/***********************************************************************************************************************/

// lookup:

	template
	<
		auto combine_func,

		auto pre_in_next       = _id_          ,
		auto loop_pred         = _equal_       ,
		auto in_next           = _increment_<> ,
		auto post_combine_func = _first_
	>
	nik_ce auto fold_frame()
	{
		return cctmp::table
		(
		 	cctmp::U_char,

			cctmp::binding( "pre_in_next"       , pre_in_next       ),
			cctmp::binding( "loop_pred"         , loop_pred         ),
			cctmp::binding( "combine_func"      , combine_func      ),
			cctmp::binding( "in_next"           , in_next           ),
			cctmp::binding( "post_combine_func" , post_combine_func )
		);
	};

	template<auto... Vs>
	nik_ce auto fold_lookup = cctmp::make_frame<fold_frame<Vs...>>;

/***********************************************************************************************************************/

// arg:

	template<auto lookup>
	struct T_fold
	{
		template<typename OutType, typename InType, typename EndType>
		nik_ces auto result(OutType o, InType i, EndType e)
			{ return cctmp::generic_assembly_apply<fold_algo, OutType, lookup>(o, i, e); }

	}; template<auto lookup>
		nik_ce auto _fold_ = U_store_T<T_fold<lookup>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (find) first:

/***********************************************************************************************************************/

// algo:

		// If the in iterator is privileged for all interval types,
		// then the out iterator is restricted to being an opening interval,
		// so as to indicate whether or not a match was found.

	nik_ce auto find_first_algo()
	{
		return cctmp::source
		(
			"find_first out in end         ;"

			"precycle:                     ;"
			"    in = pre_in_next in       ;"

			"cycle:                        ;"
			"  test loop_pred in end       ;"
			"  branch postcycle            ;"
			"  test match_pred in          ;"
			"  branch found                ;"
			"    in = in_next in           ;"
			"  goto cycle                  ;"

			"postcycle:                    ;"
			"  test post_match_pred in     ;"
			"  branch found                ;"
			"  goto done                   ;"

			"found:                        ;"
			"  !out = found_mutate_func in ;"
			"   out = found_out_next out   ;"

			"done:                         ;"
			"  return out                  ;"
		);
	}

/***********************************************************************************************************************/

// lookup:

	template
	<
		auto pre_in_next       = _id_              ,
		auto loop_pred         = _equal_           ,
		auto match_pred        = _constant_<false> ,
		auto in_next           = _increment_<>     ,
		auto post_match_pred   = _constant_<false> ,
		auto found_mutate_func = _assign_          ,
		auto found_out_next    = _increment_<>
	>
	nik_ce auto find_first_frame()
	{
		return cctmp::table
		(
		 	cctmp::U_char,

			cctmp::binding( "pre_in_next"       , pre_in_next       ),
			cctmp::binding( "loop_pred"         , loop_pred         ),
			cctmp::binding( "match_pred"        , match_pred        ),
			cctmp::binding( "in_next"           , in_next           ),
			cctmp::binding( "post_match_pred"   , post_match_pred   ),
			cctmp::binding( "found_mutate_func" , found_mutate_func ),
			cctmp::binding( "found_out_next"    , found_out_next    )
		);
	};

	template<auto... Vs>
	nik_ce auto find_first_lookup = cctmp::make_frame<find_first_frame<Vs...>>;

/***********************************************************************************************************************/

// arg:

	template<auto lookup>
	struct T_find_first
	{
		template<typename OutType, typename InType, typename EndType>
		nik_ces auto result(OutType o, InType i, EndType e)
			{ return cctmp::generic_assembly_apply<find_first_algo, OutType, lookup>(o, i, e); }

	}; template<auto lookup>
		nik_ce auto _find_first_ = U_store_T<T_find_first<lookup>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// (find) all:

/***********************************************************************************************************************/

// algo:

		// If the in iterator is privileged for all interval types,
		// then the out iterator is restricted to being an opening interval,
		// so as to indicate whether or not a match was found.

	nik_ce auto find_all_algo()
	{
		return cctmp::source
		(
			"find_all out in end               ;"

			"precycle:                         ;"
			"    in = pre_in_next in           ;"

			"cycle:                            ;"
			"  test loop_pred in end           ;"
			"  branch postcycle                ;"
			"  test match_pred in              ;"
			"  branch found                    ;"
			"    in = in_next in               ;"
			"  goto cycle                      ;"

			"postcycle:                        ;"
			"  test post_match_pred in         ;"
			"  branch postfound                ;"
			"  goto done                       ;"

			"found:                            ;"
			"  !out = found_mutate_func in     ;"
			"   out = found_out_next out       ;"
			"    in = found_in_next in         ;"
			"  goto cycle                      ;"

			"postfound:                        ;"
			"  !out = postfound_mutate_func in ;"
			"   out = postfound_out_next out   ;"

			"done:                             ;"
			"  return out                      ;"
		);
	}

/***********************************************************************************************************************/

// lookup:

	template
	<
		auto pre_in_next           = _id_              ,
		auto loop_pred             = _equal_           ,
		auto match_pred            = _constant_<false> ,
		auto in_next               = _increment_<>     ,
		auto post_match_pred       = _constant_<false> ,
		auto found_mutate_func     = _assign_          ,
		auto found_out_next        = _increment_<>     ,

		auto found_in_next         = _increment_<>     ,
		auto postfound_mutate_func = _assign_          ,
		auto postfound_out_next    = _increment_<>
	>
	nik_ce auto find_all_frame()
	{
		return cctmp::table
		(
		 	cctmp::U_char,

			cctmp::binding( "pre_in_next"           , pre_in_next           ),
			cctmp::binding( "loop_pred"             , loop_pred             ),
			cctmp::binding( "match_pred"            , match_pred            ),
			cctmp::binding( "in_next"               , in_next               ),
			cctmp::binding( "post_match_pred"       , post_match_pred       ),
			cctmp::binding( "found_mutate_func"     , found_mutate_func     ),
			cctmp::binding( "found_out_next"        , found_out_next        ),
			cctmp::binding( "found_in_next"         , found_in_next         ),
			cctmp::binding( "postfound_mutate_func" , postfound_mutate_func ),
			cctmp::binding( "postfound_out_next"    , postfound_out_next    )
		);
	};

	template<auto... Vs>
	nik_ce auto find_all_lookup = cctmp::make_frame<find_all_frame<Vs...>>;

/***********************************************************************************************************************/

// arg:

	template<auto lookup>
	struct T_find_all
	{
		template<typename OutType, typename InType, typename EndType>
		nik_ces auto result(OutType o, InType i, EndType e)
			{ return cctmp::generic_assembly_apply<find_all_algo, OutType, lookup>(o, i, e); }

	}; template<auto lookup>
		nik_ce auto _find_all_ = U_store_T<T_find_all<lookup>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// zip (bimap):

/***********************************************************************************************************************/

// algo:

	nik_ce auto zip_algo()
	{
		return cctmp::source
		(
			"zip out in1 in2 end2              ;"

			"precycle:                         ;"
			"  end2 = pre_end2_next end2       ;"
			"   out = pre_out_next out         ;"
			"   in1 = pre_in1_next in1         ;"
			"   in2 = pre_in2_next in2         ;"

			"cycle:                            ;"
			"  test loop_pred in2 end2         ;"
			"  branch postcycle                ;"
			"     . = action_func in1 in2      ;"
			"  !out = mutate_func _            ;"
			"   out = out_next out             ;"
			"   in1 = in1_next in1             ;"
			"   in2 = in2_next in2             ;"
			"  goto cycle                      ;"

			"postcycle:                        ;"
			"     . = post_action_func in1 in2 ;"
			"  !out = post_mutate_func _       ;"
			"   out = post_out_next out        ;"
			"   in1 = post_in1_next in1        ;"
			"   in2 = post_in2_next in2        ;"
			"  end2 = post_end2_next end2      ;"
			"  return out                      ;"
		);
	}

/***********************************************************************************************************************/

// lookup:

	template
	<
		auto pre_end2_next    = _id_          ,
		auto pre_out_next     = _id_          ,
		auto pre_in1_next     = _id_          ,
		auto pre_in2_next     = _id_          ,
		auto loop_pred        = _equal_       ,
		auto action_func      = _first_       ,
		auto mutate_func      = _assign_      ,
		auto out_next         = _increment_<> ,
		auto in1_next         = _increment_<> ,
		auto in2_next         = _increment_<> ,
		auto post_action_func = _id_          ,
		auto post_mutate_func = _nop_         ,
		auto post_out_next    = _id_          ,
		auto post_in1_next    = _id_          ,
		auto post_in2_next    = _id_          ,
		auto post_end2_next   = _id_
	>
	nik_ce auto zip_frame()
	{
		return cctmp::table
		(
		 	cctmp::U_char,

			cctmp::binding( "pre_end2_next"    , pre_end2_next    ),
			cctmp::binding( "pre_out_next"     , pre_out_next     ),
			cctmp::binding( "pre_in1_next"     , pre_in1_next     ),
			cctmp::binding( "pre_in2_next"     , pre_in2_next     ),
			cctmp::binding( "loop_pred"        , loop_pred        ),
			cctmp::binding( "action_func"      , action_func      ),
			cctmp::binding( "mutate_func"      , mutate_func      ),
			cctmp::binding( "out_next"         , out_next         ),
			cctmp::binding( "in1_next"         , in1_next         ),
			cctmp::binding( "in2_next"         , in2_next         ),
			cctmp::binding( "post_action_func" , post_action_func ),
			cctmp::binding( "post_mutate_func" , post_mutate_func ),
			cctmp::binding( "post_out_next"    , post_out_next    ),
			cctmp::binding( "post_in1_next"    , post_in1_next    ),
			cctmp::binding( "post_in2_next"    , post_in2_next    ),
			cctmp::binding( "post_end2_next"   , post_end2_next   )
		);
	};

	template<auto... Vs>
	nik_ce auto zip_lookup = cctmp::make_frame<zip_frame<Vs...>>;

/***********************************************************************************************************************/

// arg:

	template<auto lookup>
	struct T_zip
	{
		template<typename OutType, typename CarInType, typename CdrInType, typename EndType>
		nik_ces auto result(OutType o, CarInType i1, CdrInType i2, EndType e2)
			{ return cctmp::generic_assembly_apply<zip_algo, OutType, lookup>(o, i1, i2, e2); }

	}; template<auto lookup>
		nik_ce auto _zip_ = U_store_T<T_zip<lookup>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fasten (zip with a carry):

/***********************************************************************************************************************/

// algo:

	nik_ce auto fasten_algo()
	{
		return cctmp::source
		(
			"fasten out in in1 in2 end2        ;"

			"precycle:                         ;"
			"  end2 = pre_end2_next end2       ;"
			"   out = pre_out_next out         ;"
			"   in1 = pre_in1_next in1         ;"
			"   in2 = pre_in2_next in2         ;"

			"cycle:                            ;"
			"  test loop_pred in2 end2         ;"
			"  branch postcycle                ;"
			"     . = action_func in1 in2      ;"
			"  !out = mutate_func _            ;"
			"   aux = aux_next out in1 in2     ;"
			"     . = combine_func out in      ;"
			"  !out = mutate_func _            ;"
			"    in = in_next out in aux       ;"
			"   out = out_next out             ;"
			"   in1 = in1_next in1             ;"
			"   in2 = in2_next in2             ;"
			"  goto cycle                      ;"

			"postcycle:                        ;"
			"     . = post_action_func in1 in2 ;"
			"  !out = post_mutate_func _       ;"
			"     . = post_combine_func out in ;"
			"  !out = post_mutate_func _       ;"
			"   out = post_out_next out        ;"
			"   in1 = post_in1_next in1        ;"
			"   in2 = post_in2_next in2        ;"
			"  end2 = post_end2_next end2      ;"
			"  return out                      ;"
		);
	}

/***********************************************************************************************************************/

// lookup:

	template
	<
		auto pre_end2_next     = _id_              ,
		auto pre_out_next      = _id_              ,
		auto pre_in1_next      = _id_              ,
		auto pre_in2_next      = _id_              ,
		auto loop_pred         = _equal_           ,
		auto action_func       = _first_           ,
		auto mutate_func       = _assign_          ,
		auto aux_next          = _constant_<false> ,
		auto combine_func      = _first_           ,
		auto in_next           = _constant_<false> ,
		auto out_next          = _increment_<>     ,
		auto in1_next          = _increment_<>     ,
		auto in2_next          = _increment_<>     ,
		auto post_action_func  = _first_           ,
		auto post_mutate_func  = _first_           ,
		auto post_combine_func = _first_           ,
		auto post_out_next     = _id_              ,
		auto post_in1_next     = _id_              ,
		auto post_in2_next     = _id_              ,
		auto post_end2_next    = _id_
	>
	nik_ce auto fasten_frame()
	{
		return cctmp::table
		(
		 	cctmp::U_char,

			cctmp::binding( "pre_end2_next"     , pre_end2_next     ),
			cctmp::binding( "pre_out_next"      , pre_out_next      ),
			cctmp::binding( "pre_in1_next"      , pre_in1_next      ),
			cctmp::binding( "pre_in2_next"      , pre_in2_next      ),
			cctmp::binding( "loop_pred"         , loop_pred         ),
			cctmp::binding( "action_func"       , action_func       ),
			cctmp::binding( "mutate_func"       , mutate_func       ),
			cctmp::binding( "aux_next"          , aux_next          ),
			cctmp::binding( "combine_func"      , combine_func      ),
			cctmp::binding( "in_next"           , in_next           ),
			cctmp::binding( "out_next"          , out_next          ),
			cctmp::binding( "in1_next"          , in1_next          ),
			cctmp::binding( "in2_next"          , in2_next          ),
			cctmp::binding( "post_action_func"  , post_action_func  ),
			cctmp::binding( "post_mutate_func"  , post_mutate_func  ),
			cctmp::binding( "post_combine_func" , post_combine_func ),
			cctmp::binding( "post_out_next"     , post_out_next     ),
			cctmp::binding( "post_in1_next"     , post_in1_next     ),
			cctmp::binding( "post_in2_next"     , post_in2_next     ),
			cctmp::binding( "post_end2_next"    , post_end2_next    )
		);
	};

	template<auto... Vs>
	nik_ce auto fasten_lookup = cctmp::make_frame<fasten_frame<Vs...>>;

/***********************************************************************************************************************/

// arg:

	template<auto lookup>
	struct T_fasten
	{
		template
		<
			typename OutType, typename AuxType, typename InType,
			typename CarInType, typename CdrInType, typename EndType
		>
		nik_ces auto result(OutType o, AuxType a, InType i, CarInType i1, CdrInType i2, EndType e2)
			{ return cctmp::generic_assembly_apply<fasten_algo, OutType, lookup>(o, i, i1, i2, e2); }

	}; template<auto lookup>
		nik_ce auto _fasten_ = U_store_T<T_fasten<lookup>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// glide (bifold):

/***********************************************************************************************************************/

// algo:

	nik_ce auto glide_algo()
	{
		return cctmp::source
		(
			"glide out in1 in2 end2            ;"

			"precycle:                         ;"
			"  end2 = pre_end2_next end2       ;"
			"   in1 = pre_in1_next in1         ;"
			"   in2 = pre_in2_next in2         ;"

			"cycle:                            ;"
			"  test loop_pred in2 end2         ;"
			"  branch postcycle                ;"
			"     . = action_func in1 in2      ;"
			"   out = combine_func out _       ;"
			"   in1 = in1_next in1             ;"
			"   in2 = in2_next in2             ;"
			"  goto cycle                      ;"

			"postcycle:                        ;"
			"     . = post_action_func in1 in2 ;"
			"   out = post_combine_func out _  ;"
			"   in1 = post_in1_next in1        ;"
			"   in2 = post_in2_next in2        ;"
			"  end2 = post_end2_next end2      ;"
			"  return out                      ;"
		);
	}

/***********************************************************************************************************************/

// lookup:

	template
	<
		auto pre_end2_next     = _id_          ,
		auto pre_in1_next      = _id_          ,
		auto pre_in2_next      = _id_          ,
		auto loop_pred         = _equal_       ,
		auto action_func       = _first_       ,
		auto combine_func      = _first_       ,
		auto in1_next          = _increment_<> ,
		auto in2_next          = _increment_<> ,
		auto post_action_func  = _first_       ,
		auto post_combine_func = _first_       ,
		auto post_in1_next     = _id_          ,
		auto post_in2_next     = _id_          ,
		auto post_end2_next    = _id_
	>
	nik_ce auto glide_frame()
	{
		return cctmp::table
		(
		 	cctmp::U_char,

			cctmp::binding( "pre_end2_next"     , pre_end2_next     ),
			cctmp::binding( "pre_in1_next"      , pre_in1_next      ),
			cctmp::binding( "pre_in2_next"      , pre_in2_next      ),
			cctmp::binding( "loop_pred"         , loop_pred         ),
			cctmp::binding( "action_func"       , action_func       ),
			cctmp::binding( "combine_func"      , combine_func      ),
			cctmp::binding( "in1_next"          , in1_next          ),
			cctmp::binding( "in2_next"          , in2_next          ),
			cctmp::binding( "post_action_func"  , post_action_func  ),
			cctmp::binding( "post_combine_func" , post_combine_func ),
			cctmp::binding( "post_in1_next"     , post_in1_next     ),
			cctmp::binding( "post_in2_next"     , post_in2_next     ),
			cctmp::binding( "post_end2_next"    , post_end2_next    )
		);
	};

	template<auto... Vs>
	nik_ce auto glide_lookup = cctmp::make_frame<glide_frame<Vs...>>;

/***********************************************************************************************************************/

// arg:

	template<auto lookup>
	struct T_glide
	{
		template<typename OutType, typename CarInType, typename CdrInType, typename EndType>
		nik_ces auto result(OutType o, CarInType i1, CdrInType i2, EndType e2)
			{ return cctmp::generic_assembly_apply<glide_algo, OutType, lookup>(o, i1, i2, e2); }

	}; template<auto lookup>
		nik_ce auto _glide_ = U_store_T<T_glide<lookup>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp_chord

