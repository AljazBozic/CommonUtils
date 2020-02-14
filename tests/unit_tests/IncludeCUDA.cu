#include "common_utils/IncludeImplCUDA.hpp"

// This file is only meant to compile the necessary CUDA methods.

// To enable Google Tests, we compile all tests with cpp compiler, and
// separately compile only CUDA code here. Otherwise, this precompilation
// would not be necessary.
#include "common_utils/memory_managment/MemoryWrapperCUDA.cuh"
#include "common_utils/memory_managment/MemoryContainerCUDA.cuh"
template class common_utils::MemoryWrapper<double>;
template class common_utils::MemoryWrapper<float>;
template class common_utils::MemoryContainer<double>;
template class common_utils::MemoryContainer<float>;