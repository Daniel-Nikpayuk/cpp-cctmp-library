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

// relation:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// dependencies:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// segment:

/***********************************************************************************************************************/

	struct T_interpreter_segment
	{
		nik_ces auto sH0 = U_pack_Vs<H_id>;
		nik_ces auto  H0 = U_pack_Vs<_car_, sH0>;

		template<auto n>
		nik_ces auto contr = controller
		<
			instruction < IN::call , IT::praxis , PN::segment , n >,
			instruction < IN::halt , IT::eval                     >
		>;

		template<auto d, auto n, auto m = _zero>
		nik_ces auto result = T_interpreter_start::template result<d, contr<n>, m>(H0);
	};

/***********************************************************************************************************************/

// params (syntactic sugar):

	nik_ce auto _dpar_at_		= U_custom_T<T_interpreter_params< IT::back   , _car_           >>;
	nik_ce auto _dpar_left_		= U_custom_T<T_interpreter_params< IT::front  , _list_<>        >>;
	nik_ce auto _dpar_right_	= U_custom_T<T_interpreter_params< IT::back   , _list_<>        >>;
	nik_ce auto _dpar_replace_	= U_custom_T<T_interpreter_params< IT::mutate , _list_<> , _one >>;
	nik_ce auto _dpar_segment_	= U_custom_T<T_interpreter_segment>;

	nik_ce auto _par_at_		= ID::template with_initial_depth< _dpar_at_      >;
	nik_ce auto _par_left_		= ID::template with_initial_depth< _dpar_left_    >;
	nik_ce auto _par_right_		= ID::template with_initial_depth< _dpar_right_   >;
	nik_ce auto _par_replace_	= ID::template with_initial_depth< _dpar_replace_ >;
	nik_ce auto _par_segment_	= ID::template with_initial_depth< _dpar_segment_ >;

/***********************************************************************************************************************/

// type at:

	template<auto n, typename... Ts>
	using type_at = T_store_U<eval<_par_at_, n, U_store_T<Ts>...>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sequence:

	// some methods might seem redundant given selectors and iterators,
	// but the intention here is construction, not selection/mutation.

/***********************************************************************************************************************/

// proto:

	template<typename Type, auto Size>
	class proto_sequence
	{
		public:

			using iterator_type		= iterator<Type>;
			using iterator_ctype		= iterator_type const;

			using citerator_type		= citerator<Type>;
			using citerator_ctype		= citerator_type const;

			using cselector_type		= typename iterator_type::cselector_type;
			using cselector_ctype		= typename iterator_type::cselector_ctype;
			using cselector_ctype_ptr	= typename iterator_type::cselector_ctype_ptr;
			using cselector_ctype_cptr	= typename iterator_type::cselector_ctype_cptr;

			using selector_type		= selector<Type>;
			using selector_ctype		= selector_type const;

			using type			= typename iterator_type::type;
			using type_ptr			= typename iterator_type::type_ptr;
			using type_ref			= typename iterator_type::type_ref;
			using type_cptr			= typename iterator_type::type_cptr;

			using ctype			= typename iterator_type::ctype;
			using ctype_ptr			= typename iterator_type::ctype_ptr;
			using ctype_cptr		= typename iterator_type::ctype_cptr;
			using ctype_ref			= typename iterator_type::ctype_ref;

			using size_type			= decltype(Size);
			using csize_type		= size_type const;

		protected:

			type initial[Size];

			nik_ce void copy(type_ptr k, ctype_ptr b, ctype_cptr e) { while (b != e) *k++ = *b++; }

		public:

			template<typename... Ts>
			nik_ce proto_sequence(const Ts &... vs) : initial{type(vs)...} { }

			// immutable:

				nik_ce size_type length () const { return Size; }

				nik_ce auto left_size  (ctype_cptr i) const { return i - initial; }

				nik_ce ctype_ptr cbegin () const { return initial; }

				nik_ce ctype_ref operator [] (csize_type pos) const { return initial[pos]; }

			// mutable:

				nik_ce type_ptr begin () { return initial; }

				nik_ce type_ref operator [] (csize_type pos) { return initial[pos]; }
	};

