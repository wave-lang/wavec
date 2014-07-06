/**
 * \file wave_stack.h
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
#ifndef __WAVE_STACK_H__
#define __WAVE_STACK_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
// Enums, Structs, Typedefs.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Wave stack element.
 */
typedef struct wave_stack_element
{
    void * _pointer;                            /**<- . */
    struct wave_stack_element * _next;     /**<- Next element. */
} wave_stack_element;

/**
 * \brief Wave  stack.
 */
typedef struct wave_stack
{
    wave_stack_element * _head;        /**<- Head of the stack. */
    wave_stack_element * _tail;        /**<- Tail of the stack. */
} wave_stack;

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Alloc a wave_stack.
 * \return wave_stack.
 * \relatesalso wave_stack
 */
void * wave_stack_alloc (void);

/**
 * \brief Free a wave_stack.
 * \param s Wave stack.
 * \relatesalso wave_stack
 */
void wave_stack_free (wave_stack * s);

////////////////////////////////////////////////////////////////////////////////
// Push back your lolly Pop.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Pop.
 * \param s Wave  stack.
 * \return wave.
 * \relatesalso wave_stack
 * \warning \c s must be not \c NULL.
 */
void * wave_stack_pop (wave_stack * s);

/**
 * \brief Push.
 * \param s Stack.
 * \param p Pointer.
 * \relatesalso wave_stack
 * \warning \c s must be not \c NULL.
 */
void wave_stack_push (wave_stack * s, void * p);

////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Head.
 * \param s Stack.
 * \return pointer.
 * \relatesalso wave_stack
 * \warning \c s must be not \c NULL.
 */
void * wave_stack_head (const wave_stack * s);

/**
 * \brief Tail.
 * \param s Stack.
 * \return pointer.
 * \relatesalso wave_stack
 * \warning \c s must be not \c NULL.
 */
void * wave_stack_tail (const wave_stack * s);

/**
 * \brief Determine whether the stack is empty.
 * \param s Stack
 * \retval true if the stack is empty.
 * \retval false otherwise.
 * \relatesalso wave_stack
 * \warning \c s must be not \c NULL.
 */
bool wave_stack_is_empty (const wave_stack * s);

#endif /* __WAVE_STACK_H__ */
