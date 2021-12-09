# AED, last modified abl 2020.10.21
#
# To compile progs:
#    make   OR  make sorwords  OR qsortwords
# To run tests:
#    make t     OR: make qt     OR (Valgrind):  make tv  ETC
#
# NOTE:
# In case of trouble with the shell for loop, GNU Make has 'foreach':
#	$(foreach file,$(FILES),./labconn $(file);)
# https://stackoverflow.com/questions/1490949/how-to-write-loop-in-a-makefile
#----------------------------------------------------------------------
#   Compiler, Compiler Flags

CC = gcc
CFLAGS = -g -Wall -ansi -pedantic

#   Sources
SOURCES = word.c sortwords.c

#   Objects  ('make' automatically compiles .c to .o)
OBJECTS = word.o sortwords.o
QOBJECTS = word.o qsortwords.o
QMOBJECTS = word.o qsortwordsmedian.o

sortwords: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

word.o: word.c word.h defs.h

sortwords.o: sortwords.c word.h defs.h

qsortwords: $(QOBJECTS)
	$(CC) $(CFLAGS) -o $@ $(QOBJECTS)

word.o: word.c word.h defs.h

qsortwords.o: qsortwords.c word.h defs.h

qsortmedian: $(QMOBJECTS)
	$(CC) $(CFLAGS) -o $@ $(QMOBJECTS)

word.o: word.c word.h defs.h

qsortwordsmedian.o: qsortwordsmedian.c word.h defs.h

clean:
	rm -f *.o  sortwords qsortwords qsortmedian


FILES = $(shell ls ../test/*.txt)

VALG = valgrind --leak-check=full -s

t:
	for F in ${FILES}; do  ./sortwords $${F} ; done;


tv:
	for F in ${FILES}; do ${VALG} ./sortwords $${F} ; done;


tt:
	for F in ${FILES}; do  time ./sortwords $${F} ; done;



qt:
	for F in ${FILES}; do  ./qsortwords $${F} ; done;


qtv:
	for F in ${FILES}; do ${VALG} ./qsortwords $${F} ; done;


qtt:
	for F in ${FILES}; do  time ./qsortwords $${F} ; done;


tm:
	for F in ${FILES}; do  ./qsortmedian $${F} ; done;


tmt:
	for F in ${FILES}; do ${VALG} ./qsortmedian $${F} ; done;


qtm:
	for F in ${FILES}; do  ./qsortmedian $${F} ; done;

