cmake_minimum_required(VERSION 3.11)

# Define the project name
project(Test_Framework VERSION 1.0 LANGUAGES CXX)

# Add the include directory
add_library(Test_Framework
    src/TestRegistry.cpp
)

# Specify the include directories for the target
target_include_directories(Test_Framework
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Optionally specify C++ standard
target_compile_features(Test_Framework PUBLIC cxx_std_11)

# Define installation rules
include(GNUInstallDirs)
install(TARGETS Test_Framework
    EXPORT Test_FrameworkTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export the targets to make them available for other projects
install(EXPORT Test_FrameworkTargets
    FILE Test_FrameworkTargets.cmake
    NAMESPACE Test_Framework::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Test_Framework
)

# Create a Config file for find_package support
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/Test_FrameworkConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/Test_FrameworkConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Test_Framework
)