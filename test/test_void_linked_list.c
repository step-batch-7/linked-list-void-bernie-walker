#include <stdio.h>
#include "test.h"
#include "../linkedlist.h"
#include "../aider.h"

Status are_lists_equal(List_ptr list1, List_ptr list2, Matcher are_elements_equal)
{
  if (list1->length != list2->length)
  {
    return Failure;
  }

  Node_ptr walker1 = list1->first, walker2 = list2->first;
  while ((walker1 != NULL) && (walker2 != NULL))
  {
    if (!are_elements_equal(walker1->element, walker2->element))
    {
      return Failure;
    }
    walker1 = walker1->next;
    walker2 = walker2->next;
  }

  return Success;
}

Status is_list_empty(List_ptr list)
{
  return ((list->first == NULL) && (list->last == NULL)) ? Success : Failure;
}

void test_clear_list(void)
{
  List_ptr list = get_default_list(3, generate_int);
  forEach(list, free);
  assert_strict_equal("Should clear the list", clear_list(list), Success);
  assert_strict_equal("The count should be 0 after clearing the list", list->length, 0);
  assert_strict_equal("Both head and last should be NULL after clearing the list", is_list_empty(list), 1);
  destroy_list(list, free);
}

void test_remove_from_start(void)
{
  List_ptr list = get_default_list(2, generate_int);
  int *removed = remove_from_start(list);

  assert_strict_equal("Should remove from the start of a non empty list", *removed, 0);
  free(removed);
  assert_strict_equal("Should update the head of the list", *(int *)list->first->element, 1);
  assert_strict_equal("Should updated the count of the list", list->length, 1);

  remove_from_start(list);
  assert_strict_equal("Both head and last should be NULL after removal of an only element", is_list_empty(list), Success);

  assert_strict_equal("Should not remove from an empty list", (remove_from_start(list) == NULL), Success);
  destroy_list(list, free);
}

void test_forEach(void)
{
  List_ptr actual = get_default_list(3, generate_int);
  List_ptr expected = get_default_list(3, generate_square);
  forEach(actual, square_int);
  assert_strict_equal("should square the elements of the array", are_lists_equal(actual, expected, are_ints_equal), Success);
}

void test_reverse(void)
{
  List_ptr list = get_default_list(2, generate_int);
  List_ptr reversed1 = reverse(list);
  Status is_reversed = ((reversed1->length == 2) && (*(int *)reversed1->first->element == 1) && (*(int *)reversed1->last->element == 0));
  assert_strict_equal("should reverse the given array", is_reversed, Success);

  clear_list(reversed1);

  List_ptr reversed2 = reverse(reversed1);
  assert_strict_equal("should reverse an empty list", reversed2->length, 0);

  List_ptr lists[] = {list, reversed1, reversed2};
  destroy_multiple(3, lists, free);
}

void test_insert_at(void)
{
  int *num1 = malloc(sizeof(int));
  int *num2 = malloc(sizeof(int));
  int *num3 = malloc(sizeof(int));
  *num1 = 1;
  *num2 = 2;
  *num3 = 3;
  List_ptr list = create_list();
  assert_strict_equal("should add at a valid postion", insert_at(list, num1, 0), Success);
  assert_strict_equal("should add at at the starting of the list", *(int *)list->first->element, 1);
  insert_at(list, num2, 1);
  assert_strict_equal("should add at at the end of the list", *(int *)list->last->element, 2);
  assert_strict_equal("should update the length of the list", list->length, 2);
  insert_at(list, num3, 1);
  assert_strict_equal("should add in the middle of the list", *(int *)list->first->next->element, 3);
  assert_strict_equal("should not add at an invalid postion", insert_at(list, num1, 9), Failure);
  destroy_list(list, free);
}

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
  assert_strict_equal("should update the length of the list", list->length, 2);
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
  assert_strict_equal("should update the length of the list", list->length, 2);
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
  exec_test_suite("insert_at", test_insert_at);
  exec_test_suite("reverse", test_reverse);
  exec_test_suite("forEach", test_forEach);
  exec_test_suite("remove_from_start", test_remove_from_start);
  exec_test_suite("clear_list", test_clear_list);
  print_report();
  return 0;
}
