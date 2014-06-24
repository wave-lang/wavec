/**
 * \file wave_path_stack.h
 * \brief Wave path stack.
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
#ifndef __WAVE_PATH_STACK_H__
#define __WAVE_PATH_STACK_H__

#include <stdblib.h>
#include <stdio.h>
#include <stdbool.h>

#include "wave/ast/wave_path.h"

////////////////////////////////////////////////////////////////////////////////
// Enums, Structs, Typedefs.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Wave path stack element.
 */
typedef struct wave_path_stack_element
{
    wave_path * _path;                          /**<- Path. */
    struct wave_path_stack_element * _next;     /**<- Next element. */
} wave_path_stack_element;

/**
 * \brief Wave path stack.
 */
typedef struct wave_path_stack
{
    wave_path_stack_element * _head;        /**<- Head of the stack. */
    wave_path_stack_element * _tail;        /**<- Tail of the stack. */
} wave_path_stack;

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Alloc a wave_path_stack.
 * \return wave_path_stack.
 * \relatesalso wave_path_stack
 */
void * wave_path_stack_alloc (void);

/**
 * \brief Free a wave_path_stack.
 * \param s Wave path stack.
 * \relatesalso wave_path_stack
 */
void * wave_path_stack_free (wave_path_stack * s);

////////////////////////////////////////////////////////////////////////////////
// Push back your lolly Pop.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Pop.
 * \param s Wave path stack.
 * \return wave_path.
 * \relatesalso wave_path_stack
 * \warning \c s must be not \c NULL.
 */
wave_path * wave_path_stack_pop (wave_path_stack * s);

/**
 * \brief Push.
 * \param s Stack.
 * \param p Path.
 * \relatesalso wave_path_stack
 * \warning \c s must be not \c NULL.
 */
void wave_path_stack_push (wave_path_stack * s, wave_path * p);

////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Head.
 * \param s Stack.
 * \return wave_path
 * \relatesalso wave_path_stack.
 * \warning \c s must be not \c NULL.
 */
wave_path * wave_path_stack_head (const wave_path_stack * s);

/**
 * \brief Tail.
 * \param s Stack.
 * \return wave_path
 * \relatesalso wave_path_stack.
 * \warning \c s must be not \c NULL.
 */
wave_path * wave_path_stack_tail (const wave_path_stack * s);

/**
 * \brief Determine whether the stack is empty.
 * \param s Stack
 * \retval true if the stack is empty.
 * \retval false otherwise.
 * \relatesalso wave_path_stack.
 * \warning \c s must be not \c NULL.
 */
bool wave_path_stack_is_empty (const wave_path_stack * s);

#endif /* __WAVE_PATH_STACK_H__ */
