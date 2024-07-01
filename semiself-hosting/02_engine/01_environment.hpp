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

	// design:

		// environment : abstract away from binding variables and values. Only keep indices that point
		//               to an external data structure.

		// variables   : for now, pair pointing to source string literal positions. Later, unicode.
		// values      : straticum.
		// state stack : pair stack, keep sizes of universe and stage (stage size for error checking).

			// is it worth encoding stack state info in the straticum as well ?
			// otherwise that info is lost, and so having the straticum as record
			// might become lossy.

namespace engine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// model:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// expression:

/***********************************************************************************************************************/

// interface:

	template<typename Type, typename SizeType, SizeType WordSize, SizeType Size>
	class model_expression
	{
		public:

			using type		= Type;
			using ctype		= type const;
			using ctype_ref		= ctype &;
			using ctype_ptr		= ctype *;
			using ctype_cptr	= ctype_ptr const;

			using size_type		= SizeType;
			using size_ctype	= size_type const;

			using expr_type		= cctmp::sequence<      type , size_type ,     Size >;
			using word_type		= cctmp::sequence< size_type , size_type , WordSize >;

			using inhabit_type	= inhabit<size_type>;
			using inhabit_ctype	= inhabit_type const;

		protected:

			expr_type expression;
			word_type word_init;
			word_type word_term;

		public:

			nik_ce model_expression() { }

			nik_ce size_type current_word() const { return word_init.max(); }

			template<typename In, typename End>
			nik_ce void push(In in, End end)
			{
				word_init.push(expression.size());

				while (in != end) expression.push(*in++);

				word_term.push(expression.size());
			}

			template<typename In1>
			nik_ce bool same(size_ctype n, In1 in1) const
			{
				ctype_ptr in  = expression.citer(word_init[n]);
				ctype_ptr end = expression.citer(word_term[n]);

				return inventory_same_v0<size_type>(in, end, in1);
			}

		protected:

			template<typename In1>
			nik_ce bool find_same(inhabit_type & match, size_ctype n, In1 in1) const
			{
				if (same(n, in1)) match.push(n);

				return match.not_empty();
			}

		public:

			template<typename In1>
			nik_ce inhabit_type find(In1 in1) const
			{
				inhabit_type match;

				for (auto k = 0; k != word_init.size(); ++k)
					if (find_same(match, k, in1)) break;

				return match;
			}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// variable model:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// string sel(ection):

/***********************************************************************************************************************/

// interface:

	template<typename CharType, typename SizeType, SizeType WordSize, SizeType Size>
	struct model_variable_string : public model_expression<CharType, SizeType, WordSize, Size>
	{
		using base			= model_expression<CharType, SizeType, WordSize, Size>;

		using variable_type		= typename base::type;
		using variable_ctype		= typename base::ctype;
		using variable_ctype_ref	= typename base::ctype_ref;
		using variable_ctype_ptr	= typename base::ctype_ptr;
		using variable_ctype_cptr	= typename base::ctype_cptr;

		using size_type			= typename base::size_type;
		using size_ctype		= typename base::size_ctype;

		using expr_type			= typename base::expr_type;
		using word_type			= typename base::word_type;

		using inhabit_type		= typename base::inhabit_type;
		using inhabit_ctype		= typename base::inhabit_ctype;
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
	class model_value_number
	{
		public:

			using value_type	= NumType;
			using value_ctype	= value_type const;

			using size_type		= SizeType;
			using size_ctype	= size_type const;

			using seq_type		= cctmp::sequence<value_type, size_type, Size>;

			using inhabit_type	= inhabit<size_type>;
			using inhabit_ctype	= inhabit_type const;

		protected:

			seq_type seq;

		public:

			nik_ce model_value_number() { }

			nik_ce size_type current_word() const { return seq.max(); }

			nik_ce value_type operator [] (size_ctype n) const { return seq[n]; }

			nik_ce void push(value_ctype v) { seq.push(v); }

		protected:

			nik_ce bool find_same(inhabit_type & match, value_ctype v, size_ctype k) const
			{
				if (seq[k] == v) match.push(k);

				return match.not_empty();
			}

		public:

			nik_ce inhabit_type find(value_ctype v) const
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
		using size_ctype	= size_type const;

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
			using size_ctype	= typename base::size_ctype;

			using Index		= typename Straticum<size_type>::Value;

			nik_ce T_straticum_value() : base{} { }
		};

	// assign:

		template<typename SizeType, SizeType Size = Straticum<SizeType>::Assign::dimension>
		struct T_straticum_assign : public cctmp::sequence<SizeType, SizeType, Size>
		{
			using base		= cctmp::sequence<SizeType, SizeType, Size>;
			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

			using Index		= typename Straticum<size_type>::Assign;

			nik_ce T_straticum_assign() : base{} { }
		};

	// conditional:

		template<typename SizeType, SizeType Size = Straticum<SizeType>::Conditional::dimension>
		struct T_straticum_conditional : public cctmp::sequence<SizeType, SizeType, Size>
		{
			using base		= cctmp::sequence<SizeType, SizeType, Size>;
			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

			using Index		= typename Straticum<size_type>::Conditional;

			nik_ce T_straticum_conditional() : base{} { }
		};

	// sequence:

		template<typename SizeType, SizeType Size = Straticum<SizeType>::Sequence::dimension>
		struct T_straticum_sequence : public cctmp::sequence<SizeType, SizeType, Size>
		{
			using base		= cctmp::sequence<SizeType, SizeType, Size>;
			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

			using Index		= typename Straticum<size_type>::Sequence;

			nik_ce T_straticum_sequence() : base{} { }
		};

	// atomic:

		template<typename SizeType, SizeType Size = Straticum<SizeType>::Atomic::dimension>
		struct T_straticum_atomic : public cctmp::sequence<SizeType, SizeType, Size>
		{
			using base		= cctmp::sequence<SizeType, SizeType, Size>;
			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

			using Index		= typename Straticum<size_type>::Atomic;

			nik_ce T_straticum_atomic() : base{} { }
		};

	// compound:

		template<typename SizeType, SizeType Size = Straticum<SizeType>::Compound::dimension>
		struct T_straticum_compound : public cctmp::sequence<SizeType, SizeType, Size>
		{
			using base		= cctmp::sequence<SizeType, SizeType, Size>;
			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

			using Index		= typename Straticum<size_type>::Compound;

			nik_ce T_straticum_compound() : base{} { }
		};

	// define:

		template<typename SizeType, SizeType Size = Straticum<SizeType>::Define::dimension>
		struct T_straticum_define : public cctmp::sequence<SizeType, SizeType, Size>
		{
			using base		= cctmp::sequence<SizeType, SizeType, Size>;
			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

			using Index		= typename Straticum<size_type>::Define;

			nik_ce T_straticum_define() : base{} { }
		};

	// halt:

		template<typename SizeType, SizeType Size = Straticum<SizeType>::Halt::dimension>
		struct T_straticum_halt : public cctmp::sequence<SizeType, SizeType, Size>
		{
			using base		= cctmp::sequence<SizeType, SizeType, Size>;
			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

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
			using size_ctype	= typename base::size_ctype;

			nik_ce T_straticum_level_value() : base{} { }

			// literal (boolean):

				nik_ce void push_literal_boolean(size_ctype n)
				{
					base::push({ MN::literal , MT::boolean , n , 0 , 0 , 0 , 0 , 1 });
				}

			// literal (character):

				nik_ce void push_literal_character(size_ctype n)
				{
					base::push({ MN::literal , MT::character , n , 0 , 0 , 0 , 0 , 1 });
				}

			// literal (n number):

				nik_ce void push_literal_n_number(size_ctype n)
				{
					base::push({ MN::literal , MT::n_number , n , 0 , 0 , 0 , 0 , 1 });
				}

			// literal (r number):

				nik_ce void push_literal_r_number(size_ctype n, size_ctype m)
				{
					base::push({ MN::literal , MT::r_number , n , m , 0 , 0 , 0 , 1 });
				}

			// literal (t number):

				nik_ce void push_literal_t_number(size_ctype n)
				{
					base::push({ MN::literal , MT::t_number , n , 0 , 0 , 0 , 0 , 1 });
				}

			// variable (universe):

				nik_ce void push_variable_universe(size_ctype n)
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
			using size_ctype	= typename base::size_ctype;

			nik_ce T_straticum_level_conditional() : base{} { }
		};

	// sequence:

		template<typename SizeType, SizeType Size>
		struct T_straticum_level_sequence : public cctmp::sequence<T_straticum_sequence<SizeType>, SizeType, Size>
		{
			using value_type	= T_straticum_sequence<SizeType>;
			using base		= cctmp::sequence<value_type, SizeType, Size>;
			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

			nik_ce T_straticum_level_sequence() : base{} { }
		};

	// atomic:

		template<typename SizeType, SizeType Size>
		struct T_straticum_level_atomic : public cctmp::sequence<T_straticum_atomic<SizeType>, SizeType, Size>
		{
			using value_type	= T_straticum_atomic<SizeType>;
			using base		= cctmp::sequence<value_type, SizeType, Size>;
			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

			nik_ce T_straticum_level_atomic() : base{} { }
		};

	// compound:

		template<typename SizeType, SizeType Size>
		struct T_straticum_level_compound : public cctmp::sequence<T_straticum_compound<SizeType>, SizeType, Size>
		{
			using value_type	= T_straticum_compound<SizeType>;
			using base		= cctmp::sequence<value_type, SizeType, Size>;
			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

			nik_ce T_straticum_level_compound() : base{} { }
		};

	// define:

		template<typename SizeType, SizeType Size>
		struct T_straticum_level_define : public cctmp::sequence<T_straticum_define<SizeType>, SizeType, Size>
		{
			using value_type	= T_straticum_define<SizeType>;
			using base		= cctmp::sequence<value_type, SizeType, Size>;
			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

			nik_ce T_straticum_level_define() : base{} { }
		};

	// halt:

		template<typename SizeType, SizeType Size>
		struct T_straticum_level_halt : public cctmp::sequence<T_straticum_halt<SizeType>, SizeType, Size>
		{
			using value_type	= T_straticum_halt<SizeType>;
			using base		= cctmp::sequence<value_type, SizeType, Size>;
			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;

			nik_ce T_straticum_level_halt() : base{} { }
		};

/***********************************************************************************************************************/

// interface:

	template<typename SizeType, SizeType Size>
	struct T_straticum_assembly
	{
		using size_type			= SizeType;
		using size_ctype		= size_type const;

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

// (scheme):

	// size of { binding, frame, env } == 2 array positions.
	// worst case scenario: each env has exactly one frame, each frame has exactly one binding.
	// max size == 2*(binding size) + 2*(binding size) 2*(binding size) == 6*(binding size)

/***********************************************************************************************************************/

// interface:

	template<typename SizeType, SizeType WordSize>
	struct model_environment : public model_list<SizeType, 6*WordSize>
	{
		public:

			using base		= model_list<SizeType, 6*WordSize>;
			using size_type		= typename base::size_type;
			using size_ctype	= typename base::size_ctype;
			using Entry		= typename base::Entry;

			using inhabit_type	= inhabit<size_type>;
			using inhabit_ctype	= inhabit_type const;

		protected:

			size_type current;

		public:

			nik_ce model_environment() : base{}, current{base::null} { }

		protected:

			// frame:

				nik_ce size_type    null_frame () const { return base::null; }
				nik_ce size_type current_frame () const { return base::car(current); }

			// binding:

				nik_ce size_type make_binding(size_ctype variable, size_ctype value)
				{
					size_ctype binding = base::allocate();

					base::set_value(binding, Entry::car, variable);
					base::set_value(binding, Entry::cdr, value   );

					return binding;
				}

			// value:

				template<typename Model, typename In>
				nik_ce bool find_binding(inhabit_type & match,
					size_ctype binding, const Model & model, In in) const
				{
					if (model.same(base::car(binding), in))
						match.push(base::cdr(binding));

					return match.not_empty();
				}

				template<typename Model, typename In>
				nik_ce bool find_frame(inhabit_type & match,
					size_ctype frame, const Model & model, In in) const
				{
					for (size_type fr = frame; fr != base::null; fr = base::cdr(fr))
						if (find_binding(match, base::car(fr), model, in)) break;

					return match.not_empty();
				}

		public:

			// env:

				nik_ce void push_frame() { current = base::cons(null_frame(), current); }

			// binding:

				nik_ce void push_binding(size_ctype variable, size_ctype value)
				{
					size_ctype binding = make_binding(variable, value);
					size_ctype frame   = base::cons(binding, current_frame());

					base::set_value(current, Entry::car, frame);
				}

			// value:

				template<typename Model, typename In>
				nik_ce inhabit_type find_value(const Model & model, In in) const
				{
					inhabit_type match;

					for (size_type env = current; env != base::null; env = base::cdr(env))
						if (find_frame(match, base::car(env), model, in)) break;

					return match;
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// string value:

/***********************************************************************************************************************/

// str(ing) val(ue):

	template<typename CharType, typename NumType , typename SizeType, SizeType WordSize, SizeType VarSize>
	class model_environment_string_number
	{
		public:

			using char_type			= CharType;
			using num_type			= NumType;

			using size_type			= SizeType;
			using size_ctype		= size_type const;

			using variable_model		= model_variable_string < char_type, size_type, WordSize , VarSize >;
			using value_model		= model_value_number    <  num_type, size_type, WordSize >;
			using env_model			= model_environment     <            size_type, WordSize >;

			using value_type		= typename value_model::value_type;
			using value_ctype		= typename value_model::value_ctype;
			using inhabit_type		= typename env_model::inhabit_type;
			using inhabit_ctype		= typename env_model::inhabit_ctype;
			using inhabit_ctype_ref		= inhabit_ctype &;

		protected:

			variable_model variable;
			value_model value;
			env_model env;

		public:

			nik_ce model_environment_string_number() { env.push_frame(); }

		protected:

			template<typename In, typename End>
			nik_ce size_type maybe_push_variable(inhabit_ctype_ref record, In in, End end)
			{
				if (record.not_empty()) return *record;
				else variable.push(in, end);

				return variable.current_word();
			}

			nik_ce size_type maybe_push_value(inhabit_ctype_ref record, value_ctype v)
			{
				if (record.not_empty()) return *record;
				else value.push(v);

				return value.current_word();
			}

		public:

			template<typename In, typename End>
			nik_ce void push_binding(In in, End end, value_ctype v)
			{
				env.push_binding
				(
					maybe_push_variable (variable.find(in), in, end),
					maybe_push_value    (value.find(v), v)
				);
			}

			template<typename In>
			nik_ce inhabit_type find_value(In in) const { return env.find_value(variable, in); }

			nik_ce value_type get_value(inhabit_ctype_ref record) const { return value[*record]; }

			nik_ce void set_value(inhabit_ctype_ref record, value_ctype v) { value[*record] = v; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// string straticum:

/***********************************************************************************************************************/

// str(ing) strat(icum):

	struct model_environment_string_straticum
	{
		nik_ce model_environment_string_straticum() { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace engine

