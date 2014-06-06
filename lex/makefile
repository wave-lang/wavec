HASH_PATH = ../hash_table_c_language/
HASH_INCLUDE = $(HASH_PATH)include/
HASH_LIB = $(HASH_PATH)lib/
INCLUDE_PATH = include/
SRC_PATH = src/
OBJ_PATH = obj/
YACCPATH = ../grammar/

YACCNAME = wave_yacc.o

CC = gcc -std=gnu99

DEBUG_FLAGS = -g
WARNING_FLAGS = -Wall -Wextra -Wfloat-equal -Wdouble-promotion -Wswitch-default -Winit-self -Wshadow -Wbad-function-cast -Wcast-qual -Wcast-align -Wconversion -Wlogical-op -Wstrict-prototypes -Wnested-externs
COMPILE_FLAGS = $(WARNING_FLAGS) # $(DEBUG_FLAGS)

IFLAGS = -I$(YACCPATH) -I$(INCLUDE_PATH) -I$(HASH_INCLUDE)
LINK_FLAGS = -L$(HASH_LIB) -lhash -lfl -ly

vpath %.c $(SRC_PATH)
vpath %.h $(INCLUDE_PATH)
vpath %.o $(OBJ_PATH)
vpath libhash.a $(HASH_LIB)

wave_lex : wave_lex.o libhash.a preproc_utils.o
	$(CC) -o $@ $(YACCPATH)$(YACCNAME) $< $(OBJ_PATH)preproc_utils.o $(LINK_FLAGS)

libhash.a :
	(cd $(HASH_PATH); make)

wave_lex.c : wave_lex.l
	lex -o $@ $<

wave_lex.o : wave_lex.c
	(cd $(YACCPATH); make)
	$(CC) $(IFLAGS) -c $< -o $@

wave_preprocessor.c : wave_preprocessor.l
	lex -o $@ $<

wave_preprocessor.o : wave_preprocessor.c
	$(CC) $(IFLAGS) -c $<

wave_preprocessor : wave_preprocessor.o
	$(CC) -o $@ $< $(LINK_FLAGS)

preproc_utils.o : preproc_utils.c preproc_utils.h | obj
	$(CC) $(WARNING_FLAGS) -c $< -I$(IFLAGS) -o $(OBJ_PATH)$@

obj :
	mkdir -p $(OBJ_PATH)

clean :
	@rm -rf *.o *.c wave_lex wave_preprocessor $(OBJ_PATH) 2>/dev/null; echo Directory cleaned.

clean-all :
	@(cd $(YACCPATH); make clean 1>/dev/null 2>&1; echo $(YACCPATH) Cleaned.)
	@(cd $(HASH_PATH); make clean 1>/dev/null 2>&1; echo $(HASH_PATH) Cleaned.)
	@rm -rf *.o *.c wave_lex wave_preprocessor $(OBJ_PATH) 2>/dev/null; echo Directory cleaned.
