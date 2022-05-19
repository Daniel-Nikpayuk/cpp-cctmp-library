/************************************************************************************************************************
**
** Copyright 2022 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// define macros:

// preamble:

	#define nik_vp(_n_)												\
															\
		void(*_n_)

	#define nik_avp													\
															\
		nik_vp()

	#define nik_ces													\
															\
		constexpr static

// punctuation:

	#define NIK_EMPTY()

		// blank space.

	#define NIK_COMMA()												\
															\
		,

	#define NIK_L_PAR()												\
															\
		(

	#define NIK_R_PAR()												\
															\
		)

	#define NIK_L_ANG()												\
															\
		<

	#define NIK_R_ANG()												\
															\
		>

	#define NIK_L_BRAK()												\
															\
		[

	#define NIK_R_BRAK()												\
															\
		]

	#define NIK_AUTO()												\
															\
		auto

	#define NIK_TYPENAME()												\
															\
		typename

	#define NIK_LDOTS()												\
															\
		...

	#define NIK_R_PAR_LDOTS()											\
															\
		)...

	#define NIK_PLUS()												\
															\
		+

	#define NIK_L_STORE()												\
															\
		nik_avp(auto_pack<

	#define NIK_R_STORE()												\
															\
		...>*)

// block variables:

// upper repetitions:

		// This implementation is less efficient because it needs to align with UPPER_IDS (which follow),
		// otherwise the compiler won't be able to interpret the dependent macros properly.

	#define NIK_UPPER_1_REPS(_l_, _r_)										\
															\
		_l_() _r_()

	#define NIK_UPPER_2_REPS(_l_, _r_)										\
															\
		_l_() _r_()

	#define NIK_UPPER_4_REPS(_l_, _r_)										\
															\
		_l_() _r_() _l_() _r_()

	#define NIK_UPPER_8_REPS(_l_, _r_)										\
															\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()

	#define NIK_UPPER_16_REPS(_l_, _r_)										\
															\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()

	#define NIK_UPPER_32_REPS(_l_, _r_)										\
															\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()

	#define NIK_UPPER_64_REPS(_l_, _r_)										\
															\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()

	#define NIK_UPPER_128_REPS(_l_, _r_)										\
															\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()

	#define NIK_UPPER_256_REPS(_l_, _r_)										\
															\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
															\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()

	#define NIK_UPPER_512_REPS(_l_, _r_)										\
															\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
															\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
															\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
															\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()		\
		_l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_() _l_() _r_()

// repetitions:

	#define NIK_2_0_REPS(_l_, _r_)											\
															\
		NIK_UPPER_1_REPS(_l_, _r_)

	#define NIK_2_1_REPS(_l_, _r_)											\
															\
		NIK_UPPER_1_REPS(_l_, _r_) NIK_UPPER_2_REPS(_l_, _r_)

	#define NIK_2_2_REPS(_l_, _r_)											\
															\
		NIK_UPPER_1_REPS(_l_, _r_) NIK_UPPER_2_REPS(_l_, _r_) NIK_UPPER_4_REPS(_l_, _r_)

	#define NIK_2_3_REPS(_l_, _r_)											\
															\
		NIK_UPPER_1_REPS(_l_, _r_) NIK_UPPER_2_REPS(_l_, _r_) NIK_UPPER_4_REPS(_l_, _r_)			\
		NIK_UPPER_8_REPS(_l_, _r_)

	#define NIK_2_4_REPS(_l_, _r_)											\
															\
		NIK_UPPER_1_REPS(_l_, _r_) NIK_UPPER_2_REPS(_l_, _r_) NIK_UPPER_4_REPS(_l_, _r_)			\
		NIK_UPPER_8_REPS(_l_, _r_) NIK_UPPER_16_REPS(_l_, _r_)

	#define NIK_2_5_REPS(_l_, _r_)											\
															\
		NIK_UPPER_1_REPS(_l_, _r_) NIK_UPPER_2_REPS(_l_, _r_) NIK_UPPER_4_REPS(_l_, _r_)			\
		NIK_UPPER_8_REPS(_l_, _r_) NIK_UPPER_16_REPS(_l_, _r_) NIK_UPPER_32_REPS(_l_, _r_)

	#define NIK_2_6_REPS(_l_, _r_)											\
															\
		NIK_UPPER_1_REPS(_l_, _r_) NIK_UPPER_2_REPS(_l_, _r_) NIK_UPPER_4_REPS(_l_, _r_)			\
		NIK_UPPER_8_REPS(_l_, _r_) NIK_UPPER_16_REPS(_l_, _r_) NIK_UPPER_32_REPS(_l_, _r_)			\
		NIK_UPPER_64_REPS(_l_, _r_)

	#define NIK_2_7_REPS(_l_, _r_)											\
															\
		NIK_UPPER_1_REPS(_l_, _r_) NIK_UPPER_2_REPS(_l_, _r_) NIK_UPPER_4_REPS(_l_, _r_)			\
		NIK_UPPER_8_REPS(_l_, _r_) NIK_UPPER_16_REPS(_l_, _r_) NIK_UPPER_32_REPS(_l_, _r_)			\
		NIK_UPPER_64_REPS(_l_, _r_) NIK_UPPER_128_REPS(_l_, _r_)

	#define NIK_2_8_REPS(_l_, _r_)											\
															\
		NIK_UPPER_1_REPS(_l_, _r_) NIK_UPPER_2_REPS(_l_, _r_) NIK_UPPER_4_REPS(_l_, _r_)			\
		NIK_UPPER_8_REPS(_l_, _r_) NIK_UPPER_16_REPS(_l_, _r_) NIK_UPPER_32_REPS(_l_, _r_)			\
		NIK_UPPER_64_REPS(_l_, _r_) NIK_UPPER_128_REPS(_l_, _r_) NIK_UPPER_256_REPS(_l_, _r_)

	#define NIK_2_9_REPS(_l_, _r_)											\
															\
		NIK_UPPER_1_REPS(_l_, _r_) NIK_UPPER_2_REPS(_l_, _r_) NIK_UPPER_4_REPS(_l_, _r_)			\
		NIK_UPPER_8_REPS(_l_, _r_) NIK_UPPER_16_REPS(_l_, _r_) NIK_UPPER_32_REPS(_l_, _r_)			\
		NIK_UPPER_64_REPS(_l_, _r_) NIK_UPPER_128_REPS(_l_, _r_) NIK_UPPER_256_REPS(_l_, _r_)			\
		NIK_UPPER_512_REPS(_l_, _r_)

// upper identifiers:

	#define NIK_UPPER_1_IDS(_l_, _m_, _r_)										\
															\
		_l_() _m_ ##   0 _r_()

	#define NIK_UPPER_2_IDS(_l_, _m_, _r_)										\
															\
		_l_() _m_ ##   1 _r_()

	#define NIK_UPPER_4_IDS(_l_, _m_, _r_)										\
															\
		_l_() _m_ ##   2 _r_(),	_l_() _m_ ##   3 _r_()

	#define NIK_UPPER_8_IDS(_l_, _m_, _r_)										\
															\
		_l_() _m_ ##   4 _r_(),	_l_() _m_ ##   5 _r_(),	_l_() _m_ ##   6 _r_(),	_l_() _m_ ##   7 _r_()

	#define NIK_UPPER_16_IDS(_l_, _m_, _r_)										\
															\
		_l_() _m_ ##   8 _r_(),	_l_() _m_ ##   9 _r_(),	_l_() _m_ ##  10 _r_(),	_l_() _m_ ##  11 _r_(),		\
		_l_() _m_ ##  12 _r_(),	_l_() _m_ ##  13 _r_(),	_l_() _m_ ##  14 _r_(),	_l_() _m_ ##  15 _r_()

	#define NIK_UPPER_32_IDS(_l_, _m_, _r_)										\
															\
		_l_() _m_ ##  16 _r_(),	_l_() _m_ ##  17 _r_(),	_l_() _m_ ##  18 _r_(),	_l_() _m_ ##  19 _r_(),		\
		_l_() _m_ ##  20 _r_(),	_l_() _m_ ##  21 _r_(),	_l_() _m_ ##  22 _r_(),	_l_() _m_ ##  23 _r_(),		\
		_l_() _m_ ##  24 _r_(),	_l_() _m_ ##  25 _r_(),	_l_() _m_ ##  26 _r_(),	_l_() _m_ ##  27 _r_(),		\
		_l_() _m_ ##  28 _r_(),	_l_() _m_ ##  29 _r_(),	_l_() _m_ ##  30 _r_(),	_l_() _m_ ##  31 _r_()

	#define NIK_UPPER_64_IDS(_l_, _m_, _r_)										\
															\
		_l_() _m_ ##  32 _r_(),	_l_() _m_ ##  33 _r_(),	_l_() _m_ ##  34 _r_(),	_l_() _m_ ##  35 _r_(),		\
		_l_() _m_ ##  36 _r_(),	_l_() _m_ ##  37 _r_(),	_l_() _m_ ##  38 _r_(),	_l_() _m_ ##  39 _r_(),		\
		_l_() _m_ ##  40 _r_(),	_l_() _m_ ##  41 _r_(),	_l_() _m_ ##  42 _r_(),	_l_() _m_ ##  43 _r_(),		\
		_l_() _m_ ##  44 _r_(),	_l_() _m_ ##  45 _r_(),	_l_() _m_ ##  46 _r_(),	_l_() _m_ ##  47 _r_(),		\
		_l_() _m_ ##  48 _r_(),	_l_() _m_ ##  49 _r_(),	_l_() _m_ ##  50 _r_(),	_l_() _m_ ##  51 _r_(),		\
		_l_() _m_ ##  52 _r_(),	_l_() _m_ ##  53 _r_(),	_l_() _m_ ##  54 _r_(),	_l_() _m_ ##  55 _r_(),		\
		_l_() _m_ ##  56 _r_(),	_l_() _m_ ##  57 _r_(),	_l_() _m_ ##  58 _r_(),	_l_() _m_ ##  59 _r_(),		\
		_l_() _m_ ##  60 _r_(),	_l_() _m_ ##  61 _r_(),	_l_() _m_ ##  62 _r_(),	_l_() _m_ ##  63 _r_()

	#define NIK_UPPER_128_IDS(_l_, _m_, _r_)									\
															\
		_l_() _m_ ##  64 _r_(),	_l_() _m_ ##  65 _r_(),	_l_() _m_ ##  66 _r_(),	_l_() _m_ ##  67 _r_(),		\
		_l_() _m_ ##  68 _r_(),	_l_() _m_ ##  69 _r_(),	_l_() _m_ ##  70 _r_(),	_l_() _m_ ##  71 _r_(),		\
		_l_() _m_ ##  72 _r_(),	_l_() _m_ ##  73 _r_(),	_l_() _m_ ##  74 _r_(),	_l_() _m_ ##  75 _r_(),		\
		_l_() _m_ ##  76 _r_(),	_l_() _m_ ##  77 _r_(),	_l_() _m_ ##  78 _r_(),	_l_() _m_ ##  79 _r_(),		\
		_l_() _m_ ##  80 _r_(),	_l_() _m_ ##  81 _r_(),	_l_() _m_ ##  82 _r_(),	_l_() _m_ ##  83 _r_(),		\
		_l_() _m_ ##  84 _r_(),	_l_() _m_ ##  85 _r_(),	_l_() _m_ ##  86 _r_(),	_l_() _m_ ##  87 _r_(),		\
		_l_() _m_ ##  88 _r_(),	_l_() _m_ ##  89 _r_(),	_l_() _m_ ##  90 _r_(),	_l_() _m_ ##  91 _r_(),		\
		_l_() _m_ ##  92 _r_(),	_l_() _m_ ##  93 _r_(),	_l_() _m_ ##  94 _r_(),	_l_() _m_ ##  95 _r_(),		\
		_l_() _m_ ##  96 _r_(),	_l_() _m_ ##  97 _r_(),	_l_() _m_ ##  98 _r_(),	_l_() _m_ ##  99 _r_(),		\
		_l_() _m_ ## 100 _r_(),	_l_() _m_ ## 101 _r_(),	_l_() _m_ ## 102 _r_(),	_l_() _m_ ## 103 _r_(),		\
		_l_() _m_ ## 104 _r_(),	_l_() _m_ ## 105 _r_(),	_l_() _m_ ## 106 _r_(),	_l_() _m_ ## 107 _r_(),		\
		_l_() _m_ ## 108 _r_(),	_l_() _m_ ## 109 _r_(),	_l_() _m_ ## 110 _r_(),	_l_() _m_ ## 111 _r_(),		\
		_l_() _m_ ## 112 _r_(),	_l_() _m_ ## 113 _r_(),	_l_() _m_ ## 114 _r_(),	_l_() _m_ ## 115 _r_(),		\
		_l_() _m_ ## 116 _r_(),	_l_() _m_ ## 117 _r_(),	_l_() _m_ ## 118 _r_(),	_l_() _m_ ## 119 _r_(),		\
		_l_() _m_ ## 120 _r_(),	_l_() _m_ ## 121 _r_(),	_l_() _m_ ## 122 _r_(),	_l_() _m_ ## 123 _r_(),		\
		_l_() _m_ ## 124 _r_(),	_l_() _m_ ## 125 _r_(),	_l_() _m_ ## 126 _r_(),	_l_() _m_ ## 127 _r_()

	#define NIK_UPPER_256_IDS(_l_, _m_, _r_)									\
															\
		_l_() _m_ ## 128 _r_(),	_l_() _m_ ## 129 _r_(),	_l_() _m_ ## 130 _r_(),	_l_() _m_ ## 131 _r_(),		\
		_l_() _m_ ## 132 _r_(),	_l_() _m_ ## 133 _r_(),	_l_() _m_ ## 134 _r_(),	_l_() _m_ ## 135 _r_(),		\
		_l_() _m_ ## 136 _r_(),	_l_() _m_ ## 137 _r_(),	_l_() _m_ ## 138 _r_(),	_l_() _m_ ## 139 _r_(),		\
		_l_() _m_ ## 140 _r_(),	_l_() _m_ ## 141 _r_(),	_l_() _m_ ## 142 _r_(),	_l_() _m_ ## 143 _r_(),		\
		_l_() _m_ ## 144 _r_(),	_l_() _m_ ## 145 _r_(),	_l_() _m_ ## 146 _r_(),	_l_() _m_ ## 147 _r_(),		\
		_l_() _m_ ## 148 _r_(),	_l_() _m_ ## 149 _r_(),	_l_() _m_ ## 150 _r_(),	_l_() _m_ ## 151 _r_(),		\
		_l_() _m_ ## 152 _r_(),	_l_() _m_ ## 153 _r_(),	_l_() _m_ ## 154 _r_(),	_l_() _m_ ## 155 _r_(),		\
		_l_() _m_ ## 156 _r_(),	_l_() _m_ ## 157 _r_(),	_l_() _m_ ## 158 _r_(),	_l_() _m_ ## 159 _r_(),		\
		_l_() _m_ ## 160 _r_(),	_l_() _m_ ## 161 _r_(),	_l_() _m_ ## 162 _r_(),	_l_() _m_ ## 163 _r_(),		\
		_l_() _m_ ## 164 _r_(),	_l_() _m_ ## 165 _r_(),	_l_() _m_ ## 166 _r_(),	_l_() _m_ ## 167 _r_(),		\
		_l_() _m_ ## 168 _r_(),	_l_() _m_ ## 169 _r_(),	_l_() _m_ ## 170 _r_(),	_l_() _m_ ## 171 _r_(),		\
		_l_() _m_ ## 172 _r_(),	_l_() _m_ ## 173 _r_(),	_l_() _m_ ## 174 _r_(),	_l_() _m_ ## 175 _r_(),		\
		_l_() _m_ ## 176 _r_(),	_l_() _m_ ## 177 _r_(),	_l_() _m_ ## 178 _r_(),	_l_() _m_ ## 179 _r_(),		\
		_l_() _m_ ## 180 _r_(),	_l_() _m_ ## 181 _r_(),	_l_() _m_ ## 182 _r_(),	_l_() _m_ ## 183 _r_(),		\
		_l_() _m_ ## 184 _r_(),	_l_() _m_ ## 185 _r_(),	_l_() _m_ ## 186 _r_(),	_l_() _m_ ## 187 _r_(),		\
		_l_() _m_ ## 188 _r_(),	_l_() _m_ ## 189 _r_(),	_l_() _m_ ## 190 _r_(),	_l_() _m_ ## 191 _r_(),		\
		_l_() _m_ ## 192 _r_(),	_l_() _m_ ## 193 _r_(),	_l_() _m_ ## 194 _r_(),	_l_() _m_ ## 195 _r_(),		\
		_l_() _m_ ## 196 _r_(),	_l_() _m_ ## 197 _r_(),	_l_() _m_ ## 198 _r_(),	_l_() _m_ ## 199 _r_(),		\
		_l_() _m_ ## 200 _r_(),	_l_() _m_ ## 201 _r_(),	_l_() _m_ ## 202 _r_(),	_l_() _m_ ## 203 _r_(),		\
		_l_() _m_ ## 204 _r_(),	_l_() _m_ ## 205 _r_(),	_l_() _m_ ## 206 _r_(),	_l_() _m_ ## 207 _r_(),		\
		_l_() _m_ ## 208 _r_(),	_l_() _m_ ## 209 _r_(),	_l_() _m_ ## 210 _r_(),	_l_() _m_ ## 211 _r_(),		\
		_l_() _m_ ## 212 _r_(),	_l_() _m_ ## 213 _r_(),	_l_() _m_ ## 214 _r_(),	_l_() _m_ ## 215 _r_(),		\
		_l_() _m_ ## 216 _r_(),	_l_() _m_ ## 217 _r_(),	_l_() _m_ ## 218 _r_(),	_l_() _m_ ## 219 _r_(),		\
		_l_() _m_ ## 220 _r_(),	_l_() _m_ ## 221 _r_(),	_l_() _m_ ## 222 _r_(),	_l_() _m_ ## 223 _r_(),		\
		_l_() _m_ ## 224 _r_(),	_l_() _m_ ## 225 _r_(),	_l_() _m_ ## 226 _r_(),	_l_() _m_ ## 227 _r_(),		\
		_l_() _m_ ## 228 _r_(),	_l_() _m_ ## 229 _r_(),	_l_() _m_ ## 230 _r_(),	_l_() _m_ ## 231 _r_(),		\
		_l_() _m_ ## 232 _r_(),	_l_() _m_ ## 233 _r_(),	_l_() _m_ ## 234 _r_(),	_l_() _m_ ## 235 _r_(),		\
		_l_() _m_ ## 236 _r_(),	_l_() _m_ ## 237 _r_(),	_l_() _m_ ## 238 _r_(),	_l_() _m_ ## 239 _r_(),		\
		_l_() _m_ ## 240 _r_(),	_l_() _m_ ## 241 _r_(),	_l_() _m_ ## 242 _r_(),	_l_() _m_ ## 243 _r_(),		\
		_l_() _m_ ## 244 _r_(),	_l_() _m_ ## 245 _r_(),	_l_() _m_ ## 246 _r_(),	_l_() _m_ ## 247 _r_(),		\
		_l_() _m_ ## 248 _r_(),	_l_() _m_ ## 249 _r_(),	_l_() _m_ ## 250 _r_(),	_l_() _m_ ## 251 _r_(),		\
		_l_() _m_ ## 252 _r_(),	_l_() _m_ ## 253 _r_(),	_l_() _m_ ## 254 _r_(),	_l_() _m_ ## 255 _r_()

	#define NIK_UPPER_512_IDS(_l_, _m_, _r_)									\
															\
		_l_() _m_ ## 256 _r_(),	_l_() _m_ ## 257 _r_(),	_l_() _m_ ## 258 _r_(),	_l_() _m_ ## 259 _r_(),		\
		_l_() _m_ ## 260 _r_(),	_l_() _m_ ## 261 _r_(),	_l_() _m_ ## 262 _r_(),	_l_() _m_ ## 263 _r_(),		\
		_l_() _m_ ## 264 _r_(),	_l_() _m_ ## 265 _r_(),	_l_() _m_ ## 266 _r_(),	_l_() _m_ ## 267 _r_(),		\
		_l_() _m_ ## 268 _r_(),	_l_() _m_ ## 269 _r_(),	_l_() _m_ ## 270 _r_(),	_l_() _m_ ## 271 _r_(),		\
		_l_() _m_ ## 272 _r_(),	_l_() _m_ ## 273 _r_(),	_l_() _m_ ## 274 _r_(),	_l_() _m_ ## 275 _r_(),		\
		_l_() _m_ ## 276 _r_(),	_l_() _m_ ## 277 _r_(),	_l_() _m_ ## 278 _r_(),	_l_() _m_ ## 279 _r_(),		\
		_l_() _m_ ## 280 _r_(),	_l_() _m_ ## 281 _r_(),	_l_() _m_ ## 282 _r_(),	_l_() _m_ ## 283 _r_(),		\
		_l_() _m_ ## 284 _r_(),	_l_() _m_ ## 285 _r_(),	_l_() _m_ ## 286 _r_(),	_l_() _m_ ## 287 _r_(),		\
		_l_() _m_ ## 288 _r_(),	_l_() _m_ ## 289 _r_(),	_l_() _m_ ## 290 _r_(),	_l_() _m_ ## 291 _r_(),		\
		_l_() _m_ ## 292 _r_(),	_l_() _m_ ## 293 _r_(),	_l_() _m_ ## 294 _r_(),	_l_() _m_ ## 295 _r_(),		\
		_l_() _m_ ## 296 _r_(),	_l_() _m_ ## 297 _r_(),	_l_() _m_ ## 298 _r_(),	_l_() _m_ ## 299 _r_(),		\
		_l_() _m_ ## 300 _r_(),	_l_() _m_ ## 301 _r_(),	_l_() _m_ ## 302 _r_(),	_l_() _m_ ## 303 _r_(),		\
		_l_() _m_ ## 304 _r_(),	_l_() _m_ ## 305 _r_(),	_l_() _m_ ## 306 _r_(),	_l_() _m_ ## 307 _r_(),		\
		_l_() _m_ ## 308 _r_(),	_l_() _m_ ## 309 _r_(),	_l_() _m_ ## 310 _r_(),	_l_() _m_ ## 311 _r_(),		\
		_l_() _m_ ## 312 _r_(),	_l_() _m_ ## 313 _r_(),	_l_() _m_ ## 314 _r_(),	_l_() _m_ ## 315 _r_(),		\
		_l_() _m_ ## 316 _r_(),	_l_() _m_ ## 317 _r_(),	_l_() _m_ ## 318 _r_(),	_l_() _m_ ## 319 _r_(),		\
		_l_() _m_ ## 320 _r_(),	_l_() _m_ ## 321 _r_(),	_l_() _m_ ## 322 _r_(),	_l_() _m_ ## 323 _r_(),		\
		_l_() _m_ ## 324 _r_(),	_l_() _m_ ## 325 _r_(),	_l_() _m_ ## 326 _r_(),	_l_() _m_ ## 327 _r_(),		\
		_l_() _m_ ## 328 _r_(),	_l_() _m_ ## 329 _r_(),	_l_() _m_ ## 330 _r_(),	_l_() _m_ ## 331 _r_(),		\
		_l_() _m_ ## 332 _r_(),	_l_() _m_ ## 333 _r_(),	_l_() _m_ ## 334 _r_(),	_l_() _m_ ## 335 _r_(),		\
		_l_() _m_ ## 336 _r_(),	_l_() _m_ ## 337 _r_(),	_l_() _m_ ## 338 _r_(),	_l_() _m_ ## 339 _r_(),		\
		_l_() _m_ ## 340 _r_(),	_l_() _m_ ## 341 _r_(),	_l_() _m_ ## 342 _r_(),	_l_() _m_ ## 343 _r_(),		\
		_l_() _m_ ## 344 _r_(),	_l_() _m_ ## 345 _r_(),	_l_() _m_ ## 346 _r_(),	_l_() _m_ ## 347 _r_(),		\
		_l_() _m_ ## 348 _r_(),	_l_() _m_ ## 349 _r_(),	_l_() _m_ ## 350 _r_(),	_l_() _m_ ## 351 _r_(),		\
		_l_() _m_ ## 352 _r_(),	_l_() _m_ ## 353 _r_(),	_l_() _m_ ## 354 _r_(),	_l_() _m_ ## 355 _r_(),		\
		_l_() _m_ ## 356 _r_(),	_l_() _m_ ## 357 _r_(),	_l_() _m_ ## 358 _r_(),	_l_() _m_ ## 359 _r_(),		\
		_l_() _m_ ## 360 _r_(),	_l_() _m_ ## 361 _r_(),	_l_() _m_ ## 362 _r_(),	_l_() _m_ ## 363 _r_(),		\
		_l_() _m_ ## 364 _r_(),	_l_() _m_ ## 365 _r_(),	_l_() _m_ ## 366 _r_(),	_l_() _m_ ## 367 _r_(),		\
		_l_() _m_ ## 368 _r_(),	_l_() _m_ ## 369 _r_(),	_l_() _m_ ## 370 _r_(),	_l_() _m_ ## 371 _r_(),		\
		_l_() _m_ ## 372 _r_(),	_l_() _m_ ## 373 _r_(),	_l_() _m_ ## 374 _r_(),	_l_() _m_ ## 375 _r_(),		\
		_l_() _m_ ## 376 _r_(),	_l_() _m_ ## 377 _r_(),	_l_() _m_ ## 378 _r_(),	_l_() _m_ ## 379 _r_(),		\
		_l_() _m_ ## 380 _r_(),	_l_() _m_ ## 381 _r_(),	_l_() _m_ ## 382 _r_(),	_l_() _m_ ## 383 _r_(),		\
		_l_() _m_ ## 384 _r_(),	_l_() _m_ ## 385 _r_(),	_l_() _m_ ## 386 _r_(),	_l_() _m_ ## 387 _r_(),		\
		_l_() _m_ ## 388 _r_(),	_l_() _m_ ## 389 _r_(),	_l_() _m_ ## 390 _r_(),	_l_() _m_ ## 391 _r_(),		\
		_l_() _m_ ## 392 _r_(),	_l_() _m_ ## 393 _r_(),	_l_() _m_ ## 394 _r_(),	_l_() _m_ ## 395 _r_(),		\
		_l_() _m_ ## 396 _r_(),	_l_() _m_ ## 397 _r_(),	_l_() _m_ ## 398 _r_(),	_l_() _m_ ## 399 _r_(),		\
		_l_() _m_ ## 400 _r_(),	_l_() _m_ ## 401 _r_(),	_l_() _m_ ## 402 _r_(),	_l_() _m_ ## 403 _r_(),		\
		_l_() _m_ ## 404 _r_(),	_l_() _m_ ## 405 _r_(),	_l_() _m_ ## 406 _r_(),	_l_() _m_ ## 407 _r_(),		\
		_l_() _m_ ## 408 _r_(),	_l_() _m_ ## 409 _r_(),	_l_() _m_ ## 410 _r_(),	_l_() _m_ ## 411 _r_(),		\
		_l_() _m_ ## 412 _r_(),	_l_() _m_ ## 413 _r_(),	_l_() _m_ ## 414 _r_(),	_l_() _m_ ## 415 _r_(),		\
		_l_() _m_ ## 416 _r_(),	_l_() _m_ ## 417 _r_(),	_l_() _m_ ## 418 _r_(),	_l_() _m_ ## 419 _r_(),		\
		_l_() _m_ ## 420 _r_(),	_l_() _m_ ## 421 _r_(),	_l_() _m_ ## 422 _r_(),	_l_() _m_ ## 423 _r_(),		\
		_l_() _m_ ## 424 _r_(),	_l_() _m_ ## 425 _r_(),	_l_() _m_ ## 426 _r_(),	_l_() _m_ ## 427 _r_(),		\
		_l_() _m_ ## 428 _r_(),	_l_() _m_ ## 429 _r_(),	_l_() _m_ ## 430 _r_(),	_l_() _m_ ## 431 _r_(),		\
		_l_() _m_ ## 432 _r_(),	_l_() _m_ ## 433 _r_(),	_l_() _m_ ## 434 _r_(),	_l_() _m_ ## 435 _r_(),		\
		_l_() _m_ ## 436 _r_(),	_l_() _m_ ## 437 _r_(),	_l_() _m_ ## 438 _r_(),	_l_() _m_ ## 439 _r_(),		\
		_l_() _m_ ## 440 _r_(),	_l_() _m_ ## 441 _r_(),	_l_() _m_ ## 442 _r_(),	_l_() _m_ ## 443 _r_(),		\
		_l_() _m_ ## 444 _r_(),	_l_() _m_ ## 445 _r_(),	_l_() _m_ ## 446 _r_(),	_l_() _m_ ## 447 _r_(),		\
		_l_() _m_ ## 448 _r_(),	_l_() _m_ ## 449 _r_(),	_l_() _m_ ## 450 _r_(),	_l_() _m_ ## 451 _r_(),		\
		_l_() _m_ ## 452 _r_(),	_l_() _m_ ## 453 _r_(),	_l_() _m_ ## 454 _r_(),	_l_() _m_ ## 455 _r_(),		\
		_l_() _m_ ## 456 _r_(),	_l_() _m_ ## 457 _r_(),	_l_() _m_ ## 458 _r_(),	_l_() _m_ ## 459 _r_(),		\
		_l_() _m_ ## 460 _r_(),	_l_() _m_ ## 461 _r_(),	_l_() _m_ ## 462 _r_(),	_l_() _m_ ## 463 _r_(),		\
		_l_() _m_ ## 464 _r_(),	_l_() _m_ ## 465 _r_(),	_l_() _m_ ## 466 _r_(),	_l_() _m_ ## 467 _r_(),		\
		_l_() _m_ ## 468 _r_(),	_l_() _m_ ## 469 _r_(),	_l_() _m_ ## 470 _r_(),	_l_() _m_ ## 471 _r_(),		\
		_l_() _m_ ## 472 _r_(),	_l_() _m_ ## 473 _r_(),	_l_() _m_ ## 474 _r_(),	_l_() _m_ ## 475 _r_(),		\
		_l_() _m_ ## 476 _r_(),	_l_() _m_ ## 477 _r_(),	_l_() _m_ ## 478 _r_(),	_l_() _m_ ## 479 _r_(),		\
		_l_() _m_ ## 480 _r_(),	_l_() _m_ ## 481 _r_(),	_l_() _m_ ## 482 _r_(),	_l_() _m_ ## 483 _r_(),		\
		_l_() _m_ ## 484 _r_(),	_l_() _m_ ## 485 _r_(),	_l_() _m_ ## 486 _r_(),	_l_() _m_ ## 487 _r_(),		\
		_l_() _m_ ## 488 _r_(),	_l_() _m_ ## 489 _r_(),	_l_() _m_ ## 490 _r_(),	_l_() _m_ ## 491 _r_(),		\
		_l_() _m_ ## 492 _r_(),	_l_() _m_ ## 493 _r_(),	_l_() _m_ ## 494 _r_(),	_l_() _m_ ## 495 _r_(),		\
		_l_() _m_ ## 496 _r_(),	_l_() _m_ ## 497 _r_(),	_l_() _m_ ## 498 _r_(),	_l_() _m_ ## 499 _r_(),		\
		_l_() _m_ ## 500 _r_(),	_l_() _m_ ## 501 _r_(),	_l_() _m_ ## 502 _r_(),	_l_() _m_ ## 503 _r_(),		\
		_l_() _m_ ## 504 _r_(),	_l_() _m_ ## 505 _r_(),	_l_() _m_ ## 506 _r_(),	_l_() _m_ ## 507 _r_(),		\
		_l_() _m_ ## 508 _r_(),	_l_() _m_ ## 509 _r_(),	_l_() _m_ ## 510 _r_(),	_l_() _m_ ## 511 _r_()

// identifiers:

	#define NIK_2_0_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_)

	#define NIK_2_1_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_), NIK_UPPER_2_IDS(_l_, _m_, _r_)

	#define NIK_2_2_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_), NIK_UPPER_2_IDS(_l_, _m_, _r_), NIK_UPPER_4_IDS(_l_, _m_, _r_)

	#define NIK_2_3_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_), NIK_UPPER_2_IDS(_l_, _m_, _r_), NIK_UPPER_4_IDS(_l_, _m_, _r_),		\
		NIK_UPPER_8_IDS(_l_, _m_, _r_)

	#define NIK_2_4_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_), NIK_UPPER_2_IDS(_l_, _m_, _r_), NIK_UPPER_4_IDS(_l_, _m_, _r_),		\
		NIK_UPPER_8_IDS(_l_, _m_, _r_), NIK_UPPER_16_IDS(_l_, _m_, _r_)

	#define NIK_2_5_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_), NIK_UPPER_2_IDS(_l_, _m_, _r_), NIK_UPPER_4_IDS(_l_, _m_, _r_),		\
		NIK_UPPER_8_IDS(_l_, _m_, _r_), NIK_UPPER_16_IDS(_l_, _m_, _r_), NIK_UPPER_32_IDS(_l_, _m_, _r_)

	#define NIK_2_6_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_), NIK_UPPER_2_IDS(_l_, _m_, _r_), NIK_UPPER_4_IDS(_l_, _m_, _r_),		\
		NIK_UPPER_8_IDS(_l_, _m_, _r_), NIK_UPPER_16_IDS(_l_, _m_, _r_), NIK_UPPER_32_IDS(_l_, _m_, _r_),	\
		NIK_UPPER_64_IDS(_l_, _m_, _r_)

	#define NIK_2_7_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_), NIK_UPPER_2_IDS(_l_, _m_, _r_), NIK_UPPER_4_IDS(_l_, _m_, _r_),		\
		NIK_UPPER_8_IDS(_l_, _m_, _r_), NIK_UPPER_16_IDS(_l_, _m_, _r_), NIK_UPPER_32_IDS(_l_, _m_, _r_),	\
		NIK_UPPER_64_IDS(_l_, _m_, _r_), NIK_UPPER_128_IDS(_l_, _m_, _r_)

	#define NIK_2_8_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_), NIK_UPPER_2_IDS(_l_, _m_, _r_), NIK_UPPER_4_IDS(_l_, _m_, _r_),		\
		NIK_UPPER_8_IDS(_l_, _m_, _r_), NIK_UPPER_16_IDS(_l_, _m_, _r_), NIK_UPPER_32_IDS(_l_, _m_, _r_),	\
		NIK_UPPER_64_IDS(_l_, _m_, _r_), NIK_UPPER_128_IDS(_l_, _m_, _r_), NIK_UPPER_256_IDS(_l_, _m_, _r_)

	#define NIK_2_9_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_), NIK_UPPER_2_IDS(_l_, _m_, _r_), NIK_UPPER_4_IDS(_l_, _m_, _r_),		\
		NIK_UPPER_8_IDS(_l_, _m_, _r_), NIK_UPPER_16_IDS(_l_, _m_, _r_), NIK_UPPER_32_IDS(_l_, _m_, _r_),	\
		NIK_UPPER_64_IDS(_l_, _m_, _r_), NIK_UPPER_128_IDS(_l_, _m_, _r_), NIK_UPPER_256_IDS(_l_, _m_, _r_),	\
		NIK_UPPER_512_IDS(_l_, _m_, _r_)

// auto:

	#define NIK_2_N_AUTO_VARS(_n_, _v_)										\
															\
		NIK_2_ ## _n_ ## _IDS(NIK_AUTO, _v_, NIK_EMPTY)

// values:

	#define NIK_2_N_VARS(_n_, _v_)											\
															\
		NIK_2_ ## _n_ ## _IDS(NIK_EMPTY, _v_, NIK_EMPTY)

// typename:

	#define NIK_2_N_TYPENAME_VARS(_n_, _v_)										\
															\
		NIK_2_ ## _n_ ## _IDS(NIK_TYPENAME, _v_, NIK_EMPTY)

// argument:

	#define NIK_2_N_RESTORE_VARS(_n_, _v_)										\
															\
		NIK_2_ ## _n_ ## _IDS(U_restore_T NIK_L_ANG, _v_, NIK_R_ANG)

// variadic:

	#define NIK_2_N_VARIADIC_VARS(_n_, _v_)										\
															\
		NIK_2_ ## _n_ ## _IDS(auto NIK_LDOTS, _v_, NIK_EMPTY)

// store:

	#define NIK_2_N_STORE_VARS(_n_, _v_)										\
															\
		NIK_2_ ## _n_ ## _IDS(NIK_L_STORE, _v_, NIK_R_STORE)

// pack:

	#define NIK_2_N_PACK_VARS(_n_, _v_)										\
															\
		NIK_2_ ## _n_ ## _IDS(NIK_EMPTY, _v_, NIK_LDOTS)

// apply map:

	#define NIK_2_N_OP_MAP_VARS(_n_, _m_, _v_)									\
															\
		NIK_2_ ## _n_ ## _IDS(_m_ NIK_L_PAR, _v_, NIK_R_PAR_LDOTS)

// alias map:

	#define NIK_2_N_AL_MAP_VARS(_n_, _m_, _v_)									\
															\
		NIK_2_ ## _n_ ## _IDS(_m_::template result NIK_L_ANG, _v_, > NIK_LDOTS)

// index segment:

	#define NIK_2_N_INDEX_SEGMENT(_n_, _s_)										\
															\
		NIK_2_ ## _n_ ## _IDS(_s_ NIK_PLUS,, NIK_EMPTY)

// monoid calls:

	#define NIK_2_N_MONOID_CALLS(_n_, _l_, _r_)									\
															\
		NIK_2_ ## _n_ ## _REPS(_l_, _r_)

// monoid values:

	#define NIK_2_N_MONOID_VARS(_n_, _v_, _r_)									\
															\
		NIK_2_ ## _n_ ## _IDS(NIK_EMPTY, _v_, _r_)

// action folds:

	#define NIK_2_N_ACTION_FOLDS(_n_, _o_, _f_, _v_)								\
															\
		NIK_2_N_MONOID_CALLS(_n_, Overload::template result<_o_ NIK_COMMA, _f_... NIK_COMMA)			\
															\
		_v_, NIK_2_N_MONOID_VARS(_n_, _v_, NIK_R_ANG)

// block:

// next length:

	#define NIK_BLOCK_DISPATCH_NEXT_LENGTH(_n_)									\
															\
		nik_ces key_type next_length_ ## _n_(cdepth_type d, cindex_type n)					\
		{													\
			if (d == 0) return _zero;									\
			else        return max_length_ ## _n_(n);							\
		}

// next index:

	#define NIK_BLOCK_DISPATCH_NEXT_INDEX(_n_)									\
															\
		nik_ces index_type next_index_ ## _n_(cdepth_type d, cindex_type n)					\
		{													\
			if (d == 0) return n;										\
			else        return n - max_index_ ## _n_(n);							\
		}

// (block):

	#define NIK_BEGIN_BLOCK(_p_, _b_, _d_, _n_)									\
															\
		block													\
		<													\
			BN::_b_,											\
			BlockDispatch::next_note(_d_, _n_),								\
			BlockDispatch::next_length_ ## _p_(_d_, _n_)							\
															\
		>::template result											\
		<													\
			BlockDispatch::next_depth(_d_),									\
			BlockDispatch::next_index_ ## _p_(_d_, _n_)

	#define NIK_END_BLOCK												\
															\
		>

	#define NIK_VARIABLE_BLOCK(_p_, _d_, _n_, _h_, _v_)								\
															\
		NIK_BEGIN_BLOCK(_p_, variable, _d_, _n_), _h_, _v_... NIK_END_BLOCK

	#define NIK_FUNCTION_BLOCK(_p_, _d_, _n_, _h_, _v_)								\
															\
		NIK_BEGIN_BLOCK(_p_, function, _d_, _n_), _h_, _v_... NIK_END_BLOCK

	#define NIK_FOLD_BLOCK(_d_, _n_, _o_, _s_, _v_)									\
															\
		NIK_BEGIN_BLOCK(9, fold, _d_, _n_), _s_, _v_... NIK_END_BLOCK(_o_)

	#define NIK_CASCADE_BLOCK(_d_, _n_, _o_, _s_, _v_)								\
															\
		NIK_BEGIN_BLOCK(0, cascade, _d_, _n_), _o_, _s_, _v_... NIK_END_BLOCK()

// pass:

	#define NIK_DEFINE_BLOCK_VARIABLE_PASS(_p_)									\
															\
		template<key_type... filler>										\
		struct block<BN::variable, BT::pass, _p_, filler...>							\
		{													\
			template<auto d, auto n, auto rtn, NIK_2_N_AUTO_VARS(_p_, V), auto... Vs>			\
			nik_ces auto result = NIK_VARIABLE_BLOCK(_p_, d, n, rtn, Vs);					\
		};

	#define NIK_DEFINE_BLOCK_FUNCTION_PASS(_p_)									\
															\
		template<key_type... filler>										\
		struct block<BN::function, BT::pass, _p_, filler...>							\
		{													\
			template<auto d, auto n, auto rtn, NIK_2_N_AUTO_VARS(_p_, V), auto... Vs, auto... Ws>		\
			nik_ces auto result(nik_avp(auto_pack<Ws...>*))				 			\
			{												\
				return NIK_FUNCTION_BLOCK(_p_, d, n, rtn, Vs)						\
						(U_pack_Vs<Ws..., NIK_2_N_VARS(_p_, V)>);				\
			}												\
		};

	#define NIK_DEFINE_BLOCK_SEGMENT_PASS(_p_)									\
															\
		template<key_type... filler>										\
		struct block<BN::segment, BT::pass, _p_, filler...>							\
		{													\
			template<auto d, auto n, auto... Vs>								\
			nik_ces auto result = NIK_BEGIN_BLOCK(_p_, segment, d, n),					\
															\
				Vs..., NIK_2_N_INDEX_SEGMENT(_p_, decltype(n){sizeof...(Vs)})				\
															\
			NIK_END_BLOCK;											\
		};

	#define NIK_DEFINE_BLOCK_FOLD_PASS(_p_)										\
															\
		template<key_type... filler>										\
		struct block<BN::fold, BT::pass, _p_, filler...>							\
		{													\
			template<auto d, auto n, auto V, NIK_2_N_AUTO_VARS(_p_, V), auto... Vs, auto Op, auto... F>	\
			nik_ces auto result(nik_vp(m)(auto_pack<Op, F...>*))						\
			{												\
				return NIK_BEGIN_BLOCK(_p_, fold, d, n),						\
															\
					NIK_2_N_ACTION_FOLDS(_p_, Op, F, V), Vs...					\
															\
				NIK_END_BLOCK(m);									\
			}												\
		};

// machine:

	#define NIK_CONTR_PARAMS											\
															\
		auto d, auto m, auto c, auto i										\

	#define NIK_BEGIN_MACHINE(_d_, _m_, _c_, _i_)									\
															\
		machine													\
		<													\
			MachineDispatch::next_name(_d_, _m_, _c_, _i_),							\
			MachineDispatch::next_note(_d_, _m_, _c_, _i_)							\
															\
		>::template result											\
		<													\
			MachineDispatch::next_depth(_d_),								\
			_m_, _c_,											\
			MachineDispatch::next_index(_d_, _m_, _c_, _i_)

	#define NIK_END_MACHINE 											\
															\
		>

	#define NIK_MACHINE(_d_, _m_, _c_, _i_, _v_)									\
															\
		NIK_BEGIN_MACHINE(_d_, _m_, _c_, _i_),  _v_...  NIK_END_MACHINE

// backend:

namespace cctmp {

// constant:

// [0-10]:

	using key_type  = unsigned char;
	using ckey_type = key_type const;

	nik_ces key_type _zero		=   0;
	nik_ces key_type _one		=   1;
	nik_ces key_type _two		=   2;
	nik_ces key_type _three		=   3;
	nik_ces key_type _four		=   4;
	nik_ces key_type _five		=   5;
	nik_ces key_type _six		=   6;
	nik_ces key_type _seven		=   7;
	nik_ces key_type _eight		=   8;
	nik_ces key_type _nine		=   9;
	nik_ces key_type _ten		=  10;

// [2^0-2^9]:

	using index_type  = unsigned short;
	using cindex_type = index_type const;

	nik_ces index_type _2_0		=   1;
	nik_ces index_type _2_1		=   2;
	nik_ces index_type _2_2		=   4;
	nik_ces index_type _2_3		=   8;
	nik_ces index_type _2_4		=  16;
	nik_ces index_type _2_5		=  32;
	nik_ces index_type _2_6		=  64;
	nik_ces index_type _2_7		= 128;
	nik_ces index_type _2_8		= 256;
	nik_ces index_type _2_9		= 512;

	using depth_type  = unsigned short;
	using cdepth_type = depth_type const;

// module:

	template<key_type...>
	struct module
	{
		nik_ces key_type id			=  0;

		nik_ces key_type store			=  1;
		nik_ces key_type array			=  2;
		nik_ces key_type array_struct		=  3;
	};

	using Module = module<>;

	template<key_type... filler>
	struct module<Module::store, filler...>
	{
		// to:

			template<typename T> nik_ces void store(T) { };

		// from:

			template<typename T> struct match			{ using result = T; };
			template<typename T> struct match<void(*)(T&)>		{ using result = T&; };
			template<typename T> struct match<void(*const)(T&)>	{ using result = T&; };
			template<typename T> struct match<void(*)(T*)>		{ using result = T; };
			template<typename T> struct match<void(*const)(T*)>	{ using result = T; };
	};

	using StoreModule = module<Module::store>;

// T -> U:

	template<typename T>
	constexpr auto U_store_T = StoreModule::store<T*>;

	template<typename T>
	constexpr auto U_store_T<T&> = StoreModule::store<T&>;

// U -> T:

	template<typename T>
	using T_restore_T = typename StoreModule::match<T>::result;

	template<typename T>
	constexpr auto U_restore_T = U_store_T<T_restore_T<T>>;

	template<auto U>
	using T_store_U = T_restore_T<decltype(U)>;

// auto pack:

	template<auto...> struct auto_pack { };

	template<auto... Vs>
	constexpr auto U_pack_Vs = StoreModule::store<auto_pack<Vs...>*>;

	constexpr auto U_null_Vs = U_pack_Vs<>;

// pair:

	template<typename T1, typename T2>
	struct pair
	{
		T1 v1;
		T2 v2;

		constexpr pair(const T1 & _v1, const T2 & _v2) : v1{_v1}, v2{_v2} { }
	};

// array:

	template<typename Type, Type... Vs>
	constexpr Type array[] = { Vs... };

// U -> V:

	template<typename Type, auto... Vs>
	constexpr auto V_array_U(nik_avp(auto_pack<Vs...>*))
		{ return array<Type, Vs...>; }

// V -> U:

	template<auto Arr, auto... Is>
	constexpr auto U_array_V(nik_avp(auto_pack<Is...>*))
		{ return U_pack_Vs<Arr[Is]...>; }

// module:

	template<key_type... filler>
	struct module<Module::array, filler...>
	{
		// copy:

			struct Copy
			{
				template<typename OutIter, typename InIter, typename EndIter>
				nik_ces void result(OutIter out, InIter in, EndIter end)
					{ while (in != end) *(out++) = *(in++); }
			};

		// sequence:

			struct Sequence
			{
				template<auto f, typename OutIter, typename InIter, typename EndIter>
				nik_ces void result(OutIter out, InIter in, EndIter end)
					{ while (in != end) *(out++) = f(in++); }
			};

		// map:

			struct Map
			{
				template<auto f, typename OutIter, typename InIter, typename EndIter>
				nik_ces void result(OutIter out, InIter in, EndIter end)
					{ while (in != end) *(out++) = f(*(in++)); }
			};

		// fold:

			struct Fold
			{
				template<auto f, auto init, typename OutIter, typename InIter, typename EndIter>
				nik_ces void result(OutIter out, InIter in, EndIter end)
				{
					*out = init;

					while (in != end) *out = f(*out, *(in++));
				}
			};

		// find:

			struct Find
			{
				template<auto Size, auto p, typename OutIter, typename InIter, typename EndIter>
				nik_ces void result(OutIter out, InIter in, EndIter end)
				{
					*out = Size;
					InIter in0 = in;

					while ((*out == Size) && (in != end)) if (p(*in)) *out = (in++) - in0;
				}
			};

		// sift:

			struct Sift
			{
				template<auto p, typename OutIter, typename InIter, typename EndIter>
				nik_ces void result(OutIter out, InIter in, EndIter end)
				{
					OutIter out0 = out++;
					InIter   in0 = in;

					while (in != end) if (p(*in)) *(out++) = (in++) - in0;

					*out0 = out - out0;
				}
			};

		// (deducible) sift:

		// zip:

			struct Zip
			{
				template<auto f, typename OutIter, typename In1Iter, typename End1Iter, typename In2Iter>
				nik_ces void result(OutIter out, In1Iter in1, End1Iter end1, In2Iter in2)
					{ while (in1 != end1) *(out++) = f(*(in1++), *(in2++)); }
			};
	};

	using ArrayModule = module<Module::array>;

// array struct:

	template<typename Type, auto Size>
	struct ArrayStruct
	{
		Type value[Size];
	};

// module:

	template<key_type... filler>
	struct module<Module::array_struct, filler...>
	{
		// type:

			template<typename Type, auto Size>
			nik_ces auto type(const ArrayStruct<Type, Size> &) { return U_store_T<Type>; }

		// size:

			template<typename Type, auto Size>
			nik_ces auto size(const ArrayStruct<Type, Size> &) { return Size; }

		// begin:

			template<typename Type, auto Size>
			nik_ces auto begin(ArrayStruct<Type, Size> & arr) { return arr.value; }

		// end:

			template<typename Type, auto Size>
			nik_ces auto end(ArrayStruct<Type, Size> & arr) { return arr.value + Size; }

		// apply:

			template
			<
				typename Type, auto Size,
				typename F, auto InSize, auto... Params,
				typename InType, typename... InTypes
			>
			nik_ces auto apply(InType in, InTypes... ins)
			{
				ArrayStruct<Type, Size> arr{};

				F::template result<Params...>(begin(arr), in, in + InSize, ins...);

				return arr;
			}

		// sift:

			template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
			nik_ces auto sift(nik_vp(indices)(auto_pack<Is...>*))
			{
				constexpr auto Size	= Leng + 1;
				constexpr auto arr	= apply<Type, Size, ArrayModule::Sift, Leng, p>(Arr);
				constexpr auto leng	= arr.value[Leng];

				if constexpr (leng != sizeof...(Is)) return arr;
				else return array<Type, arr.value[Is]...>;
			}
	};

	using ArrayStructModule = module<Module::array_struct>;

// near linear apply:

	// -> V:

		template<typename Type, typename F, auto... As, auto... Ps, auto... Is>
		constexpr auto V_apply(nik_avp(auto_pack<Ps...>*), nik_avp(auto_pack<Is...>*))
		{
			constexpr auto Size	= sizeof...(Is);
			constexpr auto arr	= ArrayStructModule::template apply<Type, Size, F, Ps...>(As...);

			return array<Type, arr.value[Is]...>;
		}

	// -> U:

		template<typename Type, typename F, auto... As, auto... Ps, auto... Is>
		constexpr auto U_apply(nik_avp(auto_pack<Ps...>*), nik_avp(auto_pack<Is...>*))
		{
			constexpr auto Size	= sizeof...(Is);
			constexpr auto arr	= ArrayStructModule::apply<Type, Size, F, Ps...>(As...);

			return U_pack_Vs<arr.value[Is]...>;
		}

// sequence:

	// -> V:

		template<typename Type, auto f, auto Leng, typename Indices>
		constexpr auto V_sequence(Indices indices)
			{ return V_apply<Type, ArrayModule::Sequence, decltype(Leng){0}>(U_pack_Vs<Leng, f>, indices); }

	// -> U:

		template<typename Type, auto f, auto Leng, typename Indices>
		constexpr auto U_sequence(Indices indices)
			{ return U_apply<Type, ArrayModule::Sequence, decltype(Leng){0}>(U_pack_Vs<Leng, f>, indices); }

// map:

	// -> V:

		template<typename Type, auto f, auto Arr, auto Leng, typename Indices>
		constexpr auto V_map(Indices indices)
			{ return V_apply<Type, ArrayModule::Map, Arr>(U_pack_Vs<Leng, f>, indices); }

	// -> U:

		template<typename Type, auto f, auto Arr, auto Leng, typename Indices>
		constexpr auto U_map(Indices indices)
			{ return U_apply<Type, ArrayModule::Map, Arr>(U_pack_Vs<Leng, f>, indices); }

// fold:

	// -> V:

		template<typename Type, auto f, auto init, auto Arr, auto Leng>
		constexpr auto V_fold()
			{ return V_apply<Type, ArrayModule::Fold, Arr>(U_pack_Vs<Leng, f, init>, U_pack_Vs<0>); }

	// -> U:

		template<typename Type, auto f, auto init, auto Arr, auto Leng>
		constexpr auto U_fold()
			{ return U_apply<Type, ArrayModule::Fold, Arr>(U_pack_Vs<Leng, f, init>, U_pack_Vs<0>); }

// find:

	// -> V:

		template<typename Type, auto p, auto Arr, auto Leng>
		constexpr auto V_find()
			{ return V_apply<Type, ArrayModule::Find, Arr>(U_pack_Vs<Leng, Leng, p>, U_pack_Vs<0>); }

	// -> U:

		template<typename Type, auto p, auto Arr, auto Leng>
		constexpr auto U_find()
			{ return U_apply<Type, ArrayModule::Find, Arr>(U_pack_Vs<Leng, Leng, p>, U_pack_Vs<0>); }

// sift:

	// -> V:

		template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
		constexpr auto V_sift(nik_vp(indices)(auto_pack<Is...>*))
		{
			constexpr auto Size	= Leng + 1;
			constexpr auto arr	= ArrayStructModule::template apply<Type, Size, ArrayModule::Sift, Leng, p>(Arr);
			constexpr auto leng	= arr.value[Leng];

			if constexpr (leng != sizeof...(Is)) return arr;
			else return array<Type, arr.value[Is]...>;
		}

/*
		template<typename Type, auto p, auto Arr, auto Leng, auto I0, auto... Is>
		constexpr auto V_sift(nik_vp(indices)(auto_pack<I0, Is...>*))
		{
			constexpr auto Size	= sizeof...(Is) + 1;
			constexpr auto arr	= apply<Type, Size, ArrayModule::Sift, Leng, p>(Arr);

			return array<Type, arr.value[Is]...>;
		}
*/

	// -> U:

