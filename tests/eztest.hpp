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
        int name_len;
    };

    std::vector<Test> tests;

    void add_test(TestFunc f, const char* test_name) {
        // Get test_name length
        const char *p = test_name;
        int len = 0;
        while (*p != '\0') {
            p++;
            len++;
        }

        Test t;
        t.func = f;
        t.name = test_name;
        t.name_len = len;
        tests.push_back(t);
    }

    bool test_main() {
        // Used for aligning output
        int max_name_len = 0;
        for (Test t : tests) {
            if (t.name_len > max_name_len) {
                max_name_len = t.name_len;
            }
        }

        all_passed = true;
        for (Test t : tests) {
            std::cout << "\nRunning test: " << t.name << " ";
            bool test_passed = t.func();
            all_passed = all_passed && test_passed;

            // Align output by padding with '.'s
            if (test_passed) {
                for (int i = 0; i - 3 < max_name_len - t.name_len; i++) {
                    std::cout << ".";
                }
            }
            std::cout << (test_passed 
                ? " \033[0;32mPass\033[0m" 
                : "\n-- \033[0;31mTEST FAILED\033[0m\n");
        }

        std::cout << "\n\n" << (all_passed 
            ? "\033[0;32mAll tests passed!\033[0m" 
            : "\033[0;31mTests failed.\033[0m") << "\n";
        return all_passed;
    }
};

#endif // EZTEST_H
