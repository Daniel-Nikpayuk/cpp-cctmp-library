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
			nik_ce auto p0 = left_    <n, U_store_T<Ts>...>;
			nik_ce auto p1 = right_   <n, U_store_T<Ts>...>;
			nik_ce auto U  = _select_ <p0, p1>;

			return T_store_U<U>::result(vs...);
		}

	}; template<auto n>
		nik_ce auto _at_ = U_arg_overload<ArgOverload::at, n>;

	// syntactic sugar:

		template<auto n, auto... Vs>
		nik_ce auto at_ = T_store_U<_at_<n>>::template result<decltype(Vs)...>(Vs...);

		template<auto n, typename... Ts>
		using type_at = T_store_U<at_<n, U_store_T<Ts>...>>;

		template<auto... Vs, nik_vp(p)(T_pack_Vs<Vs...>*), auto n>
		nik_ce auto at_<p, n> = T_store_U<_at_<n>>::template result<decltype(Vs)...>(Vs...);

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ctuple:

	template<typename, auto, typename...> struct ctuple;

/***********************************************************************************************************************/

// indexed value:

	template<typename T, typename SizeType, SizeType>
	struct indexed_value
	{
		T value;

		nik_ce indexed_value(const T & v) : value{v} { }
	};

/***********************************************************************************************************************/

// interface:

	template<typename SizeType, auto... Is, nik_vp(p)(T_pack_Vs<Is...>*), typename... Ts>
	struct ctuple<SizeType, p, Ts...> : public indexed_value<Ts, SizeType, Is>...
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		nik_ce ctuple(Ts... vs) : indexed_value<Ts, size_type, Is>{vs}... { }

		template<size_type n>
		nik_ce const auto & cvalue() const
		{
			using T		= type_at<n, Ts...>;
			using BasePtr	= indexed_value<T, size_type, n> const*;

			return static_cast<BasePtr>(this)->value;
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
			make , catenate , env_tuple ,
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

	// env tuple:

		template<auto U, auto... filler>
		struct T_grammar<Shape::argument, Pattern::lambda_tuple, ArgLambdaTuple::env_tuple, U, filler...>
		{
			using size_type = T_store_U<U>;

			template<typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				using frame_type = ctuple<size_type, segment_<sizeof...(Ts)>, Ts...      >;
				using env_type   = ctuple<size_type, segment_<1            >, frame_type >;

				return env_type{frame_type{vs...}};
			}

		}; template<auto U>
			nik_ce auto _lambda_env_tuple_ = U_arg_lambda_tuple<ArgLambdaTuple::env_tuple, U>;

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

		template<typename SizeType, typename LT>
		nik_ces auto env_tuple(LT lt) { return lt(_lambda_env_tuple_<U_store_T<SizeType>>); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

