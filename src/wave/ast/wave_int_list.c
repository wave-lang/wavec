/**
 * \file wave_int_list.c
 * \brief Wave int list.
 * \author RAZANAJATO RANAIVOARIVONY Harenome
 * \author SCHMITT Maxime
 * \date 2014
 * \copyright MIT License
 */
/* The MIT License (MIT)
 *
 * Copyright (c) 2014 Éric VIOLARD, Maxime SCHMITT, Harenome RAZANAJATO RANAIVOARIVONY
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "wave/ast/wave_int_list.h"

////////////////////////////////////////////////////////////////////////////////
// Allocation, free, copy.
////////////////////////////////////////////////////////////////////////////////

void * wave_int_list_alloc (void)
{
    wave_int_list * list = malloc (sizeof * list);
    if (list != NULL)
        * list = (wave_int_list) { ._first = NULL, ._last = NULL, };

    return list;
}

void wave_int_list_free (wave_int_list * list)
{
    if (list != NULL)
    {
        wave_int_list_element * current = list->_first;
        while (current != NULL)
        {
            wave_int_list_element * next = current->_next_element;
            free (current);
            current = next;
        }
        free (list);
    }
}

wave_int_list * wave_int_list_copy (const wave_int_list * list)
{
    wave_int_list * l = wave_int_list_alloc ();
    for (wave_int_list_element * current = list->_first; current != NULL; current = current->_next_element)
        wave_int_list_push_back (l, current->_content);

    return l;
}

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

int wave_int_list_at (const wave_int_list * list, size_t i)
{
    wave_int_list_element * current = list->_first;
    for (size_t j = 0; j < i ; ++j)
        current = current->_next_element;
    return current->_content;
}

size_t wave_int_list_size (const wave_int_list * list)
{
    size_t size = 0;
    if (list != NULL)
        for (wave_int_list_element * current = list->_first; current != NULL; current = current->_next_element)
            size++;

    return size;
}

bool wave_int_list_is_empty (const wave_int_list * list)
{
    return list->_first == NULL;
}

////////////////////////////////////////////////////////////////////////////////
// Modifiers.
////////////////////////////////////////////////////////////////////////////////

int wave_int_list_pop_back (wave_int_list * list)
{
    int element = list->_last->_content;

    wave_int_list_element * last = list->_last;
    list->_last = last->_previous_element;
    if (list->_last != NULL)
        list->_last->_next_element = NULL;
    else
        list->_first = NULL;
    free (last);

    return element;
}

int wave_int_list_pop_front (wave_int_list * list)
{
    int element = list->_first->_content;

    wave_int_list_element * first = list->_first;
    list->_first = first->_next_element;
    if (list->_first != NULL)
        list->_first->_previous_element = NULL;
    else
        list->_last = NULL;
    free (first);

    return element;
}

static inline void * _wave_int_list_element_alloc (int element)
{
    wave_int_list_element * e = malloc (sizeof * e);
    if (e != NULL)
        * e = (wave_int_list_element)
        {
            ._content = element,
            ._next_element = NULL,
            ._previous_element = NULL,
        };

    return e;
}

void wave_int_list_push_back (wave_int_list * list, int element)
{
    wave_int_list_element * e = _wave_int_list_element_alloc (element);
    if (list->_last != NULL)
    {
        e->_previous_element = list->_last;
        list->_last->_next_element  = e;
        list->_last = e;
    }
    else
    {
        list->_first = e;
        list->_last = e;
    }
}

void wave_int_list_push_front (wave_int_list * list, int element)
{
    wave_int_list_element * e = _wave_int_list_element_alloc (element);
    if (list->_first != NULL)
    {
        e->_next_element = list->_first;
        list->_first->_previous_element  = e;
        list->_first = e;
    }
    else
    {
        list->_first = e;
        list->_last = e;
    }
}

void wave_int_list_insert (wave_int_list * list, size_t i, int element)
{
    if (i == 0 || list->_first == NULL)
        wave_int_list_push_front (list, element);
    else
    {
        wave_int_list_element * place = list->_first;
        size_t j = 0;
        for (j = 0; j < i && place->_next_element != NULL;++j)
            place = place->_next_element;

        if (j == i)
        {
            wave_int_list_element * e = _wave_int_list_element_alloc (element);
            e->_previous_element = place->_previous_element;
            place->_previous_element->_next_element = e;
            e->_next_element = place;
            place->_previous_element = e;
        }
        else
            wave_int_list_push_back (list, element);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Printing
////////////////////////////////////////////////////////////////////////////////

void wave_int_list_fprint (FILE * stream, const wave_int_list * list)
{
    for (wave_int_list_element * e = list->_first; e != NULL; e = e->_next_element)
        fprintf (stream, "%d ", e->_content);
}

void wave_int_list_code_fprint (FILE * stream, const wave_int_list * list)
{
    for (wave_int_list_element * e = list->_first; e != NULL; e = e->_next_element)
        fprintf (stream, "_%d", e->_content);
}

void wave_int_list_print (const wave_int_list * list)
{
    wave_int_list_fprint (stdout, list);
}
