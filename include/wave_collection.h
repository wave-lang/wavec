/**
 * \file wave_collection.h
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
#ifndef __WAVE_COLLECTION_H__
#define __WAVE_COLLECTION_H__

#include <stdbool.h>

#include "atom.h"

////////////////////////////////////////////////////////////////////////////////
// Enums, Structs, Typedefs.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Collection types.
 */
typedef enum wave_collection_type
{
    WAVE_COLLECTION_ATOM,            /**<- Atom. */
    WAVE_COLLECTION_REP,             /**<- Rep. */
    WAVE_COLLECTION_SEQ,             /**<- Seq. */
    WAVE_COLLECTION_PAR,             /**<- Par. */
    WAVE_COLLECTION_CYCLIC_SEQ,      /**<- Cyclic seq. */
    WAVE_COLLECTION_CYCLIC_PAR       /**<- Cyclic par. */
} wave_collection_type;

typedef struct wave_collection
{
    wave_collection_type _type;                 /**<- Type. */
    union
    {
        wave_atom * _atom;                           /**<- Atom. */
        struct wave_collection * _list;         /**<- Seq or Par. */
        struct
        {
        struct wave_collection * _list;     /**<- List. */
        wave_path * _path;                  /**<- Repeated path. */
        } _repetition;                          /**<- Repetition. */
        struct
        {
            struct wave_collection * _list;     /**<- Normal collection. */
            struct wave_collection * _cycle;    /**<- Cycle collection. */
        } _cyclic;                              /**<- Cyclic repetition. */
    } _inner;                                   /**<- Inner. */
    struct wave_collection * _next_collection;  /**<- Next. */
} wave_collection;

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Allocator for collections.
 * \relatesalso wave_collection
 */
void * wave_collection_allocator (void);

/**
 * \brief Free a collection.
 * \param w Collection.
 * \relatesalso wave_collection
 */
void * wave_collection_free (wave_collection * w);

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Determine whether a collection has not reached its end yet.
 * param c Collection.
 * \relatesalso wave_collection
 */
bool wave_collection_has_next (const wave_collection * const c);

/**
 * \brief Get a collection's type.
 * \param c Collection
 * \return Collection type.
 * \relatesalso wave_collection
 */
wave_collection_type wave_collection_get_type (const wave_collection * const c);

/**
 * \brief Get a collection's atom.
 * \param c Collection.
 * \return Atom.
 * \relatesalso wave_collection
 */
wave_atom * wave_collection_get_atom (const wave_collection * const c);

/**
 * \brief Get a collection's list.
 * \param c Collection.
 * \return Collection.
 * \relatesalso wave_collection
 */
wave_collection * wave_collection_get_list (const wave_collection * const c);

/**
 * \brief Get a collection's repetition list.
 * \param c Collection.
 * \return Collection.
 * \relatesalso wave_collection
 */
wave_collection * wave_collection_get_repetition_list (const wave_collection * const c);

/**
 * \brief Get a collection's repetition path.
 * \param c Collection.
 * \return Path.
 * \relatesalso wave_collection
 */
wave_path * wave_collection_get_repetition_path (const wave_collection * const c);

/**
 * \brief Get a collection's cyclic list.
 * \param c Collection.
 * \return Collection.
 * \relatesalso wave_collection
 */
wave_collection * wave_collection_get_cyclic_list (const wave_collection * const c);

/**
 * \brief Get a collection's cycle.
 * \param c Collection.
 * \return Collection.
 * \relatesalso wave_collection
 */
wave_collection * wave_collection_get_cyclic_cycle (const wave_collection * const c);

/**
 * \brief Get the next collection.
 * \param c Collection.
 * \return Collection.
 * \relatesalso wave_collection
 */
wave_collection * wave_collection_get_next (const wave_collection * const c);

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Add a collection to a collection.
 * \param c Collection.
 * \param next Next.
 * \relatesalso wave_collection
 */
void wave_collection_add_collection (wave_collection * const c,
    wave_collection * const next);

/**
 * \brief Set a collection type.
 * \param[in,out] c Collection.
 * \param[in] t Type.
 * \relatesalso wave_collection
 */
void wave_collection_set_type (wave_collection * const c,
    wave_collection_type t);

/**
 * \brief Set the atom.
 * \param[in,out] c Collection.
 * \param[in] a Atom.
 * \relatesalso wave_collection
 */
void wave_collection_set_atom (wave_collection * const c, wave_atom * const a);

/**
 * \brief Set list.
 * \param[in,out] c Collection.
 * \param[in] list List.
 * \relatesalso wave_collection
 */
void wave_collection_set_list (wave_collection * const c,
    wave_collection * const list);

/**
 * \brief Set repetition list.
 * \param[in,out] c Collection.
 * \param[in] list List.
 * \relatesalso wave_collection
 */
void wave_collection_set_repetition_list (wave_collection * const c,
    wave_collection * const list);

/**
 * \brief Set repetition path.
 * \param[in,out] c Collection.
 * \param[in] p Path.
 * \relatesalso wave_collection
 */
void wave_collection_set_repetition_path (wave_collection * const c,
    wave_path * const p);

/**
 * \brief Set cyclic list.
 * \param[in,out] c Collection.
 * \param[in] list List.
 * \relatesalso wave_collection
 */
void wave_collection_set_cyclic_list (wave_collection * const c,
    wave_collection * const list);

/**
 * \brief Set cyclic cycle.
 * \param[in,out] c Collection.
 * \param[in] cycle Cycle.
 * \relatesalso wave_collection
 */
void wave_collection_set_cyclic_cycle (wave_collection * const c,
    wave_collection * const cycle);

#endif /* __WAVE_COLLECTION_H__ */
