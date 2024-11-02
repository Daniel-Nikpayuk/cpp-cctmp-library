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

// callback:

/***********************************************************************************************************************/

// concept:

	template<typename F, auto N, typename T>
	using func_type = T(*)(const F (*)[N], T);

	template<typename F, auto N, typename T>
	constexpr auto halt(const F (*next)[N], T n) { return n; }

	template<typename F, auto N, typename T>
	constexpr auto square(const F (*next)[N], T n) { return next[n > 100 ? 0 : 1](next, n*n); }

	template<typename F, auto N, typename T>
	constexpr func_type<F, N, T> state[] =
	{
		halt   <F, N, T>,
		square <F, N, T>
	};

	template<typename F, auto N, typename T>
	constexpr auto start(const F (*next)[N], T n) { return next[1](next, n); }

	//	printf("%d\n", call<func_arr[0]>);

/***********************************************************************************************************************/

// constexpr:

	template<typename T>
	using func_type = T(*)(T);

	template<auto next, typename T>
	constexpr auto halt(T n) { return n; }

	template<auto next, typename T>
	constexpr auto square(T n) { return next[n > 100 ? 0 : 1](n * n); }

	template<typename T>
	constexpr func_type<T> state[2] =
	{
		halt   <state<T>, T>,
		square <state<T>, T>
	};

	template<typename T>
	constexpr auto start(T n) { return state<T>[1](n); }

/*
	template<typename T>
	constexpr auto start(T n)
	{
		func_type<T> state[2] = {};

		state[0] = halt   <state, T>; // state can't be passed here as a template param.
		state[1] = square <state, T>;

		return state[1](n);
	}
*/

		static_assert(start(2) == 65536);

		printf("%d\n", start(main_at(0, argc, argv, 2))); // prints: 65536

/***********************************************************************************************************************/

// constexpr deferred:

	template<typename Type, typename SizeType, SizeType Size>
	struct abstract_machine
	{
		using size_type		= SizeType;
		using function_type	= Type(*)(abstract_machine, Type);

		function_type state[Size];

		constexpr abstract_machine() : state{} { }

		constexpr function_type & operator [] (size_type n) { return state[n]; }
	};

	template<typename Machine, typename T>
	constexpr auto halt(Machine machine, T n) { return n; }

	template<typename Machine, typename T>
	constexpr auto square(Machine machine, T n) { return machine[n > 100 ? 0 : 1](machine, n * n); }

	template<typename T>
	constexpr auto start(T n)
	{
		using Machine = abstract_machine<T, unsigned, 2>;

		Machine machine;

		machine[0] = halt   <Machine, T>;
		machine[1] = square <Machine, T>;

		return machine[1](machine, n);
	}

		static_assert(start(2) == 65536);

		printf("%d\n", start(main_at(0, argc, argv, 2)));

/***********************************************************************************************************************/

// :

	template<typename F>
	using func_type = void(*)(F);

	template<typename F> constexpr void hi    (F f) { f("hi"   ); }
	template<typename F> constexpr void hey   (F f) { f("hey"  ); }
	template<typename F> constexpr void hello (F f) { f("hello"); }

	template<typename F>
	constexpr func_type<F> callback[3] = { hi<F>, hey<F>, hello<F> };

	constexpr void print_cstr(const char *str)
	{
		while (*str != '\0') printf("%c", *str++);

		printf("\n");
	}

	constexpr void print_string(int n) { callback<decltype(print_cstr)>[n](print_cstr); }

		print_string(0); // prints: hi
		print_string(1); // prints: hey
		print_string(2); // prints: hello

