cmake_minimum_required(VERSION 3.1)

project(common_utils)

# Add custom install directory.
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../LibLocal" CACHE PATH "Default install path" FORCE )
endif()

# The library prefix.
set(LIB_PREFIX common_utils_)

# Default built type.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# Postfix, based on type.
set(CMAKE_DEBUG_POSTFIX "_d" CACHE STRING "Postfix applied to debug build of libraries")
set(CMAKE_RELEASE_POSTFIX "" CACHE STRING "Postfix applied to release build of libraries")
set(CMAKE_RELWITHDEBINFO_POSTFIX "_rd" CACHE STRING "Postfix applied to release-with-debug-information libraries")
set(CMAKE_MINSIZEREL_POSTFIX "_s" CACHE STRING "Postfix applied to minimium-size-build libraries")

# Work out the postfix; required where we use OUTPUT_NAME.
if(CMAKE_BUILD_TYPE MATCHES Release)
  set(EXE_POSTFIX)
elseif(CMAKE_BUILD_TYPE MATCHES Debug)
  set(EXE_POSTFIX ${CMAKE_DEBUG_POSTFIX})
elseif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
  set(EXE_POSTFIX ${CMAKE_RELWITHDEBINFO_POSTFIX})
elseif(CMAKE_BUILD_TYPE MATCHES MinSizeRel)
  set(EXE_POSTFIX ${CMAKE_MINSIZEREL_POSTFIX})
endif(CMAKE_BUILD_TYPE MATCHES Release)

# Allow the developer to select if Dynamic or Static libraries are built.
option (BUILD_SHARED_LIBS "Build Shared Libraries" OFF)
set (common_utils_LIB_TYPE STATIC)
if (BUILD_SHARED_LIBS)
  set (common_utils_LIB_TYPE SHARED)
endif()

# set the output directory for the build executables and libraries
set(common_utils_RUNTIME_OUTPUT_DIRECTORY ${common_utils_SOURCE_DIR}/bin CACHE PATH "Target for the binaries")
if(WIN32)
  set(common_utils_LIBRARY_OUTPUT_DIRECTORY ${common_utils_SOURCE_DIR}/bin CACHE PATH "Target for the libraries")
else(WIN32)
  set(common_utils_LIBRARY_OUTPUT_DIRECTORY ${common_utils_SOURCE_DIR}/lib CACHE PATH "Target for the libraries")
endif(WIN32)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${common_utils_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${common_utils_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${common_utils_RUNTIME_OUTPUT_DIRECTORY})

# Set standard installation directories
set(RUNTIME_DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
set(LIBRARY_DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
set(ARCHIVE_DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
set(INCLUDES_DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
set(INCLUDES_INSTALL_DIR ${INCLUDES_DESTINATION}/common_utils)

# Set search directory for looking for our custom CMake scripts to
# look for grpc, protobuf.
#LIST(APPEND CMAKE_MODULE_PATH ${common_utils_SOURCE_DIR}/cmake)

# Detect OS and define macros appropriately.
if(WIN32)
  add_definitions(-DWINDOWS)
  message(STATUS "Compiling on Windows")
elseif(CYGWIN)
  message(STATUS "Compiling on Cygwin")
  add_definitions(-DCYGWIN)
elseif(APPLE)
  add_definitions(-DUNIX)
  message(STATUS "Compiling on OSX")
elseif(UNIX)
  add_definitions(-DUNIX)
  message(STATUS "Compiling on Unix")
endif(WIN32)

# C++11 support.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# OpenMP support.
find_package(OpenMP)
if(OPENMP_FOUND)
message("OPENMP FOUND")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# Specifying compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif(CMAKE_COMPILER_IS_GNUCXX)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Add global preprocessor definitions.
add_definitions(-DOUTPUT_DIR="${common_utils_SOURCE_DIR}/output")
add_definitions(-DENABLE_SERIALIZATION)

# Set up the top-level include directories.
# We add before to make prioritize local files to globally (already installed) library headers.
include_directories(BEFORE ${common_utils_SOURCE_DIR})

# Include the subdirectories
add_subdirectory(common_utils)
add_subdirectory(tests)