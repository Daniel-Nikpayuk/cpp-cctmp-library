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

#include<cstdio>
#include<cstdlib>
#include<new>

/***********************************************************************************************************************/

#include"define_macros.hpp"

#include"include/00_kernel.hpp"
#include"include/01_machine.hpp"
#include"include/02_method.hpp"

#include"undef_macros.hpp"

#include"testing/printer.hpp"
#include"testing/type_system.hpp"
//#include"testing/unit_test_type_system.hpp"
//#include"testing/unit_test_continuant_machine.hpp"
//#include"testing/unit_test_virtual_machine.hpp"

/***********************************************************************************************************************/
/***********************************************************************************************************************/

	using namespace cctmp;

/***********************************************************************************************************************/

// main at:

	template<typename T>
	auto main_at(T n, int argc, char *argv[], T def = 0) -> T
	{
		auto pos = n + 1;

		if (pos < argc) return atoi(argv[pos]);
		else            return def;
	}

/***********************************************************************************************************************/

// proof oriented programming:

	// tuple:

		template<typename SizeType>
		struct concord_tuple
		{
			using size_type             = typename alias<SizeType>::type;
			using size_ctype            = typename alias<SizeType>::ctype;
			using concord_type          = resolve_concord_type<size_type, size_type, concord_size_pack_0>;
			using icon_type             = icon<size_type>;
			using sign_type             = sign<size_type>;

			using empty_cmethod_type    = resolve_cmethod < concord_type , empty_cmethod    >;
			using empty_method_type     = resolve_method  < concord_type , empty_method     >;

			using ring_cmethod_type     = resolve_cmethod < concord_type , ring_cmethod     >;
			using ring_method_type      = resolve_method  < concord_type , ring_method      >;

			using list_cmethod_type     = resolve_cmethod < concord_type , list_cmethod     >;
			using list_method_type      = resolve_method  < concord_type , list_method      >;

			using function_cmethod_type = resolve_cmethod < concord_type , function_cmethod >;
			using function_method_type  = resolve_method  < concord_type , function_method  >;

			// square:

				constexpr static size_type square_contr[32] =
				{
					CI::program         , 6 ,            0 , 2 ,
					CI::argument_specs  , 0 ,            0 , 1 ,
					CI::function        , 6 , CP::to_stack , 1 ,
					CI::argument        , 1 , CP::to_stack , 1 ,
					CI::argument        , 1 , CP::to_stack , 1 ,
					CI::apply           , 2 , CP::to_carry , 0 ,
				// multiply:
					CI::program         , 2 ,            1 , 1 ,
					CI::multiply        , 0 , CP::to_carry , 0
				};

			concord_type value;

			icon_type empty_icon;
			icon_type ring8_icon;
			icon_type  list_icon;
			icon_type unary_icon;

			sign_type empty_sign;
			sign_type ring8_sign;
			sign_type list_sign;
			sign_type square_sign;

			constexpr concord_tuple()
			{
				auto empty_method = value.template equip<empty_method_type>();
				auto ring_method  = value.template equip<ring_method_type>();
				auto list_method  = value.template equip<list_method_type>();
				auto func_method  = value.template equip<function_method_type>();

				empty_icon        = empty_method.declare_type();
				ring8_icon        = ring_method.declare_type(8);
				 list_icon        = list_method.declare_type(ring8_icon);
				unary_icon        = func_method.declare_type({ ring8_icon, ring8_icon });

				empty_sign        = empty_method.define_value(empty_icon);
				list_sign         = list_method.define_value(list_icon, empty_sign);

				square_sign       = func_method.define_value(unary_icon, square_contr);
			}

			template<auto N>
			constexpr concord_tuple(const size_type (&s)[N]) : concord_tuple()
			{
				auto ring_method = value.template equip<ring_method_type>();
				auto list_method = value.template equip<list_method_type>();

				size_type sum = 0;

				for (size_type k = 0; k != N - 1; ++k)
				{
					ring8_sign = ring_method.define_value(ring8_icon, sum);
					list_sign  = list_method.define_value(list_icon, ring8_sign, list_sign);
					sum       += s[k];
				}

				ring8_sign = ring_method.define_value(ring8_icon, s[N-1]);
				list_sign  = list_method.define_value(list_icon, ring8_sign, list_sign);
			}

			constexpr auto function_cmethod() const
				{ return value.template cequip<function_cmethod_type>(); }

			constexpr auto cat(size_ctype n) const
			{
				auto ring_cmethod = value.template cequip<ring_cmethod_type>();
				auto list_cmethod = value.template cequip<list_cmethod_type>();

				size_ctype length = ring_cmethod.cvalue(list_cmethod.car_sign(list_sign));

				return ring_cmethod.cvalue(list_cmethod.car_sign(list_sign, length - n));
			}
		};

	// static tuple:

		template<typename SizeType, typename... Ts>
		struct static_concord_tuple
		{
			constexpr static auto length		= sizeof...(Ts);
			constexpr static auto value		= concord_tuple<SizeType>{{sizeof(Ts)..., length}};
			using type				= decltype(value);

			using concord_type			= typename type::concord_type;
			using size_type				= typename concord_type::size_type;
			using size_ctype			= typename concord_type::size_ctype;

			constexpr static auto & function	= value.square_sign;

			constexpr static auto make_offset()
			{
				using array_type = array<size_type, size_type, sizeof...(Ts)>;

				array_type array;
				for (size_type k = 0; k != array.length(); ++k)
					{ array.push(value.cat(k)); }

				return array;
			}
		};

/***********************************************************************************************************************/

		template<typename... Ts>
		class tuple
		{
			private:

				using size_type = unsigned long;
				using meta_info = static_concord_tuple<size_type, Ts...>;

				constexpr static auto length = size_type{(... + sizeof(Ts))};
				constexpr static auto offset = meta_info::make_offset();

			protected:

				unsigned char memory[length];

				template<auto... Is>
				void assign_memory(void(*)(T_pack_Vs<Is...>*), Ts const &... vs)
					{ (..., new (memory + offset[Is]) Ts(vs)); }

			public:

				tuple() { }

				tuple(Ts const &... vs) { assign_memory(segment_<sizeof...(Ts)>, vs...); }

				template<size_type n>
				auto at() { return *(new (memory + offset[n]) type_at<n, Ts...>); }

				template<size_type n>
				auto at_squared()
				{
					constexpr auto contr = U_store_T<meta_info>;

					return T_metapile_apply<contr, U_null_Vs, U_null_Vs>::result(at<n>());
				}
		};

/***********************************************************************************************************************/

	int main(int argc, char *argv[])
	{
		using tuple_type = tuple<int, float, char>;

		tuple_type tuple{main_at(0, argc, argv), 2.718, 'e'};

		printf("%d\n", tuple.at<0>());
		printf("%f\n", tuple.at<1>());
		printf("%c\n", tuple.at<2>());

		printf("\n");

		printf("%d\n", tuple.at_squared<0>());
		printf("%f\n", tuple.at_squared<1>());
		printf("%c\n", tuple.at_squared<2>());

	//	concord_empty_test      ();
	//	concord_ring_test       ();
	//	concord_utf8_char_test  ();
	//	concord_tuple_test      ();
	//	concord_cotuple_test    ();
	//	concord_function_test   ();
	//	concord_list_test       ();
	//	concord_space_test      ();

	//	continuant_machine_test ();
	//	virtual_machine_test    ();

		return 0;
	}

