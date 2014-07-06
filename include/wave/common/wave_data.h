/**
 * \file wave_data.h
 * \brief Wave data.
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
#ifndef __WAVE_DATA_H__
#define __WAVE_DATA_H__

#include "sysexits.h"

#include "wave/common/wave_types.h"
#include "wave/common/wave_operator.h"
#include "wave/common/wave_garbage.h"

/**
 * \class wave_data_type
 * \brief Used inside the \c wave_data structure to know wich data is being stored inside.
 * \see wave_types.h
 */
typedef enum wave_data_type{
    WAVE_DATA_INT = 0,          /**< An integer value */
    WAVE_DATA_FLOAT,            /**< A floating point value */
    WAVE_DATA_CHAR,             /**< A character value */
    WAVE_DATA_STRING,           /**< A string value */
    WAVE_DATA_BOOL,             /**< A boolean value */
    WAVE_DATA_SEQ,              /**< A sequential collection. */
    WAVE_DATA_PAR,              /**< A parallel collection. */
    WAVE_DATA_OPERATOR,         /**< An operator */
    WAVE_DATA_UNKNOWN,          /**< Used when no type is set yet */
} wave_data_type;

typedef enum wave_function_type{
    FUNCTION_UNARY = 0,
    FUNCTION_BINARY,
} wave_function_type;

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
        struct
        {
            union{
                void (*fun_binary)(const struct wave_data*, const struct wave_data*, struct wave_data*);
                void (*fun_unary)(const struct wave_data*, struct wave_data*);
            } _fun;
            wave_function_type type;
        } _function;
    } _content;                     /**< The union to store multiple data values */
    size_t _index;
    struct wave_data * _up;          /**< The upper wave_data */
} wave_data;

wave_data_type wave_data_get_type (const wave_data * data);

void wave_data_set_int (wave_data * data, wave_int i);

void wave_data_set_float (wave_data * data, wave_float f);

void wave_data_set_char (wave_data * data, wave_char c);

void wave_data_set_bool (wave_data * data, wave_bool b);

void wave_data_set_string (wave_data * data, wave_string s);

wave_int wave_data_get_int (const wave_data * data);

wave_float wave_data_get_float (const wave_data * data);

wave_char wave_data_get_char (const wave_data * data);

wave_string wave_data_get_string (const wave_data * data);

wave_bool wave_data_get_bool (const wave_data * data);

void wave_data_unary (const wave_data * operand, wave_data * result, wave_operator op);

void wave_data_binary (const wave_data * left, const wave_data * right, wave_data * result, wave_operator op);

wave_bool wave_data_is_atom (const wave_data * data);

static inline int wave_data_get_collection_size(wave_data* data){
    if(data->_type == WAVE_DATA_SEQ || data->_type == WAVE_DATA_PAR)
        return data->_content._collection._size;
    return -1;
}

void wave_data_fprint (FILE * stream, const wave_data * data);

#endif /* __WAVE_DATA_H__ */
