/**
 * \file wave_collection.c
 * \brief Wave collection
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
#include "wave_collection.h"

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

void * wave_collection_allocator (void)
{
    wave_collection * const w = malloc (sizeof * w);
    if (w == NULL)
        perror ("malloc");
    return w;
}
static inline void _free_current (wave_collection * w)
{
    wave_collection_type collection_type = wave_collection_get_type (w);
    switch (collection_type)
    {
        case WAVE_COLLECTION_ATOM:
            wave_atom_free (w->_inner._atom);
            break;
        case WAVE_COLLECTION_REP:
            wave_collection_free (w->_inner._repetition._list);
            if (wave_collection_get_repetition_type (w) == WAVE_COLLECTION_REPETITION_PATH)
                wave_path_free (w->_inner._repetition._description._path);
            break;
        case WAVE_COLLECTION_SEQ:
        case WAVE_COLLECTION_PAR:
            wave_collection_free (w->_inner._list);
            break;
        case WAVE_COLLECTION_CYCLIC_PAR:
        case WAVE_COLLECTION_CYCLIC_SEQ:
            wave_collection_free (w->_inner._cyclic._list);
            wave_collection_free (w->_inner._cyclic._cycle);
            break;
        default:
            break;
    }
    free (w);
}

void * wave_collection_free (wave_collection * w)
{
    if (w != NULL)
    {
        wave_collection * current, * next;
        for (current = w; current != NULL; current = next)
        {
            next = current->_next_collection;
            _free_current (current);
        }
        w = NULL;
    }
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

bool wave_collection_has_next (const wave_collection * const c)
{
    return c->_next_collection != NULL;
}

bool wave_collection_has_previous (const wave_collection * const c)
{
    return c->_next_collection != NULL;
}

wave_collection_type wave_collection_get_type (const wave_collection * const c)
{
    return c->_type;
}

wave_atom * wave_collection_get_atom (const wave_collection * const c)
{
    return c->_inner._atom;
}

wave_collection * wave_collection_get_list (const wave_collection * const c)
{
    return c->_inner._list;
}

wave_collection_repetition_type wave_collection_get_repetition_type (const wave_collection * const c)
{
    return c->_inner._repetition._type;
}

wave_collection * wave_collection_get_repetition_list (const wave_collection * const c)
{
    return c->_inner._repetition._list;
}

wave_path * wave_collection_get_repetition_path (const wave_collection * const c)
{
    return c->_inner._repetition._description._path;
}

unsigned int wave_collection_get_repetition_times (const wave_collection * const c)
{
    return c->_inner._repetition._description._times;
}

wave_collection * wave_collection_get_cyclic_list (const wave_collection * const c)
{
    return c->_inner._cyclic._list;
}

wave_collection * wave_collection_get_cyclic_cycle (const wave_collection * const c)
{
    return c->_inner._cyclic._cycle;
}

wave_collection * wave_collection_get_next (const wave_collection * const c)
{
    return c->_next_collection;
}

wave_collection * wave_collection_get_previous (const wave_collection * const c)
{
    return c->_previous_collection;
}

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

void wave_collection_add_collection (wave_collection * const c, wave_collection * const next)
{
    wave_collection * last = c;
    while (wave_collection_has_next (last))
        last = wave_collection_get_next (last);
    last->_next_collection = next;
    next->_previous_collection = last;
}

void wave_collection_set_type (wave_collection * const c,
    wave_collection_type t)
{
    c->_type = t;
}

void wave_collection_set_atom (wave_collection * const c, wave_atom * const a)
{
    c->_inner._atom = a;
}

void wave_collection_set_list (wave_collection * const c, wave_collection * const list)
{
    c->_inner._list = list;
}

void wave_collection_set_repetition_type (wave_collection * const c, wave_collection_repetition_type t)
{
    c->_inner._repetition._type = t;
}

void wave_collection_set_repetition_list (wave_collection * const c, wave_collection * const list)
{
    c->_inner._repetition._list = list;
}

void wave_collection_set_repetition_times (wave_collection * c, unsigned int times)
{
    c->_inner._repetition._description._times = times;
}

void wave_collection_set_repetition_path (wave_collection * const c, wave_path * const p)
{
    c->_inner._repetition._description._path = p;
}

void wave_collection_set_cyclic_list (wave_collection * const c, wave_collection * const list)
{
    c->_inner._cyclic._list = list;
}

void wave_collection_set_cyclic_cycle (wave_collection * const c, wave_collection * const cycle)
{
    c->_inner._cyclic._cycle = cycle;
}

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////

static void _wave_collection_fprint_sep (FILE * stream, const wave_collection * c, const char * sep);

static void _wave_collection_fprint_atom (FILE * stream, const wave_collection * c)
{
    wave_atom_fprint (stream, wave_collection_get_atom (c));
}

static void _wave_collection_fprint_seq (FILE * stream, const wave_collection * c)
{
    _wave_collection_fprint_sep (stream, wave_collection_get_list (c), ";");
}

static void _wave_collection_fprint_par (FILE * stream, const wave_collection * c)
{
    _wave_collection_fprint_sep (stream, wave_collection_get_list (c), "||");
}

static void _wave_collection_fprint_cyclic_sep (FILE * stream, const wave_collection * c, const char * sep)
{
    wave_collection_fprint (stream, wave_collection_get_cyclic_list (c));
    fprintf (stream, "{%s", sep);
    wave_collection_fprint (stream, wave_collection_get_cyclic_cycle (c));
    fprintf (stream, "}");
}

static void _wave_collection_fprint_rep (FILE * stream, const wave_collection * c)
{
    const wave_collection * const repetition = wave_collection_get_repetition_list (c);
    if (wave_collection_get_type (repetition) == WAVE_COLLECTION_SEQ)
        fprintf (stream, "{;");
    else
        fprintf (stream, "{||");
    wave_collection_fprint (stream, repetition);
    fprintf (stream, "}");
    if (wave_collection_get_repetition_type (c) == WAVE_COLLECTION_REPETITION_PATH)
    {
        fprintf (stream, "#[");
        wave_path_fprint (stream, wave_collection_get_repetition_path (c));
        fprintf (stream, "]");
    }
    else
    {
        fprintf (stream, " %d", wave_collection_get_repetition_times (c));
    }
}

static void _wave_collection_fprint_cyclic_seq (FILE * stream, const wave_collection * c)
{
    _wave_collection_fprint_cyclic_sep (stream, c, ";");
}

static void _wave_collection_fprint_cyclic_par (FILE * stream, const wave_collection * c)
{
    _wave_collection_fprint_cyclic_sep (stream, c, "||");
}

static void _wave_collection_fprint_nothing (FILE * stream, const wave_collection *c)
{
}

static void (* _wave_collection_fprint_functions []) (FILE *, const wave_collection *) =
{
    [WAVE_COLLECTION_ATOM] = _wave_collection_fprint_atom,
    [WAVE_COLLECTION_REP] = _wave_collection_fprint_rep,
    [WAVE_COLLECTION_SEQ] = _wave_collection_fprint_seq,
    [WAVE_COLLECTION_PAR] = _wave_collection_fprint_par,
    [WAVE_COLLECTION_CYCLIC_SEQ] = _wave_collection_fprint_cyclic_seq,
    [WAVE_COLLECTION_CYCLIC_PAR] = _wave_collection_fprint_cyclic_par,
    [WAVE_COLLECTION_UNKNOWN] = _wave_collection_fprint_nothing,
};

static void _fprint_current (FILE * stream, const wave_collection * c)
{
    wave_collection_type collection_type = wave_collection_get_type (c);
    if (collection_type >= 0 && collection_type < WAVE_COLLECTION_UNKNOWN)
        _wave_collection_fprint_functions [collection_type] (stream, c);
}

void _wave_collection_fprint_sep (FILE * stream, const wave_collection * c, const char * sep)
{
    const wave_collection * last = c;
    while (last != NULL)
    {
        wave_collection_type collection_type = wave_collection_get_type (last);
        if (collection_type == WAVE_COLLECTION_SEQ || collection_type == WAVE_COLLECTION_PAR)
            fprintf (stream, "(");
        _fprint_current (stream, last);
        if (collection_type == WAVE_COLLECTION_SEQ || collection_type == WAVE_COLLECTION_PAR)
            fprintf (stream, ")");
        if (wave_collection_has_next (last))
            fprintf (stream, "%s", sep);
        last = wave_collection_get_next (last);
    }
}

void wave_collection_fprint (FILE * stream, const wave_collection * c)
{
    _fprint_current (stream, c);
}

void wave_collection_print (const wave_collection * c)
{
    wave_collection_fprint (stdout, c);
}

