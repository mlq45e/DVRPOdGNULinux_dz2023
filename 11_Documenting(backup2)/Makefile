CC = cc
CFLAGS = -Wall -Wextra -std=c99 -g

EXEC = numMagician

all: $(EXEC) po/ru/$(EXEC).mo po/zh/$(EXEC).mo

$(EXEC): $(EXEC).c
	cc $(CFLAGS) -o $@ $<

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
	@rm -f $(EXEC) $(EXEC).o

.PHONY: clean
