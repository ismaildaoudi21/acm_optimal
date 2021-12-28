PROG=	test_main

CC=gcc
CFLAGS=-Wall -Wfatal-errors -g -Wincompatible-pointer-types -Werror -pedantic

# __ exécutable
all: $(PROG)

acm_optimal: tas.o acm_optimal.o graphe-4.o vlist.o msuc.o
	$(CC) $^ -o $@

acm_optimal.o:	acm_optimal.c graphe-4.h tas.h
	$(CC) -c $(CFLAGS) $< -o $@	

test_main: test_main.o test-acm.o test-acm_optimal.o acm.o acm_optimal.o graphe-4.o vlist.o msuc.o tas.o
	$(CC) $^ -o $@

test_main.o: test_main.c graphe-4.h tas.h
	$(CC) -c $(CFLAGS) $< -o $@	

test-acm_optimal: test-acm_optimal.o acm_optimal.o graphe-4.o vlist.o msuc.o tas.o
	$(CC) $^ -o $@

test-acm_optimal.o:	test-acm_optimal.c graphe-4.h tas.h
	$(CC) -c $(CFLAGS) $< -o $@	

test-acm: test-acm.o acm.o graphe-4.o vlist.o msuc.o
	$(CC) $^ -o $@

test-acm.o:	test-acm.c graphe-4.h
	$(CC) -c $(CFLAGS) $< -o $@

tas.o:	tas.c tas.h
	$(CC) -c $(CFLAGS) $< -o $@

acm.o:	acm.c acm.h
	$(CC) -c $(CFLAGS) $< -o $@

graphe-4.o:	graphe-4.c graphe-4.h
	$(CC) -c $(CFLAGS) $< -o $@

vlist.o:	vlist.c vlist.h
	$(CC) -c $(CFLAGS) $< -o $@

msuc.o:	msuc.c msuc.h
	$(CC) -c $(CFLAGS) $< -o $@

# __ nettoyage
clean:
	@rm -f *.o
distclean: clean
	@rm -f $(PROG) *~

