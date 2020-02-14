#include "common_utils/timing/Timing.h"

#include <gtest/gtest.h>

using namespace common_utils;

namespace timing_tests {

	//######################################################################################################
	// Timing test.

	TEST(TimingTest, PrintReport) {
		timing::start("TimingTest::totalTime");

		for (int i = 0; i < 100; ++i) {
			timing::start("SimpleOperations::multiplication");
			int a = i * i;
			timing::stop("SimpleOperations::multiplication");
			timing::start("SimpleOperations::assignment");
			int b = i;
			timing::stop("SimpleOperations::assignment");
			timing::start("SimpleOperations::sum");
			int c = a + b;
			timing::stop("SimpleOperations::sum");
		}

		timing::stop("TimingTest::totalTime");

		timing::print("TimingTest");
		timing::print("SimpleOperations");
		timing::print("TimingTest;SimpleOperations");
		timing::print();
	}

	TEST(TimingTest, PreprocessorSyntax) {
		TIME("TimingTest::totalTime") {
			for (int i = 0; i < 100; ++i) {
				int a, b, c;
				TIME("SimpleOperations::multiplication") {
					a = i * i;
				}
				TIME("SimpleOperations::assignment") {
					b = i;
				}
				TIME("SimpleOperations::sum") {
					c = a + b;
				}
			}
		}

		timing::print("TimingTest");
		timing::print("SimpleOperations");
		timing::print("TimingTest;SimpleOperations");
		timing::print();
	}

	TEST(TimingTest, AverageTime) {
		TIME("TimingTest::totalTime") {
			for (int i = 0; i < 100; ++i) {
				int a, b, c;
				TIME("SimpleOperations::multiplication") {
					a = i * i;
				}
				TIME("SimpleOperations::assignment") {
					b = i;
				}
				TIME("SimpleOperations::sum") {
					c = a + b;
				}
			}
		}

		cout << "Average multiplication time: " << timing::averageTime("SimpleOperations::multiplication") << endl;
		cout << "Average assignment time: " << timing::averageTime("SimpleOperations::assignment") << endl;
		cout << "Average sum time: " << timing::averageTime("SimpleOperations::sum") << endl;
	}

} // namespace timing_tests
