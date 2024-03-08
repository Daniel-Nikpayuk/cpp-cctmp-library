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

// chord progression.

namespace chord {

	// This grammar is currently experimental.

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

//	#define NIK_UNIT_TEST_REPEAT_V0
//	#define NIK_UNIT_TEST_MAP_V0
//	#define NIK_UNIT_TEST_VEC_SUM_V0
//	#define NIK_UNIT_TEST_ARRAY_ADD_V0
	#define NIK_UNIT_TEST_FOLD_V0
//	#define NIK_UNIT_TEST_DOT_PRODUCT_V0
//	#define NIK_UNIT_TEST_CONVOLUTION_V0
//	#define NIK_UNIT_TEST_FIND_V0
//	#define NIK_UNIT_TEST_SIFT_V0
//	#define NIK_UNIT_TEST_CHANGE_OF_BASE_PRINTER_V0
//	#define NIK_UNIT_TEST_ARRAY_PRINTER_V0

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// progressions:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// square:

	struct T_square
	{
		template<typename T>
		constexpr static auto result(T x) { return (x * x); }

	}; constexpr auto _square_ = U_store_T<T_square>;

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
		constexpr auto _carry_add_ = U_store_T<T_carry_add<radix>>;

/***********************************************************************************************************************/

// divide by:

	template<auto V>
	struct T_divide_by
	{
		template<typename T>
		constexpr static auto result(T v) { return (v / V); }

	}; template<auto V>
		constexpr auto _divide_by_ = U_store_T<T_divide_by<V>>;

/***********************************************************************************************************************/

// modulo by:

	template<auto V>
	struct T_modulo_by
	{
		template<typename T>
		constexpr static auto result(T v) { return (v % V); }

	}; template<auto V>
		constexpr auto _modulo_by_ = U_store_T<T_modulo_by<V>>;

/***********************************************************************************************************************/

// printer:

	struct T_print
	{
		template<typename T0, typename T1>
		constexpr static void result(T0 v0, T1 v1) { printf(v1, v0); }

	}; constexpr auto _print_ = U_store_T<T_print>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// repeat:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _repeat_v0()
	{
		return source
		(
			"f out end in                     ;"

			"definitions:                     ;"
			" arr_repeat # repeat<@ @||>[,){} ;"

			"body:                            ;"
			" . = arr_repeat !out end in      ;"
			" return _                        ;"
		);
	}

#ifdef NIK_UNIT_TEST_REPEAT_V0

	template<typename Out, typename End, typename In>
	constexpr auto repeat_v0(Out out, End end, In in)
		{ return chord_apply<_repeat_v0, null_env, Out>(out, end, in); }

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// map:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _map_v0()
	{
		return source
		(
			"f out in end                  ;"

			"definitions:                  ;"
			" arr_map # map<square||>[)[,) ;"

			"body:                         ;"
			" . = arr_map !out in end      ;"
			" return _                     ;"

			, cctmp::binding( "square" , _square_ )
		);
	}

#ifdef NIK_UNIT_TEST_MAP_V0

	template<typename Out, typename In, typename End>
	constexpr auto map_v0(Out out, In in, End end)
		{ return chord_apply<_map_v0, null_env, Out>(out, in, end); }

#endif

/***********************************************************************************************************************/

// vector sum:

	constexpr auto _vec_sum_v0()
	{
		return source
		(
			"f out in end in1             ;"

			"definitions:                 ;"
			" vec_sum # map<add||>[)[,)[) ;"

			"body:                        ;"
			" . = vec_sum !out in end in1 ;"
			" return _                    ;"
		);
	}

#ifdef NIK_UNIT_TEST_VEC_SUM_V0

	template<typename Out, typename In, typename End, typename In1>
	constexpr auto vec_sum_v0(Out out, In in, End end, In1 in1)
		{ return chord_apply<_vec_sum_v0, null_env, Out>(out, in, end, in1); }

#endif

/***********************************************************************************************************************/

// array add:

	constexpr auto _array_add_v0()
	{
		return source
		(
			"f out in end in1 aux                       ;"

			"definitions:                               ;"
			" arr_add # map<carry_add * * @||>[][,][]{} ;"

			"body:                                      ;"
			" . = arr_add !out in end in1 !aux          ;"
			" return _                                  ;"

			, cctmp::binding( "carry_add" , _carry_add_<> )
		);
	}

#ifdef NIK_UNIT_TEST_ARRAY_ADD_V0

	template<typename Out, typename In, typename End, typename In1, typename Aux>
	constexpr auto array_add_v0(Out out, In in, End end, In1 in1, Aux aux)
		{ return chord_apply<_array_add_v0, null_env, Out>(out, in, end, in1, &aux); }

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _fold_v0()
	{
		return source
		(
			"f out in end                     ;"

			"definitions:                     ;"
			" arr_fold # fold<@ @|add||>{}[,) ;"

			"body:                            ;"
			" . = arr_fold !out in end        ;"
			" return _                        ;"
		);
	}

#ifdef NIK_UNIT_TEST_FOLD_V0

