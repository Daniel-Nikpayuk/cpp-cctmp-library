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

// array class:

	// facades are intended to be shallow copies.

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// packs:

	template<auto...> struct T_pack_Vs; // intentionally undefined.

/***********************************************************************************************************************/

// types:

	// enum:

		using global_enum_type		= unsigned char;
		using genum_type		= global_enum_type;
		using genum_ctype		= global_enum_type const;

/***********************************************************************************************************************/

// alias:

	template<typename Type>
	struct alias
	{
		using type		= Type;
		using type_ptr		= type*;
		using type_cptr		= type_ptr const;
		using type_ref		= type&;

		using ctype		= type const;
		using ctype_ptr		= ctype*;
		using ctype_cptr	= ctype_ptr const;
		using ctype_ref		= ctype&;
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// model:

/***********************************************************************************************************************/

// immutable:

	template<typename Type, typename SizeType>
	class array_cmodel
	{
		public:

			using facade				= array_cmodel; // method compatible.

			nik_using_name_alias_scope_type		( type, Type)
			nik_using_name_alias_scope_ctype	(ctype, Type)

			nik_using_name_alias_scope_type		( citer_type, ctype_ptr)
			nik_using_name_alias_scope_ctype	(citer_ctype, ctype_ptr)

			nik_using_name_alias_scope_type		( cderef_type, ctype)
			nik_using_name_alias_scope_ctype	(cderef_ctype, ctype)

			nik_using_size_type_alias		(SizeType)

		protected:

			ctype_ptr  initial; // compile time compatible.
			size_type terminal; // compile time compatible.

		public:

			nik_ce array_cmodel() : initial{}, terminal{} { }

			// initial:

				nik_ce ctype_ptr cbegin() const { return initial; }

			// terminal:

				nik_ce size_type size() const { return terminal; }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, SizeType Size>
	class array_model
	{
		public:

			using facade				= array_model; // method compatible.

			nik_using_name_alias_scope_type		( type, Type)
			nik_using_name_alias_scope_ctype	(ctype, Type)

			nik_using_name_alias_scope_type		( iter_type, type_ptr)
			nik_using_name_alias_scope_ctype	(iter_ctype, type_ptr)

			nik_using_name_alias_scope_type		( citer_type, ctype_ptr)
			nik_using_name_alias_scope_ctype	(citer_ctype, ctype_ptr)

			nik_using_name_alias_scope_type		( deref_type, type)
			nik_using_name_alias_scope_ctype	(deref_ctype, type)

			nik_using_name_alias_scope_type		( cderef_type, ctype)
			nik_using_name_alias_scope_ctype	(cderef_ctype, ctype)

			nik_using_size_type_alias		(SizeType)

		public:

			nik_ces size_type length() { return Size; }

		protected:

			type initial[Size]; // compile time compatible.
			size_type terminal; // compile time compatible.

		public:

			nik_ce array_model() : initial{}, terminal{} { }

			// initial:

				nik_ce ctype_ptr cbegin() const { return initial; }
				nik_ce  type_ptr  begin()       { return initial; }

			// terminal:

				nik_ce size_type size() const { return terminal; }
				nik_ce void set_size(size_ctype n) { terminal = n; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// facade:

/***********************************************************************************************************************/

// pre:

	template<typename Model, typename AdjModel>
	class array_prefacade
	{
		public:

			using model_type		= Model;
			using adj_model_type_ptr	= typename alias<AdjModel>::type_ptr;
			using adj_model_type_cptr	= typename alias<AdjModel>::type_cptr;

			nik_using_name_scope_type	( type, model_type)
			nik_using_name_scope_ctype	(ctype, model_type)

			nik_using_name_scope_member	( iter_type, model_type,  iter_type)
			nik_using_name_scope_member	(iter_ctype, model_type, iter_ctype)

			nik_using_name_scope_member	( citer_type, model_type,  citer_type)
			nik_using_name_scope_member	(citer_ctype, model_type, citer_ctype)

			nik_using_name_scope_member	( deref_type, model_type,  deref_type)
			nik_using_name_scope_member	(deref_ctype, model_type, deref_ctype)

			nik_using_name_scope_member	( cderef_type, model_type,  cderef_type)
			nik_using_name_scope_member	(cderef_ctype, model_type, cderef_ctype)

			nik_using_size_type_scope	(model_type)

		protected:

			adj_model_type_ptr model;

		public:

			nik_ce array_prefacade() : model{} { }
			nik_ce array_prefacade(adj_model_type_cptr m) : model{m} { }

			// initial:

				nik_ce ctype_ptr cbegin() const { return model->cbegin(); }

			// terminal:

				nik_ce size_type size() const { return model->size(); }
	};

/***********************************************************************************************************************/

// immutable:

	template<typename Model>
	class array_cfacade : public array_prefacade<Model, Model const>
	{
		public:

			using facade			= array_cfacade; // method compatible.
			using base			= array_prefacade<Model, Model const>;

			using model_type		= typename base::model_type;
			using model_ctype_ptr		= typename base::adj_model_type_ptr;
			using model_ctype_cptr		= typename base::adj_model_type_cptr;

			nik_using_name_scope_type	( type, base)
			nik_using_name_scope_ctype	(ctype, base)

			nik_using_name_scope_member	( citer_type, base,  citer_type)
			nik_using_name_scope_member	(citer_ctype, base, citer_ctype)

			nik_using_name_scope_member	( cderef_type, base,  cderef_type)
			nik_using_name_scope_member	(cderef_ctype, base, cderef_ctype)

			nik_using_size_type_scope	(base)

		public:

			nik_ce array_cfacade() : base{} { }
			nik_ce array_cfacade(model_ctype_cptr m) : base{m} { }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Model>
	class array_facade : public array_prefacade<Model, Model>
	{
		public:

			using facade			= array_facade; // method compatible.
			using base			= array_prefacade<Model, Model>;

			using model_type		= typename base::model_type;
			using model_type_ptr		= typename base::adj_model_type_ptr;
			using model_type_cptr		= typename base::adj_model_type_cptr;

			nik_using_name_scope_type	( type, base)
			nik_using_name_scope_ctype	(ctype, base)

			nik_using_name_scope_member	( iter_type, base,  iter_type)
			nik_using_name_scope_member	(iter_ctype, base, iter_ctype)

			nik_using_name_scope_member	( citer_type, base,  citer_type)
			nik_using_name_scope_member	(citer_ctype, base, citer_ctype)

			nik_using_name_scope_member	( deref_type, base,  deref_type)
			nik_using_name_scope_member	(deref_ctype, base, deref_ctype)

			nik_using_name_scope_member	( cderef_type, base,  cderef_type)
			nik_using_name_scope_member	(cderef_ctype, base, cderef_ctype)

			nik_using_size_type_scope	(base)

		public:

			nik_ces size_type length() { return model_type::length(); }

		public:

			nik_ce array_facade() : base{} { }
			nik_ce array_facade(model_type_cptr m) : base{m} { }

			// initial:

				nik_ce type_ptr begin() { return base::model->begin(); }

			// terminal:

				nik_ce void set_size(size_ctype n) { base::model->set_size(n); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// subfacade:

/***********************************************************************************************************************/

// pre:

	template<typename Model, typename AdjModel>
	class array_presubfacade
	{
		public:

			using model_type		= Model;
			using adj_model_type_ptr	= typename alias<AdjModel>::type_ptr;
			using adj_model_type_cptr	= typename alias<AdjModel>::type_cptr;

			nik_using_name_scope_type	( type, model_type)
			nik_using_name_scope_ctype	(ctype, model_type)

			nik_using_name_scope_member	( iter_type, model_type,  iter_type)
			nik_using_name_scope_member	(iter_ctype, model_type, iter_ctype)

			nik_using_name_scope_member	( citer_type, model_type,  citer_type)
			nik_using_name_scope_member	(citer_ctype, model_type, citer_ctype)

			nik_using_name_scope_member	( deref_type, model_type,  deref_type)
			nik_using_name_scope_member	(deref_ctype, model_type, deref_ctype)

			nik_using_name_scope_member	( cderef_type, model_type,  cderef_type)
			nik_using_name_scope_member	(cderef_ctype, model_type, cderef_ctype)

			nik_using_size_type_scope	(model_type)

		protected:

			adj_model_type_ptr model;
			size_type  initial;
			size_type terminal;

		protected:

			nik_ce size_type right() const { return initial + terminal; }

		public:

			nik_ce array_presubfacade() : model{}, initial{}, terminal{} { }
			nik_ce array_presubfacade(adj_model_type_cptr m) : model{m}, initial{}, terminal{} { }

			// set: aligns with the start, finish paradigm.

				nik_ce void fast_mid_set(size_ctype s, size_ctype f) { initial = s; terminal = f - s; }

				nik_ce void fast_left_set  (size_ctype f) { fast_mid_set(0, f); }
				nik_ce void fast_right_set (size_ctype s) { fast_mid_set(s, model->size()); }
				nik_ce void fast_full_set  (            ) { fast_mid_set(0, model->size()); }

				nik_ce void mid_set(size_ctype s, size_ctype f) { if (s <= f) { fast_mid_set(s, f); } }

				nik_ce void left_set  (size_ctype f) { mid_set(0, f); }
				nik_ce void right_set (size_ctype s) { mid_set(s, model->size()); }
				nik_ce void full_set  (            ) { mid_set(0, model->size()); }

			// shift:

				nik_ce void fast_left_shift  (size_ctype n = 1) { initial -= n; }
				nik_ce void fast_right_shift (size_ctype n = 1) { initial += n; }

				nik_ce void left_shift(size_ctype n = 1)
					{ if (n <= initial) { fast_left_shift(n); } }

				nik_ce void right_shift(size_ctype n = 1)
					{ if (n <= right_capacity()) { fast_right_shift(n); } }

			// initial:

				nik_ce ctype_ptr cbegin() const { return model->cbegin() + initial; }

				nik_ce void fast_left_outward (size_ctype n = 1) { initial -= n; terminal += n; }
				nik_ce void fast_left_inward  (size_ctype n = 1) { initial += n; terminal -= n; }

				nik_ce void left_outward(size_ctype n = 1)
					{ if (n <=  initial) { fast_left_outward(n); } }

				nik_ce void left_inward(size_ctype n = 1)
					{ if (n <= terminal) { fast_left_inward(n); } }

			// terminal:

				nik_ce size_type size() const { return terminal; }
				nik_ce size_type right_capacity() const { return model->size() - right(); }

				nik_ce void fast_right_inward  (size_ctype n = 1) { terminal -= n; }
				nik_ce void fast_right_outward (size_ctype n = 1) { terminal += n; }

				nik_ce void right_inward(size_ctype n = 1)
					{ if (n <= terminal) { fast_right_inward(n); } }

				nik_ce void right_outward(size_ctype n = 1)
					{ if (n <= right_capacity()) { fast_right_outward(n); } }
	};

/***********************************************************************************************************************/

// immutable:

	template<typename Model>
	class array_csubfacade : public array_presubfacade<Model, Model const>
	{
		public:

			using facade			= array_csubfacade; // method compatible.
			using base			= array_presubfacade<Model, Model const>;

			using model_type		= typename base::model_type;
			using model_ctype_ptr		= typename base::adj_model_type_ptr;
			using model_ctype_cptr		= typename base::adj_model_type_cptr;

			nik_using_name_scope_type	( type, base)
			nik_using_name_scope_ctype	(ctype, base)

			nik_using_name_scope_member	( citer_type, base,  citer_type)
			nik_using_name_scope_member	(citer_ctype, base, citer_ctype)

			nik_using_name_scope_member	( cderef_type, base,  cderef_type)
			nik_using_name_scope_member	(cderef_ctype, base, cderef_ctype)

			nik_using_size_type_scope	(base)

		public:

			nik_ce array_csubfacade() : base{} { }
			nik_ce array_csubfacade(model_ctype_cptr m) : base{m} { }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Model>
	class array_subfacade : public array_presubfacade<Model, Model>
	{
		public:

			using facade			= array_subfacade; // method compatible.
			using base			= array_presubfacade<Model, Model>;

			using model_type		= typename base::model_type;
			using model_type_ptr		= typename base::adj_model_type_ptr;
			using model_type_cptr		= typename base::adj_model_type_cptr;

			nik_using_name_scope_type	( type, base)
			nik_using_name_scope_ctype	(ctype, base)

			nik_using_name_scope_member	( iter_type, base,  iter_type)
			nik_using_name_scope_member	(iter_ctype, base, iter_ctype)

			nik_using_name_scope_member	( citer_type, base,  citer_type)
			nik_using_name_scope_member	(citer_ctype, base, citer_ctype)

			nik_using_name_scope_member	( deref_type, base,  deref_type)
			nik_using_name_scope_member	(deref_ctype, base, deref_ctype)

			nik_using_name_scope_member	( cderef_type, base,  cderef_type)
			nik_using_name_scope_member	(cderef_ctype, base, cderef_ctype)

			nik_using_size_type_scope	(base)

		public:

			nik_ce array_subfacade() : base{} { }
			nik_ce array_subfacade(model_type_cptr m) : base{m} { }

			// initial:

				nik_ce type_ptr begin() { return base::model->begin() + base::initial; }

			// terminal:

				// nothing yet.
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// interface:

/***********************************************************************************************************************/

// methods:

	// array sub:

		template<typename> class array_csubmethod_disjoint;
		template<typename> class array_submethod_disjoint;

		// syntactic sugar:

			template<typename Facade>
			using array_csubmethod =
				array_csubmethod_disjoint < Facade >;

			template<typename Facade>
			using array_submethod =
				array_submethod_disjoint  <
				array_csubmethod_disjoint < Facade >>;

	// array:

		template<typename> class array_cmethod_disjoint;
		template<typename> class array_method_disjoint;

		// syntactic sugar:

			template<typename Facade>
			using array_cmethod =
				array_cmethod_disjoint    <
				array_csubmethod_disjoint < Facade >>;

			template<typename Facade>
			using array_method =
				array_method_disjoint    <
				array_submethod_disjoint <
				array_cmethod            < Facade >>>;

	// unique:

		template<typename> class unique_method;

		// syntactic sugar:

				// reimplement as an actual class ?

			template<typename Facade>
			using unique_cmethod = array_cmethod<Facade>;

	// table:

		template<typename> class table_csubmethod;
		template<typename> class table_submethod;

/***********************************************************************************************************************/

// immutable:

	template<typename Type, typename SizeType, template<typename> typename CMethodType = array_cmethod>
	class carray : public CMethodType<array_cmodel<Type, SizeType>>
	{
		public:

			using model_type		= array_cmodel<Type, SizeType>;
			using base			= CMethodType<model_type>;
			using csubfacade_type		= array_csubfacade<model_type>;
			using cfacade_type		= array_cfacade<model_type>;

			nik_using_name_scope_type	( type, base)
			nik_using_name_scope_ctype	(ctype, base)

			nik_using_size_type_scope	(base)

		public:

			nik_ce carray() : base{} { }

			nik_ce carray(ctype_cptr i, size_ctype t) : base{i, t} { }

			template<auto N>
			nik_ce carray(const Type (&a)[N]) : base{a} { }

			// subequip:

				template<typename CMethod>
				nik_ce auto csubequip() const -> CMethod
					{ return csubfacade_type{static_cast<model_type const*>(this)}; }

			// equip:

				template<typename CMethod>
				nik_ce auto cequip() const -> CMethod
					{ return cfacade_type{static_cast<model_type const*>(this)}; }
	};

/***********************************************************************************************************************/

// mutable:

	template
	<
		typename Type, typename SizeType, SizeType Size,
		template<typename> typename MethodType = array_method
	>
	class array : public MethodType<array_model<Type, SizeType, Size>>
	{
		public:

			using model_type		= array_model<Type, SizeType, Size>;
			using base			= MethodType<model_type>;
			using csubfacade_type		= array_csubfacade<model_type>;
			using subfacade_type		= array_subfacade<model_type>;
			using cfacade_type		= array_cfacade<model_type>;
			using facade_type		= array_facade<model_type>;

			nik_using_name_scope_type	( type, base)
			nik_using_name_scope_ctype	(ctype, base)

			nik_using_size_type_scope	(base)

		public:

			nik_ce array() : base{} { }

			template<typename T, auto N>
			nik_ce array(const T (&a)[N]) : base{a} { }

			// subequip:

				template<typename CMethod>
				nik_ce auto csubequip() const -> CMethod
					{ return csubfacade_type{static_cast<model_type const*>(this)}; }

				template<typename Method>
				nik_ce auto subequip() -> Method
					{ return subfacade_type{static_cast<model_type*>(this)}; }

			// equip:

				template<typename CMethod>
				nik_ce auto cequip() const -> CMethod
					{ return cfacade_type{static_cast<model_type const*>(this)}; }

				template<typename Method>
				nik_ce auto equip() -> Method
					{ return facade_type{static_cast<model_type*>(this)}; }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// string (literal):

/***********************************************************************************************************************/

// immutable:

	template<typename Type, typename SizeType>
	struct cstring : public carray<Type, SizeType>
	{
		using base			= carray<Type, SizeType>;
		using cfacade_type		= array_cfacade<cstring>;

		nik_using_name_scope_type	( type, base)
		nik_using_name_scope_ctype	(ctype, base)

		nik_using_size_type_scope	(base)

		nik_ce cstring() : base{} { }

		template<auto N>
		nik_ce cstring(const Type (&s)[N]) : base{s, N-1} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// unique array:

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, SizeType Size>
	class unique_array : public array<Type, SizeType, Size, unique_method>
	{
		public:

			using base			= array<Type, SizeType, Size, unique_method>;
			using cfacade_type		= typename base::cfacade_type;
			using facade_type		= typename base::facade_type;

			nik_using_name_scope_type	( type, base)
			nik_using_name_scope_ctype	(ctype, base)

			nik_using_size_type_scope	(base)

		public:

			nik_ce unique_array() : base{} { }

			template<typename T, auto N>
			nik_ce unique_array(const T (&a)[N]) : base{a} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// table:

/***********************************************************************************************************************/

// immutable:

	template<typename Type, typename SizeType, SizeType RowSize, SizeType ColSize>
	class ctable : public carray<Type, SizeType, table_csubmethod>
	{
		public:

			using base			= carray<Type, SizeType, table_csubmethod>;
			using cfacade_type		= typename base::cfacade_type;

			nik_using_name_scope_type	( type, base)
			nik_using_name_scope_ctype	(ctype, base)

			nik_using_size_type_scope	(base)

		public:

			nik_ce ctable() : base{} { }

			template<typename T>
			nik_ce ctable(const T (&a)[RowSize * ColSize]) : base{a} { }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, SizeType RowSize, SizeType ColSize>
	class table : public array<Type, SizeType, RowSize * ColSize, table_submethod>
	{
		public:

			using base			= array<Type, SizeType, RowSize * ColSize, table_submethod>;
			using cfacade_type		= typename base::cfacade_type;
			using facade_type		= typename base::facade_type;

			nik_using_name_scope_type	( type, base)
			nik_using_name_scope_ctype	(ctype, base)

			nik_using_size_type_scope	(base)

		protected:

			nik_ce void initialize()
			{
				base::template equip<array_method<facade_type>>().fullsize();
				base::set_sizes(RowSize, ColSize);
			}

		public:

			nik_ce table() : base{} { initialize(); }

			template<typename T, auto N>
			nik_ce table(const T (&a)[N]) : base{a} { initialize(); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

