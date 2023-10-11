TRASH = range *.txt

all:	etalon range test

range:	range.c
	cc -o0 -g $^ -o $@

test:	2.gdbinit
	gdb --command=1.gdbinit range | grep '@@@' > 1.txt
	gdb --command=2.gdbinit range | grep '@@@' > 2.txt
	cmp 1.txt 01.txt > 101.txt || cat 101.txt
	cmp 2.txt 02.txt > 202.txt || cat 202.txt

etalon:
	printf '@@@$$1 = 5\n@@@$$2 = 10' > 01.txt
	printf '@@@$$1 = -16\n@@@$$2 = -13\n@@@$$3 = -10\n@@@$$4 = -7\n@@@$$5 = -4\n@@@$$6 = -1\n@@@$$7 = 2\n@@@$$8 = 5' > 02.txt

clean:
	rm -f $(TRASH)

