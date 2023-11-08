bin_PROGRAMS=numMagician
#~ AM_CFLAGS=-D'LOCALE_PATH="$(localedir)"'
pkgdata_DATA1=ru/LC_MESSAGES/nM.mo
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
