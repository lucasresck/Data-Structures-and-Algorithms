#include <iostream>
#include <vector>

using namespace std;

vector<int> insertion_sort(vector<int> v)
{
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
    return v;
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
    vector<int> a;
    a.push_back(-10);
    a.push_back(3);
    a.push_back(2);
    a.push_back(1);
    a.push_back(4);
    a.push_back(9);
    a.push_back(1);
    a.push_back(0);
    a.push_back(-4);
    vector<int> b = insertion_sort(a);
    print(b);
    return 0;
}