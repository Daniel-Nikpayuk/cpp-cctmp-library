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

			using env_type			= unit_stack<list_type, stack_size>;
			using cache_type		= pair_stack<size_type, stack_size>;
			using cbool			= gcbool_type;

			struct Action    { enum : size_type { error, pound, port, back, first, match, dimension }; };
			struct Entry     { enum : size_type { type, init, parameter, argument, compound, dimension }; };
			struct Parameter { enum : size_type { pos  = Entry::init, dimension }; };
			struct Argument  { enum : size_type { pos  = Entry::init, dimension }; };
			struct Compound  { enum : size_type { left = Entry::init, origin, kind, port, dimension }; };

		protected:

			size_type asm_name;
			size_type asm_note;
			size_type asm_pos;
			size_type asm_num;

		public:

			env_type env;
			cache_type cache;

			nik_ce T_syntax_model(cstrlit_ref s) :
				base{s}, asm_name{}, asm_note{}, asm_pos{}, asm_num{}
					{ env.push(base::null_env()); push_env(); } // move push_env to main.

			nik_ce auto get_value(csize_type n) const { return base::base::get_value(entry(), n); }
			nik_ce void set_value(csize_type n, csize_type v) { base::base::set_value(entry(), n, v); }

			// env:

				nik_ce void push_env() { env.push(base::extend_environment(env.cvalue())); }

			// cache:

				nik_ce auto match() const { return cache.entry()[0]; }
				nik_ce auto entry() const { return cache.entry()[1]; }

			// asm:

				nik_ce auto name () const { return asm_name; }
				nik_ce auto note () const { return asm_note; }
				nik_ce auto pos  () const { return asm_pos; }
				nik_ce auto num  () const { return asm_num; }

			// lookup:

				nik_ce bool lookup_variable(const cselect & s)
				{
					cbool success = base::lookup_variable(s, env.cvalue());

					if (success) cache.push(success, base::inhabit.pop());
					else         cache.push(success, 0);

					return success;
				}

				nik_ce auto assemble_variable(const cselect & s, csize_type note)
				{
					if (lookup_variable(s)) return assemble_model(note);
					else                    return assemble_cmodel(s, note);
				}

				template<size_type N>
				nik_ce void define_variable(const cselect & s, csize_type (&ent)[N])
				{
					if (lookup_variable(s)) { } // error.
					else base::define_variable(s, ent, ent + N, env.cvalue());
				}

			// compound:

				nik_ce bool fast_is_compound() const
					{ return (get_value(Entry::type) == Entry::compound); }

				nik_ce bool is_compound() const
					{ return (match() && fast_is_compound()); }

		protected:

			// model action:

				nik_ce auto assemble_model(csize_type note)
				{
					if (fast_is_compound()) return assemble_compound();
					else                    return assemble_argument(note);
				}

				nik_ce auto assemble_compound()
				{
					auto kind = get_value(Compound::kind);

					if      (kind == 0) return assemble_pound();
					else if (kind == 1) return assemble_port();
					else                return Action::error;
				}

				nik_ce auto assemble_pound()
				{
					asm_name = AN::pound;
					asm_note = AT::id;
					asm_pos  = get_value(Compound::origin);
					asm_num  = 0;

					cache.pop();

					return Action::pound;
				}

				nik_ce auto assemble_port()
				{
					asm_name = AN::pound;
					asm_note = AT::port;
					asm_pos  = get_value(Compound::origin);
					asm_num  = get_value(Compound::port);

					cache.pop();

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
					asm_pos  = get_value(Argument::pos);
					asm_num  = 0;

					cache.pop();

					return Action::back;
				}

				nik_ce auto assemble_argument_first()
				{
					asm_name = AN::id;
					asm_note = AT::first;
					asm_pos  = get_value(Argument::pos);
					asm_num  = 0;

					cache.pop();

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
			size_type asm_pos;
			size_type asm_num;

		public:

			nik_ce T_syntax_literal() : asm_name{}, asm_pos{}, asm_num{} { }

			nik_ce auto name () const { return asm_name; }
			nik_ce auto pos  () const { return asm_pos; }
			nik_ce auto num  () const { return asm_num; }

			nik_ce void set(csize_type a, csize_type p, csize_type n)
			{
				asm_name = a;
				asm_pos  = p;
				asm_num  = n;
			}

			nik_ce void set_boolean(csize_type p)
			{
				asm_name = AN::boolean;
				asm_pos  = p;
				asm_num  = 0;
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

			using size_type = SizeType;

		protected:

			size_type arg_size;

		public:

			nik_ce T_syntax_pound() : arg_size{} { }

			nik_ce auto arity() const { return arg_size; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// variadic:

/***********************************************************************************************************************/

// padding:

	template<typename SizeType>
	class T_syntax_padding
	{
		public:

			using size_type		= SizeType;
			using csize_type	= size_type const;

		protected:

			size_type pos;
			size_type num;

		public:

			nik_ce T_syntax_padding() : pos{}, num{} { }

			nik_ce auto size  () const  { return num; }
			nik_ce void reset () { num = 0; }
			nik_ce void inc   () { ++num; }
	};

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

			struct Stage { enum : gkey_type { expedite, defer, dimension }; };

			stack_type status;
			stack_type current;
			stack_type note;

			nik_ce T_syntax_stage()
			{
				current.push(0);
				note.push(AT::first);
			}

			// status:

				nik_ce bool is_expedited () const { return (status.cvalue() == Stage::expedite); }
				nik_ce bool is_deferred  () const { return (status.cvalue() == Stage::defer); }

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

		public:

			nik_ce T_syntax_replace() : asm_pos{} { }
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
		using Compound			= typename model_type::Compound;

		using verse_type		= T_syntax_verse<size_type, stack_size>; // make stack sizes
		using stage_type		= T_syntax_stage<size_type, stack_size>; // independent?
		using Stage			= typename stage_type::Stage;

		using padding_type		= T_syntax_padding<size_type>;
		using literal_type		= T_syntax_literal<size_type>;
		using lookup_type		= T_syntax_lookup <cselect>;
		using pound_type		= T_syntax_pound<size_type>;
		using replace_type		= T_syntax_replace<cselect, size_type>;

		enum : gkey_type
		{
			src_at = 0,
			str_at,

			dimension
		};

		contr_type contr;
		model_type model;
		verse_type verse;
		stage_type stage;

		padding_type padding;
		literal_type literal;
		lookup_type lookup;
		pound_type pound;
		replace_type replace;

		nik_ce T_syntax_tree() : contr{src_at, str_at}, model{src} { }

		// action:

			template<auto name, auto note, typename... Ts>
			nik_ce void assembly_action(Ts... vs)
				{ assembly::assembly_action<name, note>(&contr, vs...); }

		// source:

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

		// param:

		//	nik_ce void param_type(const cselect & s)
		//		{ model.define_parameter(s, param_var_type{count++}, cur_env); }

		// main:

			nik_ce void main_name(const cselect & s)
			{
		//		nik_ce auto left = 0;
		//		nik_ce auto ins  = 0;
		//		nik_ce auto val  = pound_var_type(left, ins);
		//		cur_entry = model.define_compound(s, val, cur_env);

				upsize_verse();
			}

			nik_ce void main_begin()
			{
				nik_ce auto pos = 0;
				nik_ce auto pad = 1;

				assembly_action<AAN::id  , AAT::begin >();
				assembly_action<AAN::pad , AAT::id    >(pos, pad);
			}

			nik_ce void main_end() { assembly_action<AAN::id, AAT::end>(AT::first); }

		// port:

			// op:

			//	nik_ce void op_port_lookup(const cselect & s)
			//	{
			//		auto rec = model.lookup_variable(s);

			//		if (mrec_match(rec))
			//		{
			//			auto entry = mrec_entry(rec);
			//			auto pos   = model.parameter_pos(entry);

			//			model.set_value(cur_entry, Compound::kind, 1); // magic number.
			//			model.set_value(cur_entry, Compound::port, pos);
			//		}
			//		else { } // error.
			//	}

			// arg:

			//	nik_ce void port_lookup(const cselect & s)
			//	{
			//		auto rec = model.lookup_variable(s);

			//		if (mrec_match(rec))
			//		{
			//			auto entry = mrec_entry(rec);
			//			auto pos   = model.parameter_pos(entry);

			//			force_literal_return(pos);
			//		}
			//		else { } // error.
			//	}

		// declare:

		//	nik_ce void declare_op_name(const cselect & s)
		//		{ model.define_compound(s, cur_env); }

		// define:

			nik_ce void define_argument(const cselect & s, cindex pos)
				{ model.define_variable(s, {ModelEntry::argument, pos}); }

			nik_ce void define_compound(const cselect & s, cindex left, cindex origin)
			{
				nik_ce size_type kind = 0;
				nik_ce size_type port = 0;

				model.define_variable(s, {ModelEntry::compound, left, origin, kind, port});
				model.push_env();
			}

			// op:

				nik_ce void define_op_name(const cselect & s)
				{
					define_compound(s, verse.size(), contr.current(2));
					verse.current.push(verse.size());
					stage.current.push(verse.size()); // reset stage to verse.
				}

				nik_ce void define_op_arg(const cselect & s) { define_argument(s, inc_verse()); }
			//	nik_ce void define_op_arity(cindex value) { cur_arity = value; }

				nik_ce void define_op_begin()
				{
					assembly_action< AAN::go_to , AAT::begin >();
					assembly_action< AAN::id    , AAT::begin >();
				}

				nik_ce void define_op_end()
				{
					verse.current.pop();
					stage.current.pop();

					assembly_action< AAN::id    , AAT::end >(AT::first);
					assembly_action< AAN::go_to , AAT::end >();
				}

			// arg:

			//	nik_ce void define_arg_variable(const cselect & s, cindex pos)
			//		{ model.define_variable(s, arg_var_type{pos}); }

			//	nik_ce void define_arg_variable(const cselect & s)
			//		{ define_arg_variable(s, push_verse()); }

			//	nik_ce void define_arg_names(cindex pos, cindex pad_size)
			//		{ assembly_action<AAN::pad, AAT::id>(pos, pad_size); }

			//	nik_ce void define_arg_name(const cselect & s, cindex pad_size = 1)
			//	{
			//		auto pos = push_verse();

			//		define_arg_variable(s, pos);
			//		define_arg_names(pos, pad_size);
			//	}

		// refine:

			// op:

			//	nik_ce void refine_op_name(const cselect & s)
			//	{
			//		auto rec = model.lookup_variable(s);

			//		if (mrec_match(rec))
			//		{
			//			auto left = verse_size;
			//			auto ins  = contr.current(2);
			//			auto env  = push_env();
			//			cur_entry = mrec_entry(rec);

			//			model.set_value(cur_entry, Compound::left, left);
			//			model.set_value(cur_entry, Compound::ins, ins);
			//			pound.push(reset_args(), left, env);
			//		}
			//		else { } // error.
			//	}

			//	nik_ce void refine_op_args() { inc_args(cur_arity); }

		// literal:

			nik_ce void delay_boolean_return(const bool value) { literal.set_boolean(value); }

			nik_ce void delay_literal_return(cindex name, src_ptr b_ptr, src_ptr e_ptr)
				{ literal.set(name, left_size(b_ptr), left_size(e_ptr)); }

			nik_ce void force_literal_return()
			{
				auto note = stage.note_return();
				auto name = literal.name();
				auto pos  = literal.pos();
				auto num  = literal.num();

				assembly_action<AAN::literal, AAT::id>(note, name, pos, num);
				stage.upsize_if();
			}

			nik_ce void force_literal_return(cindex value)
			{
				auto note = stage.note_return();
				auto name = literal.name();
				auto pos  = literal.pos();
				auto num  = literal.num();

				assembly_action<AAN::literal, AAT::literal>(note, value, name, pos, num);
				stage.upsize_if();
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

		// apply:

			nik_ce void apply_begin(const cselect & s)
			{
				model.lookup_variable(s);
				stage.status.push(Stage::expedite);
				stage.current.push(stage.size());
				stage.note.push(AT::back);
			}

			nik_ce void apply_begin()
			{
				stage.status.push(Stage::defer);
				stage.current.push(stage.size());
				stage.note.push(AT::back);
			}

			nik_ce void apply_end()
			{
				if      (stage.is_deferred()) apply_deferred_end();
				else if (model.is_compound()) apply_compound_end();
				else                          apply_atomic_end();
			}

				nik_ce void apply_deferred_end()
				{
				}

				nik_ce void apply_compound_end()
				{
					auto left = model.get_value(Compound::left);

					model.cache.pop();
					stage.current.pop();
					stage.status.pop();
					stage.note.pop();

					assembly_action<AAN::push, AAT::instr>(AN::arg, AT::verse, left, stage.size());
					assembly_action<AAN::push, AAT::instr>(AN::bind, stage.note_return()); // AT::side ?
					stage.upsize_if();
				}

				nik_ce void apply_atomic_end()
				{
					stage.current.pop();
					stage.status.pop();
					stage.note.pop();

					assembly_action<AAN::push, AAT::instr>(AN::arg, AT::select, stage.size());
					assembly_action<AAN::push, AAT::instr>(AN::apply, stage.note_return()); // AT::side ?
					stage.upsize_if();
				}

			nik_ce void apply_patch()
			{
			}

			nik_ce void apply_call()
			{
			}

		// replace:

		//	nik_ce void copy_replace() { repl_pos = 0; }

		//	nik_ce void delay_replace(const cselect & s)
		//	{
		//		repl_name = s;
		//		auto record = model.lookup_variable(s);

		//		if (mrec_match(record)) delay_match_replace(mrec_entry(record));
		//		else { } // error.
		//	}

		//	nik_ce void delay_match_replace(cindex entry)
		//	{
		//		if (model.is_compound(entry)) repl_pos = 0;
		//		else repl_pos = model.variadic_pos(entry);
		//	}

		//	nik_ce void force_replace() { if (repl_pos) force_verse_replace(); }
		//	nik_ce void force_verse_replace() { assembly_action<AAN::replace, AAT::id>(repl_pos); }

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

