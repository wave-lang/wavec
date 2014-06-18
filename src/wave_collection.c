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
// Initialization.
////////////////////////////////////////////////////////////////////////////////

void wave_collection_init (wave_collection * const c)
{
    c->_type = WAVE_COLLECTION_UNKNOWN;
    c->_next_collection = NULL;
    c->_previous_collection = NULL;
    c->_parent_collection = NULL;
    c->_info = wave_collection_info_alloc ();
}

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

void * wave_collection_alloc (void)
{
    wave_collection * const c = malloc (sizeof * c);
    if (c == NULL)
        perror ("malloc");
    else
        wave_collection_init (c);
    return c;
}

static inline void _wave_collection_free_atom (wave_collection * c)
{
    wave_atom_free (c->_inner._atom);
}

static inline void _wave_collection_free_repetition (wave_collection * c)
{
    wave_collection_free (c->_inner._repetition._list);
    if (wave_collection_get_repetition_type (c) == WAVE_COLLECTION_REPETITION_PATH)
        wave_path_free (c->_inner._repetition._description._path);
}

static inline void _wave_collection_free_list (wave_collection * c)
{
    wave_collection_free (c->_inner._list);
}

static void (* const _wave_collection_free_functions []) (wave_collection *) =
{
    [WAVE_COLLECTION_ATOM]          = _wave_collection_free_atom,
    [WAVE_COLLECTION_REP_SEQ]       = _wave_collection_free_repetition,
    [WAVE_COLLECTION_REP_PAR]       = _wave_collection_free_repetition,
    [WAVE_COLLECTION_SEQ]           = _wave_collection_free_list,
    [WAVE_COLLECTION_PAR]           = _wave_collection_free_list,
    [WAVE_COLLECTION_CYCLIC_PAR]    = _wave_collection_free_list,
    [WAVE_COLLECTION_CYCLIC_SEQ]    = _wave_collection_free_list,
    [WAVE_COLLECTION_UNKNOWN]       = NULL,
};

static inline void _wave_collection_free_current (wave_collection * c)
{
    wave_collection_type collection_type = wave_collection_get_type (c);
    if (collection_type >= 0 && collection_type < WAVE_COLLECTION_UNKNOWN)
        _wave_collection_free_functions [collection_type] (c);
    wave_collection_info_free (c->_info);
    free (c);
}

