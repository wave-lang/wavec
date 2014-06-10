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

#include "wave_atom.h"

////////////////////////////////////////////////////////////////////////////////
// Enums, Structs, Typedefs.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Collection types.
 */
typedef enum wave_collection_type
{
    WAVE_COLLECTION_ATOM = 0,       /**<- Atom. */
    WAVE_COLLECTION_REP,            /**<- Rep. */
    WAVE_COLLECTION_SEQ,            /**<- Seq. */
    WAVE_COLLECTION_PAR,            /**<- Par. */
    WAVE_COLLECTION_CYCLIC_SEQ,     /**<- Cyclic seq. */
    WAVE_COLLECTION_CYCLIC_PAR,     /**<- Cyclic par. */
    WAVE_COLLECTION_UNKNOWN,        /**<- Unknown. */
} wave_collection_type;

/**
 * \brief Wave collection repetition types.
 */
typedef enum wave_collection_repetition_type
{
    WAVE_COLLECTION_REPETITION_CONSTANT = 0,    /**<- Constant. */
    WAVE_COLLECTION_REPETITION_PATH,            /**<- Path. */
    WAVE_COLLECTION_REPETITION_UNKNOWN,         /**<- Unknown. */
} wave_collection_repetition_type;

/**
 * \brief Collection.
 * \warning Collections not obtained with wave_collection_alloc() must be initialized using wave_collection_init() !
 */
typedef struct wave_collection
{
    wave_collection_type _type;                     /**<- Type. */
    union
    {
        wave_atom * _atom;                          /**<- Atom. */
        struct wave_collection * _list;             /**<- Seq or Par. */
        struct
        {
            wave_collection_repetition_type _type;  /**<- Repetition type. */
            struct wave_collection * _list;         /**<- List. */
            union
            {
                wave_path * _path;                  /**<- Repeated path. */
                unsigned int _times;                /**<- Repetition number. */
            } _description;                         /**<- Reptition description. */
        } _repetition;                              /**<- Repetition. */
        struct
        {
            struct wave_collection * _list;         /**<- Normal collection. */
            struct wave_collection * _cycle;        /**<- Cycle collection. */
        } _cyclic;                                  /**<- Cyclic repetition. */
    } _inner;                                       /**<- Inner. */
    struct wave_collection * _next_collection;      /**<- Next. */
    struct wave_collection * _previous_collection;  /**<- Previous. */
} wave_collection;

////////////////////////////////////////////////////////////////////////////////
// Initialization.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Initialize a wave_collection.
 * \param c Collection.
 * \relatesalso wave_collection
 */
void wave_collection_init (wave_collection * c);

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Alloc for collections.
 * \relatesalso wave_collection
 * \note Collections obtained using wave_collection_alloc() are already initialized. It is not necessary to use wave_collection_init().
 */
void * wave_collection_alloc (void);

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
 * \param c Collection.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 * \retval true if the collection has not yet ended.
 * \retval false otherwise.
 */
bool wave_collection_has_next (const wave_collection * c);

/**
 * \brief Determine whether a collection has not reached its end yet.
 * \param c Collection.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 * \retval true if the collection is not the start.
 * \retval false otherwise.
 */
bool wave_collection_has_previous (const wave_collection * c);

/**
 * \brief Get a collection's type.
 * \param c Collection
 * \return Collection type.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 */
wave_collection_type wave_collection_get_type (const wave_collection * c);

/**
 * \brief Get a collection's atom.
 * \param c Collection.
 * \return Atom.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 */
wave_atom * wave_collection_get_atom (const wave_collection * c);

/**
 * \brief Get a collection's list.
 * \param c Collection.
 * \return Collection.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 */
wave_collection * wave_collection_get_list (const wave_collection * c);

/**
 * \brief Get a collection's repetition list.
 * \param c Collection.
 * \return Collection.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 */
wave_collection * wave_collection_get_repetition_list (const wave_collection * c);

/**
 * \brief Get a collection's repetition type.
 * \param c Collection
 * \return Repetition type.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 */
wave_collection_repetition_type wave_collection_get_repetition_type (const wave_collection * c);

/**
 * \brief Get a collection's repetition path.
 * \param c Collection.
 * \return Path.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 */
wave_path * wave_collection_get_repetition_path (const wave_collection * c);

/**
 * \brief Get a collection's repetition number.
 * \param c Collection.
 * \return Repetition number.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 */
unsigned int wave_collection_get_repetition_times (const wave_collection * c);

