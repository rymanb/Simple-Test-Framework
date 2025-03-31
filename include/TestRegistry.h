#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <stdexcept>
#include <utility>


// Singleton test registry
class TestRegistry {
    public:
        // Get the singleton instance of the test registry
        static TestRegistry& Instance();
    
        // Add a test to the registry
        void AddTest(const std::string& name, std::function<void()> testFunc);
    
        // Run all tests in the registry
        void RunAllTests();

        void RunFilteredTests(const std::string& filter);
    
    private:
        TestRegistry() = default;

        // get the list of tests
        const std::vector<std::pair<std::string, std::function<void()>>>& GetTests() const;

        // Disable copy constructor and assignment operator
        TestRegistry(const TestRegistry&) = delete;
        TestRegistry& operator=(const TestRegistry&) = delete;

        // Vector to hold test functions and their names
        std::vector<std::pair<std::string, std::function<void()>>> tests;
    };
    
    // Helper function to register tests
    class TestRegister {
    public:
        TestRegister(const std::string& name, std::function<void()> func);
    };