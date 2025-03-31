#include "TestRegistry.h"
#include "ColorCodes.h"
#include <regex>

// Singleton test registry
TestRegistry& TestRegistry::Instance() {
    static TestRegistry instance;
    return instance;
}

// Add a test to the registry
void TestRegistry::AddTest(const std::string& name, std::function<void()> testFunc) {
    tests.emplace_back(name, testFunc);
}

// Run all tests in the registry
void TestRegistry::RunAllTests() {
    int passed = 0;
    int failed = 0;

    std::cout << COLOR_BLUE << "[==========] Running " << tests.size() << " test(s)." << COLOR_RESET << std::endl;

    // Run each test and catch exceptions
    for (const auto& [name, test] : tests) {
        std::cout << COLOR_YELLOW << "[ RUN      ] " << name << COLOR_RESET << std::endl;
        try {
            test();
            std::cout << COLOR_GREEN << "[       OK ] " << name << COLOR_RESET << std::endl;
            passed++;
        } catch (const std::exception& e) {
            std::cout << COLOR_RED << "[  FAILED  ] " << name << COLOR_RESET << std::endl;
            std::cout << COLOR_RED << "Error: " << e.what() << COLOR_RESET << std::endl;
            failed++;
        }
    }

    std::cout << COLOR_BLUE << "[==========] " << tests.size() << " test(s) run." << COLOR_RESET << std::endl;
    std::cout << COLOR_GREEN << "[  PASSED  ] " << passed << COLOR_RESET << std::endl;

    if (failed > 0) {
        std::cout << COLOR_RED << "[  FAILED  ] " << failed << COLOR_RESET << std::endl;
    }
}

// Get the list of tests
const std::vector<std::pair<std::string, std::function<void()>>>& TestRegistry::GetTests() const {
    return tests;
}

void TestRegistry::RunFilteredTests(const std::string& filter) {
    int passed = 0, failed = 0;
    std::regex pattern(filter);

    for (const auto& [name, test] : TestRegistry::Instance().GetTests()) {
        if (!std::regex_search(name, pattern)) continue;

        std::cout << COLOR_YELLOW << "[ RUN      ] " << name << COLOR_RESET << std::endl;
        try {
            test();
            std::cout << COLOR_GREEN << "[       OK ] " << name << COLOR_RESET << std::endl;
            passed++;
        } catch (const std::exception& e) {
            std::cout << COLOR_RED << "[  FAILED  ] " << name << COLOR_RESET << std::endl;
            std::cout << COLOR_RED << "Error: " << e.what() << COLOR_RESET << std::endl;
            failed++;
        }
    }

    std::cout << COLOR_BLUE << "[==========] " << tests.size() << " test(s) run." << COLOR_RESET << std::endl;
    std::cout << COLOR_GREEN << "[  PASSED  ] " << passed << COLOR_RESET << std::endl;

    if (failed > 0) {
        std::cout << COLOR_RED << "[  FAILED  ] " << failed << COLOR_RESET << std::endl;
    }
}


// Helper function to register tests in macros
TestRegister::TestRegister(const std::string& name, std::function<void()> func) {
    TestRegistry::Instance().AddTest(name, func);
}