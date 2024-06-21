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

// engine:

namespace assembly {

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

} // namespace assembly

