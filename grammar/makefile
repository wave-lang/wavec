all : wave_yacc

wave_yacc : wave2.y
	yacc wave2.y -d -o wave_yacc.c

wave_yacc_debug : wave2.y
	yacc wave2.y -v

clean:
	rm wave_yacc.c wave_yacc.h y.output
