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

// space:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// operators:

/***********************************************************************************************************************/

// at:

	template<auto n, auto... filler>
	struct T_grammar<Shape::argument, Pattern::overload, ArgOverload::at, n, filler...>
	{
		template<typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			nik_ce auto p0 = left_    <n, U_store_T<Ts>...>;
			nik_ce auto p1 = right_   <n, U_store_T<Ts>...>;
			nik_ce auto U  = _select_ <p0, p1>;

			return T_store_U<U>::result(vs...);
		}

	}; template<auto n>
		nik_ce auto _at_ = U_arg_overload<ArgOverload::at, n>;

	// syntactic sugar:

		template<auto n, auto... Vs>
		nik_ce auto at_ = T_store_U<_at_<n>>::template result<decltype(Vs)...>(Vs...);

		template<auto n, typename... Ts>
		using type_at = T_store_U<at_<n, U_store_T<Ts>...>>;

		template<auto... Vs, nik_vp(p)(T_pack_Vs<Vs...>*), auto n>
		nik_ce auto at_<p, n> = T_store_U<_at_<n>>::template result<decltype(Vs)...>(Vs...);

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple method:

	template<template<typename, typename, auto> typename, typename...> struct tuple_cmethod;

/***********************************************************************************************************************/

// immutable index:

	template<typename Type, typename SizeType, SizeType>
	class tuple_cindex
	{
		public:

			using type		= typename alias<Type>::type;
			using type_ptr		= typename alias<Type>::type_ptr;
			using type_cptr		= typename alias<Type>::type_cptr;
			using type_ref		= typename alias<Type>::type_ref;

			using ctype		= typename alias<Type>::ctype;
			using ctype_ptr		= typename alias<Type>::ctype_ptr;
			using ctype_cptr	= typename alias<Type>::ctype_cptr;
			using ctype_ref		= typename alias<Type>::ctype_ref;

			using size_type		= typename alias<SizeType>::type;
			using size_ctype	= typename alias<SizeType>::ctype;

		protected:

			type value;

		public:

			nik_ce tuple_cindex() : value{} { }
			nik_ce tuple_cindex(ctype_ref v) : value{v} { }

			nik_ce ctype_ref cvalue() const { return value; }
	};

/***********************************************************************************************************************/

// mutable index:

	template<typename Type, typename SizeType, SizeType Index>
	class tuple_index : public tuple_cindex<Type, SizeType, Index>
	{
		public:

			using base		= tuple_cindex<Type, SizeType, Index>;

			using type		= typename base::type;
			using type_ptr		= typename base::type_ptr;
			using type_cptr		= typename base::type_cptr;
			using type_ref		= typename base::type_ref;

			using ctype		= typename base::ctype;
			using ctype_ptr		= typename base::ctype_ptr;
			using ctype_cptr	= typename base::ctype_cptr;
			using ctype_ref		= typename base::ctype_ref;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			nik_ce tuple_index() : base{} { }
			nik_ce tuple_index(ctype_ref v) : base{v} { }

			nik_ce type_ref value() { return base::value; }

			nik_ce void set_value(ctype_ref v) { base::value = v; }
	};

/***********************************************************************************************************************/

// immutable:

	template<template<typename, typename, auto> typename Index, typename SizeType, auto... Is, typename... Types>
	class tuple_cmethod<Index, SizeType, T_pack_Vs<Is...>, Types...> : public Index<Types, SizeType, Is>...
	{
		public:

			using size_type		= typename alias<SizeType>::type;
			using size_ctype	= typename alias<SizeType>::ctype;

		public:

			template<size_type n>
			using sub_type = type_at<n, Types...>;

			nik_ces size_type length() { return sizeof...(Types); }

		public:

			nik_ce tuple_cmethod() : Index<Types, size_type, Is>{}... { }
			nik_ce tuple_cmethod(const Types &... vs) : Index<Types, size_type, Is>{vs}... { }

			template<size_type n>
			nik_ce const auto & cvalue() const
			{
				using Type      = sub_type<n>;
				using IndVal    = Index<Type, size_type, n>;
				using IndValPtr = typename alias<IndVal>::ctype_ptr;

				return static_cast<IndValPtr>(this)->cvalue();
			}
	};

/***********************************************************************************************************************/

