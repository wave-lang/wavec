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

/**
 * \brief Path number.
 */
#define _PATH_NUMBER 13

/**
 * \brief Atom number.
 */
#define _ATOM_NUMBER 8

/**
 * \brief Collection number.
 */
#define _COLLECTION_NUMBER 11

static wave_path * p[_PATH_NUMBER];
static wave_atom * a[_ATOM_NUMBER];
static wave_collection * c[_COLLECTION_NUMBER];

static int _init_path (void)
{
    for (unsigned int i = 0; i < _PATH_NUMBER; ++i)
        p[i] = wave_path_alloc ();

    for (unsigned int i = 1; i < 6; ++i)
        wave_path_add_path (p[0], p[i]);

    for (unsigned int i = 7; i < 9; ++i)
        wave_path_add_path (p[6], p[i]);

    for (unsigned int i = 10; i < 13; ++i)
        wave_path_add_path (p[9], p[i]);

    wave_path_set_move (p[0], WAVE_MOVE_UP);
    wave_path_set_move (p[1], WAVE_MOVE_DOWN);
    wave_path_set_move (p[2], WAVE_MOVE_PART);
    wave_path_set_move (p[3], WAVE_MOVE_SUC);
    wave_path_set_move (p[4], WAVE_MOVE_DOWN);
    wave_path_set_move (p[5], WAVE_MOVE_REWIND);

    wave_path_set_part (p[2], p[6]);
    wave_path_set_move (p[6], WAVE_MOVE_UP);
    wave_path_set_move (p[7], WAVE_MOVE_DOWN);
    wave_path_set_move (p[8], WAVE_MOVE_PRE);

    wave_path_set_move (p[9], WAVE_MOVE_UP);
    wave_path_set_move (p[10], WAVE_MOVE_UP);
    wave_path_set_move (p[11], WAVE_MOVE_PRE);
    wave_path_set_move (p[12], WAVE_MOVE_DOWN);

    return 0;
}

static int _init_atom (void)
{
    for (unsigned int i = 0; i < _ATOM_NUMBER; ++i)
        a[i] = wave_atom_alloc ();

    wave_atom_set_int (a[0], 10);
    wave_atom_set_float (a[1], 0.2f);
    wave_atom_set_bool (a[2], true);
    wave_atom_set_char (a[3], 'a');
    wave_atom_set_string (a[4], "abcde");
    wave_atom_set_operator (a[5], WAVE_OP_BINARY_PLUS);
    wave_atom_set_operator (a[6], WAVE_OP_BINARY_MINUS);
    wave_atom_set_path (a[7], p[0]);

    return 0;
}

static int _init_collection (void)
{
    for (unsigned int i = 0; i < _COLLECTION_NUMBER; ++i)
        c[i] = wave_collection_alloc ();

    wave_collection_set_type (c[0], WAVE_COLLECTION_SEQ);
    wave_collection_set_type (c[1], WAVE_COLLECTION_ATOM);
    wave_collection_set_type (c[2], WAVE_COLLECTION_ATOM);
    wave_collection_set_type (c[3], WAVE_COLLECTION_PAR);
    wave_collection_set_type (c[4], WAVE_COLLECTION_ATOM);
    wave_collection_set_type (c[5], WAVE_COLLECTION_ATOM);
    wave_collection_set_type (c[6], WAVE_COLLECTION_ATOM);
    wave_collection_set_type (c[7], WAVE_COLLECTION_REP);
    wave_collection_set_type (c[8], WAVE_COLLECTION_SEQ);
    wave_collection_set_type (c[9], WAVE_COLLECTION_ATOM);
    wave_collection_set_type (c[10], WAVE_COLLECTION_ATOM);
    wave_collection_add_collection (c[1], c[2]);
    wave_collection_add_collection (c[1], c[3]);
    wave_collection_add_collection (c[4], c[5]);
    wave_collection_add_collection (c[1], c[6]);
    wave_collection_add_collection (c[1], c[7]);
    wave_collection_add_collection (c[9], c[10]);
    wave_collection_set_seq_list (c[0], c[1]);
    wave_collection_set_par_list (c[3], c[4]);
    wave_collection_set_seq_list (c[8], c[9]);
    wave_collection_set_atom (c[1], a[0]);
    wave_collection_set_atom (c[2], a[1]);
    wave_collection_set_atom (c[4], a[2]);
    wave_collection_set_atom (c[5], a[3]);
    wave_collection_set_atom (c[6], a[4]);
    wave_collection_set_atom (c[9], a[5]);
    wave_collection_set_atom (c[10], a[6]);
    wave_collection_set_repetition_type (c[7], WAVE_COLLECTION_REPETITION_PATH);
    wave_collection_set_repetition_list (c[7], c[8]);
    wave_collection_set_repetition_path (c[7], p[9]);

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
    return 0;
}

static int _clean_atom (void)
{
    wave_atom_free (a[7]);
    return 0;
}

static int _clean_collection (void)
{
    wave_collection_free (c[0]);
    return 0;
}

static int _clean (void)
{
    _clean_path ();
    _clean_atom ();
    _clean_collection ();
    return 0;
}

static void _print_paths (void)
{
    wave_path_print (p[0]);
    printf ("\n");
}

static void _print_atoms (void)
{
    for (unsigned int i = 0; i < _ATOM_NUMBER; ++i)
    {
        printf ("- atom %d:\t", i);
        wave_atom_print (a[i]);
        printf ("\n");
    }
}

static void _print_collections (void)
{
    wave_collection_print (c[0]);
    printf ("\n");
}

/**
 * \brief Main.
 */
int main (void)
{
    _init ();
    printf ("Wave AST pretty printing\n");
    printf ("========================\n");

    printf ("Path printing:\n");
    printf ("--------------\n");
    _print_paths ();
    printf ("\n");
    printf ("Atom printing:\n");
    printf ("--------------\n");
    _print_atoms ();
    printf ("\n");
    printf ("Collection printing:\n");
    printf ("--------------------\n");
    _print_collections ();

    _clean ();

    return 0;
}
