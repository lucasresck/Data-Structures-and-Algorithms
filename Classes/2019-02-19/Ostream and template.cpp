#include <iostream>
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <time.h>

using namespace std;

template<class T>

void insertion_sort(vector<T> &v)
{
    for(int i = 0; i < v.size(); i++) //Todos os elementos do vetor
    {
        T big = v[i];
        int j = i - 1;
        while(j >= 0 && big < v[j])
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = big;
    }
}

template<class T>

void print(vector<T> &v)
{
	std::copy(v.begin(), v.end(), ostream_iterator<T>(cout, " "));
	cout << endl;
}

int main()
{
	srand (time(NULL));
    vector<float> a;
	for(int j = 0; j < 5; j++) a.push_back((rand() % 100) / 1.00001);
	insertion_sort<float>(a);
	print<float>(a);
    return 0;
}
