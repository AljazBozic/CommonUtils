#include "common_utils/data_structures/Grid3.h"

#include <gtest/gtest.h>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <fstream>

using namespace common_utils;

namespace data_structures_tests {

	struct Grid3Test : testing::Test {
		unsigned m_dimX{ 3 };
		unsigned m_dimY{ 4 };
		unsigned m_dimZ{ 5 };
		Grid3<float> m_grid{ m_dimX, m_dimY, m_dimZ };

		Grid3Test() = default;
	};

	TEST_F(Grid3Test, Getters) {
		EXPECT_EQ(m_grid.getDimX(), m_dimX);
		EXPECT_EQ(m_grid.getDimY(), m_dimY);
		EXPECT_EQ(m_grid.getDimZ(), m_dimZ);
		EXPECT_EQ(m_grid.getSize(), m_dimX * m_dimY * m_dimZ);
	}

	TEST_F(Grid3Test, Allocate) {
		unsigned resizedDimX{ 3 };
		unsigned resizedDimY{ 1 };
		unsigned resizedDimZ{ 2 };
		m_grid.allocate(resizedDimX, resizedDimY, resizedDimZ);

		EXPECT_EQ(m_grid.getDimX(), resizedDimX);
		EXPECT_EQ(m_grid.getDimY(), resizedDimY);
		EXPECT_EQ(m_grid.getDimZ(), resizedDimZ);
		EXPECT_EQ(m_grid.getSize(), resizedDimX * resizedDimY * resizedDimZ);
	}

	TEST_F(Grid3Test, Clear) {
		m_grid.clear();

		EXPECT_EQ(m_grid.getDimX(), 0);
		EXPECT_EQ(m_grid.getDimY(), 0);
		EXPECT_EQ(m_grid.getDimZ(), 0);
		EXPECT_EQ(m_grid.getSize(), 0);
	}

	TEST_F(Grid3Test, Serialization) {
#		ifdef ENABLE_SERIALIZATION
		{
			std::ofstream ofs(std::string(OUTPUT_DIR) + "/grid3.bin", std::fstream::binary | std::fstream::out);
			boost::archive::binary_oarchive oa(ofs);
			oa << m_grid;
		}

		Grid3<float> gridRestored;
		{
			std::ifstream ifs(std::string(OUTPUT_DIR) + "/grid3.bin", std::fstream::binary | std::fstream::in);
			boost::archive::binary_iarchive ia(ifs);
			ia >> gridRestored;
		}

		ASSERT_EQ(m_grid.getDimX(), gridRestored.getDimX());
		ASSERT_EQ(m_grid.getDimY(), gridRestored.getDimY());
		ASSERT_EQ(m_grid.getDimZ(), gridRestored.getDimZ());
		ASSERT_EQ(m_grid.getSize(), gridRestored.getSize());

		for (int i = 0; i < m_grid.getSize(); i++) {
			EXPECT_FLOAT_EQ(m_grid.getData(Type2Type<MemoryTypeCPU>())[i], gridRestored.getData(Type2Type<MemoryTypeCPU>())[i]);
		}
#		else
		ASSERT_FALSE() << "Serialization not enabled. Define ENABLE_SERIALIZATION to test serialization.";
#		endif
	}

} // namespace data_structures_tests