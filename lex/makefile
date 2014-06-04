HASH_PATH = ../hash_table_c_language/
HASH_INCLUDE = $(HASH_PATH)include/
HASH_LIB = $(HASH_PATH)lib/
INCLUDE_PATH = include/
SRC_PATH = src/
OBJ_PATH = obj/
YACCPATH = ../grammar/
YACCNAME = wave_yacc.o
CC = gcc
IFLAGS = -I$(YACCPATH) -I$(INCLUDE_PATH) -I$(HASH_INCLUDE)
LINK_FLAGS = -L$(HASH_LIB) -lhash -lfl -ly

vpath %.c $(SRC_PATH)
vpath %.h $(INCLUDE_PATH)
vpath libhash.a $(HASH_PATH)

all : wave_lex

libhash.a :
	(cd $(HASH_PATH); make)

wave_lex.c : wave_lex.l
	lex -o $@ $<

wave_lex.o : wave_lex.c
	(cd $(YACCPATH); make)
	$(CC) $(IFLAGS) -c $<

wave_lex : wave_lex.o libhash.a
	$(CC) -o $@ $(YACCPATH)$(YACCNAME) $< $(LINK_FLAGS)

wave_preprocessor.c : wave_preprocessor.l
	lex -o $@ $<

wave_preprocessor.o : wave_preprocessor.c
	$(CC) $(IFLAGS) -c $<

wave_preprocessor : wave_preprocessor.o
	$(CC) -o $@ $< $(LINK_FLAGS)

preproc_utils.o : preproc_utils.c preproc_utils.h | obj
	$(CC) -c $< -I$(INCLUDE_PATH) -o $(OBJ_PATH)$@

obj :
	mkdir -p $(OBJ_PATH)

clean :
	@rm -rf *.o *.c wave_lex wave_preprocessor $(OBJ_PATH) 2>/dev/null; echo Directory cleaned.

clean-all :
	@(cd $(YACCPATH); make clean 1>/dev/null 2>&1; echo $(YACCPATH) Cleaned.)
	@(cd $(HASH_PATH); make clean 1>/dev/null 2>&1; echo $(HASH_PATH) Cleaned.)
	@rm -rf *.o *.c wave_lex wave_preprocessor $(OBJ_PATH) 2>/dev/null; echo Directory cleaned.
