#include "test.h"

int passing = 0, failing = 0;

void print_description(char description[])
{
  printf("\n  %s\n\n", description);
}

void show_test_values(int actual, int expected)
{
  printf("\n\t\033[32mExpected: %d\033[0m\t\033[91mActual: %d\033[0m\n\n", expected, actual);
}

void print_test_status(char assertion_message[], Test_status status)
{
  char *mark = status == Passed ? "\033[32m✓\033[0m\033[90m" : "\033[31m✗";
  printf("    %s %s\n\033[0m", mark, assertion_message);
}

void assert_strict_equal(char message[], int actual, int expected)
{
  if (actual == expected)
  {
    print_test_status(message, Passed);
    ++passing;
    return;
  }

  ++failing;
  print_test_status(message, Failed);
  show_test_values(actual, expected);
}

void exec_test_suite(char description[], void (*test_suite)(void))
{
  print_description(description);
  test_suite();
}

void print_report(void)
{
  printf("\n  \033[33mTotal %d\033[0m\n", (passing + failing));
  printf("\n  \033[32m%d passing\033[0m", passing);

  if (failing > 0)
  {
    printf("\t\033[31m%d failing\033[0m", failing);
  }

  printf("\n\n");
}