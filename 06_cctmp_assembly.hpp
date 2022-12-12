/************************************************************************************************************************
**
** Copyright 2022 Daniel Nikpayuk, Inuit Nunangat, The Inuit Nation
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

// assembly:

namespace cctmp {

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lookup:

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// binding:

	template<typename CharType, auto Size, typename ValueType>
	struct binding
	{
		using char_type			= CharType;
		using string_type		= char_type const *;
		using size_type			= decltype(Size);

		nik_ces size_type size		= Size;
		nik_ces auto value		= U_restore_T<ValueType>;
		using value_type		= decltype(value);

		string_type string;

		nik_ce binding(const CharType (&s)[Size], ValueType) : string{s} { }
	};

/***********************************************************************************************************************/

// table:

	template<typename CharType, typename... Bindings>
	struct table
	{
		using char_type			= T_restore_T<CharType>;
		using cchar_type		= char_type const;
		using string_type		= char_type const*;
		using cstring_type		= string_type const;

		nik_ces auto size		= sizeof...(Bindings);
		using size_type			= decltype(size);

		nik_ces auto sizes		= array<size_type, Bindings::size...>;
		nik_ces auto values		= U_pack_Vs<Bindings::value...>;

		cstring_type string[size];

		nik_ce table(CharType, Bindings... bs) : string{bs.string...} { }
	};

/***********************************************************************************************************************/

// function:

//	template<auto Size>
//	nik_ce bool equals_charset(gstring_type b, gstring_type e, gcchar_type (&charset)[Size])
//	{
//		bool match = ((e-b) == Size);

//		for (gstring_type i = charset; match && i != charset + Size; ++b, ++i)
//			match = (*b == *i);

//		return match;
//	}

	template<typename SizeType, typename Type1, typename Type2>
	nik_ce auto ptr_diff_equal(const Type1 *b1, const Type1 *e1, const Type2 *b2, const Type2 *e2)
	{
		using size_type = SizeType;

		const size_type size1 = e1 - b1;
		const size_type size2 = e2 - b2;

		bool equal = (size1 == size2);

		while (equal && b1 != e1) equal = (*(b1++) == *(b2++));

		return equal;
	}

	template<auto f, typename StringType>
	nik_ce auto lookup_function(StringType str_begin, StringType str_end)
	{
		nik_ce auto table		= f();

		using table_type		= decltype(table);
		using size_type			= typename table_type::size_type;
		using string_type		= typename table_type::string_type;
		using cstring_type		= typename table_type::cstring_type;

		cstring_type *key		= table.string;
		cstring_type *key_end		= key + table.size;

		size_type *size			= table.sizes;

		while (key != key_end)
		{
			string_type b		= *key;
			string_type e		= b + *(size++);

			if (ptr_diff_equal<size_type>(b, e, str_begin, str_end)) break;

			++key;
		}

		return key - table.string;
	}

	template<auto f>
	nik_ce auto make_lookup_function()
	{
		using table_type	= T_out_type<f>;
		using string_type	= typename table_type::string_type;

		nik_ce auto values	= table_type::values;
		nik_ce auto lookup_f	= lookup_function<f, string_type>;

		return eval<_cons_, H_id, values, lookup_f>;
	}

	template<auto f>
	nik_ce auto make_environment = make_lookup_function<f>();

/***********************************************************************************************************************/

// default:

	nik_ce auto default_lookup()
	{
		return table
		(
		 	U_char,

			binding ( "is_zero"   , _is_zero_      ) ,
			binding ( "multiply"  , _multiply_     ) ,
			binding ( "decrement" , _decrement_<1> )
		);
	};

	nik_ce auto default_environment = make_environment<default_lookup>;

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

// assembly:

	template<gkey_type, auto...> struct T_assembly;

/***********************************************************************************************************************/

// names:

	struct Name
	{
		enum : gkey_type
		{
			generic , sift    , replace ,
			go_to   , test    , branch  ,
			unary   , binary  , re_turn ,

			dimension
		};
	};

/***********************************************************************************************************************/

// instructions:

	struct Instr
	{
		enum : gkey_type
		{
			size = 0  , name      , pos ,
			jmp = pos , op  = pos ,
			_0        , _1        , _2  ,

			dimension
		};
	};

/***********************************************************************************************************************/

// dispatch:

	struct AssemblyDisp : public AbstractDisp
	{
		nik_ces auto instr(contr_type c, gcindex_type i)
			{ return c[i]; }

		nik_ces gkey_type next_name(contr_type c, gcindex_type i)
			{ return c[i+1][Instr::name]; }

		nik_ces gindex_type next_index(contr_type, gcindex_type i)
			{ return i + 1; }
	};

/***********************************************************************************************************************/

