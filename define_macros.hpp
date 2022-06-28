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

	#define NIK_R_ANG()												\
															\
		>

	#define NIK_AUTO()												\
															\
		auto

	#define NIK_TYPENAME()												\
															\
		typename

	#define NIK_PLUS()												\
															\
		+

	#define NIK_V()													\
															\
		V

	#define NIK_OVER()												\
															\
		overload<

	#define NIK_OP()												\
															\
		op

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

	#define NIK_T_V_1(_n_)												\
															\
		T ## _n_ v ## _n_

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// block variables:

/***********************************************************************************************************************/

// upper identifiers:

	#define NIK_UPPER_1_IDS(_l_, _m_, _r_)										\
															\
		_l_() _m_(  0) _r_()

	#define NIK_UPPER_2_IDS(_l_, _m_, _r_)										\
															\
		_l_() _m_(  1) _r_()

	#define NIK_UPPER_4_IDS(_l_, _m_, _r_)										\
															\
		_l_() _m_(  2) _r_(),	_l_() _m_(  3) _r_()

	#define NIK_UPPER_8_IDS(_l_, _m_, _r_)										\
															\
		_l_() _m_(  4) _r_(),	_l_() _m_(  5) _r_(),	_l_() _m_(  6) _r_(),	_l_() _m_(  7) _r_()

	#define NIK_UPPER_16_IDS(_l_, _m_, _r_)										\
															\
		_l_() _m_(  8) _r_(),	_l_() _m_(  9) _r_(),	_l_() _m_( 10) _r_(),	_l_() _m_( 11) _r_(),		\
		_l_() _m_( 12) _r_(),	_l_() _m_( 13) _r_(),	_l_() _m_( 14) _r_(),	_l_() _m_( 15) _r_()

	#define NIK_UPPER_32_IDS(_l_, _m_, _r_)										\
															\
		_l_() _m_( 16) _r_(),	_l_() _m_( 17) _r_(),	_l_() _m_( 18) _r_(),	_l_() _m_( 19) _r_(),		\
		_l_() _m_( 20) _r_(),	_l_() _m_( 21) _r_(),	_l_() _m_( 22) _r_(),	_l_() _m_( 23) _r_(),		\
		_l_() _m_( 24) _r_(),	_l_() _m_( 25) _r_(),	_l_() _m_( 26) _r_(),	_l_() _m_( 27) _r_(),		\
		_l_() _m_( 28) _r_(),	_l_() _m_( 29) _r_(),	_l_() _m_( 30) _r_(),	_l_() _m_( 31) _r_()

	#define NIK_UPPER_64_IDS(_l_, _m_, _r_)										\
															\
		_l_() _m_( 32) _r_(),	_l_() _m_( 33) _r_(),	_l_() _m_( 34) _r_(),	_l_() _m_( 35) _r_(),		\
		_l_() _m_( 36) _r_(),	_l_() _m_( 37) _r_(),	_l_() _m_( 38) _r_(),	_l_() _m_( 39) _r_(),		\
		_l_() _m_( 40) _r_(),	_l_() _m_( 41) _r_(),	_l_() _m_( 42) _r_(),	_l_() _m_( 43) _r_(),		\
		_l_() _m_( 44) _r_(),	_l_() _m_( 45) _r_(),	_l_() _m_( 46) _r_(),	_l_() _m_( 47) _r_(),		\
		_l_() _m_( 48) _r_(),	_l_() _m_( 49) _r_(),	_l_() _m_( 50) _r_(),	_l_() _m_( 51) _r_(),		\
		_l_() _m_( 52) _r_(),	_l_() _m_( 53) _r_(),	_l_() _m_( 54) _r_(),	_l_() _m_( 55) _r_(),		\
		_l_() _m_( 56) _r_(),	_l_() _m_( 57) _r_(),	_l_() _m_( 58) _r_(),	_l_() _m_( 59) _r_(),		\
		_l_() _m_( 60) _r_(),	_l_() _m_( 61) _r_(),	_l_() _m_( 62) _r_(),	_l_() _m_( 63) _r_()

	#define NIK_UPPER_128_IDS(_l_, _m_, _r_)									\
															\
		_l_() _m_( 64) _r_(),	_l_() _m_( 65) _r_(),	_l_() _m_( 66) _r_(),	_l_() _m_( 67) _r_(),		\
		_l_() _m_( 68) _r_(),	_l_() _m_( 69) _r_(),	_l_() _m_( 70) _r_(),	_l_() _m_( 71) _r_(),		\
		_l_() _m_( 72) _r_(),	_l_() _m_( 73) _r_(),	_l_() _m_( 74) _r_(),	_l_() _m_( 75) _r_(),		\
		_l_() _m_( 76) _r_(),	_l_() _m_( 77) _r_(),	_l_() _m_( 78) _r_(),	_l_() _m_( 79) _r_(),		\
		_l_() _m_( 80) _r_(),	_l_() _m_( 81) _r_(),	_l_() _m_( 82) _r_(),	_l_() _m_( 83) _r_(),		\
		_l_() _m_( 84) _r_(),	_l_() _m_( 85) _r_(),	_l_() _m_( 86) _r_(),	_l_() _m_( 87) _r_(),		\
		_l_() _m_( 88) _r_(),	_l_() _m_( 89) _r_(),	_l_() _m_( 90) _r_(),	_l_() _m_( 91) _r_(),		\
		_l_() _m_( 92) _r_(),	_l_() _m_( 93) _r_(),	_l_() _m_( 94) _r_(),	_l_() _m_( 95) _r_(),		\
		_l_() _m_( 96) _r_(),	_l_() _m_( 97) _r_(),	_l_() _m_( 98) _r_(),	_l_() _m_( 99) _r_(),		\
		_l_() _m_(100) _r_(),	_l_() _m_(101) _r_(),	_l_() _m_(102) _r_(),	_l_() _m_(103) _r_(),		\
		_l_() _m_(104) _r_(),	_l_() _m_(105) _r_(),	_l_() _m_(106) _r_(),	_l_() _m_(107) _r_(),		\
		_l_() _m_(108) _r_(),	_l_() _m_(109) _r_(),	_l_() _m_(110) _r_(),	_l_() _m_(111) _r_(),		\
		_l_() _m_(112) _r_(),	_l_() _m_(113) _r_(),	_l_() _m_(114) _r_(),	_l_() _m_(115) _r_(),		\
		_l_() _m_(116) _r_(),	_l_() _m_(117) _r_(),	_l_() _m_(118) _r_(),	_l_() _m_(119) _r_(),		\
		_l_() _m_(120) _r_(),	_l_() _m_(121) _r_(),	_l_() _m_(122) _r_(),	_l_() _m_(123) _r_(),		\
		_l_() _m_(124) _r_(),	_l_() _m_(125) _r_(),	_l_() _m_(126) _r_(),	_l_() _m_(127) _r_()

	#define NIK_UPPER_256_IDS(_l_, _m_, _r_)									\
															\
		_l_() _m_(128) _r_(),	_l_() _m_(129) _r_(),	_l_() _m_(130) _r_(),	_l_() _m_(131) _r_(),		\
		_l_() _m_(132) _r_(),	_l_() _m_(133) _r_(),	_l_() _m_(134) _r_(),	_l_() _m_(135) _r_(),		\
		_l_() _m_(136) _r_(),	_l_() _m_(137) _r_(),	_l_() _m_(138) _r_(),	_l_() _m_(139) _r_(),		\
		_l_() _m_(140) _r_(),	_l_() _m_(141) _r_(),	_l_() _m_(142) _r_(),	_l_() _m_(143) _r_(),		\
		_l_() _m_(144) _r_(),	_l_() _m_(145) _r_(),	_l_() _m_(146) _r_(),	_l_() _m_(147) _r_(),		\
		_l_() _m_(148) _r_(),	_l_() _m_(149) _r_(),	_l_() _m_(150) _r_(),	_l_() _m_(151) _r_(),		\
		_l_() _m_(152) _r_(),	_l_() _m_(153) _r_(),	_l_() _m_(154) _r_(),	_l_() _m_(155) _r_(),		\
		_l_() _m_(156) _r_(),	_l_() _m_(157) _r_(),	_l_() _m_(158) _r_(),	_l_() _m_(159) _r_(),		\
		_l_() _m_(160) _r_(),	_l_() _m_(161) _r_(),	_l_() _m_(162) _r_(),	_l_() _m_(163) _r_(),		\
		_l_() _m_(164) _r_(),	_l_() _m_(165) _r_(),	_l_() _m_(166) _r_(),	_l_() _m_(167) _r_(),		\
		_l_() _m_(168) _r_(),	_l_() _m_(169) _r_(),	_l_() _m_(170) _r_(),	_l_() _m_(171) _r_(),		\
		_l_() _m_(172) _r_(),	_l_() _m_(173) _r_(),	_l_() _m_(174) _r_(),	_l_() _m_(175) _r_(),		\
		_l_() _m_(176) _r_(),	_l_() _m_(177) _r_(),	_l_() _m_(178) _r_(),	_l_() _m_(179) _r_(),		\
		_l_() _m_(180) _r_(),	_l_() _m_(181) _r_(),	_l_() _m_(182) _r_(),	_l_() _m_(183) _r_(),		\
		_l_() _m_(184) _r_(),	_l_() _m_(185) _r_(),	_l_() _m_(186) _r_(),	_l_() _m_(187) _r_(),		\
		_l_() _m_(188) _r_(),	_l_() _m_(189) _r_(),	_l_() _m_(190) _r_(),	_l_() _m_(191) _r_(),		\
		_l_() _m_(192) _r_(),	_l_() _m_(193) _r_(),	_l_() _m_(194) _r_(),	_l_() _m_(195) _r_(),		\
		_l_() _m_(196) _r_(),	_l_() _m_(197) _r_(),	_l_() _m_(198) _r_(),	_l_() _m_(199) _r_(),		\
		_l_() _m_(200) _r_(),	_l_() _m_(201) _r_(),	_l_() _m_(202) _r_(),	_l_() _m_(203) _r_(),		\
		_l_() _m_(204) _r_(),	_l_() _m_(205) _r_(),	_l_() _m_(206) _r_(),	_l_() _m_(207) _r_(),		\
		_l_() _m_(208) _r_(),	_l_() _m_(209) _r_(),	_l_() _m_(210) _r_(),	_l_() _m_(211) _r_(),		\
		_l_() _m_(212) _r_(),	_l_() _m_(213) _r_(),	_l_() _m_(214) _r_(),	_l_() _m_(215) _r_(),		\
		_l_() _m_(216) _r_(),	_l_() _m_(217) _r_(),	_l_() _m_(218) _r_(),	_l_() _m_(219) _r_(),		\
		_l_() _m_(220) _r_(),	_l_() _m_(221) _r_(),	_l_() _m_(222) _r_(),	_l_() _m_(223) _r_(),		\
		_l_() _m_(224) _r_(),	_l_() _m_(225) _r_(),	_l_() _m_(226) _r_(),	_l_() _m_(227) _r_(),		\
		_l_() _m_(228) _r_(),	_l_() _m_(229) _r_(),	_l_() _m_(230) _r_(),	_l_() _m_(231) _r_(),		\
		_l_() _m_(232) _r_(),	_l_() _m_(233) _r_(),	_l_() _m_(234) _r_(),	_l_() _m_(235) _r_(),		\
		_l_() _m_(236) _r_(),	_l_() _m_(237) _r_(),	_l_() _m_(238) _r_(),	_l_() _m_(239) _r_(),		\
		_l_() _m_(240) _r_(),	_l_() _m_(241) _r_(),	_l_() _m_(242) _r_(),	_l_() _m_(243) _r_(),		\
		_l_() _m_(244) _r_(),	_l_() _m_(245) _r_(),	_l_() _m_(246) _r_(),	_l_() _m_(247) _r_(),		\
		_l_() _m_(248) _r_(),	_l_() _m_(249) _r_(),	_l_() _m_(250) _r_(),	_l_() _m_(251) _r_(),		\
		_l_() _m_(252) _r_(),	_l_() _m_(253) _r_(),	_l_() _m_(254) _r_(),	_l_() _m_(255) _r_()

	#define NIK_UPPER_512_IDS(_l_, _m_, _r_)									\
															\
		_l_() _m_(256) _r_(),	_l_() _m_(257) _r_(),	_l_() _m_(258) _r_(),	_l_() _m_(259) _r_(),		\
		_l_() _m_(260) _r_(),	_l_() _m_(261) _r_(),	_l_() _m_(262) _r_(),	_l_() _m_(263) _r_(),		\
		_l_() _m_(264) _r_(),	_l_() _m_(265) _r_(),	_l_() _m_(266) _r_(),	_l_() _m_(267) _r_(),		\
		_l_() _m_(268) _r_(),	_l_() _m_(269) _r_(),	_l_() _m_(270) _r_(),	_l_() _m_(271) _r_(),		\
		_l_() _m_(272) _r_(),	_l_() _m_(273) _r_(),	_l_() _m_(274) _r_(),	_l_() _m_(275) _r_(),		\
		_l_() _m_(276) _r_(),	_l_() _m_(277) _r_(),	_l_() _m_(278) _r_(),	_l_() _m_(279) _r_(),		\
		_l_() _m_(280) _r_(),	_l_() _m_(281) _r_(),	_l_() _m_(282) _r_(),	_l_() _m_(283) _r_(),		\
		_l_() _m_(284) _r_(),	_l_() _m_(285) _r_(),	_l_() _m_(286) _r_(),	_l_() _m_(287) _r_(),		\
		_l_() _m_(288) _r_(),	_l_() _m_(289) _r_(),	_l_() _m_(290) _r_(),	_l_() _m_(291) _r_(),		\
		_l_() _m_(292) _r_(),	_l_() _m_(293) _r_(),	_l_() _m_(294) _r_(),	_l_() _m_(295) _r_(),		\
		_l_() _m_(296) _r_(),	_l_() _m_(297) _r_(),	_l_() _m_(298) _r_(),	_l_() _m_(299) _r_(),		\
		_l_() _m_(300) _r_(),	_l_() _m_(301) _r_(),	_l_() _m_(302) _r_(),	_l_() _m_(303) _r_(),		\
		_l_() _m_(304) _r_(),	_l_() _m_(305) _r_(),	_l_() _m_(306) _r_(),	_l_() _m_(307) _r_(),		\
		_l_() _m_(308) _r_(),	_l_() _m_(309) _r_(),	_l_() _m_(310) _r_(),	_l_() _m_(311) _r_(),		\
		_l_() _m_(312) _r_(),	_l_() _m_(313) _r_(),	_l_() _m_(314) _r_(),	_l_() _m_(315) _r_(),		\
		_l_() _m_(316) _r_(),	_l_() _m_(317) _r_(),	_l_() _m_(318) _r_(),	_l_() _m_(319) _r_(),		\
		_l_() _m_(320) _r_(),	_l_() _m_(321) _r_(),	_l_() _m_(322) _r_(),	_l_() _m_(323) _r_(),		\
		_l_() _m_(324) _r_(),	_l_() _m_(325) _r_(),	_l_() _m_(326) _r_(),	_l_() _m_(327) _r_(),		\
		_l_() _m_(328) _r_(),	_l_() _m_(329) _r_(),	_l_() _m_(330) _r_(),	_l_() _m_(331) _r_(),		\
		_l_() _m_(332) _r_(),	_l_() _m_(333) _r_(),	_l_() _m_(334) _r_(),	_l_() _m_(335) _r_(),		\
		_l_() _m_(336) _r_(),	_l_() _m_(337) _r_(),	_l_() _m_(338) _r_(),	_l_() _m_(339) _r_(),		\
		_l_() _m_(340) _r_(),	_l_() _m_(341) _r_(),	_l_() _m_(342) _r_(),	_l_() _m_(343) _r_(),		\
		_l_() _m_(344) _r_(),	_l_() _m_(345) _r_(),	_l_() _m_(346) _r_(),	_l_() _m_(347) _r_(),		\
		_l_() _m_(348) _r_(),	_l_() _m_(349) _r_(),	_l_() _m_(350) _r_(),	_l_() _m_(351) _r_(),		\
		_l_() _m_(352) _r_(),	_l_() _m_(353) _r_(),	_l_() _m_(354) _r_(),	_l_() _m_(355) _r_(),		\
		_l_() _m_(356) _r_(),	_l_() _m_(357) _r_(),	_l_() _m_(358) _r_(),	_l_() _m_(359) _r_(),		\
		_l_() _m_(360) _r_(),	_l_() _m_(361) _r_(),	_l_() _m_(362) _r_(),	_l_() _m_(363) _r_(),		\
		_l_() _m_(364) _r_(),	_l_() _m_(365) _r_(),	_l_() _m_(366) _r_(),	_l_() _m_(367) _r_(),		\
		_l_() _m_(368) _r_(),	_l_() _m_(369) _r_(),	_l_() _m_(370) _r_(),	_l_() _m_(371) _r_(),		\
		_l_() _m_(372) _r_(),	_l_() _m_(373) _r_(),	_l_() _m_(374) _r_(),	_l_() _m_(375) _r_(),		\
		_l_() _m_(376) _r_(),	_l_() _m_(377) _r_(),	_l_() _m_(378) _r_(),	_l_() _m_(379) _r_(),		\
		_l_() _m_(380) _r_(),	_l_() _m_(381) _r_(),	_l_() _m_(382) _r_(),	_l_() _m_(383) _r_(),		\
		_l_() _m_(384) _r_(),	_l_() _m_(385) _r_(),	_l_() _m_(386) _r_(),	_l_() _m_(387) _r_(),		\
		_l_() _m_(388) _r_(),	_l_() _m_(389) _r_(),	_l_() _m_(390) _r_(),	_l_() _m_(391) _r_(),		\
		_l_() _m_(392) _r_(),	_l_() _m_(393) _r_(),	_l_() _m_(394) _r_(),	_l_() _m_(395) _r_(),		\
		_l_() _m_(396) _r_(),	_l_() _m_(397) _r_(),	_l_() _m_(398) _r_(),	_l_() _m_(399) _r_(),		\
		_l_() _m_(400) _r_(),	_l_() _m_(401) _r_(),	_l_() _m_(402) _r_(),	_l_() _m_(403) _r_(),		\
		_l_() _m_(404) _r_(),	_l_() _m_(405) _r_(),	_l_() _m_(406) _r_(),	_l_() _m_(407) _r_(),		\
		_l_() _m_(408) _r_(),	_l_() _m_(409) _r_(),	_l_() _m_(410) _r_(),	_l_() _m_(411) _r_(),		\
		_l_() _m_(412) _r_(),	_l_() _m_(413) _r_(),	_l_() _m_(414) _r_(),	_l_() _m_(415) _r_(),		\
		_l_() _m_(416) _r_(),	_l_() _m_(417) _r_(),	_l_() _m_(418) _r_(),	_l_() _m_(419) _r_(),		\
		_l_() _m_(420) _r_(),	_l_() _m_(421) _r_(),	_l_() _m_(422) _r_(),	_l_() _m_(423) _r_(),		\
		_l_() _m_(424) _r_(),	_l_() _m_(425) _r_(),	_l_() _m_(426) _r_(),	_l_() _m_(427) _r_(),		\
		_l_() _m_(428) _r_(),	_l_() _m_(429) _r_(),	_l_() _m_(430) _r_(),	_l_() _m_(431) _r_(),		\
		_l_() _m_(432) _r_(),	_l_() _m_(433) _r_(),	_l_() _m_(434) _r_(),	_l_() _m_(435) _r_(),		\
		_l_() _m_(436) _r_(),	_l_() _m_(437) _r_(),	_l_() _m_(438) _r_(),	_l_() _m_(439) _r_(),		\
		_l_() _m_(440) _r_(),	_l_() _m_(441) _r_(),	_l_() _m_(442) _r_(),	_l_() _m_(443) _r_(),		\
		_l_() _m_(444) _r_(),	_l_() _m_(445) _r_(),	_l_() _m_(446) _r_(),	_l_() _m_(447) _r_(),		\
		_l_() _m_(448) _r_(),	_l_() _m_(449) _r_(),	_l_() _m_(450) _r_(),	_l_() _m_(451) _r_(),		\
		_l_() _m_(452) _r_(),	_l_() _m_(453) _r_(),	_l_() _m_(454) _r_(),	_l_() _m_(455) _r_(),		\
		_l_() _m_(456) _r_(),	_l_() _m_(457) _r_(),	_l_() _m_(458) _r_(),	_l_() _m_(459) _r_(),		\
		_l_() _m_(460) _r_(),	_l_() _m_(461) _r_(),	_l_() _m_(462) _r_(),	_l_() _m_(463) _r_(),		\
		_l_() _m_(464) _r_(),	_l_() _m_(465) _r_(),	_l_() _m_(466) _r_(),	_l_() _m_(467) _r_(),		\
		_l_() _m_(468) _r_(),	_l_() _m_(469) _r_(),	_l_() _m_(470) _r_(),	_l_() _m_(471) _r_(),		\
		_l_() _m_(472) _r_(),	_l_() _m_(473) _r_(),	_l_() _m_(474) _r_(),	_l_() _m_(475) _r_(),		\
		_l_() _m_(476) _r_(),	_l_() _m_(477) _r_(),	_l_() _m_(478) _r_(),	_l_() _m_(479) _r_(),		\
		_l_() _m_(480) _r_(),	_l_() _m_(481) _r_(),	_l_() _m_(482) _r_(),	_l_() _m_(483) _r_(),		\
		_l_() _m_(484) _r_(),	_l_() _m_(485) _r_(),	_l_() _m_(486) _r_(),	_l_() _m_(487) _r_(),		\
		_l_() _m_(488) _r_(),	_l_() _m_(489) _r_(),	_l_() _m_(490) _r_(),	_l_() _m_(491) _r_(),		\
		_l_() _m_(492) _r_(),	_l_() _m_(493) _r_(),	_l_() _m_(494) _r_(),	_l_() _m_(495) _r_(),		\
		_l_() _m_(496) _r_(),	_l_() _m_(497) _r_(),	_l_() _m_(498) _r_(),	_l_() _m_(499) _r_(),		\
		_l_() _m_(500) _r_(),	_l_() _m_(501) _r_(),	_l_() _m_(502) _r_(),	_l_() _m_(503) _r_(),		\
		_l_() _m_(504) _r_(),	_l_() _m_(505) _r_(),	_l_() _m_(506) _r_(),	_l_() _m_(507) _r_(),		\
		_l_() _m_(508) _r_(),	_l_() _m_(509) _r_(),	_l_() _m_(510) _r_(),	_l_() _m_(511) _r_()

