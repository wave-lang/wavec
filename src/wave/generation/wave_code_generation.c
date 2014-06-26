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

static inline void _wave_code_generation_fprint_tab_with_init(FILE* file, const wave_int_list* list, const wave_coordinate * coord ,const char* struct_field){
    fprintf(file, "wave_tab");
    wave_int_list_fprint(file, list);
    fprintf(file, "[");
    wave_coordinate_fprint(file, coord);
    fprintf(file, "]%s", struct_field);
}

static inline void wave_code_generation_alloc_collection_tab(FILE* alloc_file, const wave_collection* collection){
    wave_coordinate* collection_coordinate = wave_coordinate_get_collection_total_length(collection);
    wave_int_list* collection_index_list = wave_collection_get_full_indexes(collection);

    fprintf(alloc_file, "wave_data ");
    _wave_code_generation_fprint_tab_with_init(alloc_file, collection_index_list, collection_coordinate, "");
    fprintf(alloc_file, ";\n");

    wave_int_list_free(collection_index_list);
    wave_coordinate_free(collection_coordinate);
}

static void wave_code_generation_print_sub_info (FILE * code_file, const wave_collection * parent, const wave_collection * collection, const char * type_string)
{
    wave_coordinate* collection_coordinate = wave_collection_get_coordinate(collection);
    wave_int_list* parent_index_list = wave_collection_get_full_indexes(parent);
    wave_int_list* collection_index_list = wave_collection_get_full_indexes(collection);
    wave_coordinate* collection_length = wave_coordinate_get_collection_total_length(collection);

    _wave_code_generation_fprint_tab_with_init(code_file, parent_index_list, collection_coordinate, "._type = ");
    fprintf (code_file, "%s;\n", type_string);

    _wave_code_generation_fprint_tab_with_init(code_file, parent_index_list, collection_coordinate, "._content._collection._size = ");
    wave_coordinate_fprint (code_file, collection_length);
    fprintf (code_file, ";\n");

    _wave_code_generation_fprint_tab_with_init(code_file, parent_index_list, collection_coordinate, "._content._collection._tab = wave_tab");
    wave_int_list_fprint(code_file, collection_index_list);
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

static const char * const _atom_type_strings[] =
{
    [WAVE_ATOM_LITERAL_INT] = "_int",
    [WAVE_ATOM_LITERAL_FLOAT] = "_float",
    [WAVE_ATOM_LITERAL_BOOL] = "_bool",
    [WAVE_ATOM_LITERAL_CHAR] = "_char",
    [WAVE_ATOM_LITERAL_STRING] = "_string",
};

static const char * const _atom_type_data_strings[] =
{
    [WAVE_ATOM_LITERAL_INT] = "WAVE_DATA_INT",
    [WAVE_ATOM_LITERAL_FLOAT] = "WAVE_DATA_FLOAT",
    [WAVE_ATOM_LITERAL_BOOL] = "WAVE_DATA_BOOL",
    [WAVE_ATOM_LITERAL_CHAR] = "WAVE_DATA_CHAR",
    [WAVE_ATOM_LITERAL_STRING] = "WAVE_DATA_STRING",
};


static void _generate_content_assignement (FILE * const code_file, const wave_int_list * const list, const wave_coordinate * const c, wave_atom_type t)
{
    _wave_code_generation_fprint_tab_with_init(code_file, list, c, "._content.");
    fprintf (code_file, "%s", _atom_type_strings[t]);
}

static void _generate_type_assignement (FILE * const code_file, const wave_int_list * const list, const wave_coordinate * const c, wave_atom_type t)
{
    _wave_code_generation_fprint_tab_with_init(code_file, list, c, "._type = ");
    fprintf (code_file, "%s;\n", _atom_type_data_strings[t]);
}

static inline void _wave_generate_with_strings_inside_tm(FILE* const code_file, const wave_collection* const collection, wave_atom_type t){
    wave_coordinate* collection_coordinate = wave_collection_get_coordinate(collection);
    wave_int_list* collection_index_list = wave_collection_get_full_indexes(wave_collection_get_parent(collection));

    _generate_content_assignement (code_file, collection_index_list, collection_coordinate, t);
    fprintf(code_file, " = ");
    wave_atom_fprint(code_file, wave_collection_get_atom( collection ));
    fprintf(code_file, ";\n");

    _generate_type_assignement (code_file, collection_index_list , collection_coordinate, t);
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
    _wave_generate_with_strings_inside_tm(code_file, collection, WAVE_ATOM_LITERAL_CHAR);
}

static void _print_tab_minus (FILE * code_file, const wave_int_list * list, const wave_coordinate * c, int shift)
{
    wave_coordinate * minus = wave_coordinate_alloc ();
    wave_coordinate_set_constant  (minus, shift);
    wave_coordinate * shifted = wave_coordinate_alloc ();
    wave_coordinate * copy = wave_coordinate_copy (c);
    wave_coordinate_set_plus (shifted, minus, copy);
    _wave_code_generation_fprint_tab_with_init(code_file, list, shifted, "");
    wave_coordinate_free (shifted);
}

static void _print_unary_int_float (FILE * code_file, const wave_int_list * list, const wave_coordinate * c, wave_atom_type t, const char * type_string, const char * op)
{
    _generate_type_assignement (code_file, list, c, t);
    _generate_content_assignement (code_file, list, c, t);
    fprintf (code_file, " = wave_%s_%s (", type_string, op);
    _print_tab_minus (code_file, list, c, -1);
    fprintf (code_file, "._content.%s", _atom_type_strings[t]);
    fprintf (code_file, ");\n");
}

static void _unary_int_float (FILE * code_file, const wave_collection * collection, const char * op)
{
    wave_collection * previous = wave_collection_get_previous (collection);
    wave_collection_type tc = wave_collection_get_type (previous);
    if (tc == WAVE_COLLECTION_ATOM)
    {
        wave_atom * a = wave_collection_get_atom (previous);
        wave_atom_type ta = wave_atom_get_type (a);
        wave_int_list * indexes = wave_collection_get_full_indexes (wave_collection_get_parent(collection));
        wave_coordinate * c = wave_collection_get_coordinate (collection);
        if (ta == WAVE_ATOM_LITERAL_INT)
            _print_unary_int_float (code_file, indexes, c, ta, "int", op);
        else if (ta == WAVE_ATOM_LITERAL_FLOAT)
            _print_unary_int_float (code_file, indexes, c, ta, "float", op);
        else
        {
            fprintf (stderr, "stderror\n");
            exit (1);
        }
    }
}

static void _unary_float (FILE * code_file, const wave_collection * collection, const char * op)
{
    wave_collection * previous = wave_collection_get_previous (collection);
    wave_collection_type tc = wave_collection_get_type (previous);
    if (tc == WAVE_COLLECTION_ATOM)
    {
        wave_atom * a = wave_collection_get_atom (previous);
        wave_atom_type ta = wave_atom_get_type (a);
        wave_int_list * indexes = wave_collection_get_full_indexes (wave_collection_get_parent(collection));
        wave_coordinate * c = wave_collection_get_coordinate (collection);
        if (ta == WAVE_ATOM_LITERAL_INT)
            _print_unary_int_float (code_file, indexes, c, ta, "int", op);
        else if (ta == WAVE_ATOM_LITERAL_FLOAT)
            _print_unary_int_float (code_file, indexes, c, ta, "float", op);
        else
        {
            fprintf (stderr, "stderror\n");
            exit (1);
        }
    }
}

static void _unary_plus (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "unary_plus");
}

