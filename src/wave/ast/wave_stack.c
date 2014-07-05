/**
 * \file wave_stack.c
 * \brief Wave stack.
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
#include "wave/ast/wave_stack.h"

static wave_stack_element * wave_stack_element_alloc (void)
{
    wave_stack_element * e = malloc (sizeof * e);
    if (e == NULL)
        perror ("malloc");
    else
        * e = (wave_stack_element) { ._pointer = NULL, ._next = NULL, };
    return e;
}

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

void * wave_stack_alloc (void)
{
    wave_stack * stack = malloc (sizeof * stack);
    if (stack == NULL)
        perror ("malloc");
    else
        * stack = (wave_stack) { ._head = NULL, ._tail = NULL, };

    return stack;
}

void wave_stack_free (wave_stack * s)
{
    if (s != NULL)
    {
        wave_stack_element * e = s->_head;
        while (e != NULL)
        {
            wave_stack_element * next = e->_next;
            free (e);
            e = next;
        }
        free (s);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Push back your lolly Pop.
////////////////////////////////////////////////////////////////////////////////

void * wave_stack_pop (wave_stack * s)
{
    wave_stack_element * old_head = s->_head;
    void * pointer = old_head->_pointer;
    s->_head = old_head->_next;
    if (s->_head == NULL)
        s->_tail = NULL;
    free (old_head);
    return pointer;
}

void wave_stack_push (wave_stack * s, void * p)
{
    wave_stack_element * e = wave_stack_element_alloc ();
    e->_pointer = p;
    if (s->_tail != NULL)
        s->_tail->_next = e;
    else
    {
        s->_head = e;
        s->_tail = e;
    }
    s->_tail = e;
}

////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////

void * wave_stack_head (const wave_stack * const s)
{
    return s->_head == NULL ? NULL : s->_head->_pointer;
}

void * wave_stack_tail (const wave_stack * const s)
{
    return s->_tail == NULL ? NULL : s->_tail->_pointer;
}

bool wave_stack_is_empty (const wave_stack * const s)
{
    return s->_head == NULL;
}