// start:

	struct T_start
	{
		nik_ces auto i = AD::initial_index;

		template<auto l, auto c, typename S, typename... Ts>
		nik_ces auto result(Ts... vs) -> S
		{
			return T_assembly<next_name(c, i)>::template result<l, c, next_index(c, i), S, Ts...>(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// go to:

/***********************************************************************************************************************/

	template<auto... filler>
	struct T_assembly<Name::go_to, filler...>
	{
		template<auto l, auto c, auto i, typename S, typename... Ts>
		nik_ces auto result(Ts... vs) -> S
		{
			nik_ce auto ins = instr(c, i);
			nik_ce auto ni  = ins[Instr::jmp];

			return T_assembly<next_name(c, ni)>::template result<l, c, next_index(c, ni), S, Ts...>(vs...);
		}
	};

	template<auto... filler>
	struct T_assembly<Name::branch, filler...>
	{
		template<auto l, auto c, auto i, typename S, typename BoolType, typename... Ts>
		nik_ces auto result(BoolType v, Ts... vs) -> S
		{
			nik_ce auto ins = instr(c, i);
			nik_ce auto ni  = ins[Instr::jmp];

			if (v) return T_assembly<next_name(c, ni)>::template result<l, c, next_index(c, ni), S, Ts...>(vs...);
			else   return T_assembly<next_name(c,  i)>::template result<l, c, next_index(c,  i), S, Ts...>(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// test:

/***********************************************************************************************************************/

	template<auto... filler>
	struct T_assembly<Name::test, filler...>
	{
		template<auto l, auto c, auto i, typename S, typename... Ts>
		nik_ces auto result(Ts... vs) -> S
		{
			nik_ce auto ins  = instr(c, i);
			nik_ce auto _op  = ins[Instr::op];
			nik_ce auto _0   = ins[Instr::_0];
			nik_ce auto test = unpack_<l, _at_, _op>;

			auto arg = at<_0>(vs...);
			auto val = T_store_U<test>::result(arg);

			return T_assembly<next_name(c, i)>::template result
			<
				l, c, next_index(c, i), S, decltype(val), Ts...

			>(val, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// apply:

	// helper:

		template<auto, auto> struct T_assembly_apply;

		template<auto f, auto... Is, nik_vp(p)(T_pack_Vs<Is...>*)>
		struct T_assembly_apply<f, p>
		{
			template<typename... Ts>
			nik_ces auto result(Ts... vs) { return T_store_U<f>::result(at<Is>(vs...)...); }
		};

/***********************************************************************************************************************/

	template<auto... filler>
	struct T_assembly<Name::apply, filler...>
	{
		template<auto l, auto c, auto i, typename S, typename... Ts>
		nik_ces auto result(Ts... vs) -> S
		{
			nik_ce auto ins = instr(c, i);
			nik_ce auto _op = ins[Instr::op];
			nik_ce auto _0  = ins[Instr::_0];
			nik_ce auto _p  = ins[Instr::_1];
			nik_ce auto f   = unpack_<l, _at_, _op>;
			nik_ce auto p   = unpack_<l, _at_, _p>;

			auto val = T_assembly_apply<f, p>::template result<Ts...>(vs...);

			return T_assembly<Name::replace, _0>::template result<l, c, i, S, decltype(val), Ts...>(val, vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// resume:

/***********************************************************************************************************************/


/***********************************************************************************************************************/
/***********************************************************************************************************************/

// return:

/***********************************************************************************************************************/

	template<auto... filler>
	struct T_assembly<Name::re_turn, filler...>
	{
		template<auto l, auto c, auto i, typename S, typename... Ts>
		nik_ces auto result(Ts... vs) -> S
		{
			nik_ce auto ins	= instr(c, i);
			nik_ce auto n	= ins[Instr::pos];

			return at<n, Ts...>(vs...);
		}
	};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// case study:

/***********************************************************************************************************************/

// source:

	template
	<
		auto       n = 0 , auto        p = 1 ,
		auto is_zero = 0 , auto multiply = 1 , auto dec = 2 ,
		auto    loop = 0 , auto     done = 5
	>
	nik_ce auto pair_factorial_contr = controller
	<
	// loop:
		instruction < Name::test    , is_zero      , n     >,
		instruction < Name::branch  , done                 >,
		instruction < Name::binary  , multiply , p , n , p >,
		instruction < Name::unary   , dec      , n , n     >,
		instruction < Name::go_to   , loop                 >,
	// done:
		instruction < Name::re_turn , p                    >
	>;

/***********************************************************************************************************************/

// factorial:

	template<typename T>
	nik_ce auto factorial(T n)
	{
		return T_start::template result
		<
			U_pack_Vs
			<
				_is_equal_<0>,
				_multiply_,
				_increment_<-1>
			>,

			pair_factorial_contr<>, T

		>(n, 1, 0, 0);
	}

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // namespace cctmp

