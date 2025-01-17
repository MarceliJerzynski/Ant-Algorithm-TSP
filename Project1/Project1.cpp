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
	for (int i = 0; i < 5; i++) {
	//	cities.animation("Algorytm mrowkowy");
		cities.ant_colony_algorithm(100, 100, 20, 0.9, 0.5, 0.01);//5,0.5,100,0.1 
	}
	return 0;
}
