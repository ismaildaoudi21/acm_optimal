#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphe-4.h"
#include "acm.h"

/**
 * \brief fonction de test pour acm 
 * \param g adresse de la variable graphe à lire
 * \param acm adresse de l'arbre couvrant minimal à écrire
 * \return 0 si tout s'est bien passé, -1 en cas de problème d'allocation
 * mémoire
 *
 * On suppose que g est connexe.
 * De la mémoire est allouée pour \a acm. Il faut la libérer avec la
 * fonction \a graphe_detruire.
 */
int test_acm(graphe g, graphe acm);
