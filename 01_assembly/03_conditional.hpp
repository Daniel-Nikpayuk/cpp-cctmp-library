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

// conditional:

namespace assembly {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// go to:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::go_to, AT::id, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);

			return NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_TS(c, ni, j, l, t, r, Ts...)
					(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// branch:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::branch, AT::id, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);

			if (v) return NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_2TS(c, ni, j, l, t, r, T, Ts...)
					(v, vs...);

			else   return NIK_ASSEMBLY_TEMPLATE(c,  i)
				::NIK_ASSEMBLY_RESULT_2TS(c,  i, j, l, t, r, T, Ts...)
					(v, vs...);
		}
	};

/***********************************************************************************************************************/

// ante:

	template<auto... filler>
	struct T_assembly<AN::branch, AT::ante, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);

			if (v) return NIK_ASSEMBLY_TEMPLATE(c, ni)
					::NIK_ASSEMBLY_RESULT_2TS(c, ni, j, l, t, r, T, Ts...)
						(v, vs...);
			else
			{
				using ante_type = decltype
				(
					NIK_ASSEMBLY_TEMPLATE(c, ni)
						::NIK_ASSEMBLY_RESULT_2TS(c, ni, j, l, t, r, T, Ts...)
							(v, vs...)
				);

				return static_cast<ante_type>
				(
					NIK_ASSEMBLY_TEMPLATE(c,  i)
						::NIK_ASSEMBLY_RESULT_2TS(c,  i, j, l, t, r, T, Ts...)
							(v, vs...)
				);
			}
		}
	};

/***********************************************************************************************************************/

// conse:

	template<auto... filler>
	struct T_assembly<AN::branch, AT::conse, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);

			if (v)
			{
				using conse_type = decltype
				(
					NIK_ASSEMBLY_TEMPLATE(c,  i)
						::NIK_ASSEMBLY_RESULT_2TS(c,  i, j, l, t, r, T, Ts...)
							(v, vs...)
				);

				return static_cast<conse_type>
				(
					NIK_ASSEMBLY_TEMPLATE(c, ni)
						::NIK_ASSEMBLY_RESULT_2TS(c, ni, j, l, t, r, T, Ts...)
							(v, vs...)
				);
			}
			else return NIK_ASSEMBLY_TEMPLATE(c,  i)
					::NIK_ASSEMBLY_RESULT_2TS(c,  i, j, l, t, r, T, Ts...)
						(v, vs...);
		}
	};

/***********************************************************************************************************************/

// port:

	template<auto... filler>
	struct T_assembly<AN::branch, AT::port, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto n  = AD<c>::num(i);
			nik_ce auto s  = at_<t, n>;
			using ret_type = T_store_U<s>;

			if (v) return static_cast<ret_type>
			(
				NIK_ASSEMBLY_TEMPLATE(c, ni)
					::NIK_ASSEMBLY_RESULT_2TS(c, ni, j, l, t, r, T, Ts...)
						(v, vs...)
			);

			else   return static_cast<ret_type>
			(
				NIK_ASSEMBLY_TEMPLATE(c,  i)
					::NIK_ASSEMBLY_RESULT_2TS(c,  i, j, l, t, r, T, Ts...)
						(v, vs...)
			);
		}
	};

/***********************************************************************************************************************/

// pull:

	template<auto... filler>
	struct T_assembly<AN::branch, AT::pull, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<at_<t, r>>
		{
			nik_ce auto ni = AD<c>::pos(i);

			if (v) return NIK_ASSEMBLY_TEMPLATE(c, ni)
					::NIK_ASSEMBLY_RESULT_2TS(c, ni, j, l, t, r, T, Ts...)
						(v, vs...);

			else   return NIK_ASSEMBLY_TEMPLATE(c,  i)
					::NIK_ASSEMBLY_RESULT_2TS(c,  i, j, l, t, r, T, Ts...)
						(v, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// invert:

/***********************************************************************************************************************/

// id:

	template<auto... filler>
	struct T_assembly<AN::invert, AT::id, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);

			if (v) return NIK_ASSEMBLY_TEMPLATE(c,  i)
				::NIK_ASSEMBLY_RESULT_2TS(c,  i, j, l, t, r, T, Ts...)
					(v, vs...);

			else   return NIK_ASSEMBLY_TEMPLATE(c, ni)
				::NIK_ASSEMBLY_RESULT_2TS(c, ni, j, l, t, r, T, Ts...)
					(v, vs...);
		}
	};

