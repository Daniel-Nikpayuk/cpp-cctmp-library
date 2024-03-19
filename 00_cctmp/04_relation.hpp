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

// list model:

/***********************************************************************************************************************/

// interface:

	template<typename SizeType, SizeType Size>
	class T_list_model
	{
		public:

			using size_type			= SizeType;
			using list_type			= size_type;

			using csize_type		= size_type const;
			using clist_type		= list_type const;

		protected:

			nik_ces size_type length	= Size;
			nik_ces list_type null		= length;

			struct Pair { enum : size_type { car, cdr, dimension }; };

			size_type array[length];
			size_type free;

		public:

			nik_ce T_list_model() : array{}, free{length} { }

		protected:

			// free:

				nik_ce void clear() { free = length; }
				nik_ce auto allocate(csize_type s) { return (free -= s); }

		public:

			// array:

				nik_ce auto cbegin () const { return array; }
				nik_ce auto cend   () const { return array + length; }

				nik_ce auto get_value(csize_type p, csize_type n) const { return *(array + p + n); }
				nik_ce void set_value(csize_type p, csize_type n, csize_type v) { *(array + p + n) = v; }

			// list:

				nik_ce bool is_null  (clist_type l) const { return (l == null); }
				nik_ce bool not_null (clist_type l) const { return (l != null); }

				nik_ce bool is_model  (clist_type l) const { return (l == 0); }
				nik_ce bool not_model (clist_type l) const { return (l != 0); }

				nik_ce auto null_list() const { return null; }

				nik_ce auto car(clist_type l) const { return get_value(l, Pair::car); }
				nik_ce auto cdr(clist_type l) const { return get_value(l, Pair::cdr); }

				nik_ce auto cons(csize_type p, clist_type l)
				{
					size_type nl = allocate(Pair::dimension);

					set_value(nl, Pair::car, p);
					set_value(nl, Pair::cdr, l);

					return nl;
				}

				template<typename In, typename End>
				nik_ce auto cons(In in, End end, clist_type l)
				{
					size_type p  = allocate(end - in);
					size_type nl = cons(p, l);
					size_type k  = 0;

					while (in != end) set_value(p, k++, *in++);

					return nl;
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// stack:

/***********************************************************************************************************************/

// generic:

	template<typename SizeType, SizeType Size>
	class T_stack : public T_list_model<SizeType, Size>
	{
		public:

			using base		= T_list_model<SizeType, Size>;
			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;
			using Pair		= typename base::Pair;

		protected:

			size_type current;

		public:

			nik_ce T_stack() : base{}, current{base::null} { }

		protected:

			nik_ce auto release(csize_type s) { return (base::free += s); }

		public:

			nik_ce bool is_empty  () const { return base::is_null(current); }
			nik_ce bool not_empty () const { return base::not_null(current); }

			nik_ce bool is_full   () const { return base::is_model(current); }
			nik_ce bool not_full  () const { return base::not_model(current); }

			nik_ce csize_type content() const { return base::car(current); }

			nik_ce csize_type cbegin () const { return current; }
			nik_ce csize_type cend   () const { return base::null; }

			nik_ce void push(csize_type s) { current = base::cons(base::allocate(s), current); }

			template<typename In, typename End>
			nik_ce void push(In in, End end) { current = base::cons(in, end, current); }

			nik_ce void pop(csize_type s)
			{
				current = base::cdr(current);
				release(Pair::dimension + s);
			}

			nik_ce void clear()
			{
				current = base::null;
				base::clear();
			}
	};

/***********************************************************************************************************************/

// multi(dimensional):

	template<typename SizeType, SizeType EntrySize, SizeType Size>
	class multistack : public T_stack<SizeType, (EntrySize + 2) * Size>
	{
		protected:

			nik_ces SizeType entry_size		= EntrySize;
			nik_ces SizeType length			= (entry_size + 2) * Size;

		public:

			using base				= T_stack<SizeType, length>;
			using size_type				= typename base::size_type;
			using csize_type			= typename base::csize_type;
			using Pair				= typename base::Pair;

			using entry_type			= literal<size_type, size_type>;
			using centry_type			= entry_type const;
			using centry_ref			= centry_type &;

		protected:

			csize_type zero_array[entry_size];
			centry_type zero_entry;

		public:

			nik_ce multistack() :
				base{}, zero_array{},
				zero_entry{zero_array, zero_array + entry_size}
					{ }

			// value:

				nik_ce auto entry_begin () const { return base::array + base::content(); }
				nik_ce auto entry_end   () const { return entry_begin() + entry_size; }
				nik_ce auto entry       () const { return centry_type{entry_begin(), entry_end()}; }

			// push:

				nik_ce void fast_push(csize_type (&ent)[entry_size])
					{ base::push(ent, ent + entry_size); }

				nik_ce bool push(csize_type (&ent)[entry_size])
				{
					bool success = base::not_full();

					if (success) fast_push(ent);

					return success;
				}

			// pop:

				nik_ce centry_type fast_pop()
				{
					centry_type ent = entry();

					base::pop(entry_size);

					return ent;
				}

				nik_ce centry_type pop()
				{
					if (base::is_empty()) return zero_entry;
					else                  return fast_pop();
				}
	};

/***********************************************************************************************************************/

// unit:

	template<typename SizeType, SizeType Size>
	struct unit_stack : public multistack<SizeType, 1, Size>
	{
		using base       = multistack<SizeType, 1, Size>;
		using size_type  = typename base::size_type;
		using csize_type = typename base::csize_type;

		nik_ce unit_stack() : base{} { }

		nik_ce size_type & value() { return base::array[base::content()]; }
		nik_ce csize_type cvalue() const { return base::array[base::content()]; }

		nik_ce csize_type pop() { return base::pop()[0]; }

		nik_ce bool push(csize_type v)
			{ return base::push({v}); }
	};

/***********************************************************************************************************************/

// pair:

	template<typename SizeType, SizeType Size>
	struct pair_stack : public multistack<SizeType, 2, Size>
	{
		using base       = multistack<SizeType, 2, Size>;
		using csize_type = typename base::csize_type;

		nik_ce pair_stack() : base{} { }

		nik_ce bool push(csize_type v0, csize_type v1)
			{ return base::push({v0, v1}); }
	};

/***********************************************************************************************************************/

// triple:

	template<typename SizeType, SizeType Size>
	struct triple_stack : public multistack<SizeType, 3, Size>
	{
		using base       = multistack<SizeType, 3, Size>;
		using csize_type = typename base::csize_type;

		nik_ce triple_stack() : base{} { }

		nik_ce bool push(csize_type v0, csize_type v1, csize_type v2)
			{ return base::push({v0, v1, v2}); }
	};

/***********************************************************************************************************************/

// quad(ruple):

	template<typename SizeType, SizeType Size>
	struct quad_stack : public multistack<SizeType, 4, Size>
	{
		using base       = multistack<SizeType, 4, Size>;
		using csize_type = typename base::csize_type;

		nik_ce quad_stack() : base{} { }

		nik_ce bool push(csize_type v0, csize_type v1, csize_type v2, csize_type v3)
			{ return base::push({v0, v1, v2, v3}); }
	};

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
				nik_ce ctype_ptr origin () const { return initial; }

				nik_ce auto left_size (ctype_cptr i) const { return i - initial; }

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

			//	nik_ce bool is_empty  () const { return (base::initial == cend()); }
			//	nik_ce bool not_empty () const { return (base::initial != cend()); }
				nik_ce bool is_empty  () const { return (terminal == 0); }
				nik_ce bool not_empty () const { return (terminal != 0); }

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

// (controller) instructions:

	struct Instr { enum : gkey_type { name = 0, note, pos, num, next, dimension }; };

	// type:

		using instr_type = sequence<gindex_type, static_cast<gindex_type>(Instr::dimension)>;

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

