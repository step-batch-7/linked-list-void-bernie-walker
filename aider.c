#include "aider.h"

Element generate_int(int value)
{
  Element int_value = malloc(sizeof(int));
  *(int *)int_value = value;
  return int_value;
}

List_ptr get_default_list(int size)
{
  List_ptr list = create_list();

  for (size_t i = 0; i < size; i++)
  {
    add_to_list(list, generate_int(i));
  }

  return list;
}

void destroy_multiple(int size, List_ptr lists[size], ElementProcessor element_destroyer)
{
  for (size_t i = 0; i < size; i++)
  {
    destroy_list(lists[i], element_destroyer);
  }
}