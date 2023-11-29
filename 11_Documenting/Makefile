CC = cc
CFLAGS = -Wall -Wextra -std=c99 -g

EXEC = numMagician

all: $(EXEC) po/ru/$(EXEC).mo po/zh/$(EXEC).mo

$(EXEC): $(EXEC).c
	cc $(CFLAGS) -o $@ $< 2> cc2.txt
	doxygen Doxyfile.in 1> doxy_out.txt 2> doxy2.txt
	help2man --output=numMagician.1 --name='number magician program' ./$(EXEC)
#~ 	man2_MANS = doxygen/man/man2/numMagician.c.2 2> man2.txt

po/zh/$(EXEC).mo: po/zh/$(EXEC).po
	msgfmt --output-file=$@ $<
	cp $@ zh/LC_MESSAGES/
po/ru/$(EXEC).mo: po/ru/$(EXEC).po
	msgfmt --output-file=$@ $<
	cp $@ ru/LC_MESSAGES/
#~ po/zh/$(EXEC).po: po/$(EXEC).pot
#~     msgmerge --update $@ $<
#~ po/ru/$(EXEC).po: po/$(EXEC).pot
#~     msgmerge --update $@ $<
#~ po/$(EXEC).pot: $(EXEC).c
#~     xgettext -k_ -j -lC -c -s -o po/numMagician.pot numMagician.c

clean:
	@rm -f $(EXEC) $(EXEC).o doxy_out.txt doxy2.txt cc2.txt man2.txt numMagician.1
	@rm -rf doxygen

.PHONY: clean
