#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphe-4.h"
#include "acm_optimal.h"
#include "acm.h"


int test_acm_optimal(graphe  g, graphe acm) {
    int statut;
	
	/* initialisation d'un graphe test */


	graphe_stable(&g, 7, 0);
	graphe_ajouter_arete(&g, 0, 1, 7.);
	graphe_ajouter_arete(&g, 0, 3, 5.);
	graphe_ajouter_arete(&g, 1, 3, 9.);
	graphe_ajouter_arete(&g, 1, 2, 8.);
	graphe_ajouter_arete(&g, 1, 4, 7.);
	graphe_ajouter_arete(&g, 2, 4, 5.);
	graphe_ajouter_arete(&g, 3, 4, 15.);
	graphe_ajouter_arete(&g, 3, 5, 6.);
	graphe_ajouter_arete(&g, 4, 5, 8.);
	graphe_ajouter_arete(&g, 4, 6, 9.);
	graphe_ajouter_arete(&g, 5, 6, 11.);



	//Exemple cours:

	/*graphe_stable(&g, 8, 0);
	graphe_ajouter_arete(&g, 0, 1, 1.);
	graphe_ajouter_arete(&g, 0, 7, 3.);
	graphe_ajouter_arete(&g, 0, 6, 11.);
	graphe_ajouter_arete(&g, 0, 5, 5.);
	graphe_ajouter_arete(&g, 1, 2, 6.);
	graphe_ajouter_arete(&g, 1, 5, 6.);
	graphe_ajouter_arete(&g, 1, 4, 5.);
	graphe_ajouter_arete(&g, 1, 3, 3.);
	graphe_ajouter_arete(&g, 2, 3, 6.);
	graphe_ajouter_arete(&g, 2, 4, 7.);
	graphe_ajouter_arete(&g, 3, 4, 9.);
	graphe_ajouter_arete(&g, 4, 5, 2.);
	graphe_ajouter_arete(&g, 5, 6, 4.);
	graphe_ajouter_arete(&g, 6, 7, 8.);*/
	


	/* partie acm */
	statut = graphe_acm_optimal(&g, &acm);

	if (statut == 0) {
		graphe_ecrire_dot_avec_acm(&g, &acm, "acm.dot");
		system("dot -Tx11 acm.dot");
		
		graphe_detruire(&acm);
	}
	/* sortie (mais seulement après avoir fait le ménage) */
	graphe_detruire(&g);
	return EXIT_SUCCESS;
}
