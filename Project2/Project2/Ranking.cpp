#include "Ranking.h"
#include <iostream>
using namespace std;



/*Funkcja typu ranking ktora dodaje nam element na nasza tablice z filmami i ocenami zalezne od tego ktore ma byc miejsce w tablicy*/
void Ranking::add_film(string name, float rate, int turn, Ranking* tab)
{
	tab[turn].film_name= name;
	tab[turn].film_rate = rate;
};

/*Funkcja typu void ktora wczytuje plik z danymi do posortowania i usuwa w nim filmy ktore nie maja oceny.*/
void Ranking::erase_empty_rates()
{
	string tmp;
	ifstream MyReadFile("projekt2_dane.csv");
	ofstream newplik("projekt_dane.txt");
	while (getline(MyReadFile, tmp))
	{

		if (tmp[tmp.length() - 1] == '0')
		{
			newplik << tmp << endl;
		}

	}
	newplik.close();
	MyReadFile.close();
}

/*Funkcja typu ranking ktora zwraca nam tablice z filmami i rankingami*/
Ranking* Ranking::flood()
{
	char XD = ',';
	int n;
	string tmp;
	ifstream MyReadFile("projekt_dane.txt");


	cout << "Prosze podac liczbe filmow do posortowania: ";
	cin >> n;
	Ranking* tab = make_ranking(n);
	if (!MyReadFile.is_open())
	{
		cout << "ty kurwo";
	}
	else
	{


		for (int i = 0; i < n; i++)
		{
			getline(MyReadFile, tmp);
			char buffer1[1000];
			int size = tmp.length();
			size_t length = tmp.copy(buffer1, 4, size - 4);
			buffer1[length] = '\0';


			tmp.erase(size - 4, length);
			if (buffer1[0] == XD)
			{
				char tmp_buffer[4];
				for (int i = 0; i < 3; i++)
				{
					tmp_buffer[i] = buffer1[i + 1];
				}
				tmp_buffer[3] = '\0';
				float ratio = atof(tmp_buffer); // ocena 1-9
				add_film(tmp, ratio, i, tab);
			}

			else
			{
				float ratio1 = atof(buffer1);   //ocena 10
				add_film(tmp, ratio1, i, tab);
			}
		}
		MyReadFile.close();
		return tab;
	}
};

/*Funkcja ktora tworzy nam tablice dynamiczna do ktorej bedziemy wpisywac filmy oraz oceny*/
Ranking* Ranking::make_ranking(int size)
{
	Ranking* tab = new Ranking[size];
	return tab;		
};

/*Sortowanie przez scalanie. Podajemy funkcji nieposortowana tablice i poprzez sortowanie przez scalanie funkcja zwraca nam posortowana tablice*/
void Ranking::merge_sort(Ranking* tab, int const left,int const mid, int const right)
{
	auto const left_tab_size = (mid - left + 1);
	auto const right_tab_size = (right - mid);

	Ranking* tab_help_left = new Ranking[left_tab_size];
	Ranking* tab_help_right = new Ranking[right_tab_size];

		for (auto i = 0; i < left_tab_size; i++)
		{

			tab_help_left[i].film_rate = tab[left+i].film_rate;
			tab_help_left[i].film_name = tab[left+i].film_name;
		}

		for (auto j = 0; j < right_tab_size; j++)
		{
			tab_help_right[j].film_rate = tab[mid+1+j].film_rate;
			tab_help_right[j].film_name = tab[mid+1+j].film_name;
		}
		
		auto  left_counter = 0; // Initial index of first sub-array
	    auto  right_counter = 0; // Initial index of second sub-array
		int  real_tab_place = left; // Initial index of merged array
		// Merge the temp arrays back into array[left..right]

	    while (left_counter < left_tab_size && right_counter < right_tab_size) 
		{
			if (tab_help_left[left_counter].film_rate <= tab_help_right[right_counter].film_rate) 
			{
				tab[real_tab_place].film_rate = tab_help_left[left_counter].film_rate;
				tab[real_tab_place].film_name = tab_help_left[left_counter].film_name;
				left_counter++;
			}
			else 
			{
				tab[real_tab_place].film_rate = tab_help_right[right_counter].film_rate;
				tab[real_tab_place].film_name = tab_help_right[right_counter].film_name;
				right_counter++;	
			}
			real_tab_place++;
		}

		/*Funkcja ktora zapelnia nam tablice jesli funkcja while z linijki 118 sie skonczyla. 
		Przypadek kiedy elementy z prawej tablicy sie skoncza a w lewej tablicy nadal sa elementy*/
		while (left_counter < left_tab_size) 
		{
			tab[real_tab_place].film_rate = tab_help_left[left_counter].film_rate;
			tab[real_tab_place].film_name = tab_help_left[left_counter].film_name;
			left_counter++;
			real_tab_place++;
		}

		/*Funkcja ktora zapelnia nam tablice jesli funkcja while z linijki 118 sie skonczyla.
		Przypadek kiedy elementy z lewej tablicy sie skoncza a w prawej tablicy nadal sa elementy*/
		while (right_counter < right_tab_size) 
		{
			tab[real_tab_place].film_rate = tab_help_right[right_counter].film_rate;
			tab[real_tab_place].film_name = tab_help_right[right_counter].film_name;
			right_counter++;
			real_tab_place++;
		}

}

