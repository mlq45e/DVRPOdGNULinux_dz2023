bin_PROGRAMS = labyrint_mlq  
labyrint_mlq_SOURCES = labyrint_mlq.c

install:
	mkdir -p $(DESTDIR)/$(bindir)
	cp ./labyrint_mlq $(DESTDIR)/$(bindir)
	echo "LD_LIBRARY_PATH=$(DESTDIR)/usr/lib $(DESTDIR)/$(bindir)/labyrint_mlq" > $(DESTDIR)/$(bindir)/Labyrint_Mlq
	chmod +x $(DESTDIR)/$(bindir)/Labyrint_Mlq

demo:
	./labyrint_mlq 42 ' .' 11
