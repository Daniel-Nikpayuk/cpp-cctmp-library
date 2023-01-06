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

	#define NIK_PERIOD()												\
															\
		.

	#define NIK_L_ANG()												\
															\
		<

	#define NIK_R_ANG()												\
															\
		>

	#define NIK_AUTO()												\
															\
		auto

	#define NIK_VARIADIC_AUTO()											\
															\
		auto...

	#define NIK_TYPENAME()												\
															\
		typename

	#define NIK_PLUS()												\
															\
		+

	#define NIK_V()													\
															\
		V

	#define NIK_EVAL()												\
															\
		eval

	#define NIK_REST()												\
															\
		rest

/***********************************************************************************************************************/

// punctuation_1(_n_):

	#define NIK_EMPTY_1(_n_)

		// blank space.

	#define NIK_ID_1(_n_)												\
															\
		_n_

	#define NIK_T_1(_n_)												\
															\
		T ## _n_

	#define NIK_V_1(_n_)												\
															\
		V ## _n_

	#define NIK_LFS_1(_n_)												\
															\
		fs ## _n_

	#define NIK_BFS_FS_VP_LFS_BFS_FS_1(_n_)										\
															\
		template<auto...> typename BFs ## _n_,									\
		auto... Fs ## _n_, nik_vp(fs ## _n_)(BFs ## _n_<Fs ## _n_...>*)

	#define NIK_EVAL_FS_V_1(_n_)											\
															\
		eval<Fs ## _n_, V ## _n_>...

	#define NIK_EVAL_FS_V_PLUS_ID_1(_n_)										\
															\
		eval<Fs ## _n_, V + _n_>...

	#define NIK_EVAL_OP_V_V_1(_n_)											\
															\
		eval<Op, V ## _n_, V + _n_>

	#define NIK_OP_1(_n_)												\
															\
		Op

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

// auto:

	#define NIK_N_AUTO_VARS(_n_, _v_)										\
															\
		NIK_ ## _n_ ## _IDS(NIK_AUTO, _v_, NIK_COMMA)

// values:

	#define NIK_N_VARS(_n_, _v_)											\
															\
		NIK_ ## _n_ ## _IDS(NIK_EMPTY, _v_, NIK_COMMA)

// constants:

	#define NIK_N_CS(_n_, _v_)											\
															\
		NIK_ ## _n_ ## _IDS(_v_, NIK_EMPTY_1, NIK_COMMA)

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

// variadic auto:

	#define NIK_2_N_VARIADIC_AUTO_VARS(_n_, _v_)									\
															\
		NIK_2_ ## _n_ ## _IDS(NIK_VARIADIC_AUTO, _v_, NIK_COMMA)

// values:

	#define NIK_2_N_VARS(_n_, _v_)											\
															\
		NIK_2_ ## _n_ ## _IDS(NIK_EMPTY, _v_, NIK_COMMA)

// typename:

	#define NIK_2_N_TYPENAME_VARS(_n_, _t_)										\
															\
		NIK_2_ ## _n_ ## _IDS(NIK_TYPENAME, _t_, NIK_COMMA)

// segment:

	#define NIK_2_N_SEGMENT_VARS(_n_, _v_)										\
															\
		NIK_2_ ## _n_ ## _IDS(_v_, NIK_PLUS() NIK_ID_1, NIK_COMMA)

// tuple:

	#define NIK_2_N_TUPLE_VARS(_n_, _t_)										\
															\
		_t_ NIK_PERIOD() NIK_2_ ## _n_ ## _IDS(NIK_REST, NIK_EMPTY_1, NIK_PERIOD)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// action folds:

	#define NIK_2_N_ACTION_FOLDS(_e_, _a_, _f_, _v_)								\
															\
		NIK_2_ ## _e_ ## _IDS(_a_, NIK_L_ANG() _f_ ## _1, NIK_COMMA),						\
		_v_,													\
		NIK_2_ ## _e_ ## _IDS(NIK_EMPTY, NIK_## _v_ ##_1, NIK_R_ANG() NIK_COMMA) NIK_R_ANG()

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// eval:

