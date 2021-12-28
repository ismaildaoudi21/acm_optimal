/**
 * \file graphe-4.c
 * \brief Représentation des graphes par liste de successeurs
 * \version 2 : maillons et listes de sommets externalisées (pour les parcours)
 * \date jeudi 7 novembre 2021
 * \authors Pierre Rousselin, Antoine Rozenknop, Sophie Toulouse
 
 * TP : partie 4
*/
#include "graphe-4.h"

#include <stdio.h>
#include <stdlib.h>

#define TRACE 0

/* __________________________________ Initialisation / Destruction */
int graphe_stable(graphe* g, int n, int est_or) {
	int stat =0;	/* tout se passe bien jusqu'à preuve du contraire */
	
	/* on vérifie que la valeur donnée pour n est correcte */
	if(n <= 0)
		stat =-2;
	else {
		/* allocation d'un tableau de n pointeurs tous initialisés à NULL */
		g->tab_sucs =calloc(n, sizeof(msuc*));
		if(! g->tab_sucs)
			stat =-1;
		else {
			/* initialisation des champs atomiques */
			g->n =n;
			g->est_or =est_or;
			g->m =0;
		}
	}

    /* on retourne le statut de réussite de la fonction */
    return stat;
}

void graphe_detruire(graphe *g) {
	int v;
	msuc *suiv, *m;
	
	if(g->tab_sucs) {
		/* __ parcours & destruction des listes d'adjacence */
		/* parcours des sommets du graphe */
		for(v =0 ; v < g->n ; v ++) {
			/* destruction 1 à 1 des maillons de la liste d'adjacence du sommet v */
			m =g->tab_sucs[v];
			while(m != NULL) {
				suiv =msuc_suivant(m);
				m =msuc_detruire(m);
				m =suiv;
			}
		}

		/* __ libération de la mémoire liée au tableau */
		free(g->tab_sucs);
	}
}

/* __________________________________ Ajout / Suppression d'arêtes */
/* Attention :
 * Si le graphe est orienté, utiliser les fonctions _arc
 * Si le graphe est non orienté, utiliser les fonction _arete
 */

int graphe_ajouter_arc(graphe *g, int v, int w, double val) {
	int stat =0;
	msuc *nv_vois;
	
	/* __ mise à jour de la liste d'adjacence */

	/* création & initialisation d'un nouveau maillon */
	nv_vois =msuc_construire(w, val);
	if(! nv_vois)
		stat =-1;
	else {
		/* son insertion (en tête) dans la liste */
		msuc_set_suivant(nv_vois, g->tab_sucs[v]);
		g->tab_sucs[v] =nv_vois;

		/* __ mise à jour du nombre d'arcs */
		(g->m)++;
	}

    /* on retourne le statut de réussite de la fonction */
	return stat;
}

int graphe_ajouter_arete(graphe* g, int v, int w, double val) {
	int stat;

	/* insertion de w dans la liste de voisins de v */
	stat =graphe_ajouter_arc(g, v, w, val);
	if(!stat && v != w) {
		/* insertion de v dans la liste de voisins de w */
		stat =graphe_ajouter_arc(g, w, v, val);
		if(!stat)
			/* en cas de succès, l'arête aura été comptée 2 fois par graphe_ajouter_arc */
			(g->m) --;
		else
			/* en cas d'échec, on revient à la situation initiale */
			graphe_supprimer_arc(g, w, v, val);
	}
	
    /* on retourne le statut de réussite de la fonction */
	return stat;
}

int graphe_supprimer_arc(graphe *g, int v, int w, double val) {
	int stat =-1;
	msuc *m =g->tab_sucs[v], *mprec =NULL, *msuiv;

	while(m != NULL) {
		/* mémorisation du successeur de m */
		msuiv =msuc_suivant(m);
		
		/* le cas échéant, on supprime l'arête */
		if (msuc_sommet(m) == w && msuc_valeur(m) == val) {
			stat =0;
			m =msuc_detruire(m);
			if(mprec)
				msuc_set_suivant(mprec, msuiv);
			else
				g->tab_sucs[v] =msuiv;
			(g->m) --;
		}
		/* sinon, on met simplement à jour du prédécesseur */
		else
			mprec =m;

		/* mise à jour de m */
		m =msuiv;
		
	}
	
    /* on retourne le statut de réussite de la fonction */
	return stat;
}

int graphe_supprimer_arete(graphe* g, int v, int w, double val) {
	int stat =graphe_supprimer_arc(g, v, w, val), m =g->m;
	if(!stat && v != w) {
		stat =graphe_supprimer_arc(g, w, v, val);
		if(! stat)	/* les 2 appels à graphe_supprimer_arc ont diminué g->m de 2 pour chaque arête supprimée */
			g->m =g->m +(m -g->m)/2;	
	}
	
    /* on retourne le statut de réussite de la fonction */
	return stat;
}

