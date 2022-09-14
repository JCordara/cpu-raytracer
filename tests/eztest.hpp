#ifndef EZTEST_H
#define EZTEST_H

#include <vector>
#include <iostream>

typedef bool (*TestFunc)(void);

namespace eztest {

    bool all_passed;

    struct Test {
        TestFunc func;
        const char* name;
    };

    std::vector<Test> tests;

    void add_test(TestFunc f, const char* test_name) {
        Test t;
        t.func = f;
        t.name = test_name;
        tests.push_back(t);
    }

    bool test_main() {
        all_passed = true;

        for (Test t : tests) {
            std::cout << "\nRunning test: " << t.name << " ... ";
            bool test_passed = t.func();
            std::cout << (test_passed ? "Pass" : "\n-- TEST FAILED\n");
            all_passed = all_passed && test_passed;
        }

        std::cout << "\n\n" << (all_passed ? "All tests passed!" : "Tests failed.") << "\n";
        return all_passed;
    }
};

#endif // EZTEST_H
