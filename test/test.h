#include <stdio.h>

#ifndef __TEST_C_
#define __TEST_C_

typedef enum
{
  Passed,
  Failed
} Test_status;

void print_description(char[]);

void show_test_values(int, int);

void print_test_status(char[], Test_status);

void assert_strict_equal(char[], int, int);

void exec_test_suite(char[], void (*)(void));

void print_report(void);

#endif // !__TEST_C_