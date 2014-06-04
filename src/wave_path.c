/**
 * \file wave_path.c
 * \brief Wave PATH.
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
#include "wave_path.h"

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

void * wave_path_allocator (void)
{
    wave_path * const p = malloc (sizeof * p);
    if (p == NULL)
        perror ("malloc");
    return p;
}

static inline bool _is_complex_move (wave_path * p)
{
    bool is_complex = false;
    switch (p->_move)
    {
        /* Complex moves. */
        case WAVE_MOVE_REWIND:
        case WAVE_MOVE_PART:
        case WAVE_MOVE_REP:
            is_complex = true;
            break;
        /* Simple moves. */
        case WAVE_MOVE_UP:
        case WAVE_MOVE_DOWN:
        case WAVE_MOVE_PRE:
        case WAVE_MOVE_SUC:
        case WAVE_MOVE_UNKNOWN:
        default:
            break;
    }
    return is_complex;
}

void * wave_path_free (wave_path * p)
{
    wave_path * current, * next;
    for (current = p; current != NULL; current = next)
    {
        next = current->_next_path;
        if (_is_complex_move (p))
        {
            if (p->_move == WAVE_MOVE_PART)
                wave_path_free (p->_complex_move._part);
            else
                wave_path_free (p->_complex_move._repeat._path);
        }
        free (current);
    }

    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

bool wave_path_has_next (const wave_path * p)
{
    bool has_next = false;
    if (p != NULL)
        has_next = p->_next_path != NULL;
    return has_next;
}

wave_move_type wave_path_get_move (const wave_path * const p)
{
    wave_move_type move = WAVE_MOVE_UNKNOWN;
    if (p != NULL)
        move = p->_move;
    return move;
}

wave_path * wave_path_get_part (wave_path * const p)
{
    return p->_complex_move._part;
}

repeat_value_type wave_path_get_repeat_type (wave_path * const p)
{
    return p->_complex_move._repeat._type;
}

unsigned int wave_path_get_repeat_number (wave_path * const p)
{
    return p->_complex_move._repeat._number;
}

wave_path * wave_path_get_repeat_path (wave_path * const p)
{
    return p->_complex_move._repeat._path;
}

wave_path * wave_path_get_next (wave_path * const p)
{
    return p->_next_path;
}

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

void wave_path_set_move (wave_path * const p, wave_move_type m)
{
    if (p != NULL)
        p->_move = m;
}

void wave_path_add_path (wave_path * const p, wave_path * const next)
{
    if (p != NULL)
        p->_next_path = next;
}

void wave_path_set_part (wave_path * const p, wave_path * const part)
{
    if (p != NULL)
        p->_complex_move._part = part;
}

void wave_path_set_repeat_type (wave_path * const p, repeat_value_type t)
{
    if (p != NULL)
        p->_complex_move._repeat._type = t;
}

void wave_path_set_repeat_number (wave_path * const p, unsigned int n)
{
    if (p != NULL)
        p->_complex_move._repeat._number = n;
}

void wave_path_set_repeat_path (wave_path * const p, wave_path * const repeat)
{
    if (p != NULL)
        p->_complex_move._repeat._path = repeat;
}
