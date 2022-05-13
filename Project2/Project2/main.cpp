#include<iostream>
#include"Ranking.h"
#include<time.h>
using namespace std;
int main()
{
	Ranking* essa = new Ranking;
	Ranking test;
	essa=test.flood();

	
	double time_start = (double)clock();
    //test.bucket_sort(essa, 950000);
    test.quick_sort(essa, 0, 99);
	//test.merge_sort_divide(essa, 0, 9999);
	double time_end = (double)clock();
	cout << "Uplynelo = " << (time_end - time_start)/(CLOCKS_PER_SEC) << "s." << std::endl;
};