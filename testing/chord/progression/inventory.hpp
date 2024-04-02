/************************************************************************************************************************
**
** Copyright 2022-2024 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// inventory:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// quality:

/***********************************************************************************************************************/

	// Terminology borrowed from { western } music theory:

		// (keeping the left endpoint fixed as closed)

			//      major chord: [root, major 3rd); [perfect 5th) --- [root, tonic); [tone)
			//      minor chord: [root, minor 3rd]; [perfect 5th) --- [root, tonic]; [tone)

			// diminished chord: [root, minor 3rd]; [tritone    ] --- [root, tonic]; [tone]
			//  augmented chord: [root, major 3rd); [minor 6th  ] --- [root, tonic); [tone]

	// by interval:

		// { root, tonic ) ; { tone ) ---      major chord // aligns center
		// { root, tonic ) ; { tone ] ---  augmented chord // aligns left

		// { root, tonic ] ; { tone ] --- diminished chord // aligns center
		// { root, tonic ] ; { tone ) ---      minor chord // aligns right

	// by quality:

		//      major chord --- { root, tonic ) ; { tone ) // aligns centre
		//  augmented chord --- { root, tonic ) ; { tone ] // aligns left

		// diminished chord --- { root, tonic ] ; { tone ] // aligns centre
		//      minor chord --- { root, tonic ] ; { tone ) // aligns right

	//	0. All intervals are tethered to the one with an explicitly declared endpoint.
	//	1. If prev and peek, reverse iterate end precycle.
	//	2. For each left endpoint, if open, iterate precycle.
	//	3. Evaluate the common (closing) loop, peeking if necessary.
	//	4. If the subject iterator is right closed, then assign postcycle.
	//	5. If (4), then for each other right endpoint, when open, iterate postcycle.
	//	6. If prev and peek, iterate end to reset postcycle.

// symbols:

	// available functional operators: { repeat, map, fold, find, sift }
	// special characters            :    ~!@#$%^&*()_+`-={}|[]\:";'<>?,./
	// disallowed                    :    "
	// already used                  :    !_#=:;'.
	// chord reserved                :    <>{}[](),^@*+-|~
	// remaining                     :    $%&`\?/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// prerequisites:

/***********************************************************************************************************************/

// square:

	struct T_square
	{
		template<typename T>
		constexpr static auto result(T x) { return (x * x); }

	}; constexpr auto _square_ = cctmp::U_store_T<T_square>;

/***********************************************************************************************************************/

// carry:

	template<auto radix>
	struct T_carry_add
	{
		template<typename In, typename In1, typename Carry>
		constexpr static auto result(In in, In1 in1, Carry carry)
		{
			auto val = (in + in1 + *carry) % radix;
			*carry   = (val < in);

			return val;
		}

	}; template<auto radix = 10>
		constexpr auto _carry_add_ = cctmp::U_store_T<T_carry_add<radix>>;

/***********************************************************************************************************************/

// divide by:

	template<auto V>
	struct T_divide_by
	{
		template<typename T>
		constexpr static auto result(T v) { return (v / V); }

	}; template<auto V>
		constexpr auto _divide_by_ = cctmp::U_store_T<T_divide_by<V>>;

/***********************************************************************************************************************/

// modulo by:

	template<auto V>
	struct T_modulo_by
	{
		template<typename T>
		constexpr static auto result(T v) { return (v % V); }

	}; template<auto V>
		constexpr auto _modulo_by_ = cctmp::U_store_T<T_modulo_by<V>>;

/***********************************************************************************************************************/

// print:

	struct T_print
	{
		template<typename T> // non void return is temporary.
		constexpr static auto result(T v) { printf("%s", v.origin()); return 0; }

		template<typename T, typename Fmt> // non void return is temporary.
		constexpr static auto result(T v, Fmt fmt) { printf(fmt.origin(), v); return 0; }

	}; constexpr auto _print_ = cctmp::U_store_T<T_print>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// repeat:

/***********************************************************************************************************************/

// initialize:

	// v0:

		constexpr auto _chord_initialize_v0()
		{
			return cctmp::source
			(
				"main out end in                    ;"

				"vars:                              ;"
				"  declare arr_init                 ;"

				"defs:                              ;"
				"  arr_init # repeat[1]{@ @||}[,)<> ;"

				"body:                              ;"
				"  . = arr_init !out end in         ;"
				"  return _                         ;"
			);
		}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// map:

/***********************************************************************************************************************/

// array square:

	// v0:

		constexpr auto _chord_array_square_v0()
		{
			return cctmp::source
			(
				"main out in end                  ;"

				"vars:                            ;"
				"  declare arr_sq                 ;"

				"defs:                            ;"
				"  arr_sq # map[1]{square||}[)[,) ;"

				"body:                            ;"
				"  . = arr_map !out in end        ;"
				"  return _                       ;"

				, cctmp::binding( "square" , _square_ )
			);
		}

/***********************************************************************************************************************/

// vector add:

	// v0:

		constexpr auto _chord_vector_add_v0()
		{
			return cctmp::source
			(
				"main out in end in1              ;"

				"vars:                            ;"
				"  declare vec_add                ;"

				"defs:                            ;"
				"  vec_add # map[2]{add||}[)[,)[) ;"

				"body:                            ;"
				"  . = vec_add !out in end in1    ;"
				"  return _                       ;"
			);
		}

/***********************************************************************************************************************/

