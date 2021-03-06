/**
 * \file wave_collection_info.h
 * \brief Wave collection info.
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
#ifndef __WAVE_COLLECTION_INFO_H
#define __WAVE_COLLECTION_INFO_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "wave/ast/wave_int_list.h"
#include "wave/ast/wave_coordinate.h"

/**
 * \defgroup wave_collection_info_group Wave Collection Info
 * \ingroup wave_collection_group
 */

////////////////////////////////////////////////////////////////////////////////
// Enums, Structs, Typedefs.
////////////////////////////////////////////////////////////////////////////////

/**
 * \ingroup wave_collection_info_group
 * \brief Wave collection info.
 *
 * Collection info are used to annotate the nodes of the AST.
 *
 * # Collection info creation and destruction
 * A collection info can be dynamically created using wave_collection_info_alloc()
 * and must be destroyed with wave_collection_info_free().
 *
 * # Content access
 * - wave_collection_info_get_index()
 * - wave_collection_info_get_coordinate()
 * - wave_collection_info_get_length()
 *
 * # Content modification
 * - wave_collection_info_set_index()
 * - wave_collection_info_set_coordinate()
 * - wave_collection_info_set_length()
 */
typedef struct wave_collection_info
{
    int _index;                         /**<- Index. */
    wave_coordinate * _coordinate;      /**<- Coordinate. */
    wave_coordinate * _length;          /**<- Length. */
} wave_collection_info;

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Allocation for wave_collection_info.
 * \return Pointer to a wave_collection_info.
 * \relatesalso wave_collection_info
 */
void * wave_collection_info_alloc (void);

/**
 * \brief Free a wave_collection_info.
 * \param info Info.
 * \relatesalso wave_collection_info
 */
void wave_collection_info_free (wave_collection_info * info);

/**
 * \brief Copy a wave_collection_info.
 * \param info Info.
 * \return Copy.
 * \relatesalso wave_collection_info
 */
void * wave_collection_info_copy (const wave_collection_info * info);

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Get the index.
 * \param info Info.
 * \return Index.
 * \relatesalso wave_collection_info
 */
int wave_collection_info_get_index (const wave_collection_info * info);

/**
 * \brief Get the coordinate.
 * \param info Info.
 * \return Coordinate.
 * \relatesalso wave_collection_info
 */
wave_coordinate * wave_collection_info_get_coordinate (const wave_collection_info * info);

/**
 * \brief Get the length.
 * \param info Info.
 * \return Length.
 * \relatesalso wave_collection_info
 */
wave_coordinate * wave_collection_info_get_length (const wave_collection_info * info);

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Set the index.
 * \param info Info.
 * \param i Index.
 * \relatesalso wave_collection_info
 */
void wave_collection_info_set_index (wave_collection_info * info, int i);

/**
 * \brief Set the coordinate.
 * \param info Info.
 * \param c Coordinate.
 * \relatesalso wave_collection_info
 */
void wave_collection_info_set_coordinate (wave_collection_info * info, wave_coordinate * c);

/**
 * \brief Set the length.
 * \param info Info.
 * \param l Length.
 * \relatesalso wave_collection_info
 */
void wave_collection_info_set_length (wave_collection_info * info, wave_coordinate * l);

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Print wave_collection_info to a stream.
 * \param stream Stream.
 * \param i Info.
 */
void wave_collection_info_fprint (FILE * stream, const wave_collection_info * i);

/**
 * \brief Print wave_collection_info.
 * \param i Info.
 */
void wave_collection_info_print (const wave_collection_info * i);

#endif /* __WAVE_COLLECTION_INFO_H */
