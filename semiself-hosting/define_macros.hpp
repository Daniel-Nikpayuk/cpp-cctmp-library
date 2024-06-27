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

// define macros:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// preamble:

	#define nik_vp(_n_)												\
															\
		void(*_n_)

	#define nik_avp													\
															\
		nik_vp()

	#define nik_ce													\
															\
		constexpr

	#define nik_ces													\
															\
		constexpr static

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// punctuation():

	#define NIK_EMPTY()

		// blank space.

	#define NIK_COMMA()												\
															\
		,

	#define NIK_AUTO()												\
															\
		auto

	#define NIK_PLUS()												\
															\
		+

	#define NIK_LJ()												\
															\
		j

/***********************************************************************************************************************/

// punctuation_1(_n_):

	#define NIK_ID_1(_n_)												\
															\
		_n_

	#define NIK_V_1(_n_)												\
															\
		V ## _n_

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// variables:

/***********************************************************************************************************************/

// identifiers:

	#define  NIK_0_IDS(_l_, _m_, _r_)										\
							// blank space.
	#define  NIK_1_IDS(_l_, _m_, _r_)										\
							 						_l_() _m_( 0)
	#define  NIK_2_IDS(_l_, _m_, _r_)										\
							 NIK_1_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_( 1)
	#define  NIK_3_IDS(_l_, _m_, _r_)										\
							 NIK_2_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_( 2)
	#define  NIK_4_IDS(_l_, _m_, _r_)										\
							 NIK_3_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_( 3)
	#define  NIK_5_IDS(_l_, _m_, _r_)										\
							 NIK_4_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_( 4)
	#define  NIK_6_IDS(_l_, _m_, _r_)										\
							 NIK_5_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_( 5)
	#define  NIK_7_IDS(_l_, _m_, _r_)										\
							 NIK_6_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_( 6)
	#define  NIK_8_IDS(_l_, _m_, _r_)										\
							 NIK_7_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_( 7)
	#define  NIK_9_IDS(_l_, _m_, _r_)										\
							 NIK_8_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_( 8)
	#define NIK_10_IDS(_l_, _m_, _r_)										\
							 NIK_9_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_( 9)
	#define NIK_11_IDS(_l_, _m_, _r_)										\
							NIK_10_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(10)
	#define NIK_12_IDS(_l_, _m_, _r_)										\
							NIK_11_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(11)
	#define NIK_13_IDS(_l_, _m_, _r_)										\
							NIK_12_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(12)
	#define NIK_14_IDS(_l_, _m_, _r_)										\
							NIK_13_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(13)
	#define NIK_15_IDS(_l_, _m_, _r_)										\
							NIK_14_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(14)
	#define NIK_16_IDS(_l_, _m_, _r_)										\
							NIK_15_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(15)
	#define NIK_17_IDS(_l_, _m_, _r_)										\
							NIK_16_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(16)
	#define NIK_18_IDS(_l_, _m_, _r_)										\
							NIK_17_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(17)
	#define NIK_19_IDS(_l_, _m_, _r_)										\
							NIK_18_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(18)
	#define NIK_20_IDS(_l_, _m_, _r_)										\
							NIK_19_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(19)
	#define NIK_21_IDS(_l_, _m_, _r_)										\
							NIK_20_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(20)
	#define NIK_22_IDS(_l_, _m_, _r_)										\
							NIK_21_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(21)
	#define NIK_23_IDS(_l_, _m_, _r_)										\
							NIK_22_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(22)
	#define NIK_24_IDS(_l_, _m_, _r_)										\
							NIK_23_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(23)
	#define NIK_25_IDS(_l_, _m_, _r_)										\
							NIK_24_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(24)
	#define NIK_26_IDS(_l_, _m_, _r_)										\
							NIK_25_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(25)
	#define NIK_27_IDS(_l_, _m_, _r_)										\
							NIK_26_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(26)
	#define NIK_28_IDS(_l_, _m_, _r_)										\
							NIK_27_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(27)
	#define NIK_29_IDS(_l_, _m_, _r_)										\
							NIK_28_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(28)
	#define NIK_30_IDS(_l_, _m_, _r_)										\
							NIK_29_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(29)
	#define NIK_31_IDS(_l_, _m_, _r_)										\
							NIK_30_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(30)
	#define NIK_32_IDS(_l_, _m_, _r_)										\
							NIK_31_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(31)
	#define NIK_33_IDS(_l_, _m_, _r_)										\
							NIK_32_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(32)
	#define NIK_34_IDS(_l_, _m_, _r_)										\
							NIK_33_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(33)
	#define NIK_35_IDS(_l_, _m_, _r_)										\
							NIK_34_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(34)
	#define NIK_36_IDS(_l_, _m_, _r_)										\
							NIK_35_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(35)
	#define NIK_37_IDS(_l_, _m_, _r_)										\
							NIK_36_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(36)
	#define NIK_38_IDS(_l_, _m_, _r_)										\
							NIK_37_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(37)
	#define NIK_39_IDS(_l_, _m_, _r_)										\
							NIK_38_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(38)
	#define NIK_40_IDS(_l_, _m_, _r_)										\
							NIK_39_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(39)
	#define NIK_41_IDS(_l_, _m_, _r_)										\
							NIK_40_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(40)
	#define NIK_42_IDS(_l_, _m_, _r_)										\
							NIK_41_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(41)
	#define NIK_43_IDS(_l_, _m_, _r_)										\
							NIK_42_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(42)
	#define NIK_44_IDS(_l_, _m_, _r_)										\
							NIK_43_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(43)
	#define NIK_45_IDS(_l_, _m_, _r_)										\
							NIK_44_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(44)
	#define NIK_46_IDS(_l_, _m_, _r_)										\
							NIK_45_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(45)
	#define NIK_47_IDS(_l_, _m_, _r_)										\
							NIK_46_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(46)
	#define NIK_48_IDS(_l_, _m_, _r_)										\
							NIK_47_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(47)
	#define NIK_49_IDS(_l_, _m_, _r_)										\
							NIK_48_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(48)
	#define NIK_50_IDS(_l_, _m_, _r_)										\
							NIK_49_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(49)
	#define NIK_51_IDS(_l_, _m_, _r_)										\
							NIK_50_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(50)
	#define NIK_52_IDS(_l_, _m_, _r_)										\
							NIK_51_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(51)
	#define NIK_53_IDS(_l_, _m_, _r_)										\
							NIK_52_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(52)
	#define NIK_54_IDS(_l_, _m_, _r_)										\
							NIK_53_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(53)
	#define NIK_55_IDS(_l_, _m_, _r_)										\
							NIK_54_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(54)
	#define NIK_56_IDS(_l_, _m_, _r_)										\
							NIK_55_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(55)
	#define NIK_57_IDS(_l_, _m_, _r_)										\
							NIK_56_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(56)
	#define NIK_58_IDS(_l_, _m_, _r_)										\
							NIK_57_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(57)
	#define NIK_59_IDS(_l_, _m_, _r_)										\
							NIK_58_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(58)
	#define NIK_60_IDS(_l_, _m_, _r_)										\
							NIK_59_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(59)
	#define NIK_61_IDS(_l_, _m_, _r_)										\
							NIK_60_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(60)
	#define NIK_62_IDS(_l_, _m_, _r_)										\
							NIK_61_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(61)
	#define NIK_63_IDS(_l_, _m_, _r_)										\
							NIK_62_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(62)
	#define NIK_64_IDS(_l_, _m_, _r_)										\
							NIK_63_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(63)
	#define NIK_65_IDS(_l_, _m_, _r_)										\
							NIK_64_IDS(_l_, _m_, _r_)		_r_()	_l_() _m_(64)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// block variables:

