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

#include<cstdio>
#include<cstdlib>

/***********************************************************************************************************************/

	using size_type   = unsigned;
	using csize_type  = size_type const;
	using instr_type  = csize_type[3];
	using cinstr_type = instr_type const;
	using contr_type  = cinstr_type*;
	using ccontr_type = contr_type const;

	struct Contr
	{
		enum : size_type
		{
			initial, first, is_zero,
			branch_v0, branch_v1, branch_v2, branch_v3,
			return_1, factorial,
			dimension
		};
	};

	struct Instr
	{
		enum : size_type { instr, index, pos, dimension };

		constexpr static size_type value      (ccontr_type c, csize_type i) { return c[i][pos]; }
		constexpr static size_type next_index (ccontr_type c, csize_type i) { return i + c[i][index]; }
		constexpr static size_type next_instr (ccontr_type c, csize_type i) { return c[next_index(c, i)][instr]; }
	};

	template<size_type, auto...> struct cont;

	template<auto... filler>
	struct cont<Contr::first, filler...>
	{
		template<auto c, auto i, typename S, typename T, typename... Ts>
		constexpr static auto result(T v, Ts... vs) { return v; }
	};

	template<auto... filler>
	struct cont<Contr::is_zero, filler...>
	{
		template<auto c, auto i, typename S, typename T0, typename T, typename... Ts>
		constexpr static auto result(T0 v0, T v, Ts... vs)
		{
			constexpr auto instr = Instr::next_instr(c, i);
			constexpr auto index = Instr::next_index(c, i);

			return cont<instr>::template result<c, index, S, bool, Ts...>((v == 0), v, vs...);
		}
	};

	template<auto... filler>
	struct cont<Contr::branch_v0, filler...>
	{
		template<auto c, auto i, typename S, typename T, typename... Ts>
		constexpr static auto result(T v, Ts... vs) -> S
		{
			if (v)
			{
				constexpr auto ni    = Instr::value(c, i);
				constexpr auto instr = Instr::next_instr(c, ni);
				constexpr auto index = Instr::next_index(c, ni);

				return cont<instr>::template result<c, index, S, T, Ts...>(v, vs...);
			}
			else
			{
				constexpr auto instr = Instr::next_instr(c, i);
				constexpr auto index = Instr::next_index(c, i);

				return cont<instr>::template result<c, index, S, T, Ts...>(v, vs...);
			}
		}
	};

	template<auto... filler>
	struct cont<Contr::branch_v1, filler...>
	{
		template<auto c, auto i, typename S, typename T, typename... Ts>
		constexpr static auto result(T v, Ts... vs)
		{
			if (v)
			{
				constexpr auto ni    = Instr::value(c, i);
				constexpr auto instr = Instr::next_instr(c, ni);
				constexpr auto index = Instr::next_index(c, ni);

				return static_cast<S>(cont<instr>::template result<c, index, S, T, Ts...>(v, vs...));
			}
			else
			{
				constexpr auto instr = Instr::next_instr(c, i);
				constexpr auto index = Instr::next_index(c, i);

				return static_cast<S>(cont<instr>::template result<c, index, S, T, Ts...>(v, vs...));
			}
		}
	};

	template<auto... filler>
	struct cont<Contr::branch_v2, filler...>
	{
		template<auto c, auto i, typename S, typename T, typename... Ts>
		constexpr static auto result(T v, Ts... vs)
		{
			constexpr auto ni     = Instr::value(c, i);
			constexpr auto ninstr = Instr::next_instr(c, ni);
			constexpr auto nindex = Instr::next_index(c, ni);

			constexpr auto ante   = cont<ninstr>::template result<c, nindex, S, T, Ts...>;
			using ante_type       = decltype(ante(v, vs...));

			if (v) return ante(v, vs...);
			else
			{
				constexpr auto instr = Instr::next_instr(c, i);
				constexpr auto index = Instr::next_index(c, i);

				constexpr auto conse = cont<instr>::template result<c, index, S, T, Ts...>;

				return static_cast<ante_type>(conse(v, vs...));
			}
		}
	};

	template<auto... filler>
	struct cont<Contr::branch_v3, filler...> // doesn't work, can't deduce auto because of recursive call.
	{
		template<auto c, auto i, typename S, typename T, typename... Ts>
		constexpr static auto result(T v, Ts... vs)
		{
			constexpr auto instr = Instr::next_instr(c, i);
			constexpr auto index = Instr::next_index(c, i);

			constexpr auto conse = cont<instr>::template result<c, index, S, T, Ts...>;

			using conse_type = decltype(conse(v, vs...));

			if (v)
			{
				constexpr auto ni     = Instr::value(c, i);
				constexpr auto ninstr = Instr::next_instr(c, ni);
				constexpr auto nindex = Instr::next_index(c, ni);

				constexpr auto ante   = cont<ninstr>::template result<c, nindex, S, T, Ts...>;

				return static_cast<conse_type>(ante(v, vs...));
			}
			else return conse(v, vs...);
		}
	};

	template<auto... filler>
	struct cont<Contr::return_1, filler...>
	{
		template<auto c, auto i, typename S, typename... Ts>
		constexpr static auto result(Ts... vs) { return char{1}; }
	};

	template<auto... filler>
	struct cont<Contr::factorial, filler...>
	{
		template<auto c, auto i, typename S, typename T0, typename T, typename... Ts>
		constexpr static auto result(T0 v0, T v, Ts... vs)
		{
			constexpr auto instr = Instr::next_instr(c, i);
			constexpr auto index = Instr::next_index(c, i);

			constexpr auto subinstr = Instr::next_instr(c, 0);
			constexpr auto subindex = Instr::next_index(c, 0);

			auto val = v * cont<subinstr>::template result<c, subindex, S, T0, T, Ts...>(v0, v-1, vs...);

			return cont<instr>::template result<c, index, S, decltype(val), T, Ts...>(val, v, vs...);
		}
	};

	template<auto c, typename S, typename... Ts>
	constexpr auto apply(Ts... vs)
	{
		constexpr auto instr = Instr::next_instr(c, 0);
		constexpr auto index = Instr::next_index(c, 0);

		return cont<instr>::template result<c, index, S, Ts...>(vs...);
	}

/***********************************************************************************************************************/

	constexpr instr_type contr[] =
	{
		{ Contr::initial   , 1 , 0 },
		{ Contr::is_zero   , 1 , 0 },
		{ Contr::branch_v2 , 1 , 4 },
		{ Contr::factorial , 1 , 0 },
		{ Contr::first     , 1 , 0 },
		{ Contr::return_1  , 1 , 0 }
	};

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		auto val = apply<contr, size_type>(0, 5);

		printf("%d\n", val);

		return 0;
	}

