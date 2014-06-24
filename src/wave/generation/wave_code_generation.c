/**
 * \file wave_code_generation.c
 * \brief Wave code generation.
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

#include "wave/generation/wave_code_generation.h"

/**
 * \brief Generate C source code giving an atom.
 * \param output_file The file where the C code will be written.
 * \param collection The atom to translate into C code.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
static void wave_code_generation_atom(FILE* output_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving a sequential collection.
 * \param output_file The file where the C code will be written.
 * \param collection The sequential collection to translate into C code.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
static void wave_code_generation_collection_seq(FILE* output_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving a collection.
 * \param output_file The file where the C code will be written.
 * \param collection The parallel collection to translate into C code.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
static void wave_code_generation_collection_par(FILE* output_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving a sequential cyclic collection.
 * \param output_file The file where the C code will be written.
 * \param collection The cyclic collection to translate into C code.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
static void wave_code_generation_collection_cyclic_seq(FILE* output_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving a parallel cyclic collection.
 * \param output_file The file where the C code will be written.
 * \param collection The cyclic collection to translate into C code.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
static void wave_code_generation_collection_cyclic_par(FILE* output_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving a sequential repeated collection.
 * \param output_file The file where the C code will be written.
 * \param collection The cyclic collection to translate into C code.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
static void wave_code_generation_collection_rep_seq(FILE* output_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving a parallel repeated collection.
 * \param output_file The file where the C code will be written.
 * \param collection The cyclic collection to translate into C code.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
static void wave_code_generation_collection_rep_par(FILE* output_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving an integer atom.
 * \param output_file The file where the C code will be written.
 * \param atom The float value.
 * \param info The collection info to get the variable name and index.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_int(FILE* output_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving an float atom.
 * \param output_file The file where the C code will be written.
 * \param atom The float value.
 * \param info The collection info to get the variable name and index.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_float(FILE* output_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving an bool atom.
 * \param output_file The file where the C code will be written.
 * \param atom The float value.
 * \param info The collection info to get the variable name and index.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_bool(FILE* output_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving an char atom.
 * \param output_file The file where the C code will be written.
 * \param atom The float value.
 * \param info The collection info to get the variable name and index.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_char(FILE* output_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving an string atom.
 * \param output_file The file where the C code will be written.
 * \param atom The float value.
 * \param info The collection info to get the variable name and index.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_string(FILE* output_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving an operator atom.
 * \param output_file The file where the C code will be written.
 * \param atom The float value.
 * \param info The collection info to get the variable name and index.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_operator(FILE* output_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving an path atom.
 * \param output_file The file where the C code will be written.
 * \param atom The float value.
 * \param info The collection info to get the variable name and index.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_path(FILE* output_file, const wave_collection* collection);

static void (* const _wave_code_generation_collection_generation []) (FILE*, const wave_collection*)=
{
    [WAVE_COLLECTION_ATOM]          = wave_code_generation_atom,
    [WAVE_COLLECTION_REP_SEQ]       = wave_code_generation_collection_rep_seq,
    [WAVE_COLLECTION_REP_PAR]       = wave_code_generation_collection_rep_par,
    [WAVE_COLLECTION_SEQ]           = wave_code_generation_collection_seq,
    [WAVE_COLLECTION_PAR]           = wave_code_generation_collection_par,
    [WAVE_COLLECTION_CYCLIC_SEQ]    = wave_code_generation_collection_cyclic_seq,
    [WAVE_COLLECTION_CYCLIC_PAR]    = wave_code_generation_collection_cyclic_par,
    [WAVE_COLLECTION_UNKNOWN]       = NULL,
};
static void (* _wave_code_generation_atom []) (FILE*, const wave_collection* collection) =
{
    [WAVE_ATOM_LITERAL_INT]     = _wave_code_generation_fprint_int,
    [WAVE_ATOM_LITERAL_FLOAT]   = _wave_code_generation_fprint_float,
    [WAVE_ATOM_LITERAL_BOOL]    = _wave_code_generation_fprint_bool,
    [WAVE_ATOM_LITERAL_CHAR]    = _wave_code_generation_fprint_char,
    [WAVE_ATOM_LITERAL_STRING]  = _wave_code_generation_fprint_string,
    [WAVE_ATOM_OPERATOR]        = _wave_code_generation_fprint_operator,
    [WAVE_ATOM_PATH]            = _wave_code_generation_fprint_path,
    [WAVE_ATOM_UNKNOWN]         = NULL,
};

static inline wave_coordinate * wave_coordinate_get_collection_total_length(const wave_collection * const c){

    wave_coordinate* coord = wave_coordinate_alloc();
    wave_collection* last_one = wave_collection_get_last (wave_collection_get_list (c));
    wave_coordinate* collection_coordinate = wave_coordinate_copy(wave_collection_get_coordinate (last_one));
    wave_coordinate* local_length = wave_coordinate_copy(wave_collection_get_length(last_one));
    wave_coordinate_set_plus_left_and_right(coord, collection_coordinate, local_length);

    return coord;
}

static inline void wave_code_generation_alloc_collection_tab(FILE* output_file, const wave_collection* collection){
    fprintf(output_file, "wave_data wave_tab");
    wave_collection_fprint_full_indexes(output_file, collection);
    fprintf(output_file, "[");
    wave_coordinate* collection_coordinate = wave_coordinate_get_collection_total_length(collection);
    wave_coordinate_fprint(output_file, collection_coordinate);
    wave_coordinate_free(collection_coordinate);
    fprintf(output_file, "];\n");
}

void wave_code_generation_collection(FILE* output_file, const wave_collection* collection){
    do{
        wave_collection_type collection_type = wave_collection_get_type( collection );
        _wave_code_generation_collection_generation[ collection_type ](output_file, collection);
    }
    while( wave_collection_has_next(collection) && (collection = wave_collection_get_next(collection)) );
}

static void wave_code_generation_collection_seq(FILE* output_file, const wave_collection* collection){
    wave_code_generation_alloc_collection_tab(output_file, collection);
    wave_code_generation_collection(output_file, wave_collection_get_list(collection) );
}

static void wave_code_generation_collection_par(FILE* output_file, const wave_collection* collection){
    fprintf(output_file, "#pragma omp parallel\n{\n");
    fprintf(output_file, "#pragma omp sections\n{\n");
    wave_code_generation_alloc_collection_tab(output_file, collection);
    fprintf(output_file, "#pragma omp section\n{\n");
    wave_code_generation_collection(output_file, wave_collection_get_list(collection) );
    fprintf(output_file, "}\n");
    fprintf(output_file, "}\n");
    fprintf(output_file, "}\n");
}

static void wave_code_generation_collection_rep_seq(FILE* output_file, const wave_collection* collection){
    fprintf(output_file, "for(int __wave__parallel__iterator__ = 0;");
    fprintf(output_file, "__wave__parallel__iterator__ < ");
    ///////////// HERE PATH SIZE //////////////////
    fprintf(output_file, " ++__wave__parallel__iterator__)\n{\n");
    wave_code_generation_alloc_collection_tab(output_file, collection);
    wave_code_generation_collection(output_file, wave_collection_get_list(collection) );
    fprintf(output_file, "}\n");
}

static void wave_code_generation_collection_rep_par(FILE* output_file, const wave_collection* collection){
    fprintf(output_file, "#pragma omp parallel\n{\n");
    fprintf(output_file, "#pragma omp for\n{\n");
    fprintf(output_file, "for(int __wave__parallel__iterator__ = 0;");
    fprintf(output_file, "__wave__parallel__iterator__ < ");
    ///////////// HERE PATH SIZE //////////////////
    fprintf(output_file, " ++__wave__parallel__iterator__)\n{\n");
    fprintf(output_file, "#pragma omp sections\n{\n");
    wave_code_generation_alloc_collection_tab(output_file, collection);
    fprintf(output_file, "#pragma omp section\n{\n");
    wave_code_generation_collection(output_file, wave_collection_get_list(collection) );
    fprintf(output_file, "}\n");
    fprintf(output_file, "}\n");
    fprintf(output_file, "}\n");
    fprintf(output_file, "}\n");
    fprintf(output_file, "}\n");
}

static void wave_code_generation_collection_cyclic_seq(FILE* output_file, const wave_collection* collection){
    fprintf(output_file, "for(;;)\n{\n");
    wave_code_generation_alloc_collection_tab(output_file, collection);
    wave_code_generation_collection(output_file, wave_collection_get_list(collection) );
    fprintf(output_file, "}\n");
}

static void wave_code_generation_collection_cyclic_par(FILE* output_file, const wave_collection* collection){
    fprintf(output_file, "for(;;)\n{\n");
    fprintf(output_file, "#pragma omp parallel\n{\n");
    fprintf(output_file, "#pragma omp sections\n{\n");
    wave_code_generation_alloc_collection_tab(output_file, collection);
    fprintf(output_file, "#pragma omp section\n{\n");
    wave_code_generation_collection(output_file, wave_collection_get_list(collection) );
    fprintf(output_file, "}\n");
    fprintf(output_file, "}\n");
    fprintf(output_file, "}\n");
    fprintf(output_file, "}\n");
}

static void wave_code_generation_atom(FILE* output_file, const wave_collection* collection){
    wave_atom* atom = wave_collection_get_atom(collection);
    wave_atom_type atom_type = wave_atom_get_type(atom);
    _wave_code_generation_atom[ atom_type ](output_file, collection);
}

static void _wave_code_generation_fprint_int(FILE* output_file, const wave_collection* collection){
    fprintf(output_file, "wave_tab");
    wave_collection_fprint_full_indexes(output_file, wave_collection_get_parent(collection));
    wave_coordinate* collection_coordinate = wave_collection_info_get_coordinate( wave_collection_get_info( collection ) );
    fprintf(output_file, "[");
    wave_coordinate_fprint(output_file, collection_coordinate);
    fprintf(output_file, "] =");
    wave_atom_fprint(output_file, wave_collection_get_atom( collection ));
    fprintf(output_file, ";\n");
}

static void _wave_code_generation_fprint_float(FILE* output_file, const wave_collection* collection){
    (void) output_file; (void) collection;
}
static void _wave_code_generation_fprint_bool(FILE* output_file, const wave_collection* collection){
    (void) output_file; (void) collection;
}
static void _wave_code_generation_fprint_char(FILE* output_file, const wave_collection* collection){
    (void) output_file; (void) collection;
}
static void _wave_code_generation_fprint_string(FILE* output_file, const wave_collection* collection){
    (void) output_file; (void) collection;
}
static void _wave_code_generation_fprint_operator(FILE* output_file, const wave_collection* collection){
    (void) output_file; (void) collection;
}
static void _wave_code_generation_fprint_path(FILE* output_file, const wave_collection* collection){
    (void) output_file; (void) collection;
}