static void _unary_minus (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "unary_minus");
}

static void _unary_increment (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "increment");
}

static void _unary_decrement (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "decrement");
}

static void _unary_sqrt (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "sqrt");
}

static void _unary_sin (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "sin");
}

static void _unary_cos (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "cos");
}

static void _unary_log (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "log");
}

static void _unary_exp (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "exp");
}

static void _unary_ceil (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "ceil");
}

static void _unary_floor (FILE * code_file, const wave_collection * collection)
{
    _unary_int_float (code_file, collection, "floor");
}

static void (* const _operator_functions[]) (FILE *, const wave_collection *) =
{
    [WAVE_OP_UNARY_PLUS]                = _unary_plus,
    [WAVE_OP_UNARY_MINUS]               = _unary_minus,
    [WAVE_OP_UNARY_INCREMENT]           = _unary_increment,
    [WAVE_OP_UNARY_DECREMENT]           = _unary_decrement,
    [WAVE_OP_UNARY_SQRT]                = _unary_sqrt,
    [WAVE_OP_UNARY_SIN]                 = _unary_sin,
    [WAVE_OP_UNARY_COS]                 = _unary_cos,
    [WAVE_OP_UNARY_NOT]                 = NULL,
    [WAVE_OP_UNARY_LOG]                 = _unary_log,
    [WAVE_OP_UNARY_EXP]                 = _unary_exp,
    [WAVE_OP_UNARY_CEIL]                = _unary_ceil,
    [WAVE_OP_UNARY_FLOOR]               = _unary_floor,
    [WAVE_OP_BINARY_PLUS]               = NULL,
    [WAVE_OP_BINARY_MINUS]              = NULL,
    [WAVE_OP_BINARY_MIN]                = NULL,
    [WAVE_OP_BINARY_MAX]                = NULL,
    [WAVE_OP_BINARY_TIMES]              = NULL,
    [WAVE_OP_BINARY_DIVIDE]             = NULL,
    [WAVE_OP_BINARY_MOD]                = NULL,
    [WAVE_OP_BINARY_EQUALS]             = NULL,
    [WAVE_OP_BINARY_DIFFERS]            = NULL,
    [WAVE_OP_BINARY_LESSER_OR_EQUALS]   = NULL,
    [WAVE_OP_BINARY_GREATER_OR_EQUALS]  = NULL,
    [WAVE_OP_BINARY_GREATER]            = NULL,
    [WAVE_OP_BINARY_LESSER]             = NULL,
    [WAVE_OP_BINARY_AND]                = NULL,
    [WAVE_OP_BINARY_OR]                 = NULL,
    [WAVE_OP_BINARY_GET]                = NULL,
    [WAVE_OP_SPECIFIC_ATOM]             = NULL,
    [WAVE_OP_SPECIFIC_STOP]             = NULL,
    [WAVE_OP_SPECIFIC_CUT]              = NULL,
    [WAVE_OP_SPECIFIC_READ]             = NULL,
    [WAVE_OP_SPECIFIC_PRINT]            = NULL,
    [WAVE_OP_UNKNOWN]                   = NULL,
};

static void _wave_code_generation_fprint_operator(FILE* code_file, const wave_collection* collection){
    wave_atom * a = wave_collection_get_atom (collection);
    wave_operator o = wave_atom_get_operator (a);
    if (o >= 0 && o < WAVE_OP_UNKNOWN)
        if (_operator_functions[o] != NULL)
            _operator_functions[o] (code_file, collection);
}

static void _wave_code_generation_fprint_path(FILE* code_file, const wave_collection* collection){
    (void) code_file; (void) collection;
}
