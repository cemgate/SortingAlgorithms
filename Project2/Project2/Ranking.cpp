#include "Ranking.h"
#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;



/*!
* \brief Funkcja ktora dodaje nam film na nasza tablice 
* \param name=nazwa filmu, rate=ocena filmu, turn=miejsce na tablicy, tab=wskaznik na nasza tablice dynamiczna
*/
void Ranking::add_film(string name, float rate, int turn, Ranking* tab)
{
	tab[turn].film_name= name; //Dodajemy nazwe filmu do naszej tablicy
	tab[turn].film_rate = rate; //Dodajemy ocene filmu do naszej tablicy
};

/*!
 * \brief Funkcja ktora wczytuje plik z danymi do posortowania i usuwa w nim filmy ktore nie maja oceny. Funkcje ta uzywamy tylko raz zeby miec plik z ktorego bedziemy finalnie pobierac pliki
 */
void Ranking::erase_empty_rates()
{
	string tmp; //Tworzymy zmienna pomocnicza typu string
	ifstream MyReadFile("projekt2_dane.csv"); //Otwieramy plik przeslany na eportalu
	ofstream newplik("projekt_dane.txt"); //Tworzymy i otwieramy plik ktory bedzie przechowywal nasze filmy i oceny
	while (getline(MyReadFile, tmp))
	{

		if (tmp[tmp.length() - 1] == '0') //Sprawdzwamy czy na koncu lini znajduje sie '0' poniewaz kazda linia konczy sie ocena np. 9.0. Zadna ocena nie jest polowkowa dlatego jest to warunkiem naszego wpisania do nowego pliku
		{
			newplik << tmp << endl;  // Jesli na koncu lini jest '0' to wpisujemy dana linie na nowy plik. Jesli na koncu nie ma zera to omijamy dana linie.
		}

	}
	newplik.close();
	MyReadFile.close();
}

/*!
  * \brief Funkcja ktora dodaje nam dana ilosc filmow na nasza tablice
  * \param sizee=wielkosc tablicy dynamicznej oraz tez jest to ilosc filmow ktora dodamy na tablice
  * \return Zwraca nam nieposortowana tablice z filmami i ocenami
  */
Ranking* Ranking::flood(int sizee)
{
	
	string tmp; // Tworze pomocniczy string w ktorym bede zapisywal linie z pliku.
	ifstream MyReadFile("projekt_dane.txt"); //Otwieram plik tekstowy z ktorego bede odczytywal filmy
	Ranking* tab = make_ranking(sizee); // Tworze tablice dynamiczna typu Ranking o wielkosci sizee (sizee=ilosc filmow do wybrania w programie np. 10k, 100k)

	if (!MyReadFile.is_open()) // Jesli plik "projekt_dane.txt" nie istnieje to wyswietli nam sie informacja zwrotna, zostanie usunieta tablica tab oraz program zakonczy sie
	{
		cout << "Nie otwarto pliku";
		delete[] tab;
		exit(0);
	}
	else
	{
		for (int i = 0; i < sizee; i++) // Jesli plik "projekt_dane.txt" istnieje i zostanie otwarty to wykona sie przepisywanie filmow z pliku na tablice tyle razy ile jest rowny "sizee"
		{
			getline(MyReadFile, tmp);  //Wczytujemy linie i zapisujemy ja do zmiennej typu string tmp
			char buffer1[1000]; // Tworzymy pomocniczy buffer
			int size = tmp.length(); // Sprawdzamy dlugosc danej lini wczytanej z pliku
			size_t length = tmp.copy(buffer1, 4, size - 4); //Do buffera kopiujemy 4 ostatnie znaki ze stringa tmp poniewaz bedziemy mieli dwa przypadki. Pierwszy przypadek to jest ocena mniejsza od 10 czyli np nasze cztwery pobrane znaki to ",9.0". Drugi przypadek to ocena 10 czyli nasze cztery pobrane znaki to "10.0"
			buffer1[length] = '\0'; //Dodanie znaku konczacego ciag
			
			
			tmp.erase(size - 4, length); //Z naszego stringa usuwamy 4 ostatnie znaki (usuwamy ocene)

			

			if (buffer1[0] == ',') //Nasz pierwszy przypadek kiedy nasza ocene ma postac ",9.0"
			{
				char tmp_buffer[4]; //Tworzymy pomocniczy buffer
				for (int i = 0; i < 3; i++)
				{
					tmp_buffer[i] = buffer1[i + 1]; //Dodajemy do bufera wszystkie znaki oprocz poczatkowego przecinka
				}
				tmp_buffer[3] = '\0'; //Dodanie znaku konczacego ciag
				float ratio = atof(tmp_buffer); // Konwertujemy char na floata
				add_film(tmp, ratio, i, tab); // Dodajemy film do naszej tablicy 
			}

			else //Nasz drugi przypadek kiedy nasza ocena jest rowna 10 czyli "10.0"
			{
				float ratio1 = atof(buffer1);  //Konwertujemy  char na floata
				add_film(tmp, ratio1, i, tab); //Dodajemy film do naszej tablicy
			}
			
		}
		return tab; // Zwracamy tablice
	}
	
};

