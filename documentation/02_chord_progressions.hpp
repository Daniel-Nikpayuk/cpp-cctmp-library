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

	template<typename Out, typename End, typename In>
	constexpr auto repeat_v0(Out out, End end, In in)
		{ return metapiler_apply<_repeat_v0, null_env, Out>(out, end, in); }

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

	template<typename Out, typename In, typename End>
	constexpr auto map_v0(Out out, In in, End end)
		{ return metapiler_apply<_map_v0, null_env, Out>(out, in, end); }

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

	template<typename Out, typename In, typename End, typename In1>
	constexpr auto vec_sum_v0(Out out, In in, End end, In1 in1)
		{ return metapiler_apply<_vec_sum_v0, null_env, Out>(out, in, end, in1); }

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

	template<typename Out, typename In, typename End, typename In1, typename Aux>
	constexpr auto array_add_v0(Out out, In in, End end, In1 in1, Aux aux)
		{ return metapiler_apply<_array_add_v0, null_env, Out>(out, in, end, in1, &aux); }

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

	template<typename Out, typename In, typename End>
	constexpr auto fold_v0(Out out, In in, End end)
		{ return (Out) *metapiler_apply<_fold_v0, null_env, Out*>(&out, in, end); }

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

	template<typename Out, typename In, typename End, typename In1>
	constexpr auto dot_product_v0(Out out, In in, End end, In1 in1)
		{ return (Out) *metapiler_apply<_dot_product_v0, null_env, Out*>(&out, in, end, in1); }

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

	template<typename Out, typename In, typename End, typename In1>
	constexpr auto convolution_v0(Out out, In in, End end, In1 in1)
		{ return (Out) *metapiler_apply<_convolution_v0, null_env, Out*>(&out, in, end, in1); }

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

	template<typename Out, typename In, typename End>
	constexpr auto find_v0(Out out, In in, End end)
		{ return metapiler_apply<_find_v0, null_env, Out>(out, in, end); }

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

	template<typename Out, typename In, typename End>
	constexpr auto sift_v0(Out out, In in, End end)
		{ return metapiler_apply<_sift_v0, null_env, Out>(out, in, end); }

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

	template<auto n, typename Out, typename In>
	constexpr void change_of_base_printer_v0(const char *f, Out out, In in)
	{
		metapiler_apply<_change_of_base_printer_v0<n>, null_env, Out>(out, in, f);
		printf("\n");
	}

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

	template<typename Out, typename End>
	constexpr void array_printer_v0(const char *in, Out out, End end)
		{ metapiler_apply<_array_printer_v0, null_env, Out>(out, end, in); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

