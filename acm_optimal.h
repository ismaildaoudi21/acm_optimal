

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>


/** \brief representer graphiquement le graphe d'acm
 * \param acm le graphe d'acm
 * \param arr[] la table d'acm (parent)
 * \param key[] la table de poids minimum de chaque sommet vers son voisin
 * \param n le nombre de sommet du graphe acm
 */
void tracer_arbre(graphe* acm, int arr[],int key[], int n);

/**
 * \brief Calcule un arbre couvrant minimal de g
 * \param g adresse de la variable graphe à lire
 * \param acm adresse de l'arbre couvrant minimal à écrire
 * \return 0 si tout s'est bien passé, -1 en cas de problème d'allocation
 * mémoire
 *
 * On suppose que g est connexe.
 * De la mémoire est allouée pour \a acm. Il faut la libérer avec la
 * fonction \a graphe_detruire.
 */
int graphe_acm_optimal(graphe* graph, graphe* acm);


