/**
 * \file wave_path.h
 * \brief Wave path.
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
#ifndef __WAVE_MOVE_H__
#define __WAVE_MOVE_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * \defgroup wave_path_group Wave Path
 * \ingroup wave_ast_group
 */

////////////////////////////////////////////////////////////////////////////////
// Enums, Structs, Typedefs.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Move type.
 * \ingroup wave_path_group
 */
typedef enum wave_move_type
{
    WAVE_MOVE_UP = 0,    /**< Up. */
    WAVE_MOVE_DOWN,      /**< Down. */
    WAVE_MOVE_PRE,       /**< Predecesor. */
    WAVE_MOVE_SUC,       /**< Successor. */
    WAVE_MOVE_REWIND,    /**< Rewind. */
    WAVE_MOVE_PART,      /**< Part. */
    WAVE_MOVE_REP,       /**< Repeat. */
    WAVE_MOVE_UNKNOWN,   /**< Unknown. */
} wave_move_type;

/**
 * \brief Repeat type.
 * \ingroup wave_path_group
 */
typedef enum wave_path_repeat_type
{
    WAVE_PATH_REPEAT_CONSTANT = 0,  /**< Constant. */
    WAVE_PATH_REPEAT_INFINITE       /**< Infinite. */
} wave_path_repeat_type;

/**
 * \brief Wave path.
 * \warning Paths not obtained using wave_path_alloc() must be initialized using wave_path_init() !
 * \ingroup wave_path_group
 *
 * Wave paths are used to represent paths.
 *
 * Internally, paths are stored as trees: a wave_path is an element
 * which is linked to its predecessor, if any, and its successor, if any. This
 * element can either hold a “simple” move, or a path and additionnal
 * information.
 *
 * # Path creation and destruction
 * A path can be dynamically created using wave_path_alloc(). It must be free
 * with wave_path_free().
 *
 * # Moves
 * In order to know the move type of the current path element, one must use
 * wave_path_get_move().
 *
 * Wave move type       | Move
 * ---------------------|------------------
 * #WAVE_MOVE_UP        | Upper collection
 * #WAVE_MOVE_DOWN      | Down collection
 * #WAVE_MOVE_PRE       | Predecessor
 * #WAVE_MOVE_SUC       | Successor
 * #WAVE_MOVE_REWIND    | Rewind
 * #WAVE_MOVE_PART      | Part
 * #WAVE_MOVE_REP       | Repetition
 * #WAVE_MOVE_UNKNOWN   | Nothing
 *
 * ## Simple moves
 * #WAVE_MOVE_UP, #WAVE_MOVE_DOWN, #WAVE_MOVE_PRE and #WAVE_MOVE_SUC are
 * considered simple.
 *
 * ## Rewind
 * Though a bit special, #WAVE_MOVE_REWIND is also considered as “simple”
 * (meaning that, when encountering a #WAVE_MOVE_REWIND, no more should be done
 * with the current path element).
 *
 * ## Part
 * #WAVE_MOVE_PART denotes a path that should be saved for later use along a
 * #WAVE_MOVE_REWIND. Since the path can contain several moves, it is stored
 * inside the element and can be accessed with wave_path_get_part().
 *
 * ## repetitions
 * #WAVE_MOVE_REP symbolizes paths that are repeated.
 *
 * ### repetition type
 * There are two types of repetitions:
 *
 * Move repetition              | Meaning
 * -----------------------------|--------------------------------------
 * #WAVE_PATH_REPEAT_CONSTANT   | Repeat a finite number of times.
 * #WAVE_PATH_REPEAT_INFINITE   | Repeat until nothing can be accessed
 *
 * To know the repetition type, one must use wave_path_get_repeat_type().
 *
 * For instance, the following path falls in the #WAVE_PATH_REPEAT_INFINITE
 * category:
 *
 *      s *
 *
 * It means that when following the path, one should keep going to the successor
 * of the current collection until there is no more successor.
 *
 * ### Repeated path.
 * The path that shall be repeated can be accessed using
 * wave_path_get_repeat_path();
 *
 * ### Constant repeat
 * For #WAVE_PATH_REPEAT_CONSTANT repeated paths, one must get the number of
 * times the path will be repeated using wave_path_get_repeat_number().
 *
 * # Path iteration
 * Since paths are stored as trees, one must process the current path element,
 * and then process all of its successors. The immediate successor can be
 * obtained using wave_path_get_next().
 * If needed, predecessors can be attained with wave_path_get_previous().
 *
 * It is highly recommended to first ascertain that an element has a successor
 * (respectively a predecessor) using wave_path_has_next() (respectively
 * wave_path_has_previous()) before calling wave_path_get_next() (respectively
 * wave_path_get_previous()).
 *
 * \sa wave_path_repeat_type, wave_move_type
 */
typedef struct wave_path
{
    wave_move_type _move;                   /**< Move. */
    union
    {
        struct wave_path * _part;           /**< Part. */
        struct
        {
            wave_path_repeat_type _type;    /**< Repeat type. */
            int _number;                    /**< Repeat number. */
            struct wave_path * _path;       /**< Path to repeat. */
        } _repeat;                          /**< Repeat. */
    } _complex_move;                        /**< Complex move. */
    struct wave_path * _next_path;          /**< Next move. */
    struct wave_path * _previous_path;      /**< Previous move. */
} wave_path;

