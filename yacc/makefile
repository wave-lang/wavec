################################################################################
# Programs
################################################################################
CC = gcc -std=gnu99
YACC = yacc

################################################################################
# Paths
################################################################################
PATH_SRC = src
PATH_OBJ = obj
PATH_INCLUDE = include

PATH_WAVE_COMPILER = ..
PATH_WAVE_COMPILER_INCLUDE = $(PATH_WAVE_COMPILER)/include

################################################################################
# Flags
################################################################################

FLAGS_CC_INCLUDE = -I$(PATH_INCLUDE) -I$(PATH_WAVE_COMPILER_INCLUDE)
FLAGS_CC_DEBUG = -g
FLAGS_CC_WARNING = -Wall -Wextra -Wfloat-equal -Wdouble-promotion \
	-Wswitch-default -Winit-self -Wshadow -Wbad-function-cast -Wcast-qual \
	-Wcast-align -Wconversion -Wlogical-op -Wstrict-prototypes -Wnested-externs
FLAGS_CC = $(FLAGS_CC_INCLUDE) $(FLAGS_CC_WARNING) # $(FLAGS_CC_DEBUG)

################################################################################
# Files
################################################################################
vpath %.c $(PATH_SRC)
vpath %.h $(PATH_INCLUDE)
vpath %.o $(PATH_OBJ)
vpath %.a ../lib

################################################################################
# Compiling
################################################################################
wave_yacc : wave_yacc.o libwavecompiler.a
	touch wave_yacc

libwavecompiler.a:
	(cd ..; make)

wave_yacc.o : wave_yacc.c
	$(CC) $(FLAGS_CC) -c $(PATH_SRC)/wave_yacc.c -o $(PATH_OBJ)/wave_yacc.o

wave_yacc.c : wave.y
	$(YACC) -d -o wave_yacc.c $<
	mv wave_yacc.c $(PATH_SRC)/
	mv wave_yacc.h $(PATH_INCLUDE)/

%.o : | obj
	$(CC) $(FLAGS_CC) -c $< -o $(PATH_OBJ)$@

################################################################################
# Directories
################################################################################
obj :
	@mkdir -p $(PATH_OBJ)

src :
	@mkdir -p $(PATH_SRC)

################################################################################
# Cleaning
################################################################################
clean :
		(cd ..; make clean)
		@(rm -rf $(PATH_OBJ) $(PATH_INCLUDE)/wave_yacc.h $(PATH_SRC)/wave_yacc.c wave_yacc)
