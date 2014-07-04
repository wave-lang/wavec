/**
 * \file wave_code_generation.c
 * \brief Wave code generation.
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

#include "wave/generation/wave_code_generation.h"

/**
 * \brief Generate C source code giving a sequential collection.
 * \param code_file The file where the C code will be written.
 * \param collection The sequential collection to translate into C code.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
static void wave_code_generation_collection_seq(FILE* code_file, FILE * alloc_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving a collection.
 * \param code_file The file where the C code will be written.
 * \param collection The parallel collection to translate into C code.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
static void wave_code_generation_collection_par(FILE* code_file, FILE * alloc_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving a sequential cyclic collection.
 * \param code_file The file where the C code will be written.
 * \param collection The cyclic collection to translate into C code.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
static void wave_code_generation_collection_cyclic_seq(FILE* code_file, FILE * alloc_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving a parallel cyclic collection.
 * \param code_file The file where the C code will be written.
 * \param collection The cyclic collection to translate into C code.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
static void wave_code_generation_collection_cyclic_par(FILE* code_file, FILE * alloc_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving a sequential repeated collection.
 * \param code_file The file where the C code will be written.
 * \param collection The cyclic collection to translate into C code.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
static void wave_code_generation_collection_rep_seq(FILE* code_file, FILE * alloc_file, const wave_collection* collection);

/**
 * \brief Generate C source code giving a parallel repeated collection.
 * \param code_file The file where the C code will be written.
 * \param collection The cyclic collection to translate into C code.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
static void wave_code_generation_collection_rep_par(FILE* code_file, FILE * alloc_file, const wave_collection* collection);

/**
 * \brief An array for the code generation switch.
 */
static void (* const _wave_code_generation_collection_generation []) (FILE*, FILE *, const wave_collection*)=
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

static inline void wave_code_generation_alloc_collection_tab(FILE* alloc_file, const wave_collection* collection){
    wave_coordinate* collection_coordinate = wave_collection_get_list_length (collection);
    wave_int_list* collection_index_list = wave_collection_get_full_indexes(collection);

    fprintf(alloc_file, "wave_data ");
    wave_code_generation_fprint_tab_with_init(alloc_file, collection_index_list, collection_coordinate, "");
    fprintf(alloc_file, ";\n");

    wave_int_list_free(collection_index_list);
    wave_coordinate_free(collection_coordinate);
}

static void wave_code_generation_print_sub_info (FILE * code_file, const wave_collection * parent, const wave_collection * collection, const char * type_string)
{
    wave_coordinate* collection_coordinate = wave_collection_get_coordinate(collection);
    wave_int_list* parent_index_list = wave_collection_get_full_indexes(parent);
    wave_int_list* collection_index_list = wave_collection_get_full_indexes(collection);
    wave_coordinate* collection_length = wave_collection_get_list_length (collection);

    wave_code_generation_fprint_tab_with_init(code_file, parent_index_list, collection_coordinate, "._type = ");
    fprintf (code_file, "%s;\n", type_string);

    wave_code_generation_fprint_tab_with_init(code_file, parent_index_list, collection_coordinate, "._content._collection._size = ");
    wave_coordinate_fprint (code_file, collection_length);
    fprintf (code_file, ";\n");

    wave_code_generation_fprint_tab_with_init(code_file, parent_index_list, collection_coordinate, "._content._collection._tab = wave_tab");
    wave_int_list_code_fprint(code_file, collection_index_list);
    fprintf (code_file, ";\n");

    wave_int_list_free(parent_index_list);
    wave_int_list_free(collection_index_list);
    wave_coordinate_free(collection_length);
}

void wave_code_generation_collection(FILE* code_file, FILE * alloc_file, const wave_collection* collection){
    do{
        wave_collection_type collection_type = wave_collection_get_type( collection );
        if (wave_collection_has_parent (collection))
        {
            wave_collection * parent = wave_collection_get_parent (collection);
            if (collection_type == WAVE_COLLECTION_SEQ)
                wave_code_generation_print_sub_info (code_file, parent, collection, "WAVE_DATA_SEQ");
            else if (collection_type == WAVE_COLLECTION_PAR)
                wave_code_generation_print_sub_info (code_file, parent, collection, "WAVE_DATA_PAR");
        }
        _wave_code_generation_collection_generation[ collection_type ](code_file, alloc_file, collection);
    }
    while( wave_collection_has_next(collection) && (collection = wave_collection_get_next(collection)) );
}

static void wave_code_generation_collection_seq(FILE* code_file, FILE * alloc_file, const wave_collection* collection){
    unsigned long long int curly_backup = wave_generate_backup_curly ();
    wave_code_generation_alloc_collection_tab(alloc_file, collection);
    wave_code_generation_collection(code_file, alloc_file, wave_collection_get_list(collection) );
    wave_generate_flush_curly (code_file);
    wave_generate_restore_curly (curly_backup);
}

static inline void _fprintf_closing_curly (FILE * stream, unsigned int number)
{
    for (unsigned int i = 0; i < number; i++)
        fprintf(stream, "}\n");
}

static void wave_code_generation_collection_par(FILE* code_file, FILE * alloc_file, const wave_collection* collection){
    unsigned long long int curly_backup = wave_generate_backup_curly ();
    wave_code_generation_alloc_collection_tab(alloc_file, collection);
    wave_code_generation_collection(code_file, alloc_file, wave_collection_get_list(collection) );
    wave_generate_flush_curly (code_file);
    wave_generate_restore_curly (curly_backup);
}

static void wave_code_generation_collection_rep_seq(FILE* code_file, FILE * alloc_file, const wave_collection* collection){
    fprintf(code_file, "for(int __wave__parallel__iterator__ = 0;");
    fprintf(code_file, "__wave__parallel__iterator__ < ");
    ///////////// HERE PATH SIZE //////////////////
    fprintf(code_file, " ++__wave__parallel__iterator__)\n{\n");
    wave_code_generation_alloc_collection_tab(alloc_file, collection);
    wave_code_generation_collection(code_file, alloc_file, wave_collection_get_list(collection) );
    _fprintf_closing_curly (code_file, 1);
}

static void wave_code_generation_collection_rep_par(FILE* code_file, FILE * alloc_file, const wave_collection* collection){
    fprintf(code_file, "#pragma omp parallel\n{\n");
    fprintf(code_file, "#pragma omp for\n{\n");
    fprintf(code_file, "for(int __wave__parallel__iterator__ = 0;");
    fprintf(code_file, "__wave__parallel__iterator__ < ");
    ///////////// HERE PATH SIZE //////////////////
    fprintf(code_file, " ++__wave__parallel__iterator__)\n{\n");
    fprintf(code_file, "#pragma omp sections\n{\n");
    wave_code_generation_alloc_collection_tab(alloc_file, collection);
    fprintf(code_file, "#pragma omp section\n{\n");
    wave_code_generation_collection(code_file, alloc_file, wave_collection_get_list(collection) );
    _fprintf_closing_curly (code_file, 5);
}

static void wave_code_generation_collection_cyclic_seq(FILE* code_file, FILE * alloc_file, const wave_collection* collection){
    fprintf(code_file, "for(;;)\n{\n");
    wave_code_generation_alloc_collection_tab(alloc_file, collection);
    wave_code_generation_collection(code_file, alloc_file, wave_collection_get_list(collection) );
    _fprintf_closing_curly (code_file, 1);
}

static void wave_code_generation_collection_cyclic_par(FILE* code_file, FILE * alloc_file, const wave_collection* collection){
    fprintf(code_file, "for(;;)\n{\n");
    fprintf(code_file, "#pragma omp parallel\n{\n");
    fprintf(code_file, "#pragma omp sections\n{\n");
    wave_code_generation_alloc_collection_tab(alloc_file, collection);
    fprintf(code_file, "#pragma omp section\n{\n");
    wave_code_generation_collection(code_file, alloc_file, wave_collection_get_list(collection) );
    _fprintf_closing_curly (code_file, 4);
}