/*
		template<typename Type, auto p, auto Arr, auto Leng, auto I0, auto... Is>
		constexpr auto U_sift(nik_vp(indices)(auto_pack<I0, Is...>*))
		{
			constexpr auto Size	= sizeof...(Is) + 1;
			constexpr auto arr	= apply<Type, Size, ArrayModule::Sift, Leng, p>(Arr);

			return U_pack_Vs<arr.value[Is]...>;
		}
*/

// subsequence:

/*
	// -> V:

		template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
		constexpr auto V_subsequence(nik_vp(indices)(auto_pack<Is...>*))
			{ return V_apply<Type, ArrayModule::Sift, Arr>(U_pack_Vs<Leng, sizeof...(Is), p>, indices); }

	// -> U:

		template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
		constexpr auto U_subsequence(nik_vp(indices)(auto_pack<Is...>*))
			{ return U_apply<Type, ArrayModule::Sift, Arr>(U_pack_Vs<Leng, sizeof...(Is), p>, indices); }
*/

// zip:

	// -> V:

		template<typename Type, auto f, auto Arr1, auto Leng1, auto Arr2, typename Indices>
		constexpr auto V_zip(Indices indices)
			{ return V_apply<Type, ArrayModule::Zip, Arr1, Arr2>(U_pack_Vs<Leng1, f>, indices); }

	// -> U:

		template<typename Type, auto f, auto Arr1, auto Leng1, auto Arr2, typename Indices>
		constexpr auto U_zip(Indices indices)
			{ return U_apply<Type, ArrayModule::Zip, Arr1, Arr2>(U_pack_Vs<Leng1, f>, indices); }

