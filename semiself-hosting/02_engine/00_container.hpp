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

// container:

namespace engine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cctmp:

	template<typename T>
	nik_ce auto U_store_T						= cctmp::U_store_T<T>;

	template<typename T>
	using T_restore_T						= cctmp::T_restore_T<T>;

	template<auto U>
	using T_store_U							= cctmp::T_store_U<U>;

	using gkey_type							= cctmp::gkey_type;
	using gindex_type						= cctmp::gindex_type;

	nik_ce auto U_gindex_type					= cctmp::U_gindex_type;

	nik_ce auto _empty_						= cctmp::_empty_;
	nik_ce auto _size_						= cctmp::_size_;

	template<auto n>
	nik_ce auto _at_						= cctmp::_at_<n>;

	template<auto n>
	nik_ce auto segment_						= cctmp::segment_<n>;

	using MachineIndex						= cctmp::MachineIndex;
	using MN							= cctmp::MN;
	using MT							= cctmp::MT;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// literal:

/***********************************************************************************************************************/

// interface:

	template<typename Type, typename SizeType>
	struct literal
	{
		using type		= Type;
		using ctype		= type const;
		using ctype_ptr		= ctype*;
		using ctype_cptr	= ctype_ptr const;
		using ctype_ref		= ctype&;

		using size_type		= SizeType;
		using csize_type	= size_type const;

		ctype_ptr start;
		ctype_ptr finish;

		nik_ces ctype empty[] = { };

		template<auto N>
		nik_ce literal(const Type (&s)[N]) : start{s}, finish{s + N} { }

		nik_ce literal() : start{empty}, finish{empty} { }
		nik_ce literal(ctype_cptr s, ctype_cptr f) : start{s}, finish{f} { }

		nik_ce csize_type size   () const { return finish - start; }
		nik_ce ctype_ptr  origin () const { return start; }

		nik_ce ctype_ptr cbegin () const { return start; }
		nik_ce ctype_ptr clast  () const { return finish - 1; }
		nik_ce ctype_ptr cend   () const { return finish; }

		nik_ce ctype_ref operator [] (csize_type pos) const { return start[pos]; }
	};

/***********************************************************************************************************************/

// string literal:

	template<typename Type, typename SizeType>
	struct string_literal : public literal<Type, SizeType>
	{
		using base		= literal<Type, SizeType>;

		using type		= typename base::type;
		using ctype		= typename base::ctype;
		using ctype_ptr		= typename base::ctype_ptr;
		using ctype_cptr	= typename base::ctype_cptr;
		using ctype_ref		= typename base::ctype_ref;

		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		template<auto N>
		nik_ce string_literal(const Type (&s)[N]) : base{s, s + (N-1)} { }

		nik_ce string_literal() : base{} { } // maybe.
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lambda tuple:

	template<gkey_type, auto...> struct T_lambda_tuple;

	template<auto Name, auto... Vs>
	nik_ce auto U_lambda_tuple = U_store_T<T_lambda_tuple<Name, Vs...>>;

/***********************************************************************************************************************/

// operators:

	struct LambdaTupleIndex
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			make , catenate , env_tuple ,
			dimension
		};
	};

	using LTI = LambdaTupleIndex;

/***********************************************************************************************************************/

// lambda tuple:

	// make:

		template<auto... filler>
		struct T_lambda_tuple<LTI::make, filler...>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				return [vs...](auto U, auto... xs)
				{
					using F = T_restore_T<decltype(U)>;

					return F::template result<decltype(xs)..., Ts...>(xs..., vs...);
				};
			}

		}; nik_ce auto _lambda_tuple_ = U_lambda_tuple<LTI::make>;

	// catenate:

		template<auto... filler>
		struct T_lambda_tuple<LTI::catenate, filler...>
		{
			template<typename LT, typename... Ts>
			nik_ces auto result(LT lt, Ts... vs) { return lt(_lambda_tuple_, vs...); }

		}; nik_ce auto _lambda_tuple_catenate_ = U_lambda_tuple<LTI::catenate>;

	// env tuple:

		template<auto U, auto... filler>
		struct T_lambda_tuple<LTI::env_tuple, U, filler...>
		{
			using size_type = T_store_U<U>;

			template<typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				using frame_type = cctmp::ctuple<size_type, segment_<sizeof...(Ts)>, Ts...      >;
				using env_type   = cctmp::ctuple<size_type, segment_<1            >, frame_type >;

				return env_type{frame_type{vs...}};
			}

		}; template<auto U>
			nik_ce auto _lambda_env_tuple_ = U_lambda_tuple<LTI::env_tuple, U>;

/***********************************************************************************************************************/

// message passing:

	struct LambdaTuple
	{
		template<        typename LT> nik_ces auto empty (LT lt) { return lt(_empty_); }
		template<        typename LT> nik_ces auto size  (LT lt) { return lt(_size_ ); }
		template<auto n, typename LT> nik_ces auto value (LT lt) { return lt(_at_<n>); }

		template<typename... Ts>
		nik_ces auto make(Ts... vs) { return T_store_U<_lambda_tuple_>::template result<Ts...>(vs...); }

		template<typename LT1, typename LT2>
		nik_ces auto catenate(LT1 lt1, LT2 lt2) { return lt1(_lambda_tuple_catenate_, lt2); }

		template<typename SizeType, typename LT>
		nik_ces auto env_tuple(LT lt) { return lt(_lambda_env_tuple_<U_store_T<SizeType>>); }
	};

/***********************************************************************************************************************/

