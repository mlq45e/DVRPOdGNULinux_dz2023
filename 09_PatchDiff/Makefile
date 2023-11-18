TRASH = labyrinth l1* l2* l3* labyrint_s.c

all: labyrinth patch run

labyrinth: labyrint.c
	cc $^ -o $@

patch: labyrint.c l_size.patch l_symb.patch l_seed.patch
	@cp $< l1.c
	@patch l1.c < l_size.patch
	cc l1.c -o l1
	@cp $< l2.c
	@patch l2.c < l_symb.patch
	cc l2.c -o l2
	@cp $< l3.c
	@patch l3.c < l_seed.patch
	cc l3.c -o l3

run: labyrinth l1 l2 l3
	./$<
	./l1 11
	./l2 +# 7
	./l3 42 ' .' 8

clean:
	rm -f $(TRASH)