/***********************************************************************************************************************/

// pad:

	#define NIK_DEFINE_EVAL_PAD(_n_)										\
															\
		template<template<auto...> typename B, nik_vp(b)(T_store_B<B>*), auto V>				\
		nik_ce auto eval<_pad_, b, V, gindex_type{_n_}> = U_store_T<B<NIK_N_CS(_n_, NIK_V)>>;

	#define NIK_DEFINE_EVAL_PADS(_n_)										\
															\
		NIK_ ## _n_ ## _IDS(NIK_EMPTY, NIK_DEFINE_EVAL_PAD, NIK_EMPTY)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// praxis:

/***********************************************************************************************************************/

// controls:

	#define NIK_PRAXIS_CONTROLS(_d_, _c_, _i_, _n_)									\
															\
		auto _d_, auto _c_, auto _i_, auto _n_

// params:

	#define NIK_PRAXIS_PARAMS(_d_, _c_, _i_, _n_, _v_)								\
															\
		NIK_PRAXIS_CONTROLS(_d_, _c_, _i_, _n_), auto... _v_

/***********************************************************************************************************************/

// space:

	#define NIK_PRAXIS_L(_d_, _c_, _i_)										\
															\
		T_praxis												\
		<													\
			PD::next_name(_d_, _c_, _i_),									\
			PD::next_note(_d_, _c_, _i_)

	#define NIK_PRAXIS_M(_d_, _c_, _i_, _n_)									\
															\
		>::template result											\
		<													\
			PD::next_depth(_d_),										\
			_c_,												\
			PD::next_index(_d_, _i_),									\
			_n_

	#define NIK_PRAXIS_R												\
															\
		>

	#define NIK_PRAXIS_BEGIN(_e_, _d_, _c_, _i_, _n_)								\
															\
		NIK_PRAXIS_L(_d_, _c_, _i_), _e_ NIK_PRAXIS_M(_d_, _c_, _i_, _n_)

	#define NIK_PRAXIS_END												\
															\
		NIK_PRAXIS_R

	#define NIK_PRAXIS_TEMPLATE(_d_, _c_, _i_)									\
															\
		NIK_PRAXIS_L(_d_, _c_, _i_)

	#define NIK_PRAXIS_RESULT(_d_, _c_, _i_, _n_, _v_)								\
															\
		NIK_PRAXIS_M(_d_, _c_, _i_, _n_), _v_... NIK_PRAXIS_R

	#define NIK_PRAXIS(_e_, _d_, _c_, _i_, _n_, _v_)								\
															\
		NIK_PRAXIS_TEMPLATE(_d_, _c_, _i_), _e_ NIK_PRAXIS_RESULT(_d_, _c_, _i_, _n_, _v_)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// param:

/***********************************************************************************************************************/