/***********************************************************************************************************************/

// identifiers:

	#define NIK_2_0_IDS(_l_, _m_, _r_)										\
															\
		NIK_1_IDS(_l_, _m_, _r_)

	#define NIK_2_1_IDS(_l_, _m_, _r_)										\
															\
		NIK_2_IDS(_l_, _m_, _r_)

	#define NIK_2_2_IDS(_l_, _m_, _r_)										\
															\
		NIK_4_IDS(_l_, _m_, _r_)

	#define NIK_2_3_IDS(_l_, _m_, _r_)										\
															\
		NIK_8_IDS(_l_, _m_, _r_)

	#define NIK_2_4_IDS(_l_, _m_, _r_)										\
															\
		NIK_16_IDS(_l_, _m_, _r_)

	#define NIK_2_5_IDS(_l_, _m_, _r_)										\
															\
		NIK_32_IDS(_l_, _m_, _r_)

	#define NIK_2_6_IDS(_l_, _m_, _r_)										\
															\
		NIK_64_IDS(_l_, _m_, _r_)

/***********************************************************************************************************************/

// auto:

	#define NIK_2_N_AUTO_VARS(_n_, _v_)										\
															\
		NIK_2_ ## _n_ ## _IDS(NIK_AUTO, _v_, NIK_COMMA)

// values:

	#define NIK_2_N_VARS(_n_, _v_)											\
															\
		NIK_2_ ## _n_ ## _IDS(NIK_EMPTY, _v_, NIK_COMMA)

// segment:

	#define NIK_2_N_SEGMENT_VARS(_n_, _v_)										\
															\
		NIK_2_ ## _n_ ## _IDS(_v_, NIK_PLUS() NIK_ID_1, NIK_COMMA)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// variadic:

/***********************************************************************************************************************/

// controls:

	#define NIK_VARIADIC_CONTROLS(_d_, _c_, _i_, _j_)								\
															\
		auto _d_, auto _c_, auto _i_, auto _j_

