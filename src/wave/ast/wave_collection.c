/**
 * \file wave_collection.c
 * \brief Wave collection
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
#include "wave/ast/wave_collection.h"

static inline void _wave_collection_set_parent (wave_collection * const c, wave_collection * parent)
{
    wave_collection * current = c;
    while (current != NULL)
    {
        current->_parent_collection = parent;
        current = wave_collection_get_next (current);
    }
}

static inline void _add_list_to_stack (wave_collection * c, wave_stack * s)
{
    for (wave_collection * current = c; current != NULL; current = wave_collection_get_next (current))
        wave_stack_push (s, current);
}

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

static inline void _copy_atom (const wave_collection * const original, wave_collection * const copy)
{
    copy->_inner._atom = wave_atom_copy (original->_inner._atom);
}

static inline void _copy_list (const wave_collection * const original, wave_collection * const copy)
{
    copy->_inner._list = wave_collection_copy (original->_inner._list);
    _wave_collection_set_parent (copy->_inner._list, copy);
}

static inline void _copy_repetition (const wave_collection * const original, wave_collection * const copy)
{
    copy->_inner._repetition = original->_inner._repetition;
    copy->_inner._repetition._list = wave_collection_copy (original->_inner._repetition._list);
    if (wave_collection_get_repetition_type (original) == WAVE_COLLECTION_REPETITION_PATH)
        copy->_inner._repetition._description._path = wave_path_copy (original->_inner._repetition._description._path);
}

static inline void _copy_current (const wave_collection * const original, wave_collection * const copy)
{
    /* Be careful! Don't override the value (the pointer) of the _info member ! */
    wave_collection_type t = wave_collection_get_type (original);
    copy->_type = original->_type;
    if (t != WAVE_COLLECTION_UNKNOWN)
    {
        if (t == WAVE_COLLECTION_ATOM)
            _copy_atom (original, copy);
        else if (t == WAVE_COLLECTION_REP_SEQ || t == WAVE_COLLECTION_REP_PAR)
            _copy_repetition (original, copy);
        else
            _copy_list (original, copy);
    }
}

void * wave_collection_copy (const wave_collection * c)
{
    wave_collection * copy = NULL;
    if (c != NULL)
    {
        copy = wave_collection_alloc ();
        _copy_current (c, copy);
        for (wave_collection * current = wave_collection_get_next (c); current != NULL; current = wave_collection_get_next (current))
        {
            wave_collection * current_copy = wave_collection_alloc ();
            _copy_current (current, current_copy);
            wave_collection_add_collection (copy, current_copy);
        }
    }
    return copy;
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
    wave_collection_type collection_type = wave_collection_get_type(c);
    if(collection_type == WAVE_COLLECTION_REP_SEQ || collection_type == WAVE_COLLECTION_REP_PAR)
        return wave_collection_get_repetition_list(c);
    if(
            collection_type == WAVE_COLLECTION_SEQ || collection_type == WAVE_COLLECTION_PAR ||
            collection_type == WAVE_COLLECTION_CYCLIC_SEQ || collection_type == WAVE_COLLECTION_CYCLIC_PAR
      )
        return wave_collection_get_normal_list(c);
    return NULL;
}

wave_collection_repetition_type wave_collection_get_repetition_type (const wave_collection * const c)
{
    return c->_inner._repetition._type;
}

