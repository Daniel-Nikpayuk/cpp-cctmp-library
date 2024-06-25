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

// grammar:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// store:

/***********************************************************************************************************************/

// T -> U:

	template<typename T> nik_ce void store(T) { }

	template<typename T> nik_ce auto U_store_T     = store<T*>;
	template<typename T> nik_ce auto U_store_T<T&> = store<T&>;

// U -> T:

	template<typename T> struct store_match                    { using result = T; };
	template<typename T> struct store_match<void(*const&)(T&)> { using result = T&; };
	template<typename T> struct store_match<void(*const&)(T*)> { using result = T; };

	template<typename T>
	using T_restore_T = typename store_match<T const&>::result;

	template<typename T>
	nik_ce auto U_restore_T = U_store_T<T_restore_T<T>>;

	template<auto U>
	using T_store_U = T_restore_T<decltype(U)>;

/***********************************************************************************************************************/

// constant:

	// void:

		nik_ce auto U_void = U_store_T<void>;

	// builtin:

		nik_ce auto U_bool = U_store_T<bool>;
		nik_ce auto U_char = U_store_T<char>;

	// unsigned:

		nik_ce auto U_unsigned_char			= U_store_T < unsigned char      >;
		nik_ce auto U_unsigned_short			= U_store_T < unsigned short     >;
		nik_ce auto U_unsigned_int			= U_store_T < unsigned int       >;
		nik_ce auto U_unsigned_long			= U_store_T < unsigned long      >;
		nik_ce auto U_unsigned_long_long		= U_store_T < unsigned long long >;

	// signed:

		nik_ce auto U_signed_char			= U_store_T < signed char      >;
		nik_ce auto U_signed_short			= U_store_T < signed short     >;
		nik_ce auto U_signed_int			= U_store_T < signed int       >;
		nik_ce auto U_signed_long			= U_store_T < signed long      >;
		nik_ce auto U_signed_long_long			= U_store_T < signed long long >;

	// auto:

		nik_ce auto U_auto_bool				= U_store_T < decltype( false ) >;
		nik_ce auto U_auto_char				= U_store_T < decltype(  '\0' ) >;
		nik_ce auto U_auto_int				= U_store_T < decltype(    0  ) >;
		nik_ce auto U_auto_float			= U_store_T < decltype(  0.0  ) >;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// packs:

/***********************************************************************************************************************/

// auto:

	template<auto...> struct T_pack_Vs; // intentionally undefined.
	using T_null_Vs = T_pack_Vs<>;

	template<auto... Vs>
	nik_ce auto U_pack_Vs = store<T_pack_Vs<Vs...>*>;
	nik_ce auto U_null_Vs = U_pack_Vs<>;

// typename:

	template<typename... Ts>
	nik_ce auto U_pack_Ts = U_pack_Vs<U_store_T<Ts>...>;
	nik_ce auto U_null_Ts = U_null_Vs;

// auto template:

	template<template<auto...> typename> struct T_store_B { };

	template<template<auto...> typename B>
	nik_ce auto U_store_B = U_store_T<T_store_B<B>>;

	template<template<auto...> typename... Bs>
	nik_ce auto U_pack_Bs = U_pack_Vs<U_store_B<Bs>...>;
	nik_ce auto U_null_Bs = U_null_Vs;

	nik_ce auto H_id = U_store_B<T_pack_Vs>;

// typename template:

	template<template<typename...> typename> struct T_store_A { };

	template<template<typename...> typename A>
	nik_ce auto U_store_A = U_store_T<T_store_A<A>>;

	template<template<typename...> typename... As>
	nik_ce auto U_pack_As = U_pack_Vs<U_store_A<As>...>;
	nik_ce auto U_null_As = U_null_Vs;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// static:

/***********************************************************************************************************************/

// callable:

	template<auto Callable>
	struct T_static_callable
	{
		nik_ces auto value = Callable();
		using type         = decltype(value);

	}; template<auto Callable>
		nik_ce auto _static_callable_ = U_store_T<T_static_callable<Callable>>;

/***********************************************************************************************************************/

