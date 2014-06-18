/**
 * \file wave_path_stack.c
 * \brief Wave path stack.
 * \author RAZANAJATO RANAIVOARIVONY Harenome
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
#include "wave_path_stack.h"

static wave_path_stack_element * wave_path_stack_element_alloc (void)
{
    wave_path_stack_element * e = malloc (sizeof * e);
    if (e == NULL)
        perror ("malloc");
    else
        * e = (wave_path_stack_element) { ._path = NULL, ._next = NULL };
    return e;
}

static wave_path_stack_element * wave_path_stack_element_free (wave_path_stack_element * e)
{
    if (e != NULL)
    {
        free (e);
        e = NULL;
    }
    return NULL;
}
static wave_path_stack_element * wave_path_stack_element_get_path (const wave_path_stack_element * e)
{
    return e->_path;
}

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

void * wave_path_stack_alloc (void)
{
    wave_path_stack * stack = malloc (sizeof * stack);
    if (stack == NULL)
        perror ("malloc");
    else
        * stack = (wave_path_stack) { ._head = NULL; ._tail = NULL };

    return stack;
}

void * wave_path_stack_free (wave_path_stack * s)
{
    if (s != NULL)
    {
        free (s);
        s = NULL;
    }

    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// Push back your lolly Pop.
////////////////////////////////////////////////////////////////////////////////

wave_path * wave_path_stack_pop (wave_path_stack * s)
{
    wave_path * p = s->_head->_path;
    s->_head = s->_head->_next;
    return p;
}

void wave_path_stack_push (wave_path_stack * s, wave_path * p)
{
    wave_path_stack_element * e = wave_path_stack_element_alloc ();
    e->_path = p;
    s->_tail->_next = e;
    s->_tail = e;
}

////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////

wave_path * wave_path_stack_head (const wave_path_stack * const s)
{
    return s->_head == NULL ? NULL : s->_head->_path;
}

wave_path * wave_path_stack_tail (const wave_path_stack * const s)
{
    return s->_tail == NULL ? NULL : s->_tail->_path;
}

bool wave_path_stack_is_empty (const wave_path_stack * const s)
{
    return s->head == NULL;
}

