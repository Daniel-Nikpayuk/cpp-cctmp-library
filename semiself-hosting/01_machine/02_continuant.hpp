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

// continuant:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// operators:

/***********************************************************************************************************************/

// select:

	template<auto, auto> struct T_select;

	template
	<
		         auto... LUs, nik_vp(p0)(T_pack_Vs<    LUs...>*),
		auto RU, auto... RUs, nik_vp(p1)(T_pack_Vs<RU, RUs...>*)
	>
	struct T_select<p0, p1>
	{
		nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<RU> rv, T_store_U<RUs>... rvs)
			{ return rv; }

	}; template<auto p0, auto p1>
		nik_ce auto _select_ = U_store_T<T_select<p0, p1>>;

/***********************************************************************************************************************/

// at:

	template<auto n>
	struct T_at
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
		nik_ce auto _at_ = U_store_T<T_at<n>>;

	// syntactic sugar:

		template<auto n, auto... Vs>
		nik_ce auto at_ = T_store_U<_at_<n>>::template result<decltype(Vs)...>(Vs...);

		template<auto n, typename... Ts>
		using type_at = T_store_U<at_<n, U_store_T<Ts>...>>;

		template<auto... Vs, nik_vp(p)(T_pack_Vs<Vs...>*), auto n>
		nik_ce auto at_<p, n> = T_store_U<_at_<n>>::template result<decltype(Vs)...>(Vs...);

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// read:

/***********************************************************************************************************************/

// only:

	template<auto...>
	struct T_read
	{
		// default:

			template<typename T>
			nik_ces auto only(nik_avp(T*)) { return U_store_T<T const>; }

		// pointer (recursive):

			template<typename T>
			using T_add_pointer_const = T*const;

			template<auto U>
			nik_ces auto add_pointer_const = U_store_T<T_add_pointer_const<T_store_U<U>>>;

			template<typename T>
			nik_ces auto only(nik_avp(T**))
				{ return add_pointer_const<only(U_store_T<T>)>; }

			template<typename T>
			nik_ces auto only(nik_avp(T*const*))
				{ return add_pointer_const<only(U_store_T<T>)>; }

		// reference (recursive):

			template<typename T>
			using T_add_reference_const = T&;

			template<auto U>
			nik_ces auto add_reference_const = U_store_T<T_add_reference_const<T_store_U<U>>>;

			template<typename T>
			nik_ces auto only(nik_avp(T&))
				{ return add_reference_const<only(U_store_T<T>)>; }
	};

	// syntactic sugar:

		template<bool V, typename T>
		using read_type = typename T_read<V, U_store_T<T>>::mtype;

/***********************************************************************************************************************/

// immutable:

	template<auto U, auto... filler>
	struct T_read<false, U, filler...>
	{
		protected:

			nik_ces auto U_mtype	= T_read<filler...>::only(U);

		public:

			using mtype		= T_store_U<U_mtype>;
	};

/***********************************************************************************************************************/

