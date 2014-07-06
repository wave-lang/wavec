/**
 * \file wave_garbage.h
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
#ifndef __WAVE_GARBAGE_H__
#define __WAVE_GARBAGE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * \brief Basic garbage collector.
 *
 * wave_garbage_collector is a very basic garbage collector for Wave programs.
 * One can either:
 * - wave_garbage_alloc(): Allocate memory which will be automatically registered.
 * - wave_garbage_register(): Register memory inside the garbage collector.
 *
 * It is up to the user to clean or destroy the garbage collector:
 * - wave_garbage_clean()
 * - wave_garbage_destroy()
 *
 * The main difference between wave_garbage_clean() and wave_garbage_destroy()
 * is the fact that the former frees the registered memory but keeps the garbage
 * collector's internal storage while the latter frees both the registered
 * memory and the internal storage.
 * Thus, it is advised to call:
 * - wave_garbage_clean(): during the lifetime of the program.
 * - wave_garbage_destroy(): at the end of the program.
 */
typedef struct wave_garbage_collector
{
    size_t _size;                 /*< Current size of the GC. */
    size_t _count;                /*< Count of currently registered pointers. */
    void ** _pointers;            /*< Registered pointers. */
} wave_garbage_collector;

/**
 * \brief Allocate memory and directly register it.
 * \param size Size requested.
 * \return A pointer to the new memory.
 * \warning Do not free this memory ! It will be freed on a call to
 * wave_garbage_clean() or wave_garbage_destroy().
 *
 * The two following examples are equivalent:
 *     // First version.
 *     void * pointer = wave_garbage_alloc (size);
 *     // Second version.
 *     void * pointer = malloc (size);
 *     wave_garbage_register (pointer);
 */
void * wave_garbage_alloc (size_t size);

/**
 * \brief Register a pointer in the GC
 * \param pointer Pointer to register.
 * \warning Do not free this memory ! It will be freed on a call to
 * wave_garbage_clean() or wave_garbage_destroy().
 *
 * Once a pointer is registered, it is not necessary to free the pointed memory
 * (and it is very strongly advised not to).
 */
void wave_garbage_register (void * pointer);

/**
 * \brief Clean and free the registered memory.
 * \note The garbage collector will keep its internal storage.
 *
 */
void wave_garbage_clean (void);

/**
 * \brief Clean and destroy the garbage collector.
 * \note The garbage collector will destroy its internal storage.
 *
 * If the garbage collector will still be needed afterwards, it is advised to
 * used wave_garbage_clean() instead of wave_garbage_destroy().
 */
void wave_garbage_destroy (void);

#endif /* __WAVE_GARBAGE_H__ */
