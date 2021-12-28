/* 	DAOUDI Ismail : 12007754
	KADDARI Issam :	12109741  
	groupe 2 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "tas.h"

#include "acm_optimal.h"


//representer l'acm dans le graphe 
// complexité : O(n) ou n represente le nombre de sommets
void tracer_arbre(graphe*acm, int arr[], int key[], int n)
{
	for (int i = 1; i < n; ++i){
        graphe_ajouter_arete(acm, arr[i], i, key[i]);
    }  
}

// la fonction principale Prim-Dijkstra 
// Nombre total d’opérations élémentaires : O(n) + O(n*log(n)) + O(m*log(n)) + O(n) = O((n+m)*log(n))
// complexité: O((n+m)*log(n)) ou n represente le nombre de sommets et m le nombre d'aretes
int graphe_acm_optimal(graphe* graph, graphe* acm)
{
	int V = graphe_get_n(graph); 
    graphe_stable(acm, V, 0);
	int parent[V]; /* ensemble des parents*/
	int key[V]; /* le poids de chaque sommets */

	/* initialisation d'un tas */
	MinHeap* minHeap = createMinHeap(V);

	/* initialisation des tableaux 
	 * Complexité : O(n)*/
	for (int v = 1; v < V; ++v) {
		parent[v] = -1;
		key[v] = INT_MAX;
		minHeap->array[v] = newMinHeapNode(v, key[v]);
		minHeap->pos[v] = v;
	}

	key[0] = 0;
	minHeap->array[0] = newMinHeapNode(0, key[0]);
	minHeap->pos[0] = 0;
	minHeap->size = V;

	/* Tant que le tas n'est pas vide */
	//complexité : O(n * log(n)) 
	while (!isEmpty(minHeap)) {

		// extraire la valuer min du tas
		// Complexité : O(log n)
		MinHeapNode* minHeapNode = extractMin(minHeap);
		int u = minHeapNode->v; 

		/*liberer la memoire du noeud extrait*/
		free(minHeapNode);

		/*visiter tous les voisins de u*/
		msuc* m = graph->tab_sucs[u];

		/*visiter tous les voisins de u*/
		// complexité : O(m * log(n)) 
		while (m!= NULL) {
			int v = msuc_sommet(m);

			/* si v est encore dans le tas et son poids est inférieur à son poids precedent on le mis à jour */
			if (isInMinHeap(minHeap, v) && msuc_valeur(m) < key[v]) {
				key[v] = msuc_valeur(m);
				parent[v] = u;
				decreaseKey(minHeap, v, key[v]); // complexité : O(log(n))
			}
			m = msuc_suivant(m);
		}
	}


    /*liberer la memoire prise par le tas */
	// complexité : O(1)
    destroyMinHeap(minHeap);
	
	//tracer les arbres d'acm
	// complexité : O(n)
	tracer_arbre(acm, parent,key, V);

    return 0;
}


