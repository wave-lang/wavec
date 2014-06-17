/**
 * \file wave_coordinate.c
 * \brief Wave coordinate
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
#include "wave_coordinate.h"

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

void * wave_coordinate_alloc (void)
{
    wave_coordinate * c = malloc (sizeof * c);
    if (c != NULL)
        * c = (wave_coordinate)
        {
            ._type = WAVE_COORD_UNKNOWN,
            ._content._binary._left = NULL,
            ._content._binary._right = NULL,
        };

    return c;
}

void wave_coordinate_free (wave_coordinate * c)
{
    if (c != NULL)
    {
        if (c->_type == WAVE_COORD_PLUS || c->_type == WAVE_COORD_TIMES)
        {
            wave_coordinate_free (c->_content._binary._left);
            wave_coordinate_free (c->_content._binary._right);
        }
        else if (c->_type == WAVE_COORD_VAR)
        {
            wave_int_list_free (c->_content._var);
        }
        free (c);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

wave_coordinate_type wave_coordinate_get_type (const wave_coordinate * c)
{
    return c->_type;
}

wave_int_list * wave_coordinate_get_list (const wave_coordinate * c)
{
    return c->_content._var;
}

int wave_coordinate_get_constant (const wave_coordinate * c)
{
    return c->_content._constant;
}

wave_coordinate * wave_coordinate_get_left (const wave_coordinate * c)
{
    return c->_content._binary._left;
}

wave_coordinate * wave_coordinate_get_right (const wave_coordinate * c)
{
    return c->_content._binary._right;
}

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

static inline void _wave_coordinate_set_type (wave_coordinate * c, wave_coordinate_type t)
{
    c->_type = t;
}

void wave_coordinate_set_constant (wave_coordinate * c, int constant)
{
    _wave_coordinate_set_type (c, WAVE_COORD_CONSTANT);
    c->_content._constant = constant;
}

void wave_coordinate_set_list (wave_coordinate * c, wave_int_list * list)
{
    _wave_coordinate_set_type (c, WAVE_COORD_VAR);
    c->_content._var = list;
}

void wave_coordinate_set_plus_left (wave_coordinate * c, wave_coordinate * left)
{
    _wave_coordinate_set_type (c, WAVE_COORD_PLUS);
    c->_content._binary._left = left;
}

void wave_coordinate_set_plus_right (wave_coordinate * c, wave_coordinate * right)
{
    _wave_coordinate_set_type (c, WAVE_COORD_PLUS);
    c->_content._binary._right = right;
}

void wave_coordinate_set_times_left (wave_coordinate * c, wave_coordinate * left)
{
    _wave_coordinate_set_type (c, WAVE_COORD_TIMES);
    c->_content._binary._left = left;
}

void wave_coordinate_set_times_right (wave_coordinate * c, wave_coordinate * right)
{
    _wave_coordinate_set_type (c, WAVE_COORD_TIMES);
    c->_content._binary._right = right;
}

void wave_coordinate_set_plus_left_and_right (wave_coordinate * c, wave_coordinate * left, wave_coordinate * right)
{
    wave_coordinate_set_plus_left (c, left);
    wave_coordinate_set_plus_right (c, right);
}

void wave_coordinate_set_times_left_and_right (wave_coordinate * c, wave_coordinate * left, wave_coordinate * right)
{
    wave_coordinate_set_times_left (c, left);
    wave_coordinate_set_times_right (c, right);
}
