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

// array:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// model (base):

/***********************************************************************************************************************/

// immutable:

	template<typename Type, typename SizeType>
	class array_cmodel
	{
		public:

			using type			= typename alias<Type>::type;
			using type_ptr			= typename alias<Type>::type_ptr;
			using type_cptr			= typename alias<Type>::type_cptr;
			using type_ref			= typename alias<Type>::type_ref;

			using ctype			= typename alias<Type>::ctype;
			using ctype_ptr			= typename alias<Type>::ctype_ptr;
			using ctype_cptr		= typename alias<Type>::ctype_cptr;
			using ctype_ref			= typename alias<Type>::ctype_ref;

			using citer_type		= typename alias<ctype_ptr>::type;
			using citer_type_ptr		= typename alias<ctype_ptr>::type_ptr;
			using citer_type_cptr		= typename alias<ctype_ptr>::type_cptr;
			using citer_type_ref		= typename alias<ctype_ptr>::type_ref;

			using citer_ctype		= typename alias<ctype_ptr>::ctype;
			using citer_ctype_ptr		= typename alias<ctype_ptr>::ctype_ptr;
			using citer_ctype_cptr		= typename alias<ctype_ptr>::ctype_cptr;
			using citer_ctype_ref		= typename alias<ctype_ptr>::ctype_ref;

			using cderef_type		= typename alias<ctype>::type;
			using cderef_type_ptr		= typename alias<ctype>::type_ptr;
			using cderef_type_cptr		= typename alias<ctype>::type_cptr;
			using cderef_type_ref		= typename alias<ctype>::type_ref;

			using cderef_ctype		= typename alias<ctype>::ctype;
			using cderef_ctype_ptr		= typename alias<ctype>::ctype_ptr;
			using cderef_ctype_cptr		= typename alias<ctype>::ctype_cptr;
			using cderef_ctype_ref		= typename alias<ctype>::ctype_ref;

			using size_type			= typename alias<SizeType>::type;
			using size_ctype		= typename alias<SizeType>::ctype;

		protected:

			ctype_ptr  initial; // compile time compatible.
			size_type terminal; // compile time compatible.

		protected:

			nik_ce void assign(ctype_cptr i, size_ctype t) // inheritance convenience
			{
				 initial = i;
				terminal = t;
			}

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

			using type			= typename alias<Type>::type;
			using type_ptr			= typename alias<Type>::type_ptr;
			using type_cptr			= typename alias<Type>::type_cptr;
			using type_ref			= typename alias<Type>::type_ref;

			using ctype			= typename alias<Type>::ctype;
			using ctype_ptr			= typename alias<Type>::ctype_ptr;
			using ctype_cptr		= typename alias<Type>::ctype_cptr;
			using ctype_ref			= typename alias<Type>::ctype_ref;

			using citer_type		= typename alias<ctype_ptr>::type;
			using citer_type_ptr		= typename alias<ctype_ptr>::type_ptr;
			using citer_type_cptr		= typename alias<ctype_ptr>::type_cptr;
			using citer_type_ref		= typename alias<ctype_ptr>::type_ref;

			using citer_ctype		= typename alias<ctype_ptr>::ctype;
			using citer_ctype_ptr		= typename alias<ctype_ptr>::ctype_ptr;
			using citer_ctype_cptr		= typename alias<ctype_ptr>::ctype_cptr;
			using citer_ctype_ref		= typename alias<ctype_ptr>::ctype_ref;

			using iter_type			= typename alias<type_ptr>::type;
			using iter_type_ptr		= typename alias<type_ptr>::type_ptr;
			using iter_type_cptr		= typename alias<type_ptr>::type_cptr;
			using iter_type_ref		= typename alias<type_ptr>::type_ref;

			using iter_ctype		= typename alias<type_ptr>::ctype;
			using iter_ctype_ptr		= typename alias<type_ptr>::ctype_ptr;
			using iter_ctype_cptr		= typename alias<type_ptr>::ctype_cptr;
			using iter_ctype_ref		= typename alias<type_ptr>::ctype_ref;

			using cderef_type		= typename alias<ctype>::type;
			using cderef_type_ptr		= typename alias<ctype>::type_ptr;
			using cderef_type_cptr		= typename alias<ctype>::type_cptr;
			using cderef_type_ref		= typename alias<ctype>::type_ref;

			using cderef_ctype		= typename alias<ctype>::ctype;
			using cderef_ctype_ptr		= typename alias<ctype>::ctype_ptr;
			using cderef_ctype_cptr		= typename alias<ctype>::ctype_cptr;
			using cderef_ctype_ref		= typename alias<ctype>::ctype_ref;

			using deref_type		= typename alias<type>::type;
			using deref_type_ptr		= typename alias<type>::type_ptr;
			using deref_type_cptr		= typename alias<type>::type_cptr;
			using deref_type_ref		= typename alias<type>::type_ref;

			using deref_ctype		= typename alias<type>::ctype;
			using deref_ctype_ptr		= typename alias<type>::ctype_ptr;
			using deref_ctype_cptr		= typename alias<type>::ctype_cptr;
			using deref_ctype_ref		= typename alias<type>::ctype_ref;

			using size_type			= typename alias<SizeType>::type;
			using size_ctype		= typename alias<SizeType>::ctype;

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

// immutable:

	template<typename Model>
	class array_cfacade
	{
		public:

			using model_ctype_ptr		= typename alias<Model>::ctype_ptr;
			using model_ctype_cptr		= typename alias<Model>::ctype_cptr;

			using type			= typename Model::type;
			using type_ptr			= typename Model::type_ptr;
			using type_cptr			= typename Model::type_cptr;
			using type_ref			= typename Model::type_ref;

			using ctype			= typename Model::ctype;
			using ctype_ptr			= typename Model::ctype_ptr;
			using ctype_cptr		= typename Model::ctype_cptr;
			using ctype_ref			= typename Model::ctype_ref;

			using citer_type		= typename Model::citer_type;
			using citer_type_ptr		= typename Model::citer_type_ptr;
			using citer_type_cptr		= typename Model::citer_type_cptr;
			using citer_type_ref		= typename Model::citer_type_ref;

			using citer_ctype		= typename Model::citer_ctype;
			using citer_ctype_ptr		= typename Model::citer_ctype_ptr;
			using citer_ctype_cptr		= typename Model::citer_ctype_cptr;
			using citer_ctype_ref		= typename Model::citer_ctype_ref;

			using cderef_type		= typename Model::cderef_type;
			using cderef_type_ptr		= typename Model::cderef_type_ptr;
			using cderef_type_cptr		= typename Model::cderef_type_cptr;
			using cderef_type_ref		= typename Model::cderef_type_ref;

			using cderef_ctype		= typename Model::cderef_ctype;
			using cderef_ctype_ptr		= typename Model::cderef_ctype_ptr;
			using cderef_ctype_cptr		= typename Model::cderef_ctype_cptr;
			using cderef_ctype_ref		= typename Model::cderef_ctype_ref;

			using size_type			= typename Model::size_type;
			using size_ctype		= typename Model::size_ctype;

		protected:

			model_ctype_ptr model;

		public:

			nik_ce array_cfacade() : model{} { }
			nik_ce array_cfacade(model_ctype_cptr m) : model{m} { }

			template<typename CMethod>
			nik_ce auto cpivot() const -> CMethod { return array_cfacade{model}; }

			// initial:

				nik_ce citer_type cbegin() const { return model->cbegin(); }

			// terminal:

				nik_ce size_type size() const { return model->size(); }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Model>
	class array_facade
	{
		public:

			using model_type_ptr		= typename alias<Model>::type_ptr;
			using model_type_cptr		= typename alias<Model>::type_cptr;

			using type			= typename Model::type;
			using type_ptr			= typename Model::type_ptr;
			using type_cptr			= typename Model::type_cptr;
			using type_ref			= typename Model::type_ref;

			using ctype			= typename Model::ctype;
			using ctype_ptr			= typename Model::ctype_ptr;
			using ctype_cptr		= typename Model::ctype_cptr;
			using ctype_ref			= typename Model::ctype_ref;

			using citer_type		= typename Model::citer_type;
			using citer_type_ptr		= typename Model::citer_type_ptr;
			using citer_type_cptr		= typename Model::citer_type_cptr;
			using citer_type_ref		= typename Model::citer_type_ref;

			using citer_ctype		= typename Model::citer_ctype;
			using citer_ctype_ptr		= typename Model::citer_ctype_ptr;
			using citer_ctype_cptr		= typename Model::citer_ctype_cptr;
			using citer_ctype_ref		= typename Model::citer_ctype_ref;

			using iter_type			= typename Model::iter_type;
			using iter_type_ptr		= typename Model::iter_type_ptr;
			using iter_type_cptr		= typename Model::iter_type_cptr;
			using iter_type_ref		= typename Model::iter_type_ref;

			using iter_ctype		= typename Model::iter_ctype;
			using iter_ctype_ptr		= typename Model::iter_ctype_ptr;
			using iter_ctype_cptr		= typename Model::iter_ctype_cptr;
			using iter_ctype_ref		= typename Model::iter_ctype_ref;

			using cderef_type		= typename Model::cderef_type;
			using cderef_type_ptr		= typename Model::cderef_type_ptr;
			using cderef_type_cptr		= typename Model::cderef_type_cptr;
			using cderef_type_ref		= typename Model::cderef_type_ref;

			using cderef_ctype		= typename Model::cderef_ctype;
			using cderef_ctype_ptr		= typename Model::cderef_ctype_ptr;
			using cderef_ctype_cptr		= typename Model::cderef_ctype_cptr;
			using cderef_ctype_ref		= typename Model::cderef_ctype_ref;

			using deref_type		= typename Model::deref_type;
			using deref_type_ptr		= typename Model::deref_type_ptr;
			using deref_type_cptr		= typename Model::deref_type_cptr;
			using deref_type_ref		= typename Model::deref_type_ref;

			using deref_ctype		= typename Model::deref_ctype;
			using deref_ctype_ptr		= typename Model::deref_ctype_ptr;
			using deref_ctype_cptr		= typename Model::deref_ctype_cptr;
			using deref_ctype_ref		= typename Model::deref_ctype_ref;

			using size_type			= typename Model::size_type;
			using size_ctype		= typename Model::size_ctype;

		protected:

			model_type_ptr model;

		public:

			nik_ce array_facade() : model{} { }
			nik_ce array_facade(model_type_cptr m) : model{m} { }

			template<typename CMethod>
			nik_ce auto cpivot() const -> CMethod { return array_cfacade<Model>{model}; }

			template<typename Method>
			nik_ce auto pivot() -> Method { return array_facade{model}; }

			// initial:

				nik_ce citer_type cbegin() const { return model->cbegin(); }
				nik_ce  iter_type  begin()       { return model-> begin(); }

			// terminal:

				nik_ce size_type size() const { return model->size(); }
				nik_ce void set_size(size_ctype n) { model->set_size(n); }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// array:

/***********************************************************************************************************************/

// immutable:

	template<typename Type, typename SizeType, template<typename> typename CMethodType = array_cmethod>
	class carray : public CMethodType<array_cmodel<Type, SizeType>>
	{
		public:

			using model			= array_cmodel<Type, SizeType>;
			using base			= CMethodType<model>;
			using cfacade_type		= array_cfacade<model>;
			using cmethod_type		= CMethodType<cfacade_type>;

			using type			= typename base::type;
			using type_ptr			= typename base::type_ptr;
			using type_cptr			= typename base::type_cptr;
			using type_ref			= typename base::type_ref;

			using ctype			= typename base::ctype;
			using ctype_ptr			= typename base::ctype_ptr;
			using ctype_cptr		= typename base::ctype_cptr;
			using ctype_ref			= typename base::ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce carray() : base{} { }

			nik_ce carray(ctype_cptr i, size_ctype t) : base{} { base::assign(i, t); }

			template<auto N>
			nik_ce carray(const Type (&a)[N]) : carray{a, N} { }

			// equip:

				template<typename CMethod>
				nik_ce auto cequip() const -> CMethod
					{ return cfacade_type{static_cast<base*>(this)}; }
	};

/***********************************************************************************************************************/

// string (literal):

	template<typename Type, typename SizeType>
	struct cstring : public carray<Type, SizeType>
	{
		using base			= carray<Type, SizeType>;

		using type			= typename base::type;
		using type_ptr			= typename base::type_ptr;
		using type_cptr			= typename base::type_cptr;
		using type_ref			= typename base::type_ref;

		using ctype			= typename base::ctype;
		using ctype_ptr			= typename base::ctype_ptr;
		using ctype_cptr		= typename base::ctype_cptr;
		using ctype_ref			= typename base::ctype_ref;

		using size_type			= typename base::size_type;
		using size_ctype		= typename base::size_ctype;

		using cfacade_type		= array_cfacade<cstring>;
		using cmethod_type		= array_cmethod<cfacade_type>;

		nik_ce cstring() : base{} { }

		template<auto N>
		nik_ce cstring(const Type (&s)[N]) : base{s, N-1} { }
	};

/***********************************************************************************************************************/

// mutable:

	template
	<
		typename Type, typename SizeType, SizeType Size,
		template<typename> typename CMethodType = array_cmethod,
		template<typename> typename  MethodType = array_method
	>
	class array : public MethodType<array_model<Type, SizeType, Size>>
	{
		public:

			using model			= array_model<Type, SizeType, Size>;
			using base			= MethodType<model>;
			using cfacade_type		= array_cfacade<model>;
			using facade_type		= array_facade<model>;
			using cmethod_type		= CMethodType<cfacade_type>;
			using method_type		= MethodType<facade_type>;

			using type			= typename base::type;
			using type_ptr			= typename base::type_ptr;
			using type_cptr			= typename base::type_cptr;
			using type_ref			= typename base::type_ref;

			using ctype			= typename base::ctype;
			using ctype_ptr			= typename base::ctype_ptr;
			using ctype_cptr		= typename base::ctype_cptr;
			using ctype_ref			= typename base::ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

		public:

			nik_ce array() : base{} { }

			template<typename T, auto N>
			nik_ce array(const T (&a)[N]) : base{a} { }

			// equip:

				template<typename CMethod>
				nik_ce auto cequip() const -> CMethod
					{ return cfacade_type{static_cast<base*>(this)}; }

				template<typename Method>
				nik_ce auto equip() -> Method
					{ return facade_type{static_cast<base*>(this)}; }
	};

/***********************************************************************************************************************/

// unique:

	template<typename Type, typename SizeType, SizeType Size>
	class unique_array : public array<Type, SizeType, Size, unique_cmethod, unique_method>
	{
		public:

			using base			= array<Type, SizeType, Size, unique_cmethod, unique_method>;

			using type			= typename base::type;
			using type_ptr			= typename base::type_ptr;
			using type_cptr			= typename base::type_cptr;
			using type_ref			= typename base::type_ref;

			using ctype			= typename base::ctype;
			using ctype_ptr			= typename base::ctype_ptr;
			using ctype_cptr		= typename base::ctype_cptr;
			using ctype_ref			= typename base::ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using cfacade_type		= typename base::cfacade_type;
			using cmethod_type		= typename base::cmethod_type;

			using facade_type		= typename base::facade_type;
			using method_type		= typename base::method_type;

		public:

			nik_ce unique_array() : base{} { }

			template<typename T, auto N>
			nik_ce unique_array(const T (&a)[N]) : base{a} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// table:

	template<auto RowSize, auto ColSize>
	struct curry_table_cmethod { template<typename Model> using type = table_cmethod<Model, RowSize, ColSize>; };

	template<auto RowSize, auto ColSize>
	struct curry_table_method { template<typename Model> using type = table_method<Model, RowSize, ColSize>; };

/***********************************************************************************************************************/

// immutable:

	template<typename Type, typename SizeType, SizeType RowSize, SizeType ColSize>
	class ctable : public carray<Type, SizeType, curry_table_cmethod<RowSize, ColSize>::template type>
	{
		public:

			using curry			= curry_table_cmethod<RowSize, ColSize>;
			using base			= carray<Type, SizeType, curry::template type>;

			using type			= typename base::type;
			using type_ptr			= typename base::type_ptr;
			using type_cptr			= typename base::type_cptr;
			using type_ref			= typename base::type_ref;

			using ctype			= typename base::ctype;
			using ctype_ptr			= typename base::ctype_ptr;
			using ctype_cptr		= typename base::ctype_cptr;
			using ctype_ref			= typename base::ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using cfacade_type		= typename base::cfacade_type;
			using cmethod_type		= typename base::cmethod_type;

		public:

			nik_ce ctable() : base{} { }

			template<typename T, auto N>
			nik_ce ctable(const T (&a)[N]) : base{a} { }
	};

/***********************************************************************************************************************/

// mutable:

	template<typename Type, typename SizeType, SizeType RowSize, SizeType ColSize>
	class table	: public array
			<
				Type, SizeType, RowSize * ColSize,
				curry_table_cmethod<RowSize, ColSize>::template type,
				curry_table_method<RowSize, ColSize>::template type
			>
	{
		public:

			using ccurry			= curry_table_cmethod<RowSize, ColSize>;
			using curry			= curry_table_method<RowSize, ColSize>;
			using base			= array
							<
								Type, SizeType, RowSize * ColSize,
								ccurry::template type,
								curry::template type
							>;

			using type			= typename base::type;
			using type_ptr			= typename base::type_ptr;
			using type_cptr			= typename base::type_cptr;
			using type_ref			= typename base::type_ref;

			using ctype			= typename base::ctype;
			using ctype_ptr			= typename base::ctype_ptr;
			using ctype_cptr		= typename base::ctype_cptr;
			using ctype_ref			= typename base::ctype_ref;

			using size_type			= typename base::size_type;
			using size_ctype		= typename base::size_ctype;

			using cfacade_type		= typename base::cfacade_type;
			using cmethod_type		= typename base::cmethod_type;

			using facade_type		= typename base::facade_type;
			using method_type		= typename base::method_type;

		public:

			nik_ce table() : base{} { }

			template<typename T, auto N>
			nik_ce table(const T (&a)[N]) : base{a} { }
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

