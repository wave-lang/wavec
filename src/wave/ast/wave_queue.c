/**
 * \file wave_queue.c
 * \brief Wave queue.
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
#include "wave/ast/wave_queue.h"

static wave_queue_element * wave_queue_element_alloc (void)
{
    wave_queue_element * e = malloc (sizeof * e);
    if (e == NULL)
        perror ("malloc");
    else
        * e = (wave_queue_element) { ._pointer = NULL, ._next = NULL, };
    return e;
}

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

void * wave_queue_alloc (void)
{
    wave_queue * queue = malloc (sizeof * queue);
    if (queue == NULL)
        perror ("malloc");
    else
        * queue = (wave_queue) { ._head = NULL, ._tail = NULL, };

    return queue;
}

void wave_queue_free (wave_queue * q)
{
    if (q != NULL)
    {
        wave_queue_element * e = q->_head;
        while (e != NULL)
        {
            wave_queue_element * next = e->_next;
            free (e);
            e = next;
        }
        free (q);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Push back your lolly Pop.
////////////////////////////////////////////////////////////////////////////////

void * wave_queue_pop (wave_queue * const q)
{
    wave_queue_element * old_head = q->_head;
    void * pointer = old_head->_pointer;
    q->_head = old_head->_next;
    if (q->_head == NULL)
        q->_tail = NULL;
    free (old_head);
    return pointer;
}

void wave_queue_push (wave_queue * const q, void * const p)
{
    wave_queue_element * e = wave_queue_element_alloc ();
    e->_pointer = p;
    if (q->_tail != NULL)
        q->_tail->_next = e;
    else
    {
        q->_head = e;
        q->_tail = e;
    }
    q->_tail = e;
}

////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////

void * wave_queue_head (const wave_queue * const q)
{
    return q->_head == NULL ? NULL : q->_head->_pointer;
}

void * wave_queue_tail (const wave_queue * const q)
{
    return q->_tail == NULL ? NULL : q->_tail->_pointer;
}

bool wave_queue_is_empty (const wave_queue * const q)
{
    return q->_head == NULL;
}
