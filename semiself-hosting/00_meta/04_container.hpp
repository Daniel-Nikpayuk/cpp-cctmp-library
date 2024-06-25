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

// container:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// operators:

/***********************************************************************************************************************/

// at:

	template<auto n, auto... filler>
	struct T_grammar<Shape::argument, Pattern::overload, ArgOverload::at, n, filler...>
	{
		template<typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto p0 = left_  <n, U_store_T<Ts>...>;
			nik_ce auto p1 = right_ <n, U_store_T<Ts>...>;
			nik_ce auto U  = _at_   <p0, p1>;

			return T_store_U<U>::result(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lambda tuple:

/***********************************************************************************************************************/

// operators:

	struct ArgLambdaTuple
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			make , catenate ,
			dimension
		};
	};

/***********************************************************************************************************************/

// lambda tuple:

	// make:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::lambda_tuple, ArgLambdaTuple::make, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				return [vs...](auto U, auto... xs)
				{
					using F = T_restore_T<decltype(U)>;

					return F::template result<decltype(xs)..., Ts...>(xs..., vs...);
				};
			}

		}; nik_ce auto _lambda_tuple_ = U_arg_lambda_tuple<ArgLambdaTuple::make>;

	// catenate:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::lambda_tuple, ArgLambdaTuple::catenate, filler...>
		{
			template<typename LT, typename... Ts>
			nik_ces auto result(LT lt, Ts... vs) { return lt(_lambda_tuple_, vs...); }

		}; nik_ce auto _lambda_tuple_catenate_ = U_arg_lambda_tuple<ArgLambdaTuple::catenate>;

/***********************************************************************************************************************/

// message passing:

	struct LambdaTuple
	{
		template<        typename LT> nik_ces auto empty (LT lt) { return lt(_empty_); }
		template<        typename LT> nik_ces auto size  (LT lt) { return lt(_size_ ); }
		template<auto n, typename LT> nik_ces auto value (LT lt) { return lt(_at_<n>); }

		template<typename... Ts>
		nik_ces auto make(Ts... vs) { return T_store_U<_lambda_tuple_>::template result<Ts...>(vs...); }

		template<typename LT1, typename LT2>
		nik_ces auto catenate(LT1 lt1, LT2 lt2) { return lt1(_lambda_tuple_catenate_, lt2); }
	};

/***********************************************************************************************************************/

// binding:

	template<typename SizeType, typename CharType, SizeType N, typename T>
	nik_ce auto binding(nik_avp(SizeType*), CharType (&variable)[N], T value)
	{
		using strlit_type = string_literal<CharType, SizeType>;

		return LambdaTuple::make(strlit_type{variable}, value);
	}

	// syntactic sugar:

		template<typename CharType, gindex_type N, typename T>
		nik_ce auto gbinding(CharType (&variable)[N], T value)
			{ return binding(U_gindex_type, variable, value); }

/***********************************************************************************************************************/

// frame:

	template<typename CharType, typename SizeType, typename... Bindings>
	nik_ce auto frame(nik_avp(CharType*), nik_avp(SizeType*), Bindings... bs)
	{
		using strlit_type   = string_literal<CharType, SizeType>;
		using variable_type = sequence<strlit_type, SizeType, sizeof...(Bindings)>;

		variable_type variables;
		(variables.push(LambdaTuple::value<0>(bs)), ...);

		auto values = LambdaTuple::make(LambdaTuple::value<1>(bs)...);

		return LambdaTuple::make(variables, values);
	}

/***********************************************************************************************************************/

// source:

	template<typename SizeType, typename CharType, SizeType N, typename... Bindings>
	nik_ce auto source(const CharType (&s)[N], const Bindings &... bs)
	{
		using strlit_type       = string_literal<CharType, SizeType>;
		nik_ce auto U_char_type = U_store_T<CharType>;
		nik_ce auto U_size_type = U_store_T<SizeType>;

		return LambdaTuple::make(strlit_type{s}, frame(U_char_type, U_size_type, bs...));
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

