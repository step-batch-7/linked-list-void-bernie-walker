#include "linkedlist.h"

Node_ptr create_node(Element element)
{
  Node_ptr node = malloc(sizeof(Node));

  if (node == NULL)
  {
    return node;
  }

  node->element = element;
  node->next = NULL;
  return node;
}

List_ptr create_list(void)
{
  List_ptr list = malloc(sizeof(LinkedList));
  list->first = NULL;
  list->last = NULL;
  list->length = 0;
  return list;
}

Status add_to_start(List_ptr list, Element element)
{
  Node_ptr new_node = create_node(element);

  if (new_node == NULL)
  {
    return Failure;
  }

  new_node->next = list->first;
  list->first = new_node;
  ++list->length;

  if (list->last == NULL)
  {
    list->last = list->first;
  }

  return Success;
}

Status add_to_list(List_ptr list, Element element)
{
  if (list->first == NULL)
  {
    return add_to_start(list, element);
  }

  Node_ptr new_node = create_node(element);

  if (new_node == NULL)
  {
    return Failure;
  }

  list->last->next = new_node;
  list->last = new_node;
  ++list->length;
  return Success;
}

void destroy_list(List_ptr list, ElementProcessor element_destroyer)
{
  Node_ptr walker = list->first;

  while (walker != NULL)
  {
    Node_ptr temp = walker;
    walker = walker->next;
    element_destroyer(temp->element);
    free(temp);
  }

  free(list);
}