// params:

	#define NIK_VARIADIC_PARAMS(_d_, _c_, _i_, _j_, _v_)								\
															\
		NIK_VARIADIC_CONTROLS(_d_, _c_, _i_, _j_), auto... _v_

/***********************************************************************************************************************/

// space:

	#define NIK_VARIADIC_L(_d_, _c_, _i_)										\
															\
		T_variadic												\
		<													\
			VD<_c_>::next_name(_d_, _i_),									\
			VD<_c_>::next_note(_d_, _i_)

	#define NIK_VARIADIC_M(_d_, _c_, _i_, _j_)									\
															\
		>::template result											\
		<													\
			VD<_c_>::next_depth(_d_),									\
			_c_,												\
			VD<_c_>::next_index(_d_, _i_),									\
			_j_

	#define NIK_VARIADIC_R												\
															\
		>

	#define NIK_VARIADIC_BEGIN(_d_, _c_, _i_, _j_)									\
															\
		NIK_VARIADIC_L(_d_, _c_, _i_) NIK_VARIADIC_M(_d_, _c_, _i_, _j_)

	#define NIK_VARIADIC_END											\
															\
		NIK_VARIADIC_R

	#define NIK_VARIADIC_TEMPLATE(_d_, _c_, _i_)									\
															\
		NIK_VARIADIC_L(_d_, _c_, _i_)

	#define NIK_VARIADIC_RESULT(_d_, _c_, _i_, _j_, _v_)								\
															\
		NIK_VARIADIC_M(_d_, _c_, _i_, _j_), _v_... NIK_VARIADIC_R

	#define NIK_VARIADIC(_d_, _c_, _i_, _j_, _v_)									\
															\
		NIK_VARIADIC_TEMPLATE(_d_, _c_, _i_) NIK_VARIADIC_RESULT(_d_, _c_, _i_, _j_, _v_)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

/***********************************************************************************************************************/

// params:

	#define NIK_MACHINE_PARAMS(_c_, _i_, _l_, _t_, _r_)								\
															\
		auto _c_, auto _i_, auto _l_, auto _t_, auto _r_

/***********************************************************************************************************************/

// template:

	#define NIK_MACHINE_TEMPLATE_BEGIN(_c_, _i_)									\
															\
		T_machine												\
		<													\
			AD<_c_>::next_name(_i_),									\
			AD<_c_>::next_note(_i_)

	#define NIK_MACHINE_TEMPLATE_BEGIN_WS(_c_, _i_, ...)								\
															\
		NIK_MACHINE_TEMPLATE_BEGIN(_c_, _i_), __VA_ARGS__

	#define NIK_MACHINE_TEMPLATE_END										\
															\
		>

	#define NIK_MACHINE_TEMPLATE(_c_, _i_)										\
															\
		NIK_MACHINE_TEMPLATE_BEGIN(_c_, _i_)									\
		NIK_MACHINE_TEMPLATE_END

	#define NIK_MACHINE_TEMPLATE_WS(_c_, _i_, ...)									\
															\
		NIK_MACHINE_TEMPLATE_BEGIN_WS(_c_, _i_, __VA_ARGS__)							\
		NIK_MACHINE_TEMPLATE_END

/***********************************************************************************************************************/

// result:

	#define NIK_MACHINE_RESULT_BEGIN(_c_, _i_, _l_, _t_, _r_)							\
															\
		template result												\
		<													\
			_c_,												\
			AD<_c_>::next_index(_i_),									\
			_l_, _t_, _r_

	#define NIK_MACHINE_RESULT_BEGIN_TS(_c_, _i_, _l_, _t_, _r_, ...)						\
															\
		NIK_MACHINE_RESULT_BEGIN(_c_, _i_, _l_, _t_, _r_), __VA_ARGS__

	#define NIK_MACHINE_RESULT_END 											\
															\
		>

	#define NIK_MACHINE_RESULT(_c_, _i_, _l_, _t_, _r_)								\
															\
		NIK_MACHINE_RESULT_BEGIN(_c_, _i_, _l_, _t_, _r_)							\
		NIK_MACHINE_RESULT_END

	#define NIK_MACHINE_RESULT_TS(_c_, _i_, _l_, _t_, _r_, ...)							\
															\
		NIK_MACHINE_RESULT_BEGIN_TS(_c_, _i_, _l_, _t_, _r_, __VA_ARGS__)					\
		NIK_MACHINE_RESULT_END

/***********************************************************************************************************************/

// interface:

	#define NIK_MACHINE_TS(_c_, _i_, _l_, _t_, _r_, ...)								\
															\
		NIK_MACHINE_TEMPLATE(_c_, _i_)										\
			::NIK_MACHINE_RESULT_TS(_c_, _i_, _l_, _t_, _r_, __VA_ARGS__)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

