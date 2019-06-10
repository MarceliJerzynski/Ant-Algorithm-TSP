#include "List_of_Cities.h"



List_of_Cities::List_of_Cities()
{
}

List_of_Cities::~List_of_Cities()
{
}

void List_of_Cities::load_cities(string name_file)
{
	int i = 0;
	string text;
	fstream fd;										
	fd.open("instancja.txt", ios::in | ios::out);	//otworzenie pliku
	if (fd.good() == false)							//jesli brak dostepu do pliku, wylacz program
	{
		cout << "Dostep do pliku zostal zabroniony";
		system("pause");
		exit(0);
	}

	fd >> text;
	number_of_cities = stoi(text);
	cities = new City[number_of_cities];
	while (!fd.eof())
	{
		fd >> i;
		i--;
		fd >> cities[i].x;
		fd >> cities[i].y;
	}
}

void List_of_Cities::generate_instance()
{
	int i;
	cout << "   Podaj liczbe miast: ";
	cin >> number_of_cities;
	cout << "." << endl;
	srand(time(NULL));
	for (i = 0;i < number_of_cities;i++)
	{
		cities[i].x = rand() % 100;
		cities[i].y = rand() % 100;
	}
}

void List_of_Cities::count_length()
{
	int i,j;
	length = new double *[number_of_cities];
	for (i = 0; i < number_of_cities; i++)
	{
		length[i] = new double[number_of_cities];
	}
	for (i = 0; i < number_of_cities; i++) //aktualny wierzcholek
	{
		for (j = 0; j < number_of_cities; j++) // odleglosc i tego wierzcholka do j tego
		{
			length[i][j] = sqrt(pow((cities[i].x - cities[j].x), 2) + pow((cities[i].y - cities[j].y), 2));
			length[j][i] = length[i][j];
		}
	}

	length_to_zero = new double[number_of_cities];

	for (i = 0;i < number_of_cities;i++)
	{
		length_to_zero[i] = length[0][i];
	}

}

void List_of_Cities::greedy_algorithm()
{
	int i,j;
	double min = length[0][1];
	int najblizszy = 1;
	double suma = 0;
	int x = 0; //zaczynam z wierzcholka x = 0;
	for (i = 0; i < number_of_cities; i++) //dla kazdego wierzcholka
	{
		cout << "Jestem w wierzcholku nr : " << x << endl;
		for (j = 0; j < number_of_cities; j++) //musze znalezc kolejny wierzcholek, do ktorego mam najblizej
		{
			if (length[x][j] != 0) //tam gdzie jest 0 nie ma krawedzi
			{
				if (min > length[x][j]) //jezeli minimum jest wieksze od jakiejs odleglosci
				{
					najblizszy = j; //kolejnym wierzcholkiem bedzie "najblizszy"
					min = length[x][j];
				}
			}
		}
		min = 100000000;
		suma = suma + length[x][najblizszy];
		length[x][najblizszy] = 0;
		length[najblizszy][x] = 0;
		for (j = 0;j < number_of_cities; j++)
		{
			length[x][j] = 0;
			length[j][x] = 0;
		}
		x = najblizszy;

	}
	suma = suma + length_to_zero[x];
	cout << "Calkowita odleglosc wyniosla : " << suma << endl;

}

void List_of_Cities::animation(string text)
{
	cout << "   "<<text;
	Sleep(200);
	cout << ".";
	Sleep(200);
	cout << ".";
	Sleep(200);
	cout << "." << endl;
}

void List_of_Cities::ant_colony_algorithm(int amount_of_ants, int amount_of_iterations, double B, double Y, double Q, double T0 )
{
//stworz iteratory
	int n = 0,n2 = 0; //iterator liczby miast
	int aa = 0;//iterator kazdej mrowki
	int ai = 0;//iterator glownej petli
//

//stworz tablice feromonow na kazdej krawedzi
	double **T = new double *[number_of_cities];
	for (n = 0; n < number_of_cities; n++)
	{
		T[n] = new double[number_of_cities];
	}
//

//daj wartosci poczatkowe tablicy feromonow T
	for (n = 0; n < number_of_cities; n++)
	{
		for (n2 = 0; n2 < number_of_cities; n2++)
		{
			if (n2 != n)
			{
				T[n][n2] = T0;
			}
			else
			{
				T[n][n2] = 0;
			}
		}
	}
//

// stworz tablice mrowek
	Ant *ants = new Ant[amount_of_ants];
//

//glowna petla
	for (ai = 0; ai < amount_of_iterations; ai++)
	{
	//nadawj wartosci poczatkowe mrowkom
		for (aa = 0; aa < amount_of_ants; aa++)
		{
			ants[aa].create(number_of_cities);
		}
	//

	//dla kazdej mrowki
		for (aa = 0; aa < amount_of_ants; aa++)
		{
		//dla kazdego miasta oprocz ostatniego
			for (n = 0; n < number_of_cities - 1; n++)
			{
				ants[aa].go_to_next_city(number_of_cities, T, B, length);
			}
		//
		}
	//wroc do miasta nr 0 kazda mrowka
		for (aa = 0; aa < amount_of_ants; aa++)
		{
			ants[aa].length_of_way = ants[aa].length_of_way + length[   ants[aa].position   ][0];
			ants[aa].to_visit[ants[aa].position] = 0;
			for (n = 0; n < number_of_cities; n++)
			{
				if (ants[aa].way[n] = -1)
				{
					ants[aa].way[n] = 0;
			
					break;
				}
			}
			ants[aa].position = 0;
		}
	//

	//znajdz najlepsza mrowke
		result = ants[0];
		for (aa = 1; aa < amount_of_ants; aa++)
		{
			if (ants[aa].length_of_way < result.length_of_way)
			{
				result = ants[aa];
			}
		}
	//

	//wypusc feromon
		for (n2 = 0; n2 < number_of_cities; n2++)
		{
			for (n = 0; n < number_of_cities; n++)
			{
				T[n][n2] = Y * T[n][n2];
			}
		}

		for (aa = 0; aa < amount_of_ants; aa++)	//kazda mrowka wypuszcza na kazdej krawedzi po ktorej przeszla feromon
		{
			for (n = 0; n < number_of_cities-1; n++)
			{
				T[ ants[aa].way[n] ][ants[aa].way[n + 1] ] +=  Q / ants[aa].length_of_way;
			}
		}
		//system("cls");
		//cout << ai << "/" << amount_of_iterations << endl;
	}
	//cout << "Kolejne wierzcholki : ";
	//for (n = 0; n < number_of_cities; n++)
	//{
	//	cout << endl << result.way[n];
	//}
	cout << endl << "   Najkrotsza odleglosc : " << result.length_of_way << endl;

}