/*!
 * \brief Funkcja ktora tworzy nam tablice dynamiczna o zadanej wielkosci
 * \param size=wielkosc tablicy
 * \return Zwraca nam pusta tablice o zadanej wielkosci
 */
Ranking* Ranking::make_ranking(int size)
{
	Ranking* tab = new Ranking[size];
	return tab;		
};

/*!
* \brief Funkcja ktora sortuje nasza tablice poprzez algoryrt sortowania "Sortowanie przez scalanie"
* \param tab=wskaznik na tablice dynamiczna, left=komorka w tablicy po lewej stronie, mid=komorka posrodku, right=komorka po prawej
* \return Funkcja zwraca nam posortowana tablice
*/
void Ranking::merge_sort(Ranking* tab, int const left,int const mid, int const right)
{
	auto const left_tab_size = (mid - left + 1); //Obliczamy jaki bedzie miala rozmiar nasza tab_help_left
	auto const right_tab_size = (right - mid);  //Obliczamy jaki bedzie miala rozmiar nasza tab_help_right

	Ranking* tab_help_left = new Ranking[left_tab_size]; //Tworzymy tablice tab_help_left o zadanej wielkosci
	Ranking* tab_help_right = new Ranking[right_tab_size]; //Tworzymy tablice tab_help_right o zadanej wielkosci

		for (auto i = 0; i < left_tab_size; i++) //Dodajemy na tablice pomocnicza elementy z naszej tablicy filmow
		{
			tab_help_left[i].film_rate = tab[left+i].film_rate;
			tab_help_left[i].film_name = tab[left+i].film_name;
		}

		for (auto j = 0; j < right_tab_size; j++) //Dodajemy na tablice pomocnicza elementy z naszej tablicy filmow
		{
			tab_help_right[j].film_rate = tab[mid+1+j].film_rate;
			tab_help_right[j].film_name = tab[mid+1+j].film_name;
		}
		
		auto  left_counter = 0; // Licznik naszej lewej pomocnicznej tablicy
	    auto  right_counter = 0; //  Licznik naszej prawej pomocnicznej tablicy
		int  real_tab_place = left; // Licznik naszej prawdziwej tablicy
		

	    while (left_counter < left_tab_size && right_counter < right_tab_size) // petla w ktorej bedziemy zamieniac nasze filmy z tablicy prawdziwej na filmy z naszych tablic pomocniczych poniewaz sa one juz posortowane dopoki dwa warunki podane w petli beda spelnione
		{
			if (tab_help_left[left_counter].film_rate <= tab_help_right[right_counter].film_rate) // Jesli ocena filmu z lewej tablicy jest mniejsza lub rowna to film z lewej tablicy wskoczy na tablice prawdziwa
			{
				tab[real_tab_place].film_rate = tab_help_left[left_counter].film_rate;
				tab[real_tab_place].film_name = tab_help_left[left_counter].film_name;
				left_counter++;
			}
			else // W przeciwnym przypadku dodajemy na nasza prawdziwa tablice film z prawej tablicy
			{
				tab[real_tab_place].film_rate = tab_help_right[right_counter].film_rate;
				tab[real_tab_place].film_name = tab_help_right[right_counter].film_name;
				right_counter++;	
			}
			real_tab_place++;
		}

		/*Petla ktora zapelnia nam prawdziwa tablice jesli petla while z linijki 139 sie skonczyla. 
		Przypadek kiedy elementy z prawej tablicy sie skoncza a w lewej tablicy nadal sa elementy*/
		while (left_counter < left_tab_size) 
		{
			tab[real_tab_place].film_rate = tab_help_left[left_counter].film_rate;
			tab[real_tab_place].film_name = tab_help_left[left_counter].film_name;
			left_counter++;
			real_tab_place++;
		}

		/*Petla ktora zapelnia nam prawdziwa tablice jesli funkcja while z linijki 139 sie skonczyla.
		Przypadek kiedy elementy z lewej tablicy sie skoncza a w prawej tablicy nadal sa elementy*/
		while (right_counter < right_tab_size) 
		{
			tab[real_tab_place].film_rate = tab_help_right[right_counter].film_rate;
			tab[real_tab_place].film_name = tab_help_right[right_counter].film_name;
			right_counter++;
			real_tab_place++;
		}
		delete[] tab_help_left; // uwuwamy z pamieci pomocnicze tablice
		delete[] tab_help_right;
}

