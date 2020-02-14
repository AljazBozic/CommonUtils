// main.cpp : Defines the entry point for integration tests
//
#include <gtest/gtest.h>

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);

	// Just for debugging, you can run just a specific test.
	// Important: It will disable all other tests, even through Resharper interface.
	//testing::GTEST_FLAG(filter) = "ConstraintEvaluatorTest.EvaluateResidualsAndJacobian";

	int result = RUN_ALL_TESTS();
	return result;
}
