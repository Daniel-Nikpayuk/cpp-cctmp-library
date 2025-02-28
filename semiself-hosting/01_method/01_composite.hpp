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

// concord:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class composite_cmethod_disjoint : public Base
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

			nik_ce composite_cmethod_disjoint() : base{} { }
			nik_ce composite_cmethod_disjoint(const facade & f) : base{f} { }

			// sub(ordinate) icon:

				nik_ce auto sub_icon(icon_ctype_ref icon, size_ctype n) const
					{ return base::symbol_cmethod().sub_icon(icon, n); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class composite_method_disjoint : public Base
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
			nik_ce auto define_abstract(sign_ctype_ref sign, size_ctype v, size_ctype n, const T & value)
			{
				auto text_cival   = base::image_ctext(sign);
				auto record_ival  = base::record_submethod();
				base::record()    . copy(text_cival[Field], v);
				record_ival       . mid_set(text_cival[Point], text_cival[Point] + n);

				for (size_type k = 0; k != value.size(); ++k)
				{
					record_ival[2*k  ] = value[k].mark ();
					record_ival[2*k+1] = value[k].index();
				}

				return sign;
			}

		public:

			nik_ce composite_method_disjoint() : base{} { }
			nik_ce composite_method_disjoint(const facade & f) : base{f} { }

			// declare:

				template<size_type Mark, size_type Instr, typename T>
				nik_ce auto declare_type(const T & v, size_ctype bytes, size_ctype universe)
				{
					return base::symbol_method().template
						declare_type<Mark, Instr>(v, bytes, universe);
				}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// tuple:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class tuple_cmethod_disjoint : public Base
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

			nik_ce tuple_cmethod_disjoint() : base{} { }
			nik_ce tuple_cmethod_disjoint(const facade & f) : base{f} { }

			// sub(ordinate) sign:

				nik_ce auto sub_sign(sign_ctype_ref sign, size_ctype n) const
				{
					auto text_cival   = base::image_ctext(sign);
					size_ctype start  = text_cival[ImageTuple::point];
					size_ctype finish = start + text_cival[ImageTuple::length];
					auto record_cival = base::record_csubmethod();
					record_cival      . mid_set(start, finish);
					size_ctype pos    = (n << 1);

					return base::symbol_cmethod().
						image_cmethod().make_sign(record_cival[pos], record_cival[pos+1]);
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using tuple_cmethod =
			tuple_cmethod_disjoint     <
			composite_cmethod_disjoint <
			concord_cmethod_disjoint   < Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class tuple_method_disjoint : public Base
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

			nik_ce auto declare_image(
				icon_ctype_ref icon, size_ctype time, size_ctype length, size_ctype point)
			{
				auto field = array<size_type, size_type, ImageTuple::dimension>{};
				field.fullsize();

				field[ImageTuple::index ] = icon.index();
				field[ImageTuple::time  ] = time;
				field[ImageTuple::length] = length;
				field[ImageTuple::point ] = point;

				return base::template
					declare_image<BookMark::tuple, ImageTuple::dimension>(icon, field);
			}

			nik_ce auto declare_abstract(icon_ctype_ref icon, size_ctype n)
			{
				size_ctype length = base::record().expand(1); // only expand if not duplicate record.
				size_ctype point  = base::record().expand(n);

				return declare_image(icon, ImageTime::abstract, length, point);
			}

		public:

			nik_ce tuple_method_disjoint() : base{} { }
			nik_ce tuple_method_disjoint(const facade & f) : base{f} { }

			// declare:

				template<typename T>
				nik_ce auto declare_type(const T & type)
				{
					size_ctype bytes    = base::total_bytes(type);
					size_ctype universe = base::max_universe(type);

					return base::template declare_type
						<BookMark::tuple, GlyphInstr::tuple>(type, bytes, universe);
				}

				template<auto N>
				nik_ce auto declare_type(const icon_type (&t)[N])
					{ return declare_type(typename base::template array_type<N>{t}); }

				nik_ce auto declare_concrete(icon_ctype_ref icon, size_ctype l_adder, size_ctype addr)
					{ return declare_image(icon, ImageTime::concrete, l_adder, addr); }

			// define:

				template<auto N>
				nik_ce auto define_abstract(icon_ctype_ref icon, sign_ctype (&v)[N])
				{
					auto value   = array<sign_type, size_type, N>{v};
					size_ctype n = (N << 1);
					auto sign    = declare_abstract(icon, n); // needs to type check.

					base::template define_abstract
						<ImageTuple::length, ImageTuple::point>(sign, n, n, value);

					return sign;
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using tuple_method =
			tuple_method_disjoint      <
			tuple_cmethod_disjoint     <
			composite_method_disjoint  <
			composite_cmethod_disjoint <
			concord_method_disjoint    <
			concord_cmethod_disjoint   < Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// cotuple:

/***********************************************************************************************************************/

// immutable:

	template<typename Base>
	class cotuple_cmethod_disjoint : public Base
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

			nik_ce cotuple_cmethod_disjoint() : base{} { }
			nik_ce cotuple_cmethod_disjoint(const facade & f) : base{f} { }

			// sub(ordinate) sign:

				nik_ce auto sub_sign(sign_ctype_ref sign) const
				{
					auto text_cival   = base::image_ctext(sign);
					size_ctype start  = text_cival[ImageCotuple::point];
					size_ctype finish = start + 2;
					auto record_cival = base::record_csubmethod();
					record_cival      . mid_set(start, finish);

					return base::symbol_cmethod().
						image_cmethod().make_sign(record_cival[0], record_cival[1]);
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using cotuple_cmethod =
			cotuple_cmethod_disjoint   <
			composite_cmethod_disjoint <
			concord_cmethod_disjoint   < Facade >>>;

/***********************************************************************************************************************/

// mutable:

	template<typename Base>
	class cotuple_method_disjoint : public Base
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
				icon_ctype_ref icon, size_ctype time, size_ctype inject, size_ctype point)
			{
				auto field = array<size_type, size_type, ImageCotuple::dimension>{};
				field.fullsize();

				field[ImageCotuple::index ] = icon.index();
				field[ImageCotuple::time  ] = time;
				field[ImageCotuple::inject] = inject;
				field[ImageCotuple::point ] = point;

				return base::template
					declare_image<BookMark::cotuple, ImageCotuple::dimension>(icon, field);
			}

			nik_ce auto declare_abstract(icon_ctype_ref icon)
			{
				size_ctype inject = base::record().expand(1);
				size_ctype point  = base::record().expand(2);

				return declare_image(icon, ImageTime::abstract, inject, point);
			}

		public:

			nik_ce cotuple_method_disjoint() : base{} { }
			nik_ce cotuple_method_disjoint(const facade & f) : base{f} { }

			// declare:

				template<typename T>
				nik_ce auto declare_type(const T & type)
				{
					size_ctype bytes    = base::max_bytes(type);
					size_ctype universe = base::max_universe(type);

					return base::template declare_type
						<BookMark::cotuple, GlyphInstr::cotuple>(type, bytes, universe);
				}

				template<auto N>
				nik_ce auto declare_type(const icon_type (&t)[N])
					{ return declare_type(typename base::template array_type<N>{t}); }

				nik_ce auto declare_concrete(icon_ctype_ref icon, size_ctype inject, size_ctype addr)
					{ return declare_image(icon, ImageTime::concrete, inject, addr); }

			// define:

				nik_ce auto define_abstract(icon_ctype_ref icon, size_ctype inject, sign_ctype_ref v)
				{
					nik_ce size_type N = 2;
					auto value         = array<sign_type, size_type, N>{{v}};
					auto sign          = declare_abstract(icon); // needs to type check.

					base::template define_abstract
						<ImageCotuple::inject, ImageCotuple::point>(sign, inject, N, value);

					return sign;
				}
	};

	// syntactic sugar:

		template<typename Facade>
		using cotuple_method =
			cotuple_method_disjoint    <
			cotuple_cmethod_disjoint   <
			composite_method_disjoint  <
			composite_cmethod_disjoint <
			concord_method_disjoint    <
			concord_cmethod_disjoint   < Facade >>>>>>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