void * wave_collection_free (wave_collection * c)
{
    if (c != NULL)
    {
        wave_collection * current, * next;
        for (current = c; current != NULL; current = next)
        {
            next = current->_next_collection;
            _wave_collection_free_current (current);
        }
        c = NULL;
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
    return c->_previous_collection != NULL;
}

bool wave_collection_has_parent (const wave_collection * const c)
{
    return c->_parent_collection != NULL;
}

bool wave_collection_has_down (const wave_collection * const c)
{
    wave_collection_type collection_type = wave_collection_get_type (c);
    return collection_type == WAVE_COLLECTION_SEQ || collection_type == WAVE_COLLECTION_PAR;
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

int wave_collection_get_repetition_times (const wave_collection * const c)
{
    return c->_inner._repetition._description._times;
}

wave_collection * wave_collection_get_next (const wave_collection * const c)
{
    return c->_next_collection;
}

wave_collection * wave_collection_get_previous (const wave_collection * const c)
{
    return c->_previous_collection;
}

wave_collection * wave_collection_get_parent (const wave_collection * const c)
{
    return c->_parent_collection;
}

wave_collection * wave_collection_get_down (const wave_collection * const c)
{
    wave_collection * down = NULL;
    wave_collection_type collection_type = wave_collection_get_type (c);

    if (collection_type == WAVE_COLLECTION_SEQ || collection_type == WAVE_COLLECTION_PAR)
        down = wave_collection_get_list (c);

    return down;
}

wave_collection_info * wave_collection_get_info (const wave_collection * c)
{
    return c->_info;
}

int wave_collection_get_index (const wave_collection * c)
{
    wave_collection_info * info = wave_collection_get_info (c);
    return wave_collection_info_get_index (info);
}

wave_coordinate * wave_collection_get_coordinate (const wave_collection * c)
{
    wave_collection_info * info = wave_collection_get_info (c);
    return wave_collection_info_get_coordinate (info);
}

wave_coordinate * wave_collection_get_length (const wave_collection * c)
{
    wave_collection_info * info = wave_collection_get_info (c);
    return wave_collection_info_get_length (info);
}

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

void wave_collection_add_collection (wave_collection * const c, wave_collection * const next)
{
    if (next != NULL)
    {
        wave_collection * last = c;
        while (wave_collection_has_next (last))
            last = wave_collection_get_next (last);
        last->_next_collection = next;
        next->_previous_collection = last;
        next->_parent_collection = last->_parent_collection;
    }
}

void wave_collection_set_type (wave_collection * const c, wave_collection_type t)
{
    c->_type = t;
}

void wave_collection_set_atom (wave_collection * const c, wave_atom * const a)
{
    wave_collection_set_type (c, WAVE_COLLECTION_ATOM);
    c->_inner._atom = a;
}

static inline void _wave_collection_set_parent (wave_collection * const c, wave_collection * parent)
{
    wave_collection * current = c;
    while (current != NULL)
    {
        current->_parent_collection = parent;
        current = wave_collection_get_next (current);
    }
}

static inline void _wave_collection_set_list (wave_collection * const c, wave_collection * list, wave_collection_type t)
{
    wave_collection_set_type (c, t);
    c->_inner._list = list;
    _wave_collection_set_parent (list, c);
}

void wave_collection_set_seq_list (wave_collection * c, wave_collection * list)
{
    _wave_collection_set_list (c, list, WAVE_COLLECTION_SEQ);
}

void wave_collection_set_par_list (wave_collection * c, wave_collection * list)
{
    _wave_collection_set_list (c, list, WAVE_COLLECTION_PAR);
}

void wave_collection_set_repetition_type (wave_collection * const c, wave_collection_repetition_type t)
{
    c->_inner._repetition._type = t;
}

static inline void wave_collection_set_repetition_list (wave_collection * const c, wave_collection * const list, wave_collection_type t)
{
    wave_collection_set_type (c, t);
    c->_inner._repetition._list = list;
    _wave_collection_set_parent (list, c);
}

void wave_collection_set_repetition_seq_list (wave_collection * const c,wave_collection * const list)
{
    wave_collection_set_repetition_list (c, list, WAVE_COLLECTION_REP_SEQ);
}

void wave_collection_set_repetition_par_list (wave_collection * const c,wave_collection * const list)
{
    wave_collection_set_repetition_list (c, list, WAVE_COLLECTION_REP_PAR);
}

void wave_collection_set_repetition_times (wave_collection * c, int times)
{
    wave_collection_set_repetition_type (c, WAVE_COLLECTION_REPETITION_CONSTANT);
    c->_inner._repetition._description._times = times;
}

void wave_collection_set_repetition_path (wave_collection * const c, wave_path * const p)
{
    wave_collection_set_repetition_type (c, WAVE_COLLECTION_REPETITION_PATH);
    c->_inner._repetition._description._path = p;
}

void wave_collection_set_cyclic_seq_list (wave_collection * c, wave_collection * list)
{
    _wave_collection_set_list (c, list, WAVE_COLLECTION_CYCLIC_SEQ);
}

void wave_collection_set_cyclic_par_list (wave_collection * c, wave_collection * list)
{
    _wave_collection_set_list (c, list, WAVE_COLLECTION_CYCLIC_PAR);
}

////////////////////////////////////////////////////////////////////////////////
// Info generation.
////////////////////////////////////////////////////////////////////////////////

void wave_collection_compute_indexes (wave_collection * c)
{
    int current_index = 0;
    for (wave_collection * current = c; current != NULL; current = wave_collection_get_next (current))
    {
        wave_collection_info * info = wave_collection_get_info (current);
        wave_collection_info_set_index (info, current_index);
        current_index++;

        wave_collection_type t = wave_collection_get_type (current);
        if (t == WAVE_COLLECTION_PAR || t == WAVE_COLLECTION_SEQ
            || t == WAVE_COLLECTION_CYCLIC_SEQ || t == WAVE_COLLECTION_CYCLIC_PAR)
        {
            wave_collection * list = wave_collection_get_list (current);
            wave_collection_compute_indexes (list);
        }
        else if (t == WAVE_COLLECTION_REP_SEQ || t == WAVE_COLLECTION_REP_PAR)
        {
            wave_collection * list = wave_collection_get_repetition_list (current);
            wave_collection_compute_indexes (list);
        }
    }
}

static inline wave_int_list * _wave_collection_create_var (wave_collection * c)
{
    wave_int_list * list = wave_int_list_alloc ();
    for (wave_collection * current = c; current != NULL; current = wave_collection_get_parent (current))
    {
        wave_collection_info * info = wave_collection_get_info (c);
        wave_int_list_push_front (list, wave_collection_info_get_index (info));
    }

    return list;
}

static inline wave_coordinate * _wave_collection_sum_list_lengths (wave_collection * c)
{
    wave_coordinate * sum = wave_coordinate_copy (wave_collection_get_length (c));
    for (wave_collection * current = wave_collection_get_next (c); current != NULL; current = wave_collection_get_next (current))
    {
        wave_coordinate * new_sum = wave_coordinate_alloc ();
        wave_coordinate * right = wave_coordinate_copy (wave_collection_get_length (current));
        wave_coordinate_set_plus_left_and_right (new_sum, sum, right);
        sum = new_sum;
    }
    return sum;
}

static inline void  _wave_collection_set_length (wave_collection * c)
{
    wave_collection_type t = wave_collection_get_type (c);
    wave_collection_info * info = wave_collection_get_info (c);
    wave_coordinate * length = wave_coordinate_alloc ();
    if (t == WAVE_COLLECTION_ATOM || t == WAVE_COLLECTION_SEQ || t == WAVE_COLLECTION_PAR)
    {
        wave_coordinate_set_constant (length, 1);
    }
    else if (t == WAVE_COLLECTION_REP_SEQ || t == WAVE_COLLECTION_REP_PAR)
    {
        wave_collection_repetition_type rt = wave_collection_get_repetition_type (c);
        wave_collection * list = wave_collection_get_repetition_list (c);
        wave_coordinate * length_sum = _wave_collection_sum_list_lengths (list);
        wave_coordinate * repetition = wave_coordinate_alloc ();

        if (rt == WAVE_COLLECTION_REPETITION_CONSTANT)
        {
            int repetition_number = wave_collection_get_repetition_times (c);
            wave_coordinate_set_constant (repetition, repetition_number);
        }
        else
        {
            wave_int_list * var_length = _wave_collection_create_var (c);
            wave_coordinate_set_list (repetition, var_length);
        }
        wave_coordinate_set_times_left_and_right (length, repetition, length_sum);
    }
    wave_collection_info_set_length (info, length);
}

static inline void _wave_collection_set_coords (wave_collection * c)
{
    wave_coordinate * coord = wave_coordinate_alloc ();
    if (wave_collection_has_previous (c))
    {
        wave_collection * previous = wave_collection_get_previous (c);
        wave_coordinate * previous_coord = wave_coordinate_copy (wave_collection_get_coordinate (previous));
        wave_coordinate * previous_length = wave_coordinate_copy (wave_collection_get_length (previous));
        wave_coordinate_set_plus_left_and_right (coord, previous_coord, previous_length);
    }
    else
    {
        wave_coordinate_set_constant (coord, 0);
    }
    wave_collection_info * info = wave_collection_get_info (c);
    wave_collection_info_set_coordinate (info, coord);
}

static inline void _wave_collection_compute_current (wave_collection * c)
{
    wave_collection_type t = wave_collection_get_type (c);
    wave_collection * list = NULL;

    if (t == WAVE_COLLECTION_SEQ || t == WAVE_COLLECTION_PAR
        || t == WAVE_COLLECTION_CYCLIC_SEQ || t == WAVE_COLLECTION_CYCLIC_PAR)
        list = wave_collection_get_list (c);
    else if (t == WAVE_COLLECTION_REP_SEQ || t == WAVE_COLLECTION_REP_PAR)
        list = wave_collection_get_repetition_list (c);

    if (list != NULL)
        wave_collection_compute_length_and_coords (list);

    _wave_collection_set_length (c);
    _wave_collection_set_coords (c);
}

void wave_collection_compute_length_and_coords (wave_collection * c)
{
    for (wave_collection * current = c; current != NULL; current = wave_collection_get_next (current))
        _wave_collection_compute_current (current);
}

////////////////////////////////////////////////////////////////////////////////
// Interaction with paths.
////////////////////////////////////////////////////////////////////////////////

static inline wave_collection * _access_collection_repeat_number (wave_collection * c, const wave_path * p)
{
    wave_collection * m = c;
    for (int i = 0; m != NULL && i < p->_complex_move._repeat._number; ++i)
        m = wave_collection_access (m, p->_complex_move._repeat._path);

    return m;
}

static inline wave_collection * _access_collection_repeat_infinite (wave_collection * c, const wave_path * p)
{
    wave_collection * m = c;
    wave_collection * next = m;

    while (next != NULL)
    {
        m = next;
        next = wave_collection_access (m, p->_complex_move._repeat._path);
    }

    return m;
}

static wave_collection * _access_collection (wave_collection * c, const wave_path * p)
{
    wave_collection * access = NULL;
    wave_move_type m = wave_path_get_move (p);
    if (m == WAVE_MOVE_UP)
        access = wave_collection_get_parent (c);
    else if (m == WAVE_MOVE_DOWN)
        access = wave_collection_get_down (c);
    else if (m == WAVE_MOVE_PRE)
        access = wave_collection_get_previous (c);
    else if (m == WAVE_MOVE_SUC)
        access = wave_collection_get_next (c);
    else if (m == WAVE_MOVE_REP)
    {
        if (wave_path_get_repeat_type (p) == WAVE_PATH_REPEAT_CONSTANT)
            access = _access_collection_repeat_number (c, p);
        else
            access = _access_collection_repeat_infinite (c, p);
    }

    return access;
}

bool wave_collection_path_is_valid (wave_collection * c, const wave_path * p)
{
    return wave_collection_access (c, p) != NULL;
}

wave_collection * wave_collection_access (wave_collection * c, const wave_path * p)
{
    const wave_path * current_move = p;
    wave_collection * current_collection = c;

    while (current_move != NULL && current_collection != NULL)
    {
        current_collection = _access_collection (current_collection, current_move);
        current_move = wave_path_get_next (p);
    }

    return current_collection;
}

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////

/* "_wave_collection_fprint_*" : Functions used to print a collection according
 * to its type.
 * All the functions must have identical prototypes, for they will be stored in
 * a tab.
 */
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
    fprintf (stream, "{%s", sep);
    _wave_collection_fprint_sep (stream, wave_collection_get_list (c), sep);
    fprintf (stream, "}");
}

static void _wave_collection_fprint_rep (FILE * stream, const wave_collection * c, const char * sep)
{
    const wave_collection * const repetition = wave_collection_get_repetition_list (c);
    fprintf (stream, "{%s", sep);
    _wave_collection_fprint_sep (stream, repetition, sep);
    fprintf (stream, "}");
    if (wave_collection_get_repetition_type (c) == WAVE_COLLECTION_REPETITION_PATH)
    {
        fprintf (stream, "#");
        wave_path_fprint (stream, wave_collection_get_repetition_path (c));
    }
    else
    {
        fprintf (stream, " %d", wave_collection_get_repetition_times (c));
    }
}

static void _wave_collection_fprint_rep_seq (FILE * stream, const wave_collection * c)
{
    _wave_collection_fprint_rep (stream, c, ";");
}

static void _wave_collection_fprint_rep_par (FILE * stream, const wave_collection * c)
{
    _wave_collection_fprint_rep (stream, c, "||");
}

static void _wave_collection_fprint_cyclic_seq (FILE * stream, const wave_collection * c)
{
    _wave_collection_fprint_cyclic_sep (stream, c, ";");
}

static void _wave_collection_fprint_cyclic_par (FILE * stream, const wave_collection * c)
{
    _wave_collection_fprint_cyclic_sep (stream, c, "||");
}

/* Tab of functions used to print a wave_collection. */
static void (* const _wave_collection_fprint_functions []) (FILE *, const wave_collection *) =
{
    [WAVE_COLLECTION_ATOM]          = _wave_collection_fprint_atom,
    [WAVE_COLLECTION_REP_SEQ]       = _wave_collection_fprint_rep_seq,
    [WAVE_COLLECTION_REP_PAR]       = _wave_collection_fprint_rep_par,
    [WAVE_COLLECTION_SEQ]           = _wave_collection_fprint_seq,
    [WAVE_COLLECTION_PAR]           = _wave_collection_fprint_par,
    [WAVE_COLLECTION_CYCLIC_SEQ]    = _wave_collection_fprint_cyclic_seq,
    [WAVE_COLLECTION_CYCLIC_PAR]    = _wave_collection_fprint_cyclic_par,
    [WAVE_COLLECTION_UNKNOWN]       = NULL,
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
        last = wave_collection_get_next (last);
        if (last != NULL){
            collection_type = wave_collection_get_type(last);
            if(collection_type != WAVE_COLLECTION_REP_PAR && collection_type != WAVE_COLLECTION_REP_SEQ
                    && collection_type != WAVE_COLLECTION_CYCLIC_SEQ && collection_type != WAVE_COLLECTION_CYCLIC_PAR)
                fprintf (stream, "%s", sep);
        }
    }
}

void wave_collection_fprint (FILE * stream, const wave_collection * c)
{
    if (c != NULL)
        _fprint_current (stream, c);
}

void wave_collection_print (const wave_collection * c)
{
    wave_collection_fprint (stdout, c);
}
