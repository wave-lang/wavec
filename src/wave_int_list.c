/**
 * \file wave_int_list.c
 * \brief Wave int list.
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
#include "wave_int_list.h"

////////////////////////////////////////////////////////////////////////////////
// Allocation, free, copy.
////////////////////////////////////////////////////////////////////////////////

void * wave_int_list_alloc (void);
void wave_int_list_free (wave_int_list * list);
wave_int_list * wave_int_list_copy (const wave_int_list * list);

////////////////////////////////////////////////////////////////////////////////
// Getters.
////////////////////////////////////////////////////////////////////////////////

int wave_int_list_at (const wave_int_list * list, size_t i);
size_t wave_int_list_size (const wave_int_list * list);
bool wave_int_list_is_empty (const wave_int_list * list);

////////////////////////////////////////////////////////////////////////////////
// Modifiers.
////////////////////////////////////////////////////////////////////////////////

void wave_int_list_pop_back (wave_int_list * list);
void wave_int_list_pop_front (wave_int_list * list);
void wave_int_list_push_back (wave_int_list * list, int element);
void wave_int_list_push_front (wave_int_list * list, int element);
void wave_int_list_insert (wave_int_list * list, size_t i, int element);

