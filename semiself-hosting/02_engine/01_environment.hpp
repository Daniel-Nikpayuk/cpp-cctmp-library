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

// environment:

namespace engine {

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
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// variable model:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// string:

/***********************************************************************************************************************/

// interface:

	template<typename SrcType, typename SizeType, SizeType Size>
	class T_model_variable_string_ref
	{
		public:

			using src_type		= SrcType;
			using src_citer		= typename src_type::ctype_cptr;
			using csrc_type		= src_type const;
			using csrc_ref		= csrc_type &;

			using variable_type	= SizeType;
			using cvariable_type	= variable_type const;

			using size_type		= SizeType;
			using csize_type	= size_type const;

			using seq_type		= cctmp::sequence<variable_type, size_type, Size>;

			using inhabit_type	= T_inhabit<size_type>;
			using cinhabit_type	= inhabit_type const;

		protected:

			seq_type initial;
			seq_type terminal;

			csrc_ref src;

		public:

			nik_ce T_model_variable_string_ref(csrc_ref s) : src{s} { }

			nik_ce csize_type current() const { return initial.max(); }

			nik_ce void push(cvariable_type b, cvariable_type e)
			{
				initial.push(b);
				terminal.push(e);
			}

		protected:

			nik_ce src_citer citerator(csize_type n) const { return src.origin() + n; }

			template<typename Iterator>
			nik_ce const bool csame(csize_type n, Iterator b) const
			{
				src_citer begin = citerator(initial  [n]);
				src_citer end   = citerator(terminal [n]);

				return inventory_same_v0<size_type>(begin, end, b);
			}

		public:

			template<typename T>
			nik_ce const bool same(csize_type n, const T & variable) const
				{ return csame(n, variable.cbegin()); }

		protected:

			nik_ce const bool find_same(inhabit_type & match, src_citer b, csize_type k) const
			{
				if (csame(k, b)) match.push(k);

				return match.not_empty();
			}

		public:

