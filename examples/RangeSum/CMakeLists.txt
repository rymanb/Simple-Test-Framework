cmake_minimum_required(VERSION 3.11)

# Define the project name and specify C++ as the language
project(MyTestProject LANGUAGES CXX)

# Include the FetchContent module
include(FetchContent)

# Declare the Simple-Test-Framework dependency
FetchContent_Declare(
    Test_Framework
    GIT_REPOSITORY https://github.com/rymanb/Simple-Test-Framework.git
    GIT_TAG        main  # or specify a specific commit hash or tag
)

# Make the Simple-Test-Framework available
FetchContent_MakeAvailable(Test_Framework)

# Add the executable target
add_executable(MyTestExecutable test.cpp RangeSum.cpp)

add_definitions(-DTEST_FRAMEWORK_AUTO_RUN)


# Link the Simple-Test-Framework library to the executable
target_link_libraries(MyTestExecutable PRIVATE Test_Framework)

target_compile_options(MyTestExecutable PRIVATE -Wall -Wextra -Werror -pedantic -mavx2)