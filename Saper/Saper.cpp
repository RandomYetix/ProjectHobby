#include "pch.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

void wypisz(int size,char **tab);

void zero(int size, char **tab, char **tab_spr, int xo, int yo);

int main()
{
	int N,B,x,y;
	srand(time(NULL));
	std::cout << "Jaka wielkosc ma miec pole - ";
	std::cin >> N;
	std::cout << "Ile ma byc bomb - ";
	std::cin >> B;

	/////INICJOWANIE TABLIC/////
	char ** POLE = new char * [N];
	for (int z = 0; z < N; z++){
		POLE[z] = new char [N];
	}
	char ** POLE_SPR = new char *[N];
	for (int z = 0; z < N; z++) {
		POLE_SPR[z] = new char[N];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			POLE[j][i] = '0';
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			POLE_SPR[j][i] = '*';
		}
	}
	/////KONIEC INICJOWANIA/////

	//////BOMBY///////
	for (int i = 0; i < B; i++) {
		for (;;) {
			x = rand() % N;
			y = rand() % N;
			if (POLE[x][y] != 'X') {
				POLE[x][y] = 'X';
				if (x > 0) {
					if (y > 0) {
						if (POLE [x - 1][y - 1]!='X') POLE[x - 1][y - 1] += 1;
					}
					if (y < N - 1) {
						if (POLE[x - 1][y + 1] != 'X') POLE[x - 1][y + 1] += 1;
					}
					if (POLE[x - 1][y] != 'X') POLE[x - 1][y] += 1;
				}
				if (x < N - 1) {
					if (y > 0) {
						if (POLE[x + 1][y - 1] != 'X') POLE[x + 1][y - 1] += 1;
					}
					if (y < N - 1) {
						if (POLE[x + 1][y + 1] != 'X') POLE[x + 1][y + 1] += 1;
					}
					if (POLE[x + 1][y] != 'X') POLE[x + 1][y] += 1;
				}
				if (y > 0) {
					if (POLE[x][y - 1] != 'X') POLE[x][y - 1] += 1;
				}
				if (y < N - 1) {
					if (POLE[x][y + 1] != 'X')  POLE[x][y + 1] += 1;
				}
				break;
			}
		}
	}
	//////KONIEC BOMB//////

	wypisz(N, POLE_SPR);

	/////DZIALANIE "GRY"/////
	for (;;) {
		std::cout << "Podaj wspolrzedne x i y (wartosci od 1 do " << N << ") - ";
		std::cin >> x >> y;
		x--;
		y--;
		if (x < 0 || x > N - 1 || y < 0 || y > N - 1) {
			std::cout << "Bledna wspolrzedna"<<std::endl;
		}
		else if (POLE[x][y] == '0') {
			zero(N, POLE, POLE_SPR, x, y);
			wypisz(N, POLE_SPR);
		}
		else {
			POLE_SPR[x][y] = POLE[x][y];
			wypisz(N, POLE_SPR);
			if (POLE[x][y] == 'X') {
				std::cout << "Trafiles bombe - Porazka";
				break;
			}
		}
	}
	/////KONIEC GRY/////

	/////USUWANIE/////
	for (int z = 0; z < N; z++) {
		delete[] POLE[z];
	}
	delete[] POLE;
	for (int z = 0; z < N; z++) {
		delete[] POLE_SPR[z];
	}
	delete[] POLE_SPR;
	/////KONIEC USUWANIA/////

	return 0;
}

void wypisz(int size,char **tab) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << tab[j][i] << " ";
		}
		std::cout << "\n";
	}
}

void zero(int size, char **tab, char **tab_spr, int xo, int yo) {
	tab_spr[xo][yo] = tab[xo][yo];
	if (xo > 0) {
		if (yo > 0) {
			if (tab[xo - 1][yo - 1] != tab_spr[xo - 1][yo - 1]);
			if (tab[xo - 1][yo - 1] == '0') zero(size, tab, tab_spr, xo - 1, yo - 1);
			else tab_spr[xo - 1][yo - 1] = tab[xo - 1][yo - 1];
		}
		if (yo < size - 1) {
			tab_spr[xo - 1][yo + 1] = tab[xo - 1][yo + 1];
		}
		tab_spr[xo - 1][yo] = tab[xo - 1][yo];
	}
	if (xo < size - 1) {
		if (yo > 0) {
			tab_spr[xo + 1][yo - 1] = tab[xo + 1][yo - 1];
		}
		if (yo < size - 1) {
			tab_spr[xo + 1][yo + 1] = tab[xo + 1][yo + 1];
		}
		tab_spr[xo + 1][yo] = tab[xo + 1][yo];
	}
	if (yo > 0) {
		tab_spr[xo][yo - 1] = tab[xo][yo - 1];
	}
	if (yo < size - 1) {
		tab_spr[xo][yo + 1] = tab[xo][yo + 1];
	}
}



// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
