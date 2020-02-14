#include "common_utils/meta_structures/BasicOperations.h"

#include <gtest/gtest.h>

using namespace common_utils;

namespace meta_structures_test {

	//######################################################################################################
	// BasicOperations test.

	struct DoWorkWithoutArgs {
		template<int idx> static void f() {}
	};

	struct DoWorkWithArgs {
		template<int idx> static void f(float* input, float* output) {
			output[idx] = 2.f * input[idx];
		}
	};

	TEST(BasicOperationsTest, StaticFor_NoArgs) {
		static_for<10, DoWorkWithoutArgs>();
		EXPECT_TRUE(true);
	}

	TEST(BasicOperationsTest, StaticFor_Count) {
		float input[5]{ 1.f, 2.f, 3.f, 4.f, 5.f };
		float output[5];

		static_for<5, DoWorkWithArgs>(input, output);

		for (int i = 0; i < 5; ++i) {
			EXPECT_FLOAT_EQ(output[i], 2 * input[i]);
		}
	}

	TEST(BasicOperationsTest, StaticFor_Range) {
		float input[5]{ 1.f, 2.f, 3.f, 4.f, 5.f };
		float output[5];

		static_for<0, 4, DoWorkWithArgs>(input, output);
		
		for (int i = 0; i < 5; ++i) {
			EXPECT_FLOAT_EQ(output[i], 2 * input[i]);
		}
	}

	TEST(BasicOperationsTest, RemoveConstAndRef) {
		EXPECT_EQ(typeid(RemoveConstAndRef<NullType>::type), typeid(NullType));
		EXPECT_EQ(typeid(RemoveConstAndRef<int>::type), typeid(int));
		EXPECT_EQ(typeid(RemoveConstAndRef<float>::type), typeid(float));
		EXPECT_EQ(typeid(RemoveConstAndRef<int&>::type), typeid(int));
		EXPECT_EQ(typeid(RemoveConstAndRef<float&>::type), typeid(float));
		EXPECT_EQ(typeid(RemoveConstAndRef<const int>::type), typeid(int));
		EXPECT_EQ(typeid(RemoveConstAndRef<const float>::type), typeid(float));
		EXPECT_EQ(typeid(RemoveConstAndRef<const int&>::type), typeid(int));
		EXPECT_EQ(typeid(RemoveConstAndRef<const float&>::type), typeid(float));
		EXPECT_EQ(typeid(RemoveConstAndRef<TL<float, double>::type>::type), typeid(TL<float, double>::type));
		EXPECT_EQ(typeid(RemoveConstAndRef<TL<const float, double&>::type>::type), typeid(TL<float, double>::type));
		EXPECT_EQ(typeid(RemoveConstAndRef<TL<const float&, const double&>::type>::type), typeid(TL<float, double>::type));
	}

	TEST(BasicOperationsTest, ExtractValue_Unsigned) {
		EXPECT_EQ(ExtractValue<Unsigned2Type<0>>::value, 0);
		EXPECT_EQ(ExtractValue<Unsigned2Type<3>>::value, 3);
		EXPECT_EQ(ExtractValue<Unsigned2Type<1000>>::value, 1000);
	}

	TEST(BasicOperationsTest, ExtractValue_Int) {
		EXPECT_EQ(ExtractValue<Int2Type<0>>::value, 0);
		EXPECT_EQ(ExtractValue<Int2Type<3>>::value, 3);
		EXPECT_EQ(ExtractValue<Int2Type<1000>>::value, 1000);
		EXPECT_EQ(ExtractValue<Int2Type<-2>>::value, -2);
	}

	TEST(BasicOperationsTest, MinValue) {
		auto r0{ MinValue<0, 1>::value };
		EXPECT_EQ(r0, 0);

		auto r1{ MinValue<-1, 1>::value };
		EXPECT_EQ(r1, -1);

		auto r2{ MinValue<10, 20>::value };
		EXPECT_EQ(r2, 10);

		auto r3{ MinValue<-3, -2>::value };
		EXPECT_EQ(r3, -3);
	}

	TEST(BasicOperationsTest, MaxValue) {
		auto r0{ MaxValue<0, 1>::value };
		EXPECT_EQ(r0, 1);

		auto r1{ MaxValue<-1, 1>::value };
		EXPECT_EQ(r1, 1);

		auto r2{ MaxValue<10, 20>::value };
		EXPECT_EQ(r2, 20);

		auto r3{ MaxValue<-3, -2>::value };
		EXPECT_EQ(r3, -2);
	}

} // namespace meta_structures_test