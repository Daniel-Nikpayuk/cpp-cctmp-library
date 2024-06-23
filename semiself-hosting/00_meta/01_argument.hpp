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

// argument:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// overload:

/***********************************************************************************************************************/

// operators:

	struct ArgOverload
	{
		enum : gkey_type
		{
			id = 0, identity = id,// convenience for default params.
			nop         , empty     , size , first , at ,	// basis
			upshift     , downshift ,			// bitwise
			dereference , appoint   ,			// mutation
			dimension
		};
	};

	// id:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, ArgOverload::id, filler...>
		{
			template<typename T>
			nik_ces auto result(T v) -> T { return v; } // type preservation ?

		}; nik_ce auto _id_ = U_arg_overload<ArgOverload::id>;

/***********************************************************************************************************************/

// basis:

	// nop (no operation):

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, ArgOverload::nop, filler...>
		{
			template<typename... Ts>
			nik_ces void result(Ts...) { }

		}; nik_ce auto _nop_ = U_arg_overload<ArgOverload::nop>;

	// empty:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, ArgOverload::empty, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (sizeof...(Ts) == 0); }

		}; nik_ce auto _empty_ = U_arg_overload<ArgOverload::empty>;

	// size:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, ArgOverload::size, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return sizeof...(Ts); }

		}; nik_ce auto _size_ = U_arg_overload<ArgOverload::size>;

	// first:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, ArgOverload::first, filler...>
		{
			template<typename T, typename... Ts>
			nik_ces auto result(T v, Ts... vs) { return v; }

		}; nik_ce auto _first_ = U_arg_overload<ArgOverload::first>;

	// at:

		template
		<
			         auto... LUs, nik_vp(p0)(T_pack_Vs<    LUs...>*),
			auto RU, auto... RUs, nik_vp(p1)(T_pack_Vs<RU, RUs...>*),
			auto... filler
		>
		struct T_grammar<Shape::argument, Pattern::overload, ArgOverload::at, p0, p1, filler...>
		{
			nik_ces auto result(T_store_U<LUs>... lvs, T_store_U<RU> rv, T_store_U<RUs>... rvs)
				{ return rv; }

		}; template<auto... Vs> // open to additional specialization.
			nik_ce auto _at_ = U_arg_overload<ArgOverload::at, Vs...>;

/***********************************************************************************************************************/

// bitwise:

	// upshift:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, ArgOverload::upshift, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... << vs); }

		}; nik_ce auto _upshift_ = U_arg_overload<ArgOverload::upshift>;

	// downshift:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, ArgOverload::downshift, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... >> vs); }

		}; nik_ce auto _downshift_ = U_arg_overload<ArgOverload::downshift>;

/***********************************************************************************************************************/

// mutation:

	// dereference:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, ArgOverload::dereference, filler...>
		{
			template<typename T>
			nik_ces auto result(T v) { return *v; }

		}; nik_ce auto _dereference_ = U_arg_overload<ArgOverload::dereference>;

	// appoint:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, ArgOverload::appoint, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return *v1 = (decltype(*v1)) v2; } // c style cast

		}; nik_ce auto _appoint_ = U_arg_overload<ArgOverload::appoint>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// number:

/***********************************************************************************************************************/

// operators:

	struct ArgNumber
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			equal        , not_equal             ,	// comparison
			less_than    , less_than_or_equal    ,
			greater_than , greater_than_or_equal ,
			add          , subtract              ,
			multiply     , divide                ,
			modulo       , from_string           ,	// arithmetic
			dimension
		};
	};

/***********************************************************************************************************************/

