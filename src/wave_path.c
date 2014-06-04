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
    else
    {
        p->_move = WAVE_MOVE_UNKNOWN;
        p->_next_path = NULL;
        p->_previous_path = NULL;
    }
    return p;
}

static inline void _free_current (wave_path * p)
{
    switch (p->_move)
    {
        /* Complex moves. */
        case WAVE_MOVE_REWIND:
            break;
        case WAVE_MOVE_PART:
            wave_path_free (p->_complex_move._part);
            break;
        case WAVE_MOVE_REP:
            wave_path_free (p->_complex_move._repeat._path);
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
    free (p);
}

void * wave_path_free (wave_path * p)
{
    if (p != NULL)
    {
        wave_path * current, * next;
        for (current = p; current != NULL; current = next)
        {
            next = current->_next_path;
            _free_current (current);
        }
        p = NULL;
    }

    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

bool wave_path_has_next (const wave_path * const p)
{
    return p->_next_path != NULL;
}

bool wave_path_has_previous (const wave_path * const p)
{
    return p->_previous_path != NULL;
}

wave_move_type wave_path_get_move (const wave_path * const p)
{
    return p->_move;
}

wave_path * wave_path_get_part (const wave_path * const p)
{
    return p->_complex_move._part;
}

repeat_value_type wave_path_get_repeat_type (const wave_path * const p)
{
    return p->_complex_move._repeat._type;
}

unsigned int wave_path_get_repeat_number (const wave_path * const p)
{
    return p->_complex_move._repeat._number;
}

wave_path * wave_path_get_repeat_path (const wave_path * const p)
{
    return p->_complex_move._repeat._path;
}

wave_path * wave_path_get_next (const wave_path * const p)
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
    {
        wave_path * last = p;
        while (wave_path_has_next (last))
            last = wave_path_get_next (last);
        last->_next_path = next;
        next ->_previous_path = last;
    }
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

////////////////////////////////////////////////////////////////////////////////
// Others.
////////////////////////////////////////////////////////////////////////////////

static void _print_move (FILE * stream, wave_move_type m)
{
    char c = ' ';
    switch (m)
    {
        case WAVE_MOVE_UP:
            c = 'u';
            break;
        case WAVE_MOVE_DOWN:
            c = 'd';
            break;
        case WAVE_MOVE_PRE:
            c = 'p';
            break;
        case WAVE_MOVE_SUC:
            c = 's';
            break;
        case WAVE_MOVE_REWIND:
            c = 'r';
            break;
        case WAVE_MOVE_PART:
        case WAVE_MOVE_REP:
        case WAVE_MOVE_UNKNOWN:
        default:
            break;
    }
    if (c != ' ')
        fprintf (stream, "%c", c);
}

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////

static void _print_current (FILE * stream, const wave_path * p)
{
    wave_move_type m = wave_path_get_move (p);
    if (m == WAVE_MOVE_PART)
    {
        fprintf (stream, "[ ");
        wave_path_fprint (stream, p->_complex_move._part);
        fprintf (stream, "]");
    }
    else if (m == WAVE_MOVE_REP)
    {
        fprintf (stream, "( ");
        wave_path_fprint (stream, p->_complex_move._repeat._path);
        fprintf (stream, ") %d", p->_complex_move._repeat._number);
    }
    else
        _print_move (stream, m);

    if (wave_path_has_next (p))
        fprintf (stream, " ");
}

void wave_path_fprint (FILE * stream, const wave_path * p)
{
    const wave_path * last = p;
    while (last != NULL)
    {
        _print_current (stream, last);
        last = wave_path_get_next (last);
    }
}

void wave_path_print (const wave_path * p)
{
    wave_path_fprint (stdout, p);
}
