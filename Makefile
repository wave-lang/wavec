CC = gcc
DOC_GEN = doxygen

PATH_SRC = src
PATH_OBJ = obj
PATH_DOC = doc
PATH_LIB = lib
PATH_BIN = bin
PATH_TESTS = tests
PATH_INCLUDE = include

FLAGS_INCLUDE = -I$(PATH_INCLUDE)
FLAGS_CC_DEBUG = -g
FLAGS_CC_WARNINGS = -Wall -Wextra
FLAGS_CC = $(FLAGS_INCLUDE) -std=c99 -pedantic -O0 $(FLAGS_CC_WARNINGS) $(FLAGS_CC_DEBUG)
FLAGS_LIB = $(PATH_LIB)

vpath %.h $(PATH_INCLUDE) $(PATH_TESTS)/include
vpath %.c $(PATH_SRC) $(PATH_SRC)/src
vpath %.o $(PATH_OBJ)
vpath %.a $(PATH_LIB)

all : main

%.o: %.c | obj_dir
		$(CC) $(FLAGS_CC) -o $(PATH_OBJ)/$@ -c $<

main:
		@echo "TODO."

test: tests
tests: main
		@echo "TODO."

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
