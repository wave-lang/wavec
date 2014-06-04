/**
 * \file test_ast_print.c
 * \brief Test AST print.
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "wave_path.h"
#include "wave_atom.h"
#include "wave_collection.h"

static wave_path * p[9];

static int _init_path (void)
{
    p[0] = wave_path_allocator ();
    for (int i = 1; i < 6; ++i)
    {
        p[i] = wave_path_allocator ();
        wave_path_add_path (p[0], p[i]);
    }
    for (int i = 6; i < 9; ++i)
        p[i] = wave_path_allocator ();

    wave_path_set_move (p[0], WAVE_MOVE_UP);
    wave_path_set_move (p[1], WAVE_MOVE_DOWN);
    wave_path_set_move (p[2], WAVE_MOVE_PART);
    wave_path_set_move (p[3], WAVE_MOVE_SUC);
    wave_path_set_move (p[4], WAVE_MOVE_DOWN);
    wave_path_set_move (p[5], WAVE_MOVE_REWIND);

    wave_path_set_part (p[2], p[6]);
    wave_path_add_path (p[6], p[7]);
    wave_path_add_path (p[6], p[8]);
    wave_path_set_move (p[6], WAVE_MOVE_UP);
    wave_path_set_move (p[7], WAVE_MOVE_DOWN);
    wave_path_set_move (p[8], WAVE_MOVE_PRE);
}

static int _init_atom (void)
{
    return 0;
}

static int _init_collection (void)
{
    return 0;
}

static int _init (void)
{
    _init_path ();
    _init_atom ();
    _init_collection ();
    return 0;
}

static int _clean_path (void)
{
    wave_path_free (p[0]);
}

static int _clean_atom (void)
{
    return 0;
}

static int _clean_collection (void)
{
    return 0;
}

static int _clean (void)
{
    _clean_path ();
    _clean_atom ();
    _clean_collection ();
    return 0;
}

static void print_path (void)
{
    wave_path_print (p[0]);
    printf ("\n");
}

int main (int argc, char ** argv)
{
    _init ();

    print_path ();

    _clean ();

    return 0;
}