/***********************************************************************************************************************/

// identifiers:

	#define NIK_2_0_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_)

	#define NIK_2_1_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_), NIK_UPPER_2_IDS(_l_, _m_, _r_)

	#define NIK_2_2_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_), NIK_UPPER_2_IDS(_l_, _m_, _r_),						\
		NIK_UPPER_4_IDS(_l_, _m_, _r_)

	#define NIK_2_3_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_), NIK_UPPER_2_IDS(_l_, _m_, _r_),						\
	       	NIK_UPPER_4_IDS(_l_, _m_, _r_), NIK_UPPER_8_IDS(_l_, _m_, _r_)

	#define NIK_2_4_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_), NIK_UPPER_2_IDS(_l_, _m_, _r_),						\
	       	NIK_UPPER_4_IDS(_l_, _m_, _r_), NIK_UPPER_8_IDS(_l_, _m_, _r_),						\
		NIK_UPPER_16_IDS(_l_, _m_, _r_)

	#define NIK_2_5_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_), NIK_UPPER_2_IDS(_l_, _m_, _r_),						\
	       	NIK_UPPER_4_IDS(_l_, _m_, _r_), NIK_UPPER_8_IDS(_l_, _m_, _r_),						\
	       	NIK_UPPER_16_IDS(_l_, _m_, _r_), NIK_UPPER_32_IDS(_l_, _m_, _r_)

	#define NIK_2_6_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_), NIK_UPPER_2_IDS(_l_, _m_, _r_),						\
	       	NIK_UPPER_4_IDS(_l_, _m_, _r_), NIK_UPPER_8_IDS(_l_, _m_, _r_),						\
	       	NIK_UPPER_16_IDS(_l_, _m_, _r_), NIK_UPPER_32_IDS(_l_, _m_, _r_),					\
		NIK_UPPER_64_IDS(_l_, _m_, _r_)

	#define NIK_2_7_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_), NIK_UPPER_2_IDS(_l_, _m_, _r_),						\
	       	NIK_UPPER_4_IDS(_l_, _m_, _r_), NIK_UPPER_8_IDS(_l_, _m_, _r_),						\
	       	NIK_UPPER_16_IDS(_l_, _m_, _r_), NIK_UPPER_32_IDS(_l_, _m_, _r_),					\
		NIK_UPPER_64_IDS(_l_, _m_, _r_), NIK_UPPER_128_IDS(_l_, _m_, _r_)

	#define NIK_2_8_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_), NIK_UPPER_2_IDS(_l_, _m_, _r_),						\
	       	NIK_UPPER_4_IDS(_l_, _m_, _r_), NIK_UPPER_8_IDS(_l_, _m_, _r_),						\
	       	NIK_UPPER_16_IDS(_l_, _m_, _r_), NIK_UPPER_32_IDS(_l_, _m_, _r_),					\
		NIK_UPPER_64_IDS(_l_, _m_, _r_), NIK_UPPER_128_IDS(_l_, _m_, _r_),					\
	       	NIK_UPPER_256_IDS(_l_, _m_, _r_)

	#define NIK_2_9_IDS(_l_, _m_, _r_)										\
															\
		NIK_UPPER_1_IDS(_l_, _m_, _r_), NIK_UPPER_2_IDS(_l_, _m_, _r_),						\
	       	NIK_UPPER_4_IDS(_l_, _m_, _r_), NIK_UPPER_8_IDS(_l_, _m_, _r_),						\
	       	NIK_UPPER_16_IDS(_l_, _m_, _r_), NIK_UPPER_32_IDS(_l_, _m_, _r_),					\
		NIK_UPPER_64_IDS(_l_, _m_, _r_), NIK_UPPER_128_IDS(_l_, _m_, _r_),					\
	       	NIK_UPPER_256_IDS(_l_, _m_, _r_), NIK_UPPER_512_IDS(_l_, _m_, _r_)

