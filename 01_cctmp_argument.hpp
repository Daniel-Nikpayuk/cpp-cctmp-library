/************************************************************************************************************************
**
** Copyright 2022-2023 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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
			nop         , first     , // basis
			upshift     , downshift , // bitwise
			dereference , appoint   , // mutation
			dimension
		};
	};

	// id:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, ArgOverload::id, filler...>
		{
			template<typename T>
			nik_ces auto result(T v) { return v; }

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

	// first:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, ArgOverload::first, filler...>
		{
			template<typename T, typename... Ts>
			nik_ces auto result(T v, Ts... vs) { return v; }

		}; nik_ce auto _first_ = U_arg_overload<ArgOverload::first>;

/***********************************************************************************************************************/

// bitwise:

	// upshift:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, ArgOverload::upshift, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return (v1 << v2); }

		}; nik_ce auto _upshift_ = U_arg_overload<ArgOverload::upshift>;

	// downshift:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, ArgOverload::downshift, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return (v1 >> v2); }

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
			nik_ces auto result(T1 v1, T2 v2) { return *v1 = v2; }

			template<typename T1, typename T2>
			nik_ces auto result(T1 *v1, T2 v2) { return *v1 = (T1 const) v2; }

		}; nik_ce auto _appoint_ = U_arg_overload<ArgOverload::appoint>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// higher order:

/***********************************************************************************************************************/

// operators:

	struct ArgHigherOrder
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			cast , constant , wrap , bind , curry , find, // basis
			dimension
		};
	};

/***********************************************************************************************************************/

// basis:

	// cast:

		template<typename Type, nik_vp(V)(Type*)>
		struct T_grammar<Shape::argument, Pattern::higher_order, ArgHigherOrder::cast, V>
		{
			template<typename T>
			nik_ces auto result(T v) { return Type(v); }

		}; template<auto V>
			nik_ce auto _cast_ = U_arg_higher_order<ArgHigherOrder::cast, V>;

		// to_bool (syntactic sugar):

			nik_ce auto _to_bool_ = _cast_<U_store_T<bool>>;

	// constant:

		template<auto V>
		struct T_grammar<Shape::argument, Pattern::higher_order, ArgHigherOrder::constant, V>
		{
			template<typename... Ts>
			nik_ces auto result(Ts...) { return V; }

		}; template<auto V>
			nik_ce auto _constant_ = U_arg_higher_order<ArgHigherOrder::constant, V>;

	// wrap:

		template<auto f>
		struct T_grammar<Shape::argument, Pattern::higher_order, ArgHigherOrder::wrap, f>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return f(vs...); }

		}; template<auto f>
			nik_ce auto _wrap_ = U_arg_higher_order<ArgHigherOrder::wrap, f>;

	// bind:

		template<auto f, auto... ps>
		struct T_grammar<Shape::argument, Pattern::higher_order, ArgHigherOrder::bind, f, ps...>
		{
			using F = T_store_U<f>;

			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return F::template result<ps...>(vs...); }

		}; template<auto f, auto... ps>
			nik_ce auto _bind_ = U_arg_higher_order<ArgHigherOrder::bind, f, ps...>;

		// apply (syntactic sugar):

			template<auto f>
			nik_ce auto _apply_ = _bind_<f>;

			template<auto f, typename... Ts>
			nik_ce auto apply(Ts... vs) { return T_store_U<f>::template result<>(vs...); }

	// curry:

		template<auto f, auto... Vs>
		struct T_grammar<Shape::argument, Pattern::higher_order, ArgHigherOrder::curry, f, Vs...>
		{
			using F = T_store_U<f>;

			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return F::template result<>(Vs..., vs...); }

		}; template<auto f, auto... Vs>
			nik_ce auto _curry_ = U_arg_higher_order<ArgHigherOrder::curry, f, Vs...>;

	// find:

		template<auto p>
		struct T_grammar<Shape::argument, Pattern::higher_order, ArgHigherOrder::find, p>
		{
			using P = T_store_U<p>;

			template<typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				auto pos   = 0;
				bool match = false;

				return ((pos += not(match = (match || P::template result<>(vs)))), ...);
			}

		}; template<auto p>
			nik_ce auto _find_ = U_arg_higher_order<ArgHigherOrder::find, p>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// boolean:

