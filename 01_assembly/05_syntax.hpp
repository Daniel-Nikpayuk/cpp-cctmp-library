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

// syntax:

namespace assembly {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// memory:

/***********************************************************************************************************************/

// model:

	template
	<
		typename SizeType, auto model_size, auto stack_size,
		auto static_env_lookup, typename CharType = gchar_type
	>
	class T_syntax_model : public cctmp::T_env_model<CharType, SizeType, model_size>
	{
		public:

			using base			= cctmp::T_env_model<CharType, SizeType, model_size>;
			using size_type			= typename base::size_type;
			using csize_type		= typename base::csize_type;
			using list_type			= typename base::list_type;
			using cselect			= typename base::cselect;
			using cstrlit_ref		= typename base::cstrlit_ref;

			nik_ces auto & cmodel		= member_value_U<static_env_lookup>;
			using cinhabit_type		= typename member_type_U<static_env_lookup>::inhabit_type;

			using cache_type		= unit_stack<size_type, stack_size>;
			using cbool			= gcbool_type;

			struct Action    { enum : size_type { error, pound, port, back, first, match, dimension }; };
			struct Entry     { enum : size_type { type, init, parameter, argument, compound, dimension }; };
			struct Parameter { enum : size_type { pos  = Entry::init, dimension }; };
			struct Argument  { enum : size_type { pos  = Entry::init, dimension }; };
			struct Compound  { enum : size_type { left = Entry::init, origin, kind, port, dimension }; };

		protected:

			size_type env;
			size_type asm_name;
			size_type asm_note;
			size_type asm_pos;
			size_type asm_num;

		public:

			cache_type cache;

			nik_ce T_syntax_model(cstrlit_ref s) :
				base{s}, env{base::null_env()}, asm_name{}, asm_note{}, asm_pos{}, asm_num{}
					{ env_push(); }

			// env:

				nik_ce auto env_origin () const { return env; }
				nik_ce auto env_entry  () const { return base::get_entry(env); }

				nik_ce void env_push () { env = base::extend_env(env); }
				nik_ce void env_pop  () { env = base::cdr(env); }

			// inhabit:

				nik_ce bool is_compound() const
					{ return (base::get_value(Entry::type) == Entry::compound); }

			// cache:

				nik_ce auto get_cache_value(csize_type n) const
					{ return base::base::get_value(cache.cvalue(), n); }

				nik_ce void set_cache_value(csize_type n, csize_type v)
					{ base::base::set_value(cache.cvalue(), n, v); }

			// asm:

				nik_ce auto name () const { return asm_name; }
				nik_ce auto note () const { return asm_note; }
				nik_ce auto pos  () const { return asm_pos; }
				nik_ce auto num  () const { return asm_num; }

			// lookup:

				nik_ce bool lookup_variable(const cselect & s)
					{ return base::lookup_variable(s, env); }

				nik_ce auto assemble_variable(const cselect & s, csize_type note)
				{
					if (lookup_variable(s)) return assemble_model(note);
					else                    return assemble_cmodel(s, note);
				}

				template<size_type N>
				nik_ce void define_variable(const cselect & s, csize_type (&ent)[N])
				{
					if (lookup_variable(s)) { } // error.
					else base::define_variable(s, ent, ent + N, env);
				}

		protected:

			// model action:

				nik_ce auto assemble_model(csize_type note)
				{
					if (is_compound()) return assemble_compound();
					else               return assemble_argument(note);
				}

				nik_ce auto assemble_compound()
				{
					auto kind = base::get_value(Compound::kind);

					if      (kind == 0) return assemble_pound();
					else if (kind == 1) return assemble_port();
					else                return Action::error;
				}

				nik_ce auto assemble_pound()
				{
					asm_name = AN::pound;
					asm_note = AT::id;
					asm_pos  = base::get_value(Compound::origin);
					asm_num  = 0;

					return Action::pound;
				}

				nik_ce auto assemble_port()
				{
					asm_name = AN::pound;
					asm_note = AT::port;
					asm_pos  = base::get_value(Compound::origin);
					asm_num  = base::get_value(Compound::port);

					return Action::port;
				}

