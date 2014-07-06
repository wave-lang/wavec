/**
 * \file wave_queue.h
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
#ifndef __WAVE_QUEUE_H__
#define __WAVE_QUEUE_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
// Enums, Structs, Typedefs.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Wave queue element.
 */
typedef struct wave_queue_element
{
    void * _pointer;                       /**<- Pointer. */
    struct wave_queue_element * _next;     /**<- Next element. */
} wave_queue_element;

/**
 * \brief Wave queue.
 */
typedef struct wave_queue
{
    wave_queue_element * _head;        /**<- Head of the queue. */
    wave_queue_element * _tail;        /**<- Tail of the queue. */
} wave_queue;

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Allocate a wave_queue.
 * \return wave_queue.
 * \relatesalso wave_queue
 */
void * wave_queue_alloc (void);

/**
 * \brief Free a wave_queue.
 * \param s Wave stack.
 * \relatesalso wave_queue
 */
void wave_queue_free (wave_queue * s);

////////////////////////////////////////////////////////////////////////////////
// Push back your lolly Pop.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Pop.
 * \param q Wave queue.
 * \return Pointer.
 * \relatesalso wave_queue
 * \warning \c q must be not \c NULL.
 */
void * wave_queue_pop (wave_queue * q);

/**
 * \brief Push.
 * \param q Queue
 * \param p Pointer.
 * \relatesalso wave_queue
 * \warning \c q must be not \c NULL.
 */
void wave_queue_push (wave_queue * q, void * p);

////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Head.
 * \param q Queue.
 * \return pointer.
 * \relatesalso wave_queue
 * \warning \c q must be not \c NULL.
 */
void * wave_queue_head (const wave_queue * q);

/**
 * \brief Tail.
 * \param q Queue.
 * \return pointer.
 * \relatesalso wave_queue
 * \warning \c q must be not \c NULL.
 */
void * wave_queue_tail (const wave_queue * q);

/**
 * \brief Determine whether the queue is empty.
 * \param q Queue.
 * \retval true if the stack is empty.
 * \retval false otherwise.
 * \relatesalso wave_queue
 * \warning \c q must be not \c NULL.
 */
bool wave_queue_is_empty (const wave_queue * q);

#endif /* __wave_queue_H__ */