			nik_ce cinhabit_type find(cvariable_type b) const
			{
				inhabit_type match;

				for (auto k = 0; k != initial.size(); ++k)
					if (find_same(match, citerator(b), k)) break;

				return match;
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// value model:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// number:

/***********************************************************************************************************************/

// interface:

	template<typename NumType, typename SizeType, SizeType Size>
	class T_model_value_number
	{
		public:

			using value_type	= NumType;
			using cvalue_type	= value_type const;

			using size_type		= SizeType;
			using csize_type	= size_type const;

			using seq_type		= cctmp::sequence<value_type, size_type, Size>;

			using inhabit_type	= T_inhabit<size_type>;
			using cinhabit_type	= inhabit_type const;

		protected:

			seq_type seq;

		public:

			nik_ce T_model_value_number() { }

			nik_ce csize_type current() const { return seq.max(); }

			nik_ce cvalue_type operator [] (csize_type n) const { return seq[n]; }

			nik_ce void push(cvalue_type v) { seq.push(v); }

		protected:

			nik_ce const bool find_same(inhabit_type & match, cvalue_type v, csize_type k) const
			{
				if (seq[k] == v) match.push(k);

				return match.not_empty();
			}

		public:

			nik_ce cinhabit_type find(cvalue_type v) const
			{
				inhabit_type match;

				for (auto k = 0; k != seq.size(); ++k)
					if (find_same(match, v, k)) break;

				return match;
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// straticum:

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

// entry:

	// value:

		template<typename SizeType, SizeType Size = Straticum<SizeType>::Value::dimension>
		struct T_straticum_value : public cctmp::sequence<SizeType, SizeType, Size>
		{
			using base		= cctmp::sequence<SizeType, SizeType, Size>;
			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

			using Index		= typename Straticum<size_type>::Value;

			nik_ce T_straticum_value() : base{} { }
		};

	// assign:

		template<typename SizeType, SizeType Size = Straticum<SizeType>::Assign::dimension>
		struct T_straticum_assign : public cctmp::sequence<SizeType, SizeType, Size>
		{
			using base		= cctmp::sequence<SizeType, SizeType, Size>;
			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

			using Index		= typename Straticum<size_type>::Assign;

			nik_ce T_straticum_assign() : base{} { }
		};

	// conditional:

		template<typename SizeType, SizeType Size = Straticum<SizeType>::Conditional::dimension>
		struct T_straticum_conditional : public cctmp::sequence<SizeType, SizeType, Size>
		{
			using base		= cctmp::sequence<SizeType, SizeType, Size>;
			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

			using Index		= typename Straticum<size_type>::Conditional;

			nik_ce T_straticum_conditional() : base{} { }
		};

	// sequence:

		template<typename SizeType, SizeType Size = Straticum<SizeType>::Sequence::dimension>
		struct T_straticum_sequence : public cctmp::sequence<SizeType, SizeType, Size>
		{
			using base		= cctmp::sequence<SizeType, SizeType, Size>;
			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

			using Index		= typename Straticum<size_type>::Sequence;

			nik_ce T_straticum_sequence() : base{} { }
		};

	// atomic:

		template<typename SizeType, SizeType Size = Straticum<SizeType>::Atomic::dimension>
		struct T_straticum_atomic : public cctmp::sequence<SizeType, SizeType, Size>
		{
			using base		= cctmp::sequence<SizeType, SizeType, Size>;
			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

			using Index		= typename Straticum<size_type>::Atomic;

			nik_ce T_straticum_atomic() : base{} { }
		};

	// compound:

		template<typename SizeType, SizeType Size = Straticum<SizeType>::Compound::dimension>
		struct T_straticum_compound : public cctmp::sequence<SizeType, SizeType, Size>
		{
			using base		= cctmp::sequence<SizeType, SizeType, Size>;
			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

			using Index		= typename Straticum<size_type>::Compound;

			nik_ce T_straticum_compound() : base{} { }
		};

	// define:

		template<typename SizeType, SizeType Size = Straticum<SizeType>::Define::dimension>
		struct T_straticum_define : public cctmp::sequence<SizeType, SizeType, Size>
		{
			using base		= cctmp::sequence<SizeType, SizeType, Size>;
			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

			using Index		= typename Straticum<size_type>::Define;

			nik_ce T_straticum_define() : base{} { }
		};

	// halt:

		template<typename SizeType, SizeType Size = Straticum<SizeType>::Halt::dimension>
		struct T_straticum_halt : public cctmp::sequence<SizeType, SizeType, Size>
		{
			using base		= cctmp::sequence<SizeType, SizeType, Size>;
			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

			using Index		= typename Straticum<size_type>::Halt;

			nik_ce T_straticum_halt() : base{} { }
		};

/***********************************************************************************************************************/

// level:

	// value:

		template<typename SizeType, SizeType Size>
		struct T_straticum_level_value : public cctmp::sequence<T_straticum_value<SizeType>, SizeType, Size>
		{
			using value_type	= T_straticum_value<SizeType>;
			using base		= cctmp::sequence<value_type, SizeType, Size>;
			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

			nik_ce T_straticum_level_value() : base{} { }

			// literal (boolean):

				nik_ce void push_literal_boolean(csize_type n)
				{
					base::push({ MN::literal , MT::boolean , n , 0 , 0 , 0 , 0 , 1 });
				}

			// literal (character):

				nik_ce void push_literal_character(csize_type n)
				{
					base::push({ MN::literal , MT::character , n , 0 , 0 , 0 , 0 , 1 });
				}

			// literal (n number):

				nik_ce void push_literal_n_number(csize_type n)
				{
					base::push({ MN::literal , MT::n_number , n , 0 , 0 , 0 , 0 , 1 });
				}

			// literal (r number):

				nik_ce void push_literal_r_number(csize_type n, csize_type m)
				{
					base::push({ MN::literal , MT::r_number , n , m , 0 , 0 , 0 , 1 });
				}

			// literal (t number):

				nik_ce void push_literal_t_number(csize_type n)
				{
					base::push({ MN::literal , MT::t_number , n , 0 , 0 , 0 , 0 , 1 });
				}

			// variable (universe):

				nik_ce void push_variable_universe(csize_type n)
				{
					base::push({ MN::variable , MT::universe , n , 0 , 0 , 0 , 0 , 1 });
				}

			// variable (lookup):

				nik_ce void push_variable_lookup()
				{
					base::push({ MN::variable , MT::lookup , 0 , 0 , 0 , 0 , 0 , 1 });
				}
		};

	// conditional:

		template<typename SizeType, SizeType Size>
		struct T_straticum_level_conditional : public cctmp::sequence<T_straticum_conditional<SizeType>, SizeType, Size>
		{
			using value_type	= T_straticum_conditional<SizeType>;
			using base		= cctmp::sequence<value_type, SizeType, Size>;
			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

			nik_ce T_straticum_level_conditional() : base{} { }
		};

	// sequence:

		template<typename SizeType, SizeType Size>
		struct T_straticum_level_sequence : public cctmp::sequence<T_straticum_sequence<SizeType>, SizeType, Size>
		{
			using value_type	= T_straticum_sequence<SizeType>;
			using base		= cctmp::sequence<value_type, SizeType, Size>;
			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

			nik_ce T_straticum_level_sequence() : base{} { }
		};

	// atomic:

		template<typename SizeType, SizeType Size>
		struct T_straticum_level_atomic : public cctmp::sequence<T_straticum_atomic<SizeType>, SizeType, Size>
		{
			using value_type	= T_straticum_atomic<SizeType>;
			using base		= cctmp::sequence<value_type, SizeType, Size>;
			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

			nik_ce T_straticum_level_atomic() : base{} { }
		};

	// compound:

		template<typename SizeType, SizeType Size>
		struct T_straticum_level_compound : public cctmp::sequence<T_straticum_compound<SizeType>, SizeType, Size>
		{
			using value_type	= T_straticum_compound<SizeType>;
			using base		= cctmp::sequence<value_type, SizeType, Size>;
			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

			nik_ce T_straticum_level_compound() : base{} { }
		};

	// define:

		template<typename SizeType, SizeType Size>
		struct T_straticum_level_define : public cctmp::sequence<T_straticum_define<SizeType>, SizeType, Size>
		{
			using value_type	= T_straticum_define<SizeType>;
			using base		= cctmp::sequence<value_type, SizeType, Size>;
			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

			nik_ce T_straticum_level_define() : base{} { }
		};

	// halt:

		template<typename SizeType, SizeType Size>
		struct T_straticum_level_halt : public cctmp::sequence<T_straticum_halt<SizeType>, SizeType, Size>
		{
			using value_type	= T_straticum_halt<SizeType>;
			using base		= cctmp::sequence<value_type, SizeType, Size>;
			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;

			nik_ce T_straticum_level_halt() : base{} { }
		};

/***********************************************************************************************************************/

// interface:

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

// environment model:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// scheme:

/***********************************************************************************************************************/

// interface:

	template<typename SizeType, SizeType EnvSize, SizeType FrameSize>
	struct T_model_environment_scheme : public T_list_model<SizeType, 2*(EnvSize + FrameSize)>
	{
		public:

			using base		= T_list_model<SizeType, 2*(EnvSize + FrameSize)>;
			using size_type		= typename base::size_type;
			using csize_type	= typename base::csize_type;
			using Entry		= typename base::Entry;

			using inhabit_type	= T_inhabit<size_type>;
			using cinhabit_type	= inhabit_type const;

		protected:

			size_type current;

		public:

			nik_ce T_model_environment_scheme() : base{}, current{base::null} { }

		protected:

			// frame:

				nik_ce csize_type    null_frame () const { return base::null; }
				nik_ce csize_type current_frame () const { return base::car(current); }

			// binding:

				nik_ce csize_type make_binding(csize_type variable, csize_type value)
				{
					csize_type binding = base::allocate();

					base::set_value(binding, Entry::car, variable);
					base::set_value(binding, Entry::cdr, value   );

					return binding;
				}

			// value:

				template<typename Model, typename T>
				nik_ce const bool find_binding(inhabit_type & match,
					csize_type binding, const Model & model, const T & variable)
				{
					if (model.same(base::car(binding), variable))
						match.push(base::cdr(binding));

					return match.not_empty();
				}

				template<typename Model, typename T>
				nik_ce const bool find_frame(inhabit_type & match,
					csize_type frame, const Model & model, const T & variable)
				{
					for (size_type fr = frame; fr != base::null; fr = base::cdr(fr))
						if (find_binding(match, base::car(fr), model, variable)) break;

					return match.not_empty();
				}

		public:

			// env:

				nik_ce void push_frame() { current = base::cons(null_frame(), current); }

			// binding:

				nik_ce void push_binding(csize_type variable, csize_type value)
				{
					csize_type binding = make_binding(variable, value);
					csize_type frame   = base::cons(binding, current_frame());

					base::set_value(current, Entry::car, frame);
				}

			// value:

				template<typename Model, typename T>
				nik_ce cinhabit_type find_value(const Model & model, const T & variable)
				{
					inhabit_type match;

					for (size_type env = current; env != base::null; env = base::cdr(env))
						if (find_frame(match, base::car(env), model, variable)) break;

					return match;
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// string value:

/***********************************************************************************************************************/

// str(ing) val(ue):

	template<typename SrcType, typename NumType, typename SizeType, SizeType EnvSize, SizeType FrameSize>
	class T_model_environment_string_ref_number
	{
		public:

			using src_type			= SrcType;
			using csrc_type			= src_type const;
			using csrc_ref			= csrc_type &;

			using size_type			= SizeType;
			using csize_type		= size_type const;

			using variable_model		= T_model_variable_string_ref <  src_type, size_type, FrameSize >;
			using value_model		= T_model_value_number        <   NumType, size_type, FrameSize >;
			using env_model			= T_model_environment_scheme  < size_type,   EnvSize, FrameSize >;

			using cvariable_type		= typename variable_model::cvariable_type;
			using cvalue_type		= typename value_model::cvalue_type;
			using cinhabit_type		= typename env_model::cinhabit_type;
			using cinhabit_ref		= cinhabit_type &;

		protected:

			variable_model variable;
			value_model value;
			env_model env;

		public:

			nik_ce T_model_environment_string_ref_number(csrc_ref s) : variable{s} { env.push_frame(); }

		protected:

			nik_ce csize_type maybe_push_variable(cinhabit_ref record, cvariable_type b, cvariable_type e)
			{
				if (record.not_empty()) return *record;
				else variable.push(b, e);

				return variable.current();
			}

			nik_ce csize_type maybe_push_value(cinhabit_ref record, cvalue_type v)
			{
				if (record.not_empty()) return *record;
				else value.push(v);

				return value.current();
			}

		public:

			nik_ce void push_binding(cvariable_type b, cvariable_type e, cvalue_type v)
			{
				env.push_binding
				(
					maybe_push_variable (variable.find(b), b, e),
					maybe_push_value    (value.find(v), v)
				);
			}

			template<typename T>
			nik_ce cinhabit_type find_value(const T & var) { return env.find_value(variable, var); }

			nik_ce cvalue_type get_value(cinhabit_ref record) { return value[*record]; }

			nik_ce void set_value(cinhabit_ref record, cvalue_type v) { value[*record] = v; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// string straticum:

/***********************************************************************************************************************/

// str(ing) strat(icum):

	struct T_model_environment_string_ref_straticum
	{
		nik_ce T_model_environment_string_ref_straticum() { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace engine

