#ifndef __WAVE8STRUCT_DEF_H__
#define __WAVE8STRUCT_DEF_H__

#include "wave/common/wave_types.h"

/**
 * \class wave_data_type
 * \brief Used inside the \c wave_data structure to know wich data is being stored inside.
 * \see wave_types.h
 */
typedef enum wave_data_type{
    WAVE_DATA_INT = 0,          /**< A integer value */
    WAVE_DATA_FLOAT,            /**< A floating point value */
    WAVE_DATA_CHAR,             /**< A character value */
    WAVE_DATA_STRING,           /**< A string value */
    WAVE_DATA_BOOL,             /**< A boolean value */
    WAVE_DATA_UNKNOWN,          /**< Used when no type is set yet */
} wave_data_type;

/**
 * \brief The data structure used for the storage of the wave data types.
 * \see wave_types.h
 */
typedef struct wave_data{
    wave_data_type _type;           /**< The type of the current data */
    union{
        wave_int _int;              /**< To store an integer value */
        wave_float _float;          /**< To store an floating point value */
        wave_char _char;            /**< To store a character value */
        wave_string _string;        /**< To store a string value */
        wave_bool _bool;            /**< To store a boolean value */
    } _content;                     /**< The union to store multiple data values */
} wave_data;

#endif // ( __WAVE8STRUCT_DEF_H__ )