				nik_ce auto assemble_argument(csize_type note)
				{
					if (note == AT::back) return assemble_argument_back();
					else                  return assemble_argument_first();
				}

				nik_ce auto assemble_argument_back()
				{
					asm_name = AN::id;
					asm_note = AT::back;
					asm_pos  = base::get_value(Argument::pos);
					asm_num  = 0;

					return Action::back;
				}

				nik_ce auto assemble_argument_first()
				{
					asm_name = AN::id;
					asm_note = AT::first;
					asm_pos  = base::get_value(Argument::pos);
					asm_num  = 0;

					return Action::first;
				}

			// cmodel action:

				nik_ce auto assemble_cmodel(const cselect & s, csize_type note)
				{
					auto rec = cmodel.match_variable(s);

					if (rec.not_empty()) return assemble_match(rec, note);
					else                 return assemble_error(s);
				}

				nik_ce auto assemble_match(const cinhabit_type & rec, csize_type note)
				{
					auto ent = rec.entry();

					asm_name = AN::id;
					asm_note = note;
					asm_pos  = ent[0];
					asm_num  = ent[1];

					return Action::match;
				}

				nik_ce auto assemble_error(const cselect & s)
				{
					// nothing yet.

					return Action::error;
				}
	};

/***********************************************************************************************************************/

// literal:

	template<typename SizeType>
	class T_syntax_literal
	{
		public:

			using size_type		= SizeType;
			using csize_type	= size_type const;

		protected:

			size_type asm_name;
			size_type asm_note;
			size_type asm_pos;
			size_type asm_num;
			size_type asm_aux;

		public:

			nik_ce T_syntax_literal() : asm_name{}, asm_note{}, asm_pos{}, asm_num{}, asm_aux{} { }

			nik_ce auto name () const { return asm_name; }
			nik_ce auto note () const { return asm_note; }
			nik_ce auto pos  () const { return asm_pos; }
			nik_ce auto num  () const { return asm_num; }
			nik_ce auto aux  () const { return asm_aux; }

			nik_ce void set(csize_type n0, csize_type n1,
				csize_type p0, csize_type p1 = 0, csize_type p2 = 0)
			{
				asm_name = n0;
				asm_note = n1;
				asm_pos  = p0;
				asm_num  = p1;
				asm_aux  = p2;
			}
	};

/***********************************************************************************************************************/

// lookup:

	template<typename SelectorType>
	class T_syntax_lookup
	{
		public:

			using cselect = SelectorType;

		protected:

			cselect asm_var;
			bool asm_mute;

		public:

			nik_ce T_syntax_lookup() : asm_mute{} { }

			nik_ce auto var  () const { return asm_var; }
			nik_ce bool mute () const { return asm_mute; }

			nik_ce void set(const cselect & s, const bool m)
			{
				asm_var  = s;
				asm_mute = m;
			}

			nik_ce void reset() { asm_mute = false; }
	};

/***********************************************************************************************************************/

// pound:

	template<typename SizeType>
	class T_syntax_pound
	{
		public:

			using size_type		= SizeType;
			using csize_type	= size_type const;

		protected:

			size_type arg_size;

		public:

			nik_ce T_syntax_pound() : arg_size{} { }

			nik_ce auto arity() const { return arg_size; }
			nik_ce auto set_arity(csize_type n) { arg_size = n; }
	};

/***********************************************************************************************************************/

// count:

	template<typename SizeType>
	class T_syntax_count
	{
		public:

			using size_type		= SizeType;
			using csize_type	= size_type const;

		protected:

			size_type pos;
			size_type num;

		public:

			nik_ce T_syntax_count() : pos{}, num{} { }

			// pos:

				nik_ce size_type cache() const { return pos; }
				nik_ce void cache(csize_type n) { pos = n; }

			// num:

