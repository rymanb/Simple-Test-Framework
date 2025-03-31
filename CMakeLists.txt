cmake_minimum_required(VERSION 3.13)
project(Test_Framework VERSION 1.0 LANGUAGES CXX)

# Create the library
add_library(Test_Framework STATIC
    src/TestRegistry.cpp
)

# Ensure headers are available
target_include_directories(Test_Framework PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Export the target for external projects
install(TARGETS Test_Framework
    EXPORT Test_FrameworkTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)

# Generate a Config file for find_package
install(EXPORT Test_FrameworkTargets
    FILE Test_FrameworkConfig.cmake
    NAMESPACE Test_Framework::
    DESTINATION lib/cmake/Test_Framework
)

# Export for FetchContent builds
export(EXPORT Test_FrameworkTargets NAMESPACE Test_Framework::)