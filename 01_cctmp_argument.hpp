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

// basis:

	// id:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::id, filler...>
		{
			template<typename T>
			nik_ces auto result(T v) { return v; }

		}; nik_ce auto _id_ = U_arg_overload<Overload::id>;

/***********************************************************************************************************************/

// bitwise:

	// upshift:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::upshift, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return (v1 << v2); }

		}; nik_ce auto _upshift_ = U_arg_overload<Overload::upshift>;

	// downshift:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::downshift, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return (v1 >> v2); }

		}; nik_ce auto _downshift_ = U_arg_overload<Overload::downshift>;

/***********************************************************************************************************************/

// mutation:

	// assign:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::assign, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return v1 = v2; }

		}; nik_ce auto _assign_ = U_arg_overload<Overload::assign>;

	// dereference:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::overload, Overload::dereference, filler...>
		{
			template<typename T>
			nik_ces auto & result(T v) { return *v; }

		}; nik_ce auto _dereference_ = U_arg_overload<Overload::dereference>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// higher order:

/***********************************************************************************************************************/

// basis:

	// cast:

		template<typename Type, nik_vp(V)(Type*)>
		struct T_grammar<Shape::argument, Pattern::higher_order, HigherOrder::cast, V>
		{
			template<typename T>
			nik_ces auto result(T v) { return Type(v); }

		}; template<auto V>
			nik_ce auto _cast_ = U_arg_higher_order<HigherOrder::cast, V>;

		// to_bool (syntactic sugar):

			nik_ce auto _to_bool_ = _cast_<U_store_T<bool>>;

	// constant:

		template<auto V>
		struct T_grammar<Shape::argument, Pattern::higher_order, HigherOrder::constant, V>
		{
			template<typename... Ts>
			nik_ces auto result(Ts...) { return V; }

		}; template<auto V>
			nik_ce auto _constant_ = U_arg_higher_order<HigherOrder::constant, V>;

	// wrap:

		template<auto f>
		struct T_grammar<Shape::argument, Pattern::higher_order, HigherOrder::wrap, f>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return f(vs...); }

		}; template<auto f>
			nik_ce auto _wrap_ = U_arg_higher_order<HigherOrder::wrap, f>;

	// bind:

		template<auto f, auto... ps>
		struct T_grammar<Shape::argument, Pattern::higher_order, HigherOrder::bind, f, ps...>
		{
			using F = T_store_U<f>;

			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return F::template result<ps..., Ts...>(vs...); }

		}; template<auto f, auto... ps>
			nik_ce auto _bind_ = U_arg_higher_order<HigherOrder::bind, f, ps...>;

		// apply (syntactic sugar):

			template<auto f>
			nik_ce auto _apply_ = _bind_<f>;

	// curry:

		template<auto f, auto... Vs>
		struct T_grammar<Shape::argument, Pattern::higher_order, HigherOrder::curry, f, Vs...>
		{
			using F = T_store_U<f>;

			template<typename... Ts>
			nik_ces auto result(Ts... vs)
				{ return F::template result<decltype(Vs)..., Ts...>(Vs..., vs...); }

		}; template<auto f, auto... Vs>
			nik_ce auto _curry_ = U_arg_higher_order<HigherOrder::curry, f, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// abstract:

/***********************************************************************************************************************/

	// nothing yet.

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// access:

/***********************************************************************************************************************/

	// nothing yet.

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// list:

/***********************************************************************************************************************/

	// nothing yet.

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// boolean:

/***********************************************************************************************************************/

// logical:

	// not_:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::boolean, Boolean::not_, filler...>
		{
			template<typename T>
			nik_ces auto result(T v) { return !v; }

		}; nik_ce auto _not_ = U_arg_boolean<Boolean::not_>;

	// and_:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::boolean, Boolean::and_, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... && vs); }

		}; nik_ce auto _and_ = U_arg_boolean<Boolean::and_>;

	// or_:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::boolean, Boolean::or_, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... || vs); }

		}; nik_ce auto _or_ = U_arg_boolean<Boolean::or_>;

	// implies:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::boolean, Boolean::implies, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return (!v1 || v2); }

		}; nik_ce auto _implies_ = U_arg_boolean<Boolean::implies>;

	// equivalent:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::boolean, Boolean::equivalent, filler...>
		{
			template<typename T1, typename T2>
			nik_ces auto result(T1 v1, T2 v2) { return ((!v1 || v2) && (v1 || !v2)); }

		}; nik_ce auto _equivalent_ = U_arg_boolean<Boolean::equivalent>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// number:

