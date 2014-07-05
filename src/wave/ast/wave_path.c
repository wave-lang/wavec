/**
 * \file wave_path.c
 * \brief Wave PATH.
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
#include "wave/ast/wave_path.h"

////////////////////////////////////////////////////////////////////////////////
// Initialization.
////////////////////////////////////////////////////////////////////////////////

void wave_path_init (wave_path * const p)
{
    p->_move = WAVE_MOVE_UNKNOWN;
    p->_next_path = NULL;
    p->_previous_path = NULL;
}

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

void * wave_path_alloc (void)
{
    wave_path * const p = malloc (sizeof * p);
    if (p == NULL)
        perror ("malloc");
    else
        wave_path_init (p);
    return p;
}

static inline void _add_to_stack (wave_path * p, wave_stack * s)
{
    wave_path * current, * next;
    for (current = p; current != NULL; current = next)
    {
        next = current->_next_path;
        wave_stack_push (s, current);
    }
}

static inline void _wave_path_free_current (wave_path * p, wave_stack * s)
{
    wave_move_type move = wave_path_get_move (p);
    if (move == WAVE_MOVE_PART)
        _add_to_stack (p->_complex_move._part, s);
    else if (move == WAVE_MOVE_REP)
        _add_to_stack (p->_complex_move._repeat._path, s);
    free (p);
}

void * wave_path_free (wave_path * p)
{
    if (p != NULL)
    {
        wave_stack * s = wave_stack_alloc ();
        _add_to_stack (p, s);
        while (! wave_stack_is_empty (s))
        {
            wave_path * current = wave_stack_pop (s);
            _wave_path_free_current (current, s);
        }
        wave_stack_free (s);
    }

    return NULL;
}

static inline void _copy_move (const wave_path * const original, wave_path * const copy)
{
    copy->_move = original->_move;
}

static inline void _copy_part (const wave_path * const original, wave_path * const copy)
{
    copy->_complex_move._part = wave_path_copy (original->_complex_move._part);
}

static inline void _copy_repeat (const wave_path * const original, wave_path * const copy)
{
    copy->_complex_move._repeat._type = original->_complex_move._repeat._type;
    copy->_complex_move._repeat._number = original->_complex_move._repeat._number;
    copy->_complex_move._repeat._path = wave_path_copy (original->_complex_move._repeat._path);
}

static inline void _copy (const wave_path * const original, wave_path * const copy)
{
    wave_move_type t = wave_path_get_move (original);
    _copy_move (original, copy);
    if (t == WAVE_MOVE_PART)
        _copy_part (original, copy);
    else if (t == WAVE_MOVE_REP)
        _copy_repeat (original, copy);
}

void * wave_path_copy (const wave_path * p)
{
    wave_path * copy = NULL;
    if (p != NULL)
    {
        copy = wave_path_alloc ();
        _copy (p, copy);
        for (wave_path * current = wave_path_get_next (p); current != NULL; current = wave_path_get_next (current))
        {
            wave_path * current_copy = wave_path_alloc ();
            _copy (current, current_copy);
            wave_path_add_path (copy, current_copy);
        }
    }
    return copy;
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

wave_path_repeat_type wave_path_get_repeat_type (const wave_path * const p)
{
    return p->_complex_move._repeat._type;
}

int wave_path_get_repeat_number (const wave_path * const p)
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
    p->_move = m;
}

void wave_path_add_path (wave_path * const p, wave_path * const next)
{
    wave_path * last = p;
    while (wave_path_has_next (last))
        last = wave_path_get_next (last);
    last->_next_path = next;
    next ->_previous_path = last;
}

void wave_path_set_part (wave_path * const p, wave_path * const part)
{
    wave_path_set_move (p, WAVE_MOVE_PART);
    p->_complex_move._part = part;
}

void wave_path_set_repeat_type (wave_path * const p, wave_path_repeat_type t)
{
    wave_path_set_move (p, WAVE_MOVE_REP);
    p->_complex_move._repeat._type = t;
}

void wave_path_set_repeat_number (wave_path * const p, int n)
{
    wave_path_set_repeat_type (p, WAVE_PATH_REPEAT_CONSTANT);
    p->_complex_move._repeat._number = n;
}

void wave_path_set_repeat_path (wave_path * const p, wave_path * const repeat)
{
    wave_path_set_move (p, WAVE_MOVE_REP);
    p->_complex_move._repeat._path = repeat;
}

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////

static inline void _wave_path_fprint_char_move (FILE * stream, char c)
{
    fprintf (stream, "%c", c);
}

/* _wave_path_fprint_{up,down,pre,suc,rewind}:
 * The functions need to be of type "(FILE *, const wave_path *) -> void", even
 * though the "p" parameter is not used, hence the use of the "(void) p;" line.
 * (In order to suppress the -Wunused-parameter warning. The warning can be
 * useful, but not using the "p" parameter is deliberate here.)
 */
