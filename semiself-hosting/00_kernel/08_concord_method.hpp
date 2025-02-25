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

// concord method:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// builtin:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class concord_builtin_cmethod_disjoint : public Base
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

		public:

			nik_ce concord_builtin_cmethod_disjoint() : base{} { }
			nik_ce concord_builtin_cmethod_disjoint(const facade & f) : base{f} { }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_builtin_method_disjoint : public Base
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

			nik_ce auto declare_image(icon_ctype_ref icon, size_type time, size_ctype point)
			{
				auto field = array<size_type, size_type, ImageBuiltin::dimension>{};
				field.fullsize();

				field[ImageBuiltin::index ] = icon.index();
				field[ImageBuiltin::time  ] = time;
				field[ImageBuiltin::point ] = point;

				return base::symbol_method().declare_image(icon, field);
			}

			// declare:

				nik_ce auto declare_abstract(icon_ctype_ref icon)
					{ return declare_image(icon, ImageTime::abstract, base::record().expand(1)); }

			// define:

				nik_ce void define_abstract(sign_ctype_ref sign, size_ctype value)
					{ base::record_copy(sign, ImageBuiltin::point, value); }

		public:

			nik_ce concord_builtin_method_disjoint() : base{} { }
			nik_ce concord_builtin_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_type(size_ctype instr, size_ctype bytes)
					{ return base::symbol_method().declare_type(instr, bytes); }

				nik_ce auto declare_concrete(icon_ctype_ref icon)
					{ return declare_image(icon, ImageTime::concrete, base::record().expand(1)); }

			// define:

				nik_ce auto define_abstract(icon_ctype_ref icon, size_ctype value)
				{
					auto sign = declare_abstract(icon);

					define_abstract(sign, value);

					return sign;
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// empty:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class concord_empty_cmethod_disjoint : public Base
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

		public:

			nik_ce concord_empty_cmethod_disjoint() : base{} { }
			nik_ce concord_empty_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_empty_cmethod =
			concord_empty_cmethod_disjoint   <
			concord_builtin_cmethod_disjoint <
			concord_cmethod_disjoint         < symbol_builtin_cmethod , array_csubmethod , Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_empty_method_disjoint : public Base
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

		public:

			nik_ce concord_empty_method_disjoint() : base{} { }
			nik_ce concord_empty_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_type(size_ctype bytes)
					{ return base::declare_type(GlyphInstr::empty, bytes); }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_empty_method =
			concord_empty_method_disjoint    <
			concord_empty_cmethod_disjoint   <
			concord_builtin_method_disjoint  <
			concord_builtin_cmethod_disjoint <
			concord_method_disjoint          < symbol_builtin_method  , array_submethod  ,
			concord_cmethod_disjoint         < symbol_builtin_cmethod , array_csubmethod , Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// ring:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class concord_ring_cmethod_disjoint : public Base
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

		public:

			nik_ce concord_ring_cmethod_disjoint() : base{} { }
			nik_ce concord_ring_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_ring_cmethod =
			concord_ring_cmethod_disjoint    <
			concord_builtin_cmethod_disjoint <
			concord_cmethod_disjoint         < symbol_builtin_cmethod , array_csubmethod , Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_ring_method_disjoint : public Base
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

		public:

			nik_ce concord_ring_method_disjoint() : base{} { }
			nik_ce concord_ring_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_type(size_ctype bytes)
					{ return base::declare_type(GlyphInstr::ring, bytes); }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_ring_method =
			concord_ring_method_disjoint     <
			concord_ring_cmethod_disjoint    <
			concord_builtin_method_disjoint  <
			concord_builtin_cmethod_disjoint <
			concord_method_disjoint          < symbol_builtin_method  , array_submethod  ,
			concord_cmethod_disjoint         < symbol_builtin_cmethod , array_csubmethod , Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// flex:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class concord_flex_cmethod_disjoint : public Base
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

		public:

			nik_ce concord_flex_cmethod_disjoint() : base{} { }
			nik_ce concord_flex_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_flex_cmethod =
			concord_flex_cmethod_disjoint    <
			concord_builtin_cmethod_disjoint <
			concord_cmethod_disjoint         < symbol_builtin_cmethod , array_csubmethod , Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_flex_method_disjoint : public Base
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

		public:

			nik_ce concord_flex_method_disjoint() : base{} { }
			nik_ce concord_flex_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_type(size_ctype bytes)
					{ return base::declare_type(GlyphInstr::flex, bytes); }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_flex_method =
			concord_flex_method_disjoint     <
			concord_flex_cmethod_disjoint    <
			concord_builtin_method_disjoint  <
			concord_builtin_cmethod_disjoint <
			concord_method_disjoint          < symbol_builtin_method  , array_submethod  ,
			concord_cmethod_disjoint         < symbol_builtin_cmethod , array_csubmethod , Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// utf8_char:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class concord_utf8_char_cmethod_disjoint : public Base
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

		public:

			nik_ce concord_utf8_char_cmethod_disjoint() : base{} { }
			nik_ce concord_utf8_char_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_utf8_char_cmethod =
			concord_utf8_char_cmethod_disjoint <
			concord_builtin_cmethod_disjoint   <
			concord_cmethod_disjoint           < symbol_builtin_cmethod , array_csubmethod , Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_utf8_char_method_disjoint : public Base
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

		public:

			nik_ce concord_utf8_char_method_disjoint() : base{} { }
			nik_ce concord_utf8_char_method_disjoint(const facade & f) : base{f} { }

			// declare:

				nik_ce auto declare_type(size_ctype bytes)
					{ return base::declare_type(GlyphInstr::utf8_char, bytes); }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_utf8_char_method =
			concord_utf8_char_method_disjoint  <
			concord_utf8_char_cmethod_disjoint <
			concord_builtin_method_disjoint    <
			concord_builtin_cmethod_disjoint   <
			concord_method_disjoint            < symbol_builtin_method  , array_submethod  ,
			concord_cmethod_disjoint           < symbol_builtin_cmethod , array_csubmethod , Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// composite:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class concord_composite_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype		= typename base::sign_ctype;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce concord_composite_cmethod_disjoint() : base{} { }
			nik_ce concord_composite_cmethod_disjoint(const facade & f) : base{f} { }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_composite_method_disjoint : public Base
	{
		public:

			using base				= Base;
			using facade				= typename base::facade;
			using model_type			= typename base::model_type;

			nik_using_size_type_scope		(base)

			using icon_type				= typename base::icon_type;
			using icon_ctype_ref			= typename base::icon_ctype_ref;

			using sign_type				= typename base::sign_type;
			using sign_ctype			= typename base::sign_ctype;
			using sign_ctype_ref			= typename base::sign_ctype_ref;

		protected:

			template<size_type N> using array_type	= array<icon_type, size_type, N>;

			template<size_type Mark, size_type Size, typename T>
			nik_ce auto declare_image(icon_ctype_ref icon, const T & field)
				{ return base::symbol_method().template declare_image<Mark, Size>(icon, field); }

			template<size_type Field, size_type Point, typename T>
			nik_ce auto define_abstract(sign_ctype_ref sign, size_ctype v, size_ctype length, const T & value)
			{
				auto text_cival   = base::image_ctext(sign);
				auto record_ival  = base::record_submethod();
				base::record()    . copy(text_cival[Field], v);
				record_ival       . mid_set(text_cival[Point], text_cival[Point] + length);

				for (size_type k = 0; k != value.size(); ++k)
				{
					record_ival[2*k  ] = value[k].mark ();
					record_ival[2*k+1] = value[k].index();
				}

				return sign;
			}

		public:

			nik_ce concord_composite_method_disjoint() : base{} { }
			nik_ce concord_composite_method_disjoint(const facade & f) : base{f} { }

			// declare:

				template<size_type Mark, typename T>
				nik_ce auto declare_type(const T & v, size_ctype bytes, size_ctype universe)
					{ return base::symbol_method().template declare_type<Mark>(v, bytes, universe); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class concord_tuple_cmethod_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype		= typename base::sign_ctype;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		public:

			nik_ce concord_tuple_cmethod_disjoint() : base{} { }
			nik_ce concord_tuple_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_tuple_cmethod =
			concord_tuple_cmethod_disjoint     <
			concord_composite_cmethod_disjoint <
			concord_cmethod_disjoint           < symbol_tuple_cmethod , array_csubmethod , Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_tuple_method_disjoint : public Base
	{
		public:

			using base			= Base;
			using facade			= typename base::facade;
			using model_type		= typename base::model_type;

			nik_using_size_type_scope	(base)

			using icon_type			= typename base::icon_type;
			using icon_ctype_ref		= typename base::icon_ctype_ref;

			using sign_type			= typename base::sign_type;
			using sign_ctype		= typename base::sign_ctype;
			using sign_ctype_ref		= typename base::sign_ctype_ref;

		protected:

			nik_ce auto declare_image(icon_ctype_ref icon, size_ctype time, size_ctype length)
			{
				auto field = array<size_type, size_type, ImageTuple::dimension>{};
				field.fullsize();

				field[ImageTuple::index ] = icon.index();
				field[ImageTuple::time  ] = time;
				field[ImageTuple::length] = base::record().expand(1);
				field[ImageTuple::point ] = base::record().expand(length);

				return base::template
					declare_image<BookMark::tuple, ImageTuple::dimension>(icon, field);
			}

			nik_ce auto declare_abstract(icon_ctype_ref icon, size_ctype length)
				{ return declare_image(icon, ImageTime::abstract, length); }

		public:

			nik_ce concord_tuple_method_disjoint() : base{} { }
			nik_ce concord_tuple_method_disjoint(const facade & f) : base{f} { }

			// declare:

				template<typename T>
				nik_ce auto declare_type(const T & type)
				{
					size_ctype bytes    = base::total_bytes(type);
					size_ctype universe = base::max_universe(type);

					return base::template declare_type<BookMark::tuple>(type, bytes, universe);
				}

				template<auto N>
				nik_ce auto declare_type(const icon_type (&t)[N])
					{ return declare_type(typename base::template array_type<N>{t}); }

				nik_ce auto declare_concrete(icon_ctype_ref icon, size_ctype length)
					{ return declare_image(icon, ImageTime::concrete, (length << 1)); }

			// define:

				template<auto N>
				nik_ce auto define_abstract(icon_ctype_ref icon, sign_ctype (&v)[N])
				{
					auto value        = array<sign_type, size_type, N>{v};
					size_ctype length = (N << 1);
					auto sign         = declare_abstract(icon, length); // needs to type check.

					base::template define_abstract
						<ImageTuple::length, ImageTuple::point>(sign, length, length, value);

					return sign;
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_tuple_method =
			concord_tuple_method_disjoint      <
			concord_tuple_cmethod_disjoint     <
			concord_composite_method_disjoint  <
			concord_composite_cmethod_disjoint <
			concord_method_disjoint            < symbol_tuple_method  , array_submethod  ,
			concord_cmethod_disjoint           < symbol_tuple_cmethod , array_csubmethod , Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cotuple:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class concord_cotuple_cmethod_disjoint : public Base
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

		public:

			nik_ce concord_cotuple_cmethod_disjoint() : base{} { }
			nik_ce concord_cotuple_cmethod_disjoint(const facade & f) : base{f} { }
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_cotuple_cmethod =
			concord_cotuple_cmethod_disjoint   <
			concord_composite_cmethod_disjoint <
			concord_cmethod_disjoint           < symbol_cotuple_cmethod , array_csubmethod , Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class concord_cotuple_method_disjoint : public Base
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

			nik_ce auto declare_image(icon_ctype_ref icon, size_ctype time, size_ctype inject)
			{
				auto field = array<size_type, size_type, ImageCotuple::dimension>{};
				field.fullsize();

				field[ImageCotuple::index ] = icon.index();
				field[ImageCotuple::time  ] = time;
				field[ImageCotuple::inject] = base::record().expand(1);
				field[ImageCotuple::point ] = base::record().expand(2);

				return base::template
					declare_image<BookMark::cotuple, ImageCotuple::dimension>(icon, field);
			}

			nik_ce auto declare_abstract(icon_ctype_ref icon, size_ctype inject)
				{ return declare_image(icon, ImageTime::abstract, inject); }

		public:

			nik_ce concord_cotuple_method_disjoint() : base{} { }
			nik_ce concord_cotuple_method_disjoint(const facade & f) : base{f} { }

			// declare:

				template<typename T>
				nik_ce auto declare_type(const T & type)
				{
					size_ctype bytes    = base::max_bytes(type);
					size_ctype universe = base::max_universe(type);

					return base::template declare_type<BookMark::cotuple>(type, bytes, universe);
				}

				template<auto N>
				nik_ce auto declare_type(const icon_type (&t)[N])
					{ return declare_type(typename base::template array_type<N>{t}); }

				nik_ce auto declare_concrete(icon_ctype_ref icon, size_ctype inject)
					{ return declare_image(icon, ImageTime::concrete, inject); }

			// define:

				template<auto N>
				nik_ce auto define_abstract(icon_ctype_ref icon, size_ctype inject, sign_ctype_ref value)
				{
					size_ctype length = (N << 1);
					auto sign         = declare_abstract(icon, inject); // needs to type check.

					base::template define_abstract
						<ImageCotuple::inject, ImageCotuple::point>(sign, inject, length, value);

					return sign;
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using concord_cotuple_method =
			concord_cotuple_method_disjoint    <
			concord_cotuple_cmethod_disjoint   <
			concord_composite_method_disjoint  <
			concord_composite_cmethod_disjoint <
			concord_method_disjoint            < symbol_cotuple_method  , array_submethod  ,
			concord_cmethod_disjoint           < symbol_cotuple_cmethod , array_csubmethod , Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// function:

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

			nik_ce auto declare_image(icon_ctype_ref icon, size_ctype time, size_ctype length)
			{
				auto field = array<size_type, size_type, ImageFunction::dimension>{};
				field.fullsize();

				field[ImageFunction::index ] = icon.index();
				field[ImageFunction::time  ] = time;
				field[ImageFunction::length] = base::record().expand(1);
				field[ImageFunction::point ] = base::record().expand(length);

				return base::template
					declare_image<BookMark::function, ImageFunction::dimension>(icon, field);
			}

			nik_ce auto declare_abstract(icon_ctype_ref icon, size_ctype length)
				{ return declare_image(icon, ImageTime::abstract, length); }

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

					return base::template declare_type<BookMark::function>(type, bytes, universe);
				}

				template<auto N>
				nik_ce auto declare_type(const icon_type (&t)[N])
					{ return declare_type(typename base::template array_type<N>{t}); }

				nik_ce auto declare_concrete(icon_ctype_ref icon, size_ctype length)
					{ return declare_image(icon, ImageTime::concrete, length); }

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

// list:

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// identity:

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// exists:

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// forall:

/***********************************************************************************************************************/

// :

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