/* ______________________________________ Accesseurs en lecture */
int graphe_est_or(graphe *g) {
	return g->est_or;
}

int graphe_get_n(graphe* g) {
	return g->n;
}

int graphe_get_m(graphe* g) {
	return g->m;
}

msuc *graphe_get_prem_msuc(graphe *g, int v) {
	return g->tab_sucs[v];
}

/* NE PAS ACCÉDER DIRECTEMENT AUX CHAMPS EN-DESSOUS DE CETTE LIGNE */

/* Complexité : au plus, le plus grand degré (sortant : Delta_max) dans le graphe */
int graphe_get_multiplicite_arc(graphe* g, int v, int w) {
	int mult =0;
	msuc* m;
	for(m =graphe_get_prem_msuc(g, v) ; m != NULL ; m =msuc_suivant(m)) 
		if (msuc_sommet(m) == w)
			mult ++;
	
	return mult;
}

/* Complexité : au plus, le plus grand degré (Delta) dans le graphe */
int graphe_get_multiplicite_arete(graphe* g, int v, int w) {
	int mult =graphe_get_multiplicite_arc(g, v, w);

	if(v != w && graphe_est_or(g))
		mult =mult +graphe_get_multiplicite_arc(g, w, v);
	
	return mult;
}

/* Complexité : cas identique à celui de graphe_get_multiplicite_arc 
	attention, si cette fonction n'a pas vocation à être appelée sur les graphes non orientés, 
		elle est pour ces graphes utilisée comme sous-routine de graphe_get_degre */
int graphe_get_degre_sortant(graphe* g, int v) {
	int deg =0;
	msuc* m;
	for(m =graphe_get_prem_msuc(g, v) ; m != NULL ; m =msuc_suivant(m))
		if(msuc_sommet(m) == v && !graphe_est_or(g))
			deg =deg +2;	/* NB sinon dans graphe_get_degre on peut ajouter la multiplicité de la boucle sur v */
		else
			deg ++;
	
	return deg;
}

/* Complexité : la somme des degrés sortants, soit le nombre d'arêtes (m) du graphe */
int graphe_get_degre_entrant(graphe* g, int w) {
	int deg =0, v;
	for(v =0 ; v < graphe_get_n(g) ; v ++) 
		deg =deg +graphe_get_multiplicite_arc(g, v, w);
	
	return deg;
}

/* Complexité : 
	cas identique à celui de graphe_get_degre_sortant dans le cas non orienté
	cas identique à celui de graphe_get_degre_entrant (facteur dominant de m sur Delta_max) dans le cas orienté
*/
int graphe_get_degre(graphe *g, int v) {
	int deg =graphe_get_degre_sortant(g, v);
	if(graphe_est_or(g))
		deg =deg +graphe_get_degre_entrant(g, v);

    return deg;
}

/* ______________________________________ Entrées / Sorties */
void graphe_afficher(graphe* g) {
	int v, w;
	msuc *m;
	int n = graphe_get_n(g);
	printf("graphe %s d'ordre %d à %d aretes :\n",
		graphe_est_or(g) ? "orienté" : "non orienté",
		graphe_get_n(g), graphe_get_m(g));
	for (v = 0; v < n; ++v) {
		puts("successeurs de v : ");
		for (m = graphe_get_prem_msuc(g, v); m; m = msuc_suivant(m)) {
			w = msuc_sommet(m);
			printf("%2d, ", w);
		}
		puts("");
	}
}

int graphe_ecrire_dot(graphe *g, char *nom_fichier, int ecrire_valeurs) {
	int stat =-1;
	int u, v, n = graphe_get_n(g), est_or = graphe_est_or(g);
	msuc *m;
	double val;
	FILE *f;

	/* ouverture du fichier */
	f = fopen(nom_fichier, "w");
	if (!f)
		perror("fopen"); 
	else {
		stat =0;

		/* __ écriture du fichier */

		/* entête */
		if (est_or)
			fputs("digraph {\n", f);
		else
			fputs("graph {\n", f);

		/* sommets */
		for (u = 0; u < n; ++u)
			fprintf(f, "\t%d;\n", u);
		fputs("\n", f);

		/* arêtes (ou arcs) */
		for (u =0; u <n; ++u)
			for (m =graphe_get_prem_msuc(g, u); m; m =msuc_suivant(m)) {
				v =msuc_sommet(m);
				val =msuc_valeur(m);
				if (!est_or && v <u) /* arête déjà rencontrée */
					continue;
				fprintf(f, "\t%d -%c %d ", u, est_or ? '>' : '-', v);
				if (ecrire_valeurs)
					fprintf(f, " [label = %.2f]", val);
				fprintf(f, ";\n");
			}
		fputs("}\n", f);

		/* fermeture du fichier */
		fclose(f);
	}

    /* on retourne le statut de réussite de la fonction */
	return stat;
}

