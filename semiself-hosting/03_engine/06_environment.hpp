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
		// values      : expression.
		// state stack : pair stack, keep sizes of universe and stage (stage size for error checking).

			// is it worth encoding stack state info in the expression as well ?
			// otherwise that info is lost, and so having the expression as record
			// might become lossy.

namespace cctmp  {
namespace engine {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// model:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// symbol:

/***********************************************************************************************************************/

// interface:

/*
	template<typename Type, typename SizeType, SizeType WordSize, SizeType Size>
	class model_symbol // derive from plot.
	{
		public:

			using type		= typename using_type<Type>::type;
			using type_ptr		= typename using_type<Type>::type_ptr;
			using type_cptr		= typename using_type<Type>::type_cptr;
			using type_ref		= typename using_type<Type>::type_ref;

			using ctype		= typename using_type<Type>::ctype;
			using ctype_ptr		= typename using_type<Type>::ctype_ptr;
			using ctype_cptr	= typename using_type<Type>::ctype_cptr;
			using ctype_ref		= typename using_type<Type>::ctype_ref;

			using size_type		= typename using_size<SizeType>::type;
			using size_ctype	= typename using_size<SizeType>::ctype;

			using word_type		= array< size_type , size_type , WordSize >;
			using symbol_type	= array<      type , size_type ,     Size >;

			using inhabit_type	= inhabit<size_type>;
			using inhabit_ctype	= inhabit_type const;

		protected:

			word_type word_init;
			word_type word_term;
			symbol_type symbol;

		public:

			nik_ce model_symbol() { }

			nik_ce size_type current_word() const { return word_init.max(); }

			template<typename In, typename End>
			nik_ce void push(In in, End end)
			{
				word_init.push(symbol.size());

				while (in != end) symbol.push(*in++);

				word_term.push(symbol.size());
			}

			template<typename T, auto N>
			nik_ce void push(const T (&s)[N]) { push(s, s + N); }

			template<typename In1>
			nik_ce bool same(size_ctype n, In1 in1) const
			{
				ctype_ptr in  = symbol.citer(word_init[n]);
				ctype_ptr end = symbol.citer(word_term[n]);

				for (; in != end; ++in, ++in1) if (*in != *in1) break;

				return (in == end);
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
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// number:

/***********************************************************************************************************************/

// interface:

/*
	template<typename NumType, typename SizeType, SizeType Size>
	class model_number
	{
		public:

			using type		= NumType;
			using ctype		= type const;

			using size_type		= SizeType;
			using size_ctype	= size_type const;

			using seq_type		= array<type, size_type, Size>;

			using inhabit_type	= inhabit<size_type>;
			using inhabit_ctype	= inhabit_type const;

		protected:

			seq_type seq;

		public:

			nik_ce model_number() { }

			nik_ce size_type current_word() const { return seq.max(); }

			nik_ce type operator [] (size_ctype n) const { return seq[n]; }

			nik_ce void push(ctype v) { seq.push(v); }

		protected:

			nik_ce bool find_same(inhabit_type & match, ctype v, size_ctype k) const
			{
				if (seq[k] == v) match.push(k);

				return match.not_empty();
			}

		public:

			nik_ce inhabit_type find(ctype v) const
			{
				inhabit_type match;

				for (auto k = 0; k != seq.size(); ++k)
					if (find_same(match, v, k)) break;

				return match;
			}
	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// expression:

/***********************************************************************************************************************/

// symbol:

