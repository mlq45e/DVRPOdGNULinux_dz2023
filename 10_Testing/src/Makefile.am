.POSIX:
CFLAGS = -std=c99 -Wall -Wextra
if COND_GCOV
CFLAGS  += -O0 -g -fprofile-arcs -ftest-coverage
else
CFLAGS  += -O3 -g3
endif

lib_LTLIBRARIES = libbuf.la
bin_PROGRAMS = buf

namegen_LDADD = libbuf.la

tests: tests.c buf.h
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ tests.c $(LDLIBS)

test: check
check: tests
	./tests

gcov:
	gcov -o .libs libbuf -t -k -b | egrep -v '[[:digit:]]:[ /][*]'

clean:
	rm -f tests

