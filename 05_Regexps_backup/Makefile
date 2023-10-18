TRASH = esub *.txt *.out

all:	esub test

esub:	esub.c
	cc $^ -o $@

test:
	echo 'abcd1efg' | sed -E 's/[0-9]/#/' > s1.txt
	echo 'abcd1efg' | sed -E 's/([[:digit:]])/<\1>/' > s2.txt
	echo 'abcd1efg' | sed -E 's/([[:digit:]])(.*)/<\1><\2>/' > s3.txt
	./esub '[0-9]' '#' 'abcd1efg' > e1.txt
	./esub '([[:digit:]])' '<\1>' 'abcd1efg' > e2.txt
	./esub '([[:digit:]])(.*)' '<\1><\2>' 'abcd1efg' > e3.txt
	cmp s1.txt e1.txt > 1.txt || cat 1.txt
	cmp s2.txt e2.txt > 2.txt || cat 2.txt
	cmp s3.txt e3.txt > 3.txt || cat 3.txt

clean:
	rm -f $(TRASH)