/***********************************************************************************************************************/

// ce:

	template<typename Type, auto Size>
	class ce_sequence : public proto_sequence<Type, Size>
	{
		protected:

			using base			= proto_sequence<Type, Size>;

		public:

			using iterator_type		= typename base::iterator_type;
			using iterator_ctype		= typename base::iterator_ctype;

			using citerator_type		= typename base::citerator_type;
			using citerator_ctype		= typename base::citerator_ctype;

			using cselector_type		= typename base::cselector_type;
			using cselector_ctype		= typename base::cselector_ctype;
			using cselector_ctype_ptr	= typename base::cselector_ctype_ptr;
			using cselector_ctype_cptr	= typename base::cselector_ctype_cptr;

			using selector_type		= typename base::selector_type;
			using selector_ctype		= typename base::selector_ctype;

			using type			= typename base::type;
			using type_ptr			= typename base::type_ptr;
			using type_ref			= typename base::type_ref;
			using type_cptr			= typename base::type_cptr;

			using ctype			= typename base::ctype;
			using ctype_ptr			= typename base::ctype_ptr;
			using ctype_cptr		= typename base::ctype_cptr;
			using ctype_ref			= typename base::ctype_ref;

			using size_type			= typename base::size_type;
			using csize_type		= typename base::csize_type;

		protected:

			size_type terminal;

		public:

			template<typename... Ts>
			nik_ce ce_sequence(const Ts &... vs) : base{vs...}, terminal{sizeof...(Ts)} { }

			nik_ce ce_sequence(const ce_sequence & s) :
				base{}, terminal{s.size()} { base::copy(base::initial, s.cbegin(), s.cend()); }

			// immutable:

				nik_ce size_type max  () const { return terminal - 1; }
				nik_ce size_type size () const { return terminal; }

				nik_ce bool is_empty  () const { return (base::initial == cend()); }
				nik_ce bool not_empty () const { return (base::initial != cend()); }

				nik_ce auto right_size (ctype_cptr i) const { return cend() - i; }

				nik_ce ctype_ptr clast  () const { return base::initial + max(); }
				nik_ce ctype_ptr cend   () const { return base::initial + terminal; }

				nik_ce cselector_type cselect(csize_type lnum, csize_type rnum) const
					{ return cselector_type{base::initial + lnum, base::initial + (terminal - rnum)}; }
				nik_ce cselector_type cselect() const { return cselect(0, 0); }

				nik_ce citerator_type citerate(csize_type lnum, csize_type rnum) const
					{ return citerator_type{base::initial + lnum, base::initial + (terminal - rnum)}; }
				nik_ce citerator_type citerate() const { return citerate(0, 0); }

			// mutable:

				nik_ce void clear() { terminal = _zero; }
				nik_ce void fullsize() { terminal = Size; }
				nik_ce void upsize(csize_type num = 1) { terminal += num; }
				nik_ce void downsize(csize_type num = 1) { terminal -= num; }
				nik_ce void push(ctype_ref v) { *(base::initial + terminal++) = v; }
				nik_ce type pop() { return *(base::initial + --terminal); }

				nik_ce type_ptr last () { return base::initial + max(); }
				nik_ce type_ptr end  () { return base::initial + terminal; }

				nik_ce selector_type select(csize_type lnum, csize_type rnum)
					{ return selector_type{base::initial + lnum, base::initial + (terminal - rnum)}; }
				nik_ce selector_type select() { return select(0, 0); }

				nik_ce iterator_type iterate(csize_type lnum, csize_type rnum)
					{ return iterator_type{base::initial + lnum, base::initial + (terminal - rnum)}; }
				nik_ce iterator_type iterate() { return iterate(0, 0); }

			// unite:

				nik_ce void unite(ctype_ref v)
					{ if (cselect().find(v).is_empty()) push(v); }

				nik_ce void unite(ctype_ptr b, ctype_cptr e) { while (b != e) unite(*b++); }
				nik_ce void unite(cselector_ctype & s) { unite(s.cbegin(), s.cend()); }
				nik_ce void unite(citerator_ctype & i) { unite(i.cbegin(), i.cend()); }
	};

