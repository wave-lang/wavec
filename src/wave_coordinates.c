/**
 * \file wave_coordinates.c
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
#include "wave_coordinates.h"

/**
 * \brief Arbitrary default size step for coordinates lists.
 */
static const int _WAVE_COORDINATES_SIZE_STEP = 8;

////////////////////////////////////////////////////////////////////////////////
// Initialization and cleaning.
////////////////////////////////////////////////////////////////////////////////

void wave_coordinates_init (wave_coordinates * const c)
{
    c->_max_depth = -1;
    c->_list_size = _WAVE_COORDINATES_SIZE_STEP;
    c->_coordinates = malloc (c->_list_size * sizeof * c->_coordinates);
}

void wave_coordinates_clean (wave_coordinates * const c)
{
    free (c->_coordinates);
}

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

int wave_coordinates_get_index_at_depth (const wave_coordinates * c, int depth)
{
    return c->_coordinates[depth];
}

int wave_coordinates_get_max_depth (const wave_coordinates * c)
{
    return c->_max_depth;
}

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

static inline void _wave_coordinates_correct_depth (wave_coordinates * const c, int depth)
{
    if (depth > c->_max_depth)
        c->_max_depth = depth;
}

void wave_coordinates_set_index_at_depth (wave_coordinates * const c, int depth, int i)
{
    if (depth < c->_list_size)
        c->_coordinates[depth] = i;
    else
    {
        int new_size = ((depth / _WAVE_COORDINATES_SIZE_STEP) + 1) * _WAVE_COORDINATES_SIZE_STEP;
        int * new_coordinates = realloc (c->_coordinates, new_size * sizeof * new_coordinates);
        if (new_coordinates != NULL)
        {
            c->_coordinates = new_coordinates;
            c->_coordinates[depth] = i;
            c->_list_size = new_size;
        }
    }

    _wave_coordinates_correct_depth (c, depth);
}

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////

void wave_coordinates_fprint (FILE * stream, const wave_coordinates * c)
{
    int max_depth = wave_coordinates_get_max_depth (c);
    for (int i = 0; i < max_depth; ++i)
        fprintf (stream, "%d ", i);
}

void wave_coordinates_print (const wave_coordinates * c)
{
    wave_coordinates_fprint (stdout, c);
}
