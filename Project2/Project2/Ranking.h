#pragma once
#include <cstddef>
#include<fstream>
#include<string>
using namespace std;

class Ranking
{
public:
	string film_name;
	float film_rate = 0;

	void add_film(string film_name, float film_rate, int turn, Ranking* tab); // done 
	void erase_empty_rates(); // done

	Ranking* flood();  // done 
	Ranking* make_ranking(int size); // done
	
	
   
	
	void merge_sort(Ranking* tab, int const begin, int const mid, int const end); //done
    void merge_sort_divide(Ranking* tab, int const begin, int const end); //done

	void quick_sort(Ranking* tab, int begin, int end); //done
	void swapping(Ranking* tab, int i, int j); // done

	void bucket_sort(Ranking* tab, int len); // done

	


};

