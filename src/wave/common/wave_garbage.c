/**
 * \file wave_garbage.c
 * \brief Wave garbage collector.
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
#include "wave/common/wave_garbage.h"

////////////////////////////////////////////////////////////////////////////////
// Static utilities.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Arbitrary step.
 */
static const size_t _WAVE_GC_SIZE_STEP = 128;

/**
 * \brief The garbage collector.
 */
static struct wave_garbage_collector _WAVE_GC =
{
    ._size = 0, ._count = 0, ._pointers = NULL,
};

/**
 * \brief Reset the garbage collector.
 */
static inline void _reset_gc (void)
{
    _WAVE_GC._size = 0;
    _WAVE_GC._count = 0;
    _WAVE_GC._pointers = NULL;
}

/**
 * \brief Grow the garbage collector.
 */
static inline void _grow_gc (void)
{
    size_t new_size = _WAVE_GC._size + _WAVE_GC_SIZE_STEP;
    void * new_list = realloc (_WAVE_GC._pointers, new_size);
    if (new_list != NULL)
    {
        _WAVE_GC._pointers = new_list;
        _WAVE_GC._size = new_size;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Allocation, etc.
////////////////////////////////////////////////////////////////////////////////

void * wave_garbage_alloc (size_t size)
{
    void * new_memory = malloc (size);
    wave_garbage_register (new_memory);
    return new_memory;
}

void wave_garbage_register (void * pointer)
{
    #pragma omp critical
    {
        if (_WAVE_GC._count >= _WAVE_GC._size)
            _grow_gc ();
        _WAVE_GC._pointers[_WAVE_GC._count] = pointer;
        _WAVE_GC._count++;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Cleaning, destroying.
////////////////////////////////////////////////////////////////////////////////

void wave_garbage_clean (void)
{
    #pragma omp critical
    {
        for (size_t i = 0; i < _WAVE_GC._count; ++i)
            free (_WAVE_GC._pointers[i]);
        _WAVE_GC._count = 0;
    }
}

void wave_garbage_destroy (void)
{
    wave_garbage_clean ();
    free (_WAVE_GC._pointers);
    _reset_gc ();
}
