/**
 * \file wave_length.c
 * \brief Wave length.
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
#include "wave_length.h"

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

void * wave_length_alloc (void)
{
    wave_length * l = malloc (sizeof * l);
    if (l != NULL)
        * l = (wave_length) { ._type = WAVE_LENGTH_UNKNOWN, ._content._constant = 0, };
    return l;
}

void wave_length_free (wave_length * l)
{
    if (l != NULL)
    {
        if (l->_type == WAVE_LENGTH_VAR)
            wave_int_list_free (l->_content._var);
        free (l);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

wave_length_type wave_length_get_type (const wave_length * l)
{
    return l->_type;
}

int wave_length_get_constant (const wave_length * l)
{
    return l->_content._constant;
}

wave_int_list * wave_length_get_list (const wave_length * l)
{
    return l->_content._var;
}

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

static inline void _wave_length_set_type (wave_length * l, wave_length_type t)
{
    l->_type = t;
}

void wave_length_set_constant (wave_length * l, int c)
{
    _wave_length_set_type (l, WAVE_LENGTH_CONSTANT);
    l->_content._constant = c;
}

void wave_length_set_list (wave_length * l, wave_int_list * list)
{
    _wave_length_set_type (l, WAVE_LENGTH_VAR);
    l->_content._var = list;
}

