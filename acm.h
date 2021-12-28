/**
 * \file acm.h
 * \brief Calcul et représentation d'arbres couvrant minimaux (en-tête)
 * \version 1
 * \date lundi 14 octobre 2019
 * \authors Pierre Rousselin, Antoine Rozenknop, Sophie Toulouse
 */

#ifndef ACM_H
#define ACM_H

#include "graphe-4.h"
#include "vlist.h"

/**
 * \brief Si le graphe contient une arête {v, w}, la fonction 
 *	affecte à la variable pointée par \a val la plus petite valeur d'une telle arête
 %	et renvoie 0. Sinon, la fonction renvoie -1
 */
int graphe_get_valeur_arete(graphe* g, int v, int w, double* val);

/**
 * \brief fonction qui renvoie le sommet de poids min qui n'est pas encore inclut dans mstSet
 * \param key[] la table de poids de chaque sommet
 * \param mstSet[] la table d'acm (mstSet[u] = 1 si le sommet u dans mstSet est 0 sinon)
 * \param n le nombre de sommet d'un graphe
 */

int minKey(int key[], int mstSet[], int n);


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
int graphe_acm(graphe *g, graphe *acm);

/**
 * \brief Écrit dans le fichier nommé \a nom_fichier une description au format
 * dot du graphe \a g avec son arbre couvrant minimal \a acm
 * \param g adresse de la variable graphe à lire
 * \param acm adresse de l'arbre couvrant minimal à lire
 * \return 0 si tout s'est bien passé, -1 en cas de problème d'entrée sortie
 *
 * Les arêtes de l'arbre couvrant minimal sont tracées en rouge. Celles qui
 * n'appartiennent pas à cet arbre couvrant sont tracées en noir.
 */
int graphe_ecrire_dot_avec_acm(graphe *g, graphe *acm, char *nom_fichier);

#endif /* ACM_H */
