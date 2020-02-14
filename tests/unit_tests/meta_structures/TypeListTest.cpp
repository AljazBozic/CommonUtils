#include "common_utils/meta_structures/TypeList.h"

#include <gtest/gtest.h>

using namespace common_utils;

namespace meta_structures_test {

	//######################################################################################################
	// TypeList test.

	TEST(TypeListTest, Initialization) {
		using TList = TYPELIST_3(int, double, char);

		EXPECT_EQ(typeid(TList::Head), typeid(int));
		EXPECT_NE(typeid(TList::Head), typeid(double));

		EXPECT_EQ(typeid(TList::Tail), typeid(TypeList<double, TypeList<char, NullType>>));
		EXPECT_NE(typeid(TList::Tail), typeid(TypeList<char, TypeList<double, NullType>>));
	}

	TEST(TypeListTest, CreateTypeList) {
		EXPECT_EQ(typeid(TL<int, double, char>::type), typeid(TYPELIST_3(int, double, char)));
		EXPECT_EQ(typeid(TL<int, int, char>::type), typeid(TYPELIST_3(int, int, char)));
		EXPECT_EQ(typeid(TL<>::type), typeid(NullType));
	}

	TEST(TypeListTest, Length) {
		int result{ 0 };

		result = TypeListLength<NullType>::value;
		EXPECT_EQ(result, 0);

		result = TypeListLength<TypeList<int, NullType>>::value;
		EXPECT_EQ(result, 1);

		result = TypeListLength<TYPELIST_8(int, int, int, double, char, float, double, std::string)>::value;
		EXPECT_EQ(result, 8);
	}

	TEST(TypeListTest, TypeAt) {
		// Empty list.
		EXPECT_EQ(typeid(TypeAt<1, NullType>::type), typeid(NullType));

		// One element list.
		EXPECT_EQ(typeid(TypeAt<0, TYPELIST_1(int)>::type), typeid(int));

		// Index overflow.
		EXPECT_EQ(typeid(TypeAt<1, TYPELIST_1(int)>::type), typeid(NullType));
		
		// Multi element list.
		EXPECT_EQ(typeid(TypeAt<1, TYPELIST_5(int, int, double, char, std::string)>::type), typeid(int));
		EXPECT_EQ(typeid(TypeAt<3, TYPELIST_5(int, int, double, char, std::string)>::type), typeid(char));
		EXPECT_EQ(typeid(TypeAt<4, TYPELIST_5(int, int, double, char, std::string)>::type), typeid(std::string));
		EXPECT_EQ(typeid(TypeAt<5, TYPELIST_5(int, int, double, char, std::string)>::type), typeid(NullType));
	}

	TEST(TypeListTest, AddElements_Empty) {
		using ResultTList = AddElements<5, float, NullType>::type;

		int size{ 0 };
		size = TypeListLength<ResultTList>::value;
		EXPECT_EQ(size, 5);

		EXPECT_EQ(typeid(ResultTList), typeid(TYPELIST_5(float, float, float, float, float)));
	}

	TEST(TypeListTest, AddElements_NonEmpty) {
		using TList = TYPELIST_3(int, double, char);
		using ResultTList = AddElements<5, float, TList>::type;

		int size{ 0 };
		size = TypeListLength<ResultTList>::value;
		EXPECT_EQ(size, 8);

		EXPECT_EQ(typeid(ResultTList), typeid(TYPELIST_8(float, float, float, float, float, int, double, char)));
	}

	template<typename T>
	struct Wrapper { T val; };

	TEST(TypeListTest, WrappedTypeList) {
		using TList = TYPELIST_3(int, double, char);
		using ResultTList = WrappedTypeList<TList, Wrapper>::type;

		int size{ 0 };
		size = TypeListLength<ResultTList>::value;
		EXPECT_EQ(size, 3);

		EXPECT_EQ(typeid(ResultTList), typeid(TYPELIST_3(Wrapper<int>, Wrapper<double>, Wrapper<char>)));
	}

	TEST(TypeListTest, MergedTypeList) {
		using TList1 = TYPELIST_3(int, double, char);
		using TList2 = TYPELIST_2(int, std::string);
		using ResultTList = MergedTypeList<TList1, TList2>::type;

		EXPECT_EQ(typeid(ResultTList), typeid(TYPELIST_5(int, double, char, int, std::string)));
	}

} // namespace meta_structures_test