// array add:

	// v0:

		constexpr auto _chord_array_add_v0()
		{
			return cctmp::source
			(
				"main out in end in1 aux                        ;"

				"vars:                                          ;"
				"  declare arr_add                              ;"

				"defs:                                          ;"
				"  arr_add # map[3]{carry_add * * @||}[][,][]<> ;"

				"body:                                          ;"
				"  . = arr_add !out in end in1 !aux             ;"
				"  return _                                     ;"

				, cctmp::binding( "carry_add" , _carry_add_<> )
			);
		}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/

// sum:

	// v0:

		constexpr auto _chord_sum_v0()
		{
			return cctmp::source
			(
				"main out in end                     ;"

				"vars:                               ;"
				"  declare sum                       ;"

				"defs:                               ;"
				"  sum # fold[1]{add * @|@ @||}<>[,] ;"

				"body:                               ;"
				"  . = sum !out in end               ;"
				"  return _                          ;"
			);
		}

/***********************************************************************************************************************/

// dot product:

	// v0:

		constexpr auto _chord_dot_product_v0()
		{
			return cctmp::source
			(
				"main out in end in1                             ;"

				"vars:                                           ;"
				"  declare dot_prod                              ;"

				"defs:                                           ;"
				"  dot_prod # fold[2]{add * @|multiply||}<>[,)[) ;"

				"body:                                           ;"
				"  . = dot_prod !out in end in1                  ;"
				"  return _                                      ;"
			);
		}

/***********************************************************************************************************************/

// convolution:

	// v0:

		constexpr auto _chord_convolution_v0()
		{
			return cctmp::source
			(
				"main out in end in1                            ;"

				"vars:                                          ;"
				"  declare conv                                 ;"

				"defs:                                          ;"
				"  conv # fold[2]{add * @|multiply||}<>(-|+,][] ;"

				"body:                                          ;"
				"  . = conv !out end in in1                     ;"
				"  return _                                     ;"
			);
		}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find:

/***********************************************************************************************************************/

// first less than five:

	// v0:

		constexpr auto _chord_first_less_than_five_v0()
		{
			return cctmp::source
			(
				"main out in end                      ;"

				"vars:                                ;"
				"  declare arr_find                   ;"

				"definitions:                  	      ;"
				"  arr_find # find[1]{lt_five||}<>[,) ;"

				"body:                                ;"
				"  . = arr_find !out in end           ;"
				"  return _                           ;"

				, cctmp::binding( "lt_five" , cctmp::_is_less_than_<5> )
			);
		}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sift:

/***********************************************************************************************************************/

// all less than five:

	// v0:

		constexpr auto _chord_all_less_than_five_v0()
		{
			return cctmp::source
			(
				"main out in end                      ;"

				"vars:                                ;"
				"  declare arr_sift                   ;"

				"defs:                                ;"
				"  arr_sift # sift[1]{lt_five||}<>[,) ;"

				"body:                                ;"
				"  . = arr_sift !out in end           ;"
				"  return _                           ;"

				, cctmp::binding( "lt_five" , cctmp::_is_less_than_<5> )
			);
		}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// progressions:

/***********************************************************************************************************************/

// change of base printer:

	// v0:

		template<auto radix>
		constexpr auto _chord_change_of_base_printer_v0()
		{
			return cctmp::source
			(
				"main out in                                       ;"

				"vars:                                             ;"
				"  declare arr_map arr_pr                          ;"

				"defs:                                             ;"
				"  arr_map # map[1]{rem_by_n @||} [) [div_by_n|~,) ;"
				"  arr_pr  # repeat[1]{@ @|print * @|} (-|+,] <>   ;"

				"body:                                             ;"
				"  . = arr_map !out in 0                           ;"
				"  . = arr_pr _ out format                         ;"
				"  return _                                        ;"

				, cctmp::binding( "print"    , _print_                  )
				, cctmp::binding( "div_by_n" , _divide_by_<radix>       )
				, cctmp::binding( "rem_by_n" , _modulo_by_<radix>       )
				, cctmp::binding( "format"   , cctmp::strlit_type{"%d"} )
			);
		}

/***********************************************************************************************************************/

// array printer:

	// v0:

		constexpr auto _chord_array_printer_v0()
		{
			return cctmp::source
			(
				"main out end format                            ;"

				"vars:                                          ;"
				"  declare arr_zero arr_pr                      ;"

				"defs:                                          ;"
				"  arr_zero # repeat[1]{@ @||}[,)<>             ;"
				"  arr_pr   # repeat[1]{@ @|print * @|}(-|+,]<> ;"

				"body:                                          ;"
				"  . = arr_zero !out end 0                      ;"
				"  . = arr_pr _ out format                      ;"
				"  return _                                     ;"

				, cctmp::binding( "print" , _print_ )
			);
		}

/***********************************************************************************************************************/

// set printer:

	// v0:

		constexpr auto _chord_set_printer_v0()
		{
			return cctmp::source
			(
				"main out last                                  ;"

				"vars:                                          ;"
				"  declare arr_print                            ;"

				"defs:                                          ;"
				"  arr_print # repeat[1]{@ @|print * @|} [,) <> ;"

				"body:                                          ;"
				"  void print beg_fmt                           ;"
				"  . = arr_print out last arr_fmt               ;"
				"  . = dereference _                            ;"
				"  void print _ end_fmt                         ;"

				"  return last                                  ;"

				, cctmp::binding( "print"   , _print_                      )
				, cctmp::binding( "beg_fmt" , cctmp::strlit_type{" { "}    )
				, cctmp::binding( "arr_fmt" , cctmp::strlit_type{"%d, "}   )
				, cctmp::binding( "end_fmt" , cctmp::strlit_type{"%d }\n"} )
			);
		}