/**
 * \brief Get a collection's cyclic list.
 * \param c Collection.
 * \return Collection.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 */
wave_collection * wave_collection_get_cyclic_list (const wave_collection * c);

/**
 * \brief Get a collection's cycle.
 * \param c Collection.
 * \return Collection.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 */
wave_collection * wave_collection_get_cyclic_cycle (const wave_collection * c);

/**
 * \brief Get the next collection.
 * \param c Collection.
 * \return Collection.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 */
wave_collection * wave_collection_get_next (const wave_collection * c);

/**
 * \brief Get the previous collection.
 * \param c Collection.
 * \return Collection.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 */
wave_collection * wave_collection_get_previous (const wave_collection * c);

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Add a collection to a collection.
 * \param c Collection.
 * \param next Next.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 */
void wave_collection_add_collection (wave_collection * c, wave_collection * next);

/**
 * \brief Set a collection type.
 * \param[in,out] c Collection.
 * \param[in] t Type.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 */
void wave_collection_set_type (wave_collection * c, wave_collection_type t);

/**
 * \brief Set the atom.
 * \param[in,out] c Collection.
 * \param[in] a Atom.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 * \post wave_collection_get_type() == #WAVE_COLLECTION_ATOM
 */
void wave_collection_set_atom (wave_collection * c, wave_atom * a);

/**
 * \brief Set seq list.
 * \param[in,out] c Collection.
 * \param[in] list List.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 * \post wave_collection_get_type() == #WAVE_COLLECTION_SEQ
 */
void wave_collection_set_seq_list (wave_collection * c, wave_collection * list);

/**
 * \brief Set seq list.
 * \param[in,out] c Collection.
 * \param[in] list List.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 * \post wave_collection_get_type() == #WAVE_COLLECTION_PAR
 */
void wave_collection_set_par_list (wave_collection * c, wave_collection * list);

/**
 * \brief Set the repetition type.
 * \param[in,out] c Collection.
 * \param[in] t Repetition type.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 * \post wave_collection_get_type() == #WAVE_COLLECTION_REP
 */
void wave_collection_set_repetition_type (wave_collection * c, wave_collection_repetition_type t);

/**
 * \brief Set repetition list.
 * \param[in,out] c Collection.
 * \param[in] list List.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 * \post wave_collection_get_type() == #WAVE_COLLECTION_REP
 */
void wave_collection_set_repetition_list (wave_collection * c, wave_collection * list);

/**
 * \brief Set the repetition number.
 * \param[in,out] c Collection.
 * \param[in] times Times.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 * \post wave_collection_get_type() == #WAVE_COLLECTION_REP
 * \post wave_collection_get_repetition_type() == #WAVE_COLLECTION_REPETITION_CONSTANT
 */
void wave_collection_set_repetition_times (wave_collection * c, unsigned int times);

/**
 * \brief Set repetition path.
 * \param[in,out] c Collection.
 * \param[in] p Path.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 * \post wave_collection_get_type() == #WAVE_COLLECTION_REP
 * \post wave_collection_get_repetition_type() == #WAVE_COLLECTION_REPETITION_PATH
 */
void wave_collection_set_repetition_path (wave_collection * c, wave_path * p);

/**
 * \brief Set cyclic seq list.
 * \param[in,out] c Collection.
 * \param[in] list List.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 */
void wave_collection_set_cyclic_seq_list (wave_collection * c, wave_collection * list);

/**
 * \brief Set cyclic seq cycle.
 * \param[in,out] c Collection.
 * \param[in] cycle Cycle.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 */
void wave_collection_set_cyclic_seq_cycle (wave_collection * c, wave_collection * cycle);

/**
 * \brief Set cyclic par list.
 * \param[in,out] c Collection.
 * \param[in] list List.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 */
void wave_collection_set_cyclic_par_list (wave_collection * c, wave_collection * list);

/**
 * \brief Set cyclic par cycle.
 * \param[in,out] c Collection.
 * \param[in] cycle Cycle.
 * \relatesalso wave_collection
 * \warning \c c must be not \c NULL.
 */
void wave_collection_set_cyclic_par_cycle (wave_collection * c, wave_collection * cycle);

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Print a wave_collection to a stream.
 * \param stream Stream.
 * \param c Collection
 */
void wave_collection_fprint (FILE * stream, const wave_collection * c);

/**
 * \brief Print a wave_collection to \c stdout.
 * \param c Collection.
 */
void wave_collection_print (const wave_collection * c);

#endif /* __WAVE_COLLECTION_H__ */
