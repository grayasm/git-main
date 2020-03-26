#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/* This code counts all permutations of a string. */
void permutation(string str, string prefix)
{
    if (str.length() == 0)
    {
        cout << prefix << endl;
    }
    else
    {
        for (int i = 0; i < str.length(); i++)
        {
            string rem = str.substr(0, i) + str.substr(i+1);
            permutation(rem, prefix + str.at(i));
        }
    }
}

void permutation(string str)
{
    permutation(str, "");
}

int main()
{
    permutation("abc");
    return 0;
}


/*
   This is the dishones/workaround solution :)
   using <algorithm> std::next_permutation

void permutation(string str)
{
    vector<int> vec(str.length(), 0);
    for (int i = 0; i < vec.size(); ++i)
        vec[i] = i;

    string sper = str;
    while(next_permutation(vec.begin(), vec.end()))
        {
            for (int i = 0; i < vec.size(); ++i)
                sper[i] = str[vec[i]];
            cout << sper << endl;
        }
}
*/
