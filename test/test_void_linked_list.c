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

void test_remove_from_end(void)
{
  List_ptr list = get_default_list(2, generate_int);

  int *removed = remove_from_end(list);
  assert_strict_equal("Should remove from the end of a non empty list", *removed, 1);
  assert_strict_equal("Should update the last of the list", *(int *)list->last->element, 0);
  assert_strict_equal("Should updated the length of the list", list->length, 1);
  free(removed);

  removed = remove_from_end(list);
  assert_strict_equal("Both head and last should be NULL after removal of an only element", is_list_empty(list), 1);
  free(removed);

  assert_strict_equal("Should not remove from an empty list", (remove_from_end(list) == NULL), Success);
  destroy_list(list, free);
}

void test_remove_at(void)
{
  List_ptr list = get_default_list(3, generate_int);

  int *removed = remove_at(list, 1);
  assert_strict_equal("Should remove from middle of the list", *removed, 1);
  assert_strict_equal("Should update the length of the list", list->length, 2);
  free(removed);

  removed = remove_at(list, 1);
  assert_strict_equal("Should remove from the end of the list", *removed, 2);
  free(removed);

  removed = remove_at(list, 0);
  assert_strict_equal("Should remove from starting of the list", *removed, 0);
  assert_strict_equal("Both head and last should be NULL after removal of an only element", is_list_empty(list), Success);
  free(removed);

  assert_strict_equal("Should not remove from the list when a wrong position is given", (remove_at(list, 2) == NULL), Success);
  destroy_list(list, free);
}

void test_remove_from_start(void)
{
  List_ptr list = get_default_list(2, generate_int);

  int *removed = remove_from_start(list);
  assert_strict_equal("Should remove from the start of a non empty list", *removed, 0);
  assert_strict_equal("Should update the head of the list", *(int *)list->first->element, 1);
  assert_strict_equal("Should updated the count of the list", list->length, 1);
  free(removed);

  removed = remove_from_start(list);
  assert_strict_equal("Both first and last should be NULL after removal of an only element", is_list_empty(list), Success);
  free(removed);

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

void test_reduce(void)
{
  List_ptr list = get_default_list(4, generate_int);
  Element init = calloc(1, sizeof(int));
  assert_strict_equal("should get the total of elements in the list", *(int *)reduce(list, init, add_two_ints), 6);

  forEach(list, free);
  clear_list(list);
  *(int *)init = 9;
  assert_strict_equal("should return the initial value for an empty list", *(int *)reduce(list, init, add_two_ints), 9);

  destroy_list(list, free);
}

void test_filter(void)
{
  List_ptr list = get_default_list(5, generate_int);
  List_ptr expected = get_default_list(3, generate_even);
  List_ptr actual = filter(list, is_even);

  Status do_arrays_match = are_lists_equal(actual, expected, are_ints_equal);
  assert_strict_equal("should filter only the even numbers in the list", do_arrays_match, Success);

  clear_list(list);
  List_ptr empty_list = filter(list, is_even);
  assert_strict_equal("should filter an empty array", is_list_empty(empty_list), Success);

  List_ptr lists[4] = {list, expected, actual, empty_list};
  destroy_multiple(4, lists, free);
}

void test_map(void)
{
  List_ptr list = get_default_list(3, generate_int);
  List_ptr expected = get_default_list(3, generate_square);
  List_ptr actual = map(list, get_square_of);

  Status do_arrays_match = are_lists_equal(actual, expected, are_ints_equal);
  assert_strict_equal("should square the elements of the list", do_arrays_match, Success);

  clear_list(list);
  List_ptr empty_list = map(list, get_square_of);
  assert_strict_equal("should map an empty array", is_list_empty(empty_list), Success);

  List_ptr lists[4] = {list, expected, actual, empty_list};
  destroy_multiple(4, lists, free);
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

void test_find_element(void)
{
  List_ptr list = get_default_list(3, generate_int);

  int *num = malloc(sizeof(int));
  *num = 9;
  Pair_ptr pair = find_element(list, num, are_ints_equal);
  assert_strict_equal("should return NULL when element is not present", (pair == NULL), Success);

  *num = 1;
  pair = find_element(list, num, are_ints_equal);
  Status is_valid_pair = ((*(int *)pair->current->element == 1) && (*(int *)pair->previous->element == 0));
  assert_strict_equal("should return current previous pair when element is found", is_valid_pair, Success);
  free(pair);

  forEach(list, free);
  clear_list(list);
  pair = find_element(list, num, are_ints_equal);
  assert_strict_equal("should return NULL when list is empty ", (pair == NULL), Success);
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
  exec_test_suite("find_element", test_find_element);
  exec_test_suite("add_to_start", test_add_to_start);
  exec_test_suite("add_to_list", test_add_to_list);
  exec_test_suite("insert_at", test_insert_at);
  exec_test_suite("reverse", test_reverse);
  exec_test_suite("map", test_map);
  exec_test_suite("filter", test_filter);
  exec_test_suite("reduce", test_reduce);
  exec_test_suite("forEach", test_forEach);
  exec_test_suite("remove_from_start", test_remove_from_start);
  exec_test_suite("remove_at", test_remove_at);
  exec_test_suite("remove_from_end", test_remove_from_end);
  exec_test_suite("clear_list", test_clear_list);
  print_report();
  return 0;
}
