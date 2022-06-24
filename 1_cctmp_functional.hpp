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

// functional:

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

namespace cctmp_functional
{
	using namespace cctmp;

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// basis:

/***********************************************************************************************************************/

// variable:

/*
	struct Variable
	{
		nik_ces auto m		= MT::id;
		nik_ces auto i		= MachineDispatch::initial_index;
		nik_ces auto ctn	= MI::value;

		template<auto d, auto n, auto rtn, auto h0, auto c = controller<variable<rtn, ctn>>>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i) NIK_END_MACHINE(h0, U_pack_Vs<n>, U_null_Vs);
	};
*/

// function:

/*
	struct Function
	{
		nik_ces auto m		= MT::id;
		nik_ces auto i		= MachineDispatch::initial_index;
		nik_ces auto ctn	= MI::value;

		template<auto d, auto n, auto rtn, auto h0, auto c = controller<function<rtn, ctn>>>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i) NIK_END_MACHINE(h0, U_pack_Vs<n>, U_null_Vs);
	};
*/

// compel:

/*
	struct Compel
	{
		nik_ces auto m		= MT::id;
		nik_ces auto i		= MachineDispatch::initial_index;
		nik_ces auto ctn	= MI::value;

		template<auto d, auto h0, auto dec = _three, auto c = controller<compel<ctn, dec>>>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i) NIK_END_MACHINE(h0, U_null_Vs, U_null_Vs);
	};
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// block:

/***********************************************************************************************************************/

// at:

/*
	struct At
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = Variable::template result<d, n, BN::sifter, p>;
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	nik_ce auto at = At::template result<d, n, p>;
*/

// left:

/*
	struct Left
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = Function::template result<d, n, BN::left, p>;
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	nik_ce auto left = Left::template result<d, n, p>;
*/

// right:

/*
	struct Right
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = Variable::template result<d, n, BN::right, p>;
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	nik_ce auto right = Right::template result<d, n, p>;
*/

// cut:

/*
	struct Cut
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = Function::template result<d, n, BN::filter, p>;
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	nik_ce auto cut = Cut::template result<d, n, p>;
*/

// split:

/*
	struct Split
	{
		template<auto d, auto n, auto p>
		nik_ces auto result = Function::template result<d, n, BN::split, p>;
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	nik_ce auto split = Split::template result<d, n, p>;
*/

// segment:

/*
	struct T_Segment
	{
		template<auto d, auto n, auto m>
		nik_ces auto result = NIK_BEGIN_BLOCK(9, segment, d, n), m NIK_END_BLOCK;
	};

	nik_ce auto U_Segment = U_store_T<T_Segment>;

	struct Segment
	{
		template<auto d, auto n, auto m>
		nik_ces auto result = Compel::template result<d, U_pack_Vs<U_Segment, n, m>>;
	};

	template<auto n, auto m = index_type{0}, auto d = MachineDispatch::initial_depth>
	nik_ce auto segment = Segment::template result<d, n, m>;
*/

// fold:

/*
	struct T_Fold
	{
		template<auto d, auto op, auto V, auto l>
		nik_ces auto result = V;
	};

	template<auto d, auto op, auto V, auto... Vs, nik_vp(l)(auto_pack<Vs...>*)>
	nik_ce auto T_Fold::result<d, op, V, l> = NIK_FOLD_BLOCK(d, sizeof...(Vs), op, V, Vs);

	nik_ce auto U_Fold = U_store_T<T_Fold>;

	struct Fold
	{
		template<auto d, auto op, auto V, auto l>
		nik_ces auto result = Compel::template result<d, U_pack_Vs<U_Fold, op, V, l>>;
	};

	template<auto op, auto V, auto l, auto d = MachineDispatch::initial_depth>
	nik_ce auto fold = Fold::template result<d, op, V, l>;
*/

// cascade:

/*
	struct T_Cascade
	{
		template<auto d, auto op, auto V, auto l>
		nik_ces auto result = V;
	};

	template<auto d, auto op, auto V, auto... Vs, nik_vp(l)(auto_pack<Vs...>*)>
	nik_ce auto T_Cascade::result<d, op, V, l> = NIK_CASCADE_BLOCK(d, sizeof...(Vs), op, V, Vs);

	nik_ce auto U_Cascade = U_store_T<T_Cascade>;

	struct Cascade
	{
		template<auto d, auto op, auto V, auto l>
		nik_ces auto result = Compel::template result<d, U_pack_Vs<U_Cascade, op, V, l>>;
	};

	template<auto op, auto V, auto l, auto d = MachineDispatch::initial_depth>
	nik_ce auto cascade = Cascade::template result<d, op, V, l>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// mutators:

/***********************************************************************************************************************/

// erase:

/*
	struct Erase
	{
		nik_ces auto m = MT::id;
		nik_ces auto i = MachineDispatch::initial_index;
		nik_ces auto c = controller
		<
			function < BN::filter >,
			lift     <            >,
			unite    <     _value >
		>;

		template<auto d, auto n, auto p>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i) NIK_END_MACHINE(p, U_pack_Vs<n>, U_null_Vs);
	};

	template<auto n, auto p, auto d = MachineDispatch::initial_depth>
	nik_ce auto erase = Erase::template result<d, n, p>;
*/

// insert:

/*
	struct Insert
	{
		nik_ces auto m = MT::id;
		nik_ces auto i = MachineDispatch::initial_index;
		nik_ces auto c = controller
		<
			function <         BN::split >,
			lift     <                   >,
			copy     < _zero , _register >,
			unite    <         _value    >
		>;

		template<auto d, auto v, auto n, auto p>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i), v NIK_END_MACHINE(p, U_pack_Vs<n>, U_null_Vs);
	};

	nik_ce auto U_Insert = U_store_T<Insert>;

	template<auto v, auto n, auto p, auto d = MachineDispatch::initial_depth>
	nik_ce auto insert = Insert::template result<d, v, n, p>;
*/

// replace:

/*
	struct Replace
	{
		nik_ces auto m = MT::id;
		nik_ces auto i = MachineDispatch::initial_index;
		nik_ces auto c = controller
		<
			function <         BN::filter >,
			lift     <                    >,
			copy     < _zero , _register  >,
			unite    <         _value     >
		>;

		template<auto d, auto v, auto n, auto p>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i), v NIK_END_MACHINE(p, U_pack_Vs<n>, U_null_Vs);
	};

	template<auto v, auto n, auto p, auto d = MachineDispatch::initial_depth>
	nik_ce auto replace = Replace::template result<d, v, n, p>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// sort:

/***********************************************************************************************************************/

// insert:

/*
	template<auto cmp = less_than_op<>>
	struct T_InsertSort
	{
		nik_ces auto m = MT::id;
		nik_ces auto i = MachineDispatch::initial_index;
		nik_ces auto c = controller
		<
			find     <                   >,
			write    < _zero , _argument >,
			function <         BN::split >,
			lift     <                   >,
			copy     < _zero , _register >,
			unite    <         _value    >
		>;

		template<auto d, auto p, auto v>
		nik_ces auto result = NIK_BEGIN_MACHINE(d, m, c, i), v
					NIK_END_MACHINE(U_pack_Vs<cmp, p, v>, U_null_Vs, U_null_Vs, p);
	};

	template<auto cmp = less_than_op<>>
	nik_ce auto U_InsertSort = U_store_T<T_InsertSort<cmp>>;

	template<auto list, auto insert, auto cmp = less_than_op<>, auto d = MachineDispatch::initial_depth>
	nik_ce auto insert_sort = T_InsertSort<cmp>::template result<d, list, insert>;
*/

// (sort):

/*
	template
	<
		auto l,
		auto cmp	= less_than_op<>,
		auto d		= MachineDispatch::initial_depth
	>
	nik_ce auto sort_v2 = Cascade::template result
	<
		d,
		U_InsertSort<cmp>,
		U_null_Vs,
		l
	>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/

// lookup:

/***********************************************************************************************************************/

// match:

/*
	struct T_LookupMatch
	{
		template<auto v, auto p>
		nik_ces auto match()
		{
			nik_ce auto pos	= Overload::template result<Overload::find, is_value_op<>, p, v>;
			nik_ce auto size	= Overload::template result<Overload::length, p>;

			return pair(bool{pos < size}, pos);
		}

		template<auto v, auto p>
		nik_ces auto result = match<v, p>();
	};

	nik_ce auto U_LookupMatch = U_store_T<T_LookupMatch>;
*/

/***********************************************************************************************************************/

// (lookup):

/*
	struct T_Lookup
	{
		template<auto d, auto p, auto v>
		nik_ces auto result = Compel::template result<d, U_pack_Vs<U_LookupMatch, v, p>>;
	};

	nik_ce auto U_Lookup = U_store_T<T_Lookup>;

	template<auto list, auto val, auto d = MachineDispatch::initial_depth>
	nik_ce auto lookup = T_Lookup::template result<d, list, val>;
*/

/***********************************************************************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

} // cctmp_functional

