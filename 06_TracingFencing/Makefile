#~ need make -i !!!
TRASH = move *.so *.txt

all:	pre_remove move test

move:	move.c
	cc $^ -o $@

pre_remove:	pre_remove.c
	cc -fPIC -o $@ $^

test:	move
	cat move.c > 1.txt
	strace -o straceInfo1.txt -e fault=open:error=ENOENT ./move 1.txt 2.txt 2> err1.txt
	cat move.c > 1.txt
	strace -o straceInfo2.txt -e fault=open:error=EPERM ./move 1.txt 3.txt 2> err2.txt
	cat move.c > 1.txt
	strace -o straceInfo3.txt -e fault=read:error=ENOMEM ./move 1.txt 4.txt 2> err3.txt
	cat move.c > 1.txt
	strace -o straceInfo4.txt -e fault=write:error=ENETDOWN ./move 1.txt 5.txt 2> err4.txt
	cat move.c > 1.txt
	strace -o straceInfo5.txt -e fault=fstat:error=EOWNERDEAD ./move 1.txt 6.txt 2> err5.txt
	cat move.c > 1.txt
	strace -o straceInfo6.txt -e fault=all:error=EL3RST ./move 1.txt 7.txt 2> err6.txt
	cat move.c > 1_PROTECT.txt
	LD_PRELOAD=/home/menglq/wen2jian4/programming/gitRepo/DVRPOdGNULinux_dz2023/06_TracingFencing/pre_remove.so ./move 1_PROTECT.txt 8.txt
	chmod +x preremovetest.sh
	./preremovetest.sh

clean:
	rm -f $(TRASH)