/* ______________________________________ Autres fonctions d'initialisation */
int graphe_complet(graphe* g, int n) {
	int stat =-1;
	int v, w;

	stat =graphe_stable(g, n, 0);
	if(! stat) {
		for (v =0 ; v <graphe_get_n(g) -1 && !stat ; ++v)
			for (w =v +1 ; w <graphe_get_n(g)  && !stat ; ++w)
				stat =graphe_ajouter_arete(g, v, w, 1.);
			
		if(stat)
			graphe_detruire(g);
	}

    /* on retourne le statut de réussite de la fonction */
	return stat;
}

int graphe_aleatoire(graphe* g, int n, double p, int est_or) {
	int v, w;
	if (n < 0)
		return -2;
	if (p < 0 || p > 1)
		return -3;
	if (graphe_stable(g, n, est_or) < 0)
		return -1;
	if (!est_or) {
		for (v = 0; v < graphe_get_n(g); ++v)
			for (w = v; w < graphe_get_n(g); ++w)
				if ((double) rand()/RAND_MAX < p)
					if (graphe_ajouter_arete(g, v, w, 0.) < 0) {
						graphe_detruire(g);
						return -1;
					}
	} 
	else {
		for (v = 0; v < graphe_get_n(g); ++v)
			for (w = 0; w < graphe_get_n(g); ++w)
				if ((double) rand()/RAND_MAX < p)
					if ( graphe_ajouter_arc(g, v, w, 0.) < 0) {
						graphe_detruire(g);
						return -1;
					}
	}
	return 0;
}

int graphe_aleatoire_multi(graphe* g, int n, double p, int est_or) {
	int v, w;
	if (n < 0)
		return -2;
	if (p < 0 || p >= 1)
		return -3;
	if (graphe_stable(g, n, est_or) < 0)
		return -1;
	if (!est_or) {
		for (v = 0; v < graphe_get_n(g); ++v)
			for (w = v; w < graphe_get_n(g); ++w)
				while ((double) rand()/RAND_MAX < p)
					if (graphe_ajouter_arete(g, v, w, 0.) < 0) {
						graphe_detruire(g);
						return -1;
					}
	} 
	else {
		for (v = 0; v < graphe_get_n(g); ++v)
			for (w = 0; w < graphe_get_n(g); ++w)
				while ((double) rand()/RAND_MAX < p)
					if (graphe_ajouter_arc(g, v, w, 0.) < 0) {
						graphe_detruire(g);
						return -1;
					}
	}
	return 0;
}


/*void bfs(graphe* g) {


	int n = graphe_get_n(g);
	vlist* q = vlist_construire();
	for (int k = 0; k < n; k++)
	{
		vlist_ajouter_fin(q, k, 0);
		
		//msuc *m1 = msuc_construire(k, 0);
		//msuc * m = graphe_get_prem_msuc(g,k);
		//printf("%d, %f\n", msuc_sommet(m1),msuc_valeur(m1));
		//printf("%d, %f\n", msuc_sommet(m),msuc_valeur(m));
	}

	//vlist* file = vlist_construire();
	while (vlist_get_card(q) > 0) {
			int currentVertex = vlist_get_sommet(q);
			msuc *m = graphe_get_prem_msuc(g,currentVertex);
			m->valeur = q->pm->valeur;
			while (m) {
				if (m->valeur != 1)
				{
					printf("%d", currentVertex);
				}
				int adjVertex = msuc_sommet(m);
				printf("%d : %d, %f\n", currentVertex, adjVertex, m->valeur);
				m = m->suivant;
			}
			vlist_supprimer_deb(q);
		}
}*/





