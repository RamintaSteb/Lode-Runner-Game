// Lode.cpp : Defines the entry point for the console application.
//
/*
Zaidimo valdymas:
Vaiksdiojimas vyksta su rodyklemis
Duobes kasamos Z mygtuku (kaireje) arba X mygtuku (desineje)
Zaidimo esme: surinkti visas dezutes, kiekvienas priesas nesiojasi po dezute,
kuria pameta tik ikritus i duobe

Kai surenkamos visos dezutes zaidimo lango virsuje atsiranda kopecios.
Jomis uzlipus - laimima.
*/

#include "stdafx.h"
#include "action.h"
#include <iostream>



int main()
{
	GameField floor1;
	
	while (1) {
		floor1.Game();
	}
	system("PAUSE");

    return 0;
}

