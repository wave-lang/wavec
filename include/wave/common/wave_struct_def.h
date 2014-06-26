/**
 * \file wave_struct_def.h
 * \brief Wave struct def.
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
#ifndef __WAVE_STRUCT_DEF_H__
#define __WAVE_STRUCT_DEF_H__

#include "wave/common/wave_types.h"

/**
 * \class wave_data_type
 * \brief Used inside the \c wave_data structure to know wich data is being stored inside.
 * \see wave_types.h
 */
typedef enum wave_data_type{
    WAVE_DATA_INT = 0,          /**< A integer value */
    WAVE_DATA_FLOAT,            /**< A floating point value */
    WAVE_DATA_CHAR,             /**< A character value */
    WAVE_DATA_STRING,           /**< A string value */
    WAVE_DATA_BOOL,             /**< A boolean value */
    WAVE_DATA_SEQ,              /**< A sequential collection. */
    WAVE_DATA_PAR,              /**< A parallel collection. */
    WAVE_DATA_UNKNOWN,          /**< Used when no type is set yet */
} wave_data_type;

/**
 * \brief The data structure used for the storage of the wave data types.
 * \see wave_types.h
 */
typedef struct wave_data{
    wave_data_type _type;           /**< The type of the current data */
    union{
        wave_int _int;              /**< To store an integer value */
        wave_float _float;          /**< To store an floating point value */
        wave_char _char;            /**< To store a character value */
        wave_string _string;        /**< To store a string value */
        wave_bool _bool;            /**< To store a boolean value */
        struct
        {
            struct wave_data * _tab;
            size_t _size;
        } _collection;
    } _content;                     /**< The union to store multiple data values */
} wave_data;

#endif // ( __WAVE8STRUCT_DEF_H__ )