// mutable:

	template<auto U, auto... filler>
	struct T_read<true, U, filler...>
	{
		public:

			using mtype		= T_store_U<U>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// continuant:

	template<genum_type, auto...> struct T_continuant;

/***********************************************************************************************************************/

// dispatch:

	template<auto static_concord>
	struct ContinuantDispatch
	{
		using size_type			= typename T_store_U<static_concord>::size_type;
		using size_ctype		= typename T_store_U<static_concord>::size_ctype;

		nik_ces size_type carry_size	= 1;
		nik_ces auto & concord		= member_value_U<static_concord>;
		nik_ces auto & function		= T_store_U<static_concord>::function;
		nik_ces auto contr		= concord.function_cmethod().get_contr(function);

		// accessors:

			nik_ces size_type value (size_ctype i, size_ctype n) { return contr.cat(i, n); }
			nik_ces size_type arg   (size_ctype i, size_ctype n) { return value(i, n) + carry_size; }
			nik_ces size_type peek  (size_ctype i, size_ctype m, size_ctype n) { return value(i + m, n); }

		// navigators:

			nik_ces size_type next_offset  (size_ctype i) { return value(i, CProg::next); }
			nik_ces size_type next_counter (size_ctype i) { return i + next_offset(i); }

			nik_ces genum_type next_action (size_ctype i)
			{
				if (next_offset(i)) { return value(next_counter(i), CProg::action); }
				else                { return CI::halt; }
			}
	};

	template<auto static_contr>
	using CD = ContinuantDispatch<static_contr>;

/***********************************************************************************************************************/

// compound:

	template<auto...> struct T_continuant_compound;

	// untyped:

		template<auto c, auto i>
		struct T_continuant_compound<c, i>
		{
			template<auto l, auto t, auto r, typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				return NIK_MACHINE_TEMPLATE(c, i)
					::NIK_MACHINE_RESULT_TS(c, i, l, t, r, Ts...)
						(vs...);
			}
		};

	// typed:

		template<auto s, auto c, auto i>
		struct T_continuant_compound<s, c, i>
		{
			using S = T_store_U<s>;

			template<auto l, auto t, auto r, typename... Ts>
			nik_ces auto result(Ts... vs) -> S
			{
				return NIK_MACHINE_TEMPLATE(c, i)
					::NIK_MACHINE_RESULT_TS(c, i, l, t, r, Ts...)
						(vs...);
			}
		};

	// syntactic sugar:

		template<auto... Vs>
		nik_ce auto U_continuant_compound = U_store_T<T_continuant_compound<Vs...>>;

		nik_ce auto H_continuant_compound = U_store_B<T_continuant_compound>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// metapile:

/***********************************************************************************************************************/

// apply:

	template
	<
		auto static_contr,
		auto static_values,
		auto out_types
	>
	struct T_metapile_apply
	{
		template<typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return T_continuant_compound<static_contr, 0>::template
				result<static_values, out_types, 0, Ts...>(vs...);
		}
	};

/***********************************************************************************************************************/

// halt:

	// first:

		template<>
		struct T_continuant<CI::halt>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename T, typename... Ts>
			nik_ces auto result(T v, Ts... vs) -> T
				{ return v; }
		};

/***********************************************************************************************************************/

// function:

	// line:

		template<>
		struct T_continuant<CI::function>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				nik_ce auto policy = CD<c>::value(i, 2);

				return T_continuant<CI::function, genum_type{policy}>
					::template result<c, i, l, t, r, Ts...>(vs...);
			}
		};

	// to stack:

		template<>
		struct T_continuant<CI::function, genum_type{CP::to_stack}>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				nik_ce auto n = CD<c>::value(i, 1);
				nik_ce auto f = U_continuant_compound<c, n>;

				return NIK_MACHINE_TS(c, i, l, t, r, Ts..., decltype(f))
					(vs..., f);
			}
		};

	// to carry:

		template<>
		struct T_continuant<CI::function, genum_type{CP::to_carry}>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename T, typename... Ts>
			nik_ces auto result(T v, Ts... vs)
			{
				nik_ce auto n = CD<c>::value(i, 1);
				nik_ce auto f = U_continuant_compound<c, n>;

				return NIK_MACHINE_TS(c, i, l, t, r, decltype(f), Ts...)
					(f, vs...);
			}
		};

/***********************************************************************************************************************/

// argument:

	// line:

		template<>
		struct T_continuant<CI::argument>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				nik_ce auto n      = CD<c>::value (i, 1);
				nik_ce auto arg    = CD<c>::arg   (n, 1);
				nik_ce auto policy = CD<c>::value (i, 2);
				nik_ce auto l_pack = left_  <arg, U_store_T<Ts>...>;
				nik_ce auto r_pack = right_ <arg, U_store_T<Ts>...>;

				return T_continuant<CI::argument, genum_type{policy}, l_pack, r_pack>
					::template result<c, i, l, t, r, Ts...>(vs...);
			}
		};

	// to stack:

		template
		<
			template<auto...> typename B0,          auto... LUs, nik_vp(l_pack)(B0<    LUs...>*),
			template<auto...> typename B1, auto RU, auto... RUs, nik_vp(r_pack)(B1<RU, RUs...>*)
		>
		struct T_continuant<CI::argument, genum_type{CP::to_stack}, l_pack, r_pack>
		{
			using RT = T_store_U<RU>;

			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
			nik_ces auto result(T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs)
			{
				return NIK_MACHINE_TS(c, i, l, t, r, T_store_U<LUs>..., RT, T_store_U<RUs>..., RT)
					(lvs..., rv, rvs..., rv);
			}
		};

	// to carry:

		template
		<
			template<auto...> typename B0, auto LU, auto... LUs, nik_vp(l_pack)(B0<LU, LUs...>*),
			template<auto...> typename B1, auto RU, auto... RUs, nik_vp(r_pack)(B1<RU, RUs...>*)
		>
		struct T_continuant<CI::argument, genum_type{CP::to_carry}, l_pack, r_pack>
		{
			using LT = T_store_U<LU>;
			using RT = T_store_U<RU>;

			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
			nik_ces auto result(LT lv, T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs)
			{
				return NIK_MACHINE_TS(c, i, l, t, r, RT, T_store_U<LUs>..., RT, T_store_U<RUs>...)
					(rv, lvs..., rv, rvs...);
			}
		};