// overload:

	struct Overload
	{
		nik_ces key_type id				=  0;

		// comparision:

		nik_ces key_type same				=  1;

		nik_ces key_type equal				=  2;
		nik_ces key_type not_equal			=  3;
		nik_ces key_type less_than			=  4;
		nik_ces key_type less_than_or_equal		=  5;
		nik_ces key_type greater_than			=  6;
		nik_ces key_type greater_than_or_equal		=  7;

		nik_ces key_type is_zero			=  8;
		nik_ces key_type is_value			=  9;

		// logical:

		nik_ces key_type not_				= 10;
		nik_ces key_type and_				= 11;
		nik_ces key_type or_				= 12;

		// bitwise:

		nik_ces key_type upshift			= 13;
		nik_ces key_type downshift			= 14;

		// arithmetic:

		nik_ces key_type add				= 15;
		nik_ces key_type subtract			= 16;
		nik_ces key_type multiply			= 17;
		nik_ces key_type divide				= 18;
		nik_ces key_type modulo				= 19;

		nik_ces key_type increment			= 20;
		nik_ces key_type decrement			= 21;

		// algebraic:

		nik_ces key_type product			= 22;

		// computational:

		nik_ces key_type apply				= 23;
		nik_ces key_type alias				= 24;

		// functional:

		nik_ces key_type length				= 25;
		nik_ces key_type map				= 26;
		nik_ces key_type zip				= 27;

		nik_ces key_type is_null			= 28;
		nik_ces key_type cons				= 29;
		nik_ces key_type push				= 30;
		nik_ces key_type car				= 31;
		nik_ces key_type cdr				= 32;
		nik_ces key_type cadr				= 33;
		nik_ces key_type unite				= 34;
		nik_ces key_type find				= 35;

		nik_ces index_type match(const bool *k, cindex_type size)
		{
			const bool *b = k;
			const bool *e = k + size;

			while (k != e && !*k) ++k;

			return k - b;
		}

		template<key_type Op, auto... Vs>
		nik_ces auto result = U_pack_Vs<Op, Vs...>;
	};

	// comparison:

	template<auto V0, auto V1> constexpr auto Overload::result < Overload::same , V0, V1 > = false;
	template<auto V>           constexpr auto Overload::result < Overload::same , V, V   > = true;

	template<auto... Vs> constexpr auto Overload::result < Overload::equal                 , Vs...> = (... == Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::not_equal             , Vs...> = (... != Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::less_than             , Vs...> = (... <  Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::less_than_or_equal    , Vs...> = (... <= Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::greater_than          , Vs...> = (... >  Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::greater_than_or_equal , Vs...> = (... >= Vs);

	template<auto... Vs> constexpr auto Overload::result < Overload::is_zero               , Vs...> = (... && (Vs == 0));
	template<auto V, auto... Vs> constexpr auto Overload::result < Overload::is_value , V  , Vs...> = (... && (Vs == V));

	// logical:

	template<auto V> constexpr auto Overload::result < Overload::not_                      , V    > = !V;
	template<auto... Vs> constexpr auto Overload::result < Overload::and_                  , Vs...> = (... && Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::or_                   , Vs...> = (... || Vs);

	// bitwise:

	template<auto... Vs> constexpr auto Overload::result < Overload::upshift               , Vs...> = (... << Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::downshift             , Vs...> = (... >> Vs);

	// arithmetic:

	template<auto... Vs> constexpr auto Overload::result < Overload::add                   , Vs...> = (... +  Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::subtract              , Vs...> = (... -  Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::multiply              , Vs...> = (... *  Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::divide                , Vs...> = (... /  Vs);
	template<auto... Vs> constexpr auto Overload::result < Overload::modulo                , Vs...> = (... %  Vs);

	template<auto V>     constexpr auto Overload::result < Overload::increment             , V    > = V+1;
	template<auto V>     constexpr auto Overload::result < Overload::decrement             , V    > = V-1;

	// algebraic:

	template<auto V0, auto V1> constexpr auto Overload::result < Overload::product      , V0 , V1 > = pair(V0, V1);

	// computational:

	template<auto F, auto... Vs>
	constexpr auto Overload::result < Overload::apply , F , Vs... > = F(Vs...);

	template<auto F, auto... Vs>
	constexpr auto Overload::result < Overload::alias , F , Vs... > = T_store_U<F>::template result<Vs...>;

	// functional:

	template<auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto Overload::result < Overload::length , p > = sizeof...(Vs);

	template
	<
		auto Op, auto... F, nik_vp(op)(auto_pack<Op, F...>*),
		auto... Vs, nik_vp(p)(auto_pack<Vs...>*)
	>
	constexpr auto Overload::result < Overload::map , op , p > = U_pack_Vs
	<
		Overload::template result<Op, F..., Vs>...
	>;

	template
	<
		auto Op, auto... F, nik_vp(op)(auto_pack<Op, F...>*),
		auto... Vs, nik_vp(p0)(auto_pack<Vs...>*),
		auto... Ws, nik_vp(p1)(auto_pack<Ws...>*)
	>
	constexpr auto Overload::result < Overload::zip , op , p0 , p1 > = U_pack_Vs
	<
		Overload::template result<Op, F..., Vs, Ws>...
	>;

	template<auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto Overload::result < Overload::is_null , p > = (sizeof...(Vs) == 0);

	template<auto V0, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto Overload::result < Overload::cons , V0, p > = U_pack_Vs<V0, Vs...>;

	template<auto V0, auto... Vs, nik_vp(p)(auto_pack<Vs...>*)>
	constexpr auto Overload::result < Overload::push , V0, p > = U_pack_Vs<Vs..., V0>;

	template<auto V0, auto... Vs, nik_vp(p)(auto_pack<V0, Vs...>*)>
	constexpr auto Overload::result < Overload::car , p > = V0;

	template<auto V0, auto... Vs, nik_vp(p)(auto_pack<V0, Vs...>*)>
	constexpr auto Overload::result < Overload::cdr , p > = U_pack_Vs<Vs...>;

	template<auto V0, auto V1, auto... Vs, nik_vp(p)(auto_pack<V0, V1, Vs...>*)>
	constexpr auto Overload::result < Overload::cadr , p > = V1;

	template<auto... Vs, nik_vp(p0)(auto_pack<Vs...>*), auto... Ws, nik_vp(p1)(auto_pack<Ws...>*), auto... Xs>
	constexpr auto Overload::result < Overload::unite , p0, p1, Xs... > = U_pack_Vs<Vs..., Xs..., Ws...>;

	template
	<
		auto Op, auto... F, nik_vp(op)(auto_pack<Op, F...>*),
		auto... Vs, nik_vp(p)(auto_pack<Vs...>*),
		auto... Ws
	>
	constexpr auto Overload::result < Overload::find , op , p , Ws... > = Overload::match
	(
		array<bool, Overload::template result<Op, F..., Ws..., Vs>...>, sizeof...(Vs)
	);

	// comparision:

	template<auto... Vs> constexpr auto same_op			= U_pack_Vs<Overload::same, Vs...>;

	template<auto... Vs> constexpr auto equal_op			= U_pack_Vs<Overload::equal, Vs...>;
	template<auto... Vs> constexpr auto not_equal_op		= U_pack_Vs<Overload::not_equal, Vs...>;
	template<auto... Vs> constexpr auto less_than_op		= U_pack_Vs<Overload::less_than, Vs...>;
	template<auto... Vs> constexpr auto less_than_or_equal_op	= U_pack_Vs<Overload::less_than_or_equal, Vs...>;
	template<auto... Vs> constexpr auto greater_than_op		= U_pack_Vs<Overload::greater_than, Vs...>;
	template<auto... Vs> constexpr auto greater_than_or_equal_op	= U_pack_Vs<Overload::greater_than_or_equal, Vs...>;

	template<auto... Vs> constexpr auto is_zero_op			= U_pack_Vs<Overload::is_zero, Vs...>;
	template<auto... Vs> constexpr auto is_value_op			= U_pack_Vs<Overload::is_value, Vs...>;

	// logical:

	template<auto... Vs> constexpr auto not__op			= U_pack_Vs<Overload::not_, Vs...>;
	template<auto... Vs> constexpr auto and__op			= U_pack_Vs<Overload::and_, Vs...>;
	template<auto... Vs> constexpr auto or__op			= U_pack_Vs<Overload::or_, Vs...>;

	// bitwise:

	template<auto... Vs> constexpr auto upshift_op			= U_pack_Vs<Overload::upshift, Vs...>;
	template<auto... Vs> constexpr auto downshift_op		= U_pack_Vs<Overload::downshift, Vs...>;

	// arithmetic:

	template<auto... Vs> constexpr auto add_op			= U_pack_Vs<Overload::add, Vs...>;
	template<auto... Vs> constexpr auto subtract_op			= U_pack_Vs<Overload::subtract, Vs...>;
	template<auto... Vs> constexpr auto multiply_op			= U_pack_Vs<Overload::multiply, Vs...>;
	template<auto... Vs> constexpr auto divide_op			= U_pack_Vs<Overload::divide, Vs...>;
	template<auto... Vs> constexpr auto modulo_op			= U_pack_Vs<Overload::modulo, Vs...>;

	template<auto... Vs> constexpr auto increment_op		= U_pack_Vs<Overload::increment, Vs...>;
	template<auto... Vs> constexpr auto decrement_op		= U_pack_Vs<Overload::decrement, Vs...>;

	// algebraic:

	template<auto... Vs> constexpr auto product_op			= U_pack_Vs<Overload::product, Vs...>;

	// computational:

	template<auto... Vs> constexpr auto apply_op			= U_pack_Vs<Overload::apply, Vs...>;
	template<auto... Vs> constexpr auto alias_op			= U_pack_Vs<Overload::alias, Vs...>;

	// functional:

	template<auto... Vs> constexpr auto length_op			= U_pack_Vs<Overload::length, Vs...>;
	template<auto... Vs> constexpr auto map_op			= U_pack_Vs<Overload::map, Vs...>;
	template<auto... Vs> constexpr auto zip_op			= U_pack_Vs<Overload::zip, Vs...>;

	template<auto... Vs> constexpr auto is_null_op			= U_pack_Vs<Overload::is_null, Vs...>;
	template<auto... Vs> constexpr auto cons_op			= U_pack_Vs<Overload::cons, Vs...>;
	template<auto... Vs> constexpr auto push_op			= U_pack_Vs<Overload::push, Vs...>;
	template<auto... Vs> constexpr auto car_op			= U_pack_Vs<Overload::car, Vs...>;
	template<auto... Vs> constexpr auto cdr_op			= U_pack_Vs<Overload::cdr, Vs...>;
	template<auto... Vs> constexpr auto unite_op			= U_pack_Vs<Overload::unite, Vs...>;
	template<auto... Vs> constexpr auto find_op			= U_pack_Vs<Overload::find, Vs...>;

// machination:

	template<typename T1, typename T2>
	struct machination
	{
		T1 s1;
		T2 s2;

		constexpr machination(const T1 & _s1, const T2 & _s2) : s1{_s1}, s2{_s2} { }
	};

// is machination:

	template<typename T>
	constexpr bool is_machination = false;

	template<typename T1, typename T2> constexpr bool is_machination <       machination<T1, T2>   > = true;
	template<typename T1, typename T2> constexpr bool is_machination < const machination<T1, T2>   > = true;
	template<typename T1, typename T2> constexpr bool is_machination < const machination<T1, T2> & > = true;

// machine:

	template<key_type, key_type, key_type...> struct machine;

// names:

	struct MachineName
	{
		nik_ces key_type id				=  0;
		nik_ces key_type identity			= id; // convenience for
								      // default params.

		nik_ces key_type recall				=  1;
		nik_ces key_type call				=  2;
		nik_ces key_type halt				=  3;

		nik_ces key_type move_j_all			=  4;

		nik_ces key_type paste_r_all			=  5;
		nik_ces key_type paste_a_all			=  6;

		nik_ces key_type go_to				=  7;

		nik_ces key_type memoize			=  8;
	};

	using MN = MachineName;

// notes:

	struct MachineNote
	{
		nik_ces key_type id				=  0;
		nik_ces key_type identity			= id;	// convenience for
									// default params.

		nik_ces key_type action				=  1;

		nik_ces key_type copy_r_pos			=  2;
		nik_ces key_type copy_j_pos			=  3;
		nik_ces key_type copy_c_pos			=  4;
		nik_ces key_type copy_a_pos			=  5;
		nik_ces key_type copy				=  6;

		nik_ces key_type cut_r_pos			=  7;
		nik_ces key_type cut_a_pos			=  8;
		nik_ces key_type cut				=  9;

		nik_ces key_type variable			= 10;
		nik_ces key_type function			= 11;
		nik_ces key_type cascade			= 12;
		nik_ces key_type compel				= 13;
		nik_ces key_type propel				= 14;
		nik_ces key_type internal			= 15;

		nik_ces key_type pause				= 16;

		nik_ces key_type conditional			= 17;

		nik_ces key_type lookup				= 18;
		nik_ces key_type insert				= 19;
	};

	using MT = MachineNote;

// instructions:

	struct MachineInstr
	{
		using type						= index_type const * const;

		nik_ces key_type size					= 0;
		nik_ces key_type name					= 1;
		nik_ces key_type note					= 2;

		nik_ces key_type pos					= 3;
		nik_ces key_type dec					= 3;
		nik_ces key_type rtn					= 3;

		nik_ces key_type ctn					= 4;
		nik_ces key_type act					= 5;

		// locations:

		nik_ces key_type _register				= 0;
		nik_ces key_type _junction				= 1;
		nik_ces key_type _constant				= 2;
		nik_ces key_type _argument				= 3;

		// actions:

		nik_ces key_type h0					= 0;
		nik_ces key_type h0_write				= 1;
		nik_ces key_type h1					= 2;
		nik_ces key_type h1_pair				= 3; // C++17 specific.
		nik_ces key_type value					= 4;

		nik_ces index_type length     (type i)			{ return i[size]; }
		nik_ces bool       is_optimal (cindex_type n)		{ return (n < _eight); }

		nik_ces auto copy_note(ckey_type l)
		{
			if      (l == _register) return MT::copy_r_pos;
			else if (l == _junction) return MT::copy_j_pos;
			else if (l == _constant) return MT::copy_c_pos;
			else                     return MT::copy_a_pos;
		}

		nik_ces auto cut_note(ckey_type l)
		{
			if   (l == _register) return MT::cut_r_pos;
			else                  return MT::cut_a_pos;
		}

		nik_ces auto paste_name(ckey_type l)
		{
			if   (l == _register) return MN::paste_r_all;
			else                  return MN::paste_a_all;
		}
	};

	using MI			= MachineInstr;
	using instr_type		= typename MI::type;

	constexpr auto _register	= MI::_register;
	constexpr auto _junction	= MI::_junction;
	constexpr auto _constant	= MI::_constant;
	constexpr auto _argument	= MI::_argument;

	constexpr auto _h0		= MI::h0;
	constexpr auto _h0_write	= MI::h0_write;
	constexpr auto _h1		= MI::h1;
	constexpr auto _h1_pair		= MI::h1_pair;
	constexpr auto _value		= MI::value;

	template<index_type... Vs>
	constexpr instr_type instruction = array<index_type, sizeof...(Vs), Vs...>;

// controllers:

	struct MachineContr
	{
		using type						= instr_type const * const;

		nik_ces key_type size					= 0;

		nik_ces index_type length (type l)			{ return l[size][MI::size]; }
	};

	using MC								= MachineContr;
	using contr_type							= typename MC::type;

	template<instr_type... Vs>
	constexpr contr_type controller = array<instr_type, array<index_type, sizeof...(Vs)>, Vs...>;

// dispatch:

	struct MachineDispatch
	{
		// defaults:

			nik_ces depth_type initial_depth = 500;
			nik_ces index_type initial_index = _zero;

		// accessors:

			nik_ces auto instr(contr_type c, cindex_type i)
				{ return c[i]; }

		// navigators:

			nik_ces key_type next_name(cdepth_type d, ckey_type m, contr_type c, cindex_type i)
			{
				if (d == 0)		return MN::halt;
				else if (m != MT::id)	return MN::recall;
				else			return c[i+1][MI::name];
			}

			nik_ces key_type next_note(cdepth_type d, ckey_type m, contr_type c, cindex_type i)
			{
				if (d == 0)		return MT::pause;
				else if (m != MT::id)	return m;
				else			return c[i+1][MI::note];
			}

			nik_ces depth_type next_depth(cdepth_type d)
				{ return d - bool{d != 0}; }

			nik_ces index_type next_index(cdepth_type d, ckey_type m, contr_type, cindex_type i)
				{ return i + bool{d != 0 && m == MT::id}; }
	};

// block:

	template<key_type...> struct block;

// names:

	struct BlockName
	{
		nik_ces key_type id		=  0;

		nik_ces key_type variable	=  1;
		nik_ces key_type function	=  2;

		nik_ces key_type segment	=  3;
		nik_ces key_type fold		=  4;
		nik_ces key_type cascade	=  5;

		nik_ces key_type sifter		=  6;
		nik_ces key_type right		=  7;
		nik_ces key_type lookup		=  8;

		nik_ces key_type filter		=  9;
		nik_ces key_type left		= 10;
		nik_ces key_type split		= 11;
	};

	using BN = BlockName;

// notes:

	struct BlockNote
	{
		nik_ces key_type id		= 0;

		nik_ces key_type pause		= 1;
		nik_ces key_type halt		= 2;
		nik_ces key_type pass		= 3;
	};

	using BT = BlockNote;

// dispatch:

	struct BlockDispatch
	{
		// length:

		nik_ces key_type max_length_0(cindex_type n) { if (n >= _2_0) return 0; else return _zero; }
		nik_ces key_type max_length_1(cindex_type n) { if (n >= _2_1) return 1; else return max_length_0(n); }
		nik_ces key_type max_length_2(cindex_type n) { if (n >= _2_2) return 2; else return max_length_1(n); }
		nik_ces key_type max_length_3(cindex_type n) { if (n >= _2_3) return 3; else return max_length_2(n); }
		nik_ces key_type max_length_4(cindex_type n) { if (n >= _2_4) return 4; else return max_length_3(n); }
		nik_ces key_type max_length_5(cindex_type n) { if (n >= _2_5) return 5; else return max_length_4(n); }
		nik_ces key_type max_length_6(cindex_type n) { if (n >= _2_6) return 6; else return max_length_5(n); }
		nik_ces key_type max_length_7(cindex_type n) { if (n >= _2_7) return 7; else return max_length_6(n); }
		nik_ces key_type max_length_8(cindex_type n) { if (n >= _2_8) return 8; else return max_length_7(n); }
		nik_ces key_type max_length_9(cindex_type n) { if (n >= _2_9) return 9; else return max_length_8(n); }

		// index:

		nik_ces index_type max_index_0(cindex_type n) { if (n >= _2_0) return _2_0; else return _zero; }
		nik_ces index_type max_index_1(cindex_type n) { if (n >= _2_1) return _2_1; else return max_index_0(n); }
		nik_ces index_type max_index_2(cindex_type n) { if (n >= _2_2) return _2_2; else return max_index_1(n); }
		nik_ces index_type max_index_3(cindex_type n) { if (n >= _2_3) return _2_3; else return max_index_2(n); }
		nik_ces index_type max_index_4(cindex_type n) { if (n >= _2_4) return _2_4; else return max_index_3(n); }
		nik_ces index_type max_index_5(cindex_type n) { if (n >= _2_5) return _2_5; else return max_index_4(n); }
		nik_ces index_type max_index_6(cindex_type n) { if (n >= _2_6) return _2_6; else return max_index_5(n); }
		nik_ces index_type max_index_7(cindex_type n) { if (n >= _2_7) return _2_7; else return max_index_6(n); }
		nik_ces index_type max_index_8(cindex_type n) { if (n >= _2_8) return _2_8; else return max_index_7(n); }
		nik_ces index_type max_index_9(cindex_type n) { if (n >= _2_9) return _2_9; else return max_index_8(n); }

		// note:

			nik_ces key_type next_note(cdepth_type d, cindex_type n)
			{
				if      (d == 0) return BT::pause;
				else if (n == 0) return BT::halt;
				else             return BT::pass;
			}

		// length:

			NIK_BLOCK_DISPATCH_NEXT_LENGTH(0)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(1)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(2)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(3)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(4)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(5)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(6)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(7)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(8)
			NIK_BLOCK_DISPATCH_NEXT_LENGTH(9)

		// depth:

			nik_ces depth_type next_depth(cdepth_type d)
				{ return d - bool{d != 0}; }

		// index:

			NIK_BLOCK_DISPATCH_NEXT_INDEX(0)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(1)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(2)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(3)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(4)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(5)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(6)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(7)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(8)
			NIK_BLOCK_DISPATCH_NEXT_INDEX(9)
	};

// halters:

	// sifter:

		template<key_type... filler>
		struct block<BN::sifter, filler...>
		{
			template<auto V0, auto... Vs>
			nik_ces auto result = V0;
		};

	// right:

		template<key_type... filler>
		struct block<BN::right, filler...>
		{
			template<auto... Vs>
			nik_ces auto result = U_pack_Vs<Vs...>;
		};

	// lookup:

		template<key_type... filler>
		struct block<BN::lookup, filler...>
		{
			template<auto V0, auto... Vs>
			nik_ces auto result = Overload::template result<Overload::cadr, V0>;
		};

	// filter:

		template<key_type... filler>
		struct block<BN::filter, filler...>
		{
			template<auto V0, auto... Vs, typename Pack>
			nik_ces auto result(Pack p) { return pair(p, U_pack_Vs<Vs...>); }
		};

	// left:

		template<key_type... filler>
		struct block<BN::left, filler...>
		{
			template<auto... Vs, typename Pack>
			nik_ces auto result(Pack p) { return p; }
		};

	// split:

		template<key_type... filler>
		struct block<BN::split, filler...>
		{
			template<auto... Vs, typename Pack>
			nik_ces auto result(Pack p) { return pair(p, U_pack_Vs<Vs...>); }
		};

// variable:

	template<key_type... filler>
	struct block<BN::variable, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto rtn, auto... Vs>
		nik_ces auto result = machination(U_pack_Vs<rtn>, U_pack_Vs<n, Vs...>);
	};

	template<key_type... filler>
	struct block<BN::variable, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto rtn, auto... Vs>
		nik_ces auto result = block<rtn>::template result<Vs...>;
	};

	NIK_DEFINE_BLOCK_VARIABLE_PASS(0)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(1)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(2)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(3)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(4)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(5)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(6)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(7)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(8)
	NIK_DEFINE_BLOCK_VARIABLE_PASS(9)

// function:

	template<key_type... filler>
	struct block<BN::function, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto rtn, auto... Vs, typename Pack>
		nik_ces auto result(Pack p) { return machination(U_pack_Vs<rtn>, U_pack_Vs<U_restore_T<Pack>, n, Vs...>); }
	};

	template<key_type... filler>
	struct block<BN::function, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto rtn, auto... Vs, typename Pack>
		nik_ces auto result(Pack p) { return block<rtn>::template result<Vs...>(p); }
	};

	NIK_DEFINE_BLOCK_FUNCTION_PASS(0)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(1)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(2)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(3)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(4)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(5)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(6)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(7)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(8)
	NIK_DEFINE_BLOCK_FUNCTION_PASS(9)

// segment:

	template<key_type... filler>
	struct block<BN::segment, BT::pause, _zero, filler...>
	{
		nik_ces auto s1 = U_pack_Vs<BN::segment>;

		template<auto d, auto n, auto... Vs>
		nik_ces auto result = machination(s1, U_pack_Vs<n, Vs...>);
	};

	template<key_type... filler>
	struct block<BN::segment, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto... Vs>
		nik_ces auto result = U_pack_Vs<Vs...>;
	};

	NIK_DEFINE_BLOCK_SEGMENT_PASS(0)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(1)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(2)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(3)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(4)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(5)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(6)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(7)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(8)
	NIK_DEFINE_BLOCK_SEGMENT_PASS(9)

// (action) fold:

	template<key_type... filler>
	struct block<BN::fold, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto V, auto... Vs, auto Op, auto... F>
		nik_ces auto result(nik_vp(m)(auto_pack<Op, F...>*)) { return machination(m, U_pack_Vs<n, V, Vs...>); }
	};

	template<key_type... filler>
	struct block<BN::fold, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto V, auto... Vs, auto Op, auto... F>
		nik_ces auto result(nik_vp(m)(auto_pack<Op, F...>*)) { return V; }
	};

	NIK_DEFINE_BLOCK_FOLD_PASS(0)
	NIK_DEFINE_BLOCK_FOLD_PASS(1)
	NIK_DEFINE_BLOCK_FOLD_PASS(2)
	NIK_DEFINE_BLOCK_FOLD_PASS(3)
	NIK_DEFINE_BLOCK_FOLD_PASS(4)
	NIK_DEFINE_BLOCK_FOLD_PASS(5)
	NIK_DEFINE_BLOCK_FOLD_PASS(6)
	NIK_DEFINE_BLOCK_FOLD_PASS(7)
	NIK_DEFINE_BLOCK_FOLD_PASS(8)
	NIK_DEFINE_BLOCK_FOLD_PASS(9)

// cascade (compel fold):

	template<key_type... filler>
	struct block<BN::cascade, BT::pause, _zero, filler...>
	{
		template<auto d, auto n, auto Op, auto V, auto... Vs>
		nik_ces auto result()
		{
			return machination(U_pack_Vs<Op>, U_pack_Vs<BT::pause, n, V, Vs...>);
		}
	};

	template<key_type... filler>
	struct block<BN::cascade, BT::halt, _zero, filler...>
	{
		template<auto d, auto n, auto Op, auto V, auto... Vs>
		nik_ces auto result() { return V; }
	};

	template<key_type... filler>
	struct block<BN::cascade, BT::pass, _zero, filler...>
	{
		template<auto d, auto n, auto Op, auto V, auto V0, auto... Vs>
		nik_ces auto result()
		{
			constexpr auto val = T_store_U<Op>::template result<d, V, V0>;

			if constexpr (is_machination<decltype(val)>)

				return machination(U_pack_Vs<Op>, U_pack_Vs<BT::id, n, val.s1, val.s2, Vs...>);
			else
				return NIK_CASCADE_BLOCK(d, n, Op, val, Vs);
		}
	};

// call/recall:

// action:

	// call:

		template<key_type... filler>
		struct machine<MN::call, MT::action, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto... Xs, typename... Heaps>
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::dec];

				if constexpr (n >= d) // analogous to returning a machination.

					return NIK_MACHINE(0, MT::action, c, i, Vs)(H0, H1, Hs...);
				else
				{
					constexpr auto ctn = ins[MI::ctn];
					constexpr auto act = ins[MI::act];
					constexpr auto val = Overload::template result<act, Ws...>;

					if constexpr (ctn == MI::h1)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

					else if constexpr (ctn == MI::h1_pair)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
					else
						return val;
				}
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::action, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto... Xs, typename... Heaps>
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::dec];

				if constexpr (n >= d) // analogous to returning a machination.

					return NIK_MACHINE(0, MT::action, c, i, Vs)(H0, H1, Hs...);
				else
				{
					constexpr auto ctn	= ins[MI::ctn];
					constexpr auto act	= ins[MI::act];
					constexpr auto val	= Overload::template result<act, Ws...>;

					if constexpr (ctn == MI::h1)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

					else if constexpr (ctn == MI::h1_pair)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
					else
						return val;
				}
			}
		};

