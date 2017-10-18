#include "Outil.h"
#include "Graphe.h"
#include "Tp3.h"
int bTp3AmorceR;//ie le module a effectivement été amorcé
int bTp3OuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un Tp3 est actuellement alloué

void GrapheAllouerInitialiseR3(int nGraphe ,graf **ppgSimple){
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

void TP3Facturer(int sOrigine, int sDestination, int nLongueur, int nLargueur, int nHauteur){
	int nComplexiteh;
	graf *pgG;
	GrapheCreer(8,&pgG);
	GrapheAllouerInitialiseR3(1,&pgG);
	char gHauteur[] ="AE2BE3EF1FC2FD3GA8GB8CH9DH9" , gLargueur[] ="AE2BE3EF1FC2FD3GA8GB8CH9DH9", gLongueur[] ="AE2BE3EF1FC2FD3GA8GB8CH9DH9";;
	int coutTotal = 0;

	VecteurCopier(pgG->coulh,1,pgG->nArcEnTout,pgG->nCout);

	VecteurVoir1("Les vecteurs : ",pgG->nCout,1,pgG->nArcEnTout);

	int nArcs = pgG->nArcEnTout;

	for(int uArc = 1; uArc <= nArcs; uArc++){ //tout les sommets de notre graphe
		if(gHauteur[3*uArc-1]-'0' < nHauteur || gLargueur[3*uArc-1]-'0' < nLargueur || gLongueur[3*uArc-1]-'0' < nLongueur){ // hauteur ou largueur ou longueur passe pas
			pgG->nCout[uArc] = 99;
			printf("Un arc qui ne passe pas");
		}else{
			pgG->nCout[uArc] = pgG->coulh;
		}
	}

	coutTotal = nGrapheCheminerTaS(pgG, sOrigine, sDestination, &nComplexiteh);

	coutTotal > 99 ? printf("On ne peut pas passer") : printf("On peut passer, le cout total est de : %i",coutTotal);
	
}

void TP3Router(int nHeure, int nMinute, int nSeconde, int sOrigine, int sDestination, int nlongueur, int nLargueur, int nHauteur){

}

void Tp3AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp3AmorceR=kV;
	bTp3OuverT=kF;
}//Tp3AMORCER

void Tp3INITIALISER(){//O(?)
	//relance le présent module
	Assert2("Tp3INITIALISER",bTp3AmorceR,!bTp3OuverT);
}//Tp3INITIALISER

void Tp3TESTER(int iTest){
	//teste le présent module
	int sOrigine = 1;
	int sDestination = 1;
	int nLongueur = 1, nLargueur = 6, nHauteur = 4;


	Appel0(sC2("Tp3TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
		case 1: //calcul de la densité d'un graphe simple aléatoire
			TP3Facturer(sOrigine, sDestination, nLongueur, nLargueur, nHauteur);
			break;
		default: ;
	}
	Appel1(sC2("Tp3TESTER,test n°",sEnt(iTest)));
}//Tp3TESTER	