/***********************************************************************************************************************/

// operators:

	struct ArgBoolean
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			not_ , and_ , or_ , implies , equivalent ,	// logical
			dimension
		};
	};

/***********************************************************************************************************************/

// logical:

	// not_:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::boolean, ArgBoolean::not_, filler...>
		{
			template<typename T>
			nik_ces auto result(T v) { return !v; }

		}; nik_ce auto _not_ = U_arg_boolean<ArgBoolean::not_>;

	// and_:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::boolean, ArgBoolean::and_, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... && vs); }

		}; nik_ce auto _and_ = U_arg_boolean<ArgBoolean::and_>;

	// or_:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::boolean, ArgBoolean::or_, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... || vs); }

		}; nik_ce auto _or_ = U_arg_boolean<ArgBoolean::or_>;

	// implies:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::boolean, ArgBoolean::implies, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return (!v1 || v2); }

		}; nik_ce auto _implies_ = U_arg_boolean<ArgBoolean::implies>;

	// equivalent:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::boolean, ArgBoolean::equivalent, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return ((!v1 || v2) && (v1 || !v2)); }

		}; nik_ce auto _equivalent_ = U_arg_boolean<ArgBoolean::equivalent>;

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
			equal          , not_equal             ,	// comparison
			less_than      , less_than_or_equal    ,
			greater_than   , greater_than_or_equal ,
			add , subtract , multiply , divide , modulo ,	// arithmetic
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

			template<auto V>
			nik_ce auto _is_equal_ = _curry_<_equal_, V>;

		// is_zero:

			nik_ce auto _is_zero_ = _is_equal_<_zero>;

		// is_not_equal:

			template<auto V>
			nik_ce auto _is_not_equal_ = _curry_<_not_equal_, V>;

		// not_zero:

			nik_ce auto _is_not_zero_ = _is_not_equal_<_zero>;
			nik_ce auto _not_zero_    = _is_not_zero_;

		// is_less_than:

			template<auto V> nik_ce auto _is_less_than_		= _curry_<_gt_, V>;
			template<auto V> nik_ce auto _is_lt_			= _curry_<_gt_, V>;

		// is_less_than_or_equal:

			template<auto V> nik_ce auto _is_less_than_or_equal_	= _curry_<_gt_or_eq_, V>;
			template<auto V> nik_ce auto _is_lt_or_eq_		= _curry_<_gt_or_eq_, V>;

		// is_greater_than:

			template<auto V> nik_ce auto _is_greater_than_		= _curry_<_lt_, V>;
			template<auto V> nik_ce auto _is_gt_			= _curry_<_lt_, V>;

		// is_greater_than_or_equal:

			template<auto V> nik_ce auto _is_greater_than_or_equal_	= _curry_<_lt_or_eq_, V>;
			template<auto V> nik_ce auto _is_gt_or_eq_		= _curry_<_lt_or_eq_, V>;

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

	// syntactic sugar:

		// increment:

			template<auto V = _one> nik_ce auto _increment_		= _curry_<_add_, V>;

		// decrement:

			// Note: _curry_<_add_, -V> often has greater type safety than _curry_<_subtract_, V>.

			template<auto V = _one> nik_ce auto _decrement_		= _curry_<_add_, -V>;

		// times:

			template<auto V = _two> nik_ce auto _times_		= _curry_<_multiply_, V>;

		// quotient:

			template<auto V = _two> nik_ce auto _quotient_		= _curry_<_divide_, V>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array:

/***********************************************************************************************************************/

// operators:

	struct ArgArray
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			is        , type , length ,	// meta
			begin     , last , end    ,	// basis
			log_floor ,			// 2^N
			dimension
		};
	};

/***********************************************************************************************************************/

