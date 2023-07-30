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

// byte array ring:

namespace math {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

	template<typename T>
	nik_ce auto U_store_T					= cctmp::U_store_T<T>;

	nik_ce auto null_env					= chord::null_env;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// integer reshaping:

	//	unsigned long x = (unsigned long) 1 << 32;

	//	unsigned *y = (unsigned*) &x;

	//	printf("%lu, ", x);
	//	printf("%u, ", y[0]);
	//	printf("%u, ", y[1]);

	//	for (auto i : x) printf("%lu, ", i);
	//	printf("\n");

	//	for (unsigned *i = y; i < y + 16; ++i) printf("%u, ", *i);
	//	printf("\n");

// array reshaping:

	//	unsigned long x[] = { 0, 1, 2, 3, 4, 5, 6, ((unsigned long) 1 << 32) };

	//	unsigned *y = (unsigned*) x;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// division:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// half digit:

/***********************************************************************************************************************/

// divisor:

	// (binary):

		template<typename Full, typename Half, Half HalfBit>
		struct T_division_half_digit_divisor
		{
			using cfull = Full const;
			using chalf = Half const;

			nik_ces Half half_bit  = HalfBit;
			nik_ces Full half_base = (Full) 1 << half_bit;
			nik_ces Full low_pass  = half_base - 1;

			chalf value;

			nik_ce T_division_half_digit_divisor(chalf v) : value{v} { }
		};

	// radix:

		template<typename Full, typename Half, Full HalfBase>
		struct T_division_half_digit_radix_divisor
		{
			using cfull = Full const;
			using chalf = Half const;

			nik_ces Full half_base = HalfBase;

			chalf value;

			nik_ce T_division_half_digit_radix_divisor(chalf v) : value{v} { }
		};

/***********************************************************************************************************************/

// divide:

	// (binary):

		struct T_division_half_digit_divide
		{
			template<typename In1, typename In2>
			nik_ces auto result(In1 *in1, In2 in2)
			{
				using chalf = typename In1::chalf;
				using cfull = typename In1::cfull;

				nik_ce chalf half_bit = In1::half_bit;
				nik_ce cfull low_pass = In1::low_pass;

				chalf div = in1->value;

				chalf n2 = *(in2 + 1) & low_pass;
				chalf n1 = *in2 >> half_bit;
				chalf n0 = *in2 & low_pass;

				cfull n21 = n2 << half_bit + n1;
				cfull q1  = n21 / div;
				cfull r1  = n21 % div;
				cfull n10 = r1 << half_bit + n0;
				cfull q0  = n10 / div;
				cfull r0  = n10 % div;

				*in2 = r0;

				return q1 << half_bit + q0;
			}

		}; nik_ce auto _division_half_digit_divide_ = U_store_T<T_division_half_digit_divide>;

	// radix:

		struct T_division_half_digit_radix_divide
		{
			template<typename In1, typename In2>
			nik_ces auto result(In1 *in1, In2 in2)
			{
				using chalf = typename In1::chalf;
				using cfull = typename In1::cfull;

				nik_ce cfull half_base = In1::half_base;

				chalf div = in1->value;

				chalf n2 = *(in2 + 1) % half_base;
				chalf n1 = *in2 / half_base;
				chalf n0 = *in2 % half_base;

				cfull n21 = n2 * half_base + n1;
				cfull q1  = n21 / div;
				cfull r1  = n21 % div;
				cfull n10 = r1 * half_base + n0;
				cfull q0  = n10 / div;
				cfull r0  = n10 % div;

				*in2 = r0;

				return q1 * half_base + q0;
			}

		}; nik_ce auto _division_half_digit_radix_divide_ = U_store_T<T_division_half_digit_radix_divide>;

/***********************************************************************************************************************/

// version 0:

	nik_ce auto _division_half_digit_v0()
	{
		return chord::source
		(
			"f out found div in end                                 ;"

			"definitions:                                           ;"
			" leading_digit # find<not_zero||>[)(-,]                ;"
			" array_divide  # zip<divide_digits @ @||>[)[@|@][-|+,] ;"

			"body:                                                  ;"
			" void leading_digit !found end in                      ;"
			" lead = dereference found                              ;"
			"    . = array_divide !out div !lead in                 ;"
			" return _                                              ;"

			, cctmp::binding( "divide_digits" , _division_half_digit_radix_divide_ )
		);
	}

	template<typename Out, typename In, typename End, typename Denom>
	nik_ce auto division_half_digit_v0(Out out, In in, End end, Denom denom)
	{
		using full_type = unsigned long; // Denom
		using half_type = unsigned;      // half Denom
		using div_type  = T_division_half_digit_radix_divisor<full_type, half_type, 10>;

		End found[] = { 0 };
		div_type div{(half_type) denom};

		return chord::metapiler_apply<_division_half_digit_v0, null_env, Out>(out, found, &div, in, end);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// change of base printer:

/***********************************************************************************************************************/

// modulo by:

	template<auto V>
	struct T_modulo_by
	{
		template<typename In>
		constexpr static auto result(In *in)
		{
			division_half_digit_v0(in->current(), in->begin(), in->end(), V);

			return in->remainder();
		}

	}; template<auto V>
		constexpr auto _modulo_by_ = U_store_T<T_modulo_by<V>>;

/***********************************************************************************************************************/

// divide by:

	template<auto V>
	struct T_divide_by
	{
		template<typename In>
		constexpr static auto result(In *in) { in->reset(); return in; }

	}; template<auto V>
		constexpr auto _divide_by_ = U_store_T<T_divide_by<V>>;

/***********************************************************************************************************************/

// array equal:

	struct T_array_equal
	{
		template<typename In, typename End>
		constexpr static auto result(In *in, End end)
		{
			in->reset();

			return in;
		}

	}; constexpr auto _array_equal_ = U_store_T<T_array_equal>;

/***********************************************************************************************************************/

// printer:

	struct T_print
	{
		template<typename T>
		constexpr static void result(T v, const char *f) { printf(f, *v); }

	}; constexpr auto _print_ = U_store_T<T_print>;

/***********************************************************************************************************************/

// version 0:

	template<auto n>
	constexpr auto _change_of_base_printer_v0()
	{
		return source
		(
			"cob out in format                                 ;"

			"definitions:                                      ;"
			" arr_map # map<rem_by_n @||arr_eq>[)[div_by_n|~,) ;"
			" arr_pr  # repeat<@ @|print @ @|>(-,]{}           ;"

			"body:                                             ;"
			" . = arr_map !out !in zero                        ;"
			" . = arr_pr _ out format                          ;"
			" return _                                         ;"

			, cctmp::binding( "rem_by_n" , _modulo_by_<n>  )
			, cctmp::binding( "div_by_n" , _divide_by_<n>  )
			, cctmp::binding( "arr_eq"   , _array_equal_   )
			, cctmp::binding( "print"    , _print_         )
			, cctmp::binding( "zero"     , 0               )
		);
	}

	template<auto n, typename Out, typename In, typename End>
	constexpr void change_of_base_printer_v0(const char *f, Out out, In in, End end)
	{
		cctmp::cselector<unsigned long> num{in, end};

		chord::metapiler_apply<_change_of_base_printer_v0<n>, null_env, Out>(out, num, f);
		printf("\n");
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace math