// copy:

	// register:

		template<key_type... filler>
		struct machine<MN::call, MT::copy_r_pos, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, typename... Heaps>
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), Heaps... Hs)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::pos];
				constexpr auto ctn	= ins[MI::ctn];
				constexpr auto val	= NIK_VARIABLE_BLOCK(3, d, n, BN::sifter, Vs);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.s1, val.s2, H0, Hs...);

				else if constexpr (ctn == MI::h0)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, Hs...);

				else if constexpr (ctn == MI::h0_write)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(val, Hs...);
				else
					return val;
			}
		};

	// junction:

		template<key_type... filler>
		struct machine<MN::call, MT::copy_j_pos, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto... Xs, typename... Heaps>
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::pos];
				constexpr auto ctn	= ins[MI::ctn];
				constexpr auto val	= NIK_VARIABLE_BLOCK(3, d, n, BN::sifter, Xs);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.s1, val.s2, H0, H1, Hs...);

				else if constexpr (ctn == MI::h0)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, H1, Hs...);

				else if constexpr (ctn == MI::h0_write)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(val, H1, Hs...);
				else
					return val;
			}
		};

	// constant:

		template<key_type... filler>
		struct machine<MN::call, MT::copy_c_pos, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto... Ws, typename Heap1, auto... Ys, typename... Args
			>
			nik_ces auto result
			(
				nik_vp(H0)(auto_pack<Ws...>*), Heap1 H1,
				nik_vp(H2)(auto_pack<Ys...>*), Args... As
			)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::pos];
				constexpr auto ctn	= ins[MI::ctn];
				constexpr auto val	= NIK_VARIABLE_BLOCK(3, d, n, BN::sifter, Ys);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.s1, val.s2, H0, H1, H2, As...);

				else if constexpr (ctn == MI::h0)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, H1, H2, As...);

				else if constexpr (ctn == MI::h0_write)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(val, H1, H2, As...);
				else
					return val;
			}
		};

	// argument:

		template<key_type... filler>
		struct machine<MN::call, MT::copy_a_pos, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto... Ws, typename Heap1, typename Heap2, typename... Args
			>
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), Heap1 H1, Heap2 H2, Args... As)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::pos];
				constexpr auto ctn	= ins[MI::ctn];
				constexpr auto val	= NIK_VARIABLE_BLOCK(3, d, n, BN::sifter, U_restore_T<Args>);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.s1, val.s2, H0, H1, H2, As...);

				else if constexpr (ctn == MI::h0)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, H1, H2, As...);

				else if constexpr (ctn == MI::h0_write)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(val, H1, H2, As...);
				else
					return val;
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::copy, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto rtn, auto n, auto... _Vs,
				auto... Ws, typename... Heaps
			>
			nik_ces auto result
			(
				nik_avp(auto_pack<rtn>*), nik_avp(auto_pack<n, _Vs...>*),
				nik_vp(H0)(auto_pack<Ws...>*), Heaps... Hs
			)
			{
				constexpr auto ins = MachineDispatch::instr(c, i);
				constexpr auto ctn = ins[MI::ctn];
				constexpr auto val = NIK_VARIABLE_BLOCK(3, d, n, rtn, _Vs);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::copy, c, i, Vs)(val.s1, val.s2, H0, Hs...);

				else if constexpr (ctn == MI::h0)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., val>, Hs...);

				else if constexpr (ctn == MI::h0_write)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(val, Hs...);
				else
					return val;
			}
		};