// member value:

	template<typename T>
	nik_ce auto & member_value_T = T::value;

	template<auto U>
	nik_ce auto & member_value_U = member_value_T<T_store_U<U>>;

// member type:

	template<typename T>
	using member_type_T = typename T::type;

	template<auto U>
	using member_type_U = member_type_T<T_store_U<U>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// types:

/***********************************************************************************************************************/

// subnumbers:

	// bool:

		using global_bool_type		= bool;
		using gbool_type		= global_bool_type;
		using gcbool_type		= global_bool_type const;
		nik_ce auto U_gbool_type	= U_store_T<gbool_type>;
		nik_ce auto U_gcbool_type	= U_store_T<gcbool_type>;

	// [0-10]:

		using global_key_type		= unsigned char;
		using gkey_type			= global_key_type;
		using gckey_type		= global_key_type const;
		nik_ce auto U_gkey_type		= U_store_T<gkey_type>;
		nik_ce auto U_gckey_type	= U_store_T<gckey_type>;

		nik_ce gkey_type _zero		=   0;
		nik_ce gkey_type _one		=   1;
		nik_ce gkey_type _two		=   2;
		nik_ce gkey_type _three		=   3;
		nik_ce gkey_type _four		=   4;
		nik_ce gkey_type _five		=   5;
		nik_ce gkey_type _six		=   6;
		nik_ce gkey_type _seven		=   7;
		nik_ce gkey_type _eight		=   8;
		nik_ce gkey_type _nine		=   9;
		nik_ce gkey_type _ten		=  10;

	// [2^0-2^9]:

		using global_index_type		= unsigned short;
		using gindex_type		= global_index_type;
		using gcindex_type		= global_index_type const;
		nik_ce auto U_gindex_type	= U_store_T<gindex_type>;
		nik_ce auto U_gcindex_type	= U_store_T<gcindex_type>;

		nik_ce gindex_type _2_0		=   1;
		nik_ce gindex_type _2_1		=   2;
		nik_ce gindex_type _2_2		=   4;
		nik_ce gindex_type _2_3		=   8;
		nik_ce gindex_type _2_4		=  16;
		nik_ce gindex_type _2_5		=  32;
		nik_ce gindex_type _2_6		=  64;
		nik_ce gindex_type _2_7		= 128;
		nik_ce gindex_type _2_8		= 256;
		nik_ce gindex_type _2_9		= 512;

		using global_depth_type		= unsigned short;
		using gdepth_type		= global_depth_type;
		using gcdepth_type		= global_depth_type const;
		nik_ce auto U_gdepth_type	= U_store_T<gdepth_type>;
		nik_ce auto U_gcdepth_type	= U_store_T<gcdepth_type>;

/***********************************************************************************************************************/

// strings:

	using global_char_type		= char;
	using gchar_type		= global_char_type;
	using gcchar_type		= global_char_type const;
	nik_ce auto U_gchar_type	= U_store_T<gchar_type>;
	nik_ce auto U_gcchar_type	= U_store_T<gcchar_type>;

/***********************************************************************************************************************/

// array:

	template<typename Type, Type... Vs>
	nik_ce Type array[] = { Vs... };

	nik_ce gindex_type array_2_N[] = { _2_0, _2_1, _2_2, _2_3, _2_4, _2_5, _2_6, _2_7, _2_8, _2_9 };

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

		// The design privileges modularizing names, not grammar.
		// Given this, names are specified as enums within structs
		// rather than enum structs.

	template<gkey_type, gkey_type, gkey_type, auto...> struct T_grammar; // no default definition.

	template<auto Syn, auto Key, auto... Vs>
	nik_ce auto U_grammar = U_store_T<T_grammar<Syn, Key, Vs...>>;

/***********************************************************************************************************************/

// shapes:

	struct Shape
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			argument , // parameter
			dimension
		};
	};

/***********************************************************************************************************************/

