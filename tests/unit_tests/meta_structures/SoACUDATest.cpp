#include "common_utils/meta_structures/SoA.h"

#include <gtest/gtest.h>

using namespace common_utils;

namespace meta_structures_test {

	//######################################################################################################
	// SoA test.

	template<bool isInterface>
	class Vec3 : public SoA<
		isInterface,
		typename TL<double, double, double>::type
	> {
	public:
		CPU_AND_GPU double* x() { return t()[I<0>()]; }
		CPU_AND_GPU double* y() { return t()[I<1>()]; }
		CPU_AND_GPU double* z() { return t()[I<2>()]; }
	};

	TEST(SoACUDATest, Vec3_MemoryOperations) {
		Vec3<false> vStorage;
		vStorage.allocate(3, true, true);

		auto pointerListTuple = vStorage.getPointerList();

		Vec3<true> vInterface;
		vInterface.wrap(pointerListTuple);

		for (int i = 0; i < 3; ++i) {
			vInterface.x()[i] = i * 1.0;
			vInterface.y()[i] = i * 2.0;
			vInterface.z()[i] = i * 3.0;
		}

		vStorage.copyHostToDevice();
		vStorage.copyDeviceToHost();

		for (int i = 0; i < 3; ++i) {
			EXPECT_FLOAT_EQ(vInterface.x()[i], i * 1.0);
			EXPECT_FLOAT_EQ(vInterface.y()[i], i * 2.0);
			EXPECT_FLOAT_EQ(vInterface.z()[i], i * 3.0);
		}
	}

	template<bool isInterface>
	class Color : public SoA<
		isInterface,
		typename TL<Vec3<isInterface>, float>::type
	> {
	public:
		CPU_AND_GPU Vec3<isInterface>& rgb() { return t()[I<0>()]; }
		CPU_AND_GPU float* alpha() { return t()[I<1>()]; }
	};

	TEST(SoACUDATest, Color_MemoryOperations) {
		Color<false> colorStorage;
		colorStorage.allocate(3, true, true);

		auto pointerListTuple = colorStorage.getPointerList();

		Color<true> colorInterface;
		colorInterface.wrap(pointerListTuple);

		for (int i = 0; i < 3; ++i) {
			colorInterface.rgb().x()[i] = i * 1.0;
			colorInterface.rgb().y()[i] = i * 2.0;
			colorInterface.rgb().z()[i] = i * 3.0;
			colorInterface.alpha()[i] = i * 4.f;
		}

		colorStorage.copyHostToDevice();
		colorStorage.copyDeviceToHost();

		for (int i = 0; i < 3; ++i) {
			EXPECT_FLOAT_EQ(colorInterface.rgb().x()[i], i * 1.0);
			EXPECT_FLOAT_EQ(colorInterface.rgb().y()[i], i * 2.0);
			EXPECT_FLOAT_EQ(colorInterface.rgb().z()[i], i * 3.0);
			EXPECT_FLOAT_EQ(colorInterface.alpha()[i], i * 4.f);
		}
	}

} // namespace meta_structures_test