/*!
* \brief Funkcja ktora rekurencyjnie dzieli nam nasza tablice na mniejsze tablice do momentu az bedziemy mieli tablice dwuelementowe
* \param tab=Wskaznik na nasza tablice filmow, begin=poczatek tablicy czyli do posortowania calej tablicy jest to wartosc '0', end=wielkosc tablicy pomniejszona o 1 (pomniejszona o 1 poniewaz obliczanie srodka w srodku tej funkcji potrzebuje zeby byla to wartosc pomniejszona o 1)
*/
void Ranking::merge_sort_divide(Ranking* tab, int const begin, int const end)
{	
	if (begin >= end)
	{
		return; //Warunek zakonczenia dzielenie naszej tablicy
	}
	auto mid = begin + (end - begin) / 2; // Obliczanie srodka tablicy
	merge_sort_divide(tab, begin, mid); //Wywolanie tej samej funkcji tylko teraz koncem jest srodek tablicy, przy pierwszym wywolaniu spowodouje to ze bedziemy dzielic nasza tablice z lewej strony na coraz mniejsze tablice
	merge_sort_divide(tab, mid + 1, end); // Wywolanie tej funkcji bedzie nam dzielic nasza prawa czesc tablicy na coraz mniejsze fragmenty tablic do momentu az beda to tablice o 2 elementach
	merge_sort(tab, begin, mid, end); //Scalanie tablic
	
}

/*!
* \brief Funkcja ktora sortuje nam nasza tablice filmow algorytem "Quick sort"
* \param tab=wskaznik na tablice filmow, begin=poczat tablicy, end=koniec tablicy
*/
void Ranking::quick_sort(Ranking* tab, int begin, int end)
{
	
	if (end <= begin)
	{
		return; //Warunek przerwania funkcji
	}

	int i = begin-1;
	int j = end+1 ;
	float pivot = tab[(begin + end) / 2].film_rate; //Sprawdzanie jaka wartosc ma nasza ocena posrodku tablicy

	while (1)
	{ 
		
		while (pivot > tab[++i].film_rate); // Sprawdzanie czy jest wartosc wieksza od naszej wartosci srodkowej po lewej czesci tablicy
		
		while (pivot < tab[--j].film_rate); // Sprwadzanie czy jest wartosc mniejsza od naszej wartosci srodkowej po prawej czesci tablicy
		
		if (i <= j)
		{
			swapping(tab, i, j); // Wywolanie funkcji "swapping" ktore spowodouje ze dane dwa filmy o indeksach "i" oraz "j" zamienia sie miejscami w tablicy
		}
		else
			break;
	}
	
	if (j > begin)
	{
		quick_sort(tab, begin, j); // Wywowalnie quicksorta dla mniejszej tablicy
	}
	if (i < end)
	{
		quick_sort(tab, i, end);  // Wywowalnie quicksorta dla mniejszej tablicy
	}

}

