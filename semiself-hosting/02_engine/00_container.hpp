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

namespace cctmp  {
namespace engine {

/***********************************************************************************************************************/
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
		using strlit_type = cctmp::string_literal<CharType, SizeType>;

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
		using strlit_type   = cctmp::string_literal<CharType, SizeType>;
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
		using strlit_type       = cctmp::string_literal<CharType, SizeType>;
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

			nik_ce ctype_ref value() const { return base::get_car(current); }

			nik_ce ctype_ref operator * () const { return value(); }

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

}} // namespace cctmp::engine

