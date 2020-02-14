#include "common_utils/meta_structures/BasicTypes.h"

#include <gtest/gtest.h>

using namespace common_utils;

namespace meta_structures_test {

	//######################################################################################################
	// BasicTypes test.

	TEST(BasicTypesTest, ConditionedType) {
		EXPECT_EQ(typeid(ConditionedType<(3 > 1), int, double>::type), typeid(int));
		EXPECT_EQ(typeid(ConditionedType<(3 < 1), int, double>::type), typeid(double));
	}

	TEST(BasicTypesTest, RawArray) {
		RawArray<float, 0> emtpyArray;
		RawArray<float, 10> nonEmtpyArray;
		nonEmtpyArray[3] = 10.f;
		EXPECT_FLOAT_EQ(nonEmtpyArray[3], 10.f);
	}

} // namespace meta_structures_test