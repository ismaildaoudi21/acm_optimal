/* 	DAOUDI Ismail : 12007754
	KADDARI Issam :	12109741  
	groupe 2 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphe-4.h"
#include "acm_optimal.h"
#include "test-acm.h"
#include "test-acm_optimal.h"

int main() {
	/* pour tester le temps d'execution de chaque fonction*/
    clock_t start, end;
	graphe g; 
    graphe acm;


    start = clock();
	test_acm(g,acm);
	end = clock();
    printf("acm : %f\n", ((double) (end - start)) / CLOCKS_PER_SEC);


    start = clock();
	test_acm_optimal(g,acm);
	end = clock();
    printf("acm optimal : %f\n", ((double) (end - start)) / CLOCKS_PER_SEC);

	return EXIT_SUCCESS;
}