/***********************************************************************************************************************/

// interface:

	template<typename Type, auto Size>
	class sequence : public proto_sequence<Type, Size>
	{
		protected:

			using base			= proto_sequence<Type, Size>;

		public:

			using iterator_type		= typename base::iterator_type;
			using iterator_ctype		= typename base::iterator_ctype;

			using citerator_type		= typename base::citerator_type;
			using citerator_ctype		= typename base::citerator_ctype;

			using cselector_type		= typename base::cselector_type;
			using cselector_ctype		= typename base::cselector_ctype;
			using cselector_ctype_ptr	= typename base::cselector_ctype_ptr;
			using cselector_ctype_cptr	= typename base::cselector_ctype_cptr;

			using selector_type		= typename base::selector_type;
			using selector_ctype		= typename base::selector_ctype;

			using type			= typename base::type;
			using type_ptr			= typename base::type_ptr;
			using type_ref			= typename base::type_ref;
			using type_cptr			= typename base::type_cptr;

			using ctype			= typename base::ctype;
			using ctype_ptr			= typename base::ctype_ptr;
			using ctype_cptr		= typename base::ctype_cptr;
			using ctype_ref			= typename base::ctype_ref;

			using size_type			= typename base::size_type;
			using csize_type		= typename base::csize_type;

		protected:

			type_ptr terminal;

		public:

			template<typename... Ts>
			nik_ce sequence(const Ts &... vs) : base{vs...}, terminal{base::initial + sizeof...(Ts)} { }

			nik_ce sequence(const sequence & s) :
				base{}, terminal{base::initial + s.size()}
					{ base::copy(base::initial, s.cbegin(), s.cend()); }

			// immutable:

				nik_ce size_type size () const { return terminal - base::initial; }
				nik_ce size_type max  () const { return size() - 1; }

				nik_ce bool is_empty  () const { return (base::initial == terminal); }
				nik_ce bool not_empty () const { return (base::initial != terminal); }

				nik_ce auto right_size (ctype_cptr i) const { return terminal - i; }

				nik_ce ctype_ptr clast () const { return terminal - 1; }
				nik_ce ctype_ptr cend  () const { return terminal; }

				nik_ce cselector_type cselect(csize_type lnum, csize_type rnum) const
					{ return cselector_type{base::initial + lnum, terminal - rnum}; }
				nik_ce cselector_type cselect() const { return cselect(0, 0); }

				nik_ce citerator_type citerate(csize_type lnum, csize_type rnum) const
					{ return citerator_type{base::initial + lnum, terminal - rnum}; }
				nik_ce citerator_type citerate() const { return citerate(0, 0); }

			// mutable:

				nik_ce void clear() { terminal = base::initial; }
				nik_ce void fullsize() { terminal = base::initial + Size; }
				nik_ce void upsize(csize_type num = 1) { terminal += num; }
				nik_ce void downsize(csize_type num = 1) { terminal -= num; }
				nik_ce void push(ctype_ref v) { *terminal++ = v; }
				nik_ce type pop() { return *--terminal; }

				nik_ce type_ptr last () { return terminal - 1; }
				nik_ce type_ptr end  () { return terminal; }

				nik_ce selector_type select(csize_type lnum, csize_type rnum)
					{ return selector_type{base::initial + lnum, terminal - rnum}; }
				nik_ce selector_type select() { return select(0, 0); }

				nik_ce iterator_type iterate(csize_type lnum, csize_type rnum)
					{ return iterator_type{base::initial + lnum, terminal - rnum}; }
				nik_ce iterator_type iterate() { return iterate(0, 0); }

			// unite:

				nik_ce void unite(ctype_ref v)
					{ if (cselect().find(v).is_empty()) push(v); }

				nik_ce void unite(ctype_ptr b, ctype_cptr e) { while (b != e) unite(*b++); }
				nik_ce void unite(cselector_ctype & s) { unite(s.cbegin(), s.cend()); }
				nik_ce void unite(citerator_ctype & i) { unite(i.cbegin(), i.cend()); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pair:

/***********************************************************************************************************************/

// interface:

	template<typename T0, typename T1>
	struct pair
	{
		T0 v0;
		T1 v1;

		nik_ce pair() : v0{}, v1{} { }
		nik_ce pair(const T0 & _v0, const T1 & _v1) : v0{_v0}, v1{_v1} { }

		nik_ce bool operator == (const pair & p) const { return (p.v0 == v0) && (p.v1 == v1); }
		nik_ce bool operator != (const pair & p) const { return (p.v0 != v0) || (p.v1 != v1); }
	};

/***********************************************************************************************************************/

// static:

	// car:

		template<auto static_pair>
		struct T_static_car
		{
			nik_ces auto & value = member_value_U<static_pair>.v0;
			using type           = modify_type<_from_reference_, decltype(value)>;

		}; template<auto static_pair>
			nik_ce auto _static_car_ = U_store_T<T_static_car<static_pair>>;

	// cdr:

		template<auto static_pair>
		struct T_static_cdr
		{
			nik_ces auto & value = member_value_U<static_pair>.v1;
			using type           = modify_type<_from_reference_, decltype(value)>;

		}; template<auto static_pair>
			nik_ce auto _static_cdr_ = U_store_T<T_static_cdr<static_pair>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// table:

/***********************************************************************************************************************/

// interface:

	template<typename TU0, typename TU1, typename... Pairs>
	struct table
	{
		using T0		= T_restore_T<TU0>;
		using T1		= T_restore_T<TU1>;

		nik_ces auto length	= sizeof...(Pairs);

		sequence<T0, length> s0;
		sequence<T1, length> s1;

		nik_ce table(const TU0 &, const TU1 &, const Pairs &... ps) : s0{ps.v0...}, s1{ps.v1...} { }

		nik_ce const T1 & lookup(const T0 & v0, const T1 & v1) const
		{
			auto i = s0.citerate().find(v0);

			if (i.is_end()) return v1;
			else return s1[i.left_size()];
		}

		template<typename T>
		nik_ce const T1 & lookup(const T & v, const T1 & v1) const
		{
			auto i = s0.citerate().template find<T const&>(v);

			if (i.is_end()) return v1;
			else return s1[i.left_size()];
		}

		nik_ce const T0 & rlookup(const T1 & v1, const T0 & v0) const
		{
			auto i = s1.citerate().find(v1);

			if (i.is_end()) return v0;
			else return s0[i.left_size()];
		}

		template<typename T>
		nik_ce const T0 & rlookup(const T & v, const T0 & v0) const
		{
			auto i = s1.citerate().template find<T const&>(v);

			if (i.is_end()) return v0;
			else return s0[i.left_size()];
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

	template<typename...> struct tuple;

/***********************************************************************************************************************/

// value:

	template<typename T, auto>
	struct MITupleValue
	{
		T v;

		nik_ce MITupleValue() : v{} { }
		nik_ce MITupleValue(const T & _v) : v{_v} { }
	};

/***********************************************************************************************************************/

// multiple inheritance:

	template<typename...> struct MITuple;

	template<template<auto...> typename B, auto... Is, typename... Ts>
	class MITuple<void(*const)(B<Is...>*), Ts...> : public MITupleValue<Ts, gindex_type{Is}>...
	{
		friend class tuple<Ts...>;

		public:

			nik_ce MITuple() { }
			nik_ce MITuple(Ts... vs) : MITupleValue<Ts, gindex_type{Is}>{vs}... { }

		protected:

			template<auto n>
			nik_ce const auto & value() const
			{
				using T		= type_at<n, Ts...>;
				using BasePtr	= MITupleValue<T, gindex_type{n}> const*;

				return static_cast<BasePtr>(this)->v;
			}
	};

/***********************************************************************************************************************/

// interface:

	template<typename... Ts>
	class tuple
	{
		using mi_type = MITuple<decltype(eval<_par_segment_, sizeof...(Ts)>), Ts...>;

		protected:

			mi_type mi;

		public:

			nik_ce tuple() { }
			nik_ce tuple(Ts... vs) : mi{vs...} { }

			template<auto n>
			nik_ce const auto & cvalue() const { return mi.template value<n>(); }

			template<auto n>
			nik_ce auto & value()
			{
				auto & v = mi.template value<n>();
				using CT = typename remove_reference<decltype(v)>::result;
				using  T = typename remove_const<CT>::result;

				return (T&) v;
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// binding:

/***********************************************************************************************************************/

	template<typename KeyType, typename ValueType>
	class binding
	{
		template<typename, typename...> friend class frame;

		public:

			using strlit_type	= string_literal<KeyType>;
			using value_type	= ValueType;

		protected:

			strlit_type strlit;
			value_type value;

		public:

			template<auto N>
			nik_ce binding(const KeyType (&s)[N], const ValueType & v) : strlit{s}, value{v} { }

			nik_ce binding(const strlit_type & s, const value_type & v) : strlit{s}, value{v} { }

			nik_ce const auto & key() const { return strlit; }
			nik_ce const auto & map() const { return value; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// frame:

/***********************************************************************************************************************/

	template<typename CharType, typename... Bindings>
	class frame
	{
		public:

			using char_type		= T_restore_T<CharType>;
			using strlit_type	= string_literal<char_type>;
			using sequence_type	= ce_sequence<strlit_type, sizeof...(Bindings)>;
			using tuple_type	= tuple<typename Bindings::value_type...>;

		protected:

			sequence_type strlit;
			tuple_type value;

		public:

			nik_ce frame(const CharType &, const Bindings &... bs) :
				strlit{bs.strlit...}, value{bs.value...} { }

			template<typename T>
			nik_ce auto contains(const T & v) const { return strlit.citerate().find(v); }

			template<auto key>
			nik_ce auto map() const { return value.template cvalue<key>(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// generic:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// pair:

/***********************************************************************************************************************/

// operators:

	struct ArgPair
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			is , type , 		// meta
			dimension
		};
	};

/***********************************************************************************************************************/

// meta:

	// is:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::pair, ArgPair::is, filler...>
		{
			template<typename T> nik_ces auto result(T) { return false; }
			template<typename T0, typename T1> nik_ces auto result(const pair<T0, T1> &) { return true; }

		}; nik_ce auto _is_pair_ = U_arg_pair<ArgPair::is>;

	// type:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::pair, ArgPair::type, filler...>
		{
			template<typename T0, typename T1>
			nik_ces auto result(const pair<T0, T1> &) { return U_pack_Ts<T0, T1>; }

		}; nik_ce auto _pair_type_ = U_arg_pair<ArgPair::type>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sequence:

/***********************************************************************************************************************/

// operators:

	struct ArgSequence
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			is , type , length , // meta
			dimension
		};
	};

/***********************************************************************************************************************/

// meta:

	// is:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::sequence, ArgSequence::is, filler...>
		{
			template<typename T> nik_ces auto result(T) { return false; }
			template<typename T, auto S> nik_ces auto result(const sequence<T, S> &) { return true; }

		}; nik_ce auto _is_sequence_ = U_arg_sequence<ArgSequence::is>;

	// type:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::sequence, ArgSequence::type, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(const sequence<T, S> &) { return U_store_T<T>; }

		}; nik_ce auto _sequence_type_ = U_arg_sequence<ArgSequence::type>;

	// length:

		template<auto... filler>
		struct T_grammar<Shape::argument, Pattern::sequence, ArgSequence::length, filler...>
		{
			template<typename T, auto S>
			nik_ces auto result(const sequence<T, S> &) { return S; }

		}; nik_ce auto _sequence_length_ = U_arg_sequence<ArgSequence::length>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

