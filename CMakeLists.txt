cmake_minimum_required(VERSION 3.13)
project(Test_Framework VERSION 1.0
                  DESCRIPTION "C++ Test Framework"
                  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define library
add_library(Test_Framework STATIC
    src/TestRegistry.cpp
)

# Use relative include paths for relocatability
target_include_directories(Test_Framework
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Compiler options
target_compile_options(Test_Framework PRIVATE -Wall -Wextra -Werror -pedantic -mavx2)

# Optional: Shared library support
option(BUILD_SHARED_LIBS "Build as a shared library" OFF)
if(BUILD_SHARED_LIBS)
    set_target_properties(Test_Framework PROPERTIES POSITION_INDEPENDENT_CODE ON)
    target_compile_definitions(Test_Framework PRIVATE TEST_FRAMEWORK_SHARED)
endif()

# Ensure proper export
install(TARGETS Test_Framework
    EXPORT Test_FrameworkTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(EXPORT Test_FrameworkTargets
    FILE Test_FrameworkConfig.cmake
    NAMESPACE Test_Framework::
    DESTINATION lib/cmake/Test_Framework
)

install(DIRECTORY include/ DESTINATION include)