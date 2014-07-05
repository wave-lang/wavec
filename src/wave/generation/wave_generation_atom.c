/**
 * \file wave_generation_atom.c
 * \brief Wave code generation for operators.
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
#include "wave/generation/wave_generation_atom.h"

/**
 * \brief Generate C source code giving an integer atom.
 * \param code_file The file where the C code will be written.
 * \param collection The collection containing the value.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_int(FILE* code_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving an float atom.
 * \param code_file The file where the C code will be written.
 * \param collection The collection containing the value.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_float(FILE* code_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving an bool atom.
 * \param code_file The file where the C code will be written.
 * \param collection The collection containing the value.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_bool(FILE* code_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving an char atom.
 * \param code_file The file where the C code will be written.
 * \param collection The collection containing the value.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_char(FILE* code_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving an string atom.
 * \param code_file The file where the C code will be written.
 * \param collection The collection containing the value.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_string(FILE* code_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving an path atom.
 * \param code_file The file where the C code will be written.
 * \param collection The collection containing the value.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_path(FILE* code_file, const wave_collection* collection);

/**
 * \brief An array for the atome print switch.
 */
static void (* _wave_code_generation_atom []) (FILE*, const wave_collection* collection) =
{
    [WAVE_ATOM_LITERAL_INT]     = _wave_code_generation_fprint_int,
    [WAVE_ATOM_LITERAL_FLOAT]   = _wave_code_generation_fprint_float,
    [WAVE_ATOM_LITERAL_BOOL]    = _wave_code_generation_fprint_bool,
    [WAVE_ATOM_LITERAL_CHAR]    = _wave_code_generation_fprint_char,
    [WAVE_ATOM_LITERAL_STRING]  = _wave_code_generation_fprint_string,
    [WAVE_ATOM_OPERATOR]        = wave_code_generation_fprint_operator,
    [WAVE_ATOM_PATH]            = _wave_code_generation_fprint_path,
    [WAVE_ATOM_UNKNOWN]         = NULL,
};

void wave_code_generation_atom(FILE* code_file, FILE * alloc_file, const wave_collection* collection){
    (void) alloc_file;
    wave_atom* atom = wave_collection_get_atom(collection);
    wave_atom_type atom_type = wave_atom_get_type(atom);
    _wave_code_generation_atom[ atom_type ](code_file, collection);
}

static inline void _wave_generate_with_strings_inside_tm(FILE* const code_file, const wave_collection* const collection, wave_atom_type t){
    wave_coordinate* collection_coordinate = wave_collection_get_coordinate(collection);
    wave_int_list* collection_index_list = wave_collection_get_full_indexes(wave_collection_get_parent(collection));

    wave_generate_content_assignement (code_file, collection_index_list, collection_coordinate, t);
    fprintf(code_file, " = ");
    wave_atom_fprint(code_file, wave_collection_get_atom( collection ));
    fprintf(code_file, ";\n");

    wave_generate_type_assignement (code_file, collection_index_list , collection_coordinate, t);
    wave_int_list_free (collection_index_list);
}

static void _wave_code_generation_fprint_int(FILE* code_file, const wave_collection* collection){
    _wave_generate_with_strings_inside_tm(code_file, collection, WAVE_ATOM_LITERAL_INT);
}

static void _wave_code_generation_fprint_float(FILE* code_file, const wave_collection* collection){
    _wave_generate_with_strings_inside_tm(code_file, collection, WAVE_ATOM_LITERAL_FLOAT);
}

static void _wave_code_generation_fprint_bool(FILE* code_file, const wave_collection* collection){
    _wave_generate_with_strings_inside_tm(code_file, collection, WAVE_ATOM_LITERAL_BOOL);
}

static void _wave_code_generation_fprint_char(FILE* code_file, const wave_collection* collection){
    _wave_generate_with_strings_inside_tm(code_file, collection, WAVE_ATOM_LITERAL_CHAR);
}

static void _wave_code_generation_fprint_string(FILE* code_file, const wave_collection* collection){
    _wave_generate_with_strings_inside_tm(code_file, collection, WAVE_ATOM_LITERAL_STRING);
}

static void _wave_code_generation_fprint_path(FILE* code_file, const wave_collection* collection)
{
//    (void) code_file; (void) collection;
    wave_path * p = wave_atom_get_path (wave_collection_get_atom (collection));
    wave_collection * pointed = wave_collection_get_collection_pointed (collection, p);
    if (pointed != NULL)
    {
        wave_int_list * indexes = wave_collection_get_full_indexes (wave_collection_get_parent(collection));
        wave_coordinate * c = wave_collection_get_coordinate (collection);
        wave_int_list * indexes_pointed = wave_collection_get_full_indexes (wave_collection_get_parent (pointed));
        wave_coordinate * c_pointed = wave_collection_get_coordinate (pointed);

        wave_code_generation_fprint_tab_with_init(code_file, indexes, c, "");
        fprintf (code_file, " = ");

        wave_code_generation_fprint_tab_with_init(code_file, indexes_pointed, c_pointed, "");
        fprintf (code_file, ";\n");

        wave_int_list_free (indexes);
        wave_int_list_free (indexes_pointed);
    }
}
