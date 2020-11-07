#pragma once
#include "ecran.h"

class play : public ecran
{
private:
	// nombre de tours
	int nbtour;

	// stocke la taille pour une remise a 0
	int local_side;

	// tableau contenant les pions
	std::vector<std::vector<int>> pionstab;  // -1 = pas de pion, 0 = blanc, 1 = noir

public:
	// constructeur
	play(int nbtour = 0);

	// fonction d'initialisation de la variable nbtour
	void setNbtour(int);

	// affichage du jeu 
	void print();

	// fonction d'initialisation du tableau des pions
	void initPiontab(int);

	// permet de remettre à 0 le tableau des pions
	void resetPiontab();
	
	// verifie si le pion pose est gagnant
	int maybewin(int, int); // 0 pas de gagnant, 1 nous avons un gagnant
	
	// fonction du bot 
	void bot(int, int);
};

