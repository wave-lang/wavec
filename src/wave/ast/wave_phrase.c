/**
 * \file wave_phrase.c
 * \brief Wave phrase.
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
#include "wave/ast/wave_phrase.h"

////////////////////////////////////////////////////////////////////////////////
// Initialization.
////////////////////////////////////////////////////////////////////////////////

void wave_phrase_init (wave_phrase * p)
{
    p->_collection = NULL;
    p->_next_phrase = NULL;
    p->_previous_phrase = NULL;
}

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

void * wave_phrase_alloc (void)
{
    wave_phrase * const p = malloc (sizeof * p);
    if (p == NULL)
        perror ("malloc");
    else
        wave_phrase_init (p);
    return p;
}

void * wave_phrase_free (wave_phrase * p)
{
    if (p != NULL)
    {
        if (p->_collection != NULL)
            wave_collection_free (p->_collection);
        free (p);
        p = NULL;
    }
    return p;
}

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

bool wave_phrase_has_next (const wave_phrase * const p)
{
    return p->_next_phrase != NULL;
}

bool wave_phrase_has_previous (const wave_phrase * const p)
{
    return p->_previous_phrase != NULL;
}

wave_collection * wave_phrase_get_collection (const wave_phrase * const p)
{
    return p->_collection;
}

wave_phrase * wave_phrase_get_next (const wave_phrase * const p)
{
    return p->_next_phrase;
}

wave_phrase * wave_phrase_get_previous (const wave_phrase * const p)
{
    return p->_previous_phrase;
}

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

void wave_phrase_add_phrase (wave_phrase * const p, wave_phrase * const next)
{
    wave_phrase * last = p;
    while (wave_phrase_has_next (last))
        last = wave_phrase_get_next (last);
    last->_next_phrase = next;
    next->_previous_phrase = last;
}

void wave_phrase_set_collection (wave_phrase * const p, wave_collection * const c)
{
    p->_collection = c;
}

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////


void wave_phrase_fprint (FILE * stream, const wave_phrase * const p)
{
    const wave_phrase * current = p;
    do
    {
        wave_collection * c = wave_phrase_get_collection (current);
        if (c != NULL)
        {
            wave_collection_fprint (stream, c);
            fprintf (stream, ".\n");
        }
        current = wave_phrase_get_next (current);
    }
    while (current != NULL);
}

void wave_phrase_print (const wave_phrase * const p)
{
    wave_phrase_fprint (stdout, p);
}
