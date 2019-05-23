#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;


double insertion_sort(vector<int> v)
{
	double t = clock();
    for(int i = 0; i < v.size(); i++) //Todos os elementos do vetor
    {
        int big = v[i];
        int j = i - 1;
        while(j >= 0 && big < v[j])
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = big;
    }
    return (clock() - t) / CLOCKS_PER_SEC;
}

void print(vector<int> v)
{
    for(int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
}

int main()
{
	srand (time(NULL));
    vector<int> a;
	for(int i = 10000; i <= 100000; i = i + 10000)
	{
	    for(int j = 0; j < i; j++) a.push_back(rand() % 100);
	    double t = insertion_sort(a);
	    cout << t << ", ";
	    //print(b);
	    a.clear();
	}
    //print(b);
    return 0;
}
