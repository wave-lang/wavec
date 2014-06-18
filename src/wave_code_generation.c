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

#include "wave_code_generation.h"

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

//////////////////////////// REMOVE ME //////////////////////////////////////////////////////////
typedef void *wave_collection_info; ////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Generate C source code giving an integer atom.
 * \param output_file The file where the C code will be written.
 * \param atom The float value.
 * \param info The collection info to get the variable name and index.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_int(FILE* output_file, const wave_atom* atom, const wave_collection_info* info);

/**
 * \brief Generate C source code giving an float atom.
 * \param output_file The file where the C code will be written.
 * \param atom The float value.
 * \param info The collection info to get the variable name and index.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_float(FILE* output_file, const wave_atom* atom, const wave_collection_info* info);

/**
 * \brief Generate C source code giving an bool atom.
 * \param output_file The file where the C code will be written.
 * \param atom The float value.
 * \param info The collection info to get the variable name and index.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_bool(FILE* output_file, const wave_atom* atom, const wave_collection_info* info);

/**
 * \brief Generate C source code giving an char atom.
 * \param output_file The file where the C code will be written.
 * \param atom The float value.
 * \param info The collection info to get the variable name and index.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_char(FILE* output_file, const wave_atom* atom, const wave_collection_info* info);

/**
 * \brief Generate C source code giving an string atom.
 * \param output_file The file where the C code will be written.
 * \param atom The float value.
 * \param info The collection info to get the variable name and index.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_string(FILE* output_file, const wave_atom* atom, const wave_collection_info* info);

/**
 * \brief Generate C source code giving an operator atom.
 * \param output_file The file where the C code will be written.
 * \param atom The float value.
 * \param info The collection info to get the variable name and index.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_operator(FILE* output_file, const wave_atom* atom, const wave_collection_info* info);

/**
 * \brief Generate C source code giving an path atom.
 * \param output_file The file where the C code will be written.
 * \param atom The float value.
 * \param info The collection info to get the variable name and index.
 * \pre output_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_path(FILE* output_file, const wave_atom* atom, const wave_collection_info* info);

static void (* const _wave_code_generation_collection_generation []) (FILE*, const wave_collection*)=
{
    [WAVE_COLLECTION_ATOM]          = wave_code_generation_atom,
    [WAVE_COLLECTION_REP_SEQ]       = wave_code_generation_collection_rep_seq,
    [WAVE_COLLECTION_REP_PAR]       = wave_code_generation_collection_rep_par,
    [WAVE_COLLECTION_SEQ]           = wave_code_generation_collection_rep_par,
    [WAVE_COLLECTION_PAR]           = wave_code_generation_collection_rep_par,
    [WAVE_COLLECTION_CYCLIC_SEQ]    = wave_code_generation_collection_rep_par,
    [WAVE_COLLECTION_CYCLIC_PAR]    = wave_code_generation_collection_rep_par,
    [WAVE_COLLECTION_UNKNOWN]       = NULL,
};
static void (* _wave_code_generation_atom []) (FILE*, const wave_atom*, const wave_collection_info*) =
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

static void _wave_code_generation_fprint_int(FILE* output_file, const wave_atom* atom, const wave_collection_info* info){
}
static void _wave_code_generation_fprint_float(FILE* output_file, const wave_atom* atom, const wave_collection_info* info){
}
static void _wave_code_generation_fprint_bool(FILE* output_file, const wave_atom* atom, const wave_collection_info* info){
}
static void _wave_code_generation_fprint_char(FILE* output_file, const wave_atom* atom, const wave_collection_info* info){
}
static void _wave_code_generation_fprint_string(FILE* output_file, const wave_atom* atom, const wave_collection_info* info){
}
static void _wave_code_generation_fprint_operator(FILE* output_file, const wave_atom* atom, const wave_collection_info* info){
}
static void _wave_code_generation_fprint_path(FILE* output_file, const wave_atom* atom, const wave_collection_info* info){
}

void wave_code_generation_collection(FILE* output_file, const wave_collection* collection){
    do{
        wave_collection_type collection_type = wave_collection_get_type( collection );
        wave_collection* collection_list = wave_collection_get_list( collection );
        _wave_code_generation_collection_generation[ collection_type ](output_file, collection);
    }
    while( wave_collection_has_next(collection) && (collection = wave_collection_get_next(collection)) );
}

static void wave_code_generation_collection_seq(FILE* output_file, const wave_collection* collection){
    do{
        wave_code_generation_collection(output_file, wave_collection_get_list(collection) );
    }
    while( wave_collection_has_next( collection ) && ( collection = wave_collection_get_next( collection ) ) );
}

static void wave_code_generation_collection_par(FILE* output_file, const wave_collection* collection){
    fprintf(output_file, "#pragma omp parallel\n{\n");
    fprintf(output_file, "#pragma omp sections\n{\n");
    do{
        fprintf(output_file, "#pragma omp section\n{\n");
        wave_code_generation_collection(output_file, wave_collection_get_list(collection) );
        fprintf(output_file, "}\n");
    }
    while( wave_collection_has_next( collection ) && ( collection = wave_collection_get_next( collection ) ) );
    fprintf(output_file, "}\n");
    fprintf(output_file, "}\n");
}

static void wave_code_generation_collection_rep_seq(FILE* output_file, const wave_collection* collection){
    fprintf(output_file, "#pragma omp parallel\n{\n");
    fprintf(output_file, "#pragma omp for\n{\n");
    fprintf(output_file, "for(int __wave__parallel__iterator__ = 0;");
    fprintf(output_file, "__wave__parallel__iterator__ < ");
    ///////////// HERE PATH SIZE //////////////////
    fprintf(output_file, " ++__wave__parallel__iterator__)\n{\n");
    do{
        wave_code_generation_collection(output_file, wave_collection_get_list(collection) );
    }
    while( wave_collection_has_next( collection ) && ( collection = wave_collection_get_next( collection ) ) );
    fprintf(output_file, "}\n");
    fprintf(output_file, "}\n");
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
    do{
        fprintf(output_file, "#pragma omp section\n{\n");
        wave_code_generation_collection(output_file, wave_collection_get_list(collection) );
        fprintf(output_file, "}\n");
    }
    while( wave_collection_has_next( collection ) && ( collection = wave_collection_get_next( collection ) ) );
    fprintf(output_file, "}\n");
    fprintf(output_file, "}\n");
    fprintf(output_file, "}\n");
    fprintf(output_file, "}\n");
}

static void wave_code_generation_collection_cyclic_seq(FILE* output_file, const wave_collection* collection){
    fprintf(output_file, "for(;;)\n{\n");
    do{
        wave_code_generation_collection(output_file, wave_collection_get_list(collection) );
    }
    while( wave_collection_has_next( collection ) && ( collection = wave_collection_get_next( collection ) ) );
    fprintf(output_file, "}\n");
}

static void wave_code_generation_collection_cyclic_par(FILE* output_file, const wave_collection* collection){
    fprintf(output_file, "for(;;)\n{\n");
    fprintf(output_file, "#pragma omp parallel\n{\n");
    fprintf(output_file, "#pragma omp sections\n{\n");
    do{
        fprintf(output_file, "#pragma omp section\n{\n");
        wave_code_generation_collection(output_file, wave_collection_get_list(collection) );
        fprintf(output_file, "}\n");
    }
    while( wave_collection_has_next( collection ) && ( collection = wave_collection_get_next( collection ) ) );
    fprintf(output_file, "}\n");
    fprintf(output_file, "}\n");
    fprintf(output_file, "}\n");
}

static void wave_code_generation_atom(FILE* output_file, const wave_collection* collection){
    wave_atom* atom = wave_collection_get_atom(collection);
}