/***********************************************************************************************************************/

// auto:

	#define NIK_2_N_AUTO_VARS(_n_, _v_)										\
															\
		NIK_2_ ## _n_ ## _IDS(NIK_AUTO, _v_, NIK_EMPTY)

// values:

	#define NIK_2_N_VARS(_n_, _v_)											\
															\
		NIK_2_ ## _n_ ## _IDS(NIK_EMPTY, _v_, NIK_EMPTY)

// typename:

	#define NIK_2_N_TYPENAME_VARS(_n_, _t_)										\
															\
		NIK_2_ ## _n_ ## _IDS(NIK_TYPENAME, _t_, NIK_EMPTY)

// argument:

	#define NIK_2_N_ARG_VARS(_n_, _a_)										\
															\
		NIK_2_ ## _n_ ## _IDS(NIK_EMPTY, _a_, NIK_EMPTY)

// index segment:

	#define NIK_2_N_INDEX_SEGMENT(_n_, _s_)										\
															\
		NIK_2_ ## _n_ ## _IDS(_s_ NIK_PLUS, NIK_ID_1, NIK_EMPTY)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// monoid calls:

	#define NIK_2_N_MONOID_CALLS(_n_, _l_, _m_)									\
															\
		NIK_2_ ## _n_ ## _IDS(_l_, NIK_EMPTY_1, _m_)

