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

// sfinae:

	// inspired by an Eric Niebler post on Bluesky.

/***********************************************************************************************************************/

	template<typename...> struct T_pack_Ts;

	template<template<typename...> typename, typename F, typename... Ts>
	using _drop = T_pack_Ts<F, Ts...>;

	constexpr bool _callable(void*) { return false; }

	template<typename F, typename... Ts, typename = _drop<F::template type, F, Ts...>>
	constexpr bool _callable(T_pack_Ts<F, Ts...>*) { return true; }

	template<typename F, typename... Ts>
	constexpr bool callable = _callable(static_cast<T_pack_Ts<F, Ts...>*>(nullptr));

	template<bool True, auto...>
	struct lazy_call
	{
		template<typename F, typename... Ts>
		using lazy_type = typename F::template type<Ts...>;
	};

	template<auto... filler>
	struct lazy_call<false, filler...>
	{
		template<typename F, typename... Ts>
		using lazy_type = T_pack_Ts<F, Ts...>;
	};

	template<typename F, typename... Ts>
	using call = typename lazy_call<callable<F, Ts...>>::template lazy_call<F, Ts...>;

	struct T_func1
	{
		template<typename T0, typename T1>
		using type = T_pack_Ts<T0, T1>;
	};

	template<typename F>
	struct curry_call
	{
		template<typename... Ts>
		using type = call<F, Ts...>;
	};

	// main:

		static_assert(!callable<curry_call<T_func1>, int, int>);

