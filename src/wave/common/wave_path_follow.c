/**
 * \file wave_path_follow.c
 * \brief Runtime path following.
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

#include "wave/common/wave_path_follow.h"

typedef enum _path_enum {
    PATH_PREVIOUS = 0,
    PATH_NEXT,
    PATH_UP,
    PATH_DOWN,
    PATH_REVERSE,
    PATH_OPARENT,
    PATH_CPARENT,
    PATH_OSQBRACKET,
    PATH_CSQBRACKET,
    PATH_UNKNOWN,
} _path_enum;

static char _path_symbol[] =
{
    [PATH_PREVIOUS  ] = 'p',
    [PATH_NEXT      ] = 's',
    [PATH_UP        ] = 'u',
    [PATH_DOWN      ] = 'd',
    [PATH_REVERSE   ] = 'r',
    [PATH_OPARENT   ] = '(',
    [PATH_CPARENT   ] = ')',
    [PATH_OSQBRACKET] = '[',
    [PATH_CSQBRACKET] = ']',
};

static wave_data* _goto_previous (wave_data* data){
    return data-1;
}

static wave_data* _goto_next (wave_data* data){
    return data+1;
}

static wave_data* _goto_up (wave_data* data){
    return data->up;
}

static wave_data* _goto_down (wave_data* data){
    if(data->_type == WAVE_DATA_SEQ || data->_type == WAVE_DATA_PAR)
        return data->_content._collection._tab;
    return NULL;
}

static wave_data* (* _follow_me []) (wave_data*) =
{
    [PATH_PREVIOUS  ] = _goto_previous,
    [PATH_NEXT      ] = _goto_next,
    [PATH_UP        ] = _goto_up,
    [PATH_DOWN      ] = _goto_down,
};

static inline wave_data* _follow_infinite_path(wave_data* data, char direction, size_t* path_size){
    path_size = 0;
}

typedef enum _path_type{
    PATH_SIMPLE = 0,
    PATH_NUMBER,
    PATH_INFINITE,
    PATH_PARENTHESES_SIMPLE,
    PATH_PARENTHESES_NUMBER,
    PATH_PARENTHESES_INFINITE,
    PATH_SQBRAQUETS_SIMPLE,
    PATH_SQBRACKETS_NUMBER,
    PATH_SQBRACKETS_INFINITE,
} _path_type;

static int _test_next_path_to_follow(wave_data* data, char* where_to_go){
    if(*where_to_go == _path_symbol[PATH_PREVIOUS] ||
            *where_to_go == _path_symbol[PATH_UP] ||
            *where_to_go == _path_symbol[PATH_DOWN] ||
            *where_to_go == _path_symbol[PATH_NEXT])
    {
        if(*(where_to_go+1) == '*')
            return PATH_INFINITE;                                                                         // Case simple path with infinite rep
        if(isdigit(*(where_to_go+1)))
            return PATH_NUMBER;                                                                           // Case simple path with integer rep
        return PATH_SIMPLE;                                                                               // Case simple path
    }
    if(*where_to_go == _path_symbol[PATH_OPARENT]){
        char* nextparenth = where_to_go+1;
        while(*nextparenth != _path_symbol[PATH_CPARENT] && *nextparenth != '\0')
            nextparenth++;
        if(isdigit(*(nextparenth+1)))
            return PATH_PARENTHESES_NUMBER;                                                                           // Case parentheses with repeat
        if(*(nextparenth+1) == '*')
            return PATH_PARENTHESES_INFINITE;                                                                           // Case parentheses with infinite repeat
        return PATH_PARENTHESES_SIMPLE;                                                                               // Case parentheses without repeat
    }
    if(*where_to_go ==_path_symbol[PATH_OSQBRACKET]){
        char* nextparenth = where_to_go+1;
        while(*nextparenth != _path_symbol[PATH_CSQBRACKET] && *nextparenth != '\0')
            nextparenth++;
        if(isdigit(*(nextparenth+1)))
            return PATH_SQBRACKETS_NUMBER;                                                                           // Case square brackets with repeat
        if(isdigit(*(nextparenth+1)))
            return PATH_SQBRACKETS_INFINITE;                                                                           // Case square brackets with infinite repeat
        return PATH_SQBRAQUETS_SIMPLE;                                                                               // Case square brackets without repeat
    }
}

//static 

wave_data* wave_follow_path(wave_data* data, char* where_to_go, int* size){
    *size = 0;
    _test_next_path_to_follow(data, where_to_go);
}