// monoid values:

	#define NIK_2_N_MONOID_VARS(_n_, _v_, _r_)									\
															\
		NIK_2_ ## _n_ ## _IDS(NIK_EMPTY, _v_, _r_)

// action folds:

	#define NIK_2_N_ACTION_FOLDS(_n_, _l_, _m_, _s_, _v_, _r_)							\
															\
		NIK_2_N_MONOID_CALLS(_n_, _l_, _m_), _s_, NIK_2_N_MONOID_VARS(_n_, _v_, _r_)

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// block:

/***********************************************************************************************************************/

// next length:

	#define NIK_BLOCK_DISPATCH_NEXT_LENGTH(_n_)									\
															\
		nik_ces key_type next_length_ ## _n_(cdepth_type d, cindex_type n)					\
		{													\
			if (d == 0) return _zero;									\
			else        return max_length_ ## _n_(n);							\
		}

/***********************************************************************************************************************/

// next index:

	#define NIK_BLOCK_DISPATCH_NEXT_INDEX(_n_)									\
															\
		nik_ces index_type next_index_ ## _n_(cdepth_type d, cindex_type n)					\
		{													\
			if (d == 0) return n;										\
			else        return n - max_index_ ## _n_(n);							\
		}

/***********************************************************************************************************************/

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
		NIK_BEGIN_BLOCK(9, fold, _d_, _n_), _o_, _s_, _v_... NIK_END_BLOCK

	#define NIK_CASCADE_BLOCK(_d_, _n_, _o_, _s_, _v_)								\
															\
		NIK_BEGIN_BLOCK(0, cascade, _d_, _n_), _o_, _s_, _v_... NIK_END_BLOCK()

	#define NIK_ARGUMENT_BLOCK(_p_, _d_, _n_, _t_)									\
															\
		NIK_BEGIN_BLOCK(_p_, argument, _d_, _n_), _t_... NIK_END_BLOCK