// push id:

	#define NIK_DEFINE_PRAXIS_PUSH_ID_2_N(_e_)									\
															\
		template<auto... filler>										\
		struct T_praxis<PN::push, PT::id, _2_ ## _e_, filler...>						\
		{													\
			template											\
			<												\
				NIK_PRAXIS_CONTROLS(d, c, i, n),							\
				NIK_2_N_AUTO_VARS(_e_, NIK_V_1), auto... Vs,						\
				template<auto...> typename B0, auto... Ws, typename... Heaps				\
			>												\
			nik_ces auto result(nik_vp(H0)(B0<Ws...>*), Heaps... Hs)		 			\
			{												\
				nik_ce auto nH0 = U_store_T<B0<Ws..., NIK_2_N_VARS(_e_, NIK_V_1)>>;			\
															\
				return NIK_PRAXIS_BEGIN(_2_ ## _e_, d, c, i, n),					\
															\
					Vs...										\
															\
				NIK_PRAXIS_END(nH0, Hs...);								\
			}												\
		};

// left id:

	#define NIK_DEFINE_PRAXIS_LEFT_ID_2_N(_e_)									\
															\
		template<NIK_2_N_VARS(_e_, NIK_BFS_FS_VP_LFS_BFS_FS_1)>							\
		struct T_praxis<PN::left, PT::id, _2_ ## _e_, NIK_2_N_VARS(_e_, NIK_LFS_1)>				\
		{													\
			template											\
			<												\
				NIK_PRAXIS_CONTROLS(d, c, i, n),							\
				NIK_2_N_AUTO_VARS(_e_, NIK_V_1), auto... Vs,						\
				template<auto...> typename B0, auto... Ws, typename... Heaps				\
			>												\
			nik_ces auto result(nik_vp(H0)(B0<Ws...>*), Heaps... Hs)		 			\
			{												\
				nik_ce auto nH0 = U_store_T<B0<Ws..., NIK_2_N_VARS(_e_, NIK_EVAL_FS_V_1)>>;		\
															\
				return NIK_PRAXIS_BEGIN(_2_ ## _e_, d, c, i, n),					\
															\
					Vs...										\
															\
				NIK_PRAXIS_END(nH0, Hs...);								\
			}												\
		};

// fold id:

	#define NIK_DEFINE_PRAXIS_FOLD_ID_2_N(_e_)									\
															\
		template<auto... filler>										\
		struct T_praxis<PN::fold, PT::id, _2_ ## _e_, filler...>						\
		{													\
			template											\
			<												\
				NIK_PRAXIS_CONTROLS(d, c, i, n),							\
				auto V, NIK_2_N_AUTO_VARS(_e_, NIK_V_1), auto... Vs,					\
				template<auto...> typename B0, auto W0, auto W1, auto... Ws, typename... Heaps		\
			>												\
			nik_ces auto result(nik_vp(H0)(B0<W0, W1, Ws...>*), Heaps... Hs) 				\
			{												\
				nik_ce auto ins	= PD::instr(c, i);							\
				nik_ce auto Op  = if_then_else_<ins[PI::pos], W1, W0>;					\
															\
				return NIK_PRAXIS_BEGIN(_2_ ## _e_, d, c, i, n),					\
															\
					NIK_2_N_ACTION_FOLDS(_e_, NIK_EVAL, NIK_OP, V), Vs...				\
															\
				NIK_PRAXIS_END(H0, Hs...);								\
			}												\
		};

// segment action:

	#define NIK_DEFINE_PRAXIS_SEGMENT_ACTION_2_N(_e_)								\
															\
		template<auto... filler>										\
		struct T_praxis<PN::segment, PT::action, _2_ ## _e_, filler...>						\
		{													\
			template<NIK_PRAXIS_CONTROLS(d, c, i, n), auto V, auto... Vs, typename... Heaps>		\
			nik_ces auto result(Heaps... Hs)				 				\
			{												\
				return NIK_PRAXIS_BEGIN(_2_ ## _e_, d, c, i, n),					\
															\
					V + _2_ ## _e_, Vs..., NIK_2_N_SEGMENT_VARS(_e_, NIK_V)				\
															\
				NIK_PRAXIS_END(Hs...);									\
			}												\
		};

// segment id:

	#define NIK_DEFINE_PRAXIS_SEGMENT_ID_2_N(_e_)									\
															\
		template<NIK_2_N_VARS(_e_, NIK_BFS_FS_VP_LFS_BFS_FS_1)>							\
		struct T_praxis<PN::segment, PT::id, _2_ ## _e_, NIK_2_N_VARS(_e_, NIK_LFS_1)>				\
		{													\
			template<NIK_PRAXIS_CONTROLS(d, c, i, n), auto V, auto... Vs, typename... Heaps>		\
			nik_ces auto result(Heaps... Hs)				 				\
			{												\
				return NIK_PRAXIS_BEGIN(_2_ ## _e_, d, c, i, n),					\
															\
					V, Vs..., NIK_2_N_VARS(_e_, NIK_EVAL_FS_V_PLUS_ID_1)				\
															\
				NIK_PRAXIS_END(Hs...);									\
			}												\
		};

// sift action:

	#define NIK_DEFINE_PRAXIS_SIFT_ACTION_2_N(_e_)									\
															\
		template<auto... filler>										\
		struct T_praxis<PN::sift, PT::action, _2_ ## _e_, filler...>						\
		{													\
			template											\
			<												\
				NIK_PRAXIS_CONTROLS(d, c, i, n),							\
				auto V, NIK_2_N_AUTO_VARS(_e_, NIK_V_1), auto... Vs,					\
				template<auto...> typename B0, auto W0, auto W1, auto W2, auto... Ws,			\
				typename... Heaps									\
			>												\
			nik_ces auto result(nik_vp(H0)(B0<W0, W1, W2, Ws...>*), Heaps... Hs) 				\
			{												\
				nik_ce auto ins	= PD::instr(c, i);							\
				nik_ce auto Op  = if_then_else_<ins[PI::pos], W2, W1>;					\
															\
				return NIK_PRAXIS_L(d, c, i),								\
															\
					_2_ ## _e_, NIK_2_N_VARS(_e_, NIK_EVAL_OP_V_V_1)				\
															\
				NIK_PRAXIS_M(d, c, i, n),								\
															\
					V + _2_ ## _e_, NIK_2_N_VARS(_e_, NIK_V_1), Vs...				\
															\
				NIK_PRAXIS_R(H0, Hs...);								\
			}												\
		};

// sift id:

	#define NIK_DEFINE_PRAXIS_SIFT_ID_2_N(_e_)									\
															\
		template<NIK_2_N_VARS(_e_, NIK_BFS_FS_VP_LFS_BFS_FS_1)>							\
		struct T_praxis<PN::sift, PT::id, _2_ ## _e_, NIK_2_N_VARS(_e_, NIK_LFS_1)>				\
		{													\
			template											\
			<												\
				NIK_PRAXIS_CONTROLS(d, c, i, n),							\
				auto V, NIK_2_N_AUTO_VARS(_e_, NIK_V_1), auto... Vs,					\
				typename... Heaps									\
			>												\
			nik_ces auto result(Heaps... Hs)								\
			{												\
				return NIK_PRAXIS_BEGIN(_2_ ## _e_, d, c, i, n),					\
															\
					V, Vs..., NIK_2_N_VARS(_e_, NIK_EVAL_FS_V_1)					\
															\
				NIK_PRAXIS_END(Hs...);									\
			}												\
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

/***********************************************************************************************************************/

// controls:

	#define NIK_MACHINE_CONTROLS(_d_, _m_, _c_, _i_)								\
															\
		auto _d_, auto _m_, auto _c_, auto _i_

// params:

	#define NIK_MACHINE_PARAMS(_d_, _m_, _c_, _i_, _v_)								\
															\
		NIK_MACHINE_CONTROLS(_d_, _m_, _c_, _i_), auto... _v_

/***********************************************************************************************************************/

// space:

	#define NIK_MACHINE_L(_d_, _m_, _c_, _i_)									\
															\
		T_machine												\
		<													\
			MD::next_name(_d_, _m_, _c_, _i_),								\
			MD::next_note(_d_, _m_, _c_, _i_)

	#define NIK_MACHINE_M(_d_, _m_, _c_, _i_)									\
															\
		>::template result											\
		<													\
			MD::next_depth(_d_),										\
			_m_, _c_,											\
			MD::next_index(_d_, _m_, _i_)

	#define NIK_MACHINE_R 												\
															\
		>

	#define NIK_MACHINE_BEGIN(_e_, _d_, _m_, _c_, _i_)								\
															\
		NIK_MACHINE_L(_d_, _m_, _c_, _i_), _e_ NIK_MACHINE_M(_d_, _m_, _c_, _i_)

	#define NIK_MACHINE_END												\
															\
		NIK_MACHINE_R

	#define NIK_MACHINE_TEMPLATE(_d_, _m_, _c_, _i_)								\
															\
		NIK_MACHINE_L(_d_, _m_, _c_, _i_)

	#define NIK_MACHINE_RESULT(_d_, _m_, _c_, _i_, _v_)								\
															\
		NIK_MACHINE_M(_d_, _m_, _c_, _i_), _v_... NIK_MACHINE_R

	#define NIK_MACHINE(_e_, _d_, _m_, _c_, _i_, _v_)								\
															\
		NIK_MACHINE_TEMPLATE(_d_, _m_, _c_, _i_), _e_ NIK_MACHINE_RESULT(_d_, _m_, _c_, _i_, _v_)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// chain:

/***********************************************************************************************************************/

// controls:

	#define NIK_CHAIN_CONTROLS(_c_, _i_, _l_)									\
															\
		auto _c_, auto _i_, auto _l_

// params:

	#define NIK_CHAIN_PARAMS(_c_, _i_, _l_, _v_)									\
															\
		NIK_CHAIN_CONTROLS(_c_, _i_, _l_), auto... _v_

/***********************************************************************************************************************/

// space:

	#define NIK_CHAIN_L(_c_, _i_)											\
															\
		T_chain													\
		<													\
			CD::next_name(_c_, _i_)

	#define NIK_CHAIN_M(_c_, _i_, _l_)										\
															\
		>::template result											\
		<													\
			_c_,												\
			CD::next_index(_c_, _i_),									\
			_l_

	#define NIK_CHAIN_R 												\
															\
		>

	#define NIK_CHAIN_BEGIN(_c_, _i_, _l_)										\
															\
		NIK_CHAIN_L(_c_, _i_) NIK_CHAIN_M(_c_, _i_, _l_)

	#define NIK_CHAIN_END												\
															\
		NIK_CHAIN_R

	#define NIK_CHAIN_TEMPLATE(_c_, _i_)										\
															\
		NIK_CHAIN_L(_c_, _i_)

	#define NIK_CHAIN_RESULT(_c_, _i_, _l_, _v_)									\
															\
		NIK_CHAIN_M(_c_, _i_, _l_), _v_... NIK_CHAIN_R

	#define NIK_CHAIN(_c_, _i_, _l_, _v_)										\
															\
		NIK_CHAIN_TEMPLATE(_c_, _i_) NIK_CHAIN_RESULT(_c_, _i_, _l_, _v_)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// assembly:

/***********************************************************************************************************************/

// controls:

	#define NIK_ASSEMBLY_CONTROLS(_s_, _c_, _i_, _l_)								\
															\
		auto _s_, auto _c_, auto _i_, auto _l_

// params:

	#define NIK_ASSEMBLY_PARAMS(_s_, _c_, _i_, _l_, _v_)								\
															\
		NIK_ASSEMBLY_CONTROLS(_s_, _c_, _i_, _l_), auto... _v_

/***********************************************************************************************************************/

// space:

	#define NIK_ASSEMBLY_L(_c_, _i_)										\
															\
		T_assembly												\
		<													\
			AD::next_name(_c_, _i_),									\
			AD::next_note(_c_, _i_)

	#define NIK_ASSEMBLY_M(_s_, _c_, _i_, _l_)									\
															\
		>::template result											\
		<													\
			_s_, _c_,											\
			AD::next_index(_c_, _i_),									\
			_l_

	#define NIK_ASSEMBLY_R 												\
															\
		>

	#define NIK_ASSEMBLY_BEGIN(_s_, _c_, _i_, _l_)									\
															\
		NIK_ASSEMBLY_L(_c_, _i_) NIK_ASSEMBLY_M(_s_, _c_, _i_, _l_)

	#define NIK_ASSEMBLY_END											\
															\
		NIK_ASSEMBLY_R

	#define NIK_ASSEMBLY_TEMPLATE(_c_, _i_)										\
															\
		NIK_ASSEMBLY_L(_c_, _i_)

	#define NIK_ASSEMBLY_RESULT(_s_, _c_, _i_, _l_, _v_)								\
															\
		NIK_ASSEMBLY_M(_s_, _c_, _i_, _l_), _v_... NIK_ASSEMBLY_R

	#define NIK_ASSEMBLY(_s_, _c_, _i_, _l_, _v_)									\
															\
		NIK_ASSEMBLY_TEMPLATE(_c_, _i_) NIK_ASSEMBLY_RESULT(_s_, _c_, _i_, _l_, _v_)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

