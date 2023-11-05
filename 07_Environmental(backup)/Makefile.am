TRASH = rhasher *.txt compile *.log install-sh *.in stamp-h1 *.m4 *.h *.status depcomp Makefile *.cache configure missing *.o .deps

#~ CFLAGS = -o rhasher rhasher.o  -lrhash -lreadline -lncurses


bin_PROGRAMS=rhasher

rhasher_SOURCES=rhasher.c

test:
	echo "md5" "asdfghjkl" | ./rhasher 1> 1.txt 2> err1.txt
	echo "asdfghjkl" | md5sum 1> 2.txt 2> err2.txt
	echo "SHA1" "asdfghjkl" | ./rhasher 1> 11.txt 2> err11.txt
	echo "asdfghjkl" | sha1sum 1> 22.txt 2> err22.txt

clean:
	rm -rf $(TRASH)
