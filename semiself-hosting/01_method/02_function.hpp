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

// composite:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// glyph:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class glyph_function_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		public:

			nik_ce glyph_function_cmethod_disjoint() : base{} { }
			nik_ce glyph_function_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using glyph_function_cmethod =
			glyph_function_cmethod_disjoint  <
			glyph_composite_cmethod_disjoint <
			glyph_cmethod_disjoint           < Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class glyph_function_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

		public:

			nik_ce glyph_function_method_disjoint() : base{} { }
			nik_ce glyph_function_method_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using glyph_function_method =
			glyph_function_method_disjoint   <
			glyph_function_cmethod_disjoint  <
			glyph_composite_method_disjoint  <
			glyph_composite_cmethod_disjoint <
			glyph_method_disjoint            <
			glyph_cmethod_disjoint           < Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// image:

	struct ImageFunction { enum : genum_type { index = ImageBase::index, time, length, point, dimension }; };

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class image_function_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_type_ref		= typename base::sign_type_ref;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		protected:

			using page_cmethod_type		= typename base::page_cmethod_type;
			using text_csubmethod_type	= typename base::text_csubmethod_type;

		public:

			nik_ce image_function_cmethod_disjoint() : base{} { }
			nik_ce image_function_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using image_function_cmethod =
			image_function_cmethod_disjoint <
			image_cmethod_disjoint          < Facade >>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class image_function_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_type_ref		= typename base::icon_type_ref;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_type_ref		= typename base::sign_type_ref;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		protected:

			using page_cmethod_type		= typename base::page_cmethod_type;
			using page_method_type		= typename base::page_method_type;

			using text_csubmethod_type	= typename base::text_csubmethod_type;
			using text_submethod_type	= typename base::text_submethod_type;

		public:

			nik_ce image_function_method_disjoint() : base{} { }
			nik_ce image_function_method_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using image_function_method =
			image_function_method_disjoint  <
			image_function_cmethod_disjoint <
			image_method_disjoint           <
			image_cmethod_disjoint          < Facade >>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// symbol:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class symbol_function_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce symbol_function_cmethod_disjoint() : base{} { }
			nik_ce symbol_function_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using symbol_function_cmethod =
			symbol_function_cmethod_disjoint  <
			symbol_composite_cmethod_disjoint <
			corpus_cmethod_disjoint           < glyph_function_cmethod , image_function_cmethod , Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class symbol_function_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce symbol_function_method_disjoint() : base{} { }
			nik_ce symbol_function_method_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using symbol_function_method =
			symbol_function_method_disjoint   <
			symbol_function_cmethod_disjoint  <
			symbol_composite_method_disjoint  <
			symbol_composite_cmethod_disjoint <
			corpus_method_disjoint            < glyph_function_method  , image_function_method  ,
			corpus_cmethod_disjoint           < glyph_function_cmethod , image_function_cmethod , Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// concord:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class concord_function_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		protected:

			using contr_type		= typename model_type::template
								record_csubmethod_type<table_csubmethod>;

		public:

			nik_ce concord_function_cmethod_disjoint() : base{} { }
			nik_ce concord_function_cmethod_disjoint(const facade & f) : base{f} { }

		protected:

			// contr:

				nik_ce auto get_contr(sign_ctype_ref sign) const
				{
					auto sit_cival = base::image_ctext(sign);
					auto rec_cival = base::model->template record_csubequip<contr_type>();

					size_ctype length   = base::crecord().cat(sit_cival[ImageFunction::length]);
					size_ctype start    = sit_cival[ImageFunction::point];
					size_ctype finish   = start + length;
					size_ctype row_size = (length >> 2);
					size_ctype col_size = 4;

					rec_cival.mid_set(start, finish);
					rec_cival.set_dimension(row_size, col_size);

					return rec_cival;
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_function_cmethod =
			concord_function_cmethod_disjoint  <
			concord_composite_cmethod_disjoint <
			concord_cmethod_disjoint           < symbol_function_cmethod , array_csubmethod , Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_function_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		protected:

			nik_ce auto declare_image(
				icon_ctype_ref icon, size_ctype time, size_ctype length, size_ctype point)
			{
				auto field = array<size_type, size_type, ImageFunction::dimension>{};
				field.fullsize();

				field[ImageFunction::index ] = icon.index();
				field[ImageFunction::time  ] = time;
				field[ImageFunction::length] = length;
				field[ImageFunction::point ] = point;

				return base::template
					declare_image<BookMark::function, ImageFunction::dimension>(icon, field);
			}

			nik_ce auto declare_abstract(icon_ctype_ref icon)
			{
				size_ctype length = base::record().expand(1);
				size_ctype point  = base::record().expand(length);

				return declare_image(icon, ImageTime::abstract, length, point);
			}

			template<typename T>
			nik_ce auto define_abstract(sign_ctype_ref sign, const T & v)
			{
				auto record_ival  = base::record_submethod();
				auto text_cival   = base::image_ctext(sign);
				size_ctype start  = text_cival[ImageFunction::point];
				size_ctype finish = start + v.size();

				record_ival       . mid_set(start, finish);
				base::record()    . copy(text_cival[ImageFunction::length], v.size());
				record_ival       . copy(0, v.cbegin(), v.cend());

				return sign;
			}

		public:

			nik_ce concord_function_method_disjoint() : base{} { }
			nik_ce concord_function_method_disjoint(const facade & f) : base{f} { }

			// declare:

				template<typename T>
				nik_ce auto declare_type(const T & type)
				{
					size_ctype bytes    = 0; // incorrect.
					size_ctype universe = base::max_universe(type);

					return base::template declare_type
						<BookMark::function, GlyphInstr::function>(type, bytes, universe);
				}

				template<auto N>
				nik_ce auto declare_type(const icon_type (&t)[N])
					{ return declare_type(typename base::template array_type<N>{t}); }

				nik_ce auto declare_concrete(icon_ctype_ref icon, size_ctype addr)
					{ return declare_image(icon, ImageTime::concrete, addr); }

			// define:

				template<auto N>
				nik_ce auto define_abstract(icon_ctype_ref icon, size_ctype (&v)[N])
				{
					auto value = array<size_type, size_type, N>{v};
					auto sign  = declare_abstract(icon, N); // needs to type check.

					define_abstract(sign, value);

					return sign;
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_function_method =
			concord_function_method_disjoint   <
			concord_function_cmethod_disjoint  <
			concord_composite_method_disjoint  <
			concord_composite_cmethod_disjoint <
			concord_method_disjoint            < symbol_function_method  , array_submethod  ,
			concord_cmethod_disjoint           < symbol_function_cmethod , array_csubmethod , Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// eval:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// method:

/***********************************************************************************************************************/

// immutable:

	template
	<
		auto CarrySize, auto VerseSize, auto StageSize,
		template<typename, typename> typename Atomic,
		template<typename, typename> typename Action,
		typename Base
	>
	class eval_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename facade::model_type;

			nik_using_name_scope_type	( type, model_type)
			nik_using_name_scope_ctype	(ctype, model_type)

			nik_using_size_type_scope	(model_type)

			using sign_type			= typename base::sign_type;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

			using machine_type		= machine<type, size_type, CarrySize, VerseSize, StageSize>;
			using carry_type		= typename machine_type::carry_type;
			using verse_type		= typename machine_type::verse_type;

		protected:

			using contr_type		= typename base::contr_type;

			contr_type contr;

		protected:

			using atomic_action_type	= Atomic<type, size_type>;
			using action_type		= Action<eval_cmethod_disjoint, size_type>;

			using machine_cmethod_type	= resolve_cmethod<machine_type, machine_cmethod>;
			using  machine_method_type	=  resolve_method<machine_type,  machine_method>;

			machine_cmethod_type mach_cmethod;
			machine_method_type   mach_method;

		protected:

			machine_type _machine;

		public:

			nik_ce eval_cmethod_disjoint() : base{}, mach_cmethod{}, mach_method{} { }
			nik_ce eval_cmethod_disjoint(const facade & f) : base{f}
			{
				mach_cmethod = _machine.template cequip<machine_cmethod_type>();
				mach_method  = _machine.template  equip< machine_method_type>();
			}

			// contr:

				nik_ce size_type contr_value(size_ctype row, size_ctype col) const
					{ return contr[row][col]; }

				nik_ce size_type instr_value(size_ctype col) const
					{ return contr_value(mach_method.counter(), col); }

				nik_ce void set_contr(sign_ctype_ref sign) { contr = base::get_contr(sign); }

			// carry:

				nik_ce auto & rtn_cvalue() const { return mach_method.ccarry(); }
				nik_ce auto rtn_cat(size_ctype n) const { return mach_method.ccarry().cat(n); }

		protected:

				template<typename F>
				nik_ce void atomic_binary(F f)
					{ mach_method.atomic_binary(f, instr_value(MAppl::policy)); }

				template<typename F>
				nik_ce void atomic_fold(F f, size_type m)
					{ mach_method.atomic_fold(f, instr_value(MAppl::policy), m); }

			// execute:

				nik_ce void execute() { action_type::execute(instr_value(MAppl::action), this); }

		public:

			// atomic:

				nik_ce void atomic(size_ctype n)
					{ atomic_binary(atomic_action_type::action[n]); }

			// run:

				nik_ce void run_branch() { mach_method.branch(instr_value(MBran::line)); }
				nik_ce void run_invert() { mach_method.invert(instr_value(MBran::line)); }

				nik_ce void reset()
				{
					mach_method.carry().clear();
					mach_method.verse().clear();
					mach_method.stage().clear();
				}

				nik_ce void run_apply()
				{
					size_ctype offset    = instr_value(MAppl::offset);
					size_ctype policy    = instr_value(MAppl::policy);

					auto n_eval_cmethod  = eval_cmethod_disjoint{base::model};
					n_eval_cmethod.contr = contr;
					auto func_index      = mach_method.stage_cfunc(offset);
					n_eval_cmethod       . run(mach_method.stage_cargs(), func_index);

					mach_method.pop_stage();
					mach_method.copy_interval(policy, n_eval_cmethod.rtn_cvalue());
				}

				nik_ce void run_constant()
				{
					size_ctype policy = instr_value(MAppl::policy);
					size_ctype value  = instr_value(MAppl::offset);

					mach_method.copy_value(policy, value);
				}

				nik_ce void run_function()
				{
					size_ctype policy = instr_value(MVal::policy);
					size_ctype line   = instr_value(MVal::line);

					mach_method.copy_value(policy, line);
				}

				nik_ce void run_argument()
				{
					auto start  = contr_value(instr_value(MVal::line), MArg::start);
					auto finish = contr_value(instr_value(MVal::line), MArg::finish);

					mach_method.copy_interval(instr_value(MVal::policy), start, finish);
				}

				nik_ce void run_memory_to_stage()
				{
					size_ctype start  = instr_value(MMove::start);
					size_ctype finish = instr_value(MMove::finish);

					mach_method.interval_to_stage(start, finish);
				}

				nik_ce void run_memory_to_carry()
				{
					size_ctype start  = instr_value(MMove::start);
					size_ctype finish = instr_value(MMove::finish);

					mach_method.interval_to_carry(start, finish);
				}

		protected:

			template<typename T>
			nik_ce void run(const T & v, size_ctype n = 0)
			{
				mach_method.initialize(n, v);

				while (instr_value(MProg::next))
				{
					mach_method.inc_counter(instr_value(MProg::next));
					execute();
				}
			}

		public:

			template<auto N>
			nik_ce void apply(sign_ctype_ref sign, ctype (&v)[N])
			{
				set_contr(sign);

				run(verse_type{v});
			}
	};

	// syntactic sugar:

		template<typename Facade, auto CarrySize, auto VerseSize, auto StageSize>
		using eval_cmethod =
			eval_cmethod_disjoint   < CarrySize , VerseSize , StageSize , atomic_action , machine_action ,
			concord_function_method < Facade    >>;

		template<typename Container, auto CarrySize, auto VerseSize, auto StageSize>
		using resolve_eval_cmethod = eval_cmethod
		<
			typename Container::cfacade_type, CarrySize, VerseSize, StageSize
		>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

