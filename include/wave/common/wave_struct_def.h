#ifndef __WAVE8STRUCT_DEF_H__
#define __WAVE8STRUCT_DEF_H__

#include "wave/common/wave_types.h"

typedef enum wave_data_type{
    WAVE_DATA_INT = 0,
    WAVE_DATA_FLOAT,
    WAVE_DATA_CHAR,
    WAVE_DATA_STRING,
    WAVE_DATA_BOOL,
    WAVE_DATA_UNKNOWN,
} wave_data_type;

typedef struct wave_data{
    wave_data_type _type;
    union{
        wave_int _int;
        wave_float _float;
        wave_char _char;
        wave_string _string;
        wave_bool _bool;
    } _content;
} wave_data;

#endif // ( __WAVE8STRUCT_DEF_H__ )
