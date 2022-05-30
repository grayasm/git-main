/* Experimenting with range-based loops and STL containers.
 */

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>

using namespace std;

main()
{
    string str { "this" " is" " a " "total" " disaster\n" };
    for (char c : str)
        cout << c;

    vector<int> vec { 1, 2, 20, 21, 100, 102 };
    for (int x : vec)
        cout << x << " ";
    cout << endl;

    list<string> lst { "this", " is", " a ", "total", " disaster\n" };
    for (const string& si : lst)
        cout << si;

    map<string, int> mp { {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}};
    for (auto it : mp)
        cout << it.first << ":" << it.second << endl;

    set<string> st { "un ", "deux ", "trois ", "quatre ", "cinq ", "six " };
    for (const string& si : st)
        cout << si;
}
/*
this is a total disaster
1 2 20 21 100 102 
this is a total disaster
one:1
three:3
two:2
zero:0
cinq deux quatre six trois un 
*/
