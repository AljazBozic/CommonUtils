project(common_utils)

# Install all header files to include directory.
# file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.cuh")
# install(FILES ${headers} DESTINATION ${INCLUDES_INSTALL_DIR})

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/" # source directory
    DESTINATION ${INCLUDES_INSTALL_DIR} # target directory
    FILES_MATCHING # install only matched files
    PATTERN "*.h" 
    PATTERN "*.hpp" 
    PATTERN "*.cuh" 
)