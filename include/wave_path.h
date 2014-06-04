/**
 * \file wave_path.h
 * \brief Wave PATH.
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
#ifndef __WAVE_MOVE_H__
#define __WAVE_MOVE_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
// Enums, Structs, Typedefs.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Move type.
 */
typedef enum wave_move_type
{
    WAVE_MOVE_UP,        /**<- Up. */
    WAVE_MOVE_DOWN,      /**<- Down. */
    WAVE_MOVE_PRE,       /**<- Predecesor. */
    WAVE_MOVE_SUC,       /**<- Successor. */
    WAVE_MOVE_REWIND,    /**<- Rewind. */
    WAVE_MOVE_PART,      /**<- Part. */
    WAVE_MOVE_REP,       /**<- Repeat. */
    WAVE_MOVE_UNKNOWN,   /**<- Unknown. */
} wave_move_type;

/**
 * \brief Repeat value type.
 */
typedef enum repeat_value_type
{
    REPEAT_VALUE_CONSTANT,      /**<- Constant. */
    REPEAT_VALUE_INFINITE       /**<- Infinite. */
} repeat_value_type;

/**
 * \brief Wave path.
 */
typedef struct wave_path
{
    wave_move_type _move;                   /**<- Move. */
    union
    {
        struct wave_path * _part;           /**<- Part. */
        struct
        {
            repeat_value_type _type;        /**<- Repeat type. */
            unsigned int _number;           /**<- Repeat number. */
            struct wave_path * _path;       /**<- Path to repeat. */
        } _repeat;                          /**<- Repeat. */
    } _complex_move;                        /**<- Complex move. */
    struct wave_path * _next_path;          /**<- Next move. */
} wave_path;

////////////////////////////////////////////////////////////////////////////////
// Allocation, free.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Allocator for Wave paths.
 * \return Wave path
 * \relatesalso wave_path
 */
void * wave_path_allocator (void);

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
 */
bool wave_path_has_next (const wave_path * p);

/**
 * \brief Get a move.
 * \param p Path.
 * \return Move type.
 * \relatesalso wave_path
 */
wave_move_type wave_path_get_move (const wave_path * const p);

/**
 * \brief Get a path's part.
 * \param p Path.
 * \return Part.
 * \relatesalso wave_path
 */
wave_path * wave_path_get_part (wave_path * const p);

/**
 * \brief Get a path's repeat type.
 * \param p Path.
 * \return Repeat type.
 * \relatesalso wave_path
 */
repeat_value_type wave_path_get_repeat_type (wave_path * const p);

/**
 * \brief Get a path's repeat number.
 * \param p Path.
 * \return Number.
 * \relatesalso wave_path
 */
unsigned int wave_path_get_repeat_number (wave_path * const p);

/**
 * \brief Get path's repeat path.
 * \param p Path.
 * \return Path.
 * \relatesalso wave_path
 */
wave_path * wave_path_get_repeat_path (wave_path * const p);

/**
 * \brief Get the next path.
 * \param p Path.
 * \return Next.
 * \relatesalso wave_path
 */
wave_path * wave_path_get_next (wave_path * const p);

////////////////////////////////////////////////////////////////////////////////
// Setters.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Set a path move.
 * \param[in,out] p Path.
 * \param[in] m Move type.
 * \relatesalso wave_path
 */
void wave_path_set_move (wave_path * const p, wave_move_type m);

/**
 * \brief Add a path to another path.
 * \param[in,out] p
 * \param[in] next
 * \relatesalso wave_path
 */
void wave_path_add_path (wave_path * const p, wave_path * const next);

/**
 * \brief Set a path's part.
 * \param[in,out] p Path.
 * \param[in] part Part.
 * \relatesalso wave_path
 */
void wave_path_set_part (wave_path * const p, wave_path * const part);

/**
 * \brief Set a path's repeat type.
 * \param[in,out] p Path.
 * \param[in] t Type.
 * \relatesalso wave_path
 */
void wave_path_set_repeat_type (wave_path * const p, repeat_value_type t);

/**
 * \brief Set a path's repeat number.
 * \param[in,out] p Path.
 * \param[in] n Number.
 * \relatesalso wave_path
 */
void wave_path_set_repeat_number (wave_path * const p, unsigned int n);

/**
 * \brief Set a path's repetition.
 * \param[in,out] p Path.
 * \param[in] repeat Repat.
 * \relatesalso wave_path
 */
void wave_path_set_repeat_path (wave_path * const p, wave_path * const repeat);

#endif /* __WAVE_MOVE_H__ */
