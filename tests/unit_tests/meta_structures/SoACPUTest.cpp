#include "common_utils/meta_structures/SoA.h"

#include <gtest/gtest.h>

using namespace common_utils;

namespace meta_structures_test {

	//######################################################################################################
	// SoA test.

	TEST(SoATest, CreatePointerTypeList) {
		EXPECT_EQ(typeid(CreatePointerTypeList<typename TL<>::type>::type), typeid(NullType));
		EXPECT_EQ(typeid(CreatePointerTypeList<typename TL<double>::type>::type), typeid(TL<double*>::type));
		EXPECT_EQ(typeid(CreatePointerTypeList<typename TL<double, float>::type>::type), typeid(TL<double*, float*>::type));
		EXPECT_EQ(typeid(CreatePointerTypeList<typename TL<double, SoA<true, typename TL<float, int>::type>>::type>::type), 
			typeid(TL<double*, SoA<true, TL<float, int>::type>>::type));
		EXPECT_EQ(typeid(CreatePointerTypeList<typename TL<double, SoA<true, typename TL<float, int>::type>, float>::type>::type),
			typeid(TL<double*, SoA<true, TL<float, int>::type>, float*>::type));
	}

	TEST(SoATest, CreateBasePointerTypeList) {
		EXPECT_EQ(typeid(CreateBasePointerTypeList<typename TL<>::type>::type), typeid(NullType));
		EXPECT_EQ(typeid(CreateBasePointerTypeList<typename TL<double>::type>::type), typeid(TL<double*>::type));
		EXPECT_EQ(typeid(CreateBasePointerTypeList<typename TL<double, float>::type>::type), typeid(TL<double*, float*>::type));
		EXPECT_EQ(typeid(CreateBasePointerTypeList<typename TL<SoA<true, typename TL<float>::type>>::type>::type),
			typeid(TL<float*>::type));
		EXPECT_EQ(typeid(CreateBasePointerTypeList<typename TL<double, SoA<true, typename TL<float, int>::type>>::type>::type),
			typeid(TL<double*, float*, int*>::type));
		EXPECT_EQ(typeid(CreateBasePointerTypeList<typename TL<double, SoA<true, typename TL<float, int>::type>, float>::type>::type),
			typeid(TL<double*, float*, int*, float*>::type));
	}

	TEST(SoATest, CreateMemoryContainerTypeList) {
		EXPECT_EQ(typeid(CreateMemoryContainerTypeList<typename TL<>::type>::type), typeid(NullType));
		EXPECT_EQ(typeid(CreateMemoryContainerTypeList<typename TL<double>::type>::type), typeid(TL<MemoryContainer<double>>::type));
		EXPECT_EQ(typeid(CreateMemoryContainerTypeList<typename TL<double, float>::type>::type), typeid(TL<MemoryContainer<double>, MemoryContainer<float>>::type));
		EXPECT_EQ(typeid(CreateMemoryContainerTypeList<typename TL<double, SoA<true, typename TL<float, int>::type>>::type>::type),
			typeid(TL<MemoryContainer<double>, SoA<true, TL<float, int>::type>>::type));
		EXPECT_EQ(typeid(CreateMemoryContainerTypeList<typename TL<double, SoA<true, typename TL<float, int>::type>, float>::type>::type),
			typeid(TL<MemoryContainer<double>, SoA<true, TL<float, int>::type>, MemoryContainer<float>>::type));
	}

	TEST(SoATest, ElementSize) {
		int result{ 0 };

		result = ElementSize<float>::value;
		EXPECT_EQ(result, 1);

		result = ElementSize<SoA<true, typename TL<double>::type>>::value;
		EXPECT_EQ(result, 1);

		result = ElementSize<SoA<true, typename TL<double, float>::type>>::value;
		EXPECT_EQ(result, 2);

		result = ElementSize<SoA<true, typename TL<double, float>::type>>::value;
		EXPECT_EQ(result, 2);
	
		result = ElementSize<SoA<true, typename TL<double, SoA<true, typename TL<double, float>::type>>::type>>::value;
		EXPECT_EQ(result, 3);

		result = ElementSize<SoA<true, typename TL<double, SoA<true, typename TL<double, float>::type>, int>::type>>::value;
		EXPECT_EQ(result, 4);
	}

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