wave_collection * wave_collection_get_normal_list (const wave_collection * const c)
{
    return c->_inner._list;
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

wave_collection * wave_collection_get_last (wave_collection * c)
{
    wave_collection * last = c;
    while (wave_collection_has_next (last))
        last = wave_collection_get_next (last);

    return last;
}

static inline wave_coordinate * _wave_collection_sum_list_lengths (wave_collection * c)
{
    wave_coordinate * sum = wave_coordinate_copy (wave_collection_get_length (c));
    for (wave_collection * current = wave_collection_get_next (c); current != NULL; current = wave_collection_get_next (current))
    {
        wave_coordinate * new_sum = wave_coordinate_alloc ();
        wave_coordinate * right = wave_coordinate_copy (wave_collection_get_length (current));
        wave_coordinate_set_plus (new_sum, sum, right);
        sum = new_sum;
    }
    return sum;
}

wave_coordinate * wave_collection_get_list_length (const wave_collection * c)
{
    wave_collection * list = wave_collection_get_list (c);
    return _wave_collection_sum_list_lengths (list);
}

wave_int_list * wave_collection_get_full_indexes (const wave_collection * c)
{
    wave_int_list * list = wave_int_list_alloc ();
    for (const wave_collection * current = c; current != NULL; current = wave_collection_get_parent (current))
    {
        wave_collection_info * info = wave_collection_get_info (current);
        wave_int_list_push_front (list, wave_collection_info_get_index (info));
    }

    return list;
}

bool wave_collection_contains_path (const wave_collection * c)
{
    bool contains = false;
    if (c != NULL)
    {
        wave_stack * s = wave_stack_alloc ();
        wave_stack_push (s, c);
        while (! contains && ! wave_stack_is_empty (s))
        {
            wave_collection * current = wave_stack_pop (s);
            wave_collection_type ct = wave_collection_get_type (current);
            if (ct == WAVE_COLLECTION_ATOM)
            {
                wave_atom_type t = wave_atom_get_type (wave_collection_get_atom (current));
                contains = t == WAVE_ATOM_PATH;
            }
            else if (ct != WAVE_COLLECTION_UNKNOWN)
            {
                wave_collection * list = wave_collection_get_list (current);
                _add_list_to_stack (list, s);
            }
        }
        wave_stack_free (s);
    }

    return contains;
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

void _duplicate_list (wave_collection * list, int times)
{
    int copy_number = times - 1;
    wave_collection * copies[copy_number];
    for (int i = 0; i < copy_number; ++i)
        copies[i] = wave_collection_copy (list);
    for (int i = 0; i < copy_number; ++i)
        wave_collection_add_collection (list, copies[i]);
}

void wave_collection_set_repetition_seq_times (wave_collection * c, int times)
{
    _duplicate_list (c, times);
}

void wave_collection_set_repetition_par_times (wave_collection * c, int times)
{
    _duplicate_list (c, times);
}

void wave_collection_set_repetition_seq_path (wave_collection * c, wave_collection * list, wave_path * p)
{
    wave_collection_set_repetition_seq_list (c, list);
    wave_collection_set_repetition_path (c, p);
}

void wave_collection_set_repetition_par_path (wave_collection * c, wave_collection * list, wave_path * p)
{
    wave_collection_set_repetition_par_list (c, list);
    wave_collection_set_repetition_path (c, p);
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
        if (t != WAVE_COLLECTION_ATOM && t!= WAVE_COLLECTION_UNKNOWN)
        {
            wave_collection * list = wave_collection_get_list (current);
            wave_collection_compute_indexes (list);
        }
    }
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
            int path_length = 0;
            wave_coordinate_set_constant (repetition, path_length);
        }
        wave_coordinate_set_times (length, repetition, length_sum);
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
        wave_coordinate_set_plus (coord, previous_coord, previous_length);
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

    if (t != WAVE_COLLECTION_ATOM && t!= WAVE_COLLECTION_UNKNOWN)
        list = wave_collection_get_list (c);

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

/**
 * \brief Follow the path and calculate the size in the same time with reversal and etc.
 * \param c The starting collection where the path \c p begins.
 * \param p The path to follow.
 * \param recorded_path The path already recorded. Can be \c NULL.
 * \param rewind_recording Only if a path is curently recording.
 * \param counting_all True if all the moves must be counted, false if only the last recorded path must be counted.
 * \param destination Return the pointer to the wave_collection where the path is pointing.
 *
 * This function follows the path and return all the informations you wanted.
 * If you want the total size set counting_all to \c true.
 * If you want the destination give to destination a pointer to a wave_collection pointer.
 */
static int wave_follow_collection_with_extra_bonus(const wave_collection* c, const wave_path* p, wave_path* recorded_path, wave_path* rewind_recording, bool counting_all, const wave_collection** destination){

    int size = 0;
    const wave_path* internal_recorded_path = recorded_path;

    while(c != NULL && p != NULL){
        wave_move_type wmt = wave_path_get_move(p);
        switch(wmt){
            case WAVE_MOVE_UP:
                if(counting_all)
                    size += 1;
                if(rewind_recording != NULL){
                    wave_path* new_one = wave_path_alloc();
                    wave_path_set_move(new_one, WAVE_MOVE_DOWN);
                    wave_path_add_path(rewind_recording, new_one);
                }
                c = wave_collection_get_parent(c);
                break;

            case WAVE_MOVE_DOWN:
                if(counting_all)
                    size += 1;
                if(rewind_recording != NULL){
                    wave_path* new_one = wave_path_alloc();
                    wave_path_set_move(new_one, WAVE_MOVE_UP);
                    wave_path_add_path(rewind_recording, new_one);
                }
                c = wave_collection_get_down(c);
                break;

            case WAVE_MOVE_PRE:
                if(counting_all)
                    size += 1;
                if(rewind_recording != NULL){
                    wave_path* new_one = wave_path_alloc();
                    wave_path_set_move(new_one, WAVE_MOVE_SUC);
                    wave_path_add_path(rewind_recording, new_one);
                }
                c = wave_collection_get_previous(c);
                break;

            case WAVE_MOVE_SUC:
                if(counting_all)
                    size += 1;
                if(rewind_recording != NULL){
                    wave_path* new_one = wave_path_alloc();
                    wave_path_set_move(new_one, WAVE_MOVE_PRE);
                    wave_path_add_path(rewind_recording, new_one);
                }
                c = wave_collection_get_next(c);
                break;

            case WAVE_MOVE_REWIND:
                if(recorded_path != NULL){
                    int size_rewind = wave_follow_collection_with_extra_bonus(c, recorded_path, recorded_path, rewind_recording, counting_all, &c);
                    if(counting_all)
                        size += size_rewind;
                }
                break;

            case WAVE_MOVE_REP:
                {
                    wave_path_repeat_type type = wave_path_get_repeat_type(p);
                    const wave_collection* temp_save;
                    int nb_times;

                    if( type == WAVE_PATH_REPEAT_CONSTANT)
                        nb_times = wave_path_get_repeat_number(p);

                    wave_path* repeated_path = wave_path_get_repeat_path(p);
                    int size_rep;
                    wave_path temp;
                    temp._next_path = NULL;
                    temp._previous_path = NULL;

                    for(int i = 0; (type == WAVE_PATH_REPEAT_CONSTANT && i < nb_times) || (type == WAVE_PATH_REPEAT_INFINITE && c != NULL); i++){
                        temp_save = c;      // Save for infinite repetition. If c is null get this one as last move possible.

                        size_rep = wave_follow_collection_with_extra_bonus(c, repeated_path, recorded_path, &temp, counting_all, &c);

                        if(type == WAVE_PATH_REPEAT_CONSTANT || (type == WAVE_PATH_REPEAT_INFINITE && c != NULL)){ // If the path is constant and the infinite repeat did not find the end.
                            if( counting_all )
                                size += size_rep;
                            else{
                                if(wave_path_get_move(repeated_path) == WAVE_MOVE_PART){ // Add only if the repeat is an record path and set to zero if repeted
                                    size = 0;
                                    size += size_rep;
                                }
                            }
                        }

                        if(c == NULL){
                            wave_path_free(temp._next_path);
                            temp._next_path = NULL;
                        }
                        else{
                            if(wave_path_get_move(repeated_path) == WAVE_MOVE_PART){
                                if(recorded_path != internal_recorded_path)
                                    wave_path_free(recorded_path);
                                recorded_path = temp._next_path;
                                if(recorded_path != NULL)
                                    recorded_path->_previous_path = NULL;
                                temp._next_path = NULL;
                            }
                            if(rewind_recording != NULL)        // Case where the upper function is recording also. Add then a copy of what whe recorded when the recursive call happened
                                wave_path_add_path(rewind_recording, wave_path_copy(temp._next_path));
                        }
                    }
                    if(type == WAVE_PATH_REPEAT_INFINITE)
                        c = temp_save;
                }
                break;

            case WAVE_MOVE_PART:
                {
                    wave_path* part_pathq = wave_path_get_part(p);
                    wave_path temp;
                    temp._next_path = NULL;
                    temp._previous_path = NULL;
                    int size_mv_part = wave_follow_collection_with_extra_bonus(c, part_pathq, recorded_path, &temp, true, &c);
                    if(!counting_all)
                        size = 0;
                    size += size_mv_part;

                    if(recorded_path != internal_recorded_path && recorded_path != NULL)
                        wave_path_free(recorded_path);
                    if(rewind_recording != NULL)        // Case where the upper function is recording also. Add then a copy of what whe recorded when the recursive call happened
                        wave_path_add_path(rewind_recording, wave_path_copy(temp._next_path));

                    recorded_path = temp._next_path;
                    if(recorded_path != NULL)
                        recorded_path->_previous_path = NULL;
                }
                break;

            default:
                fprintf(stderr, "A path or not a path ... that is the question\n");
                exit(1);
                break;
        }

        p = wave_path_get_next(p);
    }

    if((internal_recorded_path == NULL && recorded_path != NULL) || internal_recorded_path != recorded_path)
        wave_path_free(recorded_path);

    if(destination != NULL)
        *destination = c;

    if(c == NULL)
        return -1;
    else
        return size;
}

int wave_collection_get_path_size_only_last_record(const wave_collection* c, const wave_path* path){
    return wave_follow_collection_with_extra_bonus(c, path, NULL, NULL, false, NULL);
}

int wave_collection_get_path_size(const wave_collection* c, const wave_path* path){
    const wave_collection* end;
    int size = wave_follow_collection_with_extra_bonus(c, path, NULL, NULL, true, &end);
    if(end == NULL)
        return -1;
    return size;
}

const wave_collection* wave_collection_get_collection_pointed(const wave_collection* c, const wave_path* path){
    const wave_collection* end;
    wave_follow_collection_with_extra_bonus(c, path, NULL, NULL, false, &end);
    return end;
}

bool wave_collection_path_is_valid (wave_collection * c, const wave_path * p)
{
    return wave_collection_get_collection_pointed (c, p) != NULL;
}

static void copy_collection_path_time(wave_collection* c){
    wave_collection* next = wave_collection_get_next(c);
    wave_collection* previous = wave_collection_get_previous(c);
    wave_collection* parent = wave_collection_get_parent(c);
    wave_collection* collection_to_copy = wave_collection_get_repetition_list(c);
    wave_collection* copy;

    wave_collection_unroll_path( collection_to_copy );

    int size = wave_collection_get_path_size_only_last_record(c, wave_collection_get_repetition_path(c));
    if(size < 0){
        fprintf(stderr, "The path is not valid\n");
        exit(1);
    }
    if(size == 0){
        fprintf(stderr, "The path did not contain any record.\n");
        exit(1);
    }
    copy = wave_collection_copy( collection_to_copy );
    for(int i=1; i < size; i++)
        wave_collection_add_collection(copy, wave_collection_copy( collection_to_copy ));

    _wave_collection_set_parent(copy, parent);
    wave_collection_add_collection(copy, next);

    previous->_next_collection = NULL;
    wave_collection_add_collection(previous, copy);

    c->_next_collection = NULL;
    wave_collection_free(c);
}

void wave_collection_unroll_path(wave_collection* c){
    if(c != NULL){
        wave_collection* collection = wave_collection_get_next(c);
        wave_collection_type type = wave_collection_get_type(c);
        if( type == WAVE_COLLECTION_REP_SEQ || type == WAVE_COLLECTION_REP_PAR )
            copy_collection_path_time(c);
        else
            if(type == WAVE_COLLECTION_SEQ || type == WAVE_COLLECTION_PAR ||
                    type == WAVE_COLLECTION_CYCLIC_SEQ || type == WAVE_COLLECTION_CYCLIC_PAR)
                wave_collection_unroll_path(wave_collection_get_list(c));
        wave_collection_unroll_path( collection );
    }
}

static void _replace_with_pointed (wave_collection * c, wave_collection * pointed)
{
    wave_collection* next = wave_collection_get_next(c);
    wave_collection* previous = wave_collection_get_previous(c);
    wave_collection* parent = wave_collection_get_parent(c);

    wave_collection* next_collection = wave_collection_get_next(pointed);
    pointed->_next_collection = NULL;
    wave_collection* copy = wave_collection_copy( pointed );
    pointed->_next_collection = next_collection;
    if(wave_collection_has_previous(c))
        c->_previous_collection->_next_collection = copy;
    if(wave_collection_has_next(c))
        c->_next_collection->_previous_collection = copy;
    copy->_previous_collection = previous;
    copy->_next_collection = next;
    copy->_parent_collection = parent;

    copy->_info = wave_collection_info_copy(c->_info);

    if(wave_collection_get_type(copy) != WAVE_COLLECTION_ATOM)
        wave_collection_compute_indexes(wave_collection_get_list(copy));

    c->_next_collection = NULL;
    fprintf (stderr, "free: ");
    fprintf (stderr, "\t");
    wave_collection_fprint (stderr, c);
    fprintf (stderr, "\n");
    fprintf (stderr, "\t");
    wave_collection_fprint (stderr, pointed);
    fprintf (stderr, "\n");
    wave_collection_free(c);
}

static void _remplace_path_if_possible(wave_collection* c){
    wave_collection* pointed = (wave_collection*) wave_collection_get_collection_pointed (c, wave_atom_get_path (wave_collection_get_atom (c)));
    if (pointed != NULL)
    {
        wave_collection_fprint (stderr, pointed);
        fprintf (stderr, "Je suis pointé\n");

        wave_int_list* me = wave_collection_get_full_indexes (c);
        wave_int_list* him_or_her = wave_collection_get_full_indexes (pointed);

        int diff = wave_int_list_compare (me, him_or_her);

        if (diff < 0)
        {
            _replace_with_pointed (c, pointed);
        }
        else if (diff > 0)
        {
            if (! wave_collection_contains_path (pointed))
            {
                fprintf (stderr, "OOO: ");
                wave_collection_fprint (stderr, pointed);
                fprintf (stderr, "\n");
                _replace_with_pointed (c, pointed);
            }
        }
    }
}

void wave_collection_replace_path(wave_collection* c)
{
    if (c != NULL)
    {
        for (wave_collection * current = c; current != NULL; current = wave_collection_get_next (current))
        {
            wave_collection_type type = wave_collection_get_type (current);
            if (type == WAVE_COLLECTION_ATOM)
            {
                wave_atom* atom = wave_collection_get_atom (current);
                wave_atom_type atom_type = wave_atom_get_type (atom);
                if (atom_type == WAVE_ATOM_PATH)
                    _remplace_path_if_possible (current);
            }
            else if (type == WAVE_COLLECTION_SEQ || type == WAVE_COLLECTION_PAR ||
                    type == WAVE_COLLECTION_CYCLIC_SEQ || type == WAVE_COLLECTION_CYCLIC_PAR)
            {
                wave_collection_replace_path (wave_collection_get_list (current));
            }
        }
    }
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

void wave_collection_fprint_full_indexes (FILE * stream, const wave_collection * c)
{
    wave_int_list * indexes = wave_collection_get_full_indexes (c);
    wave_int_list_fprint (stream, indexes);
    wave_int_list_free (indexes);
}