	// value:

/*
		template<typename SizeType>
		struct SymbolValue
		{
			using size_type		= SizeType;
			using size_ctype	= size_type const;

			struct Index
			{
				enum : size_type
				{
					ref_count, // atomic exprs.
					name, note, pos, num,
					dimension
				};
			};

			// literal (boolean):

				template<typename Model>
				nik_ces void push_literal_boolean(Model *model, size_ctype n)
					{ model->value.push({ MN::literal, MT::boolean, n }); }

			// literal (character):

				template<typename Model>
				nik_ces void push_literal_character(Model *model, size_ctype n)
					{ model->value.push({ MN::literal, MT::character, n }); }

			// literal (n number):

				template<typename Model>
				nik_ces void push_literal_n_number(Model *model, size_ctype n)
					{ model->value.push({ MN::literal, MT::n_number, n }); }

			// literal (r number):

				template<typename Model>
				nik_ces void push_literal_r_number(Model *model, size_ctype n, size_ctype m)
					{ model->value.push({ MN::literal, MT::r_number, n, m }); }

			// literal (t number):

				template<typename Model>
				nik_ces void push_literal_t_number(Model *model, size_ctype n)
					{ model->value.push({ MN::literal, MT::t_number, n }); }

			// variable (universe):

				template<typename Model>
				nik_ces void push_variable_universe(Model *model, size_ctype n)
					{ model->value.push({ MN::variable, MT::universe , n }); }

			// variable (lookup):

				template<typename Model>
				nik_ces void push_variable_lookup(Model *model)
					{ model->value.push({ MN::variable, MT::lookup }); }
		};

	// assign:

		template<typename SizeType>
		struct SymbolAssign // relationship to replace?
		{
			using size_type		= SizeType;
			using size_ctype	= size_type const;

			struct Index
			{
				enum : size_type
				{
					ref_count, has_cond, has_set,
					var_pos, val_kind, val_expr,
					dimension
				};
			};
		};

	// conditional:

		template<typename SizeType>
		struct SymbolConditional
		{
			using size_type		= SizeType;
			using size_ctype	= size_type const;

			struct Index
			{
				enum : size_type
				{
					ref_count, has_cond, has_set,
					pred_kind, pred_expr, ante_kind, ante_expr, conse_kind, conse_expr,
					dimension
				};
			};
		};

	// sequence:

		template<typename SizeType>
		struct SymbolSequence
		{
			using size_type		= SizeType;
			using size_ctype	= size_type const;

			struct Index
			{
				enum : size_type
				{
					ref_count, has_cond, has_set,
					car_kind, car_expr, cdr_pos,
					dimension
				};
			};
		};

	// atomic:

		template<typename SizeType>
		struct SymbolAtomic
		{
			using size_type		= SizeType;
			using size_ctype	= size_type const;

			struct Index
			{
				enum : size_type
				{
					ref_count, has_cond, has_set,
					car_kind, car_expr, cdr_pos,
					dimension
				};
			};
		};

	// compound:

		template<typename SizeType>
		struct SymbolCompound
		{
			using size_type		= SizeType;
			using size_ctype	= size_type const;

			struct Index
			{
				enum : size_type
				{
					ref_count, has_cond, has_set,
					car_kind, car_expr, cdr_pos,
					tag,
					dimension
				};
			};
		};

	// define:

		template<typename SizeType>
		struct SymbolDefine
		{
			using size_type		= SizeType;
			using size_ctype	= size_type const;

			struct Index
			{
				enum : size_type
				{
					ref_count, has_cond, has_set,
					uni_size, arity, port, body_kind, body_expr,
					tag,
					dimension
				};
			};
		};

	// halt:

		template<typename SizeType>
		struct SymbolHalt
		{
			using size_type		= SizeType;
			using size_ctype	= size_type const;

			struct Index
			{
				enum : size_type
				{
					ref_count, has_cond, has_set,
					expr,
					dimension
				};
			};
		};
*/

/***********************************************************************************************************************/

// interface:

/*
	template<typename SizeType, SizeType WordSize, SizeType Size>
	struct model_expression
	{
		using size_type			= SizeType;
		using size_ctype		= size_type const;

		using symbol_value		= model_symbol < size_type , size_type , WordSize , Size >;
		using symbol_conditional	= model_symbol < size_type , size_type , WordSize , Size >;
		using symbol_sequence		= model_symbol < size_type , size_type , WordSize , Size >;
		using symbol_atomic		= model_symbol < size_type , size_type , WordSize , Size >;
		using symbol_compound		= model_symbol < size_type , size_type , WordSize , Size >;
		using symbol_define		= model_symbol < size_type , size_type , WordSize , Size >;
		using symbol_halt		= model_symbol < size_type , size_type , WordSize , Size >;

		symbol_value       value;
		symbol_conditional conditional;
		symbol_sequence    sequence;
		symbol_atomic      atomic;
		symbol_compound    compound;
		symbol_define      define;
		symbol_halt        halt;

		nik_ce model_expression() { }
	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// environment:

/***********************************************************************************************************************/

// binding:

/***********************************************************************************************************************/

// frame:

/***********************************************************************************************************************/

// (scheme):

