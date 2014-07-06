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

////////////////////////////////////////////////////////////////////////////////
// Static utilities.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Concatenate two files.
 * \param destination Destination.
 * \param source Source.
 */
static inline void file_cat (FILE * destination, FILE * source)
{
    bool end = false;
    char buffer[2048];

    while (! end)
    {
        int count = 0;
        fscanf (source, "%2047c%n", buffer, & count);
        end = count == 0;

        if (! end)
        {
            buffer[count] = '\0';
            fprintf (destination, "%s", buffer);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Static utilities.
////////////////////////////////////////////////////////////////////////////////

static inline void wave_code_generation_alloc_collection_tab (FILE * const alloc_file, const wave_collection* collection)
{
    wave_coordinate * collection_coordinate = wave_collection_get_list_length (collection);
    wave_int_list * collection_index_list = wave_collection_get_full_indexes (collection);

    fprintf (alloc_file, "wave_data ");
    wave_code_generation_fprint_tab_with_init (alloc_file, collection_index_list, collection_coordinate, "");
    fprintf (alloc_file, ";\n");

    wave_int_list_free (collection_index_list);
    wave_coordinate_free (collection_coordinate);
}

static void wave_code_generation_print_sub_info (FILE * const code_file, const wave_collection * const parent, const wave_collection * const collection, const char * const type_string)
{
    wave_coordinate * collection_coordinate = wave_collection_get_coordinate (collection);
    wave_int_list * parent_index_list = wave_collection_get_full_indexes (parent);
    wave_int_list * collection_index_list = wave_collection_get_full_indexes (collection);
    wave_coordinate * collection_length = wave_collection_get_list_length (collection);

    wave_code_generation_fprint_tab_with_init (code_file, parent_index_list, collection_coordinate, "._type = ");
    fprintf (code_file, "%s;\n", type_string);

    wave_code_generation_fprint_tab_with_init (code_file, parent_index_list, collection_coordinate, "._content._collection._size = ");
    wave_coordinate_fprint (code_file, collection_length);
    fprintf (code_file, ";\n");

    wave_code_generation_fprint_tab_with_init (code_file, parent_index_list, collection_coordinate, "._content._collection._tab = wave_tab");
    wave_int_list_code_fprint (code_file, collection_index_list);
    fprintf (code_file, ";\n");

    wave_int_list_free (parent_index_list);
    wave_int_list_free (collection_index_list);
    wave_coordinate_free (collection_length);
}

////////////////////////////////////////////////////////////////////////////////
// Static utilities for the various types of collections.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Generate C source code giving a sequential collection.
 * \param code_file The file where the C code will be written.
 * \param collection The sequential collection to translate into C code.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
static void wave_code_generation_collection_seq(FILE* code_file, FILE * alloc_file, const wave_collection* collection){
    unsigned long long int curly_backup = wave_generate_backup_curly ();
    wave_code_generation_alloc_collection_tab(alloc_file, collection);
    wave_code_generation_collection(code_file, alloc_file, wave_collection_get_list(collection) );
    wave_generate_flush_curly (code_file);
    wave_generate_restore_curly (curly_backup);
}

/**
 * \brief Generate C source code giving a collection.
 * \param code_file The file where the C code will be written.
 * \param collection The parallel collection to translate into C code.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
static void wave_code_generation_collection_par(FILE* code_file, FILE * alloc_file, const wave_collection* collection){
    unsigned long long int curly_backup = wave_generate_backup_curly ();
    wave_code_generation_alloc_collection_tab(alloc_file, collection);
    wave_code_generation_collection(code_file, alloc_file, wave_collection_get_list(collection) );
    wave_generate_flush_curly (code_file);
    wave_generate_restore_curly (curly_backup);
}

/**
 * \brief Generate C source code giving a sequential repeated collection.
 * \param code_file The file where the C code will be written.
 * \param collection The cyclic collection to translate into C code.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
static void wave_code_generation_collection_rep_seq(FILE* code_file, FILE * alloc_file, const wave_collection* collection){
    fprintf(code_file, "for(int __wave__parallel__iterator__ = 0;");
    fprintf(code_file, "__wave__parallel__iterator__ < ");
    ///////////// HERE PATH SIZE //////////////////
    fprintf(code_file, " ++__wave__parallel__iterator__)\n{\n");
    wave_code_generation_alloc_collection_tab(alloc_file, collection);
    wave_code_generation_collection(code_file, alloc_file, wave_collection_get_list(collection) );
    fprintf_closing_curly (code_file, 1);
}

/**
 * \brief Generate C source code giving a parallel repeated collection.
 * \param code_file The file where the C code will be written.
 * \param collection The cyclic collection to translate into C code.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
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
    fprintf_closing_curly (code_file, 5);
}

/**
 * \brief Generate C source code giving a sequential cyclic collection.
 * \param code_file The file where the C code will be written.
 * \param collection The cyclic collection to translate into C code.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
static void wave_code_generation_collection_cyclic_seq(FILE* code_file, FILE * alloc_file, const wave_collection* collection){
    fprintf(code_file, "for(;;)\n{\n");
    wave_code_generation_alloc_collection_tab(alloc_file, collection);
    wave_code_generation_collection(code_file, alloc_file, wave_collection_get_list(collection) );
    fprintf_closing_curly (code_file, 1);
}

/**
 * \brief Generate C source code giving a parallel cyclic collection.
 * \param code_file The file where the C code will be written.
 * \param collection The cyclic collection to translate into C code.
 * \pre code_file and collection must not be NULL.
 * \relatesalso wave_collection
 */
static void wave_code_generation_collection_cyclic_par(FILE* code_file, FILE * alloc_file, const wave_collection* collection){
    fprintf(code_file, "for(;;)\n{\n");
    fprintf(code_file, "#pragma omp parallel\n{\n");
    fprintf(code_file, "#pragma omp sections\n{\n");
    wave_code_generation_alloc_collection_tab(alloc_file, collection);
    fprintf(code_file, "#pragma omp section\n{\n");
    wave_code_generation_collection(code_file, alloc_file, wave_collection_get_list(collection) );
    fprintf_closing_curly (code_file, 4);
}

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

static inline void _current_phrase (FILE * const output, const wave_phrase * const p, unsigned int phrase_count)
{
    FILE * code_file = tmpfile ();
    FILE * alloc_file = tmpfile ();
    wave_collection* collection = wave_phrase_get_collection(p);

    /* Print the beginning of the function.
     * Each function shall contain exactly one phrase.
     */
    fprintf (output, "void phrase_%d (void)\n{\n", phrase_count);
    /* Unroll repetitions that depend on paths. */
    wave_collection_unroll_path(collection);
    /* Compute the AST indexes. */
    wave_collection_compute_indexes(collection);
    /* Replace paths that can be replaced. */
    wave_collection_replace_path(collection);
    /* Compute the lengths and coordinates of the collections. */
    wave_collection_compute_length_and_coords(collection);
    /* Generate the code and the allocations.
     * Required allocations are discovered while generating the code, but must
     * be put at the beginning.
     */
    wave_code_generation_collection(code_file, alloc_file, collection);
    /* Append the contents of the files to the real output. */
    fseek (alloc_file, 0, SEEK_SET);
    fseek (code_file, 0, SEEK_SET);
    file_cat (output, alloc_file);
    file_cat (output, code_file);
    /* Print the garbage cleaning at the end of the function. */
    fprintf (output, "wave_garbage_clean ();\n");
    /* Close the function. */
    fprintf (output, "}\n");

    fclose (code_file);
    fclose (alloc_file);
}

/**
 * \brief Print the main.
 * \param output Output.
 * \param phrase_count Phrase count.
 */
static inline void _print_main (FILE * const output, unsigned int phrase_count)
{
    /* Print the main beginning. */
    fprintf (output, "int main(void)\n{\n");
    /* Call the functions for each phrases. */
    for (unsigned int i = 0; i < phrase_count; ++i)
        fprintf (output, "phrase_%d ();\n", i);
    /* Destroy the garbage collector. */
    fprintf (output, "wave_garbage_destroy ();\n");
    /* Close the main function. */
    fprintf (output, "return 0;\n}\n");
}

////////////////////////////////////////////////////////////////////////////////
// Generation functions.
////////////////////////////////////////////////////////////////////////////////

void wave_code_generation_generate (FILE * const output_file, const wave_phrase * phrases)
{
    wave_code_generation_fprintf_headers (output_file);
    unsigned int count = 0;

    for (const wave_phrase * p = phrases; p != NULL; p = wave_phrase_get_next (p))
        _current_phrase (output_file, p, count++);
    _print_main (output_file, count);
}

void wave_code_generation_collection (FILE * const code_file, FILE * const alloc_file, const wave_collection * const collection)
{
    for (const wave_collection * c = collection; c != NULL; c = wave_collection_get_next (c))
    {
        wave_collection_type collection_type = wave_collection_get_type (c);
        if (wave_collection_has_parent (c))
        {
            wave_collection * parent = wave_collection_get_parent (c);
            if (collection_type == WAVE_COLLECTION_SEQ)
                wave_code_generation_print_sub_info (code_file, parent, c, "WAVE_DATA_SEQ");
            else if (collection_type == WAVE_COLLECTION_PAR)
                wave_code_generation_print_sub_info (code_file, parent, c, "WAVE_DATA_PAR");
        }
        _wave_code_generation_collection_generation [collection_type] (code_file, alloc_file, c);
    }
}