// mutable:

	template<template<typename, typename, auto> typename Index, typename SizeType, typename Sizes, typename... Types>
	class tuple_method : public tuple_cmethod<Index, SizeType, Sizes, Types...>
	{
		public:

			using base		= tuple_cmethod<Index, SizeType, Sizes, Types...>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			nik_ce tuple_method() : base{} { }
			nik_ce tuple_method(const Types &... vs) : base{vs...} { }

			template<size_type n>
			nik_ce auto & value()
			{
				using Type      = typename base::template sub_type<n>;
				using IndVal    = Index<Type, size_type, n>;
				using IndValPtr = typename alias<IndVal>::type_ptr;

				return static_cast<IndValPtr>(this)->value();
			}

			template<size_type n, typename T>
			nik_ce void set_value(const T & v)
			{
				using Type      = typename base::template sub_type<n>;
				using IndVal    = Index<Type, size_type, n>;
				using IndValPtr = typename alias<IndVal>::type_ptr;

				return static_cast<IndValPtr>(this)->set_value(v);
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

/***********************************************************************************************************************/

// immutable:

	template<typename SizeType, typename... Types>
	class ctuple : public tuple_cmethod<tuple_cindex, SizeType, T_store_U<segment_<sizeof...(Types)>>, Types...>
	{
		public:

			using seg_pack		= T_store_U<segment_<sizeof...(Types)>>;

			using base		= tuple_cmethod<tuple_cindex, SizeType, seg_pack, Types...>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			nik_ce ctuple() : base{} { }
			nik_ce ctuple(const Types &... vs) : base{vs...} { }
	};

	// syntactic sugar:

		template<typename SizeType, typename... Ts>
		nik_ces auto env_tuple(Ts... vs)
		{
			using frame_type = ctuple<SizeType, Ts...      >;
			using env_type   = ctuple<SizeType, frame_type >;

			return env_type{frame_type{vs...}};
		}

/***********************************************************************************************************************/

// mutable:

	template<typename SizeType, typename... Types>
	class tuple : public tuple_method<tuple_index, SizeType, T_store_U<segment_<sizeof...(Types)>>, Types...>
	{
		public:

			using seg_pack		= T_store_U<segment_<sizeof...(Types)>>;

			using base		= tuple_method<tuple_index, SizeType, seg_pack, Types...>;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		public:

			nik_ce tuple() : base{} { }
			nik_ce tuple(const Types &... vs) : base{vs...} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// machine:

	template<gkey_type, gkey_type, auto...> struct T_machine;

/***********************************************************************************************************************/

// names:

	struct MachineName
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			halt    ,							//  1
			type    , literal    , floating , string , lookup , arg  ,	//  2
			pad     , hash       , pound    , apply  , bind   , eval ,	//  8
			go_to   , branch     , invert   , loop   ,			// 14
			cycle   , next       , set      ,				// 18
			repeat  , map        , fold     , find   , sift   ,		// 21

		// symbolic:

			variable , value ,						// 26

			dimension
		};
	};

	using MN = MachineName;

/***********************************************************************************************************************/

// notes:

	struct MachineNote
	{
		enum : gkey_type
		{
			id = 0, identity = id, // convenience for default params.
			none    , first     , pause    ,                //  1
			front   , back      ,				//  4
			boolean , character , n_number , r_number ,	//  6
			port    , select    ,				// 10
			push    , pull      , drop     ,		// 12
			verse   , side      , replace  ,		// 15
			inc     , dec       ,				// 18

		// symbolic:

			t_number , universe , lookup   ,		// 19

			dimension
		};
	};

	using MT = MachineNote;

/***********************************************************************************************************************/

// index:

	struct MachineIndex { enum : gkey_type { name, note, pos, num, aux0, aux1, aux2, next, dimension }; };

	using MI = MachineIndex;

/***********************************************************************************************************************/

// dispatch:

	template<auto static_contr>
	struct MachineDispatch
	{
		nik_ces auto rowsize	= T_store_U<static_contr>::rowsize;
		nik_ces auto colsize	= MachineIndex::dimension;

		using size_type		= typename T_store_U<static_contr>::size_type;
		using size_ctype	= size_type const;
		using ctab_type		= ctable<size_type, size_type, rowsize, colsize>;

		nik_ces auto contr	= ctab_type{member_value_U<static_contr>};

		// accessors:

			nik_ces size_type value (size_ctype i, size_ctype n) { return contr[i][n]; }
			nik_ces size_type peek  (size_ctype i, size_ctype m, size_ctype n) { return contr[i + m][n]; }

			nik_ces size_type pos  (size_ctype i) { return value(i, MI::pos); }
			nik_ces size_type num  (size_ctype i) { return value(i, MI::num); }
			nik_ces size_type aux0 (size_ctype i) { return value(i, MI::aux0); }
			nik_ces size_type aux1 (size_ctype i) { return value(i, MI::aux1); }
			nik_ces size_type aux2 (size_ctype i) { return value(i, MI::aux2); }

		// navigators:

			nik_ces size_type next_offset (size_ctype i) { return value(i, MI::next); }
			nik_ces size_type next_index  (size_ctype i) { return i + next_offset(i); }

			nik_ces gkey_type next_name (size_ctype i) { return value(next_index(i), MI::name); }
			nik_ces gkey_type next_note (size_ctype i) { return value(next_index(i), MI::note); }
	};

	template<auto static_contr>
	using MD = MachineDispatch<static_contr>;

/***********************************************************************************************************************/

// compound:

	template<auto...> struct T_machine_compound;

	// untyped:

		template<auto c, auto i>
		struct T_machine_compound<c, i>
		{
			template<auto l, auto t, auto r, typename... Ts>
			nik_ces auto result(Ts... vs)
			{
				return NIK_MACHINE_TEMPLATE(c, i)
					::NIK_MACHINE_RESULT_TS(c, i, l, t, r, Ts...)
						(vs...);
			}
		};

	// typed:

		template<auto s, auto c, auto i>
		struct T_machine_compound<s, c, i>
		{
			using S = T_store_U<s>;

			template<auto l, auto t, auto r, typename... Ts>
			nik_ces auto result(Ts... vs) -> S
			{
				return NIK_MACHINE_TEMPLATE(c, i)
					::NIK_MACHINE_RESULT_TS(c, i, l, t, r, Ts...)
						(vs...);
			}
		};

	// syntactic sugar:

		template<auto... Vs>
		nik_ce auto U_machine_compound = U_store_T<T_machine_compound<Vs...>>;

		nik_ce auto H_machine_compound = U_store_B<T_machine_compound>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// read:

/***********************************************************************************************************************/

// only:

	template<auto...>
	struct T_read
	{
		// default:

			template<typename T>
			nik_ces auto only(nik_avp(T*)) { return U_store_T<T const>; }

		// pointer (recursive):

			template<typename T>
			using T_add_pointer_const = T*const;

			template<auto U>
			nik_ces auto add_pointer_const = U_store_T<T_add_pointer_const<T_store_U<U>>>;

			template<typename T>
			nik_ces auto only(nik_avp(T**))
				{ return add_pointer_const<only(U_store_T<T>)>; }

			template<typename T>
			nik_ces auto only(nik_avp(T*const*))
				{ return add_pointer_const<only(U_store_T<T>)>; }

		// reference (recursive):

			template<typename T>
			using T_add_reference_const = T&;

			template<auto U>
			nik_ces auto add_reference_const = U_store_T<T_add_reference_const<T_store_U<U>>>;

			template<typename T>
			nik_ces auto only(nik_avp(T&))
				{ return add_reference_const<only(U_store_T<T>)>; }
	};

	// syntactic sugar:

		template<bool V, typename T>
		using read_type = typename T_read<V, U_store_T<T>>::mtype;

/***********************************************************************************************************************/

// immutable:

	template<auto U, auto... filler>
	struct T_read<false, U, filler...>
	{
		protected:

			nik_ces auto U_mtype	= T_read<filler...>::only(U);

		public:

			using mtype		= T_store_U<U_mtype>;
	};

/***********************************************************************************************************************/

// mutable:

	template<auto U, auto... filler>
	struct T_read<true, U, filler...>
	{
		public:

			using mtype		= T_store_U<U>;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// metapile:

/***********************************************************************************************************************/

// apply:

	template
	<
		typename SizeType,
		auto static_contr,
		auto static_values,
		auto out_types
	>
	struct T_metapile_apply
	{
		nik_ces SizeType zero = 0;

		template<typename... Ts>
		nik_ces auto result(Ts... vs)
		{
			return T_machine_compound<static_contr, zero>::template
				result<static_values, out_types, zero, Ts...>(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

