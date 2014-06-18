/**
 * \file wave_collection_info.c
 * \brief Wave collection info.
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
#include "wave_collection_info.h"

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

void * wave_collection_info_alloc (void)
{
    wave_collection_info * i = malloc (sizeof * i);
    if (i != NULL)
        * i = (wave_collection_info) { ._index = 0, ._coordinate = NULL, ._length = NULL, };
    return i;
}

void wave_collection_info_free (wave_collection_info * info)
{
    if (info != NULL)
    {
        wave_coordinate_free (info->_coordinate);
        wave_coordinate_free (info->_length);
        free (info);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

int wave_collection_info_get_index (const wave_collection_info * info)
{
    return info->_index;
}

wave_coordinate * wave_collection_info_get_coordinate (const wave_collection_info * info)
{
    return info->_coordinate;
}

wave_coordinate * wave_collection_info_get_length (const wave_collection_info * info)
{
    return info->_length;
}

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

void wave_collection_info_set_index (wave_collection_info * info, int i)
{
    info->_index = i;
}

void wave_collection_info_set_coordinate (wave_collection_info * info, wave_coordinate * c)
{
    info->_coordinate = c;
}

void wave_collection_info_set_length (wave_collection_info * info, wave_coordinate * l)
{
    info->_length = l;
}

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////

void wave_collection_info_fprint (FILE * stream, const wave_collection_info * i)
{
    fprintf (stream, "index: %d, coord: ", i->_index);
    wave_coordinate_fprint (stream, i->_coordinate);
    fprintf (stream, ", length: ");
    wave_coordinate_fprint (stream, i->_length);
}

void wave_collection_info_print (const wave_collection_info * i)
{
    wave_collection_info_fprint (stdout, i);
}