/*!
* \brief Funkcja ktora zamienia nam miejscami dwa filmy ze soba
* \param tab=wskaznik na tablice filmow, i=miejsce w tablicy ktore bedzie zamienione, j=miejsce w tablicy ktore bedzie zamienione
*/
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

/*!
* \brief Funkcja ktora sortuje nam tablice filmow algorytem "Sortowanie kubelkowe"
* \param tab=wskaznik na tablice, len=rzeczywista ilosc elementow w tablicy
*/
void Ranking::bucket_sort(Ranking* tab, int len)
{
	Ranking** bucket = new Ranking * [5]; //Tworze dwywymiarowa tablice dynamiczna poniewaz bede dzielil nasza tablice na 5 "wiader". Kazde wiadro bede sortowal algorytmen "quick sort"
	int first_counter = 0; // Licznik ile powinno znajdowac sie elementow w pierwszym wiadrze 
	int secound_counter = 0; // Licznik ile powinno znajdowac sie elementow w drugim wiadrze
	int third_counter = 0; // Licznik ile powinno znajdowac sie elementow w trzecim wiadrze
	int fourth_counter = 0; // Licznik ile powinno znajdowac sie elementow w czwartym wiadrze
	int fifth_counter = 0; // Licznik ile powinno znajdowac sie elementow w piatym wiadrze
	for (int i = 0; i < len; i++)
	{
		if (tab[i].film_rate == 1 || tab[i].film_rate == 2) // Pierwsze wiadro bedzie przechowywalo elementy o wartosci oceny filmu od 1 do 2
		{
			first_counter++; // ZLiczanie elementow do pierwszego wiadra
		}
		if (tab[i].film_rate == 3 || tab[i].film_rate == 4) // Drugie wiadro bedzie przechowywalo elementy o wartosci oceny filmu od 2 do 4
		{
			secound_counter++; // ZLiczanie elementow do drugiego wiadra
		}
		if (tab[i].film_rate == 5 || tab[i].film_rate == 6) // Trzecie wiadro bedzie przechowywalo elementy o wartosci oceny filmu od 5 do 6
		{
			third_counter++; // ZLiczanie elementow do trzeciego wiadra
		}
		if (tab[i].film_rate == 7 || tab[i].film_rate == 8) // Czwarte wiadro bedzie przechowywalo elementy o wartosci oceny filmu od 7 do 8
		{
			fourth_counter++; // ZLiczanie elementow do czwartego wiadra
		}
		if (tab[i].film_rate == 9 || tab[i].film_rate == 10) // Piate wiadro bedzie przechowywalo elementy o wartosci oceny filmu od 9 do 10
		{
			fifth_counter++; // ZLiczanie elementow do piatego wiadra
		}
	}

	/*Tworzenie tablic pomocnicznych (wiader) o zadanym rozmiarze*/
	bucket[0] = new Ranking[first_counter]; 
	bucket[1] = new Ranking[secound_counter];
	bucket[2] = new Ranking[third_counter];
	bucket[3] = new Ranking[fourth_counter];
	bucket[4] = new Ranking[fifth_counter];

	/*Zeruje liczniki poniewaz bede ich teraz uzywal zeby wpisac elementy do moich wiader*/
	first_counter = 0;
	secound_counter = 0;
	third_counter = 0;
	fourth_counter = 0;
	fifth_counter = 0;


	for (int k = 0; k < len; k++) //Petla ktora wykona sie "len" razy czyli tyle ile jest elementow na naszej tablicy filmow
	{
		if (tab[k].film_rate == 1 || tab[k].film_rate == 2) //Jesli ocena filmu znajduje jest 1 albo 2 to dodajemy film do pierwszego wiadra
		{
			bucket[0][first_counter].film_rate = tab[k].film_rate;
			bucket[0][first_counter++].film_name = tab[k].film_name;

		}
		if (tab[k].film_rate == 3 || tab[k].film_rate == 4) //Jesli ocena filmu znajduje jest 3 albo 4 to dodajemy film do drugiego wiadra
		{
			bucket[1][secound_counter].film_rate = tab[k].film_rate;
			bucket[1][secound_counter++].film_name = tab[k].film_name;
		}
		if (tab[k].film_rate == 5 || tab[k].film_rate == 6) //Jesli ocena filmu znajduje jest 5 albo 6 to dodajemy film do trzeciego wiadra
		{
			bucket[2][third_counter].film_rate = tab[k].film_rate;
			bucket[2][third_counter++].film_name = tab[k].film_name;
		}
		if (tab[k].film_rate == 7 || tab[k].film_rate == 8) //Jesli ocena filmu znajduje jest 7 albo 8 to dodajemy film do czwartego wiadra
		{
			bucket[3][fourth_counter].film_rate = tab[k].film_rate;
			bucket[3][fourth_counter++].film_name = tab[k].film_name;
		}
		if (tab[k].film_rate == 9 || tab[k].film_rate == 10) //Jesli ocena filmu znajduje jest 9 albo 10 to dodajemy film do piatego wiadra
		{
			bucket[4][fifth_counter].film_rate = tab[k].film_rate;
			bucket[4][fifth_counter++].film_name = tab[k].film_name;
		}
	}
	
	/*Wykonujemy sortowanie dla poszczegolnych wiader*/
	quick_sort(bucket[0], 0, first_counter-1);
	quick_sort(bucket[1], 0, secound_counter-1);
	quick_sort(bucket[2], 0, third_counter-1);
	quick_sort(bucket[3], 0, fourth_counter-1);
    quick_sort(bucket[4], 0, fifth_counter-1); 
	
	for(int last=0;last<len;last++) //Petla w ktorej bede wpisywal posortowane wiadra do naszej tablicy filmow zeby miec cala posortowana tablice
	{
		int k = 0;
		while (first_counter > 0) // Wpisujemy po kolei filmy z pierwszego wiadra do naszej tablicy filmow
		{
			tab[last].film_rate = bucket[0][k].film_rate;
			tab[last].film_name = bucket[0][k].film_name;
			last++;
			k++;
			first_counter--;
		}
		k = 0;
		while (secound_counter > 0)// Wpisujemy po kolei filmy z drugiego wiadra do naszej tablicy filmow
		{
			tab[last].film_rate = bucket[1][k].film_rate;
			tab[last].film_name = bucket[1][k].film_name;
			last++;
			k++;
			secound_counter--;
		}
		k = 0;
		while (third_counter > 0)// Wpisujemy po kolei filmy z trzeciego wiadra do naszej tablicy filmow
		{
			tab[last].film_rate = bucket[2][k].film_rate;
			tab[last].film_name = bucket[2][k].film_name;
			last++;
			k++;
			third_counter--;
		}
		k = 0;
		while (fourth_counter > 0)// Wpisujemy po kolei filmy z czwartego wiadra do naszej tablicy filmow
		{
			tab[last].film_rate = bucket[3][k].film_rate;
			tab[last].film_name = bucket[3][k].film_name;
			last++;
			k++;
			fourth_counter--;
		}
		k = 0;
		while (fifth_counter > 0)// Wpisujemy po kolei filmy z piatego wiadra do naszej tablicy filmow
		{
			tab[last].film_rate = bucket[4][k].film_rate;
			tab[last].film_name = bucket[4][k].film_name;
			last++;
			k++;
			fifth_counter--;
		}
		/*Usuwam z pamieci tablice*/
		delete[] bucket[0];
		delete[] bucket[1];
		delete[] bucket[2];
		delete[] bucket[3];
		delete[] bucket[4];
		delete[] bucket;
	}
};

