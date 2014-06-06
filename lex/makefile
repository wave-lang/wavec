INCLUDE_PATH = include/
SRC_PATH = src/
OBJ_PATH = obj/

HASH_PATH = ../hash_table_c_language/
HASH_INCLUDE = $(HASH_PATH)include/
HASH_LIB = $(HASH_PATH)lib/

YACC_PATH = ../yacc/
YACC_INCLUDE = $(YACC_PATH)include/
YACC_OBJ = $(YACC_PATH)obj/

CC = gcc -std=gnu99

DEBUG_FLAGS = -g
WARNING_FLAGS = -Wall -Wextra -Wfloat-equal -Wdouble-promotion -Wswitch-default -Winit-self -Wshadow -Wbad-function-cast -Wcast-qual -Wcast-align -Wconversion -Wlogical-op -Wstrict-prototypes -Wnested-externs
COMPILE_FLAGS = $(WARNING_FLAGS) # $(DEBUG_FLAGS)

IFLAGS = -I$(YACC_INCLUDE) -I$(INCLUDE_PATH) -I$(HASH_INCLUDE)
LINK_FLAGS = -L$(HASH_LIB) -lhash -lfl -ly

vpath %.c $(SRC_PATH)
vpath %.h $(INCLUDE_PATH)
vpath %.o $(OBJ_PATH)
vpath libhash.a $(HASH_LIB)

wave_preprocessor : wave_preprocessor.o preproc_utils.o libhash.a
	$(CC) -o $@ $(OBJ_PATH)wave_preprocessor.o $(OBJ_PATH)preproc_utils.o $(LINK_FLAGS)

libhash.a :
	(cd $(HASH_PATH); make)


wave_lex.o : wave_lex.c wave_yacc
	$(CC) $(COMPILE_FLAGS) $(IFLAGS) -c $< -o $@

wave_yacc : wave_yacc.o
	(cd $(YACCPATH); make)

wave_lex.c : wave_lex.l
	lex -o $(SRC_PATH)$@ $<

wave_preprocessor.c : wave_preprocessor.l
	lex -o $(SRC_PATH)$@ $<

%.c :

wave_preprocessor.o : wave_preprocessor.c | obj
	$(CC) $(COMPILE_FLAGS) $(IFLAGS) -c $(SRC_PATH)$< -o $(OBJ_PATH)$@

preproc_utils.o : preproc_utils.c preproc_utils.h | obj

%.o :
	$(CC) $(COMPILE_FLAGS) $(IFLAGS) -c $< -o $(OBJ_PATH)$@


obj :
	mkdir -p $(OBJ_PATH)

clean :
	@rm -rf $(OBJ_PATH) wave_preprocessor $(SRC_PATH)wave_preprocessor.c $(SRC_PATH)wave_lex.c 2>/dev/null; echo Directory cleaned.

clean-all : clean
	@(cd $(YACCPATH); make clean 1>/dev/null 2>&1; echo $(YACC_PATH) Cleaned.)
	@(cd $(HASH_PATH); make clean 1>/dev/null 2>&1; echo $(HASH_PATH) Cleaned.)
