/**
 * \file preproc_utils.h
 * \brief Preproc utils.
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
#ifndef __PREPROC_BUFFER_H
#define __PREPROC_BUFFER_H

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "base_hash_table.h"

/**
 * \brief Concatenate str2 to str1 end.
 * \param str1 One null terminated string.
 * \param str2 One null terminated string.
 * \return A new null terminated string.
 * \retval NULL On failure and errno is set appropriately.
 */
char* preproc_concat_two_strings(const char* str1, const char* str2);

/**
 * \brief Execute perror with the message passing in argument and quit.
 * \param message The phrase to print with perror.
 * \param code Exit code.
 */
static inline void perror_and_quit(const char* message, int code){
    perror(message);
    exit(code);
}

/**
 * \brief Init the preprocessor data structure.
 * \param size The size for the underlying hash table.
 */
void preproc_init(unsigned int size);

/**
 * \brief Print the error.
 * \param first_let The line where the first let appears.
 * \param second_let The line where the second let appears.
 */
static inline int preproc_err_let(const unsigned int first_let, const unsigned int second_let){
    fprintf(stderr, "Error !\nFound a \"Let\", line %u, after a \"Let\", line %u, without a \"be\" between them.", second_let, first_let);
    return 1;
}

/**
 * \brief Print the error.
 * \param line_previous_let The line where the Let appears.
 */
static inline int preproc_err_eof(const unsigned int line_previous_let){
    fprintf(stderr, "Error, found an \"Let\" line %u but no \"be\" detected before the end of file\n", line_previous_let);
    return 1;
}

/**
 * \brief Print the error.
 */
static inline int preproc_err_double_id(void){
    fprintf(stderr, "Error, found two names for the Let definition. Exiting ...\n");
    return 1;
}

/**
 * \brief Copy the string id into the current id.
 * \param id A pointer to a null terminated string which contains the identifier name.
 */
void preproc_new_identifier(const char* id);

/**
 * \brief Get the current identifier.
 * \return A pointer to the null terminated string containing the current identifier.
 */
char* preproc_get_actual_identifier(void);

/**
 * \brief Add the current expression and the current identifier to the data structure underlying.
 * \retval 0 On success.
 * \retval 1 On failure and errno is set appropriately.
 */
int preproc_add_current_id_with_current_expression(void);

/**
 * \brief Clean the data structure.
 */
void preproc_clean(void);

/**
 * \brief Add the definition of the identifier to the current expression.
 * \param id_or_not A pointer to a null terminated string.
 * \retval 0 On success.
 * \retval 1 If the identifier does not exist.
 */
int preproc_add_id_definition_to_current_expression(const char* id_or_not);

/**
 * \brief Add the string to the current expression.
 * \param str A pointer to a null terminated string.
 */
void preproc_add_to_current_expression(const char* str);

/**
 * \brief Test if the identifier already exists.
 * \param identifier A null terminated string which represents the identifier.
 * \param associated_value A pointer to a char* which will contain the value associated with the identifier if it exists.
 * \retval 0 On success and *associated_value is set to point to the value associated in the data structure.
 * \retval 1 On identifier not found.
 */
int preproc_check_identifier(char* identifier, char** associated_value);

#endif // ( __PREPROC_BUFFER_H )
