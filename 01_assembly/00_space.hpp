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

// space:

namespace assembly {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	template<typename T>
	nik_ce auto U_store_T					= cctmp::U_store_T<T>;

	template<auto U>
	using T_store_U						= cctmp::T_store_U<U>;

	template<template<auto...> typename B>
	nik_ce auto U_store_B					= cctmp::U_store_B<B>;

	template<typename T>
	using T_restore_T					= cctmp::T_restore_T<T>;

	template<auto U>
	nik_ce auto & member_value_U				= cctmp::member_value_U<U>;

	using gcbool_type					= cctmp::gcbool_type;
	using gchar_type					= cctmp::gchar_type;
	using gcchar_type					= cctmp::gcchar_type;
	using gkey_type						= cctmp::gkey_type;
	using gcindex_type					= cctmp::gcindex_type;

	nik_ce auto U_unsigned_long				= cctmp::U_unsigned_long;

	template<auto... Vs>
	nik_ce auto eval					= cctmp::eval<Vs...>;

	template<auto... Vs>
	nik_ce auto unpack_					= cctmp::unpack_<Vs...>;

	template<typename T>
	nik_ce auto U_custom_T					= cctmp::U_custom_T<T>;

	template<auto U>
	nik_ce auto _string_to_number_				= cctmp::_string_to_number_<U>;

	template<typename T, auto S>
	using sequence						= cctmp::sequence<T, S>;

	nik_ce auto _par_left_					= cctmp::_par_left_;
	nik_ce auto _par_right_					= cctmp::_par_right_;

	template<auto... Vs>
	nik_ce auto at_						= cctmp::at_<Vs...>;

	template<auto... Vs>
	nik_ce auto segment_					= cctmp::segment_<Vs...>;

	template<auto... Vs>
	using T_machine_action					= cctmp::T_machine_action<Vs...>;

	using MAN						= cctmp::MAN;
	using MAT						= cctmp::MAT;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

	template<gkey_type, gkey_type, auto...> struct T_assembly;

/***********************************************************************************************************************/

// names:

	struct AssemblyName
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			halt    ,
			boolean , number , character , string ,
			literal , list   , lookup    , arg    ,
			pad     , pound  , apply     , bind   , eval ,
			go_to   , branch , invert    ,
			dimension
		};
	};

	using AN = AssemblyName;

/***********************************************************************************************************************/

// notes:

	struct AssemblyNote
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			first , port  , select ,
			front , back  ,
			ante  , conse ,
			push  , pull  , drop   ,
			verse , side  ,
			dimension
		};
	};

	using AT = AssemblyNote;

/***********************************************************************************************************************/

// instructions:

	using AI = cctmp::Instr;

/***********************************************************************************************************************/

// dispatch:

	template<auto static_contr, auto _index = 0>
	using AD = cctmp::MachineDispatch<static_contr, AI, _index>;

/***********************************************************************************************************************/

// compound:

	template<auto...> struct T_assembly_compound;

	// untyped:

		template<auto c, auto i>
		struct T_assembly_compound<c, i>
		{
			template<auto j, auto l, auto t, auto r, typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				return NIK_ASSEMBLY_TEMPLATE(c, i)
					::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, r, Ts...)
						(vs...);
			}
		};

	// typed:

		template<auto s, auto c, auto i>
		struct T_assembly_compound<s, c, i>
		{
			using S = T_store_U<s>;

			template<auto j, auto l, auto t, auto r, typename... Ts>
			nik_ces auto result(Ts... vs) -> S
			{
				return NIK_ASSEMBLY_TEMPLATE(c, i)
					::NIK_ASSEMBLY_RESULT_TS(c, i, j, l, t, r, Ts...)
						(vs...);
			}
		};

	// syntactic sugar:

		template<auto... Vs>
		nik_ce auto U_assembly_compound = U_store_T<T_assembly_compound<Vs...>>;

		nik_ce auto H_assembly_compound = U_store_B<T_assembly_compound>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// read:

	// Reimplement as immutable struct.

/***********************************************************************************************************************/

// only:

	struct T_read_only
	{
		// default:

			template<typename T>
			nik_ces auto _result(nik_avp(T*)) { return U_store_T<T const>; }

		// pointer (recursive):

			template<typename T>
			using T_add_pointer_const = T*const;

			template<auto U>
			nik_ces auto add_pointer_const = U_store_T<T_add_pointer_const<T_store_U<U>>>;

			template<typename T>
			nik_ces auto _result(nik_avp(T**)) { return add_pointer_const<_result(U_store_T<T>)>; }

			template<typename T>
			nik_ces auto _result(nik_avp(T*const*)) { return add_pointer_const<_result(U_store_T<T>)>; }

		// reference (recursive):

			template<typename T>
			using T_add_reference_const = T&;

			template<auto U>
			nik_ces auto add_reference_const = U_store_T<T_add_reference_const<T_store_U<U>>>;

			template<typename T>
			nik_ces auto _result(nik_avp(T&)) { return add_reference_const<_result(U_store_T<T>)>; }

		template<auto U>
		nik_ces auto result = _result(U);

	}; nik_ce auto _read_only_ = U_custom_T<T_read_only>;

	template<auto U>
	using read_only = T_store_U<eval<_read_only_, U>>;

/***********************************************************************************************************************/

// write:

	struct T_read_write
	{
		// default (recursive):

			template<typename T>
			nik_ces auto _result(nik_avp(T*)) { return U_store_T<T>; }

			template<typename T>
			nik_ces auto _result(nik_avp(T const*)) { return U_store_T<T>; }

		// pointer (recursive):

			template<typename T>
			using T_add_pointer = T*;

			template<auto U>
			nik_ces auto add_pointer = U_store_T<T_add_pointer<T_store_U<U>>>;

			template<typename T>
			nik_ces auto _result(nik_avp(T**)) { return add_pointer<_result(U_store_T<T>)>; }

			template<typename T>
			nik_ces auto _result(nik_avp(T*const*)) { return add_pointer<_result(U_store_T<T>)>; }

		// reference:

			template<typename T>
			using T_add_reference = T&;

			template<auto U>
			nik_ces auto add_reference = U_store_T<T_add_reference<T_store_U<U>>>;

			template<typename T>
			nik_ces auto _result(nik_avp(T&)) { return add_reference<_result(U_store_T<T>)>; }

		template<auto U>
		nik_ces auto result = _result(U);

	}; nik_ce auto _read_write_ = U_custom_T<T_read_write>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace assembly

