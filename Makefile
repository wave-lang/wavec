################################################################################
# Programs
################################################################################
CC = gcc
LEX = lex
YACC = yacc
DOC_GEN = doxygen

################################################################################
# Paths
################################################################################
PATH_SRC = src
PATH_OBJ = obj
PATH_DOC = doc
PATH_LIB = lib
PATH_BIN = bin
PATH_TESTS = tests
PATH_INCLUDE = include
PATH_TESTS_SRC = $(PATH_TESTS)/$(PATH_SRC)
PATH_TESTS_INCLUDE = $(PATH_TESTS)/$(PATH_INCLUDE)

PATH_SRC_AST = $(PATH_SRC)/wave/ast
PATH_SRC_COMMON = $(PATH_SRC)/wave/common
PATH_SRC_GENERATION = $(PATH_SRC)/wave/generation
PATH_INCLUDE_AST = $(PATH_INCLUDE)/wave/ast
PATH_INCLUDE_COMMON = $(PATH_INCLUDE)/wave/common
PATH_INCLUDE_GENERATION = $(PATH_INCLUDE)/wave/generation

PATH_YACC = yacc
PATH_INCLUDE_YACC = $(PATH_INCLUDE)/wave/yacc
PATH_SRC_YACC = $(PATH_SRC)/wave/yacc

PATH_HASH = hash_table_c_language
PATH_INCLUDE_HASH = $(PATH_HASH)/include
PATH_LIB_HASH = $(PATH_HASH)/lib

PATH_LEX = lex
PATH_INCLUDE_LEX = $(PATH_INCLUDE)/wave/lex
PATH_SRC_LEX = $(PATH_SRC)/wave/lex

################################################################################
# Flags
################################################################################
FLAGS_CC_INCLUDE = -I$(PATH_INCLUDE) -I$(PATH_INCLUDE_YACC) \
	-I$(PATH_TESTS_INCLUDE) -I$(PATH_INCLUDE_HASH)
FLAGS_CC_DEBUG = -g
FLAGS_CC_WARNINGS = -pedantic -Wall -Wextra -Wfloat-equal -Wdouble-promotion \
	-Wswitch-default -Winit-self -Wshadow -Wbad-function-cast -Wcast-qual \
	-Wcast-align -Wconversion -Wlogical-op -Wstrict-prototypes -Wnested-externs
FLAGS_CC_MISC = -std=gnu99 -O0
FLAGS_CC = $(FLAGS_CC_INCLUDE) $(FLAGS_CC_WARNINGS) $(FLAGS_CC_DEBUG) \
	$(FLAGS_CC_MISC)
FLAGS_CC_LEX_YACC = -W $(FLAGS_CC_INCLUDE) $(FLAGS_CC_DEBUG) $(FLAGS_CC_MISC)
FLAGS_CC_LIB = -L$(PATH_LIB) -L$(PATH_LIB_HASH)
FLAGS_CC_LINK = $(FLAGS_CC_LIB) -lhash -lfl -ly -lm -lwaveast -lwave
FLAGS_CC_UNIT_TESTS = -lwavetests $(FLAGS_CC_LINK) -lcunit

################################################################################
# Files
################################################################################
vpath %.h $(PATH_INCLUDE) $(PATH_TESTS_INCLUDE) $(PATH_INCLUDE_AST) \
	$(PATH_INCLUDE_COMMON) $(PATH_INCLUDE_GENERATION)
vpath %.c $(PATH_SRC) $(PATH_TESTS_SRC) $(PATH_SRC_AST) $(PATH_SRC_COMMON) \
	$(PATH_SRC_GENERATION)
vpath %.o $(PATH_OBJ)
vpath %.a $(PATH_LIB) $(PATH_LIB_HASH)
vpath %.y $(PATH_YACC)
vpath %.l $(PATH_LEX)
vpath wavec $(PATH_BIN)
vpath main $(PATH_BIN)
vpath wave_yacc.c $(PATH_SRC_YACC)
vpath wave_lex.c $(PATH_SRC_LEX)

################################################################################
# Main
################################################################################

all: wavec main

################################################################################
# Hash
################################################################################

libhash.a:
	(cd $(PATH_HASH); make)

################################################################################
# Yacc
################################################################################

wave_yacc.c: wave.y | yacc_dir
	$(YACC) -d -o wave_yacc.c $<
	mv wave_yacc.c $(PATH_SRC_YACC)/
	mv wave_yacc.h $(PATH_INCLUDE_YACC)/

wave_yacc.o: wave_yacc.c | obj_dir
	$(CC) $(FLAGS_CC_LEX_YACC) -c $(PATH_SRC_YACC)/wave_yacc.c -o $(PATH_OBJ)/wave_yacc.o

################################################################################
# Lex
################################################################################

wavec: wave_lex.o wave_yacc.o libhash.a libwave.a libwaveast.a | bin_dir
	$(CC) -o $(PATH_BIN)/$@ $(PATH_OBJ)/wave_lex.o $(PATH_OBJ)/wave_yacc.o $(FLAGS_CC_LINK)

wave_preprocessor: wave_preprocessor.o preproc_utils.o libhash.a | bin_dir
	$(CC) $(FLAGS_CC) -o $(PATH_BIN)/$@ $(PATH_OBJ)/wave_preprocessor.o \
		$(PATH_OBJ)/preproc_utils.o $(FLAGS_CC_LINK)

wave_lex.o: wave_lex.c wave_yacc.o
	$(CC) $(FLAGS_CC_LEX_YACC) -c $(PATH_SRC_LEX)/wave_lex.c -o $(PATH_OBJ)/$@