/***********************************************************************************************************************/

// comparison:

	// equal:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, Number::equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... == vs); }

		}; nik_ce auto _equal_ = U_arg_number<Number::equal>;

	// not_equal:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, Number::not_equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... != vs); }

		}; nik_ce auto _not_equal_ = U_arg_number<Number::not_equal>;

	// less_than:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, Number::less_than, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... < vs); }

		}; nik_ce auto _less_than_ = U_arg_number<Number::less_than>;

	// less_than_or_equal:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, Number::less_than_or_equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... <= vs); }

		}; nik_ce auto _less_than_or_equal_ = U_arg_number<Number::less_than_or_equal>;

	// greater_than:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, Number::greater_than, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... > vs); }

		}; nik_ce auto _greater_than_ = U_arg_number<Number::greater_than>;

	// greater_than_or_equal:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, Number::greater_than_or_equal, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... >= vs); }

		}; nik_ce auto _greater_than_or_equal_ = U_arg_number<Number::greater_than_or_equal>;

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
		struct T_grammar<Shape::argument, Pattern::number, Number::add, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... + vs); }

		}; nik_ce auto _add_ = U_arg_number<Number::add>;

	// subtract:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, Number::subtract, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... - vs); }

		}; nik_ce auto _subtract_ = U_arg_number<Number::subtract>;

	// multiply:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, Number::multiply, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... * vs); }

		}; nik_ce auto _multiply_ = U_arg_number<Number::multiply>;

	// divide:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, Number::divide, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... / vs); }

		}; nik_ce auto _divide_ = U_arg_number<Number::divide>;

	// modulo:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::number, Number::modulo, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return (... % vs); }

		}; nik_ce auto _modulo_ = U_arg_number<Number::modulo>;

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

// pointer:

/***********************************************************************************************************************/

	// nothing yet.

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// reference:

/***********************************************************************************************************************/

	// nothing yet.

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array:

/***********************************************************************************************************************/

// meta:

	// is:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, Array::is, filler...>
		{
			template<typename T>         nik_ces auto result(T)       { return false; }
			template<typename T, auto S> nik_ces auto result(T(&)[S]) { return true; }

		}; nik_ce auto _is_array_ = U_arg_array<Array::is>;

	// type:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, Array::type, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(T(&)[S]) { return U_store_T<T>; }

		}; nik_ce auto _array_type_ = U_arg_array<Array::type>;

	// size:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, Array::size, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(T(&)[S]) { return S; }

		}; nik_ce auto _array_size_ = U_arg_array<Array::size>;

/***********************************************************************************************************************/

// basis:

	// begin:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, Array::begin, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(T(&a)[S]) { return a; }

		}; nik_ce auto _array_begin_ = U_arg_array<Array::begin>;

	// last:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, Array::last, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(T(&a)[S]) { return a + (S - 1); }

		}; nik_ce auto _array_last_ = U_arg_array<Array::last>;

	// end:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, Array::end, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(T(&a)[S]) { return a + S; }

		}; nik_ce auto _array_end_ = U_arg_array<Array::end>;

	// sift:

	//	template<typename Type, auto p, auto Arr, auto Leng, auto... Is>
	//	nik_ces auto sift(nik_vp(indices)(T_pack_Vs<Is...>*))
	//	{
	//		nik_ce auto Size	= Leng + 1;
	//		nik_ce auto arr		= apply<Type, Size, IteratorModule::Sift, Leng, p>(Arr);
	//		nik_ce auto leng	= arr.value[Leng]; // [0] ?

	//		if nik_ce (leng != sizeof...(Is)) return arr;
	//		else return array<Type, arr.value[Is]...>;
	//	}

/***********************************************************************************************************************/

