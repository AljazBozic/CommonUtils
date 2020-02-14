#include "common_utils/memory_managment/MemoryContainer.h"

#include <gtest/gtest.h>
#include <cuda_runtime_api.h>

#include "common_utils/memory_managment/MemoryContainerCUDA.cuh"

using namespace common_utils;

namespace memory_managment_test {

	//######################################################################################################
	// MemoryContainer test using CUDA.

	TEST(MemoryContainerCUDATest, GetData) {
		MemoryContainer<float> container;
		EXPECT_EQ(typeid(container.getData(MemoryType::CUDA_MEMORY)), typeid(float*));
	}

	TEST(MemoryContainerCUDATest, Allocate_OnlyHost) {
		unsigned size{ 10 };
		MemoryContainer<float> container;
		container.allocate(size, Type2Type<MemoryTypeCPU>());

		EXPECT_EQ(container.getSize(), size);
		EXPECT_EQ(container.isAllocatedHost(), true);
		EXPECT_EQ(container.isAllocatedDevice(), false);
	}

	TEST(MemoryContainerCUDATest, Allocate_OnlyDevice) {
		unsigned size{ 10 };
		MemoryContainer<float> container;
		container.allocate(size, Type2Type<MemoryTypeCUDA>());

		EXPECT_EQ(container.getSize(), size);
		EXPECT_EQ(container.isAllocatedHost(), false);
		EXPECT_EQ(container.isAllocatedDevice(), true);
	}

	TEST(MemoryContainerCUDATest, Allocate_BothHostAndDevice) {
		unsigned size{ 10 };
		MemoryContainer<float> container;
		
		// Resize both host and device memory.
		container.allocate(size, Type2Type<MemoryTypeCPU>());
		container.allocate(size, Type2Type<MemoryTypeCUDA>());

		EXPECT_EQ(container.getSize(), size);
		EXPECT_EQ(container.isAllocatedHost(), true);
		EXPECT_EQ(container.isAllocatedDevice(), true);

		// Reset both host and device memory.
		container.allocate(0, Type2Type<MemoryTypeCPU>());
		container.allocate(0, Type2Type<MemoryTypeCUDA>());

		EXPECT_EQ(container.getSize(), 0);
		EXPECT_EQ(container.isAllocatedHost(), false);
		EXPECT_EQ(container.isAllocatedDevice(), false);		
	}

	TEST(MemoryContainerCUDATest, SetUpdated) {
		MemoryContainer<float> container;
		container.setUpdated(true, false);

		EXPECT_EQ(container.isUpdatedHost(), true);
		EXPECT_EQ(container.isUpdatedDevice(), false);
	}

	TEST(MemoryContainerCUDATest, CopyDeviceToHost) {
		unsigned size{ 10 };
		MemoryContainer<float> container;
		container.allocate(size, Type2Type<MemoryTypeCPU>());
		container.allocate(size, Type2Type<MemoryTypeCUDA>());

		try {
			container.copyDeviceToHost();
			SUCCEED();
		}
		catch (...) {
			FAIL() << "Exception thrown";
		}
	}

	TEST(MemoryContainerCUDATest, CopyHostToDevice) {
		unsigned size{ 10 };
		MemoryContainer<float> container;
		container.allocate(size, Type2Type<MemoryTypeCPU>());
		container.allocate(size, Type2Type<MemoryTypeCUDA>());

		try {
			container.copyHostToDevice();
			SUCCEED();
		}
		catch (...) {
			FAIL() << "Exception thrown";
		}
	}

	TEST(MemoryContainerCUDATest, CopyConstructor) {
		unsigned size{ 10 };
		MemoryContainer<float> container;
		container.allocate(size, Type2Type<MemoryTypeCPU>());
		container.allocate(size, Type2Type<MemoryTypeCUDA>());

		MemoryContainer<float> newContainer{ container };

		// Check indexing.
		newContainer.getElement(5, Type2Type<MemoryTypeCPU>()) = 10.0;
		EXPECT_FLOAT_EQ(newContainer.getElement(5, Type2Type<MemoryTypeCPU>()), 10.0);

		// Check size.
		EXPECT_EQ(newContainer.getSize(), size);
	}

	TEST(MemoryContainerCUDATest, CopyAssignment) {
		unsigned size{ 10 };
		MemoryContainer<float> container;
		container.allocate(size, Type2Type<MemoryTypeCPU>());
		container.allocate(size, Type2Type<MemoryTypeCUDA>());

		MemoryContainer<float> newContainer;
		newContainer.allocate(1, Type2Type<MemoryTypeCPU>());
		newContainer.allocate(1, Type2Type<MemoryTypeCUDA>());
		newContainer = container;

		// Check indexing.
		newContainer.getElement(5, Type2Type<MemoryTypeCPU>()) = 10.0;
		EXPECT_FLOAT_EQ(newContainer.getElement(5, Type2Type<MemoryTypeCPU>()), 10.0);

		// Check size.
		EXPECT_EQ(newContainer.getSize(), size);
	}

	TEST(MemoryContainerCUDATest, MoveConstructor) {
		unsigned size{ 10 };
		MemoryContainer<float> container;
		container.allocate(size, Type2Type<MemoryTypeCPU>());
		container.allocate(size, Type2Type<MemoryTypeCUDA>());

		MemoryContainer<float> newContainer{ std::move(container) };

		// Check indexing.
		newContainer.getElement(5, Type2Type<MemoryTypeCPU>()) = 10.0;
		EXPECT_FLOAT_EQ(newContainer.getElement(5, Type2Type<MemoryTypeCPU>()), 10.0);

		// Check size.
		EXPECT_EQ(newContainer.getSize(), size);
	}

	TEST(MemoryContainerCUDATest, MoveAssignment) {
		unsigned size{ 10 };
		MemoryContainer<float> container;
		container.allocate(size, Type2Type<MemoryTypeCPU>());
		container.allocate(size, Type2Type<MemoryTypeCUDA>());

		MemoryContainer<float> newContainer;
		newContainer.allocate(1, Type2Type<MemoryTypeCPU>());
		newContainer.allocate(1, Type2Type<MemoryTypeCUDA>());
		newContainer = std::move(container);

		// Check indexing.
		newContainer.getElement(5, Type2Type<MemoryTypeCPU>()) = 10.0;
		EXPECT_FLOAT_EQ(newContainer.getElement(5, Type2Type<MemoryTypeCPU>()), 10.0);

		// Check size.
		EXPECT_EQ(newContainer.getSize(), size);
	}

} // namespace memory_managment_test