// patterns:

	struct Pattern
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			overload , number , lambda_tuple ,
			dimension

		//	overload , higher_order ,
		//	boolean  , number       , array    ,
		//	selector , iterator     , sequence , subarray , pair ,
		//	abstract , access       , list     ,
		//	pointer  , reference    , function ,
		};
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// argument:

	// no default definition.

	template<auto Key, auto... Vs>       using T_argument = T_grammar<Shape::argument, Key, Vs...>;
	template<auto Key, auto... Vs> nik_ce auto U_argument = U_grammar<Shape::argument, Key, Vs...>;

/***********************************************************************************************************************/

// overload:

	template<auto... Vs> using T_arg_overload		= T_argument<Pattern::overload, Vs...>;
	template<auto... Vs> nik_ce auto U_arg_overload		= U_argument<Pattern::overload, Vs...>;

// higher order:

//	template<auto... Vs> using T_arg_higher_order		= T_argument<Pattern::higher_order, Vs...>;
//	template<auto... Vs> nik_ce auto U_arg_higher_order	= U_argument<Pattern::higher_order, Vs...>;

// boolean:

//	template<auto... Vs> using T_arg_boolean		= T_argument<Pattern::boolean, Vs...>;
//	template<auto... Vs> nik_ce auto U_arg_boolean		= U_argument<Pattern::boolean, Vs...>;

// number:

	template<auto... Vs> using T_arg_number			= T_argument<Pattern::number, Vs...>;
	template<auto... Vs> nik_ce auto U_arg_number		= U_argument<Pattern::number, Vs...>;

// lambda tuple:

	template<auto... Vs> using T_arg_lambda_tuple		= T_argument<Pattern::lambda_tuple, Vs...>;
	template<auto... Vs> nik_ce auto U_arg_lambda_tuple	= U_argument<Pattern::lambda_tuple, Vs...>;

// array:

//	template<auto... Vs> using T_arg_array			= T_argument<Pattern::array, Vs...>;
//	template<auto... Vs> nik_ce auto U_arg_array		= U_argument<Pattern::array, Vs...>;

// selector:

//	template<auto... Vs> using T_arg_selector		= T_argument<Pattern::selector, Vs...>;
//	template<auto... Vs> nik_ce auto U_arg_selector		= U_argument<Pattern::selector, Vs...>;

// iterator:

//	template<auto... Vs> using T_arg_iterator		= T_argument<Pattern::iterator, Vs...>;
//	template<auto... Vs> nik_ce auto U_arg_iterator		= U_argument<Pattern::iterator, Vs...>;

// sequence:

//	template<auto... Vs> using T_arg_sequence		= T_argument<Pattern::sequence, Vs...>;
//	template<auto... Vs> nik_ce auto U_arg_sequence		= U_argument<Pattern::sequence, Vs...>;

// subarray:

//	template<auto... Vs> using T_arg_subarray		= T_argument<Pattern::subarray, Vs...>;
//	template<auto... Vs> nik_ce auto U_arg_subarray		= U_argument<Pattern::subarray, Vs...>;

// pair:

//	template<auto... Vs> using T_arg_pair			= T_argument<Pattern::pair, Vs...>;
//	template<auto... Vs> nik_ce auto U_arg_pair		= U_argument<Pattern::pair, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// parameter:

//	template<gkey_type Key, gkey_type Op, auto... Vs>
//	struct T_grammar<Shape::parameter, Key, Op, Vs...> { }; // empty default definition.

//	template<auto Key, auto... Vs>       using T_parameter = T_grammar<Shape::parameter, Key, Vs...>;
//	template<auto Key, auto... Vs> nik_ce auto U_parameter = U_grammar<Shape::parameter, Key, Vs...>;

/***********************************************************************************************************************/

// abstract:

//	template<auto... Vs> using T_par_abstract		= T_parameter<Pattern::abstract, Vs...>;
//	template<auto... Vs> nik_ce auto U_par_abstract		= U_parameter<Pattern::abstract, Vs...>;

// access:

//	template<auto... Vs> using T_par_access			= T_parameter<Pattern::access, Vs...>;
//	template<auto... Vs> nik_ce auto U_par_access		= U_parameter<Pattern::access, Vs...>;

// list:

