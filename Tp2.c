#include "Outil.h"
#include "Graphe.h"
#include "Tp2.h"
int bTp2AmorceR;//ie le module a effectivement été amorcé
int bTp2OuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un Tp3 est actuellement alloué
#define kuSommetMax 100

void Tp2AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp2AmorceR=kV;
	bTp2OuverT=kF;
}//Tp2AMORCER

void Tp2INITIALISER(){//O(?)
	//relance le présent module
	Assert2("Tp2INITIALISER",bTp2AmorceR,!bTp2OuverT);
}//Tp2INITIALISER

void GrapheAllouerInitialiseR2(int nGraphe ,graf **ppgSimple){
	//alloue et décrit dans ppgSimple le graphe de rang1 nGraphe
	//pour simplifier la saisie,les sommets vont de A à Z puis de a à z et les données sont supposées être des entiers dans [0..9] 
    char ksGros[]="AB1AD1AE2BC3BG2CJ2CK1DM1DN2EF2EQ1FG2FR1GS1HI2HT1IJ1IV1JX3KY2LM2LZ1Ma1NO1Nb3OP2Oc3Pe1Qe2Qf2Rf2Rg2ST2Sg2TU2UV1Uh3VW2WX1Yj1Zj2ab2ak3bm1cd1cm2de2dn2fn1go1hi2ip1kl1lm2ln2op2Aq5Br5Cs5Dt5";
	char kcMoyen[]="AB2AH1BC1BK2CD2DE1DM2EF2FG1FO2GH2HI2IJ2IP1JK1JQ2KL2LM1LS2MN2NO1NU2OP2PU2QR5RU1ST5TU1AV2CW2EX2GY2";
	char ksPetit[]="AE2BE3EF1FC2FD3GA8GB8CH9DH9";
	char *sGrapheType="ksPetit,kcMoyen,ksGros";
	Appel0("GrapheAllouerInitialiseR");
		switch(nGraphe){//NB ci-dessous,GrapheGenerer alloue puis initialise ppgSimple
			case 1:	GrapheGenerer(ksPetit,ppgSimple);
					break;
			case 2:	GrapheGenerer(kcMoyen,ppgSimple);
					break;
			case 3:	GrapheGenerer(ksGros,ppgSimple);
					break;
			default: Assert1("GrapheAllouerInitialiseR default",0);
		}//switch
		GrapheVoir0(*ppgSimple,sC2b("Graphe",sG(sItem(sGrapheType,nGraphe))),grCouleur);
		Assert1("GrapheAllouerInitialiseR",bGrapheSimple(*ppgSimple));
	Appel1("GrapheAllouerInitialiseR");
}//GrapheAllouerInitialiseR


void DistancierAvecFloyd(graf *pgG, int nDist[][1 + kuSommetMax], int *pnComplexiteh){
	int i, j, k; // Les entiers pour les boucles
	int aK,sX,sY;//a comme arc;s comme sommet
	int complexite = 0;
	int uL,uC;//u comme entier supérieur ou égal à un;L=ligne,C=colonne.
	int nSommet=pgG->nSommetEnTout;
	int dM[1+nSommet][1+nSommet];//matrice des distances sur les arcs,supposées être des entiers ou des réels déjà ramenés à des entiers
	Assert1("DistancierCalculeR",bGrapheSimple(pgG));
	//générer la matrice d'incidence sommet-sommet dM qui décrit le graphe simple pgSimple
		//dM:=0
	//int nDist[nSommet][nSommet];  // Matrice D des plus courtes distances, déja passé en paramètres

	for(i = 1; i <= nSommet ; i++){
		for(j = 1; j <= nSommet ; j++){
			if(i == j){
				nDist[i][j] = 0; // 0 sur la diagonale
			}else{
				nDist[i][j] = 1048575; // 1048575 partout, équivaut a l'infini
			}
		}
	}
	for (uL=1;uL<=nSommet;uL++){
		for (uC=1;uC<=nSommet;uC++){
			dM[uL][uC]=0;
		}
	}
	for (sX=1;sX<=nSommet;sX++){
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
			sY=pgG->sSuk[aK];
			dM[sX][sY]=pgG->coulh[aK];//distance (sX,sY), si dM existe, il y a un successeur

			if((dM[sX][sY] != 0) && (sX != sY) ){	//exécuter l'algorithme de Floyd sur dM
				nDist[sX][sY] = pgG->coulh[aK];
			}
		}
	}

	for(k = 1; k <= nSommet; k++){
		for(i = 1; i <= nSommet; i++){
			for(j = 1; j <= nSommet; j++){
				complexite++;
				if(nDist[i][j] > nDist[i][k] + nDist[k][j]){
					nDist[i][j] = nDist[i][k] + nDist[k][j];
				}
			}
		}
	}
	*pnComplexiteh = complexite;
}