// binding:

	template<typename SizeType, typename CharType, SizeType N, typename T>
	nik_ce auto binding(nik_avp(SizeType*), CharType (&variable)[N], T value)
	{
		using strlit_type = string_literal<CharType, SizeType>;

		return LambdaTuple::make(strlit_type{variable}, value);
	}

	// syntactic sugar:

		template<typename CharType, gindex_type N, typename T>
		nik_ce auto gbinding(CharType (&variable)[N], T value)
			{ return binding(U_gindex_type, variable, value); }

/***********************************************************************************************************************/

// frame:

	template<typename CharType, typename SizeType, typename... Bindings>
	nik_ce auto frame(nik_avp(CharType*), nik_avp(SizeType*), Bindings... bs)
	{
		using strlit_type   = string_literal<CharType, SizeType>;
		using variable_type = cctmp::sequence<strlit_type, SizeType, sizeof...(Bindings)>;

		variable_type variables;
		(variables.push(LambdaTuple::template value<0>(bs)), ...);

		auto values = LambdaTuple::make(LambdaTuple::template value<1>(bs)...);

		return LambdaTuple::make(variables, values);
	}

/***********************************************************************************************************************/

// instr:

	template<typename Type, typename SizeType>
	struct machine_instr : public cctmp::sequence<Type, SizeType, MachineIndex::dimension>
	{
		using Index 		= MachineIndex;
		using base 		= cctmp::sequence<Type, SizeType, Index::dimension>;

		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		nik_ce machine_instr() : base{} { }

		nik_ce void set(csize_type n, csize_type t, csize_type p, csize_type m)
		{
			base::initial[Index::name] = n;
			base::initial[Index::note] = t;
			base::initial[Index::pos ] = p;
			base::initial[Index::num ] = m;
		}
	};

/***********************************************************************************************************************/

// contr:

	template<typename Type, typename SizeType, SizeType Size>
	struct machine_contr : public cctmp::sequence<machine_instr<Type, SizeType>, SizeType, Size>
	{
		using instr_type	= machine_instr<Type, SizeType>;
		using base		= cctmp::sequence<instr_type, SizeType, Size>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		nik_ce machine_contr() : base{} { }

		nik_ce void push(csize_type n, csize_type t, csize_type p = 0, csize_type m = 0)
		{
			base::upsize();
			base::last()->set(n, t, p, m);
		}
	};

/***********************************************************************************************************************/

// source:

	template<typename SizeType, typename CharType, SizeType N, typename... Bindings>
	nik_ce auto source(const CharType (&s)[N], const Bindings &... bs)
	{
		using strlit_type       = string_literal<CharType, SizeType>;
		nik_ce auto U_char_type = U_store_T<CharType>;
		nik_ce auto U_size_type = U_store_T<SizeType>;

		return LambdaTuple::make(strlit_type{s}, frame(U_char_type, U_size_type, bs...));
	}

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
			using csize_type		= size_type const;

			using list_type			= size_type;
			using clist_type		= list_type const;

		protected:

			nik_ces size_type length	= Size;
			nik_ces list_type null		= length;

			struct Entry { enum : size_type { car, cdr, dimension }; };

			size_type array[length];
			size_type free;

		public:

			nik_ce T_list_model() : array{}, free{length} { }

		protected:

			// free:

				nik_ce void clear() { free = length; }

				nik_ce csize_type allocate(csize_type s = Entry::dimension)
					{ return (free -= s); }

		public:

			// array:

				nik_ce auto cbegin () const { return array; }
				nik_ce auto cend   () const { return array + length; }

				nik_ce csize_type get_value(csize_type p, csize_type n) const
					{ return array[p + n]; }

				nik_ce void set_value(csize_type p, csize_type n, csize_type v)
					{ array[p + n] = v; }

			// list:

				nik_ce const bool is_null  (clist_type l) const { return (l == null); }
				nik_ce const bool not_null (clist_type l) const { return (l != null); }

				nik_ce const bool is_model  (clist_type l) const { return (l == 0); }
				nik_ce const bool not_model (clist_type l) const { return (l != 0); }

				nik_ce clist_type null_list() const { return null; }

				nik_ce csize_type car(clist_type l) const { return get_value(l, Entry::car); }
				nik_ce csize_type cdr(clist_type l) const { return get_value(l, Entry::cdr); }

				nik_ce clist_type cons(csize_type v, clist_type l)
				{
					clist_type nl = allocate();

					set_value(nl, Entry::car, v);
					set_value(nl, Entry::cdr, l);

					return nl;
				}
	};

/***********************************************************************************************************************/

// stack:

	template<typename SizeType, SizeType Size>
	class T_stack : public T_list_model<SizeType, Size>
	{
		public:

			using base		= T_list_model<SizeType, Size>;
			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;
			using Entry		= typename base::Entry;

		protected:

			size_type current;

		public:

			nik_ce T_stack() : base{}, current{base::null} { }

		protected:

			nik_ce csize_type release(csize_type s = Entry::dimension)
				{ return (base::free += s); }

		public:

			nik_ce const bool is_empty  () const { return base::is_null(current); }
			nik_ce const bool not_empty () const { return base::not_null(current); }

			nik_ce const bool is_full   () const { return base::is_model(current); }
			nik_ce const bool not_full  () const { return base::not_model(current); }

			nik_ce csize_type content() const { return base::car(current); }

			nik_ce csize_type cbegin () const { return current; }
			nik_ce csize_type cend   () const { return base::null; }

			nik_ce void push(csize_type v) { current = base::cons(v, current); }

			nik_ce csize_type pop()
			{
				csize_type v = base::car(current);
				current      = base::cdr(current);

				release();

				return v;
			}

			nik_ce void clear()
			{
				current = base::null;
				base::clear();
			}
	};

/***********************************************************************************************************************/

// inhabit:

	template<typename SizeType>
	class T_inhabit : public T_stack<SizeType, 1> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace engine

