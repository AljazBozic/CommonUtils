#include "common_utils/data_structures/Grid3Interface.h"

#include <gtest/gtest.h>

using namespace common_utils;

namespace data_structures_tests {

	struct Grid3InterfaceTest : testing::Test {
		unsigned m_dimX{ 3 };
		unsigned m_dimY{ 4 };
		unsigned m_dimZ{ 5 };
		Grid3<float> m_grid{ m_dimX, m_dimY, m_dimZ };

		Grid3InterfaceTest() = default;
	};

	TEST_F(Grid3InterfaceTest, Getters) {
		Grid3Interface<float, MemoryTypeCPU> gridInt{ m_grid };
		EXPECT_EQ(gridInt.getDimX(), m_dimX);
		EXPECT_EQ(gridInt.getDimY(), m_dimY);
		EXPECT_EQ(gridInt.getDimZ(), m_dimZ);
		EXPECT_EQ(gridInt.getSize(), m_dimX * m_dimY * m_dimZ);
	}

	TEST_F(Grid3InterfaceTest, SetValue) {
		Grid3Interface<float, MemoryTypeCPU> gridInt{ m_grid };

		const float val{ 0.1f };
		gridInt.setValue(val);

		for (unsigned x = 0; x < gridInt.getDimX(); ++x) {
			for (unsigned y = 0; y < gridInt.getDimY(); ++y) {
				for (unsigned z = 0; z < gridInt.getDimZ(); z++) {
					EXPECT_FLOAT_EQ(gridInt(x, y, z), val);
				}
			}
		}
	}

	TEST_F(Grid3InterfaceTest, Indexing) {
		Grid3Interface<float, MemoryTypeCPU> gridInt{ m_grid };

		gridInt(1, 1, 1) = 0.5f;
		gridInt(1, 2, 3) = 0.3f;
		gridInt(0, 2, 3) = -0.2f;

		EXPECT_FLOAT_EQ(gridInt(1, 1, 1), 0.5f);
		EXPECT_FLOAT_EQ(gridInt(1, 2, 3), 0.3f);
		EXPECT_FLOAT_EQ(gridInt(0, 2, 3), -0.2f);
	}

} // namespace data_structures_tests