void Ranking::merge_sort_divide(Ranking* tab, int const begin, int const end)
{	
	if (begin >= end)
	{
		return;
	}
	auto mid = begin + (end - begin) / 2;
	merge_sort_divide(tab, begin, mid);
	merge_sort_divide(tab, mid + 1, end);
	merge_sort(tab, begin, mid, end);
	
}

void Ranking::quick_sort(Ranking* tab, int begin, int end)
{
	
	if (end <= begin)
	{
		return;
	}

	int i = begin-1;
	int j = end+1 ;
	float pivot = tab[(begin + end) / 2].film_rate;

	while (1)
	{ 
		
		while (pivot > tab[++i].film_rate);
		
		while (pivot < tab[--j].film_rate);
		
		if (i <= j)
		{
			swapping(tab, i, j);
		}
		else
			break;
	}
	
	if (j > begin)
	{
		quick_sort(tab, begin, j);
	}
	if (i < end)
	{
		quick_sort(tab, i, end);
	}

}

void Ranking::swapping(Ranking* tab, int i, int j)
{
	string tmp_string;
	float tmp;
	tmp_string = tab[i].film_name;
	tmp = tab[i].film_rate;
	tab[i].film_rate = tab[j].film_rate;
	tab[i].film_name = tab[j].film_name;
	tab[j].film_rate = tmp;
	tab[j].film_name = tmp_string;
}

void Ranking::bucket_sort(Ranking* tab, int len)
{
	Ranking** bucket = new Ranking * [5];
	int first_counter = 0;
	int secound_counter = 0;
	int third_counter = 0;
	int fourth_counter = 0;
	int fifth_counter = 0;
	for (int i = 0; i < len; i++)
	{
		if (tab[i].film_rate == 1 || tab[i].film_rate == 2)
		{
			first_counter++;
		}
		if (tab[i].film_rate == 3 || tab[i].film_rate == 4)
		{
			secound_counter++;
		}
		if (tab[i].film_rate == 5 || tab[i].film_rate == 6)
		{
			third_counter++;
		}
		if (tab[i].film_rate == 7 || tab[i].film_rate == 8)
		{
			fourth_counter++;
		}
		if (tab[i].film_rate == 9 || tab[i].film_rate == 10)
		{
			fifth_counter++;
		}
	}

	bucket[0] = new Ranking[first_counter];
	bucket[1] = new Ranking[secound_counter];
	bucket[2] = new Ranking[third_counter];
	bucket[3] = new Ranking[fourth_counter];
	bucket[4] = new Ranking[fifth_counter];

	first_counter = 0;
	secound_counter = 0;
	third_counter = 0;
	fourth_counter = 0;
	fifth_counter = 0;


	for (int k = 0; k < len; k++)
	{
		if (tab[k].film_rate == 1 || tab[k].film_rate == 2)
		{
			bucket[0][first_counter].film_rate = tab[k].film_rate;
			bucket[0][first_counter++].film_name = tab[k].film_name;

		}
		if (tab[k].film_rate == 3 || tab[k].film_rate == 4)
		{
			bucket[1][secound_counter].film_rate = tab[k].film_rate;
			bucket[1][secound_counter++].film_name = tab[k].film_name;
		}
		if (tab[k].film_rate == 5 || tab[k].film_rate == 6)
		{
			bucket[2][third_counter].film_rate = tab[k].film_rate;
			bucket[2][third_counter++].film_name = tab[k].film_name;
		}
		if (tab[k].film_rate == 7 || tab[k].film_rate == 8)
		{
			bucket[3][fourth_counter].film_rate = tab[k].film_rate;
			bucket[3][fourth_counter++].film_name = tab[k].film_name;
		}
		if (tab[k].film_rate == 9 || tab[k].film_rate == 10)
		{
			bucket[4][fifth_counter].film_rate = tab[k].film_rate;
			bucket[4][fifth_counter++].film_name = tab[k].film_name;
		}
	}
	
	
	quick_sort(bucket[0], 0, first_counter-1);
	quick_sort(bucket[1], 0, secound_counter-1);
	quick_sort(bucket[2], 0, third_counter-1);
	quick_sort(bucket[3], 0, fourth_counter-1);
    quick_sort(bucket[4], 0, fifth_counter-1); 
	
	for(int last=0;last<len;last++)
	{
		int k = 0;
		while (first_counter > 0)
		{
			tab[last].film_rate = bucket[0][k].film_rate;
			tab[last].film_name = bucket[0][k].film_name;
			last++;
			k++;
			first_counter--;
		}
		k = 0;
		while (secound_counter > 0)
		{
			tab[last].film_rate = bucket[1][k].film_rate;
			tab[last].film_name = bucket[1][k].film_name;
			last++;
			k++;
			secound_counter--;
		}
		k = 0;
		while (third_counter > 0)
		{
			tab[last].film_rate = bucket[2][k].film_rate;
			tab[last].film_name = bucket[2][k].film_name;
			last++;
			k++;
			third_counter--;
		}
		k = 0;
		while (fourth_counter > 0)
		{
			tab[last].film_rate = bucket[3][k].film_rate;
			tab[last].film_name = bucket[3][k].film_name;
			last++;
			k++;
			fourth_counter--;
		}
		k = 0;
		while (fifth_counter > 0)
		{
			tab[last].film_rate = bucket[4][k].film_rate;
			tab[last].film_name = bucket[4][k].film_name;
			last++;
			k++;
			fifth_counter--;
		}
	}
};
