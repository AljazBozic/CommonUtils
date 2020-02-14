#include "common_utils/memory_managment/MemoryWrapper.h"

#include <gtest/gtest.h>
#include <cuda_runtime_api.h>

#include "common_utils/memory_managment/MemoryContainer.h"
#include "common_utils/memory_managment/MemoryWrapperCUDA.cuh"
#include "common_utils/memory_managment/MemoryContainerCUDA.cuh"

using namespace common_utils;

namespace memory_managment_test {

	//######################################################################################################
	// MemoryWrapper test using CUDA.

	TEST(MemoryWrapperCUDATest, InitializeWithRawCPUData) {
		const unsigned size = 6;
		double rawData[6] = { 0.2, 0.3, 0.4, -0.1, -0.2, -0.3 };

		MemoryWrapper<double> wrapper{ rawData, size, Type2Type<MemoryTypeCPU>() };
		EXPECT_EQ(typeid(wrapper.getData(Type2Type<MemoryTypeCPU>())), typeid(double*));
		EXPECT_EQ(wrapper.getSize(), size);
		EXPECT_EQ(wrapper.isUpdatedHost(), true);
		EXPECT_EQ(wrapper.isUpdatedDevice(), false);
	}

	TEST(MemoryWrapperCUDATest, InitializeWithRawGPUData) {
		const unsigned size = 6;
		MemoryContainer<double> data;
		data.allocate(size);
		double* rawData = data.getData(Type2Type<MemoryTypeCUDA>());

		MemoryWrapper<double> wrapper{ rawData, size, Type2Type<MemoryTypeCUDA>() };
		EXPECT_EQ(typeid(wrapper.getData(Type2Type<MemoryTypeCUDA>())), typeid(double*));
		EXPECT_EQ(wrapper.getSize(), size);
		EXPECT_EQ(wrapper.isUpdatedHost(), false);
		EXPECT_EQ(wrapper.isUpdatedDevice(), true);
	}

	TEST(MemoryWrapperCUDATest, WrapAroundRawCPUData) {
		const unsigned size = 6;
		double rawData[6] = { 0.2, 0.3, 0.4, -0.1, -0.2, -0.3 };

		MemoryWrapper<double> wrapper;
		wrapper.wrapMemory(rawData, size, Type2Type<MemoryTypeCPU>());
		EXPECT_EQ(typeid(wrapper.getData(Type2Type<MemoryTypeCPU>())), typeid(double*));
		EXPECT_EQ(wrapper.getSize(), size);
		EXPECT_EQ(wrapper.isUpdatedHost(), true);
		EXPECT_EQ(wrapper.isUpdatedDevice(), false);
	}

	TEST(MemoryWrapperCUDATest, WrapAroundRawGPUData) {
		const unsigned size = 6;
		MemoryContainer<double> data;
		data.allocate(size);
		double* rawData = data.getData(Type2Type<MemoryTypeCUDA>());

		MemoryWrapper<double> wrapper;
		wrapper.wrapMemory(rawData, size, Type2Type<MemoryTypeCUDA>());
		EXPECT_EQ(typeid(wrapper.getData(Type2Type<MemoryTypeCUDA>())), typeid(double*));
		EXPECT_EQ(wrapper.getSize(), size);
		EXPECT_EQ(wrapper.isUpdatedHost(), false);
		EXPECT_EQ(wrapper.isUpdatedDevice(), true);
	}

	TEST(MemoryWrapperCUDATest, CopyMemory) {
		const unsigned size = 6;
		double rawData[6] = { 0.2, 0.3, 0.4, -0.1, -0.2, -0.3 };

		// Wrap around host memory.
		MemoryWrapper<double> wrapper;
		wrapper.wrapMemory(rawData, size, Type2Type<MemoryTypeCPU>());
		EXPECT_EQ(typeid(wrapper.getData(Type2Type<MemoryTypeCPU>())), typeid(double*));
		EXPECT_EQ(wrapper.getSize(), size);

		// Update device memory.
		EXPECT_EQ(wrapper.isUpdatedDevice(), false);
		wrapper.copyHostToDevice();
		wrapper.setUpdated(true, true);
		EXPECT_EQ(wrapper.isUpdatedDevice(), true);
	}

} // namespace memory_managment_test