/*!
* \brief Funkcja ktora wyswietla nam mediane rankingu
* \param tab=wskaznik na tablice filmow, size=wielkosc tablicy
*/
void Ranking::median(Ranking* tab, int size)
{
	if (size % 2 == 0)
	{
		cout << "Mediana rankingu wynosi:" << (tab[(size / 2) - 1].film_rate + tab[size/2].film_rate)/2<< endl;
	}
	else
	{
		cout << "Mediana rankingu wynosi:" << tab[size / 2].film_rate << endl;
	}
}

/*!
* \brief Funkcja ktora sprawdza nam czy dobrze posortowalismy, jesli sortowanie nie zostalo wykonane prawidlowo to zostaniemy o tym poinformowani 
* \param tab=wskaznik na tablice filmow, size=wielkosc tablicy
*/
void Ranking::check(Ranking* tab, int size)
{
	for (int i = 0; i < size-1; i++)
	{
		if (tab[i].film_rate > tab[i + 1].film_rate)
		{
			cout << "SORTOWANIE NIE POWIODLO SIE" << endl;
		}
	}
}

/*!
* \brief Funkcja ktora wyswietli nam srednia wartosc oceny filmu
* \param tab=wskaznik na tablice filmow, size=wielkosc tablicy
*/
void Ranking::average_value(Ranking* tab, int size)
{
	float average = 0;
	for (int i = 0; i < size; i++)
	{
	    average += tab[i].film_rate;
	}
	cout << "Srednia wartosc oceny filmu wynosi:" << average / size << endl;
}


