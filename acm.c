/* 	DAOUDI Ismail : 12007754
	KADDARI Issam :	12109741  
	groupe 2 */

/**
 * \file acm.h
 * \brief Calcul et représentation d'arbres couvrant minimaux (implémentation)
 * \version 2
 * \date lundi 22 novembre 2021
 * \authors Pierre Rousselin, Antoine Rozenknop, Sophie Toulouse
 */
#include "acm.h"

#include <stdlib.h>
#include <stdio.h>
#include <float.h>


// fonction qui renvoie le sommet de poids min qui n'est pas encore inclut dans mstSet
// complexité O(n)
int minKey(int key[], int mstSet[], int n)
{
    int min = 1000, min_index;
    for (int v = 0; v < n; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
 
    return min_index;
}

/*********************************************/
/*  fonctions à écrire						 */
/*********************************************/

// la fonction principale Prim-Dijkstra 
// Nombre total d’opérations élémentaires : O(n) + O(n^2) + O(m) + O(n)
// complexité: O(n^2)) ou n represente le nombre de sommets et m le nombre d'aretes
int graphe_acm(graphe *g, graphe *acm) {
	int n = graphe_get_n(g);
	graphe_stable(acm,n, 0);
	int S[n]; /* ensemble d'acm */
	int P[n]; /* ensemble des parents*/
	int val[n]; /* le poids de chaque sommets */
	int cout = 0; /* le cout de l'arbre */

	for (int i = 0; i < n; i++) /* 3*n = O(n) */
	{
		S[i] = 0; /*0 => sommet i n'est dans l'ensemble acm et 1 sinon */
		P[i] = -1; /* initialisation de tableau parent */
		val[i] = 1000; /* 1000 represente l'infini */
	}

	msuc *m;
	double poids;
	
	val[0] = 0;
	P[0] = -1;
	for (int k = 0; k < n; k++) /* n*n = O(n^2)  itérations*/ 
	{	
			int v =  minKey(val, S, n); //n iterations
			S[v] = 1;
			for(m=graphe_get_prem_msuc(g,v); m; m = msuc_suivant(m)) /* O(m); m itérations visiter tous ses voisins */
			{
				int w = msuc_sommet(m); /* w est le voisin de v*/

				graphe_get_valeur_arete(g, v, w, &poids); /*prendre la valeur de l'arete et la mêtre dans poids*/

				/* Si le poids de w est égale à l'infini ou son poids est supérieur 
				au nouveau poids et qu'il n'est pas encore dans S */
				if ((val[w] == -1 || val[w] > poids) && S[w] == 0) 
				{
					P[w] = v; /* le parent de w est v */
					val[w] = poids; /* on mets à jour le poids de w */
				}
			}	
	}

	/* Pour ajouter les aretes dans acm */

	for(int w=1; w < n; w++) // O(n)
	{	
		graphe_ajouter_arete(acm, P[w], w, val[w]);
		cout += val[w];
	}
	//printf("cout de l'arbre : %d\n", cout);

	return 0;
}

int graphe_get_valeur_arete(graphe* g, int v, int w, double* val) {
	int statut =-1;
	msuc* m;
	for(m =graphe_get_prem_msuc(g, v) ; m != NULL ; m =msuc_suivant(m))
		if (msuc_sommet(m) == w) {
			if (statut == -1) {
				statut =0;
				*val =msuc_valeur(m);
			}
			else if (msuc_valeur(m) < *val)
				*val =msuc_valeur(m);
		}
	
	return statut;
}

int graphe_ecrire_dot_avec_acm(graphe *g, graphe *acm, char *nom_fichier) {
	int u, v;
	double val;
	FILE *f = fopen(nom_fichier, "w");
	if (!f) { perror("fopen"); return -1; }
	fputs("graph {\n", f);
	for (u = 0; u < graphe_get_n(g); ++u)
		fprintf(f, "\t%d;\n", u);
	fputs("\n", f);
	fputs("\tsubgraph g {\n", f);
	for (u = 0; u < graphe_get_n(g); ++u)
		for (v = u; v < graphe_get_n(g); ++v)
			if (graphe_get_valeur_arete(g, u, v, &val) == 0 && (u ==v || !graphe_get_multiplicite_arete(acm, u, v)) )
				fprintf(f, "\t\t%d -- %d [label = %.2f];\n", u, v, val);
	fputs("\t}\n", f);
	fputs("\tsubgraph acm {\n\t\tedge [color = red]\n", f);
	for (u = 0; u < graphe_get_n(acm); ++u)
		for (v = u; v < graphe_get_n(acm); ++v)
			if (graphe_get_valeur_arete(acm, u, v, &val) == 0)
				fprintf(f, "\t\t %d -- %d [fontcolor = red, label = %.2f];\n", u, v, val);
	fputs("\t}\n}\n", f);
	fclose(f);
	return 0;
}