		// size of { binding, frame, env } == 2 array positions.
		// worst case scenario: each env has exactly one frame, each frame has exactly one binding.
		// max size == 2*(binding size) + 2*(binding size) 2*(binding size) == 6*(binding size)

	// reimplement as a list model of frames, where each frame is a stack(?) of bindings.

	// is this the best way? Or is the another?

/*
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
*/

/***********************************************************************************************************************/

// string number:

/*
	template<typename CharType, typename NumType, typename SizeType, SizeType WordSize, SizeType VarSize>
	class model_environment_string_number
	{
		public:

			using char_type			= CharType;
			using num_type			= NumType;

			using size_type			= SizeType;
			using size_ctype		= size_type const;

			using variable_model		= model_symbol      < char_type, size_type, WordSize , VarSize >;
			using value_model		= model_number      <  num_type, size_type, WordSize >;
			using env_model			= model_environment <            size_type, WordSize >;

			using value_type		= typename value_model::type;
			using value_ctype		= typename value_model::ctype;
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
*/

/***********************************************************************************************************************/

// string expression:

/*
	template<typename CharType, typename SizeType, SizeType WordSize, SizeType VarSize, SizeType Size>
	class model_environment_string_expression
	{
		public:

			using char_type			= CharType;

			using size_type			= SizeType;
			using size_ctype		= size_type const;

			using variable_model		= model_symbol      < char_type, size_type, WordSize , VarSize >;
			using value_model		= model_expression  <            size_type, WordSize ,    Size >;
			using env_model			= model_environment <            size_type, WordSize >;

			using value_type		= typename value_model::type;
			using value_ctype		= typename value_model::ctype;
			using inhabit_type		= typename env_model::inhabit_type;
			using inhabit_ctype		= typename env_model::inhabit_ctype;
			using inhabit_ctype_ref		= inhabit_ctype &;

		protected:

			variable_model variable;
			value_model value;
			env_model env;

		public:

			nik_ce model_environment_string_expression() { env.push_frame(); }

		protected:

		//	template<typename In, typename End>
		//	nik_ce size_type maybe_push_variable(inhabit_ctype_ref record, In in, End end)
		//	{
		//		if (record.not_empty()) return *record;
		//		else variable.push(in, end);

		//		return variable.current_word();
		//	}

		//	nik_ce size_type maybe_push_value(inhabit_ctype_ref record, value_ctype v)
		//	{
		//		if (record.not_empty()) return *record;
		//		else value.push(v);

		//		return value.current_word();
		//	}

		public:

		//	template<typename In, typename End>
		//	nik_ce void push_binding(In in, End end, value_ctype v)
		//	{
		//		env.push_binding
		//		(
		//			maybe_push_variable (variable.find(in), in, end),
		//			maybe_push_value    (value.find(v), v)
		//		);
		//	}

		//	template<typename In>
		//	nik_ce inhabit_type find_value(In in) const { return env.find_value(variable, in); }

		//	nik_ce value_type get_value(inhabit_ctype_ref record) const { return value[*record]; }

		//	nik_ce void set_value(inhabit_ctype_ref record, value_ctype v) { value[*record] = v; }
	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

}} // namespace cctmp::engine

