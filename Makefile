################################################################################
# Programs
################################################################################
CC = gcc
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

################################################################################
# Flags
################################################################################
FLAGS_CC_INCLUDE = -I$(PATH_INCLUDE) -I$(PATH_TESTS_INCLUDE)
FLAGS_CC_DEBUG = -g
FLAGS_CC_WARNINGS = -Wall -Wextra -Wfloat-equal -Wdouble-promotion \
	-Wswitch-default -Winit-self -Wshadow -Wbad-function-cast -Wcast-qual \
	-Wcast-align -Wconversion -Wlogical-op -Wstrict-prototypes -Wnested-externs
FLAGS_CC = $(FLAGS_CC_INCLUDE) -std=c99 -pedantic -O0 $(FLAGS_CC_WARNINGS) \
	$(FLAGS_CC_DEBUG)
FLAGS_CC_LIB = -L$(PATH_LIB)
FLAGS_CC_LINK = -lm -lwave -lwaveast
FLAGS_CC_UNIT_TESTS = -lcunit -lm -lwavetests $(FLAGS_CC_LINK)

################################################################################
# Files
################################################################################
vpath %.h $(PATH_INCLUDE) $(PATH_TESTS_INCLUDE) $(PATH_INCLUDE_AST) \
	$(PATH_INCLUDE_COMMON) $(PATH_INCLUDE_GENERATION)
vpath %.c $(PATH_SRC) $(PATH_TESTS_SRC) $(PATH_SRC_AST) $(PATH_SRC_COMMON) \
	$(PATH_SRC_GENERATION)
vpath %.o $(PATH_OBJ)
vpath %.a $(PATH_LIB)
vpath main $(PATH_BIN)

################################################################################
# Compiling
################################################################################
all : main

main: main.o libwave.a libwaveast.a | bin_dir
	$(CC) -o $(PATH_BIN)/$@ $(PATH_OBJ)/main.o $(FLAGS_CC_LIB) $(FLAGS_CC_LINK)

unit_tests: unit_tests.o libwave.a libwaveast.a libwavetests.a | bin_dir
	$(CC) -o $(PATH_BIN)/$@ $(PATH_OBJ)/unit_tests.o $(FLAGS_CC_LIB) \
		$(FLAGS_CC_UNIT_TESTS)

print_tests: test_ast_print.o libwave.a libwaveast.a | bin_dir
	$(CC) -o $(PATH_BIN)/$@ $(PATH_OBJ)/test_ast_print.o $(FLAGS_CC_LIB) \
		$(FLAGS_CC_LINK)

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

# Tests
test_ast_print.o: test_ast_print.c
test_wave_path.o: test_wave_path.c test_wave_path.h wave_path.h
test_wave_atom.o: test_wave_atom.c test_wave_atom.h wave_atom.h
test_wave_collection.o: test_wave_collection.c test_wave_collection.h wave_collection.h
unit_tests.o: unit_tests.c wave_test_suites.h

# Wave common lib
libwave.a: wave_types.o | lib_dir
	ar crvs $(PATH_LIB)/libwave.a $(PATH_OBJ)/wave_types.o

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

################################################################################
# Cleaning
################################################################################
clean:
	@rm -rf $(PATH_BIN) $(PATH_OBJ) $(PATH_LIB)
	@echo "Clean."

cleandoc: clean_doc
clean_doc:
	@rm -rf $(PATH_DOC)

cleanall: clean_all
clean_all: clean clean_doc
	@echo "Super clean."
