#include "common_utils/data_structures/Grid2.h"

#include <gtest/gtest.h>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <fstream>

using namespace common_utils;

namespace data_structures_tests {

	struct Grid2Test : testing::Test {
		unsigned m_dimX{ 3 };
		unsigned m_dimY{ 4 };
		Grid2<float> m_grid{ m_dimX, m_dimY };

		Grid2Test() = default;
	};

	TEST_F(Grid2Test, Getters) {
		EXPECT_EQ(m_grid.getDimX(), 3);
		EXPECT_EQ(m_grid.getDimY(), 4);
		EXPECT_EQ(m_grid.getSize(), 3 * 4);
	}

	TEST_F(Grid2Test, Allocate) {
		unsigned resizedDimX{ 3 };
		unsigned resizedDimY{ 1 };
		m_grid.allocate(resizedDimX, resizedDimY);

		EXPECT_EQ(m_grid.getDimX(), 3);
		EXPECT_EQ(m_grid.getDimY(), 1);
		EXPECT_EQ(m_grid.getSize(), 3 * 1);
	}

	TEST_F(Grid2Test, Clear) {
		m_grid.clear();

		EXPECT_EQ(m_grid.getDimX(), 0);
		EXPECT_EQ(m_grid.getDimY(), 0);
		EXPECT_EQ(m_grid.getSize(), 0);
	}

	TEST_F(Grid2Test, Serialization) {
#		ifdef ENABLE_SERIALIZATION
		{
			std::ofstream ofs(std::string(OUTPUT_DIR) + "/grid2.bin", std::fstream::binary | std::fstream::out);
			boost::archive::binary_oarchive oa(ofs);
			oa << m_grid;
		}

		Grid2<float> gridRestored;
		{
			std::ifstream ifs(std::string(OUTPUT_DIR) + "/grid2.bin", std::fstream::binary | std::fstream::in);
			boost::archive::binary_iarchive ia(ifs);
			ia >> gridRestored;
		}

		ASSERT_EQ(m_grid.getDimX(), gridRestored.getDimX());
		ASSERT_EQ(m_grid.getDimY(), gridRestored.getDimY());
		ASSERT_EQ(m_grid.getSize(), gridRestored.getSize());

		for (int i = 0; i < m_grid.getSize(); i++) {
			EXPECT_FLOAT_EQ(m_grid.getData(Type2Type<MemoryTypeCPU>())[i], gridRestored.getData(Type2Type<MemoryTypeCPU>())[i]);
		}
#		else
		ASSERT_FALSE() << "Serialization not enabled. Define ENABLE_SERIALIZATION to test serialization.";
#		endif

	}

} // namespace data_structures_tests