// meta:

	// is:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, ArgArray::is, filler...>
		{
			template<typename T> nik_ces auto result(T) { return false; }
			template<typename T, auto S> nik_ces auto result(T(&)[S]) { return true; }

		}; nik_ce auto _is_array_ = U_arg_array<ArgArray::is>;

	// type:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, ArgArray::type, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(T(&)[S]) { return U_store_T<T>; }

		}; nik_ce auto _array_type_ = U_arg_array<ArgArray::type>;

	// length:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, ArgArray::length, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(T(&)[S]) { return S; }

		}; nik_ce auto _array_length_ = U_arg_array<ArgArray::length>;

/***********************************************************************************************************************/

// basis:

	// begin:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, ArgArray::begin, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(T(&a)[S]) { return a; }

		}; nik_ce auto _array_begin_ = U_arg_array<ArgArray::begin>;

	// last:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, ArgArray::last, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(T(&a)[S]) { return a + (S - 1); }

		}; nik_ce auto _array_last_ = U_arg_array<ArgArray::last>;

	// end:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, ArgArray::end, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(T(&a)[S]) { return a + S; }

		}; nik_ce auto _array_end_ = U_arg_array<ArgArray::end>;

/***********************************************************************************************************************/

// 2^N:

	// log floor:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, ArgArray::log_floor, filler...>
		{
			nik_ces auto array_end = T_store_U<_array_end_>::result(array_2_N);

			nik_ces gkey_type result(gcindex_type n)
			{
				gcindex_type *k = array_end;

				while (--k != array_2_N) if (*k <= n) break;

				return k - array_2_N;
			}

		}; nik_ce auto _log_floor_ = U_arg_array<ArgArray::log_floor>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// subarray:

/***********************************************************************************************************************/

// operators:

	struct ArgSubarray
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			length , match , contains , same , // basis
			dimension
		};
	};

/***********************************************************************************************************************/

// basis:

	// length:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::subarray, ArgSubarray::length, filler...>
		{
			template<typename In, typename End>
			nik_ces auto result(In in, End end) { return end - in; }

		}; nik_ce auto _subarray_length_ = U_arg_subarray<ArgSubarray::length>;

	// match:

		template<auto f>
		struct T_grammar<Shape::argument, Pattern::subarray, ArgSubarray::match, f>
		{
			using F = T_store_U<f>;

			template<typename In0, typename End0, typename In1, typename End1>
			nik_ces auto result(In0 in0, End0 end0, In1 in1, End1 end1)
			{
				while (in0 != end0)
					if (F::template result<>(in0->cbegin(), in0->cend(), in1, end1))
						break; else ++in0;

				return in0;
			}

			template<typename In, typename End, typename T>
			nik_ces auto result(In in, End end, T v)
			{
				while (in != end) if (F::template result<>(*in, v)) break; else ++in;

				return in;
			}

		}; template<auto f = _equal_>
			nik_ce auto _subarray_match_ = U_arg_subarray<ArgSubarray::match, f>;

	// same:

		template<auto f>
		struct T_grammar<Shape::argument, Pattern::subarray, ArgSubarray::same, f>
		{
			using F = T_store_U<f>;

			template<typename In0, typename End0, typename In1, typename End1>
			nik_ces auto result(In0 in0, End0 end0, In1 in1, End1 end1)
			{
				if ((end0 - in0) != (end1 - in1)) return false;

				while (in0 != end0)
					if (F::template result<>(*in0, *in1)) { ++in0; ++in1; }
					else break;

				return (in0 == end0);
			}

			template<typename T0, typename T1>
			nik_ces auto result(const T0 & v0, const T1 & v1)
				{ return result(v0.cbegin(), v0.cend(), v1.cbegin(), v1.cend()); }

		}; template<auto f = _equal_>
			nik_ce auto _subarray_same_ = U_arg_subarray<ArgSubarray::same, f>;

	// syntactic sugar:

		template<auto f = _equal_>
		nik_ce auto _subarray_match_same_ = _subarray_match_<_subarray_same_<f>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

