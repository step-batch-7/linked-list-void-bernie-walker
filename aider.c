#include "aider.h"

Element generate_int(int value)
{
  Element int_value = malloc(sizeof(int));
  *(int *)int_value = value;
  return int_value;
}

List_ptr get_default_list(int size, Genearator value_generator)
{
  List_ptr list = create_list();

  for (size_t i = 0; i < size; i++)
  {
    add_to_list(list, value_generator(i));
  }

  return list;
}

Status are_ints_equal(Element int1, Element int2)
{
  return *(int *)int1 == *(int *)int2;
}

void destroy_multiple(int size, List_ptr lists[size], ElementProcessor element_destroyer)
{
  for (size_t i = 0; i < size; i++)
  {
    destroy_list(lists[i], element_destroyer);
  }
}