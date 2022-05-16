#pragma once
#include <cstddef>
#include<fstream>
#include<string>
#include<time.h>
using namespace std;


//Klasa "Ranking" w ktorej znajduje sie 
class Ranking
{
public:
	string film_name;
	float film_rate = 0;

	void add_film(string film_name, float film_rate, int turn, Ranking* tab);  
	void erase_empty_rates(); 

	Ranking* flood(int sizee);  
	Ranking* make_ranking(int size); 
	
	void median(Ranking* tab, int size);
	void check(Ranking* tab, int size);
	void average_value(Ranking* tab, int size);
   
	
	void merge_sort(Ranking* tab, int const begin, int const mid, int const end); 
    void merge_sort_divide(Ranking* tab, int const begin, int const end); 

	void quick_sort(Ranking* tab, int begin, int end); 
	void swapping(Ranking* tab, int i, int j); 

	void bucket_sort(Ranking* tab, int len); 
	
	void menu(); 
};

