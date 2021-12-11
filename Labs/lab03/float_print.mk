EXERCISES	+= float_print
CLEAN_FILES	+= float_print float_print.o test_float_print.o
float_print: $(CFLAGS) float_print.c test_float_print.c
