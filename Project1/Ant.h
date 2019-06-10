#pragma once
#include <cmath>
#include <ctime>
#include <iostream>
using namespace std;
class Ant
{
public:
	int position;	//w ktorym miescie znajduje sie mrowka
	int *to_visit;	//tablica miast do odwiedzenia 1- nieodwiedzone, 0 - odwiedzone
	int *way;		//tablica drogi mrowki
	double length_of_way;

	Ant();
	~Ant();
	void create(int n);		// n - liczba miast
	void go_to_next_city(int number_of_cities, double **T, double B, double **length);
};