// 2^N:

	// log floor:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::array, Array::log_floor, filler...>
		{
			nik_ces auto array_end = T_store_U<_array_end_>::result(array_2_N);

			nik_ces gkey_type result(gcindex_type n)
			{
				gcindex_type *k = array_end;

				while (--k != array_2_N) if (*k <= n) break;

				return k - array_2_N;
			}

		}; nik_ce auto _log_floor_ = U_arg_array<Array::log_floor>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// function:

/***********************************************************************************************************************/

	// nothing yet.

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sequence:

/***********************************************************************************************************************/

// meta:

	// is:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::sequence, Sequence::is, filler...>
		{
			template<typename T>         nik_ces auto result(T)                      { return false; }
			template<typename T, auto S> nik_ces auto result(const sequence<T, S> &) { return true; }

		}; nik_ce auto _is_sequence_ = U_arg_sequence<Sequence::is>;

	// type:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::sequence, Sequence::type, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(const sequence<T, S> &) { return U_store_T<T>; }

		}; nik_ce auto _sequence_type_ = U_arg_sequence<Sequence::type>;

	// size:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::sequence, Sequence::size, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(const sequence<T, S> &) { return S; }

		}; nik_ce auto _sequence_size_ = U_arg_sequence<Sequence::size>;

/***********************************************************************************************************************/

// basis:

	// cons:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::sequence, Sequence::to_sequence, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return sequence({vs...}); }

		}; nik_ce auto _to_sequence_ = U_arg_sequence<Sequence::to_sequence>;

	// begin:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::sequence, Sequence::begin, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(sequence<T, S> & s) { return s.value; }

			template<typename T, auto S>
			nik_ces auto result(const sequence<T, S> & s) { return s.value; }

		}; nik_ce auto _sequence_begin_ = U_arg_sequence<Sequence::begin>;

	// last:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::sequence, Sequence::last, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(sequence<T, S> & s) { return s.value + (S - 1); }

			template<typename T, auto S>
			nik_ces auto result(const sequence<T, S> & s) { return s.value + (S - 1); }

		}; nik_ce auto _sequence_last_ = U_arg_sequence<Sequence::last>;

	// end:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::sequence, Sequence::end, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(sequence<T, S> & s) { return s + S; }

			template<typename T, auto S>
			nik_ces auto result(const sequence<T, S> & s) { return s + S; }

		}; nik_ce auto _sequence_end_ = U_arg_sequence<Sequence::end>;

	// apply:

		template<auto U, auto S, auto f>
		struct T_grammar<Shape::argument, Pattern::sequence, Sequence::apply, U, S, f>
		{
			using T = T_store_U<U>;
			using F = T_store_U<f>;

			template<typename In, typename End, typename... Ins>
			nik_ces auto result(In in, End end, Ins... ins)
			{
				sequence<T, S> s{};

				F::template result<T*, In, End, Ins...>(s.value, in, end, ins...);

				return s;
			}

		}; template<auto U, auto S, auto f>
			nik_ce auto _sequence_apply_ = U_arg_sequence<Sequence::apply, U, S, f>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

/***********************************************************************************************************************/

// meta:

	// is:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::tuple, Tuple::is, filler...>
		{
			template<typename T>     nik_ces auto result(T)                    { return false; }
			template<typename... Ts> nik_ces auto result(const tuple<Ts...> &) { return true; }

		}; nik_ce auto _is_tuple_ = U_arg_tuple<Tuple::is>;

	// type:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::tuple, Tuple::type, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(const tuple<Ts...> &) { return U_pack_Ts<Ts...>; }

		}; nik_ce auto _tuple_type_ = U_arg_tuple<Tuple::type>;

	// size:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::tuple, Tuple::size, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(const tuple<Ts...> &) { return sizeof...(Ts); }

		}; nik_ce auto _tuple_size_ = U_arg_tuple<Tuple::size>;

/***********************************************************************************************************************/

// basis:

	// tuple:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::tuple, Tuple::to_tuple, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return tuple<Ts...>(vs...); }

		}; nik_ce auto _to_tuple_ = U_arg_tuple<Tuple::to_tuple>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// identity:

/***********************************************************************************************************************/

	// nothing yet.

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