/* ______________________________________ Autres fonctions de manipulation (application des parcours) */
int graphe_est_biparti(graphe* g) {
	int n = graphe_get_n(g);
	/* Creer un array pour voir si les sommets sont colorié ou non */
	double arr[n];
	for (int i = 0; i < n; i++) {
		/* mettre tous les sommets à la valeur -1 i.e: couleur grise*/
		arr[i] = -1.;
	}
	/* Initialisation d'une liste pour faire le parcours en largeur */
	vlist* q = vlist_construire();
	for (int k = 0; k < n; k++)
	{
		/* verifier si le sommet n'est pas encore colorié */
		if (arr[k] == -1.){
			/* enfiler le sommet et changer sa valeur dans l'array*/
			vlist_ajouter_fin(q, k, 0.);
			arr[k] = 0.;
			/* tant que la liste n'est pas vide*/
			while (vlist_get_card(q)>0) 
			{
				/* defiler le sommet */
				int currentVertex = vlist_get_sommet(q);
				msuc *m;
				m = q->pm;
				vlist_supprimer_deb(q);
				/*Garder la couleur du sommet parent et parcourir tous ses fils */
				double couleur = arr[currentVertex];
				for(m=graphe_get_prem_msuc(g, currentVertex); m;  m = msuc_suivant(m))
				{
					/* verifier si la couleur du sommet parent est égale à la couleur de son fils
						Si c'est vrai on renvoie faux le graphe n'est pas biparti*/
					if (arr[msuc_sommet(m)]  == couleur)
					{
						return 0;
					}
					
					/* Si le sommet n'est pas encore colorié */
					if (arr[msuc_sommet(m)] == -1.)
					{
						/* si la couleur du sommet parent est égale 0 alors on colorie son fils avec la couleur 1 */
						if (couleur == 0.)
						{
							arr[msuc_sommet(m)] = 1.;
						}
						/*sinon on fait l'inverse */
						else{
							arr[msuc_sommet(m)] = 0.;
						}
						m->valeur = arr[msuc_sommet(m)];
						/* Après on enfile le sommet fils à la liste q avec sa couleur */
						vlist_ajouter_fin(q, msuc_sommet(m), msuc_valeur(m));
					}
					
				}	
				
			}
		}
	}
	vlist_detruire(q);
	return 1;
}



/* stat : statut de réussite ou d'échec de la fonction */
/* stat : statut de réussite ou d'échec de la fonction */
int* graphe_est_sanscircuit(graphe* g, int* stat) {
	/* Parcours en profondeur et ordre topologique (inverse de N) */
	int * ordre = (int*)malloc((g->n)*sizeof(int));// ordre à retourner, inverse ordre de dépilement
	int * visit = (int*)calloc(g->n,sizeof(int)); // visité ou non, visité=1 et non visité=0, déjà dépilé=-1
	int v=0, val=1, i=1;
	msuc * w=NULL;
	vlist * M = vlist_construire(); // pile d'insertion
	vlist * L = vlist_construire(); // liste des sommets parcourus

	if (!M || !L)
	{
		*stat = -1;
	}

	visit[v]=1;   
	vlist_ajouter_deb(M, v, val); // Ajout premier sommet
	vlist_ajouter_fin(L, v, val);

	while(M->pm && vlist_get_card(L) <= g->n){ // Tant kon a pas tout parcouru

		v = msuc_sommet(M->pm);
		w=graphe_get_prem_msuc(g, v);

		if(w){ //  S'il a un successeur

			if(visit[msuc_sommet(w)]==0){
				visit[msuc_sommet(w)] = 1; // visité
				vlist_ajouter_deb(M, msuc_sommet(w), val);
				vlist_ajouter_fin(L, msuc_sommet(w), val);
			}
			// Si c'est dépilé, on regarde un autre successeur msuc_suivant(w)
			else if(visit[msuc_sommet(w)]==-1){
				if(msuc_suivant(w) != NULL && visit[msuc_sommet(w)]== 0){
					w = msuc_suivant(w);
					visit[msuc_sommet(w)] = 1; // visité
					vlist_ajouter_deb(M, msuc_sommet(w), val);
					vlist_ajouter_fin(L, msuc_sommet(w), val);
				}
				else{
					vlist_supprimer_deb(M); // dépiler
					ordre[v] = (g->n)-i;
					i++;
					printf("depile %d\n", v);
					//printf("%d\n", i);
					visit[v] = -1;
				} 
			}  

			else if(visit[msuc_sommet(w)]==1){
				return NULL; // Si y'a un circuit
			}

		}
		// Si w n'a plus de successeur
		else { // (!w)
			vlist_supprimer_deb(M); // dépiler
			ordre[v] = (g->n)-i;
			printf("depile %d\n", v);
			i++;
			//printf("%d\n", i);
			visit[v] = -1;
		}

		if(!M->pm && vlist_get_card(L) < g->n){ // Si L est vide et kon a pas parcouru tous les sommets(g non connexe)
			for(int j = 0; j< g->n; j++){
				if(visit[j] == 0){ // premier non visité kon rencontre
					vlist_ajouter_deb(M, j, val);
					vlist_ajouter_fin(L, j, val);
					visit[j] = 1; // visité
					break;
				} 
			} 
		}
	}
	 
	*stat = 0;
	return ordre;
}