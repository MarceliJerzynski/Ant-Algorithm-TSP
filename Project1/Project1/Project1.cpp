#include <iostream>
#include "List_of_Cities.h";
#include <ctime>
int main()
{
	srand(time(NULL));
	List_of_Cities cities;
	//cities.generate_instance();
	cities.animation("Ladowanie instancji");
	cities.load_cities("instancja.txt");
	cities.animation("Liczenie dlugosci miedzy miastami");
	cities.count_length();
	//cities.animation("Algorytm zachlanny");
	//cities.greedy_algorithm();
	cities.animation("Algorytm mrowkowy");
	cities.ant_colony_algorithm(20, 40, 5, 0.5, 100, 0.1);

	return 0;
}
