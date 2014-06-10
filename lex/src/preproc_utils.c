/*
   The MIT License (MIT)

   Copyright (c) 2014 Éric VIOLARD, Maxime SCHMITT, Harenome RAZANAJATO RANAIVOARIVONY

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
   */

#include "preproc_utils.h"

static HT_hash_table *_hash_table = NULL;
static char* _current_id = NULL;
static char* _current_expression = NULL;

enum{
    SQUARE_ROOT = 0,
    SIN,
    COS,
    NOT,
    LOG,
    EXP,
    CEIL,
    FLOOR,
    MIN,
    MAX,
    MOD,
    AND,
    OR,
    GET,
    PREC,
    SUCC,
    UP,
    DOWN,
    REWIND,
    READ,
    PRINT,
    ATOM,
    END_RES_ID
};

static const char* wave_reserved_id[] = {
    [SQUARE_ROOT] = "sqrt",
    [SIN] = "sin",
    [COS] = "cos",
    [NOT] = "not",
    [LOG] = "log",
    [EXP] = "exp",
    [CEIL] = "ceil",
    [FLOOR] = "floor",
    [MIN] = "min",
    [MAX] = "max",
    [MOD] = "mod",
    [AND] = "and",
    [OR] = "or",
    [GET] = "get",
    [PREC] = "p",
    [SUCC] = "s",
    [UP] = "u",
    [DOWN] = "d",
    [REWIND] = "r",
    [READ] = "read",
    [PRINT] = "print",
    [ATOM] = "atom"
};

void preproc_init(unsigned int size){
    _hash_table = HT_new_hash_string(size);
}

char* preproc_concat_two_strings(const char* str1, const char* str2){
    size_t len1, len2;
    len1 = strlen(str1);
    len2 = strlen(str2);
    char* new_one = calloc(len1 + len2 + 1, sizeof(char));
    if( new_one != NULL )
        new_one = strcpy(new_one, str1);
    new_one = strcat(new_one, str2);
    return new_one;
}

void preproc_new_identifier(const char* id){
    if(_current_id != NULL){
        free(_current_id);
    }
    _current_id = strdup(id);
}

static int preproc_add_value_with_previous_id(const char* value){
    if(_current_id == NULL){
        fprintf(stderr, "Aucun id n'a été enregistré précédement\n");
        return 2;
    }
    return HT_add_element_string(_hash_table, _current_id, value);
}

static int preproc_get_value_by_id(const char* identifier, char** value){
    if( identifier == NULL )
        return HT_get_element_string(_hash_table, _current_id, value);
    return HT_get_element_string(_hash_table, identifier, value);
}

char* preproc_get_actual_identifier(void){
    return _current_id;
}

void preproc_clean(void){
    if(_current_id != NULL)
        free(_current_id);
    if(_hash_table != NULL)
        HT_delete_pointer(_hash_table);
}

int preproc_add_current_id_with_current_expression(void){
    if(_current_expression == NULL){
        fprintf(stderr, "Aucune expression trouvée\n");
        return 1;
    }
    if( preproc_add_value_with_previous_id(_current_expression) == 1 ){
        fprintf(stderr, "The identifier \"%s\" is already used.\n", _current_id);
        return 1;
    }
    free(_current_expression);
    _current_expression = NULL;

    char* value;
    if(preproc_get_value_by_id(NULL, &value) == 0)
        printf("Expression :\n%s\n", value);
    else
        printf("\nNON TROUVE\n"); /* add in the expression found buffer */
    return 0;
}

int preproc_is_reserved_id(const char* id){
    int i;
    for(i=0; i < END_RES_ID; i++)
        if( strcmp(id, wave_reserved_id[i]) == 0 )
            return 1;
    return 0;
}

void preproc_add_to_current_expression(const char* str){
        if(_current_expression == NULL)
            _current_expression = strdup(str);
        else{
            char* tmp_string = preproc_concat_two_strings(_current_expression, str);
            free(_current_expression);
            _current_expression = tmp_string;
        }
}

int preproc_test_or_add_identifier(const char* id_or_not){
    if( preproc_is_reserved_id(id_or_not) ){
        preproc_add_to_current_expression(id_or_not);
    }
    else{
        char* value;
        int retval = preproc_get_value_by_id(id_or_not, &value);
        if(retval == 0){
            preproc_add_to_current_expression(value);
        }
        else{
            fprintf(stderr, "This identifier does not exist %s.\n", id_or_not);
            return 1;
        }
    }
    return 0;
}
int preproc_check_identifier(char* identifier, char** associated_value){
    char* val;
    if(preproc_is_reserved_id(identifier))
        *associated_value = identifier;
    else{
        if( preproc_get_value_by_id(identifier, &val) == 0){
            *associated_value = val;
        }
        else{
            return 1;
        }
    }
    return 0;
}