// comparison:

	// equal:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, ArgNumber::equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... == vs); }

		}; nik_ce auto _equal_ = U_arg_number<ArgNumber::equal>;

	// not_equal:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, ArgNumber::not_equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... != vs); }

		}; nik_ce auto _not_equal_ = U_arg_number<ArgNumber::not_equal>;

	// less_than:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, ArgNumber::less_than, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... < vs); }

		}; nik_ce auto _less_than_ = U_arg_number<ArgNumber::less_than>;

	// less_than_or_equal:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, ArgNumber::less_than_or_equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... <= vs); }

		}; nik_ce auto _less_than_or_equal_ = U_arg_number<ArgNumber::less_than_or_equal>;

	// greater_than:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, ArgNumber::greater_than, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... > vs); }

		}; nik_ce auto _greater_than_ = U_arg_number<ArgNumber::greater_than>;

	// greater_than_or_equal:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, ArgNumber::greater_than_or_equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... >= vs); }

		}; nik_ce auto _greater_than_or_equal_ = U_arg_number<ArgNumber::greater_than_or_equal>;

	// syntactic sugar:

		nik_ce auto _lt_		= _less_than_;
		nik_ce auto _gt_		= _greater_than_;
		nik_ce auto _lt_or_eq_		= _less_than_or_equal_;
		nik_ce auto _gt_or_eq_		= _greater_than_or_equal_;

		// is_equal:

		//	template<auto V>
		//	nik_ce auto _is_equal_ = _curry_<_equal_, V>;

		// is_zero:

		//	nik_ce auto _is_zero_ = _is_equal_<_zero>;

		// is_not_equal:

		//	template<auto V>
		//	nik_ce auto _is_not_equal_ = _curry_<_not_equal_, V>;

		// not_zero:

		//	nik_ce auto _is_not_zero_ = _is_not_equal_<_zero>;
		//	nik_ce auto _not_zero_    = _is_not_zero_;

		// is_less_than:

		//	template<auto V> nik_ce auto _is_less_than_		= _curry_<_gt_, V>;
		//	template<auto V> nik_ce auto _is_lt_			= _curry_<_gt_, V>;

		// is_less_than_or_equal:

		//	template<auto V> nik_ce auto _is_less_than_or_equal_	= _curry_<_gt_or_eq_, V>;
		//	template<auto V> nik_ce auto _is_lt_or_eq_		= _curry_<_gt_or_eq_, V>;

		// is_greater_than:

		//	template<auto V> nik_ce auto _is_greater_than_		= _curry_<_lt_, V>;
		//	template<auto V> nik_ce auto _is_gt_			= _curry_<_lt_, V>;

		// is_greater_than_or_equal:

		//	template<auto V> nik_ce auto _is_greater_than_or_equal_	= _curry_<_lt_or_eq_, V>;
		//	template<auto V> nik_ce auto _is_gt_or_eq_		= _curry_<_lt_or_eq_, V>;

/***********************************************************************************************************************/

// arithmetic:

	// add:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, ArgNumber::add, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... + vs); }

		}; nik_ce auto _add_ = U_arg_number<ArgNumber::add>;

	// subtract:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, ArgNumber::subtract, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... - vs); }

		}; nik_ce auto _subtract_ = U_arg_number<ArgNumber::subtract>;

	// multiply:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, ArgNumber::multiply, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... * vs); }

		}; nik_ce auto _multiply_ = U_arg_number<ArgNumber::multiply>;

	// divide:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, ArgNumber::divide, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... / vs); }

		}; nik_ce auto _divide_ = U_arg_number<ArgNumber::divide>;

	// modulo:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, ArgNumber::modulo, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... % vs); }

		}; nik_ce auto _modulo_ = U_arg_number<ArgNumber::modulo>;

	// from string:

		template<auto U>
		struct T_grammar<Shape::argument, Pattern::number, ArgNumber::from_string, U>
		{
			using size_type  = T_store_U<U>;
			using csize_type = size_type const;

			template<typename In, typename End>
			nik_ces auto result(In in, End end) -> size_type
			{
				size_type num = 0;

				for (size_type dig = 0, exp = 1; end != in; exp *= 10)
				{
					dig  = (*--end) - '0';
					num += dig * exp;
				}

				return num;
			}

		}; template<auto U = U_auto_int>
			nik_ce auto _string_to_builtin_ = U_arg_number<ArgNumber::from_string, U>;

	// syntactic sugar:

		// increment:

		//	template<auto V = _one> nik_ce auto _increment_		= _curry_<_add_, V>;

		// decrement:

			// Note: _curry_<_add_, -V> often has greater type safety than _curry_<_subtract_, V>.

		//	template<auto V = _one> nik_ce auto _decrement_		= _curry_<_add_, -V>;

		// times:

		//	template<auto V = _two> nik_ce auto _times_		= _curry_<_multiply_, V>;

		// quotient:

		//	template<auto V = _two> nik_ce auto _quotient_		= _curry_<_divide_, V>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

