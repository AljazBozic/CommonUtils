#include "common_utils/data_structures/Grid2Interface.h"

#include <gtest/gtest.h>

using namespace common_utils;

namespace data_structures_tests {

	struct Grid2InterfaceTest : testing::Test {
		unsigned m_dimX{ 3 };
		unsigned m_dimY{ 4 };
		Grid2<float> m_grid{ m_dimX, m_dimY };

		Grid2InterfaceTest() = default;
	};

	TEST_F(Grid2InterfaceTest, Getters) {
		Grid2Interface<float, MemoryTypeCPU> gridInt{ m_grid };
		EXPECT_EQ(gridInt.getDimX(), m_dimX);
		EXPECT_EQ(gridInt.getDimY(), m_dimY);
		EXPECT_EQ(gridInt.getSize(), m_dimX * m_dimY);
	}

	TEST_F(Grid2InterfaceTest, SetValue) {
		Grid2Interface<float, MemoryTypeCPU> gridInt{ m_grid };

		const float val{ 0.1f };
		gridInt.setValue(val);

		for (unsigned x = 0; x < gridInt.getDimX(); ++x) {
			for (unsigned y = 0; y < gridInt.getDimY(); ++y) {
				EXPECT_FLOAT_EQ(gridInt(x, y), val);
			}
		}
	}

	TEST_F(Grid2InterfaceTest, Indexing) {
		Grid2Interface<float, MemoryTypeCPU> gridInt{ m_grid };

		gridInt(1, 1) = 0.5f;
		gridInt(1, 2) = 0.3f;
		gridInt(0, 2) = -0.2f;

		EXPECT_FLOAT_EQ(gridInt(1, 1), 0.5f);
		EXPECT_FLOAT_EQ(gridInt(1, 2), 0.3f);
		EXPECT_FLOAT_EQ(gridInt(0, 2), -0.2f);
	}

} // namespace data_structures_tests