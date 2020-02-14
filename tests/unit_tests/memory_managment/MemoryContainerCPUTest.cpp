#include "common_utils/memory_managment/MemoryContainer.h"

#include <gtest/gtest.h>

using namespace common_utils;

namespace memory_managment_test {

	//######################################################################################################
	// MemoryContainer test using CPU.

	TEST(MemoryContainerTest, GetData) {
		MemoryContainer<float> container;
		EXPECT_EQ(typeid(container.getData(MemoryType::CPU_MEMORY)), typeid(float*));
	}

	TEST(MemoryContainerTest, Allocate) {
		unsigned size{ 10 };
		MemoryContainer<float> container;
		container.allocate(size, Type2Type<MemoryTypeCPU>());

		EXPECT_EQ(container.getSize(), size);
		EXPECT_EQ(container.isAllocatedHost(), true);
		EXPECT_EQ(container.isAllocatedDevice(), false);
	}

	TEST(MemoryContainerTest, SetUpdated) {
		MemoryContainer<float> container;
		container.setUpdated(true, false);

		EXPECT_EQ(container.isUpdatedHost(), true);
		EXPECT_EQ(container.isUpdatedDevice(), false);
	}

	TEST(MemoryContainerTest, CopyConstructor) {
		unsigned size{ 10 };
		MemoryContainer<float> container;
		container.allocate(size, Type2Type<MemoryTypeCPU>());

		MemoryContainer<float> newContainer{ container };

		// Check indexing.
		newContainer.getElement(5, Type2Type<MemoryTypeCPU>()) = 10.0;
		EXPECT_FLOAT_EQ(newContainer.getElement(5, Type2Type<MemoryTypeCPU>()), 10.0);

		// Check size.
		EXPECT_EQ(newContainer.getSize(), size);
	}

	TEST(MemoryContainerTest, CopyAssignment) {
		unsigned size{ 10 };
		MemoryContainer<float> container;
		container.allocate(size, Type2Type<MemoryTypeCPU>());

		MemoryContainer<float> newContainer;
		newContainer.allocate(1, Type2Type<MemoryTypeCPU>());
		newContainer = container;

		// Check indexing.
		newContainer.getElement(5, Type2Type<MemoryTypeCPU>()) = 10.0;
		EXPECT_FLOAT_EQ(newContainer.getElement(5, Type2Type<MemoryTypeCPU>()), 10.0);

		// Check size.
		EXPECT_EQ(newContainer.getSize(), size);
	}

	TEST(MemoryContainerTest, MoveConstructor) {
		unsigned size{ 10 };
		MemoryContainer<float> container;
		container.allocate(size, Type2Type<MemoryTypeCPU>());

		MemoryContainer<float> newContainer{ std::move(container) };

		// Check indexing.
		newContainer.getElement(5, Type2Type<MemoryTypeCPU>()) = 10.0;
		EXPECT_FLOAT_EQ(newContainer.getElement(5, Type2Type<MemoryTypeCPU>()), 10.0);

		// Check size.
		EXPECT_EQ(newContainer.getSize(), size);
	}

	TEST(MemoryContainerTest, MoveAssignment) {
		unsigned size{ 10 };
		MemoryContainer<float> container;
		container.allocate(size, Type2Type<MemoryTypeCPU>());

		MemoryContainer<float> newContainer;
		newContainer.allocate(1, Type2Type<MemoryTypeCPU>());
		newContainer = std::move(container);

		// Check indexing.
		newContainer.getElement(5, Type2Type<MemoryTypeCPU>()) = 10.0;
		EXPECT_FLOAT_EQ(newContainer.getElement(5, Type2Type<MemoryTypeCPU>()), 10.0);

		// Check size.
		EXPECT_EQ(newContainer.getSize(), size);
	}

	TEST(MemoryContainerTest, InitializationWithRawData) {
		const unsigned size = 6;
		double rawData[6] = { 0.2, 0.3, 0.4, -0.1, -0.2, -0.3 };

		MemoryContainer<double> container{ rawData, size };
		EXPECT_EQ(container.getSize(), size);

		for (int i = 0; i < size; ++i) {
			EXPECT_FLOAT_EQ(container.getElement(i, Type2Type<MemoryTypeCPU>()), rawData[i]);
		}
	}

} // namespace memory_managment_test