				nik_ce size_type size() const { return num; }
				nik_ce void reset() { num = 0; }
				nik_ce void upsize(csize_type n = 1) { num += n; }
				nik_ce size_type inc_size(csize_type n = 1) { auto v = size(); upsize(n); return v; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// variadic:

/***********************************************************************************************************************/

// verse (abstraction):

	template<typename SizeType, auto stack_size>
	class T_syntax_verse
	{
		public:

			using size_type		= SizeType;
			using csize_type	= size_type const;
			using stack_type	= unit_stack<size_type, stack_size>;

			stack_type current;

			nik_ce T_syntax_verse() { current.push(0); }

			nik_ce auto size() const { return current.cvalue(); }
			nik_ce void upsize(csize_type n = 1) { current.value() = size() + n; }
			nik_ce auto inc_size(csize_type n = 1) { auto v = size(); upsize(n); return v; }
	};

/***********************************************************************************************************************/

// stage (application):

	template<typename SizeType, auto stack_size>
	class T_syntax_stage
	{
		public:

			using size_type		= SizeType;
			using csize_type	= size_type const;
			using stack_type	= unit_stack<size_type, stack_size>;
			using StackPair		= typename stack_type::Pair;

			struct Stage { enum : gkey_type { atomic, compound, defer, dimension }; };

			stack_type side;
			stack_type procedure;
			stack_type current;
			stack_type note;

			nik_ce T_syntax_stage()
			{
				current.push(0);
				note.push(AT::first);
			}

			// procedure:

				nik_ce bool is_compound() const { return (procedure.cvalue() == Stage::compound); }
				nik_ce bool is_deferred() const { return (procedure.cvalue() == Stage::defer); }

			// return:

				nik_ce auto note_return    () const { return note.cvalue(); }
				nik_ce bool is_back_return () const { return (note_return() == AT::back); }

			// size:

				nik_ce auto size() const { return current.cvalue(); }
				nik_ce void upsize(csize_type n = 1) { current.value() += n; }
				nik_ce void upsize_if(csize_type n = 1) { if (is_back_return()) upsize(n); }
				nik_ce auto inc_size(csize_type n = 1)
					{ csize_type v = size(); upsize(n); return v; }

				nik_ce void restack(csize_type n = 1)
				{
					for (auto k = current.cbegin(); k != current.cend(); k = current.cdr(k))
						current.set_value(k, StackPair::car, current.car(k) + n);
				}
	};

/***********************************************************************************************************************/

// replace:

	template<typename SelectorType, typename SizeType>
	class T_syntax_replace
	{
		public:

			using cselect		= SelectorType;
			using size_type		= SizeType;
			using csize_type	= size_type const;

		protected:

			cselect asm_var;
			size_type asm_pos;
			bool side;

		public:

			nik_ce T_syntax_replace() : asm_pos{}, side{} { }

			nik_ce auto name () const { return asm_var; }
			nik_ce auto pos  () const { return asm_pos; }

			nik_ce bool not_copy () const { return (asm_pos != 0); }

			nik_ce void set_name(const cselect & s) { asm_var = s; }
			nik_ce void set_pos(csize_type n) { asm_pos = n; }

			nik_ce void set_side() { side = true; }
			nik_ce const bool reset_side() { const bool v = side; side = false; return v; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tree:

/***********************************************************************************************************************/

// interface:

	template<auto static_source, auto static_env_lookup, auto contr_size, auto stack_size, auto model_size>
	struct T_syntax_tree
	{
		nik_ces auto & src		= member_value_U<static_source>;
		using src_ptr			= typename member_type_U<static_source>::ctype_cptr;
		using cselect			= typename member_type_U<static_source>::cselector_type;

		using contr_type		= T_machine_contr<contr_size, stack_size>;
		using size_type			= typename contr_type::size_type;
		using csize_type		= typename contr_type::csize_type;
		using cindex			= typename contr_type::cindex;

		using model_type		= T_syntax_model<size_type, model_size, stack_size, static_env_lookup>;
		using ModelAction		= typename model_type::Action;
		using ModelEntry		= typename model_type::Entry;
		using Parameter			= typename model_type::Parameter;
		using Argument			= typename model_type::Argument;
		using Compound			= typename model_type::Compound;

		using literal_type		= T_syntax_literal<size_type>;
		using lookup_type		= T_syntax_lookup<cselect>;
		using pound_type		= T_syntax_pound<size_type>;

		using verse_type		= T_syntax_verse<size_type, stack_size>; // make stack sizes
		using stage_type		= T_syntax_stage<size_type, stack_size>; // independent?
		using Stage			= typename stage_type::Stage;

		using count_type		= T_syntax_count<size_type>;
		using replace_type		= T_syntax_replace<cselect, size_type>;

		contr_type contr;
		model_type model;
		literal_type literal;
		lookup_type lookup;
		pound_type pound;

		verse_type verse;
		stage_type stage;
		count_type count;
		replace_type replace;
		cselect name;

		nik_ce T_syntax_tree() : model{src} { }

		// action:

			template<auto name, auto note, typename... Ts>
			nik_ce void assembly_action(Ts... vs)
				{ assembly::assembly_action<name, note>(&contr, vs...); }

			nik_ce void first_return() { assembly_action<AAN::id, AAT::end>(AT::first); }

		// source:

			template<typename T>
			nik_ce auto divisor(T v) { T n{1}; while (--v != 0) n *= 10; return n; }

			nik_ce auto left_size(src_ptr i) const { return i - src.origin(); }

		// verse:

			nik_ce void upsize_verse(cindex n = 1)
			{
				verse.upsize(n);
				stage.upsize(n);
			}

			nik_ce auto inc_verse(cindex n = 1)
			{
				auto v = verse.size();

				upsize_verse(n);

				return v;
			}

			nik_ce void push_verse_stage()
			{
				verse.current.push(verse.size());
				stage.current.push(verse.size()); // reset stage to verse.
			}

		// param:

			nik_ce void param_type(const cselect & s) { define_parameter(s, count.inc_size()); }

		// main:

			nik_ce void main_begin(const cselect & s)
			{
				nik_ce auto pad = 1;

				name = s;
				assembly_action< AAN::id   , AAT::begin >();
				assembly_action< AAN::push , AAT::instr >(AN::hash, AT::port, contr.current(5));
				assembly_action< AAN::pad  , AAT::id    >(0, pad);

				upsize_verse(pad);
				define_op_name(s);
			}

			nik_ce void main_port_deduce() { contr[1][AI::note] = AT::id; }

			nik_ce void main_end()
			{
				nik_ce auto left = 1;

				define_op_end();
				assembly_action<AAN::push, AAT::instr>(AN::arg, AT::verse, left, left);
				assembly_action<AAN::push, AAT::instr>(AN::bind, stage.note_return()); // AT::side ?
				first_return();
			}

		// port:

			// op:

				nik_ce void op_port_lookup(const cselect & s)
				{
					if (model.lookup_variable(s))
					{
						auto pos = model.get_value(Parameter::pos);

						model.set_cache_value(Compound::kind, 1); // magic number.
						model.set_cache_value(Compound::port, pos);
					}
					else { } // error.
				}

			// arg:

				nik_ce void port_lookup(const cselect & s)
				{
					if (model.lookup_variable(s))
					{
						auto pos = model.get_value(Parameter::pos);

						force_literal_return(pos);
					}
					else { } // error.
				}

		// define:

			nik_ce void define_parameter(const cselect & s, cindex pos)
				{ model.define_variable(s, {ModelEntry::parameter, pos}); }

			nik_ce void define_argument(const cselect & s, cindex pos)
				{ model.define_variable(s, {ModelEntry::argument, pos}); }

			nik_ce void delay_define_compound(const cselect & s, cindex left = 0, cindex origin = 0)
			{
				nik_ce size_type kind = 0;
				nik_ce size_type port = 0;

				model.define_variable(s, {ModelEntry::compound, left, origin, kind, port});
			}

			nik_ce void force_define_compound(const cselect & s)
			{
				if (model.lookup_variable(s))
				{
					model.set_value(Compound::left, verse.size());
					model.set_value(Compound::origin, contr.current(2));
					model.env_push();

					push_verse_stage();
				}
				else { } // error.
			}

			nik_ce void define_compound(const cselect & s, cindex left = 0, cindex origin = 0)
			{
				delay_define_compound(s, left, origin);
				model.cache.push(model.env_entry());
				model.env_push();
			}

			nik_ce void undefine_compound()
			{
				model.cache.pop();
				model.env_pop();
			}

			nik_ce void delay_define_arity(cindex n) { pound.set_arity(n); }
			nik_ce void force_define_arity(cindex n) { stage.upsize(n); }
			nik_ce void force_define_arity() { force_define_arity(pound.arity()); }

			// op:

				nik_ce void define_op_name(const cselect & s)
				{
					define_compound(s, verse.size(), contr.current(2));
					push_verse_stage();
				}

				nik_ce void define_op_arg(const cselect & s) { define_argument(s, inc_verse()); }

				nik_ce void define_op_begin()
				{
					assembly_action< AAN::go_to , AAT::begin >();
					assembly_action< AAN::id    , AAT::begin >();
				}

				nik_ce void define_op_end()
				{
					verse.current.pop();
					stage.current.pop();
					undefine_compound();

					first_return();
					assembly_action<AAN::go_to, AAT::end>();
				}

			// arg:

				nik_ce void define_arg_name(const cselect & s)
					{ define_argument(s, inc_verse()); }

				nik_ce void define_arg_names(cindex pos, cindex pad_size)
					{ assembly_action<AAN::pad, AAT::id>(pos, pad_size); }

		// literal:

			// delay:

				// boolean:

					nik_ce void delay_boolean_return(const bool value)
						{ literal.set(AN::literal, AT::boolean, value); }

				// character:

					nik_ce void delay_character_return(src_ptr b, src_ptr e)
						{ literal.set(AN::literal, AT::character, *(b + 1)); }

				// n_number:

					nik_ce void delay_n_number_return(src_ptr b, src_ptr e)
					{
						auto pos = cctmp::apply<_string_to_builtin_<U_gindex_type>>(b, e);
						
						literal.set(AN::literal, AT::n_number, pos);
					}

				// r_number:

					nik_ce void delay_r_number_return(src_ptr b, src_ptr e)
					{
						src_ptr k = cctmp::apply<_subarray_match_<>>(b, e, '.');
						auto pos  = cctmp::apply<_string_to_builtin_<U_gindex_type>>(b, k);
						auto num  = cctmp::apply<_string_to_builtin_<U_gindex_type>>(k+1, e);
						auto div  = divisor(e-k);

						literal.set(AN::floating, AT::r_number, pos, num, div);
					}

			// force:

				nik_ce void force_literal_port(cindex note, cindex pos = 0)
					{ assembly_action<AAN::push, AAT::instr>(AN::type, note, pos); }

				nik_ce void force_literal_value()
				{
					auto name = literal.name();
					auto note = stage.note_return();
					auto pos  = literal.pos();
					auto num  = literal.num();
					auto aux0 = literal.aux();

					assembly_action<AAN::push, AAT::instr>(name, note, pos, num, aux0);
					stage.upsize_if();
				}

				nik_ce void force_literal_return()
				{
					force_literal_port(literal.note());
					force_literal_value();
				}

				nik_ce void force_literal_return(cindex pos)
				{
					force_literal_port(AT::push, pos);
					force_literal_value();
				}

		// lookup:

			nik_ce void delay_lookup_return(const cselect & s, const bool mute = false)
				{ lookup.set(s, mute); }

			nik_ce void force_lookup_return()
			{
				auto var    = lookup.var();
				auto note   = stage.note_return();
				auto action = model.assemble_variable(var, note);

				dispatch_lookup_return(action, lookup.mute());
				stage.upsize_if();
				lookup.reset();
			}

			nik_ce void dispatch_lookup_return(cindex action, const bool mute)
			{
				auto name = model.name();
				auto note = model.note();
				auto pos  = model.pos();
				auto num  = model.num();

				switch (action)
				{
					case ModelAction::pound: // continue:
					case ModelAction::port:
					{
						assembly_action<AAN::push, AAT::instr>(name, note, pos, num);
						break;
					}
					case ModelAction::back: // continue:
					case ModelAction::first:
					{
						assembly_action<AAN::lookup, AAT::variable>(note, mute, pos);
						break;
					}
					case ModelAction::match:
					{
						assembly_action<AAN::lookup, AAT::parameter>(note, pos, num);
						break;
					}
				}
			}

			nik_ce void lookup_return(const cselect & s, const bool mute = false)
			{
		      		delay_lookup_return(s, mute);
		      		force_lookup_return();
			}

			nik_ce void back_lookup_return(cindex pos, const bool mute = false)
				{ assembly_action<AAN::lookup, AAT::variable>(AT::back, mute, verse.size() + pos); }

		// apply:

			nik_ce void apply_begin(const cselect & s, const bool is_side = false)
			{
				auto is_pound = model.lookup_variable(s);
				auto status   = is_pound ? Stage::compound : Stage::atomic;

				if (is_pound) model.cache.push(model.inhabit.cvalue());

				stage.side.push(is_side);
				stage.procedure.push(status);
				stage.current.push(stage.size());
				stage.note.push(AT::back);
			}

			nik_ce void apply_begin(const bool is_side = false)
			{
				stage.side.push(is_side);
				stage.procedure.push(Stage::defer);
				stage.current.push(stage.size());
				stage.note.push(AT::back);
			}

			nik_ce void apply_end()
			{
				if      (stage.is_deferred()) apply_deferred_end();
				else if (stage.is_compound()) apply_compound_end();
				else                          apply_atomic_end();
			}

				nik_ce void apply_deferred_end()
				{
				}

				nik_ce void apply_compound_end(cindex left)
				{
					stage.current.pop();
					stage.procedure.pop();
					stage.note.pop();

					auto note = stage.side.pop() ? AT::side : stage.note_return();

					assembly_action<AAN::push, AAT::instr>(AN::arg, AT::verse, left, stage.size());
					assembly_action<AAN::push, AAT::instr>(AN::bind, note);
					stage.upsize_if();
				}

				nik_ce void apply_compound_end()
				{
					apply_compound_end(model.get_cache_value(Compound::left));
					model.cache.pop();
				}

				nik_ce void apply_atomic_end()
				{
					stage.current.pop();
					stage.procedure.pop();
					stage.note.pop();

					auto note = stage.side.pop() ? AT::side : stage.note_return();

					assembly_action<AAN::push, AAT::instr>(AN::arg, AT::select, stage.size());
					assembly_action<AAN::push, AAT::instr>(AN::apply, note);
					stage.upsize_if();
				}

			nik_ce void apply_patch()
			{
			}

			nik_ce void apply_call()
			{
			}

		// replace:

			nik_ce void copy_replace() { replace.set_pos(0); }
			nik_ce void side_replace() { replace.set_side(); }

			nik_ce void swap_replace(const cselect & s)
			{
				replace.set_name(s);
				replace.set_side();
			}

			nik_ce void delay_replace(const cselect & s)
			{
				replace.set_name(s);

				if (model.lookup_variable(s)) delay_match_replace();
				else { } // error.
			}

			nik_ce void delay_match_replace()
			{
				// test against all other entry types?
				if (model.is_compound()) { } // error: one definition rule?
				else replace.set_pos(model.get_value(Argument::pos));
			}

			nik_ce void force_replace() { assembly_action<AAN::replace, AAT::id>(replace.pos()); }

		// conditional:

			nik_ce void if_pred_begin  () { stage.note.push(AT::first); }
			nik_ce void if_pred_end    () { stage.note.pop(); }

			nik_ce void if_ante_begin  () { assembly_action<AAN::invert, AAT::begin>(AT::id); }
			nik_ce void if_ante_end    () { assembly_action<AAN::invert, AAT::end>(1); }

			nik_ce void if_conse_begin () { assembly_action<AAN::go_to, AAT::begin>(); }
			nik_ce void if_conse_end   () { assembly_action<AAN::go_to, AAT::end>(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace assembly

