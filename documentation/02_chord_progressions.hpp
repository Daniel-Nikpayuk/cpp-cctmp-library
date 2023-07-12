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

	// available functional operators: { repeat, map, fold, find_first, find_all, zip, fasten, glide }
	// special characters            :    ~!@#$%^&*()_+`-={}|[]\:";'<>?,./
	// disallowed                    :    "
	// already used                  :    !_#=:;'.
	// chord reserved                :    <>{}[](),@*+-|~
	// remaining                     :    $%^&`\?/

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

	struct T_carry_add
	{
		template<typename T0, typename T1>
		constexpr static auto result(T0 v0, T1 v1) { return cctmp::pair(v0 + v1, v0); }

	}; constexpr auto _carry_add_ = U_store_T<T_carry_add>;

	template<auto b>
	struct T_carry_cons
	{
		template<typename C, typename P>
		constexpr static auto result(C c, P p)
		{
			auto nc = (c + p.v0) % b;

			return cctmp::pair(nc, (nc < p.v1));
		}

	}; template<auto b = 10>
		constexpr auto _carry_cons_ = U_store_T<T_carry_cons<b>>;

	struct T_carry_car
	{
		template<typename P>
		constexpr static auto result(P p) { return p.v0; }

	}; constexpr auto _carry_car_ = U_store_T<T_carry_car>;

	struct T_carry_cdr
	{
		template<typename P>
		constexpr static auto result(P p) { return p.v1; }

	}; constexpr auto _carry_cdr_ = U_store_T<T_carry_cdr>;

/***********************************************************************************************************************/

