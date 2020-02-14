project(common_utils_unit_tests CXX)

# Add preprocessor definitions.
add_definitions(-DCOMPILE_CUDA)

# Add dependencies.
find_package(GTest CONFIG REQUIRED)
find_package(CUDA 9 REQUIRED)
find_package(Boost REQUIRED COMPONENTS serialization)

# Include all files
file(GLOB root "*.*")            
file(GLOB timing "timing/*.*")       
file(GLOB data_structures "data_structures/*.*")    
file(GLOB meta_structures "meta_structures/*.*")    
file(GLOB memory_managment "memory_managment/*.*")    

source_group("root" FILES ${root})
source_group("timing" FILES ${timing})
source_group("data_structures" FILES ${data_structures})
source_group("meta_structures" FILES ${meta_structures})
source_group("memory_managment" FILES ${memory_managment})

# Add executable.
cuda_add_executable(common_utils_unit_tests ${root} ${timing} ${data_structures} ${meta_structures} ${memory_managment})
target_link_libraries(common_utils_unit_tests ${CUDA_LIBRARIES} GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main ${Boost_SERIALIZATION_LIBRARY})
set_target_properties(common_utils_unit_tests PROPERTIES LINKER_LANGUAGE CXX)