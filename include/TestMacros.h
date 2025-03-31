#pragma once
#include <chrono>

// Defines a macro for test registration
#define TEST(test_name) \
    void test_name(); \
    TestRegister test_register_##test_name(#test_name, test_name); \
    void test_name()

// Defines macros for assertions
#define EXPECT_TRUE(condition) \
    if (!(condition)) throw std::runtime_error("Expected true: " #condition)

#define EXPECT_FALSE(condition) \
    if ((condition)) throw std::runtime_error("Expected false: " #condition)

#define EXPECT_EQ(val1, val2) \
    if ((val1) != (val2)) throw std::runtime_error("Expected equal: " #val1 " == " #val2)

#define EXPECT_NE(val1, val2) \
    if ((val1) == (val2)) throw std::runtime_error("Expected not equal: " #val1 " != " #val2)

    
#define TIME_TEST(name, test_func) \
{ \
    auto start = std::chrono::high_resolution_clock::now(); \
    test_func(); \
    auto end = std::chrono::high_resolution_clock::now(); \
    std::chrono::duration<double> duration = end - start; \
    std::cout << "[ TIME     ] " << name << " took " << duration.count() << "s" << std::endl; \
}

#define TEST_P(test_name, params, body) \
    void test_name(const auto&); \
    struct TestRegister_##test_name { \
        TestRegister_##test_name() { \
            for (const auto& param : params) { \
                TestRegistry::Instance().AddTest(#test_name "(" + std::to_string(param) + ")", [param]() { test_name(param); }); \
            } \
        } \
    } test_register_##test_name; \
    void test_name(const auto& param) body

// Defines a macro for automatic test execution
#ifdef TEST_FRAMEWORK_AUTO_RUN
    int main(int argc, char* argv[]) {
        if (argc == 2) {
            std::string filter = argv[1];
            TestRegistry::Instance().RunFilteredTests(filter);
        } else {
            TestRegistry::Instance().RunAllTests();
        }
        return 0;
    }
#endif  