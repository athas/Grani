# Grani - simple browser
# See LICENSE file for copyright and license details.

include config.mk

SRC = grani.c
OBJ = ${SRC:.c=.o}

all: options grani

options:
	@echo grani build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	@echo creating $@ from config.def.h
	@cp config.def.h $@

grani: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ grani.o ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f grani ${OBJ} grani-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p grani-${VERSION}
	@cp -R LICENSE Makefile config.mk config.def.h README \
		grani.1 ${SRC} grani-${VERSION}
	@tar -cf grani-${VERSION}.tar grani-${VERSION}
	@gzip grani-${VERSION}.tar
	@rm -rf grani-${VERSION}

install: all
	@echo installing executable files to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f grani ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/grani
	@cp -f grani-browse ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/grani-browse
	@cp -f grani-download ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/grani-download
	@cp -f grani-field ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/grani-field
	@cp -f grani-session ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/grani-session
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < grani.1 > ${DESTDIR}${MANPREFIX}/man1/grani.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/grani.1

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/grani
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/grani.1

.PHONY: all options clean dist install uninstall
