#include "linkedlist.h"

#ifndef __AIDER_H_
#define __AIDER_H_

typedef Element (*Genearator)(int);

Element generate_0(int);

Element generate_even(int);

Element generate_int(int);

Element generate_square(int);

Element get_square_of(Element);

List_ptr get_default_list(int, Genearator);

void square_int(Element);

Status is_even(Element);

Status are_ints_equal(Element, Element);

Element add_two_ints(Element, Element);

void destroy_multiple(int, List_ptr[], ElementProcessor);

#endif // !__AIDER_H_