// cut:

	// register:

		template<key_type... filler>
		struct machine<MN::call, MT::cut_r_pos, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, typename Heap0, auto X0, auto... Xs, typename... Heaps>
			nik_ces auto result(Heap0 H0, nik_vp(H1)(auto_pack<X0, Xs...>*), Heaps... Hs)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::pos];
				constexpr auto val	= NIK_FUNCTION_BLOCK(3, d, n, BN::filter, Vs)(U_null_Vs);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::cut, c, i, Vs)(val.s1, val.s2, H1, Hs...);
				else
				{
					constexpr auto h0 = Overload::template result<Overload::unite, val.v1, val.v2, X0>;

					return NIK_MACHINE(d, MT::id, c, i, Vs)(h0, U_pack_Vs<Xs...>, Hs...);
				}
			}
		};

	// argument:

		template<key_type... filler>
		struct machine<MN::call, MT::cut_a_pos, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				typename Heap0, auto X0, auto... Xs, typename Heap2, typename... Args
			>
			nik_ces auto result(Heap0 H0, nik_vp(H1)(auto_pack<X0, Xs...>*), Heap2 H2, Args... As)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::pos];
				constexpr auto val	= NIK_FUNCTION_BLOCK(3, d, n, BN::filter, U_restore_T<Args>)(U_null_Vs);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::cut, c, i, Vs)(val.s1, val.s2, H1, H2, As...);
				else
				{
					constexpr auto h0 = Overload::template result<Overload::unite, val.v1, val.v2, X0>;

					return NIK_MACHINE(d, MT::id, c, i, Vs)(h0, U_pack_Vs<Xs...>, H2, As...);
				}
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::cut, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto rtn, auto pack, auto n, auto... _Vs,
				auto X0, auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_avp(auto_pack<rtn>*), nik_avp(auto_pack<pack, n, _Vs...>*),
				nik_vp(H1)(auto_pack<X0, Xs...>*), Heaps... Hs
			)
			{
				constexpr auto val = NIK_FUNCTION_BLOCK(3, d, n, rtn, _Vs)(pack);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::cut, c, i, Vs)(val.s1, val.s2, H1, Hs...);
				else
				{
					constexpr auto h0 = Overload::template result<Overload::unite, val.v1, val.v2, X0>;

					return NIK_MACHINE(d, MT::id, c, i, Vs)(h0, U_pack_Vs<Xs...>, Hs...);
				}
			}
		};

