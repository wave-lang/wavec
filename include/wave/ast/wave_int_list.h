/**
 * \file wave_int_list.h
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
#ifndef __WAVE_INT_LIST_H__
#define __WAVE_INT_LIST_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * \defgroup wave_int_list_group Wave Int List
 * \ingroup wave_collection_info_group
 */

////////////////////////////////////////////////////////////////////////////////
// Enums, Structs, Typedefs.
////////////////////////////////////////////////////////////////////////////////

/**
 * \ingroup wave_int_list_group
 * \brief Wave int list element.
 *
 * wave_int_list_elements are used internally to store elements for
 * wave_int_list.
 *
 * It holds a content and is linked to its predecessor and its successor in
 * the list.
 */
typedef struct wave_int_list_element
{
    int _content;                                       /**<- Content. */
    struct wave_int_list_element * _next_element;       /**<- Next element. */
    struct wave_int_list_element * _previous_element;   /**<- Previous element. */
} wave_int_list_element;

/**
 * \ingroup wave_int_list_group
 * \brief Wave int list.
 *
 * # Wave int list creation and destruction
 * A wave_int_list can be dynamically created using wave_int_list_alloc(). Such
 * lists must be freed using wave_int_list_free(). Lists can also be copied
 * using wave_int_list_copy().
 *
 * # List properties
 * One can test whether a list is empty using wave_int_list_is_empty(), and get
 * the list's size using wave_int_list_size().
 *
 * # Element access
 * One can get the \c Nth element of the list using wave_int_list_at(). It is
 * also possible to get the first or last element while removing it from the
 * list with wave_int_list_pop_front() and wave_int_list_pop_back().
 *
 * # Modification
 * To insert an element into the list, one can use either
 * wave_int_list_push_back(), wave_int_list_push_front() or
 * wave_int_list_insert().
 *
 * # Printing
 * Two functions are available for printing:
 * - wave_int_list_fprint()
 * - wave_int_list_print()
 */
typedef struct wave_int_list
{
    wave_int_list_element * _first;         /**<- First element. */
    wave_int_list_element * _last;          /**<- Last element. */
} wave_int_list;

////////////////////////////////////////////////////////////////////////////////
// Allocation, free, copy.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Allocation for wave_int_list.
 * \return wave_int_list
 * \relatesalso wave_int_list
 */
void * wave_int_list_alloc (void);

/**
 * \brief Free.
 * \param list List.
 * \return wave_int_list
 * \relatesalso wave_int_list
 */
void wave_int_list_free (wave_int_list * list);

/**
 * \brief Copy a wave_int_list.
 * \param list List.
 * \return Copy.
 * \relatesalso wave_int_list
 * \warning \c list must be not \c NULL.
 */
wave_int_list * wave_int_list_copy (const wave_int_list * list);

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Get the element at index \c i.
 * \param list List.
 * \param i Index.
 * \return element.
 * \relatesalso wave_int_list
 * \pre wave_int_list_size() > i.
 * \warning \c list must be not \c NULL.
 */
int wave_int_list_at (const wave_int_list * list, size_t i);

/**
 * \brief Get the list size.
 * \param list List.
 * \return size.
 * \relatesalso wave_int_list
 * \warning \c list must be not \c NULL.
 */
size_t wave_int_list_size (const wave_int_list * list);

/**
 * \brief Check whether a list is empty.
 * \param list List.
 * \retval true if the list is empty.
 * \retval false otherwise.
 * \relatesalso wave_int_list
 * \warning \c list must be not \c NULL.
 */
bool wave_int_list_is_empty (const wave_int_list * list);

////////////////////////////////////////////////////////////////////////////////
// Modifiers.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Pop back.
 * \param list List
 * \return Back element.
 * \relatesalso wave_int_list
 * \warning \c list must be not \c NULL.
 */
int wave_int_list_pop_back (wave_int_list * list);

/**
 * \brief Pop front.
 * \param list List
 * \return Front element.
 * \relatesalso wave_int_list
 * \warning \c list must be not \c NULL.
 */
int wave_int_list_pop_front (wave_int_list * list);

/**
 * \brief Push back.
 * \param list List.
 * \param element Element.
 * \relatesalso wave_int_list
 * \warning \c list must be not \c NULL.
 */
void wave_int_list_push_back (wave_int_list * list, int element);

/**
 * \brief Push back.
 * \param list List.
 * \param element Element.
 * \relatesalso wave_int_list
 * \warning \c list must be not \c NULL.
 */
void wave_int_list_push_front (wave_int_list * list, int element);

/**
 * \brief Insert
 * \param list List.
 * \param i Index.
 * \param element Element.
 * \relatesalso wave_int_list
 * \warning \c list must be not \c NULL.
 */
void wave_int_list_insert (wave_int_list * list, size_t i, int element);

////////////////////////////////////////////////////////////////////////////////
// Printing
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Print a wave_int_list to a stream.
 * \param stream Stream.
 * \param list List.
 * \relatesalso wave_int_list
 * \warning \c list must be not \c NULL.
 */
void wave_int_list_fprint (FILE * stream, const wave_int_list * list);

/**
 * \brief Print a wave_int_list to a stream (code generation version).
 * \param stream Stream.
 * \param list List.
 * \relatesalso wave_int_list
 * \warning \c list must be not \c NULL.
 */
void wave_int_list_code_fprint (FILE * stream, const wave_int_list * list);

/**
 * \brief Print a wave_int_list to stdout.
 * \param list List.
 * \warning \c list must be not \c NULL.
 * \relatesalso wave_int_list
 */
void wave_int_list_print (const wave_int_list * list);

#endif /* __WAVE_INT_LIST_H__ */