////////////////////////////////////////////////////////////////////////////////
// Initialization.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Initialize a wave_path.
 * \param p Path.
 * \relatesalso wave_path
 */
void wave_path_init (wave_path * p);

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Alloc for Wave paths.
 * \return Wave path
 * \relatesalso wave_path
 * \note Paths obtained using wave_path_alloc() are already initialized, it is not needed to use wave_path_init().
 */
void * wave_path_alloc (void);

/**
 * \brief Free wave paths.
 * \param p Path.
 * \return NULL
 * \relatesalso wave_path
 */
void * wave_path_free (wave_path * p);

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Determine whether a wave path has a next move.
 * \param p Path.
 * \retval true If the path still has a move.
 * \retval false If the path has ended.
 * \relatesalso wave_path
 * \warning \c must be not \c NULL.
 */
bool wave_path_has_next (const wave_path * p);

/**
 * \brief Determine whether a wave path has a previous move.
 * \param p Path.
 * \retval true If the path has a previous move.
 * \retval false If this is the start.
 * \relatesalso wave_path
 * \warning \c must be not \c NULL.
 */
bool wave_path_has_previous (const wave_path * p);

/**
 * \brief Get a move.
 * \param p Path.
 * \return Move type.
 * \relatesalso wave_path
 * \warning \c must be not \c NULL.
 */
wave_move_type wave_path_get_move (const wave_path * p);

/**
 * \brief Get a path's part.
 * \param p Path.
 * \return Part.
 * \relatesalso wave_path
 * \warning \c must be not \c NULL.
 */
wave_path * wave_path_get_part (const wave_path * p);

/**
 * \brief Get a path's repeat type.
 * \param p Path.
 * \return Repeat type.
 * \relatesalso wave_path
 * \warning \c must be not \c NULL.
 */
wave_path_repeat_type wave_path_get_repeat_type (const wave_path * p);

/**
 * \brief Get a path's repeat number.
 * \param p Path.
 * \return Number.
 * \relatesalso wave_path
 * \warning \c must be not \c NULL.
 */
int wave_path_get_repeat_number (const wave_path * p);

/**
 * \brief Get path's repeat path.
 * \param p Path.
 * \return Path.
 * \relatesalso wave_path
 * \warning \c must be not \c NULL.
 */
wave_path * wave_path_get_repeat_path (const wave_path * p);

/**
 * \brief Get the next path.
 * \param p Path.
 * \return Next.
 * \relatesalso wave_path
 * \warning \c must be not \c NULL.
 */
wave_path * wave_path_get_next (const wave_path * p);

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Set a path move.
 * \param[in,out] p Path.
 * \param[in] m Move type.
 * \relatesalso wave_path
 * \warning \c must be not \c NULL.
 */
void wave_path_set_move (wave_path * p, wave_move_type m);

/**
 * \brief Add a path to another path.
 * \param[in,out] p
 * \param[in] next
 * \relatesalso wave_path
 * \warning \c must be not \c NULL.
 */
void wave_path_add_path (wave_path * p, wave_path * next);

/**
 * \brief Set a path's part.
 * \param[in,out] p Path.
 * \param[in] part Part.
 * \relatesalso wave_path
 * \warning \c must be not \c NULL.
 * \post wave_path_get_type() == #WAVE_MOVE_PART
 */
void wave_path_set_part (wave_path * p, wave_path * part);

/**
 * \brief Set a path's repeat type.
 * \param[in,out] p Path.
 * \param[in] t Type.
 * \relatesalso wave_path
 * \warning \c must be not \c NULL.
 * \post wave_path_get_type() == #WAVE_MOVE_REP
 */
void wave_path_set_repeat_type (wave_path * p, wave_path_repeat_type t);

/**
 * \brief Set a path's repeat number.
 * \param[in,out] p Path.
 * \param[in] n Number.
 * \relatesalso wave_path
 * \warning \c must be not \c NULL.
 * \post wave_path_get_type() == #WAVE_MOVE_REP
 * \post wave_path_get_repeat_type() == #WAVE_PATH_REPEAT_CONSTANT
 */
void wave_path_set_repeat_number (wave_path * p, int n);

/**
 * \brief Set a path's repetition.
 * \param[in,out] p Path.
 * \param[in] repeat Repat.
 * \relatesalso wave_path
 * \warning \c must be not \c NULL.
 * \post wave_path_get_type() == #WAVE_MOVE_REP
 */
void wave_path_set_repeat_path (wave_path * p, wave_path * repeat);

////////////////////////////////////////////////////////////////////////////////
// Printing.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Print a wave_path to a stream.
 * \param stream Stream.
 * \param p Path.
 */
void wave_path_fprint (FILE * stream, const wave_path * p);

/**
 * \brief Print a wave_path to \c stdout.
 */
void wave_path_print (const wave_path * p);

#endif /* __WAVE_MOVE_H__ */