static inline void _wave_path_fprint_up (FILE * stream, const wave_path * p)
{
    (void) p;
    _wave_path_fprint_char_move (stream, 'u');
}

static inline void _wave_path_fprint_down (FILE * stream, const wave_path * p)
{
    (void) p;
    _wave_path_fprint_char_move (stream, 'd');
}

static inline void _wave_path_fprint_pre (FILE * stream, const wave_path * p)
{
    (void) p;
    _wave_path_fprint_char_move (stream, 'p');
}

static inline void _wave_path_fprint_suc (FILE * stream, const wave_path * p)
{
    (void) p;
    _wave_path_fprint_char_move (stream, 's');
}

static inline void _wave_path_fprint_rewind (FILE * stream, const wave_path * p)
{
    (void) p;
    _wave_path_fprint_char_move (stream, 'r');
}

static inline void _wave_path_fprint_part (FILE * stream, const wave_path * p)
{
    fprintf (stream, "[");
    wave_path_fprint (stream, p->_complex_move._part);
    fprintf (stream, "]");
}

static inline void _wave_path_fprint_rep (FILE * stream, const wave_path * p)
{
    fprintf (stream, "(");
    wave_path_fprint (stream, p->_complex_move._repeat._path);
    if (p->_complex_move._repeat._type == WAVE_PATH_REPEAT_CONSTANT)
        fprintf (stream, ") %d", p->_complex_move._repeat._number);
    else
        fprintf (stream, ") *");
}

static void (* const _wave_path_fprint_functions []) (FILE * , const wave_path *) =
{
    [WAVE_MOVE_UP]          = _wave_path_fprint_up,
    [WAVE_MOVE_DOWN]        = _wave_path_fprint_down,
    [WAVE_MOVE_PRE]         = _wave_path_fprint_pre,
    [WAVE_MOVE_SUC]         = _wave_path_fprint_suc,
    [WAVE_MOVE_REWIND]      = _wave_path_fprint_rewind,
    [WAVE_MOVE_PART]        = _wave_path_fprint_part,
    [WAVE_MOVE_REP]         = _wave_path_fprint_rep,
    [WAVE_MOVE_UNKNOWN]     = NULL,
};

static void _wave_path_print_current (FILE * stream, const wave_path * p)
{
    wave_move_type m = wave_path_get_move (p);
    if (m >= 0 && m < WAVE_MOVE_UNKNOWN)
        _wave_path_fprint_functions [m] (stream, p);
    if (wave_path_has_next (p))
        fprintf (stream, " ");
}

void wave_path_fprint (FILE * stream, const wave_path * p)
{
    if (p != NULL)
    {
        const wave_path * last = p;
        while (last != NULL)
        {
            _wave_path_print_current (stream, last);
            last = wave_path_get_next (last);
        }
    }
}

void wave_path_print (const wave_path * p)
{
    wave_path_fprint (stdout, p);
}
