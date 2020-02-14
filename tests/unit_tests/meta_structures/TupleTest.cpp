#include "common_utils/meta_structures/Tuple.h"

#include <gtest/gtest.h>

using namespace common_utils;

namespace meta_structures_test {

	//######################################################################################################
	// Tuple test.

	TEST(TupleTest, ArrayGenerator) {
		using TList = TYPELIST_3(int, double, char);
		EXPECT_EQ(typeid(ArrayGenerator<TList, Holder>::Element::ElementType), typeid(Holder<int>));
		EXPECT_EQ(typeid(ArrayGenerator<TList, Holder>::Next::Element::ElementType), typeid(Holder<double>));
		EXPECT_EQ(typeid(ArrayGenerator<TList, Holder>::Next::Next::Element::ElementType), typeid(Holder<char>));

		// If we have elements of the same type, the generated array should stack them together in memory.
		ArrayGenerator<TYPELIST_3(double, double, double), Holder> arrayObj1;
		EXPECT_EQ(sizeof(arrayObj1), sizeof(double) * 3);

		// Elements of different type are padded such that they start at 8-byte mark.
		ArrayGenerator<TYPELIST_3(int, double, char), Holder> arrayObj2;
		EXPECT_EQ(sizeof(arrayObj2), 3 * 8);
	}

	TEST(TupleTest, ElementAt) {
		ArrayGenerator<TYPELIST_3(int, double, char), Holder> arrayObj;
		
		Holder<int>& e0 = ElementAt<0>(arrayObj);
		e0.m_value = 3;

		Holder<double>& e1 = ElementAt<1>(arrayObj);
		e1.m_value = 2.0;

		Holder<char>& e2 = ElementAt<2>(arrayObj);
		e2.m_value = 5;

		EXPECT_EQ(ElementAt<0>(arrayObj).m_value, 3);
		EXPECT_FLOAT_EQ(ElementAt<1>(arrayObj).m_value, 2.0);
		EXPECT_EQ(ElementAt<2>(arrayObj).m_value, 5);
	}

	TEST(TupleTest, IndexedTypeList) {
		using TList = TYPELIST_4(int, double, double, char);
		using IndexedTList = IndexedTypeList<TList>::type;

		EXPECT_EQ(TypeListLength<IndexedTList>::value, 4);
		EXPECT_EQ(typeid(TypeAt<0, IndexedTList>::type), typeid(IndexedType<0, int>));
		EXPECT_EQ(typeid(TypeAt<1, IndexedTList>::type), typeid(IndexedType<1, double>));
		EXPECT_EQ(typeid(TypeAt<2, IndexedTList>::type), typeid(IndexedType<2, double>));
		EXPECT_EQ(typeid(TypeAt<3, IndexedTList>::type), typeid(IndexedType<3, char>));
	}

	TEST(TupleTest, NonConstIndexing) {
		Tuple<TYPELIST_3(int, double, char)> tuple;
		
		tuple[I<0>()] = 3;
		tuple[I<1>()] = 2.0;
		tuple[I<2>()] = 5;

		EXPECT_EQ(tuple[I<0>()], 3);
		EXPECT_FLOAT_EQ(tuple[I<1>()], 2.0);
		EXPECT_EQ(tuple[I<2>()], 5);
	}

	TEST(TupleTest, ConstIndexing) {
		const Tuple<TYPELIST_3(int, double, char)> tuple;

		EXPECT_EQ(typeid(tuple[I<0>()]), typeid(int));
		EXPECT_EQ(typeid(tuple[I<1>()]), typeid(double));
		EXPECT_EQ(typeid(tuple[I<2>()]), typeid(char));
	}

	TEST(TupleTest, RuntimeSize) {
		Tuple<TYPELIST_3(int, double, char)> tuple;
		EXPECT_EQ(tuple.size(), 3);
	}

	TEST(TupleTest, CompileSize) {
		int size{ TupleSize<Tuple<TYPELIST_3(int, double, char)>>::value };
		EXPECT_EQ(size, 3);
	}

	TEST(TupleTest, MakeTuple) {
		const int i    = 2;
		const double d = 3.0;
		const float f  = 4.f;

		auto t0 = makeTuple();
		EXPECT_EQ(t0.size(), 0);

		auto t1 = makeTuple(i);
		EXPECT_EQ(t1.size(), 1);
		EXPECT_EQ(t1[I<0>()], i);

		auto t2 = makeTuple(i, d, f);
		EXPECT_EQ(t2.size(), 3);
		EXPECT_EQ(t2[I<0>()], i);
		EXPECT_FLOAT_EQ(t2[I<1>()], d);
		EXPECT_FLOAT_EQ(t2[I<2>()], f);

		auto t3 = makeTuple(i, i, d, f);
		EXPECT_EQ(t3.size(), 4);
		EXPECT_EQ(t3[I<0>()], i);
		EXPECT_EQ(t3[I<1>()], i);
		EXPECT_FLOAT_EQ(t3[I<2>()], d);
		EXPECT_FLOAT_EQ(t3[I<3>()], f);
	}

} // namespace meta_structures_test