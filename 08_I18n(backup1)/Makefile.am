bin_PROGRAMS=numMagician
TRASH = *.m4 *.log install-sh *.pot~ *.cache *.status * missing *.o *.po~ compile configure *.h *.in stamp-h1  depcomp numMagician zh
#~ pkgdata_DATA1=ru/LC_MESSAGES/nM.mo
pkgdata_DATA=zh/LC_MESSAGES/nM.mo

ru/LC_MESSAGES/nM.mo: ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

zh/LC_MESSAGES/nM.mo: zh.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

zh.po:	mes.pot
	msgmerge -U $@ $<

ru.po:	mes.pot
	msgmerge -U $@ $<

mes.pot:	nM.pot numMagician.c
	xgettext -k_ -c numMagician.c -o nM.new.pot
	cp nM.pot mes.pot
	msgmerge -U mes.pot nM.new.pot

trans:	mes.pot zh/LC_MESSAGES/nM.mo ru/LC_MESSAGES/nM.mo

clean:
	rm -rf $(TRASH)