	template<typename Out, typename In, typename End>
	constexpr auto fold_v0(Out out, In in, End end)
		{ return (Out) *chord_apply<_fold_v0, null_env, Out*>(&out, in, end); }

#endif

/***********************************************************************************************************************/

// dot product:

	constexpr auto _dot_product_v0()
	{
		return source
		(
			"f out in end in1                            ;"

			"definitions:                                ;"
			" dot_prod # fold<multiply|add * @||>{}[,)[) ;"

			"body:                                       ;"
			" . = dot_prod !out in end in1               ;"
			" return _                                   ;"
		);
	}

#ifdef NIK_UNIT_TEST_DOT_PRODUCT_V0

	template<typename Out, typename In, typename End, typename In1>
	constexpr auto dot_product_v0(Out out, In in, End end, In1 in1)
		{ return (Out) *chord_apply<_dot_product_v0, null_env, Out*>(&out, in, end, in1); }

#endif

/***********************************************************************************************************************/

// convolution:

	// convolution (generic assembly equivalent):

	//	return source
	//	(
	//		"conv out in end in1                  ;"

	//		"definitions:                         ;"
	//		" action   # subpose[2]{multiply * *} ;"
	//		" combine  # subpose[2]{add * @}      ;"
	//		" mutate   # subpose[2]{appoint @ @}  ;"
	//		" pred     # subpose[2]{equal @ @}    ;"
	//		" in_next  # decrement                ;"
	//		" in1_next # increment                ;"

	//		"precycle:                            ;"
	//		" in = in_next in                     ;"

	//		"cycle:                               ;"
	//		" test pred in end                    ;"
	//		" branch postcycle                    ;"
	//		" . = action in in1                   ;"
	//		" . = combine out _                   ;"
	//		" void mutate out _                   ;"
	//		" in  = in_next in                    ;"
	//		" in1 = in1_next in1                  ;"
	//		" goto cycle                          ;"

	//		"postcycle:                           ;"
	//		" . = action in in1                   ;"
	//		" . = combine out _                   ;"
	//		" void mutate out _                   ;"
	//		" return out                          ;"
	//	);

	// functions required:

		// preiterate: in_next
		// pred: subpose
		// primary: action, combine, mutate
		// iterate: in_next, in1_next
		// postiterate: nop

		// iterate requires side effects because we're calling it within a loop.
		// with the exception of pred, we can make all of these to be void functions
		// that we call within a constructed fold function.

		// we can create all iterate functions and hold them in a list for reference.
		// actually we don't need to hold the constructed functions in a list,
		// we can record keep the respective subpose locations during parsing.

		// when we pass variadic args to these functions, do we turn them all into
		// pointers? or const references?

	//	return source
	//	(
	//		"conv out in end in1                  ;"

	//		"definitions:                         ;"
	//		" action   # subpose[2]{multiply * *} ;"
	//		" combine  # subpose[2]{add * @}      ;"
	//		" mutate   # subpose[2]{appoint @ @}  ;"
	//		" pred     # subpose[2]{equal @ @}    ;"
	//		" in_next  # decrement                ;"
	//		" in1_next # increment                ;"

	//		"precycle:                            ;"
	//		" void preiterate in                  ;" // AN::cycle, AT::void_f

	//		"cycle:                               ;"
	//		" test pred in end                    ;" // AN::loop, AT::cycle
	//		" branch postcycle                    ;"
	//		" void primary out in in1             ;" // from: AN::cycle, AT::cons_f		// one cons_f
	//		" void iterate in in1                 ;" // from: AN::cycle, AT::cons_f		// or two?
	//		" goto cycle                          ;"

	//		"postcycle:                           ;"
	//		" void primary out in in1             ;" // AN::cycle, AT::void_f
	//		" return out                          ;"
	//	);

		// it makes sense to add AN::cycle to the assembly machines
		// as we are going to design for tail call optimizations anyway.
		// or do we want to add it to cycle machines, and then have
		// other cycle machines to call cycle machines?
		// but then if cycle machines can create iterate(s),
		// we can just streamline pre/post-iterate without calling,
		// which would be acceptable.

		// sometimes we call the cycle machine, sometimes we cons it.

		// we should be creating subcontrollers and referencing them
		// when we can rather than creating cons_f objects.
		// only make cons_f objects when you're required
		// to store them within the main variadic args.

/***********************************************************************************************************************/

// convolution:

	constexpr auto _convolution_v0()
	{
		return source
		(
			"f out in end in1                           ;"

			"definitions:                               ;"
			" conv # fold<multiply|add * @||>{}(-|+,][] ;"

			"body:                                      ;"
			" . = conv !out end in in1                  ;"
			" return _                                  ;"
		);
	}

#ifdef NIK_UNIT_TEST_CONVOLUTION_V0

