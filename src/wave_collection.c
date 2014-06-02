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

void * wave_collection_free (wave_collection * w)
{
    free (w);
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

bool wave_collection_has_next (const wave_collection * const c)
{
    bool has_next = false;
    if (c != NULL)
        has_next = c->_next_collection != NULL;
    return has_next;
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

wave_collection * wave_collection_get_repetition_list (const wave_collection * const c)
{
    return c->_inner._repetition._list;
}

wave_path * wave_collection_get_repetition_path (const wave_collection * const c)
{
    return c->_inner._repetition._path;
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

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

void wave_collection_add_collection (wave_collection * const c,
    wave_collection * const next)
{
    if (c != NULL)
        c->_next_collection = next;
}

void wave_collection_set_type (wave_collection * const c,
    wave_collection_type t)
{
    if (c != NULL)
        c->_type = t;
}

void wave_collection_set_atom (wave_collection * const c, atom * const a)
{
    if (c != NULL)
        c->_atom = a;
}

void wave_collection_set_list (wave_collection * const c,
    wave_collection * const list)
{
    if (c != NULL)
        c->_list = list;
}

void wave_collection_set_repetition_list (wave_collection * const c,
    wave_collection * const list)
{
    if (c != NULL)
        c->_repetition._list = list;
}

void wave_collection_set_repetition_path (wave_collection * const c,
    wave_path * const p)
{
    if (c != NULL)
        c->_repetition._path = p;
}

void wave_collection_set_cyclic_list (wave_collection * const c,
    wave_collection * const list)
{
    if (c != NULL)
        c->_cyclic._list = list;
}

void wave_collection_set_cyclic_cycle (wave_collection * const c,
    wave_collection * const cycle)
{
    if (c != NULL)
        c->_cyclic._cycle = cycle;
}