// variable:

	// call:

		template<key_type... filler>
		struct machine<MN::call, MT::variable, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto n, auto... Xs, typename... Heaps> 
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<n, Xs...>*), Heaps... Hs)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto rtn	= ins[MI::rtn];
				constexpr auto ctn	= ins[MI::ctn];
				constexpr auto val	= NIK_VARIABLE_BLOCK(9, d, n, rtn, Ws);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::variable, c, i, Vs)(val.s1, val.s2, H1, Hs...);

				else if constexpr (ctn == MI::h1)

					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

				else if constexpr (ctn == MI::h1_pair)

					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
				else
					return val;
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::variable, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto rtn, auto n, auto... _Vs,
				auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_avp(auto_pack<rtn>*), nik_avp(auto_pack<n, _Vs...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				constexpr auto ins = MachineDispatch::instr(c, i);
				constexpr auto ctn = ins[MI::ctn];
				constexpr auto val = NIK_VARIABLE_BLOCK(9, d, n, rtn, _Vs);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::variable, c, i, Vs)(val.s1, val.s2, H1, Hs...);

				else if constexpr (ctn == MI::h1)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

				else if constexpr (ctn == MI::h1_pair)

					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
				else
					return val;
			}
		};

// function:

	// call:

		template<key_type... filler>
		struct machine<MN::call, MT::function, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto n, auto... Xs, typename... Heaps>
			nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<n, Xs...>*), Heaps... Hs)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto rtn	= ins[MI::rtn];
				constexpr auto ctn	= ins[MI::ctn];
				constexpr auto val	= NIK_FUNCTION_BLOCK(9, d, n, rtn, Ws)(U_null_Vs);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::function, c, i, Vs)(val.s1, val.s2, H1, Hs...);

				else if constexpr (ctn == MI::h1 || ctn == MI::h1_pair)

					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
				else
					return val;
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::function, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto rtn, auto pack, auto n, auto... _Vs,
				auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_avp(auto_pack<rtn>*), nik_avp(auto_pack<pack, n, _Vs...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				constexpr auto val = NIK_FUNCTION_BLOCK(9, d, n, rtn, _Vs)(pack);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::function, c, i, Vs)(val.s1, val.s2, H1, Hs...);
				else
					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
			}
		};

// cascade:

	// call:

		template<key_type... filler>
		struct machine<MN::call, MT::cascade, filler...>
		{
			template<NIK_CONTR_PARAMS, auto... Vs, auto Op, auto W0, auto... Ws, auto n, auto... Xs, typename... Heaps>
			nik_ces auto result(nik_vp(H0)(auto_pack<Op, W0, Ws...>*), nik_vp(H1)(auto_pack<n, Xs...>*), Heaps... Hs)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto rtn	= ins[MI::rtn];
				constexpr auto ctn	= ins[MI::ctn];
				constexpr auto val	= NIK_CASCADE_BLOCK(d, n, Op, W0, Ws);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::cascade, c, i, Vs)(val.s1, val.s2, H1, Hs...);

				else if constexpr (ctn == MI::h1)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);
				else
					return val;
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::cascade, filler...>
		{
			// BT::id:

			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				typename OpType, auto n, auto _s1, auto _s2, auto... _Vs,
				auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				OpType op, nik_avp(auto_pack<BT::id, n, _s1, _s2, _Vs...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				constexpr auto _c	= controller<instruction<MN::call, MT::internal>>;
				constexpr auto _i	= MachineDispatch::initial_index;
				constexpr auto val	= NIK_BEGIN_MACHINE(d, MT::internal, _c, _i)
								NIK_END_MACHINE(_s1, _s2);

				if constexpr (is_machination<decltype(val)>)
				{
					constexpr auto s2 = U_pack_Vs<BT::id, n, val.s1, val.s2, _Vs...>;

					return NIK_MACHINE(d, MT::cascade, c, i, Vs)(op, s2, H1, Hs...);
				}
				else
					return NIK_MACHINE(d, MT::cascade, c, i, Vs)
						(op, U_pack_Vs<BT::pause, n, val, _Vs...>, H1, Hs...);
			}

			// BT::pause:

			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto Op, auto n, auto _V, auto... _Vs,
				auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_avp(auto_pack<Op>*), nik_avp(auto_pack<BT::pause, n, _V, _Vs...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				constexpr auto val = NIK_CASCADE_BLOCK(d, n, Op, _V, _Vs);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::cascade, c, i, Vs)(val.s1, val.s2, H1, Hs...);
				else
					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);
			}
		};

// compel:

	// call:

		template<key_type... filler>
		struct machine<MN::call, MT::compel, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto Op, auto... Ws, auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_vp(H0)(auto_pack<Op, Ws...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::dec];

				if constexpr (n >= d) // analogous to returning a machination.

					return NIK_MACHINE(0, MT::compel, c, i, Vs)(H0, H1, Hs...);
				else
				{
					constexpr auto ctn	= ins[MI::ctn];
					constexpr auto nd	= d+1-n;
					constexpr auto val	= T_store_U<Op>::template result<nd, Ws...>;

					if constexpr (is_machination<decltype(val)>)

						return NIK_MACHINE(d, MT::propel, c, i, Vs)(val.s1, val.s2, H1, Hs...);

					else if constexpr (ctn == MI::h1)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

					else if constexpr (ctn == MI::h1_pair)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
					else
						return val;
				}
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::compel, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto Op, auto... Ws, auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_vp(H0)(auto_pack<Op, Ws...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				constexpr auto ins	= MachineDispatch::instr(c, i);
				constexpr auto n	= ins[MI::dec];

				if constexpr (n >= d) // analogous to returning a machination.

					return NIK_MACHINE(0, MT::compel, c, i, Vs)(H0, H1, Hs...);
				else
				{
					constexpr auto ctn	= ins[MI::ctn];
					constexpr auto nd	= d+1-n;
					constexpr auto val	= T_store_U<Op>::template result<nd, Ws...>;

					if constexpr (is_machination<decltype(val)>)

						return NIK_MACHINE(d, MT::propel, c, i, Vs)(val.s1, val.s2, H1, Hs...);

					else if constexpr (ctn == MI::h1)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

					else if constexpr (ctn == MI::h1_pair)

						return NIK_MACHINE(d, MT::id, c, i, Vs)
							(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
					else
						return val;
				}
			}
		};

// propel:

	// call: No direct call.

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::propel, filler...>
		{
			template
			<
				NIK_CONTR_PARAMS, auto... Vs,
				auto _m, auto _c, auto _i, auto... _Vs,
				auto... _Hs, auto... Xs, typename... Heaps
			>
			nik_ces auto result
			(
				nik_avp(auto_pack<_m, _c, _i, _Vs...>*), nik_avp(auto_pack<_Hs...>*),
				nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs
			)
			{
				constexpr auto ins = MachineDispatch::instr(c, i);
				constexpr auto ctn = ins[MI::ctn];
				constexpr auto val = NIK_MACHINE(d, _m, _c, _i, _Vs)(_Hs...);

				if constexpr (is_machination<decltype(val)>)

					return NIK_MACHINE(d, MT::propel, c, i, Vs)(val.s1, val.s2, H1, Hs...);

				else if constexpr (ctn == MI::h1)

					return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, U_pack_Vs<val, Xs...>, Hs...);

				else if constexpr (ctn == MI::h1_pair)

					return NIK_MACHINE(d, MT::id, c, i, Vs)
						(U_null_Vs, U_pack_Vs<val.v1, val.v2, Xs...>, Hs...);
				else
					return val;
			}
		};

