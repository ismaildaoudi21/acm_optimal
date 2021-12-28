#ifndef TAS_H
#define TAS_H


#include "graphe-4.h"



/**
 * \brief Noeud dans un tas binaire minimal
 *
 * Un noeud d'un tas binaire minimal est représenté par :
 * un /a sommet v ,
 * une /a valeur key (valeur de l'arc ou arête allant du sommet considéré à ce
 * noeud
 */

typedef struct MinHeapNode {
	int v; // le sommet
	int key; // son poids
} MinHeapNode;


/**
 * \brief un tas binaire minimal
 *
 * Un tas binaire minimal est représenté par :
 * un /a size (la la taille du tas),
 * une /a capacity (Capacité pour creer le tas, on va l'utiliser pour l'array), 
 * une /a pos (pour pouvoir accès à chaque noeud),
 * une /a array (l'array pour representer le tas)
 */
typedef struct MinHeap {
	int size; 
	int capacity;
	int* pos; 
	struct MinHeapNode** array; 
} MinHeap;

/** \brief crée en mémoire et initialise un noeud dont l'adresse est retournée
 * \param v sommet du noeud
 * \param key valeur associée
 * \return l'adresse du noeud construit (NULL en cas d'échec d'allocation mémoire).
 */
MinHeapNode* newMinHeapNode(int v, int key);


/** \brief crée en mémoire et initialise un tas dont l'adresse est retournée
 * \param capacity sommet du tas
 * \return l'adresse du tas construit (NULL en cas d'échec d'allocation mémoire).
 */
MinHeap *createMinHeap(int capacity);

/** \brief libere la memoire du tas
 * \param minheap un tas binaire minimal
 */
void destroyMinHeap(MinHeap* minHeap);


/** \brief échanger entre le noeud a et le noeud b dans le tas
 * \param a noeud du tas
 * \param b noeud du tas
 */
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b);

/** \brief entasser un tas à partir d'un indice donné 
 * \param minheap un tas binaire minimal
 * \param idx un indice representant un noeud dans le tas (array)
 */
void minHeapify(MinHeap* minHeap, int idx);


/** \brief vérifier si le tas est vide ou non
 * \param minheap un tas binaire minimal
 * \return 1 si le tas est vide, 0 sinon
 */
int isEmpty(MinHeap* minHeap);

/** \brief éxtraire le noeud de la valeur (key) minimum (la racine)
    puis entasser le tas et reduire la taille du tas.
 * \param minheap un tas binaire minimal
 * \return l'adresse du noeud extrait.
 */
MinHeapNode *extractMin(MinHeap* minHeap);


/** \brief decrementer la valeur d'un sommet v dans le tas
 * \param minheap un tas binaire minimal
 * \param v un sommet dans le tas
 * \param key la valeur du sommet v
 */
void decreaseKey(MinHeap* minHeap, int v, int key);


/** \brief verifier si un sommet est dans le tas minheap ou non
 * \param minheap un tas binaire minimal
 * \param v un sommet dans le tas
 * \return l si le sommet v est dans le tas minheap, 0 sinon
 */
int isInMinHeap(MinHeap* minHeap, int v);


#endif