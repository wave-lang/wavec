################################################################################
# Programs
################################################################################
CC = gcc
LEX = lex

################################################################################
# Paths
################################################################################
PATH_SRC = src
PATH_OBJ = obj
PATH_INCLUDE = include

PATH_HASH_SRC = ../hash_table_c_language
PATH_HASH_INCLUDE = $(PATH_HASH_SRC)/include
PATH_HASH_LIB = $(PATH_HASH_SRC)/lib

PATH_YACC = ../yacc
PATH_YACC_INCLUDE = $(PATH_YACC)/include
PATH_YACC_OBJ = $(PATH_YACC)/obj

PATH_WAVE_COMPILER = ..
PATH_WAVE_COMPILER_LIB = $(PATH_WAVE_COMPILER)/lib
PATH_WAVE_COMPILER_INCLUDE = $(PATH_WAVE_COMPILER)/include

################################################################################
# Flags
################################################################################
FLAGS_CC_INCLUDE = -I$(PATH_YACC_INCLUDE) -I$(PATH_INCLUDE) -I$(PATH_HASH_INCLUDE) -I$(PATH_WAVE_COMPILER_INCLUDE)
FLAGS_CC_LIB = -L$(PATH_HASH_LIB) -L$(PATH_WAVE_COMPILER_LIB)
FLAGS_CC_LINK = $(FLAGS_CC_LIB) -lhash -lfl -ly -lm
FLAGS_CC_DEBUG = -g
FLAGS_CC_WARNING = -Wall -Wextra -Wfloat-equal -Wdouble-promotion \
	-Wswitch-default -Winit-self -Wshadow -Wbad-function-cast -Wcast-qual \
	-Wcast-align -Wconversion -Wlogical-op -Wstrict-prototypes -Wnested-externs

FLAGS_CC = $(FLAGS_CC_INCLUDE) $(FLAGS_CC_WARNING) -std=c99 -pedantic -O0 # $(FLAGS_CC_DEBUG)

################################################################################
# Files
################################################################################
vpath %.c $(PATH_SRC)
vpath %.h $(PATH_INCLUDE)
vpath %.o $(PATH_OBJ) $(PATH_YACC_OBJ)
vpath *.a $(PATH_HASH_LIB) $(PATH_WAVE_COMPILER_LIB)

################################################################################
# Compiling
################################################################################
all: wave_preprocessor wavec

## Final binaries.
wavec: wave_lex.o wave_yacc libhash.a libwavecompiler.a
	$(CC) -o $@ $(PATH_OBJ)/wave_lex.o $(PATH_YACC_OBJ)/wave_yacc.o $(FLAGS_CC_LINK) -lwavecompiler

wave_preprocessor : wave_preprocessor.o preproc_utils.o libhash.a
	$(CC) $(FLAGS_CC) -o $@ $(PATH_OBJ)/wave_preprocessor.o \
		$(PATH_OBJ)/preproc_utils.o $(FLAGS_CC_LINK)

## Required libraries.
libhash.a :
	(cd $(PATH_HASH_SRC); make)

libwavecompiler.a:
	(cd $(PATH_WAVE_COMPILER); make)

wave_lex.o : wave_lex.c wave_yacc
	$(CC) $(FLAGS_CC) -c $(PATH_SRC)/wave_lex.c -o $(PATH_OBJ)/$@

wave_yacc :
	(cd $(PATH_YACC); make)

wave_lex.c : wave_lex.l
	$(LEX) -o $(PATH_SRC)/$@ $<

wave_preprocessor.c : wave_preprocessor.l
	$(LEX) -o $(PATH_SRC)/$@ $<

wave_preprocessor.o : wave_preprocessor.c | obj
	$(CC) $(FLAGS_CC) -c $(PATH_SRC)/$< -o $(PATH_OBJ)/$@

preproc_utils.o : preproc_utils.c preproc_utils.h | obj
	$(CC) $(FLAGS_CC) -c $< -o $(PATH_OBJ)/$@

################################################################################
# Directories
################################################################################
obj :
	@mkdir -p $(PATH_OBJ)

################################################################################
# Cleaning
################################################################################
clean :
	@rm -rf $(PATH_OBJ) wave_preprocessor wavec $(PATH_SRC)/wave_preprocessor.c \
		$(PATH_SRC)/wave_lex.c 2>/dev/null; echo Directory cleaned.

clean-all : clean
	@(cd $(PATH_YACC); make clean 1>/dev/null 2>&1; echo $(PATH_YACC) Cleaned.)
	@(cd $(PATH_HASH_SRC); make clean 1>/dev/null 2>&1; echo $(PATH_HASH_SRC) Cleaned.)
