/**
 * \file wave_coordinates.h
 * \brief Wave coordinates.
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
#ifndef __WAVE_COORDINATES_H__
#define __WAVE_COORDINATES_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
// Enums, Structs, Typedefs, Constants.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Wave coordinates.
 */
typedef struct wave_coordinates
{
    int _max_depth;             /**<- Depth of the coordinates. */
    int _list_size;         /**<- List size. */
    int * _coordinates;     /**<- Coordinates. */

} wave_coordinates;

////////////////////////////////////////////////////////////////////////////////
// Initialization and cleaning.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Initialize wave_coordinates.
 * \param c Coordinates.
 */
void wave_coordinates_init (wave_coordinates * c);

/**
 * \brief Clean wave_coordinates.
 * \param c Coordinates.
 */
void wave_coordinates_clean (wave_coordinates * c);

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Get index at depth.
 * \param c Coordinates.
 * \param depth Depth.
 * \return Index.
 */
int wave_coordinates_get_index_at_depth (const wave_coordinates * c, int depth);

/**
 * \brief Get the max depth.
 * \param c Coordinates
 * \return Max depth.
 */
int wave_coordinates_get_max_depth (const wave_coordinates * c);

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Set an index.
 * \param c Coordinates.
 * \param depth Depth.
 * \param i Index.
 */
void wave_coordinates_set_index_at_depth (wave_coordinates * c, int depth, int i);

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Print wave_coordinates to a stream.
 * \param stream Stream.
 * \param c Coordinates.
 */
void wave_coordinates_fprint (FILE * stream, const wave_coordinates * c);

/**
 * \brief Print wave_coordinates to stdout.
 */
void wave_coordinates_print (const wave_coordinates * c);

#endif /* __WAVE_COORDINATES_H__ */
