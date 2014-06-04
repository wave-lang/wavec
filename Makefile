CC = gcc
DOC_GEN = doxygen

PATH_SRC = src
PATH_OBJ = obj
PATH_DOC = doc
PATH_LIB = lib
PATH_BIN = bin
PATH_TESTS = tests
PATH_INCLUDE = include
PATH_TESTS_SRC = $(PATH_TESTS)/$(PATH_SRC)
PATH_TESTS_INCLUDE = $(PATH_TESTS)/$(PATH_INCLUDE)

FLAGS_INCLUDE = -I$(PATH_INCLUDE) -I$(PATH_TESTS_INCLUDE)
FLAGS_CC_DEBUG = -g
FLAGS_CC_WARNINGS = -Wall -Wextra -Wfloat-equal -Wdouble-promotion -Wswitch-default -Winit-self -Wshadow -Wbad-function-cast -Wcast-qual -Wcast-align -Wconversion -Wlogical-op -Wstrict-prototypes -Wnested-externs
FLAGS_CC = $(FLAGS_INCLUDE) -std=c99 -pedantic -O0 $(FLAGS_CC_WARNINGS) $(FLAGS_CC_DEBUG)
FLAGS_CC_LIB_DIRS = -L$(PATH_LIB)
FLAGS_CC_LIB = -lwavecompiler
FLAGS_CC_UNIT_TESTS = -lcunit -lm -lwavetests $(FLAGS_CC_LIB)

vpath %.h $(PATH_INCLUDE) $(PATH_TESTS_INCLUDE)
vpath %.c $(PATH_SRC) $(PATH_TESTS_SRC)
vpath %.o $(PATH_OBJ)
vpath %.a $(PATH_LIB)

all : main

main: main.o libwavecompiler.a | bin_dir
		$(CC) -o $(PATH_BIN)/$@ $(PATH_OBJ)/main.o $(FLAGS_CC_LIB_DIRS) $(FLAGS_CC_LIB)

unit_tests: unit_tests.o libwavecompiler.a libwavetests.a | bin_dir
		$(CC) -o $(PATH_BIN)/$@ $(PATH_OBJ)/unit_tests.o $(FLAGS_CC_LIB_DIRS) $(FLAGS_CC_UNIT_TESTS)

print_tests: test_ast_print.o libwavecompiler.a | bin_dir
		$(CC) -o $(PATH_BIN)/$@ $(PATH_OBJ)/test_ast_print.o $(FLAGS_CC_LIB_DIRS) $(FLAGS_CC_LIB)


%.o: %.c | obj_dir
		$(CC) $(FLAGS_CC) -o $(PATH_OBJ)/$@ -c $<

# Compiler
wave_operator.o: wave_operator.c wave_operator.h
wave_path.o: wave_path.c wave_path.h
wave_atom.o: wave_atom.c wave_atom.h wave_types.h wave_path.h wave_operator.h
wave_collection.o: wave_collection.c wave_collection.h wave_atom.h
main.o: main.c wave_path.h wave_atom.h wave_collection.h wave_compiler_version.h

# Tests
test_ast_print.o: test_ast_print.c
test_wave_path.o: test_wave_path.c test_wave_path.h wave_path.h
test_wave_atom.o: test_wave_atom.c test_wave_atom.h wave_atom.h
test_wave_collection.o: test_wave_collection.c test_wave_collection.h wave_collection.h
unit_tests.o: unit_tests.c wave_test_suites.h

# Compiler lib
libwavecompiler.a: wave_operator.o wave_path.o wave_atom.o wave_collection.o | lib_dir
		ar -crv $(PATH_LIB)/libwavecompiler.a $(PATH_OBJ)/wave_operator.o $(PATH_OBJ)/wave_path.o $(PATH_OBJ)/wave_atom.o $(PATH_OBJ)/wave_collection.o
		ranlib $(PATH_LIB)/libwavecompiler.a

# Unit tests lib
libwavetests.a: test_wave_path.o test_wave_atom.o test_wave_collection.o | lib_dir
		ar -crv $(PATH_LIB)/libwavetests.a $(PATH_OBJ)/test_wave_path.o $(PATH_OBJ)/test_wave_atom.o $(PATH_OBJ)/test_wave_collection.o
		ranlib $(PATH_LIB)/libwavetests.a

test: tests
tests: unit_tests print_tests

doc: clean_doc
		@$(DOC_GEN)

obj_dir:
		@mkdir -p $(PATH_OBJ)

lib_dir:
		@mkdir -p $(PATH_LIB)

bin_dir:
		@mkdir -p $(PATH_BIN)

clean:
		@rm -rf $(PATH_BIN) $(PATH_OBJ) $(PATH_LIB)
		@echo "Clean."

cleandoc: clean_doc
clean_doc:
		@rm -rf $(PATH_DOC)

cleanall: clean_all
clean_all: clean clean_doc
		@echo "Super clean."
