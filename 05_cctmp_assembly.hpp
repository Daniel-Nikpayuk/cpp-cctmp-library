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

// assembly:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

	template<gkey_type, auto...> struct T_assembly;

/***********************************************************************************************************************/

// names:

	struct AssemblyName
	{
		enum : gkey_type
		{
			generic , sift    , replace ,
			go_to   , test    , branch  ,
			unary   , binary  , re_turn ,
			apply   ,

			dimension
		};
	};

	using AN = AssemblyName;

/***********************************************************************************************************************/

// instructions:

	struct AssemblyInstr
	{
		enum : gkey_type
		{
			size = 0  , name      , pos ,
			jmp = pos , op  = pos ,
			_0        , _1        , _2  ,

			dimension
		};
	};

	using AI = AssemblyInstr;

/***********************************************************************************************************************/

// dispatch:

	struct AssemblyDispatch
	{
		// defaults:

			nik_ces gindex_type initial_index = _zero;

		// accessors:

			nik_ces auto instr(ccontr_type c, gcindex_type i)
				{ return c[i]; }

		// navigators:

			nik_ces gkey_type next_name(ccontr_type c, gcindex_type i)
				{ return c[i+1][AI::name]; }

			nik_ces gindex_type next_index(ccontr_type, gcindex_type i)
				{ return i + 1; }
	};

	using AD = AssemblyDispatch;

/***********************************************************************************************************************/

// start:

	struct T_assembly_start
	{
		nik_ces auto i = AD::initial_index;

		template<auto s, auto c, auto l, auto... Vs, typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
			{ return NIK_ASSEMBLY(s, c, i, l, Vs)(vs...); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// dependencies:

/***********************************************************************************************************************/

// left:

	struct T_machine_left
	{
		nik_ces auto d  = MD::initial_depth;
		nik_ces auto H0 = U_pack_Vs<_at_, _to_list_>;

		template<auto n, auto h = _zero>
		nik_ces auto contr = controller
		<
			instruction < MN::split  , MT::call  , n >,
			instruction < MN::split  , MT::id        >,
			instruction < MN::params , MT::front     >,
			instruction < MN::halt   , MT::eval  , h >
		>;

		template<auto n, auto... Vs>
		nik_ces auto result = T_machine_start::template result<d, contr<n>, Vs...>(H0);

	}; nik_ce auto _par_left_ = U_custom_T<T_machine_left>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// go to:

/***********************************************************************************************************************/

	template<auto... filler>
	struct T_assembly<AN::go_to, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins = instr(c, i);
			nik_ce auto ni  = ins[AI::jmp];

			return NIK_ASSEMBLY(s, c, ni, l, Vs)(vs...);
		}
	};

	template<auto... filler>
	struct T_assembly<AN::branch, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename BoolType, typename... Ts>
		nik_ces auto result(BoolType v, Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins = instr(c, i);
			nik_ce auto ni  = ins[AI::jmp];

			if (v) return NIK_ASSEMBLY(s, c, ni, l, Vs)(vs...);
			else   return NIK_ASSEMBLY(s, c,  i, l, Vs)(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// argument:

/***********************************************************************************************************************/

// unit (generic):

	template<gkey_type Name, auto... Vs>
	struct T_algorithm<Shape::argument, Name, Vs...>
	{
		template<auto n, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto p = eval<_par_left_<>, n, U_store_T<Ts>...>;

			return T_algorithm_argument<Name, p, Vs...>::result(vs...);
		}

	}; template<auto Name, auto... Vs>
		nik_ce auto _arg_unit_ = U_custom_T<T_algorithm_argument<Name, Vs...>>;

/***********************************************************************************************************************/

// at:

	template<template<auto...> typename B, auto... LUs, nik_vp(p)(B<LUs...>*)>
	struct T_algorithm<Shape::argument, GN::at, p>
	{
		template<typename TN, typename... Ts>
		nik_ces auto result(T_store_U<LUs>... lvs, TN vn, Ts... vs) { return vn; }

	}; nik_ce auto _arg_at_ = _arg_unit_<GN::at>;

	// syntactic sugar:

		template<auto n, typename... Ts>
		nik_ce auto arg_at(Ts... vs) { return T_algorithm_argument<GN::at>::template result<n>(vs...); }

/***********************************************************************************************************************/

// replace:

	template<template<auto...> typename B, auto... LUs, nik_vp(p)(B<LUs...>*), auto c>
	struct T_algorithm<Shape::argument, GN::replace, p, c>
	{
		using C = T_store_U<c>;

		template<typename T, typename TN, typename... Ts>
		nik_ces auto result(T v, T_store_U<LUs>... lvs, TN vn, Ts... vs) { return C::result(lvs..., v, vs...); }

	}; template<auto cont>
		nik_ce auto _arg_replace_ = _arg_unit_<GN::replace, cont>;

	// syntactic sugar:

		template<auto cont, auto n, typename... Ts>
		nik_ce auto arg_replace(Ts... vs)
		{
			return T_algorithm_argument<GN::replace, cont>::template result<n>(vs...);
		}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// test:

/***********************************************************************************************************************/

	template<auto... filler>
	struct T_assembly<AN::test, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins  = instr(c, i);
			nik_ce auto _op  = ins[AI::op];
			nik_ce auto _0   = ins[AI::_0];
			nik_ce auto test = unpack_<l, _par_at_, _op>;

			auto arg = arg_at<_0>(vs...);
			auto val = T_store_U<test>::result(arg);

			return NIK_ASSEMBLY(s, c, i, l, Vs)(val, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// apply:

	// helper:

		template<auto, auto> struct T_assembly_apply;

		template<auto f, auto... Is, nik_vp(p)(T_pack_Vs<Is...>*)>
		struct T_assembly_apply<f, p>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return T_store_U<f>::result(arg_at<Is>(vs...)...); }
		};

/***********************************************************************************************************************/

	template<auto... filler>
	struct T_assembly<AN::apply, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins = instr(c, i);
			nik_ce auto _op = ins[AI::op];
			nik_ce auto _0  = ins[AI::_0];
			nik_ce auto _p  = ins[AI::_1];
			nik_ce auto f   = unpack_<l, _par_at_, _op>;
			nik_ce auto p   = unpack_<l, _par_at_, _p>;

			auto val = T_assembly_apply<f, p>::template result<Ts...>(vs...);

			return NIK_ASSEMBLY_TEMPLATE(c, i),

				_0

			NIK_ASSEMBLY_RESULT(s, c, i, l, Vs)(val, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// resume:

/***********************************************************************************************************************/

/*
	struct T_assembly_cont
	{
		template<auto s, auto l, auto c, auto i, typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			using S = T_store_U<s>;

			return NIK_ASSEMBLY(S, l, c, i)(vs...);
		}
	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// return:

/***********************************************************************************************************************/

	template<auto... filler>
	struct T_assembly<AN::re_turn, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(s, c, i, l, Vs), typename... Ts>
		nik_ces auto result(Ts... vs) -> T_store_U<s>
		{
			nik_ce auto ins	= instr(c, i);
			nik_ce auto n	= ins[AI::pos];

			return arg_at<n>(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