//	template<auto... Vs> using T_par_list			= T_parameter<Pattern::list, Vs...>;
//	template<auto... Vs> nik_ce auto U_par_list		= U_parameter<Pattern::list, Vs...>;

// boolean:

//	template<auto... Vs> using T_par_boolean		= T_parameter<Pattern::boolean, Vs...>;
//	template<auto... Vs> nik_ce auto U_par_boolean		= U_parameter<Pattern::boolean, Vs...>;

// number:

//	template<auto... Vs> using T_par_number			= T_parameter<Pattern::number, Vs...>;
//	template<auto... Vs> nik_ce auto U_par_number		= U_parameter<Pattern::number, Vs...>;

// pointer:

//	template<auto... Vs> using T_par_pointer		= T_parameter<Pattern::pointer, Vs...>;
//	template<auto... Vs> nik_ce auto U_par_pointer		= U_parameter<Pattern::pointer, Vs...>;

// reference:

//	template<auto... Vs> using T_par_reference		= T_parameter<Pattern::reference, Vs...>;
//	template<auto... Vs> nik_ce auto U_par_reference	= U_parameter<Pattern::reference, Vs...>;

// array:

//	template<auto... Vs> using T_par_array			= T_parameter<Pattern::array, Vs...>;
//	template<auto... Vs> nik_ce auto U_par_array		= U_parameter<Pattern::array, Vs...>;

// function:

//	template<auto... Vs> using T_par_function		= T_parameter<Pattern::function, Vs...>;
//	template<auto... Vs> nik_ce auto U_par_function		= U_parameter<Pattern::function, Vs...>;

// identity:

//	template<auto... Vs> using T_par_identity		= T_parameter<Pattern::identity, Vs...>;
//	template<auto... Vs> nik_ce auto U_par_identity		= U_parameter<Pattern::identity, Vs...>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// structure:

/***********************************************************************************************************************/

// literal:

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

// sequence:

	template<typename Type, typename SizeType, SizeType Size>
	class sequence
	{
		public:

			using type		= Type;
			using type_ptr		= type*;
			using type_cptr		= type_ptr const;
			using type_ref		= type&;

			using ctype		= type const;
			using ctype_ptr		= ctype*;
			using ctype_cptr	= ctype_ptr const;
			using ctype_ref		= ctype&;

			using size_type		= SizeType;
			using csize_type	= size_type const;

		protected:

			type initial[Size];
			size_type terminal; // compile time compatible.

		public:

			nik_ce sequence() : initial{}, terminal{} { }

			// immutable:

				nik_ce size_type length () const { return Size; }
				nik_ce ctype_ptr origin () const { return initial; }
				nik_ce size_type size   () const { return terminal; }
				nik_ce size_type max    () const { return size() - 1; }

				nik_ce bool is_empty  () const { return (terminal == 0); }
				nik_ce bool not_empty () const { return (terminal != 0); }

				nik_ce auto left_size  (ctype_cptr i) const { return i - initial; }
				nik_ce auto right_size (ctype_cptr i) const { return (initial + terminal) - i; }

				nik_ce ctype_ptr cbegin () const { return initial; }
				nik_ce ctype_ptr clast  () const { return (initial + terminal) - 1; }
				nik_ce ctype_ptr cend   () const { return initial + terminal; }

				nik_ce ctype_ref operator [] (csize_type pos) const { return initial[pos]; }

			// mutable:

				nik_ce void clear() { terminal = 0; }
				nik_ce void fullsize() { terminal = Size; }
				nik_ce void upsize(csize_type num = 1) { terminal += num; }
				nik_ce void downsize(csize_type num = 1) { terminal -= num; }
				nik_ce void push(ctype_ref v) { *(initial + terminal++) = v; }
				nik_ce type pop() { return *(initial + --terminal); }

				nik_ce type_ptr begin () { return initial; }
				nik_ce type_ptr last  () { return (initial + terminal) - 1; }
				nik_ce type_ptr end   () { return initial + terminal; }

				nik_ce type_ref operator [] (csize_type pos) { return initial[pos]; }
	};

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
/***********************************************************************************************************************/

} // namespace cctmp

