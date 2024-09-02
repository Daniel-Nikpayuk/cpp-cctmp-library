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
	using gchar_type						= cctmp::gchar_type;
	using gchar_ctype						= cctmp::gchar_ctype;

	template<typename T>
	using alias							= cctmp::alias<T>;

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

// string:

	template<typename Type, typename SizeType>
	struct string_literal : public cctmp::array_literal<Type, SizeType>
	{
		using base		= cctmp::array_literal<Type, SizeType>;

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

		template<auto N>
		nik_ce string_literal(const Type (&s)[N]) : base{s, N-1} { }

		nik_ce string_literal() : base{} { } // maybe.
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// plot:

/***********************************************************************************************************************/

// entry:

	template<typename SizeType>
	class plot_entry
	{
		public:

			using size_type		= typename alias<SizeType>::type;
			using size_ctype	= typename alias<SizeType>::ctype;

		protected:

			size_type initial;
			size_type terminal;

		public:

			nik_ce plot_entry() : initial{}, terminal{} { }

			nik_ce size_type start  () const { return initial; }
			nik_ce size_type finish () const { return terminal; }

			nik_ce void set_start  (size_ctype i) { initial = i; }
			nik_ce void set_finish (size_ctype t) { terminal = t; }
	};

/***********************************************************************************************************************/

// proto:

		// stance: circumstantial semantics separate from main.

	template<typename Stance, typename Base>
	class protoplot : public Base
	{
		public:

			using base		= Base;

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

			using stance_type	= typename alias<Stance>::type;
			using stance_type_ptr	= typename alias<Stance>::type_ptr;
			using stance_type_ref	= typename alias<Stance>::type_ref;
			using stance_ctype_ptr	= typename alias<Stance>::ctype_ptr;
			using stance_ctype_cptr	= typename alias<Stance>::ctype_cptr;
			using stance_ctype_ref	= typename alias<Stance>::ctype_ref;

		protected:

			stance_type stance;

			nik_ce size_type start  (size_ctype n) const { return base::operator [] (n).start(); }
			nik_ce size_type finish (size_ctype n) const { return base::operator [] (n).finish(); }

		public:

			nik_ce protoplot() { }

			template<typename T, auto N, typename S, auto M>
			nik_ce protoplot(const T (&e)[N], const S (&s)[M]) : base{e}, stance{s} { }

			// initial:

				using base::origin;
				using base::cbegin;
				using base::citer;
				using base::left_size;
				using base::not_equal;
				using base::equal;

				nik_ce stance_ctype_ptr origin(size_ctype n) const { return stance.citer(start(n)); }
				nik_ce stance_ctype_ptr cbegin(size_ctype n) const { return stance.citer(start(n)); }

				nik_ce stance_ctype_ptr citer(size_ctype n, size_ctype m) const
					{ return cbegin(n) + m; }

				nik_ce size_type left_size(size_ctype n, stance_ctype_cptr i) const
					{ return i - cbegin(n); }

				nik_ce stance_ctype_ref at(size_ctype n, size_ctype m) const { return cbegin(n)[m]; }

				template<typename In, typename End>
				nik_ce bool not_equal(size_ctype n, In in, End end) const
					{ return stance.not_equal(start(n), in, end); }

				template<typename In, typename End>
				nik_ce bool equal(size_ctype n, In in, End end) const
					{ return stance.equal(start(n), in, end); }

			// terminal:

				using base::size;
				using base::max;
				using base::is_empty;
				using base::not_empty;
				using base::cend;
				using base::clast;
				using base::right_size;

				nik_ce size_type size (size_ctype n) const { return finish(n) - start(n); }
				nik_ce size_type max  (size_ctype n) const { return size(n) - 1; }

				nik_ce bool is_empty  (size_ctype n) const { return (size(n) == 0); }
				nik_ce bool not_empty (size_ctype n) const { return (size(n) != 0); }

				nik_ce stance_ctype_ptr cend  (size_ctype n) const { return stance.citer(finish(n)); }
				nik_ce stance_ctype_ptr clast (size_ctype n) const { return cend(n) - 1; }

				nik_ce size_type right_size(size_ctype n, stance_ctype_cptr i) const
					{ return cend(n) - i; }
	};

/***********************************************************************************************************************/

// literal:

	template<typename Stance, typename Type, typename SizeType>
	class plot_literal	: public protoplot
				<
					cctmp::array_literal < Stance , SizeType >,
					cctmp::array_literal < Type   , SizeType >
				>
	{
		public:

			using base		= protoplot
						<
							cctmp::array_literal < Stance , SizeType >,
							cctmp::array_literal < Type   , SizeType >
						>;

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

			using stance_type	= typename base::stance_type;
			using stance_type_ptr	= typename base::stance_type_ptr;
			using stance_type_ref	= typename base::stance_type_ref;
			using stance_ctype_ptr	= typename base::stance_ctype_ptr;
			using stance_ctype_cptr	= typename base::stance_ctype_cptr;
			using stance_ctype_ref	= typename base::stance_ctype_ref;

		public:

			nik_ce plot_literal() { }

			template<typename T, auto N, typename S, auto M>
			nik_ce plot_literal(const T (&e)[N], const S (&s)[M]) : base{e, s} { }
	};

/***********************************************************************************************************************/

// interface:

	template<typename Stance, typename Type, typename SizeType, SizeType Size>
	class plot	: public protoplot // array_size(Type) <= array_size(Stance)
			<
				cctmp::array < Stance , SizeType , Size >,
				cctmp::array < Type   , SizeType , Size >
			>
	{
		public:

			using base		= protoplot
						<
							cctmp::array < Stance , SizeType , Size >,
							cctmp::array < Type   , SizeType , Size >
						>;

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

			using stance_type	= typename base::stance_type;
			using stance_type_ptr	= typename base::stance_type_ptr;
			using stance_type_ref	= typename base::stance_type_ref;
			using stance_ctype_ptr	= typename base::stance_ctype_ptr;
			using stance_ctype_cptr	= typename base::stance_ctype_cptr;
			using stance_ctype_ref	= typename base::stance_ctype_ref;

		protected:

			nik_ce void push_finish(size_ctype start)
			{
				size_ctype finish = base::stance.size();

				base::upsize();
				base::last()->set_start  (start);
				base::last()->set_finish (finish);
			}

			nik_ce void set_finish(size_ctype n, size_ctype start)
			{
				size_ctype finish = base::stance.size();

				base::operator [] (n).set_start  (start);
				base::operator [] (n).set_finish (finish);
			}

		public:

			nik_ce plot() { }

			template<typename T, auto N, typename S, auto M>
			nik_ce plot(const T (&e)[N], const S (&s)[M]) : base{e, s} { }

			// mutable:

				using base::begin;
				using base::end;
				using base::last;
				using base::at;
				using base::iter;

				nik_ce stance_type_ptr begin (size_ctype n) { return base::stance.iter(base::start(n)); }
				nik_ce stance_type_ptr end   (size_ctype n) { return base::stance.iter(base::finish(n)); }
				nik_ce stance_type_ptr last  (size_ctype n) { return end(n) - 1; }

				nik_ce stance_type_ref at(size_ctype n, size_ctype m) { return begin(n)[m]; }

				nik_ce stance_type_ptr iter(size_ctype n, size_ctype m) { return begin(n) + m; }

				template<typename In, typename End>
				nik_ce void push(In in, End end)
				{
					size_ctype start = base::stance.size();

					base::stance.push(in, end);
					push_finish(start);
				}

				template<typename F, typename In, typename End>
				nik_ce void pushmap(F f, In in, End end)
				{
					size_ctype start = base::stance.size();

					base::stance.pushmap(f, in, end);
					push_finish(start);
				}

				template<typename F, typename In, typename End>
				nik_ce void setmap(size_ctype n, F f, In in, End end)
				{
					size_ctype start = base::stance.size();

					base::stance.pushmap(f, in, end);
					set_finish(n, start);
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// plottable:

/***********************************************************************************************************************/

// proto:

	template<typename SizeType, SizeType RowSize, SizeType ColSize, typename Base>
	class protoplottable : public Base
	{
		public:

			using base		= Base;

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

			nik_ce protoplottable() { }

			template<typename T, auto N, typename S, auto M>
			nik_ce protoplottable(const T (&e)[N], const S (&s)[M]) : base{e, s} { }

			nik_ce size_type row_length () const { return RowSize; }
			nik_ce size_type col_length () const { return ColSize; }

			nik_ce ctype_ptr row_cbegin (size_ctype n) const { return base::citer(n * ColSize); }
			nik_ce ctype_ptr row_cend   (size_ctype n) const { return row_cbegin(n + 1); }
			nik_ce ctype_ptr row_clast  (size_ctype n) const { return row_cend(n) - 1; }

			nik_ce ctype_ptr operator [] (size_ctype n) const { return row_cbegin(n); }
	};

/***********************************************************************************************************************/

// literal:

	template<typename Stance, typename Type, typename SizeType, SizeType RowSize, SizeType ColSize>
	class plottable_literal	: public protoplottable
				<
					SizeType, RowSize, ColSize, plot_literal<Stance, Type, SizeType>
				>
	{
		public:

			using subbase		= plot_literal<Stance, Type, SizeType>;
			using base		= protoplottable<SizeType, RowSize, ColSize, subbase>;

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

			nik_ce plottable_literal() { }

			template<typename T, auto N, typename S, auto M>
			nik_ce plottable_literal(const T (&e)[N], const S (&s)[M]) : base{e, s} { }

			nik_ce bool operator != (const plottable_literal & l) const
				{ return base::not_equal(0, l.cbegin(), l.cend()); }

			nik_ce bool operator == (const plottable_literal & l) const
				{ return base::equal(0, l.cbegin(), l.cend()); }
	};

/***********************************************************************************************************************/

// interface:

	template<typename Stance, typename Type, typename SizeType, SizeType RowSize, SizeType ColSize>
	class plottable	: public protoplottable
			<
				SizeType, RowSize, ColSize, plot<Stance, Type, SizeType, RowSize * ColSize>
			>
	{
		public:

			using subbase		= plot<Stance, Type, SizeType, RowSize * ColSize>;
			using base		= protoplottable<SizeType, RowSize, ColSize, subbase>;

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

			nik_ce plottable() { }

			template<typename E, auto N, typename T, auto M>
			nik_ce plottable(const E (&e)[N], const T (&v)[M]) : base{e, v} { }

			using base::operator [];

			nik_ce type_ptr row_begin (size_ctype n) { return base::iter(n * ColSize); }
			nik_ce type_ptr row_end   (size_ctype n) { return row_begin(n + 1); }
			nik_ce type_ptr row_last  (size_ctype n) { return row_end(n) - 1; }

			nik_ce type_ptr operator [] (size_ctype n) { return row_begin(n); }

			template<typename F, typename In, typename End>
			nik_ce void setmap(size_ctype row, size_ctype col, F f, In in, End end)
				{ base::setmap(row * ColSize + col, f, in, end); }
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
		template<        typename LT> nik_ces auto empty  (LT lt) { return lt(_empty_); }
		template<        typename LT> nik_ces auto size   (LT lt) { return lt(_size_ ); }
		template<        typename LT> nik_ces auto first  (LT lt) { return lt(_at_<0>); }
		template<        typename LT> nik_ces auto second (LT lt) { return lt(_at_<1>); }
		template<auto n, typename LT> nik_ces auto value  (LT lt) { return lt(_at_<n>); }

		template<typename... Ts>
		nik_ces auto make(Ts... vs) { return T_store_U<_lambda_tuple_>::template result<Ts...>(vs...); }

		template<typename LT1, typename LT2>
		nik_ces auto catenate(LT1 lt1, LT2 lt2) { return lt1(_lambda_tuple_catenate_, lt2); }

		template<typename SizeType, typename LT>
		nik_ces auto env_tuple(LT lt) { return lt(_lambda_env_tuple_<U_store_T<SizeType>>); }
	};

/***********************************************************************************************************************/

// binding:

		// static assert: size_type is_ref ?

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

		// static assert: size_type is_ref ?

	template<typename CharType, typename SizeType, typename... Bindings>
	nik_ce auto frame(nik_avp(CharType*), nik_avp(SizeType*), Bindings... bs)
	{
		using strlit_type   = string_literal<CharType, SizeType>;
		using variable_type = cctmp::array<strlit_type, SizeType, sizeof...(Bindings)>;

		auto variables      = variable_type{   {LambdaTuple::first  (bs)...}};
		auto values         = LambdaTuple::make(LambdaTuple::second (bs)...);

		return LambdaTuple::make(variables, values);
	}

/***********************************************************************************************************************/

// instr:

	template<typename Type, typename SizeType>
	struct machine_instr : public cctmp::array<Type, SizeType, MachineIndex::dimension>
	{
		using Index 		= MachineIndex;
		using base 		= cctmp::array<Type, SizeType, Index::dimension>;

		using size_type		= typename base::size_type;
		using size_ctype	= typename base::size_ctype;

		nik_ce machine_instr() : base{} { }

		nik_ce void set(size_ctype n, size_ctype t, size_ctype p, size_ctype m)
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
	struct machine_contr : public cctmp::array<machine_instr<Type, SizeType>, SizeType, Size>
	{
		using instr_type	= machine_instr<Type, SizeType>;
		using base		= cctmp::array<instr_type, SizeType, Size>;
		using size_type		= typename base::size_type;
		using size_ctype	= typename base::size_ctype;

		nik_ce machine_contr() : base{} { }

		nik_ce void push(size_ctype n, size_ctype t, size_ctype p = 0, size_ctype m = 0)
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

// clookup:

/***********************************************************************************************************************/

// interface:

	template<typename Type0, typename Type1, typename SizeType, SizeType Size>
	class clookup
	{
		public:

			using size_type		= SizeType;
			using size_ctype	= size_type const;

			using left_type		= cctmp::array<Type0, size_type, Size>;
			using right_type	= cctmp::array<Type1, size_type, Size>;

		protected:

			left_type left;
			right_type right;

		public:

			nik_ce clookup() { }

			template<typename T0, typename T1, auto N>
			nik_ce clookup(const T0 (&l)[N], const T1 (&r)[N]) : left{l}, right{r} { }

			nik_ce const Type1 & lfind(const Type0 & v0, const Type1 & v1) const
			{
				for (size_type k = 0; k != Size; ++k) 
					if (left[k] == v0) return right[k];

				return v1;
			}

			nik_ce const Type0 & rfind(const Type1 & v1, const Type0 & v0) const
			{
				for (size_type k = 0; k != Size; ++k) 
					if (right[k] == v1) return left[k];

				return v0;
			}
	};

	// syntactic sugar:

		template<typename T0, typename T1>
		nik_ce auto pair(T0 t0, T1 t1) { return LambdaTuple::make(t0, t1); }

		template<typename SizeType, typename TU0, typename TU1, typename... Pairs>
		nik_ce auto lookup(nik_avp(SizeType*), TU0, TU1, Pairs... ps)
		{
			using T0         = T_restore_T<TU0>;
			using T1         = T_restore_T<TU1>;
			using lookup_type = clookup<T0, T1, SizeType, sizeof...(Pairs)>;

			return lookup_type
			{
				{LambdaTuple::first(ps)...},
				{LambdaTuple::second(ps)...}
			};
		}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// model:

/***********************************************************************************************************************/

// entry:

	template<typename Type, typename SizeType>
	struct model_entry
	{
		using type		= typename alias<Type>::type;
		using ctype		= typename alias<Type>::ctype;
		using ctype_ref		= typename alias<Type>::ctype_ref;

		using size_type		= typename alias<SizeType>::type;
		using size_ctype	= typename alias<SizeType>::ctype;

		type car;
		size_type cdr;

		nik_ce model_entry() : car{}, cdr{} { }
	};

/***********************************************************************************************************************/

// list:

	template<typename Type, typename SizeType, SizeType Size>
	class model_list
	{
		public:

			using entry_type		= model_entry<Type, SizeType>;
			using entry_ctype		= typename alias<entry_type>::ctype;
			using entry_ctype_ptr		= typename alias<entry_type>::ctype_ptr;

			using type			= typename entry_type::type;
			using ctype			= typename entry_type::ctype;
			using ctype_ref			= typename entry_type::ctype_ref;

			using size_type			= typename entry_type::size_type;
			using size_ctype		= typename entry_type::size_ctype;

			using list_type			= size_type;
			using list_ctype		= size_ctype;

		protected:

			nik_ces size_type length	= Size;
			nik_ces list_type null		= length;

			entry_type array[length];
			size_type free;

		public:

			nik_ce model_list() : array{}, free{length} { }

		protected:

			// free:

				nik_ce void clear() { free = length; }

				nik_ce size_type allocate() { return --free; }

		public:

			// array:

				nik_ce entry_ctype_ptr cbegin () const { return array; }
				nik_ce entry_ctype_ptr cend   () const { return array + length; }

				nik_ce ctype_ref get_car(size_ctype n) const { return array[n].car; }
				nik_ce void set_car(size_ctype n, ctype_ref v) { array[n].car = v; }

				nik_ce size_type get_cdr(size_ctype n) const { return array[n].cdr; }
				nik_ce void set_cdr(size_ctype n, list_ctype v) { array[n].cdr = v; }

			// list:

				nik_ce bool is_null  (list_ctype l) const { return (l == null); }
				nik_ce bool not_null (list_ctype l) const { return (l != null); }

				nik_ce bool is_model  (list_ctype l) const { return (l == 0); }
				nik_ce bool not_model (list_ctype l) const { return (l != 0); }

				nik_ce list_type null_list() const { return null; }

				nik_ce list_type cons(ctype_ref v, list_ctype l)
				{
					list_ctype nl = allocate();

					set_car(nl, v);
					set_cdr(nl, l);

					return nl;
				}
	};

/***********************************************************************************************************************/

// stack:

	template<typename Type, typename SizeType, SizeType Size>
	class stack : public model_list<Type, SizeType, Size>
	{
		public:

			using base		= model_list<Type, SizeType, Size>;

			using entry_type	= typename base::entry_type;
			using entry_ctype	= typename base::entry_ctype;
			using entry_ctype_ptr	= typename base::entry_ctype_ptr;

			using type		= typename base::type;
			using ctype		= typename base::ctype;
			using ctype_ref		= typename base::ctype_ref;

			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

		protected:

			size_type current;

		public:

			nik_ce stack() : base{}, current{base::null} { }

		protected:

			nik_ce size_type release() { return ++base::free; }

		public:

			nik_ce bool is_empty  () const { return base::is_null(current); }
			nik_ce bool not_empty () const { return base::not_null(current); }

			nik_ce bool is_full   () const { return base::is_model(current); }
			nik_ce bool not_full  () const { return base::not_model(current); }

			nik_ce ctype_ref operator * () const { return base::get_car(current); }

			nik_ce entry_ctype_ptr cbegin() const { return base::cbegin() + current; }

			nik_ce void push(ctype_ref v) { current = base::cons(v, current); }

			nik_ce void pull()
			{
				current = base::get_cdr(current);

				release();
			}

			nik_ce ctype_ref pop()
			{
				ctype_ref v = base::get_car(current);

				pull();

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

	template<typename Type>
	class inhabit : public stack<Type, unsigned char, 1> { };

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace engine

