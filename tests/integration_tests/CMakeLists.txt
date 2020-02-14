project(common_utils_integration_tests CXX)

# Add dependencies.
find_package(GTest CONFIG REQUIRED)

# Include all files
file(GLOB integration_tests "*.*")            
source_group("integration_tests" FILES ${integration_tests} )

# Add executable.
add_executable(common_utils_integration_tests ${integration_tests})
target_link_libraries(common_utils_integration_tests GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)  
set_target_properties(common_utils_integration_tests PROPERTIES LINKER_LANGUAGE CXX)