void DistancierAvecDijkstra(graf *pgG, int sSource, int nDyst[1 + kuSommetMax], int *pnComplexiteh){
	//calculer le distancier de pgG supposé peu dense (algo de Dijkstra avec tas)
	int complexite;
	int j;
	int nSommet=pgG->nSommetEnTout;

	VecteurCopier(pgG->coulh,1,pgG->nArcEnTout,pgG->nCout);

	for(j = 1; j <= nSommet; j++){
		complexite++;
		nDyst[j] = nGrapheCheminerTaS(pgG, sSource, j, &complexite); // Modification de nGrapeCheminerTas selon l'énoncé
	}

	*pnComplexiteh += complexite;
}

int nDistancierCalculer(graf *pgG, int nSommet, int bFloydSinonDijkstra, int bAfficher){
	int nDyst[1 + kuSommetMax];
	int nDist[1 + kuSommetMax][1 + kuSommetMax];
	int complexite, i,j;

	if(bFloydSinonDijkstra){
		for(i = 1; i <= nSommet; i++){
			DistancierAvecDijkstra(pgG, i, nDyst, &complexite);
			if(bAfficher){
				for(j = 1; j <= nSommet ; j++){
					printf("%10i", nDyst[j]);
				}	
			}
			printf("\n");
		}
	
	}else{
		DistancierAvecFloyd(pgG, nDist, &complexite);
		if(bAfficher){
			for(i = 1; i <= nSommet ; i++){
				for(j = 1; j <= nSommet ; j++){
					printf("%10i", nDist[i][j]);
				}
				printf("\n\n");
			}
		}
	}

	printf("\n Complexite de : %i \n",complexite);
} 


void Tp2TESTER(int iTest){
	//teste le présent module
	graf *pgG;
	int complexite, choix, nombreDeSommet = 8;
	int *nDist;
	Appel0(sC2("Tp2TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
		case 1: //calcul de la densité d'un graphe simple aléatoire
			GrapheCreer(8,&pgG); // Creation du graphe
			GrapheAllouerInitialiseR2(1,&pgG);
			DistancierAvecFloyd(pgG, nDist, &complexite);
			printf("\n Complexite de : %i \n",complexite);
			break;
		case 2:
			GrapheCreer(8,&pgG); // Creation du graphe
			GrapheAllouerInitialiseR2(1,&pgG);
			GrapheVoir(pgG, "ee");
			DistancierAvecDijkstra(pgG, 1, nDist, &complexite);
			printf("\n Complexite de : %i \n",complexite);
			break;
		case 3:
			GrapheCreer(nombreDeSommet,&pgG); // Creation du graphe
			GrapheAllouerInitialiseR2(1,&pgG);
			GrapheVoir(pgG, "ee");
			printf("Distancier avec Dijkstra ou floyd? Taper 1 pour Dijkstra, 0 pour floyd \n");
			scanf("%i",&choix);
			nDistancierCalculer(pgG, nombreDeSommet, choix, 1);
			break;
		default: ;
	}
	Appel1(sC2("Tp2TESTER,test n°",sEnt(iTest)));
}//Tp2TESTER	
