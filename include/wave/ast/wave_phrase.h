/**
 * \file wave_phrase.h
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
#ifndef __WAVE_PHRASE_H__
#define __WAVE_PHRASE_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "wave/ast/wave_collection.h"

/**
 * \defgroup wave_ast_group Wave Abstract Syntax Tree
 */

////////////////////////////////////////////////////////////////////////////////
// Enums, Structs, Typedefs.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Wave phrase.
 * \warning Prhases not obtained with wave_phrase_alloc() must be initialized using wave_phrase_init() !
 */
typedef struct wave_phrase
{
    wave_collection * _collection;              /**<- Collection. */
    struct wave_phrase * _next_phrase;          /**<- Next phrase. */
    struct wave_phrase * _previous_phrase;      /**<- Previous phrase. */
} wave_phrase;

////////////////////////////////////////////////////////////////////////////////
// Initialization.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Initialize a wave_phrase.
 * \param p Phrase.
 */
void wave_phrase_init (wave_phrase * p);

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Alloc for phrases.
 * \relatesalso wave_phrase
 * \note Phrases obtained using wave_phrase_alloc() are already initialized. It is not necessary to use wave_phrase_init().
 */
void * wave_phrase_alloc (void);

/**
 * \brief Free a phrase.
 * \param p Phrase.
 * \relatesalso wave_phrase
 */
void * wave_phrase_free (wave_phrase * p);

void wave_phrase_clean (wave_phrase * p);

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Determine whether there is another phrase following the current phrase.
 * \param p Phrase.
 * \relatesalso wave_phrase
 * \warning \c p must be not \c NULL.
 * \retval true If the phrase has a following phrase.
 * \retval false otherwise.
 */
bool wave_phrase_has_next (const wave_phrase * p);

/**
 * \brief Determine whether the current phrase follows another phrase.
 * \param p Phrase.
 * \relatesalso wave_phrase
 * \warning \c p must be not \c NULL.
 * \retval true If the phrase follows a phrase.
 * \retval false otherwise.
 */
bool wave_phrase_has_previous (const wave_phrase * p);

/**
 * \brief Get the collection within the phrase.
 * \param p Phrase.
 * \relatesalso wave_phrase
 * \warning \c p must be not \c NULL.
 * \return Underlying collection.
 */
wave_collection * wave_phrase_get_collection (const wave_phrase * p);

/**
 * \brief Get the next phrase.
 * \param p Phrase.
 * \relatesalso wave_phrase
 * \warning \c p must be not \c NULL.
 * \return Phrase.
 */
wave_phrase * wave_phrase_get_next (const wave_phrase * p);

/**
 * \brief Get the previous phrase.
 * \param p Phrase.
 * \relatesalso wave_phrase
 * \warning \c p must be not \c NULL.
 * \return Phrase.
 */
wave_phrase * wave_phrase_get_previous (const wave_phrase * p);

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Add a phrase
 * \param p Phrase.
 * \param next Phrase to add.
 * \relatesalso wave_phrase
 * \warning \c p must be not \c NULL.
 */
void wave_phrase_add_phrase (wave_phrase * p, wave_phrase * next);

/**
 * \brief Set the underlying collection.
 * \param p Phrase.
 * \param c Collection.
 * \relatesalso wave_phrase
 * \warning \c p must be not \c NULL.
 */
void wave_phrase_set_collection (wave_phrase * p, wave_collection * c);

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Print a wave_phrase to a stream.
 * \param stream Stream.
 * \param p Phrase.
 */
void wave_phrase_fprint (FILE * stream, const wave_phrase * p);

/**
 * \brief Print a wave_phrase to stdout.
 */
void wave_phrase_print (const wave_phrase * p);

#endif /* __WAVE_PHRASE_H__ */
