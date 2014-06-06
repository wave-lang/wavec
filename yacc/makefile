INCLUDE_PATH = include/
SRC_PATH = src/
OBJ_PATH = obj/

CC = gcc -std=gnu99
YACC = yacc

DEBUG_FLAGS = -g
WARNING_FLAGS = -Wall -Wextra -Wfloat-equal -Wdouble-promotion -Wswitch-default -Winit-self -Wshadow -Wbad-function-cast -Wcast-qual -Wcast-align -Wconversion -Wlogical-op -Wstrict-prototypes -Wnested-externs
COMPILE_FLAGS = $(WARNING_FLAGS) # $(DEBUG_FLAGS)

vpath %.c $(SRC_PATH)
vpath %.h $(INCLUDE_PATH)
vpath %.o $(OBJ_PATH)

wave_yacc : wave_yacc.o
	touch wave_yacc

wave_yacc.o : wave_yacc.c
	$(CC) $(COMPILE_FLAGS) -c $(SRC_PATH)$< -o $(OBJ_PATH)$@

wave_yacc.c : wave2.y
	$(YACC) -d -o wave_yacc.c $<
	mv wave_yacc.c $(SRC_PATH)
	mv wave_yacc.h $(INCLUDE_PATH)

%.o : | obj
	$(CC) $(COMPILE_FLAGS) -c $< -o $(OBJ_PATH)$@

obj :
	@mkdir -p $(OBJ_PATH)

src :
	@mkdir -p $(SRC_PATH);

clean :
	@(rm -rf $(OBJ_PATH) $(INCLUDE_PATH)wave_yacc.h $(SRC_PATH)wave_yacc.c wave_yacc)