// custom:

	constexpr auto custom_machine_frame_callable()
	{
		return cctmp::frame
		(
			cctmp::U_char,

			cctmp::binding( "c_five"     , cctmp::_constant_<5>     ),
			cctmp::binding( "lt_five"    , cctmp::_is_less_than_<5> ),

			cctmp::binding( "square"     , _square_          ),
			cctmp::binding( "carry_add"  , _carry_add_       ),
			cctmp::binding( "carry_cons" , _carry_cons_<>    ),
			cctmp::binding( "carry_car"  , _carry_car_       ),
			cctmp::binding( "carry_cdr"  , _carry_cdr_       )
		);
	};

	constexpr auto custom_machine_frame = _static_callable_<custom_machine_frame_callable>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// repeat:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _repeat_v0()
	{
		return chord::source
		(
			"f out end in                        ;"

			"definitions:                        ;"
			" arr_repeat # repeat<c_five||>[,){} ;"

			"body:                               ;"
			" . = arr_repeat !out end in         ;"
			" return _                           ;"
		);
	}

	template<typename Out, typename End, typename In>
	constexpr auto repeat_v0(Out out, End end, In in)
	{
		constexpr auto e0 = chord::env<custom_machine_frame>;

		return chord::metapiler_apply<_repeat_v0, e0, Out>(out, end, in);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fold:

/***********************************************************************************************************************/

// version 0 (full options):

	constexpr auto _fold_v0()
	{
		return chord::source
		(
			"f out in end                                              ;"

			"definitions:                                              ;"
			" arr_fold # fold<add * *|appoint @ @|not_equal @ @>{}[+,) ;"

			"body:                                                     ;"
			" . = arr_fold !out in end                                 ;"
			" return _                                                 ;"
		);
	}

	template<typename Out, typename In, typename End>
	constexpr auto fold_v0(Out out, In in, End end)
		{ return (Out) *chord::metapiler_apply<_fold_v0, chord::env<>, Out*>(&out, in, end); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// find:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _find_v0()
	{
		return chord::source
		(
			"f out in end                  	  ;"

			"definitions:                  	  ;"
			" arr_find # find<lt_five||>[)[,) ;"

			"body:                            ;"
			" . = arr_find !out !in end       ;"
			" return _                        ;"
		);
	}

	template<typename Out, typename In, typename End>
	constexpr auto find_v0(Out out, In in, End end)
	{
		constexpr auto e0 = chord::env<custom_machine_frame>;

		return chord::metapiler_apply<_find_v0, e0, Out>(out, in, end);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sift:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _sift_v0()
	{
		return chord::source
		(
			"f out in end                  	  ;"

			"definitions:                  	  ;"
			" arr_sift # sift<lt_five||>[)[,) ;"

			"body:                            ;"
			" . = arr_sift !out !in end       ;"
			" return _                        ;"
		);
	}

	template<typename Out, typename In, typename End>
	constexpr auto sift_v0(Out out, In in, End end)
	{
		constexpr auto e0 = chord::env<custom_machine_frame>;

		return chord::metapiler_apply<_sift_v0, e0, Out>(out, in, end);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// map:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _map_v0()
	{
		return chord::source
		(
			"f out in end                   ;"

			"definitions:                   ;"
			" arr_map  # map<square||>[)[,) ;"

			"body:                          ;"
			" . = arr_map !out in end       ;"
			" return _                      ;"
		);
	}

	template<typename Out, typename In, typename End>
	constexpr auto map_v0(Out out, In in, End end)
	{
		constexpr auto e0 = chord::env<custom_machine_frame>;

		return chord::metapiler_apply<_map_v0, e0, Out>(out, in, end);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// zip:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _vec_sum_v0()
	{
		return chord::source
		(
			"f out in1 in2 end2             ;"

			"definitions:                   ;"
			" vec_sum # zip<add||>[)[)[,)   ;"

			"body:                          ;"
			" . = vec_sum !out in1 in2 end2 ;"
			" return _                      ;"
		);
	}

	template<typename Out, typename In1, typename In2, typename End2>
	constexpr auto vec_sum_v0(Out out, In1 in1, In2 in2, End2 end2)
		{ return chord::metapiler_apply<_vec_sum_v0, chord::env<>, Out>(out, in1, in2, end2); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// glide:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _dot_product_v0()
	{
		return chord::source
		(
			"f out in1 in2 end2                           ;"

			"definitions:                                 ;"
			" dot_prod # glide<multiply|add * @||>{}[)[,) ;"

			"body:                                        ;"
			" . = dot_prod !out in1 in2 end2              ;"
			" return _                                    ;"
		);
	}

	template<typename Out, typename In1, typename In2, typename End2>
	constexpr auto dot_product_v0(Out out, In1 in1, In2 in2, End2 end2)
		{ return (Out) *chord::metapiler_apply<_dot_product_v0, chord::env<>, Out*>(&out, in1, in2, end2); }

/***********************************************************************************************************************/

// version 0:

	constexpr auto _convolution_v0()
	{
		return chord::source
		(
			"f out in1 in2 end2                             ;"

			"definitions:                                   ;"
			" conv # glide<multiply|add * @||>{}[](-|+,-|+] ;"

			"body:                                          ;"
			" . = conv !out in1 end2 in2                    ;"
			" return _                                      ;"
		);
	}

	template<typename Out, typename In1, typename In2, typename End2>
	constexpr auto convolution_v0(Out out, In1 in1, In2 in2, End2 end2)
		{ return (Out) *chord::metapiler_apply<_convolution_v0, chord::env<>, Out*>(&out, in1, in2, end2); }

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// fasten:

/***********************************************************************************************************************/

// version 0:

	constexpr auto _array_add_v0()
	{
		return chord::source
		(
			"f out in in1 in2 end2                                                          ;"

			"definitions:                                                                   ;"
			" arr_add # fasten<carry_add|carry_cons * @|carry_car @|carry_cdr @||>[]{}[][,] ;"

			"body:                                                                          ;"
			" . = arr_add !out !in in1 in2 end2                                             ;"
			" return _                                                                      ;"
		);
	}

	template<typename Out, typename In, typename In1, typename In2, typename End2>
	constexpr auto array_add_v0(Out out, In in, In1 in1, In2 in2, End2 end2)
	{
		constexpr auto e0 = chord::env<custom_machine_frame>;

		return chord::metapiler_apply<_array_add_v0, e0, Out>(out, &in, in1, in2, end2);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace chord

