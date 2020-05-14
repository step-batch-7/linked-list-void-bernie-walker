#include "linkedlist.h"

#ifndef __AIDER_H_
#define __AIDER_H_

typedef Element (*Genearator)(int);

Element generate_int(int);

List_ptr get_default_list(int, Genearator);

Status are_ints_equal(Element, Element);

void destroy_multiple(int, List_ptr[], ElementProcessor);

#endif // !__AIDER_H_
