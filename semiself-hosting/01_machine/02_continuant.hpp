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

	// untyped:

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
					result<static_values, out_types, 0, Ts...>(0, vs...);
			}
		};

	// typed:

		template
		<
			auto static_contr,
			auto static_values,
			auto out_types
		>
		struct T_metapile_recurse
		{
			nik_ces auto out_type = at_<out_types, 0>;

			template<typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				return T_continuant_compound<out_type, static_contr, 0>::template
					result<static_values, out_types, 0, Ts...>(0, vs...);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

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

// jump:

	// branch:

		template<>
		struct T_continuant<CI::branch>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename T, typename... Ts>
			nik_ces auto result(T v, Ts... vs)
			{
				nik_ce auto ni = CD<c>::value(i, 1);

				if (v) { return NIK_MACHINE_TS(c, ni, l, t, r, T, Ts...)(v, vs...); }
				else   { return NIK_MACHINE_TS(c,  i, l, t, r, T, Ts...)(v, vs...); }
			}
		};

	// invert:

		template<>
		struct T_continuant<CI::invert>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename T, typename... Ts>
			nik_ces auto result(T v, Ts... vs)
			{
				nik_ce auto ni = CD<c>::value(i, 1);

				if (v) { return NIK_MACHINE_TS(c,  i, l, t, r, T, Ts...)(v, vs...); }
				else   { return NIK_MACHINE_TS(c, ni, l, t, r, T, Ts...)(v, vs...); }
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
				nik_ce auto arg    = CD<c>::value(i, 1);
				nik_ce auto policy = CD<c>::value(i, 2);
				nik_ce auto l_pack = left_ <arg, U_store_T<Ts>...>;
				nik_ce auto r_pack = right_<arg, U_store_T<Ts>...>;

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
				auto value = T_restore_T<RT>::template
						result<l, t, r, decltype(0), T_store_U<RUs>...>(0, rvs...);

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
				auto value = T_restore_T<RT>::template
						result<l, t, r, decltype(0), T_store_U<RUs>...>(0, rvs...);

				return NIK_MACHINE_TS(c, i, l, t, r, decltype(value), T_store_U<LUs>...)
					(value, lvs...);
			}
		};

/***********************************************************************************************************************/

// atomic (generic):

	// line:

		template<auto F>
		struct T_continuant<CI::atomic, F>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				nik_ce auto policy = CD<c>::value(i, 2);

				return T_continuant<CI::atomic, genum_type{policy}, F>
					::template result<c, i, l, t, r, Ts...>(vs...);
			}
		};

	// to stack:

		template<auto F>
		struct T_continuant<CI::atomic, genum_type{CP::to_stack}, F>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename T, typename... Ts>
			nik_ces auto result(T v, Ts... vs)
			{
				auto value = T_store_U<F>::template result<Ts...>(vs...);

				return NIK_MACHINE_TS(c, i, l, t, r, T, Ts..., decltype(value))
					(v, vs..., value);
			}
		};

	// to carry:

		template<auto F>
		struct T_continuant<CI::atomic, genum_type{CP::to_carry}, F>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename T, typename... Ts>
			nik_ces auto result(T v, Ts... vs)
			{
				auto value = T_store_U<F>::template result<Ts...>(vs...);

				return NIK_MACHINE_TS(c, i, l, t, r, decltype(value), Ts...)
					(value, vs...);
			}
		};

/***********************************************************************************************************************/

// comparison:

	template<> struct T_continuant< CI::equal        > : public T_continuant< CI::atomic , U_equal        <> > { };
	template<> struct T_continuant< CI::not_equal    > : public T_continuant< CI::atomic , U_not_equal    <> > { };
	template<> struct T_continuant< CI::l_than       > : public T_continuant< CI::atomic , U_l_than       <> > { };
	template<> struct T_continuant< CI::l_than_or_eq > : public T_continuant< CI::atomic , U_l_than_or_eq <> > { };
	template<> struct T_continuant< CI::g_than       > : public T_continuant< CI::atomic , U_g_than       <> > { };
	template<> struct T_continuant< CI::g_than_or_eq > : public T_continuant< CI::atomic , U_g_than_or_eq <> > { };

/***********************************************************************************************************************/

// arithmetic:

	template<> struct T_continuant< CI::add      > : public T_continuant< CI::atomic , U_add      <> > { };
	template<> struct T_continuant< CI::subtract > : public T_continuant< CI::atomic , U_subtract <> > { };
	template<> struct T_continuant< CI::multiply > : public T_continuant< CI::atomic , U_multiply <> > { };
	template<> struct T_continuant< CI::divide   > : public T_continuant< CI::atomic , U_divide   <> > { };
	template<> struct T_continuant< CI::modulo   > : public T_continuant< CI::atomic , U_modulo   <> > { };

/***********************************************************************************************************************/

// constant:

	// line:

		template<>
		struct T_continuant<CI::constant>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				nik_ce auto policy = CD<c>::value(i, 2);

				return T_continuant<CI::constant, genum_type{policy}>
					::template result<c, i, l, t, r, Ts...>(vs...);
			}
		};

	// to stack:

		template<>
		struct T_continuant<CI::constant, genum_type{CP::to_stack}>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				nik_ce auto value = CD<c>::value(i, 1);

				return NIK_MACHINE_TS(c, i, l, t, r, Ts..., decltype(value))
					(vs..., value);
			}
		};

	// to carry:

		template<>
		struct T_continuant<CI::constant, genum_type{CP::to_carry}>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename T, typename... Ts>
			nik_ces auto result(T v, Ts... vs)
			{
				nik_ce auto value = CD<c>::value(i, 1);

				return NIK_MACHINE_TS(c, i, l, t, r, decltype(value), Ts...)
					(value, vs...);
			}
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

// recursive:

	// line:

		template<>
		struct T_continuant<CI::recursive>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				nik_ce auto policy = CD<c>::value(i, 2);

				return T_continuant<CI::recursive, genum_type{policy}>
					::template result<c, i, l, t, r, Ts...>(vs...);
			}
		};

	// to stack:

		template<>
		struct T_continuant<CI::recursive, genum_type{CP::to_stack}>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				nik_ce auto n    = CD<c>::value(i, 1);
				nik_ce auto fpos = CD<c>::value(n, 1);
				nik_ce auto tpos = CD<c>::value(n, 2);
				nik_ce auto u    = at_<t, tpos>;
				nik_ce auto f    = U_continuant_compound<u, c, fpos>;

				return NIK_MACHINE_TS(c, i, l, t, r, Ts..., decltype(f))
					(vs..., f);
			}
		};

	// to carry:

		template<>
		struct T_continuant<CI::recursive, genum_type{CP::to_carry}>
		{
			template<NIK_MACHINE_PARAMS(c, i, l, t, r), typename T, typename... Ts>
			nik_ces auto result(T v, Ts... vs)
			{
				nik_ce auto n    = CD<c>::value(i, 1);
				nik_ce auto fpos = CD<c>::value(n, 1);
				nik_ce auto tpos = CD<c>::value(n, 2);
				nik_ce auto u    = at_<t, tpos>;
				nik_ce auto f    = U_continuant_compound<u, c, fpos>;

				return NIK_MACHINE_TS(c, i, l, t, r, decltype(f), Ts...)
					(f, vs...);
			}
		};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

