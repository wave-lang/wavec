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
 * \brief Wave data type.
 */
typedef enum wave_data_type{
    WAVE_DATA_INT = 0,
    WAVE_DATA_FLOAT,
    WAVE_DATA_CHAR,
    WAVE_DATA_STRING,
    WAVE_DATA_BOOL,
    WAVE_DATA_UNKNOWN,
} wave_data_type;

/**
 * \brief Wave data.
 */
typedef struct wave_data{
    wave_data_type _type;       /**< Type. */
    union{
        wave_int _int;          /**< Int. */
        wave_float _float;      /**< Float. */
        wave_char _char;        /**< Char. */
        wave_string _string;    /**< String. */
        wave_bool _bool;        /**< Bool. */
    } _content;                 /**< Content. */
} wave_data;

#endif // ( __WAVE8STRUCT_DEF_H__ )
