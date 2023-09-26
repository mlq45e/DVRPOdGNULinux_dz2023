SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
GENERATES= $(OBJECTS) prog README
TRASH = *.o *~ o.* README prog prog-a prog-so liboutput_static.a liboutput.so
CC=cc
CFLAGS=-ggdb -o0 -fPIC

all:	README prog $(SOURCES) prog-a prog-so liboutput_static.a liboutput.so

%.o:	outlib.h

prog:	$(OBJECTS)

liboutput_static.a: fun.o const.o
	ar -cr $@ $^

prog-a:	prog.o liboutput_static.a
	cc $^ -o $@

liboutput.so: fun.o const.o
	cc -shared $^ -o $@

prog-so:	prog.o liboutput.so
	cc $^ -o $@

README:	prog
	./$< 2> $@

fun.o:	outlib.h

clean:
	rm -f $(TRASH)
	rm -f *.txt

distclean:	clean
	rm -rf $(GENERATES)
