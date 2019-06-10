#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "City.h"
#include "Ant.h"
using namespace std;
class List_of_Cities
{
	const double max_length = 100000000;
	City *cities;
	int number_of_cities;
	double **length;
	double *length_to_zero;
public:
	List_of_Cities();
	~List_of_Cities();
	void load_cities(string name_file);
	void generate_instance();
	void count_length();
	void greedy_algorithm();
	void animation(string text);
	void ant_colony_algorithm(int amount_of_ants, int amount_of_iterations, double B, double Y, double Q, double T0);
};