/***********************************************************************************************************************/

// pass:

	#define NIK_DEFINE_BLOCK_VARIABLE_PASS(_p_)									\
															\
		template<key_type... filler>										\
		struct block<BN::variable, BT::pass, _p_, filler...>							\
		{													\
			template<auto d, auto n, auto rtn, NIK_2_N_AUTO_VARS(_p_, NIK_V_1), auto... Vs>			\
			nik_ces auto result = NIK_VARIABLE_BLOCK(_p_, d, n, rtn, Vs);					\
		};

	#define NIK_DEFINE_BLOCK_FUNCTION_PASS(_p_)									\
															\
		template<key_type... filler>										\
		struct block<BN::function, BT::pass, _p_, filler...>							\
		{													\
			template<auto d, auto n, auto rtn, NIK_2_N_AUTO_VARS(_p_, NIK_V_1), auto... Vs, auto... Ws>	\
			nik_ces auto result(nik_avp(auto_pack<Ws...>*))				 			\
			{												\
				return NIK_FUNCTION_BLOCK(_p_, d, n, rtn, Vs)						\
						(U_pack_Vs<Ws..., NIK_2_N_VARS(_p_, NIK_V_1)>);				\
			}												\
		};

	#define NIK_DEFINE_BLOCK_SEGMENT_PASS(_p_)									\
															\
		template<key_type... filler>										\
		struct block<BN::segment, BT::pass, _p_, filler...>							\
		{													\
			template<auto d, auto n, auto m, auto... Vs>							\
			nik_ces auto result = NIK_BEGIN_BLOCK(_p_, segment, d, n),					\
															\
				m, Vs..., NIK_2_N_INDEX_SEGMENT(_p_, decltype(m){sizeof...(Vs)})			\
															\
			NIK_END_BLOCK;											\
		};

	#define NIK_DEFINE_BLOCK_FOLD_PASS(_p_)										\
															\
		template<key_type... filler>										\
		struct block<BN::fold, BT::pass, _p_, filler...>							\
		{													\
			template<auto d, auto n, auto op, auto V, NIK_2_N_AUTO_VARS(_p_, NIK_V_1), auto... Vs>		\
			nik_ces auto result = NIK_BEGIN_BLOCK(_p_, fold, d, n),	op,					\
															\
				NIK_2_N_ACTION_FOLDS(_p_, NIK_OVER, NIK_OP, V, NIK_V_1, NIK_R_ANG), Vs...		\
															\
			NIK_END_BLOCK;											\
		};

	#define NIK_DEFINE_BLOCK_ARGUMENT_PASS(_p_)									\
															\
		template<key_type... filler>										\
		struct block<BN::argument, BT::pass, _p_, filler...>							\
		{													\
			template<auto d, auto n, NIK_2_N_TYPENAME_VARS(_p_, NIK_T_1), typename... Ts>			\
			nik_ces auto result(NIK_2_N_ARG_VARS(_p_, NIK_T_V_1), Ts... vs)					\
			{												\
				return NIK_ARGUMENT_BLOCK(_p_, d, n, Ts)(vs...);					\
			}												\
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

/***********************************************************************************************************************/

	#define NIK_CONTR_PARAMS											\
															\
		auto d, auto m, auto c, auto i										\

/***********************************************************************************************************************/

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

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// labels:

/***********************************************************************************************************************/

#define NIK_LABELS_0_TO_0												\
															\
	l0<S, T, Ts...>

#define NIK_LABELS_0_TO_1												\
															\
	NIK_LABELS_0_TO_0, l1<S, T, Ts...>

#define NIK_LABELS_0_TO_2												\
															\
	NIK_LABELS_0_TO_1, l2<S, T, Ts...>

#define NIK_LABELS_0_TO_3												\
															\
	NIK_LABELS_0_TO_2, l3<S, T, Ts...>

#define NIK_LABELS_0_TO_4												\
															\
	NIK_LABELS_0_TO_3, l4<S, T, Ts...>

#define NIK_LABELS_0_TO_5												\
															\
	NIK_LABELS_0_TO_4, l5<S, T, Ts...>

#define NIK_LABELS_0_TO_6												\
															\
	NIK_LABELS_0_TO_5, l6<S, T, Ts...>

#define NIK_LABELS_0_TO_7												\
															\
	NIK_LABELS_0_TO_6, l7<S, T, Ts...>

/***********************************************************************************************************************/

#define NIK_LABELS_0_TO_N(_n_)												\
															\
	NIK_LABELS_0_TO_ ## _n_

#define NIK_DEFINE_LABEL(_m_, _n_)											\
															\
	template<auto S, typename T, typename... Ts>									\
	nik_ces T l ## _m_(Ts... vs)											\
	{														\
		return link												\
		<													\
			S,												\
			l ## _m_<S, T, Ts...>,										\
			NIK_LABELS_0_TO_N(_n_)										\
															\
		>(vs...);												\
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

#define NIK_DEFINE_LABELS_0_TO_0(_n_)											\
															\
	NIK_DEFINE_LABEL(0, _n_)

#define NIK_DEFINE_LABELS_0_TO_1(_n_)											\
															\
	NIK_DEFINE_LABELS_0_TO_0(_n_) NIK_DEFINE_LABEL(1, _n_)

#define NIK_DEFINE_LABELS_0_TO_2(_n_)											\
															\
	NIK_DEFINE_LABELS_0_TO_1(_n_) NIK_DEFINE_LABEL(2, _n_)

#define NIK_DEFINE_LABELS_0_TO_3(_n_)											\
															\
	NIK_DEFINE_LABELS_0_TO_2(_n_) NIK_DEFINE_LABEL(3, _n_)

#define NIK_DEFINE_LABELS_0_TO_4(_n_)											\
															\
	NIK_DEFINE_LABELS_0_TO_3(_n_) NIK_DEFINE_LABEL(4, _n_)

#define NIK_DEFINE_LABELS_0_TO_5(_n_)											\
															\
	NIK_DEFINE_LABELS_0_TO_4(_n_) NIK_DEFINE_LABEL(5, _n_)

#define NIK_DEFINE_LABELS_0_TO_6(_n_)											\
															\
	NIK_DEFINE_LABELS_0_TO_5(_n_) NIK_DEFINE_LABEL(6, _n_)

#define NIK_DEFINE_LABELS_0_TO_7(_n_)											\
															\
	NIK_DEFINE_LABELS_0_TO_6(_n_) NIK_DEFINE_LABEL(7, _n_)

/***********************************************************************************************************************/

#define NIK_DEFINE_LABELS_0_TO_N(_n_)											\
															\
	NIK_DEFINE_LABELS_0_TO_ ## _n_(_n_)

#define NIK_DEFINE_LABEL_STRUCT(_p_, _n_)										\
															\
	template<index_type... filler>											\
	struct Label<_n_, filler...>											\
	{														\
		NIK_DEFINE_LABELS_0_TO_N(_p_)										\
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

