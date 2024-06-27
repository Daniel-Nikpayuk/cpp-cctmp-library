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

namespace container {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
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
		using variable_type = sequence<strlit_type, SizeType, sizeof...(Bindings)>;

		variable_type variables;
		(variables.push(LambdaTuple::value<0>(bs)), ...);

		auto values = LambdaTuple::make(LambdaTuple::value<1>(bs)...);

		return LambdaTuple::make(variables, values);
	}

/***********************************************************************************************************************/

// instr:

	template<typename Type, typename SizeType>
	struct machine_instr : public sequence<Type, SizeType, MachineIndex::dimension>
	{
		using Index 		= MachineIndex;
		using base 		= sequence<Type, SizeType, Index::dimension>;

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
	struct machine_contr : public sequence<machine_instr<Type, SizeType>, SizeType, Size>
	{
		using instr_type	= machine_instr<Type, SizeType>;
		using base		= sequence<instr_type, SizeType, Size>;
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

	// design:

		// environment : abstract away from binding variables and values. Only keep indices that point
		//               to an external data structure.

		// variables   : for now, pair pointing to source string literal positions. Later, unicode.
		// values      : straticum.
		// state stack : pair stack, keep sizes of universe and stage (stage size for error checking).

			// is it worth encoding stack state info in the straticum as well ?
			// otherwise that info is lost, and so having the straticum as record
			// might become lossy.

/***********************************************************************************************************************/

	// instead of generic list, make specific varieties. Notably applications. Will we still require
	// an unknown (indeterminate?) application for when the operator is a non-trivial expression?
	// should we wrap atomic operators as compound? If so, how to correct for when it's not treated
	// as an operator but a value? How to return it from the main function?

	// if you do wrap atomic functions, you'd keep specialized instructions as the body of the compound.
	// you could assume 0 context, and the args would already be there so you could just push the atomic
	// operator to the front and apply.

	// if an application's operator is indeterminate, add a special instruction to compile time test
	// if atomic or compound, record it as a template parameter and dispatch accordingly during the apply?
	// is this the best possible solution?

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// straticum:

/***********************************************************************************************************************/
/***********************************************************************************************************************/



	// source:

	//	(define (main n)         
	//	  (define (sq m) (* m m))
	//	  (sq n)                 
	//	)                        

	// translates to:

	//	(begin
	//	  (define (body (apply-atomic (value [*]) (value [m]) (value [m]))))
	//	  (halt (apply-compound (value [sq]) (value [n])))
	//	)

	// more specifically:

	//	begin          : (define, 0) (halt, 0)
	//	define         : (apply-atomic, 0)
	//	apply-compound : ((value, 1) (value, 0))
	//	apply-atomic   : ((value, 3) (value, 2) (value, 2))
	//	halt           : (apply-compound, 0)
	//	value          : [n] [sq] [m] [*] 
	//			  0   1    2   3



/***********************************************************************************************************************/

// grammar:

	// indices:

	template<typename SizeType>
	struct Straticum
	{
		using size_type		= SizeType;
		using csize_type	= size_type const;

		struct Value
		{
			enum : size_type
			{
				ref_count, // atomic exprs.
				name, note, pos, num,
				dimension
			};
		};

		struct Assign // relationship to replace?
		{
			enum : size_type
			{
				ref_count, has_cond, has_set,
				var_pos, val_kind, val_expr,
				dimension
			};
		};

		struct Conditional
		{
			enum : size_type
			{
				ref_count, has_cond, has_set,
				pred_kind, pred_expr, ante_kind, ante_expr, conse_kind, conse_expr,
				dimension
			};
		};

		struct Sequence
		{
			enum : size_type
			{
				ref_count, has_cond, has_set,
				car_kind, car_expr, cdr_pos,
				dimension
			};
		};

		struct Atomic
		{
			enum : size_type
			{
				ref_count, has_cond, has_set,
				car_kind, car_expr, cdr_pos,
				dimension
			};
		};

		struct Compound
		{
			enum : size_type
			{
				ref_count, has_cond, has_set,
				car_kind, car_expr, cdr_pos,
				tag,
				dimension
			};
		};

		struct Define // two defines? One for functions, one for variables? Or use assign instead?
		{
			enum : size_type
			{
				ref_count, has_cond, has_set,
				uni_size, arity, port, body_kind, body_expr,
				tag,
				dimension
			};
		};

		struct Halt
		{
			enum : size_type
			{
				ref_count, has_cond, has_set,
				expr,
				dimension
			};
		};
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// entry:

/***********************************************************************************************************************/

// value:

	template<typename SizeType, SizeType Size = Straticum<SizeType>::Value::dimension>
	struct T_straticum_value : sequence<SizeType, Size>
	{
		using base		= sequence<SizeType, Size>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Index		= typename Straticum<size_type>::Value;

		nik_ce T_straticum_value() : base{} { }
	};

// assign:

	template<typename SizeType, SizeType Size = Straticum<SizeType>::Assign::dimension>
	struct T_straticum_assign : sequence<SizeType, Size>
	{
		using base		= sequence<SizeType, Size>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Index		= typename Straticum<size_type>::Assign;

		nik_ce T_straticum_assign() : base{} { }
	};

// conditional:

	template<typename SizeType, SizeType Size = Straticum<SizeType>::Conditional::dimension>
	struct T_straticum_conditional : sequence<SizeType, Size>
	{
		using base		= sequence<SizeType, Size>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Index		= typename Straticum<size_type>::Conditional;

		nik_ce T_straticum_conditional() : base{} { }
	};

// sequence:

	template<typename SizeType, SizeType Size = Straticum<SizeType>::Sequence::dimension>
	struct T_straticum_sequence : sequence<SizeType, Size>
	{
		using base		= sequence<SizeType, Size>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Index		= typename Straticum<size_type>::Sequence;

		nik_ce T_straticum_sequence() : base{} { }
	};

// atomic:

	template<typename SizeType, SizeType Size = Straticum<SizeType>::Atomic::dimension>
	struct T_straticum_atomic : sequence<SizeType, Size>
	{
		using base		= sequence<SizeType, Size>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Index		= typename Straticum<size_type>::Atomic;

		nik_ce T_straticum_atomic() : base{} { }
	};

// compound:

	template<typename SizeType, SizeType Size = Straticum<SizeType>::Compound::dimension>
	struct T_straticum_compound : sequence<SizeType, Size>
	{
		using base		= sequence<SizeType, Size>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Index		= typename Straticum<size_type>::Compound;

		nik_ce T_straticum_compound() : base{} { }
	};

// define:

	template<typename SizeType, SizeType Size = Straticum<SizeType>::Define::dimension>
	struct T_straticum_define : sequence<SizeType, Size>
	{
		using base		= sequence<SizeType, Size>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Index		= typename Straticum<size_type>::Define;

		nik_ce T_straticum_define() : base{} { }
	};

// halt:

	template<typename SizeType, SizeType Size = Straticum<SizeType>::Halt::dimension>
	struct T_straticum_halt : sequence<SizeType, Size>
	{
		using base		= sequence<SizeType, Size>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		using Index		= typename Straticum<size_type>::Halt;

		nik_ce T_straticum_halt() : base{} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// level:

/***********************************************************************************************************************/

// value:

	template<typename SizeType, SizeType Size>
	struct T_straticum_level_value : public sequence<T_straticum_value<SizeType>, Size>
	{
		using value_type	= T_straticum_value<SizeType>;
		using base		= sequence<value_type, Size>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		nik_ce T_straticum_level_value() : base{} { }

		// literal (boolean):

			nik_ce void push_literal_boolean(csize_type n)
			{
				base::push({ AN::literal , AT::boolean , n , 0 , 0 , 0 , 0 , 1 });
			}

		// literal (character):

			nik_ce void push_literal_character(csize_type n)
			{
				base::push({ AN::literal , AT::character , n , 0 , 0 , 0 , 0 , 1 });
			}

		// literal (n number):

			nik_ce void push_literal_n_number(csize_type n)
			{
				base::push({ AN::literal , AT::n_number , n , 0 , 0 , 0 , 0 , 1 });
			}

		// literal (r number):

			nik_ce void push_literal_r_number(csize_type n, csize_type m)
			{
				base::push({ AN::literal , AT::r_number , n , m , 0 , 0 , 0 , 1 });
			}

		// literal (t number):

			nik_ce void push_literal_t_number(csize_type n)
			{
				base::push({ AN::literal , AT::t_number , n , 0 , 0 , 0 , 0 , 1 });
			}

		// variable (universe):

			nik_ce void push_variable_universe(csize_type n)
			{
				base::push({ AN::variable , AT::universe , n , 0 , 0 , 0 , 0 , 1 });
			}

		// variable (lookup):

			nik_ce void push_variable_lookup()
			{
				base::push({ AN::variable , AT::lookup , 0 , 0 , 0 , 0 , 0 , 1 });
			}
	};

/***********************************************************************************************************************/

// conditional:

	template<typename SizeType, SizeType Size>
	struct T_straticum_level_conditional : public sequence<T_straticum_conditional<SizeType>, Size>
	{
		using value_type	= T_straticum_conditional<SizeType>;
		using base		= sequence<value_type, Size>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		nik_ce T_straticum_level_conditional() : base{} { }
	};

/***********************************************************************************************************************/

// sequence:

	template<typename SizeType, SizeType Size>
	struct T_straticum_level_sequence : public sequence<T_straticum_sequence<SizeType>, Size>
	{
		using value_type	= T_straticum_sequence<SizeType>;
		using base		= sequence<value_type, Size>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		nik_ce T_straticum_level_sequence() : base{} { }
	};

/***********************************************************************************************************************/

// atomic:

	template<typename SizeType, SizeType Size>
	struct T_straticum_level_atomic : public sequence<T_straticum_atomic<SizeType>, Size>
	{
		using value_type	= T_straticum_atomic<SizeType>;
		using base		= sequence<value_type, Size>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		nik_ce T_straticum_level_atomic() : base{} { }
	};

/***********************************************************************************************************************/

// compound:

	template<typename SizeType, SizeType Size>
	struct T_straticum_level_compound : public sequence<T_straticum_compound<SizeType>, Size>
	{
		using value_type	= T_straticum_compound<SizeType>;
		using base		= sequence<value_type, Size>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		nik_ce T_straticum_level_compound() : base{} { }
	};

/***********************************************************************************************************************/

// define:

	template<typename SizeType, SizeType Size>
	struct T_straticum_level_define : public sequence<T_straticum_define<SizeType>, Size>
	{
		using value_type	= T_straticum_define<SizeType>;
		using base		= sequence<value_type, Size>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		nik_ce T_straticum_level_define() : base{} { }
	};

/***********************************************************************************************************************/

// halt:

	template<typename SizeType, SizeType Size>
	struct T_straticum_level_halt : public sequence<T_straticum_halt<SizeType>, Size>
	{
		using value_type	= T_straticum_halt<SizeType>;
		using base		= sequence<value_type, Size>;
		using size_type		= typename base::size_type;
		using csize_type	= typename base::csize_type;

		nik_ce T_straticum_level_halt() : base{} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// space:

/***********************************************************************************************************************/

// assembly:

	template<typename SizeType, SizeType Size>
	struct T_straticum_assembly
	{
		using size_type			= SizeType;
		using csize_type		= size_type const;

		nik_ces size_type length	= Size;

		using level_value		= T_straticum_level_value       < size_type , length >;
		using level_conditional		= T_straticum_level_conditional < size_type , length >;
		using level_sequence		= T_straticum_level_sequence    < size_type , length >;
		using level_atomic		= T_straticum_level_atomic      < size_type , length >;
		using level_compound		= T_straticum_level_compound    < size_type , length >;
		using level_define		= T_straticum_level_define      < size_type , length >;
		using level_halt		= T_straticum_level_halt        < size_type , length >;

		level_value       value;
		level_conditional conditional;
		level_sequence    sequence;
		level_atomic      atomic;
		level_compound    compound;
		level_define      define;
		level_halt        halt;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace container

