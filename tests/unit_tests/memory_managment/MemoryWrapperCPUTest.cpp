#include "common_utils/memory_managment/MemoryWrapper.h"

#include <gtest/gtest.h>

#include "common_utils/memory_managment/MemoryContainer.h"

using namespace common_utils;

namespace memory_managment_test {

	//######################################################################################################
	// MemoryWrapper test using CPU.

	TEST(MemoryWrapperTest, InitializeWithRawCPUData) {
		const unsigned size = 6;
		double rawData[6] = { 0.2, 0.3, 0.4, -0.1, -0.2, -0.3 };

		MemoryWrapper<double> wrapper{ rawData, size, Type2Type<MemoryTypeCPU>() };
		EXPECT_EQ(typeid(wrapper.getData(Type2Type<MemoryTypeCPU>())), typeid(double*));
		EXPECT_EQ(wrapper.getSize(), size);
	}

	TEST(MemoryWrapperTest, WrapAroundRawCPUData) {
		const unsigned size = 6;
		double rawData[6] = { 0.2, 0.3, 0.4, -0.1, -0.2, -0.3 };

		MemoryWrapper<double> wrapper;
		wrapper.wrapMemory(rawData, size, Type2Type<MemoryTypeCPU>());
		EXPECT_EQ(typeid(wrapper.getData(Type2Type<MemoryTypeCPU>())), typeid(double*));
		EXPECT_EQ(wrapper.getSize(), size);
	}

} // namespace memory_managment_test