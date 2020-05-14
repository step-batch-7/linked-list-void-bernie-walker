#include <stdio.h>
#include "test.h"
#include "../linkedlist.h"

void test_add_to_list(void)
{
  int *num1 = malloc(sizeof(int));
  int *num2 = malloc(sizeof(int));
  *num1 = 8;
  *num2 = 6;
  List_ptr list = create_list();
  assert_strict_equal("should successfully add the given element", add_to_list(list, num1), Success);
  assert_strict_equal("should add to the ending of the list", *(int *)list->last->element, 8);
  assert_strict_equal("added element should also be the first element when the list was empty", *(int *)list->first->element, 8);
  add_to_list(list, num2);
  assert_strict_equal("should only add to the ending of the list", *(int *)list->last->element, 6);
  assert_strict_equal("should update the count of the list", list->length, 2);
  destroy_list(list, free);
}

void test_add_to_start(void)
{
  int *num1 = malloc(sizeof(int));
  int *num2 = malloc(sizeof(int));
  *num1 = 9;
  *num2 = 7;
  List_ptr list = create_list();
  assert_strict_equal("should successfully add the given element", add_to_start(list, num1), Success);
  assert_strict_equal("should add to the starting of the list", *(int *)list->first->element, 9);
  assert_strict_equal("added element should also be the last element when the list was empty", *(int *)list->last->element, 9);
  add_to_start(list, num2);
  assert_strict_equal("should only add to the starting of the list", *(int *)list->first->element, 7);
  assert_strict_equal("should update the count of the list", list->length, 2);
  destroy_list(list, free);
}

void test_create_list(void)
{
  List_ptr list = create_list();
  assert_strict_equal("should create a list with length 0", list->length, 0);
  Status are_both_anchors_null = ((int)list->first & (int)list->last) == (int)NULL;
  assert_strict_equal("should create a list with first and last pointing to null", are_both_anchors_null, Success);
  destroy_list(list, free);
}

int main(void)
{
  exec_test_suite("create_list", test_create_list);
  exec_test_suite("add_to_start", test_add_to_start);
  exec_test_suite("add_to_list", test_add_to_list);
  print_report();
  return 0;
}