	template<typename Out, typename In, typename End, typename In1>
	constexpr auto convolution_v0(Out out, In in, End end, In1 in1)
		{ return (Out) *chord_apply<_convolution_v0, null_env, Out*>(&out, in, end, in1); }

#endif

/*
		//	" mult_atoi # subpose[2]{multiply atoi atoi}         ;"
		//	" conv      # fold[2]{mult_atoi|add * @||}<>(-|+,][] ;"

		//	, binding("atoi", _atoi_)

	constexpr auto _convolution_v0()
	{
		return source
		(
			"main out in end in1                               ;"

			"vars:                                             ;"
			"  declare conv                                    ;"

			"defs:                                             ;"
			"  conv # fold[1]{add * @|multiply||} <> (-|+,] [] ;"

			"body:                                             ;"
			"  . = conv !out end in in1                        ;"
			"  return _                                        ;"
		);
	}

	template<typename Out, typename In, typename End, typename In1>
	constexpr auto convolution_v0(Out out, In in, End end, In1 in1)
		{ return (Out) *chord::chord_apply<_convolution_v0, null_env, Out*>(&out, in, end, in1); }
*/

	constexpr auto _chord_test_func()
	{
		return source
		(
			"main out in end in1                                  ;" // [] - closed, acts on both endpoints.

			"vars:                                                ;" // (] - opening, acts on right endpoint.
			"  declare conv                                       ;" // () - open, acts on neither endpoint.

			"defs:                                                ;" // [) - closing, acts on left endpoint.
			"  conv # fold[1]{add * @|multiply||}  <>  (-|+,]  [] ;"
		//     					       |   |       |
		//     					       |   |       ---- [in1] is a tone interval.
		//     					       |   ------------ (end, in] is the root reverse interval.
		//     					       ---------------- <out> is the tonic fixed interval.

			"body:                                                ;"
			"  . = conv !out end in in1                           ;"
			"  return _                                           ;"
		);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _find_v0()
	{
		return source
		(
			"f out in end                  	  ;"

			"definitions:                  	  ;"
			" arr_find # find<lt_five||>[)[,) ;"

			"body:                            ;"
			" . = arr_find !out in end        ;"
			" return _                        ;"

			, cctmp::binding( "lt_five" , cctmp::_is_less_than_<5> )
		);
	}

#ifdef NIK_UNIT_TEST_FIND_V0

	template<typename Out, typename In, typename End>
	constexpr auto find_v0(Out out, In in, End end)
		{ return chord_apply<_find_v0, null_env, Out>(out, in, end); }

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sift:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _sift_v0()
	{
		return source
		(
			"f out in end                  	  ;"

			"definitions:                  	  ;"
			" arr_sift # sift<lt_five||>[)[,) ;"

			"body:                            ;"
			" . = arr_sift !out in end        ;"
			" return _                        ;"

			, cctmp::binding( "lt_five" , cctmp::_is_less_than_<5> )
		);
	}

#ifdef NIK_UNIT_TEST_SIFT_V0

	template<typename Out, typename In, typename End>
	constexpr auto sift_v0(Out out, In in, End end)
		{ return chord_apply<_sift_v0, null_env, Out>(out, in, end); }

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// progressions:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// change of base printer:

/***********************************************************************************************************************/

// version 0:

	template<auto n>
	constexpr auto _change_of_base_printer_v0()
	{
		return source
		(
			"cob out in format                           ;"

			"definitions:                                ;"
			" arr_map # map<rem_by_n @||>[)[div_by_n|~,) ;"
			" arr_pr  # repeat<@ @|print * @|>(-|+,]{}   ;"

			"body:                                       ;"
			" . = arr_map !out in zero                   ;"
			" . = arr_pr _ out format                    ;"
			" return _                                   ;"

			, cctmp::binding( "div_by_n" , _divide_by_<n> )
			, cctmp::binding( "rem_by_n" , _modulo_by_<n> )
			, cctmp::binding( "print"    , _print_        )
			, cctmp::binding( "zero"     , 0              )
		);
	}

#ifdef NIK_UNIT_TEST_CHANGE_OF_BASE_PRINTER_V0

	template<auto n, typename Out, typename In>
	constexpr void change_of_base_printer_v0(const char *f, Out out, In in)
	{
		chord_apply<_change_of_base_printer_v0<n>, null_env, Out>(out, in, f);
		printf("\n");
	}

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array printer:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _array_printer_v0()
	{
		return source
		(
			"f out end format                           ;"

			"definitions:                               ;"
			" arr_zero # repeat<@ @||>[,){}             ;"
			" arr_pr   # repeat<@ @|print * @|>(-|+,]{} ;"

			"body:                                      ;"
			" . = arr_zero !out end zero                ;"
			" . = arr_pr _ out format                   ;"
			" return _                                  ;"

			, cctmp::binding( "print" , _print_ )
			, cctmp::binding( "zero"  , 0       )
		);
	}

#ifdef NIK_UNIT_TEST_ARRAY_PRINTER_V0

	template<typename Out, typename End>
	constexpr void array_printer_v0(const char *in, Out out, End end)
		{ chord_apply<_array_printer_v0, null_env, Out>(out, end, in); }

#endif

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

