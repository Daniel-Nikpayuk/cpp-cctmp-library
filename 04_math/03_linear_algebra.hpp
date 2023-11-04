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

// linear algebra:

namespace math {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// functions:

/***********************************************************************************************************************/

// inverse:

	struct T_inverse
	{
		template<typename T>
		nik_ces auto result(T v) { return (1.0 / v); }

	}; nik_ce auto _inverse_ = U_store_T<T_inverse>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// kahan algorithm:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// data:

	template<typename T>
	struct T_kahan_data
	{
		using type  = T;
		using ctype = T const;

		T out;
		T loss;

		nik_ce T_kahan_data(ctype o, ctype l) : out{o}, loss{l} { }
	};

/***********************************************************************************************************************/

// add:

	struct T_kahan_add
	{
		template<typename Sum, typename In>
		nik_ces auto result(Sum *sum, In in)
		{
			using ctype = typename Sum::ctype;
			ctype aux   = in - sum->loss;
			ctype val   = sum->out + aux;         // low bits of aux get lost.
			sum->loss   = (val - sum->out) - aux; // (negative) low bits recovered.

			return val;
		}

	}; nik_ce auto _kahan_add_ = U_store_T<T_kahan_add>;

/***********************************************************************************************************************/

// assign:

	struct T_kahan_assign
	{
		template<typename Sum, typename In>
		nik_ces void result(Sum *sum, In in) { sum->out = in; }

	}; nik_ce auto _kahan_assign_ = U_store_T<T_kahan_assign>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sum:

/***********************************************************************************************************************/

// version 0:

	template<auto action, auto add, auto assign>
	nik_ce auto _sum_v0()
	{
		return chord::source
		(
			"f out in end                               ;"

			"definitions:                               ;"
			" sum # fold<add @ action|assign @ @|>{}[,] ;"

			"body:                                      ;"
			" . = sum !out in end                       ;"
			" return _                                  ;"

			, cctmp::binding( "add"    , add    )
			, cctmp::binding( "assign" , assign )
			, cctmp::binding( "action" , action )
		);
	}

/***********************************************************************************************************************/

// base:

	template<typename Out, auto action, typename In, typename End>
	nik_ce auto sum(In in, End end)
	{
		nik_ce auto add = chord::_subpose_<cctmp::_add_, cctmp::_dereference_, cctmp::_id_>;
		nik_ce auto src = _sum_v0<action, add, cctmp::_appoint_>;

		Out out{0};

		return *chord::metapiler_apply<src, null_env, Out*>(&out, in, end);
	}

/***********************************************************************************************************************/

// kahan:

	template<typename Out, auto action, typename In, typename End>
	nik_ce auto kahan_sum(In in, End end)
	{
		using Sum       = T_kahan_data<Out>;
		nik_ce auto src = _sum_v0<action, _kahan_add_, _kahan_assign_>;

		Sum sum{0, 0};

		chord::metapiler_apply<src, null_env, Sum*>(&sum, in, end);

		return sum.out;
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace math

