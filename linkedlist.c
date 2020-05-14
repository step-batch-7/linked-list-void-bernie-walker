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

Node_ptr get_nth_node(List_ptr list, int n)
{
  if ((n < 0) || (n >= list->length))
  {
    return NULL;
  }

  Node_ptr walker = list->first;
  int index = 0;

  while ((walker != NULL) && (index != n))
  {
    walker = walker->next;
    ++index;
  }

  return walker;
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

Status insert_at(List_ptr list, Element element, int position)
{

  if (position == 0)
  {
    return add_to_start(list, element);
  }

  if (position == list->length)
  {
    return add_to_list(list, element);
  }

  Node_ptr node_before_position = get_nth_node(list, (position - 1));
  if (node_before_position == NULL)
  {
    return Failure;
  }

  Node_ptr new_node = create_node(element);
  new_node->next = node_before_position->next;
  node_before_position->next = new_node;
  ++list->length;

  return Success;
}

List_ptr reverse(List_ptr list)
{
  List_ptr reversed = create_list();
  Node_ptr walker = list->first;

  while (walker != NULL)
  {
    add_to_start(reversed, walker->element);
    walker = walker->next;
  }

  return reversed;
}

List_ptr map(List_ptr list, Mapper mapper)
{
  List_ptr result = create_list();
  Node_ptr walker = list->first;

  while (walker != NULL)
  {
    add_to_list(result, mapper(walker->element));
    walker = walker->next;
  }

  return result;
}

List_ptr filter(List_ptr list, Predicate predicate)
{
  List_ptr result = create_list();
  Node_ptr walker = list->first;

  while (walker != NULL)
  {
    if (predicate(walker->element))
    {
      add_to_list(result, walker->element);
    }
    walker = walker->next;
  }

  return result;
}

Element reduce(List_ptr list, Element init, Reducer reducer)
{
  Node_ptr walker = list->first;

  while (walker != NULL)
  {
    init = reducer(init, walker->element);
    walker = walker->next;
  }

  return init;
}

void forEach(List_ptr list, ElementProcessor process_element)
{
  Node_ptr walker = list->first;
  while (walker != NULL)
  {
    process_element(walker->element);
    walker = walker->next;
  }
}

Element remove_from_start(List_ptr list)
{
  if (list->first == NULL)
  {
    return NULL;
  }

  Node_ptr node_to_remove = list->first;
  list->first = node_to_remove->next;
  Element removed_element = node_to_remove->element;

  free(node_to_remove);
  --list->length;

  if (list->first == NULL)
  {
    list->last = NULL;
  }

  return removed_element;
}

Element remove_at(List_ptr list, int position)
{
  if (position == 0)
  {
    return remove_from_start(list);
  }

  Node_ptr node_before_position = get_nth_node(list, (position - 1));

  if (node_before_position == NULL)
  {
    return NULL;
  }

  Node_ptr node_to_remove = node_before_position->next;
  node_before_position->next = node_to_remove->next;
  Element removed_element = node_to_remove->element;

  free(node_to_remove);
  --list->length;

  if (list->length == position)
  {
    list->last = node_before_position;
  }

  return removed_element;
}

Element remove_from_end(List_ptr list)
{
  return remove_at(list, list->length - 1);
}

Status clear_list(List_ptr list)
{
  Node_ptr walker = list->first;

  while (walker != NULL)
  {
    Node_ptr temp = walker->next;
    free(walker);
    walker = temp;
  }

  list->first = NULL;
  list->last = NULL;
  list->length = 0;
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