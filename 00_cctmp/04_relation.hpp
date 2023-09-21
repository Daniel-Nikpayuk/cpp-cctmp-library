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

		public:

			nik_ce proto_sequence() : initial{} { }

			template<typename T, auto N>
			nik_ce proto_sequence(const T (&s)[N]) :
				initial{} { apply<_subarray_copy_>(initial, s, s + N); }

			nik_ce proto_sequence(const proto_sequence & s) :
				initial{} { apply<_subarray_copy_>(initial, s.initial, s.initial + Size); }

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

			nik_ce ce_sequence() : base{}, terminal{} { }

			template<auto N>
			nik_ce ce_sequence(ctype (&s)[N]) :
				base{}, terminal{N}
					{ apply<_subarray_copy_>(base::initial, s, s + N); }

			nik_ce ce_sequence(const ce_sequence & s) :
				base{}, terminal{s.size()}
					{ apply<_subarray_copy_>(base::initial, s.cbegin(), s.cend()); }

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

			nik_ce sequence() : base{}, terminal{base::initial} { }

			template<auto N>
			nik_ce sequence(ctype (&s)[N]) :
				base{}, terminal{base::initial + N}
					{ apply<_subarray_copy_>(base::initial, s, s + N); }

			nik_ce sequence(const sequence & s) :
				base{}, terminal{base::initial + s.size()}
					{ apply<_subarray_copy_>(base::initial, s.cbegin(), s.cend()); }

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

		nik_ce table(const TU0 &, const TU1 &, const Pairs &... ps) : s0{{ps.v0...}}, s1{{ps.v1...}} { }

		nik_ce const T1 & lookup(const T0 & v0, const T1 & v1) const
		{
			auto i = s0.citerate().find(v0);

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
		nik_ce const T1 & slookup(const T & v, const T1 & v1) const
		{
			auto i = s0.citerate().template find<T const&>(v);

			if (i.is_end()) return v1;
			else return s1[i.left_size()];
		}

		template<typename T>
		nik_ce const T0 & srlookup(const T & v, const T0 & v0) const
		{
			auto i = s1.citerate().template find<T const&>(v);

			if (i.is_end()) return v0;
			else return s0[i.left_size()];
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp
