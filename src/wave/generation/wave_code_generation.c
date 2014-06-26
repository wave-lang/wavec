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
 * \brief Generate C source code giving an atom.
 * \param code_file The file where the C code will be written.
 * \param collection The atom to translate into C code.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
static void wave_code_generation_atom(FILE* code_file, FILE * alloc_file, const wave_collection* collection);

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
 * \brief Generate C source code giving an operator atom.
 * \param code_file The file where the C code will be written.
 * \param collection The collection containing the value.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_atom
 * \relatesalso wave_collection_info
 */
static void _wave_code_generation_fprint_operator(FILE* code_file, const wave_collection* collection);

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
    [WAVE_ATOM_OPERATOR]        = _wave_code_generation_fprint_operator,
    [WAVE_ATOM_PATH]            = _wave_code_generation_fprint_path,
    [WAVE_ATOM_UNKNOWN]         = NULL,
};

static inline wave_coordinate * wave_coordinate_get_collection_total_length(const wave_collection * const c){

    wave_coordinate* coord = wave_coordinate_alloc();
    wave_collection* last_one = wave_collection_get_last (wave_collection_get_list (c));
    wave_coordinate* collection_coordinate = wave_coordinate_copy(wave_collection_get_coordinate (last_one));
    wave_coordinate* local_length = wave_coordinate_copy(wave_collection_get_length(last_one));
    wave_coordinate_set_plus (coord, collection_coordinate, local_length);

    return coord;
}

static inline void wave_code_generation_alloc_collection_tab(FILE* alloc_file, const wave_collection* collection){
    fprintf(alloc_file, "wave_data wave_tab");
    wave_collection_fprint_full_indexes(alloc_file, collection);
    fprintf(alloc_file, "[");
    wave_coordinate* collection_coordinate = wave_coordinate_get_collection_total_length(collection);
    wave_coordinate_fprint(alloc_file, collection_coordinate);
    wave_coordinate_free(collection_coordinate);
    fprintf(alloc_file, "];\n");
}

static void wave_code_generation_print_sub_info (FILE * code_file, const wave_collection * parent, const wave_collection * collection, const char * type_string)
{
    wave_coordinate* collection_coordinate = wave_collection_get_coordinate(collection);

    fprintf (code_file, "wave_tab");
    wave_collection_fprint_full_indexes(code_file, parent);
    fprintf (code_file, "[");
    wave_coordinate_fprint (code_file, collection_coordinate);
    fprintf (code_file, "]._type = %s;\n", type_string);

    fprintf (code_file, "wave_tab");
    wave_collection_fprint_full_indexes(code_file, parent);
    fprintf (code_file, "[");
    wave_coordinate_fprint (code_file, collection_coordinate);
    wave_collection * last = wave_collection_get_last (wave_collection_get_list (collection));
    fprintf (code_file, "]._content._collection._size = ");
    wave_coordinate * c = wave_coordinate_copy (wave_collection_get_coordinate (last));
    wave_coordinate * l = wave_coordinate_copy (wave_collection_get_length (last));
    wave_coordinate * sum = wave_coordinate_alloc ();
    wave_coordinate_set_plus (sum, c, l);
    wave_coordinate_fprint (code_file, sum);
    fprintf (code_file, ";\n");
    wave_coordinate_free (sum);

    fprintf (code_file, "wave_tab");
    wave_collection_fprint_full_indexes(code_file, parent);
    fprintf (code_file, "[");
    wave_coordinate_fprint (code_file, collection_coordinate);
    fprintf (code_file, "]._content._collection._tab = wave_tab");
    wave_collection_fprint_full_indexes (code_file, collection);
    fprintf (code_file, ";\n");
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
    wave_code_generation_alloc_collection_tab(alloc_file, collection);
    wave_code_generation_collection(code_file, alloc_file, wave_collection_get_list(collection) );
}

static inline void _fprintf_closing_curly (FILE * stream, unsigned int number)
{
    for (unsigned int i = 0; i < number; i++)
        fprintf(stream, "}\n");
}

static void wave_code_generation_collection_par(FILE* code_file, FILE * alloc_file, const wave_collection* collection){
    fprintf(code_file, "#pragma omp parallel\n{\n");
    fprintf(code_file, "#pragma omp sections\n{\n");
    wave_code_generation_alloc_collection_tab(alloc_file, collection);
    fprintf(code_file, "#pragma omp section\n{\n");
    wave_code_generation_collection(code_file, alloc_file, wave_collection_get_list(collection) );
    _fprintf_closing_curly (code_file, 3);
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

static void wave_code_generation_atom(FILE* code_file, FILE * alloc_file, const wave_collection* collection){
    (void) alloc_file;
    wave_atom* atom = wave_collection_get_atom(collection);
    wave_atom_type atom_type = wave_atom_get_type(atom);
    _wave_code_generation_atom[ atom_type ](code_file, collection);
}

static inline void _wave_generate_with_strings_inside_tm(FILE* const code_file, const wave_collection* const collection, const char* const struct_name, const char* const type_string){
    fprintf(code_file, "wave_tab");
    wave_collection_fprint_full_indexes(code_file, wave_collection_get_parent(collection));
    wave_coordinate* collection_coordinate = wave_collection_info_get_coordinate( wave_collection_get_info( collection ) );
    fprintf(code_file, "[");
    wave_coordinate_fprint(code_file, collection_coordinate);
    fprintf(code_file, "]%s = ", struct_name);
    wave_atom_fprint(code_file, wave_collection_get_atom( collection ));
    fprintf(code_file, ";\n");
    fprintf(code_file, "wave_tab");
    wave_collection_fprint_full_indexes(code_file, wave_collection_get_parent(collection));
    collection_coordinate = wave_collection_info_get_coordinate( wave_collection_get_info( collection ) );
    fprintf(code_file, "[");
    wave_coordinate_fprint(code_file, collection_coordinate);
    fprintf(code_file, "]._type = %s;\n", type_string);
}

static void _wave_code_generation_fprint_int(FILE* code_file, const wave_collection* collection){
    _wave_generate_with_strings_inside_tm(code_file, collection, "._content._int", "WAVE_DATA_INT");
}

static void _wave_code_generation_fprint_float(FILE* code_file, const wave_collection* collection){
    _wave_generate_with_strings_inside_tm(code_file, collection, "._content._float", "WAVE_DATA_FLOAT");
}

static void _wave_code_generation_fprint_bool(FILE* code_file, const wave_collection* collection){
    _wave_generate_with_strings_inside_tm(code_file, collection, "._content._bool", "WAVE_DATA_BOOL");
}

static void _wave_code_generation_fprint_char(FILE* code_file, const wave_collection* collection){
    _wave_generate_with_strings_inside_tm(code_file, collection, "._content._char", "WAVE_DATA_CHAR");
}

static void _wave_code_generation_fprint_string(FILE* code_file, const wave_collection* collection){
    _wave_generate_with_strings_inside_tm(code_file, collection, "._content._string", "WAVE_DATA_STRING");
}

static void _wave_code_generation_fprint_operator(FILE* code_file, const wave_collection* collection){
    (void) code_file; (void) collection;
}

static void _wave_code_generation_fprint_path(FILE* code_file, const wave_collection* collection){
    (void) code_file; (void) collection;
}

static void wave_code_generation_fprint_tab_with_init(FILE* code_file, const wave_collection* collection, const wave_coordinate * coord ,const char* struct_field){
    fprintf(code_file, "wave_tab");
    wave_collection_fprint_full_indexes(code_file, collection);
    fprintf(code_file, "[");
    wave_coordinate_fprint(code_file, coord);
    fprintf(code_file, "]%s = ", struct_field);
}
