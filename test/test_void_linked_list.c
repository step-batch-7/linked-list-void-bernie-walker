#include <stdio.h>
#include "test.h"
#include "../linkedlist.h"

void test_create_list(void)
{
  List_ptr list = create_list();
  assert_strict_equal("Should create a list with length 0", list->length, 0);
  Status are_both_anchors_null = ((int)list->first & (int)list->last) == (int)NULL;
  assert_strict_equal("Should create a list with first and last pointing to null", are_both_anchors_null, Success);
}

int main(void)
{
  exec_test_suite("create_list", test_create_list);
  print_report();
  return 0;
}