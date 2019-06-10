#include "Ant.h"



Ant::Ant()
{
}


Ant::~Ant()
{
}

void Ant::create(int n)
{
	length_of_way = 0;
	int i;
	to_visit = new int[n];	
	way = new int[n];
	for (i = 1; i < n; i++)
	{
		to_visit[i] = 1;
		way[i] = -1;
	}
	position = 0;					//mrowki rozpoczynaja szukanie drogi w miescie nr 0
	way[0] = position;
	to_visit[position] = 0;

}

void Ant::go_to_next_city(int number_of_cities, double ** T, double B, double **length)
{
	int nn,nn2;
	int next;
	double omega = 0;
	double *P = new double [number_of_cities];

	for (nn = 0; nn < number_of_cities; nn++)	//nn to potencjalny next
	{
		if (to_visit[nn] == 0) //jesli juz odwiedziles
		{
			P[nn] = 0;
		}
		else
		{
			P[nn] = T[position][nn] / pow(1 / length[position][nn], B);
			omega = omega + P[nn];
		}
	}
	//sortowanie babelkowe, zmienic na quicksorta by wypadalo
	double support,support2;
	/*
	for (nn = 0; nn < number_of_cities; nn++)
	{
		for (nn2 = 1; nn2 < number_of_cities - nn; nn2++)
		{
			if (P[0][nn2 - 1] > P[0][nn2])
			{
				support = P[0][nn2 - 1];
				P[0][nn2 - 1] = P[0][nn2];
				P[0][nn2] = support;
				support = P[1][nn2 - 1];
				P[1][nn2 - 1] = P[1][nn2];
				P[1][nn2] = support;
			}
		}
	}
	*/
	

	support = (double)rand()/double(RAND_MAX)*omega;
	support2 = 0;
	double support3;
	for (nn = 0; nn < number_of_cities; nn++)
	{
		support3 = P[nn] + support2;
		if ((support >= support2) && (support < support3 ) )
		{
			next = nn;
			break;
		}
		support2 += P[nn];
		if (nn == number_of_cities - 1)
		{
			nn = 0;
			support = (double)rand() / double(RAND_MAX)*omega;
		}
	}

	length_of_way = length_of_way + length[position][next];
	to_visit[next] = 0;
	for (nn = 0; nn < number_of_cities; nn++)
	{
		if (way[nn] == -1)
		{
			way[nn] = next;
			break;
		}
	}
	position = next;

}