/***********************************************************************************************************************/

// ante:

	template<auto... filler>
	struct T_assembly<AN::invert, AT::ante, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);

			if (v) return NIK_ASSEMBLY_TEMPLATE(c,  i)
					::NIK_ASSEMBLY_RESULT_2TS(c,  i, j, l, t, r, T, Ts...)
						(v, vs...);
			else
			{
				using ante_type = decltype
				(
					NIK_ASSEMBLY_TEMPLATE(c,  i)
						::NIK_ASSEMBLY_RESULT_2TS(c,  i, j, l, t, r, T, Ts...)
							(v, vs...)
				);

				return static_cast<ante_type>
				(
					NIK_ASSEMBLY_TEMPLATE(c, ni)
						::NIK_ASSEMBLY_RESULT_2TS(c, ni, j, l, t, r, T, Ts...)
							(v, vs...)
				);
			}
		}
	};

/***********************************************************************************************************************/

// conse:

	template<auto... filler>
	struct T_assembly<AN::invert, AT::conse, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);

			if (v)
			{
				using conse_type = decltype
				(
					NIK_ASSEMBLY_TEMPLATE(c, ni)
						::NIK_ASSEMBLY_RESULT_2TS(c, ni, j, l, t, r, T, Ts...)
							(v, vs...)
				);

				return static_cast<conse_type>
				(
					NIK_ASSEMBLY_TEMPLATE(c,  i)
						::NIK_ASSEMBLY_RESULT_2TS(c,  i, j, l, t, r, T, Ts...)
							(v, vs...)
				);
			}
			else return NIK_ASSEMBLY_TEMPLATE(c, ni)
					::NIK_ASSEMBLY_RESULT_2TS(c, ni, j, l, t, r, T, Ts...)
						(v, vs...);
		}
	};

/***********************************************************************************************************************/

// port:

	template<auto... filler>
	struct T_assembly<AN::invert, AT::port, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs)
		{
			nik_ce auto ni = AD<c>::pos(i);
			nik_ce auto n  = AD<c>::num(i);
			nik_ce auto s  = at_<t, n>;
			using ret_type = T_store_U<s>;

			if (v) return static_cast<ret_type>
			(
				NIK_ASSEMBLY_TEMPLATE(c,  i)
					::NIK_ASSEMBLY_RESULT_2TS(c,  i, j, l, t, r, T, Ts...)
						(v, vs...)
			);

			else   return static_cast<ret_type>
			(
				NIK_ASSEMBLY_TEMPLATE(c, ni)
					::NIK_ASSEMBLY_RESULT_2TS(c, ni, j, l, t, r, T, Ts...)
						(v, vs...)
			);
		}
	};

/***********************************************************************************************************************/

// pull:

	template<auto... filler>
	struct T_assembly<AN::invert, AT::pull, filler...>
	{
		template<NIK_ASSEMBLY_PARAMS(c, i, j, l, t, r), typename T, typename... Ts>
		nik_ces auto result(T v, Ts... vs) -> T_store_U<at_<t, r>>
		{
			nik_ce auto ni = AD<c>::pos(i);

			if (v) return NIK_ASSEMBLY_TEMPLATE(c,  i)
					::NIK_ASSEMBLY_RESULT_2TS(c,  i, j, l, t, r, T, Ts...)
						(v, vs...);

			else   return NIK_ASSEMBLY_TEMPLATE(c, ni)
					::NIK_ASSEMBLY_RESULT_2TS(c, ni, j, l, t, r, T, Ts...)
						(v, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace assembly