// internal:

	// call:

		template<key_type... filler>
		struct machine<MN::call, MT::internal, filler...>
		{
			template<NIK_CONTR_PARAMS, auto _m, auto _c, auto _i, auto... Vs, typename... Heaps>
			nik_ces auto result(Heaps...)
			{
				constexpr auto val = NIK_MACHINE(d, _m, _c, _i, Vs)(U_restore_T<Heaps>...);

				if constexpr (is_machination<decltype(val)>)

					return NIK_BEGIN_MACHINE(d, MT::internal, c, i) NIK_END_MACHINE(val.s1, val.s2);
				else
					return val;
			}
		};

	// recall:

		template<key_type... filler>
		struct machine<MN::recall, MT::internal, filler...>
		{
			template<NIK_CONTR_PARAMS, auto _m, auto _c, auto _i, auto... _Vs, auto... _Hs>
			nik_ces auto result(nik_avp(auto_pack<_m, _c, _i, _Vs...>*), nik_avp(auto_pack<_Hs...>*))
			{
				constexpr auto val = NIK_MACHINE(d, _m, _c, _i, _Vs)(_Hs...);

				if constexpr (is_machination<decltype(val)>)

					return NIK_BEGIN_MACHINE(d, MT::internal, c, i) NIK_END_MACHINE(val.s1, val.s2);
				else
					return val;
			}
		};

// halters:

// pause:

	template<key_type... filler>
	struct machine<MN::halt, MT::pause, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps...)
		{
			constexpr auto s1 = U_pack_Vs<m, c, i, Vs...>;
			constexpr auto s2 = U_pack_Vs<U_restore_T<Heaps>...>;

			return machination(s1, s2);
		}
	};

// move:

// junction:

	template<key_type... filler>
	struct machine<MN::move_j_all, MT::id, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, auto... Xs, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), nik_vp(H1)(auto_pack<Xs...>*), Heaps... Hs)
		{
			return NIK_MACHINE(d, MT::id, c, i, Vs)(U_pack_Vs<Ws..., Xs...>, U_null_Vs, Hs...);
		}
	};

// paste:

// register:

	template<key_type... filler>
	struct machine<MN::paste_r_all, MT::id, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, typename... Heaps>
		nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), Heaps... Hs)
		{
			return NIK_MACHINE(d, MT::id, c, i, Ws)(U_null_Vs, Hs...);
		}
	};

// argument:

	template<key_type... filler>
	struct machine<MN::paste_a_all, MT::id, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, auto... Ws, typename Heap1, typename Heap2, typename... Args>
		nik_ces auto result(nik_vp(H0)(auto_pack<Ws...>*), Heap1 H1, Heap2 H2, Args... As)
		{
			return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, H1, H2, Ws...);
		}
	};

// go to:

// id:

	template<key_type... filler>
	struct machine<MN::go_to, MT::id, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, typename... Heaps>
		nik_ces auto result(Heaps... Hs)
		{
			constexpr auto ins	= MachineDispatch::instr(c, i);
			constexpr auto ni	= ins[MI::pos];

			return NIK_MACHINE(d, MT::id, c, ni, Vs)(Hs...);
		}
	};

// conditional:

	template<key_type... filler>
	struct machine<MN::go_to, MT::conditional, filler...>
	{
		template<NIK_CONTR_PARAMS, auto... Vs, typename Heap0, bool X0, auto... Xs, typename... Heaps>
		nik_ces auto result(Heap0 H0, nik_vp(H1)(auto_pack<X0, Xs...>*), Heaps... Hs)
		{
			constexpr auto ins	= MachineDispatch::instr(c, i);
			constexpr auto ni	= X0 ? ins[MI::pos] : i;

			return NIK_MACHINE(d, MT::id, c, ni, Vs)(H0, U_pack_Vs<Xs...>, Hs...);
		}
	};

// memoize:

// lookup:

	template<key_type... filler>
	struct machine<MN::memoize, MT::lookup, filler...>
	{
		template<auto W, auto Z>
		nik_ces bool match = (W == Overload::template result<Overload::car, Z>);

		template
		<
			NIK_CONTR_PARAMS, auto... Vs,
			auto W0, auto... Xs, typename Heap2, auto... Zs, typename... Args
		>
		nik_ces auto result
		(
			nik_vp(H0)(auto_pack<W0>*),
			nik_vp(H1)(auto_pack<Xs...>*), Heap2 H2,
			nik_vp(A0)(auto_pack<Zs...>*), Args... As
		)
		{
			constexpr auto size	= sizeof...(Zs);
			constexpr auto arr	= array<bool, match<W0, Zs>...>;
			constexpr auto pos	= Overload::match(arr, size);

			if constexpr (pos == size)

				return NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, H1, H2, A0, As...);
			else
			{
				constexpr auto ins = MachineDispatch::instr(c, i);
				constexpr auto ni  = ins[MI::pos];

				return NIK_MACHINE(d, MT::id, c, ni, Vs)(A0, U_pack_Vs<pos, Xs...>, H2, A0, As...);
			}
		}
	};

// insert:

	template<key_type... filler>
	struct machine<MN::memoize, MT::insert, filler...>
	{
		template
		<
			NIK_CONTR_PARAMS, auto... Vs,
			auto W0, auto X0, auto... Xs, typename Heap2, auto... Zs, typename... Args
		>
		nik_ces auto result
		(
			nik_vp(H0)(auto_pack<W0>*),
			nik_vp(H1)(auto_pack<X0, Xs...>*), Heap2 H2,
			nik_vp(A0)(auto_pack<Zs...>*), Args... As
		)
		{
		//	constexpr auto h1 = U_pack_Vs<Xs...>;
			constexpr auto Z0 = U_pack_Vs<W0, X0>;
			constexpr auto a0 = U_pack_Vs<Z0, Zs...>;

			return pair(a0, X0);//NIK_MACHINE(d, MT::id, c, i, Vs)(U_null_Vs, h1, H2, a0, As...);
		}
	};

// instructions:

	template<key_type act, key_type ctn = _h1, depth_type dec = _two> // reverse order for user friendliness:
	constexpr instr_type action = instruction<MN::call, MT::action, dec, ctn, act>;

		// comparision:

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto same = action<Overload::same, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto equal = action<Overload::equal, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto not_equal = action<Overload::not_equal, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto less_than = action<Overload::less_than, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto less_than_or_equal = action<Overload::less_than_or_equal, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto greater_than = action<Overload::greater_than, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto greater_than_or_equal = action<Overload::greater_than_or_equal, ctn, dec>;

		//

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto is_zero = action<Overload::is_zero, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto is_value = action<Overload::is_value, ctn, dec>;

		// logical:

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto not_ = action<Overload::not_, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto and_ = action<Overload::and_, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto or_ = action<Overload::or_, ctn, dec>;

		// bitwise:

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto upshift = action<Overload::upshift, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto downshift = action<Overload::downshift, ctn, dec>;

		// arithmetic:

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto add = action<Overload::add, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto subtract = action<Overload::subtract, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto multiply = action<Overload::multiply, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto divide = action<Overload::divide, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto modulo = action<Overload::modulo, ctn, dec>;

		//

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto increment = action<Overload::increment, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto decrement = action<Overload::decrement, ctn, dec>;

		// algebraic:

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto product = action<Overload::product, ctn, dec>;

		// computational:

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto apply = action<Overload::apply, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _three>
		constexpr auto alias = action<Overload::alias, ctn, dec>;

		// functional:

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto length = action<Overload::length, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto map = action<Overload::map, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto zip = action<Overload::zip, ctn, dec>;

		//

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto is_null = action<Overload::is_null, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto cons = action<Overload::cons, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto push = action<Overload::push, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto car = action<Overload::car, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto cdr = action<Overload::cdr, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto unite = action<Overload::unite, ctn, dec>;

		template<key_type ctn = _h1, depth_type dec = _two>
		constexpr auto find = action<Overload::find, ctn, dec>;

	template<index_type pos, key_type loc, key_type ctn = _h0> // reverse order for user friendliness.
	constexpr instr_type copy = instruction<MN::call, MI::copy_note(loc), pos, ctn>;

		template<index_type pos, key_type loc>
		constexpr instr_type write = copy<pos, loc, _h0_write>;

		template<index_type pos, key_type loc>
		constexpr instr_type value = copy<pos, loc, _value>;

	template<index_type pos, key_type loc> // reverse order for user friendliness.
	constexpr instr_type cut = instruction<MN::call, MI::cut_note(loc), pos>;

	template<key_type rtn, key_type ctn = _h1>
	constexpr instr_type variable = instruction<MN::call, MT::variable, rtn, ctn>;

	template<key_type rtn, key_type ctn = _h1>
	constexpr instr_type function = instruction<MN::call, MT::function, rtn, ctn>;

	template<key_type rtn, key_type ctn = _h1>
	constexpr instr_type cascade = instruction<MN::call, MT::cascade, rtn, ctn>;

	template<key_type ctn = _h1, depth_type dec = _two>
	constexpr instr_type compel = instruction<MN::call, MT::compel, dec, ctn>;

	template<key_type...>
	constexpr instr_type internal = instruction<MN::call, MT::internal>;

	template<key_type...>
	constexpr instr_type lift  = instruction<MN::move_j_all, MT::id>;

	template<key_type loc>
	constexpr instr_type paste = instruction<MI::paste_name(loc), MT::id>;

	template<key_type...>
	constexpr instr_type cycle = instruction<MN::go_to, MT::id, _zero>;

	template<key_type pos>
	constexpr instr_type branch = instruction<MN::go_to, MT::conditional, pos>;

	template<key_type pos>
	constexpr instr_type mem_lookup = instruction<MN::memoize, MT::lookup, pos>;

	template<key_type...>
	constexpr instr_type mem_insert = instruction<MN::memoize, MT::insert>;

// start:

	template<auto d, auto prog, auto... Vs, typename CHeap, typename... Args>
	constexpr auto start(CHeap ch, Args... As)
	{
		constexpr auto m	= MT::id;
		constexpr auto c	= controller<internal<>>;
		constexpr auto i	= MachineDispatch::initial_index;

		return NIK_BEGIN_MACHINE(d, m, c, i),

				m, prog, i, Vs...

		NIK_END_MACHINE(U_null_Vs, U_null_Vs, ch, As...);
	}

} // namespace cctmp

// frontend:

namespace cctmp {

} // namespace cctmp

// programs:

namespace cctmp_program
{
	using namespace cctmp;

// variable:

	struct Variable
	{
		nik_ces auto m		= MT::id;
		nik_ces auto i		= MachineDispatch::initial_index;
		nik_ces auto ctn	= MI::value;

		template<auto d, auto n, auto rtn, auto h0, auto c = controller<variable<rtn, ctn>>>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i) NIK_END_MACHINE(h0, U_pack_Vs<n>, U_null_Vs);
	};

// function:

	struct Function
	{
		nik_ces auto m		= MT::id;
		nik_ces auto i		= MachineDispatch::initial_index;
		nik_ces auto ctn	= MI::value;

		template<auto d, auto n, auto rtn, auto h0, auto c = controller<function<rtn, ctn>>>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i) NIK_END_MACHINE(h0, U_pack_Vs<n>, U_null_Vs);
	};

// compel:

	struct Compel
	{
		nik_ces auto m		= MT::id;
		nik_ces auto i		= MachineDispatch::initial_index;
		nik_ces auto ctn	= MI::value;

		template<auto d, auto h0, auto dec = _three, auto c = controller<compel<ctn, dec>>>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i) NIK_END_MACHINE(h0, U_null_Vs, U_null_Vs);
	};
}

// block:

namespace cctmp_program
{

// at:

	struct At_v0
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = Variable::template result<d, n, BN::sifter, p>;
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	constexpr auto at_v0 = At_v0::template result<d, n, p>;

// left:

	struct Left_v0
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = Function::template result<d, n, BN::left, p>;
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	constexpr auto left_v0 = Left_v0::template result<d, n, p>;

// right:

	struct Right_v0
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = Variable::template result<d, n, BN::right, p>;
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	constexpr auto right_v0 = Right_v0::template result<d, n, p>;

// cut:

	struct Cut_v0
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = Function::template result<d, n, BN::filter, p>;
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	constexpr auto cut_v0 = Cut_v0::template result<d, n, p>;

// split:

	struct Split_v0
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = Function::template result<d, n, BN::split, p>;
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	constexpr auto split_v0 = Split_v0::template result<d, n, p>;

// segment:

	struct T_Segment_v0
	{
		template<auto d, auto n>
		nik_ces auto result = NIK_BEGIN_BLOCK(9, segment, d, n) NIK_END_BLOCK;
	};

	constexpr auto U_Segment_v0 = U_store_T<T_Segment_v0>;

	struct Segment_v0
	{
		template<auto d, auto n>
		nik_ces auto result = Compel::template result<d, U_pack_Vs<U_Segment_v0, n>>;
	};

	template<auto n, auto d = MachineDispatch::initial_depth>
	constexpr auto segment_v0 = Segment_v0::template result<d, n>;

// fold:

	struct T_Fold_v0
	{
		template<auto d, auto op, auto V, auto l>
		nik_ces auto result = V;
	};

	template<auto d, auto op, auto V, auto... Vs, nik_vp(l)(auto_pack<Vs...>*)>
	constexpr auto T_Fold_v0::result<d, op, V, l> = NIK_FOLD_BLOCK(d, sizeof...(Vs), op, V, Vs);

	constexpr auto U_Fold_v0 = U_store_T<T_Fold_v0>;

	struct Fold_v0
	{
		template<auto d, auto op, auto V, auto l>
		nik_ces auto result = Compel::template result<d, U_pack_Vs<U_Fold_v0, op, V, l>>;
	};

	template<auto op, auto V, auto l, auto d = MachineDispatch::initial_depth>
	constexpr auto fold_v0 = Fold_v0::template result<d, op, V, l>;

// cascade:

	struct T_Cascade_v0
	{
		template<auto d, auto op, auto V, auto l>
		nik_ces auto result = V;
	};

	template<auto d, auto op, auto V, auto... Vs, nik_vp(l)(auto_pack<Vs...>*)>
	constexpr auto T_Cascade_v0::result<d, op, V, l> = NIK_CASCADE_BLOCK(d, sizeof...(Vs), op, V, Vs);

	constexpr auto U_Cascade_v0 = U_store_T<T_Cascade_v0>;

	struct Cascade_v0
	{
		template<auto d, auto op, auto V, auto l>
		nik_ces auto result = Compel::template result<d, U_pack_Vs<U_Cascade_v0, op, V, l>>;
	};

	template<auto op, auto V, auto l, auto d = MachineDispatch::initial_depth>
	constexpr auto cascade_v0 = Cascade_v0::template result<d, op, V, l>;
}

// mutators:

namespace cctmp_program
{
// version 0:

	// erase:

		struct Erase_v0
		{
			nik_ces auto m = MT::id;
			nik_ces auto i = MachineDispatch::initial_index;
			nik_ces auto c = controller
			<
				function < BN::filter >,
				lift     <            >,
				unite    <     _value >
			>;