	TEST(SoATest, WrapAround_Vec3) {
		Vec3<false> vStorage;
		vStorage.allocate(3);

		auto pointerListTuple = vStorage.getPointerList();
		
		Vec3<true> vInterface;
		vInterface.wrap(pointerListTuple);

		for (int i = 0; i < 3; ++i) {
			vInterface.x()[i] = i * 1.0;
			vInterface.y()[i] = i * 2.0;
			vInterface.z()[i] = i * 3.0;
		}

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

	TEST(SoATest, Color_WrapAround) {
		Color<false> colorStorage;
		colorStorage.allocate(3);

		auto pointerListTuple = colorStorage.getPointerList();

		Color<true> colorInterface;
		colorInterface.wrap(pointerListTuple);

		for (int i = 0; i < 3; ++i) {
			colorInterface.rgb().x()[i] = i * 1.0;
			colorInterface.rgb().y()[i] = i * 2.0;
			colorInterface.rgb().z()[i] = i * 3.0;
			colorInterface.alpha()[i] = i * 4.f;
		}

		for (int i = 0; i < 3; ++i) {
			EXPECT_FLOAT_EQ(colorInterface.rgb().x()[i], i * 1.0);
			EXPECT_FLOAT_EQ(colorInterface.rgb().y()[i], i * 2.0);
			EXPECT_FLOAT_EQ(colorInterface.rgb().z()[i], i * 3.0);
			EXPECT_FLOAT_EQ(colorInterface.alpha()[i], i * 4.f);
		}
	}

	TEST(SoATest, IsDerivedFromSoA) {
		EXPECT_EQ(typeid(IsDerivedFromSoA<float>::type), typeid(Bool2Type<false>));
		EXPECT_EQ(typeid(IsDerivedFromSoA<SoA<true, typename TL<>::type>>::type), typeid(Bool2Type<true>));
		EXPECT_EQ(typeid(IsDerivedFromSoA<Vec3<true>>::type), typeid(Bool2Type<true>));
		EXPECT_EQ(typeid(IsDerivedFromSoA<Color<true>>::type), typeid(Bool2Type<true>));
	}

	TEST(SoATest, SoASize) {
		int size{ 0 };

		size = SoASize<Vec3<true>>::value;
		EXPECT_EQ(size, 3);
		
		size = SoASize<Vec3<false>>::value;
		EXPECT_EQ(size, 3);

		size = SoASize<Color<true>>::value;
		EXPECT_EQ(size, 4);

		size = SoASize<Color<false>>::value;
		EXPECT_EQ(size, 4);
	}

	TEST(SoATest, SoAPointerList) {
		EXPECT_EQ(typeid(SoAPointerList<Vec3<true>>::type), typeid(Tuple<TL<double*, double*, double*>::type>));
		EXPECT_EQ(typeid(SoAPointerList<Vec3<false>>::type), typeid(Tuple<TL<double*, double*, double*>::type>));
		EXPECT_EQ(typeid(SoAPointerList<Color<true>>::type), typeid(Tuple<TL<double*, double*, double*, float*>::type>));
		EXPECT_EQ(typeid(SoAPointerList<Color<false>>::type), typeid(Tuple<TL<double*, double*, double*, float*>::type>));
	}

	TEST(SoATest, GetSize) {
		const unsigned nColors = 10;

		Color<false> colorStorage;
		colorStorage.allocate(nColors);

		long size = colorStorage.getSize();
		EXPECT_EQ(size, nColors);
	}

	TEST(SoATest, GetByteSize) {
		const unsigned nColors = 10;
		
		Color<false> colorStorage;
		colorStorage.allocate(nColors);

		long size = colorStorage.getByteSize();
		EXPECT_EQ(size, 3 * nColors * sizeof(double) + nColors * sizeof(float));
	}

} // namespace meta_structures_test