/*!
* Funkcja ktora odpali nam caly program.
*/
void Ranking::menu()
{
	/* WAZNE!!!!!!!!!!!!!!!!!!! Opisze tylko jednego "case" poniewaz wszystkie inne sa identyczne */
	

	Ranking* list = new Ranking; //Tworzenie tablicy dynamicznej
	Ranking test; //Tworzenie obiektu naszej klasy zeby wywolywac funkcje
	char tmp[1];
	int wybor; 
	cout << "WITAMY W PRZEDPROGRAMIE DO SORTOWANIA FILMOW" << endl;
	cout << "Czy posiadasz plik tekstowy 'plik_dane.txt' ktory jest przefiltrowany? (nie znajduja sie na nim filmy bez oceny)" << endl;
	cout << "1.Posiadam taki plik" << endl;
	cout << "2.Nie posiadam takiego pliku." << endl;
	begin:
	cin >> tmp;
	if (tmp[0] == '1')// Jesli mamy juz przefiltrowany plik to idziemy do prawdziwego programu
	{
		goto here;
	}
	if (tmp[0]=='2')
	{
		test.erase_empty_rates(); //Jesli nie mamy przefiltrowane pliku to stworzy nam taki a potem przejdzie do prawdziwego programu
		goto here;
	}
	if (tmp[0]!= '1' && tmp[0]!='2')
	{
		cout << "Prosze wybrac opcje raz jeszcze" << endl; //Jesli zle cos wpisalismy to powrocimy do wybrania opcji czy mamy taki plik czy nie 
		goto begin;
	}

	while (1)
	{
		here:
		cout << endl;
		cout << "PROGRAM DO SORTOWANIA LISTY FILMOW" << endl;
		cout << "Wybierz ile filmow chcesz posortowac opcje:" << endl;
		cout << "1.10k" << endl;
		cout << "2.100k" << endl;
		cout << "3.500k" << endl;
		cout << "4.MAX" << endl;
		cout << "5.Wpisz liczbe filmow recznie" << endl;
		cout << "6.Koniec dzialania programu" << endl;
		cin >> wybor;

		switch (wybor) //Na podstawie wyboru odpala sie kolejne casy
		{
		case 1:
		{
			list=test.flood(10000); // Tworzenie listy z filmami o wielkosc o 10k

			int wybor1; 
			cout << "Jakim algorytmem posortowac?" << endl;
			cout << "1.Merge sort" << endl;
			cout << "2.Quick sort" << endl;
			cout << "3.Bucket sort" << endl;
			cin >> wybor1; // Wybieranie jakim sortowaniem posortowac liste

			switch (wybor1)
			{
			case 1:
			{
				
	            double time_start = (double)clock(); // Odpalamy zegar zeby obliczyc ile zajelo nam sortowanie
	            test.merge_sort_divide(list, 0, 9999); // Sortowanie algorytem "merge sort"
                double time_end = (double)clock(); // Zastopowanie zegara 
	            cout << "Uplynelo = " << (time_end - time_start)/(CLOCKS_PER_SEC) << "s." << endl; // Obliczanie i wyswietlanie naszego czasu sortowania
				cout << "" << endl;
				test.median(list, 10000); // Wyswietlanie mediany
				test.check(list, 10000); // Sprawdzanie czy prawidlowo posortowalismy nasze filmy. Brak informacji zwrotnej oznacza ze sortowanie przebieglo prawidlowo
				test.average_value(list, 10000); // Wyswietlanie sredniej wartosci oceny filmu
				delete[] list; // usuwanie listy z filmami z pamieci
				break;
			}

			case 2:
			{
				double time_start = (double)clock();
				test.quick_sort(list, 0, 9999);
				double time_end = (double)clock();
				cout << "Uplynelo = " << (time_end - time_start) / (CLOCKS_PER_SEC) << "s." << endl;
				cout << "" << endl;
				test.median(list, 10000);
				test.check(list, 10000);
				test.average_value(list, 10000);
				delete[] list;
				break;
			}

			case 3:
			{
				double time_start = (double)clock();
				test.bucket_sort(list, 10000);
				double time_end = (double)clock();
				cout << "Uplynelo = " << (time_end - time_start) / (CLOCKS_PER_SEC) << "s." << endl;
				cout << "" << endl;
				test.median(list, 10000);
				test.check(list, 10000);
				test.average_value(list, 10000);
				delete[] list;
				break;
			}
			}
			break;
		}
		case 2:
		{
			list = test.flood(100000);
			int wybor2;
			cout << "Jakim algorytmem posortowac?" << endl;
			cout << "1.Merge sort" << endl;
			cout << "2.Quick sort" << endl;
			cout << "3.Bucket sort" << endl;
			cin >> wybor2;
			switch (wybor2)
			{
			case 1:
			{
				double time_start = (double)clock();
				test.merge_sort_divide(list, 0, 99999);
				double time_end = (double)clock();
				cout << "Uplynelo = " << (time_end - time_start) / (CLOCKS_PER_SEC) << "s." << endl;
				cout << "" << endl;
				test.median(list, 100000);
				test.check(list, 100000);
				test.average_value(list, 100000);
				delete[] list;
				break;
			}

			case 2:
			{
				double time_start = (double)clock();
				test.quick_sort(list, 0, 99999);
				double time_end = (double)clock();
				cout << "Uplynelo = " << (time_end - time_start) / (CLOCKS_PER_SEC) << "s." << endl;
				cout << "" << endl;
				test.median(list, 100000);
				test.check(list, 100000);
				test.average_value(list, 100000);
				delete[] list;
				break;
			}

			case 3:
			{
				double time_start = (double)clock();
				test.bucket_sort(list, 100000);
				double time_end = (double)clock();
				cout << "Uplynelo = " << (time_end - time_start) / (CLOCKS_PER_SEC) << "s." << endl;
				cout << "" << endl;
				test.median(list, 100000);
				test.check(list, 100000);
				test.average_value(list, 100000);
				delete[] list;
				break;
			}
			}
			break;
		}
		case 3:
		{
			list = test.flood(500000);
			int wybor3;
			cout << "Jakim algorytmem posortowac?" << endl;
			cout << "1.Merge sort" << endl;
			cout << "2.Quick sort" << endl;
			cout << "3.Bucket sort" << endl;
			cin >> wybor3;

			switch (wybor3)
			{
			case 1:
			{
				double time_start = (double)clock();
				test.merge_sort_divide(list, 0, 499999);
				double time_end = (double)clock();
				cout << "Uplynelo = " << (time_end - time_start) / (CLOCKS_PER_SEC) << "s." << endl;
				cout << "" << endl;
				test.median(list, 500000);
				test.check(list, 500000);
				test.average_value(list, 500000);
				delete[] list;
				break;
			}

			case 2:
			{
				double time_start = (double)clock();
				test.quick_sort(list, 0, 499999);
				double time_end = (double)clock();
				cout << "Uplynelo = " << (time_end - time_start) / (CLOCKS_PER_SEC) << "s." << endl;
				cout << "" << endl;
				test.median(list, 500000);
				test.check(list, 500000);
				test.average_value(list, 500000);
				delete[] list;
				break;
			}

			case 3:
			{
				double time_start = (double)clock();
				test.bucket_sort(list, 500000);
				double time_end = (double)clock();
				cout << "Uplynelo = " << (time_end - time_start) / (CLOCKS_PER_SEC) << "s." << endl;
				cout << "" << endl;
				test.median(list, 500000);
				test.check(list, 500000);
				test.average_value(list, 500000);
				delete[] list;
				break;
			}
			}
			break;
		}
		case 4:
		{
			list = test.flood(962903);
			int wybor4;
			cout << "Jakim algorytmem posortowac?" << endl;
			cout << "1.Merge sort" << endl;
			cout << "2.Quick sort" << endl;
			cout << "3.Bucket sort" << endl;
			cin >> wybor4;

			switch (wybor4)
			{
			case 1:
			{
				double time_start = (double)clock();
				test.merge_sort_divide(list, 0, 962903-1);
				double time_end = (double)clock();
				cout << "Uplynelo = " << (time_end - time_start) / (CLOCKS_PER_SEC) << "s." << endl;
				cout << "" << endl;
				test.median(list, 962903);
				test.check(list, 962903);
				test.average_value(list, 962903);
				delete[] list;
				break;
			}

			case 2:
			{
				double time_start = (double)clock();
				test.quick_sort(list, 0,  962903-1);
				double time_end = (double)clock();
				cout << "Uplynelo = " << (time_end - time_start) / (CLOCKS_PER_SEC) << "s." << endl;
				cout << "" << endl;
				test.median(list, 962903);
				test.check(list, 962903);
				test.average_value(list, 962903);
				delete[] list;
				break;
			}

			case 3:
			{
				double time_start = (double)clock();
				test.bucket_sort(list, 962903);
				double time_end = (double)clock();
				cout << "Uplynelo = " << (time_end - time_start) / (CLOCKS_PER_SEC) << "s." << endl;
				cout << "" << endl;
			    test.median(list, 962903);
				test.check(list, 962903);
				test.average_value(list, 962903);
				delete[] list;
				break;
			}
			}
			break;
		}
		case 5:
		{
			int howmany;
			cout << "Ile filmow chcesz posortowac:";
			back:
			cin >> howmany;
			if (howmany > 962903)
			{
				cout << "Jest to wiecej filmow niz jest na liscie. Wpisz liczbe filmow raz jeszcze:";
					goto back;
			}
			list = test.flood(howmany);

			int wybor5;
			cout << "Jakim algorytmem posortowac?" << endl;
			cout << "1.Merge sort" << endl;
			cout << "2.Quick sort" << endl;
			cout << "3.Bucket sort" << endl;
			cin >> wybor5;

			switch (wybor5)
			{
			case 1:
			{
				double time_start = (double)clock();
				test.merge_sort_divide(list, 0, howmany - 1);
				double time_end = (double)clock();
				cout << "Uplynelo = " << (time_end - time_start) / (CLOCKS_PER_SEC) << "s." << endl;
				cout << "" << endl;
				test.median(list, howmany);
				test.check(list, howmany);
				test.average_value(list, howmany);
				delete[] list;
				break;
			}

			case 2:
			{
				double time_start = (double)clock();
				test.quick_sort(list, 0, howmany - 1);
				double time_end = (double)clock();
				cout << "Uplynelo = " << (time_end - time_start) / (CLOCKS_PER_SEC) << "s." << endl;
				cout << "" << endl;
				test.median(list, howmany);
				test.check(list, howmany);
				test.average_value(list, howmany);
				delete[] list;
				break;
			}

			case 3:
			{
				double time_start = (double)clock();
				test.bucket_sort(list, howmany);
				double time_end = (double)clock();
				cout << "Uplynelo = " << (time_end - time_start) / (CLOCKS_PER_SEC) << "s." << endl;
				cout << "" << endl;
				test.median(list, howmany);
				test.check(list, howmany);
				test.average_value(list, howmany);
				delete[] list;
				break;
			}
			}
			break;
		}

		case 6:
		{
			cout << "Zegnamy";
			exit(0);
			break;
		}

		default:
			break;

		}

	}
	
};