			template<auto d, auto n, auto p>
			nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i) NIK_END_MACHINE(p, U_pack_Vs<n>, U_null_Vs);
		};

		template<auto n, auto p, auto d = MachineDispatch::initial_depth>
		constexpr auto erase_v0 = Erase_v0::template result<d, n, p>;

	// insert:

		struct Insert_v0
		{
			nik_ces auto m = MT::id;
			nik_ces auto i = MachineDispatch::initial_index;
			nik_ces auto c = controller
			<
				function <         BN::split >,
				lift     <                   >,
				copy     < _zero , _register >,
				unite    <         _value    >
			>;

			template<auto d, auto v, auto n, auto p>
			nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i), v NIK_END_MACHINE(p, U_pack_Vs<n>, U_null_Vs);
		};

		constexpr auto U_Insert_v0 = U_store_T<Insert_v0>;

		template<auto v, auto n, auto p, auto d = MachineDispatch::initial_depth>
		constexpr auto insert_v0 = Insert_v0::template result<d, v, n, p>;

	// replace:

		struct Replace_v0
		{
			nik_ces auto m = MT::id;
			nik_ces auto i = MachineDispatch::initial_index;
			nik_ces auto c = controller
			<
				function <         BN::filter >,
				lift     <                    >,
				copy     < _zero , _register  >,
				unite    <         _value     >
			>;

			template<auto d, auto v, auto n, auto p>
			nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i), v NIK_END_MACHINE(p, U_pack_Vs<n>, U_null_Vs);
		};

		template<auto v, auto n, auto p, auto d = MachineDispatch::initial_depth>
		constexpr auto replace_v0 = Replace_v0::template result<d, v, n, p>;
}

// insert sort:

namespace cctmp_program
{
// version 0:

	template<auto insert, auto cmp, auto... Vs>
	constexpr auto sort(nik_vp(l)(auto_pack<Vs...>*))
	{
		constexpr auto d		= MachineDispatch::initial_depth;
		constexpr auto list		= U_restore_T<decltype(l)>;
		constexpr auto n		= Overload::template result<Overload::find, cmp, list, insert>;

						// bad design: does not compose well with trampolining.
		constexpr auto sp		= NIK_FUNCTION_BLOCK(9, d, n, BN::split, Vs)(U_null_Vs);

		return Overload::template result<Overload::unite, sp.v1, sp.v2, insert>;
	}

	template<auto cmp = less_than_op<>>
	struct T_InsertSort_v0
	{
		template<auto list, auto insert>
		nik_ces auto result = sort<insert, cmp>(list);
	};

	template<auto cmp = less_than_op<>>
	constexpr auto U_InsertSort_v0 = U_store_T<T_InsertSort_v0<cmp>>;

	template<auto list, auto insert, auto cmp = less_than_op<>>
	constexpr auto insert_sort_v0 = T_InsertSort_v0<cmp>::template result<list, insert>;

// version 1:

	template<auto cmp = less_than_op<>>
	struct T_InsertSort_v1
	{
		nik_ces auto m = MT::id;
		nik_ces auto i = MachineDispatch::initial_index;
		nik_ces auto c = controller
		<
			find     <                   >,
			write    < _zero , _argument >,
			function <         BN::split >,
			lift     <                   >,
			copy     < _zero , _register >,
			unite    <         _value    >
		>;

		template<auto d, auto p, auto v>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i), v
					NIK_END_MACHINE(U_pack_Vs<cmp, p, v>, U_null_Vs, U_null_Vs, p);
	};

	template<auto cmp = less_than_op<>>
	constexpr auto U_InsertSort_v1 = U_store_T<T_InsertSort_v1<cmp>>;

	template<auto list, auto insert, auto cmp = less_than_op<>, auto d = MachineDispatch::initial_depth>
	constexpr auto insert_sort_v1 = T_InsertSort_v1<cmp>::template result<d, list, insert>;
}

// sort:

namespace cctmp_program
{
// version 0:

	// less rigorous (l has a max length), but is fast!

	template
	<
		auto l,
		auto cmp	= less_than_op<>,
		auto d		= MachineDispatch::initial_depth
	>
	constexpr auto sort_v0 = Fold_v0::template result
	<
		d,
		alias_op<U_InsertSort_v0<cmp>>,
		U_null_Vs,
		l
	>;

// version 1:

	// A bit more rigorous, but almost twice as slow as v0.

	template
	<
		auto l,
		auto cmp	= less_than_op<>,
		auto d		= MachineDispatch::initial_depth
	>
	constexpr auto sort_v1 = Fold_v0::template result
	<
		d,
		alias_op<U_InsertSort_v1<cmp>, d>,
		U_null_Vs,
		l
	>;

// version 2:

	template
	<
		auto l,
		auto cmp	= less_than_op<>,
		auto d		= MachineDispatch::initial_depth
	>
	constexpr auto sort_v2 = Cascade_v0::template result
	<
		d,
		U_InsertSort_v1<cmp>,
		U_null_Vs,
		l
	>;
}

// lookup:

namespace cctmp_program
{
// version 0:

	struct T_LookupMatch
	{
		template<auto v, auto p>
		nik_ces auto match()
		{
			constexpr auto pos	= Overload::template result<Overload::find, is_value_op<>, p, v>;
			constexpr auto size	= Overload::template result<Overload::length, p>;

			return pair(bool{pos < size}, pos);
		}

		template<auto v, auto p>
		nik_ces auto result = match<v, p>();
	};

	constexpr auto U_LookupMatch = U_store_T<T_LookupMatch>;

	struct T_Lookup_v0
	{
		template<auto d, auto p, auto v>
		nik_ces auto result = Compel::template result<d, U_pack_Vs<U_LookupMatch, v, p>>;
	};

	constexpr auto U_Lookup_v0 = U_store_T<T_Lookup_v0>;

	template<auto list, auto val, auto d = MachineDispatch::initial_depth>
	constexpr auto lookup_v0 = T_Lookup_v0::template result<d, list, val>;
}

// factorial:

namespace cctmp_program
{
// version 0:

	struct Factorial_v0
	{
		template
		<
			// registers:

			key_type n		=  0,
			key_type p		=  1,

			// labels:

			key_type exit_case	= 13
		>
		nik_ces contr_type program = controller
		<
			copy      < n , _register >,
			is_zero   <               >,
			branch    <     exit_case >,

			copy      < n , _register >,
			copy      < p , _register >,
			multiply  <               >,
			cut       < p , _register >,
			paste     <     _register >,

			copy      < n , _register >,
			decrement <               >,
			cut       < n , _register >,
			paste     <     _register >,

			cycle     <               >,

			// exit_case:

			value     < p , _register >
		>;

		template<auto d, auto n>
		nik_ces auto result = start<d, program<>, n, decltype(n){_one}>(U_null_Vs);
	};

	template<auto n, auto d = MachineDispatch::initial_depth>
	constexpr auto factorial_v0 = Factorial_v0::template result<d, n>;

// version 1:

	struct Factorial_v1
	{
		template
		<
			// registers:

			key_type n			=  0,
			key_type m			=  1,

			// constants:

			key_type one			=  0,
			key_type factorial		=  1,

			// labels:

			key_type exit_case		=  9
		>
		nik_ces contr_type program = controller
		<
			copy     < n         , _register >,
			is_zero  <                       >,
			branch   <             exit_case >,

			copy     < factorial , _constant >,
			copy     < m         , _register >,
			compel   <                       >,

			copy     < n         , _register >,
			lift     <                       >,
			multiply <             _value    >,

			// exit_case:

			value    < one       , _constant >
		>;

		template<auto d, auto n>
		nik_ces auto result = start<d, program<>, n, n-1>
		(
			U_pack_Vs
			<
				decltype(n){_one},
				U_store_T<Factorial_v1>
			>
		);
	};

	template<auto n, auto d = MachineDispatch::initial_depth>
	constexpr auto factorial_v1 = Factorial_v1::template result<d, n>;

// version 2:

	struct Factorial_v2
	{
		nik_ces char source[] =

			" param: n p                        ;"
			" const: is_zero multiply decrement ;"
			"   arg:                            ;"

			" start:                            ;"
			"   if (is_zero n) then stop        ;"
			"   p = multiply n p                ;"
			"   n = decrement n                 ;"
			"   goto start:                     ;"

			" stop:                             ;"
			"   return p                        ;"
		;

		/*
		 * (LOC, param) (VAR, [n, _register, 0]) (VAR, [p, _register, 1]) (;)
		 * (LOC, const) (VAR, [is_zero, _constant, 0]) (VAR, [multiply, _constant, 1]) (VAR, [decrement, _constant, 2]) (;)
		 * (LOC, arg) (;)
		 * (LABEL, start) (;)
		 * (IF) (LP) (VAR, is_zero) (VAR, n) (RP) (INSTR, goto) (LABEL, exit_case) (;)
		 * (VAR, p) (=) (VAR, multiply) (VAR, n) (VAR, p) (;)
		 * (VAR, n) (=) (VAR, decrement) (VAR, n) (;)
		 * (INSTR, goto) (LABEL, start) (;)
		 * (LABEL, exit_case) (;)
		 * (INSTR, return) (VAR, p) (;)
		*/


	//	template<typename T> nik_ces bool is_zero(T n) { return (n == 0); }
	//	template<typename T> nik_ces T multiply(T m, T n) { return m*n; }
	//	template<typename T> nik_ces T decrement(T n) { return n-1; }

	//	template<auto d, auto n>
	//	nik_ces auto result = start<d, program<>, n, decltype(n){_one}>
	//	(
	//		U_pack_Vs
	//		<
	//			is_zero<decltype(n)>,
	//			multiply<decltype(n)>,
	//			decrement<decltype(n)>
	//		>
	//	);
	};

//	template<auto n, auto d = MachineDispatch::initial_depth>
//	constexpr auto factorial_v2 = Factorial_v2::template result<d, n>;
}

// fibonacci:

namespace cctmp_program
{
// version 0:

	struct Fibonacci_v0
	{
		template
		<
			// registers:

			key_type n			=  0,
			key_type n1			=  1,
			key_type n2			=  2,

			// constants:

			key_type one			=  0,
			key_type fibonacci		=  1,
			key_type is_0_or_1		=  2,

			// labels:

			key_type exit_case		= 12
		>
		nik_ces contr_type program = controller
		<
			copy   < is_0_or_1 , _constant >,
			copy   < n         , _register >,
			apply  <                       >,
			branch <             exit_case >,

			copy   < fibonacci , _constant >,
			copy   < n2        , _register >,
			compel <                       >,

			copy   < fibonacci , _constant >,
			copy   < n1        , _register >,
			compel <                       >,

			lift   <                       >,
			add    <             _value    >,

			// exit_case:

			value  < one       , _constant >
		>;

		template<typename T> nik_ces bool is_0_or_1(T n) { return (n == 0) || (n == 1); }

		template<auto d, auto n>
		nik_ces auto result = start<d, program<>, n, n-1, n-2>
		(
			U_pack_Vs
			<
				decltype(n){_one},
				U_store_T<Fibonacci_v0>,
				is_0_or_1<decltype(n)>
			>
		);
	};

	template<auto n, auto d = MachineDispatch::initial_depth>
	constexpr auto fibonacci_v0 = Fibonacci_v0::template result<d, n>;

// version 1:

	struct MemFib_v0
	{
		template
		<
			// registers:

			key_type n			=  0,
			key_type n1			=  1,
			key_type n2			=  2,

			// constants:

			key_type mem_fib		=  0,

			// arguments:

			key_type mem_table		=  0,

			// labels:

			key_type found_case		= 17
		>
		nik_ces contr_type program = controller
		<
			mem_lookup <               found_case >,

			copy       < mem_fib     , _constant  >,
			copy       < n2          , _register  >,
			copy       < mem_table   , _argument  >,
			compel     <               _h1_pair   >,
			cut        < mem_table   , _argument  >,
			paste      <               _argument  >,

			copy       < mem_fib     , _constant  >,
			copy       < n1          , _register  >,
			copy       < mem_table   , _argument  >,
			compel     <               _h1_pair   >,
			cut        < mem_table   , _argument  >,
			paste      <               _argument  >,

			lift       <                          >,
			add        <                          >,

			copy       < n           , _register  >,
			mem_insert <                          >,

			// found_case:

			variable   <               BN::lookup >,
			copy       < mem_table   , _argument  >,
			copy       < _zero       , _junction  >,
			product    <                   _value >
		>;

		nik_ces auto m = MT::id;
		nik_ces auto c = program<>;
		nik_ces auto i = MachineDispatch::initial_index;
		nik_ces auto f = U_store_T<MemFib_v0>;
		nik_ces auto t = U_pack_Vs
		<
			U_pack_Vs<1, 1>,
			U_pack_Vs<0, 1>
		>;

		template<auto d, auto n, auto mem_table = t>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i),

			n, n-1, n-2

		NIK_END_MACHINE
		(
			U_pack_Vs<n>, U_null_Vs,
			U_pack_Vs<f>, mem_table
		);
	};

	template<auto n, auto d = MachineDispatch::initial_depth>
	constexpr auto fibonacci_v1 = MemFib_v0::template result<d, n>.v2;
}

// undef macros:

#undef nik_vp

#undef nik_avp

#undef nik_ces

#undef NIK_EMPTY

#undef NIK_COMMA

#undef NIK_L_PAR

#undef NIK_R_PAR

#undef NIK_L_ANG

#undef NIK_R_ANG

#undef NIK_L_BRAK

#undef NIK_R_BRAK

#undef NIK_AUTO

#undef NIK_TYPENAME

#undef NIK_LDOTS

#undef NIK_R_PAR_LDOTS

#undef NIK_PLUS

#undef NIK_L_STORE

#undef NIK_R_STORE

#undef NIK_UPPER_1_REPS

#undef NIK_UPPER_2_REPS

#undef NIK_UPPER_4_REPS

#undef NIK_UPPER_8_REPS

#undef NIK_UPPER_16_REPS

#undef NIK_UPPER_32_REPS

#undef NIK_UPPER_64_REPS

#undef NIK_UPPER_128_REPS

#undef NIK_UPPER_256_REPS

#undef NIK_UPPER_512_REPS

#undef NIK_2_0_REPS

#undef NIK_2_1_REPS

#undef NIK_2_2_REPS

#undef NIK_2_3_REPS

#undef NIK_2_4_REPS

#undef NIK_2_5_REPS

#undef NIK_2_6_REPS

#undef NIK_2_7_REPS

#undef NIK_2_8_REPS

#undef NIK_2_9_REPS

#undef NIK_UPPER_1_IDS

#undef NIK_UPPER_2_IDS

#undef NIK_UPPER_4_IDS

#undef NIK_UPPER_8_IDS

#undef NIK_UPPER_16_IDS

#undef NIK_UPPER_32_IDS

#undef NIK_UPPER_64_IDS

#undef NIK_UPPER_128_IDS

#undef NIK_UPPER_256_IDS

#undef NIK_UPPER_512_IDS

#undef NIK_2_0_IDS

#undef NIK_2_1_IDS

#undef NIK_2_2_IDS

#undef NIK_2_3_IDS

#undef NIK_2_4_IDS

#undef NIK_2_5_IDS

#undef NIK_2_6_IDS

#undef NIK_2_7_IDS

#undef NIK_2_8_IDS

#undef NIK_2_9_IDS

#undef NIK_2_N_AUTO_VARS

#undef NIK_2_N_VARS

#undef NIK_2_N_TYPENAME_VARS

#undef NIK_2_N_RESTORE_VARS

#undef NIK_2_N_VARIADIC_VARS

#undef NIK_2_N_STORE_VARS

#undef NIK_2_N_PACK_VARS

#undef NIK_2_N_OP_MAP_VARS

#undef NIK_2_N_AL_MAP_VARS

#undef NIK_2_N_INDEX_SEGMENT

#undef NIK_2_N_MONOID_CALLS

#undef NIK_2_N_MONOID_VARS

#undef NIK_2_N_ACTION_FOLDS

#undef NIK_BLOCK_DISPATCH_NEXT_LENGTH

#undef NIK_BLOCK_DISPATCH_NEXT_INDEX

#undef NIK_BEGIN_BLOCK

#undef NIK_END_BLOCK

#undef NIK_VARIABLE_BLOCK

#undef NIK_FUNCTION_BLOCK

#undef NIK_FOLD_BLOCK

#undef NIK_CASCADE_BLOCK

#undef NIK_DEFINE_BLOCK_VARIABLE_PASS

#undef NIK_DEFINE_BLOCK_FUNCTION_PASS

#undef NIK_DEFINE_BLOCK_SEGMENT_PASS

#undef NIK_DEFINE_BLOCK_FOLD_PASS

#undef NIK_CONTR_PARAMS

#undef NIK_BEGIN_MACHINE

#undef NIK_END_MACHINE

#undef NIK_MACHINE

