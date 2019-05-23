#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <list>

using namespace std;

void print(list<int> a)
{
    for(list<int>::iterator it = a.begin(); it != a.end(); it++) cout << *it << " ";
    cout << "\n";
}

double insertion_sort(list<int> a)
{
	double t = clock();
	list<int>::iterator jt;
	int big;
	for(list<int>::iterator it = a.begin(); it != a.end(); ++it)
	{
		big = *it;
		jt = it;
		if (jt != a.begin())
		{
			--jt;
			while(jt != a.begin() && *jt > big) --jt;
			if (big >= *jt) ++jt;
			a.insert(jt, big);
			a.erase(it);
		}
	}
	return (clock() - t) / CLOCKS_PER_SEC;
}

int main()
{
	srand (time(NULL));
	list<int> a;
	for(int i = 10000; i <= 100000; i = i + 10000)
	{
	    for(int j = 0; j < i; j++) a.push_back(rand() % 100);
	    double t = insertion_sort(a);
	    cout << t << ", ";
	    //print(b);
	    a.clear();
	}
    return 0;
}