wave_lex.c: wave_lex.l
	$(LEX) -o $(PATH_SRC_LEX)/$@ $<

wave_preprocessor.c: wave_preprocessor.l
	$(LEX) -o $(PATH_SRC_LEX)/$@ $<

wave_preprocessor.o: wave_preprocessor.c | obj
	$(CC) $(FLAGS_CC_LEX_YACC) -c $(PATH_SRC_LEX)/$< -o $(PATH_OBJ)/$@

preproc_utils.o: preproc_utils.c preproc_utils.h | obj
	$(CC) $(FLAGS_CC) -c $< -o $(PATH_OBJ)/$@

################################################################################
# Compiling
################################################################################

main: main.o libhash.a libwave.a libwaveast.a | bin_dir
	$(CC) -o $(PATH_BIN)/$@ $(PATH_OBJ)/main.o $(FLAGS_CC_LINK)

unit_tests: unit_tests.o libhash.a libwave.a libwaveast.a libwavetests.a | bin_dir
	$(CC) -o $(PATH_BIN)/$@ $(PATH_OBJ)/unit_tests.o $(FLAGS_CC_UNIT_TESTS)

print_tests: test_ast_print.o libhash.a libwave.a libwaveast.a | bin_dir
	$(CC) -o $(PATH_BIN)/$@ $(PATH_OBJ)/test_ast_print.o $(FLAGS_CC_LINK)

%.o: %.c | obj_dir
	$(CC) $(FLAGS_CC) -o $(PATH_OBJ)/$@ -c $<

# Wave AST
wave_operator.o: wave_operator.c wave_operator.h
wave_path.o: wave_path.c wave_path.h
wave_atom.o: wave_atom.c wave_atom.h wave_types.h wave_path.h wave_operator.h
wave_collection.o: wave_collection.c wave_collection.h wave_atom.h
wave_phrase.o: wave_phrase.c wave_phrase.h wave_collection.h
wave_int_list.o: wave_int_list.c wave_int_list.h
wave_coordinate.o: wave_coordinate.c wave_coordinate.h wave_int_list.h
wave_collection_info.o: wave_collection_info.c wave_collection_info.h \
	wave_int_list.h wave_coordinate.h
wave_code_generation.o: wave_code_generation.c wave_code_generation.h
main.o: main.c wave_path.h wave_atom.h wave_collection.h wave_compiler_version.h

# Wave common
wave_types.o: wave_types.c wave_types.h
wave_headers.o: wave_headers.c wave_headers.h

# Tests
test_ast_print.o: test_ast_print.c
test_wave_path.o: test_wave_path.c test_wave_path.h wave_path.h
test_wave_atom.o: test_wave_atom.c test_wave_atom.h wave_atom.h
test_wave_collection.o: test_wave_collection.c test_wave_collection.h wave_collection.h
unit_tests.o: unit_tests.c wave_test_suites.h

# Wave common lib
libwave.a: wave_types.o wave_headers.o | lib_dir
	ar crvs $(PATH_LIB)/libwave.a $(PATH_OBJ)/wave_types.o \
		$(PATH_OBJ)/wave_headers.o

# Compiler lib
libwaveast.a: wave_operator.o wave_path.o wave_atom.o \
	wave_collection.o wave_phrase.o wave_int_list.o wave_coordinate.o \
	wave_code_generation.o wave_collection_info.o | lib_dir
	ar crvs $(PATH_LIB)/libwaveast.a \
		$(PATH_OBJ)/wave_operator.o $(PATH_OBJ)/wave_path.o \
		$(PATH_OBJ)/wave_atom.o $(PATH_OBJ)/wave_collection.o \
		$(PATH_OBJ)/wave_phrase.o $(PATH_OBJ)/wave_int_list.o \
		$(PATH_OBJ)/wave_coordinate.o $(PATH_OBJ)/wave_collection_info.o \
		$(PATH_OBJ)/wave_code_generation.o

# Unit tests lib
libwavetests.a: test_wave_path.o test_wave_atom.o test_wave_collection.o | lib_dir
	ar crvs $(PATH_LIB)/libwavetests.a $(PATH_OBJ)/test_wave_path.o \
		$(PATH_OBJ)/test_wave_atom.o $(PATH_OBJ)/test_wave_collection.o

test: tests
tests: unit_tests print_tests

################################################################################
# Directories
################################################################################
doc: clean_doc
	@$(DOC_GEN)

obj_dir:
	@mkdir -p $(PATH_OBJ)

lib_dir:
	@mkdir -p $(PATH_LIB)

bin_dir:
	@mkdir -p $(PATH_BIN)

yacc_dir:
	@mkdir -p $(PATH_INCLUDE_YACC) $(PATH_SRC_YACC)

################################################################################
# Cleaning
################################################################################
clean: clean_yacc clean_lex
	@rm -rf $(PATH_BIN) $(PATH_OBJ) $(PATH_LIB)
	@echo "Clean."

cleanyacc: clean_yacc
clean-yacc: clean_yacc
clean_yacc:
	@rm -rf $(PATH_INCLUDE_YACC) $(PATH_SRC_YACC)

cleanlex: clean_lex
clean-lex: clean_lex
clean_lex:
	@rm -rf $(PATH_SRC_LEX)/wave_preprocessor.c $(PATH_SRC_LEX)/wave_lex.c

cleanhash: clean_hash
clean-hash: clean_hash
clean_hash:
	@(cd $(PATH_HASH); make clean;)

cleandoc: clean_doc
clean-doc: clean_doc
clean_doc:
	@rm -rf $(PATH_DOC)

cleanall: clean_all
clean-all: clean_all
clean_all: clean clean_doc clean_hash
	@echo "Super clean."