/***********************************************************************************************************************/

// apply:

	// line:

		template<>
		struct T_continuant<CI::apply>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				nik_ce auto n      = CD<c>::value (i, 1);
				nik_ce auto arg    = CD<c>::value (n, 1);
				nik_ce auto policy = CD<c>::value (i, 2);
				nik_ce auto l_pack = left_  <arg, U_store_T<Ts>...>;
				nik_ce auto r_pack = right_ <arg, U_store_T<Ts>...>;

				return T_continuant<CI::apply, genum_type{policy}, l_pack, r_pack>
					::template result<c, i, l, t, r, Ts...>(vs...);
			}
		};

	// to stack:

		template
		<
			template<auto...> typename B0,          auto... LUs, nik_vp(l_pack)(B0<    LUs...>*),
			template<auto...> typename B1, auto RU, auto... RUs, nik_vp(r_pack)(B1<RU, RUs...>*)
		>
		struct T_continuant<CI::apply, genum_type{CP::to_stack}, l_pack, r_pack>
		{
			using RT = T_store_U<RU>;

			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
			nik_ces auto result(T_store_U<LUs>... lvs, RT, T_store_U<RUs>... rvs)
			{
				const auto value = RT::template result<c, l, t, r, T_store_U<RUs>...>(rvs...);

				return NIK_MACHINE_TS(c, i, l, t, r, T_store_U<LUs>..., decltype(value))
					(lvs..., value);
			}
		};

	// to carry:

		template
		<
			template<auto...> typename B0, auto LU, auto... LUs, nik_vp(l_pack)(B0<LU, LUs...>*),
			template<auto...> typename B1, auto RU, auto... RUs, nik_vp(r_pack)(B1<RU, RUs...>*)
		>
		struct T_continuant<CI::apply, genum_type{CP::to_carry}, l_pack, r_pack>
		{
			using LT = T_store_U<LU>;
			using RT = T_store_U<RU>;

			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
			nik_ces auto result(LT lv, T_store_U<LUs>... lvs, RT rv, T_store_U<RUs>... rvs)
			{
				const auto value = T_restore_T<RT>::template
						result<l, t, r, LT, T_store_U<RUs>...>(lv, rvs...);

				return NIK_MACHINE_TS(c, i, l, t, r, decltype(value), T_store_U<LUs>...)
					(value, lvs...);
			}
		};

/***********************************************************************************************************************/

// multiply:

	// line:

		template<>
		struct T_continuant<CI::multiply>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				nik_ce auto policy = CD<c>::value(i, 2);

				return T_continuant<CI::multiply, genum_type{policy}>
					::NIK_MACHINE_RESULT_TS(c, i, l, t, r, Ts...)(vs...);
			}
		};

	// to stack:

		template<>
		struct T_continuant<CI::multiply, genum_type{CP::to_stack}>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename T, typename... Ts>
			nik_ces auto result(T v, Ts... vs)
			{
				auto value = (... * vs);

				return NIK_MACHINE_TS(c, i, l, t, r, T, Ts..., decltype(value))
					(v, vs..., value);
			}
		};

	// to carry:

		template<>
		struct T_continuant<CI::multiply, genum_type{CP::to_carry}>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename T, typename... Ts>
			nik_ces auto result(T v, Ts... vs)
			{
				auto value = (... * vs);

				return NIK_MACHINE_TS(c, i, l, t, r, decltype(value), Ts...)
					(value, vs...);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

